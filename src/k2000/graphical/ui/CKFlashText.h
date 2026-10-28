// CKFlashText.h - a text field of a Flash interface (key 0x7cd, vtable 0xb16320, size 0x44). Original unit:
// CKFlashText.cpp (0x75960-0x777f8). XXL2: K/KModules/KGL/2d/Maestro/FlashObject/CKFlashText.h: the same
// members read in the same order, except that DotD reads a CKLocTextAccessor reference where XXL2 reads
// the text id.
//
// The Rt2d string objects of the movie whose text is the field's label (case-insensitive) are gathered in
// m_vpObject by the interface's PostLoad (CKFlashUI_CollectNamedStrings_cb_maybe 0x6e088); the field then
// writes its localised text, font and box width into every one of them.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/ui/IKFlashObject.h"
#include "k2000/util/TVector.h"

class CKLocTextAccessor;
class CKFlashUI;

class CKFlashText : public IKFlashObject {
public:
    DOTD_CLASS_KEY(kCategoryGraphical, 0x1f)
    DOTD_DECLARE_FACTORIES(CKFlashText)

    CKFlashText();  // inlined in 0x00076a40 CKFlashText_Create (copy 0x759b0 unreferenced)
    ~CKFlashText() override;                                                // vt+0x00 / +0x04  0x76bd0 / 0x76b48
    int32_t IsKindOfClass(uint32_t key) override {                          // vt+0x08 0x9993f8
        return key == 0x7cd || key == 0x74d || key == 0xc;
    }
    void Destroy() override;                                                // vt+0x10 0x00075fb8 CKFlashText_Destroy
    // vt+0x24 0x75f00 CKFlashText_RecursiveRegistration: with type 0, registers itself and its accessor
    // with the saving manager (engine +0x50 vt+0x24). STUB(C1.6): the saving manager is not ported.
    int32_t Load(IKFile* file, int32_t type) override;                      // vt+0x2c 0x00075ce8 CKFlashText_Load
    int32_t PostLoad(int32_t type) override;                                // vt+0x30 0x000773e0 CKFlashText_PostLoad
    void GetRt2dObject(TVector<Rt2dObject*, 1>* objects) override;          // vt+0x50 0x00076238
    void Vf54() override;                                                   // vt+0x54 0x00075ad8 CKFlashText_vf54
    uint8_t GetScreenAnchor(CVector2* position, CVector2* size, uint8_t* rgba) override;  // vt+0x60 0x000765f8
    void RegisterObjects() override;                                        // vt+0x64 0x000761a8 CKFlashText_vf64
    void ApplyColorMultiplier() override;                                   // vt+0x68 0x000760c0

    // XXL2 names where the PS3 function matches.
    void RefreshText();                       // 0x00075b10 CKFlashText_RefreshStrings_maybe
    void ApplyTextAlignment();                // 0x00076a90 CKFlashText_UpdateStringHeights_maybe (inlined in many)
    void SetText(const char* text);           // 0x00077208 CKFlashText_SetText_maybe
    void SetTextW(const uint16_t* text);      // 0x00077048 CKFlashText_SetTextW_maybe
    void SetTextId(IKSerializable* text);     // 0x00076560 CKFlashText_SetTextId_maybe (a CKStdText)
    void ChangeTextFont(const char* font);    // 0x00075c58 CKFlashText_SetFont_maybe
    void SetFontName(const char* font);       // 0x00076f20 CKFlashText_SetFontName_maybe
    void SetFontId(int32_t fontId);           // 0x000774b0 CKFlashText_SetFontIndex_maybe
    void ReloadFont();                        // 0x00077600 CKFlashText_ApplyFont_maybe
    // 0x00076358 CKFlashText_SetFontForStrings_maybe: a new font for every object, keeping its text
    // (narrowed, or widened when the font is not unicode).
    void InternChangeTextFont(const char* font, int32_t unicode);
    void RestoreTextLabel();                  // 0x000764e0 CKFlashText_ApplyTextToStrings_maybe

    CKFlashUI* GetFlashUI() const { return reinterpret_cast<CKFlashUI*>(m_pFlashUI); }

    // +0x24 the Rt2d string objects (block +0x24, capacity +0x28, count +0x2c). Load allocates room for 2.
    TVector<Rt2dObject*, 2> m_vpObject;
    CKLocTextAccessor* m_pTextAccessor;  // +0x30 CKLocTextAccessor (0xe46, a reference; XXL2 reads Int32 m_i32TextId here)
    uint8_t m_bNoTextIdNeeded;    // +0x34 (+0x35..+0x37: padding the original never writes)
    float m_fBoxWidth;            // +0x38
    uint32_t m_JustifType;        // +0x3c XXL2 Rt2dJustificationType
    int32_t m_i32FontId;          // +0x40
};
DOTD_ASSERT_SIZE(CKFlashText, 0x44);
DOTD_ASSERT_OFFSET(CKFlashText, m_vpObject, 0x24);
DOTD_ASSERT_OFFSET(CKFlashText, m_pTextAccessor, 0x30);
DOTD_ASSERT_OFFSET(CKFlashText, m_bNoTextIdNeeded, 0x34);
DOTD_ASSERT_OFFSET(CKFlashText, m_fBoxWidth, 0x38);
DOTD_ASSERT_OFFSET(CKFlashText, m_JustifType, 0x3c);
DOTD_ASSERT_OFFSET(CKFlashText, m_i32FontId, 0x40);
