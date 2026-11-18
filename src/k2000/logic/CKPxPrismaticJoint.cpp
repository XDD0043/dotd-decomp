// CKPxPrismaticJoint.cpp - reconstructed original translation unit 0x2296d0-0x22afd8 (GAME_TOC1, main_toc1), 16 functions, 16 live.
// Primary class: CKPxPrismaticJoint  key 0x52cc  category Logic  size 0xa4  vtable 0xb20220
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x2296d0  CKPxPrismaticJoint_Delete
//   [ ] 0x229720  RegisterCKPxPrismaticJointClass
//   [ ] 0x229798  _GLOBAL__I_229798
//   [ ] 0x2297a8  CKPxPrismaticJoint_Save
//   [x] 0x2297d0  CKPxPrismaticJoint_RecursiveRegistration  (the base's vf24: returns 1, registers nothing)
//   [x] 0x2297f8  CKPxPrismaticJoint_Destroy  (KBase488C's: the anchors freed)
//   [x] 0x229820  CKPxPrismaticJoint_Construct  (header)
//   [x] 0x229858  CKPxPrismaticJoint_DeleteArray
//   [x] 0x2298f8  CKPxPrismaticJoint_DeletingDestructor  (the destructor; delete)
//   [x] 0x229940  CKPxPrismaticJoint_Destructor  (C++ destructor chain: vtable stores only)
//   [x] 0x229970  CKPxPrismaticJoint_BaseDestructor  (C++ destructor chain: vtable stores only)
//   [x] 0x2299a0  CKPxPrismaticJoint_Construct_2  (the constructor's second C++ variant)
//   [x] 0x2299d8  CKPxPrismaticJoint_CreateArray
//   [x] 0x229a88  CKPxPrismaticJoint_Create
//   [x] 0x229ae0  CKPxPrismaticJoint_Load
//   [x] 0x229e00  CKPxPrismaticJoint_vf60  (Solve)
//
//   [ ] 0x9b4ab8  CKPxPrismaticJoint_IsKindOfClass  [inline]
//   [ ] 0x9b4af0  CKPxPrismaticJoint_GetClassType  [inline]
//   [ ] 0x9b4af8  CKPxPrismaticJoint_GetClassID  [inline]
//   [ ] 0x9b4b00  CKPxPrismaticJoint_InitFromDesc_maybe  [inline]
//   [ ] 0x9b4bf0  CKPxPrismaticJoint_ExportState  [inline]
#include "k2000/logic/CKPxPrismaticJoint.h"

#include "k2000/logic/CKPxBody.h"
#include "k2000/misc/Mat4.h"
#include "k2000/misc/PxJointRows.h"

namespace {
const CVector3 kNullVector{0.0f, 0.0f, 0.0f};  // 0x00c50d64
}  // namespace

// 0x00229ae0 CKPxPrismaticJoint_Load
int32_t CKPxPrismaticJoint::Load(IKFile* file, int32_t type) {
    KBase488C::Load(file, type);  // 0x0021da00
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(&m_unk58), 3);
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(&m_unk64), 3);
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(&m_unk70), 3);
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(&m_unk7c), 3);
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(&m_unk88), 3);
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(&m_unk94), 3);
    ReadF32LE(file, &m_fUnka0);
    return 1;
}

namespace {

// One of the prismatic joint's two lock rows (kind 0x20): the arms `reach` (+0xa0) along a direction from the first row's
// arms (`dirA` / `dirB`: the joint frame's direction turned by its own body), the offset less the slide axis part
// (`offset`), its length at +0x38 and, above 1e-6, the relative speed less the first row's kept part at +0x34. A zero
// length leaves +0x38 0. Returns whether the length was not zero.
bool AddLockRow(CKPxPrismaticJoint* joint, CKPxBody* body, const CVector3& dirA, const CVector3& dirB, const CVector3& armA,
                const CVector3& armB, const CVector3& offset, const CVector3& kept) {
    CKPxBody::Record* row = body->NextRecord();
    row->m_unk00 = 0x20;
    row->m_pBodyA = static_cast<CKPxBody*>(joint->m_unk20);
    row->m_pBodyB = static_cast<CKPxBody*>(joint->m_unk28);
    const float reach = joint->m_fUnka0;
    row->m_vArmA = CVector3{ppc::fmadds(reach, dirA.x, armA.x), ppc::fmadds(reach, dirA.y, armA.y),
                            ppc::fmadds(reach, dirA.z, armA.z)};
    row->m_vArmB = CVector3{ppc::fmadds(reach, dirB.x, armB.x), ppc::fmadds(reach, dirB.y, armB.y),
                            ppc::fmadds(reach, dirB.z, armB.z)};
    CKPxBody* a = static_cast<CKPxBody*>(joint->m_unk1c);
    CKPxBody* b = static_cast<CKPxBody*>(joint->m_unk24);
    CVector3 pointA = row->m_vArmA;
    CVector3 velocityA = kNullVector;
    if (a != nullptr) {
        pointA = pxrows::Add(row->m_vArmA, a->m_pWorldMatrix->m_pos);
        velocityA = pxrows::VelocityAt(a, row->m_vArmA);
    }
    CVector3 pointB = row->m_vArmB;
    CVector3 velocityB = kNullVector;
    if (b != nullptr) {
        pointB = pxrows::Add(row->m_vArmB, b->m_pWorldMatrix->m_pos);
        velocityB = pxrows::VelocityAt(b, row->m_vArmB);
    }
    row->m_vNormal = pxrows::Sub(pxrows::Sub(pointB, pointA), offset);
    const float length = pxrows::NormaliseRow(row);
    if (length == 0.0f) {
        row->m_fUnk38 = 0.0f;
        return false;
    }
    row->m_fUnk38 = length;
    if (!(length > 1e-6f)) return true;  // ble
    const CVector3 slide = pxrows::Sub(pxrows::Sub(velocityB, velocityA), kept);
    row->m_fUnk34 = pxrows::Dot(slide, row->m_vNormal);
    ++body->m_ui16Unk128;
    return true;
}

// `local` turned by the body's world matrix, or `local` itself without a body.
CVector3 Turned(CKPxBody* body, const CVector3& local) {
    CVector3 out = local;
    if (body != nullptr) Mat4_TransformVectors(body->m_pWorldMatrix, &out, &local, 1);  // 0x0023f7b0
    return out;
}

}  // namespace

// 0x00229e00 CKPxPrismaticJoint_vf60 (vt+0x60, Solve): with a body to take the rows (vt+0x5c): a row (kind 0x20)
// between the anchors (+0x58 / +0x64) across the slide axis (+0x70 turned by the first body when +0x2c is set, else +0x7c
// by the second): its length at +0x38, the relative speed across at +0x34; then two lock rows from points +0xa0 along the
// frame's second direction (+0x88 / +0x94) and along the slide axis (+0x70 / +0x7c), the slide part taken out.
void CKPxPrismaticJoint::Solve() {
    CKPxBody* body = WakeAndPickBody();  // vt+0x5c
    if (body == nullptr) return;
    CKPxBody::Record* row = body->NextRecord();
    row->m_unk00 = 0x20;
    row->m_pBodyA = static_cast<CKPxBody*>(m_unk20);
    row->m_pBodyB = static_cast<CKPxBody*>(m_unk28);
    CKPxBody* a = static_cast<CKPxBody*>(m_unk1c);
    CKPxBody* b = static_cast<CKPxBody*>(m_unk24);
    CVector3 side{};  // the stack vector 0x70
    CVector3 axis{};  // 0x7c
    CVector3 pointA, velocityA;
    if (a != nullptr) {
        Mat4_TransformVectors(a->m_pWorldMatrix, &row->m_vArmA, &m_unk58, 1);  // 0x0023f7b0
        pointA = pxrows::Add(row->m_vArmA, a->m_pWorldMatrix->m_pos);
        velocityA = pxrows::VelocityAt(a, row->m_vArmA);
        if (m_unk2c != 0) {
            Mat4_TransformVectors(a->m_pWorldMatrix, &side, &m_unk88, 1);
            Mat4_TransformVectors(a->m_pWorldMatrix, &axis, &m_unk70, 1);
        }
    } else {
        row->m_vArmA = m_unk58;
        pointA = m_unk58;
        velocityA = kNullVector;
        if (m_unk2c != 0) {
            side = m_unk88;
            axis = m_unk70;
        }
    }
    CVector3 pointB, velocityB;
    if (b != nullptr) {
        Mat4_TransformVectors(b->m_pWorldMatrix, &row->m_vArmB, &m_unk64, 1);
        pointB = pxrows::Add(row->m_vArmB, b->m_pWorldMatrix->m_pos);
        velocityB = pxrows::VelocityAt(b, row->m_vArmB);
        if (m_unk2c == 0) {
            Mat4_TransformVectors(b->m_pWorldMatrix, &side, &m_unk94, 1);
            Mat4_TransformVectors(b->m_pWorldMatrix, &axis, &m_unk7c, 1);
        }
    } else {
        row->m_vArmB = m_unk64;
        pointB = m_unk64;
        velocityB = kNullVector;
        if (m_unk2c == 0) {
            side = m_unk94;
            axis = m_unk7c;
        }
    }
    const CVector3 d = pxrows::Sub(pointB, pointA);
    row->m_vNormal = d;
    const float along = ppc::fmadds(axis.z, d.z, ppc::fmadds(d.x, axis.x, axis.y * d.y));
    const CVector3 offset{axis.x * along, axis.y * along, axis.z * along};
    row->m_vNormal = pxrows::Sub(d, offset);
    const float length = pxrows::NormaliseRow(row);
    row->m_fUnk38 = length;
    const CVector3 slide = pxrows::Sub(velocityB, velocityA);
    const float across = pxrows::Dot(slide, row->m_vNormal);
    row->m_fUnk34 = across;
    const float c = -across;
    const CVector3 n1 = row->m_vNormal;
    const CVector3 kept{ppc::fmadds(c, n1.x, slide.x), ppc::fmadds(c, n1.y, slide.y), ppc::fmadds(c, n1.z, slide.z)};
    const CVector3 armA = row->m_vArmA;  // the original keeps pointers into the block (stale if it grows): copied
    const CVector3 armB = row->m_vArmB;
    if (length > 1e-6f) ++body->m_ui16Unk128;  // ble skips (0x358637bd)
    if (m_unk2c != 0) {
        AddLockRow(this, body, side, Turned(b, m_unk94), armA, armB, offset, kept);
        if (!AddLockRow(this, body, axis, Turned(b, m_unk7c), armA, armB, offset, kept)) return;
    } else {
        AddLockRow(this, body, Turned(a, m_unk88), side, armA, armB, offset, kept);
        if (!AddLockRow(this, body, Turned(a, m_unk70), axis, armA, armB, offset, kept)) return;
    }
}
