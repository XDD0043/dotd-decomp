// CKGrpS08Meca.cpp - reconstructed original translation unit 0x3f9128-0x3f9830 (GAME_TOC1, main_toc1), 23 functions, 23 live.
// Primary class: CKGrpS08Meca  key 0xbc4  category Group  size 0x50  vtable 0xb25170
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x3f9128  CKGrpS08Meca_Delete
//   [ ] 0x3f9178  CKGrpS08Meca_vfB8
//   [ ] 0x3f9180  RegisterCKGrpS08MecaClass
//   [ ] 0x3f91f8  _GLOBAL__I_3f91f8
//   [ ] 0x3f9208  CKGrpS08Meca_Update
//   [ ] 0x3f9230  CKGrpS08Meca_Resume
//   [ ] 0x3f9258  CKGrpS08Meca_Pause
//   [ ] 0x3f9280  CKGrpS08Meca_Stop
//   [x] 0x3f92b8  CKGrpS08Meca_Start
//   [x] 0x3f92f0  CKGrpS08Meca_PostLoad
//   [ ] 0x3f9318  CKGrpS08Meca_Save
//   [ ] 0x3f9340  CKGrpS08Meca_RecursiveRegistration
//   [ ] 0x3f9368  CKGrpS08Meca_Destroy
//   [ ] 0x3f9390  CKGrpS08Meca_DeletingDestructor
//   [ ] 0x3f93d8  CKGrpS08Meca_Destructor
//   [ ] 0x3f9408  CKGrpS08Meca_DestructBody
//   [x] 0x3f9438  CKGrpS08Meca_Construct
//   [x] 0x3f9470  CKGrpS08Meca_Construct_2
//   [x] 0x3f94a8  CKGrpS08Meca_DeleteArray
//   [ ] 0x3f9550  CKGrpS08Meca_Restart
//   [x] 0x3f9560  CKGrpS08Meca_CreateArray
//   [x] 0x3f9618  CKGrpS08Meca_Create
//   [x] 0x3f9670  CKGrpS08Meca_Load
//
//   [ ] 0x9c0e40  CKGrpS08Meca_IsKindOfClass  [inline]
//   [x] 0x9c0ea0  CKGrpS08Meca_GetClassType  [inline]
//   [x] 0x9c0ea8  CKGrpS08Meca_GetClassID  [inline]
//   [ ] 0x9c0eb0  CKGrpS08Meca_vfCC  [inline]
#include "Spyro2008/groups/CKGrpS08Meca.h"
#include "k2000/misc/CKMecaCpntBase.h"

// 0x003f9670 CKGrpS08Meca_Load
int32_t CKGrpS08Meca::Load(IKFile* file, int32_t type) {
    CKGrpMeca::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        IKFile_ReadRef(file, &m_pUnk40);
        IKFile_ReadRef(file, &m_pUnk44);
        IKFile_ReadRef(file, &m_pUnk48);
    }
    return 1;
}

// 0x003f92f0 CKGrpS08Meca_PostLoad: CKGrpMeca's.
int32_t CKGrpS08Meca::PostLoad(int32_t type) {
    CKGrpMeca::PostLoad(type);  // 0x003f82f8
    return 1;
}

// 0x003f92b8 CKGrpS08Meca_Start
void CKGrpS08Meca::Start() {
    // 0x003f81c0 CKGrpMeca_vf50 (k2000/misc/CKGrpMeca.cpp, family hooks; local copy): the halfword at +0x30 and
    // the byte at +0x32 cleared (the first three bytes of the big-endian word), then every component's vt+0x58.
    m_unk30 = m_unk30 & 0x000000ffu;
    for (uint32_t i = 0; i < m_apMecaCpnts.m_ui32NbUsedElt; ++i) {
        static_cast<IKMecaCpnt*>(m_apMecaCpnts.m_pBlock[i])->Vf58();
    }
    m_unk4c = m_unk4c & 0x00ffffffu;  // the byte at +0x4c
}
