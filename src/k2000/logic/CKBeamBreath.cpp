// CKBeamBreath.cpp - DOTD: the common bodies of CKFearEyes (unit 0x39cf88-0x3a0f00) and CKPurpleRay (unit
// 0x3c5af0-0x3c9a68), which are the same code (see CKBeamBreath.h). The TOC offsets in the comments are the fear
// eyes' (the purple ray's are +0x624 further: 0x36b8 -> 0x3cdc); the values are the same.
#include "k2000/logic/CKBeamBreath.h"

#include <cmath>
#include <cstring>

#include "Renderware/rwcore/RwCamera.h"
#include "Renderware/rwcore/RwMatrix.h"
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "Spyro2008/misc/CKS08AbilityHostBase.h"
#include "k2000/hooks/IKHook.h"
#include "crt/ppc_ops.h"
#include "crt/xatan.h"
#include "crt/xsinf.h"
#include "k2000/dictionaries/CKSoundDictionaryID.h"
#include "k2000/fx/IKFx.h"
#include "k2000/geometry/CGeometry.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKParticlesEffectFxData.h"
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/logic/fx/CKParticlesEffectNodeFx.h"
#include "k2000/logic/render/CKPointLightFxData.h"
#include "k2000/logic/render/CMaterial.h"
#include "k2000/logic/sound/CKSound.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/math/Math.h"
#include "k2000/math/Vec3.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/Mat4.h"
#include "k2000/scenegraph/CNode.h"
#include "k2000/scenegraph/CSGBranch.h"
#include "k2000/services/CKSrvCollision.h"
#include "k2000/services/CKSrvFx.h"
#include "k2000/services/CollisionDatas.h"
#include "k2000/system/CTimeManager.h"
#include "k2000/system/IKTime.h"

namespace {
CKSrvFx* FxService() { return static_cast<CKSrvFx*>(g_pEngine->m_srvFx); }                       // TOC +0x3724 -> +0x60
CKSrvCollision* Collision() { return static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision); }  // TOC +0x3724 -> +0x58
// TOC +0x3724 -> +0x48 -> +0x04 -> +0x1c: the game clock's frame time.
float FrameTime() { return g_pEngine->m_timeManager->m_pTime->m_afDeltaTime[0]; }

constexpr CVector3 kNullVector{0.0f, 0.0f, 0.0f};  // 0x00c50d64 (TOC +0x36b8)
constexpr CVector3 kAxisY{0.0f, 1.0f, 0.0f};       // 0x00c50d40 (TOC +0x3740)
constexpr float kPi = 0x1.921fb6p+1f;              // TOC +0x3718 (0x40490fdb); -pi TOC +0x3728
constexpr float kMaxPitch = 0x1.0c1524p-1f;        // TOC +0x3720 (0x3f060a92, 30 degrees); -: TOC +0x371c
constexpr float kRadToDeg = 0x1.ca5dc2p+5f;        // TOC +0x372c (0x42652ee1)
constexpr float kFloatMax = 0x1.fffffep+127f;      // 0x00c4ace0 (TOC +0x3738 -> +0x28)

bool SignBitSet(float x) {
    int32_t bits;
    std::memcpy(&bits, &x, sizeof(bits));
    return bits < 0;
}
// The inlined sinf: the single-precision polynomial for a non-negative argument (by its sign bit), the library's sinf
// 0x009a1390 of the magnitude, negated, otherwise.
float GameSinf(float x) { return SignBitSet(x) ? -crt::LibSinf(-x) : crt::InlineSinf(x); }
// 0x00010690 Math_Sqrtf
float Sqrtf(float x) { return static_cast<float>(std::sqrt(static_cast<double>(x))); }
// The sign bit cleared through memory (the original's stfs / rlwinm / lwz).
float ClearSign(float x) {
    uint32_t bits;
    std::memcpy(&bits, &x, sizeof(bits));
    bits &= 0x7fffffffu;
    std::memcpy(&x, &bits, sizeof(bits));
    return x;
}
float IntToFloat(int32_t v) { return static_cast<float>(static_cast<double>(v)); }  // extsw / fcfid / frsp
// The clamp before each acosf (ble / bge with cror: ordered; a NaN passes).
float ClampUnit(float v) {
    if (v <= -1.0f) return -1.0f;  // TOC +0x3698
    if (v >= 1.0f) return 1.0f;    // TOC +0x36d4
    return v;
}

// The inlined geometry alpha walk (as CKProjectileTypeScrap's): every geometry of the mesh takes `alpha` (CGeometry
// colour byte +0x23) and the "alpha blended" property bit 11 (vt+0x60 UpdateProperties when it changes); 0xff clears the
// bit everywhere, and a geometry with property bit 12 and a material of mode 1..6 keeps 0xff without blending.
void SetMeshAlpha(CNode* node, uint8_t alpha) {
    CGeometry* geometry = static_cast<CGeometry*>(node->m_lGeometryList);
    for (; geometry != nullptr; geometry = geometry->m_pNext) {
        uint32_t blend = 0;
        uint8_t value = 0xff;
        if (alpha != 0xff) {
            blend = 1;
            value = alpha;
            if ((geometry->m_BitProperties & 0x1000u) != 0) {
                const uint32_t mode = (static_cast<CMaterial*>(geometry->m_pMaterial)->m_baProperties >> 3) & 0xfu;
                if (mode != 0 && mode <= 6) {
                    blend = 0;
                    value = 0xff;
                }
            }
        }
        geometry->m_cGeometryColor[3] = value;
        const uint32_t bits = geometry->m_BitProperties;
        if (((bits >> 11) & 1u) != blend) {
            geometry->m_BitProperties = (bits & 0xfffff7ffu) | (blend << 11);
            geometry->UpdateProperties();  // vt+0x60
        }
    }
}
// The faded alpha: fctiwz of (from x (T - t) / T + to x t / T) (fmadds), its low byte.
uint8_t FadeAlpha(float from, float to, float t, float duration) {
    const float rest = (duration - t) / duration;
    const float done = t / duration;
    return static_cast<uint8_t>(ppc::fctiwz(ppc::fmadds(from, rest, to * done)));
}
void PlayOnHero(CKSound* sound, CKS08AbilityHostBase* host) {
    sound->SetAttachObject(static_cast<IKHook*>(host->GetOwner())->m_pKGLObject);  // vt+0x08, +0x1c; 0x00111350
    sound->Play(0.0f);                                       // 0x00111230 (TOC +0x36bc)
}
}  // namespace

// 0x0039d9d0 CKFearEyes_Load / 0x003c6538 CKPurpleRay_Load: CKBreathElement's data, then (level data only) 0x88 bytes:
// three rows of three references, one reference, three rows of five words, five words and four references.
int32_t CKBeamBreath::Load(IKFile* file, int32_t type) {
    CKBreathElement::Load(file, type);
    if (type == 0) {
        for (int32_t i = 0; i < 3; ++i) {
            IKFile_ReadRef(file, &m_unk1c8[i]);
            IKFile_ReadRef(file, &m_unk1d4[i]);
            IKFile_ReadRef(file, &m_unk1e8[i]);
        }
        IKFile_ReadRef(file, &m_unk204);
        for (int32_t i = 0; i < 3; ++i) {
            ReadS32LE(file, &m_unk178[i]);
            ReadS32LE(file, &m_unk184[i]);
            ReadS32LE(file, &m_unk190[i]);
            ReadF32LE(file, &m_unk19c[i]);
            ReadF32LE(file, &m_unk1a8[i]);
        }
        ReadF32LE(file, &m_unk1b4);
        ReadF32LE(file, &m_unk1b8);
        ReadF32LE(file, &m_unk1bc[0]);
        ReadF32LE(file, &m_unk1bc[1]);
        ReadF32LE(file, &m_unk1bc[2]);
        IKFile_ReadRef(file, &m_unk208);
        IKFile_ReadRef(file, &m_unk1f4[0]);
        IKFile_ReadRef(file, &m_unk1f4[1]);
        IKFile_ReadRef(file, &m_unk1f4[2]);
    }
    return 1;
}

// 0x0039d3a0 CKFearEyes_PostLoad / 0x003c5f08 CKPurpleRay_PostLoad (the last two through TocBridge 0x98f340).
int32_t CKBeamBreath::PostLoad(int32_t type) {
    CKBreathElement::PostLoad(type);  // 0x00382d98
    SceneNode_SetVisibleInLayer(m_unk1e8[0], 1, 0, 0);  // 0x005832a8
    SceneNode_SetVisibleInLayer(m_unk1e8[1], 1, 0, 0);
    SceneNode_SetVisibleInLayer(m_unk1e8[2], 1, 0, 0);
    return 1;
}

// 0x0039cfe0 CKFearEyes_ResetRuntime / 0x003c5b48 CKPurpleRay_ResetRuntime
void CKBeamBreath::ResetBeamRuntime(int32_t type, uint8_t hotSpot) {
    CKBreathElement::ResetRuntime(type);  // 0x00381ed8
    m_unk214 = 0;
    m_unk15c = hotSpot;
    m_unk1e0 = nullptr;
    m_unk1e4 = nullptr;
    m_unk200 = nullptr;
    m_unk20c = nullptr;
    m_unk218 = 0.0f;
    if (type == 0) m_unk21c = RwMatrixCreate();  // RwMatrixCreate_Thunk 0x0023fa68
    m_unk224 = 0.0f;
    m_unk15d = 2;
}

// 0x0039d350 CKFearEyes_Start / 0x003c5eb8 CKPurpleRay_Start
void CKBeamBreath::Start(CKS08AbilityHostBase* host) {
    m_unk220 = nullptr;
    CKBreathElement::Start(host);  // 0x00380f50
    m_unk214 = 0;
    m_unk224 = 0.0f;
    m_unk218 = 0.0f;
}

// 0x0039d290 CKFearEyes_End / 0x003c5df8 CKPurpleRay_End
void CKBeamBreath::End(int32_t forced) {
    if (m_unk220 != nullptr) {
        Sound_Stop(m_unk220, 0);  // 0x001111b0
        m_unk220 = nullptr;
    }
    CKBreathElement::End(forced);  // 0x00381220
    SceneNode_SetVisibleInLayer(m_unk20c, 1, 0, 0);  // TocBridge 0x98f340 -> 0x005832a8 (a null mesh does nothing)
    m_unk20c = nullptr;
}

// 0x0039d7f0 CKFearEyes_StopBreathing / 0x003c6358 CKPurpleRay_StopBreathing
void CKBeamBreath::StopBreathing() {
    CKBreathElement::StopBreathing();  // 0x00381928
    m_unk218 = 0.0f;
    CNode* node = m_unk20c;
    if (node == nullptr) return;
    const CGeometry* geometry = static_cast<const CGeometry*>(node->m_lGeometryList);
    m_unk210 = geometry != nullptr ? geometry->m_cGeometryColor[3] : static_cast<uint32_t>(m_unk178[m_unk04]);
    if (m_unk1b8 != 0.0f) {  // TOC +0x36bc
        m_unk214 = 1;
        return;
    }
    node->m_sgProperties = (node->m_sgProperties & 0xfffffffbu) | 4u;
}

// 0x0039d6e8 CKFearEyes_GetEmitterPosition / 0x003c6250 CKPurpleRay_GetEmitterPosition. The LTM is read as stored.
CVector3 CKBeamBreath::GetEmitterPosition(uint8_t raw) {
    CVector3 out = kNullVector;
    if (m_unk20c != nullptr) {
        const RwFrame* frame = m_unk20c->m_pRwFrame;
        const RwV3d& at = raw == 0 ? frame->ltm.at : frame->modelling.at;  // +0x70 / +0x30
        out = CVector3{at.x, at.y, at.z};
    }
    if (out.x == kNullVector.x && out.y == kNullVector.y && out.z == kNullVector.z) {
        out = CKBreathElement::GetEmitterPosition(raw);  // 0x00382398
    }
    return out;
}

// 0x0039d070 CKFearEyes_GetFxSound_maybe / 0x003c5bd8 CKPurpleRay_GetFxSound_maybe
CKSound* CKBeamBreath::GetFxSound(uint32_t which) {
    CKSoundDictionaryID* sounds = static_cast<CKSoundDictionaryID*>(m_unk208);
    auto playable = [sounds](uint32_t index) {
        return sounds->GetSound(index) != nullptr && sounds->GetSound(index)->GetSample() != nullptr;  // 0x00112bc0, 0x00111000
    };
    if (which == 1) {
        if (m_unk04 == 1 || m_unk04 == 2) {
            if (m_unk04 == 2 && playable(6)) return sounds->GetSound(6);
            if (playable(5)) return sounds->GetSound(5);
        }
        return sounds->GetSound(4);
    }
    if (which == 0) {
        if (m_unk04 == 2 && playable(1)) return sounds->GetSound(1);
        return sounds->GetSound(0);
    }
    if (which != 4) return nullptr;
    if (m_unk04 == 2 && playable(3)) return sounds->GetSound(3);
    return sounds->GetSound(2);
}

// 0x003a0518 CKFearEyes_SetFxActive / 0x003c9080 CKPurpleRay_SetFxActive. The two pooled lookups are the inlined
// CKSrvFx::AcquireFx.
void CKBeamBreath::SetBeamFxActive(uint8_t on, float impactPullBack) {
    CKSrvFx* fx = FxService();
    if (on == 0) {
        if (m_unk1e0 != nullptr) {
            StopOwnedParticleEffect(static_cast<IKFx*>(m_unk1e0), this);  // 0x001cdde8
            static_cast<IKFx*>(m_unk1e0)->ReleaseReservation(this);       // vt+0x54
            m_unk1e0 = nullptr;
        }
        if (m_unk1e4 != nullptr) {
            StopOwnedParticleEffect(static_cast<IKFx*>(m_unk1e4), this);
            static_cast<IKFx*>(m_unk1e4)->ReleaseReservation(this);
            m_unk1e4 = nullptr;
        }
        if (m_unk200 != nullptr) {
            static_cast<IKFx*>(m_unk200)->StopAndRelease(this);  // vt+0x58
            m_unk200 = nullptr;
        }
        if (m_unk220 == nullptr) return;
        CKSound* end = GetFxSound(4);
        if (end != nullptr) PlayOnHero(end, m_pHost);
        Sound_Stop(m_unk220, 0);  // 0x001111b0
        m_unk220 = nullptr;
        return;
    }
    // The beam particles on the hot spot (data flag 0x10 set).
    CKParticlesEffectFxData* particles = static_cast<CKParticlesEffectFxData*>(m_unk1c8[m_unk04]);
    particles->m_pAttachHotSpot = m_pHost->GetHotspot(m_unk15c);  // vt+0xcc
    particles->m_pAttachOwner = nullptr;
    particles = static_cast<CKParticlesEffectFxData*>(m_unk1c8[m_unk04]);
    particles->m_unk08 = static_cast<uint8_t>((particles->m_unk08 & 0xefu) | 0x10u);
    m_unk1e0 = fx->AcquireFx(static_cast<CKParticlesEffectFxData*>(m_unk1c8[m_unk04]), this);
    // The level's mesh: shown at its start alpha (the low byte of +0x184[level]), hung under the hot spot.
    m_unk20c = m_unk1e8[m_unk04];
    if (m_unk20c != nullptr) {
        m_unk20c->m_sgProperties &= 0xfffffffbu;
        SetMeshAlpha(m_unk20c, static_cast<uint8_t>(m_unk184[m_unk04]));
        CSGBranch* parent = m_unk20c->m_pParent;
        if (parent != nullptr) parent->RemoveChild(m_unk20c);  // vt+0x78
        static_cast<CSGHotSpot*>(m_pHost->GetHotspot(m_unk15c))->AttachVolume(m_unk20c);  // vt+0xcc, 0x000ce2b8
        *m_unk21c = m_unk20c->m_pRwFrame->modelling;  // the 0x40 bytes, flags and pads included
        UpdateBeamAndImpact(impactPullBack);  // 0x0039f228 (the result unused)
    }
    // The level's point light on the hot spot.
    CKPointLightFxData* light = static_cast<CKPointLightFxData*>(m_unk1f4[m_unk04]);
    light->m_pAttachHotSpot = m_pHost->GetHotspot(m_unk15c);
    light->m_pAttachNode = nullptr;
    m_unk200 = fx->AcquireFx(static_cast<CKPointLightFxData*>(m_unk1f4[m_unk04]), this);
    // The start sound and the level's loop sound, both on the hero's node.
    CKSound* start = GetFxSound(0);
    if (start != nullptr) PlayOnHero(start, m_pHost);
    m_unk220 = GetFxSound(1);
    if (m_unk220 != nullptr) PlayOnHero(m_unk220, m_pHost);
}

// 0x0039ff48 CKFearEyes_UpdateFx / 0x003c8ab0 CKPurpleRay_UpdateFx. The float tests are the original's (blt / cror bge:
// a NaN clock skips the fade-in and holds the fade-out).
void CKBeamBreath::UpdateBeamFx(float dt, float impactPullBack) {
    m_unk218 = dt + m_unk218;
    CNode* node = m_unk20c;
    if (node == nullptr || node->m_pParent == nullptr || (node->m_sgProperties & 4u) != 0) return;
    const int32_t level = static_cast<int32_t>(m_unk04);
    bool held = true;  // the hold below runs (not taken during a fade-in)
    if (m_unk218 < m_unk1b4 && m_unk155 != 0) {
        // The fade-in: from +0x184 to +0x178 over +0x1b4.
        held = false;
        if (node->m_lGeometryList == nullptr) goto beam;
        SetMeshAlpha(node, FadeAlpha(IntToFloat(m_unk184[level]), IntToFloat(m_unk178[level]), m_unk218, m_unk1b4));
    }
    if (held && m_unk214 == 0) {
        // Held: the alpha +0x178 once, then faded in.
        if (m_unk155 == 0) goto beam;
        if (node->m_lGeometryList != nullptr) {
            SetMeshAlpha(node, static_cast<uint8_t>(ppc::fctiwz(IntToFloat(m_unk178[level]))));
        }
        m_unk214 = 1;
    }
    if (m_unk155 == 0 && m_unk214 != 0) {
        // The fade-out: from the alpha at the stop to +0x190 over +0x1b8, then hidden.
        if (m_unk218 >= m_unk1b8) {
            m_unk214 = 0;
            m_unk20c->m_sgProperties = (m_unk20c->m_sgProperties & 0xfffffffbu) | 4u;
        } else if (m_unk20c->m_lGeometryList != nullptr) {
            const float from = static_cast<float>(static_cast<double>(m_unk210));  // the word as unsigned
            SetMeshAlpha(m_unk20c, FadeAlpha(from, IntToFloat(m_unk190[level]), m_unk218, m_unk1b8));
        }
    }
beam:
    const CVector3 end = UpdateBeamAndImpact(impactPullBack);  // 0x0039f228
    if (m_unk1e4 != nullptr) {
        SetOwnedParticleEffectPosition(static_cast<CKParticlesEffectNodeFx*>(m_unk1e4), &end, this);  // 0x001cdce0
    }
}

// 0x0039f228 CKFearEyes_UpdateBeamAndImpact_maybe / 0x003c7d90 CKPurpleRay_UpdateBeamAndImpact_maybe. The float tests
// keep the original's senses (ble / bge with cror ordered; bgt / blt plain).
CVector3 CKBeamBreath::UpdateBeamAndImpact(float impactPullBack) {
    CVector3 out = kNullVector;
    float lift = 0.0f;                            // f23
    const float length = m_unk1bc[m_unk04];       // f22
    CNode* node = m_unk20c;
    if (node != nullptr) {
        node->SetLocalMatrix(m_unk21c);  // 0x000d0be8
        // BUG(original): without the hot spot's node the matrix is the stack's (GetWorldMatrix leaves it); zeros here.
        CMatrix34 spot{};
        static_cast<CSGHotSpot*>(m_pHost->GetHotspot(m_unk15c))->GetWorldMatrix(&spot);  // vt+0xcc, 0x000ce970
        const float px = spot.m_pos.x;  // f21
        const float py = spot.m_pos.y;  // f24
        const float pz = spot.m_pos.z;  // f20
        m_pHost->ComputeAimDirection(kPi, this, m_unk204);  // vt+0x58 (the result unused)
        RwFrame* frame = node->m_pRwFrame;
        bool reaches = false;  // r27: the beam reaches the target (or hits a mesh)
        float scale = 1.0f;    // f27
        if (m_pHost->GetLockedTarget() == nullptr) {  // vt+0xd4
            // No target: the pitch goes back to 0 at 2 pi rad/s.
            const float step = FrameTime() + FrameTime();
            float pitch = ppc::fmadds(step, -kPi, m_unk224);
            if (!(pitch >= 0.0f)) {
                pitch = ppc::fmadds(step, kPi, m_unk224);
                if (!(pitch <= 0.0f)) pitch = 0.0f;
            }
            const float degrees = pitch * kRadToDeg;
            m_unk224 = pitch;
            Mat4_RotateLocalXDeg(degrees, &spot);                 // 0x00241118
            node->RotateInPlace(&frame->modelling.right.x, degrees);  // 0x000d11b0
        } else {
            // The target: the pitch turns towards it (at most 30 degrees, 2 pi rad/s).
            const CVector3 target = m_pHost->GetTargetAimPoint(1, 0);  // vt+0xdc
            const float dx = target.x - px;
            const float dy = target.y - py;  // f28
            const float dz = target.z - pz;
            const float dx2 = dx * dx;  // f26
            const float dz2 = dz * dz;  // f27
            const float squared = ppc::fmadds(dy, dy, dx2) + dz2;
            const float distance = Sqrtf(squared);  // f25
            const float norm = Sqrtf(squared);
            float cosine = dy;
            if (norm != 0.0f) cosine = dy * (1.0f / norm);
            const float toTarget = crt::Acosf(ClampUnit(cosine));    // TocBridge_Math_Acosf
            const float current = crt::Acosf(ClampUnit(spot.m_at.y));
            float wanted = toTarget - current;
            if (wanted <= -kMaxPitch) {
                wanted = -kMaxPitch;
            } else if (wanted >= kMaxPitch) {
                wanted = kMaxPitch;
            }
            const float step = FrameTime() + FrameTime();
            float pitch = ppc::fmadds(step, -kPi, m_unk224);
            if (!(wanted <= pitch)) {
                pitch = ppc::fmadds(step, kPi, m_unk224);
                if (!(wanted >= pitch)) pitch = wanted;
            }
            const float degrees = pitch * kRadToDeg;
            m_unk224 = pitch;
            const float down = -pitch;  // f29
            Mat4_RotateLocalXDeg(degrees, &spot);
            node->RotateInPlace(&frame->modelling.right.x, degrees);
            const CVector3 target2 = m_pHost->GetTargetAimPoint(0, 0);
            const float horizontal = Sqrtf(dx2 + dz2);  // f27
            // Reached when the target is between the beam's height at its distance and the first aim point's.
            if (!(target2.y - py > GameSinf(down) * horizontal) && !(GameSinf(down) * horizontal > dy)) {
                reaches = true;
                scale = distance / length;
            }
        }
        // The beam's line: from half a unit behind the hot spot along its (pitched) at row, length + 0.5 long.
        const float span = length + 0.5f;  // f31; TOC +0x3734
        CLine line;
        line.m_start = CVector3{ppc::fmadds(spot.m_at.x, -0.5f, px), ppc::fmadds(spot.m_at.y, -0.5f, py),
                                ppc::fmadds(spot.m_at.z, -0.5f, pz)};  // TOC +0x3730
        const float endX = ppc::fmadds(span, spot.m_at.x, line.m_start.x);  // f30
        const float endY = ppc::fmadds(span, spot.m_at.y, line.m_start.y);  // f29
        const float endZ = ppc::fmadds(span, spot.m_at.z, line.m_start.z);  // f28
        line.m_VectDir = CVector3{endX - line.m_start.x, endY - line.m_start.y, endZ - line.m_start.z};
        CLineCollisionDatas hit;
        hit.m_ftOnLine = kFloatMax;
        hit.m_pCollisionMesh = nullptr;
        hit.m_i32FaceIndex = -1;
        hit.m_ui8SectorNumber = 0;
        float t = 1.0f;  // f26
        if (Collision()->RaycastMeshes(&line, &hit, 1, 1, nullptr) != 0) {  // 0x00197af8
            reaches = true;
            t = hit.m_ftOnLine;
            lift = impactPullBack;  // TOC +0x373c
        }
        CGroundEdgeDatasOut wall;
        const bool hitWall = Collision()->RaycastWalls(&line, m_unk50[m_unk04], &wall, 0, nullptr, 1) != 0;  // 0x00198438
        if (hitWall && t >= wall.m_ftLine) {
            t = wall.m_ftLine;
            lift = 0.0f;
        }
        if (hitWall || reaches) {
            // The beam stops: at the target (yawed onto it) or where it hits.
            t = ClearSign(ppc::fmsubs(t, span, 0.5f) / length);
            if (scale >= t) {
                float dirX = line.m_VectDir.x;
                float dirY = line.m_VectDir.y;
                float dirZ = line.m_VectDir.z;
                const float norm = Sqrtf(ppc::fmadds(dirZ, dirZ, ppc::fmadds(dirX, dirX, dirY * dirY)));
                if (norm != 0.0f) {
                    const float inverse = 1.0f / norm;
                    dirZ = dirZ * inverse;
                    dirX = dirX * inverse;
                    dirY = dirY * inverse;
                }
                const float reach = ppc::fmsubs(length, t, impactPullBack);
                out = CVector3{ppc::fmadds(dirX, reach, px), ppc::fmadds(dirY, reach, py), ppc::fmadds(dirZ, reach, pz)};
            } else {
                const CVector3 target = m_pHost->GetTargetAimPoint(1, 0);
                CVector3 direction = line.m_VectDir;  // sp+0x74
                lift = 0.0f;
                const CVector3 hero = m_pHost->GetOwnerPosition();  // vt+0x10 GetHeroPosition
                const CVector3 toTarget{target.x - hero.x, target.y - hero.y, target.z - hero.z};
                const float yawTarget = Vec3_GetYawAngleFromZ(&toTarget);  // 0x00244528
                const float yaw = yawTarget - Vec3_GetYawAngleFromZ(&direction);
                node->RotateAboutPoint(yaw * kRadToDeg, reinterpret_cast<const CVector3*>(&frame->modelling.pos),
                                       reinterpret_cast<const CVector3*>(&frame->modelling.up));  // 0x000d0f80
                CVector3 turned;
                CVector3 v = direction;
                CVector3 up = spot.m_up;
                Vec3_RotateTowardByAngle(&turned, &v, &up, yaw);  // TocBridge -> 0x005841a8
                const float reach = ppc::fmsubs(scale, length, impactPullBack);
                out = CVector3{ppc::fmadds(reach, turned.x, px), ppc::fmadds(turned.y, reach, py),
                               ppc::fmadds(turned.z, reach, pz)};
            }
            if (m_unk1e4 == nullptr) {
                // The impact particles (data flag 0x10 cleared).
                CKParticlesEffectFxData* impact = static_cast<CKParticlesEffectFxData*>(m_unk1d4[m_unk04]);
                impact->m_unk08 = static_cast<uint8_t>(impact->m_unk08 & 0xefu);
                m_unk1e4 = FxService()->AcquireFx(static_cast<CKParticlesEffectFxData*>(m_unk1d4[m_unk04]), this);
            }
        } else {
            // Nothing in the way: the beam's full end, no impact.
            out = CVector3{endX, endY, endZ};
            if (m_unk1e4 != nullptr) {
                StopOwnedParticleEffect(static_cast<IKFx*>(m_unk1e4), this);  // 0x001cdde8
                static_cast<IKFx*>(m_unk1e4)->ReleaseReservation(this);       // vt+0x54
                m_unk1e4 = nullptr;
            }
        }
        // The mesh scaled across and to the length it covers.
        if (!(scale < t)) scale = t;
        node->ScaleXYZ(m_unk19c[m_unk04], m_unk19c[m_unk04], (scale * length) / m_unk1a8[m_unk04]);  // 0x000d0d28
    }
    out = CVector3{ppc::fmadds(lift, kAxisY.x, out.x), ppc::fmadds(lift, kAxisY.y, out.y), ppc::fmadds(lift, kAxisY.z, out.z)};
    return out;
}
