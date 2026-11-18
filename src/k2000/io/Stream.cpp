// Stream.cpp - the memcard queue (its constructor and destructor are in SaveDataRequest.cpp).
//
// Reconstructed original translation unit: 0x2b600-0x2bcd8 (GAME_TOC1, main_toc1), 11 functions, 6 live.
// Primary owner: Stream (not a registered class)
// Other owners: CKMemcardRequestQueue (4), CKSavingManager (1), CompareObjectsByClassKey (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x2b600  CKMemcardRequestQueue_Construct
//   [x] 0x2b648  CKMemcardRequestQueue_Construct_2  (the second copy of 0x2b600: CKMemcardRequestQueue::CKMemcardRequestQueue, SaveDataRequest.cpp)
//   [x] 0x2b690  CKMemcardRequestQueue_Destructor_2_maybe  (the second copy of 0x2b760: ~CKMemcardRequestQueue, SaveDataRequest.cpp)
//   [x] 0x2b760  CKMemcardRequestQueue_Destructor_maybe
//   [x] 0x2b830  CKSavingManager_Delete  (the registry factory Delete: DOTD_DECLARE_FACTORIES(CKSavingManager))
//   [x] 0x2b880  CompareObjectsByClassKey_maybe  (only the dead CKSavingManager_SortObjectsByClassKey_maybe passes it)
//   [ ] 0x2ba28  Stream_ReadBytesRaw  [dead]
//   [ ] 0x2ba78  Stream_ReadU16ArraySwapped  [dead]
//   [ ] 0x2bb10  Stream_ReadU16ArraySwapped_2  [dead]
//   [ ] 0x2bba8  Stream_ReadU32ArraySwapped  [dead]
//   [ ] 0x2bc40  Stream_ReadU32ArraySwapped_2  [dead]

#include "k2000/core/IKSerializable.h"

// C2.8 port-all P08.
// 0x0002b880 CompareObjectsByClassKey_maybe: the qsort comparator of two object pointers by GetClassType (vt+0x14), then
// GetClassID (vt+0x18), each read twice as the original does; -1 / 0 / 1.
int32_t CompareObjectsByClassKey(const void* a, const void* b) {
    IKSerializable* x = *static_cast<IKSerializable* const*>(a);
    IKSerializable* y = *static_cast<IKSerializable* const*>(b);
    if (static_cast<uint32_t>(x->GetClassType()) > static_cast<uint32_t>(y->GetClassType())) return 1;
    if (static_cast<uint32_t>(x->GetClassType()) < static_cast<uint32_t>(y->GetClassType())) return -1;
    if (static_cast<uint32_t>(x->GetClassID()) > static_cast<uint32_t>(y->GetClassID())) return 1;
    if (static_cast<uint32_t>(x->GetClassID()) < static_cast<uint32_t>(y->GetClassID())) return -1;
    return 0;
}
