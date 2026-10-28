// KMemBuffer.h - a growable memory buffer (vtable 0xb14ef0, 0x20 bytes on the PS3), embedded in the
// game manager. Original unit: KMemBuffer.cpp (0x48350-0x497a0). STUB(C1.6): only the constructor;
// the buffer functions (Init/Resize) are not ported.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"

class KMemBuffer {
public:
    // 0x00048370 KMemBuffer_Construct
    KMemBuffer() {
        m_unk14 = 0;
        m_unk04 = 0;
        m_unk1c = 0;
        m_unk18 = 0;
    }
    virtual ~KMemBuffer() {}

    uint32_t m_unk04;   // +0x04 0
    uint32_t m_unk08;   // +0x08
    uint32_t m_unk0c;   // +0x0c
    uint32_t m_unk10;   // +0x10
    uint32_t m_unk14;   // +0x14 0
    uint32_t m_unk18;   // +0x18 0
    uint8_t m_unk1c;    // +0x1c 0
    uint8_t m_pad1d[3];
};
DOTD_ASSERT_SIZE(KMemBuffer, 0x20);
