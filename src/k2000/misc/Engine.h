// Engine.h - GameEngineContext, the engine singleton (k2000). Original unit: Engine.cpp
// (0x24bd0-0x25258): one setter per slot and the constructor.
//
// Created by CoreSingletons_Create_maybe before main (0xc0 bytes); the global g_pEngine (0x00c50f20)
// points to it. Ghidra labels the global PTR_DragonInstance_*; it is the engine, not a dragon.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"

class CAnimationManager;
class CKCoreManager;
class CKErrorTable;
class CKFlashManager;
class CKGameLoop;
class CKGraphic;
class CKInput;
class CKLevel;
class CKLoadingManager;
class CDefaultGameManager;
class CKSavingManager;
class CKServiceManager;
class CKSoundManager;
class CLocManager;
class CManager2d;
class CVideoManager;
class ClassManager;
class JobQueue;
class KFileSystem;
class CTimeManager;
struct ParticleUpdateScheduler;
class TextureBank;
struct AppConfig;

// Services and scene roots stay opaque until their classes are ported.
class IKSerializable;

class GameEngineContext {
public:
    // 0x000250c8 Engine_Construct: clears the slots and sets g_pEngine.
    GameEngineContext();

    CKLoadingManager* m_loadingManager;    // +0x00 Engine_SetLoadingManager (see m_objectDatabase)
    CKGraphic* m_graphic;                  // +0x04
    void* m_cameraContext;                 // +0x08
    IKSerializable* m_mainSceneRoot;             // +0x0c CSGRootNode _maybe
    IKSerializable* m_secondarySceneRoot;        // +0x10 CSGRootNode _maybe
    IKSerializable* m_dynamicSceneRoot;          // +0x14 CSGSectorRoot
    CKInput* m_input;                      // +0x18
    CKSoundManager* m_soundManager;        // +0x1c
    ClassManager* m_classManager;          // +0x20
    CKServiceManager* m_serviceManager;    // +0x24
    IKSerializable* m_lifeService;               // +0x28 CKServiceLife
    CKCoreManager* m_coreManager;          // +0x2c
    KFileSystem* m_fileSystem;             // +0x30
    CKGameLoop* m_gameLoop;                // +0x34
    CManager2d* m_manager2d;               // +0x38
    CKFlashManager* m_flashManager;        // +0x3c
    TextureBank* m_textureBank;            // +0x40 _maybe
    CAnimationManager* m_animationManager; // +0x44 _maybe
    CTimeManager* m_timeManager;           // +0x48 _maybe
    CKLoadingManager* m_objectDatabase;    // +0x4c Engine_SetLoadingManager_2: the CKLoadingManager in use
    CKSavingManager* m_pSavingManager;      // +0x50
    AppConfig* m_appConfig;                // +0x54 Engine_SetStaticStateBlock_maybe (the boot AppConfig)
    IKSerializable* m_srvCollision;              // +0x58
    IKSerializable* m_srvPhysics;                // +0x5c
    IKSerializable* m_srvFx;                     // +0x60
    IKSerializable* m_srvBonus;                  // +0x64 _maybe
    IKSerializable* m_srvProjectiles;            // +0x68
    IKSerializable* m_srvPathFinding;            // +0x6c
    IKSerializable* m_srvCamera;                 // +0x70 _maybe
    IKSerializable* m_srvAvoidance;              // +0x74 _maybe
    IKSerializable* m_srvBeacon;                 // +0x78
    JobQueue* m_jobQueue;                  // +0x7c _maybe
    IKSerializable* m_srvCinematic;              // +0x80
    IKSerializable* m_srvSekensor;               // +0x84
    IKSerializable* m_srvShadow;                 // +0x88 _maybe
    CDefaultGameManager* m_gameManager;    // +0x8c a CKS08GameManager (loaded from GAME.KP3)
    CKLevel* m_level;                      // +0x90
    CLocManager* m_locManager;             // +0x94
    IKSerializable* m_srvCounter;                // +0x98
    IKSerializable* m_srvTrigger;                // +0x9c
    IKSerializable* m_srvDetect;                 // +0xa0
    IKSerializable* m_srvMusic;                  // +0xa4
    IKSerializable* m_srvInput;                  // +0xa8
    CVideoManager* m_videoManager;         // +0xac
    IKSerializable* m_srvNetwork;                // +0xb0 PS3_CKSrvNetwork
    ParticleUpdateScheduler* m_particleScheduler;  // +0xb4 _maybe
    IKSerializable* m_srvDynamic;                // +0xb8 _maybe
    CKErrorTable* m_errorTable;            // +0xbc _maybe
};
DOTD_ASSERT_SIZE(GameEngineContext, 0xc0);
DOTD_ASSERT_OFFSET(GameEngineContext, m_classManager, 0x20);
DOTD_ASSERT_OFFSET(GameEngineContext, m_gameLoop, 0x34);
DOTD_ASSERT_OFFSET(GameEngineContext, m_timeManager, 0x48);
DOTD_ASSERT_OFFSET(GameEngineContext, m_objectDatabase, 0x4c);
DOTD_ASSERT_OFFSET(GameEngineContext, m_gameManager, 0x8c);
DOTD_ASSERT_OFFSET(GameEngineContext, m_videoManager, 0xac);
DOTD_ASSERT_OFFSET(GameEngineContext, m_errorTable, 0xbc);

// 0x00c50f20
extern GameEngineContext* g_pEngine;

// Setters (Engine.cpp, address order). Each stores into g_pEngine.
void Engine_SetSrvCamera(IKSerializable* service);             // 0x24bd0 _maybe
void Engine_SetInstance(GameEngineContext* engine);       // 0x24be0 _maybe: sets g_pEngine itself
void Engine_SetLoadingManager(CKLoadingManager* manager); // 0x24bf0
void Engine_SetSrvBeacon(IKSerializable* service);              // 0x24c00
void Engine_SetAvoidanceService(IKSerializable* service);       // 0x24c10 _maybe
void Engine_SetSrvCinematic(IKSerializable* service);           // 0x24c20
void Engine_SetSrvSekensor(IKSerializable* service);            // 0x24c30
void Engine_SetShadowService(IKSerializable* service);          // 0x24c40 _maybe
void Engine_SetLevel(CKLevel* level);                     // 0x24c50
void Engine_SetGameManager(CDefaultGameManager* manager); // 0x24c60
void Engine_SetLocManager(CLocManager* manager);          // 0x24c70
void Engine_SetGraphic(CKGraphic* graphic);               // 0x24c80
void Engine_SetMainSceneRoot(IKSerializable* root);             // 0x24c90 _maybe
void Engine_SetSecondarySceneRoot(IKSerializable* root);        // 0x24ca0 _maybe
void Engine_SetDynamicSceneRoot(IKSerializable* root);          // 0x24cb0
void Engine_SetInput(CKInput* input);                     // 0x24cc0
void Engine_SetSoundManager(CKSoundManager* manager);     // 0x24cd0
void Engine_SetClassManager(ClassManager* manager);       // 0x24ce0
void Engine_SetServiceManager(CKServiceManager* manager); // 0x24cf0
void Engine_SetServiceLife(IKSerializable* service);            // 0x24d00
void Engine_SetCoreManager(CKCoreManager* manager);       // 0x24d10
void Engine_SetFileSystem(KFileSystem* fileSystem);       // 0x24d20
void Engine_SetGameLoop(CKGameLoop* gameLoop);            // 0x24d30
void Engine_SetManager2d(CManager2d* manager);            // 0x24d40
void Engine_SetTextureBank(TextureBank* bank);            // 0x24d50 _maybe
void Engine_SetAnimationManager(CAnimationManager* m);    // 0x24d60 _maybe
void Engine_SetTimeManager(CTimeManager* manager);        // 0x24d70 _maybe
void Engine_SetJobQueue(JobQueue* queue);                 // 0x24d80 _maybe
void Engine_SetSavingManager(CKSavingManager* manager);   // 0x24d90
void Engine_SetLoadingManager_2(CKLoadingManager* m);     // 0x24da0 (+0x4c)
void Engine_SetSrvCollision(IKSerializable* service);           // 0x24db0 (was CKSrvCollision_ConstructBase_maybe in Ghidra)
void Engine_SetSrvPhysics(IKSerializable* service);             // 0x24dc0
void Engine_SetSrvPathFinding(IKSerializable* service);         // 0x24dd0
void Engine_SetProjectilesService(IKSerializable* service);     // 0x24de0
void Engine_SetSrvFx(IKSerializable* service);                  // 0x24df0 (was CKSrvFx_ConstructBase_maybe in Ghidra)
void Engine_SetBonusService(IKSerializable* service);           // 0x24e00 _maybe
void Engine_SetSrvCounter(IKSerializable* service);             // 0x24e10 (was CKSrvCounter_ConstructBase_maybe in Ghidra)
void Engine_SetSrvTrigger(IKSerializable* service);             // 0x24e20
void Engine_SetSrvDetect(IKSerializable* service);              // 0x24e30
void Engine_SetFlashManager(CKFlashManager* manager);     // 0x24e40
void Engine_SetSrvMusic(IKSerializable* service);               // 0x24e50
void Engine_SetSrvInput(IKSerializable* service);               // 0x24e60 (was CKSrvInput_ConstructBase_maybe in Ghidra)
void Engine_SetVideoManager(CVideoManager* manager);      // 0x24e70
void Engine_SetStaticStateBlock(AppConfig* config);       // 0x24e80 _maybe
void Engine_SetErrorTable(CKErrorTable* table);           // 0x24e90 _maybe
void Engine_SetSrvNetwork(IKSerializable* service);             // 0x24ea0 (was PS3_CKSrvNetwork_ConstructBase_maybe in Ghidra)
void Engine_SetDynamicService(IKSerializable* service);         // 0x24eb0 _maybe
void Engine_SetParticleScheduler(ParticleUpdateScheduler* scheduler);  // 0x24ec0 _maybe

// 0x00024ed0 Engine_GetGlobalInstances: hands the loader the global objects of (category, id):
// category 0 the managers, 1 the services, 2/4/12 CKCoreManager's provider, 10/13 CKGraphic's, 11:6
// CKSrvCollision's (the 50 projectiles). count 1 writes the object to *out; count > 1 fills the pointer
// array *out points to. Returns 1 when provided (an unknown category returns count == 0).
uint8_t Engine_GetGlobalInstances(GameEngineContext* engine, int32_t category, uint32_t id, uint32_t count, void* out);
