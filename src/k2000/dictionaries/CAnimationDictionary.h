// CAnimationDictionary.h - a table of animation indices (key 0x49, vtable 0xb131a8, size 0x18). Original
// unit: CAnimationDictionary.cpp. XXL2: K/KModules/KGL/Animation/CAnimationDictionary.h (m_apAnimations,
// m_ui32NbAnimations); DotD keeps indices (into the sector's animations, _maybe) in count x columns rows
// and two more fields.
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"

class CAnimationDictionary : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryDictionary, 0x1)
    DOTD_DECLARE_FACTORIES(CAnimationDictionary)

    // 0x0007a338 CAnimationDictionary_Create (the constructor inlined; also CAnimationDictionary_Construct)
    CAnimationDictionary() {
        m_apAnimations = nullptr;
        m_ui32NbColumns = 1;
        m_ui32NbAnimations = 1;
    }
    ~CAnimationDictionary() override {}

    // vt+0x2c 0x0007a438 CAnimationDictionary_Load. No type check.
    int32_t Load(IKFile* file, int32_t type) override;

    int32_t* m_apAnimations;      // +0x04 count x columns words (Mem_AllocAligned16); null when the count is 0
    uint32_t m_ui32NbAnimations;  // +0x08 the rows
    uint32_t m_ui32NbColumns;     // +0x0c (Ghidra dwColumns)
    uint32_t m_unk10;             // +0x10
    uint8_t m_unk14;              // +0x14
};
static_assert(CAnimationDictionary::kClassKey == 0x49, "key");
DOTD_ASSERT_SIZE(CAnimationDictionary, 0x18);
DOTD_ASSERT_OFFSET(CAnimationDictionary, m_apAnimations, 0x04);
DOTD_ASSERT_OFFSET(CAnimationDictionary, m_ui32NbAnimations, 0x08);
DOTD_ASSERT_OFFSET(CAnimationDictionary, m_ui32NbColumns, 0x0c);
DOTD_ASSERT_OFFSET(CAnimationDictionary, m_unk10, 0x10);
DOTD_ASSERT_OFFSET(CAnimationDictionary, m_unk14, 0x14);
