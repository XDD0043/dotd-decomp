// CKInputIconFxData.cpp - reconstructed original translation unit 0x1c34f0-0x1c4480 (GAME_TOC1, main_toc1), 19 functions, 17 live.
// Primary class: CKInputIconFxData  key 0x45cc  category Logic  size 0x48  vtable 0xb1d030
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1c34f0  CKInputIconFxData_Delete
//   [ ] 0x1c3540  CKInputIconFxData_Construct  [dead]
//   [ ] 0x1c35c8  CKInputIconFxData_PostLoad
//   [x] 0x1c35d8  CKInputIconFxData_GetNodeClassKey
//   [ ] 0x1c35e0  RegisterCKInputIconFxDataClass
//   [ ] 0x1c3658  _GLOBAL__I_1c3658
//   [ ] 0x1c3668  CKInputIconFxData_Save
//   [ ] 0x1c3690  CKInputIconFxData_RecursiveRegistration
//   [x] 0x1c36b8  CKInputIconFxData_DeleteArray
//   [ ] 0x1c3760  CKInputIconFxData_BaseDestructor
//   [ ] 0x1c37a0  CKInputIconFxData_Construct_2  [dead]
//   [ ] 0x1c3828  CKInputIconFxData_GetInfo
//   [ ] 0x1c3830  CKInputIconFxData_Destroy
//   [x] 0x1c3868  CKInputIconFxData_CreateArray
//   [x] 0x1c39c0  CKInputIconFxData_Create
//   [x] 0x1c3a70  CKInputIconFxData_Load
//   [ ] 0x1c3da0  CKInputIconFxData_DeletingDestructor
//   [ ] 0x1c3df8  CKInputIconFxData_Destructor
//   [ ] 0x1c3e38  CKInputIconFxData_MessageProc
//
//   [ ] 0x9ac708  CKInputIconFxData_IsKindOfClass  [inline]
//   [x] 0x9ac740  CKInputIconFxData_GetClassType  [inline]
//   [x] 0x9ac748  CKInputIconFxData_GetClassID  [inline]
#include "k2000/logic/fx/CKInputIconFxData.h"

#include "k2000/io/IKFile.h"

// 0x001c39c0 CKInputIconFxData_Create, the inlined constructor, in its store order.
CKInputIconFxData::CKInputIconFxData() {
    m_unk14 = 1.0f;
    m_unk1c = 1.0f;
    m_unk33 = 0;
    m_unk0c = -1;
    m_unk30 = 0;
    m_unk31 = 0;
    m_unk32 = 0;
    m_unk08 = -1;
    m_unk10 = 0;
    m_unk18 = 1.0f;
    m_unk20 = 1.0f;
    m_unk34 = 0;
    m_unk24 = 10.0f;  // 0x41200000
    m_unk28 = 40.0f;  // 0x42200000
    m_unk2c = 0;
    m_unk3c = 0;
    m_unk38 = 0.0f;
    m_pTexture = nullptr;
}

// 0x001c3a70 CKInputIconFxData_Load
int32_t CKInputIconFxData::Load(IKFile* file, int32_t type) {
    IKFxData::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadS32LE(file, &m_unk08);
    ReadS32LE(file, &m_unk0c);
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(&m_unk14), 2);  // one 8-byte read
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(&m_unk1c), 2);  // one 8-byte read
    ReadF32LE(file, &m_unk24);
    ReadF32LE(file, &m_unk28);
    ReadU32LE(file, &m_unk2c);
    ReadU32LEWords(file, &m_unk34, 3);  // one 12-byte read: +0x34, +0x38, +0x3c
    IKFile_ReadTextureRef(file, &m_pTexture, 1);
    ReadU8(file, &m_unk33);
    return 1;
}
