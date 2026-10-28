// CTextureDictionary.cpp - reconstructed original translation unit 0xc0948-0xc18d0 (GAME_TOC1, main_toc1), 14 functions, 12 live.
// Primary class: CTextureDictionary  key 0x89  category Dictionary  size 0x8  vtable 0xb13150
// Other owners: RwImage (2), Raster (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0xc0948  CTextureDictionary_Delete
//   [ ] 0xc0998  CTextureDictionary_RecursiveRegistration
//   [ ] 0xc09a0  CTextureDictionary_Save
//   [ ] 0xc09a8  CTextureDictionary_PostLoad
//   [ ] 0xc09b0  RegisterCTextureDictionaryClass
//   [ ] 0xc0a28  _GLOBAL__I_c0a28
//   [x] 0xc0a38  CTextureDictionary_DeleteArray
//   [x] 0xc0ad8  CTextureDictionary_Create
//   [x] 0xc0b18  CTextureDictionary_CreateArray
//   [x] 0xc0bb8  CTextureDictionary_LoadPITextures
//   [x] 0xc0f18  CTextureDictionary_Load
//   [ ] 0xc1028  RwImage_SwapOuterChannelBytes32_maybe  [dead]
//   [ ] 0xc10d0  RwImage_AnalyzeAlpha_maybe  [dead]
//   [ ] 0xc17a8  Raster_SwapFirstTwoChannelBytes32_maybe
//
//   [ ] 0x9915a0  CTextureDictionary_GetClassType  [inline]
//   [ ] 0x9915a8  CTextureDictionary_GetClassID  [inline]
//   [ ] 0x9915b0  CTextureDictionary_GetSerializationFlags  [inline]
//   [ ] 0x991800  CTextureDictionary_IsKindOfClass  [inline]
//   [ ] 0x9920f8  CTextureDictionary_DeletingDestructor  [inline]
//   [ ] 0x992138  CTextureDictionary_Destructor  [inline]
//   [ ] 0x9a1b78  CTextureDictionary_Destroy  [inline]
#include "k2000/dictionaries/CTextureDictionary.h"

#include <cstring>

#include "Renderware/rwcore/RwStream.h"
#include "Renderware/rwcore/RwTexture.h"
#include "k2000/io/IKFile.h"
#include "k2000/misc/CKGameLoop.h"
#include "k2000/misc/Engine.h"
#include "k2000/render/TextureBank.h"

// 0x000c0bb8 CTextureDictionary_LoadPITextures
int32_t CTextureDictionary::LoadPITextures(IKFile* file, uint8_t resolveRasters) {
    m_pTexDictionary = RwTexDictionaryCreate();
    uint32_t count = 0;
    ReadU32LE(file, &count);
    while (count != 0) {
        --count;
        if (g_pEngine->m_gameLoop->IsExitRequested() != 0) return 0;
        char name[32];
        ReadRaw(file, name, 32);
        uint32_t unused = 0, filter = 0, addressing = 0;
        ReadU32LE(file, &unused);
        ReadU32LE(file, &filter);
        ReadU32LE(file, &addressing);
        RwShim_DdsRaster* raster = nullptr;
        if (resolveRasters != 0) {
            raster = RwShim_StreamReadDDSRaster(file->m_pRwStream);  // RwStreamReadDDSRaster_maybe 0x73a8d8
        } else {
            // RwStreamFindChunk(0x18) + RwImageStreamRead + Raster_CreateFromImage_maybe through the
            // texture bank. Not used by these files. STUB(C1.4): the image is skipped as a chunk.
            RwShim_FreeBlob(RwShim_ReadChunkBlob(file->m_pRwStream, 0x18));
        }
        if (raster == nullptr) continue;
        RwTexture* texture = RwTextureCreate(raster);
        std::memcpy(texture->name, name, sizeof(name));  // strcpy into texture +0x10
        texture->name[31] = 0;
        TextureBank::ApplyGraphicsFilterMode(texture);  // 0x000a5d78 (passed the engine's bank +0x40, not read)
        texture->filterAddressing = (texture->filterAddressing & 0xfffff0ffu) | ((filter & 0xfu) << 8);
        texture->filterAddressing = (texture->filterAddressing & 0xffff0fffu) | ((addressing & 0xfu) << 12);
        RwTexDictionaryAddTexture(m_pTexDictionary, texture);
    }
    return 1;
}

// 0x000c0f18 CTextureDictionary_Load
int32_t CTextureDictionary::Load(IKFile* file, int32_t type) {
    RwTexDictionarySetCurrent(nullptr);
    if (type == K_LEVEL_PLATEFORMS) {
        uint8_t isRwDictionary = 0;
        ReadRaw(file, &isRwDictionary, 1);
        if (isRwDictionary == 0) {
            if (LoadPITextures(file, 1) == 0) return 0;
        } else if (RwStreamFindChunk(file->m_pRwStream, 0x16, nullptr, nullptr) == 0) {
            m_pTexDictionary = nullptr;
        } else {
            // RwTexDictionaryStreamRead: not used by these files. STUB(C1.4): the dictionary's payload is
            // not read; the end-offset check would report the object.
            m_pTexDictionary = RwTexDictionaryCreate();
        }
    }
    RwTexDictionarySetCurrent(nullptr);
    return 1;
}
