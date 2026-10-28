// RwStream.h - RenderWare 3.7 binary streams as the game reads them: stream read/skip/close and the
// chunk headers. Ported from the PS3 library code (TOC 0xc25974):
//   RwStreamRead 0x75cb70, RwStreamSkip 0x75c788, RwStreamClose 0x75c5f0,
//   _rwStreamReadChunkHeader 0x756808, RwStreamReadChunkHeaderInfo 0x7569d0, RwStreamFindChunk 0x756aa0.
//
// The game opens these streams as rwSTREAMFILENAME "ELB:" files: RtFS with the ElbFS device (0x5ac10),
// which takes the IKFile parked at KFileSystem +0x308 (ElbFS_FileOpen 0x5af30) and reads, seeks and
// tells through it. So an RW stream and its IKFile share one position. Here the stream reads its IKFile
// directly: the same bytes from the same position. Only the file stream type is needed so far.
#pragma once
#include <cstdint>

class IKFile;

// RW 3.7 RwStream for the file types; the PS3 build keeps no position count for file streams.
struct RwStream {
    int32_t type;       // +0x00 rwSTREAMFILENAME (2)
    int32_t accessType; // +0x04 rwSTREAMREAD (1)
    int32_t position;   // +0x08 (memory streams only)
    IKFile* file;       // +0x0c the ELB: file (RW: Type.file.fpFile, here the IKFile it reads through)
};

// RwChunkHeaderInfo (RW 3.7).
struct RwChunkHeaderInfo {
    uint32_t type;
    uint32_t length;
    uint32_t version;
    uint32_t buildNum;
    int32_t isComplex;
};

// Stands for RwStreamOpen(rwSTREAMFILENAME, rwSTREAMREAD, "ELB:...") with the file parked in KFileSystem
// (KFileSystem_OpenFile with bindRw).
RwStream* RwStreamOpenOnFile(IKFile* file);
// 0x0075c5f0: frees the stream (the IKFile stays open; KFileSystem closes it).
int32_t RwStreamClose(RwStream* stream, void* data);
// 0x0075cb70: the bytes read. A short read sets E_RW_ENDOFSTREAM (5) at the end of the file, otherwise
// 0x8000001a, and returns the count.
uint32_t RwStreamRead(RwStream* stream, void* buffer, uint32_t length);
// 0x0075c788: null on failure.
RwStream* RwStreamSkip(RwStream* stream, uint32_t offset);
// 0x00756808: reads the 12-byte header {type, length, libraryID} (little-endian) and decodes the version
// from the library id. 0 (error 0x8000001a) when 12 bytes could not be read. Null outputs are skipped.
int32_t _rwStreamReadChunkHeader(RwStream* stream, uint32_t* type, uint32_t* length, uint32_t* version,
                                 uint32_t* buildNum);
// 0x007569d0
RwStream* RwStreamReadChunkHeaderInfo(RwStream* stream, RwChunkHeaderInfo* info);
// 0x00756aa0: reads headers, skipping every chunk of another type, until one of the requested type; then
// checks its version (0x35000..0x37002; otherwise error 0x80000004 and 0). 1 = found (length/version out).
int32_t RwStreamFindChunk(RwStream* stream, uint32_t type, uint32_t* lengthOut, uint32_t* versionOut);

// The last RenderWare error code (_rwerror + RwErrorSet); nothing reads it during loading.
int32_t RwShim_LastError();

// DEV (C1.3): a chunk kept as raw bytes until its real reader is ported (Rt2d brushes and fonts, the
// Maestro movies, Rwa wave dictionaries, RpAtomic geometry). The reader's stand-in finds the chunk and
// keeps it whole, which consumes exactly what the real reader consumes when the reader reads its chunk
// and nothing after it (the loader's end-offset check catches it otherwise).
struct RwShim_Blob {
    uint32_t type;
    uint32_t version;
    uint32_t length;
    uint8_t* data;  // length bytes after the header
};
RwShim_Blob* RwShim_ReadChunkBlob(RwStream* stream, uint32_t type);
void RwShim_FreeBlob(RwShim_Blob* blob);
