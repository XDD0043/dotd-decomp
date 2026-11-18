// Reconstructed original translation unit: 0x22cba8-0x22db30 (GAME_TOC1, main_toc1), 13 functions, 13 live.
// Primary owner: CKPxShape (not a registered class)
// Other owners: KBase474C (2)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x22cba8  CKPxShape_474c_maybe_vf28  (KBase474C.h: the base's Save (returns 1))
//   [x] 0x22cbd0  CKPxShape_474c_maybe_vf24  (KBase474C.h: the base's RecursiveRegistration (returns 1, registers nothing))
//   [x] 0x22cbf8  CKPxShape_474c_maybe_ClearReferences  (KBase474C.h Destroy)
//   [x] 0x22cc48  CKPxShape_474c_maybe_BaseDestructor  (KBase474C.h destructor: vtable stores only)
//   [x] 0x22cc78  CKPxShape_474c_maybe_DeletingDestructor  (the deleting form of KBase474C.h's destructor)
//   [x] 0x22ccc0  CKPxShape_474c_maybe_Destructor  (the same as 0x22cc48 (KBase474C.h))
//   [x] 0x22ccf0  CKPxShape_UpdateLocalFromWorld_maybe  (KBase474C::UpdateLocalFromWorld; no caller in the original)
//   [x] 0x22ce50  CKPxShape_474c_maybe_ConstructBase_2  (the same stores as 0x22cec8 (KBase474C.h constructor))
//   [x] 0x22cec8  CKPxShape_474c_maybe_ConstructBase  (KBase474C.h constructor)
//   [x] 0x22cf40  CKPxShape_UpdateWorldMatrix_maybe  (KBase474C::UpdateWorldMatrix)
//   [x] 0x22d0c0  KBase474C_vf6C  (KBase474C::AddWallContact, vt+0x6c)
//   [x] 0x22d470  CKPxShape_474c_maybe_Load  (KBase474C.h Load)
//   [x] 0x22d738  KBase474C_AddGroundContact_maybe  (KBase474C::AddGroundContact, vt+0x68)
//
//   [ ] 0x9b4f40  CKPxShape_474c_maybe_vf8  [inline]
//   [ ] 0x9b4f68  CKPxShape_474c_maybe_vf14  [inline]
//   [ ] 0x9b4f70  CKPxShape_474c_maybe_vf18  [inline]
//   [ ] 0x9b4f78  KBase474C_vf58  [inline]
//
// C2.8 port-last Z7: the matrix updates and the two contact slots (declared in KBase474C.h).
#include <cmath>
#include <cstring>

#include "Renderware/rwcore/RwCamera.h"
#include "crt/ppc_ops.h"
#include "crt/xsinf.h"
#include "k2000/logic/CKPxBody.h"
#include "k2000/logic/physics/CKPxContactJoint.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/KBase474C.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/services/CKSrvCollision.h"
#include "k2000/services/CKSrvPhysics.h"

namespace {

const CVector3 kDown{0.0f, -1.0f, 0.0f};  // 0x00c50d7c (TOC1 -0x7a0; a static initialiser fills it)

bool SignBitSet(float x) {
    int32_t bits;
    std::memcpy(&bits, &x, sizeof(bits));
    return bits < 0;
}
// The game's cosine: the inlined polynomial for a clear sign bit, the library's cosf 0x009a11d8 of -x otherwise.
float GameCosf(float x) { return SignBitSet(x) ? crt::LibCosf(-x) : crt::InlineCosf(x); }

CKSrvCollision* SrvCollision() { return static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision); }
CKSrvPhysics* SrvPhysics() { return static_cast<CKSrvPhysics*>(g_pEngine->m_srvPhysics); }

// An owner node's frame LTM (frame +0x50).
const CMatrix34* NodeLtm(IKSerializable* node) {
    return reinterpret_cast<const CMatrix34*>(&static_cast<CSGMovable*>(node)->m_pRwFrame->ltm);
}

}  // namespace

// 0x0022cf40 CKPxShape_UpdateWorldMatrix_maybe
void KBase474C::UpdateWorldMatrix() {
    if ((m_unka0 & 0x80) != 0) {
        Mat4_Multiply(m_pLocalMatrix, m_pWorldMatrix, static_cast<CKPxBody*>(m_unk04)->m_pWorldMatrix);  // 0x0023f788
        Mat4_OrthoNormalizeInPlace(m_pLocalMatrix);  // 0x0023f648
        return;
    }
    if (m_unk04 != nullptr) {
        Mat4_Multiply(m_pLocalMatrix, m_pWorldMatrix, NodeLtm(m_unk04));
        Mat4_OrthoNormalizeInPlace(m_pLocalMatrix);
        return;
    }
    *m_pLocalMatrix = *m_pWorldMatrix;  // all 16 words
}

// 0x0022ccf0 CKPxShape_UpdateLocalFromWorld_maybe
void KBase474C::UpdateLocalFromWorld() {
    CMatrix34 inverse{};
    if ((m_unka0 & 0x80) != 0) {
        Mat4_Invert(&inverse, static_cast<CKPxBody*>(m_unk04)->m_pWorldMatrix);  // 0x0023f878
    } else if (m_unk04 != nullptr) {
        Mat4_Invert(&inverse, NodeLtm(m_unk04));
    } else {
        // The identity built on the stack (its pads are not written: zero here).
        inverse.m_right.x = 1.0f;
        inverse.m_up.y = 1.0f;
        inverse.m_at.z = 1.0f;
        inverse.m_ui32Flags = 0x20003;
    }
    Mat4_Multiply(m_pWorldMatrix, m_pLocalMatrix, &inverse);  // 0x0023f788
    Mat4_OrthoNormalizeInPlace(m_pWorldMatrix);
}

// 0x0022d738 KBase474C_AddGroundContact_maybe (vt+0x68): the probe height (+0x40) = +0x28, the lowest point (vt+0x60
// down) probed for the ground; on a ground (status 2) the pool's next contact joint gets the owner body, the ground's
// normal, the point farthest against the normal (vt+0x60), the depth fdH * normal.y (less (1 - cos(k x + k z)) * 0.5 *
// the service's +0x12c for a body flagged 0x400; k = its +0x134), the bounce, and joins the contact list.
void KBase474C::AddGroundContact() {
    CKPxBody* body = static_cast<CKPxBody*>(m_unk04);
    m_GrdIn.m_fObjectHeight = m_fUnk28;
    CVector3 point;
    GetSupportPoint(&kDown, &point);  // vt+0x60
    SrvCollision()->GroundProbePoints(&m_GrdIn, &m_GrdInOut, &point.x, 1);  // 0x00196540
    if (m_GrdInOut.m_eContactStatus != 2) return;
    CKSrvPhysics* physics = SrvPhysics();
    CKPxContactJoint* contact = physics->NextContactJoint();
    contact->SetBodies(body, nullptr);  // 0x002203e0
    contact->m_unk38 = m_GrdInOut.m_Normal;
    const CVector3 against{-m_GrdInOut.m_Normal.x, -m_GrdInOut.m_Normal.y, -m_GrdInOut.m_Normal.z};
    GetSupportPoint(&against, &point);  // vt+0x60
    contact->m_unk2c = point;
    float depth = m_GrdInOut.m_fdH * m_GrdInOut.m_Normal.y;
    if ((body->m_ui32Flags & 0x400) != 0) {
        const float k = physics->m_unk134;
        const float angle = ppc::fmadds(k, point.x, k * point.z);
        const float c = GameCosf(angle);
        depth = depth - (1.0f - c) * (physics->m_unk12c * 0.5f);
    }
    contact->m_unk44 = depth;
    float bounce = m_fUnk30;
    if (bounce <= 0.0f) {  // cror lt|eq: NaN goes on
        contact->m_unk18 = 0;
        bounce = 0.0f;
    } else if (!(bounce > 2.0f)) {  // ble: NaN takes it
        contact->m_unk18 = 1;
    } else {
        contact->m_unk18 = 2;
        bounce = 2.0f;
    }
    contact->m_unk48 = bounce;
    physics->CommitContactJoint();
}

// 0x0022d0c0 KBase474C_vf6C (vt+0x6c): the point farthest along the owner body's velocity (+0xa4) swept back along
// the unit velocity against the walls (radius and height +0x28); on a hit (1..3) the next point is the one farthest
// against the wall normal, swept again (radius 0.1); on a second hit the pool's next contact joint gets the body, that
// point, the wall normal, the depth normal . slide vector, no bounce (kind 0), and joins the contact list.
void KBase474C::AddWallContact() {
    CKPxBody* body = static_cast<CKPxBody*>(m_unk04);
    CVector3 direction = body->m_unka4;
    CVector3 point;
    GetSupportPoint(&direction, &point);  // vt+0x60
    float y = body->m_unka4.y;
    float x = body->m_unka4.x;
    float z = body->m_unka4.z;
    const float length = std::sqrt(ppc::fmadds(z, z, ppc::fmadds(x, x, y * y)));  // Math_Sqrtf 0x10690
    if (length != 0.0f) {
        const float inverse = 1.0f / length;
        z = z * inverse;
        x = x * inverse;
        y = y * inverse;
    }
    CLine line;
    line.m_start = {point.x - x, point.y - y, point.z - z};
    line.m_VectDir = {point.x - line.m_start.x, point.y - line.m_start.y, point.z - line.m_start.z};
    uint8_t hit = SrvCollision()->ResolveSweptCylinderWalls(&line, m_fUnk28, m_fUnk28, &m_SlideOut, nullptr, nullptr, 1);
    if (static_cast<uint32_t>(hit) - 1u <= 2u) {
        direction = {-m_SlideOut.m_v3Normal.x, -m_SlideOut.m_v3Normal.y, -m_SlideOut.m_v3Normal.z};
    }
    GetSupportPoint(&direction, &point);  // vt+0x60
    line.m_start = {point.x - x, point.y - y, point.z - z};
    line.m_VectDir = {point.x - line.m_start.x, point.y - line.m_start.y, point.z - line.m_start.z};
    hit = SrvCollision()->ResolveSweptCylinderWalls(&line, 0.1f, m_fUnk28, &m_SlideOut, nullptr, nullptr, 1);
    if (static_cast<uint32_t>(hit) - 1u > 2u) return;
    CKSrvPhysics* physics = SrvPhysics();
    CKPxContactJoint* contact = physics->NextContactJoint();
    contact->SetBodies(body, nullptr);  // 0x002203e0
    contact->m_unk2c = point;
    contact->m_unk38 = m_SlideOut.m_v3Normal;
    const CVector3& n = m_SlideOut.m_v3Normal;
    const CVector3& b = m_SlideOut.m_v3BouncingVector;
    contact->m_unk48 = 0.0f;
    contact->m_unk18 = 0;
    contact->m_unk44 = ppc::fmadds(n.z, b.z, ppc::fmadds(n.x, b.x, n.y * b.y));
    physics->CommitContactJoint();
}
