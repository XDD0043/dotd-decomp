// CKLocTextAccessor.h - gives an object its localised text: one text reference, or a list of them (key
// 0xe46, vtable 0xb14520, size 0x14). Original unit: CKLocTextAccessor.cpp (0x35e70-0x36500). No XXL2
// class of this name.
//
// Load: a count; with at most one text, the reference goes to +0x10, otherwise the count references go
// into the list at +0x04 (pushed one by one).
#pragma once
#include <cstdint>

#include "k2000/components/IKComponent.h"
#include "k2000/core/Layout.h"
#include "k2000/util/TVector.h"

class CKLocTextAccessor : public IKComponent {
public:
    DOTD_CLASS_KEY(kCategoryComponent, 0x39)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x994518
        return key == 0xe46 || key == 0x6 || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKLocTextAccessor)

    CKLocTextAccessor();  // 0x00036170 CKLocTextAccessor_Create (the constructor is inlined there)
    // 0x00036270 CKLocTextAccessor_Destructor (0x36210 deleting, 0x35f98 the same code): the list block freed, then the
    // component base (vtable only).
    ~CKLocTextAccessor() override;
    // vt+0x10 0x000361c0 CKLocTextAccessor_Destroy: the list block freed, its length and block cleared. (vt+0x24
    // 0x360a0 RecursiveRegistration: 1, the default.)
    void Destroy() override;

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x000362c8 CKLocTextAccessor_Load

    TVector<IKSerializable*, 10> m_texts;  // +0x04 the constructor: null, 10, 0 (grows by 10)
    IKSerializable* m_pText;               // +0x10 CKStdText (Ghidra draft); the constructor sets 0
};
DOTD_ASSERT_SIZE(CKLocTextAccessor, 0x14);
DOTD_ASSERT_OFFSET(CKLocTextAccessor, m_texts, 0x04);
DOTD_ASSERT_OFFSET(CKLocTextAccessor, m_pText, 0x10);
