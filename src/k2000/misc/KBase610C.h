// KBase610C.h - the unregistered base of the logic anchors (key 0x610c; CKInputAnchor, CKOutputAnchor).
// Original unit: CKAnchor.cpp (0x2050c0-0x205290; Ghidra CKAnchor_610c_maybe_*). No XXL2 class; the
// names are ours.
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"
#include "k2000/util/TVector.h"

class KBase610C : public IKSerializable {
public:
    KBase610C() {}  // 0x00205120 CKAnchor_610c_maybe_ConstructBase: the vtable only

    // 0x00205130 CKAnchor_LoadBase_maybe (vt+0x2c of the base).
    int32_t Load(IKFile* file, int32_t type) override;

    // vt+0x50 (CKOutputAnchor_vf50 0x2044f0, CKInputAnchor_vf50 0x2037b0): the link vector (+0x0c). Name ours.
    virtual TVector<IKSerializable*, 1>* GetLinks() = 0;
    // vt+0x54 (CKOutputAnchor_DisconnectAll_maybe 0x204a88, CKInputAnchor_DisconnectAll_maybe 0x203d08): every link
    // removed on both sides.
    virtual void DisconnectAll() = 0;
    // vt+0x58 0x009b1658 KBase610C_vf58 (the anchors share it): the value stored, +0x09 = 1 when it changed,
    // then vt+0x5c. Name ours.
    virtual void SetValue(uint8_t value) {
        const uint8_t previous = m_unk08;
        m_unk08 = value;
        m_unk09 = (value != previous) ? 1 : 0;  // neg + rldicl 1,63 of (value ^ previous)
        PropagateValue();
    }
    // vt+0x5c (CKInputAnchor 0x2037c0, CKOutputAnchor 0x2049e8 PropagateValue_maybe): pass a changed value on.
    virtual void PropagateValue() = 0;
    // vt+0x60 (CKOutputAnchor_ConnectInput 0x204e00): `other` linked, 1 when added. vt+0x64
    // (CKOutputAnchor_DisconnectInput 0x204c68): `other` unlinked, 1 unless `other` has the wrong class.
    // CKInputAnchor: ConnectOutput 0x2041e0 / DisconnectOutput 0x204048.
    virtual uint8_t Connect(KBase610C* other) = 0;
    virtual uint8_t Disconnect(KBase610C* other) = 0;

    IKSerializable* m_pBlock;  // +0x04 the owning logic block (CKInputBlockSequential in the samples)
    uint8_t m_unk08;           // +0x08 the value (read raw, one byte; SetValue)
    uint8_t m_unk09;           // +0x09 the value changed on the last SetValue (never initialised before)
    uint8_t m_pad0a[2];        // +0x0a never written
};
DOTD_ASSERT_SIZE(KBase610C, 0xc);
DOTD_ASSERT_OFFSET(KBase610C, m_pBlock, 0x04);
DOTD_ASSERT_OFFSET(KBase610C, m_unk08, 0x08);
DOTD_ASSERT_OFFSET(KBase610C, m_unk09, 0x09);

// The reference-vector read that CKInputAnchor_Load (0x2038c0), CKOutputAnchor_Load (0x2045a8) and
// CKInputBlockSequential_Load inline: sized to the count (1 when 0), the count stored, then the
// references (also for a count of 0: a Read of 0 bytes). The vector grows by one element.
void KAnchor_LoadRefVector(IKFile* file, TVector<IKSerializable*, 1>* vector);

// The anchor-vector append the block classes inline (CollectAnchors 0x209dd0 / 0x207c38): the block grows by one
// element when full (to one at a capacity of 0), then `anchor` is appended.
void KAnchor_PushBack(TVector<KBase610C*, 1>* vector, KBase610C* anchor);
