// CSpawnNode.h - a scene node spawned from a pool (key 0x8cb, vtable 0xb184e8, size 0x84). Original unit:
// CSpawnNode.cpp (0xd3888-...). XXL2: K/KModules/KGL/SceneGraph/CSpawnNode.h, bases CNode and ISpawnNode
// (no members of its own).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/ISpawnNode.h"
#include "k2000/scenegraph/CNode.h"

class CSpawnNode : public CNode, public ISpawnNode {
public:
    DOTD_CLASS_KEY(kCategoryNode, 0x23)
    DOTD_DECLARE_FACTORIES(CSpawnNode)

    CSpawnNode() {}  // 0x000d3cc8 CSpawnNode_Create: CNode's constructor only
    ~CSpawnNode() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x000d3b10 CSpawnNode_Load
    // vt+0x30 0x000d3aa8 CSpawnNode_PostLoad: CNode's, then SpawnNodeData_PostLoad_maybe 0xd5488 on the
    // ISpawnNode part.
    int32_t PostLoad(int32_t type) override;
};
static_assert(CSpawnNode::kClassKey == 0x8cb, "key");
DOTD_ASSERT_SIZE(CSpawnNode, 0x84);
