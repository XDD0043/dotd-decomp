// CKHkSequenceMgr.h - a hook that plays sequences of steps (key 0x18c2, vtable 0xb27310, size 0x140).
// Original unit: CKHkSequenceMgr.cpp. No XXL2 class. The nested record names follow the Ghidra helper
// names (LoadSequenceEntry_maybe, LoadObjectRefRecord_maybe, LoadStepParamsRecord_maybe); the field names
// are ours (C2.1 ported the constructor and Load, C2.8 the engine: StartSequence, Update, UpdateStep, the
// input answers and icons, StopCurrentSequence).
//
// A sequence entry is one step: the manager's node plays the entry's animation (record A), each hero its own
// (records B / C, dragons 0 / 1) and each manager item (+0x30) the animation of the entry's record of the same
// index, all attached to hot spots. A step of type 1 or 3 waits for an input (the action +0x78) inside its input
// window (+0x88), showing a button icon; type 0 / 3 ends with the actor's animation (+0xa8: -1 none, 0 the node,
// 1-2 a hero, 3+ an item); type 2 ends when its window closes. A listener (+0x138, the golem QTE phase) is asked
// through message 0x407 at every decision (SListenerMsg).
#pragma once

class AnimBlendSlot;
class CSGLeaf;
class CSGBranch;
class IKFx;
class IKTime;
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/misc/CKHkActorBase.h"
#include "k2000/services/CTriggerStarter.h"
#include "k2000/util/TVector.h"

class CKHkSequenceMgr : public CKHkActorBase {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0x63)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c40d8
        return key == 0x18c2 || key == 0xd82 || key == 0x2 || key == 0x2fe || key == 0x3fe || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKHkSequenceMgr)
    // vt+0x78 0x00462848 CKHkSequenceMgr_Resume: the actor base's (KStub_Nop_3f6e60), then with +0xd4 bit 0 (a
    // sequence running) the game manager's flag 0x10000000 (+0x64) set again.
    void Resume() override;
    // vt+0x40 0x00462930 CKHkSequenceMgr_GetInfo: the trigger values 0x15e (+0xd4 bit 0) and 0x15f (+0xec).
    int32_t GetInfo(IKInfo* info, int32_t request) override;

    // The data of message 0x407 the manager sends its listener (+0x138): the sender, the request and its data. PS3 words
    // +0x00 / +0x04 / +0x08. The requests: 0 the next entry (SNextQuery), 1 a hero to set up (SHeroQuery), 2 an item's
    // node (SItemQuery), 3 the entry's camera and node (SCameraQuery), 4 the step ended (a byte: 0 keeps it running),
    // 5 the icon placement (+0xfc), 6 an item's hot spot (SHotSpotQuery), 7 a wrong input counts (a byte, 1).
    struct SListenerMsg {
        IKSerializable* m_pSender;  // +0x00
        uint32_t m_ui32Request;     // +0x04
        void* m_pData;              // +0x08
    };
    struct SNextQuery {             // request 0 (Update)
        int32_t m_i32Next;          // +0x00 the next entry: the entry's +0x64 (+0x68 failed); -1 the following, -2 the end
        int32_t m_i32Current;       // +0x04 the entry that ended (+0xe8)
        uint8_t m_ui8Failed;        // +0x08 UpdateStep's failed flag
    };
    struct SHeroQuery {             // request 1 (SetupHeroesForSequence)
        IKSerializable* m_pHero;    // +0x00 the hero of the record (dragon index)
        uint8_t m_ui8Play;          // +0x04 1: the hero plays the record
    };
    struct SItemQuery {             // request 2 (StartActorAnims)
        IKSerializable* m_pNode;    // +0x00 the item's node (+0x00 of the item)
        AnimBlendSlot* m_pSlot;     // +0x04 0: the node's own animation, else this blend slot
        uint32_t m_ui32Word;        // +0x08 the item's +0x08
        uint8_t m_ui8Play;          // +0x0c 1 (0 when there is no node)
    };
    struct SCameraQuery {           // request 3 (BeginEntryAnimAndCamera)
        IKSerializable* m_pCamera;  // +0x00 the manager's camera (+0x4c)
        IKSerializable* m_pNode;    // +0x04 the manager's node
        uint8_t m_ui8Play;          // +0x08 1: the node plays the entry's animation and the camera is switched to
    };
    struct SHotSpotQuery {          // request 6 (AttachActorToHotSpot)
        IKSerializable* m_pNode;    // +0x00 the item's node
        int32_t m_i32HotSpot;       // +0x04 the hot spot index
        uint32_t m_unk08;           // +0x08 not set
        IKSerializable* m_pParent;  // +0x0c out: a branch to attach to (0)
        IKSerializable* m_pHotSpot; // +0x10 out: a hot spot to attach the node's volume to (0)
    };

    // 0x10 bytes: a time window of a step, tested by CheckStepWindow 0x461178 against the time since the step started
    // (+0xf0): mode 0 [start, duration), 1 [duration - start, duration), 2 [start, start + length).
    struct StepWindow {
        uint8_t m_ui8Mode;         // +0x00
        uint8_t m_pad1[3];
        float m_fStart;            // +0x04
        float m_fLength;           // +0x08
        uint8_t m_ui8Fired;        // +0x0c set when the window held (CheckStepWindow), cleared by StartSequence
        uint8_t m_padD[3];
    };

    // 0x1c bytes; read by 0x004665b8 CKHkSequenceMgr_LoadObjectRefRecord_maybe. An animation record: a dictionary whose
    // first word the actor plays.
    struct ObjectRefRecord {
        uint8_t m_unk0;            // +0x00 read last; without a dictionary: 1 hides the actor (and attaches a hero)
        uint8_t m_pad1[3];
        IKSerializable* m_pRef;    // +0x04 a CAnimationDictionary (its first word is played)
        float m_fBlend;            // +0x08 > 0: crossfaded over this many seconds, else cut
        uint8_t m_ui8Loop;         // +0x0c the animation keeps running past its end
        uint8_t m_padD[3];
        int32_t m_i32Target;       // +0x10 what the actor is attached to: -1 / 0 the node, 1-2 a hero, 3+ an item
        int32_t m_i32HotSpot;      // +0x14 the target's hot spot (-1: the target itself)
        uint8_t m_ui8Playing;      // +0x18 run time (never loaded): the record plays this step
        uint8_t m_pad19[3];
        int32_t Load(IKFile* file, int32_t type);
    };

    // 0x1c bytes (+0x6c of an entry); read with the input window by 0x00465ad0 CKHkSequenceMgr_LoadStepParamsRecord_maybe.
    struct StepParams {
        uint8_t m_unk0;            // +0x00 the step type: 0 animation, 1 input, 2 window, 3 input while the animation runs
        uint8_t m_pad1[3];
        uint32_t m_unk4;           // +0x04
        uint32_t m_unk8;           // +0x08
        uint32_t m_unkC;           // +0x0c the action to press (2..8; UpdateStep reads its low byte)
        uint32_t m_unk10;          // +0x10 the presses needed (+0xf4 / +0xf8)
        uint8_t m_unk14;           // +0x14 the icon is on the screen (+0x109)
        uint8_t m_pad15[3];
        uint32_t m_unk18;          // +0x18 the icon's input sequence (CKInputIconFxData +0x0c)
    };

    // 0x18 bytes, the elements of SequenceEntry +0x60: a sound played while its window holds.
    struct EntryItem {
        IKSerializable* m_pRef;    // +0x00 a CKSoundDictionaryID (its sound 0)
        StepWindow m_window;       // +0x04 (Load: mode 0, start 0, length 1.0f: the TOC float at +0x56fc)
        uint32_t m_unk14;          // +0x14
    };

    // 0xb4 bytes, the elements of +0x24 (stored inline in the vector's block).
    struct SequenceEntry {
        float m_unk0;                          // +0x00 the animation speed
        float m_unk4;                          // +0x04 the speed of a type 3 step whose inputs are done
        ObjectRefRecord m_recA;                // +0x08 the manager's node
        ObjectRefRecord m_recB;                // +0x24 hero 0
        ObjectRefRecord m_recC;                // +0x40 hero 1
        TVector<ObjectRefRecord, 1>* m_pvRecords;  // +0x5c Mem_CallocAligned16(1, 0xc): one per manager item
        TVector<EntryItem, 1>* m_pvItems;      // +0x60 Mem_CallocAligned16(1, 0xc)
        uint32_t m_unk64;                      // +0x64 the next entry (-1 the following one, -2 the end)
        uint32_t m_unk68;                      // +0x68 the next entry when the step failed
        StepParams m_stepParams;               // +0x6c
        StepWindow m_inputWindow;              // +0x88 the input window (fired: the window was entered)
        StepWindow m_triggerWindow;            // +0x98 the +0x50 starters fire once in it
        int32_t m_unkA8;                       // +0xa8 the actor whose animation ends the step (ActorRecord)
        CKHkSequenceMgr* m_pOwner;             // +0xac
        uint8_t m_unkB0;                       // +0xb0
        uint8_t m_unkB1;                       // +0xb1 the dragon whose player answers (2: either)
        uint8_t m_padB2[2];
        // 0x00462f60 CKHkSequenceMgr_InitSequenceEntry_maybe
        void Init(CKHkSequenceMgr* owner);
        // 0x004667a0 CKHkSequenceMgr_LoadSequenceEntry_maybe
        int32_t Load(IKFile* file, int32_t type);
        // 0x00465ad0 CKHkSequenceMgr_LoadStepParamsRecord_maybe: the step parameters and the input window.
        void LoadStepParams(IKFile* file, int32_t type);
        // The animation record of actor `index` (CheckStepWindow's table: 0 A, 1 B, 2 C, 3+ the records).
        ObjectRefRecord* ActorRecord(int32_t index);
    };

    // 0x18 bytes, the elements of +0x30 (only +0x00..+0x0b are written by the Load).
    struct MgrItem {
        IKSerializable* m_pRef;    // +0x00 reference: the item's node (a listener may replace it)
        uint8_t m_unk4;            // +0x04 the node comes from the listener (Start forgets it)
        uint8_t m_pad5[3];
        uint32_t m_unk8;           // +0x08
        AnimBlendSlot* m_pSlot;    // +0x0c run time: the blend slot that animates the node (0: the node itself)
        CSGBranch* m_pSavedParent; // +0x10 run time: the node's parent before the sequence attached it
        CMatrix34* m_pSavedMatrix; // +0x14 run time: its modelling matrix then (RwMatrixCreate)
    };

    // 0x14 bytes (OperatorNew): two references and one reference per +0x30 item.
    struct RefGroup {
        IKSerializable* m_pRef0;           // +0x00 a CKMarkedFX (the heroes' marks)
        IKSerializable* m_pRef4;           // +0x04 read first: a CKMarkedFX (the node's marks)
        TVector<IKSerializable*, 1> m_vRefs;  // +0x08 CKMarkedFX, one per item
    };

    // 0x00463600 CKHkSequenceMgr_Create (inlined constructor, the same as 0x462600
    // CKHkSequenceMgr_Construct): the three vectors empty with capacity 1.
    CKHkSequenceMgr() {
        m_vEntries.m_pBlock = nullptr;
        m_vEntries.m_ui32NbElt = 1;
        m_vEntries.m_ui32NbUsedElt = 0;
        m_vItems.m_ui32NbElt = 1;
        m_vItems.m_pBlock = nullptr;
        m_vItems.m_ui32NbUsedElt = 0;
        m_vGroups.m_ui32NbElt = 1;
        m_vGroups.m_ui32NbUsedElt = 0;
        m_vGroups.m_pBlock = nullptr;
        // +0xd4: Resume 0x462848 tests bit 0 (set: game manager flag 0x10000000, which keeps the HUD hidden for that
        // frame) on the first frame after every pause. Every store to +0xd4 in the EBOOT is a lbzu/stb pair (scan of
        // the 0xd4 accesses: Start, Restart, OnActivate, MessageProc, StartSequenceWithListener, UpdateStep, Update,
        // AbortForOwner and the dead ResetRuntimeState / StartSequenceIfIdle; no plain store, none in Create
        // 0x463600); in LVL010 only Start ran before the first resume (breath2 calls.jsonl), and it clears the low
        // nibble only for a manager without +0xc bit 2, which LVL010's three all have (the fill scan finds +0xd4..+0xfc
        // unset on all three). The original reads its fresh heap there, 0 (work/fill_test.py breath2 with fills ff /
        // 3f: the HUD hidden one frame after each pause; DOTD_FILL_ZERO=CKHkSequenceMgr:d4-d8 removes it).
        m_unkD4 = 0;
    }
    // 0x00463100 CKHkSequenceMgr_Destructor (= 0x4631c8 _BaseDestructor, 0x463290 _DeletingDestructor): the three
    // vector blocks freed and emptied (groups +0x3c, items +0x30, entries +0x24; the entries' own vectors and the groups
    // are freed by Destroy), then the actor base's.
    ~CKHkSequenceMgr() override;
    // vt+0x10 0x00462728 CKHkSequenceMgr_Destroy: the actor base's (vt+0xc0, FreeBuffers), then every group (+0x3c) and
    // the group +0x48: its reference block freed, the group deleted (the +0x3c block keeps the stale pointers).
    void Destroy() override;
    // vt+0xc0 0x00464268 CKHkSequenceMgr_FreeBuffers_maybe: each entry, last first: its two vectors (records +0x5c, items
    // +0x60) freed and emptied and the vector structs freed, +0xa8 = 0; then the entry block freed and emptied.
    void VfC0() override;

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00466e38 CKHkSequenceMgr_Load
    // vt+0x30 0x00462548 CKHkSequenceMgr_PostLoad: the actor base's, +0x11c = 0, and for the level type the four
    // bytes +0x13c..+0x13f = 0.
    int32_t PostLoad(int32_t type) override {
        CKHkActorBase::PostLoad(type);
        m_pGround = nullptr;
        if (type == K_LEVEL_PLATEFORMS) {
            m_unk13c[3] = 0;
            m_unk13c[0] = 0;
            m_unk13c[2] = 0;
            m_unk13c[1] = 0;
        }
        return 1;
    }
    void Start() override;  // vt+0x50 0x00465da0 CKHkSequenceMgr_Start
    // vt+0x54 0x004661d0 CKHkSequenceMgr_Restart: +0x134 = 0; an enabled manager (flag bit 2 clear) stops its running
    // sequence and resets its runtime as Start does; the icon sets released when the controlled hero count changed
    // (+0xe4); every entry's marked FX (its group's +0x00 / +0x04 and the first item-count references) reset.
    void Restart() override;
    // vt+0x68 0x00462520 CKHkSequenceMgr_Stop: the actor base's (KStub: IKHook's empty Stop).
    void Stop() override {}
    // vt+0x7c 0x0046a6c8 CKHkSequenceMgr_Update
    void Update(IKTime* clock) override;
    // vt+0x1c 0x00465898 CKHkSequenceMgr_MessageProc: the actor messages, then 0x996 (start the sequence at entry 0
    // unless one runs), 0x940 (stop it, ended: +0x130; the listener told 0x940 too and forgotten), 0x997 (stop it), 0x998
    // (the placement +0x12c for the next entry).
    int32_t MessageProc(uint16_t message, void* data) override;
    void VfA0() override;  // vt+0xa0 0x00465f18 CKHkSequenceMgr_OnActivate_maybe
    void VfA4() override;  // vt+0xa4 0x00463f90 CKHkSequenceMgr_OnDeactivate
    // 0x00460b28 CKHkSequenceMgr_ReleaseIconSet_maybe: the icon effect of player `which` (0 / 1: +0xd8 / +0xdc) stopped
    // and released (vt+0x58), its data's effect (+0xb8 / +0xbc: the answer flash) released (vt+0x54); both forgotten.
    void ReleaseIconSet(int32_t which);
    void DetachHeroes();    // 0x004621e0 CKHkSequenceMgr_DetachHeroes_maybe
    // 0x004657c0 CKHkSequenceMgr_StartSequenceWithListener_maybe: with entries (+0x2c count), the listener (+0x138) and
    // the arguments (+0xe8) kept, the sequence started (StartSequence 0x465348) and +0xd4 bit 0 set (a sequence runs).
    void StartSequenceWithListener(IKSerializable* listener, IKTime* clock, int32_t index);
    // 0x00463ef8 CKHkSequenceMgr_AbortForOwner_maybe: when `owner` is the listener, the running sequence stopped
    // (StopCurrentSequence 0x463690), the heroes detached, +0xd4 bits 0-1 cleared, no listener, no sequence (+0xe8 -1).
    void AbortForOwner(IKSerializable* owner);

    // ---- C2.8 sequence: the engine (CKHkSequenceMgr.cpp) ----
    // 0x00465348 CKHkSequenceMgr_StartSequence_maybe: entry +0xe8 starts at the clock's time: its windows and sounds
    // rearmed, the presses needed (+0xf4 / +0xf8), the node, items and heroes animated and attached, the ground under the
    // node kept (+0x11c / +0x120), then the first frame of the step's animation (AdvanceStepAnim).
    void StartSequence(IKTime* clock);
    // 0x00463690 CKHkSequenceMgr_StopCurrentSequence_maybe: the step's sounds stopped, the items put back under their old
    // parents, the heroes shown, put at their body hot spot and detached, the camera owner released, the marked FX
    // stopped (flagged channels) and the icon sets released.
    void StopCurrentSequence();
    // 0x00469960 CKHkSequenceMgr_UpdateStep_maybe: 1 when the step ended (`failed`: it ended by a wrong input or the
    // window closing with no input).
    uint8_t UpdateStep(IKTime* clock, uint8_t* failed);
    // 0x00461050 CKHkSequenceMgr_IsStepForPlayer_maybe / 0x00461178 CKHkSequenceMgr_CheckStepWindow_maybe
    uint8_t IsStepForPlayer(int32_t player);
    uint8_t CheckStepWindow(IKTime* clock, StepWindow* window);
    // 0x00468f10 CKHkSequenceMgr_OnCorrectInput_maybe / 0x00467bc8 CKHkSequenceMgr_OnWrongInput_maybe /
    // 0x00468530 CKHkSequenceMgr_UpdateButtonIcons_maybe (player 0 / 1)
    void OnCorrectInput(int32_t player);
    void OnWrongInput(int32_t player);
    void UpdateButtonIcons(int32_t player);
    // 0x004644a8 _BeginEntryAnimAndCamera_maybe, 0x00464f78 _StartActorAnims_maybe, 0x00464b38
    // _SetupHeroesForSequence_maybe, 0x00464858 _AttachActorToHotSpot_maybe, 0x004640f0 _AdvanceStepAnim_maybe,
    // 0x00461658 _UpdateCameraFromHotSpots_maybe, 0x00461960 _AdvanceAttachedHeroesAnim_maybe, 0x00462d48
    // _AdvanceStepObjectsAnim_maybe, 0x00462078 _UpdateSoundTriggers_maybe
    void BeginEntryAnimAndCamera();
    void StartActorAnims();
    void SetupHeroesForSequence();
    void AttachActorToHotSpot(CSGLeaf* actor, int32_t target, int32_t hotSpot);
    void AdvanceStepAnim(IKTime* clock);
    void UpdateCameraFromHotSpots();
    void AdvanceAttachedHeroesAnim(float dt);
    void AdvanceStepObjectsAnim(float dt);
    void UpdateSoundTriggers(IKTime* clock);
    SequenceEntry& CurrentEntry() { return m_vEntries.m_pBlock[m_unkE8]; }

    IKSerializable* m_unk20;                // +0x20 reference: a CKSoundDictionaryID (0 a step's start, 1 a wrong input)
    TVector<SequenceEntry, 1> m_vEntries;   // +0x24
    TVector<MgrItem, 1> m_vItems;           // +0x30
    TVector<RefGroup*, 1> m_vGroups;        // +0x3c one per entry
    RefGroup* m_pGroup48;                   // +0x48 its +0x08 references are CKMarkedTrigger
    IKSerializable* m_unk4c;                // +0x4c reference: the sequence's camera (an IKCamera)
    CTriggerStarter m_unk50;                // +0x50 the trigger window of a step / its end
    CTriggerStarter m_unk58;                // +0x58 a step ended (not failed)
    CTriggerStarter m_unk60;                // +0x60 a step failed
    CTriggerStarter m_unk68;                // +0x68 a step ended
    CTriggerStarter m_unk70;                // +0x70 a wrong input
    CTriggerStarter m_unk78;                // +0x78 a correct input (the last one needed)
    CTriggerStarter m_unk80;                // +0x80 the input window closed without the input
    float m_unk88;                          // +0x88 every Load: 1.0f (type 0 then reads it): the world icon's size x
    float m_unk8c;                          // +0x8c every Load: 1.0f: y
    float m_unk90;                          // +0x90 every Load: 0.1f: the screen icon's size x
    float m_unk94;                          // +0x94 every Load: 0.1f: y
    float m_unk98[3];                       // +0x98 every Load: 0.5f, 0.2f, 0 (type 0: one 12-byte read): the screen icon's position
    IKSerializable* m_unkA4;                // +0xa4 reference: the icon data (CKInputIconFxData) for one player
    IKSerializable* m_unkA8;                // +0xa8 reference: player 0's of two
    IKSerializable* m_unkAC;                // +0xac reference: player 1's of two
    IKSerializable* m_unkB0;                // +0xb0 reference: the correct answer's effect data
    IKSerializable* m_unkB4;                // +0xb4 reference: the wrong answer's effect data
    IKFx* m_apIconDataFx[2];                // +0xb8 the answer flash effects of players 0 / 1 (from +0xb0 / +0xb4)
    IKSerializable* m_apUnkC0[5];           // +0xc0 one contiguous read of 5 references: CSGHotSpot (camera position,
                                            // target, focal, roll; +0xd0 the icon's place)
    uint8_t m_unkD4;                        // +0xd4 runtime (Start keeps its high nibble): bit 0 a sequence runs, 1 the
                                            // camera is not taken, 2 the input window does not close the step, 3 a
                                            // dragon switch is pending
    uint8_t m_padD5[3];
    IKFx* m_apIconFx[2];                    // +0xd8 / +0xdc runtime: the button icon effects of players 0 / 1
    uint8_t m_unkE0;                        // +0xe0 runtime
    uint8_t m_unkE1;                        // +0xe1 runtime
    uint8_t m_padE2[2];
    uint32_t m_unkE4;                       // +0xe4 runtime: the controlled hero count (GetControlledHeroCount)
    int32_t m_unkE8;                        // +0xe8 runtime: the running sequence's index, -1 none
    uint32_t m_unkEC;                       // +0xec runtime: the entry of the last update (trigger value 0x15f)
    float m_unkF0;                          // +0xf0 runtime: the clock's time when the step started
    int32_t m_unkF4;                        // +0xf4 runtime: player 0's presses still needed (-1: failed)
    int32_t m_unkF8;                        // +0xf8 runtime: player 1's
    CVector3 m_v3IconPosition;              // +0xfc runtime: the icon's position (the listener's request 5 data)
    uint8_t m_ui8IconAlpha;                 // +0x108 runtime (0xff)
    uint8_t m_ui8IconOnScreen;              // +0x109 runtime: the entry's +0x80
    uint8_t m_pad10a[2];
    float m_afIconSize[2];                  // +0x10c runtime: +0x88 / +0x8c, or +0x90 / +0x94 on the screen
    uint8_t m_unk114;                       // +0x114 runtime: 0 (UpdateButtonIcons)
    uint8_t m_pad115[3];
    uint8_t m_unk118;                       // +0x118 runtime: the step's sound played
    uint8_t m_pad119[3];
    IKSerializable* m_pGround;              // +0x11c runtime: the moving ground under the node (PostLoad 0x462548 clears it)
    CVector3 m_v3GroundPoint;               // +0x120 runtime: the node's point on it
    // +0x12c runtime: message 0x998's object (its first data word); read as {+0x04 position, +0x10 quaternion}: the layout
    // of a CKMarkerBeacon (_maybe; the class the script passes is not checked).
    const IKSerializable* m_pPlacement;
    uint8_t m_unk130;                       // +0x130 runtime: the sequence ended
    uint8_t m_unk131;                       // +0x131 runtime (Start: 1): no step failed
    uint8_t m_pad132[2];
    float m_unk134;                         // +0x134 runtime (Start: 0): the HUD stays hidden while above 0 (1.0 while running)
    IKSerializable* m_unk138;               // +0x138 runtime (Start: 0): the listener (a CKGolemPhaseQTE)
    uint8_t m_unk13c[4];                    // +0x13c runtime (PostLoad clears the four bytes)
};
DOTD_ASSERT_SIZE(CKHkSequenceMgr, 0x140);
DOTD_ASSERT_SIZE(CKHkSequenceMgr::SListenerMsg, 0xc);
DOTD_ASSERT_SIZE(CKHkSequenceMgr::StepWindow, 0x10);
DOTD_ASSERT_SIZE(CKHkSequenceMgr::ObjectRefRecord, 0x1c);
DOTD_ASSERT_SIZE(CKHkSequenceMgr::StepParams, 0x1c);
DOTD_ASSERT_SIZE(CKHkSequenceMgr::EntryItem, 0x18);
DOTD_ASSERT_SIZE(CKHkSequenceMgr::SequenceEntry, 0xb4);
DOTD_ASSERT_SIZE(CKHkSequenceMgr::MgrItem, 0x18);
DOTD_ASSERT_SIZE(CKHkSequenceMgr::RefGroup, 0x14);
DOTD_ASSERT_OFFSET(CKHkSequenceMgr::ObjectRefRecord, m_ui8Playing, 0x18);
DOTD_ASSERT_OFFSET(CKHkSequenceMgr::SHotSpotQuery, m_pHotSpot, 0x10);
DOTD_ASSERT_OFFSET(CKHkSequenceMgr::SItemQuery, m_ui8Play, 0x0c);
DOTD_ASSERT_OFFSET(CKHkSequenceMgr::SequenceEntry, m_recB, 0x24);
DOTD_ASSERT_OFFSET(CKHkSequenceMgr::SequenceEntry, m_pvRecords, 0x5c);
DOTD_ASSERT_OFFSET(CKHkSequenceMgr::SequenceEntry, m_stepParams, 0x6c);
DOTD_ASSERT_OFFSET(CKHkSequenceMgr::SequenceEntry, m_inputWindow, 0x88);
DOTD_ASSERT_OFFSET(CKHkSequenceMgr::SequenceEntry, m_triggerWindow, 0x98);
DOTD_ASSERT_OFFSET(CKHkSequenceMgr::SequenceEntry, m_unkA8, 0xa8);
DOTD_ASSERT_OFFSET(CKHkSequenceMgr::SequenceEntry, m_unkB1, 0xb1);
DOTD_ASSERT_OFFSET(CKHkSequenceMgr, m_unk20, 0x20);
DOTD_ASSERT_OFFSET(CKHkSequenceMgr, m_vEntries, 0x24);
DOTD_ASSERT_OFFSET(CKHkSequenceMgr, m_vItems, 0x30);
DOTD_ASSERT_OFFSET(CKHkSequenceMgr, m_vGroups, 0x3c);
DOTD_ASSERT_OFFSET(CKHkSequenceMgr, m_pGroup48, 0x48);
DOTD_ASSERT_OFFSET(CKHkSequenceMgr, m_unk4c, 0x4c);
DOTD_ASSERT_OFFSET(CKHkSequenceMgr, m_unk50, 0x50);
DOTD_ASSERT_OFFSET(CKHkSequenceMgr, m_unk80, 0x80);
DOTD_ASSERT_OFFSET(CKHkSequenceMgr, m_unk88, 0x88);
DOTD_ASSERT_OFFSET(CKHkSequenceMgr, m_unk98, 0x98);
DOTD_ASSERT_OFFSET(CKHkSequenceMgr, m_unkA4, 0xa4);
DOTD_ASSERT_OFFSET(CKHkSequenceMgr, m_unkB4, 0xb4);
DOTD_ASSERT_OFFSET(CKHkSequenceMgr, m_apUnkC0, 0xc0);
DOTD_ASSERT_OFFSET(CKHkSequenceMgr, m_unkF0, 0xf0);
DOTD_ASSERT_OFFSET(CKHkSequenceMgr, m_v3IconPosition, 0xfc);
DOTD_ASSERT_OFFSET(CKHkSequenceMgr, m_ui8IconAlpha, 0x108);
DOTD_ASSERT_OFFSET(CKHkSequenceMgr, m_afIconSize, 0x10c);
DOTD_ASSERT_OFFSET(CKHkSequenceMgr, m_unk114, 0x114);
DOTD_ASSERT_OFFSET(CKHkSequenceMgr, m_pGround, 0x11c);
DOTD_ASSERT_OFFSET(CKHkSequenceMgr, m_pPlacement, 0x12c);
DOTD_ASSERT_OFFSET(CKHkSequenceMgr, m_unk134, 0x134);
DOTD_ASSERT_OFFSET(CKHkSequenceMgr, m_unk138, 0x138);
