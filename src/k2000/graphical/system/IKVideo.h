// IKVideo.h - base of the videos (key 0xa0d, vtable 0xb17370). Its code is in PS3_CKVideo.cpp
// (0xa9bd0-0xaee90). XXL2: K/KModules/KGL/Main/Video/IKVideo.h; DotD's Load reads the same fields in the
// same order (m_baData, m_szFileName, m_ui32AlphaLevel, m_fRatio for GAME; m_tsEndVideoTrigger and
// m_pTexture for the level). DotD's file name is 0x100 bytes (XXL2: 1024).
//
// The playback runtime (C1.4) is shared with PS3_CKVideo: IKVideo's bodies for slots +0x54 (BeginPlayback),
// +0x64 (UpdatePlaybackState), +0x68 (UpdateFrame), +0x78 (StopImpl) are what PS3_CKVideo's overrides call.
// IKVideo's own versions of the RenderWare-texture slots (+0x6c, +0x70, +0x8c..+0xa0, +0x84) are not
// reachable in DotD (PS3_CKVideo, the only subclass, overrides every one of them) and are not ported.
//
// m_baData bits (the KP3 flags; the low nibble is forced to 8 by the Load). Names ours, from the code:
//   0x1 playing (frames are produced)       0x2 paused                     0x4 stream open
//   0x10 / 0x20 leave renderer +0xa4 bit 1 / bit 2 alone (else the video sets them: no 3D / no UI behind it)
//   0x40 no screen quad (a video-to-texture)  0x200 hidden                  0x400 loop at the end
//   0x800 fit to the screen (letterbox/pillarbox)  0x1000 keep the game sounds  0x2000 reached the end
//   0x4000 the loading video                0x20000 / 0x200000 open flags   0x40000 mute the game sounds
//   0x100000 a cutscene (CKSrvCinematic: skip prompt, pause count)      0x800000 fit to the height
// m_baFrameFlags bits: 0x1 suspended by the clock (IKTime state 3)   0x2 restart the stream (read error)
//   0x4 set on (re)start   0x8 a frame was decoded this tick   0x10 a seek is pending (to m_seekFrame)
//   0x20 the first frames after a start (no pausing for 4 frames)   0x40 / 0x80 like m_baData 0x20 / 0x10
//   0x100 seeked   0x200 the seek goes to the exact frame (else the closest keyframe)   0x400 started
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"
#include "k2000/services/CTriggerStarter.h"

struct BINK;
class CKVideoSegment;
class IKTime;

class IKVideo : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryGraphical, 0x28)  // vt+0x14 / +0x18  0x9a0688 / 0x9a0690

    IKVideo();                   // 0x000ab2a8 (Ghidra PS3_CKVideo_ConstructBase_maybe; stores the IKVideo vtable)
    ~IKVideo() override {}       // 0x009a0728 / 0x009a06e8 IKVideo_vf0 / IKVideo_DeletingDestructor: the vtables only
    // vt+0x08 0x9a06c8
    int32_t IsKindOfClass(uint32_t key) override { return key == 0xa0d || key == 0xc; }
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x000ad5f8 IKVideo_Load
    int32_t PostLoad(int32_t type) override;            // vt+0x30 0x000ac410 IKVideo_vf30
    const uint32_t* GetGuid() override { return m_guidIdentifier; }  // vt+0x44 0x9a0668
    void SetGuid(const uint32_t* guid) override;                     // vt+0x48 0x9a0698
    // vt+0x0c 0x000abc88 IKVideo_vfC (DestroyGame; PS3_CKVideo_DestroyGame 0xae4f8 only calls it): the texture forgotten.
    void DestroyGame() override { m_pTexture = nullptr; }
    // vt+0x24 0x000ab2c8 IKVideo_vf24 (RecursiveRegistration; PS3_CKVideo's 0xae4d0 only calls it): registered with the
    // saving manager for types 0 and 1; type 0 also the end trigger's (KStub_Return1_2361b0: nothing).
    void RecursiveRegistration(int32_t type) override;
    // vt+0x40 0x000abb50 PS3_CKVideo_GetInfo: value 5 is the playback position (an integer, 0x000ac4a0).
    int32_t GetInfo(IKInfo* info, int32_t request) override;
    // vt+0x10 0x000ae520 PS3_CKVideo_Destroy: ReleaseTexture.
    void Destroy() override { ReleaseTexture(); }
    // 0x000abc98 PS3_CKVideo_ReleaseTexture_maybe: a video-to-texture (0x40) destroys its texture (RwTextureDestroy) and
    // forgets it; then the stream closed (vt+0x58).
    void ReleaseTexture();

    // ---- the video slots (vt+0x50..+0xa0) ----
    virtual int32_t Vf50() { return 1; }                      // vt+0x50 0x9a0680 PS3_CKVideo_vf50
    virtual int32_t Play();                                   // vt+0x54 0x000ac740 PS3_CKVideo_BeginPlayback_maybe
    virtual void CloseStreamIfOpen();                         // vt+0x58 0x000a9c50 PS3_CKVideo_CloseStreamIfOpen_maybe
    virtual void Reopen();                                    // vt+0x5c 0x000a9cc8 PS3_CKVideo_vf5C
    virtual int32_t Start(CKVideoSegment* segment);           // vt+0x60 0x000ad2c0 PS3_CKVideo_vf60
    virtual void Update(IKTime* frameClock);                  // vt+0x64 0x000ad890 PS3_CKVideo_UpdatePlaybackState_maybe
    virtual uint8_t UpdateFrame(IKTime* frameClock);          // vt+0x68 0x000ac908 PS3_CKVideo_UpdateFrame_maybe
    virtual int32_t CopyFrameToTexture(int32_t) { return 0; } // vt+0x6c 0xad4d0 IKVideo_vf6C  STUB (RW texture path)
    virtual void SelectNextFrame() {}                         // vt+0x70 0xaaa28 IKVideo_vf70  STUB (RW texture path)
    virtual void AdvanceFrame();                              // vt+0x74 0x000ab1c8 PS3_CKVideo_AdvanceFrame_maybe
    virtual void Stop();                                      // vt+0x78 0x000ab890 PS3_CKVideo_StopImpl_maybe
    virtual void Pause();                                     // vt+0x7c 0x000aafe0 PS3_CKVideo_Pause_maybe
    virtual void Resume();                                    // vt+0x80 0x000aaf60 PS3_CKVideo_vf80
    virtual void Draw(IKTime* frameClock);                    // vt+0x84 0x000abd20 IKVideo_DrawPlaceholderQuad_maybe
    virtual int32_t Vf88() = 0;                               // vt+0x88 (pure in IKVideo)
    virtual void CreateFrameTextures() {}                     // vt+0x8c 0xabeb8 IKVideo_vf8C  STUB (RW texture path)
    virtual void DestroyFrameTextures() {}                    // vt+0x90 0xab0e8  STUB (RW texture path)
    virtual void RegisterFrameBuffers() {}                    // vt+0x94 0xaa8d8 IKVideo_vf94 (empty)
    virtual void Vf98() {}                                    // vt+0x98 0xab450 IKVideo_vf98  STUB (RW texture path)
    virtual BINK* OpenStream();                               // vt+0x9c 0x000acd90 PS3_CKVideo_OpenBink_maybe
    virtual void CloseStream() {}                             // vt+0xa0 0xab070 IKVideo_vfA0  STUB (RW texture path)

    // ---- non-virtual helpers (PS3_CKVideo.cpp) ----
    void ComputeDisplayRect();            // 0x000a9d38 PS3_CKVideo_ComputeDisplayRect_maybe
    void SetRenderStates();               // 0x000a9f50 PS3_CKVideo_SetRenderStates_maybe
    void SetFadeLevel(uint32_t level);    // 0x000aa370 PS3_CKVideo_SetFadeLevel_maybe
    void SeekToKeyFrameNear(int32_t frame);  // 0x000aa398 PS3_CKVideo_SetCurrentAndTargetFrame_maybe
    void SeekToFrame(int32_t frame);         // 0x000ab260 PS3_CKVideo_SetCurrentAndTargetFrame_VariantB_maybe
    int32_t GetFrameCount();              // 0x000aa920 PS3_CKVideo_GetFrameCount_maybe
    void StopIfEnded();                   // 0x000ab3e0 PS3_CKVideo_StopIfEnded_maybe
    double GetElapsedSeconds();           // 0x000abe58 PS3_CKVideo_GetElapsedSeconds_maybe
    int32_t GetPlaybackPosition();        // 0x000ac4a0 PS3_CKVideo_GetPlaybackPosition_maybe
    void SetSegment(CKVideoSegment* segment);  // 0x000acf00 PS3_CKVideo_SetSegment_maybe
    int32_t RestartSegmentOrLoop();       // 0x000ad040 PS3_CKVideo_RestartSegmentOrLoop_maybe
    // 0x000abbc0 PS3_CKVideo_MessageProc (vt+0x1c): 0x2502 stops, 0x2501 starts, 0x2504 is swallowed. The
    // port's MessageProc slot has no arguments yet, so this is the body under its own name.
    int32_t HandleMessage(uint32_t message);
    bool IsPlaying() const { return m_state != 0; }  // the test the game makes on +0x190

    uint32_t m_baData;               // +0x004 (XXL2 CBitArray) flags, see above
    uint32_t m_baFrameFlags;         // +0x008 (XXL2 CBitArray) playback flags, see above
    char m_szFileName[0x100];        // +0x00c read without a length limit
    BINK* m_pBink;                   // +0x10c Load (GAME) sets 0
    uint32_t m_unk110;               // +0x110 a KFileSystem file handle (closed by CloseStream); Load (GAME) sets 0
    float m_fScaleX;                 // +0x114 ComputeDisplayRect: screen pixels per video pixel. Names ours.
    float m_fScaleY;                 // +0x118
    float m_fPosX;                   // +0x11c the top-left corner in screen pixels
    float m_fPosY;                   // +0x120
    uint32_t m_ui32AlphaLevel;       // +0x124
    void* m_pTexture;                // +0x128 the texture reference (level data); RwTexture*
    void* m_apRaster;                // +0x12c Load (GAME) sets 0 (XXL2 RwRaster**)
    uint32_t m_ui32RasterNb;         // +0x130 Load (GAME) sets 0
    uint32_t m_unk134[7];            // +0x134 not written by the constructor or Load
    CTriggerStarter m_tsEndVideoTrigger;  // +0x150 signalled by Stop
    uint32_t m_guidIdentifier[4];    // +0x158 the constructor sets 0; the loader's SetGuid
    float m_fRatio;                  // +0x168 height / width of the picture
    int32_t m_resumeFrame;           // +0x16c the frame the stream reopens at (start frame, then position). Ours.
    int32_t m_seekFrame;             // +0x170 the pending seek's frame (-1 = none). Name ours.
    uint8_t m_seekHoldFrames;        // +0x174 frames counted after a start (UpdateFrame, up to 4). Name ours.
    uint8_t m_pad175[3];
    uint32_t m_unk178;               // +0x178 not written by the playback code
    int32_t m_startFrame;            // +0x17c RestartSegmentOrLoop: the frame it started at. Name ours.
    int32_t m_unk180;                // +0x180 Start sets -1
    int32_t m_unk184;                // +0x184 Load (GAME) sets -1; the cutscene skip counter (flag 0x100000)
    CKVideoSegment* m_pSegment;      // +0x188 the segment being played (PostLoad: 0)
    uint32_t m_blendIndex;           // +0x18c 1 when m_ui32AlphaLevel != 0xff: blend table entry. Name ours.
    int32_t m_state;                 // +0x190 0 stopped, 1 starting, 2 waiting for the loop's pause, 3 waiting
                                     //        for the game sounds to stop, 4 open, 5 playing, 6 reopening.
                                     //        Load (GAME) sets 0 (CVideoManager_IsLoadingVideoActive_maybe)
};
DOTD_ASSERT_OFFSET(IKVideo, m_baData, 0x004);
DOTD_ASSERT_OFFSET(IKVideo, m_szFileName, 0x00c);
DOTD_ASSERT_OFFSET(IKVideo, m_pBink, 0x10c);
DOTD_ASSERT_OFFSET(IKVideo, m_fScaleX, 0x114);
DOTD_ASSERT_OFFSET(IKVideo, m_fPosY, 0x120);
DOTD_ASSERT_OFFSET(IKVideo, m_ui32AlphaLevel, 0x124);
DOTD_ASSERT_OFFSET(IKVideo, m_pTexture, 0x128);
DOTD_ASSERT_OFFSET(IKVideo, m_ui32RasterNb, 0x130);
DOTD_ASSERT_OFFSET(IKVideo, m_tsEndVideoTrigger, 0x150);
DOTD_ASSERT_OFFSET(IKVideo, m_guidIdentifier, 0x158);
DOTD_ASSERT_OFFSET(IKVideo, m_fRatio, 0x168);
DOTD_ASSERT_OFFSET(IKVideo, m_resumeFrame, 0x16c);
DOTD_ASSERT_OFFSET(IKVideo, m_seekFrame, 0x170);
DOTD_ASSERT_OFFSET(IKVideo, m_seekHoldFrames, 0x174);
DOTD_ASSERT_OFFSET(IKVideo, m_startFrame, 0x17c);
DOTD_ASSERT_OFFSET(IKVideo, m_unk184, 0x184);
DOTD_ASSERT_OFFSET(IKVideo, m_pSegment, 0x188);
DOTD_ASSERT_OFFSET(IKVideo, m_blendIndex, 0x18c);
DOTD_ASSERT_OFFSET(IKVideo, m_state, 0x190);
