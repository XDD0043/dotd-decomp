// CKSrvMusic.h - the music service (key 0x501, vtable 0xb1fba0, size 0x30). Original unit:
// CKSrvMusic.cpp (0x210070-0x211748). XXL2: K/KServices/KServiceMusic/CKSrvMusic.h: the same members
// read in the same order; DotD adds +0x18, the second per-priority array (+0x20) and the GAME byte +0x2f.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/services/IKService.h"

class CKSrvMusic : public IKService {
public:
    DOTD_CLASS_KEY(kCategoryService, 0x14)
    DOTD_DECLARE_FACTORIES(CKSrvMusic)

    CKSrvMusic();  // 0x002107d8 CKSrvMusic_Construct
    ~CKSrvMusic() override {}

    void Destroy() override;  // vt+0x10 0x00210670 CKSrvMusic_Destroy
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00210d90 CKSrvMusic_Load
    void Start() override {}                            // vt+0x50 0x2102f8  STUB(C1.6)
    void Stop() override;                               // vt+0x68 0x2101f8 CKSrvMusic_Stop
    void Pause() override {}                            // vt+0x70 0x210588  STUB(C1.6)
    void Resume() override {}                           // vt+0x78 0x210550  STUB(C1.6)
    void Update(IKTime*) override {}                    // vt+0x7c 0x211428 UpdateCKSrvMusic  STUB(C1.6)
    int32_t InitializeService() override { return 1; }  // vt+0x94 0x2100c0
    void DestroyService() override {}                   // vt+0x98 0x2100c8 (empty)

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
