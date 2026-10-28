// CKStreamWave.cpp - reconstructed original translation unit 0x11ef08-0x11f6c8 (GAME_TOC1, main_toc1), 16 functions, 14 live.
// Primary class: CKStreamWave  key 0x5a8c  category Logic  size 0x21c  vtable 0xb19a70
// Other owners: KFileSystem (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x11ef08  CKStreamWave_Delete
//   [ ] 0x11ef58  CKStreamWave_Construct  [dead]
//   [ ] 0x11ef90  CKStreamWave_Construct_2  [dead]
//   [ ] 0x11efc8  RegisterCKStreamWaveClass
//   [ ] 0x11f040  _GLOBAL__I_11f040
//   [ ] 0x11f050  CKStreamWave_SetFilePath_maybe
//   [ ] 0x11f080  KFileSystem_PrependDataRootInPlace_maybe
//   [x] 0x11f110  CKStreamWave_DeleteArray
//   [ ] 0x11f1b0  CKStreamWave_RecursiveRegistration
//   [x] 0x11f280  CKStreamWave_Load
//   [ ] 0x11f340  CKStreamWave_PostLoad
//   [ ] 0x11f348  CKStreamWave_Destroy
//   [x] 0x11f350  CKStreamWave_CreateArray
//   [x] 0x11f418  CKStreamWave_Create
//   [ ] 0x11f480  CKStreamWave_Save
//   [ ] 0x11f618  CKStreamWave_BuildFilePath_maybe
//
//   [x] 0x9a6d28  CKStreamWave_GetGuid  [inline]
//   [ ] 0x9a6d38  CKStreamWave_GetClassType  [inline]
//   [ ] 0x9a6d40  CKStreamWave_GetClassID  [inline]
//   [x] 0x9a6d48  CKStreamWave_SetGuid  [inline]
//   [ ] 0x9a6d78  CKStreamWave_Destructor  [inline]
//   [ ] 0x9a6d90  CKStreamWave_IsKindOfClass  [inline]
//   [ ] 0x9a6db0  CKStreamWave_DeletingDestructor  [inline]
#include "k2000/logic/sound/CKStreamWave.h"

#include "k2000/io/IKFile.h"

// 0x0011f418 CKStreamWave_Create (the constructor is inlined there; 0x11ef58 is dead). The stores in
// the original's order.
CKStreamWave::CKStreamWave() {
    m_uuid[0] = 0;
    m_fStreamLength = 0.0f;
    m_uuid[3] = 0;
    m_uuid[1] = 0;
    m_uuid[2] = 0;
    m_szFilePath[0] = 0;
    m_unk218 = 0;
    m_szOriginalStreamPath[0] = 0;
}

// 0x009a6d48 CKStreamWave_SetGuid
void CKStreamWave::SetGuid(const uint32_t* guid) { Uuid_Copy(m_uuid, guid); }

// 0x0011f280 CKStreamWave_Load
int32_t CKStreamWave::Load(IKFile* file, int32_t type) {
    if (type != K_GAME_PLATEFORMS) return 1;
    IKFile_ReadLengthPrefixedString(file, m_szOriginalStreamPath, -1);
    ReadF32LE(file, &m_fStreamLength);
    return 1;
}
