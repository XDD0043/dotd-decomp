// KMemoryStream.cpp - reconstructed original translation unit 0x4a788-0x4af28 (GAME_TOC1, main_toc1), 17 functions, 16 live.
// Primary owner: KMemoryStream (not a registered class)
// Other owners: FileTag (2), IKFile (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x4a788  KMemoryStream_Tell
//   [x] 0x4a798  KMemoryStream_Write
//   [ ] 0x4a848  IKFile_Destructor_2  [dead]
//   [x] 0x4a858  KMemoryStream_Construct
//   [x] 0x4a898  KMemoryStream_Construct_2
//   [x] 0x4a8d8  KMemoryStream_WriteString
//   [x] 0x4a970  KMemoryStream_Read
//   [x] 0x4a9f0  KMemoryStream_IsEOF
//   [x] 0x4aa18  KMemoryStream_Printf
//   [x] 0x4ab38  KMemoryStream_ReadLine
//   [x] 0x4ac10  KMemoryStream_Seek
//   [x] 0x4ac90  KMemoryStream_Close
//   [x] 0x4ad00  KMemoryStream_Open
//   [x] 0x4ade8  KMemoryStream_DeletingDestructor
//   [x] 0x4ae18  KMemoryStream_Destructor
//   [x] 0x4ae28  FileTag_Decode
//   [x] 0x4aea8  FileTag_Encode
#include "k2000/io/KMemoryStream.h"

#include <cstdarg>
#include <cstring>

#include "k2000/memory/KMemBuffer.h"
#include "k2000/misc/Str.h"

// 0x0004ad00 KMemoryStream_Open: a buffer without data refuses (0). Read access counts a reader on the buffer (+0x14),
// write or read-write a writer (+0x18); the position starts at 0, and write-only access empties the buffer (Resize 0).
int32_t KMemoryStream::Open(const char* path, int32_t /*mode*/) {
    KMemBuffer* buffer = reinterpret_cast<KMemBuffer*>(const_cast<char*>(path));
    if (buffer == nullptr || buffer->m_pData == nullptr) return 0;
    const int32_t access = m_eInternalOpenMode;
    if (access == 1) {
        ++buffer->m_readerCount;
    } else if (access > 0 && access < 4) {
        ++buffer->m_writerCount;
    }
    m_pMemBuffer = buffer;
    m_i32Position = 0;
    if (m_eInternalOpenMode == 2) buffer->Resize(0);  // 0x48ec0
    return 1;
}

// 0x0004ac90 KMemoryStream_Close: the reader or writer count of the open taken back, the buffer dropped; 0.
int32_t KMemoryStream::Close() {
    const int32_t access = m_eInternalOpenMode;
    if (access == 1) {
        --m_pMemBuffer->m_readerCount;
    } else if (access > 0 && access < 4) {
        --m_pMemBuffer->m_writerCount;
    }
    m_pMemBuffer = nullptr;
    return 0;
}

// 0x0004a970 KMemoryStream_Read: `size` bytes copied from the position (no bound check), the position advanced.
uint32_t KMemoryStream::Read(void* dst, uint32_t size) {
    if (size != 0) {
        std::memcpy(dst, m_pMemBuffer->m_pData + m_i32Position, size);
        m_i32Position = static_cast<int32_t>(size) + m_i32Position;
    }
    return size;
}

// 0x0004a798 KMemoryStream_Write: the buffer grown to the end of the write (EnsureCapacity), the bytes copied, the
// position advanced and the buffer's size raised to it.
uint32_t KMemoryStream::Write(const void* src, uint32_t size) {
    m_pMemBuffer->EnsureCapacity(static_cast<int32_t>(size) + m_i32Position);  // 0x484a0
    std::memcpy(m_pMemBuffer->m_pData + m_i32Position, src, size);
    const int32_t end = static_cast<int32_t>(size) + m_i32Position;
    m_i32Position = end;
    if (m_pMemBuffer->m_i32Size < end) m_pMemBuffer->m_i32Size = end;
    return size;
}

// 0x0004a8d8 KMemoryStream_WriteString: the text without its terminator, as Write but the buffer's size is left as it
// was (the original does not raise it); 0.
int32_t KMemoryStream::WriteText(const char* text) {
    const int32_t length = static_cast<int32_t>(std::strlen(text));
    m_pMemBuffer->EnsureCapacity(length + m_i32Position);  // 0x484a0
    std::memcpy(m_pMemBuffer->m_pData + m_i32Position, text, static_cast<uint32_t>(length));
    m_i32Position = length + m_i32Position;
    return 0;
}

// 0x0004aa18 KMemoryStream_Printf: formats at the position into the buffer's free capacity (Str_VFormatBounded); while
// it does not fit (-1 or longer than the room) the buffer grows by twice the room (0x200 when there is none) and the
// format is tried again. The position advances by the length; past the buffer's size, the size follows (Resize).
int32_t KMemoryStream::Printf(const char* format, ...) {
    va_list args;
    va_start(args, format);
    int32_t room = m_pMemBuffer->m_i32Capacity - m_i32Position;
    int32_t length;
    for (;;) {
        // The PS3's va_list is a pointer into the register save area, reused unchanged by every try.
        va_list again;
        va_copy(again, args);
        length = Str_VFormatBounded(reinterpret_cast<char*>(m_pMemBuffer->m_pData + m_i32Position), room, format, again);
        va_end(again);
        if (length != -1 && !(room < length)) break;
        const int32_t grow = room != 0 ? static_cast<int32_t>(static_cast<uint32_t>(room) << 1) : 0x200;
        m_pMemBuffer->EnsureCapacity(grow + m_i32Position);  // 0x484a0
        room = m_pMemBuffer->m_i32Capacity - m_i32Position;
    }
    va_end(args);
    const int32_t end = length + m_i32Position;
    m_i32Position = end;
    if (m_pMemBuffer->m_i32Size < end) m_pMemBuffer->Resize(end);  // 0x48ec0
    return length;
}

// 0x0004a9f0 KMemoryStream_IsEOF
int32_t KMemoryStream::IsEOF() { return m_i32Position >= m_pMemBuffer->m_i32Size ? 1 : 0; }

// 0x0004ab38 KMemoryStream_ReadLine: null unless the position plus `size` is below the buffer's size (signed). Copies
// characters until it has copied a LF (then a terminator follows it) or `size` characters (then none).
// BUG(original): the position is left on the LF (the next line starts with it), and a LF as character `size` writes
// its terminator at dst[size].
char* KMemoryStream::ReadLine(char* dst, uint32_t size) {
    const uint8_t* data = m_pMemBuffer->m_pData;
    if (!(static_cast<int32_t>(m_i32Position + size) < m_pMemBuffer->m_i32Size)) return nullptr;
    if (static_cast<int32_t>(size) <= 0) return dst;
    dst[0] = static_cast<char>(data[m_i32Position]);
    uint32_t count = 1;
    if (data[m_i32Position] != '\n') {
        uint32_t left = size;  // the CTR count: ((size - 1) & 0xffffffff) + 1
        for (;;) {
            m_i32Position = m_i32Position + 1;
            if (--left == 0) return dst;
            dst[count] = static_cast<char>(data[m_i32Position]);
            ++count;
            if (data[m_i32Position] == '\n') break;
        }
    }
    dst[count] = 0;
    return dst;
}

// 0x0004ac10 KMemoryStream_Seek: from the start, the position or the end (size - offset); an unknown origin fails
// (1) with the position kept. 0 when the new position is within [0, size], else 1 (the position is kept anyway).
int32_t KMemoryStream::Seek(int32_t offset, int32_t whence) {
    int32_t position;
    if (whence == kSeekCur) {
        position = offset + m_i32Position;
    } else if (whence == kSeekEnd) {
        position = m_pMemBuffer->m_i32Size - offset;
    } else if (whence == kSeekSet) {
        position = offset;
    } else {
        return 1;
    }
    m_i32Position = position;
    if (position < 0) return 1;
    return position > m_pMemBuffer->m_i32Size ? 1 : 0;
}

// C2.8 port-all P08.

// 0x0004ae28 FileTag_Decode: every non-zero byte i of the string becomes (b - i) ^ 0xc (the length taken first).
void FileTag_Decode(char* tag) {
    const uint32_t length = static_cast<uint32_t>(std::strlen(tag));
    for (uint32_t i = 0; i < length; ++i) {
        const uint8_t b = static_cast<uint8_t>(tag[i]);
        if (b != 0) tag[i] = static_cast<char>(static_cast<uint8_t>(b - static_cast<uint8_t>(i)) ^ 0xc);
    }
}

// 0x0004aea8 FileTag_Encode: every non-zero byte i becomes (b ^ 0xc) + i.
void FileTag_Encode(char* tag) {
    const uint32_t length = static_cast<uint32_t>(std::strlen(tag));
    for (uint32_t i = 0; i < length; ++i) {
        const uint8_t b = static_cast<uint8_t>(tag[i]);
        if (b != 0) tag[i] = static_cast<char>(static_cast<uint8_t>((b ^ 0xc) + static_cast<uint8_t>(i)));
    }
}
