// CKPxFixedJoint.cpp - reconstructed original translation unit 0x225828-0x226a38 (GAME_TOC1, main_toc1), 16 functions, 16 live.
// Primary class: CKPxFixedJoint  key 0x508c  category Logic  size 0x64  vtable 0xb200b8
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x225828  CKPxFixedJoint_Delete
//   [ ] 0x225878  RegisterCKPxFixedJointClass
//   [ ] 0x2258f0  _GLOBAL__I_2258f0
//   [x] 0x225900  CKPxFixedJoint_Load
//   [ ] 0x2259f0  CKPxFixedJoint_Save
//   [x] 0x225a18  CKPxFixedJoint_RecursiveRegistration  (the base's vf24: returns 1, registers nothing)
//   [x] 0x225a40  CKPxFixedJoint_Destroy
//   [x] 0x225a90  CKPxFixedJoint_DeletingDestructor  (the destructor; delete)
//   [x] 0x225ad8  CKPxFixedJoint_Destructor  (C++ destructor chain: vtable stores only)
//   [x] 0x225b08  CKPxFixedJoint_BaseDestructor  (C++ destructor chain: vtable stores only)
//   [x] 0x225b38  CKPxFixedJoint_Construct  (header)
//   [x] 0x225b70  CKPxFixedJoint_Construct_2  (the constructor's second C++ variant)
//   [x] 0x225ba8  CKPxFixedJoint_DeleteArray
//   [x] 0x225c48  CKPxFixedJoint_CreateArray
//   [x] 0x225cf8  CKPxFixedJoint_Create
//   [x] 0x225d50  CKPxFixedJoint_vf60  (Solve)
//
//   [ ] 0x9b4450  CKPxFixedJoint_IsKindOfClass  [inline]
//   [ ] 0x9b4488  CKPxFixedJoint_GetClassType  [inline]
//   [ ] 0x9b4490  CKPxFixedJoint_GetClassID  [inline]
//   [ ] 0x9b4498  CKPxFixedJoint_InitFromDesc_maybe  [inline]
//   [ ] 0x9b4650  CKPxFixedJoint_ExportState  [inline]
#include "k2000/logic/CKPxFixedJoint.h"

#include "k2000/logic/CKPxBody.h"
#include "k2000/misc/Mat4.h"
#include "k2000/misc/PxJointRows.h"

namespace {
const CVector3 kNullVector{0.0f, 0.0f, 0.0f};  // 0x00c50d64
}  // namespace

// 0x00225900 CKPxFixedJoint_Load
int32_t CKPxFixedJoint::Load(IKFile* file, int32_t type) {
    KBase488C::Load(file, type);  // 0x0021da00
    if (type != K_LEVEL_PLATEFORMS) return 1;
    m_unk58 = RwMatrixCreate_Thunk();
    CMatrix34_LoadMatrix(m_unk58, file);
    m_unk5c = RwMatrixCreate_Thunk();
    CMatrix34_LoadMatrix(m_unk5c, file);
    ReadF32LE(file, &m_fUnk60);
    return 1;
}

// 0x00225a40 CKPxFixedJoint_Destroy
void CKPxFixedJoint::Destroy() {
    RwMatrixDestroy_Thunk(m_unk58);  // 0x0023f968
    RwMatrixDestroy_Thunk(m_unk5c);  // 0x0023f968
    KBase488C::Destroy();  // 0x0021d158
}

namespace {

// One of the fixed joint's rows (kind 4) between two points: `armA` / `armB` the arms from each body (or the points
// themselves without a body), the direction from the first point to the second, its length at +0x38 and, above 1e-6,
// the relative speed along it at +0x34 (the row counted). A zero length keeps +0x38 at 0 and counts nothing.
void AddPointRow(CKPxFixedJoint* joint, CKPxBody* body, CKPxBody::Record* row) {
    CVector3 pointA, velocityA;
    if (joint->m_unk1c != nullptr) {
        CKPxBody* a = static_cast<CKPxBody*>(joint->m_unk1c);
        velocityA = pxrows::VelocityAt(a, row->m_vArmA);
        pointA = pxrows::Add(row->m_vArmA, a->m_pWorldMatrix->m_pos);
    } else {
        pointA = row->m_vArmA;
        velocityA = kNullVector;
    }
    CVector3 pointB, velocityB;
    if (joint->m_unk24 != nullptr) {
        CKPxBody* b = static_cast<CKPxBody*>(joint->m_unk24);
        velocityB = pxrows::VelocityAt(b, row->m_vArmB);
        pointB = pxrows::Add(row->m_vArmB, b->m_pWorldMatrix->m_pos);
    } else {
        pointB = row->m_vArmB;
        velocityB = kNullVector;
    }
    row->m_vNormal = pxrows::Sub(pointB, pointA);
    const float length = pxrows::NormaliseRow(row);
    if (length == 0.0f) {
        row->m_fUnk38 = 0.0f;
        return;
    }
    row->m_fUnk38 = length;
    if (!(length > 1e-6f)) return;  // ble
    row->m_fUnk34 = pxrows::Dot(pxrows::Sub(velocityB, velocityA), row->m_vNormal);
    ++body->m_ui16Unk128;
}

// The arm of an angular row: the base arm (`base`, the first row's) plus the length (+0x60) times the frame axis turned
// by the body (or the axis itself without one).
CVector3 AxisArm(IKSerializable* object, const CVector3& axis, float length, const CVector3& base) {
    CVector3 turned = axis;
    if (object != nullptr) Mat4_TransformVectors(static_cast<CKPxBody*>(object)->m_pWorldMatrix, &turned, &axis, 1);
    return CVector3{ppc::fmadds(length, turned.x, base.x), ppc::fmadds(length, turned.y, base.y),
                    ppc::fmadds(length, turned.z, base.z)};
}

}  // namespace

// 0x00225d50 CKPxFixedJoint_vf60 (vt+0x60, Solve): with a body to take the rows (vt+0x5c): a row (kind 4) between the
// two frames' origins (+0x58 / +0x5c positions, turned by each body); unless the flag 0x80000, two more rows that keep
// the frames' right and up axes together (points +0x60 along each axis from the first row's arms).
void CKPxFixedJoint::Solve() {
    CKPxBody* body = WakeAndPickBody();  // vt+0x5c
    if (body == nullptr) return;
    CKPxBody::Record* row = body->NextRecord();
    row->m_unk00 = 4;
    row->m_pBodyA = static_cast<CKPxBody*>(m_unk20);
    row->m_pBodyB = static_cast<CKPxBody*>(m_unk28);
    if (m_unk1c != nullptr) {
        Mat4_TransformVectors(static_cast<CKPxBody*>(m_unk1c)->m_pWorldMatrix, &row->m_vArmA, &m_unk58->m_pos, 1);
    } else {
        row->m_vArmA = m_unk58->m_pos;
    }
    if (m_unk24 != nullptr) {
        Mat4_TransformVectors(static_cast<CKPxBody*>(m_unk24)->m_pWorldMatrix, &row->m_vArmB, &m_unk5c->m_pos, 1);
    } else {
        row->m_vArmB = m_unk5c->m_pos;
    }
    // The original keeps pointers to this row's arms for the next two rows (stale if the block grows in between); the
    // values are copied here.
    const CVector3 baseA = row->m_vArmA;
    const CVector3 baseB = row->m_vArmB;
    AddPointRow(this, body, row);
    if ((m_unk18 & 0x80000) != 0) return;
    row = body->NextRecord();
    row->m_unk00 = 4;
    row->m_pBodyA = static_cast<CKPxBody*>(m_unk20);
    row->m_pBodyB = static_cast<CKPxBody*>(m_unk28);
    row->m_vArmA = AxisArm(m_unk1c, m_unk58->m_right, m_fUnk60, baseA);
    row->m_vArmB = AxisArm(m_unk24, m_unk5c->m_right, m_fUnk60, baseB);
    AddPointRow(this, body, row);
    row = body->NextRecord();
    row->m_unk00 = 4;
    row->m_pBodyA = static_cast<CKPxBody*>(m_unk20);
    row->m_pBodyB = static_cast<CKPxBody*>(m_unk28);
    row->m_vArmA = AxisArm(m_unk1c, m_unk58->m_up, m_fUnk60, baseA);
    row->m_vArmB = AxisArm(m_unk24, m_unk5c->m_up, m_fUnk60, baseB);
    AddPointRow(this, body, row);
}
