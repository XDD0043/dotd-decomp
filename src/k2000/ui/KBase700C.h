// KBase700C.h - the unregistered base of the localised texts (key 0x700c, vtable 0xb13f40, PS3 size
// 0x18; Ghidra CKTextBase_700c_maybe). DotD only (XXL2 has no CKLocText family), so it keeps the
// placeholder name. Original units: CKTextBase.cpp (0x2cc38-0x2ccb8) and the head of CKLocText.cpp
// (0x2ccb8-0x2cdd8: its constructor, destructors and Destroy). No fields of its own: its Load is
// IKGameObject's.
#pragma once
#include <cstdint>

#include "Spyro2008/logic/IKGameObject.h"
#include "k2000/core/Layout.h"

class KBase700C : public IKGameObject {
public:
    KBase700C() {}            // 0x0002cd18 (Ghidra CKLocText_ConstructBase_maybe): IKGameObject_ConstructBase, vtable
    ~KBase700C() override {}  // vt+0x00 / +0x04  0x2cd50 / 0x2cd90

    int32_t GetClassType() override { return 0xc; }    // vt+0x14 0x993db8
    int32_t GetClassID() override { return 0x1c0; }    // vt+0x18 0x993dc0
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0002cc68 CKTextBase_700c_maybe_Load
    // vt+0x10 0x2ccb8 (Ghidra CKLocText_Destroy) only calls IKGameObject_Destroy.
};
DOTD_ASSERT_SIZE(KBase700C, 0x18);
