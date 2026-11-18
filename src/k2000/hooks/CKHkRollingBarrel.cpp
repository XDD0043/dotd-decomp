// Reconstructed original translation unit: 0x43ef98-0x441860 (GAME_TOC1, main_toc1), 37 functions, 31 live.
// Primary class: CKHkRollingBarrel  key 0x4002  category Hook  size 0xa0  vtable 0xb264f8
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x43ef98  RegisterCKHkRollingBarrelClass
//   [ ] 0x43f010  _GLOBAL__I_43f010
//   [ ] 0x43f020  CKHkRollingBarrel_UnregisterBarrelShadow_maybe  [dead]
//   [ ] 0x43f090  CKHkRollingBarrel_RegisterBarrelShadow_maybe  [dead]
//   [ ] 0x43f190  CKHkRollingBarrel_UpdateBarrelScaleCurve_maybe  [dead]
//   [x] 0x43f298  CKHkRollingBarrel_TriggerBreakExplosion_maybe
//   [x] 0x43f5a0  CKHkRollingBarrel_GetInfo
//   [x] 0x43f5f0  CKHkRollingBarrel_OnActivate  (OnActivate, VfA0)
//   [x] 0x43f628  CKHkRollingBarrel_Resume  (the actor base's KStub_Nop_3f6e60: inherited)
//   [x] 0x43f650  CKHkRollingBarrel_Pause  (the actor base's KStub_Nop_3f6e58: inherited)
//   [x] 0x43f678  CKHkRollingBarrel_Start
//   [ ] 0x43f6c0  CKHkRollingBarrel_Save
//   [x] 0x43f6e8  CKHkRollingBarrel_RecursiveRegistration
//   [x] 0x43f768  CKHkRollingBarrel_Destroy  (the actor base's 0x3f6e08: inherited)
//   [x] 0x43f790  CKHkRollingBarrel_BaseDestructor  (the header's destructor)
//   [ ] 0x43f800  CKHkRollingBarrel_Construct  [dead]
//   [ ] 0x43f860  CKHkRollingBarrel_Construct_2  [dead]
//   [x] 0x43f8c0  CKHkRollingBarrel_DeleteArray  (DOTD_DECLARE_FACTORIES(CKHkRollingBarrel))
//   [x] 0x43f968  CKHkRollingBarrel_SetGameState
//   [x] 0x43fa40  CKHkRollingBarrel_SetDefaultState
//   [x] 0x43faa0  CKHkRollingBarrel_DeletingDestructor  (the header's destructor)
//   [x] 0x43fb18  CKHkRollingBarrel_Destructor  (the header's destructor)
//   [x] 0x43fb88  CKHkRollingBarrel_CreateArray  (DOTD_DECLARE_FACTORIES)
//   [x] 0x43fc70  CKHkRollingBarrel_Create  (DOTD_DECLARE_FACTORIES: the header's constructor)
//   [x] 0x43fce0  CKHkRollingBarrel_DeactivateAllBarrels_maybe
//   [x] 0x43fe30  CKHkRollingBarrel_OnDeactivate  (OnDeactivate, VfA4)
//   [x] 0x43fe68  CKHkRollingBarrel_Restart
//   [x] 0x43fea8  CKHkRollingBarrel_Stop
//   [x] 0x43fee0  CKHkRollingBarrel_DespawnBarrel_maybe
//   [x] 0x4400b8  CKHkRollingBarrel_DespawnBarrelsOnContact_maybe
//   [x] 0x440270  CKHkRollingBarrel_SpawnBarrel_maybe
//   [ ] 0x440560  CKHkRollingBarrel_UpdateSpawnTimeline_maybe  [dead]
//   [x] 0x4406b0  CKHkRollingBarrel_MessageProc
//   [x] 0x4408a0  CKHkRollingBarrel_UpdateBarrelGroundAndShadow_maybe
//   [x] 0x440b70  CKHkRollingBarrel_UpdateBarrels_maybe
//   [x] 0x441218  CKHkRollingBarrel_Update
//   [x] 0x441438  CKHkRollingBarrel_Load
//
//   [ ] 0x9c3448  CKHkRollingBarrel_IsKindOfClass  [inline]
//   [ ] 0x9c34a0  CKHkRollingBarrel_GetClassType  [inline]
//   [ ] 0x9c34a8  CKHkRollingBarrel_GetClassID  [inline]
//   [ ] 0x9c34b0  CKHkRollingBarrel_vfF0  [inline]
//   [ ] 0x9c34c0  CKHkRollingBarrel_vfD8  [inline]
//
// C2.8 port-all P18: left (no game file holds class 0x4002 CKHkRollingBarrel, nor its pool 0x118c / component 0xd86).
// C2.8 port-final F02: ported from the code anyway (CKHkRollingBarrel.h); nothing replays it.
#include "k2000/hooks/CKHkRollingBarrel.h"

#include <cmath>

#include "Renderware/rwcore/RwCamera.h"
#include "Renderware/rwcore/RwMatrix.h"
#include "crt/ppc_ops.h"
#include "k2000/core/IKInfo.h"
#include "k2000/dictionaries/CKSoundDictionaryID.h"
#include "k2000/fx/IKFx.h"
#include "k2000/hooks/GroundContact.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/logic/IKFxData.h"
#include "k2000/logic/ai/CKFlaggedPath.h"
#include "k2000/logic/fx/CKExplosionNodeFx.h"
#include "k2000/logic/math/IKPath.h"
#include "k2000/logic/sound/CKSound.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/CSGLeaf.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/scenegraph/IKBoundingVolume.h"
#include "k2000/services/CKSrvCollision.h"
#include "k2000/services/CKSrvFx.h"
#include "k2000/services/CKSrvShadow.h"
#include "k2000/services/ICollisionMesh.h"
#include "k2000/system/IKTime.h"

namespace {
using Barrel = CKRollingBarrelPool::Barrel;

CKSrvCollision* Collision() { return static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision); }  // engine +0x58
CKSrvShadow* Shadow() { return static_cast<CKSrvShadow*>(g_pEngine->m_srvShadow); }              // engine +0x88
CSGMovable* MovableOf(const Barrel* b) { return static_cast<CSGMovable*>(b->m_pUnk00); }
CSGLeaf* LeafOf(const Barrel* b) { return static_cast<CSGLeaf*>(b->m_pNode); }
IKBoundingVolume* VolumeOf(const Barrel* b) { return static_cast<IKBoundingVolume*>(b->m_pUnk38); }
CKSound* SoundOf(const Barrel* b, uint32_t index) {
    return static_cast<CKSoundDictionaryID*>(b->m_pUnk8c)->GetSound(index);  // 0x00112bc0
}
IKPath* PathOf(const CKFlaggedPath* path) { return static_cast<IKPath*>(path->m_pPath); }

// The shared axes (0x00c50d34 X, 0x00c50d40 Y, 0x00c50d4c Z: zero in the EBOOT's BSS, filled by static initialisers).
const CVector3 kAxisX = {1.0f, 0.0f, 0.0f};  // TOC1 +0x50cc
const CVector3 kAxisY = {0.0f, 1.0f, 0.0f};  // TOC1 +0x50b0
const CVector3 kAxisZ = {0.0f, 0.0f, 1.0f};  // TOC1 +0x50d8
const float kZero = 0.0f;                   // TOC1 +0x50bc
const float kOne = 1.0f;                    // TOC1 +0x50b4
const float kTwo = 2.0f;                    // TOC1 +0x50b8
const float kStep = 0.01f;                  // TOC1 +0x50e0 (0x3c23d70a)
const float kNoValue = 180.0f;              // TOC1 +0x50e4: a segment value of 180 stops the speed-up
const double kSteep = 0.99;                 // TOC1 +0x50e8 (a double: 0x3fefae147ae147ae)
const float kRadToDeg = 57.29578f;          // TOC1 +0x50f0 (0x42652ee1)
const float kRandMax = 65535.0f;            // TOC1 +0x50d0
const float kFullTurn = 360.0f;             // TOC1 +0x50d4
const float kHalfPi = 1.5707963705062866f;  // TOC1 +0x50dc (0x3fc90fdb, copied as a word)
}  // namespace

CKHkRollingBarrel::CKHkRollingBarrel() {
    m_vSpawnTimes.m_pBlock = nullptr;
    m_vSpawnTimes.m_ui32NbElt = 1;
    m_vSpawnTimes.m_ui32NbUsedElt = 0;
}

CKHkRollingBarrel::~CKHkRollingBarrel() {
    if (m_vSpawnTimes.m_pBlock != nullptr) Mem_FreeAligned16(m_vSpawnTimes.m_pBlock);  // 0x00052fb8
    m_vSpawnTimes.m_ui32NbUsedElt = 0;
    m_vSpawnTimes.m_pBlock = nullptr;
}

// 0x0043f298 CKHkRollingBarrel_TriggerBreakExplosion_maybe
void CKHkRollingBarrel::TriggerBreakExplosion(const CVector3* point) {
    IKFx* fx = static_cast<CKSrvFx*>(g_pEngine->m_srvFx)->AcquireFx(static_cast<IKFxData*>(m_pPool->m_pUnk1c), this);
    if (fx == nullptr) return;
    CKExplosionNodeFx* explosion = static_cast<CKExplosionNodeFx*>(fx);
    CVector3 pos = *point;
    pos.y = pos.y + m_pPool->m_unk48;
    explosion->SetTranslation(&pos, this);   // 0x001b66e8
    explosion->SetDamageOwner(this, this);   // 0x001b6340
    explosion->SetDamageCategory(1, this);   // 0x001b6318
    explosion->SetDamageFlags(0x244, this);  // 0x001b62f0
    explosion->Trigger(this, nullptr);       // 0x001b82a8 (r5 / r6 0)
    explosion->ReleaseReservation(this);     // vt+0x54
}

// 0x0043f5a0 CKHkRollingBarrel_GetInfo
int32_t CKHkRollingBarrel::GetInfo(IKInfo* info, int32_t request) {
    const int32_t base = CKHkActorBase::GetInfo(info, request);  // KStub_Return1 0x3f7140
    if (base == 2) return 2;
    return base == 0 ? 0 : 1;
}

// 0x0043f5f0 CKHkRollingBarrel_OnActivate
void CKHkRollingBarrel::VfA0() {
    CKHkActorBase::VfA0();  // 0x003f7338
    m_fTimer = 0.0f;        // stw 0
}

// 0x0043f678 CKHkRollingBarrel_Start
void CKHkRollingBarrel::Start() {
    CKHkActorBase::Start();  // 0x003f6e48 (empty)
    m_fTickRest = 0.0f;      // stw 0
    m_ui8NbBarrel = 0;
    m_fTimer = 0.0f;
}

// 0x0043f6e8 CKHkRollingBarrel_RecursiveRegistration
void CKHkRollingBarrel::RecursiveRegistration(int32_t type) {
    CKHkActorBase::RecursiveRegistration(type);                      // 0x003f6ee8
    if (m_pUnk64 != nullptr) m_pUnk64->RecursiveRegistration(type);  // 0x00019c98
    // Then the end starter's KStub_Return1_2361b0 (CTriggerStarter: nothing).
}

// 0x0043f968 CKHkRollingBarrel_SetGameState: the actor base's preset; for any other answer, game state info 6 sets
// bit 3 (running) from the state id.
int32_t CKHkRollingBarrel::SetGameState(const SApplyGameState* state) {
    if (CKHkActorBase::SetGameState(state) == 1) return 1;  // 0x003f72a8
    if (state->m_ui32InfoId != 6) return 0;
    if (state->m_ui32GameStateId != 0) {
        m_bitArray = (m_bitArray & 0xfffffff7u) | 8u;
    } else {
        m_bitArray &= 0xfffffff7u;
    }
    return 1;
}

// 0x0043fa40 CKHkRollingBarrel_SetDefaultState: bit 3 (running) from bit 4 (running at start).
void CKHkRollingBarrel::SetDefaultState(int32_t flag) {
    CKHkActorBase::SetDefaultState(flag);  // 0x003f72a0 (empty)
    m_bitArray = (m_bitArray & 0xfffffff7u) | (((m_bitArray >> 4) & 1u) << 3);
}

// 0x0043fce0 CKHkRollingBarrel_DeactivateAllBarrels_maybe
void CKHkRollingBarrel::DeactivateAllBarrels() {
    for (uint32_t i = m_ui8NbBarrel; i != 0;) {
        --i;
        CSGLeaf* leaf = LeafOf(m_apBarrels[i]);
        leaf->m_sgProperties = (leaf->m_sgProperties & 0xfffffffbu) | 4u;  // hidden
        Collision()->DisableVolume(VolumeOf(m_apBarrels[i]));             // 0x001920e8
        IKSerializable* shadowCpnt = m_pPool->m_pUnk50;
        if (shadowCpnt != nullptr && m_apBarrels[i]->m_ShadowGround.m_bUsed_maybe != 0) {
            Shadow()->UnregisterCaster(&m_apBarrels[i]->m_ShadowGround, shadowCpnt);  // 0x001fd6f0
        }
        Sound_Stop(SoundOf(m_apBarrels[i], 1), 0);  // 0x001111b0
        m_pPool->Release(m_apBarrels[i]);           // 0x00442040
    }
    m_ui8NbBarrel = 0;
}

// 0x0043fe30 CKHkRollingBarrel_OnDeactivate
void CKHkRollingBarrel::VfA4() {
    CKHkActorBase::VfA4();  // 0x003f7370
    DeactivateAllBarrels();
}

// 0x0043fe68 CKHkRollingBarrel_Restart
void CKHkRollingBarrel::Restart() {
    DeactivateAllBarrels();
    m_fTimer = 0.0f;  // stw 0
    m_ui8NbBarrel = 0;
}

// 0x0043fea8 CKHkRollingBarrel_Stop
void CKHkRollingBarrel::Stop() {
    CKHkActorBase::Stop();  // 0x003f6e50
    DeactivateAllBarrels();
}

// 0x0043fee0 CKHkRollingBarrel_DespawnBarrel_maybe. The search runs down from the last slot; a match takes the last
// rolling barrel into its slot and the search goes on below it (CTR from the matched index).
void CKHkRollingBarrel::DespawnBarrel(Barrel* barrel) {
    uint32_t i = m_ui8NbBarrel;
    while (i != 0) {
        --i;
        if (m_apBarrels[i] != barrel) continue;
        const uint32_t count = static_cast<uint8_t>(m_ui8NbBarrel - 1);
        m_ui8NbBarrel = static_cast<uint8_t>(count);
        if (i < count) m_apBarrels[i] = m_apBarrels[count];  // cmplw / ble
    }
    CSGLeaf* leaf = LeafOf(barrel);
    leaf->m_sgProperties = (leaf->m_sgProperties & 0xfffffffbu) | 4u;  // hidden
    Collision()->DisableVolume(VolumeOf(barrel));                     // 0x001920e8
    IKSerializable* shadowCpnt = m_pPool->m_pUnk50;
    if (shadowCpnt != nullptr && barrel->m_ShadowGround.m_bUsed_maybe != 0) {
        Shadow()->UnregisterCaster(&barrel->m_ShadowGround, shadowCpnt);  // 0x001fd6f0
    }
    if (m_pPool->m_unk6c[2] != 0) {  // +0x6e: the barrels break
        CVector3 point;
        PathOf(m_pPath)->GetPointAtDistance(barrel->m_unk08, &point, nullptr);  // vt+0x54
        const CVector3 at = point;
        TriggerBreakExplosion(&at);
    }
    Sound_Stop(SoundOf(barrel, 1), 0);  // 0x001111b0
    m_pPool->Release(barrel);           // 0x00442040
}

// 0x004400b8 CKHkRollingBarrel_DespawnBarrelsOnContact_maybe. The other volume of each contact is asked again for the
// answer (vt+0x00 twice when the barrel's volume is not the first).
void CKHkRollingBarrel::DespawnBarrelsOnContact() {
    if (m_pPool->m_unk6c[2] == 0) return;
    for (uint32_t i = m_ui8NbBarrel; i != 0;) {
        --i;
        ICollision* c = static_cast<ICollision*>(VolumeOf(m_apBarrels[i])->m_CollisionResList);
        if (c == nullptr) continue;
        bool hit = false;
        for (; c != nullptr; c = c->m_pNext) {
            if (c->HasContactSet() == 0) continue;  // vt+0x08
            IKSerializable* other;
            if (m_apBarrels[i]->m_pUnk38 == c->GetBoundingVolume1()) {  // vt+0x00
                other = c->GetBoundingVolume2();                          // vt+0x04
            } else {
                other = c->GetBoundingVolume1();
            }
            if ((static_cast<IKBoundingVolume*>(other)->m_ui16PropertiesFlags & 1u) == 0) continue;
            hit = true;
        }
        if (!hit || m_pPool->m_unk6c[2] == 0) continue;
        DespawnBarrel(m_apBarrels[i]);
    }
}

// 0x00440270 CKHkRollingBarrel_SpawnBarrel_maybe
void CKHkRollingBarrel::SpawnBarrel() {
    Barrel* b = m_pPool->TakeNext();  // 0x00442000
    if (b == nullptr) return;
    CSGLeaf* leaf = LeafOf(b);
    leaf->m_sgProperties &= 0xfffffffbu;     // shown
    Collision()->EnableVolume(VolumeOf(b));  // 0x00192090
    VolumeOf(b)->m_pOwner = this;
    const uint32_t r = static_cast<uint32_t>(Rand_Int()) & 0xffffu;                  // 0x00011500
    leaf->RotateInPlace(&kAxisX.x, (static_cast<float>(r) / kRandMax) * kFullTurn);  // 0x000d11b0
    b->m_vDir = kAxisZ;
    b->m_vTargetDir = kAxisZ;
    b->m_fTurnRate = kHalfPi;
    b->m_unk08 = 0.0f;  // stw 0
    b->m_unk0c = kAxisY;
    b->m_unk18 = m_fMinSpeed;
    b->m_unk3c = 0.0f;  // stw 0
    b->m_GrdContDatasInOut.m_pGround = nullptr;
    b->m_GrdContDatasInOut.m_eContactStatus = 3;
    b->m_GrdContDatasInOut.m_i32FaceIndex = -1;
    b->m_GrdContDatasInOut.m_ui8SectorNumber = 0;
    b->m_ShadowGround.m_bUsed_maybe = 0;
    IKSerializable* shadowCpnt = m_pPool->m_pUnk50;
    if (shadowCpnt != nullptr) {
        Shadow()->RegisterCaster(shadowCpnt, b->m_pUnk00, &b->m_ShadowGround, 0, nullptr, 0);  // 0x001fb6f8
        const RwV3d& pos = MovableOf(b)->m_pRwFrame->modelling.pos;  // frame +0x40
        b->m_ShadowGround.m_v3Position = {pos.x, pos.y, pos.z};
        b->m_ShadowGround.m_v3Normal = kAxisY;
        b->m_ShadowGround.m_bUsed_maybe = 1;
        b->m_ShadowGround.m_fUnk18 = 0.0f;  // stw 0
    }
    m_apBarrels[m_ui8NbBarrel] = b;  // BUG(original): no bound on the 16 slots
    m_ui8NbBarrel = static_cast<uint8_t>(m_ui8NbBarrel + 1);
    if (m_pPool->m_unk6c[6] == 0) return;  // +0x72: the rolling loop sound
    SoundOf(b, 1)->SetAttachObject(b->m_pNode);  // 0x00111350
    SoundOf(b, 1)->SetLoop(1);                   // 0x00110fd0
    SoundOf(b, 1)->Play(0.0f);                   // 0x00111230 (a stored 0 word)
}

// 0x004406b0 CKHkRollingBarrel_MessageProc. 0x996 runs (timer 0), 0x997 stops, 0x998 spawns a barrel, 0x999 takes them
// all back, 0xc32 answers the hero's hazard query from the pool (+0x7c..+0x84, +0x98) at the hitting volume.
int32_t CKHkRollingBarrel::MessageProc(uint16_t message, void* data) {
    const int32_t base = CKHkActorBase::MessageProc(message, data);  // 0x003f7148
    int32_t own = 1;
    switch (message) {
    case 0x996:
        own = 0;
        m_bitArray = (m_bitArray & 0xfffffff7u) | 8u;
        m_fTimer = 0.0f;  // stw 0
        break;
    case 0x997:
        own = 0;
        m_bitArray &= 0xfffffff7u;
        break;
    case 0x998:
        SpawnBarrel();
        own = 0;
        break;
    case 0x999:
        DeactivateAllBarrels();
        own = 0;
        break;
    case 0xc32: {
        // The hero's hazard query (CKHkS08Hero_6.cpp's HazardHitQuery: +0x04 the volume, +0x08..+0x10 three words,
        // +0x14 the point, +0x24 the damage byte).
        struct Query {
            IKSerializable* m_hero;
            IKBoundingVolume* m_volume;
            float m_dirX;
            float m_dirZ;
            float m_unk10;
            CVector3 m_point;
            int32_t m_kind;
            uint8_t m_damage;
        };
        Query* query = static_cast<Query*>(data);
        own = 0;
        query->m_dirX = m_pPool->m_unk7c;
        query->m_dirZ = m_pPool->m_unk80;
        query->m_unk10 = m_pPool->m_unk84;
        query->m_damage = m_pPool->m_unk98;
        if (query->m_volume != nullptr) {
            const RwMatrix* ltm = FrameLtm(query->m_volume->m_pRwFrame);  // volume +0x04, +0x80
            query->m_point = {ltm->pos.x, ltm->pos.y, ltm->pos.z};
        }
        break;
    }
    default:
        break;
    }
    if (base == 3 || own == 3) return 3;
    if (base == 2 || own == 2) return 2;
    return base == 0 ? 0 : own;
}

// 0x004408a0 CKHkRollingBarrel_UpdateBarrelGroundAndShadow_maybe
void CKHkRollingBarrel::UpdateBarrelGroundAndShadow(Barrel* b) {
    CGroundContactDatasInOut* contact = &b->m_GrdContDatasInOut;
    const RwV3d& pos = MovableOf(b)->m_pRwFrame->modelling.pos;  // frame +0x40
    // The pool's +0x54..+0x63 are a CGroundContactDatasIn (PostLoad: +0x48, 2 x +0x48, masks 1, 8).
    Collision()->GroundProbePoints(reinterpret_cast<const CGroundContactDatasIn*>(&m_pPool->m_unk54), contact, &pos.x,
                                   1);  // 0x00196540
    // No ground, or a ground the game manager marks (vt+0x138, its low byte): the shadow is dropped.
    bool drop = contact->m_pGround == nullptr;
    if (!drop && static_cast<uint8_t>(g_pEngine->m_gameManager->GetGroundSurfaceBit(contact->m_pGround)) != 0) {
        drop = true;
    }
    if (drop) {
        IKSerializable* shadowCpnt = m_pPool->m_pUnk50;
        if (shadowCpnt != nullptr && b->m_ShadowGround.m_bUsed_maybe != 0) {
            Shadow()->UnregisterCaster(&b->m_ShadowGround, shadowCpnt);  // 0x001fd6f0
        }
        return;
    }
    IKSerializable* shadowCpnt = m_pPool->m_pUnk50;
    if (shadowCpnt != nullptr && b->m_ShadowGround.m_bUsed_maybe == 0) {
        Shadow()->RegisterCaster(shadowCpnt, b->m_pUnk00, &b->m_ShadowGround, 0, nullptr, 0);  // 0x001fb6f8
        const RwV3d& at = MovableOf(b)->m_pRwFrame->modelling.pos;
        b->m_ShadowGround.m_v3Position = {at.x, at.y, at.z};
        b->m_ShadowGround.m_v3Normal = kAxisY;
        b->m_ShadowGround.m_bUsed_maybe = 1;
        b->m_ShadowGround.m_fUnk18 = 0.0f;  // stw 0
    }
    if (contact->m_eContactStatus == 3) return;
    GroundContact_GetWorldPoint(contact, &b->m_ShadowGround.m_v3Position);  // 0x001a70e0
    GroundContact_GetWorldNormal(contact, &b->m_ShadowGround.m_v3Normal);   // 0x001a71d8
    b->m_ShadowGround.m_fUnk18 = contact->m_fdH;
    if (((static_cast<const ICollisionMesh*>(contact->m_pGround)->m_ba16EngineFlags >> 6) & 1u) != 0) {
        b->m_ShadowGround.m_ui8Flags = static_cast<uint8_t>(b->m_ShadowGround.m_ui8Flags | 0x10u);
    } else if ((b->m_ShadowGround.m_ui8Flags & 0x10u) != 0) {
        b->m_ShadowGround.m_ui8Flags = static_cast<uint8_t>(b->m_ShadowGround.m_ui8Flags ^ 0x10u);
    }
}

// 0x00440b70 CKHkRollingBarrel_UpdateBarrels_maybe. With bit 5 the frame's time joins the steps' rest (+0x94) and the
// whole sum is the barrels' time (f27), stepped by 0.01 while it exceeds the rest.
void CKHkRollingBarrel::UpdateBarrels(IKTime* clock) {
    float dt = clock->m_afDeltaTime[0];  // +0x1c
    if ((m_bitArray & 0x20u) != 0) {
        dt = dt + m_fTickRest;
        m_fTickRest = dt;
        if (dt > kStep) {  // ble: a NaN keeps it
            float rest = dt;
            do {
                rest = rest - kStep;
            } while (rest > kStep);
            m_fTickRest = rest;
        }
    }
    for (uint32_t i = m_ui8NbBarrel; i != 0;) {
        --i;
        Barrel* b = m_apBarrels[i];
        m_pPath->m_fCursorPos = b->m_unk08;
        if ((m_bitArray & 0x20u) == 0) {
            if (b->m_unk0c.y <= kZero) {  // ble: going down (or level) speeds up
                const float speed = ppc::fmadds(dt, m_fAccel, b->m_unk18);
                b->m_unk18 = speed;
                if (speed > m_fMaxSpeed) b->m_unk18 = m_fMaxSpeed;  // ble skips
            } else {  // going up (or a NaN) slows down
                const float speed = b->m_unk18 - dt * m_fBrake;
                b->m_unk18 = speed;
                if (!(speed >= m_fMinSpeed)) b->m_unk18 = m_fMinSpeed;  // bge skips
            }
        } else {
            float left = dt;
            while (!(m_fTickRest >= left)) {  // bge ends the steps
                const float value = m_pPath->GetSegmentValueAt(b->m_unk08);  // 0x000c4350
                if (value == kNoValue) {
                    b->m_unk18 = m_fMinSpeed;
                } else {
                    const float speed = ppc::fmadds((value * kStep) * m_fAccel, kStep, b->m_unk18);
                    b->m_unk18 = speed;
                    if (speed > m_fMaxSpeed) {
                        b->m_unk18 = m_fMaxSpeed;
                    } else if (!(speed >= m_fMinSpeed)) {
                        b->m_unk18 = m_fMinSpeed;
                    }
                }
                const float distance = ppc::fmadds(b->m_unk18, kStep, b->m_unk08);
                b->m_unk08 = distance;
                if (distance > PathOf(m_pPath)->GetLength()) {  // vt+0x5c; bgt
                    QueueTriggerSignals(&m_tsEndStarter);         // 0x00236338
                    DespawnBarrel(b);
                    break;
                }
                left = left - kStep;
            }
        }
        CVector3 point;
        CVector3 dir;
        m_pPath->SetDistanceAndGetPosition(b->m_unk08, &point, &dir, nullptr);  // 0x000c4eb8
        CSGMovable* movable = MovableOf(b);
        RwFrame* frame = movable->m_pRwFrame;
        frame->modelling.pos.z = point.z;
        frame->modelling.pos.x = point.x;
        frame->modelling.pos.y = point.y;
        frame->modelling.flags &= 0xfffdffffu;
        RwFrame_MarkDirty(movable->m_pRwFrame);  // 0x00010698
        if (m_pPool->m_unk6c[3] != 0) {           // +0x6f: the trail
            m_pPool->EmitTrailPoints(reinterpret_cast<const CMatrix34*>(FrameLtm(LeafOf(b)->m_pRwFrame)));  // 0x00442810
        }
        // Landing: the path turns upwards where it went down (or level) last frame.
        if (dir.y > kZero && b->m_unk0c.y <= kZero) {  // ble; cror lt|eq
            b->m_unk3c = dt;
            const CVector3 impact = point;
            m_pPool->AddImpactPoint(&impact, 1);  // 0x00442700
            const float low = m_pPool->m_unk64;
            const uint32_t r = static_cast<uint32_t>(Rand_Int()) & 0xffffu;  // 0x00011500
            const float speed = ppc::fmadds(static_cast<float>(r) / kRandMax, m_pPool->m_unk68 - m_pPool->m_unk64, low);
            SoundOf(b, 0)->SetAttachObject(b->m_pNode);  // 0x00111350
            SoundOf(b, 0)->SetSpeed(speed);              // 0x00110e98
            SoundOf(b, 0)->Play(kZero);                  // 0x00111230
        }
        b->m_unk0c = dir;
        // The heading to turn to: the path's direction made horizontal, or the movable's at axis made horizontal when
        // the path is (almost) vertical (|y| >= 0.99, a double; a NaN takes the path's).
        CVector3 target;
        if (static_cast<double>(std::fabs(b->m_unk0c.y)) >= kSteep) {
            const RwV3d& axis = movable->m_pRwFrame->modelling.at;  // frame +0x30
            float x = axis.x;
            float z = axis.z;
            float y = kZero;
            const float length = std::sqrt(ppc::fmadds(z, z, ppc::fmadds(x, x, kZero)));  // Math_Sqrtf 0x10690
            if (length != kZero) {
                const float inverse = kOne / length;
                z = z * inverse;
                x = x * inverse;
                y = inverse * kZero;
            }
            target = {x, y, z};
        } else {
            float x = dir.x;
            float z = dir.z;
            float y = kZero;
            const float length = std::sqrt(ppc::fmadds(z, z, ppc::fmadds(x, x, kZero)));  // Math_Sqrtf 0x10690
            if (length != kZero) {
                const float inverse = kOne / length;
                z = z * inverse;
                x = x * inverse;
                y = y * inverse;
            }
            target = {x, y, z};
        }
        b->m_vTargetDir.z = target.z;
        b->m_vTargetDir.x = target.x;
        b->m_vTargetDir.y = target.y;
        // The heading turns towards it by the turn rate.
        CVector3& cur = b->m_vDir;
        const CVector3& to = b->m_vTargetDir;
        if (cur.x != to.x || cur.y != to.y || cur.z != to.z) {
            const float dx = to.x - cur.x;
            const float step = dt * b->m_fTurnRate;
            const float dy = to.y - cur.y;
            const float dz = to.z - cur.z;
            const float distance2 = ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy));
            if (step * step <= distance2) {                       // ble
                const float scale = step * rwInvSqrt(distance2);  // 0x000114d8 Math_InvSqrtf
                cur.z = ppc::fmadds(dz, scale, cur.z);
                cur.x = ppc::fmadds(dx, scale, cur.x);
                cur.y = ppc::fmadds(dy, scale, cur.y);
            } else {
                cur.z = to.z;
                cur.x = to.x;
                cur.y = to.y;
            }
        }
        CVector3 at = cur;
        const float length = std::sqrt(ppc::fmadds(at.z, at.z, ppc::fmadds(at.x, at.x, at.y * at.y)));  // 0x10690
        if (length != kZero) {
            const float inverse = kOne / length;
            at.z = at.z * inverse;
            at.x = at.x * inverse;
            at.y = at.y * inverse;
        }
        movable->SetOrientationFromAtUp(&at, &kAxisY);  // 0x000d0918
        // The roll: the distance covered over the barrel's radius (pool +0x48), in degrees.
        LeafOf(b)->RotateInPlace(&kAxisX.x, (dt * (b->m_unk18 / m_pPool->m_unk48)) * kRadToDeg);  // 0x000d11b0
        if ((LeafOf(b)->m_sgProperties & 4u) == 0) UpdateBarrelGroundAndShadow(b);
    }
}

// 0x00441218 CKHkRollingBarrel_Update
void CKHkRollingBarrel::Update(IKTime* clock) {
    CKHkActorBase::Update(clock);  // 0x003f6e68 (empty)
    if (m_pPath == nullptr) return;
    DespawnBarrelsOnContact();
    if ((m_bitArray & 8u) != 0) {
        float time = m_fTimer + clock->m_afDeltaTime[0];
        if (!(time <= m_fPeriod)) {  // ble: past the period (a NaN too) the timeline wraps
            time = time - m_fPeriod;
            for (uint32_t i = 0; i < m_vSpawnTimes.m_ui32NbUsedElt; ++i) {
                const float at = m_vSpawnTimes.m_pBlock[i];
                if (m_fTimer < at || !(time <= at)) SpawnBarrel();  // blt; ble skips
            }
        } else {
            for (uint32_t i = 0; i < m_vSpawnTimes.m_ui32NbUsedElt; ++i) {
                const float at = m_vSpawnTimes.m_pBlock[i];
                if (m_fTimer >= at) continue;  // bge
                if (time <= at) continue;      // ble
                SpawnBarrel();
            }
        }
        m_fTimer = time;
    }
    UpdateBarrels(clock);
    // The landing squash: the scale curve over its span (y the curve, z 2 - the curve).
    for (uint32_t i = m_ui8NbBarrel; i != 0;) {
        --i;
        Barrel* b = m_apBarrels[i];
        const float t = b->m_unk3c;
        if (t <= kZero) continue;  // ble
        if (m_pPool->m_fCurveSpan > t) {
            const float y = m_pPool->EvaluateCurve(t);  // 0x00442200
            MovableOf(b)->ScaleXYZ(kOne, y, kTwo - y);  // 0x000d0d28
            b->m_unk3c = b->m_unk3c + clock->m_afDeltaTime[0];
        } else {
            b->m_unk3c = kZero;
        }
    }
}

// 0x00441438 CKHkRollingBarrel_Load: (level data) the three references and the end starter; then (every type) the
// period, the spawn times (each word swapped) and the four speed words. The vector is sized as TVector's resize does
// (1 and a 4-byte block for none; the used count then kept), the old block not freed.
int32_t CKHkRollingBarrel::Load(IKFile* file, int32_t type) {
    CKHkActorBase::Load(file, type);  // 0x003f6e98
    if (type == K_LEVEL_PLATEFORMS) {
        IKFile_ReadRef(file, &m_pUnk64);
        IKFile_ReadRef(file, &m_pPool);
        IKFile_ReadRef(file, &m_pPath);
        m_tsEndStarter.Load(file, 0);  // 0x002361c0
    }
    ReadF32LE(file, &m_fPeriod);
    uint32_t count = 0;
    ReadU32LE(file, &count);
    if (count == 0) {
        m_vSpawnTimes.m_ui32NbElt = 1;
        m_vSpawnTimes.m_pBlock = static_cast<float*>(Mem_AllocAligned16(4));  // 0x00053198
    } else {
        m_vSpawnTimes.m_ui32NbElt = count;
        m_vSpawnTimes.m_pBlock = static_cast<float*>(Mem_AllocAligned16(count * 4));
        if (m_vSpawnTimes.m_ui32NbElt < count) {  // never taken (kept from the original)
            const uint32_t capacity = count + 1;
            m_vSpawnTimes.m_pBlock = static_cast<float*>(Mem_ReallocAligned16(m_vSpawnTimes.m_pBlock, capacity * 4));
            m_vSpawnTimes.m_ui32NbElt = capacity;
        }
        m_vSpawnTimes.m_ui32NbUsedElt = count;
    }
    for (uint32_t i = 0; i < count; ++i) ReadF32LE(file, &m_vSpawnTimes.m_pBlock[i]);
    ReadF32LE(file, &m_fMinSpeed);
    ReadF32LE(file, &m_fMaxSpeed);
    ReadF32LE(file, &m_fBrake);
    ReadF32LE(file, &m_fAccel);
    return 1;
}
