// TAstar.h - the K engine's A* search and its red-black open list (XXL2: K/KUL/TAstar, TRBTree). The PS3 build
// inlines them: the grid search is the out-of-line copy 0x009ae3a8 TAstar_CPFGrid_FindPath (an [inline]
// of the LwMutex.cpp unit), the graph search is inlined in 0x001e71e0 CKSrvPathFinding_SearchPFGraph.
//
// The tree is the SGI-style red-black tree with a header node (XXL2 TRBTree::Insert / Remove / LRotate / RRotate,
// 0x1001ed0ac.. in the XXL2 executable; the PS3 inlined code was checked against them): equal keys go right, the
// header's left link is the leftmost (smallest F) node, its parent the root; the rightmost link is only set when the
// tree was empty (Insert never updates it, Remove does), as in the original.
#pragma once
#include <cstddef>
#include <cstdint>

#include "k2000/core/Layout.h"

class CKPFGraphNode;
class CPFGrid;

// XXL2 TRBTreeNode<T*> (colour 0 red, 1 black; the links point at whole tree-path nodes).
template <class T>
struct TRBTreeNode {
    uint32_t m_eColour;  // +0x00
    T* m_tLeft;          // +0x04
    T* m_tRight;         // +0x08
    T* m_tParent;        // +0x0c
};

// The open list of TAstar (XXL2 TAstar::CTreePath::CPriorityQueueType = TRBTree<CTreePath*, _node_compare>): the
// sentinel node, the tree-path node it stands for (the node's address less the node member's offset), the header
// node and its tree-path node. The links are untyped here (the graph and the grid searches use different nodes).
struct TAstarOpenList {
    TRBTreeNode<void> m_NodeSentinel;  // +0x00
    void* m_pTSentinel;                // +0x10
    TRBTreeNode<void> m_NodeHead;      // +0x14
    void* m_pTHead;                    // +0x24
};
DOTD_ASSERT_SIZE(TAstarOpenList, 0x28);

// XXL2 TAstar<...> (CAstarGraph / CAstarGrid), the members in XXL2's order.
struct TAstar {
    uint32_t m_ui32NumberOfZone;      // +0x00 the SearchList size (cells or graph nodes)
    uint16_t m_ui16ResearchZoneSize;  // +0x04 the most tree-path nodes a search may create
    uint16_t m_ui16MaxPathSize;       // +0x06
    float m_fMultGCoef;               // +0x08 the heuristic's factor
    void* NodeList;                   // +0x0c the tree-path nodes (index 0 unused)
    uint16_t m_ui16NodeListSize;      // +0x10
    uint16_t m_pad12;
    TAstarOpenList OpenList;          // +0x14
    uint16_t* SearchList;             // +0x3c per cell / graph node: its tree-path node index, 0 none
    uint16_t m_ui16PathSize;          // +0x40
    uint16_t m_pad42;

    // 0x009ae3a8 TAstar_CPFGrid_FindPath (XXL2 TAstar<..CPFGrid..>::FindPath): the 4-connected search from
    // `start` to `goal` (cells x, z) over `grid` (the palette values of open cells are the step costs; the heuristic
    // is m_fMultGCoef * (dx * dx + dz * dz)). The path, goal first, into `out` (m_ui16PathSize cells); returns its
    // length, 0 when there is no path or it is longer than m_ui16MaxPathSize, or minus the length of the path to the
    // node being expanded when the search ran out of nodes (m_ui16ResearchZoneSize).
    int16_t FindPathInGrid(const CPFGrid* grid, const uint8_t* start, const uint8_t* goal, uint8_t* out);
};
DOTD_ASSERT_SIZE(TAstar, 0x44);
DOTD_ASSERT_OFFSET(TAstar, OpenList, 0x14);
DOTD_ASSERT_OFFSET(TAstar, SearchList, 0x3c);
DOTD_ASSERT_OFFSET(TAstar, m_ui16PathSize, 0x40);

// XXL2 TAstar<TAstarCell<uchar>, TAstarCellIndex<uchar>, CPFGrid, ..>::CTreePath (0x24 bytes on the PS3).
struct CAstarGridPath {
    uint8_t m_x;                         // +0x00 TAstarCellIndex m_x
    uint8_t m_y;                         // +0x01 m_y
    uint8_t m_pad02[2];
    TRBTreeNode<CAstarGridPath> m_rb;    // +0x04
    uint16_t m_ui16parent;               // +0x14 the parent's node index; bit 15: in the open list
    uint16_t m_pad16;
    float m_fGCost;                      // +0x18
    float m_fFCost;                      // +0x1c
    CAstarGridPath* m_pOpenList;         // +0x20 the node itself once inserted
};
DOTD_ASSERT_SIZE(CAstarGridPath, 0x24);
DOTD_ASSERT_OFFSET(CAstarGridPath, m_rb, 0x04);
DOTD_ASSERT_OFFSET(CAstarGridPath, m_ui16parent, 0x14);
DOTD_ASSERT_OFFSET(CAstarGridPath, m_pOpenList, 0x20);

// XXL2 TAstar<CKPFGraphNode, CPFGraphNodeIndex, CPFGraph, ..>::CTreePath (0x28 bytes on the PS3).
struct CAstarGraphPath {
    CKPFGraphNode* m_pNode;              // +0x00 CPFGraphNodeIndex m_pNode
    uint16_t m_ui16Node;                 // +0x04 CPFGraphNodeIndex m_ui16Node
    uint16_t m_pad06;
    TRBTreeNode<CAstarGraphPath> m_rb;   // +0x08
    uint16_t m_ui16parent;               // +0x18
    uint16_t m_pad1a;
    float m_fGCost;                      // +0x1c
    float m_fFCost;                      // +0x20
    CAstarGraphPath* m_pOpenList;        // +0x24
};
DOTD_ASSERT_SIZE(CAstarGraphPath, 0x28);
DOTD_ASSERT_OFFSET(CAstarGraphPath, m_rb, 0x08);
DOTD_ASSERT_OFFSET(CAstarGraphPath, m_ui16parent, 0x18);
DOTD_ASSERT_OFFSET(CAstarGraphPath, m_pOpenList, 0x24);

// XXL2 CPFGraphNodeIndex as the graph search's route entries (8 bytes on the PS3).
struct CPFGraphNodeIndex {
    CKPFGraphNode* m_pNode;  // +0x00
    uint16_t m_ui16Node;     // +0x04
    uint16_t m_pad06;
};
DOTD_ASSERT_SIZE(CPFGraphNodeIndex, 0x8);

// The tree operations on an open list whose nodes are T (the node member m_rb, the key m_fFCost).
template <class T>
class TRBTree {
public:
    explicit TRBTree(TAstarOpenList& list) : m_list(list) {}

    // The search's tree-path node of the open list's sentinel / header (InitializeService sets them once).
    static void InitializeList(TAstarOpenList& list) {
        list.m_pTSentinel = reinterpret_cast<uint8_t*>(&list.m_NodeSentinel) - offsetof(T, m_rb);
        list.m_pTHead = reinterpret_cast<uint8_t*>(&list.m_NodeHead) - offsetof(T, m_rb);
    }

    T* Sentinel() const { return static_cast<T*>(m_list.m_pTSentinel); }
    T* Head() const { return static_cast<T*>(m_list.m_pTHead); }
    T* Root() const { return Head()->m_rb.m_tParent; }
    T* Leftmost() const { return Head()->m_rb.m_tLeft; }

    // The reset at the start of a search: the sentinel black with null links, the header red, its parent the
    // sentinel and its left / right links itself (the original's store order).
    void Reset() {
        Sentinel()->m_rb.m_tParent = nullptr;
        Sentinel()->m_rb.m_tRight = nullptr;
        Sentinel()->m_rb.m_tLeft = nullptr;
        Sentinel()->m_rb.m_eColour = 1;
        Head()->m_rb.m_tParent = Sentinel();
        Head()->m_rb.m_tRight = Head();
        Head()->m_rb.m_tLeft = Head();
        Head()->m_rb.m_eColour = 0;
    }

    // XXL2 TRBTree::Insert.
    void Insert(T* z) {
        T* const nil = Sentinel();
        T* const head = Head();
        z->m_rb.m_tLeft = nil;
        z->m_rb.m_tRight = nil;
        T* root = head->m_rb.m_tParent;
        if (root == nil) {
            head->m_rb.m_tParent = z;
            z->m_rb.m_tParent = head;
            head->m_rb.m_tLeft = z;
            head->m_rb.m_tRight = z;
        } else {
            T* y;
            T* x = root;
            do {
                y = x;
                x = y->m_fFCost > z->m_fFCost ? y->m_rb.m_tLeft : y->m_rb.m_tRight;
            } while (x != nil);
            z->m_rb.m_tParent = y;
            if (y->m_fFCost > z->m_fFCost) {
                y->m_rb.m_tLeft = z;
                if (y == head->m_rb.m_tLeft) head->m_rb.m_tLeft = z;
            } else {
                y->m_rb.m_tRight = z;
            }
        }
        z->m_rb.m_eColour = 0;
        // Rebalance.
        T* x = z;
        root = head->m_rb.m_tParent;
        if (x == root) {
            x->m_rb.m_eColour = 1;
            return;
        }
        for (;;) {
            T* const p = x->m_rb.m_tParent;
            if (p->m_rb.m_eColour != 0) break;
            T* const g = p->m_rb.m_tParent;
            T* next;
            if (p == g->m_rb.m_tLeft) {
                T* const uncle = g->m_rb.m_tRight;
                if (uncle->m_rb.m_eColour == 0) {
                    p->m_rb.m_eColour = 1;
                    uncle->m_rb.m_eColour = 1;
                    g->m_rb.m_eColour = 0;
                    next = g;
                } else {
                    T* px = p;
                    T* gx = g;
                    if (x == p->m_rb.m_tRight) {
                        LRotate(p);
                        x = p;
                        px = x->m_rb.m_tParent;
                        gx = px->m_rb.m_tParent;
                    }
                    px->m_rb.m_eColour = 1;
                    gx->m_rb.m_eColour = 0;
                    RRotate(gx);
                    next = x;
                }
            } else {
                T* const uncle = g->m_rb.m_tLeft;
                if (uncle->m_rb.m_eColour == 0) {
                    p->m_rb.m_eColour = 1;
                    uncle->m_rb.m_eColour = 1;
                    g->m_rb.m_eColour = 0;
                    next = g;
                } else {
                    T* px = p;
                    T* gx = g;
                    if (x == p->m_rb.m_tLeft) {
                        RRotate(p);
                        x = p;
                        px = x->m_rb.m_tParent;
                        gx = px->m_rb.m_tParent;
                    }
                    px->m_rb.m_eColour = 1;
                    gx->m_rb.m_eColour = 0;
                    LRotate(gx);
                    next = x;
                }
            }
            root = head->m_rb.m_tParent;
            x = next;
            if (x == root) break;
        }
        head->m_rb.m_tParent->m_rb.m_eColour = 1;
    }

    // XXL2 TRBTree::Remove (the leftmost / rightmost header links kept up to date).
    void Remove(T* z) {
        T* const nil = Sentinel();
        T* const head = Head();
        T* x;
        if (z->m_rb.m_tLeft == nil || z->m_rb.m_tRight == nil) {
            x = z->m_rb.m_tLeft == nil ? z->m_rb.m_tRight : z->m_rb.m_tLeft;
            x->m_rb.m_tParent = z->m_rb.m_tParent;
            if (head->m_rb.m_tParent == z) {
                head->m_rb.m_tParent = x;
            } else if (z->m_rb.m_tParent->m_rb.m_tLeft == z) {
                z->m_rb.m_tParent->m_rb.m_tLeft = x;
            } else {
                z->m_rb.m_tParent->m_rb.m_tRight = x;
            }
            if (head->m_rb.m_tLeft == z) {
                if (z->m_rb.m_tRight == nil) {
                    head->m_rb.m_tLeft = z->m_rb.m_tParent;
                } else {
                    T* m = x;
                    while (m->m_rb.m_tLeft != nil) m = m->m_rb.m_tLeft;
                    head->m_rb.m_tLeft = m;
                }
            }
            if (head->m_rb.m_tRight == z) {
                if (z->m_rb.m_tLeft == nil) {
                    head->m_rb.m_tRight = z->m_rb.m_tParent;
                } else {
                    T* m = x;
                    while (m->m_rb.m_tRight != nil) m = m->m_rb.m_tRight;
                    head->m_rb.m_tRight = m;
                }
            }
        } else {
            T* y = z->m_rb.m_tRight;
            while (y->m_rb.m_tLeft != nil) y = y->m_rb.m_tLeft;
            x = y->m_rb.m_tRight;
            z->m_rb.m_tLeft->m_rb.m_tParent = y;
            y->m_rb.m_tLeft = z->m_rb.m_tLeft;
            if (y != z->m_rb.m_tRight) {
                x->m_rb.m_tParent = y->m_rb.m_tParent;
                y->m_rb.m_tParent->m_rb.m_tLeft = x;
                y->m_rb.m_tRight = z->m_rb.m_tRight;
                z->m_rb.m_tRight->m_rb.m_tParent = y;
            } else {
                x->m_rb.m_tParent = y;
            }
            if (head->m_rb.m_tParent == z) {
                head->m_rb.m_tParent = y;
            } else if (z->m_rb.m_tParent->m_rb.m_tLeft == z) {
                z->m_rb.m_tParent->m_rb.m_tLeft = y;
            } else {
                z->m_rb.m_tParent->m_rb.m_tRight = y;
            }
            y->m_rb.m_tParent = z->m_rb.m_tParent;
            const uint32_t colour = y->m_rb.m_eColour;
            y->m_rb.m_eColour = z->m_rb.m_eColour;
            z->m_rb.m_eColour = colour;
        }
        if (z->m_rb.m_eColour != 1) return;
        // Rebalance (z was black).
        while (x != head->m_rb.m_tParent && x->m_rb.m_eColour == 1) {
            T* p = x->m_rb.m_tParent;
            if (x == p->m_rb.m_tLeft) {
                T* w = p->m_rb.m_tRight;
                if (w->m_rb.m_eColour == 0) {
                    w->m_rb.m_eColour = 1;
                    p->m_rb.m_eColour = 0;
                    LRotate(p);
                    p = x->m_rb.m_tParent;
                    w = p->m_rb.m_tRight;
                }
                if (w->m_rb.m_tLeft->m_rb.m_eColour == 1 && w->m_rb.m_tRight->m_rb.m_eColour == 1) {
                    w->m_rb.m_eColour = 0;
                    x = p;
                    continue;
                }
                if (w->m_rb.m_tRight->m_rb.m_eColour == 1) {
                    w->m_rb.m_tLeft->m_rb.m_eColour = 1;
                    w->m_rb.m_eColour = 0;
                    RRotate(w);
                    p = x->m_rb.m_tParent;
                    w = p->m_rb.m_tRight;
                }
                w->m_rb.m_eColour = p->m_rb.m_eColour;
                p->m_rb.m_eColour = 1;
                w->m_rb.m_tRight->m_rb.m_eColour = 1;
                LRotate(p);
                break;
            }
            T* w = p->m_rb.m_tLeft;
            if (w->m_rb.m_eColour == 0) {
                w->m_rb.m_eColour = 1;
                p->m_rb.m_eColour = 0;
                RRotate(p);
                p = x->m_rb.m_tParent;
                w = p->m_rb.m_tLeft;
            }
            if (w->m_rb.m_tRight->m_rb.m_eColour == 1 && w->m_rb.m_tLeft->m_rb.m_eColour == 1) {
                w->m_rb.m_eColour = 0;
                x = p;
                continue;
            }
            if (w->m_rb.m_tLeft->m_rb.m_eColour == 1) {
                w->m_rb.m_tRight->m_rb.m_eColour = 1;
                w->m_rb.m_eColour = 0;
                LRotate(w);
                p = x->m_rb.m_tParent;
                w = p->m_rb.m_tLeft;
            }
            w->m_rb.m_eColour = p->m_rb.m_eColour;
            p->m_rb.m_eColour = 1;
            w->m_rb.m_tLeft->m_rb.m_eColour = 1;
            RRotate(p);
            break;
        }
        x->m_rb.m_eColour = 1;
    }

private:
    // XXL2 TRBTree::LRotate.
    void LRotate(T* x) {
        T* const y = x->m_rb.m_tRight;
        x->m_rb.m_tRight = y->m_rb.m_tLeft;
        if (y->m_rb.m_tLeft != Sentinel()) y->m_rb.m_tLeft->m_rb.m_tParent = x;
        y->m_rb.m_tParent = x->m_rb.m_tParent;
        T* const head = Head();
        if (head->m_rb.m_tParent == x) {
            head->m_rb.m_tParent = y;
        } else if (x->m_rb.m_tParent->m_rb.m_tLeft == x) {
            x->m_rb.m_tParent->m_rb.m_tLeft = y;
        } else {
            x->m_rb.m_tParent->m_rb.m_tRight = y;
        }
        y->m_rb.m_tLeft = x;
        x->m_rb.m_tParent = y;
    }
    // XXL2 TRBTree::RRotate.
    void RRotate(T* x) {
        T* const y = x->m_rb.m_tLeft;
        x->m_rb.m_tLeft = y->m_rb.m_tRight;
        if (y->m_rb.m_tRight != Sentinel()) y->m_rb.m_tRight->m_rb.m_tParent = x;
        y->m_rb.m_tParent = x->m_rb.m_tParent;
        T* const head = Head();
        if (head->m_rb.m_tParent == x) {
            head->m_rb.m_tParent = y;
        } else if (x->m_rb.m_tParent->m_rb.m_tRight == x) {
            x->m_rb.m_tParent->m_rb.m_tRight = y;
        } else {
            x->m_rb.m_tParent->m_rb.m_tLeft = y;
        }
        y->m_rb.m_tRight = x;
        x->m_rb.m_tParent = y;
    }

    TAstarOpenList& m_list;
};
