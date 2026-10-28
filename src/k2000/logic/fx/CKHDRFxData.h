// CKHDRFxData.h - the data of an HDR effect (key 0xf0c, vtable 0xb1ce10, size 0x18). Original unit:
// CKHDRFxData.cpp (0x1be2a0-0x1be7c0). Its node is CKHDRNodeFx (0xf8c). Not in XXL2; names ours.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/IKFxData.h"

class CKHDRFxData : public IKFxData {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x3c)
    DOTD_DECLARE_FACTORIES(CKHDRFxData)

    CKHDRFxData() {}  // inlined in 0x001be608 CKHDRFxData_Create: the vtables only

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001be3c0 CKHDRFxData_Load
    // vt+0x30 PostLoad 0x1be380 (stays the default in C2.1).
    int32_t Vf50() override { return 1; }                                  // vt+0x50 0x9ac380
    uint32_t GetAssociatedFxClassIdentifier() override { return 0xf8c; }  // vt+0x54 0x1be2f0

    IKSerializable* m_pHDRData;  // +0x08 (Ghidra draft: CHDRData*; LVL010 references class 0x54d)
    float m_unk0c;               // +0x0c
    float m_unk10;               // +0x10 not read
    int32_t m_unk14;             // +0x14 not read
};
static_assert(CKHDRFxData::kClassKey == 0xf0c, "key");
DOTD_ASSERT_SIZE(CKHDRFxData, 0x18);
DOTD_ASSERT_OFFSET(CKHDRFxData, m_pHDRData, 0x08);
DOTD_ASSERT_OFFSET(CKHDRFxData, m_unk0c, 0x0c);
