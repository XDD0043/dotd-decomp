// JobQueue.h - the game loop's job queue (0x268 bytes, GameEngineContext +0x7c). Original unit:
// JobQueue.cpp. Jobs are asynchronous system operations (save data, ...) whose completion callbacks
// run on the main thread at the start of a frame; while one is pending GameLoop shows a job message.
// The queue holds five jobs (a free list and a pending list in decreasing priority). Ported with the
// cinematic stream (package E3): its wait for the next segment is job 0xcb with a callback.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "platform/cell/sys_sync.h"

// A job's completion callback: called by ProcessCallbacks with the job's data and id; non-zero ends the job.
typedef uint8_t (*JobCallback)(void* callbackData, int32_t id, void* userData);

// A job (0x70 bytes).
struct Job {
    Job* m_pNext;               // +0x00 the list it is in (free or pending)
    uint32_t m_ui32Priority;    // +0x04 the byte posted; the constructor sets 0x7fffffff
    int32_t m_id;               // +0x08 -1 free
    void* m_pCallbackData;      // +0x0c
    JobCallback m_pfnCallback;  // +0x10 null: the job lives until the next purge
    void* m_pUserData;          // +0x14
    uint8_t m_bWaits;           // +0x18 posted from another thread than the main one: the poster waits
    uint8_t m_bDone;            // +0x19 the constructor sets 1; PostAndWait clears it
    uint8_t m_pad1a[6];
    sys_lwmutex_t m_mutex;      // +0x20 LwMutex_Create
    uint8_t m_pad38[8];
    uint8_t m_condVar[0x30];    // +0x40 CondVar_Init (host: one condition variable for all jobs, JobQueue.cpp)
};
DOTD_ASSERT_SIZE(Job, 0x70);

// 0x00023f00 Job_SignalDone_maybe: a waiting poster is woken (+0x19 set, the condition variable broadcast).
void Job_SignalDone(Job* job);

class JobQueue {
public:
    JobQueue();                       // 0x000245c0 JobQueue_Construct_maybe
    virtual ~JobQueue();              // 0x00024bc8 KStub_Nop_24bc8 is the engine's, not this

    // 0x000241c0 JobQueue_ProcessCallbacks_maybe: every pending job with a callback is called; those that answer
    // non-zero go back to the free list (id -1).
    void ProcessCallbacks();
    bool HasPending();                // 0x00024150 JobQueue_HasPending_maybe
    uint32_t PeekId();                // 0x000240a8 JobQueue_PeekId_maybe: the first pending job's id, 0xffffffff for none
    // 0x00023f80 JobQueue_PurgeWithoutCallback_maybe: the pending jobs without a callback go back to the free list.
    void PurgeWithoutCallback();
    // C1.6 gm: 0x00024318 JobQueue_PostAndWait_maybe: job `id` (priority order; -1 and, outside an active
    // mode, 500..503 ignored; an id already queued is not added; nothing when all five are pending) with an
    // optional callback; a caller on another thread waits for it (unless +0x260). Without a callback the job
    // lives until the next purge (one frame): GameLoop shows its message.
    void PostAndWait(int32_t id, uint32_t priority, void* callbackData, JobCallback callback, void* userData);
    // 0x000249c0 JobQueue_CancelJobById_maybe: the pending job `id` back to the free list, its poster woken.
    void CancelJobById(int32_t id);

    Job* m_pFree;                // +0x04
    Job* m_pPending;             // +0x08
    uint32_t m_pad0c;
    Job m_aJobs[5];              // +0x10
    uint8_t m_unk240;            // +0x240 the constructor sets 1
    uint8_t m_unk241;            // +0x241 1
    uint8_t m_unk242;            // +0x242 1
    uint8_t m_pad243[3];
    uint8_t m_unk246;            // +0x246 0
    uint8_t m_pad247;
    sys_lwmutex_t m_mutex;       // +0x248 the lists' lock
    uint8_t m_bNoWait;           // +0x260 0: posters on other threads wait
    uint8_t m_pad261[7];
};
DOTD_ASSERT_OFFSET(JobQueue, m_aJobs, 0x10);
DOTD_ASSERT_OFFSET(JobQueue, m_mutex, 0x248);
DOTD_ASSERT_OFFSET(JobQueue, m_bNoWait, 0x260);
DOTD_ASSERT_SIZE(JobQueue, 0x268);

class CKLocText;
class IKSerializable;

// MessageBox.cpp (system message boxes and the job messages drawn over the game).
void MessageBox_ClearJobMessageEntries();               // 0x000689a8 _maybe
void MessageBox_ProcessQueue();                         // 0x00068a70 _maybe
void MessageBox_PushJobMessageEntry(float alpha, uint32_t jobId);  // 0x00068510 _maybe
// 0x00c5c680 +0x40: number of job message entries (GameLoop's inhibit flag +0x1d).
int32_t MessageBox_GetJobMessageCount();
// 0x00068920 LocText_GetOrDefault_maybe: the loc text `id` once the boot loc data is loaded, else " ".
const uint16_t* LocText_GetOrDefault(uint32_t id);
// 0x00c5b92c +0xd50: number of queued message boxes (GameLoop's inhibit flag +0x1c).
int32_t MessageBox_GetQueuedCount();
// 0x00069358 MessageBox_Push_maybe: a message box request {text, buttons, default button, interrupt} queued for the Flash
// message box (the newest is processed first by MessageBox_ProcessQueue). With `sender` null only one is kept (a second
// push only refreshes the first one's start time). The caller polls the answer with MessageBox_TakeResult(sender).
// `x` and `y` are the callers' 1.0 / -1.0 (stored at +0x334 / +0x338: the timeout is y).
void MessageBox_Push(float x, float y, IKSerializable* sender, const CKLocText* text, int32_t combineType, int32_t defaultButton,
                     uint8_t (*interrupt)());
// 0x000695d0 MessageBox_Show_maybe: MessageBox_Push's request with the sender to be notified (message 0x2d00, data: the
// answer) once it is answered, instead of being polled. (With a null sender and one request queued, that one is refreshed.)
// `interrupt` (r7, stored at +0x330 like Push's): a poll that closes the box when it returns non-zero.
void MessageBox_Show(float x, float y, IKSerializable* sender, const CKLocText* text, int32_t combineType, int32_t defaultButton,
                     uint8_t (*interrupt)() = nullptr);
// 0x000685c8 MessageBox_TakeResult_maybe: the answer of the newest request of `sender` (the request leaves the queue once
// answered), or 0xb (pending / none).
int32_t MessageBox_TakeResult(const IKSerializable* sender);

// CKErrorTable (0xc bytes, vtable 0xb138b8, GameEngineContext +0xbc): one object per registered error class
// (category 14). Original unit: k2000/misc/CKErrorTable.cpp.
class CKErrorTable {
public:
    CKErrorTable();                   // 0x0001dbb0 CKErrorTable_Construct_maybe
    // vt+0x00 / +0x04 0x0001de90 CKErrorTable_Destructor / 0x0001de60 _DeletingDestructor: the root vtable only.
    virtual ~CKErrorTable();
    virtual int32_t Vf08() { return 0; }  // vt+0x08 0x990b00 KStub_Return0_990b00
    virtual void DestroyGame() {}         // vt+0x0c 0x990b08 KStub_Nop_990b08
    // vt+0x10 0x0001dc70 CKErrorTable_DestroyObjects_maybe (CKGameLoop_ShutdownSubsystems_maybe): every error object
    // deleted (ids 1..count), then the table.
    virtual void DestroyObjects();
    virtual void Vf14() {}
    virtual void Vf18() {}
    virtual void Vf1C() {}
    virtual void Vf20() {}
    // vt+0x24 0x0001dd30 CreateErrorObjects_maybe: a table of max id + 1 slots, slot id = an object of every
    // registered category-14 class id (from 1), null for the ids without a class.
    virtual void CreateErrorObjects();

    class IKBaseClass** m_ppObjects;  // +0x04 OperatorNewArray((max id + 1) * 4)
    uint32_t m_ui32MaxId;             // +0x08 ClassManager_GetMaxClassId(14)
};
