// CKPointLightFxData.cpp - reconstructed original translation unit 0x1cf310-0x1cfb08 (GAME_TOC1, main_toc1), 17 functions, 17 live.
// Primary class: CKPointLightFxData  key 0xaa8c  category Logic  size 0x38  vtable 0xb1d580
// Other owners: CKPointLightNodeFx (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1cf310  CKPointLightFxData_Delete
//   [x] 0x1cf360  CKPointLightFxData_GetNodeClassKey
//   [ ] 0x1cf370  CKPointLightFxData_PostLoad
//   [ ] 0x1cf3a8  RegisterCKPointLightFxDataClass
//   [ ] 0x1cf420  _GLOBAL__I_1cf420
//   [ ] 0x1cf430  CKPointLightNodeFx_EvaluateColorLooped_maybe
//   [ ] 0x1cf4d0  CKPointLightFxData_Save
//   [ ] 0x1cf4f8  CKPointLightFxData_RecursiveRegistration
//   [x] 0x1cf5a0  CKPointLightFxData_DeleteArray
//   [x] 0x1cf648  CKPointLightFxData_CreateArray
//   [ ] 0x1cf750  CKPointLightFxData_GetInfo
//   [ ] 0x1cf758  CKPointLightFxData_MessageProc
//   [ ] 0x1cf788  CKPointLightFxData_Destroy
//   [x] 0x1cf790  CKPointLightFxData_Create
//   [ ] 0x1cf810  CKPointLightFxData_EvaluateRadiusLooped_maybe
//   [ ] 0x1cf898  CKPointLightFxData_EvaluateIntensityLooped_maybe
//   [x] 0x1cf920  CKPointLightFxData_Load
//
//   [ ] 0x9ace40  CKPointLightFxData_IsKindOfClass  [inline]
//   [x] 0x9ace80  CKPointLightFxData_GetClassType  [inline]
//   [x] 0x9ace88  CKPointLightFxData_GetClassID  [inline]
//   [ ] 0x9ace90  CKPointLightFxData_DeletingDestructor  [inline]
//   [ ] 0x9acf08  CKPointLightFxData_Destructor  [inline]
#include "k2000/logic/render/CKPointLightFxData.h"

#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"

// 0x001cf790 CKPointLightFxData_Create, the inlined constructor, in its store order.
CKPointLightFxData::CKPointLightFxData() {
    m_colorKeys.m_pBlock = nullptr;
    m_colorKeys.m_ui32NbElt = 20;
    m_colorKeys.m_ui32NbUsedElt = 0;
    m_colorKeys.m_pBlock = static_cast<CurveKey*>(Mem_AllocAligned16(20 * static_cast<uint32_t>(sizeof(CurveKey))));
}

// 0x001cf920 CKPointLightFxData_Load
int32_t CKPointLightFxData::Load(IKFile* file, int32_t type) {
    IKFxData::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    IKFile_ReadRef(file, &m_unk08);
    IKFile_ReadRef(file, &m_unk0c);
    CurveKeys_Load(&m_colorKeys, file);
    ReadF32LE(file, &m_unk1c);
    ReadF32LE(file, &m_unk20);
    return 1;
}
