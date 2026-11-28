// Reconstructed original translation unit: 0x31b368-0x31d3d8 (GAME_TOC1, main_toc1), 13 functions, 9 live.
// Primary class: CKHkS08Hero  key 0x25c2  category Hook  size 0x1e00  vtable 0xb22c98
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x31b368  FUN_0031b368  [dead]
//   [x] 0x31b450  CKHkS08Hero_AccumulateVelocityDisplacement_maybe
//   [ ] 0x31b520  FUN_0031b520  [dead]
//   [x] 0x31b608  StaticInitAndDestruction_31b608  (the two file statics at the end)
//   [ ] 0x31b638  _GLOBAL__D_31b638
//   [ ] 0x31b648  _GLOBAL__I_31b648
//   [x] 0x31b658  CKHkS08Hero_LocoState3_TakeOffToPartner
//   [x] 0x31b8c8  CKHkS08Hero_UpdateTakeOffToPartnerLocomotion_maybe
//   [ ] 0x31c1f0  FUN_0031c1f0  [dead]
//   [ ] 0x31c328  FUN_0031c328  [dead]
//   [x] 0x31c4d8  CKHkS08Hero_ComputeTakeOffToPartnerVelocity_maybe
//   [x] 0x31c788  CKHkS08Hero_DynamicStage1TakeOffToPartner_maybe
//   [x] 0x31ce28  CKHkS08Hero_UpdateTakeOffToPartnerMovement_maybe
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "k2000/hooks/CKHkClimbZone.h"
#include <cmath>
#include <cstring>
#include "Renderware/rwcore/RwCamera.h"
#include "Spyro2008/groups/CKGrpS08Hero.h"
#include "Spyro2008/hooks/HeroTimedImpulse.h"
#include "crt/ppc_ops.h"
#include "crt/xatan.h"
#include "k2000/core/Stub.h"
#include "k2000/math/Math.h"
#include "k2000/math/Vec3.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/FloatApproach.h"
#include "k2000/misc/Mat4.h"
#include "k2000/scenegraph/CSGMovable.h"

namespace {

constexpr float kPi = 3.14159274101257324f;        // TOC +0x24e0
constexpr float kTwoPi = 6.28318548202514648f;     // TOC +0x24e8
constexpr float kRadToDeg = 57.2957801818847656f;  // TOC +0x24b0
// 0x00c50d7c: the shared down vector (0, -1, 0) (zero in the EBOOT's BSS; StaticInitAndDestruction_11578 fills it).
constexpr CVector3 kHeroDown{0.0f, -1.0f, 0.0f};

const CVector3& Vec(const float& x) { return *reinterpret_cast<const CVector3*>(&x); }

float Length(float x, float y, float z) { return std::sqrt(ppc::fmadds(z, z, ppc::fmadds(x, x, y * y))); }  // Math_Sqrtf

// The node frame's rows (RwFrame +0x10 right, +0x20 up, +0x30 at).
const RwFrame* NodeFrame(IKSerializable* node) { return static_cast<const CSGMovable*>(node)->m_pRwFrame; }

}  // namespace

// 0x0031b450 CKHkS08Hero_AccumulateVelocityDisplacement_maybe (a CKSrvDynamic hook form without callers in DotD): the
// step's displacement (the velocity times `dt` plus the external displacement) added to +0x1268, then the speed stats.
void CKHkS08Hero::AccumulateVelocityDisplacement(float dt) {
    const CVector3& zero = kHeroZeroVector;  // TOC +0x2450
    const float z = ppc::fmadds(dt, m_unk1284, zero.z);
    const float x = ppc::fmadds(dt, m_unk127c, zero.x);
    const float y = ppc::fmadds(dt, m_unk1280, zero.y);
    const CVector3 external = GetExternalDisplacement();  // 0x0030fe18
    m_unk1270 = (z + external.z) + m_unk1270;
    m_unk1268 = (x + external.x) + m_unk1268;
    m_unk126c = (y + external.y) + m_unk126c;
    UpdateForwardAndSpeedStats();  // 0x00310d88
}

// 0x0031b658 CKHkS08Hero_LocoState3_TakeOffToPartner: the locomotion state taking off to join the partner in the air
// (state 3 throughout). Each frame the partner tether acts on the velocity, which loses 1.1 times its part into the wall
// touched (+0x354 bit 18, the raw wall normal +0x61c) and into +0x514 (+0x368 bit 7); the hero is airborne (the direction
// lock). Entering sets +0xec4 bit 0 and +0x368 bit 5, clears +0xec8 bit 7 and the push between the heroes +0x17fc;
// leaving clears +0xec8 bit 7 and stops the push record +0x156c.
uint8_t CKHkS08Hero::LocoTakeOffToPartner(IKTime*, int32_t phase, uint8_t) {
    const CVector3& zero = kHeroZeroVector;  // TOC +0x2450
    if (phase == 1) {
        m_unkec4 = (m_unkec4 & ~1u) | 1u;
        m_unk368 = (m_unk368 & ~0x20u) | 0x20u;
        m_unkec8 &= ~0x80u;
        m_unk17fc = zero.x;
        m_unk1804 = zero.z;
        m_unk1800 = zero.y;
        return 3;
    }
    if (phase == 2) {
        m_unkec8 &= ~0x80u;
        m_unk1578 = zero.x;
        m_unk1580 = zero.z;
        m_unk157c = zero.y;
        SetF32(m_unk1588, 0.0f);
        m_unk1574 = 0;
        SetF32(m_unk1584, 0.0f);
        return 3;
    }
    if (phase != 0) return 3;
    ApplyPartnerTetherToVelocity();  // 0x003105d8
    if ((m_ui32HeroFlags354 & 0x40000u) != 0) {
        const float nx = m_wallSlide.m_v3Normal.x;  // +0x61c
        const float ny = m_wallSlide.m_v3Normal.y;
        const float nz = m_wallSlide.m_v3Normal.z;
        const float vx = m_unk127c;
        const float vy = m_unk1280;
        const float vz = m_unk1284;
        const float d = ppc::fmadds(nz, vz, ppc::fmadds(nx, vx, ny * vy));
        if (d < 0.0f) {  // TOC +0x246c
            const float k = d * 1.10000002384185791f;  // TOC +0x2494
            m_unk1284 = vz - nz * k;
            m_unk127c = vx - nx * k;
            m_unk1280 = vy - ny * k;
        }
    }
    if ((m_unk368 & 0x80u) != 0) {
        const float nx = m_unk514;
        const float ny = m_unk518;
        const float nz = m_unk51c;
        const float vx = m_unk127c;
        const float vy = m_unk1280;
        const float vz = m_unk1284;
        const float d = ppc::fmadds(nz, vz, ppc::fmadds(vx, nx, ny * vy));
        if (d < 0.0f) {
            const float pz = (nz * d) * 1.10000002384185791f;
            const float px = (nx * d) * 1.10000002384185791f;
            const float py = (ny * d) * 1.10000002384185791f;
            m_unk1284 = vz - pz;
            m_unk127c = vx - px;
            m_unk1280 = vy - py;
        }
    }
    SetDirectionLock(1);  // 0x00354cf0 and the +0x354 bits
    return 3;
}

// 0x0031b8c8 CKHkS08Hero_UpdateTakeOffToPartnerLocomotion_maybe (the frame hook UpdateLocomotionByMode while joining the
// partner): the partner's plane normal +0x15e0 (its node's up; climbing: its right, or its at on a zone without flag
// 0x10; else zero), the tether direction (the group's +0x2fc / +0x308) projected on it gives the side +0x15d4 (the plane
// normal crossed with it, turned to the velocity's side) and +0x15f0 (it times the speed along it); the angle +0x1600
// between the gap to the partner (projected) and down (+0x1610 cleared when it falls back to 90 degrees); the turn axis
// +0x1604 (-+0x11b4 times Y x +0x15e0, its y = +0x11bc, normalised); then the side push: with +0x358 bit 20 or the timer
// +0x1618 out, a move, the timer +0x15ec out and fewer than two pushes (+0x1610), the push record +0x156c starts along
// the side tilted by +0xd58 degrees (+0x1614 alternates), +0x15ec = +0xd48, +0x1618 = 0.8, and +0x15fc below the partner.
void CKHkS08Hero::UpdateTakeOffToPartnerLocomotion(float dt) {
    const CVector3& zero = kHeroZeroVector;  // TOC +0x2450
    CKHkS08Hero* partner = GetPartnerHero();  // 0x002f85f8
    const uint32_t partnerMode = partner->m_unk1744;
    if (partnerMode == 0) {
        const RwFrame* frame = NodeFrame(partner->m_pKGLObject);
        m_unk15e0 = frame->modelling.up.x;
        m_unk15e4 = frame->modelling.up.y;
        m_unk15e8 = frame->modelling.up.z;
    } else if (partnerMode == 2) {
        const RwFrame* frame = NodeFrame(partner->m_pKGLObject);
        // The partner's climb zone without its flag 0x10 (+0x0c) gives the right row; no zone or the flag, the at row.
        const bool right = partner->m_pCurrentClimbZone != nullptr && (partner->m_pCurrentClimbZone->m_bitArray & 0x10u) == 0;
        const RwV3d& row = right ? frame->modelling.right : frame->modelling.at;
        m_unk15e0 = row.x;
        m_unk15e4 = row.y;
        m_unk15e8 = row.z;
    } else {
        m_unk15e0 = zero.x;
        m_unk15e4 = zero.y;
        m_unk15e8 = zero.z;
    }
    CVector3 tether = zero;
    const CKGrpS08Hero* group = static_cast<const CKGrpS08Hero*>(m_pGrpHero);
    if (m_ui8Hero == 0) {
        std::memcpy(&tether, &group->m_unk2d4[10], 12);  // +0x2fc
    } else if (m_ui8Hero == 1) {
        std::memcpy(&tether, &group->m_unk2d4[13], 12);  // +0x308
    }
    const CVector3& normal = Vec(m_unk15e0);
    CVector3 side = Vec3_ProjectOnPlane(&normal, &tether);  // 0x005840d0 (TocBridge)
    {
        const float length = Length(side.x, side.y, side.z);
        if (length != 0.0f) {
            const float inv = 1.0f / length;  // TOC +0x2468
            side.z = side.z * inv;
            side.x = side.x * inv;
            side.y = side.y * inv;
        }
    }
    const float cx = ppc::fmsubs(m_unk15e4, side.z, m_unk15e8 * side.y);
    m_unk15d4 = cx;
    const float cy = ppc::fmsubs(m_unk15e8, side.x, m_unk15e0 * side.z);
    m_unk15d8 = cy;
    const float cz = ppc::fmsubs(m_unk15e0, side.y, m_unk15e4 * side.x);
    m_unk15dc = cz;
    float along = ppc::fmadds(cz, m_unk1284, ppc::fmadds(cx, m_unk127c, cy * m_unk1280));
    if (along < 0.0f) {
        m_unk15d4 = -m_unk15d4;
        m_unk15d8 = -m_unk15d8;
        m_unk15dc = -m_unk15dc;
    }
    along = std::fabs(along);
    m_unk15f0 = along * m_unk15d4;
    m_unk15f8 = along * m_unk15dc;
    m_unk15f4 = along * m_unk15d8;
    // The angle between the gap to the partner and down.
    {
        const CVector3 gap{m_unk54c - partner->m_unk54c, m_unk550 - partner->m_unk550, m_unk554 - partner->m_unk554};
        CVector3 g = Vec3_ProjectOnPlane(&normal, &gap);  // 0x005840d0 (TocBridge)
        Length(g.x, g.y, g.z);  // Math_Sqrtf (computed up to three times; one answer used)
        const float length = Length(g.x, g.y, g.z);
        if (length != 0.0f) {
            const float inv = 1.0f / length;
            g.y = g.y * inv;
            g.z = g.z * inv;
            g.x = g.x * inv;
        }
        const float before = AsF32(m_unk1600);
        float c = ppc::fmadds(g.z, kHeroDown.z, ppc::fmadds(g.x, kHeroDown.x, g.y * kHeroDown.y));  // TOC +0x2464
        if (c <= -1.0f) {  // TOC +0x2474
            c = -1.0f;
        } else if (c >= 1.0f) {
            c = 1.0f;
        }
        const float angle = crt::Acosf(c);  // TocBridge_Math_Acosf
        SetF32(m_unk1600, angle);
        if (before * kRadToDeg > 90.0f && angle * kRadToDeg <= 90.0f) m_unk1610 = 0;  // TOC +0x24b4
    }
    // The turn axis +0x1604.
    {
        const CVector3& axis = kHeroAxisY;  // TOC +0x24b8 -> 0x00c50d40
        const float ax = ppc::fmsubs(axis.y, m_unk15e8, axis.z * m_unk15e4);
        m_unk1604 = ax;
        const float ay = ppc::fmsubs(axis.z, m_unk15e0, axis.x * m_unk15e8);
        const float k = -m_unk11b4;
        m_unk1608 = ay;
        const float sx = k * ax;
        const float sy = k * ay;
        const float az = ppc::fmsubs(axis.x, m_unk15e4, axis.y * m_unk15e0);
        m_unk1604 = sx;
        m_unk1608 = sy;
        const float sz = k * az;
        m_unk160c = sz;
        m_unk1608 = m_unk11bc;
        const float length = std::sqrt(ppc::fmadds(sz, sz, ppc::fmadds(sx, sx, m_unk1608 * m_unk1608)));  // Math_Sqrtf
        if (length != 0.0f) {
            const float inv = 1.0f / length;
            m_unk160c = inv * m_unk160c;
            m_unk1604 = inv * m_unk1604;
            m_unk1608 = inv * m_unk1608;
        }
    }
    // The side push's direction: the side, turned to the move (climbing partner) or to the turn axis.
    float wx = m_unk15d4;
    float wy = m_unk15d8;
    float wz = m_unk15dc;
    bool zeroSide = false;
    if (partner->m_unk1744 == 2) {
        const float d = ppc::fmadds(m_unk384, wz, ppc::fmadds(m_unk37c, wx, m_unk380 * wy));
        if (d < 0.0f) {
            wx = -wx;
            wy = -wy;
            wz = -wz;
        } else if (d == 0.0f) {
            zeroSide = true;
        }
    } else {
        const float d = ppc::fmadds(m_unk160c, wz, ppc::fmadds(m_unk1604, wx, m_unk1608 * wy));
        if (d < 0.0f) {
            wx = -wx;
            wy = -wy;
            wz = -wz;
        } else if (d == 0.0f) {
            zeroSide = true;
        }
    }
    if (zeroSide) {
        wy = zero.y;
        wx = zero.x;
        wz = zero.z;
    }
    // The tilt: the side's part along the (unflipped) cross product decides the direction (+0x1614 records it).
    const float e = ppc::fmadds(cz, wz, ppc::fmadds(cx, wx, cy * wy));
    float tilt;
    if (!(e < 0.0f)) {
        if (m_unk1614 != 0) m_unk1610 = 0;
        tilt = m_unkd58 * 1.74532905220985413e-2f;  // TOC +0x24bc
        m_unk1614 = 0;
    } else {
        if (m_unk1614 == 0) m_unk1610 = 0;
        m_unk1614 = 1;
        tilt = -(m_unkd58 * 1.74532905220985413e-2f);
    }
    float px;
    float py;
    float pz;
    if ((wx == zero.x && wy == zero.y && wz == zero.z) ||
        (m_unk15e0 == zero.x && m_unk15e4 == zero.y && m_unk15e8 == zero.z)) {
        pz = wz;
        py = wy;
        px = wx;
    } else {
        CVector3 up{wx, wy, wz};
        CVector3 at{m_unk15e0, m_unk15e4, m_unk15e8};
        const CVector3 tilted = Vec3_TiltUpVectorAroundLocalX(tilt, &up, &at);  // 0x002fbd78
        px = tilted.x;
        py = tilted.y;
        pz = tilted.z;
    }
    if (Length(px, py, pz) < 1.0e-1f || m_unk550 > partner->m_unk550) {  // TOC +0x24c0
        pz = m_unk15dc;
        px = m_unk15d4;
        py = m_unk15d8;
    }
    if (AsF32(m_unk15ec) > 0.0f) SetF32(m_unk15ec, AsF32(m_unk15ec) - dt);
    if ((m_ui32HeroFlags358 & 0x100000u) == 0 && m_unk1618 > 0.0f) return;
    if (m_unk1378 == 0.0f) return;
    if (!(AsF32(m_unk15ec) <= 0.0f)) return;
    const uint32_t pushes = m_unk1610;
    if (pushes > 1) return;
    if ((m_ui32HeroFlags354 & 0x800u) != 0 || (m_ui32HeroFlags35C & 2u) != 0) return;
    m_unk1618 = 0.800000011920928955f;  // TOC +0x24c4
    m_unk1610 = pushes + 1;
    HeroTimedImpulse push{m_unk156c, m_unk1570, m_unk1574, Vec(m_unk1578), AsF32(m_unk1584), AsF32(m_unk1588)};
    push.Start(CVector3{px, py, pz});
    m_unk1578 = push.m_dir.x;
    m_unk157c = push.m_dir.y;
    m_unk1580 = push.m_dir.z;
    SetF32(m_unk1584, push.m_left);
    SetF32(m_unk1588, push.m_last);
    m_unk1574 = push.m_active;
    SetF32(m_unk15ec, m_unkd48);
    if (m_unk550 <= partner->m_unk550) m_unk15fc = 1;
}

// 0x0031c4d8 CKHkS08Hero_ComputeTakeOffToPartnerVelocity_maybe: below the partner, the side +0x15d4 (flipped to the
// partner's move +0x37c when climbing, else to its turn axis +0x1604) times 50 (hero 0) / 45 times the move +0x1378,
// unless its normalised form points more than 0.2 down; else nothing.
CVector3 CKHkS08Hero::ComputeTakeOffToPartnerVelocity() {
    const CVector3& zero = kHeroZeroVector;  // TOC +0x2450
    CVector3 out = zero;
    uint8_t below = 0;
    float sx = m_unk15d4;
    float sy = m_unk15d8;
    float sz = m_unk15dc;
    const float y = m_unk550;
    if (GetPartnerHero()->m_unk550 >= y) {  // 0x002f85f8
        CKHkS08Hero* partner = GetPartnerHero();
        const float* n = partner->m_unk1744 == 2 ? &m_unk37c : &m_unk1604;
        const float d = ppc::fmadds(m_unk15dc, n[2], ppc::fmadds(m_unk15d4, n[0], m_unk15d8 * n[1]));
        const float s = d < 0.0f ? -1.0f : 1.0f;  // TOC +0x2474 / +0x2468
        sz = sz * s;
        below = 1;
        sx = sx * s;
        sy = sy * s;
    }
    const float k = m_ui8Hero == 0 ? 50.0f : 45.0f;  // TOC +0x24d4 / +0x24d8
    const float zz = sz * k;
    const float xx = sx * k;
    const float yy = sy * k;
    const float speed = m_unk1378;
    float vz = speed * zz;
    float vx = speed * xx;
    float vy = speed * yy;
    if (IsAbilityActive() != 0) {  // 0x002fc228
        // The original asks the ability (+0x1cc0) IsKindOfClass(0x95cc) and drops the answer.
    }
    {
        const float up = m_unk15d8;
        float nx = vx;
        float ny = vy;
        float nz = vz;
        const float length = Length(vx, vy, vz);
        if (length != 0.0f) {
            const float inv = 1.0f / length;
            nz = vz * inv;
            nx = vx * inv;
            ny = vy * inv;
        }
        const float d = ppc::fmadds(nz, 0.0f, ppc::fmadds(nx, 0.0f, up * ny));
        if (d < -2.00000002980232239e-1f || below == 0) {  // TOC +0x24dc
            vz = zero.z;
            vx = zero.x;
            vy = zero.y;
        }
    }
    out.x = out.x + vx;
    out.y = out.y + vy;
    out.z = out.z + vz;
    return out;
}

// 0x0031c788 CKHkS08Hero_DynamicStage1TakeOffToPartner_maybe (DynamicStage1ByMode while joining the partner, each fixed
// sub-step): the forces into +0x17f0: the drag (the speed times -0.4 (hero 0) / -0.35 along the velocity), gravity
// (down times +0xd70..+0xd1c by the height gap to the partner over the group's +0x10c) times the mass, the take-off
// velocity, the pull back to the partner's plane beyond +0xd60 (times +0xd50; the plane through the partner's position
// (plus +0xd54 along +0x15e0 when it does not climb), the push between the heroes +0x17fc, the side push +0x15d4 times
// the impulse record +0x1d3c's length; over the mass into the velocity (+0xec8 bits 9 / 10 clear y / x and z), then
// the displacement.
void CKHkS08Hero::DynamicStage1TakeOffToPartner(float dt) {
    const float mass = GetMass();  // 0x002f8818
    ComputeCameraRelativeMove();   // 0x00311df0
    const CVector3& zero = kHeroZeroVector;  // TOC +0x2450
    m_unk17f0 = zero.x;
    m_unk17f4 = zero.y;
    m_unk17f8 = zero.z;
    const float drag = m_ui8Hero != 0 ? -3.49999994039535522e-1f : -4.00000005960464478e-1f;  // TOC +0x24cc / +0x24c8
    {
        float vx = m_unk127c;
        float vy = m_unk1280;
        float vz = m_unk1284;
        float length = Length(vx, vy, vz);
        if (length != 0.0f) {
            const float inv = 1.0f / length;  // TOC +0x2468
            vz = vz * inv;
            vx = vx * inv;
            vy = vy * inv;
        } else {
            length = 0.0f;
        }
        const float k = length * drag;
        const float fz = ppc::fmadds(k, vz, zero.z);
        const float fx = ppc::fmadds(k, vx, zero.x);
        const float fy = ppc::fmadds(k, vy, zero.y);
        m_unk17f8 = fz + m_unk17f8;
        m_unk17f0 = fx + m_unk17f0;
        m_unk17f4 = fy + m_unk17f4;
    }
    {
        CKHkS08Hero* partner = GetPartnerHero();  // 0x002f85f8
        const CKGrpS08Hero* group = static_cast<const CKGrpS08Hero*>(m_pGrpHero);
        const float span = group->m_unk10c;
        const float t = ((partner->m_unk550 - m_unk550) + span) / (span + span);
        const float g = Math_RemapClamped(0.0f, 1.0f, t, m_unkd70, m_unkd1c);  // 0x00333618
        const CVector3 accel{kHeroDown.x * g, kHeroDown.y * g, kHeroDown.z * g};  // TOC +0x2464 -> 0x00c50d7c
        const CVector3 f = AccelToForce(mass, &accel);  // 0x0030fb68
        m_unk17f0 = f.x + m_unk17f0;
        m_unk17f4 = f.y + m_unk17f4;
        m_unk17f8 = f.z + m_unk17f8;
    }
    {
        const CVector3 f = ComputeTakeOffToPartnerVelocity();  // 0x0031c4d8
        m_unk17f0 = f.x + m_unk17f0;
        m_unk17f4 = f.y + m_unk17f4;
        m_unk17f8 = f.z + m_unk17f8;
    }
    {
        CKHkS08Hero* partner = GetPartnerHero();  // 0x002f85f8
        const uint32_t mode = partner->m_unk1744;
        float tx;
        float ty;
        float tz;
        if (mode == 0) {
            const float k = m_unkd54;
            tx = ppc::fmadds(k, m_unk15e0, partner->m_unk54c);
            tz = ppc::fmadds(k, m_unk15e8, partner->m_unk554);
            ty = ppc::fmadds(k, m_unk15e4, partner->m_unk550);
        } else if (mode == 2) {
            tx = partner->m_unk54c;
            tz = partner->m_unk554;
            ty = partner->m_unk550;
        } else {
            tx = zero.x;
            ty = zero.y;
            tz = zero.z;
        }
        float px = zero.x;
        float py = zero.y;
        float pz = zero.z;
        const float nx = m_unk15e0;
        const float ny = m_unk15e4;
        const float nz = m_unk15e8;
        const float targetPart = ppc::fnmadds(tz, nz, ppc::fmadds(tx, nx, ty * ny));
        const float ownPart = ppc::fmadds(nz, m_unk554, ppc::fmadds(nx, m_unk54c, ny * m_unk550));
        const float distance = targetPart + ownPart;
        const float limit = m_unkd60;
        if (std::fabs(distance) > limit) {
            // BUG(original): the limit is added on the positive side and subtracted on the other (0x31ca6c fadds /
            // 0x31cdf0 fsubs), so beyond it the pull is the whole distance plus the limit.
            float over = distance > 0.0f ? distance + limit : distance - limit;
            over = -over;
            const float k = over * m_unkd50;
            pz = k * nz;
            px = k * nx;
            py = k * ny;
        }
        m_unk17f0 = px + m_unk17f0;
        m_unk17f4 = py + m_unk17f4;
        m_unk17f8 = pz + m_unk17f8;
        m_unk17f0 = m_unk17f0 + m_unk17fc;
        m_unk17f8 = m_unk17f8 + m_unk1804;
        m_unk17f4 = m_unk17f4 + m_unk1800;
    }
    {
        HeroTimedImpulse impulse{m_unk1d3c, AsF32(m_unk1d40), m_unk1d44, Vec(m_unk1d48), AsF32(m_unk1d54),
                                 AsF32(m_unk1d58)};
        impulse.Step(dt, zero);
        m_unk1d48 = impulse.m_dir.x;
        m_unk1d4c = impulse.m_dir.y;
        m_unk1d50 = impulse.m_dir.z;
        m_unk1d44 = impulse.m_active;
        SetF32(m_unk1d54, impulse.m_left);
        SetF32(m_unk1d58, impulse.m_last);
        const CVector3 v = impulse.Evaluate(zero);
        const float length = Length(v.x, v.y, v.z);
        m_unk17f8 = ppc::fmadds(length, m_unk15dc, m_unk17f8);
        m_unk17f0 = ppc::fmadds(length, m_unk15d4, m_unk17f0);
        m_unk17f4 = ppc::fmadds(length, m_unk15d8, m_unk17f4);
    }
    const CVector3 sum{m_unk17f0, m_unk17f4, m_unk17f8};
    const CVector3 accel = ForceToAccel(dt, mass, &sum);      // 0x00310ba8
    const CVector3 delta = AccelToVelocityDelta(dt, &accel);  // 0x0030fb98
    m_unk127c = m_unk127c + delta.x;
    m_unk1280 = m_unk1280 + delta.y;
    m_unk1284 = m_unk1284 + delta.z;
    const uint32_t flags = m_unkec8;
    if ((flags & 0x200u) != 0) m_unk1280 = 0.0f;
    if ((flags & 0x400u) != 0) {
        m_unk1284 = 0.0f;
        m_unk127c = 0.0f;
    }
    const float z = ppc::fmadds(dt, m_unk1284, zero.z);
    const float x = ppc::fmadds(dt, m_unk127c, zero.x);
    const float y = ppc::fmadds(dt, m_unk1280, zero.y);
    const CVector3 external = GetExternalDisplacement();  // 0x0030fe18
    m_unk1270 = (z + external.z) + m_unk1270;
    m_unk1268 = (x + external.x) + m_unk1268;
    m_unk126c = (y + external.y) + m_unk126c;
    UpdateForwardAndSpeedStats();  // 0x00310d88
}

// 0x0031ce28 CKHkS08Hero_UpdateTakeOffToPartnerMovement_maybe (UpdateMovement while joining the partner): the node's
// matrix at the position: its up towards the partner (in the partner's plane +0x15e0), its at the node's at kept in that
// plane, then turned about the up by the angle between them (stepped towards 0 / pi/2 / pi by the side +0x15d4 at +0xd4c
// times the side speed +0x15f0 above +0xd5c); the body tilt springs' speeds are cleared and +0x137c / +0x12e4 take the
// node's angles.
void CKHkS08Hero::UpdateTakeOffToPartnerMovement(float dt) {
    CMatrix34 matrix;
    matrix.m_ui32Flags = 0x20003;
    matrix.m_right.x = 1.0f;
    matrix.m_up.x = 0.0f;
    matrix.m_at.x = 0.0f;
    matrix.m_pos.x = 0.0f;
    matrix.m_at.z = 1.0f;
    matrix.m_up.y = 1.0f;
    matrix.m_right.z = 0.0f;
    matrix.m_right.y = 0.0f;
    matrix.m_at.y = 0.0f;
    matrix.m_up.z = 0.0f;
    matrix.m_pos.z = 0.0f;
    matrix.m_pos.y = 0.0f;
    matrix.m_pos.x = m_unk54c;
    matrix.m_pos.z = m_unk554;
    matrix.m_pos.y = m_unk550;
    matrix.m_ui32Flags &= ~0x20000u;
    CKHkS08Hero* partner = GetPartnerHero();  // 0x002f85f8
    CVector3 toPartner{partner->m_unk54c - m_unk54c, partner->m_unk550 - m_unk550, partner->m_unk554 - m_unk554};
    {
        const float length = Length(toPartner.x, toPartner.y, toPartner.z);
        if (length != 0.0f) {
            const float inv = 1.0f / length;  // TOC +0x2468
            toPartner.z = toPartner.z * inv;
            toPartner.x = toPartner.x * inv;
            toPartner.y = toPartner.y * inv;
        }
    }
    const float ax = m_unk15e0;
    const float ay = m_unk15e4;
    const float az = m_unk15e8;
    {
        const float k = ppc::fnmadds(az, toPartner.z, ppc::fmadds(toPartner.x, ax, ay * toPartner.y));
        toPartner.y = ppc::fmadds(ay, k, toPartner.y);
        toPartner.x = ppc::fmadds(ax, k, toPartner.x);
        toPartner.z = ppc::fmadds(az, k, toPartner.z);
        const float length = Length(toPartner.x, toPartner.y, toPartner.z);
        if (length != 0.0f) {
            const float inv = 1.0f / length;
            toPartner.z = toPartner.z * inv;
            toPartner.x = toPartner.x * inv;
            toPartner.y = toPartner.y * inv;
        }
    }
    GetPartnerHero();  // 0x002f85f8 (not used)
    const float ny = -toPartner.y;
    const float nx = -toPartner.x;
    const float nz = -toPartner.z;
    const RwFrame* frame = NodeFrame(m_pKGLObject);
    // The node's at, its part along the (reversed) direction to the partner removed.
    float bx;
    float by;
    float bz;
    const float crossZ = ppc::fmsubs(nx, ay, ny * ax);
    {
        const float atX = frame->modelling.at.x;
        const float atY = frame->modelling.at.y;
        const float atZ = frame->modelling.at.z;
        const float k = ppc::fnmadds(nz, atZ, ppc::fmadds(nx, atX, ny * atY));
        by = ppc::fmadds(ny, k, atY);
        bx = ppc::fmadds(nx, k, atX);
        bz = ppc::fmadds(nz, k, atZ);
        const float length = std::sqrt(ppc::fmadds(bz, bz, ppc::fmadds(bx, bx, by * by)));  // Math_Sqrtf
        if (length != 0.0f) {
            const float inv = 1.0f / length;
            bz = bz * inv;
            bx = bx * inv;
            by = by * inv;
        }
    }
    // The plane's in-plane axis: (reversed direction) x (plane normal), in the plane.
    CVector3 forward;
    {
        const float cy = ppc::fmsubs(nz, ax, nx * az);
        const float cx = ppc::fmsubs(ny, az, nz * ay);
        const float k = ppc::fnmadds(nz, crossZ, ppc::fmadds(nx, cx, ny * cy));
        forward.y = ppc::fmadds(ny, k, cy);
        forward.x = ppc::fmadds(nx, k, cx);
        forward.z = ppc::fmadds(nz, k, crossZ);
        const float length = std::sqrt(ppc::fmadds(forward.z, forward.z, ppc::fmadds(forward.x, forward.x, forward.y * forward.y)));
        if (length != 0.0f) {
            const float inv = 1.0f / length;
            forward.z = forward.z * inv;
            forward.x = forward.x * inv;
            forward.y = forward.y * inv;
        }
    }
    float angle;
    {
        CVector3 a{bx, by, bz};
        CVector3 b = forward;
        angle = Vec3_AngleBetween(&a, &b);  // 0x002fbbf8
    }
    const CVector3& zero = kHeroZeroVector;  // TOC +0x2450
    bool built = false;
    if (!(forward.x == zero.x && forward.y == zero.y && forward.z == zero.z)) {
        built = Mat4_BuildFromUpAndForward(&matrix, &toPartner, &forward) != 0;  // 0x0023ff80
    }
    if (!built) {
        // The original passes the matrix itself as the `at` (its right row).
        Mat4_SetBasisFromUpAt(&matrix, &toPartner, &matrix.m_right);  // 0x002400a8
    }
    const float sideSpeed = Length(m_unk15f0, m_unk15f4, m_unk15f8);
    if (!(m_unkd5c >= sideSpeed)) {
        const float d = ppc::fmadds(forward.z, m_unk15dc, ppc::fmadds(forward.x, m_unk15d4, forward.y * m_unk15d8));
        float target;
        if (d < 0.0f) {
            target = kPi;
        } else if (d <= 0.0f || !(d > 0.0f)) {
            target = 1.57079637050628662f;  // TOC +0x24e4
        } else {
            target = 0.0f;
        }
        float approach[3] = {target, m_unkd4c * Length(m_unk15f0, m_unk15f4, m_unk15f8), angle};
        FloatApproach_StepAngle(dt, approach);  // 0x00243748
        angle = approach[2];
    }
    Mat4_RotateLocalYDeg(angle * kRadToDeg, &matrix);  // 0x002413d0
    CSGMovable* node = static_cast<CSGMovable*>(m_pKGLObject);
    node->SetLocalMatrix(reinterpret_cast<const RwMatrix*>(&matrix));  // 0x000d0be8
    m_unk12ec = 0.0f;
    m_unk12e8 = 0.0f;
    {
        const RwFrame* now = node->m_pRwFrame;
        CVector3 up{now->modelling.up.x, now->modelling.up.y, now->modelling.up.z};
        float pitch = Vec3_GetAngleInYZPlane(&up);  // 0x00244748
        if (pitch > kPi) pitch = pitch - kTwoPi;
        m_unk137c = pitch;
        float roll = Vec3_GetAngleInXYPlane(&up);  // 0x002443d8
        if (roll > kPi) roll = roll - kTwoPi;
        m_unk12e4 = roll;
    }
}

// 0x0031b608 StaticInitAndDestruction_31b608: two file statics (0x00ceae34, 0x00ceae38) set to -1.0f. Nothing in the game
// reads them (their only references are the initialiser's TOC entries).
namespace {
[[maybe_unused]] float s_unkceae34 = -1.0f;
[[maybe_unused]] float s_unkceae38 = -1.0f;
}  // namespace
