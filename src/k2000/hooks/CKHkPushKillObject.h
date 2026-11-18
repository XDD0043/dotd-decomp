// CKHkPushKillObject.h - a deadly object pushed along an axis or a curve (key 0xd42, vtable 0xb262f0, size 0xe4).
// Original unit: CKHkPushKillObject.cpp (0x42cce0-0x42ffb0). No XXL2 class of this key; the layout comes from the Load
// (level type 0 only) and the users in the unit. No level of the game holds one (C2.8 port-rest R04: the class, its
// Load and its simple slots; C2.8 port-final F01: its motion (Update and its helpers, OnActivate / OnDeactivate /
// Restart) and the hit (MessageProc), all from the disassembly).
// The motion: pushed (+0xc0, messages 0x996 / 0x997) the object slides along its start matrix's axis +0x9c to +0xa0
// (FloatApproachAccel, +0xdc / +0xe0) and then follows the curve keys (+0x84: the offset along axis +0x7c over time,
// +0xc4) while it spins (+0x70: about its at axis, +0xd4 / +0xd8); released it spins down, slides back and its kill
// volume (+0x3c) leaves the collision service. The spark effect (+0x2c, node +0xb8) and the particle effect (+0x30,
// node +0xbc) follow it while it moves.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/misc/CKHkActorBase.h"
#include "k2000/services/CTriggerStarter.h"

struct RwMatrix;

class CKHkPushKillObject : public CKHkActorBase {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0x35)
    // vt+0x08 0x009c32b8 CKHkPushKillObject_IsKindOfClass [inline]
    int32_t IsKindOfClass(uint32_t key) override {
        return key == 0xd42 || key == 0xd82 || key == 0x2 || key == 0x2fe || key == 0x3fe || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKHkPushKillObject)

    CKHkPushKillObject() {}  // 0x0042d5b8 CKHkPushKillObject_Create: the CKHkActorBase defaults only
    ~CKHkPushKillObject() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0042ed08 CKHkPushKillObject_Load
    // vt+0xc0 0x0042cd98 CKHkPushKillObject_vfC0 (the actor base's Destroy calls it): the curve keys (+0x84) freed
    // (Mem_FreeAligned16) and cleared.
    void VfC0() override;
    // vt+0xc8 0x0042cd70 CKHkPushKillObject_vfC8: +0xc0 = the preset bit of +0xac (bit 0 for state 0, bit 1 otherwise).
    void ApplyStatePreset(int32_t state) override {
        m_ui8Pushed = state != 0 ? static_cast<uint8_t>((m_ui8Presets >> 1) & 1u) : static_cast<uint8_t>(m_ui8Presets & 1u);
    }
    // vt+0x38 0x0042cf50 CKHkPushKillObject_SetDefaultState: the actor base's (empty), then the preset 0 (vt+0xc8).
    void SetDefaultState(int32_t flag) override {
        CKHkActorBase::SetDefaultState(flag);
        ApplyStatePreset(0);
    }
    // vt+0x40 0x0042ce68 CKHkPushKillObject_GetInfo: the trigger value 0x98 (+0xc0, 0x9c3320, a byte), merged with the
    // actor base's answer (KStub_Return1 0x3f7140).
    int32_t GetInfo(struct IKInfo* info, int32_t request) override;
    // vt+0xb4 0x0042d218 CKHkPushKillObject_AttachSounds: sounds 0..2 of +0x20 (GetSound) on `leaf`.
    void KGLObjectAttached(IKSerializable* leaf) override;
    // vt+0x1c 0x0042f6b0 CKHkPushKillObject_MessageProc: the actor messages (0x3f7148), then 0x996 / 0x997 push / release
    // (+0xc0) and the hero's hazard query 0xc32 (the hit): the query's damage and knock words, sound 2, the FX data +0x38
    // started, the kill camera (+0x24) switched to for +0x28 seconds, FX data +0x34 placed at the hero's hot spot and
    // started, the hit signals (+0x58) queued. The answers merged as the actors do.
    int32_t MessageProc(uint16_t message, void* data) override;
    // vt+0x54 0x0042ebf8 CKHkPushKillObject_Restart: an awake object (+0x0c bit 2 clear) stops its effects, gets its start
    // matrix back and its volume under its node; then the runtime state reset.
    void Restart() override;
    void Update(IKTime* clock) override;  // vt+0x7c 0x0042ea68 CKHkPushKillObject_Update
    // vt+0xa0 0x0042dbf0 CKHkPushKillObject_OnActivate: the actor base's, the runtime state reset, the curve sound's top
    // speed drawn (one Rand_Int), the start matrix copied from the node, the volume under the node and registered, the
    // axis position placed (UpdateAxisPosition(0)).
    void VfA0() override;
    // vt+0xa4 0x0042e9b0 CKHkPushKillObject_OnDeactivate: the actor base's, the effects stopped, the start matrix back on
    // the node and destroyed, the volume unregistered and taken off its parent.
    void VfA4() override;

    // 0x0042cfa8 CKHkPushKillObject_UpdateSpin_maybe: with spins (+0x70) the spin speed (+0xd8) rises by +0x78 x dt to
    // +0x74 while pushed or on the curve, else falls to 0; the angle (+0xd4) turns by it (a random quarter turn added
    // while it moves: one Rand_Int) and the node is set facing the start matrix's at axis, rolled by the angle. 1 when
    // the speed reached its end (or without spins), else 0.
    uint8_t UpdateSpin(float dt);
    // 0x0042d610 CKHkPushKillObject_UpdateCurveMotion_maybe: the curve time advanced (wrapping after the last key), the
    // offset (+0xcc, the previous one +0xc8) interpolated from the keys, the node placed at the start position plus the
    // offset along axis +0x7c; the curve sound's speed and the spark parameters' intensity from the offset's distance to
    // +0x88 / +0x8c.
    void UpdateCurveMotion(float dt);
    // 0x0042d9a8 CKHkPushKillObject_UpdateAxisPosition_maybe: the axis position (+0xdc / +0xe0) approaches +0xa0 (pushed:
    // 0) with FloatApproachAccel (sound 0 played when it starts out), the node placed along axis +0x9c.
    void UpdateAxisPosition(float dt);
    // 0x0042de58 CKHkPushKillObject_UpdateVolumesAndFx_maybe: the spark matrix and the particle matrix placed at the ends
    // of the object's half size along axis +0x7c (the trailing end, turned round, while the offset grows); `active` 0
    // stops both effects (and the curve sound), 1 starts the missing ones (the curve sound looped).
    void UpdateVolumesAndFx(uint8_t active);

    IKSerializable* m_pSounds;             // +0x20 a CKSoundDictionaryID: 0 the axis move, 1 the curve loop, 2 the hit
    IKSerializable* m_pKillCamera;         // +0x24 the camera the hit switches to (MessageProc 0xc32)
    float m_fKillCameraTime;               // +0x28
    IKSerializable* m_pFxData2C;           // +0x2c FX data (its +0x14 matrix follows the object)
    IKSerializable* m_pFxData30;           // +0x30 FX data (a CKParticlesEffectFxData: +0x08, +0x10, +0x14, +0x24)
    IKSerializable* m_pFxData34;           // +0x34 FX data placed at the hit
    IKSerializable* m_pFxData38;           // +0x38 FX data started at the hit
    IKSerializable* m_pVolume;             // +0x3c the kill volume (an IKBoundingVolume)
    CVector3 m_unk40;                      // +0x40 one 12-byte read
    CVector3 m_unk4C;                      // +0x4c one 12-byte read (+0x4c / +0x50 / +0x54: the half sizes per axis)
    CTriggerStarter m_tsHit;               // +0x58 queued at the hit
    uint8_t m_ui8Damage;                   // +0x60 the hazard query's damage
    uint8_t m_pad61[3];
    float m_afKnock[3];                    // +0x64 the hazard query's words (+0x10, +0x0c, +0x08)
    uint8_t m_ui8Spins;                    // +0x70
    uint8_t m_pad71[3];
    float m_fSpinMax;                      // +0x74
    float m_fSpinAccel;                    // +0x78
    uint8_t m_ui8Axis;                     // +0x7c 0 right, 1 up, 2 at (of the start matrix)
    uint8_t m_pad7D[3];
    uint32_t m_ui32KeyCount;               // +0x80
    float* m_afKeys;                       // +0x84 (time, value) pairs, Mem_AllocAligned16(count * 8), words swapped
    // +0x88..+0x98 (+0x98 = 1.3 for every type before the type test): [0] / [1] the curve offsets where the sound and
    // spark ramps end / start, [2] the ramp's share of [1] - [0], [3] the curve sound's lowest speed, [4] its base top
    // speed (OnActivate adds the sound's random pitch and a random part).
    float m_unk88[5];
    uint8_t m_ui8MoveAxis;                 // +0x9c
    uint8_t m_pad9D[3];
    float m_unkA0[3];                      // +0xa0 the axis target, +0xa4 its top speed, +0xa8 its acceleration
    uint8_t m_ui8Presets;                  // +0xac bits 0 / 1: the pushed state of presets 0 / 1
    uint8_t m_padAD[3];
    IKSerializable* m_unkB0;               // +0xb0
    RwMatrix* m_pStartMatrix;              // +0xb4 runtime (OnActivate: RwMatrixCreate, the node's matrix)
    IKSerializable* m_pFxB8;               // +0xb8 runtime: the effect of +0x2c
    IKSerializable* m_pFxBC;               // +0xbc runtime: the effect of +0x30
    uint8_t m_ui8Pushed;                   // +0xc0 the preset's pushed state (0x996 / 0x997; trigger value 0x98)
    uint8_t m_padC1[3];
    // +0xc4..+0xe0 runtime: [0] the curve time, [1] the previous offset, [2] the offset, [3] the curve sound's top
    // speed, [4] the spin angle, [5] the spin speed, [6] the axis position, [7] its speed.
    float m_unkC4[8];
};
DOTD_ASSERT_SIZE(CKHkPushKillObject, 0xe4);
DOTD_ASSERT_OFFSET(CKHkPushKillObject, m_pSounds, 0x20);
DOTD_ASSERT_OFFSET(CKHkPushKillObject, m_pVolume, 0x3c);
DOTD_ASSERT_OFFSET(CKHkPushKillObject, m_unk40, 0x40);
DOTD_ASSERT_OFFSET(CKHkPushKillObject, m_tsHit, 0x58);
DOTD_ASSERT_OFFSET(CKHkPushKillObject, m_ui8Damage, 0x60);
DOTD_ASSERT_OFFSET(CKHkPushKillObject, m_ui8Spins, 0x70);
DOTD_ASSERT_OFFSET(CKHkPushKillObject, m_ui8Axis, 0x7c);
DOTD_ASSERT_OFFSET(CKHkPushKillObject, m_ui32KeyCount, 0x80);
DOTD_ASSERT_OFFSET(CKHkPushKillObject, m_unk88, 0x88);
DOTD_ASSERT_OFFSET(CKHkPushKillObject, m_ui8MoveAxis, 0x9c);
DOTD_ASSERT_OFFSET(CKHkPushKillObject, m_unkA0, 0xa0);
DOTD_ASSERT_OFFSET(CKHkPushKillObject, m_ui8Presets, 0xac);
DOTD_ASSERT_OFFSET(CKHkPushKillObject, m_unkB0, 0xb0);
DOTD_ASSERT_OFFSET(CKHkPushKillObject, m_pStartMatrix, 0xb4);
DOTD_ASSERT_OFFSET(CKHkPushKillObject, m_ui8Pushed, 0xc0);
DOTD_ASSERT_OFFSET(CKHkPushKillObject, m_unkC4, 0xc4);
