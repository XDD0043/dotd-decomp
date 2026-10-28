// RpAtomic.cpp - the C1.3 atomic and PTank shim (see RpAtomic.h).
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
    return atomic;
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

    RpAtomic* atomic = NewAtomic();
    RpPTankData* data = new RpPTankData();
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
    atomic->texture = nullptr;  // RpMaterialSetTexture(material, null)
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
    std::memcpy(data->materialColor, data->colorCC, 4);
    RwRenderStateGet(static_cast<RwRenderState>(10), &data->renderAC);
    RwRenderStateGet(static_cast<RwRenderState>(11), &data->renderB0);
    RwRenderStateGet(static_cast<RwRenderState>(12), &data->renderB4);
    atomic->renderCallBack = RpPTankAtomicRender;
    return atomic;
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
