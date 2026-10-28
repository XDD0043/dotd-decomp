// CKGrpS08WeaponPool.h - the pool of enemy weapons (key 0xb84, vtable 0xb21b40, size 0x54). Original unit:
// CKGrpS08WeaponPool.cpp. No XXL2 class of this name.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/groups/IKBaseGroup.h"

class CKGrpS08WeaponPool : public IKGroup<IKHook> {
public:
    DOTD_CLASS_KEY(kCategoryGroup, 0x2e)
    DOTD_DECLARE_FACTORIES(CKGrpS08WeaponPool)

    CKGrpS08WeaponPool() {}  // 0x0026d148 CKGrpS08WeaponPool_Create: the bases only

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0026d3a0 CKGrpS08WeaponPool_Load

    // Ten byte-swapped floats, read in the order +0x2c, +0x34, +0x38, +0x3c, +0x30, +0x50, +0x40..+0x4c
    // (LVL010: 1, 2pi, 9.81, 0.3, 2pi, 2pi, 0.87, 10, 100, 0.1).
    float m_unk2c;
    float m_unk30;
    float m_unk34;
    float m_unk38;
    float m_unk3c;
    float m_unk40;
    float m_unk44;
    float m_unk48;
    float m_unk4c;
    float m_unk50;
};
DOTD_ASSERT_SIZE(CKGrpS08WeaponPool, 0x54);
DOTD_ASSERT_OFFSET(CKGrpS08WeaponPool, m_unk2c, 0x2c);
DOTD_ASSERT_OFFSET(CKGrpS08WeaponPool, m_unk50, 0x50);
