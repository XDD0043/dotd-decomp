// KMemBuffer.h - a growable memory buffer (vtable 0xb14ef0, 0x20 bytes on the PS3), embedded in the
// game manager (the save-state buffer +0x1c and three more). Original unit: KMemBuffer.cpp (0x48350-0x497a0).
// The stream functions (ReadFromStream, CreateFromStream) belong to the save data and are not used yet.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"

class KMemBuffer {
public:
    // 0x00048370 KMemBuffer_Construct
    KMemBuffer() {
        m_readerCount = 0;
        m_pData = nullptr;
        m_bExternal = 0;
        m_writerCount = 0;
    }
    // 0x000485f8 KMemBuffer_Destructor / 0x00048550 KMemBuffer_DeletingDestructor: Free's body.
    virtual ~KMemBuffer();

    // 0x000483b8 KMemBuffer_Free: an owned block freed.
    void Free();
    // 0x00048430 KMemBuffer_Init: `granularity` and a zeroed block of `capacity` bytes (at least 10); size 0, owned.
    void Init(int32_t capacity, uint32_t granularity);
    // 0x000484a0 KMemBuffer_EnsureCapacity_maybe: an owned block smaller than `size` grows to `size` rounded up to the
    // granularity (Mem_ReallocAligned16), the new bytes zeroed.
    void EnsureCapacity(int32_t size);
    // 0x00048ec0 KMemBuffer_Resize: the size set to `size`, the block grown as EnsureCapacity does.
    void Resize(int32_t size);

    uint8_t* m_pData;           // +0x04 Mem_CallocAligned16 (Init); the constructor sets 0
    uint32_t m_ui32Granularity; // +0x08 Init
    int32_t m_i32Capacity;      // +0x0c Init: at least 10
    int32_t m_i32Size;          // +0x10 Resize
    int32_t m_readerCount;      // +0x14 the memory streams open on it for reading (KMemoryStream_Open / _Close)
    int32_t m_writerCount;      // +0x18 the memory streams open on it for writing or read-write (the same)
    uint8_t m_bExternal;        // +0x1c 0: the block is owned (not freed or grown otherwise)
    uint8_t m_pad1d[3];
};
DOTD_ASSERT_SIZE(KMemBuffer, 0x20);
