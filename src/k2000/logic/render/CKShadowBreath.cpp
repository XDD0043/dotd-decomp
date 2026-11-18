// CKShadowBreath.cpp - reconstructed original translation unit 0x3d3fe8-0x3d7500 (GAME_TOC1, main_toc1), 26 functions, 26 live.
// Primary class: CKShadowBreath  key 0xa90c  category Logic  size 0x210  vtable 0xb24758
// Other owners: UpdateShadowBreathEffects (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x3d3fe8  CKShadowBreath_Delete
//   [x] 0x3d4038  CKShadowBreath_GetAbilityId  (header)
//   [x] 0x3d4040  CKShadowBreath_SelectSound_maybe
//   [x] 0x3d4188  CKShadowBreath_ResetRuntime
//   [x] 0x3d4258  CKShadowBreath_End
//   [x] 0x3d42d0  CKShadowBreath_Start
//   [x] 0x3d4308  CKShadowBreath_PostLoad  (inherited: CKBreathElement_PostLoad)
//   [x] 0x3d4330  CKShadowBreath_RecursiveRegistration  (inherited: CKBreathElement_RecursiveRegistration)
//   [x] 0x3d4358  CKShadowBreath_Destroy  (inherited: CKBreathElement_Destroy)
//   [x] 0x3d4380  CKShadowBreath_DeletingDestructor  (the destructor; delete)
//   [x] 0x3d43c8  CKShadowBreath_Destructor  (C++ destructor chain: vtable stores only)
//   [x] 0x3d43f8  CKShadowBreath_DestructBody  (C++ destructor chain: vtable stores only)
//   [x] 0x3d4428  CKShadowBreath_Construct
//   [x] 0x3d4460  CKShadowBreath_Construct_2  (the same as CKShadowBreath_Construct)
//   [x] 0x3d4498  CKShadowBreath_DeleteArray
//   [ ] 0x3d4540  RegisterCKShadowBreathClass
//   [ ] 0x3d45c8  _GLOBAL__D_3d45c8
//   [ ] 0x3d45d8  _GLOBAL__I_3d45d8
//   [x] 0x3d45e8  CKShadowBreath_GetEmitterPosition
//   [x] 0x3d4740  CKShadowBreath_Create
//   [x] 0x3d4798  CKShadowBreath_CreateArray
//   [x] 0x3d4850  UpdateShadowBreathEffects  (CKShadowBreath::UpdateFx)
//   [x] 0x3d5128  CKShadowBreath_ConfigureSparkNode_maybe
//   [x] 0x3d5518  CKShadowBreath_Load
//   [ ] 0x3d6038  CKShadowBreath_Save
//   [x] 0x3d6b38  CKShadowBreath_SetFxActive
//
//   [x] 0x9c07c0  CKShadowBreath_IsKindOfClass  [inline]  (header)
//   [x] 0x9c0810  CKShadowBreath_GetClassType  [inline]
//   [x] 0x9c0818  CKShadowBreath_GetClassID  [inline]
//   [x] 0x9c0820  CKShadowBreath_StartEmitterFx  [inline]  (the base's (not overridden))
#include "k2000/logic/render/CKShadowBreath.h"

#include <cmath>
#include <cstring>

#include "Renderware/rwcore/RwCamera.h"
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "Spyro2008/logic/CKS08ElementDamage.h"
#include "Spyro2008/misc/CKS08HeroAbilityHost.h"
#include "crt/ppc_ops.h"
#include "crt/xatan.h"
#include "crt/xsinf.h"
#include "k2000/dictionaries/CKSoundDictionaryID.h"
#include "k2000/fx/CKSparkFxData.h"
#include "k2000/fx/IKFx.h"
#include "k2000/hooks/IKHook.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKParticlesEffectFxData.h"
#include "k2000/logic/CKProjectileAccessor.h"
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/logic/fx/CKAnimatedFx.h"
#include "k2000/logic/fx/CKAnimatedFxCollection.h"
#include "k2000/logic/fx/CKParticlesEffectNodeFx.h"
#include "k2000/logic/fx/CKSparkNodeFx.h"
#include "k2000/logic/render/CKPointLightFxData.h"
#include "k2000/logic/sound/CKSound.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/Mat4.h"
#include "k2000/scenegraph/CParticlesNodeFx.h"
#include "k2000/scenegraph/CSGLeaf.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/services/CKSrvCollision.h"
#include "k2000/services/CKSrvFx.h"
#include "k2000/services/CollisionDatas.h"

namespace {
CKSrvFx* FxService() { return static_cast<CKSrvFx*>(g_pEngine->m_srvFx); }
constexpr CVector3 kNullVector{0.0f, 0.0f, 0.0f};  // 0x00c50d64
constexpr CVector3 kAxisY{0.0f, 1.0f, 0.0f};       // 0x00c50d40 (TOC +0x4094)
bool SignBitSet(float x) {
    int32_t bits;
    std::memcpy(&bits, &x, sizeof(bits));
    return bits < 0;
}
// The inlined sinf / cosf (as CKFireBreath.cpp): the single-precision polynomials for a non-negative argument (by its
// sign bit), the library's of the magnitude otherwise (the sine negated).
float GameSinf(float x) { return SignBitSet(x) ? -crt::LibSinf(-x) : crt::InlineSinf(x); }
float GameCosf(float x) { return SignBitSet(x) ? crt::LibCosf(-x) : crt::InlineCosf(x); }
// 0x00010690 Math_Sqrtf
float Sqrtf(float x) { return static_cast<float>(std::sqrt(static_cast<double>(x))); }
}  // namespace

// A Rand_Int draw (0x00011500) as the float of its low 16 bits (rldicl 48, fcfid, frsp: exact). A macro, so that the
// rand log (DOTD_REPLAY_RANDLOG) names the function that draws.
#define SB_RAND_U16() static_cast<float>(static_cast<uint32_t>(Rand_Int()) & 0xffffu)

// 0x003d5518 CKShadowBreath_Load
int32_t CKShadowBreath::Load(IKFile* file, int32_t type) {
    CKBreathElement::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    IKFile_ReadRef(file, &m_unk1a0);
    IKFile_ReadRef(file, &m_unk1d4);
    IKFile_ReadRef(file, &m_unk1d8);
    IKFile_ReadRef(file, &m_unk1e0);
    IKFile_ReadRef(file, &m_unk1a8[0]);
    IKFile_ReadRef(file, &m_unk1a8[1]);
    IKFile_ReadRef(file, &m_unk1a8[2]);
    for (uint32_t i = 0; i < 10; ++i) ReadF32LE(file, &m_unk178[i]);  // ten separate 4-byte reads
    IKFile_ReadRef(file, &m_unk1e4);
    IKFile_ReadRef(file, &m_unk1e8);
    IKFile_ReadRef(file, &m_unk1ec);
    ReadF32LE(file, &m_unk1f0);
    ReadF32LE(file, &m_unk1f4);
    ReadF32LE(file, &m_unk1f8);
    ReadF32LE(file, &m_unk1fc);
    ReadF32LE(file, &m_unk200);
    IKFile_ReadRef(file, &m_unk1b8[0]);
    IKFile_ReadRef(file, &m_unk1b8[1]);
    IKFile_ReadRef(file, &m_unk1b8[2]);
    for (uint32_t i = 0; i < 3; ++i) ReadF32LE(file, &m_unk1c8[i]);
    return 1;
}

// 0x003d42d0 CKShadowBreath_Start
void CKShadowBreath::Start(CKS08AbilityHostBase* host) {
    m_pLoopSound = nullptr;
    m_fShotTimer = m_unk1f8;
    CKBreathElement::Start(host);  // 0x00380f50
}

// 0x003d4258 CKShadowBreath_End
void CKShadowBreath::End(int32_t forced) {
    if (m_pLoopSound != nullptr) {
        Sound_Stop(m_pLoopSound, 0);  // 0x001111b0
        m_pLoopSound = nullptr;
    }
    CKBreathElement::End(forced);  // 0x00381220
}

// 0x003d4188 CKShadowBreath_ResetRuntime
void CKShadowBreath::ResetRuntime(int32_t type) {
    m_pLoopSound = nullptr;
    CKBreathElement::ResetRuntime(type);  // 0x00381ed8
    m_unk1a4 = nullptr;
    m_unk1b4 = nullptr;
    m_unk1dc = nullptr;
    m_unk1c4 = nullptr;
    m_fShotTimer = 0.0f;
    m_unk15c = 2;
    static_cast<CKS08ElementDamage*>(m_unk1ec)->SetAbilityId(GetAbilityId());  // vt+0x68, vt+0x50
    m_unk15d = 0;
    m_fRoll = 0.0f;
}

// 0x003d4040 CKShadowBreath_SelectSound_maybe
CKSound* CKShadowBreath::SelectSound(int32_t which) {
    CKSoundDictionaryID* sounds = static_cast<CKSoundDictionaryID*>(m_unk1e0);
    if (which == 0) return sounds->GetSound(0);  // 0x00112bc0
    if (which != 1) return nullptr;
    auto playable = [sounds](uint32_t index) {
        return sounds->GetSound(index) != nullptr && sounds->GetSound(index)->GetSample() != nullptr;  // 0x00111000
    };
    if (m_unk04 == 1 || m_unk04 == 2) {
        if (m_unk04 == 2 && playable(3)) return sounds->GetSound(3);
        if (playable(2)) return sounds->GetSound(2);
    }
    return sounds->GetSound(1);
}

// 0x003d45e8 CKShadowBreath_GetEmitterPosition
CVector3 CKShadowBreath::GetEmitterPosition(uint8_t raw) {
    CVector3 out = kNullVector;
    const CKParticlesEffectNodeFx* effect = static_cast<const CKParticlesEffectNodeFx*>(m_unk1b4);
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

// 0x003d5128 CKShadowBreath_ConfigureSparkNode_maybe (CKFireBreath_ConfigureSparkNode_maybe 0x3a3e98's code; the TOC
// constants at +0x40xx are the same values)
void CKShadowBreath::ConfigureSparkNode(int32_t on) {
    if (on == 0) return;
    CKSparkNodeFx* spark = static_cast<CKSparkNodeFx*>(m_unk1a4);
    if (spark == nullptr) return;
    const float ratio = m_unk44[m_unk04] / m_unk44[0];
    float scaleA = ratio;  // the range 0x40's
    float scaleB = ratio;  // the range 0x50's
    float scaleC = ratio;  // the speed's
    float scaleD = ratio;  // the cone's
    if (!(ratio <= 1.0f)) {  // ble: a NaN scales
        const float over = ratio - 1.0f;
        scaleA = ppc::fmadds(over, m_unk178[0] - 1.0f, 1.0f);
        scaleB = ppc::fmadds(over, m_unk178[1] - 1.0f, 1.0f);
        scaleC = ppc::fmadds(over, m_unk178[2] - 1.0f, 1.0f);
        scaleD = ppc::fmadds(over, m_unk178[3] - 1.0f, 1.0f);
    }
    const float half = m_unk178[9] * 0.5f;  // +0x19c
    const float angle = (half > 180.0f ? scaleD * 180.0f : scaleD * half) * 0x1.1df468p-6f;
    float sine = 1.0f;
    if (angle <= 0x1.921fb2p+0f) sine = GameSinf(angle);  // TOC +0x40e8 (0x3fc90fd9); ble: a NaN keeps 1
    const float cosine = GameCosf(angle);
    const float mid = ppc::fmadds(cosine, 0.5f, 0.5f);
    const float rangeA[2] = {scaleA * m_unk178[4], scaleA * m_unk178[5]};  // +0x188 / +0x18c
    const float rangeB[2] = {scaleB * m_unk178[6], scaleB * m_unk178[7]};  // +0x190 / +0x194
    const float axisA[3] = {0.0f, 0.0f, mid};
    const float axisB[3] = {sine, 0.0f, 1.0f - mid};
    spark->SetParamVec2_40(rangeA);                                                 // 0x001d3f88
    static_cast<CKSparkNodeFx*>(m_unk1a4)->SetParamVec2_50(rangeB);                 // 0x001d3fd8
    static_cast<CKSparkNodeFx*>(m_unk1a4)->SetParamFloat_68(scaleC * m_unk178[8]);  // 0x001d4028 (+0x198)
    static_cast<CKSparkNodeFx*>(m_unk1a4)->SetParamVec3_10(axisA);                  // 0x001d4048
    static_cast<CKSparkNodeFx*>(m_unk1a4)->SetParamVec3_1c(axisB);                  // 0x001d40b0
}

// 0x003d6b38 CKShadowBreath_SetFxActive (SetFireBreathEffectsActive's code, the loop sound at +0x204). The three pooled
// lookups are the inlined CKSrvFx::AcquireFx.
void CKShadowBreath::SetFxActive(uint8_t on) {
    CKSrvFx* fx = FxService();
    if (on == 0) {
        ConfigureSparkNode(0);
        if (m_unk1a4 != nullptr) {
            StopOwnedSparkEffect(static_cast<CKSparkNodeFx*>(m_unk1a4), this);  // 0x001d4698
            static_cast<IKFx*>(m_unk1a4)->ReleaseReservation(this);           // vt+0x54
            m_unk1a4 = nullptr;
        }
        if (m_unk1b4 != nullptr) {
            StopOwnedParticleEffect(static_cast<IKFx*>(m_unk1b4), this);  // 0x001cdde8
            static_cast<IKFx*>(m_unk1b4)->ReleaseReservation(this);
            m_unk1b4 = nullptr;
        }
        if (m_unk1dc != nullptr) {
            static_cast<CKAnimatedFxCollection*>(m_unk1dc)->Stop();  // TocBridge -> 0x005cc990
            m_unk1dc = nullptr;
        }
        if (m_unk1c4 != nullptr) {
            static_cast<IKFx*>(m_unk1c4)->StopAndRelease(this);  // vt+0x58
            m_unk1c4 = nullptr;
        }
        if (m_pLoopSound != nullptr) {
            Sound_Stop(m_pLoopSound, 0);
            m_pLoopSound = nullptr;
        }
        return;
    }
    CSGHotSpot* spot = static_cast<CSGHotSpot*>(m_pHost->GetHotspot(m_unk15c));  // vt+0xcc
    // The spark burst under the hot spot.
    CKSparkFxData* sparkData = static_cast<CKSparkFxData*>(m_unk1a0);
    sparkData->m_unk10 = spot;
    sparkData->m_unk0c = nullptr;
    m_unk1a4 = fx->AcquireFx(sparkData, this);
    // The level's particle effect following the hot spot.
    CKParticlesEffectFxData* particles = static_cast<CKParticlesEffectFxData*>(m_unk1a8[m_unk04]);
    particles->m_pAttachOwner = nullptr;
    particles->m_pAttachHotSpot = spot;
    m_unk1b4 = fx->AcquireFx(particles, this);
    ConfigureSparkNode(1);
    // Levels 1 and 2: the animated collection on the hero's rigs.
    if (m_unk04 != 0) {
        CKAnimatedFxCollection* collection = static_cast<CKAnimatedFxCollection*>(m_unk04 == 1 ? m_unk1d4 : m_unk1d8);
        m_unk1dc = collection;
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
    CKPointLightFxData* light = static_cast<CKPointLightFxData*>(m_unk1b8[m_unk04]);
    light->m_vPosition = position;
    m_unk1c4 = fx->AcquireFx(light, this);
    // The start sound and the level's loop sound, both on the hero's node.
    CKSound* start = SelectSound(0);
    if (start != nullptr) {
        start->SetAttachObject(static_cast<IKHook*>(m_pHost->GetOwner())->m_pKGLObject);  // 0x00111350
        start->Play(0.0f);  // 0x00111230
    }
    m_pLoopSound = SelectSound(1);
    if (m_pLoopSound != nullptr) {
        m_pLoopSound->SetAttachObject(static_cast<IKHook*>(m_pHost->GetOwner())->m_pKGLObject);
        m_pLoopSound->Play(0.0f);
    }
}

// 0x003d4850 UpdateShadowBreathEffects: UpdateFireBreathEffects's steps (the particles and the spark follow the hero's
// speed; the aim (host vt+0x58, unused); with both effects the flame's roll about the hot spot's z axis towards the
// target's height (at most +0xe0 x dt x 5 per frame, -0.19635..1.0472 rad) or back to 0, and the effects take the
// rolled orientation; the point light at the flame's reach), here without the hero-class test and with the hot spot's
// matrix taken after the target query; then at level index 2 the shot: once its timer (+0x208) is below 0, one draw
// for the speed, the projectile (+0x1e8, its damage +0x1ec, owned by the user) from the hot spot raised by +0x200 along
// its levelled forward, and a second draw for the next interval; else the timer counts down.
void CKShadowBreath::UpdateFx(float dt) {
    CKParticlesEffectNodeFx* effect = static_cast<CKParticlesEffectNodeFx*>(m_unk1b4);
    if (effect != nullptr) {
        const uint32_t count = effect->m_ui32NodeCount;
        for (uint32_t i = 0; i != count; ++i) {
            CParticlesNodeFx* node = static_cast<CKParticlesEffectNodeFx*>(m_unk1b4)->m_ppParticleNodes[i];
            if (node != nullptr) node->m_fEmissionSpeedAdjustment = m_pHost->GetHeroSpeedForAbility();  // vt+0x48
        }
    }
    if (m_unk1a4 != nullptr) {
        float ratio = m_unk44[m_unk04] / m_unk44[0];
        if (!(ratio <= 1.0f)) ratio = ppc::fmadds(ratio - 1.0f, m_unk178[2] - 1.0f, 1.0f);  // TOC +0x4078 (ble skips)
        const float speed = ratio * m_unk178[8];
        static_cast<CKSparkNodeFx*>(m_unk1a4)->SetParamFloat_68(speed + m_pHost->GetHeroSpeedForAbility());  // 0x001d4028
    }
    if (m_unk1dc != nullptr) static_cast<CKAnimatedFxCollection*>(m_unk1dc)->Update(dt);  // TocBridge -> 0x005cccb0
    m_pHost->ComputeAimDirection(0x1.921fb6p+1f, this, m_unk1e4);  // vt+0x58 (pi, TOC +0x407c); the result is unused
    if (m_unk1b4 != nullptr && m_unk1a4 != nullptr) {
        CMatrix34 spot;
        CMatrix34 inverse;
        float roll;
        if (m_pHost->GetLockedTarget() == nullptr) {  // vt+0xd4
            static_cast<CSGHotSpot*>(m_pHost->GetHotspot(m_unk15c))->GetWorldMatrix(&spot);  // vt+0xcc, 0x000ce970
            Mat4_Invert(&inverse, &spot);  // 0x0023f878
            // Back to 0.
            const float step = dt * m_unkE0;
            roll = m_fRoll - step;
            if (!(roll >= 0.0f)) {  // cror gt|eq
                roll = m_fRoll + step;
                if (!(roll <= 0.0f)) roll = 0.0f;  // cror lt|eq
            }
        } else {
            const CVector3 target = m_pHost->GetTargetAimPoint(1, 0);  // vt+0xdc
            static_cast<CSGHotSpot*>(m_pHost->GetHotspot(m_unk15c))->GetWorldMatrix(&spot);  // vt+0xcc, 0x000ce970
            Mat4_Invert(&inverse, &spot);  // 0x0023f878
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
            if (wanted <= -0x1.921fb6p-3f) {  // TOC +0x4080 (0xbe490fdb)
                wanted = -0x1.921fb6p-3f;
            } else if (wanted >= 0x1.0c1524p+0f) {  // TOC +0x4084 (0x3f860a92)
                wanted = 0x1.0c1524p+0f;
            }
            const float step = dt * m_unkE0;
            const float low = ppc::fmadds(step, -5.0f, m_fRoll);  // TOC +0x4088
            if (wanted <= low) {
                roll = low;
            } else {
                const float high = ppc::fmadds(step, 5.0f, m_fRoll);  // TOC +0x408c
                roll = !(wanted >= high) ? wanted : high;
            }
        }
        m_fRoll = roll;
        Mat4_RotateLocalZDeg(roll * 0x1.ca5dc2p+5f, &spot);  // TOC +0x4090 (0x42652ee1); 0x002419c0
        CVector3 forward;
        Mat4_TransformVectors(&inverse, &forward, &spot.m_right, 1);  // 0x0023f7b0
        SetOwnedParticleEffectTransform(static_cast<CKParticlesEffectNodeFx*>(m_unk1b4), &forward, &kAxisY, this);  // 0x001cdc08
        static_cast<CSGMovable*>(static_cast<CKSparkNodeFx*>(m_unk1a4)->m_pSparkNode)->SetOrientationFromAtUp(&forward, &kAxisY);  // 0x000d0918
        if (m_unk1dc != nullptr) {
            static_cast<CKAnimatedFxCollection*>(m_unk1dc)->SetOrientation(&forward, &kAxisY);  // TocBridge -> 0x005cc7f0
        }
        if (m_unk1c4 != nullptr) {
            // The point light at the flame's reach.
            float reach = m_unk138 * m_unk16c;
            if (!(m_unk1c8[m_unk04] > reach)) reach = m_unk1c8[m_unk04];
            const float startX = ppc::fmadds(spot.m_at.x, -0.5f, spot.m_pos.x);  // TOC +0x4098
            const float startY = ppc::fmadds(spot.m_at.y, -0.5f, spot.m_pos.y);
            const float startZ = ppc::fmadds(spot.m_at.z, -0.5f, spot.m_pos.z);
            const float length = reach + 0.5f;  // TOC +0x409c
            float endX = ppc::fmadds(length, spot.m_at.x, startX);
            float endY = ppc::fmadds(length, spot.m_at.y, startY);
            float endZ = ppc::fmadds(length, spot.m_at.z, startZ);
            CLine line;
            line.m_start = CVector3{startX, startY, startZ};
            line.m_VectDir = CVector3{endX - startX, endY - startY, endZ - startZ};
            CGroundEdgeDatasOut wall;
            CKSrvCollision* collision = static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision);  // TOC +0x40a0 -> +0x58
            if (collision->RaycastWalls(&line, 0.1f, &wall, 0, nullptr, 1) != 0) {  // 0x00198438; TOC +0x40a4
                const float t = reach * wall.m_ftLine;
                endZ = ppc::fmadds(t, spot.m_at.z, startZ);
                endX = ppc::fmadds(t, spot.m_at.x, startX);
                endY = ppc::fmadds(t, spot.m_at.y, startY);
            }
            static_cast<CKPointLightFxData*>(m_unk1b8[m_unk04])->m_vPosition = CVector3{endX, endY, endZ};
        }
    }
    if (m_unk04 != 2) return;
    if (!(m_fShotTimer < 0.0f)) {  // blt
        m_fShotTimer = m_fShotTimer - dt;
        return;
    }
    const float speedBase = m_unk1f0;
    const float speedSpread = m_unk1f4;
    const float r = SB_RAND_U16();
    CMatrix34 spot;
    static_cast<CSGHotSpot*>(m_pHost->GetHotspot(m_unk15c))->GetWorldMatrix(&spot);  // vt+0xcc, 0x000ce970
    CVector3 dir{spot.m_at.x, 0.0f, spot.m_at.z};
    const float length = Sqrtf(ppc::fmadds(dir.z, dir.z, ppc::fmadds(dir.x, dir.x, 0.0f)));
    if (length != 0.0f) {
        const float inv = 1.0f / length;  // TOC +0x4078
        dir.z = dir.z * inv;
        dir.x = dir.x * inv;
        dir.y = dir.y * inv;
    }
    const CVector3 pos{spot.m_pos.x, spot.m_pos.y + m_unk200, spot.m_pos.z};
    CKProjectileAccessor* accessor = static_cast<CKProjectileAccessor*>(m_unk1e8);
    if (accessor->m_pProjectileType != nullptr) {
        IKSerializable* owner = m_pHost->GetOwner();  // vt+0x08
        // (r / 65535) x -2 x spread + (base + spread): TOC +0x40a8 / +0x40ac.
        const float speed = ppc::fmadds((r / 65535.0f) * -2.0f, speedSpread, speedBase + speedSpread);
        accessor->LaunchEx(&pos, &dir, speed, m_unk1ec, owner, nullptr);  // 0x001f2988
    }
    const float base = m_unk1f8 + m_unk1fc;
    const float r2 = SB_RAND_U16();
    m_fShotTimer = ppc::fmadds((r2 / 65535.0f) * -2.0f, m_unk1fc, base);
}
