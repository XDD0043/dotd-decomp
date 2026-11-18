// CKHkS08Malefor.cpp - reconstructed original translation unit 0x4e15d0-0x4e7ac0 (GAME_TOC1, main_toc1), 47 functions, 46 live.
// Primary class: CKHkS08Malefor  key 0x3502  category Hook  size 0x1d4  vtable 0xb2a660
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x4e15d0  CKHkS08Malefor_Delete
//   [x] 0x4e1620  CKHkS08Malefor_vf100  (CKHkS08Malefor.h)
//   [x] 0x4e1628  CKHkS08Malefor_vf104  (CKHkS08Malefor.h)
//   [x] 0x4e1630  CKHkS08Malefor_vf108  (CKHkS08Malefor.h)
//   [x] 0x4e1638  CKHkS08Malefor_vf11C  (inherited: CKHkGolem's (empty))
//   [ ] 0x4e1640  CKHkS08Malefor_InitCollisionVolume_maybe  [dead]
//   [ ] 0x4e16b0  CKHkS08Malefor_UpdateScaleByDistance_maybe  [dead: no pointer to its descriptor 0xbcf228, no call]
//   [x] 0x4e17d8  CKHkS08Malefor_AccumulateDamage_maybe
//   [x] 0x4e1a80  CKHkS08Malefor_AccumulateDamage_2_maybe
//   [x] 0x4e1d28  CKHkS08Malefor_vf114
//   [x] 0x4e1d80  CKHkS08Malefor_UpdateHotSpotSegmentVolumes_maybe
//   [x] 0x4e2080  CKHkS08Malefor_GetInfo
//   [ ] 0x4e20d0  CKHkS08Malefor_SpawnExplosionAt_maybe  [dead: no pointer to its descriptor 0xbcf258, no call]
//   [x] 0x4e2190  CKHkS08Malefor_TriggerHotSpotExplosionFx_maybe
//   [x] 0x4e2270  CKHkS08Malefor_SpawnDamageImpactFx_maybe
//   [x] 0x4e2510  CKHkS08Malefor_SetCollisionActive_maybe
//   [x] 0x4e2698  CKHkS08Malefor_Resume  (inherited: CKHkGolem's)
//   [x] 0x4e26c0  CKHkS08Malefor_Pause  (inherited: CKHkGolem's)
//   [x] 0x4e26e8  CKHkS08Malefor_Stop  (inherited: CKHkGolem's)
//   [ ] 0x4e2710  CKHkS08Malefor_Save
//   [x] 0x4e2738  CKHkS08Malefor_RecursiveRegistration  (inherited: CKHkGolem's)
//   [x] 0x4e2760  CKHkS08Malefor_Destroy
//   [ ] 0x4e27a8  CKHkS08Malefor_DestructBody  [dead: no pointer to its descriptor 0xbcf2a8, no call]
//   [ ] 0x4e2820  CKHkS08Malefor_Construct_2  [dead: no pointer to its descriptor 0xbcf2b0, no call]
//   [x] 0x4e2860  CKHkS08Malefor_Construct
//   [x] 0x4e28a0  CKHkS08Malefor_DeleteArray
//   [ ] 0x4e2940  RegisterCKHkS08MaleforClass
//   [ ] 0x4e29c8  _GLOBAL__D_4e29c8
//   [ ] 0x4e29d8  _GLOBAL__I_4e29d8
//   [x] 0x4e29e8  CKHkS08Malefor_OnDeactivate
//   [x] 0x4e2ad8  CKHkS08Malefor_OnActivate
//   [x] 0x4e2c48  CKHkS08Malefor_MessageProc
//   [x] 0x4e2dd8  CKHkS08Malefor_DeletingDestructor  (the destructor)
//   [x] 0x4e2e60  CKHkS08Malefor_Destructor  (the destructor)
//   [x] 0x4e2ed8  CKHkS08Malefor_Restart
//   [x] 0x4e2fb0  CKHkS08Malefor_CreateArray
//   [x] 0x4e3070  CKHkS08Malefor_Create
//   [x] 0x4e30d0  CKHkS08Malefor_Start
//   [x] 0x4e3198  CKHkS08Malefor_PostLoad
//   [x] 0x4e3248  CKHkS08Malefor_ProcessDamageContacts_maybe
//   [x] 0x4e3eb8  CKHkS08Malefor_Load
//   [x] 0x4e54d0  CKHkS08Malefor_UpdateCollisionVolumesFromBones_maybe
//   [x] 0x4e6560  CKHkS08Malefor_vf110
//   [x] 0x4e6570  CKHkS08Malefor_vf10C
//   [x] 0x4e6580  CKHkS08Malefor_SpawnElementHitFx_maybe
//   [x] 0x4e6fd8  CKHkS08Malefor_ApplyPendingDamage_maybe
//   [x] 0x4e75d8  CKHkS08Malefor_Update
//
//   [ ] 0x9c63f8  CKHkS08Malefor_IsKindOfClass  [inline]
//   [ ] 0x9c6458  CKHkS08Malefor_GetClassType  [inline]
//   [ ] 0x9c6460  CKHkS08Malefor_GetClassID  [inline]
#include "Spyro2008/hooks/CKHkS08Malefor.h"

#include <cmath>

#include "Renderware/rpprtstd/RpPrtStd.h"
#include "Renderware/rpprtstd/RpPrtStdRuntime.h"
#include "Renderware/rwcore/RwCamera.h"
#include "Spyro2008/groups/IKGrpHero.h"
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "Spyro2008/logic/CKS08Damage.h"
#include "Spyro2008/logic/CKS08ElementDamage.h"
#include "Spyro2008/logic/CKS08GameManager.h"
#include "crt/ppc_ops.h"
#include "k2000/core/IKInfo.h"
#include "k2000/fx/IKFx.h"
#include "k2000/geometry/CGeometry.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKGolemAttackCommon.h"
#include "k2000/logic/CKLevel.h"
#include "k2000/logic/CKSector.h"
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/logic/IKFxData.h"
#include "k2000/logic/fx/CKExplosionNodeFx.h"
#include "k2000/math/Math.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/OnNewHit.h"
#include "k2000/scenegraph/CNode.h"
#include "k2000/scenegraph/CParticlesNodeFx.h"
#include "k2000/scenegraph/CSGBranch.h"
#include "k2000/scenegraph/CSGSectorRoot.h"
#include "k2000/scenegraph/CTrailNodeFx.h"
#include "k2000/scenegraph/IKBoundingVolume.h"
#include "k2000/services/CKSrvCollision.h"
#include "k2000/services/CKSrvFx.h"
#include "k2000/system/IKTime.h"

// 0x004e3eb8 CKHkS08Malefor_Load
int32_t CKHkS08Malefor::Load(IKFile* file, int32_t type) {
    CKHkGolem::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    IKFile_ReadRef(file, &m_unkE4);
    IKFile_ReadRef(file, &m_unkE8);
    ReadU8(file, &m_unkEC);
    m_apUnkF0 = static_cast<IKSerializable**>(
        Mem_AllocAligned16(m_unkEC * static_cast<uint32_t>(sizeof(IKSerializable*))));
    IKFile_ReadObjectRefArray(file, m_apUnkF0, m_unkEC);
    IKFile_ReadObjectRefArray(file, m_apUnkF4, 2);
    for (uint32_t& word : m_unkFC) ReadU32LE(file, &word);
    IKFile_ReadRef(file, &m_unk164);
    ReadU8(file, &m_unk168);
    IKFile_ReadRef(file, &m_unk174);
    IKFile_ReadRef(file, &m_pUnk178);
    IKFile_ReadRef(file, &m_unk17C);
    IKFile_ReadRef(file, &m_unk180);
    IKFile_ReadRef(file, &m_unk184);
    ReadF32LE(file, &m_unkE0);
    ReadU32LE(file, &m_unk16C);
    ReadU32LE(file, &m_unk170);
    IKFile_ReadRef(file, &m_unk188);
    for (IKSerializable*& object : m_apUnk110) IKFile_ReadRef(file, &object);
    for (IKSerializable*& object : m_apUnk140) IKFile_ReadRef(file, &object);
    IKFile_ReadRef(file, &m_unk18C);
    IKFile_ReadRef(file, &m_unk190);
    for (float& value : m_afUnk194) ReadF32LE(file, &value);  // the words as read (ReadU32LE's bits)
    return 1;
}

// 0x004e2e60 CKHkS08Malefor_Destructor: the contact history's nodes (+0xc0) back to their pool, the list cleared.
CKHkS08Malefor::~CKHkS08Malefor() {
    for (ContactHistoryNode* node = m_unkC0; node != nullptr;) {
        ContactHistoryNode* next = node->m_pNext;  // +0x14
        ContactHistory_FreeNode(node);
        node = next;
    }
    m_unkC0 = nullptr;
}

// 0x004e2760 CKHkS08Malefor_Destroy
void CKHkS08Malefor::Destroy() {
    CKHkGolem::Destroy();  // 0x004c0388
    Mem_FreeAligned16(m_apUnkF0);  // 0x00052fb8
    m_apUnkF0 = nullptr;
}

// 0x004e2080 CKHkS08Malefor_GetInfo
int32_t CKHkS08Malefor::GetInfo(IKInfo* info, int32_t request) {
    const int32_t base = CKHkGolem::GetInfo(info, request);  // 0x004c0678
    if (base == 2) return 2;
    return base != 0 ? 1 : 0;
}

// 0x004e1d28 CKHkS08Malefor_vf114
void CKHkS08Malefor::ReleaseAllEntryObjects() {
    CKHkGolem::ReleaseAllEntryObjects();  // 0x004bfb88
    OnMark24Off(3);  // vt+0x110
}

// ---- C2.8 port-last Z6: Malefor at run time ----

namespace {

const CVector3 kNullVector = {0.0f, 0.0f, 0.0f};  // 0x00c50d64 (TOC +0x6de8)
const CVector3 kAxisY = {0.0f, 1.0f, 0.0f};        // 0x00c50d40 (TOC +0x6dcc)
constexpr float kOne = 1.0f;                       // TOC +0x6d5c
constexpr float kZero = 0.0f;                      // TOC +0x6d64
constexpr float kMinRadius = 0.001f;               // TOC +0x6d60 (0x3a83126f)
constexpr float kHalf = 0.5f;                      // TOC +0x6d74
constexpr float kWeakFactorKind89 = 0.05f;         // TOC +0x6d6c (0x3d4ccccd)
constexpr float kHistoryTime = -1000.0f;           // TOC +0x6dc8 (0xc47a0000)
constexpr float kWeakVolumeRadius = 5.0f;          // TOC +0x6d48 (0x40a00000)
constexpr float kLevel3Rate = 60.0f;               // TOC +0x6df0
constexpr float kLevel2Rate = 30.0f;               // TOC +0x6df4
constexpr float kLevel1Rate = 20.0f;               // TOC +0x6df8

CKS08GameManager* MaleforGameManager() { return static_cast<CKS08GameManager*>(g_pEngine->m_gameManager); }
CKSrvFx* MaleforSrvFx() { return static_cast<CKSrvFx*>(g_pEngine->m_srvFx); }
CKSrvCollision* MaleforSrvCollision() { return static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision); }

// The golem's reference `index` (vt+0xf8): the hot spots 6 (the body), 12 and 13 (the trails).
CSGHotSpot* MaleforHotSpot(const CKHkS08Malefor* malefor, uint32_t index) {
    return static_cast<CSGHotSpot*>(malefor->GetReference(index));
}

void HideNode(CNode* node) { node->m_sgProperties = (node->m_sgProperties & 0xfffffffbu) | 4u; }
void ShowNode(CNode* node) { node->m_sgProperties &= 0xfffffffbu; }

// The unsigned / signed words converted as the original does it (fcfid of the zero- / sign-extended value, frsp).
float UnsignedToFloat(uint32_t value) { return static_cast<float>(static_cast<double>(value)); }
float SignedToFloat(int32_t value) { return static_cast<float>(static_cast<double>(static_cast<int64_t>(value))); }

// The weak volume set up (PostLoad, Start): no properties, owned by Malefor with owner type 1, flag 0x80 of its infos,
// radius 5.0 (the stores in the original's order).
void SetUpWeakVolume(IKBoundingVolume* volume, CKHkS08Malefor* owner) {
    volume->m_ui16PropertiesFlags = 0;
    volume->m_ui8OwnerType = 0;
    volume->m_ui16PropertiesFlags = static_cast<uint16_t>(volume->m_ui16PropertiesFlags & 0xfeffu);
    volume->m_ui8OwnerType = 1;
    volume->m_pOwner = owner;
    volume->m_ba8Infos = static_cast<uint8_t>((volume->m_ba8Infos & 0x7fu) | 0x80u);
    volume->m_fRadius = kWeakVolumeRadius;
}

// The particles per point of a node: the standard emitter property's count (a word store of fctidz's low word) and the
// node's byte.
void SetParticlesPerPoint(CParticlesNodeFx* fx, int64_t count) {
    RpPrtStdEmitter* emitter = fx->m_pRpPrtStdEmitter;
    RpPrtStdEmitterStandard* standard = reinterpret_cast<RpPrtStdEmitterStandard*>(
        reinterpret_cast<uint8_t*>(emitter) + emitter->emtClass->propTab->propOffset[1]);
    standard->emtPrtEmit = static_cast<int32_t>(static_cast<uint32_t>(count));  // stw +0x48
    fx->m_ui8NbEmitParticlesPerPoint = static_cast<uint8_t>(count);             // stb +0x51
}

// Below 64 points, `point` appended to the node's emit points (z, x, y stored) with property 0x2000.
void AppendEmitPoint(CParticlesNodeFx* fx, const CVector3& point) {
    if (fx->m_ui8NbActivePoints > 0x3f) return;
    RwV3d* at = &fx->m_pAdvEmtPointList->pointList[fx->m_ui8NbActivePoints];
    at->z = point.z;
    at->x = point.x;
    at->y = point.y;
    fx->m_sgProperties = (fx->m_sgProperties & ~0x2000u) | 0x2000u;
    fx->m_ui8NbActivePoints = static_cast<uint8_t>(fx->m_ui8NbActivePoints + 1);
}

// The explosion of `data` (CKSrvFx::AcquireFx, the reserving lookup 0x9c6468 or its inlined copies) placed at
// `position` (SetTranslation 0x1b66e8), triggered and released (vt+0x54).
void TriggerExplosionAt(CKHkS08Malefor* owner, IKSerializable* data, const CVector3* position) {
    IKFx* fx = MaleforSrvFx()->AcquireFx(static_cast<IKFxData*>(data), owner);
    if (fx == nullptr) return;
    CKExplosionNodeFx* explosion = static_cast<CKExplosionNodeFx*>(fx);
    explosion->SetTranslation(position, owner);  // 0x001b66e8
    explosion->Trigger(owner, nullptr);          // 0x001b82a8
    fx->ReleaseReservation(owner);               // vt+0x54
}

// The damage's amount this frame (+0x0c: per second, dt x amount).
float FrameAmount(const CKS08Damage* damage, float dt) {
    return damage->m_unk0c != 0 ? dt * damage->m_unk04 : damage->m_unk04;
}

// The pending damage's whole part applied (fcmpu + cror: a NaN waits): the fraction kept (fctidz, its low word as
// unsigned, fcfid / frsp), the whole part, when not 0, off the health.
void ApplyWholePoints(CKHkGolem* golem, float* pending) {
    const float value = *pending;
    if (!(value >= kOne)) return;
    const int64_t whole = ppc::fctidz(value);
    const uint32_t low = static_cast<uint32_t>(whole);
    *pending = value - static_cast<float>(static_cast<double>(static_cast<uint64_t>(low)));
    if (static_cast<int32_t>(low) != 0) golem->ApplyDamagePoints(static_cast<int32_t>(low));  // 0x004becc8
}

}  // namespace

// 0x004e17d8 CKHkS08Malefor_AccumulateDamage_maybe (weak): an element damage (0x99cc) of kind 0..7 adds amount x the
// weak factor (+0x19c + 4 x kind, the jump table 0x004e1924), kinds 8 / 9 amount x 0.05, another kind nothing (fmadds);
// a hero damage (0x998c) adds amount x +0x1bc; any other damage replaces the slot with the amount.
void CKHkS08Malefor::AccumulateWeakDamage(float amount, CKS08Damage* damage, uint32_t slot) {
    if (damage->IsKindOfClass(0x99cc) != 0) {
        const uint32_t kind = damage->m_unk20;
        if (kind <= 9) {
            const float factor = kind >= 8 ? kWeakFactorKind89 : m_afUnk194[2 + kind];
            m_afUnkCC[slot] = ppc::fmadds(amount, factor, m_afUnkCC[slot]);
        }
    } else if (damage->IsKindOfClass(0x998c) != 0) {
        m_afUnkCC[slot] = ppc::fmadds(amount, m_afUnk194[10], m_afUnkCC[slot]);
    } else {
        m_afUnkCC[slot] = amount;
    }
    ApplyWholePoints(this, &m_afUnkCC[slot]);
}

// 0x004e1a80 CKHkS08Malefor_AccumulateDamage_2_maybe: CKHkS08DragonCityGolem's: kinds 0..7 the golem's factors
// (+0x94 + 4 x kind, the jump table 0x004e1bcc), kinds 8 / 9 kind 8's (+0xb4), a hero damage +0xb8.
void CKHkS08Malefor::AccumulateDamage(float amount, CKS08Damage* damage, uint32_t slot) {
    if (damage->IsKindOfClass(0x99cc) != 0) {
        const uint32_t kind = damage->m_unk20;
        if (kind <= 9) {
            m_afUnkCC[slot] = ppc::fmadds(amount, m_af94[kind >= 8 ? 8 : kind], m_afUnkCC[slot]);
        }
    } else if (damage->IsKindOfClass(0x998c) != 0) {
        m_afUnkCC[slot] = ppc::fmadds(amount, m_af94[9], m_afUnkCC[slot]);
    } else {
        m_afUnkCC[slot] = amount;
    }
    ApplyWholePoints(this, &m_afUnkCC[slot]);
}

// 0x004e1d80 CKHkS08Malefor_UpdateHotSpotSegmentVolumes_maybe (from SetTrailRibbonsActive on): the node's world matrices
// updated (vt+0x50), then each trail's two ribbons get their fixed anchors (mode 1) across its hot spot (12 for +0x18c,
// 13 for +0x190): the hot spot's position -/+ half the ribbon's width (+0x194 / +0x198 x 0.5) along its right axis
// (fmadds).
void CKHkS08Malefor::UpdateTrailAnchors() {
    CSGHotSpot* hotSpots[2] = {MaleforHotSpot(this, 0xc), MaleforHotSpot(this, 0xd)};
    static_cast<CSGMovable*>(m_pKGLObject)->ForceWorldMatrixUpdate();  // vt+0x50
    CTrailNodeFx* trails[2] = {m_unk18C, m_unk190};
    for (uint32_t t = 0; t < 2; ++t) {
        if (trails[t] == nullptr) continue;
        CMatrix34 matrix;
        hotSpots[t]->GetWorldMatrix(&matrix);  // 0x000ce970
        for (uint32_t ribbon = 0; ribbon < 2; ++ribbon) {
            const float half = m_afUnk194[ribbon] * kHalf;
            STrailNodeData* trail = trails[t]->m_apTrailData[ribbon];
            trail->m_v3Extrem1.x = ppc::fmadds(half, -matrix.m_right.x, matrix.m_pos.x);
            trail->m_v3Extrem1.y = ppc::fmadds(half, -matrix.m_right.y, matrix.m_pos.y);
            trail->m_v3Extrem1.z = ppc::fmadds(half, -matrix.m_right.z, matrix.m_pos.z);
            trail->m_v3Extrem2.x = ppc::fmadds(half, matrix.m_right.x, matrix.m_pos.x);
            trail->m_v3Extrem2.y = ppc::fmadds(half, matrix.m_right.y, matrix.m_pos.y);
            trail->m_v3Extrem2.z = ppc::fmadds(half, matrix.m_right.z, matrix.m_pos.z);
        }
    }
}

// 0x004e2190 CKHkS08Malefor_TriggerHotSpotExplosionFx_maybe: an explosion of `data` acquired, triggered where it is and
// released. BUG(original): the hot spot 6's world position is computed and never set on the explosion.
void CKHkS08Malefor::TriggerExplosion(IKSerializable* data) {
    IKFx* fx = MaleforSrvFx()->AcquireFx(static_cast<IKFxData*>(data), this);  // 0x009c6468
    if (fx == nullptr) return;
    CVector3 unused;
    MaleforHotSpot(this, 6)->GetWorldPosition(&unused);  // 0x000ce790
    static_cast<CKExplosionNodeFx*>(fx)->Trigger(this, nullptr);  // 0x001b82a8
    fx->ReleaseReservation(this);                                  // vt+0x54
}

// 0x004e2270 CKHkS08Malefor_SpawnDamageImpactFx_maybe: an element damage of kind 0..9 (the jump table 0x004e2344): the
// kind's impact explosion (+0x110 + 4 x kind; 8 / 9: +0x130) placed at `position` turned to `direction`, triggered and
// released; another element kind nothing; any other damage the golem's hit explosion (SpawnFxAt, with copies).
void CKHkS08Malefor::SpawnDamageImpactFx(const CVector3* position, const CVector3* direction, CKS08Damage* damage) {
    if (damage->IsKindOfClass(0x99cc) == 0) {
        const CVector3 at = *position;
        const CVector3 along = *direction;
        SpawnFxAt(&at, &along);  // 0x004c2758
        return;
    }
    const uint32_t kind = damage->m_unk20;
    if (kind > 9) return;
    IKFx* fx = MaleforSrvFx()->AcquireFx(static_cast<IKFxData*>(m_apUnk110[kind >= 8 ? 8 : kind]), this);
    if (fx == nullptr) return;
    CKExplosionNodeFx* explosion = static_cast<CKExplosionNodeFx*>(fx);
    explosion->SetPosition(direction, position, this);  // 0x001b6438
    explosion->Trigger(this, nullptr);                  // 0x001b82a8
    fx->ReleaseReservation(this);                       // vt+0x54
}

// 0x004e2510 CKHkS08Malefor_SetCollisionActive_maybe: weak on (from off): the start explosion (+0x174), the node +0x178
// shown, the volume switched on (EnableVolume) with property 0x100. Off (from on): the end explosion (+0x17c), the node
// hidden, the volume switched off with property 0x100 cleared. The byte +0x168 takes `on` either way.
void CKHkS08Malefor::SetWeak(uint8_t on) {
    if (on == 0) {
        if (m_unk168 != 0) {
            TriggerExplosion(m_unk17C);
            m_unk168 = 0;
            if (m_pUnk178 != nullptr) HideNode(m_pUnk178);
            if (m_unk164 != nullptr) {
                MaleforSrvCollision()->DisableVolume(m_unk164);  // 0x001920e8
                m_unk164->m_ui16PropertiesFlags = static_cast<uint16_t>(m_unk164->m_ui16PropertiesFlags & ~0x100u);
            }
        }
    } else if (m_unk168 == 0) {
        TriggerExplosion(m_unk174);
        m_unk168 = 1;
        if (m_pUnk178 != nullptr) ShowNode(m_pUnk178);
        if (m_unk164 != nullptr) {
            MaleforSrvCollision()->EnableVolume(m_unk164);  // 0x00192090
            m_unk164->m_ui16PropertiesFlags = static_cast<uint16_t>(m_unk164->m_ui16PropertiesFlags | 0x100u);
        }
    }
    m_unk168 = on;
}

// 0x004e29e8 CKHkS08Malefor_OnDeactivate: CKHkGolem's, weak off, the node +0x178 hidden, the volume out of its parent
// (vt+0x78) and under sector 0's root (vt+0x70).
void CKHkS08Malefor::VfA4() {
    CKHkGolem::VfA4();  // 0x004bfc88
    SetWeak(0);
    if (m_pUnk178 != nullptr) HideNode(m_pUnk178);
    if (m_unk164->m_pParent != nullptr) m_unk164->m_pParent->RemoveChild(m_unk164);  // vt+0x78
    CKSector* base = static_cast<CKSector*>(g_pEngine->m_level->m_vpSectors.m_pBlock[0]);
    base->m_pSectorRoot->AddChild(m_unk164);  // vt+0x70
}

// 0x004e2ad8 CKHkS08Malefor_OnActivate: CKHkGolem's, weak off; the node +0x178 hidden and its geometries of blend mode
// 2 (render flags bits 8-9) put in stage 0x2e (the low six bits); the volume out of its parent (vt+0x78), hung under
// the hot spot 6 (AttachVolume) and switched off.
void CKHkS08Malefor::VfA0() {
    CKHkGolem::VfA0();  // 0x004c00c8
    SetWeak(0);
    if (m_pUnk178 != nullptr) {
        HideNode(m_pUnk178);
        for (CGeometry* geometry = static_cast<CGeometry*>(m_pUnk178->m_lGeometryList); geometry != nullptr;
             geometry = geometry->m_pNext) {
            if (((geometry->m_BitProperties >> 8) & 3u) != 2u) continue;
            geometry->m_BitProperties = (((geometry->m_BitProperties & ~0x20u) | 0x20u) & 0xffffffe0u) | 0xeu;
        }
    }
    if (m_unk164->m_pParent != nullptr) m_unk164->m_pParent->RemoveChild(m_unk164);  // vt+0x78
    MaleforHotSpot(this, 6)->AttachVolume(m_unk164);    // 0x000ce2b8
    MaleforSrvCollision()->DisableVolume(m_unk164);     // 0x001920e8
}

// 0x004e2c48 CKHkS08Malefor_MessageProc: CKHkGolem's answer merged with Malefor's: 0x99e weak on, 0x99f weak off, 0x9a0
// / 0x9a1 (while weak, with the node) the node +0x178 shown / hidden; those answer 0, the others 1.
int32_t CKHkS08Malefor::MessageProc(uint16_t message, void* data) {
    const int32_t base = CKHkGolem::MessageProc(message, data);  // 0x004bf348
    int32_t own = 0;
    switch (message) {
    case 0x99e: SetWeak(1); break;
    case 0x99f: SetWeak(0); break;
    case 0x9a0:
        if (m_unk168 != 0 && m_pUnk178 != nullptr) ShowNode(m_pUnk178);
        break;
    case 0x9a1:
        if (m_unk168 != 0 && m_pUnk178 != nullptr) HideNode(m_pUnk178);
        break;
    default: own = 1; break;
    }
    if (base == 3 || own == 3) return 3;
    if (base == 2 || own == 2) return 2;
    if (base != 0) return own;
    return 0;
}

// 0x004e2ed8 CKHkS08Malefor_Restart: CKHkGolem's; with the sector loaded (+0x0c bit 2 clear) weak off and the volume
// switched off, else the weak byte cleared; the damage state cleared, the node +0x178 hidden, not weak.
void CKHkS08Malefor::Restart() {
    CKHkGolem::Restart();  // 0x004bfa18
    if ((m_bitArray & 4u) == 0) {
        SetWeak(0);
        MaleforSrvCollision()->DisableVolume(m_unk164);  // 0x001920e8
    } else {
        m_unk168 = 0;
    }
    m_afUnkCC[1] = 0.0f;
    m_apUnkC4[0] = nullptr;
    m_abUnkD4[0] = 0;
    m_afUnkD8[0] = 0.0f;
    m_afUnk134[1] = 0.0f;
    m_afUnkCC[0] = 0.0f;
    m_apUnkC4[1] = nullptr;
    m_abUnkD4[1] = 0;
    m_afUnkD8[1] = 0.0f;
    m_afUnk134[2] = 0.0f;
    if (m_pUnk178 != nullptr) HideNode(m_pUnk178);
    m_unk168 = 0;
}

// 0x004e30d0 CKHkS08Malefor_Start: CKHkGolem's, the damage state cleared, the weak volume set up.
void CKHkS08Malefor::Start() {
    CKHkGolem::Start();  // 0x004bf970
    m_apUnkC4[0] = nullptr;
    m_abUnkD4[0] = 0;
    m_apUnkC4[1] = nullptr;
    m_abUnkD4[1] = 0;
    m_afUnkCC[1] = 0.0f;
    m_afUnkD8[0] = 0.0f;
    m_afUnk134[1] = 0.0f;
    m_afUnkCC[0] = 0.0f;
    m_afUnkD8[1] = 0.0f;
    m_afUnk134[2] = 0.0f;
    SetUpWeakVolume(m_unk164, this);
}

// 0x004e3198 CKHkS08Malefor_PostLoad: CKHkGolem's; a level load (type 0) sets the weak volume up. Returns 0 (li r3, 0
// on both paths).
int32_t CKHkS08Malefor::PostLoad(int32_t type) {
    CKHkGolem::PostLoad(type);  // 0x004bf308
    if (type == K_LEVEL_PLATEFORMS) SetUpWeakVolume(m_unk164, this);
    return 0;
}

// 0x004e3248 CKHkS08Malefor_ProcessDamageContacts_maybe (vt+0x120). While weak, the weak volume's collisions first:
// with a contact set, the other volume dealing damage (properties bit 3) through a damage without +0x08 on the weak
// volume itself: a continuous damage (+0x0c) is kept for the hero's dragon; a one-shot one hits once per contact (the
// history +0x20 with the hero, or +0xc0 without an owner for a damage with +0x26): the explosion +0x180 at the contact,
// the hero's fury (+0x16c) and the weak damage. (The damage's IsKindOfClass(0x99cc) is asked and not used.)
// Then the attack's volumes (DOTD: the attack is passed; the original passes its +0x08 vector): the same test on a
// volume of the attack whose hits count (+0x0c), not the weak volume, and while weak only for element kinds 8 / 9; a hit
// (KStub_Return1_4becc0: every hit accepted) spawns the element's impact explosion at the contact turned toward the
// hero and, for a non-element damage, the bonuses; a combo hit for a hero (0x25c2) and the damage accumulated. Both
// histories age at the end.
void CKHkS08Malefor::ProcessContacts(IKTime* clock, CKGolemAttackCommon* attack) {
    if (m_unk168 != 0) {
        for (ICollision* c = static_cast<ICollision*>(m_unk164->m_CollisionResList); c != nullptr; c = c->m_pNext) {
            IKBoundingVolume* own;
            IKBoundingVolume* other;
            if (static_cast<IKBoundingVolume*>(c->GetBoundingVolume1())->m_pOwner == this) {  // vt+0x00
                own = static_cast<IKBoundingVolume*>(c->GetBoundingVolume1());
                other = static_cast<IKBoundingVolume*>(c->GetBoundingVolume2());  // vt+0x04
            } else {
                own = static_cast<IKBoundingVolume*>(c->GetBoundingVolume2());
                other = static_cast<IKBoundingVolume*>(c->GetBoundingVolume1());
            }
            if (c->HasContactSet() == 0) continue;  // vt+0x08
            if ((other->m_ui16PropertiesFlags & 8u) == 0) continue;
            CKS08Damage* damage = static_cast<CKS08Damage*>(other->m_unk1c);
            CKHkS08Hero* hero = static_cast<CKHkS08Hero*>(other->m_pOwner);
            if (damage == nullptr) continue;
            (void)damage->IsKindOfClass(0x99cc);  // the answer is not used
            if (damage->m_unk08 != 0 || m_unk164 != own) continue;
            if (damage->m_unk0c != 0) {
                m_apUnkC4[hero->GetDragonIndex()] = damage;  // 0x00361960
                continue;
            }
            uint8_t hit;
            if (damage->m_unk26 == 0) {
                hit = ContactHistory_Touch(kHistoryTime, kHistoryTime, &m_unk20, other, hero);  // 0x0098f380
            } else {
                hit = ContactHistory_Touch(kHistoryTime, kHistoryTime, &m_unkC0, other, nullptr);
            }
            if (hit == 0) continue;
            const CVector3 contact = *c->GetWorldContactPoint();  // vt+0x20
            TriggerExplosionAt(this, m_unk180, &contact);
            MaleforGameManager()->AddDragonFury(hero->GetDragonIndex(), m_unk16C);  // 0x004fd528
            const float amount = FrameAmount(damage, clock->m_afDeltaTime[IKTime::SCALABLE_GAME_TIME]);
            AccumulateWeakDamage(amount, damage, hero->GetDragonIndex());
        }
    }
    for (uint32_t i = 0; i < attack->m_unk08Count; ++i) {
        IKBoundingVolume* volume = attack->m_apUnk08[i]->m_unk00;
        for (ICollision* c = static_cast<ICollision*>(volume->m_CollisionResList); c != nullptr; c = c->m_pNext) {
            IKBoundingVolume* own;
            IKBoundingVolume* other;
            if (static_cast<IKBoundingVolume*>(c->GetBoundingVolume1())->m_pOwner == this) {
                own = static_cast<IKBoundingVolume*>(c->GetBoundingVolume1());
                other = static_cast<IKBoundingVolume*>(c->GetBoundingVolume2());
            } else {
                own = static_cast<IKBoundingVolume*>(c->GetBoundingVolume2());
                other = static_cast<IKBoundingVolume*>(c->GetBoundingVolume1());
            }
            if (c->HasContactSet() == 0) continue;
            CKGolemAttackCommon::Entry08* entry = nullptr;  // the last entry of this volume
            for (uint32_t k = 0; k < attack->m_unk08Count; ++k) {
                if (attack->m_apUnk08[k]->m_unk00 == own) entry = attack->m_apUnk08[k];
            }
            if ((other->m_ui16PropertiesFlags & 8u) == 0) continue;
            CKS08Damage* damage = static_cast<CKS08Damage*>(other->m_unk1c);
            // DOTD: the owner of a damage volume with bit 3 is a hero (CKHkS08Hero); the original reads its dragon index
            // (+0x24 byte) whatever it is.
            CKHkS08Hero* hero = static_cast<CKHkS08Hero*>(other->m_pOwner);
            if (damage == nullptr) continue;
            const bool kind89 = damage->IsKindOfClass(0x99cc) != 0 && (damage->m_unk20 == 8 || damage->m_unk20 == 9);
            if (!kind89 && m_unk168 != 0) continue;
            if (entry == nullptr || damage->m_unk08 != 0 || entry->m_unk0c == 0 || m_unk164 == own) continue;
            if (damage->m_unk0c != 0) {
                m_apUnkC4[hero->GetDragonIndex()] = damage;
                continue;
            }
            uint8_t hit;
            if (damage->m_unk26 == 0) {
                hit = ContactHistory_Touch(kHistoryTime, kHistoryTime, &m_unk20, other, hero);
            } else {
                hit = ContactHistory_Touch(kHistoryTime, kHistoryTime, &m_unkC0, other, nullptr);
            }
            if (hit == 0) continue;
            {
                // KStub_Return1_4becc0 (every hit accepted): the impact explosion and, without an element, the bonuses.
                const CVector3 contact = *c->GetWorldContactPoint();  // vt+0x20
                const RwFrame* ownFrame = own->m_pRwFrame;
                const RwFrame* heroFrame = static_cast<const CSGMovable*>(hero->m_pKGLObject)->m_pRwFrame;
                float dy = heroFrame->ltm.pos.y - ownFrame->ltm.pos.y;
                float dx = heroFrame->ltm.pos.x - ownFrame->ltm.pos.x;
                float dz = heroFrame->ltm.pos.z - ownFrame->ltm.pos.z;
                const float length = std::sqrt(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));  // Math_Sqrtf 0x10690
                if (length != kZero) {
                    const float inverse = kOne / length;
                    dz = dz * inverse;
                    dx = dx * inverse;
                    dy = dy * inverse;
                }
                const CVector3 direction{dx, dy, dz};
                SpawnDamageImpactFx(&contact, &direction, damage);
                if (damage->IsKindOfClass(0x99cc) == 0) {
                    const CVector3 at = contact;
                    SpawnBonuses(&at, &kAxisY);  // 0x004bed58
                }
            }
            IKSerializable* attacker = other->m_pOwner;
            if (attacker->IsKindOfClass(0x25c2) != 0) {
                CKS08GameManager* manager = MaleforGameManager();
                const uint8_t dragon = static_cast<CKHkS08Hero*>(attacker)->GetDragonIndex();
                const CVector3 point = *c->GetWorldContactPoint();
                OnNewHitW(manager, dragon, &point);  // OnNewHitW_2 0x004fe5f8
            }
            const float amount = FrameAmount(damage, clock->m_afDeltaTime[IKTime::SCALABLE_GAME_TIME]);
            AccumulateDamage(amount, damage, hero->GetDragonIndex());
        }
    }
    ContactHistory_Update(&m_unk20, clock);  // 0x0098f430
    ContactHistory_Update(&m_unkC0, clock);
}

// 0x004e54d0 CKHkS08Malefor_UpdateCollisionVolumesFromBones_maybe (vt+0x10c / +0x110 with on 1 / 0): the trails' ribbons
// switched (CTrailNodeFx_SetRibbonActive 0x9bdfb8 inlined, the geometry laid out between the anchors either way): value
// 1 or 3 both ribbons of +0x18c, 2 or 3 both of +0x190. On first lays the fixed anchors out across the hot spots
// (UpdateTrailAnchors). The inlined copies test each ribbon's state before the call, as SetRibbonActive does.
void CKHkS08Malefor::SetTrailRibbonsActive(int32_t on, uint32_t value) {
    const uint32_t active = on != 0 ? 1u : 0u;
    if (on != 0) UpdateTrailAnchors();  // 0x004e1d80
    if (m_unk18C != nullptr && (value == 1 || value == 3)) {
        for (uint32_t ribbon = 0; ribbon < 2; ++ribbon) m_unk18C->SetRibbonActive(ribbon, active, 1);
    }
    if (m_unk190 != nullptr && value - 2u <= 1u) {
        for (uint32_t ribbon = 0; ribbon < 2; ++ribbon) m_unk190->SetRibbonActive(ribbon, active, 1);
    }
}

// 0x004e6580 CKHkS08Malefor_SpawnElementHitFx_maybe: the position of the hot spot 6 (without one, the node's LTM
// position); an element damage of kind 0..9 (the jump table 0x004e667c): the kind's hit explosion (+0x140 + 4 x kind;
// 8 / 9: +0x160; kind 4: +0x120, the impact explosion of kind 4, not +0x150) placed there, triggered and released.
void CKHkS08Malefor::SpawnElementHitFx(CKS08Damage* damage) {
    CSGHotSpot* hotSpot = MaleforHotSpot(this, 6);
    CVector3 position;
    if (hotSpot == nullptr) {
        const RwV3d& at = static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame->ltm.pos;
        position = {at.x, at.y, at.z};
    } else {
        hotSpot->GetWorldPosition(&position);  // 0x000ce790
    }
    if (damage->IsKindOfClass(0x99cc) == 0) return;
    const uint32_t kind = damage->m_unk20;
    if (kind > 9) return;
    IKSerializable* data;
    if (kind == 4) {
        data = m_apUnk110[4];
    } else {
        data = m_apUnk140[kind >= 8 ? 8 : kind];
    }
    TriggerExplosionAt(this, data, &position);
}

// 0x004e6fd8 CKHkS08Malefor_ApplyPendingDamage_maybe: each dragon's continuous damage of this frame (+0xc4 / +0xc8): its
// amount (per second when +0x0c; an element damage of kind 7 with no amount takes Cynder's element level of the
// damage's ability: 3: 60, 2: 30, below 2: 20 per second) accumulated (weak and not of element kind 8 / 9: the weak
// factors). Its hit count timer starts at the interval (+0xe0) at its first frame, then grows; once at the interval
// (fcmpu + cror: a NaN waits): not weak or kind 8 / 9: a combo hit (OnNewHitW_2 at the null vector), weak otherwise the
// fury (+0x170); the timer restarts. Its hit effect timer (+0x138 / +0x13c, started at +0x134) at +0x134: not weak the
// element's hit explosion, weak +0x184 (kinds 8 / 9: +0x188); restarted. The damage is forgotten. A dragon without one
// stops its timer.
void CKHkS08Malefor::ApplyPendingDamage(IKTime* clock) {
    for (uint32_t slot = 0; slot < 2; ++slot) {
        CKS08Damage* damage = m_apUnkC4[slot];
        if (damage == nullptr) {
            if (m_abUnkD4[slot] != 0) m_abUnkD4[slot] = 0;
            m_afUnkD8[slot] = kZero;
            continue;
        }
        const uint32_t kind = damage->m_unk20;
        const uint8_t kind89 = (kind == 8 || kind == 9) ? 1 : 0;
        const float dt = clock->m_afDeltaTime[IKTime::SCALABLE_GAME_TIME];
        float amount = FrameAmount(damage, dt);
        if (kind == 7 && amount == kZero) {
            IKGrpHero* group = static_cast<IKGrpHero*>(g_pEngine->m_gameManager->m_unk04[1]);
            CKHkS08Hero* cynder = static_cast<CKHkS08Hero*>(group->m_apHeros[1]);  // GetHeroByDragonIndex 0x002ca080
            const uint8_t ability = static_cast<uint8_t>(static_cast<const CKS08ElementDamage*>(damage)->m_unk38);
            const uint8_t level = cynder->GetAbilityElementLevel(ability);  // 0x0032a8d0
            if (level == 2) {
                amount = dt * kLevel2Rate;
            } else if (level < 2) {
                amount = dt * kLevel1Rate;
            } else if (level == 3) {
                amount = dt * kLevel3Rate;
            }
        }
        if (m_unk168 == 0 || kind89 != 0) {
            AccumulateDamage(amount, damage, slot);  // 0x004e1a80
        } else {
            AccumulateWeakDamage(amount, damage, slot);  // 0x004e17d8
        }
        float timer;
        if (m_abUnkD4[slot] == 0) {
            m_abUnkD4[slot] = 1;
            m_afUnk134[1 + slot] = m_afUnk134[0];
            m_afUnkD8[slot] = m_unkE0;
            timer = m_unkE0;
        } else {
            timer = m_afUnkD8[slot] + dt;
            m_afUnkD8[slot] = timer;
            m_afUnk134[1 + slot] = m_afUnk134[1 + slot] + dt;
        }
        if (timer >= m_unkE0) {
            CKS08GameManager* manager = MaleforGameManager();
            if (m_unk168 == 0 || kind89 != 0) {
                const CVector3 point = kNullVector;
                OnNewHitW(manager, static_cast<uint8_t>(slot), &point);  // OnNewHitW_2 0x004fe5f8
                if (m_unk168 != 0 && kind89 == 0) manager->AddDragonFury(static_cast<int32_t>(slot), m_unk170);
            } else {
                manager->AddDragonFury(static_cast<int32_t>(slot), m_unk170);  // 0x004fd528
            }
            m_afUnkD8[slot] = kZero;
        }
        if (m_afUnk134[1 + slot] >= m_afUnk134[0]) {
            if (m_unk168 == 0) {
                SpawnElementHitFx(m_apUnkC4[slot]);
            } else if (kind89 == 0) {
                TriggerExplosion(m_unk184);
            } else {
                TriggerExplosion(m_unk188);
            }
            m_afUnk134[1 + slot] = 0.0f;
        }
        m_apUnkC4[slot] = nullptr;
    }
}

// 0x004e75d8 CKHkS08Malefor_Update: CKHkGolem's; while updated (+0x45): at or below the health +0xfc the particle nodes
// emit, their particles per point between the full-health and no-health counts by health / +0xfc (the ratio r, then
// fctidz(fmadds(1 - r, none, r x full))), from the +0xf0 hot spots (+0xe4) and the two +0xf4 ones (+0xe8); then the
// pending damage. With the node +0x178: its uniform scale from the health percentage (at or above +0x1c0: +0x1c8; at or
// below +0x1c4: +0x1cc; between them +0x1cc - (+0x1c0 - p) / (+0x1c0 - +0x1c4) x (+0x1cc - +0x1c8)), the weak volume's
// radius the scale x +0x1d0 when above 0 (else 0.001).
void CKHkS08Malefor::Update(IKTime* clock) {
    CKHkGolem::Update(clock);  // 0x004c4838
    if (m_unk45 == 0) return;
    if (m_unk8C <= static_cast<int32_t>(m_unkFC[0])) {
        const float ratio = SignedToFloat(m_unk8C) / SignedToFloat(static_cast<int32_t>(m_unkFC[0]));
        const float rest = kOne - ratio;
        if (m_unkE4 != nullptr) {
            SetParticlesPerPoint(m_unkE4, ppc::fctidz(ppc::fmadds(rest, UnsignedToFloat(m_unkFC[2]),
                                                                  ratio * UnsignedToFloat(m_unkFC[1]))));
            for (uint32_t i = 0; i < m_unkEC; ++i) {
                CVector3 position;
                static_cast<CSGHotSpot*>(m_apUnkF0[i])->GetWorldPosition(&position);  // 0x000ce790
                AppendEmitPoint(m_unkE4, position);
            }
        }
        if (m_unkE8 != nullptr) {
            SetParticlesPerPoint(m_unkE8, ppc::fctidz(ppc::fmadds(rest, UnsignedToFloat(m_unkFC[4]),
                                                                  ratio * UnsignedToFloat(m_unkFC[3]))));
            CVector3 position;
            static_cast<CSGHotSpot*>(m_apUnkF4[0])->GetWorldPosition(&position);
            AppendEmitPoint(m_unkE8, position);
            static_cast<CSGHotSpot*>(m_apUnkF4[1])->GetWorldPosition(&position);
            AppendEmitPoint(m_unkE8, position);
        }
    }
    ApplyPendingDamage(clock);  // 0x004e6fd8
    if (m_pUnk178 == nullptr) return;
    const float percent = GetHealthPercent();  // 0x004bed00
    const float high = m_afUnk194[11];
    float t;
    if (percent >= high) {
        t = kOne;
    } else {
        const float low = m_afUnk194[12];
        if (percent <= low) {
            t = kZero;
        } else {
            t = (high - percent) / (high - low);
        }
    }
    const float scale = m_afUnk194[14] - t * (m_afUnk194[14] - m_afUnk194[13]);
    m_pUnk178->SetUniformScale(scale);  // 0x000d0970
    const float radius = scale * m_afUnk194[15];
    m_unk164->m_fRadius = radius > kZero ? radius : kMinRadius;  // ble: a NaN takes 0.001
}
