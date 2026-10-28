// KRequest.h - asynchronous requests and the thread pool that runs them (k2000). Original unit:
// KRequest.cpp (0x573b0-0x58d68).
//
// A request is pushed onto a keCThreadPool (CKLoadRequestQueue, CKMemcardRequestQueue, ...). A worker
// thread pops it, marks it running, calls Execute and marks it done; the main thread polls
// IsFinished from the game loop. The pool keeps its requests as a stack: the newest is run first.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "platform/cell/sys_sync.h"

// vtable 0xb15510 (base 0xb15548). Size 0x60.
class KRequest {
public:
    enum State : int32_t { kIdle = 0, kQueued = 1, kRunning = 2, kDone = 3, kCancelled = 4 };

    KRequest();                       // 0x000574b0 KRequest_Construct
    virtual ~KRequest();              // vt+0x00 / +0x04
    virtual void Reset();             // vt+0x08 0x57c58 (every Post calls it before enqueueing)
    virtual void OnQueued() {}        // vt+0x0c 0x993bb8
    virtual void OnCancelled() {}     // vt+0x10 0x993bc0
    virtual void OnRunning() {}       // vt+0x14 0x993bc8
    virtual void Execute() = 0;       // vt+0x18 runs on the worker thread
    virtual void OnDone() {}          // vt+0x1c 0x993bd0
    virtual void SetQueued();         // vt+0x20 0x58010 OnQueued, state 1
    virtual void SetCancelled();      // vt+0x24 0x58130 OnCancelled, state 4, wake waiters
    virtual void SetRunning();        // vt+0x28 0x581c8 OnRunning, state 2
    virtual void SetDone();           // vt+0x2c 0x58098 OnDone, state 3, wake waiters

    // 0x00057978 KRequest_IsFinished: *succeeded = (state == 3); returns true for state 3 or 4.
    bool IsFinished(uint8_t* succeeded);
    // 0x00057a18 KRequest_Wait: blocks until the state is 3 or 4; *succeeded = (state == 3).
    void Wait(uint8_t* succeeded);

    KRequest* m_next;                 // +0x04 the next request in the pool's stack (constructor: null)
    int32_t m_state;                  // +0x08 State
    uint32_t m_unk0c;                 // +0x0c
    sys_lwmutex_t m_mutex;            // +0x10 LwMutex_Create
    uint8_t m_pad28[8];               // +0x28
    uint8_t m_condVar[0x30];          // +0x30 CondVar_Init (host: one shared condition variable, KRequest.cpp)
};

DOTD_ASSERT_SIZE(KRequest, 0x60);
DOTD_ASSERT_OFFSET(KRequest, m_state, 0x08);
DOTD_ASSERT_OFFSET(KRequest, m_mutex, 0x10);

// The worker pool (keCThreadPool, vtable 0xb15500 base). 0xd0 bytes; its owners add two bytes.
class keCThreadPool {
public:
    // 0x000585e8 keCThreadPool_Construct: threadCount workers named "<name> <i>".
    keCThreadPool(uint32_t threadCount, const char* name, int32_t priority);
    virtual ~keCThreadPool();

    void Enqueue(KRequest* request);  // 0x00057cb0 keCThreadPool_Enqueue
    void RequestAbort();              // 0x00057fa0 keCThreadPool_RequestAbort_maybe (cancels what is queued)
    void JoinThreads();               // joins the workers (KThreadSet)
    // Platform, not in the original: this pool's requests are waited for by KRequest::IsFinished in reproducible runs
    // (sys_thread.h SetDeterministicRequests). Only the load queue: a memcard request's work waits on the main thread.
    void SetWaitOnPoll();
    static void WorkerLoop(keCThreadPool* pool);  // 0x00058318 keCThreadPool_WorkerLoop_maybe

    struct HostSync;                  // platform equivalent of the pool's LwMutex and two CondVars
    HostSync* m_host;                 // +0x04 (host only; the PS3 objects live at +0x08..+0x98)
    uint8_t m_mutexStorage[0x18];     // +0x08 LwMutex
    KRequest* m_head;                 // +0x20 the request stack (KRequest +0x04 links it)
    int32_t m_activeWorkers;          // +0x24
    uint8_t m_pad28[8];
    uint8_t m_workCondVar[0x38];      // +0x30
    uint8_t m_idleCondVar[0x30];      // +0x68
    uint8_t m_abort;                  // +0x98
    uint8_t m_stopWhenIdle;           // +0x99
    uint8_t m_waitForWork;            // +0x9a constructor: 1
    uint8_t m_pad9b[5];
    uint8_t m_threadSet[0x30];        // +0xa0 KThreadSet (the workers' thread ids are kept host-side)
};
DOTD_ASSERT_SIZE(keCThreadPool, 0xd0);
DOTD_ASSERT_OFFSET(keCThreadPool, m_head, 0x20);
DOTD_ASSERT_OFFSET(keCThreadPool, m_abort, 0x98);
