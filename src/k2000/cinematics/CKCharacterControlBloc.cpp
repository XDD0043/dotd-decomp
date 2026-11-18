// CKCharacterControlBloc.cpp - reconstructed original translation unit 0x175918-0x1766f0 (GAME_TOC1, main_toc1), 15 functions, 15 live.
// Primary class: CKCharacterControlBloc  key 0x348  category CinematicNode  size 0x40  vtable 0xb1b138
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x175918  CKCharacterControlBloc_Delete
//   [x] 0x175968  CKCharacterControlBloc_Abort
//   [ ] 0x1759c0  RegisterCKCharacterControlBlocClass
//   [ ] 0x175a38  _GLOBAL__I_175a38
//   [x] 0x175a48  CKCharacterControlBloc_Stop
//   [x] 0x175c28  CKCharacterControlBloc_Update
//   [ ] 0x175d00  CKCharacterControlBloc_Save
//   [x] 0x175d28  CKCharacterControlBloc_RecursiveRegistration
//   [x] 0x175e40  CKCharacterControlBloc_DeleteArray
//   [x] 0x175ee0  CKCharacterControlBloc_CreateArray
//   [x] 0x175f90  CKCharacterControlBloc_Destroy  (empty: the default)
//   [x] 0x175f98  CKCharacterControlBloc_Create
//   [x] 0x175ff0  CKCharacterControlBloc_Start
//   [x] 0x1763b0  CKCharacterControlBloc_Load
//   [x] 0x176500  CKCharacterControlBloc_Complete
//
//   [ ] 0x9a9470  CKCharacterControlBloc_IsKindOfClass  [inline]
//   [ ] 0x9a94a8  CKCharacterControlBloc_GetClassType  [inline]
//   [ ] 0x9a94b0  CKCharacterControlBloc_GetClassID  [inline]
//   [ ] 0x9a94b8  CKCharacterControlBloc_PreActivate  [inline]
//   [ ] 0x9a94c0  CKCharacterControlBloc_Destructor  [inline]
//   [ ] 0x9a94e0  CKCharacterControlBloc_DeletingDestructor  [inline]
#include "k2000/cinematics/CKCharacterControlBloc.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/misc/Engine.h"

#include "k2000/core/Stub.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKControlableHero.h"
#include "k2000/logic/ai/CKMarkerBeacon.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/math/Quat.h"

// 0x001763b0 CKCharacterControlBloc_Load
int32_t CKCharacterControlBloc::Load(IKFile* file, int32_t type) {
    BasicLoadCinematicElement(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        IKFile_ReadRef(file, &m_unk38);
        IKFile_ReadRef(file, &m_unk3c);
    }
    return 1;
}

// The controllable hero's slots vt+0x50 / +0x54 / +0x58 (CKControlableHero: BindAndAttachHero, UpdateMoveTo, DetachHero;
// k2000/logic/CKControlableHero.cpp). The bloc passes itself as a fourth argument to vt+0x50, which does not read it.

// 0x00175ff0 CKCharacterControlBloc_Start
void CKCharacterControlBloc::Start() {
    StartCommon();
    CVector3 position;
    CVector3 direction;
    const CKMarkerBeacon* marker = static_cast<CKMarkerBeacon*>(m_unk3c);
    if (marker != nullptr) {
        alignas(16) CMatrix34 matrix;
        Quat_ToMatrixNormalizing(marker->m_qOrientation, &matrix);  // 0x00241d78
        matrix.m_pos = marker->m_v3Position;
        matrix.m_ui32Flags &= 0xfffdffffu;
        position = matrix.m_pos;
        direction = matrix.m_at;
    } else {
        position = CVector3{0.0f, 0.0f, 0.0f};   // 0x00c50d64
        direction = CVector3{0.0f, 0.0f, 0.0f};  // 0x00c50d4c
    }
    if (m_unk38 != nullptr) static_cast<CKControlableHero*>(m_unk38)->BindAndAttachHero(&position, &direction);  // vt+0x50
}

// 0x00175c28 CKCharacterControlBloc_Update
void CKCharacterControlBloc::Update(IKTime* time) {
    if (CheckSekensStop() == 0) return;
    if (m_unk38 == nullptr) return;
    if (static_cast<CKControlableHero*>(m_unk38)->UpdateMoveTo(time) != 0) Complete();  // vt+0x54, vt+0x64
}

// 0x00176500 CKCharacterControlBloc_Complete
void CKCharacterControlBloc::Complete() {
    CompleteBloc();
    if (m_unk38 != nullptr) static_cast<CKControlableHero*>(m_unk38)->DetachHero();  // vt+0x58
}

// 0x00175968 CKCharacterControlBloc_Abort
void CKCharacterControlBloc::Abort() {
    m_DataFlags &= 0xfffffffeu;
    Complete();  // vt+0x64
}

// 0x00175a48 CKCharacterControlBloc_Stop
void CKCharacterControlBloc::Stop() {
    CompleteBloc();
    Complete();  // vt+0x64
}

// 0x00175d28 CKCharacterControlBloc_RecursiveRegistration
void CKCharacterControlBloc::RecursiveRegistration(int32_t type) {
    if (static_cast<uint32_t>(type - 4) > 3u) g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);
    IKCinematicBloc::RecursiveRegistration(type);  // 0x0018e8d8
    if (type != 0) return;
    if (m_unk38 != nullptr) m_unk38->RecursiveRegistration(0);  // vt+0x24
    if (m_unk3c != nullptr) m_unk3c->RecursiveRegistration(0);
}
