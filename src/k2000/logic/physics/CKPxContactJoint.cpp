// CKPxContactJoint.cpp - reconstructed original translation unit 0x220020-0x222068 (GAME_TOC1, main_toc1), 18 functions, 18 live.
// Primary class: CKPxContactJoint  key 0x4d0c  category Logic  size 0x4c  vtable 0xb1ffe8
// Other owners: PxContactPair (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x220020  CKPxContactJoint_Delete
//   [ ] 0x220070  RegisterCKPxContactJointClass
//   [ ] 0x2200e8  _GLOBAL__I_2200e8
//   [ ] 0x2200f8  CKPxContactJoint_Save
//   [x] 0x220120  CKPxContactJoint_RecursiveRegistration  (KBase468C's vf24 0x218068: returns 1, nothing)
//   [x] 0x220148  CKPxContactJoint_Destroy  (inherited: CKPxObject_ClearReferences_BaseNop_maybe)
//   [x] 0x220170  CKPxContactJoint_Construct
//   [x] 0x2201a8  CKPxContactJoint_DeleteArray
//   [x] 0x220248  CKPxContactJoint_DeletingDestructor  (the destructor; delete)
//   [x] 0x220290  CKPxContactJoint_Destructor  (C++ destructor chain: vtable stores only)
//   [x] 0x2202c0  CKPxContactJoint_DestructBody  (C++ destructor chain: vtable stores only)
//   [x] 0x2202f0  CKPxContactJoint_Load
//   [x] 0x2203a8  CKPxContactJoint_Construct_2  (the same as 0x220170 CKPxContactJoint_Construct)
//   [x] 0x2203e0  PxContactPair_SetBodies_maybe  (CKPxContactJoint::SetBodies)
//   [x] 0x220458  CKPxContactJoint_CreateArray
//   [x] 0x220508  CKPxContactJoint_Create
//   [x] 0x220560  CKPxContactJoint_WakeIslandsAndPickBody_maybe  (WakeIslandsAndPickBody)
//   [x] 0x221b40  CKPxContactJoint_EmitContactRecord_maybe  (EmitContactRecord; RunFixedSteps calls it per contact joint)
//
//   [ ] 0x9b4050  CKPxContactJoint_IsKindOfClass  [inline]
//   [ ] 0x9b4078  CKPxContactJoint_GetClassType  [inline]
//   [ ] 0x9b4080  CKPxContactJoint_GetClassID  [inline]
#include "k2000/logic/physics/CKPxContactJoint.h"

#include <cmath>
#include <cstdint>

#include "crt/ppc_ops.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKPxBody.h"
#include "k2000/logic/memory/CKPxContainer.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/Engine.h"
#include "k2000/services/CKSrvPhysics.h"

namespace {

// 0x00c50d64 and 0x00c50d40: the shared vectors the original copies (live (0, 0, 0) and (0, 1, 0)).
const CVector3 kVector3_c50d64 = {0.0f, 0.0f, 0.0f};
const CVector3 kVector3_c50d40 = {0.0f, 1.0f, 0.0f};

}  // namespace

// 0x002202f0 CKPxContactJoint_Load
int32_t CKPxContactJoint::Load(IKFile* file, int32_t type) {
    KBase468C::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    m_unk24 = nullptr;
    m_unk18 = 0;
    m_unk1c = nullptr;
    m_unk2c = kVector3_c50d64;
    m_unk38 = kVector3_c50d40;
    m_unk48 = 0.0f;  // stw 0
    m_unk44 = 0.0f;
    return 1;
}

// 0x002203e0 PxContactPair_SetBodies_maybe
void CKPxContactJoint::SetBodies(CKPxBody* a, CKPxBody* b) {
    m_unk1c = a;
    m_unk20 = nullptr;
    m_unk24 = b;
    m_unk28 = nullptr;
    if (a == nullptr) {
        m_unk28 = b;
        return;
    }
    if (a->m_unk18 == 3) {
        if (b == nullptr) {
            m_unk20 = a;
        } else if (b->m_unk18 == 3) {
            m_unk28 = b;
            m_unk20 = a;
        } else {
            m_unk28 = b;
        }
        return;
    }
    if (b == nullptr || b->m_unk18 == 3) {
        m_unk20 = a;
        return;
    }
    m_unk28 = b;
    m_unk20 = a;
}

// ---- C2.8 port-last Z7 ----


// 0x00220560 CKPxContactJoint_WakeIslandsAndPickBody_maybe: with one body only, that body when it is awake or resting
// (0x14), else none. Two bodies both asleep (no flag 4): both put to sleep for good (unless asleep already or fixed)
// and none returned; else the sleeping one is woken with its island (WakeBodyIsland, inlined in the original). Then the
// two islands are merged (the first's into the second's when it is smaller and the first is not of kind 1) and the
// root of the merged island is returned (the body whose rows take the contact).
CKPxBody* CKPxContactJoint::WakeIslandsAndPickBody() {
    CKPxBody* a = m_unk1c;
    if (a == nullptr) {
        CKPxBody* b = m_unk24;
        return (b->m_ui32Flags & 0x14) != 0 ? b : nullptr;
    }
    CKPxBody* b = m_unk24;
    if (b == nullptr) return (a->m_ui32Flags & 0x14) != 0 ? a : nullptr;
    CKSrvPhysics* physics = static_cast<CKSrvPhysics*>(g_pEngine->m_srvPhysics);
    const uint32_t flagsA = a->m_ui32Flags;
    if ((flagsA & 4) == 0) {
        if ((b->m_ui32Flags & 4) == 0) {
            if ((flagsA & 8) == 0 && (flagsA & 0x20) == 0) physics->PutBodyToSleep(a);
            b = m_unk24;
            if ((b->m_ui32Flags & 8) != 0) return nullptr;
            if ((b->m_ui32Flags & 0x20) != 0) return nullptr;
            physics->PutBodyToSleep(b);
            return nullptr;
        }
        physics->WakeBodyIsland(a);  // 0x009b2480 (inlined)
    } else {
        physics->WakeBodyIsland(b);
    }
    return physics->MergeIslands(m_unk1c, m_unk24);
}

// 0x00221b40 CKPxContactJoint_EmitContactRecord_maybe: for a contact with depth (+0x44 above 0) whose bodies' island has
// a root (WakeIslandsAndPickBody), a constraint row of that body (+0x11c, at its count +0x128, grown by one): the two
// moving bodies, the arms from their positions to the point, the relative velocity at the point; a separating contact
// (along the normal below 0) is dropped. The row's direction is the normal velocity plus the tangential slide scaled by
// min(|slide| / normal speed, the friction +0x48), normalised (the normal itself when it is too short), its length at
// +0x34; the depth over its normal part at +0x38 (dropped below 1e-6 in either), the normal at +0x3c. Only a kept row
// counts.
void CKPxContactJoint::EmitContactRecord() {
    CKPxBody* body = WakeIslandsAndPickBody();  // 0x00220560
    if (body == nullptr) return;
    if (m_unk44 <= 0.0f) return;  // cror lt|eq: NaN goes on
    TVector<CKPxBody::Record, 1>& rows = body->m_vRecords;
    CKPxBody::Record* row;
    if (body->m_ui16Unk128 < rows.m_ui32NbUsedElt) {
        row = &rows.m_pBlock[body->m_ui16Unk128];
    } else {
        if (rows.m_ui32NbElt == rows.m_ui32NbUsedElt) {
            uint32_t capacity = rows.m_ui32NbUsedElt + 1;
            if (capacity == 0) capacity = 1;
            rows.m_pBlock = static_cast<CKPxBody::Record*>(Mem_ReallocAligned16(
                rows.m_pBlock, (capacity * static_cast<uint32_t>(sizeof(CKPxBody::Record))) & ~3u));  // 0x53190
            rows.m_ui32NbElt = capacity;
        }
        row = &rows.m_pBlock[rows.m_ui32NbUsedElt];
        ++rows.m_ui32NbUsedElt;
    }
    row->m_unk00 = 0;
    row->m_pBodyA = m_unk20;
    row->m_pBodyB = m_unk28;
    // The velocity of each body at the point: v + w x arm (none without a body).
    float ax, ay, az;
    if (m_unk1c != nullptr) {
        const CVector3& pos = m_unk1c->m_pWorldMatrix->m_pos;
        const float rz = m_unk2c.z - pos.z;
        const float rx = m_unk2c.x - pos.x;
        const float ry = m_unk2c.y - pos.y;
        row->m_vArmA = {rx, ry, rz};
        const CVector3& w = m_unk1c->m_unkb8;
        const CVector3& v = m_unk1c->m_unka4;
        const float cy = ppc::fmsubs(w.z, rx, rz * w.x);
        const float cz = ppc::fmsubs(ry, w.x, w.y * rx);
        const float cx = ppc::fmsubs(w.y, rz, w.z * ry);
        ay = cy + v.y;
        az = cz + v.z;
        ax = cx + v.x;
    } else {
        row->m_vArmA = m_unk2c;
        az = kVector3_c50d64.z;
        ax = kVector3_c50d64.x;
        ay = kVector3_c50d64.y;
    }
    float bx, by, bz;
    if (m_unk24 != nullptr) {
        const CVector3& pos = m_unk24->m_pWorldMatrix->m_pos;
        const float rz = m_unk2c.z - pos.z;
        const float rx = m_unk2c.x - pos.x;
        const float ry = m_unk2c.y - pos.y;
        row->m_vArmB = {rx, ry, rz};
        const CVector3& w = m_unk24->m_unkb8;
        const CVector3& v = m_unk24->m_unka4;
        const float cy = ppc::fmsubs(w.z, rx, rz * w.x);
        const float cz = ppc::fmsubs(ry, w.x, w.y * rx);
        const float cx = ppc::fmsubs(w.y, rz, w.z * ry);
        by = cy + v.y;
        bz = cz + v.z;
        bx = cx + v.x;
    } else {
        row->m_vArmB = m_unk2c;
        bz = kVector3_c50d64.z;
        bx = kVector3_c50d64.x;
        by = kVector3_c50d64.y;
    }
    const float rx = bx - ax;
    const float ry = by - ay;
    const float rz = bz - az;
    row->m_vNormal = {rx, ry, rz};
    const CVector3 n = m_unk38;
    const float normalSpeed = ppc::fmadds(rz, n.z, ppc::fmadds(rx, n.x, ry * n.y));
    if (normalSpeed < 0.0f) return;  // blt: NaN goes on
    const float negSpeed = -normalSpeed;
    float ty = ppc::fmadds(n.y, negSpeed, ry);
    float tx = ppc::fmadds(n.x, negSpeed, rx);
    float tz = ppc::fmadds(n.z, negSpeed, rz);
    float slide = std::sqrt(ppc::fmadds(tz, tz, ppc::fmadds(tx, tx, ty * ty)));  // Math_Sqrtf 0x10690
    if (slide != 0.0f) {
        const float inverse = 1.0f / slide;
        tz = tz * inverse;
        tx = tx * inverse;
        ty = ty * inverse;
    } else {
        slide = 0.0f;
    }
    row->m_unk4c = {tx, ty, tz};
    float ratio = 0.0f;
    if (normalSpeed > 0.0f) ratio = slide / normalSpeed;  // ble
    float friction = m_unk48;
    if (!(ratio > friction)) friction = ratio;  // bgt keeps +0x48
    const float k = friction * normalSpeed;
    const float dy = ppc::fmadds(k, ty, normalSpeed * n.y);
    const float dx = ppc::fmadds(k, tx, normalSpeed * n.x);
    const float dz = ppc::fmadds(k, tz, normalSpeed * n.z);
    row->m_vNormal = {dx, dy, dz};
    const float length = std::sqrt(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));
    if (length == 0.0f) {
        row->m_fUnk34 = 0.0f;
        row->m_vNormal = m_unk38;
    } else {
        const float inverse = 1.0f / length;
        const float nz = inverse * dz;
        const float nx = inverse * dx;
        const float ny = inverse * dy;
        row->m_vNormal = {nx, ny, nz};
        row->m_fUnk34 = length;
        if (length < 1e-6f) row->m_vNormal = m_unk38;  // blt (0x358637bd)
    }
    const CVector3& d = row->m_vNormal;
    const float along = ppc::fmadds(d.z, m_unk38.z, ppc::fmadds(d.x, m_unk38.x, d.y * m_unk38.y));
    if (along < 1e-6f) return;  // blt: NaN goes on
    const float depth = m_unk44 / along;
    row->m_fUnk38 = depth;
    if (!(std::fabs(depth) > 1e-6f)) return;  // the sign bit cleared in memory; ble: NaN returns
    row->m_unk3c = m_unk38;
    ++body->m_ui16Unk128;
}
