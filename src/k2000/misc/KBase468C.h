// KBase468C.h - the unregistered base of the physics elements (key 0x468c; CKPxContainer,
// CKPxContactJoint, ...). Original unit: CKPxElement.cpp (0x218040-0x2182d0; Ghidra
// CKPxElement_468c_maybe_*). No XXL2 class; the names are ours.
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"

class KBase468C : public IKSerializable {
public:
    KBase468C() {}  // 0x00218040 CKPxElement_468c_maybe_ConstructBase: the vtable only

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00218078 CKPxElement_468c_maybe_Load
    // 0x0022cb98 CKPxShape_474c_maybe_GetOwnerBody_maybe (unit CKPxMesh.cpp): +0x04. Its callers are CKSrvPhysics's
    // solvers (CollideBoxBoxSAT, CKPxBoxShape_vf68).
    IKSerializable* GetOwnerBody() const { return m_unk04; }

    IKSerializable* m_unk04;  // +0x04 four references, each read on its own
    IKSerializable* m_unk08;  // +0x08
    IKSerializable* m_unk0c;  // +0x0c
    IKSerializable* m_unk10;  // +0x10
    uint32_t m_unk14;         // +0x14
};
DOTD_ASSERT_SIZE(KBase468C, 0x18);
DOTD_ASSERT_OFFSET(KBase468C, m_unk04, 0x04);
DOTD_ASSERT_OFFSET(KBase468C, m_unk10, 0x10);
DOTD_ASSERT_OFFSET(KBase468C, m_unk14, 0x14);
