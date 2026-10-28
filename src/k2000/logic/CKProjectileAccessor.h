// CKProjectileAccessor.h - the handle through which game objects launch projectiles (key 0x1e0c, vtable
// 0xb1e858, size 0xc). Original unit: CKProjectileAccessor.cpp (0x1f2868-0x1f32e0). Base: KBase1DCC (the
// accessor interface: vt+0x50/+0x54 get and set +0x04). No XXL2 class of this name.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/KBase1DCC.h"

class CKProjectileAccessor : public KBase1DCC {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x78)
    DOTD_DECLARE_FACTORIES(CKProjectileAccessor)

    // 0x001f2f10 CKProjectileAccessor_Construct: KBase1DCC, the vtable, +0x04 = null (+0x08 left as is).
    CKProjectileAccessor() { m_pProjectileType = nullptr; }
    ~CKProjectileAccessor() override {}
    // vt+0x08 0x9b07a0 (CKS08EnemyAttack_Load tests its reference with it)
    int32_t IsKindOfClass(uint32_t key) override { return key == 0x1e0c || key == 0x1dcc || key == 0xc; }
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001f3190 CKProjectileAccessor_Load
    IKSerializable* Vf50() override { return m_pProjectileType; }                       // vt+0x50 0x1f28b8
    void Vf54(IKSerializable* object) override { m_pProjectileType = object; }          // vt+0x54 0x1f28c0

    // +0x04 the projectile type (file: CKProjectileTypeScrap / CKProjectileTypeBallisticPFX references).
    IKSerializable* m_pProjectileType;
    // +0x08 the projectile data (file: CKProjectileDataTypeScrap / ...BallisticPFX references).
    IKSerializable* m_pProjectileData;
};
DOTD_ASSERT_SIZE(CKProjectileAccessor, 0xc);
DOTD_ASSERT_OFFSET(CKProjectileAccessor, m_pProjectileType, 0x04);
DOTD_ASSERT_OFFSET(CKProjectileAccessor, m_pProjectileData, 0x08);
