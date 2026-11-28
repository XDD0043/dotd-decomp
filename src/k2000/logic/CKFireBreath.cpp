// CKFireBreath.cpp - reconstructed original translation unit 0x3a3240-0x3a5e60 (GAME_TOC1, main_toc1), 22 functions, 22 live.
// Primary class: CKFireBreath  key 0x924c  category Logic  size 0x1f0  vtable 0xb23a48
// Other owners: UpdateFireBreathEffects (1), SetFireBreathEffectsActive (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x3a3240  CKFireBreath_End
//   [x] 0x3a32b8  CKFireBreath_Start
//   [x] 0x3a32e8  CKFireBreath_PostLoad  (= the inherited slot)
//   [x] 0x3a3310  CKFireBreath_RecursiveRegistration  (inherited: CKBreathElement_RecursiveRegistration)
//   [x] 0x3a3338  CKFireBreath_Destroy  (inherited: CKBreathElement_Destroy)
//   [x] 0x3a3360  CKFireBreath_DeletingDestructor  (C++ destructor chain: vtable stores, CKBreathElement_DestructBody)
//   [x] 0x3a33a8  CKFireBreath_Destructor  (C++ destructor chain: vtable stores only)
//   [x] 0x3a33d8  CKFireBreath_DestructBody  (C++ destructor chain: vtable stores, CKBreathElement_DestructBody)
//   [x] 0x3a3408  CKFireBreath_Construct
//   [x] 0x3a3440  CKFireBreath_Construct_2  (the same as 0x3a3408 CKFireBreath_Construct)
//   [x] 0x3a3478  CKFireBreath_DeleteArray
//   [ ] 0x3a3520  RegisterCKFireBreathClass
//   [ ] 0x3a35a8  _GLOBAL__D_3a35a8
//   [ ] 0x3a35b8  _GLOBAL__I_3a35b8
//   [x] 0x3a35c8  CKFireBreath_GetEmitterPosition
//   [x] 0x3a3720  UpdateFireBreathEffects
//   [x] 0x3a3d88  CKFireBreath_CreateArray
//   [x] 0x3a3e40  CKFireBreath_Create
//   [x] 0x3a3e98  CKFireBreath_ConfigureSparkNode_maybe
//   [x] 0x3a4288  CKFireBreath_Load
//   [ ] 0x3a4ba8  CKFireBreath_Save
//   [x] 0x3a5498  SetFireBreathEffectsActive
//
//   [ ] 0x9bfe38  CKFireBreath_IsKindOfClass  [inline]
//   [ ] 0x9bfe88  CKFireBreath_GetClassType  [inline]
//   [ ] 0x9bfe90  CKFireBreath_GetClassID  [inline]
//   [x] 0x9bfe98  CKFireBreath_StartEmitterFx  [inline]
//   [x] 0x3a3090  CKFireBreath_GetAbilityId (in the header)
//   [x] 0x3a3098  CKFireBreath_GetSound_maybe
//   [x] 0x3a31e0  ResetFireBreathRuntimeEffects
#include "k2000/logic/CKFireBreath.h"

#include <cmath>
#include <cstring>

#include "Renderware/rwcore/RwCamera.h"
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "Spyro2008/misc/CKS08HeroAbilityHost.h"
#include "crt/ppc_ops.h"
#include "crt/xatan.h"
#include "crt/xsinf.h"
#include "k2000/dictionaries/CKSoundDictionaryID.h"
#include "k2000/fx/CKSparkFxData.h"
#include "k2000/fx/IKFx.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKParticlesEffectFxData.h"
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/logic/fx/CKAnimatedFx.h"
#include "k2000/logic/fx/CKAnimatedFxCollection.h"
#include "k2000/logic/fx/CKParticlesEffectNodeFx.h"
#include "k2000/logic/fx/CKSparkNodeFx.h"
#include "k2000/logic/render/CKPointLightFxData.h"
#include "k2000/logic/sound/CKSound.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/Mat4.h"
#include "k2000/scenegraph/CParticlesNodeFx.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/services/CKSrvCollision.h"
#include "k2000/services/CKSrvFx.h"
#include "k2000/services/CollisionDatas.h"

namespace {
CKSrvFx* FxService() { return static_cast<CKSrvFx*>(g_pEngine->m_srvFx); }
constexpr CVector3 kNullVector{0.0f, 0.0f, 0.0f};  // 0x00c50d64
constexpr CVector3 kAxisY{0.0f, 1.0f, 0.0f};       // 0x00c50d40 (TOC +0x3814)
bool SignBitSet(float x) {
    int32_t bits;
    std::memcpy(&bits, &x, sizeof(bits));
    return bits < 0;
}
// The inlined sinf / cosf: the single-precision polynomials for a non-negative argument (by its sign bit), the library's
// 0x009a1390 / 0x009a11d8 of the magnitude otherwise (the sine negated).
float GameSinf(float x) { return SignBitSet(x) ? -crt::LibSinf(-x) : crt::InlineSinf(x); }
float GameCosf(float x) { return SignBitSet(x) ? crt::LibCosf(-x) : crt::InlineCosf(x); }
// 0x00010690 Math_Sqrtf
float Sqrtf(float x) { return static_cast<float>(std::sqrt(static_cast<double>(x))); }
}  // namespace

// 0x003a4288 CKFireBreath_Load: CKBreathElement's data, then (level data only) 0x60 bytes: a reference, ten
// words, ten references and three words.
int32_t CKFireBreath::Load(IKFile* file, int32_t type) {
    CKBreathElement::Load(file, type);
    if (type == 0) {
        IKFile_ReadRef(file, &m_pSparkFxData);
        for (int32_t i = 0; i < 10; ++i) ReadF32LE(file, &m_unk178[i]);
        IKFile_ReadRef(file, &m_pAnimFxLevel1);
        IKFile_ReadRef(file, &m_pAnimFxLevel2);
        IKFile_ReadRef(file, &m_pSoundDico);
        IKFile_ReadRef(file, &m_apParticlesFxData[0]);
        IKFile_ReadRef(file, &m_apParticlesFxData[1]);
        IKFile_ReadRef(file, &m_apParticlesFxData[2]);
        IKFile_ReadRef(file, &m_pAimCamembert);
        IKFile_ReadRef(file, &m_apPointLightFxData[0]);
        IKFile_ReadRef(file, &m_apPointLightFxData[1]);
        IKFile_ReadRef(file, &m_apPointLightFxData[2]);
        ReadF32LE(file, &m_afPointLightReach[0]);
        ReadF32LE(file, &m_afPointLightReach[1]);
        ReadF32LE(file, &m_afPointLightReach[2]);
    }
    return 1;
}

// 0x003a32b8 CKFireBreath_Start
void CKFireBreath::Start(CKS08AbilityHostBase* host) {
    m_pLoopSound = nullptr;
    CKBreathElement::Start(host);  // 0x00380f50
}

// 0x003a3240 CKFireBreath_End
void CKFireBreath::End(int32_t forced) {
    if (m_pLoopSound != nullptr) {
        Sound_Stop(m_pLoopSound, 0);  // 0x001111b0
        m_pLoopSound = nullptr;
    }
    CKBreathElement::End(forced);  // 0x00381220
}

// 0x003a31e0 ResetFireBreathRuntimeEffects
void CKFireBreath::ResetRuntime(int32_t type) {
    m_pLoopSound = nullptr;
    CKBreathElement::ResetRuntime(type);  // 0x00381ed8
    m_ui8HotspotIndex = 2;
    m_fFlameRollRad = 0.0f;
    m_pPointLightNodeFx = nullptr;
    m_pSparkNodeFx = nullptr;
    m_pParticlesNodeFx = nullptr;
    m_pActiveAnimFx = nullptr;
}

// 0x003a3098 CKFireBreath_GetSound_maybe
CKSound* CKFireBreath::GetSound(int32_t which) {
    CKSoundDictionaryID* sounds = static_cast<CKSoundDictionaryID*>(m_pSoundDico);
    if (which == 0) return sounds->GetSound(0);  // 0x00112bc0
    if (which != 1) return nullptr;
    auto playable = [sounds](uint32_t index) {
        return sounds->GetSound(index) != nullptr && sounds->GetSound(index)->GetSample() != nullptr;  // 0x00111000
    };
    if (m_dwLevelIndex == 1 || m_dwLevelIndex == 2) {
        if (m_dwLevelIndex == 2 && playable(3)) return sounds->GetSound(3);
        if (playable(2)) return sounds->GetSound(2);
    }
    return sounds->GetSound(1);
}

// 0x003a35c8 CKFireBreath_GetEmitterPosition
CVector3 CKFireBreath::GetEmitterPosition(uint8_t raw) {
    CVector3 out = kNullVector;
    const CKParticlesEffectNodeFx* effect = static_cast<const CKParticlesEffectNodeFx*>(m_pParticlesNodeFx);
    if (effect != nullptr && effect->m_ui32NodeCount != 0) {
        const CParticlesNodeFx* node = nullptr;
        for (uint32_t i = effect->m_ui32NodeCount; i != 0;) {
            --i;
            node = effect->m_ppParticleNodes[i];
            if (node != nullptr) break;
        }
        if (node != nullptr) {
            const RwFrame* frame = node->m_pRwFrame;
            const RwV3d& v = raw == 0 ? FrameLtm(frame)->at : frame->modelling.right;  // +0x70 / +0x10
            out = CVector3{v.x, v.y, v.z};
        }
    }
    if (out.x == kNullVector.x && out.y == kNullVector.y && out.z == kNullVector.z) {
        out = CKBreathElement::GetEmitterPosition(raw);  // 0x00382398
    }
    return out;
}

// 0x003a3e98 CKFireBreath_ConfigureSparkNode_maybe. The float tests are the original's (ble / bgt: ordered).
void CKFireBreath::ConfigureSparkNode(int32_t on) {
    if (on == 0) return;
    CKSparkNodeFx* spark = static_cast<CKSparkNodeFx*>(m_pSparkNodeFx);
    if (spark == nullptr) return;
    const float ratio = m_afConeAngleDeg[m_dwLevelIndex] / m_afConeAngleDeg[0];
    float scaleA = ratio;  // the range 0x40's
    float scaleB = ratio;  // the range 0x50's
    float scaleC = ratio;  // the speed's
    float scaleD = ratio;  // the cone's
    if (ratio > 1.0f) {  // TOC +0x37f8
        const float over = ratio - 1.0f;
        scaleA = ppc::fmadds(over, m_unk178[0] - 1.0f, 1.0f);
        scaleB = ppc::fmadds(over, m_unk178[1] - 1.0f, 1.0f);
        scaleC = ppc::fmadds(over, m_unk178[2] - 1.0f, 1.0f);
        scaleD = ppc::fmadds(over, m_unk178[3] - 1.0f, 1.0f);
    }
    const float half = m_unk178[9] * 0.5f;  // +0x19c; TOC +0x381c
    const float angle = (half > 180.0f ? scaleD * 180.0f : scaleD * half) * 0x1.1df468p-6f;  // TOC +0x3860 / +0x3864
    float sine = 1.0f;
    if (!(angle > 0x1.921fb2p+0f)) sine = GameSinf(angle);  // TOC +0x3868 (0x3fc90fd9)
    const float cosine = GameCosf(angle);
    const float mid = ppc::fmadds(cosine, 0.5f, 0.5f);
    const float rangeA[2] = {scaleA * m_unk178[4], scaleA * m_unk178[5]};  // +0x188 / +0x18c
    const float rangeB[2] = {scaleB * m_unk178[6], scaleB * m_unk178[7]};  // +0x190 / +0x194
    const float axisA[3] = {0.0f, 0.0f, mid};
    const float axisB[3] = {sine, 0.0f, 1.0f - mid};
    spark->SetParamVec2_40(rangeA);                       // 0x001d3f88
    static_cast<CKSparkNodeFx*>(m_pSparkNodeFx)->SetParamVec2_50(rangeB);                          // 0x001d3fd8
    static_cast<CKSparkNodeFx*>(m_pSparkNodeFx)->SetParamFloat_68(scaleC * m_unk178[8]);           // 0x001d4028 (+0x198)
    static_cast<CKSparkNodeFx*>(m_pSparkNodeFx)->SetParamVec3_10(axisA);                           // 0x001d4048
    static_cast<CKSparkNodeFx*>(m_pSparkNodeFx)->SetParamVec3_1c(axisB);                           // 0x001d40b0
}

// 0x003a5498 SetFireBreathEffectsActive. The four pooled lookups are the inlined CKSrvFx::AcquireFx.
void CKFireBreath::SetFxActive(uint8_t on) {
    CKSrvFx* fx = FxService();
    if (on == 0) {
        ConfigureSparkNode(0);
        if (m_pSparkNodeFx != nullptr) {
            StopOwnedSparkEffect(static_cast<CKSparkNodeFx*>(m_pSparkNodeFx), this);  // 0x001d4698
            static_cast<IKFx*>(m_pSparkNodeFx)->ReleaseReservation(this);           // vt+0x54
            m_pSparkNodeFx = nullptr;
        }
        if (m_pParticlesNodeFx != nullptr) {
            StopOwnedParticleEffect(static_cast<IKFx*>(m_pParticlesNodeFx), this);  // 0x001cdde8
            static_cast<IKFx*>(m_pParticlesNodeFx)->ReleaseReservation(this);
            m_pParticlesNodeFx = nullptr;
        }
        if (m_pActiveAnimFx != nullptr) {
            static_cast<CKAnimatedFxCollection*>(m_pActiveAnimFx)->Stop();  // TocBridge -> 0x005cc990
            m_pActiveAnimFx = nullptr;
        }
        if (m_pPointLightNodeFx != nullptr) {
            static_cast<IKFx*>(m_pPointLightNodeFx)->StopAndRelease(this);  // vt+0x58
            m_pPointLightNodeFx = nullptr;
        }
        if (m_pLoopSound != nullptr) {
            Sound_Stop(m_pLoopSound, 0);
            m_pLoopSound = nullptr;
        }
        return;
    }
    CSGHotSpot* spot = static_cast<CSGHotSpot*>(m_pHost->GetHotspot(m_ui8HotspotIndex));  // vt+0xcc
    // The spark burst under the hot spot.
    CKSparkFxData* sparkData = static_cast<CKSparkFxData*>(m_pSparkFxData);
    sparkData->m_unk10 = spot;
    sparkData->m_unk0c = nullptr;
    m_pSparkNodeFx = fx->AcquireFx(sparkData, this);
    // The level's particle effect following the hot spot.
    CKParticlesEffectFxData* particles = static_cast<CKParticlesEffectFxData*>(m_apParticlesFxData[m_dwLevelIndex]);
    particles->m_pAttachOwner = nullptr;
    particles->m_pAttachHotSpot = spot;
    m_pParticlesNodeFx = fx->AcquireFx(particles, this);
    ConfigureSparkNode(1);
    // Levels 1 and 2: the animated collection on the hero's rigs.
    if (m_dwLevelIndex != 0) {
        CKAnimatedFxCollection* collection = static_cast<CKAnimatedFxCollection*>(m_dwLevelIndex == 1 ? m_pAnimFxLevel1 : m_pAnimFxLevel2);
        m_pActiveAnimFx = collection;
        // vt+0x08, its +0x1c
        CSGLeaf* heroNode = static_cast<CSGLeaf*>(static_cast<IKHook*>(m_pHost->GetOwner())->m_pKGLObject);
        // vt+0x104 (the hero host's GetHeroAttachmentSets 0x3ee6a0: the hero's +0x1070; a hero-only slot here).
        CKHkS08Hero* hero = static_cast<CKS08HeroAbilityHost*>(m_pHost)->GetHero();
        SAnimatedFxRig* rigs = reinterpret_cast<SAnimatedFxRig*>(&hero->m_apUnk1070[0][0]);
        collection->Play(heroNode, rigs, spot);  // TocBridge -> 0x005cc528
    }
    // The level's point light at the hot spot.
    CVector3 position;
    spot->GetWorldPosition(&position);  // 0x000ce790
    CKPointLightFxData* light = static_cast<CKPointLightFxData*>(m_apPointLightFxData[m_dwLevelIndex]);
    light->m_vPosition = position;
    m_pPointLightNodeFx = fx->AcquireFx(light, this);
    // The start sound and the level's loop sound, both on the hero's node.
    CKSound* start = GetSound(0);
    if (start != nullptr) {
        start->SetAttachObject(static_cast<IKHook*>(m_pHost->GetOwner())->m_pKGLObject);  // 0x00111350
        start->Play(0.0f);  // 0x00111230
    }
    m_pLoopSound = GetSound(1);
    if (m_pLoopSound != nullptr) {
        m_pLoopSound->SetAttachObject(static_cast<IKHook*>(m_pHost->GetOwner())->m_pKGLObject);
        m_pLoopSound->Play(0.0f);
    }
}

// 0x003a3720 UpdateFireBreathEffects. The particles and the spark follow the hero's speed; the aim direction is computed
// (host vt+0x58: the facing and target toward the aim); then, with both effects and a CKHkS08Hero, the flame rolls about
// the hot spot's z axis towards the target's height (at most +0xe0 x dt x 5 per frame, -0.19635..1.0472 rad) or back to
// 0 without one, and the effects take the rolled orientation; the point light goes to the flame's reach (the breath's
// distance, at most +0x1c8[level], stopped by a wall).
void CKFireBreath::UpdateFx(float dt) {
    CKParticlesEffectNodeFx* effect = static_cast<CKParticlesEffectNodeFx*>(m_pParticlesNodeFx);
    if (effect != nullptr) {
        const uint32_t count = effect->m_ui32NodeCount;
        for (uint32_t i = 0; i != count; ++i) {
            CParticlesNodeFx* node = static_cast<CKParticlesEffectNodeFx*>(m_pParticlesNodeFx)->m_ppParticleNodes[i];
            if (node != nullptr) node->m_fEmissionSpeedAdjustment = m_pHost->GetHeroSpeedForAbility();  // vt+0x48
        }
    }
    if (m_pSparkNodeFx != nullptr) {
        float ratio = m_afConeAngleDeg[m_dwLevelIndex] / m_afConeAngleDeg[0];
        if (ratio > 1.0f) ratio = ppc::fmadds(ratio - 1.0f, m_unk178[2] - 1.0f, 1.0f);  // TOC +0x37f8
        const float speed = ratio * m_unk178[8];
        static_cast<CKSparkNodeFx*>(m_pSparkNodeFx)->SetParamFloat_68(speed + m_pHost->GetHeroSpeedForAbility());  // 0x001d4028
    }
    if (m_pActiveAnimFx != nullptr) static_cast<CKAnimatedFxCollection*>(m_pActiveAnimFx)->Update(dt);  // TocBridge -> 0x005cccb0
    m_pHost->ComputeAimDirection(0x1.921fb6p+1f, this, m_pAimCamembert);  // vt+0x58 (pi, TOC +0x37fc); the result is unused
    if (m_pParticlesNodeFx == nullptr || m_pSparkNodeFx == nullptr) return;

    CMatrix34 spot;
    static_cast<CSGHotSpot*>(m_pHost->GetHotspot(m_ui8HotspotIndex))->GetWorldMatrix(&spot);  // vt+0xcc, 0x000ce970
    if (m_pHost->GetOwner()->IsKindOfClass(0x25c2) != 0) {  // vt+0x08, vt+0x08
        CMatrix34 inverse;
        Mat4_Invert(&inverse, &spot);  // 0x0023f878
        float roll;
        if (m_pHost->GetLockedTarget() == nullptr) {  // vt+0xd4
            // Back to 0.
            const float step = dt * m_fGroundTurnA;
            roll = m_fFlameRollRad - step;
            if (!(roll >= 0.0f)) {
                roll = m_fFlameRollRad + step;
                if (!(roll <= 0.0f)) roll = 0.0f;
            }
        } else {
            const CVector3 target = m_pHost->GetTargetAimPoint(1, 0);  // vt+0xdc
            float dy = target.y - spot.m_pos.y;
            const float dx = target.x - spot.m_pos.x;
            const float dz = target.z - spot.m_pos.z;
            const float length = Sqrtf(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));
            if (length != 0.0f) dy = dy * (1.0f / length);
            if (dy <= -1.0f) {
                dy = -1.0f;
            } else if (dy >= 1.0f) {
                dy = 1.0f;
            }
            const float toTarget = crt::Acosf(dy);  // TocBridge_Math_Acosf
            float at = spot.m_at.y;
            if (at <= -1.0f) {
                at = -1.0f;
            } else if (at >= 1.0f) {
                at = 1.0f;
            }
            float wanted = toTarget - crt::Acosf(at);
            if (wanted <= -0x1.921fb6p-3f) {  // TOC +0x3800 (0xbe490fdb)
                wanted = -0x1.921fb6p-3f;
            } else if (wanted >= 0x1.0c1524p+0f) {  // TOC +0x3804 (0x3f860a92)
                wanted = 0x1.0c1524p+0f;
            }
            const float step = dt * m_fGroundTurnA;
            const float low = ppc::fmadds(step, -5.0f, m_fFlameRollRad);  // TOC +0x3808
            const float high = ppc::fmadds(step, 5.0f, m_fFlameRollRad);  // TOC +0x3810
            if (wanted <= low) {
                roll = low;
            } else if (wanted >= high) {
                roll = high;
            } else {
                roll = wanted;
            }
        }
        m_fFlameRollRad = roll;
        Mat4_RotateLocalZDeg(roll * 0x1.ca5dc2p+5f, &spot);  // TOC +0x380c (0x42652ee1); 0x002419c0
        CVector3 forward;
        Mat4_TransformVectors(&inverse, &forward, &spot.m_right, 1);  // 0x0023f7b0
        SetOwnedParticleEffectTransform(static_cast<CKParticlesEffectNodeFx*>(m_pParticlesNodeFx), &forward, &kAxisY, this);  // 0x001cdc08
        static_cast<CSGMovable*>(static_cast<CKSparkNodeFx*>(m_pSparkNodeFx)->m_pSparkNode)->SetOrientationFromAtUp(&forward, &kAxisY);  // 0x000d0918
        if (m_pActiveAnimFx != nullptr) {
            static_cast<CKAnimatedFxCollection*>(m_pActiveAnimFx)->SetOrientation(&forward, &kAxisY);  // TocBridge -> 0x005cc7f0
        }
    }
    if (m_pPointLightNodeFx == nullptr) return;
    // The point light at the flame's reach.
    float reach = m_fSphereSpeed * m_fBreathElapsedTime;
    if (!(m_afPointLightReach[m_dwLevelIndex] > reach)) reach = m_afPointLightReach[m_dwLevelIndex];
    const float startX = ppc::fmadds(spot.m_at.x, -0.5f, spot.m_pos.x);  // TOC +0x3818
    const float startY = ppc::fmadds(spot.m_at.y, -0.5f, spot.m_pos.y);
    const float startZ = ppc::fmadds(spot.m_at.z, -0.5f, spot.m_pos.z);
    const float length = reach + 0.5f;  // TOC +0x381c
    float endX = ppc::fmadds(length, spot.m_at.x, startX);
    float endY = ppc::fmadds(length, spot.m_at.y, startY);
    float endZ = ppc::fmadds(length, spot.m_at.z, startZ);
    CLine line;
    line.m_start = CVector3{startX, startY, startZ};
    line.m_VectDir = CVector3{endX - startX, endY - startY, endZ - startZ};
    CGroundEdgeDatasOut wall;
    CKSrvCollision* collision = static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision);  // TOC +0x3820 -> +0x58
    if (collision->RaycastWalls(&line, 0.1f, &wall, 0, nullptr, 1) != 0) {  // 0x00198438; TOC +0x3824
        const float t = reach * wall.m_ftLine;
        endZ = ppc::fmadds(t, spot.m_at.z, startZ);
        endX = ppc::fmadds(t, spot.m_at.x, startX);
        endY = ppc::fmadds(t, spot.m_at.y, startY);
    }
    static_cast<CKPointLightFxData*>(m_apPointLightFxData[m_dwLevelIndex])->m_vPosition = CVector3{endX, endY, endZ};
}
