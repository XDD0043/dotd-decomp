// TextData.cpp - reconstructed original translation unit 0x6a1f0-0x6c6e8 (GAME_TOC1, main_toc1), 19 functions, 17 live.
// Primary owner: TextData (not a registered class)
// Other owners: Text2dBlock (3), Text2dPart (3), CText2d (3)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x6a1f0  TextData_SetColor
//   [ ] 0x6a238  TextData_AppendLinesToWStr_maybe
//   [ ] 0x6a2d0  TextData_GetTotalCharCount_maybe  [dead]
//   [ ] 0x6a350  Text2dBlock_MeasureSize_maybe
//   [x] 0x6a468  TextData_ComputeLayout_maybe
//   [x] 0x6aa60  Text2dPart_ReplaceButtonGlyphTokens_maybe
//   [x] 0x6ad78  Text2dPart_SubstituteVariables_maybe
//   [x] 0x6b1b8  TextData_SetTextAscii
//   [x] 0x6b260  CText2d_ConstructTextPart_maybe
//   [x] 0x6b2d8  CText2d_TokenizeText_maybe
//   [ ] 0x6b530  TextData_SetFontHeight_maybe
//   [ ] 0x6b5f8  CText2d_ConstructTextPart_2_maybe  [dead]
//   [ ] 0x6b670  Text2dBlock_Reset_maybe
//   [x] 0x6b728  Text2dBlock_Load_maybe
//   [x] 0x6bd10  Text2dPart_RefreshFromLocString_maybe
//   [x] 0x6c0a8  TextData_OnEvent_maybe
//   [x] 0x6c1f8  TextData_SetText
//   [x] 0x6c580  TextData_SetTextClearLocRef_maybe
//   [x] 0x6c668  TextData_SetTextFromLocString
//
//   [ ] 0x9942d0  TextData_ScaleSize_maybe  [inline]
//   [ ] 0x994338  TextData_DeletingDestructor  [inline]
//   [ ] 0x994368  TextData_Destructor  [inline]
//   [ ] 0x9943d8  TextData_FitSizeToText_maybe  [inline]
//   [ ] 0x9985c8  TextData_ComputeAlignedRect_maybe  [inline]
//   [x] 0x9986c8  DrawUITextLinesWithLayout  [inline]
//   [x] 0x998bc0  TextData_SetFont_maybe  [inline]
//
// Strings: the text is UTF-16 in host order (uint16_t). The Rt2d font port decodes a wide font's units in
// host order, so the words go to Rt2dFontGetStringWidth / Rt2dFontShow as they are; the PS3 reads the same
// units big-endian. (With a byte font the two would differ; the game's fonts are wide.)
#include "k2000/ui/IKText2d.h"

#include <cstdio>
#include <cstring>

#include "Renderware/rt2d/Rt2d.h"
#include "Renderware/rwcore/RwStream.h"
#include "crt/ppc_ops.h"
#include "crt/xlround.h"
#include "k2000/components/CKLocTextAccessor.h"
#include "k2000/core/IKSerializable.h"
#include "k2000/graphical/ui/CManager2d.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/ui/CKLocText.h"
#include "k2000/logic/ui/CLocManager.h"
#include "k2000/managers/CKInput.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/Wcs.h"
#include "k2000/system/IKTime.h"

namespace {

// TOC1 -0x6e18 -> 0xc296a8: the UTF-16 " " (Load's default text, the cleared text, the padding's start).
const uint16_t kSpaceW[] = {0x20, 0};
// TOC1 -0x6e10 -> 0xc29672: the text copied in place of one of 400 characters or more.
const uint16_t kTextTooBig[] = {'-', 'T', 'E', 'X', 'T', ' ', 'T', 'O', 'O', ' ', 'B', 'I', 'G', '-', 0};
// TOC1 -0x6e14 -> 0xac3ff0: the UTF-16 "0" of the variables' zero padding.
const uint16_t kZeroW[] = {'0', 0};
// LocString_GetText's text (0x00c2966e) while the loc manager has no localised data (UTF-16 " ").
const uint16_t kLocTextSpace[] = {0x20, 0};

// Local copy of 0x00010a18 Wcs_Length (misc/Wcs.cpp, not ported yet).
uint32_t Wcs_Length(const uint16_t* s) {
    uint32_t n = 0;
    while (s[n] != 0) ++n;
    return n;
}

// Local copy of 0x00010928 Wcs_FindChar (misc/Wcs.cpp, not ported yet): the first c, or null.
uint16_t* Wcs_FindChar(uint16_t* s, uint16_t c) {
    uint16_t ch = *s;
    while (ch != 0) {
        if (ch == c) return s;
        ++s;
        ch = *s;
    }
    return nullptr;
}

// Local copy of 0x00011c10 WStr_CatReturnEnd (misc/Str.cpp, not ported yet): appends src; the new end.
uint16_t* WStr_CatReturnEnd(uint16_t* dst, const uint16_t* src) {
    while (*dst != 0) ++dst;
    uint16_t c = *src;
    while (c != 0) {
        *dst = c;
        ++src;
        ++dst;
        c = *src;
    }
    *dst = 0;
    return dst;
}

// Local copy of 0x00011c88 WStr_Sprintf (misc/Str.cpp, not ported yet), for its one use here (one int):
// vsprintf into a 0x108-byte buffer, every byte zero-extended into dst.
void WStr_SprintfInt(uint16_t* dst, const char* format, int32_t value) {
    char buffer[0x108];
    std::snprintf(buffer, sizeof(buffer), format, value);
    const char* p = buffer;
    while (*p != 0) *dst++ = static_cast<uint8_t>(*p++);
    *dst = 0;
}

// Local copy of 0x000107d8 Str_HashXor4 (misc/Wcs.cpp, not ported yet; CKInput.cpp has another copy):
// the bytes XORed into four accumulators in turn, returned as a little-endian word.
uint32_t Str_HashXor4(const char* s) {
    uint8_t acc[4] = {0, 0, 0, 0};
    for (uint32_t i = 0; s[i] != 0; ++i) acc[i & 3] ^= static_cast<uint8_t>(s[i]);
    return static_cast<uint32_t>(acc[0]) | (static_cast<uint32_t>(acc[1]) << 8) |
           (static_cast<uint32_t>(acc[2]) << 16) | (static_cast<uint32_t>(acc[3]) << 24);
}

// The loc manager's text variables are the 0xc-byte records of CLocManager +0xbc (m_vTrcRecords):
// +0 value, +4 name hash (Str_HashXor4), +8 digits (the zero-padded width).
// Local copy of 0x00037328 CLocManager_FindTextVariable_maybe (CLocManager.cpp, not ported yet): the first
// record whose hash is the name's; -1 (also for a null name).
int32_t CLocManager_FindTextVariable(const CLocManager* loc, const char* name) {
    if (name == nullptr) return -1;
    const uint32_t hash = Str_HashXor4(name);
    for (uint32_t i = 0; i < loc->m_vTrcRecords.m_ui32NbUsedElt; ++i)
        if (loc->m_vTrcRecords.m_pBlock[i].m_unk4 == hash) return static_cast<int32_t>(i);
    return -1;
}
// Local copy of 0x000376f8 CLocManager_GetTextVariableValue_maybe (CLocManager.cpp, not ported yet).
uint32_t CLocManager_GetTextVariableValue(const CLocManager* loc, uint32_t index) {
    if (index < loc->m_vTrcRecords.m_ui32NbUsedElt) return loc->m_vTrcRecords.m_pBlock[index].m_unk0;
    return 0;
}
// Local copy of 0x00037578 CLocManager_GetTextVariable (CLocManager.cpp, not ported yet): the digits.
uint32_t CLocManager_GetTextVariable(const CLocManager* loc, uint32_t index) {
    if (index < loc->m_vTrcRecords.m_ui32NbUsedElt) return loc->m_vTrcRecords.m_pBlock[index].m_unk8;
    return 0;
}

// Local copy of 0x00061bf8 CManager2d_GetFont_maybe (CManager2d.cpp, not ported yet): font 0x29a is the
// localised font, 0..9 the loaded fonts, anything else none.
Rt2dFont* CManager2d_GetFont(const CManager2d* manager, uint32_t id) {
    if (id == 0x29a) return manager->m_pLocalizedFont;
    if (id < 10) return manager->m_apFonts[id];
    return nullptr;
}

// The PS3 measures the ASCII " " (0xac4008: bytes 20 00 00 00) with the font in RecursiveNodeReach(0): a
// wide font reads the big-endian unit 0x2000, a byte font " ". The same string for the host's decoding.
const RwChar* AsciiSpaceAsFontString(const Rt2dFont* font) {
    static const uint16_t kWide[] = {0x2000, 0};
    static const char kBytes[] = {' ', 0, 0, 0};
    if ((font->flag & 2) != 0) return reinterpret_cast<const RwChar*>(kWide);
    return kBytes;
}

const RwChar* AsFontString(const uint16_t* text) { return reinterpret_cast<const RwChar*>(text); }

// The word split that TokenizeText (0x6b338), SetText (0x6c270) and RefreshFromLocString (0x6bdac) inline,
// with the flag clearing of the last word: words start at the text and after each separator, which is
// replaced by 0 in place: " " (the word's bits 1 and 2 cleared), "\n" (bit 1 set: a line break follows) and
// "\e" (bit 2 set: kept with the next word); any other backslash is a character.
// BUG(original): no bound against the 60 word slots (a longer text writes past m_awszWords).
void SplitWords(IKText2d* text) {
    text->m_bAutoSize = 0;
    text->m_ui32WordsCount = 1;
    uint16_t* p = text->m_wszText;
    text->m_awszWords[0] = p;
    uint16_t c = *p;
    while (c != 0) {
        uint8_t* flags = &text->m_abWordTooLong[text->m_ui32WordsCount - 1];
        uint16_t* next = p + 1;
        if (c == 0x20) {
            *p = 0;
            *flags = static_cast<uint8_t>(*flags & ~2u);
            *flags = static_cast<uint8_t>(*flags & ~4u);
            text->m_awszWords[text->m_ui32WordsCount++] = next;
        } else if (c == 0x5c && (p[1] == 0x6e || p[1] == 0x65)) {
            const bool lineBreak = p[1] == 0x6e;  // "\n", else "\e"
            *p = 0;
            next = p + 2;
            *flags = static_cast<uint8_t>((*flags & ~2u) | (lineBreak ? 2u : 0u));
            *flags = static_cast<uint8_t>((*flags & ~4u) | (lineBreak ? 0u : 4u));
            text->m_awszWords[text->m_ui32WordsCount++] = next;
        }
        p = next;
        c = *p;
    }
    uint8_t* flags = &text->m_abWordTooLong[text->m_ui32WordsCount - 1];
    *flags = static_cast<uint8_t>(*flags & ~2u);
    *flags = static_cast<uint8_t>(*flags & ~4u);
}

// The button-token table as Render reads it (+0x708 + 2 i): entries 0..4, then the count itself (+0x712).
// BUG(original): ReplaceButtonGlyphTokens can store a sixth entry over the count, which can then exceed 6;
// the PS3 then reads on past the table (the accessor pointer and the next object's bytes). Those reads are
// not reproduced: such entries are skipped (0xff).
uint16_t ButtonTokenAt(const IKText2d* text, uint32_t i) {
    if (i < 5) return text->m_aui16ButtonTokens[i];
    if (i == 5) return text->m_ui16ButtonTokensCount;
    return 0x00ff;
}

}  // namespace

// 0x0006b260 CText2d_ConstructTextPart_maybe, in its store order. The text, the word tables, the button
// tokens and the variables are left as they are.
IKText2d::IKText2d() {
    m_ui16ButtonTokensCount = 0;
    m_i32FontId = -1;
    m_ui8HAlignType = 3;
    m_f32NextLineTimeLeft = 0.0f;
    m_pLocManager = nullptr;
    m_vBoxSize.m_fX = 0.0f;
    m_vBoxSize.m_fY = 0.0f;
    m_ui32BoxLinesCount = 0;
    m_ui32WordsCount = 0;
    m_pBrush = nullptr;
    m_pFont = nullptr;
    m_f32CharHeight = 0.0f;
    m_f32SpaceWidth = 0.0f;
    m_Color = 0;
    m_VarColor = 0;
    m_ui32VarsCount = 0;
    m_f32TextSize = 0.0f;
    m_f32Leading = 0.0f;
    m_ui8WAlignType = 0;
    m_bAutoSize = 0;
    m_ui32CurrentBeginLine = 0;
    m_f32NextLineTime = 0.0f;
}

// 0x0006b728 Text2dBlock_Load_maybe (XXL2 IKText2d::Load), every type; K_LEVEL_PLATEFORMS adds a word
// before (read into a local and dropped) and a reference after.
int32_t IKText2d::Load(IKFile* file, int32_t type) {
    if (type == K_LEVEL_PLATEFORMS) {
        uint32_t dropped = 0;
        ReadU32LE(file, &dropped);
    }
    IKFile_ReadRef(file, &m_pLocManager);
    ReadF32LE(file, &m_vBoxSize.m_fX);  // one 8-byte read, both words swapped
    ReadF32LE(file, &m_vBoxSize.m_fY);
    ReadU32LE(file, &m_ui32BoxLinesCount);
    // 0x00010a40 WStr_CopyReturnEnd(m_wszText, L" ") (TOC1 -0x6e18 -> 0xc296a8, the UTF-16 " ").
    m_wszText[0] = 0x20;
    m_wszText[1] = 0;
    uint32_t length = 0;
    ReadU32LE(file, &length);
    if (length != 0xffffffffu) {
        // Read(text, 2 * length), then lhbrx/sth on each character: the file's UTF-16LE, which is the
        // host order here. No bound against the 400 characters (as the original).
        ReadRaw(file, m_wszText, length * 2);
        m_wszText[length] = 0;
    }
    ReadS32LE(file, &m_i32FontId);
    RwStream* stream = file->m_pRwStream;
    RwStreamFindChunk(stream, 0x1a2, nullptr, nullptr);  // result ignored
    m_pBrush = Rt2dBrushStreamRead(stream);       // STUB(C1.4): kept as its stream record
    ReadS32LE(file, &m_i32FontId);  // read again (XXL2 does the same)
    ReadF32LE(file, &m_f32CharHeight);
    ReadF32LE(file, &m_f32SpaceWidth);
    ReadRaw(file, &m_Color, 4);
    ReadRaw(file, &m_VarColor, 4);
    ReadF32LE(file, &m_f32TextSize);
    ReadF32LE(file, &m_f32Leading);
    ReadU8(file, &m_ui8WAlignType);
    ReadU8(file, &m_ui8HAlignType);
    ReadU8(file, &m_bAutoSize);
    ReadF32LE(file, &m_f32NextLineTime);
    m_f32NextLineTimeLeft = 0.0f;
    m_ui32CurrentBeginLine = 0;
    if (type == K_LEVEL_PLATEFORMS) IKFile_ReadRef(file, &m_pTextAccessor);
    return 1;
}

// 0x0006a1f0 TextData_SetColor (IKText2d vt+0x44)
void IKText2d::SetColor(const uint8_t* color) {
    std::memcpy(&m_Color, color, 4);
    RwRGBA* rgba = reinterpret_cast<RwRGBA*>(&m_Color);
    Rt2dBrushSetRGBA(m_pBrush, rgba, rgba, rgba, rgba);
}

// 0x0006b2d8 CText2d_TokenizeText_maybe: with a text object in the accessor (+0x10; read without a null
// test of the accessor, which only level texts have), that text through IKText2d vt+0x34; else the loaded
// text split into words, then the layout.
int32_t IKText2d::TokenizeText() {
    IKSerializable* locText = m_pTextAccessor->m_pText;
    if (locText != nullptr) {
        SetTextById(locText);
        return 1;
    }
    SplitWords(this);
    ComputeLayout();
    return 1;
}

// 0x0006a468 TextData_ComputeLayout_maybe. Lines are filled word by word from x = the space width while
// the word and its trailing space fit (a "\e" chain must fit with it, unless the chain alone is wider than
// the box); a word that fits on no line is flagged too long (bit 0) and put at (0, 0). Then each line is
// aligned (m_ui8WAlignType: 1 centre, 2 right, 5 justify), the lines placed from y = 1 - (line + 1) x
// line height down, and the block moved by the free height (m_ui8HAlignType: 1 half, 4 all, 5 spread by
// line).
int32_t IKText2d::ComputeLayout() {
    if (m_pFont == nullptr) {
        m_ui32BoxLinesCount = 0;
        return 0;
    }
    uint16_t space[8];
    WStr_FromAscii(space, " ");  // TOC1 -0x6e3c -> 0xac4008
    const float spaceWidth = Rt2dFontGetStringWidth(m_pFont, AsFontString(space), m_f32CharHeight);
    const float leading = m_f32CharHeight * m_f32Leading;  // fmuls
    m_f32SpaceWidth = spaceWidth;
    const float boxWidth = m_vBoxSize.m_fX;
    const float usableHeight = ppc::fmadds(leading, -0x1p+1f, m_vBoxSize.m_fY);  // -2.0f (TOC1 -0x6e38)
    m_ui32BoxLinesCount =
        static_cast<uint32_t>(crt::lroundf((leading + usableHeight) / (m_f32CharHeight + leading)));
    float charHeight = m_f32CharHeight;
    uint32_t line = 0;
    float lines;           // f11: (float)(double) line count
    float linesMinusOne;   // f12: (float)(double)(uint32_t)(line count - 1)
    if (m_ui32WordsCount == 0) {
        lines = 0.0f;
        linesMinusOne = 0x1p+32f;  // (uint32_t)-1 as a float, folded by the compiler (TOC1 -0x6e34)
    } else {
        float cursorY = leading + charHeight;
        uint32_t lineFirst = 0;
        uint32_t word = 0;
        float freeWidth = 0.0f;  // f25: written with each placed word, read only when one was
        for (;;) {
            float x = m_f32SpaceWidth;
            word = lineFirst;
            uint32_t placed = 0;
            uint32_t previousBreaks = 0;
            while (x < boxWidth) {
                if (m_ui32WordsCount <= word) break;
                if (previousBreaks != 0) break;
                const uint8_t flags = m_abWordTooLong[word];
                float chain = 0.0f;
                const float width = Rt2dFontGetStringWidth(m_pFont, AsFontString(m_awszWords[word]), m_f32CharHeight);
                const float after = (x + width) + m_f32SpaceWidth;
                if ((m_abWordTooLong[word] & 4) != 0) {
                    uint32_t next = word + 1;
                    if (next < m_ui32WordsCount) {
                        for (;;) {
                            const uint32_t measured = next;
                            const float nextWidth =
                                Rt2dFontGetStringWidth(m_pFont, AsFontString(m_awszWords[measured]), m_f32CharHeight);
                            ++next;
                            chain = chain + (nextWidth + m_f32SpaceWidth);
                            if (!(next < m_ui32WordsCount)) break;
                            if ((m_abWordTooLong[measured] & 4) == 0) break;
                        }
                    }
                    if (!(chain + width <= boxWidth)) chain = 0.0f;
                }
                if (chain + after < boxWidth) {
                    const float y = 0x1p+0f - cursorY;
                    freeWidth = boxWidth - after;
                    ++placed;
                    m_abWordTooLong[word] = static_cast<uint8_t>(m_abWordTooLong[word] & 0xfe);
                    m_avWordsPos[word].m_fY = y;
                    m_avWordsPos[word].m_fX = x;
                    m_aui16WordsLine[word] = static_cast<uint16_t>(line);
                    ++word;
                }
                x = after;
                previousBreaks = (flags >> 1) & 1u;
            }
            if (placed == 0) {
                m_abWordTooLong[word] = static_cast<uint8_t>((m_abWordTooLong[word] & 0xfe) | 1);
                m_avWordsPos[word].m_fY = 0.0f;
                m_avWordsPos[word].m_fX = 0.0f;
                m_aui16WordsLine[word] = static_cast<uint16_t>(line);
                ++word;
            } else if (m_ui8WAlignType == 2) {
                for (uint32_t k = 0; k < placed; ++k)
                    m_avWordsPos[lineFirst + k].m_fX = freeWidth + m_avWordsPos[lineFirst + k].m_fX;
            } else if (m_ui8WAlignType == 5) {
                if (placed > 1) {
                    const float step = freeWidth / static_cast<float>(static_cast<double>(placed - 1));
                    float offset = step;
                    for (uint32_t k = 1; k < placed; ++k) {
                        m_avWordsPos[lineFirst + k].m_fX = m_avWordsPos[lineFirst + k].m_fX + offset;
                        offset = offset + step;
                    }
                }
            } else if (m_ui8WAlignType == 1) {
                const float half = freeWidth * 0x1p-1f;
                for (uint32_t k = 0; k < placed; ++k)
                    m_avWordsPos[lineFirst + k].m_fX = half + m_avWordsPos[lineFirst + k].m_fX;
            }
            ++line;
            charHeight = m_f32CharHeight;
            if (m_ui32WordsCount <= word) break;
            cursorY = cursorY + (leading + charHeight);
            lineFirst = word;
        }
        lines = static_cast<float>(static_cast<double>(line));
        linesMinusOne = static_cast<float>(static_cast<double>(line - 1u));
    }
    const float textHeight = ppc::fmadds(lines, charHeight, linesMinusOne * leading);
    float freeHeight = usableHeight - textHeight;
    if (m_ui8HAlignType == 4) {
        for (uint32_t i = 0; i < m_ui32WordsCount; ++i) m_avWordsPos[i].m_fY = m_avWordsPos[i].m_fY - freeHeight;
    } else if (m_ui8HAlignType == 5) {
        if (line > 1) {
            freeHeight = freeHeight / linesMinusOne;
            for (uint32_t i = 0; i < m_ui32WordsCount; ++i) {
                const float lineIndex = static_cast<float>(static_cast<double>(m_aui16WordsLine[i]));
                m_avWordsPos[i].m_fY = m_avWordsPos[i].m_fY - freeHeight * lineIndex;
            }
        }
    } else if (m_ui8HAlignType == 1) {
        freeHeight = freeHeight * 0x1p-1f;
        for (uint32_t i = 0; i < m_ui32WordsCount; ++i) m_avWordsPos[i].m_fY = m_avWordsPos[i].m_fY - freeHeight;
    }
    m_f32NextLineTimeLeft = m_f32NextLineTime;
    m_ui32CurrentBeginLine = 0;
    return 1;
}

// 0x0006aa60 Text2dPart_ReplaceButtonGlyphTokens_maybe: "#$n#" (n = a CKInput sequence id) becomes the
// glyph of the button bound to that sequence's action and is remembered in the token table (Render
// resolves it again every frame); "#£a_b_c_#" becomes the glyph of action c of configuration b of the
// input project named a, once. The token is replaced by its glyph in place (the rest moves up). 1 when a
// token was replaced.
uint8_t IKText2d::ReplaceButtonGlyphTokens() {
    CKInput* input = g_pEngine->m_input;
    // The sscanf formats are copied from 0xa6f3c0 ("#@_%d_%d_%d_#" and "#$%d#"); the first gets '$' at
    // [1] before its use, as does the ASCII copy of the "#£" token.
    char tripleFormat[] = "#@_%d_%d_%d_#";
    const char singleFormat[] = "#$%d#";
    m_ui16ButtonTokensCount = 0;
    uint16_t* p = m_wszText;
    uint16_t c = *p;
    if (c == 0) return 0;
    uint8_t replaced = 0;
    uint32_t index = 0;
    char ascii[408];
    for (;;) {
        uint16_t* next = p + 1;
        if (c == 0x23) {  // '#'
            c = *next;
            if (c == 0x24) {  // '$'
                Wcs_ToAscii(ascii, p);
                // BUG(original): the id is an uninitialised local when the token does not parse (0 here).
                int32_t id = 0;
                std::sscanf(ascii, singleFormat, &id);
                // BUG(original): without a closing '#' the copy reads from null.
                WStr_CopyReturnEnd(p, Wcs_FindChar(next, 0x23));
                const uint16_t count = m_ui16ButtonTokensCount;
                if (count <= 5) {
                    // BUG(original): the bound lets a sixth token (count 5) land on the count itself (+0x712).
                    m_ui16ButtonTokensCount = static_cast<uint16_t>(count + 1);
                    const uint16_t entry = static_cast<uint16_t>((index << 8) + static_cast<uint32_t>(id));
                    if (count < 5) {
                        m_aui16ButtonTokens[count] = entry;
                    } else {
                        m_ui16ButtonTokensCount = entry;
                    }
                }
                const InputSequenceEntry* bound = input->FindButtonIconGlyph(id);
                uint16_t glyph = 0x3f;  // '?'
                if (bound != nullptr)
                    glyph = input->GetActionButtonGlyph(bound->m_unk00, bound->m_unk04, bound->m_unk08,
                                                        bound->m_unk0c, 0);
                *p = glyph;
                c = *next;
                replaced = 1;
            } else if (c == 0xa3) {  // '£'
                Wcs_ToAscii(ascii, p);
                ascii[1] = '$';
                tripleFormat[1] = '$';
                // BUG(original): uninitialised locals when the token does not parse (0 here).
                int32_t project = 0;
                int32_t config = 0;
                int32_t action = 0;
                std::sscanf(ascii, tripleFormat, &project, &config, &action);
                const uint16_t glyph = input->GetActionButtonGlyph(
                    static_cast<uint32_t>(project), static_cast<uint32_t>(config), static_cast<uint32_t>(action), 0, 0);
                WStr_CopyReturnEnd(p, Wcs_FindChar(next, 0x23));
                *p = glyph;
                c = *next;
                replaced = 1;
            }
        } else {
            c = *next;
        }
        if (c == 0) break;
        ++index;
        p = next;
    }
    return replaced;
}

// 0x0006ad78 Text2dPart_SubstituteVariables_maybe: every "%name%" becomes the decimal value of the loc
// manager's text variable `name` (1 when there is none), zero-padded to the variable's digits behind a
// " "; m_pwszVars point at the values (Render draws those words in m_VarColor). 1 when the text had one.
// BUG(original): the stack tables hold 5 offsets, 6 lengths and 7 starts and m_pwszVars 5, with no bound;
// the result (409 characters on the stack, then over the 400 of m_wszText) is not bounded either.
int32_t IKText2d::SubstituteVariables() {
    uint16_t* const text = m_wszText;
    if (text[0] == 0) return 0;  // (the original also tests &m_wszText against null)
    m_ui32VarsCount = 0;
    int32_t offsets[5] = {0, 0, 0, 0, 0};
    int32_t lengths[6];
    const uint16_t* starts[7];
    uint32_t startCount = 0;
    uint32_t endCount = 0;
    uint32_t vars = 0;
    uint32_t inVar = 0;
    int32_t length = 0;  // uninitialised before the first '%' in the original (only read after one)
    const uint16_t* p = text;
    uint16_t c = *p;
    for (;;) {
        if (c == 0x25) {  // '%'
            if (inVar == 0) {
                starts[startCount++] = p;
                inVar = 1;
                length = 0;
            } else {
                inVar = 0;
                ++vars;
                lengths[endCount++] = length;
                m_ui32VarsCount = vars;
            }
        } else {
            length += static_cast<int32_t>(inVar & 1);
        }
        ++p;
        c = *p;
        if (c == 0) break;
    }
    if (vars == 0) return 0;
    for (uint32_t i = 0; i < vars; ++i) m_pwszVars[i] = nullptr;  // memset(m_pwszVars, 0, vars * 4)

    uint16_t result[409];
    uint16_t* out = result;
    const uint16_t* src = text;
    int32_t outIndex = 0;
    uint32_t var = 0;
    c = *src;
    for (;;) {
        if (var < m_ui32VarsCount && starts[var] == src) {
            const int32_t nameLength = lengths[var];
            uint16_t nameW[400];
            std::memcpy(nameW, src + 1, static_cast<size_t>(nameLength) * 2);
            nameW[nameLength] = 0;
            char nameA[400];
            Wcs_ToAscii(nameA, nameW);
            CLocManager* loc = static_cast<CLocManager*>(m_pLocManager);
            int32_t index = -1;
            uint32_t value = 1;
            if (loc != nullptr) {
                index = CLocManager_FindTextVariable(loc, nameA);
                value = 1;
                if (index >= 0) value = CLocManager_GetTextVariableValue(loc, static_cast<uint32_t>(index));
            }
            uint16_t number[400];
            WStr_SprintfInt(number, "%d", static_cast<int32_t>(value));  // TOC1 -0x6e1c -> 0xac4010 "%d"
            // BUG(original): called with the loc manager even when it is null (a read at +0xc4).
            const int32_t digits = static_cast<int32_t>(CLocManager_GetTextVariable(loc, static_cast<uint32_t>(index)));
            const int32_t pad = digits - static_cast<int32_t>(Wcs_Length(number));
            uint16_t padded[255];
            WStr_CopyReturnEnd(padded, kSpaceW);
            if (pad > 0) {
                int32_t added = 0;
                do {
                    ++added;
                    WStr_CatReturnEnd(padded, kZeroW);
                } while (pad != added);
                WStr_CatReturnEnd(padded, number);
                WStr_CopyReturnEnd(number, padded);
            }
            ++var;
            const uint32_t n = Wcs_Length(number);
            std::memcpy(out, number, n * 2);
            out += n;
            offsets[var - 1] = outIndex;
            outIndex += static_cast<int32_t>(n);
            src = src + nameLength + 2;
        } else {
            *out++ = c;
            ++src;
        }
        c = *src;
        if (c == 0) break;
        // BUG(original): also counted after a substitution, so each later variable's offset is one too far
        // (its m_pwszVars entry misses the word start and Render does not colour it).
        ++outIndex;
    }
    *out = 0;
    WStr_CopyReturnEnd(text, result);
    for (uint32_t i = 0; i < m_ui32VarsCount; ++i) m_pwszVars[i] = text + offsets[i];
    return 1;
}

// 0x0006c1f8 TextData_SetText: null clears the accessor's text, the variables, words and auto-size byte
// (0). Else the text (or "-TEXT TOO BIG-" from 400 characters) is copied, its variables and pad tokens
// substituted, split into words and laid out.
int32_t IKText2d::SetText(const uint16_t* text) {
    if (text == nullptr) {
        CKLocTextAccessor* accessor = m_pTextAccessor;
        if (accessor->m_texts.m_pBlock == nullptr) {
            accessor->m_pText = nullptr;
        } else {
            accessor->m_texts.m_pBlock[0] = nullptr;
        }
        m_ui32VarsCount = 0;
        m_ui32WordsCount = 0;
        m_bAutoSize = 0;
        return 0;
    }
    if (Wcs_Length(text) < 400) {
        WStr_CopyReturnEnd(m_wszText, text);
    } else {
        WStr_CopyReturnEnd(m_wszText, kTextTooBig);
    }
    SubstituteVariables();
    ReplaceButtonGlyphTokens();
    SplitWords(this);
    // 0x6c308: vt+0x00 (0x9943d8 TextData_FitSizeToText_maybe, XXL2 AutoSize) when m_bAutoSize is set, else
    // the layout; SplitWords has just cleared the byte, so only the layout is reachable (as on the PS3).
    ComputeLayout();
    return 1;
}

// 0x0006c668 TextData_SetTextFromLocString: the text object goes into the accessor (its list's first
// entry when it has a list), then SetText with the string of the accessor's +0x10 text (null: none).
uint8_t IKText2d::SetTextFromLocString(IKSerializable* text) {
    CKLocTextAccessor* accessor = m_pTextAccessor;
    if (accessor->m_texts.m_pBlock == nullptr) {
        accessor->m_pText = text;
    } else {
        accessor->m_texts.m_pBlock[0] = text;
    }
    const uint16_t* string = nullptr;
    IKSerializable* locText = m_pTextAccessor->m_pText;
    if (locText != nullptr) string = LocString_GetText(static_cast<CKLocText*>(locText));
    return static_cast<uint8_t>(SetText(string));
}

// 0x0006bd10 Text2dPart_RefreshFromLocString_maybe: SetText again from the accessor's +0x10 text (0
// without one); a null string leaves " " and no words.
int32_t IKText2d::RefreshFromLocString() {
    if (m_pTextAccessor == nullptr || m_pTextAccessor->m_pText == nullptr) return 0;
    const uint16_t* string = LocString_GetText(static_cast<CKLocText*>(m_pTextAccessor->m_pText));
    if (string == nullptr) {
        WStr_CopyReturnEnd(m_wszText, kSpaceW);
        m_ui32VarsCount = 0;
        m_ui32WordsCount = 0;
        m_bAutoSize = 0;
        return 0;
    }
    if (Wcs_Length(string) < 400) {
        WStr_CopyReturnEnd(m_wszText, string);
    } else {
        WStr_CopyReturnEnd(m_wszText, kTextTooBig);
    }
    SubstituteVariables();
    ReplaceButtonGlyphTokens();
    SplitWords(this);
    // 0x6be48: the same unreachable AutoSize call as SetText's.
    ComputeLayout();
    return 1;
}

// 0x0006c0a8 TextData_OnEvent_maybe (a jump table on what, 0..5; enabled = the node's bit 1).
void IKText2d::RecursiveNodeReach(uint8_t enabled, uint8_t what, void* data) {
    switch (what) {
    case 0:  // bind the font
        m_pFont = nullptr;
        if (m_i32FontId < 0) return;
        m_pFont = CManager2d_GetFont(g_pEngine->m_manager2d, static_cast<uint32_t>(m_i32FontId));
        if (m_pFont == nullptr) return;
        m_f32CharHeight = m_f32TextSize * 0x1.ba5e36p-4f;  // 0.108f (TOC1 -0x6e04, 0x3ddd2f1b)
        m_f32SpaceWidth = Rt2dFontGetStringWidth(m_pFont, AsciiSpaceAsFontString(m_pFont), m_f32CharHeight);
        return;
    case 1:
        if (enabled != 0) ComputeLayout();
        return;
    case 2: {  // data: the id of a font that goes away
        if (m_i32FontId == *static_cast<const int32_t*>(data)) {
            m_i32FontId = -1;
            m_pFont = nullptr;
        }
        return;
    }
    case 3: {  // data: {font id, in-use word}; bit 0 set when this text uses the font
        if (m_i32FontId < 0) return;
        int32_t* query = static_cast<int32_t*>(data);
        if (m_i32FontId == query[0]) query[1] |= 1;  // ld/ori 1/std: the low bit of the second word
        return;
    }
    case 5:
        if (enabled != 0) RefreshFromLocString();
        return;
    default:  // 4 and above 5: nothing
        return;
    }
}

// 0x009986c8 DrawUITextLinesWithLayout. The node's position is divided by the constant scale (where it is
// not 1), aligned by the box (x by its width over the aspect: -1/2 or -1; y by its height: +1/2 or +1,
// from y - 1), and becomes the CTM translation (x times the aspect) after the scale. The "#$n#" glyphs are
// resolved again (last token first). Each word of the visible lines [begin, begin + box lines) is drawn
// at its position, one line height per scrolled line up, rotated, in m_VarColor when it is the next
// substituted variable. Then the scroll timer: every m_f32NextLineTime seconds the first line moves down
// one while lines remain below the box.
uint8_t IKText2d::Render(float rotation, const CVector2* position, const CVector2* scale, uint8_t wAlign,
                         uint8_t hAlign, IKTime* time) {
    if (m_pFont == nullptr) return 0;
    float y = position->m_fY;
    float x = position->m_fX;
    const uint32_t color = m_Color;
    const uint32_t varColor = m_VarColor;
    RwRGBA* const colorRgba = reinterpret_cast<RwRGBA*>(&m_Color);
    RwRGBA* const varColorRgba = reinterpret_cast<RwRGBA*>(&m_VarColor);
    if (scale->m_fX != 0x1p+0f) x = x / scale->m_fX;
    if (scale->m_fY != 0x1p+0f) y = y / scale->m_fY;
    y = y - 0x1p+0f;
    const float boxWidth = m_vBoxSize.m_fX / g_pEngine->m_manager2d->m_fAspect;
    const float boxHeight = m_vBoxSize.m_fY;
    if (wAlign == 1) {
        x = ppc::fmadds(boxWidth, -0x1p-1f, x);
    } else if (wAlign == 2) {
        x = x - boxWidth;
    }
    if (hAlign == 1) {
        y = ppc::fmadds(boxHeight, 0x1p-1f, y);
    } else if (hAlign == 2) {
        y = y + boxHeight;
    }
    const float lineHeight = ppc::fmadds(m_f32Leading, m_f32CharHeight, m_f32CharHeight);

    CKInput* input = g_pEngine->m_input;
    for (uint32_t i = m_ui16ButtonTokensCount; i != 0; --i) {
        const uint16_t entry = ButtonTokenAt(this, i - 1);
        const uint32_t id = entry & 0xffu;
        if (id == 0xff) continue;
        const InputSequenceEntry* bound = input->FindButtonIconGlyph(static_cast<int32_t>(id));
        uint16_t glyph = 0x3f;  // '?'
        if (bound != nullptr)
            glyph = input->GetActionButtonGlyph(bound->m_unk00, bound->m_unk04, bound->m_unk08, bound->m_unk0c, 0);
        m_wszText[(entry >> 8) & 0xffu] = glyph;
    }

    const float aspect = g_pEngine->m_manager2d->m_fAspect;
    Rt2dCTMPush();
    x = x * aspect;
    Rt2dCTMScale(scale->m_fX, scale->m_fY);
    Rt2dCTMTranslate(x, y);
    uint32_t lastLine = 0;
    uint32_t var = 0;
    for (uint32_t i = 0; i < m_ui32WordsCount; ++i) {
        const uint32_t line = m_aui16WordsLine[i];
        if (lastLine < line) lastLine = line;
        const uint16_t* word = m_awszWords[i];
        if (word == nullptr) continue;
        if ((m_abWordTooLong[i] & 1) != 0) continue;
        if (line < m_ui32CurrentBeginLine) continue;
        if (!(line < m_ui32CurrentBeginLine + m_ui32BoxLinesCount)) continue;
        bool inVarColor = false;
        if (color != varColor && var < m_ui32VarsCount && m_pwszVars[var] == word) {
            ++var;
            inVarColor = true;
            Rt2dBrushSetRGBA(m_pBrush, varColorRgba, varColorRgba, varColorRgba, varColorRgba);
        }
        Rt2dCTMPush();
        const float scrolled = static_cast<float>(static_cast<double>(m_ui32CurrentBeginLine));
        Rt2dCTMTranslate(m_avWordsPos[i].m_fX, ppc::fmadds(lineHeight, scrolled, m_avWordsPos[i].m_fY));
        Rt2dCTMRotate(rotation);
        Rt2dCTMScale(0x1p+0f, 0x1p+0f);
        RwV2d anchor;
        anchor.x = 0.0f;
        anchor.y = 0.0f;
        // 0x00a3ce28 BridgeDispatchUIFontRenderCallback -> 0x0070ccc8 Rt2dFontShow
        Rt2dFontShow(m_pFont, AsFontString(word), m_f32CharHeight, &anchor, m_pBrush);
        Rt2dCTMPop();
        if (inVarColor) Rt2dBrushSetRGBA(m_pBrush, colorRgba, colorRgba, colorRgba, colorRgba);
    }
    Rt2dCTMPop();
    m_f32NextLineTimeLeft = m_f32NextLineTimeLeft - time->m_afDeltaTime[IKTime::SCALABLE_GAME_TIME];
    if (m_f32NextLineTimeLeft < 0.0f) {
        m_f32NextLineTimeLeft = m_f32NextLineTime;
        if (static_cast<int32_t>(lastLine - m_ui32CurrentBeginLine - m_ui32BoxLinesCount) >= 0) ++m_ui32CurrentBeginLine;
    }
    return 1;
}

// 0x00998bc0 TextData_SetFont_maybe (IKText2d vt+0x40, XXL2 SetFontId): font and loc manager reset, then
// CManager2d's font `id`; with one, the id, the character height (m_f32TextSize x 0.108f, TOC1 -0x6e04)
// and the layout. The space width stays 0 (RecursiveNodeReach(0) measures it; this does not). 1 with a font.
uint8_t IKText2d::SetFont(uint32_t id) {
    m_i32FontId = -1;
    m_pLocManager = static_cast<IKSerializable*>(g_pEngine->m_locManager);
    m_pFont = nullptr;
    m_f32SpaceWidth = 0.0f;
    m_f32CharHeight = 0.0f;
    CManager2d* manager = g_pEngine->m_manager2d;
    if (manager == nullptr) return 0;
    Rt2dFont* font = CManager2d_GetFont(manager, id);
    m_pFont = font;
    if (font == nullptr) return 0;
    m_i32FontId = static_cast<int32_t>(id);
    m_f32CharHeight = m_f32TextSize * 0x1.ba5e36p-4f;  // fmuls 0.108f
    ComputeLayout();
    return 1;
}

// 0x0006c580 TextData_SetTextClearLocRef_maybe
uint8_t IKText2d::SetTextClearLocRef(const uint16_t* text) {
    const uint8_t done = SetText(text) != 0 ? 1 : 0;
    CKLocTextAccessor* accessor = m_pTextAccessor;
    if (accessor != nullptr) {
        if (accessor->m_texts.m_pBlock != nullptr) {
            accessor->m_texts.m_pBlock[0] = nullptr;
        } else {
            accessor->m_pText = nullptr;
        }
    }
    return done;
}

// 0x0006a198 Text2dBlock_GetTextId_maybe
IKSerializable* IKText2d::GetTextId() const { return m_pTextAccessor->m_pText; }


// 0x0006b1b8 TextData_SetTextAscii
void IKText2d::SetTextAscii(const char* text) {
    uint16_t wide[404];  // 808 bytes on the PS3 stack
    if (std::strlen(text) < 400) {
        WStr_FromAscii(wide, text);
    } else {
        WStr_CopyReturnEnd(wide, kTextTooBig);
    }
    SetTextWide(wide);  // vt+0x38
}
