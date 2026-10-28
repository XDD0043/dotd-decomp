// CKSrvTrigger.cpp - reconstructed original translation unit 0x235188-0x2361c0 (GAME_TOC1, main_toc1), 29 functions, 28 live.
// Primary class: CKSrvTrigger  key 0x481  category Service  size 0x38  vtable 0xb20a68
// Other owners: FireTriggerActionsByIndex (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x235188  CKSrvTrigger_Delete
//   [ ] 0x2351d8  CKSrvTrigger_RecursiveRegistration
//   [ ] 0x2351e0  CKSrvTrigger_Save
//   [ ] 0x2351e8  CKSrvTrigger_Pause
//   [ ] 0x2351f0  CKSrvTrigger_Resume
//   [ ] 0x2351f8  CKSrvTrigger_SetDefaultState
//   [ ] 0x235240  CKSrvTrigger_InitializeService
//   [ ] 0x235248  RegisterCKSrvTriggerClass
//   [ ] 0x2352c0  _GLOBAL__I_2352c0
//   [x] 0x2352d0  CKSrvTrigger_Start
//   [ ] 0x235340  CKSrvTrigger_PostLoad
//   [x] 0x235368  CKSrvTrigger_Construct
//   [ ] 0x235400  CKSrvTrigger_Construct_2
//   [x] 0x235498  CKSrvTrigger_DeleteArray
//   [x] 0x235540  CKSrvTrigger_Destroy
//   [ ] 0x235628  FUN_00235628  [dead]
//   [ ] 0x235660  FireTriggerActionsByIndex_maybe
//   [x] 0x235768  CKSrvTrigger_Stop
//   [ ] 0x2357d8  CKSrvTrigger_Restart
//   [x] 0x235848  UpdateCKSrvTrigger
//   [ ] 0x235928  CKSrvTrigger_DestroyService
//   [x] 0x2359d8  CKSrvTrigger_Load
//   [ ] 0x235d30  CKSrvTrigger_Destructor
//   [x] 0x235df8  CKSrvTrigger_Create
//   [x] 0x235eb0  CKSrvTrigger_CreateArray
//   [ ] 0x236018  CKSrvTrigger_DestructBody
//   [ ] 0x2360e0  CKSrvTrigger_DeletingDestructor
//   [ ] 0x2361b0  KStub_Return1_2361b0
//   [ ] 0x2361b8  KStub_ReturnTrue_2361b8
//
//   [ ] 0x9b8950  CKSrvTrigger_IsKindOfClass  [inline]
//   [ ] 0x9b8988  CKSrvTrigger_GetClassType  [inline]
//   [ ] 0x9b8990  CKSrvTrigger_GetClassID  [inline]
#include "k2000/services/CKSrvTrigger.h"

#include <new>

#include "k2000/io/IKFile.h"
#include "k2000/logic/CKComparedData.h"
#include "k2000/logic/CKTriggerDomain.h"
#include "k2000/system/IKTime.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/Engine.h"

// 0x00235368 CKSrvTrigger_Construct. The stores in the original's order: the IKService part (its
// default members), +0x10, then the trigger's own; +0x0c, +0x24 and +0x28 are left as they are.
CKSrvTrigger::CKSrvTrigger() {
    m_unk10 = nullptr;
    m_namedRefCapacity = 1;
    m_apNamedRefs = nullptr;
    m_namedRefCount = 0;
    Engine_SetSrvTrigger(this);
    m_ui32NbRequestedStarterDatas = 0;
    m_ui32Priority = 0x82;
    m_ui32NbAllocatedActions = 0;
    m_ui32NbRequestedActions = 0;
    m_ui32NbAllocatedStarterDatas = 0;
}

// 0x00235540 CKSrvTrigger_Destroy: the action / starter-data block and the named references freed.
void CKSrvTrigger::Destroy() {
    if (m_aAllocatedActions != nullptr) {
        Mem_FreeAligned16(m_aAllocatedActions);
        m_aAllocatedActions = nullptr;
    }
    // The named references, from the last one down (OperatorDelete), then their array.
    for (uint32_t i = m_namedRefCount; i != 0; --i) ::operator delete(m_apNamedRefs[i - 1]);
    if (m_apNamedRefs != nullptr) {
        Mem_FreeAligned16(m_apNamedRefs);
        m_apNamedRefs = nullptr;
    }
    m_namedRefCount = 0;
    m_apNamedRefs = nullptr;
}

// 0x002359d8 CKSrvTrigger_Load
int32_t CKSrvTrigger::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    IKFile_ReadRef(file, &m_pRootDomain);
    ReadU32LE(file, &m_ui32NbAllocatedActions);
    ReadU32LE(file, &m_ui32NbAllocatedStarterDatas);
    // One block: the actions (0xc bytes each on the PS3), then the starter-data slots (one pointer each).
    const uint32_t size = m_ui32NbAllocatedActions * static_cast<uint32_t>(sizeof(CTriggerAction)) +
                          m_ui32NbAllocatedStarterDatas * static_cast<uint32_t>(sizeof(IKSerializable*));
    m_aAllocatedActions = size == 0 ? nullptr : static_cast<CTriggerAction*>(Mem_AllocAligned16(size));
    m_ui32NbRequestedStarterDatas = 0;
    m_ui32NbRequestedActions = 0;
    m_apAllocatedStarterDatas = reinterpret_cast<IKSerializable**>(m_aAllocatedActions + m_ui32NbAllocatedActions);

    uint32_t count = 0;
    ReadU32LE(file, &count);
    if (count == 0) {
        m_namedRefCapacity = 1;
        m_apNamedRefs = static_cast<NamedRef**>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(NamedRef*))));
        return 1;
    }
    m_namedRefCapacity = count;
    m_apNamedRefs = static_cast<NamedRef**>(Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(NamedRef*))));
    if (m_namedRefCapacity < count) {  // as in the original: cannot happen right after the assignment
        uint32_t capacity = count + 1;
        if (capacity == 0) capacity = 1;
        m_apNamedRefs = static_cast<NamedRef**>(
            Mem_ReallocAligned16(m_apNamedRefs, capacity * static_cast<uint32_t>(sizeof(NamedRef*))));
        m_namedRefCapacity = capacity;
    }
    m_namedRefCount = count;
    for (uint32_t i = count; i != 0;) {  // filled from the last record down
        --i;
        m_apNamedRefs[i] = static_cast<NamedRef*>(::operator new(sizeof(NamedRef)));  // OperatorNew(0x104)
        IKFile_ReadRef(file, &m_apNamedRefs[i]->m_object);
        IKFile_ReadLengthPrefixedString(file, m_apNamedRefs[i]->m_name, -1);
    }
    return 1;
}

// 0x00235768 CKSrvTrigger_Stop: the trigger domains reset to their start state, the pending starter data
// given back to the pool.
void CKSrvTrigger::Stop() {
    static_cast<CKTriggerDomain*>(m_pRootDomain)->ResetTriggersAndEnableState();
    for (SPendingStarterData* node = m_unk10; node != nullptr;) {
        SPendingStarterData* next = node->m_pNext;
        delete node;  // back to the FreeListPool in the original
        node = next;
    }
    m_unk10 = nullptr;
}

// 0x002352d0 CKSrvTrigger_Start: the trigger domains back to their initial enabled state, the pending starter
// data given back to the pool.
void CKSrvTrigger::Start() {
    static_cast<CKTriggerDomain*>(m_pRootDomain)->RestoreInitialEnableState();
    for (SPendingStarterData* node = m_unk10; node != nullptr;) {
        SPendingStarterData* next = node->m_pNext;
        delete node;  // back to the FreeListPool in the original
        node = next;
    }
    m_unk10 = nullptr;
}

// 0x00235848 UpdateCKSrvTrigger: only while the frame clock runs (state 0). The enabled root domain evaluates its
// triggers; then the queued starter data lose their "fired" bit (bit 0 of the byte at +0x08, bits 24-31 of the
// word here) and the pending list goes back to the pool.
void CKSrvTrigger::Update(IKTime* frameClock) {
    if (frameClock->m_eCurrentState != 0) return;
    CKTriggerDomain* root = static_cast<CKTriggerDomain*>(m_pRootDomain);
    if ((root->m_ba32Flags & 1) != 0) root->EvaluateTriggers();
    for (SPendingStarterData* node = m_unk10; node != nullptr; node = node->m_pNext) {
        static_cast<CKComparedData*>(node->m_pData)->m_unk08 &= 0xfeffffffu;
    }
    for (SPendingStarterData* node = m_unk10; node != nullptr;) {
        SPendingStarterData* next = node->m_pNext;
        delete node;  // back to the FreeListPool in the original
        node = next;
    }
    m_unk10 = nullptr;
}
