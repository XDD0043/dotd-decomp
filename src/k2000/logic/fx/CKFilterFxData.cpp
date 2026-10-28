// CKFilterFxData.cpp - reconstructed original translation unit 0x1b8778-0x1b9358 (GAME_TOC1, main_toc1), 10 functions, 9 live.
// Primary class: CKFilterFxData  key 0x1a0c  category Logic  size 0x28  vtable 0xb1cae0
// Other owners: CKFilterNode2dFx (2)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1b8778  CKFilterFxData_GetNodeClassKey
//   [ ] 0x1b8780  CKFilterFxData_RecursiveRegistration
//   [ ] 0x1b87a8  CKFilterFxData_GetInfo
//   [ ] 0x1b87b0  CKFilterFxData_Destroy
//   [x] 0x1b87e8  CKFilterFxData_Load
//   [ ] 0x1b89e8  CKFilterFxData_Save
//   [ ] 0x1b8bd8  CKFilterFxData_MessageProc
//   [ ] 0x1b92f8  CKFilterNode2dFx_Delete
//   [ ] 0x1b9348  CKFilterNode2dFx_Destroy
//   [ ] 0x1b9350  KStub_Nop_1b9350  [dead]
//
//   [ ] 0x9abd68  CKFilterFxData_IsKindOfClass  [inline]
//   [x] 0x9abda0  CKFilterFxData_GetClassType  [inline]
//   [x] 0x9abda8  CKFilterFxData_GetClassID  [inline]
//   [ ] 0x9abdb0  CKFilterFxData_DeletingDestructor  [inline]
//   [ ] 0x9abe08  CKFilterFxData_Destructor  [inline]
#include "k2000/logic/fx/CKFilterFxData.h"

#include "k2000/io/IKFile.h"

// 0x001b87e8 CKFilterFxData_Load
int32_t CKFilterFxData::Load(IKFile* file, int32_t type) {
    if (type == K_LEVEL_PLATEFORMS) {
        IKFxData::Load(file, K_LEVEL_PLATEFORMS);
        ReadF32LE(file, &m_fColorSpeed);
        ReadRaw(file, m_FinalColor, 4);
        ReadRaw(file, m_StartColor, 4);
        IKFile_ReadTextureRef(file, &m_pTexture, 1);
        uint8_t flag = 0;
        ReadU8(file, &flag);
        m_baFlags = static_cast<uint8_t>((m_baFlags & 0xfc) | (flag << 1));
        ReadU8(file, &m_ui8BlendMod);
        ReadF32LE(file, &m_unk08);
    }
    m_unk20 = 0;  // every type
    return 1;
}
