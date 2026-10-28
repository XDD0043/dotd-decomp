// 2dstr.cpp - RW 3.7 tool/2d/2dstr.c, ported from the PS3 library code (0x7090e8-0x70a430). See Rt2d.h.
//
// An object string's text (data.objectString.textString) is copied with its terminator counted in
// 2-byte units (the PS3 build's strings end with two zero bytes); maxLength is the byte length of the
// longest text stored so far (the buffer holds maxLength + 2 bytes). Whether the text is drawn as bytes
// or as 2-byte characters is the font's business (Rt2dFont flag bit 1). Flag 0x1000000: the font name
// was not in the font dictionary.
//
// Not ported (the front end never reaches them): _rt2dObjectStringStreamGetDataSize_maybe 0x709118,
// _rt2dObjectStringStreamWriteData_maybe 0x7091e0, Rt2dObjectStringDestroy 0x709f10,
// Rt2dObjectStringStreamGetSize 0x709ff0, Rt2dObjectStringStreamRead 0x70a0b8, Rt2dObjectStringCreate
// 0x70a1e8, Rt2dObjectStringStreamWrite 0x70a2f8.
#include "Renderware/rt2d/Rt2dInternal.h"

DOTD_ASSERT_OFFSET(Rt2dObject, data.objectString.textString, 0xb0);
DOTD_ASSERT_OFFSET(Rt2dObject, data.objectString.brush, 0xb4);
DOTD_ASSERT_OFFSET(Rt2dObject, data.objectString.maxLength, 0xb8);
DOTD_ASSERT_OFFSET(Rt2dObject, data.objectString.height, 0xbc);
DOTD_ASSERT_OFFSET(Rt2dObject, data.objectString.font, 0xc0);
DOTD_ASSERT_OFFSET(Rt2dObject, data.objectString.justiftype, 0xc4);
DOTD_ASSERT_OFFSET(Rt2dObject, data.objectString.boxwidth, 0xc8);

namespace {

// The text's length in bytes up to its 2-byte terminator (the loop steps by 2).
RwInt32 TextLength(const RwChar* text) {
    RwInt32 length = 0;
    while (text[length] != 0 || text[length + 1] != 0) length += 2;
    return length;
}

// The font lookup _rt2dObjectStringInit and Rt2dObjectStringSetFont share.
void SetFontEntry(Rt2dObject* string, _rt2dFontDictionaryNode* entry) {
    string->data.objectString.font = entry;
    if (entry != nullptr) {
        string->flag &= ~0x1000000;
    } else {
        string->flag |= 0x1000000;
    }
}

}  // namespace

// 0x007090e8 Rt2dObjectStringGetText
RwChar* Rt2dObjectStringGetText(Rt2dObject* string) { return string->data.objectString.textString; }

// 0x007090f0 Rt2dObjectStringGetFont: the font's name. BUG(original): a string without a font (flag
// 0x1000000) reads through a null pointer.
RwChar* Rt2dObjectStringGetFont(Rt2dObject* string) { return string->data.objectString.font->name; }

// 0x00709100 Rt2dObjectStringGetHeight / 0x00709108 Rt2dObjectStringSetHeight
RwReal Rt2dObjectStringGetHeight(Rt2dObject* string) { return string->data.objectString.height; }
Rt2dObject* Rt2dObjectStringSetHeight(Rt2dObject* string, RwReal height) {
    string->data.objectString.height = height;
    return string;
}

// 0x007093b8 Rt2dObjectStringSetText: copies text (with its terminator); a longer text reallocates the
// buffer (RwFree + RwMalloc, length + 2 bytes) and raises maxLength.
Rt2dObject* Rt2dObjectStringSetText(Rt2dObject* string, const RwChar* text) {
    const RwInt32 length = TextLength(text);
    const RwUInt32 size = static_cast<RwUInt32>(length + 2);
    if (string->data.objectString.maxLength < length) {
        if (string->data.objectString.textString != nullptr) RwFree(string->data.objectString.textString);
        string->data.objectString.maxLength = length;
        string->data.objectString.textString = static_cast<RwChar*>(RwMalloc(size, 0x301a7));
    }
    std::memcpy(string->data.objectString.textString, text, size);
    return string;
}

// 0x007094e0 Rt2dObjectStringSetBrush: the brush's contents are copied into the string's own brush.
Rt2dObject* Rt2dObjectStringSetBrush(Rt2dObject* string, Rt2dBrush* brush) {
    std::memcpy(string->data.objectString.brush, brush, sizeof(Rt2dBrush));
    return string;
}

// 0x00709930 Rt2dObjectStringSetFont: the dictionary entry of that name (null when absent, flag
// 0x1000000). Returns the string, or null when the font was not found.
Rt2dObject* Rt2dObjectStringSetFont(Rt2dObject* string, const RwChar* font) {
    _rt2dFontDictionaryNode* entry = _rt2dFontDictionaryFindEntry(font);
    SetFontEntry(string, entry);
    return entry != nullptr ? string : nullptr;
}

// 0x007099a0 _rt2dObjectStringDestruct_maybe: the text, then the brush (Rt2dBrushDestroy's result).
RwBool _rt2dObjectStringDestruct(Rt2dObject* string) {
    if (string->data.objectString.textString != nullptr) RwFree(string->data.objectString.textString);
    if (string->data.objectString.brush == nullptr) return 1;
    return Rt2dBrushDestroy(string->data.objectString.brush);
}

// 0x00709a20 _rt2dObjectStringInit_maybe: height 1, a new brush, the font by name, box width 200, left
// justified, a copy of text (or no text). Null when the brush or the copy cannot be allocated.
Rt2dObject* _rt2dObjectStringInit(Rt2dObject* string, const RwChar* text, const RwChar* font) {
    string->data.objectString.height = 1.0f;
    string->flag &= ~1;
    string->data.objectString.brush = Rt2dBrushCreate();
    if (string->data.objectString.brush == nullptr) return nullptr;
    SetFontEntry(string, _rt2dFontDictionaryFindEntry(font));
    string->data.objectString.boxwidth = 200.0f;
    string->data.objectString.justiftype = rt2dJUSTIFYLEFT;
    if (text == nullptr) {
        string->data.objectString.maxLength = 0;
        string->data.objectString.textString = nullptr;
        return string;
    }
    const RwInt32 length = TextLength(text);
    const RwUInt32 size = static_cast<RwUInt32>(length + 2);
    string->data.objectString.textString = static_cast<RwChar*>(RwMalloc(size, 0x301a7));
    if (string->data.objectString.textString == nullptr) {
        Rt2dBrushDestroy(string->data.objectString.brush);
        return nullptr;
    }
    std::memcpy(string->data.objectString.textString, text, size);
    string->data.objectString.maxLength = length;
    return string;
}

// 0x00709520 DrawUITextSceneObject (_rt2dObjectStringRender): a visible string with a font pushes its LTM;
// unless the text is exactly one space, its brush colours are transformed by the combined colour
// transform (offset x 255 as for shapes) for the call, and the text flows into the box (0, 0, boxwidth,
// height) with the string's justification (Rt2dFontFlow); then the brush colours are restored.
Rt2dObject* _rt2dObjectStringRender(Rt2dObject* string, RwRGBAReal* colorMult, RwRGBAReal* colorOffs) {
    if ((string->flag & 0x1000004) != 4) return string;
    if ((string->flag & 2) != 0) {
        _rt2dCTMPushMult(&string->MTM);
        string->LTM = *_rt2dCTMGet();
        string->flag &= ~2;
    } else {
        _rt2dCTMPush(&string->LTM);
    }
    Rt2dFont* font = string->data.objectString.font->font;
    RwChar* text = string->data.objectString.textString;
    RwInt32 step;
    if (_rt2dFontDecodeChar(font, text, &step) == 0x20 && _rt2dFontDecodeChar(font, text + step, &step) == 0) {
        Rt2dCTMPop();
        return string;
    }
    RwRGBAReal mult;
    RwRGBAReal offs;
    const RwReal oa = colorOffs->alpha * 255.0f;
    const RwReal og = colorOffs->green * 255.0f;
    const RwReal ob = colorOffs->blue * 255.0f;
    const RwReal orr = colorOffs->red * 255.0f;
    mult.red = string->colorMult.red * colorMult->red;
    mult.green = string->colorMult.green * colorMult->green;
    mult.blue = string->colorMult.blue * colorMult->blue;
    mult.alpha = string->colorMult.alpha * colorMult->alpha;
    offs.green = ppc::fmadds(string->colorOffs.green, colorMult->green, og);
    offs.blue = ppc::fmadds(string->colorOffs.blue, colorMult->blue, ob);
    offs.red = ppc::fmadds(string->colorOffs.red, colorMult->red, orr);
    offs.alpha = ppc::fmadds(string->colorOffs.alpha, colorMult->alpha, oa);
    Rt2dBrush* brush = string->data.objectString.brush;
    const RwRGBAReal bottom = brush->bottom.col;
    const RwRGBAReal dbottom = brush->dbottom.col;
    const RwRGBAReal dtop = brush->dtop.col;
    const RwRGBAReal top = brush->top.col;
    _rt2dBrushTransformColor(brush, &bottom, &dbottom, &dtop, &top, &mult, &offs);
    const RwReal height = string->data.objectString.height;
    Rt2dBBox box = {0.0f, 0.0f, string->data.objectString.boxwidth, height};
    Rt2dFontFlow(font, text, height, &box, static_cast<Rt2dJustificationType>(string->data.objectString.justiftype),
                 brush);
    Rt2dCTMPop();
    brush->bottom.col = bottom;
    brush->dbottom.col = dbottom;
    brush->dtop.col = dtop;
    brush->top.col = top;
    return string;
}

// 0x00709bf8 _rt2dObjectStringStreamReadTo: the text length and the height word, the text (length + 1
// bytes into a length + 3 buffer whose last two bytes are cleared), the font name length and name
// (length + 1 bytes), _rt2dObjectStringInit, RwStreamFindChunk(0x1a2) and the brush, then the height.
// The temporary text and name are freed (the string keeps its own copy). Any failure returns null.
// BUG(original): the paths after _rt2dObjectStringInit leave the string's text, brush and font set.
Rt2dObject* _rt2dObjectStringStreamReadTo(Rt2dObject* string, RwStream* stream) {
    RwInt32 textLength = 0;
    RwReal height = 0.0f;
    if (RwStreamRead(stream, &textLength, 4) != 4) return nullptr;
    if (RwStreamRead(stream, &height, 4) != 4) return nullptr;
    // RwMemNative32 on both: native on a little-endian host.
    RwChar* text = static_cast<RwChar*>(RwMalloc(static_cast<RwUInt32>(textLength + 3), 0x101a7));
    RwChar* fontName = nullptr;
    bool ok = text != nullptr;
    if (ok) ok = RwStreamRead(stream, text, static_cast<RwUInt32>(textLength + 1)) == static_cast<RwUInt32>(textLength + 1);
    RwInt32 fontLength = 0;
    if (ok) ok = RwStreamRead(stream, &fontLength, 4) == 4;
    if (ok) {
        text[textLength + 1] = 0;
        text[textLength + 2] = 0;
        if (fontLength != 0) {
            fontName = static_cast<RwChar*>(RwMalloc(static_cast<RwUInt32>(fontLength + 1), 0x101a7));
            ok = fontName != nullptr;
            if (ok) {
                ok = RwStreamRead(stream, fontName, static_cast<RwUInt32>(fontLength + 1)) ==
                     static_cast<RwUInt32>(fontLength + 1);
            }
        }
    }
    if (ok) ok = _rt2dObjectStringInit(string, text, fontName) != nullptr;
    if (ok) ok = RwStreamFindChunk(stream, 0x1a2, nullptr, nullptr) != 0;
    if (ok) ok = _rt2dBrushStreamReadTo(string->data.objectString.brush, stream) != nullptr;
    if (ok) string->data.objectString.height = height;
    RwFree(fontName);
    RwFree(text);
    return ok ? string : nullptr;
}
