// CKS08MenuObjectives.h - the "Menu Objectives" screen (key 0x878c, vtable 0xb2ca78, size 0x220 from 0x559438 CKS08MenuObjectives_Create). DotD only.
// Original unit: CKS08MenuObjectives.cpp (0x5582b8-0x55aec0).
#pragma once
#include <cstdint>

#include "Spyro2008/logic/CKMenuBase114c.h"
#include "k2000/core/Layout.h"

class CKS08MenuObjectives : public CKMenuBase114c {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x21e)
    DOTD_DECLARE_FACTORIES(CKS08MenuObjectives)

    CKS08MenuObjectives() { m_unk1dc = 0; }  // 0x559438 CKS08MenuObjectives_Create: then +0x1dc = 0
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c9d00
        return key == 0x878c || key == 0x114c || key == 0x730c || key == 0xc;
    }
    int32_t Load(IKFile* file, int32_t type) override;                                   // vt+0x2c 0x55a128 CKS08MenuObjectives_Load
    uint32_t GetWidgetSlotCount() override { return 12; }                                // vt+0x68 0x9c9da0
    WidgetSlot* GetWidgetSlots() override { return m_aWidgetSlots; }                     // vt+0x6c 0x9c9da8
    const char* GetMenuName() override { return "Menu Objectives"; }                     // vt+0xb8 0x9c9d50
    uint8_t VfBC() override { return 1; }                                                // vt+0xbc 0x9c9d88
    IKSerializable** VfC0() override { return m_apMessageOuts; }                         // vt+0xc0 0x9c9d90
    uint8_t VfC4() override { return 6; }                                                // vt+0xc4 0x9c9d60
    IKSerializable** VfC8() override { return m_apMessageIns; }                          // vt+0xc8 0x9c9d68
    uint8_t* VfCC() override { return m_abMessageInFlags; }                              // vt+0xcc 0x9c9d78
    int32_t GetMenuId() override { return 0xa; }                                         // vt+0xe0 0x9c9d58

    WidgetSlot m_aWidgetSlots[12];               // +0x94
    IKSerializable* m_apMessageIns[6];           // +0xf4
    uint8_t m_abMessageInFlags[6];               // +0x10c MessageProc sets one per VfC8 entry
    uint8_t m_unk112[2];
    IKSerializable* m_apMessageOuts[1];          // +0x114
    void* m_pTexture;                            // +0x118 IKFile_ReadTextureRef
    uint32_t m_unk11c[48];                       // +0x11c
    uint32_t m_unk1dc;                           // +0x1dc the constructor sets 0, the Load too (type 0)
    float m_afUnk1e0[6];                         // +0x1e0 read by the Load (0.48 0.44 0.4 0.02 0.07 0.12 in LVL000)
    uint32_t m_unk1f8;                           // +0x1f8 read raw (no swap): the file bytes, e.g. 8b 57 52 9b; a word load sees them big-endian (RGBA colour_maybe)
    uint32_t m_unk1fc;                           // +0x1fc read raw, like +0x1f8
    float m_afUnk200[6];                         // +0x200 read by the Load (0.5 0.4 0.3 0 0.03 0.06)
    IKSerializable* m_pText;                     // +0x218 CKLocTextAccessor (file key 0xe46)
    IKSerializable* m_pSound;                    // +0x21c CKSoundDictionaryID (file key 0x109)
};
DOTD_ASSERT_SIZE(CKS08MenuObjectives, 0x220);
DOTD_ASSERT_OFFSET(CKS08MenuObjectives, m_aWidgetSlots, 0x94);
DOTD_ASSERT_OFFSET(CKS08MenuObjectives, m_apMessageIns, 0xf4);
DOTD_ASSERT_OFFSET(CKS08MenuObjectives, m_abMessageInFlags, 0x10c);
DOTD_ASSERT_OFFSET(CKS08MenuObjectives, m_apMessageOuts, 0x114);
DOTD_ASSERT_OFFSET(CKS08MenuObjectives, m_pTexture, 0x118);
DOTD_ASSERT_OFFSET(CKS08MenuObjectives, m_unk1dc, 0x1dc);
DOTD_ASSERT_OFFSET(CKS08MenuObjectives, m_afUnk1e0, 0x1e0);
DOTD_ASSERT_OFFSET(CKS08MenuObjectives, m_unk1f8, 0x1f8);
DOTD_ASSERT_OFFSET(CKS08MenuObjectives, m_unk1fc, 0x1fc);
DOTD_ASSERT_OFFSET(CKS08MenuObjectives, m_afUnk200, 0x200);
DOTD_ASSERT_OFFSET(CKS08MenuObjectives, m_pText, 0x218);
DOTD_ASSERT_OFFSET(CKS08MenuObjectives, m_pSound, 0x21c);
