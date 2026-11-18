// CKInputIconFxData.h - the data of an input-icon effect (key 0x45cc, vtable 0xb1d030, size 0x48). Original
// unit: CKInputIconFxData.cpp (0x1c34f0-0x1c3f00). Its node is CKInputIconNodeFx (0x458c). Not in XXL2; names
// ours.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/IKFxData.h"
#include "k2000/math/CMatrix34.h"

class CKInputIconFxData : public IKFxData {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x117)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9ac708
        return key == 0x45cc || key == 0x304c || key == 0x6 || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKInputIconFxData)

    CKInputIconFxData();  // inlined in 0x001c39c0 CKInputIconFxData_Create (also 0x1c3540)

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001c3a70 CKInputIconFxData_Load
    // vt+0x30 0x001c35c8 CKInputIconFxData_PostLoad: no effect held.
    int32_t PostLoad(int32_t /*type*/) override {
        m_pHeldFx = nullptr;
        return 1;
    }
    // vt+0x24 0x001c3690 RecursiveRegistration: IKFxData's (nothing). vt+0x40 0x001c3828 GetInfo: the default (1).
    // 0x001c3df8 Destructor / 0x001c3da0 DeletingDestructor / 0x001c3760 BaseDestructor: the vtable stores only.
    void Destroy() override;                                     // vt+0x10 0x001c3830 CKInputIconFxData_Destroy
    int32_t MessageProc(uint16_t message, void* data) override;  // vt+0x1c 0x001c3e38 CKInputIconFxData_MessageProc
    uint32_t GetAssociatedFxClassIdentifier() override { return 0x458c; }  // vt+0x54 0x1c35d8

    int32_t m_unk08;      // +0x08 the constructor sets -1; the font id (CManager2d_GetFont_maybe, CKInputIconNodeFx_Update)
    int32_t m_unk0c;      // +0x0c the constructor sets -1; the input sequence id (CKInput_FindButtonIconGlyph_maybe)
    uint32_t m_unk10;     // +0x10 the constructor sets 0; not read by Load; the default input configuration (Update)
    float m_unk14;        // +0x14 1.0; read with +0x18 as one 8-byte block; the near scale x (UpdatePlacement)
    float m_unk18;        // +0x18 1.0; the near scale y
    float m_unk1c;        // +0x1c 1.0; read with +0x20 as one 8-byte block; the far scale x
    float m_unk20;        // +0x20 1.0; the far scale y
    float m_unk24;        // +0x24 10.0; the near distance (the scale is +0x14 up to it)
    float m_unk28;        // +0x28 40.0; the far distance (the scale is +0x1c from it)
    float m_unk2c;        // +0x2c 0; the distance the icon is pulled toward the camera (world placement)
    uint8_t m_unk30;      // +0x30 0; not read by Load; on the screen at the position as screen coordinates
    uint8_t m_unk31;      // +0x31 0; not read by Load; a screen render-stage choice (ApplyDisplayMode)
    uint8_t m_unk32;      // +0x32 0; not read by Load; a screen render-stage choice (ApplyDisplayMode)
    uint8_t m_unk33;      // +0x33 0; read last; on the screen at the projected world position
    CVector3 m_unk34;     // +0x34 0; one 12-byte read; the offset added to the icon's position
    void* m_pTexture;     // +0x40 IKFile_ReadTextureRef (the texture registry is a stub)
    IKSerializable* m_pHeldFx;  // +0x44 the CKInputIconNodeFx the messages acquired (PostLoad: 0); name ours
};
static_assert(CKInputIconFxData::kClassKey == 0x45cc, "key");
DOTD_ASSERT_SIZE(CKInputIconFxData, 0x48);
DOTD_ASSERT_OFFSET(CKInputIconFxData, m_unk08, 0x08);
DOTD_ASSERT_OFFSET(CKInputIconFxData, m_unk14, 0x14);
DOTD_ASSERT_OFFSET(CKInputIconFxData, m_unk1c, 0x1c);
DOTD_ASSERT_OFFSET(CKInputIconFxData, m_unk24, 0x24);
DOTD_ASSERT_OFFSET(CKInputIconFxData, m_unk2c, 0x2c);
DOTD_ASSERT_OFFSET(CKInputIconFxData, m_unk33, 0x33);
DOTD_ASSERT_OFFSET(CKInputIconFxData, m_unk34, 0x34);
DOTD_ASSERT_OFFSET(CKInputIconFxData, m_pTexture, 0x40);
