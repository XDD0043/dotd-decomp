// CKTargetCursorFxData.cpp - reconstructed original translation unit 0x1d4890-0x1d57b8 (GAME_TOC1, main_toc1), 14 functions, 14 live.
// Primary class: CKTargetCursorFxData  key 0x464c  category Logic  size 0x60  vtable 0xb1da20
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1d4890  CKTargetCursorFxData_Delete
//   [x] 0x1d48e0  CKTargetCursorFxData_GetNodeClassKey
//   [x] 0x1d48e8  CKTargetCursorFxData_PostLoad  (returns 1)
//   [ ] 0x1d48f0  RegisterCKTargetCursorFxDataClass
//   [ ] 0x1d4968  _GLOBAL__I_1d4968
//   [x] 0x1d4978  CKTargetCursorFxData_RecursiveRegistration  (IKFxData's, nothing)
//   [x] 0x1d49a0  CKTargetCursorFxData_DeleteArray
//   [x] 0x1d4a48  CKTargetCursorFxData_CreateArray
//   [x] 0x1d4af0  CKTargetCursorFxData_Create
//   [x] 0x1d4b38  CKTargetCursorFxData_GetInfo  (the default)
//   [x] 0x1d4b40  CKTargetCursorFxData_MessageProc  (inline in the header)
//   [x] 0x1d4b70  CKTargetCursorFxData_Destroy  (empty)
//   [x] 0x1d4b78  CKTargetCursorFxData_Load
//   [ ] 0x1d51d0  CKTargetCursorFxData_Save
//
//   [ ] 0x9ad4b0  CKTargetCursorFxData_IsKindOfClass  [inline]
//   [x] 0x9ad4e8  CKTargetCursorFxData_GetClassType  [inline]
//   [x] 0x9ad4f0  CKTargetCursorFxData_GetClassID  [inline]
//   [ ] 0x9ad4f8  CKTargetCursorFxData_DeletingDestructor  [inline]
//   [ ] 0x9ad550  CKTargetCursorFxData_Destructor  [inline]
#include "k2000/logic/fx/CKTargetCursorFxData.h"

#include "k2000/io/IKFile.h"

// 0x001d4b78 CKTargetCursorFxData_Load
int32_t CKTargetCursorFxData::Load(IKFile* file, int32_t type) {
    IKFxData::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadF32LE(file, &m_unk08);
    ReadF32LE(file, &m_unk0c);
    ReadU8(file, &m_unk10[0]);
    ReadU8(file, &m_unk10[1]);
    ReadU8(file, &m_unk10[2]);
    ReadF32LE(file, &m_unk14);
    ReadF32LE(file, &m_unk18);
    ReadF32LE(file, &m_unk1c);
    ReadF32LE(file, &m_unk20);
    ReadF32LE(file, &m_unk24);
    ReadF32LE(file, &m_unk28);
    ReadF32LE(file, &m_unk2c);
    ReadU32LE(file, &m_unk30);
    ReadU8(file, &m_unk34);
    ReadU8(file, &m_unk35);
    ReadF32LE(file, &m_unk38);
    ReadF32LE(file, &m_unk3c);
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(&m_unk40), 3);  // one 12-byte read: +0x40, +0x44, +0x48
    ReadF32LE(file, &m_unk4c);
    ReadF32LE(file, &m_unk50);
    ReadF32LE(file, &m_unk54);
    ReadF32LE(file, &m_unk58);
    return 1;
}
