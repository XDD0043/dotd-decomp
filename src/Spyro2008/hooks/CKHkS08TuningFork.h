// CKHkS08TuningFork.h - key 0x2d42, size 0x174. Original unit: CKHkS08TuningFork.cpp. No XXL2 class. The fields
// are named by offset until their use is known.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/misc/CKHkActorBase.h"
#include "k2000/services/CTriggerStarter.h"

class IKFx;
class IKTime;

class CKHkS08TuningFork : public CKHkActorBase {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0xb5)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c5db8
        return key == 0x2d42 || key == 0xd82 || key == 0x2 || key == 0x2fe || key == 0x3fe || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKHkS08TuningFork)

    // 0x004ce218 CKHkS08TuningFork_Construct (inlined in 0x004cf0f0 CKHkS08TuningFork_Create): +0x131, +0x130 = 0xff.
    CKHkS08TuningFork() {
        m_unk131 = 0xff;
        m_unk130 = 0xff;
    }
    ~CKHkS08TuningFork() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x004cfbb8 CKHkS08TuningFork_Load
    // C2.8 port-all P16. vt+0x10 0x004ce728 CKHkS08TuningFork_Destroy: the actor base's, then the matrix +0x64 destroyed.
    void Destroy() override;
    // vt+0x40 0x004ce7e0 CKHkS08TuningFork_GetInfo: 0x9a (GetTriggerProp9A 0x4ce4e0: state 1 or 2 with +0x121 set)
    // and 0x9b (GetTriggerProp9B 0x4ce528: state 3) as bytes, folded with the actor base's answer (KStub_Return1).
    int32_t GetInfo(IKInfo* info, int32_t request) override;
    // 0x004ce4b8 _IsState1AndFlag121Set_maybe; 0x004ce660 _IsVibrating_maybe: state 1 with +0x121, or states 2 / 3.
    uint32_t IsState1AndFlag121Set() const { return m_unk130 == 1 ? (m_unk121 != 0 ? 1u : 0u) : 0u; }
    uint32_t IsVibrating() const {
        if (m_unk130 == 1) return m_unk121;
        if (m_unk130 == 3) return 1;
        return m_unk130 == 2 ? 1u : 0u;
    }
    // 0x004ce910 _SetPhaseOffsetFrom_maybe: +0x74 = `phase` - +0x70 brought into [0, 360).
    void SetPhaseOffsetFrom(float phase);
    // vt+0x68 0x004ce0c8 Stop / vt+0x70 0x004ce0a0 Pause / vt+0x78 0x004ce078 Resume / vt+0x24 0x004ce1f0
    // RecursiveRegistration: the actor base's (inherited).

    // ---- C2.8 port-final F07: the runtime ----
    // The 0x94c query (the asker's buffer: the cylinder's radius at +0x0c and height at +0x10).
    struct SizeQuery {
        uint32_t m_unk00[3];
        float m_fRadius;  // +0x0c = +0x11c
        float m_fHeight;  // +0x10 = +0x118
    };
    int32_t MessageProc(uint16_t message, void* data) override;  // vt+0x1c 0x004cdda0
    int32_t PostLoad(int32_t type) override;                     // vt+0x30 0x004cfad0
    void Start() override;                                       // vt+0x50 0x004ce0f0
    void Restart() override;                                     // vt+0x54 0x004ce310
    void Update(IKTime* clock) override;                         // vt+0x7c 0x004cf530
    void VfA0() override;                                        // vt+0xa0 0x004cf788 CKHkS08TuningFork_OnActivate
    void VfA4() override;                                        // vt+0xa4 0x004cf3c0 CKHkS08TuningFork_OnDeactivate
    // The state machine (+0x12c table of (descriptor, adjust) pairs, state +0x130, four states): a handler gets the
    // clock (null when changed outside Update), the phase (0 update, 1 enter, 2 leave) and the other state (enter:
    // the previous one, leave: the next one) and returns the next state (update) or `other`.
    using StateFn = uint8_t (CKHkS08TuningFork::*)(IKTime* clock, int32_t phase, uint8_t other);
    uint8_t CallState(uint8_t state, IKTime* clock, int32_t phase, uint8_t other);
    void ChangeState(uint8_t next, IKTime* clock);
    uint8_t State0(IKTime* clock, int32_t phase, uint8_t other);  // 0x004cda40 (in CKGrpS08TuningFork.cpp's unit)
    uint8_t State1(IKTime* clock, int32_t phase, uint8_t other);  // 0x004d28d0 CKHkS08TuningFork_VibrateState_maybe
    uint8_t State2(IKTime* clock, int32_t phase, uint8_t other);  // 0x004d17b8
    uint8_t State3(IKTime* clock, int32_t phase, uint8_t other);  // 0x004d22c8
    void CheckHitByFearScream();                       // 0x004cdaa0
    void ApplyVibrationShake(float scale, IKTime* clock);  // 0x004cdf88
    void StopShakeAndRestorePose();                    // 0x004ce540
    void SetMeshAlpha(float t);                        // 0x004ce960
    void ScaleParticles(float t);                      // 0x004cebc8
    void UpdateFadeAlpha(float t);                     // 0x004cf158
    void TriggerExplosionFx();                         // 0x004d0e30
    void StartScaledParticleFx(float t);               // 0x004d10e0
    void PlayShockWaveFx();                            // 0x004d1b40
    void PlayExplosionFx();                            // 0x004d1db0
    void PlayShockWaveFx2();                           // 0x004d2058

    IKSerializable* m_pUnk20;  // +0x20
    IKSerializable* m_pUnk24;  // +0x24
    uint8_t m_bUnk28;  // +0x28 hit by a fear scream this frame (CheckHitByFearScream)
    uint8_t m_pad29[3];
    uint32_t m_unk2C;  // +0x2c
    IKSerializable* m_pUnk30;  // +0x30
    float m_fUnk34;  // +0x34
    uint32_t m_unk38;
    float m_fUnk3C;  // +0x3c
    float m_fUnk40;  // +0x40 state 3's time
    float m_fUnk44;  // +0x44
    float m_fUnk48;  // +0x48 state 2's time
    IKSerializable* m_pUnk4C;  // +0x4c
    IKSerializable* m_pUnk50;  // +0x50
    IKSerializable* m_pUnk54;  // +0x54
    IKSerializable* m_pUnk58;  // +0x58
    IKSerializable* m_pUnk5C;  // +0x5c
    IKSerializable* m_pUnk60;  // +0x60
    CMatrix34* m_pMatrix64;  // +0x64 runtime: an RwMatrix (Destroy 0x4ce728 destroys it)
    float m_fUnk68;  // +0x68
    float m_fUnk6C;  // +0x6c
    float m_fUnk70;  // +0x70 a phase in degrees (SetPhaseOffsetFrom)
    float m_fUnk74;  // +0x74 the phase offset, in [0, 360)
    IKFx* m_pFx78;  // +0x78 the explosion of +0x7c (PlayExplosionFx; released at once)
    IKSerializable* m_pUnk7C;  // +0x7c
    IKFx* m_pFx80;  // +0x80 the explosion of +0x84 (TriggerExplosionFx; released at once)
    IKSerializable* m_pUnk84;  // +0x84
    IKFx* m_pFx88;  // +0x88 the shock wave of +0x8c (PlayShockWaveFx)
    IKSerializable* m_pUnk8C;  // +0x8c
    IKFx* m_pFx90;  // +0x90 the shock wave of +0x94 (PlayShockWaveFx2)
    IKSerializable* m_pUnk94;  // +0x94
    IKSerializable* m_pUnk98;  // +0x98
    IKFx* m_pFx9C;  // +0x9c the particle effect of +0x98 (StartScaledParticleFx; Start: 0)
    float m_fUnkA0;  // +0xa0
    float m_fUnkA4;  // +0xa4
    float m_fUnkA8;  // +0xa8
    float m_fUnkAC;  // +0xac
    float m_fUnkB0;  // +0xb0
    float m_fUnkB4;  // +0xb4
    float m_fUnkB8;  // +0xb8
    float m_fUnkBC;  // +0xbc
    float m_fUnkC0;  // +0xc0
    float m_fUnkC4;  // +0xc4
    float m_fUnkC8;  // +0xc8
    float m_fUnkCC;  // +0xcc
    float m_fUnkD0;  // +0xd0
    float m_fUnkD4;  // +0xd4
    float m_fUnkD8;  // +0xd8
    IKSerializable* m_pUnkDC;  // +0xdc
    IKSerializable* m_pUnkE0;  // +0xe0
    IKSerializable* m_pUnkE4;  // +0xe4
    float m_fUnkE8;  // +0xe8
    float m_fUnkEC;  // +0xec
    uint8_t m_unkF0;  // +0xf0
    uint8_t m_unkF1;  // +0xf1
    uint8_t m_unkF2[2];
    float m_fUnkF4;  // +0xf4
    float m_fUnkF8;  // +0xf8
    uint8_t m_unkFC;  // +0xfc
    uint8_t m_unkFD;  // +0xfd
    uint8_t m_unkFE[2];
    IKSerializable* m_pUnk100;  // +0x100
    float m_fUnk104;  // +0x104
    float m_fUnk108;  // +0x108
    float m_fUnk10C;  // +0x10c
    float m_fUnk110;  // +0x110
    IKSerializable* m_pUnk114;  // +0x114
    float m_fUnk118;  // +0x118
    float m_fUnk11C;  // +0x11c
    uint8_t m_unk120;  // +0x120
    uint8_t m_unk121;  // +0x121 the vibration flag of state 1 (IsVibrating, trigger values 0x9a)
    uint8_t m_unk122;  // +0x122 state 1: the full vibration held (+0x124 counts to +0x128)
    uint8_t m_pad123;
    float m_fUnk124;   // +0x124 state 1: the time held
    float m_fUnk128;  // +0x128
    uint32_t* m_pStateTable;  // +0x12c Start: m_aStateTable
    uint8_t m_unk130;  // +0x130 constructor 0xff
    uint8_t m_unk131;  // +0x131 constructor 0xff
    uint8_t m_pad132[2];
    uint32_t m_aStateTable[8];  // +0x134 Start: the four states' (descriptor, 0) pairs
    CTriggerStarter m_unk154;  // +0x154
    CTriggerStarter m_unk15C;  // +0x15c
    CTriggerStarter m_unk164;  // +0x164
    CTriggerStarter m_unk16C;  // +0x16c
};
DOTD_ASSERT_SIZE(CKHkS08TuningFork, 0x174);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_pUnk20, 0x20);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_pUnk24, 0x24);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_unk2C, 0x2c);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_pUnk30, 0x30);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_fUnk34, 0x34);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_fUnk3C, 0x3c);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_fUnk44, 0x44);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_pUnk4C, 0x4c);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_pUnk50, 0x50);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_pUnk54, 0x54);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_pUnk58, 0x58);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_pUnk5C, 0x5c);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_pUnk60, 0x60);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_fUnk68, 0x68);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_fUnk6C, 0x6c);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_pUnk7C, 0x7c);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_pUnk84, 0x84);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_pUnk8C, 0x8c);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_pUnk94, 0x94);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_pUnk98, 0x98);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_fUnkA0, 0xa0);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_fUnkA4, 0xa4);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_fUnkA8, 0xa8);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_fUnkAC, 0xac);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_fUnkB0, 0xb0);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_fUnkB4, 0xb4);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_fUnkB8, 0xb8);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_fUnkBC, 0xbc);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_fUnkC0, 0xc0);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_fUnkC4, 0xc4);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_fUnkC8, 0xc8);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_fUnkCC, 0xcc);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_fUnkD0, 0xd0);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_fUnkD4, 0xd4);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_fUnkD8, 0xd8);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_pUnkDC, 0xdc);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_pUnkE0, 0xe0);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_pUnkE4, 0xe4);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_fUnkE8, 0xe8);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_fUnkEC, 0xec);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_unkF0, 0xf0);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_unkF1, 0xf1);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_fUnkF4, 0xf4);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_fUnkF8, 0xf8);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_unkFC, 0xfc);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_unkFD, 0xfd);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_pUnk100, 0x100);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_fUnk104, 0x104);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_fUnk108, 0x108);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_fUnk10C, 0x10c);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_fUnk110, 0x110);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_pUnk114, 0x114);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_fUnk118, 0x118);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_fUnk11C, 0x11c);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_fUnk128, 0x128);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_unk130, 0x130);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_unk131, 0x131);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_unk154, 0x154);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_unk15C, 0x15c);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_unk164, 0x164);
DOTD_ASSERT_OFFSET(CKHkS08TuningFork, m_unk16C, 0x16c);
