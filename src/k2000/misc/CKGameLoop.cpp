// CKGameLoop.cpp - reconstructed original translation unit 0x1dea0-0x228b8 (GAME_TOC1, main_toc1), 83 functions, 61 live.
// Primary owner: CKGameLoop (not a registered class)
// Other owners: RegisterCKGameLoopClass (1), UpdateGame (1), StopLevelLoadingVideo (1), PlayLevelLoadingVideo (1), InitializeCKGameLoopSubsystems (1), GameLoop (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1dea0  CKGameLoop_Destroy
//   [ ] 0x1def0  FUN_0001def0  [dead]
//   [ ] 0x1df00  KStub_Nop_1df00  [dead]
//   [ ] 0x1df08  FUN_0001df08  [dead]
//   [ ] 0x1dfc0  FUN_0001dfc0  [dead]
//   [ ] 0x1e048  FUN_0001e048  [dead]
//   [ ] 0x1e0d0  FUN_0001e0d0  [dead]
//   [ ] 0x1e0e0  KStub_Nop_1e0e0  [dead]
//   [ ] 0x1e0e8  FUN_0001e0e8  [dead]
//   [ ] 0x1e148  KStub_Nop_1e148  [dead]
//   [x] 0x1e150  CKGameLoop_HasRequestedLevel_maybe  (CKGameLoop::HasRequestedLevel)
//   [x] 0x1e178  CKGameLoop_GetGlobalUpdateInhibitByte_maybe  (CKGameLoop_GetGlobalUpdateInhibitByte)
//   [x] 0x1e188  CKGameLoop_IncPauseCount_maybe  (CKGameLoop::IncPauseCount, CKGameLoop.h)
//   [x] 0x1e198  CKGameLoop_DecPauseCount_maybe  (CKGameLoop::DecPauseCount, CKGameLoop.h)
//   [ ] 0x1e1a8  FUN_0001e1a8  [dead]
//   [ ] 0x1e1f0  FUN_0001e1f0  [dead]
//   [x] 0x1e2e0  CKGameLoop_IsRequestedLevelWithGmFlag294_maybe
//   [x] 0x1e340  CKGameLoop_IsActiveModeWithGmVfC0_maybe
//   [ ] 0x1e410  KStub_Return1_1e410  [dead]
//   [x] 0x1e418  KStub_Return1_1e418  (the modal frame: returns 1; CFlashMessageBox2d.cpp KStub_Return1_1e418)
//   [ ] 0x1e420  KStub_Return1_1e420  [dead]
//   [ ] 0x1e428  FUN_0001e428  [dead]
//   [x] 0x1e458  CKGameLoop_IsExitRequested_maybe
//   [ ] 0x1e460  FUN_0001e460  [dead]
//   [x] 0x1e468  CKGameLoop_IsShutdownReady_maybe
//   [x] 0x1e478  CKGameLoop_GetFlag58_QuitEntered_maybe
//   [ ] 0x1e480  FUN_0001e480  [dead]
//   [ ] 0x1e488  FUN_0001e488  [dead]
//   [ ] 0x1e490  FUN_0001e490  [dead]
//   [ ] 0x1e498  FUN_0001e498  [dead]
//   [x] 0x1e4a0  KStub_Return1_1e4a0  (returns 1: its OPD is the constructor's raw +0x04 word, nothing calls it)
//   [x] 0x1e4a8  CKGameLoop_Mode2_Resume_maybe
//   [x] 0x1e538  CKGameLoop_Mode4_StartLevel_maybe
//   [x] 0x1e5b8  CKGameLoop_Mode10_Quit
//   [ ] 0x1e5c0  RegisterCKGameLoopClass
//   [ ] 0x1e640  _GLOBAL__I_1e640
//   [x] 0x1e650  CKGameLoop_ShutdownAndExit_maybe
//   [x] 0x1e7f8  CKGameLoop_SetGameManager
//   [x] 0x1e828  CKGameLoop_RequestExit_maybe
//   [ ] 0x1e858  FUN_0001e858  [dead]
//   [x] 0x1e890  UpdateGame
//   [ ] 0x1ea08  StopLevelLoadingVideo_maybe  [dead]
//   [x] 0x1ea38  PlayLevelLoadingVideo_maybe  (PlayLevelLoadingVideo)
//   [x] 0x1eae8  InitializeCKGameLoopSubsystems
//   [x] 0x1ef38  CKGameLoop_ConstructBase_maybe
//   [x] 0x1f0a0  CKGameLoop_Create
//   [x] 0x1f0e0  CKGameLoop_Construct
//   [x] 0x1f248  CKGameLoop_DestroyArray
//   [x] 0x1f2f8  CKGameLoop_CreateArray
//   [x] 0x1f3a0  CKGameLoop_vf64
//   [x] 0x1f488  CKGameLoop_BroadcastPostReinit_maybe
//   [x] 0x1f570  CKGameLoop_BroadcastPreReinit_maybe
//   [x] 0x1f658  CKGameLoop_vf38
//   [x] 0x1f7b0  CKGameLoop_NotifySectorLoaded_maybe
//   [x] 0x1f938  CKGameLoop_RequestSectorLoad_maybe
//   [x] 0x1f960  CKGameLoop_Mode8_InGame
//   [x] 0x1fa28  CKGameLoop_StopAll_maybe
//   [x] 0x1fb90  CKGameLoop_Resume
//   [x] 0x1fcd8  CKGameLoop_Pause
//   [x] 0x1fe20  CKGameLoop_ReinitRuntime
//   [x] 0x1ffe0  CKGameLoop_ResetRuntime
//   [x] 0x20150  CKGameLoop_NotifySectorUnload_maybe
//   [x] 0x202d8  CKGameLoop_NotifySectorActivate
//   [x] 0x20498  CKGameLoop_Mode6_LevelLoad
//   [x] 0x20780  CKGameLoop_ShutdownSubsystems_maybe
//   [x] 0x20b98  CKGameLoop_Mode3_PauseMenu_maybe
//   [x] 0x20ce0  CKGameLoop_vf24
//   [x] 0x20ff8  CKGameLoop_SetAppActive_maybe
//   [x] 0x21130  CKGameLoop_NotifySectorDeactivate
//   [x] 0x212f0  CKGameLoop_Mode5_LevelStart
//   [x] 0x21380  CKGameLoop_vf28  (Save: returns 1, the default slot)
//   [x] 0x21388  CKGameLoop_vf2C  (Load: returns 1, the default slot)
//   [x] 0x21390  CKGameLoop_vf30  (PostLoad: returns 1, the default slot)
//   [x] 0x21398  CKGameLoop_ClearReferences
//   [ ] 0x213a0  FUN_000213a0  [dead]
//   [x] 0x213c8  CKGameLoop_Mode9_LevelExit
//   [x] 0x21678  CKGameLoop_Mode7_Loading
//   [x] 0x21848  GameLoop
//   [x] 0x22128  CKGameLoop_DeletingDestructor
//   [x] 0x221e8  CKGameLoop_Mode1_Init
//   [x] 0x22520  CKGameLoop_Mode0_Boot
//   [x] 0x22758  CKGameLoop_Destructor
//   [x] 0x22808  CKGameLoop_Destructor_2  (the same body as 0x22758: ~CKGameLoop; no reference)
//
//   [x] 0x992c78  CKGameLoop_GetClassGroup  [inline]
//   [x] 0x992c80  CKGameLoop_GetClassId  [inline]
//   [x] 0x992c88  CKGameLoop_vf7C  [inline]
//   [ ] 0x992c90  CKGameLoop_vf34  [inline]
//   [ ] 0x992c98  CKGameLoop_IsVideoMode_maybe  [inline]
//   [x] 0x992cb0  CKGameLoop_IsKindOf  [inline]
#include "k2000/misc/CKGameLoop.h"

#include <cstdlib>

#include "k2000/core/Stub.h"
#include "k2000/fx/ParticleUpdateScheduler.h"
#include "k2000/graphical/system/CVideoManager.h"
#include "k2000/io/KFileSystem.h"
#include "k2000/io/KHostFS.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/logic/CKLevel.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/logic/io/CKLoadingManager.h"
#include "k2000/managers/CKGraphic.h"
#include "k2000/managers/CKInput.h"
#include "k2000/managers/CKServiceManager.h"
#include "k2000/managers/CKSoundManager.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/JobQueue.h"
#include "k2000/render/CRenderer.h"
#include "k2000/render/CShaderManagerPSGL.h"
#include "k2000/system/CellSysutilCallback.h"
#include "k2000/system/IKTime.h"
#include "k2000/system/CTimeManager.h"
#include "platform/audio/rwa.h"

// Globals of this unit (0x00c50efc..), and the two in .data at 0x00c29608.
uint8_t g_engineBusy = 0;     // 0x00c50efc (stored as a word)
uint8_t g_bootLocLoaded = 0;  // 0x00c50f00
int32_t g_mode1Step = 0;      // 0x00c50f14
int32_t g_mode0Step = 0;      // 0x00c50f18
void* g_pScratchBuffer16k = nullptr;  // 0x00c50d30 (InitializeCKGameLoopSubsystems; CKSrvCollision keeps it as m_aPotentialEdge)

// 0x0001e2e0 CKGameLoop_IsRequestedLevelWithGmFlag294_maybe
uint8_t CKGameLoop::IsRequestedLevelWithGmFlag294() const {
    if (g_bootLocLoaded == 0 || m_gameManager->m_requestedLevel == -1 || g_pEngine->m_gameManager->m_unk294 == 0) return 0;
    return MessageBox_GetJobMessageCount() == 0 ? 1 : 0;
}

namespace {
float s_savedMasterVolume = 1.0f;  // 0x00c29608 (SetAppActive)
float s_waitTime = 0.0f;           // 0x00c50f08 modes 7 and 9: the real time waited (the job message after 10 s)
int32_t s_languageFrames = 0;      // 0x00c50f0c mode 3: the frames left after the language reload
int32_t s_levelExitStep = 0;       // 0x00c50f10 mode 9: 0 the level stopping, 1 everything stopped
int32_t s_mode6Step = 0;           // 0x00c50f04 mode 6: 0 streaming the sector, 1 waiting to settle
constexpr float kLoadingMessageDelay = 10.0f;  // TOC 0xc0dd50 (0x41200000)
uint8_t s_mode1FromBoot = 1;       // 0x00c2960c (Mode1_Init enter)
void* s_scratchBuffer16k = nullptr;  // 0x00c50d30 (InitializeCKGameLoopSubsystems)

constexpr float kJobMessageAlpha = 1.0f;  // TOC 0xc0dd5c
constexpr float kMutedVolume = 0.0f;      // TOC 0xc0dd58
}  // namespace

// Other units' functions without a header of their own.
void KStub_Nop_1038c8(CKInput* input);  // CKInput.cpp
float SoundOutput_GetMasterVolume(CKSoundManager* manager);
void SoundOutput_SetMasterVolume(float volume, CKSoundManager* manager);
void CVideoManager_PauseAllVideos(CVideoManager* manager);
void CVideoManager_ResumeAllVideos(CVideoManager* manager);
// 0x000f39a0 ShaderUniforms_ReleaseBuiltinRecords_maybe: k2000/stubs/BootStubs.cpp (no built-in records).
void ShaderUniforms_ReleaseBuiltinRecords();

// 0x00c4b070: {OPD, adjustment 0} per mode.
const CKGameLoop::ModeHandler CKGameLoop::kModeHandlers[kModeCount] = {
    &CKGameLoop::Mode0_Boot,       &CKGameLoop::Mode1_Init,      &CKGameLoop::Mode2_Resume,
    &CKGameLoop::Mode3_PauseMenu,  &CKGameLoop::Mode4_StartLevel, &CKGameLoop::Mode5_LevelStart,
    &CKGameLoop::Mode6_LevelLoad,  &CKGameLoop::Mode7_Loading,   &CKGameLoop::Mode8_InGame,
    &CKGameLoop::Mode9_LevelExit,  &CKGameLoop::Mode10_Quit,
};

// 0x0001ef38 CKGameLoop_ConstructBase_maybe (0x1f0e0 CKGameLoop_Construct has the same body).
// The members' constructors run first, as the original constructs the queues and requests before
// filling the fields.
CKGameLoop::CKGameLoop() {
    m_stopReason = 0;
    m_mode = kModeNone;
    m_modeCount = kModeNone;
    m_modeCount = kModeCount;
    m_modeTable = kModeHandlers;
    m_unk04 = 0x00b37aa8;  // OPD of KStub_Return1_1e4a0 (raw value; see the header)
    m_modeOwner = this;
    m_unk08 = 0;
    m_mode = kModeBoot;
    m_requestedSector = -2;
    m_exitAllowed = 1;
    m_inhibitMessageBox = 0;
    m_inhibitJobMessage = 0;
    m_inhibitCount = 0;
    m_hostFS = nullptr;
    m_serviceManager = nullptr;
    m_graphic = nullptr;
    m_renderer = nullptr;
    m_input = nullptr;
    m_soundManager = nullptr;
    m_timeManager = nullptr;
    m_gameManager = nullptr;
    m_appActive = 1;
    m_clockPausedByApp = 0;
    m_pendingSubsystemReset = 0;
    m_exitRequested = 0;
    m_quitEntered = 0;
    m_unk59 = 0;
    m_shutdownReady = 0;
    m_errorTable = nullptr;
    m_loadingManager = nullptr;
    m_pSavingManager = nullptr;
    m_unk60 = 0;
    m_unk64 = 0;
}

// 0x00022758 CKGameLoop_Destructor, 0x00022128 CKGameLoop_DeletingDestructor: the embedded requests and queues
// destroyed, last first (SaveDataRequest_Destructor, CKMemcardRequestQueue_Destructor_maybe, LocLoadRequest_Destructor,
// BootLoadRequest_Destructor_maybe, GameLevelLoadRequest_Destructor, CKLoadRequestQueue_Destructor_maybe): the
// members' destructors, in C++'s reverse declaration order.
CKGameLoop::~CKGameLoop() {}

// 0x0001f0a0 CKGameLoop_Create
IKBaseClass* CKGameLoop::Create() { return new CKGameLoop(); }

void CKGameLoop::Delete(IKBaseClass* object) { delete object; }

// 0x0001f2f8 CKGameLoop_CreateArray
IKBaseClass* CKGameLoop::CreateArray(uint32_t count, uint16_t* elementSize) {
    if (elementSize != nullptr) *elementSize = 0x3c0;
    return new CKGameLoop[count];
}

// 0x0001f248 CKGameLoop_DestroyArray
void CKGameLoop::DeleteArray(IKBaseClass* first) { delete[] static_cast<CKGameLoop*>(first); }

// 0x0001eae8 InitializeCKGameLoopSubsystems
int32_t CKGameLoop::InitializeSubsystems(void* startupContext) {
    g_pScratchBuffer16k = Mem_AllocAligned16(0x4000);
    JobQueue* jobQueue = new JobQueue();
    Engine_SetJobQueue(jobQueue);
    CKErrorTable* errorTable = new CKErrorTable();
    m_errorTable = errorTable;
    errorTable->CreateErrorObjects();
    Engine_SetErrorTable(m_errorTable);
    CTimeManager* timeManager = new CTimeManager();
    m_timeManager = timeManager;
    dotd::trace::Boot("create CTimeManager + CKTime");  // trace only (not in the original)
    if (timeManager->Initialize() != 1) {
        Destroy();
        return 0;
    }
    Engine_SetTimeManager(m_timeManager);
    m_graphic = static_cast<CKGraphic*>(ClassRegistry_CreateObjectByKey(0x80));
    Engine_SetGraphic(m_graphic);
    if (m_graphic->InitializeModule(startupContext) != 1) return 0x10001;
    m_renderer = m_graphic->CreateRenderer(startupContext);
    if (m_renderer == nullptr) return 0;
    m_input = static_cast<CKInput*>(ClassRegistry_CreateObjectByKey(0x100));
    Engine_SetInput(m_input);
    Engine_SetInput(m_input);  // set twice in the original
    if (m_input->InitializeModule(startupContext) != 1) return 0;
    m_hostFS = KHostFS_Create();
    m_hostFS->Init();
    m_soundManager = static_cast<CKSoundManager*>(ClassRegistry_CreateObjectByKey(0xc0));
    Engine_SetSoundManager(m_soundManager);
    if (m_soundManager->InitializeModule(startupContext) != 1) return 0;
    Engine_SetSoundManager(m_soundManager);
    CVideoManager_InitRenderer(g_pEngine->m_graphic->m_renderer->m_videoManager);
    CKServiceManager* serviceManager = static_cast<CKServiceManager*>(ClassRegistry_CreateObjectByKey(0x40));
    m_serviceManager = serviceManager;
    if (serviceManager->InitializeModule(startupContext) != 1) return 0;
    Engine_SetServiceManager(m_serviceManager);
    g_pEngine->m_fileSystem->InitSaveDevice();
    m_loadingManager = static_cast<CKLoadingManager*>(ClassRegistry_CreateObjectByKey(0x1cc));
    m_loadingManager->KUInitialize();
    Engine_SetLoadingManager_2(m_loadingManager);
    m_pSavingManager = static_cast<CKSavingManager*>(ClassRegistry_CreateObjectByKey(0x18c));
    m_pSavingManager->KUInitialize();
    Engine_SetSavingManager(m_pSavingManager);
    Engine_SetLevel(static_cast<CKLevel*>(ClassRegistry_CreateObjectByKey(0x14c)));
    g_pShaderManager->Start();
    return 1;
}

// 0x00020780 CKGameLoop_ShutdownSubsystems_maybe (vt+0x98; Cleanup): the subsystems InitializeSubsystems made, released
// and destroyed. The game manager's slot (+0x4c) keeps its pointer (the original clears only the engine's).
void CKGameLoop::ShutdownSubsystems() {
    if (g_pScratchBuffer16k != nullptr) {
        Mem_FreeAligned16(g_pScratchBuffer16k);
        g_pScratchBuffer16k = nullptr;
    }
    if (m_gameManager != nullptr) {
        m_gameManager->ReleaseManager();  // vt+0xa8 (CKS08GameManager_vfA8 0x4ef6a8)
        ClassRegistry_DestroyObject(m_gameManager);
        Engine_SetGameManager(nullptr);
    }
    if (g_pEngine->m_level != nullptr) {
        ClassRegistry_DestroyObject(g_pEngine->m_level);
        Engine_SetLevel(nullptr);
    }
    if (g_pEngine->m_jobQueue != nullptr) {
        delete g_pEngine->m_jobQueue;  // vt+0x04
        Engine_SetJobQueue(nullptr);
    }
    if (m_loadingManager != nullptr) {
        ClassRegistry_DestroyObject(m_loadingManager);
        m_loadingManager = nullptr;
        Engine_SetLoadingManager_2(nullptr);
    }
    if (m_pSavingManager != nullptr) {
        ClassRegistry_DestroyObject(m_pSavingManager);
        m_pSavingManager = nullptr;
        Engine_SetSavingManager(nullptr);
    }
    if (m_serviceManager != nullptr) {
        m_serviceManager->DestroyModule();  // vt+0x98 0x23578
        ClassRegistry_DestroyObject(m_serviceManager);
        m_serviceManager = nullptr;
        Engine_SetServiceManager(nullptr);
    }
    if (m_hostFS != nullptr) {
        m_hostFS->CloseCachedFiles();  // vt+0x1c 0x51020
        if (m_hostFS != nullptr) delete m_hostFS;  // vt+0x04
        m_hostFS = nullptr;
    }
    if (m_soundManager != nullptr) {
        m_soundManager->DestroyModule();  // vt+0x98 0x1137b8
        ClassRegistry_DestroyObject(m_soundManager);
        m_soundManager = nullptr;
        Engine_SetSoundManager(nullptr);
    }
    if (m_graphic != nullptr) {
        m_graphic->DestroyModule();  // vt+0x98 0x59c88
        ClassRegistry_DestroyObject(m_graphic);
        m_renderer = nullptr;
        m_graphic = nullptr;
        Engine_SetGraphic(nullptr);
    }
    if (m_input != nullptr) {
        m_input->DestroyModule();  // vt+0x98 0x10c450
        ClassRegistry_DestroyObject(m_input);
        m_input = nullptr;
        Engine_SetInput(nullptr);
    }
    if (m_timeManager != nullptr) {
        m_timeManager->Destroy();  // 0x53998
        if (m_timeManager != nullptr) delete m_timeManager;  // vt+0x04
        m_timeManager = nullptr;
        Engine_SetTimeManager(nullptr);
    }
    if (m_errorTable != nullptr) {
        m_errorTable->DestroyObjects();  // vt+0x10 0x1dc70
        if (m_errorTable != nullptr) delete m_errorTable;  // vt+0x04
        m_errorTable = nullptr;
        Engine_SetErrorTable(nullptr);
    }
}

// 0x0001f658 CKGameLoop_vf38: reset every subsystem to its initial state.
void CKGameLoop::SetDefaultState(int32_t mode) {
    g_engineBusy = 1;
    m_gameManager->m_level->SetDefaultState(mode);
    m_gameManager->SetDefaultState(mode);
    m_serviceManager->SetDefaultState(mode);
    m_graphic->SetDefaultState(mode);
    m_input->SetDefaultState(mode);
    m_soundManager->SetDefaultState(mode);
    g_engineBusy = 0;
}

// 0x0001ffe0 CKGameLoop_ResetRuntime
void CKGameLoop::Start() {
    SetDefaultState(0);
    g_engineBusy = 1;
    m_pendingSubsystemReset = 1;
    m_timeManager->Start();
    m_gameManager->m_level->Start();
    m_gameManager->Start();
    m_serviceManager->Start();
    m_graphic->Start();
    m_input->Start();
    m_soundManager->Start();
    g_engineBusy = 0;
}

// 0x0001f3a0 CKGameLoop_vf64: the services', graphics', input's and sound's vt+0x64.
void CKGameLoop::Vf64() {
    g_engineBusy = 1;
    m_serviceManager->Vf64();
    m_graphic->Vf64();
    m_input->Vf64();
    m_soundManager->Vf64();
    g_engineBusy = 0;
}

// 0x0001fa28 CKGameLoop_StopAll_maybe: vt+0x64, the clock stopped, then the level, the game manager, the
// services, the graphics, the input and the sound stopped (GameLoop mode 9).
void CKGameLoop::Stop() {
    g_engineBusy = 1;
    Vf64();
    m_timeManager->Stop();
    m_gameManager->m_level->Stop();
    m_gameManager->Stop();
    m_serviceManager->Stop();
    m_graphic->Stop();
    m_input->Stop();
    m_soundManager->Stop();
    g_engineBusy = 0;
}

// 0x00021130 CKGameLoop_SectorUnload (Ghidra CKGameLoop_NotifySectorDeactivate) and 0x00020150
// CKGameLoop_PostSectorUnload (CKGameLoop_NotifySectorUnload_maybe): the level, the game manager (when there
// is one), the services, the graphics, the input and the sound told that `sector` goes. The engine is busy
// meanwhile unless the clock is stopped. The core manager's vt+0x54 (SectorUnload only) is empty.
void CKGameLoop::SectorUnload(int32_t sector) {
    if (m_timeManager->m_pTime->m_eCurrentState != IKTime::STOPPED) g_engineBusy = 1;
    g_pEngine->m_level->SectorUnload(sector);
    if (m_gameManager != nullptr) m_gameManager->SectorUnload(sector);
    m_serviceManager->SectorUnload(sector);
    m_graphic->SectorUnload(sector);
    m_input->SectorUnload(sector);
    m_soundManager->SectorUnload(sector);
    g_engineBusy = 0;
}

void CKGameLoop::PostSectorUnload(int32_t sector) {
    if (m_timeManager->m_pTime->m_eCurrentState != IKTime::STOPPED) g_engineBusy = 1;
    g_pEngine->m_level->PostSectorUnload(sector);
    if (m_gameManager != nullptr) m_gameManager->PostSectorUnload(sector);
    m_serviceManager->PostSectorUnload(sector);
    m_graphic->PostSectorUnload(sector);
    m_input->PostSectorUnload(sector);
    m_soundManager->PostSectorUnload(sector);
    g_engineBusy = 0;
}

// 0x0001f7b0 CKGameLoop_PreSectorLoaded (Ghidra CKGameLoop_NotifySectorLoaded_maybe) and 0x000202d8
// CKGameLoop_SectorLoaded (Ghidra CKGameLoop_NotifySectorActivate): the level, the game manager (when there is
// one), the services, the graphics, the input and the sound told that `sector` is there, in the order of the
// unload. The engine is busy meanwhile unless the clock is stopped. SectorLoaded first calls the core manager's
// vt+0x50 (CKCoreManager_vf50 0x1c558, a bare return).
void CKGameLoop::PreSectorLoaded(int32_t sector) {
    if (m_timeManager->m_pTime->m_eCurrentState != IKTime::STOPPED) g_engineBusy = 1;
    g_pEngine->m_level->PreSectorLoaded(sector);
    if (m_gameManager != nullptr) m_gameManager->PreSectorLoaded(sector);
    m_serviceManager->PreSectorLoaded(sector);
    m_graphic->PreSectorLoaded(sector);
    m_input->PreSectorLoaded(sector);
    m_soundManager->PreSectorLoaded(sector);
    g_engineBusy = 0;
}

void CKGameLoop::SectorLoaded(int32_t sector) {
    if (m_timeManager->m_pTime->m_eCurrentState != IKTime::STOPPED) g_engineBusy = 1;
    g_pEngine->m_level->SectorLoaded(sector);
    if (m_gameManager != nullptr) m_gameManager->SectorLoaded(sector);
    m_serviceManager->SectorLoaded(sector);
    m_graphic->SectorLoaded(sector);
    m_input->SectorLoaded(sector);
    m_soundManager->SectorLoaded(sector);
    g_engineBusy = 0;
}

// 0x0001fcd8 CKGameLoop_Pause
void CKGameLoop::Pause() {
    g_engineBusy = 1;
    m_timeManager->Pause();
    m_gameManager->m_level->Pause();
    m_gameManager->Pause();
    m_serviceManager->Pause();
    m_graphic->Pause();
    m_input->Pause();
    m_soundManager->Pause();
    g_engineBusy = 0;
}

// 0x0001fb90 CKGameLoop_Resume
void CKGameLoop::Resume() {
    g_engineBusy = 1;
    m_timeManager->Resume();
    m_gameManager->m_level->Resume();
    m_gameManager->Resume();
    m_serviceManager->Resume();
    m_graphic->Resume();
    m_input->Resume();
    m_soundManager->Resume();
    g_engineBusy = 0;
}

// 0x0001e7f8 CKGameLoop_SetGameManager
void CKGameLoop::SetGameManager(CDefaultGameManager* manager) {
    m_gameManager = manager;
    Engine_SetGameManager(manager);
}

// 0x0001f938 CKGameLoop_RequestSectorLoad_maybe
void CKGameLoop::RequestSectorLoad(int32_t sector) {
    if (sector != -2) {
        m_requestedSector = sector;
        return;
    }
    m_requestedSector = g_pEngine->m_level->m_currentSector;
}

// 0x0001e828 CKGameLoop_RequestExit_maybe
void CKGameLoop::RequestExit() {
    m_exitRequested = 1;
    RwaSetExitFlag(1);
}

// 0x00020ff8 CKGameLoop_SetAppActive_maybe: pauses the clock, videos and sound while the application is
// inactive, and restores them.
void CKGameLoop::SetAppActive(uint8_t active) {
    if (m_appActive == active) return;
    if (active == 0) {
        m_appActive = 0;
        if (m_timeManager->m_pTime->m_eCurrentState == IKTime::RUNNING) {
            m_clockPausedByApp = 1;
            m_timeManager->Pause();
            CVideoManager_PauseAllVideos(g_pEngine->m_videoManager);
            s_savedMasterVolume = SoundOutput_GetMasterVolume(g_pEngine->m_soundManager);
            SoundOutput_SetMasterVolume(kMutedVolume, g_pEngine->m_soundManager);
            return;
        }
        m_clockPausedByApp = 0;
    } else {
        m_appActive = 1;
        if (m_clockPausedByApp != 0) {
            m_timeManager->Resume();
            CVideoManager_ResumeAllVideos(g_pEngine->m_videoManager);
            SoundOutput_SetMasterVolume(s_savedMasterVolume, g_pEngine->m_soundManager);
        }
    }
}

// 0x0001e650 CKGameLoop_ShutdownAndExit_maybe: once an exit was requested, waits for save data, stops
// video and sound, aborts and joins the worker threads, then exits the process.
void CKGameLoop::ShutdownAndExit() {
    if (m_exitRequested == 0) return;
    // PSGL_glFinish: nothing is queued on the GPU in this port at this point.
    bool busy;
    do {
        busy = g_pEngine->m_gameManager->IsSaveDataBusy();
        Thread_SleepMs(1);
    } while (busy);
    ShaderUniforms_ReleaseBuiltinRecords();
    g_pEngine->m_videoManager->StopAllVideos();
    g_pEngine->m_videoManager->ShutdownVideoSystem();
    g_pEngine->m_soundManager->ShutdownAudio();
    m_loadQueue.Abort();
    m_memcardQueue.Abort();
    g_pShaderManager->m_requestQueue.Abort();       // 0x1011f0 (shader manager +0x8508)
    KHostFS_GetInstance()->m_requestQueue.Abort();  // 0x51990, 0x4f360 (host file system +0x20)
    m_shutdownReady = 1;
    ShutdownParticleUpdateScheduler(g_pEngine->m_particleScheduler);
    m_loadQueue.JoinThreads();
    m_memcardQueue.JoinThreads();
    g_pShaderManager->m_requestQueue.JoinThreads();       // 0x1011b0
    KHostFS_GetInstance()->m_requestQueue.JoinThreads();  // 0x4f320
    dotd::trace::Boot("exit(0)");  // trace only (not in the original)
    std::exit(0);
}

// 0x0001e890 UpdateGame
void UpdateGame(CKGameLoop* gameLoop) {
    IKTime* frameClock = gameLoop->m_timeManager->m_pTime;
    gameLoop->m_gameManager->Update(frameClock);
    if (gameLoop->m_pendingSubsystemReset != 0) {
        gameLoop->m_graphic->UpdateSceneWorldMatrices();
        gameLoop->m_serviceManager->UpdateInitialize();
        gameLoop->m_graphic->UpdateInitialize();
        gameLoop->m_input->UpdateInitialize();
        gameLoop->m_soundManager->UpdateInitialize();
        gameLoop->m_gameManager->OnLevelStart();
        gameLoop->m_pendingSubsystemReset = 0;
    }
    gameLoop->m_serviceManager->Update(frameClock);
}

// 0x0001e340 CKGameLoop_IsActiveModeWithGmVfC0_maybe (1 << mode as a 64-bit shift; modes above 10 answer 1).
uint8_t CKGameLoop::IsActiveModeWithGmVfC0() const {
    const uint32_t mode = m_mode;
    if (mode > 10) return 1;
    const uint64_t bit = static_cast<uint64_t>(1) << mode;
    if ((bit & 0x403) != 0) return 0;
    if ((bit & 0x3fc) != 0) return g_pEngine->m_gameManager->VfC0() != 0 ? 1 : 0;  // vt+0xc0
    return 1;
}

// 0x00021848 GameLoop (ported from the assembly).
uint32_t CKGameLoop::RunFrame() {
    JobQueue* jobQueue = g_pEngine->m_jobQueue;
    IKTime* frameClock = m_timeManager->m_pTime;
    jobQueue->ProcessCallbacks();
    const uint8_t oldInhibitJob = m_inhibitJobMessage;
    const uint8_t oldInhibitMessageBox = m_inhibitMessageBox;
    MessageBox_ClearJobMessageEntries();
    if (m_mode != kModeBoot && jobQueue->HasPending()) {
        MessageBox_PushJobMessageEntry(kJobMessageAlpha, jobQueue->PeekId());
    }

    // Inhibit flags. The original computes "count != 0" as ((|count| - 1) >> 31) ^ 1.
    m_inhibitJobMessage = MessageBox_GetJobMessageCount() != 0 ? 1 : 0;
    m_inhibitMessageBox = MessageBox_GetQueuedCount() != 0 ? 1 : 0;
    if (m_mode != kModeBoot && g_systemMenuOpen != 0) m_inhibitJobMessage = 1;

    uint8_t inhibitMessageBox = m_inhibitMessageBox;
    uint8_t inhibitJob = m_inhibitJobMessage;
    if (inhibitMessageBox != 0 && inhibitJob == 0) {
        MessageBox_ProcessQueue();
        inhibitJob = m_inhibitJobMessage;
        inhibitMessageBox = m_inhibitMessageBox;
    }
    if (oldInhibitJob != inhibitJob) {
        if (inhibitJob != 0) ++m_inhibitCount;
        else --m_inhibitCount;
    }
    if (oldInhibitMessageBox != inhibitMessageBox) {
        if (inhibitMessageBox != 0) ++m_inhibitCount;
        else --m_inhibitCount;
    }
    jobQueue->PurgeWithoutCallback();

    if (m_inhibitMessageBox == 0 && m_inhibitJobMessage == 0) {
        if ((m_mode == kModeLevel || m_mode == kModeInGame) && m_pendingSubsystemReset == 0) {
            m_gameManager->HandlePauseInput(m_timeManager->m_pTime);
        }
    }

    // Stop reason (+0x0c), only written when it changes.
    const uint8_t mode = m_mode;
    if (mode != kModeBoot && mode != kModeLevelExit) {
        if (m_inhibitCount == 0) {
            if (m_stopReason != 0) m_stopReason = 0;
        } else if (m_stopReason != 1) {
            m_stopReason = 1;
        }
    }
    if (mode != kModeBoot) {
        if (m_gameManager->Vf108() != 0 && m_stopReason != 3) m_stopReason = 3;
        if (m_gameManager->m_unk290 != -1 && m_stopReason != 4) m_stopReason = 4;
    }
    if (m_exitAllowed != 0 && m_exitRequested != 0 && m_stopReason != 2) m_stopReason = 2;

    // Mode state machine: tick the current mode; on a change, leave the old one and enter the new one.
    CKGameLoop* owner = m_modeOwner;
    const uint8_t current = m_mode;
    if (current != kModeNone) {
        const uint8_t next = (owner->*m_modeTable[current])(frameClock, kPhaseTick, current);
        const uint8_t old = m_mode;
        if (next != old) {
            if (old != kModeNone) (owner->*m_modeTable[old])(frameClock, kPhaseLeave, next);
            m_mode = next;
            dotd::trace::ModeChange(old, next);  // trace only (not in the original)
            if (next != kModeNone) (owner->*m_modeTable[next])(frameClock, kPhaseEnter, old);
        }
    }

    g_engineBusy = 1;
    m_unk5c = 0;
    m_hostFS->PollDevice();
    m_timeManager->Update(0);
    if (m_mode != kModeBoot) {
        m_input->PreUpdate(frameClock);
        m_soundManager->PreUpdate(frameClock);
        m_graphic->PreUpdate(frameClock);
    }

    if (m_inhibitMessageBox == 0 && m_inhibitJobMessage == 0 && (m_mode == kModeLevel || m_mode == kModeInGame)) {
        UpdateGame(this);
    } else if (g_systemMenuOpen == 0) {
        Sys_UsleepMs(5);
    }
    if (m_mode != kModeBoot) {
        m_soundManager->Update(frameClock);
        m_graphic->Update(frameClock);
    }

    // Which renderer: the full frame in modes 2, 5 and 8, otherwise the fallback (clear, 2D, video).
    bool renderGame = false;
    if (m_pendingSubsystemReset == 0 && (m_inhibitJobMessage == 0 || g_systemMenuOpen != 0)) {
        bool check = true;
        if (m_stopReason == 4 && (m_mode == kModeLoading || m_mode == kModeInGame || m_mode == kModePauseMenu)) {
            check = false;
        }
        if (check && g_bootLocLoaded != 0 && m_gameManager->m_requestedLevel != -1 &&
            g_pEngine->m_gameManager->m_unk294 != 0 &&
            MessageBox_GetJobMessageCount() == 0) {
            check = false;  // loading screen while a level is requested
        }
        if (check && m_mode <= 8 && ((1u << m_mode) & 0x124u) != 0) renderGame = true;
    }
    if (renderGame) m_renderer->RenderGameFrame(frameClock);
    else m_renderer->RenderFallbackFrame(frameClock);

    if (m_mode != kModeBoot) {
        m_soundManager->PostUpdate(frameClock);
        m_graphic->PostUpdate(frameClock);
    }
    g_engineBusy = 0;
    const bool gameplay =
        m_inhibitMessageBox == 0 && m_inhibitJobMessage == 0 && (m_mode == kModeLevel || m_mode == kModeInGame);
    Sysutil_PollCallbacks(gameplay ? 0 : 1);
    ShutdownAndExit();
    return m_mode != kModeQuit ? 1u : 0u;
}

// ---- mode handlers -----------------------------------------------------------------------------

// 0x00022520 CKGameLoop_Mode0_Boot: pad init, GAME.KP3, the default and system-language loc files
// (then the loading video starts), then the boot data (RWS pre-open, save data, shader cache).
uint8_t CKGameLoop::Mode0_Boot(IKTime* /*frameClock*/, int32_t phase, uint8_t /*otherMode*/) {
    if (phase == kPhaseEnter) return kModeBoot;
    if (phase != kPhaseTick) return kModeBoot;
    if (g_pEngine->m_gameLoop->m_exitRequested != 0) {
        m_quitEntered = 1;
        return kModeQuit;
    }
    if (g_mode0Step == 0) {
        Pad_Init(m_input);
        g_mode0Step = 1;
    }
    if (g_mode0Step == 1) {
        if (m_levelRequest.m_posted == 0) {
            m_levelRequest.Post(GameLevelLoadRequest::kGameFile, -1);
        } else if (m_levelRequest.CheckDone() != 0) {
            BootLoad_SetGameLoopActive(m_gameManager);
            g_mode0Step = 2;
        }
    }
    if (g_mode0Step == 2) {
        if (m_locRequest.m_posted == 0) {
            m_locRequest.Post(LocLoadRequest::kDefaultAndSystemLanguage);
        } else if (m_locRequest.CheckDone() != 0) {
            m_gameManager->RecacheLocStrings();
            KStub_Nop_1038c8(m_input);
            g_bootLocLoaded = 1;
            PlayLevelLoadingVideo(1);  // 0x0001ea38 (inlined)
            g_mode0Step = 3;
        }
    }
    if (g_mode0Step != 3) return kModeBoot;
    if (m_bootRequest.m_posted == 0) {
        m_bootRequest.Post();
        return kModeBoot;
    }
    return static_cast<uint8_t>(m_bootRequest.CheckDone());  // 1 = kModeInit once finished
}

// 0x000221e8 CKGameLoop_Mode1_Init: load the requested level and its sector and loc files.
uint8_t CKGameLoop::Mode1_Init(IKTime* /*frameClock*/, int32_t phase, uint8_t otherMode) {
    if (phase == kPhaseEnter) {
        s_mode1FromBoot = otherMode == kModeBoot ? 1 : 0;
        m_gameManager->UnloadCurrentLevel();
        PlayLevelLoadingVideo(s_mode1FromBoot);  // 0x0001ea38 (inlined)
        g_mode1Step = 0;
        return kModeInit;
    }
    if (phase != kPhaseTick) return kModeInit;
    if (g_pEngine->m_gameLoop->m_exitRequested != 0) {
        m_quitEntered = 1;
        return kModeQuit;
    }

    bool sectorStep = false;
    if (g_mode1Step == 0) {
        if (m_levelRequest.m_posted == 0) {
            m_levelRequest.Post(GameLevelLoadRequest::kLevel, m_gameManager->m_requestedLevel);
        } else if (m_levelRequest.CheckDone() != 0) {
            m_gameManager->CommitRequestedLevel();
            g_mode1Step = 1;
            sectorStep = true;
        }
    }
    if (!sectorStep && g_mode1Step == 1) sectorStep = true;

    bool locStep = false;
    if (sectorStep) {
        int32_t sector = m_gameManager->m_requestedSector;
        if (sector == -2) sector = m_gameManager->m_level->GetDefaultSector();
        if (sector == 0 || sector == -2) {
            g_mode1Step = 2;
            locStep = true;
        } else {
            CKLevel* level = g_pEngine->m_level;
            if (level->m_requestedSector == sector) {
                level->UpdateSectorStreaming();
                if (g_pEngine->m_level->m_currentSector == sector) {
                    m_gameManager->ClearRequestedSector();
                    g_mode1Step = 2;
                    locStep = true;
                }
            } else {
                level->SwitchToSector(sector, 0);
            }
        }
    }

    if (!locStep) {
        if (g_mode1Step != 2) {
            if (g_mode1Step == 3) {
                IKGameManager_RestoreDefaultOptionsThenVfAC_IfFlag(m_gameManager, s_mode1FromBoot);
                return kModeStartLevel;
            }
            return kModeInit;
        }
    }

    if (m_locRequest.m_posted == 0) {
        m_locRequest.Post(LocLoadRequest::kLevel);
    } else {
        if (m_inhibitJobMessage != 0 || m_locRequest.CheckDone() == 0) return kModeInit;
        m_gameManager->ReloadLocalizedData();
        // PLATFORM (perf, not in the original): the level is in and its loading video still up: the shader programs
        // it used in earlier runs are built here instead of at their first draw (CShaderManagerPSGL.h).
        ShaderManagerPSGL_PrewarmLevelPrograms(static_cast<CDefaultGameManager*>(m_gameManager)->m_currentLevel);
        g_pEngine->m_videoManager->StopLoadingVideo();
        g_mode1Step = 3;
    }
    return kModeInit;
}

// 0x0001e4a8 CKGameLoop_Mode2_Resume_maybe
uint8_t CKGameLoop::Mode2_Resume(IKTime* /*frameClock*/, int32_t phase, uint8_t /*otherMode*/) {
    if (phase != kPhaseEnter && phase == kPhaseTick) {
        m_gameManager->UpdateSaveDataRequests();
        if (m_stopReason != 3) return kModeInGame;
    }
    return kModeResume;
}

// 0x00020b98 CKGameLoop_Mode3_PauseMenu_maybe: the language switch (Ghidra's name is an old guess; mode 8
// enters it while the game manager requests a language, +0x290). Every frame the "loading" job message
// (0xcb) and the loc request kind 3 (Engine_ChangeLanguage on the load worker); once it is done, two more
// frames, then the 2D manager's TRC strings recached, the request cleared and back to mode 8.
uint8_t CKGameLoop::Mode3_PauseMenu(IKTime* /*frameClock*/, int32_t phase, uint8_t /*otherMode*/) {
    if (phase == kPhaseEnter) {
        s_languageFrames = 0;
        return kModePauseMenu;
    }
    if (phase != kPhaseTick) return kModePauseMenu;
    if (s_languageFrames == 0) {
        g_pEngine->m_jobQueue->PostAndWait(0xcb, 2, nullptr, nullptr, nullptr);
        if (m_locRequest.m_posted == 0) {
            m_locRequest.Post(LocLoadRequest::kChangeLanguage);
        } else if (m_locRequest.CheckDone() != 0) {
            s_languageFrames = 2;
        }
        return kModePauseMenu;
    }
    --s_languageFrames;
    if (s_languageFrames == 0) {
        g_pEngine->m_gameManager->RecacheLocStringsAfterReload();
        return kModeInGame;
    }
    return kModePauseMenu;
}

// 0x0001e538 CKGameLoop_Mode4_StartLevel_maybe: enter resets the runtime; the next tick goes to mode 5.
uint8_t CKGameLoop::Mode4_StartLevel(IKTime* /*frameClock*/, int32_t phase, uint8_t /*otherMode*/) {
    if (phase != kPhaseEnter) {
        // ((sign - (sign ^ phase)) >> 31) + 5: 5 for the tick, 4 for any other phase.
        return phase == kPhaseTick ? kModeLevel : kModeStartLevel;
    }
    Start();
    return kModeStartLevel;
}

// 0x000212f0 CKGameLoop_Mode5_LevelStart: the front end and gameplay run in this mode.
uint8_t CKGameLoop::Mode5_LevelStart(IKTime* /*frameClock*/, int32_t phase, uint8_t /*otherMode*/) {
    if (phase == kPhaseEnter || phase != kPhaseTick) return kModeLevel;
    const int32_t reason = m_stopReason;
    if (reason == 2) return kModeLevelExit;
    if (reason != 3 && reason != 4) {
        if (m_requestedSector != -2) return kModeLevelLoad;
        if (m_gameManager->m_requestedLevel != -1) return kModeLevelExit;
        if (reason != 1) return kModeLevel;
    }
    return kModeLoading;
}

// 0x00020498 CKGameLoop_Mode6_LevelLoad: a sector change during play (m_requestedSector). Enter asks the
// level for the sector (or, when it is current already, restarts at once); the ticks stream it in; once it
// is current, everything restarts (vt+0x54) and the mode waits for the file system, the sound and the
// level to settle (the "loading" job message after 10 s), then goes back to mode 5. Leave clears the request.
uint8_t CKGameLoop::Mode6_LevelLoad(IKTime* /*frameClock*/, int32_t phase, uint8_t /*otherMode*/) {
    if (phase == kPhaseEnter) {
        if (g_pEngine->m_level->m_currentSector == m_requestedSector) {
            Restart();  // vt+0x54
            s_mode6Step = 1;
            s_waitTime = 0.0f;
            return kModeLevelLoad;
        }
        g_pEngine->m_level->SwitchToSector(m_requestedSector, 0);
        s_mode6Step = 0;
        return kModeLevelLoad;
    }
    if (phase != kPhaseTick) {
        if (phase == kPhaseLeave) m_requestedSector = -2;
        return kModeLevelLoad;
    }
    if (s_mode6Step == 0) {
        g_pEngine->m_level->UpdateSectorStreaming();
        if (m_requestedSector != g_pEngine->m_level->m_currentSector) return kModeLevelLoad;
        Restart();  // vt+0x54
        s_waitTime = 0.0f;
        s_mode6Step = 1;
    } else if (s_mode6Step != 1) {
        return kModeLevelLoad;
    }
    if (m_hostFS->IsReadComplete() != 0 && m_soundManager->Vf58() != 0 && g_pEngine->m_level->Vf58() != 0) {
        return kModeLevel;
    }
    if (kLoadingMessageDelay <= s_waitTime) {
        g_pEngine->m_jobQueue->PostAndWait(0xcb, 2, nullptr, nullptr, nullptr);
        return kModeLevelLoad;
    }
    s_waitTime = s_waitTime + g_pEngine->m_timeManager->m_pTime->m_afDeltaTime[IKTime::SYSTEM_TIME];
    return kModeLevelLoad;
}

// 0x0001f570 CKGameLoop_BroadcastPreReinit_maybe (vt+0x5c): the services', graphics', input's and sound's
// vt+0x5c.
void CKGameLoop::PreRestart() {
    g_engineBusy = 1;
    m_serviceManager->PreRestart();
    m_graphic->PreRestart();
    m_input->PreRestart();
    m_soundManager->PreRestart();
    g_engineBusy = 0;
}

// 0x0001f488 CKGameLoop_BroadcastPostReinit_maybe (vt+0x60): the same with vt+0x60.
void CKGameLoop::Vf60() {
    g_engineBusy = 1;
    m_serviceManager->Vf60();
    m_graphic->Vf60();
    m_input->Vf60();
    m_soundManager->Vf60();
    g_engineBusy = 0;
}

// 0x0001fe20 CKGameLoop_Restart (Ghidra CKGameLoop_ReinitRuntime): everything starts over without a new
// level: the default state 1, the engine busy while the subsystems learn it (vt+0x5c before, vt+0x60 after),
// the clock restarted, then the level, the game manager, the services, the graphics, the input and the
// sound restarted (vt+0x54). Only Mode6_LevelLoad (a sector change in play) calls it.
void CKGameLoop::Restart() {
    SetDefaultState(1);  // vt+0x38
    g_engineBusy = 1;
    PreRestart();  // vt+0x5c
    m_pendingSubsystemReset = 1;
    m_timeManager->Restart();
    m_gameManager->m_level->Restart();
    m_gameManager->Restart();
    m_serviceManager->Restart();
    m_graphic->Restart();
    m_input->Restart();
    m_soundManager->Restart();
    Vf60();  // vt+0x60
    g_engineBusy = 0;
}

// 0x00021678 CKGameLoop_Mode7_Loading: the loop paused; once the files, the sound streams and the level
// are settled, mode 8. After 10 s of real time the "loading" job message (0xcb) is shown.
uint8_t CKGameLoop::Mode7_Loading(IKTime* /*frameClock*/, int32_t phase, uint8_t /*otherMode*/) {
    if (phase == kPhaseEnter) {
        Pause();  // vt+0x70
        s_waitTime = 0.0f;
        return kModeLoading;
    }
    if (phase != kPhaseTick) return kModeLoading;
    if (m_hostFS->IsIdle() != 0 && m_soundManager->Vf74() != 0 && g_pEngine->m_level->Vf74() != 0) return kModeInGame;
    if (!(s_waitTime >= kLoadingMessageDelay)) {  // fcmpu + cror gt|eq: a NaN wait keeps adding
        s_waitTime = s_waitTime + g_pEngine->m_timeManager->m_pTime->m_afDeltaTime[IKTime::SYSTEM_TIME];
        return kModeLoading;
    }
    g_pEngine->m_jobQueue->PostAndWait(0xcb, 2, nullptr, nullptr, nullptr);
    return kModeLoading;
}

// 0x0001f960 CKGameLoop_Mode8_InGame
uint8_t CKGameLoop::Mode8_InGame(IKTime* /*frameClock*/, int32_t phase, uint8_t /*otherMode*/) {
    if (phase != kPhaseEnter) {
        if (phase == kPhaseTick) {
            const int32_t reason = m_stopReason;
            if (reason == 2) return kModeLevelExit;
            if (reason == 3) return kModeResume;
            if (reason == 4) return kModePauseMenu;
            if (reason == 0) return kModeLevel;
        } else if (phase == kPhaseLeave && m_stopReason != 3 && m_stopReason != 4) {
            Resume();
            return kModeInGame;
        }
    }
    return kModeInGame;
}

// 0x000213c8 CKGameLoop_Mode9_LevelExit: the level told to stop; once it agrees (vt+0x6c), everything
// stopped (vt+0x68); then, once the file system and the sound are settled: mode 10 for an exit, mode 1 for
// a requested level. Without either the mode waits, showing the "loading" job message after 10 s.
uint8_t CKGameLoop::Mode9_LevelExit(IKTime* /*frameClock*/, int32_t phase, uint8_t /*otherMode*/) {
    if (phase == kPhaseEnter) {
        g_pEngine->m_level->Stop();  // vt+0x68
        s_levelExitStep = 0;
        return kModeLevelExit;
    }
    if (phase != kPhaseTick) return kModeLevelExit;
    if (g_pEngine->m_gameLoop->m_exitRequested == 0) {
        if (s_levelExitStep == 0) {
            if (g_pEngine->m_level->Vf6C() == 0) return kModeLevelExit;
            Stop();  // vt+0x68
            s_levelExitStep = 1;
            s_waitTime = 0.0f;
            return kModeLevelExit;
        }
    } else if (s_levelExitStep == 0) {
        m_quitEntered = 1;
        return kModeQuit;
    }
    if (s_levelExitStep != 1) return kModeLevelExit;
    if (m_hostFS->IsReadIdle() != 0 && m_soundManager->Vf6C() != 0) {
        if (m_stopReason == 2) return kModeQuit;
        if (m_gameManager->m_requestedLevel != -1) return kModeInit;
    }
    if (!(s_waitTime >= kLoadingMessageDelay)) {  // fcmpu + cror gt|eq: a NaN wait keeps adding
        s_waitTime = s_waitTime + g_pEngine->m_timeManager->m_pTime->m_afDeltaTime[IKTime::SYSTEM_TIME];
        return kModeLevelExit;
    }
    g_pEngine->m_jobQueue->PostAndWait(0xcb, 2, nullptr, nullptr, nullptr);
    return kModeLevelExit;
}

// 0x0001e5b8 CKGameLoop_Mode10_Quit
uint8_t CKGameLoop::Mode10_Quit(IKTime*, int32_t, uint8_t) { return kModeQuit; }

// ==== C2.8 save-menu ===========================================================================================
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/logic/ui/CLocManager.h"
#include "k2000/managers/CKGraphic.h"
#include "k2000/managers/CKInput.h"
#include "k2000/managers/CKServiceManager.h"
#include "k2000/managers/CKSoundManager.h"

// 0x00020ce0 CKGameLoop_vf24 (XXL2 RecursiveRegistration)
void CKGameLoop::RecursiveRegistration(int32_t type) {
    IKSerializable* last;
    int32_t lastType;
    if (type == 0) {
        g_pEngine->m_locManager->RecursiveRegistration(0);
        m_serviceManager->RecursiveRegistration(0);
        m_graphic->RecursiveRegistration(0);
        m_input->RecursiveRegistration(0);
        m_soundManager->RecursiveRegistration(0);
        last = m_gameManager;
        lastType = 0;
    } else if (type == 1) {
        g_pEngine->m_locManager->RecursiveRegistration(1);
        m_serviceManager->RecursiveRegistration(1);
        m_gameManager->RecursiveRegistration(1);
        m_input->RecursiveRegistration(1);
        m_soundManager->RecursiveRegistration(1);
        last = m_graphic;
        lastType = 1;
    } else {
        if (static_cast<uint32_t>(type - 4) > 3u) return;
        m_serviceManager->RecursiveRegistration(type);
        m_gameManager->RecursiveRegistration(type);
        m_input->RecursiveRegistration(type);
        return;
    }
    last->RecursiveRegistration(lastType);
}

// 0x0001e150 CKGameLoop_HasRequestedLevel_maybe
bool CKGameLoop::HasRequestedLevel() const { return m_gameManager->m_requestedLevel != -1; }

// 0x0001e178 CKGameLoop_GetGlobalUpdateInhibitByte_maybe
uint8_t CKGameLoop_GetGlobalUpdateInhibitByte() { return g_systemMenuOpen; }

// 0x0001ea38 PlayLevelLoadingVideo_maybe (Mode0_Boot and Mode1_Init have it inlined)
void PlayLevelLoadingVideo(int32_t bootVideo) {
    CVideoManager* video = g_pEngine->m_videoManager;
    if (video->IsLoadingVideoActive()) return;
    CDefaultGameManager* manager = g_pEngine->m_gameManager;
    const int32_t level = bootVideo == 0 ? manager->m_requestedLevel : -1;
    video->m_pLoadingVideo = manager->GetLoadingVideo(level);  // vt+0xd8
    video->PlayLoadingVideo();
}
