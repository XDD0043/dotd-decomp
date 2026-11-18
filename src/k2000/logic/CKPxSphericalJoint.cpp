// CKPxSphericalJoint.cpp - reconstructed original translation unit 0x226a38-0x227528 (GAME_TOC1, main_toc1), 16 functions, 16 live.
// Primary class: CKPxSphericalJoint  key 0x4d8c  category Logic  size 0x78  vtable 0xb20130
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x226a38  CKPxSphericalJoint_Delete
//   [ ] 0x226a88  RegisterCKPxSphericalJointClass
//   [ ] 0x226b00  _GLOBAL__I_226b00
//   [ ] 0x226b10  CKPxSphericalJoint_Save
//   [x] 0x226b38  CKPxSphericalJoint_RecursiveRegistration  (the base's vf24: returns 1, registers nothing)
//   [x] 0x226b60  CKPxSphericalJoint_Destroy  (KBase488C's: the anchors freed)
//   [x] 0x226b88  CKPxSphericalJoint_Construct  (header)
//   [x] 0x226bc0  CKPxSphericalJoint_DeleteArray
//   [x] 0x226c68  CKPxSphericalJoint_DeletingDestructor  (the destructor; delete)
//   [x] 0x226cb0  CKPxSphericalJoint_Destructor  (C++ destructor chain: vtable stores only)
//   [x] 0x226ce0  CKPxSphericalJoint_BaseDestructor  (C++ destructor chain: vtable stores only)
//   [x] 0x226d10  CKPxSphericalJoint_Construct_2  (the constructor's second C++ variant)
//   [x] 0x226d48  CKPxSphericalJoint_vf60  (Solve)
//   [x] 0x227240  CKPxSphericalJoint_Load
//   [x] 0x227418  CKPxSphericalJoint_CreateArray
//   [x] 0x2274d0  CKPxSphericalJoint_Create
//
//   [ ] 0x9b4808  CKPxSphericalJoint_IsKindOfClass  [inline]
//   [ ] 0x9b4840  CKPxSphericalJoint_GetClassType  [inline]
//   [ ] 0x9b4848  CKPxSphericalJoint_GetClassID  [inline]
//   [ ] 0x9b4850  CKPxSphericalJoint_InitFromDesc_maybe  [inline]
//   [ ] 0x9b48c8  CKPxSphericalJoint_ExportState  [inline]
#include "k2000/logic/CKPxSphericalJoint.h"

#include "k2000/logic/CKPxBody.h"
#include "k2000/misc/Mat4.h"
#include "k2000/misc/PxJointRows.h"

namespace {
const CVector3 kNullVector{0.0f, 0.0f, 0.0f};  // 0x00c50d64
}  // namespace

// 0x00227240 CKPxSphericalJoint_Load
int32_t CKPxSphericalJoint::Load(IKFile* file, int32_t type) {
    KBase488C::Load(file, type);  // 0x0021da00
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(&m_unk58), 3);
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(&m_unk64), 3);
    ReadF32LE(file, &m_fUnk70);
    ReadF32LE(file, &m_fUnk74);
    return 1;
}

// 0x00226d48 CKPxSphericalJoint_vf60 (vt+0x60, Solve): with a body to take the rows (vt+0x5c): the limit planes
// (vt+0x64), then a row (kind 0x80) between the two anchors (+0x58 / +0x64, turned by each body): the direction from
// the first to the second, the stretch past the rest length (+0x70) beyond the slack (+0x74) at +0x38, the relative
// speed along it at +0x34. A zero or tiny distance (below 1e-6) adds no row.
void CKPxSphericalJoint::Solve() {
    CKPxBody* body = WakeAndPickBody();  // vt+0x5c
    if (body == nullptr) return;
    AddLimitRow(body);  // vt+0x64
    CKPxBody::Record* row = body->NextRecord();
    row->m_unk00 = 0x80;
    row->m_pBodyA = static_cast<CKPxBody*>(m_unk20);
    row->m_pBodyB = static_cast<CKPxBody*>(m_unk28);
    CVector3 pointA, velocityA;
    if (m_unk1c != nullptr) {
        CKPxBody* a = static_cast<CKPxBody*>(m_unk1c);
        Mat4_TransformVectors(a->m_pWorldMatrix, &row->m_vArmA, &m_unk58, 1);  // 0x0023f7b0
        velocityA = pxrows::VelocityAt(a, row->m_vArmA);
        pointA = pxrows::Add(row->m_vArmA, a->m_pWorldMatrix->m_pos);
    } else {
        row->m_vArmA = m_unk58;
        pointA = m_unk58;
        velocityA = kNullVector;
    }
    CVector3 pointB, velocityB;
    if (m_unk24 != nullptr) {
        CKPxBody* b = static_cast<CKPxBody*>(m_unk24);
        Mat4_TransformVectors(b->m_pWorldMatrix, &row->m_vArmB, &m_unk64, 1);
        velocityB = pxrows::VelocityAt(b, row->m_vArmB);
        pointB = pxrows::Add(row->m_vArmB, b->m_pWorldMatrix->m_pos);
    } else {
        row->m_vArmB = m_unk64;
        pointB = m_unk64;
        velocityB = kNullVector;
    }
    row->m_vNormal = pxrows::Sub(pointB, pointA);
    const float length = pxrows::NormaliseRow(row);
    if (length == 0.0f) {
        row->m_fUnk38 = 0.0f;
        return;
    }
    row->m_fUnk38 = length;
    if (length < 1e-6f) return;  // blt (0x358637bd)
    float stretch = length - m_fUnk70;
    row->m_fUnk38 = stretch;
    const float slack = m_fUnk74;
    if (stretch > slack) {
        row->m_fUnk38 = stretch - slack;
    } else if (-slack <= stretch) {  // ble: NaN takes it
        row->m_fUnk38 = 0.0f;
    } else {
        row->m_fUnk38 = stretch + slack;
    }
    row->m_fUnk34 = pxrows::Dot(pxrows::Sub(velocityB, velocityA), row->m_vNormal);
    ++body->m_ui16Unk128;
}

