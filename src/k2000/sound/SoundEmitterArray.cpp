// SoundEmitterArray.cpp - reconstructed original translation unit 0x115b70-0x117468 (GAME_TOC1, main_toc1), 38 functions, 33 live.
// Primary owner: SoundEmitterArray (not a registered class)
// Other owners: CKSoundStreamManager (3), SoundList (2), SoundStreams (2), PtrList (1), SoundVoicePool (1), SoundVoiceManager (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x115b70  SoundEmitterArray_Construct_2_maybe  [dead]
//   [x] 0x115b98  SoundEmitterArray_LevelReset_maybe  (CKSoundStreamManager::RecursiveRegistration)
//   [x] 0x115c38  StaticInitAndDestruction_115c38  (s_streamTypeHashes)
//   [ ] 0x115cb8  _GLOBAL__I_115cb8
//   [x] 0x115cc8  PtrList_FindByNameHash_maybe
//   [x] 0x115d60  CKSoundStreamManager_FindOrCreateType_maybe
//   [x] 0x115f38  SoundEmitterArray_TestAllGroups_maybe
//   [x] 0x1160c8  SoundEmitterArray_FreeArrays_maybe
//   [ ] 0x116158  SoundEmitterArray_Destruct_2_maybe  [dead]
//   [x] 0x1161d8  SoundEmitterArray_Init_maybe
//   [x] 0x116250  SoundEmitterArray_SnapVolumes_maybe
//   [x] 0x1162c0  SoundEmitterArray_SumVoiceCounts_maybe
//   [x] 0x116308  SoundEmitterArray_Unsuspend_maybe
//   [x] 0x116388  SoundEmitterArray_ResumeAll_maybe
//   [x] 0x1163f8  SoundEmitterArray_PauseAll_maybe
//   [x] 0x116468  SoundList_ResetEntries_maybe
//   [x] 0x1164d8  SoundStreams_CallNopHookOnEntries_maybe
//   [x] 0x116548  SoundStreams_UpdateAll_maybe
//   [x] 0x1165e0  SoundEmitterArray_DeleteAll_maybe  (CKSoundStreamManager::DeleteAll)
//   [x] 0x116690  SoundEmitterArray_Suspend_maybe
//   [ ] 0x116728  SoundEmitterArray_CountStreamsInState3_maybe  [dead]
//   [x] 0x1167a8  SoundEmitterArray_Construct_maybe
//   [x] 0x1167d0  SoundEmitterArray_Destruct_maybe
//   [x] 0x116850  CKSoundStreamManager_Load_maybe
//   [ ] 0x116ad0  CKSoundStreamManager_Save_maybe  [dead]
//   [x] 0x116cb8  SoundEmitterArray_GetMusicVolume_maybe
//   [x] 0x116d60  SoundEmitterArray_GetMusicCurrentVolume_maybe
//   [x] 0x116e30  SoundEmitterArray_SetSpeechVolume_maybe
//   [x] 0x116ef0  SoundEmitterArray_GetSpeechVolume_maybe
//   [x] 0x116f98  SoundEmitterArray_GetSpeechCurrentVolume_maybe
//   [x] 0x117040  SoundEmitterArray_SetMusicVolume_maybe
//   [ ] 0x117100  SoundEmitterArray_UpdateStreamsAndCheckAll_maybe  [dead: no pointer to its descriptor; its only call is from the dead 0x113f00 FUN_00113f00]
//   [ ] 0x1172f0  KStub_Return128_1172f0  [dead]
//   [x] 0x1172f8  KStub_Nop_1172f8  (empty: CKSoundManager::Start's call (its note))
//   [x] 0x117300  SoundVoicePool_FindFree_maybe
//   [x] 0x117368  SoundVoiceManager_LevelReset_maybe  (SoundVoiceManager::RecursiveRegistration)
//   [x] 0x1173c0  KStub_Nop_1173c0  (CKSoundManager::SectorUnload's empty call)
//   [x] 0x1173c8  SoundList_Remove
#include "k2000/sound/CKSoundStreamManager.h"

#include <cstring>

#include "k2000/core/IKSerializable.h"
#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"
#include "k2000/dictionaries/CKSoundDictionaryID.h"
#include "k2000/misc/CKGameLoop.h"
#include "k2000/misc/Engine.h"
#include "k2000/sound/SoundStreamType.h"
#include "k2000/managers/CKSoundManager.h"
#include "k2000/sound/SoundVoice.h"
#include "k2000/sound/SoundVoiceManager.h"

namespace {

// Local copies of 0x000107d8 Str_HashXor4 (misc/Wcs.cpp) and 0x00011248 Str_CopyBounded (misc/Str.cpp),
// not ported yet.
uint32_t Str_HashXor4(const char* s) {
    uint8_t acc[4] = {0, 0, 0, 0};
    for (uint32_t i = 0; s[i] != 0; ++i) acc[i & 3] ^= static_cast<uint8_t>(s[i]);
    return static_cast<uint32_t>(acc[0]) | (static_cast<uint32_t>(acc[1]) << 8) | (static_cast<uint32_t>(acc[2]) << 16) |
           (static_cast<uint32_t>(acc[3]) << 24);
}
void Str_CopyBounded(char* dst, const char* src, uint32_t size) {
    if (std::strlen(src) >= size) {
        std::strncpy(dst, src, size - 1);
        dst[size - 1] = 0;
        return;
    }
    std::strcpy(dst, src);
}

const char kNoName[] = "";  // 0x00ac6a58 (TOC 0xc1152c): the name a type has until its Load

const char kMusics[] = "Musics";  // 0x00ac6a60 (0x00c4b154)
const char kSpeech[] = "Speech";  // 0x00ac6a68 (0x00c4b158)
// 0x00ceac5a: set by CellSysutilCallback while the system (XMB) music plays: the game's music is then
// silent. The platform sends no such event.
uint8_t g_systemMusicPlaying = 0;

// 0x00115c38 StaticInitAndDestruction_115c38 (P21): the two type names' hashes (Str_HashXor4) in the static pair of TOC
// -0x44bc. Only this initialiser loads that slot; the volume functions hash the names again.
[[maybe_unused]] const uint32_t s_streamTypeHashes[2] = {Str_HashXor4(kMusics), Str_HashXor4(kSpeech)};

}  // namespace

// 0x00115b98 SoundEmitterArray_LevelReset_maybe
void CKSoundStreamManager::RecursiveRegistration(int32_t type) {
    for (uint32_t i = 0; i < m_vpStreamWaves.m_ui32NbUsedElt; ++i) m_vpStreamWaves.m_pBlock[i]->RecursiveRegistration(type);
}

// 0x001165e0 SoundEmitterArray_DeleteAll_maybe
void CKSoundStreamManager::DeleteAll() {
    for (uint32_t i = 0; i < m_vpStreamTypes.m_ui32NbUsedElt; ++i) {
        SoundStreamType* streamType = m_vpStreamTypes.m_pBlock[i];
        if (streamType != nullptr) delete streamType;  // vt+0x04 (the block's slot is left)
    }
    m_vpStreamTypes.m_ui32NbUsedElt = 0;
    m_vpStreamWaves.m_ui32NbUsedElt = 0;
}

// 0x00117368 SoundVoiceManager_LevelReset_maybe (P21): type 0: the coded dictionary's RecursiveRegistration(0).
void SoundVoiceManager::RecursiveRegistration(int32_t type) {
    if (type == 0) m_pSoundCodedDictionaryID->RecursiveRegistration(0);
}

// 0x001167a8 SoundEmitterArray_Construct_maybe. The stores in the original's order.
// 0x001160c8 SoundEmitterArray_FreeArrays_maybe
void CKSoundStreamManager::FreeArrays() {
    if (m_vpStreamTypes.m_pBlock != nullptr) {
        Mem_FreeAligned16(m_vpStreamTypes.m_pBlock);
        m_vpStreamTypes.m_pBlock = nullptr;
    }
    m_vpStreamTypes.m_pBlock = nullptr;
    m_vpStreamTypes.m_ui32NbUsedElt = 0;
    if (m_vpStreamWaves.m_pBlock != nullptr) {
        Mem_FreeAligned16(m_vpStreamWaves.m_pBlock);
        m_vpStreamWaves.m_pBlock = nullptr;
    }
    m_vpStreamWaves.m_ui32NbUsedElt = 0;
    m_vpStreamWaves.m_pBlock = nullptr;
}

// 0x001167d0 SoundEmitterArray_Destruct_maybe: the same, the wave references first.
CKSoundStreamManager::~CKSoundStreamManager() {
    if (m_vpStreamWaves.m_pBlock != nullptr) Mem_FreeAligned16(m_vpStreamWaves.m_pBlock);
    m_vpStreamWaves.m_ui32NbUsedElt = 0;
    m_vpStreamWaves.m_pBlock = nullptr;
    if (m_vpStreamTypes.m_pBlock != nullptr) Mem_FreeAligned16(m_vpStreamTypes.m_pBlock);
    m_vpStreamTypes.m_ui32NbUsedElt = 0;
    m_vpStreamTypes.m_pBlock = nullptr;
}

CKSoundStreamManager::CKSoundStreamManager() {
    m_vpStreamTypes.m_pBlock = nullptr;
    m_vpStreamTypes.m_ui32NbUsedElt = 0;
    m_vpStreamTypes.m_ui32NbElt = 2;
    m_vpStreamWaves.m_ui32NbElt = 2;
    m_vpStreamWaves.m_ui32NbUsedElt = 0;
    m_vpStreamWaves.m_pBlock = nullptr;
}

// 0x001161d8 SoundEmitterArray_Init_maybe
void CKSoundStreamManager::Init() {
    m_vpStreamTypes.m_ui32NbElt = 2;
    m_vpStreamTypes.m_pBlock = static_cast<SoundStreamType**>(Mem_AllocAligned16(2 * static_cast<uint32_t>(sizeof(void*))));
    m_vpStreamWaves.m_ui32NbElt = 2;
    m_vpStreamWaves.m_pBlock = static_cast<IKSerializable**>(Mem_AllocAligned16(2 * static_cast<uint32_t>(sizeof(void*))));
    m_unk18 = 0;
}

// 0x00115d60 CKSoundStreamManager_FindOrCreateType_maybe
SoundStreamType* CKSoundStreamManager::FindOrCreateType(const char* name, uint32_t streamCount) {
    for (uint32_t i = 0; i < m_vpStreamTypes.m_ui32NbUsedElt; ++i) {
        SoundStreamType* type = m_vpStreamTypes.m_pBlock[i];
        if (std::strcmp(type->m_szName, name) == 0) return type;
    }
    SoundStreamType* type = new SoundStreamType();  // OperatorNew(0x134)
    type->SetStreamCount(streamCount);
    Str_CopyBounded(type->m_szName, name, 0x100);
    type->m_ui32NameHash = Str_HashXor4(type->m_szName);
    const uint32_t size = m_vpStreamTypes.m_ui32NbUsedElt;
    if (m_vpStreamTypes.m_ui32NbElt == size) {
        uint32_t capacity = size + 2;
        uint32_t bytes = capacity * static_cast<uint32_t>(sizeof(SoundStreamType*));
        if (capacity == 0) {  // as in the original (cannot happen)
            capacity = 2;
            bytes = 2 * static_cast<uint32_t>(sizeof(SoundStreamType*));
        }
        m_vpStreamTypes.m_pBlock = static_cast<SoundStreamType**>(Mem_ReallocAligned16(m_vpStreamTypes.m_pBlock, bytes));
        m_vpStreamTypes.m_ui32NbElt = capacity;
    }
    m_vpStreamTypes.m_pBlock[m_vpStreamTypes.m_ui32NbUsedElt] = type;
    ++m_vpStreamTypes.m_ui32NbUsedElt;
    return type;
}

// 0x00116850 CKSoundStreamManager_Load_maybe: GAME.KP3 only. The stream waves, then the stream types:
// each loop asks for a type named "" (none after the first Load has named it), so each creates one.
int32_t CKSoundStreamManager::Load(IKFile* file, int32_t type) {
    if (type != K_GAME_PLATEFORMS) return 1;
    uint32_t count = 0;
    ReadU32LE(file, &count);
    if (count != 0) {
        if (m_vpStreamWaves.m_ui32NbElt < count) {
            uint32_t capacity = (count & ~1u) + 2;
            uint32_t bytes = capacity * static_cast<uint32_t>(sizeof(IKSerializable*));
            if (capacity == 0) {  // as in the original (cannot happen)
                capacity = 2;
                bytes = 2 * static_cast<uint32_t>(sizeof(IKSerializable*));
            }
            m_vpStreamWaves.m_pBlock = static_cast<IKSerializable**>(Mem_ReallocAligned16(m_vpStreamWaves.m_pBlock, bytes));
            m_vpStreamWaves.m_ui32NbElt = capacity;
        }
        m_vpStreamWaves.m_ui32NbUsedElt = count;
        IKFile_ReadObjectRefArray(file, m_vpStreamWaves.m_pBlock, count);
    }
    ReadU32LE(file, &count);
    if (count == 0) return 1;
    uint32_t i = 0;
    do {
        ++i;
        if (g_pEngine->m_gameLoop->IsExitRequested() != 0) return 0;
        FindOrCreateType(kNoName, 1)->Load(file, K_GAME_PLATEFORMS);
    } while (i < count);
    return 1;
}

// 0x00116250 SoundEmitterArray_SnapVolumes_maybe
void CKSoundStreamManager::SnapVolumes() {
    for (uint32_t i = 0; i < m_vpStreamTypes.m_ui32NbUsedElt; ++i) m_vpStreamTypes.m_pBlock[i]->SnapVolumeToTarget();
}

// 0x001162c0 SoundEmitterArray_SumVoiceCounts_maybe: the stream players of all types (+0x110 each; one RWA voice each).
uint32_t CKSoundStreamManager::SumVoiceCounts() {
    uint32_t sum = 0;
    for (uint32_t i = 0; i < m_vpStreamTypes.m_ui32NbUsedElt; ++i) sum += m_vpStreamTypes.m_pBlock[i]->m_vpStreams.m_ui32NbUsedElt;
    return sum;
}

// 0x00116388 SoundEmitterArray_ResumeAll_maybe
void CKSoundStreamManager::ResumeAll() {
    for (uint32_t i = 0; i < m_vpStreamTypes.m_ui32NbUsedElt; ++i) m_vpStreamTypes.m_pBlock[i]->ResumeInstances();
}

// 0x001163f8 SoundEmitterArray_PauseAll_maybe
void CKSoundStreamManager::PauseAll() {
    for (uint32_t i = 0; i < m_vpStreamTypes.m_ui32NbUsedElt; ++i) m_vpStreamTypes.m_pBlock[i]->PauseInstances();
}

// 0x00116468 SoundList_ResetEntries_maybe (CKSoundManager_Restart): KStub_Nop_11d638 on every type.
void CKSoundStreamManager::ResetEntries() {}

// 0x001164d8 SoundStreams_CallNopHookOnEntries_maybe: KStub_Nop_11d630 on every type.
void CKSoundStreamManager::CallNopHookOnEntries() {}

// 0x00116548 SoundStreams_UpdateAll_maybe
void CKSoundStreamManager::UpdateAll(IKTime* clock) {
    // KStub_Nop_106d8(6, "--Streams--"): a debug print
    for (uint32_t i = 0; i < m_vpStreamTypes.m_ui32NbUsedElt; ++i) m_vpStreamTypes.m_pBlock[i]->Update(clock);
}

// 0x00115cc8 PtrList_FindByNameHash_maybe: the first type whose name hash (+0x104) is the name's; null when none.
SoundStreamType* CKSoundStreamManager::FindTypeByName(const char* name) {
    const uint32_t hash = Str_HashXor4(name);
    for (uint32_t i = 0; i < m_vpStreamTypes.m_ui32NbUsedElt; ++i) {
        if (m_vpStreamTypes.m_pBlock[i]->m_ui32NameHash == hash) return m_vpStreamTypes.m_pBlock[i];
    }
    return nullptr;  // BUG(original): the callers read this null type's fields
}

// 0x00116cb8 SoundEmitterArray_GetMusicVolume_maybe (the manager comes from g_pEngine, not `this`)
float CKSoundStreamManager::GetMusicVolume() {
    return g_pEngine->m_soundManager->m_pSoundStreamManager->FindTypeByName(kMusics)->m_fVolume;
}

// 0x00116d60 SoundEmitterArray_GetMusicCurrentVolume_maybe: 0 while the system music plays.
float CKSoundStreamManager::GetMusicCurrentVolume() {
    if (g_systemMusicPlaying != 0) return 0.0f;
    return g_pEngine->m_soundManager->m_pSoundStreamManager->FindTypeByName(kMusics)->m_unk120;
}

// 0x00116e30 SoundEmitterArray_SetSpeechVolume_maybe
void CKSoundStreamManager::SetSpeechVolume(float volume) {
    g_pEngine->m_soundManager->m_pSoundStreamManager->FindTypeByName(kSpeech)->SetVolume(volume);
}

// 0x00116ef0 SoundEmitterArray_GetSpeechVolume_maybe
float CKSoundStreamManager::GetSpeechVolume() {
    return g_pEngine->m_soundManager->m_pSoundStreamManager->FindTypeByName(kSpeech)->m_fVolume;
}

// 0x00116f98 SoundEmitterArray_GetSpeechCurrentVolume_maybe
float CKSoundStreamManager::GetSpeechCurrentVolume() {
    return g_pEngine->m_soundManager->m_pSoundStreamManager->FindTypeByName(kSpeech)->m_unk120;
}

// 0x00117040 SoundEmitterArray_SetMusicVolume_maybe
void CKSoundStreamManager::SetMusicVolume(float volume) {
    g_pEngine->m_soundManager->m_pSoundStreamManager->FindTypeByName(kMusics)->SetVolume(volume);
}

// 0x00117300 SoundVoicePool_FindFree_maybe: the first voice without an instance.
SoundVoice* SoundVoiceManager::FindFreeVoice() {
    for (uint32_t i = 0; i < m_ui32NbVoices; ++i) {
        if (m_aVoices[i].m_pInstance == nullptr) return &m_aVoices[i];
    }
    return nullptr;
}

// 0x00115f38 SoundEmitterArray_TestAllGroups_maybe: every type's stream players pass the test (with no
// type, 1): 0 no player has an object (0x11d980), 1 every busy player has reached its state (0x11de70),
// 2 every player has no media (0x11dad0); other values: a count-down loop without effect, 1.
uint8_t CKSoundStreamManager::TestAllGroups(int32_t test) {
    const uint32_t count = m_vpStreamTypes.m_ui32NbUsedElt;
    if (count == 0) return 1;
    if (test == 0) {
        for (uint32_t i = 0; i < m_vpStreamTypes.m_ui32NbUsedElt; ++i) {
            if (m_vpStreamTypes.m_pBlock[i]->AreAllVoicesInactive() == 0) return 0;
        }
    } else if (test == 1) {
        for (uint32_t i = 0; i < m_vpStreamTypes.m_ui32NbUsedElt; ++i) {
            if (m_vpStreamTypes.m_pBlock[i]->AreAllVoicesSettled() == 0) return 0;
        }
    } else if (test == 2) {
        for (uint32_t i = 0; i < m_vpStreamTypes.m_ui32NbUsedElt; ++i) {
            if (m_vpStreamTypes.m_pBlock[i]->AreAllVoicesState9() == 0) return 0;
        }
    }
    return 1;
}

// 0x00116308 SoundEmitterArray_Unsuspend_maybe: KStub_Nop_11d648 on every type, then unsuspended.
void CKSoundStreamManager::Unsuspend() { m_unk18 = 0; }

// 0x00116690 SoundEmitterArray_Suspend_maybe: KStub_Nop_11d640 on every type, the music-flagged sounds
// stop (with their fade-out), then suspended.
void CKSoundStreamManager::Suspend() {
    g_pEngine->m_soundManager->m_pVoiceManager->StopFlaggedSounds();
    m_unk18 = 1;
}

// 0x001173c8 SoundList_Remove: the first entry equal to `sound` takes the last entry's value (unless it is the last).
void SoundVoiceManager::RemoveSound(CKSound* sound) {
    const uint32_t count = m_vpSounds.m_ui32NbUsedElt;
    if (count == 0) return;
    uint32_t index = 0;
    while (m_vpSounds.m_pBlock[index] != sound) {
        if (++index == count) return;
    }
    m_vpSounds.m_ui32NbUsedElt = count - 1;
    if (count - 1 == index) return;
    m_vpSounds.m_pBlock[index] = m_vpSounds.m_pBlock[count - 1];
}
