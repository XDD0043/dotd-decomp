// CKGrpMeca.cpp - reconstructed original translation unit 0x3f8130-0x3f8ba8 (GAME_TOC1, main_toc1), 17 functions, 15 live.
// Primary owner: CKGrpMeca (not a registered class)
// Other owners: CKGrpS08Meca (4), ActiveActorList (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x3f8130  CKGrpS08Meca_ConstructBase_maybe
//   [x] 0x3f81c0  CKGrpMeca_vf50
//   [ ] 0x3f8268  CKGrpS08Meca_vfA8
//   [x] 0x3f82f8  CKGrpMeca_PostLoad
//   [ ] 0x3f8340  CKGrpMeca_FreeBuffer_maybe  [dead]
//   [ ] 0x3f8368  CKGrpMeca_UpdateMembers_maybe
//   [ ] 0x3f8480  CKGrpMeca_OnLevelExit
//   [ ] 0x3f8508  ActiveActorList_Remove_maybe
//   [ ] 0x3f8630  CKGrpS08Meca_vfAC
//   [ ] 0x3f86c0  CKGrpS08Meca_ConstructBase_2_maybe  [dead]
//   [ ] 0x3f8750  CKGrpMeca_Save
//   [x] 0x3f8778  CKGrpMeca_Load
//   [ ] 0x3f8988  CKGrpMeca_LevelReset
//   [ ] 0x3f89b0  CKGrpMeca_ClearReferences
//   [ ] 0x3f8a20  CKGrpMeca_Destructor
//   [ ] 0x3f8aa0  CKGrpMeca_DeletingDestructor
//   [ ] 0x3f8b28  CKGrpMeca_BaseDestructor
//
//   [x] 0x9c0d60  CKGrpMeca_GetClassGroup  [inline]
//   [x] 0x9c0d68  CKGrpMeca_GetClassId  [inline]
//   [ ] 0x9c0d70  CKGrpMeca_vfCC  [inline]
//   [ ] 0x9c0d78  CKGrpMeca_IsKindOf  [inline]
#include "k2000/misc/CKGrpMeca.h"

#include "k2000/groups/TVectorPush.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/CKMecaCpntBase.h"

// 0x003f8778 CKGrpMeca_Load. A u16 count; without components the capacity is 10 and the Load returns.
int32_t CKGrpMeca::Load(IKFile* file, int32_t type) {
    GroupBasicLoad(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    uint16_t count = 0;
    ReadU16LE(file, &count);
    TVector_ResizeForLoad(m_apMecaCpnts, count);
    for (uint32_t i = 0; i < count; ++i) IKFile_ReadRef(file, &m_apMecaCpnts.m_pBlock[i]);
    return 1;
}

// 0x003f82f8 CKGrpMeca_PostLoad: IKLife_PostLoad, then 300 words (4 bytes each) at +0x2c whatever the type.
int32_t CKGrpMeca::PostLoad(int32_t type) {
    PostLoadLife(type);
    m_pUnk2c = Mem_CallocAligned16(4, 300);
    return 1;
}

// 0x003f81c0 CKGrpMeca_vf50 (the Start): the halfword +0x30 cleared, every mechanism component told (vt+0x58),
// then the byte +0x32 cleared.
void CKGrpMeca::Start() {
    m_unk30 = 0;
    for (uint32_t i = 0; i < m_apMecaCpnts.m_ui32NbUsedElt; ++i) {
        static_cast<IKMecaCpnt*>(m_apMecaCpnts.m_pBlock[i])->Vf58();
    }
    m_unk32 = 0;
}
