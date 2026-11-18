// SoundStream.cpp - reconstructed original translation unit 0x11b0a0-0x11d650 (GAME_TOC1, main_toc1), 42 functions, 24 live.
// Primary owner: SoundStream (not a registered class)
// Other owners: SoundVoice (3), SoundEmitterVoice (2), SoundStreamType (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x11b0a0  SoundStream_SetRequestedState_maybe  [dead]
//   [ ] 0x11b0c8  SoundStream_UpdateRequestedState_maybe  [dead]
//   [x] 0x11b1d8  SoundStream_RemoveHeadItemIfEquals_maybe
//   [x] 0x11b238  SoundStream_SetObjectAndClearFade_maybe
//   [x] 0x11b250  SoundStream_PushItemIfNotHead_maybe
//   [ ] 0x11b310  SoundStream_SelectItemWithVolume_maybe  [dead]
//   [ ] 0x11b3a8  SoundStream_GetItemCount_maybe  [dead]
//   [x] 0x11b3d8  SoundStream_GetPlaybackItemAndPosition_maybe
//   [ ] 0x11b488  SoundStream_ReleaseObject_maybe  [dead]
//   [ ] 0x11b4d8  SoundStream_SyncPlayerVolume_maybe  [dead]
//   [ ] 0x11b538  SoundStream_ComputeObjectVolume_maybe  [dead]
//   [ ] 0x11b630  SoundStream_ClearPlayerSource_maybe  [dead]
//   [ ] 0x11b660  SoundStream_CommandPrepare_maybe  [dead]
//   [ ] 0x11b690  SoundStream_CommandPause_maybe  [dead]
//   [ ] 0x11b6c0  SoundStream_CommandPlay_maybe  [dead]
//   [ ] 0x11b710  SoundStream_SetSourceFromObject_maybe  [dead]
//   [x] 0x11b7b0  SoundVoice_IsInRequestedState_maybe
//   [x] 0x11b898  SoundStream_GetPlayerState_maybe
//   [ ] 0x11b8c8  SoundEmitterVoice_Release_2_maybe  [dead]
//   [x] 0x11b950  SoundStream_StateTransitionCallback_maybe
//   [x] 0x11ba30  SoundEmitterVoice_Release_maybe
//   [x] 0x11bab8  SoundStream_StateStopped_maybe
//   [x] 0x11bbe8  SoundVoice_IsRwaState9_maybe
//   [x] 0x11bc30  SoundStream_StatePaused_maybe
//   [x] 0x11bd30  SoundStream_StatePreparing_maybe
//   [x] 0x11be40  SoundStream_StateIdle_maybe
//   [x] 0x11bfd8  SoundStream_StateSuspended_maybe
//   [x] 0x11c178  SoundVoice_IsInRequestedState_2_maybe
//   [x] 0x11c260  SoundStream_Init_maybe
//   [ ] 0x11c3d8  SoundStream_Init_2_maybe  [dead]
//   [ ] 0x11c550  SoundStream_ApplyPendingItemSelect_maybe  [dead]
//   [ ] 0x11c650  SoundStream_ApplyObjectItemSelect_maybe  [dead]
//   [x] 0x11c708  SoundStream_StateOpenSource_maybe
//   [ ] 0x11c968  SoundStream_UpdateItemVolume_maybe  [dead]
//   [x] 0x11cab8  SoundStream_UpdateStateMachine_maybe
//   [x] 0x11cf58  SoundStream_ApplyVolumeAndItem_maybe
//   [x] 0x11d1c8  SoundStream_StatePlaying_maybe
//   [ ] 0x11d5c8  SoundStreamType_FindStreamForObject_maybe  [dead]
//   [x] 0x11d630  KStub_Nop_11d630
//   [x] 0x11d638  KStub_Nop_11d638
//   [x] 0x11d640  KStub_Nop_11d640
//   [x] 0x11d648  KStub_Nop_11d648
#include "k2000/sound/SoundStream.h"

#include <cstring>

#include "k2000/logic/io/CKStreamObject.h"
#include "k2000/logic/sound/CKStreamWave.h"
#include "k2000/managers/CKSoundManager.h"
#include "k2000/misc/CKGameLoop.h"
#include "k2000/misc/Engine.h"
#include "k2000/sound/CKSoundOutput.h"
#include "k2000/sound/CKSoundStreamManager.h"
#include "k2000/sound/SoundStreamType.h"
#include "platform/audio/rwa_stream.h"

namespace {

constexpr float kZero = 0.0f;       // TOC -0x4428
constexpr float kOne = 1.0f;        // TOC -0x442c (the item volume's cap)
constexpr float kMinusOne = -1.0f;  // TOC -0x4418 (0xbf800000)

// 0x0011b950 SoundStream_StateTransitionCallback_maybe (a jump table on `from`, 0x0011b974): the transitions the state
// machine allows. Stored in +0x08 by Init; only the dead SoundStream_SetRequestedState_maybe pair calls it.
uint32_t StateTransitionCallback(SoundStream* /*owner*/, IKTime* /*clock*/, uint32_t to, uint32_t from) {
    switch (from) {
        case SoundStream::kNoMedia:
            return to == 1 || to == 3 || to == 5 || to == 2 || to == 4 ? 1u : 0u;
        case SoundStream::kOpening:
            return to == 0 || to == 3 || to == 5 || to == 2 || to == 4 ? 1u : 0u;
        case SoundStream::kMediaStopped:
            return to == 0 || to == 3 || to == 5 || to == 4 ? 1u : 0u;
        case SoundStream::kPlaying:
            return to <= 1 || to == 5 || to == 4 || to == 2 ? 1u : 0u;
        case SoundStream::kSuspended:
            return to <= 1 || to == 3 || to == 4 || to == 2 ? 1u : 0u;
        default:  // 4 (Paused) and anything above 5
            return 1;
    }
}

// 0x00c4b15c: the handlers by state (member function records {OPD, 0}).
const SoundStream::StateHandler kStates[7] = {
    &SoundStream::StateNoMedia,  &SoundStream::StateOpening,   &SoundStream::StateMediaStopped, &SoundStream::StatePlaying,
    &SoundStream::StatePaused,   &SoundStream::StateSuspended, &SoundStream::StateError,
};

SoundStreamRequest* NewRequest() { return new SoundStreamRequest(); }  // FreeListPool_Alloc (0xceaa30)
void FreeRequest(SoundStreamRequest* node) { delete node; }             // back to the pool's free list (+0x04)

// The request stack's head removed when it is `request` (the inlined form in StatePlaying).
void PopHeadIfEquals(SoundStream* stream, int32_t request) {
    SoundStreamRequest* head = stream->m_pRequests;
    if (head->m_i32Request == request) {
        stream->m_pRequests = head->m_pNext;
        FreeRequest(head);
    }
}

float ReadFloat(uint32_t bits) {
    float value;
    std::memcpy(&value, &bits, 4);
    return value;
}

}  // namespace

// 0x0011c260 SoundStream_Init_maybe. The stores in the original's order; the request stack starts with 1 (nothing).
void SoundStream::Init() {
    m_i32Request = kObjNoMedia;
    m_ui8State = kNoState;
    m_ui8StateCount = 0xff;
    m_pRequests = nullptr;
    m_pPlayer = RwaStreamPlayer_Create(g_pEngine->m_soundManager->m_pOutput->m_rwaOutput);  // (driver, 0, 0, 0, 0)
    m_pObject = nullptr;
    m_ui8StateCount = 7;
    m_pStates = kStates;
    m_pfnTransition = &StateTransitionCallback;
    m_pOwner = this;
    m_unk0c = 0;
    m_ui8State = kNoMedia;
    m_fItemVolume = kMinusOne;
    m_ui32StarvedCount = 0;
    m_ui32StoppedCount = 0;
    PushRequestIfNotHead(kObjNoMedia);
    m_ui32ResumeItem = 0;
    m_fResumeOffset = 0.0f;
}

// 0x0011ba30 SoundEmitterVoice_Release_maybe: the player destroyed, the request stack freed.
void SoundStream::Release() {
    RwaStreamPlayer_Destroy(m_pPlayer);  // RwaObject_Destroy_maybe(player, 0, 0)
    m_pPlayer = nullptr;
    SoundStreamRequest* node = m_pRequests;
    while (node != nullptr) {
        SoundStreamRequest* next = node->m_pNext;
        FreeRequest(node);
        node = next;
    }
    m_pRequests = nullptr;
}

// 0x0011b1d8 SoundStream_RemoveHeadItemIfEquals_maybe
void SoundStream::RemoveHeadRequestIfEquals(int32_t request) {
    SoundStreamRequest* head = m_pRequests;
    if (head->m_i32Request == request) {  // BUG(original): an empty stack is read (never empty: the bottom 1 stays)
        m_pRequests = head->m_pNext;
        FreeRequest(head);
    }
}

// 0x0011b238 SoundStream_SetObjectAndClearFade_maybe
void SoundStream::SetObject(CKStreamObject* object) {
    m_pObject = object;
    m_ui32ResumeItem = 0;
    m_fResumeOffset = 0.0f;
}

// 0x0011b250 SoundStream_PushItemIfNotHead_maybe
void SoundStream::PushRequestIfNotHead(int32_t request) {
    if (m_pRequests != nullptr && m_pRequests->m_i32Request == request) return;
    SoundStreamRequest* node = NewRequest();
    node->m_pNext = nullptr;
    node->m_i32Request = request;
    node->m_pNext = m_pRequests;
    m_pRequests = node;
}

// 0x0011b3d8 SoundStream_GetPlaybackItemAndPosition_maybe: the player's item and seconds (item 0 / 0 s while it outputs
// nothing); 0 / 0 in NoMedia and Opening.
void SoundStream::GetPlaybackItemAndPosition(int32_t* item, float* position) {
    if (m_ui8State == kNoMedia || m_ui8State == kOpening) {
        *item = 0;
        *position = 0.0f;
        return;
    }
    RwaStreamPosition current = {0xff, 3, 0.0f, 1};
    RwaStreamPlayer_GetCurrentItem(m_pPlayer, &current);
    *item = static_cast<int32_t>(current.item);
    *position = current.offset;
}

// 0x0011b7b0 SoundVoice_IsInRequestedState_maybe: the player has reached what the state asked of it.
uint8_t SoundStream::IsInRequestedState() {
    const uint32_t state = RwaStreamPlayer_GetState(m_pPlayer);
    switch (m_ui8State) {
        case kPaused:
            return state - kRwaStreamPausing <= 1 ? 1 : 0;  // PAUSING or PAUSED
        case kMediaStopped:
            return state == kRwaStreamStopped || state == kRwaStreamStopping ? 1 : 0;
        case kSuspended:
            return state == kRwaStreamStopped || state == kRwaStreamStopping || state == kRwaStreamNoMedia ? 1 : 0;
        default:
            return 0;
    }
}

// 0x0011c178 SoundVoice_IsInRequestedState_2_maybe: the same code (CKSekens_IsStreamVoiceActive_maybe and the music
// play list call this copy).
uint8_t SoundStream::IsInRequestedState2() { return IsInRequestedState(); }

// 0x0011b898 SoundStream_GetPlayerState_maybe
uint32_t SoundStream::GetPlayerState() { return RwaStreamPlayer_GetState(m_pPlayer); }

// 0x0011bbe8 SoundVoice_IsRwaState9_maybe
uint8_t SoundStream::IsPlayerNoMedia() { return RwaStreamPlayer_GetState(m_pPlayer) == kRwaStreamNoMedia ? 1 : 0; }

// 0x0011cab8 SoundStream_UpdateStateMachine_maybe: the request stack's head (1 when empty) becomes the requested state,
// then the current state's handler runs; a state change calls the old one's exit and the new one's entry.
void SoundStream::UpdateStateMachine(IKTime* clock) {
    const int32_t head = m_pRequests != nullptr ? m_pRequests->m_i32Request : kObjNoMedia;
    CKSoundManager* manager = g_pEngine->m_soundManager;
    const uint8_t suspended = manager->m_pSoundStreamManager->m_unk18;
    int32_t request = m_i32Request;
    if (manager->m_unk1c == 0 || manager->m_unk1d != 0) {
        if (suspended != 0) {
            request = kObjSuspended;
        } else if (head == 1) {
            request = m_pObject != nullptr && m_pObject->m_unk39 != 0 ? kObjStopped : kObjNoMedia;
        } else if (head == 0) {
            request = kObjPlay;
        } else if (head == 2) {
            request = kObjPause;
        } else if (head == 3) {
            request = kObjStartPaused;
        }
        // BUG(original): another head stores the sound manager's address (r11); the K code pushes only 0, 1, 2 and 3.
    } else if (suspended != 0) {
        request = kObjSuspended;
    } else {
        request = m_pObject != nullptr ? kObjPause : kObjNoMedia;  // the job queue holds the sounds
    }
    m_i32Request = request;

    const uint8_t current = m_ui8State;
    if (current != kNoState) {
        const uint8_t next = (m_pOwner->*m_pStates[current])(clock, 0, current);
        const uint8_t left = m_ui8State;
        if (next != left) {
            if (left != kNoState) (m_pOwner->*m_pStates[left])(clock, 2, next);
            m_ui8State = next;
            if (next != kNoState) (m_pOwner->*m_pStates[next])(clock, 1, left);
        }
    }
    // KStub_Nop_106d8(6, ...): a debug print of the player's state, the state, the request, "Used"/"Aucun" and the
    // volumes (RwaStreamPlayer_GetState, CKGameLoop_IsRequestedLevelWithGmFlag294_maybe and the stream manager's
    // current volume getters: reads only).
}

// 0x0011cf58 SoundStream_ApplyVolumeAndItem_maybe: the item volume (the stream type's current volume, the sound
// manager's music or speech factor and the object's ramp; 0 while a requested level loads), the player's volume (the
// object's +0x18) and the object's pending item.
void SoundStream::ApplyVolumeAndItem() {
    if (m_pObject == nullptr) return;
    const float previous = m_fItemVolume;
    RwaStreamItemVolume itemVolume = {-1, -1, -1, 0.0f};
    float volume = kZero;
    if (g_pEngine->m_gameLoop->IsRequestedLevelWithGmFlag294() == 0) {
        CKStreamWave* wave = m_pObject != nullptr ? static_cast<CKStreamWave*>(m_pObject->m_pStreamWave) : nullptr;
        if (wave != nullptr) {
            CKSoundManager* manager = g_pEngine->m_soundManager;
            float v;
            if (wave->m_unk218 != 0) {
                v = manager->m_pSoundStreamManager->GetSpeechCurrentVolume() * manager->m_unk34[1];
            } else {
                v = manager->m_pSoundStreamManager->GetMusicCurrentVolume() * manager->m_unk34[0];
            }
            v = v * m_pObject->m_pType->m_unk120;
            v = v * m_pObject->m_unk34;
            volume = v < kOne ? v : kOne;  // blt: NaN takes the cap
        }
    }
    itemVolume.volume = volume;
    if (volume != previous) {
        RwaStreamPlayer_SetItemVolume(m_pPlayer, &itemVolume);
        m_fItemVolume = volume;
    }
    const float playerVolume = m_pObject->m_unk18;
    if (playerVolume != RwaStreamPlayer_GetVolume(m_pPlayer)) RwaStreamPlayer_SetVolume(playerVolume, m_pPlayer);
    const int32_t item = m_pObject->m_unk1c;
    const float offset = ReadFloat(m_pObject->m_unk20);
    if (item == -1) return;
    const uint32_t last = RwaStreamPlayer_GetItemCount(m_pPlayer) - 1;
    RwaStreamPosition position = {static_cast<uint32_t>(item) > last ? last : static_cast<uint32_t>(item), 3, offset, 1};
    const RwaStreamSelect select = {&position, 1};
    RwaStreamPlayer_SelectItem(m_pPlayer, &select);
    m_pObject->m_unk20 = 0;
    m_pObject->m_unk1c = -1;
}

// 0x0011be40 SoundStream_StateIdle_maybe (NoMedia). Entered: the source closed (not after Suspended, which closed it)
// and the object given back to its type. Update, once the player has no media: a play or pause request opens the
// source; a stop request gives the object back.
uint8_t SoundStream::StateNoMedia(IKTime* /*clock*/, int32_t event, uint8_t other) {
    const uint32_t state = RwaStreamPlayer_GetState(m_pPlayer);
    if (event == 1) {
        m_ui32StoppedCount = 0;
        m_ui32StarvedCount = 0;
        if (other != kSuspended) RwaStreamPlayer_SetSource(m_pPlayer, nullptr);
        CKStreamObject* object = m_pObject;
        if (object != nullptr) {
            object->m_pType->RemovePending(object);
            m_pObject->m_pType = nullptr;
            m_pObject->m_pStream = nullptr;
            m_pObject = nullptr;
            return kNoMedia;
        }
    } else if (event == 0 && state == kRwaStreamNoMedia) {
        const int32_t request = m_i32Request;
        if (request == kObjPlay || request == kObjPause || request == kObjStartPaused || request == kObjStopped) return kOpening;
        if (request == kObjSuspended) return kSuspended;
        if (request == kObjNoMedia && m_pObject != nullptr) {
            m_pObject->m_pType->RemovePending(m_pObject);
            m_pObject->m_pStream = nullptr;
            m_pObject->m_pType = nullptr;
            m_pObject = nullptr;
            return kNoMedia;
        }
    }
    return kNoMedia;
}

// 0x0011c708 SoundStream_StateOpenSource_maybe (Opening). Entered: the wave's file set as the player's source. Update,
// once the player has it (STOPPED): the object gets its stream (+0x0c) and its pending item is selected; then by the
// request.
uint8_t SoundStream::StateOpening(IKTime* /*clock*/, int32_t event, uint8_t /*other*/) {
    const uint32_t state = RwaStreamPlayer_GetState(m_pPlayer);
    if (event == 1) {
        m_ui32StoppedCount = 0;
        m_ui32StarvedCount = 0;
        CKStreamWave* wave = static_cast<CKStreamWave*>(m_pObject->m_pStreamWave);
        RwaStreamSource source;
        source.path = wave->BuildFilePath();
        source.unk04 = static_cast<uint32_t>(event);
        source.unk08 = 0;
        source.unk0c = 0;
        source.unk10 = 0;
        source.unk14 = 0;
        source.unk18 = 8;
        source.unk1c = 2;
        source.unk20 = static_cast<uint32_t>(event);
        source.unk24 = wave->m_unk218 == 0 ? 1u : 0u;
        RwaStreamPlayer_SetSource(m_pPlayer, &source);
        return kOpening;
    }
    if (event != 0 || state != kRwaStreamStopped) return kOpening;
    if (m_pObject->m_pStream == nullptr) {
        m_pObject->m_pStream = this;
        const int32_t item = m_pObject->m_unk1c;
        const float offset = ReadFloat(m_pObject->m_unk20);
        if (item != -1) {
            const uint32_t last = RwaStreamPlayer_GetItemCount(m_pPlayer) - 1;
            // `by` is the player state just read (STOPPED = 3, by index).
            RwaStreamPosition position = {static_cast<uint32_t>(item) > last ? last : static_cast<uint32_t>(item), state,
                                          offset, 1};
            const RwaStreamSelect select = {&position, 1};
            RwaStreamPlayer_SelectItem(m_pPlayer, &select);
            m_pObject->m_unk1c = -1;
            m_pObject->m_unk20 = 0;
        }
    }
    const int32_t request = m_i32Request;
    if (request == kObjPlay) return kPlaying;
    if (request == kObjPause || request == kObjStartPaused) return kPaused;
    if (request == kObjNoMedia) return kNoMedia;
    if (request == kObjSuspended) return kSuspended;
    return kOpening;
}

// 0x0011bd30 SoundStream_StatePreparing_maybe (MediaStopped). Entered: the player stopped. Update, once it is: by the
// request.
uint8_t SoundStream::StateMediaStopped(IKTime* /*clock*/, int32_t event, uint8_t /*other*/) {
    const uint32_t state = RwaStreamPlayer_GetState(m_pPlayer);
    if (event == 1) {
        m_ui32StoppedCount = 0;
        m_ui32StarvedCount = 0;
        RwaStreamPlayer_SetCommand(m_pPlayer, kRwaStreamCommandStop);
        return kMediaStopped;
    }
    if (event != 0 || state != kRwaStreamStopped) return kMediaStopped;
    const int32_t request = m_i32Request;
    if (request == kObjPlay) return kPlaying;
    if (request == kObjPause || request == kObjStartPaused) return kMediaStopped;
    if (request == kObjNoMedia) return kNoMedia;
    if (request == kObjSuspended) return kSuspended;
    return kMediaStopped;
}

// 0x0011d1c8 SoundStream_StatePlaying_maybe. Entered: play, the loop flag (object +0x24), the volumes and item, then a
// position kept by Suspended. Update: the volumes follow while the player plays; the 4th update that sees it STOPPED
// ends the item (the play request popped; NoMedia, or MediaStopped for an object that keeps its media, +0x39); the 4th
// STARVED: Error. A stop request waits for the object's volume ramp to reach its target (and for the game to run).
uint8_t SoundStream::StatePlaying(IKTime* /*clock*/, int32_t event, uint8_t /*other*/) {
    const uint32_t state = RwaStreamPlayer_GetState(m_pPlayer);
    if (event == 1) {
        m_ui32StoppedCount = 0;
        m_ui32StarvedCount = 0;
        m_fItemVolume = kMinusOne;
        RwaStreamPlayer_SetCommand(m_pPlayer, kRwaStreamCommandPlay);
        RwaStreamPlayer_SetLoop(m_pPlayer, m_pObject->m_unk24);
        ApplyVolumeAndItem();
        const float offset = m_fResumeOffset;
        const uint32_t item = m_ui32ResumeItem;
        if (offset == kZero && item == 0) return kPlaying;
        const uint32_t last = RwaStreamPlayer_GetItemCount(m_pPlayer) - 1;
        RwaStreamPosition position = {item > last ? last : item, 3, offset, 1};
        const RwaStreamSelect select = {&position, 1};
        RwaStreamPlayer_SelectItem(m_pPlayer, &select);
        m_fResumeOffset = kZero;
        m_ui32ResumeItem = 0;
        return kPlaying;
    }
    if (event != 0) return kPlaying;
    const int32_t request = m_i32Request;
    if (request == kObjPlay) {
        if (state == kRwaStreamPlaying) {
            ApplyVolumeAndItem();
            return kPlaying;
        }
        if (state == kRwaStreamStopped) {
            const uint32_t count = m_ui32StoppedCount++;
            if (count <= 2) return kPlaying;
            PopHeadIfEquals(this, kObjPlay);
            if (m_pObject->m_unk39 != 0) {
                m_i32Request = kObjStopped;
                return kMediaStopped;
            }
            m_i32Request = kObjNoMedia;
            return kNoMedia;
        }
        if (state == kRwaStreamStarved) {
            const uint32_t count = m_ui32StarvedCount++;
            if (count > 2) return kError;
        }
        return kPlaying;
    }
    if (request == kObjPause || request == kObjStartPaused) return kPaused;
    if (request == kObjNoMedia) {
        if (state == kRwaStreamPlaying) ApplyVolumeAndItem();
        if (g_pEngine->m_soundManager->IsNotPausedAndTimeRunning() == 0) return kMediaStopped;
        const uint8_t mode = g_pEngine->m_gameLoop->m_mode;
        if (mode == 6 || mode == 9 || mode == 0xa) return kMediaStopped;
        if (m_pObject->m_unk2c == m_pObject->m_unk34) return kMediaStopped;  // faded out
        return kPlaying;
    }
    if (request == kObjSuspended) return kSuspended;
    return kPlaying;
}

// 0x0011bc30 SoundStream_StatePaused_maybe. Entered: the player paused.
uint8_t SoundStream::StatePaused(IKTime* /*clock*/, int32_t event, uint8_t /*other*/) {
    const uint32_t state = RwaStreamPlayer_GetState(m_pPlayer);
    if (event == 1) {
        m_ui32StoppedCount = 0;
        m_ui32StarvedCount = 0;
        RwaStreamPlayer_SetCommand(m_pPlayer, kRwaStreamCommandPause);
        return kPaused;
    }
    if (event != 0) return kPaused;
    const int32_t request = m_i32Request;
    if (request == kObjPlay || request == kObjNoMedia) return kPlaying;
    if (request == kObjSuspended) return kSuspended;
    if (state == kRwaStreamStopped) return kMediaStopped;
    return kPaused;
}

// 0x0011bfd8 SoundStream_StateSuspended_maybe. Entered (with an object): from Playing (or from Paused with no kept
// position) the position is kept for the next Playing, then the source closed (not from NoMedia). Update: back to
// NoMedia (stop request) or Opening.
uint8_t SoundStream::StateSuspended(IKTime* /*clock*/, int32_t event, uint8_t other) {
    RwaStreamPlayer_GetState(m_pPlayer);
    if (event != 1) {
        if (event != 0) return kSuspended;
        if (m_i32Request == kObjNoMedia) return kNoMedia;
        if (m_i32Request != kObjSuspended) return kOpening;
        return kSuspended;
    }
    m_ui32StoppedCount = 0;
    m_ui32StarvedCount = 0;
    if (m_pObject == nullptr) return kSuspended;
    bool keep = other == kPlaying;
    if (other == kPaused) keep = m_fResumeOffset == kZero && m_ui32ResumeItem == 0;
    if (keep) {
        if (m_ui8State == kNoMedia || m_ui8State == kOpening) {  // never: the state is Suspended already
            m_ui32ResumeItem = 0;
            m_fResumeOffset = 0.0f;
        } else {
            RwaStreamPosition current = {0xff, 3, 0.0f, static_cast<uint32_t>(event)};
            RwaStreamPlayer_GetCurrentItem(m_pPlayer, &current);
            m_ui32ResumeItem = current.item;
            m_fResumeOffset = current.offset;
        }
    }
    if (other == kNoMedia) return kSuspended;
    RwaStreamPlayer_SetSource(m_pPlayer, nullptr);
    return kSuspended;
}

// 0x0011bab8 SoundStream_StateStopped_maybe (Error): back to Playing when the player plays again.
uint8_t SoundStream::StateError(IKTime* /*clock*/, int32_t event, uint8_t /*other*/) {
    const uint32_t state = RwaStreamPlayer_GetState(m_pPlayer);
    if (event == 1) {
        m_ui32StoppedCount = 0;
        m_ui32StarvedCount = 0;
        return kError;
    }
    if (event == 0) {
        const int32_t request = m_i32Request;
        if (request == kObjPlay) {
            if (state == kRwaStreamPlaying) return kPlaying;
        } else {
            if (request == kObjSuspended) return kSuspended;
            if (request == kObjNoMedia) return kMediaStopped;
            if (request == kObjPause || request == kObjStartPaused) return kPaused;
        }
    }
    return kError;
}

// 0x0011d630 / 0x0011d638 / 0x0011d640 / 0x0011d648 KStub_Nop_*: the stream type's empty hooks (SoundStreamType vtable
// slots; CKSoundStreamManager::CallNopHookOnEntries, Suspend and Unsuspend call them). Nothing to port.
