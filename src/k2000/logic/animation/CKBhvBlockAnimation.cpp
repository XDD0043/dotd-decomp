// CKBhvBlockAnimation.cpp - reconstructed original translation unit 0x5c17a0-0x5c2868 (GAME_TOC2, main_toc2), 26 functions, 26 live.
// Primary class: CKBhvBlockAnimation  key 0x9d0c  category Logic  size ?  vtable 0xb2fb40
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x5c17a0  CKBhvBlockAnimation_Delete
//   [ ] 0x5c17f0  CKBhvBlockAnimation_vf5C
//   [ ] 0x5c17f8  RegisterCKBhvBlockAnimationClass
//   [ ] 0x5c1870  _GLOBAL__I_5c1870
//   [ ] 0x5c1880  CKBhvBlockAnimation_vf74
//   [ ] 0x5c18d0  CKBhvBlockAnimation_vf70
//   [ ] 0x5c1940  CKBhvBlockAnimation_UpdateCinematicStream_maybe
//   [ ] 0x5c19a8  CKBhvBlockAnimation_vf68
//   [ ] 0x5c1a60  CKBhvBlockAnimation_vf64
//   [ ] 0x5c1d20  CKBhvBlockAnimation_vf58
//   [ ] 0x5c1d48  CKBhvBlockAnimation_vf54
//   [ ] 0x5c1d70  CKBhvBlockAnimation_ResetRuntime
//   [ ] 0x5c1d98  CKBhvBlockAnimation_Save
//   [ ] 0x5c1dc0  CKBhvBlockAnimation_RecursiveRegistration
//   [ ] 0x5c1de8  CKBhvBlockAnimation_Destroy
//   [ ] 0x5c1e10  CKBhvBlockAnimation_DeletingDestructor
//   [ ] 0x5c1e58  CKBhvBlockAnimation_Construct_2
//   [x] 0x5c1e90  CKBhvBlockAnimation_Construct
//   [x] 0x5c1ec8  CKBhvBlockAnimation_DeleteArray
//   [ ] 0x5c1f70  CKBhvBlockAnimation_Destructor
//   [ ] 0x5c1fa0  CKBhvBlockAnimation_BaseDestructor
//   [ ] 0x5c1fd0  CKBhvBlockAnimation_Update
//   [ ] 0x5c2260  CKBhvBlockAnimation_PostLoad
//   [x] 0x5c22a8  CKBhvBlockAnimation_CreateArray
//   [x] 0x5c2360  CKBhvBlockAnimation_Create
//   [x] 0x5c23b8  CKBhvBlockAnimation_Load
//
//   [ ] 0x9cd330  CKBhvBlockAnimation_IsKindOfClass  [inline]
//   [ ] 0x9cd368  CKBhvBlockAnimation_GetClassType  [inline]
//   [ ] 0x9cd370  CKBhvBlockAnimation_GetClassID  [inline]
//   [ ] 0x9cd378  CKBhvBlockAnimation_vf7C  [inline]
#include "k2000/logic/animation/CKBhvBlockAnimation.h"

#include "k2000/io/IKFile.h"

// 0x005c23b8 CKBhvBlockAnimation_Load
int32_t CKBhvBlockAnimation::Load(IKFile* file, int32_t type) {
    KBase9C8C::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        IKFile_ReadRef(file, &m_unk10);
        ReadU8(file, &m_unk19);
        IKFile_ReadRef(file, &m_unk0c);
        ReadU8(file, &m_unk1a);
        ReadU8(file, &m_unk24);
        ReadU32LE(file, &m_unk1c);
        IKFile_ReadRef(file, &m_unk28);
        ReadU32LEWords(file, reinterpret_cast<uint32_t*>(&m_unk30), 3);  // one 0xc read, swapped
        ReadU8(file, &m_unk2c);
        ReadU8(file, &m_unk3c);
        ReadU32LE(file, &m_unk40);
        IKFile_ReadRef(file, &m_unk14);
        ReadU8(file, &m_unk18);
        IKFile_ReadRef(file, &m_unk08);
        IKFile_ReadRef(file, &m_unk04);
    }
    return 1;
}
