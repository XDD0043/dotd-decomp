// Reconstructed original translation unit: 0x30f588-0x312870 (GAME_TOC1, main_toc1), 32 functions, 27 live.
// Primary class: CKHkS08Hero  key 0x25c2  category Hook  size 0x1e00  vtable 0xb22c98
// Other owners: Vec3 (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x30f588  CKHkS08Hero_ResolveWallSegmentMovement_maybe  [dead]
//   [ ] 0x30f680  FUN_0030f680  [dead]
//   [x] 0x30f778  CKHkS08Hero_DynamicStage1ByMode_maybe
//   [x] 0x30f8c0  CKHkS08Hero_ScaleVec3_maybe
//   [x] 0x30f8f0  CKHkS08Hero_GetGameManagerExternalForce_maybe
//   [ ] 0x30f978  CKHkS08Hero_SumDisplacementVectors_maybe  [dead]
//   [ ] 0x30fae0  Vec3_AddTwoScaled_maybe
//   [x] 0x30fb68  CKHkS08Hero_AccelToForce_maybe
//   [x] 0x30fb98  CKHkS08Hero_AccelToVelocityDelta_maybe
//   [ ] 0x30fbc8  FUN_0030fbc8  [dead]
//   [ ] 0x30fd00  StaticInitAndDestruction_30fd00
//   [ ] 0x30fd30  _GLOBAL__D_30fd30
//   [ ] 0x30fd40  _GLOBAL__I_30fd40
//   [x] 0x30fd50  CKHkS08Hero_ComputeBlendedVelocityFromFlagsEC8_maybe
//   [x] 0x30fe18  CKHkS08Hero_GetExternalDisplacement_maybe
//   [x] 0x30fe70  CKHkS08Hero_ComputePartnerTetherDampingForce_maybe
//   [x] 0x30ffa0  CKHkS08Hero_DynamicStage3PredictPosition_maybe
//   [x] 0x3101e8  CKHkS08Hero_UpdateField794ByAnimAndElementLevel_maybe
//   [x] 0x310330  CKHkS08Hero_UpdateAndGetField11C8_maybe
//   [x] 0x3103f0  CKHkS08Hero_ComputePartnerTetherSpringForce_maybe
//   [x] 0x3105d8  CKHkS08Hero_ApplyPartnerTetherToVelocity_maybe
//   [x] 0x310708  CKHkS08Hero_UpdateLocomotionByMode_maybe
//   [x] 0x310888  CKHkS08Hero_ComputePairedHotspotCollisionResponse_maybe
//   [x] 0x310ba8  CKHkS08Hero_ForceToAccel_maybe
//   [ ] 0x310be0  CKHkS08Hero_UpdateOrientationAngles_maybe
//   [x] 0x310d88  CKHkS08Hero_UpdateForwardAndSpeedStats_maybe
//   [ ] 0x310e48  CKHkS08Hero_GetDistanceToHotspot4_maybe  [dead]
//   [x] 0x310ef0  CKHkS08Hero_TryRequestFlightLedgeHop_maybe
//   [x] 0x3110a8  CKHkS08Hero_UpdateLedgeGrab_maybe
//   [x] 0x311950  CKHkS08Hero_ComputeTimedAnimDisplacement_maybe
//   [x] 0x311c50  CKHkS08Hero_ClampDragToStopVelocity_maybe
//   [x] 0x311df0  CKHkS08Hero_ComputeCameraRelativeMove_maybe
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include <cmath>
#include <cstring>
#include "Renderware/rwcore/RwCamera.h"
#include "Spyro2008/groups/CKGrpS08Hero.h"
#include "Spyro2008/logic/CKS08GameManager.h"
#include "k2000/hooks/CKHkClimbZone.h"
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/math/Math.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/services/CKSrvCollision.h"
#include "k2000/services/CollisionDatas.h"
#include "k2000/services/ICollisionMesh.h"
#include "k2000/system/CTimeManager.h"
#include "k2000/system/IKTime.h"
#include "crt/ppc_ops.h"
#include "k2000/core/Stub.h"
#include "k2000/cameras/CKSrvCamera.h"
#include "k2000/math/Math.h"
#include "k2000/misc/Engine.h"
#include <cmath>

namespace {

// The game manager's record of a hero (+0xdf8 + hero * 0x20; CKS08GameManager m_unkDF4 words from index 1): a vector
// at +0x00 and one at +0x0c (the external forces: GetGameManagerExternalForce sums them), two bytes at +0x18 (the
// first: read by ProbeGroundAndUpdateLocomotionFlags) and a word at +0x1c.
uint32_t* GameManagerHeroRecord(uint8_t hero) {
    CKS08GameManager* manager = static_cast<CKS08GameManager*>(g_pEngine->m_gameManager);
    return &manager->m_unkDF4[1 + hero * 8u];
}
CVector3 RecordVector(const uint32_t* record, uint32_t word) {
    CVector3 v;
    std::memcpy(&v.x, &record[word], 4);
    std::memcpy(&v.y, &record[word + 1], 4);
    std::memcpy(&v.z, &record[word + 2], 4);
    return v;
}
void SetRecordVector(uint32_t* record, uint32_t word, const CVector3& v) {
    std::memcpy(&record[word], &v.x, 4);
    std::memcpy(&record[word + 1], &v.y, 4);
    std::memcpy(&record[word + 2], &v.z, 4);
}

// The hero group's per-hero tether direction (+0x2fc hero 0, +0x308 hero 1) and distance (+0x314 / +0x318), written by
// the group's pair geometry (CKGrpS08Hero_UpdateHeroPairGeometry_maybe 0x2d01d8, the AI family's); in the header they are
// still the words m_unk2d4[10..16] and m_unk318. Another hero index: the zero vector and 0.
CVector3 GroupTetherDirection(const CKGrpS08Hero* group, uint8_t hero) {
    CVector3 v = kHeroZeroVector;  // TOC1 +0x2244 -> 0x00c50d64
    const uint32_t* words = nullptr;
    if (hero == 0) {
        words = &group->m_unk2d4[10];  // +0x2fc
    } else if (hero == 1) {
        words = &group->m_unk2d4[13];  // +0x308
    }
    if (words != nullptr) {
        std::memcpy(&v.x, &words[0], 4);
        std::memcpy(&v.y, &words[1], 4);
        std::memcpy(&v.z, &words[2], 4);
    }
    return v;
}
float GroupTetherDistance(const CKGrpS08Hero* group, uint8_t hero) {
    float d = 0.0f;  // TOC1 +0x2248
    if (hero == 0) {
        std::memcpy(&d, &group->m_unk2d4[16], 4);  // +0x314
    } else if (hero == 1) {
        std::memcpy(&d, &group->m_unk318, 4);  // +0x318
    }
    return d;
}

// 0x002ce560 CKGrpS08Hero_GetTetherSpringStiffness_maybe (Spyro2008/groups/CKGrpS08Hero.cpp, AI family's unit; local
// copy): +0x12c with +0xfc set, else +0x118.
float GroupTetherSpringStiffness(const CKGrpS08Hero* group) { return group->m_unkfc != 0 ? group->m_unk12c : group->m_unk118; }

}  // namespace

// 0x0030f778 CKHkS08Hero_DynamicStage1ByMode_maybe (CKSrvDynamic hook, each fixed sub-step): the forces of the movement
// mode (ground; flying, climbing and taking off are step 6), then DynamicStageTail. Nothing for a hero locked to an object.
void CKHkS08Hero::DynamicStage1ByMode(float dt) {
    if (IsLockedToObject() != 0) return;  // 0x00362040
    const int8_t mode = static_cast<int8_t>(GetMovementMode());  // 0x003401b8
    if (mode == 1) {
        DynamicStage1Flying(dt);  // 0x00315d60
    } else if (mode == 2) {
        if (ShouldStayClimbing() != 0) {  // 0x00342fa8
            DynamicStage1Climb(dt);  // 0x00322518
        } else {
            DynamicStage1ClimbDetach(dt);  // 0x00322d40
        }
    } else if (mode == 0) {
        if (ShouldJoinPartnerFlight() != 0) {  // 0x00341fa0
            DynamicStage1TakeOffToPartner(dt);  // 0x0031c788
        } else {
            DynamicStage1Ground(dt);  // 0x00319420
        }
    }
    DynamicStageTail(dt, 0);  // 0x003046a8
}

// 0x0030f8c0 CKHkS08Hero_ScaleVec3_maybe: `scale` times `v`.
CVector3 CKHkS08Hero::ScaleVec3(float scale, const CVector3* v) const {
    CVector3 out;
    out.z = scale * v->z;
    out.x = scale * v->x;
    out.y = scale * v->y;
    return out;
}

// 0x0030f8f0 CKHkS08Hero_GetGameManagerExternalForce_maybe: the sum of the two vectors of the hero's game manager record
// (+0xdf8 and +0xe04 + hero * 0x20).
CVector3 CKHkS08Hero::GetGameManagerExternalForce() const {
    const uint32_t* record = GameManagerHeroRecord(m_ui8Hero);
    const CVector3 a = RecordVector(record, 0);
    const CVector3 b = RecordVector(record, 3);
    return CVector3{b.x + a.x, b.y + a.y, b.z + a.z};
}

// 0x0030fb68 CKHkS08Hero_AccelToForce_maybe: `mass` times `accel`.
CVector3 CKHkS08Hero::AccelToForce(float mass, const CVector3* accel) const {
    CVector3 out;
    out.z = mass * accel->z;
    out.x = mass * accel->x;
    out.y = mass * accel->y;
    return out;
}

// 0x0030fb98 CKHkS08Hero_AccelToVelocityDelta_maybe: `dt` times `accel`.
CVector3 CKHkS08Hero::AccelToVelocityDelta(float dt, const CVector3* accel) const {
    CVector3 out;
    out.z = dt * accel->z;
    out.x = dt * accel->x;
    out.y = dt * accel->y;
    return out;
}

// 0x0030fe18 CKHkS08Hero_GetExternalDisplacement_maybe: +0x1668 unless +0xec4 bit 22 (then the zero vector).
CVector3 CKHkS08Hero::GetExternalDisplacement() const {
    if ((m_unkec4 & 0x400000u) != 0) return kHeroZeroVector;  // TOC1 +0x2244
    return CVector3{m_unk1668, m_unk166c, m_unk1670};
}

// 0x0030fe70 CKHkS08Hero_ComputePartnerTetherDampingForce_maybe: beyond half `radius` of tether (the group's distance),
// the velocity's part along the tether direction, when it points away (positive), pushed back by `coeff`; the zero
// vector with +0xec4 bit 22.
CVector3 CKHkS08Hero::ComputePartnerTetherDampingForce(float radius, float coeff) {
    CVector3 out = kHeroZeroVector;  // TOC1 +0x2244
    const CKGrpS08Hero* group = static_cast<const CKGrpS08Hero*>(m_pGrpHero);
    const CVector3 dir = GroupTetherDirection(group, m_ui8Hero);
    const float distance = GroupTetherDistance(group, m_ui8Hero);
    if (!(radius * 0.5f >= distance)) {  // TOC1 +0x225c
        const float dot = ppc::fmadds(dir.z, m_unk1284, ppc::fmadds(dir.x, m_unk127c, dir.y * m_unk1280));
        float push;
        if (dot < 0.0f) {  // TOC1 +0x2248
            push = -0.0f;  // TOC1 +0x2260 (0x80000000)
        } else {
            push = -dot;
        }
        push = push * coeff;
        out.z = push * dir.z;
        out.x = push * dir.x;
        out.y = push * dir.y;
    }
    if ((m_unkec4 & 0x400000u) != 0) out = kHeroZeroVector;
    return out;
}

// 0x0030ffa0 CKHkS08Hero_DynamicStage3PredictPosition_maybe (CKSrvDynamic hook, the remainder of the frame): the tail,
// the hero's game manager record cleared (the two force vectors, the two bytes, the word), and (unless +0x1813) the
// predicted point +0x181c: hot spot 0 in the world with +0xec8 bit 0, 10 or 31, else the position + the adjustment
// +0x1268 + the velocity over the remainder.
void CKHkS08Hero::DynamicStage3PredictPosition(float dt) {
    if (IsLockedToObject() != 0) return;  // 0x00362040
    DynamicStageTail(dt, 1);  // 0x003046a8
    // The group's +0x66 (a hero index) equal to this hero's calls KStub_Nop_4fe320 (nothing).
    uint32_t* record = GameManagerHeroRecord(m_ui8Hero);
    SetRecordVector(record, 0, kHeroZeroVector);  // +0xdf8
    SetRecordVector(record, 3, kHeroZeroVector);  // +0xe04
    record[7] = 0;               // +0xe14
    // The bytes +0xe10 / +0xe11, byte-addressed as CKHkS08Hero_2.cpp's ResetMovementFromFrame writes them.
    reinterpret_cast<uint8_t*>(&record[6])[0] = 0;
    reinterpret_cast<uint8_t*>(&record[6])[1] = 0;
    if (m_unk1813 != 0) return;
    const uint32_t flags = m_unkec8;
    if ((flags & 1u) != 0 || (flags & 0x400u) != 0 || (flags & 0x80000000u) != 0) {
        static_cast<CSGHotSpot*>(m_apHotSpots[0])->GetWorldPosition(reinterpret_cast<CVector3*>(&m_unk181c));  // 0x000ce790
        return;
    }
    const float x = m_unk54c + m_unk1268;
    const float y = m_unk550 + m_unk126c;
    const float z = m_unk554 + m_unk1270;
    m_unk181c = x;
    m_unk1820 = y;
    m_unk1824 = z;
    const float px = ppc::fmadds(dt, m_unk127c, kHeroZeroVector.x);
    const float py = ppc::fmadds(dt, m_unk1280, kHeroZeroVector.y);
    const float pz = ppc::fmadds(dt, m_unk1284, kHeroZeroVector.z);
    m_unk181c = px + x;
    m_unk1820 = py + y;
    m_unk1824 = pz + z;
}

// 0x00310330 CKHkS08Hero_UpdateAndGetField11C8_maybe: +0x11c8 (a float) set from the ground normal's y (+0x568) on the
// ground with +0x1539 == 1 and +0x1512, kept on the ground otherwise, 1.0 flying, the normal's y climbing; returned.
float CKHkS08Hero::UpdateAndGetField11C8() {
    if (IsMovementMode0() != 0) {  // 0x00340178
        if (m_unk1539 == 1 && m_unk1512 != 0) SetF32(m_unk11c8, m_unk568);
        return AsF32(m_unk11c8);
    }
    if (IsFlyingMovementMode1() != 0) {  // 0x00340188
        SetF32(m_unk11c8, 1.0f);  // TOC1 +0x2270
    } else {
        SetF32(m_unk11c8, m_unk568);
    }
    return AsF32(m_unk11c8);
}

// 0x003103f0 CKHkS08Hero_ComputePartnerTetherSpringForce_maybe: beyond half `radius` the group's tether direction times
// (distance - radius / 2) times the spring stiffness; the zero vector with +0xec4 bit 22, or on a climb zone unless its
// linked object (+0x38) has bit 23 of its +0x0c. `unused` (the group's +0x118) is not read.
CVector3 CKHkS08Hero::ComputePartnerTetherSpringForce(float radius, float /*unused*/) {
    const float half = radius * 0.5f;  // TOC1 +0x225c
    const CKGrpS08Hero* group = static_cast<const CKGrpS08Hero*>(m_pGrpHero);
    CVector3 out = GroupTetherDirection(group, m_ui8Hero);
    const float distance = GroupTetherDistance(group, m_ui8Hero);
    float k = 0.0f;  // TOC1 +0x2248
    if (!(distance <= half)) k = (distance - half) * GroupTetherSpringStiffness(group);  // 0x002ce560
    out.x = k * out.x;
    out.y = k * out.y;
    out.z = k * out.z;
    if ((m_unkec4 & 0x400000u) != 0) return kHeroZeroVector;
    // In a climb zone the spring only pulls when the zone's body (+0x38) has its flag bit 23
    // (CKHkClimbZone_GetLinkedObjectFlagC23_maybe 0x456bc8); without a body (every LVL010 zone) it is zeroed.
    if (m_unk1694 != nullptr && m_unk1694->GetLinkedObjectFlagC23() == 0) return kHeroZeroVector;
    return out;
}

// 0x003105d8 CKHkS08Hero_ApplyPartnerTetherToVelocity_maybe: with +0x1674 and without +0xec4 bit 22, the velocity
// (+0x127c) loses its part against the group's tether direction (+0x2fc / +0x308) when it points against it.
void CKHkS08Hero::ApplyPartnerTetherToVelocity() {
    if (m_unk1674 == 0) return;
    if ((m_unkec4 & 0x400000u) != 0) return;
    const CKGrpS08Hero* group = static_cast<const CKGrpS08Hero*>(m_pGrpHero);
    const CVector3 dir = GroupTetherDirection(group, m_ui8Hero);
    const float vx = m_unk127c;
    const float vy = m_unk1280;
    const float vz = m_unk1284;
    const float dot = ppc::fmadds(dir.z, vz, ppc::fmadds(vx, dir.x, dir.y * vy));
    if (dot >= 0.0f) return;  // TOC1 +0x2248
    const float push = -dot;
    m_unk1284 = ppc::fmadds(push, dir.z, vz);
    m_unk127c = ppc::fmadds(push, dir.x, vx);
    m_unk1280 = ppc::fmadds(push, dir.y, vy);
}

// 0x00310708 CKHkS08Hero_UpdateLocomotionByMode_maybe (CKSrvDynamic hook, once per frame with the frame's dt): with
// +0xec8 bit 1 the timer +0x122c runs by +0x88c; then the locomotion of the movement mode: on the ground
// UpdateGroundLocomotionState (and the flying one when it took off); flying, climbing and taking off are step 6.
void CKHkS08Hero::UpdateLocomotionByMode(float dt) {
    (void)dt;  // passed to the flying / climbing / take-off locomotions (step 6)
    if (IsLockedToObject() != 0) return;  // 0x00362040
    if ((m_unkec8 & 2u) != 0) m_unk122c = m_unk122c + m_unk88c;
    const int8_t mode = static_cast<int8_t>(GetMovementMode());  // 0x003401b8
    bool flying = mode == 1;
    if (mode == 2) {
        if (ShouldStayClimbing() != 0) {  // 0x00342fa8
            UpdateClimbSustainedLocomotion(dt);  // 0x00325108
        } else {
            UpdateClimbLocomotion(dt);  // 0x00325c88
        }
    } else if (mode == 0) {
        if (ShouldJoinPartnerFlight() != 0) {  // 0x00341fa0
            UpdateTakeOffToPartnerLocomotion(dt);  // 0x0031b8c8
        } else {
            UpdateGroundLocomotionState();  // 0x0031a040
            if (IsFlyingMovementMode1() != 0) flying = true;  // 0x00340188
        }
    }
    if (flying) {
        UpdateFlyingLocomotion(dt);  // 0x003167e0
    }
}

// 0x00310888 CKHkS08Hero_ComputePairedHotspotCollisionResponse_maybe: the segments from the hero's position (at the hot
// spot's height) to two of its hot spots (hero 0: 25 then 24, hero 1: 24 then 23) against the walls; each slide (2)
// adds `stiffness` times its bounce vector and sets an +0xecc flag (0x200 / 0x80); a free first segment after a slide
// turns 0x200 into 0x400, a free second one 0x80 into 0x100. LocoState4_Ground stores the sum at +0x17fc.
CVector3 CKHkS08Hero::ComputePairedHotspotCollisionResponse(float stiffness) {
    CVector3 out = kHeroZeroVector;  // TOC1 +0x2244
    CKSrvCollision* collision = static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision);
    {
        const float px = m_unk54c;
        const float pz = m_unk554;
        CVector3 spot;
        static_cast<CSGHotSpot*>(m_apHotSpots[m_ui8Hero == 0 ? 25 : 24])->GetWorldPosition(&spot);  // 0x000ce790
        CLine line;
        line.m_start = {px, spot.y, pz};
        line.m_VectDir = {spot.x - px, spot.y - spot.y, spot.z - pz};
        CSlideGroundEdgeDatasOut slide;
        if (collision->ResolveWallSegmentMovement(&line, 0.0f, &slide, nullptr, nullptr, 1) == 2) {  // 0x001996b0
            m_unkecc |= 0x200u;
            out.x = ppc::fmadds(stiffness, slide.m_v3BouncingVector.x, out.x);
            out.y = ppc::fmadds(stiffness, slide.m_v3BouncingVector.y, out.y);
            out.z = ppc::fmadds(stiffness, slide.m_v3BouncingVector.z, out.z);
        } else if ((m_unkecc & 0x200u) != 0) {
            m_unkecc = (m_unkecc & ~0x600u) | 0x400u;
        }
    }
    {
        const float pz = m_unk554;
        const float px = m_unk54c;
        CVector3 spot;
        static_cast<CSGHotSpot*>(m_apHotSpots[m_ui8Hero == 0 ? 24 : 23])->GetWorldPosition(&spot);  // 0x000ce790
        CLine line;
        line.m_start = {px, spot.y, pz};
        line.m_VectDir = {spot.x - px, spot.y - spot.y, spot.z - pz};
        CSlideGroundEdgeDatasOut slide;
        if (collision->ResolveWallSegmentMovement(&line, 0.0f, &slide, nullptr, nullptr, 1) == 2) {  // 0x001996b0
            m_unkecc |= 0x80u;
            out.x = ppc::fmadds(slide.m_v3BouncingVector.x, stiffness, out.x);
            out.z = ppc::fmadds(slide.m_v3BouncingVector.z, stiffness, out.z);
            out.y = ppc::fmadds(slide.m_v3BouncingVector.y, stiffness, out.y);
        } else if ((m_unkecc & 0x80u) != 0) {
            m_unkecc = (m_unkecc & ~0x180u) | 0x100u;
        }
    }
    return out;
}

// 0x00310ba8 CKHkS08Hero_ForceToAccel_maybe: `force` over `mass` (the first float, the step, is not read).
CVector3 CKHkS08Hero::ForceToAccel(float /*unused*/, float mass, const CVector3* force) const {
    const float inverse = 1.0f / mass;  // TOC1 +0x2270
    CVector3 out;
    out.z = inverse * force->z;
    out.x = inverse * force->x;
    out.y = inverse * force->y;
    return out;
}

// 0x00310d88 CKHkS08Hero_UpdateForwardAndSpeedStats_maybe: +0x540 takes the node's facing (its modelling at row); with
// a frame dt the frame's move +0x1268 over dt gives the horizontal speed +0x530 and the vertical speed +0x534.
void CKHkS08Hero::UpdateForwardAndSpeedStats() {
    const RwFrame* frame = static_cast<const CSGMovable*>(m_pKGLObject)->m_pRwFrame;
    const float mx = m_unk1268;
    m_unk540 = frame->modelling.at.x;
    m_unk548 = frame->modelling.at.z;
    m_unk544 = frame->modelling.at.y;
    const float mz = m_unk1270;
    const float my = m_unk126c;
    const float dt = g_pEngine->m_timeManager->m_pTime->m_afDeltaTime[0];
    if (dt == 0.0f) return;  // TOC1 +0x2248
    const float inverse = 1.0f / dt;  // TOC1 +0x2270
    const float vx = mx * inverse;
    const float vz = mz * inverse;
    const float vy = my * inverse;
    const float speed = std::sqrt(ppc::fmadds(vz, vz, ppc::fmadds(vx, vx, 0.0f)));  // Math_Sqrtf 0x10690
    m_unk534 = vy;
    m_unk530 = speed;
}

namespace {
// The ProbeGroundAndUpdateLocomotionFlags exits that leave the ledge state: +0xec8 bits 9..11 (or with `keep1000` bit 12
// set and bit 9 cleared only), +0x354 bit 11, +0xec4 bits 10, 12, 13, 21 and +0xec8 bit 7 cleared.
void ClearLedgeFlags(uint32_t& ec4, uint32_t& ec8, uint32_t& f354, bool keep1000) {
    if (keep1000) {
        ec8 = (ec8 | 0x1000u) & ~0x200u;
    } else {
        ec8 &= ~0xe00u;
    }
    f354 &= ~0x800u;
    ec4 &= 0xffdfd3ffu;
    ec8 &= ~0x80u;
}
}  // namespace

// 0x00310ef0 CKHkS08Hero_TryRequestFlightLedgeHop_maybe (step 6 FLY; UpdateFlyingLocomotion without a mass): with +0x358
// bit 20 and no dash running (+0xecc bit 24), a wall ahead (the facing +0x135c times +0xa10 from the position) that is
// free +0xa14 higher requests the dash over it (+0xecc bit 23).
void CKHkS08Hero::TryStartFlightDash() {
    const float reach = m_unka10;
    const float lift = m_unka14;
    if ((m_unk358 & 0x100000u) == 0) return;
    if ((m_unkecc & 0x1000000u) != 0) return;
    CKSrvCollision* collision = static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision);
    CSlideGroundEdgeDatasOut slide;
    CLine line;
    line.m_start = CVector3{m_unk54c, m_unk550, m_unk554};
    line.m_VectDir = CVector3{reach * m_unk135c, reach * m_unk1360, reach * m_unk1364};
    if (collision->ResolveWallSegmentMovement(&line, 0.0f, &slide, nullptr, nullptr, 1) != 2) return;  // 0x001996b0
    const CVector3& axisY = kHeroAxisY;  // TOC1 +0x224c -> 0x00c50d40
    line.m_VectDir = CVector3{reach * m_unk135c, reach * m_unk1360, reach * m_unk1364};
    line.m_start = CVector3{ppc::fmadds(lift, axisY.x, m_unk54c), ppc::fmadds(lift, axisY.y, m_unk550),
                            ppc::fmadds(lift, axisY.z, m_unk554)};
    if (collision->ResolveWallSegmentMovement(&line, 0.0f, &slide, nullptr, nullptr, 1) == 2) return;
    m_unkecc = (m_unkecc & ~0x800000u) | 0x800000u;
}

// 0x003110a8 CKHkS08Hero_UpdateLedgeGrab_maybe: the ledge in front of a wall (+0x610's infos bit 2):
// two ground probes 3.5 above the position, pushed into the wall (+0x61c's opposite) by +0x794 + 1 / + 0.5, give the
// ledge heights above the hero (+0x11fc keeps the second contact); a segment into the wall at +0xbac + 0.5. Starts the
// ledge state (+0xec8 bits 7 / 10 / 22 / 23, the wall direction +0x11cc / +0x11dc, movement mode 0) when an airborne
// hero (+0x35c bit 16, +0x354 bit 0) meets a flat ledge (normal y > 0.95) within reach and falling slowly enough, keeps
// it (bits 9 / 11, the position lifted onto the ledge) or leaves it (bit 12 set: the climb up; or all cleared), and with
// the ledge animations 0x59 / 0x29 starts the climb up (bit 13) or leaves.
void CKHkS08Hero::ProbeGroundAndUpdateLocomotionFlags() {
    const uint8_t managerByte = reinterpret_cast<const uint8_t*>(&GameManagerHeroRecord(m_ui8Hero)[6])[0];  // +0xe10
    if (IsAnyComboKindActive() != 0 || (m_unkecc & 0x400000u) != 0) {  // 0x002fd030
        m_unkec8 &= ~0xc00u;
        return;
    }
    if (((m_wallSlide.m_ba8Infos >> 2) & 1u) == 0 && (m_unkec8 & 0x400u) == 0) return;
    const CVector3& axisY = kHeroAxisY;  // TOC1 +0x224c -> 0x00c50d40
    const float reach = 3.5f;  // TOC1 +0x2294
    const float nx = -m_wallSlide.m_v3Normal.x;
    const float ny = -m_wallSlide.m_v3Normal.y;
    const float nz = -m_wallSlide.m_v3Normal.z;
    // The first probe: +0x794 + 1 into the wall.
    CGroundContactDatasInOut contact;  // ground 0, face -1, status 3, sector 0
    CVector3 point;
    {
        const float ax = axisY.x * reach;
        const float ay = axisY.y * reach;
        const float az = axisY.z * reach;
        const float depth = m_unk794 + 1.0f;  // TOC1 +0x2270
        point.x = ppc::fmadds(nx, depth, ax + m_unk54c);
        point.y = ppc::fmadds(ny, depth, ay + m_unk550);
        point.z = ppc::fmadds(nz, depth, az + m_unk554);
    }
    GroundContact_ProbeGroundPoint(&contact, &point, nullptr);  // 0x00583ef8
    const float height1 = point.y - m_unk550;
    bool first = true;
    if (height1 >= reach || height1 < 0.0f) first = false;  // TOC1 +0x2248
    // The second: +0x794 + 0.5, into +0x11fc.
    {
        const float az = axisY.z * reach;
        const float ax = axisY.x * reach;
        const float ay = axisY.y * reach;
        const float depth = m_unk794 + 0.5f;  // TOC1 +0x225c
        point.x = ppc::fmadds(nx, depth, ax + m_unk54c);
        point.y = ppc::fmadds(ny, depth, ay + m_unk550);
        point.z = ppc::fmadds(nz, depth, az + m_unk554);
    }
    GroundContact_ProbeGroundPoint(&m_unk11fc, &point, nullptr);  // 0x00583ef8
    const float height2 = point.y - m_unk550;
    bool second = true;
    if (height2 >= reach || height2 < 0.0f) second = false;
    // The segment into the wall.
    CLine line;
    line.m_start.x = m_unk54c;
    line.m_start.y = (m_unk550 + m_unkbac) + 0.5f;
    line.m_start.z = m_unk554;
    line.m_VectDir = {nx, ny, nz};
    const float groundNormalY = contact.m_Normal.y;
    CSlideGroundEdgeDatasOut slide;
    const uint8_t wall = static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision)
                             ->ResolveWallSegmentMovement(&line, 0.0f, &slide, nullptr, nullptr, 1);  // 0x001996b0
    const float dH = m_gcCurDatasInOut.m_fdH;  // +0x4dc
    uint32_t ec8 = m_unkec8;
    bool tryStart = false;
    if ((ec8 & 0x2000u) != 0 || (ec8 & 0x40000u) != 0) {
        tryStart = true;
    } else {
        bool checkGround = false;
        if ((ec8 & 0x400u) != 0 || (ec8 & 0x800u) != 0) {
            // In the ledge state: kept while the wall is free, both ledges above +0xbbc and found, and the manager byte
            // clear; then as below.
            if (wall != 2 && !(height1 + dH <= m_unkbbc) && !(height2 + dH <= m_unkbbc) && first && second &&
                managerByte == 0) {
                checkGround = true;
            }
        } else {
            checkGround = true;
        }
        if (checkGround) {
            const ICollisionMesh* ground = static_cast<const ICollisionMesh*>(contact.m_pGround);
            if (ground == nullptr || (ground->m_ui16PropertiesFlags & 0x4000u) == 0) tryStart = true;
        }
        if (!tryStart) {
            ClearLedgeFlags(m_unkec4, m_unkec8, m_unk354, false);
            return;
        }
    }
    // The start of the ledge state.
    if ((m_unk35c & 0x10000u) != 0 && (m_unk354 & 1u) != 0 && (ec8 & 0x400u) == 0) {
        float maxHeight = 0.5f;  // TOC1 +0x225c
        if (IsMovementMode0() != 0) maxHeight = m_unkbac;        // 0x00340178
        if (IsFlyingMovementMode1() != 0) maxHeight = m_unkbc4;  // 0x00340188
        if (first && second && !(groundNormalY <= 0.95f) &&  // TOC1 +0x2298
            !(height1 + dH <= m_unkbbc) && !(height2 + dH <= m_unkbbc) && wall != 2 && !(maxHeight <= height1) &&
            !(m_unk1280 >= m_unkbb0) && !(height1 <= 0.0f)) {
            m_unk11cc = nx;
            m_unk11d4 = nz;
            m_unk11d0 = ny;
            m_unkec8 |= 0x80u;
            m_unk11dc = nx;
            m_unk11e4 = nz;
            m_unk11e0 = ny;
            m_unk354 |= 0x800u;
            m_unkec4 |= 0x200000u | 0x800u | 0x400u | 0x2000u;
            m_unkec8 |= 0x400000u | 0x800000u | 0x400u;
            SetMovementMode(0);  // 0x00340c18
        }
        ec8 = m_unkec8;
    }
    // In the ledge state (+0xec8 bit 10, not climbing up / bit 18).
    if ((ec8 & 0x400u) != 0 && (ec8 & 0x2000u) == 0 && (ec8 & 0x40000u) == 0) {
        m_unk354 |= 0x800u;
        m_unkec4 |= 0x200000u | 0x800u | 0x400u | 0x2000u;
        bool lifted = false;
        if (height1 >= 1.0f && !(height1 + dH <= m_unkbbc) && !(height2 + dH <= m_unkbbc)) {  // TOC1 +0x2270
            m_unk11cc = m_unk11dc;
            m_unk11d0 = m_unk11e0;
            m_unk11d4 = m_unk11e4;
            const float lift = height1 - 1.0f;
            m_unkec8 |= 0x80u | 0x200u | 0x800u;
            m_unk550 = lift + m_unk550;
            lifted = true;
        } else if ((m_unkec8 & 0x800u) != 0 && !(height1 + dH <= m_unkbbc) && !(height2 + dH <= m_unkbbc)) {
            m_unk550 = (height1 - 1.0f) + m_unk550;
            lifted = true;
        }
        if (!lifted) {
            m_unkec8 = (m_unkec8 | 0x1000u) & ~0x200u;
            m_unk354 &= ~0x800u;
            m_unkec4 &= 0xffdfd3ffu;
            m_unkec8 &= ~0x80u;
        }
        ec8 = m_unkec8;
        if ((m_unk358 & 0x100000u) != 0 && (ec8 & 0x1000u) == 0 && (ec8 & 0x2000u) == 0) {
            m_unkec8 = ec8 | 0x40000u | 0x800u;
            ec8 = m_unkec8;
        }
    }
    // The ledge animations 0x59 / 0x29: the climb up (bit 13) or leaving.
    if ((ec8 & 0x800u) == 0 || (ec8 & 0x40000u) != 0 || (ec8 & 0x1000u) != 0 || (ec8 & 0x2000u) != 0) return;
    const int16_t animation = static_cast<int16_t>(m_unk160);
    if (animation != 0x59 && animation != 0x29) return;
    if (m_unk1378 <= m_unkbb8) return;
    const float limit = AsF32(m_unkbb4);
    if (limit <= m_unk1374) {
        if (limit >= m_unk1374) return;
        m_unkec8 |= 0x2000u;
        return;
    }
    ClearLedgeFlags(m_unkec4, m_unkec8, m_unk354, true);
}

// 0x00311950 CKHkS08Hero_ComputeTimedAnimDisplacement_maybe: the root motion of the timed animations, through the curve
// of the animation's marks 13..18 (+0x14e0: Math_EvalRampHoldDecay) times a direction (+0x123c): with +0xec8 bit 1 in
// the states +0x1960 == 0x0c or +0x18d0 == 0x0f the timer +0x122c runs by `dt` and the direction comes from +0x1248 by
// the kind +0x1228 (0..3; 4 leaves it, the old direction is kept in +0x1230); with the animation 0xb9 the timer +0x1ab8
// runs, the hero leaves the ground (SetDirectionLock(1); the first time +0xec4 bit 27 and +0x1b18 = 0) and the
// direction is the node's up row. The zero vector otherwise or after the curve's end.
CVector3 CKHkS08Hero::ComputeTimedAnimDisplacement(float dt) {
    CVector3 out = kHeroZeroVector;  // TOC1 +0x2244
    float scale = 0.0f;
    float* const params = m_unk14e0;
    int32_t running;
    if ((m_unkec8 & 2u) != 0 && (m_unk1960 == 0x0c || m_unk18d0 == 0x0f)) {
        m_unk122c = dt + m_unk122c;
        m_unk1230 = m_unk123c;
        m_unk1234 = m_unk1240;
        m_unk1238 = m_unk1244;
        GetAnimParams13to18(params, -1);  // 0x00303a78
        const uint8_t kind = m_unk1228;
        if (kind <= 3) {
            m_unk123c = m_unk1248;
            m_unk1240 = m_unk124c;
            m_unk1244 = m_unk1250;
        } else if (kind == 4) {
            out = kHeroZeroVector;
        }
        running = Math_EvalRampHoldDecay(&scale, m_unk122c, params);  // 0x00583a68
    } else {
        if (m_unk160 != 0xb9) return kHeroZeroVector;
        if ((m_unkec4 & 0x8000000u) == 0) {
            m_unk1b18 = 0.0f;
            m_unkec4 |= 0x8000000u;
        }
        SetF32(m_unk1ab8, AsF32(m_unk1ab8) + dt);
        SetDirectionLock(1);  // 0x00354cf0 and +0x354 bit 0 set, bit 2 cleared
        GetAnimParams13to18(params, -1);  // 0x00303a78
        const RwFrame* frame = static_cast<const CSGMovable*>(m_pKGLObject)->m_pRwFrame;
        m_unk123c = frame->modelling.up.x;
        m_unk1240 = frame->modelling.up.y;
        m_unk1244 = frame->modelling.up.z;
        running = Math_EvalRampHoldDecay(&scale, AsF32(m_unk1ab8), params);  // 0x00583a68
    }
    if ((running & 0xff) == 0) return kHeroZeroVector;
    const float x = scale * m_unk123c;
    const float z = scale * m_unk1244;
    const float y = scale * m_unk1240;
    m_unk123c = x;
    m_unk1244 = z;
    m_unk1240 = y;
    out = {x, y, z};
    return out;
}

// 0x00311c50 CKHkS08Hero_ClampDragToStopVelocity_maybe: the drag, unless it would turn the velocity back (moving at 0.1
// or more, and the velocity after a step of the drag pointing against the velocity): then the velocity (+0x127c) and
// the drag are zeroed.
CVector3 CKHkS08Hero::ClampDragToStopVelocity(float dt, const CVector3* drag, const CVector3* velocity) {
    const float speed = std::sqrt(ppc::fmadds(velocity->z, velocity->z,
                                              ppc::fmadds(velocity->x, velocity->x, velocity->y * velocity->y)));  // Math_Sqrtf
    if (!(speed >= 0.1f)) return *drag;  // TOC1 +0x22a8
    float vx = velocity->x;
    float vy = velocity->y;
    float vz = velocity->z;
    const float dx = drag->x;
    const float dy = drag->y;
    const float dz = drag->z;
    const float length = std::sqrt(ppc::fmadds(vz, vz, ppc::fmadds(vx, vx, vy * vy)));  // Math_Sqrtf
    const float nextY = ppc::fmadds(dt, dy, vy);
    const float nextX = ppc::fmadds(dt, dx, vx);
    const float nextZ = ppc::fmadds(dt, dz, vz);
    if (length != 0.0f) {  // TOC1 +0x2248
        const float inverse = 1.0f / length;  // TOC1 +0x2270
        vy = vy * inverse;
        vx = vx * inverse;
        vz = vz * inverse;
    }
    const float dot = ppc::fmadds(nextZ, vz, ppc::fmadds(nextX, vx, nextY * vy));
    if (dot >= 0.0f) return *drag;
    m_unk127c = kHeroZeroVector.x;
    m_unk1284 = kHeroZeroVector.z;
    m_unk1280 = kHeroZeroVector.y;
    return kHeroZeroVector;
}

// 0x00311df0 CKHkS08Hero_ComputeCameraRelativeMove_maybe: the frame's movement terms from the stick, the camera and the
// node: +0x119c the stick through the camera's axes into the node's frame (unit), +0x11a8 the move input (the stick, or
// the move direction +0x37c when +0x1744; on a climb zone facing the camera the frame stick), +0x11b4 the stick,
// +0x11c0, +0x12f0 (the ground more than 0.01 below), the facing +0x12a0 / +0x135c (flat, unit) and side +0x1368 (flat,
// unit), the turn +0x1374 (move direction . facing), the stick magnitude +0x1378 (/ 255), +0x12d4, the horizontal
// speed and direction +0x12c4 / +0x1294, |vy| +0x12c8, the speed +0x12cc, the run direction +0x1288 (the velocity's
// direction across the ground normal, or +y in the air), the speed along it +0x12d0 and that velocity +0x12ac, the
// side turn +0x13b4 (or +0x13b8 = 1.5 flying with +0x13d1), and +0x12b8 the move direction in the node's frame.
void CKHkS08Hero::ComputeCameraRelativeMove() {
    const CVector3& zero = kHeroZeroVector;  // TOC +0x2244
    const CKSrvCamera* camera = static_cast<const CKSrvCamera*>(g_pEngine->m_srvCamera);
    // The stick (x, z, 0) on the camera's x / y axes. The result is overwritten below before any read.
    m_unk119c = zero.x;
    m_unk11a4 = zero.z;
    m_unk11a0 = zero.y;
    m_unk119c = m_unk370;
    m_unk11a0 = m_unk378;
    {
        const CVector3& ax = camera->m_v3RealAxisX;  // +0x5b0
        const CVector3& ay = camera->m_v3RealAxisY;  // +0x5bc
        const float sx = m_unk119c;
        const float sy = m_unk11a0;
        const float sz = zero.z;
        const float dotY = ppc::fmadds(ay.z, sz, ppc::fmadds(ay.x, sx, ay.y * sy));
        const float dotX = ppc::fmadds(ax.z, sz, ppc::fmadds(ax.x, sx, ax.y * sy));
        const float z = ppc::fmadds(ay.z, dotY, zero.z);
        const float x = ppc::fmadds(ay.x, dotY, zero.x);
        const float y = ppc::fmadds(ay.y, dotY, zero.y);
        m_unk11a4 = ppc::fmadds(ax.z, dotX, z);
        m_unk119c = ppc::fmadds(ax.x, dotX, x);
        m_unk11a0 = ppc::fmadds(ax.y, dotX, y);
    }
    // The stick on the camera's axes again, normalised: (cx, cy, cz).
    const CVector3& ax = camera->m_v3RealAxisX;
    const CVector3& ay = camera->m_v3RealAxisY;
    float cy = ppc::fmadds(ay.y, m_unk378, ppc::fmadds(ax.y, m_unk370, zero.y));
    float cx = ppc::fmadds(ay.x, m_unk378, ppc::fmadds(ax.x, m_unk370, zero.x));
    float cz = ppc::fmadds(ay.z, m_unk378, ppc::fmadds(ax.z, m_unk370, zero.z));
    float length = std::sqrt(ppc::fmadds(cz, cz, ppc::fmadds(cx, cx, cy * cy)));  // Math_Sqrtf 0x10690
    if (length != 0.0f) {
        const float inverse = 1.0f / length;  // TOC +0x2270
        cz = cz * inverse;
        cx = cx * inverse;
        cy = cy * inverse;
    }
    // Into the node's frame (its at and right rows), normalised.
    m_unk119c = zero.x;
    m_unk11a0 = zero.y;
    m_unk11a4 = zero.z;
    {
        const RwFrame* frame = static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame;
        const RwV3d& at = frame->modelling.at;
        const RwV3d& right = frame->modelling.right;
        const float dotAt = ppc::fmadds(at.z, cz, ppc::fmadds(at.x, cx, at.y * cy));
        const float dotRight = ppc::fmadds(right.z, cz, ppc::fmadds(right.x, cx, right.y * cy));
        const float y = ppc::fmadds(right.y, dotRight, ppc::fmadds(at.y, dotAt, zero.y));
        const float x = ppc::fmadds(right.x, dotRight, ppc::fmadds(at.x, dotAt, zero.x));
        const float z = ppc::fmadds(right.z, dotRight, ppc::fmadds(at.z, dotAt, zero.z));
        m_unk11a0 = y;
        m_unk119c = x;
        m_unk11a4 = z;
        length = std::sqrt(ppc::fmadds(z, z, ppc::fmadds(x, x, y * y)));
        if (length != 0.0f) {
            const float inverse = 1.0f / length;
            m_unk11a4 = inverse * m_unk11a4;
            m_unk119c = inverse * m_unk119c;
            m_unk11a0 = inverse * m_unk11a0;
        }
    }
    if (m_unk1744 == 0) {
        m_unk11a8 = m_unk370;
        m_unk11ac = m_unk374;
        m_unk11b0 = m_unk378;
    } else {
        m_unk11a8 = m_unk37c;
        m_unk11ac = m_unk380;
        m_unk11b0 = m_unk384;
    }
    m_unk11b4 = m_unk370;
    m_unk11bc = m_unk378;
    m_unk11b8 = m_unk374;
    CVector3 view;
    CKSrvCamera_GetViewDirection(&view);  // 0x00582f28
    view.y = 0.0f;  // TOC +0x2248
    length = std::sqrt(ppc::fmadds(view.z, view.z, ppc::fmadds(view.x, view.x, 0.0f)));
    if (length != 0.0f) {
        const float inverse = 1.0f / length;
        view.z = view.z * inverse;
        view.x = view.x * inverse;
        view.y = view.y * inverse;
    }
    m_unk11c0 = 1;
    if (m_unk1744 != 0) {
        m_unk11a8 = m_unk37c;
        m_unk11b0 = m_unk384;
        m_unk11ac = m_unk380;
    } else if (m_unk1694 == 0) {
        m_unk11b0 = m_unk11a4;
        m_unk11a8 = m_unk119c;
        m_unk11ac = m_unk11a0;
    } else {
        // On a climb zone: the zone's facing (its node's LTM at axis, flat and unit) against the view; a view across the
        // wall (|dot| < 0.707, TOC +0x22ac) clears +0x11c0 and keeps the previous move (+0x11a8).
        const CVector3& at = m_unk1694->NodeLtm().m_at;
        float ax = at.x;
        float az = at.z;
        float ay = 0.0f;  // TOC +0x2248
        const float flat = std::sqrt(ppc::fmadds(az, az, ppc::fmadds(ax, ax, 0.0f)));
        if (flat != 0.0f) {
            const float inverse = 1.0f / flat;  // TOC +0x2270
            az = az * inverse;
            ax = ax * inverse;
            ay = inverse * 0.0f;
        }
        const float facing = std::fabs(ppc::fmadds(az, view.z, ppc::fmadds(ax, view.x, ay * view.y)));  // the sign bit cleared
        if (facing < 0.707f) {  // TOC +0x22ac
            m_unk11c0 = 0;
        } else {
            m_unk11b0 = m_unk11a4;
            m_unk11a8 = m_unk119c;
            m_unk11ac = m_unk11a0;
        }
    }
    m_unk12f0 = m_gcCurDatasInOut.m_fdH <= 0.01f ? 0 : 1;  // +0x4dc; TOC +0x22b0 (ble: a NaN sets it)
    {
        const RwFrame* frame = static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame;
        const RwV3d& at = frame->modelling.at;
        m_unk135c = at.x;
        m_unk12a0 = at.x;
        m_unk12a4 = at.y;
        m_unk1360 = at.y;
        m_unk1360 = 0.0f;
        m_unk12a8 = at.z;
        m_unk1364 = at.z;
        length = std::sqrt(ppc::fmadds(at.z, at.z, ppc::fmadds(at.x, at.x, m_unk1360 * m_unk1360)));
        if (length != 0.0f) {
            const float inverse = 1.0f / length;
            m_unk1364 = inverse * m_unk1364;
            m_unk135c = inverse * m_unk135c;
            m_unk1360 = inverse * m_unk1360;
        }
        const RwV3d& right = static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame->modelling.right;
        m_unk1368 = right.x;
        m_unk136c = right.y;
        m_unk136c = 0.0f;
        m_unk1370 = right.z;
        length = std::sqrt(ppc::fmadds(right.z, right.z, ppc::fmadds(right.x, right.x, m_unk136c * m_unk136c)));
        if (length != 0.0f) {
            const float inverse = 1.0f / length;
            m_unk1370 = inverse * m_unk1370;
            m_unk1368 = inverse * m_unk1368;
            m_unk136c = inverse * m_unk136c;
        }
    }
    m_unk1374 = ppc::fmadds(m_unk1364, m_unk384, ppc::fmadds(m_unk135c, m_unk37c, m_unk1360 * m_unk380));
    m_unk1378 = static_cast<float>(m_unk394) * 0.0039215688593685627f;  // TOC +0x22b4 (0x3b808081)
    // BUG(original): +0x12ac..+0x12b4 are last frame's values; nothing writes them before the first call (0 on the
    // PS3's fresh heap, 0xcd natively; gate rule).
    m_unk12d4 = ppc::fmadds(m_unk12a8, m_unk12b4, ppc::fmadds(m_unk12a0, m_unk12ac, m_unk12a4 * m_unk12b0));
    // The velocity (+0x127c): horizontal speed and direction, |vy|, speed, direction.
    {
        float hx = m_unk127c;
        float hz = m_unk1284;
        float hy = 0.0f;
        float speed = std::sqrt(ppc::fmadds(hz, hz, ppc::fmadds(hx, hx, 0.0f)));
        float stored = 0.0f;
        if (speed != 0.0f) {
            const float inverse = 1.0f / speed;
            hz = hz * inverse;
            hx = hx * inverse;
            hy = inverse * 0.0f;
            stored = speed;
        }
        m_unk12c4 = stored;
        m_unk1294 = hx;
        m_unk1298 = hy;
        m_unk129c = hz;
        m_unk12c8 = std::fabs(m_unk1280);  // the sign bit cleared through memory
        m_unk12cc = std::fabs(std::sqrt(
            ppc::fmadds(m_unk1284, m_unk1284, ppc::fmadds(m_unk127c, m_unk127c, m_unk1280 * m_unk1280))));
    }
    float vy = m_unk1280;
    float vx = m_unk127c;
    float vz = m_unk1284;
    length = std::sqrt(ppc::fmadds(vz, vz, ppc::fmadds(vx, vx, vy * vy)));
    if (length != 0.0f) {
        const float inverse = 1.0f / length;
        vz = vz * inverse;
        vx = vx * inverse;
        vy = vy * inverse;
    }
    float nx, ny, nz;
    if (m_unk12f0 != 0) {
        nz = kHeroAxisY.z;  // TOC +0x224c
        nx = kHeroAxisY.x;
        ny = kHeroAxisY.y;
    } else {
        nx = m_unk564;
        nz = m_unk56c;
        ny = m_unk568;
    }
    // The run direction: the velocity's direction less its part along the normal (zero when they are parallel).
    {
        const float c0 = ppc::fmsubs(nz, vx, nx * vz);
        const float c1 = ppc::fmsubs(ny, vz, nz * vy);
        const float c2 = ppc::fmsubs(nx, vy, ny * vx);
        const float cross = std::sqrt(ppc::fmadds(c2, c2, ppc::fmadds(c1, c1, c0 * c0)));
        if (cross == 0.0f) {
            vx = zero.x;
            vy = zero.y;
            vz = zero.z;
        }
        const float minusDot = ppc::fnmadds(nz, vz, ppc::fmadds(nx, vx, ny * vy));
        float ry = ppc::fmadds(ny, minusDot, vy);
        float rx = ppc::fmadds(nx, minusDot, vx);
        float rz = ppc::fmadds(nz, minusDot, vz);
        m_unk1288 = rx;
        m_unk128c = ry;
        m_unk1290 = rz;
        length = std::sqrt(ppc::fmadds(rz, rz, ppc::fmadds(rx, rx, ry * ry)));
        if (length != 0.0f) {
            const float inverse = 1.0f / length;
            m_unk1290 = inverse * m_unk1290;
            m_unk1288 = inverse * m_unk1288;
            m_unk128c = inverse * m_unk128c;
        }
        rx = m_unk1288;
        ry = m_unk128c;
        rz = m_unk1290;
        m_unk12d0 = std::fabs(ppc::fmadds(m_unk1284, rz, ppc::fmadds(m_unk127c, rx, m_unk1280 * ry)));
        m_unk12ac = zero.x;
        m_unk12b0 = zero.y;
        m_unk12b4 = zero.z;
        const float along = m_unk12d0;
        m_unk12b4 = ppc::fmadds(along, m_unk1290, zero.z);
        m_unk12ac = ppc::fmadds(along, m_unk1288, zero.x);
        m_unk12b0 = ppc::fmadds(along, m_unk128c, zero.y);
    }
    if (m_unk13d1 != 0 && IsFlyingMovementMode1() != 0) {  // 0x00340188
        m_unk13b4.y = 1.5f;  // +0x13b8; TOC +0x2268
    } else {
        const float side = ppc::fmadds(m_unk1370, m_unk384, ppc::fmadds(m_unk1368, m_unk37c, m_unk136c * m_unk380));
        if (m_unk1374 < 0.0f) {
            m_unk13b4.x = side < 0.0f ? -1.0f : 1.0f;  // TOC +0x2254 / +0x2270
        } else {
            float turn = side * m_unk12f8;
            if (turn <= -1.0f) {
                turn = -1.0f;
            } else if (turn >= 1.0f) {
                turn = 1.0f;
            }
            m_unk13b4.x = turn;
        }
    }
    // The move direction in the node's frame (its at and right rows).
    m_unk12b8 = zero.x;
    m_unk12bc = zero.y;
    m_unk12c0 = zero.z;
    {
        const RwFrame* frame = static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame;
        const RwV3d& at = frame->modelling.at;
        const RwV3d& right = frame->modelling.right;
        const float dotAt = ppc::fmadds(m_unk384, at.z, ppc::fmadds(m_unk37c, at.x, m_unk380 * at.y));
        const float dotRight = ppc::fmadds(m_unk384, right.z, ppc::fmadds(m_unk37c, right.x, m_unk380 * right.y));
        const float z = ppc::fmadds(dotAt, at.z, zero.z);
        const float x = ppc::fmadds(dotAt, at.x, zero.x);
        const float y = ppc::fmadds(dotAt, at.y, zero.y);
        m_unk12c0 = ppc::fmadds(dotRight, right.z, z);
        m_unk12b8 = ppc::fmadds(dotRight, right.x, x);
        m_unk12bc = ppc::fmadds(dotRight, right.y, y);
    }
}

// 0x003101e8 CKHkS08Hero_UpdateField794ByAnimAndElementLevel_maybe: unless climbing, the hero's +0x794 / +0x218 from
// its animation (0.4 for the animations 0x26..0x2a, 0x4c..0x51 and 0x56..0x5a, 1.25 / 1.5 / 1.0 by Spyro's element level
// for 0xe2, +0x1724 for the others); a change clears the position adjustment's x and z (+0x1268 / +0x1270).
void CKHkS08Hero::UpdateField794ByAnimAndElementLevel() {
    if (IsClimbingMovementMode2() != 0) return;  // 0x003401a0
    const int16_t animation = static_cast<int16_t>(m_unk160);
    const float before = m_unk794;
    float value;
    if (animation > 0x51) {
        if (animation < 0x56) {
            value = m_unk1724;
            m_unk794 = value;
            m_unk218 = value;
        } else if (animation <= 0x5a) {
            m_unk218 = 0.4f;  // TOC +0x2264
            value = m_unk1724;
            m_unk794 = value;
        } else if (animation == 0xe2 && m_ui8Hero == 0) {
            // STUB(C2.7: elements): GetElementLevel 0x4f9558 of the game manager for element +0x1cc7: 3 -> 1.5, 2 -> 1.25,
            // else 1.0. Animation 0xe2 is not played before the first fight.
            DOTD_STUB_ONCE("CKHkS08Hero_UpdateField794ByAnimAndElementLevel_maybe: element level (C2.7)");
            value = 1.0f;  // TOC +0x2270
            m_unk794 = value;
            m_unk218 = value;
        } else {
            value = m_unk1724;
            m_unk794 = value;
            m_unk218 = value;
        }
    } else if (animation >= 0x4c || static_cast<uint32_t>(animation - 0x26) <= 4u) {
        m_unk218 = 0.4f;  // TOC +0x2264
        value = m_unk1724;
        m_unk794 = value;
    } else {
        value = m_unk1724;
        m_unk794 = value;
        m_unk218 = value;
    }
    if (value == before) return;
    m_unk1270 = 0.0f;
    m_unk1268 = 0.0f;
}

// 0x0030fd50 CKHkS08Hero_ComputeBlendedVelocityFromFlagsEC8_maybe: with +0xec8 bit 13 or 18, `base` moved by `scale`
// along the node's facing (its modelling at row; bit 18: the vector +0x11dc instead) and `lift` up; else the zero vector.
CVector3 CKHkS08Hero::ComputeBlendedVelocityFromFlagsEC8(const CVector3* base, float scale, float lift) const {
    CVector3 out = kHeroZeroVector;  // TOC1 +0x2244
    if ((m_unkec8 & 0x2000u) == 0 && (m_unkec8 & 0x40000u) == 0) return out;
    out = *base;
    float vx, vy, vz;
    if ((m_unkec8 & 0x40000u) == 0) {
        const RwFrame* frame = static_cast<const CSGMovable*>(m_pKGLObject)->m_pRwFrame;
        vz = frame->modelling.at.z;
        vx = frame->modelling.at.x;
        vy = frame->modelling.at.y;
    } else {
        vx = m_unk11dc;
        vz = m_unk11e4;
        vy = m_unk11e0;
    }
    const float y = ppc::fmadds(scale, vy, out.y);
    out.x = ppc::fmadds(vx, scale, out.x);
    out.z = ppc::fmadds(vz, scale, out.z);
    out.y = y + lift;
    return out;
}
