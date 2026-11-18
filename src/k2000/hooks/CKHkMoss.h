// CKHkMoss.h - a patch of moss that puffs particles where a hero walks on it or a body touches its volume (key
// 0x2282, vtable 0xb25f00, size 0x94). Original unit: CKHkMoss.cpp (0x41be10-0x41e248). No XXL2 class of this key; the
// layout comes from the Load (level type 0 only) and the users in the unit. No level of the game holds one (C2.8
// port-rest R04: ported from the disassembly, nothing replays it).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/misc/CKHkActorBase.h"
#include "k2000/util/TVector.h"

class IKTime;

class CKHkMoss : public CKHkActorBase {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0x8a)
    // vt+0x08 0x009c2f88 CKHkMoss_IsKindOfClass [inline]
    int32_t IsKindOfClass(uint32_t key) override {
        return key == 0x2282 || key == 0xd82 || key == 0x2 || key == 0x2fe || key == 0x3fe || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKHkMoss)

    // 0x0041d810 CKHkMoss_Create: the actor base's defaults, the particle node list empty with capacity 1.
    CKHkMoss() {
        m_vParticleNodes.m_pBlock = nullptr;
        m_vParticleNodes.m_ui32NbElt = 1;
        m_vParticleNodes.m_ui32NbUsedElt = 0;
    }
    // 0x0041c460 CKHkMoss_Destructor (0x41c1b0 / 0x41c3e8 the same): the list's block freed (Mem_FreeAligned16) and
    // the list cleared, then the actor base's.
    ~CKHkMoss() override;

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0041d960 CKHkMoss_Load
    // vt+0x40 0x0041bf20 CKHkMoss_GetInfo: the actor base's answer (KStub_Return1 0x3f7140) merged with none.
    int32_t GetInfo(struct IKInfo* info, int32_t request) override;
    // vt+0x1c 0x0041c220 CKHkMoss_MessageProc: the actor messages, then the hero's hazard query 0xc32 (the moss's knock
    // values +0x64..+0x6c, the node's position, the damage +0x60 for the player's hero, 0 for the others).
    int32_t MessageProc(uint16_t message, void* data) override;
    // vt+0xa0 0x0041ce58 CKHkMoss_OnActivate: the actor base's, SetActive(vt+0xf0), the timer +0x90 = 0.
    void VfA0() override;
    // vt+0xa4 0x0041ce20 CKHkMoss_OnDeactivate: the actor base's, SetActive(0).
    void VfA4() override;
    void Update(IKTime* frameClock) override;  // vt+0x7c 0x0041cec0 CKHkMoss_Update
    // vt+0xf0 0x009c2ff0 CKHkMoss_vfF0 [inline]: 1 (the moss wants to be active).
    virtual uint8_t VfF0() { return 1; }

    // 0x0041c4d0 CKHkMoss_SetActive: flag bit 3 = `active`, the node hidden without; the particle nodes (+0x28, +0x38)
    // emitting or not; the fog box (+0x3c) gets a box for the moss at the node's LTM, or loses it (sound 0 stopped);
    // the volume (+0x24) enabled under the node (its extents +0x54, its radius their length, at +0x48) or disabled under
    // the dynamic scene root; with +0x88 the path-finding box around the node (the half lengths +0x88 / +0x8c along the
    // LTM right / at rows) blocked or freed.
    void SetActive(uint8_t active);
    // The particles at `position` (the node's space): the node +0x34 moved there and emitting (bit 9 too without a
    // period +0x44, else the timer restarted when it ran out), then one of sounds 1 / 2 (a rand draw) unless one plays.
    void Puff(const float* position);

    IKSerializable* m_pGround;                         // +0x20 the moss's ground (a hero on it puffs)
    IKSerializable* m_pVolume;                         // +0x24 an IKBoundingBox (bodies touching it puff)
    TVector<IKSerializable*, 1> m_vParticleNodes;      // +0x28 CParticlesNodeFx, emitting while active
    IKSerializable* m_pPuffParticles;                  // +0x34 a CParticlesNodeFx moved to each puff
    IKSerializable* m_pAmbientParticles;               // +0x38 a CParticlesNodeFx sized by the focused hero's distance
    IKSerializable* m_pFogBox;                         // +0x3c a CFogBoxNodeFx
    IKSerializable* m_pSounds;                         // +0x40 a CKSoundDictionaryID: 0 ambient, 1 / 2 puffs
    float m_fPuffPeriod;                               // +0x44 the puff particles' emitting time (0: not timed)
    CVector3 m_vVolumePosition;                        // +0x48 one 12-byte read
    CVector3 m_vVolumeExtent;                          // +0x54 one 12-byte read
    uint8_t m_ui8Damage;                               // +0x60 the hazard query's damage for the player's hero
    uint8_t m_pad61[3];
    float m_afKnock[3];                                // +0x64 the hazard query's words +0x08..+0x10
    float m_fNearDistance;                             // +0x70 the ambient size's distances (near, far)
    float m_fFarDistance;                              // +0x74
    float m_fNearSizeX;                                // +0x78 the ambient particle size (x, y) near and far
    float m_fFarSizeX;                                 // +0x7c
    float m_fNearSizeY;                                // +0x80
    float m_fFarSizeY;                                 // +0x84
    float m_fNavHalfRight;                             // +0x88 (0: no path-finding box)
    float m_fNavHalfAt;                                // +0x8c
    float m_fPuffTimer;                                // +0x90 runtime: the puff particles' time left
};
DOTD_ASSERT_SIZE(CKHkMoss, 0x94);
DOTD_ASSERT_OFFSET(CKHkMoss, m_pGround, 0x20);
DOTD_ASSERT_OFFSET(CKHkMoss, m_vParticleNodes, 0x28);
DOTD_ASSERT_OFFSET(CKHkMoss, m_pPuffParticles, 0x34);
DOTD_ASSERT_OFFSET(CKHkMoss, m_pSounds, 0x40);
DOTD_ASSERT_OFFSET(CKHkMoss, m_vVolumePosition, 0x48);
DOTD_ASSERT_OFFSET(CKHkMoss, m_vVolumeExtent, 0x54);
DOTD_ASSERT_OFFSET(CKHkMoss, m_ui8Damage, 0x60);
DOTD_ASSERT_OFFSET(CKHkMoss, m_afKnock, 0x64);
DOTD_ASSERT_OFFSET(CKHkMoss, m_fNearDistance, 0x70);
DOTD_ASSERT_OFFSET(CKHkMoss, m_fNavHalfRight, 0x88);
DOTD_ASSERT_OFFSET(CKHkMoss, m_fPuffTimer, 0x90);
