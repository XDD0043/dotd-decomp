// CKS08EnemyAttack.h - one attack of an enemy (key 0x990c, vtable 0xb223a0, size 0x70). Original unit:
// CKS08EnemyAttack.cpp (0x2acb08-0x2ae2d0). No XXL2 class of this name. Two inlined growable byte arrays
// (data, capacity, count) at +0x48 and +0x54, sized by the attack type (+0x04) through a static table.
#pragma once
#include <cstdint>

#include "Spyro2008/logic/CKS08Damage.h"
#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"
#include "k2000/logic/CKProjectileAccessor.h"

class CKS08EnemyAttack : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x264)
    int32_t IsKindOfClass(uint32_t key) override { return key == 0x990c || key == 0xc; }  // vt+0x08 0x9bca78
    DOTD_DECLARE_FACTORIES(CKS08EnemyAttack)

    // A byte array as the Load fills it: data (Mem_AllocAligned16 / Mem_ReallocAligned16), capacity, count.
    struct ByteArray {
        uint8_t* m_data;      // +0x00
        uint32_t m_capacity;  // +0x04
        uint32_t m_count;     // +0x08
    };

    // 0x002acb58 CKS08EnemyAttack_Construct (inlined the same in Create): both arrays empty, capacity 1.
    CKS08EnemyAttack() {
        m_array48.m_data = nullptr;
        m_array48.m_capacity = 1;
        m_array48.m_count = 0;
        m_array54.m_capacity = 1;
        m_array54.m_count = 0;
        m_array54.m_data = nullptr;
    }
    // 0x002ae0d8 CKS08EnemyAttack_Destructor: both arrays freed and emptied (+0x54 first).
    CKS08EnemyAttack(const CKS08EnemyAttack& other);  // 0x002ace60 CKS08EnemyAttack_CopyConstruct_maybe
    ~CKS08EnemyAttack() override;
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x002ad690 CKS08EnemyAttack_Load

    int32_t m_unk04;                    // +0x04 _maybe the attack type: indexes the size table
    int32_t m_unk08;                    // +0x08
    float m_unk0c;                      // +0x0c
    float m_unk10;                      // +0x10
    float m_unk14;                      // +0x14
    uint8_t m_unk18;                    // +0x18
    uint8_t m_pad19[3];
    float m_unk1c;                      // +0x1c
    CKS08Damage* m_pDamage;             // +0x20
    int32_t m_unk24;                    // +0x24
    float m_unk28[6];                   // +0x28..+0x3c
    CKProjectileAccessor* m_pProjectile;// +0x40 null unless the reference is a CKProjectileAccessor
    float m_unk44;                      // +0x44
    ByteArray m_array48;                // +0x48
    ByteArray m_array54;                // +0x54
    float m_unk60;                      // +0x60
    int32_t m_unk64;                    // +0x64
    float m_unk68;                      // +0x68
    uint8_t m_unk6c;                    // +0x6c (+0x6d..+0x6f padding)
};
DOTD_ASSERT_SIZE(CKS08EnemyAttack, 0x70);
DOTD_ASSERT_SIZE(CKS08EnemyAttack::ByteArray, 0xc);
DOTD_ASSERT_OFFSET(CKS08EnemyAttack, m_unk04, 0x04);
DOTD_ASSERT_OFFSET(CKS08EnemyAttack, m_unk18, 0x18);
DOTD_ASSERT_OFFSET(CKS08EnemyAttack, m_unk1c, 0x1c);
DOTD_ASSERT_OFFSET(CKS08EnemyAttack, m_pDamage, 0x20);
DOTD_ASSERT_OFFSET(CKS08EnemyAttack, m_unk28, 0x28);
DOTD_ASSERT_OFFSET(CKS08EnemyAttack, m_pProjectile, 0x40);
DOTD_ASSERT_OFFSET(CKS08EnemyAttack, m_unk44, 0x44);
DOTD_ASSERT_OFFSET(CKS08EnemyAttack, m_array48, 0x48);
DOTD_ASSERT_OFFSET(CKS08EnemyAttack, m_array54, 0x54);
DOTD_ASSERT_OFFSET(CKS08EnemyAttack, m_unk60, 0x60);
DOTD_ASSERT_OFFSET(CKS08EnemyAttack, m_unk68, 0x68);
DOTD_ASSERT_OFFSET(CKS08EnemyAttack, m_unk6c, 0x6c);
