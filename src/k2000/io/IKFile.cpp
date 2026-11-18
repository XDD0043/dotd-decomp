// IKFile.cpp - reconstructed original translation unit 0x4cfe0-0x4d7d8 (GAME_TOC1, main_toc1), 10 functions, 8 live.
// Primary owner: IKFile (not a registered class)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x4cfe0  IKFile_Construct
//   [ ] 0x4d008  IKFile_Construct_2  [dead]
//   [x] 0x4d030  IKFile_SetAccessMode
//   [x] 0x4d088  IKFile_GetFileLength
//   [x] 0x4d168  IKFile_GetString
//   [x] 0x4d218  IKFile_ReadTextureRef
//   [x] 0x4d2e8  KStub_Return0_4d2e8  (IKFile::Printf inline default, IKFile.h)
//   [x] 0x4d2f0  IKFile_ReadLengthPrefixedString
//   [x] 0x4d4e0  IKFile_PutString
//   [ ] 0x4d620  IKFile_WriteLengthPrefixedWideString_maybe  [dead]
//
//   [x] 0x995a48  IKFile_DeletingDestructor  [inline]
//   [x] 0x995a78  IKFile_Destructor  [inline]
#include "k2000/io/IKFile.h"

#include "k2000/logic/io/CKLoadingManager.h"
#include "k2000/misc/Engine.h"

// 0x0004cfe0 IKFile_Construct
IKFile::IKFile() : m_pRwStream(nullptr), m_eInternalOpenMode(4), m_pSavingInterfaces(nullptr), m_pLoadingInterfaces(nullptr), m_unk14(0) {}

// 0x00995a78 IKFile_Destructor, 0x00995a48 IKFile_DeletingDestructor
IKFile::~IKFile() {}

// 0x0004d168 IKFile_GetString: one byte at a time through Read (vt+0x14) until a short read, a CR or LF (stored), or
// `size` bytes. BUG(original): returns null on every path and never terminates the string.
char* IKFile::ReadLine(char* dst, uint32_t size) {
    do {
        --size;
        if (Read(dst, 1) != 1) return nullptr;
        const char c = *dst++;
        if (c == '\r' || c == '\n') return nullptr;
    } while (size != 0);
    return nullptr;
}

// 0x0004d4e0 IKFile_PutString: each line up to LF or the end through Write (vt+0x20), an LF as the two bytes CR LF
// (0x00ac3c00); returns the sum of the writes.
int32_t IKFile::WriteText(const char* text) {
    static const char kCrLf[3] = {'\r', '\n', 0};  // 0x00ac3c00
    int32_t total = 0;
    for (;;) {
        const char* end = text;
        while (*end != '\n' && *end != '\0') ++end;
        total += static_cast<int32_t>(Write(text, static_cast<uint32_t>(end - text)));
        if (*end == '\0') break;
        text = end + 1;
        if (*end == '\n') total += static_cast<int32_t>(Write(kCrLf, 2));
    }
    return total;
}

// 0x0004d088 IKFile_GetFileLength: seek to the end, tell, seek back.
uint32_t IKFile::GetSize() {
    const uint32_t position = Tell();
    Seek(0, kSeekEnd);
    const uint32_t size = Tell();
    Seek(static_cast<int32_t>(position), kSeekSet);
    return size;
}

// 0x0004d030 IKFile_SetAccessMode
void IKFile_SetAccessMode(IKFile* stream, int32_t mode) {
    stream->m_pLoadingInterfaces = nullptr;
    stream->m_eInternalOpenMode = mode;
    stream->m_pSavingInterfaces = nullptr;
    if (static_cast<uint32_t>(mode - 2) < 2u) stream->m_pSavingInterfaces = g_pEngine->m_pSavingManager;
    if (mode != 1 && mode != 3) return;
    stream->m_pLoadingInterfaces = g_pEngine->m_loadingManager;
}

// 0x0004d218 IKFile_ReadTextureRef. Both paths look the texture up (the decompiler drops the
// arguments of the first call; the assembly passes stream and slot in r4/r5). Only resolve != 0 keeps
// a reference: the resolver's lookup adds one and releases it again.
uint32_t IKFile_ReadTextureRef(IKFile* stream, void** texture, int32_t resolve) {
    if (resolve == 0) {
        *texture = nullptr;
        return stream->m_pLoadingInterfaces->ReadTexture(stream, texture);
    }
    const uint32_t got = stream->m_pLoadingInterfaces->ReadTexture(stream, texture);
    if (*texture != nullptr) TextureRef_AddRef(*texture);  // RwTexture +0x54 refCount + 1
    return got;
}

// 0x0004d2f0 IKFile_ReadLengthPrefixedString
uint32_t IKFile_ReadLengthPrefixedString(IKFile* stream, char* dst, int32_t maxLength) {
    uint16_t raw = 0;
    const uint32_t gotLength = ReadU16LE(stream, &raw);
    const int16_t length = static_cast<int16_t>(raw);  // signed compare (lha / cmpwi)
    if (length < 1) {
        *dst = 0;
        return gotLength;
    }
    if (maxLength > -1 && maxLength <= length) {
        const uint32_t got = stream->Read(dst, static_cast<uint32_t>(maxLength));
        stream->Seek(length - maxLength, kSeekCur);
        dst[maxLength - 1] = 0;
        return gotLength + got;
    }
    const uint32_t got = stream->Read(dst, static_cast<uint32_t>(length));
    dst[length] = 0;
    return gotLength + got;
}

// The inlined reference read (resolver vt+0x24 / vt+0x28, or Read(dst, 4) without a resolver).
uint32_t IKFile_ReadObjectRef(IKFile* stream, IKSerializable** object) {
    if (stream->m_pLoadingInterfaces != nullptr) return stream->m_pLoadingInterfaces->ReadHandle(stream, object);
    uint32_t id = 0;
    const uint32_t got = stream->Read(&id, 4);
    *object = reinterpret_cast<IKSerializable*>(static_cast<uintptr_t>(id));
    return got;
}

uint32_t IKFile_ReadObjectRefArray(IKFile* stream, IKSerializable** objects, uint32_t count) {
    if (stream->m_pLoadingInterfaces != nullptr) return stream->m_pLoadingInterfaces->ReadContiguousHandles(stream, objects, count);
    uint32_t got = 0;
    for (uint32_t i = 0; i < count; ++i) {
        uint32_t id = 0;
        got += stream->Read(&id, 4);
        objects[i] = reinterpret_cast<IKSerializable*>(static_cast<uintptr_t>(id));
    }
    return got;
}
