// CKHkHazardousJet.cpp - reconstructed original translation unit 0x49f968-0x4a40d0 (GAME_TOC1, main_toc1), 40 functions, 32 live.
// Primary class: CKHkHazardousJet  key 0x2f42  category Hook  size 0xcc  vtable 0xb284d0
// Other owners: CKHkScrapShower (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x49f968  CKHkHazardousJet_Delete
//   [ ] 0x49f9b8  RegisterCKHkHazardousJetClass
//   [ ] 0x49fa30  _GLOBAL__I_49fa30
//   [x] 0x49fa40  CKHkHazardousJet_SetDefaultState
//   [x] 0x49faa0  CKHkHazardousJet_MessageProc
//   [x] 0x49fc00  CKHkHazardousJet_GetInfo  (in the header)
//   [ ] 0x49fc50  CKHkHazardousJet_UpdateHeroContactTimers_maybe  [dead]
//   [x] 0x49fdb0  CKHkHazardousJet_LaunchProjectile_maybe
//   [x] 0x49fff8  CKHkHazardousJet_Resume  (empty / no effect: inherited)
//   [x] 0x4a0020  CKHkHazardousJet_Pause  (empty / no effect: inherited)
//   [x] 0x4a0048  CKHkHazardousJet_Stop  (empty / no effect: inherited, CKHkActorBase_d82_maybe_Stop 0x3f6e50)
//   [x] 0x4a0070  CKHkHazardousJet_Start
//   [x] 0x4a00e0  CKHkHazardousJet_PostLoad  (in the header)
//   [ ] 0x4a0148  CKHkHazardousJet_Save
//   [x] 0x4a0170  CKHkHazardousJet_RecursiveRegistration  (= the inherited slot: CKHkActorBase_d82_maybe_LevelReset 0x3f6ee8, then 1)
//   [x] 0x4a0198  CKHkHazardousJet_Destroy  (inherited: CKHkActorBase_d82_maybe_ClearReferences 0x3f6e08 calls vt+0xc0, KStub_Nop_9c0bc8)
//   [x] 0x4a01c0  CKHkHazardousJet_Construct  [dead]
//   [x] 0x4a0200  CKHkHazardousJet_DeleteArray
//   [ ] 0x4a02a0  CKHkHazardousJet_Destructor_2  [dead]
//   [x] 0x4a0318  CKHkHazardousJet_DeletingDestructor  (the destructor)
//   [x] 0x4a03a0  CKHkHazardousJet_Destructor  (the destructor)
//   [x] 0x4a0418  CKHkHazardousJet_vfC8  (CKHkHazardousJet::ApplyStatePreset)
//   [ ] 0x4a0480  CKHkHazardousJet_Construct_2  [dead]
//   [x] 0x4a04c0  CKHkHazardousJet_OnActivate  (CKHkHazardousJet::VfA0)
//   [x] 0x4a0680  CKHkHazardousJet_CreateArray
//   [x] 0x4a0740  CKHkHazardousJet_Create
//   [x] 0x4a07a0  CKHkHazardousJet_Load
//   [x] 0x4a1288  CKHkHazardousJet_UpdateLightningTargets_maybe
//   [x] 0x4a1618  CKHkHazardousJet_ProcessHeroContacts_maybe
//   [ ] 0x4a1ad8  CKHkHazardousJet_AcquireFxBC_maybe  [dead]
//   [ ] 0x4a1d50  CKHkHazardousJet_AcquireFxB8_maybe  [dead]
//   [ ] 0x4a1fc8  CKHkHazardousJet_SetFxC0Active_maybe  [dead]
//   [x] 0x4a2350  CKHkHazardousJet_StopJetFx_maybe
//   [x] 0x4a24a8  CKHkHazardousJet_SetJetActive_maybe  (CKHkHazardousJet::VfD4)
//   [x] 0x4a2eb8  CKHkHazardousJet_vfCC  (CKHkHazardousJet::SetEnabled)
//   [x] 0x4a2f40  CKHkHazardousJet_Update
//   [x] 0x4a3e68  CKHkHazardousJet_OnDeactivate  (CKHkHazardousJet::VfA4)
//   [x] 0x4a3f40  CKHkHazardousJet_Restart
//   [x] 0x4a4048  CKHkScrapShower_Delete  (DOTD_DECLARE_FACTORIES in CKHkScrapShower.h)
//   [ ] 0x4a4098  FUN_004a4098  [dead]
//
//   [ ] 0x9c4de8  CKHkHazardousJet_IsKindOfClass  [inline]
//   [ ] 0x9c4e40  CKHkHazardousJet_GetClassType  [inline]
//   [ ] 0x9c4e48  CKHkHazardousJet_GetClassID  [inline]
#include "k2000/hooks/CKHkHazardousJet.h"

#include <cmath>
#include <cstring>

#include "Renderware/rwcore/RwCamera.h"
#include "Spyro2008/groups/IKGrpHero.h"
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "Spyro2008/hooks/IKHkHero.h"
#include "crt/ppc_ops.h"
#include "k2000/components/CKQuakeCameraLauncher.h"
#include "k2000/dictionaries/CKSoundDictionaryID.h"
#include "k2000/fx/CKSparkFxData.h"
#include "k2000/fx/IKFx.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/logic/CKParticlesEffectFxData.h"
#include "k2000/logic/CKProjectileAccessor.h"
#include "k2000/logic/IKFxData.h"
#include "k2000/logic/fx/CKExplosionNodeFx.h"
#include "k2000/logic/render/CKLightningBoltNodeFx.h"
#include "k2000/logic/sound/CKSound.h"
#include "k2000/managers/CKInput.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/CSGBranch.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/scenegraph/IKBoundingBox.h"
#include "k2000/services/CKSrvCollision.h"
#include "k2000/services/CKSrvFx.h"
#include "k2000/system/IKTime.h"

namespace {

const float kZero = 0.0f;   // TOC1 +0x61a4
const float kHalf = 0.5f;   // TOC1 +0x6164

CKSrvCollision* Collision() { return static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision); }  // engine +0x58
CKSrvFx* SrvFx() { return static_cast<CKSrvFx*>(g_pEngine->m_srvFx); }                          // engine +0x60
CKSoundDictionaryID* Sounds(const CKHkHazardousJet* j) { return static_cast<CKSoundDictionaryID*>(j->m_pUnk38); }
IKBoundingBox* Box(const CKHkHazardousJet* j) { return static_cast<IKBoundingBox*>(j->m_pUnk20); }
RwFrame* FrameOf(IKSerializable* node) { return static_cast<CSGMovable*>(node)->m_pRwFrame; }  // node +0x04

// Sound `index` played (from 0) when the dictionary has it.
void PlaySound(const CKHkHazardousJet* j, uint32_t index) {
    if (Sounds(j)->GetSound(index) == nullptr) return;  // 0x00112bc0
    CKSound_Play(kZero, Sounds(j)->GetSound(index));   // 0x00111230
}
// Sound `index` stopped when the dictionary has it.
void StopSound(const CKHkHazardousJet* j, uint32_t index) {
    if (Sounds(j)->GetSound(index) == nullptr) return;
    Sound_Stop(Sounds(j)->GetSound(index), 0);  // 0x001111b0
}
// The looping sound 1 started.
void PlayLoopSound1(const CKHkHazardousJet* j) {
    if (Sounds(j)->GetSound(1) != nullptr) Sounds(j)->GetSound(1)->SetLoop(1);  // 0x00110fd0
    PlaySound(j, 1);
}

// A particle effect data's start (the inlined attach): attached to the jet's node (+0x10), no hot spot (+0x14), then a
// pooled effect of it acquired (CKSrvFx::AcquireFx inlined, the reserving copy).
IKFx* AcquireAttachedEffect(CKHkHazardousJet* j, IKSerializable* data) {
    CKParticlesEffectFxData* effect = static_cast<CKParticlesEffectFxData*>(data);
    effect->m_pAttachHotSpot = nullptr;
    effect->m_pAttachOwner = static_cast<CSGLeaf*>(j->m_pKGLObject);
    return SrvFx()->AcquireFx(effect, j);
}

// The spark's start: its matrix (the data's +0x14) = the node's world matrix, then an effect acquired.
IKFx* AcquireSpark(CKHkHazardousJet* j) {
    CKSparkFxData* spark = static_cast<CKSparkFxData*>(j->m_pUnk30);
    std::memcpy(spark->m_unk14, FrameLtm(FrameOf(j->m_pKGLObject)), sizeof(RwMatrix));  // frame +0x50, 0x40 bytes
    return SrvFx()->AcquireFx(spark, j);
}

// The box's half sizes (x, `y`, z of +0x64), its radius from them, and its frame's position (0, `posY`, 0).
void SetBoxSize(CKHkHazardousJet* j, float y, float posY) {
    IKBoundingBox* box = Box(j);
    const float x = j->m_afUnk64[0];
    const float z = j->m_afUnk64[2];
    box->m_Extent.x = x;
    box->m_Extent.z = z;
    box->m_Extent.y = y;
    // fmuls y * y, then fmadds x, then fmadds z (the same order in all three of the original's copies).
    box->m_fRadius = std::sqrt(ppc::fmadds(z, z, ppc::fmadds(x, x, y * y)));  // Math_Sqrtf 0x10690
    RwFrame* frame = FrameOf(box);
    frame->modelling.pos.z = kZero;
    frame->modelling.pos.y = posY;
    frame->modelling.pos.x = kZero;
    frame->modelling.flags &= 0xfffdffffu;
    RwFrame_MarkDirty(frame);  // 0x00010698
}

// The contact list given back (the nodes to their pool in the original).
void FreeContacts(CKHkHazardousJet* j) {
    for (CKHkHazardousJet::JetContact* c = j->m_pUnkC8; c != nullptr;) {
        CKHkHazardousJet::JetContact* next = c->m_pNext;
        delete c;
        c = next;
    }
    j->m_pUnkC8 = nullptr;
}

// A draw of Rand_Int's low 16 bits as a float (rldicl 48, std, fcfid, frsp).
float RandU16() { return static_cast<float>(static_cast<double>(static_cast<uint32_t>(Rand_Int()) & 0xffffu)); }

// The block of the hero's hazard query 0xc32 (CKHkScrapShower.cpp's ScrapHazardQuery, the same layout).
struct JetHazardQuery {
    IKSerializable* m_hero;   // +0x00
    void* m_volume;           // +0x04
    float m_knock[3];         // +0x08..+0x10
    CVector3 m_point;         // +0x14
    int32_t m_kind;           // +0x20
    uint8_t m_damage;         // +0x24
};

}  // namespace

CKHkHazardousJet::CKHkHazardousJet() {
    m_pUnkC8 = nullptr;
    // Runtime members the Load does not read: the fresh heap's zeros.
    m_fUnkAC = 0.0f;
    m_fUnkB0 = 0.0f;
    m_fUnkB4 = 0.0f;
    m_pUnkB8 = nullptr;
    m_pUnkBC = nullptr;
    m_pUnkC0 = nullptr;
    m_pUnkC4 = nullptr;
}

CKHkHazardousJet::~CKHkHazardousJet() { FreeContacts(this); }

// 0x0049fa40 CKHkHazardousJet_SetDefaultState
void CKHkHazardousJet::SetDefaultState(int32_t flag) {
    CKHkActorBase::SetDefaultState(flag);  // 0x003f72a0 (empty)
    m_bitArray = (m_bitArray & 0xfffffff7u) | ((static_cast<uint32_t>(m_unkA4) << 3) & 0xfffffff8u);
}

// 0x0049faa0 CKHkHazardousJet_MessageProc
int32_t CKHkHazardousJet::MessageProc(uint16_t message, void* data) {
    const int32_t base = CKHkActorBase::MessageProc(message, data);  // 0x003f7148
    int32_t own = 1;
    if (message == 0xc32) {
        JetHazardQuery* query = static_cast<JetHazardQuery*>(data);
        query->m_damage = m_unk58;
        own = 0;
        if (query->m_volume == nullptr) {
            query->m_knock[2] = 0.0f;
            query->m_knock[0] = 0.0f;
            query->m_knock[1] = 0.0f;
        } else {
            query->m_knock[0] = m_afUnk4C[0];
            query->m_knock[1] = m_afUnk4C[1];
            query->m_knock[2] = m_afUnk4C[2];
            const RwMatrix* ltm = FrameLtm(FrameOf(static_cast<IKSerializable*>(query->m_volume)));  // +0x80
            query->m_point.x = ltm->pos.x;
            query->m_point.z = ltm->pos.z;
            query->m_point.y = ltm->pos.y;
        }
    }
    if (base == 3 || own == 3) return 3;
    if (base == 2 || own == 2) return 2;
    return base == 0 ? 0 : own;
}

// 0x0049fdb0 CKHkHazardousJet_LaunchProjectile_maybe
void CKHkHazardousJet::LaunchProjectile() {
    CKProjectileAccessor* accessor = static_cast<CKProjectileAccessor*>(m_pUnk78);
    if (accessor->m_pProjectileType == nullptr) return;
    const RwMatrix* ltm = FrameLtm(FrameOf(m_pKGLObject));
    CVector3 dir = {ltm->up.x, ltm->up.y, ltm->up.z};
    CVector3 pos;
    pos.z = ppc::fmadds(ltm->up.z, kHalf, ltm->pos.z);
    pos.x = ppc::fmadds(ltm->up.x, kHalf, ltm->pos.x);
    pos.y = ppc::fmadds(ltm->up.y, kHalf, ltm->pos.y);
    dir = {ltm->up.x, ltm->up.y, ltm->up.z};
    const float scale = -3.051804378628731e-05f;  // TOC1 +0x6168 (0xb8000080)
    const float one = 1.0f;                        // TOC1 +0x616c
    float s = ppc::fmadds(RandU16(), scale, one) * m_fUnk8C;
    dir.z = ppc::fmadds(s, ltm->at.z, dir.z);
    dir.x = ppc::fmadds(s, ltm->at.x, dir.x);
    dir.y = ppc::fmadds(s, ltm->at.y, dir.y);
    s = ppc::fmadds(RandU16(), scale, one) * m_fUnk8C;
    dir.z = ppc::fmadds(s, ltm->right.z, dir.z);
    dir.x = ppc::fmadds(s, ltm->right.x, dir.x);
    dir.y = ppc::fmadds(s, ltm->right.y, dir.y);
    const float u = RandU16();
    const float speed = ppc::fmadds(u / 65535.0f, m_fUnk88 - m_fUnk84, m_fUnk84);  // TOC1 +0x6170
    accessor->Launch(&pos, &dir, speed, this, nullptr);  // 0x001f2908
}

// 0x004a0070 CKHkHazardousJet_Start
void CKHkHazardousJet::Start() {
    CKHkActorBase::Start();  // 0x003f6e48 (empty)
    m_pUnkC4 = nullptr;
    m_fUnkB0 = m_fUnk80;
    m_pUnkB8 = nullptr;
    m_pUnkBC = nullptr;
    Restart();  // vt+0x54
}

// 0x004a0418 CKHkHazardousJet_vfC8
void CKHkHazardousJet::ApplyStatePreset(int32_t state) {
    const bool on = (m_unkA4 != 0 && state == 0) || (m_unkA5 != 0 && state != 0);
    m_bitArray = (m_bitArray & 0xfffffff7u) | (on ? 8u : 0u);
}

// 0x004a04c0 CKHkHazardousJet_OnActivate
void CKHkHazardousJet::VfA0() {
    CKHkActorBase::VfA0();  // 0x003f7338
    IKBoundingBox* box = Box(this);
    if (box->m_pParent != nullptr) box->m_pParent->RemoveChild(box);  // vt+0x78
    static_cast<CSGBranch*>(m_pKGLObject)->AddChild(box);              // vt+0x70
    SetBoxSize(this, m_afUnk64[1], m_afUnk64[1] - kHalf);
    m_fUnkAC = 0.0f;
    FreeContacts(this);
    m_bitArray &= 0xffffff8fu;
    m_pUnkC4 = nullptr;
    m_fUnkB0 = m_fUnk80;
    m_fUnkB4 = 0.0f;
    m_pUnkC0 = nullptr;
}

// 0x004a1288 CKHkHazardousJet_UpdateLightningTargets_maybe
void CKHkHazardousJet::UpdateLightningTargets() {
    if (m_pUnk34 == nullptr) return;
    if (m_pUnkC4 == nullptr) {
        m_pUnkC4 = SrvFx()->AcquireFx(static_cast<IKFxData*>(m_pUnk34), this);  // CKSrvFx::AcquireFx inlined
        if (m_pUnkC4 == nullptr) return;
    }
    CKLightningBoltNodeFx* bolt = static_cast<CKLightningBoltNodeFx*>(m_pUnkC4);
    const RwMatrix* ltm = FrameLtm(FrameOf(m_pKGLObject));
    const CVector3 from = {ltm->pos.x, ltm->pos.y, ltm->pos.z};
    bolt->SetNodePosition(&from, this);  // 0x0098f680 -> 0x0057c430
    IKBoundingBox* box = Box(this);
    const float height = box->m_Extent.y + box->m_Extent.y;
    const RwMatrix* boxLtm = FrameLtm(FrameOf(box));  // the box's own frame
    CVector3 to;
    to.x = ppc::fmadds(height, boxLtm->up.x, from.x);
    to.y = ppc::fmadds(height, boxLtm->up.y, from.y);
    to.z = ppc::fmadds(height, boxLtm->up.z, from.z);
    static_cast<CKLightningBoltNodeFx*>(m_pUnkC4)->SetTargetPoint(&to, this);  // 0x0098f3d0 -> 0x0057a9d0
    if ((m_pUnkC4->m_baFxData & 8u) != 0) return;
    static_cast<CKLightningBoltNodeFx*>(m_pUnkC4)->SetActiveForOwner(this, 1);  // 0x0098f3c0 -> 0x00581380
}

// 0x004a1618 CKHkHazardousJet_ProcessHeroContacts_maybe
void CKHkHazardousJet::ProcessHeroContacts() {
    for (ICollision* c = static_cast<ICollision*>(Box(this)->m_CollisionResList); c != nullptr; c = c->m_pNext) {
        IKSerializable* owner = static_cast<IKBoundingVolume*>(c->GetBoundingVolume1())->m_pOwner;  // vt+0x00
        if (owner == this) owner = static_cast<IKBoundingVolume*>(c->GetBoundingVolume2())->m_pOwner;  // vt+0x04
        if (static_cast<uint8_t>(owner->IsKindOfClass(0x3642)) == 0) continue;  // vt+0x08
        JetContact* known = nullptr;
        for (JetContact* e = m_pUnkC8; e != nullptr; e = e->m_pNext) {
            if (e->m_pHero == owner) {
                known = e;
                break;
            }
        }
        if (known != nullptr) {
            if (known->m_bTouched != 0) continue;
            known->m_bTouched = 1;
            known->m_fWindowStart = known->m_fTime;
            continue;
        }
        JetContact* entry = new JetContact;  // FreeListPool 0x00ceaa60 (FreeListPool_Grow when empty)
        entry->m_pNext = nullptr;
        entry->m_pHero = owner;
        entry->m_fTime = 0.0f;
        entry->m_bTouched = 1;
        entry->m_fWindowStart = 0.0f;
        entry->m_pNext = m_pUnkC8;
        m_pUnkC8 = entry;
        IKFx* fx = SrvFx()->AcquireFx(static_cast<IKFxData*>(m_pUnk2C), this);  // CKSrvFx::AcquireFx inlined
        if (fx == nullptr) continue;
        CKExplosionNodeFx* explosion = static_cast<CKExplosionNodeFx*>(fx);
        const CVector3* normal = c->GetNormale12();       // vt+0x1c
        const CVector3* point = c->GetWorldContactPoint();  // vt+0x20
        explosion->SetPosition(normal, point, this);  // 0x001b6438
        explosion->Trigger(this, nullptr);            // 0x001b82a8
        fx->ReleaseReservation(this);                 // vt+0x54
    }
}

// 0x004a2350 CKHkHazardousJet_StopJetFx_maybe
void CKHkHazardousJet::StopJetFx() {
    if (m_pUnkB8 != nullptr) {
        StopOwnedParticleEffect(m_pUnkB8, this);  // 0x001cdde8
        m_pUnkB8->ReleaseReservation(this);       // vt+0x54
        m_pUnkB8 = nullptr;
    }
    if (m_pUnkBC != nullptr) {
        StopOwnedParticleEffect(m_pUnkBC, this);
        m_pUnkBC->ReleaseReservation(this);
        m_pUnkBC = nullptr;
    }
    if (m_pUnkC4 != nullptr) {
        m_pUnkC4->StopAndRelease(this);  // vt+0x58
        m_pUnkC4 = nullptr;
    }
    if (m_pUnkC0 != nullptr) {
        m_pUnkC0->StopAndRelease(this);
        m_pUnkC0 = nullptr;
    }
}

// 0x004a24a8 CKHkHazardousJet_SetJetActive_maybe
void CKHkHazardousJet::VfD4(int32_t on, int32_t mode) {
    m_bitArray = (m_bitArray & 0xffffffbfu) | ((static_cast<uint32_t>(on) << 6) & 0xffffffc0u);
    if ((m_bitArray & 0x10u) != 0) {
        if (on != 0) return;
        m_bitArray &= 0xffffffefu;
        StopJetFx();
        StopSound(this, 1);
        Collision()->DisableVolume(Box(this));  // 0x001920e8
        m_bitArray &= 0xffffffdfu;
        QueueTriggerSignals(&m_tsUnk9C);  // 0x00236338
        return;
    }
    if (on == 0) return;
    m_bitArray = (m_bitArray & 0xffffffefu) | 0x10u;
    if (mode != 0) {
        if (m_pUnkBC == nullptr) m_pUnkBC = AcquireAttachedEffect(this, m_pUnk28);
        static_cast<CKQuakeCameraLauncher*>(m_pUnk74)->Trigger();  // 0x001533c0
        PlaySound(this, 2);
        PlayLoopSound1(this);
        Collision()->EnableVolume(Box(this));  // 0x00192090
        m_bitArray = (m_bitArray & 0xffffffdfu) | 0x20u;
        m_fUnkAC = 0.0f;
    } else {
        if (m_pUnkB8 == nullptr) m_pUnkB8 = AcquireAttachedEffect(this, m_pUnk24);
        if (m_pUnkC0 == nullptr) m_pUnkC0 = AcquireSpark(this);
        static_cast<CKQuakeCameraLauncher*>(m_pUnk70)->Trigger();  // 0x001533c0
        PlaySound(this, 0);
        PlaySound(this, 2);
        m_fUnkAC = m_fUnk44;
    }
    QueueTriggerSignals(&m_tsUnk94);  // 0x00236338
}

// 0x004a2eb8 CKHkHazardousJet_vfCC
void CKHkHazardousJet::SetEnabled(int32_t enabled) {
    if (enabled == 0) {
        StopJetFx();
        Collision()->DisableVolume(Box(this));  // 0x001920e8
    }
    m_bitArray = (m_bitArray & 0xfffffff7u) | ((static_cast<uint32_t>(enabled) << 3) & 0xfffffff8u);
}

// 0x004a2f40 CKHkHazardousJet_Update
void CKHkHazardousJet::Update(IKTime* clock) {
    CKHkActorBase::Update(clock);  // 0x003f6e68 (empty)
    // The contacts: each one's time runs on; past its window (+0x5c after its last new touch) it goes, else the hero is
    // hurt (its pending source: this jet) whenever the time crosses a multiple of the period +0x60.
    const float dt = clock->m_afDeltaTime[0];  // +0x1c
    JetContact* prev = nullptr;
    for (JetContact* c = m_pUnkC8; c != nullptr;) {
        const float before = c->m_fTime;
        const float now = dt + before;
        c->m_bTouched = 0;
        c->m_fTime = now;
        if (m_fUnk5C + c->m_fWindowStart >= now) {  // bge: a NaN keeps it
            const int32_t a = ppc::fctiwz(before / m_fUnk60);
            const int32_t b = ppc::fctiwz(now / m_fUnk60);
            if (a != b) static_cast<IKHkHero*>(c->m_pHero)->SetPendingSource(this, nullptr);  // 0x00362fd0
            prev = c;
            c = c->m_pNext;
            continue;
        }
        JetContact* next = c->m_pNext;
        if (m_pUnkC8 == c) {
            delete c;
            m_pUnkC8 = next;
            prev = nullptr;
        } else {
            prev->m_pNext = next;
            delete c;
        }
        c = next;
    }
    // A stopped jet's effects go after +0x90 seconds.
    if (m_fUnkB4 > kZero) {  // ble: a NaN skips
        const float left = m_fUnkB4 - clock->m_afDeltaTime[0];
        m_fUnkB4 = left;
        if (left <= kZero) StopJetFx();  // cror lt|eq
    }
    const uint32_t bits = m_bitArray;
    if ((bits & 8u) == 0) return;
    // The heroes: one within +0x3c keeps (or makes) the jet running, one within +0x40 boosts it.
    uint32_t inRange = (bits >> 4) & 1u;
    uint32_t close = 0;
    if ((bits & 0x40u) == 0) {
        inRange = 0;
        IKBoundingBox* box = Box(this);
        const RwMatrix* ltm = FrameLtm(FrameOf(box));
        const float cy = ltm->pos.y - box->m_Extent.y;
        const float cz = ltm->pos.z;
        const float cx = ltm->pos.x;
        IKGrpHero* group = static_cast<IKGrpHero*>(g_pEngine->m_gameManager->m_unk04[1]);  // engine +0x8c -> +0x08
        for (int32_t i = 0; static_cast<int32_t>(group->m_ui8ControlledHeroCount) > i; ++i) {  // 0x002ca288
            CKHkS08Hero* hero = static_cast<CKHkS08Hero*>(group->m_apControlledHeroes[i]);  // 0x002ca0e0
            const float* p = hero->GetPositionPtr();  // 0x00361968
            const float range = m_fUnk3C;
            if (!(range > kZero)) continue;  // ble
            const float dy = p[1] - cy;
            const float dx = p[0] - cx;
            const float dz = p[2] - cz;
            const float d2 = ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy));
            if (!(range * range > d2)) continue;  // ble
            const float boost = m_fUnk40;
            inRange = 1;
            if (!(boost > kZero)) continue;
            if (!(boost * boost > d2)) continue;
            close = 1;
        }
    }
    const uint32_t state = m_bitArray;
    if ((state & 0x10u) == 0) {
        // Not running: a hero in range starts it.
        if (inRange != 0) {
            if (m_pUnkB8 == nullptr) m_pUnkB8 = AcquireAttachedEffect(this, m_pUnk24);
            static_cast<CKQuakeCameraLauncher*>(m_pUnk70)->Trigger();  // 0x001533c0
            PlaySound(this, 2);
            PlaySound(this, 0);
            m_fUnkAC = m_fUnk44;
            m_fUnkB4 = 0.0f;
            QueueTriggerSignals(&m_tsUnk94);  // 0x00236338
        }
        m_bitArray = (m_bitArray & 0xffffffefu) | (inRange << 4);
        return;
    }
    if (inRange == 0) {
        // Running with no hero in range: it stops.
        m_fUnkB4 = m_fUnk90;
        StopSound(this, 1);
        StopSound(this, 0);
        PlaySound(this, 3);
        Collision()->DisableVolume(Box(this));  // 0x001920e8
        m_bitArray &= 0xffffffdfu;
        QueueTriggerSignals(&m_tsUnk9C);  // 0x00236338
        m_bitArray = (m_bitArray & 0xffffffefu) | (inRange << 4);
        return;
    }
    if ((state & 0x20u) != 0) {
        // Full strength: the bolt, the box shrinking back over +0x48 s, the projectiles and the contacts.
        UpdateLightningTargets();
        if (m_fUnkAC > kZero) {  // ble: a NaN skips
            const float left = m_fUnkAC - clock->m_afDeltaTime[0];
            m_fUnkAC = left;
            if (left < kZero) m_fUnkAC = kZero;  // blt
            const float k = m_fUnkAC / m_fUnk48;
            const float h = m_afUnk64[1];
            const float y = ppc::fmadds(k, kHalf - h, h);
            SetBoxSize(this, y, y - kHalf);
        }
        const float delay = m_fUnkB0;
        if (delay >= kZero) {  // cror gt|eq: a NaN skips
            const float left = delay - clock->m_afDeltaTime[0];
            m_fUnkB0 = left;
            if (left <= kZero) {  // cror lt|eq
                const float u = RandU16();
                m_fUnkB0 = ppc::fmadds(u / 65535.0f, m_fUnk80 - m_fUnk7C, m_fUnk7C);  // TOC1 +0x6170
                LaunchProjectile();
            }
        }
        ProcessHeroContacts();
        m_bitArray = (m_bitArray & 0xffffffefu) | (inRange << 4);
        return;
    }
    // Warming up: the timer runs down; a hero close by cuts it to 0.2 s with the boost.
    const float quick = 0.2f;  // TOC1 +0x61a8
    const float timer = m_fUnkAC;
    float next;
    bool boostTest;
    if (close != 0) {
        next = quick;
        if (!(timer > quick)) next = kZero;  // ble: a NaN takes it
        boostTest = true;
    } else {
        next = timer - clock->m_afDeltaTime[0];
        boostTest = next <= quick;  // cror lt|eq: a NaN skips the boost test
    }
    // The boost while the timer was still above 0.2 (ble: a NaN skips it).
    if (boostTest && timer > quick) {
        // The boost: its effect, the spark, the rumble, the quake, sounds 2 and 1 (looping).
        if (m_pUnkBC == nullptr) m_pUnkBC = AcquireAttachedEffect(this, m_pUnk28);
        if (m_pUnkC0 == nullptr) m_pUnkC0 = AcquireSpark(this);
        static_cast<CKInput*>(g_pEngine->m_input)->AddRumbleRequest(m_fUnkA8, this, 0, 0xff, m_unkA6, m_unkA7);  // 0x001049d8
        static_cast<CKQuakeCameraLauncher*>(m_pUnk74)->Trigger();  // 0x001533c0
        PlaySound(this, 2);
        PlayLoopSound1(this);
        m_fUnkAC = next;
        m_bitArray = (m_bitArray & 0xffffffefu) | (inRange << 4);
        return;
    }
    if (!(next <= kZero)) {  // cror lt|eq: a NaN keeps warming up
        m_fUnkAC = next;
        m_bitArray = (m_bitArray & 0xffffffefu) | (inRange << 4);
        return;
    }
    // The warm-up is over: full strength, the box on at half height.
    Collision()->EnableVolume(Box(this));  // 0x00192090
    SetBoxSize(this, kHalf, kZero);
    m_bitArray = (m_bitArray & 0xffffffdfu) | 0x20u;
    m_fUnkAC = m_fUnk48;
    m_bitArray = (m_bitArray & 0xffffffefu) | (inRange << 4);
}

// 0x004a3e68 CKHkHazardousJet_OnDeactivate
void CKHkHazardousJet::VfA4() {
    CKHkActorBase::VfA4();  // 0x003f7370
    IKBoundingBox* box = Box(this);
    Collision()->DisableVolume(box);  // 0x001920e8
    if (box->m_pParent != nullptr) box->m_pParent->RemoveChild(box);                 // vt+0x78
    static_cast<CSGBranch*>(g_pEngine->m_dynamicSceneRoot)->AddChild(box);  // engine +0x14, vt+0x70
    StopJetFx();
}

// 0x004a3f40 CKHkHazardousJet_Restart
void CKHkHazardousJet::Restart() {
    m_bitArray &= 0xffffffbfu;
    if ((m_bitArray & 4u) != 0) return;
    m_fUnkB0 = m_fUnk80;
    m_fUnkB4 = 0.0f;
    FreeContacts(this);
    m_bitArray &= 0xffffffcfu;
    StopJetFx();
    if (m_pUnkC0 != nullptr) {
        m_pUnkC0->StopAndRelease(this);  // vt+0x58
        m_pUnkC0 = nullptr;
    }
}

// 0x004a07a0 CKHkHazardousJet_Load
int32_t CKHkHazardousJet::Load(IKFile* file, int32_t type) {
    CKHkActorBase::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    IKFile_ReadRef(file, &m_pUnk20);
    for (float& f : m_afUnk64) ReadF32LE(file, &f);
    IKFile_ReadRef(file, &m_pUnk24);
    IKFile_ReadRef(file, &m_pUnk28);
    IKFile_ReadRef(file, &m_pUnk2C);
    IKFile_ReadRef(file, &m_pUnk38);
    IKFile_ReadRef(file, &m_pUnk70);
    IKFile_ReadRef(file, &m_pUnk74);
    IKFile_ReadRef(file, &m_pUnk78);
    ReadF32LE(file, &m_fUnk7C);
    ReadF32LE(file, &m_fUnk80);
    ReadF32LE(file, &m_fUnk3C);
    ReadF32LE(file, &m_fUnk40);
    ReadF32LE(file, &m_fUnk44);
    ReadF32LE(file, &m_afUnk4C[0]);
    ReadF32LE(file, &m_afUnk4C[1]);
    ReadF32LE(file, &m_afUnk4C[2]);
    ReadU8(file, &m_unk58);
    ReadF32LE(file, &m_fUnk5C);
    ReadF32LE(file, &m_fUnk60);
    ReadF32LE(file, &m_fUnk48);
    ReadF32LE(file, &m_fUnk84);
    ReadF32LE(file, &m_fUnk88);
    ReadF32LE(file, &m_fUnk8C);
    ReadF32LE(file, &m_fUnk90);
    IKFile_ReadRef(file, &m_pUnk30);
    IKFile_ReadRef(file, &m_pUnk34);
    m_tsUnk94.Load(file, K_LEVEL_PLATEFORMS);
    m_tsUnk9C.Load(file, K_LEVEL_PLATEFORMS);
    ReadU8(file, &m_unkA4);
    ReadU8(file, &m_unkA5);
    ReadU8(file, &m_unkA6);
    ReadU8(file, &m_unkA7);
    ReadF32LE(file, &m_fUnkA8);
    return 1;
}
