// CKNPCBehaviourBlockUser.h - (key 0x9ecc, vtable 0xb30058, size 0x8). Original unit:
// CKNPCBehaviourBlockUser.cpp. Base: KBase9CCC (CKNPCBehaviourBlockUserBase_maybe). No XXL2 class of this
// name. Its one member is an object reference read in level data: the scripted NPC (CKHkScriptedNPC) its blocks
// run for.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/KBase9CCC.h"

class CKNPCBehaviourBlockUser : public KBase9CCC {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x27b)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9cd5c8
        return key == 0x9ecc || key == 0xc || key == 0x9ccc;
    }
    DOTD_DECLARE_FACTORIES(CKNPCBehaviourBlockUser)

    CKNPCBehaviourBlockUser() {}  // 0x005c9f58 CKNPCBehaviourBlockUser_Construct: the base, then the vtable
    ~CKNPCBehaviourBlockUser() override {}
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x005c9d40 CKNPCBehaviourBlockUser_Load

    IKSerializable* GetOwner() override { return m_unk04; }  // vt+0x50 0x005c9c10 CKNPCBehaviourBlockUser_vf50
    IKSerializable* GetAnimatedNode() override;              // vt+0x54 0x005c9c18 CKNPCBehaviourBlockUser_vf54
    IKSerializable* GetMovable() override;                   // vt+0x58 0x005ca030 CKNPCBehaviourBlockUser_vf58
    void SetStream(IKSerializable* stream) override;         // vt+0x5c 0x005c9c28 CKNPCBehaviourBlockUser_vf5C
    IKSerializable* GetHotSpot() override;                   // vt+0x60 0x005c9c70 CKNPCBehaviourBlockUser_vf60
    void OnBlockDone(KBase9C8C* block) override;             // vt+0x64 0x005c9d08 CKNPCBehaviourBlockUser_vf64

    IKSerializable* m_unk04;  // +0x04 (file: references of key 0x32c2): the CKHkScriptedNPC
};
DOTD_ASSERT_SIZE(CKNPCBehaviourBlockUser, 0x8);
DOTD_ASSERT_OFFSET(CKNPCBehaviourBlockUser, m_unk04, 0x04);
