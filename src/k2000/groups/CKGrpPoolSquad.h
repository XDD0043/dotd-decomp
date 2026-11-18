// CKGrpPoolSquad.h - a pool of squads (key 0xb04, vtable 0xb21890, size 0x3c). Original unit:
// CKGrpPoolSquad.cpp. The base of CKGrpS08PoolEnemy. No XXL2 class of this name.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/groups/IKBaseGroup.h"
#include "k2000/util/TVector.h"

class CKGrpPoolSquad : public IKGroup<IKHook> {
public:
    DOTD_CLASS_KEY(kCategoryGroup, 0x2c)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9bba30
        return key == 0xb04 || key == 0x17e || key == 0x4 || key == 0x2fe || key == 0x3fe || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKGrpPoolSquad)

    // 0x0026a790 CKGrpPoolSquad_Create (inlined constructor): the vector null, 5, 0.
    CKGrpPoolSquad() { m_vUnk30 = {nullptr, 5, 0}; }

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0026a940 CKGrpPoolSquad_Load
    // vt+0x24 0x0026abc8 CKGrpPoolSquad_RecursiveRegistration (CKGrpS08PoolEnemy_RecursiveRegistration 0x26ae08 calls it):
    // IKGroup_LevelReset 0x12a68, then for a level file (type 0) the pool registered with the saving manager and every
    // reference of +0x30 (type 0; not tested for null).
    void RecursiveRegistration(int32_t type) override;
    // vt+0x10 0x0026ace0 CKGrpPoolSquad_Destroy (CKGrpS08PoolEnemy_Destroy 0x26ae30 only calls it): no child groups (+0x18),
    // no members (vt+0xb0's head); the reference vector stays.
    void Destroy() override {
        m_lChilds = nullptr;
        *GetMemberListHead() = nullptr;
    }
    // vt+0x30 0x0026a638 CKGrpPoolSquad_PostLoad (CKGrpS08PoolEnemy_PostLoad 0x26adb8 calls it): IKLife_PostLoad 0x19f68, then 1.
    int32_t PostLoad(int32_t type) override {
        PostLoadLife(type);
        return 1;
    }

    uint8_t m_unk2c;                         // +0x2c read last
    uint8_t m_pad2d[3];
    TVector<IKSerializable*, 5> m_vUnk30;   // +0x30 references (LVL010: CKS08EnemyCpnt, key 0x906)
};
DOTD_ASSERT_SIZE(CKGrpPoolSquad, 0x3c);
DOTD_ASSERT_OFFSET(CKGrpPoolSquad, m_unk2c, 0x2c);
DOTD_ASSERT_OFFSET(CKGrpPoolSquad, m_vUnk30, 0x30);
