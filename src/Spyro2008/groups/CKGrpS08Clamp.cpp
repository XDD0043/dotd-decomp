// CKGrpS08Clamp.cpp - reconstructed original translation unit 0x4916f8-0x492650 (GAME_TOC1, main_toc1), 31 functions, 27 live.
// Primary class: CKGrpS08Clamp  key 0xc04  category Group  size 0x4c  vtable 0xb27fe0
// Other owners: CKHkS08Clamp (1), CKHkS08ClampGun (1), CKHkS08ElectricGauge (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x4916f8  CKGrpS08Clamp_Delete
//   [ ] 0x491748  CKGrpS08Clamp_Construct  [dead]
//   [x] 0x4917c0  CKGrpS08Clamp_vfB8  (returns 0xb: undeclared slot, see CKGrpS08Clamp.h)
//   [ ] 0x4917c8  FUN_004917c8  [dead]
//   [ ] 0x491810  CKGrpS08Clamp_Construct_2  [dead]
//   [x] 0x491888  CKGrpS08Clamp_PostLoad  (header)
//   [ ] 0x4918b0  RegisterCKGrpS08ClampClass
//   [ ] 0x491928  _GLOBAL__I_491928
//   [x] 0x491938  CKHkS08Clamp_SpawnFx_maybe
//   [x] 0x491ba0  CKHkS08ClampGun_ReturnClampToPool_maybe  (CKGrpS08Clamp::ReturnClampToPool)
//   [x] 0x491bf8  CKGrpS08Clamp_TakeFreeClamp_maybe  (TakeFreeClamp, CKGrpS08Clamp.h)
//   [x] 0x491c28  CKGrpS08Clamp_DeleteArray
//   [x] 0x491cc8  CKGrpS08Clamp_GetInfo  (1: IKSerializable's)
//   [x] 0x491cd0  CKGrpS08Clamp_Update  (empty: IKBaseGroup's)
//   [x] 0x491cd8  CKGrpS08Clamp_Resume  (empty: IKBaseGroup's)
//   [x] 0x491ce0  CKGrpS08Clamp_Stop  (empty: IKBaseGroup's)
//   [x] 0x491ce8  CKGrpS08Clamp_Pause  (empty: IKBaseGroup's)
//   [x] 0x491cf0  CKGrpS08Clamp_Start
//   [x] 0x491d90  CKGrpS08Clamp_Restart
//   [x] 0x491dc8  CKGrpS08Clamp_MessageProc
//   [x] 0x491ef0  CKGrpS08Clamp_RecursiveRegistration  (IKGroup's only: IKBaseGroup::RecursiveRegistration inherited)
//   [x] 0x491f18  CKGrpS08Clamp_Destroy  (header)
//   [x] 0x491f78  CKGrpS08Clamp_Create
//   [x] 0x492008  CKGrpS08Clamp_CreateArray
//   [ ] 0x4920f0  CKGrpS08Clamp_Destructor_2  [dead]
//   [x] 0x492170  CKGrpS08Clamp_Load
//   [x] 0x492320  CKGrpS08Clamp_Destructor  (header)
//   [ ] 0x4923a0  CKGrpS08Clamp_Save
//   [x] 0x492568  CKGrpS08Clamp_DeletingDestructor  (the destructor; delete)
//   [x] 0x4925f8  CKHkS08ElectricGauge_Delete  (the Delete factory: DOTD_DECLARE_FACTORIES(CKHkS08ElectricGauge))
//   [x] 0x492648  KStub_ReturnArg4_492648  (CKHkS08ElectricGauge::State3Idle, CKHkS08ElectricGauge.h)
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
#include "Renderware/rwcore/RwCamera.h"
#include "Spyro2008/hooks/CKHkS08Clamp.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/logic/IKFxData.h"
#include "k2000/logic/fx/CKExplosionNodeFx.h"
#include "k2000/misc/Engine.h"
#include "k2000/services/CKSrvFx.h"

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

// 0x00491938 CKHkS08Clamp_SpawnFx_maybe: the explosion effect of the FX data +0x44 (the pooled lookup inlined, as
// CKSrvFx::AcquireFx: the data, the reservation, the owner, vt+0x64), placed and triggered. No ReleaseReservation.
void CKGrpS08Clamp::SpawnClampFx(const IKSerializable* owner, const CVector3* position) {
    CKSrvFx* fxService = static_cast<CKSrvFx*>(g_pEngine->m_srvFx);
    CKExplosionNodeFx* fx = static_cast<CKExplosionNodeFx*>(fxService->AcquireFx(static_cast<IKFxData*>(m_pUnk44), owner));
    if (fx == nullptr) return;
    fx->SetTranslation(position, owner);  // 0x001b66e8
    fx->Trigger(owner, 0);                // 0x001b82a8 (its fourth argument 0 as well)
}

// 0x00491cf0 CKGrpS08Clamp_Start
// 0x00491d90 CKGrpS08Clamp_Restart (vt+0x54): the byte +0x3c cleared and the hero activator disabled
// (CKHkHeroActivator_CallSetEnabled 0x448038: its vt+0xcc with 0).
void CKGrpS08Clamp::Restart() {
    m_unk3c = m_unk3c & 0x00ffffffu;  // the byte at +0x3c
    c22spyro::HeroActivatorDisable(static_cast<CKHkHeroActivator*>(m_pUnk40));
}

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

// 0x00491ba0 CKHkS08ClampGun_ReturnClampToPool_maybe
void CKGrpS08Clamp::ReturnClampToPool(IKSerializable* clamp) {
    static_cast<CKHkS08Clamp*>(clamp)->EnterState3();  // 0x0048fcc8
    m_list.SwapIntoActivePartition(clamp);             // 0x00244dc8
}

// 0x00491dc8 CKGrpS08Clamp_MessageProc (vt+0x1c)
int32_t CKGrpS08Clamp::MessageProc(uint16_t message, void* data) {
    if (message != 0x997) return 1;
    // The message's first word: the target, its +0x04..+0x0c a position.
    const uint8_t* target = *static_cast<const uint8_t* const*>(data);
    if (target == nullptr) return 0;
    CKHkS08Clamp* clamp = static_cast<CKHkS08Clamp*>(m_list.PopBack());  // 0x00244b90
    if (clamp == nullptr) return 0;
    clamp->EnterState1();  // 0x0048fb80
    CSGMovable* node = static_cast<CSGMovable*>(clamp->m_pKGLObject);
    node->SetIdentity();  // 0x000d08f0
    const CVector3* position = reinterpret_cast<const CVector3*>(target + 4);
    RwFrame* frame = node->m_pRwFrame;
    frame->modelling.pos.z = position->z;
    frame->modelling.pos.x = position->x;
    frame->modelling.pos.y = position->y;
    frame->modelling.flags &= ~0x20000u;  // rwMATRIXINTERNALIDENTITY
    RwFrame_MarkDirty(frame);  // 0x00010698
    return 0;
}
