// CKGrpS08BonusPool.cpp - reconstructed original translation unit 0x5af6a8-0x5b0c58 (GAME_TOC2, main_toc2), 37 functions, 31 live.
// Primary owner: CKGrpS08BonusPool (not a registered class)
// Other owners: CKGrpBonus (6), CKGrpBonusPool (1), RegisterCKGrpS08BonusPoolClass (1), UpdateCKGrpS08BonusPool (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x5af6a8  CKGrpS08BonusPool_Destroy  (the Delete factory: DOTD_DECLARE_FACTORIES(CKGrpS08BonusPool))
//   [ ] 0x5af6f8  CKGrpS08BonusPool_Construct  [dead]
//   [ ] 0x5af760  CKGrpS08BonusPool_Construct_2  [dead]
//   [x] 0x5af7c8  CKGrpS08BonusPool_vfB8  (returns 0x3d: undeclared slot, see CKGrpS08BonusPool.h)
//   [x] 0x5af7d0  CKGrpS08BonusPool_vf120
//   [x] 0x5af7f8  CKGrpS08BonusPool_vf128  (returns 0: undeclared slot, see CKGrpS08BonusPool.h)
//   [x] 0x5af800  CKGrpBonusPool_PlayCollectFx_maybe
//   [x] 0x5afa90  CKGrpS08BonusPool_UpdateBonuses_maybe
//   [x] 0x5afab8  CKGrpS08BonusPool_vf1C  (MessageProc)
//   [x] 0x5afb10  CKGrpS08BonusPool_PostLoad  (= CKGrpBonusPool::PostLoad, inherited)
//   [x] 0x5afb38  CKGrpS08BonusPool_LevelReset  (RecursiveRegistration)
//   [x] 0x5afc00  CKGrpS08BonusPool_ClearReferences  (inherited: CKGrpBonusPool_Destroy)
//   [x] 0x5afc28  CKGrpS08BonusPool_DestroyArray  (vtable-only destructors (implicit here))
//   [ ] 0x5afcd0  RegisterCKGrpS08BonusPoolClass
//   [ ] 0x5afd58  _GLOBAL__D_5afd58
//   [ ] 0x5afd68  _GLOBAL__I_5afd68
//   [x] 0x5afd78  CKGrpS08BonusPool_CanHeroCollect_maybe
//   [x] 0x5affd0  CKGrpS08BonusPool_ApplyBonusToHero_maybe
//   [x] 0x5b0540  UpdateCKGrpS08BonusPool  (empty: IKBaseGroup's Update)
//   [x] 0x5b0548  CKGrpS08BonusPool_vf78  (empty: IKBaseGroup's Resume)
//   [x] 0x5b0550  CKGrpS08BonusPool_vf68  (empty: IKBaseGroup's Stop)
//   [x] 0x5b0558  CKGrpS08BonusPool_vf70  (empty: IKBaseGroup's Pause)
//   [x] 0x5b0560  CKGrpS08BonusPool_vf50
//   [x] 0x5b0568  CKGrpS08BonusPool_CreateArray
//   [x] 0x5b0640  CKGrpS08BonusPool_Create
//   [ ] 0x5b06c0  CKGrpS08BonusPool_LaunchBonusProjectile_maybe  [dead]
//   [x] 0x5b08b0  CKGrpS08BonusPool_Load
//   [ ] 0x5b0970  CKGrpS08BonusPool_Save
//   [ ] 0x5b0a30  CKGrpS08BonusPool_Destructor_2  [dead]
//   [x] 0x5b0a58  CKGrpS08BonusPool_DeletingDestructor  (the implicit destructor + delete)
//   [x] 0x5b0ab0  CKGrpS08BonusPool_Destructor  (vtable only (implicit))
//   [x] 0x5b0ad8  CKGrpBonus_Destroy  (the Delete factory: DOTD_DECLARE_FACTORIES(CKGrpBonus))
//   [x] 0x5b0b28  CKGrpBonus_vfB8  (returns 1: undeclared slot, see CKGrpBonus.h)
//   [ ] 0x5b0b30  CKGrpBonus_FindChildByKey2C_maybe  [dead]
//   [ ] 0x5b0b88  CKGrpBonus_SetChildrenFlag80_maybe  [dead]
//   [x] 0x5b0bc8  CKGrpBonus_ResetRuntime
//   [x] 0x5b0c30  CKGrpBonus_PostLoad  (header)
//
//   [ ] 0x9cc010  CKGrpS08BonusPool_IsKindOf  [inline]
//   [x] 0x9cc070  CKGrpS08BonusPool_GetClassGroup  [inline]
//   [x] 0x9cc078  CKGrpS08BonusPool_GetClassId  [inline]
//   [ ] 0x9cc080  CKGrpS08BonusPool_vfCC  [inline]
#include "Spyro2008/memory/CKGrpS08BonusPool.h"

#include "Renderware/rwcore/RwCamera.h"
#include "Spyro2008/groups/IKGrpHero.h"
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "Spyro2008/logic/CKS08GameManager.h"
#include "Spyro2008/logic/CKS08GameStructure.h"
#include "Spyro2008/ui/CKHkS08Bonus.h"
#include "crt/ppc_ops.h"
#include "k2000/fx/IKFx.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/misc/Engine.h"
#include "k2000/logic/IKFxData.h"
#include "k2000/logic/fx/CKExplosionNodeFx.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/services/CKSrvFx.h"
#include "k2000/services/ICollisionMesh.h"
#include "k2000/ui/CKGrpBonus.h"

// 0x005b08b0 CKGrpS08BonusPool_Load
int32_t CKGrpS08BonusPool::Load(IKFile* file, int32_t type) {
    CKGrpBonusPool::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) IKFile_ReadRef(file, &m_pUnk6c);
    return 1;
}

// 0x005b0bc8 CKGrpBonus_ResetRuntime: CKGrpBonus::Start (k2000/ui/CKGrpBonus.cpp).

namespace {
// The upgrade points the four levels of a dragon cost (the records +0xc48.. for Spyro, +0xc84.. for Cynder; summed as
// the original: [3] + [2] + [1] + [0]).
uint32_t UpgradeCap(const CKS08GameManager* manager, uint32_t dragon) {
    const CKS08GameManager::SRecord* costs = dragon == 0 ? manager->m_aSpyroUpgradeCosts : manager->m_aCynderUpgradeCosts;
    return costs[3].m_unk8 + costs[2].m_unk8 + costs[1].m_unk8 + costs[0].m_unk8;
}
CKS08GameStructure* StatsOf(CKS08GameManager* manager) { return static_cast<CKS08GameStructure*>(manager->m_gameStructure); }
}  // namespace

// 0x005af800 CKGrpBonusPool_PlayCollectFx_maybe
void CKGrpS08BonusPool::PlayCollectFx(const CVector3* position) {
    IKFx* fx = static_cast<CKSrvFx*>(g_pEngine->m_srvFx)->AcquireFx(static_cast<IKFxData*>(m_pUnk6c), this);  // inlined
    if (fx == nullptr) return;
    CKExplosionNodeFx* explosion = static_cast<CKExplosionNodeFx*>(fx);
    explosion->SetTranslation(position, this);  // 0x001b66e8
    explosion->Trigger(this, 0);                // 0x001b82a8
    explosion->ReleaseReservation(this);        // vt+0x54
}

// 0x005afd78 CKGrpS08BonusPool_CanHeroCollect_maybe (vt+0x124)
uint8_t CKGrpS08BonusPool::CanHeroCollect(IKSerializable* heroObject) {
    CKHkS08Hero* hero = static_cast<CKHkS08Hero*>(heroObject);
    if (hero->IsPlayerControlled() == 0) {  // 0x00362af0
        const uint32_t type = m_ui32BonusType;
        if (type == 1 || type == 2) {
            CKS08GameManager* manager = static_cast<CKS08GameManager*>(g_pEngine->m_gameManager);
            const uint8_t dragon = hero->GetDragonIndex();  // 0x00361960
            const int32_t partner = dragon == 0 ? 1 : 0;   // (dragon - 1) >> 63
            uint32_t own, other;
            if (type == 1) {
                own = manager->GetDragonHealth(dragon);  // 0x004fd9c8
                other = manager->GetDragonHealth(partner);
            } else {
                own = manager->GetDragonMana(dragon);  // 0x004fd7c8
                other = manager->GetDragonMana(partner);
            }
            if (!(own < other)) return 0;
            const uint32_t capacity = type == 1 ? manager->GetDragonHealthCapacity(partner)  // 0x004fd940
                                                : manager->GetDragonManaCapacity(partner);   // 0x004fd740
            const float threshold = static_cast<float>(static_cast<double>(capacity)) * 0.65f;  // TOC2 -0x6630
            if (static_cast<float>(static_cast<double>(other)) < threshold) return 0;
        } else if (type >= 3 && type <= 6) {
            return 0;
        }
    }
    if (m_ui32BonusType - 7u <= 2u && hero->GetDragonIndex() != 0) return 0;
    if (m_ui32BonusType - 10u <= 2u) return hero->GetDragonIndex() == 1 ? 1 : 0;
    return 1;
}

// 0x005affd0 CKGrpS08BonusPool_ApplyBonusToHero_maybe (vt+0x12c; a jump table on the type)
void CKGrpS08BonusPool::ApplyBonusToHero(IKSerializable* heroObject, IKSerializable* bonusObject) {
    if (heroObject->IsKindOfClass(0x3642) == 0) return;  // vt+0x08
    const uint32_t type = m_ui32BonusType;
    CKS08GameManager* manager = static_cast<CKS08GameManager*>(g_pEngine->m_gameManager);
    if (type > 0xc) return;
    CKHkS08Hero* hero = static_cast<CKHkS08Hero*>(heroObject);
    CKHkS08Bonus* bonus = static_cast<CKHkS08Bonus*>(bonusObject);
    switch (type) {
    case 1: {  // health
        const uint32_t value = manager->GetBonusValue(1);  // 0x004f6b10
        manager->RestoreDragonHealth(hero->GetDragonIndex(), static_cast<int32_t>(value), 0);  // 0x004fdef8
        return;
    }
    case 2: {  // mana
        const uint32_t value = manager->GetBonusValue(2);
        manager->RestoreDragonMana(hero->GetDragonIndex(), static_cast<int32_t>(value), 0);  // 0x004fdca8
        return;
    }
    case 3:
    case 4:
    case 5: {  // gems: upgrade points; once the dragon is full the gem goes on to the partner
        const uint8_t dragon = hero->GetDragonIndex();
        const uint32_t value = manager->GetBonusValue(type);
        // fcfid, frsp, fctidz: the value through a float.
        const uint32_t points = static_cast<uint32_t>(ppc::fctidz(static_cast<float>(static_cast<double>(value))));
        const uint32_t total = GetDragonTotalUpgradePoints(StatsOf(manager), dragon);  // 0x0050f050
        if (UpgradeCap(manager, dragon) > total) {
            manager->AddDragonUpgradePoints(dragon, points);  // 0x005008c8 (a tail call of 0x500418)
            return;
        }
        manager->AddDragonUpgradePoints(dragon, 0);
        if (bonus->m_bSharedCopy != 0) return;
        IKGrpHero* heroes = static_cast<IKGrpHero*>(manager->m_unk04[1]);
        IKSerializable* partner = heroes->m_apHeros[dragon == 0 ? 1 : 0];  // 0x002ca080 GetHeroByDragonIndex
        const RwFrame* frame = static_cast<CSGMovable*>(bonus->m_pKGLObject)->m_pRwFrame;
        IKSerializable* shared = static_cast<CKGrpBonus*>(manager->m_unk04[3])->SpawnBonusObject(
            type, reinterpret_cast<const CVector3*>(&frame->modelling.pos), 1);  // 0x005b0df8
        if (shared != nullptr) {
            static const CVector3 kAxisY = {0.0f, 1.0f, 0.0f};  // 0x00c50d40
            static_cast<CKHkS08Bonus*>(shared)->VfE4(&kAxisY, partner);  // vt+0xe4
            return;
        }
        manager->AddDragonUpgradePoints(static_cast<CKHkS08Hero*>(partner)->GetDragonIndex(), points);
        return;
    }
    case 7:
    case 10: {  // a health shard
        const uint8_t dragon = type == 7 ? 0 : 1;
        manager->RefreshDragonStatDisplays(dragon, 1, 1);  // 0x005022b0
        manager->RefreshHealthShardHud(dragon, 1);         // 0x005032d0
        return;
    }
    case 8:
    case 11: {  // a mana shard
        const uint8_t dragon = type == 8 ? 0 : 1;
        manager->RefreshDragonStatDisplays(dragon, 1, 1);
        manager->RefreshManaShardHud(dragon, 1);  // 0x00502ca0
        return;
    }
    case 9:
    case 12: {  // the shared points (the game structure's +0x80): Spyro (9) or Cynder (12) up to his cap, the rest to the other
        CKS08GameStructure* stats = StatsOf(manager);
        uint32_t first = stats->m_dwSharedBonusPoints;
        const uint32_t dragon = type == 9 ? 0u : 1u;
        const uint32_t total = GetDragonTotalUpgradePoints(stats, static_cast<int32_t>(dragon));
        const uint32_t cap = UpgradeCap(manager, dragon);
        uint32_t second = 0;
        if (!(cap > first + total)) {
            first = cap - total;
            second = StatsOf(manager)->m_dwSharedBonusPoints - first;
        }
        if (m_ui32BonusType == 9) {
            manager->AddDragonUpgradePoints(0, first);
            manager->AddDragonUpgradePoints(1, second);
        } else {
            manager->AddDragonUpgradePoints(1, first);
            manager->AddDragonUpgradePoints(0, second);
        }
        StatsOf(manager)->SaveCheckpointSnapshot();  // 0x0050ed60
        manager->RefreshDragonStatDisplays(0, 1, 1);
        manager->RefreshDragonStatDisplays(1, 1, 1);
        return;
    }
    default:  // 0, 6
        return;
    }
}

// 0x005afab8 CKGrpS08BonusPool_vf1C (vt+0x1c)
// 0x005af7d0 CKGrpS08BonusPool_vf120: a ground (a CGround: ICollisionMesh's properties +0x38) with none of the bits
// 0x1c; 0 without one.
int32_t CKGrpS08BonusPool::Vf120(IKSerializable* ground) {
    if (ground == nullptr) return 0;
    return (static_cast<ICollisionMesh*>(ground)->m_ui16PropertiesFlags & 0x1cu) == 0 ? 1 : 0;
}

int32_t CKGrpS08BonusPool::MessageProc(uint16_t message, void* data) {
    const int32_t result = CKGrpBonusPool::MessageProc(message, data);
    if (result == 3) return 3;
    if (result == 2) return 2;
    return result != 0 ? 1 : 0;  // the branch-free (|r| - 1) sign test
}

// 0x005afb38 CKGrpS08BonusPool_LevelReset (vt+0x24)
void CKGrpS08BonusPool::RecursiveRegistration(int32_t type) {
    CKGrpBonusPool::RecursiveRegistration(type);
    if (static_cast<uint32_t>(type - 4) <= 3u) return;
    g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);  // vt+0x24
    m_pUnk6c->RecursiveRegistration(type);
}
