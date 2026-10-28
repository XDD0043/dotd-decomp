// IKProjectileType.h - the projectile types' unregistered abstract base (key 0x130c; XXL2:
// K/KServices/KServiceProjectiles/IKProjectileType.h, the same members in the same order). Its Load
// (0x1f3ca0 CKProjectileType_LoadBase, reached through 0x990090 TocBridge_CKProjectileType_LoadBase) lives
// in CKSrvProjectiles.cpp. Classes: CKProjectileTypeBallisticPFX (0x140c), CKProjectileTypeScrap (0x134c).
// Minimal for C2.1: constructor and Load.
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"
#include "k2000/math/CMatrix34.h"

class IKProjectileType : public IKSerializable {
public:
    struct CGroundContactDatasIn {  // XXL2 names (16 bytes, as in XXL2)
        float m_fDeltaMax;                // +0x00 the derived Loads set 1.0
        float m_fObjectHeight;            // +0x04 the derived Loads set 2.0
        uint32_t m_MasksOfGrdForTest[2];  // +0x08 constructor 1, 8; the Load 1, 0
    };
    struct CGroundContactDatasInOut {  // XXL2 names (the derived Loads set the projectiles' copies)
        IKSerializable* m_pGround;      // +0x00 CGround*; the Loads set 0
        int32_t m_i32FaceIndex;         // +0x04 -1
        CVector3 m_Normal;              // +0x08
        uint32_t m_eContactStatus;      // +0x14 3
        CVector3 m_ProjectionOnGround;  // +0x18
        float m_fdH;                    // +0x24
        uint8_t m_ui8SectorNumber;      // +0x28 0
        uint8_t m_pad29[3];
    };

    // The constructor inlined in CKProjectileTypeBallisticPFX_Create (0x5868e8) / CKProjectileTypeScrap_Create
    // (0x593078): this vtable, +0x18 = 8, +0x14 = 1.
    IKProjectileType() {
        m_GrdContDatasIn.m_MasksOfGrdForTest[1] = 8;
        m_GrdContDatasIn.m_MasksOfGrdForTest[0] = 1;
    }
    // vt+0x2c 0x001f3ca0 CKProjectileType_LoadBase
    int32_t Load(IKFile* file, int32_t type) override;

    // The projectile types' runtime slots (XXL2 CKProjectileTypeBallisticPFX: UpdateProjectilePosition,
    // UpdateProjectileCollision, IsProjectileNeedToBeKilled, KillProjectile, ApplyTransform, FireFrom, ...;
    // DotD has one more slot in front of KillProjectile). The classes override them; the code is not ported.
    virtual void Vf50() {}  // vt+0x50  STUB(C2.2)
    virtual void Vf54() {}  // vt+0x54  STUB(C2.2)
    virtual void Vf58() {}  // vt+0x58  STUB(C2.2)
    virtual void Vf5C() {}  // vt+0x5c  STUB(C2.2)
    // vt+0x60: CKProjectileTypeBallisticPFX 0x5886d0 (XXL2 KillProjectile(index)): the projectile of that index
    // killed (the active ones are compacted to the front, so index 0 kills them one by one).
    // STUB(C2.2): the projectile classes' runtime (hooks family). Nothing fires before gameplay, so no pool
    // has an active projectile (m_ui8NbOfActiveProjectiles is 0).
    virtual void KillProjectile(uint8_t /*index*/) {}

    void** m_apProjectileList;                // +0x04 the projectiles (pointers into +0x08), made by the derived Load
    void* m_aProjectiles;                     // +0x08 the derived class's projectile records (Mem_AllocAligned16)
    CGroundContactDatasIn m_GrdContDatasIn;   // +0x0c
    uint32_t m_baOptions;                     // +0x1c XXL2 CBitArray (bit 0x80: CKProjectileTypeBallisticPFX_PostLoad)
    uint8_t m_ui8MaxProjectiles;              // +0x20 the record count
    uint8_t m_ui8NbOfActiveProjectiles;       // +0x21 the Load sets 0
    // +0x22..+0x23: the PS3 (Itanium C++ ABI) puts a subclass's first member in this tail padding
    // (CKProjectileTypeBallisticPFX's byte at +0x22); the host compilers never do, so it is declared here.
    uint8_t m_aSubclassTail[2];
};
DOTD_ASSERT_SIZE(IKProjectileType, 0x24);
DOTD_ASSERT_SIZE(IKProjectileType::CGroundContactDatasInOut, 0x2c);
DOTD_ASSERT_OFFSET(IKProjectileType, m_apProjectileList, 0x04);
DOTD_ASSERT_OFFSET(IKProjectileType, m_aProjectiles, 0x08);
DOTD_ASSERT_OFFSET(IKProjectileType, m_GrdContDatasIn, 0x0c);
DOTD_ASSERT_OFFSET(IKProjectileType, m_baOptions, 0x1c);
DOTD_ASSERT_OFFSET(IKProjectileType, m_ui8MaxProjectiles, 0x20);
DOTD_ASSERT_OFFSET(IKProjectileType, m_ui8NbOfActiveProjectiles, 0x21);
DOTD_ASSERT_OFFSET(IKProjectileType, m_aSubclassTail, 0x22);
