// CKS08HeroBlow.h - one hero blow (key 0x7a8c, vtable 0xb230b0, size 0x68): the attack a CKS08HeroCombo node
// performs. Original unit: CKS08HeroBlow.cpp (0x36e2d0-0x36f578). No XXL2 class of this name; members keep
// placeholder names (types from the live struct draft and the file data). Create only stores the vtable.
#pragma once
#include <cstdint>

#include "Spyro2008/logic/CKS08HeroDamage.h"
#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"

class CKS08HeroBlow : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x1ea)
    DOTD_DECLARE_FACTORIES(CKS08HeroBlow)

    CKS08HeroBlow() {}  // inlined in 0x0036e440 CKS08HeroBlow_Create: the vtable only
    ~CKS08HeroBlow() override {}
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0036e6b8 CKS08HeroBlow_Load

    uint8_t m_unk04;            // +0x04
    uint8_t m_pad05[3];
    float m_unk08;              // +0x08 (file: 0.8, 1.0)
    float m_unk0c;              // +0x0c
    float m_unk10;              // +0x10
    uint8_t m_unk14;            // +0x14
    uint8_t m_pad15[3];
    float m_unk18;              // +0x18 runtime
    float m_unk1c;              // +0x1c
    float m_unk20;              // +0x20 (file: 0.02)
    float m_unk24;              // +0x24 (file: 320, 160, 200)
    float m_unk28;              // +0x28
    uint8_t m_unk2c;            // +0x2c runtime
    uint8_t m_unk2d;            // +0x2d
    uint8_t m_pad2e[2];
    int32_t m_unk30;            // +0x30
    uint8_t m_unk34;            // +0x34
    uint8_t m_pad35[3];
    float m_unk38;              // +0x38 (file: 1.0)
    IKSerializable* m_unk3c;    // +0x3c (file: key 0x9e8c references, live: CKAnimatedCameraData)
    uint8_t m_unk40;            // +0x40
    uint8_t m_pad41[3];
    float m_unk44;              // +0x44 (file: 0.4)
    uint8_t m_unk48;            // +0x48 whether +0x4c is in the file
    uint8_t m_pad49[3];
    IKSerializable* m_unk4c;    // +0x4c (live: CKCurve2DCpnt); 0 when +0x48 is 0
    uint8_t m_unk50;            // +0x50
    uint8_t m_unk51;            // +0x51
    uint8_t m_unk52;            // +0x52
    uint8_t m_unk53;            // +0x53
    float m_unk54;              // +0x54
    uint8_t m_unk58;            // +0x58
    uint8_t m_pad59[3];
    float m_unk5c;              // +0x5c (file: 1.0)
    uint8_t m_unk60;            // +0x60
    uint8_t m_unk61;            // +0x61
    uint8_t m_pad62[2];
    CKS08HeroDamage* m_pDamage; // +0x64
};
DOTD_ASSERT_SIZE(CKS08HeroBlow, 0x68);
DOTD_ASSERT_OFFSET(CKS08HeroBlow, m_unk04, 0x04);
DOTD_ASSERT_OFFSET(CKS08HeroBlow, m_unk08, 0x08);
DOTD_ASSERT_OFFSET(CKS08HeroBlow, m_unk14, 0x14);
DOTD_ASSERT_OFFSET(CKS08HeroBlow, m_unk1c, 0x1c);
DOTD_ASSERT_OFFSET(CKS08HeroBlow, m_unk2d, 0x2d);
DOTD_ASSERT_OFFSET(CKS08HeroBlow, m_unk30, 0x30);
DOTD_ASSERT_OFFSET(CKS08HeroBlow, m_unk34, 0x34);
DOTD_ASSERT_OFFSET(CKS08HeroBlow, m_unk38, 0x38);
DOTD_ASSERT_OFFSET(CKS08HeroBlow, m_unk3c, 0x3c);
DOTD_ASSERT_OFFSET(CKS08HeroBlow, m_unk40, 0x40);
DOTD_ASSERT_OFFSET(CKS08HeroBlow, m_unk44, 0x44);
DOTD_ASSERT_OFFSET(CKS08HeroBlow, m_unk48, 0x48);
DOTD_ASSERT_OFFSET(CKS08HeroBlow, m_unk4c, 0x4c);
DOTD_ASSERT_OFFSET(CKS08HeroBlow, m_unk50, 0x50);
DOTD_ASSERT_OFFSET(CKS08HeroBlow, m_unk53, 0x53);
DOTD_ASSERT_OFFSET(CKS08HeroBlow, m_unk54, 0x54);
DOTD_ASSERT_OFFSET(CKS08HeroBlow, m_unk58, 0x58);
DOTD_ASSERT_OFFSET(CKS08HeroBlow, m_unk5c, 0x5c);
DOTD_ASSERT_OFFSET(CKS08HeroBlow, m_unk60, 0x60);
DOTD_ASSERT_OFFSET(CKS08HeroBlow, m_unk61, 0x61);
DOTD_ASSERT_OFFSET(CKS08HeroBlow, m_pDamage, 0x64);
