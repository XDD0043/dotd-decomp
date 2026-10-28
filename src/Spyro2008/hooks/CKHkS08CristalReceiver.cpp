// CKHkS08CristalReceiver.cpp - reconstructed original translation unit 0x483210-0x486570 (GAME_TOC1, main_toc1), 38 functions, 34 live.
// Primary class: CKHkS08CristalReceiver  key 0x2c02  category Hook  size 0x94  vtable 0xb27cf8
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x483210  CKHkS08CristalReceiver_Delete
//   [ ] 0x483260  CKHkS08CristalReceiver_Restart
//   [ ] 0x483270  CKHkS08CristalReceiver_SetGlowLevel_maybe
//   [ ] 0x483490  CKHkS08CristalReceiver_ReleaseFxAt50_maybe  [dead]
//   [ ] 0x4834f8  CKHkS08CristalReceiver_ReleaseFxAt40_maybe  [dead]
//   [ ] 0x483560  CKHkS08CristalReceiver_Resume
//   [ ] 0x483588  CKHkS08CristalReceiver_Pause
//   [ ] 0x4835b0  CKHkS08CristalReceiver_Stop
//   [ ] 0x4835d8  CKHkS08CristalReceiver_Start
//   [ ] 0x483688  CKHkS08CristalReceiver_GetInfo
//   [ ] 0x483768  CKHkS08CristalReceiver_PostLoad
//   [ ] 0x4837c8  CKHkS08CristalReceiver_Save
//   [ ] 0x4837f0  CKHkS08CristalReceiver_RecursiveRegistration
//   [ ] 0x483818  CKHkS08CristalReceiver_Destroy
//   [ ] 0x483840  CKHkS08CristalReceiver_BaseDestructor
//   [x] 0x483870  CKHkS08CristalReceiver_Construct  [dead]
//   [ ] 0x4838c8  CKHkS08CristalReceiver_Construct_2  [dead]
//   [x] 0x483920  CKHkS08CristalReceiver_DeleteArray
//   [ ] 0x4839c0  RegisterCKHkS08CristalReceiverClass
//   [ ] 0x483a48  _GLOBAL__D_483a48
//   [ ] 0x483a58  _GLOBAL__I_483a58
//   [ ] 0x483a68  CKHkS08CristalReceiver_DeletingDestructor
//   [ ] 0x483ab0  CKHkS08CristalReceiver_Destructor
//   [ ] 0x483ae0  CKHkS08CristalReceiver_GetTriggerProp96
//   [ ] 0x483af8  CKHkS08CristalReceiver_UpdateSoundPositions_maybe
//   [ ] 0x483b88  CKHkS08CristalReceiver_AddHotspotPointsToFx_maybe
//   [x] 0x483cd0  CKHkS08CristalReceiver_CreateArray
//   [x] 0x483da0  CKHkS08CristalReceiver_Create
//   [ ] 0x483e08  CKHkS08CristalReceiver_OnDeactivate
//   [ ] 0x483ef8  CKHkS08CristalReceiver_Update
//   [ ] 0x484318  CKHkS08CristalReceiver_OnActivate_maybe
//   [ ] 0x4844c8  CKHkS08CristalReceiver_MessageProc
//   [x] 0x4846c8  CKHkS08CristalReceiver_Load
//   [ ] 0x484e60  CKHkS08CristalReceiver_TriggerReceiveFx_maybe
//   [ ] 0x485168  CKHkS08CristalReceiver_State0_AwaitOrb_maybe
//   [ ] 0x485a58  CKHkS08CristalReceiver_ShowInputIcon_maybe
//   [ ] 0x485d38  CKHkS08CristalReceiver_StartParticleFxAtHotspot_maybe
//   [ ] 0x486010  CKHkS08CristalReceiver_State1_maybe
//
//   [ ] 0x9c4868  CKHkS08CristalReceiver_IsKindOfClass  [inline]
//   [ ] 0x9c48c0  CKHkS08CristalReceiver_GetClassType  [inline]
//   [ ] 0x9c48c8  CKHkS08CristalReceiver_GetClassID  [inline]
#include "Spyro2008/hooks/CKHkS08CristalReceiver.h"

#include "k2000/io/IKFile.h"

// 0x004846c8 CKHkS08CristalReceiver_Load: the actor base, then the level data (type 0 only). The trigger
// starters are loaded with type 0.
int32_t CKHkS08CristalReceiver::Load(IKFile* file, int32_t type) {
    CKHkActorBase::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        IKFile_ReadRef(file, &m_pUnk20);
        ReadF32LE(file, &m_fUnk64);
        ReadF32LE(file, &m_fUnk30);
        IKFile_ReadRef(file, &m_pUnk24);
        IKFile_ReadRef(file, &m_pUnk34);
        IKFile_ReadRef(file, &m_pUnk2C);
        IKFile_ReadRef(file, &m_pUnk38);
        IKFile_ReadRef(file, &m_pUnk58);
        IKFile_ReadRef(file, &m_pUnk48);
        IKFile_ReadRef(file, &m_pUnk28);
        m_unk68.Load(file, K_LEVEL_PLATEFORMS);
        IKFile_ReadRef(file, &m_pUnk4C);
        IKFile_ReadRef(file, &m_pUnk5C);
        IKFile_ReadRef(file, &m_pUnk60);
        IKFile_ReadRef(file, &m_pUnk54);
        IKFile_ReadRef(file, &m_pUnk3C);
        ReadF32LE(file, &m_fUnk78);
    }
    return 1;
}
