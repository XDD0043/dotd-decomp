// PS3_CKVideo.h - a Bink video on the PS3 (key 0xa4d, vtable 0xb17420, size 0x23c). Original unit:
// PS3_CKVideo.cpp (0xa9bd0-0xaee90, with IKVideo's code). GAME.KP3 holds the 74 videos (with GUIDs);
// LVL000 their level data (globals). Playback: Start (vt+0x60) puts the video in the CVideoManager's
// running list (the loading video, flag 0x4000, is driven by the manager directly); every frame the
// manager calls Update (vt+0x64: the state machine, seeks, BinkWait and the decode), UpdateFrame
// (vt+0x68: frame pacing, segment loops, the end) and Draw (vt+0x84: the screen quad).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/graphical/system/IKVideo.h"
#include "platform/video/bink.h"

class PS3_CKVideo : public IKVideo {
public:
    DOTD_CLASS_KEY(kCategoryGraphical, 0x29)
    DOTD_DECLARE_FACTORIES(PS3_CKVideo)

    PS3_CKVideo() {}                 // 0x000ae7e8 PS3_CKVideo_Create: IKVideo's constructor, then the vtable
    ~PS3_CKVideo() override {}       // 0x009a07c0 / 0x009a0778 PS3_CKVideo_Destructor / _DeletingDestructor: the vtables only
    // vt+0x08 0x9a0740
    int32_t IsKindOfClass(uint32_t key) override { return key == 0xa4d || key == 0xa0d || key == 0xc; }
    int32_t Load(IKFile* file, int32_t type) override;      // vt+0x2c 0x000ae480 PS3_CKVideo_Load
    int32_t PostLoad(int32_t type) override;                // vt+0x30 0x000ae458 PS3_CKVideo_PostLoad
    int32_t GetSerializationFlags() override { return 1; }  // vt+0x34 0x9a0678

    int32_t Play() override;                                 // vt+0x54 0x000aede0 PS3_CKVideo_Play_maybe
    void Update(IKTime* frameClock) override;                // vt+0x64 0x000aec20 PS3_CKVideo_Update_maybe
    uint8_t UpdateFrame(IKTime* frameClock) override;        // vt+0x68 0x000ae408 PS3_CKVideo_UpdateFrameThunk_maybe
    int32_t CopyFrameToTexture(int32_t) override { return 0; }  // vt+0x6c 0x000ae110 PS3_CKVideo_vf6C
    void SelectNextFrame() override;                         // vt+0x70 0x000ae2d0 PS3_CKVideo_SelectNextFrame
    void Stop() override;                                    // vt+0x78 0x000aed08 PS3_CKVideo_Stop_maybe
    void Draw(IKTime* frameClock) override;                  // vt+0x84 0x000ae1b0 DrawPS3VideoFrameQuad
    int32_t Vf88() override { return 0; }                    // vt+0x88 0x000ae118 PS3_CKVideo_vf88
    void CreateFrameTextures() override;                     // vt+0x8c 0x000ae378 PS3_CKVideo_CreateFrameTextures_maybe
    void DestroyFrameTextures() override;                    // vt+0x90 0x000ae340 PS3_CKVideo_DestroyFrameTextures
    void RegisterFrameBuffers() override;                    // vt+0x94 0x000ae300 PS3_CKVideo_vf94
    void Vf98() override {}                                  // vt+0x98 0x000ae120 PS3_CKVideo_vf98
    BINK* OpenStream() override;                             // vt+0x9c 0x000ae840 PS3_CKVideo_OpenStream_maybe
    void CloseStream() override;                             // vt+0xa0 0x000ae9c8 PS3_CKVideo_CloseStream_maybe
    virtual int32_t RestartSegmentOrLoopSlot();              // vt+0xa4 0x000ae430 PS3_CKVideo_vfA4

    // +0x194 the Bink frame buffers and their textures (PS3Video_CreateFrameBuffers_maybe); 0xa8 bytes on
    // the PS3 (BINKFRAMEBUFFERS has the PS3 size in the 32-bit build).
    BINKFRAMEBUFFERS m_frameBuffers;
};
DOTD_ASSERT_OFFSET(PS3_CKVideo, m_frameBuffers, 0x194);
DOTD_ASSERT_SIZE(PS3_CKVideo, 0x23c);
