// CKProjectileDataTypeFromExplosion.h - the data of a projectile type launched from an explosion (key 0xa68c, vtable
// 0xb2e5f0, size 0x8c): CKProjectileDataTypeBallisticPFX plus a reference and five words. Original unit:
// CKProjectileDataTypeFromExplosion.cpp (0x599ea8-0x59a370). Its runtime CKProjectileTypeFromExplosion is not ported
// (the fields stay unnamed). Not in XXL2.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/CKProjectileDataTypeBallisticPFX.h"

class CKProjectileDataTypeFromExplosion : public CKProjectileDataTypeBallisticPFX {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x29a)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9cb810
        return key == 0xa68c || key == 0xa5cc || key == 0xa58c || key == 0x6 || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKProjectileDataTypeFromExplosion)

    // Inlined in 0x0059a050 Create / 0x0059a098 CreateArray: the vtables only.
    CKProjectileDataTypeFromExplosion() {}
    ~CKProjectileDataTypeFromExplosion() override {}

    // vt+0x10 0x00599f88 CKProjectileDataTypeFromExplosion_Destroy: the base's (0x585xxx, CKProjectileDataTypeBallisticPFX).
    void Destroy() override { CKProjectileDataTypeBallisticPFX::Destroy(); }
    int32_t Load(IKFile* file, int32_t type) override;          // vt+0x2c 0x0059a140
    int32_t PostLoad(int32_t /*type*/) override { return 1; }  // vt+0x30 0x0059a138

    IKSerializable* m_unk74;  // +0x74 a reference (level files)
    float m_unk78;            // +0x78
    float m_unk7c;            // +0x7c
    float m_unk80;            // +0x80
    float m_unk84;            // +0x84
    float m_unk88;            // +0x88
};
static_assert(CKProjectileDataTypeFromExplosion::kClassKey == 0xa68c, "key");
DOTD_ASSERT_SIZE(CKProjectileDataTypeFromExplosion, 0x8c);
DOTD_ASSERT_OFFSET(CKProjectileDataTypeFromExplosion, m_unk74, 0x74);
DOTD_ASSERT_OFFSET(CKProjectileDataTypeFromExplosion, m_unk88, 0x88);
