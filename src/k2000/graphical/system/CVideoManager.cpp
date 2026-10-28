// CVideoManager.cpp - reconstructed original translation unit 0xa81c0-0xa9b40 (GAME_TOC1, main_toc1), 50 functions, 44 live.
// Primary class: CVideoManager  key 0x9cd  category Graphical  size 0x1cc  vtable 0xb172f0
// Other owners: Video (4), SoundSuspend (3), VideoCodec (2), GraphicObjectList (2), AudioFormat (2), VideoSystem (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0xa81c0  CVideoManager_RemoveActiveVideo_maybe
//   [ ] 0xa8250  RegisterCVideoManagerClass
//   [ ] 0xa82c8  _GLOBAL__I_a82c8
//   [ ] 0xa82d8  VideoCodec_Alloc_maybe
//   [ ] 0xa8300  CVideoManager_Save
//   [x] 0xa8328  VideoSystem_Shutdown_maybe
//   [x] 0xa8350  SoundSuspend_Acquire_maybe
//   [x] 0xa83a8  CVideoManager_InitRenderer_maybe
//   [x] 0xa83d0  CVideoManager_InitCodec_maybe
//   [ ] 0xa8428  VideoCodec_Free_maybe
//   [x] 0xa8450  CVideoManager_Destroy
//   [x] 0xa8488  CVideoManager_Construct
//   [ ] 0xa8500  CVideoManager_Construct_2
//   [x] 0xa8578  CVideoManager_DeleteArray
//   [x] 0xa8618  CVideoManager_Update
//   [x] 0xa8698  CVideoManager_HasFullscreenVideo_maybe
//   [x] 0xa86e0  CVideoManager_PauseAllVideos_maybe
//   [ ] 0xa87b0  GraphicObjectList_ResumeAll_maybe
//   [ ] 0xa8820  GraphicObjectList_PauseAll_maybe
//   [ ] 0xa8890  CVideoManager_CloseAllBinkVideos_maybe  [dead]
//   [ ] 0xa88e8  FUN_000a88e8  [dead]
//   [ ] 0xa89a0  CVideoManager_HasVideoWithoutFlag1000_maybe  [dead]
//   [x] 0xa89e8  CVideoManager_HasVideoWithoutFlag40_maybe
//   [x] 0xa8a30  CVideoManager_Enqueue
//   [x] 0xa8ab0  Video_GetSpeechVolume_maybe
//   [x] 0xa8ae8  Video_RestoreGameSound_maybe
//   [x] 0xa8b20  Video_MuteGameSound_maybe
//   [x] 0xa8b58  SoundSuspend_Release_maybe
//   [x] 0xa8ba0  SoundSuspend_AreStreamsState9_maybe
//   [x] 0xa8bd8  CVideoManager_SetSpeechVolume_maybe
//   [x] 0xa8c78  CVideoManager_SetMusicVolume_maybe
//   [ ] 0xa8d18  CVideoManager_ForEachVideoNopHook_maybe
//   [x] 0xa8da8  Video_GetMusicVolume_maybe
//   [ ] 0xa8de0  CVideoManager_StartScreenFade_maybe  [dead]
//   [x] 0xa8e80  CVideoManager_ResumeAllVideos_maybe
//   [x] 0xa8f18  CVideoManager_StopFirstActiveVideoWithoutFlag40_maybe
//   [ ] 0xa8f80  CVideoManager_MessageProc
//   [ ] 0xa8f88  AudioFormat_Write_maybe  [dead]
//   [ ] 0xa9060  CVideoManager_PostLoad
//   [ ] 0xa9068  CVideoManager_DestroyGame
//   [x] 0xa90c0  CVideoManager_AddActiveVideo_maybe
//   [ ] 0xa91c8  AudioFormat_Read_maybe  [dead]
//   [x] 0xa92a0  CVideoManager_Load
//   [x] 0xa94f8  CVideoManager_StopAllVideos_maybe
//   [ ] 0xa9660  CVideoManager_DestructBody
//   [x] 0xa9708  CVideoManager_CreateArray
//   [x] 0xa9820  CVideoManager_Create
//   [x] 0xa98b0  CVideoManager_Draw
//   [ ] 0xa99e8  CVideoManager_DeletingDestructor
//   [ ] 0xa9a98  CVideoManager_Destructor
//
//   [x] 0x9a0628  CVideoManager_IsKindOfClass  [inline]
//   [x] 0x9a0650  CVideoManager_GetClassType  [inline]
//   [x] 0x9a0658  CVideoManager_GetClassID  [inline]
//   [x] 0x9a0660  CVideoManager_GetSerializationFlags  [inline]
#include "k2000/graphical/system/CVideoManager.h"

#include "k2000/core/Stub.h"
#include "k2000/graphical/fx/CColorizedScreenFx.h"
#include "k2000/graphical/system/IKVideo.h"
#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/CKGameLoop.h"
#include "k2000/managers/CKSoundManager.h"
#include "k2000/misc/Engine.h"
#include "k2000/sound/CKSoundStreamManager.h"
#include "k2000/system/CTimeManager.h"
#include "k2000/system/PS3Video.h"

namespace {
int32_t g_soundSuspendCount = 0;  // 0x00c5c9e8 (SoundSuspend_Acquire/Release)

// The frame clock the PS3 passes to UpdateAndExtract / Render (the port's slots have no arguments yet).
IKTime* FrameClock() {
    CTimeManager* timeManager = g_pEngine->m_timeManager;
    return timeManager != nullptr ? timeManager->m_pTime : nullptr;
}
}  // namespace

// 0x000a9820 CVideoManager_Create (= CVideoManager_Construct 0xa8488), in the original's store order.
CVideoManager::CVideoManager() {
    m_pNextAccumulatedObject = nullptr;
    m_BitProperties = 0;
    m_pPriorityParent = 0;
    m_pLightSet = nullptr;
    m_lRunningVideo = nullptr;
    m_ui32PausedNb = 0;
    Engine_SetVideoManager(this);
    m_pFadeFx = nullptr;
    m_pLoadingVideo = nullptr;
    m_unk28 = 0;
}

// 0x000a8450 CVideoManager_Destroy: the fade (a level object) forgotten.
void CVideoManager::Destroy() {
    IRendableObject::Destroy();  // 0xa7248
    m_pFadeFx = nullptr;
}

// 0x000a92a0 CVideoManager_Load
int32_t CVideoManager::Load(IKFile* file, int32_t type) {
    IRendableObject::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        IKFile_ReadRef(file, &m_pFadeFx);
        return 1;
    }
    if (type != K_GAME_PLATEFORMS) return 1;
    ReadU32LE(file, &m_ui32VideoNb);
    if (m_ui32VideoNb == 0) {
        m_apVideoArray = nullptr;
    } else {
        m_apVideoArray =
            static_cast<IKVideo**>(Mem_AllocAligned16(m_ui32VideoNb * static_cast<uint32_t>(sizeof(IKVideo*))));
        IKFile_ReadObjectRefArray(file, reinterpret_cast<IKSerializable**>(m_apVideoArray), m_ui32VideoNb);
    }
    ReadF32LE(file, &m_fOpenFadeTime);
    ReadF32LE(file, &m_fCloseFadeTime);
    return 1;
}

// 0x000a83d0 CVideoManager_InitCodec_maybe: BinkSetSoundSystem with the manager's allocators (audio: later
// phase), then the defaults.
void CVideoManager::InitCodec() {
    m_fCloseFadeTime = 0.5f;
    m_pLoadingVideo = nullptr;
    m_apVideoArray = nullptr;
    m_ui32VideoNb = 0;
    m_fOpenFadeTime = 0.5f;
}

// 0x000a81c0 CVideoManager_RemoveActiveVideo_maybe: unlinks the video's node (back to the pool).
void CVideoManager::RemoveActiveVideo(IKVideo* video) {
    VideoNode* head = m_lRunningVideo;
    if (head == nullptr) return;
    VideoNode* node = head;
    if (head->m_pVideo != video) {
        VideoNode* previous;
        do {
            previous = node;
            node = node->m_pNext;
            if (node == nullptr) return;
        } while (node->m_pVideo != video);
        if (head != node) {
            previous->m_pNext = node->m_pNext;
            delete node;
            return;
        }
    }
    m_lRunningVideo = head->m_pNext;
    delete head;
}

// 0x000a90c0 CVideoManager_AddActiveVideo_maybe: a new node at the tail (no duplicate check).
void CVideoManager::AddActiveVideo(IKVideo* video) {
    VideoNode* node = new VideoNode();
    node->m_pVideo = video;
    node->m_pNext = nullptr;
    if (m_lRunningVideo == nullptr) {
        m_lRunningVideo = node;
        return;
    }
    VideoNode* last = m_lRunningVideo;
    while (last->m_pNext != nullptr) last = last->m_pNext;
    last->m_pNext = node;
}

// 0x000a8618 CVideoManager_PreUpdate (Ghidra CVideoManager_Update in the checklist). The next node is read
// before the call: a video may stop (and leave the list) inside it.
void CVideoManager::PreUpdate(IKTime* frameClock) {
    VideoNode* node = m_lRunningVideo;
    while (node != nullptr) {
        IKVideo* video = node->m_pVideo;
        node = node->m_pNext;
        video->Update(frameClock);  // vt+0x64
    }
}

// 0x000a8a30 CVideoManager_UpdateAndExtract (Ghidra CVideoManager_Enqueue in the checklist)
void CVideoManager::UpdateAndExtract(float /*maxDistanceSquared*/, RenderQueue** /*stages*/, IKTime* /*frameClock*/, RwCamera* /*camera*/, int32_t /*distanceCull*/) {
    IKTime* frameClock = FrameClock();
    VideoNode* node = m_lRunningVideo;
    while (node != nullptr) {
        IKVideo* video = node->m_pVideo;
        node = node->m_pNext;
        video->UpdateFrame(frameClock);  // vt+0x68
    }
}

// 0x000a98b0 CVideoManager_Render (Ghidra CVideoManager_Draw in the checklist)
void CVideoManager::Render() {
    IKTime* frameClock = FrameClock();
    VideoNode* node = m_lRunningVideo;
    while (node != nullptr) {
        IKVideo* video = node->m_pVideo;
        node = node->m_pNext;
        video->Draw(frameClock);  // vt+0x84
    }
    IKVideo* loading = m_pLoadingVideo;
    if (loading == nullptr || loading->m_state == 0) return;
    loading->Update(frameClock);       // vt+0x64
    m_pLoadingVideo->UpdateFrame(frameClock);  // vt+0x68
    if (m_pLoadingVideo->m_pBink != nullptr) m_pLoadingVideo->Draw(frameClock);  // vt+0x84
}

// 0x000a8698 CVideoManager_HasFullscreenVideo_maybe
bool CVideoManager::HasFullscreenVideo() {
    for (VideoNode* node = m_lRunningVideo; node != nullptr; node = node->m_pNext) {
        if ((node->m_pVideo->m_baData & 0x800u) != 0) return true;
    }
    return false;
}

// 0x000a89e8 CVideoManager_HasVideoWithoutFlag40_maybe
bool CVideoManager::HasVideoWithoutFlag40() {
    for (VideoNode* node = m_lRunningVideo; node != nullptr; node = node->m_pNext) {
        if ((node->m_pVideo->m_baData & 0x40u) == 0) return true;
    }
    return false;
}

// 0x000a8f18 CVideoManager_StopFirstActiveVideoWithoutFlag40_maybe
void CVideoManager::StopFirstActiveVideoWithoutFlag40() {
    for (VideoNode* node = m_lRunningVideo; node != nullptr; node = node->m_pNext) {
        IKVideo* video = node->m_pVideo;
        if ((video->m_baData & 0x40u) == 0) {
            video->Stop();  // vt+0x78
            return;
        }
    }
}

// 0x000a86e0 CVideoManager_PauseAllVideos_maybe: pauses the playing, unpaused videos and remembers them.
void CVideoManager::PauseAllVideos() {
    m_ui32PausedNb = 0;
    VideoNode* node = m_lRunningVideo;
    while (node != nullptr) {
        IKVideo* video = node->m_pVideo;
        node = node->m_pNext;
        if ((video->m_baData & 1u) == 0 || (video->m_baData & 2u) != 0) continue;
        video->Pause();  // vt+0x7c
        // BUG(original): no bound check against the 0x64 slots.
        m_apPausedVideos[m_ui32PausedNb++] = video;
    }
}

// 0x000a8e80 CVideoManager_ResumeAllVideos_maybe
void CVideoManager::ResumeAllVideos() {
    for (uint32_t i = 0; i < m_ui32PausedNb; ++i) m_apPausedVideos[i]->Resume();  // vt+0x80
    m_ui32PausedNb = 0;
}

// 0x000a94f8 CVideoManager_StopAllVideos_maybe: stops the running videos and the loading video; unless the
// game is quitting, the fade effect's flag 0x100 is cleared.
void CVideoManager::StopAllVideos() {
    VideoNode* node = m_lRunningVideo;
    while (node != nullptr) {
        IKVideo* video = node->m_pVideo;
        node = node->m_pNext;
        video->Stop();  // vt+0x78
    }
    IKVideo* loading = m_pLoadingVideo;
    if (loading == nullptr) {
        if (m_unk28 != 0) m_unk28 = 0;
    } else {
        loading->Stop();  // vt+0x78
        m_pLoadingVideo->m_baData &= ~0x4000u;
        m_unk28 = 0;
        m_pLoadingVideo = nullptr;
    }
    CKGameLoop* loop = g_pEngine->m_gameLoop;
    const bool quitting = loop->HasEnteredQuit() != 0 && loop->IsExitRequested() != 0;
    if (!quitting && m_pFadeFx != nullptr) m_pFadeFx->m_BitProperties &= ~0x100u;
}

// 0x000a8328 VideoSystem_Shutdown_maybe
void CVideoManager::ShutdownVideoSystem() { PS3Video_Shutdown(); }

// 0x000a83a8 CVideoManager_InitRenderer_maybe
void CVideoManager_InitRenderer(CVideoManager*) {
    dotd::trace::Boot("CVideoManager_InitRenderer (Bink renderer)");
    PS3Video_InitRenderer();
}

void CVideoManager_PauseAllVideos(CVideoManager* manager) { manager->PauseAllVideos(); }
void CVideoManager_ResumeAllVideos(CVideoManager* manager) { manager->ResumeAllVideos(); }

// ==== game sound around videos ===================================================================

// 0x000a8350 SoundSuspend_Acquire_maybe: the first acquire suspends the game's sound groups (the
// music-flagged sounds stop).
void SoundSuspend_Acquire(CVideoManager*) {
    if (g_soundSuspendCount == 0) g_pEngine->m_soundManager->SuspendSoundGroups();
    ++g_soundSuspendCount;
}
// 0x000a8b58 SoundSuspend_Release_maybe: the last release resumes them.
void SoundSuspend_Release(CVideoManager*) {
    --g_soundSuspendCount;
    if (g_soundSuspendCount == 0) g_pEngine->m_soundManager->UnsuspendSoundGroups();
}
// 0x000a8ba0 SoundSuspend_AreStreamsState9_maybe: the sound streams have stopped (RWA state 9).
uint8_t SoundSuspend_AreStreamsState9(CVideoManager*) { return g_pEngine->m_soundManager->AreStreamsState9(); }
// 0x000a8b20 Video_MuteGameSound_maybe
void Video_MuteGameSound(CVideoManager*) { g_pEngine->m_soundManager->SaveAndMuteVolume(0); }
// 0x000a8ae8 Video_RestoreGameSound_maybe
void Video_RestoreGameSound(CVideoManager*) { g_pEngine->m_soundManager->RestoreSavedVolume(0); }
// 0x000a8ab0 Video_GetSpeechVolume_maybe: the speech stream type's volume.
float Video_GetSpeechVolume(CVideoManager*) { return g_pEngine->m_soundManager->m_pSoundStreamManager->GetSpeechVolume(); }
// 0x000a8da8 Video_GetMusicVolume_maybe: the music stream type's volume.
float Video_GetMusicVolume(CVideoManager*) { return g_pEngine->m_soundManager->m_pSoundStreamManager->GetMusicVolume(); }

// 0x000a8bd8 CVideoManager_SetSpeechVolume_maybe: the voice track of every playing video.
void CVideoManager_SetSpeechVolume(float volume, CVideoManager* manager) {
    for (uint32_t i = 0; i < manager->m_ui32VideoNb; ++i) {
        IKVideo* video = manager->m_apVideoArray[i];
        if (video->m_state != 0) PS3_CKVideo_SetSpeechTrackVolume(volume, video);
    }
}

// 0x000a8c78 CVideoManager_SetMusicVolume_maybe: the music track of every open video (flag 4).
void CVideoManager_SetMusicVolume(float volume, CVideoManager* manager) {
    for (uint32_t i = 0; i < manager->m_ui32VideoNb; ++i) {
        IKVideo* video = manager->m_apVideoArray[i];
        if ((video->m_baData & 4u) != 0) PS3_CKVideo_SetTrackVolume(volume, video);
    }
}
