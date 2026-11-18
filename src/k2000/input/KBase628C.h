// KBase628C.h - the unregistered base of the input blocks (key 0x628c; CKInputBlockSequential, ...).
// Original unit: CKInputBlock.cpp (Ghidra CKInputBlock_628c_maybe_* / KBase628C_*). No XXL2 class; the
// names are ours.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/KBase60CC.h"
#include "k2000/util/TVector.h"

class CKInputAnchor;
class KBase610C;

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
    // vt+0x5c 0x00209dd0 PS3_CKInputBlockPosition_CollectAnchors_maybe: the two input anchors appended to `out`
    // (CKInputBlockSequential adds its six).
    void CollectAnchors(TVector<KBase610C*, 1>* out) override;
    // vt+0x60 0x00209998 PS3_CKInputBlockPosition_vf60: every link of the two input anchors removed (their vt+0x54).
    void DisconnectAnchors() override;
    // vt+0x70 0x009b18c0 KBase628C_vf70: +0x0f = value ^ 1 (CKInputBlockSequential passes it on to its children).
    virtual void SetEnabled(uint8_t value) { m_unk0f = static_cast<uint8_t>(value ^ 1); }
    virtual int32_t GetCommonValue1C() { return -1; }                  // vt+0x74 0x009b1828
    virtual void SetCommonValue1C(int32_t /*value*/, int32_t /*propagate*/) {}  // vt+0x78 0x009b1830 (empty)
    virtual void SetBit0(uint8_t /*value*/) {}                        // vt+0x80 0x009b1840 (empty)
    virtual void SetBit1(uint8_t /*value*/) {}                        // vt+0x8c 0x009b1850 (empty)
    virtual void SetStepIndex(int32_t /*value*/, int32_t /*propagate*/) {}  // vt+0x98 0x009b1868 (empty)
    virtual void Vf9C(uint8_t /*value*/) {}                           // vt+0x9c 0x009b1870 (empty)
    virtual void VfA0(uint8_t /*value*/) {}                           // vt+0xa0 0x009b1878 (empty)
    virtual void VfA4(uint8_t /*value*/) {}                           // vt+0xa4 0x009b1880 (empty)
    virtual void VfA8(uint8_t /*value*/) {}                           // vt+0xa8 0x009b1888 (empty)
    virtual void SetStartDelay(float /*value*/) {}                    // vt+0xac 0x009b1890 (empty)
    virtual void VfB0(float /*value*/) {}                             // vt+0xb0 0x009b1898 (empty)
    virtual void VfB4(float /*value*/) {}                             // vt+0xb4 0x009b18a0 (empty)
    virtual void SetEndDelay(float /*value*/) {}                      // vt+0xb8 0x009b18a8 (empty)
    virtual uint8_t VfC0() { return 0; }                              // vt+0xc0 0x009b18b8
    // vt+0x7c..+0x94, +0xbc: the slots the input-icon effect reads (CKInputIconNodeFx_Update /
    // UpdatePlacement_maybe), with KBase628C's own bodies (0xb1f300; the shared PS3_CKInputBlockPosition stubs). The
    // other block classes (CKInputBlockSingleAction / DoubleAction / StickCircleAction, PS3_CKInputBlockPosition) are in
    // no game file. Names ours.
    virtual uint8_t Vf7C() { return 0; }                // vt+0x7c 0x009b1838: waiting for its action (the icon blinks)
    virtual uint8_t Vf84() { return 0; }                // vt+0x84 0x009b1750 KStub_Return0_9b1750
    virtual uint8_t Vf88() { return 0; }                // vt+0x88 0x009b1848: the icon shown larger (CKSrvInput +0x34)
    virtual int32_t GetButtonGlyph() { return 0x3f; }   // vt+0x90 0x009b1858: the font glyph of its button ('?')
    // vt+0x94 0x009b1860 (Ghidra PS3_CKInputBlockPosition_vf94): the block's step index; -1 here.
    // CKInputBlockSequential returns its +0x20. Name ours.
    virtual int32_t GetStepIndex() { return -1; }
    virtual uint8_t VfBC() { return 0; }                // vt+0xbc 0x009b18b0: done (the icon shows the next glyph)

    // +0x0f (m_unk0f in KBase60CC): one byte read raw; the player passed to the game manager's action
    // queries (CKInputBlockSequential_Update_maybe).
    CKInputAnchor* m_apInputs[2];  // +0x10 two references (CKInputAnchor in the samples): [0] activate, [1] deactivate
};
DOTD_ASSERT_SIZE(KBase628C, 0x18);
DOTD_ASSERT_OFFSET(KBase628C, m_unk0f, 0x0f);
DOTD_ASSERT_OFFSET(KBase628C, m_apInputs, 0x10);
