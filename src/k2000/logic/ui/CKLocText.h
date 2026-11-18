// CKLocText.h - a localised text (key 0x680c, vtable 0xb144a8, PS3 size 0x1c), the base of CKStdText and
// CKTrcText. Original units: CKLocText.cpp (0x2ccb8-0x2cdd8) and CKLocText_2.cpp (0x35948-0x35e70). Not
// in XXL2. The text itself is not in the object's data: CLocManager_Load (mode 3, the language's GLC
// file) points +0x18 at the string in its table.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/ui/KBase700C.h"

class CKLocText : public KBase700C {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x1a0)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9944d0
        return key == 0x680c || key == 0x700c || key == 0x330c || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKLocText)

    CKLocText() {}            // 0x00035be0 CKLocText_Construct: KBase700C's, then the vtable
    ~CKLocText() override {}  // vt+0x00 / +0x04  0x35b48 / 0x35b00

    // vt+0x24 0x00035998 CKLocText_RecursiveRegistration: returns 1, nothing registered (IKGameObject's not called).
    void RecursiveRegistration(int32_t /*type*/) override {}
    // vt+0x30 0x35a28 CKLocText_PostLoad: KBase700C's 0x2cc40 (IKGameObject's 0x42e40), then 1: inherited.
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00035a50 CKLocText_Load
    void InitializeGameData() override;                 // vt+0x58 0x00035ac8 CKLocText_InitGameData
    // vt+0x64 0x35aa0 CKLocText_ClearGameData_maybe only calls IKGameObject's.

    // +0x18 the text (UTF-16, 16-bit wchar_t): CLocManager_Load (0x37c20, mode 3) stores the address of
    // the text's string in the language table, or 0 for an empty string; LocString_GetText (0x35d28)
    // returns it while the loc manager is enabled. Name ours (Ghidra: none).
    const uint16_t* m_pText;
};
DOTD_ASSERT_SIZE(CKLocText, 0x1c);
DOTD_ASSERT_OFFSET(CKLocText, m_pText, 0x18);

// 0x00035cc0 LocString_CopyText (CKLocText_2.cpp): copies the text (UTF-16) into dst.
void LocString_CopyText(const CKLocText* text, uint16_t* dst);
// 0x00035d28 LocString_GetText (CKLocText_2.cpp): the text's string, or " " without localised game data.
const uint16_t* LocString_GetText(const CKLocText* text);
