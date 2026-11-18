// CKSekens.h - a sekens: a scripted sequence of speech / subtitle blocks (key 0xf4c, vtable 0xb1ea18,
// size 0x80). Original unit: CKSekens.cpp. XXL2: K/KServices/KServiceSekensor/CKSekens.h has other
// members (it keeps SSekensBlock records); DotD's blocks are objects (CKSekensBlock / CKSekensMarker) and
// the localisation file (type 2) gives each sekens its timing buffers. Names ours unless noted.
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"
#include "k2000/services/CTriggerStarter.h"
#include "k2000/util/TVector.h"

// The localisation buffers of a sekens (0x10 bytes, OperatorNew). Functions in CKStreamObject.cpp.
class CKStreamObject;
class CText2d;
class IKFile;
class IKTime;

struct CKSekensDataBuffers {
    CKSekensDataBuffers();  // 0x0011ada0 CKSekensDataBuffers_Construct_maybe
    void Free();            // 0x0011adc0 CKSekens_FreeDataBuffers_maybe
    // 0x0011ae30 CKSekens_LoadDataBuffers_maybe: only for type 2 (K_LEVEL_LOCALIZATION).
    int32_t Load(IKFile* file, int32_t type);

    uint32_t* m_aWords0;  // +0x00 m_count words (Mem_AllocAligned16)
    uint8_t m_count;      // +0x04
    uint8_t m_unk05;      // +0x05
    uint8_t m_pad06[2];
    uint32_t* m_aWords1;  // +0x08 m_count words
    uint8_t* m_aBytes;    // +0x0c m_count bytes
};
DOTD_ASSERT_SIZE(CKSekensDataBuffers, 0x10);

class CKSrvSekensor;

class CKSekens : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x3d)
    DOTD_DECLARE_FACTORIES(CKSekens)

    CKSekens();  // inlined in 0x001f6cc8 CKSekens_Create (CKSekens_Construct 0x1f3de8)
    ~CKSekens() override {}

    int32_t IsKindOfClass(uint32_t key) override { return key == kClassKey || key == 0xc; }  // 0x9b0cd8
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001f50b0 CKSekens_Load
    // vt+0x30 0x001f4c60 CKSekens_PostLoad: the level type (0) clears bit 3, hides the text, counts the lines that take
    // part in the choice (Vf58) to size the unplayed-lines list (order modes 0-2) and makes the speech stream object.
    int32_t PostLoad(int32_t type) override;
    // vt+0x38 0x001f3ec0 CKSekens_SetDefaultState: the earliest start back to -1.0 and the text hidden (any flag).
    void SetDefaultState(int32_t flag) override;
    // vt+0x1c 0x001f4ed0 CKSekens_MessageProc: 0x2701 asks the sekensor to run it (RequestSekens), 0x2702 to stop it
    // (StopSekens); 0 for those two, 1 for the others.
    int32_t MessageProc(uint16_t message, void* data) override;
    // vt+0x40 0x001f4f80 CKSekens_GetInfo: the trigger value 4, whether it is the sekensor's current sekens (a byte;
    // accessor 0x1f4a30 Sekensor_IsCurrentSekens_maybe).
    int32_t GetInfo(struct IKInfo* info, int32_t request) override;

    // 0x001f56b0 CKSekens_Stop_maybe (returns 1).
    int32_t Stop();
    // 0x001f5fe0 CKSekens_Begin_maybe: the sekens starts: its lines unmarked, the first line chosen by the order mode
    // (m_ui32OrderMode: 0 in sequence, 1 random, 2 random without repeat), marked seen in the level, the begin
    // triggers queued, the first block started and the music ducked. 0 without lines, else 1.
    uint8_t Begin();
    void Destroy() override;                          // vt+0x10 0x001f4800 CKSekens_Destroy
    void PauseSound();                                // 0x001f45a0 CKSekens_PauseSound_maybe (no caller in the original)
    void ResumeSound();                               // 0x001f4b70 CKSekens_ResumeSound_maybe (no caller in the original)
    void StopSpeechStream();                          // 0x001f45d8 CKSekens_StopSpeechStream_maybe (no caller in the original)
    void PlaySpeechStream(float volume);              // 0x001f4660 CKSekens_PlaySpeechStream_maybe (no caller in the original)
    void ForEachLineCallVf54(uint8_t a, uint32_t b);  // 0x001f4ac0 CKSekens_ForEachLineCallVf54_maybe (CKSrvSekensor_vfA8)
    // 0x001f4c58 KStub_Nop_1f4c58: empty (CKSrvSekensor_UpdateLocalizedData calls it on the current sekens).
    void LocalizedDataChanged(uint8_t /*a*/, uint32_t /*b*/) {}
    // 0x001f5bf8 CKSekens_StartLine_maybe: line `line` starts: its times, the speech stream when the sekens has one
    // and the subtitle text. `first` is 1 for the first line of the sekens.
    void StartLine(int32_t line, int32_t first);
    // 0x001f6d98 CKSekens_Update_maybe: one frame of the sekens: 0 going on, 1 the line is over and the next block starts,
    // 2 the sekens is over. `skip` says the player pressed the dialogue button.
    uint8_t Update(IKTime* time, uint8_t skip);
    // 0x001f6410 CKSekens_UpdateCurrentLine_maybe (the same results): the current line's time, or its speech stream, runs
    // out; with skip an interruptible line ends at once.
    uint8_t UpdateCurrentLine(IKTime* time, uint8_t skip);
    // 0x001f5f18 CKSekens_AdvanceToNextLine_maybe: the next text block starts (the blocks between are marked seen); 1.
    uint8_t AdvanceToNextLine();
    // 0x001f4fd8 CKSekens_ShouldShowSubtitles_maybe: whether the subtitle text is shown (`subtitlesOn`: the sekensor's option).
    uint8_t ShouldShowSubtitles(uint32_t subtitlesOn) const;
    // 0x001f59e8 CKSekens_UpdateVideoSubtitles_maybe: the line changes when the video's elapsed seconds pass its end; with
    // `updateText` the subtitle text is shown or hidden.
    void UpdateVideoSubtitles(double elapsedSeconds, int32_t updateText);
    // 0x001f3eb0 CKSekens_GetCurrentLineIndex_maybe
    int32_t GetCurrentLineIndex() const { return m_i32CurrentLine; }
    // 0x001f40a8 CKSekens_CallCurrentLineVf5C_maybe: the current line's (block's) text (vt+0x5c), null without a line.
    IKSerializable* CallCurrentLineVf5C() const;
    // 0x001f4118 CKSekens_SetFlag14Bit3_maybe: bit 3 of the flags (the sekens follows a video, not the clock); set, it
    // also puts the earliest start time to -1.
    void SetFlag14Bit3(int32_t value) {
        m_flags = (m_flags & 0xfffffff7u) | (static_cast<uint32_t>(value) << 3);
        if (value != 0) m_fEarliestStart = -1.0f;
    }
    // 0x001f4148 CKSekens_SetStreamStartPaused_maybe: the speech stream object's start-paused byte (+0x3a).
    void SetStreamStartPaused(uint8_t paused);
    // 0x001f4558 CKSekens_PollStreamPlaybackPosition_maybe: the seconds the speech stream has played (0 without one
    // playing; the item is not used).
    float PollStreamPlaybackPosition() const;
    // 0x001f4ba8 CKSekens_IsStreamVoiceActive_maybe: whether the speech stream's player is in the state asked of it.
    uint8_t IsStreamVoiceActive() const;
    // 0x001f4c00 CKSekens_StartPausedStream_maybe: the line's start time taken from the clock and the speech stream
    // unpaused, when its player exists.
    void StartPausedStream();
    // 0x001f41e0 CKSekens_UsesSpeechStream_maybe: its data buffers say it has a speech stream.
    uint8_t UsesSpeechStream() const;
    // 0x001f4a88 CKSekens_GetSekensorDelayByIndex54_maybe
    float GetSekensorDelay() const;

    CTriggerStarter m_tsOnStop;          // +0x04 queued by Stop (the Load reads it first)
    CTriggerStarter m_tsOnBegin;         // +0x0c queued by Begin
    uint32_t m_flags;                    // +0x14 bit 0 a speech stream plays, 3 the video drives it, 5 idle, 6 interruptible, 7, 8 seen,
                                         // 9 secondary (a background sekens), 11, 13 no music ducking; bits 2, 6, 7, 9 from the file
    uint32_t m_uuid[4];                  // +0x18 Uuid_Read; the constructor clears it
    int32_t m_i32CurrentLine;            // +0x28 the constructor sets -1 (XXL2 m_i32CurrentBlock _maybe); -1 = none
    CText2d* m_pText;                    // +0x2c the subtitle text (a CText2d in the files)
    CKSekensDataBuffers* m_pDataBuffers; // +0x30 the localisation's buffers (type 2)
    CKStreamObject* m_pStreamObject;     // +0x34 PostLoad makes it (class 0x5a4c); the constructor sets null
    float m_fLineStartTime;              // +0x38 the clock (or video) time the current line started
    uint32_t m_unk3c;                    // +0x3c cleared by StartLine
    TVector<IKSerializable*, 10> m_vBlocks;  // +0x40 CKSekensBlock / CKSekensMarker references
    uint32_t m_ui32BeginDelayIndex;      // +0x4c index in the sekensor's delay table: Begin's earliest start
    float m_fEarliestStart;              // +0x50 the constructor sets -1.0; the clock time before which it cannot start
    uint32_t m_ui32DelayIndex;           // +0x54 index in the sekensor's delay table (GetSekensorDelay)
    uint32_t m_ui32OrderMode;            // +0x58 0 in sequence, 1 random, 2 random without repeat
    TVector<uint32_t, 8> m_vUnplayedLines;  // +0x5c the line indices still to choose from (Begin refills it)
    uint32_t m_unk68;                    // +0x68 the localisation's word (type 2)
    uint32_t m_unk6c;                    // +0x6c
    float m_fSpeechTime;                 // +0x70 the speech time accumulated by StartLine
    uint32_t m_ui32SpeechState;          // +0x74 StartLine sets 3 for a sekens without speech stream
    uint8_t m_unk78;                     // +0x78 a byte from the file
    uint8_t m_pad79[3];
    uint32_t m_unk7c;                    // +0x7c the constructor sets 0
};
DOTD_ASSERT_SIZE(CKSekens, 0x80);
DOTD_ASSERT_OFFSET(CKSekens, m_tsOnBegin, 0x0c);
DOTD_ASSERT_OFFSET(CKSekens, m_flags, 0x14);
DOTD_ASSERT_OFFSET(CKSekens, m_uuid, 0x18);
DOTD_ASSERT_OFFSET(CKSekens, m_i32CurrentLine, 0x28);
DOTD_ASSERT_OFFSET(CKSekens, m_pText, 0x2c);
DOTD_ASSERT_OFFSET(CKSekens, m_pDataBuffers, 0x30);
DOTD_ASSERT_OFFSET(CKSekens, m_pStreamObject, 0x34);
DOTD_ASSERT_OFFSET(CKSekens, m_vBlocks, 0x40);
DOTD_ASSERT_OFFSET(CKSekens, m_ui32BeginDelayIndex, 0x4c);
DOTD_ASSERT_OFFSET(CKSekens, m_ui32DelayIndex, 0x54);
DOTD_ASSERT_OFFSET(CKSekens, m_ui32OrderMode, 0x58);
DOTD_ASSERT_OFFSET(CKSekens, m_vUnplayedLines, 0x5c);
DOTD_ASSERT_OFFSET(CKSekens, m_unk68, 0x68);
DOTD_ASSERT_OFFSET(CKSekens, m_unk78, 0x78);
DOTD_ASSERT_OFFSET(CKSekens, m_unk7c, 0x7c);
