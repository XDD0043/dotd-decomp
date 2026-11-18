// CKFileSystemRequestQueue.cpp - reconstructed original translation unit 0x4f3c0-0x4f628 (GAME_TOC1, main_toc1), 6 functions, 5 live.
// Primary owner: CKFileSystemRequestQueue (not a registered class)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x4f3c0  CKFileSystemRequestQueue_Enqueue
//   [x] 0x4f3e8  CKFileSystemRequestQueue_Construct
//   [x] 0x4f430  CKFileSystemRequestQueue_Construct_2  (the same as 0x4f3e8 CKFileSystemRequestQueue_Construct)
//   [x] 0x4f478  CKFileSystemRequestQueue_Destructor_2_maybe  (the same as 0x4f548 CKFileSystemRequestQueue_Destructor)
//   [x] 0x4f548  CKFileSystemRequestQueue_Destructor
//   [ ] 0x4f618  FUN_0004f618  [dead]
//
// Also here: 0x4f320 CKFileSystemRequestQueue_JoinThreads and 0x4f360 CKFileSystemRequestQueue_Abort (KFileReadRequest.cpp's
// range).
#include "k2000/io/CKFileSystemRequestQueue.h"

// 0x0004f3e8 CKFileSystemRequestQueue_Construct
CKFileSystemRequestQueue::CKFileSystemRequestQueue()
    : keCThreadPool(1, "CKFileSystemRequestQueue", 2), m_unkD0(0), m_unkD1(0), m_padD2() {}

// 0x0004f548 CKFileSystemRequestQueue_Destructor: the abort requested unless it was, the workers joined unless they
// were, then the pool's destructor.
CKFileSystemRequestQueue::~CKFileSystemRequestQueue() {
    if (m_unkD1 == 0) {
        RequestAbort();
        m_unkD1 = 1;
    }
    if (m_unkD0 != 0) return;
    keCThreadPool::JoinThreads();
    m_unkD0 = 1;
}

// 0x0004f3c0 CKFileSystemRequestQueue_Enqueue
void CKFileSystemRequestQueue::Enqueue(KRequest* request) { keCThreadPool::Enqueue(request); }

// 0x0004f360 CKFileSystemRequestQueue_Abort
void CKFileSystemRequestQueue::Abort() {
    RequestAbort();
    m_unkD1 = 1;
}

// 0x0004f320 CKFileSystemRequestQueue_JoinThreads
void CKFileSystemRequestQueue::JoinThreads() {
    keCThreadPool::JoinThreads();
    m_unkD0 = 1;
}
