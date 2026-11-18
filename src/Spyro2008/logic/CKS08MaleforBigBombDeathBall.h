// CKS08MaleforBigBombDeathBall.h - Malefor's big bomb attack (key 0xac0c, vtable 0xb2a790, size 0xd4). Original
// unit: CKS08MaleforBigBombDeathBall.cpp (0x4e7ac0-0x4e9120). Derives from CKGolemAttackCommon (its Load and
// constructor are called first). No XXL2 class of this name. Minimal for C2.1: constructor and Load.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/logic/CKGolemAttackCommon.h"

class CKS08MaleforBigBombDeathBall : public CKGolemAttackCommon {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x2b0)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c66a8
        return key == 0xac0c || key == 0xc || key == 0x994c || key == 0x984c;
    }
    DOTD_DECLARE_FACTORIES(CKS08MaleforBigBombDeathBall)

    // One entry of the +0xc8 array (OperatorNew(0x14)).
    struct Entry {
        float m_unk00;           // +0x00 (file: 10.3, 13.3, ...)
        float m_unk04;           // +0x04 (file: 2.07, 2.65, ...)
        CVector3 m_vDir;         // +0x08 not read by the Load: the ball's direction (ComputeSpreadDirections_maybe)
    };

    CKS08MaleforBigBombDeathBall();  // 0x004e8170 CKS08MaleforBigBombDeathBall_Construct
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x004e8a40 CKS08MaleforBigBombDeathBall_Load
    // vt+0x00 0x004e80a0 CKS08MaleforBigBombDeathBall_Destructor (and 0x4e8270 / 0x4e82e0): the entry block freed.
    ~CKS08MaleforBigBombDeathBall() override;
    // vt+0x10 0x004e8018 CKS08MaleforBigBombDeathBall_Destroy: CKGolemAttackCommon's, then every entry deleted (the
    // block and its pointers kept: BUG(original), a second Destroy deletes them again).
    void Destroy() override;
    void StartAttack() override;          // vt+0x50 0x004e7f68: CKGolemAttackCommon's, then +0xa4 = 0
    void Update(IKTime* clock) override;  // vt+0x60 0x004e8868: at the animation time +0xa0, the balls and the explosion
    // 0x004e8358 CKS08MaleforBigBombDeathBall_ComputeSpreadDirections_maybe: the golem's flat forward (its node's at, y 0,
    // unit) turned about Y by -spread..+spread degrees (+0xa8) over +0xac directions into the entries; 0 without
    // directions or the golem's hot spot 6.
    uint8_t ComputeSpreadDirections();
    // 0x004e85f8 CKS08MaleforBigBombDeathBall_RandomizeBallParams_maybe: the directions, then per entry two rand draws: the
    // speed in [+0xb8, +0xbc] and +0x04 in [+0xb0, +0xb4].
    uint8_t RandomizeBallParams();
    // 0x004e8720 CKS08MaleforBigBombDeathBall_LaunchBalls_maybe: the balls launched from the golem's hot spot 6 (the
    // projectile accessor +0x98, damage +0xc4, the golem as owner); +0xa4 = 1.
    uint8_t LaunchBalls();
    void Explode();  // 0x004e7b98 CKS08MaleforBigBombDeathBall_Explode

    IKSerializable* m_unk98;   // +0x98 object reference
    IKSerializable* m_unk9c;   // +0x9c object reference
    float m_unka0;             // +0xa0 (file: 0.1)
    uint8_t m_unka4;           // +0xa4 not read by the Load: the balls are launched (StartAttack clears it)
    uint8_t m_pada5[3];
    float m_unka8;             // +0xa8 (file: 45.0)
    int32_t m_unkac;           // +0xac (file: 5, the entry count of that object)
    float m_unkb0;             // +0xb0 (file: 2.0)
    float m_unkb4;             // +0xb4 (file: 5.0)
    float m_unkb8;             // +0xb8 (file: 10.0)
    float m_unkbc;             // +0xbc (file: 30.0)
    IKSerializable* m_unkc0;   // +0xc0 object reference
    IKSerializable* m_unkc4;   // +0xc4 object reference
    Entry** m_apEntries;       // +0xc8 (Mem_AllocAligned16 / Mem_ReallocAligned16)
    uint32_t m_entryCapacity;  // +0xcc
    uint32_t m_entryCount;     // +0xd0
};
DOTD_ASSERT_SIZE(CKS08MaleforBigBombDeathBall::Entry, 0x14);
DOTD_ASSERT_SIZE(CKS08MaleforBigBombDeathBall, 0xd4);
DOTD_ASSERT_OFFSET(CKS08MaleforBigBombDeathBall, m_unk98, 0x98);
DOTD_ASSERT_OFFSET(CKS08MaleforBigBombDeathBall, m_unk9c, 0x9c);
DOTD_ASSERT_OFFSET(CKS08MaleforBigBombDeathBall, m_unka0, 0xa0);
DOTD_ASSERT_OFFSET(CKS08MaleforBigBombDeathBall, m_unka8, 0xa8);
DOTD_ASSERT_OFFSET(CKS08MaleforBigBombDeathBall, m_unkac, 0xac);
DOTD_ASSERT_OFFSET(CKS08MaleforBigBombDeathBall, m_unkb0, 0xb0);
DOTD_ASSERT_OFFSET(CKS08MaleforBigBombDeathBall, m_unkb4, 0xb4);
DOTD_ASSERT_OFFSET(CKS08MaleforBigBombDeathBall, m_unkb8, 0xb8);
DOTD_ASSERT_OFFSET(CKS08MaleforBigBombDeathBall, m_unkbc, 0xbc);
DOTD_ASSERT_OFFSET(CKS08MaleforBigBombDeathBall, m_unkc0, 0xc0);
DOTD_ASSERT_OFFSET(CKS08MaleforBigBombDeathBall, m_unkc4, 0xc4);
DOTD_ASSERT_OFFSET(CKS08MaleforBigBombDeathBall, m_apEntries, 0xc8);
DOTD_ASSERT_OFFSET(CKS08MaleforBigBombDeathBall, m_entryCount, 0xd0);
