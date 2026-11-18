// CKQuadtree.h - a quadtree (key 0x5fcc, vtable 0xb14d10, size 0x64). Original unit: CKQuadtree.cpp
// (0x44578-0x45500). Two agent references and four arrays loaded from the level file. No game file holds one
// (outputs/remake/kp3-class-usage.json); its other methods (RepositionAgent, UpdateRootBoundsIfDirty, ...) are dead
// copies. Names ours.
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"
#include "k2000/util/TVector.h"

class CKQuadtree : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x17f)
    int32_t IsKindOfClass(uint32_t key) override { return key == 0x5fcc || key == 0xc; }  // vt+0x08 0x995830
    DOTD_DECLARE_FACTORIES(CKQuadtree)

    // The 12-byte records of +0x20 (three words, byte-swapped by the Load) and of +0x38, the 6-byte ones of +0x2c.
    struct SWords3 {
        uint32_t m_words[3];
    };
    struct SHalves3 {
        uint16_t m_halves[3];
    };

    CKQuadtree();  // inlined in 0x00044c28 CKQuadtree_Create: the four arrays (null, 1, 0)
    // 0x00045340 CKQuadtree_Destructor (the deleting one 0x45248): the arrays' blocks freed last to first, each length
    // and block cleared.
    ~CKQuadtree() override;
    // vt+0x2c 0x00044ca8 CKQuadtree_Load (level data only): two references, a word, the four arrays (a count each),
    // three words and two bytes.
    int32_t Load(IKFile* file, int32_t type) override;
    // vt+0x10 0x00044818 CKQuadtree_Destroy: the arrays' blocks freed first to last, each length and block cleared.
    void Destroy() override;
    // vt+0x24 0x00044810 CKQuadtree_RecursiveRegistration: returns 1, registers nothing (the default).

    IKSerializable* m_unk04;         // +0x04 a reference (the root agent _maybe)
    IKSerializable* m_unk08;         // +0x08 a reference
    uint32_t m_unk0c[4];             // +0x0c..+0x1b (not loaded; not set by the constructor)
    uint32_t m_unk1c;                // +0x1c
    TVector<SWords3, 1> m_unk20;     // +0x20
    TVector<SHalves3, 1> m_unk2c;    // +0x2c
    TVector<SWords3, 1> m_unk38;     // +0x38
    TVector<uint32_t, 1> m_unk44;    // +0x44
    uint32_t m_unk50;                // +0x50
    uint32_t m_unk54;                // +0x54
    uint32_t m_unk58;                // +0x58
    uint32_t m_unk5c;                // +0x5c (not loaded)
    uint8_t m_unk60;                 // +0x60
    uint8_t m_unk61;                 // +0x61
    uint8_t m_pad62[2];
};
DOTD_ASSERT_SIZE(CKQuadtree, 0x64);
DOTD_ASSERT_OFFSET(CKQuadtree, m_unk1c, 0x1c);
DOTD_ASSERT_OFFSET(CKQuadtree, m_unk20, 0x20);
DOTD_ASSERT_OFFSET(CKQuadtree, m_unk2c, 0x2c);
DOTD_ASSERT_OFFSET(CKQuadtree, m_unk38, 0x38);
DOTD_ASSERT_OFFSET(CKQuadtree, m_unk44, 0x44);
DOTD_ASSERT_OFFSET(CKQuadtree, m_unk50, 0x50);
DOTD_ASSERT_OFFSET(CKQuadtree, m_unk60, 0x60);
