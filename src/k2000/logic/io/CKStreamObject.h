// CKStreamObject.h - a streamed sound (key 0x5a4c, vtable 0xb19a00, size 0x3c). Original unit:
// CKStreamObject.cpp. DotD only; the names are ours, the reference type from the files (struct draft).
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"

class SoundStreamType;

class CKStreamObject : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x169)
    DOTD_DECLARE_FACTORIES(CKStreamObject)

    CKStreamObject();  // inlined in 0x0011a4a8 CKStreamObject_Create
    ~CKStreamObject() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0011a958 CKStreamObject_Load

    // 0x0011a728 CKStreamObject_Play_maybe: the stream played on `type` (a SoundStreamType; +0x08 set); `fade` makes the
    // volume ramp from 0. STUB(C2.3 audio): see SpeechStreamModel.h: the stream type's players are not ported, a speech
    // stream plays as a clock.
    void Play(SoundStreamType* type, int32_t fade);
    // 0x0011a1b8 CKStreamObject_SetFloat20AndInt1C_maybe: the start offset in the item (+0x20) and the item (+0x1c).
    void SetFloat20AndInt1C(float offset, int32_t item);
    // 0x0011a1c8 CKStreamObject_SetVolumeWithFade_maybe: the target volume (+0x2c) and, with a fade time and not `instant`,
    // the ramp's speed (+0x30); else the current volume (+0x34) at once.
    void SetVolumeWithFade(float volume, float fadeTime, int32_t instant);
    // 0x0011a2e8 CKStreamObject_GetPlaybackPosition_maybe: the item playing and the seconds played in it.
    void GetPlaybackPosition(int32_t* item, float* position) const;
    // FUN_0011a538: 1 without a player, else whether the stream has played its item to the end.
    uint8_t IsFinished() const;
    // The original's "+0x0c is not null": the stream has a player.
    bool HasPlayer() const;

    // 0x0011a870 CKStreamObject_Stop_maybe: a playing stream (+0x08 set by Play) stopped.
    void Stop(int32_t immediate);
    // 0x0011a6b8 CKStreamObject_ResetRuntime_maybe: volumes 1.0 / 0.0, no stream, no sound id.
    void ResetRuntime();

    IKSerializable* m_pStreamWave;  // +0x04 CKStreamWave in the files
    void* m_unk08;                  // +0x08 the Load sets null (a stream type _maybe)
    void* m_unk0c;                  // +0x0c the Load sets null
    float m_unk10;                  // +0x10 a volume _maybe
    float m_unk14;                  // +0x14
    float m_unk18;                  // +0x18
    int32_t m_unk1c;                // +0x1c the Load sets -1
    uint32_t m_unk20;               // +0x20 the Load sets 0
    uint8_t m_unk24;                // +0x24 a byte from the file
    uint8_t m_pad25[3];
    float m_unk28;                  // +0x28
    float m_unk2c;                  // +0x2c the Load copies +0x28; the constructor sets 0
    float m_unk30;                  // +0x30 the Load and the constructor set 0
    float m_unk34;                  // +0x34 the Load copies +0x28; the constructor sets 0
    uint8_t m_unk38;                // +0x38 not set by the Load or the constructor
    uint8_t m_unk39;                // +0x39 the Load sets 0
    uint8_t m_pad3a[2];
};
DOTD_ASSERT_SIZE(CKStreamObject, 0x3c);
DOTD_ASSERT_OFFSET(CKStreamObject, m_pStreamWave, 0x04);
DOTD_ASSERT_OFFSET(CKStreamObject, m_unk08, 0x08);
DOTD_ASSERT_OFFSET(CKStreamObject, m_unk10, 0x10);
DOTD_ASSERT_OFFSET(CKStreamObject, m_unk1c, 0x1c);
DOTD_ASSERT_OFFSET(CKStreamObject, m_unk24, 0x24);
DOTD_ASSERT_OFFSET(CKStreamObject, m_unk28, 0x28);
DOTD_ASSERT_OFFSET(CKStreamObject, m_unk34, 0x34);
DOTD_ASSERT_OFFSET(CKStreamObject, m_unk39, 0x39);
