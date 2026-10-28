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

// One entry of the list (vtable 0xb1fca8, 0xc bytes; XXL2 CKMusicSequence _maybe): a stream reference
// and a word. CKMusicPlayList_Entry_Construct_maybe sets the vtable only.
class CKMusicSequence {
public:
    CKMusicSequence() {}           // 0x00212fb8 CKMusicPlayList_Entry_Construct_maybe
    virtual ~CKMusicSequence() {}  // the vtable's slots come with C2.2

    // 0x00212e90 CKMusicPlayList_LoadStreamEntry
    int32_t Load(IKFile* file, int32_t type);

    IKSerializable* m_pStream;  // +0x04 a reference
    uint32_t m_unk08;           // +0x08
};
DOTD_ASSERT_SIZE(CKMusicSequence, 0xc);

class CKMusicPlayList : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0xbb)
    DOTD_DECLARE_FACTORIES(CKMusicPlayList)

    CKMusicPlayList();  // 0x002120e0 CKMusicPlayList_Create (as CKMusicPlayList_Construct 0x211798)
    ~CKMusicPlayList() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00212748 CKMusicPlayList_Load

    void BuildPlayOrder();  // 0x00212348 CKMusicPlayList_BuildPlayOrder_maybe
    // 0x00211960 CKMusicPlayList_StopTrack_maybe: the playing sequence's stream stopped; with keepPosition 0
    // the list forgets the track (position 0, index 0xff); otherwise it keeps the position and moves on.
    void StopTrack(uint32_t immediate, int32_t keepPosition);

    uint32_t m_unk04;                     // +0x04 read after the five floats
    CKMusicSequence* m_aMusicSequence;    // +0x08 new[] (with the array cookie); 0 when empty
    uint32_t m_unk0c;                     // +0x0c the Load sets 0
    uint8_t m_unk10;                      // +0x10 the Load sets 0xff
    uint8_t m_pad11[3];
    CKMusicSequence** m_aPlayingList;     // +0x14 the play order (Mem_AllocAligned16); 0 in the constructor
    uint32_t m_playingListCapacity;       // +0x18 8 in the constructor
    uint32_t m_playingListCount;          // +0x1c 0
    float m_afUnk20[5];                   // +0x20 (XXL2 has m_fFadeOutTime, m_fFadeOutTimeWhenInterrupt)
    uint8_t m_ui8NbMusicSequence;         // +0x34
    uint8_t m_unk35;                      // +0x35
    uint8_t m_unk36;                      // +0x36
    uint8_t m_baProperties;               // +0x37 _maybe (XXL2); bit 1: shuffle (BuildPlayOrder)
    uint32_t m_aUnk38[2];                 // +0x38 not set by the constructor nor the Load
    uint8_t m_unk40;                      // +0x40 0 in the constructor
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
DOTD_ASSERT_OFFSET(CKMusicPlayList, m_unk40, 0x40);
