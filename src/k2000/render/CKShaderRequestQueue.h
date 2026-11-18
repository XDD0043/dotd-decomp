// CKShaderRequestQueue.h - the shader manager's request queue (CShaderManagerPSGL +0x8508, 0xd8 bytes): a thread pool
// of one "CKShaderRequestQueue" worker (priority 1). Original unit: CKShaderRequestQueue.cpp (0x1011b0-0x1014a8).
// Nothing enqueues on it in the remake (the shader programs are translated when they are first used), so its worker
// only waits until the exit aborts and joins it (CKGameLoop_ShutdownAndExit_maybe).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/KRequest.h"

class CKShaderRequestQueue : public keCThreadPool {
public:
    CKShaderRequestQueue();                   // 0x00101278 CKShaderRequestQueue_Construct
    ~CKShaderRequestQueue() override;         // 0x001013d8 CKShaderRequestQueue_Destructor_maybe
    void Enqueue(KRequest* request);          // 0x00101250 CKShaderRequestQueue_Enqueue_maybe
    // 0x001011f0 CKShaderRequestQueue_Abort: the pool's abort, then m_unkD1 set.
    void Abort();
    // 0x001011b0 CKShaderRequestQueue_JoinThreads: the workers joined (KThreadSet_JoinAll_maybe), then m_unkD0 set.
    void JoinThreads();

    uint8_t m_unkD0;     // +0xd0 the workers were joined (JoinThreads, the destructor)
    uint8_t m_unkD1;     // +0xd1 the abort was requested (Abort, the destructor)
    uint8_t m_padD2[6];
};
DOTD_ASSERT_SIZE(CKShaderRequestQueue, 0xd8);
