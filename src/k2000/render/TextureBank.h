// TextureBank.h - the bank of textures the level creates at load time (not a registered class;
// vtable 0xb171f0, size 0xc). Original unit: TextureBank.cpp (0xa59c0-0xa71e8). XXL2:
// K/KModules/KGL/CTextureManager.h, the same two members; CKGraphic +0x08 owns it, Engine +0x40 too.
//
// The level (type 0) lists the textures to create (render targets such as "backbuffer texture_00"); a
// localisation file (type 2) replaces named textures' images (RwImage chunks).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"

class IKFile;
class CTextureDictionary;
struct RwTexture;

// One texture to create (XXL2 SDynamicTextureData), 0x120 bytes on the PS3.
struct SDynamicTextureData {
    char m_szTextureName[0x100];   // +0x000 TELBString: the characters ...
    uint16_t m_ui16NameLength;     // +0x100 ... and the length
    uint8_t m_bCreateRaster;       // +0x102
    uint8_t m_pad103;
    uint32_t m_ui32Width;          // +0x104
    uint32_t m_ui32Height;         // +0x108
    uint32_t m_ui32Depth;          // +0x10c
    uint32_t m_ui32Format;         // +0x110 RwRasterCreate flags (| 4 when created)
    uint32_t m_unk114;             // +0x114 DotD: the U and V addressing (low nibble); type 0 only
    uint32_t m_unk118;             // +0x118 DotD: the filter mode (low byte); type 0 only
    RwTexture* m_pTexture;         // +0x11c
};
DOTD_ASSERT_SIZE(SDynamicTextureData, 0x120);
DOTD_ASSERT_OFFSET(SDynamicTextureData, m_ui16NameLength, 0x100);
DOTD_ASSERT_OFFSET(SDynamicTextureData, m_bCreateRaster, 0x102);
DOTD_ASSERT_OFFSET(SDynamicTextureData, m_ui32Width, 0x104);
DOTD_ASSERT_OFFSET(SDynamicTextureData, m_unk118, 0x118);
DOTD_ASSERT_OFFSET(SDynamicTextureData, m_pTexture, 0x11c);

class TextureBank {
public:
    TextureBank() {}  // 0x000a59d0 TextureBank_Construct_maybe: the vtable only
    virtual ~TextureBank() {}                                     // vt+0x00 / +0x04 0xa5a70 / 0xa5a40
    virtual void Destroy() {}                                     // vt+0x08 0xa69e0 TextureBank_Release_maybe  STUB(C1.6)
    virtual int32_t RecursiveRegistration(int32_t) { return 1; }  // vt+0x0c 0xa59e8
    virtual int32_t Save(IKFile*, int32_t) { return 1; }          // vt+0x10 0xa59f0
    virtual int32_t Load(IKFile* file, int32_t type);             // vt+0x14 0xa6ed8 TextureBank_Load_maybe
    virtual int32_t PostLoad(int32_t) { return 1; }               // vt+0x18 0xa59f8
    virtual int32_t MessageProc(uint16_t, void*) { return 1; }                   // vt+0x1c 0xa5a38

    // 0x000a6ab8 TextureBank_LoadTextureEntry_maybe
    static void LoadTextureEntry(SDynamicTextureData* entry, IKFile* file, int32_t type);
    // 0x000a6d80 TextureBank_CreateTextures_maybe: every entry's texture, added to the dictionary.
    void CreateTextures(CTextureDictionary* dictionary);
    // 0x000a5d78 Texture_ApplyGraphicsFilterMode_maybe (C2.4 exit): the texture's filter mode (filterAddressing low byte)
    // from the graphic caps (CKGraphic +0x10): a mipmapped raster with caps bit 1 gets rwFILTERLINEARMIPLINEAR (6) with
    // bit 2, rwFILTERLINEARMIPNEAREST (5) without; any other texture rwFILTERLINEAR (2) with caps bit 0, else
    // rwFILTERNEAREST (1). The bank argument (the engine's, +0x40) is not read.
    static void ApplyGraphicsFilterMode(RwTexture* texture);

    SDynamicTextureData* m_asDynamicTextureData;  // +0x04 Mem_AllocAligned16; not set by the constructor
    uint32_t m_ui32NbDynamicTextures;             // +0x08 not set by the constructor
};
DOTD_ASSERT_SIZE(TextureBank, 0xc);
DOTD_ASSERT_OFFSET(TextureBank, m_asDynamicTextureData, 0x04);
DOTD_ASSERT_OFFSET(TextureBank, m_ui32NbDynamicTextures, 0x08);
