// KFileSystem.cpp - reconstructed original translation unit 0x497a0-0x4a788 (GAME_TOC1, main_toc1), 17 functions, 17 live.
// Primary owner: KFileSystem (not a registered class)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x497a0  KFileSystem_ConvertBackslashes
//   [x] 0x497f0  KFileSystem_MakeRelativePath
//   [x] 0x498d8  KFileSystem_Destructor_2  (the second copy of KFileSystem_Destructor 0x49c78: ~KFileSystem)
//   [ ] 0x49978  KFileSystem_InitSaveDevice_maybe  [platform] by design: the PS3 save device set up (its vt+0x58 and root); stand-in in stubs/BootStubs.cpp
//   [x] 0x499b8  KFileSystem_Construct_2  (the second copy of KFileSystem_Construct 0x49d50: KFileSystem::KFileSystem)
//   [x] 0x49a40  KFileSystem_SplitPath
//   [x] 0x49b50  KFileSystem_GetBaseName
//   [x] 0x49bc8  KFileSystem_DeletingDestructor
//   [x] 0x49c78  KFileSystem_Destructor
//   [x] 0x49d18  KFileSystem_GetToolsPath
//   [x] 0x49d50  KFileSystem_Construct
//   [x] 0x49dd8  KFileSystem_CloseFile
//   [x] 0x49ee8  KFileSystem_BuildFullPath
//   [ ] 0x49ff8  KFileSystem_OpenFileAsync  [platform] by design: the PS3 save device asynchronous open (KFileDevice_OpenAndZeroFillAsync_maybe); no caller in the binary
//   [x] 0x4a288  KFileSystem_OpenFile
//   [ ] 0x4a638  KFileSystem_FileExists  [platform] by design: RtFS_FileExists under the open lock; the platform file layer (CinematicStreamFile.cpp RtFS_FileExists) answers it
//   [x] 0x4a780  KStub_Return0_4a780  (KMemoryStream's vt+0x40: IKFile::Flush's default 0)
#include "k2000/io/KFileSystem.h"

#include "Renderware/rwcore/RwStream.h"

#include <cstdio>
#include <cstring>

#include "k2000/io/KFileStream.h"
#include "k2000/io/KMemoryStream.h"
#include "k2000/core/Stub.h"
#include "k2000/io/IKFile.h"

// 0x000497a0 KFileSystem_ConvertBackslashes
void KFileSystem_ConvertBackslashes(KFileSystem* /*fileSystem*/, char* path) {
    for (char* p = std::strchr(path, '\\'); p != nullptr; p = std::strchr(p + 1, '\\')) *p = '/';
}

// 0x00049d50 KFileSystem_Construct: the mutex created, the nesting count 0, both paths emptied (their first bytes),
// no parked stream, the default save device, +0x43c = -2. (Created by CoreSingletons_Create.)
KFileSystem::KFileSystem() {
    // LwMutex_Create_2(+0x310): see m_mutexStorage.
    m_unk328 = 0;
    m_dataRoot[0] = 0;
    m_parkedStream = nullptr;
    m_executablePath[0] = 0;
    m_saveDevice = new KSaveDevice();  // OperatorNew(0x28) + KFileSystem_ConstructBase_maybe
    m_unk43c = -2;
    dotd::trace::Boot("create KFileSystem (core singleton)");  // trace only (not in the original)
}

// 0x00049c78 KFileSystem_Destructor: the save device's vt+0x5c (KFileSystem_SaveDevice_CallVf5C_maybe), the device
// deleted (vt+0x8c) and cleared, then the mutex destroyed.
KFileSystem::~KFileSystem() {
    if (m_saveDevice != nullptr) {
        m_saveDevice->Vf5C();
        if (m_saveDevice != nullptr) delete m_saveDevice;
        m_saveDevice = nullptr;
    }
}

// 0x00049ee8 KFileSystem_BuildFullPath
void KFileSystem::BuildFullPath(char* dst, const char* path, int32_t root) {
    const char* prefix = nullptr;
    if (std::strchr(path, ':') == nullptr) {
        if (root == kRootData) prefix = m_dataRoot;
        else if (root == kRootExecutable) prefix = m_executablePath;
    }
    // A path that already contains the root (strstr; an empty root is always "contained") is kept.
    if (prefix != nullptr && std::strstr(path, prefix) == nullptr) {
        std::strcpy(dst, prefix);
        std::strcat(dst, path);
    } else {
        std::strcpy(dst, path);
    }
    for (char* p = std::strchr(dst, '\\'); p != nullptr; p = std::strchr(p + 1, '\\')) *p = '/';
}

// 0x0004a288 KFileSystem_OpenFile. Devices 0/1 open a file stream, 3 a KMemoryStream over the KMemBuffer passed as
// `path` (any other device above 2 fails); device 2 is the save device (STUB(save data): KFileDevice_OpenAndZeroFill_maybe
// 0x4cee8 on +0x304 with `size` and `asyncFlags`).
IKFile* KFileSystem::OpenFile(const char* path, uint32_t openFlags, int32_t device, int32_t root, int32_t bindRw,
                               int32_t /*size*/, int32_t /*asyncFlags*/) {
    const bool named = device != kDeviceMemory;
    if (named && *path == 0) return nullptr;
    if (m_parkedStream != nullptr) return m_parkedStream;
    char fullPath[0x100];
    if (named) BuildFullPath(fullPath, path, root);
    if (openFlags >= 9) return nullptr;
    const uint32_t bit = 1u << openFlags;
    int32_t access;
    if ((bit & 0x111) != 0) access = 1;
    else if ((bit & 0x22) != 0) access = 2;
    else if ((bit & 0x44) != 0) access = 3;
    else return nullptr;

    IKFile* stream = nullptr;
    if (device == kDeviceSave) {
        return nullptr;  // STUB(save data): the save device (KFileDevice) is not ported
    }
    if (device < kDeviceSave) {
        if (device < 0) return nullptr;
        KFileStream* fileStream = new KFileStream();  // OperatorNew(0xf8) + KFileStream_Construct 0x4ba18
        IKFile_SetAccessMode(fileStream, access);
        // The original serialises opens through the lwmutex at +0x310 (nesting count +0x328).
        if ((fileStream->Open(fullPath, static_cast<int32_t>(openFlags)) & 0xff) == 0) {  // vt+0x00 (path, flags, asyncFlags)
            delete fileStream;  // vt+0x0c
            return nullptr;
        }
        stream = fileStream;
    } else {
        if (named) return nullptr;
        KMemoryStream* memoryStream = new KMemoryStream();  // OperatorNew(0x20) + KMemoryStream_Construct 0x4a858
        IKFile_SetAccessMode(memoryStream, access);
        // vt+0x00 KMemoryStream_Open (the unmodified path: the KMemBuffer; flags, asyncFlags).
        if ((memoryStream->Open(path, static_cast<int32_t>(openFlags)) & 0xff) == 0) {
            delete memoryStream;  // vt+0x0c
            return nullptr;
        }
        stream = memoryStream;
    }
    if (bindRw != 0) {
        // The original parks the stream at +0x308 and opens RwStream(rwSTREAMFILENAME, read, "ELB:") on
        // it (stream +4), through the jump table at 0x4a4d4; ElbFS_FileOpen takes the parked stream, so
        // the RW stream reads this IKFile (Renderware/rwcore/RwStream.h).
        stream->m_pRwStream = RwStreamOpenOnFile(stream);
    }
    return stream;
}

// 0x00049dd8 KFileSystem_CloseFile
int32_t KFileSystem::CloseFile(IKFile* stream) {
    if (stream->m_pRwStream != nullptr) {
        RwStreamClose(stream->m_pRwStream, nullptr);
        stream->m_pRwStream = nullptr;
    }
    const int32_t result = stream->Close();
    delete stream;  // vt+0x0c
    return result;
}

// C2.8 port-all P08: the path helpers (no caller in the remake yet: Texture_ReloadFromImageFile_maybe 0xc0700 and
// Raster_LoadMipLevelsFromFilesOrResample 0xa5f70 use SplitPath / GetBaseName; MakeRelativePath and GetToolsPath have no
// caller in the binary).

// 0x000497f0 KFileSystem_MakeRelativePath: `path` without its leading run of characters of the root's string (root 0
// the executable path, 1 the data root; strspn), or the whole path for another root.
void KFileSystem::MakeRelativePath(char* dst, const char* path, int32_t root) {
    if (root == kRootExecutable) {
        std::strcpy(dst, path + std::strspn(path, m_executablePath));
        return;
    }
    if (root != kRootData) {
        std::strcpy(dst, path);
        return;
    }
    std::strcpy(dst, path + std::strspn(path, m_dataRoot));
}

// 0x00049a40 KFileSystem_SplitPath: at the last '\\' the directory (with the separator) and the file name; without one
// no directory and the whole path as the name. Either output may be null.
void KFileSystem::SplitPath(char* directory, char* name, const char* path) {
    const char* last = std::strrchr(path, '\\');
    if (last == nullptr) {
        if (directory != nullptr) *directory = 0;
        if (name != nullptr) std::strcpy(name, path);
        return;
    }
    if (name != nullptr) std::strcpy(name, last + 1);
    if (directory != nullptr) {
        std::strcpy(directory, path);
        directory[(last + 1) - path] = 0;
    }
}

namespace {
// 0x000120e8 Path_GetFileNamePtr (misc/Str.cpp's row; a local copy): after the last '\', else after the last '/', else
// the whole path.
const char* FileNamePtr(const char* path) {
    const char* last = std::strrchr(path, '\\');
    if (last != nullptr ||(last = std::strrchr(path, '/')) != nullptr) return last + 1;
    return path;
}
}  // namespace

// 0x00049b50 KFileSystem_GetBaseName: the file name (Path_GetFileNamePtr: after the last '/' or '\\') without its last
// extension.
void KFileSystem::GetBaseName(const char* path, char* dst) {
    std::strcpy(dst, FileNamePtr(path));
    char* dot = std::strrchr(dst, '.');
    if (dot != nullptr && *dot != 0) *dot = 0;
}

// 0x00049d18 KFileSystem_GetToolsPath: "<executable path>Tools\\" (FormatString "%s%s").
void KFileSystem::GetToolsPath(char* dst) { std::sprintf(dst, "%s%s", m_executablePath, "Tools\\"); }
