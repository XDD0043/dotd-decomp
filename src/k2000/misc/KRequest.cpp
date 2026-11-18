// KRequest.cpp - reconstructed original translation unit 0x573b0-0x58d68 (GAME_TOC1, main_toc1), 40 functions, 39 live.
// Primary owner: KRequest (not a registered class)
// Other owners: Sema (4), PpuThread (2), Sys (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x573b0  keCThreadPoolBase_Destructor_maybe_2  (keCThreadPool's destructor (the base's part: its CondVars and LwMutex are the host sync, freed with it))
//   [x] 0x57418  keCThreadPoolBase_Construct_maybe  (keCThreadPool's constructor (the base's stores: head, active count, the three flags; LwMutex / CondVars the host sync))
//   [x] 0x574b0  KRequest_Construct
//   [x] 0x57518  KRequest_Destructor_2  (the same as 0x57760 KRequest_Destructor)
//   [x] 0x57578  keCThreadPoolBase_Construct_maybe_2  (the same stores as 0x57418 (keCThreadPool's constructor))
//   [x] 0x57610  KRequest_Construct_2  (the same stores as 0x574b0 KRequest_Construct)
//   [x] 0x57678  keCThreadPoolBase_DeletingDestructor_maybe  (the deleting form of keCThreadPool's destructor)
//   [x] 0x576f8  keCThreadPoolBase_Destructor_maybe  (keCThreadPool's destructor (the base's part))
//   [x] 0x57760  KRequest_Destructor
//   [x] 0x577c0  KRequest_DeletingDestructor
//   [ ] 0x57838  KRequest_WaitTimeout_maybe  [platform]  (a timed wait on the engine's semaphore CondVar (the timeout a spin count of sys_ppu_thread_yield): host condition variables by design; no caller in the original)
//   [x] 0x57978  KRequest_IsFinished
//   [x] 0x57a18  KRequest_Wait
//   [x] 0x57af0  keCThreadPoolBase_CancelRequest_maybe  (keCThreadPool::CancelRequest)
//   [x] 0x57c58  KRequest_Reset
//   [x] 0x57cb0  keCThreadPool_Enqueue
//   [ ] 0x57d58  keCThreadPool_WaitUntilIdleTimeout_maybe  [platform]  (a timed wait on the engine's semaphore CondVar (the timeout a spin count): host condition variables by design; no caller in the original)
//   [x] 0x57e90  keCThreadPoolBase_IsIdle_maybe  (keCThreadPool::IsIdle; no caller in the original either)
//   [x] 0x57f30  keCThreadPool_RequestStopWhenIdle_maybe  (keCThreadPool::RequestStopWhenIdle; no caller in the original either)
//   [x] 0x57fa0  keCThreadPool_RequestAbort_maybe
//   [x] 0x58010  KRequest_SetQueued
//   [x] 0x58098  KRequest_SetDone
//   [x] 0x58130  KRequest_SetCancelled
//   [x] 0x581c8  KRequest_SetRunning
//   [x] 0x58250  keCThreadPool_WaitUntilIdle_maybe  (keCThreadPool::WaitUntilIdle; no caller in the original either)
//   [x] 0x58318  keCThreadPool_WorkerLoop_maybe
//   [x] 0x585e0  keCThreadPool_WorkerLoop_maybe  (the same as 0x58318 keCThreadPool_WorkerLoop_maybe)
//   [x] 0x585e8  keCThreadPool_Construct
//   [x] 0x587d8  keCThreadPool_Construct_2  (the same as 0x585e8 keCThreadPool_Construct)
//   [x] 0x589c8  keCThreadPool_DeletingDestructor  (the deleting form of 0x58a68 keCThreadPool_Destructor)
//   [x] 0x58a68  keCThreadPool_Destructor
//   [x] 0x58af0  keCThreadPool_Destructor_2  (the same as 0x58a68 keCThreadPool_Destructor)
//   [ ] 0x58b78  Sema_Destroy_2  [platform]  (a PS3 semaphore syscall (sys_semaphore_destroy): host primitives by design)
//   [ ] 0x58b98  Sema_Wait  [platform]  (a PS3 semaphore syscall (sys_semaphore_wait; the CondVar layer's): host primitives by design)
//   [ ] 0x58bf0  Sema_TryWaitRetry_maybe  [platform]  (a spin wait on sys_ppu_thread_yield (the CondVar layer's): host primitives by design)
//   [ ] 0x58c78  Sema_Post  [platform]  (a PS3 semaphore syscall (sys_semaphore_post; the CondVar layer's): host primitives by design)
//   [ ] 0x58ca0  PpuThread_InvokeEntryFunc_maybe  [dead]
//   [ ] 0x58ce0  PpuThread_Join  [platform]  (sys_ppu_thread_join (KThreadSet, the particle scheduler's SPU threads): platform/cell/sys_thread)
//   [ ] 0x58d20  sys_ppu_thread_yield  [platform]  (the syscall sys_ppu_thread_yield: platform/cell/sys_thread)
//   [x] 0x58d40  Sys_UsleepMs_maybe
#include "k2000/misc/KRequest.h"

#include "k2000/core/Stub.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/Str.h"
#include "k2000/system/LwMutex.h"
#include "platform/cell/sys_thread.h"

#include <condition_variable>
#include <cstdio>
#include <mutex>
#include <set>
#include <vector>

// The requests' condition variable (+0x30, CondVar_Init/Broadcast/Wait) is one host condition variable
// shared by every request: KRequest_Wait's waiters re-check their own request's state when it is
// broadcast. The waiter holds g_waitMutex while it tests the state, and SetDone/SetCancelled take it
// after the state changes, so no broadcast is lost.
namespace {
std::mutex g_waitMutex;
std::condition_variable g_waitCondition;
void BroadcastRequestDone() {
    { std::lock_guard<std::mutex> lock(g_waitMutex); }
    g_waitCondition.notify_all();
}
// Platform (keCThreadPool::SetWaitOnPoll): the requests enqueued on a pool whose polls wait in reproducible runs.
std::mutex g_waitOnPollMutex;
std::set<const KRequest*> g_waitOnPoll;
bool WaitsOnPoll(const KRequest* request) {
    std::lock_guard<std::mutex> lock(g_waitOnPollMutex);
    return g_waitOnPoll.count(request) != 0;
}
}  // namespace

// 0x000574b0 KRequest_Construct (CondVar_Init: the host condition variable above).
KRequest::KRequest() : m_next(nullptr), m_state(kIdle), m_unk0c(0), m_pad28(), m_condVar() { LwMutex_Create(&m_mutex); }

// 0x00057760 KRequest_Destructor, 0x000577c0 KRequest_DeletingDestructor
KRequest::~KRequest() {
    {
        std::lock_guard<std::mutex> lock(g_waitOnPollMutex);  // platform (SetWaitOnPoll)
        g_waitOnPoll.erase(this);
    }
    LwMutex_Destroy(&m_mutex);
}

// 0x00057c58 KRequest_Reset
void KRequest::Reset() {
    LwMutex_Lock(&m_mutex);
    m_state = kIdle;
    LwMutex_Unlock(&m_mutex);
}

// 0x00057978 KRequest_IsFinished
bool KRequest::IsFinished(uint8_t* succeeded) {
    if (dotd::platform::DeterministicRequests() && WaitsOnPoll(this)) {
        // Platform, not in the original (sys_thread.h): a queued or running load request is waited for, so the poll's
        // answer does not depend on the worker thread's speed. An idle request (never posted) is answered as is.
        LwMutex_Lock(&m_mutex);
        const int32_t pending = m_state;
        LwMutex_Unlock(&m_mutex);
        if (pending == kQueued || pending == kRunning) {
            uint8_t ignored = 0;
            Wait(&ignored);
        }
    }
    LwMutex_Lock(&m_mutex);
    *succeeded = m_state == kDone ? 1 : 0;
    const int32_t state = m_state;
    LwMutex_Unlock(&m_mutex);
    return static_cast<uint32_t>(state - kDone) < 2u;
}

// 0x00057a18 KRequest_Wait
void KRequest::Wait(uint8_t* succeeded) {
    std::unique_lock<std::mutex> wait(g_waitMutex);
    LwMutex_Lock(&m_mutex);
    int32_t state = m_state;
    while (static_cast<uint32_t>(state - kDone) > 1u) {  // CondVar_WaitBegin, unlock, CondVar_WaitEnd, lock
        LwMutex_Unlock(&m_mutex);
        g_waitCondition.wait(wait);
        LwMutex_Lock(&m_mutex);
        state = m_state;
    }
    *succeeded = state == kDone ? 1 : 0;
    LwMutex_Unlock(&m_mutex);
}

// 0x00058010 KRequest_SetQueued
void KRequest::SetQueued() {
    LwMutex_Lock(&m_mutex);
    OnQueued();
    m_state = kQueued;
    LwMutex_Unlock(&m_mutex);
}

// 0x00058130 KRequest_SetCancelled
void KRequest::SetCancelled() {
    LwMutex_Lock(&m_mutex);
    OnCancelled();
    m_state = kCancelled;
    LwMutex_Unlock(&m_mutex);
    BroadcastRequestDone();  // CondVar_Broadcast
}

// 0x000581c8 KRequest_SetRunning
void KRequest::SetRunning() {
    LwMutex_Lock(&m_mutex);
    OnRunning();
    m_state = kRunning;
    LwMutex_Unlock(&m_mutex);
}

// 0x00058098 KRequest_SetDone
void KRequest::SetDone() {
    LwMutex_Lock(&m_mutex);
    OnDone();
    m_state = kDone;
    LwMutex_Unlock(&m_mutex);
    BroadcastRequestDone();  // CondVar_Broadcast
}

// 0x00058d40 Sys_UsleepMs_maybe
void Sys_UsleepMs(int32_t ms) { sys_timer_usleep(static_cast<uint64_t>(static_cast<uint32_t>(ms * 1000))); }

// ---- keCThreadPool -------------------------------------------------------------------------------
// The pool's LwMutex and its two CondVars are host primitives (platform equivalent of the engine's
// semaphore-based CondVar); the queue logic and the flags are the original's.
struct keCThreadPool::HostSync {
    std::mutex mutex;
    std::condition_variable work;   // +0x30 in the original
    std::condition_variable idle;   // +0x68
    std::vector<sys_ppu_thread_t> threads;
    bool waitOnPoll = false;  // SetWaitOnPoll
};

void keCThreadPool::SetWaitOnPoll() { m_host->waitOnPoll = true; }

namespace {
void WorkerEntry(uint64_t arg) { keCThreadPool::WorkerLoop(reinterpret_cast<keCThreadPool*>(static_cast<uintptr_t>(arg))); }
}  // namespace

// 0x000585e8 keCThreadPool_Construct
keCThreadPool::keCThreadPool(uint32_t threadCount, const char* name, int32_t priority)
    : m_host(new HostSync()),
      m_mutexStorage(),
      m_head(nullptr),
      m_activeWorkers(0),
      m_pad28(),
      m_workCondVar(),
      m_idleCondVar(),
      m_abort(0),
      m_stopWhenIdle(0),
      m_waitForWork(1),
      m_pad9b(),
      m_threadSet() {
    for (uint32_t i = 0; i < threadCount; ++i) {
        char* threadName = nullptr;
        Str_FormatAllocTo(&threadName, "%s %d", name, static_cast<int32_t>(i));  // 0x00011f90
        sys_ppu_thread_t id = 0;
        // KThread priority level -> PPU priority: RPCS3 shows 1002 for level 2 and 1001 for level 3.
        const int32_t ppuPriority = priority == 2 ? 1002 : 1001;
        sys_ppu_thread_create(&id, &WorkerEntry, static_cast<uint64_t>(reinterpret_cast<uintptr_t>(this)), ppuPriority,
                              0x10000, 1, threadName);
        m_host->threads.push_back(id);
        Mem_FreeAlignedAndNull(&threadName);  // 0x00011100
    }
}

// 0x00058a68 keCThreadPool_Destructor
keCThreadPool::~keCThreadPool() {
    RequestAbort();
    JoinThreads();
    delete m_host;
}

// 0x00057cb0 keCThreadPool_Enqueue: push onto the stack, mark queued, wake a worker.
void keCThreadPool::Enqueue(KRequest* request) {
    {
        std::lock_guard<std::mutex> lock(m_host->mutex);
        request->m_next = m_head;
        m_head = request;
        request->SetQueued();  // vt+0x20
    }
    if (m_host->waitOnPoll) {
        std::lock_guard<std::mutex> lock(g_waitOnPollMutex);
        g_waitOnPoll.insert(request);
    }
    m_host->work.notify_one();
}

// 0x00057fa0 keCThreadPool_RequestAbort_maybe
void keCThreadPool::RequestAbort() {
    {
        std::lock_guard<std::mutex> lock(m_host->mutex);
        m_abort = 1;
    }
    m_host->work.notify_all();
}

// 0x00057af0 keCThreadPoolBase_CancelRequest_maybe
void keCThreadPool::CancelRequest(KRequest* request) {
    std::lock_guard<std::mutex> lock(m_host->mutex);
    KRequest* head = m_head;
    if (head == nullptr) return;
    if (request == head) {
        m_head = request->m_next;
    } else {
        KRequest* node = head;
        do {
            node = node->m_next;
            if (node == nullptr) return;
        } while (request != node);
        KRequest* previous;
        node = head;
        do {
            previous = node;
            node = previous->m_next;
            if (node == nullptr) {  // not reached: the first walk found it
                request->SetCancelled();  // vt+0x24
                return;
            }
        } while (request != node);
        previous->m_next = request->m_next;
        if (request->m_next != nullptr) request->m_next = nullptr;
    }
    request->m_next = nullptr;
    request->SetCancelled();  // vt+0x24
}

// 0x00057e90 keCThreadPoolBase_IsIdle_maybe
bool keCThreadPool::IsIdle(uint8_t* notAborted) {
    std::lock_guard<std::mutex> lock(m_host->mutex);
    *notAborted = static_cast<uint8_t>(m_abort ^ 1);
    return m_activeWorkers == 0 && m_head == nullptr;
}

// 0x00057f30 keCThreadPool_RequestStopWhenIdle_maybe
void keCThreadPool::RequestStopWhenIdle() {
    {
        std::lock_guard<std::mutex> lock(m_host->mutex);
        m_stopWhenIdle = 1;
    }
    m_host->work.notify_all();  // CondVar_Broadcast(+0x30)
}

// 0x00058250 keCThreadPool_WaitUntilIdle_maybe
void keCThreadPool::WaitUntilIdle(uint8_t* notAborted) {
    std::unique_lock<std::mutex> lock(m_host->mutex);
    while (m_activeWorkers != 0 || m_head != nullptr) m_host->idle.wait(lock);  // CondVar +0x68
    *notAborted = static_cast<uint8_t>(m_abort ^ 1);
}

// The workers' KThreadSet join (CKLoadRequestQueue_JoinThreads and friends).
void keCThreadPool::JoinThreads() {
    for (sys_ppu_thread_t id : m_host->threads) sys_ppu_thread_join(id, nullptr);
    m_host->threads.clear();
}

// 0x00058318 keCThreadPool_WorkerLoop_maybe
void keCThreadPool::WorkerLoop(keCThreadPool* pool) {
    std::unique_lock<std::mutex> lock(pool->m_host->mutex);
    ++pool->m_activeWorkers;
    for (;;) {
        KRequest* request = pool->m_head;
        while (request == nullptr && pool->m_abort == 0 && pool->m_stopWhenIdle == 0 && pool->m_waitForWork != 0) {
            pool->m_host->work.wait(lock);
            request = pool->m_head;
        }
        if (pool->m_abort != 0) {
            // Cancel everything still queued.
            while (pool->m_head != nullptr) {
                KRequest* cancelled = pool->m_head;
                pool->m_head = cancelled->m_next;
                cancelled->m_next = nullptr;
                cancelled->SetCancelled();  // vt+0x24
            }
            break;
        }
        if (request == nullptr && (pool->m_stopWhenIdle != 0 || pool->m_waitForWork == 0)) break;
        // keCThreadPoolBase_PopRequest_maybe: take the newest request.
        pool->m_head = request->m_next;
        request->m_next = nullptr;
        lock.unlock();
        request->SetRunning();  // vt+0x28
        request->Execute();     // vt+0x18
        request->SetDone();     // vt+0x2c
        lock.lock();
    }
    if (--pool->m_activeWorkers == 0) pool->m_host->idle.notify_all();
}
