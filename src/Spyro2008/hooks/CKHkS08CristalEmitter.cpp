// CKHkS08CristalEmitter.cpp - reconstructed original translation unit 0x480508-0x483210 (GAME_TOC1, main_toc1), 37 functions, 33 live.
// Primary class: CKHkS08CristalEmitter  key 0x2bc2  category Hook  size 0x88  vtable 0xb27c00
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x480508  CKHkS08CristalEmitter_Delete
//   [ ] 0x480558  CKHkS08CristalEmitter_ReleaseFxAt60_maybe  [dead]
//   [ ] 0x4805c0  CKHkS08CristalEmitter_ReleaseFxAt6C_maybe  [dead]
//   [ ] 0x480628  CKHkS08CristalEmitter_Resume
//   [ ] 0x480650  CKHkS08CristalEmitter_Pause
//   [ ] 0x480678  CKHkS08CristalEmitter_Stop
//   [ ] 0x4806a0  CKHkS08CristalEmitter_Start
//   [ ] 0x480738  CKHkS08CristalEmitter_GetInfo
//   [ ] 0x480818  CKHkS08CristalEmitter_PostLoad
//   [ ] 0x480878  CKHkS08CristalEmitter_Save
//   [ ] 0x4808a0  CKHkS08CristalEmitter_RecursiveRegistration
//   [ ] 0x4808c8  CKHkS08CristalEmitter_Destroy
//   [ ] 0x4808f0  CKHkS08CristalEmitter_BaseDestructor
//   [x] 0x480920  CKHkS08CristalEmitter_Construct  [dead]
//   [ ] 0x480978  CKHkS08CristalEmitter_Construct_2  [dead]
//   [x] 0x4809d0  CKHkS08CristalEmitter_DeleteArray
//   [ ] 0x480a78  RegisterCKHkS08CristalEmitterClass
//   [ ] 0x480b00  _GLOBAL__D_480b00
//   [ ] 0x480b10  _GLOBAL__I_480b10
//   [ ] 0x480b20  CKHkS08CristalEmitter_UpdateSoundPosition_maybe
//   [ ] 0x480ba0  CKHkS08CristalEmitter_DeletingDestructor
//   [ ] 0x480be8  CKHkS08CristalEmitter_Destructor
//   [ ] 0x480c18  CKHkS08CristalEmitter_GetTriggerProp96
//   [x] 0x480c30  CKHkS08CristalEmitter_Create
//   [x] 0x480c98  CKHkS08CristalEmitter_CreateArray
//   [ ] 0x480d70  CKHkS08CristalEmitter_SetOrbOpacity_maybe
//   [ ] 0x481020  CKHkS08CristalEmitter_State1
//   [ ] 0x4811c8  CKHkS08CristalEmitter_Restart
//   [ ] 0x481218  CKHkS08CristalEmitter_OnActivate
//   [ ] 0x481250  CKHkS08CristalEmitter_OnDeactivate
//   [ ] 0x4812c8  CKHkS08CristalEmitter_Update
//   [x] 0x4816a0  CKHkS08CristalEmitter_Load
//   [ ] 0x481c40  CKHkS08CristalEmitter_ShowInputIcon_maybe
//   [ ] 0x481f20  CKHkS08CristalEmitter_StartParticleFxAtHotspot_maybe
//   [ ] 0x482218  CKHkS08CristalEmitter_SpawnFx_maybe
//   [ ] 0x482518  CKHkS08CristalEmitter_MessageProc
//   [ ] 0x482918  CKHkS08CristalEmitter_State0_OrbReady_maybe
//
//   [ ] 0x9c4800  CKHkS08CristalEmitter_IsKindOfClass  [inline]
//   [ ] 0x9c4858  CKHkS08CristalEmitter_GetClassType  [inline]
//   [ ] 0x9c4860  CKHkS08CristalEmitter_GetClassID  [inline]
#include "Spyro2008/hooks/CKHkS08CristalEmitter.h"

#include "k2000/io/IKFile.h"

// 0x004816a0 CKHkS08CristalEmitter_Load: the actor base, then the level data (type 0 only). The trigger
// starters are loaded with type 0.
int32_t CKHkS08CristalEmitter::Load(IKFile* file, int32_t type) {
    CKHkActorBase::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        IKFile_ReadRef(file, &m_pUnk24);
        ReadF32LE(file, &m_fUnk3C);
        IKFile_ReadRef(file, &m_pUnk20);
        IKFile_ReadRef(file, &m_pUnk40);
        IKFile_ReadRef(file, &m_pUnk34);
        m_unk48.Load(file, K_LEVEL_PLATEFORMS);
        IKFile_ReadRef(file, &m_pUnk44);
        IKFile_ReadRef(file, &m_pUnk30);
        IKFile_ReadRef(file, &m_pUnk50);
        ReadF32LE(file, &m_fUnk54);
        IKFile_ReadRef(file, &m_pUnk5C);
        IKFile_ReadRef(file, &m_pUnk64);
        IKFile_ReadRef(file, &m_pUnk68);
    }
    return 1;
}
