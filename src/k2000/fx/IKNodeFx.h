// IKNodeFx.h - an effect on a scene node (key 0x148c, not registered; vtable 0xb1ddf8; Ghidra calls it
// CKNodeFx3d). Original unit: CKNodeFx3d.cpp (0x1d8898-0x1d8bf0). XXL2: K/KServices/KServiceFx/Effects/
// IKNodeFx.h, member m_pNode.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/fx/IKFx.h"

class CNode;

class IKNodeFx : public IKFx {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x52)

    IKNodeFx();  // 0x001d8898 CKNodeFx3d_ConstructBase
    ~IKNodeFx() override {}
    void Destroy() override { m_pNode = nullptr; }  // vt+0x10 0x001d88b0 CKNodeFx3d_ClearReferences: no node

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001d8940 CKNodeFx3d_Load
    int32_t PostLoad(int32_t type) override { return 1; }  // vt+0x30 0x001d8b48 IKNodeFx_PostLoad: returns 1
    // vt+0x24 0x001d88c0 CKNodeFx3d_RecursiveRegistration: the node (+0x10), when there is one, with the same type.
    void RecursiveRegistration(int32_t type) override;
    void Vf5C() override;  // vt+0x5c 0x001d8918 CKNodeFx3d_ShowSceneNode: the node's hidden bit cleared
    void Vf60() override;  // vt+0x60 0x001d8b18 CKNodeFx3d_HideSceneNode: the node's hidden bit set

    CNode* m_pNode;  // +0x10 the constructor sets 0
};
static_assert(IKNodeFx::kClassKey == 0x148c, "key");
DOTD_ASSERT_SIZE(IKNodeFx, 0x14);
DOTD_ASSERT_OFFSET(IKNodeFx, m_pNode, 0x10);
