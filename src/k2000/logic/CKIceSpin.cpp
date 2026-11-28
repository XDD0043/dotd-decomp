// CKIceSpin.cpp - reconstructed original translation unit 0x3abec0-0x3b47b8 (GAME_TOC1, main_toc1), 29 functions, 29 live.
// Primary class: CKIceSpin  key 0x988c  category Logic  size 0x33c  vtable 0xb23c10
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x3abec0  CKIceSpin_Delete
//   [x] 0x3abf10  CKIceSpin_GetAbilityId
//   [x] 0x3abf18  CKIceSpin_GetFamilyId
//   [x] 0x3abf20  CKIceSpin_IsGroundTrailActive_maybe
//   [x] 0x3abf80  CKIceSpin_GetFxSound_maybe
//   [x] 0x3ac188  CKIceSpin_ApplyHeroControl
//   [x] 0x3ac1b0  CKIceSpin_End
//   [x] 0x3ac318  CKIceSpin_ResetRuntime
//   [x] 0x3ac3f8  CKIceSpin_RecursiveRegistration  (inherited: CKTransformElement_RecursiveRegistration)
//   [x] 0x3ac420  CKIceSpin_Destroy  (inherited: CKTransformElement_Destroy)
//   [x] 0x3ac448  CKIceSpin_DeletingDestructor  (C++ destructor chain: vtable stores only)
//   [x] 0x3ac490  CKIceSpin_Destructor  (C++ destructor chain: vtable stores only)
//   [x] 0x3ac4c0  CKIceSpin_DestructBody  (C++ destructor chain: vtable stores only)
//   [x] 0x3ac4f0  CKIceSpin_Construct
//   [x] 0x3ac528  CKIceSpin_Construct_2  (the same as 0x3ac4f0 CKIceSpin_Construct)
//   [x] 0x3ac560  CKIceSpin_DeleteArray
//   [x] 0x3ac600  CKIceSpin_PostLoad
//   [ ] 0x3ac750  RegisterCKIceSpinClass
//   [ ] 0x3ac7d8  _GLOBAL__D_3ac7d8
//   [ ] 0x3ac7e8  _GLOBAL__I_3ac7e8
//   [x] 0x3ac7f8  CKIceSpin_StopFx
//   [x] 0x3aca48  CKIceSpin_CreateArray
//   [x] 0x3acaf8  CKIceSpin_Create
//   [x] 0x3acb50  CKIceSpin_Start
//   [x] 0x3ad010  CKIceSpin_Load
//   [ ] 0x3af0f8  CKIceSpin_Save
//   [x] 0x3b0e60  CKIceSpin_UpdateAttack_maybe
//   [x] 0x3b1848  CKIceSpin_UpdateEffect_maybe
//   [x] 0x3b3668  CKIceSpin_SetFxActive
//
//   [ ] 0x9bffc0  CKIceSpin_IsKindOfClass  [inline]
//   [ ] 0x9c0010  CKIceSpin_GetClassType  [inline]
//   [ ] 0x9c0018  CKIceSpin_GetClassID  [inline]
//   [x] 0x9c0020  CKIceSpin_StartEmitterFx  [inline]
#include "k2000/logic/CKIceSpin.h"

#include <cmath>
#include <cstring>

#include "Renderware/rwcore/RwCamera.h"
#include "Spyro2008/logic/CKS08ElementDamage.h"
#include "Spyro2008/misc/CKS08AbilityHostBase.h"
#include "crt/ppc_ops.h"
#include "crt/xsinf.h"
#include "k2000/components/CKImpulsionCpnt.h"
#include "k2000/dictionaries/CKSoundDictionaryID.h"
#include "k2000/fx/CKSparkFxData.h"
#include "k2000/fx/IKFx.h"
#include "k2000/geometry/CGeometry.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKParticlesEffectFxData.h"
#include "k2000/logic/CKProjectileAccessor.h"
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/logic/fx/CKAnimatedFxCollection.h"
#include "k2000/logic/render/CKMeshPopFxData.h"
#include "k2000/logic/render/CKMeshPopNodeFx.h"
#include "k2000/logic/render/CKPointLightFxData.h"
#include "k2000/logic/sound/CKSound.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/math/Math.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/Mat4.h"
#include "k2000/scenegraph/CNode.h"
#include "k2000/scenegraph/CSGBranch.h"
#include "k2000/scenegraph/CSGLeaf.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/scenegraph/CTrailNodeFx.h"

namespace {
// The helpers are in this anonymous namespace so that the rand log (DOTD_REPLAY_RANDLOG) names the inlining function
// (CKIceSpin::UpdateEffect) for their draws, as the original makes them.
constexpr float kRandMax = 65535.0f;          // TOC +0x3a40 (0x477fff00)
constexpr float kRandScale = -0x1.0001p-15f;  // TOC +0x3a64 (0xb8000080, -1 / 32767.5)
constexpr float kDegToRad = 0x1.1df468p-6f;   // TOC +0x3a60 (0x3c8efa34)
constexpr float kDashTopMargin = 0x1.99999ap-5f;  // TOC +0x3a3c (0x3d4ccccd, 0.05)
// 0x00c50d40 (TOC +0x3a54): the shared Y axis; 0x00c50d64 (TOC +0x3a38): the null vector (zero in the EBOOT's BSS,
// filled by static initialisers).
const CVector3 kAxisY = {0.0f, 1.0f, 0.0f};
const CVector3 kNullVector = {0.0f, 0.0f, 0.0f};

// One Rand_Int draw, its low 16 bits as a float (clrldi 48, fcfid, frsp).
float RandUnit16() { return static_cast<float>(static_cast<double>(static_cast<uint32_t>(Rand_Int()) & 0xffffu)); }
// 0x00010690 Math_Sqrtf
float Sqrtf(float x) { return static_cast<float>(std::sqrt(static_cast<double>(x))); }
// (float) of a word read with lwz then extsw (signed) / clrldi (unsigned): fcfid, frsp.
float SignedToFloat(int32_t word) { return static_cast<float>(static_cast<double>(word)); }
float UnsignedToFloat(uint32_t word) { return static_cast<float>(static_cast<double>(word)); }
// The alpha byte of a float (fctiwz, the low byte through stfiwx / lbz).
uint8_t AlphaByte(float value) { return static_cast<uint8_t>(ppc::fctiwz(value)); }
// The inlined cosf / sinf: a negative argument (its sign bit tested through memory) goes to the library's.
float GameCosf(float x) { return std::signbit(x) ? crt::LibCosf(-x) : crt::InlineCosf(x); }   // 0x009a11d8
float GameSinf(float x) { return std::signbit(x) ? -crt::LibSinf(-x) : crt::InlineSinf(x); }  // 0x009a1390
// A spin angle brought into [-360, 360) by steps of 720 (TOC +0x3a48 / +0x3a4c / +0x3a50).
float WrapDegrees(float angle) {
    if (angle < -360.0f) {
        do {
            angle = angle + 720.0f;
        } while (angle < -360.0f);
    }
    if (angle >= 360.0f) {
        do {
            angle = angle - 720.0f;
        } while (angle >= 360.0f);
    }
    return angle;
}
// A node the effect still draws: hung somewhere and not hidden (scene flag 4).
bool IsShownUnderParent(IKSerializable* node) {
    if (node == nullptr) return false;
    CSGLeaf* leaf = static_cast<CSGLeaf*>(node);
    return leaf->m_pParent != nullptr && (leaf->m_sgProperties & 4u) == 0;
}
CGeometry* FirstGeometry(IKSerializable* node) {
    return static_cast<CGeometry*>(static_cast<CNode*>(node)->m_lGeometryList);
}
// A node hung under the user's hot spot +0x13c: shown, taken from its parent (vt+0x78), attached (0x000ce2b8).
void HangUnderHotSpot(IKSerializable* node, CKS08AbilityHostBase* host, uint8_t hotSpot) {
    CSGLeaf* leaf = static_cast<CSGLeaf*>(node);
    if (leaf->m_pParent != nullptr) leaf->m_pParent->RemoveChild(leaf);  // vt+0x78
    static_cast<CSGHotSpot*>(host->GetHotspot(hotSpot))->AttachVolume(leaf);  // vt+0xcc
}
// The node's scale this frame: `scale` x (1 + `spread` x a draw in [-1, 1]) (one Rand_Int).
float RandomScale(float spread, float scale) {
    const float base = spread + 1.0f;  // TOC +0x39a8
    const float t = RandUnit16() / kRandMax * -2.0f;  // 0x00011500; TOC +0x3a44
    return ppc::fmadds(t, spread, base) * scale;
}
// The node's frame: the inverse of the parent's modelling matrix turned to the world up (its at row kept as the
// forward), placed at the node's own x / z and `y`, scaled by `scale`, turned about its y by -`spin` degrees
// (CSGMovable_SetLocalMatrix_maybe 0x000d0be8). The frame's pads are kept (the matrix starts as its copy).
void PlaceNode(IKSerializable* node, float y, float spin, float scale) {
    CSGMovable* movable = static_cast<CSGMovable*>(node);
    CMatrix34 matrix;
    std::memcpy(&matrix, &movable->m_pRwFrame->modelling, sizeof(matrix));
    const float x = matrix.m_pos.x;
    const float z = matrix.m_pos.z;
    matrix.m_right = CVector3{1.0f, 0.0f, 0.0f};
    matrix.m_ui32Flags = 0x20003u;
    matrix.m_up = CVector3{0.0f, 1.0f, 0.0f};
    matrix.m_at = CVector3{0.0f, 0.0f, 1.0f};
    matrix.m_pos = CVector3{0.0f, 0.0f, 0.0f};
    CSGMovable* parent = static_cast<CSGMovable*>(static_cast<IKSerializable*>(static_cast<CSGLeaf*>(node)->m_pParent));
    Mat4_Invert(&matrix, reinterpret_cast<const CMatrix34*>(&parent->m_pRwFrame->modelling));  // 0x0023f878
    Mat4_BuildFromUpAndForward(&matrix, &kAxisY, &matrix.m_at);                                 // 0x0023ff80
    matrix.m_pos = CVector3{x, y, z};
    matrix.m_ui32Flags &= ~0x20000u;
    matrix.m_right = CVector3{scale * matrix.m_right.x, scale * matrix.m_right.y, scale * matrix.m_right.z};
    matrix.m_up = CVector3{scale * matrix.m_up.x, scale * matrix.m_up.y, scale * matrix.m_up.z};
    matrix.m_at = CVector3{scale * matrix.m_at.x, scale * matrix.m_at.y, scale * matrix.m_at.z};
    matrix.m_ui32Flags &= 0xfffdfffeu;
    Mat4_RotateLocalYDeg(-spin, &matrix);                                         // 0x002413d0
    movable->SetLocalMatrix(reinterpret_cast<const RwMatrix*>(&matrix));          // 0x000d0be8
}

// One ground ring (B or C): its fade, its alpha with the user's height, its frame. `flag` is its +0x328 byte; the
// alpha only changes when it differs from the first geometry's.
struct SRingData {
    IKSerializable* node;
    uint8_t* flag;
    float fadeIn;
    int32_t fullAlpha;
    int32_t startAlpha;
    float fadeOut;
    int32_t endAlpha;
    uint32_t stopAlpha;
    float low;
    float high;
    float spread;
    float spin;
    float scale;
};
void UpdateRing(CKIceSpin* self, const SRingData& ring) {
    const float now = self->m_fEffectTimer;
    float alpha = SignedToFloat(ring.fullAlpha);
    if (now < ring.fadeIn && self->m_bLoop != 0) {
        // The fade-in, from the start alpha.
        const float done = now / ring.fadeIn;
        const float rest = (ring.fadeIn - now) / ring.fadeIn;
        alpha = ppc::fmadds(SignedToFloat(ring.startAlpha), rest, alpha * done);
    } else if (self->m_bLoop != 0) {
        if (*ring.flag == 0) *ring.flag = 1;
    } else if (*ring.flag != 0) {
        // The fade-out once the loop is over; the ring is hidden at its end (and still placed this frame).
        // BUG(original): the time is the whole timer, not the time since StopFx (node A uses +0x310; the rings don't).
        if (now >= ring.fadeOut) {
            *ring.flag = 0;
            TransformFx::HideNode(ring.node);
        }
        const float rest = (ring.fadeOut - self->m_fEffectTimer) / ring.fadeOut;
        const float done = self->m_fEffectTimer / ring.fadeOut;
        alpha = ppc::fmadds(UnsignedToFloat(ring.stopAlpha), rest, SignedToFloat(ring.endAlpha) * done);
    }
    // The user's height above the ground under it (host vt+0x10 / +0x14): invisible above `high`, fading from `low`.
    const CVector3 position = self->m_pHost->GetOwnerPosition();
    const CVector3 ground = self->m_pHost->GetOwnerGroundPoint();
    const float height = position.y - ground.y;
    uint8_t value = 0;
    if (height > ring.high) {
        value = 0;
    } else if (height >= ring.low) {
        value = AlphaByte(alpha * ((ring.high - height) / (ring.high - ring.low)));
    } else {
        value = AlphaByte(alpha);
    }
    // The original reads the first geometry's alpha before it tests the list (never empty for these nodes).
    CGeometry* first = FirstGeometry(ring.node);
    if (first != nullptr && value != first->m_cGeometryColor[3]) TransformFx::SetGeometriesAlpha(ring.node, value);
    const float spin = WrapDegrees(ring.spin * self->m_fEffectTimer);
    const float scale = RandomScale(ring.spread, ring.scale);
    PlaceNode(ring.node, -height, spin, scale);
}

// Node A: its fade (+0x16c -> +0x160 over +0x194 while the loop runs; after StopFx +0x31c -> +0x178 over +0x198,
// then hidden) and its frame at its own height.
void UpdateTopNode(CKIceSpin* self) {
    IKSerializable* node = self->m_pNodeA;
    const uint32_t level = static_cast<uint32_t>(self->m_levelIndex);
    const float now = self->m_fEffectTimer;
    if (self->m_bLoop != 0) {
        if (now < self->m_fNodeAFadeInTime) {
            if (FirstGeometry(node) != nullptr) {
                const float done = now / self->m_fNodeAFadeInTime;
                const float rest = (self->m_fNodeAFadeInTime - now) / self->m_fNodeAFadeInTime;
                TransformFx::SetGeometriesAlpha(node, AlphaByte(ppc::fmadds(SignedToFloat(self->m_ai32NodeAStartAlpha[level]), rest,
                                                                            SignedToFloat(self->m_ai32NodeAFullAlpha[level]) * done)));
            }
        } else if (self->m_abNodeFadeState[0] == 0) {
            if (FirstGeometry(node) != nullptr) {
                TransformFx::SetGeometriesAlpha(node, AlphaByte(SignedToFloat(self->m_ai32NodeAFullAlpha[level])));
            }
            self->m_abNodeFadeState[0] = 1;
        }
    } else if (self->m_abNodeFadeState[0] != 0) {
        if (now - self->m_fStopFxTime >= self->m_fNodeAFadeOutTime) {
            self->m_abNodeFadeState[0] = 0;
            TransformFx::HideNode(node);
        } else if (FirstGeometry(node) != nullptr) {
            // BUG(original): the alpha runs on the whole timer, not on the time since the fade-out started.
            const float rest = (self->m_fNodeAFadeOutTime - now) / self->m_fNodeAFadeOutTime;
            const float done = now / self->m_fNodeAFadeOutTime;
            TransformFx::SetGeometriesAlpha(node, AlphaByte(ppc::fmadds(UnsignedToFloat(self->m_unk31c), rest,
                                                                        SignedToFloat(self->m_ai32NodeAEndAlpha[level]) * done)));
        }
    }
    const float y = static_cast<CSGMovable*>(node)->m_pRwFrame->modelling.pos.y;
    const float spin = WrapDegrees(self->m_afNodeASpinDegPerSec[level] * self->m_fEffectTimer);
    const float scale = RandomScale(self->m_fNodeAScaleWobble, self->m_afNodeAScale[level]);
    PlaceNode(node, y, spin, scale);
}

// The level 2 shard: thrown from the hot spot +0x13c (+0x2f8 higher) within +-+0x300 / 2 degrees of the user's forward
// (vt+0x18; the user's right vt+0x28), its direction's y set to +0x2fc, at a speed between +0x2e8 and +0x2ec with the
// dash's value; one of the two accessors by a draw (each only when it has a type); the next one in +0x2f0 +- +0x2f4
// seconds of the scaled timer. Three Rand_Int draws.
void ThrowShard(CKIceSpin* self) {
    CKImpulsionCpnt* dash = static_cast<CKImpulsionCpnt*>(self->m_pDashImpulsion);
    const float value = self->m_fDashTimeScale;
    const float bottom = dash->m_unk04[1];
    const float top = dash->m_unk04[0];
    CVector3 direction = kNullVector;
    const float half = ppc::fmadds(self->m_fShardConeDeg, 0.5f, 0.0f);  // TOC +0x3a58
    const float range = top - bottom;
    const float speed = ppc::fmadds((top - value) / range, self->m_fShardSpeedMin, (value - bottom) / range * self->m_fShardSpeedMax);
    const float draw = RandUnit16();  // 0x00011500
    const CVector3 forward = self->m_pHost->GetHeroForward();  // vt+0x18
    float spread = draw / kRandMax;
    spread = spread + spread;
    spread = spread * self->m_fShardConeDeg;
    const float angle = ppc::fmadds(spread, -0.5f, half) * kDegToRad;  // TOC +0x3a5c
    const float c = GameCosf(angle);
    direction.x = ppc::fmadds(c, forward.x, direction.x);
    direction.z = ppc::fmadds(c, forward.z, direction.z);
    direction.y = ppc::fmadds(c, forward.y, direction.y);
    const CVector3 right = self->m_pHost->GetOwnerRight();  // vt+0x28
    const float s = GameSinf(angle);
    direction.y = ppc::fmadds(s, right.y, direction.y);
    direction.x = ppc::fmadds(s, right.x, direction.x);
    direction.z = ppc::fmadds(s, right.z, direction.z);
    const float length = Sqrtf(ppc::fmadds(direction.z, direction.z,
                                           ppc::fmadds(direction.x, direction.x, direction.y * direction.y)));
    if (length != 0.0f) {
        const float inverse = 1.0f / length;
        direction.z = direction.z * inverse;
        direction.x = direction.x * inverse;
        direction.y = direction.y * inverse;
    }
    direction.y = self->m_fShardDirY;
    const CVector3 spot = self->m_pHost->GetHotspotPosition(self->m_ui8HotSpot);  // vt+0xd0
    const CVector3 start = {spot.x, spot.y + self->m_fShardHeightOffset, spot.z};
    // fmadds(r, -1 / 32767.5, 1) below 0 (blt; a NaN is not) takes the second accessor.
    const uint8_t second = ppc::fmadds(RandUnit16(), kRandScale, 1.0f) < 0.0f ? 1 : 0;
    CKProjectileAccessor* first = static_cast<CKProjectileAccessor*>(self->m_pShardAccessorA);
    if (first->m_pProjectileType != nullptr && second == 0) {
        first->LaunchEx(&start, &direction, speed, self->m_pShardDamage, self->m_pHost->GetOwner(), nullptr);  // 0x001f2988
    }
    CKProjectileAccessor* other = static_cast<CKProjectileAccessor*>(self->m_pShardAccessorB);
    if (other->m_pProjectileType != nullptr && second != 0) {
        other->LaunchEx(&start, &direction, speed, self->m_pShardDamage, self->m_pHost->GetOwner(), nullptr);
    }
    const float base = self->m_fShardIntervalSpread + 0.0f;
    const float wait = self->m_fShardInterval;
    const float t = RandUnit16() / kRandMax * -2.0f;
    self->m_fNextShardTimer = (wait + ppc::fmadds(t, self->m_fShardIntervalSpread, base)) / self->m_fDashTimeScale;
}
}  // namespace

// 0x003ac318 CKIceSpin_ResetRuntime
void CKIceSpin::ResetRuntime() {
    CKTransformElement::ResetRuntime();
    m_fDashTimeScale = 1.0f;  // TOC +0x39a8
    m_ui8HotSpot = 0;
    m_pActivePointLight = nullptr;
    m_unk330 = 0;
    m_pActiveDashTopSparks = nullptr;
    m_pActiveLoopParticles = nullptr;
    m_pActiveDashParticles = nullptr;
    m_pActiveMeshPopFx = nullptr;
    m_fEffectTimer = 0.0f;
    m_fStopFxTime = 0.0f;
    m_fUnusedTimer2 = 0.0f;
    m_fNextShardTimer = 0.0f;
    m_abNodeFadeState[0] = 0;
    m_abNodeFadeState[1] = 0;
    m_abNodeFadeState[2] = 0;
    m_pLoopSound = nullptr;
    m_pDashSound = nullptr;
    m_pActiveAnimFx = nullptr;
    static_cast<CKS08ElementDamage*>(m_pShardDamage)->SetAbilityId(GetAbilityId());  // vt+0x68
}

// 0x003abf20 CKIceSpin_IsGroundTrailActive_maybe
uint8_t CKIceSpin::IsGroundTrailActive() {
    if (m_levelIndex == 0) return 0;
    return m_pHost->IsOnGround();  // vt+0x30
}

// 0x003abf80 CKIceSpin_GetFxSound_maybe
CKSound* CKIceSpin::GetFxSound(uint32_t which) {
    CKSoundDictionaryID* sounds = static_cast<CKSoundDictionaryID*>(m_pSoundDico);
    auto usable = [sounds](uint32_t index) {
        return sounds->GetSound(index) != nullptr && sounds->GetSound(index)->GetSample() != nullptr;  // 0x00111000
    };
    if (which == 3) {
        if (m_levelIndex != 1) {
            if (m_levelIndex != 2) return nullptr;
            if (usable(5)) return sounds->GetSound(5);
        }
        if (usable(4)) return sounds->GetSound(4);
        return nullptr;
    }
    if (which == 4) return sounds->GetSound(3);
    if (which != 1) return nullptr;
    if (m_levelIndex == 1 || m_levelIndex == 2) {
        if (m_levelIndex == 2 && usable(2)) return sounds->GetSound(2);
        if (usable(1)) return sounds->GetSound(1);
    }
    return sounds->GetSound(0);
}

// 0x003ac188 CKIceSpin_ApplyHeroControl
void CKIceSpin::ApplyHeroControl(uint8_t on) { CKTransformElement::ApplyHeroControl(on); }

// 0x003ac1b0 CKIceSpin_End
void CKIceSpin::End(int32_t forced) {
    m_pHost->SetHero1d20(1.0f);  // vt+0x84; TOC +0x39a8
    if (m_pLoopSound != nullptr) {
        m_pLoopSound->Stop(0);  // 0x001111b0
        m_pLoopSound = nullptr;
    }
    if (m_pDashSound != nullptr) {
        m_pDashSound->Stop(0);
        m_pDashSound = nullptr;
    }
    CKTransformElement::End(forced);
    SceneNode_SetVisibleInLayer(static_cast<CSGLeaf*>(m_pNodeA), 1, 0, 0);  // 0x005832a8 (through its TocBridge)
    SceneNode_SetVisibleInLayer(static_cast<CSGLeaf*>(m_pRingB), 1, 0, 0);
    SceneNode_SetVisibleInLayer(static_cast<CSGLeaf*>(m_pRingC), 1, 0, 0);
    TransformFx::ReleaseMeshPop(&m_pActiveMeshPopFx, this);  // CKMeshPopNodeFx_SetActive_maybe 0x001cb568, vt+0x54
}

// 0x003acb50 CKIceSpin_Start
void CKIceSpin::Start(CKS08AbilityHostBase* host) {
    m_pDashSound = nullptr;
    m_pLoopSound = nullptr;
    CKTransformElement::Start(host);
    if (m_pNodeA != nullptr) {
        TransformFx::ShowNode(m_pNodeA);
        // The low byte of the level's word (lbz +3).
        TransformFx::SetGeometriesAlpha(m_pNodeA, static_cast<uint8_t>(m_ai32NodeAStartAlpha[m_levelIndex]));
        HangUnderHotSpot(m_pNodeA, m_pHost, m_ui8HotSpot);
    }
    if (m_pRingB != nullptr) {
        TransformFx::ShowNode(m_pRingB);
        TransformFx::SetGeometriesAlpha(m_pRingB, 0);
        HangUnderHotSpot(m_pRingB, m_pHost, m_ui8HotSpot);
    }
    if (m_pRingC != nullptr && m_levelIndex == 2) {
        TransformFx::ShowNode(m_pRingC);
        TransformFx::SetGeometriesAlpha(m_pRingC, 0);
        HangUnderHotSpot(m_pRingC, m_pHost, m_ui8HotSpot);
    }
    CKImpulsionCpnt* dash = static_cast<CKImpulsionCpnt*>(m_pDashImpulsion);
    dash->m_fImpulseTimer = 0.0f;
    dash->m_fValue = 0.0f;
    dash->m_fSpeed = 0.0f;
    m_abNodeFadeState[2] = 0;
    m_unk330 = 0;
    m_fNextShardTimer = m_fShardInterval;
    m_fDashTimeScale = 1.0f;  // TOC +0x39a8
    m_fEffectTimer = 0.0f;
    m_fUnusedTimer2 = 0.0f;
    m_abNodeFadeState[0] = 0;
    m_abNodeFadeState[1] = 0;
}

// 0x003ac7f8 CKIceSpin_StopFx: each node keeps its alpha (its first geometry's, else the level's full alpha word) for
// its fade-out, or is hidden at once when its fade-out time is 0 (a NaN time fades).
void CKIceSpin::StopFx() {
    CKTransformElement::StopFx();
    m_fStopFxTime = m_fEffectTimer;
    const uint32_t level = static_cast<uint32_t>(m_levelIndex);
    if (m_pNodeA != nullptr) {
        CGeometry* first = FirstGeometry(m_pNodeA);
        m_unk31c = first != nullptr ? first->m_cGeometryColor[3] : static_cast<uint32_t>(m_ai32NodeAFullAlpha[level]);
        if (m_fNodeAFadeOutTime == 0.0f) {
            TransformFx::HideNode(m_pNodeA);
        } else {
            m_abNodeFadeState[0] = 1;
        }
    }
    if (m_pRingB != nullptr) {
        CGeometry* first = FirstGeometry(m_pRingB);
        m_unk320 = first != nullptr ? first->m_cGeometryColor[3] : static_cast<uint32_t>(m_ai32RingBFullAlpha[level]);
        if (m_fRingBFadeOutTime == 0.0f) {
            TransformFx::HideNode(m_pRingB);
        } else {
            m_abNodeFadeState[1] = 1;
        }
    }
    if (m_pRingC != nullptr) {
        CGeometry* first = FirstGeometry(m_pRingC);
        m_unk324 = first != nullptr ? first->m_cGeometryColor[3] : static_cast<uint32_t>(m_ai32RingCFullAlpha[level]);
        if (m_fRingCFadeOutTime == 0.0f) {
            TransformFx::HideNode(m_pRingC);
        } else {
            m_abNodeFadeState[2] = 1;
        }
    }
    m_pHost->SetAbilityAttackSpheres(this, 0, 1.0f, nullptr, 1.0f, nullptr);  // vt+0xfc; TOC +0x39a8
    m_pHost->SetHero1d20(1.0f);                                                // vt+0x84
}

// 0x003b0e60 CKIceSpin_UpdateAttack_maybe
void CKIceSpin::UpdateAttack(float dt) {
    if (m_levelIndex == 0) return;
    if (m_pHost->IsAbilityButtonDown(3) != 0) {  // vt+0x8c
        static_cast<CKImpulsionCpnt*>(m_pDashImpulsion)->Impulse(1.0f);  // 0x0024bce0
        // The kick's sparks on the hot spot (the inlined CKSrvFx::StartEffect: not reserved, not kept).
        CKSparkFxData* kick = static_cast<CKSparkFxData*>(m_pDashKickSparkFxData);
        kick->m_unk10 = m_pHost->GetHotspot(m_ui8HotSpot);  // vt+0xcc
        kick->m_unk0c = nullptr;
        TransformFx::Start(m_pDashKickSparkFxData, this);
    }
    CKImpulsionCpnt* dash = static_cast<CKImpulsionCpnt*>(m_pDashImpulsion);
    dash->Update(dt);  // 0x0024bd40
    m_fDashTimeScale = dash->m_fValue;
    m_pHost->SetHero1d20(m_fDashTimeScale);  // vt+0x84
    // Near the dash's top (cror: a NaN is not), its particles and sparks run on the hot spot; below it they are let go.
    if (m_fDashTimeScale >= dash->m_unk04[0] - kDashTopMargin) {
        if (m_pActiveDashParticles == nullptr) {
            CKParticlesEffectFxData* particles = static_cast<CKParticlesEffectFxData*>(m_pDashParticlesData);
            IKSerializable* spot = m_pHost->GetHotspot(m_ui8HotSpot);  // vt+0xcc
            particles->m_pAttachOwner = nullptr;
            particles->m_pAttachHotSpot = spot;
            m_pActiveDashParticles = TransformFx::Acquire(m_pDashParticlesData, this);
        }
        if (m_pActiveDashTopSparks == nullptr) {
            CKSparkFxData* sparks = static_cast<CKSparkFxData*>(m_pDashTopSparkFxData);
            IKSerializable* spot = m_pHost->GetHotspot(m_ui8HotSpot);
            sparks->m_unk0c = nullptr;
            sparks->m_unk10 = spot;
            m_pActiveDashTopSparks = TransformFx::Acquire(m_pDashTopSparkFxData, this);
        }
    }
    if (m_fDashTimeScale < static_cast<CKImpulsionCpnt*>(m_pDashImpulsion)->m_unk04[0] - kDashTopMargin) {
        TransformFx::ReleaseParticles(&m_pActiveDashParticles, this);  // StopOwnedParticleEffect 0x001cdde8, vt+0x54
        TransformFx::ReleaseSpark(&m_pActiveDashTopSparks, this);      // StopOwnedSparkEffect_maybe 0x001d4698, vt+0x54
    }
}

// 0x003b1848 CKIceSpin_UpdateEffect_maybe
void CKIceSpin::UpdateEffect(float dt) {
    const float step = dt * m_fDashTimeScale;
    m_fEffectTimer = step + m_fEffectTimer;
    m_fUnusedTimer2 = step + m_fUnusedTimer2;
    if (m_pDashSound != nullptr) {
        // The dash sound's pitch with the dash's value between its bottom and its top (1 .. +0x308).
        CKImpulsionCpnt* dash = static_cast<CKImpulsionCpnt*>(m_pDashImpulsion);
        const float bottom = dash->m_unk04[1];
        float t = (m_fDashTimeScale - bottom) / (dash->m_unk04[0] - bottom);
        if (t <= 0.0f) {
            t = 0.0f;
        } else if (t >= 1.0f) {
            t = 1.0f;
        }
        m_pDashSound->SetPitch(ppc::fmadds(t, m_fDashSoundTopPitch - 1.0f, 1.0f));  // 0x00110ea0
    }
    const uint32_t level = static_cast<uint32_t>(m_levelIndex);
    if (IsShownUnderParent(m_pNodeA)) UpdateTopNode(this);
    if (IsShownUnderParent(m_pRingB)) {
        UpdateRing(this, SRingData{m_pRingB, &m_abNodeFadeState[1], m_fRingBFadeInTime, m_ai32RingBFullAlpha[level], m_ai32RingBStartAlpha[level], m_fRingBFadeOutTime,
                                   m_ai32RingBEndAlpha[level], m_unk320, m_afRingBFadeHeightStart[level], m_afRingBFadeHeightEnd[level], m_fRingBScaleWobble,
                                   m_afRingBSpinDegPerSec[level], m_afRingBScale[level]});
    }
    if (m_levelIndex == 2 && IsShownUnderParent(m_pRingC)) {
        // Ring C runs at level 2 only: its alphas are read at +0x210 / +0x21c (the level 2 words).
        UpdateRing(this, SRingData{m_pRingC, &m_abNodeFadeState[2], m_fRingCFadeInTime, m_ai32RingCFullAlpha[2], m_ai32RingCStartAlpha[2], m_fRingCFadeOutTime,
                                   m_ai32RingCEndAlpha[level], m_unk324, m_afRingCFadeHeightStart[level], m_afRingCFadeHeightEnd[level], m_fRingCScaleWobble,
                                   m_afRingCSpinDegPerSec[level], m_afRingCScale[level]});
    }
    if (m_pActiveAnimFx != nullptr) static_cast<CKAnimatedFxCollection*>(m_pActiveAnimFx)->Update(step);  // 0x005cccb0 (TocBridge)
    if (IsGroundTrailActive() != 0) {  // vt+0x8c
        if (m_pActiveMeshPopFx == nullptr) {
            // The ground mesh pop on the hot spot 0 (the inlined CKSrvFx::AcquireFx), switched on.
            CKMeshPopFxData* data = static_cast<CKMeshPopFxData*>(m_pMeshPopFxData);
            CSGHotSpot* spot = static_cast<CSGHotSpot*>(m_pHost->GetHotspot(0));  // vt+0xcc
            data->m_unk08 = nullptr;
            data->m_unk0c = spot;
            m_pActiveMeshPopFx = TransformFx::Acquire(m_pMeshPopFxData, this);
            if (m_pActiveMeshPopFx != nullptr) static_cast<CKMeshPopNodeFx*>(m_pActiveMeshPopFx)->SetActive(this, 1);  // 0x001cb568
        }
    } else {
        TransformFx::ReleaseMeshPop(&m_pActiveMeshPopFx, this);
    }
    if (m_levelIndex != 2) return;
    if (m_fNextShardTimer < 0.0f) {
        ThrowShard(this);
        return;
    }
    m_fNextShardTimer = m_fNextShardTimer - step;
}

// 0x003b3668 CKIceSpin_SetFxActive
void CKIceSpin::SetFxActive(int32_t on) {
    if (on != 0) {
        CKParticlesEffectFxData* loop = static_cast<CKParticlesEffectFxData*>(m_pLoopParticlesData);
        loop->m_pAttachHotSpot = m_pHost->GetHotspot(m_ui8HotSpot);  // vt+0xcc
        loop->m_pAttachOwner = nullptr;
        m_pActiveLoopParticles = TransformFx::Acquire(m_pLoopParticlesData, this);
        if (m_levelIndex == 1 || static_cast<uint32_t>(m_levelIndex) > 1) {
            IKSerializable* collection = m_levelIndex == 1 ? m_pAnimFxLevel1 : m_pAnimFxLevel2;
            m_pActiveAnimFx = collection;
            CSGLeaf* node = TransformFx::OwnerNode(m_pHost);                // vt+0x08, +0x1c
            SAnimatedFxRig* rigs = TransformFx::AttachmentSets(m_pHost);    // vt+0x104
            static_cast<CKAnimatedFxCollection*>(collection)->Play(
                node, rigs, static_cast<CSGHotSpot*>(m_pHost->GetHotspot(m_ui8HotSpot)));  // 0x005cc528 (TocBridge)
        }
        CKPointLightFxData* light = static_cast<CKPointLightFxData*>(m_apPointLightFxData[m_levelIndex]);
        light->m_pAttachHotSpot = m_pHost->GetHotspot(m_ui8HotSpot);
        light->m_pAttachNode = nullptr;
        m_pActivePointLight = TransformFx::Acquire(m_apPointLightFxData[m_levelIndex], this);
        m_pLoopSound = GetFxSound(1);
        if (m_pLoopSound != nullptr) {
            m_pLoopSound->SetAttachObject(TransformFx::OwnerNode(m_pHost));  // 0x00111350
            m_pLoopSound->Play(0.0f);                                       // 0x00111230
        }
        m_pDashSound = GetFxSound(3);
        if (m_pDashSound != nullptr) {
            m_pDashSound->SetPitch(1.0f);  // 0x00110ea0
            m_pDashSound->SetAttachObject(TransformFx::OwnerNode(m_pHost));
            m_pDashSound->Play(0.0f);
        }
        ApplyDamageParams(0);  // vt+0x88 (one Rand_Int)
        m_pHost->SetAbilityAttackSpheres(this, 1, m_afHitSphereRadius[m_levelIndex], m_elementDamage, 1.0f, nullptr);  // vt+0xfc
        if (m_pTrailNode != nullptr) {
            if (m_pNodeA != nullptr) static_cast<CSGLeaf*>(m_pNodeA)->ForceWorldMatrixUpdate();  // vt+0x50
            // Every ribbon of the trail on (CTrailNodeFx_SetRibbonActive_maybe 0x009bdfb8, inlined).
            const uint32_t count = static_cast<CTrailNodeFx*>(m_pTrailNode)->m_ui32NbTrail;
            for (uint32_t i = 0; i < count; ++i) static_cast<CTrailNodeFx*>(m_pTrailNode)->SetRibbonActive(i, 1, 1);
        }
        return;
    }
    TransformFx::ReleaseParticles(&m_pActiveLoopParticles, this);
    TransformFx::ReleaseParticles(&m_pActiveDashParticles, this);
    TransformFx::ReleaseSpark(&m_pActiveDashTopSparks, this);
    if (m_pActiveAnimFx != nullptr) {
        static_cast<CKAnimatedFxCollection*>(m_pActiveAnimFx)->Stop();  // 0x005cc990 (TocBridge)
        m_pActiveAnimFx = nullptr;
    }
    if (m_pActivePointLight != nullptr) {
        static_cast<IKFx*>(m_pActivePointLight)->StopAndRelease(this);  // vt+0x58
        m_pActivePointLight = nullptr;
    }
    if (m_pLoopSound != nullptr) {
        // The end sound (not kept), then the loop sound stopped.
        CKSound* end = GetFxSound(4);
        if (end != nullptr) {
            end->SetAttachObject(TransformFx::OwnerNode(m_pHost));
            end->Play(0.0f);
        }
        m_pLoopSound->Stop(0);  // 0x001111b0
        m_pLoopSound = nullptr;
    }
    if (m_pDashSound != nullptr) {
        m_pDashSound->Stop(0);
        m_pDashSound = nullptr;
    }
    if (m_pTrailNode == nullptr) return;
    // Every ribbon of the trail off, its points laid out again (CTrailNodeFx_SetRibbonActive_maybe, inlined).
    const uint32_t count = static_cast<CTrailNodeFx*>(m_pTrailNode)->m_ui32NbTrail;
    for (uint32_t i = 0; i < count; ++i) static_cast<CTrailNodeFx*>(m_pTrailNode)->SetRibbonActive(i, 0, 1);
}

// 0x003ac600 CKIceSpin_PostLoad
int32_t CKIceSpin::PostLoad(int32_t type) {
    CKTransformElement::PostLoad(type);
    SceneNode_SetVisibleInLayer(static_cast<CSGLeaf*>(m_pNodeA), 1, 0, 0);  // 0x005832a8
    SceneNode_SetVisibleInLayer(static_cast<CSGLeaf*>(m_pRingB), 1, 0, 0);
    SceneNode_SetVisibleInLayer(static_cast<CSGLeaf*>(m_pRingC), 1, 0, 0);
    CSGLeaf* trail = static_cast<CSGLeaf*>(m_pTrailNode);
    if (trail == nullptr) return 1;
    if (trail->m_pParent != nullptr) trail->m_pParent->RemoveChild(trail);  // vt+0x78
    CSGBranch* parent = m_pNodeA != nullptr ? static_cast<CSGBranch*>(m_pNodeA)
                                            : static_cast<CSGBranch*>(g_pEngine->m_dynamicSceneRoot);
    parent->AddChild(static_cast<CSGLeaf*>(m_pTrailNode));  // vt+0x70
    return 1;
}

// 0x003ad010 CKIceSpin_Load: CKTransformElement's data, then (level data only, type K_LEVEL_PLATEFORMS) 416
// bytes of references and words (702 bytes in all).
int32_t CKIceSpin::Load(IKFile* file, int32_t type) {
    CKTransformElement::Load(file, type);
    if (type == 0) {
        IKFile_ReadRef(file, &m_pDashTopSparkFxData);
        IKFile_ReadRef(file, &m_pLoopParticlesData);
        IKFile_ReadRef(file, &m_pNodeA);
        IKFile_ReadRef(file, &m_pDashImpulsion);
        IKFile_ReadRef(file, &m_pShardAccessorA);
        for (int32_t i = 0; i < 3; ++i) {
            ReadF32LE(file, &m_afHitSphereRadius[i]);
            ReadS32LE(file, &m_ai32NodeAFullAlpha[i]);
            ReadS32LE(file, &m_ai32NodeAStartAlpha[i]);
            ReadS32LE(file, &m_ai32NodeAEndAlpha[i]);
            ReadF32LE(file, &m_afNodeAScale[i]);
        }
        ReadF32LE(file, &m_fNodeAScaleWobble);
        ReadF32LE(file, &m_fNodeAFadeInTime);
        ReadF32LE(file, &m_fNodeAFadeOutTime);
        ReadF32LE(file, &m_fShardSpeedMin);
        ReadF32LE(file, &m_fShardSpeedMax);
        ReadF32LE(file, &m_fShardInterval);
        ReadF32LE(file, &m_fShardIntervalSpread);
        ReadF32LE(file, &m_fShardHeightOffset);
        ReadF32LE(file, &m_fShardDirY);
        ReadF32LE(file, &m_afNodeASpinDegPerSec[0]);
        ReadF32LE(file, &m_afNodeASpinDegPerSec[1]);
        ReadF32LE(file, &m_afNodeASpinDegPerSec[2]);
        for (int32_t i = 0; i < 3; ++i) {
            ReadS32LE(file, &m_ai32RingBFullAlpha[i]);
            ReadS32LE(file, &m_ai32RingBStartAlpha[i]);
            ReadS32LE(file, &m_ai32RingBEndAlpha[i]);
            ReadF32LE(file, &m_afRingBScale[i]);
            ReadF32LE(file, &m_afRingBSpinDegPerSec[i]);
        }
        ReadF32LE(file, &m_fRingBScaleWobble);
        ReadF32LE(file, &m_fRingBFadeInTime);
        ReadF32LE(file, &m_fRingBFadeOutTime);
        IKFile_ReadRef(file, &m_pRingB);
        IKFile_ReadRef(file, &m_pDashKickSparkFxData);
        IKFile_ReadRef(file, &m_pAnimFxLevel1);
        IKFile_ReadRef(file, &m_pAnimFxLevel2);
        for (int32_t i = 0; i < 3; ++i) {
            ReadF32LE(file, &m_afRingBFadeHeightStart[i]);
            ReadF32LE(file, &m_afRingBFadeHeightEnd[i]);
        }
        ReadF32LE(file, &m_unk274);
        ReadF32LE(file, &m_unk278);
        ReadF32LE(file, &m_unk27c);
        ReadF32LE(file, &m_unk280);
        ReadF32LE(file, &m_unk284);
        ReadF32LE(file, &m_unk288);
        ReadS32LE(file, &m_unk28c);
        ReadU32LE(file, &m_unk290);
        IKFile_ReadRef(file, &m_pMeshPopFxData);
        for (int32_t i = 0; i < 3; ++i) {
            ReadS32LE(file, &m_ai32RingCFullAlpha[i]);
            ReadS32LE(file, &m_ai32RingCStartAlpha[i]);
            ReadS32LE(file, &m_ai32RingCEndAlpha[i]);
            ReadF32LE(file, &m_afRingCScale[i]);
            ReadF32LE(file, &m_afRingCSpinDegPerSec[i]);
            // C2.8 gate-l20: ring C's heights are read per level with its other words (the C2.1 Load's order; a
            // second loop read them after all three levels: objects_diff against both in-game dumps).
            ReadF32LE(file, &m_afRingCFadeHeightStart[i]);
            ReadF32LE(file, &m_afRingCFadeHeightEnd[i]);
        }
        ReadF32LE(file, &m_fRingCScaleWobble);
        ReadF32LE(file, &m_fRingCFadeInTime);
        ReadF32LE(file, &m_fRingCFadeOutTime);
        IKFile_ReadRef(file, &m_pRingC);
        IKFile_ReadRef(file, &m_pShardAccessorB);
        IKFile_ReadRef(file, &m_pDashParticlesData);
        IKFile_ReadRef(file, &m_pSoundDico);
        ReadF32LE(file, &m_fDashSoundTopPitch);
        IKFile_ReadRef(file, &m_pShardDamage);
        IKFile_ReadRef(file, &m_apPointLightFxData[0]);
        IKFile_ReadRef(file, &m_apPointLightFxData[1]);
        IKFile_ReadRef(file, &m_apPointLightFxData[2]);
        ReadF32LE(file, &m_fShardConeDeg);
        IKFile_ReadRef(file, &m_pTrailNode);
    }
    return 1;
}
