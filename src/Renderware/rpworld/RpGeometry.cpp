// RpGeometry.cpp - the RpWorld geometry/material/atomic calls the Rt2d shapes make. See RpGeometry.h.
#include "Renderware/rpworld/RpGeometry.h"

#include <cstring>

#include "Renderware/rpskin/RpSkin.h"
#include "Renderware/rpworld/RpAtomicPSGL.h"
#include "Renderware/rwcore/RwCamera.h"
#include "Renderware/rwcore/RwDevice.h"
#include "Renderware/rwcore/RwIm3D.h"
#include "Renderware/rwcore/RwMatrix.h"
#include "Renderware/rwcore/RwSList.h"
#include "Renderware/rwcore/RwTexture.h"
#include "crt/ppc_ops.h"
#include "platform/gfx/mesh.h"

namespace {

std::vector<RpAtomicDraw> g_atomicDraws;

// RwTextureDestroy as RpMaterial uses it (RW 3.7: the texture's reference count). STUB(C1.4): the
// textures belong to the shim's dictionaries, which free them; only the count is kept.
void TextureRelease(RwTexture* texture) {
    if (texture != nullptr) --texture->refCount;
}

// 0x0069d180 RW_RenderAtomicThroughPipeline (RW's AtomicDefaultRenderCallBack, the default +0x48 set by
// RpAtomicCreate): the atomic through the default PSGL atomic pipeline. Here the draw goes to the device
// layer (RwDevice_DrawAtomic: per material, prelight x material colour, the frame's LTM) and is recorded.
RpAtomic* AtomicDefaultRenderCallBack(RpAtomic* atomic) {
    // A streamed geometry (bin mesh or native data) goes through the PSGL atomic pipeline and the uber-shader
    // (RpAtomicPSGL.cpp); the Rt2d shapes' in-memory geometries keep the immediate path below.
    if (RpAtomicPSGL_Render(atomic)) return atomic;
    RpAtomicDraw draw;
    draw.atomic = atomic;
    draw.geometry = atomic->geometry;
    if (atomic->frame != nullptr) {
        draw.ltm = *RwFrameGetLTM(atomic->frame);
    } else {
        RwMatrixSetIdentity(&draw.ltm);
    }
    if (atomic->geometry != nullptr) {
        const RpMaterialList& list = atomic->geometry->matList;
        for (RwInt32 i = 0; i < list.numMaterials; ++i) draw.materialColors.push_back(list.materials[i]->color);
    }
    draw.states = RwIm3DCurrentStates();
    RwDevice_DrawAtomic(draw);
    g_atomicDraws.push_back(draw);
    return atomic;
}

}  // namespace

// 0x006a1388 RpGeometryCreate. The PS3 allocates the geometry and its arrays as one block (plugin data,
// then the prelight colours, the texture coordinate sets and the triangles); here each array is its own
// block with the same contents. STUB(C1.4): the plugin registry.
RpGeometry* RpGeometryCreate(RwInt32 numVerts, RwInt32 numTriangles, RwUInt32 format) {
    if (static_cast<RwUInt32>(numVerts) > 0xffff || numTriangles < 0) return nullptr;  // _rwerror(6)
    RwUInt32 numTexCoordSets;
    RwUInt32 texFlag;
    if ((format & 0xff0000) == 0) {
        if ((format & rpGEOMETRYTEXTURED2) != 0) {
            numTexCoordSets = 2;
        } else {
            numTexCoordSets = (format >> 2) & 1;
        }
    } else {
        numTexCoordSets = (format & 0xff0000) >> 16;
    }
    if (numTexCoordSets == 1) {
        texFlag = rpGEOMETRYTEXTURED;
    } else if (numTexCoordSets < 2) {
        texFlag = 0;
    } else {
        texFlag = rpGEOMETRYTEXTURED2;
    }
    RpGeometry* geometry = static_cast<RpGeometry*>(RwMalloc(sizeof(RpGeometry), 0x23000f));
    if (geometry == nullptr) return nullptr;
    std::memset(geometry, 0, sizeof(RpGeometry));
    geometry->objectType = 8;
    geometry->refCount = 1;
    geometry->numTexCoordSets = static_cast<RwInt32>(numTexCoordSets);
    geometry->flags = (format & 0xf000000) | texFlag | (format & 0x7b);
    geometry->numTriangles = numTriangles;
    geometry->numVertices = numVerts;
    if ((format & 0x1000000) == 0) {  // not rpGEOMETRYNATIVE
        if ((format & rpGEOMETRYPRELIT) != 0 && numVerts != 0) {
            geometry->preLitLum = static_cast<RwRGBA*>(RwMalloc(numVerts * sizeof(RwRGBA), 0x23000f));
        }
        if (numTexCoordSets != 0 && numVerts != 0) {
            for (RwUInt32 i = 0; i < numTexCoordSets; ++i) {
                geometry->texCoords[i] = static_cast<RwTexCoords*>(RwMalloc(numVerts * sizeof(RwTexCoords), 0x23000f));
            }
        }
        if (numTriangles != 0) {
            geometry->triangles = static_cast<RpTriangle*>(RwMalloc(numTriangles * sizeof(RpTriangle), 0x23000f));
            for (RwInt32 i = 0; i < numTriangles; ++i) geometry->triangles[i].matIndex = 0xffff;
        }
    }
    // RpGeometryAddMorphTargets(geometry, 1)
    RpMorphTarget* target = static_cast<RpMorphTarget*>(RwMalloc(sizeof(RpMorphTarget), 0x23000f));
    std::memset(target, 0, sizeof(RpMorphTarget));
    target->parentGeom = geometry;
    if (numVerts != 0) {
        target->verts = static_cast<RwV3d*>(RwMalloc(numVerts * sizeof(RwV3d), 0x23000f));
        if ((format & rpGEOMETRYNORMALS) != 0) {
            target->normals = static_cast<RwV3d*>(RwMalloc(numVerts * sizeof(RwV3d), 0x23000f));
        }
    }
    geometry->morphTarget = target;
    geometry->numMorphTargets = 1;
    return geometry;
}

// RpGeometryAddMorphTargets (RW 3.7 bageomet.c): the morph target array grown by `mtsToAdd`; the new targets
// get vertices and, when the geometry has normals, normals. The bounding spheres are zero until set.
RwInt32 RpGeometryAddMorphTargets(RpGeometry* geometry, RwInt32 mtsToAdd) {
    if (mtsToAdd <= 0) return geometry->numMorphTargets;
    const RwInt32 first = geometry->numMorphTargets;
    const RwInt32 total = first + mtsToAdd;
    RpMorphTarget* targets = static_cast<RpMorphTarget*>(RwMalloc(static_cast<RwUInt32>(total) * sizeof(RpMorphTarget), 0x23000f));
    if (first != 0) std::memcpy(targets, geometry->morphTarget, static_cast<size_t>(first) * sizeof(RpMorphTarget));
    std::memset(targets + first, 0, static_cast<size_t>(mtsToAdd) * sizeof(RpMorphTarget));
    for (RwInt32 i = 0; i < total; ++i) targets[i].parentGeom = geometry;
    for (RwInt32 i = first; i < total; ++i) {
        if (geometry->numVertices != 0) {
            targets[i].verts = static_cast<RwV3d*>(RwMalloc(static_cast<RwUInt32>(geometry->numVertices) * sizeof(RwV3d), 0x23000f));
            if ((geometry->flags & rpGEOMETRYNORMALS) != 0) {
                targets[i].normals = static_cast<RwV3d*>(RwMalloc(static_cast<RwUInt32>(geometry->numVertices) * sizeof(RwV3d), 0x23000f));
            }
        }
    }
    RwFree(geometry->morphTarget);
    geometry->morphTarget = targets;
    geometry->numMorphTargets = total;
    return first;
}

// 0x006a1830 RpGeometryDestroy (the last reference frees the geometry, its materials and arrays).
RwBool RpGeometryDestroy(RpGeometry* geometry) {
    if (geometry->refCount > 1) {
        --geometry->refCount;
        return 1;
    }
    --geometry->refCount;
    for (RwInt32 i = 0; i < geometry->matList.numMaterials; ++i) RpMaterialDestroy(geometry->matList.materials[i]);
    RwFree(geometry->matList.materials);
    RwFree(geometry->preLitLum);
    for (RwTexCoords* set : geometry->texCoords) RwFree(set);
    RwFree(geometry->triangles);
    for (RwInt32 i = 0; i < geometry->numMorphTargets; ++i) {
        RwFree(geometry->morphTarget[i].verts);
        RwFree(geometry->morphTarget[i].normals);
    }
    RwFree(geometry->morphTarget);
    delete geometry->mesh;       // the bin mesh (RwFree'd by the PS3's _rpMeshHeaderDestroy)
    delete geometry->repEntry;   // the native data (RwResourcesFreeResEntry + RwPSGL_DeleteMeshBuffers_maybe)
    if (geometry->device != nullptr) {  // the device meshes (RwPSGL_DeleteMeshBuffers_maybe)
        for (RpDeviceMesh& mesh : geometry->device->meshes) dotd::gfx::DestroyMesh(mesh.gfxMesh);
        delete geometry->device;
    }
    RpSkinGeometryDestructor(geometry);  // 0x00773d38, the skin plugin's geometry destructor
    RwFree(geometry);
    return 1;
}

// 0x006a0a28 RpGeometryUnlock. STUB(C1.4): the mesh (RpMeshes by material, tristripped) the pipeline
// renders; nothing reads it before then.
RpGeometry* RpGeometryUnlock(RpGeometry* geometry) { return geometry; }

// 0x006a0230 RpGeometryTriangleSetVertexIndices
RpGeometry* RpGeometryTriangleSetVertexIndices(const RpGeometry* geometry, RpTriangle* triangle, RwUInt16 vert1,
                                               RwUInt16 vert2, RwUInt16 vert3) {
    triangle->vertIndex[2] = vert3;
    triangle->vertIndex[0] = vert1;
    triangle->vertIndex[1] = vert2;
    return const_cast<RpGeometry*>(geometry);
}

// 0x006a0ec0 RpGeometryTriangleSetMaterial: the material's index in the geometry's list, appended when
// new; a null material sets 0xffff. A failed append returns null (the index is not written).
RpGeometry* RpGeometryTriangleSetMaterial(RpGeometry* geometry, RpTriangle* triangle, RpMaterial* material) {
    RwInt32 index = -1;
    if (material != nullptr) {
        index = _rpMaterialListFindMaterialIndex(&geometry->matList, material);
        if (index < 0) {
            index = _rpMaterialListAppendMaterial(&geometry->matList, material);
            if (index < 0) return nullptr;
        }
    }
    triangle->matIndex = static_cast<RwUInt16>(index);
    return geometry;
}

// 0x00744b10 RwBBoxCalculate. BUG(original): numVerts 0 loops (numVerts - 2) + 1 times over memory past
// the array (the caller never passes 0 here).
RwBBox* RwBBoxCalculate(RwBBox* box, const RwV3d* verts, RwInt32 numVerts) {
    box->inf = verts[0];
    box->sup = verts[0];
    for (RwInt32 i = 1; i < numVerts; ++i) {
        const RwV3d& v = verts[i];
        if (v.x < box->inf.x) box->inf.x = v.x;
        if (v.y < box->inf.y) box->inf.y = v.y;
        if (v.z < box->inf.z) box->inf.z = v.z;
        if (box->sup.x < v.x) box->sup.x = v.x;
        if (box->sup.y < v.y) box->sup.y = v.y;
        if (box->sup.z < v.z) box->sup.z = v.z;
    }
    return box;
}

// 0x006a1248 RpMorphTargetCalcBoundingSphere: the box centre, the farthest vertex (squared, fmadds),
// RW_Sqrt when positive, then x 1.001 (0x3f8020c5).
RpMorphTarget* RpMorphTargetCalcBoundingSphere(const RpMorphTarget* morphTarget, RwSphere* sphere) {
    const RwInt32 numVerts = morphTarget->parentGeom->numVertices;
    RwBBox box;
    RwBBoxCalculate(&box, morphTarget->verts, numVerts);
    const float cx = (box.inf.x + box.sup.x) * 0.5f;
    const float cy = (box.inf.y + box.sup.y) * 0.5f;
    const float cz = (box.inf.z + box.sup.z) * 0.5f;
    float radius = 0.0f;
    if (numVerts != 0) {
        for (RwInt32 i = 0; i < numVerts; ++i) {
            const RwV3d& v = morphTarget->verts[i];
            const float dy = v.y - cy;
            const float dx = v.x - cx;
            const float dz = v.z - cz;
            const float d = ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy));
            if (d > radius) radius = d;
        }
        if (radius > 0.0f) radius = rwSqrt(radius);
        radius = radius * 1.00100005f;  // 0x3f8020c5
    }
    sphere->center.x = cx;
    sphere->radius = radius;
    sphere->center.z = cz;
    sphere->center.y = cy;
    return const_cast<RpMorphTarget*>(morphTarget);
}

// 0x006a3908 RpMaterialCreate: white, no texture, surface properties (1, 1, 1), one reference.
RpMaterial* RpMaterialCreate() {
    RpMaterial* material = static_cast<RpMaterial*>(RwMalloc(sizeof(RpMaterial), 0x30007));
    if (material == nullptr) return nullptr;
    std::memset(material, 0, sizeof(RpMaterial));
    material->refCount = 1;
    material->color = RwRGBA{0xff, 0xff, 0xff, 0xff};
    material->pipeline = nullptr;
    material->texture = nullptr;
    material->surfaceProps = RwSurfaceProperties{1.0f, 1.0f, 1.0f};
    return material;
}

// 0x006a3ca0 RpMaterialDestroy
RwBool RpMaterialDestroy(RpMaterial* material) {
    if (material->refCount != 1) {
        --material->refCount;
        return 1;
    }
    TextureRelease(material->texture);
    material->texture = nullptr;
    RwFree(material);
    return 1;
}

// 0x006a3890 RpMaterialSetTexture
RpMaterial* RpMaterialSetTexture(RpMaterial* material, RwTexture* texture) {
    if (texture != nullptr) ++texture->refCount;
    TextureRelease(material->texture);
    material->texture = texture;
    return material;
}

// 0x006a45a0 _rpMaterialListFindMaterialIndex: searches from the end; -1 when absent.
RwInt32 _rpMaterialListFindMaterialIndex(const RpMaterialList* matList, const RpMaterial* material) {
    RwInt32 index = matList->numMaterials;
    while (--index >= 0) {
        if (matList->materials[index] == material) return index;
    }
    return index;
}

// 0x006a4a60 _rpMaterialListAppendMaterial: grows by 20 entries; the list takes a reference.
RwInt32 _rpMaterialListAppendMaterial(RpMaterialList* matList, RpMaterial* material) {
    if (matList->numMaterials >= matList->space) {
        const RwUInt32 size = static_cast<RwUInt32>(matList->space + 20) * sizeof(RpMaterial*);
        RpMaterial** materials = static_cast<RpMaterial**>(
            matList->materials == nullptr ? RwMalloc(size, 0x1030008) : RwRealloc(matList->materials, size, 0x1030008));
        if (materials == nullptr) return -1;  // _rwerror(0x80000013)
        matList->materials = materials;
        matList->space += 20;
    }
    matList->materials[matList->numMaterials] = material;
    ++material->refCount;
    return matList->numMaterials++;
}

// 0x0069cb58 RpAtomicCreate (Ghidra RW_CreateAtomic). STUB(C1.4): the pipeline, bounding-sphere sync and
// the plugin data; the render callback records the draw.
RpAtomic* RpAtomicCreate() {
    RpAtomic* atomic = new RpAtomic();
    atomic->renderCallBack = AtomicDefaultRenderCallBack;
    return atomic;
}

// 0x0069c270 RpAtomicSetFrame
RpAtomic* RpAtomicSetFrame(RpAtomic* atomic, RwFrame* frame) {
    atomic->frame = frame;
    return atomic;
}

// 0x0069ccb8 RpAtomicSetGeometry: the atomic takes a reference; without flag 1 its bounding sphere is the
// geometry's morph target's.
RpAtomic* RpAtomicSetGeometry(RpAtomic* atomic, RpGeometry* geometry, RwUInt32 flags) {
    if (atomic->geometry == geometry) return atomic;
    if (geometry != nullptr) ++geometry->refCount;  // RpGeometryAddRef
    if (atomic->geometry != nullptr) RpGeometryDestroy(atomic->geometry);
    atomic->geometry = geometry;
    if ((flags & 1) == 0 && geometry != nullptr) {
        const RwSphere& sphere = geometry->morphTarget->boundingSphere;
        atomic->boundingSphere[0] = sphere.center.x;
        atomic->boundingSphere[1] = sphere.center.y;
        atomic->boundingSphere[2] = sphere.center.z;
        atomic->boundingSphere[3] = sphere.radius;
    }
    return atomic;
}

// 0x0069ecb0 RpAtomicDestroy
RwBool RpAtomicDestroy(RpAtomic* atomic) {
    if (atomic->geometry != nullptr) {
        RpGeometryDestroy(atomic->geometry);
        atomic->geometry = nullptr;
    }
    delete atomic;
    return 1;
}

const std::vector<RpAtomicDraw>& RpAtomicFrameDraws() { return g_atomicDraws; }
void RpAtomicBeginFrame() { g_atomicDraws.clear(); }
