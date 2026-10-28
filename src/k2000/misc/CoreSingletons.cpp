// CoreSingletons.cpp - reconstructed original translation unit 0x252a40-0x253790 (GAME_TOC1, main_toc1), 19 functions, 14 live.
// Primary owner: CoreSingletons (not a registered class)
// Other owners: Engine (2), RegisterClass (2), Str (1), Run (1), Main (1), Cleanup (1), HandleParametersInternal (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x252a40  FUN_00252a40  [dead]
//   [x] 0x252a90  Engine_GetBootConfigStruct_maybe
//   [ ] 0x252aa0  Engine_GetInstance_maybe  [dead]
//   [x] 0x252ab0  StaticInitAndDestruction_252ab0
//   [ ] 0x252b78  _GLOBAL__D_252b78
//   [ ] 0x252b88  _GLOBAL__I_252b88
//   [x] 0x252b98  Str_FindTokenValueAfterSpace_maybe
//   [x] 0x252bf8  Run
//   [x] 0x252c28  Main_InitGame_maybe
//   [x] 0x252d20  CoreSingletons_Destroy_maybe
//   [ ] 0x252e68  CoreSingletons_Teardown_maybe  [dead]
//   [x] 0x252e90  CoreSingletons_Create_maybe
//   [ ] 0x252f88  CoreSingletons_EnsureCreated_2_maybe  [dead]
//   [x] 0x252fe8  Cleanup
//   [ ] 0x253120  RegisterClass_2  [dead]
//   [x] 0x2531f0  CoreSingletons_EnsureCreated_maybe
//   [x] 0x253250  RegisterClass
//   [x] 0x253320  HandleParametersInternal
//   [x] 0x253688  HandleParameters
#include "k2000/misc/CoreSingletons.h"

#include <cstdio>
#include <cstring>

#include "k2000/core/Stub.h"
#include "k2000/io/KFileSystem.h"
#include "k2000/logic/CKCoreManager.h"
#include "k2000/logic/io/CKLoadingManager.h"
#include "k2000/logic/ui/CLocManager.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/CKGameLoop.h"
#include "k2000/misc/ClassManager.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/misc/Engine.h"

CKGameLoop* g_pCKGameLoop = nullptr;  // 0x00ceab68
AppConfig g_appConfig;                // 0x00ceab6c

namespace {
// The core singletons (0x00ceac4c..0x00ceac54), owned here; the engine slots point to the same objects.
KFileSystem* s_fileSystem = nullptr;      // 0x00ceac4c
CKCoreManager* s_coreManager = nullptr;   // 0x00ceac50
ClassManager* s_classManager = nullptr;   // 0x00ceac54
// 0x00c40269 (.data, initial 1): the singletons still have to be created.
uint8_t s_coreSingletonsPending = 1;
// 0x00c50df8: read into AppConfig.backColor before -BackColor is parsed. TODO(verify): its value at that
// point (it is in .bss; a static constructor also references it).
uint32_t s_defaultBackColor = 0;

const char* const kGameName = "Spyro 2008";        // 0x00ac9080
const char* const kCompanyName = "Vivendi Games";  // 0x00ac9090
const char* const kProductCode = "SPYRO08";        // 0x00ac90a0
const char* const kTitleId = "BLUS-30205";         // 0x00ac90a8
}  // namespace

// STUB helpers from units that are not ported yet (bodies in k2000/stubs/BootStubs.cpp).
void FreeListPools_InitGlobal();      // 0x00244a08 _maybe
void FreeListPools_FreeAllGlobal();   // 0x00244af0 _maybe
void KThread_InitMainThread();        // 0x000537b0 _maybe
void KThread_ReleaseMainThread();     // 0x000535e0 _maybe
void* KMemoryManager_GetGlobal();     // 0x00012158 _maybe: returns the never-constructed KMemoryManager (null)
void KStub_Nop_11730();               // Str.cpp
void KStub_Nop_10688();               // 0x00010688
void KStub_Nop_12168();               // 0x00012168
void Uuid_Clear(uint8_t* uuid);       // 0x002461c0
void Uuid_ParseHexString(uint8_t* uuid, const char* text);  // 0x002462d0 _maybe

// 0x00252a90 Engine_GetBootConfigStruct_maybe
AppConfig* Engine_GetBootConfigStruct() { return &g_appConfig; }

// 0x00252ab0 StaticInitAndDestruction_252ab0 (priority 0xffff static initialiser of this unit)
void CoreSingletons_StaticInit() {
    g_appConfig.displayId = 0;
    g_appConfig.width = 0;
    g_appConfig.height = 0;
    g_appConfig.bitsPerPixel = 0;
    g_appConfig.backColor = 0;
    g_appConfig.flag14 = 0;
    g_appConfig.parametersHandled = 0;
    std::memset(g_appConfig.gameStateUuid, 0, sizeof(g_appConfig.gameStateUuid));
    g_appConfig.unk18 = 0;
    g_appConfig.unk20 = 0;
    g_appConfig.gameName[0] = 0;
    g_appConfig.companyName[0] = 0;
    g_appConfig.productCode[0] = 0;
    g_appConfig.titleId[0] = 0;
    Uuid_Clear(g_appConfig.gameStateUuid);
    g_appConfig.performanceAnalysis = 0;
    g_appConfig.unkAc = -1;
}

// 0x00252b98 Str_FindTokenValueAfterSpace_maybe: the text after the first space following the token.
const char* Str_FindTokenValueAfterSpace(const char* text, const char* token) {
    const char* found = std::strstr(text, token);
    if (found == nullptr) return nullptr;
    const char* space = std::strchr(found, ' ');
    return space != nullptr ? space + 1 : found;
}

// 0x00252bf8 Run
uint32_t Run() { return g_pCKGameLoop->RunFrame() & 0xff; }

// 0x00252c28 Main_InitGame_maybe
int32_t Main_InitGame() {
    FreeListPools_InitGlobal();
    KThread_InitMainThread();
    g_pCKGameLoop = static_cast<CKGameLoop*>(ClassRegistry_CreateObjectByKey(0x4c));
    Engine_SetGameLoop(g_pCKGameLoop);
    if (g_pCKGameLoop == nullptr) return 0;
    const int32_t result = g_pCKGameLoop->InitializeSubsystems(&g_appConfig);
    if (result != 1) return result;
    g_pEngine->m_coreManager->Init();
    Engine_SetLocManager(static_cast<CLocManager*>(ClassRegistry_CreateObjectByKey(0xecc)));
    KStub_Nop_11730();
    return 1;
}

// 0x00252d20 CoreSingletons_Destroy_maybe
void CoreSingletons_Destroy() {
    delete s_fileSystem;
    s_fileSystem = nullptr;
    Engine_SetFileSystem(nullptr);
    delete s_coreManager;
    s_coreManager = nullptr;
    Engine_SetCoreManager(nullptr);
    Engine_SetClassManager(nullptr);
    delete s_classManager;
    s_classManager = nullptr;
    GameEngineContext* engine = g_pEngine;
    if (engine != nullptr) delete engine;  // KStub_Nop_24bc8 (empty destructor) + operator delete
    Engine_SetInstance(nullptr);
}

// 0x00252e90 CoreSingletons_Create_maybe
void CoreSingletons_Create() {
    GameEngineContext* engine = new GameEngineContext();  // sets g_pEngine
    Engine_SetStaticStateBlock(&g_appConfig);
    (void)engine;
    s_classManager = new ClassManager();
    Engine_SetClassManager(s_classManager);
    s_coreManager = new CKCoreManager();
    Engine_SetCoreManager(s_coreManager);
    s_fileSystem = new KFileSystem();
    Engine_SetFileSystem(s_fileSystem);
}

// 0x00252fe8 Cleanup
void Cleanup() {
    CKLoadingManager* loadingManager = g_pEngine->m_objectDatabase;
    if (loadingManager != nullptr) {
        loadingManager->UnloadLevel();
        loadingManager->UnloadGameObjects();
    }
    KStub_Nop_10688();
    g_pCKGameLoop->ShutdownSubsystems();
    ClassRegistry_DestroyObject(g_pCKGameLoop);
    Engine_SetGameLoop(nullptr);
    g_pCKGameLoop = nullptr;
    CLocManager* locManager = g_pEngine->m_locManager;
    if (locManager != nullptr) {
        locManager->Destroy();
        ClassRegistry_DestroyObject(locManager);
        Engine_SetLocManager(nullptr);
    }
    g_pEngine->m_coreManager->ShutdownParticleUpdateScheduler();
    FreeListPools_FreeAllGlobal();
    KThread_ReleaseMainThread();
    CoreSingletons_Destroy();
    KStub_Nop_12168();
}

// 0x002531f0 CoreSingletons_EnsureCreated_maybe
void CoreSingletons_EnsureCreated() {
    if (s_coreSingletonsPending == 0) return;
    s_coreSingletonsPending = 0;
    KMemoryManager_GetGlobal();
    CoreSingletons_Create();
}

// 0x00253250 RegisterClass
void RegisterClass(uint16_t category, uint16_t id, ClassManager::CreateFn create, ClassManager::DeleteFn destroy,
                   ClassManager::CreateArrayFn createArray, ClassManager::DeleteArrayFn destroyArray) {
    if (s_coreSingletonsPending != 0) {
        s_coreSingletonsPending = 0;
        KMemoryManager_GetGlobal();
        CoreSingletons_Create();
    }
    s_classManager->RegisterClass(category, id, create, destroy, createArray, destroyArray);
}

// 0x00253320 HandleParametersInternal
int32_t HandleParametersInternal(const char* arguments) {
    char argBuffer[0x1008];
    char path[0x100];
    argBuffer[0] = 0;
    std::strcpy(g_appConfig.gameName, kGameName);
    std::strcpy(g_appConfig.companyName, kCompanyName);
    std::strcpy(g_appConfig.productCode, kProductCode);
    std::strcpy(g_appConfig.titleId, kTitleId);
    const size_t length = std::strlen(argBuffer);
    argBuffer[length] = ' ';
    argBuffer[length + 1] = 0;
    std::strncat(argBuffer, arguments, sizeof(argBuffer) - std::strlen(argBuffer) - 1);

    // -Path "<dir>": the data root (default "").
    const char* value = std::strstr(argBuffer, "-Path");
    if (value != nullptr) {
        const char* space = std::strchr(value, ' ');
        if (space != nullptr) value = space + 1;
    }
    if (value == nullptr || *value != '"') {
        g_pEngine->m_fileSystem->SetDataRoot("");
    } else {
        std::snprintf(path, sizeof(path), "%s", value + 1);
        if (std::strchr(value, '"') == value) {
            std::snprintf(path, sizeof(path), "%s", value + 1);
            char* quote = std::strchr(path, '"');
            if (quote != nullptr) *quote = 0;
        }
        g_pEngine->m_fileSystem->SetDataRoot(path);
    }
    g_appConfig.parametersHandled = 1;

    // -BackColor "0x%x"
    g_appConfig.backColor = s_defaultBackColor;
    value = std::strstr(argBuffer, "-BackColor");
    if (value != nullptr) {
        const char* space = std::strchr(value, ' ');
        if (space != nullptr) value = space + 1;
        unsigned int color = 0;
        if (std::sscanf(value, "\"0x%x", &color) == 1) g_appConfig.backColor = color & 0xffffff00u;
    }

    // -GameState "<uuid>"
    value = std::strstr(argBuffer, "-GameState");
    if (value != nullptr) {
        const char* space = std::strchr(value, ' ');
        if (space != nullptr) value = space + 1;
    }
    if (value == nullptr) {
        Uuid_Clear(g_appConfig.gameStateUuid);
    } else if (*value == '"') {
        Uuid_ParseHexString(g_appConfig.gameStateUuid, value + 1);
    }

    // -PerformanceAnalysis
    g_appConfig.performanceAnalysis = std::strstr(argBuffer, "-PerformanceAnalysis") != nullptr ? 1 : 0;
    return 1;
}

// 0x00253688 HandleParameters
int32_t HandleParameters(int32_t argc, const char* const* argv) {
    char buffer[0x400];
    buffer[0] = 0;  // the original leaves it uninitialised when argc is 0 (never the case: argv[0] is always passed)
    if (argc != 0) {
        std::snprintf(buffer, sizeof(buffer), "%s", argv[0]);
        for (int32_t i = 1; i < argc; ++i) {
            const size_t length = std::strlen(buffer);
            if (length + 1 < sizeof(buffer)) {
                buffer[length] = ' ';
                buffer[length + 1] = 0;
            }
            std::strncat(buffer, argv[i], sizeof(buffer) - std::strlen(buffer) - 1);
        }
    }
    HandleParametersInternal(buffer);
    return 1;
}
