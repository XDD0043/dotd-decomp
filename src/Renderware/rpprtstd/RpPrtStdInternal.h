// RpPrtStdInternal.h - what RpPrtStd.cpp and RpPrtAdv.cpp share: the stream the plugin readers read from
// (the atomic's bytes in memory: the RW stream reads, little-endian to native), the plugin globals the
// readers consult, and the property helpers.
#pragma once
#include <cstdint>
#include <cstring>

#include "Renderware/rpprtstd/RpPrtStd.h"

namespace rpprtstd {

// The RW reads the plugin readers make: RwStreamRead (raw bytes), RwStreamReadInt32 / RwStreamReadReal
// (little-endian words to native), RwStreamFindChunk. Reads past the end yield zeros (the RW stream would
// stop with E_RW_ENDOFSTREAM).
struct Stream {
    const uint8_t* data;
    uint32_t length;
    uint32_t position;

    void Read(void* out, uint32_t bytes) {
        uint8_t* dst = static_cast<uint8_t*>(out);
        for (uint32_t i = 0; i < bytes; ++i) dst[i] = position + i < length ? data[position + i] : 0;
        position += bytes;
    }
    // RwStreamReadInt32 / RwStreamReadReal (RwMemNative32 / RwMemFloat32ToReal): `bytes` / 4 words.
    void ReadWords(void* out, uint32_t bytes) {
        uint8_t* dst = static_cast<uint8_t*>(out);
        for (uint32_t i = 0; i + 4 <= bytes; i += 4) {
            uint8_t b[4];
            Read(b, 4);
            const uint32_t word = static_cast<uint32_t>(b[0]) | (static_cast<uint32_t>(b[1]) << 8) |
                                  (static_cast<uint32_t>(b[2]) << 16) | (static_cast<uint32_t>(b[3]) << 24);
            std::memcpy(dst + i, &word, 4);
        }
    }
    int32_t ReadInt32() {
        int32_t value = 0;
        ReadWords(&value, 4);
        return value;
    }
    void Skip(uint32_t bytes) { position += bytes; }
    // RwStreamFindChunk: headers read, other chunks skipped, until `type`; 1 when found (the position
    // after its header). The library version check (0x35000..0x37002) always passes on the game's data.
    int32_t FindChunk(uint32_t type, uint32_t* lengthOut) {
        while (position + 12 <= length) {
            const uint32_t chunkType = static_cast<uint32_t>(ReadInt32());
            const uint32_t chunkLength = static_cast<uint32_t>(ReadInt32());
            ReadInt32();  // library id
            if (chunkType == type) {
                if (lengthOut != nullptr) *lengthOut = chunkLength;
                return 1;
            }
            Skip(chunkLength);
        }
        return 0;
    }
};

// 0x00cfba80 (RpPrtStd globals +0x0c): the stream version of the plugin data being read (the top byte of
// the atomic's emitter count; 3 in DotD's data), 0 outside a read.
extern int32_t g_streamVersion;

// A property of an emitter as a byte pointer (emitter + offset).
inline uint8_t* PropertyAt(RpPrtStdEmitter* emitter, int32_t offset) {
    return reinterpret_cast<uint8_t*>(emitter) + offset;
}
inline int32_t EmitterPropOffset(const RpPrtStdEmitter* emitter, int32_t propID) {
    return RpPrtStdPropTabGetPropOffset(emitter->emtClass->propTab, propID);
}
inline uint32_t& WordAt(uint8_t* base, uint32_t offset) { return *reinterpret_cast<uint32_t*>(base + offset); }

// A property's pointer to its own data (multi colour, multi texcoords, ...): the PS3 word holds the
// address; natively only 32-bit builds can store it (the readers use the fixed position instead).
inline void StoreSelfPointer(uint8_t* slot, const void* pointer) {
    uint32_t word = 0;
    if (sizeof(void*) == 4) word = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(pointer));
    std::memcpy(slot, &word, 4);
}

// The adv callbacks (RpPrtAdv.cpp) the emitter class builder installs.
RpPrtStdEmitter* PointListInit(RpAtomic*, RpPrtStdEmitter* emitter, void*);          // 0x6f20a0
RpPrtStdEmitter* PointListStreamRead(RpAtomic*, RpPrtStdEmitter* emitter, void*);    // 0x6f23e8
RpPrtStdEmitter* PointListCopy(RpAtomic*, RpPrtStdEmitter* emitter, void*);          // 0x6f25a0
RpPrtStdEmitter* CircleStreamRead(RpAtomic*, RpPrtStdEmitter* emitter, void*);       // 0x6f17b0
RpPrtStdEmitter* CircleCopy(RpAtomic*, RpPrtStdEmitter* emitter, void*);             // 0x6f18c0
RpPrtStdEmitter* SphereStreamRead(RpAtomic*, RpPrtStdEmitter* emitter, void*);       // 0x6f0f08
RpPrtStdEmitter* SphereCopy(RpAtomic*, RpPrtStdEmitter* emitter, void*);             // 0x6f1010
RpPrtStdEmitter* PrtEmitterStreamRead(RpAtomic*, RpPrtStdEmitter* emitter, void*);   // 0x6f2fb0
RpPrtStdEmitter* PrtEmitterCopy(RpAtomic*, RpPrtStdEmitter* emitter, void*);         // 0x6f3078
RpPrtStdEmitter* MultiInit(RpAtomic*, RpPrtStdEmitter* emitter, void*);              // 0x6f38f0
RpPrtStdEmitter* MultiStreamRead(RpAtomic*, RpPrtStdEmitter* emitter, void*);        // 0x6f3d58
RpPrtStdEmitter* MultiCopy(RpAtomic*, RpPrtStdEmitter* emitter, void*);              // 0x6f3fd0
RpPrtStdEmitter* TexCoordsStepInit(RpAtomic*, RpPrtStdEmitter* emitter, void*);      // 0x6f54e0
RpPrtStdEmitter* TexCoordsStepStreamRead(RpAtomic*, RpPrtStdEmitter* emitter, void*);  // 0x6f56c8
RpPrtStdEmitter* TexCoordsStepCopy(RpAtomic*, RpPrtStdEmitter* emitter, void*);      // 0x6f57d0

// 0x006ef7c8 RpPrtStdEClass_BuildStdCallBackArray_maybe (RpPrtAdv.cpp): the emitter class setup callback.
RpPrtStdEmitterClass* EClassBuildCallBackArray(RpPrtStdEmitterClass* eClass);
// 0x007297c8 RpPrtStdEClassSetCallBackArray_maybe (RpPrtStd.cpp)
void EClassSetCallBackArray(RpPrtStdEmitterClass* eClass, int32_t count, const RpPrtStdEmitterCallBackArray* arrays);
// The standard emitter callbacks (RpPrtStd.cpp; TOC 0x00c21ce0..0x00c21d04 in the builder).
RpPrtStdEmitterCallBackArray StandardCallBacks();

}  // namespace rpprtstd
