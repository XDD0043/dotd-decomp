// CKS08MenuElements.h - the "Menu Elements" screen (key 0x84cc, vtable 0xb2c550, size 0x498 from 0x54c920 CKS08MenuElements_Create). DotD only.
// Original unit: CKS08MenuElements.cpp (0x54ad98-0x553bc8).
#pragma once
#include <cstdint>

#include "Spyro2008/logic/CKMenuBase114c.h"
#include "k2000/core/Layout.h"

class CKS08MenuElements : public CKMenuBase114c {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x213)
    DOTD_DECLARE_FACTORIES(CKS08MenuElements)

    CKS08MenuElements() {  // 0x54c920 CKS08MenuElements_Create: the base part, then three vectors
        m_vUnk248[0] = 0.0f;  // the stores in the original order (lfs TOC1+0x7e20 = 0.0)
        m_vUnk274[0] = 0.0f;
        m_vUnk248[1] = 0.0f;
        m_vUnk248[2] = 0.0f;
        m_vUnk280[0] = 0.0f;
        m_vUnk274[1] = 0.0f;
        m_vUnk274[2] = 0.0f;
        m_vUnk280[1] = 0.0f;
        m_vUnk280[2] = 0.0f;
    }
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c9948
        return key == 0x84cc || key == 0x114c || key == 0x730c || key == 0xc;
    }
    int32_t Load(IKFile* file, int32_t type) override;                                   // vt+0x2c 0x5514f0 CKS08MenuElements_Load
    uint32_t GetWidgetSlotCount() override { return 44; }                                // vt+0x68 0x9c99e8
    WidgetSlot* GetWidgetSlots() override { return m_aWidgetSlots; }                     // vt+0x6c 0x9c99f0
    const char* GetMenuName() override { return "Menu Elements"; }                       // vt+0xb8 0x9c9998
    uint8_t VfBC() override { return 5; }                                                // vt+0xbc 0x9c99d0
    IKSerializable** VfC0() override { return m_apMessageOuts; }                         // vt+0xc0 0x9c99d8
    uint8_t VfC4() override { return 8; }                                                // vt+0xc4 0x9c99a8
    IKSerializable** VfC8() override { return m_apMessageIns; }                          // vt+0xc8 0x9c99b0
    uint8_t* VfCC() override { return m_abMessageInFlags; }                              // vt+0xcc 0x9c99c0
    int32_t GetMenuId() override { return 0x5; }                                         // vt+0xe0 0x9c99a0

    WidgetSlot m_aWidgetSlots[44];               // +0x94
    IKSerializable* m_apMessageIns[8];           // +0x1f4
    uint8_t m_abMessageInFlags[8];               // +0x214 MessageProc sets one per VfC8 entry
    IKSerializable* m_apMessageOuts[5];          // +0x21c
    uint32_t m_unk230[4];                        // +0x230
    uint8_t m_unk240;                            // +0x240 the Load clears it
    uint8_t m_unk241[3];
    uint32_t m_unk244;                           // +0x244 read by the Load
    float m_vUnk248[3];                          // +0x248 the constructor sets 0
    uint32_t m_unk254[2];                        // +0x254
    float m_afUnk25c[6];                         // +0x25c read by the Load
    float m_vUnk274[3];                          // +0x274 the constructor sets 0
    float m_vUnk280[3];                          // +0x280 the constructor sets 0
    uint8_t m_unk28c;                            // +0x28c read by the Load (1 byte)
    uint8_t m_unk28d[3];
    float m_fUnk290;                             // +0x290 read by the Load
    float m_fUnk294;                             // +0x294 read by the Load
    uint32_t m_unk298[2];                        // +0x298
    IKSerializable* m_pText2a0;                  // +0x2a0 CKLocTextAccessor (struct draft)
    IKSerializable* m_pText2a4;                  // +0x2a4 CKLocTextAccessor (struct draft)
    uint32_t m_unk2a8;                           // +0x2a8
    void* m_apTextures2ac[8];                    // +0x2ac IKFile_ReadTextureRef, the last first
    void* m_apTextures2cc[24];                   // +0x2cc IKFile_ReadTextureRef, the last first
    uint8_t m_unk32c;                            // +0x32c the Load clears it
    uint8_t m_unk32d[3];
    IKSerializable* m_pFlashFx;                  // +0x330 CKFlashFxData (struct draft)
    uint32_t m_unk334;                           // +0x334
    IKSerializable* m_pQuake338;                 // +0x338 CKQuakeCpnt (struct draft)
    IKSerializable* m_pQuakeUpdater33c;          // +0x33c CKQuakeCpntUpdater (struct draft)
    uint32_t m_unk340[3];                        // +0x340
    IKSerializable* m_pQuake34c;                 // +0x34c CKQuakeCpnt (struct draft)
    IKSerializable* m_pQuakeUpdater350;          // +0x350 CKQuakeCpntUpdater (struct draft)
    uint32_t m_unk354[11];                       // +0x354
    int32_t m_unk380;                            // +0x380 read raw (no swap): a word load sees the file bytes big-endian
    uint32_t m_unk384;                           // +0x384 read by the Load
    uint32_t m_unk388;                           // +0x388 read by the Load
    uint32_t m_unk38c[11];                       // +0x38c
    uint32_t m_unk3b8;                           // +0x3b8 read raw (no swap)
    float m_fUnk3bc;                             // +0x3bc read by the Load
    float m_fUnk3c0;                             // +0x3c0 read by the Load
    uint32_t m_unk3c4[35];                       // +0x3c4
    int32_t m_unk450;                            // +0x450 read raw (no swap)
    float m_fUnk454;                             // +0x454 read by the Load
    float m_fUnk458;                             // +0x458 read by the Load
    uint32_t m_unk45c[6];                        // +0x45c
    uint32_t m_unk474;                           // +0x474 read raw (no swap)
    float m_fUnk478;                             // +0x478 read by the Load
    float m_fUnk47c;                             // +0x47c read by the Load
    uint32_t m_unk480[2];                        // +0x480
    uint8_t m_unk488;                            // +0x488 read by the Load (1 byte)
    uint8_t m_unk489;                            // +0x489 read by the Load (1 byte)
    uint8_t m_unk48a[2];
    float m_fUnk48c;                             // +0x48c read by the Load
    IKSerializable* m_pSound;                    // +0x490 CKSoundDictionaryID (struct draft)
    uint32_t m_unk494;                           // +0x494
};
DOTD_ASSERT_SIZE(CKS08MenuElements, 0x498);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_aWidgetSlots, 0x94);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_apMessageIns, 0x1f4);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_abMessageInFlags, 0x214);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_apMessageOuts, 0x21c);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_unk240, 0x240);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_unk244, 0x244);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_vUnk248, 0x248);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_afUnk25c, 0x25c);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_vUnk274, 0x274);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_vUnk280, 0x280);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_unk28c, 0x28c);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_fUnk290, 0x290);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_fUnk294, 0x294);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_pText2a0, 0x2a0);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_pText2a4, 0x2a4);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_apTextures2ac, 0x2ac);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_apTextures2cc, 0x2cc);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_unk32c, 0x32c);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_pFlashFx, 0x330);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_pQuake338, 0x338);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_pQuakeUpdater33c, 0x33c);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_pQuake34c, 0x34c);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_pQuakeUpdater350, 0x350);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_unk380, 0x380);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_unk384, 0x384);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_unk388, 0x388);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_unk3b8, 0x3b8);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_fUnk3bc, 0x3bc);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_fUnk3c0, 0x3c0);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_unk450, 0x450);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_fUnk454, 0x454);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_fUnk458, 0x458);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_unk474, 0x474);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_fUnk478, 0x478);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_fUnk47c, 0x47c);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_unk488, 0x488);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_unk489, 0x489);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_fUnk48c, 0x48c);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_pSound, 0x490);
