// CKInputIconFxData.h - the data of an input-icon effect (key 0x45cc, vtable 0xb1d030, size 0x48). Original
// unit: CKInputIconFxData.cpp (0x1c34f0-0x1c3f00). Its node is CKInputIconNodeFx (0x458c). Not in XXL2; names
// ours.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/IKFxData.h"

class CKInputIconFxData : public IKFxData {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x117)
    DOTD_DECLARE_FACTORIES(CKInputIconFxData)

    CKInputIconFxData();  // inlined in 0x001c39c0 CKInputIconFxData_Create (also 0x1c3540)

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001c3a70 CKInputIconFxData_Load
    // vt+0x30 PostLoad 0x1c35c8 (stays the default in C2.1).
    uint32_t GetAssociatedFxClassIdentifier() override { return 0x458c; }  // vt+0x54 0x1c35d8

    int32_t m_unk08;      // +0x08 the constructor sets -1
    int32_t m_unk0c;      // +0x0c the constructor sets -1
    uint32_t m_unk10;     // +0x10 the constructor sets 0; not read
    float m_unk14;        // +0x14 1.0; read with +0x18 as one 8-byte block
    float m_unk18;        // +0x18 1.0
    float m_unk1c;        // +0x1c 1.0; read with +0x20 as one 8-byte block
    float m_unk20;        // +0x20 1.0
    float m_unk24;        // +0x24 10.0
    float m_unk28;        // +0x28 40.0
    uint32_t m_unk2c;     // +0x2c 0
    uint8_t m_unk30;      // +0x30 0; not read
    uint8_t m_unk31;      // +0x31 0; not read
    uint8_t m_unk32;      // +0x32 0; not read
    uint8_t m_unk33;      // +0x33 0; read last
    uint32_t m_unk34;     // +0x34 0; read with +0x38/+0x3c as one 12-byte block
    float m_unk38;        // +0x38 0.0
    uint32_t m_unk3c;     // +0x3c 0
    void* m_pTexture;     // +0x40 IKFile_ReadTextureRef (the texture registry is a stub)
    uint32_t m_unk44;     // +0x44 not set
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
