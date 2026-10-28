// KFileSystem.h - the engine's file system front (size 0x458, constructor 0x49d50). Original unit:
// KFileSystem.cpp. Created by CoreSingletons_Create; GameEngineContext +0x30.
#pragma once
#include <cstdint>

class IKFile;

class KFileSystem {
public:
    // Devices of OpenFile.
    enum Device : int32_t { kDeviceFile = 0, kDeviceDisc = 1, kDeviceSave = 2, kDeviceMemory = 3 };
    // Roots of BuildFullPath.
    enum Root : int32_t { kRootExecutable = 0, kRootData = 1, kRootNone = 2 };

    KFileSystem();                                    // 0x00049d50 KFileSystem_Construct  STUB(C1.2): fields only
    virtual ~KFileSystem();

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

    char m_executablePath[0x100];  // +0x004
    char m_dataRoot[0x200];        // +0x104 (live: "")
    void* m_saveDevice;            // +0x304 KFileDevice (STUB)
    IKFile* m_parkedStream;       // +0x308 handed to the RenderWare "ELB:" file open
    uint8_t m_pad30c[0x1c];        // +0x30c lwmutex at +0x310, nesting count at +0x328 (not needed yet)
};

// 0x000497a0 KFileSystem_ConvertBackslashes: '\' -> '/' in place.
void KFileSystem_ConvertBackslashes(KFileSystem* fileSystem, char* path);
