// CKS08MaleforFireBreath.h - Malefor's fire breath attack (key 0xac4c, vtable 0xb2a8f0, size 0x130). Original
// unit: CKS08MaleforFireBreath.cpp (0x4ea4c8-0x4eafb0). Derives from CKGolemAttackCommon (its Load and
// constructor are called first). No XXL2 class of this name. Minimal for C2.1: constructor and Load.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/CKGolemAttackCommon.h"

class CKS08AbilityHostBase;

class CKS08MaleforFireBreath : public CKGolemAttackCommon {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x2b1)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c6768
        return key == 0xac4c || key == 0xc || key == 0x994c || key == 0x984c;
    }
    DOTD_DECLARE_FACTORIES(CKS08MaleforFireBreath)

    // Eight groups of four references (all null in the LVL120 data).
    struct RefGroup {
        IKSerializable* m_unk00;  // +0x00
        IKSerializable* m_unk04;  // +0x04
        IKSerializable* m_unk08;  // +0x08
        IKSerializable* m_unk0c;  // +0x0c
    };

    // 0x004ea860 CKS08MaleforFireBreath_Construct: stores the vtable only. DOTD: +0x118 (the host) is read by Destroy
    // before any write when no type-0 PostLoad ran; the original's fresh heap has 0 there.
    CKS08MaleforFireBreath() { m_unk118 = nullptr; }
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x004eac60 CKS08MaleforFireBreath_Load
    // vt+0x30 0x004ea650 CKS08MaleforFireBreath_PostLoad: CKGolemAttackCommon's, then (type 0) the ability host.
    int32_t PostLoad(int32_t type) override;
    // vt+0x60 0x004ea9e0 CKS08MaleforFireBreath_Update_maybe: CKGolemAttackCommon's, then the breath ability (+0x12c)
    // started with the host at +0x120 seconds, stopped at +0x124, stepped while it runs.
    void Update(IKTime* clock) override;
    // vt+0x10 0x004ea718 CKS08MaleforFireBreath_Destroy: CKGolemAttackCommon's, then the ability host deleted (vt+0x04).
    void Destroy() override;
    void StartAttack() override;  // vt+0x50 0x004ea608: CKGolemAttackCommon's, then +0x11d, +0x128, +0x11c cleared
    // vt+0x54 0x004ea570: CKGolemAttackCommon's, then a started breath not stopped yet is stopped (the ability's vt+0x5c 0).
    void StopAttack() override;

    RefGroup m_unk98[8];       // +0x98..+0x117
    // +0x118 not read by the Load: the ability host (CKS08MaleforFireBreathAbilityHost, OperatorNew(8)) PostLoad makes for
    // the breath (+0x12c).
    CKS08AbilityHostBase* m_unk118;
    uint8_t m_unk11c;          // +0x11c not read by the Load: the breath started (Update)
    uint8_t m_unk11d;          // +0x11d the breath stopped
    uint8_t m_pad11e[2];
    float m_unk120;            // +0x120 (file: 1.46, 0.64)
    float m_unk124;            // +0x124 (file: 4.12, 1.8)
    float m_unk128;            // +0x128 not read by the Load: the time since the start (StartAttack clears it)
    IKSerializable* m_unk12c;  // +0x12c object reference
};
DOTD_ASSERT_SIZE(CKS08MaleforFireBreath::RefGroup, 0x10);
DOTD_ASSERT_SIZE(CKS08MaleforFireBreath, 0x130);
DOTD_ASSERT_OFFSET(CKS08MaleforFireBreath, m_unk98, 0x98);
DOTD_ASSERT_OFFSET(CKS08MaleforFireBreath, m_unk120, 0x120);
DOTD_ASSERT_OFFSET(CKS08MaleforFireBreath, m_unk124, 0x124);
DOTD_ASSERT_OFFSET(CKS08MaleforFireBreath, m_unk12c, 0x12c);
