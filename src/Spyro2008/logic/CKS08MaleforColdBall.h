// CKS08MaleforColdBall.h - Malefor's cold ball attack (key 0xabcc, vtable 0xb2a840, size 0xd0). Original unit:
// CKS08MaleforColdBall.cpp (0x4e9120-0x4ea4c8). Derives from CKGolemAttackCommon (its Load and constructor are
// called first). No XXL2 class of this name. Minimal for C2.1: constructor and Load.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/logic/CKGolemAttackCommon.h"

class CKS08MaleforColdBall : public CKGolemAttackCommon {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x2af)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c6708
        return key == 0xabcc || key == 0xc || key == 0x994c || key == 0x984c;
    }
    DOTD_DECLARE_FACTORIES(CKS08MaleforColdBall)

    CKS08MaleforColdBall();  // 0x004e9998 CKS08MaleforColdBall_Construct
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x004ea110 CKS08MaleforColdBall_Load
    // vt+0x00 0x004e98c8 CKS08MaleforColdBall_Destructor (and 0x4e9a98 / 0x4e9b08): the point block freed.
    ~CKS08MaleforColdBall() override;
    // vt+0x30 0x004e9710 CKS08MaleforColdBall_PostLoad: CKGolemAttackCommon's; type 0: a fresh one-point block (capacity
    // 1) and +0xa8 "no point" vectors (FLT_MAX) appended (BUG(original): the old block and count are kept).
    int32_t PostLoad(int32_t type) override;
    void StartAttack() override;          // vt+0x50 0x004e96d0: CKGolemAttackCommon's, then +0xb0 = 0, +0xc4 = 0
    // vt+0x60 0x004ea078: the time counts to +0xb4, then (once) the balls and the explosion.
    void Update(IKTime* clock) override;
    // vt+0x64 0x004e9cd0 CKS08MaleforColdBall_vf64: the projectile type's live balls at or below the beacon (+0xa0) height
    // killed (vt+0x5c); without type, beacon or balls: vt+0x6c.
    void Vf64() override;
    // 0x004e9500 CKS08MaleforColdBall_ScatterTargetPoints_maybe: per point two rand draws: x and z within +0xa4 of the
    // beacon's, y the beacon's; 0 without the beacon (LaunchBalls inlines it).
    uint8_t ScatterTargetPoints();
    // 0x004e9e00 CKS08MaleforColdBall_LaunchBalls_maybe: the points scattered, then a ball from the golem's hot spot 11 at
    // every point that is not "no point" (speed +0xac, damage +0xcc, the golem as owner), each followed by vt+0x68.
    void LaunchBalls();
    void Explode();  // 0x004e91a8 CKS08MaleforColdBall_Explode

    IKSerializable* m_unk98;  // +0x98 object reference
    IKSerializable* m_unk9c;  // +0x9c object reference
    IKSerializable* m_unka0;  // +0xa0 object reference
    float m_unka4;            // +0xa4 (file: 10.0)
    int32_t m_unka8;          // +0xa8 (file: 4)
    float m_unkac;            // +0xac (file: 30.0)
    float m_unkb0;            // +0xb0 not read by the Load: the time since the start (StartAttack clears it)
    float m_unkb4;            // +0xb4 (file: 2.38)
    CVector3* m_unkb8;        // +0xb8 a runtime array (data, capacity, count) of target points; constructor 0
    uint32_t m_unkbc;         // +0xbc constructor 1
    uint32_t m_unkc0;         // +0xc0 constructor 0
    uint8_t m_unkc4;          // +0xc4 not read by the Load: the balls are launched (StartAttack clears it)
    uint8_t m_padc5[3];
    IKSerializable* m_unkc8;  // +0xc8 object reference
    IKSerializable* m_unkcc;  // +0xcc object reference
};
DOTD_ASSERT_SIZE(CKS08MaleforColdBall, 0xd0);
DOTD_ASSERT_OFFSET(CKS08MaleforColdBall, m_unk98, 0x98);
DOTD_ASSERT_OFFSET(CKS08MaleforColdBall, m_unk9c, 0x9c);
DOTD_ASSERT_OFFSET(CKS08MaleforColdBall, m_unka0, 0xa0);
DOTD_ASSERT_OFFSET(CKS08MaleforColdBall, m_unka4, 0xa4);
DOTD_ASSERT_OFFSET(CKS08MaleforColdBall, m_unka8, 0xa8);
DOTD_ASSERT_OFFSET(CKS08MaleforColdBall, m_unkac, 0xac);
DOTD_ASSERT_OFFSET(CKS08MaleforColdBall, m_unkb4, 0xb4);
DOTD_ASSERT_OFFSET(CKS08MaleforColdBall, m_unkb8, 0xb8);
DOTD_ASSERT_OFFSET(CKS08MaleforColdBall, m_unkc8, 0xc8);
DOTD_ASSERT_OFFSET(CKS08MaleforColdBall, m_unkcc, 0xcc);
