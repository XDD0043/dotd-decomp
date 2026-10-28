// CKMusicPlayList.cpp - reconstructed original translation unit 0x211748-0x213028 (GAME_TOC1, main_toc1), 39 functions, 30 live.
// Primary class: CKMusicPlayList  key 0x2ecc  category Logic  size 0x44  vtable 0xb1fc50
// Other owners: SoundMusicPlayer (2), StopMusicPlayList (1), RequestMusicTrack (1), CKSrvMusic (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x211748  CKMusicPlayList_Delete
//   [ ] 0x211798  CKMusicPlayList_Construct  [dead]
//   [ ] 0x2117c0  SoundMusicPlayer_OnPause_maybe
//   [ ] 0x2117c8  CKMusicPlayList_GetTrackEntry_maybe  [dead]
//   [ ] 0x2117e8  CKMusicPlayList_GetTrackStream_maybe  [dead]
//   [ ] 0x211818  CKMusicPlayList_GetCurrentStreamIfActive_maybe  [dead]
//   [ ] 0x211868  RegisterCKMusicPlayListClass
//   [ ] 0x2118e0  _GLOBAL__I_2118e0
//   [ ] 0x2118f0  StopMusicPlayList
//   [ ] 0x211928  RequestMusicTrack
//   [x] 0x211960  CKMusicPlayList_StopTrack_maybe
//   [ ] 0x211a90  CKMusicPlayList_PlayTrack_maybe
//   [ ] 0x211cd8  CKMusicPlayList_Start_maybe
//   [x] 0x211d90  CKMusicPlayList_DeleteArray
//   [ ] 0x211e38  CKMusicPlayList_GetCurrentTrackPosition_maybe
//   [ ] 0x211eb8  SoundMusicPlayer_ResyncTimeOnResume_maybe
//   [ ] 0x211ee0  CKMusicPlayList_IsCurrentTrackReady_maybe
//   [ ] 0x211f80  CKMusicPlayList_Construct_2  [dead]
//   [ ] 0x211fa8  CKMusicPlayList_StartPausedTrack_maybe
//   [x] 0x212028  CKMusicPlayList_CreateArray
//   [x] 0x2120e0  CKMusicPlayList_Create
//   [ ] 0x212138  CKMusicPlayList_Save
//   [ ] 0x212140  CKMusicPlayList_GetInfo
//   [ ] 0x212148  CKMusicPlayList_RecursiveRegistration
//   [ ] 0x2121a8  CKMusicPlayList_PostLoad
//   [ ] 0x2121b8  CKMusicPlayList_Destroy
//   [ ] 0x2122a8  CKMusicPlayList_MessageProc
//   [x] 0x212348  CKMusicPlayList_BuildPlayOrder_maybe
//   [ ] 0x2126d0  CKMusicPlayList_RestartWithMode_maybe
//   [x] 0x212748  CKMusicPlayList_Load
//   [ ] 0x212af8  CKSrvMusic_UpdatePlayback_maybe
//   [ ] 0x212e30  FUN_00212e30  [dead]
//   [ ] 0x212e88  KStub_Return1_212e88  [dead]
//   [x] 0x212e90  CKMusicPlayList_LoadStreamEntry
//   [ ] 0x212f78  CKMusicPlayList_Entry_ClampStreamEndMargin_maybe
//   [ ] 0x212fa8  FUN_00212fa8  [dead]
//   [x] 0x212fb8  CKMusicPlayList_Entry_Construct_maybe
//   [ ] 0x212fc8  FUN_00212fc8  [dead]
//   [ ] 0x212ff0  CKMusicPlayList_Entry_GetPlaybackPosition_maybe
//
//   [ ] 0x9b2000  CKMusicPlayList_GetClassType  [inline]
//   [ ] 0x9b2008  CKMusicPlayList_GetClassID  [inline]
//   [ ] 0x9b2010  CKMusicPlayList_IsKindOfClass  [inline]
//   [ ] 0x9b2030  CKMusicPlayList_Destructor  [inline]
//   [ ] 0x9b2098  CKMusicPlayList_DeletingDestructor  [inline]
#include "k2000/logic/sound/CKMusicPlayList.h"

#include "k2000/core/Stub.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/io/CKStreamObject.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/ClassRegistry.h"

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

// 0x00211960 CKMusicPlayList_StopTrack_maybe
// STUB(C2.2): keepPosition != 0 (the position read from the stream, the next track chosen) is not ported;
// CKSrvMusic_Stop and the music service's other callers so far pass 0.
void CKMusicPlayList::StopTrack(uint32_t immediate, int32_t keepPosition) {
    if (m_unk10 == 0xff) return;
    CKStreamObject* stream = static_cast<CKStreamObject*>(m_aPlayingList[m_unk10]->m_pStream);
    if (keepPosition == 0) {
        m_unk0c = 0;
        m_unk10 = 0xff;
    } else {
        DOTD_STUB_ONCE("CKMusicPlayList_StopTrack_maybe: keep the position (C2.2)");
    }
    stream->Stop(static_cast<int32_t>(immediate & 0xff));
}
