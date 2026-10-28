// CKVideoSegment.h - a frame range of a video (key 0xd8d, vtable 0xb17298, size 0x28). Original unit:
// CKVideoSegment.cpp. Not in XXL2; the names are ours. LVL000 has three, on PS3_004 (the main-menu
// backgrounds): an intro (start..introEnd) then a loop (loopStart..end). Play (0xa75c8) starts the video on
// the segment or switches the running video to it; every frame UpdateFrame asks IsAtEnd / UpdatePlayback.
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"

class IKVideo;

class CKVideoSegment : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryGraphical, 0x36)
    DOTD_DECLARE_FACTORIES(CKVideoSegment)

    // The end modes (+0x14). 3 passed to Play means "the segment's default" (+0x18).
    enum : uint32_t { kModePause = 0, kModeReportEnd = 1, kModeLoop = 2, kModeDefault = 3 };

    CKVideoSegment();                 // 0x000a7918 CKVideoSegment_Create (inlined; = CKVideoSegment_Construct 0xa7418)
    ~CKVideoSegment() override {}     // STUB(C1.6): 0x9a0610 / 0x9a05b0
    // vt+0x08 0x9a05f0
    int32_t IsKindOfClass(uint32_t key) override { return key == 0xd8d || key == 0xc; }
    // vt+0x2c 0x000a7ad8 CKVideoSegment_Load: reads for K_LEVEL_PLATEFORMS; the last three stores for every type.
    int32_t Load(IKFile* file, int32_t type) override;

    // 0x000a7488 CKVideoSegment_MarkEndedIfPlaying_maybe
    void MarkEndedIfPlaying();
    // 0x000a7520 / 0x000a7530 CKVideoSegment_GetStartFrame_maybe / _GetLoopFrame_maybe
    uint32_t GetStartFrame() const { return m_startFrame; }
    uint32_t GetLoopFrame() const { return m_loopStartFrame; }
    // 0x000a75c8 CKVideoSegment_Play_maybe: mode (kMode*), useLoopStart: the next (re)start begins at the loop
    // instead of the intro; force: also when the segment is already playing.
    void Play(uint32_t mode, uint8_t useLoopStart, int32_t force);
    // 0x000a7790 CKVideoSegment_IsAtEnd_maybe: at the intro's end (a jump to the loop follows), or at the end
    // in loop mode.
    uint8_t IsAtEnd();
    // 0x000a7978 CKVideoSegment_UpdatePlayback_maybe: the jumps; 1 when the end is reached in mode 1.
    uint8_t UpdatePlayback();

    uint32_t m_startFrame;        // +0x04 (LVL000 [0]: 1)
    uint32_t m_introEndFrame;     // +0x08 (0x50)
    uint32_t m_loopStartFrame;    // +0x0c (0x51)
    uint32_t m_endFrame;          // +0x10 (0x62d)
    uint32_t m_mode;              // +0x14 Load sets 0; Play sets it
    uint32_t m_defaultMode;       // +0x18 read after the reference (LVL000: 2)
    uint32_t m_ended;             // +0x1c Load sets 1: not playing
    uint8_t m_useLoopStart;       // +0x20 Load sets 0
    uint8_t m_pad21[3];           // +0x21 never written
    IKVideo* m_pVideo;            // +0x24 a PS3_CKVideo reference (by GUID)
};
DOTD_ASSERT_SIZE(CKVideoSegment, 0x28);
DOTD_ASSERT_OFFSET(CKVideoSegment, m_mode, 0x14);
DOTD_ASSERT_OFFSET(CKVideoSegment, m_defaultMode, 0x18);
DOTD_ASSERT_OFFSET(CKVideoSegment, m_useLoopStart, 0x20);
DOTD_ASSERT_OFFSET(CKVideoSegment, m_pVideo, 0x24);
