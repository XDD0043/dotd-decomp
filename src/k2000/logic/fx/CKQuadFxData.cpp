// Reconstructed original translation unit: 0x1d0470-0x1d0978 (GAME_TOC1, main_toc1), 5 functions, 5 live.
// Primary class: CKQuadFxData  key 0x17cc  category Logic  size 0x28  vtable 0xb1d690
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1d0470  CKQuadFxData_GetNodeClassKey
//   [x] 0x1d0478  CKQuadFxData_Destroy
//   [x] 0x1d04b0  CKQuadFxData_RecursiveRegistration  (IKFxData's, nothing)
//   [x] 0x1d04d8  CKQuadFxData_Load
//   [ ] 0x1d0750  CKQuadFxData_Save
//
//   [x] 0x9ad038  CKQuadFxData_IsKindOfClass  [inline]
//   [x] 0x9ad070  CKQuadFxData_GetClassType  [inline]
//   [x] 0x9ad078  CKQuadFxData_GetClassID  [inline]
//   [ ] 0x9ad080  CKQuadFxData_Destructor  [inline]
//   [ ] 0x9ad0c0  CKQuadFxData_DeletingDestructor  [inline]
#include "k2000/logic/fx/CKQuadFxData.h"

#include "k2000/io/IKFile.h"

// 0x001d04d8 CKQuadFxData_Load: level files only (IKFxData's included): the texture (unresolved, one reference more),
// the size, the rotation speed, the two bytes (+0x25 first), the size jitter and the colour word (raw); no position.
int32_t CKQuadFxData::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    IKFxData::Load(file, K_LEVEL_PLATEFORMS);
    IKFile_ReadTextureRef(file, &m_pTexture, 0);
    if (m_pTexture != nullptr) TextureRef_AddRef(m_pTexture);  // the texture's refCount (+0x54) + 1
    ReadF32LE(file, &m_afSize[0]);
    ReadF32LE(file, &m_afSize[1]);
    ReadF32LE(file, &m_fRotationSpeed);
    ReadRaw(file, &m_i8RotationSign, 1);
    ReadRaw(file, &m_bJitterSize, 1);
    ReadF32LE(file, &m_fSizeJitter);
    ReadRaw(file, &m_color, 4);
    m_pPosition = nullptr;
    return 1;
}

// 0x001d0478 CKQuadFxData_Destroy
void CKQuadFxData::Destroy() {
    if (m_pTexture != nullptr) TextureRef_Release(m_pTexture);  // RwTextureDestroy
}
