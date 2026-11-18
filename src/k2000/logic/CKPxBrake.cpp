// CKPxBrake.cpp - reconstructed original translation unit 0x22fc48-0x230598 (GAME_TOC1, main_toc1), 15 functions, 15 live.
// Primary class: CKPxBrake  key 0x494c  category Logic  size 0x40  vtable 0xb20690
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x22fc48  CKPxBrake_Delete
//   [ ] 0x22fc98  RegisterCKPxBrakeClass
//   [ ] 0x22fd10  _GLOBAL__I_22fd10
//   [ ] 0x22fd20  CKPxBrake_Save
//   [x] 0x22fd48  CKPxBrake_RecursiveRegistration  (the base's vf24: returns 1, registers nothing)
//   [x] 0x22fd70  CKPxBrake_Destroy
//   [x] 0x22fdb8  CKPxBrake_DestructBody  (the destructor)
//   [x] 0x22fe28  CKPxBrake_Construct  (header)
//   [x] 0x22fe88  CKPxBrake_Construct_2  (the constructor's second C++ variant)
//   [x] 0x22fee8  CKPxBrake_DeleteArray
//   [x] 0x22ff88  CKPxBrake_DeletingDestructor  (the destructor; delete)
//   [x] 0x230000  CKPxBrake_Destructor
//   [x] 0x230070  CKPxBrake_Load
//   [x] 0x230448  CKPxBrake_Create
//   [x] 0x2304b8  CKPxBrake_CreateArray
//
//   [ ] 0x9b7238  CKPxBrake_IsKindOfClass  [inline]
//   [ ] 0x9b7260  CKPxBrake_GetClassType  [inline]
//   [ ] 0x9b7268  CKPxBrake_GetClassID  [inline]
#include "k2000/logic/CKPxBrake.h"

#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"

namespace {
// The inlined word-array read: `count` words in one read (Mem_AllocAligned16, each word swapped), or null for none.
uint32_t* ReadWordArray(IKFile* file, uint32_t count) {
    if (count == 0) return nullptr;
    uint32_t* words = static_cast<uint32_t*>(Mem_AllocAligned16(count * 4));  // 0x00053198
    ReadU32LEWords(file, words, count);
    return words;
}

// The inlined reference-list read: a 16-bit count, a fresh block of that many references (one for none; native
// pointer size), then the references one by one. BUG(original): the previous block is not freed (a second Load of the
// same object leaks it); the capacity test after the allocation can never grow it.
void ReadRefList(IKFile* file, TVector<IKSerializable*, 1>& list) {
    uint16_t count = 0;
    ReadU16LE(file, &count);
    if (count == 0) {
        list.m_ui32NbElt = 1;
        list.m_pBlock = static_cast<IKSerializable**>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(IKSerializable*))));
    } else {
        list.m_ui32NbElt = count;
        list.m_pBlock = static_cast<IKSerializable**>(
            Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(IKSerializable*))));
    }
    if (list.m_ui32NbElt < count) {
        uint32_t capacity = static_cast<uint32_t>(count) + 1;
        list.m_pBlock = static_cast<IKSerializable**>(
            Mem_ReallocAligned16(list.m_pBlock, capacity * static_cast<uint32_t>(sizeof(IKSerializable*))));
        list.m_ui32NbElt = capacity;
    }
    list.m_ui32NbUsedElt = count;
    for (uint32_t i = 0; i < count; ++i) IKFile_ReadRef(file, &list.m_pBlock[i]);
}

// The destructors' inlined list release: the block freed, the length and block cleared (the capacity kept).
void FreeRefList(TVector<IKSerializable*, 1>& list) {
    if (list.m_pBlock != nullptr) Mem_FreeAligned16(list.m_pBlock);  // 0x00052fb8
    list.m_ui32NbUsedElt = 0;
    list.m_pBlock = nullptr;
}
}  // namespace

// 0x00230000 CKPxBrake_Destructor
CKPxBrake::~CKPxBrake() { FreeRefList(m_unk30); }

// 0x0022fd70 CKPxBrake_Destroy
void CKPxBrake::Destroy() {
    KBase468C::Destroy();  // CKPxObject_ClearReferences_BaseNop_maybe
    if (m_unk24 != nullptr) Mem_FreeAligned16(m_unk24);
}

// 0x00230070 CKPxBrake_Load
int32_t CKPxBrake::Load(IKFile* file, int32_t type) {
    KBase468C::Load(file, type);  // 0x00218078
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadU8(file, &m_unk18);
    IKFile_ReadRef(file, &m_unk1c);
    m_unk20 = 0;
    ReadU16LE(file, &m_unk22);
    m_unk24 = nullptr;
    m_unk24 = ReadWordArray(file, m_unk22);
    m_unk28 = 0;
    ReadU32LE(file, &m_unk2c);
    ReadRefList(file, m_unk30);
    ReadU32LE(file, &m_unk3c);
    return 1;
}
