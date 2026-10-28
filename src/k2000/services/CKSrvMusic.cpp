// CKSrvMusic.cpp - reconstructed original translation unit 0x210070-0x211748 (GAME_TOC1, main_toc1), 33 functions, 32 live.
// Primary class: CKSrvMusic  key 0x501  category Service  size 0x30  vtable 0xb1fba0
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x210070  CKSrvMusic_Delete
//   [x] 0x2100c0  CKSrvMusic_InitializeService
//   [x] 0x2100c8  CKSrvMusic_DestroyService
//   [ ] 0x2100d0  CKSrvMusic_GetPlayList
//   [ ] 0x210100  FUN_00210100  [dead]
//   [ ] 0x210118  RegisterCKSrvMusicClass
//   [ ] 0x210190  _GLOBAL__I_210190
//   [ ] 0x2101a0  CKSrvMusic_ClearChannelRequests_maybe
//   [x] 0x2101f8  CKSrvMusic_Stop
//   [ ] 0x210278  CKSrvMusic_Restart
//   [ ] 0x2102f8  CKSrvMusic_Start
//   [ ] 0x210358  CKSrvMusic_RequestTrack_maybe
//   [ ] 0x210550  CKSrvMusic_Resume
//   [ ] 0x210588  CKSrvMusic_Pause
//   [ ] 0x2105c0  CKSrvMusic_PostLoad
//   [x] 0x210670  CKSrvMusic_Destroy
//   [x] 0x210730  CKSrvMusic_DeleteArray
//   [x] 0x2107d8  CKSrvMusic_Construct
//   [ ] 0x210858  CKSrvMusic_Construct_2
//   [ ] 0x2108d8  CKSrvMusic_StopCurrentAndClearLowerSlots_maybe
//   [ ] 0x2109a8  CKSrvMusic_RequestPriorityPlaylist_maybe
//   [ ] 0x210bd8  CKSrvMusic_StopPlayList_maybe
//   [ ] 0x210d78  CKSrvMusic_Save
//   [ ] 0x210d80  CKSrvMusic_GetInfo
//   [ ] 0x210d88  CKSrvMusic_RecursiveRegistration
//   [x] 0x210d90  CKSrvMusic_Load
//   [ ] 0x211118  CKSrvMusic_Destructor
//   [ ] 0x211178  CKSrvMusic_MessageProc
//   [x] 0x211208  CKSrvMusic_CreateArray
//   [x] 0x211328  CKSrvMusic_Create
//   [ ] 0x2113c8  CKSrvMusic_Destructor_2
//   [ ] 0x211428  UpdateCKSrvMusic
//   [ ] 0x2116e0  CKSrvMusic_DeletingDestructor
//
//   [ ] 0x9b1fb8  CKSrvMusic_IsKindOfClass  [inline]
//   [ ] 0x9b1ff0  CKSrvMusic_GetClassType  [inline]
//   [ ] 0x9b1ff8  CKSrvMusic_GetClassID  [inline]
#include "k2000/services/CKSrvMusic.h"

#include <cstring>

#include "k2000/io/IKFile.h"
#include "k2000/logic/sound/CKMusicPlayList.h"
#include "k2000/misc/Engine.h"

namespace {
// count references read one by one into a new array (OperatorNewArray(count * 4)); none: null.
IKSerializable** LoadRefList(IKFile* file, uint32_t count) {
    if (count == 0) return nullptr;
    IKSerializable** list = new IKSerializable*[count];
    for (uint32_t i = 0; i < count; ++i) IKFile_ReadRef(file, &list[i]);
    return list;
}
}  // namespace

// 0x002107d8 CKSrvMusic_Construct (the same stores inlined in 0x211328 CKSrvMusic_Create).
CKSrvMusic::CKSrvMusic() {
    m_ui32Priority = 0x7c;
    Engine_SetSrvMusic(this);
    m_ui32NbPlayList = 0;
    m_pCurrentPlayListPlaying = nullptr;
    m_ui8NbPriority = 0;
}

// 0x00210670 CKSrvMusic_Destroy: the counts cleared, the four arrays (OperatorDeleteArray) freed.
void CKSrvMusic::Destroy() {
    m_ui32NbPlayList = 0;
    m_ui8NbPriority = 0;
    m_ui32NbMusicDetector = 0;
    if (m_apPlayList != nullptr) {
        delete[] m_apPlayList;
        m_apPlayList = nullptr;
    }
    if (m_apWaitingPlayList != nullptr) {
        delete[] m_apWaitingPlayList;
        m_apWaitingPlayList = nullptr;
    }
    if (m_unk20 != nullptr) {
        delete[] m_unk20;
        m_unk20 = nullptr;
    }
    if (m_apDetector != nullptr) {
        delete[] m_apDetector;
        m_apDetector = nullptr;
    }
}

// 0x00210d90 CKSrvMusic_Load: GAME.KP3 gives one byte; a level the play lists, the priority count
// and the music detectors.
int32_t CKSrvMusic::Load(IKFile* file, int32_t type) {
    if (type == K_GAME_PLATEFORMS) {
        ReadU8(file, &m_unk2f);
        return 1;
    }
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadU32LE(file, &m_ui32NbPlayList);
    m_apPlayList = LoadRefList(file, m_ui32NbPlayList);
    ReadU8(file, &m_ui8NbPriority);
    const uint32_t priorities = m_ui8NbPriority + 1u;  // lbz, addi, cmplwi 0xff
    m_ui8NbPriority = static_cast<uint8_t>(priorities > 0xff ? 0xff : priorities);
    ReadU32LE(file, &m_ui32NbMusicDetector);
    m_apDetector = LoadRefList(file, m_ui32NbMusicDetector);
    if (m_ui8NbPriority == 0) {  // as in the original: cannot happen after the + 1
        m_unk20 = nullptr;
        m_apWaitingPlayList = nullptr;
    } else {
        m_apWaitingPlayList = new IKSerializable*[m_ui8NbPriority];
        m_unk20 = new IKSerializable*[m_ui8NbPriority];
        std::memset(m_apWaitingPlayList, 0, m_ui8NbPriority * sizeof(IKSerializable*));
        std::memset(m_unk20, 0, m_ui8NbPriority * sizeof(IKSerializable*));
    }
    m_pCurrentPlayListPlaying = nullptr;
    return 1;
}

// 0x002101f8 CKSrvMusic_Stop: the playing list's track stopped and forgotten, the waiting lists emptied.
void CKSrvMusic::Stop() {
    if (m_pCurrentPlayListPlaying != nullptr) static_cast<CKMusicPlayList*>(m_pCurrentPlayListPlaying)->StopTrack(0, 0);
    m_pCurrentPlayListPlaying = nullptr;
    std::memset(m_apWaitingPlayList, 0, m_ui8NbPriority * sizeof(IKSerializable*));
    std::memset(m_unk20, 0, m_ui8NbPriority * sizeof(IKSerializable*));
}
