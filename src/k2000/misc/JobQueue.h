// JobQueue.h - the game loop's job queue (0x268 bytes, GameEngineContext +0x7c). Original unit:
// JobQueue.cpp. Jobs are asynchronous system operations (save data, ...) whose completion callbacks
// run on the main thread at the start of a frame; while one is pending GameLoop shows a job message.
// STUB(save data): the queue is always empty.
#pragma once
#include <cstdint>

class JobQueue {
public:
    JobQueue();                       // 0x000245c0 JobQueue_Construct_maybe
    virtual ~JobQueue();              // 0x00024bc8 KStub_Nop_24bc8 is the engine's, not this

    void ProcessCallbacks();          // 0x000241c0 JobQueue_ProcessCallbacks_maybe
    bool HasPending();                // 0x00024150 JobQueue_HasPending_maybe
    uint32_t PeekId();                // 0x000240a8 JobQueue_PeekId_maybe
    void PurgeWithoutCallback();      // 0x00023f80 JobQueue_PurgeWithoutCallback_maybe
    // C1.6 gm: 0x00024318 JobQueue_PostAndWait_maybe: job `id` (priority order; -1 and, outside an active
    // mode, 500..503 ignored; an id already queued is not added) with an optional callback; a caller on
    // another thread waits for it. Without a callback the job lives until the next purge (one frame):
    // GameLoop shows its message. STUB(save data) with the queue.
    void PostAndWait(int32_t id, uint32_t priority, void* callbackData, const void* callback, void* userData);
};

class CKLocText;
class IKSerializable;

// MessageBox.cpp (system message boxes drawn over the game). STUB(C1.6).
void MessageBox_ClearJobMessageEntries();               // 0x000689a8 _maybe
void MessageBox_ProcessQueue();                         // 0x00068a70 _maybe
void MessageBox_PushJobMessageEntry(float alpha, uint32_t jobId);  // 0x00068510 _maybe
// 0x00c5c680 +0x40: number of job message entries (GameLoop's inhibit flag +0x1d).
int32_t MessageBox_GetJobMessageCount();
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
void MessageBox_Show(float x, float y, IKSerializable* sender, const CKLocText* text, int32_t combineType, int32_t defaultButton);
// 0x000685c8 MessageBox_TakeResult_maybe: the answer of the newest request of `sender` (the request leaves the queue once
// answered), or 0xb (pending / none).
int32_t MessageBox_TakeResult(const IKSerializable* sender);

// CKErrorTable (0xc bytes, GameEngineContext +0xbc): one object per registered error class.
class CKErrorTable {
public:
    CKErrorTable();                   // 0x0001dbb0 CKErrorTable_Construct_maybe
    virtual ~CKErrorTable();
    virtual void Vf08() {}
    virtual void DestroyGame() {}
    virtual void Vf10() {}
    virtual void Vf14() {}
    virtual void Vf18() {}
    virtual void Vf1C() {}
    virtual void Vf20() {}
    virtual void CreateErrorObjects();  // vt+0x24 0x1dd30 CreateErrorObjects_maybe
};
