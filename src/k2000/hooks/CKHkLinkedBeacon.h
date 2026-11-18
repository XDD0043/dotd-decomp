// CKHkLinkedBeacon.h - a beacon of a linked-beacon path (key 0x1002, vtable 0xb26cb8, size 0xf4). Original
// unit: CKHkLinkedBeacon.cpp. No XXL2 class. Field types from the Ghidra struct draft (live samples).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/fx/IKFx.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/misc/CKHkActorBase.h"
#include "k2000/services/CTriggerStarter.h"

class IKTime;

class CKHkLinkedBeacon : public CKHkActorBase {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0x40)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c3c18
        return key == 0x1002 || key == 0xd82 || key == 0x2 || key == 0x2fe || key == 0x3fe || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKHkLinkedBeacon)

    // A link record (0xc bytes, OperatorNew'd and zeroed one by one by Load, then read by LoadLinkRecord): a detector
    // whose state runs one of the beacon's actions (UpdateConditionalLinks). LVL010's beacons have none; LVL020..040's
    // name CKDetectorBase objects (key 0x270c).
    struct LinkRecord {
        IKSerializable* m_pTarget;  // +0x00 the detector (CKDetectorBase in the files)
        uint8_t m_unk4;             // +0x04 read first: the condition (0 on entering, 1 on leaving after inside, 2 inside,
                                    //       3 on leaving without having been inside)_maybe
        uint8_t m_unk5;             // +0x05 read third: the hero (dragon index) it watches; 0xfe / 0xff any
        uint8_t m_unk6;             // +0x06 read second: whether that hero must be the player-controlled one
        uint8_t m_unk7;             // +0x07 read fourth: the action (ExecuteLinkAction 0..10)
        uint8_t m_unk8;             // +0x08 read last: the action's argument (action 10: a stage number from 1)
        uint8_t m_unk9;             // +0x09 run-time: the detector was seen inside (Restart / OnActivate clear it)
        uint8_t m_padA[2];
    };

    CKHkLinkedBeacon() {}  // 0x0044bbd8 CKHkLinkedBeacon_Create: the CKHkActorBase defaults only
    ~CKHkLinkedBeacon() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0044c240 CKHkLinkedBeacon_Load
    void SetDefaultState(int32_t flag) override;  // vt+0x38 0x0044bb58 CKHkLinkedBeacon_SetDefaultState
    void Start() override;                        // vt+0x50 0x0044b788 CKHkLinkedBeacon_Start
    void Restart() override;                      // vt+0x54 0x0044bf20 CKHkLinkedBeacon_Restart
    // 0x0044af18 CKHkLinkedBeacon_ShowInputIcon_maybe (not virtual): 0 releases the input-icon effect (vt+0x58 with
    // this hook); nonzero (with the data +0xc0) acquires one and places it (InputIconFx_UpdateWorldPosition_maybe).
    void ShowInputIcon(int32_t on);
    // 0x0044c0b8 CKHkLinkedBeacon_LoadLinkRecord_maybe (this unused; the last argument is 0 at the call).
    void LoadLinkRecord(IKFile* file, LinkRecord* record, int32_t unused);

    // C2.7 sparx: the live path. The bit array's own bits (from the files / SetDefaultState / vt+0xc8, and run-time):
    // 2 finished_maybe (Restart and the hand-over skip it), 3 switching off clears bit 18, 4 the beacon drives a
    // character through a stage sequence (+0x64 / +0x60; else it is a plain way point), 5 the time-out (+0x38) and the
    // stages loop, 6 only switched on in the camera's view, 7 the arrived character faces the hero (else +0x2c), 8 / 9
    // the state presets, 10 the beacon's own sequence (+0x64) animates, 11 SetDefaultState arms it, 12 the character
    // flies the path-finding route / the arrival placement, 13 message 0x940 makes it switch on again, 14 the second
    // word of vt+0x8c, 15 / 16 the input icon (16: following the character); run-time: 17 active, 18 armed (may switch
    // on), 19 arrived, 20 / 21 hand over to the next (+0x58) / previous (+0x54) beacon on switching off, 22 the stage's
    // animation steps run, 23 the character was outside the switch-on range, 24 the beacon's own sequence is done, 25
    // the stage shown to the triggers is the current one, 26 / 27 a switch-on / switch-off is pending, 28 the stage's
    // sekens waits to start, 29 the stage is over.
    // vt+0x10 0x0044b888 CKHkLinkedBeacon_Destroy: CKHkActorBase_d82_maybe_ClearReferences 0x3f6e08 (the hook's vt+0xc0,
    // KStub_Nop_9c0bc8 here), then the stage array and the link records freed.
    void Destroy() override;
    // vt+0x1c 0x0044e2c8 CKHkLinkedBeacon_MessageProc: the actor messages 0x908..0x90f (CKHkActorBase_d82_maybe_MessageProc
    // 0x3f7148), then the beacon's 0x940 and 0x996..0x9a0 (answer 0); the answers merged.
    int32_t MessageProc(uint16_t message, void* data) override;
    // vt+0x24 0x0044b860 CKHkLinkedBeacon_RecursiveRegistration: CKHkActorBase_d82_maybe_LevelReset 0x3f6ee8 (IKHook_LevelReset
    // 0x19ab8: outside the memory-card types 4..7 the hook's node registers too).
    void RecursiveRegistration(int32_t type) override {
        if (static_cast<uint32_t>(type - 4) > 3u && m_pKGLObject != nullptr) m_pKGLObject->RecursiveRegistration(type);
    }
    int32_t Save(IKFile* /*file*/, int32_t /*type*/) override { return 1; }   // vt+0x28 0x0044b838 (CKHkActorBase's: IKHook_Save, nothing)
    // vt+0x30 0x0044b810 CKHkLinkedBeacon_PostLoad: CKHkActorBase's (IKLife_PostLoad), then 1.
    int32_t PostLoad(int32_t type) override {
        CKHkActorBase::PostLoad(type);
        return 1;
    }
    // vt+0x40 0x0044b2b0 CKHkLinkedBeacon_GetInfo: the trigger values 0xa6 (GetTriggerPropA6, an integer) and 0xa7
    // (GetTriggerPropA7, a byte); the actor base (KStub_Return1_3f7140) answers 1.
    int32_t GetInfo(struct IKInfo* info, int32_t request) override;
    void Stop() override {}    // vt+0x68 0x0044b760 CKHkLinkedBeacon_Stop (CKHkActorBase_d82_maybe_Stop 0x3f6e50: empty)
    void Pause() override {}   // vt+0x70 0x0044b738 CKHkLinkedBeacon_Pause (KStub_Nop_3f6e58)
    void Resume() override {}  // vt+0x78 0x0044b710 CKHkLinkedBeacon_Resume (KStub_Nop_3f6e60)
    // vt+0x7c 0x0044f620 CKHkLinkedBeacon_Update: an armed or active beacon with a character: the pending switches, the
    // links, then the inactive beacon's switch-on test (range +0x3c and the cone +0x48 of +0x2c, a 100 - +0x4c percent
    // chance: one Rand_Int draw) or the active one's frame: the input icon, the character brought in (path, flight or
    // placement, arrival radius +0x84), the time-out, the stage (UpdateCurrentStage) and the next one, the character's
    // facing, and the release distances to the hero (+0x40 / +0x44).
    void Update(IKTime* clock) override;
    // vt+0xa0 0x0044be70 CKHkLinkedBeacon_OnActivate: the actor base's (the active actor list), then the run-time bits
    // as Restart's end (0x800000 only among 0xe345ffff), no sekens, no path query, every link record's +9 cleared.
    void VfA0() override;
    // vt+0xa4 0x0044d838 CKHkLinkedBeacon_OnDeactivate: the actor base's, then an active beacon stops its sekens, drops
    // the hand-over bits 20 / 21 and switches off.
    void VfA4() override;
    // vt+0xc8 0x0044baf8 CKHkLinkedBeacon_vfC8: bit 18 (armed) = bit 8 (preset 0) or bit 9 (preset 1).
    void ApplyStatePreset(int32_t state) override;
    // 0x0044b3e0 CKHkLinkedBeacon_BeginLinkStage_maybe: the stage (+0xcc; -1 the beacon's own sequence +0x64) begins: its
    // start time, the previous sekens let go, the stage's sekens started (or waited for: bit 28), its animation steps.
    void BeginLinkStage(IKTime* clock);
    // 0x0044cbb8 CKHkLinkedBeacon_SwitchOn_maybe: an armed beacon with a character (and in view with bit 6) takes it
    // unless a beacon of a higher priority (+0xbc) is active (lower ones are switched off): the Sparx targets it, flies
    // to it or is placed (+0x50), the beacon's own sequence starts, the marker, trigger +0x88, the first stage.
    void SwitchOn(IKTime* clock);
    // 0x0044d518 CKHkLinkedBeacon_SwitchOff_maybe: an active beacon whose sekens still plays a line stops it and waits
    // (bit 27); else it lets the character go, stops its sekens, fires trigger +0x98, clears the marker, the sound and
    // the icon. Then a hand-over (bit 20 / 21) switches on the first armed beacon along +0x58 / +0x54.
    void SwitchOff(IKTime* clock);
    // 0x0044d908 CKHkLinkedBeacon_ExecuteLinkAction_maybe: a link record's action: 0 switch on, 1 / 2 hand over to the
    // next / previous beacon, 3 the next stage, 4 a pending switch-on cancelled, 5 / 6 switch off and disarm (6 the whole
    // chain), 7 / 8 arm (8 the whole chain), 9 take the Sparx from a beacon of the same class, 10 stage `param` - 1.
    // SwitchOn / SwitchOff / BeginLinkStage get the engine's clock.
    void ExecuteLinkAction(uint32_t action, uint32_t param);
    // 0x0044dee0 CKHkLinkedBeacon_UpdateConditionalLinks_maybe: every link record whose hero condition holds and whose
    // action suits the beacon's state runs its detector (Detect, GetDetectionType 0 / 1 / 2) and, on its condition,
    // the action.
    void UpdateConditionalLinks();
    // 0x0044eb40 CKHkLinkedBeacon_UpdateCurrentStage_maybe: one frame of the stage: the beacon's own sequence's animation
    // (steps 0 / 1 / 2: arrival, loops +0x68, near the beacon +0x6c), the stage's sekens (restarted when looping), its
    // time-out (+0x18 of the sequence), its animation steps (by sekens line with +0x15, else by the steps' end flags /
    // durations); 1 when the stage is over.
    uint8_t UpdateCurrentStage(IKTime* clock);
    // 0x009c3c90 CKHkLinkedBeacon_GetTriggerPropA6 / 0x009c3c80 _GetTriggerPropA7 (inline; GetInfo's values 0xa6 / 0xa7):
    // the stage shown to the triggers (-1 inactive; +1 unless bit 25) / bit 19 (arrived).
    int32_t GetTriggerPropA6() const {
        if ((m_bitArray & 0x20000u) == 0) return -1;
        if ((m_bitArray & 0x2000000u) != 0) return m_iStage;
        return m_iStage + 1;
    }
    uint32_t GetTriggerPropA7() const { return (m_bitArray >> 19) & 1u; }

    // The arrival of the character (Update, SwitchOn, UpdateCurrentStage inline the same code): vt+0x8c (the move updater:
    // still on the beacon's own sequence), trigger +0xa8, bit 19, the input icon, sound 0 placed at the character and
    // played.
    void Arrive();
    // The character placed for the stage (+0x50: 3 / 5 flies to the beacon at +0x70, slow / fast; 4 is put there; else
    // flies there facing +0x2c, fast with a nonzero byte).
    void PlaceCharacter();

    CVector3 m_unk20;                 // +0x20 the beacon's position (one 12-byte read, each word swapped)
    CVector3 m_unk2C;                 // +0x2c its direction (one 12-byte read): the switch-on cone's axis, the facing
    float m_fTimeOut;                 // +0x38 the active beacon's time-out (bit 5; 0 none)
    float m_unk3C;                    // +0x3c the switch-on range (character to beacon)
    float m_fReleaseNear;             // +0x40 the hero within it releases the beacon (0 none; trigger +0x90, bit 20)
    float m_fReleaseFar;              // +0x44 the hero beyond it, in the cone, releases it (0 none; bit 21)
    float m_unk48;                    // +0x48 the cone's angle in degrees (LVL010: 360, no cone)
    float m_unk4C;                    // +0x4c the switch-on chance in percent (LVL010: 100, no draw)
    uint8_t m_unk50;                  // +0x50 how the character comes (PlaceCharacter)
    uint8_t m_pad51[3];
    IKSerializable* m_unk54;          // +0x54 the previous beacon of the chain (CKHkLinkedBeacon in the files)
    IKSerializable* m_unk58;          // +0x58 the next beacon of the chain (CKHkLinkedBeacon in the files)
    int32_t m_unk5C;                  // +0x5c the count of +0x60
    IKSerializable** m_apUnk60;       // +0x60 OperatorNewArray'd references: the stages (CKLinkedBeaconSeq)
    IKSerializable* m_unk64;          // +0x64 the beacon's own sequence (CKLinkedBeaconSeq); 0 without bit 0x10 of m_bitArray
    uint8_t m_unk68;                  // +0x68 the loops of its animation step 1 (0: until the beacon is near); 0 without
                                      //       bit 0x10
    uint8_t m_pad69[3];
    float m_unk6C;                    // +0x6c the distance of its animation step 2 (near the beacon); 0.8f without bit 0x10
    float m_unk70;                    // +0x70 the flight speed of the placements 3 / 5
    uint8_t m_unk74;                  // +0x74 how the character turns once placed by bit 12 (1 to the beacon, 2 the
                                      //       path-finding route, 3 to +0x78)
    uint8_t m_pad75[3];
    CVector3 m_unk78;                 // +0x78 the point mode 3 of +0x74 faces (one 12-byte read)
    float m_fArrivalRadius;           // +0x84 the character arrives within it (horizontal; 0: SwitchOn does not test it)
    CTriggerStarter m_unk88;          // +0x88
    CTriggerStarter m_unk90;          // +0x90
    CTriggerStarter m_unk98;          // +0x98
    CTriggerStarter m_unkA0;          // +0xa0
    CTriggerStarter m_unkA8;          // +0xa8
    IKSerializable* m_unkB0;          // +0xb0
    int32_t m_unkB4;                  // +0xb4 the count of +0xb8
    LinkRecord** m_apLinks;           // +0xb8 OperatorNewArray'd record pointers
    uint8_t m_unkBC;                  // +0xbc
    uint8_t m_padBD[3];
    IKSerializable* m_unkC0;          // +0xc0
    IKSerializable* m_unkC4;          // +0xc4
    IKSerializable* m_unkC8;          // +0xc8 CKKLBCharacterSparx* (struct draft)
    // +0xcc..+0xe4 runtime (not set by Create or Load):
    int32_t m_iStage;                 // +0xcc the current stage (index in +0x60), -1 the beacon's own (+0x64)
    int32_t m_iPendingStage;          // +0xd0 the stage message 0x9a0 asked for during the beacon's own sequence (SwitchOn:
                                      //       -1; Update takes it when above 0)
    int32_t m_iAnimStep;              // +0xd4 the animation step of the stage's sequence (-1 none)
    int32_t m_iAnimLoops;             // +0xd8 the loops of step 1 (+0x68 of them)
    float m_fSwitchOnTime;            // +0xdc the clock's current time at SwitchOn (+0x38: the time-out)
    float m_fStageStartTime;          // +0xe0 the clock's current time at BeginLinkStage
    float m_fAnimStepTime;            // +0xe4 the clock's current time when the animation step started
    IKSerializable* m_pSekens;        // +0xe8 runtime: a CKSekensLauncherCpnt* (Restart stops its sekens)
    int8_t m_unkEC;                   // +0xec runtime: the path-finding query slot (AcquirePathQuery; -1 none; Restart: 0xff)
    uint8_t m_padED[3];
    IKFx* m_pInputIconFx;             // +0xf0 runtime: the input-icon effect (CKInputIconNodeFx*), or null
};
DOTD_ASSERT_SIZE(CKHkLinkedBeacon::LinkRecord, 0xc);
DOTD_ASSERT_SIZE(CKHkLinkedBeacon, 0xf4);
DOTD_ASSERT_OFFSET(CKHkLinkedBeacon, m_unk20, 0x20);
DOTD_ASSERT_OFFSET(CKHkLinkedBeacon, m_unk2C, 0x2c);
DOTD_ASSERT_OFFSET(CKHkLinkedBeacon, m_fTimeOut, 0x38);
DOTD_ASSERT_OFFSET(CKHkLinkedBeacon, m_unk3C, 0x3c);
DOTD_ASSERT_OFFSET(CKHkLinkedBeacon, m_fReleaseNear, 0x40);
DOTD_ASSERT_OFFSET(CKHkLinkedBeacon, m_fReleaseFar, 0x44);
DOTD_ASSERT_OFFSET(CKHkLinkedBeacon, m_unk48, 0x48);
DOTD_ASSERT_OFFSET(CKHkLinkedBeacon, m_unk50, 0x50);
DOTD_ASSERT_OFFSET(CKHkLinkedBeacon, m_unk54, 0x54);
DOTD_ASSERT_OFFSET(CKHkLinkedBeacon, m_unk5C, 0x5c);
DOTD_ASSERT_OFFSET(CKHkLinkedBeacon, m_apUnk60, 0x60);
DOTD_ASSERT_OFFSET(CKHkLinkedBeacon, m_unk64, 0x64);
DOTD_ASSERT_OFFSET(CKHkLinkedBeacon, m_unk68, 0x68);
DOTD_ASSERT_OFFSET(CKHkLinkedBeacon, m_unk6C, 0x6c);
DOTD_ASSERT_OFFSET(CKHkLinkedBeacon, m_unk70, 0x70);
DOTD_ASSERT_OFFSET(CKHkLinkedBeacon, m_unk74, 0x74);
DOTD_ASSERT_OFFSET(CKHkLinkedBeacon, m_unk78, 0x78);
DOTD_ASSERT_OFFSET(CKHkLinkedBeacon, m_fArrivalRadius, 0x84);
DOTD_ASSERT_OFFSET(CKHkLinkedBeacon, m_iStage, 0xcc);
DOTD_ASSERT_OFFSET(CKHkLinkedBeacon, m_fAnimStepTime, 0xe4);
DOTD_ASSERT_OFFSET(CKHkLinkedBeacon, m_pSekens, 0xe8);
DOTD_ASSERT_OFFSET(CKHkLinkedBeacon, m_unkEC, 0xec);
DOTD_ASSERT_OFFSET(CKHkLinkedBeacon, m_unk88, 0x88);
DOTD_ASSERT_OFFSET(CKHkLinkedBeacon, m_unkA8, 0xa8);
DOTD_ASSERT_OFFSET(CKHkLinkedBeacon, m_unkB0, 0xb0);
DOTD_ASSERT_OFFSET(CKHkLinkedBeacon, m_unkB4, 0xb4);
DOTD_ASSERT_OFFSET(CKHkLinkedBeacon, m_apLinks, 0xb8);
DOTD_ASSERT_OFFSET(CKHkLinkedBeacon, m_unkBC, 0xbc);
DOTD_ASSERT_OFFSET(CKHkLinkedBeacon, m_unkC0, 0xc0);
DOTD_ASSERT_OFFSET(CKHkLinkedBeacon, m_unkC8, 0xc8);
