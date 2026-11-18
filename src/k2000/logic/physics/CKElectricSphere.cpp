// CKElectricSphere.cpp - reconstructed original translation unit 0x396748-0x39cf88 (GAME_TOC1, main_toc1), 28 functions, 28 live.
// Primary class: CKElectricSphere  key 0x964c  category Logic  size 0x334  vtable 0xb23888
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x396748  CKElectricSphere_Delete
//   [x] 0x396798  CKElectricSphere_GetAbilityId
//   [x] 0x3967a0  CKElectricSphere_GetFamilyId
//   [x] 0x3967a8  CKElectricSphere_GetFxSound_maybe
//   [x] 0x3968c8  CKElectricSphere_ApplyHeroControl
//   [x] 0x396998  CKElectricSphere_End
//   [x] 0x396a90  CKElectricSphere_ResetRuntime
//   [x] 0x396b58  CKElectricSphere_PostLoad
//   [x] 0x396bc0  CKElectricSphere_RecursiveRegistration  (inherited: CKTransformElement_RecursiveRegistration)
//   [x] 0x396be8  CKElectricSphere_Destroy  (inherited: CKTransformElement_Destroy)
//   [x] 0x396c10  CKElectricSphere_Construct
//   [x] 0x396c48  CKElectricSphere_DeleteArray
//   [x] 0x396ce8  CKElectricSphere_DeletingDestructor  (the destructor; delete)
//   [x] 0x396d30  CKElectricSphere_Destructor  (C++ destructor chain: vtable stores only)
//   [x] 0x396d60  CKElectricSphere_DestructBody  (C++ destructor chain: vtable stores only)
//   [ ] 0x396d90  RegisterCKElectricSphereClass
//   [ ] 0x396e18  _GLOBAL__D_396e18
//   [ ] 0x396e28  _GLOBAL__I_396e28
//   [x] 0x396e38  CKElectricSphere_Construct_2  (the same as CKElectricSphere_Construct)
//   [x] 0x396e70  CKElectricSphere_Start
//   [x] 0x397130  CKElectricSphere_StopFx
//   [x] 0x397240  CKElectricSphere_CreateArray
//   [x] 0x3972f0  CKElectricSphere_Create
//   [x] 0x397348  CKElectricSphere_Load
//   [ ] 0x398a48  CKElectricSphere_Save
//   [x] 0x39a0c0  CKElectricSphere_UpdateAttack_maybe
//   [x] 0x39a798  CKElectricSphere_UpdateEffect_maybe
//   [x] 0x39bd78  CKElectricSphere_SetFxActive
//
//   [ ] 0x9bfca0  CKElectricSphere_IsKindOfClass  [inline]
//   [ ] 0x9bfcf0  CKElectricSphere_GetClassType  [inline]
//   [ ] 0x9bfcf8  CKElectricSphere_GetClassID  [inline]
//   [x] 0x9bfd00  CKElectricSphere_StartEmitterFx  [inline]
#include "k2000/logic/physics/CKElectricSphere.h"

#include "k2000/io/IKFile.h"
#include "k2000/math/Math.h"
#include <cmath>
#include <cstring>
#include "Renderware/rwcore/RwCamera.h"
#include "Spyro2008/misc/CKS08AbilityHostBase.h"
#include "crt/ppc_ops.h"
#include "k2000/components/CKImpulsionCpnt.h"
#include "k2000/dictionaries/CKSoundDictionaryID.h"
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/fx/CKSparkFxData.h"
#include "k2000/fx/IKFx.h"
#include "k2000/logic/CKParticlesEffectFxData.h"
#include "k2000/logic/fx/CKAnimatedFxCollection.h"
#include "k2000/logic/fx/CKElectricArcNodeFx.h"
#include "k2000/logic/fx/CKExplosionNodeFx.h"
#include "k2000/logic/render/CKPointLightFxData.h"
#include "k2000/logic/sound/CKSound.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/scenegraph/CSGBranch.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/scenegraph/CSGLeaf.h"

// 0x00396a90 CKElectricSphere_ResetRuntime. Its stores in order; the arc slots +0x258..+0x264 in pairs.
void CKElectricSphere::ResetRuntime() {
    m_unk328 = nullptr;
    m_unk32c = nullptr;
    CKTransformElement::ResetRuntime();
    m_ui8HotSpot = 9;
    m_unk27c = nullptr;
    m_unk1e4 = nullptr;
    m_unk1e8 = nullptr;
    for (uint32_t i = 0; i < 4; i += 2) {
        m_unk258[i + 1] = nullptr;
        m_unk258[i] = nullptr;
    }
    m_unk29c = 1.0f;  // TOC +0x35f0
    m_unk330 = 0.0f;
    m_unk26c = nullptr;
    m_unk320 = 1;
    m_unk294 = 0.0f;
    m_unk298 = 0.0f;
    m_unk2a0 = 0;
    m_unk288 = nullptr;
    m_unk314 = 0;
    m_unk318 = 0.0f;
    m_unk31c = 0.0f;
    m_unk324 = 0;
}

namespace {
// 0x00010690 Math_Sqrtf
float Sqrtf(float x) { return static_cast<float>(std::sqrt(static_cast<double>(x))); }
// One Rand_Int draw, its low 16 bits as a float (clrldi 48, fcfid, frsp).
float RandUnit16() { return static_cast<float>(static_cast<double>(static_cast<uint32_t>(Rand_Int()) & 0xffffu)); }
constexpr float kRandMax = 65535.0f;          // TOC +0x3620
constexpr float kRandScale = -0x1.0001p-15f;  // TOC +0x3664 (0xb8000080)
// The next explosion's interval: 1 / (base + spread + spread x a draw in [-1, 1]) (one Rand_Int).
float NextInterval(float base, float spread) {
    const float both = base + spread;
    const float t = RandUnit16() / kRandMax * -2.0f;  // 0x00011500; TOC +0x3624
    return 1.0f / ppc::fmadds(t, spread, both);       // TOC +0x35f0
}
}  // namespace

// 0x003967a8 CKElectricSphere_GetFxSound_maybe
CKSound* CKElectricSphere::GetFxSound(uint32_t which) {
    CKSoundDictionaryID* sounds = static_cast<CKSoundDictionaryID*>(m_unk28c);
    auto usable = [sounds](uint32_t index) {
        return sounds->GetSound(index) != nullptr && sounds->GetSound(index)->GetSample() != nullptr;  // 0x00111000
    };
    if (which == 1) return sounds->GetSound(0);
    if (which != 3) return nullptr;
    if (m_levelIndex == 2 && usable(2)) return sounds->GetSound(2);
    if ((m_levelIndex == 1 || m_levelIndex == 2) && usable(1)) return sounds->GetSound(1);
    return nullptr;
}

// 0x003968c8 CKElectricSphere_ApplyHeroControl
void CKElectricSphere::ApplyHeroControl(uint8_t on) {
    CKTransformElement::ApplyHeroControl(on);
    const uint8_t allow = on != 0 ? 1 : 0;
    m_pHost->SetHeroActionPermission(3, allow, allow, allow);  // vt+0x44
}

// 0x00396998 CKElectricSphere_End
void CKElectricSphere::End(int32_t forced) {
    if (m_unk328 != nullptr) {
        static_cast<CKSound*>(m_unk328)->Stop(0);  // 0x001111b0
        m_unk328 = nullptr;
    }
    if (m_unk32c != nullptr) {
        static_cast<CKSound*>(m_unk32c)->Stop(0);
        m_unk32c = nullptr;
    }
    m_pHost->SetHero1d20(1.0f);  // vt+0x84; TOC +0x35f0
    CKTransformElement::End(forced);
    SceneNode_SetVisibleInLayer(static_cast<CSGLeaf*>(m_unk224), 1, 0, 0);  // 0x005832a8
    SceneNode_SetVisibleInLayer(static_cast<CSGLeaf*>(m_unk228), 1, 0, 0);
}

// 0x00396e70 CKElectricSphere_Start
void CKElectricSphere::Start(CKS08AbilityHostBase* host) {
    m_unk32c = nullptr;
    m_unk328 = nullptr;
    CKTransformElement::Start(host);
    CSGLeaf* sphere = static_cast<CSGLeaf*>(m_unk224);
    if (sphere != nullptr) {
        TransformFx::ShowNode(sphere);
        TransformFx::SetGeometriesAlpha(sphere, 0);
        CSGHotSpot* spot = static_cast<CSGHotSpot*>(m_pHost->GetHotspot(m_ui8HotSpot));  // vt+0xcc
        if (spot->m_pParent != sphere->m_pParent) {
            if (sphere->m_pParent != nullptr) sphere->m_pParent->RemoveChild(sphere);  // vt+0x78
            static_cast<CSGHotSpot*>(m_pHost->GetHotspot(m_ui8HotSpot))->AttachVolume(sphere);  // 0x000ce2b8
        }
    }
    CKImpulsionCpnt* dash = static_cast<CKImpulsionCpnt*>(m_unk18c);
    dash->m_unk2c = 0.0f;
    dash->m_unk24 = 0.0f;
    dash->m_unk28 = 0.0f;
    const uint32_t level = static_cast<uint32_t>(m_levelIndex);
    m_unk2a0 = 0;
    m_unk29c = 1.0f;
    m_unk324 = 0;
    m_unk314 = 0;
    m_unk294 = m_unk160[level] * 0.5f;  // TOC +0x361c
    m_unk330 = NextInterval(m_unk20c[level], m_unk218[level]);
}

// 0x00397130 CKElectricSphere_StopFx
void CKElectricSphere::StopFx() {
    CKTransformElement::StopFx();
    m_unk298 = m_unk294;
    if (m_unk224 != nullptr) TransformFx::HideNode(m_unk224);
    if (m_unk228 != nullptr) TransformFx::HideNode(m_unk228);
    m_pHost->SetAbilityAttackSpheres(this, 0, 1.0f, nullptr, 1.0f, nullptr);  // vt+0xfc
    m_pHost->SetHero1d20(1.0f);                                                // vt+0x84
}

// 0x0039a0c0 CKElectricSphere_UpdateAttack_maybe
void CKElectricSphere::UpdateAttack(float dt) {
    if (m_levelIndex == 0) return;
    CKImpulsionCpnt* dash = static_cast<CKImpulsionCpnt*>(m_unk18c);
    if (m_pHost->IsAbilityButtonDown(3) != 0) {  // vt+0x8c
        dash->Impulse(1.0f);                       // 0x0024bce0
        m_unk314 = m_unk22c;  // the burst's time
        m_unk320 = 1;
        CSGLeaf* burst = static_cast<CSGLeaf*>(m_unk228);
        if (burst != nullptr) {
            // The burst node hung under the hot spot, turned by a random angle about a random axis, its two timers drawn.
            if (burst->m_pParent != nullptr) burst->m_pParent->RemoveChild(burst);               // vt+0x78
            static_cast<CSGHotSpot*>(m_pHost->GetHotspot(m_ui8HotSpot))->AttachVolume(burst);  // 0x000ce2b8
            burst->ForceWorldMatrixUpdate();                                                     // vt+0x50
            CVector3 axis;
            axis.x = ppc::fmadds(RandUnit16(), kRandScale, 1.0f);  // 0x00011500
            axis.y = ppc::fmadds(RandUnit16(), kRandScale, 1.0f);
            const float xy = ppc::fmadds(axis.x, axis.x, axis.y * axis.y);
            axis.z = ppc::fmadds(RandUnit16(), kRandScale, 1.0f);
            const float length = Sqrtf(ppc::fmadds(axis.z, axis.z, xy));  // 0x00010690
            if (length != 0.0f) {
                const float inverse = 1.0f / length;
                axis.z = axis.z * inverse;
                axis.x = axis.x * inverse;
                axis.y = axis.y * inverse;
            }
            CSGMovable* movable = static_cast<CSGMovable*>(static_cast<IKSerializable*>(burst));
            const CVector3* point = reinterpret_cast<const CVector3*>(&movable->m_pRwFrame->modelling.pos);  // frame +0x40
            const float degrees = RandUnit16() / kRandMax * 360.0f;  // TOC +0x3668
            movable->RotateAboutPoint(degrees, point, &axis);       // 0x000d0f80 (the frame's own position)
            const float baseA = m_unk230 + m_unk234;
            m_unk318 = ppc::fmadds(RandUnit16() / kRandMax * -2.0f, m_unk234, baseA);
            const float baseB = m_unk238 + m_unk23c;
            m_unk31c = ppc::fmadds(RandUnit16() / kRandMax * -2.0f, m_unk23c, baseB);
        }
        if (m_levelIndex == 2) {
            CKExplosionNodeFx* fx = static_cast<CKExplosionNodeFx*>(TransformFx::Acquire(m_unk200[2], this));
            if (fx != nullptr) {
                const CVector3 position = m_pHost->GetHotspotPosition(m_ui8HotSpot);  // vt+0xd0
                fx->SetTranslation(&position, this);  // 0x001b66e8
                fx->Trigger(this, 0);                 // 0x001b82a8
                fx->ReleaseReservation(this);         // vt+0x54
                const uint32_t level = static_cast<uint32_t>(m_levelIndex);
                m_unk330 = NextInterval(m_unk20c[level], m_unk218[level]);
            }
        }
    }
    dash->Update(dt);  // 0x0024bd40
    m_unk29c = dash->m_unk24;
    m_pHost->SetHero1d20(m_unk29c);  // vt+0x84
}

namespace {
constexpr float kArcReachGrowth = 0.1f;    // TOC +0x367c
constexpr float kArcReachShrink = -0.1f;   // TOC +0x3680
constexpr float kDashTopMargin = 0.05f;    // TOC +0x3678

// UpdateEffect's running arc in slot `k` (inlined, 0x0039adf4): both of its points turned about the user's up by
// dt x the arc's speed around the hot spot, flat (y 0) offsets. The end point's reach varies by +/-10 % (one Rand_Int)
// and it keeps its height (the original stores the new y, then the old one over it). The start point's direction takes
// the old start point's absolute y as its y (not the turned vector's): kept as the original computes it.
void TurnArc(CKElectricSphere* self, uint32_t k, float dt, float sphereScale) {
    CKS08AbilityHostBase* host = self->m_pHost;
    const CVector3 spot = host->GetHotspotPosition(self->m_ui8HotSpot);  // vt+0xd0
    CVector3& end = self->m_unk2e4[k];
    CVector3& start = self->m_unk2a4[k];
    CVector3 offset;
    offset.x = end.x - spot.x;
    offset.z = end.z - spot.z;
    const float reach = Sqrtf(ppc::fmadds(offset.z, offset.z, ppc::fmadds(offset.x, offset.x, 0.0f)));  // 0x00010690
    offset.y = 0.0f;
    CVector3 up = host->GetOwnerUp();  // vt+0x2c
    CVector3 turned;
    Vec3_RotateTowardByAngle(&turned, &offset, &up, dt * self->m_unk2d4[k]);  // 0x005841a8 (bridge 0x0098f300)
    const float grown = ppc::fmadds(reach, kArcReachGrowth, reach);
    float draw = RandUnit16() / kRandMax;  // 0x00011500
    draw = draw + draw;
    const float newReach = ppc::fmadds(reach * draw, kArcReachShrink, grown);
    end.z = ppc::fmadds(turned.z, newReach, spot.z);
    end.x = ppc::fmadds(turned.x, newReach, spot.x);
    // end.y: the original writes fmadds(turned.y, newReach, spot.y), then the y read before it back over it.
    CVector3 startOffset;
    startOffset.x = start.x - spot.x;
    startOffset.y = 0.0f;
    startOffset.z = start.z - spot.z;
    CVector3 up2 = host->GetOwnerUp();  // vt+0x2c
    CVector3 turned2;
    Vec3_RotateTowardByAngle(&turned2, &startOffset, &up2, dt * self->m_unk2d4[k]);
    float dy = start.y;
    float dx = turned2.x;
    float dz = turned2.z;
    const float length = Sqrtf(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));
    if (length != 0.0f) {
        const float inverse = 1.0f / length;
        dz = dz * inverse;
        dx = dx * inverse;
        dy = dy * inverse;
    }
    const float radius = sphereScale * self->m_unk17c;
    start.z = ppc::fmadds(radius, dz, spot.z);
    start.x = ppc::fmadds(dx, radius, spot.x);
    start.y = ppc::fmadds(dy, radius, spot.y);
    CKElectricArcNodeFx* arc = static_cast<CKElectricArcNodeFx*>(self->m_unk258[k]);
    arc->SetStartPoint(&start, self);  // 0x001b1f80
    arc->SetEndPoint(&end, self);      // 0x001b1f40
}

// UpdateEffect's new arc in slot `k` (inlined, 0x0039b448): six Rand_Int draws. The start point on a sphere of
// sphereScale x +0x17c about the hot spot (a random flat direction, a random height +0x1a8 / +0x1b4), the end point a
// random reach (+0x1c0 / +0x1cc) from the user's ground point along the start's flat direction, the turn speed a
// random sign times a random speed (+0x190 / +0x19c) over the end offset's length.
void SpawnArc(CKElectricSphere* self, uint32_t k, uint32_t level, float sphereScale) {
    CKS08AbilityHostBase* host = self->m_pHost;
    const CVector3 spot = host->GetHotspotPosition(self->m_ui8HotSpot);  // vt+0xd0
    float dx = ppc::fmadds(RandUnit16(), kRandScale, 1.0f);  // 0x00011500
    float dz = ppc::fmadds(RandUnit16(), kRandScale, 1.0f);
    float dxx = dx * dx;
    float dzz = dz * dz;
    const float flat = Sqrtf((dxx + 0.0f) + dzz);
    if (flat != 0.0f) {
        const float inverse = 1.0f / flat;
        dz = dz * inverse;
        dx = dx * inverse;
        dzz = dz * dz;
        dxx = dx * dx;
    }
    const float heightBase = self->m_unk1a8[level] + self->m_unk1b4[level];
    float dy = ppc::fmadds(RandUnit16() / kRandMax * -2.0f, self->m_unk1b4[level], heightBase);  // TOC +0x3624
    const float length = Sqrtf(ppc::fmadds(dy, dy, dxx) + dzz);
    if (length != 0.0f) {
        const float inverse = 1.0f / length;
        dz = dz * inverse;
        dx = dx * inverse;
        dy = dy * inverse;
    }
    float radius = sphereScale * self->m_unk17c;
    dx = dx * radius;
    dz = dz * radius;
    CVector3 start;
    start.y = ppc::fmadds(dy, radius, spot.y);
    start.x = dx + spot.x;
    start.z = dz + spot.z;
    const CVector3 ground = host->GetOwnerGroundPoint();  // vt+0x14
    float ey = 0.0f;
    const float flat2 = Sqrtf(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, 0.0f)));
    if (flat2 != 0.0f) {
        const float inverse = 1.0f / flat2;
        dz = dz * inverse;
        dx = dx * inverse;
        ey = inverse * 0.0f;
    }
    const float reachBase = self->m_unk1c0[level] + self->m_unk1cc[level];
    const float reach = ppc::fmadds(RandUnit16() / kRandMax * -2.0f, self->m_unk1cc[level], reachBase);
    dz = dz * reach;
    dx = dx * reach;
    ey = ey * reach;
    CVector3 end;
    end.z = dz + ground.z;
    end.x = dx + ground.x;
    end.y = ey + ground.y;
    const float xy = ppc::fmadds(dx, dx, ey * ey);
    CKElectricArcNodeFx* arc = static_cast<CKElectricArcNodeFx*>(self->m_unk258[k]);
    arc->SetStartPoint(&start, self);  // 0x001b1f80
    arc->SetEndPoint(&end, self);      // 0x001b1f40
    self->m_unk2a4[k] = start;
    self->m_unk2e4[k] = end;
    float sign = ppc::fmadds(RandUnit16(), kRandScale, 1.0f);
    const float speedBase = self->m_unk190[level] + self->m_unk19c[level];
    const float draw = RandUnit16();
    const float offsetLength = ppc::fmadds(dz, dz, xy);
    sign = sign / std::fabs(sign);
    const float speed = sign * ppc::fmadds(draw / kRandMax * -2.0f, self->m_unk19c[level], speedBase);
    self->m_unk2d4[k] = speed / Sqrtf(offsetLength);
}
}  // namespace

// 0x0039a798 CKElectricSphere_UpdateEffect_maybe. `dt` scaled by the dash value (+0x29c) runs the pulse and the timed
// explosion; the burst, the dash explosion, the collection and the arcs' turns take `dt` itself.
void CKElectricSphere::UpdateEffect(float dt) {
    const uint32_t level = static_cast<uint32_t>(m_levelIndex);
    // The pulse: the attack sphere is on for the one frame after the clock passes the period.
    if (m_unk2a0 != 0) {
        m_pHost->SetAbilityAttackSpheres(this, 0, 1.0f, nullptr, 1.0f, nullptr);  // vt+0xfc
        m_unk2a0 = 0;
    }
    const float scaled = dt * m_unk29c;
    const float period = m_unk160[level];
    m_unk294 = scaled + m_unk294;
    if (period <= m_unk294) {  // cror lt|eq: not on NaN
        ApplyDamageParams(0);  // vt+0x88
        m_pHost->SetAbilityAttackSpheres(this, 1, m_unk154[level], m_elementDamage, 1.0f, nullptr);  // vt+0xfc
        m_unk2a0 = 1;
        m_unk294 = m_unk294 - period;
    }
    // The dash sound's pitch: 1 up to +0x290 as the dash value goes from the dash's lowest to its top value.
    if (m_unk32c != nullptr) {
        const CKImpulsionCpnt* dash = static_cast<const CKImpulsionCpnt*>(m_unk18c);
        const float low = dash->m_unk04[1];
        float t = (m_unk29c - low) / (dash->m_unk04[0] - low);
        if (t <= 0.0f) {
            t = 0.0f;
        } else if (t >= 1.0f) {
            t = 1.0f;
        }
        static_cast<CKSound*>(m_unk32c)->SetPitch(ppc::fmadds(t, m_unk290 - 1.0f, 1.0f));  // 0x00110ea0
    }
    // The sphere node: a random scale around +0x180, the alpha up to +0x16c at the period's ends, 0 at its middle.
    float sphereScale = m_unk180[level];
    if (m_unk224 != nullptr) {
        const float half = period * 0.5f;  // TOC +0x361c
        const float clock = m_unk294;
        const float t = !(clock > half) ? (half - clock) / half : ppc::fmadds(period, -0.5f, clock) / half;  // TOC +0x3674
        const float spread = m_unk178 + 1.0f;
        sphereScale = sphereScale * ppc::fmadds(RandUnit16() / kRandMax * -2.0f, m_unk178, spread);  // 0x00011500
        CSGMovable* sphere = static_cast<CSGMovable*>(m_unk224);
        sphere->SetIdentity();                                     // 0x000d08f0
        sphere->ScaleXYZ(sphereScale, sphereScale, sphereScale);  // 0x000d0d28
        const uint8_t alpha = static_cast<uint8_t>(ppc::fctiwz(t * static_cast<float>(m_unk16c[level])));
        TransformFx::SetGeometriesAlpha(m_unk224, alpha);
    }
    // The arcs: slot 2 x pass + i for the data i below the level, two passes.
    if (m_bLoop != 0 && m_unk29c > m_unk1d8) {
        for (uint32_t pass = 0; pass < 2; ++pass) {
            for (uint32_t i = 0; static_cast<uint32_t>(m_levelIndex) > i; ++i) {
                if (i == 2) continue;
                const uint32_t k = pass * 2 + i;
                IKFx* arc = static_cast<IKFx*>(m_unk258[k]);
                if (arc != nullptr) {
                    if ((arc->m_baFxData & 1u) == 0) {  // still playing
                        TurnArc(this, k, dt, sphereScale);
                        continue;
                    }
                    arc->StopAndRelease(this);  // vt+0x58
                    m_unk258[k] = nullptr;
                }
                m_unk258[k] = TransformFx::Acquire(m_unk24c[i], this);
                if (m_unk258[k] == nullptr) continue;
                SpawnArc(this, k, level, sphereScale);
            }
        }
    }
    // The burst node: while its time runs it flickers (shown at its grown scale every other frame).
    CSGLeaf* burst = static_cast<CSGLeaf*>(m_unk228);
    if (burst != nullptr) {
        if (!(m_unk314 > 0.0f)) {
            TransformFx::HideNode(burst);
        } else {
            if (TransformFx::IsNodeHidden(burst) != 0) {
                const float from = m_unk318;
                const float slope = (m_unk31c - from) / m_unk22c;
                float scale = ppc::fmadds(m_unk22c - m_unk314, slope, from) * m_unk240[level];
                const RwV3d& at = burst->m_pRwFrame->modelling.at;  // the current scale (frame +0x30)
                scale = scale / Sqrtf(ppc::fmadds(at.z, at.z, ppc::fmadds(at.x, at.x, at.y * at.y)));
                burst->ScaleXYZ(scale, scale, scale);  // 0x000d0d28
                TransformFx::ShowNode(burst);
            } else {
                TransformFx::HideNode(burst);
            }
            m_unk314 = m_unk314 - dt;
        }
    }
    // Level 2: held near the dash's top value for +0x1f8, the dash explosion (+0x1f4) and the dash stopped.
    CKImpulsionCpnt* dash = static_cast<CKImpulsionCpnt*>(m_unk18c);
    if (m_unk29c >= dash->m_unk04[0] - kDashTopMargin && m_levelIndex == 2) {
        m_unk324 = dt + m_unk324;
        if (m_unk1f8 <= m_unk324) {
            CKExplosionNodeFx* fx = static_cast<CKExplosionNodeFx*>(TransformFx::Acquire(m_unk1f4, this));
            if (fx != nullptr) {
                fx->SetDamageOwner(m_pHost->GetOwner(), this);              // vt+0x08; 0x001b6340
                fx->SetDamageCategory(m_pHost->GetCollisionGroup(), this);  // vt+0xb0; 0x001b6318
                fx->SetDamageFlags(m_pHost->GetCollisionMask(), this);      // vt+0xb4; 0x001b62f0
                fx->SetDamage(m_unk1fc, this);                              // 0x001b62c8
                const CVector3 position = m_pHost->GetOwnerPosition();      // vt+0x10
                fx->SetTranslation(&position, this);  // 0x001b66e8
                fx->Trigger(this, 0);                 // 0x001b82a8
                fx->ReleaseReservation(this);         // vt+0x54
                dash->m_unk2c = 0.0f;
                dash->m_unk24 = 0.0f;
                dash->m_unk28 = 0.0f;
                m_unk324 = 0.0f;
            }
        }
    } else {
        m_unk324 = 0.0f;
    }
    if (m_unk288 != nullptr) static_cast<CKAnimatedFxCollection*>(m_unk288)->Update(dt);  // 0x005cccb0 (bridge 0x0098f4b0)
    // The timed explosion at the hot spot, then the next interval (one Rand_Int).
    m_unk330 = m_unk330 - scaled;
    if (m_unk330 <= 0.0f) {
        CKExplosionNodeFx* fx = static_cast<CKExplosionNodeFx*>(TransformFx::Acquire(m_unk200[level], this));
        if (fx == nullptr) return;
        const CVector3 position = m_pHost->GetHotspotPosition(m_ui8HotSpot);  // vt+0xd0
        fx->SetTranslation(&position, this);  // 0x001b66e8
        fx->Trigger(this, 0);                 // 0x001b82a8
        fx->ReleaseReservation(this);         // vt+0x54
        m_unk330 = NextInterval(m_unk20c[level], m_unk218[level]);
    }
}

namespace {
// A pooled explosion at the user's position (host vt+0x10, read once the effect is found).
void ExplodeAtOwner(IKSerializable* data, const IKSerializable* owner, CKS08AbilityHostBase* host) {
    CKExplosionNodeFx* fx = static_cast<CKExplosionNodeFx*>(TransformFx::Acquire(data, owner));
    if (fx == nullptr) return;
    const CVector3 position = host->GetOwnerPosition();
    fx->SetTranslation(&position, owner);  // 0x001b66e8
    fx->Trigger(owner, 0);                 // 0x001b82a8
    fx->ReleaseReservation(owner);         // vt+0x54
}
}  // namespace

// 0x0039bd78 CKElectricSphere_SetFxActive
void CKElectricSphere::SetFxActive(int32_t on) {
    if (on != 0) {
        if (m_levelIndex != 0) {
            CKParticlesEffectFxData* loop = static_cast<CKParticlesEffectFxData*>(m_unk268);
            loop->m_pAttachHotSpot = m_pHost->GetHotspot(m_ui8HotSpot);  // vt+0xcc
            loop->m_pAttachOwner = nullptr;
            m_unk26c = TransformFx::Acquire(m_unk268, this);
        }
        ExplodeAtOwner(m_unk1ec, this, m_pHost);
        for (uint32_t i = 0; i < 2; ++i) {
            IKSerializable* data = i == 0 ? m_unk1dc : m_unk1e0;
            CKSparkFxData* spark = static_cast<CKSparkFxData*>(data);
            spark->m_unk10 = m_pHost->GetHotspot(2);
            spark->m_unk0c = nullptr;
            IKFx* fx = TransformFx::Acquire(data, this);
            if (i == 0) {
                m_unk1e4 = fx;
            } else {
                m_unk1e8 = fx;
            }
        }
        if (m_levelIndex == 1 || m_levelIndex == 2) {
            IKSerializable* collection = m_levelIndex == 1 ? m_unk280 : m_unk284;
            m_unk288 = collection;
            CSGLeaf* node = TransformFx::OwnerNode(m_pHost);
            SAnimatedFxRig* rigs = TransformFx::AttachmentSets(m_pHost);
            static_cast<CKAnimatedFxCollection*>(collection)->Play(
                node, rigs, static_cast<CSGHotSpot*>(m_pHost->GetHotspot(m_ui8HotSpot)));  // 0x005cc528
        }
        CKPointLightFxData* light = static_cast<CKPointLightFxData*>(m_unk270[m_levelIndex]);
        light->m_pAttachHotSpot = m_pHost->GetHotspot(m_ui8HotSpot);
        light->m_pAttachNode = nullptr;
        m_unk27c = TransformFx::Acquire(m_unk270[m_levelIndex], this);
        CKSound* loopSound = GetFxSound(1);
        m_unk328 = loopSound;
        if (loopSound != nullptr) {
            loopSound->SetAttachObject(TransformFx::OwnerNode(m_pHost));  // 0x00111350
            loopSound->Play(0.0f);                                       // 0x00111230
        }
        CKSound* dashSound = GetFxSound(3);
        m_unk32c = dashSound;
        if (dashSound != nullptr) {
            dashSound->SetAttachObject(TransformFx::OwnerNode(m_pHost));
            dashSound->SetPitch(1.0f);  // 0x00110ea0
            dashSound->Play(0.0f);
        }
        return;
    }
    if (m_unk26c != nullptr) {
        TransformFx::ReleaseParticles(&m_unk26c, this);
        ExplodeAtOwner(m_unk1f0, this, m_pHost);
    }
    TransformFx::ReleaseSpark(&m_unk1e4, this);
    TransformFx::ReleaseSpark(&m_unk1e8, this);
    for (uint32_t i = 0; i < 4; i += 2) {
        for (uint32_t k = i; k < i + 2; ++k) {
            if (m_unk258[k] == nullptr) continue;
            static_cast<IKFx*>(m_unk258[k])->StopAndRelease(this);  // vt+0x58
            m_unk258[k] = nullptr;
        }
    }
    if (m_unk288 != nullptr) {
        static_cast<CKAnimatedFxCollection*>(m_unk288)->Stop();  // 0x005cc990
        m_unk288 = nullptr;
    }
    if (m_unk27c != nullptr) {
        static_cast<IKFx*>(m_unk27c)->StopAndRelease(this);  // vt+0x58
        m_unk27c = nullptr;
    }
    if (m_unk328 != nullptr) {
        static_cast<CKSound*>(m_unk328)->Stop(0);  // 0x001111b0
        m_unk328 = nullptr;
    }
    if (m_unk32c != nullptr) {
        static_cast<CKSound*>(m_unk32c)->Stop(0);
        m_unk32c = nullptr;
    }
}

// 0x00396b58 CKElectricSphere_PostLoad
int32_t CKElectricSphere::PostLoad(int32_t type) {
    CKTransformElement::PostLoad(type);
    SceneNode_SetVisibleInLayer(static_cast<CSGLeaf*>(m_unk224), 1, 0, 0);  // 0x005832a8
    SceneNode_SetVisibleInLayer(static_cast<CSGLeaf*>(m_unk228), 1, 0, 0);
    return 1;
}

// 0x00397348 CKElectricSphere_Load: CKTransformElement's data, then (level data only, type K_LEVEL_PLATEFORMS) 284
// bytes of references and words (570 bytes in all).
int32_t CKElectricSphere::Load(IKFile* file, int32_t type) {
    CKTransformElement::Load(file, type);
    if (type == 0) {
        IKFile_ReadRef(file, &m_unk1ec);
        IKFile_ReadRef(file, &m_unk1f0);
        IKFile_ReadRef(file, &m_unk1dc);
        IKFile_ReadRef(file, &m_unk1e0);
        IKFile_ReadRef(file, &m_unk224);
        IKFile_ReadRef(file, &m_unk18c);
        for (uint32_t level = 0; level < 3; ++level) {
            ReadF32LE(file, &m_unk154[level]);
            ReadF32LE(file, &m_unk160[level]);
            ReadS32LE(file, &m_unk16c[level]);
        }
        ReadF32LE(file, &m_unk178);
        IKFile_ReadRef(file, &m_unk24c[0]);
        IKFile_ReadRef(file, &m_unk24c[1]);
        IKFile_ReadRef(file, &m_unk24c[2]);
        for (uint32_t level = 0; level < 3; ++level) {
            ReadF32LE(file, &m_unk190[level]);
            ReadF32LE(file, &m_unk19c[level]);
            ReadF32LE(file, &m_unk1a8[level]);
            ReadF32LE(file, &m_unk1b4[level]);
            ReadF32LE(file, &m_unk1c0[level]);
            ReadF32LE(file, &m_unk1cc[level]);
        }
        ReadF32LE(file, &m_unk1d8);
        ReadF32LE(file, &m_unk17c);
        IKFile_ReadRef(file, &m_unk280);
        IKFile_ReadRef(file, &m_unk284);
        IKFile_ReadRef(file, &m_unk268);
        IKFile_ReadRef(file, &m_unk228);
        ReadF32LE(file, &m_unk22c);
        ReadF32LE(file, &m_unk230);
        ReadF32LE(file, &m_unk234);
        ReadF32LE(file, &m_unk238);
        ReadF32LE(file, &m_unk23c);
        IKFile_ReadRef(file, &m_unk1f4);
        ReadF32LE(file, &m_unk1f8);
        for (uint32_t level = 0; level < 3; ++level) {
            ReadF32LE(file, &m_unk180[level]);
            ReadF32LE(file, &m_unk240[level]);
        }
        IKFile_ReadRef(file, &m_unk28c);
        ReadF32LE(file, &m_unk290);
        IKFile_ReadRef(file, &m_unk1fc);
        IKFile_ReadRef(file, &m_unk270[0]);
        IKFile_ReadRef(file, &m_unk270[1]);
        IKFile_ReadRef(file, &m_unk270[2]);
        IKFile_ReadRef(file, &m_unk200[0]);
        IKFile_ReadRef(file, &m_unk200[1]);
        IKFile_ReadRef(file, &m_unk200[2]);
        ReadF32LE(file, &m_unk20c[0]);
        ReadF32LE(file, &m_unk218[0]);
        ReadF32LE(file, &m_unk20c[1]);
        ReadF32LE(file, &m_unk218[1]);
        ReadF32LE(file, &m_unk20c[2]);
        ReadF32LE(file, &m_unk218[2]);
    }
    return 1;
}
