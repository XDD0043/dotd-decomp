// KHostFS.h - the host file system service (0x400180 bytes, aligned 0x40): RtFS on cellFs, the "ELB:"
// file system, the CKFileSystemRequestQueue thread. Original unit: KHostFS.cpp. Not an IKSerializable.
// STUB(C1.2): no RtFS and nothing posted to the request queue (+0x20); files are opened through the cellFs shims directly.
#pragma once
#include <cstdint>

#include "k2000/io/CKFileSystemRequestQueue.h"

class KHostFS {
public:
    KHostFS();
    virtual ~KHostFS();                    // vt+0x00 / +0x04
    virtual void Vf08() {}                 // vt+0x08
    virtual void DestroyGame() {}                 // vt+0x0c
    virtual void Init();                   // vt+0x10 KHostFS_Init -> KHostFS_InitFileSystems
    virtual void PreopenRwsFiles();        // vt+0x14 KHostFS_PreopenRwsFiles (boot load)
    virtual void PollDevice();             // vt+0x18 KHostFS_PollDevice_maybe (every frame)
    // vt+0x1c 0x00051020 KHostFS_CloseCachedFiles (CKGameLoop_ShutdownSubsystems_maybe): KHostFS_CloseRtFSManager_maybe
    // 0x51a08 (RtFS_ManagerClose, the RtFS and ELB: file system pointers +0x04 / +0x08 cleared), every cached file
    // descriptor of the +0x0c hash table closed (cellFsClose) and its node deleted, the table's count +0x10 = 0.
    // STUB(C1.2) with the rest of KHostFS: this stand-in opens no RtFS manager and caches no descriptor (the reads go
    // through KFileStreamHost.cpp), so there is nothing to close.
    virtual void CloseCachedFiles() {}
    // vt+0x20 0x4fd18 KFileLoader_IsReadComplete_maybe (CKGameLoop mode 6): the device present (KStub_Return1_519a8) and
    // the read request at +0x100 done (KFileReadRequest_Poll 0x4ef78 non-zero). The platform layer's reads are
    // synchronous (no request stays pending), so both answer yes: always complete.
    virtual uint8_t IsReadComplete() { return 1; }
    virtual uint8_t IsIdle();              // vt+0x24 0x4fcb0 KHostFS_vf24: no read request pending
    // C1.6 gm: vt+0x28 0x4fc48 KHostFS_PollReadRequest_maybe: IsIdle's body (KStub_Return1_519b8 for the
    // device test); GameLoop mode 9 waits on it.
    virtual uint8_t IsReadIdle();
    // 0x000519c8 KHostFS_GetDeviceState_maybe (not virtual): the RtFS file system's device state (RtFS_FileSystemGetDeviceState),
    // 2 without one (+0x04 null). The stand-in has no RtFS (see the top): 2, the PC's file system is always there.
    int32_t GetDeviceState() const { return 2; }

    // +0x20 the request queue (KHostFS_Construct 0x50248 constructs it; CKGameLoop_ShutdownAndExit_maybe aborts and joins
    // it; KHostFS_Destructor 0x515c0 destroys it). The fields before it (+0x04 RtFS, +0x08 ELB:, +0x0c the cached-fd
    // table) are the stand-in's (see the top).
    CKFileSystemRequestQueue m_requestQueue;
};

// 0x00051b50 KHostFS_Create
KHostFS* KHostFS_Create();
// 0x00051990 KHostFS_GetInstance: the host file system KHostFS_ConstructBase_maybe 0x51950 registered (0x00c5b840).
KHostFS* KHostFS_GetInstance();
