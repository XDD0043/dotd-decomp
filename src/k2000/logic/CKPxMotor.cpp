// CKPxMotor.cpp - reconstructed original translation unit 0x230598-0x2317a8 (GAME_TOC1, main_toc1), 18 functions, 15 live.
// Primary class: CKPxMotor  key 0x48cc  category Logic  size 0x80  vtable 0xb206e8
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x230598  CKPxMotor_Delete
//   [ ] 0x2305e8  CKPxMotor_BuildQuadraticTable_maybe  [dead]
//   [ ] 0x230660  CKPxMotor_InterpolateCurveGaps_maybe  [dead]
//   [ ] 0x2307c0  RegisterCKPxMotorClass
//   [ ] 0x230838  _GLOBAL__I_230838
//   [ ] 0x230848  CKPxMotor_RebuildGearTables_maybe  [dead]
//   [ ] 0x2309c0  CKPxMotor_Save
//   [x] 0x2309e8  CKPxMotor_RecursiveRegistration  (the base's vf24: returns 1, registers nothing)
//   [x] 0x230a10  CKPxMotor_Destroy
//   [x] 0x230ab8  CKPxMotor_Destructor
//   [x] 0x230b28  CKPxMotor_Construct  (header)
//   [x] 0x230b88  CKPxMotor_Construct_2  (the constructor's second C++ variant)
//   [x] 0x230be8  CKPxMotor_DeleteArray
//   [x] 0x230c88  CKPxMotor_DestructBody  (the destructor)
//   [x] 0x230cf8  CKPxMotor_DeletingDestructor  (the destructor; delete)
//   [x] 0x230d70  CKPxMotor_CreateArray
//   [x] 0x230e50  CKPxMotor_Create
//   [x] 0x230ec0  CKPxMotor_Load
//
//   [ ] 0x9b7270  CKPxMotor_IsKindOfClass  [inline]
//   [ ] 0x9b7298  CKPxMotor_GetClassType  [inline]
//   [ ] 0x9b72a0  CKPxMotor_GetClassID  [inline]
#include "k2000/logic/CKPxMotor.h"

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

// 0x00230ab8 CKPxMotor_Destructor
CKPxMotor::~CKPxMotor() { FreeRefList(m_unk70); }

// 0x00230a10 CKPxMotor_Destroy
void CKPxMotor::Destroy() {
    KBase468C::Destroy();  // CKPxObject_ClearReferences_BaseNop_maybe
    if (m_unk24 != nullptr) Mem_FreeAligned16(m_unk24);
    if (m_unk30 != nullptr) {
        Mem_FreeAligned16(m_unk30);
        Mem_FreeAligned16(m_unk34);
        Mem_FreeAligned16(m_unk38);
    }
    if (m_unk40 != nullptr) Mem_FreeAligned16(m_unk40);
    if (m_unk58 != nullptr) Mem_FreeAligned16(m_unk58);
}

// 0x00230ec0 CKPxMotor_Load
int32_t CKPxMotor::Load(IKFile* file, int32_t type) {
    KBase468C::Load(file, type);  // 0x00218078
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadU8(file, &m_unk18);
    IKFile_ReadRef(file, &m_unk1c);
    ReadU8(file, &m_unk20);
    ReadU8(file, &m_unk21);
    m_unk24 = nullptr;
    m_unk24 = ReadWordArray(file, m_unk21);
    m_unk28 = 2;
    ReadU32LE(file, &m_unk2c);
    m_unk30 = nullptr;
    if (m_unk21 != 0) {
        m_unk30 = ReadWordArray(file, m_unk21);
        m_unk34 = ReadWordArray(file, m_unk21);
        m_unk38 = ReadWordArray(file, m_unk21);
    }
    m_unk3c = 0;
    ReadU16LE(file, &m_unk3e);
    m_unk40 = nullptr;
    m_unk40 = ReadWordArray(file, m_unk3e);
    m_unk44 = 0;
    m_unk48 = 0;
    ReadU32LE(file, &m_unk4c);
    ReadU32LE(file, &m_unk50);
    ReadU16LE(file, &m_unk54);
    m_unk58 = nullptr;
    m_unk58 = ReadWordArray(file, m_unk54);
    ReadU16LE(file, &m_unk5c);
    ReadU32LE(file, &m_unk60);
    ReadU32LE(file, &m_unk64);
    ReadU32LE(file, &m_unk68);
    ReadU32LE(file, &m_unk6c);
    ReadRefList(file, m_unk70);
    ReadU32LE(file, &m_unk7c);
    return 1;
}
