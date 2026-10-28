// CKAnimatedFx.cpp - reconstructed original translation unit 0x5ca148-0x5cc298 (GAME_TOC2, main_toc2), 27 functions, 23 live.
// Primary class: CKAnimatedFx  key 0xa04c  category Logic  size ?  vtable 0xb300c8
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x5ca148  CKAnimatedFx_Delete
//   [ ] 0x5ca198  CKAnimatedFx_Construct  [dead]
//   [ ] 0x5ca1a8  CKAnimatedFx_Construct_2  [dead]
//   [ ] 0x5ca1b8  CKAnimatedFx_ResetState_maybe
//   [ ] 0x5ca1e8  RegisterCKAnimatedFxClass
//   [ ] 0x5ca260  _GLOBAL__I_5ca260
//   [ ] 0x5ca270  CKAnimatedFx_SetBasisFromRightUp_maybe  [dead]
//   [ ] 0x5ca2d8  CKAnimatedFx_SetOrientation_maybe
//   [ ] 0x5ca340  CKAnimatedFx_SetPosition
//   [ ] 0x5ca3c8  CKAnimatedFx_UpdateSegmentVolumes_maybe
//   [ ] 0x5ca4d8  CKAnimatedFx_ResetRigTransform_maybe
//   [ ] 0x5ca828  CKAnimatedFx_Play
//   [ ] 0x5ca908  CKAnimatedFx_PlayAnim_maybe
//   [x] 0x5ca980  CKAnimatedFx_DeleteArray
//   [x] 0x5caa28  CKAnimatedFx_CreateArray
//   [x] 0x5caac0  CKAnimatedFx_Create
//   [ ] 0x5caaf8  CKAnimatedFx_Save
//   [ ] 0x5cab00  CKAnimatedFx_RecursiveRegistration
//   [ ] 0x5cab08  CKAnimatedFx_PostLoad
//   [ ] 0x5cab50  CKAnimatedFx_Destroy
//   [x] 0x5cab58  CKAnimatedFx_Load
//   [ ] 0x5cb010  CKAnimatedFx_DeletingDestructor
//   [ ] 0x5cb050  CKAnimatedFx_Destructor
//   [ ] 0x5cb068  CKAnimatedFx_Destructor_2  [dead]
//   [ ] 0x5cb080  CKAnimatedFx_SetFxActive
//   [ ] 0x5cbf48  CKAnimatedFx_Stop_maybe
//   [ ] 0x5cbfb8  CKAnimatedFx_Update
//
//   [x] 0x9cd610  CKAnimatedFx_GetClassType  [inline]
//   [x] 0x9cd618  CKAnimatedFx_GetClassID  [inline]
//   [ ] 0x9cd620  CKAnimatedFx_IsKindOfClass  [inline]
#include "k2000/logic/fx/CKAnimatedFx.h"

#include "k2000/io/IKFile.h"

// 0x005cab58 CKAnimatedFx_Load
int32_t CKAnimatedFx::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadU8(file, &m_unk35);
    ReadU8(file, &m_unk36);
    IKFile_ReadRef(file, &m_unk04);
    IKFile_ReadRef(file, &m_unk3c);
    IKFile_ReadRef(file, &m_unk44);
    ReadF32LE(file, &m_unk0c);
    ReadU8(file, &m_unk1c);
    ReadF32LE(file, &m_unk20);
    ReadF32LE(file, &m_unk24);
    ReadF32LE(file, &m_unk28);
    ReadF32LE(file, &m_unk2c);
    ReadF32LE(file, &m_unk30);
    ReadU8(file, &m_unk34);
    ReadU8(file, &m_unk37);
    IKFile_ReadRef(file, &m_unk4c);
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(&m_unk10), 3);  // one 12-byte read
    return 1;
}
