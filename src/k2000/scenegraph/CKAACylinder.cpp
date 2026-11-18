// CKAACylinder.cpp - reconstructed original translation unit 0xd65c0-0xd6e60 (GAME_TOC1, main_toc1), 11 functions, 11 live.
// Primary class: CKAACylinder  key 0x60b  category SceneNode  size 0x34  vtable 0xb18710
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0xd65c0  CKAACylinder_Delete
//   [x] 0xd6610  CKAACylinder_GetShapeType_maybe
//   [ ] 0xd6618  RegisterCKAACylinderClass
//   [ ] 0xd6690  _GLOBAL__I_d6690
//   [x] 0xd66a0  CKAACylinder_DeleteArray
//   [x] 0xd6740  CKAACylinder_Create
//   [x] 0xd67b0  CKAACylinder_CreateArray
//   [x] 0xd6898  CKAACylinder_Destroy  (inherited: CSGLeaf_Destroy)
//   [x] 0xd68c0  CKAACylinder_RecursiveRegistration  (CSGLeaf's (nothing))
//   [x] 0xd68e8  CKAACylinder_Load
//   [ ] 0xd6ab0  CKAACylinder_Save
//
//   [ ] 0x9a3ba0  CKAACylinder_GetClassType  [inline]
//   [ ] 0x9a3ba8  CKAACylinder_GetClassID  [inline]
//   [ ] 0x9a3bb0  CKAACylinder_DeletingDestructor  [inline]
//   [ ] 0x9a3c08  CKAACylinder_IsKindOfClass  [inline]
//   [ ] 0x9a3c50  CKAACylinder_Destructor  [inline]
#include "k2000/scenegraph/CKAACylinder.h"

#include <cstring>

#include "k2000/io/IKFile.h"

// 0x000d68e8 CKAACylinder_Load
int32_t CKAACylinder::Load(IKFile* file, int32_t type) {
    IKBoundingVolume::Load(file, type);
    uint32_t words[2];
    ReadU32LEWords(file, words, 2);
    std::memcpy(&m_fCylinderRadius, &words[0], 4);
    std::memcpy(&m_fCylinderHalfHeight, &words[1], 4);
    return 1;
}
