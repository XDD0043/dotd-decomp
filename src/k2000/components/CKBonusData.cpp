// CKBonusData.cpp - reconstructed original translation unit 0x126d20-0x127470 (GAME_TOC1, main_toc1), 18 functions, 15 live.
// Primary class: CKBonusData  key 0x686  category Component  size 0x14  vtable 0xb19d90
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x126d20  CKBonusData_Delete
//   [ ] 0x126d70  CKBonusData_Construct  [dead]
//   [ ] 0x126d80  CKBonusData_Construct_2  [dead]
//   [x] 0x126d90  CKBonusData_ResetRuntime_maybe
//   [ ] 0x126dd0  KStub_Return1_126dd0  [dead]
//   [ ] 0x126dd8  RegisterCKBonusDataClass
//   [ ] 0x126e50  _GLOBAL__I_126e50
//   [x] 0x126e60  CKBonusData_DeleteArray
//   [ ] 0x126f08  CKBonusData_Destructor
//   [ ] 0x126f38  CKBonusData_BaseDestructor
//   [ ] 0x126f68  CKBonusData_DeletingDestructor
//   [x] 0x126fb0  CKBonusData_CreateArray
//   [x] 0x127048  CKBonusData_Create
//   [ ] 0x127080  CKBonusData_Save
//   [ ] 0x127088  CKBonusData_RecursiveRegistration
//   [ ] 0x127090  CKBonusData_Destroy
//   [x] 0x1270d8  CKBonusData_LoadEntry
//   [x] 0x1272c8  CKBonusData_Load
//
//   [ ] 0x9a7040  CKBonusData_IsKindOfClass  [inline]
//   [x] 0x9a7068  CKBonusData_GetClassType  [inline]
//   [x] 0x9a7070  CKBonusData_GetClassID  [inline]
#include "k2000/components/CKBonusData.h"

#include "k2000/io/IKFile.h"

// 0x001270d8 CKBonusData_LoadEntry: six byte-swapped words (+0x14 and +0x18 are not read).
static void CKBonusData_LoadEntry(CKBonusData::Entry* entry, IKFile* file) {
    ReadU32LE(file, &entry->m_unk00);
    ReadU32LE(file, &entry->m_unk04);
    ReadU32LE(file, &entry->m_unk08);
    ReadF32LE(file, &entry->m_unk0c);
    ReadU32LE(file, &entry->m_unk10);
    ReadU32LE(file, &entry->m_unk1c);
}

// 0x001272c8 CKBonusData_Load
int32_t CKBonusData::Load(IKFile* file, int32_t type) {
    ReadU8(file, &m_count);
    // BUG(original): Create does not set +0x08, so a first Load with another type would free whatever
    // the heap left there. The front-end files only load it as K_LEVEL_PLATEFORMS.
    if (type != K_LEVEL_PLATEFORMS && m_pEntries != nullptr) {
        delete[] m_pEntries;  // OperatorDeleteArray
        m_pEntries = nullptr;
    }
    if (m_count == 0) {
        m_pEntries = nullptr;
    } else {
        m_pEntries = new Entry[m_count];  // OperatorNewArray(count << 5)
        for (uint32_t i = m_count; i != 0;) {  // from the last entry down
            --i;
            CKBonusData_LoadEntry(&m_pEntries[i], file);
        }
    }
    ReadF32LE(file, &m_unk0c);
    ReadU8(file, &m_unk10);
    return 1;
}

// 0x00126d90 CKBonusData_ResetRuntime_maybe (C1.6 gm)
void CKBonusData::ResetRuntime() {
    if (m_count == 0) return;
    int32_t i = 0;
    do {
        m_pEntries[i].m_unk18 = 0xffffffffu;
        ++i;
    } while (i < static_cast<int32_t>(m_count));
}
