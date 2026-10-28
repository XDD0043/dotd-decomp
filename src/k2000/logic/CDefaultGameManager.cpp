// CDefaultGameManager.cpp - reconstructed original translation unit 0x130f8-0x1a0d8 (GAME_TOC1, main_toc1), 151 functions, 128 live.
// Primary class: CDefaultGameManager  key 0xc4c  category Logic  size 0x298  vtable 0xb13550
// Other owners: KBaseBCC (45), GameManager (4), KBase2 (4), KBase2FE (4), CGameManager (2), BootLoad (2), Engine (2)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x130f8  CDefaultGameManager_LevelResetImpl
//   [ ] 0x13288  CDefaultGameManager_RecursiveRegistration
//   [x] 0x132b0  IKGameManager_FindNonRecreableInstances
//   [x] 0x13408  CDefaultGameManager_RequestSave_maybe
//   [ ] 0x13430  KStub_Return0_13430  [dead]
//   [ ] 0x13438  CDefaultGameManager_IsSaveDataBusy_maybe
//   [x] 0x13448  SaveFlow_OnMsgDialogClosed_maybe
//   [ ] 0x13490  CDefaultGameManager_Restart
//   [x] 0x134e0  CGameManager_BasePause_maybe
//   [x] 0x134e8  CGameManager_BaseResume_maybe
//   [ ] 0x134f0  CDefaultGameManager_SectorLoaded
//   [ ] 0x134f8  CDefaultGameManager_SectorUnload
//   [ ] 0x13500  CDefaultGameManager_vf198
//   [ ] 0x13508  CDefaultGameManager_vf19C
//   [ ] 0x13510  CDefaultGameManager_vf1A0
//   [ ] 0x13518  IKGameManager_vf1A4
//   [ ] 0x13520  IKGameManager_vf1A8
//   [ ] 0x13528  CDefaultGameManager_vf1AC
//   [x] 0x13530  IKGameManager_IsMotionSensorEnabled
//   [x] 0x13558  IKGameManager_HaveOptionsChanged
//   [x] 0x137b0  CDefaultGameManager_vf1E4
//   [x] 0x137b8  CDefaultGameManager_GetSkipVideoPromptText_maybe
//   [ ] 0x137e8  CDefaultGameManager_vf138
//   [x] 0x137f8  CDefaultGameManager_TogglePlayerVibration_maybe
//   [x] 0x138e8  CDefaultGameManager_ToggleVibrationBothPlayers_maybe
//   [x] 0x13920  IKGameManager_ApplyOptions_maybe
//   [x] 0x13c00  IKGameManager_ApplyCurrentOptions
//   [x] 0x13c18  IKGameManager_ApplyEditedOptions
//   [x] 0x13c30  IKGameManager_CommitEditedOptions
//   [x] 0x13cc8  IKGameManager_CopyOptionsToEditBlock
//   [x] 0x13d60  IKGameManager_SwitchToFocusedHeroCamera_maybe
//   [x] 0x13e08  IKGameManager_OnLevelExit
//   [ ] 0x13e48  CDefaultGameManager_GetCurrentLevelNumber_maybe
//   [x] 0x13e78  CDefaultGameManager_OnLevelStart_maybe
//   [ ] 0x13fb8  CDefaultGameManager_SaveFlow_PostAndWaitDone_maybe  [dead]
//   [ ] 0x140a8  IKGameManager_UpdateSaveGameFlow_maybe
//   [ ] 0x143b8  CDefaultGameManager_LoadSelectedSlotObjects_maybe  [dead]
//   [ ] 0x144a8  CDefaultGameManager_SaveDialogCallback_NotSaveDeviceVf10_maybe
//   [x] 0x14508  CDefaultGameManager_PostLoadImpl
//   [ ] 0x145c8  CDefaultGameManager_UnloadSectorAndClearSlot_maybe  [dead]
//   [x] 0x14618  CDefaultGameManager_RecacheLocStrings_maybe_2
//   [x] 0x14660  BootLoad_SetGameLoopActive_maybe
//   [ ] 0x14698  BootLoad_InitSaveData_maybe
//   [ ] 0x146f8  FUN_000146f8  [dead]
//   [ ] 0x14708  FUN_00014708  [dead]
//   [ ] 0x14738  FUN_00014738  [dead]
//   [x] 0x14750  CDefaultGameManager_InitDefaultOptions_maybe
//   [ ] 0x14870  CDefaultGameManager_SaveFlowA_State4_maybe
//   [ ] 0x14958  CDefaultGameManager_SaveFlowA_State2_maybe
//   [ ] 0x14a08  CDefaultGameManager_SaveFlowB_State5_maybe
//   [ ] 0x14af0  CDefaultGameManager_SaveFlowB_State3_maybe
//   [ ] 0x14ba0  CDefaultGameManager_SaveFlowB_State1_maybe
//   [ ] 0x14c68  CDefaultGameManager_SaveDialogCallback_NotSaveDeviceVfC_maybe
//   [ ] 0x14cc8  CDefaultGameManager_ReleaseGameData_maybe
//   [x] 0x14d68  CDefaultGameManager_RequestGameExit_maybe
//   [ ] 0x14d98  Engine_PopGamePause_maybe
//   [ ] 0x14dc8  Engine_PushGamePause_maybe
//   [x] 0x14df8  CKS08GameManager_CommitRequestedLevel_maybe
//   [ ] 0x14e38  GameManager_PollPlayer2Reconnected_maybe
//   [x] 0x14ec0  CDefaultGameManager_GetCannotSkipPromptText_maybe
//   [x] 0x14ef0  CDefaultGameManager_GetSkipCinematicPromptText_maybe
//   [x] 0x14f20  CDefaultGameManager_SetSaveRequestFlag_maybe
//   [x] 0x14f60  IKGameManager_SetFlag64Bit2_maybe
//   [x] 0x14f78  IKGameManager_RefreshOptionsChangedFlag
//   [ ] 0x14fc0  FUN_00014fc0  [dead]
//   [ ] 0x14fd8  IKGameManager_GetCurrentSpawnPoint_maybe
//   [x] 0x14fe8  IKGameManager_vfD8
//   [ ] 0x15090  ApplySoundVolumesToVideoManager_maybe
//   [ ] 0x15100  ZeroVideoManagerVolumes_maybe  [dead]
//   [x] 0x15160  LoadDefaultAndSystemLanguageLocFiles_maybe
//   [x] 0x15208  GameManager_ReloadLocalizedData_maybe
//   [ ] 0x15240  FindVideoModeMatchingAspect_maybe
//   [x] 0x153d8  CDefaultGameManager_vf108
//   [ ] 0x15428  CDefaultGameManager_SaveSelectedSlotObjects_maybe  [dead]
//   [ ] 0x155b0  CDefaultGameManager_SaveFlowA_State3_maybe
//   [x] 0x156d8  CDefaultGameManager_ClearReferencesImpl
//   [ ] 0x15700  CDefaultGameManager_SaveImpl
//   [ ] 0x157e8  CDefaultGameManager_SaveFlowA_State0_maybe
//   [x] 0x159a8  CDefaultGameManager_ResetProgressImpl_maybe
//   [x] 0x15ba0  CDefaultGameManager_InitImpl
//   [ ] 0x15e48  CDefaultGameManager_SaveFlowB_State4_maybe
//   [ ] 0x16018  CDefaultGameManager_SaveFlowB_State0_maybe
//   [x] 0x162a0  CDefaultGameManager_RecacheLocStrings_maybe
//   [x] 0x162e8  CKS08GameManager_UnloadCurrentLevel_maybe
//   [ ] 0x16388  FUN_00016388  [dead]
//   [ ] 0x16468  IKGameManager_ApplyCurrentOptions_maybe  [dead]
//   [x] 0x16480  GameManager_RevertOptions_maybe
//   [x] 0x16500  GameManager_BackupOptions_maybe
//   [x] 0x16618  IKGameManager_UpdateAutoLoadFlow_maybe
//   [x] 0x167d0  IKGameManager_UpdateLoadGameFlow_maybe
//   [x] 0x16bb8  IKGameManager_RestoreDefaultOptions_maybe
//   [ ] 0x16c88  CDefaultGameManager_Save
//   [x] 0x16d78  CDefaultGameManager_LoadImpl
//   [ ] 0x170a8  CDefaultGameManager_Load
//   [x] 0x170d0  CDefaultGameManager_ResetRuntimeImpl
//   [ ] 0x171e0  CDefaultGameManager_PostLoad
//   [x] 0x172b0  CDefaultGameManager_vf1D4
//   [x] 0x17320  IKGameManager_ToggleAutosaveOption_maybe
//   [x] 0x17340  IKGameManager_ResetScreenOffsetOption
//   [x] 0x17368  IKGameManager_ResetBrightnessOption
//   [x] 0x17388  IKGameManager_ToggleSubtitlesOption_maybe
//   [x] 0x173a8  IKGameManager_ResetSoundAndAspectOptions_maybe
//   [x] 0x173e8  IKGameManager_ApplyEditedOptions_2
//   [x] 0x17400  IKGameManager_CycleLanguageOption
//   [x] 0x17498  IKGameManager_DecScreenOffsetYOption_maybe
//   [x] 0x174b8  IKGameManager_DecScreenOffsetXOption_maybe
//   [x] 0x174d8  IKGameManager_ApplyEditedOptions_3
//   [x] 0x174f0  IKGameManager_TogglePerPlayerOption10C
//   [x] 0x17540  IKGameManager_ToggleMotionSensorOption
//   [x] 0x17588  IKGameManager_IncScreenOffsetXOption_maybe
//   [x] 0x175a8  IKGameManager_ApplyEditedOptions_4
//   [x] 0x175c0  IKGameManager_ToggleAspectRatioOption
//   [x] 0x17628  IKGameManager_StepBrightnessOption
//   [x] 0x17680  IKGameManager_IncScreenOffsetYOption_maybe
//   [x] 0x176a0  IKGameManager_CycleSoundOutputOption
//   [x] 0x17708  IKGameManager_TogglePerPlayerOption10A
//   [x] 0x17758  IKGameManager_ToggleOptionF1
//   [x] 0x17780  IKGameManager_ToggleMotionSensorBothPlayersOption
//   [x] 0x177f8  IKGameManager_TogglePerPlayerOption10CBothPlayers
//   [x] 0x17870  IKGameManager_TogglePerPlayerOption10ABothPlayers
//   [x] 0x178e8  IKGameManager_UpdateSaveDataRequests_maybe
//   [ ] 0x17c38  CDefaultGameManager_SaveFlowA_State1_maybe
//   [ ] 0x17e80  CDefaultGameManager_SaveFlowB_State2_maybe
//   [ ] 0x18040  CDefaultGameManager_RunSaveFlowAStateMachine_maybe  [dead]
//   [ ] 0x184e0  CDefaultGameManager_StepSaveFlowA_maybe  [dead]
//   [ ] 0x18650  CDefaultGameManager_RunSaveCheckStateMachine_maybe
//   [ ] 0x18a80  CDefaultGameManager_UpdateSaveDataFlow_maybe
//   [ ] 0x18e20  CDefaultGameManager_RunSaveFlowBStateMachine_maybe  [dead]
//   [ ] 0x195a8  CDefaultGameManager_StepSaveFlowB_Variant1_maybe  [dead]
//   [ ] 0x19688  CDefaultGameManager_StepSaveFlowB_Variant2_maybe  [dead]
//   [ ] 0x19770  FUN_00019770  [dead]
//   [ ] 0x197e0  KStub_Return1_197e0  [dead]
//   [ ] 0x19808  FUN_00019808  [dead]
//   [ ] 0x198c8  IKHook_vf9C
//   [ ] 0x198d8  IKHook_Save
//   [ ] 0x19900  CKHook_Load
//   [ ] 0x19a90  IKHook_vfBC
//   [ ] 0x19ab8  IKHook_LevelReset
//   [ ] 0x19b30  FUN_00019b30  [dead]
//   [ ] 0x19ba8  KStub_Return1_19ba8  [dead]
//   [ ] 0x19bd0  FUN_00019bd0  [dead]
//   [ ] 0x19c90  KStub_Return1_19c90
//   [ ] 0x19c98  KObject_LevelResetIfNotNull_maybe
//   [ ] 0x19ce8  KStub_Return1_19ce8
//   [ ] 0x19cf0  IKLife_Load
//   [x] 0x19e60  IKLife_SectorLoaded
//   [x] 0x19ed8  IKLife_SectorUnload
//   [ ] 0x19f68  IKLife_PostLoad
//   [ ] 0x19f90  CKS08Player_Destroy
//   [ ] 0x19f98  CKDefaultPlayer_SaveImpl
//   [ ] 0x1a0d0  CKS08Player_PostLoad
//
//   [ ] 0x990d30  IKLife_IsKindOf  [inline]
//   [ ] 0x990dd8  IKLife_Destructor  [inline]
//   [ ] 0x990e70  IKLife_DeletingDestructor  [inline]
//   [ ] 0x990eb8  IKError_IsKindOf  [inline]
//   [ ] 0x990ed0  IKError_vf28  [inline]
//   [ ] 0x991258  CDefaultGameManager_vf94  [inline]
//   [ ] 0x991260  CDefaultGameManager_vf98  [inline]
//   [ ] 0x991268  IKGameManager_vfA4  [inline]
//   [ ] 0x991270  CDefaultGameManager_vfC0  [inline]
//   [x] 0x991278  CDefaultGameManager_vfC4  [inline]
//   [ ] 0x991280  CDefaultGameManager_vfC8  [inline]
//   [ ] 0x991288  CDefaultGameManager_vfDC  [inline]
//   [ ] 0x991290  CDefaultGameManager_vfE0  [inline]
//   [ ] 0x991298  IKGameManager_vfE4  [inline]
//   [ ] 0x9912a0  CDefaultGameManager_vfE8  [inline]
//   [ ] 0x9912a8  IKGameManager_vfEC  [inline]
//   [ ] 0x9912b0  CDefaultGameManager_vfF0  [inline]
//   [ ] 0x9912b8  CDefaultGameManager_vfF4  [inline]
//   [ ] 0x9912c0  CDefaultGameManager_vfF8  [inline]
//   [ ] 0x9912c8  CDefaultGameManager_vfFC  [inline]
//   [ ] 0x9912d0  CDefaultGameManager_vf100  [inline]
//   [ ] 0x9912d8  IKGameManager_vf110  [inline]
//   [ ] 0x9912e0  IKGameManager_vf114  [inline]
//   [ ] 0x9912e8  IKGameManager_vf11C  [inline]
//   [ ] 0x9912f0  CDefaultGameManager_vf13C  [inline]
//   [ ] 0x9912f8  CDefaultGameManager_vf140  [inline]
//   [ ] 0x991320  CDefaultGameManager_vf144  [inline]
//   [ ] 0x991328  CDefaultGameManager_vf14C  [inline]
//   [ ] 0x991330  CDefaultGameManager_vf150  [inline]
//   [ ] 0x991338  CDefaultGameManager_vf154  [inline]
//   [ ] 0x991340  CDefaultGameManager_vf158  [inline]
//   [ ] 0x991348  CDefaultGameManager_vf15C  [inline]
//   [x] 0x991350  CDefaultGameManager_vf160  [inline]
//   [x] 0x991358  CDefaultGameManager_vf164  [inline]
//   [ ] 0x991360  CDefaultGameManager_vf168  [inline]
//   [ ] 0x991368  CDefaultGameManager_vf16C  [inline]
//   [ ] 0x991370  IKGameManager_vf170  [inline]
//   [ ] 0x991378  IKGameManager_vf174  [inline]
//   [ ] 0x991380  IKGameManager_vf178  [inline]
//   [ ] 0x991388  IKGameManager_vf17C  [inline]
//   [ ] 0x991390  CDefaultGameManager_vf180  [inline]
//   [ ] 0x991398  CDefaultGameManager_vf184  [inline]
//   [ ] 0x9913a0  CDefaultGameManager_vf188  [inline]
//   [ ] 0x9913a8  CDefaultGameManager_vf18C  [inline]
//   [ ] 0x9913b0  CDefaultGameManager_vf190  [inline]
//   [ ] 0x9913b8  CDefaultGameManager_vf1B0  [inline]
//   [ ] 0x991400  IKGameManager_vf1B4  [inline]
//   [ ] 0x991428  CDefaultGameManager_vf1B8  [inline]
//   [ ] 0x991470  IKGameManager_vf1BC  [inline]
//   [ ] 0x991498  IKGameManager_vf1C4  [inline]
//   [ ] 0x9914a0  IKGameManager_vf1C8  [inline]
//   [ ] 0x9914a8  IKGameManager_vf1CC  [inline]
//   [ ] 0x9914b0  CDefaultGameManager_vf1E8  [inline]
//   [ ] 0x9914b8  CDefaultGameManager_vf1EC  [inline]
//   [ ] 0x9914c0  CDefaultGameManager_vf1F0  [inline]
//   [ ] 0x9914c8  CDefaultGameManager_vf1F4  [inline]
//   [ ] 0x9914d0  CDefaultGameManager_vf1F8  [inline]
//   [ ] 0x9914d8  IKGameManager_vf1FC  [inline]
//   [ ] 0x9914e0  IKGameManager_vf200  [inline]
//   [ ] 0x9914e8  IKGameManager_vf204  [inline]
//   [ ] 0x9914f0  CDefaultGameManager_vf208  [inline]
//   [ ] 0x9914f8  CDefaultGameManager_vf20C  [inline]
//   [ ] 0x991500  CDefaultGameManager_vf210  [inline]
//   [ ] 0x991508  CDefaultGameManager_vf218  [inline]
//   [ ] 0x991510  CDefaultGameManager_vf21C  [inline]
//   [ ] 0x991518  CDefaultGameManager_vf228  [inline]
//   [ ] 0x991520  CDefaultGameManager_vf22C  [inline]
//   [ ] 0x991528  CDefaultGameManager_vf234  [inline]
//   [ ] 0x991530  CDefaultGameManager_vf238  [inline]
//   [ ] 0x991538  IKGameManager_vf23C  [inline]
//   [ ] 0x991540  CDefaultGameManager_vf240  [inline]
//   [ ] 0x991548  IKGameManager_vf244  [inline]
//   [ ] 0x991550  IKGameManager_vf248  [inline]
//   [ ] 0x991558  IKGameManager_vf24C  [inline]
//   [ ] 0x991560  IKGameManager_vf250  [inline]
//   [ ] 0x991708  IKGameManager_vf220  [inline]
//   [ ] 0x991738  IKGameManager_vf118  [inline]
//   [ ] 0x991790  IKBoundingVolume_Destructor  [inline]
//   [ ] 0x991860  IKBoundingVolume_DeletingDestructor  [inline]
//   [ ] 0x9918a8  IKGameManager_IsKindOf  [inline]
//   [ ] 0x991e20  IKGameManager_Destructor  [inline]
//   [ ] 0x9925a0  IKGameManager_DeletingDestructor  [inline]
//   [ ] 0x992640  KStub_Nop_992640  [inline]
//   [ ] 0x992648  KStub_Nop_992648  [inline]
//   [ ] 0x992650  KStub_Nop_992650  [inline]
//   [ ] 0x992658  KStub_Nop_992658  [inline]
//   [ ] 0x992660  KStub_Nop_992660  [inline]
//   [ ] 0x992668  KStub_Nop_992668  [inline]
//   [ ] 0x992670  KStub_Return0_992670  [inline]
//   [ ] 0x992678  KStub_Nop_992678  [inline]
//   [ ] 0x992680  KStub_Nop_992680  [inline]
//   [ ] 0x992690  CKHook_Load  [inline]
//   [ ] 0x992698  IKHook_IsKindOf  [inline]
//   [ ] 0x9926d0  IKHook_Save_2  [inline]
//   [ ] 0x9926f8  IKHook_LevelReset_2  [inline]
//   [ ] 0x992770  IKHook_DeletingDestructor  [inline]
//   [ ] 0x9927b8  IKHook_Destructor  [inline]
//   [ ] 0x992998  CDefaultGameManager_IsKindOfClass  [inline]
//   [ ] 0x9929d0  CDefaultGameManager_GetClassType  [inline]
//   [ ] 0x9929d8  CDefaultGameManager_GetClassID  [inline]
//   [ ] 0x9929e0  CDefaultGameManager_GetSerializationFlags  [inline]
//   [ ] 0x9929e8  CDefaultGameManager_vfBC  [inline]
//   [ ] 0x9929f0  CDefaultGameManager_vfCC  [inline]
//   [ ] 0x9929f8  CDefaultGameManager_vfD0  [inline]
//   [ ] 0x992a00  CDefaultGameManager_vf254  [inline]
//   [ ] 0x992a08  CDefaultGameManager_vfD4  [inline]
//   [ ] 0x992a10  CDefaultGameManager_vf120  [inline]
//   [ ] 0x992a18  CDefaultGameManager_vf124  [inline]
//   [x] 0x992a20  CDefaultGameManager_vf128  [inline]
//   [ ] 0x992a28  CDefaultGameManager_vf12C  [inline]
//   [ ] 0x992a30  CDefaultGameManager_vf130  [inline]
//   [ ] 0x992a38  CDefaultGameManager_vf134  [inline]
//   [ ] 0x992a40  CDefaultGameManager_vf1D8  [inline]
//   [ ] 0x992a48  CDefaultGameManager_vf1DC  [inline]
//   [ ] 0x992a50  CDefaultGameManager_vf1E0  [inline]
//   [ ] 0x992a58  CDefaultGameManager_vf214  [inline]
//   [ ] 0x992a60  CDefaultGameManager_DeletingDestructor  [inline]
//   [ ] 0x992b00  CDefaultGameManager_Destructor  [inline]
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/cameras/CKSrvCamera.h"
#include "k2000/components/CKLocTextAccessor.h"
#include "k2000/logic/CKCinematicScene.h"
#include "k2000/services/CKSrvCinematic.h"

#include <cstring>
#include "k2000/graphical/system/IKVideo.h"
#include "k2000/logic/CKCoreManager.h"
#include "k2000/logic/CKGameLevel.h"
#include "k2000/logic/CKGameSpawnPoint.h"
#include "k2000/misc/IKGameStructure.h"
#include "k2000/logic/IKPlayer.h"

#include "k2000/logic/CKLevel.h"
#include "k2000/logic/io/CKLoadingManager.h"
#include "k2000/misc/CKGameLoop.h"
#include "k2000/misc/Engine.h"
#include "k2000/core/Stub.h"
#include "k2000/io/LoadRequests.h"
#include "k2000/io/SaveData.h"

// 0x00014660 BootLoad_SetGameLoopActive_maybe
void BootLoad_SetGameLoopActive(CDefaultGameManager* /*manager*/) { g_pEngine->m_gameLoop->SetAppActive(1); }

// 0x00014fe8 IKGameManager_vfD8: level -1 = the boot loading video (+0x84); otherwise the video (+0x84) of
// the game structure's level whose number (+0x1c) matches, searched from the last; null when none does.
IKVideo* CDefaultGameManager::GetLoadingVideo(int32_t level) {
    if (level == -1) return static_cast<IKVideo*>(m_unk84);
    IKGameStructure* structure = static_cast<IKGameStructure*>(m_gameStructure);
    uint32_t count = structure->m_vpStages.m_ui32NbUsedElt;  // CKDefaultGameStructure_CountLevels(gs, null) 0x413c8
    while (count != 0) {
        --count;
        CKGameLevel* stage = structure->m_vpStages.m_pBlock[count];
        if (stage->m_i32StageIndex == level) return static_cast<IKVideo*>(stage->m_pUnk84);
    }
    return nullptr;
}

// 0x00014df8 CKS08GameManager_CommitRequestedLevel_maybe: the requested level becomes the current one.
void CDefaultGameManager::CommitRequestedLevel() {
    m_currentLevel = m_requestedLevel;
    m_requestedLevel = -1;
    g_pEngine->m_level->ClearLoadingSector();
}

// 0x000162e8 CKS08GameManager_UnloadCurrentLevel_maybe
void CDefaultGameManager::UnloadCurrentLevel() {
    if (m_currentLevel != -1) {
        g_pEngine->m_objectDatabase->UnloadSector(-1);
        m_currentLevel = -1;
        g_pEngine->m_level->ResetSectorState();
        return;
    }
    g_pEngine->m_level->ResetSectorState();
}

#include "k2000/io/IKFile.h"
#include "k2000/logic/io/CKLoadingManager.h"
#include "k2000/misc/ClassManager.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/misc/IKGameStructure.h"

// 0x00015ba0 CDefaultGameManager_InitImpl
void CDefaultGameManager::InitImpl() {
    m_unk274 = 9;
    m_flags64 &= ~1u;
    m_currentLevel = -1;
    m_requestedLevel = -1;
    m_requestedSector = -2;
    for (IKSerializable*& reference : m_unk04) reference = nullptr;
    m_unk288 = -1;
    m_level = g_pEngine->m_level;
    const uint32_t playerKey = GetPlayerClassKey();
    m_playerArray = static_cast<IKSerializable*>(g_pEngine->m_classManager->CreateObjectArray(
        static_cast<int32_t>(playerKey & 0x3f), (playerKey >> 6) & 0x7ff, 7, &m_playerStride));
    for (IKSerializable*& player : m_players) player = nullptr;
    // KMemBuffer_Init/Resize (+0x1c) and the save-state memory stream (KFileSystem_OpenFile device 3
    // -> +0x3c): STUB(save data).
    m_gameStructure = static_cast<IKSerializable*>(ClassRegistry_CreateObjectByKey(GetGameStructureClassKey()));
    static_cast<IKGameStructure*>(m_gameStructure)->SetGameManager(this);  // vt+0x70
    m_unk84 = nullptr;
    std::memset(m_unk8c, 0, sizeof(m_unk8c));  // 0x002461c0 Uuid_Clear
    m_unk9c = -1;
    std::memset(m_unkA0, 0, sizeof(m_unkA0));
    m_unkB0 = -1;
    m_unk89 = 0;
    m_bSaveRequestPosted = 0;
    // The global byte at TOC1 -0x1fc5*4 = 0: STUB(C1.6), its readers are not ported.
    m_unk270 = 1;
    m_flags64 &= ~0x3eu;
}

// 0x000132b0 IKGameManager_FindNonRecreableInstances
uint8_t CDefaultGameManager::FindNonRecreableInstances(int32_t category, uint32_t id, uint32_t count, void* out) {
    if (category != kCategoryLogic) return 0;
    const uint32_t key = id * 0x40 + kCategoryLogic;
    if (key == GetPlayerClassKey()) {
        IKSerializable** array = *static_cast<IKSerializable***>(out);
        for (uint32_t i = 0; i < count; ++i) {
            array[i] = reinterpret_cast<IKSerializable*>(reinterpret_cast<uint8_t*>(m_playerArray) + m_playerStride * i);
        }
        return 1;
    }
    if (key == GetGameStructureClassKey()) {
        *static_cast<IKSerializable**>(out) = m_gameStructure;
        return 1;
    }
    return 0;
}

// 0x00016d78 CDefaultGameManager_LoadImpl. GAME (mode 1) gives the requested level and the players; a
// level (mode 0) five references, two trigger starters and one more reference; a save restore (mode 6)
// +0x28c and a raw block.
void CDefaultGameManager::LoadImpl(IKFile* stream, int32_t mode) {
    if (mode == 1) {
        ReadS32LE(stream, &m_requestedLevel);
        m_unk28c = -1;
        IKFile_ReadRef(stream, &m_unk84);
        IKFile_ReadObjectRefArray(stream, m_players, 7);
        return;
    }
    if (mode == 6) {
        ReadS32LE(stream, &m_unk28c);
        ReadRaw(stream, &m_currentOptions, 0x34);  // the PS3 words as they are (save data)
        return;
    }
    if (mode != 0) return;
    IKFile_ReadObjectRefArray(stream, m_unk04, 5);
    m_unk70.Load(stream, 0);
    m_unk78.Load(stream, 0);
    IKFile_ReadRef(stream, &m_unk144);
}

#include "k2000/logic/ui/CLocManager.h"

class CKCoreManager;
void Engine_UnloadLocalizedData(CKCoreManager* coreManager);  // 0x0001c838 (CKCoreManager.cpp)

// 0x00015160 LoadDefaultAndSystemLanguageLocFiles_maybe
void LoadDefaultAndSystemLanguageLocFiles(CDefaultGameManager* /*manager*/) {
    g_pEngine->m_objectDatabase->LoadLocFile(0, K_GAME_LOCALIZATION, -1);
    const uint32_t language = g_pEngine->m_locManager->GetSystemLanguageIndex();
    if (language != 0) {
        Engine_UnloadLocalizedData(g_pEngine->m_coreManager);
        g_pEngine->m_objectDatabase->LoadLocFile(static_cast<int32_t>(language), K_GAME_LOCALIZATION, -1);
        g_pEngine->m_locManager->m_languageIndex = static_cast<uint16_t>(language);
    }
}

// 0x00015208 GameManager_ReloadLocalizedData_maybe
void CDefaultGameManager::ReloadLocalizedData() { Engine_ReloadLocalizedData(g_pEngine->m_coreManager, 0); }


// 0x00014508 CDefaultGameManager_PostLoadImpl: a level (0) runs its two trigger lists' PostLoad
// (TriggerEventList_PostLoad_maybe 0x236330 returns 1); a save restore (5) the game structure's vt+0x60
// with the first player (STUB(C1.6)).
void CDefaultGameManager::PostLoadImpl(int32_t type) {
    m_unk80 = (m_unk80 & 0x00ffffffu);  // the byte at +0x80
    if (type == 5) DOTD_STUB_ONCE("CDefaultGameManager_PostLoadImpl: save restore (C1.6)");
}

// 0x000153d8 CDefaultGameManager_vf108
// 0x00992a18 CDefaultGameManager_vf124: the static vector at 0x00c50d64 (four zero words in the image).
const float* CDefaultGameManager::GetFocusedHeroNodePosition() {
    static const float kZeroVector[4] = {0.0f, 0.0f, 0.0f, 0.0f};
    return kZeroVector;
}

// 0x00992a20 CDefaultGameManager_vf128 / 0x00992a30 CDefaultGameManager_vf130: the same static vector.
const float* CDefaultGameManager::GetFocusedHeroPosition() { return GetFocusedHeroNodePosition(); }
const float* CDefaultGameManager::GetFocusedHeroMoveVector() { return CDefaultGameManager::GetFocusedHeroNodePosition(); }

uint8_t CDefaultGameManager::Vf108() {
    const uint32_t flags = m_flags64;
    if ((flags & 2) != 0 || (flags & 4) != 0 || (flags & 8) != 0 || (flags & 0x10) != 0) return 1;
    return static_cast<uint8_t>((flags >> 5) & 1);
}

// 0x00016618 IKGameManager_UpdateAutoLoadFlow_maybe
int32_t CDefaultGameManager::UpdateAutoLoadFlow(uint8_t* done) {
    SaveDataRequest& request = g_pEngine->m_gameLoop->m_saveDataRequest;
    if (m_bSaveRequestPosted == 0) {
        Vf23C();
        request.Post(SaveDataRequest::kListAutoLoad);
        m_bSaveRequestPosted = 1;
        return 0;
    }
    if (request.CheckDone() == 0) return 0;
    if (g_saveDataResult == 0) {
        ApplyOptions(&m_currentOptions, 1);
        m_editedOptions = m_currentOptions;
    } else {
        m_unk28c = -1;
    }
    m_bSaveRequestPosted = 0;
    *done = 1;
    return 1;
}

// 0x000170d0 CDefaultGameManager_ResetRuntimeImpl: when player 0 has the current level saved (bit `level`
// of its +0x04, levels below 32), the level's saved objects restored from the save-state stream; then
// +0x80 = 1, the game structure's game state applied to the level (vt+0x5c) and its modules' trigger
// domains refreshed (CKDefaultGameStructure_RefreshModuleTriggerDomains_maybe).
void CDefaultGameManager::ResetRuntimeImpl() {
    const uint32_t level = static_cast<uint32_t>(m_currentLevel);
    if (level != 0xffffffffu && level < 0x20 &&
        ((1u << level) & static_cast<IKPlayer*>(m_players[0])->m_baLevelSaved) != 0) {
        // STUB(save data): the save-state stream (+0x3c) seeks to level * the slot size (0x00c40710; vt+0x2c)
        // and CKLoadingManager_LoadSavedObjects_maybe (0x2a7c8) reads it in mode 4. No saved level exists
        // until a save is loaded.
        DOTD_STUB_ONCE("CDefaultGameManager_ResetRuntimeImpl: the level's saved objects (save data)");
    }
    IKGameStructure* structure = static_cast<IKGameStructure*>(m_gameStructure);
    m_unk80 = (m_unk80 & 0x00ffffffu) | 0x01000000u;  // the byte at +0x80
    if (structure != nullptr) {
        structure->ApplyGameStateToLevel();  // vt+0x5c
        structure->RefreshModuleTriggerDomains();
    }
}

// 0x000159a8 CDefaultGameManager_ResetProgressImpl_maybe (XXL2 IKGameManager::BasicNewGame)
void CDefaultGameManager::BasicNewGame() {
    std::memset(m_unk8c, 0, sizeof(m_unk8c));  // 0x002461c0 Uuid_Clear
    m_unk9c = -1;
    for (uint32_t i = 1; i <= 5; ++i) static_cast<IKPlayer*>(m_players[i])->InitializeNewGame();  // vt+0x54
    static_cast<IKPlayer*>(m_players[0])->InitializeNewGame();
    static_cast<IKPlayer*>(m_players[6])->InitializeNewGame();
    // memset(the save-state buffer (KMemBuffer +0x1c, its data +0x20), 0, the slot size * the slot count
    // (TOC1 -0x7ec8 / -0x7ed4)). STUB(save data): CDefaultGameManager_InitImpl does not allocate the buffer
    // yet, so there is nothing to clear.
    if (m_unk1c.m_unk04 != 0) DOTD_STUB_ONCE("CDefaultGameManager_ResetProgressImpl_maybe: save-state buffer (save data)");
}

// 0x00014d68 CDefaultGameManager_RequestGameExit_maybe
void CDefaultGameManager::RequestGameExit() { g_pEngine->m_gameLoop->RequestExit(); }

// 0x000172b0 CDefaultGameManager_vf1D4
void CDefaultGameManager::ResetEditedOptions() {
    InitDefaultOptions(0);  // vt+0x1d0
    ApplyOptions(&m_editedOptions, 0);
}

#include "k2000/logic/ui/CKLocText.h"
#include "platform/cell/l10n.h"
#include "platform/cell/msgdialog.h"

namespace {
// 0x00c50e1c: the save flows' system dialog: 0 none, 1 open, 2 YES, 3 NO, 4 escape.
int32_t s_saveFlowDialogState = 0;

// 0x00013448 SaveFlow_OnMsgDialogClosed_maybe (the dialog callback, OPD 0x00b35598)
void SaveFlow_OnMsgDialogClosed(int32_t button, void* /*userData*/) {
    if (button == 2) s_saveFlowDialogState = 3;
    else if (button == 3) s_saveFlowDialogState = 4;
    else if (button == 1) s_saveFlowDialogState = 2;
}

// 0x00035d28 LocString_GetText (CKLocText_2.cpp; the local copy TextData.cpp also keeps): a single space
// (0x00c2966e) while the loc manager has no localised data.
const uint16_t* LocTextString(const CKLocText* text) {
    static const uint16_t kSpace[] = {' ', 0};
    if (g_pEngine->m_locManager->m_bGameLocalizedDataValid == 0) return kSpace;
    return text->m_pText;
}
}  // namespace

// 0x000167d0 IKGameManager_UpdateLoadGameFlow_maybe
int32_t CDefaultGameManager::UpdateLoadGameFlow(uint8_t* done) {
    SaveDataRequest& request = g_pEngine->m_gameLoop->m_saveDataRequest;
    if (m_bSaveRequestPosted == 0) {
        Vf23C();
        request.Post(SaveDataRequest::kListLoad);
        m_bSaveRequestPosted = 1;
        return 0;
    }
    if (request.CheckDone() == 0) return 0;
    if (g_saveDataResult == 0) {
        // Player 6 (the loaded one) into player 0 (vt+0x50). STUB(save data): no save loads yet.
        DOTD_STUB_ONCE("IKGameManager_UpdateLoadGameFlow_maybe: player vt+0x50 (save data)");
        Vf240(0);
        ApplyOptions(&m_currentOptions, 1);
        m_editedOptions = m_currentOptions;
    } else if (g_saveDataResult == 1) {
        Vf240(1);
    } else {
        // No (readable) save data: the system dialog with text 0x169 (YES/NO, no cancel).
        if (s_saveFlowDialogState == 0) {
            const uint16_t* text = LocTextString(g_pEngine->m_locManager->GetText(0x169));
            size_t length = 0;
            while (text[length] != 0) ++length;  // Wcs_Length
            size_t utf8Length = 0;
            size_t sourceLength = length;
            UCS2stoUTF8s(text, &sourceLength, nullptr, &utf8Length);
            uint8_t* utf8 = new uint8_t[utf8Length + 1];
            std::memset(utf8, 0, utf8Length + 1);
            sourceLength = length;
            UCS2stoUTF8s(text, &sourceLength, utf8, &utf8Length);
            cellMsgDialogOpen2(0x90, reinterpret_cast<const char*>(utf8), &SaveFlow_OnMsgDialogClosed, nullptr, nullptr);
            delete[] utf8;
            s_saveFlowDialogState = 1;
            return 1;
        }
        if (s_saveFlowDialogState == 1) return 1;
        if (static_cast<uint32_t>(s_saveFlowDialogState - 3) < 2) *done = 1;  // NO or escape: the flow ends
        m_bSaveRequestPosted = 0;  // YES: the request again
        s_saveFlowDialogState = 0;
        return 1;
    }
    m_bSaveRequestPosted = 0;
    *done = 1;
    return 1;
}

// 0x000178e8 IKGameManager_UpdateSaveDataRequests_maybe: player 1 active with two players; then the
// first pending flow: 2 save game, 4 load game, 8 the options restored, 0x20 the auto-load, 0x10 a delete
// then a save. A finished flow with more than one player activates player 1 again.
void CDefaultGameManager::UpdateSaveDataRequests() {
    uint8_t done = 0;
    SetPlayerActive(1, GetPlayerCount() == 2 ? 1 : 0);
    const uint32_t flags = m_flags64;
    if ((flags & 2) != 0) {
        DOTD_STUB_ONCE("IKGameManager_UpdateSaveGameFlow_maybe (C1.6)");  // 0x140a8; done: flags &= ~3
    } else if ((flags & 4) != 0) {
        UpdateLoadGameFlow(&done);
        if (done == 0) return;
        m_flags64 &= ~7u;  // (flags >> 3) << 3: bits 0..2
    } else if ((flags & 8) != 0) {
        m_currentOptions = m_editedOptions;
        ApplyOptions(&m_currentOptions, 1);
        m_flags64 &= ~8u;
    } else if ((flags & 0x20) != 0) {
        UpdateAutoLoadFlow(&done);
        if (done == 0) return;
        m_flags64 &= ~0x20u;
    } else if ((flags & 0x10) != 0) {
        SaveDataRequest& request = g_pEngine->m_gameLoop->m_saveDataRequest;
        if (m_bSaveRequestPosted == 0) {
            request.Post(SaveDataRequest::kDelete);
            m_bSaveRequestPosted = 1;
            return;
        }
        if (request.CheckDone() == 0) return;
        m_flags64 = (m_flags64 & ~2u) | 2;
        m_bSaveRequestPosted = 0;
        done = 1;
        m_flags64 &= ~0x10u;
    }
    if (done != 0 && GetPlayerCount() > 1) SetPlayerActive(1, 1);
}

// ==== C1.6: the options ===========================================================================
#include "k2000/cameras/CameraContext.h"
#include "k2000/graphical/ui/CManager2d.h"
#include "k2000/managers/CKGraphic.h"
#include "k2000/managers/CKInput.h"
#include "k2000/managers/CKSoundManager.h"
#include "k2000/services/CKSrvSekensor.h"
#include "platform/cell/videoout.h"
#include "crt/ppc_ops.h"

namespace {
// 0x00a6f380 (TOC1 -0x7ef0): the options' sound output index -> the output mode, then (+0x14) the
// aspect ratios by index.
const int32_t kSoundOutputModes[5] = {0, 1, 3, 4, 5};
const float kAspectRatios[2] = {0x1.555556p+0f, 0x1.c71c72p+0f};  // 4/3 (0x3faaaaab), 16/9 (0x3fe38e39)

// The output mode back to its option index (ApplyOptions and InitDefaultOptions inline this); -1 for a
// mode without one (the index is then left as it is).
int32_t SoundOutputIndex(int32_t mode) {
    switch (mode) {
    case 5: return 4;
    case 4: return 3;
    case 3: return 2;
    case 1: return 1;
    case 0: return 0;
    default: return -1;
    }
}
}  // namespace

// 0x00013530 IKGameManager_IsMotionSensorEnabled (the current options)
uint8_t CDefaultGameManager::IsMotionSensorEnabled(int32_t player) {
    return player == 0 ? m_currentOptions.m_abMotionSensor[0] : m_currentOptions.m_abMotionSensor[1];
}

// 0x00013558 IKGameManager_HaveOptionsChanged: any field of the edited options differs from the current
// ones (the floats compared as floats, the bytes and words as integers).
uint32_t CDefaultGameManager::HaveOptionsChanged() {
    const SGameOptions& a = m_currentOptions;
    const SGameOptions& b = m_editedOptions;
    const bool changed = a.m_ui32Language != b.m_ui32Language || a.m_bSubtitles != b.m_bSubtitles ||
                         a.m_unk05 != b.m_unk05 || a.m_ui32SoundOutput != b.m_ui32SoundOutput ||
                         a.m_ui32AspectRatio != b.m_ui32AspectRatio || a.m_afVolumes[0] != b.m_afVolumes[0] ||
                         a.m_afVolumes[1] != b.m_afVolumes[1] || a.m_afVolumes[2] != b.m_afVolumes[2] ||
                         a.m_abVibration[0] != b.m_abVibration[0] || a.m_abVibration[1] != b.m_abVibration[1] ||
                         a.m_abUnk1E[0] != b.m_abUnk1E[0] || a.m_abUnk1E[1] != b.m_abUnk1E[1] ||
                         a.m_abUnk20[0] != b.m_abUnk20[0] || a.m_abUnk20[1] != b.m_abUnk20[1] ||
                         a.m_i32ScreenOffsetX != b.m_i32ScreenOffsetX || a.m_i32ScreenOffsetY != b.m_i32ScreenOffsetY ||
                         a.m_bAutosave != b.m_bAutosave || a.m_abMotionSensor[0] != b.m_abMotionSensor[0] ||
                         a.m_abMotionSensor[1] != b.m_abMotionSensor[1] || a.m_ui32Brightness != b.m_ui32Brightness;
    return changed ? 1u : 0u;
}

// 0x000137f8 CDefaultGameManager_TogglePlayerVibration_maybe: the edited vibration flag of player 0 or 1
// toggled; turned on, the pad rumbles a quarter of a second (motor 1 at 0xff), turned off it stops.
void CDefaultGameManager::TogglePlayerVibration(int32_t player) {
    if (player != 0 && player != 1) return;
    const uint8_t was = m_editedOptions.m_abVibration[player];
    m_editedOptions.m_abVibration[player] = static_cast<uint8_t>(was ^ 1);
    if (was == 0) {
        g_pEngine->m_input->AddRumbleRequest(0x1p-2f, this, static_cast<int8_t>(player), static_cast<uint8_t>(player), 1, 0xff);
        return;
    }
    g_pEngine->m_input->StopVibration(this, static_cast<int8_t>(player));
}

// 0x000138e8 CDefaultGameManager_ToggleVibrationBothPlayers_maybe
void CDefaultGameManager::ToggleVibrationBothPlayers() {
    TogglePlayerVibration(0);
    TogglePlayerVibration(1);
}

// 0x00013920 IKGameManager_ApplyOptions_maybe: an options block made effective. A language other than the
// loaded one is requested (+0x290: GameLoop's stop reason 4, mode 3 reloads the GLC/LLC); the subtitles,
// the volumes, (current only) the pads' vibration flags read back, the sound output (its index read back),
// the screen offset (read back), the game's hook (vt+0x1c4), the aspect, the gamma from the brightness, the
// motion sensors.
void CDefaultGameManager::ApplyOptions(SGameOptions* options, uint8_t current) {
    if (g_pEngine->m_locManager->m_languageIndex != options->m_ui32Language)
        m_unk290 = static_cast<int32_t>(options->m_ui32Language);
    static_cast<CKSrvSekensor*>(g_pEngine->m_srvSekensor)->SetSubtitlesEnabled(options->m_bSubtitles);
    CKSoundManager_SetVolumes(0x1p+0f, options->m_afVolumes[2], options->m_afVolumes[1], options->m_afVolumes[0],
                              g_pEngine->m_soundManager);  // TOC1 -0x7ef4: 1.0
    if (current != 0) {
        CKInput* input = g_pEngine->m_input;
        input->SetVibrationEnabled(0, options->m_abVibration[0]);
        input->SetVibrationEnabled(1, options->m_abVibration[1]);
        options->m_abVibration[0] = input->GetVibrationEnabled(0);
        options->m_abVibration[1] = input->GetVibrationEnabled(1);
    }
    CKSoundOutput* output = g_pEngine->m_soundManager->m_pOutput;
    SoundOutput_SetOutputMode(output, kSoundOutputModes[options->m_ui32SoundOutput]);
    const int32_t index = SoundOutputIndex(SoundOutput_GetOutputMode(g_pEngine->m_soundManager->m_pOutput));
    if (index >= 0) options->m_ui32SoundOutput = static_cast<uint32_t>(index);
    CKGraphic* graphic = g_pEngine->m_graphic;
    graphic->SetScreenOffset(options->m_i32ScreenOffsetX, options->m_i32ScreenOffsetY);
    g_pEngine->m_graphic->GetScreenOffset(&options->m_i32ScreenOffsetX, &options->m_i32ScreenOffsetY);
    ApplyGameOptions(options, current);  // vt+0x1c4
    Camera_SetFovAndAspectFromRaster(kAspectRatios[options->m_ui32AspectRatio],
                                     static_cast<CameraContext*>(g_pEngine->m_cameraContext));
    // fcfid of the unsigned word, frsp, then fdivs and fmadds (TOC1 -0x7eec 10.0, -0x7ee8 -0.4, -0x7ee4 1.2),
    // clamped to [0.8 (-0x7ee0), 1.2].
    const float brightness = static_cast<float>(static_cast<double>(options->m_ui32Brightness));
    float gamma = ppc::fmadds(brightness / 0x1.4p+3f, -0x1.99999cp-2f, 0x1.333334p+0f);
    if (gamma <= 0x1.99999ap-1f) gamma = 0x1.99999ap-1f;
    else if (gamma >= 0x1.333334p+0f) gamma = 0x1.333334p+0f;
    cellVideoOutSetGamma(0, gamma);
    g_pEngine->m_input->SetMotionSensorEnabled(0, options->m_abMotionSensor[0]);
    g_pEngine->m_input->SetMotionSensorEnabled(1, options->m_abMotionSensor[1]);
}

// 0x00013c00 IKGameManager_ApplyCurrentOptions
void CDefaultGameManager::ApplyCurrentOptions() { ApplyOptions(&m_currentOptions, 1); }
// 0x00013c18 IKGameManager_ApplyEditedOptions
void CDefaultGameManager::ApplyEditedOptions() { ApplyOptions(&m_editedOptions, 0); }

// 0x00013c30 IKGameManager_CommitEditedOptions: the edited options become the current ones.
void CDefaultGameManager::CommitEditedOptions() { m_currentOptions = m_editedOptions; }
// 0x00013cc8 IKGameManager_CopyOptionsToEditBlock
void CDefaultGameManager::CopyOptionsToEditBlock() { m_editedOptions = m_currentOptions; }

// 0x00014618 CDefaultGameManager_RecacheLocStrings_maybe_2 (GameLoop mode 3 after the reload): the 2D
// manager's TRC copies, the language request cleared.
void CDefaultGameManager::RecacheLocStringsAfterReload() {
    CManager2d_CacheLocStrings(g_pEngine->m_manager2d);
    m_unk290 = -1;
}

// 0x00014750 CDefaultGameManager_InitDefaultOptions_maybe: the defaults into the edited options: the
// system language (withLanguage), no subtitles, +0x05 on, the sound output of the output's default mode,
// 4:3, the volumes at 1.0 (TOC1 -0x7ef4), vibration on, brightness 5, autosave on.
void CDefaultGameManager::InitDefaultOptions(int32_t withLanguage) {
    SGameOptions& options = m_editedOptions;
    if (withLanguage != 0) options.m_ui32Language = g_pEngine->m_locManager->GetSystemLanguageIndex();
    options.m_bSubtitles = 0;
    options.m_unk05 = 1;
    options.m_ui32AspectRatio = 0;
    options.m_ui32SoundOutput = 0;
    const int32_t index = SoundOutputIndex(KStub_Return0_114508(g_pEngine->m_soundManager->m_pOutput));
    if (index >= 0) options.m_ui32SoundOutput = static_cast<uint32_t>(index);
    options.m_afVolumes[2] = 0x1p+0f;
    options.m_afVolumes[0] = 0x1p+0f;
    options.m_afVolumes[1] = 0x1p+0f;
    options.m_abUnk20[1] = 0;
    options.m_ui32Brightness = 5;
    options.m_bAutosave = 1;
    options.m_abMotionSensor[1] = 0;
    options.m_abVibration[0] = 1;
    options.m_abVibration[1] = 1;
    options.m_abUnk1E[0] = 0;
    options.m_abUnk1E[1] = 0;
    options.m_abUnk20[0] = 0;
    options.m_i32ScreenOffsetX = 0;
    options.m_i32ScreenOffsetY = 0;
    options.m_abMotionSensor[0] = 0;
}

// 0x00014f60 IKGameManager_SetFlag64Bit2_maybe: the load-game flow requested (+0x64 value 4).
void CDefaultGameManager::SetFlag64Bit2() { m_flags64 = (m_flags64 & ~4u) | 4; }

// 0x00014f78 IKGameManager_RefreshOptionsChangedFlag: +0x64 bit 3 = the options changed.
void CDefaultGameManager::RefreshOptionsChangedFlag() {
    const uint32_t changed = HaveOptionsChanged();
    m_flags64 = (m_flags64 & ~8u) | ((changed & 0xff) << 3);
}

// 0x000162a0 CDefaultGameManager_RecacheLocStrings_maybe (boot mode 0): as RecacheLocStringsAfterReload.
void CDefaultGameManager::RecacheLocStrings() {
    CManager2d_CacheLocStrings(g_pEngine->m_manager2d);
    m_unk290 = -1;
}

// 0x00016480 GameManager_RevertOptions_maybe: the edited options back into the current ones (the
// options menus' cancel), applied.
void CDefaultGameManager::RevertOptions() {
    m_currentOptions = m_editedOptions;
    ApplyOptions(&m_currentOptions, 1);
}

// 0x00016500 GameManager_BackupOptions_maybe: the current options into the edited ones and the reset
// copies (+0x120..), both pads' vibration enabled.
void CDefaultGameManager::BackupOptions() {
    m_editedOptions = m_currentOptions;
    m_i32BackupScreenOffsetX = m_currentOptions.m_i32ScreenOffsetX;
    m_i32BackupScreenOffsetY = m_currentOptions.m_i32ScreenOffsetY;
    m_ui32BackupSoundOutput = m_editedOptions.m_ui32SoundOutput;
    m_ui32BackupAspectRatio = m_editedOptions.m_ui32AspectRatio;
    m_afBackupVolumes[0] = m_editedOptions.m_afVolumes[0];
    m_afBackupVolumes[1] = m_editedOptions.m_afVolumes[1];
    m_afBackupVolumes[2] = m_editedOptions.m_afVolumes[2];
    g_pEngine->m_input->SetVibrationEnabled(0, 1);
    g_pEngine->m_input->SetVibrationEnabled(1, 1);
    m_ui32BackupBrightness = m_editedOptions.m_ui32Brightness;
}

// 0x00016bb8 IKGameManager_RestoreDefaultOptions_maybe
void CDefaultGameManager::RestoreDefaultOptions(int32_t withLanguage) {
    InitDefaultOptions(withLanguage);  // vt+0x1d0
    m_currentOptions = m_editedOptions;
    ApplyOptions(&m_currentOptions, 1);
}

// 0x00017320 IKGameManager_ToggleAutosaveOption_maybe
void CDefaultGameManager::ToggleAutosaveOption() {
    m_editedOptions.m_bAutosave ^= 1;
    ApplyOptions(&m_editedOptions, 0);
}

// 0x00017340 IKGameManager_ResetScreenOffsetOption
void CDefaultGameManager::ResetScreenOffsetOption() {
    m_editedOptions.m_i32ScreenOffsetX = m_i32BackupScreenOffsetX;
    m_editedOptions.m_i32ScreenOffsetY = m_i32BackupScreenOffsetY;
    ApplyOptions(&m_editedOptions, 0);
}

// 0x00017368 IKGameManager_ResetBrightnessOption
void CDefaultGameManager::ResetBrightnessOption() {
    m_editedOptions.m_ui32Brightness = m_ui32BackupBrightness;
    ApplyOptions(&m_editedOptions, 0);
}

// 0x00017388 IKGameManager_ToggleSubtitlesOption_maybe
void CDefaultGameManager::ToggleSubtitlesOption() {
    m_editedOptions.m_bSubtitles ^= 1;
    ApplyOptions(&m_editedOptions, 0);
}

// 0x000173a8 IKGameManager_ResetSoundAndAspectOptions_maybe
void CDefaultGameManager::ResetSoundAndAspectOptions() {
    m_editedOptions.m_ui32SoundOutput = m_ui32BackupSoundOutput;
    m_editedOptions.m_ui32AspectRatio = m_ui32BackupAspectRatio;
    m_editedOptions.m_afVolumes[0] = m_afBackupVolumes[0];
    m_editedOptions.m_afVolumes[1] = m_afBackupVolumes[1];
    m_editedOptions.m_afVolumes[2] = m_afBackupVolumes[2];
    ApplyOptions(&m_editedOptions, 0);
}

// 0x000173e8 IKGameManager_ApplyEditedOptions_2
void CDefaultGameManager::ApplyEditedOptions2() { ApplyOptions(&m_editedOptions, 0); }

// 0x00017400 IKGameManager_CycleLanguageOption: the next (or previous) language of the loc manager's
// table, wrapping; applying it requests the reload.
void CDefaultGameManager::CycleLanguageOption(int32_t backwards) {
    uint32_t& language = m_editedOptions.m_ui32Language;
    const int32_t count = g_pEngine->m_locManager->m_ui16NbLanguage;
    if (backwards == 0) {
        const int32_t next = static_cast<int32_t>(language) + 1;
        language = static_cast<uint32_t>(next);
        if (count <= next) language = 0;
    } else {
        const int32_t previous = static_cast<int32_t>(language) - 1;
        language = static_cast<uint32_t>(previous);
        if (previous < 0) language = static_cast<uint32_t>(count - 1);
    }
    ApplyOptions(&m_editedOptions, 0);
}

// 0x00017498 IKGameManager_DecScreenOffsetYOption_maybe
void CDefaultGameManager::DecScreenOffsetYOption() {
    m_editedOptions.m_i32ScreenOffsetY -= 2;
    ApplyOptions(&m_editedOptions, 0);
}

// 0x000174b8 IKGameManager_DecScreenOffsetXOption_maybe
void CDefaultGameManager::DecScreenOffsetXOption() {
    m_editedOptions.m_i32ScreenOffsetX -= 2;
    ApplyOptions(&m_editedOptions, 0);
}

// 0x000174d8 IKGameManager_ApplyEditedOptions_3
void CDefaultGameManager::ApplyEditedOptions3() { ApplyOptions(&m_editedOptions, 0); }

// 0x000174f0 IKGameManager_TogglePerPlayerOption10C
void CDefaultGameManager::TogglePerPlayerOption20(int32_t player) {
    if (player == 0) m_editedOptions.m_abUnk20[0] ^= 1;
    else if (player == 1) m_editedOptions.m_abUnk20[1] ^= 1;
    ApplyOptions(&m_editedOptions, 0);
}

// 0x00017540 IKGameManager_ToggleMotionSensorOption
void CDefaultGameManager::ToggleMotionSensorOption(int32_t player) {
    if (player == 0) m_editedOptions.m_abMotionSensor[0] ^= 1;
    else m_editedOptions.m_abMotionSensor[1] ^= 1;
    ApplyOptions(&m_editedOptions, 0);
}

// 0x00017588 IKGameManager_IncScreenOffsetXOption_maybe
void CDefaultGameManager::IncScreenOffsetXOption() {
    m_editedOptions.m_i32ScreenOffsetX += 2;
    ApplyOptions(&m_editedOptions, 0);
}

// 0x000175a8 IKGameManager_ApplyEditedOptions_4
void CDefaultGameManager::ApplyEditedOptions4() { ApplyOptions(&m_editedOptions, 0); }

// 0x000175c0 IKGameManager_ToggleAspectRatioOption: 0 and 1, wrapping (an unsigned compare).
void CDefaultGameManager::ToggleAspectRatioOption(int32_t backwards) {
    uint32_t& aspect = m_editedOptions.m_ui32AspectRatio;
    if (backwards == 0) {
        aspect = aspect + 1;
        if (aspect > 1) aspect = 0;
    } else {
        aspect = aspect - 1;
        if (aspect > 1) aspect = 1;
    }
    ApplyOptions(&m_editedOptions, 0);
}

// 0x00017628 IKGameManager_StepBrightnessOption: 0..10; nothing at the ends.
void CDefaultGameManager::StepBrightnessOption(int32_t down) {
    uint32_t& brightness = m_editedOptions.m_ui32Brightness;
    if (down == 0) {
        if (brightness > 9) return;
        brightness = brightness + 1;
    } else {
        if (brightness == 0) return;
        brightness = brightness - 1;
    }
    ApplyOptions(&m_editedOptions, 0);
}

// 0x00017680 IKGameManager_IncScreenOffsetYOption_maybe
void CDefaultGameManager::IncScreenOffsetYOption() {
    m_editedOptions.m_i32ScreenOffsetY += 2;
    ApplyOptions(&m_editedOptions, 0);
}

// 0x000176a0 IKGameManager_CycleSoundOutputOption: 0..4, wrapping (an unsigned compare).
void CDefaultGameManager::CycleSoundOutputOption(int32_t backwards) {
    uint32_t& output = m_editedOptions.m_ui32SoundOutput;
    if (backwards == 0) {
        output = output + 1;
        if (output > 4) output = 0;
    } else {
        output = output - 1;
        if (output > 4) output = 4;
    }
    ApplyOptions(&m_editedOptions, 0);
}

// 0x00017708 IKGameManager_TogglePerPlayerOption10A
void CDefaultGameManager::TogglePerPlayerOption1E(int32_t player) {
    if (player == 0) m_editedOptions.m_abUnk1E[0] ^= 1;
    else if (player == 1) m_editedOptions.m_abUnk1E[1] ^= 1;
    ApplyOptions(&m_editedOptions, 0);
}

// 0x00017758 IKGameManager_ToggleOptionF1
void CDefaultGameManager::ToggleOption05() {
    m_editedOptions.m_unk05 ^= 1;
    ApplyOptions(&m_editedOptions, 0);
}

// 0x00017780 IKGameManager_ToggleMotionSensorBothPlayersOption
void CDefaultGameManager::ToggleMotionSensorBothPlayersOption() {
    m_editedOptions.m_abMotionSensor[0] ^= 1;
    ApplyOptions(&m_editedOptions, 0);
    m_editedOptions.m_abMotionSensor[1] ^= 1;
    ApplyOptions(&m_editedOptions, 0);
}

// 0x000177f8 IKGameManager_TogglePerPlayerOption10CBothPlayers
void CDefaultGameManager::TogglePerPlayerOption20BothPlayers() {
    m_editedOptions.m_abUnk20[0] ^= 1;
    ApplyOptions(&m_editedOptions, 0);
    m_editedOptions.m_abUnk20[1] ^= 1;
    ApplyOptions(&m_editedOptions, 0);
}

// 0x00017870 IKGameManager_TogglePerPlayerOption10ABothPlayers
void CDefaultGameManager::TogglePerPlayerOption1EBothPlayers() {
    m_editedOptions.m_abUnk1E[0] ^= 1;
    ApplyOptions(&m_editedOptions, 0);
    m_editedOptions.m_abUnk1E[1] ^= 1;
    ApplyOptions(&m_editedOptions, 0);
}

// 0x00013408 CDefaultGameManager_RequestSave_maybe (vt+0x104)
void CDefaultGameManager::RequestSave(uint32_t /*unused*/, uint8_t value) {
    m_unk88 = (m_currentOptions.m_bAutosave != 0 && value != 0) ? 1 : 0;
}

// 0x00014f20 CDefaultGameManager_SetSaveRequestFlag_maybe (vt+0x10c)
void CDefaultGameManager::SetSaveRequestFlag(uint32_t /*unused*/, uint8_t value) {
    m_unk88 = (m_currentOptions.m_bAutosave != 0 && value != 0) ? 1 : 0;
    m_flags64 = (m_flags64 & 0xfffffffdu) | 2;
}

// 0x00039288 CKGameLevel_PlayLaunchScene (C2.2 gm; k2000/logic/CKGameLevel.cpp's unit): a level with a launch
// cinematic scene (+0x80) that has not played yet (+0x14 bit 1) starts it and remembers it.
static void PlayLaunchScene(CKGameLevel* level) {
    if (level->m_pCinematicScene != nullptr && (level->m_baFlags & 2) == 0) {
        static_cast<CKSrvCinematic*>(g_pEngine->m_srvCinematic)->StartScene(static_cast<CKCinematicScene*>(level->m_pCinematicScene));  // 0x166810
        level->m_baFlags = (level->m_baFlags & 0xfffffffdu) | 2;
    }
}

// 0x00013e78 CDefaultGameManager_OnLevelStart_maybe
void CDefaultGameManager::OnLevelStart() {
    IKGameStructure* structure = static_cast<IKGameStructure*>(m_gameStructure);
    CKGameLevel* level = structure->GetCurrentLevel();
    CKGameSpawnPoint* spawnPoint = structure->m_pCurrentSpawnPoint;
    if (spawnPoint != nullptr && spawnPoint->m_pGameStage->GetMatchesThisLevel() != 0) spawnPoint->Activate();
    if (level != nullptr) PlayLaunchScene(level);
    if ((m_unk80 >> 24) != 0) {
        QueueTriggerSignals(&m_unk78);
        m_unk80 &= 0x00ffffffu;
        return;
    }
    QueueTriggerSignals(&m_unk70);
}

namespace {
const CKLocText* PromptText(CKLocTextAccessor* accessor, uint32_t index) {
    if (accessor->m_texts.m_pBlock != nullptr) return static_cast<const CKLocText*>(accessor->m_texts.m_pBlock[index]);
    return static_cast<const CKLocText*>(accessor->m_pText);
}
}  // namespace

// 0x000137b8 CDefaultGameManager_GetSkipVideoPromptText_maybe
const CKLocText* CDefaultGameManager::GetSkipVideoPromptText() { return PromptText(static_cast<CKLocTextAccessor*>(m_unk144), 1); }
// 0x00014ef0 CDefaultGameManager_GetSkipCinematicPromptText_maybe
const CKLocText* CDefaultGameManager::GetSkipCinematicPromptText() { return PromptText(static_cast<CKLocTextAccessor*>(m_unk144), 2); }
// 0x00014ec0 CDefaultGameManager_GetCannotSkipPromptText_maybe
const CKLocText* CDefaultGameManager::GetCannotSkipPromptText() { return PromptText(static_cast<CKLocTextAccessor*>(m_unk144), 3); }

// 0x00013d60 IKGameManager_SwitchToFocusedHeroCamera_maybe
uint8_t CDefaultGameManager::SwitchToFocusedHeroCamera() {
    CKSrvCamera* camera = static_cast<CKSrvCamera*>(g_pEngine->m_srvCamera);
    IKSerializable* focused = GetFocusedHeroCamera();  // vt+0x120
    const IKSerializable* current = camera->m_ui32NbStacked != 0 ? camera->m_aStack[0].m_pTarget : nullptr;
    uint8_t result = 1;
    if (current != focused && focused != nullptr) {
        camera->SwitchCameraIfDifferent(1.0f, focused, 0);
        result = 0;
    }
    return result;
}
