// SoundStreamType.cpp - reconstructed original translation unit 0x11d650-0x11ef08 (GAME_TOC1, main_toc1), 27 functions, 23 live.
// Primary owner: SoundStreamType (not a registered class)
// Other owners: SoundEmitterGroup (11), SoundStream (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x11d650  SoundStreamType_RemovePending_maybe
//   [ ] 0x11d6e0  SoundStreamType_AssignObjectToFreeStream_maybe  [dead]
//   [x] 0x11d7e0  SoundEmitterGroup_DestroyVoices_maybe
//   [ ] 0x11d880  SoundStreamType_Construct_2_maybe  [dead]
//   [x] 0x11d940  SoundEmitterGroup_SnapVolumeToTarget_maybe
//   [x] 0x11d958  SoundEmitterGroup_SetVolume_maybe
//   [x] 0x11d980  SoundEmitterGroup_AreAllVoicesInactive_maybe
//   [x] 0x11d9f8  SoundStreamType_StartVolumeFade_maybe
//   [ ] 0x11da78  SoundStreamType_CountStreamsInState3_maybe  [dead]
//   [x] 0x11dad0  SoundEmitterGroup_AreAllVoicesState9_maybe
//   [x] 0x11db78  SoundStreamType_UnpauseObject_maybe
//   [x] 0x11dc20  SoundEmitterGroup_ResumeVoiceOf_maybe
//   [x] 0x11dcc8  SoundEmitterGroup_PauseVoiceOf_maybe
//   [x] 0x11dd70  SoundEmitterGroup_PauseInstances_maybe
//   [x] 0x11ddc0  SoundEmitterGroup_ResumeInstances_maybe
//   [x] 0x11de10  SoundEmitterGroup_StartVolumeFade_maybe
//   [x] 0x11de70  SoundEmitterGroup_AreAllVoicesSettled_maybe
//   [x] 0x11df10  SoundStreamType_Construct_maybe
//   [x] 0x11dfd0  SoundStreamType_Load_maybe
//   [x] 0x11e1b0  SoundStreamType_StopObject_maybe
//   [x] 0x11e340  SoundStreamType_Save_maybe
//   [x] 0x11e588  SoundStream_Update_maybe
//   [x] 0x11e818  SoundStreamType_PlayObject_maybe
//   [x] 0x11ea28  SoundStreamType_SetStreamCount_maybe
//   [ ] 0x11ebe0  SoundStreamType_Destructor_2_maybe  [dead]
//   [x] 0x11ece8  SoundStreamType_DeletingDestructor_maybe
//   [x] 0x11ee00  SoundStreamType_Destructor_maybe
#include "k2000/sound/SoundStreamType.h"

#include <cmath>
#include <cstring>

#include "k2000/core/IKSerializable.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/io/CKStreamObject.h"
#include "k2000/managers/CKSoundManager.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/FloatApproach.h"
#include "k2000/sound/SoundStream.h"
#include "k2000/sound/SoundVoiceManager.h"
#include "k2000/system/CTimeManager.h"
#include "k2000/system/IKTime.h"

namespace {

// Local copy of 0x000107d8 Str_HashXor4 (misc/Wcs.cpp, not ported yet): the bytes XORed into four
// accumulators in turn, returned as a little-endian word (lwbrx).
uint32_t Str_HashXor4(const char* s) {
    uint8_t acc[4] = {0, 0, 0, 0};
    for (uint32_t i = 0; s[i] != 0; ++i) acc[i & 3] ^= static_cast<uint8_t>(s[i]);
    return static_cast<uint32_t>(acc[0]) | (static_cast<uint32_t>(acc[1]) << 8) | (static_cast<uint32_t>(acc[2]) << 16) |
           (static_cast<uint32_t>(acc[3]) << 24);
}

// The stream player of `type` that plays `object` (the inlined search of the callers), null when none.
SoundStream* FindStream(SoundStreamType* type, const CKStreamObject* object) {
    for (uint32_t i = 0; i < type->m_vpStreams.m_ui32NbUsedElt; ++i) {
        SoundStream* stream = type->m_vpStreams.m_pBlock[i];
        if (stream->m_pObject == object) return stream;
    }
    return nullptr;
}

// A free stream player bound to `object` with a play request (and a pause request on top for an object that starts
// paused, +0x3a): the inlined form in PlayObject and Update.
void AssignFreeStream(SoundStreamType* type, CKStreamObject* object) {
    SoundStream* stream = FindStream(type, nullptr);
    if (stream == nullptr) return;
    stream->SetObject(object);
    stream->PushRequestIfNotHead(SoundStream::kObjPlay);
    if (object->m_unk3a != 0) stream->PushRequestIfNotHead(3);
}

// The track of `object` unlinked and given back to the pool (the inlined form in RemovePending and StopObject).
void UnlinkTrack(SoundStreamType* type, const CKStreamObject* object) {
    SoundStreamTrack* head = type->m_pTracks;
    if (head == nullptr) return;
    if (head->m_pObject == object) {
        type->m_pTracks = head->m_pNext;
        delete head;  // FreeListPool 0xceaa30
        return;
    }
    for (SoundStreamTrack* prev = head; prev->m_pNext != nullptr; prev = prev->m_pNext) {
        SoundStreamTrack* node = prev->m_pNext;
        if (node->m_pObject == object) {
            prev->m_pNext = node->m_pNext;
            delete node;
            return;
        }
    }
}

// The stream players released and deleted (SetStreamCount and DestroyVoices).
void ReleaseStreams(SoundStreamType* type) {
    for (uint32_t i = 0; i < type->m_vpStreams.m_ui32NbUsedElt; ++i) {
        SoundStream* stream = type->m_vpStreams.m_pBlock[i];
        if (stream != nullptr) {
            stream->Release();
            delete stream;  // OperatorDelete
        }
    }
    type->m_vpStreams.m_ui32NbUsedElt = 0;
}

}  // namespace

// 0x0011df10 SoundStreamType_Construct_maybe. The stores in the original's order.
SoundStreamType::SoundStreamType() {
    m_vpStreams.m_pBlock = nullptr;
    m_vpStreams.m_ui32NbUsedElt = 0;
    m_unk118 = 0.0f;
    m_unk11c = 0.0f;
    m_unk120 = 0.0f;
    m_pTracks = nullptr;
    m_vpStreams.m_ui32NbElt = 2;
    m_vpStreams.m_pBlock = static_cast<SoundStream**>(Mem_AllocAligned16(2 * static_cast<uint32_t>(sizeof(SoundStream*))));
    m_fVolume = 1.0f;          // TOC 0xc115f4
    m_unk12c = 0x1.99999ap-1f;  // 0.8, TOC 0xc115f8
    m_unk11c = 0.0f;
    m_unk120 = m_fVolume;
    m_unk118 = m_fVolume;
    m_ui32NameHash = 0;
    m_unk128 = 0x1.99999ap-1f;
    m_unk124 = 0x1.99999ap-1f;
}

// 0x0011ee00 SoundStreamType_Destructor_maybe (0x0011ece8 SoundStreamType_DeletingDestructor_maybe then deletes): every
// player released (SoundEmitterVoice_Release_maybe 0x11ba30) and deleted, the count cleared; the track list's nodes
// back to their pool (FreeListPool 0xceaa30), the list cleared; the player block freed (its pointer is left).
SoundStreamType::~SoundStreamType() {
    ReleaseStreams(this);
    SoundStreamTrack* node = m_pTracks;
    while (node != nullptr) {
        SoundStreamTrack* next = node->m_pNext;
        delete node;
        node = next;
    }
    m_pTracks = nullptr;
    if (m_vpStreams.m_pBlock != nullptr) Mem_FreeAligned16(m_vpStreams.m_pBlock);
}

// 0x0011ea28 SoundStreamType_SetStreamCount_maybe: only while the engine clock is not running (the GAME.KP3 load and
// post-load): the old players released, `count` new ones, then the voice pool rebuilt around them.
void SoundStreamType::SetStreamCount(uint32_t count) {
    if (g_pEngine->m_timeManager->m_pTime->m_eCurrentState == IKTime::RUNNING) return;
    if (m_vpStreams.m_ui32NbUsedElt == count) return;
    ReleaseStreams(this);
    for (uint32_t n = 0; n < count; ++n) {
        SoundStream* stream = new SoundStream();  // OperatorNew(0x38)
        stream->Init();
        const uint32_t used = m_vpStreams.m_ui32NbUsedElt;
        if (m_vpStreams.m_ui32NbElt == used) {
            uint32_t capacity = used + 2;
            uint32_t bytes = capacity * static_cast<uint32_t>(sizeof(SoundStream*));
            if (capacity == 0) {  // as in the original (cannot happen)
                capacity = 2;
                bytes = 2 * static_cast<uint32_t>(sizeof(SoundStream*));
            }
            m_vpStreams.m_pBlock = static_cast<SoundStream**>(Mem_ReallocAligned16(m_vpStreams.m_pBlock, bytes));
            m_vpStreams.m_ui32NbElt = capacity;
        }
        m_vpStreams.m_pBlock[m_vpStreams.m_ui32NbUsedElt] = stream;
        ++m_vpStreams.m_ui32NbUsedElt;
    }
    g_pEngine->m_soundManager->m_pVoiceManager->RebuildVoicePool();
}

// 0x0011d7e0 SoundEmitterGroup_DestroyVoices_maybe (the destructor's part, package C)
void SoundStreamType::DestroyVoices() { ReleaseStreams(this); }

// 0x0011d650 SoundStreamType_RemovePending_maybe: the object's track dropped.
void SoundStreamType::RemovePending(CKStreamObject* object) { UnlinkTrack(this, object); }

// 0x0011dfd0 SoundStreamType_Load_maybe
void SoundStreamType::Load(IKFile* file, int32_t type) {
    if (type != K_GAME_PLATEFORMS) return;
    IKFile_ReadLengthPrefixedString(file, m_szName, -1);
    m_ui32NameHash = Str_HashXor4(m_szName);
    ReadF32LE(file, &m_fVolume);
    ReadF32LE(file, &m_unk12c);
    ReadF32LE(file, &m_unk124);
    ReadF32LE(file, &m_unk128);
}

// 0x0011e340 SoundStreamType_Save_maybe: Load's fields (vt+0x20 writes, little-endian: the name's u16 length and
// bytes, then the four floats). Reached only from the dead CKSoundStreamManager_Save_maybe 0x116ad0.
void SoundStreamType::Save(IKFile* file, int32_t type) {
    if (type != K_GAME_PLATEFORMS) return;
    const uint16_t length = static_cast<uint16_t>(std::strlen(m_szName));
    file->Write(&length, 2);
    file->Write(m_szName, length);
    file->Write(&m_fVolume, 4);
    file->Write(&m_unk12c, 4);
    file->Write(&m_unk124, 4);
    file->Write(&m_unk128, 4);
}

// 0x0011d940 SoundEmitterGroup_SnapVolumeToTarget_maybe
void SoundStreamType::SnapVolumeToTarget() {
    m_unk118 = m_fVolume;
    m_unk120 = m_fVolume;
}

// 0x0011d958 SoundEmitterGroup_SetVolume_maybe: without a fade running the ramp jumps to the volume.
void SoundStreamType::SetVolume(float volume) {
    if (m_unk118 == m_fVolume) {
        m_unk120 = volume;
        m_unk118 = volume;
    }
    m_fVolume = volume;
}

// 0x0011d980 SoundEmitterGroup_AreAllVoicesInactive_maybe: no player has an object.
uint8_t SoundStreamType::AreAllVoicesInactive() {
    for (uint32_t i = 0; i < m_vpStreams.m_ui32NbUsedElt; ++i) {
        if (m_vpStreams.m_pBlock[i]->m_pObject != nullptr) return 0;
    }
    return 1;
}

// 0x0011d9f8 SoundStreamType_StartVolumeFade_maybe: towards min(volume, +0x12c) over +0x128 seconds.
void SoundStreamType::StartVolumeFade(int32_t fromTarget) {
    const float volume = m_fVolume;
    if (fromTarget != 0) m_unk120 = volume;
    const float target = volume <= m_unk12c ? volume : m_unk12c;
    m_unk118 = target;
    if (m_unk128 != 0.0f) {
        m_unk11c = std::fabs((m_unk120 - target) / m_unk128);
        return;
    }
    m_unk120 = target;
}

// 0x0011dad0 SoundEmitterGroup_AreAllVoicesState9_maybe: every player has no media.
uint8_t SoundStreamType::AreAllVoicesState9() {
    for (uint32_t i = 0; i < m_vpStreams.m_ui32NbUsedElt; ++i) {
        if (m_vpStreams.m_pBlock[i]->IsPlayerNoMedia() == 0) return 0;
    }
    return 1;
}

// 0x0011db78 SoundStreamType_UnpauseObject_maybe: the start-paused request of the object's player dropped.
void SoundStreamType::UnpauseObject(CKStreamObject* object) {
    SoundStream* stream = FindStream(this, object);
    if (stream != nullptr) stream->RemoveHeadRequestIfEquals(3);
}

// 0x0011dc20 SoundEmitterGroup_ResumeVoiceOf_maybe: the pause request of the object's player dropped.
void SoundStreamType::ResumeVoiceOf(CKStreamObject* object) {
    SoundStream* stream = FindStream(this, object);
    if (stream != nullptr) stream->RemoveHeadRequestIfEquals(2);
}

// 0x0011dcc8 SoundEmitterGroup_PauseVoiceOf_maybe: a pause request on the object's player.
void SoundStreamType::PauseVoiceOf(CKStreamObject* object) {
    SoundStream* stream = FindStream(this, object);
    if (stream != nullptr) stream->PushRequestIfNotHead(2);
}

// 0x0011de10 SoundEmitterGroup_StartVolumeFade_maybe
void SoundStreamType::ReleaseVolumeFade() {
    m_unk118 = m_fVolume;
    if (m_unk124 != 0.0f) {
        m_unk11c = std::fabs((m_unk120 - m_fVolume) / m_unk124);
        return;
    }
    m_unk120 = m_fVolume;
}

// 0x0011dd70 SoundEmitterGroup_PauseInstances_maybe: every track's object paused (CKStreamObject_Pause_maybe).
void SoundStreamType::PauseInstances() {
    for (SoundStreamTrack* node = m_pTracks; node != nullptr; node = node->m_pNext) node->m_pObject->Pause();
}

// 0x0011ddc0 SoundEmitterGroup_ResumeInstances_maybe: every track's object resumed (CKStreamObject_Resume_maybe).
void SoundStreamType::ResumeInstances() {
    for (SoundStreamTrack* node = m_pTracks; node != nullptr; node = node->m_pNext) node->m_pObject->Resume();
}

// 0x0011de70 SoundEmitterGroup_AreAllVoicesSettled_maybe: every player with an object has reached its state.
uint8_t SoundStreamType::AreAllVoicesSettled() {
    for (uint32_t i = 0; i < m_vpStreams.m_ui32NbUsedElt; ++i) {
        SoundStream* stream = m_vpStreams.m_pBlock[i];
        if (stream->IsInRequestedState() == 0 && stream->m_pObject != nullptr) return 0;
    }
    return 1;
}

// 0x0011e1b0 SoundStreamType_StopObject_maybe: a played object's play (and start-paused) request dropped, its player
// stops it; an object still waiting for a player leaves the track list at once.
void SoundStreamType::StopObject(CKStreamObject* object) {
    SoundStream* stream = FindStream(this, object);
    if (stream != nullptr) {
        const int32_t head = stream->m_pRequests->m_i32Request;
        if (head == 3) {
            stream->RemoveHeadRequestIfEquals(3);
            stream->RemoveHeadRequestIfEquals(0);
            return;
        }
        if (head == 1) return;
        stream->RemoveHeadRequestIfEquals(0);
        return;
    }
    UnlinkTrack(this, object);
    object->m_pType = nullptr;
    object->m_pStream = nullptr;
}

// 0x0011e588 SoundStream_Update_maybe: the volume ramp; each track's object ramps its volume and, without a player,
// takes a free one (while the game runs and the job queue does not hold the sounds); then every player's state machine.
void SoundStreamType::Update(IKTime* clock) {
    FloatApproach_Step(clock->m_afDeltaTime[IKTime::FIXED_GAME_TIME], &m_unk118);
    for (SoundStreamTrack* node = m_pTracks; node != nullptr; node = node->m_pNext) {
        CKStreamObject* object = node->m_pObject;
        object->UpdateFader(clock);
        if (FindStream(this, object) != nullptr) continue;
        CKSoundManager* manager = g_pEngine->m_soundManager;
        if (manager->IsNotPausedAndTimeRunning() != 0 && manager->m_unk1c == 0) AssignFreeStream(this, object);
    }
    // KStub_Nop_106d8(6, "%s volume %f", name, +0x120): a debug print
    const uint32_t count = m_vpStreams.m_ui32NbUsedElt;
    for (uint32_t i = 0; i != count; ++i) m_vpStreams.m_pBlock[i]->UpdateStateMachine(clock);
}

// 0x0011e818 SoundStreamType_PlayObject_maybe: an object that has a player gets a play request again; another takes a
// free player (unless the job queue holds the sounds) and joins the track list.
void SoundStreamType::PlayObject(CKStreamObject* object) {
    SoundStream* stream = FindStream(this, object);
    if (stream != nullptr) {
        stream->PushRequestIfNotHead(SoundStream::kObjPlay);
        if (object->m_unk3a == 0) return;
        stream->PushRequestIfNotHead(3);
        return;
    }
    if (g_pEngine->m_soundManager->m_unk1c == 0) AssignFreeStream(this, object);
    SoundStreamTrack* node = new SoundStreamTrack();  // FreeListPool_Alloc (0xceaa30)
    node->m_pNext = nullptr;
    node->m_pObject = object;
    node->m_pNext = m_pTracks;
    m_pTracks = node;
}
