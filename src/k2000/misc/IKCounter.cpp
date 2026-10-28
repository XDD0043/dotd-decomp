// IKCounter.cpp - reconstructed original translation unit 0x1ffbf8-0x1ffc70 (GAME_TOC1, main_toc1), 4 functions, 4 live.
// Primary owner: IKCounter (not a registered class)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x1ffbf8  IKCounter_LevelReset
//   [x] 0x1ffc58  IKCounter_Load
//   [ ] 0x1ffc60  IKCounter_Save
//   [ ] 0x1ffc68  KStub_Nop_1ffc68
//
//   [ ] 0x9b1270  IKCounter_GetClassGroup  [inline]
//   [ ] 0x9b1278  IKCounter_GetClassId  [inline]
//   [ ] 0x9b1280  IKCounter_Destructor  [inline]
//   [ ] 0x9b1298  IKCounter_IsKindOf  [inline]
//   [ ] 0x9b12b8  IKCounter_DeletingDestructor  [inline]
#include "k2000/misc/IKCounter.h"

// 0x001ffc58 IKCounter_Load
int32_t IKCounter::Load(IKFile* /*file*/, int32_t /*type*/) { return 1; }
