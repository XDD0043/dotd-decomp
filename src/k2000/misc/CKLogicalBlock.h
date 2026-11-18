// CKLogicalBlock.h - the unregistered base of the two-input logical blocks (key 0x640c, vtable 0xb1fb28, size 0x1c:
// CKLogicalBlockAnd / Nand / Nor / Or / Xor). Original unit: CKLogicalBlock.cpp (0x20fb08-0x210070; Ghidra
// CKLogicalBlock_640c_maybe_* / KBase640C_*). No XXL2 class; the names are ours. No KP3 file of LVL000 / LVL010 holds
// one; the classes are registered for the levels that do.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/KBase60CC.h"
#include "k2000/misc/KBase610C.h"

class CKLogicalBlock : public KBase60CC {
public:
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9b1f80
        return key == 0x640c || key == 0x60cc || key == 0xc;
    }

    // 0x0020fd98 CKLogicalBlock_640c_maybe_Construct (0x0020fd60 Construct_2: the same): the KBase60CC part and the
    // vtable; the anchors are left as the fresh heap has them (0).
    CKLogicalBlock() : m_pInputs{nullptr, nullptr}, m_pOutput(nullptr) {}
    // 0x0020fd30 CKLogicalBlock_640c_maybe_BaseDestructor (0x0020fd00 Destructor, 0x0020fcb8 DeletingDestructor):
    // the vtable stores only.
    ~CKLogicalBlock() override {}

    // vt+0x24 0x0020fc68 CKLogicalBlock_640c_maybe_LevelReset (the recursive registration): KBase60CC's (nothing).
    // vt+0x10 0x0020fc90 CKLogicalBlock_640c_maybe_ClearReferences (Destroy): KBase60CC's (nothing).
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0020fb08 CKLogicalBlock_640c_maybe_Load

    // vt+0x50 / +0x54 / +0x58: empty (each derived class has its own empty copy, 0x9b1c18 ... ).
    void OnActivate() override {}
    void OnDeactivate() override {}
    void Update(float /*dt*/) override {}
    // vt+0x5c 0x0020fe70 KBase640C_CollectAnchors_maybe: the two inputs and the output appended to `out`.
    void CollectAnchors(TVector<KBase610C*, 1>* out) override;
    // vt+0x60 0x0020fdd0 KBase640C_vf60: every link of the three anchors removed (vt+0x54).
    void DisconnectAnchors() override;
    // vt+0x64 (pure here): the derived class's gate of the two input values written to the output anchor.

    KBase610C* m_pInputs[2];  // +0x10 references: the two input anchors (their value byte +0x08 is read)
    KBase610C* m_pOutput;     // +0x18 a reference: the output anchor (vt+0x58 SetValue)
};
DOTD_ASSERT_SIZE(CKLogicalBlock, 0x1c);
DOTD_ASSERT_OFFSET(CKLogicalBlock, m_pInputs, 0x10);
DOTD_ASSERT_OFFSET(CKLogicalBlock, m_pOutput, 0x18);
