// CScene2d.h - a list of 2D nodes drawn as one scene (key 0x50d, vtable 0xb15c80, size 0x28). Original
// unit: CScene2d.cpp (0x649d8-0x65e50). XXL2: K/KModules/KGL/2d/CScene2d.h (m_pRootNode, m_pLastNode,
// m_ui32NodeCount, m_bEnable, read in that order). XXL2 derives it from IKSerializable; DotD from
// IRendableObject (its Create stores the IRendableObject vtable 0xb17218 first, its Load calls
// IRendableObject_Load first).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/graphical/IRendableObject.h"

class IKNode2d;

class CScene2d : public IRendableObject {
public:
    DOTD_CLASS_KEY(kCategoryGraphical, 0x14)
    DOTD_DECLARE_FACTORIES(CScene2d)

    CScene2d();                    // 0x00065c98 CScene2d_Create (inlined; = CScene2d_Construct 0x64a28)
    ~CScene2d() override {}        // 0x00065dc8 / 0x00065e08 CScene2d_Destructor / _DeletingDestructor: the vtables only
    // vt+0x08 0x997cf8
    int32_t IsKindOfClass(uint32_t key) override { return key == 0x50d || key == 0xa8d || key == 0xc; }
    // vt+0x2c 0x00998010 CScene2d_Load: reads for every type (no type check).
    int32_t Load(IKFile* file, int32_t type) override;
    // vt+0x5c 0x00065608 DrawUISceneWidgetList (Ghidra CScene2d_Render): under pushed overlay render
    // states, every node's vt+0x84 when the scene is enabled.
    void Render(IKTime* frameClock) override;
    // 0x00064a98 CScene2d_BroadcastEvent_maybe: every node's vt+0x58 (RecursiveNodeReach) with the event.
    void BroadcastEvent(uint8_t event, void* data);
    // 0x000650d8 CContainer2d_RemoveChild_maybe: `node` out of this scene's list; the node, or null when it is
    // not in it.
    IKNode2d* RemoveChild(IKNode2d* node);
    // 0x000652b8 CScene2d_AddChild (+ thunk 0x65468): `node` appended; 1 when added.
    uint8_t AddChild(IKNode2d* node);
    // 0x00064b20 CContainer2d_GetFirstChild (Ghidra's name; it is CScene2d's): m_pRootNode.
    IKSerializable* GetFirstChild() const { return m_pRootNode; }
    // 0x00064b28 CContainer2d_GetLastChild: m_pLastNode.
    IKSerializable* GetLastChild() const { return m_pLastNode; }
    // 0x00064b30 CContainer2d_GetChildAt: the node at index along the m_pNext chain; null when index is not
    // below the node count or the chain ends first.
    IKSerializable* GetChildAt(uint32_t index) const;
    // vt+0x10 0x00065518 CScene2d_Destroy: IRendableObject's, then disabled and emptied (root, last, count).
    void Destroy() override;
    // 0x00064be0 CContainer2d_SwapChildWithPrev (Ghidra's name; CScene2d's): `node` (of this scene, with a previous
    // node) trades places with its previous node; 1 when it moved.
    uint8_t SwapChildWithPrev(IKNode2d* node);
    // 0x00064e70 CContainer2d_SwapChildWithNext: the same with the next node.
    uint8_t SwapChildWithNext(IKNode2d* node);
    // 0x00064dd0 CContainer2d_MoveChildToHead_maybe: SwapChildWithPrev until `node` is the last or the first node (or a
    // swap fails, 0). BUG(original): a last node does not move.
    uint8_t MoveChildToHead(IKNode2d* node);
    // 0x00065060 CContainer2d_MoveChildToTail_maybe: SwapChildWithNext until `node` is the last or the first node or a
    // swap fails; always 1. BUG(original): a first node does not move.
    uint8_t MoveChildToTail(IKNode2d* node);
    // 0x000656c8 CContainer2d_ShowChildren_maybe / 0x00065a28 CContainer2d_HideChildren_maybe: every unlocked node's
    // Enable / Disable (vt+0x64 / +0x68); 1.
    uint8_t ShowChildren();
    uint8_t HideChildren();
    // 0x00065c30 CContainer2d_RemoveChildAt: RemoveChild of the node at `index` (GetChildAt's walk).
    IKNode2d* RemoveChildAt(uint32_t index);

    IKSerializable* m_pRootNode;   // +0x18 IKNode2d (a reference)
    IKSerializable* m_pLastNode;   // +0x1c IKNode2d (a reference)
    uint32_t m_ui32NodeCount;      // +0x20
    uint8_t m_bEnable;             // +0x24
    uint8_t m_pad25[3];            // +0x25 never written
};
DOTD_ASSERT_SIZE(CScene2d, 0x28);
DOTD_ASSERT_OFFSET(CScene2d, m_pRootNode, 0x18);
DOTD_ASSERT_OFFSET(CScene2d, m_pLastNode, 0x1c);
DOTD_ASSERT_OFFSET(CScene2d, m_ui32NodeCount, 0x20);
DOTD_ASSERT_OFFSET(CScene2d, m_bEnable, 0x24);
