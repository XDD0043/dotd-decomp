// CKBhvBlockAnimationMove.h - a behaviour block that plays an animation and moves its user's node to its hot spot at the
// end (DotD) (key 0x9d4c, vtable 0xb2fbd0, size 0xc). Original unit: CKBhvBlockAnimationMove.cpp (0x5c2868-0x5c3080).
// In no level file of the game (work/level-class-keys.json). Not in XXL2; names ours.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/KBase9C8C.h"

class IKFile;

class CKBhvBlockAnimationMove : public KBase9C8C {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x275)
    int32_t IsKindOfClass(uint32_t key) override { return key == 0x9d4c || key == 0xc || key == 0x9c8c; }
    DOTD_DECLARE_FACTORIES(CKBhvBlockAnimationMove)

    // 0x005c2e28 CKBhvBlockAnimationMove_Create (0x5c2b18 CKBhvBlockAnimationMove_Construct): the base, then the vtable.
    CKBhvBlockAnimationMove() {}
    ~CKBhvBlockAnimationMove() override {}

    // vt+0x2c 0x005c2f38 CKBhvBlockAnimationMove_Load: the base's, then (level files) the user and the dictionary.
    int32_t Load(IKFile* file, int32_t type) override;
    // vt+0x64 0x005c2948 CKBhvBlockAnimationMove_Start_maybe: the dictionary's first word plays from 0 on the user's
    // (+0x04, not the argument) animated node (vt+0x54).
    void Enter(IKSerializable* user) override;
    void Leave(IKSerializable* /*user*/) override {}  // vt+0x68 0x005c28b8 CKBhvBlockAnimationMove_vf68 (empty)
    // vt+0x6c 0x005c2bf8 CKBhvBlockAnimationMove_Update: the animation advances; at its end it is held on its last time,
    // the user's node is put at the user's hot spot (vt+0x60, its world position) and the user told (vt+0x64).
    void Update(IKTime* clock) override;
    // vt+0x10 0x005c2a10 Destroy / vt+0x24 0x005c29e8 RecursiveRegistration: the base's (KStub_Nop_5c57c0 / KBase9C8C_vf24,
    // return 1): the defaults.

    IKSerializable* m_pUser;        // +0x04 the user (a KBase9CCC, CKNPCBehaviourBlockUser _maybe)
    IKSerializable* m_pDictionary;  // +0x08 a CAnimationDictionary
};
static_assert(CKBhvBlockAnimationMove::kClassKey == 0x9d4c, "key");
DOTD_ASSERT_SIZE(CKBhvBlockAnimationMove, 0xc);
DOTD_ASSERT_OFFSET(CKBhvBlockAnimationMove, m_pUser, 0x04);
DOTD_ASSERT_OFFSET(CKBhvBlockAnimationMove, m_pDictionary, 0x08);
