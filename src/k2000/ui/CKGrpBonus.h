// CKGrpBonus.h - the group of the bonus pools (key 0x1704, size 0x2c; XXL2 CKGrpBonus: IKGroup<IKHkBonus>,
// no members). Original unit: CKGrpBonus.cpp (0x5b0ce0-0x5b1348, TOC2). The Load is GroupBasicLoad.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/groups/IKBaseGroup.h"
#include "k2000/math/CMatrix34.h"

class CKGrpBonus : public IKGroup<IKHook> {
public:
    DOTD_CLASS_KEY(kCategoryGroup, 0x5c)
    DOTD_DECLARE_FACTORIES(CKGrpBonus)

    CKGrpBonus() {}  // 0x005b0d80 CKGrpBonus_Create: the bases only

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x005b1298 CKGrpBonus_Load
    // vt+0x30 0x005b0c30 CKGrpBonus_PostLoad: IKLife_PostLoad 0x19f68, then 1.
    int32_t PostLoad(int32_t type) override {
        PostLoadLife(type);
        return 1;
    }
    // vt+0x50 0x005b0bc8 CKGrpBonus_ResetRuntime: every pool (the child groups) builds its free list (vt+0xec ResetPool;
    // the CKGrpS08BonusPool vtable's slot is 0x5b1f10, not a getter).
    void Start() override;
    // vt+0x54 0x005b0e90 CKGrpBonus_ReinitRuntime: every pool (the child groups) releases its active bonuses (vt+0xf8).
    void Restart() override;
    // vt+0x68 0x005b0f70 CKGrpBonus_OnLevelExit_maybe: every pool's vt+0xf0 (its active bonuses released).
    void Stop() override;
    // vt+0x7c 0x005b0ef8 UpdateCKGrpBonus: every pool's UpdateBonuses (vt+0xf4).
    void Update(IKTime* frameClock) override;
    // 0x005b0df8 BonusPool_SpawnBonusObject: a bonus of the first pool of type `kind` without bit 8 (vt+0xfc); null
    // without one.
    IKSerializable* SpawnBonusObject(uint32_t kind, const CVector3* position, uint8_t playSound);

    // vt+0x1c 0x005b10b0 CKGrpBonus_vf1C (MessageProc): 0xe00 sets bit 7 of every pool's (child group's) bit array,
    // 0xe01 clears it; both answer 0, anything else 1.
    int32_t MessageProc(uint16_t message, void* data) override;
    // vt+0x10 0x005b12e8 CKGrpBonus_Destroy: no child groups (+0x18), no members (vt+0xb0's head).
    void Destroy() override {
        m_lChilds = nullptr;
        *GetMemberListHead() = nullptr;
    }
    // vt+0x24 0x005b1210 CKGrpBonus_RecursiveRegistration: IKGroup's (IKGroup_LevelReset 0x12a68), then registered with
    // the saving manager (vt+0x24) unless a save restore (types 4..7), then 1.
    void RecursiveRegistration(int32_t type) override;
    // vt+0xb8 0x005b0b28 CKGrpBonus_vfB8 returns 1: IKBaseGroup models no slot there and no ported code calls it
    // (port-all P22; its line is in CKGrpS08BonusPool.cpp).
    // vt+0x40 0x005b0fd8 CKGrpBonus_vf40 (GetInfo) returns 1: the default.
};
DOTD_ASSERT_SIZE(CKGrpBonus, 0x2c);
