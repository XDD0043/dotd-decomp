// CSGBranch.h - a scene-graph branch (key 0x24b, vtable 0xb18118, size 0x1c). Original unit:
// CSGBranch.cpp (0xcd528-0xcdf20). XXL2: K/KModules/KGL/SceneGraph/CSGBranch.h, member m_lChildList.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/scenegraph/CSGLeaf.h"

class CSGBranch : public CSGLeaf {
public:
    DOTD_CLASS_KEY(kCategoryNode, 0x9)
    DOTD_DECLARE_FACTORIES(CSGBranch)

    CSGBranch();  // inlined in 0x000cdec0 CSGBranch_Create
    ~CSGBranch() override {}

    void Destroy() override;                            // vt+0x10 0x000cd870: no children, then CSGLeaf's
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x000cd6a0 CSGBranch_Load
    int32_t PostLoad(int32_t type) override;             // vt+0x30 0x000cd678 CSGBranch_PostLoad: CSGLeaf's
    // vt+0x58 0x000cdca8 EnqueueSceneRootChildren: unless hidden (flag 4), marked drawn and every child's
    // vt+0x58 with distance 0 and no distance cull.
    void UpdateAndExtract(float maxDistanceSquared, RenderQueue** stages, IKTime* frameClock, RwCamera* camera,
                          int32_t distanceCull) override;

    // vt+0x70 0x000cd808 CSGBranch_AddChild_maybe: the child at the head of the child list, its frame under
    // this one's (RwFrameAddChild), the child's parent this node with no bone (0xff).
    virtual void AddChild(CSGLeaf* child);
    // vt+0x74 0x000cd780 CSGBranch_AddChildKeepWorldTransform_maybe: AddChild (vt+0x70), then the child's local
    // matrix is rebuilt from its world one (this node's LTM inverted, SceneNode_SetLocalFromWorldTimes_maybe
    // 0xd0b90).
    virtual void AddChildKeepWorldTransform(CSGLeaf* child);
    // vt+0x78 0x000cdb30 CSGBranch_RemoveChild_maybe (CAnimatedNode overrides it): the child's frame leaves
    // this one's (RwFrameRemoveChild), the child leaves the child list, its parent is null (bone 0xff).
    virtual void RemoveChild(CSGLeaf* child);

    // +0x18 XXL2 ChildList (a TSNodeList: the first child; the others follow through CSGLeaf::m_pNext).
    // XXL2 reads it with EUL_TSNodeList_Read, one reference. The constructor sets 0.
    CSGLeaf* m_lChildList;
};
static_assert(CSGBranch::kClassKey == 0x24b, "key");
DOTD_ASSERT_SIZE(CSGBranch, 0x1c);
DOTD_ASSERT_OFFSET(CSGBranch, m_lChildList, 0x18);
