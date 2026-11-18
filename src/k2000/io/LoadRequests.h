// LoadRequests.h - the requests and queues CKGameLoop embeds. Original units: GameLevelLoadRequest.cpp,
// ui/LocLoadRequest.cpp, BootLoadRequest.cpp (with CKLoadRequestQueue), SaveDataRequest.cpp (with
// CKMemcardRequestQueue).
//
// Post resets the request, stores its arguments, enqueues it and sets m_posted; CheckDone returns 1 once
// the worker has finished it and clears m_posted. The Execute bodies are the original's, except BootLoadRequest's:
// STUB(C1.2): 0x34388 BootLoadRequest_Execute_maybe is a stand-in (BootStubs.cpp); it runs KHostFS_PreopenRwsFiles
// (vt+0x14, the RtFS host file system), BootLoad_InitSaveData_maybe 0x14698 (save data) and
// CShaderManagerPSGL_LoadShaderCacheFile_maybe 0xfbad0 (the Cg shader cache).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/KRequest.h"

// "CKLoadRequestQueue 0" thread (prio 1002): loads GAME.KP3, levels, sectors, loc files, boot data.
class CKLoadRequestQueue : public keCThreadPool {
public:
    CKLoadRequestQueue();                       // 0x00034770 CKLoadRequestQueue_Construct
    ~CKLoadRequestQueue() override;             // 0x000348d0 CKLoadRequestQueue_Destructor_maybe
    void Enqueue(KRequest* request);            // 0x000346b0 CKLoadRequestQueue_Enqueue
    // 0x00034650 CKLoadRequestQueue_Abort: the pool's abort, then m_unkD1 set.
    void Abort() {
        RequestAbort();
        m_unkD1 = 1;
    }
    // 0x00034610 CKLoadRequestQueue_JoinThreads: the workers joined (KThreadSet_JoinAll_maybe), then m_unkD0 set.
    void JoinThreads() {
        keCThreadPool::JoinThreads();
        m_unkD0 = 1;
    }
    uint8_t m_unkD0;                            // +0xd0 the workers were joined (JoinThreads, the destructor)
    uint8_t m_unkD1;                            // +0xd1 the abort was requested (Abort, the destructor)
    uint8_t m_padD2[6];
};
DOTD_ASSERT_SIZE(CKLoadRequestQueue, 0xd8);

// "CKMemcardRequestQueue::keCThreadPool 0" thread (prio 1001): save data.
class CKMemcardRequestQueue : public keCThreadPool {
public:
    CKMemcardRequestQueue();                    // 0x0002b600 CKMemcardRequestQueue_Construct
    ~CKMemcardRequestQueue() override;          // 0x0002b760 CKMemcardRequestQueue_Destructor_maybe
    // CKMemcardRequestQueue_Abort / _JoinThreads: as CKLoadRequestQueue's (the flags +0xd1 / +0xd0).
    void Abort() {
        RequestAbort();
        m_unkD1 = 1;
    }
    void JoinThreads() {
        keCThreadPool::JoinThreads();
        m_unkD0 = 1;
    }
    uint8_t m_unkD0;                            // +0xd0 the workers were joined
    uint8_t m_unkD1;                            // +0xd1 the abort was requested
    uint8_t m_padD2[6];
};
DOTD_ASSERT_SIZE(CKMemcardRequestQueue, 0xd8);

// vtable 0xb14260. Size 0x70.
class GameLevelLoadRequest : public KRequest {
public:
    enum Kind : int32_t { kGameFile = 1, kLevel = 2 };

    GameLevelLoadRequest();                     // 0x00033dc0 GameLevelLoadRequest_Construct
    void Reset() override;                      // vt+0x08 0x33be0
    void Execute() override;                    // vt+0x18 0x33e60
    void Post(int32_t kind, int32_t level);     // 0x00033c88 GameLevelLoadRequest_Post
    int32_t CheckDone();                        // 0x00033c20 GameLevelLoadRequest_CheckDone
    void RunSync(int32_t kind);                 // 0x00033ee0 GameLevelLoadRequest_RunSync (no caller)

    uint8_t m_posted;     // +0x60
    uint8_t m_pad61[3];
    int32_t m_kind;       // +0x64
    int32_t m_level;      // +0x68 -1 after completion
    uint8_t m_pad6c[4];
};
DOTD_ASSERT_SIZE(GameLevelLoadRequest, 0x70);
DOTD_ASSERT_OFFSET(GameLevelLoadRequest, m_posted, 0x60);
DOTD_ASSERT_OFFSET(GameLevelLoadRequest, m_level, 0x68);

// vtable 0xb14298. Size 0x68.
class LocLoadRequest : public KRequest {
public:
    enum Kind : int32_t { kDefaultAndSystemLanguage = 1, kLevel = 2, kChangeLanguage = 3 };  // 3: C1.6 gm (GameLoop mode 3)

    LocLoadRequest();                           // 0x00034198 LocLoadRequest_Construct
    void Reset() override;                      // vt+0x08 0x33f80
    void Execute() override;                    // vt+0x18 0x34228
    void Post(int32_t kind);                    // 0x00034070 LocLoadRequest_Post
    int32_t CheckDone();                        // 0x00033fb8 LocLoadRequest_CheckDone

    uint8_t m_posted;     // +0x60
    uint8_t m_pad61[3];
    int32_t m_kind;       // +0x64
};
DOTD_ASSERT_SIZE(LocLoadRequest, 0x68);

// vtable 0xb142d0. Size 0x68.
class BootLoadRequest : public KRequest {
public:
    BootLoadRequest();                          // 0x00034590 BootLoadRequest_Construct_maybe
    void Reset() override;                      // vt+0x08 0x343f0
    void Execute() override;                    // vt+0x18 0x34388 BootLoadRequest_Execute_maybe
    void Post();                                // 0x00034478 BootLoadRequest_Post_maybe
    int32_t CheckDone();                        // 0x00034418 BootLoadRequest_CheckDone_maybe

    uint8_t m_posted;     // +0x60
    uint8_t m_pad61[7];
};
DOTD_ASSERT_SIZE(BootLoadRequest, 0x68);

// Size 0x68. STUB(save data).
class SaveDataRequest : public KRequest {
public:
    enum Kind : int32_t { kListSave = 0, kListLoad = 1, kDelete = 2, kListAutoLoad = 3 };
    SaveDataRequest();                          // 0x0002b4c8 SaveDataRequest_Construct
    void Execute() override;                    // 0x0002b2d0 SaveDataRequest_Execute (worker thread)
    void Post(int32_t kind);                    // 0x0002b3a8 SaveDataRequest_Post
    uint8_t CheckDone();                        // 0x0002b370 SaveDataRequest_CheckDone: finished successfully
    void SettleForReplay();                     // platform (replays): past Execute, the done state waited for
    int32_t m_kind;                             // +0x60 Kind
    uint8_t m_pad64[4];
};
DOTD_ASSERT_SIZE(SaveDataRequest, 0x68);
