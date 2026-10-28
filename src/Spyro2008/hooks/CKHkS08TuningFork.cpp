// CKHkS08TuningFork.cpp - reconstructed original translation unit 0x4cdaa0-0x4d3438 (GAME_TOC1, main_toc1), 54 functions, 45 live.
// Primary class: CKHkS08TuningFork  key 0x2d42  category Hook  size 0x174  vtable 0xb29b58
// Other owners: CKHkS08PowerBucket (3)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x4cdaa0  CKHkS08TuningFork_CheckHitByFearScream_maybe
//   [ ] 0x4cdc90  CKHkS08TuningFork_ReleaseRef9C_maybe  [dead]
//   [ ] 0x4cdcf8  RegisterCKHkS08TuningForkClass
//   [ ] 0x4cdd80  _GLOBAL__D_4cdd80
//   [ ] 0x4cdd90  _GLOBAL__I_4cdd90
//   [ ] 0x4cdda0  CKHkS08TuningFork_MessageProc
//   [ ] 0x4cdeb8  CKHkS08TuningFork_InitCollisionVolume_maybe  [dead]
//   [ ] 0x4cdf88  CKHkS08TuningFork_ApplyVibrationShake_maybe
//   [ ] 0x4ce078  CKHkS08TuningFork_Resume
//   [ ] 0x4ce0a0  CKHkS08TuningFork_Pause
//   [ ] 0x4ce0c8  CKHkS08TuningFork_Stop
//   [ ] 0x4ce0f0  CKHkS08TuningFork_Start
//   [ ] 0x4ce1c8  CKHkS08TuningFork_Save
//   [ ] 0x4ce1f0  CKHkS08TuningFork_RecursiveRegistration
//   [x] 0x4ce218  CKHkS08TuningFork_Construct  [dead]
//   [x] 0x4ce270  CKHkS08TuningFork_DeleteArray
//   [ ] 0x4ce310  CKHkS08TuningFork_Restart
//   [ ] 0x4ce4b8  CKHkS08TuningFork_IsState1AndFlag121Set_maybe
//   [ ] 0x4ce4e0  CKHkS08TuningFork_GetTriggerProp9A
//   [ ] 0x4ce528  CKHkS08TuningFork_GetTriggerProp9B
//   [ ] 0x4ce540  CKHkS08TuningFork_StopShakeAndRestorePose_maybe
//   [ ] 0x4ce5f0  CKHkS08TuningFork_StartShakeForState_maybe  [dead]
//   [ ] 0x4ce660  CKHkS08TuningFork_IsVibrating_maybe
//   [ ] 0x4ce6a0  CKHkS08TuningFork_BaseDestructor
//   [ ] 0x4ce6d0  CKHkS08TuningFork_Construct_2  [dead]
//   [ ] 0x4ce728  CKHkS08TuningFork_Destroy
//   [ ] 0x4ce768  CKHkS08TuningFork_DeletingDestructor
//   [ ] 0x4ce7b0  CKHkS08TuningFork_Destructor
//   [ ] 0x4ce7e0  CKHkS08TuningFork_GetInfo
//   [ ] 0x4ce910  CKHkS08TuningFork_SetPhaseOffsetFrom_maybe
//   [ ] 0x4ce960  CKHkS08TuningFork_SetMeshAlpha_maybe
//   [ ] 0x4ceb88  FUN_004ceb88  [dead]
//   [ ] 0x4cebc8  CKHkS08TuningFork_ScaleParticles_maybe
//   [x] 0x4cf020  CKHkS08TuningFork_CreateArray
//   [x] 0x4cf0f0  CKHkS08TuningFork_Create
//   [ ] 0x4cf158  CKHkS08TuningFork_UpdateFadeAlpha_maybe
//   [ ] 0x4cf380  FUN_004cf380  [dead]
//   [ ] 0x4cf3c0  CKHkS08TuningFork_OnDeactivate
//   [ ] 0x4cf530  CKHkS08TuningFork_Update
//   [ ] 0x4cf788  CKHkS08TuningFork_OnActivate
//   [ ] 0x4cfad0  CKHkS08TuningFork_PostLoad
//   [x] 0x4cfbb8  CKHkS08TuningFork_Load
//   [ ] 0x4d0e30  CKHkS08TuningFork_TriggerExplosionFx_maybe
//   [ ] 0x4d10e0  CKHkS08TuningFork_StartScaledParticleFx_maybe
//   [ ] 0x4d17b8  CKHkS08TuningFork_State2
//   [ ] 0x4d1b40  CKHkS08TuningFork_PlayShockWaveFx_maybe
//   [ ] 0x4d1db0  CKHkS08TuningFork_PlayExplosionFx_maybe
//   [ ] 0x4d2058  CKHkS08TuningFork_PlayShockWaveFx_2_maybe
//   [ ] 0x4d22c8  CKHkS08TuningFork_State3
//   [ ] 0x4d28d0  CKHkS08TuningFork_VibrateState_maybe
//   [ ] 0x4d3358  CKHkS08PowerBucket_Delete
//   [ ] 0x4d33a8  CKHkS08PowerBucket_vf190
//   [ ] 0x4d33b0  CKHkS08PowerBucket_ReleaseRef1E4_maybe  [dead]
//   [ ] 0x4d3418  FUN_004d3418  [dead]
//
//   [ ] 0x9c5db8  CKHkS08TuningFork_IsKindOfClass  [inline]
//   [ ] 0x9c5e10  CKHkS08TuningFork_GetClassType  [inline]
//   [ ] 0x9c5e18  CKHkS08TuningFork_GetClassID  [inline]
#include "Spyro2008/hooks/CKHkS08TuningFork.h"

#include "k2000/io/IKFile.h"

// 0x004cfbb8 CKHkS08TuningFork_Load: the actor base, then the level data (type 0 only). The trigger
// starters are loaded with type 0.
int32_t CKHkS08TuningFork::Load(IKFile* file, int32_t type) {
    CKHkActorBase::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        IKFile_ReadRef(file, &m_pUnk30);
        IKFile_ReadRef(file, &m_pUnk4C);
        IKFile_ReadRef(file, &m_pUnk50);
        IKFile_ReadRef(file, &m_pUnk54);
        IKFile_ReadRef(file, &m_pUnk58);
        IKFile_ReadRef(file, &m_pUnk5C);
        IKFile_ReadRef(file, &m_pUnk60);
        ReadU32LE(file, &m_unk2C);
        ReadF32LE(file, &m_fUnk34);
        ReadF32LE(file, &m_fUnk3C);
        IKFile_ReadRef(file, &m_pUnk7C);
        IKFile_ReadRef(file, &m_pUnk84);
        IKFile_ReadRef(file, &m_pUnk100);
        ReadF32LE(file, &m_fUnk104);
        ReadF32LE(file, &m_fUnk10C);
        ReadF32LE(file, &m_fUnk110);
        ReadF32LE(file, &m_fUnk108);
        ReadF32LE(file, &m_fUnk11C);
        ReadF32LE(file, &m_fUnk118);
        IKFile_ReadRef(file, &m_pUnk94);
        IKFile_ReadRef(file, &m_pUnk8C);
        IKFile_ReadRef(file, &m_pUnk20);
        IKFile_ReadRef(file, &m_pUnk24);
        IKFile_ReadRef(file, &m_pUnk114);
        m_unk154.Load(file, K_LEVEL_PLATEFORMS);
        m_unk15C.Load(file, K_LEVEL_PLATEFORMS);
        ReadF32LE(file, &m_fUnk44);
        IKFile_ReadRef(file, &m_pUnkDC);
        IKFile_ReadRef(file, &m_pUnk98);
        ReadF32LE(file, &m_fUnkA0);
        ReadF32LE(file, &m_fUnkA4);
        ReadF32LE(file, &m_fUnkA8);
        ReadF32LE(file, &m_fUnkAC);
        ReadF32LE(file, &m_fUnkB0);
        ReadF32LE(file, &m_fUnkB4);
        ReadF32LE(file, &m_fUnkB8);
        ReadF32LE(file, &m_fUnkBC);
        ReadF32LE(file, &m_fUnkC0);
        ReadF32LE(file, &m_fUnkC4);
        ReadF32LE(file, &m_fUnkC8);
        ReadF32LE(file, &m_fUnkCC);
        ReadF32LE(file, &m_fUnkD0);
        ReadF32LE(file, &m_fUnkD4);
        ReadF32LE(file, &m_fUnkD8);
        IKFile_ReadRef(file, &m_pUnkE0);
        IKFile_ReadRef(file, &m_pUnkE4);
        m_unk16C.Load(file, K_LEVEL_PLATEFORMS);
        m_unk164.Load(file, K_LEVEL_PLATEFORMS);
        ReadF32LE(file, &m_fUnkE8);
        ReadF32LE(file, &m_fUnkEC);
        ReadU8(file, &m_unkF0);
        ReadU8(file, &m_unkF1);
        ReadF32LE(file, &m_fUnkF4);
        ReadF32LE(file, &m_fUnkF8);
        ReadU8(file, &m_unkFC);
        ReadU8(file, &m_unkFD);
        ReadF32LE(file, &m_fUnk128);
        ReadF32LE(file, &m_fUnk68);
        ReadF32LE(file, &m_fUnk6C);
    }
    return 1;
}
