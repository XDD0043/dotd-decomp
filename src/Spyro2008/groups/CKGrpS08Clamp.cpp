// CKGrpS08Clamp.cpp - reconstructed original translation unit 0x4916f8-0x492650 (GAME_TOC1, main_toc1), 31 functions, 27 live.
// Primary class: CKGrpS08Clamp  key 0xc04  category Group  size 0x4c  vtable 0xb27fe0
// Other owners: CKHkS08Clamp (1), CKHkS08ClampGun (1), CKHkS08ElectricGauge (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x4916f8  CKGrpS08Clamp_Delete
//   [ ] 0x491748  CKGrpS08Clamp_Construct  [dead]
//   [ ] 0x4917c0  CKGrpS08Clamp_vfB8
//   [ ] 0x4917c8  FUN_004917c8  [dead]
//   [ ] 0x491810  CKGrpS08Clamp_Construct_2  [dead]
//   [ ] 0x491888  CKGrpS08Clamp_PostLoad
//   [ ] 0x4918b0  RegisterCKGrpS08ClampClass
//   [ ] 0x491928  _GLOBAL__I_491928
//   [ ] 0x491938  CKHkS08Clamp_SpawnFx_maybe
//   [ ] 0x491ba0  CKHkS08ClampGun_ReturnClampToPool_maybe
//   [ ] 0x491bf8  CKGrpS08Clamp_TakeFreeClamp_maybe
//   [x] 0x491c28  CKGrpS08Clamp_DeleteArray
//   [ ] 0x491cc8  CKGrpS08Clamp_GetInfo
//   [ ] 0x491cd0  CKGrpS08Clamp_Update
//   [ ] 0x491cd8  CKGrpS08Clamp_Resume
//   [ ] 0x491ce0  CKGrpS08Clamp_Stop
//   [ ] 0x491ce8  CKGrpS08Clamp_Pause
//   [x] 0x491cf0  CKGrpS08Clamp_Start
//   [ ] 0x491d90  CKGrpS08Clamp_Restart
//   [ ] 0x491dc8  CKGrpS08Clamp_MessageProc
//   [ ] 0x491ef0  CKGrpS08Clamp_RecursiveRegistration
//   [ ] 0x491f18  CKGrpS08Clamp_Destroy
//   [x] 0x491f78  CKGrpS08Clamp_Create
//   [x] 0x492008  CKGrpS08Clamp_CreateArray
//   [ ] 0x4920f0  CKGrpS08Clamp_Destructor_2  [dead]
//   [x] 0x492170  CKGrpS08Clamp_Load
//   [ ] 0x492320  CKGrpS08Clamp_Destructor
//   [ ] 0x4923a0  CKGrpS08Clamp_Save
//   [ ] 0x492568  CKGrpS08Clamp_DeletingDestructor
//   [ ] 0x4925f8  CKHkS08ElectricGauge_Delete
//   [ ] 0x492648  KStub_ReturnArg4_492648
//
//   [x] 0x9c49a8  CKGrpS08Clamp_GetClassType  [inline]
//   [x] 0x9c49b0  CKGrpS08Clamp_GetClassID  [inline]
//   [ ] 0x9c49b8  CKGrpS08Clamp_vfCC  [inline]
//   [ ] 0x9c4a08  CKGrpS08Clamp_vfB0  [inline]
//   [ ] 0x9c4a18  CKGrpS08Clamp_vfB4  [inline]
//   [ ] 0x9c4a28  CKGrpS08Clamp_vfBC  [inline]
//   [ ] 0x9c4ad0  CKGrpS08Clamp_vfE0  [inline]
//   [ ] 0x9c4ad8  CKGrpS08Clamp_vfE4  [inline]
//   [ ] 0x9c4ae0  CKGrpS08Clamp_vfE8  [inline]
//   [ ] 0x9c4ae8  CKGrpS08Clamp_vfD8  [inline]
//   [ ] 0x9c4b28  CKGrpS08Clamp_vfDC  [inline]
//   [ ] 0x9c4be8  CKGrpS08Clamp_IsKindOfClass  [inline]
#include "Spyro2008/groups/CKGrpS08Clamp.h"
#include "Spyro2008/groups/C22SpyroShims.h"

// 0x00492170 CKGrpS08Clamp_Load
int32_t CKGrpS08Clamp::Load(IKFile* file, int32_t type) {
    GroupBasicLoad(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    m_list.Load(file, K_LEVEL_PLATEFORMS);
    IKFile_ReadRef(file, &m_pUnk40);
    IKFile_ReadRef(file, &m_pUnk44);
    IKFile_ReadRef(file, &m_pUnk48);
    return 1;
}

// 0x00491cf0 CKGrpS08Clamp_Start
void CKGrpS08Clamp::Start() {
    m_unk3c = m_unk3c & 0x00ffffffu;  // the byte at +0x3c
    // CKHkHeroActivator_CallSetEnabled 0x448038: the activator's vt+0xcc with 0.
    c22spyro::HeroActivatorDisable(static_cast<CKHkHeroActivator*>(m_pUnk40));
    // The clamp's particle node: shown (bit 2 off), active (bit 10), not pending (bit 19), emitting.
    CParticlesNodeFx* fx = static_cast<CParticlesNodeFx*>(m_pUnk48);
    fx->m_sgProperties = fx->m_sgProperties & 0xfffffffbu;
    fx->m_sgProperties = (fx->m_sgProperties & 0xfff7ffffu) | 0x400u;
    fx->m_fEmissionSpeedAdjustment = 0.0f;
    fx->m_pRpPrtStdEmitter->flag = fx->m_pRpPrtStdEmitter->flag | (rpPRTSTDEMITTERFLAGACTIVE | rpPRTSTDEMITTERFLAGEMIT);
}
