// CKProjectileTypeScrap.h - a debris projectile pool (key 0x134c, vtable 0xb2e3c8, size 0x30). Original
// unit: CKProjectileTypeScrap.cpp (0x5929d8-0x596240). Base: IKProjectileType (its Load is called first).
// XXL2 has a class of this name, but DotD loads different data (a word and references, no floats), so the
// members keep placeholder names.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/services/IKProjectileType.h"

class CSGLeaf;

class CKProjectileTypeScrap : public IKProjectileType {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x4d)
    DOTD_DECLARE_FACTORIES(CKProjectileTypeScrap)

    // One projectile (0x90 bytes, m_ui8MaxProjectiles of them; the Load sets what is listed).
    struct Projectile {
        uint32_t m_ui32Index;                           // +0x00 its index
        uint32_t m_unk04;                               // +0x04 0
        uint32_t m_unk08;                               // +0x08 not set by the Load
        CSGLeaf* m_pNode;                               // +0x0c a reference (file); the Load sets its flag 0x4 (hidden)
        IKSerializable* m_unk10;                        // +0x10 a reference (file)
        CVector3 m_unk14;                               // +0x14 (0, 0, 0)
        CVector3 m_unk20;                               // +0x20 (0, 0, 0)
        CVector3 m_unk2c;                               // +0x2c (0, 0, 0)
        uint32_t m_unk38;                               // +0x38 0
        CVector3 m_unk3c;                               // +0x3c (0, 0, 0)
        uint32_t m_unk48;                               // +0x48 0
        float m_unk4c;                                  // +0x4c 1.0
        uint32_t m_unk50;                               // +0x50 0
        float m_unk54;                                  // +0x54 1.0
        uint8_t m_unk58;                                // +0x58 0
        uint8_t m_pad59[3];
        CGroundContactDatasInOut m_GrdContDatasInOut;   // +0x5c _maybe (the constructor values of XXL2's type)
        uint32_t m_unk88;                               // +0x88 0
        uint32_t m_unk8c;                               // +0x8c 0
    };

    // The constructor inlined in 0x00593078 CKProjectileTypeScrap_Create: IKProjectileType's, then the
    // vtable only.
    CKProjectileTypeScrap() {}
    ~CKProjectileTypeScrap() override {}
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00595e28 CKProjectileTypeScrap_Load

    uint32_t m_unk24;         // +0x24 (samples: 0)
    IKSerializable* m_unk28;  // +0x28 a reference
    IKSerializable* m_unk2c;  // +0x2c a reference
};
DOTD_ASSERT_SIZE(CKProjectileTypeScrap, 0x30);
DOTD_ASSERT_SIZE(CKProjectileTypeScrap::Projectile, 0x90);
DOTD_ASSERT_OFFSET(CKProjectileTypeScrap::Projectile, m_pNode, 0x0c);
DOTD_ASSERT_OFFSET(CKProjectileTypeScrap::Projectile, m_unk10, 0x10);
DOTD_ASSERT_OFFSET(CKProjectileTypeScrap::Projectile, m_unk58, 0x58);
DOTD_ASSERT_OFFSET(CKProjectileTypeScrap::Projectile, m_GrdContDatasInOut, 0x5c);
DOTD_ASSERT_OFFSET(CKProjectileTypeScrap::Projectile, m_unk8c, 0x8c);
DOTD_ASSERT_OFFSET(CKProjectileTypeScrap, m_unk24, 0x24);
DOTD_ASSERT_OFFSET(CKProjectileTypeScrap, m_unk28, 0x28);
DOTD_ASSERT_OFFSET(CKProjectileTypeScrap, m_unk2c, 0x2c);
