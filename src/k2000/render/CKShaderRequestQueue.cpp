// CKShaderRequestQueue.cpp - reconstructed original translation unit 0x1011b0-0x1014a8 (GAME_TOC1, main_toc1), 8 functions, 8 live.
// Primary owner: CKShaderRequestQueue (not a registered class)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1011b0  CKShaderRequestQueue_JoinThreads
//   [x] 0x1011f0  CKShaderRequestQueue_Abort
//   [ ] 0x101228  CKShaderRequestQueue_CancelRequest_maybe  [platform]  (keCThreadPoolBase_CancelRequest_maybe for ShaderRequest_Cancel_maybe: the PS3 compile thread pool; nothing is enqueued, replaced by design: platform/gfx/cg_program translates the Cg programs to GLSL per variant)
//   [x] 0x101250  CKShaderRequestQueue_Enqueue_maybe
//   [x] 0x101278  CKShaderRequestQueue_Construct
//   [ ] 0x1012c0  CKShaderRequestQueue_Construct_2  [dead: no pointer to its descriptor 0xb57268, no call]
//   [ ] 0x101308  CKShaderRequestQueue_Destructor_2_maybe  [dead: no pointer to its descriptor 0xb57270, no call]
//   [x] 0x1013d8  CKShaderRequestQueue_Destructor_maybe
//
// 0x101228 CancelRequest (keCThreadPoolBase_CancelRequest_maybe 0x57af0) has no caller in the remake: nothing enqueues.
#include "k2000/render/CKShaderRequestQueue.h"

// 0x00101278 CKShaderRequestQueue_Construct
CKShaderRequestQueue::CKShaderRequestQueue()
    : keCThreadPool(1, "CKShaderRequestQueue", 1), m_unkD0(0), m_unkD1(0), m_padD2() {}

// 0x001013d8 CKShaderRequestQueue_Destructor_maybe: the abort requested unless it was, the workers joined unless they
// were, then the pool's destructor.
CKShaderRequestQueue::~CKShaderRequestQueue() {
    if (m_unkD1 == 0) {
        RequestAbort();
        m_unkD1 = 1;
    }
    if (m_unkD0 != 0) return;
    keCThreadPool::JoinThreads();
    m_unkD0 = 1;
}

// 0x00101250 CKShaderRequestQueue_Enqueue_maybe
void CKShaderRequestQueue::Enqueue(KRequest* request) { keCThreadPool::Enqueue(request); }

// 0x001011f0 CKShaderRequestQueue_Abort
void CKShaderRequestQueue::Abort() {
    RequestAbort();
    m_unkD1 = 1;
}

// 0x001011b0 CKShaderRequestQueue_JoinThreads
void CKShaderRequestQueue::JoinThreads() {
    keCThreadPool::JoinThreads();
    m_unkD0 = 1;
}
