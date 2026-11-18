// CKPxWheelJoint.cpp - reconstructed original translation unit 0x22afd8-0x22c4b8 (GAME_TOC1, main_toc1), 16 functions, 16 live.
// Primary class: CKPxWheelJoint  key 0x534c  category Logic  size 0xb8  vtable 0xb20298
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x22afd8  CKPxWheelJoint_Delete
//   [ ] 0x22b028  RegisterCKPxWheelJointClass
//   [ ] 0x22b0a0  _GLOBAL__I_22b0a0
//   [ ] 0x22b0b0  CKPxWheelJoint_Save
//   [x] 0x22b0d8  CKPxWheelJoint_RecursiveRegistration  (the base's vf24: returns 1, registers nothing)
//   [x] 0x22b100  CKPxWheelJoint_Destroy  (KBase488C's: the anchors freed)
//   [x] 0x22b128  CKPxWheelJoint_Construct  (header)
//   [x] 0x22b160  CKPxWheelJoint_DeleteArray
//   [x] 0x22b200  CKPxWheelJoint_DeletingDestructor  (the destructor; delete)
//   [x] 0x22b248  CKPxWheelJoint_Destructor  (C++ destructor chain: vtable stores only)
//   [x] 0x22b278  CKPxWheelJoint_BaseDestructor  (C++ destructor chain: vtable stores only)
//   [x] 0x22b2a8  CKPxWheelJoint_Construct_2  (the constructor's second C++ variant)
//   [x] 0x22b2e0  CKPxWheelJoint_CreateArray
//   [x] 0x22b390  CKPxWheelJoint_Create
//   [x] 0x22b3e8  CKPxWheelJoint_vf60  (Solve)
//   [x] 0x22c198  CKPxWheelJoint_Load
//
//   [ ] 0x9b4ce0  CKPxWheelJoint_IsKindOfClass  [inline]
//   [ ] 0x9b4d18  CKPxWheelJoint_GetClassType  [inline]
//   [ ] 0x9b4d20  CKPxWheelJoint_GetClassID  [inline]
//   [ ] 0x9b4d28  CKPxWheelJoint_InitFromDesc_maybe  [inline]
//   [ ] 0x9b4e18  CKPxWheelJoint_ExportState  [inline]
#include "k2000/logic/CKPxWheelJoint.h"

#include "k2000/logic/CKPxBody.h"
#include "k2000/misc/Mat4.h"
#include "k2000/misc/PxJointRows.h"

namespace {
const CVector3 kNullVector{0.0f, 0.0f, 0.0f};  // 0x00c50d64
}  // namespace

// 0x0022c198 CKPxWheelJoint_Load
int32_t CKPxWheelJoint::Load(IKFile* file, int32_t type) {
    KBase488C::Load(file, type);  // 0x0021da00
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(&m_unk58), 3);
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(&m_unk64), 3);
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(&m_unk70), 3);
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(&m_unk7c), 3);
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(&m_unk88), 3);
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(&m_unk94), 3);
    ReadF32LE(file, &m_fUnkb4);
    return 1;
}

// 0x0022b3e8 CKPxWheelJoint_vf60 (vt+0x60, Solve): with a body to take the rows (vt+0x5c), the suspension: a row (kind
// 0x200) between the anchors (+0x58 / +0x64) across the suspension axis (+0x70 turned by the first body when +0x2c is
// set, else +0x7c by the second): the distance off the axis at +0x38, the relative speed across it at +0x34; along the
// axis a spring (rest +0xa0, slack +0xa4, stiffness +0xa8, damping +0xb0 opening / +0xac closing) applied as forces and
// torques to the moving bodies; then the axle row (kind 0x200) between points +0xb4 along the axle directions (+0x88 /
// +0x94) from the first row's arms, less the suspension offset, with the relative speed less the first row's slide.
void CKPxWheelJoint::Solve() {
    CKPxBody* body = WakeAndPickBody();  // vt+0x5c
    if (body == nullptr) return;
    CKPxBody::Record* row = body->NextRecord();
    row->m_unk00 = 0x200;
    row->m_pBodyA = static_cast<CKPxBody*>(m_unk20);
    row->m_pBodyB = static_cast<CKPxBody*>(m_unk28);
    CKPxBody* a = static_cast<CKPxBody*>(m_unk1c);
    CKPxBody* b = static_cast<CKPxBody*>(m_unk24);
    CVector3 axle{};  // the stack vector 0x70
    CVector3 axis{};  // 0x7c
    CVector3 pointA, velocityA;
    if (a != nullptr) {
        Mat4_TransformVectors(a->m_pWorldMatrix, &row->m_vArmA, &m_unk58, 1);  // 0x0023f7b0
        pointA = pxrows::Add(row->m_vArmA, a->m_pWorldMatrix->m_pos);
        velocityA = pxrows::VelocityAt(a, row->m_vArmA);
        if (m_unk2c != 0) {
            Mat4_TransformVectors(a->m_pWorldMatrix, &axle, &m_unk88, 1);
            Mat4_TransformVectors(a->m_pWorldMatrix, &axis, &m_unk70, 1);
        }
    } else {
        row->m_vArmA = m_unk58;
        pointA = m_unk58;
        velocityA = kNullVector;
        if (m_unk2c != 0) {
            axle = m_unk88;
            axis = m_unk70;
        }
    }
    CVector3 pointB, velocityB;
    if (b != nullptr) {
        Mat4_TransformVectors(b->m_pWorldMatrix, &row->m_vArmB, &m_unk64, 1);
        pointB = pxrows::Add(row->m_vArmB, b->m_pWorldMatrix->m_pos);
        velocityB = pxrows::VelocityAt(b, row->m_vArmB);
        if (m_unk2c == 0) {
            Mat4_TransformVectors(b->m_pWorldMatrix, &axle, &m_unk94, 1);
            Mat4_TransformVectors(b->m_pWorldMatrix, &axis, &m_unk7c, 1);
        }
    } else {
        row->m_vArmB = m_unk64;
        pointB = m_unk64;
        velocityB = kNullVector;
        if (m_unk2c == 0) {
            axle = m_unk94;
            axis = m_unk7c;
        }
    }
    // The suspension row: the offset across the axis.
    const CVector3 d = pxrows::Sub(pointB, pointA);
    row->m_vNormal = d;
    const float along = ppc::fmadds(axis.z, d.z, ppc::fmadds(d.x, axis.x, axis.y * d.y));
    const CVector3 offset{axis.x * along, axis.y * along, axis.z * along};
    row->m_vNormal = pxrows::Sub(d, offset);
    float length = pxrows::NormaliseRow(row);
    if (length == 0.0f) length = 0.0f;
    const CVector3 slide = pxrows::Sub(velocityB, velocityA);
    row->m_fUnk38 = length;
    const CVector3 n1 = row->m_vNormal;
    const float slideAcross = pxrows::Dot(slide, n1);
    const float slideAlong = ppc::fmadds(slide.z, axis.z, ppc::fmadds(slide.x, axis.x, slide.y * axis.y));
    row->m_fUnk34 = slideAcross;
    const CVector3 armA = row->m_vArmA;  // the original keeps pointers into the block (stale if it grows): copied
    const CVector3 armB = row->m_vArmB;
    if (length > 1e-6f) ++body->m_ui16Unk128;  // ble skips (0x358637bd)
    // The spring along the axis.
    const float stretch = along - m_fUnka0;
    const float slack = m_fUnka4;
    float spring;
    if (stretch > slack) {  // ble
        spring = stretch - slack;
    } else {
        spring = 0.0f;
        if (!(-slack <= stretch)) spring = stretch + slack;  // ble keeps 0
    }
    const float damping = slideAlong > 0.0f ? m_fUnkb0 : m_fUnkac;  // ble takes +0xac
    const float force = ppc::fmadds(spring, m_fUnka8, slideAlong * damping);
    const CVector3 f{force * axis.x, force * axis.y, force * axis.z};
    if (m_unk20 != nullptr) {
        CKPxBody* moving = static_cast<CKPxBody*>(m_unk20);
        moving->m_unk50 = pxrows::Add(f, moving->m_unk50);
        const CVector3 t{ppc::fmsubs(f.z, armA.y, f.y * armA.z), ppc::fmsubs(f.x, armA.z, f.z * armA.x),
                         ppc::fmsubs(f.y, armA.x, f.x * armA.y)};
        moving->m_unk78 = pxrows::Add(t, moving->m_unk78);
    }
    if (m_unk28 != nullptr) {
        CKPxBody* moving = static_cast<CKPxBody*>(m_unk28);
        const CVector3 g{-f.x, -f.y, -f.z};
        moving->m_unk50 = pxrows::Add(g, moving->m_unk50);
        const CVector3 t{ppc::fmsubs(g.z, armB.y, g.y * armB.z), ppc::fmsubs(g.x, armB.z, g.z * armB.x),
                         ppc::fmsubs(g.y, armB.x, g.x * armB.y)};
        moving->m_unk78 = pxrows::Add(t, moving->m_unk78);
    }
    // The axle row.
    row = body->NextRecord();
    row->m_unk00 = 0x200;
    row->m_pBodyA = static_cast<CKPxBody*>(m_unk20);
    row->m_pBodyB = static_cast<CKPxBody*>(m_unk28);
    const float reach = m_fUnkb4;
    CVector3 pointA2, velocityA2, pointB2, velocityB2;
    if (m_unk2c != 0) {
        row->m_vArmA = CVector3{ppc::fmadds(reach, axle.x, armA.x), ppc::fmadds(reach, axle.y, armA.y),
                                ppc::fmadds(reach, axle.z, armA.z)};
        CVector3 turned = m_unk94;
        if (b != nullptr) Mat4_TransformVectors(b->m_pWorldMatrix, &turned, &m_unk94, 1);
        row->m_vArmB = CVector3{ppc::fmadds(reach, turned.x, armB.x), ppc::fmadds(reach, turned.y, armB.y),
                                ppc::fmadds(reach, turned.z, armB.z)};
    } else {
        CVector3 turned = m_unk88;
        if (a != nullptr) Mat4_TransformVectors(a->m_pWorldMatrix, &turned, &m_unk88, 1);
        row->m_vArmA = CVector3{ppc::fmadds(reach, turned.x, armA.x), ppc::fmadds(reach, turned.y, armA.y),
                                ppc::fmadds(reach, turned.z, armA.z)};
        row->m_vArmB = CVector3{ppc::fmadds(reach, axle.x, armB.x), ppc::fmadds(reach, axle.y, armB.y),
                                ppc::fmadds(reach, axle.z, armB.z)};
    }
    if (a != nullptr) {
        pointA2 = pxrows::Add(row->m_vArmA, a->m_pWorldMatrix->m_pos);
        velocityA2 = pxrows::VelocityAt(a, row->m_vArmA);
    } else {
        pointA2 = row->m_vArmA;
        velocityA2 = kNullVector;
    }
    if (b != nullptr) {
        pointB2 = pxrows::Add(row->m_vArmB, b->m_pWorldMatrix->m_pos);
        velocityB2 = pxrows::VelocityAt(b, row->m_vArmB);
    } else {
        pointB2 = row->m_vArmB;
        velocityB2 = kNullVector;
    }
    row->m_vNormal = pxrows::Sub(pxrows::Sub(pointB2, pointA2), offset);
    const float length2 = pxrows::NormaliseRow(row);
    if (length2 == 0.0f) {
        row->m_fUnk38 = 0.0f;
        return;
    }
    row->m_fUnk38 = length2;
    if (!(length2 > 1e-6f)) return;  // ble
    const float c = -slideAcross;
    const CVector3 kept{ppc::fmadds(c, n1.x, slide.x), ppc::fmadds(c, n1.y, slide.y), ppc::fmadds(c, n1.z, slide.z)};
    const CVector3 slide2 = pxrows::Sub(pxrows::Sub(velocityB2, velocityA2), kept);
    row->m_fUnk34 = pxrows::Dot(slide2, row->m_vNormal);
    ++body->m_ui16Unk128;
}
