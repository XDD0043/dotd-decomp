// CKSrvMusic.h - the music service (key 0x501, vtable 0xb1fba0, size 0x30). Original unit:
// CKSrvMusic.cpp (0x210070-0x211748). XXL2: K/KServices/KServiceMusic/CKSrvMusic.h: the same members
// read in the same order; DotD adds +0x18, the second per-priority array (+0x20) and the GAME byte +0x2f.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/services/IKService.h"

class CKMusicPlayList;

class CKSrvMusic : public IKService {
public:
    DOTD_CLASS_KEY(kCategoryService, 0x14)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9b1fb8
        return key == 0x501 || key == 0x1 || key == 0x3fe || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKSrvMusic)

    CKSrvMusic();  // 0x002107d8 CKSrvMusic_Construct
    // 0x00211118 CKSrvMusic_Destructor (0x2113c8 Destructor_2 the same, 0x2116e0 DeletingDestructor + delete): the
    // engine's music service cleared (Engine_SetSrvMusic(0)).
    ~CKSrvMusic() override;

    void Destroy() override;  // vt+0x10 0x00210670 CKSrvMusic_Destroy
    // vt+0x1c 0x00211178 CKSrvMusic_MessageProc: 0x102 empties the waiting (+0x1c) and the deferred (+0x20) requests.
    int32_t MessageProc(uint16_t message, void* data) override;
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00210d90 CKSrvMusic_Load
    int32_t PostLoad(int32_t type) override;            // vt+0x30 0x002105c0 CKSrvMusic_PostLoad
    // vt+0x50 0x002102f8 CKSrvMusic_Start: no list playing, the waiting and the deferred lists emptied.
    void Start() override;
    void Restart() override;                            // vt+0x54 0x210278 CKSrvMusic_Restart (Stop's body)
    void Stop() override;                               // vt+0x68 0x2101f8 CKSrvMusic_Stop
    // vt+0x70 0x00210588 CKSrvMusic_Pause: the playing list's OnPause (0x2117c0, empty).
    void Pause() override;
    // vt+0x78 0x00210550 CKSrvMusic_Resume: the playing list's start time taken from the clock again (0x211eb8).
    void Resume() override;
    // vt+0x7c 0x00211428 UpdateCKSrvMusic: while the clock runs: the detection flag cleared; unless the streams are
    // suspended, the deferred requests (+0x20, the highest priority first) taken as RequestTrack does; the playing list's
    // frame (when enabled); then the music detectors of the current sector (or of none) until one reports a detection.
    void Update(IKTime* clock) override;
    // pre-C2.7 gamemgr: 0x002101a0 CKSrvMusic_ClearChannelRequests_maybe: the waiting and the deferred requests (one per
    // priority) cleared (the game manager's hero death state).
    void ClearChannelRequests();
    int32_t InitializeService() override { return 1; }  // vt+0x94 0x2100c0
    void DestroyService() override {}                   // vt+0x98 0x2100c8 (empty)

    // 0x002100d0 CKSrvMusic_GetPlayList: play list `index`, null past the end.
    CKMusicPlayList* GetPlayList(uint32_t index) const;
    // 0x00210358 CKSrvMusic_RequestTrack_maybe: `playList` asked to play (CKDetectorMusic action 0). A list of a priority
    // the service has: while the streams are suspended it waits in the deferred slot (+0x20) of its priority; the playing
    // list stays; with the service disabled it waits in its priority's slot (+0x1c). A list of a lower priority than the
    // playing one waits (when its mode word +0x04 allows) or is dropped; otherwise the playing one is stopped keeping its
    // position (and waits, when it was of a lower priority and its mode allows) and the list starts; `clear` empties the
    // waiting slots up to its priority.
    void RequestTrack(CKMusicPlayList* playList, uint8_t clear);
    // 0x002109a8 CKSrvMusic_RequestPriorityPlaylist_maybe (CKDetectorMusic action 1): the waiting list of priority
    // `priority` given up; the playing list stopped when it is of that priority (then the next waiting one below it
    // starts, unless `clear`) or, with `clear`, of a lower one; `clear` empties the waiting slots below it.
    void RequestPriorityPlaylist(uint32_t priority, uint8_t clear);
    // 0x00210bd8 CKSrvMusic_StopPlayList_maybe: `playList` stopped when it plays (the highest waiting list below its
    // priority then starts, resumed) or taken out of its waiting slot. Nothing while the streams are suspended.
    void StopPlayList(CKMusicPlayList* playList);

    uint32_t m_ui32NbPlayList;                   // +0x0c
    IKSerializable** m_apPlayList;               // +0x10 CKMusicPlayList* (OperatorNewArray)
    IKSerializable* m_pCurrentPlayListPlaying;   // +0x14 CKMusicPlayList; Load clears it
    uint32_t m_unk18;                            // +0x18 not set by the constructor or Load
    IKSerializable** m_apWaitingPlayList;        // +0x1c CKMusicPlayList*, one per priority, zeroed
    // +0x20 CKMusicPlayList*, one per priority, zeroed: the requests UpdateCKSrvMusic consumes _maybe.
    IKSerializable** m_unk20;
    IKSerializable** m_apDetector;               // +0x24 CKDetectorMusic* (OperatorNewArray)
    uint32_t m_ui32NbMusicDetector;              // +0x28
    uint8_t m_ui8NbPriority;                     // +0x2c the file's value + 1, at most 0xff
    uint8_t m_bDectectionFound;                  // +0x2d (XXL2 spelling) UpdateCKSrvMusic clears it
    uint8_t m_bEnable;                           // +0x2e PostLoad sets 1
    uint8_t m_unk2f;                             // +0x2f read from GAME.KP3 (K_GAME_PLATEFORMS)
};
DOTD_ASSERT_SIZE(CKSrvMusic, 0x30);

// DOTD debug (DOTD_DBG_MUSIC set): one log line per music request (`what`, the play list's index in the service's array,
// its priority, `arg`), with the render frame counter and the clock, so a run (dotd.exe or a replay) shows when the
// music changes. Nothing without the variable.
void MusicDebugLog(const char* what, const CKMusicPlayList* playList, uint32_t arg);
DOTD_ASSERT_OFFSET(CKSrvMusic, m_ui32Priority, 0x08);
DOTD_ASSERT_OFFSET(CKSrvMusic, m_ui32NbPlayList, 0x0c);
DOTD_ASSERT_OFFSET(CKSrvMusic, m_apPlayList, 0x10);
DOTD_ASSERT_OFFSET(CKSrvMusic, m_pCurrentPlayListPlaying, 0x14);
DOTD_ASSERT_OFFSET(CKSrvMusic, m_apWaitingPlayList, 0x1c);
DOTD_ASSERT_OFFSET(CKSrvMusic, m_unk20, 0x20);
DOTD_ASSERT_OFFSET(CKSrvMusic, m_apDetector, 0x24);
DOTD_ASSERT_OFFSET(CKSrvMusic, m_ui32NbMusicDetector, 0x28);
DOTD_ASSERT_OFFSET(CKSrvMusic, m_ui8NbPriority, 0x2c);
DOTD_ASSERT_OFFSET(CKSrvMusic, m_unk2f, 0x2f);
