// CKS08MaleforFireBreath.h - Malefor's fire breath attack (key 0xac4c, vtable 0xb2a8f0, size 0x130). Original
// unit: CKS08MaleforFireBreath.cpp (0x4ea4c8-0x4eafb0). Derives from CKGolemAttackCommon (its Load and
// constructor are called first). No XXL2 class of this name. Minimal for C2.1: constructor and Load.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/CKGolemAttackCommon.h"

class CKS08MaleforFireBreath : public CKGolemAttackCommon {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x2b1)
    DOTD_DECLARE_FACTORIES(CKS08MaleforFireBreath)

    // Eight groups of four references (all null in the LVL120 data).
    struct RefGroup {
        IKSerializable* m_unk00;  // +0x00
        IKSerializable* m_unk04;  // +0x04
        IKSerializable* m_unk08;  // +0x08
        IKSerializable* m_unk0c;  // +0x0c
    };

    CKS08MaleforFireBreath() {}  // 0x004ea860 CKS08MaleforFireBreath_Construct: stores the vtable only
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x004eac60 CKS08MaleforFireBreath_Load

    RefGroup m_unk98[8];       // +0x98..+0x117
    uint32_t m_unk118;         // +0x118 not read by the Load
    uint32_t m_unk11c;         // +0x11c not read by the Load
    float m_unk120;            // +0x120 (file: 1.46, 0.64)
    float m_unk124;            // +0x124 (file: 4.12, 1.8)
    uint32_t m_unk128;         // +0x128 not read by the Load
    IKSerializable* m_unk12c;  // +0x12c object reference
};
DOTD_ASSERT_SIZE(CKS08MaleforFireBreath::RefGroup, 0x10);
DOTD_ASSERT_SIZE(CKS08MaleforFireBreath, 0x130);
DOTD_ASSERT_OFFSET(CKS08MaleforFireBreath, m_unk98, 0x98);
DOTD_ASSERT_OFFSET(CKS08MaleforFireBreath, m_unk120, 0x120);
DOTD_ASSERT_OFFSET(CKS08MaleforFireBreath, m_unk124, 0x124);
DOTD_ASSERT_OFFSET(CKS08MaleforFireBreath, m_unk12c, 0x12c);
