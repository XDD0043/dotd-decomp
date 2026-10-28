// CKS08MaleforFireBreath.cpp - reconstructed original translation unit 0x4ea4c8-0x4eafb0 (GAME_TOC1, main_toc1), 23 functions, 23 live.
// Primary class: CKS08MaleforFireBreath  key 0xac4c  category Logic  size 0x130  vtable 0xb2a8f0
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x4ea4c8  CKS08MaleforFireBreath_Delete
//   [ ] 0x4ea518  CKS08MaleforFireBreath_vf64
//   [ ] 0x4ea520  CKS08MaleforFireBreath_vf5C
//   [ ] 0x4ea548  CKS08MaleforFireBreath_AttachVolumesToHotSpots_maybe
//   [ ] 0x4ea570  CKS08MaleforFireBreath_StopAttack_maybe
//   [ ] 0x4ea608  CKS08MaleforFireBreath_StartAttack_maybe
//   [ ] 0x4ea650  CKS08MaleforFireBreath_PostLoad
//   [ ] 0x4ea6c8  CKS08MaleforFireBreath_Save
//   [ ] 0x4ea6f0  CKS08MaleforFireBreath_RecursiveRegistration
//   [ ] 0x4ea718  CKS08MaleforFireBreath_Destroy
//   [ ] 0x4ea780  CKS08MaleforFireBreath_DeletingDestructor
//   [ ] 0x4ea7c8  CKS08MaleforFireBreath_Destructor
//   [ ] 0x4ea7f8  CKS08MaleforFireBreath_DestructBody
//   [ ] 0x4ea828  CKS08MaleforFireBreath_Construct_2
//   [x] 0x4ea860  CKS08MaleforFireBreath_Construct
//   [x] 0x4ea898  CKS08MaleforFireBreath_DeleteArray
//   [ ] 0x4ea938  RegisterCKS08MaleforFireBreathClass
//   [ ] 0x4ea9c0  _GLOBAL__D_4ea9c0
//   [ ] 0x4ea9d0  _GLOBAL__I_4ea9d0
//   [ ] 0x4ea9e0  CKS08MaleforFireBreath_Update_maybe
//   [x] 0x4eab58  CKS08MaleforFireBreath_Create
//   [x] 0x4eabb0  CKS08MaleforFireBreath_CreateArray
//   [x] 0x4eac60  CKS08MaleforFireBreath_Load
//
//   [ ] 0x9c6768  CKS08MaleforFireBreath_IsKindOfClass  [inline]
//   [ ] 0x9c67b8  CKS08MaleforFireBreath_GetClassType  [inline]
//   [ ] 0x9c67c0  CKS08MaleforFireBreath_GetClassID  [inline]
#include "Spyro2008/logic/CKS08MaleforFireBreath.h"

#include "k2000/io/IKFile.h"

// 0x004eac60 CKS08MaleforFireBreath_Load: CKGolemAttackCommon's data, then, for K_LEVEL_PLATEFORMS only, two
// floats, a reference and eight groups of four references.
int32_t CKS08MaleforFireBreath::Load(IKFile* file, int32_t type) {
    CKGolemAttackCommon::Load(file, type);
    if (type != 0) return 1;

    ReadF32LE(file, &m_unk120);
    ReadF32LE(file, &m_unk124);
    IKFile_ReadRef(file, &m_unk12c);
    for (int32_t i = 0; i < 8; ++i) {
        IKFile_ReadRef(file, &m_unk98[i].m_unk00);
        IKFile_ReadRef(file, &m_unk98[i].m_unk04);
        IKFile_ReadRef(file, &m_unk98[i].m_unk08);
        IKFile_ReadRef(file, &m_unk98[i].m_unk0c);
    }
    return 1;
}
