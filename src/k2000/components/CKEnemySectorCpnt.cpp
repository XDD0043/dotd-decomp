// CKEnemySectorCpnt.cpp - reconstructed original translation unit 0x2b30b8-0x2b3bc8 (GAME_TOC1, main_toc1), 20 functions, 18 live.
// Primary class: CKEnemySectorCpnt  key 0x386  category Component  size 0x28  vtable 0xb22528
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x2b30b8  CKEnemySectorCpnt_Delete
//   [x] 0x2b3108  CKEnemySectorCpnt_RecursiveRegistration  (returns 1, registers nothing: the default)
//   [x] 0x2b3110  CKEnemySectorCpnt_GetAnimatedNode
//   [x] 0x2b3128  CKEnemySectorCpnt_GetAnimDictionary
//   [x] 0x2b3140  CKEnemySectorCpnt_GetChainedEntryFromArray0C_maybe
//   [x] 0x2b31b0  CKEnemySectorCpnt_GetCollisionVolume_maybe
//   [x] 0x2b31c8  CKEnemySectorCpnt_GetArray18Entry_maybe
//   [x] 0x2b31e0  CKEnemySectorCpnt_GetHotSpot
//   [ ] 0x2b31f8  CKEnemySectorCpnt_GetArray20Entry_maybe  [dead]
//   [ ] 0x2b3210  RegisterCKEnemySectorCpntClass
//   [ ] 0x2b3288  _GLOBAL__I_2b3288
//   [x] 0x2b3298  CKEnemySectorCpnt_FreeBuffers_maybe  (CKEnemySectorCpnt::Destroy)
//   [x] 0x2b33c0  CKEnemySectorCpnt_Destroy
//   [x] 0x2b33c8  CKEnemySectorCpnt_DeleteArray
//   [x] 0x2b3470  CKEnemySectorCpnt_Create
//   [ ] 0x2b34a8  CKEnemySectorCpnt_GetChainedEntryFromArray24_maybe  [dead]
//   [x] 0x2b3518  CKEnemySectorCpnt_CreateArray
//   [ ] 0x2b35b0  CKEnemySectorCpnt_Save
//   [x] 0x2b35b8  CKEnemySectorCpnt_PostLoad  (returns 1: the default)
//   [x] 0x2b35c0  CKEnemySectorCpnt_Load
//
//   [ ] 0x9bcc40  CKEnemySectorCpnt_IsKindOfClass  [inline]
//   [x] 0x9bcc68  CKEnemySectorCpnt_GetClassType  [inline]
//   [x] 0x9bcc70  CKEnemySectorCpnt_GetClassID  [inline]
//   [ ] 0x9bcc78  CKEnemySectorCpnt_DeletingDestructor  [inline]
//   [ ] 0x9bccc0  CKEnemySectorCpnt_Destructor  [inline]
#include "k2000/components/CKEnemySectorCpnt.h"

#include "k2000/dictionaries/CAnimationDictionary.h"
#include "k2000/graphical/animation/CKBlenderController.h"

#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"

namespace {
// The inlined array read: a block of count references, read through the resolver's array read
// (resolver vt+0x28) or raw without a resolver.
IKSerializable** ReadRefArray(IKFile* file, uint8_t count) {
    IKSerializable** array = static_cast<IKSerializable**>(
        Mem_AllocAligned16(static_cast<uint32_t>(count) * static_cast<uint32_t>(sizeof(IKSerializable*))));
    IKFile_ReadObjectRefArray(file, array, count);
    return array;
}
}  // namespace

// 0x002b35c0 CKEnemySectorCpnt_Load
int32_t CKEnemySectorCpnt::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    uint8_t count = 0;
    ReadU8(file, &count);
    m_apUnk04 = ReadRefArray(file, count);
    m_apUnk08 = ReadRefArray(file, count);
    m_apUnk0c = ReadRefArray(file, count);
    ReadU8(file, &count);
    m_apUnk10 = ReadRefArray(file, count);
    ReadU8(file, &count);
    m_apUnk14 = ReadRefArray(file, count);
    ReadU8(file, &count);
    m_apUnk18 = ReadRefArray(file, count);
    IKFile_ReadRef(file, &m_pUnk1c);
    ReadU8(file, &count);
    m_apUnk20 = ReadRefArray(file, count);
    m_apUnk24 = ReadRefArray(file, count);
    return 1;
}

// 0x002b3140 CKEnemySectorCpnt_GetChainedEntryFromArray0C_maybe
IKSerializable* CKEnemySectorCpnt::GetChainedEntry(uint32_t layer, uint32_t slot) const {
    const CAnimationDictionary* dictionary = reinterpret_cast<const CAnimationDictionary*>(m_apUnk08[layer]);
    IKSerializable* entry = m_apUnk0c[layer];
    const uint32_t steps = dictionary->m_ui32NbColumns - slot;
    if (steps != 1) {
        for (uint32_t n = steps - 1; n != 0; --n) entry = static_cast<CKBlenderController*>(entry)->m_apControllers[0];
    }
    if (slot != 0) entry = static_cast<CKBlenderController*>(entry)->m_apControllers[1];
    return entry;
}

// 0x002b3298 CKEnemySectorCpnt_FreeBuffers_maybe (CKEnemySectorCpnt_Destroy 0x2b33c0)
void CKEnemySectorCpnt::Destroy() {
    IKSerializable*** const arrays[] = {&m_apUnk04, &m_apUnk08, &m_apUnk0c, &m_apUnk10,
                                        &m_apUnk14, &m_apUnk18, &m_apUnk20, &m_apUnk24};
    for (IKSerializable*** array : arrays) {
        if (*array == nullptr) continue;
        Mem_FreeAligned16(*array);  // 0x00052fb8
        *array = nullptr;
    }
}
