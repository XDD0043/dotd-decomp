// CKSparkFxData.h - the data of a spark effect (key 0x24cc, vtable 0xb1d908, size 0x18). Original unit:
// k2000/fx/CKSparkFxData.cpp (0x1d3908-0x1d3e68); Create/CreateArray (0x1ae160/0x1ae0c0) sit in another
// unit. Its node is CKSparkNodeFx (0x244c). No XXL2 class of this name; names ours.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/IKFxData.h"

class CKSparkFxData : public IKFxData {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x93)
    DOTD_DECLARE_FACTORIES(CKSparkFxData)

    CKSparkFxData();  // 0x001d3908 CKSparkFxData_ConstructBase_maybe (called by Create 0x1ae160)

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001d39c8 CKSparkFxData_Load
    // vt+0x30 PostLoad 0x1d3940 (stays the default in C2.1): fills +0x14.
    uint32_t GetAssociatedFxClassIdentifier() override { return 0x244c; }  // vt+0x54 0x1d3930

    IKSerializable* m_pSparkParam;  // +0x08 the spark parameters (Ghidra draft: CKSparkParam*); name ours
    uint32_t m_unk0c;               // +0x0c the constructor sets 0
    uint32_t m_unk10;               // +0x10 the constructor sets 0
    void* m_unk14;                  // +0x14 the constructor sets 0; a heap pointer live (PostLoad)
};
static_assert(CKSparkFxData::kClassKey == 0x24cc, "key");
DOTD_ASSERT_SIZE(CKSparkFxData, 0x18);
DOTD_ASSERT_OFFSET(CKSparkFxData, m_pSparkParam, 0x08);
DOTD_ASSERT_OFFSET(CKSparkFxData, m_unk14, 0x14);
