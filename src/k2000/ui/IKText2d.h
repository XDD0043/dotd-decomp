// IKText2d.h - the text part of the 2D text nodes (unregistered, size 0x718; XXL2:
// K/KModules/KGL/2d/IKText2d.h). The second base of CText2d (at +0x28, vtable = CText2d's + 0x9c).
// Original unit: TextData.cpp (0x6b260 constructor, 0x6b728 Load; Ghidra: Text2dBlock_*/TextData_*).
//
// The members follow XXL2's in order and size (WChar = 2 bytes), with fewer variable slots (5, XXL2 10)
// and the three alignment bytes moved after m_f32NextLineTimeLeft; the constructor's defaults agree
// (m_i32FontId -1, m_ui8HAlignType 3). DotD reads one word between m_vBoxSize and the text where XXL2
// reads two (m_ui32BoxLinesCount, m_i32TextId); the layout (0x6a468) computes +0x10 as the box's line
// count, so it is XXL2's m_ui32BoxLinesCount. DotD adds +0x708..+0x717 (the pad-button tokens and the
// text accessor).
//
// The text path: Load reads the text; CText2d_PostLoad (0x66628) tokenises it (0x6b2d8), or, when the
// accessor holds a text object, sets that object's localised string (SetTextById, IKText2d vt+0x34 ->
// SetTextFromLocString 0x6c668 -> SetText 0x6c1f8: copy, %variables%, #$n# pad glyphs, tokenise). The
// fonts come with RecursiveNodeReach (0x6c0a8) event 0; Render (0x9986c8) draws the words line by line.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/math/CVector2.h"

class CKLocTextAccessor;
class IKFile;
class IKSerializable;
class IKTime;
struct Rt2dBrush;
struct Rt2dFont;

class IKText2d {
public:
    IKText2d();  // 0x0006b260 CText2d_ConstructTextPart_maybe (XXL2 IKText2d::IKText2d)
    virtual ~IKText2d() {}
    virtual int32_t Load(IKFile* file, int32_t type);  // 0x0006b728 Text2dBlock_Load_maybe (XXL2 IKText2d::Load)
    // vt+0x44 0x0006a1f0 TextData_SetColor (XXL2 IKText2d::SetColor): the colour word, then the brush's four
    // corners. Called directly (the slot is not declared yet; no front-end class overrides it).
    void SetColor(const uint8_t* color);
    // vt+0x40 0x00998bc0 TextData_SetFont_maybe (XXL2 IKText2d::SetFontId): CManager2d's font `id` with a new
    // character height and layout; 1 when the font exists. Called directly (only CText2d has the part).
    uint8_t SetFont(uint32_t id);
    // vt+0x34 (CText2d's thunk 0x998208 -> 0x66440 CText2d_SetTextById): the text of a localised text object
    // (a CKLocText; the Ghidra name says "id"). The only implementation is CText2d's.
    virtual uint8_t SetTextById(IKSerializable* text) = 0;
    // vt+0x38 (CText2d's thunk 0x998200 -> 0x66398 CText2d_SetTextWide_maybe): a UTF-16 text through the linked
    // text when there is one. The only implementation is CText2d's.
    virtual uint8_t SetTextWide(const uint16_t* text) = 0;
    // 0x0006b1b8 TextData_SetTextAscii: an ASCII text of fewer than 400 characters widened and set through
    // vt+0x38; a longer one becomes "-TEXT TOO BIG-".
    void SetTextAscii(const char* text);

    // 0x0006b2d8 CText2d_TokenizeText_maybe (CText2d_PostLoad, CColorTextButton2d_PostLoad): the accessor's
    // text when it has one, else m_wszText split into words in place, then the layout. Returns 1.
    int32_t TokenizeText();
    // 0x0006a468 TextData_ComputeLayout_maybe: space width, box line count, word positions and lines,
    // horizontal (m_ui8WAlignType) and vertical (m_ui8HAlignType) alignment. 0 without a font.
    int32_t ComputeLayout();
    // 0x0006aa60 Text2dPart_ReplaceButtonGlyphTokens_maybe: "#$n#" and "#£a_b_c_#" tokens -> one pad glyph.
    uint8_t ReplaceButtonGlyphTokens();
    // 0x0006ad78 Text2dPart_SubstituteVariables_maybe: "%name%" -> the loc manager's text variable.
    int32_t SubstituteVariables();
    // 0x0006c1f8 TextData_SetText: copies a UTF-16 text (null: clears), substitutes, tokenises, lays out.
    int32_t SetText(const uint16_t* text);
    // 0x0006c668 TextData_SetTextFromLocString: stores the text object in the accessor, then SetText.
    uint8_t SetTextFromLocString(IKSerializable* text);
    // 0x0006bd10 Text2dPart_RefreshFromLocString_maybe: SetText again from the accessor's text (event 5).
    int32_t RefreshFromLocString();
    // 0x0006c580 TextData_SetTextClearLocRef_maybe: SetText, then the accessor's text object cleared (its
    // list's first entry when it has a list); 1 when SetText succeeded.
    uint8_t SetTextClearLocRef(const uint16_t* text);
    // 0x0006a198 Text2dBlock_GetTextId_maybe: the accessor's +0x10 text object (no null check on the accessor).
    IKSerializable* GetTextId() const;
    // 0x0006c0a8 TextData_OnEvent_maybe (XXL2 IKText2d::RecursiveNodeReach(Bool, UInt8, void*), IKText2d
    // vt+0x30): 0 bind the font, 1 lay out again (enabled), 2 a font id goes away, 3 font-in-use query,
    // 5 refresh from the loc string (enabled).
    void RecursiveNodeReach(uint8_t enabled, uint8_t what, void* data);
    // 0x009986c8 DrawUITextLinesWithLayout (XXL2 IKText2d::Render(const CVector2&, Float, UInt8, UInt8,
    // IKTime*); DotD adds the constant scale): the visible lines' words at position, then the line scroll.
    // 0 without a font, else 1.
    uint8_t Render(float rotation, const CVector2* position, const CVector2* scale, uint8_t wAlign, uint8_t hAlign,
                   IKTime* time);

    IKSerializable* m_pLocManager;   // +0x004 a reference (XXL2 CLocManager*, read the same way)
    CVector2 m_vBoxSize;             // +0x008
    uint32_t m_ui32BoxLinesCount;    // +0x010 read; ComputeLayout sets lround((boxY - 2 leading + leading) / line height)
    uint16_t m_wszText[400];         // +0x014 UTF-16; Load sets " " then reads the file's text over it
    uint32_t m_ui32WordsCount;       // +0x334 (the tokenizer fills the word tables)
    uint16_t* m_awszWords[60];       // +0x338 words inside m_wszText (each ended in place)
    CVector2 m_avWordsPos[60];       // +0x428
    uint16_t m_aui16WordsLine[60];   // +0x608
    // +0x680 per word: bit 0 too long for the box (ComputeLayout), bit 1 a line break follows ("\n"),
    // bit 2 kept with the next word ("\e"; ComputeLayout measures the chain) (_maybe for bit 2).
    uint8_t m_abWordTooLong[60];
    int32_t m_i32FontId;             // +0x6bc the constructor sets -1; Load reads it twice (as XXL2)
    Rt2dFont* m_pFont;               // +0x6c0 RecursiveNodeReach(0): CManager2d's font m_i32FontId
    float m_f32CharHeight;           // +0x6c4 RecursiveNodeReach(0): m_f32TextSize x 0.108
    float m_f32SpaceWidth;           // +0x6c8
    Rt2dBrush* m_pBrush;             // +0x6cc Rt2dBrushStreamRead
    uint32_t m_Color;                // +0x6d0 CColor, read raw (4 file bytes, seen big-endian by the PS3)
    uint32_t m_VarColor;             // +0x6d4 CColor, read raw (the substituted variables' colour)
    uint32_t m_ui32VarsCount;        // +0x6d8
    uint16_t* m_pwszVars[5];         // +0x6dc (XXL2: 10) the substituted values inside m_wszText
    float m_f32TextSize;             // +0x6f0
    float m_f32Leading;              // +0x6f4
    uint32_t m_ui32CurrentBeginLine; // +0x6f8 Load sets 0; Render scrolls it
    float m_f32NextLineTime;         // +0x6fc
    float m_f32NextLineTimeLeft;     // +0x700 Load sets 0
    uint8_t m_bAutoSize;             // +0x704 read third of the three bytes (XXL2's read order)
    uint8_t m_ui8WAlignType;         // +0x705 read first; ComputeLayout: 1 centre, 2 right, 5 justify
    uint8_t m_ui8HAlignType;         // +0x706 read second; the constructor sets 3 (as XXL2); 1 centre, 4 bottom, 5 spread
    uint8_t m_pad707;
    // +0x708 (DotD) the "#$n#" tokens of the text: (character index << 8) + button id, resolved again each
    // Render (the binding can change); name ours.
    uint16_t m_aui16ButtonTokens[5];
    uint16_t m_ui16ButtonTokensCount;  // +0x712 (DotD) the constructor sets 0
    // +0x714 (DotD) a reference, K_LEVEL_PLATEFORMS only (XXL-Editor: ogLocTextAccessor); the tokenizer and
    // SetTextFromLocString use its +0x04 list and +0x10 text.
    CKLocTextAccessor* m_pTextAccessor;
};
DOTD_ASSERT_SIZE(IKText2d, 0x718);
DOTD_ASSERT_OFFSET(IKText2d, m_pLocManager, 0x004);
DOTD_ASSERT_OFFSET(IKText2d, m_vBoxSize, 0x008);
DOTD_ASSERT_OFFSET(IKText2d, m_ui32BoxLinesCount, 0x010);
DOTD_ASSERT_OFFSET(IKText2d, m_wszText, 0x014);
DOTD_ASSERT_OFFSET(IKText2d, m_ui32WordsCount, 0x334);
DOTD_ASSERT_OFFSET(IKText2d, m_awszWords, 0x338);
DOTD_ASSERT_OFFSET(IKText2d, m_avWordsPos, 0x428);
DOTD_ASSERT_OFFSET(IKText2d, m_aui16WordsLine, 0x608);
DOTD_ASSERT_OFFSET(IKText2d, m_abWordTooLong, 0x680);
DOTD_ASSERT_OFFSET(IKText2d, m_i32FontId, 0x6bc);
DOTD_ASSERT_OFFSET(IKText2d, m_pFont, 0x6c0);
DOTD_ASSERT_OFFSET(IKText2d, m_f32CharHeight, 0x6c4);
DOTD_ASSERT_OFFSET(IKText2d, m_f32SpaceWidth, 0x6c8);
DOTD_ASSERT_OFFSET(IKText2d, m_pBrush, 0x6cc);
DOTD_ASSERT_OFFSET(IKText2d, m_Color, 0x6d0);
DOTD_ASSERT_OFFSET(IKText2d, m_VarColor, 0x6d4);
DOTD_ASSERT_OFFSET(IKText2d, m_ui32VarsCount, 0x6d8);
DOTD_ASSERT_OFFSET(IKText2d, m_pwszVars, 0x6dc);
DOTD_ASSERT_OFFSET(IKText2d, m_f32TextSize, 0x6f0);
DOTD_ASSERT_OFFSET(IKText2d, m_f32Leading, 0x6f4);
DOTD_ASSERT_OFFSET(IKText2d, m_ui32CurrentBeginLine, 0x6f8);
DOTD_ASSERT_OFFSET(IKText2d, m_f32NextLineTime, 0x6fc);
DOTD_ASSERT_OFFSET(IKText2d, m_f32NextLineTimeLeft, 0x700);
DOTD_ASSERT_OFFSET(IKText2d, m_bAutoSize, 0x704);
DOTD_ASSERT_OFFSET(IKText2d, m_ui8WAlignType, 0x705);
DOTD_ASSERT_OFFSET(IKText2d, m_ui8HAlignType, 0x706);
DOTD_ASSERT_OFFSET(IKText2d, m_aui16ButtonTokens, 0x708);
DOTD_ASSERT_OFFSET(IKText2d, m_ui16ButtonTokensCount, 0x712);
DOTD_ASSERT_OFFSET(IKText2d, m_pTextAccessor, 0x714);
