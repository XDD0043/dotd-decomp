// IKFile.h - the engine's stream interface (k2000). Original unit: IKFile.cpp (0x4cfe0-0x4d7d8).
//
// Every Load reads through it: Read (vt+0x14), Seek (vt+0x2c), Tell (vt+0x44). References go through
// the resolver at +0x10 (the CKLoadingManager while a KP3 file is read). KP3 data is little-endian;
// the PS3 code byte-swaps after each read. On little-endian hosts the bytes are already in order, so
// the ports read straight into the field (see the Read*LE helpers).
#pragma once
#include <cstdint>
#include <cstring>

#include "k2000/core/Layout.h"

class CKLoadingManager;
class CKSavingManager;
class IKSerializable;
struct RwStream;

enum KStreamWhence : int32_t { kSeekSet = 0, kSeekCur = 1, kSeekEnd = 2 };

// vtable 0xb15218 (abstract base); KFileStream 0xb14f70.
class IKFile {
public:
    IKFile();                                                   // 0x0004cfe0 IKFile_Construct
    virtual int32_t Open(const char* path, int32_t mode) = 0;    // vt+0x00 (KFileStream_Open; arguments unverified)
    virtual int32_t Vf04() { return 0; }                         // vt+0x04
    virtual ~IKFile();                                          // vt+0x08 / +0x0c
    virtual int32_t Close() = 0;                                 // vt+0x10
    virtual uint32_t Read(void* dst, uint32_t size) = 0;         // vt+0x14 returns the bytes read
    virtual int32_t BeginAsyncRead() { return 0; }               // vt+0x18 (not used by KP3 streams)
    virtual int32_t UpdateAsyncRead() { return 0; }              // vt+0x1c
    virtual uint32_t Write(const void* /*src*/, uint32_t /*size*/) { return 0; }  // vt+0x20
    virtual int32_t BeginAsyncWrite() { return 0; }              // vt+0x24
    virtual int32_t UpdateAsyncWrite() { return 0; }             // vt+0x28
    virtual int32_t Seek(int32_t offset, int32_t whence) = 0;    // vt+0x2c KStreamWhence
    virtual int32_t ReadLine() { return 0; }                     // vt+0x30 IKFile_GetString (arguments unverified)
    virtual int32_t WriteText() { return 0; }                    // vt+0x34 IKFile_PutString (arguments unverified)
    virtual int32_t Vf38() { return 0; }                         // vt+0x38 0x4d2e8
    virtual int32_t IsEOF() = 0;                                 // vt+0x3c
    virtual int32_t Flush() { return 0; }                        // vt+0x40
    virtual uint32_t Tell() = 0;                                 // vt+0x44
    virtual uint32_t GetSize();                                  // vt+0x48 0x4d088 (IKSBufferFile overrides it)

    RwStream* m_pRwStream;            // +0x04 the RenderWare "ELB:" stream over this file (KFileSystem_OpenFile bindRw)
    int32_t m_eInternalOpenMode;            // +0x08 1 read, 2/3 write, 4 none (constructor)
    CKSavingManager* m_pSavingInterfaces;  // +0x0c access 2 and 3
    CKLoadingManager* m_pLoadingInterfaces;    // +0x10 access 1 and 3: reads object and texture references
    uint8_t m_unk14;                 // +0x14
};

// 0x0004d030 IKFile_SetAccessMode
void IKFile_SetAccessMode(IKFile* stream, int32_t mode);
// 0x0004d218 IKFile_ReadTextureRef: *texture = the named texture, or null; with resolve != 0 the
// texture's reference count is incremented.
uint32_t IKFile_ReadTextureRef(IKFile* stream, void** texture, int32_t resolve);
// 0x0004d2f0 IKFile_ReadLengthPrefixedString: s16 length + bytes. With maxLength >= 0 and a longer
// string, maxLength bytes are read, the rest is skipped and dst[maxLength - 1] becomes 0.
uint32_t IKFile_ReadLengthPrefixedString(IKFile* stream, char* dst, int32_t maxLength);

// Little-endian field reads (the PS3 code reads, then byte-swaps with lwbrx/lhbrx).
inline uint32_t ReadU32LE(IKFile* stream, uint32_t* dst) {
    uint8_t b[4];
    const uint32_t got = stream->Read(b, 4);
    *dst = static_cast<uint32_t>(b[0]) | (static_cast<uint32_t>(b[1]) << 8) | (static_cast<uint32_t>(b[2]) << 16) |
           (static_cast<uint32_t>(b[3]) << 24);
    return got;
}
inline uint32_t ReadU16LE(IKFile* stream, uint16_t* dst) {
    uint8_t b[2];
    const uint32_t got = stream->Read(b, 2);
    *dst = static_cast<uint16_t>(b[0] | (b[1] << 8));
    return got;
}
inline uint32_t ReadU8(IKFile* stream, uint8_t* dst) { return stream->Read(dst, 1); }
inline uint32_t ReadS32LE(IKFile* stream, int32_t* dst) { return ReadU32LE(stream, reinterpret_cast<uint32_t*>(dst)); }
inline uint32_t ReadS16LE(IKFile* stream, int16_t* dst) { return ReadU16LE(stream, reinterpret_cast<uint16_t*>(dst)); }
inline uint32_t ReadF32LE(IKFile* stream, float* dst) {
    uint32_t bits = 0;
    const uint32_t got = ReadU32LE(stream, &bits);
    std::memcpy(dst, &bits, 4);
    return got;
}
// One read of count words, each byte-swapped after the read (the PS3's inlined Read(n*4) + swap loop).
inline uint32_t ReadU32LEWords(IKFile* stream, uint32_t* dst, uint32_t count) {
    const uint32_t got = stream->Read(dst, count * 4);
    for (uint32_t i = 0; i < count; ++i) {
        const uint8_t* b = reinterpret_cast<const uint8_t*>(dst + i);
        dst[i] = static_cast<uint32_t>(b[0]) | (static_cast<uint32_t>(b[1]) << 8) |
                 (static_cast<uint32_t>(b[2]) << 16) | (static_cast<uint32_t>(b[3]) << 24);
    }
    return got;
}
// Bytes that the PS3 code reads and does not byte-swap (colours, packed bytes): exactly as stored.
inline uint32_t ReadRaw(IKFile* stream, void* dst, uint32_t size) { return stream->Read(dst, size); }

// The object-reference read every Load inlines: through the stream's resolver (stream +0x10, set for
// KP3 files), or, without one, the raw 4-byte id (the PS3 then stores the id in the pointer field).
uint32_t IKFile_ReadObjectRef(IKFile* stream, IKSerializable** object);
uint32_t IKFile_ReadObjectRefArray(IKFile* stream, IKSerializable** objects, uint32_t count);
template <class T>
inline uint32_t IKFile_ReadRef(IKFile* stream, T** object) {
    IKSerializable* read = nullptr;
    const uint32_t got = IKFile_ReadObjectRef(stream, &read);
    *object = static_cast<T*>(read);
    return got;
}

// The texture registry (STUB(C1.3): RenderWare textures; until then no texture is ever found).
void TextureRef_AddRef(void* texture);
void* FindTextureByName(const char* name);
struct RwShim_Blob;
struct RwTexture;
// 0x000c0570 Texture_ReplaceRasterFromImage_maybe (render/Texture.cpp): the texture's raster made from an RwImage.
int32_t Texture_ReplaceRasterFromImage(RwTexture* texture, const RwShim_Blob* image, const char* path);  // 0x000c0828 FindTextureByName_maybe (RwTextureRead(name, NULL))
void TextureRef_Release(void* texture);     // RwTextureDestroy (decrements, destroys at 0)

// Uuid.cpp: 16 bytes as four little-endian words.
uint32_t Uuid_Read(uint32_t* uuid, IKFile* stream);       // 0x00245e08
void Uuid_Copy(uint32_t* dst, const uint32_t* src);        // 0x00246190
bool Uuid_Equals(const uint32_t* a, const uint32_t* b);    // Uuid_Equals
bool Uuid_IsNull(const uint32_t* uuid);                     // 0x002461d8 Uuid_IsNull
