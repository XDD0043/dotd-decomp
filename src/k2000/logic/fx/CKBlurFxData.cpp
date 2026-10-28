// CKBlurFxData.cpp - reconstructed original translation unit 0x571348-0x571be0 (GAME_TOC2, main_toc2), 7 functions, 7 live.
// Primary class: CKBlurFxData  key 0x28c  category Logic  size ?  vtable 0xb2dd18
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x571348  CKBlurFxData_Destroy
//   [ ] 0x5713c0  CKBlurFxData_PostLoad
//   [ ] 0x5713e8  CKBlurFxData_RecursiveRegistration
//   [ ] 0x571460  CKBlurFxData_MessageProc
//   [ ] 0x5717d8  CKBlurFxData_GetInfo
//   [x] 0x5717e0  CKBlurFxData_Load
//   [ ] 0x5719e8  CKBlurFxData_Save
//
//   [ ] 0x9cac28  CKBlurFxData_IsKindOfClass  [inline]
//   [x] 0x9cac60  CKBlurFxData_GetClassType  [inline]
//   [x] 0x9cac68  CKBlurFxData_GetClassID  [inline]
//   [ ] 0x9cac70  CKBlurFxData_Destructor  [inline]
//   [ ] 0x9cacb0  CKBlurFxData_DeletingDestructor  [inline]
#include "k2000/logic/fx/CKBlurFxData.h"

#include "k2000/io/IKFile.h"

// 0x005717e0 CKBlurFxData_Load
int32_t CKBlurFxData::Load(IKFile* file, int32_t type) {
    IKFxData::Load(file, type);  // through TocBridge_IKFxData_Load
    if (type == K_LEVEL_PLATEFORMS) {
        IKFile_ReadRef(file, &m_unk08);
        ReadU8(file, &m_unk0c);
        ReadU8(file, &m_unk18);
        ReadF32LE(file, &m_unk10);
        m_unk14 = new Key[m_unk18];
        ReadU32LEWords(file, reinterpret_cast<uint32_t*>(m_unk14), static_cast<uint32_t>(m_unk18) * 2);
    }
    m_unk1c = 0;
    return 1;
}
