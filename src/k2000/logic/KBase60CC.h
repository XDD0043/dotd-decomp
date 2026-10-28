// KBase60CC.h - the unregistered base of the logic blocks (key 0x60cc; KBase628C, the logical blocks).
// Original unit: KBase60CC.cpp (0x203460-...). No XXL2 class; the names are ours.
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"

class KBase60CC : public IKSerializable {
public:
    KBase60CC() { m_unk04 = nullptr; }  // 0x00203460 KBase60CC_Construct

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x002035d8 KBase60CC_Load

    // The block runtime (KBase60CC's vtable 0xb1f068 has +0x50..+0x64 pure). CKS08GameManager_Start
    // activates the input service's blocks 0 and 1 (vt+0x50); CKS08GameManager_vf320 (system time step)
    // and UpdateCKSrvInput 0x2029b8 (fixed game time step) update the active ones (vt+0x58).
    virtual void OnActivate() = 0;           // vt+0x50
    virtual void OnDeactivate() = 0;         // vt+0x54
    virtual void Update(float dt) = 0;       // vt+0x58
    // vt+0x5c / +0x60 (CKInputBlockSequential_CollectAnchors_maybe 0x207c38, _vf60 0x206aa8): not ported.
    virtual void Evaluate(uint8_t value) = 0;  // vt+0x64: an input anchor's value changed (CKInputAnchor vt+0x5c)
    // vt+0x68 0x002034c8 KBase60CC_Activate_maybe: once (+0x0e), into the parent block's active children
    // (+0x08) or, without a parent, the input service's active list.
    virtual void Activate();
    // vt+0x6c 0x00203558 KBase60CC_Deactivate_maybe: the reverse.
    virtual void Deactivate();

    KBase60CC* m_unk04;      // +0x04 the next block in the active list it is in (Activate), else 0
    IKSerializable* m_unk08;  // +0x08 a reference: the parent block (a CKInputBlockSequential) or null
    uint16_t m_unk0c;        // +0x0c
    uint8_t m_unk0e;         // +0x0e active: the Load sets 0, Activate 1, Deactivate 0
    // +0x0f: KBase628C's first member, kept here because the host compilers do not place a derived
    // member in a base's tail padding (the PS3 compiler did).
    uint8_t m_unk0f;
};
DOTD_ASSERT_SIZE(KBase60CC, 0x10);
DOTD_ASSERT_OFFSET(KBase60CC, m_unk08, 0x08);
DOTD_ASSERT_OFFSET(KBase60CC, m_unk0c, 0x0c);
DOTD_ASSERT_OFFSET(KBase60CC, m_unk0e, 0x0e);
