// CKHkS08CristalReceiver.h - key 0x2c02, size 0x94. Original unit: CKHkS08CristalReceiver.cpp. No XXL2 class. The fields
// are named by offset until their use is known.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/CKHkActorBase.h"
#include "k2000/services/CTriggerStarter.h"

class CKHkS08CristalReceiver : public CKHkActorBase {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0xb0)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c4868
        return key == 0x2c02 || key == 0xd82 || key == 0x2 || key == 0x2fe || key == 0x3fe || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKHkS08CristalReceiver)

    // 0x00483870 CKHkS08CristalReceiver_Construct (inlined in 0x00483da0 CKHkS08CristalReceiver_Create): +0x81, +0x80 = 0xff.
    CKHkS08CristalReceiver() {
        m_unk81 = 0xff;
        m_unk80 = 0xff;
    }
    ~CKHkS08CristalReceiver() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x004846c8 CKHkS08CristalReceiver_Load
    // vt+0x30 0x00483768 CKHkS08CristalReceiver_PostLoad: the actor base's; for the level type +0x44, +0x50, +0x40 = 0. 1.
    int32_t PostLoad(int32_t type) override {
        CKHkActorBase::PostLoad(type);  // 0x003f6e70
        if (type == K_LEVEL_PLATEFORMS) {
            m_unk40[1] = nullptr;
            m_unk50 = nullptr;
            m_unk40[0] = nullptr;
        }
        return 1;
    }
    void Restart() override { m_unk70[0] = 0.0f; }  // vt+0x54 0x00483260 CKHkS08CristalReceiver_Restart: +0x70 = 0 (stw)
    // Resume / Pause / Stop / Destroy / RecursiveRegistration (0x483560 .. 0x483818, 0x4837f0) only call CKHkActorBase's;
    // the destructors (0x483ab0 / 0x483a68) only CKHkActorBase's: inherited.
    // 0x00483ae0 CKHkS08CristalReceiver_GetTriggerProp96: the byte +0x80 is 1.
    uint8_t GetTriggerProp96() const { return m_unk80 == 1 ? 1 : 0; }
    // vt+0x40 0x00483688 CKHkS08CristalReceiver_GetInfo: value 0x96, GetTriggerProp96 (descriptor 0x00bc2b70, type 0);
    // the actor base answers 1.
    int32_t GetInfo(IKInfo* info, int32_t request) override;
    // port-final F06: the state engine (table +0x7c, state +0x80, count +0x81, the pairs from +0x84 per Start 0x4835d8),
    // public for CKHkS08CristalKey, which switches the receiver directly. A handler is (clock, phase 0 tick / 1 enter /
    // 2 leave, the other state) -> next.
    uint8_t CallState(const uint32_t pair[2], class IKTime* clock, int32_t phase, uint8_t other);
    // The switch as the code inlines it: the current state left (phase 2, other `leaveOther`), `next` entered (phase 1,
    // other the old state; none when `next` is 0xff).
    void SwitchState(uint8_t next, class IKTime* clock, uint8_t leaveOther);
    uint8_t GetState() const { return m_unk80; }
    // port-final F06: the run time.
    // vt+0x50 0x004835d8 CKHkS08CristalReceiver_Start: the base's (empty); the two-state table (no state entered); the
    // actor +0x20 disabled (vt+0xcc 0).
    void Start() override;
    // vt+0x7c 0x00483ef8 CKHkS08CristalReceiver_Update: the actor base's (empty); with no state yet, a transportable key
    // (class id 0xc2) taken from the group +0x28 for the CKHkS08CristalKey +0x24 (its +0x20; none without a group): out of
    // its state machine (vt+0x108), placed (vt+0x128 1), state 1 entered with the key's byte +0x39 cleared around it;
    // the key's emitter (+0x24) +0x28 follows. Then the machine's tick and the glow (+0x70).
    void Update(class IKTime* clock) override;
    // vt+0x1c 0x004844c8 CKHkS08CristalReceiver_MessageProc: the actor base's first; 0x900: state 1 (0). The answers
    // folded: 3, then 2, then the base's 0, else this one's (1 for other messages).
    int32_t MessageProc(uint16_t message, void* data) override;
    // vt+0xa0 0x00484318 CKHkS08CristalReceiver_OnActivate_maybe (not the actor base's: the receiver does not join the
    // active actors): the glow node hidden, state 0, the particle node +0x4c emitting (message 0x1a00's 1 inlined), +0x70
    // = 0.
    void VfA0() override;
    // vt+0xa4 0x00483e08 CKHkS08CristalReceiver_OnDeactivate: the actor base's; the particle node +0x4c off (message
    // 0x1a00's 0 inlined), the effects +0x50 and +0x40 stopped and released.
    void VfA4() override;
    // 0x00483270 CKHkS08CristalReceiver_SetGlowLevel_maybe: the node +0x58 hidden at 0 or less (its geometries' alpha 0);
    // else shown with alpha 254 at 1 or more, else level * 254 clamped to 254 (the low byte of fctiwz).
    void SetGlowLevel(float level);
    // 0x00483b88 CKHkS08CristalReceiver_AddHotspotPointsToFx_maybe: the hot spots +0x5c and +0x60 added as emit points
    // of the particle node +0x4c (64 at most; the node's 0x2000 bit set).
    void AddHotspotPointsToFx();
    // 0x00484e60 CKHkS08CristalReceiver_TriggerReceiveFx_maybe: an explosion of the data +0x48 acquired (+0x44), put at
    // the hot spot +0x34 (else the node's modelling position), triggered and stopped / released (vt+0x58).
    void TriggerReceiveFx();
    // The states (the table Start builds at +0x84). 0x00485168 CKHkS08CristalReceiver_State0_AwaitOrb_maybe: tick only:
    // a hero carrying the key's object within +0x64 makes it glow, within +0x30 shows the input icon (+0x3c -> +0x40)
    // and with action 3 the object is given (vt+0xf8): placed, the hero told (0x94d), the receive effect, glow 1,
    // state 1. 0x00486010 CKHkS08CristalReceiver_State1_maybe: enter: the starter +0x68 (when the key's +0x39 is set),
    // the object hung on the hot spot +0x34 (else the sector root at the node's position), placed, +0x20 enabled;
    // tick: the glow fades over +0x78, the particle effect of +0x54 (+0x50) and the emit points; leave: +0x20
    // disabled, the effect released.
    uint8_t State0(class IKTime* clock, int32_t phase, uint8_t other);
    uint8_t State1(class IKTime* clock, int32_t phase, uint8_t other);
    using StateFn = uint8_t (CKHkS08CristalReceiver::*)(class IKTime* clock, int32_t phase, uint8_t other);

    IKSerializable* m_pUnk20;  // +0x20 an actor State1 enables (vt+0xcc)
    IKSerializable* m_pUnk24;  // +0x24 the CKHkS08CristalKey (its +0x20 object, +0x24 emitter, +0x39 byte)
    IKSerializable* m_pUnk28;  // +0x28 the CKGrpTransportableObject it takes its object from
    IKSerializable* m_pUnk2C;  // +0x2c
    float m_fUnk30;  // +0x30 the interaction radius (State0)
    IKSerializable* m_pUnk34;  // +0x34 a CSGHotSpot: where the object hangs and the effects go
    IKSerializable* m_pUnk38;  // +0x38
    IKSerializable* m_pUnk3C;  // +0x3c the input icon's data (State0 -> +0x40)
    IKSerializable* m_unk40[2];  // +0x40 runtime: the input icon (State0), +0x44 the receive explosion (PostLoad: 0)
    IKSerializable* m_pUnk48;  // +0x48 the receive explosion's data (TriggerReceiveFx)
    IKSerializable* m_pUnk4C;  // +0x4c a CParticlesNodeFx (OnActivate / OnDeactivate, the emit points)
    IKSerializable* m_unk50;   // +0x50 runtime: the particle effect of +0x54 (State1; PostLoad: 0)
    IKSerializable* m_pUnk54;  // +0x54 the particle effect's data (State1)
    IKSerializable* m_pUnk58;  // +0x58 the glow node (SetGlowLevel)
    IKSerializable* m_pUnk5C;  // +0x5c a CSGHotSpot (an emit point)
    IKSerializable* m_pUnk60;  // +0x60 a CSGHotSpot (an emit point)
    float m_fUnk64;  // +0x64 the glow radius (State0)
    CTriggerStarter m_unk68;  // +0x68
    float m_unk70[2];  // +0x70 runtime: the glow level (Restart / OnActivate: 0; Update shows it); +0x74 not used here
    float m_fUnk78;  // +0x78 the glow's fade time (State1)
    uint32_t* m_pStateTable;  // +0x7c Start: m_aStateTable
    uint8_t m_unk80;  // +0x80 the state (constructor 0xff; GetTriggerProp96: state 1)
    uint8_t m_unk81;  // +0x81 the state count (constructor 0xff; Start: 2)
    uint8_t m_pad82[2];
    uint32_t m_aStateTable[4];  // +0x84 two handler pairs (Start: State0 0xbc2cd0, State1 0xbc2d08)
};
DOTD_ASSERT_SIZE(CKHkS08CristalReceiver, 0x94);
DOTD_ASSERT_OFFSET(CKHkS08CristalReceiver, m_pUnk20, 0x20);
DOTD_ASSERT_OFFSET(CKHkS08CristalReceiver, m_pUnk24, 0x24);
DOTD_ASSERT_OFFSET(CKHkS08CristalReceiver, m_pUnk28, 0x28);
DOTD_ASSERT_OFFSET(CKHkS08CristalReceiver, m_pUnk2C, 0x2c);
DOTD_ASSERT_OFFSET(CKHkS08CristalReceiver, m_fUnk30, 0x30);
DOTD_ASSERT_OFFSET(CKHkS08CristalReceiver, m_pUnk34, 0x34);
DOTD_ASSERT_OFFSET(CKHkS08CristalReceiver, m_pUnk38, 0x38);
DOTD_ASSERT_OFFSET(CKHkS08CristalReceiver, m_pUnk3C, 0x3c);
DOTD_ASSERT_OFFSET(CKHkS08CristalReceiver, m_pUnk48, 0x48);
DOTD_ASSERT_OFFSET(CKHkS08CristalReceiver, m_pUnk4C, 0x4c);
DOTD_ASSERT_OFFSET(CKHkS08CristalReceiver, m_pUnk54, 0x54);
DOTD_ASSERT_OFFSET(CKHkS08CristalReceiver, m_pUnk58, 0x58);
DOTD_ASSERT_OFFSET(CKHkS08CristalReceiver, m_pUnk5C, 0x5c);
DOTD_ASSERT_OFFSET(CKHkS08CristalReceiver, m_pUnk60, 0x60);
DOTD_ASSERT_OFFSET(CKHkS08CristalReceiver, m_fUnk64, 0x64);
DOTD_ASSERT_OFFSET(CKHkS08CristalReceiver, m_unk68, 0x68);
DOTD_ASSERT_OFFSET(CKHkS08CristalReceiver, m_fUnk78, 0x78);
DOTD_ASSERT_OFFSET(CKHkS08CristalReceiver, m_unk80, 0x80);
DOTD_ASSERT_OFFSET(CKHkS08CristalReceiver, m_unk81, 0x81);
DOTD_ASSERT_OFFSET(CKHkS08CristalReceiver, m_unk40, 0x40);
DOTD_ASSERT_OFFSET(CKHkS08CristalReceiver, m_unk50, 0x50);
DOTD_ASSERT_OFFSET(CKHkS08CristalReceiver, m_unk70, 0x70);
DOTD_ASSERT_OFFSET(CKHkS08CristalReceiver, m_pStateTable, 0x7c);
DOTD_ASSERT_OFFSET(CKHkS08CristalReceiver, m_aStateTable, 0x84);
