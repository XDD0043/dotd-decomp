// CDefaultGameManager.h - the engine-side game manager (key 0xc4c, vtable 0xb13550, size 0x298) and
// its unregistered base KBaseBCC. Original units: CDefaultGameManager.cpp, CDefaultGameManager_2.cpp.
// The game's CKS08GameManager (Spyro2008) derives from it and comes out of GAME.KP3.
//
// STUB(C1.6): only the fields and methods the game loop's boot path touches. The virtual slots between
// the ones declared here are not declared yet; the slot offsets are in the comments.
#pragma once
#include <cstdint>

#include "k2000/core/IKUpdatable.h"
#include "k2000/core/Layout.h"
#include "k2000/memory/KMemBuffer.h"
#include "k2000/services/CTriggerStarter.h"

class IKFile;
class IKSerializable;
class IKVideo;

class CKLevel;

// The game options (0x34 bytes): IKGameManager_ApplyOptions_maybe applies a block; the game manager holds
// the current ones (+0xb8, also the save data's) and the edited ones (+0xec, the options menus'). Names
// from what ApplyOptions does with each field.
struct SGameOptions {
    uint32_t m_ui32Language;      // +0x00 the language index (CLocManager); another one requests the reload
    uint8_t m_bSubtitles;         // +0x04 CKSrvSekensor_SetSubtitlesEnabled_maybe
    uint8_t m_unk05;              // +0x05 InitDefaultOptions: 1 (IKGameManager_ToggleOptionF1)
    uint8_t m_pad06[2];
    uint32_t m_ui32SoundOutput;   // +0x08 index into the output-mode table (0x00a6f380: 0, 1, 3, 4, 5)
    uint32_t m_ui32AspectRatio;   // +0x0c index into the aspect table (0x00a6f394: 4/3, 16/9)
    float m_afVolumes[3];         // +0x10 / +0x14 / +0x18 (CKSoundManager_SetVolumes_maybe takes them reversed)
    uint8_t m_abVibration[2];     // +0x1c / +0x1d per pad (CKInput_SetVibrationEnabled)
    uint8_t m_abUnk1E[2];         // +0x1e / +0x1f per player (IKGameManager_TogglePerPlayerOption10A)
    uint8_t m_abUnk20[2];         // +0x20 / +0x21 per player (IKGameManager_TogglePerPlayerOption10C)
    uint8_t m_pad22[2];
    int32_t m_i32ScreenOffsetX;   // +0x24 steps of 2 (CKGraphic +0x14)
    int32_t m_i32ScreenOffsetY;   // +0x28 steps of 2 (CKGraphic +0x18)
    uint8_t m_bAutosave;          // +0x2c _maybe (IKGameManager_ToggleAutosaveOption_maybe)
    uint8_t m_abMotionSensor[2];  // +0x2d / +0x2e per pad (CKInput_SetMotionSensorEnabled)
    uint8_t m_pad2f;
    uint32_t m_ui32Brightness;    // +0x30 0..10 (default 5): the video-out gamma
};
DOTD_ASSERT_SIZE(SGameOptions, 0x34);

class CKLocText;

class CDefaultGameManager : public IKUpdatable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x31)

    CDefaultGameManager();
    ~CDefaultGameManager() override;

    void Start() override;                                   // vt+0x50 0x0001a7d8 CDefaultGameManager_Start
    void Stop() override;                                    // vt+0x68 0x00013e08 IKGameManager_Stop
    void Pause() override {}                                 // vt+0x70 0x1a7b0 CDefaultGameManager_Pause (CGameManager_BasePause_maybe 0x134e0: empty)
    void Resume() override {}                                // vt+0x78 0x1a760 CDefaultGameManager_Resume (0x134e8: empty)
    void Update(IKTime* frameClock) override;                // vt+0x7c 0x0001a738 CDefaultGameManager_Update
    // vt+0x20 0x132b0 IKGameManager_FindNonRecreableInstances: the 7 players (pointer array) and the game structure.
    uint8_t FindNonRecreableInstances(int32_t category, uint32_t id, uint32_t count, void* out) override;
    // vt+0x9c 0x00013e78 CDefaultGameManager_OnLevelStart_maybe (UpdateGame's reset path, right after a Start):
    // the current spawn point activated, the level's launch scene started, the level start trigger signals queued.
    virtual void OnLevelStart();
    virtual void Init() = 0;                                  // vt+0xa0 (CKS08GameManager_Init 0x4ef738)
    virtual void VfA4() {}                                    // vt+0xa4 0x991268 (empty)
    virtual void VfAC() {}                                    // vt+0xac
    // C1.6 gm: vt+0xb4 0x0001a6d0 CDefaultGameManager_vfB4 (XXL2 ExitGame: the slot after ExitLevel, and
    // the code): RequestGameExit.
    virtual void ExitGame();
    // C1.6 gm: vt+0xb8 0x0001a6a8 CDefaultGameManager_ResetProgress_maybe (XXL2 NewGame, which calls
    // IKGameManager::BasicNewGame): BasicNewGame.
    virtual void NewGame();
    // vt+0xc4 0x991278 CDefaultGameManager_vfC4: 0 (CKS08GameManager: bit 5 of +0xafc).
    virtual uint8_t VfC4() { return 0; }
    // vt+0xc8 0x991280 (empty): a pad's port went missing (PollPs3ControllerState).
    virtual void HandleControllerDisconnect(uint8_t /*port*/) {}
    virtual uint32_t GetPlayerClassKey() = 0;                 // vt+0xd4 (CKS08GameManager: 0x780c CKS08Player)
    // vt+0xd8 0x00014fe8 IKGameManager_vfD8: the loading video of a level (-1 = the boot video, +0x84).
    virtual IKVideo* GetLoadingVideo(int32_t level);
    virtual IKVideo* GetInterfaceVideo() { return nullptr; }  // vt+0xdc 0x991288 (CKS08: +0x460, the menus' video)
    virtual IKVideo* GetDemoVideo() { return nullptr; }       // vt+0xe0 0x991290 _maybe (CKS08: +0x2e0)
    // vt+0xf4 0x9912b8: 0. Whether the system's background music may play during this video (PS3_CKVideo).
    virtual uint8_t AllowsBgmDuringVideo(IKVideo* /*video*/) { return 0; }
    // vt+0x104 0x00013408 CDefaultGameManager_RequestSave_maybe: byte +0x88 = the autosave option and `value`.
    // (The first argument, an 8-byte register on the PS3, is not used.) CKS08GameManager's (0x4ed220) then
    // calls vt+0x10c.
    virtual void RequestSave(uint32_t unused, uint8_t value);
    // vt+0x108 0x000153d8 CDefaultGameManager_vf108: a save-data request pending (flags +0x64 bits 1-5);
    // GameLoop's stop reason 3 (mode 5 -> 7) while non-zero.
    virtual uint8_t Vf108();
    // vt+0x10c 0x00014f20 CDefaultGameManager_SetSaveRequestFlag_maybe: byte +0x88 as RequestSave, and flags
    // +0x64 bit 1 set (a save request pending).
    virtual void SetSaveRequestFlag(uint32_t unused, uint8_t value);
    // vt+0x124 0x992a18 CDefaultGameManager_vf124: the zero vector at 0x00c50d64 (CKS08GameManager: the position of
    // the focused hero node's frame, 0x4eea60). CKLevel_Update reads it to find the hero's sector.
    virtual const float* GetFocusedHeroNodePosition();
    // vt+0x128 0x992a20 CDefaultGameManager_vf128 / vt+0x130 0x992a30 CDefaultGameManager_vf130: the zero vector at
    // 0x00c50d64 (CKS08GameManager: the focused hero's targeting position 0x4eda18, its move vector 0x4ed930). The
    // camera's heading lock reads them (step 5).
    virtual const float* GetFocusedHeroPosition();
    virtual const float* GetFocusedHeroMoveVector();
    // vt+0x120 (CKS08GameManager 0x004f6e78 GetFocusedHeroCamera_maybe): the focused hero's camera target (a CSGLeaf);
    // null here.
    virtual IKSerializable* GetFocusedHeroCamera() { return nullptr; }
    // vt+0x148 0x00013d60 IKGameManager_SwitchToFocusedHeroCamera_maybe: the camera follows the focused hero's target
    // (CKSrvCamera::SwitchCameraIfDifferent with blend 1.0); 0 when it was switched, 1 when it already followed it or
    // there is none.
    virtual uint8_t SwitchToFocusedHeroCamera();
    // vt+0x144 0x991320 CDefaultGameManager_vf144 (empty; CKS08GameManager 0x4eda80: the hero group's vt+0x184, which
    // runs CKHkS08Hero_UpdateModeFlagsAndTetherTimers_maybe 0x2dd340 for every hero: their camera targets).
    // CKSrvCamera::UpdateInitialize calls it.
    virtual void UpdateHeroCameraTargets() {}
    virtual uint8_t GetControlledHeroCount() { return 1; }    // vt+0x134 0x992a38
    virtual uint8_t GetMaxPlayers() { return 0; }             // vt+0x150 0x991330
    virtual uint8_t GetPlayerCount() { return 0; }            // vt+0x154 0x991338
    virtual uint8_t SetPlayerCount(uint32_t /*count*/) { return 0; }  // vt+0x158 0x991340
    // vt+0x160 / +0x164 0x991350 / 0x991358: the input-block action queries (CKInputBlockSequential_Update_maybe):
    // `action`'s filtered state / analog value for `player`. 0 and 0.0 (TOC1 -0x7f20) here.
    virtual uint8_t IsActionPressed(uint32_t /*action*/, uint8_t /*player*/) { return 0; }
    virtual float GetActionValue(uint32_t /*action*/, uint8_t /*player*/) { return 0.0f; }
    virtual uint8_t IsPlayerActive(int32_t /*player*/) { return 0; }  // vt+0x180 0x991390
    // vt+0x18c (CKS08GameManager 0x004ecd10 CKS08GameManager_vf18C): the filtered state of the button the player has for
    // the dialogue (0xff pressed); 0 here. Name ours.
    virtual uint8_t GetDialogueButtonState(int32_t /*player*/) { return 0; }
    virtual void SetPlayerActive(int32_t /*player*/, uint8_t /*active*/) {}  // vt+0x184 0x991398
    virtual uint32_t GetGameStructureClassKey() = 0;          // vt+0x194 (CKS08GameManager: 0x798c CKS08GameStructure)
    // vt+0x1c0 0x00016bb8 IKGameManager_RestoreDefaultOptions_maybe: the defaults (vt+0x1d0, the argument
    // passed on in r4) made current and applied.
    virtual void RestoreDefaultOptions(int32_t withLanguage);
    // vt+0x1c4 0x991498 IKGameManager_vf1C4 (empty): ApplyOptions' hook for the game's own options.
    virtual void ApplyGameOptions(SGameOptions* /*options*/, uint8_t /*current*/) {}
    // vt+0x1d0 0x00014750 CDefaultGameManager_InitDefaultOptions_maybe: the edited block set to the defaults
    // (with the system language when withLanguage is not 0).
    virtual void InitDefaultOptions(int32_t withLanguage);
    // C1.6 gm: vt+0x1d4 0x000172b0 CDefaultGameManager_vf1D4: the edited options set to the defaults
    // (vt+0x1d0 with 0) and applied as edited ones (ApplyOptions(+0xec, 0)). Name ours.
    virtual void ResetEditedOptions();
    // C1.6 gm: vt+0x1e4 0x137b0: 0 (CKS08GameManager: a video skip button pressed).
    virtual uint8_t IsVideoSkipPressed() { return 0; }
    // 0x000137b8 / 0x00014ef0 / 0x00014ec0 CDefaultGameManager_GetSkipVideoPromptText_maybe / GetSkipCinematicPromptText_maybe /
    // GetCannotSkipPromptText_maybe: texts 1, 2 and 3 of the game manager's text accessor (+0x144, a CKLocTextAccessor), or its
    // single text (+0x10) without a list. Not virtual.
    const CKLocText* GetSkipVideoPromptText();
    const CKLocText* GetSkipCinematicPromptText();
    const CKLocText* GetCannotSkipPromptText();
    // C2.3: vt+0x1e8 / +0x1ec 0x4ed8b8 / 0x4ed878 CKS08GameManager_SetInputBlocked_maybe / IsInputBlocked_maybe: the
    // hero group's "input blocked" bit (+0xf8 bit 3); the base class has nothing (the IKGameManager stubs).
    virtual void SetInputBlocked(uint8_t /*blocked*/) {}
    virtual uint8_t IsInputBlocked() { return 0; }
    // vt+0x1f0 / +0x1f4 / +0x1f8 0x4edd20 / 0x4ede20 / 0x4ed7d8: the heroes' invulnerable bits (hero +0x35c bit 2) as a
    // mask (bit = dragon index), put back from a mask, or set for all.
    virtual void GetHeroesInvulnerableMask(uint32_t* /*mask*/) {}
    virtual void SetHeroesInvulnerableFromMask(const uint32_t* /*mask*/) {}
    virtual void SetAllHeroesInvulnerable(uint8_t /*invulnerable*/) {}
    // vt+0x20c 0x9914f8: 0 (CKS08: the current level is the front-end level, +0x2cc).
    virtual uint8_t IsFrontEndLevel() { return 0; }
    virtual IKSerializable* Vf214() { return nullptr; }       // vt+0x214 0x992a58 (CKS08: a CKStdText)
    // vt+0x21c 0x991510 CDefaultGameManager_vf21C (empty): a device button seen pressed this frame (device 0 pad, 2 mouse
    // / keyboard; CKInput_DetectButtonActivity_maybe 0x1053f8).
    virtual void NotifyInputActivity(int32_t /*device*/, int32_t /*button*/) {}
    virtual void HandlePauseInput(IKTime* frameClock) {}      // vt+0x224 _maybe
    virtual void UpdateSaveDataRequests();                    // vt+0x230 0x000178e8 IKGameManager_UpdateSaveDataRequests_maybe
    virtual void Vf23C() {}                                   // vt+0x23c 0x991538 (empty; the auto-load calls it)
    virtual void Vf240(int32_t /*result*/) {}                 // vt+0x240 0x991540 (empty; the load-game flow's end)

    // 0x00015ba0 CDefaultGameManager_InitImpl (the fields, players and game structure; the rest STUB(C1.6))
    void InitImpl();
    // 0x000170d0 CDefaultGameManager_ResetRuntimeImpl
    void ResetRuntimeImpl();
    // C1.6 gm: 0x000159a8 CDefaultGameManager_ResetProgressImpl_maybe (XXL2 IKGameManager::BasicNewGame:
    // the same player order): the UUID +0x8c cleared, +0x9c = -1, players 1..5, 0 and 6 InitializeNewGame
    // (vt+0x54), the save-state buffer cleared.
    void BasicNewGame();
    // C1.6 gm: 0x00014d68 CDefaultGameManager_RequestGameExit_maybe: CKGameLoop_RequestExit_maybe.
    void RequestGameExit();
    // 0x00014508 CDefaultGameManager_PostLoadImpl
    void PostLoadImpl(int32_t type);
    // 0x00016618 IKGameManager_UpdateAutoLoadFlow_maybe: the auto-load request (save data kind 3) posted,
    // then polled; *done once it finished. Returns 1 when finished.
    int32_t UpdateAutoLoadFlow(uint8_t* done);
    // 0x000167d0 IKGameManager_UpdateLoadGameFlow_maybe: the load request (save data kind 1) posted, then
    // polled. Loaded: player 6 copied into player 0 (its vt+0x50), vt+0x240(0), the options applied and
    // copied to the edited block; result 1: vt+0x240(1); otherwise the "no save data" system dialog (text
    // 0x169, YES/NO): YES retries, NO / escape ends the flow. *done once it ended; returns 1 once polled.
    int32_t UpdateLoadGameFlow(uint8_t* done);
    // 0x00016d78 CDefaultGameManager_LoadImpl: modes 0 (a level), 1 (GAME) and 6 (a save restore).
    void LoadImpl(IKFile* stream, int32_t mode);

    // ---- the options (CDefaultGameManager.cpp; the options menus call these) ----
    uint32_t HaveOptionsChanged();                                // 0x00013558 IKGameManager_HaveOptionsChanged
    uint8_t IsMotionSensorEnabled(int32_t player);                // 0x00013530 IKGameManager_IsMotionSensorEnabled
    void TogglePlayerVibration(int32_t player);                   // 0x000137f8 CDefaultGameManager_TogglePlayerVibration_maybe
    void ToggleVibrationBothPlayers();                            // 0x000138e8 CDefaultGameManager_ToggleVibrationBothPlayers_maybe
    void ApplyOptions(SGameOptions* options, uint8_t current);    // 0x00013920 IKGameManager_ApplyOptions_maybe
    void ApplyCurrentOptions();                                   // 0x00013c00 IKGameManager_ApplyCurrentOptions
    void ApplyEditedOptions();                                    // 0x00013c18 IKGameManager_ApplyEditedOptions
    void CommitEditedOptions();                                   // 0x00013c30 IKGameManager_CommitEditedOptions
    void CopyOptionsToEditBlock();                                // 0x00013cc8 IKGameManager_CopyOptionsToEditBlock
    void RecacheLocStringsAfterReload();                          // 0x00014618 CDefaultGameManager_RecacheLocStrings_maybe_2
    void SetFlag64Bit2();                                         // 0x00014f60 IKGameManager_SetFlag64Bit2_maybe
    void RefreshOptionsChangedFlag();                             // 0x00014f78 IKGameManager_RefreshOptionsChangedFlag
    void RevertOptions();                                         // 0x00016480 GameManager_RevertOptions_maybe
    void BackupOptions();                                         // 0x00016500 GameManager_BackupOptions_maybe
    void ToggleAutosaveOption();                                  // 0x00017320 IKGameManager_ToggleAutosaveOption_maybe
    void ResetScreenOffsetOption();                               // 0x00017340 IKGameManager_ResetScreenOffsetOption
    void ResetBrightnessOption();                                 // 0x00017368 IKGameManager_ResetBrightnessOption
    void ToggleSubtitlesOption();                                 // 0x00017388 IKGameManager_ToggleSubtitlesOption_maybe
    void ResetSoundAndAspectOptions();                            // 0x000173a8 IKGameManager_ResetSoundAndAspectOptions_maybe
    void ApplyEditedOptions2();                                   // 0x000173e8 IKGameManager_ApplyEditedOptions_2
    void CycleLanguageOption(int32_t backwards);                  // 0x00017400 IKGameManager_CycleLanguageOption
    void DecScreenOffsetYOption();                                // 0x00017498 IKGameManager_DecScreenOffsetYOption_maybe
    void DecScreenOffsetXOption();                                // 0x000174b8 IKGameManager_DecScreenOffsetXOption_maybe
    void ApplyEditedOptions3();                                   // 0x000174d8 IKGameManager_ApplyEditedOptions_3
    void TogglePerPlayerOption20(int32_t player);                 // 0x000174f0 IKGameManager_TogglePerPlayerOption10C
    void ToggleMotionSensorOption(int32_t player);                // 0x00017540 IKGameManager_ToggleMotionSensorOption
    void IncScreenOffsetXOption();                                // 0x00017588 IKGameManager_IncScreenOffsetXOption_maybe
    void ApplyEditedOptions4();                                   // 0x000175a8 IKGameManager_ApplyEditedOptions_4
    void ToggleAspectRatioOption(int32_t backwards);              // 0x000175c0 IKGameManager_ToggleAspectRatioOption
    void StepBrightnessOption(int32_t down);                      // 0x00017628 IKGameManager_StepBrightnessOption
    void IncScreenOffsetYOption();                                // 0x00017680 IKGameManager_IncScreenOffsetYOption_maybe
    void CycleSoundOutputOption(int32_t backwards);               // 0x000176a0 IKGameManager_CycleSoundOutputOption
    void TogglePerPlayerOption1E(int32_t player);                 // 0x00017708 IKGameManager_TogglePerPlayerOption10A
    void ToggleOption05();                                        // 0x00017758 IKGameManager_ToggleOptionF1
    void ToggleMotionSensorBothPlayersOption();                   // 0x00017780 IKGameManager_ToggleMotionSensorBothPlayersOption
    void TogglePerPlayerOption20BothPlayers();                    // 0x000177f8 IKGameManager_TogglePerPlayerOption10CBothPlayers
    void TogglePerPlayerOption1EBothPlayers();                    // 0x00017870 IKGameManager_TogglePerPlayerOption10ABothPlayers

    // Non-virtual helpers (CDefaultGameManager.cpp)
    // 0x000156d8 CDefaultGameManager_ClearReferencesImpl: SaveData_FreeWorkBuffer_maybe (0x2d100: the save
    // work buffer at 0x00c517b4 freed). STUB(save data): the remake has no such buffer.
    void ClearReferencesImpl() {}
    void UnloadCurrentLevel();          // 0x000162e8 CKS08GameManager_UnloadCurrentLevel_maybe
    void CommitRequestedLevel();        // 0x00014df8 CKS08GameManager_CommitRequestedLevel_maybe
    void ClearRequestedSector();        // 0x00013048 CKS08GameManager_ClearRequestedSector_maybe
    void RecacheLocStrings();           // 0x000162a0 CDefaultGameManager_RecacheLocStrings_maybe
    void ReloadLocalizedData();         // 0x00015208 GameManager_ReloadLocalizedData_maybe
    bool IsSaveDataBusy();              // 0x00013438 CDefaultGameManager_IsSaveDataBusy_maybe

    // The layout follows the PS3 (0x298 bytes); the fields the constructor (CKS08GameManager_ConstructBase_maybe
    // 0x4edee0, which inlines this class's) and the Loads touch are named, the others are m_unkXX.
    IKSerializable* m_unk04[5];  // +0x04 a level (mode 0) reads five references
    CKLevel* m_level;            // +0x18
    KMemBuffer m_unk1c;          // +0x1c
    IKFile* m_unk3c;             // +0x3c the save-state memory stream (InitImpl, STUB)
    IKSerializable* m_playerArray;     // +0x40 CreateObjectArray(GetPlayerClassKey(), 7)
    IKSerializable* m_players[7];      // +0x44 loaded as references (mode 1)
    uint16_t m_playerStride;     // +0x60
    uint16_t m_pad62;
    uint32_t m_flags64;          // +0x64
    uint32_t m_unk68;            // +0x68
    IKSerializable* m_gameStructure;   // +0x6c CreateObjectByKey(GetGameStructureClassKey())
    CTriggerStarter m_unk70;     // +0x70 mode 0
    CTriggerStarter m_unk78;     // +0x78 mode 0
    uint32_t m_unk80;            // +0x80
    IKSerializable* m_unk84;           // +0x84 a reference (mode 1)
    uint8_t m_unk88;             // +0x88
    uint8_t m_unk89;             // +0x89 InitImpl: 0
    uint16_t m_pad8a;
    uint32_t m_unk8c[4];         // +0x8c a UUID (constructor: 0)
    int32_t m_unk9c;             // +0x9c InitImpl: -1
    uint32_t m_unkA0[4];         // +0xa0 a UUID (constructor: 0)
    int32_t m_unkB0;             // +0xb0 InitImpl: -1
    uint8_t m_bSaveRequestPosted;  // +0xb4 the save-data request is posted (the flows set it, then poll)
    uint8_t m_padB5[3];
    SGameOptions m_currentOptions;  // +0xb8 the options in use; mode 6 (a save restore) reads them raw
    SGameOptions m_editedOptions;   // +0xec the options menus' copy (the defaults before a save loads)
    // +0x120..+0x143: BackupOptions' copies, restored by the options menus' resets.
    int32_t m_i32BackupScreenOffsetX;  // +0x120
    int32_t m_i32BackupScreenOffsetY;  // +0x124
    uint32_t m_ui32BackupSoundOutput;  // +0x128
    uint32_t m_ui32BackupAspectRatio;  // +0x12c
    float m_afBackupVolumes[3];        // +0x130
    uint32_t m_unk13C;                 // +0x13c
    uint32_t m_ui32BackupBrightness;   // +0x140
    IKSerializable* m_unk144;    // +0x144 mode 0
    uint32_t m_unk148;           // +0x148 0
    uint32_t m_unk14c;           // +0x14c 0
    uint8_t m_unk150;            // +0x150 0
    uint8_t m_unk151;            // +0x151 0xff
    uint16_t m_pad152;
    uint32_t m_unk154[6];        // +0x154 0
    KMemBuffer m_unk16c;         // +0x16c
    uint32_t m_unk18c;           // +0x18c
    KMemBuffer m_unk190;         // +0x190
    uint32_t m_unk1b0[0x14];     // +0x1b0
    KMemBuffer m_unk200;         // +0x200
    uint32_t m_unk220[4];        // +0x220 0
    uint32_t m_unk230[4];        // +0x230 0
    uint32_t m_unk240[2];        // +0x240
    uint8_t m_unk248;            // +0x248
    uint8_t m_unk249;            // +0x249 1
    uint16_t m_pad24a;
    uint32_t m_unk24c[2];        // +0x24c
    uint32_t m_unk254[4];        // +0x254 0
    uint32_t m_unk264[3];        // +0x264
    uint32_t m_unk270;           // +0x270 InitImpl: 1 (back to one player: the next IKGameManager_Update sets 1 player, then 0)
    int32_t m_unk274;            // +0x274 InitImpl: 9
    uint32_t m_unk278;           // +0x278
    int32_t m_currentLevel;      // +0x27c -1 = none
    int32_t m_requestedLevel;    // +0x280 -1 = none; GAME.KP3 sets 0 (LVL000)
    int32_t m_requestedSector;   // +0x284 -2 = the level's default sector
    int32_t m_unk288;            // +0x288
    int32_t m_unk28c;            // +0x28c
    int32_t m_unk290;            // +0x290 -1 = none; otherwise GameLoop exit reason 4
    uint8_t m_unk294;            // +0x294 render gate in GameLoop
    uint8_t m_pad295[3];
};
DOTD_ASSERT_SIZE(CDefaultGameManager, 0x298);
DOTD_ASSERT_OFFSET(CDefaultGameManager, m_unk04, 0x04);
DOTD_ASSERT_OFFSET(CDefaultGameManager, m_level, 0x18);
DOTD_ASSERT_OFFSET(CDefaultGameManager, m_playerArray, 0x40);
DOTD_ASSERT_OFFSET(CDefaultGameManager, m_players, 0x44);
DOTD_ASSERT_OFFSET(CDefaultGameManager, m_gameStructure, 0x6c);
DOTD_ASSERT_OFFSET(CDefaultGameManager, m_unk70, 0x70);
DOTD_ASSERT_OFFSET(CDefaultGameManager, m_unk84, 0x84);
DOTD_ASSERT_OFFSET(CDefaultGameManager, m_currentOptions, 0xb8);
DOTD_ASSERT_OFFSET(CDefaultGameManager, m_editedOptions, 0xec);
DOTD_ASSERT_OFFSET(CDefaultGameManager, m_i32BackupScreenOffsetX, 0x120);
DOTD_ASSERT_OFFSET(CDefaultGameManager, m_ui32BackupBrightness, 0x140);
DOTD_ASSERT_OFFSET(CDefaultGameManager, m_unk144, 0x144);
DOTD_ASSERT_OFFSET(CDefaultGameManager, m_unk16c, 0x16c);
DOTD_ASSERT_OFFSET(CDefaultGameManager, m_unk200, 0x200);
DOTD_ASSERT_OFFSET(CDefaultGameManager, m_unk249, 0x249);
DOTD_ASSERT_OFFSET(CDefaultGameManager, m_unk274, 0x274);
DOTD_ASSERT_OFFSET(CDefaultGameManager, m_currentLevel, 0x27c);
DOTD_ASSERT_OFFSET(CDefaultGameManager, m_unk28c, 0x28c);
DOTD_ASSERT_OFFSET(CDefaultGameManager, m_unk294, 0x294);

// 0x00013088 IKGameManager_UpdateLevelIfCtx30Zero_maybe: the level's Update while the clock runs.
void IKGameManager_UpdateLevel(CDefaultGameManager* manager, IKTime* frameClock);
// 0x00012fc0 IKGameManager_RestoreDefaultOptionsThenVfAC_IfFlag_maybe
void IKGameManager_RestoreDefaultOptionsThenVfAC_IfFlag(CDefaultGameManager* manager, int32_t flag);
// 0x00015160 LoadDefaultAndSystemLanguageLocFiles_maybe: 00GLC, then the system language's GLC.
void LoadDefaultAndSystemLanguageLocFiles(CDefaultGameManager* manager);
// 0x00014660 BootLoad_SetGameLoopActive_maybe
void BootLoad_SetGameLoopActive(CDefaultGameManager* manager);
