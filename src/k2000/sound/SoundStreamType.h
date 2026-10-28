// SoundStreamType.h - a named group of sound streams with its volume and fade settings (vtable
// 0xb19a58, 0x134 bytes; not a registered class; no XXL2 counterpart). Original unit: SoundStreamType.cpp
// (0x11d650-0x11ef08). GAME.KP3 defines two, "Musics" and "Speech" (CKSoundStreamManager::Load); the
// music/speech volume accessors find them by m_ui32NameHash (SoundEmitterArray_GetMusicVolume_maybe).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/util/TVector.h"

class IKFile;
class IKTime;

class SoundStreamType {
public:
    SoundStreamType();                                 // 0x0011df10 SoundStreamType_Construct_maybe
    virtual ~SoundStreamType() {}                      // STUB(C1.6): 0x11ee00
    virtual void Load(IKFile* file, int32_t type);     // vt+0x08 0x0011dfd0 SoundStreamType_Load_maybe
    virtual void Save() {}                             // vt+0x0c 0x11e340  STUB(C1.6) (arguments unverified)
    void SetStreamCount(uint32_t count);               // 0x0011ea28 SoundStreamType_SetStreamCount_maybe
    void SnapVolumeToTarget();                         // 0x0011d940 SoundEmitterGroup_SnapVolumeToTarget_maybe
    void SetVolume(float volume);                      // 0x0011d958 SoundEmitterGroup_SetVolume_maybe
    void StartVolumeFade(int32_t fromTarget);          // 0x0011d9f8 SoundStreamType_StartVolumeFade_maybe
    // 0x0011de10 SoundEmitterGroup_StartVolumeFade_maybe: the fade back to the full volume (over +0x124 seconds).
    void ReleaseVolumeFade();
    void PauseInstances();                             // 0x0011dd70 SoundEmitterGroup_PauseInstances_maybe
    void ResumeInstances();                            // 0x0011ddc0 SoundEmitterGroup_ResumeInstances_maybe
    void Update(IKTime* clock);                        // 0x0011e588 SoundStream_Update_maybe (a type method)

    char m_szName[0x100];          // +0x004 not set by the constructor (CKSoundStreamManager copies the name in)
    uint32_t m_ui32NameHash;       // +0x104 Str_HashXor4(m_szName)
    TVector<void*, 2> m_vpStreams; // +0x108 the SoundStreams (0x38 bytes each); the constructor allocates 2 slots
    float m_fVolume;               // +0x114 1.0; the music/speech volume (SoundEmitterGroup_SetVolume_maybe)
    // +0x118 the volume ramp (FloatApproach {target, speed, current}, stepped by Update): +0x118 the
    // target, +0x11c the speed, +0x120 the current volume (what music-flagged sounds are mixed with)
    float m_unk118;
    float m_unk11c;
    float m_unk120;
    float m_unk124;                // +0x124 0.8
    float m_unk128;                // +0x128 0.8; the fade's divisor in StartVolumeFade
    float m_unk12c;                // +0x12c 0.8; caps the fade target in StartVolumeFade
    // +0x130 the stream tracks playing (a node list; SoundStreamType_PlayObject_maybe 0x11e818). None in
    // the front end: no stream player exists until SetStreamCount creates them.
    void* m_unk130;
};
DOTD_ASSERT_SIZE(SoundStreamType, 0x134);
DOTD_ASSERT_OFFSET(SoundStreamType, m_szName, 0x004);
DOTD_ASSERT_OFFSET(SoundStreamType, m_ui32NameHash, 0x104);
DOTD_ASSERT_OFFSET(SoundStreamType, m_vpStreams, 0x108);
DOTD_ASSERT_OFFSET(SoundStreamType, m_fVolume, 0x114);
DOTD_ASSERT_OFFSET(SoundStreamType, m_unk124, 0x124);
DOTD_ASSERT_OFFSET(SoundStreamType, m_unk128, 0x128);
DOTD_ASSERT_OFFSET(SoundStreamType, m_unk12c, 0x12c);
DOTD_ASSERT_OFFSET(SoundStreamType, m_unk130, 0x130);
