// CSGLeaf.h - a scene-graph leaf (key 0x20b, vtable 0xb181f8, size 0x18). Original unit: CSGLeaf.cpp
// (0xceb28-0xcf6e0). XXL2: K/KModules/KGL/SceneGraph/CSGLeaf.h, the same members in the same order
// (XXL2's m_pAdditionnalData and m_bNeverUpdated are not in the PS3 build; DotD uses the pad byte +0x15).
//
// A leaf hangs under its parent branch: the parent's child list is the first child, and the children
// chain through m_pNext (XXL2 CSBaseNode<CSGLeaf*>, kept here as a member at the same offset).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/scenegraph/CSGMovable.h"

class CSGBranch;
class IKTime;
class RenderQueue;
struct RwCamera;

class CSGLeaf : public CSGMovable {
public:
    DOTD_CLASS_KEY(kCategoryNode, 0x8)
    DOTD_DECLARE_FACTORIES(CSGLeaf)

    CSGLeaf();  // 0x000cefe0 CSGLeaf_Construct
    ~CSGLeaf() override {}

    // vt+0x10 0x000ceda8 CSGLeaf_Destroy: no parent, no parent bone (0xff), then CSGMovable's.
    void Destroy() override;
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x000cf550 CSGLeaf_Load
    // vt+0x30 0x000cf0f8 CSGLeaf_PostLoad: a node with a parent and no parent bone (0xff) puts its frame
    // under the parent's (RwFrameAddChild inlined, under the render lock).
    int32_t PostLoad(int32_t type) override;
    // vt+0x50 0x000cf300 CSGLeaf_ComputeLTM_maybe: when the node hangs under a bone (the bone parent is not
    // 0xff) or its frame's root is flagged (private flag 1, the hierarchy needs a sync), the LTM is made
    // current: copied from the modelling matrix without a parent, else through the parent's
    // ChildWorldMatrixUpdate.
    void ForceWorldMatrixUpdate() override;
    // vt+0x54 0x000cf1e0 CSGLeaf_ComputeLTMWithParent_maybe: `child`'s LTM = child's modelling matrix times
    // this node's LTM, after this node's own LTM was made current (the parent's update, or a copy).
    void ChildWorldMatrixUpdate(CSGMovable* child) override;
    // vt+0x58 0x000ceb80 CSGLeaf_Enqueue (XXL2 UpdateAndExtract): the render traversal. `stages` is the
    // renderer's stage array (CRenderer +0x38), `frameClock` the frame's clock, `camera` the camera the
    // root is drawn with. A leaf only marks itself drawn this frame (+0x16 = the frame counter) unless
    // hidden (flag 4).
    virtual void UpdateAndExtract(float maxDistanceSquared, RenderQueue** stages, IKTime* frameClock, RwCamera* camera,
                                  int32_t distanceCull);
    // Slots +0x5c..+0x68 (0xceba0, 0x991568, 0xcd580 (CSGBranch's), 0xcdd60) are not ported yet; they are
    // declared so that the slot after them is in place.
    virtual void Vf5C() {}  // vt+0x5c 0x000ceba0  STUB(C2.2)
    virtual void Vf60() {}  // vt+0x60 0x00991568  STUB(C2.2)
    virtual void Vf64() {}  // vt+0x64 0x000cd580  STUB(C2.2)
    virtual void Vf68() {}  // vt+0x68 0x000cdd60  STUB(C2.2)
    // vt+0x6c 0x000ceba8 CSGLeaf_GetSectorIndex_maybe (XXL2 CSGRootNode::GetSectorNumber): the parent's, or
    // 0xfffffffe without one. The roots answer for themselves (CSGRootNode 0, CSGSectorRoot its index).
    virtual uint32_t GetSectorIndex();

    // 0x000cec08 SceneNode_SetParent_maybe: the parent branch and the bone it hangs under (0xff without a
    // parent, whatever bone the caller passed).
    void SetParent(CSGBranch* parent, uint8_t bone) {
        m_pParent = parent;
        m_ui8BoneParent = parent != nullptr ? bone : static_cast<uint8_t>(0xff);
    }

    CSGLeaf* m_pNext;                  // +0x08 XXL2 CSBaseNode<CSGLeaf*>::m_pNext; the constructor sets 0
    CSGBranch* m_pParent;              // +0x0c
    uint32_t m_sgProperties;           // +0x10 XXL2 CBitArray (m_ui32Bits)
    uint8_t m_ui8BoneParent;           // +0x14 0xff = none (SceneNode_SetParent_maybe 0xcec08)
    uint8_t m_unk15;                   // +0x15 DotD (XXL2: padding); not set by the constructor or Load
    uint16_t m_ui16LastRenderedFrame;  // +0x16 Load sets 0; the enqueue code stores the frame counter
};
static_assert(CSGLeaf::kClassKey == 0x20b, "key");
DOTD_ASSERT_SIZE(CSGLeaf, 0x18);
DOTD_ASSERT_OFFSET(CSGLeaf, m_pNext, 0x08);
DOTD_ASSERT_OFFSET(CSGLeaf, m_pParent, 0x0c);
DOTD_ASSERT_OFFSET(CSGLeaf, m_sgProperties, 0x10);
DOTD_ASSERT_OFFSET(CSGLeaf, m_ui8BoneParent, 0x14);
DOTD_ASSERT_OFFSET(CSGLeaf, m_ui16LastRenderedFrame, 0x16);
