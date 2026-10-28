// KMemBuffer.cpp - reconstructed original translation unit 0x48350-0x497a0 (GAME_TOC1, main_toc1), 30 functions, 19 live.
// Primary owner: KMemBuffer (not a registered class)
// Other owners: KFileSystem (10), CopyString4Offset (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x48350  KMemBuffer_Construct_2  [dead]
//   [x] 0x48370  KMemBuffer_Construct
//   [ ] 0x48390  KMemBuffer_AttachExternalBuffer_maybe  [dead]
//   [ ] 0x483b8  KMemBuffer_Free
//   [ ] 0x48430  KMemBuffer_Init
//   [ ] 0x484a0  KMemBuffer_EnsureCapacity_maybe
//   [ ] 0x48550  KMemBuffer_DeletingDestructor
//   [ ] 0x485f8  KMemBuffer_Destructor
//   [ ] 0x48678  KMemBuffer_Destructor_2  [dead]
//   [ ] 0x486f8  KMemBuffer_Equals  [dead]
//   [ ] 0x48768  KMemBuffer_Create  [dead]
//   [ ] 0x487b8  KMemBuffer_WriteDataToStream_maybe  [dead]
//   [ ] 0x48918  KMemBuffer_WriteToStream_maybe  [dead]
//   [ ] 0x489c8  KMemBuffer_CopyFrom_maybe  [dead]
//   [ ] 0x48ac0  KMemBuffer_ReadFromStream_maybe
//   [ ] 0x48dc0  KMemBuffer_CreateFromStream_maybe
//   [ ] 0x48ec0  KMemBuffer_Resize
//   [ ] 0x48f78  FUN_00048f78  [dead]
//   [ ] 0x48f88  KFileSystem_GetSaveDevice
//   [ ] 0x48f90  KFileSystem_GetPathBuf4_maybe  [dead]
//   [ ] 0x48fa0  KFileSystem_GetDataRoot
//   [ ] 0x48fb0  FUN_00048fb0  [dead]
//   [ ] 0x48fc0  KFileSystem_ZeroFillStreamAsync_maybe
//   [ ] 0x49208  KFileSystem_ZeroFillStream
//   [ ] 0x49368  KFileSystem_SplitExtension
//   [ ] 0x49428  KFileSystem_GetFileName
//   [ ] 0x49540  KFileSystem_GetDirectory
//   [ ] 0x49628  KFileSystem_SetSaveRoot_maybe
//   [ ] 0x496c8  KFileSystem_SetDataRoot
//   [ ] 0x49770  CopyString4Offset
#include "k2000/memory/KMemBuffer.h"

// 0x00048370 KMemBuffer_Construct: inline in KMemBuffer.h.
