// RpGeometry.cpp - the RpWorld geometry/material/atomic calls the Rt2d shapes make. See RpGeometry.h.
#include "Renderware/rpworld/RpGeometry.h"

#include <cstring>

#include "Renderware/rpprtstd/RpPrtStd.h"
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

// RwTextureDestroy 0x7548c0 as RpMaterial calls it (when it has a texture).
void TextureRelease(RwTexture* texture) {
    if (texture != nullptr) RwTextureDestroy(texture);
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

RpAtomicCallBackRender RpAtomicGetDefaultRenderCallBack() { return AtomicDefaultRenderCallBack; }

// 0x006a1388 RpGeometryCreate. The PS3 allocates the geometry and its arrays as one block (plugin data,
// then the prelight colours, the texture coordinate sets and the triangles); here each array is its own
// block with the same contents. The plugin registry (_rwPluginRegistryInitObject 0x75dbe0) runs the geometry plugins'
// constructors in their registration order: the bin mesh (0x50e) and the native data (0x510, both registered by
// _rpWorldRegisterObjectPlugins_maybe 0x6b38d0 without data or constructor), then the skin (0x116, 4 bytes,
// RpSkinPluginAttach_maybe 0x773620: RpSkinGeometryConstructor).
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
    RpSkinGeometryConstructor(geometry);  // _rwPluginRegistryInitObject
    return geometry;
}

// 0x006a1eb0 RW_CreateEmptyGeometryWithRadius_maybe (RpGeometryCreateSpace). A failed unlock drops the reference
// (RpGeometryDestroy inlined: with other references only the count; else the resource entry and the geometry).
RpGeometry* RpGeometryCreateSpace(RwReal radius) {
    RpGeometry* geometry = RpGeometryCreate(0, 0, 0);
    if (geometry == nullptr) return nullptr;
    RpMorphTarget* target = geometry->morphTarget;
    target->boundingSphere.radius = radius;
    target->boundingSphere.center.z = 0.0f;
    target->boundingSphere.center.x = 0.0f;
    target->boundingSphere.center.y = 0.0f;
    if (RpGeometryUnlock(geometry) == nullptr) {
        RpGeometryDestroy(geometry);
        return nullptr;
    }
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

// 0x006a0e28 RpGeometryLock (_rpMeshDestroy 0x6a5fc8 is the bin mesh's delete here)
RpGeometry* RpGeometryLock(RpGeometry* geometry, RwInt32 lockMode) {
    if ((lockMode & 1) == 0) {
        geometry->lockedSinceLastInst = static_cast<RwUInt16>(geometry->lockedSinceLastInst | 0xffe);
        return geometry;
    }
    geometry->lockedSinceLastInst = static_cast<RwUInt16>(geometry->lockedSinceLastInst | 0xfff);
    if (geometry->mesh != nullptr) {
        delete geometry->mesh;
        geometry->mesh = nullptr;
    }
    return geometry;
}

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

// 0x0069cb58 RpAtomicCreate (Ghidra RW_CreateAtomic; RW 3.7 baclump.c): from the atomic free list (RwFreeListAlloc
// through the engine's +0x118); the object header (type 1 rpATOMIC, sub type 0, flags 5 = rpATOMICCOLLISIONTEST |
// rpATOMICRENDER, private flags 1), the frame sync callback (+0x10 RpAtomicUpdateBoundingSphereIfDirty_maybe) and no
// frame (RwObjectHasFrameSetFrame(atomic, null)); the private world-bound-dirty bit set again; the interpolator: time
// and recipTime 1.0f (TOC -0x466c), position 0, flags 3 (dirty instance and sphere: the first sphere read resyncs it),
// morph targets 0 / 0; the default render callback (+0x48), no pipeline (+0x6c), no geometry, zero spheres, the empty
// world-sector tie list (+0x64); then the plugins' constructors (_rwPluginRegistryInitObject 0x75dbe0: the K engine's,
// skin, RpPrtStd and PTank extensions, which only zero their data; the remake's fields start zeroed: value-initialised).
RpAtomic* RpAtomicCreate() {
    RpAtomic* atomic = new RpAtomic();
    atomic->privateFlags = 1;
    atomic->objectFlags = 5;
    atomic->frame = nullptr;  // RwObjectHasFrameSetFrame(atomic, null)
    atomic->privateFlags |= 1;
    atomic->interpRecipTime = 1.0f;
    atomic->interpTime = 1.0f;
    atomic->renderCallBack = AtomicDefaultRenderCallBack;
    atomic->interpPosition = 0.0f;
    atomic->flags = 3;
    atomic->pipeline = nullptr;
    atomic->geometry = nullptr;
    for (int i = 0; i < 4; ++i) {
        atomic->worldSphere[i] = 0.0f;
        atomic->boundingSphere[i] = 0.0f;
    }
    atomic->startMorphTarget = 0;
    atomic->endMorphTarget = 0;
    atomic->llWorldSectorsInAtomic.next = &atomic->llWorldSectorsInAtomic;  // rwLinkListInitialize (+0x64)
    atomic->llWorldSectorsInAtomic.prev = &atomic->llWorldSectorsInAtomic;
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

// 0x0069bbe0 _rpAtomicResyncInterpolatedSphere. The single key frame is the start one when both are equal and
// in range, else key frame 0; two key frames in range are interpolated by recipTime * position: the radius with
// one fused multiply-add, the centre by separate multiply and add. The private flag is RpAtomic::privateFlags
// bit 0 here (as GetGeometryWorldBoundingSphere clears it).
void _rpAtomicResyncInterpolatedSphere(RpAtomic* atomic) {
    const RpGeometry* geometry = atomic->geometry;
    if (geometry == nullptr) return;
    const int32_t start = atomic->startMorphTarget;
    const int32_t end = atomic->endMorphTarget;
    const RpMorphTarget* single = &geometry->morphTarget[0];
    if (start == end) {
        if (end < geometry->numMorphTargets) single = &geometry->morphTarget[end];
    } else if (start < geometry->numMorphTargets && end < geometry->numMorphTargets) {
        const RpMorphTarget* from = &geometry->morphTarget[start];
        const RpMorphTarget* to = &geometry->morphTarget[end];
        const float scale = atomic->interpRecipTime * atomic->interpPosition;
        const float dx = scale * (to->boundingSphere.center.x - from->boundingSphere.center.x);
        const float dy = scale * (to->boundingSphere.center.y - from->boundingSphere.center.y);
        const float dz = scale * (to->boundingSphere.center.z - from->boundingSphere.center.z);
        atomic->boundingSphere[0] = dx;
        atomic->boundingSphere[1] = dy;
        atomic->boundingSphere[2] = dz;
        atomic->boundingSphere[3] =
            ppc::fmadds(scale, to->boundingSphere.radius - from->boundingSphere.radius, from->boundingSphere.radius);
        atomic->boundingSphere[0] = dx + from->boundingSphere.center.x;
        atomic->boundingSphere[2] = dz + from->boundingSphere.center.z;
        atomic->boundingSphere[1] = dy + from->boundingSphere.center.y;
        atomic->flags &= 0xfffffffdu;
        atomic->privateFlags |= 1;
        return;
    }
    atomic->boundingSphere[0] = single->boundingSphere.center.x;
    atomic->boundingSphere[1] = single->boundingSphere.center.y;
    atomic->boundingSphere[2] = single->boundingSphere.center.z;
    atomic->boundingSphere[3] = single->boundingSphere.radius;
    atomic->flags &= 0xfffffffdu;
    atomic->privateFlags |= 1;
}

// 0x0069dd20 RpAtomicGetWorldBoundingSphere (RW 3.7 baclump.c; the PSGL lighting callback's local lights, never reached:
// RpPSGLLighting.cpp): a dirty interpolated sphere (flag 2) resynced first (_rpAtomicResyncInterpolatedSphere inlined,
// with a geometry); with the frame's hierarchy dirty (RwFrameDirty 0x74a428: the root's private flags & 3) or the world
// bound dirty (private flag 1): the centre through the frame's LTM, the radius as it is for an orthonormal LTM (flags & 3
// == 3), else times the square root of the largest squared axis length (the compares as fcmpu / cror), the private flag
// cleared. Returns the world sphere.
const float* RpAtomicGetWorldBoundingSphere(RpAtomic* atomic) {
    RwFrame* frame = atomic->frame;
    if ((atomic->flags & 2u) != 0 && atomic->geometry != nullptr) _rpAtomicResyncInterpolatedSphere(atomic);
    if ((frame->root->object.privateFlags & 3) == 0 && (atomic->privateFlags & 1) == 0) return atomic->worldSphere;
    const RwMatrix* ltm = RwFrameGetLTM(frame);  // 0x0074a6f0
    RwV3dTransformPoint(reinterpret_cast<RwV3d*>(atomic->worldSphere), reinterpret_cast<const RwV3d*>(atomic->boundingSphere),
                        ltm);  // 0x0075e7f0
    if ((ltm->flags & 3u) == 3u) {
        atomic->worldSphere[3] = atomic->boundingSphere[3];
    } else {
        const float right = ppc::fmadds(ltm->right.z, ltm->right.z, ppc::fmadds(ltm->right.x, ltm->right.x, ltm->right.y * ltm->right.y));
        const float up = ppc::fmadds(ltm->up.z, ltm->up.z, ppc::fmadds(ltm->up.x, ltm->up.x, ltm->up.y * ltm->up.y));
        const float at = ppc::fmadds(ltm->at.z, ltm->at.z, ppc::fmadds(ltm->at.x, ltm->at.x, ltm->at.y * ltm->at.y));
        const float larger = up >= at ? up : at;
        const float scale = larger <= right ? right : (up >= at ? up : at);
        atomic->worldSphere[3] = rwSqrt(scale) * atomic->boundingSphere[3];  // 0x0075e738
    }
    atomic->privateFlags &= 0xfe;
    return atomic->worldSphere;
}

// 0x0069ecb0 RpAtomicDestroy
RwBool RpAtomicDestroy(RpAtomic* atomic) {
    // rwPluginRegistryDeInitObject: the RpPrtStd plugin's destructor (0x730158; the other plugins' are not
    // ported here).
    RpPrtStdAtomicDestruct(atomic);
    if (atomic->geometry != nullptr) {
        RpGeometryDestroy(atomic->geometry);
        atomic->geometry = nullptr;
    }
    delete atomic;
    return 1;
}

const std::vector<RpAtomicDraw>& RpAtomicFrameDraws() { return g_atomicDraws; }
void RpAtomicBeginFrame() { g_atomicDraws.clear(); }
