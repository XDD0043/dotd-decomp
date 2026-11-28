// Reconstructed original translation unit: 0x317200-0x31b368 (GAME_TOC1, main_toc1), 26 functions, 15 live.
// Primary class: CKHkS08Hero  key 0x25c2  category Hook  size 0x1e00  vtable 0xb22c98
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x317200  FUN_00317200  [dead]
//   [ ] 0x3172b0  FUN_003172b0  [dead]
//   [ ] 0x3172f0  FUN_003172f0  [dead]
//   [ ] 0x317328  KStub_Nop_317328  [dead]
//   [ ] 0x317330  FUN_00317330  [dead]
//   [ ] 0x317360  FUN_00317360  [dead]
//   [ ] 0x317380  FUN_00317380  [dead]
//   [x] 0x3174b0  CKHkS08Hero_ComputeGroundBrakeForce_maybe
//   [x] 0x317658  CKHkS08Hero_ComputeGroundInputForce_maybe
//   [ ] 0x317bf0  FUN_00317bf0  [dead]
//   [x] 0x317cc0  CKHkS08Hero_AccumulateGroundDisplacement_maybe
//   [x] 0x317e68  CKHkS08Hero_LocoState3_TakeOffToPartner_Condition
//   [x] 0x317e90  CKHkS08Hero_LocoState4_Ground_Condition
//   [ ] 0x317eb8  FUN_00317eb8  [dead]
//   [x] 0x317f18  StaticInitAndDestruction_317f18  (the two file statics at the end)
//   [ ] 0x317f48  _GLOBAL__D_317f48
//   [ ] 0x317f58  _GLOBAL__I_317f58
//   [ ] 0x317f68  FUN_00317f68  [dead]
//   [ ] 0x318390  FUN_00318390  [dead]
//   [x] 0x318538  CKHkS08Hero_ComputeJumpImpulseForce_maybe
//   [x] 0x318758  CKHkS08Hero_ComputeGroundMoveDirection_maybe
//   [x] 0x3189a8  CKHkS08Hero_UpdateGroundMovement_maybe
//   [x] 0x319110  CKHkS08Hero_ComputeGroundRunForce_maybe
//   [x] 0x319420  CKHkS08Hero_DynamicStage1Ground_maybe
//   [x] 0x319a10  CKHkS08Hero_LocoState4_Ground
//   [x] 0x31a040  CKHkS08Hero_UpdateGroundLocomotionState_maybe
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include <cmath>
#include <cstring>
#include "k2000/animation/AnimBlendSlot.h"
#include "k2000/misc/FloatApproach.h"
#include "k2000/misc/Mat4.h"
#include "k2000/math/Vec3.h"
#include "k2000/core/Stub.h"
#include "Spyro2008/groups/C22SpyroShims.h"
#include "Renderware/rwcore/RwCamera.h"
#include "crt/ppc_ops.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/services/CKSrvDynamic.h"
#include "k2000/services/ICollisionMesh.h"
#include "k2000/math/Math.h"
#include "Spyro2008/groups/CKGrpS08Hero.h"
#include "crt/xsinf.h"

namespace {
// 0x00c50d7c: the shared down vector (0, -1, 0) (zero in the EBOOT's BSS; StaticInitAndDestruction_11578 fills it).
constexpr CVector3 kHeroDown{0.0f, -1.0f, 0.0f};

// A float stored with stfs into a member typed as a 32-bit word (or already a float).
template <class T>
void StoreF32(T& word, float value) {
    static_assert(sizeof(T) == 4, "a 32-bit member");
    std::memcpy(&word, &value, 4);
}

bool SignBitSet(float x) {
    int32_t bits;
    std::memcpy(&bits, &x, 4);
    return bits < 0;
}
}  // namespace

// 0x003174b0 CKHkS08Hero_ComputeGroundBrakeForce_maybe: with +0xec4 bit 24, a move speed +0x1378, or (no speed) a combo
// or +0xed4 bit 6 unless +0xec4 bit 21: the brake along the facing +0x1288 ramping from -+0xa8c (at rest) to -+0xa90 (at
// the top speed) with `speed` / the top speed; then, with +0xec8 bit 17 (+0x1444) or +0xec4 bit 24 (6.0), the pull of
// the vertical velocity +0x1280 back to 0.
CVector3 CKHkS08Hero::ComputeGroundBrakeForce(float speed) {
    const CVector3& zero = kHeroZeroVector;  // TOC +0x23a4
    CVector3 out = zero;
    bool brake;
    if ((m_unkec4 & 0x1000000u) != 0 || m_unk1378 != 0.0f) {
        brake = true;
    } else if (IsAnyComboKindActive() != 0 || (m_ui32StatusFlagsED4 & 0x40u) != 0) {  // 0x002fd030
        brake = (m_unkec4 & 0x200000u) == 0;
    } else {
        brake = false;
    }
    if (brake) {
        const float ratio = speed / GetMaxGroundSpeed();  // 0x002f94b0 inlined: +0x11f8 with +0xec8 bit 26, else +0xaf4
        const float low = m_unka8c;
        const float factor = ppc::fnmadds(ratio, m_unka90 - low, low);
        out.z = ppc::fmadds(factor, m_unk1290, out.z);
        out.x = ppc::fmadds(factor, m_unk1288, out.x);
        out.y = ppc::fmadds(factor, m_unk128c, out.y);
    }
    float stiffness;
    if ((m_unkec8 & 0x20000u) != 0) {
        stiffness = AsF32(m_unk1444);
    } else if ((m_unkec4 & 0x1000000u) != 0) {
        stiffness = 6.0f;  // TOC +0x23a8
    } else {
        return out;
    }
    const float pull = zero.y - m_unk1280;
    out.x = out.x + 0.0f;  // TOC +0x238c
    out.z = out.z + 0.0f;
    out.y = ppc::fmadds(pull, stiffness, out.y);
    return out;
}

// 0x00317658 CKHkS08Hero_ComputeGroundInputForce_maybe: the drive along the facing +0x1288 from the stick's force
// (`force`, the forces summed so far) on the ground (not with +0x1511). Its gain is the part of the force along the
// ground normal +0x564 times the move kind's factor (+0xa7c / +0xa80 / +0xa84 for +0x150a / +0x1508 / +0x1509, 1 when
// the force points less along the facing; +0xa88 when moving (+0x1378 above 0.1); the slope's +0xb80 / +0xb84 with
// +0xec4 bit 17; +0x89c (over the extra mass +0x1b2c with +0xed4 bit 0) during a combo). Above the top speed +0xaf4 it
// is scaled by the speed ratio; above the limit (+0xaf0, the slope's +0xb88) it is kept whole (projected on the
// node's right axis when moving, unless +0xec4 bit 10); below it, while still or with bit 10, it is scaled by the
// velocity after one step along the facing over the limit. A drive against the velocity after the step is dropped.
CVector3 CKHkS08Hero::ComputeGroundInputForce(float dt, const CVector3* force) {
    const CVector3& zero = kHeroZeroVector;  // TOC +0x23a4
    CVector3 out = zero;
    if (m_unk1511 == 0) {
        const float fx = force->x;
        const float fy = force->y;
        const float fz = force->z;
        const float alongNormal = ppc::fmadds(fz, m_unk56c, ppc::fmadds(fx, m_unk564, fy * m_unk568));
        float scale = 0.0f;  // TOC +0x238c
        if (m_unk150a != 0) scale = m_unka7c;
        if (m_unk1508 != 0) scale = m_unka80;
        if (m_unk1509 != 0) scale = m_unka84;
        const float alongFacing = ppc::fmadds(fz, m_unk1290, ppc::fmadds(fx, m_unk1288, fy * m_unk128c));
        constexpr float kStill = 0.1f;  // TOC +0x23ac
        bool moving;
        // The two layouts of the compare differ for NaN only: blt (no move kind / 0x150a / 0x1508), bge-else (0x1509).
        const bool below = m_unk1509 != 0 ? !(alongFacing >= scale * alongNormal) : (alongFacing < scale * alongNormal);
        if (below) {
            scale = 1.0f;  // TOC +0x2390
            moving = !(m_unk1378 <= kStill);
        } else {
            moving = m_unk1378 > kStill;
        }
        if (moving) scale = m_unka88;
        if ((m_unkec4 & 0x20000u) != 0) scale = m_unk12d0 < m_unkb88 ? m_unkb80 : m_unkb84;
        if (IsAnyComboKindActive() != 0) {  // 0x002fd030
            scale = (m_ui32StatusFlagsED4 & 1u) != 0 ? m_unk89c / m_fExtraMass : m_unk89c;
        }
        const float drive = scale * alongNormal;
        const float speed = m_unk12d0;
        const float topSpeed = m_unkaf4;
        float limit;
        bool overTop;
        if ((m_unkec4 & 0x20000u) != 0) {
            limit = m_unkb88;
            overTop = !(speed <= topSpeed);
        } else {
            limit = m_unkaf0;
            overTop = speed > topSpeed;
        }
        bool belowTop = true;
        if (overTop) {
            if (m_unk1378 <= kStill || (m_unkec4 & 0x400u) != 0) belowTop = false;
        }
        if (!belowTop) {
            float ratio = 1.0f;  // TOC +0x2390
            if (topSpeed != 0.0f) ratio = speed / topSpeed;
            const float k = ratio * drive;
            out.z = ppc::fmadds(k, m_unk1290, out.z);
            out.x = ppc::fmadds(k, m_unk1288, out.x);
            out.y = ppc::fmadds(k, m_unk128c, out.y);
        } else if (limit < speed) {
            out.z = ppc::fmadds(drive, m_unk1290, out.z);
            out.x = ppc::fmadds(drive, m_unk1288, out.x);
            out.y = ppc::fmadds(drive, m_unk128c, out.y);
            bool project;
            if (m_unk1378 <= kStill) {
                project = IsAnyComboKindActive() != 0;  // 0x002fd030
            } else {
                project = true;
            }
            if (project && (m_unkec4 & 0x400u) == 0) {
                const RwMatrix& m = static_cast<const CSGMovable*>(m_pKGLObject)->m_pRwFrame->modelling;
                const float dot = ppc::fmadds(m.right.z, out.z, ppc::fmadds(m.right.x, out.x, m.right.y * out.y));
                out.z = ppc::fmadds(m.right.z, dot, zero.z);
                out.x = ppc::fmadds(m.right.x, dot, zero.x);
                out.y = ppc::fmadds(m.right.y, dot, zero.y);
            }
        } else if (m_unk1378 <= kStill || (m_unkec4 & 0x400u) != 0) {
            const CVector3 copy = *force;
            const CVector3 step = ScaleVec3(dt, &copy);  // 0x0030f8c0
            const float vy = m_unk1280 + step.y;
            const float vx = m_unk127c + step.x;
            const float vz = m_unk1284 + step.z;
            const float along = ppc::fmadds(vz, m_unk1290, ppc::fmadds(vx, m_unk1288, vy * m_unk128c));
            float k = limit == 0.0f ? along / kStill : along / limit;
            k = k * drive;
            out.z = ppc::fmadds(k, m_unk1290, out.z);
            out.x = ppc::fmadds(m_unk1288, k, out.x);
            out.y = ppc::fmadds(k, m_unk128c, out.y);
        }
    }
    const float nx = ppc::fmadds(zero.x + out.x, dt, m_unk127c);
    const float ny = ppc::fmadds(zero.y + out.y, dt, m_unk1280);
    const float nz = ppc::fmadds(zero.z + out.z, dt, m_unk1284);
    const float dot = ppc::fmadds(m_unk1284, nz, ppc::fmadds(m_unk127c, nx, m_unk1280 * ny));
    if (!(dot >= 0.0f)) out = zero;
    return out;
}

// 0x00317cc0 CKHkS08Hero_AccumulateGroundDisplacement_maybe: the step's displacement (the velocity +0x127c and the
// animation's root motion, ComputeTimedAnimDisplacement, times `dt`, plus the external displacement) added to +0x1268;
// +0xec8 bit 20 = +0xedc bit 9 and +0xec8 bit 1; then the speed stats.
void CKHkS08Hero::AccumulateGroundDisplacement(float dt) {
    const CVector3& zero = kHeroZeroVector;  // TOC +0x23a4
    const float vx = m_unk127c;
    const float vy = m_unk1280;
    const float vz = m_unk1284;
    const CVector3 anim = ComputeTimedAnimDisplacement(dt);  // 0x00311950
    if ((m_unkedc & 0x200u) != 0 && (m_unkec8 & 2u) != 0) {
        m_unkec8 = (m_unkec8 & ~0x100000u) | 0x100000u;
    } else {
        m_unkec8 &= ~0x100000u;
    }
    const CVector3 external = GetExternalDisplacement();  // 0x0030fe18
    const float ax = ppc::fmadds(dt, anim.x, zero.x);
    const float px = ppc::fmadds(dt, vx, zero.x);
    const float az = ppc::fmadds(dt, anim.z, zero.z);
    const float ay = ppc::fmadds(dt, anim.y, zero.y);
    const float py = ppc::fmadds(dt, vy, zero.y);
    const float pz = ppc::fmadds(dt, vz, zero.z);
    m_unk1268 = ((px + ax) + external.x) + m_unk1268;
    m_unk126c = ((py + ay) + external.y) + m_unk126c;
    m_unk1270 = ((pz + az) + external.z) + m_unk1270;
    UpdateForwardAndSpeedStats();  // 0x00310d88
}

// 0x00317e68 CKHkS08Hero_LocoState3_TakeOffToPartner_Condition: ShouldJoinPartnerFlight.
uint8_t CKHkS08Hero::LocoTakeOffToPartnerCondition(IKTime*, uint8_t) { return ShouldJoinPartnerFlight(); }

// 0x00317e90 CKHkS08Hero_LocoState4_Ground_Condition: on the ground (movement mode 0).
uint8_t CKHkS08Hero::LocoGroundCondition(IKTime*, uint8_t) { return IsMovementMode0(); }

// 0x00319a10 CKHkS08Hero_LocoState4_Ground: the locomotion state on foot. Entering and leaving reset the ground
// locomotion's state (+0x150b..+0x1513, +0x17f0, +0x17fc, the slide vector +0x14f8, the facing +0x1288 from the node's
// frame) and flags; each frame the velocity (+0x127c) is kept off the ground's normal (+0x564), the push plane
// (+0x61c), the wall (+0x514) and the tether, redirected along +0x11ec, and pulled back toward +0x135c.
uint8_t CKHkS08Hero::LocoGround(IKTime*, int32_t phase, uint8_t other) {
    const CVector3& zero = kHeroZeroVector;  // TOC +0x23a4 -> 0x00c50d64
    if (phase == 1) {
        m_unk17f0 = zero.x;
        m_unk17f4 = zero.y;
        m_unk17f8 = zero.z;
        m_unkec4 = (m_unkec4 & 0xfffffffeu) | 1u;
        m_unk368 = (m_unk368 & 0xffffffdfu) | 0x20u;
        m_unk150b = 1;
        m_unk151c = 0.0f;
        m_unk150c = 0;
        m_unk150d = 0;
        m_unk150e = 0;
        m_unk1512 = 0;
        m_unk1513 = 0;
        m_unk1520 = kHeroAxisY.x;  // 0x00c50d40 (TOC +0x2404)
        m_unk1528 = kHeroAxisY.z;
        m_unk1524 = kHeroAxisY.y;
        const RwFrame* frame = static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame;
        m_unk1288 = frame->modelling.at.x;
        m_unk1290 = frame->modelling.at.z;
        m_unk128c = frame->modelling.at.y;
        ComputeCameraRelativeMove();  // 0x00311df0
        if ((m_unkec4 & 0x20000u) == 0) m_ui32HeroFlags35C = (m_ui32HeroFlags35C & 0x7fffffffu) | 0x80000000u;
        static_cast<CKSrvDynamic*>(g_pEngine->m_srvDynamic)->SetEntryFlag(this, 1);  // 0x0023aff8
        m_unk1505 = 0;
        m_unk1507 = 0;
        m_unk14f8 = zero.x;
        m_unk14fc = zero.y;
        m_unk1500 = zero.z;
        m_unk1506 = 0;
        if (((m_ui32HeroFlags354 & 1u) != 0 && m_unk510 > 0.001f) || m_i16CurAnimIndex == 0x55) {  // 0x00361c00 GetFloat510; TOC +0x2430
            m_unk1511 = 1;
        } else {
            m_unk1511 = 0;
        }
        m_unkec8 &= 0xffffff7fu;
        m_unk368 = (m_unk368 & 0xfffffeffu) | 0x100u;
        m_unk17fc = zero.x;
        m_unk1800 = zero.y;
        m_unk1804 = zero.z;
        m_ui32HeroFlags35C &= 0xffffff7fu;
        return other;
    }
    if (phase == 2) {
        m_unk17f0 = zero.x;
        m_unk17f4 = zero.y;
        m_unk17f8 = zero.z;
        m_unk1507 = 0;
        m_unkec4 = (m_unkec4 & 0xfffffffeu) | 1u;
        m_unk368 = (m_unk368 & 0xffffffdfu) | 0x20u;
        m_ui32HeroFlags35C &= 0x7fffffffu;
        m_unkec8 &= 0xffffff7fu;
        m_unk368 &= 0xfffffeffu;
        return other;
    }
    if (phase != 0) return other;
    UpdateSlopeAngleAndFlagEC8Bit24();  // 0x002f9540
    if (m_unk1511 == 0 && m_unk1518 == 0) {
        const float dot = ppc::fmadds(m_unk1284, m_unk56c, ppc::fmadds(m_unk127c, m_unk564, m_unk1280 * m_unk568));
        if (dot < 0.0f) {  // TOC +0x238c
            const float push = -dot;
            const float vx = m_unk127c;
            const float vy = m_unk1280;
            m_unk1284 = ppc::fmadds(push, m_unk56c, m_unk1284);
            m_unk127c = ppc::fmadds(m_unk564, push, vx);
            m_unk1280 = ppc::fmadds(push, m_unk568, vy);
        }
    }
    // The speed (Math_Sqrtf 0x00010690 of the velocity's square length) is computed and not used.
    (void)c22spyro::MathSqrtf(ppc::fmadds(m_unk1284, m_unk1284, ppc::fmadds(m_unk127c, m_unk127c, m_unk1280 * m_unk1280)));
    ApplyPartnerTetherToVelocity();  // 0x003105d8
    if ((m_ui32HeroFlags354 & 0x40000u) != 0) {
        float x = m_wallSlide.m_v3Normal.x;  // +0x61c
        float y = m_wallSlide.m_v3Normal.y;
        float z = m_wallSlide.m_v3Normal.z;
        const float length = static_cast<float>(c22spyro::MathSqrtf(ppc::fmadds(z, z, ppc::fmadds(x, x, y * y))));
        if (length != 0.0f) {
            const float inverse = 1.0f / length;  // TOC +0x2390
            z = z * inverse;
            x = x * inverse;
            y = y * inverse;
        }
        const float dot = ppc::fmadds(z, m_unk1284, ppc::fmadds(x, m_unk127c, y * m_unk1280));
        if (dot < 0.0f) {
            const float push = -dot;
            const float vy = m_unk1280;
            m_unk1284 = ppc::fmadds(z, push, m_unk1284);
            m_unk127c = ppc::fmadds(x, push, m_unk127c);
            m_unk1280 = ppc::fmadds(y, push, vy);
        }
    }
    if ((m_unk368 & 0x80u) != 0) {
        const float dot = ppc::fmadds(m_unk51c, m_unk1284, ppc::fmadds(m_unk127c, m_unk514, m_unk518 * m_unk1280));
        if (dot < 0.0f) {
            m_unk1284 = m_unk1284 - m_unk51c * dot;
            m_unk127c = m_unk127c - m_unk514 * dot;
            m_unk1280 = m_unk1280 - m_unk518 * dot;
        }
    }
    if (m_unk11ec != zero.x || m_unk11f0 != zero.y || m_unk11f4 != zero.z) {
        const float speed = static_cast<float>(
            c22spyro::MathSqrtf(ppc::fmadds(m_unk1284, m_unk1284, ppc::fmadds(m_unk127c, m_unk127c, m_unk1280 * m_unk1280))));
        const float dz = m_unk11f4;
        const float dx = m_unk11ec;
        const float dy = m_unk11f0;
        m_unk11f4 = zero.z;
        m_unk11ec = zero.x;
        m_unk11f0 = zero.y;
        m_unk1284 = speed * dz;
        m_unk127c = speed * dx;
        m_unk1280 = speed * dy;
    }
    {
        const CVector3 push = ComputePairedHotspotCollisionResponse(m_unka44);  // 0x00310888
        m_unk17fc = push.x;
        m_unk1804 = push.z;
        m_unk1800 = push.y;
    }
    if ((m_ui32StatusFlagsED0 & 2u) != 0) {
        float vx = m_unk127c;
        float vz = m_unk1284;
        const float dot = ppc::fmadds(vz, m_unk1364, ppc::fmadds(vx, m_unk135c, m_unk1360 * 0.0f));
        if (dot < 0.0f) {
            const float length = static_cast<float>(c22spyro::MathSqrtf(ppc::fmadds(vz, vz, ppc::fmadds(vx, vx, 0.0f))));
            float vy = 0.0f;
            if (length != 0.0f) {
                const float inverse = 1.0f / length;
                vz = vz * inverse;
                vx = vx * inverse;
                vy = inverse * 0.0f;
            }
            m_unk127c = ppc::fmadds(dot, vx, m_unk127c);
            m_unk1280 = ppc::fmadds(dot, vy, m_unk1280);
            m_unk1284 = ppc::fmadds(dot, vz, m_unk1284);
        }
    }
    return other;
}

// 0x003189a8 CKHkS08Hero_UpdateGroundMovement_maybe: the hero node's matrix on the ground. The position (+0x54c) takes
// the blended velocity of +0xec8 bits 13 / 18 once (bit 25; the animations 0x27 / 0x28), an identity at the position is
// turned by the yaw +0x538 (stepped towards the move direction: by the turn rate of the move kind, or by the speed-based
// ramp +0x1198), its up is the body tilt springs' (towards the Y axis with +0x1511, else the blend of the ground normal
// +0x564 and the radial ground probe's), and the basis goes into the node (CSGMovable_SetLocalMatrix).
void CKHkS08Hero::UpdateGroundMovement(float dt) {
    constexpr float kPi = 3.14159274101257324f;     // TOC1 +0x2418
    constexpr float kTwoPi = 6.28318548202514648f;  // TOC1 +0x241c
    CVector3* const position = reinterpret_cast<CVector3*>(&m_unk54c);
    // The once-only push of the animations 0x27 / 0x28 (+0xec8 bit 25 when done).
    {
        const uint32_t flags = m_unkec8;
        bool checkSlot = false;
        bool push = false;
        if ((flags & 0x40000u) != 0) {
            if (m_i16CurAnimIndex == 0x27) {
                checkSlot = true;
            } else if ((flags & 0x2000000u) == 0) {
                push = true;
            }
        } else if ((flags & 0x2000u) != 0) {
            checkSlot = true;
        }
        if (push) {
            *position = ComputeBlendedVelocityFromFlagsEC8(position, 1.39999997615814209f, 1.0f);  // TOC1 +0x2414
            uint32_t value = (m_unkec8 & ~0x4000u) | 0x4000u;
            value = (value & ~0x2000000u) | 0x2000000u;
            m_unkec8 = value;
        } else if (checkSlot) {
            AnimBlendSlot* slot = GetAnimBlendSlot();  // vt+0x194
            if (slot->m_unk14 == 0 && m_i16CurAnimIndex == 0x28 && (m_unkec8 & 0x2000000u) == 0) {
                m_unkec8 = (m_unkec8 & ~0x4000u) | 0x4000u;
                *position = ComputeBlendedVelocityFromFlagsEC8(position, 1.39999997615814209f, 1.0f);
                m_unkec8 = (m_unkec8 & ~0x2000000u) | 0x2000000u;
            }
        }
    }
    CMatrix34 matrix;
    matrix.m_at.z = 1.0f;
    matrix.m_ui32Flags = 0x20003;
    matrix.m_up.y = 1.0f;
    matrix.m_right.x = 1.0f;
    matrix.m_up.x = 0.0f;
    matrix.m_right.z = 0.0f;
    matrix.m_right.y = 0.0f;
    matrix.m_at.y = 0.0f;
    matrix.m_at.x = 0.0f;
    matrix.m_up.z = 0.0f;
    matrix.m_pos.z = 0.0f;
    matrix.m_pos.y = 0.0f;
    matrix.m_pos.x = 0.0f;
    matrix.m_pos.x = position->x;
    matrix.m_pos.z = position->z;
    matrix.m_pos.y = position->y;
    matrix.m_ui32Flags &= ~0x20000u;
    const CVector3 direction = ComputeGroundMoveDirection();  // 0x00318758
    // The turn rate of the move kind.
    float turnRate = 0.0f;
    if (m_unk1507 == 0 || m_unk1518 != 0) {
        if (m_unk1505 != 0) {
            turnRate = IsAnyComboKindActive() != 0 ? m_unk8c0 : m_unkb0c;
        } else if (m_unk1506 != 0) {
            turnRate = IsAnyComboKindActive() != 0 ? m_unk8bc : m_unkb10;
        } else if (m_unk1d10 != 0) {
            turnRate = m_unk1d14;
        } else if ((m_unkec8 & 0x80u) != 0) {
            turnRate = m_unk8b4;
        } else {
            turnRate = (m_unkec4 & 0x20000u) != 0 ? m_unkb8c : m_unkaf8;
        }
    }
    const float yaw = Vec3_GetYawAngleFromX(&direction);  // 0x00244638
    if ((m_unkec4 & 0x1000u) == 0) {
        const bool steered = (m_unkec8 & 0x80u) != 0;
        if (!steered && m_unk1378 == 0.0f) {
            if (m_unk1505 != 0 || m_unk1506 != 0) {
                m_unk538 = Angle_StepTowardInDirection(m_unk538, yaw, turnRate, dt, 1);  // 0x002f8520
            } else {
                m_unk1198 = 0.0f;
            }
        } else if (m_unk1505 != 0 || m_unk1506 != 0) {
            m_unk538 = Angle_StepTowardInDirection(m_unk538, yaw, turnRate, dt, 1);
        } else if (steered) {
            float approach[3] = {yaw, turnRate, m_unk538};
            FloatApproach_StepAngle(dt, approach);  // 0x00243748 (returns approach[2])
            m_unk538 = approach[2];
        } else {
            // The speed-based turn: the angle left (the short way, signed by the side of the node's right row the move
            // direction is on) per dt, clamped to the turn rate and scaled by the speed's remap; the turn speed +0x1198
            // ramps towards it.
            float bits = yaw - m_unk538;
            float left = std::fabs(bits);  // the sign bit cleared in memory
            if (!(left <= kPi)) left = kTwoPi - left;
            const RwFrame* frame = static_cast<const CSGMovable*>(m_pKGLObject)->m_pRwFrame;
            const float side = ppc::fmadds(direction.z, frame->modelling.right.z,
                                           ppc::fmadds(direction.x, frame->modelling.right.x, direction.y * frame->modelling.right.y));
            if (side > 0.0f) left = -left;
            const float wanted = left / dt;
            float clamped;
            if (wanted <= -turnRate) {
                clamped = -turnRate;
            } else if (turnRate <= wanted) {
                clamped = turnRate;
            } else {
                clamped = wanted;
            }
            const float rampSpeed = Math_RemapClamped(0.0f, GetMaxGroundSpeed(), m_unk12d0, m_unkafc, m_unkb00);  // 0x00333618
            const float scale = Math_RemapClamped(0.0f, GetMaxGroundSpeed(), m_unk12d0, m_unkb04, m_unkb08);
            float approach[3] = {clamped * scale, rampSpeed, m_unk1198};
            const float turnSpeed = FloatApproach_Step(dt, approach);  // 0x002436e8
            float angle = ppc::fmadds(dt, turnSpeed, m_unk538);
            m_unk1198 = turnSpeed;
            m_unk538 = angle;
            if (!(angle >= 0.0f)) {
                do {
                    angle = angle + kTwoPi;
                } while (angle < 0.0f);
            }
            while (angle >= kTwoPi) angle = angle - kTwoPi;
            m_unk538 = angle;
        }
    }
    Mat4_RotateLocalYDeg((1.57079637050628662f - m_unk538) * 57.2957801818847656f, &matrix);  // TOC1 +0x23fc / +0x2420
    CVector3 target;
    if (m_unk1511 != 0) {
        target = kHeroAxisY;  // TOC1 +0x2404
    } else {
        const uint8_t count = m_unkacc;
        const CVector3 radial = GroundProbe_ComputeRadialAverageNormal(position, reinterpret_cast<const CVector3*>(&m_unk12a0),
                                                                       m_unkac8, m_unkad0, m_unkad4, count);  // 0x002fa6a8
        target = BlendGroundNormals(reinterpret_cast<const CVector3*>(&m_unk564), &radial, 1.0f,
                                    static_cast<float>(static_cast<double>(count)));  // 0x002f8958
        const float length = std::sqrt(ppc::fmadds(target.z, target.z, ppc::fmadds(target.x, target.x, target.y * target.y)));
        if (length != 0.0f) {
            const float inv = 1.0f / length;
            target.z = target.z * inv;
            target.x = target.x * inv;
            target.y = target.y * inv;
        }
    }
    CSGMovable* node = static_cast<CSGMovable*>(m_pKGLObject);
    const CVector3 current{node->m_pRwFrame->modelling.up.x, node->m_pRwFrame->modelling.up.y, node->m_pRwFrame->modelling.up.z};
    const CVector3 up = UpdateBodyTiltSprings(&current, &target);  // 0x002fbfc0
    if (!Mat4_BuildFromUpAndForward(&matrix, &up, &matrix.m_at)) {
        // The original passes the matrix itself as the `at` (its right row).
        Mat4_SetBasisFromUpAt(&matrix, &up, &matrix.m_right);
    }
    node->SetLocalMatrix(reinterpret_cast<const RwMatrix*>(&matrix));  // 0x000d0be8
}

// 0x00318758 CKHkS08Hero_ComputeGroundMoveDirection_maybe: the direction the model faces on the ground, normalised: the
// move direction +0x37c (the input's +0x1288 while it is weak (+0x12cc < 0.1) or with +0x1511 below the speed +0xbc8,
// unless a combo runs), the run direction +0x12a0 when the speed +0x1378 is not above +0xbc8 or +0x1ac7 is set, the
// direction +0x11cc with +0xec8 bit 7, the attack direction +0x14f8 (taken from -+0x135c once, +0x1504) during the
// combo moves +0x1505 / +0x1506 (+0x1507 without +0x1518: not).
CVector3 CKHkS08Hero::ComputeGroundMoveDirection() {
    const float limit = m_unkbc8;
    CVector3 d;
    bool move = true;
    if (m_unk12cc < 0.1f) {  // TOC1 +0x23ac
        move = false;
    } else if (m_unk1511 != 0 && !(m_unk1378 <= limit)) {
        move = false;
    }
    if (!move && IsAnyComboKindActive() != 0) move = true;
    if (move) {
        d = {m_unk37c, m_unk380, m_unk384};
    } else {
        d = {m_unk1288, m_unk128c, m_unk1290};
    }
    if (m_unk1378 <= limit || m_unk1ac7 != 0) d = {m_unk12a0, m_unk12a4, m_unk12a8};
    if ((m_unkec8 & 0x80u) != 0) d = {m_unk11cc, m_unk11d0, m_unk11d4};
    if (!(m_unk1507 != 0 && m_unk1518 == 0)) {
        bool attack = false;
        if (m_unk1505 != 0) {
            attack = true;
        } else if (m_unk1506 != 0) {
            attack = true;
        }
        if (attack) {
            if (m_unk1504 != 0) {
                m_unk1504 = 0;
                m_unk14f8 = -m_unk135c;
                m_unk14fc = -m_unk1360;
                m_unk1500 = -m_unk1364;
            }
            d = {m_unk14f8, m_unk14fc, m_unk1500};
        }
    }
    const float length = std::sqrt(ppc::fmadds(d.z, d.z, ppc::fmadds(d.x, d.x, d.y * d.y)));  // Math_Sqrtf 0x10690
    if (length != 0.0f) {
        const float inv = 1.0f / length;  // TOC1 +0x2390
        d.z = inv * d.z;
        d.x = inv * d.x;
        d.y = inv * d.y;
    }
    return d;
}

// 0x00318538 CKHkS08Hero_ComputeJumpImpulseForce_maybe: the jump's push along +0x1520 while the jump runs (+0x150e):
// the impulse of the jump kind +0x1539 (1: +0xa94, 2: +0xa98 times the hold factor +0x153c, 3: +0xa9c), scaled by the
// mass over the mass without the extra mass with +0xed4 bit 0; on the jump's first step (+0x1512) the direction is the
// Y axis times UpdateAndGetField11C8; on the step the timer +0x151c ran out (+0x1513) only its part of the step counts;
// x1.15 for a hero following another (+0x25 != +0x24).
CVector3 CKHkS08Hero::ComputeJumpImpulseForce(float dt) {
    CVector3 out = kHeroZeroVector;  // TOC +0x23a4
    float impulse;
    const uint8_t kind = m_unk1539;
    if (kind == 2) {
        impulse = m_unka98 * AsF32(m_unk153c);
    } else if (kind == 3) {
        impulse = m_unka9c;
    } else if (kind == 1) {
        impulse = m_unka94;
    } else {
        impulse = 0.0f;  // TOC +0x238c
    }
    if ((m_ui32StatusFlagsED4 & 1u) != 0) {
        const float mass = GetMass();  // 0x002f8818
        const float extra = (m_ui32StatusFlagsED4 & 1u) != 0 ? m_fExtraMass : 0.0f;
        impulse = impulse * (mass / (mass - extra));
    }
    if (m_unk1512 != 0) {
        m_unk1520 = kHeroAxisY.x;  // 0x00c50d40 (TOC +0x2404)
        m_unk1524 = kHeroAxisY.y;
        m_unk1528 = kHeroAxisY.z;
        const float k = UpdateAndGetField11C8();  // 0x00310330
        m_unk1520 = k * m_unk1520;
        m_unk1528 = k * m_unk1528;
        m_unk1524 = k * m_unk1524;
    }
    float f = impulse;
    if (m_unk1513 != 0) f = impulse * ((dt + m_unk151c) / dt);
    if (m_unk150e != 0) {
        out.x = ppc::fmadds(f, m_unk1520, out.x);
        out.z = ppc::fmadds(f, m_unk1528, out.z);
        out.y = ppc::fmadds(f, m_unk1524, out.y);
    }
    if (m_ui8Hero != m_ui8TrackedLeader) {
        constexpr float kFollowerBoost = 1.14999997615814209f;  // TOC +0x2408 (0x3f933333)
        out.x = out.x * kFollowerBoost;
        out.y = out.y * kFollowerBoost;
        out.z = out.z * kFollowerBoost;
    }
    return out;
}

// 0x00319110 CKHkS08Hero_ComputeGroundRunForce_maybe: unless +0x1508, the run force along +0x12b8: from +0xa8c to
// +0xa90 by the move speed +0x1378 (on a slope, +0xec4 bit 17, both scaled by +0xb98 / +0xb9c, or +0xba0 / +0xba4 above
// the slope angle +0xbd4); while running fast (+0x150d) in the air (+0x1511) or jumping (+0x150e) the direction is
// flattened (projected on the Y axis' plane, normalised). A follower (+0x25 != +0x24) gets x1.5 on steep slopes
// (+0x11c4 above 40) or when the pair is apart further than the group's +0x108 and it is on the ground.
CVector3 CKHkS08Hero::ComputeGroundRunForce() {
    CVector3 out = kHeroZeroVector;  // TOC +0x23a4
    if (m_unk1508 != 0) return out;
    float low = m_unka8c;
    float high = m_unka90;
    if ((m_unkec4 & 0x20000u) != 0) {
        if (m_unk11c4 > m_unkbd4) {
            low = low * AsF32(m_unkba0);
            high = high * m_unkba4;
        } else {
            low = low * AsF32(m_unkb98);
            high = high * m_unkb9c;
        }
    }
    const float f = low + ppc::fmadds(high - low, m_unk1378, 0.0f);  // TOC +0x238c
    if (m_unk150d == 0) {
        out.z = ppc::fmadds(f, m_unk12c0, out.z);
        out.x = ppc::fmadds(f, m_unk12b8, out.x);
        out.y = ppc::fmadds(f, m_unk12bc, out.y);
    } else {
        CVector3 dir{m_unk12b8, m_unk12bc, m_unk12c0};
        if (m_unk1511 != 0 || m_unk150e != 0) {
            const CVector3 flat = Vec3_ProjectOnPlane(&kHeroAxisY, &dir);  // 0x005840d0 (TOC +0x2404)
            dir = flat;
            const float length = std::sqrt(ppc::fmadds(flat.z, flat.z, ppc::fmadds(flat.x, flat.x, flat.y * flat.y)));
            if (length != 0.0f) {
                const float inverse = 1.0f / length;  // TOC +0x2390
                dir.z = flat.z * inverse;
                dir.x = flat.x * inverse;
                dir.y = flat.y * inverse;
            }
        }
        out.x = ppc::fmadds(f, dir.x, out.x);
        out.y = ppc::fmadds(f, dir.y, out.y);
        out.z = ppc::fmadds(f, dir.z, out.z);
    }
    if (m_ui8Hero != m_ui8TrackedLeader) {
        const CKGrpS08Hero* group = static_cast<const CKGrpS08Hero*>(m_pGrpHero);
        const float distance0 = AsF32(group->m_unk2d4[16]);  // +0x314
        const float distance1 = AsF32(group->m_fHero1ToMidDist);      // +0x318
        bool boost;
        if (m_unk11c4 <= 40.0f) {  // TOC +0x2424
            // 0x002ce518 CKGrpS08Hero_GetMaxPartnerDistance_maybe (+0x108)
            boost = !(distance1 + distance0 <= group->m_unk108) && (m_ui32HeroFlags354 & 1u) == 0;
        } else {
            boost = true;
        }
        if (boost) {
            constexpr float kFollowerBoost = 1.5f;  // TOC +0x2428
            out.z = out.z * kFollowerBoost;
            out.x = out.x * kFollowerBoost;
            out.y = out.y * kFollowerBoost;
        }
    }
    return out;
}

// 0x00319420 CKHkS08Hero_DynamicStage1Ground_maybe: one fixed step of the ground dynamics. The jump timer +0x151c runs
// down (+0x1513 on the step it runs out; +0x150e cleared once it is out); the forces are summed into +0x17f0: gravity
// (the down vector times +0x1b18 / +0x11d8 / +0xa78) times the mass, the stick's drive (unless +0xec8 bit 5), the jump
// impulse, the run force and the brake (by the flags), the lunge from the animation marks, the external push, the partner
// tether's spring and damping, the game manager's force (times +0xac4 unless +0xec4 bit 24) and the push between the
// heroes +0x17fc; over the mass and times `dt` it goes into the velocity +0x127c (unless +0xec8 bit 24; +0xec8 bits 9 /
// 10 clear its y / its x and z); then the step's displacement.
void CKHkS08Hero::DynamicStage1Ground(float dt) {
    const CVector3& zero = kHeroZeroVector;  // TOC +0x23a4
    ComputeCameraRelativeMove();  // 0x00311df0
    m_unk1513 = 0;
    const float timer = m_unk151c;
    if (timer <= 0.0f) {  // TOC +0x238c
        m_unk150e = 0;
    } else {
        const float left = timer - dt;
        m_unk151c = left;
        if (left <= 0.0f) m_unk1513 = 1;
    }
    const float mass = GetMass();  // 0x002f8818
    m_unk17f0 = zero.x;
    m_unk17f8 = zero.z;
    m_unk17f4 = zero.y;
    float gravity;
    if ((m_unkec4 & 0x8000000u) != 0) {
        gravity = m_unk1b18;
    } else if ((m_unkec8 & 0x100u) != 0) {
        gravity = AsF32(m_unk11d8);
    } else {
        gravity = m_unka78;
    }
    {
        const CVector3 accel{kHeroDown.x * gravity, kHeroDown.y * gravity, kHeroDown.z * gravity};  // TOC +0x2388
        const CVector3 f = AccelToForce(mass, &accel);  // 0x0030fb68
        m_unk17f0 = f.x + m_unk17f0;
        m_unk17f4 = f.y + m_unk17f4;
        m_unk17f8 = f.z + m_unk17f8;
    }
    if ((m_unkec8 & 0x20u) == 0) {
        const CVector3 sum{m_unk17f0, m_unk17f4, m_unk17f8};
        const CVector3 f = ComputeGroundInputForce(dt, &sum);  // 0x00317658
        m_unk17f0 = f.x + m_unk17f0;
        m_unk17f4 = f.y + m_unk17f4;
        m_unk17f8 = f.z + m_unk17f8;
    }
    {
        const CVector3 f = ComputeJumpImpulseForce(dt);  // 0x00318538
        m_unk17f0 = f.x + m_unk17f0;
        m_unk17f4 = f.y + m_unk17f4;
        m_unk17f8 = f.z + m_unk17f8;
    }
    if ((m_unkec4 & 0x800u) == 0 && (m_unk1511 != 0 || (m_unkec4 & 0x20000u) == 0)) {
        const CVector3 f = ComputeGroundRunForce();  // 0x00319110
        m_unk17f0 = f.x + m_unk17f0;
        m_unk17f4 = f.y + m_unk17f4;
        m_unk17f8 = f.z + m_unk17f8;
    }
    if ((m_unkec4 & 0x2000u) == 0 && (m_unk1511 != 0 || (m_unkec4 & 0x20000u) == 0)) {
        const CVector3 brake = ComputeGroundBrakeForce(m_unk12d0);  // 0x003174b0
        const CVector3 f = ClampDragToStopVelocity(dt, &brake, reinterpret_cast<const CVector3*>(&m_unk127c));  // 0x00311c50
        m_unk17f0 = m_unk17f0 + f.x;
        m_unk17f4 = m_unk17f4 + f.y;
        m_unk17f8 = m_unk17f8 + f.z;
    }
    {
        const CVector3 f = StartLungeFromMark(dt);  // 0x003008d8
        m_unk17f0 = f.x + m_unk17f0;
        m_unk17f4 = f.y + m_unk17f4;
        m_unk17f8 = f.z + m_unk17f8;
    }
    {
        const CVector3 f = ComputeExternalPushForce(dt);  // 0x003011c8
        m_unk17f0 = f.x + m_unk17f0;
        m_unk17f4 = f.y + m_unk17f4;
        m_unk17f8 = f.z + m_unk17f8;
    }
    {
        const CKGrpS08Hero* group = static_cast<const CKGrpS08Hero*>(m_pGrpHero);
        const float dampingRadius = group->m_fTetherDampingRadius;
        const float dampingCoeff = group->m_fTetherDampingCoeff;
        const CVector3 spring = ComputePartnerTetherSpringForce(group->m_fTetherSpringRadius, group->m_fTetherSpringStiffness);  // 0x003103f0
        const CVector3 damping = ComputePartnerTetherDampingForce(dampingRadius, dampingCoeff);    // 0x0030fe70
        const float sx = spring.x + m_unk17f0;
        const float sy = spring.y + m_unk17f4;
        const float sz = spring.z + m_unk17f8;
        m_unk17f0 = damping.x + sx;
        m_unk17f4 = damping.y + sy;
        m_unk17f8 = damping.z + sz;
    }
    {
        CVector3 e = GetGameManagerExternalForce();  // 0x0030f8f0
        if ((m_unkec4 & 0x1000000u) == 0) {
            const float s = m_unkac4;
            e.z = e.z * s;
            e.x = e.x * s;
            e.y = e.y * s;
        }
        float ax = e.x + m_unk17f0;
        float ay = e.y + m_unk17f4;
        float az = e.z + m_unk17f8;
        m_unk17f0 = ax;
        m_unk17f4 = ay;
        m_unk17f8 = az;
        ax = ax + m_unk17fc;
        az = az + m_unk1804;
        ay = ay + m_unk1800;
        m_unk17f0 = ax;
        m_unk17f8 = az;
        m_unk17f4 = ay;
    }
    const CVector3 sum{m_unk17f0, m_unk17f4, m_unk17f8};
    const CVector3 accel = ForceToAccel(dt, mass, &sum);  // 0x00310ba8
    const CVector3 delta = AccelToVelocityDelta(dt, &accel);  // 0x0030fb98
    if ((m_unkec8 & 0x1000000u) == 0) {
        m_unk127c = m_unk127c + delta.x;
        m_unk1280 = m_unk1280 + delta.y;
        m_unk1284 = m_unk1284 + delta.z;
    }
    if ((m_unkec8 & 0x200u) != 0) m_unk1280 = 0.0f;
    if ((m_unkec8 & 0x400u) != 0) {
        m_unk1284 = 0.0f;
        m_unk127c = 0.0f;
    }
    AccumulateGroundDisplacement(dt);  // 0x00317cc0
}

// 0x0031a040 CKHkS08Hero_UpdateGroundLocomotionState_maybe (the frame hook UpdateLocomotionByMode's ground case): the
// ground locomotion's decisions. +0x1511 (in the air: airborne with the ground more than 0.001 below, unless a dropping
// hero (+0x358 bit 20) without a jump and a combo) ends a jump (+0x1518) on the ground; the slope flag +0xec4 bit 17
// (a ground of property 2, or the slope angle +0x11c4 above +0xbd4); the speed bands walk / run / sprint (+0x150b /
// +0x150c / +0x150d) by the speed +0x12d0 and their thresholds; the move kinds +0x150a / +0x1508 / +0x1509 and the turn
// moves +0x1505 / +0x1506 (from the turn rate +0x1374); +0x35c bit 31; the stop request (+0xec4 bit 11); then the jump
// start (the jump count +0x1538 against the maximum +0xab0, the kinds 1 / 2 / 3 with their timers +0xaa0..+0xaa8, the
// hold factor +0x153c from the vertical speed), the fall to flying (SetMovementModeUnlessLocked), the fall kind
// +0x1530, the flags +0x1514 / +0x1517 / +0xec4 bit 24, the jump clock +0x1534, the take-off point +0x125c, and the
// ground probe (ProbeGroundAndUpdateLocomotionFlags).
void CKHkS08Hero::UpdateGroundLocomotionState() {
    // The in-air flag +0x1511.
    bool inAir = false;
    if ((m_ui32HeroFlags354 & 1u) != 0 && m_gcCurDatasInOut.m_fdH > 0.001f) {  // TOC +0x2430
        inAir = true;
        if (m_unk1538 == 0 && (m_ui32HeroFlags358 & 0x100000u) != 0 && IsAnyComboKindActive() == 0) inAir = false;  // 0x002fd030
    }
    if (inAir) {
        m_unk1506 = 0;
        m_unk1511 = 1;
        m_unk1507 = 0;
        m_unk1505 = 0;
    } else {
        m_unk1511 = 0;
        if (m_unk1518 != 0) {
            m_unk1518 = 0;
            m_unk1534 = 0;
            m_unk1539 = 0;
            m_unk1530 = 0;
            m_unk1538 = 0;
            m_unk1544 = -m_unk1280;
        }
    }
    // The slope flag +0xec4 bit 17.
    {
        const ICollisionMesh* ground = static_cast<const ICollisionMesh*>(GetGroundInfo());  // 0x00361b68
        const uint32_t cleared = m_unkec4 & ~0x20000u;
        m_unkec4 = cleared;
        if (ground != nullptr && (ground->m_ui16PropertiesFlags & 2u) != 0 && m_unk1511 == 0) m_unkec4 = cleared | 0x20000u;
    }
    if ((m_unkec4 & 0x20000u) == 0 && m_unkbd4 < m_unk11c4) m_unkec4 = (m_unkec4 & ~0x20000u) | 0x20000u;
    // The speed bands.
    const float speed = m_unk12d0;
    if ((m_unkec4 & 0x20000u) != 0) {
        m_unk150c = 0;
        if (m_unk150d == 0) {
            m_unk150b = 1;
            if (!(speed <= m_unkb90)) {
                m_unk150b = 0;
                m_unk150d = 1;
            }
        } else if (!(speed >= m_unkb94)) {
            m_unk150d = 0;
            m_unk150b = 1;
        }
    } else if (m_unk150b != 0) {
        m_unk150c = 0;
        m_unk150b = 1;
        m_unk150d = 0;
        if (!(speed <= m_unkad8)) {
            m_unk150b = 0;
            m_unk150c = 1;
        }
    } else if (m_unk150c != 0) {
        m_unk150b = 0;
        m_unk150c = 1;
        m_unk150d = 0;
        if (!(speed >= m_unkadc)) {
            m_unk150b = 1;
            m_unk150c = 0;
        }
        if (!(speed <= m_unkae0)) {
            m_unk150c = 0;
            m_unk150d = 1;
        }
    } else if (m_unk150d != 0) {
        m_unk150c = 0;
        m_unk150d = 1;
        m_unk150b = 0;
        if (!(speed >= m_unkae4)) {
            m_unk150d = 0;
            m_unk150c = 1;
        }
    }
    // The move kinds and the turn moves.
    const float turn = m_unk1374;
    m_unk1509 = 0;
    m_unk150a = 0;
    m_unk1508 = 0;
    if (turn <= 0.0f && (m_unk150d != 0 || m_unk150c != 0 || m_unk150b != 0) && !(m_unk12d0 <= 0.1f) &&
        (m_ui32HeroFlags358 & 0x100000u) == 0 && m_unk1518 == 0) {  // TOC +0x238c, +0x23ac
        m_unk150a = 1;
        bool turnMove = true;
        if (m_unk150d != 0) {
            const float limit = m_unkaec;
            if (m_unk1378 == 0.0f) {
                m_unk1508 = 1;
            } else if (!(turn >= -limit)) {
                m_unk1508 = 1;
            }
            if (!(turn >= -limit) && (m_unkec4 & 0x200u) == 0) {
                m_unk1509 = 1;
                turnMove = false;
            }
        }
        if (turnMove && !(turn >= -m_unkb14) && m_unk1506 == 0 && m_unk1505 == 0 && !(m_unk1378 <= m_unkb18) &&
            (m_unkec4 & 0x200u) == 0) {
            m_unk14f8 = -m_unk135c;
            m_unk14fc = -m_unk1360;
            m_unk1500 = -m_unk1364;
            m_unk1506 = 1;
            m_unk1504 = 1;
            m_unk1507 = 1;
        }
    }
    // +0x35c bit 31.
    {
        ICollisionMesh* ground = static_cast<ICollisionMesh*>(m_gcCurDatasInOut.m_pGround);
        const bool onMovingGround = ground != nullptr && ground->GetClassID() == 0x13;  // vt+0x18
        bool set;
        if ((m_unkec8 & 2u) != 0 && (m_unkec8 & 0x100000u) == 0) {
            set = true;
        } else if ((m_ui32StatusFlagsED4 & 2u) != 0) {
            set = true;
        } else if (m_unk1378 != 0.0f || onMovingGround) {
            if (m_unk150d != 0 && (m_unkec4 & 0x20000u) == 0) {
                set = true;
            } else {
                set = onMovingGround;
            }
        } else {
            set = false;
        }
        if (set) {
            m_ui32HeroFlags35C = (m_ui32HeroFlags35C & 0x7fffffffu) | 0x80000000u;
        } else {
            m_ui32HeroFlags35C &= 0x7fffffffu;
        }
    }
    if (m_unk1509 != 0 && m_unk1506 == 0 && m_unk1505 == 0 && !(m_unk1378 <= m_unkb18) && (m_unkec4 & 0x200u) == 0) {
        m_unk1507 = 1;
        m_unk14f8 = -m_unk135c;
        m_unk14fc = -m_unk1360;
        m_unk1500 = -m_unk1364;
        m_unk1505 = 1;
        m_unk1504 = 1;
    }
    // The stop request: a stick push (+0x388) on the ground with +0xec4 bit 15.
    if (!(AsF32(m_unk388) <= 0.0f) && m_unk1518 == 0 && (m_unkec4 & 0x8000u) != 0) {
        m_unkec4 = (m_unkec4 & ~0x800u) | 0x800u;
        m_unk394 = 0;
        m_unk1508 = 1;
    }
    // The jump start and the fall.
    m_unk1512 = 0;
    if ((m_unkec8 & 0x400u) == 0) {
        bool done = false;  // a path that goes on to 0x0031a340 / 0x0031a344 / 0x0031a350 without a jump
        bool jump = false;
        uint8_t jumps = 0;
        uint32_t dropping = m_ui32HeroFlags358 & 0x100000u;
        if (dropping != 0 && m_unk1538 == 2) {
            if (m_unkab0 != 0xff && m_unk150e == 0 && (m_unkec8 & 2u) == 0) {
                SetMovementModeUnlessLocked(1);  // 0x00342ef8
                dropping = m_ui32HeroFlags358 & 0x100000u;
            }
        }
        if (!(m_unk1260 - m_unk550 <= m_unkb7c) && dropping != 0 && m_unk150e == 0 && (m_unkec8 & 2u) == 0) {
            SetMovementModeUnlessLocked(1);  // 0x00342ef8
            done = true;
        } else {
            bool test = false;  // 0x0031a310
            if (dropping == 0) {
                if (m_unk1304 == 0 && m_unk1305 != 0 && m_unk1538 == 0 && (m_unkec4 & 0x8000u) != 0) {
                    jumps = 0;
                    test = true;
                } else {
                    done = true;
                }
            } else {
                jumps = m_unk1538;
                test = true;
            }
            if (test) {
                bool tryJump;  // 0x0031a320
                if (AsF32(m_unk1534) <= m_unkaac) {
                    if (jumps != 0) {
                        done = true;
                        tryJump = false;
                    } else if (m_unk1518 != 0) {
                        done = true;
                        tryJump = false;
                    } else if (m_unk1511 == 0) {
                        tryJump = true;
                    } else if (m_unk1548 - m_unk790 >= m_unk20c) {
                        // 0x0031a350 directly.
                        done = true;
                        tryJump = false;
                    } else {
                        tryJump = true;
                    }
                } else {
                    tryJump = true;
                }
                if (tryJump) {
                    const int32_t maximum = static_cast<int8_t>(m_unkab0);
                    if (static_cast<int32_t>(jumps) < maximum || maximum == -1) {
                        if ((m_ui32HeroFlags354 & 0x800u) == 0 && (m_ui32HeroFlags35C & 2u) == 0 &&
                            !(jumps == 1 && static_cast<int32_t>(m_unkecc) < 0)) {
                            jump = true;
                        }
                    }
                    if (!jump) done = true;
                }
            }
        }
        if (jump) {
            m_unkec4 &= ~0x800u;
            SetDirectionLock(1);  // 0x009bdb48 inlined: SetCameraDirectionLock 0x00354cf0, +0x354 bit 0 set, bit 2 cleared
            const uint8_t count = m_unk1538;
            m_unk1518 = 1;
            m_unk1512 = 1;
            m_unk150e = 1;
            float timer;
            float scale;
            uint8_t base = count;
            if (count == 1) {
                m_unk1539 = 2;
                timer = m_unkaa4;
                scale = m_unkaa0;
            } else if (count == 0 && !(AsF32(m_unk1308) <= m_unkb1c) && (m_unkec4 & 0x8000u) != 0) {
                m_unk1539 = 3;
                timer = m_unkaa8;
                base = 1;
                scale = m_unkaa0;
                m_unk1538 = 1;
            } else {
                scale = m_unkaa0;
                m_unk1539 = 1;
                timer = scale;
            }
            m_unk151c = timer;
            m_unk1538 = static_cast<uint8_t>(base + 1);
            const float limit = (m_unka94 - m_unka78) * scale;
            const float vy = m_unk1280;
            float clamped;
            if (vy <= -limit) {
                clamped = -limit;
            } else if (vy >= limit) {
                clamped = limit;
            } else {
                clamped = vy;
            }
            const float angle = (clamped * 1.57079637050628662f) / limit;  // TOC +0x23fc
            // The inlined sinf (0x0031aa98..): the octant polynomials, a negative argument through -sin(-x).
            const float s = SignBitSet(angle) ? -crt::InlineSinf(-angle) : crt::InlineSinf(angle);
            m_unk1534 = 0;
            m_unk790 = -1000.0f;  // TOC +0x2434
            StoreF32(m_unk153c, (1.0f - s) * 0.5f);  // TOC +0x2390, +0x2400
        }
        (void)done;
    }
    // 0x0031a344 / 0x0031a350 (every path): the fall kind while in the air, by the vertical speed.
    if (m_unk1511 != 0) {
        const float vy = m_unk1280;
        if (m_unkb2c >= vy) {
            m_unk1530 = -m_unkb30 > vy ? 3 : 1;
        } else {
            m_unk1530 = 2;
        }
    }
    // +0x1517: running against the run direction from standing.
    float moveSpeed = m_unk1378;
    bool against = false;
    if (m_unk150a != 0) {
        const float dot =
            ppc::fmadds(m_unk1290, m_unk12a8, ppc::fmadds(m_unk1288, m_unk12a0, m_unk128c * m_unk12a4));
        if (!(dot >= 0.0f) && moveSpeed == 0.0f && !(m_unk12d0 <= 0.5f)) against = true;  // TOC +0x2400
    }
    m_unk1517 = against ? 1 : 0;
    uint8_t moving = m_unk1511;
    if (m_unk150e != 0 || m_unk150a != 0 || m_unk150c != 0 || m_unk150d != 0) moving = 1;
    m_unk1514 = moving;
    if (!(moveSpeed <= 0.0f)) m_unk1514 = 1;
    if (m_unk1518 != 0) StoreF32(m_unk1534, AsF32(m_unk1534) + m_unk88c);
    if (m_unk1511 == 0) {
        m_unk125c = m_unk54c;
        m_unk1264 = m_unk554;
        m_unk1260 = m_unk550;
    }
    bool hold = false;
    if (m_unkf08 == 3 && m_unk1539 == 2) {
        if ((m_unk1280 < 0.0f || (m_unkec4 & 0x1000000u) != 0) && m_unk1511 != 0 && m_unk150e == 0) hold = true;
    }
    if (hold) {
        m_unkec4 = (m_unkec4 & ~0x1000000u) | 0x1000000u;
    } else {
        m_unkec4 &= ~0x1000000u;
    }
    ProbeGroundAndUpdateLocomotionFlags();  // 0x003110a8
    if ((m_unkec8 & 0x400u) != 0) {
        m_unk1518 = 0;
        m_unk1534 = 0;
        m_unk1539 = 0;
        m_unk1530 = 0;
        m_unk1538 = 0;
    }
}

// 0x00317f18 StaticInitAndDestruction_317f18: two file statics (0x00ceae2c, 0x00ceae30) set to -1.0f. Nothing in the game
// reads them (their only references are the initialiser's TOC entries).
namespace {
[[maybe_unused]] float s_unkceae2c = -1.0f;
[[maybe_unused]] float s_unkceae30 = -1.0f;
}  // namespace
