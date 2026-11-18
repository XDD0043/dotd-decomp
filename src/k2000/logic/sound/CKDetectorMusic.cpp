// CKDetectorMusic.cpp - reconstructed original translation unit 0x1a9ff0-0x1aa680 (GAME_TOC1, main_toc1), 14 functions, 14 live.
// Primary class: CKDetectorMusic  key 0x2f4c  category Logic  size 0x20  vtable 0xb1c478
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1a9ff0  CKDetectorMusic_Delete
//   [ ] 0x1aa040  RegisterCKDetectorMusicClass
//   [ ] 0x1aa0b8  _GLOBAL__I_1aa0b8
//   [x] 0x1aa0c8  CKDetectorMusic_SetEnabled_maybe
//   [x] 0x1aa0f0  CKDetectorMusic_CheckAndTriggerMusic_maybe
//   [x] 0x1aa210  CKDetectorMusic_GetInfo  (CKDetectorBase::GetInfo)
//   [x] 0x1aa238  CKDetectorMusic_MessageProc
//   [x] 0x1aa260  CKDetectorMusic_PostLoad
//   [x] 0x1aa288  CKDetectorMusic_RecursiveRegistration  (the base's: returns 1)
//   [x] 0x1aa2b0  CKDetectorMusic_DeleteArray
//   [x] 0x1aa350  CKDetectorMusic_CreateArray
//   [x] 0x1aa3e0  CKDetectorMusic_Create
//   [x] 0x1aa418  CKDetectorMusic_Load
//   [ ] 0x1aa550  CKDetectorMusic_Save  [never runs: the music detectors register nothing with the saving manager]
//
//   [ ] 0x9ab0a8  CKDetectorMusic_IsKindOfClass  [inline]
//   [ ] 0x9ab0d0  CKDetectorMusic_GetClassType  [inline]
//   [ ] 0x9ab0d8  CKDetectorMusic_GetClassID  [inline]
//   [ ] 0x9ab0e0  CKDetectorMusic_Destructor  [inline]
//   [ ] 0x9ab100  CKDetectorMusic_DeletingDestructor  [inline]
#include "k2000/logic/sound/CKDetectorMusic.h"

#include "k2000/io/IKFile.h"
#include "k2000/logic/sound/CKMusicPlayList.h"
#include "k2000/misc/Engine.h"
#include "k2000/services/CKSrvMusic.h"

// 0x001aa0f0 CKDetectorMusic_CheckAndTriggerMusic_maybe
int32_t CKDetectorMusic::Detect() {
    if ((CKDetectorBase::Detect() & 0xff) == 0) return 0;  // 0x1a8c70
    if ((GetDetectionType(1) & 0xff) == 0) return 1;
    CKSrvMusic* music = static_cast<CKSrvMusic*>(g_pEngine->m_srvMusic);
    if (m_eActionType == 0) {
        music->RequestTrack(music->GetPlayList(m_ui32Index), m_bClear);  // 0x2100d0, 0x210358
    } else if (m_eActionType == 1) {
        music->RequestPriorityPlaylist(m_ui32Index, m_bClear);  // 0x2109a8
    }
    music->m_bDectectionFound = 1;
    return 1;
}

// 0x001aa418 CKDetectorMusic_Load
int32_t CKDetectorMusic::Load(IKFile* file, int32_t type) {
    const int32_t result = CKDetectorBase::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        ReadU32LE(file, &m_eActionType);
        ReadU32LE(file, &m_ui32Index);
        ReadRaw(file, &m_bClear, 1);
    }
    return result;
}
