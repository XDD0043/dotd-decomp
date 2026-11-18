// CKStreamObject.h - a streamed sound (key 0x5a4c, vtable 0xb19a00, size 0x3c). Original unit:
// CKStreamObject.cpp. DotD only; the names are ours, the reference type from the files (struct draft).
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"

class IKTime;
class SoundStream;
class SoundStreamType;

class CKStreamObject : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x169)
    int32_t IsKindOfClass(uint32_t key) override { return key == 0x5a4c || key == 0xc; }  // vt+0x08 0x9a6cc8
    DOTD_DECLARE_FACTORIES(CKStreamObject)

    CKStreamObject();  // inlined in 0x0011a4a8 CKStreamObject_Create
    ~CKStreamObject() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0011a958 CKStreamObject_Load
    // vt+0x24 0x0011a118 CKStreamObject_RecursiveRegistration: type 0 registers the object with the saving manager.
    void RecursiveRegistration(int32_t type) override;
    // vt+0x30 0x0011a6b0 CKStreamObject_PostLoad: returns 1; vt+0x10 0x0011a720 CKStreamObject_Destroy: empty
    // (IKSerializable's).

    // 0x0011a728 CKStreamObject_Play_maybe: the stream played on `type` (+0x08); `fade` makes the volume ramp from 0 (over
    // +0x10 seconds). The wave records whether the type is "Speech" (+0x218); a music wave needs a length.
    void Play(SoundStreamType* type, int32_t fade);
    // 0x0011a1b8 CKStreamObject_SetFloat20AndInt1C_maybe: the start offset in the item (+0x20) and the item (+0x1c).
    void SetFloat20AndInt1C(float offset, int32_t item);
    // 0x0011a1c8 CKStreamObject_SetVolumeWithFade_maybe: the target volume (+0x2c) and, with a fade time and not `instant`,
    // the ramp's speed (+0x30); else the current volume (+0x34) at once.
    void SetVolumeWithFade(float volume, float fadeTime, int32_t instant);
    // 0x0011a2a8 CKStreamObject_GetStreamState_maybe: the RWA player's state (0 without a player).
    uint32_t GetStreamState() const;
    // 0x0011a2e8 CKStreamObject_GetPlaybackPosition_maybe: the item playing and the seconds played in it (-1 / 0 without a
    // player).
    void GetPlaybackPosition(int32_t* item, float* position) const;
    void Unpause();                               // 0x0011a350 CKStreamObject_Unpause_maybe
    void Resume();                                // 0x0011a380 SoundInstance_Resume_maybe (CKStreamObject_Resume_maybe)
    void Pause();                                 // 0x0011a3c0 SoundInstance_Pause_maybe (CKStreamObject_Pause_maybe)
    void UpdateFader(IKTime* clock);              // 0x0011a4f8 SoundStreamTrack_UpdateFader_maybe
    // 0x0011a538 FUN_0011a538 (CKStreamObject_IsFinished_maybe): 1 without a player, else whether its player has stopped
    // the media for good (MediaStopped with a stop request).
    uint8_t IsFinished() const;
    float GetLength() const;                      // 0x0011a5d8 CKStreamObject_GetLength_maybe: the wave's length
    // The original's "+0x0c is not null": the stream has a player.
    bool HasPlayer() const { return m_pStream != nullptr; }

    // 0x0011a870 CKStreamObject_Stop_maybe: a playing stream (+0x08 set by Play) stopped.
    void Stop(int32_t immediate);
    // 0x0011a6b8 CKStreamObject_ResetRuntime_maybe: volumes 1.0 / 0.0, no stream, no sound id.
    void ResetRuntime();

    IKSerializable* m_pStreamWave;  // +0x04 CKStreamWave in the files
    SoundStreamType* m_pType;       // +0x08 the stream type it plays on (Play); the Load sets null
    SoundStream* m_pStream;         // +0x0c its player, once the player has opened the source; the Load sets null
    float m_unk10;                  // +0x10 the fade-in time of Play
    float m_unk14;                  // +0x14 the fade-out time of Stop
    float m_unk18;                  // +0x18 the player's volume (RwaStreamPlayer_SetVolume)
    int32_t m_unk1c;                // +0x1c the item to select (-1 none; the player takes it); the Load sets -1
    uint32_t m_unk20;               // +0x20 the start offset in it (float bits); the Load sets 0
    uint8_t m_unk24;                // +0x24 a byte from the file: the loop flag (RwaStreamPlayer_SetLoop)
    uint8_t m_pad25[3];
    float m_unk28;                  // +0x28 the volume Play ramps to
    // +0x2c the volume ramp (FloatApproach {target, speed, current}, SoundStreamTrack_UpdateFader_maybe): +0x2c the target
    // (the Load copies +0x28; the constructor sets 0), +0x30 the speed (0), +0x34 the current volume (as +0x2c)
    float m_unk2c;
    float m_unk30;
    float m_unk34;
    uint8_t m_unk38;                // +0x38 paused (Pause 1, Resume 0); not set by the Load or the constructor
    uint8_t m_unk39;                // +0x39 the media stays open after the item (MediaStopped, not NoMedia); the Load sets 0
    uint8_t m_unk3a;                // +0x3a start paused (a pause request on top of the play request)
    uint8_t m_pad3b;
};
DOTD_ASSERT_SIZE(CKStreamObject, 0x3c);
DOTD_ASSERT_OFFSET(CKStreamObject, m_pStreamWave, 0x04);
DOTD_ASSERT_OFFSET(CKStreamObject, m_pType, 0x08);
DOTD_ASSERT_OFFSET(CKStreamObject, m_pStream, 0x0c);
DOTD_ASSERT_OFFSET(CKStreamObject, m_unk10, 0x10);
DOTD_ASSERT_OFFSET(CKStreamObject, m_unk1c, 0x1c);
DOTD_ASSERT_OFFSET(CKStreamObject, m_unk24, 0x24);
DOTD_ASSERT_OFFSET(CKStreamObject, m_unk28, 0x28);
DOTD_ASSERT_OFFSET(CKStreamObject, m_unk34, 0x34);
DOTD_ASSERT_OFFSET(CKStreamObject, m_unk39, 0x39);
DOTD_ASSERT_OFFSET(CKStreamObject, m_unk3a, 0x3a);
