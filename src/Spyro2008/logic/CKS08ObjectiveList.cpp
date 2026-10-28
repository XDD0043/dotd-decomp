// CKS08ObjectiveList.cpp - reconstructed original translation unit 0x506400-0x506ba8 (GAME_TOC1, main_toc1), 21 functions, 17 live.
// Primary class: CKS08ObjectiveList  key 0x920c  category Logic  size 0xc  vtable 0xb2b2f0
// Other owners: CKS08GameLevel (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x506400  CKS08ObjectiveList_GetFirstTextId_maybe
//   [ ] 0x506430  CKS08ObjectiveList_Construct  [dead]
//   [ ] 0x506448  CKS08ObjectiveList_Construct_2  [dead]
//   [ ] 0x506460  RegisterCKS08ObjectiveListClass
//   [ ] 0x5064d8  _GLOBAL__I_5064d8
//   [ ] 0x5064e8  CKS08ObjectiveList_FreeEntries_maybe
//   [x] 0x506530  CKS08ObjectiveList_DeleteArray
//   [ ] 0x5065d8  CKS08ObjectiveList_AllocEntries_maybe
//   [ ] 0x506638  CKS08ObjectiveList_Destructor
//   [x] 0x506650  CKS08ObjectiveList_Create
//   [x] 0x506690  CKS08ObjectiveList_CreateArray
//   [ ] 0x506738  CKS08ObjectiveList_Save
//   [ ] 0x506740  CKS08ObjectiveList_PostLoad
//   [ ] 0x506748  KStub_Nop_506748  [dead]
//   [x] 0x506750  CKS08ObjectiveList_LoadEntry
//   [ ] 0x506880  CKS08ObjectiveList_RecursiveRegistration
//   [ ] 0x506990  CKS08ObjectiveList_Destroy
//   [x] 0x5069d8  CKS08ObjectiveList_Load
//   [ ] 0x506b00  CKS08ObjectiveList_Destructor_2  [dead]
//   [ ] 0x506b18  CKS08ObjectiveList_DeletingDestructor
//   [ ] 0x506b58  CKS08GameLevel_Delete
//
//   [ ] 0x9c7038  CKS08ObjectiveList_GetClassType  [inline]
//   [ ] 0x9c7040  CKS08ObjectiveList_GetClassID  [inline]
//   [ ] 0x9c7048  CKS08ObjectiveList_IsKindOfClass  [inline]
#include "Spyro2008/logic/CKS08ObjectiveList.h"

#include "k2000/io/IKFile.h"

// 0x00506650 CKS08ObjectiveList_Create (the constructor inlined): only +0x04. The count is left as it is.
CKS08ObjectiveList::CKS08ObjectiveList() { m_aEntries = nullptr; }

namespace {

// 0x00506750 CKS08ObjectiveList_LoadEntry: the reference, then two u16 (lhbrx after each 2-byte read).
// The original tests the type itself (only K_LEVEL_PLATEFORMS reads); its caller passes 0.
void LoadEntry(CKS08ObjectiveList::Entry* entry, IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return;
    IKFile_ReadRef(file, &entry->m_pObject);
    ReadU16LE(file, &entry->m_ui16Unk4);
    ReadU16LE(file, &entry->m_ui16Unk6);
}

}  // namespace

// 0x005069d8 CKS08ObjectiveList_Load. The entries are read from the last one down.
int32_t CKS08ObjectiveList::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadU16LE(file, &m_ui16NbEntries);
    if (m_ui16NbEntries == 0) {
        m_aEntries = nullptr;
    } else {
        m_aEntries = new Entry[m_ui16NbEntries];  // OperatorNewArray(count * 8)
    }
    for (uint32_t i = m_ui16NbEntries; i-- != 0;) LoadEntry(&m_aEntries[i], file, K_LEVEL_PLATEFORMS);
    return 1;
}
