// RpAtomicPSGL.cpp - see RpAtomicPSGL.h. The PSGL atomic pipeline's instancing and mesh dispatch for the geometries of
// the level files (C2.4 step 3).
//
//   [x] 0x0069d180  RW_RenderAtomicThroughPipeline  (the chain to the mesh callbacks; no RxPipeline objects)
//   [x] 0x006bafc8  DispatchPSGLPipelineMeshes
//   [x] 0x006bb940  RwPSGL_CreateMeshInstanceData_maybe  (device meshes instead of GL buffer names)
//   [x] 0x006baec0  RwPSGL_ReinstanceMeshes_maybe  (a generic geometry locked since its last instance is instanced again)
//   [x] 0x006b99d0  RwPSGL_AtomicReinstanceCallback_maybe
#include "Renderware/rpworld/RpAtomicPSGL.h"

#include <algorithm>
#include <cstring>
#include <vector>

#include "Renderware/rpskin/RpSkin.h"
#include "Renderware/rpworld/RpAtomic.h"
#include "Renderware/rpworld/RpGeometry.h"
#include "Renderware/rwcore/RwCamera.h"
#include "k2000/core/Stub.h"
#include "k2000/render/CShaderManagerPSGL.h"
#include "k2000/render/ShaderMatrixCache.h"
#include "platform/gfx/mesh.h"

namespace {

uint32_t Swap32(uint32_t v) { return (v >> 24) | ((v >> 8) & 0xff00u) | ((v << 8) & 0xff0000u) | (v << 24); }

// The shader input slots of the mesh's attributes (cg_to_glsl.h: POSITION 0, BLENDWEIGHT 1, NORMAL 2, COLOR0 3,
// BLENDINDICES 7, TEXCOORD0.. 8, TANGENT 14).
constexpr uint8_t kLocPosition = 0, kLocBlendWeight = 1, kLocNormal = 2, kLocColor = 3, kLocBlendIndices = 7,
                  kLocTexCoord0 = 8, kLocTangent = 14;

std::vector<dotd::gfx::MeshAttribute> AttributesOf(const RpNativeMesh& m) {
    std::vector<dotd::gfx::MeshAttribute> attributes;
    attributes.push_back({kLocPosition, 3, false, 0});
    if ((m.format & rpGEOMETRYNORMALS) != 0) attributes.push_back({kLocNormal, 3, false, m.normalOffset});
    if ((m.format & rpGEOMETRYPRELIT) != 0) attributes.push_back({kLocColor, 4, true, m.colorOffset});
    if ((m.format & (rpGEOMETRYTEXTURED | rpGEOMETRYTEXTURED2)) != 0) attributes.push_back({kLocTexCoord0, 2, false, m.uvOffset[0]});
    if ((m.format & rpGEOMETRYTEXTURED2) != 0) attributes.push_back({static_cast<uint8_t>(kLocTexCoord0 + 1), 2, false, m.uvOffset[1]});
    // DrawPSGLMeshPasses: the tangent (cgGLSetParameterPointer slot 0xe) when the mesh has one (word 28) and the
    // geometry format asks for it (0x200).
    if (m.word28 != 0 && (m.format & 0x200) != 0) attributes.push_back({kLocTangent, 3, false, m.tangentOffset});
    // DrawPSGLMeshPasses: a mesh with skin attributes (word 29, dwHasSkinAttributes) binds its four weights on slot 1
    // and its four bone indices on slot 7, both as floats (cgGLSetParameterPointer(1 / 7, 4, GL_FLOAT, 0, stride,
    // word 26 / word 27)). The native data stores the indices as floats (RpSkinPSGL_AtomicInstanceCallback_maybe
    // 0x774a38 converts a generic skin's index bytes the same way); the uber-shader indexes the palette with them.
    if (m.word29 != 0) {
        attributes.push_back({kLocBlendWeight, 4, false, m.word26});
        attributes.push_back({kLocBlendIndices, 4, false, m.word27});
    }
    return attributes;
}

// A native geometry: the PS3 vertex and index buffers (big-endian) converted for the host.
bool InstanceNative(RpGeometry* geometry, RpGeometryDevice* device) {
    RpNativeGeometry* native = geometry->repEntry;
    if (native == nullptr || native->meshes.empty()) return false;
    for (size_t index = 0; index < native->meshes.size(); ++index) {
        RpDeviceMesh deviceMesh;
        deviceMesh.record = native->meshes[index];
        RpNativeMesh& m = deviceMesh.record;
        if (index == 0 && !native->vertexData.empty()) {  // the file holds the buffers of the first mesh only
            std::vector<uint8_t> vertices = native->vertexData;
            for (uint32_t v = 0; v < m.numVertices; ++v) {
                uint8_t* vertex = vertices.data() + static_cast<size_t>(v) * m.stride;
                for (uint32_t off = 0; off + 4 <= m.stride; off += 4) {
                    if ((m.format & rpGEOMETRYPRELIT) != 0 && off == m.colorOffset) continue;  // 4 bytes, not a float
                    uint32_t word;
                    std::memcpy(&word, vertex + off, 4);
                    word = Swap32(word);
                    std::memcpy(vertex + off, &word, 4);
                }
            }
            std::vector<uint32_t> indices(native->indexData.size() / 4);
            for (size_t i = 0; i < indices.size(); ++i) {
                uint32_t word;
                std::memcpy(&word, native->indexData.data() + i * 4, 4);
                indices[i] = Swap32(word);
            }
            const std::vector<dotd::gfx::MeshAttribute> attributes = AttributesOf(m);
            deviceMesh.gfxMesh = dotd::gfx::CreateMesh(vertices.data(), vertices.size(), m.stride,
                                                       indices.empty() ? nullptr : indices.data(), indices.size(),
                                                       attributes.data(), static_cast<int>(attributes.size()));
        }
        device->meshes.push_back(deviceMesh);
    }
    return true;
}

// A generic geometry (RW's vertex arrays and the bin mesh): the interleaved layout the PS3 driver builds for native
// data, position, normal, prelit colour, the texture coordinate sets, one mesh per bin-mesh entry. `reuse` (perf): the
// device meshes of the geometry's last instance (a geometry instanced again): the n-th new mesh takes the n-th old one's
// GL objects with the new contents when the layout is the same (gfx::UpdateMesh); the old meshes not taken are destroyed.
bool InstanceGeneric(RpGeometry* geometry, RpGeometryDevice* device, RpGeometryDevice* reuse = nullptr) {
    struct DestroyUnused {  // (on every return path)
        RpGeometryDevice* reuse;
        ~DestroyUnused() {
            if (reuse == nullptr) return;
            for (RpDeviceMesh& mesh : reuse->meshes) {
                if (mesh.gfxMesh != 0) dotd::gfx::DestroyMesh(mesh.gfxMesh);
            }
        }
    } destroyUnused{reuse};
    size_t reuseIndex = 0;
    if (geometry->mesh == nullptr || geometry->morphTarget == nullptr || geometry->numVertices <= 0) return false;
    const RwV3d* positions = geometry->morphTarget[0].verts;
    if (positions == nullptr) return false;
    const RwV3d* normals = geometry->morphTarget[0].normals;
    const uint32_t format = geometry->flags;
    const bool hasNormals = (format & rpGEOMETRYNORMALS) != 0 && normals != nullptr;
    const bool hasColors = (format & rpGEOMETRYPRELIT) != 0 && geometry->preLitLum != nullptr;
    const int uvSets = std::min<int>(geometry->numTexCoordSets, 2);
    RpNativeMesh layout = {};
    layout.format = (format & ~(rpGEOMETRYNORMALS | rpGEOMETRYPRELIT | rpGEOMETRYTEXTURED | rpGEOMETRYTEXTURED2)) |
                    (hasNormals ? rpGEOMETRYNORMALS : 0u) | (hasColors ? rpGEOMETRYPRELIT : 0u) |
                    (uvSets >= 1 ? rpGEOMETRYTEXTURED : 0u) | (uvSets >= 2 ? rpGEOMETRYTEXTURED2 : 0u);
    uint32_t stride = 12;
    if (hasNormals) { layout.normalOffset = stride; stride += 12; }
    if (hasColors) { layout.colorOffset = stride; stride += 4; }
    for (int set = 0; set < uvSets; ++set) { layout.uvOffset[set] = stride; stride += 8; }
    // A skinned geometry: the skin pipeline's instance callback RpSkinPSGL_AtomicInstanceCallback_maybe 0x774a38 puts the
    // weights and bone indices after the attributes (none in the level files: every skin is on native data).
    if (geometry->skin != nullptr) stride = RpSkinPSGL_InstanceLayout(geometry, &layout, stride);
    layout.stride = stride;
    layout.numVertices = static_cast<uint32_t>(geometry->numVertices);
    layout.vertexBytes = stride * layout.numVertices;
    std::vector<uint8_t> vertices(layout.vertexBytes);
    for (uint32_t v = 0; v < layout.numVertices; ++v) {
        uint8_t* out = vertices.data() + static_cast<size_t>(v) * stride;
        std::memcpy(out, &positions[v], 12);
        if (hasNormals) std::memcpy(out + layout.normalOffset, &normals[v], 12);
        if (hasColors) {
            const RwRGBA& c = geometry->preLitLum[v];
            out[layout.colorOffset + 0] = c.red;
            out[layout.colorOffset + 1] = c.green;
            out[layout.colorOffset + 2] = c.blue;
            out[layout.colorOffset + 3] = c.alpha;
        }
        for (int set = 0; set < uvSets; ++set) std::memcpy(out + layout.uvOffset[set], &geometry->texCoords[set][v], 8);
    }
    if (geometry->skin != nullptr) RpSkinPSGL_InstanceSkinVertices(geometry, &layout, vertices.data());  // 0x774a38
    const RpMeshHeader* header = geometry->mesh;
    const bool strip = (header->flags & 1) != 0;
    const std::vector<dotd::gfx::MeshAttribute> attributes = AttributesOf(layout);
    for (const RpMesh& rpMesh : header->meshes) {
        if (rpMesh.indices == nullptr || rpMesh.numIndices == 0) continue;
        RpDeviceMesh deviceMesh;
        deviceMesh.record = layout;
        RpNativeMesh& m = deviceMesh.record;
        m.primType = strip ? 5u : 4u;
        m.numIndices = rpMesh.numIndices;
        m.indexed = 1;
        m.material = rpMesh.material;
        uint32_t lowest = 0xffffffffu, highest = 0;
        for (uint32_t i = 0; i < rpMesh.numIndices; ++i) {
            lowest = std::min(lowest, rpMesh.indices[i]);
            highest = std::max(highest, rpMesh.indices[i]);
        }
        m.firstIndex = lowest;
        m.lastIndex = highest;
        uint32_t taken = 0;
        if (reuse != nullptr && reuseIndex < reuse->meshes.size()) {
            RpDeviceMesh& old = reuse->meshes[reuseIndex++];
            if (old.gfxMesh != 0 && dotd::gfx::UpdateMesh(old.gfxMesh, vertices.data(), vertices.size(), stride, rpMesh.indices,
                                                          rpMesh.numIndices, attributes.data(),
                                                          static_cast<int>(attributes.size()))) {
                taken = old.gfxMesh;
                old.gfxMesh = 0;  // (not destroyed with the others)
            }
        }
        deviceMesh.gfxMesh = taken != 0 ? taken
                                        : dotd::gfx::CreateMesh(vertices.data(), vertices.size(), stride, rpMesh.indices,
                                                                rpMesh.numIndices, attributes.data(),
                                                                static_cast<int>(attributes.size()));
        device->meshes.push_back(deviceMesh);
    }
    return !device->meshes.empty();
}

}  // namespace

namespace {
// RpAtomicPSGL_InstanceGeometry for a geometry without a device; `reuse`: InstanceGeneric's (a generic geometry only).
bool InstanceGeometry(RpGeometry* geometry, RpGeometryDevice* reuse) {
    RpGeometryDevice* device = new RpGeometryDevice();
    const bool native = (geometry->flags & rpGEOMETRYNATIVE) != 0 && geometry->repEntry != nullptr;
    const bool ok = native ? InstanceNative(geometry, device) : InstanceGeneric(geometry, device, reuse);
    geometry->device = device;  // kept even when empty: nothing to draw, nothing to retry
    return ok;
}
}  // namespace

bool RpAtomicPSGL_InstanceGeometry(RpGeometry* geometry) {
    if (geometry->device != nullptr) return !geometry->device->meshes.empty();
    return InstanceGeometry(geometry, nullptr);
}

// 0x0069d180 RW_RenderAtomicThroughPipeline + 0x006bafc8 DispatchPSGLPipelineMeshes: per mesh, PreparePSGLAtomicMeshShaders
// (the pass state, the shader variant) then DrawPSGLMeshPasses.
bool RpAtomicPSGL_Render(RpAtomic* atomic) {
    RpGeometry* geometry = atomic->geometry;
    if (geometry == nullptr || (geometry->repEntry == nullptr && geometry->mesh == nullptr)) return false;
    if (!dotd::gfx::IsReady()) return false;
    // A skinned atomic keeps the skin plugin's pipeline its stream chose (ShaderManagerPSGL_TryAssignOverride_maybe
    // 0xf8168 leaves it). The generic one (_rpSkinCreatePlatformPipeline_maybe 0x774830 with no render callback) runs
    // DispatchPSGLPipelineMeshes like the shader manager's, with the mesh callbacks InstallPSGLMeshCallbacks gave it; a
    // native geometry needs no instance callback. STUB(C2.9): the MatFX skin pipeline's render callback
    // RwPSGL_DrawMeshList_maybe 0x69b118 (fixed function, no skinning): every skinned atomic of the level files has the
    // right-to-render data 1 (generic). A generic skinned geometry (none in the level files) is instanced with the skin
    // pipeline's instance callback 0x774a38 (InstanceGeneric's skin part, port-final F06).
    if (atomic->skinPipeline == 2) {
        DOTD_STUB_ONCE("RpAtomicPSGL_Render: the MatFX skin pipeline (RwPSGL_DrawMeshList_maybe 0x69b118, C2.9)");
        return true;
    }
    // ExecutePSGLAtomicPipelineNode 0x6b9228 calls the pipeline's reinstance callback only for a generic geometry that
    // already has its resource entry (the first draw instances it; native data has no callback at all).
    const bool reinstance = (geometry->flags & rpGEOMETRYNATIVE) == 0 && geometry->device != nullptr;
    // 0x006b99d0 RwPSGL_AtomicReinstanceCallback_maybe: a geometry locked since its last instance (lockedSinceLastInst)
    // is instanced again, every mesh through the instance callback (RwPSGL_ReinstanceMeshes_maybe 0x6baec0): here the
    // device meshes of a generic geometry are rebuilt from its vertex arrays (a native geometry's buffers are the file's);
    // then the lock flags are cleared. A geometry with more than one morph target keeps the interpolator's dirty bit (+0x4c
    // bit 0) only while it has one.
    if (geometry->lockedSinceLastInst != 0) {
        const bool native = (geometry->flags & rpGEOMETRYNATIVE) != 0 && geometry->repEntry != nullptr;
        bool instanced;
        if (geometry->device != nullptr && !native) {
            // perf: the old device meshes' GL objects are handed to the new instance (InstanceGeneric's `reuse`), which
            // fills them again or destroys them; before, every mesh was destroyed here and created again.
            RpGeometryDevice* old = geometry->device;
            geometry->device = nullptr;
            instanced = InstanceGeometry(geometry, old);
            delete old;
        } else {
            instanced = RpAtomicPSGL_InstanceGeometry(geometry);
        }
        if (!instanced) {
            geometry->lockedSinceLastInst = 0;
            return true;
        }
        geometry->lockedSinceLastInst = 0;
    }
    if (geometry->numMorphTargets != 1 && (atomic->flags & 1u) != 0) atomic->flags &= 0xfffffffeu;
    // The skin pipeline's reinstance callback 0x7758c0 wraps the one above (_rpSkinCreatePlatformPipeline_maybe
    // 0x774830 keeps it at the plugin globals +0x44): its skin part follows (port-final F06).
    if (reinstance && atomic->skinPipeline == rpSKINTYPEGENERIC) RpSkinPSGL_AtomicReinstanceCallback(atomic);
    if (!RpAtomicPSGL_InstanceGeometry(geometry)) return true;
    ShaderMatrixCache_BeginCamera();
    for (RpDeviceMesh& mesh : geometry->device->meshes) {
        if (mesh.gfxMesh == 0 || mesh.record.material == nullptr) continue;
        PreparePSGLAtomicMeshShaders(&mesh, atomic);                 // vt: private +0x14
        DrawPSGLMeshPasses(&mesh, mesh.record.format);               // vt: private +0x1c
    }
    return true;
}
