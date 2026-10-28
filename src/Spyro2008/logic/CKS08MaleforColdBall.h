// CKS08MaleforColdBall.h - Malefor's cold ball attack (key 0xabcc, vtable 0xb2a840, size 0xd0). Original unit:
// CKS08MaleforColdBall.cpp (0x4e9120-0x4ea4c8). Derives from CKGolemAttackCommon (its Load and constructor are
// called first). No XXL2 class of this name. Minimal for C2.1: constructor and Load.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/CKGolemAttackCommon.h"

class CKS08MaleforColdBall : public CKGolemAttackCommon {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x2af)
    DOTD_DECLARE_FACTORIES(CKS08MaleforColdBall)

    CKS08MaleforColdBall();  // 0x004e9998 CKS08MaleforColdBall_Construct
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x004ea110 CKS08MaleforColdBall_Load

    IKSerializable* m_unk98;  // +0x98 object reference
    IKSerializable* m_unk9c;  // +0x9c object reference
    IKSerializable* m_unka0;  // +0xa0 object reference
    float m_unka4;            // +0xa4 (file: 10.0)
    int32_t m_unka8;          // +0xa8 (file: 4)
    float m_unkac;            // +0xac (file: 30.0)
    uint32_t m_unkb0;         // +0xb0 not read by the Load
    float m_unkb4;            // +0xb4 (file: 2.38)
    void* m_unkb8;            // +0xb8 a runtime array (data, capacity, count); constructor 0
    uint32_t m_unkbc;         // +0xbc constructor 1
    uint32_t m_unkc0;         // +0xc0 constructor 0
    uint32_t m_unkc4;         // +0xc4 not read by the Load
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
