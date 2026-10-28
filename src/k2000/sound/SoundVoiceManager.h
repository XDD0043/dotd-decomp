// SoundVoiceManager.h - the voice and channel pools, the listener and the level's sound dictionaries
// (0x38 bytes; not a registered class). Original unit: SoundVoiceManager.cpp (0x117468-0x11a0c8; Ghidra
// spreads it over SoundVoiceManager_*, SoundEngine_*, SoundBackend_*, SoundChannelSet_*, SoundList_*).
// CKSoundManager_InitializeModule builds it inline (CKSoundManager +0x08). Its Load reads what XXL2's
// CKSoundManager::Load reads: the listener, m_fVoiceRatioVelocity, the coded dictionary ID and the
// dictionaries (XXL2 member names).
//
// Every frame (CKSoundManager::Update -> Update): the stopped instances go back to the free list, the
// others run their state machines, the audible ones are sorted by priority and the first
// m_ui32NbVoices of them may hold a voice; then every voice pushes its parameters to RWA.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/util/TVector.h"

class CKListener;
class CKSound;
class CKSoundDictionaryID;
class IKFile;
class IKSerializable;
class IKTime;
class SoundInstance;
class SoundVoice;
struct SoundNode;

class SoundVoiceManager {
public:
    SoundVoiceManager();                       // inlined in CKSoundManager_InitializeModule (0x113b04)
    void Init();                               // 0x001196a0 SoundVoiceManager_Init_maybe
    int32_t Load(IKFile* file, int32_t type);  // 0x00117860 SoundVoiceManager_Load_maybe

    void AppendSound(CKSound* sound);                          // 0x00117780 SoundList_Append
    void InsertByPriority(SoundInstance* instance);            // 0x00117db8 SoundEngine_InsertByPriority_maybe
    void PauseAll();                                           // 0x00118340 SoundChannelSet_PauseAll_maybe
    void ResumeAll();                                          // 0x001183f0 SoundChannelSet_ResumeAll_maybe
    SoundInstance* AcquireChannel(float startSeconds, CKSound* sound);  // 0x001187b0 SoundVoiceManager_AcquireChannel_maybe
    void CullAndPrioritise();                                  // 0x00118b68 SoundEngine_CullAndPrioritise_maybe
    void Update(IKTime* clock);                                // 0x00118cf8 SoundEngine_Update_maybe
    void StopAll();                                            // 0x00119120 SoundVoiceManager_StopAll_maybe
    // 0x001175c0 SoundBank_StopSectorSounds: every sound of that sector stopped (immediately).
    void StopSectorSounds(int32_t sector);
    // 0x00119000 SoundBank_PlaySectorAutoSounds_maybe: every sound of the coded dictionary that is in the sound list,
    // belongs to that sector and has the auto-play flag (8) is played.
    void PlaySectorAutoSounds(int32_t sector);
    void StopSound(CKSound* sound, uint8_t immediate);         // 0x00119d10 SoundBackend_StopSound_maybe
    void PlaySound(float startSeconds, CKSound* sound);        // 0x00119e50 SoundBackend_PlaySound_maybe
    SoundVoice* FindFreeVoice();
    void StopFlaggedSounds();                                  // 0x001184a0 SoundList_StopFlaggedSounds_maybe                               // 0x00117300 SoundVoicePool_FindFree_maybe (SoundEmitterArray.cpp)

    SoundInstance* m_pPriorityList;   // +0x00 the audible instances, highest priority first (rebuilt each Update)
    SoundVoice* m_aVoices;            // +0x04 the voice pool (OperatorNewArray, 0xc bytes each)
    // +0x08 the output's 0x80 voices minus the stream players (SoundEmitterArray_SumVoiceCounts_maybe):
    // 125 live (two music and one speech player); 128 here until the stream players exist
    uint32_t m_ui32NbVoices;
    CKListener* m_pListener;          // +0x0c
    float m_fVoiceRatioVelocity;      // +0x10 Init 1.0; read after the listener; scales the instances' velocity
    // +0x14 every CKSound of the loaded levels (CKSound_PostLoad -> SoundList_Append), grown by 100
    TVector<CKSound*, 100> m_vpSounds;
    CKSoundDictionaryID* m_pSoundCodedDictionaryID;  // +0x20
    IKSerializable** m_apSoundDictionary;            // +0x24 CKSoundDictionary references (OperatorNewArray)
    uint32_t m_ui32NbSoundDictionary;                // +0x28
    // +0x2c Mem_AllocAligned16(0x10040): its 64-byte aligned 64 KB are zeroed and published to RWA as the
    // stream players' buffer (the words at TOC 0xc11560 / 0xc11564: address, 0x10000)
    void* m_pStreamBuffer;
    SoundNode* m_pFreeInstances;      // +0x30 128 SoundInstances (Init)
    SoundNode* m_pActiveInstances;    // +0x34 the playing ones, newest first
};
DOTD_ASSERT_SIZE(SoundVoiceManager, 0x38);
DOTD_ASSERT_OFFSET(SoundVoiceManager, m_aVoices, 0x04);
DOTD_ASSERT_OFFSET(SoundVoiceManager, m_ui32NbVoices, 0x08);
DOTD_ASSERT_OFFSET(SoundVoiceManager, m_pListener, 0x0c);
DOTD_ASSERT_OFFSET(SoundVoiceManager, m_fVoiceRatioVelocity, 0x10);
DOTD_ASSERT_OFFSET(SoundVoiceManager, m_vpSounds, 0x14);
DOTD_ASSERT_OFFSET(SoundVoiceManager, m_pSoundCodedDictionaryID, 0x20);
DOTD_ASSERT_OFFSET(SoundVoiceManager, m_apSoundDictionary, 0x24);
DOTD_ASSERT_OFFSET(SoundVoiceManager, m_ui32NbSoundDictionary, 0x28);
DOTD_ASSERT_OFFSET(SoundVoiceManager, m_pStreamBuffer, 0x2c);
DOTD_ASSERT_OFFSET(SoundVoiceManager, m_pFreeInstances, 0x30);
DOTD_ASSERT_OFFSET(SoundVoiceManager, m_pActiveInstances, 0x34);
