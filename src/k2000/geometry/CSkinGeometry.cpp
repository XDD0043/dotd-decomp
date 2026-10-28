// CSkinGeometry.cpp - reconstructed original translation unit 0x8b218-0x8b918 (GAME_TOC1, main_toc1), 28 functions, 10 live.
// Primary class: CSkinGeometry  key 0xca  category Geometry  size 0x30  vtable 0xb16a68
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x8b218  CSkinGeometry_Delete
//   [ ] 0x8b268  CSkinGeometry_Save
//   [x] 0x8b290  CSkinGeometry_Load
//   [x] 0x8b2b8  CSkinGeometry_PostLoad
//   [ ] 0x8b2e0  RegisterCSkinGeometryClass
//   [ ] 0x8b358  _GLOBAL__I_8b358
//   [x] 0x8b368  CSkinGeometry_SetHAnimHierarchy_maybe
//   [x] 0x8b390  CSkinGeometry_DeleteArray
//   [x] 0x8b438  CSkinGeometry_CreateArray
//   [x] 0x8b500  CSkinGeometry_Create
//   [ ] 0x8b568  FUN_0008b568  [dead]
//   [ ] 0x8b5a0  KStub_Nop_8b5a0  [dead]
//   [ ] 0x8b5a8  KStub_Nop_8b5a8  [dead]
//   [ ] 0x8b5b0  FUN_0008b5b0  [dead]
//   [ ] 0x8b5d8  FUN_0008b5d8  [dead]
//   [ ] 0x8b610  FUN_0008b610  [dead]
//   [ ] 0x8b670  KStub_Nop_8b670  [dead]
//   [ ] 0x8b678  KStub_Nop_8b678  [dead]
//   [ ] 0x8b680  FUN_0008b680  [dead]
//   [ ] 0x8b6f0  KStub_Nop_8b6f0  [dead]
//   [ ] 0x8b6f8  FUN_0008b6f8  [dead]
//   [ ] 0x8b778  FUN_0008b778  [dead]
//   [ ] 0x8b7f8  FUN_0008b7f8  [dead]
//   [ ] 0x8b888  KStub_Nop_8b888  [dead]
//   [ ] 0x8b890  KStub_Nop_8b890  [dead]
//   [ ] 0x8b898  KStub_Nop_8b898  [dead]
//   [ ] 0x8b8a0  FUN_0008b8a0  [dead]
//   [ ] 0x8b910  KStub_Nop_8b910  [dead]
//
//   [ ] 0x99c3b0  CSkinGeometry_GetClassType  [inline]
//   [ ] 0x99c3b8  CSkinGeometry_GetClassID  [inline]
//   [ ] 0x99c3c0  CSkinGeometry_IsKindOfClass  [inline]
//   [ ] 0x99c3f8  CSkinGeometry_DeletingDestructor  [inline]
//   [ ] 0x99c440  CSkinGeometry_Destructor  [inline]
#include "k2000/geometry/CSkinGeometry.h"

#include "Renderware/rpskin/RpSkin.h"

// 0x0008b290 CSkinGeometry_Load
int32_t CSkinGeometry::Load(IKFile* file, int32_t type) {
    CGeometry::Load(file, type);  // 0x892a0
    return 1;
}

// 0x0008b2b8 CSkinGeometry_PostLoad: CGeometry's, then 1.
int32_t CSkinGeometry::PostLoad(int32_t type) {
    CGeometry::PostLoad(type);  // 0x88c90
    return 1;
}

// 0x0008b368 CSkinGeometry_SetHAnimHierarchy_maybe
void CSkinGeometry_SetHAnimHierarchy(CGeometry* geometry, RpHAnimHierarchy* hierarchy) {
    RpSkinAtomicSetHAnimHierarchy(geometry->m_pRpAtomic, hierarchy);  // 0x772ef8 (the TOC bridge inlined)
}
