// CKProjectileTypeBallisticPFX.h - a ballistic projectile pool (key 0x140c, vtable 0xb2e208, size 0x34).
// Original unit: CKProjectileTypeBallisticPFX.cpp (0x586258-0x58e9c0). Base: IKProjectileType (its Load is
// called first). XXL2 has a class of this name, but DotD loads different data (no floats; references, a
// word and a byte), so the members keep placeholder names.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/services/IKProjectileType.h"

class CSGLeaf;

class CKProjectileTypeBallisticPFX : public IKProjectileType {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x50)
    DOTD_DECLARE_FACTORIES(CKProjectileTypeBallisticPFX)

    // One projectile (0x88 bytes, m_ui8MaxProjectiles of them; the Load sets what is listed).
    struct Projectile {
        uint32_t m_unk00;                               // +0x00 0
        uint32_t m_unk04;                               // +0x04 not set by the Load
        CSGLeaf* m_pNode;                               // +0x08 a reference (file); the Load sets its flag 0x4 (hidden)
        CVector3 m_unk0c;                               // +0x0c (0, 0, 0)
        CVector3 m_unk18;                               // +0x18 (0, 0, 0)
        CVector3 m_unk24;                               // +0x24 (0, 0, 0)
        uint32_t m_unk30;                               // +0x30 0
        uint32_t m_unk34;                               // +0x34 0
        CGroundContactDatasInOut m_GrdContDatasInOut;   // +0x38 _maybe (the constructor values of XXL2's type)
        uint8_t m_unk64;                                // +0x64 0
        uint8_t m_pad65[3];
        uint32_t m_unk68;                               // +0x68 0
        float m_unk6c;                                  // +0x6c 1.0
        uint32_t m_unk70;                               // +0x70 not set by the Load
        uint8_t m_ui8Index;                             // +0x74 its index
        uint8_t m_pad75[3];
        uint32_t m_unk78;                               // +0x78 0
        uint32_t m_unk7c;                               // +0x7c 0
        IKSerializable* m_unk80;                        // +0x80 a reference (file)
        uint32_t m_unk84;                               // +0x84 not set by the Load
    };

    // The constructor inlined in 0x005868e8 CKProjectileTypeBallisticPFX_Create: IKProjectileType's, then
    // the vtable only.
    CKProjectileTypeBallisticPFX() {}
    ~CKProjectileTypeBallisticPFX() override {}
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0058e508 CKProjectileTypeBallisticPFX_Load

    // +0x22 (in IKProjectileType's tail padding, m_aSubclassTail[0]): a byte, the last one the Load reads.
    uint8_t& Unk22() { return m_aSubclassTail[0]; }

    IKSerializable* m_unk24;  // +0x24 a reference
    IKSerializable* m_unk28;  // +0x28 a reference (PostLoad clears option 0x80 when it is null)
    int32_t m_unk2c;          // +0x2c (samples: 0, -1)
    IKSerializable* m_unk30;  // +0x30 a reference
};
DOTD_ASSERT_SIZE(CKProjectileTypeBallisticPFX, 0x34);
DOTD_ASSERT_SIZE(CKProjectileTypeBallisticPFX::Projectile, 0x88);
DOTD_ASSERT_OFFSET(CKProjectileTypeBallisticPFX::Projectile, m_pNode, 0x08);
DOTD_ASSERT_OFFSET(CKProjectileTypeBallisticPFX::Projectile, m_GrdContDatasInOut, 0x38);
DOTD_ASSERT_OFFSET(CKProjectileTypeBallisticPFX::Projectile, m_ui8Index, 0x74);
DOTD_ASSERT_OFFSET(CKProjectileTypeBallisticPFX::Projectile, m_unk80, 0x80);
DOTD_ASSERT_OFFSET(CKProjectileTypeBallisticPFX, m_unk24, 0x24);
DOTD_ASSERT_OFFSET(CKProjectileTypeBallisticPFX, m_unk28, 0x28);
DOTD_ASSERT_OFFSET(CKProjectileTypeBallisticPFX, m_unk2c, 0x2c);
DOTD_ASSERT_OFFSET(CKProjectileTypeBallisticPFX, m_unk30, 0x30);
