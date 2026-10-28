// Reconstructed original translation unit: 0x31d3d8-0x326448 (GAME_TOC1, main_toc1), 45 functions, 30 live.
// Primary class: CKHkS08Hero  key 0x25c2  category Hook  size 0x1e00  vtable 0xb22c98
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x31d3d8  FUN_0031d3d8  [dead]
//   [ ] 0x31d518  FUN_0031d518  [dead]
//   [ ] 0x31d570  KStub_ReturnFloat0_31d570  [dead]
//   [ ] 0x31d578  FUN_0031d578  [dead]
//   [ ] 0x31d5b8  FUN_0031d5b8  [dead]
//   [ ] 0x31d640  FUN_0031d640  [dead]
//   [ ] 0x31d6f8  FUN_0031d6f8  [dead]
//   [ ] 0x31d780  FUN_0031d780  [dead]
//   [ ] 0x31d808  FUN_0031d808  [dead]
//   [x] 0x31d880  CKHkS08Hero_GetClimbFlag1627Or1626And1628_maybe
//   [x] 0x31d8b8  CKHkS08Hero_BlendOrientationFromClimbSnapshot_maybe
//   [x] 0x31db40  CKHkS08Hero_TryClimbLeap_maybe
//   [x] 0x31df00  CKHkS08Hero_StickToCurrentClimbZone_maybe
//   [ ] 0x31e0f8  CKHkS08Hero_SetNodeBasisFromUp_maybe  [dead]
//   [x] 0x31e1e8  CKHkS08Hero_LocoState1_ClimbSustained_maybe_Condition
//   [x] 0x31e210  CKHkS08Hero_ComputeClimbMountOffset16BC_maybe
//   [x] 0x31e480  CKHkS08Hero_ComputeClimbMountOffset16B0_maybe
//   [x] 0x31e6f0  CKHkS08Hero_ApplyClimbMountAnimOffset_maybe
//   [ ] 0x31e828  FUN_0031e828  [dead]
//   [x] 0x31ea00  CKHkS08Hero_UpdateClimbZoneAttachment_maybe
//   [x] 0x31ece8  CKHkS08Hero_ComputeClimbDetachForce_maybe
//   [ ] 0x31ee60  FUN_0031ee60  [dead]
//   [x] 0x31ef70  CKHkS08Hero_ComputeClimbMoveVectorByMode_maybe
//   [x] 0x31f2a0  CKHkS08Hero_LocoState2_Climb_maybe_Condition
//   [ ] 0x31f2c8  StaticInitAndDestruction_31f2c8
//   [ ] 0x31f2f8  _GLOBAL__D_31f2f8
//   [ ] 0x31f308  _GLOBAL__I_31f308
//   [x] 0x31f318  CKHkS08Hero_LocoState2_Climb_maybe
//   [ ] 0x31f5c8  FUN_0031f5c8  [dead]
//   [x] 0x31f6a8  CKHkS08Hero_UpdateClimbMovement_maybe
//   [x] 0x31fb68  CKHkS08Hero_TryAttachToClimbZoneList16BC_maybe
//   [x] 0x31fd78  CKHkS08Hero_TryAttachToClimbZoneList16B0_maybe
//   [x] 0x31ff88  CKHkS08Hero_UpdateClimbSustainedMovement_maybe
//   [x] 0x321080  CKHkS08Hero_ClassifyClimbZoneApproach_maybe
//   [x] 0x321438  CKHkS08Hero_IntegrateClimbVelocity_maybe
//   [x] 0x321948  CKHkS08Hero_UpdateClimbDisplacement_maybe
//   [x] 0x322518  CKHkS08Hero_DynamicStage1Climb_maybe
//   [x] 0x3229f8  CKHkS08Hero_AccumulateClimbDetachDisplacement_maybe
//   [x] 0x322d40  CKHkS08Hero_DynamicStage1ClimbDetach_maybe
//   [ ] 0x323288  FUN_00323288  [dead]
//   [ ] 0x323a10  FUN_00323a10  [dead]
//   [x] 0x324190  CKHkS08Hero_UpdateClimbMountState_maybe
//   [x] 0x324780  CKHkS08Hero_LocoState1_ClimbSustained_maybe
//   [x] 0x325108  CKHkS08Hero_UpdateClimbSustainedLocomotion_maybe
//   [x] 0x325c88  CKHkS08Hero_UpdateClimbLocomotion_maybe

#include "Spyro2008/hooks/CKHkS08Hero.h"

#include <cmath>
#include <cstring>

#include "Spyro2008/groups/CKGrpS08Hero.h"
#include "k2000/animation/AnimBlendSlot.h"
#include "k2000/core/Stub.h"
#include "k2000/graphical/CKAnmKeyFrameController.h"
#include "k2000/graphical/animation/CKBlenderController.h"
#include "k2000/hooks/CKHkClimbZone.h"
#include "k2000/math/Quat.h"
#include "k2000/math/Vec3.h"
#include "k2000/misc/FloatApproach.h"
#include "k2000/misc/Mat4.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/system/IKTime.h"
#include "Renderware/rwcore/RwCamera.h"
#include "crt/ppc_ops.h"
#include "crt/xatan.h"
#include "crt/xsinf.h"
#include "k2000/math/Math.h"
#include "k2000/misc/Engine.h"
#include "k2000/services/CKSrvCollision.h"
#include "Renderware/rtanim/RtAnim.h"
#include "Renderware/rwcore/RwMatrix.h"

// ---- step 6 CLIMB: the hero's climbing (shared helpers are local copies, as the other hero units keep theirs). ----
namespace {

// 0x00c50d64 (TOC1 +0x24ec): the zero vector.
constexpr CVector3 kZero{0.0f, 0.0f, 0.0f};

RwFrame* NodeFrame(const CKHkS08Hero* hero) { return static_cast<const CSGMovable*>(hero->m_pKGLObject)->m_pRwFrame; }
CMatrix34& Modelling(const CKHkS08Hero* hero) { return *reinterpret_cast<CMatrix34*>(&NodeFrame(hero)->modelling); }

// 0x002d51e0 CKGrpS08Hero_ClearFollowTrail_maybe (local copy): the group's +0xa88 = 0.
void ClearFollowTrail(IKSerializable* group) { static_cast<CKGrpS08Hero*>(group)->m_unka88 = 0; }
// 0x002ce518 CKGrpS08Hero_GetMaxPartnerDistance_maybe (local copy): the group's +0x108.
float GetMaxPartnerDistance(IKSerializable* group) { return static_cast<CKGrpS08Hero*>(group)->m_unk108; }

// 0x003013c8 CKHkS08Hero_IsAnimFinished (local copy): +0x354 bit 15 while the animation is `animation`.
uint8_t IsAnimFinished(const CKHkS08Hero* hero, uint16_t animation) {
    if (hero->m_unk160 != animation) return 0;
    return static_cast<uint8_t>((hero->m_unk354 >> 15) & 1u);
}
// The inner blender's active key-frame controller (vt+0x194 GetAnimBlendSlot, the slot's controller +4, its +0x50 array
// at the slot's +0x10): the time (+0x50) is CKHkS08Hero_GetCurrentAnimTime 0x303368's answer.
CKAnmKeyFrameController* ActiveController(CKHkS08Hero* hero) {
    AnimBlendSlot* slot = hero->GetAnimBlendSlot();
    CKBlenderController* blender = static_cast<CKBlenderController*>(slot->m_pController);
    return static_cast<CKAnmKeyFrameController*>(blender->m_apControllers[slot->m_unk10]);
}

// 0x0030fae0 Vec3_AddTwoScaled_maybe (local copy): base + a * u + b * v.
CVector3 AddTwoScaled(float a, float b, const CVector3* base, const CVector3* u, const CVector3* v) {
    CVector3 out = *base;
    out.z = ppc::fmadds(a, u->z, out.z);
    out.x = ppc::fmadds(u->x, a, out.x);
    out.y = ppc::fmadds(u->y, a, out.y);
    out.z = ppc::fmadds(b, v->z, out.z);
    out.x = ppc::fmadds(v->x, b, out.x);
    out.y = ppc::fmadds(v->y, b, out.y);
    return out;
}

// 0x003342c0 Vec3_LerpByRangeClamped_maybe (local copy): `a` to `b` as `t` goes from `lo` to `hi` (the middle when the
// range is empty, `b` above it, `a` below it).
CVector3 LerpByRangeClamped(float lo, float hi, float t, const CVector3* a, const CVector3* b) {
    if (hi == lo) {
        const float half = 0.5f;  // TOC1 +0x2810
        return {((kZero.x + b->x) + a->x) * half, ((kZero.y + b->y) + a->y) * half, ((kZero.z + b->z) + a->z) * half};
    }
    if (hi >= t && lo <= t) {
        const float f = (t - lo) / (hi - lo);
        return {ppc::fmadds(f, b->x - a->x, a->x), ppc::fmadds(f, b->y - a->y, a->y), ppc::fmadds(f, b->z - a->z, a->z)};
    }
    if (hi < t) return *b;
    if (lo <= t) return kZero;  // only unordered (NaN) compares get here
    return *a;
}

// 0x00582bc8 Math_SmoothStep_maybe (local copy, through TocBridge 0x98f350): 3t^2 - 2t^3 inside (0, 1), else t.
float SmoothStep(float t) {
    if (!(t < 1.0f)) return t;
    if (!(t > 0.0f)) return t;
    const float t2 = t * t;
    const float t3 = t * t2;
    return ppc::fmadds(t3, -2.0f, t2 * 3.0f);
}

// 0x00241d78 Quat_ToMatrixNormalizing_maybe (local copy): the rotation of the (not necessarily unit) quaternion, the
// position zeroed, flags 3.
void QuatToMatrixNormalizing(const float* q, CMatrix34* m) {
    const float y = q[1];
    const float x = q[0];
    const float z = q[2];
    const float w = q[3];
    m->m_pos.z = 0.0f;
    m->m_ui32Flags = 3;
    m->m_pos.x = 0.0f;
    m->m_pos.y = 0.0f;
    float n = y * y;
    n = ppc::fmadds(x, x, n);
    n = ppc::fmadds(z, z, n);
    n = ppc::fmadds(w, w, n);
    const float s = 2.0f / n;
    const float zs = z * s;
    const float xs = x * s;
    const float ys = y * s;
    const float zz = z * zs;
    const float xx = x * xs;
    const float yy = y * ys;
    const float xz = z * xs;
    const float yz = y * zs;
    const float wx = w * xs;
    const float wz = w * zs;
    const float xy = x * ys;
    const float wy = w * ys;
    m->m_at.y = yz - wx;     // +0x24
    m->m_up.z = wx + yz;     // +0x18
    m->m_up.x = xy - wz;     // +0x10
    m->m_at.x = wy + xz;     // +0x20
    m->m_right.y = wz + xy;  // +0x04
    m->m_right.z = xz - wy;  // +0x08
    m->m_up.y = 1.0f - (xx + zz);
    m->m_at.z = 1.0f - (xx + yy);
    m->m_right.x = 1.0f - (yy + zz);
}

}  // namespace

// 0x0031e1e8 CKHkS08Hero_LocoState1_ClimbSustained_maybe_Condition: ShouldStayClimbing.
uint8_t CKHkS08Hero::LocoClimbSustainedCondition(IKTime*, uint8_t) { return ShouldStayClimbing(); }

// 0x0031f2a0 CKHkS08Hero_LocoState2_Climb_maybe_Condition: climbing (movement mode 2).
uint8_t CKHkS08Hero::LocoClimbCondition(IKTime*, uint8_t) { return IsClimbingMovementMode2(); }

// 0x0031d880 CKHkS08Hero_GetClimbFlag1627Or1626And1628_maybe: 1 when +0x1628 or +0x1626 is set, else +0x1627.
uint8_t CKHkS08Hero::GetClimbFlag1627Or1626And1628() {
    if (m_unk1628 == 0 && m_unk1626 == 0) return m_unk1627;
    return 1;
}

// 0x0031f318 CKHkS08Hero_LocoState2_Climb_maybe: the locomotion state of a climbing hero that no climb holds (mode 2,
// ShouldStayClimbing false: let go). Enter: the yaw (+0x538) from the node's at axis and the move input recomputed
// (+0x1629 cleared). Exit: the climb timers and flags cleared. Update: unless a jump (+0x1625) or a leap holds it, the
// velocity loses its part into the ground (+0x564); then the partner tether.
uint8_t CKHkS08Hero::LocoClimb(IKTime*, int32_t phase, uint8_t other) {
    if (phase == 1) {
        m_unkec4 = (m_unkec4 & 0xfffffffeu) | 1u;
        m_unk1638 = 0;
        m_unk538 = Vec3_GetYawAngleFromX(&Modelling(this).m_at);  // 0x00244638
        if (m_unk1629 != 0) m_unk1629 = 0;
        ComputeCameraRelativeMove();  // 0x00311df0
        m_unk35c &= 0x7fffffffu;
        m_unkec8 &= 0xffffff7fu;
        m_unk16ac = 0;
        return other;
    }
    if (phase == 2) {
        m_unk1638 = 0;
        m_unk162c = 0.0f;
        m_unk1634 = 0.0f;
        m_unk1630 = 0.0f;
        m_unk1628 = 0;
        m_unk1620 = 0;
        m_unkec4 = (m_unkec4 & 0xfffffffeu) | 1u;
        if ((m_unkec4 & 0x20000u) == 0) m_unk35c = (m_unk35c & 0x7fffffffu) | 0x80000000u;
        m_unkec8 &= 0xffffff7fu;
        return other;
    }
    if (phase != 0) return other;
    bool fix;
    if (m_unk1625 != 0) {
        fix = false;
    } else if (m_unk1628 != 0) {
        fix = m_unk1626 != 0;
    } else {
        fix = m_unk1626 != 0 || m_unk1627 == 0;
    }
    if (fix) {
        const float vx = m_unk127c;
        const float vy = m_unk1280;
        const float vz = m_unk1284;
        float dot = vy * m_unk568;
        dot = ppc::fmadds(vx, m_unk564, dot);
        dot = ppc::fmadds(vz, m_unk56c, dot);
        if (dot < 0.0f) {  // TOC1 +0x24f0
            const float push = -dot;
            m_unk1284 = ppc::fmadds(push, m_unk56c, vz);
            m_unk127c = ppc::fmadds(m_unk564, push, vx);
            m_unk1280 = ppc::fmadds(push, m_unk568, vy);
        }
    }
    ApplyPartnerTetherToVelocity();  // 0x003105d8
    return other;
}

// 0x00324780 CKHkS08Hero_LocoState1_ClimbSustained_maybe: the locomotion state of a hero a climb holds.
uint8_t CKHkS08Hero::LocoClimbSustained(IKTime* clock, int32_t phase, uint8_t other) {
    CKGrpS08Hero* group = static_cast<CKGrpS08Hero*>(m_pGrpHero);
    if (phase == 1) {
        m_unk1664 = 9;
        m_unk1626 = 0;
        m_unk1630 = 0.0f;
        m_unkec4 = (m_unkec4 & 0xfffffffeu) | 1u;
        m_unk794 = 0.05f;  // TOC1 +0x2528
        m_unk218 = 0.05f;
        m_unk1675 = static_cast<uint8_t>(phase);
        m_unk1838 = 0;
        if ((m_unkec4 & 0x20000u) == 0) m_unk35c = (m_unk35c & 0x7fffffffu) | 0x80000000u;
        m_unk1628 = 0;
        m_unk1688 = m_unkc48;
        m_unk161f = 0;
        m_unk167b = 0;
        m_unk167e = 0;
        m_unk1680 = 0;
        m_unk1684 = 0;
        m_unk16f9 = 0;
        if (m_ui8Hero == m_ui8TrackedLeader) ClearFollowTrail(group);  // 0x002d51e0
        m_unkec8 &= 0xffffff7fu;
        m_unk127c = kZero.x;
        m_unk1280 = kZero.y;
        m_unk1284 = kZero.z;
        m_unk354 = (m_unk354 & 0xffffffbfu) | 0x40u;
        m_unkecc &= 0xfffbffffu;
        m_unk368 = (m_unk368 & 0xfffff7ffu) | 0x800u;
        m_unk16a8 = nullptr;
        m_unk16a4 = nullptr;
        m_unkec8 = (m_unkec8 & 0xffbfffffu) | 0x400000u;
        m_unkec8 = (m_unkec8 & 0xff7fffffu) | 0x800000u;
        m_unk1758 = 1.0f;  // TOC1 +0x251c
        m_unk175c = 0;
        m_unk1764 = kZero.x;
        m_unk176c = kZero.z;
        m_unk1768 = kZero.y;
        m_unk1774 = 0;
        m_unk1760 = 0;
        m_unk1770 = 0;
        m_unkec4 &= 0x9fffffffu;
        return other;
    }
    if (phase == 2) {
        m_unkec4 = (m_unkec4 & 0xfffffffeu) | 1u;
        m_unk16f9 = 0;
        m_unk1677 = 0;
        m_unk1676 = 0;
        m_unk1678 = 0;
        m_unk1679 = 0;
        if (m_unk1694 != nullptr) {
            m_unk1694->RemoveClimber(CKHkClimbZone::ClimberKey(this));  // 0x00457180
            m_unkecc &= 0xfffbffffu;
        }
        m_unk1694 = nullptr;
        m_unk16a0 = nullptr;
        m_unk1698 = nullptr;
        m_unk169c = nullptr;
        m_unk1690 = nullptr;
        if (m_unk16a4 != nullptr) {
            m_unk16a4->RemoveClimber(CKHkClimbZone::ClimberKey(this));
            m_unk16a4 = nullptr;
        }
        if (m_unk16a8 != nullptr) {
            m_unk16a8->RemoveClimber(CKHkClimbZone::ClimberKey(this));
            m_unk16a8 = nullptr;
        }
        m_unk794 = m_unk1724;
        m_unk16fc = 0;
        m_unk163c = 0.0f;
        m_unk168d = 0;
        m_unk168c = 0;
        m_unk168e = 0;
        m_unk1268 = 0.0f;
        m_unk1270 = 0.0f;
        m_unk1675 = 0;
        m_unk218 = m_unk1724;
        m_unk35c &= 0x7fffffffu;
        if (m_ui8Hero == m_ui8TrackedLeader) ClearFollowTrail(group);
        m_unk1629 = 0;
        m_unkec8 &= 0xffffff7fu;
        m_unk354 &= 0xffffffbfu;
        m_unk35c &= 0xffffff7fu;
        m_unkec4 &= 0xfffeffffu;
        m_unk1628 = 0;
        m_unkecc = (m_unkecc & 0xffbfffffu) | 0x400000u;
        m_unk368 &= 0xfffff7ffu;
        m_unkec8 &= 0xff3fffffu;
        m_unk1758 = 1.0f;
        m_unk175c = 0;
        m_unk1764 = kZero.x;
        m_unk176c = kZero.z;
        m_unk1768 = kZero.y;
        m_unk1774 = 0;
        m_unk1760 = 0;
        m_unk1770 = 0;
        return other;
    }
    if (phase != 0) return other;
    const float dt = clock->m_afDeltaTime[0];
    if ((m_unkec8 & 1u) == 0) {
        UpdateClimbMountState();        // 0x00324190
        UpdateClimbZoneAttachment(dt);  // 0x0031ea00
        if (m_unk1628 == 0) m_unk1690 = m_unk1694;
        m_unk35c &= 0xffffff7fu;
        if (m_unk1690 != nullptr) {
            const uint8_t kind = m_unk1690->m_unk34;
            if (kind == 1) {
                m_unk1744 = 1;
            } else if (kind == 0) {
                m_unk1744 = 2;
                if (m_unk1628 == 0) m_unk35c = (m_unk35c & 0xffffff7fu) | 0x80u;
            } else if (kind == 2) {
                m_unk1744 = 0;
            } else {
                m_unk1744 = 3;
            }
        }
    }
    CKHkClimbZone* zone = m_unk1694;
    float y = m_unk550;
    if (zone != nullptr) {
        const float margin = 0.1f;  // TOC1 +0x2530
        const float top = zone->NodeLtm().m_pos.y + zone->m_fUnk30;
        if (y + margin > top && (zone->m_bitArray & 0x40000u) != 0 && zone->m_pUnk50 != nullptr && m_unk1665 == 0 &&
            m_unk19a8 != 2 && m_unk1744 == 0 && static_cast<int32_t>(m_unkec8) >= 0 && m_unk1628 == 0 && m_unk1626 == 0 &&
            m_unk1627 == 0 && m_unk1678 == 0) {
            m_unkec8 = (m_unkec8 & 0xfffffffeu) | 1u;  // the top of the zone: the ledge
            zone = m_unk1694;
            y = m_unk550;
        }
        if (zone != nullptr && zone->NodeLtm().m_pos.y > y - margin && m_unk1665 == 1 && m_unk19a8 != 2 && m_unk1744 == 0) {
            const float height = GetHeightAboveGround();  // 0x0032a008
            if (m_unkc70 > height && m_unk1679 != 0) m_unkecc = (m_unkecc & 0xffefffffu) | 0x100000u;
        }
    }
    if (m_unk1626 == 0 && static_cast<int32_t>(m_unkec8) >= 0 && (m_unkec8 & 1u) == 0) {
        uint32_t status = m_unkec4;
        if (m_unk1679 != 0 && (status & 0x20000000u) == 0 && (status & 0x40000000u) == 0) {
            bool attached = false;
            uint32_t bit = 0;
            if (m_unk1665 == 2 && m_unk16b8 != 0) {
                attached = TryAttachToClimbZoneList16B0() != 0;  // 0x0031fd78
                bit = 0x20000000u;
            } else if (m_unk1665 == 3 && m_unk16c4 != 0) {
                attached = TryAttachToClimbZoneList16BC() != 0;  // 0x0031fb68
                bit = 0x40000000u;
            }
            if (attached) {
                m_unkec4 = (m_unkec4 & ~bit) | bit;
                m_unk16c8 = m_unk54c;
                m_unk16d0 = m_unk554;
                m_unk16cc = m_unk550;
                m_unk127c = kZero.x;
                m_unk1284 = kZero.z;
                m_unk1280 = kZero.y;
            }
            status = m_unkec4;
        }
        if ((status & 0x20000000u) != 0 || (status & 0x40000000u) != 0) {
            if ((status & 0x20000000u) != 0 && m_unk160 == 0x85) {
                const CVector3 offset = ComputeClimbMountOffset16B0();  // 0x0031e480
                m_unk5c0 = m_unk5c0 + offset.x;
                m_unk5c4 = m_unk5c4 + offset.y;
                m_unk5c8 = m_unk5c8 + offset.z;
                status = m_unkec4;
            }
            if ((status & 0x40000000u) != 0 && m_unk160 == 0x86) {
                const CVector3 offset = ComputeClimbMountOffset16BC();  // 0x0031e210
                m_unk5c0 = m_unk5c0 + offset.x;
                m_unk5c4 = m_unk5c4 + offset.y;
                m_unk5c8 = m_unk5c8 + offset.z;
            }
        }
    }
    if ((m_unk368 & 0x80u) != 0) {
        const float vx = m_unk127c;
        const float vy = m_unk1280;
        const float vz = m_unk1284;
        float dot = m_unk518 * vy;
        dot = ppc::fmadds(vx, m_unk514, dot);
        dot = ppc::fmadds(m_unk51c, vz, dot);
        if (dot < 0.0f) {
            m_unk1284 = vz - m_unk51c * dot;
            m_unk127c = vx - m_unk514 * dot;
            m_unk1280 = vy - m_unk518 * dot;
        }
    }
    if ((m_unk354 & 0x40000u) != 0) {
        // The wall slide's normal (+0x61c), normalised, keeps the velocity from going into the wall.
        float nx = m_wallSlide.m_v3Normal.x;
        float ny = m_wallSlide.m_v3Normal.y;
        float nz = m_wallSlide.m_v3Normal.z;
        const float length = std::sqrt(ppc::fmadds(nz, nz, ppc::fmadds(nx, nx, ny * ny)));  // Math_Sqrtf
        if (length != 0.0f) {
            const float inverse = 1.0f / length;
            nz = nz * inverse;
            nx = nx * inverse;
            ny = ny * inverse;
        }
        const float vx = m_unk127c;
        const float vy = m_unk1280;
        const float vz = m_unk1284;
        const float dot = ppc::fmadds(nz, vz, ppc::fmadds(vx, nx, ny * vy));
        if (dot < 0.0f) {
            const float push = -dot;
            m_unk1284 = ppc::fmadds(push, nz, vz);
            m_unk127c = ppc::fmadds(push, nx, vx);
            m_unk1280 = ppc::fmadds(push, ny, vy);
        }
    }
    if (PartnerShouldStayClimbing() != 0) ApplyPartnerTetherToVelocity();  // 0x002f8628, 0x003105d8
    return other;
}

// 0x00324190 CKHkS08Hero_UpdateClimbMountState_maybe: the mount and the ledge. A mount (+0x1679) without a zone in
// reach ends; on the ledge (+0xec8 bit 31) the climb-over targets (+0x1728 the attach's up, +0x1734 the point above the
// ledge) and the side (+0x1740) are set; a fresh climb (+0x1677) starts the mount blend from the node's matrix (+0x16d4 ->
// +0x16dc) to the attach (+0x16d8 -> +0x16e0, 0.05 out), +0x16f4 its length; the end of the blend (+0x16f8 / +0x16f9)
// records the climber and starts the mount (+0x1679).
void CKHkS08Hero::UpdateClimbMountState() {
    if (m_unk1679 != 0 && m_unk1676 == 0 && m_unk1628 == 0) {
        m_unk1678 = 0;
        m_unk1679 = 0;
    }
    if (static_cast<int32_t>(m_unkec8) < 0) {
        if (m_unk1694 != nullptr) {
            const CMatrix34& attach = *m_unk16d8;
            m_unk1678 = 1;
            m_unk1728 = attach.m_up.x;
            m_unk172c = attach.m_up.y;
            m_unk1730 = attach.m_up.z;
            const CVector3 down{-attach.m_up.x, -attach.m_up.y, -attach.m_up.z};
            const CVector3 out = AddTwoScaled(1.04999995f, 1.0f, &attach.m_pos, &down, &kHeroAxisY);  // TOC1 +0x2598 / +0x251c
            m_unk173c = out.z;
            m_unk1734 = out.x;
            m_unk1738 = out.y;
            m_unk1734 = ppc::fmadds(m_unk1728, 0.05f, out.x);  // TOC1 +0x2528
            m_unk1738 = ppc::fmadds(m_unk172c, 0.05f, out.y);
            m_unk173c = ppc::fmadds(m_unk1730, 0.05f, out.z);
            // Vec3_GetYawAngleFromZ 0x244528 of +0x1728 and of +0x135c: the answers are not used.
            float dot = m_unk172c * m_unk1360;
            dot = ppc::fmadds(m_unk1728, m_unk135c, dot);
            dot = ppc::fmadds(m_unk1730, m_unk1364, dot);
            if (dot <= 0.0f) {
                m_unk1740 = 1;
                m_unk1728 = -m_unk1728;
                m_unk172c = -m_unk172c;
                m_unk1730 = -m_unk1730;
            } else {
                m_unk1740 = 0;
            }
        }
    } else {
        bool tail = true;
        if (m_unk1677 != 0) {
            m_unk1628 = 0;
            m_unk127c = kZero.x;
            m_unk1280 = kZero.y;
            m_unk1284 = kZero.z;
            m_unk163c = 0.0f;
            m_unk1677 = 0;
            m_unk1679 = 0;
            m_unk1684 = 0;
            m_unk1678 = 1;
            *m_unk16dc = *m_unk16d4;
            *m_unk16e0 = *m_unk16d8;
            CMatrix34& target = *m_unk16e0;
            target.m_pos.z = ppc::fmadds(target.m_up.z, 0.05f, target.m_pos.z);
            target.m_pos.x = ppc::fmadds(target.m_up.x, 0.05f, target.m_pos.x);
            target.m_pos.y = ppc::fmadds(target.m_up.y, 0.05f, target.m_pos.y);
            target.m_ui32Flags &= 0xfffdffffu;
            const float dy = m_unk16d4->m_pos.y - m_unk16d8->m_pos.y;
            const float dx = m_unk16d4->m_pos.x - m_unk16d8->m_pos.x;
            const float dz = m_unk16d4->m_pos.z - m_unk16d8->m_pos.z;
            m_unk16f4 = std::sqrt(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));  // Math_Sqrtf
            if (m_unk1694 != nullptr && m_unk1694->GetLinkedObjectFlagC23() != 0) {  // 0x00456bc8
                m_unkec4 = (m_unkec4 & 0xfffeffffu) | 0x10000u;
            } else {
                m_unkec4 &= 0xfffeffffu;
            }
        }
        if (tail) {
            if (m_unk16f8 != 0) m_unk167e = 1;
            if (m_unk16f9 != 0) {
                m_unk16f9 = 0;
                if (m_unk1694 != nullptr) m_unk1694->AddOrUpdateClimber(0.0f, 1, &kZero, 0);  // 0x00458e98
                if (m_unk1678 != 0) {
                    m_unk1679 = 1;
                    m_unk167a = 1;
                } else {
                    m_unk167a = 0;
                }
                m_unk1678 = 0;
                return;
            }
        }
    }
    if (m_unk1678 != 0 && m_unk1744 == 0) {
        SetCameraDirectionLock(1);  // 0x00354cf0
        m_unk354 = ((m_unk354 | 1u) & ~4u);
    }
}

// 0x0031ea00 CKHkS08Hero_UpdateClimbZoneAttachment_maybe: off the ledge, the mount blend: its time +0x1750 (started at
// +0x16f4 / +0xce8, at least 0.1) runs down by dt and the blended matrix (BlendClimbAttachMatrix) gives the attach axes
// (+0x1700 up, +0x170c at) and the position adjustment (+0x5c0); +0x16f8 when the hero did not move. After a mount
// (+0x167a) the target's axes are taken once.
void CKHkS08Hero::UpdateClimbZoneAttachment(float dt) {
    if (static_cast<int32_t>(m_unkec8) < 0) return;
    const float zx = kZero.x, zy = kZero.y, zz = kZero.z;
    if (m_unk1678 == 0) {
        if (m_unk167a == 0) return;
        const CMatrix34& target = *m_unk16e0;
        const float x = zx + m_unk5c0;
        m_unk1700[0] = target.m_up.x;
        m_unk1700[2] = target.m_up.z;
        m_unk1700[1] = target.m_up.y;
        m_unk170c[0] = target.m_at.x;
        m_unk170c[2] = target.m_at.z;
        m_unk170c[1] = target.m_at.y;
        m_unk5c0 = x;
        m_unk5c4 = zy + m_unk5c4;
        m_unk5c8 = zz + m_unk5c8;
        m_unk167a = 0;
        return;
    }
    if (m_unk1750 < 0.0f) {
        float length = m_unk16f4 / m_unkce8;
        if (length <= 0.1f) length = 0.1f;  // TOC1 +0x2530
        m_unk1750 = length;
        m_unk1754 = length;
    } else {
        m_unk1750 = m_unk1750 - dt;
    }
    const CMatrix34 blended = BlendClimbAttachMatrix(m_unk16dc, m_unk16e0);  // 0x002f9bd8
    m_unk1700[0] = blended.m_up.x;
    m_unk170c[0] = blended.m_at.x;
    m_unk1700[1] = blended.m_up.y;
    m_unk1700[2] = blended.m_up.z;
    m_unk170c[1] = blended.m_at.y;
    m_unk170c[2] = blended.m_at.z;
    m_unk5c0 = (blended.m_pos.x - m_unk54c) + m_unk5c0;
    m_unk5c4 = (blended.m_pos.y - m_unk550) + m_unk5c4;
    m_unk5c8 = (blended.m_pos.z - m_unk554) + m_unk5c8;
    m_unk16f8 = (m_unk54c == m_unk558 && m_unk550 == m_unk55c && m_unk554 == m_unk560) ? 1 : 0;
}

// 0x0031e480 CKHkS08Hero_ComputeClimbMountOffset16B0_maybe / 0x0031e210 ..16BC_maybe: during the mount animation (0x85 /
// 0x86) the move from the hero's position to the point between the start (+0x16c8) and the zone's attach point (0.05 out)
// by the animation's time; the attach point itself once the animation is finished.
CVector3 CKHkS08Hero::ComputeClimbMountOffset(CKHkClimbZone* zone, uint16_t animation) {
    CVector3 out = kZero;
    const CVector3 start{m_unk16c8, m_unk16cc, m_unk16d0};
    CVector3 probe = start;
    alignas(16) CMatrix34 matrix;
    zone->GetAttachMatrix(&probe, &matrix, CKHkClimbZone::ClimberKey(this));  // 0x00458a88
    const float s = 0.05f;  // TOC1 +0x2528
    const CVector3 target{ppc::fmadds(matrix.m_up.x, s, matrix.m_pos.x), ppc::fmadds(matrix.m_up.y, s, matrix.m_pos.y),
                          ppc::fmadds(matrix.m_up.z, s, matrix.m_pos.z)};
    const float duration = ActiveController(this)->GetDuration();  // 0x0007ab60
    const float time = ActiveController(this)->m_unk50;
    CVector3 point = LerpByRangeClamped(0.0f, duration, time, &start, &target);  // 0x003342c0
    if (IsAnimFinished(this, animation) != 0) point = target;  // 0x003013c8
    const float x = point.x + out.x;
    const float y = point.y + out.y;
    const float z = point.z + out.z;
    out.x = x - m_unk54c;
    out.z = z - m_unk554;
    out.y = y - m_unk550;
    return out;
}
CVector3 CKHkS08Hero::ComputeClimbMountOffset16B0() { return ComputeClimbMountOffset(m_unk16b0[0], 0x85); }
CVector3 CKHkS08Hero::ComputeClimbMountOffset16BC() { return ComputeClimbMountOffset(m_unk16bc[0], 0x86); }

// 0x0031e6f0 CKHkS08Hero_ApplyClimbMountAnimOffset_maybe: the mount offsets of the two lists added to +0x5c0 (as the
// update of LocoState1_ClimbSustained does inline).
void CKHkS08Hero::ApplyClimbMountAnimOffset() {
    uint32_t status = m_unkec4;
    if ((status & 0x20000000u) == 0) {
        if ((status & 0x40000000u) == 0) return;
    } else if (m_unk160 == 0x85) {
        const CVector3 offset = ComputeClimbMountOffset16B0();
        m_unk5c0 = m_unk5c0 + offset.x;
        m_unk5c4 = m_unk5c4 + offset.y;
        m_unk5c8 = m_unk5c8 + offset.z;
        status = m_unkec4;
    }
    if ((status & 0x40000000u) != 0 && m_unk160 == 0x86) {
        const CVector3 offset = ComputeClimbMountOffset16BC();
        m_unk5c0 = m_unk5c0 + offset.x;
        m_unk5c4 = m_unk5c4 + offset.y;
        m_unk5c8 = m_unk5c8 + offset.z;
    }
}

// 0x0031fd78 CKHkS08Hero_TryAttachToClimbZoneList16B0_maybe / 0x0031fb68 ..16BC_maybe: the zones touched this frame (last
// first): one whose attach point is level with the hero (within 0.2) and, while the partner climbs, within the group's
// partner distance, records the hero (+0x16a4 the zone, +0x16a8 the current one). 1 when one did.
uint8_t CKHkS08Hero::TryAttachToClimbZoneList(CKHkClimbZone** zones, uint32_t count) {
    uint8_t attached = 0;
    while (count != 0) {
        count -= 1;
        CKHkClimbZone* zone = zones[count];
        CVector3 probe{m_unk54c, m_unk550, m_unk554};
        alignas(16) CMatrix34 matrix;
        zone->GetAttachMatrix(&probe, &matrix, CKHkClimbZone::ClimberKey(this));  // 0x00458a88
        CKHkS08Hero* partner = GetPartnerHero();  // 0x002f85f8
        const float dx = matrix.m_pos.x - partner->m_unk54c;
        const float dy = matrix.m_pos.y - partner->m_unk550;
        const float dz = matrix.m_pos.z - partner->m_unk554;
        const float distance = std::sqrt(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));
        if (distance >= GetMaxPartnerDistance(m_pGrpHero) && PartnerShouldStayClimbing() != 0) continue;  // bge
        const float level = std::fabs(matrix.m_pos.y - m_unk550);  // the sign bit cleared in memory
        if (level >= 0.2f) continue;  // TOC1 +0x2520; bge
        attached = 1;
        zone->AddOrUpdateClimber(m_unkd18 + m_unkd18, 1, reinterpret_cast<const CVector3*>(&m_unk54c),
                                 CKHkClimbZone::ClimberKey(this));  // 0x00458e98
        m_unk16a4 = zone;
        m_unk16a8 = m_unk1690;
    }
    return attached;
}
uint8_t CKHkS08Hero::TryAttachToClimbZoneList16B0() { return TryAttachToClimbZoneList(m_unk16b0, m_unk16b8); }
uint8_t CKHkS08Hero::TryAttachToClimbZoneList16BC() { return TryAttachToClimbZoneList(m_unk16bc, m_unk16c4); }

// 0x0031df00 CKHkS08Hero_StickToCurrentClimbZone_maybe: a hero climbing freely on its zone is put on the zone's attach
// point (0.05 out along the node's up) and, unless +0xecc bit 17, the node takes the attach matrix (turned round with
// +0xecc bit 18).
void CKHkS08Hero::StickToCurrentClimbZone() {
    if (m_unk1628 != 0 || m_unk1626 != 0 || m_unk1627 != 0 || (m_unkec8 & 1u) != 0 || (m_unkec4 & 0x20000000u) != 0 ||
        (m_unkec4 & 0x40000000u) != 0 || m_unk1678 != 0 || m_unk1694 == nullptr) {
        return;
    }
    const CVector3 up = Modelling(this).m_up;
    alignas(16) CMatrix34 matrix;
    if (m_unk1694->AttachClimberIfValid(m_unkd18 + m_unkd18, reinterpret_cast<const CVector3*>(&m_unk54c), &matrix,
                                        CKHkClimbZone::ClimberKey(this)) == 0) {  // 0x004591e0
        return;
    }
    const float s = 0.05f;  // TOC1 +0x2528
    const float x = ppc::fmadds(up.x, s, matrix.m_pos.x);
    const float z = ppc::fmadds(up.z, s, matrix.m_pos.z);
    const float y = ppc::fmadds(up.y, s, matrix.m_pos.y);
    m_unk54c = x;
    matrix.m_pos.x = x;
    m_unk554 = z;
    m_unk550 = y;
    matrix.m_pos.z = z;
    matrix.m_pos.y = y;
    const uint32_t flags = matrix.m_ui32Flags & 0xfffdffffu;
    matrix.m_ui32Flags = flags;
    if ((m_unkecc & 0x20000u) != 0) return;
    if ((m_unkecc & 0x40000u) != 0) {
        matrix.m_ui32Flags = flags & 0xfffdfffcu;
        matrix.m_right.x = -matrix.m_right.x;
        matrix.m_right.y = -matrix.m_right.y;
        matrix.m_right.z = -matrix.m_right.z;
        matrix.m_at.x = -matrix.m_at.x;
        matrix.m_at.y = -matrix.m_at.y;
        matrix.m_at.z = -matrix.m_at.z;
    }
    static_cast<CSGMovable*>(m_pKGLObject)->SetLocalMatrix(reinterpret_cast<const RwMatrix*>(&matrix));  // 0x000d0be8
}

// 0x0031f6a8 CKHkS08Hero_UpdateClimbMovement_maybe (the node of a hero no climb holds): the yaw turned towards the move
// (+0x12a0 while a leap or a jump runs, else +0x37c) at +0xc24, the up axis by the tilt springs towards the ground normal
// (+0x564), the node's matrix at the position; free of the climb, the velocity keeps only its forward part.
void CKHkS08Hero::UpdateClimbMovement(float dt) {
    alignas(16) CMatrix34 matrix;
    matrix.m_ui32Flags = 0x20003;
    matrix.m_right = {1.0f, 0.0f, 0.0f};
    matrix.m_up = {0.0f, 1.0f, 0.0f};
    matrix.m_at = {0.0f, 0.0f, 1.0f};
    matrix.m_pos = {m_unk54c, m_unk550, m_unk554};
    matrix.m_ui32Flags &= 0xfffdffffu;
    const float speed = m_unk1378;
    CVector3 direction;
    if (m_unk1628 != 0 || m_unk1626 != 0 || m_unk1627 != 0) {
        direction = {m_unk12a0, m_unk12a4, m_unk12a8};
    } else {
        direction = {m_unk37c, m_unk380, m_unk384};
    }
    // The switch on +0x1664 (0..4, through the table at TOC1 +0x254c) has no case of its own.
    if (speed != 0.0f) {
        float approach[3] = {Vec3_GetYawAngleFromX(&direction), m_unkc24, m_unk538};  // 0x00244638
        FloatApproach_StepAngle(dt, approach);  // 0x00243748
        m_unk538 = approach[2];
    }
    Mat4_RotateLocalYDeg((1.57079637050628662f - m_unk538) * 57.2957801818847656f, &matrix);  // TOC1 +0x2550 / +0x2554
    const CVector3 current = matrix.m_up;
    const CVector3 target{m_unk564, m_unk568, m_unk56c};
    const CVector3 up = UpdateBodyTiltSprings(&current, &target);  // 0x002fbfc0
    Mat4_BuildFromUpAndForward(&matrix, &up, &matrix.m_at);  // 0x0023ff80
    static_cast<CSGMovable*>(m_pKGLObject)->SetLocalMatrix(reinterpret_cast<const RwMatrix*>(&matrix));  // 0x000d0be8
    if (m_unk1628 != 0 || m_unk1626 != 0 || m_unk1627 != 0 || m_unk1625 != 0 || m_unk1378 == 0.0f) return;
    const CVector3& at = Modelling(this).m_at;
    const float vx = m_unk127c;
    const float vy = m_unk1280;
    const float vz = m_unk1284;
    m_unk127c = kZero.x;
    m_unk1280 = kZero.y;
    m_unk1284 = kZero.z;
    float along = vy * at.y;
    along = ppc::fmadds(vx, at.x, along);
    along = ppc::fmadds(vz, at.z, along);
    if (!(along > 0.0f)) return;
    m_unk1284 = ppc::fmadds(along, at.z, kZero.z);
    m_unk127c = ppc::fmadds(along, at.x, kZero.x);
    m_unk1280 = ppc::fmadds(along, at.y, kZero.y);
}

// ---- The climbing dynamics (CKSrvDynamic sub-steps) ----

namespace {
// 0x00c50d7c (TOC1 +0x24f4): the shared down vector (0, -1, 0).
constexpr CVector3 kDown{0.0f, -1.0f, 0.0f};
float Length(const CVector3& v) { return std::sqrt(ppc::fmadds(v.z, v.z, ppc::fmadds(v.x, v.x, v.y * v.y))); }
// 0x002ce540 / 0x002ce580 CKGrpS08Hero_GetTetherDampingRadius_maybe / ..Coeff_maybe (local copies): +0x128 / +0x130 with
// +0xfc set, else +0x114 / +0x11c. 0x002ce560 ..SpringStiffness_maybe: +0x12c / +0x118.
float TetherDampingRadius(const CKGrpS08Hero* group) { return group->m_unkfc != 0 ? group->m_unk128 : group->m_unk114; }
float TetherDampingCoeff(const CKGrpS08Hero* group) { return group->m_unkfc != 0 ? group->m_unk130 : group->m_unk11c; }
float TetherSpringStiffness(const CKGrpS08Hero* group) { return group->m_unkfc != 0 ? group->m_unk12c : group->m_unk118; }
}  // namespace

// 0x0031ef70 CKHkS08Hero_ComputeClimbMoveVectorByMode_maybe: the climb impulse of the current climb move (+0x1664): the
// move's up (+0x164c), tilted about the move's x axis (+0x1658) by the move's angle when that axis is set, times the
// move's push (scaled by (dt + +0x162c) / dt on the frame the push ends, +0xecc bit 13), while +0x1622 is set.
CVector3 CKHkS08Hero::ComputeClimbMoveVectorByMode(float dt) {
    CVector3 out = kZero;
    const uint8_t mode = m_unk1664;
    float angle = 0.0f;
    switch (mode) {
        case 0: angle = m_unkc10; break;
        case 1:
        case 2: angle = m_unkc0c; break;
        case 3: angle = m_unkc14; break;
        case 4: angle = m_unkc84; break;
        case 5: angle = AsF32(m_unkca4); break;
        case 6:
        case 7: angle = m_unkc94; break;
        case 8: angle = m_unkcb4; break;
        default: break;
    }
    CVector3 v;
    const CVector3 axis{m_unk1658, m_unk165c, m_unk1660};
    if (Length(axis) == 0.0f) {  // Math_Sqrtf
        v = {m_unk164c, m_unk1650, m_unk1654};
    } else {
        CVector3 up{m_unk164c, m_unk1650, m_unk1654};
        CVector3 at = axis;
        v = Vec3_TiltUpVectorAroundLocalX(angle, &up, &at);  // 0x002fbd78
    }
    float push = 0.0f;
    if (mode <= 8) {
        switch (mode) {  // TOC1 +0x2538 / +0x253c (the same pushes in both tables)
            case 0: push = m_unkbf8; break;
            case 1:
            case 2: push = m_unkbf4; break;
            case 3: push = m_unkbfc; break;
            case 4: push = m_unkc74; break;
            case 5: push = m_unkc98; break;
            case 6:
            case 7: push = m_unkc88; break;
            default: push = m_unkca8; break;
        }
    }
    if (m_unk1624 != 0) {
        m_unkecc = (m_unkecc & 0xffffdfffu) | 0x2000u;
        push = push * ((dt + m_unk162c) / dt);
    }
    if (m_unk1622 != 0) {
        out.x = ppc::fmadds(push, v.x, out.x);
        out.y = ppc::fmadds(push, v.y, out.y);
        out.z = ppc::fmadds(push, v.z, out.z);
    }
    return out;
}

// 0x00321438 CKHkS08Hero_IntegrateClimbVelocity_maybe: the velocity (+0x127c) moved one step by the climbing forces:
// gravity (+0xc2c) and the lift that carries it (scaled by the stick's speed +0x1378 going down (+0x1665 1) or up (0,
// to +0xc1c)), a drag of +0xd10 along `direction` times the speed, the timed push +0x1764 (+0x1758 x its time left
// +0x1770 over +0x1774); a velocity turned against `direction` stops; at most `maxSpeed`. The step dt x velocity is
// returned.
CVector3 CKHkS08Hero::IntegrateClimbVelocity(float dt, float maxSpeed, const CVector3* direction) {
    const float mass = GetMass();  // 0x002f8818
    const CVector3 gravity{kDown.x * m_unkc2c, kDown.y * m_unkc2c, kDown.z * m_unkc2c};
    const CVector3 weight = AccelToForce(mass, &gravity);  // 0x0030fb68
    float lift = mass * m_unkc2c;
    CVector3 up;
    if (m_unk1665 == 1) {
        lift = Math_RemapClamped(0.0f, 1.0f, m_unk1378, lift, 0.0f);  // 0x00333618
    } else if (m_unk1665 == 0) {
        lift = Math_RemapClamped(0.0f, 1.0f, m_unk1378, lift, m_unkc1c);
    }
    up.z = kHeroAxisY.z * lift;
    up.x = kHeroAxisY.x * lift;
    up.y = kHeroAxisY.y * lift;
    const float drag = -m_unkd10;
    const CVector3 dir = *direction;
    const float speed = Length({m_unk127c, m_unk1280, m_unk1284});  // Math_Sqrtf
    CVector3 push = kZero;
    if (m_unk1760 != 0) {
        uint8_t timed = m_unk1760;
        if (AsF32(m_unk1770) < 0.0f) {
            m_unk1764 = kZero.x;
            m_unk176c = kZero.z;
            m_unk1768 = kZero.y;
            SetF32(m_unk1774, 0.0f);
            SetF32(m_unk1770, 0.0f);
            m_unk1760 = 0;
        } else {
            SetF32(m_unk1774, dt);
            SetF32(m_unk1770, AsF32(m_unk1770) - dt);
        }
        push = kZero;
        const float step = AsF32(m_unk1774);
        if (timed != 0 && step != 0.0f) {
            const float left = AsF32(m_unk1770);
            float scale = m_unk1758;
            if (!(left >= 0.0f)) scale = ((step + left) / step) * m_unk1758;
            push.z = ppc::fmadds(scale, m_unk176c, push.z);
            push.x = ppc::fmadds(scale, m_unk1764, push.x);
            push.y = ppc::fmadds(scale, m_unk1768, push.y);
        }
    }
    CVector3 force;
    force.x = ppc::fmadds((kZero.x + dir.x) * drag, speed, (weight.x + kZero.x) + up.x) + push.x;
    force.y = ppc::fmadds((kZero.y + dir.y) * drag, speed, (weight.y + kZero.y) + up.y) + push.y;
    force.z = ppc::fmadds((kZero.z + dir.z) * drag, speed, (weight.z + kZero.z) + up.z) + push.z;
    const CVector3 accel = ForceToAccel(dt, mass, &force);  // 0x00310ba8
    const CVector3 delta = AccelToVelocityDelta(dt, &accel);  // 0x0030fb98
    const float vy = m_unk1280 + delta.y;
    const float vx = m_unk127c + delta.x;
    const float vz = m_unk1284 + delta.z;
    m_unk1280 = vy;
    m_unk127c = vx;
    m_unk1284 = vz;
    float along = vy * dir.y;
    along = ppc::fmadds(vx, dir.x, along);
    along = ppc::fmadds(vz, dir.z, along);
    if (along < 0.0f) {
        m_unk127c = kZero.x;
        m_unk1280 = kZero.y;
        m_unk1284 = kZero.z;
    }
    if (Length({m_unk127c, m_unk1280, m_unk1284}) > maxSpeed) {
        const float length = Length({m_unk127c, m_unk1280, m_unk1284});
        if (length != 0.0f) {
            const float inverse = 1.0f / length;
            m_unk1284 = inverse * m_unk1284;
            m_unk127c = inverse * m_unk127c;
            m_unk1280 = inverse * m_unk1280;
        }
        m_unk1284 = maxSpeed * m_unk1284;
        m_unk127c = maxSpeed * m_unk127c;
        m_unk1280 = maxSpeed * m_unk1280;
    }
    return {dt * m_unk127c, dt * m_unk1280, dt * m_unk1284};
}

// 0x00321948 CKHkS08Hero_UpdateClimbDisplacement_maybe: the frame's climb move into the position adjustment (+0x1268).
// A wall (+0x1744 0): up (+0x1665 0, below the top), down (1 or +0x1760, above the bottom), or slowing to a stop,
// clamped to the zone's extent; a ceiling (+0x1744 2): along the node's at axis by the stick (+0x1374 its sign) within
// the zone's extent. The move is dropped while the partner climbs out of reach; the move flags +0x161c / +0x161f /
// +0x168c..+0x168e tell the animation. A leap (+0x1628) moves by the velocity; +0x1626 stops it.
void CKHkS08Hero::UpdateClimbDisplacement(float dt) {
    const uint32_t kind = m_unk1744;
    CVector3* velocity = reinterpret_cast<CVector3*>(&m_unk127c);
    CVector3* adjust = reinterpret_cast<CVector3*>(&m_unk1268);
    const CVector3 position{m_unk54c, m_unk550, m_unk554};
    // The move dropped when the partner climbs and the move would take the hero out of its reach (and farther than now).
    auto partnerHolds = [&](const CVector3& d) {
        CKHkS08Hero* partner = GetPartnerHero();  // 0x002f85f8
        const float tx = ((m_unk54c + m_unk1268) + d.x) - partner->m_unk54c;
        const float ty = ((m_unk550 + m_unk126c) + d.y) - partner->m_unk550;
        const float tz = ((m_unk554 + m_unk1270) + d.z) - partner->m_unk554;
        const float after = std::sqrt(ppc::fmadds(tz, tz, ppc::fmadds(tx, tx, ty * ty)));
        if (PartnerShouldStayClimbing() == 0 || (m_unkec4 & 0x400000u) != 0) return false;  // 0x002f8628
        if (!(after >= GetMaxPartnerDistance(m_pGrpHero))) return false;
        CKHkS08Hero* other = GetPartnerHero();
        const float cx = m_unk54c - other->m_unk54c;
        const float cy = m_unk550 - other->m_unk550;
        const float cz = m_unk554 - other->m_unk554;
        const float now = std::sqrt(ppc::fmadds(cz, cz, ppc::fmadds(cx, cx, cy * cy)));
        return after >= now;
    };
    if (kind == 0) {
        bool climb = (m_unkec4 & 0x40000000u) == 0 && (m_unkec4 & 0x20000000u) == 0 && (m_unkec8 & 1u) == 0 && m_unk1679 != 0;
        if (climb && m_unk1628 != 0) {
            adjust->x = ppc::fmadds(dt, velocity->x, kZero.x) + adjust->x;
            adjust->y = ppc::fmadds(dt, velocity->y, kZero.y) + adjust->y;
            adjust->z = ppc::fmadds(dt, velocity->z, kZero.z) + adjust->z;
            climb = false;
        } else if (climb && m_unk1626 != 0) {
            climb = false;
        } else if (climb && (m_unk167a != 0 || m_unk1678 != 0 || m_unk1694 == nullptr)) {
            UpdateForwardAndSpeedStats();  // 0x00310d88
            return;
        }
        if (climb) {
            const float speed = GetClimbSpeed();  // 0x002f94d0
            CKHkClimbZone* zone = m_unk1694;
            const float bottom = zone->NodeLtm().m_pos.y;
            const float top = bottom + zone->m_fUnk30;
            m_unk168d = 0;
            m_unk168c = 0;
            m_unk168e = 0;
            CVector3 d = kZero;
            enum { kMoveIdle, kMoveUp, kMoveDown } move = kMoveIdle;
            if (m_unk1665 == 0) {
                CVector3 probe = position;
                if (zone->IsBelowTop(&probe) != 0) move = kMoveUp;  // 0x00457768
            }
            if (move == kMoveIdle && (m_unk1665 == 1 || m_unk1760 != 0)) {
                CVector3 probe = position;
                if (zone->IsAboveBottom(&probe) != 0) move = kMoveDown;  // 0x00457740
            }
            if (move == kMoveUp) {
                const CVector3 dir = kHeroAxisY;  // TOC1 +0x252c
                d = IntegrateClimbVelocity(dt, speed, &dir);  // 0x00321438
                if (d.y + m_unk550 > top) {
                    const float x = d.x + m_unk54c;
                    const float z = d.z + m_unk554;
                    d.y = top - m_unk550;
                    d.x = x - m_unk54c;
                    d.z = z - m_unk554;
                }
                if (Length(d) <= 0.0f) {
                    m_unk161f = 0;
                    m_unk161c = 1;
                } else {
                    m_unk161c = 0;
                    m_unk168c = 1;
                    m_unk161f = 1;
                }
            } else if (move == kMoveDown) {
                const CVector3 dir = kDown;
                d = IntegrateClimbVelocity(dt, speed, &dir);
                if (!(d.y + m_unk550 >= bottom)) {
                    const float x = d.x + m_unk54c;
                    const float z = d.z + m_unk554;
                    d.y = bottom - m_unk550;
                    d.x = x - m_unk54c;
                    d.z = z - m_unk554;
                }
                if (Length(d) <= 0.0f) {
                    m_unk161f = 0;
                    m_unk161c = 1;
                } else {
                    m_unk161c = 0;
                    m_unk168d = 1;
                    m_unk161f = 1;
                    const float limit = (m_unkec8 & 0x10000u) != 0 ? m_unkc60 : m_unkc5c;
                    m_unk168e = limit >= Length(*velocity) ? 0 : 1;
                }
            } else if (m_unkd14 < Length(*velocity)) {
                // Slowing to a stop along the velocity, within the zone's bottom and top.
                CVector3 n = *velocity;
                const float length = Length(n);
                if (length != 0.0f) {
                    const float inverse = 1.0f / length;
                    n.z = n.z * inverse;
                    n.x = n.x * inverse;
                    n.y = n.y * inverse;
                }
                d = IntegrateClimbVelocity(dt, speed, &n);
                const float y = d.y + m_unk550;
                const float x = d.x + m_unk54c;
                const float z = d.z + m_unk554;
                if (!(top >= y)) {
                    *velocity = kZero;
                    d = kZero;
                    m_unk54c = x;
                    m_unk550 = top;
                    m_unk554 = z;
                } else if (!(bottom <= y)) {
                    *velocity = kZero;
                    d = kZero;
                    m_unk54c = x;
                    m_unk550 = bottom;
                    m_unk554 = z;
                }
                if (!(d.y <= 0.0f)) {  // ble
                    m_unk168c = 1;
                    m_unk168d = 0;
                    m_unk161f = 1;
                    m_unk161c = 0;
                } else if (d.y >= 0.0f) {
                    *velocity = kZero;
                    m_unk161f = 0;
                    m_unk161c = 1;
                } else {
                    m_unk168d = 1;
                    m_unk168c = 0;
                    m_unk161f = 1;
                    m_unk161c = 0;
                    const float limit = (m_unkec8 & 0x10000u) != 0 ? m_unkc60 : m_unkc5c;
                    m_unk168e = limit >= Length(*velocity) ? 0 : 1;
                }
            } else {
                *velocity = kZero;
                m_unk161f = 0;
                m_unk161c = 1;
            }
            if (partnerHolds(d)) d = kZero;
            adjust->x = adjust->x + d.x;
            adjust->y = adjust->y + d.y;
            adjust->z = adjust->z + d.z;
        }
        if (m_unk1626 != 0) *velocity = kZero;
        UpdateForwardAndSpeedStats();
        return;
    }
    if (kind != 2) {
        UpdateForwardAndSpeedStats();
        return;
    }
    // A ceiling zone (kind 0).
    bool after = true;
    if (m_unk1679 != 0 && m_unk1628 == 0 && m_unk1626 == 0) {
        if (m_unk167a != 0 || m_unk1678 != 0 || m_unk1694 == nullptr) {
            UpdateForwardAndSpeedStats();
            return;
        }
        const float climbSpeed = GetClimbSpeed() * m_unk1378;
        m_unk168e = 0;
        m_unk168d = 0;
        m_unk168c = 0;
        CVector3 at = Modelling(this).m_at;
        const float sign = m_unk1374 < 0.0f ? -1.0f : 1.0f;  // TOC1 +0x2544 / +0x251c
        at.x = at.x * sign;
        at.z = at.z * sign;
        at.y = at.y * sign;
        float step;
        if (m_unk1374 < 0.0f || (m_unkecc & 0x20000u) != 0) {
            at = kZero;
            *velocity = kZero;
            if ((m_unkecc & 0x20000u) == 0) m_unkecc = (m_unkecc & 0xfffbffffu) | ((((m_unkecc >> 18) & 1u) ^ 1u) << 18);
            m_unkecc = (m_unkecc & 0xfffdffffu) | 0x20000u;
            step = 0.0f;
        } else {
            step = dt * climbSpeed;
        }
        CVector3 d = m_unk1694->ClampMoveToExtent(&position, &at);  // 0x00457ad8
        if (kZero.x != d.x || kZero.y != d.y || kZero.z != d.z) {
            const float length = Length(d);
            if (step > length) step = Length(d);
            d.x = step * at.x;
            d.z = step * at.z;
            d.y = step * at.y;
        }
        if (partnerHolds(d)) d = kZero;
        if (Length(d) <= 0.0f) {
            m_unk161f = 0;
            m_unk161c = 1;
        } else {
            m_unk161f = 1;
            m_unk161c = 0;
            if (m_unk1374 <= 0.0f) {
                m_unk168d = 1;
            } else {
                m_unk168c = 1;
            }
        }
        velocity->x = climbSpeed * at.x;
        velocity->z = climbSpeed * at.z;
        velocity->y = climbSpeed * at.y;
        adjust->x = adjust->x + d.x;
        adjust->y = adjust->y + d.y;
        adjust->z = adjust->z + d.z;
    } else if (m_unk1679 != 0 && m_unk1628 == 0) {
        after = true;  // +0x1626: the velocity is cleared below
    }
    (void)after;
    if (m_unk1626 != 0) *velocity = kZero;
    if (m_unk1679 != 0 && m_unk1628 != 0) {
        adjust->x = ppc::fmadds(dt, velocity->x, kZero.x) + adjust->x;
        adjust->y = ppc::fmadds(dt, velocity->y, kZero.y) + adjust->y;
        adjust->z = ppc::fmadds(dt, velocity->z, kZero.z) + adjust->z;
    }
    UpdateForwardAndSpeedStats();
}

// 0x00322518 CKHkS08Hero_DynamicStage1Climb_maybe (CKSrvDynamic hook, each fixed sub-step, a climb holds the hero): the
// move input, the climb timers (+0x162c the push, +0x1630 / +0x1634 the leap's, +0x163c the leap's time), the let-go
// (+0x1629: a leap near the ground or too long), the zone's push from the partner tether, the leap's forces into the
// velocity, then the climb move (UpdateClimbDisplacement).
void CKHkS08Hero::DynamicStage1Climb(float dt) {
    ComputeCameraRelativeMove();  // 0x00311df0
    m_unk1624 = 0;
    if (!(m_unk162c <= 0.0f)) {  // ble
        m_unk162c = m_unk162c - dt;
        if (m_unk162c <= 0.0f) m_unk1624 = 1;
    } else {
        m_unk1622 = 0;
    }
    m_unk1630 = m_unk1626 != 0 ? m_unk1630 - dt : 0.0f;
    m_unk1634 = m_unk1627 != 0 ? m_unk1634 - dt : 0.0f;
    m_unk1629 = 0;
    if (m_unk1628 != 0) {
        if (m_unk1744 == 2) {
            CGroundContactDatasInOut contact;
            CVector3 point{m_unk54c, m_unk550, m_unk554};
            GroundContact_ProbeGroundPoint(&contact, &point, nullptr);  // 0x00583ef8 (TocBridge 0x98f360)
            const float drop = m_unk550 - point.y;
            if (drop > 0.0f && m_unkcc4 > drop) m_unk1629 = 1;
        } else if (!(m_gcCurDatasInOut.m_fdH >= m_unkcc4)) {  // +0x4dc; bge
            m_unk1629 = 1;
        }
        const float time = m_unk163c;
        if (time > m_unkcbc) m_unk1694 = nullptr;
        if (time > m_unkcc0) m_unk1629 = 1;
        m_unk163c = dt + time;
    }
    CKGrpS08Hero* group = static_cast<CKGrpS08Hero*>(m_pGrpHero);
    if (m_unk1694 != nullptr) {
        const CVector3 damping = ComputePartnerTetherDampingForce(TetherDampingRadius(group), TetherDampingCoeff(group));  // 0x0030fe70
        const CVector3 spring = ComputePartnerTetherSpringForce(group->GetTetherSpringRadius(), TetherSpringStiffness(group));  // 0x003103f0
        CKHkClimbZone* zone = m_unk1694;
        zone->m_vUnk9C.x = (kZero.x + damping.x) + spring.x;
        zone->m_vUnk9C.y = (kZero.y + damping.y) + spring.y;
        zone->m_vUnk9C.z = (kZero.z + damping.z) + spring.z;
        zone->m_vUnkA8 = {m_unk54c, m_unk550, m_unk554};
    }
    const float mass = GetMass();  // 0x002f8818
    if (m_unk1628 != 0) {
        const CVector3 move = ComputeClimbMoveVectorByMode(dt);  // 0x0031ef70
        const CVector3 gravity{ppc::fmadds(m_unkc2c, kDown.x, kZero.x), ppc::fmadds(m_unkc2c, kDown.y, kZero.y),
                               ppc::fmadds(m_unkc2c, kDown.z, kZero.z)};
        CVector3 force{kZero.x + move.x, kZero.y + move.y, kZero.z + move.z};
        const CVector3 weight = AccelToForce(mass, &gravity);  // 0x0030fb68
        force.x = force.x + weight.x;
        force.y = force.y + weight.y;
        force.z = force.z + weight.z;
        const CVector3 lunge = StartLungeFromMark(dt);  // 0x003008d8
        force.x = force.x + lunge.x;
        force.y = force.y + lunge.y;
        force.z = force.z + lunge.z;
        // The tether's spring and damping (group +0x110 / +0x118, +0x114 / +0x11c) are computed and not used.
        (void)ComputePartnerTetherSpringForce(group->m_unk110, group->m_unk118);  // 0x003103f0
        (void)ComputePartnerTetherDampingForce(group->m_unk114, group->m_unk11c);  // 0x0030fe70
        const CVector3 accel = ForceToAccel(dt, mass, &force);  // 0x00310ba8
        const CVector3 delta = AccelToVelocityDelta(dt, &accel);  // 0x0030fb98
        m_unk127c = m_unk127c + delta.x;
        m_unk1280 = m_unk1280 + delta.y;
        m_unk1284 = m_unk1284 + delta.z;
    }
    UpdateClimbDisplacement(dt);  // 0x00321948
}

// ---- Letting go, the climb locomotion (once per frame), the node while climbing ----

namespace {
// The game's inlined cosf / sinf of a float whose sign bit is set go through the library with -x (the original tests the
// stored float's bits).
bool SignBit(float x) {
    uint32_t bits;
    std::memcpy(&bits, &x, 4);
    return static_cast<int32_t>(bits) < 0;
}
float GameCosf(float x) { return SignBit(x) ? crt::LibCosf(-x) : crt::InlineCosf(x); }
// The facing (+0x540 cos, +0x548 sin of the yaw +0x538) as AccumulateClimbDetachDisplacement computes it: the sine of a
// negative yaw is -sinf(-yaw).
float GameSinf(float x) { return SignBit(x) ? -crt::LibSinf(-x) : crt::InlineSinf(x); }

// The clamp before Math_Acosf (cror lt|eq against -1, gt|eq against 1).
float AcosClamped(float d) {
    if (d <= -1.0f) return crt::Acosf(-1.0f);  // TOC1 +0x2544
    if (d >= 1.0f) d = 1.0f;                   // TOC1 +0x251c
    return crt::Acosf(d);                      // 0x00780c90 (TocBridge 0x98e1a0)
}

// 0x00310be0 CKHkS08Hero_UpdateOrientationAngles_maybe (CKHkS08Hero_7.cpp's unit; local copy): the tilt springs' speeds
// (+0x12e8 / +0x12ec) stop and their angles follow the node's up axis: the pitch +0x137c (Vec3_GetAngleInYZPlane, in
// (-pi, pi]; 0 for an up axis without a (y, z) part) and the roll +0x12e4 (Vec3_GetAngleInXYPlane; pi / 2 without an
// (x, y) part).
void UpdateOrientationAngles(CKHkS08Hero* hero) {
    constexpr float kPi = 3.14159274101257324f;     // TOC1 +0x2280
    constexpr float kTwoPi = 6.28318548202514648f;  // TOC1 +0x2284
    hero->m_unk12e8 = 0.0f;
    hero->m_unk12ec = 0.0f;
    const CVector3& up = Modelling(hero).m_up;
    const float yz = std::sqrt(ppc::fmadds(up.y, up.y, ppc::fmadds(up.z, up.z, 0.0f)));
    if (yz >= 0.001f) {  // TOC1 +0x227c
        const float pitch = Vec3_GetAngleInYZPlane(&up);  // 0x00244748
        hero->m_unk137c = pitch > kPi ? pitch - kTwoPi : pitch;
    } else {
        hero->m_unk137c = 0.0f;
    }
    const float nx = -up.x;
    const float xy = std::sqrt(ppc::fmadds(up.y, up.y, nx * nx) + 0.0f);
    if (xy >= 0.001f) {
        const float roll = Vec3_GetAngleInXYPlane(&up);  // 0x002443d8
        hero->m_unk12e4 = roll > kPi ? roll - kTwoPi : roll;
    } else {
        hero->m_unk12e4 = 1.57079637050628662f;  // TOC1 +0x2288
    }
}

// The animation time of the inner blender wrapped into its animation's duration (1 without an animation), as
// UpdateClimbSustainedMovement does inline (CKHkS08Hero_GetCurrentAnimResource_maybe 0x301458 / GetCurrentAnimTime
// 0x303368).
void WrappedAnimTime(CKHkS08Hero* hero, float* duration, float* time) {
    const RtAnimAnimation* animation = ActiveController(hero)->m_unk58;
    float d = 1.0f;  // TOC1 +0x251c
    if (animation != nullptr) d = animation->duration;
    float t = ActiveController(hero)->m_unk50;
    if (!(t >= 0.0f)) {
        do {
            t = t + d;
        } while (t < 0.0f);
    }
    while (d <= t) t = t - d;
    *duration = d;
    *time = t;
}

// The two halves of a turn animation: the blend parameter of the first half (to +0.5) or of the second, and which.
float TurnBlend(CKHkS08Hero* hero, uint16_t animation, bool* firstHalf) {
    float r = 0.0f;
    float to = 0.5f;  // TOC1 +0x258c
    if (hero->m_unk160 == animation) {
        float duration;
        float time;
        WrappedAnimTime(hero, &duration, &time);
        r = Math_RemapClamped(0.0f, duration, time, 0.0f, 1.0f);  // 0x00333618
        if (!(duration * 0.5f >= time)) {
            *firstHalf = false;
            return Math_RemapClamped(0.5f, 1.0f, r, 0.0f, 1.0f);
        }
    }
    *firstHalf = true;
    return Math_RemapClamped(0.0f, to, r, 0.0f, 1.0f);
}
}  // namespace

// 0x0031d8b8 CKHkS08Hero_BlendOrientationFromClimbSnapshot_maybe: during a leap the node turns from the snapshot (+0x16e4,
// taken when the leap started) towards the leap's facing by +0x163c / +0xcc0.
void CKHkS08Hero::BlendOrientationFromClimbSnapshot() {
    alignas(16) CMatrix34 matrix = Modelling(this);
    const float t = Math_RemapClamped(0.0f, m_unkcc0, m_unk163c, 0.0f, 1.0f);  // 0x00333618
    float from[4];
    Quat_FromMatrix(from, reinterpret_cast<const float*>(m_unk16e4));  // 0x002420f8
    // BUG(original): the target matrix (a stack block) is only written for the side and down leaps (+0x1664 5..8); for the
    // others its quaternion comes from whatever the stack held. Natively that block is the zero matrix.
    alignas(16) CMatrix34 target{};
    if (static_cast<uint8_t>(m_unk1664 - 5) <= 3) {
        const CMatrix34& snapshot = *m_unk16e4;
        target.m_at = snapshot.m_at;
        target.m_ui32Flags &= 0xfffdfffcu;
        target.m_right = {-snapshot.m_right.x, -snapshot.m_right.y, -snapshot.m_right.z};
        target.m_up = {-snapshot.m_up.x, -snapshot.m_up.y, -snapshot.m_up.z};
    }
    float to[4];
    Quat_FromMatrix(to, reinterpret_cast<const float*>(&target));
    float q[4];
    Quat_Slerp(t, q, from, to);  // 0x00242728
    QuatToMatrixNormalizing(q, &matrix);  // 0x00241d78
    matrix.m_pos = {m_unk54c, m_unk550, m_unk554};
    matrix.m_ui32Flags &= 0xfffdffffu;
    static_cast<CSGMovable*>(m_pKGLObject)->SetLocalMatrix(reinterpret_cast<const RwMatrix*>(&matrix));  // 0x000d0be8
}

// 0x0031ff88 CKHkS08Hero_UpdateClimbSustainedMovement_maybe (the node of a hero a climb holds): turning round on a
// ceiling (+0xecc bit 17, the turn animation 0x8c), the mount's end (animations 0x89 / 0x8a: on the attach point), the
// ledge (+0xec8 bit 31: towards the climb-over point +0x1734, turning to +0x1728), the climb-over start (animation 0x88
// with the blender at its start), a leap's turn (animation 0x8b) or the plain attach axes (+0x1700 / +0x170c); then
// the hero sticks to its zone and the yaw follows the node.
void CKHkS08Hero::UpdateClimbSustainedMovement(float dt) {
    CSGMovable* node = static_cast<CSGMovable*>(m_pKGLObject);
    bool stick = true;  // the mount's end sticks to the zone itself
    if ((m_unkecc & 0x20000u) != 0 && m_unk1694 != nullptr) {
        // The ceiling turn: from the attach matrix to the one turned round (right and at negated), half way through a
        // side matrix (the at axis the attach's right, the right the turned at).
        CVector3 probe{m_unk54c, m_unk550, m_unk554};
        alignas(16) CMatrix34 a;
        m_unk1694->GetAttachMatrix(&probe, &a, 0);  // 0x00458a88
        alignas(16) CMatrix34 b = a;
        b.m_at = {-a.m_at.x, -a.m_at.y, -a.m_at.z};
        b.m_ui32Flags = a.m_ui32Flags & 0xfffdfffcu;
        b.m_right = {-a.m_right.x, -a.m_right.y, -a.m_right.z};
        bool firstHalf = true;
        const float t = TurnBlend(this, 0x8c, &firstHalf);
        if ((m_unkecc & 0x40000u) == 0) {
            const CMatrix34 swap = a;
            a = b;
            b = swap;
        }
        alignas(16) CMatrix34 c = a;
        c.m_at = a.m_right;
        c.m_ui32Flags &= 0xfffdfffcu;
        c.m_right = b.m_at;
        float qa[4];
        float qb[4];
        if (firstHalf) {
            Quat_FromMatrix(qa, reinterpret_cast<const float*>(&a));
            Quat_FromMatrix(qb, reinterpret_cast<const float*>(&c));
        } else {
            Quat_FromMatrix(qa, reinterpret_cast<const float*>(&c));
            Quat_FromMatrix(qb, reinterpret_cast<const float*>(&b));
        }
        float q[4];
        Quat_Slerp(t, q, qa, qb);
        alignas(16) CMatrix34 m;
        QuatToMatrixNormalizing(q, &m);
        m.m_pos = {m_unk54c, m_unk550, m_unk554};
        m.m_ui32Flags &= 0xfffdffffu;
        node->SetLocalMatrix(reinterpret_cast<const RwMatrix*>(&m));
        m_unk170c[0] = m.m_at.x;
        m_unk170c[2] = m.m_at.z;
        m_unk170c[1] = m.m_at.y;
        m_unk1700[0] = m.m_up.x;
        m_unk1700[2] = m.m_up.z;
        m_unk1700[1] = m.m_up.y;
    } else if (IsAnimFinished(this, 0x89) != 0 || IsAnimFinished(this, 0x8a) != 0) {
        // The mount is over: the hero on the attach point (0.05 out), climbing.
        m_unkecc = (m_unkecc & 0xfffffffeu) | 1u;
        m_unkec8 &= 0x7fffffffu;
        m_unk1677 = 0;
        m_unk1679 = 1;
        m_unk1678 = 0;
        node->SetLocalMatrix(reinterpret_cast<const RwMatrix*>(m_unk16d8));  // 0x000d0be8
        const CMatrix34& attach = *m_unk16d8;
        m_unk54c = attach.m_pos.x;
        m_unk550 = attach.m_pos.y;
        m_unk554 = attach.m_pos.z;
        m_unk554 = ppc::fmadds(attach.m_up.z, 0.05f, attach.m_pos.z);  // TOC1 +0x2528
        m_unk54c = ppc::fmadds(attach.m_up.x, 0.05f, attach.m_pos.x);
        m_unk550 = ppc::fmadds(attach.m_up.y, 0.05f, attach.m_pos.y);
        m_unk1700[0] = attach.m_up.x;
        m_unk1700[1] = attach.m_up.y;
        m_unk1700[2] = attach.m_up.z;
        m_unk170c[0] = attach.m_at.x;
        m_unk170c[1] = attach.m_at.y;
        m_unk170c[2] = attach.m_at.z;
        RwFrame* frame = node->m_pRwFrame;
        frame->modelling.pos.x = m_unk54c;
        frame->modelling.pos.y = m_unk550;
        frame->modelling.pos.z = m_unk554;
        reinterpret_cast<CMatrix34*>(&frame->modelling)->m_ui32Flags &= 0xfffdffffu;
        RwFrame_MarkDirty(frame);  // 0x00010698
        static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision)->GroundProbePoints(&m_gcDatasIn, &m_gcCurDatasInOut, &m_unk54c, 1);  // 0x00196540
        StickToCurrentClimbZone();  // 0x0031df00
        UpdateOrientationAngles(this);  // 0x00310be0
        stick = false;
    } else if (static_cast<int32_t>(m_unkec8) < 0) {
        // The ledge: towards the climb-over point at +0xccc, turning to the ledge's facing at +0xcc8 degrees.
        float x = m_unk54c;
        float y = m_unk550;
        float z = m_unk554;
        if (x != m_unk1734 || y != m_unk1738 || z != m_unk173c) {
            const float dy = m_unk1738 - y;
            const float dx = m_unk1734 - x;
            const float step = dt * m_unkccc;
            const float dz = m_unk173c - z;
            const float left = ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy));
            if (!(step * step <= left)) {
                x = m_unk1734;
                y = m_unk1738;
                z = m_unk173c;
            } else {
                const float scale = step * rwInvSqrt(left);  // 0x000114d8 Math_InvSqrtf
                z = ppc::fmadds(dz, scale, z);
                x = ppc::fmadds(dx, scale, x);
                y = ppc::fmadds(dy, scale, y);
            }
        }
        m_unk54c = x;
        m_unk550 = y;
        m_unk554 = z;
        const float current = Vec3_GetYawAngleFromZ(&Modelling(this).m_at);  // 0x00244528
        const CVector3 facing{m_unk1728, m_unk172c, m_unk1730};
        float approach[3] = {Vec3_GetYawAngleFromZ(&facing), m_unkcc8 * 0.0174532905f, current};  // TOC1 +0x2594
        FloatApproach_StepAngle(dt, approach);  // 0x00243748
        alignas(16) CMatrix34 m;
        m.m_right = {1.0f, 0.0f, 0.0f};
        m.m_up = {0.0f, 1.0f, 0.0f};
        m.m_at = {0.0f, 0.0f, 1.0f};
        m.m_pos = {0.0f, 0.0f, 0.0f};
        m.m_ui32Flags = 0x20003;
        Mat4_RotateLocalYDeg(approach[2] * 57.2957801818847656f, &m);  // TOC1 +0x2554
        m.m_pos = {m_unk54c, m_unk550, m_unk554};
        m.m_ui32Flags &= 0xfffdffffu;
        node->SetLocalMatrix(reinterpret_cast<const RwMatrix*>(&m));
    } else {
        AnimBlendSlot* slot = GetAnimBlendSlot();  // vt+0x194
        if (slot->m_unk14 == 0 && m_unk160 == 0x88) {
            // The climb-over starts: the hero 1.05 back from the wall and 2 up, on the ground there, upright.
            m_unkec4 = (m_unkec4 & 0x7fffffffu) | 0x80000000u;
            CVector3 probe{m_unk54c, m_unk550, m_unk554};
            alignas(16) CMatrix34 attach;
            m_unk1694->GetAttachMatrix(&probe, &attach, 0);  // 0x00458a88
            const CVector3 wall = m_unk1694->NodeLtm().m_at;
            const CVector3 top = AddTwoScaled(1.04999995f, 2.0f, &attach.m_pos, &wall, &kHeroAxisY);  // TOC1 +0x2598 / +0x259c
            m_unk54c = top.x;
            m_unk550 = top.y;
            m_unk554 = top.z;
            CGroundContactDatasInOut contact;
            GroundContact_ProbeGroundPoint(&contact, reinterpret_cast<CVector3*>(&m_unk54c), nullptr);  // 0x00583ef8
            alignas(16) CMatrix34 m;
            m.m_right = {1.0f, 0.0f, 0.0f};
            m.m_up = {0.0f, 1.0f, 0.0f};
            m.m_at = {0.0f, 0.0f, 1.0f};
            m.m_pos = {0.0f, 0.0f, 0.0f};
            m.m_ui32Flags = 0x20003;
            Mat4_SetBasisFromUpAt(&m, &kHeroAxisY, &Modelling(this).m_right);  // 0x002400a8 (the frame's +0x10)
            m.m_pos = {m_unk54c, m_unk550, m_unk554};
            m.m_ui32Flags &= 0xfffdffffu;
            node->SetLocalMatrix(reinterpret_cast<const RwMatrix*>(&m));
            const CMatrix34& placed = Modelling(this);
            m_unk1700[0] = placed.m_up.x;
            m_unk1700[2] = placed.m_up.z;
            m_unk1700[1] = placed.m_up.y;
            m_unk170c[0] = placed.m_at.x;
            m_unk170c[2] = placed.m_at.z;
            m_unk170c[1] = placed.m_at.y;
        } else if (m_unk178c == 0 && m_unk1628 != 0 && m_unk1664 == 8) {
            // The down leap's turn (animation 0x8b): the snapshot towards the leap matrices.
            alignas(16) CMatrix34 m = Modelling(this);
            float t;
            float qa[4];
            float qb[4];
            bool firstHalf = true;
            t = TurnBlend(this, 0x8b, &firstHalf);
            if (firstHalf) {
                Quat_FromMatrix(qa, reinterpret_cast<const float*>(m_unk16e4));
                Quat_FromMatrix(qb, reinterpret_cast<const float*>(m_unk16ec));
            } else {
                Quat_FromMatrix(qa, reinterpret_cast<const float*>(m_unk16ec));
                Quat_FromMatrix(qb, reinterpret_cast<const float*>(m_unk16e8));
            }
            float q[4];
            Quat_Slerp(t, q, qa, qb);
            QuatToMatrixNormalizing(q, &m);
            m.m_pos = {m_unk54c, m_unk550, m_unk554};
            m.m_ui32Flags &= 0xfffdffffu;
            node->SetLocalMatrix(reinterpret_cast<const RwMatrix*>(&m));
            m_unk1828 = -0.5f;  // TOC1 +0x25a0
            m_unkecc = (m_unkecc & 0xfffeffffu) | 0x10000u;
        } else if (m_unk178c != 0 && m_unk1628 != 0) {
            BlendOrientationFromClimbSnapshot();  // 0x0031d8b8
        } else {
            alignas(16) CMatrix34 m;
            const CVector3 up{m_unk1700[0], m_unk1700[1], m_unk1700[2]};
            const CVector3 at{m_unk170c[0], m_unk170c[1], m_unk170c[2]};
            Mat4_BuildFromUpAndForward(&m, &up, &at);  // 0x0023ff80
            m.m_pos = {m_unk54c, m_unk550, m_unk554};
            m.m_ui32Flags &= 0xfffdffffu;
            node->SetLocalMatrix(reinterpret_cast<const RwMatrix*>(&m));
        }
    }
    if (stick) {
        StickToCurrentClimbZone();  // 0x0031df00
        UpdateOrientationAngles(this);  // 0x00310be0
    }
    if ((m_unkec8 & 1u) == 0 && m_unk1664 != 8 && m_unk1744 != 2) {
        const CVector3& up = Modelling(this).m_up;
        const CVector3 down{-up.x, -up.y, -up.z};
        m_unk538 = Vec3_GetYawAngleFromX(&down);  // 0x00244638
    } else {
        m_unk538 = Vec3_GetYawAngleFromX(&Modelling(this).m_at);
    }
}

// 0x0031ece8 CKHkS08Hero_ComputeClimbDetachForce_maybe: without stick (or during a leap) the force along the facing
// (+0x1288) from `force`'s part into the ground normal (+0x564) times +0xc20, scaled down below the speed +0xd04.
CVector3 CKHkS08Hero::ComputeClimbDetachForce(float dt, const CVector3* force) {
    CVector3 out = kZero;
    if (m_unk1378 != 0.0f && m_unk1627 == 0 && m_unk1626 == 0) return out;
    float dot = force->y * m_unk568;
    dot = ppc::fmadds(force->x, m_unk564, dot);
    dot = ppc::fmadds(force->z, m_unk56c, dot);
    float scale = dot * m_unkc20;
    if (m_unk12d0 < m_unkd04) {
        (void)ScaleVec3(dt, force);  // 0x0030f8c0 (its answer is not used)
        if (m_unkd04 == 0.0f) {
            scale = scale * (m_unk12d0 / 0.1f);  // TOC1 +0x2530
        } else {
            scale = scale * (m_unk12d0 / m_unkd04);
        }
    }
    out.x = ppc::fmadds(scale, m_unk1288, out.x);
    out.z = ppc::fmadds(scale, m_unk1290, out.z);
    out.y = ppc::fmadds(scale, m_unk128c, out.y);
    return out;
}

// 0x003229f8 CKHkS08Hero_AccumulateClimbDetachDisplacement_maybe: the velocity's step and the external displacement into
// +0x1268, the horizontal / vertical speeds (+0x530 / +0x534) from the wall move (+0x5b4) and the facing from the yaw.
void CKHkS08Hero::AccumulateClimbDetachDisplacement(float dt) {
    float x = ppc::fmadds(dt, m_unk127c, kZero.x);
    float z = ppc::fmadds(dt, m_unk1284, kZero.z);
    float y = ppc::fmadds(dt, m_unk1280, kZero.y);
    const CVector3 external = GetExternalDisplacement();  // 0x0030fe18
    x = x + external.x;
    z = z + external.z;
    y = y + external.y;
    m_unk1268 = x + m_unk1268;
    m_unk1270 = z + m_unk1270;
    m_unk126c = y + m_unk126c;
    const float horizontal = std::sqrt(ppc::fmadds(m_unk5bc, m_unk5bc, ppc::fmadds(m_unk5b4, m_unk5b4, 0.0f)));
    const float yaw = m_unk538;
    m_unk534 = m_unk5b8 / dt;
    m_unk530 = horizontal / dt;
    const float c = GameCosf(yaw);
    const float s = GameSinf(yaw);
    m_unk540 = c;
    m_unk548 = s;
    m_unk544 = 0.0f;
}

// 0x00322d40 CKHkS08Hero_DynamicStage1ClimbDetach_maybe (CKSrvDynamic hook, each fixed sub-step, climbing with no climb
// holding the hero): gravity, the detach force off the wall, the run along the move input while free, the climb move's
// impulse, the drag along the facing, the tether and the game manager's force into the velocity; the displacement
// accumulated while airborne (+0x1620), tethered (+0x1674) or moving (+0x12d0).
void CKHkS08Hero::DynamicStage1ClimbDetach(float dt) {
    ComputeCameraRelativeMove();  // 0x00311df0
    m_unk1624 = 0;
    if (!(m_unk162c <= 0.0f)) {  // ble
        m_unk162c = m_unk162c - dt;
        if (m_unk162c <= 0.0f) m_unk1624 = 1;
    } else {
        m_unk1622 = 0;
    }
    CVector3 force = kZero;
    m_unk17f0 = force.x;
    m_unk17f4 = force.y;
    m_unk17f8 = force.z;
    force.y = ppc::fmadds(m_unkc2c, kDown.y, kZero.y) + force.y;
    force.x = ppc::fmadds(m_unkc2c, kDown.x, kZero.x) + force.x;
    force.z = ppc::fmadds(m_unkc2c, kDown.z, kZero.z) + force.z;
    m_unk17f4 = force.y;
    m_unk17f0 = force.x;
    m_unk17f8 = force.z;
    bool run = false;
    if (m_unk1628 == 0 && m_unk1626 == 0) {
        if (m_unk1625 == 0) {
            const CVector3 copy = force;
            const CVector3 detach = ComputeClimbDetachForce(dt, &copy);  // 0x0031ece8
            force.x = detach.x + force.x;
            force.y = detach.y + force.y;
            force.z = detach.z + force.z;
            m_unk17f0 = force.x;
            m_unk17f4 = force.y;
            m_unk17f8 = force.z;
            run = m_unk1628 == 0 && m_unk1626 == 0;
        } else {
            run = true;
        }
    }
    if (run && m_unk1627 == 0 && (m_unkec4 & 0x800u) == 0) {
        // The run along the move input: (+0xc18..+0xc1c by the stick) along +0x37c, its part along +0x12a0 kept
        // (not negative), along +0x135c while jumping (+0x1625).
        const float k = m_unkc18 + ppc::fmadds(m_unkc1c - m_unkc18, m_unk1378, 0.0f);
        const float ax = ppc::fmadds(k, m_unk37c, kZero.x);
        const float ay = ppc::fmadds(k, m_unk380, kZero.y);
        const float az = ppc::fmadds(k, m_unk384, kZero.z);
        float along = ay * m_unk12a4;
        along = ppc::fmadds(ax, m_unk12a0, along);
        along = ppc::fmadds(az, m_unk12a8, along);
        if (along < 0.0f) along = 0.0f;
        float rx;
        float ry;
        float rz;
        if (m_unk1625 != 0) {
            rx = ppc::fmadds(along, m_unk135c, kZero.x);
            rz = ppc::fmadds(along, m_unk1364, kZero.z);
            ry = ppc::fmadds(along, m_unk1360, kZero.y);
        } else {
            rz = ppc::fmadds(along, m_unk12a8, kZero.z);
            rx = ppc::fmadds(along, m_unk12a0, kZero.x);
            ry = ppc::fmadds(along, m_unk12a4, kZero.y);
        }
        force.x = (kZero.x + rx) + force.x;
        force.y = (kZero.y + ry) + force.y;
        force.z = (kZero.z + rz) + force.z;
        m_unk17f0 = force.x;
        m_unk17f4 = force.y;
        m_unk17f8 = force.z;
    }
    const CVector3 move = ComputeClimbMoveVectorByMode(dt);  // 0x0031ef70
    force.x = move.x + m_unk17f0;
    force.y = move.y + m_unk17f4;
    force.z = move.z + m_unk17f8;
    m_unk17f0 = force.x;
    m_unk17f4 = force.y;
    m_unk17f8 = force.z;
    CVector3 drag = kZero;
    const float speed = m_unk12d0;
    bool dragCheck = true;
    if (m_unk1378 == 0.0f && IsAnyComboKindActive() == 0) dragCheck = false;  // 0x002fd030
    if (dragCheck && m_unk1628 == 0 && m_unk1626 == 0 && m_unk1627 == 0) {
        const float s = ppc::fnmadds(speed / m_unkbf0, m_unkc1c - m_unkc18, m_unkc18);
        drag.z = ppc::fmadds(s, m_unk1290, drag.z);
        drag.x = ppc::fmadds(s, m_unk1288, drag.x);
        drag.y = ppc::fmadds(s, m_unk128c, drag.y);
    }
    force.x = force.x + drag.x;
    force.y = force.y + drag.y;
    force.z = force.z + drag.z;
    m_unk17f0 = force.x;
    m_unk17f4 = force.y;
    m_unk17f8 = force.z;
    CKGrpS08Hero* group = static_cast<CKGrpS08Hero*>(m_pGrpHero);
    const float dampingRadius = group->m_unk114;
    const float dampingCoeff = group->m_unk11c;
    const CVector3 spring = ComputePartnerTetherSpringForce(group->m_unk110, group->m_unk118);  // 0x003103f0
    const CVector3 damping = ComputePartnerTetherDampingForce(dampingRadius, dampingCoeff);    // 0x0030fe70
    force.x = damping.x + (spring.x + m_unk17f0);
    force.y = damping.y + (spring.y + m_unk17f4);
    force.z = damping.z + (spring.z + m_unk17f8);
    m_unk17f0 = force.x;
    m_unk17f4 = force.y;
    m_unk17f8 = force.z;
    const CVector3 external = GetGameManagerExternalForce();  // 0x0030f8f0
    force.y = external.y + m_unk17f4;
    force.x = external.x + m_unk17f0;
    force.z = external.z + m_unk17f8;
    m_unk17f4 = force.y;
    m_unk17f0 = force.x;
    m_unk17f8 = force.z;
    const CVector3 delta = ScaleVec3(dt, &force);  // 0x0030f8c0
    m_unk127c = m_unk127c + delta.x;
    m_unk1280 = m_unk1280 + delta.y;
    m_unk1284 = m_unk1284 + delta.z;
    if (m_unk1620 != 0 || m_unk1674 != 0 || m_unk12d0 > 0.0f) AccumulateClimbDetachDisplacement(dt);  // 0x003229f8
}

// 0x0031db40 CKHkS08Hero_TryClimbLeap_maybe: a jump press (+0x358 bit 20) during a leap (+0x1628) on a zone, once the
// cooldown +0x1778 is over and no push runs: a new leap in the stick's direction (+0x1665: the climb move +0x1664 5..8
// with its up / axis from the node), the snapshot matrices (+0x16e4 the node, +0x16e8 / +0x16ec turned), the leap time
// and the velocity reset; +0xed0 bit 29.
void CKHkS08Hero::TryClimbLeap() {
    if ((m_unk358 & 0x100000u) == 0) return;
    if (m_unk1778 > 0.0f) return;
    if (m_unk1628 == 0 || m_unk1694 == nullptr || m_unk1622 != 0) return;
    m_unked0 = (m_unked0 & 0xdfffffffu) | 0x20000000u;
    m_unk178c = 0;
    m_unk1778 = 0.2f;  // TOC1 +0x2520
    m_unk1658 = kZero.x;
    m_unk165c = kZero.y;
    m_unk1660 = kZero.z;
    const CMatrix34& frame = Modelling(this);
    switch (m_unk1665) {
        case 0:
            m_unk1664 = 5;
            m_unk164c = frame.m_at.x;
            m_unk1650 = frame.m_at.y;
            m_unk1654 = frame.m_at.z;
            m_unk1658 = -frame.m_right.x;
            m_unk165c = -frame.m_right.y;
            m_unk1660 = -frame.m_right.z;
            break;
        case 1:
        case 4:
            m_unk1664 = 8;
            m_unk164c = frame.m_up.x;
            m_unk1650 = frame.m_up.y;
            m_unk1654 = frame.m_up.z;
            m_unk1658 = frame.m_right.x;
            m_unk165c = frame.m_right.y;
            m_unk1660 = frame.m_right.z;
            break;
        case 2:
            m_unk1664 = 7;
            m_unk164c = frame.m_right.x;
            m_unk1650 = frame.m_right.y;
            m_unk1654 = frame.m_right.z;
            m_unk1658 = -frame.m_up.x;
            m_unk165c = -frame.m_up.y;
            m_unk1660 = -frame.m_up.z;
            break;
        case 3:
            m_unk1664 = 6;
            m_unk164c = -frame.m_right.x;
            m_unk1650 = -frame.m_right.y;
            m_unk1654 = -frame.m_right.z;
            m_unk1658 = frame.m_up.x;
            m_unk165c = frame.m_up.y;
            m_unk1660 = frame.m_up.z;
            break;
        default:
            break;
    }
    if (m_unk1744 == 2) {
        m_unk1658 = kZero.x;
        m_unk1660 = kZero.z;
        m_unk165c = kZero.y;
    }
    *m_unk16e4 = Modelling(this);
    Mat4_SetBasisFromAtUp(m_unk16e8, &Modelling(this).m_up, &Modelling(this).m_at);  // 0x0023fd30
    Mat4_SetBasisFromAtRight(m_unk16ec, &Modelling(this).m_at, &Modelling(this).m_up);  // 0x0023fe58
    m_unk163c = 0.0f;
    m_unk127c = kZero.x;
    m_unk1284 = kZero.z;
    m_unk1280 = kZero.y;
}

// 0x00321080 CKHkS08Hero_ClassifyClimbZoneApproach_maybe: how the hero comes onto the zone (+0x1740): kind 1 (+0x1744) 9,
// kind 2 8, others 3; on a wall (0) the velocity's part in the attach's (at, right) plane: too slow (+0xcf8) 3, within
// +0xcf4 / 2 degrees of at 2, of -at 3, of right 4 / 5 or of -right 6 / 7 (the faster when at least +0xcf0), else 3.
uint32_t CKHkS08Hero::ClassifyClimbZoneApproach(const CVector3* at, const CVector3* right) {
    const uint32_t kind = m_unk1744;
    if (kind == 1) return 9;
    if (kind != 0) return kind == 2 ? 8 : 3;
    const float vx = m_unk127c;
    const float vy = m_unk1280;
    const float vz = m_unk1284;
    float fa = at->y * vy;
    float fb = right->y * vy;
    fa = ppc::fmadds(at->x, vx, fa);
    fb = ppc::fmadds(right->x, vx, fb);
    fa = ppc::fmadds(at->z, vz, fa);
    fb = ppc::fmadds(right->z, vz, fb);
    float py = ppc::fmadds(right->y, fb, ppc::fmadds(at->y, fa, kZero.y));
    float px = ppc::fmadds(right->x, fb, ppc::fmadds(at->x, fa, kZero.x));
    float pz = ppc::fmadds(right->z, fb, ppc::fmadds(at->z, fa, kZero.z));
    float length = std::sqrt(ppc::fmadds(pz, pz, ppc::fmadds(px, px, py * py)));
    if (length == 0.0f) {
        length = 0.0f;
    } else {
        const float inverse = 1.0f / length;
        pz = pz * inverse;
        px = px * inverse;
        py = py * inverse;
    }
    if (m_unkcf8 > length) return 3;
    const float half = 0.5f;               // TOC1 +0x258c
    const float degrees = 0.0174532905f;   // TOC1 +0x2594
    const float limit = (m_unkcf4 * half) * degrees;
    const float a1 = AcosClamped(ppc::fmadds(pz, at->z, ppc::fmadds(px, at->x, py * at->y)));
    if (limit > a1) return 2;
    const float a2 = AcosClamped(ppc::fmadds(pz, -at->z, ppc::fmsubs(py, -at->y, at->x * px)));
    if (limit > a2) return 3;
    const float side = ((180.0f - m_unkcf4) * half) * degrees;  // TOC1 +0x25a4
    const float a3 = AcosClamped(ppc::fmadds(pz, right->z, ppc::fmadds(px, right->x, py * right->y)));
    const uint32_t fast = m_unkcf0 > length ? 0u : 1u;
    if (side > a3) return 4 + fast;
    const float a4 = AcosClamped(ppc::fmadds(pz, -right->z, ppc::fmsubs(py, -right->y, right->x * px)));
    if (side <= a4) return 3;
    return 6 + fast;
}

// 0x00325c88 CKHkS08Hero_UpdateClimbLocomotion_maybe (once per frame, climbing with no climb holding the hero): airborne
// off the wall (+0x1625) or pushed (+0x1622) the camera locks; the leap's end starts its fall time (+0x1634 by the move);
// the move flags by the speed; a jump press (+0x358 bit 20) leaps (+0x1626) in the direction the stick classifies
// (+0x1664 0..4 against the cone +0xc28) for the move's time (+0x1630), and the push (+0x162c) when it runs out.
void CKHkS08Hero::UpdateClimbLocomotion(float dt) {
    const bool air = ((m_unk354 & 1u) != 0 && m_gcCurDatasInOut.m_fdH > 0.001f) || m_unk1622 != 0;  // TOC1 +0x25ec
    if (air) {
        m_unk1625 = 1;
        SetCameraDirectionLock(1);  // 0x00354cf0
        m_unk354 = (m_unk354 | 1u) & ~4u;
    } else {
        m_unk1625 = 0;
        if (m_unk1628 != 0) {
            m_unk1627 = 1;
            float fall = 0.0f;
            switch (m_unk1664) {
                case 0:
                case 5: fall = m_unkc3c; break;
                case 1:
                case 2:
                case 6:
                case 7: fall = m_unkc40; break;
                case 3: fall = m_unkc44; break;
                case 4:
                case 8: fall = m_unkc80; break;
                default: break;
            }
            m_unk1634 = fall;
            m_unk1628 = 0;
        }
    }
    if (!(m_unkcfc >= m_unk12d0) && m_unk161c != 0) {
        m_unk161c = 0;
        m_unk161f = 1;
    } else if (m_unkd00 > m_unk12d0 && m_unk161f != 0) {
        m_unk161c = 1;
        m_unk161f = 0;
    }
    float stick = m_unk1378;
    m_unk1621 = 0;
    if (stick == 0.0f && m_unk161f != 0) m_unk1621 = 1;
    if (m_unk1626 != 0) {
        m_unk1630 = m_unk1630 - dt;
        if (m_unk1630 == 0.0f) m_unk1630 = m_unk1630 - dt;
    } else {
        m_unk1630 = 0.0f;
    }
    m_unk1634 = m_unk1627 != 0 ? m_unk1634 - dt : 0.0f;
    m_unk1626 = 0;
    if ((m_unk358 & 0x100000u) != 0 && m_unk1625 == 0 && (m_unk354 & 0x800u) == 0 && (m_unk35c & 2u) == 0) {
        m_unk1626 = 1;
        m_unk1640[0] = m_unk37c;
        m_unk1640[1] = m_unk380;
        m_unk1640[2] = m_unk384;
        const float cone = m_unkc28;
        const float turn = m_unk1374;
        if (GameCosf(cone * 0.5f) >= turn) {  // TOC1 +0x258c
            if (GameCosf(ppc::fmadds(cone, -0.5f, 3.14159274101257324f)) > turn) {  // TOC1 +0x25a0 / +0x25c8
                m_unk1664 = 3;
            } else {
                float dot = m_unk380 * m_unk136c;
                dot = ppc::fmadds(m_unk37c, m_unk1368, dot);
                dot = ppc::fmadds(m_unk384, m_unk1370, dot);
                m_unk1664 = dot <= 0.0f ? 1 : 2;
            }
        } else {
            m_unk1664 = 0;
        }
        stick = m_unk1378;
        float time = 0.0f;
        if (stick == 0.0f) {
            m_unk1664 = 4;
            time = m_unkc7c;
        } else {
            switch (m_unk1664) {
                case 0: time = m_unkc30; break;
                case 1:
                case 2: time = m_unkc34; break;
                case 3: time = m_unkc38; break;
                case 4: time = m_unkc7c; break;
                case 5: time = m_unkca0; break;
                case 6:
                case 7: time = m_unkc90; break;
                case 8: time = m_unkcb0; break;
                default: break;
            }
        }
        m_unk1630 = time;
    }
    const float leap = m_unk1630;
    if (leap <= 0.0f) {
        m_unk1626 = 0;
    } else {
        m_unk1626 = 1;
    }
    m_unk1627 = m_unk1634 <= 0.0f ? 0 : 1;
    m_unk1623 = 0;
    if (leap < 0.0f && m_unk1625 == 0) {
        m_unk1622 = 1;
        m_unk1623 = 1;
        float push = 0.0f;
        switch (m_unk1664) {
            case 0: push = m_unkc04; break;
            case 1:
            case 2: push = m_unkc00; break;
            case 3: push = m_unkc08; break;
            case 4: push = m_unkc78; break;
            case 5: push = m_unk1744 == 2 ? m_unkcdc : m_unkc9c; break;
            case 6:
            case 7: push = m_unk1744 == 2 ? m_unkcd4 : m_unkc8c; break;
            case 8: push = m_unk1744 == 2 ? m_unkce4 : m_unkcac; break;
            default: break;
        }
        m_unk162c = push;
        m_unk1628 = 1;
        SetCameraDirectionLock(1);
        m_unk354 = (m_unk354 | 1u) & ~4u;
        stick = m_unk1378;
    }
    m_unk1620 = (m_unk161f != 0 || m_unk1622 != 0) ? 1 : m_unk1625;
    if (stick > 0.0f) m_unk1620 = 1;
    m_unk1678 = 0;
}

// 0x00325108 CKHkS08Hero_UpdateClimbSustainedLocomotion_maybe (once per frame, a climb holds the hero): the stick
// (+0x11a8, projected on the node's at / right on a ceiling or with +0x11c0) classified into +0x1665 (0 up, 1 down, 2 / 3
// the sides, 4 none) against the cone +0xc28; a jump press (+0x358 bit 20) mounted on a wall or ceiling starts a leap
// (+0x1626: the move +0x1664 5..8 and its time +0x1630, the snapshot matrices); a new leap within one (TryClimbLeap);
// the leap and fall flags; the push when the leap's time runs out (+0x1628: the hero leaves its zones).
void CKHkS08Hero::UpdateClimbSustainedLocomotion(float /*dt*/) {
    const uint32_t kind = m_unk1744;
    float along = m_unk11b0;
    float across = m_unk11a8;
    const float cone = m_unkc28;
    if (kind == 2 || m_unk11c0 != 0) {
        const CMatrix34& frame = Modelling(this);
        const float sy = m_unk11ac;
        const float aRight = ppc::fmadds(along, frame.m_right.z, ppc::fmadds(across, frame.m_right.x, sy * frame.m_right.y));
        const float aAt = ppc::fmadds(along, frame.m_at.z, ppc::fmadds(across, frame.m_at.x, sy * frame.m_at.y));
        across = aRight;
        along = aAt;
    }
    if (!(GameCosf(cone * 0.5f) >= along)) {  // TOC1 +0x258c; bge
        m_unk1665 = 0;
    } else if (!(GameCosf(ppc::fmadds(cone, -0.5f, 3.14159274101257324f)) <= along)) {  // ble
        m_unk1665 = 1;
    } else if (across <= 0.0f) {
        m_unk1665 = m_unk11c0 != 0 ? 3 : 4;
    } else {
        m_unk1665 = m_unk11c0 != 0 ? 2 : 4;
    }
    if (m_unk1378 == 0.0f) m_unk1665 = 4;
    if (kind == 2) {
        m_unk1658 = kZero.x;
        m_unk165c = kZero.y;
        m_unk1660 = kZero.z;
    }
    auto setMove = [this](uint8_t stickClass) {
        const CMatrix34& frame = Modelling(this);
        switch (stickClass) {
            case 1:
            case 4:
                m_unk1664 = 8;
                m_unk164c = frame.m_up.x;
                m_unk1650 = frame.m_up.y;
                m_unk1654 = frame.m_up.z;
                m_unk1658 = frame.m_right.x;
                m_unk165c = frame.m_right.y;
                m_unk1660 = frame.m_right.z;
                break;
            case 0:
                m_unk1664 = 5;
                m_unk164c = frame.m_at.x;
                m_unk1650 = frame.m_at.y;
                m_unk1654 = frame.m_at.z;
                m_unk1658 = -frame.m_right.x;
                m_unk165c = -frame.m_right.y;
                m_unk1660 = -frame.m_right.z;
                break;
            case 2:
                m_unk1664 = 7;
                m_unk164c = frame.m_right.x;
                m_unk1650 = frame.m_right.y;
                m_unk1654 = frame.m_right.z;
                m_unk1658 = -frame.m_up.x;
                m_unk165c = -frame.m_up.y;
                m_unk1660 = -frame.m_up.z;
                break;
            case 3:
                m_unk1664 = 6;
                m_unk164c = -frame.m_right.x;
                m_unk1650 = -frame.m_right.y;
                m_unk1654 = -frame.m_right.z;
                m_unk1658 = frame.m_up.x;
                m_unk165c = frame.m_up.y;
                m_unk1660 = frame.m_up.z;
                break;
            default:
                break;
        }
    };
    if (m_unk1626 != 0 && m_unk1665 != 4) setMove(m_unk1665);  // 4 (no stick) keeps the move here
    m_unk1626 = 0;
    if ((m_unk358 & 0x100000u) != 0 && m_unk1679 != 0 && m_unk1630 <= 0.0f && m_unk1628 == 0 && m_unk1627 == 0 &&
        (m_unk1744 == 0 || m_unk1744 == 2) && (m_unkecc & 0x20000u) == 0 && (m_unkec8 & 1u) == 0) {
        m_unk1658 = kZero.x;
        m_unk165c = kZero.y;
        m_unk1660 = kZero.z;
        if (m_unk1665 <= 4) setMove(m_unk1665);
        m_unk1626 = 1;
        float time = 0.0f;
        switch (m_unk1664) {
            case 0: time = m_unkc30; break;
            case 1:
            case 2: time = m_unkc34; break;
            case 3: time = m_unkc38; break;
            case 4: time = m_unkc7c; break;
            case 5: time = m_unkca0; break;
            case 6:
            case 7: time = m_unkc90; break;
            case 8: time = m_unkcb0; break;
            default: break;
        }
        m_unk1630 = time;
        m_unk178c = 0;
        if (m_unk1744 == 2) {
            m_unk178c = 1;
            m_unk1658 = kZero.x;
            m_unk165c = kZero.y;
            m_unk1660 = kZero.z;
        }
        *m_unk16e4 = Modelling(this);
        Mat4_SetBasisFromAtUp(m_unk16e8, &Modelling(this).m_up, &Modelling(this).m_at);  // 0x0023fd30
        Mat4_SetBasisFromAtRight(m_unk16ec, &Modelling(this).m_at, &Modelling(this).m_up);  // 0x0023fe58
        m_unk16ac = m_unk1694;  // the zone the leap starts from
    }
    TryClimbLeap();  // 0x0031db40
    const float leap = m_unk1630;
    if (leap <= 0.0f) {
        m_unk1626 = 0;
    } else {
        m_unk1284 = 0.0f;
        m_unk127c = 0.0f;
        m_unk1626 = 1;
    }
    if (m_unk1634 <= 0.0f) {
        m_unk1627 = 0;
    } else {
        m_unk1284 = 0.0f;
        m_unk127c = 0.0f;
        m_unk1627 = 1;
    }
    m_unk1623 = 0;
    if (leap < 0.0f || (m_unked0 & 0x20000000u) != 0) {
        m_unk1622 = 1;
        m_unk1623 = 1;
        float push = 0.0f;
        switch (m_unk1664) {
            case 0: push = m_unkc04; break;
            case 1:
            case 2: push = m_unkc00; break;
            case 3: push = m_unkc08; break;
            case 4: push = m_unkc78; break;
            case 5: push = m_unk1744 == 2 ? m_unkcdc : m_unkc9c; break;
            case 6:
            case 7: push = m_unk1744 == 2 ? m_unkcd4 : m_unkc8c; break;
            case 8: push = m_unk1744 == 2 ? m_unkce4 : m_unkcac; break;
            default: break;
        }
        m_unk162c = push;
        m_unk1628 = 1;
        const int32_t key = CKHkClimbZone::ClimberKey(this);
        if (m_unk1694 != nullptr) m_unk1694->RemoveClimber(key);  // 0x00457180
        if (m_unk16a4 != nullptr) m_unk16a4->RemoveClimber(key);
        if (m_unk16a8 != nullptr) m_unk16a8->RemoveClimber(key);
        m_unkecc &= 0xfffbffffu;
    }
    if (m_unk1628 != 0 && m_unk1ac4 != 0) m_unk1629 = 1;
    if ((m_unkec8 & 1u) == 0) {
        SetCameraDirectionLock(1);  // 0x00354cf0
        m_unk354 = (m_unk354 | 1u) & ~4u;
    }
}
