// CKHkS08FlamingTorch.cpp - reconstructed original translation unit 0x4961c0-0x49b440 (GAME_TOC1, main_toc1), 52 functions, 42 live.
// Primary class: CKHkS08FlamingTorch  key 0x2e82  category Hook  size 0x10c  vtable 0xb282e0
// Other owners: CKHkS08FogHorn (3)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x4961c0  CKHkS08FlamingTorch_Delete
//   [ ] 0x496210  CKHkS08FlamingTorch_AttachCollisionNodeToActor_maybe  [dead]
//   [ ] 0x4962a8  CKHkS08FlamingTorch_vfC8
//   [ ] 0x4962e0  CKHkS08FlamingTorch_ReleaseFxAt50_maybe  [dead]
//   [ ] 0x496348  FUN_00496348  [dead]
//   [ ] 0x496358  CKHkS08FlamingTorch_StopSound0_maybe  [dead]
//   [ ] 0x4963a0  CKHkS08FlamingTorch_InitCollisionVolume_maybe  [dead]
//   [ ] 0x496470  CKHkS08FlamingTorch_DetectElementHits_maybe
//   [ ] 0x496758  CKHkS08FlamingTorch_StartFlameFx_maybe
//   [ ] 0x496a20  CKHkS08FlamingTorch_Resume
//   [ ] 0x496a48  CKHkS08FlamingTorch_Pause
//   [ ] 0x496a70  CKHkS08FlamingTorch_Stop
//   [ ] 0x496a98  CKHkS08FlamingTorch_SetDefaultState
//   [ ] 0x496ae0  CKHkS08FlamingTorch_GetInfo
//   [ ] 0x496bc0  CKHkS08FlamingTorch_Save
//   [ ] 0x496be8  CKHkS08FlamingTorch_RecursiveRegistration
//   [x] 0x496c10  CKHkS08FlamingTorch_Construct  [dead]
//   [x] 0x496c70  CKHkS08FlamingTorch_DeleteArray
//   [ ] 0x496d10  RegisterCKHkS08FlamingTorchClass
//   [ ] 0x496d98  _GLOBAL__D_496d98
//   [ ] 0x496da8  _GLOBAL__I_496da8
//   [ ] 0x496db8  CKHkS08FlamingTorch_DeletingDestructor
//   [ ] 0x496e40  CKHkS08FlamingTorch_Destructor
//   [ ] 0x496eb8  CKHkS08FlamingTorch_Destructor_2  [dead]
//   [ ] 0x496f30  CKHkS08FlamingTorch_Construct_2  [dead]
//   [ ] 0x496f90  CKHkS08FlamingTorch_Destroy
//   [ ] 0x496fb8  CKHkS08FlamingTorch_IsLit_maybe
//   [ ] 0x496fe0  CKHkS08FlamingTorch_ScaleFlameParticles_maybe
//   [ ] 0x4971f0  CKHkS08FlamingTorch_AddHotspotPointsToFx_maybe
//   [x] 0x497478  CKHkS08FlamingTorch_CreateArray
//   [x] 0x497558  CKHkS08FlamingTorch_Create
//   [ ] 0x4975c8  CKHkS08FlamingTorch_OnActivate
//   [ ] 0x4977a0  CKHkS08FlamingTorch_OnDeactivate
//   [ ] 0x497970  CKHkS08FlamingTorch_State1
//   [ ] 0x497c98  CKHkS08FlamingTorch_UpdateFlameParticles_maybe
//   [ ] 0x498350  CKHkS08FlamingTorch_StartFlameParticles_maybe
//   [ ] 0x4987a0  CKHkS08FlamingTorch_State3_Lit_maybe
//   [ ] 0x498988  CKHkS08FlamingTorch_State0_Unlit_maybe
//   [ ] 0x498a20  CKHkS08FlamingTorch_TriggerHotSpotExplosionFx_maybe
//   [ ] 0x498ce0  CKHkS08FlamingTorch_State2
//   [x] 0x498f90  CKHkS08FlamingTorch_Load
//   [ ] 0x499bc0  CKHkS08FlamingTorch_PostLoad
//   [ ] 0x499db0  CKHkS08FlamingTorch_Start
//   [ ] 0x49a008  CKHkS08FlamingTorch_Update
//   [ ] 0x49a240  CKHkS08FlamingTorch_vfCC
//   [ ] 0x49a4b8  CKHkS08FlamingTorch_MessageProc
//   [ ] 0x49ad80  CKHkS08FlamingTorch_Restart
//   [ ] 0x49b1b8  CKHkS08FogHorn_Delete
//   [ ] 0x49b208  CKHkS08FogHorn_ApplyStatePreset_maybe
//   [ ] 0x49b230  CKHkS08FogHorn_DetectWindBeamContact
//   [ ] 0x49b430  KStub_ReturnArg4_49b430  [dead]
//   [ ] 0x49b438  KStub_ReturnArg4_49b438  [dead]
//
//   [ ] 0x9c4d18  CKHkS08FlamingTorch_IsKindOfClass  [inline]
//   [ ] 0x9c4d70  CKHkS08FlamingTorch_GetClassType  [inline]
//   [ ] 0x9c4d78  CKHkS08FlamingTorch_GetClassID  [inline]
#include "Spyro2008/hooks/CKHkS08FlamingTorch.h"

#include "k2000/io/IKFile.h"

// 0x00498f90 CKHkS08FlamingTorch_Load: the actor base, then the level data (type 0 only). The trigger
// starters are loaded with type 0.
int32_t CKHkS08FlamingTorch::Load(IKFile* file, int32_t type) {
    CKHkActorBase::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        IKFile_ReadRef(file, &m_pUnkBC);
        IKFile_ReadRef(file, &m_pUnk4C);
        ReadF32LE(file, &m_fUnk30);
        ReadF32LE(file, &m_fUnk34);
        ReadF32LE(file, &m_fUnk44);
        ReadF32LE(file, &m_fUnk3C);
        m_unkAC.Load(file, K_LEVEL_PLATEFORMS);
        IKFile_ReadRef(file, &m_pUnkE0);
        IKFile_ReadRef(file, &m_pUnk94);
        ReadF32LE(file, &m_fUnk48);
        ReadU32LE(file, &m_unk98);
        IKFile_ReadRef(file, &m_pUnk54);
        IKFile_ReadRef(file, &m_pUnk28);
        IKFile_ReadRef(file, &m_pUnk88);
        m_unkB4.Load(file, K_LEVEL_PLATEFORMS);
        IKFile_ReadRef(file, &m_pUnk20);
        IKFile_ReadRef(file, &m_pUnk24);
        uint32_t count = 0;
        ReadU32LE(file, &count);
        // BUG(original): no bound check; a count above 2 would write past the table.
        for (uint32_t i = 0; i < count; ++i) {
            SEntry& entry = m_aUnk5C[i];
            ReadF32LE(file, &entry.m_fUnk8);
            ReadF32LE(file, &entry.m_fUnkC);
            ReadF32LE(file, &entry.m_fUnk0);
            ReadF32LE(file, &entry.m_fUnk4);
            ReadF32LE(file, &entry.m_fUnk10);
        }
        IKFile_ReadRef(file, &m_pUnk9C);
        IKFile_ReadRef(file, &m_pUnkA0);
        IKFile_ReadRef(file, &m_pUnkA4);
        IKFile_ReadRef(file, &m_pUnkA8);
        IKFile_ReadRef(file, &m_pUnk8C);
        IKFile_ReadRef(file, &m_pUnk90);
        IKFile_ReadRef(file, &m_pUnkC0);
        ReadU8(file, &m_unkD8);
        ReadU8(file, &m_unkD9);
        ReadU8(file, &m_unkDA);
        ReadU8(file, &m_unkDD);
        ReadU8(file, &m_unkDE);
        ReadU8(file, &m_unkDF);
    }
    return 1;
}
