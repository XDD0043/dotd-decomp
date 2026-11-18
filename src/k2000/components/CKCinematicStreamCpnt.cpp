// CKCinematicStreamCpnt.cpp - reconstructed original translation unit 0x80a90-0x864b8 (GAME_TOC1, main_toc1), 67 functions, 32 live.
// Primary class: CKCinematicStreamCpnt  key 0x13c6  category Component  size 0x100  vtable 0xb168b8
// Other owners: CinematicStreamFile (2)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x80a90  CKCinematicStreamCpnt_Delete
//   [ ] 0x80ae0  CKCinematicStreamCpnt_ZeroRuntimeFields_maybe  [dead]
//   [x] 0x80b38  CKCinematicStreamCpnt_vf50  (CKCinematicStreamCpnt.h Vf50 (empty))
//   [ ] 0x80b40  CKCinematicStreamCpnt_LinkEntriesById_maybe  [dead]
//   [ ] 0x80be0  CKCinematicStreamCpnt_SetEntryState_maybe  [dead]
//   [ ] 0x80c50  FUN_00080c50  [dead]
//   [ ] 0x80ca0  KStub_Nop_80ca0  [dead]
//   [ ] 0x80ca8  KStub_Nop_80ca8  [dead]
//   [ ] 0x80cb0  KStub_Nop_80cb0  [dead]
//   [ ] 0x80cb8  CKCinematicStreamCpnt_CheckFileOpened_maybe  [dead]
//   [ ] 0x80ce0  CinematicStreamFile_ConsumeReadComplete_maybe  [dead]
//   [ ] 0x80d18  CKCinematicStreamCpnt_PollReadCompleteSetState5_maybe  [dead]
//   [ ] 0x80d90  CKCinematicStreamCpnt_PollReadCompleteSetState7_maybe  [dead]
//   [ ] 0x80e30  FUN_00080e30  [dead]
//   [ ] 0x80f40  FUN_00080f40  [dead]
//   [ ] 0x81070  FUN_00081070  [dead]
//   [x] 0x81130  CKCinematicStreamCpnt_GetChannelMarkList_maybe
//   [ ] 0x81188  CinematicStreamFile_GetTrackSlot_maybe  [dead]
//   [ ] 0x811a8  CKCinematicStreamCpnt_FindChannelIndexByActor_maybe  [dead]
//   [ ] 0x81218  RegisterCKCinematicStreamCpntClass
//   [ ] 0x81348  _GLOBAL__I_81348
//   [x] 0x81358  CKCinematicStreamCpnt_DeleteArray
//   [x] 0x81400  CKCinematicStreamCpnt_CloseStream_maybe
//   [ ] 0x81468  CKCinematicStreamCpnt_RequestRead_maybe  [dead]
//   [ ] 0x814b8  CKCinematicStreamCpnt_StopSekens_maybe  [dead]
//   [ ] 0x81508  CKCinematicStreamCpnt_StartPausedSekens_maybe  [dead]
//   [ ] 0x81590  CKCinematicStreamCpnt_RequestSekensPaused_maybe  [dead]
//   [ ] 0x81638  CKCinematicStreamCpnt_RefreshSekensActiveFlag_maybe  [dead]
//   [ ] 0x816d0  CKCinematicStreamCpnt_StopMusicPlayList_maybe  [dead]
//   [ ] 0x81720  CKCinematicStreamCpnt_StartPausedMusicTrack_maybe  [dead]
//   [ ] 0x817a8  CKCinematicStreamCpnt_RequestMusicTrack_maybe  [dead]
//   [ ] 0x81850  CKCinematicStreamCpnt_RefreshMusicReadyFlag_maybe  [dead]
//   [ ] 0x818f0  CKCinematicStreamCpnt_FreeAllEntryBuffers_maybe  [dead]
//   [x] 0x81980  CKCinematicStreamCpnt_BuildStreamPath_maybe
//   [x] 0x81a38  CKCinematicStreamCpnt_PostLoad
//   [ ] 0x81b58  FUN_00081b58  [dead]
//   [ ] 0x81c30  CKCinematicStreamCpnt_FindChannelIndexBySecondActor_maybe  [dead]
//   [x] 0x81ca0  CKCinematicStreamCpnt_InitChannels_maybe
//   [x] 0x81db8  CKCinematicStreamCpnt_ResetChannels_maybe
//   [ ] 0x81ed0  CKCinematicStreamCpnt_Save
//   [x] 0x81ed8  CKCinematicStreamCpnt_RecursiveRegistration
//   [ ] 0x81f40  CKCinematicStreamCpnt_GetChannelBufferField20_maybe  [dead]
//   [x] 0x82008  CKCinematicStreamCpnt_Stop_maybe
//   [x] 0x82290  CKCinematicStreamCpnt_ReadNextChunk_maybe
//   [ ] 0x82470  CKCinematicStreamCpnt_RequestChunkHeader_maybe  [dead]
//   [ ] 0x82598  FUN_00082598  [dead]
//   [x] 0x826d8  CKCinematicStreamCpnt_UpdateSyncedMedia_maybe
//   [x] 0x829d0  CKCinematicStreamCpnt_ReopenStream_maybe
//   [x] 0x82a88  CKCinematicStreamCpnt_Finish_maybe
//   [ ] 0x82cb0  CKCinematicStreamCpnt_UpdateSetHandlers_maybe  [dead]
//   [x] 0x82ec0  CKCinematicStreamCpnt_DispatchChunk_maybe
//   [ ] 0x83138  CKCinematicStreamCpnt_ResizeChannels_maybe  [dead]
//   [x] 0x83268  CKCinematicStreamCpnt_StepSegmentStateMachine_maybe
//   [x] 0x83820  CKCinematicStreamCpnt_Update_maybe
//   [x] 0x83f18  CKCinematicStreamCpnt_UpdateStream_maybe
//   [x] 0x84308  CKCinematicStreamCpnt_StreamReadyJobCallback_maybe
//   [x] 0x843c0  CKCinematicStreamCpnt_AllocChunkTables_maybe
//   [x] 0x84860  CKCinematicStreamCpnt_FreeChunkTables_maybe
//   [x] 0x84a58  CKCinematicStreamCpnt_Destroy
//   [x] 0x84a60  CKCinematicStreamCpnt_OpenStreamFile_maybe
//   [x] 0x84ca8  CKCinematicStreamCpnt_StartStream_maybe
//   [x] 0x84ef8  CKCinematicStreamCpnt_ConstructBase_maybe
//   [ ] 0x85238  CKCinematicStreamCpnt_Construct  [dead]
//   [ ] 0x852d8  CKCinematicStreamCpnt_Construct_2  [dead]
//   [x] 0x85378  CKCinematicStreamCpnt_Create
//   [x] 0x85458  CKCinematicStreamCpnt_CreateArray
//   [x] 0x855c0  CKCinematicStreamCpnt_Load
//
//   [ ] 0x99b5a0  CKCinematicStreamCpnt_IsKindOfClass  [inline]
//   [ ] 0x99b5c8  CKCinematicStreamCpnt_GetClassType  [inline]
//   [ ] 0x99b5d0  CKCinematicStreamCpnt_GetClassID  [inline]
//   [ ] 0x99b5d8  KStub_Return0_99b5d8  [inline]
//   [ ] 0x99b5e0  KStub_Nop_99b5e0  [inline]
//   [ ] 0x99b5e8  KStub_Nop_99b5e8  [inline]
//   [ ] 0x99b5f0  KStub_Return1_99b5f0  [inline]
//   [ ] 0x99b5f8  KStub_Nop_99b5f8  [inline]
//   [ ] 0x99b600  KStub_Nop_99b600  [inline]
//   [ ] 0x99b608  KStub_Nop_99b608  [inline]
//   [ ] 0x99b610  KStub_Return0_99b610  [inline]
//   [x] 0x99b840  CKCinematicStreamCpnt_Destructor  [inline]  (CKCinematicStreamCpnt.h)
//   [ ] 0x99b968  CKCinematicStreamCpnt_DeletingDestructor  [inline]
//   [x] 0x99baa0  CKCinematicStreamCpnt_ChannelArray_Resize_maybe  [inline]
//   [x] 0x99bd40  CKCinematicStreamCpnt_SetTimeQuantizedToFrames_maybe  [inline]
#include "k2000/components/CKCinematicStreamCpnt.h"

#include <cstdio>
#include <cstring>

#include "k2000/animation/AnimBlendSlot.h"
#include "k2000/cameras/IKCamera.h"
#include "k2000/io/IKFile.h"
#include "k2000/io/KFileSystem.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/logic/CKGameLevel.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/logic/CKSekens.h"
#include "k2000/logic/sound/CKMusicPlayList.h"
#include "k2000/managers/CKSoundManager.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/IKGameStructure.h"
#include "k2000/misc/JobQueue.h"
#include "k2000/services/CKSrvMusic.h"
#include "k2000/services/CKSrvSekensor.h"
#include "k2000/system/CTimeManager.h"
#include "k2000/system/IKTime.h"

SCinematicStreamGlobals g_cinematicStreamFile = {};  // 0x00c5c6d8 (bss)

namespace {

const CVector3 kVectorZero = {0.0f, 0.0f, 0.0f};  // 0x00c50d64

// The engine's minimum time step: 0.1f (TOC -0x6920), or 1 / the fixed rate when the time manager runs at
// a fixed rate (m_properties bit 0).
float MinimumTimeStep() {
    const CTimeManager* manager = g_pEngine->m_timeManager;
    if ((manager->m_properties & 1) == 0) return 0x1.99999ap-4f;
    return 0x1p+0f / static_cast<float>(manager->m_ui8FixedRate);  // fdivs
}

// The frame clock (GameEngineContext +0x48 -> +0x04).
IKTime* FrameClock() { return g_pEngine->m_timeManager->m_pTime; }

// A new key or event block for the Load: the "resize to count" of the K vectors (one element for an empty first
// block, the used count then left alone), the new elements constructed.
template <class T>
void ResizeConstructed(TVector<T, 1>& v, uint32_t count) {
    if (v.m_pBlock == nullptr) {
        if (count == 0) {
            v.m_ui32NbElt = 1;
            v.m_pBlock = static_cast<T*>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(T))));
            return;
        }
        v.m_ui32NbElt = count;
        v.m_pBlock = static_cast<T*>(Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(T))));
        // (the original's "capacity < count" reserve cannot run here)
    } else if (v.m_ui32NbElt < count) {
        uint32_t capacity = count + 1;
        if (capacity == 0) capacity = 1;
        v.m_pBlock = static_cast<T*>(Mem_ReallocAligned16(v.m_pBlock, capacity * static_cast<uint32_t>(sizeof(T))));
        v.m_ui32NbElt = capacity;
    }
    for (uint32_t i = v.m_ui32NbUsedElt; i < count; ++i) v.m_pBlock[i].Construct();
    v.m_ui32NbUsedElt = count;
}

// 0x0099b730 U32Array_Reserve_maybe [inline]: the table sized to `count` words (one for 0, the used count then left
// alone).
void ReserveWords(TVector<uint8_t*, 1>& v, uint32_t count) {
    if (v.m_pBlock == nullptr) {
        if (count == 0) {
            v.m_ui32NbElt = 1;
            v.m_pBlock = static_cast<uint8_t**>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(uint8_t*))));
            return;
        }
        v.m_ui32NbElt = count;
        v.m_pBlock = static_cast<uint8_t**>(Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(uint8_t*))));
    }
    if (v.m_ui32NbElt < count) {
        if (count + 1 == 0) {
            v.m_pBlock = static_cast<uint8_t**>(Mem_ReallocAligned16(v.m_pBlock, static_cast<uint32_t>(sizeof(uint8_t*))));
            v.m_ui32NbElt = 1;
        } else {
            v.m_pBlock = static_cast<uint8_t**>(
                Mem_ReallocAligned16(v.m_pBlock, (count + 1) * static_cast<uint32_t>(sizeof(uint8_t*))));
            v.m_ui32NbElt = count + 1;
        }
    }
    v.m_ui32NbUsedElt = count;
}

// The chunk buffers freed (OperatorDeleteArray each, then the tables), inlined in AllocChunkTables, Stop and
// FreeChunkTables.
void FreeChunkBuffers(TVector<uint8_t*, 1>& buffers, TVector<uint8_t*, 1>& data) {
    const uint32_t count = buffers.m_ui32NbUsedElt;
    for (uint32_t i = 0; i != count; ++i) {
        if (buffers.m_pBlock[i] != nullptr) {
            ::operator delete[](buffers.m_pBlock[i]);  // OperatorDeleteArray
            buffers.m_pBlock[i] = nullptr;
        }
    }
    if (buffers.m_pBlock != nullptr) {
        Mem_FreeAligned16(buffers.m_pBlock);
        buffers.m_pBlock = nullptr;
    }
    buffers.m_pBlock = nullptr;
    buffers.m_ui32NbUsedElt = 0;
    if (data.m_pBlock != nullptr) {
        Mem_FreeAligned16(data.m_pBlock);
        data.m_pBlock = nullptr;
    }
    data.m_ui32NbUsedElt = 0;
    data.m_pBlock = nullptr;
}

// A channel's type object with its state cleared and pointed at the channel (every caller inlines it).
SCinematicStreamTrackType* TypeFor(CKCinematicStreamCpnt::SChannel* channel) {
    SCinematicStreamTrackType* type = &g_cinematicStreamFile.m_aTypes[channel->m_type];
    type->ResetState();
    type->m_pChannel = channel;
    return type;
}

// Local copies of 0x0002f590 Game_GetCurrentLevelNumber_maybe (CKLevel.cpp) and 0x00013e48
// CDefaultGameManager_GetCurrentLevelNumber_maybe (CDefaultGameManager.cpp), as in CKSrvSekensor.cpp.
int32_t GetCurrentLevelNumber() {
    CDefaultGameManager* manager = g_pEngine->m_gameManager;
    if (manager == nullptr) return 0;
    CKGameLevel* level = static_cast<IKGameStructure*>(manager->m_gameStructure)->GetCurrentLevel();
    return level->m_i32StageIndex;
}

// 0x00c4afc8 + 7 * 0x14 (Platform_GetFileTag_maybe 0x1f8518 with 7): the file names' platform tag.
const char kPlatformTag[] = "PS3";

uint32_t WithMediaBit(uint32_t flags) { return (flags >> 11) & 1; }

}  // namespace

// 0x00084ef8 CKCinematicStreamCpnt_ConstructBase_maybe
void CKCinematicStreamCpnt::ConstructBase() {
    m_unk1c = 3;
    m_unkc4 = -1;
    m_d20 = 0.0;  // the double TOC -0x6998
    m_ui32NbFrames = 0;
    m_ui32SegmentWrite = 0;
    m_ui32ChunkWrite = 0;
    m_unkbc = 0;
    m_ui32SegmentRead = 0;
    m_ui32NextKey = 0;
    m_ui32SegmentsRead = 0;
    m_ui32SegmentsPlayed = 0;
    m_d40 = 0.0;
    m_d38 = 0.0;
    m_d30 = 0.0;
    m_d28 = 0.0;
    m_d48 = 0.0;
    m_d58 = 0.0;
    m_d50 = 0.0;
    m_ui32Frame = 0;
    m_ui32FrameInSegment = 0;
    m_unkfc = 0;
    m_unkcc = 0;
    const float step = MinimumTimeStep();
    if (m_unkcc == 1) {
        // Dead (m_unkcc was just cleared): SetTimeQuantizedToFrames(0.98333335f) inlined.
        m_ui32NbFrames = 0x3c;
        m_fTime = 0x1.f77778p-1f;  // 0.98333335f
        if (0x1.f77778p-1f < step) SetTimeQuantizedToFrames(0x1.044444p+0f);  // 1.0166667f
    } else {
        m_fTime = step < 0x1p+0f ? 0x1p+0f : step;
    }
    m_fCameraFar = 0x1.18p+6f;  // 70.0f (TOC 0x428c0000)
    m_unkf8 = 0;
    m_unkdc = 2;
    m_unkd0 = 0.0f;
    m_unke0 = 0;
    m_unke4 = 0;
    m_unkc8 = 0;
    m_pUnkec = nullptr;
    m_pUnkf0 = nullptr;
    // The three channel types' slots (stored by every construction), then KStub_Nop_7f3e0 twice (between the types).
    SCinematicStreamTrackType* types = g_cinematicStreamFile.m_aTypes;
    types[0].m_pfnBeginChunk = CinematicStream_CreateAnimTrackAnimation;      // 0x7fb30
    types[0].m_pfnEndChunk = CinematicStream_DestroyAnimTrackAnimation;       // 0x7fae0
    types[0].m_pfnReset = [](SCinematicStreamTrackType*) {};                  // 0x7f530 KStub_Nop_7f530
    types[0].m_pfnInit = [](SCinematicStreamTrackType*) {};                   // 0x7f538 KStub_Nop_7f538
    types[0].m_pfnKeepActor = CinematicStream_SaveActorMatrix;                // 0x7f540
    types[0].m_pfnGiveBackActor = CinematicStream_AttachActor;                // 0x804b0
    types[0].m_pfnStop = CinematicStream_RestartActorAnimIfInList;            // 0x7f860
    types[0].m_pfnTakeActor = CinematicStream_RestoreActor;                   // 0x7f698
    types[0].m_pfnApplyTime = CinematicStream_ApplyAnimTrackTime;             // 0x80050
    types[0].m_pfnGetBufferSize = CinematicStream_GetFloatBlock9Size;        // 0x7f680
    types[0].m_pfnLoadBuffer = CinematicStream_LoadFloatBlock9;              // 0x7fcb8
    types[0].m_pfnPostLoad = CinematicStream_IsActorSceneLeaf;               // 0x7f4d8
    types[0].m_pfnSaveBuffer = nullptr;  // 0x7fc90 CinematicStream_SaveFloatBlock9_maybe (not called, not ported)
    types[0].m_pfnResolve = CinematicStream_ResolveAnimatedNode;             // 0x7f3e8
    types[0].m_pfnResolve2 = [](IKSerializable*) -> IKSerializable* { return nullptr; };  // 0x99b5d8 KStub_Return0
    types[1].m_pfnBeginChunk = CinematicStream_ResetTrackBufferPtr;          // 0x7e268
    types[1].m_pfnEndChunk = CinematicStream_FreeTrackBuffer;                // 0x7e298
    types[1].m_pfnReset = [](SCinematicStreamTrackType*) {};                 // 0x99b5e0 KStub_Nop
    types[1].m_pfnInit = [](SCinematicStreamTrackType*) {};                  // 0x99b5e8 KStub_Nop
    types[1].m_pfnKeepActor = [](SCinematicStreamTrackType*, uint32_t) -> uint8_t { return 1; };  // 0x99b5f0
    types[1].m_pfnGiveBackActor = CinematicCameraTrack_Release;              // 0x7e878
    types[1].m_pfnStop = [](SCinematicStreamTrackType*, TVector<uint8_t*, 1>*, uint32_t) {};  // 0x99b5f8 KStub_Nop
    types[1].m_pfnTakeActor = [](SCinematicStreamTrackType*, uint32_t) {};  // 0x99b600 KStub_Nop
    types[1].m_pfnApplyTime = CinematicCameraTrack_Update;                   // 0x7e318
    types[1].m_pfnGetBufferSize = CinematicStream_GetNoBufferSize;           // 0x7e290
    types[1].m_pfnLoadBuffer = CinematicStream_LoadNothing;                  // 0x7e258
    types[1].m_pfnPostLoad = [](SCinematicStreamTrackType*) {};              // 0x99b608 KStub_Nop
    types[1].m_pfnSaveBuffer = CinematicStream_SaveNothing;                  // 0x7e260
    types[1].m_pfnResolve = CinematicStream_ResolveCamera;                   // 0x7e1d8
    types[1].m_pfnResolve2 = [](IKSerializable*) -> IKSerializable* { return nullptr; };  // 0x99b610 KStub_Return0
    // Type 2: the thunks 0x99b618 / 0x99b640 / 0x99b668 / 0x99b690 / 0x99b6b8 / 0x99b6e0 / 0x99b708 are the type 0
    // functions; the empty reset and init are KStub_Nop_7f688 / 7f690.
    types[2].m_pfnBeginChunk = CinematicStream_CreateAnimTrackAnimation;     // 0x99b618
    types[2].m_pfnEndChunk = CinematicStream_DestroyAnimTrackAnimation;      // 0x99b640
    types[2].m_pfnReset = [](SCinematicStreamTrackType*) {};                 // 0x7f688
    types[2].m_pfnInit = [](SCinematicStreamTrackType*) {};                  // 0x7f690
    types[2].m_pfnKeepActor = CinematicStream_SaveActorMatrices;             // 0x807b0
    types[2].m_pfnGiveBackActor = CinematicStream_AttachSecondActor;         // 0x80608
    types[2].m_pfnStop = CinematicStream_RestartActorAnimAndClearNodeFlag2000;  // 0x7ff90
    types[2].m_pfnTakeActor = CinematicStream_RestoreSecondActor;            // 0x7fdf0
    types[2].m_pfnApplyTime = CinematicStream_ApplyAnimTrackTime;            // 0x99b668
    types[2].m_pfnGetBufferSize = CinematicStream_GetFloatBlock9Size_Thunk;  // 0x99b708
    types[2].m_pfnLoadBuffer = CinematicStream_LoadFloatBlock9_Thunk;        // 0x99b6b8
    types[2].m_pfnPostLoad = CinematicStream_IsActorSceneLeaf_WithSecond;    // 0x80408
    types[2].m_pfnSaveBuffer = nullptr;  // 0x99b690 (its thunk; not called, not ported)
    types[2].m_pfnResolve = CinematicStream_ResolveAnimatedNode;             // 0x99b6e0
    types[2].m_pfnResolve2 = CinematicStream_ResolveSceneLeaf;               // 0x7fd20
}

// 0x0099baa0 CKCinematicStreamCpnt_ChannelArray_Resize_maybe
void CKCinematicStreamCpnt::ResizeChannels(uint32_t count) {
    TVector<SChannel, 1>& v = m_vChannels;
    if (v.m_pBlock == nullptr) {
        if (count == 0) {
            v.m_ui32NbElt = 1;
            v.m_pBlock = static_cast<SChannel*>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(SChannel))));
            return;  // the used count is left alone
        }
        v.m_ui32NbElt = count;
        v.m_pBlock = static_cast<SChannel*>(Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(SChannel))));
    } else if (v.m_ui32NbElt < count) {
        if (count + 1 == 0) {
            v.m_pBlock = static_cast<SChannel*>(Mem_ReallocAligned16(v.m_pBlock, static_cast<uint32_t>(sizeof(SChannel))));
            v.m_ui32NbElt = 1;
        } else {
            v.m_pBlock = static_cast<SChannel*>(
                Mem_ReallocAligned16(v.m_pBlock, (count + 1) * static_cast<uint32_t>(sizeof(SChannel))));
            v.m_ui32NbElt = count + 1;
        }
    }
    for (uint32_t i = v.m_ui32NbUsedElt; i < count; ++i) {
        SChannel& channel = v.m_pBlock[i];
        channel.m_type = 0xffff;
        channel.m_pBuffer = nullptr;
        channel.m_pUnk04 = nullptr;
        channel.m_pUnk08 = nullptr;
        channel.m_pUnk0c = nullptr;
        channel.m_pMatrix10 = nullptr;
        channel.m_pUnk18 = nullptr;
        channel.m_pUnk1c = nullptr;
        channel.m_pUnk20 = nullptr;
        channel.m_pMatrix24 = nullptr;
        channel.m_v28 = kVectorZero;
        channel.m_unk14 = 0;
    }
    v.m_ui32NbUsedElt = count;
}

// 0x0099bd40 CKCinematicStreamCpnt_SetTimeQuantizedToFrames_maybe (the original unrolls its tail call).
void CKCinematicStreamCpnt::SetTimeQuantizedToFrames(float time) {
    for (;;) {
        const float step = MinimumTimeStep();
        if (m_unkcc != 1) {
            m_fTime = step >= time ? step : time;
            return;
        }
        m_ui32NbFrames = 0;
        float quantised = 0.0f;
        if (!(static_cast<double>(time) <= 0x1.1111111111111p-6)) {  // 1/60 (TOC double)
            uint32_t frames = 1;
            while (static_cast<double>(frames + 1) / 60.0 < static_cast<double>(time)) ++frames;
            m_ui32NbFrames = frames;
            quantised = static_cast<float>(static_cast<double>(frames) / 60.0);
        }
        const uint32_t frames = m_ui32NbFrames;
        m_fTime = quantised;
        m_ui32NbFrames = frames + 1;
        if (quantised >= step) return;
        time = static_cast<float>(static_cast<double>(frames + 2) / 60.0);
    }
}

// 0x000855c0 CKCinematicStreamCpnt_Load
int32_t CKCinematicStreamCpnt::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadS32LE(file, &m_unkc4);
    uint32_t channelCount = 0;
    ReadU32LE(file, &channelCount);
    ReadS32LE(file, &m_unkc8);
    ReadU32LE(file, &m_unke0);
    ReadU32LE(file, &m_unke4);
    ReadS32LE(file, &m_unkcc);
    ReadF32LE(file, &m_fTime);
    ReadS32LE(file, &m_unkdc);
    ReadF32LE(file, &m_unkd0);
    ReadF32LE(file, &m_fCameraFar);
    IKFile_ReadRef(file, &g_cinematicStreamFile.m_pCamera);
    if (g_cinematicStreamFile.m_pCamera != nullptr) {
        ++g_cinematicStreamFile.m_ui32CameraCount;
        IKCamera* camera = static_cast<IKCamera*>(g_cinematicStreamFile.m_pCamera);
        camera->m_Flags &= ~0x40u;
        camera->m_Flags &= ~0x20u;
        camera->m_fFar = m_fCameraFar;
    }
    const uint32_t oldCount = m_vChannels.m_ui32NbUsedElt;
    if (m_vChannels.m_pBlock != nullptr && oldCount != 0) {
        for (uint32_t i = 0; i < oldCount; ++i) m_vChannels.m_pBlock[i].FreeBuffers();
    }
    ResizeChannels(channelCount);
    for (uint32_t i = 0; i < channelCount; ++i) {
        SChannel& channel = m_vChannels.m_pBlock[i];
        IKFile_ReadRef(file, &channel.m_pUnk08);
        IKFile_ReadRef(file, &channel.m_pUnk04);
        IKFile_ReadRef(file, &channel.m_pUnk1c);
        IKFile_ReadRef(file, &channel.m_pUnk18);
        ReadU32LE(file, &channel.m_unk14);
        uint32_t channelType = 0xffff;
        ReadU32LE(file, &channelType);
        channel.m_type = channelType;
        ReadU32LEWords(file, reinterpret_cast<uint32_t*>(&channel.m_v28), 3);
        const SCinematicStreamTrackType& handlers = g_cinematicStreamFile.m_aTypes[channel.m_type];
        channel.AllocBuffer(handlers.m_pfnGetBufferSize());           // slot +0x24
        handlers.m_pfnLoadBuffer(channel.m_pBuffer, file, K_LEVEL_PLATEFORMS);  // slot +0x28
    }
    ReadRaw(file, &m_unkf8, 1);
    uint32_t keyCount = 0;
    ReadU32LE(file, &keyCount);
    ResizeConstructed(m_vKeys, keyCount);
    for (uint32_t i = 0; i < keyCount; ++i) m_vKeys.m_pBlock[i].Load(file, K_LEVEL_PLATEFORMS);
    uint32_t eventCount = 0;
    ReadU32LE(file, &eventCount);
    ResizeConstructed(m_vEvents, eventCount);
    for (uint32_t i = 0; i < eventCount; ++i) m_vEvents.m_pBlock[i].Load(file, K_LEVEL_PLATEFORMS);
    IKFile_ReadRef(file, &m_pUnkec);
    IKFile_ReadRef(file, &m_pUnkf0);
    // Each key points at the event with its id.
    const int32_t events = static_cast<int32_t>(m_vEvents.m_ui32NbUsedElt);
    const int32_t keys = static_cast<int32_t>(m_vKeys.m_ui32NbUsedElt);
    for (int32_t e = 0; e < events; ++e) {
        SEvent& event = m_vEvents.m_pBlock[e];
        for (int32_t k = 0; k < keys; ++k) {
            SKey& key = m_vKeys.m_pBlock[k];
            if (key.m_id != event.m_id) continue;
            event.m_id = key.m_id;
            key.m_pEvent = &event;
        }
    }
    // The time step: at least the engine's minimum step; in the 60 fps mode a whole number of frames.
    const float time = m_fTime;
    const float step = MinimumTimeStep();
    if (m_unkcc == 1) {
        float quantised = 0.0f;
        m_ui32NbFrames = 0;
        if (!(static_cast<double>(time) <= 0x1.1111111111111p-6)) {
            uint32_t frames = 1;
            while (static_cast<double>(frames + 1) / 60.0 < static_cast<double>(time)) ++frames;
            m_ui32NbFrames = frames;
            quantised = static_cast<float>(static_cast<double>(frames) / 60.0);
        }
        const uint32_t frames = m_ui32NbFrames;
        m_fTime = quantised;
        m_ui32NbFrames = frames + 1;
        if (!(quantised >= step)) SetTimeQuantizedToFrames(static_cast<float>(static_cast<double>(frames + 2) / 60.0));
    } else if (step >= time) {
        m_fTime = step;
    } else {
        m_fTime = time;
    }
    return 1;
}

// 0x00081a38 CKCinematicStreamCpnt_PostLoad (the type is not tested).
int32_t CKCinematicStreamCpnt::PostLoad(int32_t /*type*/) {
    const uint32_t count = m_vChannels.m_ui32NbUsedElt;
    for (uint32_t i = 0; i != count; ++i) {
        SCinematicStreamTrackType* type = TypeFor(&m_vChannels.m_pBlock[i]);
        type->m_pfnPostLoad(type);  // slot +0x2c
    }
    return 1;
}

// 0x00081ca0 CKCinematicStreamCpnt_InitChannels_maybe: ResetChannels' loop with the type's init handler (slot +0x0c:
// KStub_Nop_7f538 / 0x99b5e8 / 0x7f690, empty for all three types) instead of its reset handler. The count is read once.
void CKCinematicStreamCpnt::InitChannels() {
    const uint32_t count = m_vChannels.m_ui32NbUsedElt;
    for (uint32_t i = 0; i != count; ++i) {
        SCinematicStreamTrackType* type = TypeFor(&m_vChannels.m_pBlock[i]);
        type->m_pfnInit(type);
    }
}

// 0x00081db8 CKCinematicStreamCpnt_ResetChannels_maybe. The channel's type indexes the three type objects (the
// original does not range-check it).
void CKCinematicStreamCpnt::ResetChannels() {
    for (uint32_t i = 0; i < m_vChannels.m_ui32NbUsedElt; ++i) {
        SCinematicStreamTrackType* type = TypeFor(&m_vChannels.m_pBlock[i]);
        type->m_pfnReset(type);  // KStub_Nop_7f530 / 0x99b5e0 / 0x7f688
    }
}

// 0x00081130 CKCinematicStreamCpnt_GetChannelMarkList_maybe
IKSerializable* CKCinematicStreamCpnt::GetChannelMarkList(int32_t index) {
    if (index < 0 || index >= static_cast<int32_t>(m_vChannels.m_ui32NbUsedElt)) return nullptr;
    const void* buffer = m_vChannels.m_pBlock[index].m_pBuffer;
    if (buffer == nullptr) return nullptr;
    return static_cast<const AnimFloatBlock9*>(buffer)->m_pUnk20;
}

// 0x00081980 CKCinematicStreamCpnt_BuildStreamPath_maybe (FormatString, the TOC string -0x6960).
void CKCinematicStreamCpnt::BuildStreamPath(char* path) {
    const char* root = g_pEngine->m_fileSystem->m_dataRoot;  // KFileSystem_GetDataRoot 0x48fa0
    std::snprintf(path, 0x108, "%sLVL%03d/STREAMS/%s%d.KCS", root, GetCurrentLevelNumber(), kPlatformTag, m_unkc4);
    KFileSystem_ConvertBackslashes(g_pEngine->m_fileSystem, path);
}

// 0x00081400 CKCinematicStreamCpnt_CloseStream_maybe
void CKCinematicStreamCpnt::CloseStream() {
    if (m_unk1c == 3) return;
    CinematicStreamFile_Close(&g_cinematicStreamFile.m_file, this);
    m_unk1c = 3;
    m_unkfc &= 0xfffffbffu;
}

// 0x000829d0 CKCinematicStreamCpnt_ReopenStream_maybe
uint8_t CKCinematicStreamCpnt::ReopenStream(const char* path) {
    CloseStream();
    m_unk1c = 1;
    return CinematicStreamFile_Open(&g_cinematicStreamFile.m_file, path, this);
}

// 0x000843c0 CKCinematicStreamCpnt_AllocChunkTables_maybe (the data root it is passed is not used).
void CKCinematicStreamCpnt::AllocChunkTables(float segmentTime, uint32_t channelCount, uint32_t segmentCount) {
    m_fTime = segmentTime;
    m_unkdc = static_cast<int32_t>(segmentCount);
    // The segment states, zeroed (an empty first block keeps its used count).
    TVector<uint32_t, 1>& states = m_vSegmentStates;
    if (states.m_pBlock == nullptr && segmentCount == 0) {
        states.m_ui32NbElt = 1;
        states.m_pBlock = static_cast<uint32_t*>(Mem_AllocAligned16(4));
    } else {
        if (states.m_pBlock == nullptr) {
            states.m_ui32NbElt = segmentCount;
            states.m_pBlock = static_cast<uint32_t*>(Mem_AllocAligned16(segmentCount << 2));
        } else if (states.m_ui32NbElt < segmentCount) {
            const uint32_t capacity = segmentCount + 1 == 0 ? 1 : segmentCount + 1;
            states.m_pBlock = static_cast<uint32_t*>(Mem_ReallocAligned16(states.m_pBlock, capacity << 2));
            states.m_ui32NbElt = capacity;
        }
        states.m_ui32NbUsedElt = segmentCount;
    }
    std::memset(states.m_pBlock, 0, static_cast<size_t>(m_unkdc) << 2);
    // The chunk table: one entry per channel and segment.
    m_unke8 = channelCount * static_cast<uint32_t>(m_unkdc);
    ResizeConstructed(m_vChunks, m_unke8);
    // The chunk buffers of an earlier stream freed, the two tables made again and emptied.
    FreeChunkBuffers(m_vChunkBuffers, m_vChunkData);
    ReserveWords(m_vChunkBuffers, m_unke8);
    ReserveWords(m_vChunkData, m_unke8);
    for (uint32_t i = 0; i < m_unke8; ++i) {
        m_vChunkBuffers.m_pBlock[i] = nullptr;
        m_vChunkData.m_pBlock[i] = nullptr;
    }
}

// 0x00084860 CKCinematicStreamCpnt_FreeChunkTables_maybe
void CKCinematicStreamCpnt::FreeChunkTables() {
    if (m_vSegmentStates.m_pBlock != nullptr) {
        Mem_FreeAligned16(m_vSegmentStates.m_pBlock);
        m_vSegmentStates.m_pBlock = nullptr;
    }
    m_vSegmentStates.m_ui32NbUsedElt = 0;
    m_vSegmentStates.m_pBlock = nullptr;
    if (m_vChunks.m_pBlock != nullptr) Mem_FreeAligned16(m_vChunks.m_pBlock);
    m_vChunks.m_ui32NbUsedElt = 0;
    m_vChunks.m_pBlock = nullptr;
    if (m_vKeys.m_pBlock != nullptr) Mem_FreeAligned16(m_vKeys.m_pBlock);
    m_vKeys.m_ui32NbUsedElt = 0;
    m_vKeys.m_pBlock = nullptr;
    if (m_vEvents.m_pBlock != nullptr) Mem_FreeAligned16(m_vEvents.m_pBlock);
    m_vEvents.m_ui32NbUsedElt = 0;
    m_vEvents.m_pBlock = nullptr;
    const uint32_t channels = m_vChannels.m_ui32NbUsedElt;
    if (m_vChannels.m_pBlock != nullptr && channels != 0) {
        for (uint32_t i = 0; i != channels; ++i) m_vChannels.m_pBlock[i].FreeBuffers();
    }
    FreeChunkBuffers(m_vChunkBuffers, m_vChunkData);
}

// 0x00084a60 CKCinematicStreamCpnt_OpenStreamFile_maybe
uint8_t CKCinematicStreamCpnt::OpenStreamFile() {
    char path[0x108];
    BuildStreamPath(path);  // inlined
    AllocChunkTables(m_fTime, m_vChannels.m_ui32NbUsedElt, static_cast<uint32_t>(m_unkdc));
    CloseStream();  // inlined
    m_unk1c = 1;
    if (CinematicStreamFile_Open(&g_cinematicStreamFile.m_file, path, this) == 0) return 0;
    const uint32_t count = m_vChannels.m_ui32NbUsedElt;
    for (uint32_t i = 0; i != count; ++i) {
        SCinematicStreamTrackType* type = TypeFor(&m_vChannels.m_pBlock[i]);
        type->m_pfnKeepActor(type, WithMediaBit(m_unkfc));  // slot +0x10
    }
    if (g_cinematicStreamFile.m_pCamera != nullptr) {
        static_cast<IKCamera*>(g_cinematicStreamFile.m_pCamera)->m_fFar = m_fCameraFar;
    }
    return 1;
}

// 0x00084ca8 CKCinematicStreamCpnt_StartStream_maybe
uint8_t CKCinematicStreamCpnt::StartStream(uint8_t withMedia) {
    if (g_cinematicStreamFile.m_bRunning != 0) return 0;
    m_d58 = 0.0;
    m_unkfc = 0;
    m_d50 = 0.0;
    m_ui32FrameInSegment = 0;
    m_ui32SegmentWrite = 0;
    m_ui32ChunkWrite = 0;
    m_unkbc = 0;
    m_ui32SegmentRead = 0;
    m_ui32NextKey = 0;
    m_ui32SegmentsRead = 0;
    m_ui32SegmentsPlayed = 0;
    m_d40 = 0.0;
    m_d38 = 0.0;
    m_d30 = 0.0;
    m_d28 = 0.0;
    m_d48 = 0.0;
    m_ui32Frame = 0;
    m_d20 = 0.0;
    // Bit 11 = withMedia (rlwinm 11, bits 11..18 of the byte), bit 6 and bit 7 set (each a one-bit insert).
    m_unkfc = (m_unkfc & ~0x800u) | ((static_cast<uint32_t>(withMedia) << 11) & 0x7f800u);
    m_unkfc = (m_unkfc & ~0x40u) | 0x40u;
    m_unkfc = (m_unkfc & ~0x80u) | 0x80u;
    g_cinematicStreamFile.m_bRunning = 1;
    m_d50 = static_cast<double>(FrameClock()->m_afCurrentTime[IKTime::FIXED_GAME_TIME]);
    m_d58 = 0.0;
    if (OpenStreamFile() == 0) return 0;
    if ((m_unkfc & 0x800) != 0 && m_pUnkf0 != nullptr) {
        CKSekens* sekens = static_cast<CKSekens*>(m_pUnkf0);
        sekens->m_flags &= ~0x40u;
        sekens->m_flags = (sekens->m_flags & ~0x2000u) | 0x2000u;
        sekens->SetStreamStartPaused(1);  // 0x001f4148
        static_cast<CKSrvSekensor*>(g_pEngine->m_srvSekensor)->RequestSekens(sekens);
    }
    if ((m_unkfc & 0x800) != 0 && m_pUnkec != nullptr) {
        CKMusicPlayList* playList = static_cast<CKMusicPlayList*>(m_pUnkec);
        CKSrvMusic* music = static_cast<CKSrvMusic*>(g_pEngine->m_srvMusic);
        playList->m_unk35 = static_cast<uint8_t>(music->m_ui8NbPriority - 1);
        playList->m_unk40 = static_cast<uint8_t>((playList->m_unk40 & ~2u) | 2u);
        playList->m_unk40 = static_cast<uint8_t>((playList->m_unk40 & ~1u) | 1u);
        music->RequestTrack(playList, 0);
    }
    return 1;
}

// 0x00082290 CKCinematicStreamCpnt_ReadNextChunk_maybe
uint8_t CKCinematicStreamCpnt::ReadNextChunk() {
    m_unk1c = 6;
    m_vSegmentStates.m_pBlock[m_ui32SegmentWrite] = 3;
    SChunk& chunk = m_vChunks.m_pBlock[m_ui32ChunkWrite];
    chunk.m_ui32State = 3;
    const uint32_t size = chunk.m_ui32Size;
    if (size == 0) return 1;
    uint32_t index = m_ui32ChunkWrite;
    if (m_vChunkBuffers.m_pBlock[index] != nullptr) {
        ::operator delete[](m_vChunkBuffers.m_pBlock[index]);  // OperatorDeleteArray
        m_vChunkBuffers.m_pBlock[m_ui32ChunkWrite] = nullptr;
        index = m_ui32ChunkWrite;
    }
    uint8_t* buffer = static_cast<uint8_t*>(::operator new[](size + 0x40));  // OperatorNewArray
    m_vChunkBuffers.m_pBlock[index] = buffer;
    m_vChunkData.m_pBlock[m_ui32ChunkWrite] =
        reinterpret_cast<uint8_t*>((reinterpret_cast<uintptr_t>(m_vChunkBuffers.m_pBlock[m_ui32ChunkWrite]) + 0x3f) &
                                   ~static_cast<uintptr_t>(0x3f));
    if (g_cinematicStreamFile.m_file.m_bBusy == 0) {
        m_unkbc = size;
        CinematicStreamFile_RequestRead(&g_cinematicStreamFile.m_file, m_vChunkData.m_pBlock[m_ui32ChunkWrite], size,
                                        this);
    }
    return 1;
}

// 0x00082ec0 CKCinematicStreamCpnt_DispatchChunk_maybe
uint8_t CKCinematicStreamCpnt::DispatchChunk() {
    const uint32_t index = m_ui32ChunkWrite;
    const uint32_t channels = m_vChannels.m_ui32NbUsedElt;
    SChunk* chunk = &m_vChunks.m_pBlock[index];
    chunk->m_pData = nullptr;
    if (chunk->m_ui32HasData != 0) {
        SChannel* channel = &m_vChannels.m_pBlock[index % channels];  // divwu
        // DOTD (platform, not in the original): the body read is the PS3 image of the type's data; its native image
        // replaces it in the two buffer tables (CinematicStream_ConvertChunkBody).
        uint8_t* raw = nullptr;
        uint8_t* converted = nullptr;
        if (chunk->m_ui32Size != 0) {
            converted = CinematicStream_ConvertChunkBody(channel->m_type, m_vChunkData.m_pBlock[index],
                                                         chunk->m_ui32Size, &raw);
        }
        if (converted != nullptr) {
            ::operator delete[](m_vChunkBuffers.m_pBlock[index]);
            m_vChunkBuffers.m_pBlock[index] = raw;
            m_vChunkData.m_pBlock[index] = converted;
        }
        uint8_t* data = m_vChunkData.m_pBlock[index];
        SCinematicStreamTrackType* type = TypeFor(channel);
        type->m_fSegmentTime = m_fTime;
        uint8_t* chunkData = nullptr;
        if (chunk->m_ui32HasData != 0) chunkData = m_vChunkData.m_pBlock[m_ui32ChunkWrite];
        chunk->m_pData = chunkData;
        type->m_pChunk = chunk;
        type->m_pfnBeginChunk(type, data);  // slot +0x00
    }
    m_unk1c = 2;
    m_vChunks.m_pBlock[m_ui32ChunkWrite].m_ui32State = 5;
    const uint32_t next = (m_ui32ChunkWrite + 1) % m_unke8;  // divwu
    m_ui32ChunkWrite = next;
    if (next == next / m_vChannels.m_ui32NbUsedElt * m_vChannels.m_ui32NbUsedElt) {
        // A whole segment is read.
        m_vSegmentStates.m_pBlock[m_ui32SegmentWrite] = 5;
        ++m_ui32SegmentsRead;
        m_unkfc = (m_unkfc & ~0x10u) | 0x10u;
        const uint32_t flags = m_unkfc;
        if ((flags & 0x100) == 0 && m_ui32SegmentsRead == 1) {
            m_unkfc = (flags & ~0x100u) | 0x100u;
            m_d38 = 0.0;
            m_ui32FrameInSegment = 0;
            m_d30 = 0.0;
            m_d40 = 0.0;
            m_d28 = 0.0;
            m_ui32Frame = 0;
        }
        m_ui32SegmentWrite = (m_ui32SegmentWrite + 1) % static_cast<uint32_t>(m_unkdc);
    }
    return 1;
}

// 0x000826d8 CKCinematicStreamCpnt_UpdateSyncedMedia_maybe
uint8_t CKCinematicStreamCpnt::UpdateSyncedMedia() {
    const double now = static_cast<double>(FrameClock()->m_afCurrentTime[IKTime::FIXED_GAME_TIME]);
    if ((m_unkfc & 0x200) != 0) return static_cast<uint8_t>(((m_unkfc >> 14) & 1) ^ 1);
    if ((m_unkfc & 0x20) != 0) return 0;
    if ((m_unkfc & 0x800) != 0) {
        uint32_t voice = 1;
        if (m_pUnkf0 != nullptr) voice = static_cast<CKSekens*>(m_pUnkf0)->IsStreamVoiceActive();  // 0x001f4ba8
        m_unkfc = (m_unkfc & 0xfffffffeu) | voice;
    } else {
        m_unkfc = (m_unkfc & 0xfffffffeu) | 1;
    }
    if ((m_unkfc & 0x800) != 0) {
        uint32_t ready = 4;
        if (m_pUnkec != nullptr) {
            ready = (static_cast<uint32_t>(static_cast<CKMusicPlayList*>(m_pUnkec)->IsCurrentTrackReady()) << 2) & 0x3fc;
        }
        m_unkfc = (m_unkfc & ~4u) | ready;
    } else {
        m_unkfc = (m_unkfc & ~4u) | 4;
    }
    const double elapsed = now - m_d50;
    if (elapsed < 0.0) {
        m_d58 = 0.0;
    } else {
        m_d58 = elapsed;
        if (elapsed >= static_cast<double>(15.0f)) {  // TOC -0x6948
            // Fifteen seconds: what is not ready is stopped.
            if ((m_unkfc & 4) == 0) {
                m_unkfc = (m_unkfc & ~8u) | 8;
                if ((m_unkfc & 0x800) != 0 && m_pUnkec != nullptr) {
                    static_cast<CKSrvMusic*>(g_pEngine->m_srvMusic)->StopPlayList(static_cast<CKMusicPlayList*>(m_pUnkec));
                }
            }
            if ((m_unkfc & 1) == 0) {
                m_unkfc = (m_unkfc & ~2u) | 2;
                if ((m_unkfc & 0x800) != 0 && m_pUnkf0 != nullptr) {
                    static_cast<CKSrvSekensor*>(g_pEngine->m_srvSekensor)->StopSekens(static_cast<CKSekens*>(m_pUnkf0));
                }
            }
            if ((m_unkfc & 0x10) == 0) m_unkfc = (m_unkfc & ~0x20u) | 0x20;
            if ((m_unkfc & 0x10) == 0) return 0;
            m_unkfc = (m_unkfc & ~0x200u) | 0x200;
            m_unkfc = (m_unkfc & ~0x400u) | 0x400;
            return 1;
        }
    }
    const uint32_t flags = m_unkfc;
    if ((flags & 1) == 0 || (flags & 4) == 0 || (flags & 0x10) == 0) return 1;
    m_unkfc = (m_unkfc & ~0x200u) | 0x200;
    m_unkfc = (m_unkfc & ~0x400u) | 0x400;
    return 1;
}

// 0x00083f18 CKCinematicStreamCpnt_UpdateStream_maybe
uint8_t CKCinematicStreamCpnt::UpdateStream(IKTime* clock) {
    CinematicStreamFile_PumpAsync();  // DOTD (platform): the RtFS callbacks due by now (CinematicStreamFile.cpp)
    if ((m_unkfc & 0x40) == 0 || (m_unkfc & 0x80) == 0 || g_cinematicStreamFile.m_bRunning == 0) return 0;
    SCinematicStreamFile* file = &g_cinematicStreamFile.m_file;
    const double start = clock->KGetExactTime();  // vt+0x08
    for (;;) {
        int32_t state = m_unk1c;
        if (static_cast<uint32_t>(state) <= 1 || state == 3) {
            if (file->m_bOpened == 0) break;
            state = 2;
            m_unk1c = 2;
        }
        if (state == 2) {
            if (m_ui32SegmentsRead >= static_cast<uint32_t>(m_unkc8)) {
                m_unk1c = 0;
                break;
            }
            const uint32_t segmentState = m_vSegmentStates.m_pBlock[m_ui32SegmentWrite];
            if (segmentState != 0 && segmentState != 3) break;
            SChunk* chunk = &m_vChunks.m_pBlock[m_ui32ChunkWrite];
            if (chunk->m_ui32State != 0) break;
            m_unk1c = 4;
            m_vSegmentStates.m_pBlock[m_ui32SegmentWrite] = 3;
            m_vChunks.m_pBlock[m_ui32ChunkWrite].m_ui32State = 3;
            if (file->m_bBusy == 0) {
                m_unkbc = 8;
                CinematicStreamFile_RequestRead(file, chunk, 8, this);  // the chunk header into the entry
            }
            state = m_unk1c;
        }
        if (state == 4) {
            if (file->m_bBusy != 0 || file->m_bDone == 0) break;
            file->m_bDone = 0;
            file->m_bBusy = 0;
            m_unk1c = 5;
            m_vSegmentStates.m_pBlock[m_ui32SegmentWrite] = 3;
            SChunk& chunk = m_vChunks.m_pBlock[m_ui32ChunkWrite];
            chunk.m_ui32State = 3;
            // DOTD (platform, not in the original): the header's two words are big-endian on disc (the PS3 reads them
            // as they are).
            chunk.m_ui32Size = CinematicStream_FromBigEndian(chunk.m_ui32Size);
            chunk.m_ui32HasData = CinematicStream_FromBigEndian(chunk.m_ui32HasData);
            state = m_unk1c;
        }
        if (state == 5) {
            if (ReadNextChunk() == 0) break;
            state = m_unk1c;
        }
        if (state == 6) {
            SChunk* chunk;
            if (file->m_bBusy == 0 && file->m_bDone != 0) {
                file->m_bDone = 0;
                file->m_bBusy = 0;
                chunk = &m_vChunks.m_pBlock[m_ui32ChunkWrite];
            } else {
                chunk = &m_vChunks.m_pBlock[m_ui32ChunkWrite];
                if (chunk->m_ui32Size != 0) break;
            }
            m_unk1c = 7;
            chunk->m_ui32State = 4;
            state = m_unk1c;
        }
        if (state == 7 && DispatchChunk() == 0) break;
        // 0.5 ms of reading per call (TOC double -0x6928).
        if (clock->KGetExactTime() - start > 0x1.0624dd2f1a9fcp-11) break;
    }
    if (UpdateSyncedMedia() == 0) return 0;
    uint32_t over = 0;
    if (m_unk1c == 0) over = m_ui32SegmentsPlayed == static_cast<uint32_t>(m_unkc8) ? 1u : 0u;
    return static_cast<uint8_t>(over ^ 1);
}

// 0x00084308 CKCinematicStreamCpnt_StreamReadyJobCallback_maybe
uint8_t CKCinematicStreamCpnt::StreamReadyJobCallback(void* data, int32_t /*id*/, void* /*user*/) {
    CKCinematicStreamCpnt* stream = static_cast<CKCinematicStreamCpnt*>(data);
    stream->UpdateStream(FrameClock());
    uint32_t flags = stream->m_unkfc;
    if ((flags & 0x10) != 0) {
        const double now = static_cast<double>(FrameClock()->m_afCurrentTime[IKTime::SYSTEM_TIME]);
        if (now - stream->m_d20 < static_cast<double>(2.0f)) return 0;  // TOC -0x6934
        stream->m_d20 = 0.0;
        flags = (flags & ~0x400u) | 0x400u;
        flags = (flags & ~0x10000u) | 0x10000u;
        stream->m_unkfc = flags;
    }
    return static_cast<uint8_t>((flags >> 10) & 1);
}

// 0x00083268 CKCinematicStreamCpnt_StepSegmentStateMachine_maybe (the original recurses through itself).
uint8_t CKCinematicStreamCpnt::StepSegmentStateMachine(float dt) {
    const uint32_t flags = m_unkfc;
    if ((flags & 0x40) == 0 || g_cinematicStreamFile.m_bRunning == 0 || FrameClock()->m_eCurrentState != IKTime::RUNNING ||
        (flags & 0x80) == 0 || (flags & 0x200) == 0 || (flags & 0x400) == 0) {
        return 0;
    }
    const uint32_t frameRate = m_unkcc == 1 ? 0x3c : 0;
    uint32_t segment = m_ui32SegmentRead;
    const uint32_t state = m_vSegmentStates.m_pBlock[segment];
    if (state > 5) return 0;
    uint8_t first;  // r22
    switch (state) {  // jump table 0x833a4
        case 0:
            if (m_ui32SegmentsPlayed == static_cast<uint32_t>(m_unkc8)) return 0;
            [[fallthrough]];
        case 3:
        case 4: {
            // The segment is not read yet: the game waits on the job queue until the stream is ready again.
            m_unkfc &= 0xfffffbefu;
            m_d20 = static_cast<double>(FrameClock()->m_afCurrentTime[IKTime::SYSTEM_TIME]);
            g_pEngine->m_jobQueue->PostAndWait(0xcb, 2, this, &CKCinematicStreamCpnt::StreamReadyJobCallback, nullptr);
            return 0;
        }
        case 1:
            first = 0;
            break;
        case 2:
            ++m_ui32SegmentsPlayed;
            m_ui32SegmentRead = (segment + 1) % static_cast<uint32_t>(m_unkdc);
            return StepSegmentStateMachine(dt);
        default: {  // 5: the segment begins; the previous one is free again
            int32_t previous = static_cast<int32_t>(segment) - 1;
            if (previous < 0) previous = m_unkdc - 1;
            uint32_t* previousState = &m_vSegmentStates.m_pBlock[previous];
            if (*previousState == 2) {
                *previousState = 0;
                const uint32_t channels = m_vChannels.m_ui32NbUsedElt;
                const uint32_t begin = static_cast<uint32_t>(previous) * channels;
                for (uint32_t i = begin; i < begin + channels; ++i) m_vChunks.m_pBlock[i].m_ui32State = 0;
                segment = m_ui32SegmentRead;
            }
            first = 1;
            break;
        }
    }
    bool play = !(static_cast<float>(m_d30) > m_unkd0);
    if (play) {
        if (frameRate == 0) {
            // !(the segment's end < the stream time): blt skips.
            play = !(static_cast<float>(m_ui32SegmentsPlayed + 1) * m_fTime < m_d30);
        } else {
            play = m_ui32FrameInSegment < m_ui32NbFrames;
        }
    }
    if (play) {
        const uint32_t channels = m_vChannels.m_ui32NbUsedElt;
        const uint32_t begin = channels * segment;
        uint32_t allDone = 1;
        for (uint32_t i = begin; i < begin + channels; ++i) {
            SChannel* channel = &m_vChannels.m_pBlock[i % m_vChannels.m_ui32NbUsedElt];  // divwu
            SCinematicStreamTrackType* type = &g_cinematicStreamFile.m_aTypes[channel->m_type];
            type->m_fDt = 0.0f;
            type->m_fSegmentTime = 0.0f;
            type->m_dStreamTime = 0.0;
            type->m_dSegmentTime = 0.0;
            type->m_ui32Frame = 0;
            type->m_ui32FrameInSegment = 0;
            type->m_ui32FrameRate = 0;
            type->m_bFirst = 0;
            type->m_bPlaying = 0;
            type->m_bStopped = 0;
            type->m_pChannel = nullptr;
            type->m_pChunk = nullptr;
            type->m_fSegmentTime = m_fTime;
            type->m_fDt = dt;
            type->m_dStreamTime = m_d30;
            type->m_dSegmentTime = m_d28;
            type->m_ui32Frame = m_ui32Frame;
            type->m_ui32FrameInSegment = m_ui32FrameInSegment;
            type->m_bFirst = first;
            type->m_bPlaying = 1;
            type->m_bStopped = 0;
            type->m_ui32FrameRate = m_unkcc == 1 ? 0x3c : 0;
            type->m_pChannel = channel;
            type->m_pChunk = &m_vChunks.m_pBlock[i];
            const uint8_t going = type->m_pfnApplyTime(type);  // slot +0x20
            if (going != 0) allDone = 0;  // ((going & 0xff) - 1) >> 31 & allDone
        }
        if (allDone == 0) {
            const uint32_t current = m_ui32SegmentRead;
            m_vSegmentStates.m_pBlock[current] = 1;
            const uint32_t from = current * m_vChannels.m_ui32NbUsedElt;
            for (uint32_t i = from; i < from + m_vChannels.m_ui32NbUsedElt; ++i) m_vChunks.m_pBlock[i].m_ui32State = 1;
            return 1;
        }
        segment = m_ui32SegmentRead;
    }
    // The segment is over (or its time passed).
    uint32_t* segmentState = &m_vSegmentStates.m_pBlock[segment];
    if (*segmentState != 5 && *segmentState != 1) return 1;
    *segmentState = 2;
    const uint32_t from = segment * m_vChannels.m_ui32NbUsedElt;
    for (uint32_t i = from; i < from + m_vChannels.m_ui32NbUsedElt; ++i) m_vChunks.m_pBlock[i].m_ui32State = 2;
    if (frameRate != 0) {
        const int32_t left = static_cast<int32_t>(m_ui32FrameInSegment - m_ui32NbFrames);
        m_ui32FrameInSegment = static_cast<uint32_t>(left & (~left >> 31));
    } else {
        const double left = m_d28 - static_cast<double>(m_fTime);
        m_d28 = left < 0.0 ? 0.0 : left;
    }
    return StepSegmentStateMachine(0.0f);  // TOC -0x693c
}

// 0x00083820 CKCinematicStreamCpnt_Update_maybe
uint8_t CKCinematicStreamCpnt::Update(IKTime* time) {
    const uint32_t frameRate = m_unkcc == 1 ? 0x3c : 0;
    const double dt = static_cast<double>(time->m_afDeltaTime[IKTime::FIXED_GAME_TIME]);  // +0x20
    double streamTime;
    if ((m_unkfc & 0x100) != 0) {
        // The first update of the stream: the media started (paused until now), every actor taken over.
        if ((m_unkfc & 0x800) != 0) g_pEngine->m_soundManager->SaveAndMuteVolume(0);
        m_d48 = 0.0;
        m_d28 = 0.0;
        m_d40 = 0.0;
        m_d38 = 0.0;
        m_d30 = 0.0;
        if ((m_unkfc & 0x800) != 0 && m_pUnkf0 != nullptr && (m_unkfc & 1) != 0 && (m_unkfc & 2) == 0) {
            m_unkfc = (m_unkfc & ~0x1000u) | 0x1000u;
            static_cast<CKSekens*>(m_pUnkf0)->StartPausedStream();  // 0x001f4c00
        }
        if ((m_unkfc & 0x800) != 0 && m_pUnkec != nullptr && (m_unkfc & 4) != 0 && (m_unkfc & 8) == 0) {
            m_unkfc = (m_unkfc & ~0x2000u) | 0x2000u;
            static_cast<CKMusicPlayList*>(m_pUnkec)->StartPausedTrack();  // 0x00211fa8
        }
        m_unkfc &= ~0x100u;
        m_ui32FrameInSegment = 0;
        m_ui32Frame = 0;
        const uint32_t count = m_vChannels.m_ui32NbUsedElt;
        for (uint32_t i = 0; i != count; ++i) {
            SCinematicStreamTrackType* type = TypeFor(&m_vChannels.m_pBlock[i]);
            type->m_pfnKeepActor(type, WithMediaBit(m_unkfc));  // slot +0x10
            type = TypeFor(&m_vChannels.m_pBlock[i]);
            type->m_pfnTakeActor(type, m_unkf8);  // slot +0x1c
        }
        streamTime = m_d30;
    } else {
        m_d48 = dt + m_d48;
        if (m_pUnkf0 == nullptr) {
            // The stream follows the frame time, at most 0.9 segment per frame.
            const double limit = static_cast<double>(m_fTime * 0x1.ccccccp-1f);  // fmuls 0.9f (TOC -0x6938)
            const double step = dt > limit ? limit : dt;
            m_d30 = step + m_d30;
            m_d28 = step + m_d28;
        } else {
            // The stream follows the sekens' speech while its position is believable.
            const double position = static_cast<double>(static_cast<CKSekens*>(m_pUnkf0)->PollStreamPlaybackPosition());
            if ((m_unkfc & 0x8000) == 0) {
                if (!(m_d30 > 0.0)) {
                    if (position < static_cast<double>(0.0f) ||
                        static_cast<double>(m_fTime * 0x1.ccccccp-1f) < position) {
                        m_unkfc = (m_unkfc & ~0x8000u) | 0x8000u;
                        m_d30 = 0.0;
                    } else {
                        m_d30 = position;
                    }
                    if (!(m_d48 <= static_cast<double>(2.0f))) {  // ble
                        m_d48 = 0.0;
                        m_unkfc = (m_unkfc & ~0x8000u) | 0x8000u;
                    }
                } else {
                    const double ahead = position - m_d30;
                    if (ahead < 0.0 || static_cast<double>(m_fTime * 0x1.ccccccp-1f) < ahead) {
                        m_unkfc = (m_unkfc & ~0x8000u) | 0x8000u;
                    } else {
                        m_d30 = position;
                    }
                }
            }
            double now;
            if ((m_unkfc & 0x8000) == 0) {
                now = m_d30;
            } else {
                const double limit = static_cast<double>(m_fTime * 0x1.ccccccp-1f);
                const double step = dt > limit ? limit : dt;
                now = step + m_d30;
                m_d30 = now;
            }
            m_d28 = m_d28 + (now - m_d40);
        }
        if ((m_unkfc & 0x10000) != 0) {
            // Back from the job wait: the time it took does not count.
            m_unkfc &= ~0x10000u;
            m_d30 = m_d40;
            m_d28 = m_d38;
        }
        streamTime = m_d30;
        if (frameRate != 0) {
            const float rate = static_cast<float>(frameRate);
            uint32_t next = m_ui32Frame + 1;
            while (static_cast<double>(static_cast<float>(next) / rate) <= streamTime) {
                m_ui32Frame = next;
                ++next;
                ++m_ui32FrameInSegment;
            }
        }
    }
    m_d40 = streamTime;
    StepSegmentStateMachine(time->m_afDeltaTime[IKTime::FIXED_GAME_TIME]);
    m_d38 = m_d28;
    // The keys the stream time reached: their events' triggers.
    const uint32_t keys = m_vKeys.m_ui32NbUsedElt;
    for (uint32_t k = m_ui32NextKey; k < keys; ++k) {
        const SKey& key = m_vKeys.m_pBlock[k];
        if (!(static_cast<double>(key.m_fTime) <= m_d30)) break;  // fcmpu, cror lt|eq
        if (key.m_pEvent != nullptr) QueueTriggerSignals(&key.m_pEvent->m_tsTriggers);  // 0x00236338 (this as sender)
        ++m_ui32NextKey;
    }
    const bool readDone = m_unk1c == 0;
    if (readDone && m_ui32SegmentsPlayed == static_cast<uint32_t>(m_unkc8)) return 0;
    if ((m_unkfc & 0x800) == 0) {
        if (!(m_d48 <= static_cast<double>(m_unkd0))) {  // ble
            m_unkfc = (m_unkfc & ~0x4000u) | 0x4000u;
            return 0;
        }
    } else if (!(m_d30 <= 0.0) && m_d48 > static_cast<double>(m_unkd0) * 0x1.3333333333333p+0) {  // 1.2 (TOC -0x6930)
        m_unkfc = (m_unkfc & ~0x20u) | 0x20u;
        m_unkfc = (m_unkfc & ~0x4000u) | 0x4000u;
        return 0;
    }
    if (!readDone) return 1;
    return m_ui32SegmentsPlayed == static_cast<uint32_t>(m_unkc8) ? 0 : 1;
}

// 0x00082a88 CKCinematicStreamCpnt_Finish_maybe
void CKCinematicStreamCpnt::Finish() {
    if ((m_unkfc & 0x40) == 0 || g_cinematicStreamFile.m_bRunning == 0) return;
    if ((m_unkfc & 0x80) != 0) {
        const uint32_t count = m_vChannels.m_ui32NbUsedElt;
        for (uint32_t i = 0; i != count; ++i) {
            SCinematicStreamTrackType* type = TypeFor(&m_vChannels.m_pBlock[i]);
            type->m_pfnGiveBackActor(type, WithMediaBit(m_unkfc));  // slot +0x14
        }
    }
    CloseStream();
    if ((m_unkfc & 0x800) != 0 && m_pUnkf0 != nullptr) {
        static_cast<CKSrvSekensor*>(g_pEngine->m_srvSekensor)->StopSekens(static_cast<CKSekens*>(m_pUnkf0));
    }
    if ((m_unkfc & 0x800) != 0 && m_pUnkec != nullptr) {
        static_cast<CKSrvMusic*>(g_pEngine->m_srvMusic)->StopPlayList(static_cast<CKMusicPlayList*>(m_pUnkec));
    }
    if ((m_unkfc & 0x800) != 0) g_pEngine->m_soundManager->RestoreSavedVolume(0);
}

// 0x00082008 CKCinematicStreamCpnt_Stop_maybe
void CKCinematicStreamCpnt::Stop() {
    if ((m_unkfc & 0x40) == 0 || g_cinematicStreamFile.m_bRunning == 0) return;
    if ((m_unkfc & 0x80) != 0) {
        const uint32_t count = m_vChannels.m_ui32NbUsedElt;
        for (uint32_t i = 0; i != count; ++i) {
            SCinematicStreamTrackType* type = TypeFor(&m_vChannels.m_pBlock[i]);
            type->m_pfnStop(type, &m_vChunkData, WithMediaBit(m_unkfc));  // slot +0x18
        }
    }
    if (m_vSegmentStates.m_pBlock != nullptr) {
        Mem_FreeAligned16(m_vSegmentStates.m_pBlock);
        m_vSegmentStates.m_pBlock = nullptr;
    }
    m_vSegmentStates.m_ui32NbUsedElt = 0;
    m_vSegmentStates.m_pBlock = nullptr;
    if (m_vChunks.m_pBlock != nullptr) Mem_FreeAligned16(m_vChunks.m_pBlock);
    m_vChunks.m_ui32NbUsedElt = 0;
    m_vChunks.m_pBlock = nullptr;
    FreeChunkBuffers(m_vChunkBuffers, m_vChunkData);
    m_unkfc &= 0xffffff3fu;
    m_unkfc = 0;
    g_cinematicStreamFile.m_bRunning = 0;
}

// 0x00081ed8 CKCinematicStreamCpnt_RecursiveRegistration (returns 1)
void CKCinematicStreamCpnt::RecursiveRegistration(int32_t type) {
    if (static_cast<uint32_t>(type - 4) > 3u) g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);
}
