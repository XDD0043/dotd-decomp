// BootLoadRequest.cpp - reconstructed original translation unit 0x34388-0x34770 (GAME_TOC1, main_toc1), 16 functions, 12 live.
// Primary owner: BootLoadRequest (not a registered class)
// Other owners: CKLoadRequestQueue (4)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x34388  BootLoadRequest_Execute_maybe
//   [x] 0x343f0  BootLoadRequest_Reset_maybe
//   [x] 0x34418  BootLoadRequest_CheckDone_maybe
//   [x] 0x34478  BootLoadRequest_Post_maybe
//   [ ] 0x344e8  BootLoadRequest_DeletingDestructor_maybe
//   [ ] 0x34530  BootLoadRequest_Destructor_maybe
//   [ ] 0x34560  BootLoadRequest_Destructor_2_maybe
//   [x] 0x34590  BootLoadRequest_Construct_maybe
//   [ ] 0x345d0  BootLoadRequest_Construct_2_maybe
//   [ ] 0x34610  CKLoadRequestQueue_JoinThreads
//   [ ] 0x34650  CKLoadRequestQueue_Abort
//   [ ] 0x34688  CKLoadRequestQueue_CancelRequest_maybe  [dead]
//   [x] 0x346b0  CKLoadRequestQueue_Enqueue
//   [ ] 0x346d8  FUN_000346d8  [dead]
//   [ ] 0x34708  FUN_00034708  [dead]
//   [ ] 0x34738  FUN_00034738  [dead]
#include "k2000/io/LoadRequests.h"

#include "k2000/misc/CKGameLoop.h"
#include "k2000/misc/Engine.h"

// 0x00034590 BootLoadRequest_Construct_maybe
BootLoadRequest::BootLoadRequest() : m_posted(0), m_pad61() {}

// 0x000343f0 BootLoadRequest_Reset_maybe
void BootLoadRequest::Reset() { KRequest::Reset(); }

// 0x00034478 BootLoadRequest_Post_maybe
void BootLoadRequest::Post() {
    Reset();
    g_pEngine->m_gameLoop->m_loadQueue.Enqueue(this);
    m_posted = 1;
}

// 0x00034418 BootLoadRequest_CheckDone_maybe (the decompiler drops the "done" branch; the assembly
// returns 1 and clears m_posted)
int32_t BootLoadRequest::CheckDone() {
    uint8_t succeeded = 0;
    IsFinished(&succeeded);
    if (succeeded == 0) return 0;
    m_posted = 0;
    return 1;
}

// 0x00034770 CKLoadRequestQueue_Construct. Priority level 2 (RPCS3 shows the thread at 1002).
CKLoadRequestQueue::CKLoadRequestQueue() : keCThreadPool(1, "CKLoadRequestQueue", 2), m_unkD0(0), m_unkD1(0), m_padD2() {
    SetWaitOnPoll();  // platform: the loads are waited for in reproducible runs (sys_thread.h SetDeterministicRequests)
}

// 0x000346b0 CKLoadRequestQueue_Enqueue
void CKLoadRequestQueue::Enqueue(KRequest* request) { keCThreadPool::Enqueue(request); }
