// CKVideoSegment.cpp - reconstructed original translation unit 0xa73c8-0xa81c0 (GAME_TOC1, main_toc1), 40 functions, 25 live.
// Primary class: CKVideoSegment  key 0xd8d  category Graphical  size 0x28  vtable 0xb17298
// Other owners: CVideoManager (10), AudioFormat (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0xa73c8  CKVideoSegment_Delete  (the registry factory: DOTD_DECLARE_FACTORIES(CKVideoSegment))
//   [ ] 0xa7418  CKVideoSegment_Construct  [dead]
//   [ ] 0xa7440  CKVideoSegment_Construct_2  [dead]
//   [x] 0xa7468  CKVideoSegment_RecursiveRegistration  (RecursiveRegistration: returns 1, the default slot)
//   [ ] 0xa7470  CKVideoSegment_ResetState_maybe  [dead]
//   [x] 0xa7488  CKVideoSegment_MarkEndedIfPlaying_maybe
//   [ ] 0xa74a8  CKVideoSegment_EndPlayback_maybe  [dead]
//   [x] 0xa7520  CKVideoSegment_GetStartFrame_maybe
//   [ ] 0xa7528  FUN_000a7528  [dead]
//   [x] 0xa7530  CKVideoSegment_GetLoopFrame_maybe
//   [ ] 0xa7538  CKVideoSegment_GetEndFrame_maybe  [dead]
//   [ ] 0xa7540  RegisterCKVideoSegmentClass
//   [ ] 0xa75b8  _GLOBAL__I_a75b8
//   [x] 0xa75c8  CKVideoSegment_Play_maybe
//   [x] 0xa76e8  CKVideoSegment_DeleteArray  (the registry factory: DOTD_DECLARE_FACTORIES(CKVideoSegment))
//   [x] 0xa7790  CKVideoSegment_IsAtEnd_maybe
//   [x] 0xa7848  CKVideoSegment_MessageProc  (MessageProc: returns 1, the default slot)
//   [ ] 0xa7850  CKVideoSegment_Save
//   [x] 0xa7858  CKVideoSegment_GetInfo  (GetInfo: returns 1, the default slot)
//   [x] 0xa7860  CKVideoSegment_CreateArray  (the registry factory: DOTD_DECLARE_FACTORIES(CKVideoSegment), the constructor per element)
//   [x] 0xa7918  CKVideoSegment_Create
//   [x] 0xa7968  CKVideoSegment_PostLoad  (PostLoad: returns 1, the default slot)
//   [x] 0xa7970  CKVideoSegment_Destroy  (Destroy: empty, the default slot)
//   [x] 0xa7978  CKVideoSegment_UpdatePlayback_maybe
//   [x] 0xa7ad8  CKVideoSegment_Load
//   [ ] 0xa7d18  CKVideoSegment_Restart_maybe  [dead]
//   [x] 0xa7e70  CVideoManager_Delete  (the registry factory: DOTD_DECLARE_FACTORIES(CVideoManager))
//   [x] 0xa7ec0  CVideoManager_RecursiveRegistration  (RecursiveRegistration: returns 1, the default slot)
//   [x] 0xa7ec8  KStub_Nop_a7ec8  (empty: CKGraphic_Start calls it, nothing to port)
//   [ ] 0xa7ed0  CVideoManager_GetVideoCount_maybe  [dead]
//   [ ] 0xa7ed8  CVideoManager_GetVideoAt_maybe  [dead]
//   [ ] 0xa7ef0  CVideoManager_PlayVideoAt_maybe  [dead]
//   [x] 0xa7f48  CVideoManager_PlayLoadingVideo_maybe
//   [x] 0xa7fb8  CVideoManager_StopLoadingVideo_maybe
//   [ ] 0xa8068  KStub_Nop_a8068  [dead]
//   [ ] 0xa8070  KStub_Nop_a8070  [dead]
//   [ ] 0xa8078  CVideoManager_UpdateLoadingVideo_maybe  [dead]
//   [x] 0xa8148  CVideoManager_IsLoadingVideoActive_maybe
//   [ ] 0xa8178  CVideoManager_ClearScreenFadeFlag_maybe  [dead]
//   [ ] 0xa81a0  AudioFormat_InitDefault_maybe  [dead]
//
//   [ ] 0x9a0598  CKVideoSegment_GetSerializationFlags  [inline]
//   [x] 0x9a05a0  CKVideoSegment_GetClassType  [inline]
//   [x] 0x9a05a8  CKVideoSegment_GetClassID  [inline]
//   [x] 0x9a05b0  CKVideoSegment_DeletingDestructor  [inline]
//   [x] 0x9a05f0  CKVideoSegment_IsKindOfClass  [inline]
//   [x] 0x9a0610  CKVideoSegment_Destructor  [inline]
#include "k2000/graphical/system/CKVideoSegment.h"

#include "k2000/graphical/system/CVideoManager.h"
#include "k2000/graphical/system/IKVideo.h"
#include "k2000/io/IKFile.h"

// 0x000a7918 CKVideoSegment_Create, in the original's store order.
CKVideoSegment::CKVideoSegment() {
    m_useLoopStart = 0;
    m_startFrame = 0;
    m_introEndFrame = 0;
    m_loopStartFrame = 0;
    m_endFrame = 0;
}

// 0x000a7ad8 CKVideoSegment_Load
int32_t CKVideoSegment::Load(IKFile* file, int32_t type) {
    if (type == K_LEVEL_PLATEFORMS) {
        ReadU32LE(file, &m_startFrame);
        ReadU32LE(file, &m_introEndFrame);
        ReadU32LE(file, &m_loopStartFrame);
        ReadU32LE(file, &m_endFrame);
        IKFile_ReadRef(file, &m_pVideo);
        ReadU32LE(file, &m_defaultMode);
    }
    m_useLoopStart = 0;
    m_ended = 1;
    m_mode = 0;
    return 1;
}

// 0x000a7488 CKVideoSegment_MarkEndedIfPlaying_maybe
void CKVideoSegment::MarkEndedIfPlaying() {
    if (m_ended != 0) return;
    m_useLoopStart = 0;
    m_ended = 1;
}

// 0x000a75c8 CKVideoSegment_Play_maybe
void CKVideoSegment::Play(uint32_t mode, uint8_t useLoopStart, int32_t force) {
    if (m_ended == 0 && force == 0) return;
    if (mode == kModeDefault) {
        m_mode = m_defaultMode;
    } else {
        m_mode = mode;
    }
    IKVideo* video = m_pVideo;
    m_useLoopStart = useLoopStart;
    m_ended = 0;
    if (video->m_state == 0) {
        if (video->Start(this) != 1) m_ended = 1;  // vt+0x60
        return;
    }
    if ((video->m_baData & 2u) != 0) {
        video->Resume();  // vt+0x80
        video = m_pVideo;
    }
    video->SetSegment(this);
}

// 0x000a7790 CKVideoSegment_IsAtEnd_maybe
uint8_t CKVideoSegment::IsAtEnd() {
    const uint32_t position = static_cast<uint32_t>(m_pVideo->GetPlaybackPosition());
    if (m_introEndFrame == position && m_loopStartFrame != position) return 1;
    if (m_endFrame != position) return 0;
    return m_mode == kModeLoop ? 1 : 0;
}

// 0x000a7978 CKVideoSegment_UpdatePlayback_maybe. The comparisons are unsigned.
uint8_t CKVideoSegment::UpdatePlayback() {
    const uint32_t position = static_cast<uint32_t>(m_pVideo->GetPlaybackPosition());
    const uint32_t introEnd = m_introEndFrame;
    if (position == introEnd && position != m_loopStartFrame) {
        m_pVideo->SeekToKeyFrameNear(static_cast<int32_t>(m_loopStartFrame));
        return 0;
    }
    uint32_t last = m_endFrame;
    if (position == last) {
        if (m_mode == kModeReportEnd) return 1;
        if (m_mode == kModeLoop) {
            m_pVideo->SeekToKeyFrameNear(static_cast<int32_t>(m_loopStartFrame));
            return 0;
        }
        if (m_mode == kModePause) {
            if (m_ended != 0) return 0;
            m_ended = 1;
            m_pVideo->Pause();  // vt+0x7c
            return 0;
        }
    }
    if (last <= introEnd) last = introEnd;
    if (position <= last) return 0;
    // Past the segment (a seek landed after it): back to its last frame, exactly.
    m_pVideo->SeekToFrame(static_cast<int32_t>(last));
    m_ended = 0;
    return 0;
}

// ==== CVideoManager (this unit holds its loading-video functions) =================================

// 0x000a7f48 CVideoManager_PlayLoadingVideo_maybe
void CVideoManager::PlayLoadingVideo() {
    IKVideo* video = m_pLoadingVideo;
    if (video == nullptr) return;
    video->m_baData = (video->m_baData & ~0x4000u) | 0x4000u;
    video->Start(nullptr);  // vt+0x60
}

// 0x000a7fb8 CVideoManager_StopLoadingVideo_maybe
void CVideoManager::StopLoadingVideo() {
    IKVideo* video = m_pLoadingVideo;
    if (video == nullptr) {
        if (m_unk28 != 0) m_unk28 = 0;
        return;
    }
    video->Stop();  // vt+0x78
    m_pLoadingVideo->m_baData &= ~0x4000u;
    m_unk28 = 0;
    m_pLoadingVideo = nullptr;
}

// 0x000a8148 CVideoManager_IsLoadingVideoActive_maybe
bool CVideoManager::IsLoadingVideoActive() {
    if (m_pLoadingVideo == nullptr) return false;
    return m_pLoadingVideo->m_state != 0;
}
