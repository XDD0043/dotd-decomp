// CKGrpBonusPool_2.cpp - reconstructed original translation unit 0x5b1668-0x5b4840 (GAME_TOC2, main_toc2), 30 functions, 25 live.
// Primary owner: CKGrpBonusPool (not a registered class)
// Other owners: CKHkBasicBonus (2), Bonus (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x5b1668  CKGrpBonusPool_ReleaseBonusFx_maybe
//   [x] 0x5b16e8  CKGrpBonusPool_DestroyArray  (the DeleteArray factory: DOTD_DECLARE_FACTORIES(CKGrpBonusPool); port-rest R07)
//   [x] 0x5b1788  CKGrpBonusPool_Create
//   [x] 0x5b1800  CKGrpBonusPool_SpawnBonus_maybe
//   [ ] 0x5b1918  CKGrpBonusPool_BonusList_Remove_maybe  [dead]
//   [x] 0x5b1990  CKGrpBonusPool_vf10C  (SetSectorBeaconBits; port-rest R07; CKGrpS08BonusPool inherits it)
//   [x] 0x5b1b58  CKGrpBonusPool_vf108  (ReleaseBeaconed; port-rest R07; CKGrpS08BonusPool inherits it)
//   [x] 0x5b1c50  CKGrpBonusPool_ReleaseAllActive_maybe
//   [x] 0x5b1db8  CKGrpBonusPool_vf118  (Vf118; port-rest R07; CKGrpS08BonusPool inherits it)
//   [x] 0x5b1e48  CKGrpBonusPool_vf114  (Vf114 in the header; port-rest R07; CKGrpS08BonusPool inherits it)
//   [x] 0x5b1eb0  CKGrpBonusPool_vfF8  (VfF8 in the header; port-rest R07; CKGrpS08BonusPool inherits it)
//   [x] 0x5b1f10  CKGrpBonusPool_ResetPool_maybe
//   [x] 0x5b1fe0  CKGrpBonusPool_vf40  (GetInfo: the IKSerializable default (1); port-rest R07; CKGrpS08BonusPool inherits it)
//   [x] 0x5b1fe8  CKGrpBonusPool_vf1C  (MessageProc; port-rest R07; CKGrpS08BonusPool's MessageProc calls it)
//   [x] 0x5b23f8  CKGrpBonusPool_CreateArray
//   [x] 0x5b24c8  CKGrpBonusPool_LevelReset  (RecursiveRegistration; port-rest R07; CKGrpS08BonusPool's RecursiveRegistration calls it)
//   [ ] 0x5b25e8  CKGrpBonusPool_Save
//   [x] 0x5b2610  CKGrpBonusPool_ClearReferences
//   [ ] 0x5b2670  CKGrpBonusPool_CountActiveBonuses_maybe  [dead: no pointer to its descriptor 0xbf06d0, no call]
//   [ ] 0x5b2728  CKGrpBonusPool_ClearBeaconBitsOfType_maybe  [dead]
//   [x] 0x5b28e8  CKGrpBonusPool_UpdateBonuses_maybe
//   [x] 0x5b3240  CKGrpBonusPool_Load
//   [ ] 0x5b3630  CKGrpBonusPool_TriggerCollectEffects_maybe  [dead]
//   [x] 0x5b3958  CKGrpBonusPool_AcquireBonusFx_maybe
//   [x] 0x5b3bc0  Bonus_TriggerCollectExplosion_maybe
//   [x] 0x5b3e50  CKGrpBonusPool_StopBonusTrail_maybe
//   [x] 0x5b3ea8  CKGrpBonusPool_ResetBonusTrail_maybe
//   [x] 0x5b4778  CKHkBasicBonus_Destroy  (the Delete factory: DOTD_DECLARE_FACTORIES(CKHkBasicBonus), k2000/ui/CKHkBasicBonus.h; port-final F06)
//   [ ] 0x5b47c8  CKHkBasicBonus_SetFlagBitfields_maybe  [dead]
//   [ ] 0x5b4828  FUN_005b4828  [dead]
//
//   [ ] 0x9cc008  CKGrpBonusPool_vf11C  [inline]
//   [x] 0x9cc408  CKGrpBonusPool_GetClassGroup  [inline]
//   [x] 0x9cc410  CKGrpBonusPool_GetClassId  [inline]
//   [ ] 0x9cc418  CKGrpBonusPool_vfCC  [inline]
//   [ ] 0x9cc420  CKGrpBonusPool_vf120  [inline]
//   [x] 0x9cc438  CKGrpBonusPool_vf124  [inline]
//   [ ] 0x9cc440  CKGrpBonusPool_vf128  [inline]
//   [x] 0x9cc448  CKGrpBonusPool_vf12C  [inline]
//   [ ] 0x9cc450  CKGrpBonusPool_IsKindOf  [inline]
//   [ ] 0x9cc4a8  CKGrpBonusPool_DeletingDestructor  [inline]
//   [ ] 0x9cc4f8  CKGrpBonusPool_Destructor  [inline]
//   [ ] 0x9cc518  KBase1C42_IsKindOf  [inline]
//   [ ] 0x9cc560  KBase1C42_GetClassGroup  [inline]
//   [ ] 0x9cc568  KBase1C42_GetClassId  [inline]
#include "k2000/memory/CKGrpBonusPool.h"
#include "Renderware/rwcore/RwCamera.h"
#include "Spyro2008/groups/IKGrpHero.h"
#include "k2000/ui/IKHkBonus.h"
#include "k2000/ui/CKBonusCpnt.h"
#include "crt/ppc_ops.h"
#include "k2000/cameras/CameraContext.h"
#include "k2000/components/IKBonusCpnt.h"
#include "k2000/core/Stub.h"
#include "k2000/dictionaries/CKSoundDictionaryID.h"
#include "k2000/fx/IKFx.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/logic/CKLevel.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/logic/CKParticlesEffectFxData.h"
#include "k2000/logic/IKFxData.h"
#include "k2000/logic/fx/CKExplosionNodeFx.h"
#include "k2000/logic/sound/CKSound.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/CSGLeaf.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/scenegraph/CTrailNodeFx.h"
#include "k2000/services/CKSrvBeacon.h"
#include "k2000/services/CKSrvFx.h"
#include "k2000/system/IKTime.h"

// 0x005b3240 CKGrpBonusPool_Load. The original tests "type not 4..7" and then type 0.
int32_t CKGrpBonusPool::Load(IKFile* file, int32_t type) {
    GroupBasicLoad(file, type);
    if (static_cast<uint32_t>(type) - 4u <= 3u || type != K_LEVEL_PLATEFORMS) return 1;
    ReadU32LE(file, &m_ui32BonusType);
    ReadU32LE(file, &m_ui32BonusBeaconID);
    ReadU32LE(file, &m_ui32MaxSimultaneousBonusOnBeacon);
    ReadF32LE(file, &m_fFarDistance);
    ReadU8(file, &m_unk3c);
    IKFile_ReadObjectRefArray(file, &m_pFirstUsed, 4);  // +0x40..+0x4c
    IKFile_ReadRef(file, &m_pStaticParticles);
    IKFile_ReadRef(file, &m_pCatchedParticles);
    IKFile_ReadRef(file, &m_pUnk58);
    ReadF32LE(file, &m_unk5c);
    ReadU8(file, &m_unk60);
    return 1;
}

// 0x005b1f10 CKGrpBonusPool_ResetPool_maybe. The pool's hooks are bonus hooks (IKHkBonus: +0x20 and +0x24 are its
// free-list link and index; its slots are virtual calls, port-final F06).
namespace {
// A pool list's bonuses (their +0x20 links) told vt+0xd8, then the list chained in front of the free list.
IKSerializable* ReleaseList(IKSerializable* head, IKSerializable* freeList) {
    if (head == nullptr) return freeList;
    for (IKSerializable* it = head; it != nullptr; it = static_cast<IKHkBonus*>(it)->m_pNextBonus) {
        static_cast<IKHkBonus*>(it)->DisableAndReleaseFx();  // vt+0xd8 0x005b7890
    }
    if (freeList == nullptr) return head;
    IKSerializable* last = head;
    while (static_cast<IKHkBonus*>(last)->m_pNextBonus != nullptr) last = static_cast<IKHkBonus*>(last)->m_pNextBonus;
    static_cast<IKHkBonus*>(last)->m_pNextBonus = freeList;
    return head;
}
}  // namespace

// 0x005b1c50 CKGrpBonusPool_ReleaseAllActive_maybe (vt+0xf8; CKGrpBonus_ReinitRuntime): the used, then the beaconed
// bonuses released (vt+0xd8) and put back in front of the free list; both lists empty.
void CKGrpBonusPool::ReleaseAllActive() {
    m_pFirstFree = ReleaseList(m_pFirstUsed, m_pFirstFree);
    m_pFirstFree = ReleaseList(m_pFirstBeaconed, m_pFirstFree);
    m_pFirstBeaconed = nullptr;
    m_pFirstUsed = nullptr;
}

// 0x005b1668 CKGrpBonusPool_ReleaseBonusFx_maybe: a bonus's effect stopped when the pool owns it (StopOwnedParticleEffect,
// the TOC bridge 0x98fe20), then its reservation released (vt+0x54).
void CKGrpBonusPool::ReleaseBonusFx(IKSerializable* effect) {
    if (effect == nullptr) return;
    StopOwnedParticleEffect(static_cast<IKFx*>(effect), this);  // 0x001cdde8
    static_cast<IKFx*>(effect)->ReleaseReservation(this);       // vt+0x54
}

void CKGrpBonusPool::ResetPool() {
    m_pFirstUsed = nullptr;
    m_pFirstBeaconed = nullptr;
    IKHook* hook = *reinterpret_cast<IKHook**>(GetMemberListHead());  // vt+0xb0
    m_pFirstFree = hook;
    uint32_t index = 0;
    while (hook != nullptr) {
        IKHkBonus* bonus = static_cast<IKHkBonus*>(hook);
        bonus->m_ui32PoolIndex = index;
        bonus->m_pNextBonus = bonus->m_pNextHook;
        hook = bonus->m_pNextHook;
        ++index;
    }
    m_bitArray &= 0xfffffe7fu;
    m_unk68 = 0;
    m_unk64 = 0.0f;
}

namespace {
IKHkBonus* Bonus(IKSerializable* hook) { return static_cast<IKHkBonus*>(hook); }
// The world position of a hook's node (its frame's LTM position).
const RwV3d& WorldPos(IKSerializable* hook) {
    return static_cast<CSGMovable*>(static_cast<IKHook*>(hook)->m_pKGLObject)->m_pRwFrame->ltm.pos;
}
// The squared distance as the original sums it: (y first) fmadds x, then fmadds z.
float Dist2(float dx, float dy, float dz) { return ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)); }
// A list's collected / hidden members moved to the front of `to` (UpdateBonuses' first and third passes; the member
// before a moved one keeps its place).
template <class Pred>
void MoveMatching(IKSerializable** from, IKSerializable** to, Pred pred) {
    IKSerializable* prev = nullptr;
    IKSerializable* cur = *from;
    while (cur != nullptr) {
        IKSerializable* next = Bonus(cur)->m_pNextBonus;
        if (!pred(Bonus(cur))) {
            prev = cur;
            cur = next;
            continue;
        }
        if (prev == nullptr) {
            Bonus(cur)->m_pNextBonus = nullptr;  // the head: its link cleared (r28 = 0), the list starts at the next one
            *from = next;
        } else {
            IKSerializable* taken = Bonus(prev)->m_pNextBonus;
            if (taken != nullptr) {
                Bonus(prev)->m_pNextBonus = Bonus(taken)->m_pNextBonus;
                Bonus(taken)->m_pNextBonus = nullptr;
            }
        }
        Bonus(cur)->m_pNextBonus = *to;
        *to = cur;
        cur = next;
    }
}
}  // namespace

// 0x005b28e8 CKGrpBonusPool_UpdateBonuses_maybe (vt+0xf4)
void CKGrpBonusPool::UpdateBonuses(IKTime* frameClock) {
    const float zero = 0.0f;  // TOC2 -0x6560
    if (m_unk64 > zero) m_unk64 = m_unk64 - frameClock->m_afDeltaTime[0];
    if (m_unk68 != 0 && m_unk64 <= zero) {  // cror lt|eq
        CKSound* sound = static_cast<CKSoundDictionaryID*>(static_cast<IKBonusCpnt*>(m_pBonusCpnt)->m_pSoundDictionary)
                             ->GetSound(0);  // 0x00112bc0
        if (sound != nullptr) {
            sound->ResetPan(1);   // 0x00111b70
            sound->Play(zero);    // 0x00111230
        }
        m_unk64 = 0.05f;  // TOC2 -0x6548
        --m_unk68;
    }
    if (m_pBonusCpnt->IsKindOfClass(0x586) != 0) {  // vt+0x08: CKBonusCpnt
        // 0x005bad28 CKBonusCpnt_ComputeSpinBobMatrix_maybe (port-rest R09). No CKBonusCpnt (0x586) exists in LVL010's data:
        // the pools hold CKS08BonusCpnt (0x1306, IsKindOfClass false for 0x586).
        static_cast<CKBonusCpnt*>(m_pBonusCpnt)->ComputeSpinBobMatrix(frameClock);
    }
    // The heroes (CKGrpS08Hero_GetHeroList 0x002ca0f0 of the game manager's hero group, null-terminated) and the camera.
    CKSrvBeacon* beacons = static_cast<CKSrvBeacon*>(g_pEngine->m_srvBeacon);
    IKGrpHero* group = static_cast<IKGrpHero*>(g_pEngine->m_gameManager->m_unk04[1]);
    const RwFrame* camera =
        static_cast<CSGMovable*>(static_cast<CameraContext*>(g_pEngine->m_cameraContext)->m_pCamera)->m_pRwFrame;
    IKSerializable** heroes = nullptr;
    uint32_t heroCount = 0;
    if (group != nullptr) {
        heroes = group->m_apHeroesCopy;
        if (heroes != nullptr) {
            while (heroes[heroCount] != nullptr) ++heroCount;
        }
    }
    // The beaconed bonuses that were collected join the used ones.
    MoveMatching(&m_pFirstBeaconed, &m_pFirstUsed, [](IKHkBonus* b) { return b->IsCollected() != 0; });  // vt+0xcc
    // The used bonuses: updated, then a free one is collected by the nearest hero that may take it and is in reach.
    if (m_pFirstUsed != nullptr) {
        for (IKSerializable* it = m_pFirstUsed; it != nullptr;) {
            IKSerializable* next = Bonus(it)->m_pNextBonus;
            Bonus(it)->Update(frameClock);  // vt+0x7c
            if (Bonus(it)->IsCollected() == 0) {
                float best = 3.40282347e+38f;  // 0x00c4ace0
                if (heroCount != 0) {
                    IKSerializable* nearest = nullptr;
                    for (uint32_t i = 0; i < heroCount; ++i) {
                        IKSerializable* hero = heroes[i];
                        const RwV3d& b = WorldPos(it);
                        const RwV3d& h = WorldPos(hero);
                        const float bz = b.z, bx = b.x, by = b.y;
                        const float hz = h.z, hx = h.x, hy = h.y;
                        if (CanHeroCollect(hero) == 0) continue;  // vt+0x124
                        const float d = Dist2(bx - hx, by - hy, bz - hz);
                        if (static_cast<IKBonusCpnt*>(m_pBonusCpnt)->m_fSquareCatchDist >= d && best > d) {
                            best = d;
                            nearest = hero;
                        }
                    }
                    if (nearest != nullptr) Bonus(it)->Collect(nearest, nullptr);  // vt+0xc8
                }
            }
            it = next;
        }
        // The hidden ones (node flag 4) back to the free list.
        MoveMatching(&m_pFirstUsed, &m_pFirstFree, [](IKHkBonus* b) {
            return (static_cast<CSGLeaf*>(b->m_pKGLObject)->m_sgProperties & 4u) != 0;
        });
    }
    // The beaconed bonuses are released every frame (vt+0xd8) and the list put in front of the free one.
    if (m_pFirstBeaconed != nullptr) {
        IKSerializable* last = m_pFirstBeaconed;
        Bonus(last)->DisableAndReleaseFx();
        for (IKSerializable* it = Bonus(last)->m_pNextBonus; it != nullptr; it = Bonus(it)->m_pNextBonus) {
            Bonus(it)->DisableAndReleaseFx();
            last = it;
        }
        Bonus(last)->m_pNextBonus = m_pFirstFree;
        m_pFirstFree = m_pFirstBeaconed;
        m_pFirstBeaconed = nullptr;
    }
    if ((m_bitArray & 0x100u) != 0) return;
    // The beacons of the pool's type (the low byte of +0x30) in the drawn sectors, in the frustum (flags 3): each one not
    // collected yet takes a free bonus while the pool has fewer than its maximum out and the beacon is within the far
    // distance of the camera (else, or without a free bonus, the update stops).
    CKSrvBeacon::CKBeaconSet* list =
        beacons->GatherBeaconsOfType(static_cast<uint8_t>(m_ui32BonusBeaconID), 3, nullptr, nullptr);  // 0x00123b40
    const float tenth = 0.1f;  // TOC2 -0x653c
    uint32_t spawned = 0;
    while (CKSrvBeacon::CKBeaconSet* set = CKSrvBeacon::TakeNext(&list)) {  // 0x00123530
        uint16_t accessor[4] = {set->m_aui16Accessor[0], set->m_aui16Accessor[1], set->m_aui16Accessor[2], 0xffff};
        const uint8_t* beacon = static_cast<const uint8_t*>(set->m_aBeacons);
        for (uint32_t left = set->m_ui32NbBeacons; left != 0; --left, beacon += set->m_ui8VolatileSizeBytes) {
            ++accessor[3];
            // The beacon's persistent bits (the set's own start and size): bit 0 says it was collected.
            uint32_t collected = 0;
            const uint32_t bits = set->m_ui8PersistentSizeBits;
            if (bits != 0) {
                const uint8_t* block = g_pSrvBeacon->m_aBeaconSectors[accessor[0]].m_bavPersistent.m_p8Bits;
                const uint32_t base = static_cast<uint32_t>(set->m_aui16Accessor[3]) + bits * accessor[3];
                uint32_t value = 0;
                for (uint32_t b = 0; b < bits; ++b) {
                    const uint32_t n = base + b;
                    if (((block[n >> 3] >> (n & 7)) & 1u) != 0) value += ppc::slw(1u, b);
                }
                collected = value & 1u;
            }
            const uint16_t heroAccessor[4] = {accessor[0], accessor[1], accessor[2], accessor[3]};
            const int16_t* raw = reinterpret_cast<const int16_t*>(beacon);
            if (collected != 0) continue;
            IKSerializable* bonus = m_pFirstFree;
            if (bonus == nullptr) return;
            if (!(m_ui32MaxSimultaneousBonusOnBeacon > spawned)) return;
            const float x = static_cast<float>(static_cast<double>(raw[0])) * tenth;
            const float y = static_cast<float>(static_cast<double>(raw[1])) * tenth;
            const float z = static_cast<float>(static_cast<double>(raw[2])) * tenth;
            if (!(m_fFarDistance < zero)) {
                const float d = Dist2(x - camera->ltm.pos.x, y - camera->ltm.pos.y, z - camera->ltm.pos.z);
                if (!(d < m_fFarDistance * m_fFarDistance)) return;  // bge
            }
            ++spawned;
            m_pFirstFree = Bonus(bonus)->m_pNextBonus;
            Bonus(bonus)->m_pNextBonus = nullptr;
            Bonus(bonus)->m_pNextBonus = m_pFirstBeaconed;
            m_pFirstBeaconed = bonus;
            Bonus(bonus)->SpawnAtBeacon(heroAccessor);  // vt+0xd0
            Bonus(bonus)->Update(frameClock);           // vt+0x7c
            for (uint32_t i = 0; i < heroCount; ++i) {
                IKSerializable* hero = heroes[i];
                if (CanHeroCollect(hero) == 0) continue;  // vt+0x124
                const RwV3d& h = WorldPos(hero);
                const float d = Dist2(x - h.x, y - h.y, z - h.z);
                if (d <= static_cast<IKBonusCpnt*>(m_pBonusCpnt)->m_fSquareCatchDist) {  // cror lt|eq
                    Bonus(bonus)->Collect(hero, heroAccessor);  // vt+0xc8
                    break;
                }
            }
        }
    }
}

// 0x005b1800 CKGrpBonusPool_SpawnBonus_maybe (vt+0xfc)
IKSerializable* CKGrpBonusPool::SpawnBonus(const CVector3* position, uint8_t playSound) {
    IKSerializable* bonus = m_pFirstFree;
    if (bonus == nullptr) return nullptr;
    m_pFirstFree = Bonus(bonus)->m_pNextBonus;
    Bonus(bonus)->m_pNextBonus = nullptr;
    Bonus(bonus)->m_pNextBonus = m_pFirstUsed;
    m_pFirstUsed = bonus;
    Bonus(bonus)->SpawnAt(static_cast<IKBonusCpnt*>(m_pBonusCpnt)->m_fSpawnedLifeExpectancy, position);  // vt+0xc4
    if (playSound != 0) {
        CKSound* sound =
            static_cast<CKSoundDictionaryID*>(static_cast<IKBonusCpnt*>(m_pBonusCpnt)->m_pSoundDictionary)->GetSound(1);
        if (sound != nullptr) {
            sound->SetPosition(position);  // 0x00110fa0
            sound->Play(0.0f);             // 0x00111230
        }
    }
    return bonus;
}

// 0x005b3958 CKGrpBonusPool_AcquireBonusFx_maybe
IKSerializable* CKGrpBonusPool::AcquireBonusFx(IKSerializable* node) {
    if (node == nullptr) return nullptr;
    CKParticlesEffectFxData* data = static_cast<CKParticlesEffectFxData*>(m_pStaticParticles);
    data->m_ui8Flags = static_cast<uint8_t>((data->m_ui8Flags & 0xe0u) | (data->m_ui8Flags & 0x0fu) | 0x10u);
    data->m_pAttachOwner = static_cast<CSGLeaf*>(node);
    data->m_pAttachHotSpot = nullptr;
    return static_cast<CKSrvFx*>(g_pEngine->m_srvFx)->AcquireFx(data, this);  // inlined
}

// 0x005b3bc0 Bonus_TriggerCollectExplosion_maybe
void CKGrpBonusPool::TriggerCollectExplosion(const CVector3* position) {
    IKFx* fx = static_cast<CKSrvFx*>(g_pEngine->m_srvFx)->AcquireFx(static_cast<IKFxData*>(m_pCatchedParticles), this);
    if (fx == nullptr) return;
    CKExplosionNodeFx* explosion = static_cast<CKExplosionNodeFx*>(fx);
    explosion->SetTranslation(position, this);  // 0x001b66e8
    explosion->Trigger(this, 0);                // 0x001b82a8
    explosion->ReleaseReservation(this);        // vt+0x54
}

// 0x005b3e50 CKGrpBonusPool_StopBonusTrail_maybe
void CKGrpBonusPool::StopBonusTrail(uint32_t index) {
    if (m_pUnk58 == nullptr) return;
    STrailNodeData* trail = static_cast<CTrailNodeFx*>(m_pUnk58)->m_apTrailData[index & 0xffu];
    if ((trail->m_ba8Properties & 1u) == 0) return;
    trail->m_ba8Properties = static_cast<uint8_t>(trail->m_ba8Properties & 0xfeu);
    trail->m_ui8Visible = static_cast<uint8_t>(trail->m_ui32NbCtrPoints);
}

// 0x005b3ea8 CKGrpBonusPool_ResetBonusTrail_maybe (CTrailNodeFx_SetRibbonActive_maybe inlined twice)
void CKGrpBonusPool::ResetBonusTrail(uint32_t index, const CVector3* position, const CVector3* up) {
    if (m_pUnk58 == nullptr) return;
    CTrailNodeFx* trail = static_cast<CTrailNodeFx*>(m_pUnk58);
    trail->SetRibbonActive(index & 0xffu, 0, 1);  // 0x009bdfb8
    SetBonusTrailEndpoints(index, position, up);  // inlined
    trail->SetRibbonActive(index & 0xffu, 1, 1);
}

// 0x005b2610 CKGrpBonusPool_Destroy
void CKGrpBonusPool::Destroy() {
    m_lChilds = nullptr;
    *GetMemberListHead() = nullptr;  // vt+0xb0
}

// ---- C2.8 port-rest R07: the pool's remaining slots ------------------------------------------------------------------

// 0x005b1b58 CKGrpBonusPool_vf108 (vt+0x108)
void CKGrpBonusPool::ReleaseBeaconed() {
    m_pFirstFree = ReleaseList(m_pFirstBeaconed, m_pFirstFree);
    m_pFirstBeaconed = nullptr;
}

// 0x005b1990 CKGrpBonusPool_vf10C (vt+0x10c). The beacon's set comes from its accessor (the sector's kluster, the id's
// set: CKSrvBeacon::GetBeaconSet); the bits are the set's persistent ones, PersistentSizeBits wide from the set's start
// (+0x1a) plus the beacon's index times the width. Only the field's first bit is cleared before `value` is or-ed in at
// that place (the original's andc / or with slw).
void CKGrpBonusPool::SetSectorBeaconBits(uint8_t sector, uint8_t value) {
    CKSrvBeacon* beacons = static_cast<CKSrvBeacon*>(g_pEngine->m_srvBeacon);  // engine +0x78
    CKSrvBeacon::CKBeaconSet* list =
        beacons->BeginTypeIteration(static_cast<uint8_t>(m_ui32BonusBeaconID), sector);  // TocBridge 0x9906c0
    while (CKSrvBeacon::CKBeaconSet* set = CKSrvBeacon::TakeNext(&list)) {             // TocBridge 0x9906d0
        uint16_t accessor[4] = {set->m_aui16Accessor[0], set->m_aui16Accessor[1], set->m_aui16Accessor[2], 0xffff};
        for (uint32_t left = set->m_ui32NbBeacons; left != 0; --left) {
            ++accessor[3];
            CKSrvBeacon::CKBeaconSector& where = beacons->m_aBeaconSectors[accessor[0]];
            if (where.m_apBeaconKlusters == nullptr) continue;
            // BUG(original): an id without a set (-1) reads the set at address 0; the port skips the beacon.
            const CKSrvBeacon::CKBeaconSet* own = beacons->GetBeaconSet(accessor);
            if (own == nullptr) continue;
            const uint32_t n = static_cast<uint32_t>(own->m_aui16Accessor[3]) +
                               static_cast<uint32_t>(own->m_ui8PersistentSizeBits) * accessor[3];
            uint8_t* bits = where.m_bavPersistent.m_p8Bits;
            const uint32_t shift = n & 7u;
            bits[n >> 3] = static_cast<uint8_t>(bits[n >> 3] & ~ppc::slw(1u, shift));
            bits[n >> 3] = static_cast<uint8_t>(ppc::slw(value, shift) | bits[n >> 3]);
        }
    }
}

// 0x005b1db8 CKGrpBonusPool_vf118 (vt+0x118): the members (vt+0xb0's head, through the hooks' +0x14) told vt+0xdc.
void CKGrpBonusPool::Vf118() {
    for (IKHook* hook = *reinterpret_cast<IKHook**>(GetMemberListHead()); hook != nullptr; hook = hook->m_pNextHook) {
        static_cast<IKHkBonus*>(hook)->VfDC();  // vt+0xdc 0x005b7010
    }
}

// 0x005b24c8 CKGrpBonusPool_RecursiveRegistration (vt+0x24)
void CKGrpBonusPool::RecursiveRegistration(int32_t type) {
    IKBaseGroup::RecursiveRegistration(type);  // TocBridge_IKBaseGroup_RecursiveRegistration
    if (static_cast<uint32_t>(type) - 4u <= 3u) return;
    g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);  // vt+0x24
    m_pBonusCpnt->RecursiveRegistration(type);
    m_pStaticParticles->RecursiveRegistration(type);
    m_pCatchedParticles->RecursiveRegistration(type);
}

// 0x005b1fe8 CKGrpBonusPool_vf1C (vt+0x1c; the 0x10xx cases through the jump table 0x5b2090). The original computes a
// "handled" flag and returns it xor 1.
int32_t CKGrpBonusPool::MessageProc(uint16_t message, void* data) {
    const uint32_t high = (message >> 8) & 0xffu;
    const uint32_t low = message & 0xffu;
    if (high == 0x0e) {
        if (low == 3 || low == 2) {
            // engine +0x90 (the level) +0x1b: the low byte of the current sector
            SetSectorBeaconBits(static_cast<uint8_t>(g_pEngine->m_level->m_currentSector), low == 3 ? 1 : 0);  // vt+0x10c
            return 0;
        }
        if (low == 4) {
            m_bitArray = (m_bitArray & ~0x100u) | (static_cast<uint32_t>(*static_cast<const uint8_t*>(data)) << 8);
            return 0;
        }
        return 1;
    }
    if (high != 0x10 || low > 4) return 1;
    CKSrvBeacon::SKBeaconMsg* msg = static_cast<CKSrvBeacon::SKBeaconMsg*>(data);
    switch (low) {
    case 0: {  // 0x005b2170: the beacons written, four half-words each, low byte first (the PS3's lhbrx; here the
               // values are in host order already)
        IKFile* file = msg->m_pFile;
        const CKSrvBeacon::CKBeaconSet* set = msg->m_pBeaconSet;
        while (--msg->m_ui32NbBeacons != 0xffffffffu) {
            ++msg->m_ai16Accessor[3];
            const uint8_t* beacon = msg->m_pvBeacon;
            msg->m_pvBeacon = msg->m_pvBeacon + set->m_ui8VolatileSizeBytes;
            for (int i = 0; i < 4; ++i) file->Write(beacon + i * 2, 2);  // vt+0x20
        }
        return 0;
    }
    case 1: {  // 0x005b22c4. BUG(original): the iterator advances by one beacon only, though all of them are read.
        uint8_t* beacons = msg->m_pvBeacon;
        ++msg->m_ai16Accessor[3];
        msg->m_pvBeacon = beacons + msg->m_pBeaconSet->m_ui8VolatileSizeBytes;
        const uint32_t halves = msg->m_ui32NbBeacons * 4;
        msg->m_pFile->Read(beacons, msg->m_ui32NbBeacons << 3);  // vt+0x14
        uint16_t* values = reinterpret_cast<uint16_t*>(beacons);
        for (uint32_t i = 0; i < halves; ++i) {
            const uint8_t* b = reinterpret_cast<const uint8_t*>(&values[i]);
            values[i] = static_cast<uint16_t>(b[0] | (b[1] << 8));  // lhbrx: the file is little-endian
        }
        return 0;
    }
    case 2:  // 0x005b235c (the data argument's low byte)
        Vf110(static_cast<uint8_t>(reinterpret_cast<uintptr_t>(data)));  // vt+0x110
        return 0;
    case 3:  // 0x005b238c
        Vf114(static_cast<uint8_t>(reinterpret_cast<uintptr_t>(data)));  // vt+0x114
        return 0;
    default:  // 4: 0x005b23a0
        ReleaseBeaconed();  // vt+0x108
        Vf118();            // vt+0x118
        return 0;
    }
}
