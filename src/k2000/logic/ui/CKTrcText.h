// CKTrcText.h - a localised TRC text (key 0x684c, vtable 0xb145f0, PS3 size 0x1c; "Texte TRC": the
// platform-requirement messages). Original unit: CKTrcText.cpp (0x36a90-0x36fc8). Not in XXL2. No
// fields of its own.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/ui/CKLocText.h"

class CKTrcText : public CKLocText {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x1a1)
    DOTD_DECLARE_FACTORIES(CKTrcText)

    // The live constructor is inlined in CKTrcText_Create 0x36ed0 / CreateArray 0x36e18 (CKTrcText_Construct
    // 0x36d00 is dead): CKLocText_Construct, then the vtable.
    CKTrcText() {}
    ~CKTrcText() override {}  // vt+0x00 / +0x04  0x36ca0 / 0x36c58

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00036b90 CKTrcText_Load
    // vt+0x58 0x36c30 CKTrcText_InitGameData and vt+0x64 0x36c08 CKTrcText_ClearGameData_maybe only call
    // CKLocText's.
};
DOTD_ASSERT_SIZE(CKTrcText, 0x1c);
