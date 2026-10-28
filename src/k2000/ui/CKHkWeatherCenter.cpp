// CKHkWeatherCenter.cpp - reconstructed original translation unit 0x5acb48-0x5ae528 (GAME_TOC2, main_toc2), 29 functions, 23 live.
// Primary owner: CKHkWeatherCenter (not a registered class)
// Other owners: RegisterCKHkWeatherCenterClass (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x5acb48  CKHkWeatherCenter_Destroy
//   [x] 0x5acb98  CKHkWeatherCenter_Construct  [dead]
//   [ ] 0x5acbe8  CKHkWeatherCenter_Construct_2  [dead]
//   [ ] 0x5acc38  RegisterCKHkWeatherCenterClass
//   [ ] 0x5accb0  _GLOBAL__I_5accb0
//   [ ] 0x5accc0  CKHkWeatherCenter_ApplyPreset_maybe
//   [ ] 0x5acf10  CKHkWeatherCenter_ClearReferences
//   [x] 0x5acfb0  CKHkWeatherCenter_DestroyArray
//   [ ] 0x5ad050  CKHkWeatherCenter_PushPreset_maybe  [dead]
//   [ ] 0x5ad1e8  CKHkWeatherCenter_SetBasePresetByObject_maybe  [dead]
//   [ ] 0x5ad2b8  CKHkWeatherCenter_RemovePreset_maybe  [dead]
//   [x] 0x5ad440  CKHkWeatherCenter_Create
//   [x] 0x5ad4b0  CKHkWeatherCenter_CreateArray
//   [ ] 0x5ad578  CKHkWeatherCenter_Destructor_2  [dead]
//   [ ] 0x5ad5d8  CKHkWeatherCenter_DeletingDestructor
//   [ ] 0x5ad660  CKHkWeatherCenter_Destructor
//   [ ] 0x5ad6c0  CKHkWeatherCenter_PostLoad
//   [ ] 0x5ad708  CKHkWeatherCenter_Save
//   [ ] 0x5ad730  CKHkWeatherCenter_LevelReset
//   [ ] 0x5ad758  CKHkWeatherCenter_HandleMessage
//   [ ] 0x5ad878  CKHkWeatherCenter_ResolveTriggerProperty
//   [x] 0x5ad8f0  CKHkWeatherCenter_Load
//   [ ] 0x5add18  CKHkWeatherCenter_vf50
//   [ ] 0x5add20  CKHkWeatherCenter_vf70
//   [ ] 0x5add28  CKHkWeatherCenter_vf78
//   [ ] 0x5add30  CKHkWeatherCenter_OnLevelExit_maybe
//   [ ] 0x5adda8  CKHkWeatherCenter_ResetToInitialState_maybe
//   [ ] 0x5adea8  CKHkWeatherCenter_UpdateCloudUVScroll_maybe
//   [ ] 0x5ae200  CKHkWeatherCenter_Update
//
//   [ ] 0x9cbed8  CKHkWeatherCenter_IsKindOf  [inline]
//   [ ] 0x9cbf20  CKHkWeatherCenter_GetClassGroup  [inline]
//   [ ] 0x9cbf28  CKHkWeatherCenter_GetClassId  [inline]
//   [ ] 0x9cbf30  CKHkWeatherCenter_GetTriggerPropC8  [inline]
#include "k2000/ui/CKHkWeatherCenter.h"

#include "k2000/io/IKFile.h"

// 0x005ad8f0 CKHkWeatherCenter_Load
int32_t CKHkWeatherCenter::Load(IKFile* file, int32_t type) {
    IKHook::Load(file, type);  // through TocBridge_CKHook_Load
    if (type != K_LEVEL_PLATEFORMS) return 1;
    IKFile_ReadRef(file, &m_pBackgroundSkyNode);
    IKFile_ReadRef(file, &m_pBackgroundCloudsNode);
    IKFile_ReadRef(file, &m_pBackgroundSunNode);
    IKFile_ReadRef(file, &m_pCloudsNodeFx);
    ReadU8(file, &m_ui8NbPreset);
    m_apWeatherPreset = new IKSerializable*[m_ui8NbPreset];  // OperatorNewArray(count * 4)
    IKFile_ReadObjectRefArray(file, m_apWeatherPreset, m_ui8NbPreset);
    IKFile_ReadRef(file, &m_pCurrentWeatherPreset);
    ReadU8(file, &m_ui8StartPreset);
    m_ui8NextPreset = 0;
    m_fInterpolSpeed = 1.0f;  // TOC 0xc1f244 (0x3f800000)
    m_ui8CurrentPreset = 0;
    m_fInterpolRatio = 1.0f;
    // The asked-preset list: every node back to the pool, then one node (preset 0) for this hook.
    for (PresetNode* node = m_lAskedPreset; node != nullptr;) {
        PresetNode* next = node->m_pNext;
        delete node;  // back to the FreeListPool at 0x00ceaa20 in the original
        node = next;
    }
    m_lAskedPreset = nullptr;
    PresetNode* node = new PresetNode;  // FreeListPool at 0x00ceaa20 (FreeListPool_Grow when empty)
    node->m_pNext = m_lAskedPreset;
    m_lAskedPreset = node;
    node->m_pOwner = this;
    node->m_ui8Preset = 0;
    return 1;
}
