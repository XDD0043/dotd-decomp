// CKMusicPlayList.h - a music play list (key 0x2ecc, vtable 0xb1fc50, size 0x44). Original unit:
// CKMusicPlayList.cpp. XXL2: K/KServices/KServiceMusic/CKMusicPlayList.h (m_aMusicSequence,
// m_aPlayingList, m_ui8NbMusicSequence, m_baProperties); DotD's layout differs, so most fields keep
// placeholder names.
//
// Its Load ends with BuildPlayOrder, which fills the playing order and, for a shuffled list, draws from
// the game's rand() (Rand_Int): loading a level with shuffled play lists advances the random sequence.
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"

class IKFile;
class IKTime;

// One entry of the list (vtable 0xb1fca8, 0xc bytes; XXL2 CKMusicSequence _maybe): a stream reference
// and a word. CKMusicPlayList_Entry_Construct_maybe sets the vtable only.
class CKMusicSequence {
public:
    CKMusicSequence() {}           // 0x00212fb8 CKMusicPlayList_Entry_Construct_maybe
    virtual ~CKMusicSequence() {}  // the vtable's slots come with C2.2
    // vt+0x08 0x00212f78 CKMusicPlayList_Entry_ClampStreamEndMargin_maybe (port-rest R07; no code calls a sequence's
    // vt+0x08): the stream's fade-out time (+0x14) at least 0.3 (TOC1 -0xcb0 0x3e99999a; ble: NaN becomes 0.3); 1.
    virtual int32_t ClampStreamEndMargin();

    // 0x00212e90 CKMusicPlayList_LoadStreamEntry
    int32_t Load(IKFile* file, int32_t type);
    // 0x00212ff0 CKMusicPlayList_Entry_GetPlaybackPosition_maybe: the seconds its stream has played
    // (CKStreamObject_GetPlaybackPosition_maybe; the item is not used).
    float GetPlaybackPosition() const;

    IKSerializable* m_pStream;  // +0x04 a reference (CKStreamObject)
    uint32_t m_unk08;           // +0x08
};
DOTD_ASSERT_SIZE(CKMusicSequence, 0xc);

class CKMusicPlayList : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0xbb)
    int32_t IsKindOfClass(uint32_t key) override { return key == 0x2ecc || key == 0xc; }  // vt+0x08 0x9b2010
    DOTD_DECLARE_FACTORIES(CKMusicPlayList)

    CKMusicPlayList();  // 0x002120e0 CKMusicPlayList_Create (as CKMusicPlayList_Construct 0x211798)
    ~CKMusicPlayList() override {}

    // vt+0x10 0x002121b8 CKMusicPlayList_Destroy: the sequences deleted (new[], each one's destructor), the play order
    // freed, its count cleared.
    void Destroy() override;
    // vt+0x1c 0x002122a8 CKMusicPlayList_MessageProc: 0x100 asks the music service to play the list
    // (CKSrvMusic_RequestTrack_maybe, no clear), 0x101 to stop it (CKSrvMusic_StopPlayList_maybe); both answer 0, any
    // other message 1. The level's triggers switch the music this way (LVL010: the fights' and the golem's music).
    int32_t MessageProc(uint16_t message, void* data) override;
    // vt+0x24 0x00212148 CKMusicPlayList_RecursiveRegistration: registered with the saving manager (vt+0x24) for type 0.
    void RecursiveRegistration(int32_t type) override;
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00212748 CKMusicPlayList_Load
    // vt+0x30 0x002121a8 CKMusicPlayList_PostLoad: the stall frame count (+0x3c) cleared; 1.
    int32_t PostLoad(int32_t type) override;
    // vt+0x28 0x00212138 CKMusicPlayList_Save and vt+0x40 0x00212140 CKMusicPlayList_GetInfo return 1: the defaults.

    void BuildPlayOrder();  // 0x00212348 CKMusicPlayList_BuildPlayOrder_maybe
    // 0x00211960 CKMusicPlayList_StopTrack_maybe: the playing sequence's stream stopped; with keepPosition 0
    // the list forgets the track (position 0, index 0xff); otherwise it keeps the played position (+0x0c), and a track
    // within its fade-out of the end moves on (the next one, or the loop start +0x36 for a looping list, else none).
    void StopTrack(uint32_t immediate, int32_t keepPosition);
    // 0x00211a90 CKMusicPlayList_PlayTrack_maybe: the track `index` (0xff: the first, from its start) played on the
    // "Musics" stream type when its stream is free: the playing one stopped, the stream given the list's fades and
    // volume (and its kept position when resumed), the start time taken. 0 when the stream was still busy.
    uint8_t PlayTrack(uint8_t index);
    // 0x00211cd8 CKMusicPlayList_Start_maybe: from the start unless `resume` (mode 1 always from the start, mode 2 the
    // current track from its start); the list forgets its track when it cannot play it.
    void Start(int32_t resume);
    // 0x00212af8 CKSrvMusic_UpdatePlayback_maybe: the playing list's frame: a list without a track starts; a track that
    // has played to its fade-out (or whose stream stalled for 24 frames) is followed by the next one, the loop start, or
    // the end of the list (CKSrvMusic_StopPlayList_maybe). The clock is not read.
    void UpdatePlayback(IKTime* clock);
    // 0x002117c0 SoundMusicPlayer_OnPause_maybe (empty).
    void OnPause() {}
    // 0x00211eb8 SoundMusicPlayer_ResyncTimeOnResume_maybe: a list with a track takes the clock's fixed time as its
    // start time again.
    void ResyncTimeOnResume();
    // 0x00211ee0 CKMusicPlayList_IsCurrentTrackReady_maybe: whether the playing track's stream player is in the state
    // asked of it (1 without a track entry); with no track, whether the list is empty.
    uint8_t IsCurrentTrackReady() const;
    // 0x00211fa8 CKMusicPlayList_StartPausedTrack_maybe: with a track, the start time taken from the clock and, when the
    // stream was started paused (+0x40 bit 1), its stream unpaused.
    void StartPausedTrack();

    uint32_t m_unk04;                     // +0x04 read after the five floats: the start mode (Start_maybe: 1, 2)
    CKMusicSequence* m_aMusicSequence;    // +0x08 new[] (with the array cookie); 0 when empty
    float m_unk0c;                        // +0x0c the kept position in seconds (StopTrack); the Load sets 0
    uint8_t m_unk10;                      // +0x10 the playing track's index in the play order, 0xff none; the Load sets 0xff
    uint8_t m_pad11[3];
    CKMusicSequence** m_aPlayingList;     // +0x14 the play order (Mem_AllocAligned16); 0 in the constructor
    uint32_t m_playingListCapacity;       // +0x18 8 in the constructor
    uint32_t m_playingListCount;          // +0x1c 0
    // +0x20 (XXL2 has m_fFadeOutTime, m_fFadeOutTimeWhenInterrupt). PlayTrack gives the stream [0] its volume (+0x28),
    // [1] +0x18, [2] its fade-in (+0x10; [3] when resumed at a kept position), [4] its fade-out (+0x14).
    float m_afUnk20[5];
    uint8_t m_ui8NbMusicSequence;         // +0x34
    uint8_t m_unk35;                      // +0x35 the priority (CKSrvMusic's slots)
    uint8_t m_unk36;                      // +0x36 the loop start index
    uint8_t m_baProperties;               // +0x37 _maybe (XXL2); bit 0: loop, bit 1: shuffle (BuildPlayOrder)
    float m_unk38;                        // +0x38 the clock's fixed time when the track started; not set by the
                                          //       constructor nor the Load
    uint32_t m_unk3c;                     // +0x3c the frames the stream has reported no item (UpdatePlayback)
    uint8_t m_unk40;                      // +0x40 0 in the constructor; bit 0 the stream's +0x3a, bit 1 a stream
                                          //       without an item is not stalled
    uint8_t m_pad41[3];
};
DOTD_ASSERT_SIZE(CKMusicPlayList, 0x44);
DOTD_ASSERT_OFFSET(CKMusicPlayList, m_unk04, 0x04);
DOTD_ASSERT_OFFSET(CKMusicPlayList, m_aMusicSequence, 0x08);
DOTD_ASSERT_OFFSET(CKMusicPlayList, m_unk0c, 0x0c);
DOTD_ASSERT_OFFSET(CKMusicPlayList, m_unk10, 0x10);
DOTD_ASSERT_OFFSET(CKMusicPlayList, m_aPlayingList, 0x14);
DOTD_ASSERT_OFFSET(CKMusicPlayList, m_playingListCount, 0x1c);
DOTD_ASSERT_OFFSET(CKMusicPlayList, m_afUnk20, 0x20);
DOTD_ASSERT_OFFSET(CKMusicPlayList, m_ui8NbMusicSequence, 0x34);
DOTD_ASSERT_OFFSET(CKMusicPlayList, m_baProperties, 0x37);
DOTD_ASSERT_OFFSET(CKMusicPlayList, m_unk38, 0x38);
DOTD_ASSERT_OFFSET(CKMusicPlayList, m_unk3c, 0x3c);
DOTD_ASSERT_OFFSET(CKMusicPlayList, m_unk40, 0x40);
