// SoundStream.h - one stream player of a SoundStreamType (0x38 bytes, OperatorNew; not a registered class): an RWA
// stream player and the CKStreamObject it plays, driven by a seven-state machine (the K engine's generic state machine:
// a table of member handlers at +0x14, the current state +0x18, the count +0x19, the owner +0x1c). Original unit:
// SoundStream.cpp (0x11b0a0-0x11d650; Ghidra also names its functions SoundVoice_* / SoundEmitterVoice_*).
//
// The object asks for a state through a request stack (+0x24, FreeListPool 0xceaa30 nodes: 0 play, 2 pause, 3 start
// paused; the bottom entry 1 = nothing), UpdateStateMachine turns the head into the requested state (+0x10, the names
// of the debug table 0x00b00f68) and the current state's handler moves the player (the state names: table 0x00b00f4c).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"

class CKStreamObject;
class IKTime;
struct RwaStreamPlayer;

// A node of the request stack (+0x24) and of the type's track list (SoundStreamType +0x130): 8 bytes from the
// FreeListPool 0xceaa30 (not ported: a plain allocation, as SoundNode).
struct SoundStreamRequest {
    int32_t m_i32Request;
    SoundStreamRequest* m_pNext;
};
DOTD_ASSERT_SIZE(SoundStreamRequest, 0x8);

class SoundStream {
public:
    // +0x10 (debug names 0x00b00f68)
    enum ERequest : int32_t {
        kObjPlay = 0,
        kObjNoMedia = 1,
        kObjStopped = 2,
        kObjPause = 3,
        kObjSuspended = 4,
        kObjStartPaused = 5,
    };
    // +0x18 (debug names 0x00b00f4c)
    enum EState : uint8_t {
        kNoMedia = 0,
        kOpening = 1,
        kMediaStopped = 2,
        kPlaying = 3,
        kPaused = 4,
        kSuspended = 5,
        kError = 6,
        kNoState = 0xff,
    };
    // A state handler (the entries of the table 0x00c4b15c): event 0 update (returns the next state), 1 entered (from
    // `other`), 2 left (for `other`).
    using StateHandler = uint8_t (SoundStream::*)(IKTime* clock, int32_t event, uint8_t other);
    // 0x0011b950 SoundStream_StateTransitionCallback_maybe (+0x08): whether `to` may follow `from`. Stored only.
    using TransitionCheck = uint32_t (*)(SoundStream* owner, IKTime* clock, uint32_t to, uint32_t from);

    void Init();                                // 0x0011c260 SoundStream_Init_maybe
    void Release();                             // 0x0011ba30 SoundEmitterVoice_Release_maybe
    void RemoveHeadRequestIfEquals(int32_t request);  // 0x0011b1d8 SoundStream_RemoveHeadItemIfEquals_maybe
    void SetObject(CKStreamObject* object);     // 0x0011b238 SoundStream_SetObjectAndClearFade_maybe
    void PushRequestIfNotHead(int32_t request); // 0x0011b250 SoundStream_PushItemIfNotHead_maybe
    // 0x0011b3d8 SoundStream_GetPlaybackItemAndPosition_maybe
    void GetPlaybackItemAndPosition(int32_t* item, float* position);
    uint8_t IsInRequestedState();               // 0x0011b7b0 SoundVoice_IsInRequestedState_maybe
    uint32_t GetPlayerState();                  // 0x0011b898 SoundStream_GetPlayerState_maybe
    uint8_t IsPlayerNoMedia();                  // 0x0011bbe8 SoundVoice_IsRwaState9_maybe
    uint8_t IsInRequestedState2();              // 0x0011c178 SoundVoice_IsInRequestedState_2_maybe (a copy)
    void UpdateStateMachine(IKTime* clock);     // 0x0011cab8 SoundStream_UpdateStateMachine_maybe
    void ApplyVolumeAndItem();                  // 0x0011cf58 SoundStream_ApplyVolumeAndItem_maybe

    // The states (Ghidra names in brackets where they differ from the debug table's).
    uint8_t StateNoMedia(IKTime* clock, int32_t event, uint8_t other);       // 0x0011be40 [SoundStream_StateIdle_maybe]
    uint8_t StateOpening(IKTime* clock, int32_t event, uint8_t other);       // 0x0011c708 [SoundStream_StateOpenSource_maybe]
    uint8_t StateMediaStopped(IKTime* clock, int32_t event, uint8_t other);  // 0x0011bd30 [SoundStream_StatePreparing_maybe]
    uint8_t StatePlaying(IKTime* clock, int32_t event, uint8_t other);       // 0x0011d1c8 SoundStream_StatePlaying_maybe
    uint8_t StatePaused(IKTime* clock, int32_t event, uint8_t other);        // 0x0011bc30 SoundStream_StatePaused_maybe
    uint8_t StateSuspended(IKTime* clock, int32_t event, uint8_t other);     // 0x0011bfd8 SoundStream_StateSuspended_maybe
    uint8_t StateError(IKTime* clock, int32_t event, uint8_t other);         // 0x0011bab8 [SoundStream_StateStopped_maybe]

    RwaStreamPlayer* m_pPlayer;         // +0x00 RwaStreamPlayer_Create_maybe(the output's driver, 0, 0, 0, 0)
    CKStreamObject* m_pObject;          // +0x04 the object it plays (SetObject); null when free
    TransitionCheck m_pfnTransition;    // +0x08 0x0011b950 (its OPD 0x00b59518)
    uint32_t m_unk0c;                   // +0x0c 0
    int32_t m_i32Request;               // +0x10 ERequest
    const StateHandler* m_pStates;      // +0x14 the handler table (0x00c4b15c)
    uint8_t m_ui8State;                 // +0x18 EState; 0xff = none
    uint8_t m_ui8StateCount;            // +0x19 7
    uint8_t m_pad1a[2];
    SoundStream* m_pOwner;              // +0x1c this (the object the handlers are called on)
    float m_fItemVolume;                // +0x20 the item volume last sent (-1.0 when a play starts)
    SoundStreamRequest* m_pRequests;    // +0x24 the request stack
    uint32_t m_ui32StoppedCount;        // +0x28 updates in Playing that saw the player STOPPED (the 4th ends the item)
    uint32_t m_ui32StarvedCount;        // +0x2c ... STARVED (the 4th: Error)
    float m_fResumeOffset;              // +0x30 where Playing starts again (Suspended keeps the position)
    uint32_t m_ui32ResumeItem;          // +0x34
};
DOTD_ASSERT_SIZE(SoundStream, 0x38);
DOTD_ASSERT_OFFSET(SoundStream, m_pObject, 0x04);
DOTD_ASSERT_OFFSET(SoundStream, m_pfnTransition, 0x08);
DOTD_ASSERT_OFFSET(SoundStream, m_i32Request, 0x10);
DOTD_ASSERT_OFFSET(SoundStream, m_pStates, 0x14);
DOTD_ASSERT_OFFSET(SoundStream, m_ui8State, 0x18);
DOTD_ASSERT_OFFSET(SoundStream, m_ui8StateCount, 0x19);
DOTD_ASSERT_OFFSET(SoundStream, m_pOwner, 0x1c);
DOTD_ASSERT_OFFSET(SoundStream, m_fItemVolume, 0x20);
DOTD_ASSERT_OFFSET(SoundStream, m_pRequests, 0x24);
DOTD_ASSERT_OFFSET(SoundStream, m_ui32StoppedCount, 0x28);
DOTD_ASSERT_OFFSET(SoundStream, m_fResumeOffset, 0x30);
DOTD_ASSERT_OFFSET(SoundStream, m_ui32ResumeItem, 0x34);
