// CKBhvBlockSpeech.cpp - reconstructed original translation unit 0x5c4e50-0x5c5788 (GAME_TOC2, main_toc2), 19 functions, 19 live.
// Primary class: CKBhvBlockSpeech  key 0xa54c  category Logic  size ?  vtable 0xb2fcf0
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x5c4e50  CKBhvBlockSpeech_Delete
//   [ ] 0x5c4ea0  RegisterCKBhvBlockSpeechClass
//   [ ] 0x5c4f18  _GLOBAL__I_5c4f18
//   [ ] 0x5c4f28  CKBhvBlockSpeech_Update
//   [ ] 0x5c4fe8  CKBhvBlockSpeech_Stop_maybe
//   [ ] 0x5c5040  CKBhvBlockSpeech_IsFinished_maybe
//   [ ] 0x5c50c8  CKBhvBlockSpeech_StartSpeech_maybe
//   [ ] 0x5c51d8  CKBhvBlockSpeech_Save
//   [ ] 0x5c5200  CKBhvBlockSpeech_RecursiveRegistration
//   [ ] 0x5c5228  CKBhvBlockSpeech_Destroy
//   [ ] 0x5c5250  CKBhvBlockSpeech_DeletingDestructor
//   [ ] 0x5c5298  CKBhvBlockSpeech_Destructor
//   [ ] 0x5c52c8  CKBhvBlockSpeech_BaseDestructor
//   [ ] 0x5c52f8  CKBhvBlockSpeech_Construct_2
//   [x] 0x5c5330  CKBhvBlockSpeech_Construct
//   [x] 0x5c5368  CKBhvBlockSpeech_DeleteArray
//   [x] 0x5c5410  CKBhvBlockSpeech_Create
//   [x] 0x5c5468  CKBhvBlockSpeech_CreateArray
//   [x] 0x5c5520  CKBhvBlockSpeech_Load
//
//   [ ] 0x9cd450  CKBhvBlockSpeech_IsKindOfClass  [inline]
//   [ ] 0x9cd488  CKBhvBlockSpeech_GetClassType  [inline]
//   [ ] 0x9cd490  CKBhvBlockSpeech_GetClassID  [inline]
#include "k2000/logic/sound/CKBhvBlockSpeech.h"

#include "k2000/io/IKFile.h"

// 0x005c5520 CKBhvBlockSpeech_Load
int32_t CKBhvBlockSpeech::Load(IKFile* file, int32_t type) {
    KBase9C8C::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        IKFile_ReadRef(file, &m_unk04);
        IKFile_ReadRef(file, &m_unk08);
        IKFile_ReadRef(file, &m_unk0c);
        ReadU8(file, &m_unk10);
        ReadU8(file, &m_unk11);
        ReadU32LE(file, &m_unk14);
    }
    return 1;
}
