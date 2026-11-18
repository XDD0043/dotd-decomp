// CKHkS08ElectricGauge.h - an electric gauge hook (key 0x2e42, vtable 0xb281d0, size 0xf4). Original unit:
// CKHkS08ElectricGauge.cpp. No XXL2 class. Field names are placeholders (C2.1 ports the constructor and
// Load only).
#pragma once
#include <cstdint>

#include "Spyro2008/ui/CKHkS08ElectricGaugeBase.h"
#include "k2000/core/Layout.h"
#include "k2000/services/CTriggerStarter.h"
#include "k2000/fx/IKFx.h"

class CKHkS08ElectricGauge : public CKHkS08ElectricGaugeBase {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0xb9)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c4ca8
        return key == 0x2e42 || key == 0x3542 || key == 0xd82 || key == 0x2 || key == 0x2fe || key == 0x3fe ||
               key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKHkS08ElectricGauge)
    // vt+0x40 0x00492f88 CKHkS08ElectricGauge_GetInfo: the trigger values 0x99 (below the bottom hot spot), 0x9a (the level ratio), 0x9c (state 0).
    int32_t GetInfo(IKInfo* info, int32_t request) override;

    // 0x00493268 CKHkS08ElectricGauge_Create (inlined constructor, the same as 0x492ad8
    // CKHkS08ElectricGauge_Construct): +0xd1 and +0xd0 = 0xff.
    CKHkS08ElectricGauge() {
        m_unkD1 = 0xff;
        m_unkD0 = 0xff;
    }
    ~CKHkS08ElectricGauge() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00493a38 CKHkS08ElectricGauge_Load
    void Start() override;  // vt+0x50 0x00493518 CKHkS08ElectricGauge_Start (C2.2)
    void Restart() override;  // vt+0x54 0x004932d0 CKHkS08ElectricGauge_Restart
    // The state engine: the state `state` of the table at +0xd4 called with the frame clock, the phase (0 tick,
    // 1 enter, 2 leave) and the other state; returns the next state.
    uint8_t CallState(uint8_t state, IKTime* clock, int32_t phase, uint8_t other);
    using StateFn = uint8_t (CKHkS08ElectricGauge::*)(IKTime* clock, int32_t phase, uint8_t other);
    // 0x00492648 KStub_ReturnArg4_492648 (descriptor 0xbc4290, state 3): the state stays as given.
    uint8_t State3Idle(IKTime*, int32_t, uint8_t other) { return other; }
    // 0x00494d28 CKHkS08ElectricGauge_State1_Moving_maybe (descriptor 0xbc4568)
    uint8_t State1Moving(IKTime* clock, int32_t phase, uint8_t other);
    // 0x00495120 CKHkS08ElectricGauge_UpdateLevel_maybe (descriptor 0xbc4570, state 0: a hero holds the gauge)
    uint8_t State0Held(IKTime* clock, int32_t phase, uint8_t other);
    // 0x00492d40 CKHkS08ElectricGauge_State2_Wait_maybe (descriptor 0xbc43a0)
    uint8_t State2Wait(IKTime* clock, int32_t phase, uint8_t other);
    // 0x00492810 CKHkS08ElectricGauge_UpdateArcEndpoints_maybe: both arc effects from the hot spot +0x2c's world position
    // (none: the hook node's LTM position) to +0x30's.
    void UpdateArcEndpoints();
    // 0x00494a50 CKHkS08ElectricGauge_TriggerTopReachedFx_maybe: the explosion +0x48 at the hot spot +0x2c.
    void TriggerTopReachedFx();
    // 0x004944e8 CKHkS08ElectricGauge_TriggerBottomReachedFx_maybe / 0x00495490 _TriggerRandomSparkFx_maybe: the explosion
    // +0x44 / +0x4c at the hot spot +0x2c, then another at +0x30.
    void TriggerBottomReachedFx();
    void TriggerRandomSparkFx();
    void Update(IKTime* clock) override;  // vt+0x7c 0x00495ab0 CKHkS08ElectricGauge_Update
    int32_t PostLoad(int32_t type) override;  // vt+0x30 0x004929c0 CKHkS08ElectricGauge_PostLoad
    void VfA0() override;                 // vt+0xa0 0x00492c70 CKHkS08ElectricGauge_OnActivate
    // vt+0xa4 0x00493458 CKHkS08ElectricGauge_OnDeactivate: CKHkActorBase's, the two arc effects released (vt+0x58).
    // (vt+0x68 0x00492998 _Stop, vt+0x10 0x00492db0 _Destroy and 0x00492e78 _Destructor: the base's, all empty.)
    void VfA4() override {
        CKHkActorBase::VfA4();  // 0x003f7370
        for (int32_t i = 0; i < 2; ++i) {
            if (m_unk3c[i] != nullptr) {
                static_cast<IKFx*>(m_unk3c[i])->StopAndRelease(this);
                m_unk3c[i] = nullptr;
            }
        }
    }
    // 0x004930e8 CKHkS08ElectricGauge_GetLevelRatioSq_maybe: the squared distance from the bottom hot spot (+0x24) to
    // the gauge node's position (+0x20, its LTM) over the squared distance between the two hot spots (+0x24, +0x28).
    float GetLevelRatioSq() const;
    // vt+0xf4 0x00493868 CKHkS08ElectricGauge_OnHeroEnter_maybe: none held (+0x70): the state engine switched to state 0
    // (unless in state 2), +0x78 cleared, `hero` held, the starter +0xbc signalled: 1; else 0.
    uint8_t OnHeroEnter(IKSerializable* hero);
    // vt+0xf8 0x004936b0 CKHkS08ElectricGauge_OnHeroLeave_maybe: `hero` held: the state engine switched to state 1
    // (unless in state 2), +0x78 and the holder cleared, the starter +0xac signalled.
    void OnHeroLeave(IKSerializable* hero);
    // vt+0xfc 0x00492658 CKHkS08ElectricGauge_vfFC: +0x78 = `weight` (the hero is not read).
    void SetGrabWeight(float weight, IKSerializable* /*hero*/) { m_unk78[0] = weight; }
    // vt+0xf0 0x00492650 CKHkS08ElectricGauge_vfF0: li r3, 1 (the hero is not read): the gauge accepts any hero as an
    // ability target (CKHkS08Hero_FindAbilityMecaTarget_maybe). The base's slot (vtable 0xb2a458) is pure virtual.
    uint8_t AcceptsAbilityTarget(IKSerializable* /*hero*/) const { return 1; }
    // vt+0x104 0x00492660 CKHkS08ElectricGauge_vf104: the reference +0x30 (LVL010: a CSGHotSpot).
    IKSerializable* GetGrabHotSpot() const { return m_apUnk24[3]; }
    // vt+0x100 0x00492ea8 CKHkS08ElectricGauge_vf100 (CKHkS08ElectricGauge.cpp): the grab hot spot's (+0x30) world position
    // (the node +0x20's world matrix updated first, vt+0x50), the null vector without one. The base's slot is pure; no
    // ported code calls it yet.
    CVector3 GetGrabHotSpotPosition();

    IKSerializable* m_unk20;          // +0x20 reference (LVL010: a CNode)
    IKSerializable* m_apUnk24[6];     // +0x24..+0x3b references (separate reads; LVL010: CSGHotSpots, then two of key 0x174c)
    IKSerializable* m_unk3c[2];       // +0x3c runtime: the two arc effects (IKFx) of the data +0x34 / +0x38
    IKSerializable* m_apUnk44[3];     // +0x44..+0x4f references (LVL010: CKExplosionFxData)
    float m_unk50;                    // +0x50
    float m_unk54;                    // +0x54 runtime: the spark timer
    float m_unk58;                    // +0x58
    float m_unk5c;                    // +0x5c runtime (Start: a random value around m_unk50)
    float m_fWaitTime;                // +0x60 runtime: the time in state 2 (State2_Wait; its enter clears it)
    float m_unk64;                    // +0x64: the time state 2 waits
    IKSerializable* m_unk68;          // +0x68 reference (read last)
    IKSerializable* m_unk6c;          // +0x6c reference
    IKSerializable* m_unk70;          // +0x70 runtime: the hero holding the gauge (OnHeroEnter; PostLoad 0x4929c0 clears it for the level type)
    float m_unk74;                    // +0x74
    float m_unk78[10];                // +0x78..+0x9f runtime: +0x7c position, +0x88 velocity, +0x94 acceleration
    float m_unkA0;                    // +0xa0
    float m_unkA4;                    // +0xa4
    float m_unkA8;                    // +0xa8
    CTriggerStarter m_unkAC;          // +0xac
    CTriggerStarter m_unkB4;          // +0xb4
    CTriggerStarter m_unkBC;          // +0xbc
    CTriggerStarter m_unkC4;          // +0xc4
    void* m_pStateTable;              // +0xcc Start: the state table at +0xd4 (the state engine)
    uint8_t m_unkD0;                  // +0xd0 constructor 0xff
    uint8_t m_unkD1;                  // +0xd1 constructor 0xff
    uint8_t m_padD2[2];
    // +0xd4 the state table: four {descriptor, this adjustment} pairs of PS3 pointers to member functions
    // (Start; the descriptors 0xbc4570 / 0xbc4568 / 0xbc43a0 / 0xbc4290 are the OPDs of the states 0 to 3).
    uint32_t m_unkD4[8];
};
DOTD_ASSERT_SIZE(CKHkS08ElectricGauge, 0xf4);
DOTD_ASSERT_OFFSET(CKHkS08ElectricGauge, m_unk20, 0x20);
DOTD_ASSERT_OFFSET(CKHkS08ElectricGauge, m_apUnk24, 0x24);
DOTD_ASSERT_OFFSET(CKHkS08ElectricGauge, m_apUnk44, 0x44);
DOTD_ASSERT_OFFSET(CKHkS08ElectricGauge, m_unk50, 0x50);
DOTD_ASSERT_OFFSET(CKHkS08ElectricGauge, m_unk58, 0x58);
DOTD_ASSERT_OFFSET(CKHkS08ElectricGauge, m_unk64, 0x64);
DOTD_ASSERT_OFFSET(CKHkS08ElectricGauge, m_unk68, 0x68);
DOTD_ASSERT_OFFSET(CKHkS08ElectricGauge, m_unk6c, 0x6c);
DOTD_ASSERT_OFFSET(CKHkS08ElectricGauge, m_unk74, 0x74);
DOTD_ASSERT_OFFSET(CKHkS08ElectricGauge, m_unkA0, 0xa0);
DOTD_ASSERT_OFFSET(CKHkS08ElectricGauge, m_unkAC, 0xac);
DOTD_ASSERT_OFFSET(CKHkS08ElectricGauge, m_unkC4, 0xc4);
DOTD_ASSERT_OFFSET(CKHkS08ElectricGauge, m_unkD0, 0xd0);
