// GameLevelLoadRequest.cpp - reconstructed original translation unit 0x33b30-0x33f80 (GAME_TOC1, main_toc1), 11 functions, 9 live.
// Primary owner: GameLevelLoadRequest (not a registered class)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x33b30  GameLevelLoadRequest_RunSyncLevel_maybe  [dead]
//   [x] 0x33be0  GameLevelLoadRequest_Reset
//   [x] 0x33c20  GameLevelLoadRequest_CheckDone
//   [x] 0x33c88  GameLevelLoadRequest_Post
//   [x] 0x33d18  GameLevelLoadRequest_DeletingDestructor  (the deleting form of the implicit destructor)
//   [x] 0x33d60  GameLevelLoadRequest_Destructor
//   [ ] 0x33d90  GameLevelLoadRequest_Destructor_2  [dead]
//   [x] 0x33dc0  GameLevelLoadRequest_Construct
//   [x] 0x33e10  GameLevelLoadRequest_Construct_2  (the same as 0x33dc0 GameLevelLoadRequest_Construct)
//   [x] 0x33e60  GameLevelLoadRequest_Execute
//   [x] 0x33ee0  GameLevelLoadRequest_RunSync  (no reference to its descriptor in the original either)
#include "k2000/io/LoadRequests.h"

#include "k2000/misc/CKGameLoop.h"
#include "k2000/misc/Engine.h"

// 0x00033dc0 GameLevelLoadRequest_Construct
GameLevelLoadRequest::GameLevelLoadRequest() : m_posted(0), m_pad61(), m_kind(0), m_level(-1), m_pad6c() {}

// 0x00033be0 GameLevelLoadRequest_Reset
void GameLevelLoadRequest::Reset() {
    KRequest::Reset();
    m_kind = 0;
    m_level = -1;
}

// 0x00033c88 GameLevelLoadRequest_Post
void GameLevelLoadRequest::Post(int32_t kind, int32_t level) {
    Reset();
    m_kind = kind;
    m_level = level;
    g_pEngine->m_gameLoop->m_loadQueue.Enqueue(this);
    m_posted = 1;
}

// 0x00033c20 GameLevelLoadRequest_CheckDone
int32_t GameLevelLoadRequest::CheckDone() {
    uint8_t succeeded = 0;
    IsFinished(&succeeded);
    if (succeeded == 0) return 0;
    m_level = -1;
    m_posted = 0;
    return 1;
}

#include "k2000/logic/io/CKLoadingManager.h"

// 0x00033e60 GameLevelLoadRequest_Execute (worker thread)
void GameLevelLoadRequest::Execute() {
    if (m_kind == kGameFile) {
        g_pEngine->m_objectDatabase->LoadGameFile();
        return;
    }
    if (m_kind != kLevel) return;
    g_pEngine->m_objectDatabase->LoadLevel(m_level);
}

// 0x00033ee0 GameLevelLoadRequest_RunSync: the request run on the calling thread (Reset, the kind, Execute, Reset).
void GameLevelLoadRequest::RunSync(int32_t kind) {
    Reset();
    m_kind = kind;
    Execute();
    Reset();
}
