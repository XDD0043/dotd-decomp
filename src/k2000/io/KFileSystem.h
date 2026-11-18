// KFileSystem.h - the engine's file system front (size 0x458, constructor 0x49d50). Original unit:
// KFileSystem.cpp. Created by CoreSingletons_Create; GameEngineContext +0x30.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"

class IKFile;

// The save device KFileSystem_Construct creates (OperatorNew(0x28), vtable 0xb150d8; Ghidra Vt_b150d8_*, unit
// misc/Vt_3.cpp): the default device, whose slots are stubs (KStub_*), until KFileSystem_InitSaveDevice_maybe sets it
// up. Only the slots KFileSystem calls are declared (the PS3 slot of each in its comment).
class KSaveDevice {
public:
    KSaveDevice() {}                 // 0x0004c640 KFileSystem_ConstructBase_maybe: the vtable only
    virtual ~KSaveDevice() {}        // vt+0x88 / +0x8c 0x0004c8e0 / 0x0004c8b0 Vt_b150d8_Destructor_maybe / _Deleting..
    // vt+0x5c 0x0004c658 KStub_Return1_4c658 (KFileSystem_SaveDevice_CallVf5C_maybe 0x4c980 calls it): 1.
    virtual uint8_t Vf5C() { return 1; }
    // C2.8 port-rest R05: the slots the game manager's save-data checks call (BootLoad_InitSaveData_maybe 0x14698,
    // CDefaultGameManager_UpdateSaveDataFlow_maybe 0x18a80 and its states / message-box polls). The default device's:
    // vt+0x00 0x995988 KStub_Return1 (the device set up), vt+0x0c 0x4c6e8 KStub_Return0, vt+0x10 0x4c6f0 KStub_Return1
    // (a save device is present_maybe). Names ours.
    virtual uint8_t Vf00() { return 1; }
    virtual uint8_t Vf0C() { return 0; }
    virtual uint8_t Vf10() { return 1; }
    uint8_t m_pad04[0x24];           // +0x04 not modelled yet
};
DOTD_ASSERT_SIZE(KSaveDevice, 0x28);

class KFileSystem {
public:
    // Devices of OpenFile.
    enum Device : int32_t { kDeviceFile = 0, kDeviceDisc = 1, kDeviceSave = 2, kDeviceMemory = 3 };
    // Roots of BuildFullPath.
    enum Root : int32_t { kRootExecutable = 0, kRootData = 1, kRootNone = 2 };

    KFileSystem();                                    // 0x00049d50 KFileSystem_Construct
    virtual ~KFileSystem();                           // vt+0x00 / +0x04 0x00049c78 / 0x00049bc8

    void SetExecutablePath(const char* path);         // main: CopyString4Offset(fs, argv[0]) (0x49770, copies to +4)
    void SetDataRoot(const char* root);               // 0x000496c8 KFileSystem_SetDataRoot  STUB: plain copy
    void InitSaveDevice();                            // 0x00049978 KFileSystem_InitSaveDevice_maybe  STUB

    // 0x0004a288 KFileSystem_OpenFile. openFlags 0/4/8 read, 1/5 write, 2/6 read-write (access 1/2/3);
    // bindRw opens the RenderWare "ELB:" stream on the new stream. Returns null on failure.
    IKFile* OpenFile(const char* path, uint32_t openFlags, int32_t device, int32_t root, int32_t bindRw,
                      int32_t size, int32_t asyncFlags);
    // 0x00049dd8 KFileSystem_CloseFile: closes and deletes the stream.
    int32_t CloseFile(IKFile* stream);
    // 0x00049ee8 KFileSystem_BuildFullPath
    void BuildFullPath(char* dst, const char* path, int32_t root);
    // 0x000497f0 KFileSystem_MakeRelativePath (KFileSystem.cpp)
    void MakeRelativePath(char* dst, const char* path, int32_t root);
    // 0x00049a40 KFileSystem_SplitPath: at the last backslash; either output may be null.
    void SplitPath(char* directory, char* name, const char* path);
    // 0x00049b50 KFileSystem_GetBaseName: the file name without its extension.
    void GetBaseName(const char* path, char* dst);
    // 0x00049d18 KFileSystem_GetToolsPath: the executable path + "Tools\\".
    void GetToolsPath(char* dst);

    char m_executablePath[0x100];  // +0x004
    char m_dataRoot[0x200];        // +0x104 (live: "")
    KSaveDevice* m_saveDevice;     // +0x304 the save device (the constructor's default one)
    IKFile* m_parkedStream;       // +0x308 handed to the RenderWare "ELB:" file open
    uint8_t m_pad30c[4];           // +0x30c
    // +0x310 the LwMutex the opens are serialised with (LwMutex_Create_2 0x996538 in the constructor,
    // LwMutex_Destroy_Wrapper 0x996498 in the destructor): a PS3 system object; the remake's opens do not take it.
    uint8_t m_mutexStorage[0x18];
    int32_t m_unk328;              // +0x328 the constructor sets 0 (the lock's nesting count _maybe)
    uint8_t m_pad32c[0x110];       // +0x32c
    int32_t m_unk43c;              // +0x43c the constructor sets -2
    uint8_t m_pad440[0x18];        // +0x440
};
DOTD_ASSERT_SIZE(KFileSystem, 0x458);
DOTD_ASSERT_OFFSET(KFileSystem, m_dataRoot, 0x104);
DOTD_ASSERT_OFFSET(KFileSystem, m_saveDevice, 0x304);
DOTD_ASSERT_OFFSET(KFileSystem, m_unk328, 0x328);
DOTD_ASSERT_OFFSET(KFileSystem, m_unk43c, 0x43c);

// 0x000497a0 KFileSystem_ConvertBackslashes: '\' -> '/' in place.
void KFileSystem_ConvertBackslashes(KFileSystem* fileSystem, char* path);
