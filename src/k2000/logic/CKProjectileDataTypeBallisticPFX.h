// CKProjectileDataTypeBallisticPFX.h - the launch parameters of a ballistic projectile (a component; key
// 0xa5cc, vtable 0xb2e158, size 0x74). Original unit: CKProjectileDataTypeBallisticPFX.cpp
// (0x5854c8-0x586258). Base: IKComponent. Referenced by CKProjectileAccessor (+0x08). No XXL2 class of
// this name. Types from the LVL010 data (floats where the samples are floats).
#pragma once
#include <cstdint>

#include "k2000/components/IKComponent.h"
#include "k2000/core/Layout.h"

class CKProjectileDataTypeBallisticPFX : public IKComponent {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x297)
    DOTD_DECLARE_FACTORIES(CKProjectileDataTypeBallisticPFX)

    // The constructor inlined in 0x00585648 CKProjectileDataTypeBallisticPFX_Create: the vtable only.
    CKProjectileDataTypeBallisticPFX() {}
    ~CKProjectileDataTypeBallisticPFX() override {}
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00585928 CKProjectileDataTypeBallisticPFX_Load

    IKSerializable* m_unk04;  // +0x04 a reference
    IKSerializable* m_unk08;  // +0x08 a reference
    IKSerializable* m_unk0c;  // +0x0c a reference
    IKSerializable* m_unk10;  // +0x10 a reference
    IKSerializable* m_unk14;  // +0x14 a reference
    IKSerializable* m_unk18;  // +0x18 a reference
    float m_unk1c;            // +0x1c (samples: 0, 30.0)
    float m_unk20;            // +0x20
    float m_unk24;            // +0x24 (samples: 0)
    float m_unk28;            // +0x28
    uint8_t m_unk2c;          // +0x2c (+0x2d..+0x2f padding)
    uint8_t m_pad2d[3];
    float m_unk30;            // +0x30
    float m_unk34;            // +0x34
    float m_unk38;            // +0x38
    float m_unk3c;            // +0x3c (samples: 180.0, 750.0)
    float m_unk40;            // +0x40
    uint8_t m_unk44;          // +0x44
    uint8_t m_unk45;          // +0x45 (+0x46..+0x47 padding)
    uint8_t m_pad46[2];
    uint32_t m_unk48;         // +0x48 (samples: 0x40a00000, 0x0614068c: not a float)
    uint8_t m_unk4c;          // +0x4c (+0x4d padding)
    uint8_t m_pad4d;
    uint16_t m_unk4e;         // +0x4e
    uint32_t m_unk50;         // +0x50 (samples: 0x02010459, 0x0316c4d9: a key or hash)
    float m_unk54;            // +0x54 (samples: 0)
    float m_unk58;            // +0x58
    float m_unk5c;            // +0x5c
    uint32_t m_unk60;         // +0x60 (samples: 0)
    float m_unk64;            // +0x64
    float m_unk68;            // +0x68
    float m_unk6c;            // +0x6c
    uint32_t m_unk70;         // +0x70 (samples: 0)
};
DOTD_ASSERT_SIZE(CKProjectileDataTypeBallisticPFX, 0x74);
DOTD_ASSERT_OFFSET(CKProjectileDataTypeBallisticPFX, m_unk04, 0x04);
DOTD_ASSERT_OFFSET(CKProjectileDataTypeBallisticPFX, m_unk08, 0x08);
DOTD_ASSERT_OFFSET(CKProjectileDataTypeBallisticPFX, m_unk0c, 0x0c);
DOTD_ASSERT_OFFSET(CKProjectileDataTypeBallisticPFX, m_unk10, 0x10);
DOTD_ASSERT_OFFSET(CKProjectileDataTypeBallisticPFX, m_unk14, 0x14);
DOTD_ASSERT_OFFSET(CKProjectileDataTypeBallisticPFX, m_unk18, 0x18);
DOTD_ASSERT_OFFSET(CKProjectileDataTypeBallisticPFX, m_unk1c, 0x1c);
DOTD_ASSERT_OFFSET(CKProjectileDataTypeBallisticPFX, m_unk20, 0x20);
DOTD_ASSERT_OFFSET(CKProjectileDataTypeBallisticPFX, m_unk24, 0x24);
DOTD_ASSERT_OFFSET(CKProjectileDataTypeBallisticPFX, m_unk28, 0x28);
DOTD_ASSERT_OFFSET(CKProjectileDataTypeBallisticPFX, m_unk2c, 0x2c);
DOTD_ASSERT_OFFSET(CKProjectileDataTypeBallisticPFX, m_unk30, 0x30);
DOTD_ASSERT_OFFSET(CKProjectileDataTypeBallisticPFX, m_unk34, 0x34);
DOTD_ASSERT_OFFSET(CKProjectileDataTypeBallisticPFX, m_unk38, 0x38);
DOTD_ASSERT_OFFSET(CKProjectileDataTypeBallisticPFX, m_unk3c, 0x3c);
DOTD_ASSERT_OFFSET(CKProjectileDataTypeBallisticPFX, m_unk40, 0x40);
DOTD_ASSERT_OFFSET(CKProjectileDataTypeBallisticPFX, m_unk44, 0x44);
DOTD_ASSERT_OFFSET(CKProjectileDataTypeBallisticPFX, m_unk45, 0x45);
DOTD_ASSERT_OFFSET(CKProjectileDataTypeBallisticPFX, m_unk48, 0x48);
DOTD_ASSERT_OFFSET(CKProjectileDataTypeBallisticPFX, m_unk4c, 0x4c);
DOTD_ASSERT_OFFSET(CKProjectileDataTypeBallisticPFX, m_unk4e, 0x4e);
DOTD_ASSERT_OFFSET(CKProjectileDataTypeBallisticPFX, m_unk50, 0x50);
DOTD_ASSERT_OFFSET(CKProjectileDataTypeBallisticPFX, m_unk54, 0x54);
DOTD_ASSERT_OFFSET(CKProjectileDataTypeBallisticPFX, m_unk58, 0x58);
DOTD_ASSERT_OFFSET(CKProjectileDataTypeBallisticPFX, m_unk5c, 0x5c);
DOTD_ASSERT_OFFSET(CKProjectileDataTypeBallisticPFX, m_unk60, 0x60);
DOTD_ASSERT_OFFSET(CKProjectileDataTypeBallisticPFX, m_unk64, 0x64);
DOTD_ASSERT_OFFSET(CKProjectileDataTypeBallisticPFX, m_unk68, 0x68);
DOTD_ASSERT_OFFSET(CKProjectileDataTypeBallisticPFX, m_unk6c, 0x6c);
DOTD_ASSERT_OFFSET(CKProjectileDataTypeBallisticPFX, m_unk70, 0x70);
