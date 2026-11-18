// CVideoManager.h - Bink video playback (key 0x9cd, vtable 0xb172f0, size 0x1cc). Original unit:
// CVideoManager.cpp (0xa81c0-0xa9b40); its loading-video functions are in CKVideoSegment.cpp's unit. XXL2:
// KGL/Main/Video/CVideoManager.h (m_apVideoArray, m_ui32VideoNb, m_lRunningVideo, m_pLoadingVideo,
// m_fOpenFadeTime, m_fCloseFadeTime: the same order and the same GAME Load). A renderer stage manager:
// created by InitializeRendererStages (renderer +0xb4). Every frame it runs the running videos' Update
// (PreUpdate), UpdateFrame (UpdateAndExtract) and Draw (Render, between 2D stages 17 and 18); the loading
// video (+0x24) is not in the list and is updated and drawn by Render.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/graphical/IRendableObject.h"

class CColorizedScreenFx;
class IKVideo;

class CVideoManager : public IRendableObject {
public:
    DOTD_CLASS_KEY(kCategoryGraphical, 0x27)
    DOTD_DECLARE_FACTORIES(CVideoManager)

    // A node of the running-video list (8 bytes, FreeListPool at 0x00ceaa30 in the original).
    struct VideoNode {
        IKVideo* m_pVideo;   // +0x00
        VideoNode* m_pNext;  // +0x04
    };

    CVideoManager();                  // 0x000a9820 CVideoManager_Create (inlined; = CVideoManager_Construct 0xa8488)
    ~CVideoManager() override;        // 0x000a9a98 / 0x000a99e8 CVideoManager_Destructor / _DeletingDestructor
    // vt+0x08 0x9a0628
    int32_t IsKindOfClass(uint32_t key) override { return key == 0x9cd || key == 0xa8d || key == 0xc; }
    void Destroy() override;  // vt+0x10 0x000a8450 CVideoManager_Destroy
    // vt+0x0c 0x000a9068 CVideoManager_DestroyGame: the fade forgotten, the video array (+0x18) freed.
    void DestroyGame() override;
    int32_t Load(IKFile* file, int32_t type) override;      // vt+0x2c 0x000a92a0 CVideoManager_Load
    int32_t GetSerializationFlags() override { return 0; }  // vt+0x34 0x9a0660
    // vt+0x54 0x000a8618 CVideoManager_PreUpdate: every running video's Update (vt+0x64).
    void PreUpdate(IKTime* frameClock) override;
    // vt+0x58 0x000a8a30 CVideoManager_UpdateAndExtract: every running video's UpdateFrame (vt+0x68) with the
    // frame clock (the PS3 passes its third argument, XXL2 UpdateAndExtract(IAccumulator**, IKTime*); the
    // port's slot has no arguments yet, so the clock is the time manager's).
    void UpdateAndExtract(float maxDistanceSquared, RenderQueue** stages, IKTime* frameClock, RwCamera* camera, int32_t distanceCull) override;
    // vt+0x5c 0x000a98b0 CVideoManager_Render (Ghidra also CVideoManager_Draw): the running videos' Draw
    // (vt+0x84), then the loading video's Update, UpdateFrame and Draw. The PS3 passes the frame clock
    // (XXL2 Render(IKTime*)); the port's slot has none, so it is the time manager's clock.
    void Render(IKTime* frameClock) override;

    bool IsLoadingVideoActive();   // 0x000a8148 CVideoManager_IsLoadingVideoActive_maybe
    void PlayLoadingVideo();       // 0x000a7f48 CVideoManager_PlayLoadingVideo_maybe (plays m_pLoadingVideo)
    void StopLoadingVideo();       // 0x000a7fb8 CVideoManager_StopLoadingVideo_maybe
    void StopAllVideos();          // 0x000a94f8 CVideoManager_StopAllVideos_maybe
    void ShutdownVideoSystem();    // 0x000a8328 VideoSystem_Shutdown_maybe
    void InitCodec();              // 0x000a83d0 CVideoManager_InitCodec_maybe
    void RemoveActiveVideo(IKVideo* video);  // 0x000a81c0 CVideoManager_RemoveActiveVideo_maybe
    void AddActiveVideo(IKVideo* video);     // 0x000a90c0 CVideoManager_AddActiveVideo_maybe (at the tail)
    bool HasFullscreenVideo();               // 0x000a8698 CVideoManager_HasFullscreenVideo_maybe (flag 0x800)
    bool HasVideoWithoutFlag40();            // 0x000a89e8 CVideoManager_HasVideoWithoutFlag40_maybe
    void StopFirstActiveVideoWithoutFlag40();  // 0x000a8f18
    void PauseAllVideos();                   // 0x000a86e0 CVideoManager_PauseAllVideos_maybe
    void ResumeAllVideos();                  // 0x000a8e80 CVideoManager_ResumeAllVideos_maybe
    // 0x000a8820 GraphicObjectList_PauseAll_maybe / 0x000a87b0 GraphicObjectList_ResumeAll_maybe (CKGraphic Pause /
    // Resume): every running video's Pause (vt+0x7c) / Resume (vt+0x80), the next node read before the call.
    void PauseRunningVideos();
    void ResumeRunningVideos();

    IKVideo** m_apVideoArray;        // +0x18 PS3_CKVideo references (GAME; Mem_AllocAligned16)
    uint32_t m_ui32VideoNb;          // +0x1c
    VideoNode* m_lRunningVideo;      // +0x20 the running videos (Start adds, Stop removes); the constructor sets 0
    IKVideo* m_pLoadingVideo;        // +0x24 IKGameManager vt+0xd8's video, while loading
    uint32_t m_unk28;                // +0x28 the constructor sets 0; StopLoadingVideo clears it
    float m_fOpenFadeTime;           // +0x2c
    float m_fCloseFadeTime;          // +0x30
    CColorizedScreenFx* m_pFadeFx;   // +0x34 a CColorizedScreenFx reference (level data). Name ours.
    IKVideo* m_apPausedVideos[0x64]; // +0x38 PauseAllVideos: the videos it paused (count +0x1c8). Name ours.
    uint32_t m_ui32PausedNb;         // +0x1c8 the constructor sets 0
};
DOTD_ASSERT_SIZE(CVideoManager, 0x1cc);
DOTD_ASSERT_OFFSET(CVideoManager, m_apVideoArray, 0x18);
DOTD_ASSERT_OFFSET(CVideoManager, m_ui32VideoNb, 0x1c);
DOTD_ASSERT_OFFSET(CVideoManager, m_lRunningVideo, 0x20);
DOTD_ASSERT_OFFSET(CVideoManager, m_pLoadingVideo, 0x24);
DOTD_ASSERT_OFFSET(CVideoManager, m_fOpenFadeTime, 0x2c);
DOTD_ASSERT_OFFSET(CVideoManager, m_fCloseFadeTime, 0x30);
DOTD_ASSERT_OFFSET(CVideoManager, m_pFadeFx, 0x34);
DOTD_ASSERT_OFFSET(CVideoManager, m_apPausedVideos, 0x38);
DOTD_ASSERT_OFFSET(CVideoManager, m_ui32PausedNb, 0x1c8);

// 0x000a83a8 CVideoManager_InitRenderer_maybe: PS3Video_InitRenderer (BinkPS3 + the YUV shader).
void CVideoManager_InitRenderer(CVideoManager* manager);
// CKGameLoop's pause path (free-function forms of the methods above).
void CVideoManager_PauseAllVideos(CVideoManager* manager);
void CVideoManager_ResumeAllVideos(CVideoManager* manager);

// The game-sound helpers of the video manager's unit (CVideoManager.cpp). STUB(audio): the CKSoundManager
// calls they make are not ported; the suspend counter is.
void SoundSuspend_Acquire(CVideoManager* manager);           // 0x000a8350 SoundSuspend_Acquire_maybe
void SoundSuspend_Release(CVideoManager* manager);           // 0x000a8b58 SoundSuspend_Release_maybe
uint8_t SoundSuspend_AreStreamsState9(CVideoManager* manager);  // 0x000a8ba0 SoundSuspend_AreStreamsState9_maybe
void Video_MuteGameSound(CVideoManager* manager);            // 0x000a8b20 Video_MuteGameSound_maybe
void Video_RestoreGameSound(CVideoManager* manager);         // 0x000a8ae8 Video_RestoreGameSound_maybe
float Video_GetSpeechVolume(CVideoManager* manager);         // 0x000a8ab0 Video_GetSpeechVolume_maybe
float Video_GetMusicVolume(CVideoManager* manager);          // 0x000a8da8 Video_GetMusicVolume_maybe
// C1.6 audio: the options' video volumes (ApplySoundVolumesToVideoManager_maybe 0x150a0)
void CVideoManager_SetSpeechVolume(float volume, CVideoManager* manager);  // 0x000a8bd8 CVideoManager_SetSpeechVolume_maybe
void CVideoManager_SetMusicVolume(float volume, CVideoManager* manager);   // 0x000a8c78 CVideoManager_SetMusicVolume_maybe
class IKVideo;
void PS3_CKVideo_SetTrackVolume(float volume, IKVideo* video);         // 0x000aae20 PS3_CKVideo_SetTrackVolume_maybe
void PS3_CKVideo_SetSpeechTrackVolume(float volume, IKVideo* video);   // 0x000aae70 PS3_CKVideo_SetSpeechTrackVolume_maybe
