// CKS08MenuElements.cpp - reconstructed original translation unit 0x54ad98-0x553bc8 (GAME_TOC1, main_toc1), 43 functions, 35 live.
// Primary class: CKS08MenuElements  key 0x84cc  category Logic  size 0x498  vtable 0xb2c550
// Other owners: Color (3)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x54ad98  CKS08MenuElements_Delete
//   [ ] 0x54ade8  FUN_0054ade8  [dead]
//   [ ] 0x54ae30  FUN_0054ae30  [dead]
//   [ ] 0x54aef8  FUN_0054aef8  [dead]
//   [ ] 0x54af08  FUN_0054af08  [dead]
//   [ ] 0x54af58  CKS08MenuElements_SetSelectionAndWidgetStates_maybe  [dead]
//   [ ] 0x54b040  CKS08MenuElements_ComputeElementRank_maybe
//   [ ] 0x54b160  CKS08MenuElements_UpdateUpgradePointsDisplay_maybe
//   [ ] 0x54b2e0  Color_ComputeFadeSpeed_maybe
//   [ ] 0x54b3b0  CKS08MenuElements_ResetPlayerVisualEffects_maybe
//   [ ] 0x54be80  CKS08MenuElements_Save
//   [ ] 0x54bea8  CKS08MenuElements_RecursiveRegistration
//   [x] 0x54c050  CKS08MenuElements_DeleteArray
//   [ ] 0x54c0f0  RegisterCKS08MenuElementsClass
//   [ ] 0x54c178  _GLOBAL__D_54c178
//   [ ] 0x54c188  _GLOBAL__I_54c188
//   [ ] 0x54c198  FUN_0054c198  [dead]
//   [ ] 0x54c288  CKS08MenuElements_Construct  [dead]
//   [ ] 0x54c360  CKS08MenuElements_Destroy
//   [ ] 0x54c490  CKS08MenuElements_SetTotalLevelGaugeTier_maybe
//   [ ] 0x54c6a8  CKS08MenuElements_Construct_2  [dead]
//   [x] 0x54c780  CKS08MenuElements_CreateArray
//   [x] 0x54c920  CKS08MenuElements_Create
//   [ ] 0x54ca48  CKS08MenuElements_RefreshElementTexts_maybe
//   [ ] 0x54d1c8  CKS08MenuElements_UpdateProgressIndicator_maybe
//   [ ] 0x54d6a8  CKS08MenuElements_GetTotalLevelUpText_maybe
//   [ ] 0x54d8f8  CKS08MenuElements_RefreshTotalLevelGauge_maybe
//   [ ] 0x54dd08  CKS08MenuElements_CheckElementLevelUp_maybe
//   [ ] 0x54e2d0  CKS08MenuElements_AnimateElementWheel_maybe
//   [ ] 0x54e648  CKS08MenuElements_TransferGemsStep_maybe
//   [ ] 0x54e940  CKS08MenuElements_OnItemEvent
//   [ ] 0x54ea08  Color_UpdateBlinkFade_maybe
//   [ ] 0x54eee8  CKS08MenuElements_UpdatePlayerVisualEffects_maybe
//   [ ] 0x550030  Color_StartBlinkFade_maybe
//   [ ] 0x5501d0  CKS08MenuElements_ToggleActiveDragon_maybe
//   [ ] 0x550610  CKS08MenuElements_HandleElementSelectInput
//   [ ] 0x550af8  CKS08MenuElements_OnStatePhase
//   [ ] 0x5513b8  CKS08MenuElements_Destructor_2
//   [x] 0x5514f0  CKS08MenuElements_Load
//   [ ] 0x551fd0  CKS08MenuElements_DeletingDestructor
//   [ ] 0x552108  CKS08MenuElements_Destructor
//   [ ] 0x552240  CKS08MenuElements_PlayLevelUpFeedback_maybe
//   [ ] 0x5538d0  CKS08MenuElements_MessageProc
//
//   [x] 0x9c9948  CKS08MenuElements_IsKindOfClass  [inline]
//   [x] 0x9c9988  CKS08MenuElements_GetClassType  [inline]
//   [x] 0x9c9990  CKS08MenuElements_GetClassID  [inline]
//   [x] 0x9c9998  CKS08MenuElements_vfB8  [inline]
//   [x] 0x9c99a0  CKS08MenuElements_vfE0  [inline]
//   [x] 0x9c99a8  CKS08MenuElements_vfC4  [inline]
//   [x] 0x9c99b0  CKS08MenuElements_vfC8  [inline]
//   [x] 0x9c99c0  CKS08MenuElements_vfCC  [inline]
//   [x] 0x9c99d0  CKS08MenuElements_vfBC  [inline]
//   [x] 0x9c99d8  CKS08MenuElements_vfC0  [inline]
//   [x] 0x9c99e8  CKS08MenuElements_GetWidgetSlotCount  [inline]
//   [x] 0x9c99f0  CKS08MenuElements_GetWidgetSlots  [inline]
//   [ ] 0x9c9a00  CKS08MenuElements_vfF0  [inline]
//   [ ] 0x9c9a08  CKS08MenuElements_vfF4  [inline]
#include "Spyro2008/logic/ui/CKS08MenuElements.h"

#include "k2000/io/IKFile.h"

// 0x005514f0 CKS08MenuElements_Load: no type test of its own.
int32_t CKS08MenuElements::Load(IKFile* file, int32_t type) {
    CKMenuBase114c::Load(file, type);
    m_unk32c = 0;
    m_unk240 = 0;
    for (float& value : m_afUnk25c) ReadF32LE(file, &value);
    ReadU8(file, &m_unk28c);
    ReadF32LE(file, &m_fUnk290);
    ReadF32LE(file, &m_fUnk294);
    for (uint32_t i = 8; i-- != 0;) IKFile_ReadTextureRef(file, &m_apTextures2ac[i], 1);
    IKFile_ReadRef(file, &m_pText2a0);
    IKFile_ReadRef(file, &m_pFlashFx);
    IKFile_ReadRef(file, &m_pQuake338);
    IKFile_ReadRef(file, &m_pQuakeUpdater33c);
    IKFile_ReadRef(file, &m_pQuake34c);
    IKFile_ReadRef(file, &m_pQuakeUpdater350);
    ReadRaw(file, &m_unk380, 4);
    ReadU32LE(file, &m_unk384);
    ReadU32LE(file, &m_unk388);
    ReadRaw(file, &m_unk3b8, 4);
    ReadF32LE(file, &m_fUnk3bc);
    ReadF32LE(file, &m_fUnk3c0);
    ReadRaw(file, &m_unk450, 4);
    ReadF32LE(file, &m_fUnk454);
    ReadF32LE(file, &m_fUnk458);
    IKFile_ReadRef(file, &m_pSound);
    IKFile_ReadRef(file, &m_pText2a4);
    for (uint32_t i = 24; i-- != 0;) IKFile_ReadTextureRef(file, &m_apTextures2cc[i], 1);
    ReadU32LE(file, &m_unk244);
    ReadU8(file, &m_unk488);
    ReadU8(file, &m_unk489);
    ReadF32LE(file, &m_fUnk48c);
    ReadRaw(file, &m_unk474, 4);
    ReadF32LE(file, &m_fUnk478);
    ReadF32LE(file, &m_fUnk47c);
    return 1;
}
