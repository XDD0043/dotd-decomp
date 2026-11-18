// PS3_CKVideo.cpp - reconstructed original translation unit 0xa9bd0-0xaee90 (GAME_TOC1, main_toc1), 101 functions, 79 live.
// Primary class: PS3_CKVideo  key 0xa4d  category Graphical  size 0x23c  vtable 0xb17420
// Other owners: IKVideo (13), PS3Video (4), Bink (2), Math (1), RegisterPS3 (1), DrawPS3VideoFrameQuad (1), Video (1)
//
// The Bink library calls go to platform/video/bink.h, the PSGL drawing to k2000/system/PS3Video.h. Audio
// (track selection, volumes, the XMB background music) goes to Bink's audio calls (platform/video/bink.h);
// the mixing is platform/audio.
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0xa9bd0  PS3_CKVideo_ResetState_maybe  [dead]
//   [x] 0xa9c50  PS3_CKVideo_CloseStreamIfOpen_maybe
//   [x] 0xa9cc8  PS3_CKVideo_vf5C
//   [x] 0xa9d38  PS3_CKVideo_ComputeDisplayRect_maybe
//   [x] 0xa9f50  PS3_CKVideo_SetRenderStates_maybe
//   [ ] 0xaa240  FUN_000aa240  [dead]
//   [ ] 0xaa2a8  PS3_CKVideo_CheckLastFrameReached_maybe  [dead]
//   [x] 0xaa370  PS3_CKVideo_SetFadeLevel_maybe
//   [ ] 0xaa390  KStub_Nop_aa390  [dead]
//   [x] 0xaa398  PS3_CKVideo_SetCurrentAndTargetFrame_maybe
//   [ ] 0xaa3d0  PS3_CKVideo_GetDurationSeconds_maybe  [dead]
//   [ ] 0xaa420  PS3_CKVideo_DrawSingleTile_maybe  [dead]
//   [ ] 0xaa4c0  PS3_CKVideo_DrawTiledFrame_maybe  [dead: its only caller PS3_CKVideo_DrawFrame_maybe 0xac5e8 is dead (C2.8 port-rest R02)]
//   [ ] 0xaa830  Math_NextPowerOfTwoMax1024_maybe  [dead]
//   [x] 0xaa8d8  IKVideo_vf94  (IKVideo::RegisterFrameBuffers, empty (IKVideo.h))
//   [ ] 0xaa8e0  PS3_CKVideo_GetHeight_maybe  [dead]
//   [ ] 0xaa900  PS3_CKVideo_GetWidth_maybe  [dead]
//   [x] 0xaa920  PS3_CKVideo_GetFrameCount_maybe
//   [ ] 0xaa940  KStub_Nop_aa940  [dead]
//   [x] 0xaa948  KStub_ReturnFloat0p02_aa948  (returns 0.02f: CKFlashUI::Update and CKS08GameManager_2.cpp use the constant inline)
//   [ ] 0xaa950  PS3_CKVideo_GetFrameRate_maybe  [dead]
//   [ ] 0xaa998  PS3_CKVideo_GetFrameRateNumerator_maybe  [dead]
//   [ ] 0xaa9b8  PS3_CKVideo_GetFrameRateDivisor_maybe  [dead]
//   [ ] 0xaa9d8  FUN_000aa9d8  [dead]
//   [x] 0xaaa28  IKVideo_vf70  (IKVideo::SelectNextFrame, empty (IKVideo.h))
//   [ ] 0xaaa30  Bink_CopyFrameTileToRaster_maybe  [platform] (the IKVideo RW-raster path: a Bink frame tile into an RwRaster; called by IKVideo_vf6C (never run: IKVideo is abstract and PS3_CKVideo overrides it) and the dead 0xaac10; dotd's video goes through platform/video (C2.8 port-rest R02))
//   [ ] 0xaac10  Bink_CopyFrameToRasterTiles_maybe  [dead: no pointer to its descriptor 0xb49df0, no call (C2.8 port-rest R02)]
//   [ ] 0xaad38  PS3_CKVideo_GetClosestKeyFrame_maybe  [dead]
//   [x] 0xaad78  PS3Video_SelectSoundTracks_maybe
//   [ ] 0xaade8  PS3_CKVideo_SetSoundOnOff_maybe  [dead]
//   [x] 0xaae20  PS3_CKVideo_SetTrackVolume_maybe
//   [x] 0xaae70  PS3_CKVideo_SetSpeechTrackVolume_maybe
//   [ ] 0xaaef0  PS3_CKVideo_SetTrackEnabled_maybe  [dead]
//   [x] 0xaaf60  PS3_CKVideo_vf80
//   [x] 0xaafe0  PS3_CKVideo_Pause_maybe
//   [ ] 0xab070  IKVideo_vfA0  [platform] (IKVideo's own CloseStream of the RW-raster path; never run: IKVideo is abstract (vt+0x88 pure) and PS3_CKVideo, its only class, overrides the slot; dotd's video goes through platform/video (C2.8 port-rest R02))
//   [ ] 0xab0e8  IKVideo_DestroyFrameTextures_maybe  [platform] (IKVideo's own DestroyFrameTextures of the RW-raster path; never run, PS3_CKVideo overrides it (C2.8 port-rest R02))
//   [x] 0xab1c8  PS3_CKVideo_AdvanceFrame_maybe
//   [x] 0xab260  PS3_CKVideo_SetCurrentAndTargetFrame_VariantB_maybe
//   [x] 0xab2a8  PS3_CKVideo_ConstructBase_maybe
//   [x] 0xab2c8  IKVideo_vf24  (IKVideo::RecursiveRegistration)
//   [ ] 0xab3c0  PS3_CKVideo_ConstructBase_2_maybe  [dead]
//   [x] 0xab3e0  PS3_CKVideo_StopIfEnded_maybe
//   [x] 0xab448  KStub_Nop_ab448  (empty: CVideoManager_ForEachVideoNopHook_maybe calls it, nothing to port)
//   [ ] 0xab450  IKVideo_vf98  [platform] (IKVideo's own vt+0x98 of the RW-raster path; never run, PS3_CKVideo overrides it (C2.8 port-rest R02))
//   [x] 0xab890  PS3_CKVideo_StopImpl_maybe
//   [x] 0xabb50  PS3_CKVideo_GetInfo  (IKVideo::GetInfo)
//   [x] 0xabbb8  IKVideo_vf28  (Save: returns 1, the default slot (PS3_CKVideo_Save calls it))
//   [x] 0xabbc0  PS3_CKVideo_MessageProc
//   [x] 0xabc88  IKVideo_vfC  (IKVideo::DestroyGame, IKVideo.h)
//   [x] 0xabc98  PS3_CKVideo_ReleaseTexture_maybe  (IKVideo::ReleaseTexture)
//   [x] 0xabd20  IKVideo_DrawPlaceholderQuad_maybe
//   [ ] 0xabd80  PS3_CKVideo_UpdateFrameDeltaSeconds_maybe  [dead]
//   [x] 0xabe58  PS3_CKVideo_GetElapsedSeconds_maybe
//   [ ] 0xabeb8  IKVideo_vf8C  [platform] (IKVideo's own CreateFrameTextures of the RW-raster path; never run, PS3_CKVideo overrides it (C2.8 port-rest R02))
//   [x] 0xac410  IKVideo_vf30
//   [x] 0xac4a0  PS3_CKVideo_GetPlaybackPosition_maybe
//   [ ] 0xac550  PS3_CKVideo_SeekToFrame_maybe  [dead]
//   [ ] 0xac5e8  PS3_CKVideo_DrawFrame_maybe  [dead: no pointer to its descriptor 0xb49f18, no call (C2.8 port-rest R02)]
//   [x] 0xac740  PS3_CKVideo_BeginPlayback_maybe
//   [x] 0xac908  PS3_CKVideo_UpdateFrame_maybe
//   [x] 0xacd90  PS3_CKVideo_OpenBink_maybe
//   [x] 0xacf00  PS3_CKVideo_SetSegment_maybe
//   [ ] 0xacfa8  PS3_CKVideo_RequestSeekToSeconds_maybe  [dead]
//   [x] 0xad040  PS3_CKVideo_RestartSegmentOrLoop_maybe
//   [x] 0xad2c0  PS3_CKVideo_vf60
//   [ ] 0xad4d0  IKVideo_vf6C  [platform] (IKVideo's own CopyFrameToTexture of the RW-raster path; never run, PS3_CKVideo overrides it (C2.8 port-rest R02))
//   [x] 0xad5f8  IKVideo_Load
//   [x] 0xad890  PS3_CKVideo_UpdatePlaybackState_maybe
//   [x] 0xae020  PS3_CKVideo_Delete
//   [ ] 0xae070  FUN_000ae070  [dead]
//   [x] 0xae110  PS3_CKVideo_vf6C
//   [x] 0xae118  PS3_CKVideo_vf88
//   [x] 0xae120  PS3_CKVideo_vf98
//   [x] 0xae128  RegisterPS3_CKVideoClass  (RegisterAllClasses: ClassTable.inc)
//   [ ] 0xae1a0  _GLOBAL__I_ae1a0
//   [x] 0xae1b0  DrawPS3VideoFrameQuad
//   [x] 0xae2d0  PS3_CKVideo_SelectNextFrame
//   [x] 0xae300  PS3_CKVideo_vf94
//   [x] 0xae340  PS3_CKVideo_DestroyFrameTextures
//   [x] 0xae378  PS3_CKVideo_CreateFrameTextures_maybe
//   [x] 0xae408  PS3_CKVideo_UpdateFrameThunk_maybe
//   [x] 0xae430  PS3_CKVideo_vfA4
//   [x] 0xae458  PS3_CKVideo_PostLoad
//   [x] 0xae480  PS3_CKVideo_Load
//   [ ] 0xae4a8  PS3_CKVideo_Save
//   [x] 0xae4d0  PS3_CKVideo_RecursiveRegistration  (IKVideo::RecursiveRegistration (inherited; it only calls IKVideo_vf24))
//   [x] 0xae4f8  PS3_CKVideo_DestroyGame  (IKVideo::DestroyGame (inherited; it only calls IKVideo_vfC))
//   [x] 0xae520  PS3_CKVideo_Destroy  (IKVideo::Destroy, IKVideo.h)
//   [x] 0xae548  PS3Video_Shutdown_maybe
//   [ ] 0xae578  PS3Video_ConfigureAudioOutput_maybe  [dead: no pointer to its descriptor 0xb4a178, no call; cellAudioOut configuration, platform code (C2.8 port-rest R02)]
//   [x] 0xae748  PS3_CKVideo_DeleteArray
//   [x] 0xae7e8  PS3_CKVideo_Create
//   [x] 0xae840  PS3_CKVideo_OpenStream_maybe
//   [x] 0xae9c8  PS3_CKVideo_CloseStream_maybe
//   [x] 0xaea40  PS3Video_InitRenderer_maybe
//   [x] 0xaeab0  PS3_CKVideo_CreateArray
//   [ ] 0xaeb60  Video_SetSystemBgmPlayback_maybe  [dead: no pointer to its descriptor 0xb4a1d0, no call; cellSysutil BGM playback, platform code (C2.8 port-rest R02)]
//   [x] 0xaec20  PS3_CKVideo_Update_maybe
//   [x] 0xaed08  PS3_CKVideo_Stop_maybe
//   [x] 0xaede0  PS3_CKVideo_Play_maybe
//
//   [x] 0x9a0668  PS3_CKVideo_GetGuid  [inline]
//   [x] 0x9a0678  PS3_CKVideo_GetSerializationFlags  [inline]
//   [x] 0x9a0680  PS3_CKVideo_vf50  [inline]
//   [x] 0x9a0688  IKVideo_vf14  [inline]
//   [x] 0x9a0690  IKVideo_vf18  [inline]
//   [x] 0x9a0698  PS3_CKVideo_SetGuid  [inline]
//   [x] 0x9a06c8  IKVideo_vf8  [inline]
//   [x] 0x9a06e8  IKVideo_DeletingDestructor  [inline]
//   [x] 0x9a0728  IKVideo_vf0  [inline]
//   [x] 0x9a0740  PS3_CKVideo_IsKindOfClass  [inline]
//   [x] 0x9a0768  PS3_CKVideo_GetClassType  [inline]
//   [x] 0x9a0770  PS3_CKVideo_GetClassID  [inline]
//   [x] 0x9a0778  PS3_CKVideo_DeletingDestructor  [inline]
//   [x] 0x9a07c0  PS3_CKVideo_Destructor  [inline]
#include "k2000/graphical/system/PS3_CKVideo.h"

#include <cstdio>

#include "Renderware/rwcore/RwIm3D.h"
#include "Renderware/rwcore/RwTexture.h"
#include "crt/ppc_ops.h"
#include "k2000/graphical/system/CKVideoSegment.h"
#include "k2000/graphical/system/CVideoManager.h"
#include "k2000/graphical/ui/CameraContextUi.h"
#include "k2000/io/IKFile.h"
#include "k2000/io/KFileSystem.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/logic/ui/CLocManager.h"
#include "k2000/managers/CKGraphic.h"
#include "k2000/misc/CKGameLoop.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/JobQueue.h"
#include "k2000/misc/MessageBox.h"
#include "k2000/render/CRenderer.h"
#include "k2000/services/CKSrvCinematic.h"
#include "k2000/services/CTriggerStarter.h"
#include "k2000/system/CellSysutilCallback.h"
#include "k2000/system/IKTime.h"
#include "k2000/system/PS3Video.h"
#include "platform/cell/sysutil.h"

namespace {

// 0x00c5c9ec: added to BinkGetKeyFrame's result before a seek (only read; the .bss value is 0).
int32_t g_videoKeyFrameOffset = 0;
// TOC float 0x47000000: the 0..1 volume scale for BinkSetVolume.
constexpr float kBinkVolumeScale = 32768.0f;

// The camera context's +0x84 (the screen's pixel aspect, 1.0 at 1280x720; ConstructRendererCameraContext).
float CameraContext_GetVideoPixelAspect() { return CameraContext_GetPixelAspect84(); }

CVideoManager* VideoManager() { return g_pEngine->m_videoManager; }
CKGameLoop* GameLoop() { return g_pEngine->m_gameLoop; }

// 0x0001e150 CKGameLoop_HasRequestedLevel_maybe / 0x0001e188 _IncPauseCount_maybe / 0x0001e198 _DecPauseCount_maybe
bool GameLoop_HasRequestedLevel(CKGameLoop* loop) { return loop->HasRequestedLevel(); }
void GameLoop_IncPauseCount(CKGameLoop* loop) { loop->IncPauseCount(); }
void GameLoop_DecPauseCount(CKGameLoop* loop) { loop->DecPauseCount(); }

// IKGameManager vt+0xf4 (CKS08GameManager_vfF4 0x4ec878): whether the XMB background music may keep
// playing during this video (0 in GameManager state 3, the logos; in state 5 only for videos other than
// the demo video, vt+0xe0).
uint8_t GameManager_AllowsBgmDuringVideo(IKVideo* video) { return g_pEngine->m_gameManager->AllowsBgmDuringVideo(video); }
// IKGameManager vt+0x1c MessageProc(0x2501 = video started / 0x2502 = video stopped, video). The game
// manager's handler is 0x4fa438 CKS08GameManager_MessageProc (its HandleUIMessage part).
void GameManager_VideoMessage(uint32_t message, IKVideo* video) {
    g_pEngine->m_gameManager->MessageProc(static_cast<uint16_t>(message), video);
}

// CKSrvCinematic_UpdateVideoSkipPrompt_maybe 0x167d18 / CKSrvCinematic_PlayNextVideo_maybe 0x1666a8: the cutscene path
// (flag 0x100000).
int32_t CKSrvCinematic_UpdateVideoSkipPrompt(IKSerializable* service, IKVideo*) {
    return static_cast<CKSrvCinematic*>(service)->UpdateVideoSkipPrompt();
}
void CKSrvCinematic_PlayNextVideo(IKSerializable* service, IKVideo*) { static_cast<CKSrvCinematic*>(service)->PlayNextVideo(); }

// 0x000aad78 PS3Video_SelectSoundTracks_maybe: the tracks BinkOpen opens with BINKSNDTRACK: the music
// track 0 and the voice language's (its index + 1; 1 when that is 0) when withVoice, else none.
void PS3Video_SelectSoundTracks(IKVideo*, uint32_t withVoice) {
    uint32_t voice = g_pEngine->m_locManager->GetVoiceLanguageIndex() + 1;
    if (voice == 0) voice = 1;
    const uint32_t tracks[2] = {0, voice};
    BinkSetSoundTrack((withVoice & 0xffu) != 0 ? 2u : 0u, tracks);
}


// The renderer flags the playing videos set every frame (renderer +0xa4, cleared after the frame).
uint32_t& RendererBits() { return g_pEngine->m_graphic->m_renderer->m_bitProperties; }

}  // namespace

// 0x000ab2a8 IKVideo constructor (Ghidra PS3_CKVideo_ConstructBase_maybe), in the original's store order.
IKVideo::IKVideo() {
    m_guidIdentifier[0] = 0;
    m_guidIdentifier[3] = 0;
    m_guidIdentifier[1] = 0;
    m_guidIdentifier[2] = 0;
}

// 0x009a0698 PS3_CKVideo_SetGuid (IKVideo's slot)
void IKVideo::SetGuid(const uint32_t* guid) { Uuid_Copy(m_guidIdentifier, guid); }

// 0x000ad5f8 IKVideo_Load
int32_t IKVideo::Load(IKFile* file, int32_t type) {
    if (type == K_GAME_PLATEFORMS) {
        ReadU32LE(file, &m_baData);
        IKFile_ReadLengthPrefixedString(file, m_szFileName, -1);
        ReadU32LE(file, &m_ui32AlphaLevel);
        ReadF32LE(file, &m_fRatio);
        m_state = 0;
        m_baFrameFlags &= ~0x400u;
        m_baData = (m_baData & ~0xfu) | 8u;
        m_ui32RasterNb = 0;
        m_pBink = nullptr;
        m_unk110 = 0;
        m_apRaster = nullptr;
        m_baData &= ~0x4000u;
        m_baFrameFlags &= ~2u;
        m_baData &= ~0x100000u;
        m_unk184 = -1;
        return 1;
    }
    if (type == K_LEVEL_PLATEFORMS) {
        m_tsEndVideoTrigger.Load(file, K_LEVEL_PLATEFORMS);
        IKFile_ReadTextureRef(file, &m_pTexture, 0);
        if (m_pTexture != nullptr) TextureRef_AddRef(m_pTexture);  // RwTexture +0x54 refCount + 1
    }
    return 1;
}

// 0x000ac410 IKVideo_vf30 (PostLoad): for the level, no segment; a video-to-texture (0x40) gets its texture's
// filter (bit 22 of the flags: linear) and clamp addressing.
int32_t IKVideo::PostLoad(int32_t type) {
    if (type != 0) return 1;
    m_pSegment = nullptr;
    const uint32_t linear = (m_baData >> 22) & 1u;
    if ((m_baData & 0x40u) == 0) return 1;
    m_baData = (m_baData & ~0x400000u) | (linear << 22);
    RwTexture* texture = static_cast<RwTexture*>(m_pTexture);
    if ((m_baData & 0x40u) != 0) {
        texture->filterAddressing = (texture->filterAddressing & 0xffffff00u) | (2u - (linear ^ 1u));
    }
    texture->filterAddressing = (texture->filterAddressing & 0xffff00ffu) | 0x1100u;
    return 1;
}

// 0x000ae480 PS3_CKVideo_Load
int32_t PS3_CKVideo::Load(IKFile* file, int32_t type) {
    IKVideo::Load(file, type);
    return 1;
}

// 0x000ae458 PS3_CKVideo_PostLoad
int32_t PS3_CKVideo::PostLoad(int32_t type) {
    IKVideo::PostLoad(type);
    return 1;
}

// ==== display rectangle and render states =========================================================

// 0x000a9d38 PS3_CKVideo_ComputeDisplayRect_maybe. Flag 0x800 fits the picture to the screen: letterboxed
// (full width) when the video's H/W is below the screen's and 0x800000 is clear, else pillarboxed (full
// height, 0x800000 forces it). Without 0x800 the picture is stretched to the screen; 0x40 (no quad) gives
// scale 1 at the origin.
void IKVideo::ComputeDisplayRect() {
    uint32_t width = 0;
    uint32_t height = 0;
    if (CameraContext_HasRasters()) {
        width = CameraContext_GetRasterWidth();    // raster +0x0c
        height = CameraContext_GetRasterHeight();  // raster +0x10
    }
    const uint32_t flags = m_baData;
    const BINK* bink = m_pBink;
    if ((flags & 0x800u) != 0) {
        const float pixelAspect = CameraContext_GetVideoPixelAspect();  // ctx +0x84
        const float screenRatio = CameraContext_GetHeightOverWidth();   // ctx +0x48
        const float ratio = m_fRatio;
        if ((flags & 0x800000u) == 0 && ratio < screenRatio) {
            // Letterbox: full width, height = width * ratio / pixel aspect, centred vertically.
            const float w = static_cast<float>(width);
            m_fScaleX = w / static_cast<float>(bink->Width);
            const float shown = (w * ratio) / pixelAspect;
            m_fPosX = 0.0f;
            m_fScaleY = shown / static_cast<float>(bink->Height);
            m_fPosY = (static_cast<float>(height) - shown) * 0.5f;
            return;
        }
        // Pillarbox: full height, width = pixel aspect * height / ratio, centred horizontally.
        const float h = static_cast<float>(height);
        m_fScaleY = h / static_cast<float>(bink->Height);
        m_fPosY = 0.0f;
        const float shown = pixelAspect * (h / ratio);
        m_fScaleX = shown / static_cast<float>(bink->Width);
        m_fPosX = (static_cast<float>(width) - shown) * 0.5f;
        return;
    }
    if ((flags & 0x40u) == 0) {
        m_fScaleX = static_cast<float>(width) / static_cast<float>(bink->Width);
        m_fPosY = 0.0f;
        m_fPosX = 0.0f;
        m_fScaleY = static_cast<float>(height) / static_cast<float>(bink->Height);
        return;
    }
    m_fScaleY = 1.0f;
    m_fPosY = 0.0f;
    m_fScaleX = 1.0f;
    m_fPosX = 0.0f;
}

// 0x000a9f50 PS3_CKVideo_SetRenderStates_maybe: z test and z write off, no texture raster, linear filtering, clamp
// addressing, Gouraud shading, no culling, no fog, alpha test "always", then (alpha level below 0xff) vertex alpha on
// and the blend pair m_blendIndex of the blend tables 0xc297ec / 0xc297fc (0: ONE / ZERO, 1: SRCALPHA /
// INVSRCALPHA), or (opaque) that pair and vertex alpha off. Draw wraps them in Push/PopRenderStates. The frame quad
// itself is the platform's PSGL replacement (DrawPSGLTexturedScreenQuad -> gfx DrawVideoPlanes), which sets the same
// GL blend from m_blendIndex.
void IKVideo::SetRenderStates() {
    static const int32_t kBlendSrc[4] = {2, 5, 5, 1};   // 0x00c297ec
    static const int32_t kBlendDest[4] = {1, 6, 2, 4};  // 0x00c297fc
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE, reinterpret_cast<void*>(0));
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, reinterpret_cast<void*>(0));
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER, nullptr);
    RwRenderStateSet(rwRENDERSTATETEXTUREFILTER, reinterpret_cast<void*>(2));
    RwRenderStateSet(rwRENDERSTATETEXTUREADDRESS, reinterpret_cast<void*>(3));
    RwRenderStateSet(rwRENDERSTATESHADEMODE, reinterpret_cast<void*>(2));
    RwRenderStateSet(rwRENDERSTATECULLMODE, reinterpret_cast<void*>(1));
    RwRenderStateSet(rwRENDERSTATEFOGENABLE, reinterpret_cast<void*>(0));
    RwRenderStateSet(rwRENDERSTATEALPHATESTFUNCTION, reinterpret_cast<void*>(8));
    if (m_ui32AlphaLevel != 0xffu) {
        RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, reinterpret_cast<void*>(1));
        RwRenderStateSet(rwRENDERSTATESRCBLEND, reinterpret_cast<void*>(static_cast<intptr_t>(kBlendSrc[m_blendIndex])));
        RwRenderStateSet(rwRENDERSTATEDESTBLEND, reinterpret_cast<void*>(static_cast<intptr_t>(kBlendDest[m_blendIndex])));
        return;
    }
    RwRenderStateSet(rwRENDERSTATESRCBLEND, reinterpret_cast<void*>(static_cast<intptr_t>(kBlendSrc[m_blendIndex])));
    RwRenderStateSet(rwRENDERSTATEDESTBLEND, reinterpret_cast<void*>(static_cast<intptr_t>(kBlendDest[m_blendIndex])));
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, reinterpret_cast<void*>(0));
}

// 0x000aa370 PS3_CKVideo_SetFadeLevel_maybe
void IKVideo::SetFadeLevel(uint32_t level) {
    m_ui32AlphaLevel = level;
    m_blendIndex = level != 0xffu ? 1u : 0u;
}

// ==== seeking and position ========================================================================

// 0x000aa398 PS3_CKVideo_SetCurrentAndTargetFrame_maybe: a pending seek to the keyframe closest to frame.
void IKVideo::SeekToKeyFrameNear(int32_t frame) {
    m_baFrameFlags = (m_baFrameFlags & ~0x200u) | 0x30u;
    m_seekFrame = frame;
    m_seekHoldFrames = 0;
    m_resumeFrame = frame;
}

// 0x000ab260 PS3_CKVideo_SetCurrentAndTargetFrame_VariantB_maybe: a pending seek to exactly frame.
void IKVideo::SeekToFrame(int32_t frame) {
    m_baFrameFlags |= 0x230u;
    m_seekFrame = frame;
    m_seekHoldFrames = 0;
    m_resumeFrame = frame;
}

// 0x000aa920 PS3_CKVideo_GetFrameCount_maybe
int32_t IKVideo::GetFrameCount() {
    if (m_pBink == nullptr) return -1;
    return static_cast<int32_t>(m_pBink->Frames);
}

// 0x000abe58 PS3_CKVideo_GetElapsedSeconds_maybe
double IKVideo::GetElapsedSeconds() {
    const BINK* bink = m_pBink;
    if (bink == nullptr) return 0.0;
    return static_cast<double>(static_cast<float>(bink->FrameNum) /
                               (static_cast<float>(bink->FrameRate) / static_cast<float>(bink->FrameRateDiv)));
}

// 0x000ac4a0 PS3_CKVideo_GetPlaybackPosition_maybe: the current frame, or the pending seek's target.
int32_t IKVideo::GetPlaybackPosition() {
    BINK* bink = m_pBink;
    if (bink == nullptr || (m_baData & 1u) == 0) return 0;
    if ((m_baFrameFlags & 0x10u) == 0) return static_cast<int32_t>(bink->FrameNum);
    if ((m_baFrameFlags & 0x200u) == 0) {
        return static_cast<int32_t>(BinkGetKeyFrame(bink, static_cast<uint32_t>(m_seekFrame), BINKGETKEYCLOSEST)) +
               g_videoKeyFrameOffset;
    }
    return m_seekFrame;
}

// 0x000acf00 PS3_CKVideo_SetSegment_maybe: switches the running video to another segment (a keyframe seek
// to its start).
void IKVideo::SetSegment(CKVideoSegment* segment) {
    CKVideoSegment* current = m_pSegment;
    if (current != nullptr && current != segment) current->MarkEndedIfPlaying();
    m_pSegment = segment;
    const int32_t start = static_cast<int32_t>(segment->GetStartFrame());
    m_baFrameFlags = (m_baFrameFlags & ~0x200u) | 0x30u;
    m_seekFrame = start;
    m_seekHoldFrames = 0;
    m_resumeFrame = start;
}

// ==== start, play, stop ===========================================================================

// 0x000ad2c0 PS3_CKVideo_vf60: starts playback (of the segment, if any). A video that is not already
// playing and draws a quad first stops the other quad videos. The loading video (0x4000) opens at once
// (state 5); the others join the manager's list and open through Update's states.
int32_t IKVideo::Start(CKVideoSegment* segment) {
    if (m_state != 0) return 1;
    if ((m_baData & 1u) == 0 && (m_baData & 0x40u) == 0) {
        CKSrvCinematic* cinematic = static_cast<CKSrvCinematic*>(g_pEngine->m_srvCinematic);
        CVideoManager* manager = VideoManager();
        if (cinematic->m_pCurrentVideoBloc != nullptr) cinematic->m_pCurrentVideoBloc = nullptr;
        while (manager->HasVideoWithoutFlag40()) manager->StopFirstActiveVideoWithoutFlag40();
    }
    m_baData &= ~0x2000u;
    m_baFrameFlags = ((m_baFrameFlags & ~4u) | 4u) & ~0x108u;
    m_baData &= ~2u;
    m_baFrameFlags = (m_baFrameFlags & ~0xe1u) | 0x20u;
    m_seekHoldFrames = 0;
    m_baFrameFlags &= ~0x210u;
    m_unk180 = -1;
    m_pSegment = segment;
    m_seekFrame = -1;
    if ((m_baData & 0x4000u) == 0) VideoManager()->AddActiveVideo(this);
    m_baFrameFlags &= ~0x400u;
    if ((m_baData & 0x4000u) == 0) {
        m_state = 1;
        return 1;
    }
    RestartSegmentOrLoop();
    m_state = m_pBink != nullptr ? 5 : 4;
    return 1;
}

// 0x000ad040 PS3_CKVideo_RestartSegmentOrLoop_maybe: opens the stream (vt+0x54) and arms a seek to the
// start: the segment's start (or its loop start), else frame 1.
int32_t IKVideo::RestartSegmentOrLoop() {
    m_baFrameFlags |= 0x400u;
    if ((m_baData & 1u) != 0) return 1;
    m_resumeFrame = 1;
    CKVideoSegment* segment = m_pSegment;
    if (segment != nullptr) {
        m_resumeFrame = static_cast<int32_t>(segment->m_useLoopStart != 0 ? segment->GetLoopFrame()
                                                                          : segment->GetStartFrame());
    }
    const int32_t result = Play();  // vt+0x54
    if (result != 1) return result;
    if (m_resumeFrame == 1 && (m_baData & 0x4000u) == 0) GameManager_VideoMessage(0x2501, this);
    CreateFrameTextures();  // vt+0x8c
    m_baData = ((m_baData & ~1u) | 1u) & ~0x2000u;
    m_baFrameFlags = ((m_baFrameFlags & ~4u) | 4u) & ~0x108u;
    m_blendIndex = m_ui32AlphaLevel != 0xffu ? 1u : 0u;
    const int32_t frame = m_resumeFrame;
    m_baFrameFlags = ((((m_baFrameFlags & ~0x10u) | 0x10u) & ~0x220u) | 0x20u);
    m_startFrame = frame;
    m_seekHoldFrames = 0;
    m_resumeFrame = frame;
    m_seekFrame = frame;
    if ((m_baData & 2u) != 0) return result;
    BinkPause(m_pBink, 0);
    return 1;
}

// 0x000ac740 PS3_CKVideo_BeginPlayback_maybe (IKVideo vt+0x54): opens the stream paused, sets the track
// volumes and the display rectangle.
int32_t IKVideo::Play() {
    if ((m_baData & 4u) != 0) return 1;
    BINK* bink = m_pBink;
    if (bink == nullptr) {
        OpenStream();  // vt+0x9c
        bink = m_pBink;
        if (bink == nullptr) return 0;
    }
    BinkPause(bink, 1);
    if (bink->Width == 1 && bink->Height == 1) m_baData = (m_baData & ~0x200u) | 0x200u;  // a 1x1 video: hidden
    const float speech = Video_GetSpeechVolume(VideoManager());
    if (m_pBink != nullptr) {
        const uint32_t voiceTrack = g_pEngine->m_locManager->GetVoiceLanguageIndex() + 1;
        BinkSetVolume(m_pBink, voiceTrack, ppc::fctiwz(static_cast<double>(speech) * static_cast<double>(kBinkVolumeScale)));
    }
    const float music = Video_GetMusicVolume(VideoManager());
    if (m_pBink != nullptr) {
        BinkSetVolume(m_pBink, 0u, ppc::fctiwz(static_cast<double>(music) * static_cast<double>(kBinkVolumeScale)));
    }
    m_baData = (m_baData & ~4u) | 4u;
    ComputeDisplayRect();
    return 1;
}

// 0x000aede0 PS3_CKVideo_Play_maybe: BeginPlayback, then the XMB background music is disabled unless the
// game manager allows it (or the video has several audio tracks).
int32_t PS3_CKVideo::Play() {
    const int32_t result = IKVideo::Play();
    if (GameManager_AllowsBgmDuringVideo(this) == 0 || (m_pBink != nullptr && 1 < static_cast<int32_t>(m_pBink->NumTracks))) {
        cellSysutilDisableBgmPlayback();
    }
    return result;
}

// 0x000a9c50 PS3_CKVideo_CloseStreamIfOpen_maybe
void IKVideo::CloseStreamIfOpen() {
    if ((m_baData & 4u) == 0) return;
    CloseStream();  // vt+0xa0
    m_baData &= ~4u;
}

// 0x000a9cc8 PS3_CKVideo_vf5C
void IKVideo::Reopen() {
    CloseStreamIfOpen();  // vt+0x58
    Play();               // vt+0x54
}

// 0x000acd90 PS3_CKVideo_OpenBink_maybe (IKVideo vt+0x9c; PS3_CKVideo overrides it with OpenStream).
BINK* IKVideo::OpenStream() { return nullptr; }  // STUB: not reachable (PS3_CKVideo overrides vt+0x9c)

// 0x000ae840 PS3_CKVideo_OpenStream_maybe: "%s%s" (data root, file name), backslashes converted, then
// BinkOpen with the open flags the video's flags choose.
BINK* PS3_CKVideo::OpenStream() {
    char path[0x100];
    std::snprintf(path, sizeof(path), "%s%s", g_pEngine->m_fileSystem->m_dataRoot, m_szFileName);  // KFileSystem_GetDataRoot 0x48fa0
    KFileSystem_ConvertBackslashes(g_pEngine->m_fileSystem, path);
    uint32_t openFlags = 0x2000u;
    uint32_t withVoice = 0;
    const uint32_t flags = m_baData;
    if ((flags & 0x4000u) == 0 && (flags & 0x20000u) == 0) {
        openFlags = ((flags & 0x200000u) != 0 ? 0x100000u : 0u) + 0x204000u;
        if ((flags & 0x1000u) == 0) withVoice = 1;
    }
    PS3Video_SelectSoundTracks(this, withVoice);
    m_unk110 = 0;
    // The PS3 copies the path into a 0x40-byte name buffer (memset + strcpy) before BinkOpen.
    m_pBink = BinkOpen(path, openFlags);
    return m_pBink;
}

// 0x000ae9c8 PS3_CKVideo_CloseStream_maybe
void PS3_CKVideo::CloseStream() {
    if (m_pBink == nullptr) return;
    BinkClose(m_pBink);
    m_pBink = nullptr;
    if (m_unk110 != 0) m_unk110 = 0;  // KFileSystem_CloseFile 0x49dd8: no file handle is ever stored here
}

// 0x000ae430 PS3_CKVideo_vfA4
int32_t PS3_CKVideo::RestartSegmentOrLoopSlot() { return RestartSegmentOrLoop(); }

// 0x000aafe0 PS3_CKVideo_Pause_maybe
void IKVideo::Pause() {
    if (m_state == 2) return;
    if ((m_baData & 0x100000u) != 0 && m_unk184 != -1) return;
    m_baData = (m_baData & ~2u) | 2u;
    if (m_pBink != nullptr) BinkPause(m_pBink, 1);
}

// 0x000aaf60 PS3_CKVideo_vf80 (resume)
void IKVideo::Resume() {
    if ((m_baData & 0x100000u) != 0 && m_unk184 != -1) return;
    m_baData &= ~2u;
    if (m_pBink != nullptr) BinkPause(m_pBink, 0);
}

// 0x000ab890 PS3_CKVideo_StopImpl_maybe: leaves the manager's list, closes the stream, gives the game
// sounds back, signals the end trigger and the game manager (0x2502).
void IKVideo::Stop() {
    if (m_state == 0) return;
    if (m_pSegment != nullptr) {
        m_pSegment->MarkEndedIfPlaying();
        m_pSegment = nullptr;
    }
    if ((m_baData & 0x4000u) == 0) VideoManager()->RemoveActiveVideo(this);
    m_baData &= ~1u;
    DestroyFrameTextures();  // vt+0x90
    if (m_pBink != nullptr) BinkPause(m_pBink, 1);
    CloseStreamIfOpen();  // vt+0x58
    if ((m_baData & 0x4000u) == 0) {
        int32_t state = m_state;
        if (1 < state && (m_baData & 0x100000u) != 0 && m_unk184 == -1) {
            GameLoop_DecPauseCount(GameLoop());
            state = m_state;
        }
        if (2 < state) {
            if ((m_baData & 0x1000u) == 0) SoundSuspend_Release(VideoManager());
            Video_RestoreGameSound(VideoManager());
        }
        QueueTriggerSignals(&m_tsEndVideoTrigger);
    }
    m_baData &= ~0x2002u;
    if ((m_baData & 0x4000u) == 0) GameManager_VideoMessage(0x2502, this);
    if ((m_baData & 0x100000u) != 0) {
        m_baData &= ~0x100000u;
        m_unk184 = -1;
    }
    m_baFrameFlags &= ~0x400u;
    m_state = 0;
}

// 0x000aed08 PS3_CKVideo_Stop_maybe: StopImpl; a playing video gives the XMB music back when it took it.
void PS3_CKVideo::Stop() {
    if (m_state != 0 &&
        (GameManager_AllowsBgmDuringVideo(this) == 0 || (m_pBink != nullptr && 1 < static_cast<int32_t>(m_pBink->NumTracks)))) {
        cellSysutilEnableBgmPlayback();
    }
    IKVideo::Stop();
}

// 0x000ab3e0 PS3_CKVideo_StopIfEnded_maybe: an open video that reached its end (and is not a cutscene)
// stops.
void IKVideo::StopIfEnded() {
    const uint32_t flags = m_baData;
    if ((flags & 4u) != 0 && (flags & 0x2000u) != 0 && (flags & 0x100000u) == 0) Stop();  // vt+0x78
}

// 0x000abbc0 PS3_CKVideo_MessageProc
int32_t IKVideo::HandleMessage(uint32_t message) {
    if (message == 0x2502) {
        Stop();  // vt+0x78
        return 0;
    }
    if (message == 0x2504) return 0;
    if (message == 0x2501) {
        Start(nullptr);  // vt+0x60
        return 0;
    }
    return 1;
}

// ==== the per-frame work ==========================================================================

// 0x000ad890 PS3_CKVideo_UpdatePlaybackState_maybe (IKVideo vt+0x64): the start states (wait for the game
// loop's pause count, the game sounds), the stream reopen after a read error, the renderer flags, the
// cutscene skip path, pausing while a system message or the XMB is up, the pending seek, then BinkWait:
// when the next frame is due it is decoded (vt+0x74) and frame flag 8 is set for UpdateFrame.
void IKVideo::Update(IKTime*) {
    CKGameLoop* loop = GameLoop();
    int32_t state = m_state;
    BINK* bink = nullptr;
    uint32_t frameFlags = 0;
    switch (state) {
    case 1: goto state1;
    case 2: goto state2;
    case 3: goto state3;
    case 4: goto state4;
    case 5: goto state5;
    case 6: goto state6;
    default: goto tail;
    }

state1: {
    const uint32_t flags = m_baData;
    if ((flags & 0x100000u) != 0) {
        // A cutscene waits until the game loop is not inhibited and pausable.
        if (loop->m_inhibitCount != 0) {
            state = m_state;
            goto from5;
        }
        if (loop->Vf74() == 0) {
            m_state = 2;
            GameLoop_IncPauseCount(loop);
        }
        state = m_state;
        goto from2;
    }
    if (loop->m_inhibitCount != 0) {
        m_state = 2;
        goto state2;
    }
    m_state = 4;
    if ((flags & 0x4000u) != 0) goto state4;
    uint32_t reread = flags;
    if ((flags & 0x1000u) == 0) {
        m_state = 3;
        SoundSuspend_Acquire(VideoManager());
        reread = m_baData;
    }
    if ((reread & 0x40000u) != 0) Video_MuteGameSound(VideoManager());
    state = m_state;
    goto from2;
}

state2: {
    if (loop->Vf74() != 0) {
        uint32_t flags = m_baData;
        m_state = 4;
        if ((flags & 0x1000u) == 0) {
            m_state = 3;
            SoundSuspend_Acquire(VideoManager());
            flags = m_baData;
        }
        if ((flags & 0x40000u) != 0) Video_MuteGameSound(VideoManager());
    }
    state = m_state;
    goto from3;
}

state3:
    if (SoundSuspend_AreStreamsState9(VideoManager()) != 0) {
        m_state = 4;
        goto state4;
    }
    state = m_state;
    goto from4;

state4:
    RestartSegmentOrLoop();
    if (m_pBink == nullptr) {
        state = m_state;
        goto from5;
    }
    m_state = 5;
    goto state5;

state5:
    if ((m_baFrameFlags & 2u) == 0) goto tail;
    // A read error: remember where to resume, close and reopen the stream.
    m_baFrameFlags &= ~2u;
    if (m_pBink != nullptr) {
        int32_t resume = 0;
        if ((m_baData & 1u) != 0) {
            if ((m_baFrameFlags & 0x10u) == 0) {
                resume = static_cast<int32_t>(m_pBink->FrameNum);
            } else if ((m_baFrameFlags & 0x200u) == 0) {
                resume = static_cast<int32_t>(BinkGetKeyFrame(m_pBink, static_cast<uint32_t>(m_seekFrame),
                                                              BINKGETKEYCLOSEST)) +
                         g_videoKeyFrameOffset;
            } else {
                resume = m_seekFrame;
            }
        }
        m_resumeFrame = resume;
    }
    CloseStream();  // vt+0xa0
    m_state = 6;
    goto state6;

state6:
    OpenStream();  // vt+0x9c
    if (m_pBink != nullptr) {
        BinkGoto(m_pBink, static_cast<uint32_t>(m_resumeFrame), 0);
        RegisterFrameBuffers();  // vt+0x94
        m_state = 5;
    }
    goto tail;

from2:  // 0xad8d8: the dispatch again, from state 2 on
    if (state == 2) goto state2;
from3:
    if (state == 3) goto state3;
from4:
    if (state == 4) goto state4;
from5:
    if (state == 5) goto state5;
    if (state == 6) goto state6;

tail:
    if ((m_baData & 0x20u) == 0 && (m_baFrameFlags & 0x40u) == 0) RendererBits() |= 4u;
    if ((m_baData & 0x10u) == 0 && (m_baFrameFlags & 0x80u) == 0) RendererBits() |= 2u;
    bink = m_pBink;
    if (bink == nullptr) return;
    if ((m_baData & 0x100000u) != 0) {
        if (m_unk184 == -1) {
            IKSerializable* cinematic = g_pEngine->m_srvCinematic;
            const int32_t prompt = CKSrvCinematic_UpdateVideoSkipPrompt(cinematic, this);
            if (static_cast<uint32_t>(prompt - 2) <= 1u || (m_baData & 0x2000u) != 0 ||
                GameLoop_HasRequestedLevel(loop)) {
                if (prompt != 3) CKSrvCinematic_PlayNextVideo(cinematic, this);
                if (m_state == 0) return;
                m_unk184 = 0;
                GameLoop_DecPauseCount(loop);
            }
        } else {
            m_unk184 += 1;
            if (static_cast<uint32_t>(m_unk184) > 4u) Stop();  // vt+0x78
        }
        if (m_state == 0) return;
    }
    if (m_unk184 == -1) {
        // Paused while the loop is inhibited more than once, the XMB is open or a system message is queued
        // (not during the first frames after a start).
        const bool inhibited = static_cast<uint32_t>(loop->m_inhibitCount) > 1u || g_systemMenuOpen != 0 ||
                               MessageBox_GetQueuedCount() != 0;
        if (inhibited && (m_baFrameFlags & 0x20u) == 0) {
            if ((m_baData & 2u) == 0 && bink->Paused == 0) BinkPause(bink, 1);
        } else if ((m_baData & 2u) == 0 && bink->Paused == 1) {
            BinkPause(bink, 0);
        }
    }
    frameFlags = m_baFrameFlags;
    if ((frameFlags & 0x10u) != 0) {
        BINK* current = m_pBink;
        int32_t target = m_seekFrame;
        if (current != nullptr) {
            if ((frameFlags & 0x200u) == 0) {
                target = static_cast<int32_t>(BinkGetKeyFrame(current, static_cast<uint32_t>(m_seekFrame),
                                                              BINKGETKEYCLOSEST)) +
                         g_videoKeyFrameOffset;
            }
            BinkGoto(current, static_cast<uint32_t>(target), 0);
        }
        m_baFrameFlags = (m_baFrameFlags & ~0x310u) | 0x100u;
        m_seekHoldFrames = 0;
        m_seekFrame = -1;
    }
    // BinkWait (Ghidra: TocBridge_BinkShouldSkip_maybe 0x98e650) is 0 once the next frame is due.
    const int32_t wait = BinkWait(bink);
    m_baFrameFlags = (m_baFrameFlags & ~8u) | (wait == 0 ? 8u : 0u);
    if ((m_baFrameFlags & 8u) != 0) AdvanceFrame();  // vt+0x74
}

// 0x000aec20 PS3_CKVideo_Update_maybe: the state machine, then (when the game manager lets the system
// music play during this video and the video has at most one track) the music track is silent while the
// XMB plays music, else at the game's music volume.
void PS3_CKVideo::Update(IKTime* frameClock) {
    IKVideo::Update(frameClock);
    if (GameManager_AllowsBgmDuringVideo(this) == 0) return;
    if (m_pBink != nullptr && 1 < static_cast<int32_t>(m_pBink->NumTracks)) return;
    CellSysutilBgmPlaybackStatus status;
    float volume;
    if (cellSysutilGetBgmPlaybackStatus(&status) != 0 || status.playerState != 0) {
        volume = Video_GetMusicVolume(VideoManager());
    } else {
        volume = 0.0f;  // TOC -0x17c1
    }
    PS3_CKVideo_SetTrackVolume(volume, this);
}

// 0x000ab1c8 PS3_CKVideo_AdvanceFrame_maybe: next frame set (vt+0x70), decode.
void IKVideo::AdvanceFrame() {
    SelectNextFrame();  // vt+0x70
    BINK* bink = m_pBink;
    if (bink == nullptr) return;
    BinkDoFrame(bink);
    if (bink->ReadError != 0) m_baFrameFlags = (m_baFrameFlags & ~2u) | 2u;
}

// 0x000ae2d0 PS3_CKVideo_SelectNextFrame
void PS3_CKVideo::SelectNextFrame() { PS3Video_SelectNextFrame(&m_frameBuffers); }

// 0x000ac908 PS3_CKVideo_UpdateFrame_maybe (IKVideo vt+0x68): follows the clock's pause, then, when Update
// decoded a frame: the segment's jumps, the end of the video (flag 0x2000, unless it loops: 0x400) and
// BinkNextFrame; while Bink reports playback behind (BinkShouldSkip, Ghidra: TocBridge_BinkWait 0x98e620)
// the next frames are decoded without being shown.
uint8_t IKVideo::UpdateFrame(IKTime* frameClock) {
    BINK* bink = m_pBink;
    if (bink == nullptr) return 0;
    if ((m_baFrameFlags & 1u) == 0) ComputeDisplayRect();
    if ((m_baData & 0x4000u) == 0) {
        if (frameClock->m_eCurrentState == 3) {
            if ((m_baData & 2u) != 0) return 0;
            Pause();  // vt+0x7c
            m_baFrameFlags = (m_baFrameFlags & ~1u) | 1u;
            return 0;
        }
        if ((m_baFrameFlags & 1u) != 0) {
            m_baFrameFlags &= ~1u;
            if ((m_baData & 2u) != 0) Resume();  // vt+0x80
        }
    }
    if (bink->Paused == 1) return 0;
    if ((m_baFrameFlags & 8u) != 0) {
        bool first = true;
        for (;;) {
            uint8_t segmentStop = 0;
            if (m_pSegment != nullptr) {
                const uint8_t atEnd = m_pSegment->IsAtEnd();
                segmentStop = m_pSegment->UpdatePlayback();
                m_baData = (m_baData & ~0x2000u) | ((static_cast<uint32_t>(segmentStop) << 13) & 0x1fe000u);
                if (atEnd != 0) break;
            }
            if (!first) AdvanceFrame();  // vt+0x74
            m_baFrameFlags &= ~4u;
            bool show = true;
            bool more = true;
            if (m_pBink->FrameNum == m_pBink->Frames && (m_baData & 0x400u) == 0) {
                // The last frame of a video that does not loop: it ends (StopIfEnded stops it after the draw).
                show = false;
                more = false;
                m_baData = (m_baData & ~0x2000u) | 0x2000u;
            } else if (m_pBink->ReadError != 0) {
                m_baFrameFlags = (m_baFrameFlags & ~2u) | 2u;
            }
            const bool behind = BinkShouldSkip(bink) == 1;
            if (!behind && show) CopyFrameToTexture(0);  // vt+0x6c
            if (!more) break;
            if ((m_baFrameFlags & 2u) != 0 || segmentStop != 0) break;
            BinkNextFrame(bink);
            if (bink->ReadError != 0) m_baFrameFlags = (m_baFrameFlags & ~2u) | 2u;
            first = false;
            if (!behind) break;
        }
    }
    if ((m_baFrameFlags & 0x20u) != 0) {
        if (m_seekHoldFrames <= 3) {
            ++m_seekHoldFrames;
            return 1;
        }
        m_baFrameFlags &= ~0x20u;
    }
    return 1;
}

// 0x000ae408 PS3_CKVideo_UpdateFrameThunk_maybe
uint8_t PS3_CKVideo::UpdateFrame(IKTime* frameClock) { return IKVideo::UpdateFrame(frameClock); }

// ==== drawing =====================================================================================

// 0x000abd20 IKVideo_DrawPlaceholderQuad_maybe: without a stream (+0x10c), and unless hidden (m_baData
// 0x200 or 0x40), the screen is covered with the shared black at 0x00c50df8 (TOC1 -0x5f70; 0, 0, 0, 0xff
// from Str.cpp's static initialiser, opaque; live RPCS3 000000ff) through Draw2d_FullScreenColorQuad.
void IKVideo::Draw(IKTime*) {
    if (m_pBink != nullptr) return;
    if ((m_baData & 0x40u) != 0 || (m_baData & 0x200u) != 0) return;
    static const uint8_t kSharedBlack[4] = {0x00, 0x00, 0x00, 0xff};
    Draw2d_FullScreenColorQuad(kSharedBlack);  // 0x687a8
}

// 0x000ae1b0 DrawPS3VideoFrameQuad (vt+0x84)
void PS3_CKVideo::Draw(IKTime* frameClock) {
    IKVideo::Draw(frameClock);
    BINK* bink = m_pBink;
    if (bink != nullptr && (m_baData & 0x200u) == 0 && (m_baData & 0x40u) == 0) {
        PushRenderStates(g_pRenderStateRenderer);
        SetRenderStates();
        DrawPSGLTexturedScreenQuad(m_fPosX, m_fPosY, m_fScaleX, m_fScaleY, 1.0f, &m_frameBuffers, bink->Width,
                                   bink->Height, 0, m_blendIndex != 0);
        PopRenderStates(g_pRenderStateRenderer);
    }
    StopIfEnded();
}

// 0x000ae378 PS3_CKVideo_CreateFrameTextures_maybe
void PS3_CKVideo::CreateFrameTextures() {
    BINK* bink = m_pBink;
    if (bink == nullptr) return;
    BinkGetFrameBuffersInfo(bink, &m_frameBuffers);
    if (PS3Video_CreateFrameBuffers(&m_frameBuffers) != 0) BinkRegisterFrameBuffers(bink, &m_frameBuffers);
}

// 0x000ae340 PS3_CKVideo_DestroyFrameTextures
void PS3_CKVideo::DestroyFrameTextures() {
    if (m_pBink != nullptr) PS3Video_DestroyFrameTextures(&m_frameBuffers);
}

// 0x000ae300 PS3_CKVideo_vf94: the buffers again for a reopened stream.
void PS3_CKVideo::RegisterFrameBuffers() {
    if (m_pBink != nullptr) BinkRegisterFrameBuffers(m_pBink, &m_frameBuffers);
}

// ==== the video system ============================================================================

// 0x000aea40 PS3Video_InitRenderer_maybe: BinkPS3's renderer (an SPU count of 2; the remake decodes on
// the CPU), then the shader for the frame buffer's size.
void PS3Video_InitRenderer() {
    uint32_t width = 0;
    uint32_t height = 0;
    if (CameraContext_HasRasters()) {
        width = CameraContext_GetRasterWidth();
        height = CameraContext_GetRasterHeight();
    }
    PS3Video_CreateShader(width, height);
}

// 0x000ae548 PS3Video_Shutdown_maybe: BinkPS3's shutdown. Nothing to release on the host.
void PS3Video_Shutdown() {}

// 0x000aae20 PS3_CKVideo_SetTrackVolume_maybe: the music track (0).
void PS3_CKVideo_SetTrackVolume(float volume, IKVideo* video) {
    if (video->m_pBink != nullptr) {
        BinkSetVolume(video->m_pBink, 0u, static_cast<int32_t>(ppc::fctiwz(static_cast<double>(volume) * 32768.0)));
    }
}

// 0x000aae70 PS3_CKVideo_SetSpeechTrackVolume_maybe: the voice language's track.
void PS3_CKVideo_SetSpeechTrackVolume(float volume, IKVideo* video) {
    if (video->m_pBink != nullptr) {
        const uint32_t track = g_pEngine->m_locManager->GetVoiceLanguageIndex() + 1;
        BinkSetVolume(video->m_pBink, track,
                      static_cast<int32_t>(ppc::fctiwz(static_cast<double>(volume) * static_cast<double>(kBinkVolumeScale))));
    }
}

#include "Renderware/rwcore/RwTexture.h"
#include "k2000/core/IKInfo.h"
#include "k2000/logic/CKSavingManager.h"

// 0x000ab2c8 IKVideo_vf24
void IKVideo::RecursiveRegistration(int32_t type) {
    if (type == 0) {
        g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);  // vt+0x24
        // KStub_Return1_2361b0(&m_tsEndVideoTrigger, 0): the trigger starter registers nothing.
        return;
    }
    if (type != 1) return;
    g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);
}

// 0x000abb50 PS3_CKVideo_GetInfo
int32_t IKVideo::GetInfo(IKInfo* info, int32_t request) {
    if (request == kGetInfoValueAccessor && info->m_ui32Id == 5) {
        return AnswerInfo(
            info, [](IKSerializable* self, uint32_t) { return static_cast<uint32_t>(static_cast<IKVideo*>(self)->GetPlaybackPosition()); },
            1);
    }
    return 1;
}

// 0x000abc98 PS3_CKVideo_ReleaseTexture_maybe
void IKVideo::ReleaseTexture() {
    if ((m_baData & 0x40u) != 0) {
        if (m_pTexture != nullptr) RwTextureDestroy(static_cast<RwTexture*>(m_pTexture));
        m_pTexture = nullptr;
    }
    CloseStreamIfOpen();  // vt+0x58
}
