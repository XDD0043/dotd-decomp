// CKBsptreeNode.h - a node of a BSP tree (key 0x76cc, vtable 0xb14ca8, size 0x4c). Original unit: CKBsptreeNode.cpp
// (0x43948-0x443d8); its embedded part's functions (vtable 0xb14d00) sit in k2000/misc/Vt.cpp (0x443d8-0x44578).
// Derived straight from IKSerializable. No XXL2 class of this name; no level of DotD holds one (level-class-keys.json).
// The members keep placeholder names.
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"
#include "k2000/util/TVector.h"

class CKBsptreeNode : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x1db)
    int32_t IsKindOfClass(uint32_t key) override { return key == 0x76cc || key == 0xc; }  // vt+0x08 0x995800
    DOTD_DECLARE_FACTORIES(CKBsptreeNode)

    // The embedded part at +0x04 (vtable 0xb14d00, 0x14 bytes; its slots are its destructors and Load only, so it is a
    // plain member here). 0x00044430 CKBsptreeNode_ConstructBase_maybe: +0x10 = 8, +0x0c = 0. 0x000443e0
    // Vt_b14d00_Destructor_maybe / 0x00044400 DeletingDestructor: the vtable only.
    struct Part {
        uint32_t m_unk00;     // +0x00 the original's vtable word (0xb14d00); not used here
        uint32_t m_unk04[2];  // +0x04 one 8-byte read, swapped word by word
        uint32_t m_unk0c;     // +0x0c
        uint8_t m_unk10;      // +0x10
        uint8_t m_pad11[3];
        // 0x00044450 Vt_b14d00_Load_maybe: for type 0 two words, a word and a byte.
        void Load(IKFile* file, int32_t type);
    };

    // 0x00044060 CKBsptreeNode_Create / 0x00043f58 CreateArray: the part's constructor, then the three arrays empty with
    // a capacity of 1.
    CKBsptreeNode();
    // 0x000441e8 CKBsptreeNode_Destructor / 0x000440f8 DeletingDestructor: the arrays' blocks freed (the last first),
    // their lengths and blocks cleared, then the part's destructor.
    ~CKBsptreeNode() override;
    // vt+0x10 0x00043bd0 CKBsptreeNode_Destroy: the arrays' blocks freed (the first first), their blocks and lengths
    // cleared. (vt+0x24 0x00043bc8 RecursiveRegistration returns 1.)
    void Destroy() override;
    // vt+0x2c 0x00043c90 CKBsptreeNode_Load: for type 0 the part, two references, a pair of references and the three
    // arrays of half-words (a count, then the elements; an array grows to count + 1 when its capacity is below count).
    int32_t Load(IKFile* file, int32_t type) override;

    Part m_part;                       // +0x04
    IKSerializable* m_unk18;           // +0x18 a reference
    IKSerializable* m_unk1c;           // +0x1c a reference
    IKSerializable* m_unk20[2];        // +0x20 two references (one array read)
    TVector<uint16_t, 1> m_aUnk28[3];  // +0x28 / +0x34 / +0x40
};
DOTD_ASSERT_SIZE(CKBsptreeNode, 0x4c);
DOTD_ASSERT_OFFSET(CKBsptreeNode, m_part, 0x04);
DOTD_ASSERT_OFFSET(CKBsptreeNode, m_unk18, 0x18);
DOTD_ASSERT_OFFSET(CKBsptreeNode, m_aUnk28, 0x28);
