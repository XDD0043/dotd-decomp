// CKSpark.h - (key 0x25cc, vtable 0xb1d8b0, size 0x68): a serializable holding one reference; the rest of its 0x68 bytes
// is never written. Original unit: CKSpark.cpp (0x1d3568-0x1d3910). Not in XXL2; names ours.
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"

class CKSpark : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x97)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9ad2f0
        return key == 0x25cc || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKSpark)

    // 0x001d37b0 CKSpark_Create stores only the vtable; 0x001d3710 CreateArray also clears +0x04.
    CKSpark() : m_pRef(nullptr) {}
    ~CKSpark() override {}  // 0x001d38f0 / 0x001d38b0: the vtable stores only

    void Destroy() override {}                            // vt+0x10 0x001d3890 (empty)
    void RecursiveRegistration(int32_t /*type*/) override {}  // vt+0x24 0x001d3888 (nothing)
    int32_t Load(IKFile* file, int32_t type) override;    // vt+0x2c 0x001d37f8 CKSpark_Load

    IKSerializable* m_pRef;    // +0x04 a reference (level files)
    uint8_t m_unk08[0x60];     // +0x08 never written
};
static_assert(CKSpark::kClassKey == 0x25cc, "key");
DOTD_ASSERT_SIZE(CKSpark, 0x68);
DOTD_ASSERT_OFFSET(CKSpark, m_pRef, 0x04);
