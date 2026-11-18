// CSGSectorRoot.cpp - reconstructed original translation unit 0xd2e28-0xd32b8 (GAME_TOC1, main_toc1), 12 functions, 12 live.
// Primary class: CSGSectorRoot  key 0x8b  category SceneNode  size 0x2c  vtable 0xb183c0
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0xd2e28  CSGSectorRoot_Delete
//   [x] 0xd2e78  CSGSectorRoot_GetSectorIndex_maybe  (GetSectorIndex, CSGSectorRoot.h)
//   [ ] 0xd2e80  RegisterCSGSectorRootClass
//   [ ] 0xd2ef8  _GLOBAL__I_d2ef8
//   [x] 0xd2f08  CSGSectorRoot_PostLoad  (= the inherited slot)
//   [x] 0xd2f30  CSGSectorRoot_Load
//   [ ] 0xd3068  CSGSectorRoot_Save
//   [x] 0xd3090  CSGSectorRoot_RecursiveRegistration  (CNode's (nothing))
//   [x] 0xd30b8  CSGSectorRoot_Destroy  (CNode's: inherited)
//   [x] 0xd30e0  CSGSectorRoot_DeleteArray
//   [x] 0xd3180  CreateCSGSectorRoot
//   [x] 0xd31e8  CSGSectorRoot_CreateArray
//
//   [ ] 0x9a2a10  CSGSectorRoot_IsKindOfClass  [inline]
//   [x] 0x9a2a68  CSGSectorRoot_GetClassType  [inline]
//   [x] 0x9a2a70  CSGSectorRoot_GetClassID  [inline]
//   [ ] 0x9a2a78  CSGSectorRoot_DeletingDestructor  [inline]
//   [ ] 0x9a2ac0  CSGSectorRoot_Destructor  [inline]
#include "k2000/scenegraph/CSGSectorRoot.h"

#include "k2000/io/IKFile.h"

// Inlined in 0x000d3180 CreateCSGSectorRoot (the stores: +0x28, then +0x24; CSGSectorRoot_CreateArray
// 0x000d31e8 stores them the other way round).
CSGSectorRoot::CSGSectorRoot() {
    m_tSectorIndex = 0xfffffffe;
    m_pTextureDictionary = nullptr;
}

// 0x000d2f30 CSGSectorRoot_Load: the sector's own fields only in level files.
int32_t CSGSectorRoot::Load(IKFile* file, int32_t type) {
    CNode::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadU32LE(file, &m_tSectorIndex);
    IKFile_ReadRef(file, &m_pTextureDictionary);
    return 1;
}
