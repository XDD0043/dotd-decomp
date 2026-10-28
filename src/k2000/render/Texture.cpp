// Texture.cpp - reconstructed original translation unit: 0xc0370-0xc0948 (GAME_TOC1, main_toc1), 5 functions, 4 live.
// Primary owner: Texture (not a registered class)
// Other owners: FindTextureByName (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0xc0370  FUN_000c0370  [dead]
//   [ ] 0xc0518  Texture_SwapRasters
//   [x] 0xc0570  Texture_ReplaceRasterFromImage_maybe
//   [ ] 0xc0700  Texture_ReloadFromImageFile_maybe
//   [x] 0xc0828  FindTextureByName_maybe
#include <cstring>

#include "Renderware/rwcore/RwStream.h"
#include "Renderware/rwcore/RwTexture.h"
#include "k2000/io/IKFile.h"

namespace {

// Path_GetFileNamePtr: the part after the last '/' or '\\'.
const char* FileNamePart(const char* path) {
    const char* name = path;
    for (const char* p = path; *p != 0; ++p) {
        if (*p == '/' || *p == '\\') name = p + 1;
    }
    return name;
}

// RwTextureRead(name, NULL) as the engine sets it up: the texture by name in the loaded dictionaries,
// with a reference added (RW: the dictionary's texture, refCount + 1). STUB: the PS3 searches the current
// dictionary, then the engine's find callback over the texture bank; here every dictionary in load order
// (the shim's dictionaries: LVL000's CTextureDictionary, the font dictionaries, ...), case-blind.
RwTexture* TextureRead(const char* name) {
    RwTexDictionary* current = RwTexDictionaryGetCurrent();
    if (current != nullptr) {
        if (RwTexture* texture = RwTexDictionaryFindNamedTexture(current, name)) {
            ++texture->refCount;
            return texture;
        }
    }
    for (RwTexDictionary* dictionary : RwShim_AllTexDictionaries()) {
        if (RwTexture* texture = RwTexDictionaryFindNamedTexture(dictionary, name)) {
            ++texture->refCount;
            return texture;
        }
    }
    return nullptr;
}

}  // namespace

// 0x000c0828 FindTextureByName_maybe: names longer than 31 characters are not looked up. The original then
// tests the raster's width and height for powers of two (the result only decides between two returns of
// the same texture).
void* FindTextureByName(const char* name) {
    if (std::strlen(FileNamePart(name)) > 0x1f) return nullptr;
    return TextureRead(name);
}

// RwTexture +0x54 refCount + 1 (inlined at the callers).
void TextureRef_AddRef(void* texture) { ++static_cast<RwTexture*>(texture)->refCount; }

// RwTextureDestroy: the reference count - 1 (the texture stays in its dictionary; the shim's dictionaries
// own their textures).
void TextureRef_Release(void* texture) { --static_cast<RwTexture*>(texture)->refCount; }

// 0x000c0570 Texture_ReplaceRasterFromImage_maybe: a raster made from the image (Raster_CreateFromImage_maybe
// with the texture bank), set on the texture (RwTextureSetRaster), the old raster destroyed (RwRasterDestroy).
// `path` (the image path for RwImageSetPath) is always null from the texture bank. The power-of-two walk
// over the image's width and height decides nothing (both branches set the raster). Returns 0 without a
// raster. The old raster's device texture is not released (the shim never frees device textures).
int32_t Texture_ReplaceRasterFromImage(RwTexture* texture, const RwShim_Blob* image, const char* /*path*/) {
    RwShim_DdsRaster* raster = RwShim_RasterFromImageBlob(image);
    if (raster == nullptr) return 0;
    RwShim_DdsRaster* old = texture->raster;
    texture->raster = raster;
    delete old;
    return 1;
}
