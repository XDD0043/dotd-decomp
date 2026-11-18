// CKLoadRequestQueue.cpp - the load queue's destructor (the constructor and Enqueue are in BootLoadRequest.cpp).
//
// Reconstructed original translation unit: 0x34770-0x349a0 (GAME_TOC1, main_toc1), 4 functions, 4 live.
// Primary owner: CKLoadRequestQueue (not a registered class)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x34770  CKLoadRequestQueue_Construct
//   [x] 0x347b8  CKLoadRequestQueue_Construct_2  (the same as 0x34770 CKLoadRequestQueue_Construct)
//   [x] 0x34800  CKLoadRequestQueue_Destructor_2_maybe  (the same as 0x348d0 CKLoadRequestQueue_Destructor_maybe)
//   [x] 0x348d0  CKLoadRequestQueue_Destructor_maybe
#include "k2000/io/LoadRequests.h"

// 0x000348d0 CKLoadRequestQueue_Destructor_maybe: the abort requested unless it was, the workers joined unless they
// were, then the pool's destructor (keCThreadPool_Destructor; the host pool also aborts and joins, idempotently).
CKLoadRequestQueue::~CKLoadRequestQueue() {
    if (m_unkD1 == 0) {
        RequestAbort();
        m_unkD1 = 1;
    }
    if (m_unkD0 != 0) return;
    keCThreadPool::JoinThreads();
    m_unkD0 = 1;
}
