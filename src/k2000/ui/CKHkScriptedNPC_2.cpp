// CKHkScriptedNPC_2.cpp - reconstructed original translation unit 0x5c7c80-0x5c9bc0 (GAME_TOC2, main_toc2), 31 functions, 31 live.
// Primary owner: CKHkScriptedNPC (not a registered class)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x5c7c80  CKHkScriptedNPC_Resume
//   [ ] 0x5c7ca8  CKHkScriptedNPC_Pause
//   [ ] 0x5c7cd0  CKHkScriptedNPC_OnLevelExit_maybe
//   [x] 0x5c7da8  CKHkScriptedNPC_ResetRuntime
//   [x] 0x5c7e08  CKHkScriptedNPC_ResetToInitialState_maybe
//   [ ] 0x5c7e48  CKHkScriptedNPC_PostLoad
//   [ ] 0x5c7eb0  CKHkScriptedNPC_Save
//   [ ] 0x5c7ed8  CKHkScriptedNPC_LevelReset
//   [ ] 0x5c7f30  CKHkScriptedNPC_HandleMessage
//   [ ] 0x5c8160  CKHkScriptedNPC_Construct_2
//   [x] 0x5c81d0  CKHkScriptedNPC_Construct
//   [x] 0x5c8240  CKHkScriptedNPC_DestroyArray
//   [ ] 0x5c82e8  CKHkScriptedNPC_ClearReferences
//   [ ] 0x5c8360  CKHkScriptedNPC_vfFC
//   [ ] 0x5c83c8  CKHkScriptedNPC_vfF8
//   [ ] 0x5c84a8  CKHkScriptedNPC_OnDeactivate
//   [ ] 0x5c85d8  CKHkScriptedNPC_OnActivate
//   [ ] 0x5c8780  CKHkScriptedNPC_TrySwitchBlock_maybe
//   [ ] 0x5c8a08  CKHkScriptedNPC_vfCC
//   [ ] 0x5c8ab0  CKHkScriptedNPC_vfD4
//   [ ] 0x5c8b58  CKHkScriptedNPC_ResolveTriggerProperty
//   [ ] 0x5c8c88  CKHkScriptedNPC_GetAnchorPosition_maybe
//   [ ] 0x5c8d30  CKHkScriptedNPC_ReinitRuntime
//   [ ] 0x5c8f28  CKHkScriptedNPC_QueueSignalsAndChainNextBlock_maybe
//   [ ] 0x5c9050  CKHkScriptedNPC_BaseDestructor
//   [ ] 0x5c90f0  CKHkScriptedNPC_DeletingDestructor
//   [ ] 0x5c91a0  CKHkScriptedNPC_Destructor
//   [x] 0x5c9240  CKHkScriptedNPC_CreateArray
//   [x] 0x5c9338  CKHkScriptedNPC_Create
//   [ ] 0x5c93b8  CKHkScriptedNPC_Update
//   [x] 0x5c9560  CKHkScriptedNPC_Load
//
//   [ ] 0x9cd560  CKHkScriptedNPC_IsKindOf  [inline]
//   [ ] 0x9cd5b8  CKHkScriptedNPC_GetClassGroup  [inline]
//   [ ] 0x9cd5c0  CKHkScriptedNPC_GetClassId  [inline]
#include "k2000/ui/CKHkScriptedNPC.h"

#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"

namespace {
// The TVector<T, 1> push the Load inlines: grows by one element when full (0 -> 1).
template <class T>
void PushBack(TVector<T, 1>& v, T value) {
    const uint32_t length = v.m_ui32NbUsedElt;
    if (v.m_ui32NbElt == length) {
        uint32_t capacity = length + 1;
        if (capacity == 0) capacity = 1;
        v.m_pBlock = static_cast<T*>(Mem_ReallocAligned16(v.m_pBlock, capacity * static_cast<uint32_t>(sizeof(T))));
        v.m_ui32NbElt = capacity;
    }
    v.m_pBlock[v.m_ui32NbUsedElt] = value;
    v.m_ui32NbUsedElt = v.m_ui32NbUsedElt + 1;
}
}  // namespace

// 0x005c9560 CKHkScriptedNPC_Load
int32_t CKHkScriptedNPC::Load(IKFile* file, int32_t type) {
    CKHkActorBase::Load(file, type);  // through TocBridge_CKHkActorBase_d82_maybe_Load
    if (type != K_LEVEL_PLATEFORMS) return 1;
    IKFile_ReadRef(file, &m_pUnk2C);
    IKFile_ReadRef(file, &m_pUnk30);
    ReadU8(file, &m_unk4D);
    uint32_t count = 0;
    ReadU32LE(file, &count);
    // BUG(original): a new one-element block replaces the old one (not freed); the length is not reset.
    m_vpUnk34.m_ui32NbElt = 1;
    m_vpUnk34.m_pBlock = static_cast<IKSerializable**>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(IKSerializable*))));
    for (uint32_t i = 0; i < count; ++i) {
        IKSerializable* ref = nullptr;
        IKFile_ReadRef(file, &ref);
        PushBack(m_vpUnk34, ref);
    }
    ReadU8(file, &m_unk51);
    ReadU8(file, &m_unk52);
    ReadU8(file, &m_unk53);
    ReadU8(file, &m_unk4E);
    ReadU8(file, &m_unk4F);
    m_tsUnk78.Load(file, 0);
    IKFile_ReadRef(file, &m_pUnk20);
    IKFile_ReadRef(file, &m_pUnk24);
    ReadU32LE(file, &count);
    m_vpUnk40.m_ui32NbElt = 1;
    m_vpUnk40.m_pBlock = static_cast<Entry**>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(Entry*))));
    for (uint32_t i = 0; i < count; ++i) {
        Entry* entry = new Entry;  // OperatorNew(8), no constructor
        ReadU8(file, &entry->m_unk0);
        ReadU32LE(file, &entry->m_unk4);
        PushBack(m_vpUnk40, entry);
    }
    return 1;
}

// 0x005c7e08 CKHkScriptedNPC_SetDefaultState: the two default bytes copied to the current ones.
void CKHkScriptedNPC::SetDefaultState(int32_t flag) {
    CKHkActorBase::SetDefaultState(flag);
    m_unk4C = m_unk4D;
    m_unk50 = m_unk51;
}

// 0x005c7da8 CKHkScriptedNPC_ResetRuntime (the Start). KStub_Nop_5cebf0(+0x20, this) is empty.
void CKHkScriptedNPC::Start() {
    CKHkActorBase::Start();
    m_unk58 = 0xffffffffu;
    m_unk80 = 0;
    m_unk28 = 0;
    m_unk54 = 0;
}
