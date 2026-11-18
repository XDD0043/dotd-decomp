// KMemoryStream.h - the stream over a KMemBuffer (0x20 bytes, vtable 0xb14f10, constructor 0x4a858): KFileSystem's
// memory device (KFileSystem_OpenFile device 3, the "path" is the KMemBuffer*). The game manager's save-state stream
// (CDefaultGameManager +0x3c) is one. Original unit: KMemoryStream.cpp (0x4a788-0x4af28).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/io/IKFile.h"

class KMemBuffer;

class KMemoryStream : public IKFile {
public:
    // 0x0004a858 KMemoryStream_Construct (0x0004a898 KMemoryStream_Construct_2 the same): IKFile_Construct, the vtable,
    // no buffer (+0x1c). The original leaves the position (+0x18) to Open, which every caller runs before a read.
    KMemoryStream() : m_i32Position(0), m_pMemBuffer(nullptr) {}

    // vt+0x00 0x0004ad00 KMemoryStream_Open: `path` is the KMemBuffer.
    int32_t Open(const char* path, int32_t mode) override;
    // vt+0x04 0x00995930 KStub_Return0_995930: IKFile's default.
    // vt+0x08 / +0x0c 0x0004ae18 / 0x0004ade8 KMemoryStream_Destructor / _DeletingDestructor: IKFile's vtable back
    // only (the buffer is not closed).
    ~KMemoryStream() override {}
    int32_t Close() override;                                   // vt+0x10 0x0004ac90 KMemoryStream_Close
    uint32_t Read(void* dst, uint32_t size) override;           // vt+0x14 0x0004a970 KMemoryStream_Read
    int32_t BeginAsyncRead() override { return 0; }             // vt+0x18 0x00995948 KStub_Nop_995948
    int32_t UpdateAsyncRead() override { return -1; }           // vt+0x1c 0x00995950 KStub_ReturnM1_995950
    uint32_t Write(const void* src, uint32_t size) override;    // vt+0x20 0x0004a798 KMemoryStream_Write
    int32_t BeginAsyncWrite() override { return 0; }            // vt+0x24 0x00995958 KStub_Nop_995958
    int32_t UpdateAsyncWrite() override { return -1; }          // vt+0x28 0x00995960 KStub_ReturnM1_995960
    int32_t Seek(int32_t offset, int32_t whence) override;      // vt+0x2c 0x0004ac10 KMemoryStream_Seek
    char* ReadLine(char* dst, uint32_t size) override;          // vt+0x30 0x0004ab38 KMemoryStream_ReadLine
    int32_t WriteText(const char* text) override;               // vt+0x34 0x0004a8d8 KMemoryStream_WriteString
    int32_t Printf(const char* format, ...) override;           // vt+0x38 0x0004aa18 KMemoryStream_Printf
    // vt+0x3c 0x0004a9f0 KMemoryStream_IsEOF: the position at or past the buffer's size (signed).
    int32_t IsEOF() override;
    int32_t Flush() override { return 0; }                      // vt+0x40 0x0004a780 KStub_Return0_4a780
    uint32_t Tell() override { return static_cast<uint32_t>(m_i32Position); }  // vt+0x44 0x0004a788 KMemoryStream_Tell
    // vt+0x48 0x0004d088 IKFile_GetFileLength: IKFile's (seek to the end, tell, seek back).

    int32_t m_i32Position;      // +0x18 the read / write position in the buffer
    KMemBuffer* m_pMemBuffer;   // +0x1c the buffer (Open; Close clears it)
};
DOTD_ASSERT_SIZE(KMemoryStream, 0x20);
DOTD_ASSERT_OFFSET(KMemoryStream, m_i32Position, 0x18);
DOTD_ASSERT_OFFSET(KMemoryStream, m_pMemBuffer, 0x1c);

// 0x0004ae28 FileTag_Decode / 0x0004aea8 FileTag_Encode (KMemoryStream.cpp): the save files' tag string obfuscation, in place.
void FileTag_Decode(char* tag);
void FileTag_Encode(char* tag);
