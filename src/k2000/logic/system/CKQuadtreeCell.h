// CKQuadtreeCell.h - a cell of a quadtree (key 0x5f8c, vtable 0xb14e28, size 0x5c). Original unit: CKQuadtreeCell.cpp
// (0x46ab8-0x478b0). Four references, the cell's rectangle, four child cells and three wide-string arrays loaded from
// the level file. No game file holds one (outputs/remake/kp3-class-usage.json); its agent methods (MoveAgent,
// AddAgent, RemoveAgent, MoveAllAgentsTo) are dead copies. Names ours.
//
// C2.8 port-all P07 wrote KQuadtreeRect (vtable 0xb14e80) for the cell's +0x0c member; its bodies are inline here and
// Vt_2.cpp's checklist (P10's file) is left as it was: ConstructBase 0x479a0 (the constructor), Destructor 0x478f0 /
// DeletingDestructor 0x478c0 (the destructor) and Load 0x47c18.
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"
#include "k2000/io/IKFile.h"
#include "k2000/util/TVector.h"

// vtable 0xb14e80, size 0x14: a rectangle (two words twice); its containment / quadrant tests are dead copies.
class KQuadtreeRect {
public:
    KQuadtreeRect() {}           // 0x000479a0 CKQuadtreeCell_ConstructBase_maybe: the vtable only
    virtual ~KQuadtreeRect() {}  // 0x000478f0 Vt_b14e80_Destructor_maybe (0x478c0 deleting): the vtable only
    // 0x00047c18 Vt_b14e80_Load_maybe (level data only): two 8-byte reads, each swapped word by word.
    int32_t Load(IKFile* file, int32_t type) {
        if (type != K_LEVEL_PLATEFORMS) return 1;
        ReadU32LEWords(file, m_unk04, 2);
        ReadU32LEWords(file, m_unk0c, 2);
        return 1;
    }

    uint32_t m_unk04[2];  // +0x04 (the minimum _maybe)
    uint32_t m_unk0c[2];  // +0x0c (the maximum _maybe)
};

class CKQuadtreeCell : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x17e)
    int32_t IsKindOfClass(uint32_t key) override { return key == 0x5f8c || key == 0xc; }  // vt+0x08 0x9958e0
    DOTD_DECLARE_FACTORIES(CKQuadtreeCell)

    CKQuadtreeCell();  // inlined in 0x00047538 CKQuadtreeCell_Create (and CreateArray 0x47420)
    // 0x000476d8 CKQuadtreeCell_Destructor (0x475e8 deleting): the arrays' blocks freed last to first, each length and
    // block cleared; then the rectangle's destructor.
    ~CKQuadtreeCell() override;
    // vt+0x10 0x00046ee8 CKQuadtreeCell_Destroy: the arrays' blocks freed first to last, each length and block cleared.
    void Destroy() override;
    // vt+0x24 0x00046ee0 CKQuadtreeCell_RecursiveRegistration: returns 1, registers nothing (the default).
    // vt+0x2c 0x000470a8 CKQuadtreeCell_Load (level data only).
    int32_t Load(IKFile* file, int32_t type) override;

    IKSerializable* m_unk04;          // +0x04 a reference (constructor: 0)
    IKSerializable* m_unk08;          // +0x08 a reference (constructor: 0)
    KQuadtreeRect m_rect;             // +0x0c
    IKSerializable* m_unk20;          // +0x20 a reference (not set by the constructor)
    IKSerializable* m_unk24;          // +0x24 a reference (not set by the constructor)
    IKSerializable* m_apChildren[4];  // +0x28 four references (one contiguous read; the child cells _maybe)
    TVector<uint16_t, 1> m_unk38;     // +0x38 UTF-16 units, each swapped
    TVector<uint16_t, 1> m_unk44;     // +0x44
    TVector<uint16_t, 1> m_unk50;     // +0x50
};
DOTD_ASSERT_SIZE(CKQuadtreeCell, 0x5c);
DOTD_ASSERT_OFFSET(CKQuadtreeCell, m_rect, 0x0c);
DOTD_ASSERT_OFFSET(CKQuadtreeCell, m_unk20, 0x20);
DOTD_ASSERT_OFFSET(CKQuadtreeCell, m_apChildren, 0x28);
DOTD_ASSERT_OFFSET(CKQuadtreeCell, m_unk38, 0x38);
DOTD_ASSERT_OFFSET(CKQuadtreeCell, m_unk50, 0x50);
