// CKHkS08DragonCityGolem.cpp - reconstructed original translation unit 0x4d5418-0x4d6cc8 (GAME_TOC1, main_toc1), 30 functions, 28 live.
// Primary class: CKHkS08DragonCityGolem  key 0x31c2  category Hook  size 0xe0  vtable 0xb29df0
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x4d5418  CKHkS08DragonCityGolem_Delete
//   [x] 0x4d5468  CKHkS08DragonCityGolem_vf100
//   [x] 0x4d5470  CKHkS08DragonCityGolem_vf104
//   [x] 0x4d5478  CKHkS08DragonCityGolem_vf108
//   [x] 0x4d5480  CKHkS08DragonCityGolem_AccumulateDamage_maybe
//   [x] 0x4d5728  CKHkS08DragonCityGolem_ApplyPendingDamage_maybe
//   [x] 0x4d5a78  CKHkS08DragonCityGolem_Update
//   [x] 0x4d5ae8  CKHkS08DragonCityGolem_Resume  (empty / no effect: inherited)
//   [x] 0x4d5b10  CKHkS08DragonCityGolem_Pause  (empty / no effect: inherited)
//   [x] 0x4d5b38  CKHkS08DragonCityGolem_Restart
//   [x] 0x4d5b90  CKHkS08DragonCityGolem_Stop
//   [x] 0x4d5bb8  CKHkS08DragonCityGolem_Start
//   [x] 0x4d5c10  CKHkS08DragonCityGolem_PostLoad
//   [x] 0x4d5c38  CKHkS08DragonCityGolem_Load
//   [ ] 0x4d5c60  CKHkS08DragonCityGolem_Save
//   [x] 0x4d5c88  CKHkS08DragonCityGolem_RecursiveRegistration  (inherited: CKHkGolem's)
//   [x] 0x4d5cb0  CKHkS08DragonCityGolem_Destroy  (CKHkGolem's, inherited)
//   [x] 0x4d5cd8  CKHkS08DragonCityGolem_Destructor  (CKHkGolem's; DOTD: the +0xc0 contact entries are not returned to their pool)
//   [ ] 0x4d5d50  CKHkS08DragonCityGolem_Construct  [dead]
//   [ ] 0x4d5d90  CKHkS08DragonCityGolem_Construct_2  [dead]
//   [x] 0x4d5dd0  CKHkS08DragonCityGolem_DeleteArray
//   [ ] 0x4d5e78  RegisterCKHkS08DragonCityGolemClass
//   [ ] 0x4d5f00  _GLOBAL__D_4d5f00
//   [ ] 0x4d5f10  _GLOBAL__I_4d5f10
//   [ ] 0x4d5f20  CKHkS08DragonCityGolem_DestructBody  [dead: no pointer to its descriptor 0xbcce80, no call]
//   [x] 0x4d5f98  CKHkS08DragonCityGolem_DeletingDestructor
//   [x] 0x4d6020  CKHkS08DragonCityGolem_GetNearestAimVolume_maybe
//   [x] 0x4d63a0  CKHkS08DragonCityGolem_CreateArray
//   [x] 0x4d6468  CKHkS08DragonCityGolem_Create
//   [x] 0x4d64c8  CKHkS08DragonCityGolem_ProcessDamageContacts_maybe
//
//   [ ] 0x9c5ec8  CKHkS08DragonCityGolem_IsKindOfClass  [inline]
//   [ ] 0x9c5f28  CKHkS08DragonCityGolem_GetClassType  [inline]
//   [ ] 0x9c5f30  CKHkS08DragonCityGolem_GetClassID  [inline]
#include "Spyro2008/hooks/CKHkS08DragonCityGolem.h"
#include <cstring>
#include "k2000/system/IKTime.h"
#include "k2000/system/CTimeManager.h"
#include "k2000/misc/Engine.h"
#include "Spyro2008/groups/C22SpyroShims.h"
#include "crt/ppc_ops.h"
#include "k2000/core/Stub.h"
#include "k2000/logic/CKGolemAttackCommon.h"
#include "k2000/logic/CKGolemPhaseAttack.h"
#include "k2000/math/Math.h"
#include "k2000/misc/OnNewHit.h"
#include "k2000/scenegraph/IKBoundingVolume.h"
#include "k2000/services/CKSrvCollision.h"
#include "Renderware/rwcore/RwCamera.h"
#include "Spyro2008/groups/IKGrpHero.h"
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "Spyro2008/logic/CKS08Damage.h"
#include "Spyro2008/logic/CKS08ElementDamage.h"
#include "Spyro2008/logic/CKS08GameManager.h"
#include "k2000/logic/CKGolemPhaseManager.h"
#include "k2000/math/Vec3.h"

// 0x004d5c38 CKHkS08DragonCityGolem_Load: CKHkGolem's part only.
int32_t CKHkS08DragonCityGolem::Load(IKFile* file, int32_t type) {
    CKHkGolem::Load(file, type);
    return 1;
}

// 0x004d5c10 CKHkS08DragonCityGolem_PostLoad: CKHkGolem's.
int32_t CKHkS08DragonCityGolem::PostLoad(int32_t type) {
    CKHkGolem::PostLoad(type);  // 0x004bf308
    return 1;
}

// 0x004d5bb8 CKHkS08DragonCityGolem_Start: CKHkGolem's, then the damage state cleared.
void CKHkS08DragonCityGolem::Start() {
    CKHkGolem::Start();  // 0x004bf970
    m_unkD4[0] = 0;
    m_unkD4[1] = 0;
    m_unkCC[1] = 0.0f;
    m_unkC4[0] = nullptr;
    m_unkD8[0] = 0.0f;
    m_unkCC[0] = 0.0f;
    m_unkC4[1] = nullptr;
    m_unkD8[1] = 0.0f;
}

// ---- C2.8: the Dragon City golem's damage ----

// 0x004d5b38 CKHkS08DragonCityGolem_Restart: CKHkGolem's, then the damage state cleared.
void CKHkS08DragonCityGolem::Restart() {
    CKHkGolem::Restart();  // 0x004bfa18
    m_unkD4[1] = 0;
    m_unkCC[1] = 0.0f;
    m_unkC4[0] = nullptr;
    m_unkD4[0] = 0;
    m_unkD8[0] = 0.0f;
    m_unkCC[0] = 0.0f;
    m_unkC4[1] = nullptr;
    m_unkD8[1] = 0.0f;
}

// 0x004d5a78 CKHkS08DragonCityGolem_Update: while updated (+0x45), CKHkGolem's, then the pending damage.
void CKHkS08DragonCityGolem::Update(IKTime* clock) {
    if (m_unk45 == 0) return;
    CKHkGolem::Update(clock);  // 0x004c4838
    ApplyPendingDamage(clock);
}

// 0x004d5480 CKHkS08DragonCityGolem_AccumulateDamage_maybe: an element damage (0x99cc) of kind below 10 adds amount x
// the kind's factor (+0x94 + 4 x kind; kind 9 uses kind 8's) to the slot (fmadds), another kind adds nothing; a hero
// damage (0x998c) adds amount x +0xb8; any other damage replaces the slot with the amount. A slot of at least 1.0
// (fcmpu + cror: a NaN waits) keeps its fraction (the whole part through fctidz, its low word as unsigned, fcfid /
// frsp) and the whole part, when not 0, is applied.
void CKHkS08DragonCityGolem::AccumulateDamage(float amount, CKS08Damage* damage, uint32_t slot) {
    if (damage->IsKindOfClass(0x99cc) != 0) {
        const uint32_t kind = damage->m_unk20;
        if (kind <= 9) {
            static const uint8_t kFactor[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 8};  // the jump table 0x004d55cc
            m_unkCC[slot] = ppc::fmadds(amount, m_af94[kFactor[kind]], m_unkCC[slot]);
        }
    } else if (damage->IsKindOfClass(0x998c) != 0) {
        m_unkCC[slot] = ppc::fmadds(amount, m_af94[9], m_unkCC[slot]);
    } else {
        m_unkCC[slot] = amount;
    }
    const float pending = m_unkCC[slot];
    if (!(pending >= 1.0f)) return;
    const int64_t whole = ppc::fctidz(pending);
    const uint32_t low = static_cast<uint32_t>(whole);
    m_unkCC[slot] = pending - static_cast<float>(static_cast<double>(static_cast<uint64_t>(low)));
    if (static_cast<int32_t>(low) != 0) ApplyDamagePoints(static_cast<int32_t>(low));  // 0x004becc8
}

namespace {
// The continuous damage of a frame: the amount (per second when +0x0c: x the frame time); an element damage of kind 7
// with no amount takes Cynder's (GetHeroByDragonIndex 1) element level of the damage's ability (+0x38's low byte): 3:
// 60, 2: 30, below 2: 20 per second (TOC +0x6a80 / +0x6a84 / +0x6a88).
float ContinuousAmount(const CKS08Damage* damage, float dt) {
    float amount = damage->m_unk0c != 0 ? dt * damage->m_unk04 : damage->m_unk04;
    if (damage->m_unk20 == 7 && amount == 0.0f) {
        IKGrpHero* group = static_cast<IKGrpHero*>(g_pEngine->m_gameManager->m_unk04[1]);
        CKHkS08Hero* cynder = static_cast<CKHkS08Hero*>(group->m_apHeros[1]);  // 0x002ca080
        const uint8_t ability = static_cast<uint8_t>(static_cast<const CKS08ElementDamage*>(damage)->m_unk38);
        const uint8_t level = cynder->GetAbilityElementLevel(ability);  // 0x0032a8d0
        if (level == 2) {
            amount = dt * 30.0f;
        } else if (level < 2) {
            amount = dt * 20.0f;
        } else if (level == 3) {
            amount = dt * 60.0f;
        }
    }
    return amount;
}
}  // namespace

// 0x004d5728 CKHkS08DragonCityGolem_ApplyPendingDamage_maybe: each dragon's continuous damage of this frame (+0xc4 /
// +0xc8) is accumulated into its slot; its hit count timer starts at its first frame, then every 0.3 s (TOC +0x6a74;
// fcmpu + cror) one combo hit is counted (OnNewHitW_2 0x4fe5f8) and the timer restarts; the damage is forgotten.
// BUG(original): OnNewHitW_2 gets an uninitialised stack point (dotd: the null vector).
void CKHkS08DragonCityGolem::ApplyPendingDamage(IKTime* clock) {
    const float dt = clock->m_afDeltaTime[IKTime::SCALABLE_GAME_TIME];
    for (uint32_t slot = 0; slot < 2; ++slot) {
        CKS08Damage* damage = m_unkC4[slot];
        if (damage == nullptr) continue;
        AccumulateDamage(ContinuousAmount(damage, dt), m_unkC4[slot], slot);
        if (m_unkD4[slot] == 0) {
            m_unkD4[slot] = 1;
            m_unkD8[slot] = 0.0f;
        } else {
            m_unkD8[slot] = m_unkD8[slot] + dt;
            if (m_unkD8[slot] >= 0.3f) {
                const CVector3 point{0.0f, 0.0f, 0.0f};
                OnNewHitW(static_cast<CKS08GameManager*>(g_pEngine->m_gameManager), static_cast<uint8_t>(slot), &point);
                m_unkD8[slot] = 0.0f;
            }
        }
        m_unkC4[slot] = nullptr;
    }
}

// 0x004d64c8 CKHkS08DragonCityGolem_ProcessDamageContacts_maybe (vt+0x120): every collision of the attack's volumes
// that has a contact set, with the golem's volume and the other one told apart by the owner, is tested: the other
// volume must deal damage (properties bit 3) through a damage without +0x08, on a volume of the attack whose hits count
// (+0x0c). A continuous damage (+0x0c) is kept for the hero's dragon; a one-shot one hits once per contact (the contact
// history +0x20 with the hero, or +0xc0 without an owner for a damage with +0x26): the hit explosion at the contact
// point turned toward the hero, the bonuses, a combo hit for a hero (0x25c2) and the damage accumulated for the hero's
// dragon. Every tested collision touches the history +0x20 (times -1000, TOC +0x6ad0), the unqualified ones twice
// when their first touch is new. Both histories age at the end.
void CKHkS08DragonCityGolem::ProcessContacts(IKTime* clock, CKGolemAttackCommon* attack) {
    static const CVector3 kAxisY = {0.0f, 1.0f, 0.0f};  // 0x00c50d40 (TOC +0x6ad4)
    for (uint32_t i = 0; i < attack->m_unk08Count; ++i) {
        IKBoundingVolume* volume = attack->m_apUnk08[i]->m_unk00;
        for (ICollision* c = static_cast<ICollision*>(volume->m_CollisionResList); c != nullptr; c = c->m_pNext) {
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
            CKGolemAttackCommon::Entry08* entry = nullptr;
            for (uint32_t k = 0; k < attack->m_unk08Count; ++k) {
                if (attack->m_apUnk08[k]->m_unk00 == own) entry = attack->m_apUnk08[k];
            }
            if ((other->m_ui16PropertiesFlags & 8u) == 0) continue;
            // DOTD: the owner of a damage volume with bit 3 is a hero (CKHkS08Hero) in LVL010; the original reads its
            // dragon index (+0x24 byte) whatever it is.
            CKHkS08Hero* hero = static_cast<CKHkS08Hero*>(other->m_pOwner);
            CKS08Damage* damage = static_cast<CKS08Damage*>(other->m_unk1c);
            if (entry != nullptr && damage != nullptr && damage->m_unk08 == 0 && entry->m_unk0c != 0) {
                bool hit = false;
                if (damage->m_unk0c != 0) {
                    m_unkC4[hero->GetDragonIndex()] = damage;  // 0x00361960
                } else if (damage->m_unk26 == 0) {
                    hit = ContactHistory_Touch(-1000.0f, -1000.0f, &m_unk20, other, hero) != 0;  // 0x0098f380
                    if (!hit) ContactHistory_Touch(-1000.0f, -1000.0f, &m_unk20, other, hero);
                } else {
                    hit = ContactHistory_Touch(-1000.0f, -1000.0f, &m_unkC0, other, nullptr) != 0;
                }
                if (hit) {
                    // KStub_Return1_4becc0 (the golem accepts every hit): the explosion and the bonuses.
                    const CVector3 contact = *c->GetWorldContactPoint();  // vt+0x20
                    const RwFrame* ownFrame = own->m_pRwFrame;
                    const RwFrame* heroFrame = static_cast<const CSGMovable*>(hero->m_pKGLObject)->m_pRwFrame;
                    float dy = heroFrame->ltm.pos.y - ownFrame->ltm.pos.y;
                    float dx = heroFrame->ltm.pos.x - ownFrame->ltm.pos.x;
                    float dz = heroFrame->ltm.pos.z - ownFrame->ltm.pos.z;
                    const float length = static_cast<float>(
                        c22spyro::MathSqrtf(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy))));  // 0x00010690
                    if (length != 0.0f) {
                        const float inverse = 1.0f / length;
                        dz = dz * inverse;
                        dx = dx * inverse;
                        dy = dy * inverse;
                    }
                    const CVector3 direction{dx, dy, dz};
                    SpawnFxAt(&contact, &direction);  // 0x004c2758
                    SpawnBonuses(&contact, &kAxisY);  // 0x004bed58
                    if (hero->IsKindOfClass(0x25c2) != 0) {
                        CKS08GameManager* manager = static_cast<CKS08GameManager*>(g_pEngine->m_gameManager);
                        const uint8_t dragon = hero->GetDragonIndex();
                        const CVector3 point = *c->GetWorldContactPoint();
                        OnNewHitW(manager, dragon, &point);  // OnNewHitW_2 0x004fe5f8
                    }
                    const float dt = clock->m_afDeltaTime[IKTime::SCALABLE_GAME_TIME];
                    const float amount = damage->m_unk0c != 0 ? dt * damage->m_unk04 : damage->m_unk04;
                    AccumulateDamage(amount, damage, hero->GetDragonIndex());
                }
            }
            ContactHistory_Touch(-1000.0f, -1000.0f, &m_unk20, other, hero);
        }
    }
    ContactHistory_Update(&m_unk20, clock);  // 0x0098f430
    ContactHistory_Update(&m_unkC0, clock);
}

// 0x004d6020 CKHkS08DragonCityGolem_GetNearestAimVolume_maybe (CKHkS08Hero_GetAimPointOnHook, from the hero's hot spot
// 5). The current phase of the phase manager (+0x30, CKGolemPhaseManager_GetCurrentPhase_maybe 0x4bd330): an attack
// phase (0x97cc, vt+0x88) with an attack (0x994c) searches its aim volumes; otherwise `out` is the "no point" (0x00c50da0
// = TOC +0x6abc) and the distance FLT_MAX (0x00c4acb8 +0x28 = TOC +0x6ab8).
// An attack phase's current attack: its volumes whose hits count (+0x0c), the distance from `from` to the volume's
// centre (the frame's LTM position) or, for a sphere (0x38b), to the point of its surface toward `from` (the
// direction normalised unless of length 0: Math_Sqrtf, 1.0 / length). The nearest one (fcmpu / bge: strictly nearer)
// gives `out` its centre and the result its squared distance from the centre (not from the surface point).
float CKHkS08DragonCityGolem::GetNearestAimVolume(CVector3* out, const CVector3* from) {
    static const CVector3 kNoPoint = {3.40282347e+38f, 3.40282347e+38f, 3.40282347e+38f};  // 0x00c50da0
    IKSerializable* phase = PhaseManager()->GetCurrentPhase();  // 0x004bd330
    CKGolemAttackCommon* attack = nullptr;
    if (phase != nullptr && phase->IsKindOfClass(0x97cc) != 0) {
        CKGolemPhaseAttack::Step* step = static_cast<CKGolemPhaseAttack*>(phase)->GetCurrentStep();  // vt+0x88
        if (step != nullptr && step->m_unk00 != nullptr && step->m_unk00->IsKindOfClass(0x994c) != 0) attack = step->m_unk00;
    }
    *out = kNoPoint;
    float best = 3.40282347e+38f;
    if (attack == nullptr) return best;
    for (uint32_t i = 0; i < attack->m_unk08Count; ++i) {
        CKGolemAttackCommon::Entry08* entry = attack->m_apUnk08[i];
        if (entry->m_unk0c == 0) continue;
        IKBoundingVolume* volume = entry->m_unk00;
        const float fx = from->x;
        const float fy = from->y;
        const float fz = from->z;
        const RwV3d& centre = volume->m_pRwFrame->ltm.pos;
        const float cz = centre.z;
        const float cx = centre.x;
        const float cy = centre.y;
        float distance;
        if (volume->IsKindOfClass(0x38b) == 0) {
            const float dy = cy - fy;
            distance = ppc::fmadds(cz - fz, cz - fz, ppc::fmadds(cx - fx, cx - fx, dy * dy));
        } else {
            const float radius = volume->m_fRadius;  // +0x20
            float vy = from->y - cy;
            float vx = from->x - cx;
            float vz = from->z - cz;
            const float length = static_cast<float>(c22spyro::MathSqrtf(ppc::fmadds(vz, vz, ppc::fmadds(vx, vx, vy * vy))));
            if (length != 0.0f) {
                const float inverse = 1.0f / length;
                vz = vz * inverse;
                vx = vx * inverse;
                vy = vy * inverse;
            }
            const float py = ppc::fmadds(vy, radius, cy) - from->y;
            const float px = ppc::fmadds(radius, vx, cx) - from->x;
            const float pz = ppc::fmadds(vz, radius, cz) - from->z;
            distance = ppc::fmadds(pz, pz, ppc::fmadds(px, px, py * py));
        }
        if (!(distance < best)) continue;
        const RwV3d& nearest = attack->m_apUnk08[i]->m_unk00->m_pRwFrame->ltm.pos;
        const float dy = nearest.y - from->y;
        const float dx = nearest.x - from->x;
        const float dz = nearest.z - from->z;
        out->x = nearest.x;
        out->y = nearest.y;
        out->z = nearest.z;
        best = ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy));
    }
    return best;
}

// 0x004d5f98 CKHkS08DragonCityGolem_DeletingDestructor (the destructor body; 0x004d5f20 DestructBody is a dead copy): the
// contact history's nodes (+0xc0) back to their pool (in front of the free list 0x00ceaa74), the list cleared, then
// CKHkGolem's destructor.
CKHkS08DragonCityGolem::~CKHkS08DragonCityGolem() {
    for (ContactHistoryNode* node = m_unkC0; node != nullptr;) {
        ContactHistoryNode* next = node->m_pNext;  // +0x14
        ContactHistory_FreeNode(node);
        node = next;
    }
    m_unkC0 = nullptr;
}
