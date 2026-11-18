// TextureBank.cpp - reconstructed original translation unit 0xa59c0-0xa71e8 (GAME_TOC1, main_toc1), 31 functions, 20 live.
// Primary owner: TextureBank (not a registered class)
// Other owners: Rw (5), Texture (2), Raster (2), CGeometry (2), IRendableObject (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0xa59c0  TextureBank_Construct_2_maybe  [dead]
//   [x] 0xa59d0  TextureBank_Construct_maybe
//   [ ] 0xa59e0  KStub_Nop_a59e0  [dead]
//   [x] 0xa59e8  KStub_Return1_a59e8
//   [x] 0xa59f0  KStub_Return1_a59f0
//   [x] 0xa59f8  KStub_Return1_a59f8
//   [ ] 0xa5a00  TextureBank_GetEntryArray_maybe  [dead]
//   [ ] 0xa5a20  FUN_000a5a20  [dead]
//   [x] 0xa5a38  KStub_Return1_a5a38
//   [x] 0xa5a40  TextureBank_DeletingDestructor_maybe
//   [x] 0xa5a70  TextureBank_Destructor_maybe
//   [ ] 0xa5a80  TextureBank_Destructor_2_maybe  [dead]
//   [ ] 0xa5a90  Rw_AddTextureToDictionary_maybe  [dead]
//   [ ] 0xa5ac0  Rw_CreateNamedTextureInDictionary_maybe  [dead: no pointer to its descriptor 0xb49248, no call]
//   [ ] 0xa5b60  Rw_RemoveAndDestroyTexture_maybe  [dead]
//   [ ] 0xa5bc8  Rw_CreateBlankNamedTexture_maybe  [left: the 16x16 "Null Texture" (CKGraphic +0x20) of CKGraphic_InitializeModule 0x5aa70, its only caller ([platform]: BootStubs.cpp stands in); it needs RwRasterPushContext / RwRGBAToPixel / RwRasterClear, which the native RenderWare does not have; MeshShaderPassState's BindFallbackUnit7 covers the null texture]
//   [ ] 0xa5d28  Rw_SetCurrentTexDictionary_maybe  [dead]
//   [x] 0xa5d78  Texture_ApplyGraphicsFilterMode_maybe
//   [ ] 0xa5e38  TextureBank_FindEntryByTexture_maybe  [dead]
//   [ ] 0xa5ea8  TextureBank_FindTextureByName_maybe  [dead]
//   [ ] 0xa5f70  Raster_LoadMipLevelsFromFilesOrResample  [platform]  (the mip levels read from mip files on disc next to a path: the PS3 file stack; every Raster_CreateFromImage caller passes no path, so it never runs)
//   [x] 0xa6548  Raster_CreateFromImage_maybe
//   [x] 0xa66b0  Texture_CreateFromImage_maybe
//   [ ] 0xa6728  TextureBank_SaveTextureEntry_maybe  [dead]
//   [x] 0xa69e0  TextureBank_Release_maybe
//   [x] 0xa6ab8  TextureBank_LoadTextureEntry_maybe
//   [x] 0xa6d80  TextureBank_CreateTextures_maybe
//   [x] 0xa6ed8  TextureBank_Load_maybe
//   [x] 0xa71b0  IRendableObject_GetMaterialRenderInfo  (IRendableObject::GetRenderingProperties, IRendableObject.cpp)
//   [x] 0xa71d0  CGeometry_SetField8_maybe  (inline at its only caller StartParticleEffect, CKParticlesEffectNodeFx.cpp)
//   [x] 0xa71d8  CGeometry_ExchangeLightZone  (IRendableObject::ChangeLightSet, IRendableObject.cpp)
#include "k2000/render/TextureBank.h"

#include <cstring>

#include "Renderware/rwcore/RwRaster.h"
#include "Renderware/rwcore/RwStream.h"
#include "Renderware/rwcore/RwTexture.h"
#include "k2000/dictionaries/CTextureDictionary.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/io/CKLoadingManager.h"
#include "k2000/managers/CKGraphic.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/Engine.h"

// 0x000a5d78 Texture_ApplyGraphicsFilterMode_maybe
void TextureBank::ApplyGraphicsFilterMode(RwTexture* texture) {
    const uint32_t caps = g_pEngine->m_graphic->m_baHardwareCaps;
    const RwRaster* raster = texture->raster;
    uint32_t mode;
    if (raster != nullptr && (raster->cFormat & 0x80) != 0 && (caps & 2) != 0) {  // rwRASTERFORMATMIPMAP
        mode = (caps & 4) != 0 ? 6u : 5u;
    } else {
        mode = (caps & 1) != 0 ? 2u : 1u;
    }
    texture->filterAddressing = (texture->filterAddressing & 0xffffff00u) | mode;
}

// 0x000a69e0 TextureBank_Release_maybe (vt+0x08; CKGraphic_Destroy at the level unload): every entry's texture out of
// its dictionary, destroyed (RwTextureDestroy, when not null), its raster cleared (RwTextureSetRaster(texture, NULL)),
// then the entry block freed (its pointer and the count are left: the next level's Load replaces them).
// BUG(original): the raster is cleared after the texture was destroyed (freed when that was its last reference: the
// write lands in the texture free list's entry, RwTexture.cpp), and a null texture is still handed to
// RwTexDictionaryRemoveTexture.
void TextureBank::Destroy() {
    if (m_asDynamicTextureData == nullptr) return;
    for (uint32_t i = 0; i < m_ui32NbDynamicTextures; ++i) {
        RwTexture* texture = m_asDynamicTextureData[i].m_pTexture;
        RwTexDictionaryRemoveTexture(texture);
        if (texture != nullptr) RwTextureDestroy(texture);
        RwTextureSetRaster(texture, nullptr);
    }
    Mem_FreeAligned16(m_asDynamicTextureData);
}

// 0x000a6ab8 TextureBank_LoadTextureEntry_maybe: the name (s16 length + characters, then a 0), the
// raster parameters, and in a level (type 0) the addressing and filter words.
void TextureBank::LoadTextureEntry(SDynamicTextureData* entry, IKFile* file, int32_t type) {
    ReadU16LE(file, &entry->m_ui16NameLength);
    int16_t length = 0;
    if (static_cast<int16_t>(entry->m_ui16NameLength) != 0) {
        file->Read(entry->m_szTextureName, static_cast<uint32_t>(static_cast<int32_t>(static_cast<int16_t>(entry->m_ui16NameLength))));
        length = static_cast<int16_t>(entry->m_ui16NameLength);
    }
    entry->m_szTextureName[length] = 0;  // BUG(original): no bound against the 0x100-byte name
    ReadU8(file, &entry->m_bCreateRaster);
    ReadU32LE(file, &entry->m_ui32Width);
    ReadU32LE(file, &entry->m_ui32Height);
    ReadU32LE(file, &entry->m_ui32Depth);
    ReadU32LE(file, &entry->m_ui32Format);
    if (type == 0) {
        ReadU32LE(file, &entry->m_unk114);
        ReadU32LE(file, &entry->m_unk118);
    }
}

// 0x000a6d80 TextureBank_CreateTextures_maybe
void TextureBank::CreateTextures(CTextureDictionary* dictionary) {
    const uint32_t count = m_ui32NbDynamicTextures;
    if (count == 0) return;
    for (uint32_t i = 0; i != count; ++i) {
        SDynamicTextureData* entry = &m_asDynamicTextureData[i];
        // Rw_CreateNamedTextureInDictionary_maybe 0xa5ac0 inlined: a raster when asked (RwRasterCreate(width, height,
        // depth, format | 4)), the texture, its name, into the dictionary.
        RwRaster* raster = nullptr;
        if (entry->m_bCreateRaster != 0) {
            raster = RwRasterCreate(static_cast<RwInt32>(entry->m_ui32Width), static_cast<RwInt32>(entry->m_ui32Height),
                                    static_cast<RwInt32>(entry->m_ui32Depth), static_cast<RwInt32>(entry->m_ui32Format | 4));
        }
        RwTexture* texture = RwTextureCreate(raster);
        RwTextureSetName(texture, entry->m_szTextureName);
        RwTexDictionaryAddTexture(dictionary->m_pTexDictionary, texture);
        entry->m_pTexture = texture;
        const uint32_t addressing = entry->m_unk114 & 0xf;
        texture->filterAddressing = (addressing << 12) | (texture->filterAddressing & 0xffff00ffu) | (addressing << 8);
        entry->m_pTexture->filterAddressing = (entry->m_pTexture->filterAddressing & 0xffffff00u) | (entry->m_unk118 & 0xff);
    }
}

// 0x000a6ed8 TextureBank_Load_maybe
int32_t TextureBank::Load(IKFile* file, int32_t type) {
    if (type == 2) {
        uint32_t count = 0;
        ReadU32LE(file, &count);
        for (uint32_t i = 0; i < count; ++i) {
            Thread_YieldDuringLoad(1);
            char name[264];
            IKFile_ReadLengthPrefixedString(file, name, -1);
            RwStreamFindChunk(file->m_pRwStream, 0x18, nullptr, nullptr);  // rwID_IMAGE (result not checked)
            RwImage* image = RwImageStreamRead(file->m_pRwStream);
            // The localised image (a language's flag, its logos) replaces the texture's raster. BUG(original): neither
            // the image nor the texture is checked (every name the localisation files list is in a dictionary).
            RwTexture* texture = RwTextureRead(name, nullptr);
            Texture_ReplaceRasterFromImage(texture, image, nullptr);
            RwImageDestroy(image);
            RwTextureDestroy(texture);
        }
        return 1;
    }
    if (type == 0) {
        ReadU32LE(file, &m_ui32NbDynamicTextures);
        if (m_ui32NbDynamicTextures == 0) {
            m_ui32NbDynamicTextures = 0;
            m_asDynamicTextureData = nullptr;
        } else {
            m_asDynamicTextureData = static_cast<SDynamicTextureData*>(
                Mem_AllocAligned16(m_ui32NbDynamicTextures * static_cast<uint32_t>(sizeof(SDynamicTextureData))));
            for (uint32_t i = 0; i < m_ui32NbDynamicTextures; ++i) LoadTextureEntry(&m_asDynamicTextureData[i], file, 0);
        }
        CTextureDictionary* dictionary = nullptr;
        IKFile_ReadRef(file, &dictionary);
        CreateTextures(dictionary);
        return 1;
    }
    return 1;
}

// 0x000a6548 Raster_CreateFromImage_maybe: the raster an image becomes (RwImageFindRasterFormat for a texture,
// with rwRASTERFORMATMIPMAP when mipmaps are asked and the graphic caps have bit 1), its pixels set from the image;
// a mipmapped one gets its levels from mip files next to `path` (Raster_LoadMipLevelsFromFilesOrResample 0xa5f70) or,
// failing that, from the texture module's mipmap callback (RwTexture_RasterGenerateMipmaps_maybe). Null (the raster
// destroyed) when a step fails. The bank is passed on to the mip file loader only. Every caller passes no path:
// the fonts (CManager2d) and Texture_ReplaceRasterFromImage_maybe without mipmaps, CTextureDictionary_LoadPITextures'
// image branch (never run: its only caller passes resolveRasters 1) with mipmaps for names without a UI prefix.
RwRaster* Raster_CreateFromImage(TextureBank* /*bank*/, RwImage* image, uint8_t mipmap, const char* path) {
    bool mipmaps = false;
    RwInt32 type = rwRASTERTYPETEXTURE;
    if (mipmap != 0 && (g_pEngine->m_graphic->m_baHardwareCaps & 2) != 0) {
        mipmaps = true;
        type = rwRASTERFORMATMIPMAP | rwRASTERTYPETEXTURE;
    }
    // BUG(original): the result is not checked (it fails only for raster types the calls here never ask for).
    RwInt32 width = 0, height = 0, depth = 0, format = 0;
    RwImageFindRasterFormat(image, type, &width, &height, &depth, &format);
    RwRaster* raster = RwRasterCreate(width, height, depth, format);
    if (raster == nullptr) return nullptr;
    bool failed = RwRasterSetFromImage(raster, image) == nullptr;
    if (!failed && mipmaps) {
        // With a path, Raster_LoadMipLevelsFromFilesOrResample 0xa5f70 (mip files on disc) first: the only call with
        // mipmaps passes none, so the mipmap callback makes the levels.
        (void)path;
        failed = RwTextureRasterGenerateMipmaps(raster, image) == nullptr;
    }
    if (failed) {
        RwRasterDestroy(raster);
        return nullptr;
    }
    return raster;
}

// 0x000a66b0 Texture_CreateFromImage_maybe: a texture of Raster_CreateFromImage_maybe's raster (the raster destroyed
// when the texture cannot be made).
RwTexture* Texture_CreateFromImage(TextureBank* bank, RwImage* image, uint8_t mipmap, const char* path) {
    RwRaster* raster = Raster_CreateFromImage(bank, image, mipmap, path);
    if (raster == nullptr) return nullptr;
    RwTexture* texture = RwTextureCreate(raster);
    if (texture == nullptr) RwRasterDestroy(raster);
    return texture;
}
