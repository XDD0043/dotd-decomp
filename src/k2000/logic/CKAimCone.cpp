// Reconstructed original translation unit: 0x5bed60-0x5bf8d8 (GAME_TOC2, main_toc2), 21 functions, 18 live.
// Primary class: CKAimCone  key 0x9c0c  category Logic  size ?  vtable 0xb2f9f0
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x5bed60  CKAimCone_Delete  (registry factory: DOTD_DECLARE_FACTORIES)
//   [ ] 0x5bedb0  CKAimCone_Construct  [dead]
//   [x] 0x5bedc0  CKAimCone_vf54
//   [x] 0x5beea0  CKAimCone_vf58
//   [ ] 0x5bef00  RegisterCKAimConeClass
//   [ ] 0x5bef78  _GLOBAL__I_5bef78
//   [x] 0x5bef88  CKAimCone_DeleteArray  (registry factory: DOTD_DECLARE_FACTORIES)
//   [x] 0x5bf030  CKAimCone_vf60
//   [x] 0x5bf080  CKAimCone_vf5C
//   [ ] 0x5bf120  CKAimCone_Construct_2  [dead]
//   [x] 0x5bf130  CKAimCone_CreateArray  (registry factory: DOTD_DECLARE_FACTORIES)
//   [x] 0x5bf1c8  CKAimCone_Create  (registry factory: DOTD_DECLARE_FACTORIES)
//   [x] 0x5bf200  CKAimCone_RecursiveRegistration  (returns 1: the root's empty slot)
//   [x] 0x5bf208  CKAimCone_PostLoad
//   [x] 0x5bf250  CKAimCone_Destroy  (empty)
//   [x] 0x5bf258  CKAimCone_ScoreTarget_maybe
//   [ ] 0x5bf478  CKAimCone_Destructor_2  [dead]
//   [x] 0x5bf498  CKAimCone_DeletingDestructor  (C++ deleting destructor)
//   [x] 0x5bf4e0  CKAimCone_Destructor  (C++ destructor chain: vtable stores only)
//   [x] 0x5bf500  CKAimCone_Load
//   [ ] 0x5bf710  CKAimCone_Save
//
//   [ ] 0x9cd1e8  CKAimCone_GetClassType  [inline]
//   [ ] 0x9cd1f0  CKAimCone_GetClassID  [inline]
//   [ ] 0x9cd1f8  CKAimCone_IsKindOfClass  [inline]
#include "k2000/logic/CKAimCone.h"

#include <cmath>

#include "Renderware/rwcore/RwMatrix.h"
#include "crt/ppc_ops.h"
#include "crt/xatan.h"
#include "k2000/io/IKFile.h"

namespace {
// 0x00010690 Math_Sqrtf (through its TocBridge 0x98fc10; fsqrts).
inline float MathSqrtf(float x) { return std::sqrt(x); }
}  // namespace

// 0x005bf500 CKAimCone_Load
int32_t CKAimCone::Load(IKFile* file, int32_t type) {
    if (type == 0) {
        for (float& v : m_afUnk04) ReadF32LE(file, &v);
    }
    return 1;
}

// 0x005bf208 CKAimCone_PostLoad
int32_t CKAimCone::PostLoad(int32_t /*type*/) {
    ResetAim();  // vt+0x60
    return 1;
}

// 0x005bf030 CKAimCone_vf60
void CKAimCone::ResetAim() {
    m_pMatrix = nullptr;
    m_vOrigin = CVector3{0.0f, 0.0f, 0.0f};     // 0x00c50d64
    m_vDirection = CVector3{1.0f, 0.0f, 0.0f};  // 0x00c50d34
    m_unk38 = 0;
}

// 0x005beea0 CKAimCone_vf58
void CKAimCone::FollowMatrix(const RwMatrix* matrix) {
    ResetAim();  // vt+0x60
    m_pMatrix = matrix;
    m_unk38 = 1;
}

// 0x005bf080 CKAimCone_vf5C
void CKAimCone::SetOriginAndDirection(const CVector3* origin, const CVector3* direction) {
    ResetAim();  // vt+0x60
    m_vOrigin = *origin;
    m_vDirection = *direction;
}

// 0x005bedc0 CKAimCone_vf54. BUG(original): when the first point is in the cone the second is not scored, yet its score's
// stack slot is compared (ble: the larger kept); DOTD: that slot starts at -1, so the first point's score is kept.
uint8_t CKAimCone::ScoreBestOfTwo(const CVector3* first, const CVector3* second, float* score) {
    float a = -1.0f;
    float b = -1.0f;
    if (ScoreTarget(first, &a) == 0 && ScoreTarget(second, &b) == 0) return 0;  // vt+0x50
    *score = (a <= b) ? b : a;
    return 1;
}

// 0x005bf258 CKAimCone_ScoreTarget_maybe: the cone from the origin along the direction (normalised; the matrix's at and
// position while +0x38). The point's angle from the aim (Math_Acosf 0x780c90 of the clamped cosine) must be within half
// the opening angle (bge: a NaN angle passes) and its distance within [2]..[3]; its score is the inverse of the distance
// part ((distance - [2]) x [4] / ([3] - [2])) plus the angle part (angle x [5] / [0]).
uint8_t CKAimCone::ScoreTarget(const CVector3* point, float* score) {
    *score = -1.0f;  // TOC2 -0x61b4
    float dx0;
    float dy0;
    float dz0;
    float ox;
    float oy;
    float oz;
    if (m_unk38 != 0 && m_pMatrix != nullptr) {
        dz0 = m_pMatrix->at.z;
        oz = m_pMatrix->pos.z;
        ox = m_pMatrix->pos.x;
        oy = m_pMatrix->pos.y;
        dx0 = m_pMatrix->at.x;
        dy0 = m_pMatrix->at.y;
    } else {
        dx0 = m_vDirection.x;
        ox = m_vOrigin.x;
        oz = m_vOrigin.z;
        dz0 = m_vDirection.z;
        oy = m_vOrigin.y;
        dy0 = m_vDirection.y;
    }
    const float length = MathSqrtf(ppc::fmadds(dz0, dz0, ppc::fmadds(dx0, dx0, dy0 * dy0)));
    if (length != 0.0f) {
        const float inv = 1.0f / length;
        dz0 = dz0 * inv;
        dx0 = dx0 * inv;
        dy0 = dy0 * inv;
    }
    const float dy = point->y - oy;
    const float dx = point->x - ox;
    const float dz = point->z - oz;
    const float distanceSq = ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy));
    const float dot = ppc::fmadds(dz, dz0, ppc::fmadds(dx, dx0, dy * dy0));
    float cosine = dot / MathSqrtf(distanceSq);
    if (cosine < -1.0f || cosine == -1.0f) {
        cosine = -1.0f;
    } else if (cosine > 1.0f || cosine == 1.0f) {
        cosine = 1.0f;
    }
    const float angle = crt::Acosf(cosine);  // 0x00780c90 Math_Acosf
    if (m_afUnk04[0] * 0.5f < angle) return 0;
    const float distance = MathSqrtf(distanceSq);
    if (distance > m_afUnk04[3]) return 0;
    if (distance < m_afUnk04[2]) return 0;
    const float nearDist = m_afUnk04[2];
    const float part = (distance - nearDist) * m_afUnk04[4] / (m_afUnk04[3] - nearDist);
    *score = 1.0f / (part + angle * m_afUnk04[5] / m_afUnk04[0]);
    return 1;
}
