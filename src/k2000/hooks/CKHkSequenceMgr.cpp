// CKHkSequenceMgr.cpp - reconstructed original translation unit 0x460790-0x46b0c8 (GAME_TOC1, main_toc1), 88 functions, 55 live.
// Primary class: CKHkSequenceMgr  key 0x18c2  category Hook  size 0x140  vtable 0xb27310
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x460790  CKHkSequenceMgr_Delete
//   [ ] 0x4607e0  CKHkSequenceMgr_ResetRuntimeState_maybe  [dead]
//   [ ] 0x4608b0  CKHkSequenceMgr_IsWrongActionPressed_maybe  [dead]
//   [ ] 0x460b28  CKHkSequenceMgr_ReleaseIconSet_maybe
//   [ ] 0x460c90  CKHkSequenceMgr_SendMsg407ToOwner_maybe  [dead]
//   [ ] 0x460d00  KStub_Return1_460d00  [dead]
//   [ ] 0x460d08  KStub_Return1_460d08  [dead]
//   [ ] 0x460d10  FUN_00460d10  [dead]
//   [ ] 0x460d40  KStub_Nop_460d40  [dead]
//   [ ] 0x460d48  KStub_Return1_460d48  [dead]
//   [ ] 0x460d50  FUN_00460d50  [dead]
//   [ ] 0x460d98  KStub_Nop_460d98  [dead]
//   [ ] 0x460da0  KStub_Return1_460da0  [dead]
//   [ ] 0x460da8  FUN_00460da8  [dead]
//   [ ] 0x460dd0  KStub_Return1_460dd0  [dead]
//   [ ] 0x460dd8  FUN_00460dd8  [dead]
//   [ ] 0x460df8  KStub_Nop_460df8  [dead]
//   [ ] 0x460e00  CKHkSequenceMgr_SetIconSetsFlag80000_maybe  [dead]
//   [ ] 0x460ee8  FUN_00460ee8  [dead]
//   [ ] 0x460f18  FUN_00460f18  [dead]
//   [ ] 0x460fc8  RegisterCKHkSequenceMgrClass
//   [ ] 0x461040  _GLOBAL__I_461040
//   [ ] 0x461050  CKHkSequenceMgr_IsStepForPlayer_maybe
//   [ ] 0x461178  CKHkSequenceMgr_CheckStepWindow_maybe
//   [ ] 0x461408  CKHkSequenceMgr_RefreshIconsForPlayerCount_maybe
//   [ ] 0x461498  CKHkSequenceMgr_SequenceEntry_Assign_maybe  [dead]
//   [ ] 0x461658  CKHkSequenceMgr_UpdateCameraFromHotSpots_maybe
//   [ ] 0x461860  CKHkSequenceMgr_UpdateStepAnimation_maybe
//   [ ] 0x461960  CKHkSequenceMgr_AdvanceAttachedHeroesAnim_maybe
//   [ ] 0x461af0  CKHkSequenceMgr_NotifyStepObjectsHookA_maybe  [dead]
//   [ ] 0x461c58  CKHkSequenceMgr_NotifyStepObjectsHookB_maybe  [dead]
//   [ ] 0x461dc0  CKHkSequenceMgr_UpdateMarkedTriggers_maybe  [dead]
//   [ ] 0x461e68  CKHkSequenceMgr_UpdateStepMarkedFx_maybe  [dead]
//   [ ] 0x461fc8  CKHkSequenceMgr_FireStepTriggersInWindow_maybe
//   [ ] 0x462078  CKHkSequenceMgr_UpdateSoundTriggers_maybe
//   [x] 0x4621e0  CKHkSequenceMgr_DetachHeroes_maybe
//   [ ] 0x462300  CKHkSequenceMgr_FollowAttachedObject_maybe
//   [ ] 0x4623d0  CKHkSequenceMgr_ProbeGroundPoints_maybe  [dead]
//   [ ] 0x4624f8  CKHkSequenceMgr_Pause
//   [ ] 0x462520  CKHkSequenceMgr_Stop
//   [ ] 0x462548  CKHkSequenceMgr_PostLoad
//   [ ] 0x4625b0  CKHkSequenceMgr_Save
//   [ ] 0x4625d8  CKHkSequenceMgr_RecursiveRegistration
//   [x] 0x462600  CKHkSequenceMgr_Construct  [dead]
//   [x] 0x462680  CKHkSequenceMgr_DeleteArray
//   [ ] 0x462728  CKHkSequenceMgr_Destroy
//   [ ] 0x462848  CKHkSequenceMgr_Resume
//   [ ] 0x4628b0  CKHkSequenceMgr_Construct_2  [dead]
//   [ ] 0x462930  CKHkSequenceMgr_GetInfo
//   [ ] 0x462a60  CKHkSequenceMgr_ComputeStepWindowTimes_maybe  [dead]
//   [ ] 0x462ca8  CKHkSequenceMgr_SetEntryFlag2ById_maybe  [dead]
//   [ ] 0x462d30  FUN_00462d30  [dead]
//   [ ] 0x462d48  CKHkSequenceMgr_AdvanceStepObjectsAnim_maybe
//   [x] 0x462f60  CKHkSequenceMgr_InitSequenceEntry_maybe
//   [ ] 0x463100  CKHkSequenceMgr_Destructor
//   [ ] 0x4631c8  CKHkSequenceMgr_BaseDestructor
//   [ ] 0x463290  CKHkSequenceMgr_DeletingDestructor
//   [ ] 0x463360  CKHkSequenceMgr_AcquireOrReleaseCamera_maybe  [dead]
//   [x] 0x4634f0  CKHkSequenceMgr_CreateArray
//   [x] 0x463600  CKHkSequenceMgr_Create
//   [ ] 0x463690  CKHkSequenceMgr_StopCurrentSequence_maybe
//   [ ] 0x463ef8  CKHkSequenceMgr_AbortForOwner_maybe
//   [ ] 0x463f90  CKHkSequenceMgr_OnDeactivate
//   [ ] 0x4640f0  CKHkSequenceMgr_AdvanceStepAnim_maybe
//   [ ] 0x464268  CKHkSequenceMgr_FreeBuffers_maybe
//   [ ] 0x4643a0  FUN_004643a0  [dead]
//   [ ] 0x4644a8  CKHkSequenceMgr_BeginEntryAnimAndCamera_maybe
//   [ ] 0x464858  CKHkSequenceMgr_AttachActorToHotSpot_maybe
//   [ ] 0x464b38  CKHkSequenceMgr_SetupHeroesForSequence_maybe
//   [ ] 0x464f78  CKHkSequenceMgr_StartActorAnims_maybe
//   [ ] 0x465348  CKHkSequenceMgr_StartSequence_maybe
//   [ ] 0x465670  CKHkSequenceMgr_PlayNextSequence_maybe
//   [ ] 0x4657c0  CKHkSequenceMgr_StartSequenceWithListener_maybe
//   [ ] 0x465828  CKHkSequenceMgr_StartSequenceIfIdle_maybe  [dead]
//   [ ] 0x465898  CKHkSequenceMgr_MessageProc
//   [x] 0x465ad0  CKHkSequenceMgr_LoadStepParamsRecord_maybe
//   [x] 0x465da0  CKHkSequenceMgr_Start
//   [ ] 0x465f18  CKHkSequenceMgr_OnActivate_maybe
//   [ ] 0x4661d0  CKHkSequenceMgr_Restart
//   [ ] 0x466418  CKHkSequenceMgr_LoadSize0x18Record_maybe  [dead]
//   [x] 0x4665b8  CKHkSequenceMgr_LoadObjectRefRecord_maybe
//   [x] 0x4667a0  CKHkSequenceMgr_LoadSequenceEntry_maybe
//   [x] 0x466e38  CKHkSequenceMgr_Load
//   [ ] 0x467bc8  CKHkSequenceMgr_OnWrongInput_maybe
//   [ ] 0x468530  CKHkSequenceMgr_UpdateButtonIcons_maybe
//   [ ] 0x468f10  CKHkSequenceMgr_OnCorrectInput_maybe
//   [ ] 0x469960  CKHkSequenceMgr_UpdateStep_maybe
//   [ ] 0x46a6c8  CKHkSequenceMgr_Update
//
//   [ ] 0x9c40d8  CKHkSequenceMgr_IsKindOfClass  [inline]
//   [ ] 0x9c4130  CKHkSequenceMgr_GetClassType  [inline]
//   [ ] 0x9c4138  CKHkSequenceMgr_GetClassID  [inline]
//   [ ] 0x9c4140  CKHkSequenceMgr_GetResult  [inline]
//   [ ] 0x9c4150  CKHkSequenceMgr_GetTriggerProp15E_maybe  [inline]
#include "k2000/hooks/CKHkSequenceMgr.h"

#include <cstring>

#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"
#include "k2000/core/Stub.h"
#include "Spyro2008/groups/CKGrpS08Hero.h"
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "k2000/misc/Engine.h"
#include "k2000/logic/CDefaultGameManager.h"

namespace {

// The TVector push every loop of these Loads inlines: grow to used + 1 when full (Grow 1).
template <class T>
T* PushBack(TVector<T, 1>& v) {
    const uint32_t used = v.m_ui32NbUsedElt;
    if (v.m_ui32NbElt == used) {
        uint32_t capacity = used + 1;
        if (capacity == 0) capacity = 1;
        v.m_pBlock = static_cast<T*>(Mem_ReallocAligned16(v.m_pBlock, capacity * static_cast<uint32_t>(sizeof(T))));
        v.m_ui32NbElt = capacity;
    }
    v.m_ui32NbUsedElt = used + 1;
    return &v.m_pBlock[used];
}

// The TOC float at +0x56fc (0x00c1b0d4): 1.0f.
const float kOne = 1.0f;

}  // namespace

// 0x004665b8 CKHkSequenceMgr_LoadObjectRefRecord_maybe
int32_t CKHkSequenceMgr::ObjectRefRecord::Load(IKFile* file, int32_t type) {
    if (type == K_LEVEL_PLATEFORMS) {
        IKFile_ReadRef(file, &m_pRef);
        ReadU32LE(file, &m_unk8);
        ReadU8(file, &m_unkC);
        ReadU32LE(file, &m_unk10);
        ReadU32LE(file, &m_unk14);
        ReadU8(file, &m_unk0);
    }
    return 1;
}

// 0x00465ad0 CKHkSequenceMgr_LoadStepParamsRecord_maybe
int32_t CKHkSequenceMgr::StepParams::Load(IKFile* file, int32_t type) {
    if (type == K_LEVEL_PLATEFORMS) {
        ReadU8(file, &m_unk0);
        ReadU32LE(file, &m_unk4);
        ReadU32LE(file, &m_unk8);
        ReadU32LE(file, &m_unkC);
        ReadU32LE(file, &m_unk10);
        ReadU32LE(file, &m_unk18);
        ReadU8(file, &m_unk14);
        ReadU8(file, &m_unk1c);
        ReadU32LE(file, &m_unk20);
        ReadF32LE(file, &m_unk24);
    }
    return 1;
}

// 0x00462f60 CKHkSequenceMgr_InitSequenceEntry_maybe (stores in the original's order)
void CKHkSequenceMgr::SequenceEntry::Init(CKHkSequenceMgr* owner) {
    m_unk0 = 1.0f;
    m_unk4 = 1.0f;
    m_recB.m_unk0 = 1;
    m_recA.m_unk0 = 1;
    m_recC.m_unk0 = 1;
    m_recA.m_unk14 = 0xffffffffu;
    m_recA.m_pRef = nullptr;
    m_recA.m_unk8 = 0;
    m_recA.m_unkC = 0;
    m_recA.m_unk10 = 0;
    m_recC.m_unk14 = 0xffffffffu;
    m_recC.m_pRef = nullptr;
    m_recC.m_unk8 = 0;
    m_recC.m_unkC = 0;
    m_recC.m_unk10 = 0;
    m_recB.m_unk14 = 0xffffffffu;
    m_recB.m_pRef = nullptr;
    m_recB.m_unk8 = 0;
    m_recB.m_unkC = 0;
    m_recB.m_unk10 = 0;
    m_pvRecords = static_cast<TVector<ObjectRefRecord, 1>*>(
        Mem_CallocAligned16(1, static_cast<uint32_t>(sizeof(TVector<ObjectRefRecord, 1>))));
    m_pvItems = static_cast<TVector<EntryItem, 1>*>(
        Mem_CallocAligned16(1, static_cast<uint32_t>(sizeof(TVector<EntryItem, 1>))));
    m_pvRecords->m_ui32NbElt = 1;
    m_pvRecords->m_pBlock = static_cast<ObjectRefRecord*>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(ObjectRefRecord))));
    m_pvItems->m_ui32NbElt = 1;
    m_pvItems->m_pBlock = static_cast<EntryItem*>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(EntryItem))));
    m_unk64 = 0xffffffffu;
    m_unk68 = 0xffffffffu;
    m_stepParams.m_unk18 = 0xffffffffu;
    m_stepParams.m_unk10 = 1;
    m_stepParams.m_unk0 = 0;
    m_stepParams.m_unk4 = 0;
    m_stepParams.m_unk8 = 0;
    m_stepParams.m_unkC = 0;
    m_stepParams.m_unk14 = 0;
    m_stepParams.m_unk24 = 1.0f;
    m_stepParams.m_unk1c = 0;
    m_stepParams.m_unk20 = 0;
    m_unkA0 = 1.0f;
    m_unk9c = 0;
    m_unk98 = 0;
    m_pOwner = owner;
    m_unkB0 = 0;
    m_unkB1 = 2;
    m_unkA8 = 0;
}

// 0x004667a0 CKHkSequenceMgr_LoadSequenceEntry_maybe
int32_t CKHkSequenceMgr::SequenceEntry::Load(IKFile* file, int32_t type) {
    if (type == K_LEVEL_PLATEFORMS) {
        ReadF32LE(file, &m_unk0);
        ReadF32LE(file, &m_unk4);
        m_recA.Load(file, K_LEVEL_PLATEFORMS);
        m_recC.Load(file, K_LEVEL_PLATEFORMS);
        m_recB.Load(file, K_LEVEL_PLATEFORMS);
        uint32_t count = 0;
        ReadU32LE(file, &count);
        if (m_pvRecords->m_pBlock == nullptr) {
            m_pvRecords->m_ui32NbElt = 1;
            m_pvRecords->m_pBlock =
                static_cast<ObjectRefRecord*>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(ObjectRefRecord))));
        }
        for (uint32_t i = 0; i < count; ++i) {
            ObjectRefRecord* record = PushBack(*m_pvRecords);
            record->m_unk0 = 1;
            record->m_pRef = nullptr;
            record->m_unk8 = 0;
            record->m_unkC = 0;
            record->m_unk10 = 0;
            record->m_unk14 = 0xffffffffu;
            record->Load(file, K_LEVEL_PLATEFORMS);
        }
        ReadU32LE(file, &count);
        if (m_pvItems->m_pBlock == nullptr) {
            m_pvItems->m_ui32NbElt = 1;
            m_pvItems->m_pBlock = static_cast<EntryItem*>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(EntryItem))));
        }
        for (uint32_t i = 0; i < count; ++i) {
            EntryItem* item = PushBack(*m_pvItems);
            item->m_unk4 = 0;
            item->m_unk8 = 0;
            std::memcpy(&item->m_unkC, &kOne, 4);
            item->m_unk14 = 0;
            IKFile_ReadRef(file, &item->m_pRef);
            ReadU8(file, &item->m_unk4);
            ReadU32LE(file, &item->m_unk8);
            ReadU32LE(file, &item->m_unkC);
            ReadU32LE(file, &item->m_unk14);
        }
        ReadU32LE(file, &m_unk64);
        ReadU32LE(file, &m_unk68);
        m_stepParams.Load(file, K_LEVEL_PLATEFORMS);
        ReadU8(file, &m_unk98);
        ReadU32LE(file, &m_unk9c);
        ReadF32LE(file, &m_unkA0);
        ReadU32LE(file, &m_unkA8);
        ReadU8(file, &m_unkB1);
    }
    return 1;
}

// 0x00466e38 CKHkSequenceMgr_Load
int32_t CKHkSequenceMgr::Load(IKFile* file, int32_t type) {
    CKHkActorBase::Load(file, type);
    m_unk8c = 1.0f;
    m_unk94 = 1.0e-1f;
    m_unk88 = 1.0f;
    m_unk90 = 1.0e-1f;
    m_unk98[0] = 0.5f;
    m_unk98[1] = 2.0e-1f;
    m_unk98[2] = 0.0f;
    if (m_vEntries.m_pBlock == nullptr) {
        m_vEntries.m_ui32NbElt = 1;
        m_vEntries.m_pBlock = static_cast<SequenceEntry*>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(SequenceEntry))));
    }
    if (m_vItems.m_pBlock == nullptr) {
        m_vItems.m_ui32NbElt = 1;
        m_vItems.m_pBlock = static_cast<MgrItem*>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(MgrItem))));
    }
    if (type != K_LEVEL_PLATEFORMS) return 1;
    uint32_t count = 0;
    ReadU32LE(file, &count);
    for (uint32_t i = 0; i < count; ++i) {
        SequenceEntry* entry = PushBack(m_vEntries);
        entry->Init(this);
        entry->Load(file, K_LEVEL_PLATEFORMS);
    }
    ReadU32LE(file, &count);
    for (uint32_t i = 0; i < count; ++i) {
        MgrItem* item = PushBack(m_vItems);
        ReadU8(file, &item->m_unk4);
        IKFile_ReadRef(file, &item->m_pRef);
        ReadU32LE(file, &item->m_unk8);
    }
    IKFile_ReadRef(file, &m_unk4c);
    IKFile_ReadObjectRefArray(file, m_apUnkC0, 5);
    m_unk50.Load(file, K_LEVEL_PLATEFORMS);
    m_unk60.Load(file, K_LEVEL_PLATEFORMS);
    m_unk68.Load(file, K_LEVEL_PLATEFORMS);
    m_unk70.Load(file, K_LEVEL_PLATEFORMS);
    m_unk80.Load(file, K_LEVEL_PLATEFORMS);
    m_unk58.Load(file, K_LEVEL_PLATEFORMS);
    m_unk78.Load(file, K_LEVEL_PLATEFORMS);
    IKFile_ReadRef(file, &m_unkA4);
    IKFile_ReadRef(file, &m_unkB0);
    IKFile_ReadRef(file, &m_unkB4);
    ReadF32LE(file, &m_unk88);
    ReadF32LE(file, &m_unk8c);
    ReadF32LE(file, &m_unk90);
    ReadF32LE(file, &m_unk94);
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(m_unk98), 3);
    IKFile_ReadRef(file, &m_unk20);
    // One group per sequence entry: two references, then one reference per +0x30 item.
    m_vGroups.m_ui32NbElt = 1;
    m_vGroups.m_pBlock = static_cast<RefGroup**>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(RefGroup*))));
    for (uint32_t i = 0; i < m_vEntries.m_ui32NbUsedElt; ++i) {
        RefGroup* group = new RefGroup;
        group->m_vRefs.m_pBlock = nullptr;
        group->m_vRefs.m_ui32NbUsedElt = 0;
        group->m_vRefs.m_ui32NbElt = 1;
        group->m_vRefs.m_pBlock =
            static_cast<IKSerializable**>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(IKSerializable*))));
        IKFile_ReadRef(file, &group->m_pRef4);
        IKFile_ReadRef(file, &group->m_pRef0);
        for (uint32_t j = 0; j < m_vItems.m_ui32NbUsedElt; ++j) {
            IKSerializable* ref = nullptr;
            IKFile_ReadRef(file, &ref);
            *PushBack(group->m_vRefs) = ref;
        }
        *PushBack(m_vGroups) = group;
    }
    RefGroup* group = new RefGroup;
    group->m_vRefs.m_pBlock = nullptr;
    group->m_vRefs.m_ui32NbElt = 1;
    group->m_vRefs.m_ui32NbUsedElt = 0;
    m_pGroup48 = group;
    IKFile_ReadRef(file, &group->m_pRef4);
    IKFile_ReadRef(file, &m_pGroup48->m_pRef0);
    group = m_pGroup48;
    group->m_vRefs.m_ui32NbElt = 1;
    group->m_vRefs.m_pBlock =
        static_cast<IKSerializable**>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(IKSerializable*))));
    for (uint32_t j = 0; j < m_vItems.m_ui32NbUsedElt; ++j) {
        IKSerializable* ref = nullptr;
        IKFile_ReadRef(file, &ref);
        *PushBack(m_pGroup48->m_vRefs) = ref;
    }
    IKFile_ReadRef(file, &m_unkA8);
    IKFile_ReadRef(file, &m_unkAC);
    return 1;
}

// 0x004621e0 CKHkSequenceMgr_DetachHeroes_maybe: every hero attached to this manager (+0x90) is released: +0x530 /
// +0x534 to 0 (TOC1 +0x572c) when its attached movement is on, detached, vulnerable again, and the game manager's
// input unblocked (vt+0x1e8 with 0).
void CKHkSequenceMgr::DetachHeroes() {
    CDefaultGameManager* manager = g_pEngine->m_gameManager;
    CKGrpS08Hero* group = static_cast<CKGrpS08Hero*>(manager->m_unk04[1]);  // +0x08
    if (group == nullptr) return;
    for (int32_t i = static_cast<int32_t>(group->GetHeroCount()) - 1; i != -1; --i) {  // 0x002ca038
        CKHkS08Hero* hero = static_cast<CKHkS08Hero*>(group->m_apHeros[static_cast<uint8_t>(i)]);  // 0x002ca080
        if (hero->GetAttachedObject() != this) continue;  // 0x00361d50
        hero->SetUnk530IfAttachedMovement(0.0f);  // 0x003626a0
        hero->SetUnk534IfAttachedMovement(0.0f);  // 0x00362688
        hero->DetachFromObject();                 // 0x00364608
        hero->SetInvulnerable(0);                 // 0x00361b20
        g_pEngine->m_gameManager->SetInputBlocked(0);  // vt+0x1e8
    }
}

// 0x00465da0 CKHkSequenceMgr_Start. Unless the manager is flagged (bit 2): a sequence still running (index in
// range) is stopped and the heroes it holds are released, the run-time words are cleared (every item's three
// words, and its reference when the item's byte is set), then the pending words. BUG(original): +0xe8 is read
// before anything wrote it on the first start.
// STUB(C2.8: sequences): CKHkSequenceMgr_StopCurrentSequence_maybe (0x463690: the running sequence's sounds, its
// items' attached nodes, the heroes' scene flag bit 2 and their attachment to this manager (as DetachHeroes), the
// camera's list +0xe14, marked effects, icon sets) only runs with a sequence running (never on a fresh level).
void CKHkSequenceMgr::Start() {
    CKHkActorBase::Start();
    m_unk131 = 1;
    m_unk134 = 0;
    if ((m_bitArray & 4) == 0) {
        if (m_unkE8 >= 0 && static_cast<uint32_t>(m_unkE8) < m_vEntries.m_ui32NbUsedElt) {
            DOTD_STUB_ONCE("CKHkSequenceMgr_StopCurrentSequence_maybe 0x463690 (C2.8)");
        }
        DetachHeroes();  // 0x004621e0
        m_unkE8 = -1;
        m_unkE1 = 0;
        m_unkD8 = 0;
        m_unkDC = 0;
        m_unkF4 = 0;
        m_unkF8 = 0;
        m_unk138 = 0;
        m_unk118 = 0;
        m_unkE0 = 0;
        m_unkF0 = 0;
        for (uint32_t i = m_vItems.m_ui32NbUsedElt; i != 0; --i) {
            MgrItem& item = m_vItems.m_pBlock[i - 1];
            item.m_unkC[1] = 0;  // +0x10
            item.m_unkC[2] = 0;  // +0x14
            item.m_unkC[0] = 0;  // +0x0c
            if (item.m_unk4 != 0) item.m_pRef = nullptr;
        }
        m_unkD4 &= 0xf0;
    }
    m_unkDC = 0;
    m_unkB8[0] = 0;
    m_unkB8[1] = 0;
    m_unkD8 = 0;
}
