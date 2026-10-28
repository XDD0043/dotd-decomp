// Engine.cpp - reconstructed original translation unit 0x24bd0-0x25258 (GAME_TOC1, main_toc1), 51 functions, 50 live.
// Primary owner: Engine (not a registered class)
// Other owners: none (the five "ConstructBase" names in the generated list were setters; corrected 2026-10-15)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x24bd0  Engine_SetSrvCamera_maybe
//   [x] 0x24be0  Engine_SetInstance_maybe
//   [x] 0x24bf0  Engine_SetLoadingManager
//   [x] 0x24c00  Engine_SetSrvBeacon
//   [x] 0x24c10  Engine_SetAvoidanceService_maybe
//   [x] 0x24c20  Engine_SetSrvCinematic
//   [x] 0x24c30  Engine_SetSrvSekensor
//   [x] 0x24c40  Engine_SetShadowService_maybe
//   [x] 0x24c50  Engine_SetLevel
//   [x] 0x24c60  Engine_SetGameManager
//   [x] 0x24c70  Engine_SetLocManager
//   [x] 0x24c80  Engine_SetGraphic
//   [x] 0x24c90  Engine_SetMainSceneRoot_maybe
//   [x] 0x24ca0  Engine_SetSecondarySceneRoot_maybe
//   [x] 0x24cb0  Engine_SetDynamicSceneRoot
//   [x] 0x24cc0  Engine_SetInput
//   [x] 0x24cd0  Engine_SetSoundManager
//   [x] 0x24ce0  Engine_SetClassManager
//   [x] 0x24cf0  Engine_SetServiceManager
//   [x] 0x24d00  Engine_SetServiceLife
//   [x] 0x24d10  Engine_SetCoreManager
//   [x] 0x24d20  Engine_SetFileSystem
//   [x] 0x24d30  Engine_SetGameLoop
//   [x] 0x24d40  Engine_SetManager2d
//   [x] 0x24d50  Engine_SetTextureBank_maybe
//   [x] 0x24d60  Engine_SetAnimationManager_maybe
//   [x] 0x24d70  Engine_SetTimeManager_maybe
//   [x] 0x24d80  Engine_SetJobQueue_maybe
//   [x] 0x24d90  Engine_SetSavingManager
//   [x] 0x24da0  Engine_SetLoadingManager_2
//   [x] 0x24db0  Engine_SetSrvCollision
//   [x] 0x24dc0  Engine_SetSrvPhysics
//   [x] 0x24dd0  Engine_SetSrvPathFinding
//   [x] 0x24de0  Engine_SetProjectilesService
//   [x] 0x24df0  Engine_SetSrvFx
//   [x] 0x24e00  Engine_SetBonusService_maybe
//   [x] 0x24e10  Engine_SetSrvCounter
//   [x] 0x24e20  Engine_SetSrvTrigger
//   [x] 0x24e30  Engine_SetSrvDetect
//   [x] 0x24e40  Engine_SetFlashManager
//   [x] 0x24e50  Engine_SetSrvMusic
//   [x] 0x24e60  Engine_SetSrvInput
//   [x] 0x24e70  Engine_SetVideoManager
//   [x] 0x24e80  Engine_SetStaticStateBlock_maybe
//   [x] 0x24e90  Engine_SetErrorTable_maybe
//   [x] 0x24ea0  Engine_SetSrvNetwork
//   [x] 0x24eb0  Engine_SetDynamicService_maybe
//   [x] 0x24ec0  Engine_SetParticleScheduler_maybe
//   [x] 0x24ed0  Engine_GetGlobalInstances
//   [x] 0x250c8  Engine_Construct
//   [ ] 0x25190  Engine_Construct_2  [dead]

#include "k2000/misc/Engine.h"

#include "k2000/logic/CKCoreManager.h"
#include "k2000/managers/CKGraphic.h"
#include "k2000/managers/CKInput.h"
#include "k2000/managers/CKServiceManager.h"
#include "k2000/managers/CKSoundManager.h"
#include "k2000/misc/CKGameLoop.h"

// 0x00c50f20
GameEngineContext* g_pEngine = nullptr;

// 0x00024bd0 Engine_SetSrvCamera_maybe
void Engine_SetSrvCamera(IKSerializable* service) { g_pEngine->m_srvCamera = service; }

// 0x00024be0 Engine_SetInstance_maybe
void Engine_SetInstance(GameEngineContext* engine) { g_pEngine = engine; }

// 0x00024bf0 Engine_SetLoadingManager
void Engine_SetLoadingManager(CKLoadingManager* manager) { g_pEngine->m_loadingManager = manager; }

// 0x00024c00 Engine_SetSrvBeacon
void Engine_SetSrvBeacon(IKSerializable* service) { g_pEngine->m_srvBeacon = service; }

// 0x00024c10 Engine_SetAvoidanceService_maybe
void Engine_SetAvoidanceService(IKSerializable* service) { g_pEngine->m_srvAvoidance = service; }

// 0x00024c20 Engine_SetSrvCinematic
void Engine_SetSrvCinematic(IKSerializable* service) { g_pEngine->m_srvCinematic = service; }

// 0x00024c30 Engine_SetSrvSekensor
void Engine_SetSrvSekensor(IKSerializable* service) { g_pEngine->m_srvSekensor = service; }

// 0x00024c40 Engine_SetShadowService_maybe
void Engine_SetShadowService(IKSerializable* service) { g_pEngine->m_srvShadow = service; }

// 0x00024c50 Engine_SetLevel
void Engine_SetLevel(CKLevel* level) { g_pEngine->m_level = level; }

// 0x00024c60 Engine_SetGameManager
void Engine_SetGameManager(CDefaultGameManager* manager) { g_pEngine->m_gameManager = manager; }

// 0x00024c70 Engine_SetLocManager
void Engine_SetLocManager(CLocManager* manager) { g_pEngine->m_locManager = manager; }

// 0x00024c80 Engine_SetGraphic
void Engine_SetGraphic(CKGraphic* graphic) { g_pEngine->m_graphic = graphic; }

// 0x00024c90 Engine_SetMainSceneRoot_maybe
void Engine_SetMainSceneRoot(IKSerializable* root) { g_pEngine->m_mainSceneRoot = root; }

// 0x00024ca0 Engine_SetSecondarySceneRoot_maybe
void Engine_SetSecondarySceneRoot(IKSerializable* root) { g_pEngine->m_secondarySceneRoot = root; }

// 0x00024cb0 Engine_SetDynamicSceneRoot
void Engine_SetDynamicSceneRoot(IKSerializable* root) { g_pEngine->m_dynamicSceneRoot = root; }

// 0x00024cc0 Engine_SetInput
void Engine_SetInput(CKInput* input) { g_pEngine->m_input = input; }

// 0x00024cd0 Engine_SetSoundManager
void Engine_SetSoundManager(CKSoundManager* manager) { g_pEngine->m_soundManager = manager; }

// 0x00024ce0 Engine_SetClassManager
void Engine_SetClassManager(ClassManager* manager) { g_pEngine->m_classManager = manager; }

// 0x00024cf0 Engine_SetServiceManager
void Engine_SetServiceManager(CKServiceManager* manager) { g_pEngine->m_serviceManager = manager; }

// 0x00024d00 Engine_SetServiceLife
void Engine_SetServiceLife(IKSerializable* service) { g_pEngine->m_lifeService = service; }

// 0x00024d10 Engine_SetCoreManager
void Engine_SetCoreManager(CKCoreManager* manager) { g_pEngine->m_coreManager = manager; }

// 0x00024d20 Engine_SetFileSystem
void Engine_SetFileSystem(KFileSystem* fileSystem) { g_pEngine->m_fileSystem = fileSystem; }

// 0x00024d30 Engine_SetGameLoop
void Engine_SetGameLoop(CKGameLoop* gameLoop) { g_pEngine->m_gameLoop = gameLoop; }

// 0x00024d40 Engine_SetManager2d
void Engine_SetManager2d(CManager2d* manager) { g_pEngine->m_manager2d = manager; }

// 0x00024d50 Engine_SetTextureBank_maybe
void Engine_SetTextureBank(TextureBank* bank) { g_pEngine->m_textureBank = bank; }

// 0x00024d60 Engine_SetAnimationManager_maybe
void Engine_SetAnimationManager(CAnimationManager* m) { g_pEngine->m_animationManager = m; }

// 0x00024d70 Engine_SetTimeManager_maybe
void Engine_SetTimeManager(CTimeManager* manager) { g_pEngine->m_timeManager = manager; }

// 0x00024d80 Engine_SetJobQueue_maybe
void Engine_SetJobQueue(JobQueue* queue) { g_pEngine->m_jobQueue = queue; }

// 0x00024d90 Engine_SetSavingManager
void Engine_SetSavingManager(CKSavingManager* manager) { g_pEngine->m_pSavingManager = manager; }

// 0x00024da0 Engine_SetLoadingManager_2
void Engine_SetLoadingManager_2(CKLoadingManager* m) { g_pEngine->m_objectDatabase = m; }

// 0x00024db0 Engine_SetSrvCollision  (renamed in Ghidra 2026-10-15; was CKSrvCollision_ConstructBase_maybe)
void Engine_SetSrvCollision(IKSerializable* service) { g_pEngine->m_srvCollision = service; }

// 0x00024dc0 Engine_SetSrvPhysics
void Engine_SetSrvPhysics(IKSerializable* service) { g_pEngine->m_srvPhysics = service; }

// 0x00024dd0 Engine_SetSrvPathFinding
void Engine_SetSrvPathFinding(IKSerializable* service) { g_pEngine->m_srvPathFinding = service; }

// 0x00024de0 Engine_SetProjectilesService
void Engine_SetProjectilesService(IKSerializable* service) { g_pEngine->m_srvProjectiles = service; }

// 0x00024df0 Engine_SetSrvFx  (renamed in Ghidra 2026-10-15; was CKSrvFx_ConstructBase_maybe)
void Engine_SetSrvFx(IKSerializable* service) { g_pEngine->m_srvFx = service; }

// 0x00024e00 Engine_SetBonusService_maybe
void Engine_SetBonusService(IKSerializable* service) { g_pEngine->m_srvBonus = service; }

// 0x00024e10 Engine_SetSrvCounter  (renamed in Ghidra 2026-10-15; was CKSrvCounter_ConstructBase_maybe)
void Engine_SetSrvCounter(IKSerializable* service) { g_pEngine->m_srvCounter = service; }

// 0x00024e20 Engine_SetSrvTrigger
void Engine_SetSrvTrigger(IKSerializable* service) { g_pEngine->m_srvTrigger = service; }

// 0x00024e30 Engine_SetSrvDetect
void Engine_SetSrvDetect(IKSerializable* service) { g_pEngine->m_srvDetect = service; }

// 0x00024e40 Engine_SetFlashManager
void Engine_SetFlashManager(CKFlashManager* manager) { g_pEngine->m_flashManager = manager; }

// 0x00024e50 Engine_SetSrvMusic
void Engine_SetSrvMusic(IKSerializable* service) { g_pEngine->m_srvMusic = service; }

// 0x00024e60 Engine_SetSrvInput  (renamed in Ghidra 2026-10-15; was CKSrvInput_ConstructBase_maybe)
void Engine_SetSrvInput(IKSerializable* service) { g_pEngine->m_srvInput = service; }

// 0x00024e70 Engine_SetVideoManager
void Engine_SetVideoManager(CVideoManager* manager) { g_pEngine->m_videoManager = manager; }

// 0x00024e80 Engine_SetStaticStateBlock_maybe
void Engine_SetStaticStateBlock(AppConfig* config) { g_pEngine->m_appConfig = config; }

// 0x00024e90 Engine_SetErrorTable_maybe
void Engine_SetErrorTable(CKErrorTable* table) { g_pEngine->m_errorTable = table; }

// 0x00024ea0 Engine_SetSrvNetwork  (renamed in Ghidra 2026-10-15; was PS3_CKSrvNetwork_ConstructBase_maybe)
void Engine_SetSrvNetwork(IKSerializable* service) { g_pEngine->m_srvNetwork = service; }

// 0x00024eb0 Engine_SetDynamicService_maybe
void Engine_SetDynamicService(IKSerializable* service) { g_pEngine->m_srvDynamic = service; }

// 0x00024ec0 Engine_SetParticleScheduler_maybe
void Engine_SetParticleScheduler(ParticleUpdateScheduler* scheduler) { g_pEngine->m_particleScheduler = scheduler; }

// 0x00024ed0 Engine_GetGlobalInstances
uint8_t Engine_GetGlobalInstances(GameEngineContext* engine, int32_t category, uint32_t id, uint32_t count, void* out) {
    IKSerializable** slot = static_cast<IKSerializable**>(out);
    switch (category) {
    case kCategoryManager: {
        IKSerializable* manager = nullptr;
        if (id == 1) manager = engine->m_serviceManager;
        else if (id == 2) manager = engine->m_graphic;
        else if (id == 3) manager = engine->m_soundManager;
        else if (id == 4) manager = engine->m_input;
        else return engine->m_gameLoop->FindNonRecreableInstances(kCategoryManager, id, count, out);
        *slot = manager;
        return *slot != nullptr ? 1 : 0;  // (x != 0) computed with sign arithmetic
    }
    case kCategoryService:
        *slot = CKServiceManager_GetServiceByClassId(engine->m_serviceManager, id);
        return *slot != nullptr ? 1 : 0;
    case kCategoryHook:
    case kCategoryGroup:
    case kCategoryLogic:
        return engine->m_coreManager->FindNonRecreableInstances(category, id, count, out);
    case 10:
    case kCategoryGraphical:
        return engine->m_graphic->FindNonRecreableInstances(category, id, count, out);
    case kCategoryNode:
        if (id == 6) return engine->m_srvCollision->FindNonRecreableInstances(kCategoryNode, 6, count, out);
        return engine->m_graphic->FindNonRecreableInstances(kCategoryNode, id, count, out);
    default:
        return count == 0 ? 1 : 0;  // ((|count| - 1) >> 31)
    }
}

// 0x000250c8 Engine_Construct. +0x54 (AppConfig), +0xb4 (particle scheduler) and +0xb8 are left
// uninitialised, as in the original; their setters run before anything reads them.
GameEngineContext::GameEngineContext()
    : m_loadingManager(nullptr),
      m_graphic(nullptr),
      m_cameraContext(nullptr),
      m_mainSceneRoot(nullptr),
      m_secondarySceneRoot(nullptr),
      m_dynamicSceneRoot(nullptr),
      m_input(nullptr),
      m_soundManager(nullptr),
      m_classManager(nullptr),
      m_serviceManager(nullptr),
      m_lifeService(nullptr),
      m_coreManager(nullptr),
      m_fileSystem(nullptr),
      m_gameLoop(nullptr),
      m_manager2d(nullptr),
      m_flashManager(nullptr),
      m_textureBank(nullptr),
      m_animationManager(nullptr),
      m_timeManager(nullptr),
      m_objectDatabase(nullptr),
      m_pSavingManager(nullptr),
      m_srvCollision(nullptr),
      m_srvPhysics(nullptr),
      m_srvFx(nullptr),
      m_srvBonus(nullptr),
      m_srvProjectiles(nullptr),
      m_srvPathFinding(nullptr),
      m_srvCamera(nullptr),
      m_srvAvoidance(nullptr),
      m_srvBeacon(nullptr),
      m_jobQueue(nullptr),
      m_srvCinematic(nullptr),
      m_srvSekensor(nullptr),
      m_srvShadow(nullptr),
      m_gameManager(nullptr),
      m_level(nullptr),
      m_locManager(nullptr),
      m_srvCounter(nullptr),
      m_srvTrigger(nullptr),
      m_srvDetect(nullptr),
      m_srvMusic(nullptr),
      m_srvInput(nullptr),
      m_videoManager(nullptr),
      m_srvNetwork(nullptr),
      m_errorTable(nullptr) {
    g_pEngine = this;
}
