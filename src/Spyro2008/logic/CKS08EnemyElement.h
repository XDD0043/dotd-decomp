// CKS08EnemyElement.h - (key 0x7a0c, vtable 0xb21a80, size 0x64). Original unit: CKS08EnemyElement.cpp
// (0x26b348-0x26c918). No XXL2 class of this name. Its Load reads two scene-node references; the rest of
// the object is runtime state (never set by Create, which only stores the vtable).
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"

class CKS08EnemyElement : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x1e8)
    DOTD_DECLARE_FACTORIES(CKS08EnemyElement)

    CKS08EnemyElement() {}  // inlined in 0x0026b7d8 CKS08EnemyElement_Create: the vtable only
    ~CKS08EnemyElement() override {}
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0026c7b8 CKS08EnemyElement_Load

    uint32_t m_unk04[18];      // +0x04..+0x4b runtime
    IKSerializable* m_pNode;   // +0x4c a scene node (file: key 0xcb references; live: CNode)
    uint32_t m_unk50[3];       // +0x50..+0x5b runtime
    IKSerializable* m_pGlow;   // +0x5c _maybe a CGlowNodeFx (live), mostly null
    uint32_t m_unk60;          // +0x60 runtime
};
DOTD_ASSERT_SIZE(CKS08EnemyElement, 0x64);
DOTD_ASSERT_OFFSET(CKS08EnemyElement, m_pNode, 0x4c);
DOTD_ASSERT_OFFSET(CKS08EnemyElement, m_pGlow, 0x5c);
