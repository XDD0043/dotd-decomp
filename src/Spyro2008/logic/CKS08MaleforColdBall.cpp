// CKS08MaleforColdBall.cpp - reconstructed original translation unit 0x4e9120-0x4ea4c8 (GAME_TOC1, main_toc1), 24 functions, 24 live.
// Primary class: CKS08MaleforColdBall  key 0xabcc  category Logic  size 0xd0  vtable 0xb2a840
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x4e9120  RegisterCKS08MaleforColdBallClass
//   [ ] 0x4e9198  _GLOBAL__I_4e9198
//   [ ] 0x4e91a8  CKS08MaleforColdBall_Explode
//   [ ] 0x4e9500  CKS08MaleforColdBall_ScatterTargetPoints_maybe
//   [ ] 0x4e9658  CKS08MaleforColdBall_vf5C
//   [ ] 0x4e9680  CKS08MaleforColdBall_AttachVolumesToHotSpots_maybe
//   [ ] 0x4e96a8  CKS08MaleforColdBall_StopAttack_maybe
//   [ ] 0x4e96d0  CKS08MaleforColdBall_StartAttack_maybe
//   [ ] 0x4e9710  CKS08MaleforColdBall_PostLoad
//   [ ] 0x4e9850  CKS08MaleforColdBall_Save
//   [ ] 0x4e9878  CKS08MaleforColdBall_RecursiveRegistration
//   [ ] 0x4e98a0  CKS08MaleforColdBall_Destroy
//   [ ] 0x4e98c8  CKS08MaleforColdBall_Destructor
//   [ ] 0x4e9938  CKS08MaleforColdBall_Construct_2
//   [x] 0x4e9998  CKS08MaleforColdBall_Construct
//   [x] 0x4e99f8  CKS08MaleforColdBall_DeleteArray
//   [ ] 0x4e9a98  CKS08MaleforColdBall_DestructBody
//   [ ] 0x4e9b08  CKS08MaleforColdBall_DeletingDestructor
//   [x] 0x4e9b80  CKS08MaleforColdBall_Create
//   [x] 0x4e9bf0  CKS08MaleforColdBall_CreateArray
//   [ ] 0x4e9cd0  CKS08MaleforColdBall_vf64
//   [ ] 0x4e9e00  CKS08MaleforColdBall_LaunchBalls_maybe
//   [ ] 0x4ea078  CKS08MaleforColdBall_Update_maybe
//   [x] 0x4ea110  CKS08MaleforColdBall_Load
//
//   [ ] 0x9c6708  CKS08MaleforColdBall_IsKindOfClass  [inline]
//   [ ] 0x9c6758  CKS08MaleforColdBall_GetClassType  [inline]
//   [ ] 0x9c6760  CKS08MaleforColdBall_GetClassID  [inline]
#include "Spyro2008/logic/CKS08MaleforColdBall.h"

#include "k2000/io/IKFile.h"

// 0x004e9998 CKS08MaleforColdBall_Construct: CKGolemAttackCommon's constructor, then the runtime array header.
CKS08MaleforColdBall::CKS08MaleforColdBall() {
    m_unkb8 = nullptr;
    m_unkbc = 1;
    m_unkc0 = 0;
}

// 0x004ea110 CKS08MaleforColdBall_Load: CKGolemAttackCommon's data, then, for K_LEVEL_PLATEFORMS only, a
// reference, four words and four references.
int32_t CKS08MaleforColdBall::Load(IKFile* file, int32_t type) {
    CKGolemAttackCommon::Load(file, type);
    if (type != 0) return 1;

    IKFile_ReadRef(file, &m_unk98);
    ReadF32LE(file, &m_unkac);
    ReadF32LE(file, &m_unka4);
    ReadS32LE(file, &m_unka8);
    ReadF32LE(file, &m_unkb4);
    IKFile_ReadRef(file, &m_unka0);
    IKFile_ReadRef(file, &m_unk9c);
    IKFile_ReadRef(file, &m_unkc8);
    IKFile_ReadRef(file, &m_unkcc);
    return 1;
}
