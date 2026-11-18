// RwTexture.h - RenderWare 3.7 textures and texture dictionaries (core/src/batextur.c, babintex.c), ported from the PS3
// library code. The rasters they hold: RwRaster.h.
//
// The texture globals (RWTEXTUREGLOBAL, RWEngineInstance + [0xcf0158]): the list of every dictionary (+0x00, newest
// first), the texture and dictionary free lists (+0x08 / +0x0c), the current dictionary (+0x10), the read and find
// callbacks (+0x14 / +0x18), the mipmap flags and callbacks. The game sets no callback of its own (RwTextureSetFindCallBack
// / SetReadCallBack / RwImageRegisterImageFormat have no TocBridge), so RW's defaults run. RW's _rwTextureOpen also
// makes an empty dictionary the current one; the remake has no RW engine start, so the current dictionary starts null
// (CTextureDictionary_Load sets null before anything reads it).
#pragma once
#include <vector>

#include "Renderware/rwcore/RwCamera.h"
#include "Renderware/rwcore/RwRaster.h"

struct RwStream;

// RwLinkList (RW 3.7: a sentinel link).
struct RwLinkList {
    RwLLLink link;
};

// RwTexture (RW 3.7, 0x58; no texture plugin is registered).
struct RwTexture {
    RwRaster* raster;            // +0x00
    RwTexDictionary* dict;       // +0x04 the dictionary it is in (null: none)
    RwLLLink lInDictionary;      // +0x08 its link in the dictionary's list
    RwChar name[32];             // +0x10
    RwChar mask[32];             // +0x30
    RwUInt32 filterAddressing;   // +0x50 bits 0-7 filter mode, 8-11 U addressing, 12-15 V addressing
    RwInt32 refCount;            // +0x54
};
DOTD_ASSERT_SIZE(RwTexture, 0x58);
DOTD_ASSERT_OFFSET(RwTexture, lInDictionary, 0x08);
DOTD_ASSERT_OFFSET(RwTexture, name, 0x10);
DOTD_ASSERT_OFFSET(RwTexture, mask, 0x30);
DOTD_ASSERT_OFFSET(RwTexture, filterAddressing, 0x50);
DOTD_ASSERT_OFFSET(RwTexture, refCount, 0x54);

// RwTexDictionary (RW 3.7, 0x18).
struct RwTexDictionary {
    RwObject object;             // +0x00 type 6 (rwTEXDICTIONARY)
    RwLinkList texturesInDict;   // +0x08 its textures, the last added first
    RwLLLink lInInstance;        // +0x10 its link in the globals' list of dictionaries
};
DOTD_ASSERT_SIZE(RwTexDictionary, 0x18);
DOTD_ASSERT_OFFSET(RwTexDictionary, texturesInDict, 0x08);
DOTD_ASSERT_OFFSET(RwTexDictionary, lInInstance, 0x10);

typedef RwTexture* (*RwTextureCallBack)(RwTexture* texture, void* data);
typedef RwTexDictionary* (*RwTexDictionaryCallBack)(RwTexDictionary* dict, void* data);

// 0x007549d0 RwTextureCreate: wrap / wrap addressing, rwFILTERNEAREST (0x1101), one reference, in no dictionary.
RwTexture* RwTextureCreate(RwRaster* raster);
// 0x007548c0 RwTextureDestroy: one reference less; the last one takes the texture out of its dictionary and destroys
// its raster and the texture.
RwBool RwTextureDestroy(RwTexture* texture);
// 0x007532b0 RwTextureSetRaster (the device's rwSTANDARDTEXTURESETRASTER 0x739858 stores it).
RwTexture* RwTextureSetRaster(RwTexture* texture, RwRaster* raster);
// 0x007541c0 RwTextureSetName / 0x007540c8 RwTextureSetMaskName: rwstrncpy of 32 characters, cut at 31 when longer.
RwTexture* RwTextureSetName(RwTexture* texture, const RwChar* name);
RwTexture* RwTextureSetMaskName(RwTexture* texture, const RwChar* mask);
// 0x00754be0 RwTextureRead: the find callback's texture with a reference added, or the read callback's (added to the
// current dictionary); null when neither has one.
RwTexture* RwTextureRead(const RwChar* name, const RwChar* maskName);

// 0x00746870 RwTextureStreamRead: after the texture chunk (6) was found.
RwTexture* RwTextureStreamRead(RwStream* stream);
// 0x007531e8 / 0x00753210 / 0x00753238 / 0x00753260 Rw{Set,Get}{,Auto}Mipmapping
RwBool RwTextureSetMipmapping(RwBool enable);
RwBool RwTextureGetMipmapping();
RwBool RwTextureSetAutoMipmapping(RwBool enable);
RwBool RwTextureGetAutoMipmapping();

// 0x00753788 RwTexture_RasterGenerateMipmaps_maybe (RwTextureRasterGenerateMipmaps): the texture module's mipmap
// callback (TextureRasterDefaultBuildMipmaps) on the raster; null when it fails.
RwRaster* RwTextureRasterGenerateMipmaps(RwRaster* raster, RwImage* image);

// 0x00754a90 RwTexDictionaryCreate: an empty dictionary at the head of the globals' list.
RwTexDictionary* RwTexDictionaryCreate();
// 0x00754da0 RwTexDictionaryDestroy: no longer current; RwTextureDestroy on each texture; out of the list.
RwBool RwTexDictionaryDestroy(RwTexDictionary* dict);
// 0x00753490 RwTexDictionaryAddTexture (out of its previous dictionary first; added at the head).
RwTexture* RwTexDictionaryAddTexture(RwTexDictionary* dict, RwTexture* texture);
// 0x007534e8 RwTexDictionaryRemoveTexture
RwTexture* RwTexDictionaryRemoveTexture(RwTexture* texture);
// 0x00753520 RwTexDictionaryFindNamedTexture: case-blind (a-z folded to upper case), as rwstrcmpi.
RwTexture* RwTexDictionaryFindNamedTexture(RwTexDictionary* dict, const RwChar* name);
// 0x00753628 RwTexDictionarySetCurrent / 0x00753650 RwTexDictionaryGetCurrent
RwTexDictionary* RwTexDictionarySetCurrent(RwTexDictionary* dict);
RwTexDictionary* RwTexDictionaryGetCurrent();
// 0x00753338 RwTexDictionaryForAllTextures: until the callback returns null.
RwTexDictionary* RwTexDictionaryForAllTextures(RwTexDictionary* dict, RwTextureCallBack callBack, void* data);
// 0x007533e0 RwTexDictionary_ForAllTexDictionaries_maybe (RwTexDictionaryForAllTexDictionaries): newest first.
RwBool RwTexDictionaryForAllTexDictionaries(RwTexDictionaryCallBack callBack, void* data);
