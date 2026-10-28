// CSectorAnimation.h - a sector's RenderWare animations (key 0xdcd, vtable 0xb17198, size 0xc). Original
// unit: CSectorAnimation.cpp (0xa54c0..). Not in XXL2; the field names say what the Load stores.
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"

struct RtAnimAnimation;

class CSectorAnimation : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryGraphical, 0x37)
    DOTD_DECLARE_FACTORIES(CSectorAnimation)

    CSectorAnimation() {}                               // 0x000a5670 CSectorAnimation_Create: the vtable only
    ~CSectorAnimation() override {}                     // STUB(C1.6): 0x9a0498 / 0xa5928 free the animations
    int32_t IsKindOfClass(uint32_t key) override { return key == 0xdcd || key == 0xc; }  // 0x9a04b0
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x000a5748 CSectorAnimation_Load
    int32_t GetSerializationFlags() override { return 1; }  // vt+0x34 0x9a0490

    uint32_t m_ui32NbAnimations;      // +0x04
    RtAnimAnimation** m_apAnimations; // +0x08 Mem_AllocAligned16; null when the count is 0
};
DOTD_ASSERT_SIZE(CSectorAnimation, 0xc);
DOTD_ASSERT_OFFSET(CSectorAnimation, m_ui32NbAnimations, 0x04);
DOTD_ASSERT_OFFSET(CSectorAnimation, m_apAnimations, 0x08);

// 0x00079898 (in the AnimBlendSlot unit): the game data after each animation chunk.
void CSectorAnimation_LoadEntry_maybe(RtAnimAnimation* animation, IKFile* file);
