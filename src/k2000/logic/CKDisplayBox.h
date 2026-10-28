// CKDisplayBox.h - a display box shape (key 0x604c, vtable 0xb16e10, size 0x20). Original unit:
// CKDisplayBox.cpp. No XXL2 class of this name; it adds nothing to CMultiGeometryBasic (same size, its
// Load is the base's).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/CMultiGeometryBasic.h"

class CKDisplayBox : public CMultiGeometryBasic {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x181)
    DOTD_DECLARE_FACTORIES(CKDisplayBox)

    CKDisplayBox() {}  // inlined in 0x00094e78 CKDisplayBox_Create: only the vtable
    ~CKDisplayBox() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00094cf8 CKDisplayBox_Load
};
static_assert(CKDisplayBox::kClassKey == 0x604c, "key");
DOTD_ASSERT_SIZE(CKDisplayBox, 0x20);
