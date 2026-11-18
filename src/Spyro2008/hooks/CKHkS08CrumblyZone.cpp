// CKHkS08CrumblyZone.cpp - reconstructed original translation unit 0x4140f0-0x4150b8 (GAME_TOC1, main_toc1), 24 functions, 24 live.
// Primary class: CKHkS08CrumblyZone  key 0x2ec2  category Hook  size 0x1cc  vtable 0xb25ae8
// Other owners: CKHkCrumblyZone (3)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x4140f0  CKHkS08CrumblyZone_Delete
//   [ ] 0x414140  RegisterCKHkS08CrumblyZoneClass
//   [ ] 0x4141b8  _GLOBAL__I_4141b8
//   [x] 0x4141c8  CKHkS08CrumblyZone_vf100
//   [x] 0x414230  CKHkS08CrumblyZone_MessageProc
//   [x] 0x414288  CKHkS08CrumblyZone_OnDeactivate
//   [x] 0x4142b0  CKHkS08CrumblyZone_OnActivate
//   [x] 0x4142e8  CKHkS08CrumblyZone_Restart
//   [x] 0x414320  CKHkS08CrumblyZone_Start
//   [x] 0x414358  CKHkS08CrumblyZone_Update
//   [x] 0x414380  CKHkS08CrumblyZone_vfF4
//   [x] 0x4143a8  CKHkS08CrumblyZone_vfF0
//   [x] 0x4143d0  CKHkS08CrumblyZone_PostLoad
//   [ ] 0x4143f8  CKHkS08CrumblyZone_Save
//   [x] 0x414420  CKHkS08CrumblyZone_RecursiveRegistration  (inherited: CKHkCrumblyZone's)
//   [x] 0x414448  CKHkS08CrumblyZone_DeleteArray
//   [x] 0x4144e8  CKHkS08CrumblyZone_CreateArray
//   [x] 0x414638  CKHkS08CrumblyZone_UpdateHeroWeight_maybe
//   [x] 0x414808  CKHkCrumblyZone_RestoreIfDestroyed_maybe
//   [x] 0x414840  CKHkCrumblyZone_CrumbleIfIntact_maybe
//   [x] 0x414880  CKHkS08CrumblyZone_OnHit_maybe
//   [x] 0x414e00  CKHkCrumblyZone_TryTriggerCollapse_maybe
//   [x] 0x414e60  CKHkS08CrumblyZone_Create
//   [x] 0x414f28  CKHkS08CrumblyZone_Load
//
//   [ ] 0x9c2778  CKHkS08CrumblyZone_IsKindOfClass  [inline]
//   [ ] 0x9c27d8  CKHkS08CrumblyZone_GetClassType  [inline]
//   [ ] 0x9c27e0  CKHkS08CrumblyZone_GetClassID  [inline]
//   [ ] 0x9c27e8  CKHkS08CrumblyZone_DeletingDestructor  [inline]
//   [ ] 0x9c29a8  CKHkS08CrumblyZone_Destructor  [inline]
#include "Spyro2008/hooks/CKHkS08CrumblyZone.h"
#include "Spyro2008/groups/C22SpyroShims.h"

#include "k2000/io/IKFile.h"
#include "k2000/misc/Engine.h"

#include <cmath>
#include <cstring>

#include "crt/ppc_ops.h"
#include "k2000/cameras/CKSrvCamera.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/system/CTimeManager.h"
#include "k2000/system/IKTime.h"
#include "Renderware/rwcore/RwCamera.h"
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "Spyro2008/logic/CKS08Damage.h"
#include "k2000/logic/CKDamage.h"
#include "k2000/scenegraph/IKBoundingVolume.h"
#include "platform/fps.h"

// 0x004143d0 CKHkS08CrumblyZone_PostLoad: CKHkCrumblyZone_PostLoad (0x406080) only.
int32_t CKHkS08CrumblyZone::PostLoad(int32_t type) { return CKHkCrumblyZone::PostLoad(type); }

namespace {
float S08WordAsFloat(uint32_t word) {
    float value;
    std::memcpy(&value, &word, sizeof value);
    return value;
}
}  // namespace

// 0x00414638 CKHkS08CrumblyZone_UpdateHeroWeight_maybe
void CKHkS08CrumblyZone::VfF8() {
    static const CVector3 kNullVector = {0.0f, 0.0f, 0.0f};  // 0x00c50d64 (TOC +0x4b10)
    const uint8_t count = CountHeroesOnZone();  // 0x00405c30
    const uint32_t flags = m_unk154;
    if ((flags & 4u) != 0 && m_unk68 != count) {
        m_unk68 = count;
        TriggerCollapse(0, &kNullVector, 0);  // vt+0xf4
    } else if (count != 0 && (flags & 0x8000000u) != 0 && (flags & 8u) == 0) {
        TriggerCollapse(0, &kNullVector, 0);
    }
    if (m_unk1C1 == 0) return;
    const uint8_t floor = m_unk1C2;
    if (floor == 0 || count < m_unk1C1) return;
    const float timer = S08WordAsFloat(m_unk1C8) + g_pEngine->m_timeManager->m_pTime->m_afDeltaTime[0];  // TOC +0x4b14
    std::memcpy(&m_unk1C8, &timer, 4);
    const float period = S08WordAsFloat(m_unk1C4);
    if (!(timer >= period)) return;
    const float left = timer - period;
    std::memcpy(&m_unk1C8, &left, 4);
    const RwMatrix* ltm = FrameLtm(static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame);
    const CVector3 at = {ltm->pos.x, ltm->pos.y, ltm->pos.z};
    if (m_unk188 > floor) {
        CollapseAndSpawnBonuses(static_cast<uint16_t>(m_unk188 - floor), &at);  // 0x00405720
        return;
    }
    if (IsInCameraView() != 0) StartCrumble(&at, 0);  // 0x004057b0, 0x0040aab8
}


// 0x00414f28 CKHkS08CrumblyZone_Load
int32_t CKHkS08CrumblyZone::Load(IKFile* file, int32_t type) {
    CKHkCrumblyZone::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadU32LE(file, &m_unk1BC);
    ReadU8(file, &m_unk1C1);
    ReadU8(file, &m_unk1C2);
    ReadU32LE(file, &m_unk1C4);
    ReadU8(file, &m_unk1C0);
    return 1;
}

namespace {
// 0x00406de0 CKHkCrumblyZone_Start (k2000/hooks/CKHkCrumblyZone.cpp, family hooks; local copy until that
// port lands, see the C2.2 spyro report). The zone goes back to its initial state: the volumes off, the
// "current" flag bits taken from their saved twins.
void CrumblyZoneStart(CKHkCrumblyZone* zone) {
    zone->m_bitArray = zone->m_bitArray & 0xfffff9ffu;  // bits 9, 10
    for (uint32_t i = 0; i < zone->m_vUnkA4.m_ui32NbUsedElt; ++i) {
        c22spyro::CollisionDisableVolume(static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision),
                                         static_cast<IKBoundingVolume*>(zone->m_vUnkA4.m_pBlock[i].m_pUnk0));
    }
    uint32_t w = zone->m_unk154;
    w = (w & ~(1u << 19)) | (((w >> 22) & 1u) << 19);
    w = (w & ~(1u << 20)) | (((w >> 23) & 1u) << 20);
    w = (w & ~1u) | ((w >> 24) & 1u);  // the first byte of the word, its lowest bit
    w = (w & ~2u) | (((w >> 25) & 1u) << 1);
    zone->m_unk154 = w;
    uint32_t f = zone->m_bitArray;
    f = (f & ~(1u << 13)) | (((f >> 15) & 1u) << 13);
    f = (f & ~(1u << 14)) | (((f >> 16) & 1u) << 14);
    zone->m_bitArray = f;
    zone->m_unk144[1] = zone->m_unk150;
    zone->m_unk144[0] = zone->m_unk14C;
    zone->m_unk154 = zone->m_unk154 & 0xeffffff7u;
    zone->m_unk128 = 1;
    zone->m_fUnk120 = 0.0f;  // an integer 0 store
    zone->m_unk124 = 0;
    // CKHkActorBase_d82_maybe_ResetRuntime 0x3f6e48: empty.
}
}  // namespace

// 0x00414320 CKHkS08CrumblyZone_Start
void CKHkS08CrumblyZone::Start() {
    CrumblyZoneStart(this);
    m_unk1C8 = 0;
}

// 0x004142b0 CKHkS08CrumblyZone_OnActivate: the base's, then +0x1c8 = 0.
void CKHkS08CrumblyZone::VfA0() {
    CKHkCrumblyZone::VfA0();
    m_unk1C8 = 0;
}

// 0x00414230 CKHkS08CrumblyZone_MessageProc
int32_t CKHkS08CrumblyZone::MessageProc(uint16_t message, void* data) {
    const int32_t answer = CKHkCrumblyZone::MessageProc(message, data);  // 0x0040b500
    if (answer == 3) return 3;
    if (answer == 2) return 2;
    return answer != 0 ? 1 : 0;
}

// 0x004141c8 CKHkS08CrumblyZone_vf100
uint8_t CKHkS08CrumblyZone::Vf100(IKSerializable* hero) {
    if (hero == nullptr || m_unk169 == 0) return 1;
    return static_cast<CKHkS08Hero*>(hero)->IsInCombo() == 0 ? 1 : 0;  // 0x0032a698
}

// 0x00414880 CKHkS08CrumblyZone_OnHit_maybe. The general part after the hero damages is the base's OnHit body, inlined.
void CKHkS08CrumblyZone::OnHit(IKBoundingVolume* volume) {
    CKDamage* damage = static_cast<CKDamage*>(volume->m_unk1c);
    if (volume->m_ui8OwnerType == 3 && damage != nullptr) {
        if (damage->IsKindOfClass(0x998c) != 0) {  // vt+0x08 CKS08HeroDamage
            if (m_unk1C0 != 0 && static_cast<CKS08Damage*>(damage)->m_unk20 != 5) return;
        } else if (damage->IsKindOfClass(0x99cc) != 0 &&  // CKS08ElementDamage
                   (ppc::slw(1u, static_cast<CKS08Damage*>(damage)->m_unk20) & m_unk1BC) != 0) {
            const float dt = g_pEngine->m_timeManager->m_pTime->m_afDeltaTime[0];  // +0x48 -> +0x04 -> +0x1c
            const float amount = damage->m_unk0c != 0 ? dt * damage->m_unk04 : damage->m_unk04;
            uint32_t hits = static_cast<uint32_t>(ppc::fctidz(amount));  // fctidz, the low word compared
            // --fps N (not in the original): a held (per-second) damage chips what this frame's 60 Hz frames would.
            if (dotd::fps::Unlocked() && damage->m_unk0c != 0) {
                hits = static_cast<uint32_t>(dotd::fps::TruncSteps(damage->m_unk04, dt));
            }
            if (hits != 0) {
                const RwFrame* frame = m_vUnkA4.m_ui32NbUsedElt != 0 ? volume->m_pRwFrame
                                                                     : static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame;
                const CVector3 at = {frame->ltm.pos.x, frame->ltm.pos.y, frame->ltm.pos.z};
                if (m_unk188 > hits) {
                    CollapseAndSpawnBonuses(static_cast<uint16_t>(m_unk188 - hits), &at);  // 0x00405720
                    return;
                }
                if (IsInCameraView() == 0) return;  // 0x004057b0
                const RwMatrix* ltm = FrameLtm(static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame);
                const CVector3 node = {ltm->pos.x, ltm->pos.y, ltm->pos.z};
                StartCrumble(&node, 0);  // 0x0040aab8
                return;
            }
        }
    }
    CKHkCrumblyZone::OnHit(volume);  // 0x0040b120's body
}

namespace {
const CVector3 kCrumblyNullPoint{0.0f, 0.0f, 0.0f};  // 0x00c50d64
}  // namespace

// 0x00414808 CKHkCrumblyZone_RestoreIfDestroyed_maybe: a destroyed zone (+0x188 0) restored.
void CKHkCrumblyZone::RestoreIfDestroyed() {
    if (m_unk188 == 0) Restore();  // 0x004085d8
}

// 0x00414840 CKHkCrumblyZone_CrumbleIfIntact_maybe: an intact zone (+0x188 not 0) crumbles (no point, not a child).
void CKHkCrumblyZone::CrumbleIfIntact() {
    if (m_unk188 != 0) StartCrumble(&kCrumblyNullPoint, 0);  // 0x0040aab8
}

// 0x00414e00 CKHkCrumblyZone_TryTriggerCollapse_maybe: without +0x154 bit 3, the collapse (vt+0xf4: mode 0, no point).
void CKHkCrumblyZone::TryTriggerCollapse() {
    if ((m_unk154 & 8u) == 0) TriggerCollapse(0, &kCrumblyNullPoint, 0);  // vt+0xf4
}
