// CKHkS08CristalEmitter.h - key 0x2bc2, size 0x88. Original unit: CKHkS08CristalEmitter.cpp. No XXL2 class. The fields
// are named by offset until their use is known.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/CKHkActorBase.h"
#include "k2000/services/CTriggerStarter.h"

class CKHkS08CristalEmitter : public CKHkActorBase {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0xaf)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c4800
        return key == 0x2bc2 || key == 0xd82 || key == 0x2 || key == 0x2fe || key == 0x3fe || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKHkS08CristalEmitter)

    // 0x00480920 CKHkS08CristalEmitter_Construct (inlined in 0x00480c30 CKHkS08CristalEmitter_Create): +0x75, +0x74 = 0xff.
    CKHkS08CristalEmitter() {
        m_unk75 = 0xff;
        m_unk74 = 0xff;
    }
    // 0x00480be8 CKHkS08CristalEmitter_Destructor / 0x004808f0 BaseDestructor / 0x00480ba0 DeletingDestructor: the
    // vtable, then CKHkActorBase's.
    ~CKHkS08CristalEmitter() override {}
    // vt+0x10 Destroy 0x4808c8, vt+0x24 RecursiveRegistration 0x4808a0, vt+0x68 Stop 0x480678, vt+0x70 Pause 0x480650,
    // vt+0x78 Resume 0x480628: CKHkActorBase's / IKHook's (inherited here).
    // vt+0x30 0x00480818 CKHkS08CristalEmitter_PostLoad: the base's; type 0: +0x60 and +0x6c cleared.
    int32_t PostLoad(int32_t type) override {
        CKHkActorBase::PostLoad(type);  // 0x3f6e70
        if (type == 0) {
            m_pUnk60 = nullptr;
            m_pUnk6C = nullptr;
        }
        return 1;
    }
    // vt+0x40 0x00480738 CKHkS08CristalEmitter_GetInfo: value 0x96 (GetTriggerProp96 0x480c18: +0x74 == 1, a byte).
    int32_t GetInfo(struct IKInfo* info, int32_t request) override;

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x004816a0 CKHkS08CristalEmitter_Load
    // port-rest R09:
    void Start() override;    // vt+0x50 0x004806a0 CKHkS08CristalEmitter_Start
    void Restart() override;  // vt+0x54 0x004811c8 CKHkS08CristalEmitter_Restart
    void VfA0() override;     // vt+0xa0 0x00481218 CKHkS08CristalEmitter_OnActivate
    void VfA4() override;     // vt+0xa4 0x00481250 CKHkS08CristalEmitter_OnDeactivate
    // 0x00480d70 CKHkS08CristalEmitter_SetOrbOpacity_maybe: the orb node +0x50 hidden at 0 or less; else shown with its
    // geometries' alpha (0xfe at 1 or more, else opacity * 254 clamped to 254, the low byte of fctiwz).
    void SetOrbOpacity(float opacity);
    // port-final F06: the run time.
    // vt+0x7c 0x004812c8 CKHkS08CristalEmitter_Update: the actor base's (empty); with the sector loaded (IKLife bit 2 clear)
    // and no state yet, a transportable key (class id 0xc2) taken from the group +0x30 (or none without a group): left
    // its state machine (vt+0x108), placed (vt+0x128 1), the machine switched to state 0 with the CKHkS08CristalKey +0x20's
    // byte +0x39 cleared around it; the key's +0x20 tracks it. Then the machine's tick.
    void Update(class IKTime* clock) override;
    // vt+0x1c 0x00482518 CKHkS08CristalEmitter_MessageProc: the actor base's first. 0x93f (data: the hero who brings
    // the transportable +0x28): the hero kept (+0x2c); when his carrier can pick it up (vt+0x58), it can be taken
    // (vt+0xf4), the carrier's +0x90 set, and it is taken (vt+0xf0): the starter +0x48 fired, the object off the hot
    // spot +0x40 onto the carrier's (vt+0x84), state 1, the input icon +0x6c released, the object unplaced (vt+0x128 0),
    // +0x58 = 0, SpawnFx and the hero detached; 0. Other messages: the base's answer folded (3, 2, else 0 / 1).
    int32_t MessageProc(uint16_t message, void* data) override;
    // 0x00482218 CKHkS08CristalEmitter_SpawnFx_maybe: an effect of the data +0x64 acquired (CKSrvFx::AcquireFx inlined;
    // an explosion), put at the hot spot +0x40 (else the node's LTM position), triggered and its reservation released.
    void SpawnFx();
    // The states (the table Start builds at +0x78). 0x00482918 CKHkS08CristalEmitter_State0_OrbReady_maybe: enter: the
    // object (no state without one) hung on the hot spot +0x40 (else the sector root at the node's position) unless
    // carried, the particle effect of +0x5c acquired (+0x60) at the hot spot; tick: the orb opaque, the player heroes
    // within +0x3c (not in a combo) get this as interaction target and the input icon (+0x68 -> +0x6c) shows, else it
    // goes; leave: both effects released. 0x00481020 CKHkS08CristalEmitter_State1: enter: the sound 0 of +0x44 played,
    // +0x24 enabled (vt+0xcc 1), +0x58 = 0; tick: +0x58 runs to +0x54, the orb fades out; leave: +0x24 disabled, the orb
    // transparent.
    uint8_t State0(class IKTime* clock, int32_t phase, uint8_t other);
    uint8_t State1(class IKTime* clock, int32_t phase, uint8_t other);
    using StateFn = uint8_t (CKHkS08CristalEmitter::*)(class IKTime* clock, int32_t phase, uint8_t other);
    // port-final F06: the state engine (table +0x70, state +0x74, count +0x75), public for CKHkS08CristalKey, which
    // switches the emitter directly. A handler is (clock, phase 0 tick / 1 enter / 2 leave, the other state) -> next.
    uint8_t CallState(const uint32_t pair[2], class IKTime* clock, int32_t phase, uint8_t other);
    // The switch as the code inlines it: the current state left (phase 2, other `leaveOther`), `next` entered (phase 1,
    // other the old state; none when `next` is 0xff).
    void SwitchState(uint8_t next, class IKTime* clock, uint8_t leaveOther);
    uint8_t GetState() const { return m_unk74; }

    IKSerializable* m_pUnk20;  // +0x20 the CKHkS08CristalKey (Update: its +0x20 / +0x39)
    IKSerializable* m_pUnk24;  // +0x24 an actor State1 enables (vt+0xcc)
    IKSerializable* m_pUnk28;  // +0x28 runtime: the transportable key (class id 0xc2) it holds (Start: 0; CKHkS08CristalKey clears it)
    IKSerializable* m_unk2C;  // +0x2c runtime: the hero of message 0x93f (Start: 0)
    IKSerializable* m_pUnk30;  // +0x30 the CKGrpTransportableObject it takes its object from
    IKSerializable* m_pUnk34;  // +0x34
    uint8_t m_unk38;  // +0x38 runtime (Start: 1, a byte)
    uint8_t m_pad39[3];
    float m_fUnk3C;  // +0x3c the interaction radius (State0)
    IKSerializable* m_pUnk40;  // +0x40 a CSGHotSpot: where the object hangs and the effects go
    IKSerializable* m_pUnk44;  // +0x44 a CKSoundDictionaryID (State1: sound 0)
    CTriggerStarter m_unk48;  // +0x48
    IKSerializable* m_pUnk50;  // +0x50
    float m_fUnk54;  // +0x54 the fade-out time (State1)
    float m_fUnk58;  // +0x58 runtime (Start / Restart: FLT_MAX, 0x00c4ace0)
    IKSerializable* m_pUnk5C;  // +0x5c the particle effect's data (State0; a CKParticlesEffectFxData_maybe)
    IKSerializable* m_pUnk60;  // +0x60 runtime: an effect (PostLoad / Start: 0)
    IKSerializable* m_pUnk64;  // +0x64 the explosion's data (SpawnFx)
    IKSerializable* m_pUnk68;  // +0x68 the input icon's data (State0 -> +0x6c)
    IKSerializable* m_pUnk6C;  // +0x6c runtime: an effect (PostLoad: 0; OnDeactivate stops and releases it)
    uint32_t* m_pStateTable;  // +0x70 Start: m_aStateTable
    uint8_t m_unk74;  // +0x74 the state (constructor 0xff; CKHkS08CristalKey reads it, GetInfo 0x96: state 1)
    uint8_t m_unk75;  // +0x75 the state count (constructor 0xff; Start: 2)
    uint8_t m_pad76[2];
    uint32_t m_aStateTable[4];  // +0x78 two handler pairs (Start: State0 0xbc2688, State1 0xbc2558)
};
DOTD_ASSERT_SIZE(CKHkS08CristalEmitter, 0x88);
DOTD_ASSERT_OFFSET(CKHkS08CristalEmitter, m_pUnk20, 0x20);
DOTD_ASSERT_OFFSET(CKHkS08CristalEmitter, m_pUnk24, 0x24);
DOTD_ASSERT_OFFSET(CKHkS08CristalEmitter, m_pUnk30, 0x30);
DOTD_ASSERT_OFFSET(CKHkS08CristalEmitter, m_pUnk34, 0x34);
DOTD_ASSERT_OFFSET(CKHkS08CristalEmitter, m_fUnk3C, 0x3c);
DOTD_ASSERT_OFFSET(CKHkS08CristalEmitter, m_pUnk40, 0x40);
DOTD_ASSERT_OFFSET(CKHkS08CristalEmitter, m_pUnk44, 0x44);
DOTD_ASSERT_OFFSET(CKHkS08CristalEmitter, m_unk48, 0x48);
DOTD_ASSERT_OFFSET(CKHkS08CristalEmitter, m_pUnk50, 0x50);
DOTD_ASSERT_OFFSET(CKHkS08CristalEmitter, m_fUnk54, 0x54);
DOTD_ASSERT_OFFSET(CKHkS08CristalEmitter, m_pUnk5C, 0x5c);
DOTD_ASSERT_OFFSET(CKHkS08CristalEmitter, m_pUnk64, 0x64);
DOTD_ASSERT_OFFSET(CKHkS08CristalEmitter, m_pUnk68, 0x68);
DOTD_ASSERT_OFFSET(CKHkS08CristalEmitter, m_unk74, 0x74);
DOTD_ASSERT_OFFSET(CKHkS08CristalEmitter, m_unk75, 0x75);
DOTD_ASSERT_OFFSET(CKHkS08CristalEmitter, m_pStateTable, 0x70);
DOTD_ASSERT_OFFSET(CKHkS08CristalEmitter, m_aStateTable, 0x78);
