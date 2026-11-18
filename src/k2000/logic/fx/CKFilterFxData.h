// CKFilterFxData.h - a full-screen colour filter effect (key 0x1a0c, vtable 0xb1cae0, size 0x28).
// Original unit: CKFilterFxData.cpp (0x1b8778-0x1b9358); Create and CreateArray are in
// CKMeshPopFxData.cpp, DeleteArray in CKFlashFxData.cpp. XXL2: KServiceFx/Effects/CKFilterFxData.h:
// m_fColorSpeed, m_FinalColor, m_StartColor, m_pTexture, m_baFlags and m_ui8BlendMod are read in the same
// order; DotD then reads one more float (+0x08).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/IKFxData.h"

class IKFx;

class CKFilterFxData : public IKFxData {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x68)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9abd68
        return key == 0x1a0c || key == 0x304c || key == 0x6 || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKFilterFxData)

    CKFilterFxData() {}  // 0x001adf50 CKFilterFxData_Create: IKFxData, then the vtable

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001b87e8 CKFilterFxData_Load
    uint32_t GetAssociatedFxClassIdentifier() override { return 0x19cc; }  // vt+0x54 0x1b8778
    // vt+0x10 0x001b87b0 CKFilterFxData_Destroy: the texture destroyed (the pointer kept).
    void Destroy() override;
    // vt+0x1c 0x001b8bd8 CKFilterFxData_MessageProc: 0x1b00 with flag bit 1 clear releases the held effect (vt+0x58) and
    // acquires a free one (the inlined CKSrvFx::AcquireFx), with bit 1 set starts one (the inlined CKSrvFx::StartEffect);
    // 0x1b01 releases the held one; 0x1b1e fades the held one out over *data seconds (CKFilterNode2dFx_BeginFadeOut_maybe)
    // and gives up its reservation (vt+0x54; the pointer kept). 0 for those, else 1.
    int32_t MessageProc(uint16_t message, void* data) override;

    float m_unk08;            // +0x08
    float m_fColorSpeed;      // +0x0c
    void* m_pTexture;         // +0x10 an RwTexture (IKFile_ReadTextureRef, a reference taken)
    uint8_t m_FinalColor[4];  // +0x14 XXL2 CColor, read without a swap: the file's bytes
    uint8_t m_StartColor[4];  // +0x18 XXL2 CColor, read without a swap: the file's bytes
    uint8_t m_ui8BlendMod;    // +0x1c
    uint8_t m_pad1d[3];
    IKFx* m_unk20;            // +0x20 Load sets 0 for every type; the effect MessageProc 0x1b00 acquired (flag bit 1 clear)
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
