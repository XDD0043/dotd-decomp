// RwStream.cpp - RenderWare 3.7 file streams and chunk headers (see RwStream.h).
#include "Renderware/rwcore/RwStream.h"

#include <cstring>
#include <new>

#include "k2000/io/IKFile.h"

namespace {
int32_t g_lastError = 0;

constexpr int32_t kStreamFilename = 2;
constexpr int32_t kStreamRead = 1;
constexpr int32_t kErrEndOfStream = 5;                       // E_RW_ENDOFSTREAM
constexpr int32_t kErrReadError = static_cast<int32_t>(0x8000001au);
constexpr int32_t kErrBadVersion = static_cast<int32_t>(0x80000004u);

void SetError(int32_t code) { g_lastError = code; }  // _rwerror + RwErrorSet

uint32_t LoadLE32(const uint8_t* b) {
    return static_cast<uint32_t>(b[0]) | (static_cast<uint32_t>(b[1]) << 8) | (static_cast<uint32_t>(b[2]) << 16) |
           (static_cast<uint32_t>(b[3]) << 24);
}
}  // namespace

int32_t RwShim_LastError() { return g_lastError; }

RwStream* RwStreamOpenOnFile(IKFile* file) {
    RwStream* stream = new RwStream();
    stream->type = kStreamFilename;
    stream->accessType = kStreamRead;
    stream->position = 0;
    stream->file = file;
    return stream;
}

// 0x0075c5f0 RwStreamClose
int32_t RwStreamClose(RwStream* stream, void* /*data*/) {
    delete stream;
    return 1;
}

// 0x0075cb70 RwStreamRead (the file branch: RtFS_FileRead through ElbFS, i.e. the IKFile)
uint32_t RwStreamRead(RwStream* stream, void* buffer, uint32_t length) {
    const uint32_t got = stream->file->Read(buffer, length);
    if (got == length) return got;
    SetError(stream->file->IsEOF() != 0 ? kErrEndOfStream : kErrReadError);
    return got;
}

// 0x0075c788 RwStreamSkip (the file branch: RtFS_FileSeek(fp, offset, CURRENT) through ElbFS_FileSeek)
RwStream* RwStreamSkip(RwStream* stream, uint32_t offset) {
    if (offset == 0) return stream;
    stream->file->Seek(static_cast<int32_t>(offset), kSeekCur);
    return stream;
}

// 0x00756808 _rwStreamReadChunkHeader
int32_t _rwStreamReadChunkHeader(RwStream* stream, uint32_t* type, uint32_t* length, uint32_t* version,
                                 uint32_t* buildNum) {
    uint8_t header[12];
    if (RwStreamRead(stream, header, 12) != 12) {
        SetError(kErrReadError);
        return 0;
    }
    const uint32_t chunkType = LoadLE32(header);
    const uint32_t chunkLength = LoadLE32(header + 4);
    const uint32_t libraryId = LoadLE32(header + 8);
    uint32_t chunkVersion = libraryId << 8;  // old-style id: the version only
    uint32_t chunkBuild = 0;
    if ((libraryId & 0xffff0000u) != 0) {
        chunkVersion = (((libraryId >> 14) & 0x3ff00u) + 0x30000u) | ((libraryId >> 16) & 0x3fu);
        chunkBuild = libraryId & 0xffffu;
    }
    if (type != nullptr) *type = chunkType;
    if (length != nullptr) *length = chunkLength;
    if (buildNum != nullptr) *buildNum = chunkBuild;
    if (version != nullptr) *version = chunkVersion;
    return 1;
}

// 0x007569d0 RwStreamReadChunkHeaderInfo
RwStream* RwStreamReadChunkHeaderInfo(RwStream* stream, RwChunkHeaderInfo* info) {
    uint32_t type = 0, length = 0, version = 0, build = 0;
    if (_rwStreamReadChunkHeader(stream, &type, &length, &version, &build) == 0) return nullptr;
    info->length = length;
    info->version = version;
    info->buildNum = build;
    info->type = type;
    // Complex chunk types: bit set in 0x415cfe0 for types below 0x1b.
    info->isComplex = type < 0x1b && ((0x415cfe0u >> type) & 1u) != 0 ? 1 : 0;
    return stream;
}

// 0x00756aa0 RwStreamFindChunk
int32_t RwStreamFindChunk(RwStream* stream, uint32_t type, uint32_t* lengthOut, uint32_t* versionOut) {
    uint32_t chunkType = 0, length = 0, version = 0;
    for (;;) {
        if (_rwStreamReadChunkHeader(stream, &chunkType, &length, &version, nullptr) == 0) return 0;
        if (chunkType == type) break;
        if (RwStreamSkip(stream, length) == nullptr) return 0;
    }
    if (version < 0x35000u || version > 0x37002u) {
        SetError(kErrBadVersion);
        return 0;
    }
    if (lengthOut != nullptr) *lengthOut = length;
    if (versionOut != nullptr) *versionOut = version;
    return 1;
}

RwShim_Blob* RwShim_ReadChunkBlob(RwStream* stream, uint32_t type) {
    uint32_t length = 0, version = 0;
    if (RwStreamFindChunk(stream, type, &length, &version) == 0) return nullptr;
    RwShim_Blob* blob = new RwShim_Blob();
    blob->type = type;
    blob->version = version;
    blob->length = length;
    blob->data = new uint8_t[length != 0 ? length : 1];
    RwStreamRead(stream, blob->data, length);
    return blob;
}

void RwShim_FreeBlob(RwShim_Blob* blob) {
    if (blob == nullptr) return;
    delete[] blob->data;
    delete blob;
}
