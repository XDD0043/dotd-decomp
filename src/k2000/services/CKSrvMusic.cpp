// CKSrvMusic.cpp - reconstructed original translation unit 0x210070-0x211748 (GAME_TOC1, main_toc1), 33 functions, 32 live.
// Primary class: CKSrvMusic  key 0x501  category Service  size 0x30  vtable 0xb1fba0
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x210070  CKSrvMusic_Delete
//   [x] 0x2100c0  CKSrvMusic_InitializeService
//   [x] 0x2100c8  CKSrvMusic_DestroyService
//   [x] 0x2100d0  CKSrvMusic_GetPlayList
//   [ ] 0x210100  FUN_00210100  [dead]
//   [ ] 0x210118  RegisterCKSrvMusicClass
//   [ ] 0x210190  _GLOBAL__I_210190
//   [x] 0x2101a0  CKSrvMusic_ClearChannelRequests_maybe
//   [x] 0x2101f8  CKSrvMusic_Stop
//   [x] 0x210278  CKSrvMusic_Restart
//   [x] 0x2102f8  CKSrvMusic_Start
//   [x] 0x210358  CKSrvMusic_RequestTrack_maybe
//   [x] 0x210550  CKSrvMusic_Resume
//   [x] 0x210588  CKSrvMusic_Pause
//   [x] 0x2105c0  CKSrvMusic_PostLoad
//   [x] 0x210670  CKSrvMusic_Destroy
//   [x] 0x210730  CKSrvMusic_DeleteArray
//   [x] 0x2107d8  CKSrvMusic_Construct
//   [x] 0x210858  CKSrvMusic_Construct_2  (the not-in-charge copy of the constructor 0x2107d8: CKSrvMusic())
//   [ ] 0x2108d8  CKSrvMusic_StopCurrentAndClearLowerSlots_maybe  [dead: no pointer to its descriptor 0xb7c7a0]
//   [x] 0x2109a8  CKSrvMusic_RequestPriorityPlaylist_maybe
//   [x] 0x210bd8  CKSrvMusic_StopPlayList_maybe
//   [x] 0x210d78  CKSrvMusic_Save  (returns 1: the default)
//   [x] 0x210d80  CKSrvMusic_GetInfo  (returns 1: the default)
//   [x] 0x210d88  CKSrvMusic_RecursiveRegistration  (returns 1, registers nothing: the default)
//   [x] 0x210d90  CKSrvMusic_Load
//   [x] 0x211118  CKSrvMusic_Destructor  (~CKSrvMusic)
//   [x] 0x211178  CKSrvMusic_MessageProc
//   [x] 0x211208  CKSrvMusic_CreateArray
//   [x] 0x211328  CKSrvMusic_Create
//   [x] 0x2113c8  CKSrvMusic_Destructor_2  (~CKSrvMusic)
//   [x] 0x211428  UpdateCKSrvMusic
//   [x] 0x2116e0  CKSrvMusic_DeletingDestructor  (~CKSrvMusic + delete)
//
//   [ ] 0x9b1fb8  CKSrvMusic_IsKindOfClass  [inline]
//   [ ] 0x9b1ff0  CKSrvMusic_GetClassType  [inline]
//   [ ] 0x9b1ff8  CKSrvMusic_GetClassID  [inline]
#include "k2000/services/CKSrvMusic.h"

#include <cstdlib>
#include <cstring>

#include "k2000/io/IKFile.h"
#include "k2000/logic/CKLevel.h"
#include "k2000/logic/ai/CKDetectorBase.h"
#include "k2000/logic/io/CKStreamObject.h"
#include "k2000/logic/sound/CKMusicPlayList.h"
#include "k2000/logic/sound/CKStreamWave.h"
#include "k2000/managers/CKSoundManager.h"
#include "k2000/misc/Engine.h"
#include "k2000/managers/CKSoundManager.h"
#include "k2000/sound/CKSoundStreamManager.h"
#include "k2000/sound/SoundStreamType.h"
#include "k2000/system/CTimeManager.h"
#include "k2000/system/IKTime.h"
#include "platform/log.h"

extern uint16_t g_ui16RenderFrameCounter;  // 0x00c29694 (CRenderer.cpp)

namespace {
// count references read one by one into a new array (OperatorNewArray(count * 4)); none: null.
IKSerializable** LoadRefList(IKFile* file, uint32_t count) {
    if (count == 0) return nullptr;
    IKSerializable** list = new IKSerializable*[count];
    for (uint32_t i = 0; i < count; ++i) IKFile_ReadRef(file, &list[i]);
    return list;
}

// The stream manager's suspended flag (GameEngineContext +0x1c -> CKSoundManager +0x0c -> +0x18).
uint8_t StreamsSuspended() { return g_pEngine->m_soundManager->m_pSoundStreamManager->m_unk18; }
CKMusicPlayList* AsPlayList(IKSerializable* object) { return static_cast<CKMusicPlayList*>(object); }
}  // namespace

// DOTD debug: see the header.
void MusicDebugLog(const char* what, const CKMusicPlayList* playList, uint32_t arg) {
    static const bool on = std::getenv("DOTD_DBG_MUSIC") != nullptr;
    if (!on) return;
    const CKSrvMusic* music = static_cast<const CKSrvMusic*>(g_pEngine->m_srvMusic);
    int32_t index = -1;
    if (music != nullptr && playList != nullptr) {
        for (uint32_t i = 0; i < music->m_ui32NbPlayList; ++i)
            if (music->m_apPlayList[i] == playList) index = static_cast<int32_t>(i);
    }
    // A detector asks every frame a movable is inside it: only a request that differs from the last one is logged.
    static const char* lastWhat = nullptr;
    static int32_t lastIndex = -3;
    static uint32_t lastArg = 0;
    if (what == lastWhat && index == lastIndex && arg == lastArg) return;
    lastWhat = what;
    lastIndex = index;
    lastArg = arg;
    const IKTime* clock = g_pEngine->m_timeManager != nullptr ? g_pEngine->m_timeManager->m_pTime : nullptr;
    // The list's first stream (CKMusicSequence -> CKStreamObject -> CKStreamWave path) and its properties (bit 0 loop).
    const char* path = "";
    if (playList != nullptr && playList->m_ui8NbMusicSequence != 0 && playList->m_aMusicSequence != nullptr) {
        const CKStreamObject* stream = static_cast<const CKStreamObject*>(playList->m_aMusicSequence[0].m_pStream);
        const CKStreamWave* wave = stream != nullptr ? static_cast<const CKStreamWave*>(stream->m_pStreamWave) : nullptr;
        if (wave != nullptr) path = wave->m_szOriginalStreamPath;
    }
    DOTD_LOG("music %s list %d prio %d arg %u (counter %u, t %.3f) %s tracks %d props %d", what, index,
             playList != nullptr ? static_cast<int32_t>(playList->m_unk35) : -1, arg, g_ui16RenderFrameCounter,
             clock != nullptr ? clock->m_afCurrentTime[0] : -1.0f, path,
             playList != nullptr ? static_cast<int32_t>(playList->m_ui8NbMusicSequence) : 0,
             playList != nullptr ? static_cast<int32_t>(playList->m_baProperties) : 0);
}

// 0x002107d8 CKSrvMusic_Construct (the same stores inlined in 0x211328 CKSrvMusic_Create).
CKSrvMusic::CKSrvMusic() {
    m_ui32Priority = 0x7c;
    Engine_SetSrvMusic(this);
    m_ui32NbPlayList = 0;
    m_pCurrentPlayListPlaying = nullptr;
    m_ui8NbPriority = 0;
}

// 0x00211118 CKSrvMusic_Destructor (0x2113c8 / 0x2116e0 the same)
CKSrvMusic::~CKSrvMusic() { Engine_SetSrvMusic(nullptr); }

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

// 0x002105c0 CKSrvMusic_PostLoad: GAME.KP3's post-load gives the "Musics" stream type its two players
// (PtrList_FindByNameHash_maybe 0x115cc8 with "Musics", 0x00c4b154; the base PostLoad KStub_Return1_1a5b0); the
// service is enabled after any post-load.
int32_t CKSrvMusic::PostLoad(int32_t type) {
    if (type == K_GAME_PLATEFORMS) {
        g_pEngine->m_soundManager->m_pSoundStreamManager->FindTypeByName("Musics")->SetStreamCount(2);
    }
    m_bEnable = 1;
    return 1;
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

// 0x002100d0 CKSrvMusic_GetPlayList
CKMusicPlayList* CKSrvMusic::GetPlayList(uint32_t index) const {
    if (!(m_ui32NbPlayList > index)) return nullptr;
    return AsPlayList(m_apPlayList[index]);
}

// 0x002102f8 CKSrvMusic_Start
void CKSrvMusic::Start() {
    m_pCurrentPlayListPlaying = nullptr;
    std::memset(m_apWaitingPlayList, 0, m_ui8NbPriority * sizeof(IKSerializable*));  // memset (TOC bridge)
    std::memset(m_unk20, 0, m_ui8NbPriority * sizeof(IKSerializable*));
}

// 0x00210588 CKSrvMusic_Pause
void CKSrvMusic::Pause() {
    if (m_pCurrentPlayListPlaying != nullptr) AsPlayList(m_pCurrentPlayListPlaying)->OnPause();  // 0x2117c0
}

// 0x00210550 CKSrvMusic_Resume
void CKSrvMusic::Resume() {
    if (m_pCurrentPlayListPlaying != nullptr) AsPlayList(m_pCurrentPlayListPlaying)->ResyncTimeOnResume();  // 0x211eb8
}

// 0x00210358 CKSrvMusic_RequestTrack_maybe
void CKSrvMusic::RequestTrack(CKMusicPlayList* playList, uint8_t clear) {
    MusicDebugLog("RequestTrack", playList, clear);
    if (playList == nullptr) return;
    const uint8_t priority = playList->m_unk35;
    if (!(m_ui8NbPriority > priority)) return;
    if (StreamsSuspended() != 0) {
        m_unk20[priority] = playList;
        return;
    }
    CKMusicPlayList* current = AsPlayList(m_pCurrentPlayListPlaying);
    if (playList == current) return;
    if (m_bEnable == 0) {
        m_apWaitingPlayList[priority] = playList;
        return;
    }
    if (current != nullptr) {
        const uint8_t currentPriority = current->m_unk35;
        if (priority < currentPriority) {
            if (playList->m_unk04 != 0) m_apWaitingPlayList[priority] = playList;
            return;
        }
        current->StopTrack(1, 1);  // 0x211960
        if (priority > currentPriority) {
            CKMusicPlayList* stopped = AsPlayList(m_pCurrentPlayListPlaying);
            if (stopped->m_unk04 != 0) m_apWaitingPlayList[currentPriority] = stopped;
        }
    }
    m_pCurrentPlayListPlaying = playList;
    playList->Start(0);  // 0x211cd8
    if (clear == 0) return;
    // The slots 0 .. priority (a byte counter).
    const uint8_t end = static_cast<uint8_t>(priority + 1);
    uint8_t i = 0;
    uint8_t slot = 0;
    do {
        m_apWaitingPlayList[slot] = nullptr;
        i = static_cast<uint8_t>(i + 1);
        slot = i;
    } while (slot != end);
}

// 0x002109a8 CKSrvMusic_RequestPriorityPlaylist_maybe
void CKSrvMusic::RequestPriorityPlaylist(uint32_t priority, uint8_t clear) {
    MusicDebugLog("RequestPriorityPlaylist", nullptr, priority * 0x100u + clear);
    if (StreamsSuspended() != 0) return;
    if (m_bEnable != 0 && m_pCurrentPlayListPlaying != nullptr) {
        CKMusicPlayList* current = AsPlayList(m_pCurrentPlayListPlaying);
        const uint8_t currentPriority = current->m_unk35;
        const bool same = static_cast<int32_t>(priority) == static_cast<int32_t>(currentPriority);
        if (same || (priority > currentPriority && clear != 0)) {
            current->StopTrack(1, 0);  // 0x211960
            m_pCurrentPlayListPlaying = nullptr;
            if (currentPriority != 0 && same) {
                if (clear != 0) {
                    m_apWaitingPlayList[priority] = nullptr;
                } else {
                    // The highest waiting list below the stopped one resumes (a signed byte index).
                    for (int8_t i = static_cast<int8_t>(currentPriority - 1); i >= 0; i = static_cast<int8_t>(i - 1)) {
                        CKMusicPlayList* waiting = AsPlayList(m_apWaitingPlayList[i]);
                        if (waiting == nullptr) continue;
                        waiting->Start(1);  // 0x211cd8
                        m_pCurrentPlayListPlaying = m_apWaitingPlayList[i];
                        m_apWaitingPlayList[i] = nullptr;
                        return;
                    }
                    m_apWaitingPlayList[priority] = nullptr;
                    return;
                }
                goto clearBelow;
            }
        } else if (priority > currentPriority) {
            m_apWaitingPlayList[priority] = nullptr;
            return;
        }
    }
    m_apWaitingPlayList[priority] = nullptr;
    if (clear == 0) return;
clearBelow:
    if (priority == 0) return;
    {
        // The slots 0 .. priority - 1 (a byte counter).
        uint8_t i = 0;
        uint32_t slot = 0;
        do {
            m_apWaitingPlayList[slot] = nullptr;
            i = static_cast<uint8_t>(i + 1);
            slot = i;
        } while (priority > slot);
    }
}

// 0x00210bd8 CKSrvMusic_StopPlayList_maybe
void CKSrvMusic::StopPlayList(CKMusicPlayList* playList) {
    MusicDebugLog("StopPlayList", playList, 0);
    if (StreamsSuspended() != 0) return;
    if (playList == nullptr) return;
    const uint8_t priority = playList->m_unk35;
    if (m_bEnable == 0 || AsPlayList(m_pCurrentPlayListPlaying) != playList) {
        if (m_apWaitingPlayList[priority] == playList) m_apWaitingPlayList[priority] = nullptr;
        return;
    }
    playList->StopTrack(1, 0);  // 0x211960
    m_pCurrentPlayListPlaying = nullptr;
    if (priority == 0) return;
    // The highest waiting list below it resumes (a signed byte index).
    for (int8_t i = static_cast<int8_t>(priority - 1); i >= 0; i = static_cast<int8_t>(i - 1)) {
        CKMusicPlayList* waiting = AsPlayList(m_apWaitingPlayList[i]);
        if (waiting == nullptr) continue;
        waiting->Start(1);  // 0x211cd8
        m_pCurrentPlayListPlaying = m_apWaitingPlayList[i];
        m_apWaitingPlayList[i] = nullptr;
        return;
    }
}

// 0x00211428 UpdateCKSrvMusic
void CKSrvMusic::Update(IKTime* clock) {
    if (clock->m_eCurrentState != 0) return;
    m_bDectectionFound = 0;
    if (StreamsSuspended() == 0) {
        // The deferred requests, the highest priority first: RequestTrack (inlined, `clear` 0).
        for (uint32_t i = m_ui8NbPriority; i != 0;) {
            --i;
            CKMusicPlayList* playList = AsPlayList(m_unk20[i]);
            if (playList == nullptr) continue;
            const uint8_t priority = playList->m_unk35;
            if (m_ui8NbPriority > priority) {
                if (StreamsSuspended() != 0) {
                    m_unk20[priority] = playList;
                } else {
                    CKMusicPlayList* current = AsPlayList(m_pCurrentPlayListPlaying);
                    if (playList != current) {
                        if (m_bEnable == 0) {
                            m_apWaitingPlayList[priority] = playList;
                        } else {
                            bool start = true;
                            if (current != nullptr) {
                                const uint8_t currentPriority = current->m_unk35;
                                if (priority < currentPriority) {
                                    if (playList->m_unk04 != 0) m_apWaitingPlayList[priority] = playList;
                                    start = false;
                                } else {
                                    current->StopTrack(1, 1);  // 0x211960
                                    if (priority > currentPriority) {
                                        CKMusicPlayList* stopped = AsPlayList(m_pCurrentPlayListPlaying);
                                        if (stopped->m_unk04 != 0) m_apWaitingPlayList[currentPriority] = stopped;
                                    }
                                }
                            }
                            if (start) {
                                m_pCurrentPlayListPlaying = playList;
                                playList->Start(0);  // 0x211cd8
                            }
                        }
                    }
                }
            }
            m_unk20[i] = nullptr;
        }
    }
    if (m_pCurrentPlayListPlaying != nullptr && m_bEnable != 0) {
        AsPlayList(m_pCurrentPlayListPlaying)->UpdatePlayback(clock);  // 0x212af8
    }
    const int32_t sector = g_pEngine->m_level->m_currentSector;
    if (m_ui32NbMusicDetector == 0) return;
    uint32_t i = 0;
    while (m_bDectectionFound == 0) {
        CKDetectorBase* detector = static_cast<CKDetectorBase*>(m_apDetector[i]);
        ++i;
        const int32_t detectorSector = static_cast<int32_t>(detector->m_ui32NumSector);
        if (sector == detectorSector || detectorSector == 0) detector->Detect();  // vt+0x50
        if (!(m_ui32NbMusicDetector > i)) return;
    }
}

// 0x002101f8 CKSrvMusic_Stop: the playing list's track stopped and forgotten, the waiting lists emptied.
void CKSrvMusic::Stop() {
    if (m_pCurrentPlayListPlaying != nullptr) static_cast<CKMusicPlayList*>(m_pCurrentPlayListPlaying)->StopTrack(0, 0);
    m_pCurrentPlayListPlaying = nullptr;
    std::memset(m_apWaitingPlayList, 0, m_ui8NbPriority * sizeof(IKSerializable*));
    std::memset(m_unk20, 0, m_ui8NbPriority * sizeof(IKSerializable*));
}

// 0x00210278 CKSrvMusic_Restart (vt+0x54): the same body as Stop.
void CKSrvMusic::Restart() {
    if (m_pCurrentPlayListPlaying != nullptr) static_cast<CKMusicPlayList*>(m_pCurrentPlayListPlaying)->StopTrack(0, 0);
    m_pCurrentPlayListPlaying = nullptr;
    std::memset(m_apWaitingPlayList, 0, m_ui8NbPriority * sizeof(IKSerializable*));  // memset (TOC bridge)
    std::memset(m_unk20, 0, m_ui8NbPriority * sizeof(IKSerializable*));
}

// 0x00211178 CKSrvMusic_MessageProc: 0x102 empties the waiting and the deferred requests (the playing list goes on)
// and answers 0; any other message 1.
int32_t CKSrvMusic::MessageProc(uint16_t message, void* /*data*/) {
    if (message != 0x102) return 1;
    MusicDebugLog("message 0x102", nullptr, 0);
    std::memset(m_apWaitingPlayList, 0, m_ui8NbPriority * sizeof(IKSerializable*));
    std::memset(m_unk20, 0, m_ui8NbPriority * sizeof(IKSerializable*));  // memset (TOC bridge)
    return 0;
}

// ---- pre-C2.7 gamemgr: the hero death state's music ----

// 0x002101a0 CKSrvMusic_ClearChannelRequests_maybe
void CKSrvMusic::ClearChannelRequests() {
    std::memset(m_apWaitingPlayList, 0, m_ui8NbPriority * sizeof(IKSerializable*));
    std::memset(m_unk20, 0, m_ui8NbPriority * sizeof(IKSerializable*));
}
