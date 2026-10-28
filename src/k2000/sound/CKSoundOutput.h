// CKSoundOutput.h - the sound output: the RWA PS3 driver, the master volume and the level's output
// (reverb) environments (0x28 bytes; not a registered class). Original unit: SoundOutput.cpp
// (0x114510-0x115058; Ghidra names it SoundOutput_* / SoundOutputEffectMgr_*). XXL2:
// K/KModules/KSL/CKSoundOutput.h (m_rwaOutput, m_aEnvironment, m_fVolume, the constructor's 1.0): XXL2
// reads its environments inline, DotD reads references to CKSoundOutputEffect objects.
// CKSoundManager_InitializeModule creates it (CKSoundManager +0x04).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/util/TVector.h"

class CKSoundManager;
class CKSoundOutputEffect;
class IKFile;
class IKSerializable;
struct RwaOutput;

class CKSoundOutput {
public:
    CKSoundOutput();                           // 0x00114858 SoundOutput_Construct_maybe
    void Init();                               // 0x001148d8 SoundOutput_Init_maybe
    int32_t Load(IKFile* file, int32_t type);  // 0x00114bd0 SoundOutput_LoadEffectRefs_maybe
    void SetCurrentEffect(CKSoundOutputEffect* effect);  // 0x00114578 SoundOutputEffectMgr_SetCurrent_maybe
    void ResetOutputEffect();                  // 0x00114b80 SoundOutput_ResetOutputEffect_maybe

    // +0x00 RwaPS3Driver_Create_maybe(0, 0, 4, 0, 0) (Init): platform/audio/rwa.h
    RwaOutput* m_rwaOutput;
    uint32_t m_unk04;  // +0x04 0x80 (Init): the voice budget SoundVoiceManager_Init_maybe shares with the streams
    float m_fVolume;   // +0x08 the master volume, [0, 1]; the constructor sets 1.0
    // +0x0c CKSoundOutputEffect references (XXL2 m_aEnvironment); Init allocates one slot, Load grows
    // it to count + 1
    TVector<IKSerializable*, 1> m_vpEnvironment;
    TVector<IKSerializable*, 1> m_vpUnk18;    // +0x18 a second reference list, same handling; empty in LVL000
    CKSoundOutputEffect* m_pCurrentEffect;    // +0x24 SoundOutputEffectMgr_SetCurrent_maybe; Init sets null
};
DOTD_ASSERT_SIZE(CKSoundOutput, 0x28);
DOTD_ASSERT_OFFSET(CKSoundOutput, m_unk04, 0x04);
DOTD_ASSERT_OFFSET(CKSoundOutput, m_fVolume, 0x08);
DOTD_ASSERT_OFFSET(CKSoundOutput, m_vpEnvironment, 0x0c);
DOTD_ASSERT_OFFSET(CKSoundOutput, m_vpUnk18, 0x18);
DOTD_ASSERT_OFFSET(CKSoundOutput, m_pCurrentEffect, 0x24);

float SoundOutput_GetMasterVolume(CKSoundOutput* output);               // 0x00114510 SoundOutput_GetMasterVolume_maybe
void SoundOutput_SetMasterVolume(float volume, CKSoundOutput* output);  // 0x00114518 SoundOutput_SetMasterVolume_maybe
// CKGameLoop.cpp (CKGameLoop_SetAppActive) calls these with the sound manager; the original passes the
// manager's output (0x000210ec: lwz r3, 4(manager)).
float SoundOutput_GetMasterVolume(CKSoundManager* manager);
void SoundOutput_SetMasterVolume(float volume, CKSoundManager* manager);
