// CKFilterFxData.h - a full-screen colour filter effect (key 0x1a0c, vtable 0xb1cae0, size 0x28).
// Original unit: CKFilterFxData.cpp (0x1b8778-0x1b9358); Create and CreateArray are in
// CKMeshPopFxData.cpp, DeleteArray in CKFlashFxData.cpp. XXL2: KServiceFx/Effects/CKFilterFxData.h:
// m_fColorSpeed, m_FinalColor, m_StartColor, m_pTexture, m_baFlags and m_ui8BlendMod are read in the same
// order; DotD then reads one more float (+0x08).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/IKFxData.h"

class CKFilterFxData : public IKFxData {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x68)
    DOTD_DECLARE_FACTORIES(CKFilterFxData)

    CKFilterFxData() {}  // 0x001adf50 CKFilterFxData_Create: IKFxData, then the vtable

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001b87e8 CKFilterFxData_Load
    uint32_t GetAssociatedFxClassIdentifier() override { return 0x19cc; }  // vt+0x54 0x1b8778

    float m_unk08;            // +0x08
    float m_fColorSpeed;      // +0x0c
    void* m_pTexture;         // +0x10 IKFile_ReadTextureRef (the texture registry is STUB(C1.3))
    uint8_t m_FinalColor[4];  // +0x14 XXL2 CColor, read without a swap: the file's bytes
    uint8_t m_StartColor[4];  // +0x18 XXL2 CColor, read without a swap: the file's bytes
    uint8_t m_ui8BlendMod;    // +0x1c
    uint8_t m_pad1d[3];
    uint32_t m_unk20;         // +0x20 Load sets 0 for every type
    // +0x24 XXL2 CBitArray8. Load keeps bits 2..7, clears bit 0 and ORs in the file byte shifted left by
    // one (XXL2 puts the byte in bit 0 instead).
    uint8_t m_baFlags;
    uint8_t m_pad25[3];
};
DOTD_ASSERT_SIZE(CKFilterFxData, 0x28);
DOTD_ASSERT_OFFSET(CKFilterFxData, m_unk08, 0x08);
DOTD_ASSERT_OFFSET(CKFilterFxData, m_fColorSpeed, 0x0c);
DOTD_ASSERT_OFFSET(CKFilterFxData, m_pTexture, 0x10);
DOTD_ASSERT_OFFSET(CKFilterFxData, m_FinalColor, 0x14);
DOTD_ASSERT_OFFSET(CKFilterFxData, m_StartColor, 0x18);
DOTD_ASSERT_OFFSET(CKFilterFxData, m_ui8BlendMod, 0x1c);
DOTD_ASSERT_OFFSET(CKFilterFxData, m_unk20, 0x20);
DOTD_ASSERT_OFFSET(CKFilterFxData, m_baFlags, 0x24);
