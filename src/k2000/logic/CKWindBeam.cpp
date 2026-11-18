// CKWindBeam.cpp - reconstructed original translation unit 0x3e0248-0x3e6f80 (GAME_TOC1, main_toc1), 26 functions, 26 live.
// Primary class: CKWindBeam  key 0xa50c  category Logic  size 0x318  vtable 0xb24920
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x3e0248  CKWindBeam_ApplyDamageParams
//   [x] 0x3e02a0  CKWindBeam_GetFxSound_maybe
//   [x] 0x3e03e8  CKWindBeam_PostLoad
//   [x] 0x3e0450  CKWindBeam_RecursiveRegistration  (CKGrabElement's 0x3a8368: returns 1; the default slot)
//   [x] 0x3e0478  CKWindBeam_Destroy  (inherited: CKGrabElement_Destroy)
//   [x] 0x3e04a0  CKWindBeam_Construct
//   [x] 0x3e04d8  CKWindBeam_DeleteArray
//   [x] 0x3e0578  CKWindBeam_DeletingDestructor  (the destructor; delete)
//   [x] 0x3e05c0  CKWindBeam_Destructor  (C++ destructor chain: vtable stores only)
//   [x] 0x3e05f0  CKWindBeam_DestructBody  (C++ destructor chain: vtable stores only)
//   [x] 0x3e0620  CKWindBeam_Construct_2  (the constructor, CKWindBeam.h)
//   [x] 0x3e0658  CKWindBeam_Start
//   [ ] 0x3e0758  RegisterCKWindBeamClass
//   [ ] 0x3e07e0  _GLOBAL__D_3e07e0
//   [ ] 0x3e07f0  _GLOBAL__I_3e07f0
//   [x] 0x3e0800  CKWindBeam_End
//   [x] 0x3e08f0  CKWindBeam_Slot80_maybe
//   [x] 0x3e0cd8  CKWindBeam_ReleaseAndStopFx_maybe
//   [x] 0x3e0e38  CKWindBeam_ResetRuntime
//   [x] 0x3e0f98  CKWindBeam_GrabTarget_maybe
//   [x] 0x3e1398  CKWindBeam_CreateArray
//   [x] 0x3e1448  CKWindBeam_Create
//   [x] 0x3e14a0  CKWindBeam_SetFxActive
//   [x] 0x3e1e60  CKWindBeam_Slot84_maybe
//   [x] 0x3e4a18  CKWindBeam_Load
//   [ ] 0x3e5c80  CKWindBeam_Save
//
//   [ ] 0x9c0930  CKWindBeam_IsKindOfClass  [inline]
//   [ ] 0x9c0980  CKWindBeam_GetClassType  [inline]
//   [ ] 0x9c0988  CKWindBeam_GetClassID  [inline]
//   [x] 0x9c0990  CKWindBeam_vf90  [inline]
//   [x] 0x9c0998  CKWindBeam_StartEmitterFx  [inline]
#include "k2000/logic/CKWindBeam.h"

#include <cmath>
#include <cstring>

#include "Renderware/rpprtstd/RpPrtStd.h"
#include "Renderware/rwcore/RwCamera.h"
#include "Spyro2008/logic/CKS08ElementDamage.h"
#include "Spyro2008/misc/CKS08AbilityHostBase.h"
#include "crt/ppc_ops.h"
#include "crt/xatan.h"
#include "k2000/dictionaries/CKSoundDictionaryID.h"
#include "k2000/fx/IKFx.h"
#include "k2000/geometry/CGeometry.h"
#include "k2000/hooks/IKHook.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKParticlesEffectFxData.h"
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/logic/IKFxData.h"
#include "k2000/logic/cameras/CKAimCamembert.h"
#include "k2000/logic/render/CMaterial.h"
#include "k2000/logic/sound/CKSound.h"
#include "k2000/math/Math.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/Mat4.h"
#include "k2000/scenegraph/CNode.h"
#include "k2000/scenegraph/CParticlesNodeFx.h"
#include "k2000/scenegraph/CSGBranch.h"
#include "k2000/services/CKSrvFx.h"
#include "platform/fps.h"

// 0x003e4a18 CKWindBeam_Load: CKGrabElement's data, then (level data only) 0x154 bytes. The vectors are one
// 12-byte read each, byte-swapped word by word afterwards.
int32_t CKWindBeam::Load(IKFile* file, int32_t type) {
    CKGrabElement::Load(file, type);
    if (type == 0) {
        IKFile_ReadRef(file, &m_unk1a4);
        for (int32_t i = 0; i < 3; ++i) {
            ReadF32LE(file, &m_unk140[i]);
            ReadS32LE(file, &m_unk14c[i]);
            ReadS32LE(file, &m_unk158[i]);
            ReadS32LE(file, &m_unk164[i]);
            ReadF32LE(file, &m_unk170[i]);
            ReadU32LEWords(file, reinterpret_cast<uint32_t*>(m_unk17c[i]), 3);
        }
        ReadF32LE(file, &m_unk1a0);
        for (int32_t i = 0; i < 3; ++i) {
            IKFile_ReadRef(file, &m_unk1fc[i]);
            IKFile_ReadRef(file, &m_unk20c[i]);
        }
        IKFile_ReadRef(file, &m_unk1f8);
        for (int32_t i = 0; i < 3; ++i) {
            ReadS32LE(file, &m_unk1a8[i]);
            ReadS32LE(file, &m_unk1b4[i]);
            ReadS32LE(file, &m_unk1c0[i]);
            ReadU32LEWords(file, reinterpret_cast<uint32_t*>(m_unk1cc[i]), 3);
        }
        ReadF32LE(file, &m_unk1f0);
        ReadF32LE(file, &m_unk1f4);
        for (int32_t i = 0; i < 3; ++i) {
            IKFile_ReadRef(file, &m_unk21c[i]);
            IKFile_ReadRef(file, &m_unk228[i]);
        }
        ReadU32LE(file, &m_unk234);
        for (int32_t i = 0; i <= 3; ++i) ReadF32LE(file, &m_unk238[i]);   // +0x238..+0x244
        for (int32_t i = 7; i <= 20; ++i) ReadF32LE(file, &m_unk238[i]);  // +0x254..+0x288
        for (int32_t i = 4; i <= 6; ++i) ReadF32LE(file, &m_unk238[i]);   // +0x248..+0x250
        IKFile_ReadRef(file, &m_unk28c);
        IKFile_ReadRef(file, &m_unk290[0]);
        IKFile_ReadRef(file, &m_unk290[1]);
        IKFile_ReadRef(file, &m_unk290[2]);
    }
    return 1;
}

namespace {
const CVector3 kNullVector = {0.0f, 0.0f, 0.0f};  // 0x00c50d64 (TOC +0x4244)
const RwV3d kAxisY = {0.0f, 1.0f, 0.0f};          // 0x00c50d40 (TOC +0x42d8): the shared Y axis
constexpr float kDegToRad = 0x1.1df468p-6f;       // TOC +0x423c (0x3c8efa34)
constexpr float kHalfPi = 0x1.921fb2p+0f;         // TOC +0x426c (0x3fc90fd9)
constexpr float kPi = 0x1.921fb6p+1f;             // TOC +0x4278 (0x40490fdb)
constexpr float kTenDegrees = 0x1.657182p-3f;     // TOC +0x42c8 (0x3e32b8c1)
constexpr float kRandStep = -0x1.0001p-15f;       // TOC +0x42c0 (0xb8000080, -1 / 32767.5)

// The draws are macros so that the rand log (DOTD_REPLAY_RANDLOG) names the function that draws (CSparkNodeFx's way).
// A Rand_Int draw (0x00011500) as the float of its low 16 bits (rldicl 48, fcfid, frsp: exact).
#define WB_RAND_U16() static_cast<float>(static_cast<uint32_t>(Rand_Int()) & 0xffffu)
// One draw in base +/- spread: fmadds(r / 65535 x -2, spread, base + spread) (TOC +0x42ac, +0x42bc).
#define WB_RAND_RANGE(base, spread) ppc::fmadds(WB_RAND_U16() / 65535.0f * -2.0f, (spread), (base) + (spread))
// One draw for a sign: fmadds(r, -1 / 32767.5, 1) below 0 (bge: not below) is -1, else 1.
#define WB_RAND_SIGN() (ppc::fmadds(WB_RAND_U16(), kRandStep, 1.0f) < 0.0f ? -1.0f : 1.0f)
// A rate drawn again turning the other way: the opposite sign of `old` (blt: a negative one gives +1, anything else
// -1) times |WB_RAND_RANGE(base, spread)| (the sign bit cleared through memory).
#define WB_REDRAW_RATE(old, base, spread) (((old) < 0.0f ? 1.0f : -1.0f) * std::fabs(WB_RAND_RANGE(base, spread)))

// 0x00010690 Math_Sqrtf of the original's squared lengths: y*y first, then x and z fused in.
float LengthYXZ(const CVector3& v) { return std::sqrt(ppc::fmadds(v.z, v.z, ppc::fmadds(v.x, v.x, v.y * v.y))); }
// The in-place normalisation (1 / length; skipped for a zero length).
void NormaliseInPlace(CVector3* v) {
    const float length = LengthYXZ(*v);
    if (length == 0.0f) return;
    const float inv = 1.0f / length;
    v->z = inv * v->z;
    v->x = inv * v->x;
    v->y = inv * v->y;
}
// The in-place rescale to `length` (skipped for a zero vector).
void ScaleToLength(CVector3* v, float length) {
    const float current = LengthYXZ(*v);
    if (current == 0.0f) return;
    const float k = length / current;
    v->z = k * v->z;
    v->x = k * v->x;
    v->y = k * v->y;
}
CVector3 Negated(const CVector3& v) { return CVector3{-v.x, -v.y, -v.z}; }

// The original's truncation of the emission phase (0x3e2310..0x3e2350): the float's fraction bits below its exponent
// masked off; below 1 (exponent 0x7e or less) the result is +0, from exponent 158 on the value itself.
float TruncateBits(float x) {
    uint32_t bits;
    std::memcpy(&bits, &x, sizeof(bits));
    const int32_t exponent = static_cast<int32_t>((bits >> 23) & 0xffu);
    uint32_t kept;
    if (exponent <= 0x7e) {
        kept = 0;
    } else if (exponent < 0x7f + 31) {
        kept = bits & ~(0x7fffffu >> (exponent - 0x7f));
    } else {
        kept = bits;
    }
    float value;
    std::memcpy(&value, &kept, sizeof(value));
    return value;
}

// The inlined geometry alpha walk (CKPoisonGrenade's / CKBeamBreath's): every geometry takes `alpha` (CGeometry colour
// byte +0x23) and the "alpha blended" property bit 11 (vt+0x60 when it changes); 0xff clears it everywhere, and a
// geometry with property bit 12 and a material of mode 1..6 keeps 0xff without blending. With `setStage` each geometry's
// low six property bits become 0x2c first (GrabTarget / SetFxActive: (bits & ~0x1f) | 0xc, then bit 5 set).
void SetMeshAlpha(CNode* node, uint8_t alpha, bool setStage = false) {
    for (CGeometry* geometry = static_cast<CGeometry*>(node->m_lGeometryList); geometry != nullptr;
         geometry = geometry->m_pNext) {
        if (setStage) geometry->m_BitProperties = (geometry->m_BitProperties & 0xffffffc0u) | 0x2cu;
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
// An alpha the original converts with fctiwz and stores as the word's low byte.
uint8_t AlphaByte(float value) { return static_cast<uint8_t>(ppc::fctiwz(value)); }
float IntToFloat(int32_t value) { return static_cast<float>(static_cast<double>(value)); }   // extsw, fcfid, frsp
float UIntToFloat(uint32_t value) { return static_cast<float>(static_cast<double>(value)); }  // clrldi, fcfid, frsp

// SceneNode_SetVisibleInLayer_maybe 0x005832a8 (through its TOC bridge 0x0098f340): the node hidden under sector 0's
// root.
void HideUnderSector0(IKSerializable* node) { SceneNode_SetVisibleInLayer(static_cast<CSGLeaf*>(node), 1, 0, 0); }

// The sound put on the user's node (host vt+0x08, its +0x1c; CKSound_SetAttachObject 0x00111350) and played
// (CKSound_Play 0x00111230 at 0.0, TOC +0x427c).
void PlayOnUser(CKSound* sound, CKS08AbilityHostBase* host) {
    sound->SetAttachObject(static_cast<IKHook*>(host->GetOwner())->m_pKGLObject);
    sound->Play(0.0f);
}

// A particle node's emission point (the CParticlesNodeFx AddPointToList inlined): below 64 points, `point` and the Y
// axis appended, the node's property 0x2000 set.
void EmitPoint(IKSerializable* object, const CVector3& point) {
    CParticlesNodeFx* node = static_cast<CParticlesNodeFx*>(object);
    if (node == nullptr || node->m_ui8NbActivePoints > 0x3f) return;
    RwV3d* at = &node->m_pAdvEmtPointList->pointList[node->m_ui8NbActivePoints];
    at->z = point.z;
    at->x = point.x;
    at->y = point.y;
    node->m_pAdvEmtPointList->directionList[node->m_ui8NbActivePoints] = kAxisY;
    node->m_sgProperties = (node->m_sgProperties & ~0x2000u) | 0x2000u;
    node->m_ui8NbActivePoints = static_cast<uint8_t>(node->m_ui8NbActivePoints + 1);
}

// A frame's stored LTM (RwFrame +0x50; the hook's node +0x1c, its frame +0x04), read as it is.
const RwMatrix* TargetLtm(IKSerializable* target) {
    return FrameLtm(static_cast<CSGMovable*>(static_cast<IKHook*>(target)->m_pKGLObject)->m_pRwFrame);
}
}  // namespace

// 0x003e03e8 CKWindBeam_PostLoad
int32_t CKWindBeam::PostLoad(int32_t type) {
    CKGrabElement::PostLoad(type);
    HideUnderSector0(m_unk1a4);
    HideUnderSector0(m_unk1f8);
    return 1;
}

// 0x003e0658 CKWindBeam_Start. The state is cleared whether the base started or not (no host test).
void CKWindBeam::Start(CKS08AbilityHostBase* host) {
    m_pLoopSound = nullptr;
    CKGrabElement::Start(host);
    m_unk2a8 = 0;
    m_unk2c0 = 0.0f;
    m_unk2a0 = 0.0f;
    m_unk30c = 0.0f;
    m_unk2b0 = 0;
    m_unk314 = 0;
    m_unk2bc = 0;
    m_unk2c4 = kNullVector;
    m_unk2d0 = kNullVector;
    m_unk2dc[0] = kNullVector.x;  // +0x2dc and +0x2e8 written as two null vectors
    m_unk2dc[1] = kNullVector.y;
    m_unk2dc[2] = kNullVector.z;
    m_unk2dc[3] = kNullVector.x;
    m_unk2dc[4] = kNullVector.y;
    m_unk2dc[5] = kNullVector.z;
    m_unk2f4 = kNullVector;
    m_unk310 = 0;
}

// 0x003e0800 CKWindBeam_End
void CKWindBeam::End(int32_t forced) {
    if (m_pLoopSound != nullptr) {
        Sound_Stop(m_pLoopSound, 0);  // 0x001111b0
        m_pLoopSound = nullptr;
    }
    CVector3 none = kNullVector;
    GrabTarget(0, 0, &none);  // vt+0x7c
    HideUnderSector0(m_unk1a4);
    HideUnderSector0(m_unk1f8);
    CKGrabElement::End(static_cast<uint8_t>(forced));
}

// 0x003e0e38 CKWindBeam_ResetRuntime
void CKWindBeam::ResetRuntime() {
    CKGrabElement::ResetRuntime();
    m_unk2a4 = 0.0f;
    m_unk12c = 2;
    m_unk314 = 0;
    m_unk310 = 0;
    m_unk29c = 0;
    m_unk2a0 = 0.0f;
    m_unk30c = 0.0f;
    m_unk2a8 = 0;
    m_unk2b0 = 0;
    m_pFx208 = nullptr;
    m_pLoopSound = nullptr;
    m_pFx218 = nullptr;
    // The six particle nodes in the original's order (+0x21c, +0x228, +0x220, +0x22c, +0x224, +0x230).
    IKSerializable* const nodes[6] = {m_unk21c[0], m_unk228[0], m_unk21c[1], m_unk228[1], m_unk21c[2], m_unk228[2]};
    for (IKSerializable* object : nodes) {
        CSGLeaf* node = static_cast<CSGLeaf*>(object);
        if (node != nullptr) node->m_sgProperties = (node->m_sgProperties & ~0x8000u) | 0x8000u;
    }
}

// 0x003e02a0 CKWindBeam_GetFxSound_maybe (CKSoundDictionaryID_GetSound 0x00112bc0, CKSound_GetSample_maybe 0x00111000;
// each sound looked up again before it is returned, as the original).
CKSound* CKWindBeam::GetFxSound(int32_t which) {
    CKSoundDictionaryID* sounds = static_cast<CKSoundDictionaryID*>(m_unk28c);
    if (which == 0) return sounds->GetSound(0);
    if (which != 1) return nullptr;
    const auto usable = [sounds](uint32_t i) {
        return sounds->GetSound(i) != nullptr && sounds->GetSound(i)->GetSample() != nullptr;
    };
    if (m_unk04 == 2 && usable(3)) return sounds->GetSound(3);
    if ((m_unk04 == 1 || m_unk04 == 2) && usable(2)) return sounds->GetSound(2);
    return sounds->GetSound(1);
}

// 0x003e0248 CKWindBeam_ApplyDamageParams
void CKWindBeam::ApplyDamageParams(uint8_t continuous) {
    CKGrabElement::ApplyDamageParams(continuous);
    const float angle = m_unk140[m_unk04] * kDegToRad;
    std::memcpy(&static_cast<CKS08ElementDamage*>(m_unk138)->m_unk18, &angle, sizeof(angle));
}

// 0x003e14a0 CKWindBeam_SetFxActive. The effects are the inlined CKSrvFx::AcquireFx (owned by this element); off, they
// are stopped when this element holds them (StopOwnedParticleEffect 0x001cdde8) and released (vt+0x54).
void CKWindBeam::SetFxActive(int32_t on) {
    CKSrvFx* fxService = static_cast<CKSrvFx*>(g_pEngine->m_srvFx);  // TOC +0x429c -> +0x60
    if (on == 0) {
        if (m_pFx208 != nullptr) {
            IKFx* fx = static_cast<IKFx*>(m_pFx208);
            StopOwnedParticleEffect(fx, this);
            fx->ReleaseReservation(this);
            m_pFx208 = nullptr;
        }
        if (m_pFx218 != nullptr) {
            IKFx* fx = static_cast<IKFx*>(m_pFx218);
            StopOwnedParticleEffect(fx, this);
            fx->ReleaseReservation(this);
            m_pFx218 = nullptr;
        }
        CParticlesNodeFx* particles = static_cast<CParticlesNodeFx*>(m_unk21c[m_unk04]);
        if (particles != nullptr) {
            particles->m_sgProperties &= 0xfff7fbffu;
            particles->m_pRpPrtStdEmitter->flag &= ~static_cast<uint32_t>(rpPRTSTDEMITTERFLAGEMIT);
        }
        particles = static_cast<CParticlesNodeFx*>(m_unk228[m_unk04]);
        if (particles != nullptr) {
            particles->m_sgProperties &= 0xfff7fbffu;
            particles->m_pRpPrtStdEmitter->flag &= ~static_cast<uint32_t>(rpPRTSTDEMITTERFLAGEMIT);
        }
        if (m_pLoopSound != nullptr) {
            Sound_Stop(m_pLoopSound, 0);  // 0x001111b0
            m_pLoopSound = nullptr;
        }
        return;
    }
    // The hot spot's effect, then (with the beam mesh) the mesh's.
    CKParticlesEffectFxData* spotData = static_cast<CKParticlesEffectFxData*>(m_unk1fc[m_unk04]);
    spotData->m_pAttachHotSpot = m_pHost->GetHotspot(m_unk12c);  // vt+0xcc
    spotData->m_pAttachOwner = nullptr;
    m_pFx208 = fxService->AcquireFx(static_cast<IKFxData*>(m_unk1fc[m_unk04]), this);
    CNode* beam = static_cast<CNode*>(m_unk1a4);
    if (beam != nullptr) {
        CKParticlesEffectFxData* beamData = static_cast<CKParticlesEffectFxData*>(m_unk20c[m_unk04]);
        beamData->m_pAttachHotSpot = nullptr;
        beamData->m_pAttachOwner = beam;
        m_pFx218 = fxService->AcquireFx(static_cast<IKFxData*>(m_unk20c[m_unk04]), this);
    }
    // The tip mesh under the hot spot, scaled, shown with the level's alpha.
    CNode* tip = static_cast<CNode*>(m_unk1f8);
    if (tip != nullptr) {
        if (tip->m_pParent != nullptr) tip->m_pParent->RemoveChild(tip);  // vt+0x78
        static_cast<CSGHotSpot*>(m_pHost->GetHotspot(m_unk12c))->AttachVolume(tip);  // vt+0xcc, 0x000ce2b8
        tip->Scale(m_unk1cc[m_unk04]);  // 0x000d0d88
        tip->m_sgProperties &= 0xfffffffbu;
        SetMeshAlpha(tip, static_cast<uint8_t>(m_unk1b4[m_unk04]), true);
    }
    // The level's particle nodes emit: properties 0x400 set and 0x80000 cleared, no speed adjustment, the emitter
    // ACTIVE | EMIT.
    IKSerializable* const nodes[2] = {m_unk21c[m_unk04], m_unk228[m_unk04]};
    for (IKSerializable* object : nodes) {
        CParticlesNodeFx* particles = static_cast<CParticlesNodeFx*>(object);
        if (particles == nullptr) continue;
        particles->m_sgProperties = ((particles->m_sgProperties & ~0x400u) | 0x400u) & ~0x80000u;
        particles->m_fEmissionSpeedAdjustment = 0.0f;  // stw 0
        particles->m_pRpPrtStdEmitter->flag |= rpPRTSTDEMITTERFLAGACTIVE | rpPRTSTDEMITTERFLAGEMIT;  // 0xa
    }
    CKSound* start = GetFxSound(0);
    if (start != nullptr) PlayOnUser(start, m_pHost);
    m_pLoopSound = GetFxSound(1);
    if (m_pLoopSound != nullptr) PlayOnUser(m_pLoopSound, m_pHost);
}

// 0x003e0f98 CKWindBeam_GrabTarget_maybe
void CKWindBeam::GrabTarget(uint8_t grab, uint8_t mode, CVector3* direction) {
    if (m_pTarget != nullptr && m_unk310 == 3) {
        // The throw: along the end point's velocity, the damage's push twice its speed over 0.2 s (TOC +0x4288).
        direction->y = m_unk300.y;
        direction->x = m_unk300.x;
        direction->z = m_unk300.z;
        const float speed = LengthYXZ(m_unk300);
        CKS08ElementDamage* damage = static_cast<CKS08ElementDamage*>(m_unk138);
        damage->m_unk10 = (speed + speed) / 0.2f;
        damage->m_unk14 = 0.2f;
    }
    CVector3 copy = *direction;
    CKGrabElement::GrabTarget(grab, mode, &copy);
    if (grab == 0) {
        m_pHost->SetAbilityAttackSpheres(this, 0, 1.0f, nullptr, 1.0f, nullptr);  // vt+0xfc; TOC +0x4274
        m_pHost->SetHeroActionPermission(1, m_unkD8, m_unkE4, m_unk104);         // vt+0x44
        m_pHost->SetHeroActionPermission(0, m_unkD9, m_unkE5, m_unk105);
        return;
    }
    if (m_pTarget == nullptr) return;
    m_unk29c = 0;
    CNode* beam = static_cast<CNode*>(m_unk1a4);
    if (beam != nullptr) {
        beam->SetIdentity();             // 0x000d08f0
        beam->Scale(m_unk17c[m_unk04]);  // 0x000d0d88
        const CVector3 aim = m_pHost->GetTargetAimPoint(0, 0);  // vt+0xdc
        RwFrame* frame = beam->m_pRwFrame;
        frame->modelling.pos.z = aim.z;
        frame->modelling.pos.x = aim.x;
        frame->modelling.pos.y = aim.y;
        frame->modelling.flags &= ~0x20000u;
        RwFrame_MarkDirty(frame);  // 0x00010698
        beam->m_sgProperties &= 0xfffffffbu;
        SetMeshAlpha(beam, static_cast<uint8_t>(m_unk158[m_unk04]), true);
    }
    m_pHost->SetHeroActionPermission(1, 0, 0, 0);
    m_pHost->SetHeroActionPermission(0, 1, 0, 1);
}

// 0x003e08f0 CKWindBeam_Slot80_maybe. The hold: the host keeps the target (GrabEnemy grab 1, mode 1, the null
// direction); lost, permissions 1 / 0 back and 0. The pull: state 0 aims (vt+0x58, the aim cone, pi/2) and waits;
// state 1 sets the damage parameters (vt+0x8c, continuous) and pulls; pulling (2): the aim and the small attack sphere
// with the element damage (vt+0xfc, 0.1) each step, and once the host's pull ratio (vt+0xe8) reaches 1 (cror gt|eq)
// state 3: the throw spheres with the level's stun damage (+0x290), permissions 1 / 0 back, the aim reset (pi, no cone).
uint8_t CKWindBeam::Vf80(float /*dt*/) {
    if (m_unk314 != 0 || m_pTarget == nullptr) return 0;
    const CVector3 none = kNullVector;
    if (m_pHost->GrabEnemy(this, 1, 1, &none, nullptr, nullptr) == 0) {  // vt+0xec
        m_pHost->SetHeroActionPermission(1, m_unkD8, m_unkE4, m_unk104);
        m_pHost->SetHeroActionPermission(0, m_unkD9, m_unkE5, m_unk105);
        return 0;
    }
    if (m_unk310 == 0) m_pHost->ComputeAimDirection(kHalfPi, this, m_unkD0);  // vt+0x58 (the result unused)
    if (m_unk310 == 1) {
        ApplyDamageParams(1);  // vt+0x8c
        m_unk310 = 2;
    } else if (m_unk310 != 2) {
        return 1;
    }
    m_pHost->ComputeAimDirection(kHalfPi, this, m_unkD0);
    m_pHost->SetAbilityAttackSpheres(this, 1, 0.1f, m_unk138, 1.0f, nullptr);  // TOC +0x4270 / +0x4274
    if (m_unk310 == 2 && m_pHost->GetGrabPullRatio(this) >= 1.0f) {
        m_unk310 = 3;
        m_pHost->SetAbilityAttackSpheres(this, 1, 1.0f, nullptr, 1.0f, m_unk290[m_unk04]);
        m_pHost->SetHeroActionPermission(1, m_unkD8, m_unkE4, m_unk104);
        m_pHost->SetHeroActionPermission(0, m_unkD9, m_unkE5, m_unk105);
        m_pHost->ComputeAimDirection(kPi, this, nullptr);
    }
    return 1;
}

// 0x003e0cd8 CKWindBeam_ReleaseAndStopFx_maybe
void CKWindBeam::ReleaseAndStopFx() {
    CKGrabElement::ReleaseAndStopFx();
    CNode* beam = static_cast<CNode*>(m_unk1a4);
    if (beam != nullptr) {
        CGeometry* geometry = static_cast<CGeometry*>(beam->m_lGeometryList);
        m_unk2ac = geometry != nullptr ? geometry->m_cGeometryColor[3] : static_cast<uint32_t>(m_unk14c[m_unk04]);
        if (m_unk1a0 == 0.0f) {  // TOC +0x427c
            HideUnderSector0(beam);
        } else {
            m_unk2a8 = 1;
        }
    }
    CNode* tip = static_cast<CNode*>(m_unk1f8);
    if (tip != nullptr) {
        CGeometry* geometry = static_cast<CGeometry*>(tip->m_lGeometryList);
        m_unk2b4 = geometry != nullptr ? geometry->m_cGeometryColor[3] : static_cast<uint32_t>(m_unk1a8[m_unk04]);
        if (m_unk1f4 == 0.0f) {
            HideUnderSector0(tip);
        } else {
            m_unk2b0 = 1;
        }
    }
    m_unk2a4 = m_unk2a0;
}

// 0x003e1e60 CKWindBeam_Slot84_maybe, the hold step (after Vf80). In three parts:
// 1. The beam mesh (+0x1a4): while pulling (states 2, 3) its alpha goes from the grab's (+0x158) to the full pull's
//    (+0x14c) with the host's pull ratio (vt+0xe8) and it is marked fading; outside the loop phase a fading mesh goes from
//    its release alpha (+0x2ac) to +0x164 over +0x1a0 (BUG(original): the test uses the time since the release, the
//    blend the time since Start) and is then hidden under sector 0's root; every step it spins about its y axis
//    (+0x2a0 x +0x170 degrees, wrapped into -360..360 by steps of 720) at the target's aim point (vt+0xdc), scaled by
//    +0x17c (RwMatrixScalePreConcat_Thunk 0x0023f670).
// 2. The tip mesh (+0x1f8): faded in over +0x1f0 (+0x1b4 -> +0x1a8) in the loop phase, then marked shown (+0x2b0); once
//    the loop is over, faded out over +0x1f4 (+0x2b4 -> +0x1c0; the same time base) and hidden.
// 3. The beam (with the level's particle nodes): the emission phase advances by dt x +0x238 points per point spacing;
//    the end point T (the target's aim point, else the hot spot + the aim cone's reach along the aim); the points grow
//    (+0x2bc up to +0x234) with the time held (+0x2a0 - +0x30c), the first one drawing the curve (two inner control
//    points around the hot spot -> T line at random lengths, angles and rates: 18 Rand_Int draws); the end point flies
//    to its goal (the held enemy's position while it is held and not thrown, else the aim) with the level's
//    acceleration and top speed, braking to arrive; each inner control point turns by its rates within its cone (and
//    away from below), its rates drawn again at the cone's edge or by chance (1 in 10), its length kept in its range
//    and scaled with the beam's reach; then the points along the Bezier are emitted into both particle nodes, and the
//    last one checks that the thrown target can be held at the beam's end (host vt+0xe0; not: +0x314) or starts the
//    pull (state 0 -> 1) once all points are out. The float tests are the original's (cror where it has them; plain
//    blt / bgt / ble / bge otherwise, a NaN taking the branch's C semantics as written).
void CKWindBeam::Vf84(float dt) {
    if (m_unk310 == 2) m_unk30c = dt + m_unk30c;
    m_unk2a0 = m_unk2a0 + dt;

    // 1. The beam mesh.
    CNode* beam = static_cast<CNode*>(m_unk1a4);
    if (beam != nullptr) {
        if (m_unk310 - 2u <= 1u) {
            const float ratio = m_pHost->GetGrabPullRatio(this);  // vt+0xe8
            if (beam->m_lGeometryList != nullptr) {
                const int32_t from = m_unk158[m_unk04];
                const int32_t to = m_unk14c[m_unk04];
                SetMeshAlpha(beam, AlphaByte(ppc::fmadds(ratio, IntToFloat(to - from), IntToFloat(from))));
            }
            m_unk2a8 = 1;
        }
        if (m_unk125 == 0 && m_unk2a8 != 0) {
            const float time = m_unk2a0;
            const float span = m_unk1a0;
            if (time - m_unk2a4 >= span) {  // cror gt|eq
                m_unk2a8 = 0;
                SceneNode_SetVisibleInLayer(beam, 1, 1, 0);  // TocBridge 0x0098f340
            } else if (beam->m_lGeometryList != nullptr) {
                const float tail = IntToFloat(m_unk164[m_unk04]) * (time / span);
                SetMeshAlpha(beam, AlphaByte(ppc::fmadds(UIntToFloat(m_unk2ac), (span - time) / span, tail)));
            }
        }
        // The spin matrix: the identity (flags 0x20003) with the frame's modelling pads.
        const RwMatrix& modelling = beam->m_pRwFrame->modelling;
        CMatrix34 spin;
        std::memcpy(&spin, &modelling, sizeof(spin));
        spin.m_right = CVector3{1.0f, 0.0f, 0.0f};
        spin.m_ui32Flags = 0x20003;
        spin.m_up = CVector3{0.0f, 1.0f, 0.0f};
        spin.m_at = CVector3{0.0f, 0.0f, 1.0f};
        spin.m_pos = CVector3{0.0f, 0.0f, 0.0f};
        float angle = m_unk2a0 * m_unk170[m_unk04];
        while (angle < -360.0f) angle = angle + 720.0f;  // TOC +0x42a0 / +0x42a4
        while (angle >= 360.0f) angle = angle - 720.0f;  // TOC +0x42a8
        Mat4_RotateLocalYDeg(angle, &spin);  // 0x002413d0
        const CVector3 aim = m_pHost->GetTargetAimPoint(0, 0);  // vt+0xdc
        spin.m_pos.x = aim.x;
        spin.m_pos.z = aim.z;
        spin.m_pos.y = aim.y;
        spin.m_ui32Flags &= ~0x20000u;
        RwMatrixScalePreConcat_Thunk(&spin, reinterpret_cast<const CVector3*>(m_unk17c[m_unk04]));  // 0x0023f670
        beam->SetLocalMatrix(reinterpret_cast<const RwMatrix*>(&spin));  // 0x000d0be8
    }

    // 2. The tip mesh.
    CNode* tip = static_cast<CNode*>(m_unk1f8);
    if (tip != nullptr) {
        const float time = m_unk2a0;
        const float fadeIn = m_unk1f0;
        bool toBeam = false;  // 0x3e22ac: straight to the beam (a missing geometry list)
        uint8_t loop = 0;
        bool afterShow = true;  // 0x3e2178 runs (else straight to 0x3e2290)
        if (time < fadeIn && m_unk125 != 0) {
            if (tip->m_lGeometryList == nullptr) {
                toBeam = true;
            } else {
                const float tail = IntToFloat(m_unk1a8[m_unk04]) * (time / fadeIn);
                SetMeshAlpha(tip, AlphaByte(ppc::fmadds(IntToFloat(m_unk1b4[m_unk04]), (fadeIn - time) / fadeIn, tail)));
                loop = m_unk125;
                afterShow = false;
            }
        } else {
            loop = time < fadeIn ? 0 : m_unk125;
        }
        if (!toBeam && afterShow && m_unk2b0 == 0) {
            if (loop == 0) {
                toBeam = true;
            } else {
                if (tip->m_lGeometryList != nullptr) {
                    SetMeshAlpha(tip, AlphaByte(IntToFloat(m_unk1a8[m_unk04])));
                    loop = m_unk125;
                }
                m_unk2b0 = 1;
            }
        }
        if (!toBeam && loop == 0 && m_unk2b0 != 0) {
            const float fadeOut = m_unk1f4;
            if (time >= fadeOut) {  // cror gt|eq
                m_unk2b0 = 0;
                tip->m_sgProperties = (tip->m_sgProperties & 0xfffffffbu) | 4u;
            } else if (tip->m_lGeometryList != nullptr) {
                const float tail = IntToFloat(m_unk1c0[m_unk04]) * (time / fadeOut);
                SetMeshAlpha(tip, AlphaByte(ppc::fmadds(UIntToFloat(m_unk2b4), (fadeOut - time) / fadeOut, tail)));
            }
        }
    }

    // 3. The beam.
    const float reach = static_cast<CKAimCamembert*>(m_unkD0)->m_afUnk04[2];  // the aim cone's +0x0c
    if (m_unk21c[m_unk04] == nullptr && m_unk228[m_unk04] == nullptr) return;
    const uint32_t pointCount = m_unk234;
    const float held = m_unk2a0 - m_unk30c;
    {
        const float spacing = reach / UIntToFloat(pointCount);
        const float phase = (dt * m_unk238[0]) / spacing + m_unk2c0;
        m_unk2c0 = phase - TruncateBits(phase);
    }
    const CVector3 spot = m_pHost->GetHotspotPosition(m_unk12c);  // vt+0xd0
    CVector3 goal;
    if (m_pTarget == nullptr) {
        const CVector3 aim = m_pHost->GetAimDirection(0);  // vt+0x24
        goal.x = ppc::fmadds(reach, aim.x, spot.x);
        goal.y = ppc::fmadds(reach, aim.y, spot.y);
        goal.z = ppc::fmadds(reach, aim.z, spot.z);
    } else {
        goal = m_pHost->GetTargetAimPoint(1, 0);  // vt+0xdc
    }
    CVector3 axis = {goal.x - spot.x, goal.y - spot.y, goal.z - spot.z};
    NormaliseInPlace(&axis);

    // The points grow with the time held; the first one draws the curve.
    uint32_t grown = m_unk2bc;
    if (pointCount > grown && (reach / UIntToFloat(pointCount)) * UIntToFloat(grown) <= held * m_unk238[0]) {
        do {
            if (grown == 0) {
                CMatrix34 basis = {};
                const CVector3 up = m_pHost->GetOwnerUp();  // vt+0x2c
                if (Mat4_SetBasisFromAtUp(&basis, &axis, &up) == 0) {
                    const CVector3 back = Negated(m_pHost->GetHeroForward());  // vt+0x18
                    Mat4_SetBasisFromAtUp(&basis, &axis, &back);
                }
                // The first inner control point: a random turn about z (-90..90) and x (0..-cone), a random length.
                const float rz = WB_RAND_U16() / 65535.0f;
                Mat4_RotateLocalZDeg(ppc::fmadds(rz + rz, -90.0f, 90.0f), &basis);
                Mat4_RotateLocalXDeg(WB_RAND_U16() / -65535.0f * m_unk238[9], &basis);
                const float length0 = WB_RAND_RANGE(m_unk238[10], m_unk238[11]);
                m_unk2c4.z = ppc::fmadds(length0, basis.m_at.z, kNullVector.z);
                m_unk2c4.x = ppc::fmadds(length0, basis.m_at.x, kNullVector.x);
                m_unk2c4.y = ppc::fmadds(length0, basis.m_at.y, kNullVector.y);
                float sign = WB_RAND_SIGN();
                m_unk2dc[0] = sign * WB_RAND_RANGE(m_unk238[7], m_unk238[8]);
                sign = WB_RAND_SIGN();
                m_unk2dc[1] = sign * WB_RAND_RANGE(m_unk238[12], m_unk238[13]);
                sign = WB_RAND_SIGN();
                m_unk2dc[2] = sign * WB_RAND_RANGE(m_unk238[12], m_unk238[13]);
                // The second one, from the other end.
                const CVector3 reverse = Negated(axis);
                const CVector3 up2 = m_pHost->GetOwnerUp();
                if (Mat4_SetBasisFromAtUp(&basis, &reverse, &up2) == 0) {
                    const CVector3 reverse2 = Negated(axis);
                    const CVector3 forward = m_pHost->GetHeroForward();
                    Mat4_SetBasisFromAtUp(&basis, &reverse2, &forward);
                }
                const float rz2 = WB_RAND_U16() / 65535.0f;
                Mat4_RotateLocalZDeg(ppc::fmadds(rz2 + rz2, -90.0f, 90.0f), &basis);
                Mat4_RotateLocalXDeg(WB_RAND_U16() / -65535.0f * m_unk238[16], &basis);
                const float length1 = WB_RAND_RANGE(m_unk238[17], m_unk238[18]);
                m_unk2d0.z = ppc::fmadds(length1, basis.m_at.z, kNullVector.z);
                m_unk2d0.x = ppc::fmadds(length1, basis.m_at.x, kNullVector.x);
                m_unk2d0.y = ppc::fmadds(length1, basis.m_at.y, kNullVector.y);
                sign = WB_RAND_SIGN();
                m_unk2dc[3] = sign * WB_RAND_RANGE(m_unk238[14], m_unk238[15]);
                sign = WB_RAND_SIGN();
                m_unk2dc[4] = sign * WB_RAND_RANGE(m_unk238[19], m_unk238[20]);
                sign = WB_RAND_SIGN();
                const float rate5 = WB_RAND_RANGE(m_unk238[19], m_unk238[20]);
                m_unk2f4 = goal;
                m_unk300 = kNullVector;
                m_unk2dc[5] = sign * rate5;
            }
            grown = grown + 1;
            m_unk2bc = grown;
        } while (pointCount > grown && held * m_unk238[0] >= UIntToFloat(grown) * (reach / UIntToFloat(pointCount)));
    }
    if (grown == 0) return;

    // The end point flies to its goal: the held enemy (held, not thrown), else the hot spot + the reach along the aim.
    const bool tracking = m_pTarget != nullptr && m_unk310 <= 2;
    CVector3 toGoal;
    if (tracking) {
        const RwV3d& target = TargetLtm(m_pTarget)->pos;
        toGoal = CVector3{target.x - m_unk2f4.x, target.y - m_unk2f4.y, target.z - m_unk2f4.z};
    } else {
        const CVector3 aim = m_pHost->GetAimDirection(0);  // vt+0x24
        const float gx = ppc::fmadds(reach, aim.x, spot.x);
        const float gy = ppc::fmadds(reach, aim.y, spot.y);
        const float gz = ppc::fmadds(reach, aim.z, spot.z);
        toGoal = CVector3{gx - m_unk2f4.x, gy - m_unk2f4.y, gz - m_unk2f4.z};
    }
    float lead = 0.0f;  // the first control point's pull along toGoal (a quarter of the distance)
    {
        const float distance = LengthYXZ(toGoal);
        if (distance != 0.0f) {
            const float inv = 1.0f / distance;
            toGoal.z = toGoal.z * inv;
            toGoal.x = toGoal.x * inv;
            toGoal.y = toGoal.y * inv;
            if (distance > 0.1f) {  // TOC +0x4270
                const float speed = LengthYXZ(m_unk300);
                const float acceleration = m_unk238[4 + m_unk04];
                float next;
                if (speed * (speed / acceleration) > distance) {
                    next = speed - dt * acceleration;  // braking
                    if (!(next > 0.0f)) next = 0.0f;
                } else {
                    next = ppc::fmadds(dt, acceleration, speed);
                    const float top = m_unk238[1 + m_unk04];
                    if (next > top) next = top;
                }
                const CVector3 velocity = {next * toGoal.x, next * toGoal.y, next * toGoal.z};
                lead = distance * 0.25f;  // TOC +0x42c4
                m_unk300 = velocity;
                m_unk2f4.x = ppc::fmadds(dt, velocity.x, m_unk2f4.x);
                m_unk2f4.y = ppc::fmadds(dt, velocity.y, m_unk2f4.y);
                m_unk2f4.z = ppc::fmadds(dt, velocity.z, m_unk2f4.z);
            } else {
                lead = distance * 0.25f;
            }
        }
    }
    const float span = std::sqrt(ppc::fmadds(m_unk2f4.z - spot.z, m_unk2f4.z - spot.z,
                                             ppc::fmadds(m_unk2f4.x - spot.x, m_unk2f4.x - spot.x,
                                                         (m_unk2f4.y - spot.y) * (m_unk2f4.y - spot.y))));
    uint32_t emitCount = grown;
    if (tracking) {
        // Held: as many points as the beam's growth covers at the current length, at most +0x234 (fctidz, low word).
        const float total = UIntToFloat(pointCount);
        const float reachable = (held * m_unk238[0]) / (span / total);
        emitCount = static_cast<uint32_t>(ppc::fctidz(total < reachable ? total : reachable));
    }

    // The first inner control point (+0x2c4) turns in the frame of the beam's axis.
    {
        const float length = LengthYXZ(m_unk2c4);
        NormaliseInPlace(&m_unk2c4);
        CMatrix34 basis = {};
        if (Mat4_SetBasisFromAtUp(&basis, &axis, &m_unk2c4) == 0) {
            const CVector3 up = m_pHost->GetOwnerUp();  // vt+0x2c
            if (Mat4_SetBasisFromAtUp(&basis, &axis, &up) == 0) {
                const CVector3 forward = m_pHost->GetHeroForward();  // vt+0x18
                Mat4_SetBasisFromAtUp(&basis, &axis, &forward);
            }
        }
        CMatrix34 inverse = {};
        Mat4_Invert(&inverse, &basis);
        CVector3 local;
        Mat4_TransformVectors(&inverse, &local, &m_unk2c4, 1);
        NormaliseInPlace(&local);
        float cosine = local.z;
        if (cosine <= -1.0f) {
            cosine = -1.0f;
        } else if (cosine >= 1.0f) {
            cosine = 1.0f;
        }
        const float angle = crt::Acosf(cosine);  // TocBridge 0x0098e1a0
        const float cone = m_unk238[9] * kDegToRad;
        float turnX = (dt * m_unk2dc[2]) / length;
        const float turnZ = (dt * m_unk2dc[1]) / length;
        if (!(cone <= angle)) {
            if (angle < kTenDegrees) {
                m_unk2dc[2] = WB_REDRAW_RATE(m_unk2dc[2], m_unk238[12], m_unk238[13]);
                turnX = -std::fabs(turnX);
            }
        } else {
            m_unk2dc[2] = WB_REDRAW_RATE(m_unk2dc[2], m_unk238[12], m_unk238[13]);
            turnX = std::fabs(turnX);
        }
        Mat4_RotateLocalZDeg(turnZ, &basis);
        Mat4_RotateLocalXDeg(turnX, &basis);
        Mat4_TransformVectors(&basis, &m_unk2c4, &local, 1);
        // --fps N (not in the original): the 10% roll once per 60 Hz frame (none in a displayed frame that ends none).
        if (m_unk2c4.y < 0.0f || ((!dotd::fps::Unlocked() || dotd::fps::Ticks() > 0) && WB_RAND_U16() / 65535.0f < 0.1f)) {
            Mat4_RotateLocalZDeg(-turnZ, &basis);
            Mat4_TransformVectors(&basis, &m_unk2c4, &local, 1);
            m_unk2dc[1] = WB_REDRAW_RATE(m_unk2dc[1], m_unk238[12], m_unk238[13]);
        }
        const float grownLength = ppc::fmadds(dt, m_unk2dc[0], length);
        if (m_unk238[10] - m_unk238[11] > grownLength || m_unk238[10] + m_unk238[11] < grownLength) {
            m_unk2dc[0] = WB_REDRAW_RATE(m_unk2dc[0], m_unk238[7], m_unk238[8]);
        }
        const float low = m_unk238[10] - m_unk238[11];
        const float want = grownLength * (span / reach);
        float kept;
        if (want <= low) {
            kept = low;
        } else if (want >= m_unk238[10] + m_unk238[11]) {
            kept = m_unk238[10] + m_unk238[11];
        } else {
            kept = want;
        }
        ScaleToLength(&m_unk2c4, kept);
    }

    // The second inner control point (+0x2d0), in the frame of the reversed axis; at a fog horn it is laid along the
    // horn's frame instead (and the end point onto its aim point).
    {
        const float length = LengthYXZ(m_unk2d0);
        NormaliseInPlace(&m_unk2d0);
        CMatrix34 basis = {};
        const CVector3 reverse = Negated(axis);
        if (Mat4_SetBasisFromAtUp(&basis, &reverse, &m_unk2d0) == 0) {
            const CVector3 reverse2 = Negated(axis);
            const CVector3 up = m_pHost->GetOwnerUp();
            if (Mat4_SetBasisFromAtUp(&basis, &reverse2, &up) == 0) {
                const CVector3 reverse3 = Negated(axis);
                const CVector3 forward = m_pHost->GetHeroForward();
                Mat4_SetBasisFromAtUp(&basis, &reverse3, &forward);
            }
        }
        CMatrix34 inverse = {};
        Mat4_Invert(&inverse, &basis);
        CVector3 local;
        Mat4_TransformVectors(&inverse, &local, &m_unk2d0, 1);
        NormaliseInPlace(&local);
        float cosine = local.z;
        if (cosine <= -1.0f) {
            cosine = -1.0f;
        } else if (cosine >= 1.0f) {
            cosine = 1.0f;
        }
        const float angle = crt::Acosf(cosine);
        const float cone = m_unk238[16] * kDegToRad;
        float turnX = (dt * m_unk2dc[5]) / length;
        const float turnZ = (dt * m_unk2dc[4]) / length;
        if (!(cone <= angle)) {
            if (angle < kTenDegrees) {
                m_unk2dc[5] = WB_REDRAW_RATE(m_unk2dc[5], m_unk238[19], m_unk238[20]);
                turnX = -std::fabs(turnX);
            }
        } else {
            m_unk2dc[5] = WB_REDRAW_RATE(m_unk2dc[5], m_unk238[19], m_unk238[20]);
            turnX = std::fabs(turnX);
        }
        Mat4_RotateLocalZDeg(turnZ, &basis);
        Mat4_RotateLocalXDeg(turnX, &basis);
        Mat4_TransformVectors(&basis, &m_unk2d0, &local, 1);
        if (m_unk2d0.y < 0.0f || ((!dotd::fps::Unlocked() || dotd::fps::Ticks() > 0) && WB_RAND_U16() / 65535.0f < 0.1f)) {
            Mat4_RotateLocalZDeg(-turnZ, &basis);
            Mat4_TransformVectors(&basis, &m_unk2d0, &local, 1);
            m_unk2dc[4] = WB_REDRAW_RATE(m_unk2dc[4], m_unk238[19], m_unk238[20]);
        }
        const float grownLength = ppc::fmadds(dt, m_unk2dc[3], length);
        if (m_unk238[17] - m_unk238[18] > grownLength || m_unk238[17] + m_unk238[18] < grownLength) {
            m_unk2dc[3] = WB_REDRAW_RATE(m_unk2dc[3], m_unk238[14], m_unk238[15]);
        }
        float want;
        if (m_pTarget != nullptr && m_pTarget->IsKindOfClass(0x2f02) != 0) {  // vt+0x08: CKHkS08FogHorn
            m_unk2f4 = m_pHost->GetTargetAimPoint(1, 0);  // vt+0xdc
            const RwMatrix* ltm = TargetLtm(m_pTarget);
            CVector3 side = {kNullVector.x - ltm->at.x, kNullVector.y - ltm->at.y, kNullVector.z - ltm->at.z};
            side.z = ppc::fmadds(ltm->up.z, 0.5f, side.z);  // TOC +0x42cc
            side.x = ppc::fmadds(ltm->up.x, 0.5f, side.x);
            side.y = ppc::fmadds(ltm->up.y, 0.5f, side.y);
            side.x = ppc::fmadds(ltm->right.x, -0.1f, side.x);  // TOC +0x42d0
            side.y = ppc::fmadds(ltm->right.y, -0.1f, side.y);
            side.z = ppc::fmadds(ltm->right.z, -0.1f, side.z);
            m_unk2d0 = side;
            NormaliseInPlace(&m_unk2d0);
            m_unk2f4.x = m_unk2f4.x + m_unk2d0.x;
            m_unk2f4.y = m_unk2f4.y + m_unk2d0.y;
            m_unk2f4.z = m_unk2f4.z + m_unk2d0.z;
            const RwMatrix* ltm2 = TargetLtm(m_pTarget);
            m_unk2f4.z = ppc::fmadds(ltm2->right.z, 0.3f, m_unk2f4.z);  // TOC +0x42d4
            m_unk2f4.x = ppc::fmadds(ltm2->right.x, 0.3f, m_unk2f4.x);
            m_unk2f4.y = ppc::fmadds(ltm2->right.y, 0.3f, m_unk2f4.y);
            want = m_unk238[17] + m_unk238[18];
        } else {
            want = (span / reach) * grownLength;
        }
        const float low = m_unk238[17] - m_unk238[18];
        float kept;
        if (want <= low) {
            kept = low;
        } else if (want >= m_unk238[17] + m_unk238[18]) {
            kept = m_unk238[17] + m_unk238[18];
        } else {
            kept = want;
        }
        ScaleToLength(&m_unk2d0, kept);
    }

    // The Bezier: the hot spot, the hot spot + the first control point + lead along toGoal, the end point + the second
    // control point, the end point.
    const CVector3 control1 = {ppc::fmadds(toGoal.x, lead, spot.x + m_unk2c4.x),
                               ppc::fmadds(toGoal.y, lead, spot.y + m_unk2c4.y),
                               ppc::fmadds(toGoal.z, lead, spot.z + m_unk2c4.z)};
    const CVector3 control2 = {m_unk2f4.x + m_unk2d0.x, m_unk2f4.y + m_unk2d0.y, m_unk2f4.z + m_unk2d0.z};
    if (emitCount == 0) return;
    for (uint32_t i = 0; i != emitCount; ++i) {
        const float t = (UIntToFloat(i) + m_unk2c0) / UIntToFloat(m_unk234);
        CVector3 point;
        Vec3_CubicBezier(t, &point, &spot, &control1, &control2, &m_unk2f4);  // 0x00010fc0
        EmitPoint(m_unk21c[m_unk04], point);
        EmitPoint(m_unk228[m_unk04], point);
        if (i != emitCount - 1 || m_pTarget == nullptr) continue;
        if (m_unk310 == 3) {
            // Thrown: the beam's end at the growth so far (clamped 0..1) must be a place the target can be held.
            float along = (held * m_unk238[0]) / reach;
            if (along <= 0.0f) {
                along = 0.0f;
            } else if (along >= 1.0f) {
                along = 1.0f;
            }
            CVector3 end;
            Vec3_CubicBezier(along, &end, &spot, &control1, &control2, &m_unk2f4);
            CVector3 place = end;
            if (m_pHost->CanGrabTarget(this, m_pTarget, &place) == 0) m_unk314 = 1;  // vt+0xe0
        } else if (m_unk234 - 1 == emitCount - 1 && m_unk310 == 0) {
            m_unk310 = 1;  // every point is out: the pull starts
        }
    }
}
