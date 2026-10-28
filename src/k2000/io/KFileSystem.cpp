// KFileSystem.cpp - reconstructed original translation unit 0x497a0-0x4a788 (GAME_TOC1, main_toc1), 17 functions, 17 live.
// Primary owner: KFileSystem (not a registered class)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x497a0  KFileSystem_ConvertBackslashes
//   [ ] 0x497f0  KFileSystem_MakeRelativePath
//   [ ] 0x498d8  KFileSystem_Destructor_2
//   [ ] 0x49978  KFileSystem_InitSaveDevice_maybe
//   [ ] 0x499b8  KFileSystem_Construct_2
//   [ ] 0x49a40  KFileSystem_SplitPath
//   [ ] 0x49b50  KFileSystem_GetBaseName
//   [ ] 0x49bc8  KFileSystem_DeletingDestructor
//   [ ] 0x49c78  KFileSystem_Destructor
//   [ ] 0x49d18  KFileSystem_GetToolsPath
//   [ ] 0x49d50  KFileSystem_Construct
//   [x] 0x49dd8  KFileSystem_CloseFile
//   [x] 0x49ee8  KFileSystem_BuildFullPath
//   [ ] 0x49ff8  KFileSystem_OpenFileAsync
//   [x] 0x4a288  KFileSystem_OpenFile
//   [ ] 0x4a638  KFileSystem_FileExists
//   [ ] 0x4a780  KStub_Return0_4a780
#include "k2000/io/KFileSystem.h"

#include "Renderware/rwcore/RwStream.h"

#include <cstring>

#include "k2000/io/KFileStream.h"
#include "k2000/io/IKFile.h"

// 0x000497a0 KFileSystem_ConvertBackslashes
void KFileSystem_ConvertBackslashes(KFileSystem* /*fileSystem*/, char* path) {
    for (char* p = std::strchr(path, '\\'); p != nullptr; p = std::strchr(p + 1, '\\')) *p = '/';
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

// 0x0004a288 KFileSystem_OpenFile (devices 0/1 and the access mapping ported; the save device, the
// memory stream and the RenderWare bind are STUB(C1.3 / save data)).
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
    if (device == kDeviceSave || device == kDeviceMemory || device < 0) {
        return nullptr;  // STUB(save data): KFileDevice and KMemoryStream are not ported yet
    }
    KFileStream* fileStream = new KFileStream();
    IKFile_SetAccessMode(fileStream, access);
    // The original serialises opens through the lwmutex at +0x310 (nesting count +0x328).
    if (fileStream->Open(fullPath, static_cast<int32_t>(openFlags)) == 0) {  // vt+0x00 (path, flags, asyncFlags)
        delete fileStream;  // vt+0x0c
        return nullptr;
    }
    stream = fileStream;
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
