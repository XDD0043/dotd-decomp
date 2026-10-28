// Reconstructed original translation unit: 0x312870-0x317200 (GAME_TOC1, main_toc1), 23 functions, 18 live.
// Primary class: CKHkS08Hero  key 0x25c2  category Hook  size 0x1e00  vtable 0xb22c98
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x312870  FUN_00312870  [dead]
//   [ ] 0x312a48  FUN_00312a48  [dead]
//   [ ] 0x312ab0  FUN_00312ab0  [dead]
//   [ ] 0x312ab8  FUN_00312ab8  [dead]
//   [x] 0x312bb0  CKHkS08Hero_UpdateFlightAltitudeAndProbes_maybe
//   [x] 0x312f98  CKHkS08Hero_AccumulateFlightDisplacement_maybe
//   [ ] 0x3131e0  FUN_003131e0  [dead]
//   [x] 0x313340  CKHkS08Hero_ComputeFlightGravityAccel_maybe
//   [x] 0x313780  CKHkS08Hero_LocoState0_Flying_Condition
//   [ ] 0x3137a8  StaticInitAndDestruction_3137a8
//   [ ] 0x3137d8  _GLOBAL__D_3137d8
//   [ ] 0x3137e8  _GLOBAL__I_3137e8
//   [x] 0x3137f8  CKHkS08Hero_ComputeFlightDragForce_maybe
//   [x] 0x313a48  CKHkS08Hero_ComputeFlightDashImpulse_maybe
//   [x] 0x313d20  CKHkS08Hero_ComputeFlightField13D8Force_maybe
//   [x] 0x313f50  CKHkS08Hero_ComputeFlightThrustForce_maybe
//   [x] 0x3141b0  CKHkS08Hero_UpdateFlyingMovement_maybe
//   [x] 0x314b58  CKHkS08Hero_ComputeFlightAimHeightForce_maybe
//   [x] 0x314dc8  CKHkS08Hero_ComputeFlightGroundSlideForce_maybe
//   [x] 0x315088  CKHkS08Hero_LocoState0_Flying
//   [x] 0x315970  CKHkS08Hero_ComputeFlightInputForce_maybe
//   [x] 0x315d60  CKHkS08Hero_DynamicStage1Flying_maybe
//   [x] 0x3167e0  CKHkS08Hero_UpdateFlyingLocomotion_maybe

#include "Spyro2008/hooks/CKHkS08Hero.h"
#include <cmath>
#include <cstring>
#include "Renderware/rtanim/RtAnim.h"
#include "Renderware/rwcore/RwCamera.h"
#include "Spyro2008/groups/CKGrpS08Hero.h"
#include "Spyro2008/hooks/HeroTimedImpulse.h"
#include "Spyro2008/logic/CKS08GameManager.h"
#include "crt/ppc_ops.h"
#include "crt/xatan.h"
#include "k2000/animation/AnimBlendSlot.h"
#include "k2000/components/CKCurve2DCpnt.h"
#include "k2000/components/CKImpulsionCpnt.h"
#include "k2000/core/Stub.h"
#include "k2000/dictionaries/CAnimationDictionary.h"
#include "k2000/graphical/animation/CAnimationManager.h"
#include "k2000/hooks/GroundContact.h"
#include "k2000/logic/physics/CGround.h"
#include "k2000/math/Math.h"
#include "k2000/math/Vec3.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/FloatApproach.h"
#include "k2000/misc/Mat4.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/services/CKSrvCollision.h"
#include "k2000/services/CKSrvDynamic.h"
#include "k2000/services/CollisionDatas.h"
#include "k2000/services/ICollisionMesh.h"

namespace {

constexpr float kPi = 3.14159274101257324f;        // TOC +0x2340
constexpr float kHalfPi = 1.57079637050628662f;    // TOC +0x2344
constexpr float kTwoPi = 6.28318548202514648f;     // TOC +0x22fc
constexpr float kRadToDeg = 57.2957801818847656f;  // TOC +0x2348
// 0x00c50d7c: the shared down vector (0, -1, 0) (zero in the EBOOT's BSS; StaticInitAndDestruction_11578 fills it).
constexpr CVector3 kHeroDown{0.0f, -1.0f, 0.0f};

const CVector3& Vec(const float& x) { return *reinterpret_cast<const CVector3*>(&x); }
CVector3& Vec(float& x) { return *reinterpret_cast<CVector3*>(&x); }

// The game manager's record of a hero (+0xdf8 + hero * 0x20; CKHkS08Hero_7.cpp's layout).
uint32_t* GameManagerHeroRecord(uint8_t hero) {
    CKS08GameManager* manager = static_cast<CKS08GameManager*>(g_pEngine->m_gameManager);
    return &manager->m_unkDF4[1 + hero * 8u];
}

float WordAsFloat(uint32_t word) {
    float value;
    std::memcpy(&value, &word, 4);
    return value;
}

// 0x00301348 CKHkS08Hero_IsInSpecialAnim_maybe (local copy; CKHkS08Hero_3.cpp): the animation (+0x160) is one of
// 0x33, 0x36, 0x3a, 0x3d, 0x41, 0x43, 0x44.
uint8_t IsInSpecialAnim(const CKHkS08Hero* hero) {
    switch (static_cast<int16_t>(hero->m_unk160)) {
    case 0x33: case 0x36: case 0x3a: case 0x3d: case 0x41: case 0x43: case 0x44: return 1;
    default: return 0;
    }
}

}  // namespace

// 0x00312bb0 CKHkS08Hero_UpdateFlightAltitudeAndProbes_maybe: the flight height +0x1458 (the height above the ground;
// on a ground of property 0x200, or 0x20 above +0x910, less the ground's value without a mass +0x1258 and less +0x8e4);
// +0xed0 bit 0 cleared; without a mass, two rings of ground probes around the hero (+0xa48 points at +0xa4c raised by
// +0xa50, then +0xa58 / +0xa5c / +0xa60) lower the height to a ground found less than +0xa54 (+0xa64) below the probe
// point (+0xed0 bit 0 set then).
void CKHkS08Hero::UpdateFlightAltitudeAndProbes() {
    uint32_t count = static_cast<uint32_t>(m_unka48);
    float radius = m_unka4c;
    float lift = m_unka50;
    float maxStep = m_unka54;
    m_unk1458 = GetHeightAboveGround();  // 0x0032a008
    m_unked0 &= ~1u;
    const CGround* ground = static_cast<const CGround*>(GetGroundInfo());  // 0x00361b68
    if (ground != nullptr) {
        const uint16_t props = ground->m_ui16PropertiesFlags;
        if ((props & 0x200u) != 0 || ((props & 0x20u) != 0 && m_unk1458 > m_unk910)) {
            float height = m_unk1458;
            if (!(m_unk1258 >= 1.0e-1f)) {  // TOC +0x22f4
                height = height - ground->m_fPropertieValue;
                m_unk1458 = height;
            }
            height = height - m_unk8e4;
            m_unk1458 = height;
        }
    }
    if (m_unk1258 >= 1.0e-1f) return;
    const CVector3* center = &Vec(m_unk54c);
    const CVector3* direction = &Vec(m_unk135c);
    for (int ring = 0; ring < 2; ++ring) {
        if (ring == 1) {
            count = static_cast<uint32_t>(m_unka58);
            radius = m_unka5c;
            lift = m_unka60;
            maxStep = m_unka64;
        }
        const float step = kTwoPi / static_cast<float>(static_cast<double>(count));
        CGroundContactDatasInOut contact;
        for (uint32_t i = 0; i != count;) {
            const float angle = step * static_cast<float>(static_cast<double>(i));
            ++i;
            CVector3 radial;
            Vec3_GenerateRadialPointsXZ(angle, radius, center, direction, &radial, 1, nullptr);  // 0x00585110
            const float raised = lift + radial.y;
            CVector3 point{radial.x, raised, radial.z};
            contact.m_pGround = nullptr;
            contact.m_i32FaceIndex = -1;
            contact.m_eContactStatus = 3;
            contact.m_ui8SectorNumber = 0;
            GroundContact_ProbeGroundPoint(&contact, &point, nullptr);  // 0x00583ef8
            float below = m_unk550 - point.y;
            if (below < 0.0f) below = 0.0f;
            if (contact.m_eContactStatus != 3 && raised - point.y < maxStep && m_unk1458 > below) {
                m_unked0 = (m_unked0 & ~1u) | 1u;
                m_unk1458 = below;
            }
        }
    }
}

// 0x00312f98 CKHkS08Hero_AccumulateFlightDisplacement_maybe: AccumulateGroundDisplacement's flight form: with +0x13d8 and
// no thrust (+0x13fc) the velocity first loses its part along +0x13dc when it points that way.
void CKHkS08Hero::AccumulateFlightDisplacement(float dt) {
    const CVector3& zero = kHeroZeroVector;  // TOC +0x22dc
    if (m_unk13d8 != 0 && m_unk13fc == 0) {
        const float dot = ppc::fmadds(m_unk1284, m_unk13e4, ppc::fmadds(m_unk127c, m_unk13dc, m_unk1280 * m_unk13e0));
        if (dot > 0.0f) {
            const float k = -dot;
            const float vz = ppc::fmadds(k, m_unk13e4, m_unk1284);
            const float vx = ppc::fmadds(m_unk13dc, k, m_unk127c);
            const float vy = ppc::fmadds(k, m_unk13e0, m_unk1280);
            m_unk1284 = vz;
            m_unk127c = vx;
            m_unk1280 = vy;
        }
    }
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

// 0x00313340 CKHkS08Hero_ComputeFlightGravityAccel_maybe: the Y axis times minus the gravity of the flight: from the
// flight height +0x1458 (the partner's gap +0xac8 taken off it for the group's hero +0xacc without a mass) over +0x8e0
// times +0x8f4 / +0x904 (on a ground of property 0x20: high above +0x910 the band +0x908..+0x8fc, else +0x8f8..+0x90c;
// otherwise +0x8f8..+0x8fc, or near a ground of property 0x200 the curve +0x147c from +0x8f8 down to +0x8f0); +0x914
// for the other hero low above a plain ground; +0x1b18 with +0xec4 bit 27; +0x9b4 with +0x13d8 (less up to half with two
// controlled heroes by the group's gap); +0x11d8 scaled into +0x8f8..+0x8fc with +0xec8 bit 8.
CVector3 CKHkS08Hero::ComputeFlightGravityAccel() {
    CVector3 out = kHeroAxisY;  // TOC +0x22e0 -> 0x00c50d40
    const CKGrpS08Hero* group = static_cast<const CKGrpS08Hero*>(m_pGrpHero);
    float height = m_unk1458;
    if (static_cast<int32_t>(m_ui8Hero) == static_cast<int8_t>(group->m_unkacc)) {
        if (m_unk1258 < 1.0e-1f) {  // TOC +0x22f4
            const float gap = m_unk550 - group->m_unkac8;
            if (height > gap) height = gap;
        }
    }
    const ICollisionMesh* ground = static_cast<const ICollisionMesh*>(GetGroundInfo());  // 0x00361b68
    uint8_t onFlightGround = 0;  // property 0x200
    uint8_t onProperty20 = 0;
    uint8_t highAbove = 0;
    if (ground != nullptr) {
        const uint16_t props = ground->m_ui16PropertiesFlags;
        onFlightGround = static_cast<uint8_t>((props >> 9) & 1u);
        if ((props & 0x20u) != 0) {
            onProperty20 = 1;
            highAbove = m_unk910 >= GetHeightAboveGround() ? 0 : 1;  // 0x0032a008
        }
    }
    float gravity;
    auto band = [&](float scale, float lo, float hi) {
        const float wanted = (height / m_unk8e0) * scale;
        if (lo >= wanted) return lo;
        if (wanted >= hi) return hi;
        return wanted;
    };
    if (onFlightGround != 0 && highAbove == 0 && (m_unkec8 & 0x20000000u) == 0 && (m_unked0 & 1u) == 0) {
        const float ratio = height / m_unk8e0;
        GetHeightAboveGround();  // 0x0032a008 (the answer is not used)
        const float wanted = ratio * m_unk8f4;
        if (m_unk8f8 >= wanted) {
            gravity = m_unk8f8;
        } else if (wanted >= m_unk8fc) {
            gravity = m_unk8fc;
        } else {
            gravity = wanted;
        }
        if (m_unk8e4 > GetHeightAboveGround()) {
            const float h = GetHeightAboveGround();
            const float span = m_unk8f8 - m_unk8f0;
            const float c = static_cast<const CKCurve2DCpnt*>(m_unk147c)->Evaluate(h / m_unk8e4);  // 0x00249ea8
            gravity = ppc::fmadds(span, c, m_unk8f8);
        }
    } else {
        if (onProperty20 == 0) {
            if (highAbove != 0) {
                gravity = band(m_unk8f4, m_unk908, m_unk8fc);
            } else {
                gravity = band(m_unk8f4, m_unk8f8, m_unk8fc);
            }
        } else if (highAbove != 0) {
            gravity = band(m_unk8f4, m_unk908, m_unk8fc);
        } else {
            gravity = band(m_unk904, m_unk8f8, m_unk90c);
        }
        if (m_unk918 > height && onFlightGround == 0 && m_unk138c <= 0.0f &&
            static_cast<int32_t>(m_ui8Hero) != static_cast<int8_t>(group->m_unkacc) &&
            (m_unked0 & 1u) == 0 && !(m_unk1258 >= 1.0e-1f) && m_unk18d0 != 0xc && highAbove == 0) {
            gravity = m_unk914;
        }
    }
    if ((m_unkec4 & 0x8000000u) != 0) gravity = m_unk1b18;
    if (m_unk13d8 != 0) {
        gravity = m_unk9b4;
        if (group->m_ui8ControlledHeroCount == 2) {
            const float gap = WordAsFloat(group->m_unk318) + WordAsFloat(group->m_unk2d4[16]);  // +0x318 + +0x314
            const float r = Math_RemapClamped(0.0f, group->m_unk10c, gap, 0.0f, 0.5f);  // 0x00333618; TOC +0x2300
            gravity = gravity * (1.0f - r);  // TOC +0x2304
        }
    }
    if ((m_unkec8 & 0x100u) != 0) gravity = band(AsF32(m_unk11d8), m_unk8f8, m_unk8fc);
    const float k = -gravity;
    out.z = k * out.z;
    out.x = k * out.x;
    out.y = k * out.y;
    return out;
}

// 0x003137f8 CKHkS08Hero_ComputeFlightDragForce_maybe: the velocity times minus its length times +0x958 (+0x1444 with
// +0xec8 bit 17); with +0xec8 bit 26 the horizontal part scales by (+0x12c4 / +0x11f8)^2 (^4 above it); near a ground
// (+0xec4 bit 18, the hero less than +0x8e4 plus the ground's value above +0x574) the drag is linear in +0x12c4 (+0x8ec
// vertically); during an ability the vertical part is minus +0x8cc times vy |vy|.
CVector3 CKHkS08Hero::ComputeFlightDragForce() {
    const float vx = m_unk127c;
    const float vy = m_unk1280;
    const float vz = m_unk1284;
    CVector3 out{vx, vy, vz};
    const float coeff = (m_unkec8 & 0x20000u) != 0 ? AsF32(m_unk1444) : m_unk958;
    {
        const float k = -coeff * std::sqrt(ppc::fmadds(vz, vz, ppc::fmadds(vx, vx, vy * vy)));  // Math_Sqrtf
        out.z = k * out.z;
        out.x = k * out.x;
        out.y = k * out.y;
    }
    if ((m_unkec8 & 0x4000000u) != 0) {
        const float speed = m_unk12c4;
        const float ratio = speed / m_unk11f8;
        float scale = ratio * ratio;
        if (speed > m_unk11f8) scale = scale * scale;
        out.x = scale * out.x;
        out.z = scale * out.z;
    }
    const float y = m_unk550;
    const float groundY = m_unk574;
    float reach = m_unk8e4;
    if (GetGroundInfo() != nullptr) reach = reach + static_cast<const CGround*>(GetGroundInfo())->m_fPropertieValue;
    if ((m_unkec4 & 0x40000u) != 0 && y - groundY < reach) {
        const float k = -m_unk958;
        const float kv = -m_unk8ec;
        const float speed = m_unk12c4;
        const float zz = vz * k;
        const float yy = vy * kv;
        const float xx = vx * k;
        const float vertical = kv * 0.0f;  // TOC +0x22e4
        const float horizontal = k * 0.0f;
        out.z = ppc::fmadds(zz, speed, vertical);
        out.x = ppc::fmadds(xx, speed, vertical);
        out.y = ppc::fmadds(horizontal, speed, yy);
    }
    if (IsAbilityActive() != 0) {  // 0x002fc228
        out.y = vy;
        out.y = vy * std::fabs(vy);
        out.y = out.y * -m_unk8cc;
    }
    return out;
}

// 0x00313a48 CKHkS08Hero_ComputeFlightDashImpulse_maybe: the dash record (+0x145c): with +0xecc bit 23 it starts along
// the move (+0x37c, or the facing +0x135c below 0.1) times +0xa1c raised by +0xa18 on the Y axis, normalised, the length
// as the magnitude and +0xa20 as the duration; then the record's step and its push.
CVector3 CKHkS08Hero::ComputeFlightDashImpulse(float dt) {
    const CVector3& zero = kHeroZeroVector;  // TOC +0x22dc
    HeroTimedImpulse dash{m_unk145c, AsF32(m_unk1460), m_unk1464, CVector3{m_unk1468, m_unk146c, m_unk1470},
                          AsF32(m_unk1474), AsF32(m_unk1478)};
    if ((m_unkecc & 0x800000u) != 0) {
        const CVector3& axis = kHeroAxisY;  // TOC +0x22e0
        float x = m_unk37c;
        float y = m_unk380;
        float z = m_unk384;
        if (std::sqrt(ppc::fmadds(z, z, ppc::fmadds(x, x, y * y))) < 1.0e-1f) {  // TOC +0x22f4
            x = m_unk135c;
            y = m_unk1360;
            z = m_unk1364;
        }
        const float scale = AsF32(m_unka1c);
        const float nx = ppc::fmadds(axis.x, m_unka18, scale * x);
        const float ny = ppc::fmadds(axis.y, m_unka18, scale * y);
        const float nz = ppc::fmadds(axis.z, m_unka18, scale * z);
        x = nx;
        y = ny;
        z = nz;
        float length = std::sqrt(ppc::fmadds(z, z, ppc::fmadds(x, x, y * y)));
        if (length != 0.0f) {
            const float inv = 1.0f / length;  // TOC +0x2304
            z = z * inv;
            x = x * inv;
            y = y * inv;
        } else {
            length = 0.0f;
        }
        dash.m_duration = m_unka20;
        dash.m_magnitude = length;
        dash.Start(CVector3{x, y, z});
    }
    dash.Step(dt, zero);
    const CVector3 out = dash.Evaluate(zero);
    m_unk145c = dash.m_magnitude;
    SetF32(m_unk1460, dash.m_duration);
    m_unk1464 = dash.m_active;
    m_unk1468 = dash.m_dir.x;
    m_unk146c = dash.m_dir.y;
    m_unk1470 = dash.m_dir.z;
    SetF32(m_unk1474, dash.m_left);
    SetF32(m_unk1478, dash.m_last);
    return out;
}

// 0x00313d20 CKHkS08Hero_ComputeFlightField13D8Force_maybe (a force): with +0x13d8, during the thrust (+0x13fc)
// the push +0x13e8 times +0x9e4 while the record +0x1414 runs; otherwise minus +0x9d0 times +0x13dc, the record's step
// and push, and +0x13e8 times +0x9e8 (+0x9e4 more while the record runs).
CVector3 CKHkS08Hero::ComputeFlightField13D8Displacement(float dt) {
    const CVector3& zero = kHeroZeroVector;  // TOC +0x22dc
    CVector3 out = zero;
    if (m_unk13d8 == 0) return out;
    auto pushWhileRunning = [&]() {
        if (m_unk13d8 == 0 || m_unk141c == 0) return;
        const float k = m_unk9e4;
        out.x = ppc::fmadds(m_unk13e8, k, out.x);
        out.z = ppc::fmadds(m_unk13f0, k, out.z);
        out.y = ppc::fmadds(m_unk13ec, k, out.y);
    };
    if (m_unk13fc != 0) {
        pushWhileRunning();
        return out;
    }
    {
        const float k = -m_unk9d0;
        out.x = m_unk13dc;
        out.z = m_unk13e4;
        out.y = m_unk13e0;
        out.z = k * out.z;
        out.x = k * out.x;
        out.y = k * out.y;
    }
    HeroTimedImpulse record{m_unk1414, m_unk1418, m_unk141c, CVector3{m_unk1420, m_unk1424, m_unk1428}, m_unk142c,
                            m_unk1430};
    record.Step(dt, zero);
    m_unk1420 = record.m_dir.x;
    m_unk1424 = record.m_dir.y;
    m_unk1428 = record.m_dir.z;
    m_unk141c = record.m_active;
    m_unk142c = record.m_left;
    m_unk1430 = record.m_last;
    const CVector3 push = record.Evaluate(zero);
    out.x = out.x + push.x;
    out.y = out.y + push.y;
    out.z = out.z + push.z;
    {
        const float k = m_unk9e8;
        out.x = ppc::fmadds(m_unk13e8, k, out.x);
        out.z = ppc::fmadds(m_unk13f0, k, out.z);
        out.y = ppc::fmadds(m_unk13ec, k, out.y);
    }
    pushWhileRunning();
    return out;
}

// 0x00313f50 CKHkS08Hero_ComputeFlightThrustForce_maybe: in the air (no +0x13d1) during the take-off push (+0x1385) the
// ground normal +0x564 times +0x988 (the part of the step left of the timer +0x1388 on its last step); then the thrust
// record +0x13f4's step and push; all times UpdateAndGetField11C8.
CVector3 CKHkS08Hero::ComputeFlightThrustForce(float dt) {
    const CVector3& zero = kHeroZeroVector;  // TOC +0x22dc
    CVector3 out = zero;
    if (m_unk13d1 == 0 && m_unk1385 != 0) {
        const float before = m_unk1388;
        const float left = before - dt;
        m_unk1388 = left;
        float k = m_unk988;
        if (left <= 0.0f) k = (before * m_unk988) / dt;
        out.x = ppc::fmadds(k, m_unk564, out.x);
        out.z = ppc::fmadds(k, m_unk56c, out.z);
        out.y = ppc::fmadds(k, m_unk568, out.y);
    }
    HeroTimedImpulse thrust{m_unk13f4, AsF32(m_unk13f8), m_unk13fc, CVector3{m_unk1400, m_unk1404, m_unk1408},
                            AsF32(m_unk140c), AsF32(m_unk1410)};
    thrust.Step(dt, zero);
    m_unk1400 = thrust.m_dir.x;
    m_unk1404 = thrust.m_dir.y;
    m_unk1408 = thrust.m_dir.z;
    m_unk13fc = thrust.m_active;
    SetF32(m_unk140c, thrust.m_left);
    SetF32(m_unk1410, thrust.m_last);
    const CVector3 push = thrust.Evaluate(zero);
    out.x = out.x + push.x;
    out.y = out.y + push.y;
    out.z = out.z + push.z;
    const float scale = UpdateAndGetField11C8();  // 0x00310330
    out.x = scale * out.x;
    out.z = scale * out.z;
    out.y = scale * out.y;
    return out;
}

// 0x00314b58 CKHkS08Hero_ComputeFlightAimHeightForce_maybe: towards the aimed enemy's height (+0x1d30; with a target
// +0x1d28 and no take-off timer +0x138c), vertical, times +0x8d4 + +0x8d8 the height above the ground (0..10; 1 on grounds
// of property 0x200 / 0x20).
CVector3 CKHkS08Hero::ComputeFlightTargetHeightForce() {
    CVector3 out = kHeroZeroVector;  // TOC +0x22dc
    if (m_unk1d28 == 0 || !(m_unk138c <= 0.0f)) return out;
    // The original also stores |dx|, |dy|, |dz| to the stack and drops them.
    const float y = m_unk1d30 + out.y;
    out.x = 0.0f;
    out.z = 0.0f;
    const float dy = y - m_unk550;
    out.y = dy;
    const float length = std::sqrt(ppc::fmadds(dy, dy, 0.0f) + 0.0f);  // Math_Sqrtf
    if (length == 0.0f) {
        out.z = out.z * 0.0f;
        out.x = out.x * 0.0f;
        out.y = out.y * 0.0f;
        return out;
    }
    const float inv = 1.0f / length;
    out.z = inv * out.z;
    out.x = inv * out.x;
    out.y = inv * out.y;
    if (length <= 0.0f) {
        out.z = out.z * 0.0f;
        out.x = out.x * 0.0f;
        out.y = out.y * 0.0f;
        return out;
    }
    float h = GetHeightAboveGround();  // 0x0032a008
    const ICollisionMesh* ground = static_cast<const ICollisionMesh*>(GetGroundInfo());
    if (h <= 0.0f) {
        h = 0.0f;
    } else if (h >= 10.0f) {  // TOC +0x2354
        h = 10.0f;
    }
    if (ground != nullptr && ((ground->m_ui16PropertiesFlags & 0x200u) != 0 || (ground->m_ui16PropertiesFlags & 0x20u) != 0)) {
        h = 1.0f;
    }
    const float k = ppc::fmadds(h, m_unk8d8, m_unk8d4);
    out.z = k * out.z;
    out.x = k * out.x;
    out.y = k * out.y;
    return out;
}

// 0x00314dc8 CKHkS08Hero_ComputeFlightGroundSlideForce_maybe: in the air without the take-off push, the part of the summed force
// +0x17f0 along the ground normal +0x564, moved onto the facing +0x1288: above the speed +0x9ac capped by a fraction of
// it (+0x9a4 without a move, +0x9a8 turning hard, else +0x97c / +0x980 by the velocity's part along the facing against
// +0x984; +0x13a5 records the first two), below it scaled by +0x12d0 / +0x9ac without a move.
CVector3 CKHkS08Hero::ComputeFlightAuxForce(float callerF27) {
    CVector3 out = kHeroZeroVector;  // TOC +0x22dc
    if (m_unk13d1 != 0 || m_unk1385 != 0) return out;
    const float nx = m_unk564;
    const float ny = m_unk568;
    const float nz = m_unk56c;
    const float along = ppc::fmadds(nz, m_unk17f8, ppc::fmadds(nx, m_unk17f0, ny * m_unk17f4));
    float sx = kHeroZeroVector.x;
    float sy = kHeroZeroVector.y;
    float sz = kHeroZeroVector.z;
    if (m_unk12d0 > m_unk9ac) {
        // The original takes the length of the velocity (less its part along the normal when it has one) here and drops it.
        const float fx = m_unk1288;
        const float fy = m_unk128c;
        const float fz = m_unk1290;
        const float forward = ppc::fmadds(fz, m_unk17f8, ppc::fmadds(fx, m_unk17f0, fy * m_unk17f4));
        m_unk13a5 = 0;
        // BUG(original): when the hero moves (+0x1378 not 0) without turning hard and +0x1378 is not positive, the fraction
        // is the caller's f27 (DynamicStage1Flying's mass).
        float fraction = callerF27;
        if (m_unk1378 == 0.0f) {  // TOC +0x22e4
            m_unk13a5 = 1;
            fraction = m_unk9a4;
        } else if (m_unk1374 < -m_unk9b0) {
            m_unk13a5 = 1;
            fraction = m_unk9a8;
        } else if (m_unk1378 > 0.0f) {
            const float run = ppc::fmadds(fz, m_unk1284, ppc::fmadds(fx, m_unk127c, fy * m_unk1280));
            fraction = run <= m_unk984 ? m_unk97c : m_unk980;
        }
        float k = fraction * along;
        if (!(forward >= k)) k = forward;
        sz = ppc::fmadds(k, fz, sz);
        sx = ppc::fmadds(k, fx, sx);
        sy = ppc::fmadds(k, fy, sy);
    } else if (m_unk1378 == 0.0f) {
        const float k = along * (m_unk12d0 / m_unk9ac);
        sz = ppc::fmadds(k, m_unk1290, sz);
        sy = ppc::fmadds(k, m_unk128c, sy);
        sx = ppc::fmadds(k, m_unk1288, sx);
    }
    out.x = out.x + sx;
    out.y = out.y + sy;
    out.z = out.z + sz;
    return out;
}

// 0x00315970 CKHkS08Hero_ComputeFlightInputForce_maybe: the flight's push: in the air (+0x13d1) a push timer +0x138c with
// its horizontal / vertical scales +0x1390 / +0x1394 starts on a take-off (+0x13ce: +0x930.. after a ground take-off at
// speed (+0x1809 above +0x964), else +0x924..) or a flap (+0x13cc: +0x93c..); while it runs, the Y axis plus the move
// (+0x37c times +0x1378; minus +0x1294 times it with +0x13a4; +0x135c with +0x13cd), normalised, kept as the push
// direction +0x1398 on a start (else scaled by its part along it), times the scales (prorated on the last step); all times
// UpdateAndGetField11C8. On the ground the timer is cleared.
CVector3 CKHkS08Hero::ComputeFlightInputForce(float dt) {
    CVector3 out = kHeroZeroVector;  // TOC +0x22dc
    if (m_unk13d1 == 0) {
        m_unk138c = 0.0f;
    } else {
        float timer;
        const uint8_t takeOff = m_unk13ce;
        bool start = false;
        if (takeOff != 0) {
            m_unk138c = 0.0f;
            timer = 0.0f;
            if (m_unk1809 != 0 && m_unk12c4 > m_unk964) {
                m_unk1390 = m_unk930;
                m_unk1394 = AsF32(m_unk934);
                m_unk138c = m_unk938;
                timer = m_unk938;
            } else {
                start = true;
            }
        } else {
            timer = m_unk138c;
            if (timer <= 0.0f) start = true;
        }
        if (start) {
            if (m_unk13cc != 0) {
                m_unk1390 = m_unk93c;
                m_unk1394 = m_unk940;
                m_unk138c = m_unk944;
                timer = m_unk944;
            } else if (takeOff != 0) {
                m_unk1390 = m_unk924;
                m_unk1394 = m_unk928;
                m_unk138c = m_unk92c;
                timer = m_unk92c;
            } else {
                timer = m_unk138c;
            }
        }
        if (timer > 0.0f) {
            out = kHeroAxisY;  // TOC +0x22e0
            float ax;
            float ay;
            float az;
            if (m_unk13a4 != 0) {
                const float k = -m_unk1378;
                az = m_unk129c * k;
                ax = m_unk1294 * k;
                ay = m_unk1298 * k;
            } else if (m_unk13cd == 0) {
                const float k = m_unk1378;
                ax = m_unk37c * k;
                az = m_unk384 * k;
                ay = m_unk380 * k;
            } else {
                ax = m_unk135c;
                az = m_unk1364;
                ay = m_unk1360;
            }
            out.y = out.y + ay;
            out.x = out.x + ax;
            out.z = az + out.z;
            const float length = std::sqrt(ppc::fmadds(out.z, out.z, ppc::fmadds(out.x, out.x, out.y * out.y)));
            if (length != 0.0f) {
                const float inv = 1.0f / length;  // TOC +0x2304
                out.z = inv * out.z;
                out.x = inv * out.x;
                out.y = inv * out.y;
            }
            if (m_unk13cc != 0 || m_unk13ce != 0) {
                m_unk1398 = out.x;
                m_unk13a0 = out.z;
                m_unk139c = out.y;
            } else if (m_unk13cd == 0) {
                float d = ppc::fmadds(m_unk13a0, out.z, ppc::fmadds(out.x, m_unk1398, m_unk139c * out.y));
                if (d < 0.0f) d = 0.0f;
                out.x = d * out.x;
                out.y = d * out.y;
                out.z = d * out.z;
            }
            const float left = m_unk138c;
            if (left >= dt) {
                out.x = out.x * m_unk1390;
                out.y = out.y * m_unk1394;
                out.z = out.z * m_unk1390;
            } else {
                out.x = out.x * ((left * m_unk1390) / dt);
                out.y = out.y * ((m_unk1394 * m_unk138c) / dt);
                out.z = out.z * ((m_unk1390 * m_unk138c) / dt);
            }
            m_unk138c = m_unk138c - dt;
        }
    }
    const float scale = UpdateAndGetField11C8();  // 0x00310330
    out.x = scale * out.x;
    out.z = scale * out.z;
    out.y = scale * out.y;
    return out;
}

// 0x00315d60 CKHkS08Hero_DynamicStage1Flying_maybe (DynamicStage1ByMode while flying, each fixed sub-step): the take-off
// push ends (+0x1385 with +0x1388 run out; else +0x13d1 cleared while it runs), the timer +0x1434 runs down; the forces
// into +0x17f0, each kept in its record: gravity (+0x17a8) times the mass, the push (+0x1790), the dash, the move
// (+0x179c, unless +0xec4 bit 11), the drag (+0x17c0, clamped), the lift along the node's up (+0x17b4, from the speed
// along its at), the partner tether (without +0x13d8: +0x17d8 / +0x17cc), the aux (+0x17e4), the thrust, the game
// manager's force (times +0xe64 with +0x13d8), the push between the heroes +0x17fc, the lunge, the external push, the
// +0x13d8 force, the downward pull of +0xec8 bit 16 with a mass and the target height; over the mass into the velocity
// (with +0x13a4 its part against +0x135c removed; +0xec8 bits 9 / 10 clear y / x and z; bit 19 adds +0x135c times +0xbc0
// once); then the displacement.
void CKHkS08Hero::DynamicStage1Flying(float dt) {
    ComputeCameraRelativeMove();  // 0x00311df0
    if (m_unk1385 != 0) {
        if (!(m_unk1388 > 0.0f)) {
            m_unk1385 = 0;
        } else {
            m_unk13d1 = 0;
        }
    }
    {
        const float timer = AsF32(m_unk1434);
        if (timer > 0.0f) SetF32(m_unk1434, timer - dt);
    }
    const float mass = GetMass();  // 0x002f8818
    const CVector3& zero = kHeroZeroVector;  // TOC +0x22dc
    m_unk17f0 = zero.x;
    m_unk17f4 = zero.y;
    m_unk17f8 = zero.z;
    auto add = [this](const CVector3& f) {
        m_unk17f0 = f.x + m_unk17f0;
        m_unk17f4 = f.y + m_unk17f4;
        m_unk17f8 = f.z + m_unk17f8;
    };
    m_unk17a8 = ComputeFlightGravityAccel();  // 0x00313340
    add(AccelToForce(mass, &m_unk17a8));      // 0x0030fb68
    m_unk1790 = ComputeFlightInputForce(dt);  // 0x00315970
    add(m_unk1790);
    add(ComputeFlightDashImpulse(dt));  // 0x00313a48
    if ((m_unkec4 & 0x800u) == 0) {
        float bx = zero.x;
        float by = zero.y;
        float bz = zero.z;
        float mx = bx;
        float my = by;
        float mz = bz;
        const uint8_t inAir = m_unk13d1;
        bool computeMove = true;
        if (m_unk138c > 0.0f && inAir != 0) {
            // the push runs in the air: no move, unless +0x13cd
            if (m_unk13cd == 0) computeMove = false;
        }
        if (computeMove) {
            const uint8_t backwards = m_unk13a4;
            if (backwards == 0) {
                const float s = m_unk91c;
                const float speed = m_unk1378;
                mx = (m_unk37c * s) * speed;
                mz = (m_unk384 * s) * speed;
                my = (m_unk380 * s) * speed;
            } else {
                mx = -m_unk1294;
                mz = -m_unk129c;
                my = -m_unk1298;
            }
            if (inAir != 0) {
                const CVector3& axis = kHeroAxisY;  // TOC +0x22e0
                const float k = m_unk9ec;
                bz = k * axis.z;
                bx = k * axis.x;
                by = k * axis.y;
                if ((m_unkec8 & 2u) == 0) {
                    const float speed = m_unk1378;
                    bz = bz * speed;
                    bx = bx * speed;
                    by = by * speed;
                }
            }
            if (backwards == 0 && inAir != 0 && m_unk12c4 > m_unk964) {
                mx = mx + bx;
                my = my + by;
                mz = mz + bz;
            }
        }
        if (m_unk13d8 != 0 && m_unk13fc == 0) {
            m_unk179c = zero;
        } else {
            m_unk179c = CVector3{mx, my, mz};
        }
        add(m_unk179c);
    }
    m_unk17c0 = ComputeFlightDragForce();  // 0x003137f8
    m_unk17c0 = ClampDragToStopVelocity(dt, &m_unk17c0, &Vec(m_unk127c));  // 0x00311c50
    float lx = zero.x;
    float ly = zero.y;
    float lz = zero.z;
    if (m_unk13a4 == 0 && m_unk160 != 0x40) {
        const RwFrame* frame = static_cast<const CSGMovable*>(m_pKGLObject)->m_pRwFrame;
        const RwV3d& at = frame->modelling.at;
        const RwV3d& up = frame->modelling.up;
        float along = 0.0f;  // TOC +0x22e4
        const float d = ppc::fmadds(m_unk1284, at.z, ppc::fmadds(m_unk127c, at.x, m_unk1280 * at.y));
        if (d > 0.0f) along = d;
        float k;
        if (m_unk13d1 != 0 || m_unk18d0 == 6) {
            k = m_unk954;
        } else {
            k = m_unk9a0;
        }
        k = k * along;
        lz = up.z * k;
        lx = up.x * k;
        ly = up.y * k;
    }
    {
        const float s = UpdateAndGetField11C8();  // 0x00310330
        m_unk17b4 = CVector3{s * lx, s * ly, s * lz};
    }
    {
        const float ax = m_unk17f0 + m_unk17c0.x;
        const float az = m_unk17f8 + m_unk17c0.z;
        const float ay = m_unk17f4 + m_unk17c0.y;
        m_unk17f0 = ax;
        m_unk17f8 = az;
        m_unk17f4 = ay;
        m_unk17f0 = ax + m_unk17b4.x;
        m_unk17f8 = az + m_unk17b4.z;
        m_unk17f4 = ay + m_unk17b4.y;
    }
    if (m_unk13d8 == 0) {
        const CKGrpS08Hero* group = static_cast<const CKGrpS08Hero*>(m_pGrpHero);
        const float dampingRadius = group->m_unk114;
        const float dampingCoeff = group->m_unk11c;
        m_unk17d8 = ComputePartnerTetherSpringForce(group->m_unk110, group->m_unk118);  // 0x003103f0
        m_unk17cc = ComputePartnerTetherDampingForce(dampingRadius, dampingCoeff);      // 0x0030fe70
        const float ax = m_unk17f0 + m_unk17d8.x;
        const float az = m_unk17f8 + m_unk17d8.z;
        const float ay = m_unk17f4 + m_unk17d8.y;
        m_unk17f0 = ax;
        m_unk17f8 = az;
        m_unk17f4 = ay;
        m_unk17f0 = ax + m_unk17cc.x;
        m_unk17f8 = az + m_unk17cc.z;
        m_unk17f4 = ay + m_unk17cc.y;
    }
    m_unk17e4 = ComputeFlightAuxForce(mass);  // 0x00314dc8 (its f27: the mass)
    add(m_unk17e4);
    add(ComputeFlightThrustForce(dt));  // 0x00313f50
    {
        CVector3 e = GetGameManagerExternalForce();  // 0x0030f8f0
        if (m_unk13d8 != 0) {
            const float s = m_unke64;
            e.z = e.z * s;
            e.x = e.x * s;
            e.y = e.y * s;
        }
        add(e);
        m_unk17f0 = m_unk17f0 + m_unk17fc;
        m_unk17f8 = m_unk17f8 + m_unk1804;
        m_unk17f4 = m_unk17f4 + m_unk1800;
    }
    add(StartLungeFromMark(dt));                  // 0x003008d8
    add(ComputeExternalPushForce(dt));            // 0x003011c8
    add(ComputeFlightField13D8Displacement(dt));  // 0x00313d20
    {
        float px = zero.x;
        float py = zero.y;
        float pz = zero.z;
        if ((m_unkec8 & 0x10000u) != 0 && m_unk1258 > 1.0e-1f) {  // TOC +0x22f4
            const ICollisionMesh* ground = static_cast<const ICollisionMesh*>(GetGroundInfo());  // 0x00361b68
            const float k = (ground->m_ui16PropertiesFlags & 0x200u) == 0 ? m_unka6c : m_unka68;
            pz = kHeroDown.z * k;  // TOC +0x22f8 -> 0x00c50d7c
            px = kHeroDown.x * k;
            py = kHeroDown.y * k;
        }
        add(CVector3{px, py, pz});
    }
    add(ComputeFlightTargetHeightForce());  // 0x00314b58
    const CVector3 sum{m_unk17f0, m_unk17f4, m_unk17f8};
    const CVector3 accel = ForceToAccel(dt, mass, &sum);      // 0x00310ba8
    const CVector3 delta = AccelToVelocityDelta(dt, &accel);  // 0x0030fb98
    m_unk127c = m_unk127c + delta.x;
    m_unk1280 = m_unk1280 + delta.y;
    m_unk1284 = m_unk1284 + delta.z;
    if (m_unk13a4 != 0) {
        const float vx = m_unk127c;
        const float vy = m_unk1280;
        const float vz = m_unk1284;
        const float d = ppc::fmadds(vz, m_unk1364, ppc::fmadds(vx, m_unk135c, vy * m_unk1360));
        if (d < 0.0f) {
            const float k = -d;
            m_unk1284 = ppc::fmadds(k, m_unk1364, vz);
            m_unk127c = ppc::fmadds(m_unk135c, k, vx);
            m_unk1280 = ppc::fmadds(k, m_unk1360, vy);
        }
    }
    const uint32_t flags = m_unkec8;
    if ((flags & 0x200u) != 0) m_unk1280 = 0.0f;
    if ((flags & 0x400u) != 0) {
        m_unk1284 = 0.0f;
        m_unk127c = 0.0f;
    }
    if ((flags & 0x80000u) != 0) {
        m_unkec8 &= ~0x80000u;
        const float k = m_unkbc0;
        m_unk127c = ppc::fmadds(m_unk135c, k, m_unk127c);
        m_unk1280 = ppc::fmadds(m_unk1360, k, m_unk1280);
        m_unk1284 = ppc::fmadds(m_unk1364, k, m_unk1284);
    }
    AccumulateFlightDisplacement(dt);  // 0x00312f98
}

// 0x003167e0 CKHkS08Hero_UpdateFlyingLocomotion_maybe (the frame hook UpdateLocomotionByMode while flying, and
// UpdateMovementModeFromInput): +0x13d1 (near the ground: within 0.1 while airborne, or on a ground of property 0x200;
// +0x1440 counts the time away from it), the dash request, the ground probe; then (without +0xec8 bit 10) the ground under
// the hero moved back along +0x13dc (+0x13d8 off without a wall or on a ground without property 0x100, or slow along
// +0x13e8, or away from the ground), the backwards flight +0x13a4 (the leader against the move with speed), the take-off
// and flap requests from input 4 (+0x388 against the hold time +0x1380: +0x13ce / +0x13cf; a long hold away from a
// climbing partner lands, +0xec4 bit 24), the take-off push +0x1385 / +0x1388 on +0x358 bit 20, the thrust record on it
// with +0x13d8 (+0x1434), +0xec4 bits 12 / 26 while thrusting, the airborne direction lock, the landing after +0x1440
// passes +0x9f0 / +0x9f4 (by the speed against +0x9f8) unless held up, and the altitude probes; then the aimed enemy
// (+0x1d28; the group's flag 0x400).
void CKHkS08Hero::UpdateFlyingLocomotion(float dt) {
    const ICollisionMesh* groundInfo = static_cast<const ICollisionMesh*>(GetGroundInfo());  // 0x00361b68
    const uint8_t onFlightGround =
        groundInfo != nullptr ? static_cast<uint8_t>((groundInfo->m_ui16PropertiesFlags >> 9) & 1u) : 0;
    m_unk13d2 = m_unk13d1;
    const float kNear = 1.0e-1f;  // TOC +0x22f4
    if (((m_unk354 & 1u) != 0 && m_gcCurDatasInOut.m_fdH > kNear) || onFlightGround != 0) {
        m_unk13d1 = 1;
        m_unk1440 = 0;
        if (m_unk1258 < kNear) TryStartFlightDash();  // 0x00310ef0
    } else {
        m_unk13d1 = 0;
        SetF32(m_unk1440, AsF32(m_unk1440) + dt);
        if (!(m_unk1258 >= kNear)) TryStartFlightDash();
    }
    if ((m_unkecc & 0x1000000u) == 0 && (m_unkecc & 0x800000u) == 0) {
        ProbeGroundAndUpdateLocomotionFlags();  // 0x003110a8
    }
    if ((m_unkec8 & 0x400u) == 0) {
        CKSrvCollision* collision = static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision);
        // The ground under the hero moved back along +0x13dc (4 times), against the walls.
        const float dx = -m_unk13dc * 4.0f;  // TOC +0x2380
        const float dy = -m_unk13e0 * 4.0f;
        const float dz = -m_unk13e4 * 4.0f;
        CLine line;
        line.m_start = CVector3{m_unk54c, m_unk550, m_unk554};
        line.m_VectDir = CVector3{dx, dy, dz};
        CSlideGroundEdgeDatasOut slide;
        const uint8_t wall = collision->ResolveWallSegmentMovement(&line, 0.0f, &slide, nullptr, nullptr, 1);  // 0x001996b0
        CVector3 point{(m_unk54c + dx) + slide.m_v3BouncingVector.x, (m_unk550 + dy) + slide.m_v3BouncingVector.y,
                       (m_unk554 + dz) + slide.m_v3BouncingVector.z};
        CGroundContactDatasInOut contact;
        contact.m_eContactStatus = 3;
        contact.m_i32FaceIndex = -1;
        contact.m_ui8SectorNumber = 0;
        contact.m_pGround = nullptr;
        GroundContact_ProbeGroundPoint(&contact, &point, nullptr);  // 0x00583ef8 (TocBridge)
        if (contact.m_pGround != nullptr &&
            (static_cast<const ICollisionMesh*>(contact.m_pGround)->m_ui16PropertiesFlags & 0x100u) == 0) {
            m_unk13d8 = 0;
        }
        if (wall == 0) m_unk13d8 = 0;
        const float side = std::fabs(ppc::fmadds(m_unk1284, m_unk13f0, ppc::fmadds(m_unk127c, m_unk13e8, m_unk1280 * m_unk13ec)));
        const uint8_t inAir = m_unk13d1;
        if (m_unk9c4 > side || inAir == 0) m_unk13d8 = 0;
        // The backwards flight.
        {
            const float d = ppc::fmadds(m_unk1364, m_unk384, ppc::fmadds(m_unk135c, m_unk37c, m_unk1360 * m_unk380));
            uint8_t wanted;
            if (m_unk13a4 == 0) {
                wanted = (m_unk12c4 > m_unk964 && -m_unk9b0 > d) ? static_cast<uint8_t>(m_unk13cf == 0 ? 1 : 0) : 0;
            } else if (!(d < 0.0f) && m_unk12c4 >= 0.5f) {  // TOC +0x2300
                wanted = 0;
            } else {
                wanted = m_unk1378 > kNear ? 1 : 0;  // ble: not above (NaN too) gives 0
            }
            m_unk13a4 = m_ui8Hero == m_ui8TrackedLeader ? wanted : 0;
            if (inAir == 0) m_unk13a4 = 0;
        }
        m_unk13cf = 0;
        m_unk13ce = 0;
        bool landed = false;
        if (IsAnyComboKindActive() != 0) {  // 0x002fd030
            SetF32(m_unk1380, 0.0f);
            m_unk1384 = 0;
        } else {
            const float held = m_unk388;
            const float hold = AsF32(m_unk1380);
            float next = held;
            if (held == 0.0f) {  // TOC +0x22e4
                const CAnimationDictionary* dictionary = static_cast<const CAnimationDictionary*>(m_pAnimDico);
                const RtAnimAnimation* flap =
                    CAnimationManager_GetAnimation(static_cast<uint32_t>(dictionary->m_apAnimations[0x3a]));  // +0xe8
                const float duration = flap == nullptr ? 1.0f : flap->duration;  // TOC +0x2304
                if (!(duration > hold) && m_unk948 > hold) m_unk13ce = 1;
            } else if (hold != 0.0f) {
                if (!(m_unk978 >= hold)) {
                    GetGroundInfo();  // 0x00361b68 (not used)
                    const CKGrpS08Hero* group = static_cast<const CKGrpS08Hero*>(m_pGrpHero);
                    const float gap318 = WordAsFloat(group->m_unk318);
                    const float gap314 = WordAsFloat(group->m_unk2d4[16]);
                    bool stay = (m_unkec4 & 0x40000u) != 0;
                    if (!stay && PartnerShouldStayClimbing() != 0) {  // 0x002f8628
                        stay = gap318 + gap314 > group->m_unk108 - 3.0f;  // 0x002ce518; TOC +0x2384
                    }
                    if (!stay) {
                        SetMovementMode(0);  // 0x00340c18
                        m_unkec4 = (m_unkec4 & ~0x1000000u) | 0x1000000u;
                        landed = true;
                    }
                }
            } else if (m_unk13a4 != 0 && m_unk12c4 < m_unk9fc && (m_unk18d0 == 3 || m_unk18d0 == 4)) {
                m_unk13a4 = 0;
                m_unk13cf = 1;
                m_unk13ce = 1;
            } else if (IsInSpecialAnim(this) == 0 || m_unk13c0 > m_unk978) {
                m_unk13ce = 1;
            }
            if (!landed) {
                SetF32(m_unk1380, next);
                m_unk1384 = 0;
            }
        }
        if (landed) {
            // the hero landed: nothing more this frame (the aimed enemy is not looked for either)
            return;
        }
        if ((m_unk358 & 0x100000u) != 0 && m_unk13d1 == 0 && m_unk1388 <= 0.0f && (m_unk354 & 0x800u) == 0 &&
            (m_unk35c & 2u) == 0) {
            SetDirectionLock(1);  // 0x00354cf0 and the +0x354 bits
            m_unk1385 = 1;
            m_unk1388 = m_unk98c;
            m_unk1384 = 1;
        }
        if ((m_unk358 & 0x100000u) != 0 && m_unk13d8 != 0) {
            HeroTimedImpulse thrust{m_unk9b8, m_unk9bc, 0, kHeroZeroVector, 0.0f, 0.0f};
            thrust.Start(CVector3{m_unk13dc, m_unk13e0, m_unk13e4});
            m_unk13f4 = thrust.m_magnitude;
            SetF32(m_unk13f8, thrust.m_duration);
            m_unk1400 = thrust.m_dir.x;
            m_unk1404 = thrust.m_dir.y;
            m_unk1408 = thrust.m_dir.z;
            SetF32(m_unk140c, thrust.m_left);
            SetF32(m_unk1410, thrust.m_last);
            m_unk13fc = 1;
            m_unk1384 = 1;
            SetF32(m_unk1434, m_unk9c8);
        }
        if (m_unk13fc != 0) {
            m_unk13d8 = 0;
            m_unkec4 |= 0x1000u | 0x4000000u;
        } else if ((m_unkec4 & 0x4000000u) != 0) {
            m_unkec4 &= 0xfbffefffu;
        }
        {
            uint8_t request = 0;
            if (m_unk13d3 != 0 && m_unk18d0 != 1) request = m_unk18d0 != 2 ? 1 : 0;
            m_unk13d3 = 0;
            m_unk13ce = (m_unk13ce | request) != 0 ? 1 : 0;
        }
        if ((m_unk354 & 0x800u) != 0 || (m_unk35c & 2u) != 0) {
            m_unk13ce = 0;
            SetF32(m_unk1380, 0.0f);
        }
        SetDirectionLock(1);  // 0x00354cf0 and the +0x354 bits
        const float landTime = m_unk12d0 >= m_unk9f8 ? m_unk9f0 : m_unk9f4;
        if ((m_unkec8 & 2u) != 0 || !(m_unk138c <= 0.0f) || m_unk1388 > 0.0f) m_unk1440 = 0;
        if ((m_unkec4 & 0x2000000u) == 0 && AsF32(m_unk1440) > landTime && (m_unkec4 & 0x40000u) == 0 &&
            reinterpret_cast<const uint8_t*>(&GameManagerHeroRecord(m_ui8Hero)[6])[0] == 0 &&  // the record's byte +0xe10
            (PartnerShouldStayClimbing() == 0 || m_ui8Hero == m_ui8TrackedLeader)) {
            SetDirectionLock(0);  // 0x00354cf0 and the +0x354 / +0x364 bits, +0x590
            SetMovementMode(0);   // 0x00340c18
        }
        UpdateFlightAltitudeAndProbes();  // 0x00312bb0
    }
    m_unk1d28 = 0;
    const CKGrpS08Hero* group = static_cast<const CKGrpS08Hero*>(m_pGrpHero);
    if ((group->m_unkf8 & 0x400u) != 0) {
        const float length =
            std::sqrt(ppc::fmadds(m_unk1364, m_unk1364, ppc::fmadds(m_unk135c, m_unk135c, m_unk1360 * m_unk1360)));
        if (length > kNear) {
            // STUB(C2.7: targets): CKHkS08Hero_FindBestEnemyInAimCone_maybe 0x2fe5b8 (+0x1d38's cone, the facing) finds no
            // enemy before the enemies are ported; then CKHkS08Hero_GetAimPointOnEnemy 0x2fdec8 into +0x1d2c.
            DOTD_STUB_ONCE("CKHkS08Hero_UpdateFlyingLocomotion_maybe 0x3167e0: the aimed enemy (C2.7)");
            m_unk1d28 = 0;
        }
    }
}

// 0x00315088 CKHkS08Hero_LocoState0_Flying: the locomotion state in the air. Each frame the velocity loses its part into
// the wall touched (+0x354 bit 18, the wall normal +0x61c), into the ground in the air (+0x564), into +0x514 (+0x368 bit
// 7); the animation 0x43 without a move stops it in x / z; a pending velocity direction +0x11ec takes its length; the push
// between the heroes +0x17fc. Entering resets the flight's state (+0x17f0, +0x133c, +0xec4 bits 0..2, the push and flap
// fields, the roll approaches +0x13a8 / +0x13b4, +0x13d1 from +0x354 bit 0, +0x368 bit 5, +0x35c bit 31 unless +0xec4 bit
// 17, +0x358 bit 20 / +0x13d3 for a take-off, +0x1440, +0xec8 bit 7, the dynamic entry's flag, +0x17fc, +0xecc bit 22, the
// impulsion state, +0x35c bit 7, +0x1d28); leaving resets them again (+0x3b8 = +0x540, the speed +0x530 halved, with
// +0x360 bit 9 the node's angles +0x594 / +0x598 from its frame, the records +0x13f4 / +0x1414).
uint8_t CKHkS08Hero::LocoFlying(IKTime*, int32_t phase, uint8_t other) {
    const CVector3& zero = kHeroZeroVector;  // TOC +0x22dc
    if (phase == 1) {
        m_unk17f0 = zero.x;
        m_unk17f8 = zero.z;
        m_unk17f4 = zero.y;
        m_unk133c = 0;
        m_unkec4 = (m_unkec4 & ~7u) | 3u;
        SetF32(m_unk1380, 0.0f);
        m_unk138c = 0.0f;
        m_unk1390 = 0.0f;
        m_unk1394 = 0.0f;
        m_unk13cc = 0;
        m_unk13cd = 0;
        m_unk13ce = 0;
        m_unk13cf = 0;
        m_unk13a4 = 0;
        m_unk137c = 0.0f;
        m_unk1340 = 0.0f;
        m_unk13a8.y = 90.0f;  // TOC +0x2358
        m_unk13a8.z = 0.0f;
        m_unk13a8.x = 0.0f;
        m_unk13b4.y = 1.5f;  // TOC +0x235c
        m_unk13b4.z = 0.0f;
        m_unk13b4.x = 0.0f;
        m_unk1388 = 0.0f;
        m_unk1385 = 0;
        m_unk1384 = 0;
        m_unk13d1 = static_cast<uint8_t>(m_unk354 & 1u);
        m_unk368 = (m_unk368 & ~0x20u) | 0x20u;
        ComputeCameraRelativeMove();  // 0x00311df0
        if ((m_unkec4 & 0x20000u) == 0) m_unk35c = (m_unk35c & 0x7fffffffu) | 0x80000000u;
        if (m_unk13d8 == 0) {
            if (m_unk13d1 == 0) {
                m_unk358 = (m_unk358 & ~0x100000u) | 0x100000u;
            } else if (PartnerShouldStayClimbing() == 0) {  // 0x002f8628
                m_unk358 = (m_unk358 & ~0x100000u) | 0x100000u;
                m_unk13d3 = 1;
            }
        }
        m_unk1440 = 0;
        m_unkec8 &= ~0x80u;
        static_cast<CKSrvDynamic*>(g_pEngine->m_srvDynamic)->SetEntryFlag(this, 1);  // 0x0023aff8
        m_unk17fc = zero.x;
        m_unk1804 = zero.z;
        m_unk1800 = zero.y;
        m_unkecc &= ~0x400000u;
        CKImpulsionCpnt* impulsion = static_cast<CKImpulsionCpnt*>(m_unk1190);
        impulsion->m_unk2c = 0;
        impulsion->m_unk24 = 0;
        impulsion->m_unk28 = 0;
        m_unk35c &= ~0x80u;
        m_unk1d28 = 0;
        return other;
    }
    if (phase == 2) {
        m_unk17f0 = zero.x;
        m_unk17f8 = zero.z;
        m_unk17f4 = zero.y;
        m_unk3b8 = m_unk540;
        m_unk3c0 = m_unk548;
        m_unk3bc = m_unk544;
        float speed = m_unk530;
        if (speed >= m_unk8dc) speed = m_unk8dc;
        m_unk530 = speed * 0.5f;  // TOC +0x2300
        if ((m_unk360 & 0x200u) != 0) {
            const RwFrame* frame = static_cast<const CSGMovable*>(m_pKGLObject)->m_pRwFrame;
            CMatrix34 local;
            std::memcpy(&local, &frame->modelling, sizeof(local));
            const float yaw = Vec3_GetYawAngleFromX(&local.m_at);  // 0x00244638
            Mat4_RotateInPlace(&local, &kHeroAxisY, (kHalfPi - yaw) * -57.2957801818847656f);  // 0x00240498; TOC +0x2360
            float pitch = Vec3_GetAngleInYZPlane(&local.m_up);  // 0x00244748
            if (pitch > kPi) pitch = pitch - kTwoPi;
            SetF32(m_unk594, pitch * kRadToDeg);
            float roll = Vec3_GetAngleInXYPlane(&local.m_right);  // 0x002443d8
            if (roll > kPi) roll = roll - kTwoPi;
            SetF32(m_unk598, roll * kRadToDeg);
        }
        m_unk360 &= ~0x200u;
        m_unkec4 = ((((m_unkec4 & ~8u) | 8u) & ~3u) | 1u);
        SetF32(m_unk1380, 0.0f);
        m_unk138c = 0.0f;
        m_unk1390 = 0.0f;
        m_unk1394 = 0.0f;
        m_unk13cc = 0;
        m_unk13cd = 0;
        m_unk13ce = 0;
        m_unk13cf = 0;
        m_unk13a4 = 0;
        m_unk13d2 = 0;
        m_unk13d1 = 0;
        m_unk368 = (m_unk368 & ~0x20u) | 0x20u;
        m_unk35c &= 0x7fffffffu;
        m_unkec8 &= ~0x80u;
        m_unk13d9 = 0;
        m_unk13d8 = 0;
        m_unk13dc = zero.x;
        m_unk13e4 = zero.z;
        m_unk13e0 = zero.y;
        m_unk13e8 = zero.x;
        m_unk13ec = zero.y;
        m_unk13f0 = zero.z;
        m_unkec4 &= 0xfbffefffu;
        SetF32(m_unk13f8, 0.0f);
        m_unk13f4 = 1.0f;  // TOC +0x2304
        m_unk1400 = zero.x;
        m_unk1408 = zero.z;
        m_unk1404 = zero.y;
        SetF32(m_unk1410, 0.0f);
        m_unk13fc = 0;
        SetF32(m_unk140c, 0.0f);
        m_unk1414 = 1.0f;
        m_unk1418 = 0.0f;
        m_unk1420 = zero.x;
        m_unk1428 = zero.z;
        m_unk1424 = zero.y;
        m_unk1430 = 0.0f;
        m_unk141c = 0;
        m_unk142c = 0.0f;
        m_unkec4 &= ~0x80000u;
        return other;
    }
    if (phase != 0) return other;
    float vx;
    float vy;
    float vz;
    if ((m_unk354 & 0x40000u) != 0) {
        float nx = m_wallSlide.m_v3Normal.x;  // +0x61c
        float ny = m_wallSlide.m_v3Normal.y;
        float nz = m_wallSlide.m_v3Normal.z;
        const float length = std::sqrt(ppc::fmadds(nz, nz, ppc::fmadds(nx, nx, ny * ny)));
        if (length != 0.0f) {
            const float inv = 1.0f / length;  // TOC +0x2304
            nz = nz * inv;
            nx = nx * inv;
            ny = ny * inv;
        }
        vx = m_unk127c;
        vy = m_unk1280;
        vz = m_unk1284;
        const float d = ppc::fmadds(nz, vz, ppc::fmadds(vx, nx, ny * vy));
        if (d < 0.0f) {
            const float k = -d;
            m_unk1284 = ppc::fmadds(k, nz, vz);
            m_unk127c = ppc::fmadds(k, nx, vx);
            m_unk1280 = ppc::fmadds(k, ny, vy);
        }
    }
    if (m_unk13d1 == 0) {
        vx = m_unk127c;
        vy = m_unk1280;
        vz = m_unk1284;
        const float d = ppc::fmadds(vz, m_unk56c, ppc::fmadds(vx, m_unk564, vy * m_unk568));
        if (d < 0.0f) {
            const float k = -d;
            m_unk1284 = ppc::fmadds(k, m_unk56c, vz);
            m_unk127c = ppc::fmadds(m_unk564, k, vx);
            m_unk1280 = ppc::fmadds(k, m_unk568, vy);
        }
    }
    if (m_unk160 == 0x43 && m_unk1378 == 0.0f) {
        m_unk1284 = 0.0f;
        m_unk127c = 0.0f;
    }
    if ((m_unk368 & 0x80u) != 0) {
        vx = m_unk127c;
        vy = m_unk1280;
        vz = m_unk1284;
        const float nx = m_unk514;
        const float ny = m_unk518;
        const float nz = m_unk51c;
        const float d = ppc::fmadds(nz, vz, ppc::fmadds(vx, nx, ny * vy));
        if (d < 0.0f) {
            m_unk1284 = vz - nz * d;
            m_unk127c = vx - nx * d;
            m_unk1280 = vy - ny * d;
        }
    }
    if (m_unk11ec != zero.x || m_unk11f0 != zero.y || m_unk11f4 != zero.z) {
        vx = m_unk127c;
        vy = m_unk1280;
        vz = m_unk1284;
        const float length = std::sqrt(ppc::fmadds(vz, vz, ppc::fmadds(vx, vx, vy * vy)));  // Math_Sqrtf
        const float dz = m_unk11f4;
        const float dx = m_unk11ec;
        const float dy = m_unk11f0;
        m_unk11f4 = zero.z;
        m_unk11ec = zero.x;
        m_unk11f0 = zero.y;
        m_unk1284 = length * dz;
        m_unk127c = length * dx;
        m_unk1280 = length * dy;
    }
    const CVector3 push = ComputePairedHotspotCollisionResponse(m_unka44);  // 0x00310888
    m_unk17fc = push.x;
    m_unk1804 = push.z;
    m_unk1800 = push.y;
    return other;
}

// 0x003141b0 CKHkS08Hero_UpdateFlyingMovement_maybe (UpdateMovement while flying): the hero node's matrix in the air.
// The once-only pushes of the animations 0x57 / 0x58 (+0xec8 bits 13 / 18 / 25), the air current's tube (the game
// manager record's +0x1c; C2.8), the yaw +0x538 stepped towards the move (the turn rate +0x1d14 / +0x8b8 / +0x95c; the
// dodge direction +0x11cc, the push +0x13e8, the move +0x37c, the facing +0x1288 or the velocity) or turned round by
// half a turn for the backwards take-off (+0x13cf); in the air (+0x13d1) the pitch +0x1340 follows the climb angle (the
// velocity crossed with +0x1368 against the facing, within +0x970 degrees, at +0x960 degrees a second) and the roll
// approach +0x13a8 the turn (+0x96c / +0x974 degrees), then +0x137c / +0x12e4 take the node's angles; near the ground
// the body tilt springs follow the ground normal.
void CKHkS08Hero::UpdateFlyingMovement(float dt) {
    CVector3* const position = &Vec(m_unk54c);
    {
        const uint32_t flags = m_unkec8;
        bool checkSlot = false;
        bool push = false;
        if ((flags & 0x2000u) != 0) {
            if ((flags & 0x40000u) != 0) {
                if (m_unk160 == 0x57) {
                    checkSlot = true;
                } else if ((flags & 0x2000000u) == 0) {
                    push = true;
                }
            } else {
                checkSlot = true;
            }
        } else if ((flags & 0x40000u) != 0) {
            if (m_unk160 == 0x57) {
                checkSlot = true;
            } else if ((flags & 0x2000000u) == 0) {
                push = true;
            }
        }
        if (push) {
            *position = ComputeBlendedVelocityFromFlagsEC8(position, 1.39999997615814209f, 2.0f);  // TOC +0x2334 / +0x2338
            uint32_t value = (m_unkec8 & ~0x4000u) | 0x4000u;
            value = (value & ~0x2000000u) | 0x2000000u;
            m_unkec8 = value;
        } else if (checkSlot) {
            AnimBlendSlot* slot = GetAnimBlendSlot();  // vt+0x194
            if (slot->m_unk14 == 0 && m_unk160 == 0x58 && (m_unkec8 & 0x2000000u) == 0) {
                m_unkec8 = (m_unkec8 & ~0x4000u) | 0x4000u;
                *position = ComputeBlendedVelocityFromFlagsEC8(position, 1.39999997615814209f, 1.0f);
                m_unkec8 = (m_unkec8 & ~0x2000000u) | 0x2000000u;
            }
        }
    }
    if (GameManagerHeroRecord(m_ui8Hero)[7] != 0) {  // the record's word +0xe14: the air current holding the hero
        // STUB(C2.8: air currents): CKHkS08AirCurrent_ClampPositionToTube_maybe 0x475278 (the current, +0x558, the
        // position) puts the position back into the current's tube. No air current holds a hero before the first fight.
        DOTD_STUB_ONCE("CKHkS08Hero_UpdateFlyingMovement_maybe 0x3141b0: the air current's tube (C2.8)");
    }
    CMatrix34 matrix;
    matrix.m_pos.x = 0.0f;
    matrix.m_ui32Flags = 0x20003;
    matrix.m_right.z = 0.0f;
    matrix.m_right.y = 0.0f;
    matrix.m_right.x = 0.0f;
    matrix.m_at.y = 0.0f;
    matrix.m_at.x = 0.0f;
    matrix.m_up.z = 0.0f;
    matrix.m_up.x = 0.0f;
    matrix.m_pos.z = 0.0f;
    matrix.m_pos.y = 0.0f;
    matrix.m_at.z = 1.0f;
    matrix.m_up.y = 1.0f;
    matrix.m_right.x = 1.0f;
    matrix.m_pos.x = position->x;
    matrix.m_pos.z = position->z;
    matrix.m_pos.y = position->y;
    matrix.m_ui32Flags &= ~0x20000u;
    float turnRate;
    if (m_unk1d10 != 0) {
        turnRate = m_unk1d14;
    } else if ((m_unkec8 & 0x80u) != 0) {
        turnRate = m_unk8b8;
    } else {
        turnRate = m_unk95c;
    }
    if ((m_unkec4 & 0x1000u) == 0) {
        bool steer = false;
        bool moveTurn = false;
        if (m_unk12c4 > 0.5f && m_unk13d1 != 0 && m_unk13cf == 0 && m_unk13d0 == 0) {  // TOC +0x2300
            steer = true;
        } else if ((m_unkec8 & 0x80u) != 0) {
            steer = true;
        } else if (m_unk13d1 == 0) {
            moveTurn = true;
        }
        bool turn = false;
        CVector3 direction;
        if (steer) {
            turn = true;
            if ((m_unkec8 & 0x80u) != 0) {
                direction = Vec(m_unk11cc);
            } else if (m_unk13d8 != 0) {
                direction = Vec(m_unk13e8);
            } else if (AsF32(m_unk1434) > 0.0f) {
                direction = Vec(m_unk37c);
            } else if (IsAnyComboKindActive() != 0 && m_unk1378 != 0.0f) {  // 0x002fd030
                direction = Vec(m_unk37c);
            } else {
                direction = Vec(m_unk127c);
            }
        } else if (moveTurn && m_unk1378 != 0.0f) {
            turn = true;
            direction = m_unk12d0 > 1.0e-1f ? Vec(m_unk1288) : Vec(m_unk37c);  // TOC +0x22f4
        }
        if (turn) {
            const float yaw = Vec3_GetYawAngleFromX(&direction);  // 0x00244638
            float approach[3] = {yaw, turnRate, m_unk538};
            FloatApproach_StepAngle(dt, approach);  // 0x00243748
            m_unk538 = approach[2];
        }
    }
    if (m_unk13cf != 0 && m_unk13d0 == 0 && m_unk160 != 0x43) {
        const float yaw = m_unk538 + kPi;
        m_unk538 = yaw;
        Mat4_RotateLocalYDeg((kHalfPi - yaw) * kRadToDeg, &matrix);  // 0x002413d0
    } else {
        Mat4_RotateLocalYDeg((kHalfPi - m_unk538) * kRadToDeg, &matrix);
    }
    CSGMovable* node = static_cast<CSGMovable*>(m_pKGLObject);
    if (m_unk13d1 == 0) {
        const CVector3 current = matrix.m_up;
        const CVector3 target = Vec(m_unk564);
        const CVector3 up = UpdateBodyTiltSprings(&current, &target);  // 0x002fbfc0
        Mat4_BuildFromUpAndForward(&matrix, &up, &matrix.m_at);        // 0x0023ff80 (the answer is not used)
        m_unk13a8.z = 0.0f;
        node->SetLocalMatrix(reinterpret_cast<const RwMatrix*>(&matrix));  // 0x000d0be8
        return;
    }
    // The pitch.
    {
        const float vx = m_unk127c;
        const float vy = m_unk1280;
        const float vz = m_unk1284;
        const float ax = m_unk1368;
        const float ay = m_unk136c;
        const float az = m_unk1370;
        const float t8 = az * vx;
        const float t11 = vz * ay;
        const float t12 = vy * ax;
        float cy = ppc::fmsubs(vz, ax, t8);
        float cx = ppc::fmsubs(vy, az, t11);
        float cz = ppc::fmsubs(ay, vx, t12);
        const float length = std::sqrt(ppc::fmadds(cz, cz, ppc::fmadds(cx, cx, cy * cy)));  // Math_Sqrtf
        if (length != 0.0f) {
            const float inv = 1.0f / length;
            cz = cz * inv;
            cx = cx * inv;
            cy = cy * inv;
        }
        float s = ppc::fmadds(cz, m_unk1364, ppc::fmadds(cx, m_unk135c, cy * m_unk1360));
        if (s <= -1.0f) {  // TOC +0x230c
            s = -1.0f;
        } else if (s >= 1.0f) {
            s = 1.0f;
        }
        float pitch = crt::Asinf(s);  // TocBridge_Math_Asinf_maybe
        if ((m_unkec8 & 0x10000000u) != 0) pitch = 0.0f;
        float target = m_unk970 * -1.74532923847436905e-2f;  // TOC +0x234c
        if (!(pitch <= target)) {
            const float high = m_unk970 * 1.74532923847436905e-2f;  // TOC +0x2350
            target = pitch >= high ? high : pitch;
        }
        if (m_unk12c4 < m_unk964 || m_unk13a4 != 0) {
            if (IsAbilityActive() == 0) target = 0.0f;  // 0x002fc228
        }
        const float diff = target - m_unk1340;
        const float sign = diff < 0.0f ? -1.0f : 1.0f;
        const float step = sign * (m_unk960 * dt);
        const float absStep = std::fabs(step);
        const float absDiff = std::fabs(target - m_unk1340);
        float pitchNew;
        if (absStep > absDiff) {
            const float current = m_unk1340;
            pitchNew = (target - current) + current;
        } else {
            pitchNew = step + m_unk1340;
        }
        m_unk1340 = pitchNew;
        Mat4_RotateLocalXDeg(pitchNew * kRadToDeg, &matrix);  // 0x00241118
    }
    // The roll.
    {
        const uint32_t flags = m_unkec8;
        uint32_t rollWord = 0;
        if ((flags & 0x10000000u) == 0) {
            float word = m_unk12c4 < m_unk964 ? m_unk974 : m_unk96c;
            std::memcpy(&rollWord, &word, 4);
        }
        const float roll = WordAsFloat(rollWord);
        float dot = 0.0f;  // TOC +0x22e4
        if (m_unk13d8 == 0 && (flags & 0x80u) == 0) {
            dot = ppc::fmadds(m_unk1370, m_unk384, ppc::fmadds(m_unk1368, m_unk37c, m_unk136c * m_unk380));
        }
        if (m_unk13a4 != 0 || m_unk160 == 0x41) {
            m_unk13b4.x = 0.0f;
            m_unk13a8.x = 0.0f;
        } else if (m_unk1374 < 0.0f) {
            const float side = dot < 0.0f ? -1.0f : 1.0f;
            m_unk13b4.x = side;
            m_unk13a8.x = side * roll;
        } else {
            if (dot <= -1.0f) {
                dot = -1.0f;
                m_unk13b4.x = -1.0f;
            } else {
                m_unk13b4.x = dot >= 1.0f ? 1.0f : dot;
                if (dot >= 1.0f) dot = 1.0f;
            }
            m_unk13a8.x = dot * roll;
        }
        FloatApproach_Step(dt, &m_unk13a8.x);         // 0x002436e8
        Mat4_RotateLocalZDeg(m_unk13a8.z, &matrix);  // 0x002419c0
    }
    m_unk12ec = 0.0f;
    m_unk12e8 = 0.0f;
    {
        const RwFrame* frame = node->m_pRwFrame;
        CVector3 up{frame->modelling.up.x, frame->modelling.up.y, frame->modelling.up.z};
        float pitch = Vec3_GetAngleInYZPlane(&up);  // 0x00244748
        if (pitch > kPi) pitch = pitch - kTwoPi;
        m_unk137c = pitch;
        float roll = Vec3_GetAngleInXYPlane(&up);  // 0x002443d8
        if (roll > kPi) roll = roll - kTwoPi;
        m_unk12e4 = roll;
    }
    node->SetLocalMatrix(reinterpret_cast<const RwMatrix*>(&matrix));  // 0x000d0be8
}

// 0x00313780 CKHkS08Hero_LocoState0_Flying_Condition: flying (movement mode 1).
uint8_t CKHkS08Hero::LocoFlyingCondition(IKTime*, uint8_t) { return IsFlyingMovementMode1(); }
