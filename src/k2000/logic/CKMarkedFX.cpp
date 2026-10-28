// CKMarkedFX.cpp - reconstructed original translation unit 0x5ceb68-0x5d1748 (GAME_TOC2, main_toc2), 38 functions, 30 live.
// Primary class: CKMarkedFX  key 0xab4c  category Logic  size ?  vtable 0xb301e0
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x5ceb68  CKMarkedFX_Delete
//   [ ] 0x5cebb8  CKMarkedFX_Construct  [dead]
//   [ ] 0x5cebf0  KStub_Nop_5cebf0
//   [ ] 0x5cebf8  KStub_Nop_5cebf8
//   [ ] 0x5cec00  CKMarkedFX_StopChannelNodesMatching_maybe  [dead]
//   [ ] 0x5ced80  CKMarkedFX_StopAllChannelNodes_maybe
//   [ ] 0x5ceec0  CKMarkedFX_StopFlaggedChannelNodes_maybe
//   [ ] 0x5cf020  KStub_Nop_5cf020  [dead]
//   [ ] 0x5cf028  KStub_Nop_5cf028  [dead]
//   [ ] 0x5cf030  KStub_Nop_5cf030  [dead]
//   [ ] 0x5cf038  KStub_Nop_5cf038  [dead]
//   [ ] 0x5cf040  CKMarkedFX_Construct_2  [dead]
//   [x] 0x5cf078  CKMarkedFX_DeleteArray
//   [ ] 0x5cf118  RegisterCKMarkedFXClass
//   [ ] 0x5cf1a0  _GLOBAL__D_5cf1a0
//   [ ] 0x5cf1b0  _GLOBAL__I_5cf1b0
//   [ ] 0x5cf1c0  CKMarkedFX_ResetChannels_maybe
//   [ ] 0x5cf258  CKMarkedFX_Save
//   [ ] 0x5cf260  CKMarkedFX_RecursiveRegistration
//   [ ] 0x5cf268  CKMarkedFX_PostLoad
//   [ ] 0x5cf300  CKMarkedFX_Destroy
//   [x] 0x5cf4e8  CKMarkedFX_CreateArray
//   [x] 0x5cf5a8  CKMarkedFX_Create
//   [ ] 0x5cf608  CKMarkedFX_UpdateChannel_maybe
//   [ ] 0x5cfb70  CKMarkedFX_StopAllChannelNodes_2_maybe
//   [ ] 0x5cfcb0  CKMarkedFX_StopAllChannelNodesAndReset_maybe
//   [ ] 0x5cfdf8  CKMarkedFX_StartChannelNodesMatching_maybe  [dead]
//   [ ] 0x5d0178  CKMarkedFX_FireChannel_maybe
//   [ ] 0x5d0558  CKMarkedFX_FireChannelIfMarkCrossed_maybe
//   [ ] 0x5d0640  CKMarkedFX_UpdateFromAnimMarks
//   [x] 0x5d0a20  CKMarkedFX_LoadFxMarkRecord_maybe
//   [x] 0x5d0bb8  CKMarkedFX_LoadFxEntry_maybe
//   [x] 0x5d0da8  CKMarkedFX_LoadChannelEntry_maybe
//   [x] 0x5d0f28  CKMarkedFX_LoadChannelTable_maybe
//   [x] 0x5d1118  CKMarkedFX_Load
//   [ ] 0x5d1568  CKMarkedFX_DeletingDestructor
//   [ ] 0x5d1618  CKMarkedFX_Destructor
//   [ ] 0x5d16b0  CKMarkedFX_Destructor_2
//
//   [x] 0x9cd6b8  CKMarkedFX_GetClassType  [inline]
//   [x] 0x9cd6c0  CKMarkedFX_GetClassID  [inline]
//   [ ] 0x9cd6c8  CKMarkedFX_IsKindOfClass  [inline]
#include "k2000/logic/CKMarkedFX.h"

#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"

namespace {
// The inlined push_back of the record lists: grows by one element when full.
template <class T>
void PushBackGrow1(TVector<T*, 1>* list, T* element) {
    const uint32_t used = list->m_ui32NbUsedElt;
    if (list->m_ui32NbElt == used) {
        uint32_t capacity = used + 1;
        uint32_t bytes = capacity * static_cast<uint32_t>(sizeof(T*));
        if (capacity == 0) {
            capacity = 1;
            bytes = static_cast<uint32_t>(sizeof(T*));
        }
        list->m_pBlock = static_cast<T**>(Mem_ReallocAligned16(list->m_pBlock, bytes));
        list->m_ui32NbElt = capacity;
    }
    list->m_pBlock[list->m_ui32NbUsedElt] = element;
    ++list->m_ui32NbUsedElt;
}

// The list reset every Load helper does before its loop: capacity 1 and a new one-element block (the old
// block is not freed and the length is not reset).
template <class T>
void ResetToOne(TVector<T*, 1>* list) {
    list->m_ui32NbElt = 1;
    list->m_pBlock = static_cast<T**>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(T*))));
}
}  // namespace

// 0x005cf5a8 CKMarkedFX_Create, the inlined constructor, in its store order.
CKMarkedFX::CKMarkedFX() {
    m_fxEntries.m_pBlock = nullptr;
    m_fxEntries.m_ui32NbElt = 1;
    m_fxEntries.m_ui32NbUsedElt = 0;
    m_channels.m_ui32NbElt = 1;
    m_channels.m_ui32NbUsedElt = 0;
    m_channels.m_pBlock = nullptr;
}

// 0x005d0a20 CKMarkedFX_LoadFxMarkRecord_maybe
void CKMarkedFX::MarkRecord::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return;
    ReadU32LE(file, &m_unk00);
    IKFile_ReadRef(file, &m_unk08);
    IKFile_ReadRef(file, &m_unk0c);
    ReadU32LE(file, &m_unk04);
}

// 0x005d0bb8 CKMarkedFX_LoadFxEntry_maybe
void CKMarkedFX::FxEntry::Load(IKFile* file, int32_t type, CKMarkedFX* owner) {
    (void)owner;  // passed on to the mark records, which ignore it
    if (type != K_LEVEL_PLATEFORMS) return;
    IKFile_ReadRef(file, &m_unk00);
    uint32_t count = 0;
    ReadU32LE(file, &count);
    ResetToOne(&m_marks);
    for (uint32_t i = 0; i < count; ++i) {
        MarkRecord* record = static_cast<MarkRecord*>(::operator new(sizeof(MarkRecord)));
        record->Load(file, K_LEVEL_PLATEFORMS);
        PushBackGrow1(&m_marks, record);
    }
}

// 0x005d0da8 CKMarkedFX_LoadChannelEntry_maybe
void CKMarkedFX::ChannelEntry::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return;
    ReadU32LE(file, &m_unk04);
    IKFile_ReadRef(file, &m_unk0c);
    ReadU32LE(file, &m_unk08);
    ReadU8(file, &m_unk10);
}

// 0x005d0f28 CKMarkedFX_LoadChannelTable_maybe
void CKMarkedFX::ChannelTable::Load(IKFile* file, int32_t type, CKMarkedFX* owner) {
    (void)owner;  // passed on to the channel entries, which ignore it
    if (type != K_LEVEL_PLATEFORMS) return;
    IKFile_ReadRef(file, &m_unk00);
    uint32_t count = 0;
    ReadU32LE(file, &count);
    ResetToOne(&m_entries);
    for (uint32_t i = 0; i < count; ++i) {
        ChannelEntry* entry = static_cast<ChannelEntry*>(::operator new(sizeof(ChannelEntry)));
        entry->Load(file, K_LEVEL_PLATEFORMS);
        PushBackGrow1(&m_entries, entry);
    }
}

// 0x005d1118 CKMarkedFX_Load
int32_t CKMarkedFX::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    IKFile_ReadRef(file, &m_unk04);
    IKFile_ReadRef(file, &m_unk08);
    uint32_t count = 0;
    ReadU32LE(file, &count);
    ResetToOne(&m_fxEntries);
    for (uint32_t i = 0; i < count; ++i) {
        FxEntry* entry = static_cast<FxEntry*>(::operator new(sizeof(FxEntry)));
        entry->m_marks.m_ui32NbElt = 1;
        entry->m_marks.m_pBlock = nullptr;
        entry->m_marks.m_ui32NbUsedElt = 0;
        entry->Load(file, K_LEVEL_PLATEFORMS, this);
        PushBackGrow1(&m_fxEntries, entry);
    }
    count = 0;
    ReadU32LE(file, &count);
    ResetToOne(&m_channels);
    for (uint32_t i = 0; i < count; ++i) {
        ChannelTable* table = static_cast<ChannelTable*>(::operator new(sizeof(ChannelTable)));
        table->m_entries.m_ui32NbElt = 1;
        table->m_entries.m_pBlock = nullptr;
        table->m_entries.m_ui32NbUsedElt = 0;
        table->Load(file, K_LEVEL_PLATEFORMS, this);
        PushBackGrow1(&m_channels, table);
    }
    IKFile_ReadRef(file, &m_unk0c);
    return 1;
}
