// CKHkGolem.cpp - reconstructed original translation unit 0x4bed00-0x4c4a00 (GAME_TOC1, main_toc1), 45 functions, 42 live.
// Primary class: CKHkGolem  key 0x3182  category Hook  size 0xc0  vtable 0xb29260
// Other owners: GolemAttack (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x4bed00  CKHkGolem_GetHealthPercent_maybe
//   [ ] 0x4bed50  CKHkGolem_SetByte45_maybe
//   [ ] 0x4bed58  CKHkGolem_SpawnBonuses_maybe
//   [ ] 0x4beda0  CKHkGolem_CreatePhaseCondition
//   [ ] 0x4befc0  CKHkGolem_UpdateProjectileLaunchers_maybe
//   [ ] 0x4bf248  CKHkGolem_Resume
//   [ ] 0x4bf270  CKHkGolem_Pause
//   [ ] 0x4bf298  CKHkGolem_Stop
//   [x] 0x4bf308  CKHkGolem_PostLoad
//   [ ] 0x4bf348  CKHkGolem_MessageProc
//   [ ] 0x4bf5d0  CKHkGolem_Save
//   [ ] 0x4bf5f8  CKHkGolem_RecursiveRegistration
//   [ ] 0x4bf620  CKHkGolem_Construct_2  [dead]
//   [x] 0x4bf6b8  CKHkGolem_Construct
//   [ ] 0x4bf750  CKHkGolem_DeleteArray
//   [ ] 0x4bf7f8  RegisterCKHkGolemClass
//   [ ] 0x4bf880  _GLOBAL__D_4bf880
//   [ ] 0x4bf890  _GLOBAL__I_4bf890
//   [ ] 0x4bf8a0  CKHkGolem_AddObjectToList2C_maybe
//   [x] 0x4bf970  CKHkGolem_Start
//   [ ] 0x4bf9f8  CKHkGolem_SetTime54ToNow_maybe
//   [ ] 0x4bfa18  CKHkGolem_Restart
//   [ ] 0x4bfb88  CKHkGolem_ReleaseAllEntryObjects_maybe
//   [ ] 0x4bfc88  CKHkGolem_OnDeactivate
//   [ ] 0x4bfdf0  CKHkGolem_SetActiveWithBossGauge_maybe
//   [ ] 0x4c00c8  CKHkGolem_OnActivate
//   [ ] 0x4c0388  CKHkGolem_Destroy
//   [ ] 0x4c0678  CKHkGolem_GetInfo
//   [ ] 0x4c07c0  CKHkGolem_RemoveObjectFromList2C_maybe
//   [ ] 0x4c0850  CKHkGolem_Destructor
//   [ ] 0x4c09b0  CKHkGolem_BaseDestructor
//   [ ] 0x4c0b10  CKHkGolem_DeletingDestructor
//   [ ] 0x4c0c80  CKHkGolem_GetHealthPercentInt_maybe
//   [x] 0x4c0ce0  CKHkGolem_Create
//   [ ] 0x4c0d88  CKHkGolem_SaveRefArray_maybe  [dead]
//   [ ] 0x4c0ec8  CKHkGolem_CreateArray
//   [x] 0x4c0ff0  CKHkGolem_LoadRefArray34_maybe
//   [x] 0x4c11c0  CKHkGolem_Load
//   [ ] 0x4c2288  GolemAttack_TriggerStepExplosions_maybe
//   [ ] 0x4c2758  CKHkGolem_SpawnFxAt_maybe
//   [ ] 0x4c29f8  CKHkGolem_AcquireIndexedFxNodes_maybe  [dead]
//   [ ] 0x4c2dc8  CKHkGolem_SpawnContactParticleFx_maybe
//   [ ] 0x4c31c0  CKHkGolem_ProcessContacts_maybe
//   [ ] 0x4c3998  CKHkGolem_UpdateAnimMarkEvents_maybe
//   [ ] 0x4c4838  CKHkGolem_Update
//
//   [ ] 0x9c56e8  CKHkGolem_IsKindOfClass  [inline]
//   [ ] 0x9c5740  CKHkGolem_GetClassType  [inline]
//   [ ] 0x9c5748  CKHkGolem_GetClassID  [inline]
//   [ ] 0x9c5750  CKHkGolem_GetTriggerProp2  [inline]
//   [ ] 0x9c5760  CKHkGolem_vf100  [inline]
//   [ ] 0x9c5768  CKHkGolem_vf104  [inline]
//   [ ] 0x9c5770  CKHkGolem_vf108  [inline]
//   [ ] 0x9c5778  KStub_Nop_9c5778  [inline]
//   [ ] 0x9c5780  KStub_Nop_9c5780  [inline]
//   [ ] 0x9c5788  CKHkGolem_vfFC_GetCount_maybe  [inline]
//   [ ] 0x9c5790  CKHkGolem_vfF8_GetAt_maybe  [inline]
#include "k2000/hooks/CKHkGolem.h"

#include <new>

#include "Renderware/rwcore/RwMatrix.h"
#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/Engine.h"
#include "k2000/system/CTimeManager.h"
#include "k2000/system/IKTime.h"

// 0x004bf6b8 CKHkGolem_Construct (the same body inlined in CKHkGolem_Create 0x4c0ce0): the four vectors
// empty with capacity 1.
CKHkGolem::CKHkGolem() {
    m_unk2C = 0;
    m_unk20 = 0;
    m_unk34.m_ui32NbElt = 1;
    m_unk34.m_pBlock = nullptr;
    m_unk34.m_ui32NbUsedElt = 0;
    m_unk58.m_ui32NbElt = 1;
    m_unk58.m_pBlock = nullptr;
    m_unk58.m_ui32NbUsedElt = 0;
    m_unk64.m_ui32NbElt = 1;
    m_unk64.m_pBlock = nullptr;
    m_unk64.m_ui32NbUsedElt = 0;
    m_unk70.m_ui32NbElt = 1;
    m_unk70.m_ui32NbUsedElt = 0;
    m_unk70.m_pBlock = nullptr;
}

namespace {
// The inlined TVector start: capacity 1 and a fresh one-element block (the old block is not freed).
template <class T>
void StartVector(TVector<T, 1>& vector) {
    vector.m_ui32NbElt = 1;
    vector.m_pBlock = static_cast<T*>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(T))));
}

// The inlined TVector push (growth step 1).
template <class T>
void Push(TVector<T, 1>& vector, T element) {
    if (vector.m_ui32NbElt == vector.m_ui32NbUsedElt) {
        uint32_t capacity = vector.m_ui32NbUsedElt + 1;
        if (capacity == 0) capacity = 1;
        vector.m_pBlock = static_cast<T*>(
            Mem_ReallocAligned16(vector.m_pBlock, capacity * static_cast<uint32_t>(sizeof(T))));
        vector.m_ui32NbElt = capacity;
    }
    vector.m_pBlock[vector.m_ui32NbUsedElt] = element;
    vector.m_ui32NbUsedElt++;
}

// A record's common head: the word, then the reference.
template <class Record>
void ReadRecordHead(IKFile* file, Record* record) {
    ReadU32LE(file, &record->m_ui32Value);
    IKFile_ReadRef(file, &record->m_pObject);
}
}  // namespace

// 0x004c0ff0 CKHkGolem_LoadRefArray34_maybe: a count, then that many references pushed one by one (read into
// a local first). The type argument (always 0) is not used.
void CKHkGolem::LoadObjectVector(IKFile* file, int32_t /*type*/) {
    uint32_t count = 0;
    ReadU32LE(file, &count);
    StartVector(m_unk34);
    for (uint32_t i = 0; i < count; ++i) {
        IKSerializable* object = nullptr;
        IKFile_ReadRef(file, &object);
        Push(m_unk34, object);
    }
}

// 0x004c11c0 CKHkGolem_Load
int32_t CKHkGolem::Load(IKFile* file, int32_t type) {
    CKHkActorBase::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    IKFile_ReadRef(file, &m_unk30);
    LoadObjectVector(file, K_LEVEL_PLATEFORMS);

    uint32_t count = 0;
    ReadU32LE(file, &count);
    StartVector(m_unk58);
    for (uint32_t i = 0; i < count; ++i) {
        CKHkGolemNode18* node = static_cast<CKHkGolemNode18*>(::operator new(sizeof(CKHkGolemNode18)));
        node->m_records.m_pBlock = nullptr;
        node->m_records.m_ui32NbUsedElt = 0;
        node->m_records.m_ui32NbElt = 1;
        IKFile_ReadRef(file, &node->m_pObject);
        IKFile_ReadRef(file, &node->m_pObject14);
        ReadU8(file, &node->m_unk10);
        uint32_t records = 0;
        ReadU32LE(file, &records);
        StartVector(node->m_records);
        for (uint32_t j = 0; j < records; ++j) {
            CKHkGolemRecord8* record = static_cast<CKHkGolemRecord8*>(::operator new(sizeof(CKHkGolemRecord8)));
            record->m_pObject = nullptr;
            record->m_ui32Value = 0;
            ReadRecordHead(file, record);
            Push(node->m_records, record);
        }
        Push(m_unk58, node);
    }

    ReadU32LE(file, &count);
    StartVector(m_unk64);
    for (uint32_t i = 0; i < count; ++i) {
        auto* node = static_cast<CKHkGolemNode10<CKHkGolemRecordC>*>(
            ::operator new(sizeof(CKHkGolemNode10<CKHkGolemRecordC>)));
        node->m_records.m_pBlock = nullptr;
        node->m_records.m_ui32NbUsedElt = 0;
        node->m_records.m_ui32NbElt = 1;
        IKFile_ReadRef(file, &node->m_pObject);
        uint32_t records = 0;
        ReadU32LE(file, &records);
        StartVector(node->m_records);
        for (uint32_t j = 0; j < records; ++j) {
            CKHkGolemRecordC* record = static_cast<CKHkGolemRecordC*>(::operator new(sizeof(CKHkGolemRecordC)));
            record->m_pObject = nullptr;
            record->m_ui32Value = 0;
            record->m_unk8 = 0;
            ReadRecordHead(file, record);
            record->m_unk8 = 0;
            Push(node->m_records, record);
        }
        Push(m_unk64, node);
    }

    ReadU32LE(file, &count);
    StartVector(m_unk70);
    for (uint32_t i = 0; i < count; ++i) {
        auto* node = static_cast<CKHkGolemNode10<CKHkGolemRecord20>*>(
            ::operator new(sizeof(CKHkGolemNode10<CKHkGolemRecord20>)));
        node->m_records.m_pBlock = nullptr;
        node->m_records.m_ui32NbUsedElt = 0;
        node->m_records.m_ui32NbElt = 1;
        IKFile_ReadRef(file, &node->m_pObject);
        uint32_t records = 0;
        ReadU32LE(file, &records);
        StartVector(node->m_records);
        for (uint32_t j = 0; j < records; ++j) {
            CKHkGolemRecord20* record = static_cast<CKHkGolemRecord20*>(::operator new(sizeof(CKHkGolemRecord20)));
            record->m_pObject = nullptr;
            record->m_ui32Value = 0;
            for (uint32_t& word : record->m_unk8) word = 0;
            for (uint32_t& word : record->m_unk14) word = 0;
            ReadRecordHead(file, record);
            ReadU32LE(file, &record->m_unk8[0]);
            ReadU32LE(file, &record->m_unk8[1]);
            ReadU32LE(file, &record->m_unk8[2]);
            Push(node->m_records, record);
        }
        Push(m_unk70, node);
    }

    IKFile_ReadRef(file, &m_unk7C);
    IKFile_ReadRef(file, &m_unk80);
    ReadU32LE(file, &m_unk88);
    IKFile_ReadRef(file, &m_unk28);
    IKFile_ReadRef(file, &m_unk24);
    ReadU8(file, &m_unk90);
    IKFile_ReadRef(file, &m_unkBC);
    for (float& value : m_af94) ReadF32LE(file, &value);
    return 1;
}

// 0x004bf308 CKHkGolem_PostLoad (CKHkS08DragonCityGolem_PostLoad 0x4d5c10 is this one with no addition): the
// actor base's, then a new matrix at +0x84 whatever the type.
int32_t CKHkGolem::PostLoad(int32_t type) {
    CKHkActorBase::PostLoad(type);
    m_pUnk84 = reinterpret_cast<CMatrix34*>(RwMatrixCreate());  // RwMatrixCreate_Thunk 0x23fa68
    return 1;
}

// 0x004bf970 CKHkGolem_Start: the run-time state cleared and the two time stamps set to the clock's game time
// (the frame clock's accumulated scalable time, IKTime +0x04). KStub_Nop_5cebf0(+0xbc, this) is empty.
void CKHkGolem::Start() {
    CKHkActorBase::Start();
    const float now = g_pEngine->m_timeManager->m_pTime->m_afCurrentTime[IKTime::SCALABLE_GAME_TIME];
    m_unk48 = 0;
    m_unk40 = 0;
    m_unk44 = 0;
    m_fUnk54 = now;
    m_fUnk50 = now;
    m_unk45 = 1;
}
