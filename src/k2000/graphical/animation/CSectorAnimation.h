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
    ~CSectorAnimation() override {}                     // 0x009a0498 / 0x009a04d0 CSectorAnimation_Destructor / _DeletingDestructor: the vtables only
    int32_t IsKindOfClass(uint32_t key) override { return key == 0xdcd || key == 0xc; }  // 0x9a04b0
    // vt+0x10 0x000a5928 CSectorAnimation_Destroy (the sector unload): every animation destroyed, the array freed.
    void Destroy() override;
    // vt+0x24 0x000a58c8 CSectorAnimation_RecursiveRegistration: type 0 registers the object.
    void RecursiveRegistration(int32_t type) override;
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
