// LocLoadRequest.cpp - reconstructed original translation unit 0x33f80-0x34388 (GAME_TOC1, main_toc1), 11 functions, 7 live.
// Primary owner: LocLoadRequest (not a registered class)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x33f80  LocLoadRequest_Reset
//   [x] 0x33fb8  LocLoadRequest_CheckDone
//   [ ] 0x34018  LocLoadRequest_Wait_maybe  [dead]
//   [x] 0x34070  LocLoadRequest_Post
//   [ ] 0x340f0  LocLoadRequest_DeletingDestructor
//   [ ] 0x34138  LocLoadRequest_Destructor
//   [ ] 0x34168  LocLoadRequest_Destructor_2  [dead]
//   [x] 0x34198  LocLoadRequest_Construct
//   [ ] 0x341e0  LocLoadRequest_Construct_2  [dead]
//   [x] 0x34228  LocLoadRequest_Execute
//   [ ] 0x342f8  LocLoadRequest_RunSync_maybe  [dead]
#include "k2000/io/LoadRequests.h"

#include "k2000/misc/CKGameLoop.h"
#include "k2000/misc/Engine.h"

// 0x00034198 LocLoadRequest_Construct
LocLoadRequest::LocLoadRequest() : m_posted(0), m_pad61(), m_kind(0) {}

// 0x00033f80 LocLoadRequest_Reset
void LocLoadRequest::Reset() {
    KRequest::Reset();
    m_kind = 0;
}

// 0x00034070 LocLoadRequest_Post
void LocLoadRequest::Post(int32_t kind) {
    Reset();
    m_kind = kind;
    g_pEngine->m_gameLoop->m_loadQueue.Enqueue(this);
    m_posted = 1;
}

// 0x00033fb8 LocLoadRequest_CheckDone
int32_t LocLoadRequest::CheckDone() {
    uint8_t succeeded = 0;
    IsFinished(&succeeded);
    if (succeeded == 0) return 0;
    m_posted = 0;
    return 1;
}

#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/logic/io/CKLoadingManager.h"
#include "k2000/logic/CKCoreManager.h"
#include "k2000/logic/ui/CLocManager.h"

// 0x00034228 LocLoadRequest_Execute (worker thread)
void LocLoadRequest::Execute() {
    const int32_t kind = m_kind;
    if (kind == kLevel) {
        g_pEngine->m_objectDatabase->LoadLocFile(g_pEngine->m_locManager->m_languageIndex, K_LEVEL_LOCALIZATION,
                                                 g_pEngine->m_gameManager->m_currentLevel);
        return;
    }
    if (kind != 3) {
        if (kind != kDefaultAndSystemLanguage) return;
        LoadDefaultAndSystemLanguageLocFiles(g_pEngine->m_gameManager);
        return;
    }
    // Kind 3 (kChangeLanguage): the options menu's language change. The PS3 code leaves r5 (reload) as it
    // was; Engine_ReloadLocalizedData does not use it.
    Engine_ChangeLanguage(g_pEngine->m_coreManager, g_pEngine->m_gameManager->m_unk290, 0);
}
