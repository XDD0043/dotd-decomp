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
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9a27a0
        return key == 0x20b || key == 0x14b || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CSGLeaf)

    CSGLeaf();  // 0x000cefe0 CSGLeaf_Construct
    ~CSGLeaf() override {}

    // vt+0x10 0x000ceda8 CSGLeaf_Destroy: no parent, no parent bone (0xff), then CSGMovable's.
    void Destroy() override;
    // vt+0x24 0x000ceb78 CSGLeaf_RecursiveRegistration: returns 1, registers nothing (CSGMovable's registration not
    // inherited). The shapes' (CKAABB 0xd6598, CKAACylinder 0xd68c0, CKBoundingSphere 0xd7138, CKOBB 0xd8050,
    // CKDynamicBoundingSphere 0xd74e8) and the branches' (CSGBranch 0xcd578, CNode 0xcbaa8 and the nodes on top)
    // call this one down the chain: nothing either.
    void RecursiveRegistration(int32_t /*type*/) override {}
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
    // vt+0x5c 0x000ceba0 KStub_Return0_ceba0 (XXL2 CSGLeaf::GetKlusterListHead, one slot later there: XXL2 has
    // GetModelName at +0x54): no kluster list. Every scene-graph vtable of the PS3 build keeps this stub.
    virtual void* GetKlusterListHead() { return nullptr; }
    // vt+0x60 0x00991568 CSGLeaf_vf60 [inline] (XXL2 CSGLeaf::SetAutoUpdatable(bool)): bit 0 of the properties
    // replaced by the argument, ORed in as the whole register (the callers pass 0 or 1). CAnimatedNode's
    // (0xc8bd0) is empty.
    virtual void SetAutoUpdatable(uint32_t autoUpdatable) {
        m_sgProperties = (m_sgProperties & 0xfffffffeu) | autoUpdatable;
    }
    // vt+0x64 0x00991580 KStub_Return0_991580 [inline] (XXL2 CSGLeaf::GetHotSpots(CSGLeaf**, unsigned)): a leaf has
    // no hot spots. The branches (CSGBranch 0xcd580, CAnimatedNode 0xc9e90) store their children with the hot-spot
    // flag (bit 3) into `out`, at most `max`, and return how many.
    virtual uint32_t GetHotSpots(CSGLeaf** /*out*/, uint32_t /*max*/) { return 0; }
    // vt+0x68 0x000cef68 CSGLeaf_UpdateWorldMatrices (the same code as SceneNode_UpdateWorldMatrix 0xcede0): this
    // node's LTM recomputed when `force`, its frame's root carries the hierarchy sync mark (privateFlags bit 0) or the
    // frame its own (bit 2): from its modelling matrix alone without a parent; times the parent's LTM when it hangs
    // under no bone or the parent was never drawn (+0x16 0); else times the bone's matrix and the parent's LTM. Both
    // marks are cleared. 1 when the LTM was recomputed. (CSGBranch 0xcdd60 and CAnimatedNode 0xc9ab0 then update
    // their children with that answer, the animated node's bone attachments always.)
    virtual uint8_t UpdateWorldMatrices(int32_t force) { return UpdateWorldMatrix(force); }
    // 0x000cede0 SceneNode_UpdateWorldMatrix
    uint8_t UpdateWorldMatrix(int32_t force);
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
