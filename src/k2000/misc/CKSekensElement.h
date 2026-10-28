// CKSekensElement.h - the unregistered base of the sekens (sequence) elements (key 0x658c, vtable
// 0xb1ec50, size 0x10): CKSekensBlock and CKSekensMarker. Original unit: CKSekensElement.cpp
// (0x1fa758-0x1fa938; Ghidra calls the Load CKSekensEntry_Load). No XXL2 counterpart (XXL2's sekens
// keeps plain SSekensBlock records); the names are ours.
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"

class CKSekensElement : public IKSerializable {
public:
    CKSekensElement();  // 0x001fa758 CKSekensElement_658c_maybe_Construct
    ~CKSekensElement() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001fa788 CKSekensEntry_Load
    int32_t IsKindOfClass(uint32_t key) override { return key == 0x658c || key == 0xc; }  // 0x9b10d0
    // The line slots (vt+0x50..+0x5c; names ours): Vf50 is pure here (CKSekensBlock 0x1f7068 returns its byte +0x18,
    // CKSekensMarker 0x9b0f10 returns 1); Vf54 is empty; Vf58 (block: its byte +0x19; marker: 0) says whether the line
    // takes part in the sekens' line choice; Vf5C (block: its text +0x10; marker: null).
    virtual uint8_t Vf50() = 0;
    virtual void Vf54() {}
    virtual uint8_t Vf58() { return 0; }
    virtual IKSerializable* Vf5C() { return nullptr; }

    float m_fTime;              // +0x04 a time in seconds _maybe (0.15, 2.04 in the samples)
    uint8_t m_unk08;            // +0x08 the constructor sets 0
    uint8_t m_pad09[3];
    IKSerializable* m_pSekens;  // +0x0c the owning CKSekens (in the files); the constructor sets null
};
DOTD_ASSERT_SIZE(CKSekensElement, 0x10);
DOTD_ASSERT_OFFSET(CKSekensElement, m_fTime, 0x04);
DOTD_ASSERT_OFFSET(CKSekensElement, m_unk08, 0x08);
DOTD_ASSERT_OFFSET(CKSekensElement, m_pSekens, 0x0c);
