// CoreSingletons.h - process-level setup (k2000). Original unit: CoreSingletons.cpp (0x252a40-0x253790):
// the core singletons created before main, class registration, the boot AppConfig, command-line
// parameters, Main_InitGame, the per-frame Run and Cleanup. main itself is in CellSysutilCallback.cpp.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/ClassManager.h"

class CKGameLoop;
class CKCoreManager;
class KFileSystem;

// 0x00ceab6c, the boot configuration ("static state block", GameEngineContext +0x54). Zeroed by the
// static initialiser 0x252ab0, filled by main and HandleParametersInternal, read by CKGraphic init.
struct AppConfig {
    int32_t displayId;           // +0x00 RwEngineOpen display
    int32_t width;               // +0x04 main: 640 (the device later writes 1280)
    int32_t height;              // +0x08 main: 480 (720)
    int32_t bitsPerPixel;        // +0x0c main: 0 (32)
    uint32_t backColor;          // +0x10 -BackColor "0x%x" & 0xffffff00
    uint8_t flag14;              // +0x14 main: 1
    uint8_t parametersHandled;   // +0x15 _maybe: HandleParametersInternal sets 1
    uint8_t pad16[2];            // +0x16
    int32_t unk18;               // +0x18 main: 0
    int32_t unk1c;               // +0x1c never initialised
    int32_t unk20;               // +0x20 main: 0
    char gameName[0x28];         // +0x24 "Spyro 2008"
    char companyName[0x28];      // +0x4c "Vivendi Games"
    char productCode[0x14];      // +0x74 "SPYRO08"
    char titleId[0x14];          // +0x88 "BLUS-30205"
    uint8_t gameStateUuid[0x10]; // +0x9c -GameState "<uuid>"
    int32_t unkAc;               // +0xac static init: -1
    int32_t performanceAnalysis; // +0xb0 -PerformanceAnalysis
    uint8_t unkB4[0x2c];         // +0xb4 not referenced so far (up to the next global at 0xceac4c)
};
DOTD_ASSERT_SIZE(AppConfig, 0xe0);
DOTD_ASSERT_OFFSET(AppConfig, backColor, 0x10);
DOTD_ASSERT_OFFSET(AppConfig, gameName, 0x24);
DOTD_ASSERT_OFFSET(AppConfig, gameStateUuid, 0x9c);
DOTD_ASSERT_OFFSET(AppConfig, performanceAnalysis, 0xb0);

// 0x00ceab68 g_pCKGameLoop: the game loop object (also GameEngineContext +0x34).
extern CKGameLoop* g_pCKGameLoop;
// 0x00ceab6c
extern AppConfig g_appConfig;

// 0x00252a90 Engine_GetBootConfigStruct_maybe
AppConfig* Engine_GetBootConfigStruct();
// 0x00252ab0 StaticInitAndDestruction_252ab0: the AppConfig static initialiser (called by RegisterAllClasses
// before any class registration, as the original static-constructor order does for this unit).
void CoreSingletons_StaticInit();
// 0x00252b98 Str_FindTokenValueAfterSpace_maybe
const char* Str_FindTokenValueAfterSpace(const char* text, const char* token);
// 0x00252bf8 Run: one frame. Returns 0 when the game loop has reached mode 10 (quit).
uint32_t Run();
// 0x00252c28 Main_InitGame_maybe: 1 = ok.
int32_t Main_InitGame();
// 0x00252d20 CoreSingletons_Destroy_maybe
void CoreSingletons_Destroy();
// 0x00252e90 CoreSingletons_Create_maybe
void CoreSingletons_Create();
// 0x00252fe8 Cleanup
void Cleanup();
// 0x002531f0 CoreSingletons_EnsureCreated_maybe
void CoreSingletons_EnsureCreated();
// 0x00253250 RegisterClass. The original's first argument (a per-class "registered" byte) and fourth
// (a priority) are not used by the function and are left out.
void RegisterClass(uint16_t category, uint16_t id, ClassManager::CreateFn create, ClassManager::DeleteFn destroy,
                   ClassManager::CreateArrayFn createArray, ClassManager::DeleteArrayFn destroyArray);
// 0x00253320 HandleParametersInternal
int32_t HandleParametersInternal(const char* arguments);
// 0x00253688 HandleParameters: joins argv with spaces, then HandleParametersInternal.
int32_t HandleParameters(int32_t argc, const char* const* argv);
