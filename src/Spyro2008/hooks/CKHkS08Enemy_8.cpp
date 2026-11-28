// Reconstructed original translation unit: 0x291478-0x294b18 (GAME_TOC1, main_toc1), 28 functions, 26 live.
// Primary class: CKHkS08Enemy  key 0x26c2  category Hook  size 0x8f8  vtable 0xb22078
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x291478  CKHkS08Enemy_vfD4
//   [ ] 0x291480  CKHkS08Enemy_ReleaseAllElements_maybe  [dead]
//   [x] 0x2915e8  CKHkS08Enemy_DropShield
//   [x] 0x2916f0  CKHkS08Enemy_DetachWeapon_maybe
//   [x] 0x2917e0  CKHkS08Enemy_AttachRandomAccessories_maybe
//   [x] 0x291e60  CKHkS08Enemy_vfC8
//   [x] 0x291e88  CKHkS08Enemy_ResetRuntimeState_maybe
//   [x] 0x292008  StaticInitAndDestruction_292008  (the two file statics at the end)
//   [ ] 0x292038  _GLOBAL__D_292038
//   [ ] 0x292048  _GLOBAL__I_292048
//   [x] 0x292058  CKHkS08Enemy_ConstrainToGroundAndNavMesh_maybe
//   [ ] 0x292278  CKHkS08Enemy_ReleaseElement_maybe  [dead]
//   [x] 0x2923c8  CKHkS08Enemy_CanSpawnFromSquad_maybe
//   [x] 0x292710  CKHkS08Enemy_AttachRandomShield
//   [x] 0x292a10  CKHkS08Enemy_EquipWeapon_maybe
//   [x] 0x292b40  CKHkS08Enemy_AttachRandomWeapon
//   [x] 0x292e60  CKHkS08Enemy_Activate
//   [x] 0x2937c8  CKHkS08Enemy_SpawnAtPosition_maybe
//   [x] 0x293cb0  CKHkS08Enemy_Deactivate
//   [x] 0x294860  CKHkS08Enemy_Restart  (empty: the inherited IKUpdatable default)
//   [x] 0x294868  CKHkS08Enemy_Pause  (empty: the inherited IKHook default)
//   [x] 0x294870  CKHkS08Enemy_Resume  (empty: the inherited IKHook default)
//   [x] 0x294878  CKHkS08Enemy_InitMainStateMachine
//   [x] 0x294a50  CKHkS08Enemy_Stop  (IKHkEnemy_OnLevelExit_maybe only: empty)
//   [x] 0x294a78  CKHkS08Enemy_Start
//   [x] 0x294aa0  CKHkS08Enemy_PostLoad
//   [x] 0x294ac8  CKHkS08Enemy_RecursiveRegistration  (inherited: IKHkEnemy's (IKHook's))
//   [x] 0x294af0  CKHkS08Enemy_Destroy  (IKHkEnemy::Destroy)
#include "Spyro2008/hooks/CKHkS08Enemy.h"
#include "Spyro2008/misc/CKS08EnemyAbilityHost.h"
#include "k2000/logic/CKAbilityElement.h"

#include "k2000/core/Stub.h"

#include <cmath>
#include <cstring>

#include "Renderware/rwcore/RwCamera.h"
#include "Spyro2008/components/CKS08EnemyCpnt.h"
#include "Spyro2008/components/CKS08FightZoneCpnt.h"
#include "Spyro2008/groups/CKChoreoKey.h"
#include "Spyro2008/groups/CKGrpS08Enemy.h"
#include "Spyro2008/hooks/CKHkS08EnemyShared.h"
#include "k2000/scenegraph/CSGLeaf.h"
#include "k2000/misc/IKGrpEnemy.h"
#include "Renderware/rpprtstd/RpPrtStd.h"
#include "k2000/scenegraph/CParticlesNodeFx.h"
#include "Spyro2008/hooks/CKHkS08Egg.h"
#include "Spyro2008/hooks/CKHkS08Weapon.h"
#include "Spyro2008/hooks/CKHkS08Shield.h"
#include "k2000/cameras/CKSrvCamera.h"
#include "Spyro2008/logic/CKS08CarrierEnemy.h"
#include "Spyro2008/misc/CKHkS08TransportableBase.h"
#include "Spyro2008/logic/CKS08EnemyElement.h"
#include "Spyro2008/logic/memory/CKS08EnemyElementPool.h"
#include "crt/ppc_ops.h"
#include "crt/xatan.h"
#include "k2000/components/CKBonusData.h"
#include "k2000/components/CKEnemySectorCpnt.h"
#include "k2000/groups/CKGrpFightZone.h"
#include "k2000/groups/CKGrpSquad.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/logic/CKChoreography.h"
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/CSGBranch.h"
#include "k2000/services/CKSrvCollision.h"
#include "platform/log.h"
// 0x00291e88 CKHkS08Enemy_ResetRuntimeState_maybe
void CKHkS08Enemy::ResetRuntimeState() {
    ResetMovementState();  // 0x00277df8
    m_unk290 = 0;
    m_pLastGrabbingHero = 0;
    m_ui8HitByCount = 0;
    m_bPendingHit = 0;
    m_fStunGauge = 0;
    m_unk260 = 0;
    m_unk264 = 0;
    m_pGrabbingHero = 0;
    m_unk2a4 = 0;
    m_unk2a8 = 0;
    m_unk2ac = 0;
    for (uint32_t i = 0; i < 30; ++i) m_afAttackCooldowns[i] = 0;
    m_unk344 = 0;
    m_unk32c = 0;
    m_pTarget = nullptr;
    m_unk348 = 0;
    m_unk328 = 0;
    m_bitArray = m_bitArray & 0xfff8ffffu;
    m_unk35c = 0;
    m_unk358 = 0;
    // the zero vector 0x00c50d64 twice
    m_unk364 = 0.0f;
    m_unk36c = 0.0f;
    m_unk368 = 0.0f;
    m_unk370 = 0.0f;
    m_unk378 = 0.0f;
    m_unk374 = 0.0f;
    m_unk37c = m_v3Position.x;
    m_unk384 = m_v3Position.z;
    m_unk380 = m_v3Position.y;
    // the unit X vector 0x00c50d34 (TOC1 +0xf9c)
    m_unk388 = 1.0f;
    m_unk38c = 0.0f;
    m_unk390 = 0.0f;
    // The original stores a word at +0x394 (stw): its three high bytes 0, the low one (+0x397, the move mode
    // SteerGround passes) the value.
    m_unk394 = 0;
    m_unk395 = 0;
    m_unk396 = 0;
    m_unk397 = 1;
    m_unk398 = 0;
    m_PFCpnt.m_CharacterType.m_bits |= 0xf0u;
    m_unk1ee = 0;
}

// 0x00294aa0 CKHkS08Enemy_PostLoad
int32_t CKHkS08Enemy::PostLoad(int32_t type) {
    IKHkEnemy::PostLoad(type);  // 0x00277528
    return 1;
}

// 0x00294a78 CKHkS08Enemy_Start
void CKHkS08Enemy::Start() {
    IKHkEnemy::Start();  // 0x276f40, empty
}

// 0x00291e60 CKHkS08Enemy_vfC8: the base's (empty).
void CKHkS08Enemy::VfC8() {
    IKHkEnemy::VfC8();  // 0x00276f50
}

namespace {
// 0x00a70140 (TOC +0xf78): per enemy kind, the number of accessory slots (+0x00), of moving spheres (+0x78) and of
// particle nodes (+0x88).
constexpr uint8_t kDeactivateAccessories[9] = {3, 1, 5, 4, 5, 7, 9, 0, 4};
constexpr uint8_t kDeactivateSpheres[9] = {2, 3, 3, 2, 3, 3, 3, 3, 2};
constexpr uint8_t kDeactivateParticles[9] = {22, 22, 22, 22, 22, 22, 22, 22, 22};
}  // namespace

// 0x00293cb0 CKHkS08Enemy_Deactivate (vt+0xd0): IKHkEnemy's (UnregisterActive); the main state left (to 0xff); volume
// groups 0-2 off and +0x7cd set; the moving spheres released; the armour parts back under the enemy group's first +0x40
// node, hidden and free; the shield and the weapon dropped; the particle nodes stopped; the carried object and the
// carrier let go; the six trail ribbons stopped; the attack slot (+0x7d8, +0x891) released; the ability host deleted;
// the weapon holder (+0x838) stopped; kinds 5 / 6 leave the camera service's target list; the glow node (+0x88c) back
// under the dynamic scene root.
void CKHkS08Enemy::Deactivate() {
    IKHkEnemy::Deactivate();  // 0x0027a748 CKHkS08Enemy_UnregisterActive
    if (m_mainState == 7 && m_pLastGrabbingHero != nullptr) (void)m_pLastGrabbingHero->IsKindOfClass(0x25c2);  // vt+0x08, the answer unused
    if (m_mainState != 0xff) CallMainState(m_mainState, nullptr, 2, 0xff);
    m_mainState = 0xff;
    DisableVolumeGroup(0);  // vt+0xfc
    DisableVolumeGroup(1);
    DisableVolumeGroup(2);
    m_unk7cd = 1;
    const uint8_t kind = m_ui8EnemyClassType;
    for (uint32_t i = 0; i < kDeactivateSpheres[kind]; ++i) ReleaseDynSphere(static_cast<uint8_t>(i));  // vt+0x10c
    auto* parts = reinterpret_cast<CKS08EnemyElement**>(m_unk514.m_pBlock);
    for (uint32_t i = 0; i < kDeactivateAccessories[kind]; ++i) {
        CKS08EnemyElement* part = parts[i];
        if (part != nullptr) {
            CSGLeaf* node = static_cast<CSGLeaf*>(part->m_pNode);
            if (node->m_pParent != nullptr) {
                node->m_pParent->RemoveChild(node);  // vt+0x78
                const IKGrpEnemy* group = static_cast<const IKGrpEnemy*>(g_pEngine->m_gameManager->m_unk04[0]);
                static_cast<CSGBranch*>(group->m_vUnk40.m_pBlock[0])->AddChild(node);  // vt+0x70
                node->m_sgProperties = (node->m_sgProperties & ~4u) | 4u;
                part->m_inUse54 = 0;
            }
        }
        parts[i] = nullptr;
    }
    if (m_pHeldShield != nullptr) {
        DropShield();  // 0x002915e8
    }
    if (m_pHeldWeapon != nullptr) {
        // The weapon dropped: its node at its LTM (0x000d0be8), not in hand, under the dynamic scene root, no owner,
        // back in its pool (vt+0xc8), vt+0xcc (empty).
        CKHkS08Weapon* weapon = m_pHeldWeapon;
        CSGLeaf* node = static_cast<CSGLeaf*>(weapon->m_pKGLObject);
        node->SetLocalMatrix(&node->m_pRwFrame->ltm);  // 0x000d0be8
        weapon->m_inHandA8 = 0;
        if (node->m_pParent != nullptr) node->m_pParent->RemoveChild(node);      // vt+0x78
        static_cast<CSGBranch*>(g_pEngine->m_dynamicSceneRoot)->AddChild(node);  // vt+0x70
        weapon->m_pOwnerB4 = nullptr;
        m_pHeldWeapon = nullptr;
        weapon->ReturnToPool();  // vt+0xc8 0x002b1558
        weapon->VfCC();          // vt+0xcc
    }
    for (uint32_t i = 0; i < kDeactivateParticles[kind]; ++i) {
        CParticlesNodeFx* particles = static_cast<CParticlesNodeFx*>(m_apParticleNodeFx[i]);
        if (particles == nullptr) continue;
        particles->m_sgProperties &= 0xfff7fbffu;
        particles->m_pRpPrtStdEmitter->flag &= ~0x8u;  // rpPRTSTDEMITTERFLAGEMIT
        particles->StopEmitting();  // 0x000e6938
    }
    bool carrying = false;
    if (m_unk738 != nullptr) {
        static_cast<CKHkS08TransportableBase*>(m_unk738)->Vf138(0);  // vt+0x138
        carrying = static_cast<CKS08CarrierEnemy*>(m_pCarrierEnemy)->IsCarrying() != 0;  // 0x004c7c48
    }
    if (carrying) DropCarriedTransportableAtHand();  // 0x002945bc (then the carrier's drop too)
    static_cast<CKS08CarrierEnemy*>(m_pCarrierEnemy)->DropCarriedObject();  // vt+0x6c 0x004c82d0
    for (int32_t i = 0; i < 6; ++i) StopTrailRibbon(i);  // vt+0x11c
    if (m_unk891 != 0) {
        CKGrpS08Enemy* group = static_cast<CKGrpS08Enemy*>(g_pEngine->m_gameManager->m_unk04[0]);  // 0x00276f58
        group->ReleaseAttackSlot(static_cast<int32_t>(m_unk7d8), this);                           // 0x00267138
        m_unk7d8 = 0xffffffffu;
        m_unk891 = 0;
    }
    if (m_pAbilityHost != nullptr) {
        // 0x2942b4: the ability stopped, the host deleted.
        if (m_pSpecialAbility != nullptr) {
            m_unk819 = 0;
            m_unk818 = 0;
            static_cast<CKAbilityElement*>(m_pSpecialAbility)->Stop(0);  // vt+0x5c
        }
        delete m_pAbilityHost;  // vt+0x04
        m_pAbilityHost = nullptr;
    }
    if (m_pHeldWeapon == nullptr && m_unk838 != 0) {
        // The weapon dropped in state 0x21 (+0x838): back in its pool (vt+0xc8), vt+0xcc, its state machine (+0xb8)
        // left (phase 2 toward 0xff, no clock) and stopped.
        CKHkS08Weapon* dropped = m_unk838;
        dropped->ReturnToPool();  // vt+0xc8 0x002b1558
        dropped->VfCC();          // vt+0xcc
        const uint8_t old = dropped->m_unkBC;
        if (old != 0xff) dropped->CallState(static_cast<uint32_t*>(dropped->m_unkB8) + old * 2, nullptr, 2, 0xff);
        dropped->m_unkBC = 0xff;
    }
    if (static_cast<uint8_t>(kind - 5) <= 1) {
        // The camera service's target stack (+0xd08, count +0xdf8) loses the enemy's node (the last entry moved into
        // its place) and the stack-changed flag 0x800000 of +0x46c is set; nothing when the node is not stacked.
        CKSrvCamera* camera = static_cast<CKSrvCamera*>(g_pEngine->m_srvCamera);  // engine +0x70
        const uint32_t stacked = camera->m_ui32NbStacked;
        if (stacked != 0) {
            uint32_t i = 0;
            bool found = camera->m_aStack[0].m_pTarget == m_pKGLObject;
            while (!found) {
                i = (i + 1) & 0xffu;
                if (i >= stacked) break;
                found = camera->m_aStack[i].m_pTarget == m_pKGLObject;
            }
            if (found) {
                const uint32_t last = stacked - 1;
                camera->m_ui32NbStacked = last;
                if (last != i) camera->m_aStack[i] = camera->m_aStack[last];
                camera->m_baTemporaryFlags |= 0x800000u;
            }
        }
    }
    CSGLeaf* glow = static_cast<CSGLeaf*>(m_pGlowNode);
    if (glow->m_pParent != nullptr) glow->m_pParent->RemoveChild(glow);              // vt+0x78
    static_cast<CSGBranch*>(g_pEngine->m_dynamicSceneRoot)->AddChild(glow);          // TOC +0xf7c -> +0x14, vt+0x70
}


namespace {
// 0x00a70140 (TOC +0xf78): per enemy kind (IKHkEnemy::m_ui8EnemyClassType, 9 kinds) three word tables after 12 bytes:
// +0x0c the first accessory hot spot of the kind (AttachRandomAccessories), +0x30 the number of weapon pools
// (AttachRandomWeapon, CanSpawnFromSquad), +0x54 the number of shield pools (AttachRandomShield, CanSpawnFromSquad).
const uint32_t kAccessoryHotSpotBase[9] = {4, 4, 9, 9, 9, 10, 16, 0, 8};
using enemy::kWeaponPoolCount;  // CKHkS08EnemyShared.h
const uint32_t kShieldPoolCount[9] = {0, 0, 1, 0, 0, 1, 0, 0, 0};
// 0x00b00fc8 (TOC +0xfac): per kind, the enemy group's weapon pool indices (+0x180); kind 1's list is 0x00ceacfc, a
// zero word nothing writes. 0x00b00fa4 (TOC +0xfb0): the shield pool indices (+0x19c); kind 2's list is 0x00ceacf8 (0).
using enemy::kWeaponPools;  // CKHkS08EnemyShared.h
const uint32_t kShieldPools2[1] = {0};
const uint32_t kShieldPools5[1] = {1};
const uint32_t* const kShieldPools[9] = {nullptr, nullptr, kShieldPools2, nullptr, nullptr,
                                         kShieldPools5, nullptr, nullptr, nullptr};

// 0x00276f58 GetEnemyGroup: the game manager's enemy group (+0x04).
CKGrpS08Enemy* EnemyGroup() { return static_cast<CKGrpS08Enemy*>(g_pEngine->m_gameManager->m_unk04[0]); }

// 0x0025ab50 CKGrpSquad_GetFightZone: the squad's parent group (+0x1c).
CKGrpFightZone* SquadFightZone(IKSerializable* squad) {
    return static_cast<CKGrpFightZone*>(static_cast<CKGrpSquad*>(squad)->m_pParent);
}

// 0x002b3110 CKEnemySectorCpnt_GetAnimatedNode / 0x002b31e0 CKEnemySectorCpnt_GetHotSpot.
CSGLeaf* SectorAnimatedNode(IKSerializable* sector, uint32_t index) {
    return static_cast<CSGLeaf*>(static_cast<CKEnemySectorCpnt*>(sector)->m_apUnk04[index]);
}
CSGHotSpot* SectorHotSpot(IKSerializable* sector, uint32_t index) {
    return static_cast<CSGHotSpot*>(static_cast<CKEnemySectorCpnt*>(sector)->m_apUnk14[index]);
}

// 0x002649e8 CKChoreography_GetCurrentKey_maybe: the current key, null without keys.
CKChoreoKey* ChoreoCurrentKey(IKSerializable* choreography) {
    CKChoreography* c = static_cast<CKChoreography*>(choreography);
    if (c->m_apChoreoKey.m_ui32NbUsedElt == 0) return nullptr;
    return c->m_apChoreoKey.m_pBlock[c->m_ui8CurrentKey];
}

// A pool group's hook list (vt+0xb0 GetMemberListHead): its first hook. DOTD: a pool index beyond the enemy group's
// vector (the shield pools at +0x19c are filled by CKGrpS08Enemy_PostLoad, not ported) reads as an empty pool.
IKHook* PoolFirstHook(TVector<IKSerializable*, 1>& pools, uint32_t index) {
    if (index >= pools.m_ui32NbUsedElt) {
        static bool s_logged = false;
        if (!s_logged) {
            s_logged = true;
            DOTD_LOG("CKHkS08Enemy: enemy group pool %u missing (C2.7, CKGrpS08Enemy_PostLoad)", index);
        }
        return nullptr;
    }
    IKBaseGroup* pool = static_cast<IKBaseGroup*>(pools.m_pBlock[index]);
    return *reinterpret_cast<IKHook**>(pool->GetMemberListHead());
}

// DOTD: the enemy group's shield pools (+0x19c, filled by CKGrpS08Enemy_PostLoad: not ported). The vector is declared
// with word elements in CKGrpS08Enemy.h; its elements are the pool groups.
TVector<IKSerializable*, 1>& ShieldPools() {
    return reinterpret_cast<TVector<IKSerializable*, 1>&>(EnemyGroup()->m_vUnk19c);
}

// The rand draw scaled the original's way: (rand & 0xffff) / 65535.0f (TOC +0xf94) times count, truncated (fctidz).
uint32_t RandIndex(uint32_t count) {
    const float r = static_cast<float>(static_cast<double>(static_cast<uint32_t>(Rand_Int()) & 0xffffu)) / 65535.0f;
    const float n = static_cast<float>(static_cast<double>(count));
    return static_cast<uint32_t>(ppc::fctidz(r * n));
}

// The weapon / shield taken from a pool and hung under the hot spot `hotSpot` of the enemy's sector component
// (AttachRandomWeapon / AttachRandomShield / EquipWeapon): its node leaves its parent (vt+0x78) first.
void HangUnderHotSpot(IKHook* hook, IKSerializable* sector, uint32_t hotSpot) {
    CSGLeaf* node = static_cast<CSGLeaf*>(hook->m_pKGLObject);
    if (node != nullptr && node->m_pParent != nullptr) node->m_pParent->RemoveChild(node);  // vt+0x78
    SectorHotSpot(sector, hotSpot)->AttachVolume(node);  // CSGHotSpot_AttachVolume 0xce2b8
}
}  // namespace

CKS08EnemyCpnt* CKHkS08Enemy::Cfg() const { return static_cast<CKS08EnemyCpnt*>(m_pActiveEnemyCpnt); }

void CKHkS08Enemy::SwitchMainState(uint8_t next, IKTime* clock) {
    const uint8_t old = m_mainState;
    if (old != 0xff) CallMainState(old, clock, 2, next);
    m_mainState = next;
    CallMainState(next, clock, 1, old);
}

// 0x002917e0 CKHkS08Enemy_AttachRandomAccessories_maybe: per accessory slot of the kind, a random category (0 / 1 / 2:
// the pools +0x4f0 / +0x4fc / +0x508, allowed per enemy type by the fight zone component's byte vectors +0x70 / +0x7c /
// +0x88) is tried, then the next two in turn; with none allowed the slot's default pool (+0x4e4). From the chosen pool a
// random free element (+0x54) is taken: hung under the slot's hot spot and kept in +0x514. +0x898: a category pool won.
void CKHkS08Enemy::AttachRandomAccessories() {
    IKSerializable* sector = m_apEnemySectorCpnt[GetSectorIndex()];
    CKS08FightZoneCpnt* zone = SquadFightZone(m_pGroupSquad)->m_pFightZoneCpnt;
    m_unk898 = 0;
    for (uint32_t i = 0; i < m_unk4E4.m_ui32NbUsedElt; ++i) {
        const uint32_t type = m_unk1b4;
        TVector<IKSerializable*, 1>* const categories[3] = {&m_unk4F0, &m_unk4FC, &m_unk508};
        TVector<uint8_t, 1>* const allowed[3] = {&zone->m_vUnk70, &zone->m_vUnk7c, &zone->m_vUnk88};
        IKSerializable* pool = nullptr;
        bool any = false;
        for (uint32_t c = 0; c < 3; ++c) {
            if (allowed[c]->m_pBlock[type] != 0 && categories[c]->m_pBlock[i] != nullptr) any = true;
            if (any) break;
        }
        if (!any) {
            pool = m_unk4E4.m_pBlock[i];
            if (pool == nullptr) continue;
        } else {
            const uint32_t r = static_cast<uint32_t>(Rand_Int()) & 0xffffu;
            uint32_t c = ((r << 1) + r) >> 16;  // 0..2
            for (uint32_t attempt = 0; attempt < 3; ++attempt) {
                if (allowed[c]->m_pBlock[m_unk1b4] != 0 && categories[c]->m_pBlock[i] != nullptr) {
                    pool = categories[c]->m_pBlock[i];
                    break;
                }
                m_unk898 = 0;
                c = (c + 1) % 3;
            }
            if (pool == nullptr) {
                m_unk898 = 0;
                continue;
            }
            m_unk898 = 1;
        }
        CKS08EnemyElementPool* elements = static_cast<CKS08EnemyElementPool*>(pool);
        const uint32_t count = elements->m_count;
        if (count == 0) continue;
        const float r = static_cast<float>(static_cast<double>(static_cast<uint32_t>(Rand_Int()) & 0xffffu)) / 65535.0f;
        uint32_t index = static_cast<uint32_t>(ppc::fctidz(r * static_cast<float>(static_cast<double>(count - 1))));
        // The search from the drawn index: count tries, then the index after the last one once more.
        bool found = false;
        for (uint32_t tries = count;;) {
            if (elements->m_apElements[index]->m_inUse54 == 0) {
                found = true;
                break;
            }
            index = (index + 1) % count;
            if (--tries == 0) break;
        }
        if (!found && elements->m_apElements[index]->m_inUse54 != 0) continue;
        CKS08EnemyElement* element = elements->m_apElements[index];
        element->m_inUse54 = 1;
        CSGLeaf* node = static_cast<CSGLeaf*>(element->m_pNode);
        CSGLeaf* hung = nullptr;
        if (node != nullptr) {
            hung = node;
            if (node->m_pParent != nullptr) node->m_pParent->RemoveChild(node);  // vt+0x78
        }
        SectorHotSpot(sector, i + kAccessoryHotSpotBase[m_ui8EnemyClassType])->AttachVolume(hung);
        // BUG(original): with no node the flag store goes through a null pointer (+0x10).
        node->m_sgProperties &= 0xfffffffbu;
        m_unk514.m_pBlock[i] = element;
        element->AttachToOwner(pool);  // 0x0026b8b8
    }
}

// 0x00292710 CKHkS08Enemy_AttachRandomShield: the shield pools of the kind in order; from the first non-empty one a
// random shield (the draw past the end skips the pool) is taken (vt+0xc0, vt+0xc4) and hung under hot spot 4.
void CKHkS08Enemy::AttachRandomShield() {
    IKSerializable* sector = m_apEnemySectorCpnt[GetSectorIndex()];
    const uint32_t kind = m_ui8EnemyClassType;
    const uint32_t pools = kShieldPoolCount[kind];
    for (uint32_t j = 0; j < pools; ++j) {
        IKHook* first = PoolFirstHook(ShieldPools(), kShieldPools[kind][j]);
        uint32_t count = 0;
        for (IKHook* h = first; h != nullptr; h = h->m_pNextHook) ++count;
        if (count == 0) continue;
        const uint32_t index = RandIndex(count);
        if (index >= count) continue;
        IKHook* shield = first;
        for (uint32_t k = 0; k < index; ++k) shield = shield->m_pNextHook;
        static_cast<CKHkS08Shield*>(shield)->VfC0();  // vt+0xc0 0x002ac398 (empty)
        HangUnderHotSpot(shield, sector, 4);
        static_cast<CKHkS08Shield*>(shield)->TakeFromPool();  // vt+0xc4 0x002ac6e8
        m_pHeldShield = shield;
        return;
    }
    m_pHeldShield = nullptr;
}

// 0x00292a10 CKHkS08Enemy_EquipWeapon_maybe: a weapon picked up, hung under hot spot 2 and owned (+0xb4).
void CKHkS08Enemy::EquipWeapon(IKSerializable* weaponObject) {
    CKHkS08Weapon* weapon = static_cast<CKHkS08Weapon*>(weaponObject);
    IKSerializable* sector = m_apEnemySectorCpnt[GetSectorIndex()];
    HangUnderHotSpot(weapon, sector, 2);
    weapon->m_inHandA8 = 1;
    weapon->m_unkA9 = 0;
    weapon->SetEjected(0);  // 0x002b2bc0
    weapon->SetLanded(0);   // 0x002b2a70
    m_pHeldWeapon = weapon;
    weapon->m_pOwnerB4 = this;
}

// 0x00292b40 CKHkS08Enemy_AttachRandomWeapon: as the shield, from the weapon pools (hot spot 2, the weapon owned).
void CKHkS08Enemy::AttachRandomWeapon() {
    IKSerializable* sector = m_apEnemySectorCpnt[GetSectorIndex()];
    const uint32_t kind = m_ui8EnemyClassType;
    const uint32_t pools = kWeaponPoolCount[kind];
    for (uint32_t j = 0; j < pools; ++j) {
        IKHook* first = PoolFirstHook(EnemyGroup()->m_vUnk180, kWeaponPools[kind][j]);
        uint32_t count = 0;
        for (IKHook* h = first; h != nullptr; h = h->m_pNextHook) ++count;
        if (count == 0) continue;
        const uint32_t index = RandIndex(count);
        if (index >= count) continue;
        IKHook* hook = first;
        for (uint32_t k = 0; k < index; ++k) hook = hook->m_pNextHook;
        CKHkS08Weapon* weapon = static_cast<CKHkS08Weapon*>(hook);
        weapon->VfC0();  // vt+0xc0 0x2b0f00 (empty)
        HangUnderHotSpot(weapon, sector, 2);
        weapon->m_inHandA8 = 1;
        weapon->m_unkA9 = 0;
        weapon->TakeFromPool();  // vt+0xc4 0x2b12f8
        m_pHeldWeapon = weapon;
        weapon->m_pOwnerB4 = this;
        return;
    }
    m_pHeldWeapon = nullptr;
}

// 0x00292e60 CKHkS08Enemy_Activate: the enemy comes alive for a spawn: the kind parameters, animation slot 0, health
// and the random first-attack delay (one rand draw), accessories, the four state machines, the shield and the weapon
// (more draws), the carrier, the run-time fields, the glow node under hot spot 2; then, in a fight zone with eggs of
// this enemy type, the first egg that can take it (state 0).
void CKHkS08Enemy::Activate() {
    IKHkEnemy::Activate();  // 0x0027b590
    IKSerializable* sector = m_apEnemySectorCpnt[GetSectorIndex()];
    m_pActiveEnemyCpnt = m_pEnemyCpnt;
    m_bitArray = m_bitArray & 0xfd78f0ffu;
    ForceAnimSlot(0, 0, 0, 0);  // 0x00285b98
    m_bitArray = m_bitArray & 0xfffffdffu;
    CSGLeaf* node = SectorAnimatedNode(sector, 0);
    node->m_sgProperties = (node->m_sgProperties & 0xffffdffbu) | 0x2000u;
    CKS08EnemyCpnt* cfg = Cfg();
    m_fHealth = cfg->m_unkcc;
    const uint32_t r = static_cast<uint32_t>(Rand_Int()) & 0xffffu;
    m_unk290 = 0;
    m_pLastGrabbingHero = 0;
    m_pGrabbingHero = 0;
    m_unk1f4 = (static_cast<float>(static_cast<double>(r)) / 65535.0f) * cfg->m_unkc0;  // TOC +0xf94
    AttachRandomAccessories();  // 0x002917e0
    if (g_pEngine->m_gameManager->VfC4() != 0 && m_unk898 == 0) m_fHealth = m_fHealth + m_fHealth;
    cfg = Cfg();
    m_unk52c = 0;
    m_unk528 = static_cast<uint32_t>(cfg->m_unk198);
    m_unk530 = 0.0f;
    m_unk67c = 0.0f;
    m_fDisarmGauge = 0.0f;
    m_fTimeScale = 1.0f;  // TOC +0xf90
    m_unk204 = 1.0f;
    m_unk254 = cfg->m_unk1f0;
    m_unk6b0 = 0.0f;
    m_fFireGauge = 0.0f;
    m_unk6bc = 0;
    m_fPoisonGauge = 0.0f;
    m_fShadowGauge = 0.0f;
    m_fIceGauge = 0.0f;
    m_fFearGauge = 0.0f;
    m_fWindGauge = 0.0f;
    m_fElectricGauge = 0.0f;
    m_unk6fc = 0;
    m_unk708 = 0;
    m_unk709 = 0;
    m_unk724 = 0;
    InitMainStateMachine();         // 0x00294878
    InitAwarenessStateMachine();    // 0x002884b8
    InitHitReactionStateMachine();  // 0x00297250
    InitAuxStateMachine();          // 0x0029dd38
    m_pClaimedWeapon = 0;
    m_pHeldWeapon = nullptr;
    Cfg()->m_unk330 = 0;
    m_unk728 = 0.0f;
    if (m_ui8EnemyClassType == 5 || m_ui8EnemyClassType == 2) {
        AttachRandomShield();  // 0x00292710
        if (m_pHeldShield == nullptr && m_unk730 != 0) m_bitArray |= 8u;
    } else {
        m_pHeldShield = nullptr;
    }
    m_unk838 = 0;
    AttachRandomWeapon();  // 0x00292b40
    if (m_pHeldWeapon == nullptr && m_unk730 != 0) m_bitArray |= 8u;
    m_unk738 = nullptr;
    static_cast<CKS08CarrierEnemy*>(m_pCarrierEnemy)->Reset();  // vt+0x68 0x004c9720
    m_unk794 = 0.0f;
    m_unk744 = 0;
    m_unk748 = 0;
    m_unk74c = 0;
    m_unk750 = 0;
    m_unk774 = 1.0f;
    m_pAbilityHost = nullptr;
    m_unk78c = 0.0f;
    m_unk7b4 = m_ui8EnemyClassType == 8 ? 1 : 0;
    m_unk72c = 0;
    m_unk7c4 = 1;
    m_unk7bc = 0;
    m_unk7b8 = 0;
    m_unk714 = 0.0f;
    m_unk7b5 = 0;
    m_unk7b6 = 0;
    m_unk7b7 = 0;
    CKBonusData* bonus = static_cast<CKBonusData*>(Cfg()->m_pUnk4b4);
    for (uint32_t i = 0; i < bonus->m_count; ++i) bonus->m_pEntries[i].m_unk18 = 0xffffffffu;
    // BUG(original): +0x7c8 gets an uninitialised stack word (0x70(r1)); DOTD stores 0.
    m_unk7c8 = 0;
    m_pCurrentAttack = 0;
    m_unk7cc = 0;
    cfg = Cfg();
    m_unk718 = cfg->m_unkf4;
    m_unk6f8 = 1.0f;
    m_unk7d8 = 0xffffffffu;
    m_unk7dc = 1;
    m_unk7f9 = 0;
    m_unk804 = 0.0f;
    m_pLastAttacker = nullptr;
    m_unk7dd = 0;
    m_unk7e0 = 0.0f;
    m_unk76c = 0;
    if (bonus->m_count > 1) {
        // entry 0 + 0x28: the second entry's +0x08 word
        m_unk804 = cfg->m_unkcc / static_cast<float>(static_cast<double>(bonus->m_pEntries[1].m_unk08));
    }
    m_unk800 = 0.0f;
    m_unk834 = 0;
    m_unk818 = 0;
    m_unk819 = 0;
    m_unk83c = 0.0f;  // the zero vector 0x00c50d64 (TOC +0xf98)
    m_unk840 = 0.0f;
    m_unk844 = 0.0f;
    m_pFreezeMeshPopFx = nullptr;
    m_pBurrowMeshPopFx = 0;
    m_unk84c = 0.0f;
    m_unk868 = 0;
    m_pBurrowDustFx = 0;
    m_unk86d = 0;
    m_unk86e = 0;
    m_unk86f = 0;
    m_unk870 = 0.0f;
    m_unk874 = 0;
    m_pPendingDamage = 0;
    m_unk891 = 0;
    m_unk7a8 = 0.0f;
    m_unk7ac = 0.0f;
    m_unk7b0 = 0.0f;
    m_unk79c = 0.0f;
    m_unk7a0 = 0.0f;
    m_unk7a4 = 0.0f;
    CSGLeaf* glow = static_cast<CSGLeaf*>(m_pGlowNode);
    m_unk89c = 0;
    m_unk8a0 = 0;
    m_unk8a4 = 0.0f;
    if (glow->m_pParent != nullptr) glow->m_pParent->RemoveChild(glow);  // vt+0x78
    GetHotSpot(2)->AttachVolume(glow);  // 0x002892e8, CSGHotSpot_AttachVolume 0xce2b8
    m_unk8b0 = 0;
    m_unk890 = 0;
    m_unk8a8 = 0;
    m_unk8b4 = 0.0f;
    m_unk8b8 = EnemyGroup()->m_unk268[4];  // +0x278
    m_unk8e4 = 0.0f;
    m_unk8e8 = 0.0f;
    m_unk8ec = 0.0f;
    m_unk8f0 = 0.0f;
    if (m_ui8EnemyClassType == 1 || m_ui8EnemyClassType == 8) {
        m_PFCpnt.m_CharacterType.m_bits = (m_PFCpnt.m_CharacterType.m_bits & 0xfffffff8u) | 4u;
    }
    // The eggs of the fight zone (its component's +0x30, vt+0x70 the count; vt+0x74 / vt+0x78 +0xa8).
    CKGrpFightZone* fightZone = SquadFightZone(m_pGroupSquad);
    CKS08FightZoneCpnt* zone = fightZone->m_pFightZoneCpnt;
    const uint32_t eggs = zone->m_vUnk30.m_ui32NbUsedElt;
    m_pSpawnEgg = nullptr;
    if (eggs != 0) {
        int32_t waiting = 0;  // the enemies the eggs of this type still hold (+0x54 - +0x58)
        for (uint32_t i = 0; i < eggs; ++i) {
            CKHkS08Egg* egg = static_cast<CKHkS08Egg*>(zone->m_vUnk30.m_pBlock[i]);
            if (egg->m_unk40 == m_unk1b4 && (egg->m_unk30 >> 24) != 0) {
                waiting += static_cast<int32_t>(egg->m_unk54 - egg->m_unk58);
            }
        }
        for (uint32_t i = 0; i < eggs; ++i) {
            CKHkS08Egg* egg = static_cast<CKHkS08Egg*>(zone->m_vUnk30.m_pBlock[i]);
            if ((egg->m_unk30 >> 24) == 0 || egg->m_unk60 >= egg->m_unk54 || egg->m_unk40 != m_unk1b4) continue;
            if (static_cast<int32_t>(zone->m_unka8) < 1) {
                CKGrpFightZone::SEntry4c& entry = fightZone->m_vUnk4c.m_pBlock[m_unk1b4];
                const int32_t left = static_cast<int32_t>(static_cast<int16_t>(entry.m_unk06)) -
                                     static_cast<int32_t>(entry.m_unk08);  // lhz +8: the type's spawned count
                if (left > waiting) continue;
            }
            egg->AssignEnemy(this);  // 0x00473630
            if (egg->m_unk64 == 0) egg->m_unk60 += 1;
            SwitchMainState(0, nullptr);
            if (static_cast<int32_t>(zone->m_unka8) > 0 && egg->m_unk64 == 0) {
                zone->m_unka8 = static_cast<uint32_t>(static_cast<int32_t>(zone->m_unka8) - 1);  // vt+0x78 (vt+0x74 - 1)
            }
            break;
        }
    }
    m_unk684 = 0.0f;
}

// 0x002923c8 CKHkS08Enemy_CanSpawnFromSquad_maybe: whether the squad may spawn this enemy now. A zone component of
// mode 0, 3 or 4 caps the active enemies (its +0x3c and the squad choreography key's position count); an enemy that
// needs equipment (+0x730) needs a non-empty weapon pool, and for kinds 2 / 5 a shield pool (enough alone).
uint8_t CKHkS08Enemy::CanSpawnFromSquad(IKSerializable* squadObject) {
    CKGrpSquad* squad = static_cast<CKGrpSquad*>(squadObject);
    const uint32_t kind = m_ui8EnemyClassType;
    const uint32_t weaponPools = kWeaponPoolCount[kind];
    CKS08FightZoneCpnt* zone = SquadFightZone(squad)->m_pFightZoneCpnt;
    const uint32_t mode = zone->m_unk04;
    if (mode <= 4 && ((1u << mode) & 0x19u) != 0) {
        if (!(EnemyGroup()->m_ui32NbActiveEnemies < zone->m_unk3c)) return 0;
        const uint32_t active = EnemyGroup()->m_ui32NbActiveEnemies;
        CKChoreoKey* key = ChoreoCurrentKey(squad->m_vStates.m_pBlock[squad->m_unk55].m_pUnk34);
        if (!(key->m_asPos.m_ui32NbUsedElt > active)) return 0;
    }
    if (m_unk730 == 0) return 1;
    uint8_t hasWeapon = 0;
    for (uint32_t j = 0; j < weaponPools; ++j) {
        uint32_t count = 0;
        for (IKHook* h = PoolFirstHook(EnemyGroup()->m_vUnk180, kWeaponPools[kind][j]); h != nullptr; h = h->m_pNextHook) {
            ++count;
        }
        if (count != 0) hasWeapon = 1;
    }
    uint32_t result = 1;
    if (m_ui8EnemyClassType == 5 || m_ui8EnemyClassType == 2) {
        const uint32_t shieldPools = kShieldPoolCount[kind];
        for (uint32_t j = 0; j < shieldPools; ++j) {
            uint32_t count = 0;
            for (IKHook* h = PoolFirstHook(ShieldPools(), kShieldPools[kind][j]); h != nullptr;
                 h = h->m_pNextHook) {
                ++count;
            }
            if (count != 0) return 1;
        }
        result = 0;
    }
    return hasWeapon != 0 ? static_cast<uint8_t>(result & 1u) : 0;
}

// 0x002937c8 CKHkS08Enemy_SpawnAtPosition_maybe: teleported (IKHkEnemy's slot), placed at the spawn point or near the
// hero as the squad state says, the previous / reference positions set, the life flags' top bits from `flags`, the
// ground constraint unless flags, the node moved and turned to `direction`, the yaw (+0x154) from it, main state 0.
void CKHkS08Enemy::SpawnAtPosition(const CVector3* position, const CVector3* direction, uint32_t flags) {
    CVector3 positionCopy = *position;
    CVector3 directionCopy = *direction;
    IKHkEnemy::SpawnAtPosition(&positionCopy, &directionCopy, flags & 0xffu);  // 0x00277c90
    CKGrpSquad* squad = static_cast<CKGrpSquad*>(m_pGroupSquad);
    const CKGrpSquad::SState& state = squad->m_vStates.m_pBlock[squad->m_unk55];
    const uint8_t useSpawnPoint =
        reinterpret_cast<const uint8_t*>(squad->m_vUnkc0.m_pBlock)[m_unk1b4] != 0 ? state.m_unk3a : state.m_unk39;
    if (useSpawnPoint != 0) {
        m_v3Position = *position;
    } else {
        m_v3Position = PickAttackSpotNearHero();  // 0x00280190
        if (m_v3Position.x == 0.0f && m_v3Position.y == 0.0f && m_v3Position.z == 0.0f) m_v3Position = *position;
    }
    m_unk140 = m_v3Position.x;
    m_unk144 = m_v3Position.y;
    m_unk148 = m_v3Position.z;
    m_unk37c = m_unk1c4;
    m_unk380 = m_unk1c8;
    m_unk384 = m_unk1cc;
    m_unk388 = m_unk1d0;
    m_unk38c = m_unk1d4;
    m_unk390 = m_unk1d8;
    uint32_t bits1f0;  // +0x1f0 read as a word here (lwz)
    std::memcpy(&bits1f0, &m_unk1f0, sizeof(bits1f0));
    // The original stores a word at +0x394 (stw): its three high bytes 0, the low one (+0x397, the move mode
    // SteerGround passes) the value.
    m_unk394 = 0;
    m_unk395 = 0;
    m_unk396 = 0;
    m_unk397 = static_cast<uint8_t>(bits1f0 & 3u);
    m_unk398 = m_unk1ed;
    m_unk38c = 0.0f;  // TOC +0xfdc
    const float length = std::sqrt(ppc::fmadds(m_unk390, m_unk390, ppc::fmadds(m_unk388, m_unk388, m_unk38c * m_unk38c)));
    if (length != 0.0f) {
        const float k = 1.0f / length;  // TOC +0xf90
        m_unk390 = k * m_unk390;
        m_unk388 = k * m_unk388;
        m_unk38c = k * m_unk38c;
    }
    const uint32_t b = flags & 0xffu;
    m_bitArray = (m_bitArray & 0xf3ffffffu) | ((b << 26) & 0xfc000000u);
    if (b == 0) ConstrainToGroundAndNavMesh();  // vt+0xe0
    CSGMovable* movable = static_cast<CSGMovable*>(m_pKGLObject);
    RwFrame* frame = movable->m_pRwFrame;
    frame->modelling.pos.x = m_v3Position.x;
    frame->modelling.pos.y = m_v3Position.y;
    frame->modelling.pos.z = m_v3Position.z;
    frame->modelling.flags &= 0xfffdffffu;
    RwFrame_MarkDirty(frame);
    static const CVector3 kUp = {0.0f, 1.0f, 0.0f};  // TOC +0xfd0: 0x00c50d40
    movable->SetOrientationFromAtUp(direction, &kUp);  // 0x000d0918
    float x = direction->x;
    float z = direction->z;
    const float planar = std::sqrt(ppc::fmadds(z, z, ppc::fmadds(x, x, 0.0f)));
    if (planar != 0.0f) {
        const float k = 1.0f / planar;
        z = z * k;
        x = x * k;
    }
    float yaw;
    bool outside;  // NaN counts as outside (the compare branches of the original)
    if (z < 0.0f) {
        outside = z < -1.0f;  // TOC +0xfa4
    } else {
        outside = !(z <= 1.0f);
    }
    if (outside) {
        yaw = z < 0.0f ? 3.14159274f : 0.0f;  // TOC +0xfd4 pi / +0xfdc 0
    } else {
        yaw = crt::Acosf(z);  // TocBridge_Math_Acosf 0x98e1a0
        if (!(x >= 0.0f)) yaw = 6.28318548f - yaw;  // TOC +0xfd8
    }
    m_fYaw = yaw;  // +0x154 the yaw
    SwitchMainState(0, nullptr);
}

// 0x00292058 CKHkS08Enemy_ConstrainToGroundAndNavMesh_maybe: IKHkEnemy's constraint (not in state 0x11); when it fails
// an enemy with life flag 0x10 dies (state 0x15). Too far above the ground (contact dH >= the kind's +0x188) outside
// states 0xff / 1 and kinds 1 / 8, the enemy goes back to its previous position. Returns the constraint's success.
uint32_t CKHkS08Enemy::ConstrainToGroundAndNavMesh() {
    const uint8_t entry = m_mainState;
    uint32_t ok = 0;
    if (entry != 0x11) {
        ok = 1;
        if ((IKHkEnemy::ConstrainToGroundAndNavMesh() & 0xffu) == 0) ok = 0;  // 0x00278330
    }
    if (ok == 0 && (m_bitArray & 0x10u) != 0) {
        const uint8_t state = m_mainState;
        if (state != 0xff && state != 0x15) SwitchMainState(0x15, nullptr);
    }
    if (m_GrdContDatasInOut.m_fdH >= Cfg()->m_unk188 && entry != 0xff && entry != 1 && m_ui8EnemyClassType != 1 &&
        m_ui8EnemyClassType != 8) {
        m_v3Position.x = m_unk140;
        m_v3Position.y = m_unk144;
        m_v3Position.z = m_unk148;
    }
    return ok;
}

// 0x00294878 CKHkS08Enemy_InitMainStateMachine: 40 rows of virtual descriptors (rows 9, 16, 17 and 20 are not written),
// no state yet.
void CKHkS08Enemy::InitMainStateMachine() {
    static const uint32_t kSlots[40] = {0x14c, 0x150, 0x154, 0x158, 0x15c, 0x160, 0x164, 0x19c, 0x1a0, 0,
                                        0x1a4, 0x168, 0x16c, 0x170, 0x174, 0x178, 0,     0,     0x17c, 0x180,
                                        0,     0x188, 0x18c, 0x190, 0x194, 0x198, 0x1a8, 0x1ac, 0x1b0, 0x1b4,
                                        0x1b8, 0x1bc, 0x1c0, 0x1c4, 0x1c8, 0x1cc, 0x1d0, 0x1d4, 0x1d8, 0x1dc};
    for (uint32_t i = 0; i < 40; ++i) {
        if (kSlots[i] == 0) continue;
        m_aMainStates[i][0] = kSlots[i] + 1;
        m_aMainStates[i][1] = 0;
    }
    m_pMainStates = &m_aMainStates[0][0];
    m_mainState = 0xff;
    m_mainStateCount = 0x28;
}

// 0x002915e8 CKHkS08Enemy_DropShield: a shield (+0x524) falls: the shield-drop FX, the sound 0x2a, its node off its
// parent (vt+0x78), back in its pool (vt+0xc8), vt+0xcc; +0x524 cleared.
void CKHkS08Enemy::DropShield() {
    if (m_pHeldShield == nullptr) return;
    SpawnShieldDropFx();  // 0x0028cec0
    PlaySound(0x2a, 0, m_pKGLObject);  // 0x002795c0
    CKHkS08Shield* shield = static_cast<CKHkS08Shield*>(m_pHeldShield);
    CSGLeaf* node = static_cast<CSGLeaf*>(shield->m_pKGLObject);
    if (node->m_pParent != nullptr) {
        node->m_pParent->RemoveChild(node);  // vt+0x78
        shield = static_cast<CKHkS08Shield*>(m_pHeldShield);
    }
    shield->ReturnToPool();  // vt+0xc8 0x002ac900
    static_cast<CKHkS08Shield*>(m_pHeldShield)->VfCC();  // vt+0xcc 0x002ac3a0 (empty)
    m_pHeldShield = nullptr;
}

// 0x002916f0 CKHkS08Enemy_DetachWeapon_maybe: the held weapon's node keeps its place (its local matrix the LTM), out of
// the hand, off its parent (vt+0x78) and under the dynamic scene root (vt+0x70), unowned; +0x520 cleared.
void CKHkS08Enemy::DetachWeapon() {
    if (m_pHeldWeapon == nullptr) return;
    CSGLeaf* node = static_cast<CSGLeaf*>(m_pHeldWeapon->m_pKGLObject);
    node->SetLocalMatrix(&node->m_pRwFrame->ltm);  // 0x000d0be8
    m_pHeldWeapon->m_inHandA8 = 0;
    CSGLeaf* again = static_cast<CSGLeaf*>(m_pHeldWeapon->m_pKGLObject);
    if (again->m_pParent != nullptr) again->m_pParent->RemoveChild(again);  // vt+0x78
    static_cast<CSGBranch*>(g_pEngine->m_dynamicSceneRoot)->AddChild(again);  // TOC +0xf7c -> +0x14, vt+0x70
    m_pHeldWeapon->m_pOwnerB4 = nullptr;
    m_pHeldWeapon = nullptr;
}

// The carried transportable (+0x738) dropped on the ground under the hand point (+0x8e4), inlined in Deactivate
// (0x002945bc) and State21_Dying (0x0029f928): the point probed into the enemy's contact pair (GroundProbePoints
// 0x00196540; status 0 lowers it by the contact's dH, 1..2 raise it), the transportable's node unhooked from its parent
// (keeping its world matrix, SetLocalMatrix 0x000d0be8 with the frame's LTM) and put under the dynamic scene root at the
// point, then the reference cleared. The callers then let the carrier drop its object (vt+0x6c) as well.
void CKHkS08Enemy::DropCarriedTransportableAtHand() {
    CVector3 point{m_unk8e4, m_unk8e8, m_unk8ec};
    static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision)
        ->GroundProbePoints(&m_GrdContDatasIn, &m_GrdContDatasInOut, &point.x, 1);  // 0x00196540
    const int32_t status = static_cast<int32_t>(m_GrdContDatasInOut.m_eContactStatus);
    if (status == 0) {
        point.y = point.y - m_GrdContDatasInOut.m_fdH;
    } else if (status > 0 && status <= 2) {
        point.y = point.y + m_GrdContDatasInOut.m_fdH;
    }
    CKHkS08TransportableBase* transportable = static_cast<CKHkS08TransportableBase*>(m_unk738);
    CSGLeaf* node = static_cast<CSGLeaf*>(transportable->m_pKGLObject);
    if (node->m_pParent != nullptr) {
        node->SetLocalMatrix(&node->m_pRwFrame->ltm);  // 0x000d0be8
        node->m_pParent->RemoveChild(node);            // vt+0x78
    }
    static_cast<CSGBranch*>(g_pEngine->m_dynamicSceneRoot)->AddChild(node);  // vt+0x70
    RwFrame* frame = node->m_pRwFrame;
    frame->modelling.pos.z = point.z;
    frame->modelling.pos.x = point.x;
    frame->modelling.pos.y = point.y;
    frame->modelling.flags &= 0xfffdffffu;
    RwFrame_MarkDirty(frame);         // 0x00010698
    node->ForceWorldMatrixUpdate();   // vt+0x50
    m_unk738 = nullptr;
}

// 0x00292008 StaticInitAndDestruction_292008: two file statics (0x00ceacf0, 0x00ceacf4) set to -1.0f. Nothing in the game
// reads them (their only references are the initialiser's TOC entries).
namespace {
[[maybe_unused]] float s_unkceacf0 = -1.0f;
[[maybe_unused]] float s_unkceacf4 = -1.0f;
}  // namespace
