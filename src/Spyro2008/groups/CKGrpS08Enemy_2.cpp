// CKGrpS08Enemy_2.cpp - reconstructed original translation unit 0x266d20-0x26a1b8 (GAME_TOC1, main_toc1), 58 functions, 48 live.
// Primary class: CKGrpS08Enemy  key 0xa44  category Group  size 0x290  vtable 0xb215f8
// Other owners: CKS08FightZoneCpnt (3)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x266d20  CKGrpS08Enemy_Delete
//   [ ] 0x266d70  CKGrpS08Enemy_vfF8
//   [ ] 0x266d88  CKGrpS08Enemy_vfFC
//   [ ] 0x266da0  CKGrpS08Enemy_vf100
//   [ ] 0x266db8  CKGrpS08Enemy_Pause
//   [ ] 0x266dc0  CKGrpS08Enemy_Resume
//   [ ] 0x266dc8  CKGrpS08Enemy_vfB8
//   [ ] 0x266dd0  CKGrpS08Enemy_vf150
//   [ ] 0x266dd8  CKGrpS08Enemy_vf178
//   [ ] 0x266e40  KStub_Nop_266e40  [dead]
//   [ ] 0x266e48  KStub_Nop_266e48  [dead]
//   [ ] 0x266e50  CKGrpS08Enemy_GetTriggerProp64_2  [dead]
//   [ ] 0x266e70  CKGrpS08Enemy_GetTriggerProp65_2  [dead]
//   [ ] 0x266e90  KStub_Return0_266e90  [dead]
//   [ ] 0x266e98  KStub_Nop_266e98  [dead]
//   [ ] 0x266ea0  CKGrpS08Enemy_CountGroundedWeapons_maybe
//   [ ] 0x266ff8  FUN_00266ff8  [dead]
//   [ ] 0x267090  CKGrpS08Enemy_SignalEnemyHit_maybe
//   [ ] 0x2670c8  CKGrpS08Enemy_ResetMembersAwarenessState_maybe  [dead]
//   [ ] 0x267138  CKGrpS08Enemy_ReleaseAttackSlot
//   [ ] 0x267220  CKGrpS08Enemy_vf164
//   [ ] 0x267260  CKGrpS08Enemy_ReserveAttackSlot_maybe
//   [ ] 0x267368  CKGrpS08Enemy_vf168
//   [ ] 0x267398  CKGrpS08Enemy_ResetAttackSlotState_maybe  [dead]
//   [ ] 0x267478  CKGrpS08Enemy_Stop
//   [ ] 0x2674d0  CKGrpS08Enemy_Save
//   [ ] 0x2674f8  CKGrpS08Enemy_RecursiveRegistration
//   [ ] 0x267568  CKGrpS08Enemy_Destroy
//   [x] 0x267590  CKGrpS08Enemy_DeleteArray
//   [x] 0x267630  CKGrpS08Enemy_Create
//   [ ] 0x2676e0  CKGrpS08Enemy_vf190
//   [ ] 0x267710  CKGrpS08Enemy_vf18C
//   [ ] 0x267740  CKGrpS08Enemy_vf188
//   [ ] 0x267770  CKGrpS08Enemy_vf184
//   [ ] 0x2677a0  RegisterCKGrpS08EnemyClass
//   [ ] 0x267828  _GLOBAL__D_267828
//   [ ] 0x267838  _GLOBAL__I_267838
//   [ ] 0x267848  CKGrpS08Enemy_CanReserveAttackSlot_maybe
//   [ ] 0x2678a8  CKS08FightZoneCpnt_FindFreeCristalOrb_maybe  [dead]
//   [ ] 0x267950  CKS08FightZoneCpnt_RemoveCristalOrb_maybe
//   [ ] 0x2679f0  CKS08FightZoneCpnt_CompleteObjective_maybe
//   [ ] 0x267a68  CKGrpS08Enemy_PostLoad
//   [ ] 0x267cb8  CKGrpS08Enemy_vf15C
//   [ ] 0x267d68  CKGrpS08Enemy_GetHeroMatrix
//   [ ] 0x267f10  CKGrpS08Enemy_GetInfo
//   [ ] 0x267ff8  CKGrpS08Enemy_MessageProc
//   [ ] 0x268178  CKGrpS08Enemy_SignalAlert_maybe
//   [ ] 0x2681d0  CKGrpS08Enemy_vf160
//   [ ] 0x2683a0  UpdateCKGrpS08Enemy
//   [x] 0x268600  CKGrpS08Enemy_CreateArray
//   [ ] 0x268738  CKGrpS08Enemy_MoveAttackerToBack_maybe
//   [ ] 0x268898  CKGrpS08Enemy_StartAttackCooldownAndRequeue_maybe
//   [ ] 0x268a60  CKGrpS08Enemy_ReleaseAttackSlotOfType_maybe
//   [ ] 0x268be0  CKGrpS08Enemy_vf16C
//   [ ] 0x268d28  CKGrpS08Enemy_Restart
//   [x] 0x268eb8  CKGrpS08Enemy_Start
//   [ ] 0x268fe0  CKGrpS08Enemy_vf170
//   [x] 0x269118  CKGrpS08Enemy_Load
//
//   [ ] 0x9bb468  CKGrpS08Enemy_IsKindOfClass  [inline]
//   [ ] 0x9bb4c8  CKGrpS08Enemy_GetClassType  [inline]
//   [ ] 0x9bb4d0  CKGrpS08Enemy_GetClassID  [inline]
//   [ ] 0x9bb4d8  CKGrpS08Enemy_vfCC  [inline]
//   [ ] 0x9bb4e0  CKGrpS08Enemy_vfF4  [inline]
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
//   [ ] 0x9bb608  CKGrpS08Enemy_vf158  [inline]
//   [ ] 0x9bb610  CKGrpS08Enemy_vf174  [inline]
//   [ ] 0x9bb618  CKGrpS08Enemy_GetTriggerProp67  [inline]
//   [ ] 0x9bb628  CKGrpS08Enemy_GetTriggerProp64  [inline]
//   [ ] 0x9bb648  CKGrpS08Enemy_vfEC  [inline]
//   [ ] 0x9bb668  CKGrpS08Enemy_vfF0  [inline]
//   [ ] 0x9bb688  CKGrpS08Enemy_GetTriggerProp65  [inline]
//   [ ] 0x9bb6a8  KStub_Return0_9bb6a8  [inline]
//   [ ] 0x9bb6b0  CKGrpS08Enemy_DeletingDestructor  [inline]
//   [ ] 0x9bb7f8  CKGrpS08Enemy_Destructor  [inline]
#include "Spyro2008/groups/CKGrpS08Enemy.h"

#include "Spyro2008/logic/CKS08AccessoryManager.h"
#include "k2000/components/CKCameraEventCpnt.h"
#include "k2000/groups/TVectorPush.h"
#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"

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
        m_vUnk19c.m_pBlock = static_cast<uint32_t*>(Mem_AllocAligned16(sizeof(uint32_t)));
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
// STUB(C2.2): the ResetTrack call (IKCamera has no such virtual yet; the camera family adds it).
void ScriptedCameraHandle_Reset(CKCameraEventCpnt* handle) {
    handle->m_unk0c = 0xbf800000u;                     // -1.0f (the word)
    handle->m_unk10 = handle->m_unk10 & 0x00ffffffu;  // the byte at +0x10 (bits 31..24 of the big-endian word)
}
}  // namespace

// 0x00268eb8 CKGrpS08Enemy_Start
void CKGrpS08Enemy::Start() {
    IKGrpEnemy::Start();  // 0x2659d8
    m_unk170[2] = 0;      // +0x178
    m_unk170[0] = 0;      // +0x170
    m_unk14c[2] = 0;      // +0x154
    m_unk14c[3] = 0;      // +0x158
    m_unk14c[4] = 0;      // +0x15c
    m_unk14c[5] = 0;      // +0x160
    if (m_vUnk164.m_pBlock == nullptr) {
        m_vUnk164.m_ui32NbElt = 1;
        m_vUnk164.m_pBlock = static_cast<uint32_t*>(Mem_AllocAligned16(4));
    }
    m_unk1dc = 0;
    m_unk1bc = 0;
    m_unk1d0[0] = 0;
    m_unk1d0[1] = 0;
    m_unk1d0[2] = 0;
    m_unk1e0 = 20.0f;  // TOC 0x518
    if (m_vUnk1b0.m_pBlock == nullptr) {
        m_vUnk1b0.m_ui32NbElt = 1;
        m_vUnk1b0.m_pBlock = static_cast<uint32_t*>(Mem_AllocAligned16(4));
    }
    m_unk1f0 = 0.3f;  // TOC 0x51c
    static_cast<CKS08AccessoryManager*>(m_pUnk1ec)->ResetRuntime();  // vt+0x50 0x2c7b80
    ScriptedCameraHandle_Reset(static_cast<CKCameraEventCpnt*>(m_pUnk264));
    m_unk14c[1] = 0;  // +0x150
    m_unk14c[0] = 0;  // +0x14c
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
