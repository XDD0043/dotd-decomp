// CKGrpS08Enemy_2.cpp - reconstructed original translation unit 0x266d20-0x26a1b8 (GAME_TOC1, main_toc1), 58 functions, 48 live.
// Primary class: CKGrpS08Enemy  key 0xa44  category Group  size 0x290  vtable 0xb215f8
// Other owners: CKS08FightZoneCpnt (3)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x266d20  CKGrpS08Enemy_Delete
//   [x] 0x266d70  CKGrpS08Enemy_vfF8  (GetKindTableF8, CKGrpS08Enemy.h)
//   [x] 0x266d88  CKGrpS08Enemy_vfFC  (GetKindTableFC, CKGrpS08Enemy.h)
//   [x] 0x266da0  CKGrpS08Enemy_vf100  (GetKindTable100, CKGrpS08Enemy.h)
//   [x] 0x266db8  CKGrpS08Enemy_Pause  (empty: IKBaseGroup's Pause)
//   [x] 0x266dc0  CKGrpS08Enemy_Resume  (empty: IKBaseGroup's Resume)
//   [x] 0x266dc8  CKGrpS08Enemy_vfB8  (returns 1: undeclared slot, see CKGrpS08Enemy.h)
//   [x] 0x266dd0  CKGrpS08Enemy_vf150  (CanTransferEnemy, CKGrpS08Enemy.h)
//   [x] 0x266dd8  CKGrpS08Enemy_vf178  (CKGrpS08Enemy.h)
//   [ ] 0x266e40  KStub_Nop_266e40  [dead]
//   [ ] 0x266e48  KStub_Nop_266e48  [dead]
//   [ ] 0x266e50  CKGrpS08Enemy_GetTriggerProp64_2  [dead]
//   [ ] 0x266e70  CKGrpS08Enemy_GetTriggerProp65_2  [dead]
//   [ ] 0x266e90  KStub_Return0_266e90  [dead]
//   [ ] 0x266e98  KStub_Nop_266e98  [dead]
//   [x] 0x266ea0  CKGrpS08Enemy_CountGroundedWeapons_maybe
//   [ ] 0x266ff8  FUN_00266ff8  [dead]
//   [x] 0x267090  CKGrpS08Enemy_SignalEnemyHit_maybe
//   [ ] 0x2670c8  CKGrpS08Enemy_ResetMembersAwarenessState_maybe  [dead]
//   [x] 0x267138  CKGrpS08Enemy_ReleaseAttackSlot
//   [x] 0x267220  CKGrpS08Enemy_vf164
//   [x] 0x267260  CKGrpS08Enemy_ReserveAttackSlot_maybe
//   [x] 0x267368  CKGrpS08Enemy_vf168  (AllocSaveRecord)
//   [ ] 0x267398  CKGrpS08Enemy_ResetAttackSlotState_maybe  [dead]
//   [x] 0x267478  CKGrpS08Enemy_Stop
//   [ ] 0x2674d0  CKGrpS08Enemy_Save
//   [x] 0x2674f8  CKGrpS08Enemy_RecursiveRegistration
//   [x] 0x267568  CKGrpS08Enemy_Destroy  (IKGrpEnemy::Destroy)
//   [x] 0x267590  CKGrpS08Enemy_DeleteArray
//   [x] 0x267630  CKGrpS08Enemy_Create
//   [x] 0x2676e0  CKGrpS08Enemy_vf190  (CKGrpS08Enemy.h)
//   [x] 0x267710  CKGrpS08Enemy_vf18C  (CKGrpS08Enemy.h)
//   [x] 0x267740  CKGrpS08Enemy_vf188  (CKGrpS08Enemy.h)
//   [x] 0x267770  CKGrpS08Enemy_vf184  (CKGrpS08Enemy.h)
//   [ ] 0x2677a0  RegisterCKGrpS08EnemyClass
//   [ ] 0x267828  _GLOBAL__D_267828
//   [ ] 0x267838  _GLOBAL__I_267838
//   [x] 0x267848  CKGrpS08Enemy_CanReserveAttackSlot_maybe
//   [ ] 0x2678a8  CKS08FightZoneCpnt_FindFreeCristalOrb_maybe  [dead]
//   [x] 0x267950  CKS08FightZoneCpnt_RemoveCristalOrb_maybe  (CKGrpS08Enemy::RemoveCristalOrb (the enemy group's +0x1b0))
//   [x] 0x2679f0  CKS08FightZoneCpnt_CompleteObjective_maybe
//   [x] 0x267a68  CKGrpS08Enemy_PostLoad
//   [x] 0x267cb8  CKGrpS08Enemy_vf15C
//   [x] 0x267d68  CKGrpS08Enemy_GetHeroMatrix
//   [x] 0x267f10  CKGrpS08Enemy_GetInfo
//   [x] 0x267ff8  CKGrpS08Enemy_MessageProc
//   [x] 0x268178  CKGrpS08Enemy_SignalAlert_maybe
//   [x] 0x2681d0  CKGrpS08Enemy_vf160
//   [x] 0x2683a0  UpdateCKGrpS08Enemy
//   [x] 0x268600  CKGrpS08Enemy_CreateArray
//   [x] 0x268738  CKGrpS08Enemy_MoveAttackerToBack_maybe
//   [x] 0x268898  CKGrpS08Enemy_StartAttackCooldownAndRequeue_maybe
//   [x] 0x268a60  CKGrpS08Enemy_ReleaseAttackSlotOfType_maybe
//   [x] 0x268be0  CKGrpS08Enemy_vf16C  (SaveRecord)
//   [x] 0x268d28  CKGrpS08Enemy_Restart
//   [x] 0x268eb8  CKGrpS08Enemy_Start
//   [x] 0x268fe0  CKGrpS08Enemy_vf170  (LoadRecord)
//   [x] 0x269118  CKGrpS08Enemy_Load
//
//   [ ] 0x9bb468  CKGrpS08Enemy_IsKindOfClass  [inline]
//   [ ] 0x9bb4c8  CKGrpS08Enemy_GetClassType  [inline]
//   [ ] 0x9bb4d0  CKGrpS08Enemy_GetClassID  [inline]
//   [ ] 0x9bb4d8  CKGrpS08Enemy_vfCC  [inline]
//   [x] 0x9bb4e0  CKGrpS08Enemy_vfF4  [inline]
//   [ ] 0x9bb4e8  CKGrpS08Enemy_vf104  [inline]
//   [ ] 0x9bb4f8  CKGrpS08Enemy_vf108  [inline]
//   [ ] 0x9bb508  CKGrpS08Enemy_vf10C  [inline]
//   [ ] 0x9bb510  CKGrpS08Enemy_vf110  [inline]
//   [ ] 0x9bb520  CKGrpS08Enemy_vf114  [inline]
//   [ ] 0x9bb530  CKGrpS08Enemy_vf118  [inline]
//   [ ] 0x9bb540  CKGrpS08Enemy_vf11C  [inline]
//   [ ] 0x9bb550  CKGrpS08Enemy_vf120  [inline]
//   [ ] 0x9bb560  CKGrpS08Enemy_vf124  [inline]
//   [ ] 0x9bb570  CKGrpS08Enemy_vf128  [inline]
//   [ ] 0x9bb580  CKGrpS08Enemy_vf12C  [inline]
//   [ ] 0x9bb590  CKGrpS08Enemy_vf130  [inline]
//   [ ] 0x9bb5a8  CKGrpS08Enemy_vf134  [inline]
//   [ ] 0x9bb5b0  CKGrpS08Enemy_vf138  [inline]
//   [ ] 0x9bb5c8  CKGrpS08Enemy_vf13C  [inline]
//   [ ] 0x9bb5e0  CKGrpS08Enemy_vf140  [inline]
//   [ ] 0x9bb5f0  CKGrpS08Enemy_vf144  [inline]
//   [ ] 0x9bb5f8  CKGrpS08Enemy_vf148  [inline]
//   [ ] 0x9bb600  CKGrpS08Enemy_vf154  [inline]
//   [x] 0x9bb608  CKGrpS08Enemy_vf158  [inline]
//   [ ] 0x9bb610  CKGrpS08Enemy_vf174  [inline]
//   [ ] 0x9bb618  CKGrpS08Enemy_GetTriggerProp67  [inline]
//   [ ] 0x9bb628  CKGrpS08Enemy_GetTriggerProp64  [inline]
//   [x] 0x9bb648  CKGrpS08Enemy_vfEC  [inline]
//   [x] 0x9bb668  CKGrpS08Enemy_vfF0  [inline]
//   [ ] 0x9bb688  CKGrpS08Enemy_GetTriggerProp65  [inline]
//   [ ] 0x9bb6a8  KStub_Return0_9bb6a8  [inline]
//   [ ] 0x9bb6b0  CKGrpS08Enemy_DeletingDestructor  [inline]
//   [ ] 0x9bb7f8  CKGrpS08Enemy_Destructor  [inline]
#include "Spyro2008/logic/CKS08EnemyAttack.h"
#include "Spyro2008/groups/CKGrpS08Enemy.h"
#include "Spyro2008/logic/CKS08AccessoryManager.h"

#include <cstring>

#include "Spyro2008/components/CKS08FightZoneCpnt.h"
#include "Spyro2008/hooks/CKHkS08Enemy.h"
#include "Spyro2008/hooks/CKHkS08Enemy_xforkA.h"
#include "Spyro2008/hooks/CKHkS08Weapon.h"
#include "Spyro2008/logic/CKS08AccessoryManager.h"
#include "Spyro2008/logic/CKS08GameStructure.h"
#include "Renderware/rwcore/RwCamera.h"
#include "Spyro2008/groups/CKGrpS08Hero.h"
#include "Spyro2008/hooks/IKHkHero.h"
#include "k2000/groups/CKGrpFightZone.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/scenegraph/CSGLeaf.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/misc/Engine.h"
#include "k2000/system/IKTime.h"
#include "k2000/cameras/IKCamera.h"
#include "k2000/components/CKCameraEventCpnt.h"
#include "k2000/groups/TVectorPush.h"
#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"
#include "k2000/core/IKInfo.h"

// 0x00266ea0 CKGrpS08Enemy_CountGroundedWeapons_maybe
uint32_t CKGrpS08Enemy::CountGroundedWeapons() {
    IKBaseGroup* weapons = static_cast<IKBaseGroup*>(m_pUnk190);
    uint32_t members = 0;
    for (IKHook* hook = *reinterpret_cast<IKHook**>(weapons->GetMemberListHead()); hook != nullptr;
         hook = hook->m_pNextHook) {
        ++members;  // vt+0xb0, the next at +0x14
    }
    uint32_t grounded = 0;
    for (uint32_t i = 0; i < members; ++i) {
        IKHook* hook = *reinterpret_cast<IKHook**>(weapons->GetMemberListHead());
        for (uint32_t k = 0; k < i; ++k) hook = hook->m_pNextHook;
        if (static_cast<CKHkS08Weapon*>(hook)->m_landedAB != 0) ++grounded;
    }
    return grounded;
}

// 0x00269118 CKGrpS08Enemy_Load
int32_t CKGrpS08Enemy::Load(IKFile* file, int32_t type) {
    IKGrpEnemy::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        for (CTriggerStarter& trigger : m_aTriggers) trigger.Load(file, K_LEVEL_PLATEFORMS);
    }
    // Not under the type test: the rest is read for every type.
    if (m_vUnk180.m_pBlock == nullptr) {
        m_vUnk180.m_ui32NbElt = 1;
        m_vUnk180.m_pBlock = static_cast<IKSerializable**>(Mem_AllocAligned16(sizeof(IKSerializable*)));
    }
    IKFile_ReadRef(file, &m_pUnk17c);
    uint32_t count = 0;
    ReadU32LE(file, &count);
    if (m_vUnk180.m_ui32NbUsedElt != 0) {
        if (m_vUnk180.m_pBlock != nullptr) Mem_FreeAligned16(m_vUnk180.m_pBlock);
        m_vUnk180.m_ui32NbUsedElt = 0;
        m_vUnk180.m_pBlock = nullptr;
    }
    if (m_vUnk180.m_pBlock == nullptr) {
        m_vUnk180.m_ui32NbElt = 1;
        m_vUnk180.m_pBlock = static_cast<IKSerializable**>(Mem_AllocAligned16(sizeof(IKSerializable*)));
    }
    // At most 9 references are kept; the others are read into a local and dropped.
    const uint32_t kept = count > 9 ? 9 : count;
    for (uint32_t i = 0; i < kept; ++i) {
        TVector_GrowIfFull(m_vUnk180);
        ++m_vUnk180.m_ui32NbUsedElt;
        IKFile_ReadRef(file, &m_vUnk180.m_pBlock[i]);
    }
    for (uint32_t i = 9; i < count; ++i) {
        IKSerializable* dropped = nullptr;
        IKFile_ReadRef(file, &dropped);
    }
    ReadU32LE(file, &m_unk194);
    IKFile_ReadRef(file, &m_pUnk190);
    if (m_vUnk19c.m_pBlock == nullptr) {
        m_vUnk19c.m_ui32NbElt = 1;
        m_vUnk19c.m_pBlock = static_cast<IKSerializable**>(Mem_AllocAligned16(sizeof(IKSerializable*)));
    }
    IKFile_ReadRef(file, &m_pUnk198);
    IKFile_ReadRef(file, &m_pUnk1e4);
    IKFile_ReadRef(file, &m_pUnk1ec);
    // Each list gets 1.0, 2.0, 3.0 (TOC 0x5a0..0x5a8) pushed at its count, which grows by 3.
    // BUG(original): no capacity check; with a count above 0 (a second Load) the pushes run past the three
    // floats into the count and the next list.
    for (SFloat3List& list : m_aFloat3Lists) {
        const uint32_t n = list.m_ui32NbElt;
        list.m_ui32NbElt = n + 3;
        list.m_af[n + 0] = 0x1p+0f;
        list.m_af[n + 1] = 0x1p+1f;
        list.m_af[n + 2] = 0x1.8p+1f;
    }
    for (SFloat3List& list : m_aFloat3Lists) {
        ReadF32LE(file, &list.m_af[0]);
        ReadF32LE(file, &list.m_af[1]);
        ReadF32LE(file, &list.m_af[2]);
    }
    ReadF32LE(file, &m_unk238[0]);   // +0x238
    ReadF32LE(file, &m_unk238[1]);   // +0x23c
    ReadF32LE(file, &m_unk238[2]);   // +0x240
    ReadF32LE(file, &m_unk238[3]);   // +0x244
    ReadF32LE(file, &m_unk238[8]);   // +0x258
    IKFile_ReadRef(file, &m_pUnk264);
    ReadF32LE(file, &m_unk268[0]);   // +0x268
    ReadF32LE(file, &m_unk268[1]);   // +0x26c
    ReadF32LE(file, &m_unk268[2]);   // +0x270
    ReadF32LE(file, &m_unk238[9]);   // +0x25c
    ReadF32LE(file, &m_unk268[3]);   // +0x274
    ReadF32LE(file, &m_unk268[4]);   // +0x278
    ReadF32LE(file, &m_unk238[10]);  // +0x260
    ReadF32LE(file, &m_unk268[5]);   // +0x27c
    ReadF32LE(file, &m_unk268[6]);   // +0x280
    ReadF32LE(file, &m_unk268[7]);   // +0x284
    ReadF32LE(file, &m_unk238[4]);   // +0x248
    ReadF32LE(file, &m_unk238[5]);   // +0x24c
    ReadF32LE(file, &m_unk238[6]);   // +0x250
    ReadF32LE(file, &m_unk238[7]);   // +0x254
    ReadF32LE(file, &m_unk268[8]);   // +0x288
    ReadF32LE(file, &m_unk268[9]);   // +0x28c
    return 1;
}

namespace {
// 0x00165af8 ScriptedCameraHandle_Reset_maybe (k2000/components/CKCameraEventCpnt.cpp, owner: family hooks;
// local copy until that port lands, see the C2.2 spyro report). The camera's vt+0x6c is IKCamera's
// ResetTrack (CKCamera 0x13db38 copies the track state back, CKCameraPathTrack 0x9a7358 clears +0x5c,
// CKCameraClassicTrack3 0x9a7d00 is empty).
void ScriptedCameraHandle_Reset(CKCameraEventCpnt* handle) { handle->Reset(); }
}  // namespace

// 0x00268eb8 CKGrpS08Enemy_Start
void CKGrpS08Enemy::Start() {
    IKGrpEnemy::Start();  // 0x2659d8
    m_unk178 = 0;
    m_pFightZoneCpnt170 = nullptr;
    m_unk154 = 0;
    m_unk158 = 0;
    m_unk15c = 0;
    m_unk160 = 0;
    if (m_vUnk164.m_pBlock == nullptr) {
        m_vUnk164.m_ui32NbElt = 1;
        m_vUnk164.m_pBlock = static_cast<IKSerializable**>(Mem_AllocAligned16(sizeof(IKSerializable*)));
    }
    m_unk1dc = 0;
    m_unk1bc = 0;
    m_unk1d0[0] = 0;
    m_unk1d0[1] = 0;
    m_unk1d0[2] = 0;
    m_unk1e0 = 20.0f;  // TOC 0x518
    if (m_vUnk1b0.m_pBlock == nullptr) {
        m_vUnk1b0.m_ui32NbElt = 1;
        m_vUnk1b0.m_pBlock = static_cast<IKSerializable**>(Mem_AllocAligned16(sizeof(IKSerializable*)));
    }
    m_unk1f0 = 0.3f;  // TOC 0x51c
    static_cast<CKS08AccessoryManager*>(m_pUnk1ec)->ResetRuntime();  // vt+0x50 0x2c7b80
    ScriptedCameraHandle_Reset(static_cast<CKCameraEventCpnt*>(m_pUnk264));
    m_unk150 = 0.0f;
    m_unk14c = 0.0f;
}

// 0x00268d28 CKGrpS08Enemy_Restart (vt+0x54): the base's; every active enemy (the count read once) hidden (its node's
// bit 2) and out of its main state machine; then Start's run-time fields (no camera reset; the accessory manager's
// reinit, vt+0x54, instead of its vt+0x50).
void CKGrpS08Enemy::Restart() {
    IKGrpEnemy::Restart();  // 0x2659f8
    const uint32_t count = m_ui32NbActiveEnemies;
    for (uint32_t i = 0; i != count; ++i) {
        CKHkS08Enemy* enemy = static_cast<CKHkS08Enemy*>(m_apActiveEnemies[i]);
        CSGLeaf* node = static_cast<CSGLeaf*>(enemy->m_pKGLObject);
        node->m_sgProperties = node->m_sgProperties | 4u;  // rlwinm 29,1,31 / 3,0,31 / ori 4
        enemy->ResetMainStateMachine();  // 0x0028aa70
    }
    m_pFightZoneCpnt170 = nullptr;
    m_unk178 = 0;
    m_unk154 = 0;
    m_unk158 = 0;
    m_unk15c = 0;
    m_unk160 = 0;
    if (m_vUnk164.m_pBlock == nullptr) {
        m_vUnk164.m_ui32NbElt = 1;
        m_vUnk164.m_pBlock = static_cast<IKSerializable**>(Mem_AllocAligned16(sizeof(IKSerializable*)));
    }
    m_unk1dc = 0;
    m_unk1bc = 0;
    m_unk1d0[0] = 0;
    m_unk1d0[1] = 0;
    m_unk1d0[2] = 0;
    m_unk1e0 = 20.0f;  // TOC 0x518
    if (m_vUnk1b0.m_pBlock == nullptr) {
        m_vUnk1b0.m_ui32NbElt = 1;
        m_vUnk1b0.m_pBlock = static_cast<IKSerializable**>(Mem_AllocAligned16(sizeof(IKSerializable*)));
    }
    m_unk1f0 = 0.3f;  // TOC 0x51c
    static_cast<CKS08AccessoryManager*>(m_pUnk1ec)->ReinitRuntime();  // vt+0x54 0x2c7b30
    m_unk150 = 0.0f;
    m_unk14c = 0.0f;
}

namespace {
// 0x00a6fed8: the number of animation layers of each enemy kind (CKGrpS08Enemy_vf108); 0x00a6ff48: the number of
// trail nodes (vf128); 0x00a6ff68: the number of slots of a layer, indexed by kind + layer (vf130). The PS3's
// tables run on into other data after the nine kinds; the reads past them are not reproduced (no kind above 8).
const uint8_t kNbAnimLayers[16] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0};
const uint8_t kNbTrailNodes[16] = {6, 6, 6, 6, 6, 6, 6, 6, 6, 0, 0, 0, 0, 0, 0, 0};
const uint8_t kNbAnimLayerSlots[0x60] = {
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x02, 0x01, 0x01, 0x02, 0x02,
    0x02, 0x01, 0x07, 0x07, 0x02, 0x01, 0x07, 0x07, 0x01, 0x01, 0x07, 0x07, 0x02, 0x01, 0x0a, 0x0a,
    0x03, 0x01, 0x0d, 0x0d, 0x02, 0x01, 0x02, 0x02, 0x02, 0x01, 0x06, 0x06, 0x02, 0x00, 0x01, 0x01,
    0x03, 0x00, 0x01, 0x01, 0x03, 0x00, 0x01, 0x01, 0x08, 0x00, 0x01, 0x01, 0x08, 0x00, 0x01, 0x01,
    0x08, 0x00, 0x01, 0x01, 0x0b, 0x00, 0x01, 0x01, 0x0e, 0x00, 0x01, 0x01, 0x03, 0x00, 0x01, 0x01,
    0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
}  // namespace

// 0x009bb4f8 CKGrpS08Enemy_vf108
uint8_t CKGrpS08Enemy::GetNbAnimLayers(uint8_t kind) { return kNbAnimLayers[kind]; }
// 0x009bb570 CKGrpS08Enemy_vf128
uint8_t CKGrpS08Enemy::GetNbTrailNodes(uint8_t kind) { return kNbTrailNodes[kind]; }
// 0x009bb590 CKGrpS08Enemy_vf130 (BUG(original): the index is kind + layer, the tables overlap)
uint8_t CKGrpS08Enemy::GetNbAnimLayerSlots(uint8_t kind, uint8_t layer) { return kNbAnimLayerSlots[kind + layer]; }

// 0x00267cb8 CKGrpS08Enemy_vf15C: the zone becomes current (the base's), its component is remembered, bit 0 of +0x178
// set and bit 2 cleared, the timers and counters cleared, and the game structure's checkpoint snapshot taken.
void CKGrpS08Enemy::SetCurrentFightZone(CKGrpFightZone* zone) {
    IKGrpEnemy::SetCurrentFightZone(zone);  // 0x00265a20
    m_pFightZoneCpnt170 = zone->m_pFightZoneCpnt;
    m_unk178 |= 1u;
    m_unk150 = 0.0f;
    m_unk14c = 0.0f;
    m_unk154 = 0;
    m_unk158 = 0;
    m_unk15c = 0;
    m_unk160 = 0;
    m_unk178 &= ~4u;
    m_unk174 = 0;
    static_cast<CKS08GameStructure*>(g_pEngine->m_gameManager->m_gameStructure)->SaveCheckpointSnapshot();  // 0x0050ed60
}

// 0x002681d0 CKGrpS08Enemy_vf160: the zone stops being current (the base's); every weapon of the weapon pool whose byte
// +0xa8 is 0 gets vt+0xc8 and vt+0xcc (the list is walked by index, and the index and count step back after each one,
// as the original); the component forgotten when it is the zone's, then +0x1bc and +0x178 cleared.
void CKGrpS08Enemy::ClearCurrentFightZone(CKGrpFightZone* zone) {
    IKGrpEnemy::ClearCurrentFightZone(zone);  // 0x00265a38
    IKBaseGroup* pool = static_cast<IKBaseGroup*>(m_pUnk190);
    uint32_t count = 0;
    for (IKHook* hook = *reinterpret_cast<IKHook**>(pool->GetMemberListHead()); hook != nullptr; hook = hook->m_pNextHook) {
        ++count;
    }
    for (uint32_t i = 0; count > i; ++i) {
        IKHook* weapon = *reinterpret_cast<IKHook**>(pool->GetMemberListHead());  // vt+0xb0
        for (uint32_t j = 0; j < i; ++j) weapon = weapon->m_pNextHook;
        if (static_cast<CKHkS08Weapon*>(weapon)->m_inHandA8 == 0) {  // the byte +0xa8
            --i;
            --count;
            CKHkS08Weapon_ReleaseAtFightEnd(weapon);  // vt+0xc8, vt+0xcc
        }
    }
    if (m_pFightZoneCpnt170 == zone->m_pFightZoneCpnt) m_pFightZoneCpnt170 = nullptr;
    m_unk1bc = 0;
    m_unk178 = 0;
}

namespace {
// Whether an active enemy has its byte +0x239 set (CKHkS08Enemy's pending hit; the loop UpdateCKGrpS08Enemy inlines).
bool AnyActiveEnemyPendingHit(const IKGrpEnemy* group) {
    for (uint32_t i = 0; i < group->m_ui32NbActiveEnemies; ++i) {
        if (static_cast<const CKHkS08Enemy*>(group->m_apActiveEnemies[i])->m_unk239 != 0) return true;
    }
    return false;
}
}  // namespace

// 0x002683a0 UpdateCKGrpS08Enemy: the two timers counted down; while the current zone component's byte +0x10 is set,
// bit 1 of +0x178 ("a fight is on") follows the alarm bytes +0x1e8 / +0x1bc, the counter +0x154 and the enemies'
// pending hits: it is set (and the zone's trigger starter +0xf4 fired) when one of them holds, cleared when none does.
// Then +0x1e8 cleared, the accessory manager's frame, and +0x1f0 counted up to 0.3.
void CKGrpS08Enemy::Update(IKTime* clock) {
    if (m_unk14c > 0.0f) m_unk14c = m_unk14c - clock->m_afDeltaTime[0];
    if (m_unk150 > 0.0f) m_unk150 = m_unk150 - clock->m_afDeltaTime[0];
    CKS08FightZoneCpnt* cpnt = static_cast<CKS08FightZoneCpnt*>(m_pFightZoneCpnt170);
    if (cpnt != nullptr && cpnt->m_unk10 != 0) {
        const uint8_t alarm = m_unk1e8;
        bool done = false;
        if (alarm != 0 || m_unk154 != 0 || AnyActiveEnemyPendingHit(this) || m_unk1bc != 0) {
            if ((m_unk178 & 2u) == 0) {
                m_unk178 |= 2u;
                QueueTriggerSignals(&m_pCurrentFightZone->m_aTriggers[9]);  // +0xf4
                done = true;
            }
        }
        if (!done && alarm == 0 && m_unk154 == 0 && !AnyActiveEnemyPendingHit(this) && m_unk1bc == 0 &&
            (m_unk178 & 2u) != 0) {
            m_unk178 &= ~2u;
        }
    }
    m_unk1e8 = 0;
    CKS08AccessoryManager_UpdateActiveItems(m_pUnk1ec, clock);  // vt+0x5c 0x2c78e0
    if (m_unk1f0 < 0.3f) m_unk1f0 = m_unk1f0 + clock->m_afDeltaTime[0];  // TOC 0x51c
}

// 0x002679f0 CKS08FightZoneCpnt_CompleteObjective_maybe
void CKGrpS08Enemy::CompleteObjective() {
    QueueTriggerSignals(&m_aTriggers[2]);  // +0x134
    if (m_pCurrentFightZone != nullptr) {
        m_pCurrentFightZone->SetCompleted(1);  // 0x26e348
        static_cast<CKS08GameStructure*>(g_pEngine->m_gameManager->m_gameStructure)->SaveCheckpointSnapshot();  // 0x0050ed60
    }
    m_unk1bc = 0;
}

// 0x00268178 CKGrpS08Enemy_SignalAlert_maybe
void CKGrpS08Enemy::SignalAlert() {
    QueueTriggerSignals(&m_aTriggers[3]);                     // +0x13c
    QueueTriggerSignals(&m_pCurrentFightZone->m_aTriggers[9]);  // +0x30, +0xf4
}

// 0x00267d68 CKGrpS08Enemy_GetHeroMatrix (the hero's targeting position: IKHkHero_GetTargetingPositionPtr_maybe 0x363c78,
// its +0x570 unless bit 1 is set, then its frame's LTM position; natively RwFrameGetLTM makes it current).
void CKGrpS08Enemy::GetHeroMatrix(uint8_t hero, CMatrix34* out) {
    CKGrpS08Hero* heroes = static_cast<CKGrpS08Hero*>(g_pEngine->m_gameManager->m_unk04[1]);
    if (heroes == nullptr) return;
    IKSerializable* chosen;
    if (hero == 1) {
        chosen = heroes->m_apHeros[0];  // GetHeroByDragonIndex 0x2ca080
    } else if (hero < 1) {
        chosen = heroes->m_apControlledHeroes[0];  // GetControlledHeroArray 0x2ca0e0
    } else if (hero == 2) {
        chosen = heroes->m_apHeros[1];
    } else {
        return;
    }
    IKHkHero* h = static_cast<IKHkHero*>(chosen);
    RwFrame* frame = static_cast<CSGMovable*>(h->m_pKGLObject)->m_pRwFrame;
    std::memcpy(out, &frame->modelling, sizeof(CMatrix34));
    const CVector3* position = (h->m_bitArray & 2u) == 0 ? reinterpret_cast<const CVector3*>(&h->m_unk570)
                                                          : reinterpret_cast<const CVector3*>(&FrameLtm(frame)->pos);
    out->m_pos = *position;
    out->m_ui32Flags &= ~0x20000u;
}

// 0x00267a68 CKGrpS08Enemy_PostLoad: IKGrpEnemy's (the trigger starters' PostLoads, for the level type, do nothing); the
// run-time words +0x1bc..+0x1dc cleared and +0x1e0 = 20; +0x1ac = the first child group of +0x198, the others appended
// to +0x19c.
int32_t CKGrpS08Enemy::PostLoad(int32_t type) {
    IKGrpEnemy::PostLoad(type);  // 0x265b08
    m_unk1bc = 0;
    for (uint32_t& w : m_unk1c0) w = 0;
    for (uint32_t& w : m_unk1d0) w = 0;
    m_unk1dc = 0;
    m_unk1e0 = 20.0f;  // TOC 0x518
    IKBaseGroup* pools = static_cast<IKBaseGroup*>(m_pUnk198);
    m_pUnk1ac = pools->m_lChilds;
    uint32_t count = 0;
    for (IKBaseGroup* child = pools->m_lChilds; child != nullptr; child = child->m_pNextGroup) ++count;
    for (uint32_t i = 1; i < count; ++i) {
        IKBaseGroup* child = static_cast<IKBaseGroup*>(m_pUnk198)->m_lChilds;
        for (uint32_t k = 0; k < i; ++k) child = child->m_pNextGroup;
        if (m_vUnk19c.m_ui32NbElt == m_vUnk19c.m_ui32NbUsedElt) {
            uint32_t capacity = m_vUnk19c.m_ui32NbUsedElt + 1;
            if (capacity == 0) capacity = 1;
            m_vUnk19c.m_pBlock = static_cast<IKSerializable**>(
                Mem_ReallocAligned16(m_vUnk19c.m_pBlock, capacity * static_cast<uint32_t>(sizeof(IKSerializable*))));
            m_vUnk19c.m_ui32NbElt = capacity;
        }
        m_vUnk19c.m_pBlock[m_vUnk19c.m_ui32NbUsedElt++] = child;
    }
    return 1;
}

namespace {
uint32_t& ReservedOfCategory(CKGrpS08Enemy* group, int32_t category) {
    return (&group->m_unk158)[category];  // +0x158 + 4 x category
}
}  // namespace

// 0x00267848 CKGrpS08Enemy_CanReserveAttackSlot_maybe: room in the total (unsigned compares) and in the category.
uint8_t CKGrpS08Enemy::CanReserveAttackSlot(int32_t category) {
    const CKS08FightZoneCpnt* zone = m_pCurrentFightZone->m_pFightZoneCpnt;  // +0x30 -> +0x2c
    if (!(m_unk154 < zone->m_unk20)) return 0;
    return ReservedOfCategory(this, category) < zone->m_unk24[category] ? 1 : 0;
}

// 0x00267260 CKGrpS08Enemy_ReserveAttackSlot_maybe: both counts up, `enemy` appended to the holders (+0x164; a full
// vector grows by one, Mem_ReallocAligned16).
void CKGrpS08Enemy::ReserveAttackSlot(int32_t category, IKSerializable* enemy) {
    m_unk154 = m_unk154 + 1;
    ReservedOfCategory(this, category) = ReservedOfCategory(this, category) + 1;
    TVector<IKSerializable*, 1>& holders = m_vUnk164;
    if (holders.m_ui32NbElt == holders.m_ui32NbUsedElt) {
        uint32_t capacity = holders.m_ui32NbUsedElt + 1;
        if (capacity == 0) capacity = 1;
        holders.m_pBlock = static_cast<IKSerializable**>(
            Mem_ReallocAligned16(holders.m_pBlock, (capacity * sizeof(IKSerializable*)) & ~3u));  // 0x00053190
        holders.m_ui32NbElt = capacity;
    }
    holders.m_pBlock[holders.m_ui32NbUsedElt] = enemy;
    holders.m_ui32NbUsedElt = holders.m_ui32NbUsedElt + 1;
}

// 0x00267138 CKGrpS08Enemy_ReleaseAttackSlot: `enemy` out of the holders (the last one takes its place), both counts
// down; nothing when it does not hold a slot.
void CKGrpS08Enemy::ReleaseAttackSlot(int32_t category, IKSerializable* enemy) {
    TVector<IKSerializable*, 1>& holders = m_vUnk164;
    const uint32_t count = holders.m_ui32NbUsedElt;
    if (count == 0) return;
    for (uint32_t i = 0; i < count; ++i) {
        if (holders.m_pBlock[i] != enemy) continue;
        const uint32_t last = count - 1;
        holders.m_ui32NbUsedElt = last;
        if (i != last) holders.m_pBlock[i] = holders.m_pBlock[last];
        m_unk154 = m_unk154 - 1;
        ReservedOfCategory(this, category) = ReservedOfCategory(this, category) - 1;
        return;
    }
}

// 0x00268738 CKGrpS08Enemy_MoveAttackerToBack_maybe: `enemy` moved to the end of the slot holders (+0x164; nothing when it
// holds none; the later ones move down, memmove).
void CKGrpS08Enemy::MoveAttackerToBack(IKSerializable* enemy) {
    TVector<IKSerializable*, 1>& holders = m_vUnk164;
    const uint32_t count = holders.m_ui32NbUsedElt;
    uint32_t i = 0;
    while (i < count && holders.m_pBlock[i] != enemy) ++i;
    if (i == count) return;
    const uint32_t last = count - 1;
    holders.m_ui32NbUsedElt = last;
    std::memmove(&holders.m_pBlock[i], &holders.m_pBlock[i + 1], (last - i) * sizeof(holders.m_pBlock[0]));  // TocBridge_memmove
    if (holders.m_ui32NbUsedElt == holders.m_ui32NbElt) {
        uint32_t capacity = holders.m_ui32NbUsedElt + 1;
        if (capacity == 0) capacity = 1;
        holders.m_pBlock = static_cast<IKSerializable**>(
            Mem_ReallocAligned16(holders.m_pBlock, (capacity * sizeof(IKSerializable*)) & ~3u));  // 0x00053190
        holders.m_ui32NbElt = capacity;
    }
    holders.m_pBlock[holders.m_ui32NbUsedElt] = enemy;
    holders.m_ui32NbUsedElt = holders.m_ui32NbUsedElt + 1;
}

// 0x00268898 CKGrpS08Enemy_StartAttackCooldownAndRequeue_maybe (vt+0x17c). Dragon 0 with its timer still running tests
// the other dragon's timer, as the original does.
void CKGrpS08Enemy::StartAttackCooldown(uint8_t dragon, IKSerializable* enemy) {
    if (dragon == 0 && m_unk14c <= 0.0f) {
        m_unk14c = m_unk14c + m_pCurrentFightZone->m_pFightZoneCpnt->m_unk18;
    } else if (m_unk150 <= 0.0f) {
        m_unk150 = m_unk150 + m_pCurrentFightZone->m_pFightZoneCpnt->m_unk1c;
    }
    MoveAttackerToBack(enemy);  // the same requeue, inlined
}

// 0x00268a60 CKGrpS08Enemy_ReleaseAttackSlotOfType_maybe: with slots reserved in all and in `category`, from the last
// holder down: one with an attack (+0x73c) of that category (CKHkS08Enemy_GetAttackSlotCategoryThunk_maybe 0x289370 on
// the attack's +0x08) clears its reservation (0x289120) and leaves the holders (the later ones move down, memmove).
void CKGrpS08Enemy::ReleaseAttackSlotOfType(int32_t category) {
    if (m_unk154 == 0 || ReservedOfCategory(this, category) == 0) return;
    TVector<IKSerializable*, 1>& holders = m_vUnk164;
    for (int32_t i = static_cast<int32_t>(m_unk154) - 1; i >= 0; --i) {
        CKHkS08Enemy* enemy = static_cast<CKHkS08Enemy*>(holders.m_pBlock[i]);
        if (enemy == nullptr || enemy->m_unk73c == nullptr) continue;
        if (CKHkS08Enemy::GetAttackSlotCategory(enemy->m_unk73c->m_unk08) != category) continue;
        static_cast<CKHkS08Enemy*>(holders.m_pBlock[i])->ClearAttackSlotReservation();  // 0x00289120
        const uint32_t count = holders.m_ui32NbUsedElt - 1;
        holders.m_ui32NbUsedElt = count;
        std::memmove(&holders.m_pBlock[i], &holders.m_pBlock[i + 1],
                     (count - static_cast<uint32_t>(i)) * sizeof(holders.m_pBlock[0]));  // TocBridge_memmove
        m_unk154 = m_unk154 - 1;
        ReservedOfCategory(this, category) = ReservedOfCategory(this, category) - 1;
        return;
    }
}

// 0x00267478 CKGrpS08Enemy_Stop (the manager is read without a test)
void CKGrpS08Enemy::Stop() {
    IKGrpEnemy::Stop();  // 0x002659e8 IKGrpEnemy_OnLevelExit_maybe (empty)
    static_cast<CKS08AccessoryManager*>(m_pUnk1ec)->ClearAccessories();  // vt+0x58 0x002c7818
}

// 0x00267ff8 CKGrpS08Enemy_MessageProc (vt+0x1c): the group's own result combined with IKGrpEnemy's (3 over 2 over the
// own one, 0 when IKGrpEnemy's is 0).
int32_t CKGrpS08Enemy::MessageProc(uint16_t message, void* data) {
    const uint8_t* bytes = static_cast<const uint8_t*>(data);
    int32_t own = 1;
    switch (message) {
    case 0x1305:
        m_unk178 = (m_unk178 & ~1u) | static_cast<uint32_t>(bytes[0]);
        own = 0;
        break;
    case 0x1306:
        m_unk178 = (m_unk178 & ~2u) | (static_cast<uint32_t>(bytes[0]) << 1);
        own = 0;
        break;
    case 0x1307:
        m_unk174 = bytes[0];
        own = 0;
        break;
    case 0x1309:
        m_unk178 = (m_unk178 & ~8u) | (static_cast<uint32_t>(bytes[0]) << 3);
        own = 0;
        break;
    case 0x940:
    case 0x1000:
    case 0x1001:
        own = 0;
        break;
    default:
        break;
    }
    const int32_t base = IKGrpEnemy::MessageProc(message, data);  // 0x00265ee0
    if (base == 3 || own == 3) return 3;
    if (base == 2 || own == 2) return 2;
    return base != 0 ? own : 0;
}

// 0x002674f8 CKGrpS08Enemy_RecursiveRegistration (vt+0x24)
void CKGrpS08Enemy::RecursiveRegistration(int32_t type) {
    IKGrpEnemy::RecursiveRegistration(type);  // 0x002661f0 (IKGroup_LevelReset 0x12a68)
    m_pUnk1e4->RecursiveRegistration(type);
}

// 0x00267f10 CKGrpS08Enemy_GetInfo (vt+0x40); found 0, else 1.
int32_t CKGrpS08Enemy::GetInfo(IKInfo* info, int32_t request) {
    if (request != kGetInfoValueAccessor) return 1;
    switch (info->m_ui32Id) {
    case 0x64: return AnswerInfo(info, &CKGrpS08Enemy::InfoInFight, 0);        // 0xb86ec8
    case 0x65: return AnswerInfo(info, &CKGrpS08Enemy::InfoFightOn, 0);        // 0xb86ee8
    case 0x66: return AnswerInfo(info, &CKGrpS08Enemy::InfoZero, 0);           // 0xb86f00
    case 0x67: return AnswerInfo(info, &CKGrpS08Enemy::InfoActiveEnemies, 1);  // 0xb86ce0
    default: return 1;
    }
}
uint32_t CKGrpS08Enemy::InfoInFight(IKSerializable* self, uint32_t) {
    return static_cast<CKGrpS08Enemy*>(self)->IsInFight();
}
uint32_t CKGrpS08Enemy::InfoFightOn(IKSerializable* self, uint32_t) {
    return static_cast<CKGrpS08Enemy*>(self)->IsFightOn();
}
uint32_t CKGrpS08Enemy::InfoZero(IKSerializable*, uint32_t) { return 0; }
uint32_t CKGrpS08Enemy::InfoActiveEnemies(IKSerializable* self, uint32_t) {
    return static_cast<CKGrpS08Enemy*>(self)->m_ui32NbActiveEnemies;
}

// 0x00267950 CKS08FightZoneCpnt_RemoveCristalOrb_maybe
void CKGrpS08Enemy::RemoveCristalOrb(IKSerializable* orb) {
    const uint32_t count = m_vUnk1b0.m_ui32NbUsedElt;
    if (count == 0) return;
    uint32_t i = 0;
    while (m_vUnk1b0.m_pBlock[i] != orb) {
        if (++i == count) return;
    }
    m_vUnk1b0.m_ui32NbUsedElt = count - 1;
    if (i == count - 1) return;
    m_vUnk1b0.m_pBlock[i] = m_vUnk1b0.m_pBlock[count - 1];
}

namespace {
// The record of CKGrpS08Enemy (0x38 bytes): IKGrpEnemy's, then four floats.
struct SS08SaveRecord : IKGrpEnemy::SSaveRecord {
    float m_unk28;  // +0x28
    float m_unk2c;  // +0x2c
    float m_unk30;  // +0x30
    float m_unk34;  // +0x34
};
}  // namespace

// 0x00267368 CKGrpS08Enemy_vf168
void* CKGrpS08Enemy::AllocSaveRecord() { return Mem_CallocAligned16(1, sizeof(SS08SaveRecord)); }

// 0x00268be0 CKGrpS08Enemy_vf16C
void CKGrpS08Enemy::SaveRecord(IKFile* file, void* unused, void* record) {
    IKGrpEnemy::SaveRecord(file, unused, record);  // 0x00266468
    SS08SaveRecord* r = static_cast<SS08SaveRecord*>(record);
    file->Write(&r->m_unk28, 4);
    file->Write(&r->m_unk30, 4);
    file->Write(&r->m_unk34, 4);
    file->Write(&r->m_unk2c, 4);
}

// 0x00268fe0 CKGrpS08Enemy_vf170
void CKGrpS08Enemy::LoadRecord(IKFile* file, void* unused, void* record) {
    IKGrpEnemy::LoadRecord(file, unused, record);  // 0x00266320
    SS08SaveRecord* r = static_cast<SS08SaveRecord*>(record);
    ReadF32LE(file, &r->m_unk28);
    ReadF32LE(file, &r->m_unk30);
    ReadF32LE(file, &r->m_unk34);
    ReadF32LE(file, &r->m_unk2c);
}
