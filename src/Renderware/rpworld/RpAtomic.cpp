// RpAtomic.cpp - the atomic clone and the PTank atomics (see RpAtomic.h).
#include "Renderware/rpworld/RpAtomic.h"

#include <cstring>

#include "Renderware/rpprtstd/RpPrtStd.h"
#include "Renderware/rpworld/RpGeometry.h"
#include "Renderware/rwcore/RwIm3D.h"
#include "Renderware/rwcore/RwStream.h"

namespace {
// rpPTANKDFLAG bit -> PS3 stride of its per-particle array.
constexpr uint32_t kStrides[9] = {16, 4, 8, 64, 12, 4, 16, 16, 32};

RpAtomic* NewAtomic() {
    RpAtomic* atomic = new RpAtomic();
    std::memset(atomic, 0, sizeof(RpAtomic));
    atomic->llWorldSectorsInAtomic.next = &atomic->llWorldSectorsInAtomic;  // the empty tie list (RpAtomicCreate's)
    atomic->llWorldSectorsInAtomic.prev = &atomic->llWorldSectorsInAtomic;
    return atomic;
}

// 0x0077b500 RpPTank_CreateEmptyQuadGeometry_maybe (the PTank's create callback, args atomic, PTank + 0x50, count,
// data flags): an empty geometry (RW_CreateEmptyGeometryWithRadius_maybe 0x6a1eb0 = RpGeometryCreateSpace(1.0f))
// with the flags 0x06 (positions, textured) or, with per-particle normals (0x10), 0x76 (+ normals, light, modulate
// material colour), | 8 (prelit) with any colour data (0x40042); one material (ambient 0.3f TOC -0x2f48, specular and
// diffuse 1.0f) appended through RpGeometryTriangleSetMaterial on a stack triangle; the atomic takes the geometry
// (RpAtomicSetGeometry flags 0: its sphere (0, 0, 0, 1)) and the references are dropped; the constant colour
// (PTank +0xcc) opaque black; then the format hook (0xcfbbc4 -> the game's 0x8b918 PTank_SetupInstanceFormat_maybe:
// the instancer indices, computed at the draw here, RpPTankRender.cpp) and the setup / unlock callbacks (+0x24 =
// 0x77b6b8, +0x38 = 0). 1 on success, 0 when the geometry or the material cannot be made.
int32_t CreateEmptyQuadGeometry(RpAtomic* atomic, RpPTankData* data, uint32_t dataFlags) {
    uint32_t format = (dataFlags & 0x10) != 0 ? 0x76u : 0x06u;  // ((flag - 1) >> 31 & -0x70) + 0x76
    if ((dataFlags & 0x40042) != 0) format |= 8;
    RpGeometry* geometry = RpGeometryCreateSpace(1.0f);  // TOC -0x2f4c
    if (geometry == nullptr) return 0;
    geometry->flags = format;
    RpMaterial* material = RpMaterialCreate();
    if (material == nullptr) {
        RpGeometryDestroy(geometry);
        return 0;
    }
    material->surfaceProps.ambient = 0.300000012f;  // 0x3e99999a
    material->surfaceProps.diffuse = 1.0f;
    material->surfaceProps.specular = 1.0f;
    RpTriangle triangle;  // sp+0x70, only its material index is written
    RpGeometryTriangleSetMaterial(geometry, &triangle, material);
    RpAtomicSetGeometry(atomic, geometry, 0);
    RpGeometryDestroy(geometry);
    RpMaterialDestroy(material);
    data->colorCC[2] = 0;
    data->colorCC[0] = 0;
    data->colorCC[1] = 0;
    data->colorCC[3] = 0xff;
    return 1;
}
}  // namespace

RpAtomic* RpAtomicClone(RpAtomic* atomic) {
    if (atomic == nullptr) return nullptr;
    RpAtomic* clone = NewAtomic();
    *clone = *atomic;
    clone->clonedFrom = atomic;
    if (clone->geometry != nullptr) ++clone->geometry->refCount;  // RpAtomicClone: RpAtomicSetGeometry takes a reference
    // The plugins' copy callbacks: RpPrtStd's clones the emitters (0x730298).
    RpPrtStdAtomicCopy(clone, atomic);
    return clone;
}

// 0x0077ab00 RpPTankAtomicCreate: the flags normalised: with a per-particle matrix (0x8) the per-particle
// position, size and 2D rotation flags go; without a matrix or a position a position is added; without a
// storage flag (0x30000000) separate arrays (0x10000000). BUG(original): where a per-particle array and its
// constant twin are both asked for (0x8 / 0x8000, 0x20 / 0x20000, 0x40 / 0x40000, 0x80 / 0x80000,
// 0x100 / 0x100000) the flags are ANDed with the constant's bit (rlwinm with one bit), leaving only it.
// Then 0x00779ee0 RpPTankAtomicCreateCustom_maybe with the default (separate) storage: one array of
// maxParticles + 4 entries per flag, the constants defaulted (size 1x1, black opaque colour, white vertex
// colours' alpha, tex coords (0,0)-(0,1)-(1,1)-(1,0) as the PS3 words, an identity matrix), the blend
// states read from the device, the atomic's render callback the PTank's (the default one kept).
RpAtomic* RpPTankAtomicCreate(uint32_t maxParticles, uint32_t dataFlags, uint32_t platFlags) {
    uint32_t flags = dataFlags;
    const bool matrix = ((dataFlags >> 3) & 1) == 1;
    const bool rotate = ((dataFlags >> 5) & 1) == 1;
    if (matrix && (dataFlags & 0x8000) != 0) flags = dataFlags & 0x8000;
    if (rotate && (dataFlags & 0x20000) != 0) flags = flags & 0x20000;
    if ((dataFlags & 0x40) != 0 && (dataFlags & 0x40000) != 0) flags = flags & 0x40000;
    if ((dataFlags & 0x80) != 0 && (dataFlags & 0x80000) != 0) flags = flags & 0x80000;
    if ((dataFlags & 0x100) != 0 && (dataFlags & 0x100000) != 0) flags = flags & 0x100000;
    if (matrix) {
        if ((dataFlags & 1) == 1) flags &= 0xfffffffeu;
        if ((dataFlags & 4) != 0) flags &= 0xfffffffbu;
        if (rotate) flags &= 0xffffffdfu;
    }
    if ((dataFlags & 1) == 0 && !matrix) flags |= 1;
    if ((flags & 0x30000000) == 0) flags |= 0x10000000;
    (void)platFlags;

    RpAtomic* atomic = RpAtomicCreate();  // RW_CreateAtomic
    if (atomic == nullptr) return nullptr;
    RpPTankData* data = new RpPTankData();
    data->defaultRenderCallBack = atomic->renderCallBack;  // +0x10 = atomic +0x48
    atomic->renderCallBack = RpPTankAtomicRender;
    atomic->ptank = data;
    data->maxParticles = maxParticles;
    data->numPrt = 0;
    data->lockFlags = 0;
    data->flags40 = 0xffffffffu;
    data->dataFlags = flags;
    data->strideOverride = 0;
    data->numProp = 0;
    for (int bit = 0; bit < 9; ++bit) {
        data->data[bit] = nullptr;
        data->stride[bit] = 0;
        if ((flags & (1u << bit)) == 0) continue;
        ++data->numProp;
        std::vector<uint8_t>& storage = data->storage[bit];
        storage.assign((maxParticles + 4) * kStrides[bit] + 16, 0);
        const uintptr_t base = reinterpret_cast<uintptr_t>(storage.data());
        data->data[bit] = storage.data() + ((16 - (base & 15)) & 15);
        data->stride[bit] = static_cast<int32_t>(kStrides[bit]);
    }
    // The create callback (+4 of the callback block): 0x0077b500 RpPTank_CreateEmptyQuadGeometry_maybe.
    if (CreateEmptyQuadGeometry(atomic, data, flags) != 1) {
        RpAtomicDestroy(atomic);
        return nullptr;
    }
    RpMaterialSetTexture(atomic->geometry->matList.materials[0], nullptr);
    const float one = 1.0f;
    std::memcpy(&data->renderC0[0], &one, 4);
    std::memcpy(&data->renderC0[1], &one, 4);
    data->renderC8 = 0;
    data->colorCC[0] = 0;
    data->colorCC[1] = 0;
    data->colorCC[2] = 0;
    data->colorCC[3] = 0xff;
    for (int i = 0; i < 4; ++i) {
        data->vtxColorD0[i * 4 + 0] = 0;
        data->vtxColorD0[i * 4 + 1] = 0;
        data->vtxColorD0[i * 4 + 2] = 0;
        data->vtxColorD0[i * 4 + 3] = 0xff;
    }
    const float tex[8] = {0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f};
    std::memcpy(data->texCoordsE0, tex, sizeof tex);
    std::memset(data->matrix100, 0, sizeof data->matrix100);
    std::memcpy(&data->matrix100[0], &one, 4);
    std::memcpy(&data->matrix100[5], &one, 4);
    std::memcpy(&data->matrix100[10], &one, 4);
    data->matrix100[3] |= 0x20003u;
    data->wordB8 = 0;
    data->wordBC = 0;
    RwRenderStateGet(static_cast<RwRenderState>(10), &data->renderAC);
    RwRenderStateGet(static_cast<RwRenderState>(11), &data->renderB0);
    RwRenderStateGet(static_cast<RwRenderState>(12), &data->renderB4);
    return atomic;
}

RpMaterial* RpPTankAtomicGetMaterial(RpAtomic* atomic) { return atomic->geometry->matList.materials[0]; }

void RpPTankAtomicCopyConstantColorToMaterial(RpAtomic* atomic) {
    RpMaterial* material = atomic->geometry->matList.materials[0];
    if (material == nullptr) return;
    material->color.red = atomic->ptank->colorCC[0];
    material->color.green = atomic->ptank->colorCC[1];
    material->color.blue = atomic->ptank->colorCC[2];
    material->color.alpha = atomic->ptank->colorCC[3];
}

const RpPTankPropertyTable* RpPTankAtomicGetPropertyTable(RpAtomic* atomic) {
    static thread_local RpPTankPropertyTable table;
    table.numProp = atomic->ptank->numProp;
    table.stride = atomic->ptank->strideOverride;
    table.dataFlags = atomic->ptank->dataFlags;
    return &table;
}

int32_t RpPTankAtomicLock(RpAtomic* atomic, RpPTankLockStruct* lock, uint32_t flag, uint32_t lockFlags) {
    RpPTankData* data = atomic->ptank;
    if ((flag & data->dataFlags) == 0) {
        lock->stride = 0;
        lock->data = nullptr;
        return 0;
    }
    lock->data = nullptr;
    lock->stride = 0;
    for (int bit = 0; bit < 9; ++bit) {
        if (flag == (1u << bit)) {
            lock->data = data->data[bit];
            lock->stride = data->stride[bit];
        }
    }
    if (data->strideOverride != 0) lock->stride = data->strideOverride;
    if (lock->data != nullptr && (lockFlags & 0x40000000u) != 0) data->lockFlags |= lockFlags | flag;
    return 1;
}

RpAtomic* RpPTankAtomicUnlock(RpAtomic* atomic) {
    RpPTankData* data = atomic->ptank;
    const uint32_t locked = data->lockFlags;
    data->lockFlags = 0;
    data->flags40 |= locked;
    return atomic;
}

int32_t RpAtomicIsPTank(RpAtomic* atomic) { return atomic != nullptr && atomic->ptank != nullptr ? 1 : 0; }

uint8_t* RwShim_PTankArray(RpAtomic* atomic, uint32_t flag) {
    for (int bit = 0; bit < 9; ++bit) {
        if (flag == (1u << bit)) {
            // An array the creation flags dropped (the loader's flags may name it): made on first use.
            RpPTankData* data = atomic->ptank;
            if (data->data[bit] == nullptr) {
                data->storage[bit].assign((data->maxParticles + 4) * kStrides[bit] + 16, 0);
                const uintptr_t base = reinterpret_cast<uintptr_t>(data->storage[bit].data());
                data->data[bit] = data->storage[bit].data() + ((16 - (base & 15)) & 15);
                data->stride[bit] = static_cast<int32_t>(kStrides[bit]);
            }
            return data->data[bit];
        }
    }
    return nullptr;
}
