// KHostFS.h - the host file system service (0x400180 bytes, aligned 0x40): RtFS on cellFs, the "ELB:"
// file system, the CKFileSystemRequestQueue thread. Original unit: KHostFS.cpp. Not an IKSerializable.
// STUB(C1.2): no RtFS, no request thread; files are opened through the cellFs shims directly.
#pragma once
#include <cstdint>

class KHostFS {
public:
    KHostFS();
    virtual ~KHostFS();                    // vt+0x00 / +0x04
    virtual void Vf08() {}                 // vt+0x08
    virtual void DestroyGame() {}                 // vt+0x0c
    virtual void Init();                   // vt+0x10 KHostFS_Init -> KHostFS_InitFileSystems
    virtual void PreopenRwsFiles();        // vt+0x14 KHostFS_PreopenRwsFiles (boot load)
    virtual void PollDevice();             // vt+0x18 KHostFS_PollDevice_maybe (every frame)
    virtual void Vf1C() {}                 // vt+0x1c
    // vt+0x20 0x4fd18 KFileLoader_IsReadComplete_maybe (CKGameLoop mode 6). The remake's reads are
    // synchronous: always complete.
    virtual uint8_t IsReadComplete() { return 1; }
    virtual uint8_t IsIdle();              // vt+0x24 0x4fcb0 KHostFS_vf24: no read request pending
    // C1.6 gm: vt+0x28 0x4fc48 KHostFS_PollReadRequest_maybe: IsIdle's body (KStub_Return1_519b8 for the
    // device test); GameLoop mode 9 waits on it.
    virtual uint8_t IsReadIdle();
};

// 0x00051b50 KHostFS_Create
KHostFS* KHostFS_Create();
