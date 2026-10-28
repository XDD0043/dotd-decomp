// CTextureDictionary.h - a level's textures (key 0x89, vtable 0xb13150, size 0x8). Original unit:
// CTextureDictionary.cpp (0xc0948-0xc18d0). LVL000 holds one, 11.4 MB: 147 PS3 textures, each a name
// record followed by a raw DDS file (CTextureDictionary_LoadPITextures).
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"

struct RwTexDictionary;

class CTextureDictionary : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryDictionary, 0x2)
    DOTD_DECLARE_FACTORIES(CTextureDictionary)

    CTextureDictionary() : m_pTexDictionary(nullptr) {}  // 0x000c0ad8 CTextureDictionary_Create (inlined)
    ~CTextureDictionary() override {}                     // STUB(C1.6): 0x992138 (frees the dictionary)

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x000c0f18 CTextureDictionary_Load
    // 0x000c0bb8: count records of name[32], u32 (unused), u32 filter mode, u32 addressing, then a raw DDS
    // file (resolveRasters != 0) or an RwImage chunk (0x18) that becomes a raster through the texture bank.
    // 0 when the game loop asks to exit in the middle.
    int32_t LoadPITextures(IKFile* file, uint8_t resolveRasters);

    RwTexDictionary* m_pTexDictionary;  // +0x04
};
DOTD_ASSERT_SIZE(CTextureDictionary, 0x8);
DOTD_ASSERT_OFFSET(CTextureDictionary, m_pTexDictionary, 0x04);
