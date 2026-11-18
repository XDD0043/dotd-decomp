// CKHkTransportableObjectSpawner.cpp - reconstructed original translation unit 0x4a8688-0x4ac108 (GAME_TOC1, main_toc1), 45 functions, 39 live.
// Primary class: CKHkTransportableObjectSpawner  key 0x3042  category Hook  size 0x78  vtable 0xb28920
// Other owners: CKHkS08TransportableBase (5), CKHkS08TransportableKey (2), CKGrpTransportableObject (1), KBase3002 (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x4a8688  FUN_004a8688  [dead]
//   [x] 0x4a8700  CKHkTransportableObjectSpawner_ApplyStatePreset_maybe
//   [ ] 0x4a8730  RegisterCKHkTransportableObjectSpawnerClass
//   [ ] 0x4a87a8  _GLOBAL__I_4a87a8
//   [x] 0x4a87b8  CKHkTransportableObjectSpawner_SetDefaultState
//   [x] 0x4a87f0  CKHkTransportableObjectSpawner_IsPlayerHeroInRange_maybe
//   [ ] 0x4a8988  CKGrpTransportableObject_SortEntries_maybe  [dead]
//   [x] 0x4a89c8  CKHkTransportableObjectSpawner_Resume  (empty / no effect: inherited)
//   [x] 0x4a89f0  CKHkTransportableObjectSpawner_Pause  (empty / no effect: inherited)
//   [x] 0x4a8a18  CKHkTransportableObjectSpawner_Stop  (header)
//   [x] 0x4a8a40  CKHkTransportableObjectSpawner_GetInfo
//   [x] 0x4a8a90  CKHkTransportableObjectSpawner_MessageProc
//   [ ] 0x4a8b80  CKHkTransportableObjectSpawner_Save
//   [x] 0x4a8ba8  CKHkTransportableObjectSpawner_RecursiveRegistration  (the actor base's (IKHook's): inherited)
//   [x] 0x4a8bd0  CKHkTransportableObjectSpawner_Construct  [dead]
//   [ ] 0x4a8c40  CKHkTransportableObjectSpawner_Construct_2  [dead]
//   [x] 0x4a8cb0  CKHkTransportableObjectSpawner_DeleteArray
//   [x] 0x4a8d58  CKHkTransportableObjectSpawner_Destroy
//   [ ] 0x4a8de8  CKHkTransportableObjectSpawner_LevelResetEntryObjects_maybe  [dead]
//   [ ] 0x4a8e78  CKHkTransportableObjectSpawner_SaveSpawnEntries_maybe  [dead]
//   [x] 0x4a8fc8  CKHkTransportableObjectSpawner_OnDeactivate
//   [x] 0x4a9230  CKHkTransportableObjectSpawner_Restart
//   [x] 0x4a9510  CKHkTransportableObjectSpawner_OnActivate
//   [x] 0x4a9950  CKHkTransportableObjectSpawner_Start
//   [x] 0x4a9b08  CKHkTransportableObjectSpawner_LoadSpawnEntries_maybe
//   [x] 0x4a9d08  CKHkTransportableObjectSpawner_BaseDestructor  (= the header's destructor)
//   [x] 0x4a9da8  CKHkTransportableObjectSpawner_DeletingDestructor  (= the header's destructor)
//   [x] 0x4a9e58  CKHkTransportableObjectSpawner_Destructor  (header)
//   [x] 0x4a9ef8  CKHkTransportableObjectSpawner_PostLoad  (empty / no effect: inherited)
//   [x] 0x4a9f80  CKHkTransportableObjectSpawner_TrySpawn_maybe
//   [x] 0x4aa490  CKHkTransportableObjectSpawner_TrySpawnOntoReceiver_maybe
//   [x] 0x4aad40  CKHkTransportableObjectSpawner_CreateArray
//   [x] 0x4aae38  CKHkTransportableObjectSpawner_Create
//   [x] 0x4aaeb8  CKHkTransportableObjectSpawner_Load
//   [x] 0x4ab368  CKHkTransportableObjectSpawner_CanSpawnNow_maybe
//   [x] 0x4ab500  CKHkTransportableObjectSpawner_CanSpawnAtTime_maybe
//   [x] 0x4ab6d0  CKHkTransportableObjectSpawner_Update
//   [x] 0x4abfb0  CKHkS08TransportableBase_3002_maybe_GetOwnerSpawner_maybe  (CKHkS08TransportableBase.h)
//   [x] 0x4abfb8  CKHkS08TransportableBase_3002_maybe_SetOwnerSpawner_maybe
//   [x] 0x4abfc0  CKHkS08TransportableBase_3002_maybe_Update  (empty / no effect: inherited)
//   [x] 0x4abfe8  CKHkS08TransportableKey_BaseResume_maybe  (empty / no effect: inherited)
//   [x] 0x4ac010  CKHkS08TransportableKey_BasePause_maybe  (empty / no effect: inherited)
//   [x] 0x4ac038  CKHkS08TransportableBase_3002_maybe_OnLevelExit  (CKHkS08TransportableBase.h, Stop: empty)
//   [x] 0x4ac060  CKHkS08TransportableBase_3002_maybe_ResetRuntime
//   [x] 0x4ac0c8  KBase3002_PostLoad
//
//   [x] 0x9c5210  CKHkTransportableObjectSpawner_IsKindOfClass  [inline]
//   [x] 0x9c5268  CKHkTransportableObjectSpawner_GetClassType  [inline]
//   [x] 0x9c5270  CKHkTransportableObjectSpawner_GetClassID  [inline]
#include "k2000/hooks/CKHkTransportableObjectSpawner.h"

#include "Renderware/rpmatfx/RpMatFX.h"
#include "crt/ppc_ops.h"
#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/Mat4.h"
#include "Spyro2008/misc/CKHkS08TransportableBase.h"
#include "k2000/fx/IKFx.h"
#include "k2000/groups/CKGrpTransportableObject.h"
#include "k2000/scenegraph/CSGLeaf.h"
#include "k2000/scenegraph/CSGBranch.h"
#include "k2000/scenegraph/CSGSectorRoot.h"
#include "k2000/hooks/CKHkPressionStone.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/logic/CKLevel.h"
#include "k2000/logic/CKSector.h"
#include "k2000/logic/CKParticlesEffectFxData.h"
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/misc/Engine.h"
#include "k2000/services/CKSrvCollision.h"
#include "k2000/services/CKSrvFx.h"
#include "k2000/system/IKTime.h"
#include "k2000/hooks/GroundContact.h"
#include "crt/Ps3Qsort.h"
#include "Renderware/rwcore/RwCamera.h"
#include "Spyro2008/groups/IKGrpHero.h"
#include "Spyro2008/hooks/CKHkS08Hero.h"

#include <cfloat>

namespace {

// The CVector3 globals the Load passes (initialised at run time; their live values, as in
// CLightComponent.cpp and CKExplosionFxData.cpp).
const CVector3 kVectorAxisZ = {0.0f, 0.0f, 1.0f};  // 0x00c50d4c
const CVector3 kVectorAxisY = {0.0f, 1.0f, 0.0f};  // 0x00c50d40
// 0x00c50da0 (StaticInitAndDestruction_11578): FLT_MAX x3, the "no point" vector (TOC +0x62d8 / +0x4e24).
const CVector3 kNoPoint = {FLT_MAX, FLT_MAX, FLT_MAX};

// 0x004a8660 CKGrpTransportableObject_CompareNullsLast_maybe (the qsort comparator at TOC +0x62cc): -1 when the first is
// set and the second null, else 1 (never 0: BUG(original), equal elements compare unequal; PS3 qsort's order is kept by
// Ps3Qsort).
int CompareNullsLast(const void* a, const void* b) {
    if (*static_cast<void* const*>(a) == nullptr || *static_cast<void* const*>(b) != nullptr) return 1;
    return -1;
}

IKGrpHero* HeroGroup() { return static_cast<IKGrpHero*>(g_pEngine->m_gameManager->m_unk04[1]); }  // engine +0x8c -> +0x08

CSGLeaf* NodeOf(IKSerializable* object) { return static_cast<CSGLeaf*>(static_cast<IKHook*>(object)->m_pKGLObject); }

// A node's frame modelling position set (the identity flag 0x20000 cleared) and the frame marked dirty (RwFrame_MarkDirty
// 0x10698), as the transportable code inlines it.
void SetNodePosition(CSGLeaf* node, float x, float y, float z) {
    RwFrame* frame = node->m_pRwFrame;
    frame->modelling.pos.x = x;
    frame->modelling.pos.y = y;
    frame->modelling.pos.z = z;
    frame->modelling.flags &= 0xfffdffffu;
    RwFrame_MarkDirty(frame);
}

// The inlined RwMatrixSetIdentity on the stack (flags 0x20003, TOC +0x62d4 = 1.0) given to CSGMovable_SetLocalMatrix_maybe.
void SetNodeIdentityLocal(CSGLeaf* node) {
    RwMatrix m;
    m.right.x = 1.0f;
    m.right.y = 0.0f;
    m.right.z = 0.0f;
    m.flags = 0x20003u;
    m.up.x = 0.0f;
    m.up.y = 1.0f;
    m.up.z = 0.0f;
    m.pad1 = 0;
    m.at.x = 0.0f;
    m.at.y = 0.0f;
    m.at.z = 1.0f;
    m.pad2 = 0;
    m.pos.x = 0.0f;
    m.pos.y = 0.0f;
    m.pos.z = 0.0f;
    m.pad3 = 0;
    node->SetLocalMatrix(&m);  // 0x000d0be8
}

// The class-specific recycle step of TrySpawn / TrySpawnOntoReceiver: a weight (0xc5) or power bucket (0xc3) gets vt+0x18c,
// then vt+0x108 and back into the group's pool by class id (ReleaseObject).
void RecycleLiveObject(CKGrpTransportableObject* group, IKSerializable* object) {
    CKHkS08TransportableBase* item = static_cast<CKHkS08TransportableBase*>(object);
    if (item->GetClassID() == 0xc5) item->Vf18C();  // vt+0x18 / +0x18c
    if (item->GetClassID() == 0xc3) item->Vf18C();
    item->Vf108();
    group->ReleaseObject(object);  // 0x004a7ce0
}

}  // namespace

// 0x00426be8 CarryTarget_GetGroundedPlacementPoint_maybe (unit CKHkPressionStone.cpp): the ground under the stone's node
// (GroundProbePoints with height 2, masks {1, 2}); on the stone's own ground (+0x6c) the node's world position plus the
// contact's projection, else the "no point" vector (0x00c50da0).
CVector3 CarryTarget_GetGroundedPlacementPoint(IKSerializable* target) {
    CKHkPressionStone* stone = static_cast<CKHkPressionStone*>(target);
    CGroundContactDatasIn in;
    in.m_fDeltaMax = 2.0f;      // TOC +0x4e20
    in.m_fObjectHeight = 2.0f;
    in.m_MasksOfGrdForTest[0] = 1;
    in.m_MasksOfGrdForTest[1] = 2;
    CGroundContactDatasInOut contact;  // ground 0, face -1, status 3, sector 0
    const RwV3d& at = FrameLtm(NodeOf(stone)->m_pRwFrame)->pos;
    static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision)->GroundProbePoints(&in, &contact, &at.x, 1);
    if (contact.m_pGround != stone->m_apUnk6C[0]) return kNoPoint;
    const RwV3d& pos = FrameLtm(NodeOf(stone)->m_pRwFrame)->pos;
    return {pos.x + contact.m_ProjectionOnGround.x, pos.y + contact.m_ProjectionOnGround.y,
            pos.z + contact.m_ProjectionOnGround.z};
}

// 0x004a87f0 CKHkTransportableObjectSpawner_IsPlayerHeroInRange_maybe. The spawn point is read for every hero (the node's
// LTM position, else the spawn matrix's); a hero counts when it is player-controlled and d^2 < range^2 (fmadds), or the
// range is 0.
uint8_t CKHkTransportableObjectSpawner::IsPlayerHeroInRange() const {
    IKGrpHero* group = HeroGroup();
    for (uint32_t i = 0; static_cast<uint32_t>(group->GetHeroCount()) > i; ++i) {  // 0x002ca038
        CKHkS08Hero* hero = static_cast<CKHkS08Hero*>(group->m_apHeros[i & 0xffu]);  // 0x002ca080
        CVector3 at;
        if (m_pKGLObject == nullptr) {
            at = m_pMatrix->m_pos;
        } else {
            const RwV3d& p = FrameLtm(static_cast<CSGLeaf*>(m_pKGLObject)->m_pRwFrame)->pos;
            at = {p.x, p.y, p.z};
        }
        if (hero->IsPlayerControlled() == 0) continue;  // 0x00362af0
        const float range = m_unk74;
        const float r2 = range * range;
        const RwV3d& h = FrameLtm(static_cast<CSGLeaf*>(hero->m_pKGLObject)->m_pRwFrame)->pos;
        const float dy = at.y - h.y;
        const float dx = at.x - h.x;
        const float dz = at.z - h.z;
        const float d2 = ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy));
        if (d2 < r2 || range == 0.0f) return 1;
    }
    return 0;
}

// 0x004ab368 CKHkTransportableObjectSpawner_CanSpawnNow_maybe: a hero in range, nothing spawned, the interval elapsed,
// and under the count (or recycling, +0x68).
uint8_t CKHkTransportableObjectSpawner::CanSpawnNow() const {
    if (IsPlayerHeroInRange() == 0) return 0;
    if (m_unk28 != nullptr || !(m_unk50 <= m_fSpawnTimer)) return 0;
    if (m_unk4c <= m_ui32SpawnCount) return m_unk68;
    return 1;
}

// 0x004ab500 CKHkTransportableObjectSpawner_CanSpawnAtTime_maybe: the same with the entry's timer.
uint8_t CKHkTransportableObjectSpawner::CanSpawnAtTime(const SpawnEntry* entry) const {
    if (IsPlayerHeroInRange() == 0) return 0;
    if (!(m_unk50 <= entry->m_unk4)) return 0;
    if (m_unk4c <= m_ui32SpawnCount) return m_unk68;
    return 1;
}

// 0x004ab6d0 CKHkTransportableObjectSpawner_Update. The live list loses the transportables that left their state machine
// (vt+0x110 == 0) and is sorted nulls last. A spawner with a node runs per spawn entry: an entry's transportable that is
// carried (vt+0x100) goes into the first free live slot, gets vt+0x128 with 0 and the entry is free again (its timer
// cleared); without spawn entries (or without a node) the spawned transportable does the same, and the spawn timer
// restarts at 0. Then, when spawning is on (+0x24): with a node, each free entry spawns (TrySpawn) when a hero is in range,
// its timer reached the interval and the count allows it, else its timer advances; without entries or a node, nothing
// spawned yet: the same with the spawner's timer and TrySpawnOntoReceiver.
void CKHkTransportableObjectSpawner::Update(IKTime* clock) {
    // 0x003f6e68 WorldObjectBase_Update_Nop (empty).
    for (uint32_t i = 0; i < m_vUnk2c.m_ui32NbUsedElt; ++i) {
        CKHkS08TransportableBase* object = static_cast<CKHkS08TransportableBase*>(m_vUnk2c.m_pBlock[i]);
        if (object != nullptr && object->Vf110() == 0) m_vUnk2c.m_pBlock[i] = nullptr;  // vt+0x110
    }
    Ps3Qsort(m_vUnk2c.m_pBlock, m_vUnk2c.m_ui32NbUsedElt, 4, CompareNullsLast);
    const float dt = clock->m_afDeltaTime[0];

    // The first free live slot gets `object` (none free: dropped).
    auto keepLive = [this](IKSerializable* object) {
        for (uint32_t i = 0; i < m_vUnk2c.m_ui32NbUsedElt; ++i) {
            if (m_vUnk2c.m_pBlock[i] == nullptr) {
                m_vUnk2c.m_pBlock[i] = object;
                return;
            }
        }
    };
    bool spawnedPath = m_pKGLObject == nullptr || m_vSpawnEntries.m_ui32NbUsedElt == 0;
    if (!spawnedPath) {
        for (uint32_t i = 0; i < m_vSpawnEntries.m_ui32NbUsedElt; ++i) {
            SpawnEntry* entry = m_vSpawnEntries.m_pBlock[i];
            CKHkS08TransportableBase* object = static_cast<CKHkS08TransportableBase*>(entry->m_unk8);
            if (object == nullptr || object->Vf100() == 0) continue;  // vt+0x100
            keepLive(object);
            static_cast<CKHkS08TransportableBase*>(entry->m_unk8)->Vf128(0);  // vt+0x128
            entry->m_unk8 = nullptr;
            entry->m_unk4 = 0.0f;  // the word 0
        }
    } else if (m_unk28 != nullptr && static_cast<CKHkS08TransportableBase*>(m_unk28)->Vf100() != 0) {
        keepLive(m_unk28);
        static_cast<CKHkS08TransportableBase*>(m_unk28)->Vf128(0);
        m_unk28 = nullptr;
        m_fSpawnTimer = 0.0f;  // TOC +0x62c8
    }

    if (m_unk24 == 0) return;
    if (m_pKGLObject != nullptr && m_vSpawnEntries.m_ui32NbUsedElt != 0) {
        for (uint32_t i = 0; i < m_vSpawnEntries.m_ui32NbUsedElt; ++i) {
            SpawnEntry* entry = m_vSpawnEntries.m_pBlock[i];
            if (entry->m_unk8 != nullptr) continue;
            // With no hero in range the entry's timer advances too (the inlined range test jumps to the timer step).
            if (IsPlayerHeroInRange() != 0 && !(entry->m_unk4 < m_unk50) &&
                (m_ui32SpawnCount < m_unk4c || m_unk68 != 0)) {
                TrySpawn(entry);
            } else {
                entry->m_unk4 = entry->m_unk4 + dt;
            }
        }
        return;
    }
    if (m_unk28 != nullptr) return;
    if (IsPlayerHeroInRange() != 0 && m_unk28 == nullptr && m_unk50 <= m_fSpawnTimer &&
        (m_ui32SpawnCount < m_unk4c || m_unk68 != 0)) {
        TrySpawnOntoReceiver();
        return;
    }
    m_fSpawnTimer = m_fSpawnTimer + dt;
}

// 0x004a9f80 CKHkTransportableObjectSpawner_TrySpawn_maybe. The entry's timer restarts. Under the count (or not recycling)
// the count goes up; at the count, recycling: a free live slot lets the spawn go on, otherwise every live transportable
// that is not carried (vt+0x100) and in its state machine (vt+0x110) goes back to the pool (the list re-sorted after each);
// none: no spawn. Then a pooled transportable is placed (vt+0x128 with 1), its node hung under the entry's hot spot with an
// identity local matrix and shown, moved so that its own hot spot (vt+0x118) sits on the entry's, and kept by the entry.
void CKHkTransportableObjectSpawner::TrySpawn(SpawnEntry* entry) {
    entry->m_unk4 = 0.0f;
    if (m_ui32SpawnCount < m_unk4c || m_unk68 == 0) {
        m_ui32SpawnCount += 1;
    } else {
        const uint32_t count = m_vUnk2c.m_ui32NbUsedElt;
        if (count == 0) return;
        bool full = true;
        for (uint32_t i = count; i != 0; --i) {
            if (m_vUnk2c.m_pBlock[i - 1] == nullptr) {
                full = false;
                break;
            }
        }
        if (full) {
            bool recycled = false;
            for (uint32_t i = 0; i < m_vUnk2c.m_ui32NbUsedElt; ++i) {
                CKHkS08TransportableBase* object = static_cast<CKHkS08TransportableBase*>(m_vUnk2c.m_pBlock[i]);
                if (object->Vf100() == 0 && object->Vf110() != 0) {
                    recycled = true;
                    RecycleLiveObject(static_cast<CKGrpTransportableObject*>(m_unk64), object);
                    m_vUnk2c.m_pBlock[i] = nullptr;
                    Ps3Qsort(m_vUnk2c.m_pBlock, m_vUnk2c.m_ui32NbUsedElt, 4, CompareNullsLast);
                }
            }
            if (!recycled) return;
        }
    }
    CKHkS08TransportableBase* object =
        static_cast<CKHkS08TransportableBase*>(static_cast<CKGrpTransportableObject*>(m_unk64)->TakePooledObject(m_unk3c));
    if (object == nullptr) return;
    object->Vf128(1);
    CSGLeaf* node = NodeOf(object);
    if (node->m_pParent != nullptr) node->m_pParent->RemoveChild(node);  // vt+0x78
    CSGHotSpot* spot = static_cast<CSGHotSpot*>(entry->m_pUnk0);
    spot->AttachVolume(node);  // 0x000ce2b8
    node = NodeOf(object);
    node->m_sgProperties &= 0xfffffffbu;
    SetNodeIdentityLocal(node);
    if (object->Vf118() != nullptr) {
        const CVector3 at = spot->m_v3RelativePosition;
        const CSGHotSpot* own = object->Vf118();
        SetNodePosition(NodeOf(object), at.x - own->m_v3RelativePosition.x, at.y - own->m_v3RelativePosition.y,
                        at.z - own->m_v3RelativePosition.z);
    }
    entry->m_unk8 = object;
}

// 0x004aa490 CKHkTransportableObjectSpawner_TrySpawnOntoReceiver_maybe. The spawn timer restarts. Under the count (or not
// recycling) the count goes up; at the count with no free live slot, the first live transportable that can go is
// recycled (no receiver: not carried, in its state machine, +0x69 set and not marked (vt+0x148): back to the pool; with a
// receiver: vt+0x140 (in its pool) frees its slot), the list re-sorted; none: no spawn. A pooled transportable then goes
// onto the receiver when the receiver's ground has a placement point (moved there by its hot spot, vt+0x134, marked with
// vt+0x144); otherwise it is placed (vt+0x128 with 1) under the spawner's sector root at the spawn point (less its hot
// spot), shown, and its state machine started (vt+0x10c).
void CKHkTransportableObjectSpawner::TrySpawnOntoReceiver() {
    CKGrpTransportableObject* group = static_cast<CKGrpTransportableObject*>(m_unk64);
    m_fSpawnTimer = 0.0f;
    if (m_ui32SpawnCount < m_unk4c || m_unk68 == 0) {
        m_ui32SpawnCount += 1;
    } else {
        const uint32_t count = m_vUnk2c.m_ui32NbUsedElt;
        if (count == 0) return;
        bool full = true;
        for (uint32_t i = count; i != 0; --i) {
            if (m_vUnk2c.m_pBlock[i - 1] == nullptr) {
                full = false;
                break;
            }
        }
        if (full) {
            bool freed = false;
            for (uint32_t i = 0; i < m_vUnk2c.m_ui32NbUsedElt && !freed; ++i) {
                CKHkS08TransportableBase* object = static_cast<CKHkS08TransportableBase*>(m_vUnk2c.m_pBlock[i]);
                if (m_unk20 == nullptr) {
                    if (object->Vf100() == 0 && object->Vf110() != 0 && m_unk69 != 0 && object->Vf148() == 0) {
                        RecycleLiveObject(group, object);
                        freed = true;
                    }
                } else if (object->Vf140() != 0) {
                    freed = true;
                }
                if (freed) {
                    m_vUnk2c.m_pBlock[i] = nullptr;
                    Ps3Qsort(m_vUnk2c.m_pBlock, m_vUnk2c.m_ui32NbUsedElt, 4, CompareNullsLast);
                }
            }
            if (!freed) return;
        }
    }
    CKHkS08TransportableBase* object = static_cast<CKHkS08TransportableBase*>(group->TakePooledObject(m_unk3c));
    if (object == nullptr) return;
    if (m_unk20 != nullptr) {
        const CVector3 at = CarryTarget_GetGroundedPlacementPoint(m_unk20);  // 0x00426be8
        const CSGHotSpot* own = object->Vf118();
        const float x = at.x - own->m_v3RelativePosition.x;
        const float z = at.z - own->m_v3RelativePosition.z;
        const float y = at.y - own->m_v3RelativePosition.y;
        if (kNoPoint.x != x || kNoPoint.y != y || kNoPoint.z != z) {
            CSGLeaf* node = NodeOf(object);
            node->SetIdentity();  // 0x000d08f0
            SetNodePosition(NodeOf(object), x, y, z);
            NodeOf(object)->ForceWorldMatrixUpdate();  // vt+0x50
            object->Vf134(m_unk20);
            m_unk28 = object;
            object->SetOwnerSpawner(this);
            static_cast<CKHkPressionStone*>(m_unk20)->m_pObject = m_unk28;  // the receiver's +0x3c
            static_cast<CKHkS08TransportableBase*>(m_unk28)->SetFlag2C(1);  // vt+0x144
            NodeOf(object)->ForceWorldMatrixUpdate();
            return;
        }
    }
    object->Vf128(1);
    CSGLeaf* node = NodeOf(object);
    if (node->m_pParent != nullptr) node->m_pParent->RemoveChild(node);  // vt+0x78
    CKSector* sector = static_cast<CKSector*>(g_pEngine->m_level->m_vpSectors.m_pBlock[m_iSectorIndex]);
    sector->m_pSectorRoot->AddChild(node);  // vt+0x70
    SetNodeIdentityLocal(NodeOf(object));
    CVector3 at;
    if (m_pKGLObject == nullptr) {
        at = m_pMatrix->m_pos;
    } else {
        const RwV3d& p = static_cast<CSGLeaf*>(m_pKGLObject)->m_pRwFrame->modelling.pos;
        at = {p.x, p.y, p.z};
    }
    SetNodePosition(NodeOf(object), at.x, at.y, at.z);
    NodeOf(object)->m_sgProperties &= 0xfffffffbu;
    if (object->Vf118() != nullptr) {
        const RwV3d p = NodeOf(object)->m_pRwFrame->modelling.pos;
        const CSGHotSpot* own = object->Vf118();
        SetNodePosition(NodeOf(object), p.x - own->m_v3RelativePosition.x, p.y - own->m_v3RelativePosition.y,
                        p.z - own->m_v3RelativePosition.z);
    }
    NodeOf(object)->ForceWorldMatrixUpdate();  // vt+0x50
    m_unk28 = object;
    object->SetOwnerSpawner(this);
    object->Vf10C();
}

// 0x004a8a90 CKHkTransportableObjectSpawner_MessageProc: 0x996 turns spawning on (+0x24), 0x997 off; merged with the actor
// base's answer.
int32_t CKHkTransportableObjectSpawner::MessageProc(uint16_t message, void* data) {
    const int32_t base = CKHkActorBase::MessageProc(message, data);  // 0x003f7148
    int32_t own;
    if (message == 0x996) {
        own = 0;
        m_unk24 = 1;
    } else {
        own = 1;
        if (message == 0x997) {
            own = 0;
            m_unk24 = 0;
        }
    }
    if (base == 3 || own == 3) return 3;
    if (base == 2 || own == 2) return 2;
    if (base != 0) return own;
    return 0;
}

// 0x004a8a40 CKHkTransportableObjectSpawner_GetInfo
int32_t CKHkTransportableObjectSpawner::GetInfo(IKInfo* info, int32_t request) {
    const int32_t value = CKHkActorBase::GetInfo(info, request);  // 0x003f7140 KStub_Return1_3f7140
    if (value == 2) return 2;
    return value == 0 ? 0 : 1;  // ((|v| - 1) >> 31) ^ 1
}

// 0x004a9510 CKHkTransportableObjectSpawner_OnActivate: the actor base's; the effect data (+0x6c) gets bit 4 of its byte
// +0x08 cleared and the spawn matrix (no node) or the node's modelling matrix copied into its matrix +0x24; the effect is
// acquired (the pooled lookup, the spawner as owner) into +0x70.
void CKHkTransportableObjectSpawner::VfA0() {
    CKHkActorBase::VfA0();  // 0x003f7338
    CKParticlesEffectFxData* data = static_cast<CKParticlesEffectFxData*>(m_unk6c);
    data->m_unk08 = static_cast<uint8_t>((data->m_unk08 & 0xe0u) | (data->m_unk08 & 0x0fu));
    if (m_pKGLObject == nullptr) {
        *reinterpret_cast<CMatrix34*>(data->m_unk24) = *m_pMatrix;
    } else {
        *data->m_unk24 = static_cast<CSGLeaf*>(m_pKGLObject)->m_pRwFrame->modelling;
    }
    m_unk70 = static_cast<CKSrvFx*>(g_pEngine->m_srvFx)->AcquireFx(data, this);  // inlined
}

// 0x004a8fc8 CKHkTransportableObjectSpawner_OnDeactivate: the actor base's; the effect released (vt+0x58); the spawned
// transportable and every entry's back into the pool m_unk3c (ReturnObjectToPool), their nodes under sector 0's root.
void CKHkTransportableObjectSpawner::VfA4() {
    CKHkActorBase::VfA4();  // 0x003f7370
    if (m_unk70 != nullptr) {
        static_cast<IKFx*>(m_unk70)->StopAndRelease(this);  // vt+0x58
        m_unk70 = nullptr;
    }
    CKGrpTransportableObject* group = static_cast<CKGrpTransportableObject*>(m_unk64);
    if (m_unk28 != nullptr) {
        group->ReturnObjectToPool(m_unk3c, m_unk28);  // 0x004a7a18
        ReparentToBaseSectorRoot(NodeOf(m_unk28));
        m_unk28 = nullptr;
    }
    for (uint32_t i = 0; i < m_vSpawnEntries.m_ui32NbUsedElt; ++i) {
        SpawnEntry* entry = m_vSpawnEntries.m_pBlock[i];
        if (entry->m_unk8 == nullptr) continue;
        group->ReturnObjectToPool(m_unk3c, entry->m_unk8);
        ReparentToBaseSectorRoot(NodeOf(entry->m_unk8));
        entry->m_unk8 = nullptr;
    }
}

// 0x004a8d58 CKHkTransportableObjectSpawner_Destroy: CKHkActorBase_d82_maybe_Destroy 0x3f6e40 (vt+0xc0, empty), the spawn
// matrix destroyed (RwMatrixDestroy), every spawn entry deleted.
void CKHkTransportableObjectSpawner::Destroy() {
    RwMatrixDestroy_Thunk(m_pMatrix);
    for (uint32_t i = 0; i < m_vSpawnEntries.m_ui32NbUsedElt; ++i) delete m_vSpawnEntries.m_pBlock[i];
}

// 0x004a9b08 CKHkTransportableObjectSpawner_LoadSpawnEntries_maybe: a count, then one reference per
// entry, each pushed onto +0x40 (reset to capacity 1 first; the old block is not freed).
void CKHkTransportableObjectSpawner::LoadSpawnEntries(IKFile* file) {
    uint32_t count = 0;
    ReadU32LE(file, &count);
    m_vSpawnEntries.m_ui32NbElt = 1;
    m_vSpawnEntries.m_pBlock = static_cast<SpawnEntry**>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(SpawnEntry*))));
    for (uint32_t i = 0; i < count; ++i) {
        SpawnEntry* entry = new SpawnEntry;
        entry->m_pUnk0 = nullptr;
        entry->m_unk4 = 0;
        entry->m_unk8 = 0;
        IKFile_ReadRef(file, &entry->m_pUnk0);
        entry->m_unk4 = 0;
        entry->m_unk8 = 0;
        const uint32_t used = m_vSpawnEntries.m_ui32NbUsedElt;
        if (m_vSpawnEntries.m_ui32NbElt == used) {
            uint32_t capacity = used + 1;
            if (capacity == 0) capacity = 1;
            m_vSpawnEntries.m_pBlock = static_cast<SpawnEntry**>(Mem_ReallocAligned16(
                m_vSpawnEntries.m_pBlock, capacity * static_cast<uint32_t>(sizeof(SpawnEntry*))));
            m_vSpawnEntries.m_ui32NbElt = capacity;
        }
        m_vSpawnEntries.m_pBlock[m_vSpawnEntries.m_ui32NbUsedElt] = entry;
        m_vSpawnEntries.m_ui32NbUsedElt += 1;
    }
}

// 0x004aaeb8 CKHkTransportableObjectSpawner_Load
int32_t CKHkTransportableObjectSpawner::Load(IKFile* file, int32_t type) {
    CKHkActorBase::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    m_pMatrix = RwMatrixCreate_Thunk();
    CVector3 pos;
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(&pos), 3);
    // The inlined identity (RwMatrixSetIdentity), then the position; the identity flag is cleared.
    CMatrix34* m = m_pMatrix;
    m->m_ui32Flags = 0x20003u;
    m->m_right.x = 1.0f;
    m->m_right.z = 0.0f;
    m->m_right.y = 0.0f;
    m->m_pos.x = 0.0f;
    m->m_up.y = 1.0f;
    m->m_up.x = 0.0f;
    m->m_at.y = 0.0f;
    m->m_at.x = 0.0f;
    m->m_up.z = 0.0f;
    m->m_pos.z = 0.0f;
    m->m_pos.y = 0.0f;
    m->m_at.z = 1.0f;
    m->m_pos.z = pos.z;
    m->m_pos.x = pos.x;
    m->m_pos.y = pos.y;
    m->m_ui32Flags &= 0xfffdffffu;
    Mat4_SetBasisFromAtUp(m_pMatrix, &kVectorAxisZ, &kVectorAxisY);
    IKFile_ReadRef(file, &m_unk5c);
    ReadU32LE(file, &m_unk4c);
    ReadF32LE(file, &m_unk50);
    LoadSpawnEntries(file);
    IKFile_ReadRef(file, &m_unk64);
    ReadU32LE(file, &m_unk3c);
    ReadU8(file, &m_unk68);
    IKFile_ReadRef(file, &m_unk6c);
    ReadF32LE(file, &m_unk74);
    ReadU8(file, &m_unk25);
    IKFile_ReadRef(file, &m_unk20);
    ReadU8(file, &m_unk69);
    return 1;
}

// 0x004a87b8 CKHkTransportableObjectSpawner_SetDefaultState
void CKHkTransportableObjectSpawner::SetDefaultState(int32_t flag) {
    CKHkActorBase::SetDefaultState(flag);
    m_unk24 = 1;
}

// 0x004a9230 CKHkTransportableObjectSpawner_Restart (vt+0x54): with the life flag bit 2 the effect (+0x70) released
// (vt+0x58 with the spawner as owner); the spawned object (+0x28) and every spawn entry's object (+0x08) back into the
// group's pool m_unk3c (ReturnObjectToPool), their nodes under sector 0's root, their state machines reset (vt+0x11c);
// the two counters cleared.
void CKHkTransportableObjectSpawner::Restart() {
    if ((m_bitArray & 4u) != 0 && m_unk70 != nullptr) {
        static_cast<IKFx*>(m_unk70)->StopAndRelease(this);  // vt+0x58
        m_unk70 = nullptr;
    }
    CKGrpTransportableObject* group = static_cast<CKGrpTransportableObject*>(m_unk64);
    if (m_unk28 != nullptr) {
        group->ReturnObjectToPool(m_unk3c, m_unk28);  // 0x004a7a18
        CKHkS08TransportableBase* object = static_cast<CKHkS08TransportableBase*>(m_unk28);
        ReparentToBaseSectorRoot(static_cast<CSGLeaf*>(object->m_pKGLObject));
        object->ResetStateMachine();  // vt+0x11c
        m_unk28 = nullptr;
    }
    for (uint32_t i = 0; i < m_vSpawnEntries.m_ui32NbUsedElt; ++i) {
        SpawnEntry* entry = m_vSpawnEntries.m_pBlock[i];
        if (entry->m_unk8 == nullptr) continue;
        group->ReturnObjectToPool(m_unk3c, entry->m_unk8);
        CKHkS08TransportableBase* object = static_cast<CKHkS08TransportableBase*>(entry->m_unk8);
        ReparentToBaseSectorRoot(static_cast<CSGLeaf*>(object->m_pKGLObject));
        object->ResetStateMachine();  // vt+0x11c
        entry->m_unk8 = nullptr;
    }
    m_ui32SpawnCount = 0;
    m_fSpawnTimer = 0.0f;
}

// 0x004a9950 CKHkTransportableObjectSpawner_Start. The current entry is the group's entry m_unk3c. The +0x2c
// vector is resized to m_unk4c elements unless its length already equals the word at +0x58 (a first start
// allocates a one-element block, then grows it to m_unk4c); the spawn entries' two words and the vector's
// elements are cleared, then the counters.
void CKHkTransportableObjectSpawner::Start() {
    CKHkActorBase::Start();
    m_pCurrentEntry = static_cast<CKGrpTransportableObject*>(m_unk64)->m_vEntries.m_pBlock[m_unk3c];
    bool resize = false;
    if (m_vUnk2c.m_pBlock == nullptr) {
        m_vUnk2c.m_ui32NbElt = 1;
        m_vUnk2c.m_pBlock = static_cast<IKSerializable**>(Mem_AllocAligned16(4));
        resize = true;
    } else if (m_vUnk2c.m_ui32NbUsedElt != m_ui32SpawnCount) {
        resize = true;
    }
    if (resize) {
        const uint32_t count = m_unk4c;
        if (m_vUnk2c.m_ui32NbElt < count) {
            uint32_t capacity = count + 1;
            uint32_t bytes = capacity * 4;
            if (capacity == 0) {
                capacity = 1;
                bytes = 4;
            }
            m_vUnk2c.m_pBlock = static_cast<IKSerializable**>(Mem_ReallocAligned16(m_vUnk2c.m_pBlock, bytes));
            m_vUnk2c.m_ui32NbElt = capacity;
        }
        m_vUnk2c.m_ui32NbUsedElt = count;
    }
    for (uint32_t i = 0; i < m_vSpawnEntries.m_ui32NbUsedElt; ++i) {
        m_vSpawnEntries.m_pBlock[i]->m_unk8 = 0;
        m_vSpawnEntries.m_pBlock[i]->m_unk4 = 0;
    }
    for (uint32_t i = 0; i < m_vUnk2c.m_ui32NbUsedElt; ++i) m_vUnk2c.m_pBlock[i] = nullptr;
    m_unk70 = nullptr;
    m_fSpawnTimer = 0.0f;
    m_unk28 = nullptr;
    m_ui32SpawnCount = 0;
}

// 0x004ac060 CKHkS08TransportableBase_3002_maybe_ResetRuntime (the base's Start, in the spawner's unit):
// CKHkActorBase_d82_maybe_ResetRuntime (empty), +0x25 = 1, +0x28 = 0, then vt+0x144 with 0.
void CKHkS08TransportableBase::Start() {
    CKHkActorBase::Start();
    m_unk25 = 1;
    m_unk28 = 0;
    SetFlag2C(0);
}
