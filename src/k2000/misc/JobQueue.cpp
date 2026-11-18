// JobQueue.cpp - reconstructed original translation unit 0x23ba8-0x24bd0 (GAME_TOC1, main_toc1), 15 functions, 13 live.
// Primary owner: JobQueue (not a registered class)
// Other owners: Job (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x23ba8  JobQueue_Destructor_maybe_2  (the same code as 0x248d0 JobQueue_Destructor_maybe)
//   [x] 0x23c98  JobQueue_Construct_maybe_2  (the same stores as 0x245c0 JobQueue_Construct_maybe)
//   [ ] 0x23ea0  FUN_00023ea0  [dead]
//   [x] 0x23f00  Job_SignalDone_maybe
//   [x] 0x23f80  JobQueue_PurgeWithoutCallback_maybe
//   [x] 0x240a8  JobQueue_PeekId_maybe
//   [x] 0x24150  JobQueue_HasPending_maybe
//   [x] 0x241c0  JobQueue_ProcessCallbacks_maybe
//   [x] 0x24318  JobQueue_PostAndWait_maybe
//   [x] 0x245c0  JobQueue_Construct_maybe
//   [x] 0x247c8  JobQueue_DeletingDestructor_maybe  (the deleting form of the destructor)
//   [x] 0x248d0  JobQueue_Destructor_maybe
//   [x] 0x249c0  JobQueue_CancelJobById_maybe
//   [ ] 0x24bc0  KStub_Nop_24bc0  [dead]
//   [x] 0x24bc8  KStub_Nop_24bc8  (empty (CoreSingletons_Destroy_maybe's call): nothing to call)
#include "k2000/misc/JobQueue.h"

#include <condition_variable>
#include <mutex>
#include <thread>

#include "k2000/core/Stub.h"
#include "k2000/misc/CKGameLoop.h"
#include "k2000/misc/Engine.h"
#include "k2000/system/LwMutex.h"

namespace {

// The jobs' condition variables (+0x40, CondVar_Init / CondVar_Broadcast / CondVar_WaitBegin+End) are one host
// condition variable for all the jobs (as KRequest.cpp's): a waiter re-checks its own job's done byte when it is
// broadcast; the waiter holds g_waitMutex while it tests, Job_SignalDone takes it after the byte is set.
std::mutex g_waitMutex;
std::condition_variable g_waitCondition;

// 0x00053680 KThread_IsCurrentMainThread_maybe: the KThread records are not ported; platform: the thread that made
// the queue (InitializeCKGameLoopSubsystems, the main thread).
std::thread::id g_mainThread;
bool IsCurrentMainThread() { return std::this_thread::get_id() == g_mainThread; }

// A job out of the pending list (the inlined list removal: the job's link cleared when it had one).
void Unlink(Job** head, Job* job) {
    Job* node = *head;
    if (node == nullptr) return;
    if (node == job) {
        *head = job->m_pNext;
    } else {
        Job* previous;
        do {
            previous = node;
            node = node->m_pNext;
            if (node == nullptr) return;
        } while (node != job);
        previous->m_pNext = job->m_pNext;
        if (job->m_pNext != nullptr) job->m_pNext = nullptr;
    }
    job->m_pNext = nullptr;
}

}  // namespace

// 0x000245c0 JobQueue_Construct_maybe
JobQueue::JobQueue() {
    dotd::trace::Boot("create JobQueue");
    g_mainThread = std::this_thread::get_id();
    m_pFree = nullptr;
    m_pPending = nullptr;
    m_pad0c = 0;
    for (Job& job : m_aJobs) {
        job.m_pNext = nullptr;
        job.m_ui32Priority = 0x7fffffff;
        LwMutex_Create(&job.m_mutex);
        // CondVar_Init(+0x40): the host condition variable above.
    }
    LwMutex_Create(&m_mutex);
    m_bNoWait = 0;
    m_unk240 = 1;
    m_unk241 = 1;
    m_unk242 = 1;
    m_unk246 = 0;
    for (Job& job : m_aJobs) {
        job.m_id = -1;
        job.m_bDone = 1;
        job.m_pNext = m_pFree;
        m_pFree = &job;
    }
}

// 0x000248d0 JobQueue_Destructor_maybe (0x247c8 deleting, 0x23ba8 the same code): the lists cleared, the queue's LwMutex
// and the jobs' (last first) destroyed; their CondVars are the host one (CondVar_Destroy: nothing to do).
JobQueue::~JobQueue() {
    m_pPending = nullptr;
    m_pFree = nullptr;
    LwMutex_Destroy(&m_mutex);
    for (int32_t i = 4; i >= 0; --i) LwMutex_Destroy(&m_aJobs[i].m_mutex);
}

// 0x00023f00 Job_SignalDone_maybe
void Job_SignalDone(Job* job) {
    if (job->m_bWaits == 0) return;
    LwMutex_Lock(&job->m_mutex);
    job->m_bDone = 1;
    LwMutex_Unlock(&job->m_mutex);
    { std::lock_guard<std::mutex> lock(g_waitMutex); }
    g_waitCondition.notify_all();  // CondVar_Broadcast(+0x40)
}

// 0x00024150 JobQueue_HasPending_maybe
bool JobQueue::HasPending() {
    LwMutex_Lock(&m_mutex);
    Job* pending = m_pPending;
    LwMutex_Unlock(&m_mutex);
    return pending != nullptr;
}

// 0x000240a8 JobQueue_PeekId_maybe
uint32_t JobQueue::PeekId() {
    LwMutex_Lock(&m_mutex);
    if (m_pPending == nullptr) {
        LwMutex_Unlock(&m_mutex);
        return 0xffffffffu;
    }
    const uint32_t id = static_cast<uint32_t>(m_pPending->m_id);
    LwMutex_Unlock(&m_mutex);
    return id;
}

// 0x000241c0 JobQueue_ProcessCallbacks_maybe (the callbacks run with the queue locked).
void JobQueue::ProcessCallbacks() {
    LwMutex_Lock(&m_mutex);
    Job* next = m_pPending;
    while (next != nullptr) {
        Job* job = next;
        next = job->m_pNext;
        if (job->m_pfnCallback == nullptr) continue;
        if (job->m_pfnCallback(job->m_pCallbackData, job->m_id, job->m_pUserData) == 0) continue;
        Unlink(&m_pPending, job);
        job->m_id = -1;
        job->m_pNext = m_pFree;
        m_pFree = job;
    }
    LwMutex_Unlock(&m_mutex);
}

// 0x00023f80 JobQueue_PurgeWithoutCallback_maybe
void JobQueue::PurgeWithoutCallback() {
    LwMutex_Lock(&m_mutex);
    Job* next = m_pPending;
    while (next != nullptr) {
        Job* job = next;
        next = job->m_pNext;
        if (job->m_pfnCallback != nullptr) continue;
        Unlink(&m_pPending, job);
        job->m_id = -1;
        job->m_pNext = m_pFree;
        m_pFree = job;
    }
    LwMutex_Unlock(&m_mutex);
}

// 0x00024318 JobQueue_PostAndWait_maybe
void JobQueue::PostAndWait(int32_t id, uint32_t priority, void* callbackData, JobCallback callback, void* userData) {
    if (id == -1) return;
    if (g_pEngine->m_gameLoop->IsActiveModeWithGmVfC0() == 0 && static_cast<uint32_t>(id - 500) < 4) return;
    LwMutex_Lock(&m_mutex);
    for (Job* job = m_pPending; job != nullptr; job = job->m_pNext) {
        if (job->m_id == id) {
            LwMutex_Unlock(&m_mutex);
            return;
        }
    }
    Job* job = m_pFree;
    if (job == nullptr) {
        LwMutex_Unlock(&m_mutex);
        return;
    }
    if (job->m_pNext == nullptr) {
        m_pFree = nullptr;
    } else {
        m_pFree = job->m_pNext;
        job->m_pNext = nullptr;
    }
    job->m_ui32Priority = priority & 0xff;
    job->m_id = id;
    job->m_pCallbackData = callbackData;
    job->m_pfnCallback = callback;
    job->m_pUserData = userData;
    LwMutex_Lock(&job->m_mutex);
    job->m_bDone = 0;
    LwMutex_Unlock(&job->m_mutex);
    job->m_bWaits = IsCurrentMainThread() ? 0 : 1;
    // The pending list in decreasing priority: behind the last job of a higher priority, else at the head.
    Job* head = m_pPending;
    if (head != nullptr && job->m_ui32Priority < head->m_ui32Priority) {
        Job* previous;
        Job* node = head;
        do {
            previous = node;
            node = previous->m_pNext;
        } while (node != nullptr && job->m_ui32Priority < node->m_ui32Priority);
        job->m_pNext = previous->m_pNext;
        previous->m_pNext = job;
    } else {
        job->m_pNext = m_pPending;
        m_pPending = job;
    }
    LwMutex_Unlock(&m_mutex);
    if (m_bNoWait != 0 || job->m_bWaits == 0) return;
    std::unique_lock<std::mutex> wait(g_waitMutex);
    LwMutex_Lock(&job->m_mutex);
    while (job->m_bDone == 0) {  // CondVar_WaitBegin, unlock, CondVar_WaitEnd, lock
        LwMutex_Unlock(&job->m_mutex);
        g_waitCondition.wait(wait);
        LwMutex_Lock(&job->m_mutex);
    }
    LwMutex_Unlock(&job->m_mutex);
}

// 0x000249c0 JobQueue_CancelJobById_maybe
void JobQueue::CancelJobById(int32_t id) {
    if (id == -1) return;
    LwMutex_Lock(&m_mutex);
    Job* job = m_pPending;
    while (job != nullptr && job->m_id != id) job = job->m_pNext;
    LwMutex_Unlock(&m_mutex);
    if (job == nullptr) return;
    LwMutex_Lock(&m_mutex);
    Unlink(&m_pPending, job);
    job->m_id = -1;
    job->m_pNext = m_pFree;
    m_pFree = job;
    LwMutex_Unlock(&m_mutex);
    if (job->m_bWaits == 0) return;
    LwMutex_Lock(&job->m_mutex);
    job->m_bDone = 1;
    LwMutex_Unlock(&job->m_mutex);
    { std::lock_guard<std::mutex> lock(g_waitMutex); }
    g_waitCondition.notify_all();
}
