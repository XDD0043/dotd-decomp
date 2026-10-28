// CKS08GameManager.h - Spyro's game manager (key 0x784c, vtable 0xb2af78, size 0xf2c), loaded from
// GAME.KP3 and every level. Original units: CKS08GameManager*.cpp. PS3 chain: IKCommonGameManager
// (0x3b0c, unregistered; +0x298..+0xae8, vtable at TOC +0x6ff4) -> IKGameManager (here
// CDefaultGameManager). IKCommonGameManager is not a class of its own here: its fields, its Load
// (LoadCommon) and its code (the game state and interface state machines, Update) live in this class.
// C1.4 ports the front end: Init's tables, Update, the states 0-6 and the interface (menu) switching;
// STUB(C1.6): the in-game states (7 in game, 8 pause menu, 9 hero death), the HUD and the heroes.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/math/CVector2.h"
#include "k2000/services/CTriggerStarter.h"
#include "k2000/util/TVector.h"

class CKInputDico;
class CKVideoSegment;

class CKS08GameManager : public CDefaultGameManager {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x1e1)

    // vt+0x08 0x009c6cb0 CKS08GameManager_IsKindOfClass: itself, IKCommonGameManager (0x3b0c, not a class of its own
    // here), IKGameManager's two bases and the root.
    int32_t IsKindOfClass(uint32_t key) override {
        return key == 0x784c || key == 0x3b0c || key == 0xbcc || key == 0x3fe || key == 0xc;
    }

    CKS08GameManager();  // 0x004f9408 CKS08GameManager_Construct (with 0x4edee0, the bases' part)

    // A state of one of the two state machines (IKCommonGameManager's, a pointer to member function: the
    // PS3 stores {OPD, this adjustment} pairs): called with phase 1 on enter (the previous state), 2 on
    // leave (the next state) and 0 every frame (the state itself); the update returns the next state.
    typedef uint8_t (CKS08GameManager::*StateHandler)(int32_t phase, uint8_t other);
    // The machine (0xc bytes on the PS3): the object the handlers run on, the table, its size and the
    // current state (0xff: none).
    struct StateMachine {
        CKS08GameManager* m_pOwner;  // +0x00
        StateHandler* m_pTable;      // +0x04 Mem_AllocAligned16
        uint8_t m_ui8Count;          // +0x08
        uint8_t m_ui8Current;        // +0x09
        uint8_t m_pad0a[2];          // +0x0a (the interface stack reads +0x30f, its second byte, at depth 0)
        // Calls state `state`'s handler (the PS3 inlines this, re-reading the table for every call).
        uint8_t Call(uint8_t state, int32_t phase, uint8_t other) { return (m_pOwner->*m_pTable[state])(phase, other); }
        // The inlined switch: leave the current state, store the next one, enter it with the previous one
        // (the current state re-read after the leave call).
        void Switch(uint8_t next);
        // The inlined frame: the current state's update; when it returns another state, the switch. Returns
        // the current state afterwards.
        uint8_t Tick();
    };

    static IKBaseClass* Create();
    static void Delete(IKBaseClass* object);

    void Start() override;                    // vt+0x50 0x004f8d08 CKS08GameManager_Start
    void Stop() override;                     // vt+0x68 0x004f22e8 CKS08GameManager_Stop (leaving the level or the front end)
    // vt+0x8c 0x004eeab8 CKS08GameManager_SectorUnload: the HUD screens whose flash interface belongs to the
    // sector closed (vt+0xa8).
    void SectorUnload(int32_t sector) override;
    // vt+0x88 0x004ed310 CKS08GameManager_SectorLoaded: CDefaultGameManager_SectorLoaded (0x134f0, a bare return),
    // then every HUD screen (last to first) whose flash interface belongs to the sector reset (vt+0x9c).
    void SectorLoaded(int32_t sector) override;
    // vt+0x124 0x004eea60 CKS08GameManager_GetFocusedHeroNodePosition_maybe: the zero vector without the hero group
    // (+0x08), else the position of the LTM of the frame of the focused hero's node.
    const float* GetFocusedHeroNodePosition() override;
    // vt+0x128 0x004eda18 CKS08GameManager_GetFocusedHeroPosition_maybe: the zero vector without the hero group or a
    // focused hero, else the hero's targeting position (IKHkHero_GetTargetingPositionPtr_maybe 0x363c78: +0x570, or with
    // +0x0c bit 1 its node's world position).
    const float* GetFocusedHeroPosition() override;
    // vt+0x130 0x004ed930 CKS08GameManager_GetFocusedHeroMoveVector_maybe: the focused hero's move vector (+0x3b8) when it has player input
    // (CKHkS08Hero_GetPlayerInputByte394 0x362dd0), else the zero vector.
    const float* GetFocusedHeroMoveVector() override;
    // vt+0x120 0x004f6e78 CKS08GameManager_GetFocusedHeroCamera_maybe: null without the hero group, else the camera target
    // (hook +0x1818, a CSGLeaf) of the hero at the group's focused index (0x2d4bc0 CKGrpS08Hero_GetFocusedHeroCamera_maybe).
    IKSerializable* GetFocusedHeroCamera() override;
    void OnLevelStart() override;             // vt+0x9c 0x004ee710 CKS08GameManager_OnLevelStart_maybe
    void Pause() override;                    // vt+0x70 0x004ed540 CKS08GameManager_Pause
    void Resume() override;                   // vt+0x78 0x004ed440 CKS08GameManager_Resume
    void Update(IKTime* frameClock) override; // vt+0x7c 0x004f8f78 CKS08GameManager_Update
    int32_t PostLoad(int32_t type) override;  // vt+0x30 0x004f7180 CKS08GameManager_PostLoad
    int32_t GetSerializationFlags() override { return 0; }  // vt+0x34 0x991250
    // vt+0x10 0x004f7c28 CKS08GameManager_Destroy (the level unload): IKCommonGameManager's, the level
    // references +0xd88 / +0xf20 / +0xf24 forgotten, the HUD textures released.
    void Destroy() override;

    // vt+0xa0 0x004ef738 CKS08GameManager_Init: InitImpl, then the two state machines' tables.
    void Init() override;
    void VfAC() override;                     // vt+0xac 0x004f6eb8 CKS08GameManager_vfAC (the front end restarts)
    void ExitGame() override;                 // vt+0xb4 0x004ed298 CKS08GameManager_vfB4: CDefaultGameManager's RequestGameExit
    // vt+0xb8 0x004f80f8 CKS08GameManager_ResetGameProgress_maybe (XXL2 NewGame): IKCommonGameManager's
    // NewGame, +0xe98 = -1, the game structure's new-game progress, the new-game state (+0x474 entry 0,
    // vt+0x2f0) applied to it, player 0's game state taken from it (vt+0x58) and copied to player 6
    // (vt+0x50); with flag 0x80 (+0x64) the structure's vt+0x58.
    void NewGame() override;
    uint8_t VfC4() override { return static_cast<uint8_t>((m_unkAFC >> 5) & 1); }  // vt+0xc4 0x9c7028
    void HandleControllerDisconnect(uint8_t port) override;  // vt+0xc8 0x004ee1a8 STUB(C1.6)
    IKVideo* GetInterfaceVideo() override;   // vt+0xdc 0x9c6a78: m_unk460
    IKVideo* GetDemoVideo() override;        // vt+0xe0 0x9c69f8: m_unk2E0
    // vt+0xf4 0x004ec878 CKS08GameManager_vfF4: not during the logos (state 3); during press start (5)
    // only for videos other than the demo (vt+0xe0).
    uint8_t AllowsBgmDuringVideo(IKVideo* video) override;
    uint8_t Vf108() override { return CDefaultGameManager::Vf108(); }  // vt+0x108 0x4ed1f8
    void RequestSave(uint32_t unused, uint8_t value) override;         // vt+0x104 0x004ed220 CKS08GameManager_RequestSave_maybe
    void SetSaveRequestFlag(uint32_t unused, uint8_t value) override;  // vt+0x10c 0x004f7130
    uint8_t GetControlledHeroCount() override;                   // vt+0x134 0x004ed8f0
    uint8_t GetMaxPlayers() override { return 2; }               // vt+0x150 0x9c6d38
    uint8_t GetPlayerCount() override { return m_unkAE9; }       // vt+0x154 0x9c6d40
    uint8_t SetPlayerCount(uint32_t count) override;             // vt+0x158 0x004f68e0
    // vt+0x160 0x004ecdd0 CKS08GameManager_IsActionPressed / vt+0x164 0x004ecf80 _GetActionValue: entry
    // player * 50 + action of the common input configuration (+0x2e8) for actions below 50, else
    // (GetMaxPlayers() * 25 + player) * 2 + action - 50 (byte-wrapped).
    uint8_t IsActionPressed(uint32_t action, uint8_t player) override;
    float GetActionValue(uint32_t action, uint8_t player) override;
    uint8_t IsPlayerActive(int32_t player) override;             // vt+0x180 0x004edde8
    uint8_t GetDialogueButtonState(int32_t player) override;     // vt+0x18c 0x004ecd10 CKS08GameManager_vf18C
    void SetPlayerActive(int32_t player, uint8_t active) override;  // vt+0x184 0x004edce8
    // vt+0x188 0x004f6be8 CKS08GameManager_GetDirectionActionState_maybe (step 5, the camera's right stick; not
    // virtual here, the camera track is its caller): the mean filtered state of the direction (0 / 1 the y axis, 2 / 3
    // the x axis) over the players that hold it, the directions swapped by the per-player options Vf1BC (2 <-> 3) and
    // Vf1B4 (0 <-> 1); entry player * 50 + m_unk498[direction] of the common input configuration.
    uint8_t GetDirectionActionState(uint8_t direction);
    uint8_t Vf1B0() { return 0; }  // vt+0x1b0 0x9c6d20 CKS08GameManager_vf1B0 (0: the camera's stick y is not inverted)
    uint8_t Vf1B8() { return 0; }  // vt+0x1b8 0x9c6d28 CKS08GameManager_vf1B8 (0: the camera's stick x is not inverted)
    // vt+0x1b4 0x991400 IKGameManager_vf1B4 / vt+0x1bc 0x991470 IKGameManager_vf1BC: the current options' per-player bytes
    // +0x1e / +0x20 (player 1's for 1, else player 0's).
    uint8_t Vf1B4(int32_t player) const { return m_currentOptions.m_abUnk1E[player == 1 ? 1 : 0]; }
    uint8_t Vf1BC(int32_t player) const { return m_currentOptions.m_abUnk20[player == 1 ? 1 : 0]; }
    // vt+0x1d4 0x004f6bc0 CKS08GameManager_vf1D4 -> 0x004ed058 IKCommonGameManager_vf1D4 -> CDefaultGameManager's
    // (the options menu's item 10: the edited options back to the defaults).
    void ResetEditedOptions() override;
    void ResetEditedOptionsCommon();  // 0x004ed058 IKCommonGameManager_vf1D4
    // vt+0x1e4 0x004ee310 CKS08GameManager_IsVideoSkipPressed_maybe: the "Flash Manager" project's second
    // configuration: entries 0xe, 4 or 5 pressed (0xff), with player 1 active also 0x22, 0x18 or 0x19.
    uint8_t IsVideoSkipPressed() override;
    // vt+0x1c 0x004fa438 CKS08GameManager_MessageProc: HandleUIMessage (the cinematic and video notifications), then the
    // level scripts' messages: the jump table 0x263c..0x270a (the dragons' counters +0x1e4..+0x1e9 of the game structure,
    // the boss HUD's flash messages, the info pages of CKS08MenuPauseInfo: 0x26c8 slow motion on, 0x26c9 title, 0x26ca a
    // page; the checkpoint snapshot 0x270a; 0x2704..0x2709 known, nothing done) and the twelve objective lists' messages
    // 0x26cb..0x26fa (an objective's state 0..3, with its HUD text). The data is the trigger action (its CMultiData
    // word first). Ids of neither answer 1, the known ones 0, combined with HandleUIMessage's answer.
    int32_t MessageProc(uint16_t message, void* data) override;
    // 0x004fefd8 CKS08GameManager_QueueHudMessage_maybe: the centre HUD (GetHudInterfaces()[1]) queues the text.
    void QueueHudMessage(IKSerializable* text);
    // 0x004ff080 CKS08GameManager_ShowCenterHudMessagePairSecondFromTable_maybe: the centre HUD shows the text with the
    // second text of the accessor +0xec4 (its m_pText without a list).
    void ShowCenterHudMessagePairSecond(IKSerializable* text);
    // 0x004ff150 CKS08GameManager_ShowCenterHudMessage_maybe: the centre HUD shows the accessor +0xec4's first text with
    // this one.
    void ShowCenterHudMessage(IKSerializable* text);
    // 0x004eee20 CKS08GameManager_HandleCinematicAndUIMessage_maybe: 0x500, 0x2501 and 0x2502 only; 0 for anything else.
    uint8_t HandleUIMessage(uint16_t message, void* data);
    // C2.3 step 4: vt+0x224 0x004fb3d8 CKS08GameManager_HandlePauseInput_maybe (CheckPauseRequest 0x004f1f88, then the pause
    // button -> state 8) and the pause request itself. In game (state 7) with a skippable scene playing, START asks the
    // skip prompt (+0x4d0 = 2) instead; its answer arrives as message 0x2d00 (HandleUIMessage).
    void HandlePauseInput(IKTime* frameClock) override;
    void CheckPauseRequest();
    // C2.3: vt+0x1e8 0x004ed8b8 / vt+0x1ec 0x004ed878 / vt+0x1f0 0x004edd20 / vt+0x1f4 0x004ede20 / vt+0x1f8 0x004ed7d8.
    void SetInputBlocked(uint8_t blocked) override;
    uint8_t IsInputBlocked() override;
    void GetHeroesInvulnerableMask(uint32_t* mask) override;
    void SetHeroesInvulnerableFromMask(const uint32_t* mask) override;
    void SetAllHeroesInvulnerable(uint8_t invulnerable) override;
    uint8_t IsFrontEndLevel() override;                          // vt+0x20c 0x004ed198 CKS08GameManager_IsTrackedLevelCurrent_maybe
    IKSerializable* Vf214() override;                            // vt+0x214 0x9c6da8
    // vt+0x21c 0x004ec6e8 CKS08GameManager_NotifyInputActivity_maybe (step 4 INPUT; its unit is CKS08GameManager_2.cpp): a pad (device
    // 0) button 0xc..0x13 seen pressed sets its byte of +0x480.
    void NotifyInputActivity(int32_t device, int32_t button) override {
        if (device != 0) return;
        const uint32_t index = static_cast<uint32_t>(button - 0xc);
        if (index > 7) return;  // cmplwi 7; bgtlr
        m_aUnk480[index] = 1;
    }
    uint32_t GetPlayerClassKey() override { return 0x780c; }         // vt+0xd4 0x9c6f38
    uint32_t GetGameStructureClassKey() override { return 0x798c; }  // vt+0x194 0x9c6f40
    // vt+0x2c 0x4fc228 CKS08GameManager_Load
    int32_t Load(IKFile* stream, int32_t mode) override;

    // vt+0x240 0x004f7158 CKS08GameManager_vf240 -> 0x004eebe8 IKCommonGameManager_vf240: the menu after a
    // load-game flow: 0 (loaded) the game structure's vt+0x60 with player 0 and menu vt+0x2fc; 1 the main
    // menu (vt+0x2f8); the menu stack depth 1.
    void Vf240(int32_t result) override;
    void Vf240Common(int32_t result);  // 0x004eebe8 IKCommonGameManager_vf240
    // vt+0x1d0 0x4ed2e8 CKS08GameManager_InitDefaultOptions_maybe passes its arguments on to the base's
    // (CDefaultGameManager::InitDefaultOptions); not overridden.

    // IKCommonGameManager's slots (+0x2d8..+0x35c) the front end uses.
    // vt+0x138 0x004f88f8 CKS08GameManager_GetGroundSurfaceBit_maybe: the ground's surface kind bit for a hero on it (1 with engine flag 6, or
    // with property 0x200 without engine flag 1; else property bit 1). Called for the hero's ground (not virtual here).
    uint16_t GetGroundSurfaceBit(const IKSerializable* ground) const;
    // vt+0x270 0x009c6938 CKS08GameManager_vf270 / vt+0x274 0x009c6940 CKS08GameManager_vf274: 0xff for any hero (the
    // hazard code's hit points; not virtual here).
    uint8_t Vf270(uint8_t /*hero*/) const { return 0xff; }
    uint8_t Vf274(uint8_t /*hero*/) const { return 0xff; }
    virtual IKSerializable* Vf2E0() { return nullptr; }               // vt+0x2e0 0x9c6a08
    // vt+0x2e4 0x004ec540 CKS08GameManager_RequestLevelChange_maybe: level and sector requested (GameLoop
    // mode 5 -> 9 -> 1), +0x2fc = 2 (the front end comes back on the chapter menu). Returns 1.
    virtual uint8_t RequestLevelChange(int32_t level, int32_t sector);
    // vt+0x2e8 0x004efb48 CKS08GameManager_vf2E8: the game structure's current spawn point made current
    // again (vt+0x6c), then its level and sector requested (vt+0x2e4). New game / continue from the menus.
    virtual uint8_t RequestSpawnPointLevel();
    // vt+0x2f0 0x004ee668 CKS08GameManager_vf2F0: game state `index` of +0x474 (the new-game states) applied
    // to the game structure (vt+0x70, then vt+0x74). 0 when there is no such state, else 1.
    virtual uint8_t Vf2F0(uint32_t index);
    virtual uint8_t MainMenuId() { return MenuId(9); }                // vt+0x2f8 0x9c6de0 (vt+0x304(9))
    virtual uint8_t Vf2FC() { return MenuId(6); }                     // vt+0x2fc 0x9c6e28 (vt+0x304(6))
    virtual uint8_t Vf300() { return 0; }                             // vt+0x300 0x9c6e70
    virtual uint8_t MenuId(uint8_t menu) { return menu; }             // vt+0x304 0x9c6f68
    virtual void SetInterfaceSegment(CKVideoSegment* segment) { m_unk464 = segment; }  // vt+0x308 0x9c6a80
    virtual CKVideoSegment* GetInterfaceSegment() { return m_unk464; }                 // vt+0x30c 0x9c6a88
    // vt+0x310 0x9c6b68 / +0x314 0x9c6aa0: flags +0x64 bit 12 (player 0) or 13 (player 1).
    virtual uint8_t Vf310(int32_t player);
    virtual void Vf314(int32_t player, uint8_t value);
    // vt+0x31c 0x004f6b48 CKS08GameManager_vf31C (Ghidra GetPointerPosition_maybe): the pointer position of
    // `player`, always (-1, -1) on the PS3, also stored in +0x298.
    virtual CVector2 GetPointerPosition(int32_t player);
    // vt+0x320 0x004f8b50 CKS08GameManager_vf320 (IKCommonGameManager's 0x9c6af0 is empty): the input
    // service's blocks 0 and 1 updated with the system time step while active (+0x0e), then both players'
    // pointer positions (vt+0x31c). IKGameManager_Update calls it while the frame clock is not running.
    virtual void Vf320();
    virtual uint8_t StateCount() { return 0xc; }                      // vt+0x324 0x9c6af8
    virtual void InitStateHandlerTable(StateHandler* table);          // vt+0x328 0x004f6698
    virtual void Vf334();                                             // vt+0x334 0x004fdc38
    virtual uint8_t NoMenuId() { return 0x24; }                       // vt+0x338 0x9c6e90
    virtual uint8_t MenuStateCount() { return 0x25; }                 // vt+0x33c 0x9c6e98
    // The reference tables IKCommonGameManager_Load reads through virtual accessors.
    virtual uint8_t Vf340() { return 0x24; }                          // vt+0x340 0x9c6e78 (the menu count)
    virtual IKSerializable** Vf344() { return m_unkB08; }             // vt+0x344 0x9c6e80
    virtual uint8_t Vf348() { return 5; }                             // vt+0x348 0x9c6ea0
    // 0x004ff2d8 / 0x00500b38 Notify{Spyro,Cynder}MovementModeChanged_Stub (CKS08GameManager_5.cpp).
    void NotifySpyroMovementModeChanged(uint8_t mode);
    void NotifyCynderMovementModeChanged(uint8_t mode);
    virtual IKSerializable** GetHudInterfaces() { return m_apHudInterfaces; }  // vt+0x34c 0x9c6ea8
    virtual uint8_t Vf350() { return 0x32; }                          // vt+0x350 0x9c6eb8
    virtual uint32_t* GetCounterTextVarTable() { return m_unkCC0; }   // vt+0x354 0x9c6ec0 _maybe
    virtual uint8_t Vf358() { return 1; }                             // vt+0x358 0x9c6d30
    // vt+0x35c 0x9c6fe0 CKS08GameManager_IsInterfaceStateNot10_maybe: the interface state (+0x30d) is not 0x10.
    virtual uint8_t Vf35C() { return m_interfaceState.m_ui8Current != 0x10 ? 1 : 0; }

    // 0x004f0110 IKCommonGameManager_Load: LoadImpl, then the common part (GAME: mode 1; a level: mode 0).
    void LoadCommon(IKFile* stream, int32_t mode);
    // 0x004ff768 CKS08GameManager_LoadHudResources_maybe (mode 0)
    void LoadHudResources(IKFile* stream, int32_t mode);
    // 0x004fc010 CKS08GameManager_LoadRefTableE4C_maybe (mode 0)
    void LoadRefTable(IKFile* stream, int32_t mode);

    // ---- IKCommonGameManager's code (the front end) ----
    void UpdateCommon(IKTime* frameClock);  // 0x004f2dd0 IKGameManager_Update
    void ResetRuntime();                    // 0x004f0ff8 IKGameManager_ResetRuntimeImpl
    void VfACCommon();                      // 0x004f1d90 IKCommonGameManager_vfAC: the game state set to 1
    // 0x004eed08 CKS08GameManager_ResetProgress_maybe (XXL2 IKCommonGameManager::NewGame, which CKA2's NewGame
    // calls first): BasicNewGame, vt+0x334, flags +0x64 &= ~0x80, +0x2fc = 2 (the front end comes back on
    // the chapter menu).
    void NewGameCommon();
    // 0x00502410 ResetDragonStatHud: the dragon stat fields cleared, then the HUD texts and gauges refreshed.
    void ResetDragonStatHud();

    // ---- C2.2 gm: the in-game start and the HUD ----
    // One player's HUD slot (the +0x2c8 array, GetMaxPlayers() entries, 8 bytes on the PS3): the hero that
    // wants a panel this frame (set by the hero) and a flag. The game manager clears them every frame.
    struct PlayerHudSlot {
        IKSerializable* m_pHero;  // +0x00
        uint8_t m_ui8Flag;        // +0x04
    };
    PlayerHudSlot* PlayerHudSlots() { return static_cast<PlayerHudSlot*>(m_unk2C8); }
    // The data of message 0x2666, which a hero answers with the HUD panel it wants (16 bytes on the PS3): the
    // text (a CKStdText) in, the counter value and the panel type (0 or 1) out; the second word is -1 going in.
    struct SHudPanelMessage {
        IKSerializable* m_pText;
        int32_t m_i32Unused;
        int32_t m_i32Value;
        int32_t m_i32Type;
    };
    // vt+0x294 0x004ec968 CKS08GameManager_SetActiveCameraIndex_maybe: the camera service's active sector-mode
    // camera list, when it exists and has a camera.
    virtual void SetActiveCameraIndex(uint32_t index);
    // vt+0x144 0x004eda80 CKS08GameManager_vf144: the hero group's vt+0x184 when there is a group.
    void UpdateHeroCameraTargets() override;
    // vt+0x2d8 0x00502688 CKS08GameManager_ShowPlayerHudPanel_maybe / vt+0x2dc 0x005008d0 ..HidePlayerHudPanel_maybe:
    // the panel of the dragon `player`'s hero (Spyro: the left panel, Cynder: the right one).
    virtual void ShowPlayerHudPanel(IKSerializable* text, int32_t value, int32_t type, uint8_t player);
    virtual void HidePlayerHudPanel(uint8_t player);
    void UpdateInGameHud(IKTime* frameClock);   // 0x00501b00
    void UpdateComboTimers(IKTime* frameClock);  // 0x00500628
    void UpdateBossGaugeTotals();               // 0x004ff318
    void UpdateSecondBossGaugeTotals();         // 0x004ff540
    // 0x00500140 / 0x005013a8 / 0x00501188 / 0x00500ee8 / 0x00500cc8 / 0x00501648: the dragon's (0 Spyro,
    // 1 Cynder) upgrade text, health and mana gauges and their capacity markers.
    void UpdateDragonUpgradeText(uint8_t dragon, uint8_t shake);
    void SetCenterTwinGauges(float first, float second);  // 0x004fed80
    void UpdateDragonHealthGauge(uint8_t dragon);
    void UpdateDragonHealthCapacityMarker(uint8_t dragon);
    void UpdateDragonManaGauge(uint8_t dragon);
    void UpdateDragonManaCapacityMarker(uint8_t dragon);
    // ---- step 4 ANIM: the dragon stats (0 Spyro, 1 Cynder; any other dragon: 0 / nothing) in the game structure
    // (+0x6c): health +0x4c / +0x54, mana +0x64 / +0x6c. ----
    // 0x004fd628 GetArmorMeshHiddenFlag_maybe: the game structure's +0xbb (Spyro) / +0xba (any other dragon).
    uint8_t GetArmorMeshHiddenFlag(int32_t dragon);
    // 0x004fd658 GetEquippedArmor_maybe: the armour in `slot` (0..2) of the dragon, +0xb4 + 3 dragon + slot (3: none).
    uint8_t GetEquippedArmor(int32_t dragon, int32_t slot);
    uint32_t GetDragonManaCapacity(int32_t dragon);                     // 0x004fd740 (CKS08GameManager_3.cpp)
    uint32_t GetDragonMana(int32_t dragon);                             // 0x004fd7c8
    void ConsumeDragonMana(int32_t dragon, uint32_t amount);            // 0x004fd808
    uint32_t GetDragonHealthCapacity(int32_t dragon);                   // 0x004fd940
    uint32_t GetDragonHealth(int32_t dragon);                           // 0x004fd9c8
    void DamageDragon(int32_t dragon, uint32_t amount);                 // 0x004fda08
    void RestoreDragonMana(int32_t dragon, int32_t amount, int32_t quiet);    // 0x004fdca8 (CKS08GameManager_4.cpp)
    void RestoreDragonHealth(int32_t dragon, int32_t amount, int32_t quiet);  // 0x004fdef8 (CKS08GameManager_4.cpp)
    // 0x005022b0 RefreshDragonStatDisplays_maybe (CKS08GameManager_5.cpp): the health and / or mana gauges and their
    // capacity markers, then the stat change feedback (0x501fb8, STUB(C2.7: HUD)).
    void RefreshDragonStatDisplays(uint8_t dragon, int32_t health, int32_t mana);
    void UpdateDragonHealthAndManaGauges(uint8_t dragon, int32_t health, int32_t mana);
    void SelectSpyroHudPanelElement(uint8_t element);   // 0x004ff220 CKS08GameManager_SelectSpyroHudPanelElement_maybe
    void SelectCynderHudPanelElement(uint8_t element);  // 0x00500a88 CKS08GameManager_SelectCynderHudPanelElement_maybe
    int32_t PostLoadCommon(int32_t type);   // 0x004edaf8 IKCommonGameManager_PostLoad
    void DestroyCommon();                   // 0x004ed790 IKCommonGameManager_Destroy (Ghidra ..._ClearReferences)
    void DestroyTextures();                 // 0x004fe638 CKS08GameManager_DestroyTextures
    // 0x004ec420 CKS08GameManager_RequestState_maybe (CKS08Damage.cpp): another game state requested (+0x2fa).
    void RequestState(uint8_t state);
    void PlayDemoVideo();                   // 0x004f6838 CKS08GameManager_CallMember2E0Vf60Arg0_maybe
    void StopDemoVideo();                   // 0x004f6890 CKS08GameManager_CallMember2E0Vf78_maybe
    // The game states (table built by Init and InitStateHandlerTable). Names from Ghidra.
    uint8_t StateReturn0(int32_t phase, uint8_t other);         // 0x004f46f8 KStub_Return0_4f46f8 (state 0: idle)
    uint8_t State1(int32_t phase, uint8_t other);               // 0x004f4de0 IKCommonGameManager_State1_maybe (auto-load)
    uint8_t State2Common(int32_t phase, uint8_t other);         // 0x004f49a8 IKCommonGameManager_State2_maybe
    uint8_t State3(int32_t phase, uint8_t other);               // 0x004f4b08 IKCommonGameManager_State3_maybe (logos)
    uint8_t StateReturn4(int32_t phase, uint8_t other);         // 0x004f4700 KStub_Return4_4f4700
    uint8_t State5Common(int32_t phase, uint8_t other);         // 0x004f4928 IKCommonGameManager_State5_maybe
    uint8_t State6Common(int32_t phase, uint8_t other);         // 0x004f4708 IKCommonGameManager_State6_maybe
    uint8_t StateInGameCommon(int32_t phase, uint8_t other);    // 0x004f4fa0 STUB(C1.6)
    uint8_t StateMenuCommon(int32_t phase, uint8_t other);      // 0x004f5128 STUB(C1.6)
    uint8_t StateHeroDeathCommon(int32_t phase, uint8_t other); // 0x004f48d0 STUB(C1.6)
    uint8_t StateReturn10(int32_t phase, uint8_t other);        // 0x004f48f0 KStub_Return10_4f48f0
    uint8_t StateReturn11(int32_t phase, uint8_t other);        // 0x004f48f8 KStub_Return11_4f48f8
    uint8_t State2(int32_t phase, uint8_t other);               // 0x00504248 CKS08GameManager_State2_maybe
    uint8_t State4(int32_t phase, uint8_t other);               // 0x005044e0 CKS08GameManager_State4_maybe (copyrights)
    uint8_t State5(int32_t phase, uint8_t other);               // 0x00504750 CKS08GameManager_State5_maybe (press start)
    uint8_t State6(int32_t phase, uint8_t other);               // 0x00504040 CKS08GameManager_State6_maybe (main menu)
    uint8_t StateInGame(int32_t phase, uint8_t other);          // 0x005043a8 STUB(C1.6)
    uint8_t StateMenuPause(int32_t phase, uint8_t other);       // 0x00504990 STUB(C1.6)
    uint8_t StateHeroDeath(int32_t phase, uint8_t other);       // 0x00504c88 STUB(C1.6)
    // The interface (menu) states: none (vt+0x338) and every menu.
    uint8_t InterfaceNone(int32_t phase, uint8_t other);        // 0x004ed080 CKS08GameManager_ResetFadeVideoIfMode2ThenVf338_maybe
    uint8_t InterfaceStateDispatch(int32_t phase, uint8_t other);  // 0x004ee100
    void PickRandomTipText();                                   // 0x004ec9b8 CKS08GameManager_PickRandomTipText_maybe

    // A 0xc-byte record of the two five-entry tables a level gives (+0xc48, +0xc84).
    struct SRecord {
        uint32_t m_unk0;
        uint32_t m_unk4;
        uint32_t m_unk8;
    };

    // ---- IKCommonGameManager (+0x298) ----
    float m_afUnk298[4];                      // +0x298 a 2D position per player (vt+0x31c sets -1, -1); State6 places the +0x2a8 billboard there
    IKSerializable* m_unk2A8[2];              // +0x2a8 mode 0
    IKSerializable* m_unk2B0[2];              // +0x2b0 mode 0
    uint32_t m_unk2B8;                        // +0x2b8
    TVector<uint32_t, 10> m_unk2BC;           // +0x2bc mode 1 (words)
    void* m_unk2C8;                           // +0x2c8 PostLoad (mode 0): new[GetMaxPlayers() * 8], one {word, byte} per player
    IKSerializable* m_unk2CC;                 // +0x2cc mode 1
    TVector<IKSerializable*, 8> m_unk2D0;     // +0x2d0 mode 1: the logo videos (PS3_CKVideo references), State3 plays them
    int32_t m_i32CurrentLogo;                 // +0x2dc State3: the logo video playing (index into m_unk2D0), -1 none
    IKSerializable* m_unk2E0;                 // +0x2e0 mode 1
    IKSerializable* m_unk2E4;                 // +0x2e4 mode 1
    // +0x2e8 the "IKCommonGameManager" input project's configurations (CKInput::m_aaInputDico[project];
    // IKGameManager_ResetRuntimeImpl); states 2, 3 and 5 enable its first configuration's entry 0 (skip).
    CKInputDico* m_pCommonInputDicos;
    // +0x2ec the game state machine (owner +0x2ec, table +0x2f0, count +0x2f4, state +0x2f5): 1 auto-load,
    // 2, 3 logos, 4 copyrights, 5 press start, 6 main menu, 7 in game, 8 pause, 9 hero death. The
    // constructor sets the state 0xff.
    StateMachine m_gameState;
    uint8_t m_ui8PrevState;                   // +0x2f8 the state at the start of the frame (or the one switched to on request)
    uint8_t m_ui8UpdatedState;                // +0x2f9 the state after the frame's update
    uint8_t m_ui8RequestedState;              // +0x2fa a switch request, 0xff none (vfAC sets 0xff)
    uint8_t m_pad2FB;
    int32_t m_unk2FC;                         // +0x2fc Init: 1; State6 enter: 1 = the main menu, 2 = the chapter menu (vt+0xc4) or 6
    uint32_t m_unk300;                        // +0x300
    // +0x304 the interface state machine (owner +0x304, table +0x308, count +0x30c, menu +0x30d): the
    // menu shown, NoMenuId (0x24) for none. The constructor sets the menu 0xff.
    StateMachine m_interfaceState;
    uint8_t m_aMenuStack[8];                  // +0x310 the requested menus; the top is m_aMenuStack[depth - 1]
    uint32_t m_ui32MenuStackDepth;            // +0x318 the constructor sets 0; the states set 1 with a new menu
    uint8_t m_ui8PrevMenu;                    // +0x31c the menu before the last switch
    uint8_t m_pad31D[3];
    float m_fUnk320;                          // +0x320 ResetRuntime: FLT_MAX (TOC +0x7090 -> +0x28); flags 0x200: time * 0.06
    uint32_t m_unk324;                        // +0x324 Init: 0
    uint32_t m_unk328;                        // +0x328 Init: 0xffff
    uint32_t m_unk32C[0x4d];                  // +0x32c
    IKSerializable* m_unk460;                 // +0x460 mode 1
    CKVideoSegment* m_unk464;                 // +0x464 the interface video's segment (vt+0x308 / +0x30c); PostLoad: 0
    // +0x468 the interface video's fade (FloatApproach: target, speed, current; 0 .. 255); the constructor
    // sets 0.0 (TOC +0x6ff8), the none interface state 255, 0, 255.
    float m_unk468[3];
    TVector<IKSerializable*, 8> m_unk474;     // +0x474 mode 1 (references): the new-game CKS08GameStates (GAME.KP3: one), vt+0x2f0
    uint8_t m_aUnk480[8];                     // +0x480 per-frame bytes (UpdateCommon moves them to +0x488, then clears them)
    uint8_t m_aUnk488[8];                     // +0x488
    IKSerializable* m_unk490;                 // +0x490 mode 0
    uint32_t m_unk494;                        // +0x494
    uint8_t m_unk498[9];                      // +0x498 mode 1: read raw
    uint8_t m_unk4A1;                         // +0x4a1 mode 1
    uint8_t m_unk4A2;                         // +0x4a2 mode 1
    uint8_t m_unk4A3;                         // +0x4a3 ResetRuntime: 0
    CTriggerStarter m_unk4A4;                 // +0x4a4 mode 0
    CTriggerStarter m_unk4AC;                 // +0x4ac mode 0
    CTriggerStarter m_unk4B4;                 // +0x4b4 mode 0
    IKSerializable* m_unk4BC;                 // +0x4bc mode 0
    IKSerializable* m_unk4C0;                 // +0x4c0 mode 0
    IKSerializable* m_unk4C4;                 // +0x4c4 mode 0
    uint32_t m_unk4C8;                        // +0x4c8
    uint8_t m_unk4CC;                         // +0x4cc
    uint8_t m_unk4CD;                         // +0x4cd 0
    uint16_t m_pad4CE;
    uint32_t m_unk4D0;                        // +0x4d0 0
    uint32_t m_unk4D4;                        // +0x4d4
    IKSerializable* m_unk4D8;                 // +0x4d8 mode 0
    float m_unk4DC;                           // +0x4dc 0.0
    IKSerializable* m_unk4E0;                 // +0x4e0 mode 0
    uint8_t m_unk4E4[0x200];                  // +0x4e4 cleared
    uint8_t m_unk6E4[0x400];                  // +0x6e4 cleared
    uint8_t* m_unkAE4;                        // +0xae4 0; the tips shown so far (one flag per tip pair, PickRandomTipText)
    // ---- CKS08GameManager (+0xae8) ----
    uint8_t m_unkAE8;                         // +0xae8
    uint8_t m_unkAE9;                         // +0xae9 0
    uint16_t m_padAEA;
    IKSerializable* m_unkAEC;                 // +0xaec mode 0
    IKSerializable* m_unkAF0;                 // +0xaf0 mode 0
    uint8_t m_unkAF4[6];                      // +0xaf4 mode 1: six bytes
    uint16_t m_padAFA;
    uint32_t m_unkAFC;                        // +0xafc flags (VfC4: bit 5)
    CTriggerStarter m_unkB00;                 // +0xb00 mode 0
    IKSerializable* m_unkB08[0x24];           // +0xb08 mode 0 (Vf344)
    IKSerializable* m_apHudInterfaces[5];     // +0xb98 mode 0 (GetHudInterfaces)
    float m_afUnkBAC[2];                      // +0xbac boss gauge: the zones' health total, their maximum total
    TVector<IKSerializable*, 5> m_unkBB4;     // +0xbb4 a 5-element block: the boss zones (CKHkS08CrumblyZoneMultiState)
    float m_afUnkBC0[2];                      // +0xbc0 the second boss gauge's totals
    TVector<IKSerializable*, 5> m_unkBC8;     // +0xbc8 a 5-element block: the second boss's zones
    float m_unkBD4;                           // +0xbd4 a HUD countdown (UpdateInGameHud)
    uint32_t m_unkBD8;                        // +0xbd8 mode 0 (HUD)
    IKSerializable* m_unkBDC;                 // +0xbdc mode 0
    uint32_t m_unkBE0;                        // +0xbe0 mode 0 (HUD)
    void* m_apHudTextures[16];                // +0xbe4 mode 0: textures (IKFile_ReadTextureRef, resolved), read in a fixed order
    // The two dragons' combo timers (UpdateComboTimers): Spyro's elapsed time and timer, Cynder's, then the two
    // hit counts (Spyro's, Cynder's).
    float m_fUnkC24;                          // +0xc24 Spyro's combo: elapsed time
    float m_fUnkC28;                          // +0xc28 Cynder's combo: elapsed time
    float m_fUnkC2C;                          // +0xc2c Spyro's combo: timer
    float m_fUnkC30;                          // +0xc30 Cynder's combo: timer
    uint32_t m_unkC34;                        // +0xc34 Spyro's combo: hits
    uint32_t m_unkC38;                        // +0xc38 Cynder's combo: hits
    uint32_t m_unkC3C;                        // +0xc3c mode 0 (HUD)
    float m_fUnkC40;                          // +0xc40 mode 0 (HUD): the combo timer's acceleration
    IKSerializable* m_unkC44;                 // +0xc44 mode 0 (HUD)
    SRecord m_aUnkC48[5];                     // +0xc48 mode 0, read from the last
    SRecord m_aUnkC84[5];                     // +0xc84 mode 0, read from the last
    uint32_t m_unkCC0[0x32];                  // +0xcc0 mode 1 (GetCounterTextVarTable)
    IKSerializable* m_unkD88;                 // +0xd88
    uint32_t m_unkD8C[2];                     // +0xd8c
    uint32_t m_unkD94;                        // +0xd94
    IKSerializable* m_unkD98;                 // +0xd98
    IKSerializable* m_unkD9C[2];              // +0xd9c
    uint32_t m_unkDA4;                        // +0xda4
    IKSerializable* m_unkDA8;                 // +0xda8
    IKSerializable* m_unkDAC;                 // +0xdac
    IKSerializable* m_unkDB0;                 // +0xdb0
    IKSerializable* m_unkDB4;                 // +0xdb4
    uint32_t m_unkDB8[2];                     // +0xdb8
    uint32_t m_unkDC0;                        // +0xdc0
    uint32_t m_unkDC4;                        // +0xdc4
    uint32_t m_unkDC8;                        // +0xdc8
    uint32_t m_unkDCC[4];                     // +0xdcc
    IKSerializable* m_unkDDC;                 // +0xddc
    IKSerializable* m_unkDE0;                 // +0xde0
    IKSerializable* m_unkDE4;                 // +0xde4
    uint32_t m_unkDE8;                        // +0xde8
    uint32_t m_unkDEC;                        // +0xdec
    uint32_t m_unkDF0;                        // +0xdf0
    uint32_t m_unkDF4[0x11];                  // +0xdf4 PostLoad (mode 0) sets +0xdf8..+0xe34
    IKSerializable* m_unkE38;                 // +0xe38
    IKSerializable* m_unkE3C;                 // +0xe3c
    IKSerializable* m_unkE40;                 // +0xe40
    IKSerializable* m_unkE44;                 // +0xe44
    uint32_t m_unkE48;                        // +0xe48
    IKSerializable* m_aRefTable[5][3];        // +0xe4c LoadRefTable: rows of three
    IKSerializable* m_unkE88[3];              // +0xe88 a counted list (the file's count; it runs over +0xe8c/+0xe90)
    uint32_t m_unkE94[3];                     // +0xe94
    float m_unkEA0;                           // +0xea0 Start: -1.0 (TOC1 +0x7204); CKS08GameManager_Update counts it down
    uint32_t m_unkEA4;                        // +0xea4 its high byte: a sector notification is pending (Update)
    uint32_t m_unkEA8[6];                     // +0xea8
    IKSerializable* m_unkEC0;                 // +0xec0
    IKSerializable* m_unkEC4;                 // +0xec4
    IKSerializable* m_unkEC8[12];             // +0xec8
    IKSerializable* m_unkEF8;                 // +0xef8
    IKSerializable* m_unkEFC;                 // +0xefc
    IKSerializable* m_unkF00[7];              // +0xf00
    uint32_t m_unkF1C;                        // +0xf1c
    IKSerializable* m_unkF20;                 // +0xf20
    IKSerializable* m_unkF24;                 // +0xf24
    uint32_t m_unkF28;                        // +0xf28
};
DOTD_ASSERT_SIZE(CKS08GameManager, 0xf2c);
DOTD_ASSERT_SIZE(CKS08GameManager::StateMachine, 0xc);
DOTD_ASSERT_OFFSET(CKS08GameManager, m_unk2A8, 0x2a8);
DOTD_ASSERT_OFFSET(CKS08GameManager, m_unk2BC, 0x2bc);
DOTD_ASSERT_OFFSET(CKS08GameManager, m_unk2D0, 0x2d0);
DOTD_ASSERT_OFFSET(CKS08GameManager, m_unk2C8, 0x2c8);
DOTD_ASSERT_OFFSET(CKS08GameManager, m_pCommonInputDicos, 0x2e8);
DOTD_ASSERT_OFFSET(CKS08GameManager, m_gameState, 0x2ec);
DOTD_ASSERT_OFFSET(CKS08GameManager, m_ui8PrevState, 0x2f8);
DOTD_ASSERT_OFFSET(CKS08GameManager, m_ui8RequestedState, 0x2fa);
DOTD_ASSERT_OFFSET(CKS08GameManager, m_unk2FC, 0x2fc);
DOTD_ASSERT_OFFSET(CKS08GameManager, m_interfaceState, 0x304);
DOTD_ASSERT_OFFSET(CKS08GameManager, m_aMenuStack, 0x310);
DOTD_ASSERT_OFFSET(CKS08GameManager, m_ui32MenuStackDepth, 0x318);
DOTD_ASSERT_OFFSET(CKS08GameManager, m_ui8PrevMenu, 0x31c);
DOTD_ASSERT_OFFSET(CKS08GameManager, m_fUnk320, 0x320);
DOTD_ASSERT_OFFSET(CKS08GameManager, m_unk328, 0x328);
DOTD_ASSERT_OFFSET(CKS08GameManager, m_unk464, 0x464);
DOTD_ASSERT_OFFSET(CKS08GameManager, m_unk468, 0x468);
DOTD_ASSERT_OFFSET(CKS08GameManager, m_unk460, 0x460);
DOTD_ASSERT_OFFSET(CKS08GameManager, m_unk474, 0x474);
DOTD_ASSERT_OFFSET(CKS08GameManager, m_unk490, 0x490);
DOTD_ASSERT_OFFSET(CKS08GameManager, m_unk498, 0x498);
DOTD_ASSERT_OFFSET(CKS08GameManager, m_unk4A4, 0x4a4);
DOTD_ASSERT_OFFSET(CKS08GameManager, m_unk4BC, 0x4bc);
DOTD_ASSERT_OFFSET(CKS08GameManager, m_unk4D8, 0x4d8);
DOTD_ASSERT_OFFSET(CKS08GameManager, m_unk4E4, 0x4e4);
DOTD_ASSERT_OFFSET(CKS08GameManager, m_unkAE4, 0xae4);
DOTD_ASSERT_OFFSET(CKS08GameManager, m_unkAEC, 0xaec);
DOTD_ASSERT_OFFSET(CKS08GameManager, m_unkAF4, 0xaf4);
DOTD_ASSERT_OFFSET(CKS08GameManager, m_unkAFC, 0xafc);
DOTD_ASSERT_OFFSET(CKS08GameManager, m_unkB00, 0xb00);
DOTD_ASSERT_OFFSET(CKS08GameManager, m_unkB08, 0xb08);
DOTD_ASSERT_OFFSET(CKS08GameManager, m_apHudInterfaces, 0xb98);
DOTD_ASSERT_OFFSET(CKS08GameManager, m_unkBB4, 0xbb4);
DOTD_ASSERT_OFFSET(CKS08GameManager, m_unkBC8, 0xbc8);
DOTD_ASSERT_OFFSET(CKS08GameManager, m_unkBD8, 0xbd8);
DOTD_ASSERT_OFFSET(CKS08GameManager, m_apHudTextures, 0xbe4);
DOTD_ASSERT_OFFSET(CKS08GameManager, m_unkC3C, 0xc3c);
DOTD_ASSERT_OFFSET(CKS08GameManager, m_aUnkC48, 0xc48);
DOTD_ASSERT_OFFSET(CKS08GameManager, m_aUnkC84, 0xc84);
DOTD_ASSERT_OFFSET(CKS08GameManager, m_unkCC0, 0xcc0);
DOTD_ASSERT_OFFSET(CKS08GameManager, m_unkD88, 0xd88);
DOTD_ASSERT_OFFSET(CKS08GameManager, m_unkD9C, 0xd9c);
DOTD_ASSERT_OFFSET(CKS08GameManager, m_unkDC0, 0xdc0);
DOTD_ASSERT_OFFSET(CKS08GameManager, m_unkDDC, 0xddc);
DOTD_ASSERT_OFFSET(CKS08GameManager, m_unkDF0, 0xdf0);
DOTD_ASSERT_OFFSET(CKS08GameManager, m_unkE38, 0xe38);
DOTD_ASSERT_OFFSET(CKS08GameManager, m_aRefTable, 0xe4c);
DOTD_ASSERT_OFFSET(CKS08GameManager, m_unkE88, 0xe88);
DOTD_ASSERT_OFFSET(CKS08GameManager, m_unkEA8, 0xea8);
DOTD_ASSERT_OFFSET(CKS08GameManager, m_unkEC8, 0xec8);
DOTD_ASSERT_OFFSET(CKS08GameManager, m_unkEF8, 0xef8);
DOTD_ASSERT_OFFSET(CKS08GameManager, m_unkF00, 0xf00);
DOTD_ASSERT_OFFSET(CKS08GameManager, m_unkF20, 0xf20);
