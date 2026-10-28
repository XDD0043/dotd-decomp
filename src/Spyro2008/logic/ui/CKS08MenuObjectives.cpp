// CKS08MenuObjectives.cpp - reconstructed original translation unit 0x5582b8-0x55aec0 (GAME_TOC2, main_toc2), 30 functions, 22 live.
// Primary class: CKS08MenuObjectives  key 0x878c  category Logic  size ?  vtable 0xb2ca78
// Other owners: Menu (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x5582b8  CKS08MenuObjectives_Delete
//   [ ] 0x558308  CKS08MenuObjectives_ClearObjectiveList_maybe  [dead]
//   [ ] 0x558540  CKS08MenuObjectives_SetTitleTextByIndex_maybe  [dead]
//   [ ] 0x5585c0  CKS08MenuObjectives_SetEntryFontAndScale_maybe
//   [ ] 0x5587c0  Menu_PlayConfirmSound_maybe
//   [ ] 0x558820  CKS08MenuObjectives_SetEntryText_maybe
//   [ ] 0x558988  CKS08MenuObjectives_SetEntryTextVariantC_maybe  [dead]
//   [ ] 0x558aa8  CKS08MenuObjectives_SetEntryTextVariantB_maybe  [dead]
//   [ ] 0x558bc8  CKS08MenuObjectives_SetEntryTextVariantA_maybe  [dead]
//   [ ] 0x558ce8  CKS08MenuObjectives_BuildObjectiveList_maybe
//   [ ] 0x558e30  CKS08MenuObjectives_RecursiveRegistration
//   [ ] 0x558ed0  CKS08MenuObjectives_Destroy
//   [x] 0x558f18  CKS08MenuObjectives_DeleteArray
//   [ ] 0x558fc0  RegisterCKS08MenuObjectivesClass
//   [ ] 0x559048  _GLOBAL__D_559048
//   [ ] 0x559058  _GLOBAL__I_559058
//   [ ] 0x559068  CKS08MenuObjectives_OnItemEvent
//   [ ] 0x5590b0  CKS08MenuObjectives_SetSelectionAndWidgetStates_maybe  [dead]
//   [ ] 0x559198  CKS08MenuObjectives_Construct  [dead]
//   [ ] 0x559240  CKS08MenuObjectives_Construct_2  [dead]
//   [x] 0x5592e8  CKS08MenuObjectives_CreateArray
//   [x] 0x559438  CKS08MenuObjectives_Create
//   [ ] 0x559528  CKS08MenuObjectives_RefreshPage_maybe
//   [ ] 0x559a10  CKS08MenuObjectives_HandleInput_maybe
//   [ ] 0x559c60  CKS08MenuObjectives_OnMenuState_maybe
//   [x] 0x55a128  CKS08MenuObjectives_Load
//   [ ] 0x55a660  CKS08MenuObjectives_Save
//   [ ] 0x55ab18  CKS08MenuObjectives_Destructor
//   [ ] 0x55ac50  CKS08MenuObjectives_Destructor_2
//   [ ] 0x55ad88  CKS08MenuObjectives_DeletingDestructor
//
//   [x] 0x9c9d00  CKS08MenuObjectives_IsKindOfClass  [inline]
//   [x] 0x9c9d40  CKS08MenuObjectives_GetClassType  [inline]
//   [x] 0x9c9d48  CKS08MenuObjectives_GetClassID  [inline]
//   [x] 0x9c9d50  CKS08MenuObjectives_vfB8  [inline]
//   [x] 0x9c9d58  CKS08MenuObjectives_vfE0  [inline]
//   [x] 0x9c9d60  CKS08MenuObjectives_vfC4  [inline]
//   [x] 0x9c9d68  CKS08MenuObjectives_vfC8  [inline]
//   [x] 0x9c9d78  CKS08MenuObjectives_vfCC  [inline]
//   [x] 0x9c9d88  CKS08MenuObjectives_vfBC  [inline]
//   [x] 0x9c9d90  CKS08MenuObjectives_vfC0  [inline]
//   [x] 0x9c9da0  CKS08MenuObjectives_GetWidgetSlotCount  [inline]
//   [x] 0x9c9da8  CKS08MenuObjectives_GetWidgetSlots  [inline]
//   [ ] 0x9c9db8  CKS08MenuObjectives_vfF0  [inline]
//   [ ] 0x9c9dc0  CKS08MenuObjectives_vfF4  [inline]
//   [ ] 0x9c9dc8  CKS08MenuObjectives_vfE4  [inline]
#include "Spyro2008/logic/ui/CKS08MenuObjectives.h"

#include "k2000/io/IKFile.h"

// 0x0055a128 CKS08MenuObjectives_Load
int32_t CKS08MenuObjectives::Load(IKFile* file, int32_t type) {
    CKMenuBase114c::Load(file, type);
    IKFile_ReadTextureRef(file, &m_pTexture, 1);
    for (float& value : m_afUnk1e0) ReadF32LE(file, &value);
    ReadRaw(file, &m_unk1f8, 4);
    ReadRaw(file, &m_unk1fc, 4);
    for (float& value : m_afUnk200) ReadF32LE(file, &value);
    if (type == K_LEVEL_PLATEFORMS) m_unk1dc = 0;
    IKFile_ReadRef(file, &m_pText);
    IKFile_ReadRef(file, &m_pSound);
    return 1;
}
