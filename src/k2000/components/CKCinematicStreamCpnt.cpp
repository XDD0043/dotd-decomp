// CKCinematicStreamCpnt.cpp - reconstructed original translation unit 0x80a90-0x864b8 (GAME_TOC1, main_toc1), 67 functions, 32 live.
// Primary class: CKCinematicStreamCpnt  key 0x13c6  category Component  size 0x100  vtable 0xb168b8
// Other owners: CinematicStreamFile (2)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x80a90  CKCinematicStreamCpnt_Delete
//   [ ] 0x80ae0  CKCinematicStreamCpnt_ZeroRuntimeFields_maybe  [dead]
//   [ ] 0x80b38  CKCinematicStreamCpnt_vf50
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
//   [ ] 0x81130  CKCinematicStreamCpnt_GetChannelMarkList_maybe
//   [ ] 0x81188  CinematicStreamFile_GetTrackSlot_maybe  [dead]
//   [ ] 0x811a8  CKCinematicStreamCpnt_FindChannelIndexByActor_maybe  [dead]
//   [ ] 0x81218  RegisterCKCinematicStreamCpntClass
//   [ ] 0x81348  _GLOBAL__I_81348
//   [x] 0x81358  CKCinematicStreamCpnt_DeleteArray
//   [ ] 0x81400  CKCinematicStreamCpnt_CloseStream_maybe
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
//   [ ] 0x81980  CKCinematicStreamCpnt_BuildStreamPath_maybe
//   [ ] 0x81a38  CKCinematicStreamCpnt_PostLoad
//   [ ] 0x81b58  FUN_00081b58  [dead]
//   [ ] 0x81c30  CKCinematicStreamCpnt_FindChannelIndexBySecondActor_maybe  [dead]
//   [ ] 0x81ca0  CKCinematicStreamCpnt_InitChannels_maybe
//   [x] 0x81db8  CKCinematicStreamCpnt_ResetChannels_maybe
//   [ ] 0x81ed0  CKCinematicStreamCpnt_Save
//   [ ] 0x81ed8  CKCinematicStreamCpnt_RecursiveRegistration
//   [ ] 0x81f40  CKCinematicStreamCpnt_GetChannelBufferField20_maybe  [dead]
//   [ ] 0x82008  CKCinematicStreamCpnt_Stop_maybe
//   [ ] 0x82290  CKCinematicStreamCpnt_ReadNextChunk_maybe
//   [ ] 0x82470  CKCinematicStreamCpnt_RequestChunkHeader_maybe  [dead]
//   [ ] 0x82598  FUN_00082598  [dead]
//   [ ] 0x826d8  CKCinematicStreamCpnt_UpdateSyncedMedia_maybe
//   [ ] 0x829d0  CKCinematicStreamCpnt_ReopenStream_maybe
//   [ ] 0x82a88  CKCinematicStreamCpnt_Finish_maybe
//   [ ] 0x82cb0  CKCinematicStreamCpnt_UpdateSetHandlers_maybe  [dead]
//   [ ] 0x82ec0  CKCinematicStreamCpnt_DispatchChunk_maybe
//   [ ] 0x83138  CKCinematicStreamCpnt_ResizeChannels_maybe  [dead]
//   [ ] 0x83268  CKCinematicStreamCpnt_StepSegmentStateMachine_maybe
//   [ ] 0x83820  CKCinematicStreamCpnt_Update_maybe
//   [ ] 0x83f18  CKCinematicStreamCpnt_UpdateStream_maybe
//   [ ] 0x84308  CKCinematicStreamCpnt_StreamReadyJobCallback_maybe
//   [ ] 0x843c0  CKCinematicStreamCpnt_AllocChunkTables_maybe
//   [ ] 0x84860  CKCinematicStreamCpnt_FreeChunkTables_maybe
//   [ ] 0x84a58  CKCinematicStreamCpnt_Destroy
//   [ ] 0x84a60  CKCinematicStreamCpnt_OpenStreamFile_maybe
//   [ ] 0x84ca8  CKCinematicStreamCpnt_StartStream_maybe
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
//   [ ] 0x99b840  CKCinematicStreamCpnt_Destructor  [inline]
//   [ ] 0x99b968  CKCinematicStreamCpnt_DeletingDestructor  [inline]
//   [x] 0x99baa0  CKCinematicStreamCpnt_ChannelArray_Resize_maybe  [inline]
//   [x] 0x99bd40  CKCinematicStreamCpnt_SetTimeQuantizedToFrames_maybe  [inline]
#include "k2000/components/CKCinematicStreamCpnt.h"

#include "k2000/cameras/IKCamera.h"
#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/Engine.h"
#include "k2000/system/CTimeManager.h"

IKSerializable* g_pCinematicStreamCamera = nullptr;  // 0x00c5c85c
uint32_t g_ui32CinematicStreamCameraCount = 0;        // 0x00c5c860
SCinematicStreamChannelType g_aCinematicStreamChannelTypes[3] = {};  // 0x00c5c6d8 (bss)
SCinematicStreamChannelState g_aCinematicStreamChannelState[3] = {};  // 0x00c5c744 (bss)

namespace {

const CVector3 kVectorZero = {0.0f, 0.0f, 0.0f};  // 0x00c50d64

// The engine's minimum time step: 0.1f (TOC -0x6920), or 1 / the fixed rate when the time manager runs at
// a fixed rate (m_properties bit 0).
float MinimumTimeStep() {
    const CTimeManager* manager = g_pEngine->m_timeManager;
    if ((manager->m_properties & 1) == 0) return 0x1.99999ap-4f;
    return 0x1p+0f / static_cast<float>(manager->m_ui8FixedRate);  // fdivs
}

// A new key or event block for the Load: the "resize to count" of the keys and events vectors (one element
// for an empty first block, the used count then left alone), the new elements constructed.
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

}  // namespace

// 0x00084ef8 CKCinematicStreamCpnt_ConstructBase_maybe
void CKCinematicStreamCpnt::ConstructBase() {
    m_unk1c = 3;
    m_unkc4 = -1;
    for (uint32_t& word : m_unk20) word = 0;  // +0x20..+0x7c (+0x50 as 0.0f)
    m_ui32NbFrames = 0;
    m_unkbc = 0;
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
    // The channel types' Load slots (the original stores every slot of the three types here).
    g_aCinematicStreamChannelTypes[0] = {CinematicStream_GetFloatBlock9Size, CinematicStream_LoadFloatBlock9};
    g_aCinematicStreamChannelTypes[1] = {CinematicStream_GetNoBufferSize, CinematicStream_LoadNothing};
    g_aCinematicStreamChannelTypes[2] = {CinematicStream_GetFloatBlock9Size_Thunk,
                                         CinematicStream_LoadFloatBlock9_Thunk};
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
        channel.m_unk0c = 0;
        channel.m_pMatrix10 = nullptr;
        channel.m_pUnk18 = nullptr;
        channel.m_pUnk1c = nullptr;
        channel.m_unk20 = 0;
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
    IKFile_ReadRef(file, &g_pCinematicStreamCamera);
    if (g_pCinematicStreamCamera != nullptr) {
        ++g_ui32CinematicStreamCameraCount;
        IKCamera* camera = static_cast<IKCamera*>(g_pCinematicStreamCamera);
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
        const SCinematicStreamChannelType& handlers = g_aCinematicStreamChannelTypes[channel.m_type];
        channel.AllocBuffer(handlers.m_pfnGetBufferSize());
        handlers.m_pfnLoadBuffer(channel.m_pBuffer, file, K_LEVEL_PLATEFORMS);
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

// 0x00081db8 CKCinematicStreamCpnt_ResetChannels_maybe. The channel's type indexes the three type objects (the
// original does not range-check it).
void CKCinematicStreamCpnt::ResetChannels() {
    for (uint32_t i = 0; i < m_vChannels.m_ui32NbUsedElt; ++i) {
        SChannel& channel = m_vChannels.m_pBlock[i];
        SCinematicStreamChannelState& state = g_aCinematicStreamChannelState[channel.m_type];
        state.m_pChannel = nullptr;  // +0x40, set below
        state.m_unk44 = 0;
        state.m_unk4c = 0;
        state.m_unk50[0] = state.m_unk50[1] = 0;
        state.m_unk58[0] = state.m_unk58[1] = 0;
        state.m_unk60 = 0;
        state.m_unk64 = 0;
        state.m_unk68 = 0;
        state.m_unk6c = 0;
        state.m_unk6d = 0;
        state.m_unk6e = 0;
        state.m_unk3c = 0;
        state.m_pChannel = &channel;
        // The type's reset handler (slot +0x08: KStub_Nop_7f530 / 0x99b5e0 / 0x7f688) does nothing.
    }
}
