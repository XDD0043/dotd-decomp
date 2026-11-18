// RwTexture.cpp - RW 3.7 textures and texture dictionaries. See RwTexture.h.
#include "Renderware/rwcore/RwTexture.h"

#include <cstddef>
#include <cstring>

#include "Renderware/rwcore/RwSList.h"
#include "Renderware/rwcore/RwStream.h"
#include "k2000/core/Stub.h"

namespace {

// RWTEXTUREGLOBAL: the dictionaries (+0x00) and the current one (+0x10).
RwLinkList g_texDictList = {{&g_texDictList.link, &g_texDictList.link}};
RwTexDictionary* g_currentTexDict = nullptr;

// The texture (0x30006) and dictionary (0x30016) free lists. An RW free list keeps its blocks: a destroyed texture's or
// dictionary's memory stays the free list's, so the original's writes into one after its destroy (TextureBank_Release,
// a texture outliving its dictionary) land in memory that is still there. Freed entries are kept for reuse here too.
std::vector<void*> g_freeTextures;
std::vector<void*> g_freeDictionaries;

// RwFreeListFree: the entry's bit in its block cleared, so freeing an entry twice (a dictionary destroyed twice, as
// _rt2dFontClose can after CManager2d_UnloadLocalizedFonts) frees it once.
void FreeListFree(std::vector<void*>& freeEntries, void* entry) {
    for (void* free : freeEntries) {
        if (free == entry) return;
    }
    freeEntries.push_back(entry);
}

void* FreeListAlloc(std::vector<void*>& freeEntries, RwUInt32 size, RwUInt32 hint) {
    if (!freeEntries.empty()) {
        void* entry = freeEntries.back();
        freeEntries.pop_back();
        return entry;
    }
    return RwMalloc(size, hint);
}

void LinkRemove(RwLLLink* link) {
    link->prev->next = link->next;
    link->next->prev = link->prev;
}

// The head insertion of rwLinkListAddLLLink.
void LinkAddHead(RwLinkList* list, RwLLLink* link) {
    link->next = list->link.next;
    link->prev = &list->link;
    list->link.next->prev = link;
    list->link.next = link;
}

RwTexture* TextureOfLink(RwLLLink* link) {
    return reinterpret_cast<RwTexture*>(reinterpret_cast<RwUInt8*>(link) - offsetof(RwTexture, lInDictionary));
}

RwTexDictionary* DictionaryOfLink(RwLLLink* link) {
    return reinterpret_cast<RwTexDictionary*>(reinterpret_cast<RwUInt8*>(link) - offsetof(RwTexDictionary, lInInstance));
}

// rwstrcmpi as the PS3 build inlines it: a-z folded to upper case.
bool NamesEqual(const RwChar* a, const RwChar* b) {
    for (;;) {
        RwChar ca = *a++;
        RwChar cb = *b++;
        if (static_cast<RwUInt8>(ca - 'a') < 26) ca = static_cast<RwChar>(ca - 0x20);
        if (static_cast<RwUInt8>(cb - 'a') < 26) cb = static_cast<RwChar>(cb - 0x20);
        if (ca != cb) return false;
        if (ca == 0) return true;
    }
}

RwTexture* FindInDictionary(RwTexDictionary* dict, const RwChar* name) {
    RwLLLink* end = &dict->texturesInDict.link;
    for (RwLLLink* link = end->next; link != end; link = link->next) {
        RwTexture* texture = TextureOfLink(link);
        if (NamesEqual(texture->name, name)) return texture;
    }
    return nullptr;
}

// 0x00754ef8 _rwTextureFindNamedTexture_maybe (TextureDefaultFind): the current dictionary only when there is one,
// else every dictionary, newest first.
RwTexture* TextureDefaultFind(const RwChar* name) {
    if (g_currentTexDict != nullptr) return FindInDictionary(g_currentTexDict, name);
    for (RwLLLink* link = g_texDictList.link.next; link != &g_texDictList.link; link = link->next) {
        if (RwTexture* texture = FindInDictionary(DictionaryOfLink(link), name)) return texture;
    }
    return nullptr;
}

// 0x00755768 RwTexture_DefaultReadCallback_maybe (TextureDefaultRead): the name and mask copied (255 characters at
// most), then the image read through RwImageRead from the image path with the registered image formats (and the
// mipmap levels through the mipmap name callback when mipmapping is on), made a raster and a texture. The game
// registers no image format (RwImageRegisterImageFormat 0x74d900 is not called), so the image read fails and the
// callback returns null.
RwTexture* TextureDefaultRead(const RwChar* /*name*/, const RwChar* /*maskName*/) { return nullptr; }

RwBool g_haveTexMipmaps = 0;      // RWTEXTUREGLOBAL +0x1c
RwBool g_generateTexMipmaps = 0;  // +0x20

// _rwStringStreamFindAndRead (rwstring.c): the next string chunk (rwID_STRING 2: its bytes; rwID_UNICODESTRING 0x13:
// each 16-bit character's low byte), other chunks skipped; null at the end of the stream or a bad version.
RwChar* StringStreamFindAndRead(RwChar* string, RwStream* stream) {
    uint32_t type = 0, length = 0, version = 0;
    while (_rwStreamReadChunkHeader(stream, &type, &length, &version, nullptr) != 0) {
        if (version < 0x35000u || version > 0x37002u) return nullptr;  // E_RW_BADVERSION
        if (type == 2) {
            if (RwStreamRead(stream, string, length) != length) return nullptr;
            return string;
        }
        if (type == 0x13) {
            for (uint32_t i = 0; i < length / 2; ++i) {
                uint16_t unit = 0;
                if (RwStreamRead(stream, &unit, 2) != 2) return nullptr;
                string[i] = static_cast<RwChar>(unit);
            }
            return string;
        }
        if (RwStreamSkip(stream, length) == nullptr) return nullptr;
    }
    return nullptr;
}

// _rwPluginRegistrySkipDataChunks: the extension chunk (3) skipped whole.
bool SkipDataChunks(RwStream* stream) {
    uint32_t length = 0, version = 0;
    if (RwStreamFindChunk(stream, 3, &length, &version) == 0) return false;
    return RwStreamSkip(stream, length) != nullptr;
}

// 0x0073b0b0 Texture_FindAndLoadDDS_maybe: "<name>.dds" looked for in each directory of the image path (RwImageGetPath,
// ';'-separated; the name's own directory when it is absolute) and read through RwStreamOpen(rwSTREAMFILENAME) and
// RwStreamReadDDSRaster (0x73afa8 Texture_LoadFromDDSFile_maybe: filter rwFILTERLINEARMIPLINEAR for a mipmapped raster,
// rwFILTERLINEAR otherwise). STUB(left): the game's files are all in KP3 containers (USRDIR holds no loose DDS file),
// so on the PS3 every lookup fails; the remake has no RtFS file stream to look with and returns null.
RwTexture* TextureFindAndLoadDDS(const RwChar* /*name*/, const RwChar* /*maskName*/) { return nullptr; }

// TextureRasterDefaultBuildMipmaps (batextur.c; the default mipmap callback, RWTEXTUREGLOBAL +0x2c): each level
// below the first locked and filled from the previous level's image resampled (RwImageCreateResample, palettised
// again for a palettised raster), the AUTOMIPMAP bit off meanwhile. A raster of one level (no rwRASTERFORMATMIPMAP)
// has nothing to build. STUB(dead code): the levels themselves are reached only through Raster_CreateFromImage_maybe
// with mipmaps, i.e. CTextureDictionary_LoadPITextures' image branch, which the binary never runs (its only caller,
// CTextureDictionary_Load 0xc0fa8, passes resolveRasters = 1); not ported, that fails.
RwRaster* TextureRasterDefaultBuildMipmaps(RwRaster* raster, RwImage* /*image*/) {
    if (RwRasterGetNumLevels(raster) <= 1) return raster;
    DOTD_STUB_ONCE("TextureRasterDefaultBuildMipmaps (CTextureDictionary's image branch, dead in the binary)");
    return nullptr;
}

}  // namespace

// 0x00753788 RwTexture_RasterGenerateMipmaps_maybe
RwRaster* RwTextureRasterGenerateMipmaps(RwRaster* raster, RwImage* image) {
    return TextureRasterDefaultBuildMipmaps(raster, image);
}

// 0x007549d0 RwTextureCreate
RwTexture* RwTextureCreate(RwRaster* raster) {
    RwTexture* texture = static_cast<RwTexture*>(FreeListAlloc(g_freeTextures, sizeof(RwTexture), 0x30006));
    if (texture == nullptr) return nullptr;
    texture->mask[0] = 0;
    texture->raster = raster;
    texture->refCount = 1;
    texture->filterAddressing = 0x1101;
    texture->dict = nullptr;
    texture->name[0] = 0;
    return texture;  // _rwPluginRegistryInitObject: no texture plugin
}

// 0x007548c0 RwTextureDestroy
RwBool RwTextureDestroy(RwTexture* texture) {
    const RwInt32 count = texture->refCount;
    texture->refCount = count - 1;
    if (count - 1 > 0) return 1;
    texture->refCount = count;
    if (texture->dict != nullptr) LinkRemove(&texture->lInDictionary);
    if (texture->raster != nullptr) {
        RwRasterDestroy(texture->raster);
        texture->raster = nullptr;
    }
    texture->refCount -= 1;
    FreeListFree(g_freeTextures, texture);
    return 1;
}

// 0x007532b0 RwTextureSetRaster: null clears it; otherwise the device stores it (0x00739858
// RwPSGL_DeviceStd_SetValueReturn1_maybe).
RwTexture* RwTextureSetRaster(RwTexture* texture, RwRaster* raster) {
    texture->raster = raster;
    return texture;
}

// 0x007541c0 RwTextureSetName
RwTexture* RwTextureSetName(RwTexture* texture, const RwChar* name) {
    std::strncpy(texture->name, name, 32);
    if (std::strlen(name) > 0x1f) texture->name[31] = 0;  // error 0x8000001e
    return texture;
}

// 0x007540c8 RwTextureSetMaskName
RwTexture* RwTextureSetMaskName(RwTexture* texture, const RwChar* mask) {
    std::strncpy(texture->mask, mask, 32);
    if (std::strlen(mask) > 0x1f) texture->mask[31] = 0;  // error 0x8000001e
    return texture;
}

// 0x00754be0 RwTextureRead
RwTexture* RwTextureRead(const RwChar* name, const RwChar* maskName) {
    RwTexture* texture = TextureDefaultFind(name);
    if (texture != nullptr) {
        ++texture->refCount;
        return texture;
    }
    texture = TextureDefaultRead(name, maskName);
    if (texture == nullptr) return nullptr;  // error 0x16 (the name and mask, "(null)" without one)
    if (g_currentTexDict != nullptr) RwTexDictionaryAddTexture(g_currentTexDict, texture);
    return texture;
}

// 0x00754a90 RwTexDictionaryCreate
RwTexDictionary* RwTexDictionaryCreate() {
    RwTexDictionary* dict =
        static_cast<RwTexDictionary*>(FreeListAlloc(g_freeDictionaries, sizeof(RwTexDictionary), 0x30016));
    if (dict == nullptr) return nullptr;
    dict->object.type = 6;
    dict->object.privateFlags = 0;
    dict->object.parent = nullptr;
    dict->object.subType = 0;
    dict->object.flags = 0;
    LinkAddHead(&g_texDictList, &dict->lInInstance);
    dict->texturesInDict.link.prev = &dict->texturesInDict.link;
    dict->texturesInDict.link.next = &dict->texturesInDict.link;
    return dict;  // _rwPluginRegistryInitObject: no dictionary plugin
}

// 0x00754da0 RwTexDictionaryDestroy. A texture with references left stays alive with its link into the destroyed
// dictionary (RW's behaviour; the free list keeps the dictionary's memory, see above).
RwBool RwTexDictionaryDestroy(RwTexDictionary* dict) {
    if (g_currentTexDict == dict) g_currentTexDict = nullptr;
    RwLLLink* end = &dict->texturesInDict.link;
    for (RwLLLink* link = end->next; link != end;) {
        RwTexture* texture = TextureOfLink(link);
        link = link->next;
        if (RwTextureDestroy(texture) == 0) break;
    }
    LinkRemove(&dict->lInInstance);
    FreeListFree(g_freeDictionaries, dict);
    return 1;
}

// 0x00753490 RwTexDictionaryAddTexture
RwTexture* RwTexDictionaryAddTexture(RwTexDictionary* dict, RwTexture* texture) {
    if (texture->dict != nullptr) LinkRemove(&texture->lInDictionary);
    texture->dict = dict;
    LinkAddHead(&dict->texturesInDict, &texture->lInDictionary);
    return texture;
}

// 0x007534e8 RwTexDictionaryRemoveTexture
RwTexture* RwTexDictionaryRemoveTexture(RwTexture* texture) {
    if (texture->dict == nullptr) return texture;
    texture->dict = nullptr;
    LinkRemove(&texture->lInDictionary);
    return texture;
}

// 0x00753520 RwTexDictionaryFindNamedTexture
RwTexture* RwTexDictionaryFindNamedTexture(RwTexDictionary* dict, const RwChar* name) {
    return FindInDictionary(dict, name);
}

// 0x00753628 RwTexDictionarySetCurrent
RwTexDictionary* RwTexDictionarySetCurrent(RwTexDictionary* dict) {
    g_currentTexDict = dict;
    return dict;
}

// 0x00753650 RwTexDictionaryGetCurrent
RwTexDictionary* RwTexDictionaryGetCurrent() { return g_currentTexDict; }

// 0x00753338 RwTexDictionaryForAllTextures (the next link read before the callback)
RwTexDictionary* RwTexDictionaryForAllTextures(RwTexDictionary* dict, RwTextureCallBack callBack, void* data) {
    RwLLLink* end = &dict->texturesInDict.link;
    for (RwLLLink* link = end->next; link != end;) {
        RwTexture* texture = TextureOfLink(link);
        link = link->next;
        if (callBack(texture, data) == nullptr) break;
    }
    return dict;
}

// 0x007533e0 RwTexDictionary_ForAllTexDictionaries_maybe
RwBool RwTexDictionaryForAllTexDictionaries(RwTexDictionaryCallBack callBack, void* data) {
    for (RwLLLink* link = g_texDictList.link.next; link != &g_texDictList.link;) {
        RwTexDictionary* dict = DictionaryOfLink(link);
        link = link->next;
        if (callBack(dict, data) == nullptr) break;
    }
    return 1;
}

// 0x007531e8 RwTextureSetMipmapping .. 0x00753260 RwTextureGetAutoMipmapping (RWTEXTUREGLOBAL haveTexMipmaps /
// generateTexMipmaps): read by the texture read callback only.
RwBool RwTextureSetMipmapping(RwBool enable) {
    g_haveTexMipmaps = enable;
    return 1;
}
RwBool RwTextureGetMipmapping() { return g_haveTexMipmaps; }
RwBool RwTextureSetAutoMipmapping(RwBool enable) {
    g_generateTexMipmaps = enable;
    return 1;
}
RwBool RwTextureGetAutoMipmapping() { return g_generateTexMipmaps; }

// 0x00746870 RwTextureStreamRead (after the texture chunk was found): the struct chunk's filter / addressing word (a V
// addressing of 0 takes the U one), the mipmapping state set from its filter mode for the read, the name and the mask
// (_rwStringStreamFindAndRead), RwTextureRead, else Texture_FindAndLoadDDS_maybe; a texture the read made (one
// reference) takes the word's low 16 bits and its plugin chunks, any other skips them. Null when neither finds it.
RwTexture* RwTextureStreamRead(RwStream* stream) {
    uint32_t size = 0, version = 0;
    if (RwStreamFindChunk(stream, 1, &size, &version) == 0) return nullptr;
    if (version - 0x35000u > 0x2002u) return nullptr;  // error 0x80000004
    uint32_t flags[2] = {0, 0};
    if (RwStreamRead(stream, flags, size) != size) return nullptr;
    uint32_t word = flags[0];  // RwMemNative32
    if (((word >> 12) & 0xf) == 0) word |= (word & 0xf00) << 4;
    const RwBool mipmapping = RwTextureGetMipmapping();
    const RwBool autoMipmapping = RwTextureGetAutoMipmapping();
    if ((word & 0xff) - 3u <= 3u) {
        RwTextureSetMipmapping(1);
        RwTextureSetAutoMipmapping((word & 0x10000) == 0 ? 1 : 0);
    } else {
        RwTextureSetMipmapping(0);
        RwTextureSetAutoMipmapping(0);
    }
    RwChar name[0x80];
    RwChar mask[0x80];
    if (StringStreamFindAndRead(name, stream) == nullptr || StringStreamFindAndRead(mask, stream) == nullptr) {
        RwTextureSetMipmapping(mipmapping);
        RwTextureSetAutoMipmapping(autoMipmapping);
        return nullptr;
    }
    RwTexture* texture = RwTextureRead(name, mask);
    if (texture == nullptr) texture = TextureFindAndLoadDDS(name, mask);
    if (texture == nullptr) {
        SkipDataChunks(stream);
        RwTextureSetMipmapping(mipmapping);
        RwTextureSetAutoMipmapping(autoMipmapping);
        return nullptr;
    }
    RwTextureSetMipmapping(mipmapping);
    RwTextureSetAutoMipmapping(autoMipmapping);
    bool ok;
    if (texture->refCount == 1) {
        texture->filterAddressing = word & 0xffff;
        ok = SkipDataChunks(stream);  // _rwPluginRegistryReadDataChunks: no texture plugin reads a chunk
    } else {
        ok = SkipDataChunks(stream);
    }
    return ok ? texture : nullptr;
}
