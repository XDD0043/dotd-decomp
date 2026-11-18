// CKHkS08Fire.h - a fire hook (key 0x3442, size 0xd8). Original unit: CKHkS08Fire.cpp. No XXL2 class.
// The fields are named by offset until their use is known.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/misc/CKHkActorBase.h"
#include "k2000/fx/IKFx.h"
#include "k2000/services/CTriggerStarter.h"

class IKTime;

class CKHkS08Fire : public CKHkActorBase {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0xd1)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c6250
        return key == 0x3442 || key == 0xd82 || key == 0x2 || key == 0x2fe || key == 0x3fe || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKHkS08Fire)

    // 0x004db3d0 CKHkS08Fire_Construct (inlined in 0x004db538 CKHkS08Fire_Create): +0x58 = 0,
    // +0x85/+0x84 = 0xff.
    CKHkS08Fire() {
        m_unk58 = 0;
        m_unk85 = 0xff;
        m_unk84 = 0xff;
    }
    // 0x004db318 CKHkS08Fire_Destructor (0x004db290 the deleting one): the contacts (+0x58) back to their pool
    // (ContactHistory_FreeNode), the list cleared, then CKHkActorBase's.
    ~CKHkS08Fire() override;

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x004db7c8 CKHkS08Fire_Load
    // vt+0xc8 0x004da7f0 CKHkS08Fire_vfC8 (unit CKHkS08SpawnableMushroom.cpp): the byte +0x50 = +0x7c for a nonzero
    // preset, else +0x7d.
    void ApplyStatePreset(int32_t state) override { m_unk50 = state != 0 ? m_unk7C : m_unk7D; }
    // vt+0x30 0x004db088 CKHkS08Fire_PostLoad: the actor base's; for the level type +0xc4, +0xb8, +0xbc, +0xc0 = 0. 1.
    int32_t PostLoad(int32_t type) override;
    // vt+0x38 0x004dafd8 CKHkS08Fire_SetDefaultState: the actor base's (empty), then +0x50 = +0x7e.
    void SetDefaultState(int32_t flag) override;
    // vt+0x40 0x004daef8 CKHkS08Fire_GetInfo: value 0x9a, the state +0x84 (0x009c62b8, type 1); the actor base answers 1.
    int32_t GetInfo(IKInfo* info, int32_t request) override;
    // vt+0x10 0x004db390 CKHkS08Fire_Destroy: the actor base's, then the matrix +0x64 destroyed (RwMatrixDestroy_Thunk).
    void Destroy() override;
    // 0x004dab70 CKHkS08Fire_StopSounds_maybe: sounds 0, 1 and 2 of the dictionary +0x2c stopped (those it has).
    void StopSounds();
    // Resume / Pause / Stop / RecursiveRegistration (0x4db010 .. 0x4db060, 0x4db0f0) only call CKHkActorBase's: inherited.

    // ---- C2.8 port-rest R10: the fire's runtime (a state machine of four flame stages; LVL050 / LVL060 class) ----
    // vt+0x50 0x004dcc78 CKHkS08Fire_Start: the actor base's; the four states, none current; no stage effects; the
    // volume (+0x54, a CKAACylinder) owned by the fire, radius +0x5c, half height +0x60 * 0.5.
    void Start() override;
    // vt+0x54 0x004dc850 CKHkS08Fire_Restart: the stage effects 1..3 and the lights let go; enabled: the sounds stopped
    // and the preset state (+0x50) entered when it is not the current one; disabled (+0xc bit 2): no state.
    void Restart() override;
    // vt+0x7c 0x004dcdb0 CKHkS08Fire_Update: the actor base's, then the state machine's frame.
    void Update(IKTime* clock) override;
    // vt+0xa0 0x004dddd0 CKHkS08Fire_OnActivate / vt+0xa4 0x004db5a8 CKHkS08Fire_OnDeactivate.
    void VfA0() override;
    void VfA4() override;
    // vt+0x1c 0x004dc2c0 CKHkS08Fire_MessageProc: 0x996..0x999 switch to the state 0..3, 0x99a to the next one (from
    // 0..2), with the trigger starters quiet (+0x7f); 0 for those, else 1.
    int32_t MessageProc(uint16_t message, void* data) override;
    // 0x004dd2a0 CKHkS08Fire_StartFlameStage_maybe: stage `stage`'s particles started if not running (at the fire's
    // position); stages 1..3 then loop their sound (0..2) unless it plays.
    void StartFlameStage(int32_t stage);
    // 0x004dace8 CKHkS08Fire_ProcessPowerBucketContacts_maybe: a power bucket (class id 0xc3) newly touching the volume
    // asks for the stage below (none below 0); the contacts aged.
    void ProcessPowerBucketContacts(IKTime* clock);
    // The states (the table Start builds at +0x88): 0x004dee10 / 0x004df490 / 0x004de748 / 0x004de0a0.
    uint8_t State0(IKTime* clock, int32_t phase, uint8_t other);
    uint8_t State1(IKTime* clock, int32_t phase, uint8_t other);
    uint8_t State2(IKTime* clock, int32_t phase, uint8_t other);
    uint8_t State3(IKTime* clock, int32_t phase, uint8_t other);
    using StateFn = uint8_t (CKHkS08Fire::*)(IKTime* clock, int32_t phase, uint8_t other);
    uint8_t CallState(uint8_t state, IKTime* clock, int32_t phase, uint8_t other);
    // The inlined switch: the current state left (phase 2, other `next`), `next` entered (phase 1, other the old one).
    void SwitchState(uint8_t next, IKTime* clock);
    // The shared body of State1..3 (stage `n`, the next state +0x68 when the timer runs out).
    uint8_t FlameState(uint32_t n, IKTime* clock, int32_t phase, uint8_t other);
    IKFx* AcquireLightFx(uint32_t n);

    float m_fUnk20;             // +0x20 (3600 in the sample): State1's duration before state 2 (0 or less: none)
    float m_fUnk24;             // +0x24 State2's duration before state 3 (0 or less: none)
    float m_fStateTime;         // +0x28 runtime: the time in the current state (the enters store a word 0)
    IKSerializable* m_pUnk2C;   // +0x2c the sounds (a CKSoundDictionaryID: 0..2 the stages 1..3)
    // +0x30 / +0x38 / +0x40 / +0x48: the flame stages' particles data (CKParticlesEffectFxData), each followed by the
    // effect StartFlameStage acquired for it (+0x34 / +0x3c / +0x44 / +0x4c).
    IKSerializable* m_pUnk30;   // +0x30
    IKFx* m_pStageFx0;          // +0x34
    IKSerializable* m_pUnk38;   // +0x38
    IKFx* m_pStageFx1;          // +0x3c
    IKSerializable* m_pUnk40;   // +0x40
    IKFx* m_pStageFx2;          // +0x44
    IKSerializable* m_pUnk48;   // +0x48
    IKFx* m_pStageFx3;          // +0x4c
    uint8_t m_unk50;            // +0x50
    uint8_t m_unk51[3];
    IKSerializable* m_pUnk54;   // +0x54
    struct ContactHistoryNode* m_unk58;  // +0x58 constructor 0: the contacts (ContactHistory)
    float m_fUnk5C;             // +0x5c
    float m_fUnk60;             // +0x60
    CMatrix34* m_pMatrix64;     // +0x64 RwMatrixCreate in the Load, then pos, at, up, right from the file
    uint8_t m_ui8NextState;     // +0x68 runtime: the state the current one asks for (0xff none; the ticks return it)
    uint8_t m_pad69[3];
    CTriggerStarter m_unk6C;    // +0x6c
    CTriggerStarter m_unk74;    // +0x74
    uint8_t m_unk7C;            // +0x7c
    uint8_t m_unk7D;            // +0x7d
    uint8_t m_unk7E;            // +0x7e
    uint8_t m_unk7F;            // +0x7f runtime (Start: 1): the state enters queue the trigger starters (+0x6c / +0x74)
    uint32_t* m_pStateTable;    // +0x80 Start: the table +0x88
    uint8_t m_unk84;            // +0x84 constructor 0xff: the current state (0..3: the flame stages)
    uint8_t m_unk85;            // +0x85 constructor 0xff: the state count (Start: 4)
    uint8_t m_unk86[2];
    uint32_t m_unk88[8];        // +0x88 Start: the four states' (descriptor, adjust) pairs
    // +0xa8..+0xb4: the stages' point lights (CKPointLightFxData), their effects (+0xb8..+0xc4) and the objects whose
    // position (+0x4) the lights take (+0xc8..+0xd4).
    IKSerializable* m_pUnkA8;   // +0xa8
    IKSerializable* m_pUnkAC;   // +0xac
    IKSerializable* m_pUnkB0;   // +0xb0
    IKSerializable* m_pUnkB4;   // +0xb4
    IKFx* m_unkB8[4];           // +0xb8 runtime: the lights' effects
    IKSerializable* m_pUnkC8;   // +0xc8 (paired with +0xa8; +0xcc with +0xac, ...)
    IKSerializable* m_pUnkCC;   // +0xcc
    IKSerializable* m_pUnkD0;   // +0xd0
    IKSerializable* m_pUnkD4;   // +0xd4
};
DOTD_ASSERT_SIZE(CKHkS08Fire, 0xd8);
DOTD_ASSERT_OFFSET(CKHkS08Fire, m_fUnk20, 0x20);
DOTD_ASSERT_OFFSET(CKHkS08Fire, m_pUnk2C, 0x2c);
DOTD_ASSERT_OFFSET(CKHkS08Fire, m_pUnk30, 0x30);
DOTD_ASSERT_OFFSET(CKHkS08Fire, m_pUnk38, 0x38);
DOTD_ASSERT_OFFSET(CKHkS08Fire, m_pUnk40, 0x40);
DOTD_ASSERT_OFFSET(CKHkS08Fire, m_pUnk48, 0x48);
DOTD_ASSERT_OFFSET(CKHkS08Fire, m_unk50, 0x50);
DOTD_ASSERT_OFFSET(CKHkS08Fire, m_pUnk54, 0x54);
DOTD_ASSERT_OFFSET(CKHkS08Fire, m_unk58, 0x58);
DOTD_ASSERT_OFFSET(CKHkS08Fire, m_fUnk5C, 0x5c);
DOTD_ASSERT_OFFSET(CKHkS08Fire, m_fUnk60, 0x60);
DOTD_ASSERT_OFFSET(CKHkS08Fire, m_pMatrix64, 0x64);
DOTD_ASSERT_OFFSET(CKHkS08Fire, m_unk6C, 0x6c);
DOTD_ASSERT_OFFSET(CKHkS08Fire, m_unk74, 0x74);
DOTD_ASSERT_OFFSET(CKHkS08Fire, m_unk7C, 0x7c);
DOTD_ASSERT_OFFSET(CKHkS08Fire, m_unk84, 0x84);
DOTD_ASSERT_OFFSET(CKHkS08Fire, m_pUnkA8, 0xa8);
DOTD_ASSERT_OFFSET(CKHkS08Fire, m_pUnkB4, 0xb4);
DOTD_ASSERT_OFFSET(CKHkS08Fire, m_pUnkC8, 0xc8);
DOTD_ASSERT_OFFSET(CKHkS08Fire, m_pUnkD4, 0xd4);
