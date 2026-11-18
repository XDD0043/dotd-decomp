// CKFileSystemRequestQueue.h - the host file system's request queue (KHostFS +0x20, 0xd8 bytes): a thread pool of one
// "CKFileSystemRequestQueue" worker (priority 2). Original unit: CKFileSystemRequestQueue.cpp (0x4f3c0-0x4f628); its
// Abort and JoinThreads (0x4f360 / 0x4f320) sit in KFileReadRequest.cpp's range. On the PS3 KHostFS_FileSync posts the
// RtFS reads to it; the remake's reads are synchronous (KHostFS is STUB(C1.2)), so its worker only waits until the exit
// aborts and joins it (CKGameLoop_ShutdownAndExit_maybe).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/KRequest.h"

class CKFileSystemRequestQueue : public keCThreadPool {
public:
    CKFileSystemRequestQueue();               // 0x0004f3e8 CKFileSystemRequestQueue_Construct
    ~CKFileSystemRequestQueue() override;     // 0x0004f548 CKFileSystemRequestQueue_Destructor
    void Enqueue(KRequest* request);          // 0x0004f3c0 CKFileSystemRequestQueue_Enqueue
    // 0x0004f360 CKFileSystemRequestQueue_Abort: the pool's abort, then m_unkD1 set.
    void Abort();
    // 0x0004f320 CKFileSystemRequestQueue_JoinThreads: the workers joined (KThreadSet_JoinAll_maybe), then m_unkD0 set.
    void JoinThreads();

    uint8_t m_unkD0;     // +0xd0 the workers were joined (JoinThreads, the destructor)
    uint8_t m_unkD1;     // +0xd1 the abort was requested (Abort, the destructor)
    uint8_t m_padD2[6];
};
DOTD_ASSERT_SIZE(CKFileSystemRequestQueue, 0xd8);
