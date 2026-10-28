// SaveDataRequest.cpp - reconstructed original translation unit 0x2b2d0-0x2b600 (GAME_TOC1, main_toc1), 12 functions, 9 live.
// Primary owner: SaveDataRequest (not a registered class)
// Other owners: CKMemcardRequestQueue (3), SaveDataQueue (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x2b2d0  SaveDataRequest_Execute
//   [x] 0x2b370  SaveDataRequest_CheckDone
//   [x] 0x2b3a8  SaveDataRequest_Post
//   [ ] 0x2b420  SaveDataRequest_DeletingDestructor
//   [ ] 0x2b468  SaveDataRequest_Destructor
//   [ ] 0x2b498  SaveDataRequest_Destructor_2  [dead]
//   [x] 0x2b4c8  SaveDataRequest_Construct
//   [ ] 0x2b500  SaveDataRequest_Construct_2  [dead]
//   [ ] 0x2b538  CKMemcardRequestQueue_JoinThreads
//   [ ] 0x2b578  CKMemcardRequestQueue_Abort
//   [ ] 0x2b5b0  CKMemcardRequestQueue_CancelRequest_maybe  [dead]
//   [x] 0x2b5d8  SaveDataQueue_Enqueue_maybe
#include "k2000/io/LoadRequests.h"

// 0x0002b4c8 SaveDataRequest_Construct  STUB(save data)
SaveDataRequest::SaveDataRequest() : m_kind(0), m_pad64() {}

// 0x0002b600 CKMemcardRequestQueue_Construct. Priority level 3 (RPCS3 shows the thread at 1001).
CKMemcardRequestQueue::CKMemcardRequestQueue()
    : keCThreadPool(1, "CKMemcardRequestQueue::keCThreadPool", 3), m_unkD0(0), m_unkD1(0), m_padD2() {}

#include "k2000/io/SaveData.h"
#include "k2000/misc/CKGameLoop.h"
#include "k2000/misc/Engine.h"

// 0x0002b2d0 SaveDataRequest_Execute
void SaveDataRequest::Execute() {
    switch (m_kind) {
    case kListLoad: SaveData_ListLoad(); return;
    case kListSave: SaveData_ListSave(); return;
    case kDelete: SaveData_Delete(); return;
    case kListAutoLoad: SaveData_ListAutoLoad(); return;
    default: return;
    }
}

// 0x0002b370 SaveDataRequest_CheckDone
uint8_t SaveDataRequest::CheckDone() {
    uint8_t succeeded = 0;
    IsFinished(&succeeded);
    return succeeded;
}

// 0x0002b3a8 SaveDataRequest_Post: reset, the kind, onto the memcard queue (0x2b5d8 SaveDataQueue_Enqueue_maybe).
void SaveDataRequest::Post(int32_t kind) {
    Reset();
    m_kind = kind;
    g_pEngine->m_gameLoop->m_memcardQueue.Enqueue(this);
}
