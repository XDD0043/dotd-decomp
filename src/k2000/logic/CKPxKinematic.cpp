// Reconstructed original translation unit: 0x21ae38-0x21cb38 (GAME_TOC1, main_toc1), 19 functions, 19 live.
// Primary class: CKPxKinematic  key 0x580c  category Logic  size 0x12c  vtable 0xb1fe90
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x21ae38  CKPxKinematic_Delete  (DOTD_DECLARE_FACTORIES)
//   [x] 0x21ae88  CKPxKinematic_ApplyTranslationAxisConstraint_maybe
//   [x] 0x21b1c0  CKPxKinematic_ApplyRotationAxisConstraint_maybe
//   [ ] 0x21b5a0  RegisterCKPxKinematicClass
//   [ ] 0x21b618  _GLOBAL__I_21b618
//   [x] 0x21b628  CKPxKinematic_Load
//   [ ] 0x21b6c0  CKPxKinematic_Save
//   [x] 0x21b6e8  CKPxKinematic_RecursiveRegistration  (RecursiveRegistration: the header)
//   [x] 0x21b710  CKPxKinematic_Destroy  (Destroy: the header)
//   [x] 0x21b738  CKPxKinematic_DeletingDestructor  (the destructor, then delete)
//   [x] 0x21b780  CKPxKinematic_Destructor  (the destructor)
//   [x] 0x21b7b0  CKPxKinematic_BaseDestructor  (the destructor)
//   [x] 0x21b7e0  CKPxKinematic_Construct  (the constructor)
//   [x] 0x21b818  CKPxKinematic_Construct_2  (the constructor)
//   [x] 0x21b850  CKPxKinematic_DeleteArray  (DOTD_DECLARE_FACTORIES)
//   [x] 0x21b8f0  CKPxKinematic_CreateArray  (DOTD_DECLARE_FACTORIES)
//   [x] 0x21b9a0  CKPxKinematic_Create  (DOTD_DECLARE_FACTORIES: the constructor)
//   [x] 0x21b9f8  CKPxKinematic_Integrate_maybe  (Integrate: CKPxBody::IntegrateCommon with the kinematic's limits and locks)
//   [x] 0x21c568  CKPxKinematic_ComputeDriveVelocities_maybe  (ComputeDriveVelocities)
//
//   [x] 0x9b3808  CKPxKinematic_IsKindOfClass  [inline]  (the header)
//   [x] 0x9b3840  CKPxKinematic_GetClassType  [inline]  (DOTD_CLASS_KEY)
//   [x] 0x9b3848  CKPxKinematic_GetClassID  [inline]  (DOTD_CLASS_KEY)
//   [x] 0x9b3850  CKPxKinematic_ExportState  [inline]  (ExportState)
//   [x] 0x9b3b10  CKPxKinematic_CreateRuntimeState_maybe  [inline]  (CreateRuntimeState)
//   [x] 0x9b3c60  CKPxKinematic_InitFromDesc_maybe  [inline]  (InitFromDesc)
//   [x] 0x9b3ee0  CKPxKinematic_Step_maybe  [inline]  (Step)
//
// C2.8 port-final F03: the class (CKPxKinematic.h), its Load, construction and the axis locks. C2.8 port-last Z7: the
// solver (Integrate 0x21b9f8, ComputeDriveVelocities 0x21c568, the inline Export / Init / Step slots).
#include "k2000/logic/CKPxKinematic.h"

#include <cmath>

#include "Renderware/rwcore/RwCamera.h"
#include "crt/ppc_ops.h"
#include "k2000/math/Quat.h"
#include "k2000/misc/Mat4.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/io/IKFile.h"

namespace {

const CVector3 kNullVector{0.0f, 0.0f, 0.0f};  // 0x00c50d64 (TOC1 -0xb80)

// The part along the unit axis n taken out (fmadds(n.x, v.x, n.y * v.y), fnmadds with n.z, then fmadds back).
void RemoveAlong(const CVector3& n, CVector3* v) {
    const float d = ppc::fnmadds(n.z, v->z, ppc::fmadds(n.x, v->x, n.y * v->y));
    const float x = ppc::fmadds(n.x, d, v->x);
    const float y = ppc::fmadds(d, n.y, v->y);
    const float z = ppc::fmadds(d, n.z, v->z);
    v->x = x;
    v->y = y;
    v->z = z;
}

// Only the part along the unit axis n kept.
void KeepAlong(const CVector3& n, CVector3* v) {
    const float d = ppc::fmadds(n.z, v->z, ppc::fmadds(n.x, v->x, n.y * v->y));
    v->x = n.x * d;
    v->y = d * n.y;
    v->z = d * n.z;
}

// The lock of both constraints: `lock` 1..7 (the field shifted down) on the three vectors.
void ApplyLock(const CMatrix34* m, uint32_t lock, CVector3* a, CVector3* b, CVector3* c) {
    switch (lock) {
        case 1:
            RemoveAlong(m->m_right, a);
            RemoveAlong(m->m_right, b);
            RemoveAlong(m->m_right, c);
            return;
        case 2:
            RemoveAlong(m->m_up, a);
            RemoveAlong(m->m_up, b);
            RemoveAlong(m->m_up, c);
            return;
        case 3:
            KeepAlong(m->m_at, a);
            KeepAlong(m->m_at, b);
            KeepAlong(m->m_at, c);
            return;
        case 4:
            RemoveAlong(m->m_at, a);
            RemoveAlong(m->m_at, b);
            RemoveAlong(m->m_at, c);
            return;
        case 5:
            KeepAlong(m->m_up, a);
            KeepAlong(m->m_up, b);
            KeepAlong(m->m_up, c);
            return;
        case 6:
            KeepAlong(m->m_right, a);
            KeepAlong(m->m_right, b);
            KeepAlong(m->m_right, c);
            return;
        case 7:
            *a = kNullVector;
            *b = kNullVector;
            *c = kNullVector;
            return;
        default:
            return;
    }
}

}  // namespace

CKPxKinematic::CKPxKinematic() {}
CKPxKinematic::~CKPxKinematic() {}

int32_t CKPxKinematic::Load(IKFile* file, int32_t type) {
    CKPxBody::Load(file, type);  // 0x0021a298
    if (type == 0) ReadU8(file, &m_ui8Unk12b);
    return 1;
}

void CKPxKinematic::CreateRuntimeState() { m_pDesc = new CKPxKinematicDesc; }  // OperatorNew(0x6c)

void CKPxKinematic::ApplyTranslationAxisConstraint() {
    ApplyLock(m_pWorldMatrix, m_ui8Unk12b & 7u, &m_unkd8, &m_unk6c, &m_unka4);  // jump table 0x21aeb8
}

void CKPxKinematic::ApplyRotationAxisConstraint() {
    ApplyLock(m_pWorldMatrix, (m_ui8Unk12b & 0x38u) >> 3, &m_unke4, &m_unk94, &m_unkb8);  // jump table 0x21b1f8
}

// ---- C2.8 port-last Z7: the solver ----

// 0x009b3850 CKPxKinematic_ExportState (vt+0x50, inline): the body's, then the locks.
void CKPxKinematic::ExportState(CKPxBodyDesc* desc) {
    CKPxBody::ExportState(desc);
    static_cast<CKPxKinematicDesc*>(desc)->m_ui8Unk68 = m_ui8Unk12b;
}

// 0x009b3c60 CKPxKinematic_InitFromDesc_maybe (vt+0x54, inline): the body's parameters, SetWorldMatrix 0x219c70 (called,
// not inlined), then the locks.
void CKPxKinematic::InitFromDesc(const CKPxBodyDesc* desc) {
    InitParametersFromDesc(desc);
    CKPxBody::SetWorldMatrix(desc->m_pUnk60);  // 0x00219c70
    m_ui8Unk12b = static_cast<const CKPxKinematicDesc*>(desc)->m_ui8Unk68;
}

// 0x009b3ee0 CKPxKinematic_Step_maybe (vt+0x64, inline): driven (lock bit 0x40) or integrated, then the sample and the
// shapes; no sleep test.
void CKPxKinematic::Step(float dt, float dt2, float frequency, float /*halfFrequencySq*/, uint8_t lastStep) {
    if ((m_ui8Unk12b & 0x40) != 0) {
        ComputeDriveVelocities(dt, dt2, frequency, lastStep);  // 0x0021c568
    } else {
        Integrate(dt, dt2, frequency, lastStep);  // 0x0021b9f8
    }
    RecordSampleAndUpdateShapes(dt, lastStep);  // 0x00218790
}

// 0x0021b9f8 CKPxKinematic_Integrate_maybe: CKPxBody's Integrate with the kinematic's limits and locks (CKPxBody.cpp).
void CKPxKinematic::Integrate(float dt, float dt2, float frequency, uint8_t lastStep) {
    IntegrateCommon(dt, dt2, frequency, lastStep, true);
}

// 0x0021c568 CKPxKinematic_ComputeDriveVelocities_maybe: the body driven onto its node: the target = the node offset
// (+0xf8) times the node's frame LTM; the angular velocity that turns the world matrix onto it in one 1 / frequency
// (the axis-angle of world^-1 * target, in degrees, times the frequency), its acceleration (clamped with 0x10000), the
// linear velocity that moves it there and its acceleration (clamped with 0x1000), the velocity change through vt+0x58,
// then the world matrix = the target.
void CKPxKinematic::ComputeDriveVelocities(float dt, float /*dt2*/, float frequency, uint8_t /*lastStep*/) {
    CMatrix34 target{};
    Mat4_Multiply(&target, m_pUnkf8,
                  reinterpret_cast<const CMatrix34*>(&static_cast<CSGMovable*>(m_pNode)->m_pRwFrame->ltm));  // 0x23f788
    CMatrix34 delta{};
    Mat4_Invert(&delta, m_pWorldMatrix);  // 0x0023f878
    Mat4_TransformPostConcat(&delta, &target);  // 0x0023f760
    Mat4_OrthoNormalizeInPlace(&delta);  // 0x0023f648
    float q[4];
    Quat_FromMatrixNormalized(q, reinterpret_cast<const float*>(&delta));  // 0x00242648
    float axis[3];
    float angle;
    Quat_ToAxisAngle(q, axis, &angle);  // 0x00241fd0
    axis[0] = axis[0] * angle;
    axis[2] = angle * axis[2];
    axis[1] = axis[1] * angle;
    // The angular part.
    float ex = ppc::fmsubs(frequency, axis[0], m_unkb8.x);
    float ey = ppc::fmsubs(frequency, axis[1], m_unkb8.y);
    float ez = ppc::fmsubs(axis[2], frequency, m_unkb8.z);
    m_unk94.x = frequency * ex;
    m_unk94.y = frequency * ey;
    m_unk94.z = frequency * ez;
    if ((m_ui32Flags & 0x10000) != 0) {
        const float length = std::sqrt(ppc::fmadds(m_unk94.z, m_unk94.z, ppc::fmadds(m_unk94.x, m_unk94.x, m_unk94.y * m_unk94.y)));
        const float maxAcceleration = m_fUnk90;
        if (length > maxAcceleration) {  // ble
            const float scale = maxAcceleration / length;
            m_unk94.z = scale * m_unk94.z;
            m_unk94.x = scale * m_unk94.x;
            m_unk94.y = scale * m_unk94.y;
            m_ui32Flags |= 0x40000;
        } else {
            m_ui32Flags &= ~0x40000u;
        }
        float wy = ppc::fmadds(dt, m_unk94.y, m_unkb8.y);
        float wx = ppc::fmadds(dt, m_unk94.x, m_unkb8.x);
        float wz = ppc::fmadds(dt, m_unk94.z, m_unkb8.z);
        const float speed = std::sqrt(ppc::fmadds(wz, wz, ppc::fmadds(wx, wx, wy * wy)));
        const float maxSpeed = m_fUnkc4;
        if (speed > maxSpeed) {  // ble
            m_ui32Flags |= 0x20000;
            const float scale = maxSpeed / speed;
            wz = wz * scale;
            wx = wx * scale;
            wy = wy * scale;
        } else {
            m_ui32Flags &= ~0x20000u;
        }
        ez = wz - m_unkb8.z;
        ex = wx - m_unkb8.x;
        ey = wy - m_unkb8.y;
        m_unk94.z = frequency * ez;
        m_unk94.x = frequency * ex;
        m_unk94.y = frequency * ey;
    }
    {
        float wz = ez + m_unkb8.z;
        float wx = ex + m_unkb8.x;
        float wy = ey + m_unkb8.y;
        if ((m_ui32Flags & 0x1000) != 0) {
            const float speed = std::sqrt(ppc::fmadds(wz, wz, ppc::fmadds(wx, wx, wy * wy)));
            const float maxSpeed = m_fUnkb0;  // the linear limit, as in Integrate
            if (speed > maxSpeed) {  // bgt
                m_ui32Flags |= 0x20000;
                const float scale = maxSpeed / speed;
                wx = wx * scale;
                wz = wz * scale;
                wy = wy * scale;
            } else {
                m_ui32Flags &= ~0x20000u;
            }
        }
        m_unkb8.z = wz;
        m_unkb8.y = wy;
        m_unkb8.x = wx;
    }
    // The linear part.
    const CMatrix34* world = m_pWorldMatrix;
    const float dx = target.m_pos.x - world->m_pos.x;
    const float dy = target.m_pos.y - world->m_pos.y;
    const float dz = target.m_pos.z - world->m_pos.z;
    CVector3 change{ppc::fmsubs(frequency, dx, m_unka4.x), ppc::fmsubs(frequency, dy, m_unka4.y),
                    ppc::fmsubs(frequency, dz, m_unka4.z)};
    m_unk6c.x = frequency * change.x;
    m_unk6c.y = frequency * change.y;
    m_unk6c.z = frequency * change.z;
    if ((m_ui32Flags & 0x1000) != 0) {
        const float length = std::sqrt(ppc::fmadds(m_unk6c.z, m_unk6c.z, ppc::fmadds(m_unk6c.x, m_unk6c.x, m_unk6c.y * m_unk6c.y)));
        const float maxAcceleration = m_fUnk68;
        if (length > maxAcceleration) {  // ble
            const float scale = maxAcceleration / length;
            m_unk6c.z = scale * m_unk6c.z;
            m_unk6c.x = scale * m_unk6c.x;
            m_unk6c.y = scale * m_unk6c.y;
            m_ui32Flags |= 0x4000;
        } else {
            m_ui32Flags &= ~0x4000u;
        }
        float vy = ppc::fmadds(dt, m_unk6c.y, m_unka4.y);
        float vx = ppc::fmadds(dt, m_unk6c.x, m_unka4.x);
        float vz = ppc::fmadds(dt, m_unk6c.z, m_unka4.z);
        const float speed = std::sqrt(ppc::fmadds(vz, vz, ppc::fmadds(vx, vx, vy * vy)));
        const float maxSpeed = m_fUnkb0;
        if (speed > maxSpeed) {  // ble
            m_ui32Flags |= 0x2000;
            const float scale = maxSpeed / speed;
            vz = vz * scale;
            vx = vx * scale;
            vy = vy * scale;
        } else {
            m_ui32Flags &= ~0x2000u;
        }
        change.z = vz - m_unka4.z;
        change.x = vx - m_unka4.x;
        change.y = vy - m_unka4.y;
        m_unk6c.z = frequency * change.z;
        m_unk6c.x = frequency * change.x;
        m_unk6c.y = frequency * change.y;
    }
    AddVelocity(&change);  // vt+0x58
    *m_pWorldMatrix = target;  // all 16 words
}
