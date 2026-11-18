// CKS08GameManager.h - Spyro's game manager (key 0x784c, vtable 0xb2af78, size 0xf2c), loaded from
// GAME.KP3 and every level. Original units: CKS08GameManager*.cpp. PS3 chain: IKCommonGameManager
// (0x3b0c, unregistered; +0x298..+0xae8, vtable at TOC +0x6ff4) -> IKGameManager (here
// CDefaultGameManager). IKCommonGameManager is not a class of its own here: its fields, its Load
// (LoadCommon) and its code (the game state and interface state machines, Update) live in this class.
// C1.4 ports the front end: Init's tables, Update, the states 0-6 and the interface (menu) switching; C2.2..pre-C2.7
// the in-game states (7 in game, 8 pause menu, 9 hero death), the HUD and the heroes.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/math/CVector2.h"
#include "k2000/services/CTriggerStarter.h"
#include "k2000/util/TVector.h"

class CKInputDico;
class CKSoundOutputEffect;
class CKVideoSegment;
struct CVector3;

class CKS08GameManager : public CDefaultGameManager {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x1e1)

    // vt+0x08 0x009c6cb0 CKS08GameManager_IsKindOfClass: itself, IKCommonGameManager (0x3b0c, not a class of its own
    // here), IKGameManager's two bases and the root.
    int32_t IsKindOfClass(uint32_t key) override {
        return key == 0x784c || key == 0x3b0c || key == 0xbcc || key == 0x3fe || key == 0xc;
    }

    CKS08GameManager();  // 0x004f9408 CKS08GameManager_Construct (with 0x4edee0, the bases' part)
    // vt+0x00 / +0x04 0x004f9a60 CKS08GameManager_Destructor / 0x004f9988 _DeletingDestructor: the two boss zone blocks
    // freed, then IKCommonGameManager_DestructBody 0x4f0ed8 (its blocks +0x474 / +0x2d0 / +0x2bc freed, the menu stack
    // emptied; CDefaultGameManager's four KMemBuffers destroyed: their destructors, the members').
    ~CKS08GameManager() override;

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
    void Restart() override;                  // vt+0x54 0x004fa0e8 CKS08GameManager_Restart
    // 0x004f8618 CKS08GameManager_SpawnGemReward_maybe: `gems` split into the gem table's (+0xec0, three entries)
    // large (+0xeb8), medium (+0xeb4) and small (+0xeb0, the rest rounded to the nearest) counts, then dropped by the bonus
    // service at `pos` around `dir`.
    void SpawnGemReward(uint32_t gems, const CVector3* pos, const CVector3* dir);
    // 0x004f6b10 CKS08GameManager_GetBonusValue_maybe: a bonus type's value (types 1..6: the words +0xea8..+0xebc;
    // anything else 1).
    uint32_t GetBonusValue(uint32_t type) const { return type - 1u <= 5u ? m_unkEA8[type - 1u] : 1u; }
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
    // vt+0xa8 0x004ef6a8 CKS08GameManager_vfA8: ReleaseGameData, then both state machines emptied (their tables freed,
    // no state).
    void ReleaseManager() override;
    void VfAC() override;                     // vt+0xac 0x004f6eb8 CKS08GameManager_vfAC (the front end restarts)
    void ExitGame() override;                 // vt+0xb4 0x004ed298 CKS08GameManager_vfB4: CDefaultGameManager's RequestGameExit
    // vt+0xb8 0x004f80f8 CKS08GameManager_ResetGameProgress_maybe (XXL2 NewGame): IKCommonGameManager's
    // NewGame, +0xe98 = -1, the game structure's new-game progress, the new-game state (+0x474 entry 0,
    // vt+0x2f0) applied to it, player 0's game state taken from it (vt+0x58) and copied to player 6
    // (vt+0x50); with flag 0x80 (+0x64) the structure's vt+0x58.
    void NewGame() override;
    // vt+0xc0 0x004f70d0 CKS08GameManager_vfC0: 0x004edcc8 IKCommonGameManager_vfC0: the game state (+0x2f5) is none
    // of 1..5 (the auto-load, logos, copyrights, press start).
    uint8_t VfC0() override { return static_cast<uint32_t>(m_gameState.m_ui8Current) - 1u > 4u ? 1 : 0; }
    uint8_t VfC4() override { return static_cast<uint8_t>((m_unkAFC >> 5) & 1); }  // vt+0xc4 0x9c7028
    // vt+0xc8 0x004ee1a8 CKS08GameManager_HandleControllerDisconnect_maybe: pad 0 lost: the "TRC_WIIMOTE_SLOT" /
    // "TRC_PAD_SLOT" text variables 1 and the system job 500; another pad, unless the game has one player (vt+0x154)
    // or a save request is pending (+0x64 bit 1): +0x4d0 = 1, the reconnect message box (text 0x3e9, interrupted by
    // pad 1 coming back), +0x4d4 = 0, one player (vt+0x158).
    void HandleControllerDisconnect(uint8_t port) override;
    IKVideo* GetInterfaceVideo() override;   // vt+0xdc 0x9c6a78: m_unk460
    IKVideo* GetDemoVideo() override;        // vt+0xe0 0x9c69f8: m_unk2E0
    // vt+0xf4 0x004ec878 CKS08GameManager_vfF4: not during the logos (state 3); during press start (5)
    // only for videos other than the demo (vt+0xe0).
    uint8_t AllowsBgmDuringVideo(IKVideo* video) override;
    uint8_t Vf108() override { return CDefaultGameManager::Vf108(); }  // vt+0x108 0x4ed1f8
    void RequestSave(uint32_t unused, uint8_t value) override;         // vt+0x104 0x004ed220 CKS08GameManager_RequestSave_maybe
    // C2.8 save-menu (CKS08GameManager_3.cpp).
    // vt+0x24 0x004f7280 CKS08GameManager_RecursiveRegistration: IKCommonGameManager's (0x4ed698: CDefaultGameManager_
    // LevelResetImpl), type 0 the music, the death state's objects and the trigger starter +0xb00, then the referenced
    // objects (texts, FX data, sound dictionaries, ...) with `type`.
    void RecursiveRegistration(int32_t type) override;
    // vt+0x28 0x004f8f18 CKS08GameManager_Save: IKCommonGameManager's (0x4ed670: CDefaultGameManager_SaveImpl), then
    // KStub_Nop_4fe300; 1.
    int32_t Save(IKFile* file, int32_t type) override;
    void BuildSaveDetailText(uint16_t* text) override;        // vt+0xf8 0x004f6e18 (the stats menu's, CKS08MenuStatsGame)
    const uint16_t* GetSaveSubtitleText() override;          // vt+0xfc 0x004f8858: the current spawn point's name
    void Vf234() override;                                    // vt+0x234 0x004f8940 CKS08GameManager_SetOnlyMainPlayerActive_maybe
    void OnSaveGameDone(int32_t result) override;             // vt+0x238 0x004f8318 CKS08GameManager_OnSaveGameDone_maybe
    void SetSaveRequestFlag(uint32_t unused, uint8_t value) override;  // vt+0x10c 0x004f7130
    uint8_t GetControlledHeroCount() override;                   // vt+0x134 0x004ed8f0
    // 0x004f9628 CKS08GameManager_SpawnSurfaceFx: the explosion data of surface `surface` (0..4) and kind `mode`
    // (0..2) (+0xe4c [surface][mode]): its sounds at `volume`, then one of its explosions from the FX pool set off at
    // `position` for `owner`.
    void SpawnSurfaceFx(float volume, const IKSerializable* owner, uint32_t surface, uint32_t mode, const float* position);
    uint8_t GetMaxPlayers() override { return 2; }               // vt+0x150 0x9c6d38
    uint8_t GetPlayerCount() override { return m_unkAE9; }       // vt+0x154 0x9c6d40
    uint8_t SetPlayerCount(uint32_t count) override;             // vt+0x158 0x004f68e0
    // vt+0x258 0x009c6d18 CKS08GameManager_vf258: the channel of the sound marks (0x1b, "MarkI_Sound"; vt+0x254
    // 0x009c6d10 answers 0x1a, "MarkI_Activate"). CKMarkedSoundDico_UpdateFromAnimMarks_maybe asks it.
    uint32_t GetSoundMarkChannel() const { return 0x1b; }
    // vt+0x160 0x004ecdd0 CKS08GameManager_IsActionPressed / vt+0x164 0x004ecf80 _GetActionValue: entry
    // player * 50 + action of the common input configuration (+0x2e8) for actions below 50, else
    // (GetMaxPlayers() * 25 + player) * 2 + action - 50 (byte-wrapped).
    uint8_t IsActionPressed(uint32_t action, uint8_t player) override;
    float GetActionValue(uint32_t action, uint8_t player) override;
    // vt+0x168 0x004ecea8 CKS08GameManager_vf168 (C2.8 port-rest R10): the same entry's filter type (0x0010eb00).
    uint8_t GetActionFilterType(uint32_t action, uint8_t player) override;
    // vt+0x14c 0x009c6868 CKS08GameManager_vf14C: "IKCommonGameManager" (TOC +0x6fbc -> 0xacac68). vt+0x15c 0x004ec7e8
    // CKS08GameManager_vf15C: the stick directions 0..7 are the actions 10..17, else -1. vt+0x16c 0x009c6880
    // CKS08GameManager_vf16C: 50 actions. (C2.8 port-all P06, for the input blocks.)
    const char* GetInputProjectName() override { return "IKCommonGameManager"; }
    int32_t GetStickDirectionAction(uint32_t direction) override { return direction < 8 ? static_cast<int32_t>(direction) + 10 : -1; }
    uint8_t GetActionCount() override { return 0x32; }
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
    // vt+0x210 0x004f1a38 CKS08GameManager_vf210 (C2.8 port-rest R10): on the front-end level +0x2fc = 1 and the game
    // state switches to 5 (press start), 1; else out of the pause (8 -> 7), then Vf2EC: when it answers, +0x2fc = 0, 1.
    uint8_t Vf210() override;
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
    // C2.8 port-all P12 (CKS08GameManager_2.cpp / _3.cpp): slots without a known caller are plain methods.
    uint8_t IsFlag480ClearedThisFrame(int32_t index) const;  // 0x004ec798
    uint8_t* Vf228();                                        // vt+0x228 0x004ec928: +0x4e4
    uint8_t* Vf22C();                                        // vt+0x22c 0x004ec938: +0x6e4
    uint8_t Vf190(int32_t index) const;                      // vt+0x190 0x004eccb0
    uint8_t GetCommonDirectionActionState(int32_t direction) const;  // 0x004ecd70 IKCommonGameManager_GetDirectionActionState_maybe
    void VfB0() override;                                    // vt+0xb0 0x004ed2c0: SetRequestedLevel(0)
    IKSerializable* GetFocusedHeroNode() const;              // 0x004edab8 CKS08GameManager_GetFocusedHeroNode_maybe
    const float* GetFocusedHeroNodeForward();                // 0x004ed9c0 CKS08GameManager_GetFocusedHeroNodeForward_maybe
    uint8_t IsNoRestartPending() const;                      // 0x004edc78 CKS08GameManager_IsNoRestartPending_maybe
    uint8_t Vf94Slot();                                      // vt+0x94 0x004f7080 (IKCommonGameManager 0x4ec438)
    uint8_t Vf98Slot();                                      // vt+0x98 0x004f70a8 (IKCommonGameManager 0x4ec440)
    // 0x004fbd70 CKS08GameManager_SpawnExplosionFx / 0x004fbb08 _SpawnDefaultExplosionFx_maybe (CKS08GameManager_3.cpp).
    void SpawnExplosionFx(IKSerializable* owner, int32_t index, const CVector3* position);
    void SpawnDefaultExplosionFx(uint32_t unused, IKSerializable* owner, const CVector3* position);
    int32_t GetInfo(IKInfo* info, int32_t request) override;  // vt+0x40 0x004f7e90 (the trigger values)
    void DestroyGame() override;                            // vt+0x0c 0x004ed6c0
    uint8_t SwitchInterfaceStateToStackTop();               // 0x004eff30
    void VfD0();                                            // vt+0xd0 0x004f7dc8 (the save is done)
    void VfBC(uint8_t value);                               // vt+0xbc 0x004f8208 (the save-slot menu)
    // vt+0xcc 0x004f9d60 (C2.8 port-rest R10; the save-check flow's slot choice) and its IKCommonGameManager part
    // 0x004ec458 (CKS08Damage.cpp).
    uint8_t VfCC(uint8_t value, int32_t* slot) override;
    uint8_t VfCCCommon();
    void VfF0();                                            // vt+0xf0 0x004f9c00 (leave the pause)
    void HideFuryGaugeIfShown();                            // 0x004feef0 CKS08GameManager_HideFuryGaugeIfShown_maybe
    void RefreshComboCountText();                           // 0x00503900 CKS08GameManager_RefreshComboCountText_maybe
    void UpdateCenterTwinGauges();                          // 0x00500b78 CKS08GameManager_UpdateCenterTwinGauges_maybe
    uint8_t IsAnyMenuButtonActive();                        // 0x004ee4d0 CKS08GameManager_IsAnyMenuButtonActive_maybe
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
    // vt+0x268 0x009c6928 CKS08GameManager_vf268: empty (the hazard hit's notification; not virtual here).
    void Vf268(uint8_t /*damage*/, uint8_t /*hero*/, uint8_t /*flag*/) {}
    uint8_t Vf270(uint8_t /*hero*/) const { return 0xff; }
    // vt+0x2c0 0x009c69d0 / vt+0x2c4 0x009c69d8 / vt+0x2c8 0x009c69e0 CKS08GameManager_vf2C0 / vf2C4 / vf2C8: empty (the
    // hero's surface timer gauge shown, hidden and set: UpdateMainShadowAndSurfaceFx; not virtual here).
    void Vf2C0(uint8_t /*flag*/, uint8_t /*hero*/) {}
    void Vf2C4(uint8_t /*flag*/, uint8_t /*hero*/) {}
    void Vf2C8(float /*value*/, uint8_t /*flag*/, uint8_t /*hero*/) {}
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
    // vt+0x2ec 0x004f8090 CKS08GameManager_vf2EC: player 0's game state applied to the game structure (vt+0x60), then
    // IKCommonGameManager's part (0x004ec560 IKCommonGameManager_vf2EC, CKS08Damage.cpp): the front-end level
    // (+0x2cc) requested (vt+0x2e4 with sector 0). The pause menu's quit answered yes (CKS08MenuPause_MessageProc).
    virtual uint8_t Vf2EC();
    uint8_t Vf2ECCommon();
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
    void ReinitRuntime();                   // 0x004f27b0 IKGameManager_ReinitRuntimeImpl
    void VfACCommon();                      // 0x004f1d90 IKCommonGameManager_vfAC: the game state set to 1
    // 0x004eed08 CKS08GameManager_ResetProgress_maybe (XXL2 IKCommonGameManager::NewGame, which CKA2's NewGame
    // calls first): BasicNewGame, vt+0x334, flags +0x64 &= ~0x80, +0x2fc = 2 (the front end comes back on
    // the chapter menu).
    void NewGameCommon();
    // 0x00502410 ResetDragonStatHud: the dragon stat fields cleared, then the HUD texts and gauges refreshed.
    void ResetDragonStatHud();
    // 0x00502340 ResetDragonStatHud_2 (CKS08GameManager_Restart): the HUD texts and gauges refreshed first, then the
    // dragon stat fields cleared.
    void ResetDragonStatHud2();
    // 0x004f6b78 CKS08GameManager_RequestStoredMusicTrack_maybe (CKS08GameManager_3.cpp; C2.8 carry-mechs-2): the play list
    // kept at +0xef8 asked again (CKSrvMusic_RequestTrack_maybe, no clear) when there is one.
    void RequestStoredMusicTrack();

    // ---- C2.2 gm: the in-game start and the HUD ----
    // One player's HUD slot (the +0x2c8 array, GetMaxPlayers() entries, 8 bytes on the PS3): the hero that
    // wants a panel this frame (set by the hero) and a flag. The game manager clears them every frame.
    struct PlayerHudSlot {
        IKSerializable* m_pHero;  // +0x00
        uint8_t m_ui8Flag;        // +0x04
    };
    PlayerHudSlot* PlayerHudSlots() { return static_cast<PlayerHudSlot*>(m_unk2C8); }
    // 0x004ee770 SetHeroInteractionTarget (C2.8 meca-hero): `target` (with its byte `arg`) becomes the interaction target
    // of player `player` (its slot above; message 0x2666 asks it for the prompt text) unless the target held has the
    // same class id, or comes first in the priority list +0x2bc; the hero must hold or be the target, be the group, or
    // pass CanAttachTo. 1 when set.
    uint8_t SetHeroInteractionTarget(IKSerializable* target, uint8_t arg, uint8_t player);
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
    // ---- C2.7 step 7: the HUD pieces (CKS08GameManager_5.cpp unless noted) ----
    // 0x00502a80 CKS08GameManager_UpdateCounterTextVariables_maybe: the text variables 5..10 of the counter table
    // (vt+0x354) take the game structure's bytes +0x1e4..+0x1e9.
    void UpdateCounterTextVariables();
    // 0x004fb848 SpawnElementGroundFx_maybe (CKS08GameManager_3.cpp; the breath's ground scorch): the particle effect
    // data of the element (+0xe8c + 4 x type, a CKParticlesEffectFxData) placed at `position` (its matrix +0x24, the
    // internal-identity flag cleared), its byte +0x08 bit 4 cleared, then a pooled effect of it started for `owner`
    // (CKSrvFx::AcquireFx) and its reservation let go (vt+0x54).
    void SpawnElementGroundFx(const IKSerializable* owner, uint32_t type, const CVector3* position);
    // pre-C2.7 gamemgr, a collectible picked up (CKS08GameManager_5.cpp unless noted): 0x004f8cc0
    // CKS08GameManager_PlayCollectibleMusic_maybe (_3.cpp: the play list +0xefc requested), 0x00501a08
    // ShowCollectedItemMessage_maybe, 0x004ffdd0 QueueFirstCollectibleInfo_maybe, 0x00501938 QueueCollectibleMessage_maybe,
    // 0x005032d0 RefreshHealthShardHud_maybe / 0x00502ca0 RefreshManaShardHud_maybe (the dragon's shard gauge and the
    // info page when `show`).
    void PlayCollectibleMusic();
    void ShowCollectedItemMessage(uint8_t a, uint8_t b, uint8_t c);
    void QueueFirstCollectibleInfo();
    void QueueCollectibleMessage();
    void RefreshHealthShardHud(uint8_t dragon, uint32_t show);
    void RefreshManaShardHud(uint8_t dragon, uint32_t show);
    // 0x004fd438 IsFuryGaugeFull_2_maybe (CKS08GameManager_3.cpp): 1 with +0x64 bit 24, else whether the game structure's
    // +0x74 + +0x78 equals +0x7c.
    uint8_t IsFuryGaugeFull2() const;
    // 0x00501860 CKS08GameManager_ShowCenterMessage_maybe: the accessor +0xf14's text `index` queued on the centre HUD.
    void ShowCenterMessage(uint8_t index);
    // 0x005039e8 ShowSpyroSelectedElementHud / 0x005024d8 ShowCynderSelectedElementHud: the element's sound (elements
    // 0-4: dictionary +0xbdc entry 1 + element / 6 + element), the panel's element bar run with the texture +0xbfc /
    // +0xc10 [element], then the stat change feedback.
    void ShowSpyroSelectedElementHud(uint8_t element);
    void ShowCynderSelectedElementHud(uint8_t element);
    // 0x00501fb8 ShowDragonStatChangeFeedback_maybe: the dragon's panel: the upgrade text (shaking unless the panel is
    // already active), message out 1, the panel up and active, its timer restarted.
    void ShowDragonStatChangeFeedback(int32_t dragon);
    // 0x00501700 CKS08GameManager_CloseDragonHudTimedPanel_maybe: the dragon's HUD panel (0: [0] Spyro's, 1: [2]
    // Cynder's) closes its timed panel.
    void CloseDragonHudTimedPanel(int32_t dragon);
    // 0x00500418 CKS08GameManager_AddDragonUpgradePoints_maybe: points added to the dragon's free points (capped at
    // the four levels' costs, the records +0xc50.. / +0xc8c..), the "upgrade available" info at the first 5000, the text.
    void AddDragonUpgradePoints(uint8_t dragon, uint32_t points);
    // vt+0x360 0x00503df0 OnComboHit_comboStart / vt+0x368 0x00503ba0 OnNewHit_continuecombo / vt+0x364 0x004fffe0
    // CKS08GameManager_EndComboDisplay_maybe: the combo text variables 0x30 / 0x31 (the two hit counts) and the dragon's
    // combo display. Not declared as virtuals yet (nothing overrides them; the callers are the hero's combat, C2.7
    // wave 2).
    void OnComboHitComboStart(uint8_t dragon, float value);
    void OnNewHitContinueCombo(uint8_t dragon, float value);
    void EndComboDisplay(int32_t dragon);
    void UpdateBossGaugeTotals();               // 0x004ff318
    void UpdateSecondBossGaugeTotals();         // 0x004ff540
    // The boss gauge (the boss HUD, vt+0x34c [3]), when it exists (C2.8 golem): 0x004feb00 SetBossGaugeHealth_maybe
    // (+0xf4), 0x004fea60 SetEnemyGaugeMaxHealth_maybe (+0xf8), 0x004fe9c0 SetEnemyGaugeMaxHealth_2_maybe (+0xfc),
    // 0x00501ea0 RefreshBossGauge_maybe (its message out 1 posted, +0xe0 bit 0 set, the timer +0xf0 cleared).
    void SetBossGaugeHealth(float value);
    void SetEnemyGaugeMaxHealth(float value);
    void SetEnemyGaugeMaxHealth2(float value);
    void RefreshBossGauge();
    // The fight zone gauge (CKS08FightZoneCpnt mode 5: the crumbly zones' health) on the second boss HUD (vt+0x34c [4]),
    // when it exists: 0x004fe920 SetFightZoneGaugeValue_maybe (+0xf4), 0x004fe880 SetFightZoneGaugeMax_maybe (+0xf8),
    // 0x004fe7e0 SetFightZoneGaugeMax2_maybe (+0xfc), 0x00501c90 SendFightZoneHudMessageAndClearTimer_maybe (its message
    // out 1 posted, +0xe0 bit 0 set, the timer +0xf0 cleared).
    void SetFightZoneGaugeValue(float value);
    void SetFightZoneGaugeMax(float value);
    void SetFightZoneGaugeMax2(float value);
    void SendFightZoneHudMessageAndClearTimer();
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
    // 0x004fe148 IsFuryGaugeFull_maybe: the two dragons' fury (the game structure's +0x74 + +0x78) at its cap (+0x7c,
    // also stored in `capacity`), or the cheat flag +0x64 bit 24 (CKS08GameManager_4.cpp).
    uint8_t IsFuryGaugeFull(uint32_t* capacity);
    void ConsumeDragonMana(int32_t dragon, uint32_t amount);            // 0x004fd808
    // 0x004fe1a0 AddDragonFuryFromAttack_maybe: the combo's hits scaled by the fury curve (+0xaec at the hits) added to the
    // dragon's fury (the game structure's +0x74 / +0x78), the two together at most +0x7c; the fury gauge refreshed.
    void AddDragonFuryFromAttack(uint8_t dragon, uint32_t hits);
    void RefreshFuryGaugeHud();  // 0x004fec98 (CKS08GameManager_4.cpp)
    // pre-C2.7 gamemgr, the pause menu's cheat codes (CKS08MenuPause_ApplyCheatCode_maybe 0x55dd18):
    // 0x004fd480 SetEquippedArmor_maybe (_3.cpp): the armour (0..3, else nothing) put in `slot` of the dragon (the game
    // structure's +0xb4 + 3 dragon + slot).
    void SetEquippedArmor(uint8_t dragon, uint8_t slot, uint32_t armor);
    // 0x004fd528 AddDragonFury_maybe (_3.cpp): `amount` added to the dragon's fury (the game structure's +0x74 / +0x78),
    // the two together at most +0x7c; the fury gauge refreshed (any dragon).
    void AddDragonFury(int32_t dragon, uint32_t amount);
    // 0x004fdb28 DrainDragonFury_maybe (_4.cpp): `amount` taken from the dragon's fury (0 / 1, down to 0); `shared`:
    // both dragons' fury set to half the total less half the amount (fctidz each half), or both 0.
    void DrainDragonFury(int32_t dragon, uint32_t amount, int32_t shared);
    void QueueUpgradeAvailableInfo();  // 0x004ffaf0 CKS08GameManager_QueueUpgradeAvailableInfo_maybe (_5.cpp)
    uint32_t GetDragonFury(int32_t dragon);  // 0x004fd680 GetDragonFury_maybe (_4.cpp): +0x74 / +0x78, else 0
    uint32_t GetTotalFury();                 // 0x004fd420 GetTotalFury_maybe (_4.cpp): +0x74 + +0x78
    // 0x00500880 CKS08GameManager_CheatMaxUpgradePoints_maybe (_5.cpp): 1000000 upgrade points for each dragon.
    void CheatMaxUpgradePoints();
    uint32_t GetDragonHealthCapacity(int32_t dragon);                   // 0x004fd940
    uint32_t GetDragonHealth(int32_t dragon);                           // 0x004fd9c8
    uint32_t GetElementLevel(uint8_t dragon, uint8_t element);          // 0x004f9558 (CKS08GameManager_3.cpp)
    void DamageDragon(int32_t dragon, uint32_t amount);                 // 0x004fda08
    void RestoreDragonMana(int32_t dragon, int32_t amount, int32_t quiet);    // 0x004fdca8 (CKS08GameManager_4.cpp)
    void RestoreDragonHealth(int32_t dragon, int32_t amount, int32_t quiet);  // 0x004fdef8 (CKS08GameManager_4.cpp)
    // 0x004fe330 CKS08GameManager_RegisterBossGaugeZone_maybe (CKS08GameManager_4.cpp) / 0x004feba0
    // .._RegisterSecondBossGaugeZone_maybe (_5.cpp): `zone` appended to +0xbb4 / +0xbc8 unless it is in the list already
    // (the block grows by 5 when full).
    void RegisterBossGaugeZone(IKSerializable* zone);
    void RegisterSecondBossGaugeZone(IKSerializable* zone);
    // 0x005022b0 RefreshDragonStatDisplays_maybe (CKS08GameManager_5.cpp): the health and / or mana gauges and their
    // capacity markers, then the stat change feedback (0x501fb8).
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
    uint8_t StateInGameCommon(int32_t phase, uint8_t other);    // 0x004f4fa0 IKCommonGameManager_StateInGame_maybe
    uint8_t StateMenuCommon(int32_t phase, uint8_t other);      // 0x004f5128 CKS08GameManager_StateMenuCommon_maybe
    uint8_t StateHeroDeathCommon(int32_t phase, uint8_t other); // 0x004f48d0 IKCommonGameManager_StateHeroDeath_maybe
    uint8_t StateReturn10(int32_t phase, uint8_t other);        // 0x004f48f0 KStub_Return10_4f48f0
    uint8_t StateReturn11(int32_t phase, uint8_t other);        // 0x004f48f8 KStub_Return11_4f48f8
    uint8_t State2(int32_t phase, uint8_t other);               // 0x00504248 CKS08GameManager_State2_maybe
    uint8_t State4(int32_t phase, uint8_t other);               // 0x005044e0 CKS08GameManager_State4_maybe (copyrights)
    uint8_t State5(int32_t phase, uint8_t other);               // 0x00504750 CKS08GameManager_State5_maybe (press start)
    uint8_t State6(int32_t phase, uint8_t other);               // 0x00504040 CKS08GameManager_State6_maybe (main menu)
    uint8_t StateInGame(int32_t phase, uint8_t other);          // 0x005043a8 CKS08GameManager_StateInGame_maybe
    uint8_t StateMenuPause(int32_t phase, uint8_t other);       // 0x00504990 CKS08GameManager_StateMenuPause
    uint8_t StateHeroDeath(int32_t phase, uint8_t other);       // 0x00504c88 CKS08GameManager_StateHeroDeath_maybe
    // 0x004f8750 CKS08GameManager_StartDeathSequence_maybe (CKS08GameManager_3.cpp): the death mode (1 or 2) and the
    // dragon that died kept, the other heroes' model nodes hidden (scene flag 4: Spyro's when Cynder died, Cynder's
    // otherwise), then game state 9 requested.
    void StartDeathSequence(uint8_t mode, uint8_t dragon);
    // 0x004f89d8 CKS08GameManager_IsAnyMenuButtonPressed_maybe (CKS08GameManager_3.cpp): a button 10..18 of the
    // "Flash Manager" project's second configuration held.
    uint8_t IsAnyMenuButtonPressed();
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
    // +0x324 Init: 0; the pause menu (StateMenuCommon) keeps the sound output's current environment here while it
    // shows environment 0.
    CKSoundOutputEffect* m_unk324;
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
    IKSerializable* m_unk4C8;                 // +0x4c8 the pause menu's effect of the FX data +0x4c4 (AcquireFx)
    uint8_t m_unk4CC;                         // +0x4cc
    uint8_t m_unk4CD;                         // +0x4cd 0
    uint16_t m_pad4CE;
    uint32_t m_unk4D0;                        // +0x4d0 0
    uint8_t m_ui8PausePlayer;                 // +0x4d4 the player whose pointer the pause menu shows (HandleControllerDisconnect: 0)
    uint8_t m_pad4D5[3];
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
    // ---- the hero death (game state 9, StateHeroDeath; the level's mode-0 part). Names ours. ----
    uint8_t m_ui8DeathMode;                   // +0xd8c StartDeathSequence: 0 none, 1 the camera rises, 2 the hero sinks
    uint8_t m_ui8DeathDragon;                 // +0xd8d StartDeathSequence: the dragon that died
    uint8_t m_padD8E[2];
    float m_fDeathTime;                       // +0xd90 the state's elapsed time
    float m_fDeathSkipDelay;                  // +0xd94 a menu button ends the state after this long (LVL010: 5)
    IKSerializable* m_unkD98;                 // +0xd98 CKMusicPlayList: the death music
    IKSerializable* m_unkD9C[2];              // +0xd9c CAnimationDictionary per dragon: the death animation (mode 2)
    float m_fDeathDuration1;                  // +0xda4 mode 1's length (LVL010: 9.5)
    IKSerializable* m_unkDA8;                 // +0xda8 CKCamera of mode 1
    // +0xdac / +0xdb0 CKFilterFxData, +0xdb4 CKHDRFxData: the three effects the state starts (+0xdcc..+0xdd4).
    IKSerializable* m_unkDAC;                 // +0xdac
    IKSerializable* m_unkDB0;                 // +0xdb0
    IKSerializable* m_unkDB4;                 // +0xdb4
    IKSerializable* m_unkDB8;                 // +0xdb8 a CKSekens the state stops when it ends (cleared on enter)
    float m_fDeathCameraSpeed;                // +0xdbc the death camera's rising speed (0 on enter)
    float m_fDeathCameraAccel;                // +0xdc0 its acceleration in mode 1 (mode 2: 3.0, TOC)
    float m_fDeathCameraMaxSpeed;             // +0xdc4 its top speed
    float m_fDeathCameraRollSpeed;            // +0xdc8 the camera's vt+0x88 value grows by this per second
    IKSerializable* m_apDeathFx[3];           // +0xdcc the effects of +0xdac / +0xdb0 / +0xdb4 (AcquireFx)
    uint32_t m_unkDD8;                        // +0xdd8
    IKSerializable* m_unkDDC;                 // +0xddc CKCamera of mode 2
    IKSerializable* m_unkDE0;                 // +0xde0 CColorizedScreenFx (mode 2's screen tint)
    IKSerializable* m_unkDE4;                 // +0xde4 CColorizedScreenData
    float m_fDeathSinkHeight;                 // +0xde8 mode 2: the hero sinks while higher than this above the ground
    float m_fDeathDuration2;                  // +0xdec mode 2's length
    float m_fDeathSinkAccel;                  // +0xdf0 mode 2: the sinking speed's acceleration
    uint32_t m_unkDF4[0x11];                  // +0xdf4 [0] the sinking speed (a float); PostLoad (mode 0) sets +0xdf8..+0xe34
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
    IKSerializable* m_unkF1C;                 // +0xf1c the effect of the FX data +0xf18 (Update, flag +0xafc bit 8)
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
DOTD_ASSERT_OFFSET(CKS08GameManager, m_ui8DeathMode, 0xd8c);
DOTD_ASSERT_OFFSET(CKS08GameManager, m_fDeathTime, 0xd90);
DOTD_ASSERT_OFFSET(CKS08GameManager, m_unkDB8, 0xdb8);
DOTD_ASSERT_OFFSET(CKS08GameManager, m_apDeathFx, 0xdcc);
DOTD_ASSERT_OFFSET(CKS08GameManager, m_fDeathSinkHeight, 0xde8);
DOTD_ASSERT_OFFSET(CKS08GameManager, m_fDeathCameraAccel, 0xdc0);
DOTD_ASSERT_OFFSET(CKS08GameManager, m_unkDDC, 0xddc);
DOTD_ASSERT_OFFSET(CKS08GameManager, m_fDeathSinkAccel, 0xdf0);
DOTD_ASSERT_OFFSET(CKS08GameManager, m_unkE38, 0xe38);
DOTD_ASSERT_OFFSET(CKS08GameManager, m_aRefTable, 0xe4c);
DOTD_ASSERT_OFFSET(CKS08GameManager, m_unkE88, 0xe88);
DOTD_ASSERT_OFFSET(CKS08GameManager, m_unkEA8, 0xea8);
DOTD_ASSERT_OFFSET(CKS08GameManager, m_unkEC8, 0xec8);
DOTD_ASSERT_OFFSET(CKS08GameManager, m_unkEF8, 0xef8);
DOTD_ASSERT_OFFSET(CKS08GameManager, m_unkF00, 0xf00);
DOTD_ASSERT_OFFSET(CKS08GameManager, m_unkF20, 0xf20);

// 0x004fd6d8 RefillAllDragonsMana / 0x004fd8d8 RefillAllDragonsHealth (CKS08GameManager_3.cpp).
void RefillAllDragonsMana(CKS08GameManager* manager);
void RefillAllDragonsHealth(CKS08GameManager* manager);
