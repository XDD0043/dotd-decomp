// KBase628C.h - the unregistered base of the input blocks (key 0x628c; CKInputBlockSequential, ...).
// Original unit: CKInputBlock.cpp (Ghidra CKInputBlock_628c_maybe_* / KBase628C_*). No XXL2 class; the
// names are ours.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/KBase60CC.h"

class CKInputAnchor;

class KBase628C : public KBase60CC {
public:
    KBase628C() {}  // 0x00209d98 KBase628C_Construct_maybe: KBase60CC_Construct, then the vtable

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00209b38 CKInputBlock_628c_maybe_Load

    // KBase628C's vtable 0xb1f300 (KBase628C_Construct_maybe 0x209d98 stores it).
    void OnActivate() override;    // vt+0x50 0x00209a10 InputBlock_CallActivate_maybe: Activate (vt+0x68)
    void OnDeactivate() override;  // vt+0x54 0x00209a50 InputBlock_CallDeactivate_maybe: Deactivate (vt+0x6c)
    // vt+0x58 pure (__cxa_pure_virtual).
    // vt+0x64 0x00209fa0 KBase628C_Evaluate: input 1 set -> both inputs cleared and OnDeactivate; else
    // input 0 set -> cleared and OnActivate unless the block has a parent and is already active.
    void Evaluate(uint8_t value) override;
    // vt+0x70..+0x90: not ported.
    // vt+0x94 0x009b1860 (Ghidra PS3_CKInputBlockPosition_vf94): the block's step index; -1 here.
    // CKInputBlockSequential returns its +0x20. Name ours.
    virtual int32_t GetStepIndex() { return -1; }

    // +0x0f (m_unk0f in KBase60CC): one byte read raw; the player passed to the game manager's action
    // queries (CKInputBlockSequential_Update_maybe).
    CKInputAnchor* m_apInputs[2];  // +0x10 two references (CKInputAnchor in the samples): [0] activate, [1] deactivate
};
DOTD_ASSERT_SIZE(KBase628C, 0x18);
DOTD_ASSERT_OFFSET(KBase628C, m_unk0f, 0x0f);
DOTD_ASSERT_OFFSET(KBase628C, m_apInputs, 0x10);
