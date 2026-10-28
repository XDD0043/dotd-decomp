// CKNPCBehaviourBlockUser.h - (key 0x9ecc, vtable 0xb30058, size 0x8). Original unit:
// CKNPCBehaviourBlockUser.cpp. Base: KBase9CCC (CKNPCBehaviourBlockUserBase_maybe). No XXL2 class of this
// name. Its one member is an object reference read in level data.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/KBase9CCC.h"

class CKNPCBehaviourBlockUser : public KBase9CCC {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x27b)
    DOTD_DECLARE_FACTORIES(CKNPCBehaviourBlockUser)

    CKNPCBehaviourBlockUser() {}  // 0x005c9f58 CKNPCBehaviourBlockUser_Construct: the base, then the vtable
    ~CKNPCBehaviourBlockUser() override {}
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x005c9d40 CKNPCBehaviourBlockUser_Load

    IKSerializable* m_unk04;  // +0x04 (file: references of key 0x32c2)
};
DOTD_ASSERT_SIZE(CKNPCBehaviourBlockUser, 0x8);
DOTD_ASSERT_OFFSET(CKNPCBehaviourBlockUser, m_unk04, 0x04);
