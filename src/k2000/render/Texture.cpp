// Texture.cpp - reconstructed original translation unit: 0xc0370-0xc0948 (GAME_TOC1, main_toc1), 5 functions, 4 live.
// Primary owner: Texture (not a registered class)
// Other owners: FindTextureByName (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0xc0370  FUN_000c0370  [dead]
//   [ ] 0xc0518  Texture_SwapRasters  [dead: no pointer to its descriptor 0xb4cd88, no call]
//   [x] 0xc0570  Texture_ReplaceRasterFromImage_maybe
//   [ ] 0xc0700  Texture_ReloadFromImageFile_maybe  [dead: no pointer to its descriptor 0xb4cd98, no call]
//   [x] 0xc0828  FindTextureByName_maybe
#include <cstring>

#include "Renderware/rwcore/RwRaster.h"
#include "Renderware/rwcore/RwTexture.h"
#include "k2000/io/IKFile.h"
#include "k2000/misc/Engine.h"
#include "k2000/render/TextureBank.h"

namespace {

// Path_GetFileNamePtr: the part after the last '/' or '\\'.
const char* FileNamePart(const char* path) {
    const char* name = path;
    for (const char* p = path; *p != 0; ++p) {
        if (*p == '/' || *p == '\\') name = p + 1;
    }
    return name;
}

}  // namespace

// 0x000c0828 FindTextureByName_maybe: names longer than 31 characters are not looked up; otherwise RwTextureRead(name,
// NULL) (the current dictionary when there is one, else every dictionary, newest first; a reference added). The
// original then tests the raster's width and height for powers of two (the result only decides between two returns of
// the same texture).
void* FindTextureByName(const char* name) {
    if (std::strlen(FileNamePart(name)) > 0x1f) return nullptr;
    return RwTextureRead(name, nullptr);
}

// RwTexture +0x54 refCount + 1 (inlined at the callers).
void TextureRef_AddRef(void* texture) { ++static_cast<RwTexture*>(texture)->refCount; }

// RwTextureDestroy (TocBridge 0x98d430): a reference less; the last one destroys the texture and its raster.
void TextureRef_Release(void* texture) { RwTextureDestroy(static_cast<RwTexture*>(texture)); }

// 0x000c0570 Texture_ReplaceRasterFromImage_maybe: a raster made from the image (Raster_CreateFromImage_maybe with the
// texture bank, no mipmaps), set on the texture (RwTextureSetRaster), the old raster destroyed (RwRasterDestroy).
// With a path (Texture_ReloadFromImageFile_maybe's) its directory becomes the image path first (KFileSystem_SplitPath,
// RwImageSetPath); the texture bank passes none. The power-of-two walk over the image's width and height decides
// nothing (both branches set the raster). Returns 0 without a raster.
int32_t Texture_ReplaceRasterFromImage(RwTexture* texture, RwImage* image, const char* path) {
    RwRaster* raster = Raster_CreateFromImage(g_pEngine->m_textureBank, image, 0, path);
    if (raster == nullptr) return 0;
    RwRaster* old = texture->raster;
    RwTextureSetRaster(texture, raster);
    if (old != nullptr) RwRasterDestroy(old);
    return 1;
}
