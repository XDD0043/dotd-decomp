// CKGameLoop.h - the game loop (key 0x4c, vtable 0xb138e8, size 0x3c0). Original unit: CKGameLoop.cpp
// (0x1dea0-0x228b8).
//
// main calls Run -> GameLoop once per frame. GameLoop drives an 11-mode state machine (table 0xc4b070)
// and then, in order: time, input, sound, UpdateGame, render, system callbacks
// (outputs/remake/research/boot-and-platform.md section 2). The mode names come from Ghidra and do not
// all match what the modes do at run time: the front end and gameplay both run in mode 5.
#pragma once
#include <cstdint>

#include "k2000/core/IKUpdatable.h"
#include "k2000/core/Layout.h"
#include "k2000/io/LoadRequests.h"

class CDefaultGameManager;
class CKErrorTable;
class CKGraphic;
class CKInput;
class CKLoadingManager;
class CKSavingManager;
class CKServiceManager;
class CKSoundManager;
class CRenderer;
class IKTime;
class KHostFS;
class CTimeManager;

#if defined(_MSC_VER)
// MSVC picks the pointer-to-member representation from the declaration it sees first; the mode table
// is declared inside the class, so state the (single) inheritance up front.
class __single_inheritance CKGameLoop;
#endif

class CKGameLoop : public IKUpdatable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 1)

    enum Mode : uint8_t {
        kModeBoot = 0,        // 0x22520 Mode0_Boot: pad init, GAME.KP3, loc files, boot data
        kModeInit = 1,        // 0x221e8 Mode1_Init: load the requested level (LVL000 first)
        kModeResume = 2,      // 0x1e4a8 Mode2_Resume_maybe
        kModePauseMenu = 3,   // 0x20b98 Mode3_PauseMenu_maybe: the language reload (GLC/LLC)
        kModeStartLevel = 4,  // 0x1e538 Mode4_StartLevel_maybe: Start, then 5
        kModeLevel = 5,       // 0x212f0 Mode5_LevelStart: front end and gameplay run here
        kModeLevelLoad = 6,   // 0x20498 Mode6_LevelLoad
        kModeLoading = 7,     // 0x21678 Mode7_Loading
        kModeInGame = 8,      // 0x1f960 Mode8_InGame (the pause menu at run time)
        kModeLevelExit = 9,   // 0x213c8 Mode9_LevelExit
        kModeQuit = 10,       // 0x1e5b8 Mode10_Quit
        kModeCount = 11,
        kModeNone = 0xff,
    };
    enum ModePhase : int32_t { kPhaseTick = 0, kPhaseEnter = 1, kPhaseLeave = 2 };

    // A mode handler: tick returns the next mode; enter and leave get the other mode.
    typedef uint8_t (CKGameLoop::*ModeHandler)(IKTime* frameClock, int32_t phase, uint8_t otherMode);
    static const ModeHandler kModeHandlers[kModeCount];  // 0x00c4b070

    CKGameLoop();                                    // 0x0001ef38 CKGameLoop_ConstructBase_maybe (= 0x1f0e0)
    ~CKGameLoop() override;                          // vt+0x00 / +0x04  0x22758 / 0x22128

    static IKBaseClass* Create();                       // 0x0001f0a0 CKGameLoop_Create
    static void Delete(IKBaseClass* object);
    static IKBaseClass* CreateArray(uint32_t count, uint16_t* elementSize);  // 0x0001f2f8
    static void DeleteArray(IKBaseClass* first);       // 0x0001f248

    int32_t IsKindOfClass(uint32_t key) override {        // vt+0x08 0x992cb0
        return key == 0x4c || key == 0x3fe || key == 0xc;
    }
    void Destroy() override {}               // vt+0x10 0x21398 (empty)
    void SetDefaultState(int32_t mode) override; // vt+0x38 0x1f658 CKGameLoop_vf38
    void Start() override;                    // vt+0x50 0x1ffe0
    void Restart() override;                  // vt+0x54 0x1fe20 CKGameLoop_ReinitRuntime
    void PreRestart() override;               // vt+0x5c 0x1f570 CKGameLoop_BroadcastPreReinit_maybe
    void Vf60() override;                     // vt+0x60 0x1f488 CKGameLoop_BroadcastPostReinit_maybe
    void Vf64() override;                         // vt+0x64 0x1f3a0 CKGameLoop_vf64
    void Stop() override;                         // vt+0x68 0x1fa28 CKGameLoop_StopAll_maybe
    void PreSectorLoaded(int32_t sector) override;   // vt+0x84 0x1f7b0 CKGameLoop_NotifySectorLoaded_maybe
    void SectorLoaded(int32_t sector) override;      // vt+0x88 0x202d8 CKGameLoop_NotifySectorActivate
    void SectorUnload(int32_t sector) override;      // vt+0x8c 0x21130 CKGameLoop_NotifySectorDeactivate
    void PostSectorUnload(int32_t sector) override;  // vt+0x90 0x20150 CKGameLoop_NotifySectorUnload_maybe
    void Pause() override;                           // vt+0x70 0x1fcd8
    void Resume() override;                          // vt+0x78 0x1fb90
    void Update(IKTime*) override {}                 // vt+0x7c 0x992c88 (inline, empty)
    // vt+0x74 0x992c98 CKGameLoop_IsVideoMode_maybe (inline): 1 in mode 8 (the paused in-game mode), else 0. A cutscene video waits for
    // it to be 0 before it inhibits the loop (PS3_CKVideo's state 1).
    int32_t Vf74() override { return m_mode == kModeInGame ? 1 : 0; }
    // vt+0x94 0x1eae8 InitializeCKGameLoopSubsystems
    virtual int32_t InitializeSubsystems(void* startupContext);
    // vt+0x98 0x20780 CKGameLoop_ShutdownSubsystems_maybe  STUB(C1.6)
    virtual void ShutdownSubsystems();

    // 0x00021848 GameLoop: one frame. Returns 0 once the mode is 10 (quit).
    uint32_t RunFrame();

    void SetGameManager(CDefaultGameManager* manager);   // 0x0001e7f8 CKGameLoop_SetGameManager
    // 0x0001f938 CKGameLoop_RequestSectorLoad_maybe: a sector change requested (mode 5 goes to 6); -2 asks for
    // the current sector (a restart in place).
    void RequestSectorLoad(int32_t sector);
    void RequestExit();                                  // 0x0001e828 CKGameLoop_RequestExit_maybe
    void SetAppActive(uint8_t active);                   // 0x00020ff8 CKGameLoop_SetAppActive_maybe
    uint8_t IsExitRequested() const { return m_exitRequested; }  // 0x0001e458 _maybe
    uint8_t IsShutdownReady() const { return m_shutdownReady; }  // 0x0001e468 _maybe
    uint8_t HasEnteredQuit() const { return m_quitEntered; }     // 0x0001e478 _maybe
    void ShutdownAndExit();                              // 0x0001e650 CKGameLoop_ShutdownAndExit_maybe

    // Mode handlers (kModeHandlers order).
    uint8_t Mode0_Boot(IKTime* frameClock, int32_t phase, uint8_t otherMode);
    uint8_t Mode1_Init(IKTime* frameClock, int32_t phase, uint8_t otherMode);
    uint8_t Mode2_Resume(IKTime* frameClock, int32_t phase, uint8_t otherMode);
    uint8_t Mode3_PauseMenu(IKTime* frameClock, int32_t phase, uint8_t otherMode);   // the language reload
    uint8_t Mode4_StartLevel(IKTime* frameClock, int32_t phase, uint8_t otherMode);
    uint8_t Mode5_LevelStart(IKTime* frameClock, int32_t phase, uint8_t otherMode);
    uint8_t Mode6_LevelLoad(IKTime* frameClock, int32_t phase, uint8_t otherMode);   // a sector change
    uint8_t Mode7_Loading(IKTime* frameClock, int32_t phase, uint8_t otherMode);     // STUB(C1.6)
    uint8_t Mode8_InGame(IKTime* frameClock, int32_t phase, uint8_t otherMode);
    uint8_t Mode9_LevelExit(IKTime* frameClock, int32_t phase, uint8_t otherMode);
    uint8_t Mode10_Quit(IKTime* frameClock, int32_t phase, uint8_t otherMode);

    // +0x04/+0x08: a pointer-to-member {OPD 0xb37aa8 = KStub_Return1_1e4a0, adjustment 0} set by the
    // constructor. No reader is known yet; kept as raw words.
    uint32_t m_unk04;                       // +0x04
    uint32_t m_unk08;                       // +0x08
    int32_t m_stopReason;                   // +0x0c _maybe: 0 none, 1 inhibited, 2 exit, 3 GM vf108, 4 GM +0x290
    const ModeHandler* m_modeTable;         // +0x10 kModeHandlers
    uint8_t m_mode;                         // +0x14 Mode (kModeNone before the first switch)
    uint8_t m_modeCount;                    // +0x15 11
    uint8_t m_pad16[2];
    CKGameLoop* m_modeOwner;                // +0x18 this (the object the handlers are called on)
    uint8_t m_inhibitMessageBox;            // +0x1c queued system message boxes
    uint8_t m_inhibitJobMessage;            // +0x1d job message shown, or the system menu (XMB) open
    uint8_t m_pad1e[2];
    int32_t m_inhibitCount;                 // +0x20 +1/-1 on each inhibit edge
    int32_t m_requestedSector;              // +0x24 _maybe: -2 = none; otherwise mode 5 goes to 6
    KHostFS* m_hostFS;                      // +0x28
    CKServiceManager* m_serviceManager;     // +0x2c
    CTimeManager* m_timeManager;            // +0x30 (its clock is the frame clock)
    CKGraphic* m_graphic;                   // +0x34
    CRenderer* m_renderer;                  // +0x38
    CKInput* m_input;                       // +0x3c
    CKSoundManager* m_soundManager;         // +0x40
    CKLoadingManager* m_loadingManager;     // +0x44
    CKSavingManager* m_pSavingManager;       // +0x48
    CDefaultGameManager* m_gameManager;     // +0x4c (a CKS08GameManager)
    CKErrorTable* m_errorTable;             // +0x50
    uint8_t m_clockPausedByApp;             // +0x54 SetAppActive(0) paused a running clock
    uint8_t m_pendingSubsystemReset;        // +0x55 set by Start, cleared by UpdateGame
    uint8_t m_appActive;                    // +0x56 constructor: 1
    uint8_t m_exitRequested;                // +0x57
    uint8_t m_quitEntered;                  // +0x58 a mode handler returned 10 because of the exit request
    uint8_t m_unk59;                        // +0x59
    uint8_t m_shutdownReady;                // +0x5a set by ShutdownAndExit before the threads are joined
    uint8_t m_exitAllowed;                  // +0x5b _maybe constructor: 1; with m_exitRequested gives reason 2
    uint8_t m_unk5c;                        // +0x5c cleared every frame
    uint8_t m_pad5d[3];
    int32_t m_unk60;                        // +0x60
    int32_t m_unk64;                        // +0x64
    CKLoadRequestQueue m_loadQueue;         // +0x68
    GameLevelLoadRequest m_levelRequest;    // +0x140
    BootLoadRequest m_bootRequest;          // +0x1b0
    LocLoadRequest m_locRequest;            // +0x218
    CKMemcardRequestQueue m_memcardQueue;   // +0x280
    SaveDataRequest m_saveDataRequest;      // +0x358
};
DOTD_ASSERT_SIZE(CKGameLoop, 0x3c0);
DOTD_ASSERT_OFFSET(CKGameLoop, m_stopReason, 0x0c);
DOTD_ASSERT_OFFSET(CKGameLoop, m_modeTable, 0x10);
DOTD_ASSERT_OFFSET(CKGameLoop, m_mode, 0x14);
DOTD_ASSERT_OFFSET(CKGameLoop, m_inhibitCount, 0x20);
DOTD_ASSERT_OFFSET(CKGameLoop, m_hostFS, 0x28);
DOTD_ASSERT_OFFSET(CKGameLoop, m_gameManager, 0x4c);
DOTD_ASSERT_OFFSET(CKGameLoop, m_pendingSubsystemReset, 0x55);
DOTD_ASSERT_OFFSET(CKGameLoop, m_exitAllowed, 0x5b);
DOTD_ASSERT_OFFSET(CKGameLoop, m_loadQueue, 0x68);
DOTD_ASSERT_OFFSET(CKGameLoop, m_levelRequest, 0x140);
DOTD_ASSERT_OFFSET(CKGameLoop, m_bootRequest, 0x1b0);
DOTD_ASSERT_OFFSET(CKGameLoop, m_locRequest, 0x218);
DOTD_ASSERT_OFFSET(CKGameLoop, m_memcardQueue, 0x280);
DOTD_ASSERT_OFFSET(CKGameLoop, m_saveDataRequest, 0x358);

// 0x0001e890 UpdateGame
void UpdateGame(CKGameLoop* gameLoop);

// CKGameLoop.cpp globals (0x00c50efc..), named from their use.
extern uint8_t g_engineBusy;          // 0x00c50efc (word) _maybe: 1 inside the frame's update/render and the broadcasts
extern uint8_t g_bootLocLoaded;       // 0x00c50f00 _maybe: mode 0 step 2 done (render gate in GameLoop)
extern int32_t g_mode1Step;           // 0x00c50f14
extern int32_t g_mode0Step;           // 0x00c50f18
extern void* g_pScratchBuffer16k;     // 0x00c50d30: the 16 KB block InitializeSubsystems allocates first
