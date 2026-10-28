// CKHkS08Clamp.cpp - reconstructed original translation unit 0x48c7a0-0x4916f8 (GAME_TOC1, main_toc1), 55 functions, 44 live.
// Primary class: CKHkS08Clamp  key 0x2c82  category Hook  size 0x130  vtable 0xb27ee8
// Other owners: GetSpyroCynderMidpoint (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x48c7a0  CKHkS08Clamp_Delete
//   [ ] 0x48c7f0  CKHkS08Clamp_UpdateSegmentVolumeFromNode_maybe  [dead]
//   [ ] 0x48c8e8  FUN_0048c8e8  [dead]
//   [ ] 0x48c958  CKHkS08Clamp_ReflectVelocity_maybe  [dead]
//   [ ] 0x48c9d8  CKHkS08Clamp_InitCollisionVolume_maybe  [dead]
//   [ ] 0x48ca50  CKHkS08Clamp_IsPointInsideQuadXZ_maybe  [dead]
//   [ ] 0x48cbb0  CKHkS08Clamp_SetDefaultState
//   [ ] 0x48cbc0  CKHkS08Clamp_vfC8
//   [ ] 0x48cbc8  CKHkS08Clamp_SpawnFxAtNodePosition_maybe  [dead]
//   [ ] 0x48cc10  GetSpyroCynderMidpoint_maybe
//   [ ] 0x48cd00  CKHkS08Clamp_GetDistSqToHeroLink_maybe
//   [ ] 0x48cef8  CKHkS08Clamp_UpdateRotationBlend_maybe
//   [ ] 0x48d0e8  CKHkS08Clamp_SpinAroundAxis_maybe  [dead]
//   [ ] 0x48d180  CKHkS08Clamp_Resume
//   [ ] 0x48d1a8  CKHkS08Clamp_Pause
//   [ ] 0x48d1d0  CKHkS08Clamp_GetInfo
//   [ ] 0x48d220  CKHkS08Clamp_Save
//   [ ] 0x48d248  CKHkS08Clamp_RecursiveRegistration
//   [ ] 0x48d270  CKHkS08Clamp_Destroy
//   [x] 0x48d2b8  CKHkS08Clamp_Construct  [dead]
//   [x] 0x48d330  CKHkS08Clamp_DeleteArray
//   [ ] 0x48d3d0  CKHkS08Clamp_Destructor_2  [dead]
//   [ ] 0x48d448  CKHkS08Clamp_Construct_2  [dead]
//   [ ] 0x48d4c0  RegisterCKHkS08ClampClass
//   [ ] 0x48d548  _GLOBAL__D_48d548
//   [ ] 0x48d558  _GLOBAL__I_48d558
//   [ ] 0x48d568  CKHkS08Clamp_IsInState2
//   [ ] 0x48d580  CKHkS08Clamp_State3_Inactive_maybe
//   [ ] 0x48d648  CKHkS08Clamp_OnActivate
//   [ ] 0x48d6e0  CKHkS08Clamp_DeletingDestructor
//   [ ] 0x48d768  CKHkS08Clamp_Destructor
//   [ ] 0x48d7e0  CKHkS08Clamp_vf94
//   [ ] 0x48d7e8  CKHkS08Clamp_vf98
//   [ ] 0x48d7f0  CKHkS08Clamp_OnContactHit_maybe
//   [ ] 0x48d9c8  CKHkS08Clamp_ProcessContacts_maybe
//   [x] 0x48dbc0  CKHkS08Clamp_PostLoad
//   [ ] 0x48dcb8  CKHkS08Clamp_UpdateMotionAndSpin_maybe  [dead]
//   [ ] 0x48ddc8  CKHkS08Clamp_PlaySound1AndSpawnFx_maybe
//   [ ] 0x48df08  CKHkS08Clamp_State1
//   [x] 0x48e140  CKHkS08Clamp_CreateArray
//   [x] 0x48e240  CKHkS08Clamp_Create
//   [ ] 0x48e2c8  CKHkS08Clamp_UpdateGroundImpact_maybe
//   [ ] 0x48e828  CKHkS08Clamp_State2
//   [x] 0x48ee18  CKHkS08Clamp_Load
//   [ ] 0x48f330  CKHkS08Clamp_LaunchRandomDirection_maybe
//   [ ] 0x48f8d8  CKHkS08Clamp_Update
//   [ ] 0x48fb80  CKHkS08Clamp_EnterState1_maybe
//   [ ] 0x48fcc8  CKHkS08Clamp_EnterState3_maybe
//   [ ] 0x48fe08  CKHkS08Clamp_MessageProc
//   [ ] 0x490008  CKHkS08Clamp_Launch_maybe
//   [ ] 0x490210  CKHkS08Clamp_Restart
//   [ ] 0x4903f0  CKHkS08Clamp_UpdateCollisionVolumesFromBones_maybe
//   [ ] 0x490cc8  CKHkS08Clamp_State0
//   [ ] 0x491338  CKHkS08Clamp_Stop
//   [ ] 0x4913d8  CKHkS08Clamp_Start
//
//   [ ] 0x9c4940  CKHkS08Clamp_IsKindOfClass  [inline]
//   [ ] 0x9c4998  CKHkS08Clamp_GetClassType  [inline]
//   [ ] 0x9c49a0  CKHkS08Clamp_GetClassID  [inline]
#include "Spyro2008/hooks/CKHkS08Clamp.h"

#include "Renderware/rwcore/RwMatrix.h"
#include "Spyro2008/groups/CKGrpS08Meca.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/IKBoundingVolume.h"

// 0x0048dbc0 CKHkS08Clamp_PostLoad: the clamp group (the game manager's third reference, a CKGrpS08Meca, its
// +0x40) becomes the context, two new matrices, and the collision sphere at +0x2c is set up as this hook's
// (owner type 1, owner this, bit 7 of its info byte, the radius from +0xe0 when that is positive, else 0.001).
int32_t CKHkS08Clamp::PostLoad(int32_t type) {
    CKHkActorBase::PostLoad(type);  // 0x003f6e70
    m_pUnk24 = static_cast<CKGrpS08Meca*>(static_cast<CDefaultGameManager*>(g_pEngine->m_gameManager)->m_unk04[2])
                   ->m_pUnk40;
    m_pUnk40 = reinterpret_cast<CMatrix34*>(RwMatrixCreate());  // RwMatrixCreate_Thunk 0x23fa68
    m_pUnk3C = reinterpret_cast<CMatrix34*>(RwMatrixCreate());
    IKBoundingVolume* volume = static_cast<IKBoundingVolume*>(m_pUnk2C);
    volume->m_ui16PropertiesFlags = 0;
    volume->m_ui8OwnerType = 1;  // (the original stores 0, then 1)
    volume->m_pOwner = this;
    volume->m_ba8Infos = (volume->m_ba8Infos & 0x7f) | 0x80;
    if (0.0f < m_fUnkE0) {
        volume->m_fRadius = m_fUnkE0;
    } else {
        volume->m_fRadius = 0.001f;  // TOC1 +0x1788: 0x3a83126f
    }
    m_unk20 = m_unk20 & 0x00ffffffu;  // the byte at +0x20
    return 1;
}

// 0x0048ee18 CKHkS08Clamp_Load: the actor base, then the level data (type 0 only).
int32_t CKHkS08Clamp::Load(IKFile* file, int32_t type) {
    CKHkActorBase::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        ReadF32LE(file, &m_fUnk38);
        ReadF32LE(file, &m_fUnkDC);
        ReadF32LE(file, &m_fUnkE0);
        ReadF32LE(file, &m_fUnk78);
        ReadF32LE(file, &m_fUnk74);
        ReadF32LE(file, &m_fUnk7C);
        ReadF32LE(file, &m_fUnk8C);
        ReadF32LE(file, &m_fUnk90);
        ReadF32LE(file, &m_fUnkE4);
        IKFile_ReadRef(file, &m_pUnk2C);
        ReadF32LE(file, &m_fUnk94);
        ReadF32LE(file, &m_fUnk44);
        IKFile_ReadRef(file, &m_pUnkEC);
        IKFile_ReadRef(file, &m_pUnkF8);
        ReadF32LE(file, &m_fUnkFC);
        ReadU32LE(file, &m_unk100);
        ReadU8(file, &m_unk104);
    }
    return 1;
}
