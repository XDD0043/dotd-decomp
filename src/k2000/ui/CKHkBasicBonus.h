// CKHkBasicBonus.h - the k2000 bonus pickup (key 0x1c82, vtable 0xb2f338, size 0x88; library-TOC code). Original unit:
// k2000/ui/CKHkBasicBonus.cpp (0x5b48c8-0x5b6fc0). XXL2: Commun/K/KBonus/CKHkBasicBonus.h (IKHkBonus, then m_pGroup,
// m_pBonusCpnt, m_pCatcher, m_fLifeExpectancy, m_fCurrentHeight, m_fTimer, m_fMinSpawnTime, m_vSpeed,
// m_GrndDataInOut: the same fields in the same order; DotD has the bonus effect where XXL2 has m_pBonusEntityCpnt,
// and IKHkBonus's +0x24 index and a beacon accessor at the end). A member of a CKGrpBonusPool whose component is a
// CKBonusCpnt; no level file of DotD holds one (LVL000..LVL120, GAME: only CKHkS08Bonus 0x3302), so nothing replays it.
//
// The behaviour lives in IKLife's bit array (+0x0c; XXL2 SetBehaviour(EBONUS_STATICROTATION, _STATICTRANSLATION,
// _SCALE, _DYNAMICROTATION, _DYNAMICTRANSLATION)), set by the spawns from the component's flags (+0x44):
//   bit 3      the static rotation: the component's spin matrix (flag bit 2)
//   bits 4..5  the static translation (flag bits 0..1): 1 the bob (the spin matrix's height), 2 a drop to rest, 3 the
//              free fall with ground / wall bounces (InitSpeedAndLanding also sets 1 / 2 / 3)
//   bits 6..7  the scale (flag bits 3..4): 0 / 2 the frame kept at scale 1, 2 grows while caught
//   bits 8..9  the caught rotation (flag bits 7..8): 1 the spin matrix, 2 the spin matrix turned about y
//   bits 10..11 the caught translation (flag bits 5..6): 0 applied at once (then it flies), 1 the flight to the
//              catcher, 2 a rise for the component's maximum fly time, 3 applied at once and despawned
//   bit 12     spawned at a position (FastSpawn(pos)), cleared when caught
//   bit 13     attached under a moving ground's node (InitSpeedAndLanding)
// port-final F06.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/hooks/GroundContact.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/ui/IKHkBonus.h"

class IKTime;

class CKHkBasicBonus : public IKHkBonus {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0x72)
    // vt+0x08 0x009cc660 CKHkBasicBonus_IsKindOfClass: itself, IKHkBonus (0x1c42), IKHook, IKLife's keys.
    int32_t IsKindOfClass(uint32_t key) override {
        return key == 0x1c82 || key == 0x1c42 || key == 0x2 || key == 0x2fe || key == 0x3fe || key == 0xc;
    }
    // 0x005b49a8 CKHkBasicBonus_Create / 0x005b4f20 CreateArray / 0x005b4778 Delete / 0x005b48f8 DeleteArray.
    DOTD_DECLARE_FACTORIES(CKHkBasicBonus)

    // The Create's fields (OperatorNew(0x88)): IKHook's, the ground contact's defaults (ground 0, face -1, status 3,
    // sector byte 0), then the accessor's four halfwords 0xffff (stored +0x80, +0x86, +0x82, +0x84).
    CKHkBasicBonus() {
        m_aui16Accessor[0] = 0xffff;
        m_aui16Accessor[3] = 0xffff;
        m_aui16Accessor[1] = 0xffff;
        m_aui16Accessor[2] = 0xffff;
    }
    // 0x009cc6b8 _Destructor / 0x009cc798 _DeletingDestructor (inline copies): the vtables only.
    ~CKHkBasicBonus() override {}

    // vt+0x10 0x005b4f18 (Ghidra CKHkBasicBonus_ClearReferences; the Destroy slot): empty.
    void Destroy() override {}
    // vt+0x24 0x005b5028 CKHkBasicBonus_LevelReset: outside the types 4..7 registered with the saving manager, then
    // IKHook's.
    void RecursiveRegistration(int32_t type) override;
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x005b5cf0 CKHkBasicBonus_Load
    // vt+0x30 0x00019f68 IKLife_PostLoad (IKHook's).
    void Update(IKTime* frameClock) override;  // vt+0x7c 0x005b5f50 CKHkBasicBonus_Update

    // The pool's slots (IKHkBonus).
    void ReturnToPool() override;                                          // vt+0xc0 0x005b4b58 (XXL2 Despawn)
    void SpawnAt(float lifeExpectancy, const CVector3* position) override;  // vt+0xc4 0x005b6df0 (XXL2 Spawn)
    void Collect(IKSerializable* catcher, const uint16_t* accessor) override;  // vt+0xc8 0x005b56d0 (XXL2 Catched)
    // vt+0xcc 0x009cc580 CKHkBasicBonus_vfCC (XXL2 IsCatched): a catcher (+0x30).
    uint8_t IsCollected() const override { return m_pCatcher != nullptr ? 1 : 0; }
    void SpawnAtBeacon(const uint16_t* accessor) override;      // vt+0xd0 0x005b4d88 (XXL2 FastSpawn(accessor))
    void SpawnAtPosition(const CVector3* position) override;    // vt+0xd4 0x005b6c70 (XXL2 FastSpawn(pos))
    void DisableAndReleaseFx() override;                        // vt+0xd8 0x005b4c90 (XXL2 FastDespawn)
    void VfDC() override;                                       // vt+0xdc 0x005b4ae0 (XXL2 OnSectorUnload)
    // vt+0xe0 0x005b50b8 (Ghidra CKHkBasicBonus_SnapToGround_maybe; XXL2 InitSpeedAndLanding)
    void SetLaunchVelocity(const CVector3* velocity, const CGroundContactDatasInOut* contact) override;
    void VfE4(const CVector3* velocity, IKSerializable* catcher) override;  // vt+0xe4 0x005b4a50 (InitSpeedAndTarget)

    IKSerializable* m_pGroup;                   // +0x28 XXL2 m_pGroup (CKGrpBonusPool); +0x28..+0x30 one ref array
    IKSerializable* m_pBonusCpnt;               // +0x2c XXL2 m_pBonusCpnt (CKBonusCpnt)
    IKSerializable* m_pCatcher;                 // +0x30 XXL2 m_pCatcher (IKHook)
    float m_fLifeExpectancy;                    // +0x34 XXL2 (Spawn's; FastSpawn: -1)
    float m_fCurrentHeight;                     // +0x38 XXL2: the height above the ground / the bob's height
    float m_fTimer;                             // +0x3c XXL2: the age (or the time since caught)
    float m_fMinSpawnTime;                      // +0x40 XXL2: caught only when older (Spawn: 0.3, FastSpawn: -1)
    CVector3 m_vSpeed;                          // +0x44 XXL2
    CGroundContactDatasInOut m_GrndDataInOut;   // +0x50 XXL2
    IKSerializable* m_pUnk7C;                   // +0x7c runtime: the bonus's effect (the pool's AcquireBonusFx)
    uint16_t m_aui16Accessor[4];                // +0x80 the beacon accessor it was caught at (Catched)
};
static_assert(CKHkBasicBonus::kClassKey == 0x1c82, "key");
DOTD_ASSERT_SIZE(CKHkBasicBonus, 0x88);
DOTD_ASSERT_OFFSET(CKHkBasicBonus, m_pGroup, 0x28);
DOTD_ASSERT_OFFSET(CKHkBasicBonus, m_pCatcher, 0x30);
DOTD_ASSERT_OFFSET(CKHkBasicBonus, m_fLifeExpectancy, 0x34);
DOTD_ASSERT_OFFSET(CKHkBasicBonus, m_fMinSpawnTime, 0x40);
DOTD_ASSERT_OFFSET(CKHkBasicBonus, m_vSpeed, 0x44);
DOTD_ASSERT_OFFSET(CKHkBasicBonus, m_GrndDataInOut, 0x50);
DOTD_ASSERT_OFFSET(CKHkBasicBonus, m_pUnk7C, 0x7c);
DOTD_ASSERT_OFFSET(CKHkBasicBonus, m_aui16Accessor, 0x80);
