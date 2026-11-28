// CKFearScream.cpp - reconstructed original translation unit 0x3a0f00-0x3a3240 (GAME_TOC1, main_toc1), 29 functions, 29 live.
// Primary class: CKFearScream  key 0x944c  category Logic  size 0x24c  vtable 0xb239b8
// Other owners: CKFireBreath (3), ResetFireBreathRuntimeEffects (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x3a0f00  CKFearScream_Delete
//   [x] 0x3a0f50  CKFearScream_GetAbilityId
//   [x] 0x3a0f58  CKFearScream_IsChargeDisabled_maybe
//   [x] 0x3a0fa8  CKFearScream_End
//   [x] 0x3a1038  CKFearScream_GetFxSound_maybe
//   [x] 0x3a1180  CKFearScream_ResetRuntime
//   [x] 0x3a11d0  CKFearScream_Start
//   [x] 0x3a1220  CKFearScream_PostLoad
//   [x] 0x3a1270  CKFearScream_RecursiveRegistration  (inherited: CKProjectileElement_RecursiveRegistration)
//   [x] 0x3a1298  CKFearScream_Destroy  (inherited: CKProjectileElement_Destroy)
//   [x] 0x3a12c0  CKFearScream_Construct
//   [x] 0x3a12f8  CKFearScream_Construct_2  (the same as 0x3a12c0 CKFearScream_Construct)
//   [x] 0x3a1330  CKFearScream_DeleteArray
//   [x] 0x3a13d0  CKFearScream_DeletingDestructor  (C++ destructor chain: vtable stores only)
//   [x] 0x3a1418  CKFearScream_Destructor  (C++ destructor chain: vtable stores only)
//   [x] 0x3a1448  CKFearScream_DestructBody  (C++ destructor chain: vtable stores only)
//   [ ] 0x3a1478  RegisterCKFearScreamClass
//   [ ] 0x3a1500  _GLOBAL__D_3a1500
//   [ ] 0x3a1510  _GLOBAL__I_3a1510
//   [x] 0x3a1520  CKFearScream_Create
//   [x] 0x3a1578  CKFearScream_CreateArray
//   [x] 0x3a1628  CKFearScream_UpdateCharge
//   [x] 0x3a1cb8  CKFearScream_Load
//   [ ] 0x3a21b8  CKFearScream_Save
//   [x] 0x3a2750  CKFearScream_Fire
//   [x] 0x3a3040  CKFireBreath_Delete  (the registry factory: DOTD_DECLARE_FACTORIES)
//   [x] 0x3a3090  CKFireBreath_GetAbilityId  (ported in CKFireBreath.cpp)
//   [x] 0x3a3098  CKFireBreath_GetSound_maybe  (ported in CKFireBreath.cpp)
//   [x] 0x3a31e0  ResetFireBreathRuntimeEffects  (ported in CKFireBreath.cpp)
//
//   [ ] 0x9bfdb0  CKFearScream_IsKindOfClass  [inline]
//   [ ] 0x9bfe00  CKFearScream_GetClassType  [inline]
//   [ ] 0x9bfe08  CKFearScream_GetClassID  [inline]
//   [x] 0x9bfe10  CKFearScream_StartEmitterFx  [inline]
#include "k2000/logic/CKFearScream.h"

#include <cmath>
#include <cstdint>

#include "Renderware/rwcore/RwCamera.h"
#include "crt/ppc_ops.h"
#include "k2000/dictionaries/CKSoundDictionaryID.h"
#include "k2000/geometry/CGeometry.h"
#include "k2000/hooks/IKHook.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/logic/IKFxData.h"
#include "k2000/logic/fx/CKExplosionNodeFx.h"
#include "k2000/logic/render/CMaterial.h"
#include "k2000/logic/sound/CKSound.h"
#include "k2000/math/Math.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/CNode.h"
#include "k2000/scenegraph/CSGBranch.h"
#include "k2000/services/CKSrvFx.h"

namespace {
const CVector3 kNullVector = {0.0f, 0.0f, 0.0f};  // 0x00c50d64 (TOC +0x37b0)
constexpr float kAlphaScale = 254.0f;             // TOC +0x3784

// The inlined geometry alpha walk (CKPoisonGrenade's / CKBeamBreath's): every geometry takes `alpha` (CGeometry colour
// byte +0x23) and the "alpha blended" property bit 11 (vt+0x60 when it changes); 0xff clears it everywhere, and a
// geometry with property bit 12 and a material of mode 1..6 keeps 0xff without blending.
void SetMeshAlpha(CNode* node, uint8_t alpha) {
    for (CGeometry* geometry = static_cast<CGeometry*>(node->m_lGeometryList); geometry != nullptr;
         geometry = geometry->m_pNext) {
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

// SceneNode_SetVisibleInLayer_maybe 0x005832a8 (through its TOC bridge 0x0098f340): the node hidden under sector 0's
// root.
void HideUnderSector0(IKSerializable* node) { SceneNode_SetVisibleInLayer(static_cast<CSGLeaf*>(node), 1, 0, 0); }

// The sound put on the user's node (host vt+0x08, its +0x1c; CKSound_SetAttachObject 0x00111350) and played
// (CKSound_Play 0x00111230 at 0.0, TOC +0x37bc).
void PlayOnUser(CKSound* sound, CKS08AbilityHostBase* host) {
    sound->SetAttachObject(static_cast<IKHook*>(host->GetOwner())->m_pKGLObject);
    sound->Play(0.0f);
}
}  // namespace

// 0x003a1220 CKFearScream_PostLoad
int32_t CKFearScream::PostLoad(int32_t type) {
    CKProjectileElement::PostLoad(type);
    HideUnderSector0(m_pChargeNode);
    return 1;
}

// 0x003a11d0 CKFearScream_Start
void CKFearScream::Start(CKS08AbilityHostBase* host) {
    m_pLoopSound = nullptr;
    CKProjectileElement::Start(host);
    if (m_pHost != nullptr) m_bFullChargeBurstFired = 0;
}

// 0x003a0fa8 CKFearScream_End
void CKFearScream::End(int32_t forced) {
    if (m_pLoopSound != nullptr) {
        Sound_Stop(m_pLoopSound, 0);  // 0x001111b0
        m_pLoopSound = nullptr;
    }
    HideUnderSector0(m_pChargeNode);
    CKProjectileElement::End(static_cast<uint8_t>(forced));
}

// 0x003a1180 CKFearScream_ResetRuntime
void CKFearScream::ResetRuntime(int32_t type) {
    CKProjectileElement::ResetRuntime(type);
    m_ui8HotSpotIndex = 2;
    m_pLoopSound = nullptr;
    m_ui8ButtonIndex = 1;
    m_bFullChargeBurstFired = 0;
}

// 0x003a1038 CKFearScream_GetFxSound_maybe (CKSoundDictionaryID_GetSound 0x00112bc0, CKSound_GetSample_maybe
// 0x00111000; each sound looked up again before it is returned, as the original).
CKSound* CKFearScream::GetFxSound(int32_t which) {
    CKSoundDictionaryID* sounds = static_cast<CKSoundDictionaryID*>(m_pSoundDico);
    if (which == 0) return sounds->GetSound(0);
    if (which != 1) return nullptr;
    const auto usable = [sounds](uint32_t i) {
        return sounds->GetSound(i) != nullptr && sounds->GetSound(i)->GetSample() != nullptr;
    };
    if (m_ui32LevelIndex == 2 && usable(3)) return sounds->GetSound(3);
    if ((m_ui32LevelIndex == 1 || m_ui32LevelIndex == 2) && usable(2)) return sounds->GetSound(2);
    return sounds->GetSound(1);
}

// 0x003a1628 CKFearScream_UpdateCharge. Past the level's full charge time (+0x200 > +0x68: ble, a NaN does not) the
// burst +0x22c goes off once at the hot spot +0x208 (the inlined CKSrvFx::AcquireFx, owned by this element). The charge
// node (+0x230): hidden, it is shown transparent on the first charging frame under the hot spot 0 (removed from its
// parent first, vt+0x78), moved by +0x234; shown, its alpha follows the charge (254 x +0x200 / +0x68 up to the full
// time, then 254; fctiwz, the low byte).
void CKFearScream::UpdateCharge(float /*dt*/) {
    if (m_fChargeTime > m_afFullChargeTime[m_ui32LevelIndex] && m_bFullChargeBurstFired == 0) {
        m_bFullChargeBurstFired = 1;
        CKSrvFx* fxService = static_cast<CKSrvFx*>(g_pEngine->m_srvFx);  // TOC +0x3780 -> +0x60
        CKExplosionNodeFx* burst =
            static_cast<CKExplosionNodeFx*>(fxService->AcquireFx(reinterpret_cast<IKFxData*>(m_unk214[6]), this));
        if (burst != nullptr) {
            const CVector3 position = m_pHost->GetHotspotPosition(m_ui8HotSpotIndex);  // vt+0xd0
            burst->SetTranslation(&position, this);  // 0x001b66e8
            burst->Trigger(this, 0);                 // 0x001b82a8
            burst->ReleaseReservation(this);         // vt+0x54
        }
    }
    CNode* node = static_cast<CNode*>(m_pChargeNode);
    if (node == nullptr) return;
    if ((node->m_sgProperties & 4u) == 0) {
        const float alpha = m_fChargeTime > m_afFullChargeTime[m_ui32LevelIndex] ? kAlphaScale : m_fChargeTime / m_afFullChargeTime[m_ui32LevelIndex] * kAlphaScale;
        if (node->m_lGeometryList == nullptr) return;
        SetMeshAlpha(node, static_cast<uint8_t>(ppc::fctiwz(alpha)));
        return;
    }
    node->m_sgProperties &= 0xfffffffbu;
    if (node->m_lGeometryList != nullptr) SetMeshAlpha(node, 0);
    if (node->m_pParent != nullptr) node->m_pParent->RemoveChild(node);  // vt+0x78
    static_cast<CSGHotSpot*>(m_pHost->GetHotspot(0))->AttachVolume(node);  // vt+0xcc, 0x000ce2b8
    RwFrame* frame = node->m_pRwFrame;
    frame->modelling.pos.x = frame->modelling.pos.x + m_vChargeNodeOffset[0];
    frame->modelling.pos.y = frame->modelling.pos.y + m_vChargeNodeOffset[1];
    frame->modelling.pos.z = frame->modelling.pos.z + m_vChargeNodeOffset[2];
    frame->modelling.flags &= ~0x20000u;
    RwFrame_MarkDirty(frame);  // 0x00010698
}

// 0x003a2750 CKFearScream_Fire. The launch point (GetLaunchPosDir, no offset), the aim (host vt+0x58, the result
// unused), the direction to the locked target's aim point (vt+0xdc from the hot spot) or the aim direction (vt+0x24),
// normalised. Charged (+0x200 >= +0x68: cror gt|eq, a NaN is not) the level's charged explosion (+0x220), else its
// normal one (+0x214), owned by the user (the inlined CKSrvFx::AcquireFx); the charged one also hides the charge node
// above level index 0. The explosion: at the launch point, along the direction, the damage parameters (vt+0x74, one rand
// draw) and object, the user's collision group and mask (vt+0xb0 / +0xb4), triggered and released. Then, unless the
// loop sound still has a sample: the start sound and the level's loop sound (+0x248) on the user. Returns 1.
uint8_t CKFearScream::Fire() {
    const CVector3 pos = GetLaunchPosDir(&kNullVector);
    m_pHost->ComputeAimDirection(0x1.921fb6p+1f, this, m_pAimCone);  // vt+0x58; pi (TOC +0x37b4)
    CVector3 dir;
    if (m_pHost->GetLockedTarget() != nullptr) {  // vt+0xd4
        const CVector3 target = m_pHost->GetTargetAimPoint(1, 0);  // vt+0xdc
        dir.y = target.y - pos.y;
        dir.x = target.x - pos.x;
        dir.z = target.z - pos.z;
    } else {
        dir = m_pHost->GetAimDirection(0);  // vt+0x24
    }
    const float length = std::sqrt(ppc::fmadds(dir.z, dir.z, ppc::fmadds(dir.x, dir.x, dir.y * dir.y)));  // 0x00010690
    if (length != 0.0f) {
        const float inv = 1.0f / length;  // TOC +0x37b8
        dir.z = dir.z * inv;
        dir.x = dir.x * inv;
        dir.y = dir.y * inv;
    }
    IKSerializable* owner = m_pHost->GetOwner();  // vt+0x08
    CKSrvFx* fxService = static_cast<CKSrvFx*>(g_pEngine->m_srvFx);  // TOC +0x3780 -> +0x60
    CKExplosionNodeFx* scream;
    if (!(m_fChargeTime >= m_afFullChargeTime[m_ui32LevelIndex])) {
        scream = static_cast<CKExplosionNodeFx*>(
            fxService->AcquireFx(reinterpret_cast<IKFxData*>(m_unk214[m_ui32LevelIndex]), owner));
    } else {
        scream = static_cast<CKExplosionNodeFx*>(
            fxService->AcquireFx(reinterpret_cast<IKFxData*>(m_unk214[3 + m_ui32LevelIndex]), owner));
        CNode* node = static_cast<CNode*>(m_pChargeNode);
        if (m_ui32LevelIndex != 0 && node != nullptr) node->m_sgProperties = (node->m_sgProperties & 0xfffffffbu) | 4u;
    }
    m_bFullChargeBurstFired = 0;
    if (scream != nullptr) {
        scream->SetTranslation(&pos, owner);  // 0x001b66e8
        scream->SetDirection(&dir, owner);    // 0x001b5e20
        ApplyDamageParams(0);                 // vt+0x74
        scream->SetDamage(m_pElementDamage, owner);                         // 0x001b62c8
        scream->SetDamageOwner(owner, owner);                       // 0x001b6340
        scream->SetDamageCategory(m_pHost->GetCollisionGroup(), owner);  // vt+0xb0, 0x001b6318
        scream->SetDamageFlags(m_pHost->GetCollisionMask(), owner);      // vt+0xb4, 0x001b62f0
        scream->Trigger(owner, 0);                                  // 0x001b82a8
        scream->ReleaseReservation(owner);                          // vt+0x54
    }
    if (m_pLoopSound != nullptr && m_pLoopSound->GetSample() != nullptr) return 1;  // 0x00111000
    CKSound* start = GetFxSound(0);
    if (start != nullptr) PlayOnUser(start, m_pHost);
    m_pLoopSound = GetFxSound(1);
    if (m_pLoopSound != nullptr) PlayOnUser(m_pLoopSound, m_pHost);
    return 1;
}

// 0x003a1cb8 CKFearScream_Load: CKProjectileElement's data, then (level data only) 48 bytes: eight object
// references, a 12-byte block of three swapped words, a sound reference.
int32_t CKFearScream::Load(IKFile* file, int32_t type) {
    CKProjectileElement::Load(file, type);
    if (type != 0) return 1;
    for (int32_t i = 0; i < 7; ++i) IKFile_ReadRef(file, &m_unk214[i]);
    IKFile_ReadRef(file, &m_pChargeNode);
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(m_vChargeNodeOffset), 3);
    IKFile_ReadRef(file, &m_pSoundDico);
    return 1;
}
