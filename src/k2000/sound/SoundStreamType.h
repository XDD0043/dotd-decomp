// SoundStreamType.h - a named group of sound streams with its volume and fade settings (vtable
// 0xb19a58, 0x134 bytes; not a registered class; no XXL2 counterpart). Original unit: SoundStreamType.cpp
// (0x11d650-0x11ef08). GAME.KP3 defines two, "Musics" and "Speech" (CKSoundStreamManager::Load); the
// music/speech volume accessors find them by m_ui32NameHash (SoundEmitterArray_GetMusicVolume_maybe).
// The type owns its stream players (+0x108: two for "Musics" (CKSrvMusic_PostLoad), one for "Speech"
// (CKSrvSekensor_PostLoad)) and lists the CKStreamObjects playing on it (+0x130); an object waits there until a player
// is free.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/util/TVector.h"

class CKStreamObject;
class IKFile;
class IKTime;
class SoundStream;

// A node of the track list (+0x130): FreeListPool 0xceaa30 nodes (8 bytes), as the streams' request stacks.
struct SoundStreamTrack {
    CKStreamObject* m_pObject;
    SoundStreamTrack* m_pNext;
};
DOTD_ASSERT_SIZE(SoundStreamTrack, 0x8);

class SoundStreamType {
public:
    SoundStreamType();                                 // 0x0011df10 SoundStreamType_Construct_maybe
    virtual ~SoundStreamType();                        // 0x0011ee00 / 0x0011ece8 SoundStreamType_Destructor_maybe / _DeletingDestructor_maybe
    virtual void Load(IKFile* file, int32_t type);     // vt+0x08 0x0011dfd0 SoundStreamType_Load_maybe
    virtual void Save(IKFile* file, int32_t type);     // vt+0x0c 0x0011e340 SoundStreamType_Save_maybe
    void SetStreamCount(uint32_t count);               // 0x0011ea28 SoundStreamType_SetStreamCount_maybe
    void DestroyVoices();                              // 0x0011d7e0 SoundEmitterGroup_DestroyVoices_maybe
    void RemovePending(CKStreamObject* object);        // 0x0011d650 SoundStreamType_RemovePending_maybe
    void SnapVolumeToTarget();                         // 0x0011d940 SoundEmitterGroup_SnapVolumeToTarget_maybe
    void SetVolume(float volume);                      // 0x0011d958 SoundEmitterGroup_SetVolume_maybe
    uint8_t AreAllVoicesInactive();                    // 0x0011d980 SoundEmitterGroup_AreAllVoicesInactive_maybe
    void StartVolumeFade(int32_t fromTarget);          // 0x0011d9f8 SoundStreamType_StartVolumeFade_maybe
    uint8_t AreAllVoicesState9();                      // 0x0011dad0 SoundEmitterGroup_AreAllVoicesState9_maybe
    void UnpauseObject(CKStreamObject* object);        // 0x0011db78 SoundStreamType_UnpauseObject_maybe
    void ResumeVoiceOf(CKStreamObject* object);        // 0x0011dc20 SoundEmitterGroup_ResumeVoiceOf_maybe
    void PauseVoiceOf(CKStreamObject* object);         // 0x0011dcc8 SoundEmitterGroup_PauseVoiceOf_maybe
    // 0x0011de10 SoundEmitterGroup_StartVolumeFade_maybe: the fade back to the full volume (over +0x124 seconds).
    void ReleaseVolumeFade();
    void PauseInstances();                             // 0x0011dd70 SoundEmitterGroup_PauseInstances_maybe
    void ResumeInstances();                            // 0x0011ddc0 SoundEmitterGroup_ResumeInstances_maybe
    uint8_t AreAllVoicesSettled();                     // 0x0011de70 SoundEmitterGroup_AreAllVoicesSettled_maybe
    void StopObject(CKStreamObject* object);           // 0x0011e1b0 SoundStreamType_StopObject_maybe
    void Update(IKTime* clock);                        // 0x0011e588 SoundStream_Update_maybe (a type method)
    void PlayObject(CKStreamObject* object);           // 0x0011e818 SoundStreamType_PlayObject_maybe

    char m_szName[0x100];          // +0x004 not set by the constructor (CKSoundStreamManager copies the name in)
    uint32_t m_ui32NameHash;       // +0x104 Str_HashXor4(m_szName)
    TVector<SoundStream*, 2> m_vpStreams;  // +0x108 the stream players (0x38 bytes each); the constructor allocates 2 slots
    float m_fVolume;               // +0x114 1.0; the music/speech volume (SoundEmitterGroup_SetVolume_maybe)
    // +0x118 the volume ramp (FloatApproach {target, speed, current}, stepped by Update): +0x118 the
    // target, +0x11c the speed, +0x120 the current volume (what music-flagged sounds and the streams are mixed with)
    float m_unk118;
    float m_unk11c;
    float m_unk120;
    float m_unk124;                // +0x124 0.8
    float m_unk128;                // +0x128 0.8; the fade's divisor in StartVolumeFade
    float m_unk12c;                // +0x12c 0.8; caps the fade target in StartVolumeFade
    SoundStreamTrack* m_pTracks;   // +0x130 the objects playing on this type, newest first (PlayObject)
};
DOTD_ASSERT_SIZE(SoundStreamType, 0x134);
DOTD_ASSERT_OFFSET(SoundStreamType, m_szName, 0x004);
DOTD_ASSERT_OFFSET(SoundStreamType, m_ui32NameHash, 0x104);
DOTD_ASSERT_OFFSET(SoundStreamType, m_vpStreams, 0x108);
DOTD_ASSERT_OFFSET(SoundStreamType, m_fVolume, 0x114);
DOTD_ASSERT_OFFSET(SoundStreamType, m_unk120, 0x120);
DOTD_ASSERT_OFFSET(SoundStreamType, m_unk124, 0x124);
DOTD_ASSERT_OFFSET(SoundStreamType, m_unk128, 0x128);
DOTD_ASSERT_OFFSET(SoundStreamType, m_unk12c, 0x12c);
DOTD_ASSERT_OFFSET(SoundStreamType, m_pTracks, 0x130);
