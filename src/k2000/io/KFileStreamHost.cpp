// KFileStreamHost.cpp - KFileStream (see KFileStream.h): platform equivalent of KFileStream +
// IKSBufferFile + KHostFS for reading. The original units are KFileStream.cpp, KFileStream_2.cpp,
// IKSBufferFile.cpp and KHostFS.cpp; their checklists stay open.
#include "k2000/io/KFileStream.h"

#include <cstring>
#include <string>

#include "platform/cell/cell_errors.h"
#include "platform/cell/fs.h"

namespace {
constexpr uint32_t kBlockSize = 0x100000;  // IKSBufferFile_Construct(1 MB, align 0x40)
constexpr const char* kRoot = "/dev_bdvd/PS3_GAME/USRDIR";  // KHostFS_BuildPath
}  // namespace

KFileStream::KFileStream() : m_fd(-1), m_size(0), m_position(0), m_blockStart(0), m_blockSize(0) {}

KFileStream::~KFileStream() { Close(); }

int32_t KFileStream::Open(const char* path, int32_t mode) {
    if (mode != 0 && mode != 4 && mode != 8) return 0;  // read-only open flags; writing is not needed yet
    std::string full = std::string(kRoot) + "/" + path;
    CellFsStat st;
    if (cellFsStat(full.c_str(), &st) != CELL_OK) return 0;
    if (cellFsOpen(full.c_str(), CELL_FS_O_RDONLY, &m_fd, nullptr, 0) != CELL_OK) {
        m_fd = -1;
        return 0;
    }
    m_size = static_cast<uint32_t>(st.size);
    m_position = 0;
    m_blockSize = 0;
    m_block.resize(kBlockSize);
    return 1;
}

int32_t KFileStream::Close() {
    if (m_fd >= 0) cellFsClose(m_fd);
    m_fd = -1;
    m_blockSize = 0;
    return 1;
}

bool KFileStream::LoadBlock(uint32_t blockStart) {
    uint64_t at = 0;
    if (cellFsLseek(m_fd, blockStart, CELL_FS_SEEK_SET, &at) != CELL_OK) return false;
    uint64_t got = 0;
    const uint32_t want = m_size - blockStart < kBlockSize ? m_size - blockStart : kBlockSize;
    if (cellFsRead(m_fd, m_block.data(), want, &got) != CELL_OK) return false;
    m_blockStart = blockStart;
    m_blockSize = static_cast<uint32_t>(got);
    return true;
}

uint32_t KFileStream::Read(void* dst, uint32_t size) {
    uint8_t* out = static_cast<uint8_t*>(dst);
    uint32_t done = 0;
    while (done < size && m_position < m_size) {
        if (m_blockSize == 0 || m_position < m_blockStart || m_position >= m_blockStart + m_blockSize) {
            if (!LoadBlock(m_position - m_position % kBlockSize)) break;
        }
        const uint32_t offset = m_position - m_blockStart;
        uint32_t chunk = m_blockSize - offset;
        if (chunk > size - done) chunk = size - done;
        std::memcpy(out + done, m_block.data() + offset, chunk);
        done += chunk;
        m_position += chunk;
    }
    return done;
}

int32_t KFileStream::Seek(int32_t offset, int32_t whence) {
    int64_t target = offset;
    if (whence == kSeekCur) target += m_position;
    else if (whence == kSeekEnd) target += m_size;
    if (target < 0) target = 0;
    if (target > m_size) target = m_size;
    m_position = static_cast<uint32_t>(target);
    return 1;
}
