// CKGrpBonusPool.h - a pool of bonus pickups (key 0xf44, size 0x6c). Original units: CKGrpBonusPool.cpp
// and CKGrpBonusPool_2.cpp (TOC2; the Load 0x5b3240 is in the second). XXL2: CKGrpBonusPool
// (IKGroup<IKHkBonus>): its Load reads the same fields in the same order (the type, beacon id, maximum,
// far distance, the four list heads / component as one reference array, the two particle nodes); DotD adds
// a byte after the far distance and a reference, a word and a byte at the end.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/groups/IKBaseGroup.h"
#include "k2000/hooks/IKHook.h"

class CKGrpBonusPool : public IKGroup<IKHook> {
public:
    DOTD_CLASS_KEY(kCategoryGroup, 0x3d)
    DOTD_DECLARE_FACTORIES(CKGrpBonusPool)

    CKGrpBonusPool() {}  // 0x005b1788 CKGrpBonusPool_Create: the bases only

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x005b3240 CKGrpBonusPool_Load
    // vt+0xec 0x005b1f10 CKGrpBonusPool_ResetPool_maybe (not in the base IKBaseGroup's slots yet): the used and
    // beaconed lists emptied, every pool hook chained into the free list (its +0x20 = the next hook, its
    // +0x24 = its index), the pool's bits 7 and 8 cleared.
    virtual void ResetPool();

    uint32_t m_ui32BonusType;                     // +0x2c
    uint32_t m_ui32BonusBeaconID;                 // +0x30
    uint32_t m_ui32MaxSimultaneousBonusOnBeacon;  // +0x34
    float m_fFarDistance;                         // +0x38
    uint8_t m_unk3c;                              // +0x3c (DotD only)
    uint8_t m_pad3d[3];
    IKSerializable* m_pFirstUsed;                 // +0x40 XXL2 IKHkBonus*; the four words are one reference array
    IKSerializable* m_pFirstBeaconed;             // +0x44
    IKSerializable* m_pFirstFree;                 // +0x48
    IKSerializable* m_pBonusCpnt;                 // +0x4c XXL2 IKBonusCpnt*
    IKSerializable* m_pStaticParticles;           // +0x50 XXL2 CParticlesNodeFx*
    IKSerializable* m_pCatchedParticles;          // +0x54 XXL2 CParticlesNodeFx*
    IKSerializable* m_pUnk58;                     // +0x58 reference (DotD only)
    uint32_t m_unk5c;                             // +0x5c byte-swapped word (DotD only)
    uint8_t m_unk60;                              // +0x60 (DotD only)
    uint8_t m_pad61[3];
    uint32_t m_unk64;                             // +0x64..+0x6b not set by the constructor or the Load
    uint32_t m_unk68;
};
DOTD_ASSERT_SIZE(CKGrpBonusPool, 0x6c);
DOTD_ASSERT_OFFSET(CKGrpBonusPool, m_ui32BonusType, 0x2c);
DOTD_ASSERT_OFFSET(CKGrpBonusPool, m_unk3c, 0x3c);
DOTD_ASSERT_OFFSET(CKGrpBonusPool, m_pFirstUsed, 0x40);
DOTD_ASSERT_OFFSET(CKGrpBonusPool, m_pStaticParticles, 0x50);
DOTD_ASSERT_OFFSET(CKGrpBonusPool, m_unk5c, 0x5c);
DOTD_ASSERT_OFFSET(CKGrpBonusPool, m_unk60, 0x60);
