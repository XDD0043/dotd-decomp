// CKQuadTreeLeaf.h - a leaf of the navigation quadtree (key 0x190c, vtable 0xb1e798, size 0x8). Original
// unit: CKQuadTreeLeaf.cpp (0x1f1a58-0x1f20d0). No XXL2 class; the names are ours.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/physics/CKQuadTreeBranch.h"

class CKQuadTreeLeaf : public KBase16CC {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x64)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9b0730
        return key == 0x190c || key == 0x16cc || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKQuadTreeLeaf)

    // A node of the leaf's list (8 bytes, from the FreeListPool at TOC -0x14bc in the original; here a
    // plain allocation).
    struct LeafNode {
        uint16_t m_ui16Value;  // +0x00 the u16 the file holds (an index, _maybe a ground or triangle id)
        LeafNode* m_pNext;     // +0x04
    };

    CKQuadTreeLeaf() : m_pList(nullptr) {}  // 0x001f1d98 CKQuadTreeLeaf_Create (inlined constructor)
    // 0x001f1f88 CKQuadTreeLeaf_Destructor: the list given back (Destroy's loop), then the base vtables.
    ~CKQuadTreeLeaf() override { FreeList(); }
    // vt+0x10 0x001f1f48 CKQuadTreeLeaf_Destroy: every node given back to the pool, the list cleared.
    void Destroy() override { FreeList(); }
    // vt+0x24 0x001f1f40 CKQuadTreeLeaf_RecursiveRegistration: returns 1, registers nothing (IKSerializable's).

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001f1de0 CKQuadTreeLeaf_Load
    // vt+0x50 0x001f1c00 CKQuadTreeLeaf_FindLeaf: the first listed node whose box holds the cell's centre
    // (x * cell + 0.001, z * cell + 0.001) and y; its index, or -1.
    int16_t FindLeaf(int32_t x, int32_t z, float y, IKSerializable** const* graphNodes) override;

    // +0x04 the nodes, the last read first (each read node is pushed at the head).
    LeafNode* m_pList;

private:
    // The nodes pushed back onto the FreeListPool (TOC -0x14bc) in list order; here deleted.
    void FreeList() {
        LeafNode* node = m_pList;
        while (node != nullptr) {
            LeafNode* next = node->m_pNext;
            delete node;
            node = next;
        }
        m_pList = nullptr;
    }
};
static_assert(CKQuadTreeLeaf::kClassKey == 0x190c, "key");
DOTD_ASSERT_SIZE(CKQuadTreeLeaf, 0x8);
DOTD_ASSERT_OFFSET(CKQuadTreeLeaf, m_pList, 0x04);
