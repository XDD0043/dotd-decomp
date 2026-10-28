// CKHkS08Sparx.cpp - reconstructed original translation unit 0x3f4108-0x3f6dc0 (GAME_TOC1, main_toc1), 45 functions, 38 live.
// Primary class: CKHkS08Sparx  key 0x3282  category Hook  size 0xd4  vtable 0xb24be8
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x3f4108  CKHkS08Sparx_Delete
//   [x] 0x3f4158  CKHkS08Sparx_Construct  [dead]
//   [ ] 0x3f41d8  CKHkS08Sparx_ResetRuntime_2  [dead]
//   [ ] 0x3f4250  CKHkS08Sparx_Stop
//   [ ] 0x3f4258  CKHkS08Sparx_Pause
//   [ ] 0x3f4260  CKHkS08Sparx_Resume
//   [ ] 0x3f4268  CKHkS08Sparx_SetTarget_maybe
//   [ ] 0x3f4318  CKHkS08Sparx_StopMoveUpdaterIfCurrent_maybe
//   [ ] 0x3f4378  CKHkS08Sparx_AddNodeAnimTime_maybe  [dead]
//   [ ] 0x3f43a0  CKHkS08Sparx_ResolveWallCollision_maybe  [dead]
//   [ ] 0x3f44d0  CKHkS08Sparx_ProbeGround_maybe  [dead]
//   [x] 0x3f4540  CKHkS08Sparx_PostLoad
//   [ ] 0x3f4598  CKHkS08Sparx_Save
//   [ ] 0x3f45c0  CKHkS08Sparx_RecursiveRegistration
//   [ ] 0x3f45e8  CKHkS08Sparx_Destroy
//   [x] 0x3f4610  CKHkS08Sparx_DeleteArray
//   [ ] 0x3f46b0  CKHkS08Sparx_SetDirectionVec_maybe
//   [ ] 0x3f46d0  RegisterCKHkS08SparxClass
//   [ ] 0x3f4758  _GLOBAL__D_3f4758
//   [ ] 0x3f4768  _GLOBAL__I_3f4768
//   [ ] 0x3f4778  CKHkS08Sparx_Construct_2  [dead]
//   [ ] 0x3f47f8  CKHkS08Sparx_ResetMoveTargetToCurrentPosition_maybe
//   [ ] 0x3f4850  CKHkS08Sparx_SetMoveGoalPosDirFloat70_maybe
//   [ ] 0x3f48a8  CKHkS08Sparx_ClearTargetIfCurrentAndPlayAnim_maybe
//   [ ] 0x3f4938  CKHkS08Sparx_StartMoveUpdater_maybe
//   [ ] 0x3f4a58  CKHkS08Sparx_GetInfo
//   [ ] 0x3f4a60  CKHkS08Sparx_MessageProc
//   [ ] 0x3f4a70  CKHkS08Sparx_SetDefaultState
//   [ ] 0x3f4a78  CKHkS08Sparx_SetGameState
//   [ ] 0x3f4a80  CKHkS08Sparx_OnDeactivate
//   [x] 0x3f4b20  CKHkS08Sparx_CreateArray
//   [x] 0x3f4c28  CreateCKHkS08Sparx
//   [ ] 0x3f4cc0  CKHkS08Sparx_SetPositionAndDirection_maybe
//   [ ] 0x3f4dc8  CKHkS08Sparx_Destructor
//   [ ] 0x3f4de8  CKHkS08Sparx_PickRandomPointAround_maybe
//   [ ] 0x3f52d0  CKHkS08Sparx_PlaceNearFocusedHero_maybe
//   [ ] 0x3f5488  CKHkS08Sparx_OnActivate
//   [ ] 0x3f5568  CKHkS08Sparx_SteerTowardTarget_maybe
//   [ ] 0x3f5c38  CKHkS08Sparx_MoveTowardTarget_maybe
//   [ ] 0x3f5da8  UpdateCKHkS08Sparx
//   [ ] 0x3f66e8  CKHkS08Sparx_Restart
//   [x] 0x3f67e8  CKHkS08Sparx_Start
//   [x] 0x3f6860  CKHkS08Sparx_Load
//   [ ] 0x3f6d58  CKHkS08Sparx_Destructor_2  [dead]
//   [ ] 0x3f6d78  CKHkS08Sparx_DeletingDestructor
//
//   [ ] 0x9c0b18  CKHkS08Sparx_IsKindOfClass  [inline]
//   [ ] 0x9c0b60  CKHkS08Sparx_GetClassType  [inline]
//   [ ] 0x9c0b68  CKHkS08Sparx_GetClassID  [inline]
#include "Spyro2008/hooks/CKHkS08Sparx.h"

#include "k2000/io/IKFile.h"
#include "k2000/misc/Mat4.h"

// 0x003f4540 CKHkS08Sparx_PostLoad: IKLife_PostLoad 0x19f68 (level type only: bit 2 of the bit array), then for the
// level type a matrix (RwMatrixCreate_Thunk) at +0xc4.
int32_t CKHkS08Sparx::PostLoad(int32_t type) {
    if (type == K_LEVEL_PLATEFORMS) m_bitArray = (m_bitArray & 0xfffffffbu) | 4u;
    if (type == K_LEVEL_PLATEFORMS) m_pMatrixC4 = RwMatrixCreate_Thunk();
    return 1;
}

// 0x003f6860 CKHkS08Sparx_Load
int32_t CKHkS08Sparx::Load(IKFile* file, int32_t type) {
    IKHook::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    IKFile_ReadRef(file, &m_pAnimationDictionary);
    IKFile_ReadRef(file, &m_pParticlesNode);
    IKFile_ReadRef(file, &m_pGlowNode);
    IKFile_ReadRef(file, &m_pPointLightFxData);
    IKFile_ReadRef(file, &m_pNode);
    ReadF32LE(file, &m_fl2c);
    ReadF32LE(file, &m_fl30);
    ReadF32LE(file, &m_fl34);
    ReadF32LE(file, &m_fl38);
    ReadF32LE(file, &m_fl3c);
    ReadF32LE(file, &m_fl40);
    ReadF32LE(file, &m_fl44);
    ReadF32LE(file, &m_fl48);
    return 1;
}

// 0x003f67e8 CKHkS08Sparx_Start
void CKHkS08Sparx::Start() {
    m_unk54[0] = (m_unk54[0] & 0xffffffecu) | 0x10u;
    m_unk54[9] = 0;  // +0x78
    m_unk54[8] = 0;  // +0x74
    m_GContactIn.m_MasksOfGrdForTest[0] = 1;
    m_GContactIn.m_MasksOfGrdForTest[1] = 0;
    m_GContactIn.m_fDeltaMax = 0.1f;      // TOC +0x44a8 (0x3dcccccd)
    m_GContactIn.m_fObjectHeight = 1.0f;  // TOC +0x44ac
    m_GContactInOut.m_i32FaceIndex = -1;
    m_GContactInOut.m_eContactStatus = 3;
    m_GContactInOut.m_ui8SectorNumber = 0;
    m_GContactInOut.m_pGround = nullptr;
    m_unkB8[2] = 0;  // +0xc0
    m_unkB8[0] = 0;  // +0xb8
}
