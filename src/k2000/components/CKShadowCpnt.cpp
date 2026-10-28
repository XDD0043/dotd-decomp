// CKShadowCpnt.cpp - reconstructed original translation unit 0x1fe788-0x1fee18 (GAME_TOC1, main_toc1), 15 functions, 13 live.
// Primary class: CKShadowCpnt  key 0x486  category Component  size 0x2c  vtable 0xb1ed88
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1fe788  CKShadowCpnt_Delete
//   [ ] 0x1fe7d8  CKShadowCpnt_RecursiveRegistration
//   [ ] 0x1fe7e0  CKShadowCpnt_SetFloat04_maybe
//   [ ] 0x1fe7e8  CKShadowCpnt_SetFloat08_maybe
//   [ ] 0x1fe7f0  RegisterCKShadowCpntClass
//   [ ] 0x1fe868  _GLOBAL__I_1fe868
//   [ ] 0x1fe878  CKShadowCpnt_SetByte1Clamped_maybe  [dead]
//   [ ] 0x1fe8d8  CKShadowCpnt_SetValue6AndPush_maybe  [dead]
//   [x] 0x1fe910  CKShadowCpnt_DeleteArray
//   [x] 0x1fe9b0  CKShadowCpnt_Create
//   [x] 0x1fe9e8  CKShadowCpnt_CreateArray
//   [ ] 0x1fea78  CKShadowCpnt_Save
//   [ ] 0x1fea80  CKShadowCpnt_Destroy
//   [x] 0x1fea88  CKShadowCpnt_Load
//   [ ] 0x1fee10  KStub_Nop_1fee10
//
//   [ ] 0x9b1180  CKShadowCpnt_IsKindOfClass  [inline]
//   [x] 0x9b11a8  CKShadowCpnt_GetClassType  [inline]
//   [x] 0x9b11b0  CKShadowCpnt_GetClassID  [inline]
//   [ ] 0x9b11b8  CKShadowCpnt_DeletingDestructor  [inline]
//   [ ] 0x9b1200  CKShadowCpnt_Destructor  [inline]
#include "k2000/components/CKShadowCpnt.h"

#include "k2000/io/IKFile.h"

// 0x001fea88 CKShadowCpnt_Load
int32_t CKShadowCpnt::Load(IKFile* file, int32_t type) {
    if (type == K_LEVEL_PLATEFORMS) {
        ReadF32LE(file, &m_fShadowLong);
        ReadF32LE(file, &m_fShadowWidth);
        ReadF32LE(file, &m_fShadowScale);
        ReadF32LE(file, &m_fShadowMinScale);
        ReadF32LE(file, &m_fShadowDistanceMax);
        ReadF32LE(file, &m_fShadowDistanceThreshold);
        ReadRaw(file, m_ShadowColor, 4);  // not swapped
        ReadF32LE(file, &m_fSpeedSmoothColor);
        ReadF32LE(file, &m_fSpeedSmoothNormal);
        ReadU8(file, &m_ui8Priority);
        ReadU8(file, &m_ui8IndexTexture);
        ReadU8(file, &m_bAlwaysVisible);
        ReadU8(file, &m_bSmoothNormal);
    }
    return 1;
}
