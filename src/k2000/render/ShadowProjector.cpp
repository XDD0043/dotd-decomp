//
// Reconstructed original translation unit: 0x1fee18-0x1ffbf8 (GAME_TOC1, main_toc1), 4 functions, 4 live.
// Primary owner: ShadowProjector (not a registered class)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1fee18  ShadowProjector_ResetFade
//   [x] 0x1fee38  ShadowProjector_Bind
//   [x] 0x1feff0  ShadowProjector_BuildGroundAlignedMatrix_maybe
//   [x] 0x1ff2c0  ShadowProjector_Update
//
//   [ ] 0x9b1230  ShadowProjector_Destructor  [inline]
//   [ ] 0x9b1240  ShadowProjector_DeletingDestructor  [inline]

#include <cmath>
#include <cstring>

#include "crt/ppc_ops.h"
#include "k2000/cameras/CKSrvCamera.h"
#include "k2000/components/CKShadowCpnt.h"
#include "k2000/geometry/CGeometry.h"
#include "k2000/logic/render/CMaterial.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/Mat4.h"
#include "k2000/render/CRenderer.h"
#include "k2000/scenegraph/CNode.h"
#include "k2000/scenegraph/CSGLeaf.h"
#include "k2000/services/CKSrvCollision.h"
#include "k2000/services/CKSrvShadow.h"
#include "k2000/system/IKTime.h"
#include "Renderware/rwcore/RwCamera.h"
#include "Renderware/rwcore/RwMatrix.h"
#include "Spyro2008/logic/CKS08GameManager.h"

// 0x001fee38 CKShadowSpot_SetData_maybe: the component's colour (+0x1c, four bytes; also the target colour), the two
// smoothing speeds (+0x20 colour, +0x24 normal).
void CKShadowSpot::SetData(IKSerializable* shadowCpnt, IKSerializable* leaf, void* ground) {
    const CKShadowCpnt* cpnt = static_cast<const CKShadowCpnt*>(shadowCpnt);
    m_pShadowCpnt = shadowCpnt;
    m_pLeaf = leaf;
    CGeometry* spotGeometry = static_cast<CGeometry*>(static_cast<CNode*>(g_pSrvShadow->m_pShadowSpotNode)->m_lGeometryList);
    std::memcpy(m_cColor, cpnt->m_ShadowColor, 4);
    for (int i = 0; i < 4; ++i) m_afColor[i] = static_cast<float>(m_cColor[i]);
    std::memcpy(m_cTargetColor, cpnt->m_ShadowColor, 4);
    m_fUnk1c = cpnt->m_fSpeedSmoothColor;
    static const CVector3 kUp = {0.0f, 1.0f, 0.0f};  // 0x00c50d40
    m_v3c = kUp;
    m_v30 = kUp;
    m_fUnk48 = cpnt->m_fSpeedSmoothNormal;
    // The spot node's material takes the service's shadow texture (SetMaterialTexture_maybe);
    // without a component it is cleared.
    static_cast<CMaterial*>(spotGeometry->m_pMaterial)
        ->SetTexture(m_pShadowCpnt == nullptr ? nullptr : static_cast<RwTexture*>(static_cast<CKSrvShadow*>(g_pEngine->m_srvShadow)->m_pShadowTexture));
    m_pGround = ground;
    m_groundIn.m_MasksOfGrdForTest[0] = 1;
    m_groundIn.m_MasksOfGrdForTest[1] = 8;
    m_groundIn.m_fDeltaMax = 0.2f;  // TOC1 -0x11ac (0x3e4ccccd)
    m_groundIn.m_fObjectHeight = 0.0f;
    m_groundContact.m_pGround = nullptr;
    m_groundContact.m_ui8SectorNumber = 0;
    m_groundContact.m_i32FaceIndex = -1;
    m_groundContact.m_eContactStatus = 3;
}

namespace {
// A vector normalised in place when its length (y first, fused, fsqrts) is not 0: z, x, y times 1 / length.
void NormaliseIfNotZero(CVector3* v) {
    const float length = std::sqrt(ppc::fmadds(v->z, v->z, ppc::fmadds(v->x, v->x, v->y * v->y)));  // Math_Sqrtf
    if (length == 0.0f) return;
    const float k = 1.0f / length;
    v->z = v->z * k;
    v->x = v->x * k;
    v->y = v->y * k;
}
}  // namespace

// 0x001feff0 ShadowProjector_BuildGroundAlignedMatrix_maybe. The cross product's squared length against 0.0175 (TOC1 -0x11a0)
// tells a usable hint; the comparisons keep the original's branch senses (bge / blt: a NaN takes the other side in the two
// normalised cases).
void CKShadowSpot::BuildGroundAlignedMatrix(CMatrix34* matrix, IKSerializable* leaf, const CVector3* at) {
    const RwFrame* frame = static_cast<const CSGLeaf*>(leaf)->m_pRwFrame;
    const RwMatrix& modelling = frame->modelling;  // frame +0x10
    const float kThreshold = 0.0175f;
    // (hint x at)'s squared length, the y component first (fmsubs, then fmuls / fmadds).
    auto crossLength2 = [at](const CVector3& h) {
        const float cy = ppc::fmsubs(h.z, at->x, at->z * h.x);
        const float cx = ppc::fmsubs(h.y, at->z, h.z * at->y);
        const float cz = ppc::fmsubs(at->y, h.x, h.y * at->x);
        return ppc::fmadds(cz, cz, ppc::fmadds(cx, cx, cy * cy));
    };
    if ((modelling.flags & 1) != 0) {
        const CVector3 hint = {modelling.at.x, modelling.at.y, modelling.at.z};
        if (crossLength2(hint) >= kThreshold) {
            Mat4_SetBasisFromAtUp(matrix, at, reinterpret_cast<const CVector3*>(&modelling.at));  // 0x23fd30
        } else {
            Mat4_SetBasisFromAtUp(matrix, at, reinterpret_cast<const CVector3*>(&modelling.up));
        }
        return;
    }
    CVector3 hint = {modelling.at.x, modelling.at.y, modelling.at.z};
    const float length = std::sqrt(ppc::fmadds(hint.z, hint.z, ppc::fmadds(hint.x, hint.x, hint.y * hint.y)));
    bool useAt;
    if (length == 0.0f) {
        useAt = !(crossLength2(hint) < kThreshold);
    } else {
        const float k = 1.0f / length;
        hint.z = hint.z * k;
        hint.x = hint.x * k;
        hint.y = hint.y * k;
        useAt = crossLength2(hint) >= kThreshold;
    }
    if (useAt) {
        Mat4_SetBasisFromAtUp(matrix, at, &hint);
        return;
    }
    CVector3 up = {modelling.up.x, modelling.up.y, modelling.up.z};
    NormaliseIfNotZero(&up);
    Mat4_SetBasisFromAtUp(matrix, at, &up);
}

// 0x001ff2c0 ShadowProjector_Update
int32_t CKShadowSpot::Update(IKTime* clock, CMatrix34* matrix, float* uv, uint8_t* color) {
    CKShadowGround* ground = static_cast<CKShadowGround*>(m_pGround);
    const uint8_t flags = ground->m_ui8Flags;
    if ((flags & 0x10) != 0) return 1;
    if (static_cast<const CSGLeaf*>(m_pLeaf)->m_ui16LastRenderedFrame != g_ui16RenderFrameCounter &&
        static_cast<const CKShadowCpnt*>(m_pShadowCpnt)->m_bAlwaysVisible == 0) {
        return 1;
    }
    CKSrvShadow* service = static_cast<CKSrvShadow*>(g_pEngine->m_srvShadow);       // engine +0x88
    const CKSrvCamera* camera = static_cast<const CKSrvCamera*>(g_pEngine->m_srvCamera);  // engine +0x70
    if ((flags & 1) != 0) {
        if ((flags & 8) != 0) {
            const RwV3d& pos = FrameLtm(static_cast<const CSGLeaf*>(m_pLeaf)->m_pRwFrame)->pos;
            ground->m_v3Position.z = pos.z;
            ground->m_v3Position.x = pos.x;
            ground->m_v3Position.y = pos.y;
        }
        static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision)
            ->GroundProbePoints(&m_groundIn, &m_groundContact, &ground->m_v3Position.x, 1);  // 0x196540
        if (m_groundContact.m_eContactStatus == 3) return 1;
        const CKS08GameManager* manager = static_cast<const CKS08GameManager*>(g_pEngine->m_gameManager);
        if ((manager->GetGroundSurfaceBit(m_groundContact.m_pGround) & 0xffu) != 0) return 1;  // vt+0x138 0x4f88f8
        GroundContact_GetWorldPoint(&m_groundContact, &ground->m_v3Position);  // 0x1a70e0
        if ((ground->m_ui8Flags & 2) == 0) GroundContact_GetWorldNormal(&m_groundContact, &ground->m_v3Normal);  // 0x1a71d8
        if ((ground->m_ui8Flags & 4) == 0) ground->m_fUnk18 = m_groundContact.m_fdH;
    }
    const CVector3& focus = camera->m_v3RealPos;  // +0x598
    float distance;
    {
        const RwV3d& pos = FrameLtm(static_cast<const CSGLeaf*>(m_pLeaf)->m_pRwFrame)->pos;
        const float dy = pos.y - focus.y;
        const float dx = pos.x - focus.x;
        const float dz = pos.z - focus.z;
        distance = std::sqrt(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));  // Math_Sqrtf
    }
    const CKShadowCpnt* cpnt = static_cast<const CKShadowCpnt*>(m_pShadowCpnt);
    const float gx = ground->m_v3Position.x;
    const float gy = ground->m_v3Position.y;
    const float gz = ground->m_v3Position.z;
    if (!(cpnt->m_fShadowDistanceMax > distance) && cpnt->m_bAlwaysVisible == 0) return 1;

    // The quad's orientation: the ground's normal, or with normal smoothing the smoothed one (the ground's becomes the target).
    CVector3 normal = ground->m_v3Normal;
    if (cpnt->m_bSmoothNormal != 0) {
        m_v30 = normal;
        normal = m_v3c;
    }
    if (m_pLeaf != nullptr) {
        NormaliseIfNotZero(&normal);
        BuildGroundAlignedMatrix(matrix, m_pLeaf, &normal);  // 0x1feff0
    }
    matrix->m_pos = {gx, gy, gz};
    matrix->m_ui32Flags &= ~0x20000u;  // rwMATRIXINTERNALIDENTITY
    // Lifted towards the focus point by the service's offset.
    float ty = focus.y - gy;
    float tx = focus.x - gx;
    float tz = focus.z - gz;
    const float toFocus = std::sqrt(ppc::fmadds(tz, tz, ppc::fmadds(tx, tx, ty * ty)));
    if (toFocus != 0.0f) {
        const float k = 1.0f / toFocus;
        tz = tz * k;
        tx = tx * k;
        ty = ty * k;
    }
    const float offset = service->m_fOffsetShadow;
    matrix->m_pos.x = ppc::fmadds(tx, offset, matrix->m_pos.x);
    matrix->m_pos.z = ppc::fmadds(tz, offset, matrix->m_pos.z);
    matrix->m_pos.y = ppc::fmadds(ty, offset, matrix->m_pos.y);
    matrix->m_ui32Flags &= ~0x20000u;

    const float height = ground->m_fUnk18;
    if (height > 0.05f) {  // TOC1 -0x1190
        // Above the ground: the quad and both alphas shrink with the height, down to the minimum scale.
        float fade = 1.0f - height / cpnt->m_fShadowScale;
        if (fade < cpnt->m_fShadowMinScale) fade = cpnt->m_fShadowMinScale;
        const float sRight = fade * cpnt->m_fShadowLong;
        const float sUp = fade * cpnt->m_fShadowWidth;
        matrix->m_right.z = sRight * matrix->m_right.z;
        matrix->m_right.y = sRight * matrix->m_right.y;
        matrix->m_right.x = sRight * matrix->m_right.x;
        matrix->m_up.x = sUp * matrix->m_up.x;
        matrix->m_up.y = sUp * matrix->m_up.y;
        matrix->m_up.z = sUp * matrix->m_up.z;
        matrix->m_ui32Flags &= 0xfffdfffeu;
        const int32_t alpha = ppc::fctiwz(fade * static_cast<float>(m_cColor[3]));
        const int32_t targetAlpha = ppc::fctiwz(fade * static_cast<float>(m_cTargetColor[3]));
        m_cColor[3] = static_cast<uint8_t>(alpha);
        m_afColor[3] = static_cast<float>(static_cast<uint32_t>(alpha) & 0xffu);
        m_cTargetColor[3] = static_cast<uint8_t>(targetAlpha);
    } else {
        const float sRight = cpnt->m_fShadowLong;
        const float sUp = cpnt->m_fShadowWidth;
        matrix->m_right.z = sRight * matrix->m_right.z;
        matrix->m_right.y = sRight * matrix->m_right.y;
        matrix->m_up.x = sUp * matrix->m_up.x;
        matrix->m_right.x = sRight * matrix->m_right.x;
        matrix->m_up.y = sUp * matrix->m_up.y;
        matrix->m_up.z = sUp * matrix->m_up.z;
        matrix->m_ui32Flags &= 0xfffdfffeu;
    }
    // Past the threshold distance the target alpha fades out towards the maximum distance; else both alphas are the
    // component's.
    bool fullAlpha = true;
    if (distance > cpnt->m_fShadowDistanceThreshold) {
        const float range = cpnt->m_fShadowDistanceMax - cpnt->m_fShadowDistanceThreshold;
        if (range != 0.0f) {
            const float faded = (static_cast<float>(cpnt->m_ShadowColor[3]) * (cpnt->m_fShadowDistanceMax - distance)) / range;
            m_cTargetColor[3] = static_cast<uint8_t>(ppc::fctiwz(faded));
            fullAlpha = false;
        }
    }
    if (fullAlpha) {
        const uint8_t alpha = cpnt->m_ShadowColor[3];
        m_cColor[3] = alpha;
        m_afColor[3] = static_cast<float>(alpha);
        m_cTargetColor[3] = cpnt->m_ShadowColor[3];
    }
    std::memcpy(color, m_cColor, 4);
    const CKSrvShadow::CTexCoord* lo = service->GetUVMin(cpnt->m_ui8IndexTexture);  // 0x1facc8
    uv[1] = lo->m_fV;
    uv[0] = lo->m_fU;
    const CKSrvShadow::CTexCoord* hi = service->GetUVMax(cpnt->m_ui8IndexTexture);  // 0x1face0
    uv[2] = hi->m_fU;
    uv[3] = hi->m_fV;

    // The normal turns towards its target at m_fUnk48 per second (scalable game time).
    float dt = clock->m_afDeltaTime[IKTime::SCALABLE_GAME_TIME];
    if (m_v3c.x != m_v30.x || m_v3c.y != m_v30.y || m_v3c.z != m_v30.z) {
        const float dx = m_v30.x - m_v3c.x;
        const float dy = m_v30.y - m_v3c.y;
        const float dz = m_v30.z - m_v3c.z;
        const float step = dt * m_fUnk48;
        const float d2 = ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy));
        if (step * step > d2) {
            m_v3c.z = m_v30.z;
            m_v3c.x = m_v30.x;
            m_v3c.y = m_v30.y;
        } else {
            const float k = step * rwInvSqrt(d2);  // Math_InvSqrtf 0x114d8
            m_v3c.z = ppc::fmadds(dz, k, m_v3c.z);
            m_v3c.x = ppc::fmadds(dx, k, m_v3c.x);
            m_v3c.y = ppc::fmadds(dy, k, m_v3c.y);
        }
        dt = clock->m_afDeltaTime[IKTime::SCALABLE_GAME_TIME];
    }
    // The colour moves towards the target colour at m_fUnk1c x 255 per second.
    if (std::memcmp(m_cColor, m_cTargetColor, 4) == 0) return 0;
    const float dg = static_cast<float>(m_cTargetColor[1]) - m_afColor[1];
    const float dr = static_cast<float>(m_cTargetColor[0]) - m_afColor[0];
    const float db = static_cast<float>(m_cTargetColor[2]) - m_afColor[2];
    const float da = static_cast<float>(m_cTargetColor[3]) - m_afColor[3];
    const float step = (dt * m_fUnk1c) * 255.0f;  // TOC1 -0x118c
    const float d2 = ppc::fmadds(da, da, ppc::fmadds(db, db, ppc::fmadds(dr, dr, dg * dg)));
    if (step * step > d2) {
        std::memcpy(m_cColor, m_cTargetColor, 4);  // the float colour is left as it is
        return 0;
    }
    const float k = step * rwInvSqrt(d2);  // Math_InvSqrtf 0x114d8
    m_afColor[0] = ppc::fmadds(dr, k, m_afColor[0]);
    m_afColor[3] = ppc::fmadds(da, k, m_afColor[3]);
    m_afColor[1] = ppc::fmadds(dg, k, m_afColor[1]);
    m_afColor[2] = ppc::fmadds(db, k, m_afColor[2]);
    for (int i = 0; i < 4; ++i) m_cColor[i] = static_cast<uint8_t>(ppc::fctiwz(m_afColor[i]));
    return 0;
}
