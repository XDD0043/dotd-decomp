// CKHkS08FlamingTorch.h - a flaming torch hook (key 0x2e82, size 0x10c). Original unit:
// CKHkS08FlamingTorch.cpp. No XXL2 class. The fields are named by offset until their use is known.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/misc/CKHkActorBase.h"
#include "k2000/services/CTriggerStarter.h"

class IKFx;
class IKTime;

class CKHkS08FlamingTorch : public CKHkActorBase {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0xba)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c4d18
        return key == 0x2e82 || key == 0xd82 || key == 0x2 || key == 0x2fe || key == 0x3fe || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKHkS08FlamingTorch)

    // A 0x14-byte entry of the +0x5c table (all 1.0f in the LVL040 samples).
    struct SEntry {
        float m_fUnk0;  // +0x00 read third
        float m_fUnk4;  // +0x04 read fourth
        float m_fUnk8;  // +0x08 read first
        float m_fUnkC;  // +0x0c read second
        float m_fUnk10; // +0x10 read last
    };

    // 0x00496c10 CKHkS08FlamingTorch_Construct (inlined in 0x00497558 CKHkS08FlamingTorch_Create): +0x2c = 0,
    // +0xe9/+0xe8 = 0xff.
    CKHkS08FlamingTorch() {
        m_unk2C = 0;
        m_unkE9 = 0xff;
        m_unkE8 = 0xff;
    }
    // 0x00496e40 CKHkS08FlamingTorch_Destructor (0x00496db8 the deleting one): the contacts (+0x2c) back to their pool
    // (ContactHistory_FreeNode), the list cleared, then CKHkActorBase's.
    ~CKHkS08FlamingTorch() override;

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00498f90 CKHkS08FlamingTorch_Load
    // vt+0x38 0x00496a98 CKHkS08FlamingTorch_SetDefaultState: the actor base's (empty), then +0xdc = +0xdd, +0xdb = !+0xd8.
    void SetDefaultState(int32_t flag) override;
    // vt+0x40 0x00496ae0 CKHkS08FlamingTorch_GetInfo: value 0x98, IsLit (0x00496fb8, type 0); the actor base answers 1.
    int32_t GetInfo(IKInfo* info, int32_t request) override;
    // vt+0xc8 0x004962a8 CKHkS08FlamingTorch_vfC8: the state preset: on, +0xdc = +0xdf and +0xdb = !+0xda; off, +0xdc =
    // +0xde and +0xdb = !+0xd9.
    void ApplyStatePreset(int32_t state) override;
    // 0x00496fb8 CKHkS08FlamingTorch_IsLit_maybe: the state (+0xe8) is 2 or 3.
    uint8_t IsLit() const { return static_cast<uint8_t>(m_unkE8 == 3 || m_unkE8 == 2); }
    // Resume / Pause / Stop / Destroy / RecursiveRegistration (0x496a20 .. 0x496f90, 0x496be8) only call CKHkActorBase's:
    // inherited.

    // ---- C2.8 port-last Z5: the runtime ----
    int32_t MessageProc(uint16_t message, void* data) override;  // vt+0x1c 0x0049a4b8
    int32_t PostLoad(int32_t type) override;                     // vt+0x30 0x00499bc0
    void Start() override;                                       // vt+0x50 0x00499db0
    void Restart() override;                                     // vt+0x54 0x0049ad80
    void Update(IKTime* clock) override;                         // vt+0x7c 0x0049a008
    void VfA0() override;                                        // vt+0xa0 0x004975c8 CKHkS08FlamingTorch_OnActivate
    void VfA4() override;                                        // vt+0xa4 0x004977a0 CKHkS08FlamingTorch_OnDeactivate
    void SetEnabled(int32_t enabled) override;                   // vt+0xcc 0x0049a240 CKHkS08FlamingTorch_vfCC
    // The state machine (+0xe4 table of (descriptor, adjust) pairs, state +0xe8, four states: 0 unlit, 1 lighting,
    // 2 going out, 3 lit), as CKHkS08TuningFork's: a handler gets the clock (null outside Update), the phase (0 update,
    // 1 enter, 2 leave) and the other state, and returns the next state (update) or `other`.
    using StateFn = uint8_t (CKHkS08FlamingTorch::*)(IKTime* clock, int32_t phase, uint8_t other);
    uint8_t CallState(uint8_t state, IKTime* clock, int32_t phase, uint8_t other);
    // The inlined state change (no clock): the current state left towards `next` (unless none), `next` entered.
    void ChangeState(uint8_t next);
    uint8_t State0(IKTime* clock, int32_t phase, uint8_t other);  // 0x00498988 CKHkS08FlamingTorch_State0_Unlit_maybe
    uint8_t State1(IKTime* clock, int32_t phase, uint8_t other);  // 0x00497970
    uint8_t State2(IKTime* clock, int32_t phase, uint8_t other);  // 0x00498ce0
    uint8_t State3(IKTime* clock, int32_t phase, uint8_t other);  // 0x004987a0 CKHkS08FlamingTorch_State3_Lit_maybe
    void DetectElementHits();                  // 0x00496470
    void StartFlameFx();                       // 0x00496758
    void ScaleFlameParticles(float t);         // 0x00496fe0
    void AddHotspotPointsToFx();               // 0x004971f0
    void UpdateFlameParticles(IKTime* clock);  // 0x00497c98
    void StartFlameParticles(float t);         // 0x00498350
    void TriggerHotSpotExplosionFx();          // 0x00498a20

    IKSerializable* m_pUnk20;   // +0x20 a CKImpulsionCpnt: the lighting (State1: its value grows to 1)
    IKSerializable* m_pUnk24;   // +0x24 a CKImpulsionCpnt: the going out (State2: the flame is 1 - its value)
    IKSerializable* m_pUnk28;   // +0x28 a CKAACylinder: PostLoad sizes it from +0x30 (height) / +0x34 (radius)
    struct ContactHistoryNode* m_unk2C;  // +0x2c constructor 0: the contacts (ContactHistory)
    float m_fUnk30;             // +0x30 the cylinder's height
    float m_fUnk34;             // +0x34 the cylinder's radius
    float m_fUnk38;             // +0x38 State1's enter sets 0
    float m_fUnk3C;             // +0x3c copied into the particle effect data's +0x0c (StartFlameParticles)
    uint32_t m_unk40;           // +0x40 State2's enter sets 0 (a word store)
    float m_fUnk44;             // +0x44
    float m_fUnk48;             // +0x48
    IKSerializable* m_pUnk4C;   // +0x4c a CKParticlesEffectFxData: the flame particles
    IKFx* m_pFx50;              // +0x50 runtime (PostLoad: 0): the flame particles' effect (a CKParticlesEffectNodeFx)
    IKSerializable* m_pUnk54;   // +0x54 the flame's FX data (an explosion)
    IKFx* m_pFx58;              // +0x58 runtime: its effect (StartFlameFx; released at once, kept)
    SEntry m_aUnk5C[2];         // +0x5c the file gives the count (2 in every sample): per particle node of +0x50, the
                                // size property's start (x, y) / end (x, y) and the initial speed at full flame
    float m_fUnk84;             // +0x84 the flame level (the sound's volume, the particles' scale)
    IKSerializable* m_pUnk88;   // +0x88 the hot spot explosion's FX data (TriggerHotSpotExplosionFx)
    IKSerializable* m_pUnk8C;   // +0x8c a CParticlesNodeFx (AddHotspotPointsToFx adds its emit points)
    IKSerializable* m_pUnk90;   // +0x90 a CParticlesNodeFx hung under the hot spot +0x94 (emits while lit)
    IKSerializable* m_pUnk94;   // +0x94 a CSGHotSpot: the flame's place
    uint32_t m_unk98;           // +0x98
    IKSerializable* m_pUnk9C;   // +0x9c CSGHotSpot (an emit point of +0x8c)
    IKSerializable* m_pUnkA0;   // +0xa0 CSGHotSpot
    IKSerializable* m_pUnkA4;   // +0xa4 CSGHotSpot
    IKSerializable* m_pUnkA8;   // +0xa8 CSGHotSpot
    CTriggerStarter m_unkAC;    // +0xac fired when the torch is lit
    CTriggerStarter m_unkB4;    // +0xb4 fired when it goes out
    IKSerializable* m_pUnkBC;   // +0xbc
    IKSerializable* m_pUnkC0;   // +0xc0 an ICollisionMesh (SetActive 1 when lighting starts, 0 when out / activated)
    uint8_t m_unkC4;            // +0xc4 DetectElementHits: an element damage of type 0 touches the cylinder
    uint8_t m_unkC5;            // +0xc5 ... of type 1
    uint8_t m_unkC6;            // +0xc6 ... of type 7
    uint8_t m_unkC7;            // +0xc7 ... any damage (properties bit 3 with a damage object)
    CVector3 m_vUnkC8;          // +0xc8 the flame's lean: from the last hit towards the torch, flat, normalised
    float m_fUnkD4;             // +0xd4 the lean's time left (1 at a hit, counted down by UpdateFlameParticles)
    uint8_t m_unkD8;            // +0xd8
    uint8_t m_unkD9;            // +0xd9
    uint8_t m_unkDA;            // +0xda
    uint8_t m_unkDB[2];         // +0xdb (an enable flag: !+0xd8 / !+0xd9 / !+0xda), +0xdc (+0xdd / +0xde / +0xdf)
    uint8_t m_unkDD;            // +0xdd
    uint8_t m_unkDE;            // +0xde
    uint8_t m_unkDF;            // +0xdf
    IKSerializable* m_pUnkE0;   // +0xe0 a CKSoundDictionaryID (sound 0: the flame's loop)
    uint32_t* m_pStateTable;    // +0xe4 runtime (PostLoad: m_aStateTable)
    uint8_t m_unkE8;            // +0xe8 constructor 0xff: the state
    uint8_t m_unkE9;            // +0xe9 constructor 0xff: the state count (PostLoad: 4)
    uint8_t m_unkEA[2];
    uint32_t m_aStateTable[8];  // +0xec runtime (PostLoad): the four states' (descriptor, 0) pairs
};
DOTD_ASSERT_SIZE(CKHkS08FlamingTorch::SEntry, 0x14);
DOTD_ASSERT_SIZE(CKHkS08FlamingTorch, 0x10c);
DOTD_ASSERT_OFFSET(CKHkS08FlamingTorch, m_pUnk20, 0x20);
DOTD_ASSERT_OFFSET(CKHkS08FlamingTorch, m_pUnk28, 0x28);
DOTD_ASSERT_OFFSET(CKHkS08FlamingTorch, m_unk2C, 0x2c);
DOTD_ASSERT_OFFSET(CKHkS08FlamingTorch, m_fUnk30, 0x30);
DOTD_ASSERT_OFFSET(CKHkS08FlamingTorch, m_fUnk38, 0x38);
DOTD_ASSERT_OFFSET(CKHkS08FlamingTorch, m_fUnk3C, 0x3c);
DOTD_ASSERT_OFFSET(CKHkS08FlamingTorch, m_unk40, 0x40);
DOTD_ASSERT_OFFSET(CKHkS08FlamingTorch, m_fUnk44, 0x44);
DOTD_ASSERT_OFFSET(CKHkS08FlamingTorch, m_fUnk48, 0x48);
DOTD_ASSERT_OFFSET(CKHkS08FlamingTorch, m_pUnk4C, 0x4c);
DOTD_ASSERT_OFFSET(CKHkS08FlamingTorch, m_pFx50, 0x50);
DOTD_ASSERT_OFFSET(CKHkS08FlamingTorch, m_pUnk54, 0x54);
DOTD_ASSERT_OFFSET(CKHkS08FlamingTorch, m_pFx58, 0x58);
DOTD_ASSERT_OFFSET(CKHkS08FlamingTorch, m_aUnk5C, 0x5c);
DOTD_ASSERT_OFFSET(CKHkS08FlamingTorch, m_fUnk84, 0x84);
DOTD_ASSERT_OFFSET(CKHkS08FlamingTorch, m_pUnk88, 0x88);
DOTD_ASSERT_OFFSET(CKHkS08FlamingTorch, m_pUnk94, 0x94);
DOTD_ASSERT_OFFSET(CKHkS08FlamingTorch, m_unk98, 0x98);
DOTD_ASSERT_OFFSET(CKHkS08FlamingTorch, m_pUnk9C, 0x9c);
DOTD_ASSERT_OFFSET(CKHkS08FlamingTorch, m_pUnkA8, 0xa8);
DOTD_ASSERT_OFFSET(CKHkS08FlamingTorch, m_unkAC, 0xac);
DOTD_ASSERT_OFFSET(CKHkS08FlamingTorch, m_unkB4, 0xb4);
DOTD_ASSERT_OFFSET(CKHkS08FlamingTorch, m_pUnkBC, 0xbc);
DOTD_ASSERT_OFFSET(CKHkS08FlamingTorch, m_pUnkC0, 0xc0);
DOTD_ASSERT_OFFSET(CKHkS08FlamingTorch, m_unkC4, 0xc4);
DOTD_ASSERT_OFFSET(CKHkS08FlamingTorch, m_unkC7, 0xc7);
DOTD_ASSERT_OFFSET(CKHkS08FlamingTorch, m_vUnkC8, 0xc8);
DOTD_ASSERT_OFFSET(CKHkS08FlamingTorch, m_fUnkD4, 0xd4);
DOTD_ASSERT_OFFSET(CKHkS08FlamingTorch, m_unkD8, 0xd8);
DOTD_ASSERT_OFFSET(CKHkS08FlamingTorch, m_unkDD, 0xdd);
DOTD_ASSERT_OFFSET(CKHkS08FlamingTorch, m_pUnkE0, 0xe0);
DOTD_ASSERT_OFFSET(CKHkS08FlamingTorch, m_pStateTable, 0xe4);
DOTD_ASSERT_OFFSET(CKHkS08FlamingTorch, m_unkE8, 0xe8);
DOTD_ASSERT_OFFSET(CKHkS08FlamingTorch, m_aStateTable, 0xec);
