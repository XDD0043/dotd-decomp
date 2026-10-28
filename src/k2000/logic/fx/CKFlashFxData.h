// CKFlashFxData.h - a flash (lens glow) effect (key 0x170c, vtable 0xb1cd00, size 0x68). Original units:
// CKFlashFxData_2.cpp (0x1bb408-0x1bc520: Load, PostLoad, ...) and CKFlashFxData.cpp (0x1ad058-0x1adc70:
// the registration and the FX data DeleteArrays); Create and CreateArray are in CKMeshPopFxData.cpp.
// XXL2: KServiceFx/Effects/CKFlashFxData.h. DotD reads many more values; only m_pTexture and m_Color,
// read one after the other in both games, take XXL2's names.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/IKFxData.h"

class CKFlashFxData : public IKFxData {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x5c)
    DOTD_DECLARE_FACTORIES(CKFlashFxData)

    CKFlashFxData() {}  // 0x001ae070 CKFlashFxData_Create: IKFxData, then the vtable

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001bb870 CKFlashFxData_Load
    // vt+0x30 PostLoad 0x1bb820 calls IKFxData's (returns 1).
    uint32_t GetAssociatedFxClassIdentifier() override { return 0x15cc; }  // vt+0x54 0x1bb408

    void* m_pTexture;      // +0x08 IKFile_ReadTextureRef (the texture registry is STUB(C1.3))
    uint8_t m_Color[4];    // +0x0c XXL2 CColor, read without a swap: the file's bytes
    uint8_t m_unk10;       // +0x10
    uint8_t m_unk11;       // +0x11
    uint8_t m_unk12;       // +0x12
    uint8_t m_unk13;       // +0x13
    float m_unk14[2];      // +0x14 pairs: one 8-byte read, two byte-swapped words
    float m_unk1c[2];      // +0x1c pair
    float m_unk24[2];      // +0x24 pair
    float m_unk2c;         // +0x2c
    float m_unk30;         // +0x30
    float m_unk34[2];      // +0x34 pair
    float m_unk3c[2];      // +0x3c pair
    float m_unk44[2];      // +0x44 pair
    uint32_t m_unk4c;      // +0x4c
    float m_unk50;         // +0x50
    float m_unk54;         // +0x54
    float m_unk58;         // +0x58
    float m_unk5c;         // +0x5c
    float m_unk60;         // +0x60
    float m_unk64;         // +0x64
};
DOTD_ASSERT_SIZE(CKFlashFxData, 0x68);
DOTD_ASSERT_OFFSET(CKFlashFxData, m_pTexture, 0x08);
DOTD_ASSERT_OFFSET(CKFlashFxData, m_Color, 0x0c);
DOTD_ASSERT_OFFSET(CKFlashFxData, m_unk10, 0x10);
DOTD_ASSERT_OFFSET(CKFlashFxData, m_unk13, 0x13);
DOTD_ASSERT_OFFSET(CKFlashFxData, m_unk14, 0x14);
DOTD_ASSERT_OFFSET(CKFlashFxData, m_unk1c, 0x1c);
DOTD_ASSERT_OFFSET(CKFlashFxData, m_unk24, 0x24);
DOTD_ASSERT_OFFSET(CKFlashFxData, m_unk2c, 0x2c);
DOTD_ASSERT_OFFSET(CKFlashFxData, m_unk30, 0x30);
DOTD_ASSERT_OFFSET(CKFlashFxData, m_unk34, 0x34);
DOTD_ASSERT_OFFSET(CKFlashFxData, m_unk3c, 0x3c);
DOTD_ASSERT_OFFSET(CKFlashFxData, m_unk44, 0x44);
DOTD_ASSERT_OFFSET(CKFlashFxData, m_unk4c, 0x4c);
DOTD_ASSERT_OFFSET(CKFlashFxData, m_unk50, 0x50);
DOTD_ASSERT_OFFSET(CKFlashFxData, m_unk54, 0x54);
DOTD_ASSERT_OFFSET(CKFlashFxData, m_unk64, 0x64);
