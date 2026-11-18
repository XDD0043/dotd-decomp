// CKSandal.cpp - reconstructed original translation unit: 0x455dc0-0x456b78 (GAME_TOC1, main_toc1), 15 functions, 15 live.
// Primary class: CKSandal  key 0x2f0c  category Logic  size 0x34  vtable 0xb27070
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x455dc0  CKSandal_ProcessDamageContacts  (vt+0xa4, empty: CKSandal.h)
//   [ ] 0x455dc8  RegisterCKSandalClass
//   [ ] 0x455e40  _GLOBAL__I_455e40
//   [x] 0x455e50  CKSandal_PlaceInstance_maybe
//   [x] 0x456098  CKSandal_DeleteArray  (DOTD_DECLARE_FACTORIES)
//   [x] 0x456138  CKSandal_Create  (DOTD_DECLARE_FACTORIES; the constructor in CKSandal.h)
//   [x] 0x456190  CKSandal_vf68
//   [x] 0x4562d0  CKSandal_UpdateMotion
//   [x] 0x456348  CKSandal_CreateArray  (DOTD_DECLARE_FACTORIES)
//   [x] 0x456400  CKSandal_UpdateFadeOut_maybe  (UpdateOrientation, vt+0x64)
//   [x] 0x4565d0  CKSandal_OnDeath
//   [x] 0x456738  CKSandal_Destroy
//   [ ] 0x456760  CKSandal_Save
//   [x] 0x456768  CKSandal_RecursiveRegistration
//   [x] 0x4567d8  CKSandal_Load
//
//   [x] 0x9b09e0  CKSandal_vf84  [inline]  (Launch, CKSandal.h)
//   [x] 0x9b0a60  CKSandal_vf88  [inline]  (LaunchEx, CKSandal.h)
//   [x] 0x9b0bf0  CKSandal_vf98  [inline]  (LaunchAtPoint, CKSandal.h)
//   [x] 0x9b0bf8  CKSandal_vf9C  [inline]  (LaunchAtPointEx, CKSandal.h)
//   [ ] 0x9b0c48  KStub_Return0_9b0c48  [inline]
//   [x] 0x9c3e40  CKSandal_IsKindOfClass  [inline]  (CKSandal.h)
//   [x] 0x9c3e68  CKSandal_GetClassType  [inline]  (DOTD_CLASS_KEY)
//   [x] 0x9c3e70  CKSandal_GetClassID  [inline]  (DOTD_CLASS_KEY)
//   [x] 0x9c3e78  CKSandal_Destructor  [inline]  (CKSandal.h)
//   [x] 0x9c3e98  CKSandal_DeletingDestructor  [inline]  (CKSandal.h)
#include "k2000/logic/CKSandal.h"

#include "Renderware/rpprtstd/RpPrtStd.h"
#include "Renderware/rwcore/RwCamera.h"
#include "Renderware/rtanim/RtAnim.h"
#include "crt/ppc_ops.h"
#include "k2000/dictionaries/CAnimationDictionary.h"
#include "k2000/geometry/CGeometry.h"
#include "k2000/graphical/animation/CAnimationManager.h"
#include "k2000/hooks/IKHook.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/render/CMaterial.h"
#include "k2000/memory/Mem.h"
#include "k2000/scenegraph/CAnimatedNode.h"
#include "k2000/scenegraph/CParticlesNodeFx.h"

namespace {
const CVector3 kNullVector = {0.0f, 0.0f, 0.0f};  // g_nullVector 0x00c50d64
const CVector3 kAxisY = {0.0f, 1.0f, 0.0f};       // 0x00c50d40

// The geometries of the sandal's node all opaque again: alpha 0xff, the blend bit (0x800) cleared with the stage
// update (vt+0x60) when it was set (PlaceInstance and the fade's 0xff case inline the same loop).
void ResetGeometryAlpha(CAnimatedNode* node) {
    for (CGeometry* geometry = static_cast<CGeometry*>(node->m_lGeometryList); geometry != nullptr;
         geometry = geometry->m_pNext) {
        geometry->m_cGeometryColor[3] = 0xff;
        const uint32_t bits = geometry->m_BitProperties;
        if ((bits & 0x800u) != 0) {
            geometry->m_BitProperties = bits & 0xfffff7ffu;
            geometry->UpdateProperties();  // vt+0x60
        }
    }
}

// The blend pair: the dictionary's words 0 and 1.
uint32_t AnimWord(const CAnimationDictionary* dictionary, uint32_t i) {
    return static_cast<uint32_t>(dictionary->m_apAnimations[i]);
}
}  // namespace

CKSandal::CKSandal() {}
CKSandal::~CKSandal() {}

// 0x00456738 CKSandal_Destroy: IKProjectileType_Destroy 0x1f3c38 (the two lists freed).
void CKSandal::Destroy() { IKProjectileType::Destroy(); }

// 0x00456768 CKSandal_RecursiveRegistration: the base's KStub_Return1_1f3c90 (nothing), then the animation dictionary
// recurses with the same type. BUG(original): no null test.
void CKSandal::RecursiveRegistration(int32_t type) { m_pAnimatedDictionary->RecursiveRegistration(type); }

// 0x004567d8 CKSandal_Load: IKProjectileType's; level files then read the duration and the fade duration (byte-swapped
// words), the death FX reference, one node reference per sandal (the node hidden, the sandal at the origin, ratio and
// timer 0) and the animation dictionary reference.
int32_t CKSandal::Load(IKFile* file, int32_t type) {
    IKProjectileType::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadF32LE(file, &m_fDuration);
    ReadF32LE(file, &m_fFadeDuration);
    IKFile_ReadRef(file, &m_pDeathFx);
    // PS3: count << 2 and count * 0x18 (one allocation each, the list first); native sizes here.
    const uint32_t count = m_ui8MaxProjectiles;
    SSandal** list = static_cast<SSandal**>(Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(SSandal*))));
    SSandal* sandals = static_cast<SSandal*>(Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(SSandal))));
    m_aProjectiles = sandals;
    m_apProjectileList = reinterpret_cast<void**>(list);
    for (uint32_t i = 0; i < m_ui8MaxProjectiles; i = static_cast<uint8_t>(i + 1)) {
        list[i] = &sandals[i];
        IKFile_ReadRef(file, &list[i]->m_pAnimNode);
        // BUG(original): no null test of the node reference.
        list[i]->m_pAnimNode->m_sgProperties = (list[i]->m_pAnimNode->m_sgProperties & ~0x4u) | 0x4u;
        list[i]->m_v3Position = kNullVector;
        list[i]->m_fRatio = 0.0f;
        list[i]->m_fTimer = 0.0f;
    }
    IKFile_ReadRef(file, &m_pAnimatedDictionary);
    return 1;
}

// 0x004562d0 CKSandal_UpdateMotion: the timer advances; the blend pair is posed at the timer, held at the first
// animation's duration (ble: a NaN timer is kept), with the sandal's ratio.
void CKSandal::UpdateMotion(uint8_t index, float dt) {
    SSandal* sandal = static_cast<SSandal*>(m_apProjectileList[index]);
    float t = dt + sandal->m_fTimer;
    sandal->m_fTimer = t;
    const uint32_t first = AnimWord(m_pAnimatedDictionary, 0);
    const uint32_t second = AnimWord(m_pAnimatedDictionary, 1);
    const float duration = CAnimationManager_GetAnimation(first)->duration;
    if (t > duration) t = duration;
    sandal->m_pAnimNode->SetBlendAnimPairAndWeight(first, second, t, t, sandal->m_fRatio);
}

// 0x00455bb0 CKSandal_vf58: dead once its timer is past the duration (bgt: NaN lives).
uint8_t CKSandal::IsDead(uint8_t index) {
    const SSandal* sandal = static_cast<const SSandal*>(m_apProjectileList[index]);
    return sandal->m_fTimer > m_fDuration ? 1 : 0;
}

// 0x004565d0 CKSandal_OnDeath: the node hidden; with the death FX option (bit 0) the FX gets the sandal's position as
// one more emitter point (below 64: property 0x2000) and starts emitting (0x200 | 0x400 set, 0x80000 cleared, the
// emission speed adjustment 0, the RpPrtStdEmitter's ACTIVE | EMIT); then KillProjectile (vt+0x60).
void CKSandal::OnDeath(uint8_t index) {
    SSandal* sandal = static_cast<SSandal*>(m_apProjectileList[index]);
    sandal->m_pAnimNode->m_sgProperties = (sandal->m_pAnimNode->m_sgProperties & ~0x4u) | 0x4u;
    if ((m_baOptions & 1u) != 0) {
        CParticlesNodeFx* fx = m_pDeathFx;
        if (fx->m_ui8NbActivePoints <= 0x3f) {
            RwV3d& point = fx->m_pAdvEmtPointList->pointList[fx->m_ui8NbActivePoints];
            point.x = sandal->m_v3Position.x;
            point.y = sandal->m_v3Position.y;
            point.z = sandal->m_v3Position.z;
            fx->m_sgProperties = (fx->m_sgProperties & ~0x2000u) | 0x2000u;
            fx->m_ui8NbActivePoints = static_cast<uint8_t>(fx->m_ui8NbActivePoints + 1);
            fx = m_pDeathFx;
        }
        uint32_t properties = fx->m_sgProperties;
        properties = (properties & ~0x200u) | 0x200u;
        properties = (properties & ~0x400u) | 0x400u;
        properties &= ~0x80000u;
        fx->m_sgProperties = properties;
        fx->m_fEmissionSpeedAdjustment = 0.0f;  // stw 0
        fx->m_pRpPrtStdEmitter->flag |= rpPRTSTDEMITTERFLAGACTIVE | rpPRTSTDEMITTERFLAGEMIT;
    }
    KillProjectile(index);  // vt+0x60
}

// 0x00455be8 CKSandal_vf60: the node hidden; the active count drops and the last active sandal takes this one's place
// in the list (this one moves to the end).
void CKSandal::KillProjectile(uint8_t index) {
    void** list = m_apProjectileList;
    SSandal* sandal = static_cast<SSandal*>(list[index]);
    sandal->m_pAnimNode->m_sgProperties = (sandal->m_pAnimNode->m_sgProperties & ~0x4u) | 0x4u;
    const uint8_t last = static_cast<uint8_t>(m_ui8NbOfActiveProjectiles - 1);
    if (static_cast<int32_t>(index) != static_cast<int32_t>(m_ui8NbOfActiveProjectiles) - 1) {
        m_ui8NbOfActiveProjectiles = last;
        list[index] = list[last];
        list[m_ui8NbOfActiveProjectiles] = sandal;
        return;
    }
    m_ui8NbOfActiveProjectiles = last;
}

// 0x00456400 CKSandal_UpdateFadeOut_maybe (vt+0x64): with the fade option (bit 1), once the timer is inside the last
// m_fFadeDuration (bge: NaN skips), the node's geometries take alpha (duration - timer) / fade * 255 (fctiwz, the low
// byte); 0xff makes them opaque, any other value blends them, except geometries flagged 0x1000 whose material mode is
// 1..6 (kept opaque).
void CKSandal::UpdateOrientation(uint8_t index, float /*dt*/) {
    SSandal* sandal = static_cast<SSandal*>(m_apProjectileList[index]);
    if ((m_baOptions & 2u) == 0) return;
    const float fade = m_fFadeDuration;
    const float duration = m_fDuration;
    const float t = sandal->m_fTimer;
    if (!(duration - fade < t)) return;
    const float scaled = ((duration - t) / fade) * 255.0f;  // TOC -0x5584 255.0
    const uint8_t alpha = static_cast<uint8_t>(ppc::fctiwz(scaled));  // fctiwz, stfiwx, lbz +3
    CGeometry* geometry = static_cast<CGeometry*>(sandal->m_pAnimNode->m_lGeometryList);
    if (geometry == nullptr) return;
    if (alpha == 0xff) {
        ResetGeometryAlpha(sandal->m_pAnimNode);
        return;
    }
    for (; geometry != nullptr; geometry = geometry->m_pNext) {
        uint32_t blend = 1;
        uint8_t value = alpha;
        if ((geometry->m_BitProperties & 0x1000u) != 0) {
            const uint32_t mode = (static_cast<CMaterial*>(geometry->m_pMaterial)->m_baProperties >> 3) & 0xfu;
            if (mode != 0 && mode <= 6) {
                blend = 0;
                value = 0xff;
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

// 0x00456190 CKSandal_vf68: with a free sandal and an owner that is a hook (IsKindOfClass(2)), the next sandal is placed
// (PlaceInstance with copies of pos and dir) and counted active; 1. Otherwise 0.
uint8_t CKSandal::Vf68(const CVector3* pos, const CVector3* dir, const void* /*r6*/, float speed, IKSerializable* owner,
                       const void* /*r8*/) {
    if (m_ui8NbOfActiveProjectiles >= m_ui8MaxProjectiles) return 0;
    if (owner == nullptr) return 0;
    if (static_cast<uint8_t>(owner->IsKindOfClass(2)) == 0) return 0;
    const CVector3 posCopy = *pos;
    const CVector3 dirCopy = *dir;
    PlaceInstance(m_ui8NbOfActiveProjectiles, &posCopy, &dirCopy, speed, owner);
    m_ui8NbOfActiveProjectiles = static_cast<uint8_t>(m_ui8NbOfActiveProjectiles + 1);
    return 1;
}

// 0x00455e50 CKSandal_PlaceInstance_maybe: the weight from d = dot(owner's node at, dir) (fused: at.y * dir.y first):
// d > 0.7 gives 1, d > -0.7 gives (d + 0.7) / 1.4, else 0 (ble: NaN gives 0). The sandal's position and its frame's
// position set (the identity flag cleared, the frame marked dirty), the node shown and turned along the owner's `at`
// with the Y axis up, its geometries opaque, ratio = the weight, timer 0, and the blend pair posed at 0 with it.
void CKSandal::PlaceInstance(uint8_t index, const CVector3* pos, const CVector3* dir, float /*speed*/,
                             IKSerializable* owner) {
    const RwFrame* ownerFrame = static_cast<CSGMovable*>(static_cast<IKHook*>(owner)->m_pKGLObject)->m_pRwFrame;
    SSandal* sandal = static_cast<SSandal*>(m_apProjectileList[index]);
    const CVector3 at = {ownerFrame->modelling.at.x, ownerFrame->modelling.at.y, ownerFrame->modelling.at.z};
    const float d = ppc::fmadds(at.z, dir->z, ppc::fmadds(at.x, dir->x, at.y * dir->y));
    float weight;
    if (d > 0.0f) {
        if (d > 0.7f) {
            weight = 1.0f;
        } else {
            weight = (d + 0.7f) / 1.4f;
        }
    } else {
        weight = 0.0f;
        if (d > -0.7f) weight = (d + 0.7f) / 1.4f;
    }
    sandal->m_v3Position = *pos;
    CAnimatedNode* node = sandal->m_pAnimNode;
    node->m_sgProperties &= ~0x4u;
    RwFrame* frame = node->m_pRwFrame;
    frame->modelling.pos.x = pos->x;
    frame->modelling.pos.y = pos->y;
    frame->modelling.pos.z = pos->z;
    frame->modelling.flags &= ~0x20000u;  // rwMATRIXINTERNALIDENTITY
    RwFrame_MarkDirty(frame);
    sandal->m_pAnimNode->SetOrientationFromAtUp(&at, &kAxisY);
    ResetGeometryAlpha(sandal->m_pAnimNode);
    sandal->m_fRatio = weight;
    sandal->m_fTimer = 0.0f;
    sandal->m_pAnimNode->SetBlendAnimPairAndWeight(AnimWord(m_pAnimatedDictionary, 0),
                                                   AnimWord(m_pAnimatedDictionary, 1), 0.0f, 0.0f, weight);
}
