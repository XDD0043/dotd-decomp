// CNode.h - a scene-graph node with geometries (key 0xcb, vtable 0xb17f80, size 0x24). Original unit:
// CNode.cpp (0xcba58-0xccaa0). XXL2: K/KModules/KGL/SceneGraph/CNode.h, member m_lGeometryList, plus
// DotD's float at +0x20.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/scenegraph/CSGBranch.h"

class CNode : public CSGBranch {
public:
    DOTD_CLASS_KEY(kCategoryNode, 0x3)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9a2548
        return key == 0xcb || key == 0x24b || key == 0x20b || key == 0x14b || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CNode)

    CNode();  // 0x000cbe40 InitializeCNode (the constructor; also clears m_pParent, as XXL2's)
    ~CNode() override {}

    void Destroy() override;                            // vt+0x10 0x000cbe10: no geometry, then CSGBranch's
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x000cbd28 CNode_Load
    // vt+0x30 0x000cc340 CNode_PostLoad: CSGBranch's, then every geometry's atomic put on the node's frame
    // (RpAtomicSetFrame inlined: off its old frame's object list, onto this one's) and marked (flag 1).
    int32_t PostLoad(int32_t type) override;
    // vt+0x58 0x000cc160 EnqueueSceneNodeAndChildren (CSGSectorRoot's too; C2.4 step 5): unless hidden (flag 4), the
    // node's own geometries are culled and queued (vt+0x84, below), the node is stamped with the frame counter when
    // something was queued, then every child is traversed.
    void UpdateAndExtract(float maxDistanceSquared, RenderQueue** stages, IKTime* frameClock, RwCamera* camera,
                          int32_t distanceCull) override;
    // vt+0x84 0x000cc460 CullAndEnqueueNodeGeometry (declared non-virtual: the slots between +0x58 and
    // +0x84 are not ported; every caller so far is a CNode). Flags bits 4-5: 0 sphere / frustum test per
    // geometry, 1 the atomic's cached sphere, 2 every geometry without a frustum test, 3 none. Returns 1
    // when something was queued.
    uint32_t CullAndEnqueueGeometry(RenderQueue** stages, IKTime* frameClock, RwCamera* camera);
    // 0x000cc808 CNode_SetFlag10Bit5_ResetField20To1_maybe (not virtual): bit 5 of the properties set to `on` (the whole
    // value shifted in); when it changes to set, bits 21-22 are cleared and +0x20 becomes 1.0 (TOC -0x55cc).
    void SetFlag10Bit5ResetField20To1(uint32_t on);

    // +0x1c XXL2 GeometryList: the first CGeometry (they chain through the geometry's next pointer),
    // one reference. The constructor sets 0.
    IKSerializable* m_lGeometryList;
    // +0x20 DotD; name from the Ghidra struct (flDistanceLimitSquared). Not set by the constructor.
    float m_fDistanceLimitSquared;
};
static_assert(CNode::kClassKey == 0xcb, "key");
DOTD_ASSERT_SIZE(CNode, 0x24);
DOTD_ASSERT_OFFSET(CNode, m_lGeometryList, 0x1c);
DOTD_ASSERT_OFFSET(CNode, m_fDistanceLimitSquared, 0x20);

// 0x000cbfc0 TransformNodeBoundingSphereToWorld: a local bounding sphere (centre, radius) through the node
// frame's LTM into world space.
void TransformNodeBoundingSphereToWorld(float radius, CNode* node, float* worldCenter, float* worldRadius,
                                        const float* localCenter);
