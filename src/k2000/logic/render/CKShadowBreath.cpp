// CKShadowBreath.cpp - reconstructed original translation unit 0x3d3fe8-0x3d7500 (GAME_TOC1, main_toc1), 26 functions, 26 live.
// Primary class: CKShadowBreath  key 0xa90c  category Logic  size 0x210  vtable 0xb24758
// Other owners: UpdateShadowBreathEffects (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x3d3fe8  CKShadowBreath_Delete
//   [ ] 0x3d4038  CKShadowBreath_GetAbilityId
//   [ ] 0x3d4040  CKShadowBreath_SelectSound_maybe
//   [ ] 0x3d4188  CKShadowBreath_ResetRuntime
//   [ ] 0x3d4258  CKShadowBreath_End
//   [ ] 0x3d42d0  CKShadowBreath_Start
//   [ ] 0x3d4308  CKShadowBreath_PostLoad
//   [ ] 0x3d4330  CKShadowBreath_RecursiveRegistration
//   [ ] 0x3d4358  CKShadowBreath_Destroy
//   [ ] 0x3d4380  CKShadowBreath_DeletingDestructor
//   [ ] 0x3d43c8  CKShadowBreath_Destructor
//   [ ] 0x3d43f8  CKShadowBreath_DestructBody
//   [x] 0x3d4428  CKShadowBreath_Construct
//   [ ] 0x3d4460  CKShadowBreath_Construct_2
//   [x] 0x3d4498  CKShadowBreath_DeleteArray
//   [ ] 0x3d4540  RegisterCKShadowBreathClass
//   [ ] 0x3d45c8  _GLOBAL__D_3d45c8
//   [ ] 0x3d45d8  _GLOBAL__I_3d45d8
//   [ ] 0x3d45e8  CKShadowBreath_GetEmitterPosition
//   [x] 0x3d4740  CKShadowBreath_Create
//   [x] 0x3d4798  CKShadowBreath_CreateArray
//   [ ] 0x3d4850  UpdateShadowBreathEffects
//   [ ] 0x3d5128  CKShadowBreath_ConfigureSparkNode_maybe
//   [x] 0x3d5518  CKShadowBreath_Load
//   [ ] 0x3d6038  CKShadowBreath_Save
//   [ ] 0x3d6b38  CKShadowBreath_SetFxActive
//
//   [ ] 0x9c07c0  CKShadowBreath_IsKindOfClass  [inline]
//   [x] 0x9c0810  CKShadowBreath_GetClassType  [inline]
//   [x] 0x9c0818  CKShadowBreath_GetClassID  [inline]
//   [ ] 0x9c0820  CKShadowBreath_StartEmitterFx  [inline]
#include "k2000/logic/render/CKShadowBreath.h"

#include "k2000/io/IKFile.h"

// 0x003d5518 CKShadowBreath_Load
int32_t CKShadowBreath::Load(IKFile* file, int32_t type) {
    CKBreathElement::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    IKFile_ReadRef(file, &m_unk1a0);
    IKFile_ReadRef(file, &m_unk1d4);
    IKFile_ReadRef(file, &m_unk1d8);
    IKFile_ReadRef(file, &m_unk1e0);
    IKFile_ReadRef(file, &m_unk1a8);
    IKFile_ReadRef(file, &m_unk1ac);
    IKFile_ReadRef(file, &m_unk1b0);
    for (uint32_t i = 0; i < 10; ++i) ReadU32LE(file, &m_unk178[i]);  // ten separate 4-byte reads
    IKFile_ReadRef(file, &m_unk1e4);
    IKFile_ReadRef(file, &m_unk1e8);
    IKFile_ReadRef(file, &m_unk1ec);
    for (uint32_t i = 0; i < 5; ++i) ReadU32LE(file, &m_unk1f0[i]);
    IKFile_ReadRef(file, &m_unk1b8);
    IKFile_ReadRef(file, &m_unk1bc);
    IKFile_ReadRef(file, &m_unk1c0);
    for (uint32_t i = 0; i < 3; ++i) ReadU32LE(file, &m_unk1c8[i]);
    return 1;
}
