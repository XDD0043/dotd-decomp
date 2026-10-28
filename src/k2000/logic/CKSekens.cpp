// CKSekens.cpp - reconstructed original translation unit 0x1f3d98-0x1f7018 (GAME_TOC1, main_toc1), 56 functions, 40 live.
// Primary class: CKSekens  key 0xf4c  category Logic  size 0x80  vtable 0xb1ea18
// Other owners: CKSrvSekensor (1), Sekensor (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1f3d98  CKSekens_Delete
//   [x] 0x1f3de8  CKSekens_Construct  [dead]
//   [ ] 0x1f3e90  CKSekens_Save
//   [ ] 0x1f3e98  CKSekens_SetSubtitleElement_maybe  [dead]
//   [ ] 0x1f3ea8  KStub_Nop_1f3ea8  [dead]
//   [x] 0x1f3eb0  CKSekens_GetCurrentLineIndex_maybe
//   [ ] 0x1f3ec0  CKSekens_SetDefaultState
//   [ ] 0x1f3f18  CKSekens_AdvanceVideoSubtitleLine_maybe  [dead]
//   [ ] 0x1f40a8  CKSekens_CallCurrentLineVf5C_maybe
//   [x] 0x1f4118  CKSekens_SetFlag14Bit3_maybe
//   [ ] 0x1f4148  CKSekens_SetStreamStartPaused_maybe
//   [ ] 0x1f4158  CKSekens_GetStreamStartPaused_maybe  [dead]
//   [ ] 0x1f4168  CKSekens_GetLineVolume_maybe  [dead]
//   [ ] 0x1f4188  CKSekens_CurrentLineHasStartOffset_maybe  [dead]
//   [x] 0x1f41e0  CKSekens_UsesSpeechStream_maybe
//   [ ] 0x1f41f8  KStub_Return1_1f41f8  [dead]
//   [ ] 0x1f4200  CKSekens_SkipToNextBlockEntry_maybe  [dead]
//   [ ] 0x1f42b8  FUN_001f42b8  [dead]
//   [ ] 0x1f43e0  CKSekens_AdvanceSkippingMarkers_maybe  [dead]
//   [ ] 0x1f44d0  RegisterCKSekensClass
//   [ ] 0x1f4548  _GLOBAL__I_1f4548
//   [ ] 0x1f4558  CKSekens_PollStreamPlaybackPosition_maybe
//   [ ] 0x1f45a0  CKSekens_PauseSound_maybe
//   [ ] 0x1f45d8  CKSekens_StopSpeechStream_maybe
//   [ ] 0x1f4630  FUN_001f4630  [dead]
//   [ ] 0x1f4660  CKSekens_PlaySpeechStream_maybe
//   [ ] 0x1f46e0  CKSekens_CreateDataBuffers_maybe  [dead]
//   [ ] 0x1f4728  CKSrvSekensor_IsSekensDone_maybe
//   [ ] 0x1f47a0  CKSekens_RecursiveRegistration
//   [ ] 0x1f4800  CKSekens_Destroy
//   [x] 0x1f48c0  CKSekens_DeleteArray
//   [ ] 0x1f4960  CKSekens_IsCurrentLineFinished_maybe
//   [ ] 0x1f4a30  Sekensor_IsCurrentSekens_maybe
//   [x] 0x1f4a88  CKSekens_GetSekensorDelayByIndex54_maybe
//   [ ] 0x1f4ac0  CKSekens_ForEachLineCallVf54_maybe
//   [ ] 0x1f4b70  CKSekens_ResumeSound_maybe
//   [ ] 0x1f4ba8  CKSekens_IsStreamVoiceActive_maybe
//   [ ] 0x1f4c00  CKSekens_StartPausedStream_maybe
//   [ ] 0x1f4c58  KStub_Nop_1f4c58
//   [x] 0x1f4c60  CKSekens_PostLoad
//   [ ] 0x1f4e28  CKSekens_Construct_2  [dead]
//   [ ] 0x1f4ed0  CKSekens_MessageProc
//   [ ] 0x1f4f80  CKSekens_GetInfo
//   [x] 0x1f4fd8  CKSekens_ShouldShowSubtitles_maybe
//   [x] 0x1f50b0  CKSekens_Load
//   [x] 0x1f56b0  CKSekens_Stop_maybe
//   [ ] 0x1f5858  CKSekens_StartLineSpeechStream_maybe  [dead]
//   [ ] 0x1f5948  FUN_001f5948  [dead]
//   [x] 0x1f59e8  CKSekens_UpdateVideoSubtitles_maybe
//   [x] 0x1f5bf8  CKSekens_StartLine_maybe
//   [x] 0x1f5f18  CKSekens_AdvanceToNextLine_maybe
//   [x] 0x1f5fe0  CKSekens_Begin_maybe
//   [x] 0x1f6410  CKSekens_UpdateCurrentLine_maybe
//   [x] 0x1f6b98  CKSekens_CreateArray
//   [x] 0x1f6cc8  CKSekens_Create
//   [x] 0x1f6d98  CKSekens_Update_maybe
//
//   [ ] 0x9b0cc8  CKSekens_GetClassType  [inline]
//   [ ] 0x9b0cd0  CKSekens_GetClassID  [inline]
//   [ ] 0x9b0cd8  CKSekens_IsKindOfClass  [inline]
//   [ ] 0x9b0cf8  CKSekens_DeletingDestructor  [inline]
//   [ ] 0x9b0da8  CKSekens_Destructor  [inline]
#include "k2000/logic/CKSekens.h"

#include <cstring>
#include <new>

#include "k2000/core/Stub.h"
#include "k2000/graphical/ui/CText2d.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/logic/io/CKStreamObject.h"
#include "k2000/managers/CKSoundManager.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/misc/CKSekensElement.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/IKGameStructure.h"
#include "k2000/logic/CKSekensBlock.h"
#include "k2000/services/CKSrvSekensor.h"
#include "k2000/sound/CKSoundStreamManager.h"
#include "k2000/sound/SoundStreamType.h"
#include "k2000/system/CTimeManager.h"
#include "k2000/system/IKTime.h"
#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"

// Inlined in 0x001f6cc8 CKSekens_Create (CKSekens_Construct 0x1f3de8).
CKSekens::CKSekens() {
    m_uuid[0] = 0;
    m_uuid[3] = 0;
    m_uuid[1] = 0;
    m_uuid[2] = 0;
    m_vBlocks.m_ui32NbElt = 10;
    m_vBlocks.m_pBlock = nullptr;
    m_vBlocks.m_ui32NbUsedElt = 0;
    m_vUnplayedLines.m_ui32NbElt = 8;
    m_vUnplayedLines.m_pBlock = nullptr;
    m_vUnplayedLines.m_ui32NbUsedElt = 0;
    m_fEarliestStart = -1.0f;
    m_i32CurrentLine = -1;
    m_unk7c = 0;
    m_pDataBuffers = nullptr;
    m_pStreamObject = nullptr;
    m_pText = nullptr;
    m_ui32BeginDelayIndex = 0;
    m_ui32DelayIndex = 0;
    // Bits 3-9 cleared, bit 5 set; bits 0-2 and 10-31 kept (rlwinm/or on the uninitialised word).
    m_flags = (m_flags & 0xfffffc00u) | (m_flags & 7u) | 0x20u;
}

// 0x001f50b0 CKSekens_Load. Type 0: the level's data; type 2 (the level localisation, called by
// CKSrvSekensor_Load): fresh data buffers and one word.
int32_t CKSekens::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) {
        if (type != K_LEVEL_LOCALIZATION) return 1;
        if (m_pDataBuffers != nullptr) {
            m_pDataBuffers->Free();
            if (m_pDataBuffers != nullptr) ::operator delete(m_pDataBuffers);
            m_pDataBuffers = nullptr;
        }
        CKSekensDataBuffers* buffers = new (::operator new(sizeof(CKSekensDataBuffers))) CKSekensDataBuffers();
        m_pDataBuffers = buffers;
        buffers->Load(file, K_LEVEL_LOCALIZATION);
        ReadU32LE(file, &m_unk68);
        return 1;
    }
    uint32_t count = 0;
    ReadU32LE(file, &count);
    if (count == 0) {
        m_vBlocks.m_ui32NbElt = 1;
        m_vBlocks.m_pBlock = static_cast<IKSerializable**>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(IKSerializable*))));
    } else {
        m_vBlocks.m_ui32NbElt = count;
        m_vBlocks.m_pBlock =
            static_cast<IKSerializable**>(Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(IKSerializable*))));
    }
    if (m_vBlocks.m_ui32NbElt < count) {  // as in the original: cannot happen
        uint32_t capacity = (count / 10) * 10 + 10;
        if (capacity == 0) capacity = 10;
        m_vBlocks.m_pBlock = static_cast<IKSerializable**>(
            Mem_ReallocAligned16(m_vBlocks.m_pBlock, capacity * static_cast<uint32_t>(sizeof(IKSerializable*))));
        m_vBlocks.m_ui32NbElt = capacity;
    }
    m_vBlocks.m_ui32NbUsedElt = count;
    for (uint32_t i = 0; i < count; ++i) IKFile_ReadRef(file, &m_vBlocks.m_pBlock[i]);
    ReadU8(file, &m_unk78);
    IKFile_ReadRef(file, &m_pText);
    // Four bytes into bits 2, 6, 7 and 9 (each byte shifted in unmasked, as the original's or).
    uint8_t b = 0;
    ReadU8(file, &b);
    m_flags = (m_flags & ~0x4u) | (static_cast<uint32_t>(b) << 2);
    ReadU8(file, &b);
    m_flags = (m_flags & ~0x40u) | (static_cast<uint32_t>(b) << 6);
    ReadU8(file, &b);
    m_flags = (m_flags & ~0x80u) | (static_cast<uint32_t>(b) << 7);
    ReadU8(file, &b);
    m_flags = (m_flags & ~0x200u) | (static_cast<uint32_t>(b) << 9);
    ReadU32LE(file, &m_ui32BeginDelayIndex);
    ReadU32LE(file, &m_ui32DelayIndex);
    m_tsOnStop.Load(file, K_LEVEL_PLATEFORMS);
    m_tsOnBegin.Load(file, K_LEVEL_PLATEFORMS);
    ReadU32LE(file, &m_ui32OrderMode);
    Uuid_Read(m_uuid, file);
    return 1;
}


namespace {

CKSrvSekensor* Sekensor() { return static_cast<CKSrvSekensor*>(g_pEngine->m_srvSekensor); }
CKSekensElement* Line(CKSekens* sekens, uint32_t index) { return static_cast<CKSekensElement*>(sekens->m_vBlocks.m_pBlock[index]); }
SoundStreamType* StreamType(const char* name) { return g_pEngine->m_soundManager->m_pSoundStreamManager->FindTypeByName(name); }
const char kMusics[] = "Musics";  // 0x00ac6a60
const char kSpeech[] = "Speech";  // 0x00ac6a68
// The unscaled game time of the frame clock (the PS3 KClock +0x08).
float UnscaledTime() { return g_pEngine->m_timeManager->m_pTime->m_afCurrentTime[IKTime::FIXED_GAME_TIME]; }

}  // namespace

// 0x001f41e0 CKSekens_UsesSpeechStream_maybe
uint8_t CKSekens::UsesSpeechStream() const { return m_pDataBuffers->m_unk05 != 0 ? 1 : 0; }

// 0x001f4a88 CKSekens_GetSekensorDelayByIndex54_maybe
float CKSekens::GetSekensorDelay() const { return Sekensor()->GetSekensTypeDelay(m_ui32DelayIndex); }

// 0x001f4c60 CKSekens_PostLoad
int32_t CKSekens::PostLoad(int32_t type) {
    if (type == 0) {
        m_flags &= 0xfffffff7u;
        m_unk7c = 0;
        if (m_pText != nullptr) m_pText->Disable();  // vt+0x68
        uint32_t counted = 0;
        for (uint32_t i = m_vBlocks.m_ui32NbUsedElt; i != 0;) {
            --i;
            if (Line(this, i)->Vf58() != 0) ++counted;
        }
        if (m_ui32OrderMode < 3) {
            if (counted == 0) {
                m_vUnplayedLines.m_ui32NbElt = 1;
                m_vUnplayedLines.m_pBlock = static_cast<uint32_t*>(Mem_AllocAligned16(4));
            } else {
                m_vUnplayedLines.m_ui32NbElt = counted;
                m_vUnplayedLines.m_pBlock = static_cast<uint32_t*>(Mem_AllocAligned16((counted & 0x3fffffffu) << 2));
            }
        }
        CKStreamObject* stream = static_cast<CKStreamObject*>(ClassRegistry_CreateObjectByKey(0x5a4c));
        m_pStreamObject = stream;
        stream->ResetRuntime();
        stream->m_pStreamWave = static_cast<CKSrvSekensor*>(g_pEngine->m_srvSekensor)->m_unk4c;
    }
    m_tsOnStop.PostLoad(type);
    m_tsOnBegin.PostLoad(type);
    return 1;
}

// 0x001f56b0 CKSekens_Stop_maybe
int32_t CKSekens::Stop() {
    m_unk7c = 0;
    for (uint32_t i = 0; i < m_vBlocks.m_ui32NbUsedElt; ++i) Line(this, i)->m_unk08 = 0;
    if ((m_flags & 1) != 0) {
        StreamType(kSpeech);  // PtrList_FindByNameHash_maybe, the result unused
        m_pStreamObject->Stop(1);
    }
    if (m_pText != nullptr) m_pText->Disable();  // vt+0x68
    m_i32CurrentLine = -1;
    m_flags = (m_flags & 0xffffffcfu) | 0x20;
    QueueTriggerSignals(&m_tsOnStop);
    if ((m_flags & 0x2000) == 0 && (m_flags & 0x200) == 0) StreamType(kMusics)->ReleaseVolumeFade();  // 0x11de10
    return 1;
}

// 0x001f5fe0 CKSekens_Begin_maybe
uint8_t CKSekens::Begin() {
    const uint32_t count = m_vBlocks.m_ui32NbUsedElt;
    if (count == 0) return 0;
    for (uint32_t i = 0; i < count; ++i) Line(this, i)->m_unk08 = 0;
    if (m_vUnplayedLines.m_ui32NbUsedElt == 0) {
        for (uint32_t i = count; i != 0;) {
            --i;
            if (Line(this, i)->Vf58() == 0) continue;
            const uint32_t used = m_vUnplayedLines.m_ui32NbUsedElt;
            if (m_vUnplayedLines.m_ui32NbElt == used) {  // grows by 8
                uint32_t capacity = used + 8;
                if (capacity == 0) capacity = 8;
                m_vUnplayedLines.m_pBlock = static_cast<uint32_t*>(
                    Mem_ReallocAligned16(m_vUnplayedLines.m_pBlock, (capacity & 0x3fffffffu) << 2));
                m_vUnplayedLines.m_ui32NbElt = capacity;
            }
            m_vUnplayedLines.m_pBlock[used] = i;
            ++m_vUnplayedLines.m_ui32NbUsedElt;
        }
    }
    uint32_t& unplayed = m_vUnplayedLines.m_ui32NbUsedElt;
    if (unplayed == 0) {
        m_i32CurrentLine = 0;
    } else if (m_ui32OrderMode == 1) {
        const uint32_t r = static_cast<uint32_t>(Rand_Int()) & 0xffffu;
        m_i32CurrentLine = static_cast<int32_t>(m_vUnplayedLines.m_pBlock[(r * unplayed) >> 16]);
    } else if (m_ui32OrderMode == 2) {
        const uint32_t r = static_cast<uint32_t>(Rand_Int()) & 0xffffu;
        const uint32_t pick = (r * unplayed) >> 16;
        m_i32CurrentLine = static_cast<int32_t>(m_vUnplayedLines.m_pBlock[pick]);
        --unplayed;
        if (pick != unplayed) m_vUnplayedLines.m_pBlock[pick] = m_vUnplayedLines.m_pBlock[unplayed];
    } else if (m_ui32OrderMode == 0) {
        m_i32CurrentLine = static_cast<int32_t>(m_vUnplayedLines.m_pBlock[unplayed - 1]);
        --unplayed;
    }
    m_flags = (m_flags & 0xfffffeffu) | 0x100;
    static_cast<IKGameStructure*>(g_pEngine->m_gameManager->m_gameStructure)->MarkSekensSeenInCurrentLevel(this);
    if ((m_flags & 8) == 0) {
        const double delay = Sekensor()->GetSekensTypeDelay(m_ui32BeginDelayIndex);
        m_fEarliestStart = static_cast<float>(delay + static_cast<double>(UnscaledTime()));
    } else {
        m_fEarliestStart = -1.0f;
    }
    m_flags &= 0xfffff7fcu;
    QueueTriggerSignals(&m_tsOnBegin);
    CKSekensElement* line = Line(this, static_cast<uint32_t>(m_i32CurrentLine));
    while (line->IsKindOfClass(0x65cc) == 0) {  // markers before the first block are passed
        line->m_unk08 = 1;
        ++m_i32CurrentLine;
        line = Line(this, static_cast<uint32_t>(m_i32CurrentLine));
    }
    StartLine(m_i32CurrentLine, 1);
    if ((m_flags & 0x2000) == 0 && (m_flags & 0x200) == 0) StreamType(kMusics)->StartVolumeFade(0);
    return 1;
}

// 0x001f5bf8 CKSekens_StartLine_maybe
void CKSekens::StartLine(int32_t lineIndex, int32_t first) {
    CKSekensBlock* line = static_cast<CKSekensBlock*>(Line(this, static_cast<uint32_t>(lineIndex)));
    const float lineTime = reinterpret_cast<const float*>(m_pDataBuffers->m_aWords0)[lineIndex];
    m_unk3c = 0;
    m_flags &= 0xfffffbffu;
    if (first != 0) m_fSpeechTime = 0.0f;
    bool sameClockPath = true;
    if (m_unk78 == 0) {
        m_fSpeechTime = (m_fSpeechTime + lineTime) + line->m_fTime;
        if ((m_flags & 8) != 0) sameClockPath = false;
    } else {
        m_fSpeechTime = lineTime + m_fSpeechTime;
        sameClockPath = (m_flags & 8) == 0;
    }
    if (sameClockPath) m_fLineStartTime = UnscaledTime();
    else m_fLineStartTime = 0.0f;
    if (m_unk78 != 0) {
        line->m_unk14 = 0.0f;
    } else if (0.0f <= line->m_fTime) {
        line->m_unk14 = line->m_fTime;
    } else {
        line->m_unk14 = -1.0f;
    }
    if (m_pDataBuffers->m_unk05 == 0) {
        m_ui32SpeechState = 3;
    } else if ((m_flags & 1) == 0) {
        if (first != 0) {
            // The first line starts the speech stream: the "Speech" type, the line's volume, the item (the sekens' base
            // plus the line's byte) from the data buffers. (STUB(C2.3 audio): the stream plays as a clock.)
            const uint8_t item = m_pDataBuffers->m_aBytes[lineIndex];
            float volume;
            std::memcpy(&volume, &m_pDataBuffers->m_aWords1[lineIndex], 4);
            SoundStreamType* speech = StreamType(kSpeech);
            m_pStreamObject->m_unk24 = 0;
            m_pStreamObject->m_unk28 = volume;
            m_pStreamObject->Play(speech, 0);
            m_pStreamObject->SetFloat20AndInt1C(0.0f, static_cast<int32_t>(item) + static_cast<int32_t>(m_unk68));
            m_flags = (m_flags & 0xfffffffeu) | 1;
            m_ui32SpeechState = 3;
        }
    } else {
        // A line of the running speech: the sound manager's float +0x18 takes the line's volume, the stream's follows.
        float volume;
        std::memcpy(&volume, &m_pDataBuffers->m_aWords1[lineIndex], 4);
        std::memcpy(&g_pEngine->m_soundManager->m_unk18, &volume, 4);
        if (m_pStreamObject->HasPlayer()) m_pStreamObject->SetVolumeWithFade(volume, 0.0f, 1);
    }
    if (m_pText != nullptr) {
        if (line->m_pText == nullptr) {
            m_pText->SetTextAscii("");  // vt+0x90 with the empty string 0x00ac8200
        } else {
            m_pText->SetTextById(line->m_pText);  // vt+0x88
        }
    }
}

// 0x001f59e8 CKSekens_UpdateVideoSubtitles_maybe
void CKSekens::UpdateVideoSubtitles(double elapsedSeconds, int32_t updateText) {
    const int32_t current = m_i32CurrentLine;
    if (current != -1) {
        const float lineEnd = m_fLineStartTime + Line(this, static_cast<uint32_t>(current))->m_fTime;
        if (static_cast<double>(lineEnd) < elapsedSeconds && m_pText != nullptr) {
            if (static_cast<int32_t>(m_vBlocks.m_ui32NbUsedElt) - 1 == current) {
                m_i32CurrentLine = -1;
            } else {
                m_fLineStartTime = lineEnd;
                m_i32CurrentLine = current + 1;
                CKSekensElement* line = Line(this, static_cast<uint32_t>(current + 1));
                bool ended = false;
                while (line->IsKindOfClass(0x660c) != 0) {  // markers are passed
                    line->m_unk08 = 1;
                    ++m_i32CurrentLine;
                    if (static_cast<int32_t>(m_vBlocks.m_ui32NbUsedElt) == m_i32CurrentLine) {
                        m_i32CurrentLine = -1;
                        ended = true;
                        break;
                    }
                    line = Line(this, static_cast<uint32_t>(m_i32CurrentLine));
                }
                if (!ended) {
                    CKSekensBlock* block = static_cast<CKSekensBlock*>(line);
                    if (block->m_pText == nullptr) {
                        m_pText->SetTextAscii("");
                    } else {
                        m_pText->SetTextById(block->m_pText);
                    }
                }
            }
        }
    }
    if (updateText != 0 && m_pText != nullptr) {
        if (m_i32CurrentLine == -1 || (Sekensor()->m_unk2c & 1) == 0) {
            m_pText->Disable();  // vt+0x68
        } else {
            m_pText->Enable();  // vt+0x64
        }
    }
}

// 0x001f4fd8 CKSekens_ShouldShowSubtitles_maybe
uint8_t CKSekens::ShouldShowSubtitles(uint32_t subtitlesOn) const {
    if ((m_pDataBuffers->m_unk05 != 0 || m_unk78 != 0 || m_unk7c != 0) && (m_flags & 0x20) != 0 && m_ui32SpeechState != 2) {
        const float* lineTimes = reinterpret_cast<const float*>(m_pDataBuffers->m_aWords0);
        if (subtitlesOn == 0 || m_ui32SpeechState == 0 || m_ui32SpeechState == 1) return 0;
        if ((m_flags & 1) != 0 && ((m_flags & 2) == 0 || (m_flags & 0x800) == 0 ||
                                   static_cast<int32_t>(m_vBlocks.m_ui32NbUsedElt) <= m_i32CurrentLine ||
                                   lineTimes[m_i32CurrentLine] == 0.0f))
            return 0;
    }
    return 1;
}

// 0x001f5f18 CKSekens_AdvanceToNextLine_maybe
uint8_t CKSekens::AdvanceToNextLine() {
    for (;;) {
        ++m_i32CurrentLine;
        CKSekensElement* element = Line(this, static_cast<uint32_t>(m_i32CurrentLine));
        if (element->IsKindOfClass(0x65cc) != 0) break;
        element->m_unk08 = 1;
    }
    StartLine(m_i32CurrentLine, 0);
    return 1;
}

// 0x001f6d98 CKSekens_Update_maybe. A sekens bound to a video (+0x7c, which nothing in the ported code sets) follows the
// video's clock like the video bloc's UpdateVideoSubtitles; the others run their current line.
uint8_t CKSekens::Update(IKTime* time, uint8_t skip) {
    if (m_unk7c == 0) return UpdateCurrentLine(time, skip);
    DOTD_STUB_ONCE("CKSekens_Update_maybe 0x1f6d98: a sekens bound to a video (+0x7c) is not reachable");
    return 0;
}

// 0x001f6410 CKSekens_UpdateCurrentLine_maybe. The line ends when the time it was given (the data buffers' first words,
// and the block's own time) has gone, or - a line with speech - when the speech stream has played up to the end of
// the line's time (the last line: when the stream is over). A line gets at least two updates; the results are those of
// Update. The control flow follows the original's labels.
uint8_t CKSekens::UpdateCurrentLine(IKTime* time, uint8_t skip) {
    int32_t line = m_i32CurrentLine;
    uint32_t flags;
    uint32_t finished = skip;  // param_3
    CKSekensBlock* block;
    const float* lineTimes = reinterpret_cast<const float*>(m_pDataBuffers->m_aWords0);
    const float* volumes = reinterpret_cast<const float*>(m_pDataBuffers->m_aWords1);
    float now;
    float elapsed;
    double dt;
    double speechLength;
    bool last;
    int32_t localItem;
    float localPosition;
    bool streamFinished;
    double position;
    if (line < 0) return 2;
    flags = m_flags;
    if ((flags & 8) != 0) return 0;
    block = static_cast<CKSekensBlock*>(Line(this, static_cast<uint32_t>(line)));
    ++m_unk3c;
    if ((flags & 0x400) != 0) goto label_649c;
    now = time->m_afCurrentTime[IKTime::FIXED_GAME_TIME];
    elapsed = now - m_fLineStartTime;
    dt = static_cast<double>(time->m_afDeltaTime[IKTime::FIXED_GAME_TIME]);
    if (m_ui32SpeechState == 2) {
        double offset = 0.0;
        double lineEnd = static_cast<double>(lineTimes[line]);
        if (0.0 <= static_cast<double>(block->m_fTime)) lineEnd = static_cast<double>(static_cast<float>(lineEnd + static_cast<double>(block->m_fTime)));
        const uint8_t item = m_pDataBuffers->m_aBytes[line];
        for (int32_t i = 0; i < line; ++i) {
            offset = static_cast<double>(static_cast<float>(offset + static_cast<double>(lineTimes[i] + Line(this, static_cast<uint32_t>(i))->m_fTime)));
        }
        finished = lineEnd <= static_cast<double>(elapsed) ? 1 : 0;
        m_pStreamObject->SetFloat20AndInt1C(static_cast<float>(offset), static_cast<int32_t>(m_unk68) + item);
        flags = m_flags;
        goto label_64a0;
    }
    if (m_ui32SpeechState != 3) {
        if (m_ui32SpeechState == 0) {
            // The speech stream starts (the same as the first line's StartLine).
            finished = 0;
            const uint8_t item = m_pDataBuffers->m_aBytes[line];
            const float volume = volumes[line];
            SoundStreamType* speech = StreamType(kSpeech);
            m_pStreamObject->m_unk24 = 0;
            m_pStreamObject->m_unk28 = volume;
            m_pStreamObject->Play(speech, 0);
            m_pStreamObject->SetFloat20AndInt1C(0.0f, static_cast<int32_t>(item) + static_cast<int32_t>(m_unk68));
            m_flags = (m_flags & 0xfffffffeu) | 1;
            flags = m_flags;
            m_ui32SpeechState = 3;
            goto label_64a0;
        }
        goto label_649c;
    }
    if (block->m_unk14 == -1.0f) goto label_64a0;
    if (finished != 0 && (flags & 4) != 0) goto label_649c;  // skipped, and the sekens can be
    speechLength = static_cast<double>(lineTimes[line]);
    localPosition = 0.0f;
    localItem = 0xff;
    last = true;
    {
        const int32_t count = static_cast<int32_t>(m_vBlocks.m_ui32NbUsedElt);
        if (line + 1 < count) {
            for (int32_t j = line + 1;; ++j) {
                CKSekensElement* following = Line(this, static_cast<uint32_t>(j));
                if (following->Vf58() != 0) break;
                if (following->IsKindOfClass(0x65cc) != 0) {
                    last = false;
                    break;
                }
                if (count <= j + 1) break;
            }
            flags = m_flags;
        }
    }
    if (speechLength == 0.0 || (flags & 1) == 0) goto label_68e8;
    if ((flags & 2) == 0) {
        if (static_cast<double>(elapsed) <= 3.0) goto label_68e8;
        goto label_649c;
    } else {
        float limit;
        if (m_unk78 == 0) {
            limit = static_cast<float>(static_cast<double>(static_cast<float>(speechLength + static_cast<double>(block->m_fTime))) + 3.0);
        } else {
            limit = static_cast<float>(speechLength + 3.0);
        }
        if (static_cast<double>(elapsed) <= static_cast<double>(limit)) goto label_68e8;
        goto label_649c;
    }
label_68e8:
    if ((flags & 1) != 0 && speechLength != 0.0) {
        if ((flags & 2) == 0 && m_pStreamObject->HasPlayer()) {  // the stream has its player: the line starts now
            m_flags = (m_flags & 0xfffffffdu) | 2;
            flags = m_flags;
            m_fLineStartTime = now;
        }
        if ((flags & 2) == 0) {
            finished = 0;
            goto label_64a0;
        }
        localPosition = 0.0f;
        localItem = 0xff;
        m_pStreamObject->GetPlaybackPosition(&localItem, &localPosition);
        streamFinished = m_pStreamObject->IsFinished() != 0;
        if (!streamFinished && static_cast<int32_t>(m_unk68) + m_pDataBuffers->m_aBytes[line] != localItem) {
            flags = m_flags;
            finished = 0;
            goto label_64a0;
        }
        position = static_cast<double>(localPosition);
        if (position <= 0.0) {
            if (!last) goto label_6afc;
            goto label_6b84;
        }
        m_flags = (m_flags & 0xfffff7ffu) | 0x800;
        if (last) goto label_6b84;
        localPosition = static_cast<float>(dt + static_cast<double>(static_cast<float>(
                            dt + static_cast<double>(static_cast<float>(dt + static_cast<double>(static_cast<float>(dt + static_cast<double>(localPosition))))))));
        position = static_cast<double>(localPosition);
    label_6afc:
        if (position < static_cast<double>(m_fSpeechTime)) goto label_6b84;
        finished = 1;
        flags = m_flags;
        goto label_64a0;
    label_6b84:
        flags = m_flags;
        finished = streamFinished ? 1 : 0;
        goto label_64a0;
    }
    if (0.0 < static_cast<double>(block->m_unk14)) {  // a line without speech waits for its own time
        finished = 0;
        block->m_unk14 = static_cast<float>(static_cast<double>(block->m_unk14) - dt);
        flags = m_flags;
        goto label_64a0;
    }
label_649c:
    finished = 1;
label_64a0:
    if ((flags & 0x400) != 0 || (finished & 0xff) != 0) {
        if (static_cast<int32_t>(m_unk3c) < 2) {  // a line is updated twice at least
            m_flags = (m_flags & 0xfffffbffu) | 0x400;
            return 0;
        }
        if ((finished & 0xff) != 0) {
            int32_t index = m_i32CurrentLine;
            const int32_t count = static_cast<int32_t>(m_vBlocks.m_ui32NbUsedElt);
            int32_t next = index + 1;
            if (next < count) {
                for (int32_t j = index + 1; j < count; ++j) {
                    CKSekensElement* following = Line(this, static_cast<uint32_t>(j));
                    if (following->Vf58() != 0) break;
                    if (following->IsKindOfClass(0x65cc) != 0) return 1;  // a text block follows
                }
                index = m_i32CurrentLine;
            }
            index = index + 1;
            m_i32CurrentLine = index;
            for (;;) {
                if (count <= index) return 2;
                CKSekensElement* following = Line(this, static_cast<uint32_t>(index));
                if (following->IsKindOfClass(0x660c) == 0) {
                    if (following->Vf58() != 0) return 2;
                } else {
                    following->m_unk08 = 1;  // a marker passed
                }
                index = m_i32CurrentLine + 1;
                m_i32CurrentLine = index;
            }
        }
    }
    return 0;
}
