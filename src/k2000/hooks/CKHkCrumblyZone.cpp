// CKHkCrumblyZone.cpp - reconstructed original translation unit 0x405608-0x410190 (GAME_TOC1, main_toc1), 50 functions, 46 live.
// Primary class: CKHkCrumblyZone  key 0x1982  category Hook  size 0x1bc  vtable 0xb257b0
// Other owners: CKSrvBonus (1), CKHkS08CrumblyZone (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x405608  CKHkCrumblyZone_Delete
//   [ ] 0x405658  CKHkCrumblyZone_IsDestroyedProperty_maybe
//   [ ] 0x405668  RegisterCKHkCrumblyZoneClass
//   [ ] 0x4056e0  _GLOBAL__I_4056e0
//   [ ] 0x4056f0  CKSrvBonus_SpawnBonuses_ViaEngine_maybe  [dead]
//   [ ] 0x405720  CKHkCrumblyZone_CollapseAndSpawnBonuses_maybe
//   [ ] 0x4057b0  CKHkS08CrumblyZone_IsInCameraView_maybe
//   [ ] 0x405930  CKHkCrumblyZone_UpdateAnimation_maybe
//   [ ] 0x405a18  CKHkCrumblyZone_IsAnimEndReached_maybe  [dead]
//   [ ] 0x405a48  CKHkCrumblyZone_UpdateResetAnim_maybe
//   [ ] 0x405ae8  CKHkCrumblyZone_AddRumbleRequestKind1_maybe  [dead]
//   [x] 0x405b40  CKHkCrumblyZone_SetGroundSets_maybe
//   [ ] 0x405c30  CKHkCrumblyZone_CountHeroesOnZone_maybe
//   [ ] 0x405d18  CKHkCrumblyZone_PickRandomStageMotionTargetByMode_maybe
//   [x] 0x406080  CKHkCrumblyZone_PostLoad
//   [ ] 0x406128  CKHkCrumblyZone_DeleteArray
//   [x] 0x4061c8  CKHkCrumblyZone_Create
//   [ ] 0x406278  CKHkCrumblyZone_GetHitPointsProperty_maybe
//   [ ] 0x406280  CKHkCrumblyZone_IsIntactProperty_maybe
//   [x] 0x406290  CKHkCrumblyZone_SetDefaultState
//   [ ] 0x406308  CKHkCrumblyZone_SetGameState
//   [ ] 0x406398  CKHkCrumblyZone_Destroy
//   [ ] 0x406410  CKHkCrumblyZone_UpdateStageNodeMotion_maybe
//   [ ] 0x406810  CKHkCrumblyZone_RecursiveRegistration
//   [ ] 0x406c20  CKHkCrumblyZone_GetInfo
//   [ ] 0x406d88  CKHkCrumblyZone_AddRumbleRequestKind0_maybe  [dead]
//   [x] 0x406de0  CKHkCrumblyZone_Start
//   [x] 0x406f90  CKHkCrumblyZone_ShowStageNode
//   [ ] 0x407168  CKHkCrumblyZone_CreateArray
//   [ ] 0x4072a8  CKHkCrumblyZone_vfF8
//   [ ] 0x407410  CKHkCrumblyZone_PlaceEffectNodeB0_maybe
//   [ ] 0x407648  CKHkCrumblyZone_PlaceEffectNodeB8_maybe
//   [ ] 0x407880  CKHkCrumblyZone_TriggerCollapse_maybe
//   [ ] 0x4082f8  CKHkCrumblyZone_ResetStageRecursive_maybe
//   [ ] 0x408538  CKHkCrumblyZone_ResetStagesWithAnim_maybe
//   [ ] 0x4085d8  CKHkCrumblyZone_Restore
//   [ ] 0x408e58  CKHkCrumblyZone_ForceBroken_maybe
//   [ ] 0x408fe8  CKHkCrumblyZone_Crumble
//   [ ] 0x40aa28  CKHkCrumblyZone_UpdateCrumbleAnim_maybe
//   [ ] 0x40aab8  CKHkCrumblyZone_StartCrumble_maybe
//   [ ] 0x40abc0  CKHkCrumblyZone_ApplyHitDamageType4_maybe
//   [ ] 0x40ae70  CKHkCrumblyZone_ApplyHitDamageType8_maybe
//   [ ] 0x40b120  CKHkCrumblyZone_OnHit_maybe
//   [ ] 0x40b500  CKHkCrumblyZone_MessageProc
//   [ ] 0x40bcd8  CKHkCrumblyZone_OnDeactivate
//   [x] 0x40bf00  CKHkCrumblyZone_OnActivate
//   [ ] 0x40c2f8  CKHkCrumblyZone_Update
//   [ ] 0x40c7d8  CKHkCrumblyZone_Restart
//   [x] 0x40ca50  CKHkCrumblyZone_Load
//   [ ] 0x40e6d0  CKHkCrumblyZone_Save
//
//   [ ] 0x9c1178  CKHkCrumblyZone_IsKindOfClass  [inline]
//   [ ] 0x9c11d0  CKHkCrumblyZone_GetClassType  [inline]
//   [ ] 0x9c11d8  CKHkCrumblyZone_GetClassID  [inline]
//   [ ] 0x9c11e0  CKHkCrumblyZone_vf100  [inline]
//   [ ] 0x9c11e8  CKHkCrumblyZone_Destructor  [inline]
//   [ ] 0x9c1388  CKHkCrumblyZone_DeletingDestructor  [inline]
//   [ ] 0x9c1538  CKHkCrumblyZone_UpdatePathBlocking_maybe  [inline]
#include "k2000/hooks/CKHkCrumblyZone.h"
#include "k2000/scenegraph/CAnimatedNode.h"
#include "k2000/dictionaries/CAnimationDictionary.h"

#include <cstring>

#include "Renderware/rwcore/RwCamera.h"
#include "k2000/components/CKBonusData.h"
#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/Mat4.h"
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
    m_unk120[8] = 1;
    for (int i = 0; i < 8; ++i) m_unk120[i] = 0;
    CKHkActorBase::Start();
}

namespace {
CSGLeaf* Leaf(IKSerializable* node) { return static_cast<CSGLeaf*>(node); }
void Hide(IKSerializable* node) { Leaf(node)->m_sgProperties = (Leaf(node)->m_sgProperties & 0xfffffffbu) | 4u; }
void Show(IKSerializable* node) { Leaf(node)->m_sgProperties &= 0xfffffffbu; }
}  // namespace

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
// STUB(C2.7): CKHkActorBase_d82_maybe_OnActivate 0x3f7338 (ActiveActorList_AddUnique_maybe 0x3f80d0: the zone joins
// the meca group's active actor list, which updates it: hits and crumbling are the first fight's) and
// CKHkCrumblyZone_UpdatePathBlocking_maybe 0x9c1538 (the path-finding boxes the zone blocks, CKSrvPathFinding).
// The collision side: a zone showing its safe leaf moves its +0xa4 volumes under the zone's node (the old parent's vt+0x78,
// the node's vt+0x70) and switches them on (CKSrvCollision_EnableVolume 0x192090), then its ground sets (SetGroundSets);
// +0x68 counts the heroes whose ground object (CKHkS08Hero_GetGroundObject_maybe 0x363c40) is the zone's ground +0x24.
// With an animation dictionary (+0x17c) the zone's node plays its first animation from 0 (CAnimatedNode_PlayAnim_maybe
// 0xc98b8, no restart).
void CKHkCrumblyZone::VfA0() {
    const RwFrame* frame = static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame;
    std::memcpy(m_pUnk74[1], &frame->modelling, sizeof(CMatrix34));
    static_cast<CKBonusData*>(m_pUnk10C)->ResetRuntime();  // 0x00126d90
    m_flags158 &= 0xfffcffffu;
    CKSrvCollision* collision = static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision);
    if (m_unk188 == 0 && (m_flags158 & 0x400) == 0) {
        ShowStageNode(m_pBrokenLeaf);
        SetGroundSets(0);  // 0x00405b40
        // STUB(C2.7): CKHkCrumblyZone_UpdatePathBlocking_maybe 0x9c1538 (the path-finding boxes, CKSrvPathFinding).
        m_flags158 &= 0xffffbfffu;
    } else {
        ShowStageNode(m_pSafeLeaf);
        for (uint32_t i = 0; i < m_vUnkA4.m_ui32NbUsedElt; ++i) {
            CSGLeaf* volume = static_cast<CSGLeaf*>(m_vUnkA4.m_pBlock[i].m_pUnk0);
            if (volume->m_pParent != nullptr) volume->m_pParent->RemoveChild(volume);    // vt+0x78
            static_cast<CSGBranch*>(m_pKGLObject)->AddChild(volume);                     // vt+0x70
            collision->EnableVolume(static_cast<IKBoundingVolume*>(m_vUnkA4.m_pBlock[i].m_pUnk0));  // 0x00192090
        }
        SetGroundSets(1);  // 0x00405b40
        // STUB(C2.7): CKHkCrumblyZone_UpdatePathBlocking_maybe 0x9c1538 (the path-finding boxes, CKSrvPathFinding).
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
    m_unk120[8] = 1;  // +0x128
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
