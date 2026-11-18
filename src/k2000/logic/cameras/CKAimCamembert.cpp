// CKAimCamembert.cpp - reconstructed original translation unit 0x5bdfd8-0x5bed60 (GAME_TOC2, main_toc2), 21 functions, 18 live.
// Primary class: CKAimCamembert  key 0x9b4c  category Logic  size ?  vtable 0xb2f918
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x5bdfd8  CKAimCamembert_Delete
//   [ ] 0x5be028  CKAimCamembert_Construct  [dead]
//   [x] 0x5be038  CKAimCamembert_vf54  (CKAimCamembert::ScoreBestOfTwo)
//   [x] 0x5be118  CKAimCamembert_vf58  (CKAimCamembert::SetReference)
//   [ ] 0x5be178  RegisterCKAimCamembertClass
//   [ ] 0x5be1f0  _GLOBAL__I_5be1f0
//   [x] 0x5be200  CKAimCamembert_DeleteArray
//   [x] 0x5be2a0  CKAimCamembert_vf60
//   [x] 0x5be2f0  CKAimCamembert_SetOriginAndDirection_maybe
//   [ ] 0x5be3d0  CKAimCamembert_Construct_2  [dead]
//   [x] 0x5be3e0  CKAimCamembert_ScoreTarget_maybe
//   [x] 0x5be760  CKAimCamembert_CreateArray
//   [x] 0x5be7f0  CKAimCamembert_Create
//   [x] 0x5be828  CKAimCamembert_RecursiveRegistration  (returns 1: the default slot)
//   [x] 0x5be830  CKAimCamembert_PostLoad  (CKAimCamembert.h)
//   [x] 0x5be878  CKAimCamembert_Destroy  (empty: the default slot)
//   [x] 0x5be880  CKAimCamembert_Destructor  (C++ destructor chain: vtable stores only)
//   [ ] 0x5be8a0  CKAimCamembert_Destructor_2  [dead]
//   [x] 0x5be8c0  CKAimCamembert_Load
//   [ ] 0x5beb18  CKAimCamembert_Save
//   [x] 0x5bed18  CKAimCamembert_DeletingDestructor  (the destructor; delete)
//
//   [ ] 0x9cd148  CKAimCamembert_GetClassType  [inline]
//   [ ] 0x9cd150  CKAimCamembert_GetClassID  [inline]
//   [ ] 0x9cd158  CKAimCamembert_IsKindOfClass  [inline]
//   [ ] 0x9cd190  KBase9B0C_DeletingDestructor  [inline]
//   [ ] 0x9cd1d0  KBase9B0C_vf0  [inline]
#include "k2000/logic/cameras/CKAimCamembert.h"

#include "k2000/io/IKFile.h"

#include <cmath>
#include <cstring>

#include "crt/ppc_ops.h"
#include "crt/xtanf.h"
#include "k2000/math/Math.h"
#include "k2000/math/Vec3.h"

// 0x005be8c0 CKAimCamembert_Load
int32_t CKAimCamembert::Load(IKFile* file, int32_t type) {
    if (type == K_LEVEL_PLATEFORMS) {
        for (float& v : m_afUnk04) ReadF32LE(file, &v);
    }
    return 1;
}

// 0x005be2a0 CKAimCamembert_vf60
void CKAimCamembert::ResetAim() {
    m_pUnk20 = nullptr;
    m_vOrigin = CVector3{0.0f, 0.0f, 0.0f};     // TOC2 -0x6214: 0x00c50d64
    m_vDirection = CVector3{1.0f, 0.0f, 0.0f};  // TOC2 -0x6210: 0x00c50d34, the X axis (a static initialiser's)
    m_unk3c = 0;
}

// 0x005be2f0 CKAimCamembert_SetOriginAndDirection_maybe: reset (vt+0x60), the origin, then the direction unless it is
// still the null vector (compared part by part).
void CKAimCamembert::SetOriginAndDirection(const CVector3* origin, const CVector3* direction) {
    ResetAim();  // vt+0x60
    m_vOrigin = *origin;
    if (m_vDirection.x != 0.0f || m_vDirection.y != 0.0f || m_vDirection.z != 0.0f) m_vDirection = *direction;
}

// 0x005be3e0 CKAimCamembert_ScoreTarget_maybe: the sector from the origin along the direction (the reference object's while
// +0x3c), with the apex moved back by half the width / tan(half the angle) when the angle is not 180. The point's yaw from
// the aim must be within half the opening angle; along the direction turned by that yaw about Y it must be between
// [1] and [2] (past the moved apex) and within [4] of that line. Its score is the inverse of the distance part
// ((along - [1]) x [5] / ([2] - [1])) plus the angle part (yaw x [6] / [0]).
uint8_t CKAimCamembert::ScoreTarget(const CVector3* point, float* score) {
    *score = -1.0f;  // TOC2 -0x620c
    CVector3 origin;
    CVector3 direction;
    if (m_unk3c != 0 && m_pUnk20 != nullptr) {
        const uint8_t* object = reinterpret_cast<const uint8_t*>(m_pUnk20);
        std::memcpy(&direction, object + 0x20, sizeof direction);
        std::memcpy(&origin, object + 0x30, sizeof origin);
    } else {
        origin = m_vOrigin;
        direction = m_vDirection;
    }
    {
        const float length = std::sqrt(ppc::fmadds(direction.z, direction.z, ppc::fmadds(direction.x, direction.x,
                                                                                         direction.y * direction.y)));
        if (length != 0.0f) {  // TOC2 -0x61ec
            const float inverse = 1.0f / length;  // TOC2 -0x6208
            direction.z = direction.z * inverse;
            direction.x = direction.x * inverse;
            direction.y = direction.y * inverse;
        }
    }
    const float width = m_afUnk04[3];
    float apexBack = 0.0f;  // f27
    if (width != 0.0f && m_afUnk04[0] != 180.0f) {  // TOC2 -0x6204
        const float half = crt::Tanf(m_afUnk04[0] * 0.5f * 0.0174532905f);  // TOC2 -0x6200 / -0x61fc, tanf 0x780a90
        apexBack = (width * 0.5f) / half;
        const float back = -apexBack;
        origin.z = ppc::fmadds(back, direction.z, origin.z);
        origin.x = ppc::fmadds(back, direction.x, origin.x);
        origin.y = ppc::fmadds(back, direction.y, origin.y);
    }
    CVector3 toPoint{point->x - origin.x, point->y - origin.y, point->z - origin.z};
    const float pointYaw = Vec3_GetYawAngleFromZ(&toPoint);   // 0x00244528 (TocBridge)
    const float aimYaw = Vec3_GetYawAngleFromZ(&direction);
    const float yaw = (pointYaw - aimYaw) * 57.2957802f;      // TOC2 -0x61f8
    float angle = std::fabs(yaw);                             // the sign bit cleared
    if (angle > 180.0f) angle = 360.0f - angle;               // TOC2 -0x61f4
    if (m_afUnk04[0] * 0.5f < angle) return 0;                // bge: unordered passes
    CVector3 aim = direction;
    CVector3 axisY{0.0f, 1.0f, 0.0f};  // TOC2 -0x61f0: 0x00c50d40, the Y axis
    CVector3 turned;
    Vec3_RotateTowardByAngle(&turned, &aim, &axisY, yaw * 0.0174532905f);  // 0x005841a8
    const float along = ppc::fmadds(turned.z, toPoint.z, ppc::fmadds(turned.x, toPoint.x, turned.y * toPoint.y));
    if (apexBack + m_afUnk04[2] < along) return 0;
    if (apexBack + m_afUnk04[1] > along) return 0;
    const float dy = ppc::fmadds(turned.y, along, origin.y) - point->y;
    const float dx = ppc::fmadds(turned.x, along, origin.x) - point->x;
    const float dz = ppc::fmadds(turned.z, along, origin.z) - point->z;
    const float distance = std::sqrt(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));
    if (m_afUnk04[4] < distance) return 0;
    const float range = (along - apexBack - m_afUnk04[1]) * m_afUnk04[5] / (m_afUnk04[2] - m_afUnk04[1]);
    *score = 1.0f / (range + angle * m_afUnk04[6] / m_afUnk04[0]);
    return 1;
}

// 0x005be038 CKAimCamembert_vf54
uint8_t CKAimCamembert::ScoreBestOfTwo(const CVector3* a, const CVector3* b, float* score) {
    float scoreA;
    float scoreB = -1.0f;  // BUG(original): unset on the PS3 when `a` is inside
    if (ScoreTarget(a, &scoreA) == 0 && ScoreTarget(b, &scoreB) == 0) return 0;  // vt+0x50
    float best = scoreA;
    if (!(scoreA > scoreB)) best = scoreB;  // ble: NaN takes it
    *score = best;
    return 1;
}
