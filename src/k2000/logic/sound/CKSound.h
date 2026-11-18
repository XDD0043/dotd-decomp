// CKSound.h - one sound of a level (key 0x2acc, vtable 0xb197d8, size 0x74). Original unit: CKSound.cpp
// (0x110e40-0x1122f8). XXL2: K/KModules/KSL/CKSound.h. DotD reads a CKWave reference where XXL2 reads a
// sound id (XXL2's PostLoad looks the wave up from it), has four more floats after XXL2's volume/pitch/pan
// and two more words after the flags; the rest (flags 0x10 = attached to a scene leaf, else a position;
// distances, pause time, bounding box, sector) is XXL2's order. LVL000 holds 446.
//
// Playing: CKSound::Play (0x111230) hands the sound to the voice manager (SoundVoiceManager::PlaySound),
// which takes a SoundInstance from its free list and links it on m_pInstances; the instances' state
// machines run in CKSoundManager::Update. Names of the floats come from their setters and readers.
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"
#include "k2000/math/CMatrix34.h"

class CKWave;
class SoundInstance;
struct SoundNode;

class CKSound : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0xab)
    int32_t IsKindOfClass(uint32_t key) override { return key == 0x2acc || key == 0xc; }  // vt+0x08 0x9a6988
    DOTD_DECLARE_FACTORIES(CKSound)

    // m_SoundFlags bits (the readers in CKSound.cpp, SoundVoiceManager.cpp, SoundInstance.cpp)
    enum : uint32_t {
        kFlagBoundingBox = 0x1,   // heard only inside m_BoundingBox (SoundEngine_CullAndPrioritise_maybe)
        kFlagLoop = 0x2,          // CKSound_SetLoop_maybe
        kFlagPan = 0x4,           // positioned on a circle around the listener from m_fPan
        kFlagAttached = 0x10,     // follows m_pLeafObjectAttached
        kFlagMultiInstance = 0x40,  // several instances (up to m_ui32MaxInstances); else a new Play restarts
        kFlagMusic = 0x80,        // mixed with the music volume
        kFlagDelayFirst = 0x100,  // the first instance waits m_fPauseTime
    };

    CKSound();                                          // 0x00111310 CKSound_Create (inlined)
    // 0x009a6a28 / 0x009a69a8 CKSound_Destructor / _DeletingDestructor: the instance list's nodes back to their pool
    // (FreeListPool 0x00ceaa34 in the original; SoundNode_Free), the list cleared. The instances stay with the voice manager.
    ~CKSound() override;
    // vt+0x10 0x00111610 CKSound_Destroy: the sound leaves the voice manager's sound list (SoundList_Remove 0x1173c8).
    void Destroy() override;
    int32_t MessageProc(uint16_t message, void* data) override;  // vt+0x1c 0x00111728 CKSound_MessageProc
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00111d08 CKSound_Load
    int32_t PostLoad(int32_t type) override;            // vt+0x30 0x00111ae0 CKSound_PostLoad

    void SetSpeed(float speed);                   // 0x00110e98 CKSound_SetSpeed_maybe
    void SetPitch(float pitch);                   // 0x00110ea0 CKSound_SetPitch_maybe
    void SetBaseVolume(float volume);             // 0x00110ee8 CKSound_SetBaseVolume_maybe
    void SetVolume(float volume);                 // 0x00110f10 CKSound_SetVolume_maybe
    void SetPosition(const CVector3* position);   // 0x00110fa0 CKSound_SetPosition
    void SetLoop(int32_t loop);                   // 0x00110fd0 CKSound_SetLoop_maybe
    CVector3* GetPosition();                      // 0x00110ff0 CKSound_GetPosition
    CKWave* GetSample();                          // 0x00111000 CKSound_GetSample_maybe
    IKSerializable* GetAttachedNode();            // 0x00111008 CKSound_GetAttachedNode_maybe
    SoundInstance* GetInstanceAt(uint32_t index); // 0x00111050 CKSound_GetInstanceAt_maybe
    float GetRandomVolumeOffset();                // 0x00111158 CKSound_GetRandomVolumeOffset_maybe
    int32_t Stop(uint8_t immediate);              // 0x001111b0 Sound_Stop
    int32_t Play(float startSeconds);             // 0x00111230 CKSound_Play
    int32_t SetAttachObject(IKSerializable* node);  // 0x00111350 CKSound_SetAttachObject
    float ComputePlaybackRate();                  // 0x001113c0 SoundInstance_ComputePlaybackRate_maybe
    uint32_t IsPlaying();                         // 0x00111568 CKSound_IsPlaying_maybe
    void UpdatePan();                             // 0x00111818 CKSound_UpdatePan_maybe
    void ResetPan(int32_t pan);                   // 0x00111b70 CKSound_ResetPan_maybe
    uint32_t CountInstances() const;              // the inlined list walk (m_pInstances)

    float m_fVolume;          // +0x04 read first (XXL2 reads m_fVolume first); 0.6 or 1.0 in LVL000; SetBaseVolume
    float m_fRandomVolume;    // +0x08 scales the random volume offset (GetRandomVolumeOffset)
    float m_fSpeed;           // +0x0c 1.0 in LVL000; SetSpeed; multiplies the playback rate
    float m_fRandomPitch;     // +0x10 a random addition to the playback rate when non-zero
    // +0x14 CKSound_UpdatePan_maybe (PostLoad, flag 4) turns it into a position on a 10-unit circle:
    // angle (pan + 1) * pi/2, as XXL2's PostLoad does with m_fPan.
    float m_fPan;
    float m_fFadeInTime;      // +0x18 seconds; 0 starts an instance at full volume (state 1, not 0)
    float m_fFadeOutTime;     // +0x1c seconds; the end of a one-shot and Stop(0) fade over it
    float m_fVolumeScale;     // +0x20 PostLoad sets 1.0; SetVolume
    float m_fPitch;           // +0x24 PostLoad sets 1.0; SetPitch (clamped to [0.01, 10])
    // +0x28 the scene leaf the sound follows (XXL2 TRestrictedPointer<CSGLeaf>; Ghidra: CSGBranch*),
    // read when m_SoundFlags has 0x10, else null
    IKSerializable* m_pLeafObjectAttached;
    // +0x2c read (12 bytes, one read) without flag 0x10; with it, the zero vector (0x00c50d64)
    CVector3 m_v3LeafPosition;
    float m_fDistanceMin;     // +0x38 15.0 in LVL000
    float m_fDistanceMax;     // +0x3c 40.0 in LVL000; beyond it no voice
    float m_fPauseTime;       // +0x40 the delay before (flag 0x100) or between (looping) plays
    // +0x44 XXL2 CBBox (0x18 bytes, one read): max (15, 15, 15) then min (-15, -15, -15) in LVL000
    float m_BoundingBox[6];
    uint32_t m_SoundFlags;    // +0x5c XXL2 CBitArray: kFlag*
    uint32_t m_ui32MaxInstances;  // +0x60 16 in LVL000 (with kFlagMultiInstance)
    // +0x64 what Play does when m_ui32MaxInstances play: 1 stops the oldest, 2 fades it out (stops it
    // without a fade-out time), others refuse
    uint32_t m_eInstanceMode;
    SoundNode* m_pInstances;  // +0x68 the playing SoundInstances (newest first); Create sets null
    CKWave* m_pKWave;         // +0x6c read first
    uint32_t m_iSectorIndex;  // +0x70 KSectorIndex, read last
};
DOTD_ASSERT_SIZE(CKSound, 0x74);
DOTD_ASSERT_OFFSET(CKSound, m_fVolume, 0x04);
DOTD_ASSERT_OFFSET(CKSound, m_fRandomVolume, 0x08);
DOTD_ASSERT_OFFSET(CKSound, m_fSpeed, 0x0c);
DOTD_ASSERT_OFFSET(CKSound, m_fRandomPitch, 0x10);
DOTD_ASSERT_OFFSET(CKSound, m_fPan, 0x14);
DOTD_ASSERT_OFFSET(CKSound, m_fFadeInTime, 0x18);
DOTD_ASSERT_OFFSET(CKSound, m_fFadeOutTime, 0x1c);
DOTD_ASSERT_OFFSET(CKSound, m_fVolumeScale, 0x20);
DOTD_ASSERT_OFFSET(CKSound, m_fPitch, 0x24);
DOTD_ASSERT_OFFSET(CKSound, m_pLeafObjectAttached, 0x28);
DOTD_ASSERT_OFFSET(CKSound, m_v3LeafPosition, 0x2c);
DOTD_ASSERT_OFFSET(CKSound, m_fDistanceMin, 0x38);
DOTD_ASSERT_OFFSET(CKSound, m_fDistanceMax, 0x3c);
DOTD_ASSERT_OFFSET(CKSound, m_fPauseTime, 0x40);
DOTD_ASSERT_OFFSET(CKSound, m_BoundingBox, 0x44);
DOTD_ASSERT_OFFSET(CKSound, m_SoundFlags, 0x5c);
DOTD_ASSERT_OFFSET(CKSound, m_ui32MaxInstances, 0x60);
DOTD_ASSERT_OFFSET(CKSound, m_eInstanceMode, 0x64);
DOTD_ASSERT_OFFSET(CKSound, m_pInstances, 0x68);
DOTD_ASSERT_OFFSET(CKSound, m_pKWave, 0x6c);
DOTD_ASSERT_OFFSET(CKSound, m_iSectorIndex, 0x70);

// The original's free functions, for the callers in other units (menus, game manager, hooks).
inline int32_t CKSound_Play(float startSeconds, CKSound* sound) { return sound->Play(startSeconds); }  // 0x00111230
inline int32_t Sound_Stop(CKSound* sound, uint8_t immediate) { return sound->Stop(immediate); }       // 0x001111b0
inline uint32_t CKSound_IsPlaying(CKSound* sound) { return sound->IsPlaying(); }                     // 0x00111568
inline void CKSound_SetLoop(CKSound* sound, int32_t loop) { sound->SetLoop(loop); }                   // 0x00110fd0
inline void CKSound_ResetPan(CKSound* sound, int32_t pan) { sound->ResetPan(pan); }                   // 0x00111b70
inline void CKSound_SetVolume(float volume, CKSound* sound) { sound->SetVolume(volume); }             // 0x00110f10
inline void CKSound_SetPitch(float pitch, CKSound* sound) { sound->SetPitch(pitch); }                 // 0x00110ea0
