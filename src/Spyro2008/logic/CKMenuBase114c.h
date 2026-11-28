// CKMenuBase114c.h - the base of DotD's menus and HUD screens (key 0x114c: id 0x45, category Logic;
// vtable 0xb2b658, 0x3f slots, two of them pure). DotD only: no XXL2 counterpart, so the name is
// descriptive (Ghidra: CKMenuBase_114c_maybe_*, and the 0x51xxxx KBase730C_* functions, which only
// this vtable and the leaves' hold). Original unit: KBase730C.cpp (0x5122f8-0x51b9d0).
//
// The Load (0x51a160) reads the screen's flash objects and animation tables, then asks the leaf, through
// virtual accessors, where its fixed reference arrays are (widget slots vt+0x68/+0x6c, reference groups
// vt+0x84..+0x8c, three reference arrays vt+0xbc..+0xd4), so most leaves only add a few fields.
// The animation tables are TVectors read from the last element down; the entry layouts are named from
// their users (KBase730C_UpdateElementAnimations_maybe 0x519130, KBase730C_MessageProc 0x515b78).
#pragma once
#include <cstdint>

#include "Spyro2008/logic/KBase730C.h"

class CKVideoSegment;
class IKTime;
#include "k2000/core/Layout.h"
#include "k2000/util/TVector.h"

class CKMenuBase114c : public KBase730C {
public:
    // A named flash object (+0x10): KBase730C_FindWidgetByName_maybe 0x513ab0 looks entries up by
    // Str_HashXor4(name). The files reference CKFlashText / CKFlashMessageOut objects here.
    struct NamedObject {
        uint32_t m_ui32NameHash;  // +0x00
        IKSerializable* m_pObject;  // +0x04
    };

    // A node animation (+0x1c, 0x54 bytes): an oscillating rotation (sin per axis, Quat_FromEulerDeg) and
    // a scale ramp on a scene node, both driven by 0x519130. The meanings are _maybe.
    struct NodeAnim {
        IKSerializable* m_pBinding;  // +0x00 FlashWidgetBinding (FlashWidgetBinding_IsAnchorUnresolved_maybe)
        IKSerializable* m_pNode;     // +0x04 CSGMovable (SetIdentity, ScaleXYZ)
        float m_vUnk08[3];           // +0x08 amplitude per axis_maybe (zero = no rotation)
        float m_vUnk14[3];           // +0x14 frequency per axis_maybe
        float m_vUnk20[3];           // +0x20 phase per axis_maybe
        float m_fUnk2c;              // +0x2c end value of the first ramp_maybe
        float m_fTime;               // +0x30 runtime (0x519130 accumulates it); not read
        float m_fUnk34;              // +0x34 FloatApproach target; not read
        float m_fUnk38;              // +0x38 FloatApproach speed
        float m_fUnk3c;              // +0x3c FloatApproach current; not read
        float m_fUnk40;              // +0x40 end value of the second ramp_maybe
        float m_fUnk44;              // +0x44 FloatApproach target (scale_maybe); not read
        float m_fUnk48;              // +0x48 FloatApproach speed
        float m_fUnk4c;              // +0x4c FloatApproach current; not read
        float m_fUnk50;              // +0x50 the scale factor (x the second ramp; z negated)
    };

    // A 2D element animation (+0x28, 0x50 bytes): oscillation of an element's position (0x519130
    // writes element +0x20/+0x24). The meanings are _maybe.
    struct ElementAnim {
        IKSerializable* m_pBinding;  // +0x00 FlashWidgetBinding
        IKSerializable* m_pElement;  // +0x04
        uint8_t m_unk08;             // +0x08 runtime flags; not read
        uint8_t m_unk09;             // +0x09
        uint8_t m_unk0a;             // +0x0a
        uint8_t m_pad0b;
        float m_vUnk0c[2];           // +0x0c amplitude_maybe (one 8-byte read, both words swapped)
        float m_vUnk14[2];           // +0x14 frequency_maybe
        float m_vUnk1c[2];           // +0x1c phase_maybe
        float m_fTime;               // +0x24 runtime
        float m_fUnk28;              // +0x28 the base scale (ResetWidgets sets 1.0)
        float m_fUnk2c;              // +0x2c FloatApproach target; not read
        float m_fUnk30;              // +0x30 FloatApproach speed
        float m_fUnk34;              // +0x34 FloatApproach current; not read
        uint32_t m_unk38;            // +0x38
        float m_fUnk3c;              // +0x3c FloatApproach target; not read
        float m_fUnk40;              // +0x40 FloatApproach speed
        float m_fUnk44;              // +0x44 FloatApproach current; not read
        uint32_t m_unk48;            // +0x48
        float m_fUnk4c;              // +0x4c speed used while +0x0a is set (0x519130)
    };

    // A delayed show (+0x34, 0x18 bytes; m_pElement a CParticlesNodeFx): MessageProc 0x515b78 starts the
    // particles when m_pShowSender sends message 0x2300 and sets m_fEndTime = m_fDelay + the menu time;
    // m_pHideSender stops them, and 0x519130 stops them at m_fEndTime.
    struct DelayedShow {
        IKSerializable* m_pBinding;     // +0x00 FlashWidgetBinding
        IKSerializable* m_pElement;     // +0x04
        IKSerializable* m_pShowSender;  // +0x08
        IKSerializable* m_pHideSender;  // +0x0c
        float m_fDelay;                 // +0x10
        float m_fEndTime;               // +0x14 runtime; not read
    };

    // A video trigger (+0x48, 0xc bytes): MessageProc plays m_pVideo (CKVideoSegment) when m_pSender
    // sends message 0x2300, then copies m_unk08 to the menu's +0x58.
    struct VideoTrigger {
        IKSerializable* m_pSender;  // +0x00
        IKSerializable* m_pVideo;   // +0x04 CKVideoSegment
        uint32_t m_unk08;           // +0x08
    };

    // One reference group of a leaf (vt+0x88, 0x10 bytes); its references are at Vf8C(index) and a state
    // per reference at Vf90(index). After the base Load, CKS08MenuArmors and CKS08MenuStatsUpgrades clear
    // the references [m_unk04, m_unk08) and the first m_unk08 states, and set m_unk0c.
    struct RefGroup {
        IKSerializable* m_pObject;  // +0x00 (CKS08MenuArmors: a CParticlesNodeFx, struct draft)
        uint32_t m_unk04;           // +0x04 first dynamic reference_maybe
        uint32_t m_unk08;           // +0x08 reference count_maybe
        uint8_t m_unk0c;            // +0x0c not read
        uint8_t m_pad0d[3];
    };
    // The state of one group reference (vt+0x90, 8 bytes; CKS08MenuArmors_UpdateSlotAnimations_maybe
    // 0x545360 clears both words when it places a reference).
    struct GroupState {
        uint32_t m_unk00;
        uint32_t m_unk04;
    };

    CKMenuBase114c();            // inlined into every leaf's Create (e.g. 0x56e0f0 CKS08MenuBonus_Create)
    ~CKMenuBase114c() override;  // vt+0x00 0x9c7388 CKMenuBase_114c_maybe_Destructor
    // vt+0x10 0x00513c60 CKMenuBase_114c_maybe_Destroy: KBase730C's (KStub_Nop_67eb8), the tables freed (named objects,
    // node and element animations, delayed shows, buttons), the flags cleared, then the video triggers freed.
    void Destroy() override;
    // vt+0x24 0x00513c38 CKMenuBase_114c_maybe_RecursiveRegistration (checklist: _LevelReset): KBase730C's (0x67eb0,
    // registers nothing); the leaves register their own references around it.
    void RecursiveRegistration(int32_t type) override { KBase730C::RecursiveRegistration(type); }

    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c7240
        return key == 0x114c || key == 0x730c || key == 0xc;
    }
    int32_t GetClassType() override { return kCategoryLogic; }  // vt+0x14 0x9c7268
    int32_t GetClassID() override { return 0x45; }              // vt+0x18 0x9c7270
    int32_t Load(IKFile* file, int32_t type) override;          // vt+0x2c 0x51a160 CKMenuBase_114c_maybe_Load
    int32_t PostLoad(int32_t type) override;  // vt+0x30 0x00514f18 KBase730C_PostLoad

    void Open() override;                       // vt+0x50 0x00514a00 KBase730C_Open
    void Pause(int32_t stopVideo) override;     // vt+0x54 0x005139a0 KBase730C_vf54
    void Resume() override;                     // vt+0x58 0x00513700 KBase730C_Open_maybe
    void Close() override;                      // vt+0x5c 0x00513f88 KBase730C_Close
    IKSerializable* Vf60() override { return m_pFlashUI; }                            // vt+0x60 0x9c7278
    void Vf64(uint32_t flag) override { m_ui32Flags = (m_ui32Flags & ~1u) | flag; }  // vt+0x64 0x9c72c0
    uint32_t GetWidgetSlotCount() override { return 0; }                              // vt+0x68 0x9c7280
    WidgetSlot* GetWidgetSlots() override { return nullptr; }                         // vt+0x6c 0x9c7288
    float GetElementX(uint32_t slot) override;         // vt+0x70 0x00512830 KBase730C_GetElementX_maybe
    float GetElementY(uint32_t slot) override;         // vt+0x74 0x00514e10 KBase730C_GetElementY_maybe
    void SetElementX(float x, uint32_t slot) override;  // vt+0x7c 0x00512510 KBase730C_SetElementX_maybe
    void SetElementY(float y, uint32_t slot) override;  // vt+0x80 0x005126a0 KBase730C_SetElementY_maybe
    // vt+0x78 0x00512370 KBase730C_SetElementPosition_maybe: the slot's element offset (2D list for a 2D node 0x24d, 3D
    // list for a scene node 0xcb, searched from the last) set to position[0..1]; nothing without the hot spot, the
    // element or the entry.
    void Vf78(uint32_t slot, const float* position) override;
    // Helpers of the menus (no vtable slot). Names ours from Ghidra's.
    // 0x005122f8 KBase730C_CallOwnerVfDCObjectVf80_maybe: the interface video (manager vt+0xdc) resumed (vt+0x80).
    void ResumeInterfaceVideo();
    // 0x00514668 KBase730C_CallOwnerVfDCObjectVf78AfterVf308_maybe: the interface video stopped (vt+0x78), its segment
    // kept as the interface segment (manager vt+0x308) first. (CKInterfaceButton.cpp, CKInterfaceButtonDouble.cpp and
    // CKInterfaceCheckBox.cpp hold local copies.)
    void StopInterfaceVideoKeepSegment();
    // 0x005137d8 KBase730C_SetFlashHidden_maybe: the flash UI's flags bit 8 = hidden; hiding hides its hot spots.
    void SetFlashHidden(uint8_t hidden);
    // 0x00513880 KBase730C_PlayVideoSegmentById_maybe: the video trigger whose sender is `sender` (from the last): its
    // segment played from mode 3 as the interface segment; a segment not ended with a wait frame pauses the interface
    // until that frame (as MessageProc's message 0x2300).
    void PlayVideoSegmentById(IKSerializable* sender);
    // 0x00513ab0 KBase730C_FindWidgetByName_maybe (and its copies 0x5159a8 / 0x515a48): the named object whose name hash
    // is Str_HashXor4(name), from the last; null without one.
    IKSerializable* FindWidgetByName(const char* name);
    // 0x00515ae8 KBase730C_SendFlashMessageByName_maybe: the named CKFlashMessageOut posted.
    void SendFlashMessageByName(const char* name);
    // 0x00514228 / 0x00514388 KBase730C_Get / SetSelectionOfFirstActivePlayer_maybe: the selection (+0x78 + player) of the
    // first active player (manager vt+0x180), 0xff without one; only with +0x83 set, the player loop repeated +0x80 times.
    uint8_t GetSelectionOfFirstActivePlayer();
    void SetSelectionOfFirstActivePlayer(uint8_t selection);
    // The reference groups' common operations, inlined by the HUD screens: ClearRefGroup clears group g's dynamic
    // references [+0x04, +0x08) and its first +0x08 states; AddToRefGroup puts `object` in the first reference of
    // group g that holds it or is free (that reference's state cleared), nothing when the group is full or `object`
    // is null.
    void ClearRefGroup(uint32_t group);
    void AddToRefGroup(IKSerializable* object, uint32_t group);

    // The leaf accessors the Load reads through (defaults: nothing). Counts are bytes (the Load masks
    // them with 0xff).
    virtual uint8_t Vf84() { return 0; }                                  // vt+0x84 0x9c7290 reference-group count
    virtual RefGroup* Vf88() { return nullptr; }                          // vt+0x88 0x9c7298 the groups
    virtual IKSerializable** Vf8C(uint32_t /*group*/) { return nullptr; }  // vt+0x8c 0x9c72a0 a group's references
    virtual GroupState* Vf90(uint32_t /*group*/) { return nullptr; }      // vt+0x90 0x9c72a8 a group's states
    virtual void Vf94() {}                     // vt+0x94 0x9c72b0 (PostLoad calls it)
    virtual void ResetWidgets();               // vt+0x98 0x005151b0 KBase730C_ResetWidgets_maybe
    virtual void Reset();                      // vt+0x9c 0x00515050 KBase730C_vf9C (the game manager's reset)
    // vt+0xa0 0x005140b0 KBase730C_vfA0: with the interface's sector active, the interface stopped (vt+0x5c
    // when vt+0xb4, else its messages flushed), the widgets reset and an open menu entered again.
    virtual void VfA0();
    virtual void UpdateElementAnimations();    // vt+0xa4 0x00519130 KBase730C_UpdateElementAnimations_maybe
    virtual void VfA8();                       // vt+0xa8 0x00518f28 KBase730C_ClearSlotsAndClose_maybe
    virtual void VfAC() {}                     // vt+0xac 0x9c72b8
    virtual uint8_t SetVisible(uint8_t visible);  // vt+0xb0 0x00514f98 KBase730C_SetVisible_maybe
    virtual uint8_t VfB4() { return 0; }       // vt+0xb4 0x9c72d8 (non-zero: Open does not reset the widgets)
    virtual const char* GetMenuName() = 0;                                // vt+0xb8 pure: "Menu Bonus", ...
    // vt+0xbc / +0xc0: references, mostly CKFlashMessageOut (KBase730C_StartTransitionToMenu 0x5148c0
    // sends entry 0); a leaf may keep other flash objects there (CKMenuMessageBox: a CKFlashText).
    virtual uint8_t VfBC() { return 0; }                 // vt+0xbc 0x9c72e0
    virtual IKSerializable** VfC0() { return nullptr; }  // vt+0xc0 0x9c72e8
    // vt+0xc4 / +0xc8: CKFlashMessageIn references (file keys 0x84d); MessageProc 0x515b78 matches the
    // sender of message 0x2300 against them and sets the entry's VfCC flag (Ghidra, CKS08MenuPause:
    // GetWatchedMessageCount / GetWatchedMessageIds / GetMessageFlags).
    virtual uint8_t VfC4() { return 0; }                 // vt+0xc4 0x9c72f0
    virtual IKSerializable** VfC8() { return nullptr; }  // vt+0xc8 0x9c72f8
    virtual uint8_t* VfCC() { return nullptr; }          // vt+0xcc 0x9c7300
    virtual uint8_t VfD0() { return 0; }                                  // vt+0xd0 0x9c7308 (no leaf overrides it)
    virtual IKSerializable** VfD4() { return nullptr; }                   // vt+0xd4 0x9c7310
    // vt+0xd8 0x00518760 KBase730C_HandleStatePhase: the menu as a state of the game manager's interface
    // state machine (phase 1 enter, 2 leave, 0 update; `other` the previous / next menu id). Returns the
    // menu id (vt+0xe0): the menus never switch by their return value.
    virtual uint8_t HandleStatePhase(int32_t phase, uint8_t other);
    // vt+0xdc 0x009c7318 KBase730C_vfDC: the leaf's part of each phase (Ghidra <Leaf>_OnMenuState_maybe).
    virtual uint8_t OnMenuState(int32_t /*phase*/, uint8_t /*other*/) { return static_cast<uint8_t>(GetMenuId()); }
    virtual int32_t GetMenuId() = 0;  // vt+0xe0 pure (Ghidra: CKS08MenuPause_GetMenuId)
    virtual uint8_t GetSelection(uint8_t /*player*/) { return 0; }        // vt+0xe4 0x9c7360
    virtual void OnItemState(uint8_t /*item*/, uint8_t /*state*/, uint8_t /*arg*/) {}  // vt+0xe8 0x9c7368
    // vt+0xec 0x9c7370 (nop): CKInterfaceButton_Open calls it with the button (CKS08MenuGame 0x554b90 sets
    // its first button's texts).
    virtual void VfEC(IKSerializable* /*button*/) {}
    // vt+0xf0 0x9c7378 / vt+0xf4 0x9c7380: the menu has a back item (the leaves with a back button return
    // 1 and its index); HandleShortcutButtons 0x512d68 then calls vt+0xf8 with it. FindItemUnderCursor
    // skips that item.
    virtual uint8_t VfF0() { return 0; }
    virtual uint8_t VfF4() { return 0xff; }
    // vt+0xf8 0x00514720 KBase730C_TryBackButton: back (action 5, player 2: 0x19) pressed by an active
    // player validates `item` with its delay (SetItemState(item, 1, 1)); returns 1 then.
    virtual uint8_t TryBackButton(uint8_t item);

    // ---- the navigation (C1.6) ----
    // 0x00512040 KBase730C_SetItemState (the TU map puts it at the end of CKS08GameStructure.cpp's range):
    // vt+0xe8(item, its state, 2), the button's SetInteractionState(state), with `delayed` and state 1 the
    // item and its delay kept (+0x60, +0x5c), then vt+0xe8(item, state, 1). Not while a delayed item runs.
    void SetItemState(uint8_t item, uint32_t state, uint8_t delayed);
    // 0x00512938 KBase730C_ReadNavDirection: 0 up, 1 down, 2 left, 3 right (the "Flash Manager" actions
    // 2/8, 3/9, 0/6, 1/7; player 2 + 0x14), 0xff none or while the 0.2 s repeat delay runs.
    uint8_t ReadNavDirection(uint8_t player, IKTime* frameClock);
    // 0x00512d68 KBase730C_HandleShortcutButtons: a button's shortcut action (+0x3b4), the back item (vt+0xf0),
    // and the delay after a validated item. Returns 1 when the frame's input is used.
    uint8_t HandleShortcutButtons(uint8_t player, IKTime* frameClock);
    // 0x00513188 KBase730C_HandleValidateButton: validate (action 4, player 2: 0x18) or left/right on a
    // two-part item. Returns 1 when the frame's input is used.
    uint8_t HandleValidateButton(uint8_t player, uint8_t dir, IKTime* frameClock);
    // 0x00515f20 KBase730C_FindItemUnderCursor: the item under the player's pointer (the game manager's
    // +0x298; on the PS3 always (-1, -1)), 0xff none. Also shows the pointer billboard there.
    uint8_t FindItemUnderCursor(uint8_t player);
    // 0x00516de0 KBase730C_MoveFocusByInput_maybe: the focus moved to `item` (left/right on a two-part item).
    void MoveFocusByInput(uint8_t player, uint8_t dir, uint8_t item);
    // 0x00518248 KBase730C_UpdateFocus_maybe
    void UpdateFocus(uint8_t player, uint8_t dir);
    // 0x005148c0 KBase730C_StartTransitionToMenu: the transition flag (bit 3), the leaving message posted
    // (vt+0xc0 entry 0), the next menu kept (+0x90) and every button faded out (vt+0x74).
    void StartTransitionToMenu(uint8_t menu);
    // 0x00513df8 KBase730C_RefreshOptionWidgets_maybe: every two-part item and option box reloads its value
    // from the options (their LoadOptionValue).
    void RefreshOptionWidgets();

    // 0x00518428 KBase730C_UpdateInput
    void UpdateInput(IKTime* frameClock);
    // 0x005144f0 KBase730C_PlayScreenVideo_maybe: plays the interface video's segment (the game
    // manager's vt+0x30c, else the video's own) from `mode`, then resumes and shows the menu.
    void PlayScreenVideo(int32_t mode, uint8_t arg);
    // vt+0x1c 0x00515b78 KBase730C_MessageProc: message 0x2300 from a CKFlashMessageIn.
    int32_t MessageProc(uint16_t message, void* data) override;

    uint32_t m_ui32Flags;                            // +0x04 bit 0: Vf64; read by the Load
    IKSerializable* m_pGameManager;                  // +0x08 CKS08GameManager (struct draft; MessageProc calls its vt+0x308)
    IKSerializable* m_pFlashUI;                      // +0x0c CKFlashUI (PostLoad hides it)
    TVector<NamedObject, 5> m_aNamedObjects;         // +0x10
    TVector<NodeAnim, 5> m_aNodeAnims;               // +0x1c
    TVector<ElementAnim, 5> m_aElementAnims;         // +0x28
    TVector<DelayedShow, 5> m_aDelayedShows;         // +0x34
    // +0x40..+0x44 and +0x54..+0x80: the menu's run state, not set by the constructor nor the Load. Writers:
    // KBase730C_ResetWidgets_maybe 0x5151b0 (vt+0x98), KBase730C_HandleStatePhase 0x518760 (vt+0xd8),
    // KBase730C_Open 0x514a00, UpdateInput 0x518428, SetSelectionOfFirstActivePlayer_maybe 0x514388.
    float m_fTime;                                   // +0x40 ResetWidgets sets 0; 0x519130 adds the frame time
    uint8_t m_unk44[4];                              // +0x44 HandleStatePhase sets byte 0 to 0xff
    TVector<VideoTrigger, 8> m_aVideoTriggers;       // +0x48
    // +0x54 the interface video's segment while the menu is paused (Pause stores it, Resume plays it);
    // ResetWidgets sets 0. Name ours.
    CKVideoSegment* m_pPausedSegment;
    // +0x58 a video frame the menu waits for with its interface paused (-1: none): HandleStatePhase sets -1,
    // MessageProc a video trigger's m_unk08; when the video reaches it the interface resumes.
    int32_t m_i32WaitVideoFrame;
    float m_fDelayedItemTimer;                                  // +0x5c HandleStatePhase sets 0; HandleShortcutButtons 0x512d68
    uint8_t m_unk60[4];                              // +0x60 bytes; HandleStatePhase clears +0x60, +0x61
    float m_unk64;                                   // +0x64 per player: the validated item's delay (HandleValidateButton); HandleStatePhase sets 0
    float m_unk68;                                   // +0x68 (player 2)
    uint8_t m_aui8FocusedItem[4];                              // +0x6c bytes (vt+0xe4 results in HandleStatePhase)
    float m_fUnk70;                                  // +0x70 HandleStatePhase sets 0.2
    float m_fUnk74;                                  // +0x74 HandleStatePhase sets 0.2
    uint8_t m_aui8NavDirection[4];                             // +0x78 a selection per player_maybe (ResetWidgets: 0xff)
    float m_fOpenInputDelay;                                  // +0x7c Open sets 0.5; UpdateInput counts it down
    uint8_t m_unk80[4];                              // +0x80 bytes: player count_maybe (+0x80), flags (+0x82, +0x83)
    TVector<IKSerializable*, 3> m_apButtons;         // +0x84 CKInterfaceButton (file refs 0x630c)
    uint8_t m_ui8NextTransitionMenu;                                 // +0x90 set by KBase730C_StartTransitionToMenu 0x5148c0
    uint8_t m_bTitleShown;                                 // _maybe: +0x91 CKS08MenuPauseInfo: a title is shown (SetTitleText sets 1, ShowNextPage 0)
    uint8_t m_pad92[2];
};
DOTD_ASSERT_SIZE(CKMenuBase114c, 0x94);
DOTD_ASSERT_SIZE(CKMenuBase114c::NamedObject, 0x8);
DOTD_ASSERT_SIZE(CKMenuBase114c::NodeAnim, 0x54);
DOTD_ASSERT_SIZE(CKMenuBase114c::ElementAnim, 0x50);
DOTD_ASSERT_SIZE(CKMenuBase114c::DelayedShow, 0x18);
DOTD_ASSERT_SIZE(CKMenuBase114c::VideoTrigger, 0xc);
DOTD_ASSERT_SIZE(CKMenuBase114c::RefGroup, 0x10);
DOTD_ASSERT_SIZE(CKMenuBase114c::GroupState, 0x8);
DOTD_ASSERT_OFFSET(CKMenuBase114c, m_ui32Flags, 0x04);
DOTD_ASSERT_OFFSET(CKMenuBase114c, m_pGameManager, 0x08);
DOTD_ASSERT_OFFSET(CKMenuBase114c, m_pFlashUI, 0x0c);
DOTD_ASSERT_OFFSET(CKMenuBase114c, m_aNamedObjects, 0x10);
DOTD_ASSERT_OFFSET(CKMenuBase114c, m_aNodeAnims, 0x1c);
DOTD_ASSERT_OFFSET(CKMenuBase114c, m_aElementAnims, 0x28);
DOTD_ASSERT_OFFSET(CKMenuBase114c, m_aDelayedShows, 0x34);
DOTD_ASSERT_OFFSET(CKMenuBase114c, m_aVideoTriggers, 0x48);
DOTD_ASSERT_OFFSET(CKMenuBase114c, m_fTime, 0x40);
DOTD_ASSERT_OFFSET(CKMenuBase114c, m_pPausedSegment, 0x54);
DOTD_ASSERT_OFFSET(CKMenuBase114c, m_i32WaitVideoFrame, 0x58);
DOTD_ASSERT_OFFSET(CKMenuBase114c, m_fOpenInputDelay, 0x7c);
DOTD_ASSERT_OFFSET(CKMenuBase114c, m_apButtons, 0x84);
DOTD_ASSERT_OFFSET(CKMenuBase114c, m_ui8NextTransitionMenu, 0x90);

// C1.6 menus: the game manager calls the menus make (vt+0xb4 ExitGame, vt+0xb8 NewGame, vt+0x1d4
// ResetEditedOptions, vt+0x1e4 IsVideoSkipPressed, the game structure's vt+0x60 ApplyPlayerGameState) are
// the game manager's own methods now (C1.6 gm).
class CKS08GameManager;
// The menus' request: the game manager's menu stack set to the one menu MenuId(menu) (vt+0x304).
void MenuGm_RequestMenu(CKS08GameManager* manager, uint8_t menu);
