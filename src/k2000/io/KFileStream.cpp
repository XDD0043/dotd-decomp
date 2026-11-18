// KFileStream.cpp - the KP3 file stream (PS3 part) and the file tag of the save files.
//
// Reconstructed original translation unit: 0x4af28-0x4b688 (GAME_TOC1, main_toc1), 8 functions, 7 live.
// Primary owner: KFileStream (not a registered class)
// Other owners: IKFile (2), KFile (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x4af28  IKFile_ReadFileTag
//   [x] 0x4b0b0  IKFile_WriteFileTag
//   [ ] 0x4b380  KFileStream_OnAsyncOpenComplete_maybe  [platform] by design: the PS3 KFileStream over RtFS / cellFs; KFileStream.h / KFileStreamHost.cpp are the platform equivalent
//   [ ] 0x4b3a0  KStub_Nop_4b3a0  [dead]
//   [ ] 0x4b3a8  KFile_Exists  [platform] by design: the PS3 KFileStream over RtFS / cellFs; KFileStream.h / KFileStreamHost.cpp are the platform equivalent
//   [ ] 0x4b3e0  KFileStream_Close  [platform] by design: the PS3 KFileStream over RtFS / cellFs; KFileStream.h / KFileStreamHost.cpp are the platform equivalent
//   [ ] 0x4b508  KFileStream_PollAsyncDone  [platform] by design: the PS3 KFileStream over RtFS / cellFs; KFileStream.h / KFileStreamHost.cpp are the platform equivalent
//   [ ] 0x4b5d0  KFileStream_WaitAsyncDone  [platform] by design: the PS3 KFileStream over RtFS / cellFs; KFileStream.h / KFileStreamHost.cpp are the platform equivalent
#include "k2000/io/IKFile.h"
#include "k2000/io/KMemoryStream.h"

#include <cstring>

// C2.8 port-all P08: the file tag (no caller in the binary).
namespace {
const char kFileTagMagic[] = "12ta...reumb07i1";  // TOC -0x7410
}  // namespace

// 0x0004af28 IKFile_ReadFileTag
int32_t IKFile_ReadFileTag(IKFile* file, char* tag) {
    if (file == nullptr) return 1;
    char magic[0x18] = {};
    file->Seek(0x30, kSeekEnd);  // vt+0x2c
    file->Read(magic, 0x10);     // vt+0x14
    magic[0x10] = 0;
    if (std::strcmp(magic, kFileTagMagic) != 0) {
        *tag = 0;
        return 2;
    }
    char text[0x30] = {};
    file->Seek(0x20, kSeekEnd);
    file->Read(text, 0x20);
    text[0x20] = 0;
    std::strcpy(tag, text);
    tag[0x20] = 0;
    return 0;
}

// 0x0004b0b0 IKFile_WriteFileTag
int32_t IKFile_WriteFileTag(IKFile* file, const char* tag) {
    if (file == nullptr) return 1;
    const uint32_t length = static_cast<uint32_t>(std::strlen(tag));
    if (length > 0x20) return 5;
    char text[0x28] = {};
    if (length == 0x20) {
        std::strncpy(text, tag, 0x20);
    } else {
        const uint32_t pad = (0x20 - length) >> 1;
        for (uint32_t i = 0; i < pad; ++i) text[i] = ' ';
        std::strcpy(text + pad, tag);
        for (uint32_t i = length + pad; i < 0x20; ++i) text[i] = ' ';
    }
    text[0x20] = 0;
    FileTag_Encode(text);  // inlined in the original
    char magic[0x18] = {};
    file->Seek(0x30, kSeekEnd);
    file->Read(magic, 0x10);
    magic[0x10] = 0;
    if (std::strcmp(magic, kFileTagMagic) == 0) {
        file->Seek(0x20, kSeekEnd);
    } else {
        file->Seek(0, kSeekEnd);
        file->Write(kFileTagMagic, 0x10);  // vt+0x20
    }
    file->Write(text, 0x20);
    return 0;
}
