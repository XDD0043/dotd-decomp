// CKPxSpringJoint.cpp - reconstructed original translation unit 0x227528-0x2296d0 (GAME_TOC1, main_toc1), 17 functions, 17 live.
// Primary class: CKPxSpringJoint  key 0x4dcc  category Logic  size 0x88  vtable 0xb201a8
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x227528  CKPxSpringJoint_Delete
//   [ ] 0x227578  RegisterCKPxSpringJointClass
//   [ ] 0x2275f0  _GLOBAL__I_2275f0
//   [ ] 0x227600  CKPxSpringJoint_Save
//   [x] 0x227628  CKPxSpringJoint_RecursiveRegistration  (the base's vf24: returns 1, registers nothing)
//   [x] 0x227650  CKPxSpringJoint_Destroy  (KBase488C's: the anchors freed)
//   [x] 0x227678  CKPxSpringJoint_Construct  (header)
//   [x] 0x2276b0  CKPxSpringJoint_DeleteArray
//   [x] 0x227758  CKPxSpringJoint_DeletingDestructor  (the destructor; delete)
//   [x] 0x2277a0  CKPxSpringJoint_Destructor  (C++ destructor chain: vtable stores only)
//   [x] 0x2277d0  CKPxSpringJoint_BaseDestructor  (C++ destructor chain: vtable stores only)
//   [x] 0x227800  CKPxSpringJoint_Construct_2  (the constructor's second C++ variant)
//   [x] 0x227838  CKPxSpringJoint_Create
//   [x] 0x227890  CKPxSpringJoint_CreateArray
//   [x] 0x227948  CKPxSpringJoint_vf60  (Solve)
//   [x] 0x228058  CKPxSpringJoint_Load
//   [x] 0x228340  CKPxSpringJoint_vf5C  (WakeAndPickBody)
//
//   [ ] 0x9b4940  CKPxSpringJoint_IsKindOfClass  [inline]
//   [ ] 0x9b4978  CKPxSpringJoint_GetClassType  [inline]
//   [ ] 0x9b4980  CKPxSpringJoint_GetClassID  [inline]
//   [ ] 0x9b4988  CKPxSpringJoint_InitFromDesc_maybe  [inline]
//   [ ] 0x9b4a20  CKPxSpringJoint_ExportState  [inline]
#include "k2000/logic/CKPxSpringJoint.h"

#include <cmath>

#include "crt/xatan.h"
#include "k2000/logic/CKPxBody.h"
#include "k2000/logic/memory/CKPxContainer.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/Mat4.h"
#include "k2000/misc/PxJointRows.h"
#include "k2000/services/CKSrvPhysics.h"

namespace {
const CVector3 kNullVector{0.0f, 0.0f, 0.0f};  // 0x00c50d64
}  // namespace

// 0x00228058 CKPxSpringJoint_Load
int32_t CKPxSpringJoint::Load(IKFile* file, int32_t type) {
    KBase488C::Load(file, type);  // 0x0021da00
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadU32LE(file, &m_unk58);
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(&m_unk5c), 3);
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(&m_unk68), 3);
    ReadF32LE(file, &m_fUnk74);
    ReadF32LE(file, &m_fUnk78);
    ReadF32LE(file, &m_fUnk7c);
    ReadF32LE(file, &m_fUnk80);
    ReadF32LE(file, &m_fUnk84);
    return 1;
}

// 0x00228340 CKPxSpringJoint_vf5C (vt+0x5c): KBase488C_vf5C without the island merge: with one body, that body when it
// is awake or resting (0x14); both asleep: both put to sleep and the joint taken out of the joint container (none
// returned); else the sleeping one woken (unless resting / locked (0x14) or fixed (0x20)) and the first body returned.
CKPxBody* CKPxSpringJoint::WakeAndPickBody() {
    if ((m_unk18 & 0x2000) != 0) return nullptr;
    CKPxBody* a = static_cast<CKPxBody*>(m_unk1c);
    if (a == nullptr) {
        CKPxBody* b = static_cast<CKPxBody*>(m_unk24);
        return (b->m_ui32Flags & 0x14) != 0 ? b : nullptr;
    }
    CKPxBody* b = static_cast<CKPxBody*>(m_unk24);
    if (b == nullptr) return (a->m_ui32Flags & 0x14) != 0 ? a : nullptr;
    CKSrvPhysics* physics = static_cast<CKSrvPhysics*>(g_pEngine->m_srvPhysics);
    const uint32_t flagsA = a->m_ui32Flags;
    if ((flagsA & 4) == 0) {
        if ((b->m_ui32Flags & 4) == 0) {
            if ((flagsA & 8) == 0 && (flagsA & 0x20) == 0) physics->PutBodyToSleep(a);
            b = static_cast<CKPxBody*>(m_unk24);
            const uint32_t flagsB = b->m_ui32Flags;
            if ((flagsB & 8) == 0 && (flagsB & 0x20) == 0) physics->PutBodyToSleep(b);
            if ((m_unk18 & 0x4000) != 0) {
                m_unk18 &= ~0x4000u;
                if (m_unk08 != nullptr) CKPxContainer::Unlink(static_cast<CKPxContainer*>(physics->m_unk54), this);
            }
            return nullptr;
        }
        if ((flagsA & 0x14) != 0) return a;
        if ((flagsA & 0x20) != 0) return a;
        physics->WakeBodyIsland(a);  // 0x009b2480 (inlined)
        return static_cast<CKPxBody*>(m_unk1c);
    }
    const uint32_t flagsB = b->m_ui32Flags;
    if ((flagsB & 0x14) != 0) return a;
    if ((flagsB & 0x20) != 0) return a;
    physics->WakeBodyIsland(b);
    return static_cast<CKPxBody*>(m_unk1c);
}
// 0x00227948 CKPxSpringJoint_vf60 (vt+0x60, Solve): with a body awake (vt+0x5c), mode 0 (+0x58) a linear spring
// between the anchors (+0x5c / +0x68): the stretch past the rest length (+0x74) beyond the slack (+0x78) times the
// stiffness (+0x7c) plus the speed along it times the damping (+0x84 opening, +0x80 closing), applied as forces and
// torques (+0x50 / +0x78) to the moving bodies; mode 1 an angular spring on the angle between the two axes (turned by
// each body) about their cross product, applied as torques. Rows are not used.
void CKPxSpringJoint::Solve() {
    if (WakeAndPickBody() == nullptr) return;  // vt+0x5c
    if (m_unk58 == 0) {
        CVector3 armA{};  // BUG(original): read uninitialised for a moving first body without a first body (cannot be)
        CVector3 pointA, velocityA;
        if (m_unk1c != nullptr) {
            CKPxBody* a = static_cast<CKPxBody*>(m_unk1c);
            Mat4_TransformVectors(a->m_pWorldMatrix, &armA, &m_unk5c, 1);  // 0x0023f7b0
            velocityA = pxrows::VelocityAt(a, armA);
            pointA = pxrows::Add(armA, a->m_pWorldMatrix->m_pos);
        } else {
            pointA = m_unk5c;
            velocityA = kNullVector;
        }
        CVector3 armB{};
        CVector3 pointB, velocityB;
        if (m_unk24 != nullptr) {
            CKPxBody* b = static_cast<CKPxBody*>(m_unk24);
            Mat4_TransformVectors(b->m_pWorldMatrix, &armB, &m_unk68, 1);
            velocityB = pxrows::VelocityAt(b, armB);
            pointB = pxrows::Add(armB, b->m_pWorldMatrix->m_pos);
        } else {
            pointB = m_unk68;
            velocityB = kNullVector;
        }
        const CVector3 d = pxrows::Sub(pointB, pointA);
        const float length = pxrows::Length(d);
        if (length == 0.0f) return;
        if (length < 1e-6f) return;  // blt
        const float stretch = length - m_fUnk74;
        const float slack = m_fUnk78;
        float spring;
        if (stretch > slack) {  // ble
            spring = stretch - slack;
        } else {
            spring = 0.0f;
            if (!(-slack <= stretch)) spring = stretch + slack;  // ble: NaN keeps 0
        }
        const float inverse = 1.0f / length;
        const CVector3 n{d.x * inverse, d.y * inverse, d.z * inverse};
        const float speed = pxrows::Dot(pxrows::Sub(velocityB, velocityA), n);
        const float damping = speed > 0.0f ? m_fUnk84 : m_fUnk80;  // ble takes +0x80
        const float force = ppc::fmadds(spring, m_fUnk7c, speed * damping);
        const CVector3 f{force * n.x, force * n.y, force * n.z};
        if (m_unk20 != nullptr) {
            CKPxBody* a = static_cast<CKPxBody*>(m_unk20);
            a->m_unk50 = pxrows::Add(a->m_unk50, f);
            const CVector3 torque{ppc::fmsubs(armA.y, f.z, armA.z * f.y), ppc::fmsubs(armA.z, f.x, armA.x * f.z),
                                  ppc::fmsubs(armA.x, f.y, armA.y * f.x)};
            a->m_unk78 = pxrows::Add(torque, a->m_unk78);
        }
        if (m_unk28 != nullptr) {
            CKPxBody* b = static_cast<CKPxBody*>(m_unk28);
            const CVector3 g{-f.x, -f.y, -f.z};
            b->m_unk50 = pxrows::Add(g, b->m_unk50);
            const CVector3 torque{ppc::fmsubs(g.z, armB.y, g.y * armB.z), ppc::fmsubs(g.x, armB.z, g.z * armB.x),
                                  ppc::fmsubs(g.y, armB.x, g.x * armB.y)};
            b->m_unk78 = pxrows::Add(torque, b->m_unk78);
        }
        return;
    }
    if (m_unk58 != 1) return;
    CVector3 axisA, spinA;
    if (m_unk1c != nullptr) {
        CKPxBody* a = static_cast<CKPxBody*>(m_unk1c);
        Mat4_TransformVectors(a->m_pWorldMatrix, &axisA, &m_unk5c, 1);
        spinA = a->m_unkb8;
    } else {
        axisA = m_unk5c;
        spinA = kNullVector;
    }
    CVector3 axisB, spinB;
    if (m_unk24 != nullptr) {
        CKPxBody* b = static_cast<CKPxBody*>(m_unk24);
        Mat4_TransformVectors(b->m_pWorldMatrix, &axisB, &m_unk68, 1);
        spinB = b->m_unkb8;
    } else {
        axisB = m_unk68;
        spinB = kNullVector;
    }
    // The turn axis axisA x axisB, normalised unless 0.
    float ny = ppc::fmsubs(axisA.z, axisB.x, axisB.z * axisA.x);
    float nx = ppc::fmsubs(axisA.y, axisB.z, axisA.z * axisB.y);
    float nz = ppc::fmsubs(axisB.y, axisA.x, axisA.y * axisB.x);
    const float length = pxrows::Length(CVector3{nx, ny, nz});
    if (length != 0.0f) {
        const float inverse = 1.0f / length;
        nz = nz * inverse;
        nx = nx * inverse;
        ny = ny * inverse;
    }
    float cosine = pxrows::Dot(axisA, axisB);
    if (cosine < -1.0f) {  // blt
        cosine = -1.0f;
    } else if (cosine > 1.0f) {  // ble keeps it
        cosine = 1.0f;
    }
    const float angle = crt::Acosf(cosine);  // TocBridge_Math_Acosf 0x98e1a0
    const float stretch = angle - m_fUnk74;
    const float slack = m_fUnk78;
    float spring;
    if (stretch > slack) {  // ble
        spring = stretch - slack;
    } else {
        spring = 0.0f;
        if (!(-slack <= stretch)) spring = stretch + slack;  // ble: NaN keeps 0
    }
    if (std::fabs(spring) < 1e-6f) return;  // the sign bit cleared in memory; blt: NaN goes on
    const CVector3 n{nx, ny, nz};
    const float speed = pxrows::Dot(pxrows::Sub(spinB, spinA), n);
    const float damping = speed > 0.0f ? m_fUnk84 : m_fUnk80;  // ble takes +0x80
    const float torque = ppc::fmadds(spring, m_fUnk7c, speed * damping);
    const CVector3 t{torque * nx, torque * ny, torque * nz};
    if (m_unk20 != nullptr) {
        CKPxBody* a = static_cast<CKPxBody*>(m_unk20);
        a->m_unk78 = pxrows::Add(a->m_unk78, t);
    }
    if (m_unk28 != nullptr) {
        CKPxBody* b = static_cast<CKPxBody*>(m_unk28);
        b->m_unk78 = pxrows::Sub(b->m_unk78, t);
    }
}
