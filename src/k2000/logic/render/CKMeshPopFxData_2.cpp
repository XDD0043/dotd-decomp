// CKMeshPopFxData_2.cpp - reconstructed original translation unit 0x1c8060-0x1c9338 (GAME_TOC1, main_toc1), 8 functions, 8 live.
// Primary class: CKMeshPopFxData  key 0xa28c  category Logic  size 0x64  vtable 0xb1d360
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1c8060  CKMeshPopFxData_GetNodeClassKey
//   [ ] 0x1c8070  CKMeshPopFxData_PostLoad
//   [ ] 0x1c8090  CKMeshPopFxData_Save
//   [ ] 0x1c80b8  CKMeshPopFxData_RecursiveRegistration
//   [ ] 0x1c8160  CKMeshPopFxData_GetInfo
//   [ ] 0x1c8168  CKMeshPopFxData_Destroy
//   [x] 0x1c8170  CKMeshPopFxData_Load
//   [ ] 0x1c8700  CKMeshPopFxData_MessageProc
//
//   [ ] 0x9acae8  CKMeshPopFxData_IsKindOfClass  [inline]
//   [x] 0x9acb28  CKMeshPopFxData_GetClassType  [inline]
//   [x] 0x9acb30  CKMeshPopFxData_GetClassID  [inline]
//   [ ] 0x9acb38  CKMeshPopFxData_DeletingDestructor  [inline]
//   [ ] 0x9acb90  CKMeshPopFxData_Destructor  [inline]
#include "k2000/logic/render/CKMeshPopFxData.h"

#include "k2000/io/IKFile.h"

// 0x001c8170 CKMeshPopFxData_Load
int32_t CKMeshPopFxData::Load(IKFile* file, int32_t type) {
    IKFxData::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        IKFile_ReadRef(file, &m_unk10);
        ReadU8(file, &m_unk18);
        ReadU8(file, &m_unk19);
        ReadF32LE(file, &m_unk1c);
        ReadF32LE(file, &m_unk20);
        ReadF32LE(file, &m_unk24);
        ReadF32LE(file, &m_unk2c);
        ReadF32LE(file, &m_unk30);
        ReadF32LE(file, &m_unk34);
        ReadF32LE(file, &m_unk40);
        ReadS32LE(file, &m_unk38);
        ReadS32LE(file, &m_unk3c);
    }
    // The rest is read whatever the type.
    ReadU8(file, &m_unk44);
    ReadF32LE(file, &m_unk48);
    IKFile_ReadRef(file, &m_unk14);
    ReadF32LE(file, &m_unk28);
    ReadU8(file, &m_unk4c);
    ReadF32LE(file, &m_unk50);
    ReadU32LEWords(file, m_unk54, 3);  // one 12-byte read
    return 1;
}
