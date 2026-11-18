// CKHkCrumblyZone.cpp - reconstructed original translation unit 0x405608-0x410190 (GAME_TOC1, main_toc1), 50 functions, 46 live.
// Primary class: CKHkCrumblyZone  key 0x1982  category Hook  size 0x1bc  vtable 0xb257b0
// Other owners: CKSrvBonus (1), CKHkS08CrumblyZone (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x405608  CKHkCrumblyZone_Delete  (DOTD_DECLARE_FACTORIES)
//   [x] 0x405658  CKHkCrumblyZone_IsDestroyedProperty_maybe  (the accessor of id 0x4f in GetInfo)
//   [ ] 0x405668  RegisterCKHkCrumblyZoneClass
//   [ ] 0x4056e0  _GLOBAL__I_4056e0
//   [ ] 0x4056f0  CKSrvBonus_SpawnBonuses_ViaEngine_maybe  [dead]
//   [x] 0x405720  CKHkCrumblyZone_CollapseAndSpawnBonuses_maybe
//   [x] 0x4057b0  CKHkS08CrumblyZone_IsInCameraView_maybe
//   [ ] 0x405930  CKHkCrumblyZone_UpdateAnimation_maybe  [dead: no pointer to its descriptor 0xbb49f8, no call]
//   [ ] 0x405a18  CKHkCrumblyZone_IsAnimEndReached_maybe  [dead]
//   [ ] 0x405a48  CKHkCrumblyZone_UpdateResetAnim_maybe  [dead: no pointer to its descriptor 0xbb4a08, no call]
//   [ ] 0x405ae8  CKHkCrumblyZone_AddRumbleRequestKind1_maybe  [dead]
//   [x] 0x405b40  CKHkCrumblyZone_SetGroundSets_maybe
//   [x] 0x405c30  CKHkCrumblyZone_CountHeroesOnZone_maybe
//   [x] 0x405d18  CKHkCrumblyZone_PickRandomStageMotionTargetByMode_maybe
//   [x] 0x406080  CKHkCrumblyZone_PostLoad
//   [x] 0x406128  CKHkCrumblyZone_DeleteArray  (DOTD_DECLARE_FACTORIES)
//   [x] 0x4061c8  CKHkCrumblyZone_Create
//   [x] 0x406278  CKHkCrumblyZone_GetHitPointsProperty_maybe  (the accessor of id 0x50 in GetInfo)
//   [x] 0x406280  CKHkCrumblyZone_IsIntactProperty_maybe  (the accessor of id 0x4e in GetInfo)
//   [x] 0x406290  CKHkCrumblyZone_SetDefaultState
//   [x] 0x406308  CKHkCrumblyZone_SetGameState
//   [x] 0x406398  CKHkCrumblyZone_Destroy
//   [x] 0x406410  CKHkCrumblyZone_UpdateStageNodeMotion_maybe
//   [x] 0x406810  CKHkCrumblyZone_RecursiveRegistration
//   [x] 0x406c20  CKHkCrumblyZone_GetInfo
//   [ ] 0x406d88  CKHkCrumblyZone_AddRumbleRequestKind0_maybe  [dead]
//   [x] 0x406de0  CKHkCrumblyZone_Start
//   [x] 0x406f90  CKHkCrumblyZone_ShowStageNode
//   [x] 0x407168  CKHkCrumblyZone_CreateArray  (DOTD_DECLARE_FACTORIES)
//   [x] 0x4072a8  CKHkCrumblyZone_vfF8
//   [x] 0x407410  CKHkCrumblyZone_PlaceEffectNodeB0_maybe
//   [x] 0x407648  CKHkCrumblyZone_PlaceEffectNodeB8_maybe
//   [x] 0x407880  CKHkCrumblyZone_TriggerCollapse_maybe
//   [x] 0x4082f8  CKHkCrumblyZone_ResetStageRecursive_maybe
//   [ ] 0x408538  CKHkCrumblyZone_ResetStagesWithAnim_maybe  [dead: no pointer to its descriptor 0xbb4c40, no call]
//   [x] 0x4085d8  CKHkCrumblyZone_Restore
//   [x] 0x408e58  CKHkCrumblyZone_ForceBroken_maybe
//   [x] 0x408fe8  CKHkCrumblyZone_Crumble
//   [x] 0x40aa28  CKHkCrumblyZone_UpdateCrumbleAnim_maybe
//   [x] 0x40aab8  CKHkCrumblyZone_StartCrumble_maybe
//   [x] 0x40abc0  CKHkCrumblyZone_ApplyHitDamageType4_maybe
//   [x] 0x40ae70  CKHkCrumblyZone_ApplyHitDamageType8_maybe
//   [x] 0x40b120  CKHkCrumblyZone_OnHit_maybe
//   [x] 0x40b500  CKHkCrumblyZone_MessageProc
//   [x] 0x40bcd8  CKHkCrumblyZone_OnDeactivate
//   [x] 0x40bf00  CKHkCrumblyZone_OnActivate
//   [x] 0x40c2f8  CKHkCrumblyZone_Update
//   [x] 0x40c7d8  CKHkCrumblyZone_Restart
//   [x] 0x40ca50  CKHkCrumblyZone_Load
//   [ ] 0x40e6d0  CKHkCrumblyZone_Save
//
//   [x] 0x9c1178  CKHkCrumblyZone_IsKindOfClass  [inline]  (in the header)
//   [ ] 0x9c11d0  CKHkCrumblyZone_GetClassType  [inline]
//   [ ] 0x9c11d8  CKHkCrumblyZone_GetClassID  [inline]
//   [x] 0x9c11e0  CKHkCrumblyZone_vf100  [inline]
//   [ ] 0x9c11e8  CKHkCrumblyZone_Destructor  [inline]
//   [ ] 0x9c1388  CKHkCrumblyZone_DeletingDestructor  [inline]
//   [x] 0x9c1538  CKHkCrumblyZone_UpdatePathBlocking_maybe  [inline]
#include "k2000/hooks/CKHkCrumblyZone.h"
#include "k2000/ai/CKSrvPathFinding.h"
#include "k2000/scenegraph/CAnimatedNode.h"
#include "k2000/graphical/animation/CAnimationManager.h"
#include "k2000/dictionaries/CAnimationDictionary.h"

#include <cmath>
#include <cstring>

#include "Renderware/rwcore/RwCamera.h"
#include "k2000/components/CKBonusData.h"
#include "k2000/components/CKCrumblyZoneCpnt.h"
#include "k2000/components/CKQuakeCpntUpdater.h"
#include "k2000/core/IKInfo.h"
#include "k2000/geometry/CGeometry.h"
#include "k2000/logic/render/CMaterial.h"
#include "k2000/scenegraph/CNode.h"
#include "Renderware/rwcore/RwMatrix.h"
#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/Mat4.h"
#include "crt/ppc_ops.h"
#include "crt/xsinf.h"
#include "k2000/dictionaries/CKSoundDictionaryID.h"
#include "k2000/fx/IKFx.h"
#include "k2000/logic/CKProjectileAccessor.h"
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/logic/IKFxData.h"
#include "k2000/logic/fx/CKExplosionNodeFx.h"
#include "k2000/logic/sound/CKSound.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/scenegraph/IKBoundingVolume.h"
#include "k2000/cameras/CKSrvCamera.h"
#include "k2000/math/Math.h"
#include "k2000/scenegraph/CParticlesNodeFx.h"
#include "k2000/system/IKTime.h"
#include "Renderware/rpprtstd/RpPrtStd.h"
#include "Renderware/rpprtstd/RpPrtStdRuntime.h"
#include "k2000/services/CKSrvCollision.h"
#include "k2000/services/CKSrvFx.h"
#include "k2000/services/CTriggerStarter.h"
#include "k2000/services/KBase201.h"
#include "k2000/misc/Engine.h"
#include "k2000/services/CKSrvCollision.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/scenegraph/CSGBranch.h"
#include "k2000/services/ICollisionMesh.h"
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "Spyro2008/groups/IKGrpHero.h"
#include "k2000/scenegraph/CSGLeaf.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/scenegraph/IKBoundingVolume.h"

namespace {

void ReadVec3(IKFile* file, float* v) {
    for (int i = 0; i < 3; ++i) ReadF32LE(file, &v[i]);
}

// The ground list load: the old nodes go back to the pool, then count references, each pushed to the
// front of the list (so the list ends up in reverse file order).
void LoadGroundList(IKFile* file, CKHkCrumblyZone::GroundNode*& head) {
    CKHkCrumblyZone::GroundNode* node = head;
    while (node != nullptr) {
        CKHkCrumblyZone::GroundNode* next = node->m_pNext;
        delete node;  // back to the FreeListPool (TOC+0x49a8) in the original
        node = next;
    }
    head = nullptr;
    uint32_t count = 0;
    ReadU32LE(file, &count);
    for (uint32_t i = 0; i < count; ++i) {
        IKSerializable* ground = nullptr;
        IKFile_ReadRef(file, &ground);
        node = new CKHkCrumblyZone::GroundNode();  // FreeListPool (TOC+0x49a8) in the original
        node->m_pNext = nullptr;
        node->m_pGround = ground;
        node->m_pNext = head;
        head = node;
    }
}

// The inlined TVector<T, 1> sizing of the +0x7c and +0x88 vectors: capacity = count (1 when 0) and a block
// for it; the grow branch cannot run. The length is set only when the count is not 0.
template <class T>
void LoadReserve1(TVector<T, 1>& v, uint32_t count) {
    if (count == 0) {
        v.m_ui32NbElt = 1;
        v.m_pBlock = static_cast<T*>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(T))));
        return;
    }
    v.m_ui32NbElt = count;
    v.m_pBlock = static_cast<T*>(Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(T))));
    if (v.m_ui32NbElt < count) {
        uint32_t capacity = count + 1;
        v.m_pBlock = static_cast<T*>(Mem_ReallocAligned16(v.m_pBlock, capacity * static_cast<uint32_t>(sizeof(T))));
        v.m_ui32NbElt = capacity;
    }
    v.m_ui32NbUsedElt = count;
}

}  // namespace

// 0x0040ca50 CKHkCrumblyZone_Load
int32_t CKHkCrumblyZone::Load(IKFile* file, int32_t type) {
    CKHkActorBase::Load(file, type);
    m_unk150 = 0;
    m_unk14C = 0;
    if (type != K_LEVEL_PLATEFORMS) return 1;
    IKFile_ReadRef(file, &m_pSoundDico);
    IKFile_ReadRef(file, &m_pGround);
    IKFile_ReadRef(file, &m_pSafeLeaf);
    IKFile_ReadRef(file, &m_pBrokenLeaf);
    IKFile_ReadRef(file, &m_pUnkC4);
    IKFile_ReadRef(file, &m_pUnkB0);
    IKFile_ReadRef(file, &m_pUnkB8);
    ReadU32LE(file, &m_unkC8);
    ReadVec3(file, m_afUnkCC);
    ReadVec3(file, m_afUnkD8);
    ReadU16LE(file, &m_unk12A);
    m_tsUnk134.Load(file, K_LEVEL_PLATEFORMS);
    m_tsUnk13C.Load(file, K_LEVEL_PLATEFORMS);
    ReadU32LE(file, &m_unk58);
    ReadU32LE(file, &m_unk5C);
    float unk54 = 0.0f;
    ReadF32LE(file, &unk54);
    ReadU32LE(file, &m_unk154);
    ReadU32LE(file, &m_flags158);
    ReadU32LE(file, &m_unk150);
    ReadU32LE(file, &m_unk14C);
    m_fUnk54 = unk54;
    // BUG(original): +0x18a is copied before it is read below, so +0x188 gets what the allocation held.
    m_unk188 = m_unk18A;
    m_flags158 = (m_flags158 & ~0x1000u) | (((m_flags158 >> 11) & 1u) << 12);
    IKFile_ReadRef(file, &m_pBrokenGround);
    ReadU32LE(file, &m_unkB4);
    ReadU32LE(file, &m_unk15C);
    ReadU32LE(file, &m_unk160);
    ReadU32LE(file, &m_unk164);
    ReadU8(file, &m_unk168);
    LoadGroundList(file, m_lAddedSafeGround);
    LoadGroundList(file, m_lAddedBrokenGround);
    IKFile_ReadRef(file, &m_pUnk9C);
    ReadU32LE(file, &m_unkBC);
    ReadU32LE(file, &m_unkC0);
    ReadU8(file, &m_unk16B);
    ReadU8(file, &m_unk16C);
    ReadU32LE(file, &m_unk170);
    ReadU8(file, &m_unk174);
    ReadU8(file, &m_unk175);
    ReadU32LE(file, &m_unk178);
    IKFile_ReadRef(file, &m_pUnk17C);
    ReadU32LE(file, &m_unk184);
    ReadU32LE(file, &m_unk12C);
    ReadU32LE(file, &m_unk130);
    ReadU16LE(file, &m_unk18A);
    ReadU16LE(file, &m_unk18C);
    ReadU16LE(file, &m_unk18E);
    ReadU32LE(file, &m_unk190);
    ReadU32LE(file, &m_unk194);
    ReadU32LE(file, &m_unk198);
    ReadU32LE(file, &m_unk19C);

    // +0x1a0: TVector<IKSerializable*, 10>, one array read.
    uint32_t count = 0;
    ReadU32LE(file, &count);
    if (count == 0) {
        m_vUnk1A0.m_ui32NbElt = 1;
        m_vUnk1A0.m_pBlock = static_cast<IKSerializable**>(Mem_AllocAligned16(sizeof(IKSerializable*)));
    } else {
        m_vUnk1A0.m_ui32NbElt = count;
        m_vUnk1A0.m_pBlock = static_cast<IKSerializable**>(
            Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(IKSerializable*))));
    }
    if (m_vUnk1A0.m_ui32NbElt < count) {
        uint32_t capacity = (count / 10) * 10 + 10;
        if (capacity == 0) capacity = 10;
        m_vUnk1A0.m_pBlock = static_cast<IKSerializable**>(Mem_ReallocAligned16(
            m_vUnk1A0.m_pBlock, capacity * static_cast<uint32_t>(sizeof(IKSerializable*))));
        m_vUnk1A0.m_ui32NbElt = capacity;
    }
    m_vUnk1A0.m_ui32NbUsedElt = count;
    IKFile_ReadObjectRefArray(file, m_vUnk1A0.m_pBlock, count);

    ReadVec3(file, m_afUnkE4);
    ReadVec3(file, m_afUnkF0);
    IKFile_ReadRef(file, &m_pUnk10C);
    ReadU8(file, &m_ui8NbUnk1AC);
    m_apUnk1AC = new IKSerializable*[m_ui8NbUnk1AC];  // OperatorNewArray
    IKFile_ReadObjectRefArray(file, m_apUnk1AC, m_ui8NbUnk1AC);
    IKFile_ReadRef(file, &m_pUnk6C);
    IKFile_ReadRef(file, &m_pUnk70);

    // +0x7c: references, one read each.
    ReadU32LE(file, &count);
    LoadReserve1(m_vUnk7C, count);
    for (uint32_t i = 0; i < count; ++i) IKFile_ReadRef(file, &m_vUnk7C.m_pBlock[i]);

    // +0x88: a word and a reference each.
    ReadU32LE(file, &count);
    LoadReserve1(m_vUnk88, count);
    for (uint32_t i = 0; i < count; ++i) {
        ReadU32LE(file, &m_vUnk88.m_pBlock[i].m_unk0);
        IKFile_ReadRef(file, &m_vUnk88.m_pBlock[i].m_pUnk4);
    }

    // +0xa4: capacity 1 and a one-element block whatever the count, grown to count + 1 when the count is
    // above 1; the length is set only when the count is not 0.
    ReadU32LE(file, &count);
    m_vUnkA4.m_ui32NbElt = 1;
    m_vUnkA4.m_pBlock = static_cast<Entry14*>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(Entry14))));
    if (count != 0) {
        if (m_vUnkA4.m_ui32NbElt < count) {
            uint32_t capacity = count + 1;
            m_vUnkA4.m_pBlock = static_cast<Entry14*>(
                Mem_ReallocAligned16(m_vUnkA4.m_pBlock, capacity * static_cast<uint32_t>(sizeof(Entry14))));
            m_vUnkA4.m_ui32NbElt = capacity;
        }
        m_vUnkA4.m_ui32NbUsedElt = count;
    }
    for (uint32_t i = 0; i < count; ++i) {
        Entry14& entry = m_vUnkA4.m_pBlock[i];
        IKFile_ReadRef(file, &entry.m_pUnk0);
        ReadVec3(file, entry.m_afUnk4);
        ReadU8(file, &entry.m_unk10);
    }

    IKFile_ReadRef(file, &m_pUnkFC);
    ReadU8(file, &m_unk110);
    ReadU32LE(file, &m_unk11C);
    ReadU32LE(file, &m_unk114);
    ReadU8(file, &m_unk118);
    ReadU8(file, &m_ui8NbUnk1B4);
    if (m_ui8NbUnk1B4 == 0) {
        m_apUnk1B4 = nullptr;
    } else {
        m_apUnk1B4 = static_cast<IKSerializable**>(
            Mem_AllocAligned16(m_ui8NbUnk1B4 * static_cast<uint32_t>(sizeof(IKSerializable*))));
        IKFile_ReadObjectRefArray(file, m_apUnk1B4, m_ui8NbUnk1B4);
    }
    ReadU8(file, &m_unk169);
    ReadU8(file, &m_unk16A);
    IKFile_ReadRef(file, &m_pUnk100);
    IKFile_ReadRef(file, &m_pUnk104);
    ReadU32LE(file, &m_unk108);
    ReadU32LE(file, &m_unk94);
    return 1;
}

// 0x00406080 CKHkCrumblyZone_PostLoad: CKHkActorBase_d82_maybe_PostLoad 0x3f6e70 -> IKLife_PostLoad 0x19f68 (level
// type only: bit 2 of the bit array); for the level type two RwMatrixCreate_Thunk matrices (+0x74, +0x78); then the
// PostLoads of the two trigger starters (+0x134, +0x13c: they return 1).
int32_t CKHkCrumblyZone::PostLoad(int32_t type) {
    if (type == K_LEVEL_PLATEFORMS) m_bitArray = (m_bitArray & 0xfffffffbu) | 4u;
    if (type == K_LEVEL_PLATEFORMS) {
        m_pUnk74[0] = RwMatrixCreate_Thunk();
        m_pUnk74[1] = RwMatrixCreate_Thunk();
    }
    m_tsUnk134.PostLoad(type);
    m_tsUnk13C.PostLoad(type);
    return 1;
}

// 0x00406290 CKHkCrumblyZone_SetDefaultState
void CKHkCrumblyZone::SetDefaultState(int32_t flag) {
    CKHkActorBase::SetDefaultState(flag);
    m_unk188 = m_unk18A;
    m_unk1B8 = static_cast<uint8_t>(m_ui8NbUnk1B4 + 1);
    m_flags158 = (m_flags158 & ~0x1000u) | (((m_flags158 >> 11) & 1) << 12);
}

// 0x00406308 CKHkCrumblyZone_SetGameState: info 1 only (0 otherwise). State 0: the hit points (+0x188 = +0x18a),
// the stage counter (+0x1b8 = stage count + 1) and flag bit 12 = bit 11, as SetDefaultState. Any other state: the
// zone is broken (+0x188 = 0, +0x1b8 = 0). Returns 1 for info 1.
int32_t CKHkCrumblyZone::SetGameState(const SApplyGameState* state) {
    if (state->m_ui32InfoId != 1) return 0;
    if (state->m_ui32GameStateId == 0) {
        m_unk188 = m_unk18A;
        m_unk1B8 = static_cast<uint8_t>(m_ui8NbUnk1B4 + 1);
        m_flags158 = (m_flags158 & ~0x1000u) | (((m_flags158 >> 11) & 1u) << 12);
    } else {
        m_unk188 = 0;
        m_unk1B8 = 0;
    }
    return 1;
}

// 0x00406de0 CKHkCrumblyZone_Start. Flags bits 9 and 10 cleared, every volume of the +0xa4 list switched off,
// then bit moves in the two flag words (rlwimi chains in the original; the sources are never targets):
// +0x154 bit 22 -> 19, 23 -> 20, 24 -> 0, 25 -> 1 (bit 24 is the low bit of its first byte); +0xc bit 15 ->
// 13, 16 -> 14.
void CKHkCrumblyZone::Start() {
    m_bitArray &= 0xfffff9ffu;
    CKSrvCollision* collision = static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision);
    for (uint32_t i = 0; i < m_vUnkA4.m_ui32NbUsedElt; ++i) {
        collision->DisableVolume(static_cast<IKBoundingVolume*>(m_vUnkA4.m_pBlock[i].m_pUnk0));
    }
    const uint32_t f = m_unk154;
    uint32_t r = f;
    r = (r & ~(1u << 19)) | (((f >> 22) & 1) << 19);
    r = (r & ~(1u << 20)) | (((f >> 23) & 1) << 20);
    r = (r & ~(1u << 0)) | (((f >> 24) & 1) << 0);
    r = (r & ~(1u << 1)) | (((f >> 25) & 1) << 1);
    m_unk154 = r;
    const uint32_t g = m_bitArray;
    uint32_t h = g;
    h = (h & ~(1u << 13)) | (((g >> 15) & 1) << 13);
    h = (h & ~(1u << 14)) | (((g >> 16) & 1) << 14);
    m_bitArray = h;
    m_unk144[1] = m_unk150;
    m_unk144[0] = m_unk14C;
    m_unk154 &= 0xeffffff7u;
    m_unk128 = 1;
    m_fUnk120 = 0.0f;  // an integer 0 store
    m_unk124 = 0;
    CKHkActorBase::Start();
}

namespace {
CSGLeaf* Leaf(IKSerializable* node) { return static_cast<CSGLeaf*>(node); }
void Hide(IKSerializable* node) { Leaf(node)->m_sgProperties = (Leaf(node)->m_sgProperties & 0xfffffffbu) | 4u; }
void Show(IKSerializable* node) { Leaf(node)->m_sgProperties &= 0xfffffffbu; }
}  // namespace

// 0x0040c7d8 CKHkCrumblyZone_Restart (vt+0x54): flag bits 9-10 cleared, the regrowth timer and the bonus data reset (the
// regrowth count too with +0x118), every +0xa4 volume switched off; then, unless the life flag bit 2: a zone without hit
// points (+0x188) shows its broken leaf with its grounds unsafe, any other its safe leaf with its volumes under the zone's
// node and switched on and its grounds safe; with +0x154 bit 3 the safe leaf gets the kept matrix (+0x78) back. Last,
// +0x154 bits 3 and 28 cleared.
void CKHkCrumblyZone::Restart() {
    m_bitArray &= 0xfffff9ffu;  // rlwinm 21,2,31 / 11,0,31
    m_fUnk120 = 0.0f;  // an integer 0 store
    static_cast<CKBonusData*>(m_pUnk10C)->ResetRuntime();  // 0x00126d90
    if (m_unk118 != 0) m_unk124 = 0;
    CKSrvCollision* collision = static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision);
    for (uint32_t i = 0; i < m_vUnkA4.m_ui32NbUsedElt; ++i) {
        collision->DisableVolume(static_cast<IKBoundingVolume*>(m_vUnkA4.m_pBlock[i].m_pUnk0));  // 0x001920e8
    }
    if ((m_bitArray & 4u) == 0) {
        if (m_unk188 == 0) {
            ShowStageNode(m_pBrokenLeaf);
            SetGroundSets(0);       // 0x00405b40
            UpdatePathBlocking(0);  // 0x009c1538
        } else {
            ShowStageNode(m_pSafeLeaf);
            for (uint32_t i = 0; i < m_vUnkA4.m_ui32NbUsedElt; ++i) {
                CSGLeaf* volume = static_cast<CSGLeaf*>(m_vUnkA4.m_pBlock[i].m_pUnk0);
                if (volume->m_pParent != nullptr) volume->m_pParent->RemoveChild(volume);  // vt+0x78
                static_cast<CSGBranch*>(m_pKGLObject)->AddChild(volume);                   // vt+0x70
                collision->EnableVolume(static_cast<IKBoundingVolume*>(m_vUnkA4.m_pBlock[i].m_pUnk0));  // 0x00192090
            }
            SetGroundSets(1);
            UpdatePathBlocking(0);  // 0x009c1538
        }
        if ((m_unk154 & 8u) != 0) {
            static_cast<CSGMovable*>(m_pSafeLeaf)->SetLocalMatrix(reinterpret_cast<const RwMatrix*>(m_pUnk74[1]));  // 0x000d0be8
        }
    }
    m_unk154 &= 0xeffffff7u;
}

// 0x00406f90 CKHkCrumblyZone_ShowStageNode. The safe leaf (+0x34) shown: the broken leaf (+0x38) hidden. The broken
// leaf shown: the safe one hidden, and the broken leaf's frame moved to the safe leaf's position (its modelling
// matrix loses the identity flag 0x20000, the frame is marked dirty). Any other node: both hidden. Then every node of
// the stage list (+0x1b4, +0x1b1 entries) is shown when it is `node` and hidden otherwise. The safe leaf is not
// tested for null (the original's loads).
void CKHkCrumblyZone::ShowStageNode(IKSerializable* node) {
    if (node == m_pSafeLeaf) {
        Show(node);
        if (m_pBrokenLeaf != nullptr) Hide(m_pBrokenLeaf);
    } else if (m_pBrokenLeaf == node) {
        Hide(m_pSafeLeaf);
        if (m_pBrokenLeaf != nullptr) {
            Show(m_pBrokenLeaf);
            const RwFrame* from = static_cast<CSGMovable*>(m_pSafeLeaf)->m_pRwFrame;
            RwFrame* to = static_cast<CSGMovable*>(m_pBrokenLeaf)->m_pRwFrame;
            to->modelling.pos.z = from->modelling.pos.z;
            to->modelling.pos.x = from->modelling.pos.x;
            to->modelling.pos.y = from->modelling.pos.y;
            to->modelling.flags &= 0xfffdffffu;
            RwFrame_MarkDirty(to);  // 0x00010698
        }
    } else {
        Hide(m_pSafeLeaf);
        if (m_pBrokenLeaf != nullptr) Hide(m_pBrokenLeaf);
    }
    for (int32_t i = 0; i < static_cast<int32_t>(m_ui8NbUnk1B4); ++i) {
        IKSerializable* stage = m_apUnk1B4[i];
        if (stage == node) {
            Show(stage);
        } else {
            Hide(stage);
        }
    }
}

// 0x0040bf00 CKHkCrumblyZone_OnActivate (vt+0xa0, called by IKLife::SectorLoaded for the zone's sector). The scene
// node's modelling matrix is kept in the second PostLoad matrix (+0x78), the bonus data reset, flag bits 16 and 17
// cleared; a zone without hit points (+0x188) that is not marked 0x400 shows its broken leaf (flag bit 14 cleared),
// any other its safe leaf (a zone marked 0x400 also gets its hit points, stage counter and bit 12 back). With an
// animation (+0x17c) the two bytes +0x180 / +0x181 are cleared. Then +0x68 = the number of heroes whose ground is the
// zone's ground (+0x24), +0x128 = 1.
// First the actor base's (CKHkActorBase_d82_maybe_OnActivate 0x3f7338: the zone joins the meca group's active actor
// list). Each branch then updates the zone's path-finding boxes (CKHkCrumblyZone_UpdatePathBlocking_maybe 0x9c1538, 0).
// The collision side: a zone showing its safe leaf moves its +0xa4 volumes under the zone's node (the old parent's vt+0x78,
// the node's vt+0x70) and switches them on (CKSrvCollision_EnableVolume 0x192090), then its ground sets (SetGroundSets);
// +0x68 counts the heroes whose ground object (CKHkS08Hero_GetGroundObject_maybe 0x363c40) is the zone's ground +0x24.
// With an animation dictionary (+0x17c) the zone's node plays its first animation from 0 (CAnimatedNode_PlayAnim_maybe
// 0xc98b8, no restart).
// 0x0040bcd8 CKHkCrumblyZone_OnDeactivate (vt+0xa4; CKHkS08CrumblyZone's 0x414288 calls it): the actor base's, every
// +0xa4 volume switched off (CKSrvCollision_DisableVolume) and moved from its parent (vt+0x78) to the dynamic scene root
// (engine +0x14, vt+0x70), the two particle nodes (+0xb0 / +0xb8) stopped (scene flags 0x400 / 0x80000 and the emitter's
// emit flag cleared), the path-finding boxes freed; with +0x154 bit 3 the safe leaf gets the kept matrix (+0x78) back;
// the dictionary's sound 2 stopped.
void CKHkCrumblyZone::VfA4() {
    CKHkActorBase::VfA4();  // 0x003f7370
    CKSrvCollision* collision = static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision);
    for (uint32_t i = 0; i < m_vUnkA4.m_ui32NbUsedElt; ++i) {
        CSGLeaf* volume = static_cast<CSGLeaf*>(m_vUnkA4.m_pBlock[i].m_pUnk0);
        collision->DisableVolume(static_cast<IKBoundingVolume*>(volume));  // 0x001920e8
        if (volume->m_pParent != nullptr) volume->m_pParent->RemoveChild(volume);       // vt+0x78
        static_cast<CSGBranch*>(g_pEngine->m_dynamicSceneRoot)->AddChild(volume);       // vt+0x70
    }
    for (IKSerializable* node : {m_pUnkB8, m_pUnkB0}) {
        if (node == nullptr) continue;
        CParticlesNodeFx* particles = static_cast<CParticlesNodeFx*>(node);
        particles->m_sgProperties &= 0xfff7fbffu;
        particles->m_pRpPrtStdEmitter->flag &= ~static_cast<uint32_t>(rpPRTSTDEMITTERFLAGEMIT);
    }
    UpdatePathBlocking(0);  // 0x009c1538
    if ((m_unk154 & 8u) != 0) {
        static_cast<CSGMovable*>(m_pSafeLeaf)->SetLocalMatrix(reinterpret_cast<const RwMatrix*>(m_pUnk74[1]));  // 0x000d0be8
    }
    if (CKSoundDictionaryID_GetSound(static_cast<CKSoundDictionaryID*>(m_pSoundDico), 2) != nullptr) {  // 0x00112bc0
        Sound_Stop(CKSoundDictionaryID_GetSound(static_cast<CKSoundDictionaryID*>(m_pSoundDico), 2), 0);  // 0x001111b0
    }
}

void CKHkCrumblyZone::VfA0() {
    CKHkActorBase::VfA0();  // 0x003f7338
    const RwFrame* frame = static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame;
    std::memcpy(m_pUnk74[1], &frame->modelling, sizeof(CMatrix34));
    static_cast<CKBonusData*>(m_pUnk10C)->ResetRuntime();  // 0x00126d90
    m_flags158 &= 0xfffcffffu;
    CKSrvCollision* collision = static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision);
    if (m_unk188 == 0 && (m_flags158 & 0x400) == 0) {
        ShowStageNode(m_pBrokenLeaf);
        SetGroundSets(0);       // 0x00405b40
        UpdatePathBlocking(0);  // 0x009c1538
        m_flags158 &= 0xffffbfffu;
    } else {
        ShowStageNode(m_pSafeLeaf);
        for (uint32_t i = 0; i < m_vUnkA4.m_ui32NbUsedElt; ++i) {
            CSGLeaf* volume = static_cast<CSGLeaf*>(m_vUnkA4.m_pBlock[i].m_pUnk0);
            if (volume->m_pParent != nullptr) volume->m_pParent->RemoveChild(volume);    // vt+0x78
            static_cast<CSGBranch*>(m_pKGLObject)->AddChild(volume);                     // vt+0x70
            collision->EnableVolume(static_cast<IKBoundingVolume*>(m_vUnkA4.m_pBlock[i].m_pUnk0));  // 0x00192090
        }
        SetGroundSets(1);       // 0x00405b40
        UpdatePathBlocking(0);  // 0x009c1538
        if ((m_flags158 & 0x400) != 0) {
            m_unk188 = m_unk18A;
            m_unk1B8 = static_cast<uint8_t>(m_ui8NbUnk1B4 + 1);
            m_flags158 = (m_flags158 & 0xffffefffu) | (((m_flags158 >> 11) & 1u) << 12);
        }
    }
    if (m_pUnk17C != nullptr) {
        m_unk181 = 0;
        m_unk180 = 0;
        const uint32_t first = static_cast<uint32_t>(static_cast<CAnimationDictionary*>(m_pUnk17C)->m_apAnimations[0]);
        static_cast<CAnimatedNode*>(m_pKGLObject)->PlayAnim(0.0, first, 0);  // TOC +0x497c: 0.0f
    }
    uint8_t standing = 0;
    IKGrpHero* group = static_cast<IKGrpHero*>(g_pEngine->m_gameManager->m_unk04[1]);  // the hero group (game manager +0x8)
    if (group != nullptr && m_pGround != nullptr) {
        for (IKSerializable** hero = group->m_apHeroesCopy; *hero != nullptr; ++hero) {  // 0x002ca0f0 (+0x3c)
            if (static_cast<CKHkS08Hero*>(*hero)->GetGroundObject() == m_pGround) ++standing;  // 0x00363c40
        }
    }
    m_unk68 = standing;
    m_unk128 = 1;
}

// 0x00405b40 CKHkCrumblyZone_SetGroundSets_maybe
void CKHkCrumblyZone::SetGroundSets(uint8_t safe) {
    if (m_pGround != nullptr) static_cast<ICollisionMesh*>(m_pGround)->SetActive(safe);
    for (GroundNode* node = m_lAddedSafeGround; node != nullptr; node = node->m_pNext) {
        static_cast<ICollisionMesh*>(node->m_pGround)->SetActive(safe);
    }
    if (m_pBrokenGround != nullptr) static_cast<ICollisionMesh*>(m_pBrokenGround)->SetActive(static_cast<uint16_t>(safe ^ 1));
    for (GroundNode* node = m_lAddedBrokenGround; node != nullptr; node = node->m_pNext) {
        static_cast<ICollisionMesh*>(node->m_pGround)->SetActive(static_cast<uint16_t>(safe ^ 1));
    }
}

namespace {
float HitWordAsFloat(uint32_t word) {
    float value;
    std::memcpy(&value, &word, sizeof value);
    return value;
}

// The block of the hero's hazard query 0xc32 (CKHkS08Hero_6.cpp's HazardHitQuery, the same layout).
struct ZoneHazardQuery {
    IKSerializable* m_hero;      // +0x00
    IKBoundingVolume* m_volume;  // +0x04
    uint32_t m_dirX;             // +0x08 (a float)
    uint32_t m_dirZ;             // +0x0c (a float)
    uint32_t m_unk10;            // +0x10
    CVector3 m_point;            // +0x14
    int32_t m_kind;              // +0x20
    uint8_t m_damage;            // +0x24
};

IKGrpHero* HeroGroup() { return static_cast<IKGrpHero*>(g_pEngine->m_gameManager->m_unk04[1]); }  // engine +0x8c -> +0x08

// The index of the hero owning `volume` (GetHeroByDragonIndex 0x2ca080 from 0), the hero count when none does.
uint32_t HeroIndexOfVolume(IKGrpHero* group, const IKBoundingVolume* volume) {
    uint32_t index = 0;
    for (;;) {
        const uint32_t at = index;
        if (group->GetHeroCount() <= at) return at;                                    // 0x002ca038
        if (volume->m_pOwner == group->m_apHeros[at & 0xffu]) return at;               // 0x002ca080
        index = at + 1;
    }
}
}  // namespace

// 0x0040b500 CKHkCrumblyZone_MessageProc. The actor base's answer (CKHkActorBase_d82_maybe_MessageProc 0x3f7148, first) and
// the zone's merge: 3 from either wins, then 2, then 0 when the base answered 0, else the zone's. 0x996 answers 0 without
// the merge; 0x9a0 and unknown messages answer 1. The byte arguments of 0x996..0x999 / 0x99f are the block's first byte,
// the bit indices of 0x99a..0x99d a word's low byte.
int32_t CKHkCrumblyZone::MessageProc(uint16_t message, void* data) {
    const int32_t base = CKHkActorBase::MessageProc(message, data);  // 0x003f7148
    int32_t own = 0;
    switch (message) {
    case 0x300:    // the collision list of the zone's lives (CKSrvCollision_ProcessPairs): the other volume of each
    case 0x301: {  // the projectile collisions (the warned target's list): their first volume
        if ((m_flags158 & 0x20000u) != 0 || (m_flags158 & 0x10000u) != 0 || m_unk188 == 0) break;
        for (ICollision* collision = static_cast<ICollision*>(data); collision != nullptr;) {
            IKSerializable* other;
            if (message == 0x300 && static_cast<IKBoundingVolume*>(collision->GetBoundingVolume1())->m_pOwner == this) {
                other = collision->GetBoundingVolume2();  // vt+0x04
            } else {
                other = collision->GetBoundingVolume1();  // vt+0x00
            }
            OnHit(static_cast<IKBoundingVolume*>(other));  // vt+0xfc
            if (m_unk188 == 0) break;
            collision = collision->m_pNext;
        }
        break;
    }
    case 0x400: {
        SAimPointQuery* query = static_cast<SAimPointQuery*>(data);
        if (m_vUnk1A0.m_ui32NbUsedElt != 0) {
            query->m_pHotSpot = m_vUnk1A0.m_pBlock[query->m_ui8Index];
        } else {
            const RwFrame* frame = static_cast<CSGMovable*>(m_pSafeLeaf)->m_pRwFrame;
            Mat4_TransformPoints(reinterpret_cast<const CMatrix34*>(&frame->ltm), &query->m_point,
                                 reinterpret_cast<const CVector3*>(m_afUnkD8), 1);  // 0x0023f7e8
        }
        break;
    }
    case 0x401:  // the zone's ground, while it is in play (+0x0c bit 2 clear)
        if ((m_bitArray & 4u) == 0) *static_cast<IKSerializable**>(data) = m_pGround;
        break;
    case 0x402: {
        uint8_t* hittable = static_cast<uint8_t*>(data);
        if ((m_flags158 & 0x1000u) != 0 && m_unk188 != 0) {
            *hittable = 1;
            const uint32_t grounds = m_vUnk1A0.m_ui32NbUsedElt;  // +0x1a8
            if (grounds != 0) *hittable = static_cast<uint8_t>(grounds);
        } else {
            *hittable = 0;
        }
        break;
    }
    case 0x900:
        if ((m_bitArray & 4u) == 0) Restore();  // 0x004085d8
        break;
    case 0x901:
        // The crumble at the zone's node (its stored LTM position) while it has hit points (+0x188).
        if (m_unk188 != 0) {
            const RwMatrix* ltm = FrameLtm(static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame);
            const CVector3 at = {ltm->pos.x, ltm->pos.y, ltm->pos.z};
            StartCrumble(&at, 0);  // 0x0040aab8
        }
        break;
    case 0x902: {
        // Reset, and the regrowth animation (entry 1 of the dictionary +0x17c) crossfaded in (+0x180 = 1, flag 0x10000).
        ResetStageRecursive();  // 0x004082f8
        CAnimationDictionary* animations = static_cast<CAnimationDictionary*>(m_pUnk17C);
        if (animations == nullptr || CAnimationManager_GetAnimation(static_cast<uint32_t>(animations->m_apAnimations[1])) == nullptr) break;  // the original tests the resolved entry
        m_unk180 = 1;
        static_cast<CAnimatedNode*>(m_pSafeLeaf)
            ->CrossfadeToAnim(0.2f, 0.0f, static_cast<uint32_t>(animations->m_apAnimations[1]), 1);  // 0x000c8eb0, TOC +0x4a0c / +0x497c
        m_flags158 = (m_flags158 & ~0x10000u) | 0x10000u;
        break;
    }
    case 0x996:
        m_unk154 = (m_unk154 & ~0x80000u) | (static_cast<uint32_t>(*static_cast<const uint8_t*>(data)) << 19);
        return 0;
    case 0x997:
        m_unk154 = (m_unk154 & ~0x100000u) | (static_cast<uint32_t>(*static_cast<const uint8_t*>(data)) << 20);
        break;
    case 0x998:
        m_unk154 = (m_unk154 & ~1u) | *static_cast<const uint8_t*>(data);
        break;
    case 0x999:
        m_unk154 = (m_unk154 & ~2u) | (static_cast<uint32_t>(*static_cast<const uint8_t*>(data)) << 1);
        break;
    case 0x99a:  // a hero's kind-4 hit allowed (+0x148), 0x99b its kind-8 hit (+0x144); 0x99c / 0x99d forbidden
    case 0x99b: {
        uint32_t& mask = message == 0x99a ? m_unk144[1] : m_unk144[0];
        const uint32_t bit = ppc::slw(1u, static_cast<uint8_t>(*static_cast<const uint32_t*>(data)));
        mask = (mask & ~bit) | bit;
        break;
    }
    case 0x99c:
    case 0x99d: {
        uint32_t& mask = message == 0x99c ? m_unk144[1] : m_unk144[0];
        mask &= ppc::rotl32(0xfffffffeu, static_cast<uint8_t>(*static_cast<const uint32_t*>(data)));
        break;
    }
    case 0x99e:
        // Broken at once, with the child zones (+0x1ac) that still have hit points.
        if (m_unk188 == 0) break;
        ForceBroken();  // 0x00408e58
        for (uint32_t i = 0; static_cast<int32_t>(i) < static_cast<int32_t>(m_ui8NbUnk1AC); ++i) {
            CKHkCrumblyZone* zone = static_cast<CKHkCrumblyZone*>(m_apUnk1AC[i]);
            if (zone->m_unk188 != 0) zone->ForceBroken();
        }
        break;
    case 0x99f:
        m_flags158 = (m_flags158 & ~0x1000u) | (static_cast<uint32_t>(*static_cast<const uint8_t*>(data)) << 12);
        break;
    case 0x9a0:
        m_unk128 = 0;
        own = 1;
        break;
    case 0xc32: {
        // The hero's hazard query: the zone's knock direction, value and damage (+0x15c..+0x168) when Vf100 lets the hero
        // be hit, else no hit (kind 3); the origin at the hitting volume; a zone with +0x16a crumbles there.
        ZoneHazardQuery* query = static_cast<ZoneHazardQuery*>(data);
        if (Vf100(query->m_hero) != 0) {  // vt+0x100
            query->m_dirX = m_unk15C;
            query->m_dirZ = m_unk160;
            query->m_unk10 = m_unk164;
            query->m_damage = m_unk168;
        } else {
            query->m_unk10 = 0;
            query->m_damage = 0;
            query->m_kind = 3;
            query->m_dirX = 0;
            query->m_dirZ = 0;
        }
        if (query->m_volume != nullptr) {
            const RwMatrix* ltm = FrameLtm(query->m_volume->m_pRwFrame);
            query->m_point = {ltm->pos.x, ltm->pos.y, ltm->pos.z};
        }
        if (m_unk16A != 0) StartCrumble(&query->m_point, 0);  // 0x0040aab8
        break;
    }
    case 0x2668: {
        uint32_t* out = static_cast<uint32_t*>(data);
        out[0] = m_unk188;
        out[1] = m_unk18A;
        break;
    }
    default:
        own = 1;
        break;
    }
    if (base == 3 || own == 3) return 3;
    if (base == 2 || own == 2) return 2;
    return base == 0 ? 0 : own;
}

// 0x0040b120 CKHkCrumblyZone_OnHit_maybe
void CKHkCrumblyZone::OnHit(IKBoundingVolume* volume) {
    const uint16_t flags = volume->m_ui16PropertiesFlags;
    const uint32_t kind4 = flags & 4u;
    if (kind4 == 0 && (flags & 8u) == 0) return;
    if ((m_bitArray & 0x400u) != 0) return;
    uint32_t allow8;
    switch (volume->m_ui8OwnerType) {
    case 1:
        if ((m_unk154 & 1u) != 0 && kind4 != 0) return ApplyHitDamageType4(volume);
        allow8 = m_unk154 & 2u;
        break;
    case 2:
        if ((m_unk154 & 0x80000u) != 0 && kind4 != 0) return ApplyHitDamageType4(volume);
        allow8 = m_unk154 & 0x100000u;
        break;
    case 5:
        if ((m_bitArray & 0x2000u) != 0 && kind4 != 0) return ApplyHitDamageType4(volume);
        allow8 = m_bitArray & 0x4000u;
        break;
    case 3: {
        // A hero: every hero allowed (the masks +0x148 for kind 4, +0x144 for kind 8), or the volume's hero.
        IKGrpHero* group = HeroGroup();
        uint32_t all4 = 1;
        uint32_t all8 = 1;
        for (uint32_t i = 0; static_cast<uint32_t>(group->GetHeroCount()) > i; ++i) {  // 0x002ca038
            const uint32_t bit = ppc::slw(1u, i & 0xffu);
            if ((volume->m_ui16PropertiesFlags & 4u) != 0 && (bit & m_unk144[1]) == 0) all4 = 0;
            if ((volume->m_ui16PropertiesFlags & 8u) != 0 && (bit & m_unk144[0]) == 0) all8 = 0;
        }
        if ((volume->m_ui16PropertiesFlags & 4u) != 0) {
            if (all4 == 0) {
                const uint32_t index = HeroIndexOfVolume(group, volume) & 0xffu;
                if (group->GetHeroCount() <= index) return;
                if ((ppc::slw(1u, index) & m_unk144[1]) == 0) return;
            }
            return ApplyHitDamageType4(volume);
        }
        if ((volume->m_ui16PropertiesFlags & 8u) == 0) return;
        if (all8 == 0) {
            const uint32_t index = HeroIndexOfVolume(group, volume) & 0xffu;
            if (group->GetHeroCount() <= index) return;
            if ((ppc::slw(1u, index) & m_unk144[0]) == 0) return;
        }
        return ApplyHitDamageType8(volume);
    }
    default:
        return;
    }
    if (allow8 == 0 || (flags & 8u) == 0) return;
    ApplyHitDamageType8(volume);
}

// 0x0040abc0 CKHkCrumblyZone_ApplyHitDamageType4_maybe
void CKHkCrumblyZone::ApplyHitDamageType4(IKBoundingVolume* volume) { ApplyHitDamage(volume, m_unk18E); }

// 0x0040ae70 CKHkCrumblyZone_ApplyHitDamageType8_maybe
void CKHkCrumblyZone::ApplyHitDamageType8(IKBoundingVolume* volume) { ApplyHitDamage(volume, m_unk18C); }

// The body of both (two copies in the original). The contact history times: TOC +0x4a0c (0.2) and +0x4a1c (-1000).
void CKHkCrumblyZone::ApplyHitDamage(IKBoundingVolume* volume, uint16_t damage) {
    const uint16_t hits = m_unk188;
    m_bitArray = (m_bitArray & ~0x400u) | 0x400u;
    if (ContactHistory_Touch(0.2f, -1000.0f, &m_pContactHistory, volume, nullptr) == 0) return;  // TocBridge 0x98f380
    const RwMatrix* ltm = FrameLtm(volume->m_pRwFrame);
    const CVector3 at = {ltm->pos.x, ltm->pos.y, ltm->pos.z};
    uint16_t left;
    if ((m_bitArray & 0x40000000u) != 0) {
        left = hits;  // unbreakable
    } else if (hits > damage) {
        left = static_cast<uint16_t>(hits - damage);
    } else {
        if (IsInCameraView() != 0) StartCrumble(&at, 0);  // the test inlined, 0x0040aab8
        return;
    }
    CollapseAndSpawnBonuses(left, &at);  // inlined: the hit points, vt+0xf4 (mode 1), the bonuses at the safe leaf
}

// 0x00408e58 CKHkCrumblyZone_ForceBroken_maybe
void CKHkCrumblyZone::ForceBroken() {
    m_unk1B8 = 0;
    m_unk188 = 0;
    if ((m_bitArray & 4u) != 0) return;
    ShowStageNode(m_pBrokenLeaf);  // 0x00406f90
    SetGroundSets(0);              // 0x00405b40
    CKSrvCollision* collision = static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision);
    for (uint32_t i = 0; i < m_vUnkA4.m_ui32NbUsedElt; ++i) {
        collision->DisableVolume(static_cast<IKBoundingVolume*>(m_vUnkA4.m_pBlock[i].m_pUnk0));  // 0x001920e8
    }
    UpdatePathBlocking(0);  // 0x009c1538
    uint8_t* state = &static_cast<CKCrumblyZoneCpnt*>(m_pUnk9C)->m_unk0d;  // 2 becomes 3, else 1
    *state = *state == 2 ? 3 : 1;
    CKSoundDictionaryID* sounds = static_cast<CKSoundDictionaryID*>(m_pSoundDico);
    if (sounds->GetSound(2) != nullptr) sounds->GetSound(2)->Stop(0);  // 0x00112bc0, 0x001111b0
}

// 0x004085d8 CKHkCrumblyZone_Restore (message 0x900): after CKHkCrumblyZone::Crumble below (it shares its helpers).

// 0x004057b0 CKHkS08CrumblyZone_IsInCameraView_maybe
uint8_t CKHkCrumblyZone::IsInCameraView() const {
    if (!(HitWordAsFloat(m_unk198) >= 0.0f)) return 1;  // TOC +0x497c
    const RwMatrix* ltm = FrameLtm(static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame);
    const CKSrvCamera* camera = static_cast<CKSrvCamera*>(g_pEngine->m_srvCamera);
    const float dy = camera->m_v3RealPos.y - ltm->pos.y;
    const float dx = camera->m_v3RealPos.x - ltm->pos.x;
    const float dz = camera->m_v3RealPos.z - ltm->pos.z;
    const float distance = std::sqrt(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));  // 0x00010690
    const float farDistance = HitWordAsFloat(m_unk194);
    float radius;
    if (distance >= farDistance) {
        radius = HitWordAsFloat(m_unk190);
    } else {
        const float nearDistance = HitWordAsFloat(m_unk19C);
        if (distance <= nearDistance) {
            radius = HitWordAsFloat(m_unk198);
        } else {
            radius = (distance - nearDistance) * HitWordAsFloat(m_unk190) / (farDistance - nearDistance) +
                     HitWordAsFloat(m_unk198);
        }
    }
    // The original also stores radius^2 behind the sphere; the test reads (x, y, z, radius).
    const float sphere[4] = {ltm->pos.x, ltm->pos.y, ltm->pos.z, radius};
    return camera->TestSphereAgainstFrustum(sphere, 5) == 2 ? 1 : 0;  // 0x0012c830
}

namespace {

float WordAsFloat(uint32_t word) {
    float value;
    std::memcpy(&value, &word, sizeof value);
    return value;
}
bool SignBitSet(float x) {
    int32_t bits;
    std::memcpy(&bits, &x, 4);
    return bits < 0;
}
// The inlined cosf / sinf (the single-precision polynomials for a non-negative argument by its sign bit, the library's
// cosf 0x009a11d8 / sinf 0x009a1390 of the magnitude otherwise).
float GameCosf(float x) { return SignBitSet(x) ? crt::LibCosf(-x) : crt::InlineCosf(x); }
float GameSinf(float x) { return SignBitSet(x) ? -crt::LibSinf(-x) : crt::InlineSinf(x); }
// (u & 0xffff) x -3.0518044e-05 + 1 (TOC1 +0x4a10, +0x4998): a draw in -1..1.
float RandSigned() {
    const float u = static_cast<float>(static_cast<double>(static_cast<uint32_t>(Rand_Int()) & 0xffffu));
    return ppc::fmadds(u, -3.051804378628731e-05f, 1.0f);
}
const CVector3 kNullPoint = {0.0f, 0.0f, 0.0f};  // 0x00c50d64 (TOC1 +0x49b4)
bool IsNullPoint(const CVector3* p) { return kNullPoint.x == p->x && p->y == kNullPoint.y && p->z == kNullPoint.z; }

// The direction away from `from` in the horizontal plane (the zone's centre minus the point, normalised), turned by
// `angle`: (cos dx - sin dz, keep, sin dx + cos dz); the cos / sin are computed in the original's order.
void TurnAway(float angle, float dx, float dz, float* outX, float* outZ) {
    const float c0 = GameCosf(angle);
    const float s0 = GameSinf(angle);
    *outX = ppc::fmsubs(c0, dx, s0 * dz);
    const float s1 = GameSinf(angle);
    const float c1 = GameCosf(angle);
    *outZ = ppc::fmadds(s1, dx, c1 * dz);
}

// The launch matrix: the zone node's LTM rotation (with its flag and pad words) at the null position, the identity
// flag cleared (the identity stores before the copy are overwritten).
void LaunchMatrix(const RwMatrix* ltm, RwMatrix* out) {
    std::memcpy(out, ltm, sizeof *out);
    out->pos = {kNullPoint.x, kNullPoint.y, kNullPoint.z};
    out->flags &= 0xfffdffffu;
}

}  // namespace

// 0x00408fe8 CKHkCrumblyZone_Crumble: one stage of the zone breaks at `point` (the null point: no hit point).
// The stage counter (+0x1b8) steps down: a stage left shows its node (+0x1b4); the last one shows the broken leaf, puts
// the grounds to the broken set and disables the pieces' volumes. Then (with a projectile type, +0xc4) the life's
// piece count (bits 3-8) of debris launch from random points of the node's box (+0xcc along its axes from the centre
// +0xd8): with a hit point and the flag 0x20000 away from it in a random turn of +-22.5 degrees, else at the random
// speed +0xf0 around +0xe4 through the node's axes; the explosion data (+0xfc) explodes at the centre (+0x108 up),
// along the node's at or (life bit 31) away from the point; every hot spot (+0x88) launches its projectile turned
// within +0x94 degrees; the bonus table (+0x10c) spawns, with bit 11 toward +0xb0 (or the first piece) from the point,
// after the effect node (life bits 24-25: STUB); the crumble sound (life bit 26, not for a child). The last stage ends
// the zone: the end sound stopped, +0x134 fired, the hit points 0, the path blocking (STUB), +0x9c's +0x0d state, the
// child zones (+0x1ac) still standing crumble too (as children). Otherwise the hit points are restored (+0x18a).
void CKHkCrumblyZone::Crumble(const CVector3* point, uint8_t child) {
    m_flags158 &= ~0x30000u;
    const uint8_t stages = m_unk1B8;
    bool last = true;
    if (stages != 0) {
        m_unk1B8 = static_cast<uint8_t>(stages - 1);
        if (static_cast<uint8_t>(stages - 1) != 0) {
            ShowStageNode(m_apUnk1B4[static_cast<uint8_t>(stages - 1) - 1]);  // 0x00406f90
            last = false;
        }
    }
    if (last) {
        ShowStageNode(m_pBrokenLeaf);
        SetGroundSets(0);  // 0x00405b40
        CKSrvCollision* collision = static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision);
        for (uint32_t i = 0; i < m_vUnkA4.m_ui32NbUsedElt; ++i) {
            collision->DisableVolume(static_cast<IKBoundingVolume*>(m_vUnkA4.m_pBlock[i].m_pUnk0));  // 0x001920e8
        }
    }
    const RwFrame* frame = static_cast<CSGMovable*>(m_pSafeLeaf)->m_pRwFrame;
    const RwMatrix* ltm = FrameLtm(frame);  // the stored LTM (+0x50)
    CVector3 centre;
    Mat4_TransformPoints(reinterpret_cast<const CMatrix34*>(ltm), &centre, reinterpret_cast<const CVector3*>(m_afUnkD8), 1);
    CVector3 dir = {0.0f, 1.0f, 0.0f};  // +0x94..+0x9c: only its y is set here (1.0); the paths below write x / z
    CKProjectileAccessor* accessor = static_cast<CKProjectileAccessor*>(m_pUnkC4);
    if (accessor->m_pProjectileType != nullptr) {
        CMatrix34 inverse;
        Mat4_Invert(&inverse, reinterpret_cast<const CMatrix34*>(ltm));  // 0x0023f878 (not read afterwards)
        uint32_t pieces = (m_bitArray >> 3) & 0x3fu;
        while (pieces != 0) {
            --pieces;
            CVector3 pos = centre;
            float k = m_afUnkCC[0] * RandSigned();
            pos.z = ppc::fmadds(k, ltm->right.z, pos.z);
            pos.x = ppc::fmadds(k, ltm->right.x, pos.x);
            pos.y = ppc::fmadds(k, ltm->right.y, pos.y);
            k = m_afUnkCC[1] * RandSigned();
            pos.z = ppc::fmadds(k, ltm->up.z, pos.z);
            pos.x = ppc::fmadds(k, ltm->up.x, pos.x);
            pos.y = ppc::fmadds(k, ltm->up.y, pos.y);
            k = m_afUnkCC[2] * RandSigned();
            pos.z = ppc::fmadds(k, ltm->at.z, pos.z);
            pos.x = ppc::fmadds(k, ltm->at.x, pos.x);
            pos.y = ppc::fmadds(k, ltm->at.y, pos.y);
            if (!IsNullPoint(point) && (m_bitArray & 0x20000u) != 0) {
                float dz = centre.z - point->z;
                float dx = centre.x - point->x;
                const float length = std::sqrt(ppc::fmadds(dx, dx, dz * dz));  // 0x00010690 Math_Sqrtf
                if (length != 0.0f) {
                    const float inv = 1.0f / length;
                    dz = dz * inv;
                    dx = dx * inv;
                }
                const float angle = RandSigned() * 0.39269909262657166f;  // TOC1 +0x4a14 (pi / 8)
                TurnAway(angle, dx, dz, &dir.x, &dir.z);
            } else {
                CVector3 speed;
                speed.x = m_afUnkF0[0] * RandSigned();
                speed.y = m_afUnkF0[1] * RandSigned();
                const float rz = RandSigned();
                speed.x = speed.x + m_afUnkE4[0];
                speed.y = speed.y + m_afUnkE4[1];
                speed.z = m_afUnkF0[2] * rz;
                speed.z = speed.z + m_afUnkE4[2];
                Mat4_TransformVectors(reinterpret_cast<const CMatrix34*>(ltm), &dir, &speed, 1);  // 0x0023f7b0
            }
            RwMatrix launch;
            LaunchMatrix(ltm, &launch);
            if (accessor->m_pProjectileType == nullptr) continue;
            accessor->Launch(&pos, &dir, WordAsFloat(m_unkC8), this, &launch);  // 0x001f2908
        }
    }
    // The explosion.
    if (m_pUnkFC != nullptr) {
        IKFx* fx = static_cast<CKSrvFx*>(g_pEngine->m_srvFx)->AcquireFx(static_cast<IKFxData*>(m_pUnkFC), this);  // inlined
        if (fx != nullptr) {
            CKExplosionNodeFx* explosion = static_cast<CKExplosionNodeFx*>(fx);
            CVector3 pos = centre;
            if (static_cast<int32_t>(m_bitArray) < 0) {
                float dz = centre.z - point->z;
                float dx = centre.x - point->x;
                const float length = std::sqrt(ppc::fmadds(dx, dx, dz * dz));
                if (length != 0.0f) {
                    const float inv = 1.0f / length;
                    dz = dz * inv;
                    dx = dx * inv;
                }
                const float angle = RandSigned() * 0.39269909262657166f;
                TurnAway(angle, dx, dz, &dir.x, &dir.z);
            } else {
                dir = {ltm->at.x, ltm->at.y, ltm->at.z};
            }
            pos.y = pos.y + WordAsFloat(m_unk108);
            RwMatrix matrix;
            LaunchMatrix(ltm, &matrix);
            explosion->SetDirection(&dir, this);    // 0x001b5e20
            explosion->SetTranslation(&pos, this);  // 0x001b66e8
            // The original also passes the matrix (r5), handed on to the sub-effects at time 0; not ported.
            explosion->Trigger(this, 0);            // 0x001b82a8
            explosion->ReleaseReservation(this);    // vt+0x54
        }
    }
    // The hot spots' projectiles.
    for (uint32_t i = 0; i < m_vUnk88.m_ui32NbUsedElt; ++i) {
        const Entry8& entry = m_vUnk88.m_pBlock[i];
        CKProjectileAccessor* spot = static_cast<CKProjectileAccessor*>(m_vUnk7C.m_pBlock[entry.m_unk0]);
        if (spot == nullptr || spot->m_pProjectileType == nullptr) continue;
        CMatrix34 world;
        static_cast<CSGHotSpot*>(entry.m_pUnk4)->GetWorldMatrix(&world);  // 0x000ce970
        float dz = centre.z - point->z;
        float dx = centre.x - point->x;
        const float length = std::sqrt(ppc::fmadds(dx, dx, dz * dz));
        if (length != 0.0f) {
            const float inv = 1.0f / length;
            dz = dz * inv;
            dx = dx * inv;
        }
        const float spread = WordAsFloat(m_unk94) * 0.01745329052209854f;  // TOC1 +0x4a18
        const float angle = RandSigned() * spread;
        TurnAway(angle, dx, dz, &dir.x, &dir.z);
        spot->Launch(&world.m_pos, &dir, WordAsFloat(m_unkC8), this, reinterpret_cast<const RwMatrix*>(&world));
    }
    // The bonuses.
    CVector3 toward = {ltm->at.x, ltm->at.y, ltm->at.z};  // the effect node's direction
    if ((m_bitArray & 0x800u) != 0 && !IsNullPoint(point)) {
        const float* target;
        if (m_pUnkB0 != nullptr) {
            target = &FrameLtm(static_cast<CSGMovable*>(m_pUnkB0)->m_pRwFrame)->pos.x;  // +0x80
        } else {
            // The first piece's frame (its modelling position, +0x40).
            target = &static_cast<const CSGMovable*>(m_vUnkA4.m_pBlock[0].m_pUnk0)->m_pRwFrame->modelling.pos.x;
        }
        float x = target[0] - point->x;
        float z = target[2] - point->z;
        float y = 0.0f;
        const float length = std::sqrt(ppc::fmadds(z, z, ppc::fmadds(x, x, 0.0f)));
        if (length != 0.0f) {
            const float inv = 1.0f / length;
            z = z * inv;
            x = x * inv;
            y = y * inv;
        }
        const float speed = WordAsFloat(m_unkB4);
        toward = {speed * x, speed * y, speed * z};
    }
    if (((m_bitArray >> 24) & 3u) != 0) PlaceEffectNodeB0(&centre, &toward);  // 0x00407410
    const CVector3 base = {ltm->pos.x, ltm->pos.y, ltm->pos.z};
    const CVector3 along = {ltm->at.x, ltm->at.y, ltm->at.z};
    static_cast<KBase201*>(g_pEngine->m_srvBonus)
        ->SpawnBonuses(static_cast<CKBonusData*>(m_pUnk10C), &base, &along, &base, 0);  // 0x00126278
    if ((m_bitArray & 0x04000000u) != 0 && child == 0) {
        CKSound* sound = static_cast<CKSoundDictionaryID*>(m_pSoundDico)->GetSound2(0);  // 0x00112bd8
        sound->SetPosition(&base);  // 0x00110fa0
        sound->Play(0.0f);          // 0x00111230
    }
    if (m_unk1B8 != 0) {
        m_unk188 = m_unk18A;
        return;
    }
    CKSoundDictionaryID* sounds = static_cast<CKSoundDictionaryID*>(m_pSoundDico);
    if (sounds->GetSound(2) != nullptr) sounds->GetSound(2)->Stop(0);  // 0x00112bc0, 0x001111b0
    QueueTriggerSignals(&m_tsUnk134);  // 0x00236338
    m_unk188 = 0;
    UpdatePathBlocking(0);  // 0x009c1538
    uint8_t* state = &static_cast<CKCrumblyZoneCpnt*>(m_pUnk9C)->m_unk0d;  // +0x9c (LVL010: CKCrumblyZoneCpnt)'s +0x0d: 2 becomes 3, else 1
    *state = *state == 2 ? 3 : 1;
    for (uint32_t i = 0; i < m_ui8NbUnk1AC; ++i) {
        CKHkCrumblyZone* zone = static_cast<CKHkCrumblyZone*>(m_apUnk1AC[i]);
        if (zone->m_unk188 != 0) zone->Crumble(point, 1);
    }
}

// 0x004085d8 CKHkCrumblyZone_Restore (message 0x900, RestoreIfDestroyed): the zone intact again. Flags 0x30000 of +0x158
// cleared, the safe leaf shown, the bonus data reset, the grounds safe, every +0xa4 volume on; then from the safe leaf's
// box centre (+0xd8 through its LTM): with a projectile type (+0xc4) and life bit 19 the life's piece count (bits 3-8)
// of debris launched from random points of the box (+0xcc along the LTM's axes) with a random horizontal direction (y
// 1; five draws each); with life bit 20 and bits 24-25 the effect node placed (PlaceEffectNodeB0, the null direction);
// with life bit 21 sound 0 at the node; the explosion (+0x104) at the node raised by +0x108 along its at axis. Last the
// hit points (+0x18a) and the stage counter back, +0x158 bit 12 = bit 11, the path-finding boxes freed, the component's
// state (+0x9c +0x0d: 2 becomes 3, else 1) and with +0x154 bit 29 the child zones (+0x1ac) restored too.
void CKHkCrumblyZone::Restore() {
    m_flags158 &= 0xfffcffffu;
    ShowStageNode(m_pSafeLeaf);  // 0x00406f90
    static_cast<CKBonusData*>(m_pUnk10C)->ResetRuntime();  // 0x00126d90
    SetGroundSets(1);  // 0x00405b40
    CKSrvCollision* collision = static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision);
    for (uint32_t i = 0; i < m_vUnkA4.m_ui32NbUsedElt; ++i) {
        collision->EnableVolume(static_cast<IKBoundingVolume*>(m_vUnkA4.m_pBlock[i].m_pUnk0));  // 0x00192090
    }
    const RwFrame* frame = static_cast<CSGMovable*>(m_pSafeLeaf)->m_pRwFrame;
    const RwMatrix* ltm = FrameLtm(frame);  // +0x50
    CVector3 centre;
    Mat4_TransformPoints(reinterpret_cast<const CMatrix34*>(ltm), &centre, reinterpret_cast<const CVector3*>(m_afUnkD8), 1);  // 0x0023f7e8
    CVector3 dir;
    dir.y = 1.0f;  // TOC1 +0x4998 (stored once, before the pieces)
    CKProjectileAccessor* accessor = static_cast<CKProjectileAccessor*>(m_pUnkC4);
    if (accessor->m_pProjectileType != nullptr && (m_bitArray & 0x80000u) != 0) {
        const uint32_t pieces = (m_bitArray >> 3) & 0x3fu;
        for (uint32_t n = 0; n < pieces; ++n) {
            CVector3 pos = centre;
            float k = m_afUnkCC[0] * RandSigned();
            pos.z = ppc::fmadds(k, ltm->right.z, pos.z);
            pos.x = ppc::fmadds(k, ltm->right.x, pos.x);
            pos.y = ppc::fmadds(k, ltm->right.y, pos.y);
            k = m_afUnkCC[1] * RandSigned();
            pos.z = ppc::fmadds(k, ltm->up.z, pos.z);
            pos.x = ppc::fmadds(k, ltm->up.x, pos.x);
            pos.y = ppc::fmadds(k, ltm->up.y, pos.y);
            k = m_afUnkCC[2] * RandSigned();
            pos.z = ppc::fmadds(k, ltm->at.z, pos.z);
            pos.x = ppc::fmadds(k, ltm->at.x, pos.x);
            pos.y = ppc::fmadds(k, ltm->at.y, pos.y);
            dir.x = RandSigned();
            dir.z = RandSigned();
            // BUG(original): the owner argument (r6) is not set: the value Rand_Int left there. Null here; the matrix (r7)
            // is null.
            accessor->Launch(&pos, &dir, WordAsFloat(m_unkC8), nullptr, nullptr);  // 0x001f2908
        }
    }
    if ((m_bitArray & 0x100000u) != 0 && ((m_bitArray >> 24) & 3u) != 0) {
        PlaceEffectNodeB0(&centre, &kNullPoint);  // 0x00407410 (the null vector 0x00c50d64)
    }
    if ((m_bitArray & 0x200000u) != 0) {
        CKSound* sound = static_cast<CKSoundDictionaryID*>(m_pSoundDico)->GetSound2(0);  // 0x00112bd8
        const CVector3 at = {ltm->pos.x, ltm->pos.y, ltm->pos.z};
        sound->SetPosition(&at);  // 0x00110fa0
        sound->Play(0.0f);        // 0x00111230
    }
    if (m_pUnk104 != nullptr) {
        IKFx* fx = static_cast<CKSrvFx*>(g_pEngine->m_srvFx)->AcquireFx(static_cast<IKFxData*>(m_pUnk104), this);  // inlined
        if (fx != nullptr) {
            CKExplosionNodeFx* explosion = static_cast<CKExplosionNodeFx*>(fx);
            const RwMatrix* now = FrameLtm(static_cast<CSGMovable*>(m_pSafeLeaf)->m_pRwFrame);
            CVector3 pos;
            pos.x = now->pos.x;
            pos.z = now->pos.z;
            pos.y = now->pos.y + WordAsFloat(m_unk108);
            const CVector3 along = {now->at.x, now->at.y, now->at.z};
            explosion->SetDirection(&along, this);  // 0x001b5e20
            explosion->SetTranslation(&pos, this);  // 0x001b66e8
            // The original passes the launch matrix (the LTM's rows at the null position) as Trigger's third argument; the
            // explosion's projectile sub-effects drop it (CKExplosionNodeFx::FireSubEffect).
            explosion->Trigger(this, 0);          // 0x001b82a8
            explosion->ReleaseReservation(this);  // vt+0x54
        }
    }
    m_unk188 = m_unk18A;
    m_unk1B8 = static_cast<uint8_t>(m_ui8NbUnk1B4 + 1);
    m_flags158 = (m_flags158 & 0xffffefffu) | (((m_flags158 >> 11) & 1u) << 12);
    UpdatePathBlocking(0);  // 0x009c1538
    uint8_t* state = &static_cast<CKCrumblyZoneCpnt*>(m_pUnk9C)->m_unk0d;  // 2 becomes 3, else 1
    *state = *state == 2 ? 3 : 1;
    if ((m_unk154 & 0x20000000u) != 0 && m_ui8NbUnk1AC != 0) {
        for (int32_t i = 0; i < static_cast<int32_t>(m_ui8NbUnk1AC); ++i) {
            static_cast<CKHkCrumblyZone*>(m_apUnk1AC[i])->Restore();  // 0x004085d8
        }
    }
}

// 0x0040aab8 CKHkCrumblyZone_StartCrumble_maybe: a zone whose animation dictionary (+0x17c) has a crumble animation
// (entry 2) starts it on the safe leaf (+0x34: +0x180 = 2, a 0.2 s crossfade from 0, flag 0x20000) and plays sound 0 at
// the point; the crumble itself follows at the animation's end (UpdateCrumbleAnim, the zone's Update). Any other zone
// crumbles now. (The dictionary keeps the words: the original's non-null entry is a word that resolves.)
void CKHkCrumblyZone::StartCrumble(const CVector3* point, uint8_t child) {
    if (m_pUnk17C != nullptr) {
        const uint32_t word = static_cast<uint32_t>(static_cast<CAnimationDictionary*>(m_pUnk17C)->m_apAnimations[2]);
        if (CAnimationManager_GetAnimation(word) != nullptr) {
            m_unk180 = 2;
            static_cast<CAnimatedNode*>(m_pSafeLeaf)->CrossfadeToAnim(0.2f, 0.0f, word, 1);  // 0x000c8eb0, TOC +0x4a0c / +0x497c
            m_flags158 = (m_flags158 & 0xfffdffffu) | 0x20000u;
            CKSound* sound = static_cast<CKSoundDictionaryID*>(m_pSoundDico)->GetSound2(0);  // 0x00112bd8
            sound->SetPosition(point);  // 0x00110fa0
            sound->Play(0.0f);          // 0x00111230
            return;
        }
    }
    Crumble(point, child);
}

// 0x0040aa28 CKHkCrumblyZone_UpdateCrumbleAnim_maybe: the safe leaf's animation ended within `dt`: the crumble (no point:
// the null vector 0x00c50d64, as a child); else the animation advances.
void CKHkCrumblyZone::UpdateCrumbleAnim(double dt) {
    CAnimatedNode* node = static_cast<CAnimatedNode*>(m_pSafeLeaf);
    if (node->IsAnimEndReached(dt)) {  // 0x000ca368
        const CVector3 none = {0.0f, 0.0f, 0.0f};
        Crumble(&none, 1);
        return;
    }
    node->AddAnimTime(dt);  // 0x000c9638
}

// ---- the zone's per-frame update (C2.7 fx-2) ----

namespace {
const CVector3 kZoneNullVector = {0.0f, 0.0f, 0.0f};  // 0x00c50d64 (TOC1 +0x49b4)
float ZoneWordAsFloat(uint32_t word) {
    float value;
    std::memcpy(&value, &word, sizeof value);
    return value;
}
}  // namespace

// 0x0040c2f8 CKHkCrumblyZone_Update. (WorldObjectBase_Update_Nop 0x3f6e68, the actor base's Update, comes first: empty.)
void CKHkCrumblyZone::Update(IKTime* clock) {
    m_flags158 &= ~0x8000u;
    m_bitArray = (m_bitArray & ~0x600u) | (((m_bitArray >> 10) & 1u) << 9);
    const float dt = clock->m_afDeltaTime[0];
    if ((m_flags158 & 0x20000u) != 0) {
        UpdateCrumbleAnim(dt);  // 0x0040aa28 (inlined)
        return;
    }
    if ((m_flags158 & 0x10000u) != 0) {
        // The regrowth animation of the safe leaf: the flag cleared at its end.
        CAnimatedNode* node = static_cast<CAnimatedNode*>(m_pSafeLeaf);
        if (node->IsAnimEndReached(dt)) {  // 0x000ca368
            m_flags158 &= ~0x10000u;
            return;
        }
        node->AddAnimTime(dt);  // 0x000c9638
        return;
    }
    if (m_unk188 != 0) {
        VfF8();  // vt+0xf8 (the Spyro zone's UpdateHeroWeight)
        if ((m_unk154 & 8u) != 0) UpdateStageNodeMotion(clock);  // vt+0xf0
        CAnimationDictionary* animations = static_cast<CAnimationDictionary*>(m_pUnk17C);
        if (animations != nullptr) {
            const uint8_t wanted = m_unk181;
            const float speed = ZoneWordAsFloat(m_unk184);
            CAnimatedNode* node = static_cast<CAnimatedNode*>(m_pKGLObject);
            if (m_unk180 == wanted) {
                if ((m_flags158 & 0x4000u) != 0) {
                    node->SetCurrentAnimTime(0.0f);  // 0x000c9690, TOC +0x497c
                    m_flags158 &= ~0x4000u;
                }
                node->AddAnimTime(speed * dt);  // fmuls
            } else {
                m_unk180 = wanted;
                node->PlayAnim(0.0, static_cast<uint32_t>(animations->m_apAnimations[wanted]), 0);  // 0x000c98b8
            }
            if ((m_unk154 & 0x4000000u) != 0 && m_unk180 == 3 && node->IsAnimEndReached(dt)) m_unk181 = 0;
        }
        CKSound* sound = static_cast<CKSoundDictionaryID*>(m_pSoundDico)->GetSound(2);  // 0x00112bc0
        if (sound != nullptr && sound->GetSample() != nullptr && sound->IsPlaying() == 0) {  // 0x00111000 / 0x00111568
            sound->SetLoop(1);  // 0x00110fd0
            const RwMatrix* ltm = FrameLtm(static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame);
            const CVector3 at = {ltm->pos.x, ltm->pos.y, ltm->pos.z};
            sound->SetPosition(&at);  // 0x00110fa0
            sound->Play(0.0f);        // 0x00111230
        }
    } else {
        const int32_t limit = static_cast<int32_t>(m_unk114);
        if ((m_unk124 < limit || limit < 0) && m_unk128 != 0) {
            m_fUnk120 = m_fUnk120 + dt;
            if (!(ZoneWordAsFloat(m_unk11C) >= m_fUnk120)) {  // bge: the delay not reached (or NaN)
                ResetStageRecursive();  // 0x004082f8
                CAnimationDictionary* animations = static_cast<CAnimationDictionary*>(m_pUnk17C);
                if (animations != nullptr && CAnimationManager_GetAnimation(static_cast<uint32_t>(animations->m_apAnimations[1])) != nullptr) {
                    m_unk180 = 1;
                    static_cast<CAnimatedNode*>(m_pSafeLeaf)
                        ->CrossfadeToAnim(0.2f, 0.0f, static_cast<uint32_t>(animations->m_apAnimations[1]), 1);  // 0x000c8eb0
                    m_flags158 = (m_flags158 & ~0x10000u) | 0x10000u;
                }
                m_fUnk120 = 0.0f;  // an integer 0 store
                m_unk124 = m_unk124 + 1;
            }
        }
    }
    if (static_cast<int8_t>(static_cast<CKCrumblyZoneCpnt*>(m_pUnk9C)->m_unk0d) > 1) {
        UpdatePathBlocking(1);  // 0x009c1538
    }
    ContactHistory_Update(&m_pContactHistory, clock);  // TocBridge 0x98f430 -> 0x5833c0
}

namespace {
// (u & 0xffff) / 65535 - 0.5 (TOC1 +0x4984, +0x4988), scaled by `spread` onto `base` (fmadds): a draw in +-spread / 2.
float RandSpread(float spread, float base) {
    const float u = static_cast<float>(static_cast<double>(static_cast<uint32_t>(Rand_Int()) & 0xffffu));
    return ppc::fmadds(spread, u / 65535.0f - 0.5f, base);
}

// The first geometry's material of a scene node (CNode +0x1c, CGeometry +0x24).
CMaterial* FirstGeometryMaterial(IKSerializable* node) {
    CGeometry* geometry = static_cast<CGeometry*>(static_cast<CNode*>(node)->m_lGeometryList);
    return static_cast<CMaterial*>(geometry->m_pMaterial);
}
}  // namespace

// 0x00405d18 CKHkCrumblyZone_PickRandomStageMotionTargetByMode_maybe: `base` moved by a random spread (+0x58) on the axes
// of the mode (+0x154 bits 4-6): 0 x y, 1 x z, 2 y z, 3 x y z, 4 x, 5 y, 6 z (one draw per axis, in that order); 7 none.
CVector3 CKHkCrumblyZone::PickRandomStageMotionTarget(const CVector3* base) const {
    CVector3 out = *base;
    const float spread = WordAsFloat(m_unk58);
    switch ((m_unk154 >> 4) & 7u) {
    case 0:
        out.x = RandSpread(spread, out.x);
        out.y = RandSpread(WordAsFloat(m_unk58), out.y);
        break;
    case 1:
        out.x = RandSpread(spread, out.x);
        out.z = RandSpread(WordAsFloat(m_unk58), out.z);
        break;
    case 2:
        out.y = RandSpread(spread, out.y);
        out.z = RandSpread(WordAsFloat(m_unk58), out.z);
        break;
    case 3:
        out.x = RandSpread(spread, out.x);
        out.y = RandSpread(WordAsFloat(m_unk58), out.y);
        out.z = RandSpread(WordAsFloat(m_unk58), out.z);
        break;
    case 4:
        out.x = RandSpread(spread, out.x);
        break;
    case 5:
        out.y = RandSpread(spread, out.y);
        break;
    case 6:
        out.z = RandSpread(spread, out.z);
        break;
    default:
        break;
    }
    return out;
}

// 0x00406410 CKHkCrumblyZone_UpdateStageNodeMotion_maybe (vt+0xf0): the current stage node (+0x1b8: 0 the broken leaf,
// the stage count + 1 the safe leaf, else stage n - 1 of +0x1b4) moves, the time +0x64 counting. After a collapse
// (+0x154 bit 28) the quake +0x70 shakes it about the rest matrix (+0x78) while the quake runs; otherwise, until the
// time passes +0x5c, it walks (+0x54 per second, InvSqrt step) toward a random target about the rest position (a new
// one each time it arrives; the countdown +0x60 reloads with +0x58). At the end (or when the quake stops) the node
// returns to rest, bit 3 of +0x154 is cleared and with +0x154 bit 21 the node's material gets the rest coefficient
// +0x98. While moving with bit 21, the hook node's material coefficient advances by 2 x +0x54 x dt, wrapped below 1.
void CKHkCrumblyZone::UpdateStageNodeMotion(IKTime* clock) {
    IKSerializable* node;
    if (m_unk1B8 == 0) {
        node = m_pBrokenLeaf;
    } else if (m_unk1B8 == static_cast<uint32_t>(m_ui8NbUnk1B4) + 1) {
        node = m_pSafeLeaf;
    } else {
        node = m_apUnk1B4[m_unk1B8 - 1];
    }
    if (node == nullptr) return;
    CSGMovable* movable = static_cast<CSGMovable*>(node);
    const float dt = clock->m_afDeltaTime[IKTime::SCALABLE_GAME_TIME];
    m_fUnk64 = m_fUnk64 + dt;
    bool atRest = false;
    if ((m_unk154 & 0x10000000u) != 0) {
        CKQuakeCpntUpdater* quake = static_cast<CKQuakeCpntUpdater*>(m_pUnk70);
        if (quake->m_bRunning == 0) {
            atRest = true;
        } else {
            float out[15];
            quake->EvaluateScaled(dt, 1.0f, out);  // 0x0024f5c8 (TOC1 +0x4998)
            CMatrix34 shake;
            ShakeSample_BuildMatrix(quake, out, &shake, m_pUnk74[0]);  // 0x0024ee90
            Mat4_TransformPostConcat(&shake, m_pUnk74[1]);             // 0x0023f760
            movable->SetLocalMatrix(reinterpret_cast<const RwMatrix*>(&shake));  // 0x000d0be8
        }
    } else if (WordAsFloat(m_unk5C) < m_fUnk64) {  // fcmpu / blt: a NaN keeps moving
        atRest = true;
    } else {
        m_fUnk60 = m_fUnk60 - dt;
        if (m_fUnk60 < 0.0f) m_fUnk60 = WordAsFloat(m_unk58);  // TOC1 +0x497c
        if (m_vUnk3C.x == m_vUnk48.x && m_vUnk3C.y == m_vUnk48.y && m_vUnk3C.z == m_vUnk48.z) {
            const CVector3 rest = m_pUnk74[1]->m_pos;  // the rest matrix's position (+0x30)
            m_vUnk3C = PickRandomStageMotionTarget(&rest);  // 0x00405d18
        }
        if (m_vUnk48.x != m_vUnk3C.x || m_vUnk48.y != m_vUnk3C.y || m_vUnk48.z != m_vUnk3C.z) {
            const float dx = m_vUnk3C.x - m_vUnk48.x;
            const float dy = m_vUnk3C.y - m_vUnk48.y;
            const float step = dt * m_fUnk54;
            const float dz = m_vUnk3C.z - m_vUnk48.z;
            const float distance2 = ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy));
            if (step * step <= distance2) {  // fcmpu / ble: a NaN snaps to the target
                const float scale = step * rwInvSqrt(distance2);  // Math_InvSqrtf 0x000114d8
                m_vUnk48.z = ppc::fmadds(dz, scale, m_vUnk48.z);
                m_vUnk48.x = ppc::fmadds(dx, scale, m_vUnk48.x);
                m_vUnk48.y = ppc::fmadds(dy, scale, m_vUnk48.y);
            } else {
                m_vUnk48 = m_vUnk3C;
            }
        }
        RwFrame* frame = movable->m_pRwFrame;
        frame->modelling.pos.z = m_vUnk48.z;
        frame->modelling.pos.x = m_vUnk48.x;
        frame->modelling.pos.y = m_vUnk48.y;
        frame->modelling.flags &= 0xfffdffffu;  // rwMATRIXINTERNALIDENTITY cleared
        RwFrame_MarkDirty(frame);  // 0x00010698
    }
    if (atRest) {
        m_unk154 &= 0xfffffff7u;
        movable->SetLocalMatrix(reinterpret_cast<const RwMatrix*>(m_pUnk74[1]));  // 0x000d0be8
        if ((m_unk154 & 0x200000u) != 0) FirstGeometryMaterial(node)->SetEnvMapCoefficient(m_fUnk98);  // 0x000bbc30
        return;
    }
    if ((m_unk154 & 0x200000u) == 0) return;
    CMaterial* material = FirstGeometryMaterial(m_pKGLObject);
    const float advance = m_fUnk54 * dt;
    float coefficient = material->GetEnvMapCoefficient() + (advance + advance);  // 0x000bbf70
    while (coefficient > 1.0f) coefficient = coefficient - 1.0f;  // fcmpu / ble (TOC1 +0x4998)
    material->SetEnvMapCoefficient(coefficient);  // 0x000bbc30
}

// 0x00407880 CKHkCrumblyZone_TriggerCollapse_maybe (vt+0xf4): the stage node's motion starts (+0x154 bit 3, the update
// flag +0x158 bit 15, +0x154 bit 28 = the mode). The collapse explosion (+0x100, a pooled effect reserved for the zone)
// goes off at the point (mode 0: the safe leaf), turned away from the safe leaf, launched with the leaf's LTM without
// its position. Mode 0 walks: the countdown +0x60 reloaded, a random target (draws) about the rest position, the
// position at rest; another mode shakes: the quake's base (+0x74) turned toward the point (horizontally, from the hook
// node; the x axis when the point is above it) relative to the rest matrix, the quake started. Then: sound 1 at the rest
// position (hook bit 27, not for a child), the effect node +0xb8 at the leaf's box centre (+0xd8) along the leaf's at
// axis or (hook bit 11) away from the point scaled by +0xb4, the node material's coefficient kept (+0x98, +0x154 bit
// 21), the trigger starter +0x13c fired, +0x181 = 3 with +0x154 bit 26 (and +0x158 bit 14 with its bit 13), and with
// +0x154 bit 31 the child zones not updating (+0x158 bit 15 clear) collapse the same way (arg 1).
void CKHkCrumblyZone::TriggerCollapse(uint32_t mode, const CVector3* point, uint32_t arg) {
    const uint32_t byteMode = mode & 0xffu;
    m_unk154 = (m_unk154 & 0xfffffff7u) | 8u;
    m_flags158 = (m_flags158 & 0xffff7fffu) | 0x8000u;
    m_unk154 = (m_unk154 & 0xefffffffu) | (byteMode << 28);
    if (m_pUnk100 != nullptr) {
        IKFx* effect = static_cast<CKSrvFx*>(g_pEngine->m_srvFx)->AcquireFx(static_cast<IKFxData*>(m_pUnk100), this);
        if (effect != nullptr) {
            CKExplosionNodeFx* explosion = static_cast<CKExplosionNodeFx*>(effect);
            const RwMatrix* leaf = FrameLtm(static_cast<CSGMovable*>(m_pSafeLeaf)->m_pRwFrame);
            CVector3 position;
            if (byteMode == 0) {
                position = {leaf->pos.x, leaf->pos.y, leaf->pos.z};
            } else {
                position = *point;
            }
            float dy = position.y - leaf->pos.y;
            float dx = position.x - leaf->pos.x;
            float dz = position.z - leaf->pos.z;
            const float length = std::sqrt(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));  // 0x00010690
            CVector3 direction;
            if (length == 0.0f) {
                direction = {leaf->at.x, leaf->at.y, leaf->at.z};
            } else {
                const float inverse = 1.0f / length;
                direction = {dx * inverse, dy * inverse, dz * inverse};
            }
            CMatrix34 launch;
            std::memcpy(&launch, leaf, sizeof launch);  // the LTM (flags and pads too)
            launch.m_pos = kNullPoint;
            launch.m_ui32Flags &= 0xfffdffffu;
            explosion->SetDirection(&direction, this);   // 0x001b5e20
            explosion->SetTranslation(&position, this);  // 0x001b66e8
            explosion->Trigger(this, &launch);           // 0x001b82a8
            explosion->ReleaseReservation(this);         // vt+0x54
        }
    }
    m_fUnk64 = 0.0f;  // TOC1 +0x497c
    if (byteMode == 0) {
        m_fUnk60 = WordAsFloat(m_unk58);
        const CVector3 rest = m_pUnk74[1]->m_pos;
        m_vUnk3C = PickRandomStageMotionTarget(&rest);  // 0x00405d18
        m_vUnk48 = m_pUnk74[1]->m_pos;
    } else {
        const RwMatrix* hook = FrameLtm(static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame);
        CVector3 toward = {point->x - hook->pos.x, 0.0f, point->z - hook->pos.z};
        if (toward.x == 0.0f && toward.z == 0.0f) {
            toward = {1.0f, 0.0f, 0.0f};  // 0x00c50d34 (TOC1 +0x4a04): the x axis
        } else {
            const float length = std::sqrt(ppc::fmadds(toward.z, toward.z, ppc::fmadds(toward.x, toward.x, 0.0f)));
            if (length != 0.0f) {
                const float inverse = 1.0f / length;
                toward.z = toward.z * inverse;
                toward.x = toward.x * inverse;
                toward.y = toward.y * inverse;
            }
        }
        CMatrix34* base = m_pUnk74[0];
        base->m_ui32Flags = 0x20003u;
        base->m_right = {1.0f, 0.0f, 0.0f};
        base->m_up = {0.0f, 1.0f, 0.0f};
        base->m_at = {0.0f, 0.0f, 1.0f};
        base->m_pos = {0.0f, 0.0f, 0.0f};
        const CVector3 up = {0.0f, 1.0f, 0.0f};  // 0x00c50d40 (TOC1 +0x49b8)
        Mat4_SetBasisFromAtUp(base, &toward, &up);  // 0x0023fd30
        CMatrix34 inverse;
        Mat4_Invert(&inverse, m_pUnk74[1]);           // 0x0023f878
        Mat4_TransformPostConcat(base, &inverse);     // 0x0023f760
        static_cast<CKQuakeCpntUpdater*>(m_pUnk70)->Start();  // 0x0024f770
    }
    if ((m_bitArray & 0x08000000u) != 0 && arg == 0) {
        // No null test of the sound (as in the original).
        CKSound* sound = static_cast<CKSoundDictionaryID*>(m_pSoundDico)->GetSound2(1);  // 0x00112bd8
        sound->SetPosition(&m_pUnk74[1]->m_pos);  // 0x00110fa0
        sound->Play(0.0f);                        // 0x00111230
    }
    if (((m_bitArray >> 22) & 3u) != 0) {
        CVector3 along = kNullPoint;
        CVector3 centre;
        const RwMatrix* leaf = FrameLtm(static_cast<CSGMovable*>(m_pSafeLeaf)->m_pRwFrame);
        Mat4_TransformPoints(reinterpret_cast<const CMatrix34*>(leaf), &centre,
                             reinterpret_cast<const CVector3*>(m_afUnkD8), 1);  // 0x0023f7e8
        if (IsNullPoint(point) || (m_bitArray & 0x800u) == 0) {
            const RwMatrix* now = FrameLtm(static_cast<CSGMovable*>(m_pSafeLeaf)->m_pRwFrame);
            along = {now->at.x, now->at.y, now->at.z};
        } else {
            along = {centre.x - point->x, 0.0f, centre.z - point->z};
            const float length = std::sqrt(ppc::fmadds(along.z, along.z, ppc::fmadds(along.x, along.x, 0.0f)));
            if (length != 0.0f) {
                const float inverse = 1.0f / length;
                along.z = along.z * inverse;
                along.x = along.x * inverse;
                along.y = along.y * inverse;
            }
            const float scale = WordAsFloat(m_unkB4);
            along.z = along.z * scale;
            along.x = along.x * scale;
            along.y = along.y * scale;
        }
        PlaceEffectNodeB8(&centre, &along);  // 0x00407648
    }
    if ((m_unk154 & 0x200000u) != 0) m_fUnk98 = FirstGeometryMaterial(m_pKGLObject)->GetEnvMapCoefficient();  // 0x000bbf70
    QueueTriggerSignals(&m_tsUnk13C);  // 0x00236338
    if ((m_unk154 & 0x04000000u) != 0) {
        m_unk181 = 3;
        if ((m_flags158 & 0x2000u) != 0) m_flags158 = (m_flags158 & 0xffffbfffu) | 0x4000u;
    }
    if (static_cast<int32_t>(m_unk154) >= 0) return;
    for (int32_t i = 0; i < static_cast<int32_t>(m_ui8NbUnk1AC); ++i) {
        CKHkCrumblyZone* child = static_cast<CKHkCrumblyZone*>(m_apUnk1AC[i]);
        if ((child->m_flags158 & 0x8000u) != 0) continue;
        child->TriggerCollapse(byteMode, point, 1);  // vt+0xf4
    }
}

// 0x00407648 CKHkCrumblyZone_PlaceEffectNodeB8_maybe: PlaceEffectNodeB0's body for the second effect (hook bits 22-23,
// the particle node +0xb8, the component's emitter +0xc0).
void CKHkCrumblyZone::PlaceEffectNodeB8(const CVector3* position, const CVector3* direction) {
    CVector3 along = *direction;
    const float length = std::sqrt(ppc::fmadds(along.z, along.z, ppc::fmadds(along.x, along.x, along.y * along.y)));
    float speed = 0.0f;  // TOC +0x497c
    if (length != speed) {
        const float inverse = 1.0f / length;  // TOC +0x4998
        along.z = along.z * inverse;
        along.x = along.x * inverse;
        along.y = along.y * inverse;
        speed = length;
    }
    CParticlesNodeFx* node = static_cast<CParticlesNodeFx*>(m_pUnkB8);
    if (((m_bitArray >> 22) & 3u) == 1 && node != nullptr) {
        if (!(direction->x == kZoneNullVector.x && direction->y == kZoneNullVector.y && direction->z == kZoneNullVector.z)) {
            const CVector3 up = {0.0f, 1.0f, 0.0f};  // 0x00c50d40 (TOC +0x49b8)
            node->SetOrientationFromAtUp(&along, &up);  // 0x000d0918
            if ((m_bitArray & 0x800u) != 0) {
                RpPrtStdEmitter* emitter = node->m_pRpPrtStdEmitter;
                RpPrtStdEmitterStandard* standard = reinterpret_cast<RpPrtStdEmitterStandard*>(
                    reinterpret_cast<uint8_t*>(emitter) + emitter->emtClass->propTab->propOffset[1]);
                standard->force.x = direction->x;
                standard->force.y = direction->y;
                standard->force.z = direction->z;
            }
            node = static_cast<CParticlesNodeFx*>(m_pUnkB8);
        }
        node->m_sgProperties = (node->m_sgProperties | 0x200u | 0x400u) & ~0x80000u;
        node->m_fEmissionSpeedAdjustment = 0.0f;
        node->m_pRpPrtStdEmitter->flag |= rpPRTSTDEMITTERFLAGACTIVE | rpPRTSTDEMITTERFLAGEMIT;  // 0xa
        return;
    }
    if ((m_bitArray & 0x800u) == 0) speed = 0.0f;
    static_cast<CKCrumblyZoneCpnt*>(m_pUnk9C)
        ->QueueInstanceTransform(speed, static_cast<int32_t>(m_unkC0), position, &along,
                                 reinterpret_cast<const CVector3*>(m_afUnkCC));  // 0x00401bd0
}

// 0x004072a8 CKHkCrumblyZone_vfF8: the base class's weight update (LVL010 holds only the Spyro zone, which overrides it:
// CKHkS08CrumblyZone_UpdateHeroWeight_maybe 0x414638). The heroes on the zone's ground counted (the inlined
// CountHeroesOnZone); with +0x154 bit 2 a changed count is kept (+0x68) and collapses the zone (vt+0xf4, mode 0, the
// null point); otherwise (or unchanged) a count above 0 collapses it with +0x154 bit 27 unless it moves (bit 3).
void CKHkCrumblyZone::VfF8() {
    const uint8_t count = CountHeroesOnZone();  // inlined
    const uint32_t bits = m_unk154;
    if ((bits & 4u) != 0 && m_unk68 != count) {
        m_unk68 = count;
        TriggerCollapse(0, &kNullPoint, 0);  // vt+0xf4
        return;
    }
    if (count == 0 || (bits & 0x08000000u) == 0 || (bits & 8u) != 0) return;
    TriggerCollapse(0, &kNullPoint, 0);  // vt+0xf4
}

// 0x00406c20 CKHkCrumblyZone_GetInfo, with its accessors 0x00406280 IsIntactProperty_maybe, 0x00405658
// IsDestroyedProperty_maybe and 0x00406278 GetHitPointsProperty_maybe.
int32_t CKHkCrumblyZone::GetInfo(IKInfo* info, int32_t request) {
    const int32_t base = CKHkActorBase::GetInfo(info, request);  // KStub_Return1 0x3f7140
    int32_t own = 1;
    if (request == kGetInfoValueAccessor) {
        if (info->m_ui32Id == 0x4f) {
            own = AnswerInfo(info, [](IKSerializable* o, uint32_t) {
                return static_cast<CKHkCrumblyZone*>(o)->m_unk188 == 0 ? 1u : 0u;
            }, 0);
        } else if (info->m_ui32Id == 0x50) {
            own = AnswerInfo(info, [](IKSerializable* o, uint32_t) {
                return static_cast<uint32_t>(static_cast<CKHkCrumblyZone*>(o)->m_unk188);
            }, 1);
        } else if (info->m_ui32Id == 0x4e) {
            own = AnswerInfo(info, [](IKSerializable* o, uint32_t) {
                return static_cast<CKHkCrumblyZone*>(o)->m_unk188 != 0 ? 1u : 0u;
            }, 0);
        }
    }
    if (base == 2 || own == 2) return 2;
    return base != 0 ? own : 0;
}

namespace {
// 0x00019c98 KObject_LevelResetIfNotNull_maybe: the object's RecursiveRegistration when there is one.
void RegisterIfNotNull(IKSerializable* object, int32_t type) {
    if (object != nullptr) object->RecursiveRegistration(type);
}
}  // namespace

// 0x00406810 CKHkCrumblyZone_RecursiveRegistration (returns 1): the actor base's (IKHook's); with type 0 the sound
// dictionary, the leaves, the grounds, the effect nodes, the animation (+0x17c), both ground lists, the volumes (+0xa4),
// the stage nodes (+0x1b4), the projectile type (+0xc4, vt+0x24 0), the +0x1a0 references, the bonus data (+0x10c),
// +0x6c, the quake (+0x70), the +0x88 entries' objects, the +0x7c references, +0xfc, the effects (+0x100, +0x104); then
// for every type the component (+0x9c) and the trigger starters (nothing).
void CKHkCrumblyZone::RecursiveRegistration(int32_t type) {
    CKHkActorBase::RecursiveRegistration(type);  // 0x003f6ee8
    if (type == 0) {
        RegisterIfNotNull(m_pSoundDico, 0);
        RegisterIfNotNull(m_pSafeLeaf, 0);
        RegisterIfNotNull(m_pBrokenLeaf, 0);
        RegisterIfNotNull(m_pGround, 0);
        RegisterIfNotNull(m_pBrokenGround, 0);
        RegisterIfNotNull(m_pUnkB0, 0);
        RegisterIfNotNull(m_pUnkB8, 0);
        RegisterIfNotNull(m_pUnk17C, 0);
        for (GroundNode* node = m_lAddedSafeGround; node != nullptr; node = node->m_pNext) RegisterIfNotNull(node->m_pGround, 0);
        for (GroundNode* node = m_lAddedBrokenGround; node != nullptr; node = node->m_pNext) RegisterIfNotNull(node->m_pGround, 0);
        for (uint32_t i = 0; i < m_vUnkA4.m_ui32NbUsedElt; ++i) RegisterIfNotNull(m_vUnkA4.m_pBlock[i].m_pUnk0, 0);
        for (uint32_t i = 0; i < m_ui8NbUnk1B4; ++i) RegisterIfNotNull(m_apUnk1B4[i], 0);
        if (m_pUnkC4 != nullptr) m_pUnkC4->RecursiveRegistration(0);  // vt+0x24
        for (uint32_t i = 0; i < m_vUnk1A0.m_ui32NbUsedElt; ++i) RegisterIfNotNull(m_vUnk1A0.m_pBlock[i], 0);
        RegisterIfNotNull(m_pUnk10C, 0);
        RegisterIfNotNull(m_pUnk6C, 0);
        RegisterIfNotNull(m_pUnk70, 0);
        for (uint32_t i = 0; i < m_vUnk88.m_ui32NbUsedElt; ++i) RegisterIfNotNull(m_vUnk88.m_pBlock[i].m_pUnk4, 0);
        for (uint32_t i = 0; i < m_vUnk7C.m_ui32NbUsedElt; ++i) RegisterIfNotNull(m_vUnk7C.m_pBlock[i], 0);
        if (m_pUnkFC != nullptr) RegisterIfNotNull(m_pUnkFC, 0);
        RegisterIfNotNull(m_pUnk100, 0);
        RegisterIfNotNull(m_pUnk104, 0);
    }
    m_pUnk9C->RecursiveRegistration(type);  // vt+0x24
}

// 0x00405c30 CKHkCrumblyZone_CountHeroesOnZone_maybe
uint8_t CKHkCrumblyZone::CountHeroesOnZone() const {
    IKGrpHero* group = static_cast<IKGrpHero*>(g_pEngine->m_gameManager->m_unk04[1]);  // the hero group (game manager +0x8)
    if (group == nullptr || m_pGround == nullptr) return 0;
    uint32_t count = 0;
    for (IKSerializable** hero = group->m_apHeroesCopy; *hero != nullptr; ++hero) {  // 0x002ca0f0 (+0x3c)
        if (static_cast<CKHkS08Hero*>(*hero)->GetGroundObject() == m_pGround) ++count;  // 0x00363c40
    }
    return static_cast<uint8_t>(count);
}

// 0x00405720 CKHkCrumblyZone_CollapseAndSpawnBonuses_maybe: the bonuses at the safe leaf's LTM position along its at
// row (spawn flag 1).
void CKHkCrumblyZone::CollapseAndSpawnBonuses(uint16_t hits, const CVector3* point) {
    m_unk188 = hits;
    TriggerCollapse(1, point, 0);  // vt+0xf4
    const RwMatrix* ltm = FrameLtm(static_cast<CSGMovable*>(m_pSafeLeaf)->m_pRwFrame);
    const CVector3 position = {ltm->pos.x, ltm->pos.y, ltm->pos.z};
    const CVector3 along = {ltm->at.x, ltm->at.y, ltm->at.z};
    static_cast<KBase201*>(g_pEngine->m_srvBonus)
        ->SpawnBonuses(static_cast<CKBonusData*>(m_pUnk10C), &position, &along, &position, 1);  // 0x00126278
}

// 0x009c1538 CKHkCrumblyZone_UpdatePathBlocking_maybe. Every box: x and z of the ground's AABB (sup +0x18, inf +0x24)
// moved toward its centre, inf + (sup - inf) * 0.5 * (1 - scale) and sup - (sup - inf) * 0.5 * (1 - scale) (fmadds; TOC
// +0x4988 0.5, +0x4a08 -0.5, +0x4998 1.0), y from the AABB; the scales (+0x12c, +0x130) and the flag word are read again
// for every box. The node box: the scene node's LTM position +/- 0.5 on x and z, its y on both sides.
void CKHkCrumblyZone::UpdatePathBlocking(int32_t update) {
    CKSrvPathFinding* pathFinding = static_cast<CKSrvPathFinding*>(g_pEngine->m_srvPathFinding);  // engine +0x6c
    const auto box = [&](const CVector3& sup, const CVector3& inf, uint32_t bit) {
        const float one = 1.0f;
        const float sx = one - ZoneWordAsFloat(m_unk12C);
        const float sz = one - ZoneWordAsFloat(m_unk130);
        const float dx = sup.x - inf.x;
        const float dz = sup.z - inf.z;
        CVector3 low;
        low.x = ppc::fmadds(dx * 0.5f, sx, inf.x);
        low.y = inf.y;
        low.z = ppc::fmadds(dz * 0.5f, sz, inf.z);
        CVector3 high;
        high.x = ppc::fmadds(dx * -0.5f, sx, sup.x);
        high.y = sup.y;
        high.z = ppc::fmadds(dz * -0.5f, sz, sup.z);
        const uint8_t blocked = bit == 0 ? 0 : static_cast<uint8_t>((m_unk154 >> bit) & 1u);  // li r7,0 or +0x154's bit
        pathFinding->SetBoxBlocked(m_unk12A, &low, &high, blocked);  // 0x001e5f60
    };
    const auto groundBox = [&](IKSerializable* ground, uint32_t bit) {
        const float* aabb = static_cast<ICollisionMesh*>(ground)->m_AABB;
        box({aabb[0], aabb[1], aabb[2]}, {aabb[3], aabb[4], aabb[5]}, bit);
    };
    const auto groundSet = [&](IKSerializable* ground, GroundNode* list, uint32_t bit) {
        groundBox(ground, bit);
        for (GroundNode* node = list; node != nullptr; node = node->m_pNext) groundBox(node->m_pGround, bit);
    };
    const auto nodeBox = [&](uint32_t bit) {
        const RwV3d& p = FrameLtm(static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame)->pos;  // RwFrame +0x80
        const float half = 0.5f;  // TOC +0x4988
        box({p.x + half, p.y, p.z + half}, {p.x - half, p.y, p.z - half}, bit);
    };
    if (m_unk188 != 0) {
        if (update == 0) {
            if (m_pBrokenGround != nullptr) {
                groundSet(m_pBrokenGround, m_lAddedBrokenGround, 0);
            } else if (m_pGround != nullptr) {
                groundSet(m_pGround, m_lAddedSafeGround, 0);
            } else {
                nodeBox(0);
            }
        } else if ((m_unk154 & 0x20000u) == 0) {
            return;
        }
        if (m_pGround != nullptr) {
            groundSet(m_pGround, m_lAddedSafeGround, 17);
        } else if (m_pBrokenGround != nullptr) {
            groundSet(m_pBrokenGround, m_lAddedBrokenGround, 17);
        } else {
            nodeBox(17);
        }
        return;
    }
    if (update == 0) {
        if (m_pGround != nullptr) {
            groundSet(m_pGround, m_lAddedSafeGround, 0);
        } else if (m_pBrokenGround != nullptr) {
            groundSet(m_pBrokenGround, m_lAddedBrokenGround, 0);
        } else {
            nodeBox(0);
        }
    } else if ((m_unk154 & 0x40000u) == 0) {
        return;
    }
    if (m_pBrokenGround != nullptr) {
        groundSet(m_pBrokenGround, m_lAddedBrokenGround, 18);
    } else if (m_pGround != nullptr) {
        groundSet(m_pGround, m_lAddedSafeGround, 18);
    } else {
        nodeBox(18);
    }
}

// 0x004082f8 CKHkCrumblyZone_ResetStageRecursive_maybe
void CKHkCrumblyZone::ResetStageRecursive() {
    m_unk188 = m_unk18A;
    m_unk1B8 = static_cast<uint8_t>(m_ui8NbUnk1B4 + 1);
    m_flags158 = (m_flags158 & ~0x1000u) | (((m_flags158 >> 11) & 1u) << 12);
    static_cast<CKBonusData*>(m_pUnk10C)->ResetRuntime();  // 0x00126d90
    m_flags158 &= 0xfffcffffu;
    if ((m_bitArray & 4u) != 0) return;
    ShowStageNode(m_pSafeLeaf);  // 0x00406f90
    SetGroundSets(1);            // 0x00405b40
    UpdatePathBlocking(0);       // 0x009c1538
    CKCrumblyZoneCpnt* component = static_cast<CKCrumblyZoneCpnt*>(m_pUnk9C);
    component->m_unk0d = component->m_unk0d == 2 ? 3 : 1;
    CKSrvCollision* collision = static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision);
    for (uint32_t i = 0; i < m_vUnkA4.m_ui32NbUsedElt; ++i) {
        CSGLeaf* volume = static_cast<CSGLeaf*>(m_vUnkA4.m_pBlock[i].m_pUnk0);
        if (volume->m_pParent != nullptr) volume->m_pParent->RemoveChild(volume);  // vt+0x78
        static_cast<CSGBranch*>(m_pKGLObject)->AddChild(volume);                   // vt+0x70
        collision->EnableVolume(static_cast<IKBoundingVolume*>(m_vUnkA4.m_pBlock[i].m_pUnk0));  // 0x00192090
    }
    if ((m_unk154 & 0x20000000u) != 0 && m_ui8NbUnk1AC != 0) {
        for (int32_t i = 0; i < static_cast<int32_t>(m_ui8NbUnk1AC); ++i) {
            static_cast<CKHkCrumblyZone*>(m_apUnk1AC[i])->ResetStageRecursive();
        }
    }
}

// 0x00407410 CKHkCrumblyZone_PlaceEffectNodeB0_maybe
void CKHkCrumblyZone::PlaceEffectNodeB0(const CVector3* position, const CVector3* direction) {
    CVector3 along = *direction;
    const float length = std::sqrt(ppc::fmadds(along.z, along.z, ppc::fmadds(along.x, along.x, along.y * along.y)));
    float speed = 0.0f;  // TOC +0x497c
    if (length != speed) {
        const float inverse = 1.0f / length;  // TOC +0x4998
        along.z = along.z * inverse;
        along.x = along.x * inverse;
        along.y = along.y * inverse;
        speed = length;
    }
    CParticlesNodeFx* node = static_cast<CParticlesNodeFx*>(m_pUnkB0);
    if (((m_bitArray >> 24) & 3u) == 1 && node != nullptr) {
        if (!(direction->x == kZoneNullVector.x && direction->y == kZoneNullVector.y && direction->z == kZoneNullVector.z)) {
            const CVector3 up = {0.0f, 1.0f, 0.0f};  // 0x00c50d40 (TOC +0x49b8)
            node->SetOrientationFromAtUp(&along, &up);  // 0x000d0918
            if ((m_bitArray & 0x800u) != 0) {
                // The force along the unnormalised direction.
                RpPrtStdEmitter* emitter = node->m_pRpPrtStdEmitter;
                RpPrtStdEmitterStandard* standard = reinterpret_cast<RpPrtStdEmitterStandard*>(
                    reinterpret_cast<uint8_t*>(emitter) + emitter->emtClass->propTab->propOffset[1]);
                standard->force.x = direction->x;
                standard->force.y = direction->y;
                standard->force.z = direction->z;
            }
            node = static_cast<CParticlesNodeFx*>(m_pUnkB0);
        }
        node->m_sgProperties = (node->m_sgProperties | 0x200u | 0x400u) & ~0x80000u;
        node->m_fEmissionSpeedAdjustment = 0.0f;
        node->m_pRpPrtStdEmitter->flag |= rpPRTSTDEMITTERFLAGACTIVE | rpPRTSTDEMITTERFLAGEMIT;  // 0xa
        return;
    }
    if ((m_bitArray & 0x800u) == 0) speed = 0.0f;
    static_cast<CKCrumblyZoneCpnt*>(m_pUnk9C)
        ->QueueInstanceTransform(speed, static_cast<int32_t>(m_unkBC), position, &along,
                                 reinterpret_cast<const CVector3*>(m_afUnkCC));  // 0x00401bd0
}

// 0x00406398 CKHkCrumblyZone_Destroy
void CKHkCrumblyZone::Destroy() {
    CKHkActorBase::Destroy();
    if (m_apUnk1AC != nullptr) {
        delete[] m_apUnk1AC;  // OperatorDeleteArray
        m_apUnk1AC = nullptr;
    }
    RwMatrixDestroy_Thunk(m_pUnk74[0]);
    RwMatrixDestroy_Thunk(m_pUnk74[1]);
    Mem_FreeAligned16(m_apUnk1B4);
}
