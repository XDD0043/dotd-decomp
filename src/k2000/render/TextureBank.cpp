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
//   [ ] 0xa5ac0  Rw_CreateNamedTextureInDictionary_maybe
//   [ ] 0xa5b60  Rw_RemoveAndDestroyTexture_maybe  [dead]
//   [ ] 0xa5bc8  Rw_CreateBlankNamedTexture_maybe
//   [ ] 0xa5d28  Rw_SetCurrentTexDictionary_maybe  [dead]
//   [x] 0xa5d78  Texture_ApplyGraphicsFilterMode_maybe
//   [ ] 0xa5e38  TextureBank_FindEntryByTexture_maybe  [dead]
//   [ ] 0xa5ea8  TextureBank_FindTextureByName_maybe  [dead]
//   [ ] 0xa5f70  Raster_LoadMipLevelsFromFilesOrResample
//   [ ] 0xa6548  Raster_CreateFromImage_maybe
//   [ ] 0xa66b0  Texture_CreateFromImage_maybe
//   [ ] 0xa6728  TextureBank_SaveTextureEntry_maybe  [dead]
//   [ ] 0xa69e0  TextureBank_Release_maybe
//   [x] 0xa6ab8  TextureBank_LoadTextureEntry_maybe
//   [x] 0xa6d80  TextureBank_CreateTextures_maybe
//   [x] 0xa6ed8  TextureBank_Load_maybe
//   [ ] 0xa71b0  IRendableObject_GetMaterialRenderInfo
//   [ ] 0xa71d0  CGeometry_SetField8_maybe
//   [ ] 0xa71d8  CGeometry_ExchangeLightZone
#include "k2000/render/TextureBank.h"

#include <cstring>

#include "Renderware/rwcore/RwStream.h"
#include "Renderware/rwcore/RwTexture.h"
#include "k2000/core/Stub.h"
#include "k2000/dictionaries/CTextureDictionary.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/io/CKLoadingManager.h"
#include "k2000/managers/CKGraphic.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/Engine.h"

// 0x000a5d78 Texture_ApplyGraphicsFilterMode_maybe
void TextureBank::ApplyGraphicsFilterMode(RwTexture* texture) {
    const uint32_t caps = g_pEngine->m_graphic->m_baHardwareCaps;
    const RwShim_DdsRaster* raster = texture->raster;
    uint32_t mode;
    if (raster != nullptr && raster->mipmapFormat && (caps & 2) != 0) {
        mode = (caps & 4) != 0 ? 6u : 5u;
    } else {
        mode = (caps & 1) != 0 ? 2u : 1u;
    }
    texture->filterAddressing = (texture->filterAddressing & 0xffffff00u) | mode;
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
        RwShim_DdsRaster* raster = nullptr;
        if (entry->m_bCreateRaster != 0) {
            // RwRasterCreate(width, height, depth, format | 4). STUB(C1.4): the shim has no render rasters.
            DOTD_STUB_ONCE("TextureBank_CreateTextures: RwRasterCreate");
        }
        RwTexture* texture = RwTextureCreate(raster);
        std::strncpy(texture->name, entry->m_szTextureName, sizeof(texture->name) - 1);  // RwTextureSetName
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
            // RwStreamFindChunk(stream, rwID_IMAGE) + RwImageStreamRead: the image chunk, whole.
            RwShim_Blob* image = RwShim_ReadChunkBlob(file->m_pRwStream, 0x18);
            void* texture = FindTextureByName(name);  // RwTextureRead(name, NULL)
            // The localised image (a language's flag, its logos) replaces the texture's raster.
            if (texture != nullptr) Texture_ReplaceRasterFromImage(static_cast<RwTexture*>(texture), image, nullptr);
            RwShim_FreeBlob(image);       // RwImageDestroy
            TextureRef_Release(texture);  // RwTextureDestroy
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
