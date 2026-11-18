// CKSoundStreamManager.h - the stream manager: the stream types and the CKStreamWave list (0x1c bytes;
// not a registered class). Original unit: SoundEmitterArray.cpp (0x115b70-0x117468; Ghidra names its
// constructor/Init SoundEmitterArray_*, its Load CKSoundStreamManager_Load_maybe). XXL2's
// CKSoundManager::Load calls m_pSoundStreamManager->Load at the same point; the layout is DotD's.
// CKSoundManager_InitializeModule creates it (CKSoundManager +0x0c).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/util/TVector.h"

class IKFile;
class IKSerializable;
class IKTime;
class SoundStreamType;

class CKSoundStreamManager {
public:
    CKSoundStreamManager();                    // 0x001167a8 SoundEmitterArray_Construct_maybe
    void Init();                               // 0x001161d8 SoundEmitterArray_Init_maybe
    ~CKSoundStreamManager();                   // 0x001167d0 SoundEmitterArray_Destruct_maybe
    // 0x001160c8 SoundEmitterArray_FreeArrays_maybe (CKSoundManager_DestroyModule): both vectors' blocks freed, their
    // lengths and blocks cleared. The stream types themselves are not deleted.
    void FreeArrays();
    // 0x00115b98 SoundEmitterArray_LevelReset_maybe (CKSoundManager's RecursiveRegistration, P21): every stream wave's
    // RecursiveRegistration(type).
    void RecursiveRegistration(int32_t type);
    // 0x001165e0 SoundEmitterArray_DeleteAll_maybe (CKSoundManager_DestroyGame, P21): every stream type deleted (vt+0x04),
    // both lengths 0 (the blocks kept).
    void DeleteAll();
    int32_t Load(IKFile* file, int32_t type);  // 0x00116850 CKSoundStreamManager_Load_maybe
    // 0x00115d60 CKSoundStreamManager_FindOrCreateType_maybe
    SoundStreamType* FindOrCreateType(const char* name, uint32_t streamCount);
    void SnapVolumes();                         // 0x00116250 SoundEmitterArray_SnapVolumes_maybe
    uint32_t SumVoiceCounts();                  // 0x001162c0 SoundEmitterArray_SumVoiceCounts_maybe
    void ResumeAll();                           // 0x00116388 SoundEmitterArray_ResumeAll_maybe
    void PauseAll();                            // 0x001163f8 SoundEmitterArray_PauseAll_maybe
    void ResetEntries();                        // 0x00116468 SoundList_ResetEntries_maybe
    void CallNopHookOnEntries();                // 0x001164d8 SoundStreams_CallNopHookOnEntries_maybe
    void UpdateAll(IKTime* clock);              // 0x00116548 SoundStreams_UpdateAll_maybe
    // the "Musics" / "Speech" types' volumes (found by name hash; the PS3 reads a null type's fields
    // when one is missing)
    float GetMusicVolume();                     // 0x00116cb8 SoundEmitterArray_GetMusicVolume_maybe
    float GetMusicCurrentVolume();              // 0x00116d60 SoundEmitterArray_GetMusicCurrentVolume_maybe
    void SetSpeechVolume(float volume);         // 0x00116e30 SoundEmitterArray_SetSpeechVolume_maybe
    float GetSpeechVolume();                    // 0x00116ef0 SoundEmitterArray_GetSpeechVolume_maybe
    float GetSpeechCurrentVolume();             // 0x00116f98 SoundEmitterArray_GetSpeechCurrentVolume_maybe
    void SetMusicVolume(float volume);          // 0x00117040 SoundEmitterArray_SetMusicVolume_maybe
    SoundStreamType* FindTypeByName(const char* name);
    // 0x00115f38 SoundEmitterArray_TestAllGroups_maybe: 0 all players inactive, 1 settled, 2 in RWA state 9
    uint8_t TestAllGroups(int32_t test);
    void Unsuspend();                           // 0x00116308 SoundEmitterArray_Unsuspend_maybe
    void Suspend();                             // 0x00116690 SoundEmitterArray_Suspend_maybe  // the inlined hash search of the six above

    TVector<SoundStreamType*, 2> m_vpStreamTypes;  // +0x00 "Musics", "Speech" after GAME.KP3
    TVector<IKSerializable*, 2> m_vpStreamWaves;   // +0x0c the CKStreamWave references (GAME.KP3: 143)
    uint8_t m_unk18;                               // +0x18 Init sets 0; Suspend 1 (music-flagged sounds refuse to play), Unsuspend 0
    uint8_t m_pad19[3];
};
DOTD_ASSERT_SIZE(CKSoundStreamManager, 0x1c);
DOTD_ASSERT_OFFSET(CKSoundStreamManager, m_vpStreamWaves, 0x0c);
DOTD_ASSERT_OFFSET(CKSoundStreamManager, m_unk18, 0x18);
