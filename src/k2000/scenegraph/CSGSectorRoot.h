// CSGSectorRoot.h - the root node of a sector (key 0x8b, vtable 0xb183c0, size 0x2c). Original unit:
// CSGSectorRoot.cpp (0xd2e28-0xd32b8). XXL2: K/KModules/KGL/SceneGraph/CSGSectorRoot.h, the same members
// in the same order.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/scenegraph/CNode.h"

class CSGSectorRoot : public CNode {
public:
    DOTD_CLASS_KEY(kCategoryNode, 0x2)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9a2a10
        return key == 0x8b || key == 0xcb || key == 0x24b || key == 0x20b || key == 0x14b || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CSGSectorRoot)

    CSGSectorRoot();  // inlined in 0x000d3180 CreateCSGSectorRoot
    ~CSGSectorRoot() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x000d2f30 CSGSectorRoot_Load
    uint32_t GetSectorIndex() override { return m_tSectorIndex; }  // vt+0x6c 0x000d2e78 CSGSectorRoot_GetSectorIndex_maybe

    IKSerializable* m_pTextureDictionary;  // +0x24 CTextureDictionary; the constructor sets 0
    uint32_t m_tSectorIndex;               // +0x28 XXL2 KSectorIndex; the constructor sets 0xfffffffe
};
static_assert(CSGSectorRoot::kClassKey == 0x8b, "key");
DOTD_ASSERT_SIZE(CSGSectorRoot, 0x2c);
DOTD_ASSERT_OFFSET(CSGSectorRoot, m_pTextureDictionary, 0x24);
DOTD_ASSERT_OFFSET(CSGSectorRoot, m_tSectorIndex, 0x28);
