// CKPxD6Joint.cpp - reconstructed original translation unit 0x222068-0x225828 (GAME_TOC1, main_toc1), 17 functions, 17 live.
// Primary class: CKPxD6Joint  key 0x4b4c  category Logic  size 0x68  vtable 0xb20040
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x222068  CKPxD6Joint_Delete
//   [ ] 0x2220b8  RegisterCKPxD6JointClass
//   [ ] 0x222130  _GLOBAL__I_222130
//   [x] 0x222140  CKPxD6Joint_Load
//   [ ] 0x222280  CKPxD6Joint_Save
//   [x] 0x2222a8  CKPxD6Joint_RecursiveRegistration  (the base's vf24: returns 1, registers nothing)
//   [x] 0x2222d0  CKPxD6Joint_Destroy
//   [x] 0x222320  CKPxD6Joint_DeletingDestructor  (the destructor; delete)
//   [x] 0x222368  CKPxD6Joint_Destructor  (C++ destructor chain: vtable stores only)
//   [x] 0x222398  CKPxD6Joint_BaseDestructor  (C++ destructor chain: vtable stores only)
//   [x] 0x2223c8  CKPxD6Joint_Construct  (header)
//   [x] 0x222400  CKPxD6Joint_Construct_2  (the constructor's second C++ variant)
//   [x] 0x222438  CKPxD6Joint_DeleteArray
//   [x] 0x2224d8  CKPxD6Joint_vf58  (SetDisabled)
//   [x] 0x222758  CKPxD6Joint_Create
//   [x] 0x2227b0  CKPxD6Joint_CreateArray
//   [x] 0x222860  CKPxD6Joint_vf60  (Solve; 0x222860-0x225828, the unit's end: jump-table cases past Ghidra's body)
//
//   [ ] 0x9b4088  CKPxD6Joint_IsKindOfClass  [inline]
//   [ ] 0x9b40c0  CKPxD6Joint_GetClassType  [inline]
//   [ ] 0x9b40c8  CKPxD6Joint_GetClassID  [inline]
//   [ ] 0x9b40d0  CKPxD6Joint_InitFromDesc_maybe  [inline]
//   [ ] 0x9b4290  CKPxD6Joint_ExportState  [inline]
#include "k2000/logic/CKPxD6Joint.h"

#include "k2000/logic/CKPxBody.h"
#include "k2000/misc/Mat4.h"
#include "k2000/misc/PxJointRows.h"

// 0x00222140 CKPxD6Joint_Load
int32_t CKPxD6Joint::Load(IKFile* file, int32_t type) {
    KBase488C::Load(file, type);  // 0x0021da00
    if (type != K_LEVEL_PLATEFORMS) return 1;
    m_unk58 = RwMatrixCreate_Thunk();
    CMatrix34_LoadMatrix(m_unk58, file);
    m_unk5c = RwMatrixCreate_Thunk();
    CMatrix34_LoadMatrix(m_unk5c, file);
    ReadU16LE(file, &m_unk60);
    ReadF32LE(file, &m_fUnk64);
    return 1;
}

// 0x002222d0 CKPxD6Joint_Destroy
void CKPxD6Joint::Destroy() {
    RwMatrixDestroy_Thunk(m_unk58);  // 0x0023f968
    RwMatrixDestroy_Thunk(m_unk5c);  // 0x0023f968
    KBase488C::Destroy();  // 0x0021d158
}

// 0x002224d8 CKPxD6Joint_vf58 (vt+0x58): KBase488C_vf58 0x21f1e8 (called directly), then, enabled: with +0x2c set the
// second body gets the frame +0x58 through the first body's world matrix (+0x58 itself without one), else the first body
// gets +0x5c through the second's.
void CKPxD6Joint::SetDisabled(int32_t disabled) {
    KBase488C::SetDisabled(disabled);  // 0x0021f1e8
    if ((m_unk18 & 0x2000) != 0) return;
    CMatrix34 frame{};
    if (m_unk2c != 0) {
        if (m_unk1c != nullptr) {
            Mat4_Multiply(&frame, m_unk58, static_cast<CKPxBody*>(m_unk1c)->m_pWorldMatrix);  // 0x0023f788
        } else {
            frame = *m_unk58;  // all 16 words
        }
        if (m_unk24 != nullptr) static_cast<CKPxBody*>(m_unk24)->SetWorldMatrix(&frame);  // vt+0x5c
        return;
    }
    if (m_unk24 != nullptr) {
        Mat4_Multiply(&frame, m_unk5c, static_cast<CKPxBody*>(m_unk24)->m_pWorldMatrix);
    } else {
        frame = *m_unk5c;
    }
    if (m_unk1c != nullptr) static_cast<CKPxBody*>(m_unk1c)->SetWorldMatrix(&frame);
}

namespace {

const CVector3 kNullVector{0.0f, 0.0f, 0.0f};  // 0x00c50d64

// The frame axis `k` (0 right, 1 up, 2 at).
const CVector3& FrameAxis(const CMatrix34* frame, int32_t k) {
    return k == 0 ? frame->m_right : (k == 1 ? frame->m_up : frame->m_at);
}

// `local` turned by the body's world matrix, or `local` itself without a body.
CVector3 Turned(CKPxBody* body, const CVector3& local) {
    CVector3 out = local;
    if (body != nullptr) Mat4_TransformVectors(body->m_pWorldMatrix, &out, &local, 1);  // 0x0023f7b0
    return out;
}

// The world point and velocity of an arm: the arm plus the body's position and the body's velocity there; without a
// body the arm itself and no velocity.
void ArmState(CKPxBody* body, const CVector3& arm, CVector3* point, CVector3* velocity) {
    if (body != nullptr) {
        *point = pxrows::Add(arm, body->m_pWorldMatrix->m_pos);
        *velocity = pxrows::VelocityAt(body, arm);
    } else {
        *point = arm;
        *velocity = kNullVector;
    }
}

// base + reach * dir per part (fmadds).
CVector3 Reach(float reach, const CVector3& dir, const CVector3& base) {
    return CVector3{ppc::fmadds(reach, dir.x, base.x), ppc::fmadds(reach, dir.y, base.y),
                    ppc::fmadds(reach, dir.z, base.z)};
}

// s * v per part.
CVector3 Scale(float s, const CVector3& v) { return CVector3{s * v.x, s * v.y, s * v.z}; }

// The angular rows' shared tail (0x222b8c / 0x222e28): the direction = the points' offset less the point row's free
// part (`offset`), normalised, its length at +0x38 (0 for a zero length) and, above 1e-6, the relative speed along it at
// +0x34 (the row counted).
void FinishAngularRow(CKPxBody* body, CKPxBody::Record* row, const CVector3& diff, const CVector3& rel,
                      const CVector3& offset) {
    row->m_vNormal = pxrows::Sub(diff, offset);
    const float length = pxrows::NormaliseRow(row);
    if (length == 0.0f) {
        row->m_fUnk38 = 0.0f;
        return;
    }
    row->m_fUnk38 = length;
    if (!(length > 1e-6f)) return;  // ble (0x358637bd)
    row->m_fUnk34 = pxrows::Dot(rel, row->m_vNormal);
    ++body->m_ui16Unk128;
}

// The point row's record: the angular rows' base arms are read through the block at each use, as the original does
// through its pointers. When the point row is not counted the next row takes the same record (NextRecord), so a later
// row reads the arms an earlier angular row wrote there. (The original's pointers go stale if the block grows; the index
// reads the same bytes, the block being copied.)
const CKPxBody::Record& BaseRecord(const CKPxBody* body, uint32_t first) { return body->m_vRecords.m_pBlock[first]; }

// One angular row (kind 2) that keeps the frames' axis `k` together: the arms `reach` (+0x64) along the axis turned by
// each body (the turned reference axes `axes` on the reference side) from the point row's arms.
void AddAxisRow(CKPxD6Joint* joint, CKPxBody* body, CKPxBody::Record* row, uint32_t first, int32_t k,
                const CVector3* axes, const CVector3& offset, const CVector3& kept) {
    CKPxBody* a = static_cast<CKPxBody*>(joint->m_unk1c);
    CKPxBody* b = static_cast<CKPxBody*>(joint->m_unk24);
    CVector3 dirA, dirB;
    if (joint->m_unk2c != 0) {
        dirA = axes[k];
        dirB = Turned(b, FrameAxis(joint->m_unk5c, k));
    } else {
        dirA = Turned(a, FrameAxis(joint->m_unk58, k));
        dirB = axes[k];
    }
    row->m_vArmA = Reach(joint->m_fUnk64, dirA, BaseRecord(body, first).m_vArmA);
    row->m_vArmB = Reach(joint->m_fUnk64, dirB, BaseRecord(body, first).m_vArmB);
    CVector3 pointA, velocityA, pointB, velocityB;
    ArmState(a, row->m_vArmA, &pointA, &velocityA);
    ArmState(b, row->m_vArmB, &pointB, &velocityB);
    FinishAngularRow(body, row, pxrows::Sub(pointB, pointA), pxrows::Sub(pxrows::Sub(velocityB, velocityA), kept), offset);
}

// The twist row (kind 2) of one locked rotation: on the second body's side (+0x2c set, else the first's) the arm `reach`
// along that body's frame axis `k` (turned); on the other side the same axis less its part along `c` (a turned reference
// axis), scaled to `reach` (unless it is zero); only the relative speed along `c` counts.
void AddTwistRow(CKPxD6Joint* joint, CKPxBody* body, CKPxBody::Record* row, uint32_t first, const CVector3& c,
                 int32_t k, const CVector3& offset, const CVector3& kept) {
    CKPxBody* a = static_cast<CKPxBody*>(joint->m_unk1c);
    CKPxBody* b = static_cast<CKPxBody*>(joint->m_unk24);
    const float reach = joint->m_fUnk64;
    const bool onB = joint->m_unk2c != 0;
    CVector3 fixed, u;
    if (onB) {
        fixed = BaseRecord(body, first).m_vArmA;  // copied first, as the original (the row may be the point row's record)
        u = Turned(b, FrameAxis(joint->m_unk5c, k));
        row->m_vArmB = Reach(reach, u, BaseRecord(body, first).m_vArmB);
    } else {
        fixed = BaseRecord(body, first).m_vArmB;
        u = Turned(a, FrameAxis(joint->m_unk58, k));
        row->m_vArmA = Reach(reach, u, BaseRecord(body, first).m_vArmA);
    }
    // fnmadds(c.z, u.z, fmadds(u.x, c.x, c.y * u.y))
    const float t = -pxrows::Dot(u, c);
    CVector3 p{ppc::fmadds(t, c.x, u.x), ppc::fmadds(t, c.y, u.y), ppc::fmadds(t, c.z, u.z)};
    const float length = pxrows::Length(p);
    if (length != 0.0f) p = Scale(reach / length, p);
    if (onB) {
        row->m_vArmA = pxrows::Add(fixed, p);
    } else {
        row->m_vArmB = pxrows::Add(fixed, p);
    }
    CVector3 pointA, velocityA, pointB, velocityB;
    ArmState(a, row->m_vArmA, &pointA, &velocityA);
    ArmState(b, row->m_vArmB, &pointB, &velocityB);
    const CVector3 rel = pxrows::Sub(pxrows::Sub(velocityB, velocityA), kept);
    const float along = pxrows::Dot(rel, c);
    FinishAngularRow(body, row, pxrows::Sub(pointB, pointA), Scale(along, c), offset);
}

// A new row of kind 2 between the joint's bodies (+0x20 / +0x28).
CKPxBody::Record* NextD6Row(CKPxBody* body, IKSerializable* bodyA, IKSerializable* bodyB) {
    CKPxBody::Record* row = body->NextRecord();
    row->m_unk00 = 2;
    row->m_pBodyA = static_cast<CKPxBody*>(bodyA);
    row->m_pBodyB = static_cast<CKPxBody*>(bodyB);
    return row;
}

}  // namespace

// 0x00222860 CKPxD6Joint_vf60 (vt+0x60, Solve): with a body to take the rows (vt+0x5c): the limit planes' row (vt+0x64);
// a point row (kind 2) between the frames' origins (+0x58 / +0x5c positions, turned by each body) whose free axes (bits
// 0-2 of +0x60 clear; the reference frame +0x58 turned by the first body when +0x2c is set, else +0x5c by the second)
// are taken out; unless the flag 0x80000, the angular rows of the locked rotations (bits 3-5): one axis row for two
// locked rotations (the free one's axis), two (right, up) for three, a twist row for one. The jump tables at 0x222b68 /
// 0x223200 are the two switches.
void CKPxD6Joint::Solve() {
    CKPxBody* body = WakeAndPickBody();  // vt+0x5c
    if (body == nullptr) return;
    AddLimitRow(body);  // vt+0x64
    CKPxBody::Record* row = NextD6Row(body, m_unk20, m_unk28);
    const uint32_t first = static_cast<uint32_t>(row - body->m_vRecords.m_pBlock);
    CKPxBody* a = static_cast<CKPxBody*>(m_unk1c);
    CKPxBody* b = static_cast<CKPxBody*>(m_unk24);
    CVector3 axes[3];  // the stack vectors 0x70 / 0x7c / 0x88: the reference frame's axes
    if (a != nullptr) {
        Mat4_TransformVectors(a->m_pWorldMatrix, &row->m_vArmA, &m_unk58->m_pos, 1);  // 0x0023f7b0
    } else {
        row->m_vArmA = m_unk58->m_pos;
    }
    CVector3 pointA, velocityA;
    ArmState(a, row->m_vArmA, &pointA, &velocityA);
    if (m_unk2c != 0) {
        for (int32_t k = 0; k < 3; ++k) axes[k] = Turned(a, FrameAxis(m_unk58, k));
    }
    if (b != nullptr) {
        Mat4_TransformVectors(b->m_pWorldMatrix, &row->m_vArmB, &m_unk5c->m_pos, 1);
    } else {
        row->m_vArmB = m_unk5c->m_pos;
    }
    CVector3 pointB, velocityB;
    ArmState(b, row->m_vArmB, &pointB, &velocityB);
    if (m_unk2c == 0) {
        for (int32_t k = 0; k < 3; ++k) axes[k] = Turned(b, FrameAxis(m_unk5c, k));
    }
    const CVector3 d = pxrows::Sub(pointB, pointA);
    row->m_vNormal = d;
    const CVector3 rel = pxrows::Sub(velocityB, velocityA);
    // The point row by its locked axes (jump table 0x222b68): `offset` is the free part of the frames' offset and `kept`
    // the relative velocity left to the angular rows.
    CVector3 offset, kept;
    const uint32_t linear = m_unk60 & 7u;
    if (linear == 0) {  // 0x223930: nothing locked
        offset = d;
        row->m_vNormal = kNullVector;
        row->m_fUnk34 = 0.0f;  // stw 0
        row->m_fUnk38 = 0.0f;  // stw 0
        kept = rel;
    } else if (linear == 7) {  // 0x2238c4: all locked
        offset = kNullVector;
        const float length = pxrows::NormaliseRow(row);
        row->m_fUnk38 = length == 0.0f ? 0.0f : length;
        row->m_fUnk34 = pxrows::Dot(rel, row->m_vNormal);
        kept = kNullVector;
    } else {
        if (linear == 1 || linear == 2 || linear == 4) {  // 0x223854 / 0x22388c / 0x2237d0: one locked axis
            const CVector3& axis = axes[linear == 1 ? 0 : (linear == 2 ? 1 : 2)];
            const float along = pxrows::Dot(d, axis);
            const CVector3 locked = Scale(along, axis);
            row->m_vNormal = locked;
            const float length = pxrows::NormaliseRow(row);
            row->m_fUnk38 = length == 0.0f ? 0.0f : length;
            offset = pxrows::Sub(d, locked);
        } else {  // 0x2238a8 / 0x223724 / 0x223870 (6 / 5 / 3): one free axis
            const CVector3& axis = axes[linear == 6 ? 0 : (linear == 5 ? 1 : 2)];
            const float along = pxrows::Dot(d, axis);
            offset = Scale(along, axis);
            row->m_vNormal = pxrows::Sub(d, offset);
            const float length = pxrows::NormaliseRow(row);
            row->m_fUnk38 = length == 0.0f ? 0.0f : length;
        }
        const CVector3 n = row->m_vNormal;
        const float speed = pxrows::Dot(rel, n);
        row->m_fUnk34 = speed;
        const float c = -speed;
        kept = CVector3{ppc::fmadds(c, n.x, rel.x), ppc::fmadds(c, n.y, rel.y), ppc::fmadds(c, n.z, rel.z)};
    }
    if (row->m_fUnk38 > 1e-6f) ++body->m_ui16Unk128;  // 0x223170 (ble skips)
    if ((m_unk18 & 0x80000) != 0) return;
    // The angular rows (jump table 0x223200 by bits 3-5); the record is taken even with none.
    row = NextD6Row(body, m_unk20, m_unk28);
    const uint16_t mode = m_unk60;
    switch ((mode >> 3) & 7u) {
    case 0:
        return;
    case 7:  // 0x2244d4: the right then the up axis rows
        AddAxisRow(this, body, row, first, 0, axes, offset, kept);
        row = NextD6Row(body, m_unk20, m_unk28);
        AddAxisRow(this, body, row, first, 1, axes, offset, kept);
        return;
    case 6:  // 0x223974
        AddAxisRow(this, body, row, first, 0, axes, offset, kept);
        return;
    case 5:  // 0x223b4c
        AddAxisRow(this, body, row, first, 1, axes, offset, kept);
        return;
    case 3:  // 0x223d2c
        AddAxisRow(this, body, row, first, 2, axes, offset, kept);
        return;
    case 1:  // 0x223e18
        if ((mode & 0x80) == 0 && (mode & 0x100) != 0) {
            AddTwistRow(this, body, row, first, axes[2], 1, offset, kept);
        } else {
            AddTwistRow(this, body, row, first, axes[1], 2, offset, kept);
        }
        return;
    case 2:  // 0x2242e0
        if ((mode & 0x40) == 0 && (mode & 0x100) != 0) {
            AddTwistRow(this, body, row, first, axes[2], 0, offset, kept);
        } else {
            AddTwistRow(this, body, row, first, axes[0], 2, offset, kept);
        }
        return;
    default:  // 4: 0x2240e4
        if ((mode & 0x80) == 0 && (mode & 0x40) != 0) {
            AddTwistRow(this, body, row, first, axes[0], 1, offset, kept);
        } else {
            AddTwistRow(this, body, row, first, axes[1], 0, offset, kept);
        }
        return;
    }
}

