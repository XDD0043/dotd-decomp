// font.cpp - RW 3.7 tool/2d/font.c, ported from the PS3 library code (0x70cb48-0x711a20). See Rt2d.h.
//
// Characters: with font flag bit 1 a character is two bytes, high byte first ((s[0] << 8) | s[1]), else
// one byte; a string ends at a character <= 0. Characters 0..0x7f map through aCharIndex, the others
// through uCharIndex[c - uCharOffset] (out of range: skipped); a negative index has no glyph.
//
// Not ported (the front end never reaches them): Rt2dFontSetPath 0x70cb68, the global show callback
// 0x70cc68 / 0x70cc78 / 0x70cc88, FUN_0070cd18, Rt2dFont_CollectMappedCharacters_maybe 0x70cd20,
// _rt2dFontDictionaryFind_maybe 0x70d028 (the name -> font form), FUN_0070d0e8, KStub_Return1_70d0f8,
// Rt2dFont_CheckStringGlyphs_maybe 0x70d100, _rt2dFontGetStringWidthAndCount_maybe 0x70d7e0,
// Rt2dFontGetHeight_maybe 0x70db60, Rt2dFontStreamGetSize 0x70e608, Rt2dFontStreamWrite 0x70e830,
// Rt2dFontRead 0x70fa60 (fonts from .met files: the game streams its fonts), FUN_007119e0.
#include "Renderware/rt2d/Rt2dInternal.h"
#include "Renderware/rwcore/RwTexture.h"

DOTD_ASSERT_OFFSET(Rt2dFont, textures, 0x14);
DOTD_ASSERT_OFFSET(Rt2dFont, aCharIndex, 0x24);
DOTD_ASSERT_OFFSET(Rt2dFont, uCharOffset, 0x124);
DOTD_ASSERT_OFFSET(Rt2dFont, uCharIndex, 0x12c);
DOTD_ASSERT_OFFSET(Rt2dFont, charMap, 0x134);
DOTD_ASSERT_OFFSET(Rt2dFont, fontshowCB, 0x138);
DOTD_ASSERT_OFFSET(rt2dCharRect, path, 0x18);
DOTD_ASSERT_OFFSET(rt2dCharRect, charpage, 0x1c);

// The two show callbacks (Rt2dFont +0x138; render code below the readers).
Rt2dFont* _rt2dFontShowBitmap(Rt2dFont* font, const RwChar* string, RwReal height, RwV2d* anchor, Rt2dBrush* brush);
Rt2dFont* _rt2dFontShowOutline(Rt2dFont* font, const RwChar* string, RwReal height, RwV2d* anchor, Rt2dBrush* brush);

namespace {

// 0x00c458c4: the font and dictionary-node free-list blocks ({8, 1} and {0x10, 1}).
RwInt32 s_fontFreeListBlockSize = 8;
RwInt32 s_fontFreeListPreallocBlocks = 1;
RwInt32 s_dictNodeFreeListBlockSize = 0x10;
RwInt32 s_dictNodeFreeListPreallocBlocks = 1;

// 0x00ced5c4: set by _rt2dFontOpen, cleared by _rt2dFontClose (nothing else reads it in the front end).
RwInt32 s_fontOpen = 0;

// 0x00ad14a0: the default font path.
const RwChar kDefaultFontPath[] = "fonts\\";

// RwTextureRead(name, null) 0x754be0 as the font reader calls it (the font texture dictionary is current then).
RwTexture* TextureRead(const RwChar* name) { return RwTextureRead(name, nullptr); }

// RwTextureDestroy 0x7548c0 as the font calls it.
void TextureRelease(RwTexture* texture) { RwTextureDestroy(texture); }

}  // namespace

// The character at s and the step to the next one (the decoding inlined in every string walk). The PS3
// reads a 2-byte character as (s[0] << 8) | s[1]: the 16-bit unit as stored in its (big-endian) memory.
// The remake keeps the K side's UTF-16 text in host order (CKFlashText), so the unit is read in host
// order: the same character for the same stored text.
RwInt32 _rt2dFontDecodeChar(const Rt2dFont* font, const RwChar* s, RwInt32* step) {
    if ((font->flag & 2) != 0) {
        *step = 2;
        uint16_t unit;
        std::memcpy(&unit, s, sizeof(unit));
        return unit;
    }
    *step = 1;
    return static_cast<RwUInt8>(s[0]);
}

// The glyph index of character c (-1: none). The uCharIndex range check is the PS3's: below the offset
// or at/after the count, no glyph.
RwInt32 _rt2dFontCharIndex(const Rt2dFont* font, RwInt32 c) {
    if (c <= 0x7f) return font->aCharIndex[c];
    const RwInt32 i = c - font->uCharOffset;
    if (i < 0 || font->uCharIndexCount <= i) return -1;
    return font->uCharIndex[i];
}

// 0x0070cb48 Rt2dFontSetFreeListCreateParams / 0x0070cb58 Rt2dFontDictNodeSetFreeListCreateParams_maybe
void Rt2dFontSetFreeListCreateParams(RwInt32 blockSize, RwInt32 numBlocksToPrealloc) {
    s_fontFreeListPreallocBlocks = numBlocksToPrealloc;
    s_fontFreeListBlockSize = blockSize;
}
void Rt2dFontDictNodeSetFreeListCreateParams(RwInt32 blockSize, RwInt32 numBlocksToPrealloc) {
    s_dictNodeFreeListPreallocBlocks = numBlocksToPrealloc;
    s_dictNodeFreeListBlockSize = blockSize;
}

// 0x0070f810 _rt2dFontOpen_maybe: the font and dictionary-node free lists, the font path (0x51 bytes,
// "fonts\"), the font index table (per glyph quad q: 4q, 4q+2, 4q+3, 4q, 4q+3, 4q+1), an empty font
// dictionary, a new texture dictionary for the fonts (also the current one), Rt2dFontRead as the reader.
RwBool _rt2dFontOpen() {
    Rt2dGlobalVars& g = rt2dGlobals;
    g.fontFreeList = RwFreeListCreateAndPreallocateSpace(sizeof(Rt2dFont), s_fontFreeListBlockSize, 4,
                                                         s_fontFreeListPreallocBlocks, nullptr, 0x40199);
    if (g.fontFreeList == nullptr) return 0;
    g.fontDictNodeFreeList = RwFreeListCreateAndPreallocateSpace(sizeof(_rt2dFontDictionaryNode),
                                                                 s_dictNodeFreeListBlockSize, 4,
                                                                 s_dictNodeFreeListPreallocBlocks, nullptr, 0x40190);
    if (g.fontDictNodeFreeList == nullptr) return 0;
    g.fontPath = static_cast<RwChar*>(RwMalloc(0x51, 0x1040190));
    if (g.fontPath == nullptr) return 0;
    g.fontPathSize = 0x51;
    const RwUInt32 length = static_cast<RwUInt32>(rwstrlen(kDefaultFontPath)) + 1;
    bool copy = true;
    if (g.fontPathSize < length) {
        RwChar* grown = static_cast<RwChar*>(RwRealloc(g.fontPath, length, 0x1040190));
        if (grown == nullptr) {
            copy = false;
        } else {
            g.fontPath = grown;
            g.fontPathSize = length;
        }
    }
    if (copy) rwstrcpy(g.fontPath, kDefaultFontPath);
    for (RwUInt32 q = 0; q < 0x40; ++q) {
        RwImVertexIndex* idx = &g.fonttopo[q * 6];
        const RwImVertexIndex v = q * 4;
        idx[0] = v;
        idx[3] = v;
        idx[5] = v + 1;
        idx[1] = v + 2;
        idx[4] = v + 3;
        idx[2] = v + 3;
    }
    g.fontDictionary = nullptr;
    RwTexDictionary* dictionary = RwTexDictionaryCreate();
    g.currFontTexDictionary = dictionary;
    g.fontTexDictionary = dictionary;
    g.fontReadFunc = nullptr;  // Rt2dFontRead 0x70fa60 (not ported)
    s_fontOpen = 1;
    g.uCharIndexSize = 0;
    g.uCharIndex = nullptr;
    return 1;
}

// 0x0070de08 _rt2dFontClose_maybe: every dictionary entry (its name and font), the texture dictionary _rt2dFontOpen
// made (destroyed when there is one), the free lists, the buffers.
RwBool _rt2dFontClose() {
    Rt2dGlobalVars& g = rt2dGlobals;
    _rt2dFontDictionaryNode* node = g.fontDictionary;
    while (node != nullptr) {
        RwFree(node->name);
        Rt2dFontDestroy(node->font);
        _rt2dFontDictionaryNode* next = node->next;
        RwFreeListFree(g.fontDictNodeFreeList, node);
        node = next;
    }
    g.fontDictionary = nullptr;
    if (g.fontTexDictionary != nullptr) RwTexDictionaryDestroy(g.fontTexDictionary);
    g.fontTexDictionary = nullptr;
    g.currFontTexDictionary = nullptr;
    RwFreeListDestroy(g.fontDictNodeFreeList);
    g.fontDictNodeFreeList = nullptr;
    RwFreeListDestroy(g.fontFreeList);
    g.fontFreeList = nullptr;
    if (g.uCharIndex != nullptr) RwFree(g.uCharIndex);
    g.uCharIndex = nullptr;
    if (g.fontPath != nullptr) RwFree(g.fontPath);
    g.fontPathSize = 0;
    g.fontPath = nullptr;
    s_fontOpen = 0;
    return 1;
}

// 0x0070cd08 Rt2dFontSetIntergapSpacing_maybe
Rt2dFont* Rt2dFontSetIntergapSpacing(Rt2dFont* font, RwReal gap) {
    font->intergap = gap;
    return font;
}

// 0x0070d220 Rt2dFontTexDictionarySet / 0x0070d230 Rt2dFontTexDictionaryGet_maybe: the dictionary the
// bitmap fonts' textures are read from (currFontTexDictionary, +0xa20).
RwTexDictionary* Rt2dFontTexDictionarySet(RwTexDictionary* texDict) {
    rt2dGlobals.currFontTexDictionary = texDict;
    return texDict;
}
RwTexDictionary* Rt2dFontTexDictionaryGet() { return rt2dGlobals.currFontTexDictionary; }

// 0x0070cde0 _rt2dFontDictionaryAdd_maybe: a new entry (a copy of name) at the head of the dictionary.
// Returns the font. BUG(original): the node allocation is not checked.
Rt2dFont* _rt2dFontDictionaryAdd(Rt2dFont* font, const RwChar* name) {
    Rt2dGlobalVars& g = rt2dGlobals;
    _rt2dFontDictionaryNode* node =
        static_cast<_rt2dFontDictionaryNode*>(RwFreeListAlloc(g.fontDictNodeFreeList, 0x30190));
    node->font = font;
    node->name = static_cast<RwChar*>(RwMalloc(static_cast<RwUInt32>(rwstrlen(name)) + 1, 0x30190));
    rwstrcpy(node->name, name);
    node->next = g.fontDictionary;
    g.fontDictionary = node;
    return node->font;
}

// 0x0070cf08 _rt2dFontDictionaryRemove_maybe: unlinks and frees the entry of font (not the font).
// Returns the font, or null when it is not in the dictionary.
Rt2dFont* _rt2dFontDictionaryRemove(Rt2dFont* font) {
    Rt2dGlobalVars& g = rt2dGlobals;
    _rt2dFontDictionaryNode* node = g.fontDictionary;
    if (node == nullptr) return nullptr;
    if (node->font == font) {
        g.fontDictionary = node->next;
    } else {
        _rt2dFontDictionaryNode* prev = node;
        for (node = node->next; node != nullptr && node->font != font; node = node->next) prev = node;
        if (node == nullptr) return nullptr;
        prev->next = node->next;
    }
    RwFree(node->name);
    RwFreeListFree(g.fontDictNodeFreeList, node);
    return font;
}

// 0x0070e770 _rt2dFontDictionaryFindEntry_maybe: the entry named name (strcmp), or null.
_rt2dFontDictionaryNode* _rt2dFontDictionaryFindEntry(const RwChar* name) {
    for (_rt2dFontDictionaryNode* node = rt2dGlobals.fontDictionary; node != nullptr; node = node->next) {
        if (rwstrcmp(name, node->name) == 0) return node;
    }
    return nullptr;
}

// 0x0070d9a0 Rt2dFontDestroy: the glyph paths, the character map, the unicode index table, the textures,
// then the font. 0 for a null font.
RwBool Rt2dFontDestroy(Rt2dFont* font) {
    if (font == nullptr) return 0;
    if (font->charMap != nullptr) {
        rt2dCharRect* rect = static_cast<rt2dCharRect*>(_rwSListGetArray(font->charMap));
        for (RwInt32 i = 0; i < font->charCount; ++i) {
            if (rect[i].path != nullptr) {
                Rt2dPathDestroy(rect[i].path);
                rect[i].path = nullptr;
            }
        }
        _rwSListDestroy(font->charMap);
    }
    font->charMap = nullptr;
    if (font->uCharIndex != nullptr) {
        RwFree(font->uCharIndex);
        font->uCharIndex = nullptr;
    }
    for (RwTexture*& texture : font->textures) {
        if (texture != nullptr) TextureRelease(texture);
        texture = nullptr;
    }
    RwFreeListFree(rt2dGlobals.fontFreeList, font);
    return 1;
}

// 0x0070d638 Rt2dFontGetStringWidth: the sum of (glyph width + intergap) over the glyphs, x height.
RwReal Rt2dFontGetStringWidth(Rt2dFont* font, const RwChar* string, RwReal height) {
    const rt2dCharRect* rects = static_cast<const rt2dCharRect*>(_rwSListGetArray(font->charMap));
    RwReal width = 0.0f;
    RwInt32 step;
    RwInt32 c = _rt2dFontDecodeChar(font, string, &step);
    while (c > 0) {
        const RwInt32 index = _rt2dFontCharIndex(font, c);
        string += step;
        if (index >= 0) width = width + (rects[index].width + font->intergap);
        c = _rt2dFontDecodeChar(font, string, &step);
    }
    return width * height;
}

// 0x0070ccc8 DispatchUIFontRenderCallback (Rt2dFontShow): the font's show callback.
Rt2dFont* Rt2dFontShow(Rt2dFont* font, const RwChar* string, RwReal height, RwV2d* anchor, Rt2dBrush* brush) {
    return font->fontshowCB(font, string, height, anchor, brush);
}

// 0x0070d240 DrawUIWrappedFontText (Rt2dFontFlow): the text wrapped into bbox line by line from the top
// (anchor y = y + h - height, then down by height per line): a line ends at a newline or when it would be
// wider than the box (it then breaks at the last space, whose run of spaces is skipped); each line is
// shown (terminated in place for the call) at x + justification x (box width - line width), the factor
// being 0 (left), height / 2 (centre) or height (right) over widths in font units. Null when a line falls
// below the box.
Rt2dFont* Rt2dFontFlow(Rt2dFont* font, RwChar* string, RwReal height, Rt2dBBox* bbox, Rt2dJustificationType format,
                       Rt2dBrush* brush) {
    const rt2dCharRect* rects = static_cast<const rt2dCharRect*>(_rwSListGetArray(font->charMap));
    const RwReal boxWidth = bbox->w / height;
    RwReal justify;
    if (format == rt2dJUSTIFYCENTER) {
        justify = height * 0.5f;
    } else if (format == rt2dJUSTIFYRIGHT) {
        justify = height;
    } else {
        justify = 0.0f;
    }
    const bool wide = (font->flag & 2) != 0;
    const RwInt32 step = wide ? 2 : 1;
    RwV2d anchor;
    anchor.y = (bbox->y + bbox->h) - height;
    RwChar* lineStart = string;
    RwReal width = 0.0f;
    RwInt32 dummy;
    RwChar* p = string;
    RwInt32 c = _rt2dFontDecodeChar(font, p, &dummy);
    if (c > 0) {
        RwReal widthAtBreak = 0.0f;
        RwChar* breakAt = string;
        RwInt32 notSpace = 1;
        for (;;) {
            const RwInt32 index = _rt2dFontCharIndex(font, c);
            if (notSpace != 0 && c == 0x20) {
                widthAtBreak = width;
                breakAt = p;
                notSpace = 0;
            } else {
                notSpace = 1;
                if (c == '\n') {
                    widthAtBreak = width;
                    breakAt = p + step;
                }
            }
            if (index >= 0) width = width + (rects[index].width + font->intergap);
            bool emit = width > boxWidth;
            if (!emit) {
                p += step;
                if (c == '\n') emit = true;
            }
            if (emit) {
                // The line up to breakAt, terminated in place for the call.
                RwChar* b0 = breakAt;
                RwChar* b1 = breakAt + (wide ? 1 : 0);
                const RwChar saved0 = *b0;
                const RwChar saved1 = *b1;
                *b0 = 0;
                *b1 = 0;
                anchor.x = ppc::fmadds(justify, boxWidth - widthAtBreak, bbox->x);
                font->fontshowCB(font, lineStart, height, &anchor, brush);
                *b0 = saved0;
                *b1 = saved1;
                if (_rt2dFontDecodeChar(font, breakAt, &dummy) == 0x20) {
                    RwChar* q = breakAt + step;
                    while (_rt2dFontDecodeChar(font, q, &dummy) == 0x20) q += step;
                    breakAt = q;
                }
                anchor.y = anchor.y - height;
                if (bbox->y > anchor.y) return nullptr;
                p = breakAt;
                width = 0.0f;
                lineStart = breakAt;
                notSpace = 1;
                c = _rt2dFontDecodeChar(font, p, &dummy);
                if (c > 0) continue;
                break;
            }
            c = _rt2dFontDecodeChar(font, p, &dummy);
            if (c <= 0) break;
        }
    }
    anchor.x = ppc::fmadds(justify, boxWidth - width, bbox->x);
    font->fontshowCB(font, lineStart, height, &anchor, brush);
    return font;
}

// 0x0070dbc8 DrawUIVectorFontGlyphs (the outline fonts' show callback): with the CTM pushed, translated to
// the anchor, scaled by height and moved down by the baseline, each glyph without a texture is stroked
// with brush and the CTM advances by its width + intergap. BUG(original): a glyph with a texture does not
// advance.
Rt2dFont* _rt2dFontShowOutline(Rt2dFont* font, const RwChar* string, RwReal height, RwV2d* anchor, Rt2dBrush* brush) {
    if (font == nullptr) return font;
    const rt2dCharRect* rects = static_cast<const rt2dCharRect*>(_rwSListGetArray(font->charMap));
    Rt2dCTMPush();
    Rt2dCTMTranslate(anchor->x, anchor->y);
    Rt2dCTMScale(height, height);
    Rt2dCTMTranslate(0.0f, -font->baseline);
    RwInt32 step;
    RwInt32 c = _rt2dFontDecodeChar(font, string, &step);
    while (c > 0) {
        const RwInt32 index = _rt2dFontCharIndex(font, c);
        string += step;
        if (index >= 0 && rects[index].tex == nullptr) {
            Rt2dPathStroke(rects[index].path, brush);
            Rt2dCTMTranslate(rects[index].width + font->intergap, 0.0f);
        }
        c = _rt2dFontDecodeChar(font, string, &step);
    }
    Rt2dCTMPop();
    return font;
}

namespace {

// The colour of a glyph vertex: the brush's bottom / top colour at t along the string when it varies,
// else the colour cache.
void GlyphColor(RwIm3DVertex* v, const Rt2dBrush* brush, bool top, RwReal t) {
    if ((brush->flag & 1) == 0) {
        v->color = brush->colorCache;
        return;
    }
    const rt2dShadeParameters& base = top ? brush->top : brush->bottom;
    const rt2dShadeParameters& delta = top ? brush->dtop : brush->dbottom;
    v->color.red = static_cast<RwUInt8>(ppc::fctiwz(ppc::fmadds(t, delta.col.red, base.col.red)));
    v->color.green = static_cast<RwUInt8>(ppc::fctiwz(ppc::fmadds(t, delta.col.green, base.col.green)));
    v->color.blue = static_cast<RwUInt8>(ppc::fctiwz(ppc::fmadds(t, delta.col.blue, base.col.blue)));
    v->color.alpha = static_cast<RwUInt8>(ppc::fctiwz(ppc::fmadds(t, delta.col.alpha, base.col.alpha)));
}

// The flush of the glyph batch: a triangle list over fonttopo (flags rwIM3D_VERTEXUV | rwIM3D_NOCLIP).
void FlushGlyphs(RwIm3DVertex* end, RwMatrix* ltm, RwInt32 numIndices) {
    Rt2dGlobalVars& g = rt2dGlobals;
    const RwUInt32 numVerts = static_cast<RwUInt32>(end - g.brushVertexCache);
    if (RwIm3DTransform(g.brushVertexCache, numVerts, ltm, rwIM3D_VERTEXUV | rwIM3D_NOCLIP) != nullptr) {
        RwIm3DRenderIndexedPrimitive(rwPRIMTYPETRILIST, g.fonttopo, numIndices);
        RwIm3DEnd();
    }
}

}  // namespace

// 0x0070ee30 DrawUIBitmapFontGlyphs (the bitmap fonts' show callback): with the CTM pushed, translated to
// the anchor, scaled by height and moved down by the baseline: the string's width (sum of width +
// intergap); then a quad per glyph (x .. x + width, y 0 .. 1, z the layer depth's bits, or 0 with the PS3's CTM
// override set; UVs from the glyph's corners; the brush colour along the string) into the vertex
// cache, batched per texture page (filter and raster set on a page change) up to 0x180 indices; finally
// the anchor advances by width x height. A string without width draws nothing.
// BUG(original): a textured brush with flag 2 loses flag 2 at the first page change.
Rt2dFont* _rt2dFontShowBitmap(Rt2dFont* font, const RwChar* string, RwReal height, RwV2d* anchor, Rt2dBrush* brush) {
    Rt2dGlobalVars& g = rt2dGlobals;
    RwReal z = 0.0f;
    if (g.overrideCTM == nullptr) z = g.layerDepth;  // 0x70eea8: lwz of +0x1630, beq -> lwz +0xbf8
    if (font == nullptr) return nullptr;
    const rt2dCharRect* rects = static_cast<const rt2dCharRect*>(_rwSListGetArray(font->charMap));
    Rt2dCTMPush();
    Rt2dCTMTranslate(anchor->x, anchor->y);
    Rt2dCTMScale(height, height);
    Rt2dCTMTranslate(0.0f, -font->baseline);
    RwMatrix* ltm = _rt2dCTMGetComposite();
    RwInt32 step;
    RwReal total = 0.0f;
    for (const RwChar* s = string;;) {
        const RwInt32 c = _rt2dFontDecodeChar(font, s, &step);
        if (c <= 0) break;
        const RwInt32 index = _rt2dFontCharIndex(font, c);
        s += step;
        if (index >= 0) total = total + (rects[index].width + font->intergap);
    }
    RwReal x = 0.0f;
    if (total != 0.0f) {
        const RwReal invTotal = 1.0f / total;
        RwReal colorX = 0.0f;
        RwTexture* page = nullptr;
        RwInt32 numIndices = 0;
        RwIm3DVertex* v = g.brushVertexCache;
        for (const RwChar* s = string;;) {
            const RwInt32 c = _rt2dFontDecodeChar(font, s, &step);
            if (c <= 0) break;
            const RwInt32 index = _rt2dFontCharIndex(font, c);
            s += step;
            if (index < 0) continue;
            const rt2dCharRect* rect = &rects[index];
            if (rect->tex == page && numIndices <= 0x17a) {
                numIndices += 6;
            } else {
                if (numIndices != 0) FlushGlyphs(v, ltm, numIndices);
                if (page != rect->tex) {
                    RwRenderStateSet(rwRENDERSTATETEXTUREFILTER,
                                     reinterpret_cast<void*>(static_cast<uintptr_t>(rect->tex->filterAddressing & 0xff)));
                    RwRenderStateSet(rwRENDERSTATETEXTURERASTER, rect->tex->raster);
                    page = rect->tex;
                }
                v = g.brushVertexCache;
                if (brush->texture != nullptr && (brush->flag & 2) != 0) brush->flag &= ~2;
                numIndices = 6;
            }
            const RwReal right = x + rect->width;
            v[0].objVertex = RwV3d{x, 0.0f, z};
            v[0].u = rect->uv[0].x;
            v[0].v = rect->uv[1].y;
            GlyphColor(&v[0], brush, false, colorX * invTotal);
            v[1].objVertex = RwV3d{x, 1.0f, z};
            v[1].u = rect->uv[0].x;
            v[1].v = rect->uv[0].y;
            GlyphColor(&v[1], brush, true, colorX * invTotal);
            v[2].objVertex = RwV3d{right, 0.0f, z};
            v[2].u = rect->uv[1].x;
            v[2].v = rect->uv[1].y;
            GlyphColor(&v[2], brush, false, (colorX + rect->width) * invTotal);
            v[3].objVertex = RwV3d{right, 1.0f, z};
            v[3].u = rect->uv[1].x;
            v[3].v = rect->uv[0].y;
            GlyphColor(&v[3], brush, true, (colorX + rect->width) * invTotal);
            v += 4;
            const RwReal advance = rect->width + font->intergap;
            colorX = colorX + advance;
            x = x + advance;
        }
        if (numIndices != 0) FlushGlyphs(v, ltm, numIndices);
    }
    anchor->x = ppc::fmadds(height, x, anchor->x);
    Rt2dCTMPop();
    return font;
}

// 0x0070df88 Rt2dFontStreamRead (after the caller's RwStreamFindChunk(0x199)): the header (a version
// word whose top byte must be positive; isOutline, height, baseline, intergap, flag, uCharOffset,
// charCount, uCharIndexCount), the unicode index table, the 128-entry ASCII table, then per glyph:
// outline fonts a word, the width, a kind word (5: a 0x1a1 chunk with the glyph's path, then a word) and
// a word; bitmap fonts the two UV corners, the width and the page byte, then the page textures by name
// (from the font texture dictionary, made current meanwhile), each glyph taking its page's texture,
// which must have a raster. A failed read destroys the font and returns null.
Rt2dFont* Rt2dFontStreamRead(RwStream* stream) {
    Rt2dGlobalVars& g = rt2dGlobals;
    Rt2dFont* font = static_cast<Rt2dFont*>(RwFreeListAlloc(g.fontFreeList, 0x30199));
    if (font == nullptr) return nullptr;
    font->height = 1.0f;
    font->isOutline = 1;
    font->intergap = 0.0f;
    font->baseline = 0.0f;
    font->flag = 0;
    for (RwTexture*& texture : font->textures) texture = nullptr;
    font->uCharIndexCount = 0;
    font->charCount = 0;
    font->uCharOffset = 0;
    font->uCharIndex = nullptr;
    font->charMap = _rwSListCreate(sizeof(rt2dCharRect), 0x30190);
    font->strCache = nullptr;
    font->fontshowCB = _rt2dFontShowBitmap;
    font->nextBatch = nullptr;
    for (RwInt16& index : font->aCharIndex) index = -1;

    RwUInt32 version = 0;
    bool ok = Rt2dStreamReadInt32(stream, &version, 4) != nullptr;
    if (ok) ok = static_cast<RwInt8>(version >> 24) > 0;  // lbz of the big-endian word's first byte
    if (ok) ok = Rt2dStreamReadInt32(stream, &font->isOutline, 4) != nullptr;
    if (ok) ok = Rt2dStreamReadReal(stream, &font->height, 4) != nullptr;
    if (ok) ok = Rt2dStreamReadReal(stream, &font->baseline, 4) != nullptr;
    if (ok) ok = Rt2dStreamReadReal(stream, &font->intergap, 4) != nullptr;
    if (ok) ok = Rt2dStreamReadInt32(stream, &font->flag, 4) != nullptr;
    if (ok) ok = Rt2dStreamReadInt32(stream, &font->uCharOffset, 4) != nullptr;
    if (ok) ok = Rt2dStreamReadInt32(stream, &font->charCount, 4) != nullptr;
    if (ok) ok = Rt2dStreamReadInt32(stream, &font->uCharIndexCount, 4) != nullptr;
    if (ok && font->uCharIndexCount > 0) {
        const RwUInt32 size = static_cast<RwUInt32>(font->uCharIndexCount) * 2;
        font->uCharIndex = static_cast<RwInt16*>(RwMalloc(size, 0x30190));
        std::memset(font->uCharIndex, 0, size);  // BUG(original): before the null check
        ok = font->uCharIndex != nullptr && Rt2dStreamReadInt16(stream, font->uCharIndex, size) != nullptr;
    }
    if (ok) ok = Rt2dStreamReadInt16(stream, font->aCharIndex, 0x100) != nullptr;
    if (!ok) {
        Rt2dFontDestroy(font);
        return nullptr;
    }
    _rwSListGetNewEntries(font->charMap, font->charCount, 0x30190);
    std::memset(_rwSListGetArray(font->charMap), 0, static_cast<size_t>(font->charCount) * sizeof(rt2dCharRect));

    if (font->isOutline != 0) {
        rt2dCharRect* rect = static_cast<rt2dCharRect*>(_rwSListGetArray(font->charMap));
        for (RwInt32 i = 0; i < font->charCount; ++i, ++rect) {
            RwInt32 word = 0;
            Rt2dPath* path = nullptr;
            ok = Rt2dStreamReadInt32(stream, &word, 4) != nullptr;
            if (ok) ok = Rt2dStreamReadReal(stream, &rect->width, 4) != nullptr;
            if (ok) ok = Rt2dStreamReadInt32(stream, &word, 4) != nullptr;
            if (ok && word == 5) {
                ok = RwStreamFindChunk(stream, 0x1a1, nullptr, nullptr) != 0;
                if (ok) path = Rt2dPathStreamRead(stream);
                if (ok) ok = Rt2dStreamReadInt32(stream, &word, 4) != nullptr;
            }
            if (ok) ok = Rt2dStreamReadInt32(stream, &word, 4) != nullptr;
            if (!ok) {
                Rt2dFontDestroy(font);
                return nullptr;
            }
            rect->path = path;
        }
        font->fontshowCB = _rt2dFontShowOutline;
        return font;
    }

    RwTexDictionary* previous = RwTexDictionaryGetCurrent();
    RwTexDictionarySetCurrent(g.currFontTexDictionary);
    rt2dCharRect* rects = static_cast<rt2dCharRect*>(_rwSListGetArray(font->charMap));
    for (RwInt32 i = 0; i < font->charCount && ok; ++i) {
        rt2dCharRect* rect = &rects[i];
        ok = Rt2dStreamReadReal(stream, rect->uv, 0x10) != nullptr;
        if (ok) ok = Rt2dStreamReadReal(stream, &rect->width, 4) != nullptr;
        if (ok) ok = RwStreamRead(stream, &rect->charpage, 1) == 1;
        if (ok) rect->path = nullptr;
    }
    RwInt32 numTextures = 0;
    if (ok) ok = Rt2dStreamReadInt32(stream, &numTextures, 4) != nullptr;
    for (RwInt32 i = 0; i < numTextures && ok; ++i) {
        RwChar name[0x20];
        ok = RwStreamRead(stream, name, 0x20) == 0x20;
        if (ok) {
            font->textures[i] = TextureRead(name);
            ok = font->textures[i] != nullptr;
        }
    }
    for (RwInt32 i = 0; i < font->charCount && ok; ++i) {
        rt2dCharRect* rect = &rects[i];
        rect->tex = font->textures[rect->charpage];
        ok = rect->tex->raster != nullptr;
    }
    if (!ok) {
        Rt2dFontDestroy(font);
        RwTexDictionarySetCurrent(previous);
        return nullptr;
    }
    font->fontshowCB = _rt2dFontShowBitmap;
    font->strCache = nullptr;
    font->nextBatch = nullptr;
    RwTexDictionarySetCurrent(previous);
    return font;
}
