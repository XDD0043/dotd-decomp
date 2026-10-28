// KFileStream.h - the file stream KP3 files are read through.
//
// Platform equivalent, not a port: the original is KFileStream (0xf8 bytes, vtable 0xb14f70) on
// IKSBufferFile (a 1 MB block buffer) over RtFS "HOSTFS" -> KHostFS -> cellFs. This one keeps the
// observable behaviour: synchronous reads through a 1 MB block window over the cellFs shim, with
// paths under /dev_bdvd/PS3_GAME/USRDIR (KHostFS_BuildPath).
#pragma once
#include <cstdint>
#include <vector>

#include "k2000/io/IKFile.h"

class KFileStream : public IKFile {
public:
    KFileStream();
    ~KFileStream() override;

    // path: relative to USRDIR, '/' separators; mode: KFileSystem open flags (only reading so far).
    int32_t Open(const char* path, int32_t mode) override;
    int32_t Close() override;
    uint32_t Read(void* dst, uint32_t size) override;
    int32_t Seek(int32_t offset, int32_t whence) override;
    int32_t IsEOF() override { return m_position >= m_size ? 1 : 0; }
    uint32_t Tell() override { return m_position; }
    uint32_t GetSize() override { return m_size; }

private:
    bool LoadBlock(uint32_t blockStart);

    int32_t m_fd;
    uint32_t m_size;
    uint32_t m_position;
    uint32_t m_blockStart;  // file offset of the buffered block
    uint32_t m_blockSize;   // valid bytes in the block (0 = none loaded)
    std::vector<uint8_t> m_block;
};
