// CKMusicPlayList.cpp - reconstructed original translation unit 0x211748-0x213028 (GAME_TOC1, main_toc1), 39 functions, 30 live.
// Primary class: CKMusicPlayList  key 0x2ecc  category Logic  size 0x44  vtable 0xb1fc50
// Other owners: SoundMusicPlayer (2), StopMusicPlayList (1), RequestMusicTrack (1), CKSrvMusic (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x211748  CKMusicPlayList_Delete
//   [ ] 0x211798  CKMusicPlayList_Construct  [dead]
//   [x] 0x2117c0  SoundMusicPlayer_OnPause_maybe
//   [ ] 0x2117c8  CKMusicPlayList_GetTrackEntry_maybe  [dead]
//   [ ] 0x2117e8  CKMusicPlayList_GetTrackStream_maybe  [dead]
//   [ ] 0x211818  CKMusicPlayList_GetCurrentStreamIfActive_maybe  [dead]
//   [ ] 0x211868  RegisterCKMusicPlayListClass
//   [ ] 0x2118e0  _GLOBAL__I_2118e0
//   [ ] 0x2118f0  StopMusicPlayList  [dead: no pointer to its descriptor 0xb7c938 in the EBOOT]
//   [ ] 0x211928  RequestMusicTrack  [dead: no pointer to its descriptor 0xb7c940 in the EBOOT]
//   [x] 0x211960  CKMusicPlayList_StopTrack_maybe
//   [x] 0x211a90  CKMusicPlayList_PlayTrack_maybe
//   [x] 0x211cd8  CKMusicPlayList_Start_maybe
//   [x] 0x211d90  CKMusicPlayList_DeleteArray
//   [ ] 0x211e38  CKMusicPlayList_GetCurrentTrackPosition_maybe  [dead: no pointer to its descriptor 0xb7c968]
//   [x] 0x211eb8  SoundMusicPlayer_ResyncTimeOnResume_maybe
//   [x] 0x211ee0  CKMusicPlayList_IsCurrentTrackReady_maybe
//   [ ] 0x211f80  CKMusicPlayList_Construct_2  [dead]
//   [x] 0x211fa8  CKMusicPlayList_StartPausedTrack_maybe
//   [x] 0x212028  CKMusicPlayList_CreateArray
//   [x] 0x2120e0  CKMusicPlayList_Create
//   [x] 0x212138  CKMusicPlayList_Save  (returns 1: the default)
//   [x] 0x212140  CKMusicPlayList_GetInfo  (returns 1: the default)
//   [x] 0x212148  CKMusicPlayList_RecursiveRegistration
//   [x] 0x2121a8  CKMusicPlayList_PostLoad
//   [x] 0x2121b8  CKMusicPlayList_Destroy
//   [x] 0x2122a8  CKMusicPlayList_MessageProc
//   [x] 0x212348  CKMusicPlayList_BuildPlayOrder_maybe
//   [ ] 0x2126d0  CKMusicPlayList_RestartWithMode_maybe  [dead: no pointer to its descriptor 0xb7c9f8]
//   [x] 0x212748  CKMusicPlayList_Load
//   [x] 0x212af8  CKSrvMusic_UpdatePlayback_maybe
//   [ ] 0x212e30  FUN_00212e30  [dead]
//   [ ] 0x212e88  KStub_Return1_212e88  [dead]
//   [x] 0x212e90  CKMusicPlayList_LoadStreamEntry
//   [x] 0x212f78  CKMusicPlayList_Entry_ClampStreamEndMargin_maybe  (CKMusicSequence::ClampStreamEndMargin, vt+0x08 (no code calls a sequence's vt+0x08); port-rest R07)
//   [ ] 0x212fa8  FUN_00212fa8  [dead]
//   [x] 0x212fb8  CKMusicPlayList_Entry_Construct_maybe
//   [ ] 0x212fc8  FUN_00212fc8  [dead]
//   [x] 0x212ff0  CKMusicPlayList_Entry_GetPlaybackPosition_maybe
//
//   [ ] 0x9b2000  CKMusicPlayList_GetClassType  [inline]
//   [ ] 0x9b2008  CKMusicPlayList_GetClassID  [inline]
//   [ ] 0x9b2010  CKMusicPlayList_IsKindOfClass  [inline]
//   [ ] 0x9b2030  CKMusicPlayList_Destructor  [inline]
//   [ ] 0x9b2098  CKMusicPlayList_DeletingDestructor  [inline]
#include "k2000/logic/sound/CKMusicPlayList.h"

#include "k2000/io/IKFile.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/logic/io/CKStreamObject.h"
#include "k2000/managers/CKSoundManager.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/misc/Engine.h"
#include "k2000/services/CKSrvMusic.h"
#include "k2000/sound/CKSoundStreamManager.h"
#include "k2000/sound/SoundStream.h"
#include "k2000/system/CTimeManager.h"
#include "k2000/system/IKTime.h"
#include "platform/fps.h"

// 0x002120e0 CKMusicPlayList_Create (the constructor inlined)
CKMusicPlayList::CKMusicPlayList() {
    m_aPlayingList = nullptr;
    m_playingListCapacity = 8;
    m_playingListCount = 0;
    m_unk40 = 0;
}

// 0x00212e90 CKMusicPlayList_LoadStreamEntry
int32_t CKMusicSequence::Load(IKFile* file, int32_t type) {
    if (type == K_LEVEL_PLATEFORMS) {
        IKFile_ReadRef(file, &m_pStream);
        ReadU32LE(file, &m_unk08);
    }
    return 1;
}

// 0x00212748 CKMusicPlayList_Load
int32_t CKMusicPlayList::Load(IKFile* file, int32_t type) {
    if (type == K_LEVEL_PLATEFORMS) {
        ReadU8(file, &m_ui8NbMusicSequence);
        const uint32_t count = m_ui8NbMusicSequence;
        // OperatorNewArray(count * 0xc + 4): the count cookie, then CKMusicPlayList_Entry_Construct_maybe each.
        m_aMusicSequence = count == 0 ? nullptr : new CKMusicSequence[count];
        for (uint32_t i = 0; i < m_ui8NbMusicSequence; ++i) m_aMusicSequence[i].Load(file, K_LEVEL_PLATEFORMS);
        for (float& v : m_afUnk20) ReadF32LE(file, &v);
        ReadU32LE(file, &m_unk04);
        ReadU8(file, &m_unk35);
        ReadU8(file, &m_unk36);
        ReadU8(file, &m_baProperties);
        m_unk10 = 0xff;
        m_unk0c = 0;
        BuildPlayOrder();
    }
    return 1;
}

namespace {
// The play-order vector's inlined push_back: grows by 8 when full.
void PushPlaying(CKMusicSequence**& block, uint32_t& capacity, uint32_t& count, CKMusicSequence* entry) {
    if (capacity == count) {
        uint32_t grown = count + 8;
        uint32_t bytes = grown * static_cast<uint32_t>(sizeof(CKMusicSequence*));
        if (grown == 0) {
            grown = 8;
            bytes = 8 * static_cast<uint32_t>(sizeof(CKMusicSequence*));
        }
        block = static_cast<CKMusicSequence**>(Mem_ReallocAligned16(block, bytes));
        capacity = grown;
    }
    block[count] = entry;
    ++count;
}
}  // namespace

// 0x00212348 CKMusicPlayList_BuildPlayOrder_maybe: the play order, in list order, or shuffled when bit 1
// of m_baProperties is set (a draw without replacement with Rand_Int).
void CKMusicPlayList::BuildPlayOrder() {
    const uint32_t ptrSize = static_cast<uint32_t>(sizeof(CKMusicSequence*));
    if (m_aPlayingList == nullptr) {
        // The count is not reset on this path.
        if (m_ui8NbMusicSequence != 0) {
            m_playingListCapacity = m_ui8NbMusicSequence;
            m_aPlayingList = static_cast<CKMusicSequence**>(Mem_AllocAligned16(m_ui8NbMusicSequence * ptrSize));
        } else {
            m_playingListCapacity = 1;
            m_aPlayingList = static_cast<CKMusicSequence**>(Mem_AllocAligned16(ptrSize));
        }
    } else {
        if (m_playingListCapacity < m_ui8NbMusicSequence) {
            uint32_t grown = (m_ui8NbMusicSequence & 0xf8u) + 8;
            m_aPlayingList = static_cast<CKMusicSequence**>(Mem_ReallocAligned16(m_aPlayingList, grown * ptrSize));
            m_playingListCapacity = grown;
        }
        m_playingListCount = 0;
    }

    if (((m_baProperties >> 1) & 1) == 0) {
        for (uint32_t i = 0; i < m_ui8NbMusicSequence; ++i) {
            PushPlaying(m_aPlayingList, m_playingListCapacity, m_playingListCount, &m_aMusicSequence[i]);
        }
        return;
    }

    // Shuffle: a scratch vector of the entries (capacity 8, grows by 8), then draws.
    CKMusicSequence** pool = static_cast<CKMusicSequence**>(Mem_AllocAligned16(8 * ptrSize));
    if (m_ui8NbMusicSequence != 0) {
        uint32_t poolCapacity = 8;
        uint32_t remaining = 0;
        for (uint32_t i = 0; i < m_ui8NbMusicSequence; ++i) {
            if (remaining == poolCapacity) {
                poolCapacity = remaining + 8;
                pool = static_cast<CKMusicSequence**>(Mem_ReallocAligned16(pool, poolCapacity * ptrSize));
            }
            pool[remaining++] = &m_aMusicSequence[i];
        }
        uint32_t last = remaining - 1;  // the scratch slot moved into a drawn one
        uint8_t drawn = 0;
        do {
            const uint32_t r = static_cast<uint32_t>(Rand_Int()) & 0xffffu;
            ++drawn;
            const uint32_t pick = ((r * remaining) >> 16) & 0xffu;  // mullw, then bits 16..23
            --remaining;
            PushPlaying(m_aPlayingList, m_playingListCapacity, m_playingListCount, pool[pick]);
            if (pick != remaining) pool[pick] = pool[last];
            --last;
        } while (drawn < m_ui8NbMusicSequence);
    }
    if (pool != nullptr) Mem_FreeAligned16(pool);
}

// 0x00212ff0 CKMusicPlayList_Entry_GetPlaybackPosition_maybe
float CKMusicSequence::GetPlaybackPosition() const {
    int32_t item;
    float position;
    static_cast<const CKStreamObject*>(m_pStream)->GetPlaybackPosition(&item, &position);  // 0x11a2e8
    return position;
}

// 0x00212f78 CKMusicPlayList_Entry_ClampStreamEndMargin_maybe (vt+0x08)
int32_t CKMusicSequence::ClampStreamEndMargin() {
    CKStreamObject* stream = static_cast<CKStreamObject*>(m_pStream);
    const float margin = 0.3f;  // TOC1 -0xcb0 0x3e99999a
    const float fade = stream->m_unk14;
    stream->m_unk14 = fade > margin ? fade : margin;  // fcmpu / ble
    return 1;
}

namespace {
// The engine's clock, fixed game time (CTimeManager +0x04, IKTime +0x08).
float FixedTime() { return g_pEngine->m_timeManager->m_pTime->m_afCurrentTime[IKTime::FIXED_GAME_TIME]; }
CKStreamObject* StreamOf(const CKMusicSequence* sequence) { return static_cast<CKStreamObject*>(sequence->m_pStream); }
}  // namespace

// 0x00211960 CKMusicPlayList_StopTrack_maybe
void CKMusicPlayList::StopTrack(uint32_t immediate, int32_t keepPosition) {
    if (m_unk10 == 0xff) return;
    CKMusicSequence* sequence = m_aPlayingList[m_unk10];
    CKStreamObject* stream = StreamOf(sequence);
    if (keepPosition == 0) {
        m_unk0c = 0.0f;
        m_unk10 = 0xff;
    } else {
        const float position = sequence->GetPlaybackPosition();  // 0x212ff0
        m_unk0c = position;
        // A track within its fade-out (+0x14) of its end does not resume: the list moves on.
        if (stream->GetLength() - stream->m_unk14 <= position) {
            if (static_cast<int32_t>(m_unk10) + 1 < static_cast<int32_t>(m_ui8NbMusicSequence)) {
                m_unk10 = static_cast<uint8_t>(m_unk10 + 1);
                m_unk0c = 0.0f;
            } else if ((m_baProperties & 1) == 0) {
                m_unk0c = 0.0f;
                m_unk10 = 0xff;
            } else {
                m_unk10 = m_unk36;
                m_unk0c = 0.0f;
            }
        }
    }
    stream->Stop(static_cast<int32_t>(immediate & 0xff));  // 0x11a870
}

// 0x00211a90 CKMusicPlayList_PlayTrack_maybe
uint8_t CKMusicPlayList::PlayTrack(uint8_t index) {
    const bool resume = index != 0xff;
    const uint8_t track = resume ? index : 0;
    if (StreamOf(m_aPlayingList[track])->IsFinished() == 0) return 0;  // FUN_0011a538
    if (m_unk10 != 0xff) StreamOf(m_aPlayingList[m_unk10])->Stop(1);
    m_unk10 = track;
    if (track == 0xff) return 1;  // as the original (cannot happen)
    SoundStreamType* type = g_pEngine->m_soundManager->m_pSoundStreamManager->FindTypeByName("Musics");  // 0x115cc8
    CKStreamObject* stream = StreamOf(m_aPlayingList[m_unk10]);
    // The stream loops itself (+0x24) when the list loops back from its last track to that same track.
    uint8_t loopItself = 0;
    if ((m_baProperties & 1) != 0 && static_cast<int32_t>(m_unk10) == static_cast<int32_t>(m_ui8NbMusicSequence) - 1) {
        loopItself = m_unk10 == m_unk36 ? 1 : 0;
    }
    const bool atKeptPosition = resume && m_unk0c != 0.0f;
    stream->m_unk10 = atKeptPosition ? m_afUnk20[3] : m_afUnk20[2];
    stream->m_unk28 = m_afUnk20[0];
    stream->m_unk18 = m_afUnk20[1];
    stream->m_unk14 = m_afUnk20[4];
    stream->m_unk24 = loopItself;
    stream->m_unk3a = static_cast<uint8_t>(m_unk40 & 1);  // +0x3a start paused
    stream->Play(type, 1);  // 0x11a728
    if (resume && m_unk0c != 0.0f) stream->SetFloat20AndInt1C(m_unk0c, 0);  // 0x11a1b8
    m_unk3c = 0;
    m_unk38 = FixedTime();
    return 1;
}

// 0x00211cd8 CKMusicPlayList_Start_maybe
void CKMusicPlayList::Start(int32_t resume) {
    if (m_ui8NbMusicSequence == 0) return;
    if (resume == 0) {
        m_unk0c = 0.0f;
        m_unk10 = 0xff;
    }
    if (m_unk04 == 1) {
        m_unk0c = 0.0f;
        m_unk10 = 0xff;
    } else if (m_unk04 == 2) {
        m_unk0c = 0.0f;
    }
    if (PlayTrack(m_unk10) == 0) {
        m_unk0c = 0.0f;
        m_unk10 = 0xff;
    }
}

// 0x00212af8 CKSrvMusic_UpdatePlayback_maybe
void CKMusicPlayList::UpdatePlayback(IKTime* /*clock*/) {
    if (m_unk10 == 0xff) {
        Start(0);  // inlined
        return;
    }
    CKStreamObject* stream = StreamOf(m_aPlayingList[m_unk10]);
    const float now = FixedTime();
    const float fadeOut = stream->m_unk14;
    const float length = stream->GetLength();  // 0x11a5d8
    int32_t item = -1;
    float position = 0.0f;
    uint8_t ended = 0;
    if (g_pEngine->m_soundManager->m_pSoundStreamManager->m_unk18 == 0) {
        const float elapsed = now - m_unk38;
        stream->GetPlaybackPosition(&item, &position);  // 0x11a2e8
        if (length < elapsed) position = length;
        ended = length - fadeOut <= position ? 1 : 0;
    } else {
        // Suspended streams: the start time follows the clock.
        m_unk38 = now;
    }
    bool stalled = false;
    if (m_unk38 != now) {
        // A stream in state 7, or without an item (unless +0x40 bit 1), for more than 23 frames is taken as over.
        if (stream->GetStreamState() == 7 || (item == -1 && (m_unk40 & 2) == 0)) {
            m_unk3c = m_unk3c + 1;
            // --fps N (not in the original): count 60 Hz frames, so a stall still takes 24 of them (0.4 s).
            if (dotd::fps::Unlocked()) m_unk3c = m_unk3c - 1 + dotd::fps::Ticks();
            stalled = m_unk3c > 0x17;
        } else {
            m_unk3c = 0;
        }
    } else {
        m_unk3c = 0;
    }
    if (!stalled && ended == 0) return;

    const uint8_t count = m_ui8NbMusicSequence;
    m_unk0c = 0.0f;
    if (count == 1 && (m_baProperties & 1) == 0) {
        if (m_unk10 != 0xff) {
            CKStreamObject* playing = StreamOf(m_aPlayingList[m_unk10]);
            m_unk10 = 0xff;
            playing->Stop(1);
        }
    } else if (static_cast<int32_t>(m_unk10) + 1 < static_cast<int32_t>(count)) {
        PlayTrack(static_cast<uint8_t>(m_unk10 + 1));
        return;
    } else if ((m_baProperties & 1) != 0) {
        PlayTrack(m_unk36);
        return;
    }
    static_cast<CKSrvMusic*>(g_pEngine->m_srvMusic)->StopPlayList(this);  // 0x210bd8
}

// 0x00211eb8 SoundMusicPlayer_ResyncTimeOnResume_maybe
void CKMusicPlayList::ResyncTimeOnResume() {
    if (m_unk10 == 0xff) return;
    m_unk38 = FixedTime();
}

// 0x00211ee0 CKMusicPlayList_IsCurrentTrackReady_maybe
uint8_t CKMusicPlayList::IsCurrentTrackReady() const {
    if (m_unk10 == 0xff) return m_ui8NbMusicSequence == 0 ? 1 : 0;
    const CKMusicSequence* sequence = m_aPlayingList[m_unk10];
    if (sequence == nullptr) return 1;
    SoundStream* stream = static_cast<CKStreamObject*>(sequence->m_pStream)->m_pStream;
    if (stream == nullptr) return 0;
    return stream->IsInRequestedState2() != 0 ? 1 : 0;  // 0x0011c178
}

// 0x00211fa8 CKMusicPlayList_StartPausedTrack_maybe
void CKMusicPlayList::StartPausedTrack() {
    if (m_unk10 == 0xff) return;
    m_unk38 = FixedTime();
    if (((m_unk40 >> 1) & 1) == 0) return;
    const CKMusicSequence* sequence = m_aPlayingList[m_unk10];
    if (sequence == nullptr) return;
    static_cast<CKStreamObject*>(sequence->m_pStream)->Unpause();  // 0x0011a350
}

// 0x002122a8 CKMusicPlayList_MessageProc
int32_t CKMusicPlayList::MessageProc(uint16_t message, void* /*data*/) {
    CKSrvMusic* music = static_cast<CKSrvMusic*>(g_pEngine->m_srvMusic);
    if (message == 0x100 || message == 0x101) MusicDebugLog(message == 0x100 ? "message 0x100" : "message 0x101", this, 0);
    if (message == 0x100) {
        music->RequestTrack(this, 0);  // 0x210358
        return 0;
    }
    if (message != 0x101) return 1;
    music->StopPlayList(this);  // 0x210bd8
    return 0;
}

// 0x00212148 CKMusicPlayList_RecursiveRegistration (returns 1)
void CKMusicPlayList::RecursiveRegistration(int32_t type) {
    if (type == 0) g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);  // vt+0x24
}

// 0x002121a8 CKMusicPlayList_PostLoad
int32_t CKMusicPlayList::PostLoad(int32_t /*type*/) {
    m_unk3c = 0;
    return 1;
}

// 0x002121b8 CKMusicPlayList_Destroy
void CKMusicPlayList::Destroy() {
    if (m_aMusicSequence != nullptr) {
        delete[] m_aMusicSequence;  // the elements' vt+0x00 from the last, then OperatorDeleteArray (the cookie)
        m_aMusicSequence = nullptr;
    }
    if (m_aPlayingList != nullptr) {
        Mem_FreeAligned16(m_aPlayingList);
        m_aPlayingList = nullptr;
    }
    m_playingListCount = 0;
    m_aPlayingList = nullptr;
}
