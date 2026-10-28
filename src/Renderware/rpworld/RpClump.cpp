// RpClump.cpp - see RpClump.h.
#include "Renderware/rpworld/RpClump.h"

#include <vector>

#include "Renderware/rpworld/RpGeometry.h"
#include "Renderware/rwcore/RwFrameList.h"
#include "Renderware/rwcore/RwStream.h"
#include "k2000/core/Stub.h"

namespace {
constexpr uint32_t kIdStruct = 0x1;
constexpr uint32_t kIdExtension = 0x3;
constexpr uint32_t kIdGeometry = 0xf;
constexpr uint32_t kIdFrameList = 0xe;
constexpr uint32_t kIdGeometryList = 0x1a;

bool ReadBytes(RwStream* stream, void* data, uint32_t length) { return RwStreamRead(stream, data, length) == length; }
}  // namespace

// 0x0069f4a0 RpClumpStreamRead
RpClump* RpClumpStreamRead(RwStream* stream) {
    uint32_t length = 0, version = 0;
    if (RwStreamFindChunk(stream, kIdStruct, &length, &version) == 0) return nullptr;
    int32_t counts[3] = {};  // numAtomics, numLights, numCameras (RwStreamRead 0xc + RwMemNative32)
    if (RwStreamRead(stream, counts, sizeof counts) != sizeof counts) return nullptr;
    RpClump* clump = new RpClump();
    rwFrameList frames = {nullptr, 0};
    bool ok = false;
    std::vector<RpGeometry*> geometries;
    if (RwStreamFindChunk(stream, kIdFrameList, nullptr, nullptr) != 0 && _rwFrameListStreamRead(stream, &frames) != nullptr) {
        clump->frame = frames.frames[0];
        if (RwStreamFindChunk(stream, kIdGeometryList, nullptr, nullptr) != 0 &&
            RwStreamFindChunk(stream, kIdStruct, nullptr, &version) != 0) {
            int32_t numGeometries = 0;
            ok = ReadBytes(stream, &numGeometries, 4);
            for (int32_t i = 0; ok && i < numGeometries; ++i) {
                ok = RwStreamFindChunk(stream, kIdGeometry, nullptr, &version) != 0;
                RpGeometry* geometry = ok ? RpGeometryStreamRead(stream) : nullptr;
                if (geometry == nullptr) ok = false;
                else geometries.push_back(geometry);
            }
            // STUB(C2.9): ClumpAtomicStreamRead 0x69f0d8 with a frame list and a geometry list, RpLightStreamRead,
            // RwCameraStreamRead. No clump of the game files has an atomic, a light or a camera (the 194 team players of
            // the nine levels with a clone manager: each clump is two frames and no geometry), so this fails like
            // the original does on a short read.
            if (ok && (counts[0] > 0 || counts[1] > 0 || counts[2] > 0)) {
                DOTD_STUB_ONCE("RpClumpStreamRead: clump atomics, lights and cameras (C2.9)");
                ok = false;
            }
        }
        for (RpGeometry* geometry : geometries) RpGeometryDestroy(geometry);
        _rwFrameListDeinitialize(&frames);
        // _rwPluginRegistryReadDataChunks: the clump's extension (no plugin of the clump registry has a reader that the
        // game files use; every plugin chunk is skipped).
        if (ok) {
            uint32_t extension = 0;
            ok = RwStreamFindChunk(stream, kIdExtension, &extension, &version) != 0 && RwStreamSkip(stream, extension) != nullptr;
        }
    }
    if (!ok) {
        RpClumpDestroy(clump);
        return nullptr;
    }
    return clump;
}

// 0x0069d748 RpClumpDestroy
int32_t RpClumpDestroy(RpClump* clump) {
    if (clump->frame != nullptr) RwFrameDestroyHierarchy(clump->frame);
    delete clump;
    return 1;
}
