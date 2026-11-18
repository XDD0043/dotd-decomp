// CKS08BonusCpnt.h - a bonus pickup's parameters (key 0x1306, size 0x64; IsKindOfClass 0x9ccb38 tests
// 0x1306, 0x606 IKBonusCpnt, 0x6, 0xc). Original unit: CKS08BonusCpnt.cpp (0x5b9f08-0x5ba9f8). No XXL2
// class of this name (XXL2's CKBonusCpnt has other members after the base).
#pragma once
#include <cstdint>

#include "k2000/components/IKBonusCpnt.h"
#include "k2000/core/Layout.h"

class CKS08BonusCpnt : public IKBonusCpnt {
public:
    DOTD_CLASS_KEY(kCategoryComponent, 0x4c)
    DOTD_DECLARE_FACTORIES(CKS08BonusCpnt)

    CKS08BonusCpnt() {}  // 0x005ba090 CKS08BonusCpnt_Create: the vtables only

    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9ccb38
        return key == 0x1306 || key == 0x606 || key == 0x6 || key == 0xc;
    }
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x005ba2f8 CKS08BonusCpnt_Load
    // vt+0x24 0x005ba210 CKS08BonusCpnt_LevelReset (port-all P22): outside the types 4..7 the component registered with
    // the saving manager and, for type 0, its sound dictionary's (+0x0c) registration with 0; then +0x48's with `type`.
    // vt+0x10 0x005b9f58 (Ghidra _ClearReferences / _Destroy): empty (IKBaseClass's).
    void RecursiveRegistration(int32_t type) override;

    // All words byte-swapped; the read order is +0x4c, +0x50, +0x14..+0x20, +0x2c..+0x44, +0x24, +0x28,
    // +0x54..+0x60, then the byte at +0x10.
    uint8_t m_unk10;     // +0x10 read last
    uint8_t m_pad11[3];
    float m_unk14[4];    // +0x14..+0x20
    float m_unk24;       // +0x24
    float m_unk28;       // +0x28
    uint32_t m_unk2c;    // +0x2c (LVL010: 3, 1) an integer
    float m_unk30[6];    // +0x30..+0x44
    IKSerializable* m_pUnk48;  // +0x48 reference (type 0 only)
    float m_unk4c;       // +0x4c
    float m_unk50;       // +0x50
    float m_unk54[4];    // +0x54..+0x60
};
DOTD_ASSERT_SIZE(CKS08BonusCpnt, 0x64);
DOTD_ASSERT_OFFSET(CKS08BonusCpnt, m_unk10, 0x10);
DOTD_ASSERT_OFFSET(CKS08BonusCpnt, m_unk14, 0x14);
DOTD_ASSERT_OFFSET(CKS08BonusCpnt, m_unk2c, 0x2c);
DOTD_ASSERT_OFFSET(CKS08BonusCpnt, m_unk30, 0x30);
DOTD_ASSERT_OFFSET(CKS08BonusCpnt, m_pUnk48, 0x48);
DOTD_ASSERT_OFFSET(CKS08BonusCpnt, m_unk54, 0x54);
