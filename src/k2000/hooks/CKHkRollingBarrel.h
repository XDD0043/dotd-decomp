// CKHkRollingBarrel.h - barrels rolled down a flagged path (key 0x4002, vtable 0xb264f8, size 0xa0). Original unit:
// CKHkRollingBarrel.cpp (0x43ef98-0x441860). No XXL2 class of this key; names ours. No game file holds one
// (work/level-class-keys.json); C2.8 port-final F02 ported it from the code.
//
// While running (bit 3; messages 0x996 / 0x997, the game state 6) a timer loops over a period (+0x70) and every spawn
// time (+0x74) it passes takes a barrel from the pool (+0x68, a CKRollingBarrelPool) and starts it at the path's start
// (+0x6c, a CKFlaggedPath). The barrels speed up / slow down with the path's slope (or, bit 5, by the path's segment
// values in 0.01 s steps), turn their heading towards the path's, roll, stick to the ground with a blob shadow, puff an
// impact effect when they land, break (an explosion) on a contact or at the path's end, which also fires the end
// trigger (+0x98).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/memory/CKRollingBarrelPool.h"
#include "k2000/misc/CKHkActorBase.h"
#include "k2000/services/CTriggerStarter.h"
#include "k2000/util/TVector.h"

class CKFlaggedPath;

class CKHkRollingBarrel : public CKHkActorBase {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0x100)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c3448
        return key == 0x4002 || key == 0xd82 || key == 0x2 || key == 0x2fe || key == 0x3fe || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKHkRollingBarrel)

    // 0x0043fc70 CKHkRollingBarrel_Create (the dead 0x43f800 / 0x43f860 _Construct copies): the actor base, the vtable,
    // the spawn time vector null, capacity 1, 0 used. Out of line (LNK1163).
    CKHkRollingBarrel();
    // 0x0043fb18 CKHkRollingBarrel_Destructor (= 0x43f790 _BaseDestructor; 0x43faa0 _DeletingDestructor + delete): the
    // spawn times' block freed, the vector's used count and block cleared, then the actor base's.
    ~CKHkRollingBarrel() override;

    int32_t Load(IKFile* file, int32_t type) override;              // vt+0x2c 0x00441438 CKHkRollingBarrel_Load
    void RecursiveRegistration(int32_t type) override;              // vt+0x24 0x0043f6e8
    int32_t MessageProc(uint16_t message, void* data) override;     // vt+0x1c 0x004406b0
    void SetDefaultState(int32_t flag) override;                    // vt+0x38 0x0043fa40
    int32_t SetGameState(const SApplyGameState* state) override;    // vt+0x3c 0x0043f968
    int32_t GetInfo(IKInfo* info, int32_t request) override;        // vt+0x40 0x0043f5a0
    void Start() override;                                          // vt+0x50 0x0043f678
    void Restart() override;                                        // vt+0x54 0x0043fe68
    void Stop() override;                                           // vt+0x68 0x0043fea8
    void Update(IKTime* clock) override;                            // vt+0x7c 0x00441218
    void VfA0() override;                                           // vt+0xa0 0x0043f5f0 CKHkRollingBarrel_OnActivate
    void VfA4() override;                                           // vt+0xa4 0x0043fe30 CKHkRollingBarrel_OnDeactivate
    // vt+0x10 0x43f768 Destroy, vt+0x30 PostLoad 0x3f6e70, vt+0x70 / +0x78 0x43f650 / 0x43f628 Pause / Resume: the actor
    // base's (inherited). vt+0xb4 0x43eeb8 CKHkRollingBarrel_vfB4 (KGLObjectAttached): an empty blr, IKHook's (inherited).
    // vt+0xd8 0x9c34c0 returns 0 and vt+0xf0 0x9c34b0 (a slot past the actor base's) stores 0 through its third
    // argument and returns 0: the port models neither slot (no caller is known).

    // 0x0043f298 CKHkRollingBarrel_TriggerBreakExplosion_maybe: a free explosion of the pool's FX data (+0x1c; the
    // service's AcquireFx, inlined) goes off at `point` raised by the pool's +0x48, with the hook as damage owner
    // (category 1, flags 0x244).
    void TriggerBreakExplosion(const CVector3* point);
    // 0x0043fce0 CKHkRollingBarrel_DeactivateAllBarrels_maybe: every rolling barrel hidden, its volume off, its shadow
    // gone, its loop sound stopped and given back to the pool; none left.
    void DeactivateAllBarrels();
    // 0x0043fee0 CKHkRollingBarrel_DespawnBarrel_maybe: `barrel` out of the rolling list, hidden, volume off, shadow
    // gone, broken (an explosion at its path point, with the pool's +0x6e), loop sound stopped, back to the pool.
    void DespawnBarrel(CKRollingBarrelPool::Barrel* barrel);
    // 0x004400b8 CKHkRollingBarrel_DespawnBarrelsOnContact_maybe: (pool +0x6e) a barrel whose volume touches a volume
    // with property bit 0 breaks.
    void DespawnBarrelsOnContact();
    // 0x00440270 CKHkRollingBarrel_SpawnBarrel_maybe: a pool barrel (none free: nothing) shown at the path's start with
    // a random roll, its volume on, its shadow, its loop sound (pool +0x72).
    void SpawnBarrel();
    // 0x004408a0 CKHkRollingBarrel_UpdateBarrelGroundAndShadow_maybe: the ground under the barrel; its shadow follows
    // it (registered when it finds ground, dropped over a ground the game manager marks or without ground).
    void UpdateBarrelGroundAndShadow(CKRollingBarrelPool::Barrel* barrel);
    // 0x00440b70 CKHkRollingBarrel_UpdateBarrels_maybe: every rolling barrel's speed, distance, position, landing
    // impact, heading, roll and ground.
    void UpdateBarrels(IKTime* clock);

    CKRollingBarrelPool::Barrel* m_apBarrels[16];  // +0x20 the rolling barrels (BUG(original): SpawnBarrel has no bound)
    uint8_t m_ui8NbBarrel;                         // +0x60 how many roll
    uint8_t m_pad61[3];
    IKSerializable* m_pUnk64;                      // +0x64 a reference (level data; only RecursiveRegistration uses it)
    CKRollingBarrelPool* m_pPool;                  // +0x68 a reference: the barrels
    CKFlaggedPath* m_pPath;                        // +0x6c a reference: the path they roll down
    float m_fPeriod;                               // +0x70 the spawn timeline's length
    TVector<float, 1> m_vSpawnTimes;               // +0x74 the spawn times in the timeline
    float m_fTimer;                                // +0x80 the timeline's time
    float m_fMinSpeed;                             // +0x84 the speed range along the path
    float m_fMaxSpeed;                             // +0x88
    float m_fBrake;                                // +0x8c the speed lost per second (not falling)
    float m_fAccel;                                // +0x90 the speed gained per second (falling; bit 5: x segment value)
    float m_fTickRest;                             // +0x94 bit 5: the time left of the 0.01 s steps
    CTriggerStarter m_tsEndStarter;                // +0x98 fired when a barrel passes the path's end (bit 5)
};
static_assert(CKHkRollingBarrel::kClassKey == 0x4002, "key");
DOTD_ASSERT_SIZE(CKHkRollingBarrel, 0xa0);
DOTD_ASSERT_OFFSET(CKHkRollingBarrel, m_ui8NbBarrel, 0x60);
DOTD_ASSERT_OFFSET(CKHkRollingBarrel, m_pPool, 0x68);
DOTD_ASSERT_OFFSET(CKHkRollingBarrel, m_vSpawnTimes, 0x74);
DOTD_ASSERT_OFFSET(CKHkRollingBarrel, m_fTimer, 0x80);
DOTD_ASSERT_OFFSET(CKHkRollingBarrel, m_fTickRest, 0x94);
DOTD_ASSERT_OFFSET(CKHkRollingBarrel, m_tsEndStarter, 0x98);
