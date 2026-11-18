// Reconstructed original translation unit: 0x21d108-0x220020 (GAME_TOC1, main_toc1), 13 functions, 12 live.
// Primary owner: CKPxJoint (not a registered class)
// Other owners: KBase488C (3)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x21d108  CKPxJoint_488c_maybe_vf28  (Save: KBase468C_vf28, then 1; KBase488C.h inherits it)
//   [x] 0x21d130  CKPxJoint_488c_maybe_vf24  (RecursiveRegistration: KBase468C_vf24, then 1; KBase488C.h inherits it)
//   [x] 0x21d158  CKPxJoint_488c_maybe_ClearReferences  (KBase488C::Destroy, KBase488C.h)
//   [x] 0x21d1c0  CKPxJoint_488c_maybe_ConstructBase  (KBase488C(), KBase488C.h)
//   [x] 0x21d220  CKPxJoint_488c_maybe_DeletingDestructor  (~KBase488C, KBase488C.h; delete)
//   [ ] 0x21d280  CKPxJoint_488c_maybe_SetBodies_maybe  [dead]
//   [x] 0x21d2f8  CKPxJoint_488c_maybe_ConstructBase_2  (the same as 0x21d1c0: KBase488C(), KBase488C.h)
//   [x] 0x21d358  KBase488C_vf64  (AddLimitRow)
//   [x] 0x21d950  CKPxJoint_488c_maybe_Destructor  (~KBase488C, KBase488C.h)
//   [x] 0x21d9a8  CKPxJoint_488c_maybe_BaseDestructor  (~KBase488C, KBase488C.h)
//   [x] 0x21da00  CKPxJoint_488c_maybe_Load  (KBase488C::Load, KBase488C.h)
//   [x] 0x21df28  KBase488C_vf5C  (WakeAndPickBody)
//   [x] 0x21f1e8  KBase488C_vf58  (SetDisabled)
//
//   [ ] 0x9b3fc0  CKPxJoint_488c_maybe_vf8  [inline]
//   [ ] 0x9b3fe8  CKPxJoint_488c_maybe_vf14  [inline]
//   [ ] 0x9b3ff0  CKPxJoint_488c_maybe_vf18  [inline]
//   [ ] 0x9b3ff8  KStub_Nop_9b3ff8  [inline]
//   [ ] 0x9b4000  CKPxJoint_488c_maybe_vf50  [inline]
//   [ ] 0x9b4028  CKPxJoint_488c_maybe_vf54  [inline]
//
// C2.8 port-last Z7: the base's solver slots (declared in KBase488C.h).
#include "k2000/misc/KBase488C.h"

#include <cstdint>

#include "crt/ppc_ops.h"
#include "k2000/logic/CKPxBody.h"
#include "k2000/logic/memory/CKPxContainer.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/Mat4.h"
#include "k2000/services/CKSrvPhysics.h"

namespace {

const CVector3 kNullVector{0.0f, 0.0f, 0.0f};  // 0x00c50d64 (TOC1 -0xacc)

CKSrvPhysics* SrvPhysics() { return static_cast<CKSrvPhysics*>(g_pEngine->m_srvPhysics); }
CKPxBody* Body(IKSerializable* object) { return static_cast<CKPxBody*>(object); }

}  // namespace

// 0x0021f1e8 KBase488C_vf58 (vt+0x58): `disabled` sets the flag 0x2000 (else it is cleared). An enabled joint not yet in
// the joint container (0x4000 clear) is marked, put in the container (+0x54) when in none, and its two bodies woken with
// their islands (WakeBodyIsland, inlined); a disabled one in it is marked out and unlinked from the container +0x54.
void KBase488C::SetDisabled(int32_t disabled) {
    if (disabled != 0) {
        m_unk18 |= 0x2000;
    } else {
        m_unk18 &= ~0x2000u;
    }
    CKSrvPhysics* physics = SrvPhysics();
    if ((m_unk18 & 0x2000) == 0) {
        if ((m_unk18 & 0x4000) != 0) return;
        m_unk18 |= 0x4000;
        if (m_unk08 == nullptr) static_cast<CKPxContainer*>(physics->m_unk54)->PushFront(this);
        if (m_unk1c != nullptr) physics->WakeBodyIsland(Body(m_unk1c));
        if (m_unk24 != nullptr) physics->WakeBodyIsland(Body(m_unk24));
        return;
    }
    if ((m_unk18 & 0x4000) == 0) return;
    m_unk18 &= ~0x4000u;
    if (m_unk08 != nullptr) CKPxContainer::Unlink(static_cast<CKPxContainer*>(physics->m_unk54), this);
}

// 0x0021df28 KBase488C_vf5C (vt+0x5c): an enabled joint's body that takes its rows: with one body, that body when it is
// awake or resting (0x14); both asleep: both put to sleep for good and the joint taken out of the joint container (none
// returned); else the sleeping one woken with its island and the two islands merged (CKSrvPhysics::MergeIslands).
CKPxBody* KBase488C::WakeAndPickBody() {
    if ((m_unk18 & 0x2000) != 0) return nullptr;
    CKPxBody* a = Body(m_unk1c);
    if (a == nullptr) {
        CKPxBody* b = Body(m_unk24);
        return (b->m_ui32Flags & 0x14) != 0 ? b : nullptr;
    }
    CKPxBody* b = Body(m_unk24);
    if (b == nullptr) return (a->m_ui32Flags & 0x14) != 0 ? a : nullptr;
    CKSrvPhysics* physics = SrvPhysics();
    const uint32_t flagsA = a->m_ui32Flags;
    if ((flagsA & 4) == 0) {
        if ((b->m_ui32Flags & 4) == 0) {
            if ((flagsA & 8) == 0 && (flagsA & 0x20) == 0) physics->PutBodyToSleep(a);
            b = Body(m_unk24);
            const uint32_t flagsB = b->m_ui32Flags;
            if ((flagsB & 8) == 0 && (flagsB & 0x20) == 0) physics->PutBodyToSleep(b);
            if ((m_unk18 & 0x4000) != 0) {
                m_unk18 &= ~0x4000u;
                if (m_unk08 != nullptr) CKPxContainer::Unlink(static_cast<CKPxContainer*>(physics->m_unk54), this);
            }
            return nullptr;
        }
        physics->WakeBodyIsland(a);  // 0x009b2480 (inlined)
    } else {
        physics->WakeBodyIsland(b);
    }
    return physics->MergeIslands(Body(m_unk1c), Body(m_unk24));
}

// 0x0021d358 KBase488C_vf64 (vt+0x64): the limit planes (the anchors: a normal and an offset each), when the joint has
// some and the flag 0x400: the anchor point (+0x44) in world space through one body (the second when +0x2c is set, else
// the first) and in the other's frame; the plane it is deepest behind (below 0) gives a row of `body` (kind 0x400): the
// two moving bodies, the arms, the plane's normal turned to world space (negated through the first body when +0x2c is
// set), the relative normal speed at +0x34 (a separating one drops the row) and the depth at +0x38.
void KBase488C::AddLimitRow(CKPxBody* body) {
    if (static_cast<uint16_t>(m_anchors.m_ui32NbUsedElt) == 0) return;
    if ((m_unk18 & 0x400) == 0) return;
    CKPxBody::Record* row = body->NextRecord();
    row->m_unk00 = 0x400;
    row->m_pBodyA = Body(m_unk20);
    row->m_pBodyB = Body(m_unk28);
    CVector3 point;
    CVector3 local;
    if (m_unk2c != 0) {
        if (m_unk24 != nullptr) {
            Mat4_TransformPoints(Body(m_unk24)->m_pWorldMatrix, &point, &m_unk44, 1);  // 0x0023f7e8
        } else {
            point = m_unk44;
        }
        if (m_unk1c != nullptr) {
            Mat4_InverseTransformPoints(Body(m_unk1c)->m_pWorldMatrix, &local, &point, 1);  // 0x002405b0
        } else {
            local = point;
        }
    } else {
        if (m_unk1c != nullptr) {
            Mat4_TransformPoints(Body(m_unk1c)->m_pWorldMatrix, &point, &m_unk44, 1);
        } else {
            point = m_unk44;
        }
        if (m_unk24 != nullptr) {
            Mat4_InverseTransformPoints(Body(m_unk24)->m_pWorldMatrix, &local, &point, 1);
        } else {
            local = point;
        }
    }
    float deepest = 0.0f;
    CVector3 normal = kNullVector;
    for (uint32_t i = 0; i < static_cast<uint16_t>(m_anchors.m_ui32NbUsedElt); ++i) {
        const SAnchor& plane = m_anchors.m_pBlock[i];
        const CVector3& n = plane.m_vNormal;
        const float d = ppc::fmadds(local.z, n.z, ppc::fmadds(local.x, n.x, local.y * n.y)) + plane.m_fOffset;
        if (!(d < deepest)) continue;  // bge: NaN skips
        CVector3 copy = n;
        if (m_unk2c != 0) {
            const CVector3 negated{-n.x, -n.y, -n.z};
            deepest = d;
            if (m_unk1c != nullptr) {
                Mat4_TransformVectors(Body(m_unk1c)->m_pWorldMatrix, &normal, &negated, 1);  // 0x0023f7b0
            } else {
                normal = n;  // BUG(original): not negated without a first body
            }
        } else {
            deepest = d;
            if (m_unk24 != nullptr) {
                Mat4_TransformVectors(Body(m_unk24)->m_pWorldMatrix, &normal, &copy, 1);
            } else {
                normal = n;
            }
        }
    }
    if (normal.x == kNullVector.x && normal.y == kNullVector.y && normal.z == kNullVector.z) return;
    float ax, ay, az;
    if (m_unk1c != nullptr) {
        CKPxBody* a = Body(m_unk1c);
        const CVector3& pos = a->m_pWorldMatrix->m_pos;
        const float rz = point.z - pos.z;
        const float rx = point.x - pos.x;
        const float ry = point.y - pos.y;
        row->m_vArmA = {rx, ry, rz};
        const CVector3& w = a->m_unkb8;
        const CVector3& v = a->m_unka4;
        const float cy = ppc::fmsubs(w.z, rx, rz * w.x);
        const float cz = ppc::fmsubs(ry, w.x, w.y * rx);
        const float cx = ppc::fmsubs(w.y, rz, w.z * ry);
        ay = cy + v.y;
        az = cz + v.z;
        ax = cx + v.x;
    } else {
        row->m_vArmA = point;
        ax = kNullVector.x;
        ay = kNullVector.y;
        az = kNullVector.z;
    }
    float bx, by, bz;
    if (m_unk24 != nullptr) {
        CKPxBody* b = Body(m_unk24);
        const CVector3& pos = b->m_pWorldMatrix->m_pos;
        const float rz = point.z - pos.z;
        const float rx = point.x - pos.x;
        const float ry = point.y - pos.y;
        row->m_vArmB = {rx, ry, rz};
        const CVector3& w = b->m_unkb8;
        const CVector3& v = b->m_unka4;
        const float cy = ppc::fmsubs(w.z, rx, rz * w.x);
        const float cz = ppc::fmsubs(ry, w.x, w.y * rx);
        const float cx = ppc::fmsubs(w.y, rz, w.z * ry);
        bz = cz + v.z;
        bx = cx + v.x;
        by = cy + v.y;
    } else {
        row->m_vArmB = point;
        bz = kNullVector.z;
        bx = kNullVector.x;
        by = kNullVector.y;
    }
    const float ry = by - ay;
    const float rx = bx - ax;
    const float rz = bz - az;
    row->m_vNormal = {rx, ry, rz};
    const float speed = ppc::fmadds(rz, normal.z, ppc::fmadds(rx, normal.x, ry * normal.y));
    row->m_fUnk34 = speed;
    if (speed < 0.0f) return;  // blt: NaN goes on
    row->m_vNormal = normal;
    row->m_fUnk38 = -deepest;
    ++body->m_ui16Unk128;
}
