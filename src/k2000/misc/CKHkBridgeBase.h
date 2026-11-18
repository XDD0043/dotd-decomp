// CKHkBridgeBase.h - the unregistered base of the drawbridges (key 0x9c2 "KBase9C2", vtable 0xb25360, 66 slots, size
// 0xfc): CKHkButterflyBridge (0xb42) and CKHkFoldawayBridge (0x4042) derive from it (their first own member at +0xfc).
// Original unit: CKHkBridgeBase.cpp (0x3fb460-0x3ff9b8); its SetDefaultState / SetGameState 0x3fb408 / 0x3fb420 sit at
// the end of CKHkActivator.cpp's unit. No XXL2 class; no level file holds a bridge (work/level-class-keys.json). C2.8
// port-rest R08 ported it from the code; member names are placeholders where the code does not say more.
//
// The bridge: segments (+0x88, scene nodes) that rise one after another to the raised height (+0xc8), each with two
// moving grounds (+0x90 / +0x98, CDynamicGround) switched on while it is up, and an end segment whose height runs
// between +0xd0 (lowered) and +0xcc (raised). A nine-state machine (+0x2c, the handler table +0x34 that Start fills):
//   0 lowered, 1 raising a segment (the FloatApproachAccel state +0xac), 2 raised, 3 (vt+0xf8: the derived bridge's
//   next segment up), 4 the end segment rising, 5 the end segment lowering, 6 (vt+0xfc: the next segment down), 7 a
//   segment lowering, 8 (blocked, the hero group told 0xc08).
// The messages 0x996 / 0x998 / 0x999 raise it, 0x997 toggles it (ComputeNextState); 0x93f / 0x940 attach / detach a
// hero (up to three, +0x7c). The heroes standing on it (vt+0x100: on one of its grounds) are attached while a segment
// moves down (state 7) and walked off it (state 5 / 7: ReleaseHeroesOffBridge). The four path-finding transitions
// (+0x9c..+0xa8) are open while the bridge is raised.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/CKHkActorBase.h"
#include "k2000/services/CTriggerStarter.h"

class CDynamicGround;
class CKHkS08Hero;
class CKPFGraphTransition;
class CSGMovable;
class IKTime;

class CKHkBridgeBase : public CKHkActorBase {
public:
    // vt+0x14 / +0x18 0x9c0f90 / 0x9c0f98: category 2 (hook), id 0x27.
    DOTD_CLASS_KEY(kCategoryHook, 0x27)
    // vt+0x08 0x009c0f38 CKHkBridgeBase_9c2_maybe_IsKindOfClass: 0x9c2, then the actor base's chain.
    int32_t IsKindOfClass(uint32_t key) override {
        return key == 0x9c2 || key == 0xd82 || key == 0x2 || key == 0x2fe || key == 0x3fe || key == 0xc;
    }

    // A state handler (the original's pointers to member functions, {OPD, adjust} pairs; states 3 and 6 are the virtual
    // slots +0xf8 / +0xfc, stored as offset + 1): phase 1 on enter (the previous state), 2 on leave (the next state), 0
    // every frame (returns the next state). The clock is null for the switches outside Update.
    typedef uint8_t (CKHkBridgeBase::*StateHandler)(IKTime* clock, int32_t phase, uint8_t other);
    enum { kStateCount = 9 };

    // 0x003fbdf0 CKHkBridgeBase_9c2_maybe_ConstructBase (the dead 0x3fbf48 _ConstructBase_2 copy): the actor base, then
    // no state (+0x30 / +0x31 = 0xff). The rest is what the fresh heap leaves (zero).
    CKHkBridgeBase();
    // 0x003fbf18 _Destructor (= 0x3fbdc0 _BaseDestructor; 0x3fbed0 _DeletingDestructor adds the operator delete): the
    // actor base's.
    ~CKHkBridgeBase() override {}

    // vt+0x10 0x003fbc98 CKHkBridgeBase_9c2_maybe_Destroy (Ghidra _ClearReferences): the actor base's (vt+0xc0), then
    // the segment and ground arrays freed; the two optional arrays only when +0x24 is not 0 (else just cleared).
    void Destroy() override;
    // vt+0x1c 0x003ff080 CKHkBridgeBase_9c2_maybe_MessageProc
    int32_t MessageProc(uint16_t message, void* data) override;
    // vt+0x24 0x3fbc70 _RecursiveRegistration (Ghidra _LevelReset): the actor base's (IKHook's), inherited.
    // vt+0x28 0x3fbc48 _Save: not ported (the saves are out of scope).
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x003fcd78 CKHkBridgeBase_9c2_maybe_Load
    // vt+0x30 0x3fbd98 KBase9C2_PostLoad: the actor base's (IKLife's PostLoad, 1), inherited.
    // vt+0x38 0x003fb408 KBase9C2_SetDefaultState: flag 0 clears +0xf5 and +0xf6 (the byte stores of the flag).
    void SetDefaultState(int32_t flag) override {
        if (flag != 0) return;
        m_ui8RaisedAtStart = static_cast<uint8_t>(flag);
        m_ui8Initialised = static_cast<uint8_t>(flag);
    }
    // vt+0x3c 0x003fb420 KBase9C2_SetGameState: info 1: +0xf6 cleared, +0xf5 = (game state == 0); 1 for info 1, else 0.
    int32_t SetGameState(const SApplyGameState* state) override;
    // vt+0x40 0x003fba38 KBase9C2_GetInfo: the trigger value 0x9c (0x9c0fa0 KBase9C2_GetTriggerProp9C: raised, state
    // 2), folded with the actor base's answer.
    int32_t GetInfo(IKInfo* info, int32_t request) override;
    // vt+0x50 0x003fbb90 CKHkBridgeBase_9c2_maybe_Start: the actor base's (empty), +0xfa set, the nine state handlers,
    // no hero.
    void Start() override;
    // vt+0x54 0x003fe890 CKHkBridgeBase_9c2_maybe_Restart
    void Restart() override;
    // vt+0x68 / +0x70 / +0x78 0x3fbb68 / 0x3fbb40 / 0x3fbb18 KBase9C2_Stop / Pause / Resume: the actor base's (IKHook's
    // empty 0x3f6e50 / 0x3f6e58 / 0x3f6e60), inherited.
    void Update(IKTime* clock) override;  // vt+0x7c 0x003fe138 CKHkBridgeBase_9c2_maybe_Update
    void VfA0() override;                 // vt+0xa0 0x003fe550 KBase9C2_OnActivate
    void VfA4() override;                 // vt+0xa4 0x003fe018 CKHkBridgeBase_9c2_maybe_OnDeactivate
    // vt+0xb4 0x003fbe48 CKHkBridgeBase_9c2_maybe_AttachSounds: sounds 0..2 of +0x20 attached to the node (no null
    // checks).
    void KGLObjectAttached(IKSerializable* leaf) override;

    // vt+0xf0..+0x104: pure here (the derived bridges' slots). +0xf0 / +0xf4: the bridge snapped lowered / raised (the
    // derived parts' pose); +0xf8 / +0xfc: states 3 and 6 (the next segment up / down); +0x100: whether a ground (a
    // hero's) belongs to the bridge; +0x104: not called by the base.
    virtual void OnSnappedLowered() = 0;                                         // vt+0xf0
    virtual void OnSnappedRaised() = 0;                                          // vt+0xf4
    virtual uint8_t StateNextSegmentUp(IKTime* clock, int32_t phase, uint8_t other) = 0;    // vt+0xf8 (state 3)
    virtual uint8_t StateNextSegmentDown(IKTime* clock, int32_t phase, uint8_t other) = 0;  // vt+0xfc (state 6)
    virtual uint8_t IsBridgeGround(IKSerializable* ground) = 0;                  // vt+0x100
    virtual void Vf104() = 0;                                                    // vt+0x104

    // 0x003fb668 CKHkBridgeBase_9c2_maybe_DetachHero_maybe: hero slot `slot`'s hero (if any) let go (DetachHeroFrom); 1.
    int32_t DetachHero(int32_t slot);
    // 0x003fb6f0 CKHkBridgeBase_9c2_maybe_AttachHero_maybe: `hero` attached to the bridge (mode 2), invulnerable, its
    // attached movement on; the middle of the second transition's (+0xa0) first portal's arrival box snapped to the
    // ground; a hero on the first segment's ground A is set on its place again (locked, teleported, unlocked); then the
    // hero walks to the point, facing the way from it there (vt+0xcc, 5 s). 1.
    int32_t AttachHero(CKHkS08Hero* hero);
    // 0x003fcba8 CKHkBridgeBase_9c2_maybe_AttachHeroesStandingOn_maybe (Update in state 7): every companion hero
    // standing on the bridge (vt+0x100 with its ground) that may attach to it (vt+0xe0, 2) and is not one of the three
    // goes to the first free slot and is attached; 1 when a hero stands on it, else 0.
    int32_t AttachHeroesStandingOn();
    // 0x003fd648 CKHkBridgeBase_9c2_maybe_DetachAllHeroes_maybe (the inlined copies in Restart, OnDeactivate, the states
    // and ComputeNextState are the same code): the three slots let go.
    void DetachAllHeroes();
    // 0x003fd760 CKHkBridgeBase_9c2_maybe_ReleaseHeroesOffBridge_maybe (states 5 and 7): each attached hero off the
    // bridge's grounds that is flying (+0x354 bit 0) is put back at the second transition's arrival point (snapped) and
    // let go; the others walk on (vt+0xd0) and are let go when they arrive.
    void ReleaseHeroesOffBridge(IKTime* clock);
    // 0x003fc2b0 CKHkBridgeBase_9c2_maybe_SnapToLowered_maybe: every segment at the origin (grounds off, unless the life
    // sleeps, +0x0c bit 2), the end segment at +0xd0, vt+0xf0, the four transitions closed.
    void SnapToLowered();
    // 0x003fc4f8 CKHkBridgeBase_9c2_maybe_SnapToRaised_maybe: every segment at the raised height (grounds on, unless
    // bit 2), the end segment at +0xcc, vt+0xf4, the four transitions open.
    void SnapToRaised();
    // 0x003feba0 CKHkBridgeBase_9c2_maybe_ComputeNextState_maybe: the state an event leads to (0 / 2 raise, 1 / 2 toggle;
    // the heroes let go when a lowered or moving-down bridge starts up; the transitions +0x9c / +0xa4 / +0xa8 closed on a
    // toggle).
    uint8_t ComputeNextState(uint8_t event);

    // The states (the handler table's entries 0, 1, 2, 4, 5, 7, 8).
    uint8_t State0Lowered(IKTime* clock, int32_t phase, uint8_t other);      // 0x003fcad8 _State0_Lowered_maybe
    uint8_t State1RaiseSegment(IKTime* clock, int32_t phase, uint8_t other); // 0x003fbfa0 _State1
    uint8_t State2Raised(IKTime* clock, int32_t phase, uint8_t other);       // 0x003fc760 _State2_Raised_maybe
    uint8_t State4RaiseEnd(IKTime* clock, int32_t phase, uint8_t other);     // 0x003fc7d0 _State4
    uint8_t State5LowerEnd(IKTime* clock, int32_t phase, uint8_t other);     // 0x003fd9c8 _State5_Lower_maybe
    uint8_t State7LowerSegment(IKTime* clock, int32_t phase, uint8_t other); // 0x003fdbc0 _State7_MoveSegments_maybe
    uint8_t State8Blocked(IKTime* clock, int32_t phase, uint8_t other);      // 0x003fca10 _State8_maybe

    // The inlined state switch (MessageProc, Restart, OnActivate): the current state left with `next`, `next` stored and
    // entered with the previous one (0xff: none).
    void SwitchState(uint8_t next);

    IKSerializable* m_pSoundDictionary;  // +0x20 a CKSoundDictionaryID (sounds 0..2)
    uint32_t m_ui32NbExtra;              // +0x24 the count of the two optional arrays (+0x8c / +0x94)
    uint8_t m_ui8NbSegments;             // +0x28
    uint8_t m_ui8CurrentSegment;         // +0x29 the segment moving (states 1 / 7)
    // +0x2c..+0x31 the state machine: the handler table (the Load points it at +0x34), the current state (0xff none),
    // the count (the Load: 9).
    StateHandler* m_pStateTable;   // +0x2c
    uint8_t m_ui8State;            // +0x30
    uint8_t m_ui8NbStates;         // +0x31
    StateHandler m_aStates[kStateCount];  // +0x34 (8 bytes each on the PS3) Start
    CKHkS08Hero* m_apHeroes[3];           // +0x7c the attached heroes
    CSGMovable** m_apSegments;            // +0x88 Mem_AllocAligned16(count x 0x24): one reference each (the 0x24 stride
                                          //       is never used)
    IKSerializable** m_apExtraA;          // +0x8c Mem_AllocAligned16(+0x24 x 0x24): references
    CDynamicGround** m_apGroundsA;        // +0x90 one per segment
    IKSerializable** m_apExtraB;          // +0x94 references (+0x24 of them; the butterfly bridge reads them in pairs)
    CDynamicGround** m_apGroundsB;        // +0x98 one per segment
    CKPFGraphTransition* m_apTransitions[4];  // +0x9c (may be null) open while raised
    float m_aSegmentMotion[5];            // +0xac FloatApproachAccel state {target, top speed, speed, acceleration,
                                          //       current}: the moving segment's height (states 1 / 7)
    float m_fTopSpeed;                    // +0xc0
    float m_fAcceleration;                // +0xc4
    float m_fRaisedHeight;                // +0xc8 a raised segment's height (z)
    float m_fEndRaised;                   // +0xcc the end segment's raised height (y)
    float m_fEndLowered;                  // +0xd0 the end segment's lowered height (y)
    float m_fEndCurrent;                  // +0xd4
    float m_fEndSpeed;                    // +0xd8
    CTriggerStarter m_tsRaised;           // +0xdc queued when the end segment is up (state 4)
    CTriggerStarter m_tsUnk0e4;           // +0xe4 (read third)
    CTriggerStarter m_tsUnk0ec;           // +0xec (read second)
    uint8_t m_ui8Raised;                  // +0xf4 SnapToRaised / state 4's leave 1, SnapToLowered / state 5's leave 0
    uint8_t m_ui8RaisedAtStart;           // +0xf5 OnActivate / Restart snap raised (SetDefaultState / SetGameState)
    uint8_t m_ui8Initialised;             // +0xf6 OnActivate / Restart done once
    uint8_t m_ui8OneShot;                 // +0xf7 (Load) state 1's leave locks the bridge (+0xf8)
    uint8_t m_ui8Locked;                  // +0xf8 (Load) the messages no longer switch states
    uint8_t m_ui8NotifyHeroGroup;         // +0xf9 (Load) the hero group is told 0xc07 / 0xc08
    uint8_t m_ui8HeroGroupNotified;       // +0xfa the hero group was told 0xc07 (Start sets it)
    uint8_t m_ui8Unk0fb;                  // +0xfb message 0x999 sets it; the snaps and state 8 clear it
};
DOTD_ASSERT_OFFSET(CKHkBridgeBase, m_pSoundDictionary, 0x20);
DOTD_ASSERT_OFFSET(CKHkBridgeBase, m_ui32NbExtra, 0x24);
DOTD_ASSERT_OFFSET(CKHkBridgeBase, m_ui8NbSegments, 0x28);
DOTD_ASSERT_OFFSET(CKHkBridgeBase, m_ui8CurrentSegment, 0x29);
DOTD_ASSERT_OFFSET(CKHkBridgeBase, m_pStateTable, 0x2c);
DOTD_ASSERT_OFFSET(CKHkBridgeBase, m_ui8State, 0x30);
DOTD_ASSERT_OFFSET(CKHkBridgeBase, m_ui8NbStates, 0x31);
DOTD_ASSERT_OFFSET(CKHkBridgeBase, m_aStates, 0x34);
// Past the handler table the PS3 offsets hold only where a pointer to member function is 8 bytes (the PS3's pair);
// a 32-bit MSVC one is 4, so the remaining offsets are not asserted: +0x7c heroes, +0x88..+0x98 arrays, +0x9c
// transitions, +0xac motion, +0xc0..+0xd8 floats, +0xdc / +0xe4 / +0xec starters, +0xf4..+0xfb bytes, size 0xfc.
