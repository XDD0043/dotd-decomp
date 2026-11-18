// CKSrvSekensor.cpp - reconstructed original translation unit 0x1f8450-0x1fa758 (GAME_TOC1, main_toc1), 48 functions, 41 live.
// Primary class: CKSrvSekensor  key 0x281  category Service  size 0x50  vtable 0xb1eb98
// Other owners: Platform (2), FormatLevelSpeechPath (1), FormatSpeechExportWavPath (1), FormatSpeechExportDir (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1f8450  CKSrvSekensor_Delete
//   [ ] 0x1f84a0  CKSrvSekensor_Construct  [dead]
//   [x] 0x1f8518  Platform_GetFileTag_maybe
//   [ ] 0x1f8548  Platform_GetSecondFileTag_maybe  [dead]
//   [ ] 0x1f8578  CKSrvSekensor_GetSekensCount_maybe  [dead]
//   [ ] 0x1f8580  KStub_Nop_1f8580  [dead]
//   [x] 0x1f8588  CKSrvSekensor_GetCurrentSekens_maybe  (inline, CKSrvSekensor.h)
//   [x] 0x1f8590  CKSrvSekensor_GetPendingSekens_maybe
//   [ ] 0x1f8598  CKSrvSekensor_Construct_2  [dead]
//   [x] 0x1f8610  CKSrvSekensor_GetSekensTypeDelay_maybe
//   [ ] 0x1f8640  RegisterCKSrvSekensorClass
//   [ ] 0x1f86b8  _GLOBAL__I_1f86b8
//   [x] 0x1f86c8  CKSrvSekensor_RefreshSubtitleVisibility_maybe
//   [x] 0x1f8808  CKSrvSekensor_Resume
//   [x] 0x1f8810  CKSrvSekensor_Stop
//   [x] 0x1f8880  CKSrvSekensor_Restart
//   [x] 0x1f88f0  CKSrvSekensor_IsCurrentSekensRunningWithFlag14Bit4_maybe
//   [x] 0x1f8970  CKSrvSekensor_IsCurrentSekensDone
//   [x] 0x1f89b0  CKSrvSekensor_RequestSekens_maybe
//   [x] 0x1f8ce0  CKSrvSekensor_StopSekens_maybe
//   [x] 0x1f8e08  FormatLevelSpeechPath
//   [x] 0x1f8e40  FormatSpeechExportWavPath
//   [x] 0x1f8e88  FormatSpeechExportDir
//   [x] 0x1f8ec0  CKSrvSekensor_DestroyService
//   [x] 0x1f8f38  CKSrvSekensor_InitializeService
//   [x] 0x1f8fa0  CKSrvSekensor_PostLoad
//   [x] 0x1f9028  CKSrvSekensor_Destroy
//   [x] 0x1f9080  CKSrvSekensor_DeleteArray
//   [x] 0x1f9128  CKSrvSekensor_Pause
//   [x] 0x1f91d8  CKSrvSekensor_FindSekensByUuid_maybe
//   [ ] 0x1f92a8  CKSrvSekensor_AnySekensUsesSpeechStream_maybe  [dead]
//   [x] 0x1f9350  CKSrvSekensor_SetDefaultState
//   [x] 0x1f93e8  CKSrvSekensor_GetSekens
//   [x] 0x1f9418  CKSrvSekensor_Start
//   [x] 0x1f9450  CKSrvSekensor_vfA8
//   [x] 0x1f94e8  CKSrvSekensor_RecursiveRegistration
//   [ ] 0x1f9590  CKSrvSekensor_IsSubtitleVisible_maybe  [dead]
//   [x] 0x1f95f0  CKSrvSekensor_SetSubtitlesEnabled_maybe
//   [ ] 0x1f9760  CKSrvSekensor_Save
//   [x] 0x1f9768  CKSrvSekensor_GetInfo  (returns 1: the root's default)
//   [x] 0x1f9770  CKSrvSekensor_RegisterSekens_maybe
//   [x] 0x1f9858  CKSrvSekensor_Load
//   [x] 0x1f9c48  CKSrvSekensor_UpdateLocalizedData
//   [x] 0x1f9d50  CKSrvSekensor_MessageProc
//   [x] 0x1f9ef0  CKSrvSekensor_CreateArray
//   [x] 0x1fa000  CKSrvSekensor_Create
//   [x] 0x1fa0a8  CKSrvSekensor_CancelSekens_maybe
//   [x] 0x1fa2a0  UpdateCKSrvSekensor
//
//   [ ] 0x9b0f18  CKSrvSekensor_IsKindOfClass  [inline]
//   [ ] 0x9b0f50  CKSrvSekensor_GetClassType  [inline]
//   [ ] 0x9b0f58  CKSrvSekensor_GetClassID  [inline]
//   [ ] 0x9b0f60  CKSrvSekensor_DeletingDestructor  [inline]
//   [ ] 0x9b1018  CKSrvSekensor_Destructor  [inline]
#include "k2000/services/CKSrvSekensor.h"

#include <cstring>

#include "k2000/graphical/ui/CText2d.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/logic/CKSekensBlock.h"
#include "k2000/managers/CKSoundManager.h"
#include "k2000/sound/CKSoundStreamManager.h"
#include "k2000/system/CTimeManager.h"
#include "k2000/system/IKTime.h"
#include "k2000/core/Stub.h"
#include "k2000/logic/CKSekens.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/misc/Engine.h"
#include "k2000/io/KFileSystem.h"
#include "k2000/logic/CKGameLevel.h"
#include "k2000/logic/sound/CKStreamWave.h"
#include "k2000/logic/ui/CLocManager.h"
#include "k2000/misc/IKGameStructure.h"
#include "k2000/sound/SoundStreamType.h"
#include <cstdio>

namespace {
// The inlined TVector sizing of both vectors: the block is sized to count; growth (to the next
// multiple of 8 above count) cannot trigger right after.
template <class T>
void ReserveExactly(TVector<T, 8>* vector, uint32_t count) {
    vector->m_ui32NbElt = count;
    vector->m_pBlock = static_cast<T*>(Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(T))));
    if (vector->m_ui32NbElt < count) {  // as in the original: cannot happen right after the assignment
        uint32_t capacity = (count & ~7u) + 8;
        if (capacity == 0) capacity = 8;
        vector->m_pBlock = static_cast<T*>(
            Mem_ReallocAligned16(vector->m_pBlock, capacity * static_cast<uint32_t>(sizeof(T))));
        vector->m_ui32NbElt = capacity;
    }
    vector->m_ui32NbUsedElt = count;
}
}  // namespace

// Inlined in 0x001fa000 CKSrvSekensor_Create (0x1f84a0 CKSrvSekensor_Construct is an unreferenced copy).
CKSrvSekensor::CKSrvSekensor() {
    m_vSekensList.m_ui32NbElt = 8;
    m_vSekensList.m_pBlock = nullptr;
    m_vSekensList.m_ui32NbUsedElt = 0;
    m_unk30.m_ui32NbElt = 8;
    m_unk30.m_pBlock = nullptr;
    m_unk30.m_ui32NbUsedElt = 0;
    m_unk48 = 0.0f;
    m_ui32Priority = 0xb4;
    m_unk24 = nullptr;
    m_unk1c = nullptr;
    // Not set by the original constructor: the PS3's live service has zero here (census objects-lvl010_ingame), and
    // UpdateCKSrvSekensor reads the pending sekens at once; the native heap fills new blocks with 0xcd.
    m_pPendingSekens = nullptr;
    m_unk28 = 0;
    m_fRequestTime = 0.0f;
    m_i32CurrentIndex = 0;
}

// 0x001f8f38 CKSrvSekensor_InitializeService
int32_t CKSrvSekensor::InitializeService() {
    Engine_SetSrvSekensor(this);
    m_unk2c = (m_unk2c & ~1u) | 1;
    m_unk4c = static_cast<IKSerializable*>(ClassRegistry_CreateObjectByKey(0x5a8c));
    return 1;
}

// 0x001f95f0 CKSrvSekensor_SetSubtitlesEnabled_maybe: +0x2c bit 0, then the subtitle texts of the current sekens
// (shown while the engine clock runs and the sekens says so) and of the secondary one (+0x24) shown or hidden. A
// current sekens without a text ends it there: the secondary one's is left as it is.
void CKSrvSekensor::SetSubtitlesEnabled(uint32_t enabled) {
    m_unk2c = enabled | (m_unk2c & ~1u);
    CKSekens* current = m_unk1c;
    if (current != nullptr) {
        CText2d* text = current->m_pText;
        if (text == nullptr) return;
        if (g_pEngine->m_timeManager->m_pTime->m_eCurrentState == IKTime::RUNNING && current->ShouldShowSubtitles(enabled & 0xff) != 0) {
            text->Enable();  // vt+0x64
        } else {
            text->Disable();  // vt+0x68
        }
    }
    CKSekens* secondary = m_unk24;
    if (secondary != nullptr && secondary->m_pText != nullptr) {
        CText2d* text = secondary->m_pText;
        if (g_pEngine->m_timeManager->m_pTime->m_eCurrentState == IKTime::RUNNING && secondary->ShouldShowSubtitles(enabled & 0xff) != 0) {
            text->Enable();
        } else {
            text->Disable();
        }
    }
}

// 0x001f8fa0 CKSrvSekensor_PostLoad: GAME.KP3's post-load gives the "Speech" stream type its one player
// (PtrList_FindByNameHash_maybe 0x115cc8 with "Speech", 0x00c4b158; the base PostLoad KStub_Return1_1a5b0).
int32_t CKSrvSekensor::PostLoad(int32_t type) {
    if (type != K_GAME_PLATEFORMS) return 1;
    g_pEngine->m_soundManager->m_pSoundStreamManager->FindTypeByName("Speech")->SetStreamCount(1);
    return 1;
}

namespace {

// Local copies of 0x0002f590 Game_GetCurrentLevelNumber_maybe (CKLevel.cpp) and 0x00013e48
// CDefaultGameManager_GetCurrentLevelNumber_maybe (CDefaultGameManager.cpp): the loaded stage's level number (+0x1c), 0
// without a game manager.
int32_t Game_GetCurrentLevelNumber() {
    CDefaultGameManager* manager = g_pEngine->m_gameManager;
    if (manager == nullptr) return 0;
    CKGameLevel* level = static_cast<IKGameStructure*>(manager->m_gameStructure)->GetCurrentLevel();
    return level->m_i32StageIndex;  // BUG(original): a structure without a loaded stage is not checked (a null read)
}

// 0x00c4b054: the platform tag of the file names ("PS3", 0x00ac3038).
const char kPlatformTag[] = "PS3";

}  // namespace

// 0x001f8e08 FormatLevelSpeechPath: "%sLVL%03d/SPEECH" (UpdateLocalizedData formats the same inline).
//
// vt+0xa0 0x001f9c48 CKSrvSekensor_UpdateLocalizedData: the speech wave (+0x4c) takes the speech file of the loaded
// level in the voice language, "LVL%03d/SPEECH/%d_PS30.RWS" (KStub_Nop_1f4c58 on the current sekens first).
void CKSrvSekensor::UpdateLocalizedData() {
    if (m_unk1c != nullptr) m_unk1c->LocalizedDataChanged(0, 0);  // 0x001f4c58 KStub_Nop_1f4c58 (empty)
    const uint32_t voice = g_pEngine->m_locManager->GetVoiceLanguageIndex();
    const char* tag = kPlatformTag;
    const int32_t level = Game_GetCurrentLevelNumber();
    char directory[0xa08];
    char path[0x100];
    std::snprintf(directory, sizeof(directory), "%sLVL%03d/SPEECH", "", level);  // TOC -0x12b8 / -0x12a0
    std::snprintf(path, sizeof(path), "%s/%d_%s0.RWS", directory, static_cast<int32_t>(voice), tag);  // TOC -0x129c
    KFileSystem_ConvertBackslashes(g_pEngine->m_fileSystem, path);
    static_cast<CKStreamWave*>(m_unk4c)->SetFilePath(path);
}

// 0x001f9028 CKSrvSekensor_Destroy: the sekens list freed.
void CKSrvSekensor::Destroy() {
    if (m_vSekensList.m_pBlock != nullptr) {
        Mem_FreeAligned16(m_vSekensList.m_pBlock);
        m_vSekensList.m_ui32NbUsedElt = 0;
        m_vSekensList.m_pBlock = nullptr;
    }
}

// 0x001f9858 CKSrvSekensor_Load. A level gives the sekens references; the level localisation file
// lets every sekens of the list load its own part (vt+0x2c with type 2); GAME.KP3 gives DotD's words.
int32_t CKSrvSekensor::Load(IKFile* file, int32_t type) {
    if (type == K_LEVEL_PLATEFORMS) {
        uint32_t count = 0;
        ReadU32LE(file, &count);
        if (count == 0) return 1;
        ReserveExactly(&m_vSekensList, count);
        for (uint32_t i = 0; i < count; ++i) IKFile_ReadRef(file, &m_vSekensList.m_pBlock[i]);
        return 1;
    }
    if (type == K_LEVEL_LOCALIZATION) {
        const uint32_t count = m_vSekensList.m_ui32NbUsedElt;
        for (uint32_t i = 0; i != count; ++i) m_vSekensList.m_pBlock[i]->Load(file, K_LEVEL_LOCALIZATION);
        return 1;
    }
    if (type == K_GAME_PLATEFORMS) {
        uint32_t count = 0;
        ReadU32LE(file, &count);
        if (count != 0) {
            ReserveExactly(&m_unk30, count);
            for (uint32_t i = 0; i < count; ++i) ReadU32LE(file, &m_unk30.m_pBlock[i]);
        }
        ReadF32LE(file, &m_unk3c);
        ReadF32LE(file, &m_unk40);
    }
    return 1;
}

// 0x001f9418 CKSrvSekensor_Start
void CKSrvSekensor::Start() {
    m_unk28 &= 0x00ffffffu;  // stb 0 at +0x28: bits 24-31 of the word
    m_unk1c = nullptr;
    m_pPendingSekens = nullptr;
    m_unk24 = nullptr;
    m_unk2c &= 0xfffffffdu;
    m_unk48 = 9999.99f;  // TOC1 -0x12a4: 0x461c3ff6
}

// 0x001f9128 CKSrvSekensor_Pause
void CKSrvSekensor::Pause() {
    if (m_unk1c != nullptr && m_unk1c->m_pText != nullptr) m_unk1c->m_pText->Disable();  // vt+0x68
    if (m_unk24 != nullptr && m_unk24->m_pText != nullptr) m_unk24->m_pText->Disable();
}

// 0x001f8ec0 CKSrvSekensor_DestroyService
void CKSrvSekensor::DestroyService() {
    Engine_SetSrvSekensor(nullptr);  // 0x24c30
    if (m_unk30.m_pBlock != nullptr) {
        Mem_FreeAligned16(m_unk30.m_pBlock);
        m_unk30.m_pBlock = nullptr;
    }
    m_unk30.m_ui32NbUsedElt = 0;
    m_unk30.m_pBlock = nullptr;
    ClassRegistry_DestroyObject(m_unk4c);  // 0x11420
}

// 0x001f8810 CKSrvSekensor_Stop: the running sekens (+0x1c) stopped and forgotten; the second one (+0x24)
// stopped, its byte at +0x28 (bits 24-31 of the word, the first byte on the PS3) cleared, and kept.
void CKSrvSekensor::Stop() {
    if (m_unk1c != nullptr) {
        m_unk1c->Stop();
        m_unk1c = nullptr;
    }
    if (m_unk24 != nullptr) {
        m_unk24->Stop();
        m_unk28 &= 0x00ffffffu;
    }
    m_pPendingSekens = nullptr;
}

// 0x001f8880 CKSrvSekensor_Restart (vt+0x54): the same body as Stop.
void CKSrvSekensor::Restart() {
    if (m_unk1c != nullptr) {
        m_unk1c->Stop();  // 0x001f56b0
        m_unk1c = nullptr;
    }
    if (m_unk24 != nullptr) {
        m_unk24->Stop();
        m_unk28 &= 0x00ffffffu;  // stb 0 at +0x28
    }
    m_pPendingSekens = nullptr;
}

// 0x001f9350 CKSrvSekensor_SetDefaultState
void CKSrvSekensor::SetDefaultState(int32_t flag) {
    const int32_t byteFlag = flag & 0xff;  // rldicl r29,r4,0,56
    for (uint32_t i = 0; i < m_vSekensList.m_ui32NbUsedElt; ++i) {
        m_vSekensList.m_pBlock[i]->SetDefaultState(byteFlag);  // vt+0x38 CKSekens_SetDefaultState 0x1f3ec0
    }
}

// 0x001f93e8 CKSrvSekensor_GetSekens
CKSekens* CKSrvSekensor::GetSekens(uint32_t index) const {
    if (index < m_vSekensList.m_ui32NbUsedElt) return static_cast<CKSekens*>(m_vSekensList.m_pBlock[index]);
    return nullptr;
}

// 0x001f8610 CKSrvSekensor_GetSekensTypeDelay_maybe (the table's words are floats)
float CKSrvSekensor::GetSekensTypeDelay(uint32_t index) const {
    if (m_unk30.m_ui32NbUsedElt <= index) return 0.0f;
    float delay;
    std::memcpy(&delay, &m_unk30.m_pBlock[index], 4);
    return delay;
}

// 0x001f89b0 CKSrvSekensor_RequestSekens_maybe
uint8_t CKSrvSekensor::RequestSekens(CKSekens* sekens) {
    CKSekens* current = m_unk1c;
    CKSekens* pending = m_pPendingSekens;
    const float now = g_pEngine->m_timeManager->m_pTime->m_afCurrentTime[IKTime::FIXED_GAME_TIME];
    const double nowDouble = static_cast<double>(now);
    if (sekens == nullptr || current == sekens ||
        (g_pEngine->m_soundManager->m_pSoundStreamManager->m_unk18 != 0 && sekens->UsesSpeechStream() != 0) ||
        ((sekens->m_flags & 0x100) != 0 && (sekens->m_flags & 0x80) != 0) ||
        static_cast<double>(m_unk48) < static_cast<double>(sekens->GetSekensorDelay()) || now < sekens->m_fEarliestStart)
        return 0;
    uint32_t flags = sekens->m_flags;
    if ((flags & 0x200) != 0) {  // a secondary sekens runs beside the current one
        if (m_unk24 != nullptr && (m_unk28 >> 24) != 0) {
            m_unk24->Stop();
            m_unk28 &= 0x00ffffffu;
        }
        m_unk24 = sekens;
        return 1;
    }
    bool stopCurrent = true;
    if (current != nullptr) {
        bool sameCheck = false;
        if ((current->m_flags & 0x40) == 0) {
            sameCheck = true;
        } else if (current->m_i32CurrentLine != -1 &&
                   static_cast<CKSekensElement*>(current->m_vBlocks.m_pBlock[current->m_i32CurrentLine])->Vf50() == 0) {
            flags = sekens->m_flags;
            sameCheck = true;
        }
        if (sameCheck && (flags & 0x2000) == 0) {
            if (pending == nullptr || pending == sekens || (pending->m_flags & 0x40) != 0 || (flags & 0x40) == 0) {
                m_unk2c &= 0xfffffffdu;
                m_fRequestTime = now;
                m_pPendingSekens = sekens;
                return 1;
            }
            return 0;
        }
        (void)stopCurrent;
        current->Stop();
    }
    if (m_unk24 != nullptr) {
        m_unk24->Stop();
        m_unk28 &= 0x00ffffffu;
    }
    int32_t index = static_cast<int32_t>(m_vSekensList.m_ui32NbUsedElt);
    for (;;) {
        if (index == 0) break;
        --index;
        if (m_vSekensList.m_pBlock[index] == sekens) {
            m_i32CurrentIndex = index;
            break;
        }
    }
    m_unk2c &= 0xfffffffdu;
    m_unk1c = sekens;
    if (sekens->Begin() == 0) {
        m_unk1c = nullptr;
        m_i32CurrentIndex = -1;
        return 0;
    }
    (void)nowDouble;
    return 1;
}

// 0x001f9d50 CKSrvSekensor_MessageProc
int32_t CKSrvSekensor::MessageProc(uint16_t message, void* /*data*/) {
    if (message == 0xf08) {
        if (m_unk1c != nullptr) {
            m_unk1c->Stop();
            m_pPendingSekens = nullptr;
            m_unk1c = nullptr;
        }
    } else {
        if (message != 0xf09) return 1;
        CKSekens* current = m_unk1c;
        if (current != nullptr) {
            if ((current->m_flags & 0x40) == 0) {
                m_unk2c = (m_unk2c & 0xfffffffdu) | 2;
                m_pPendingSekens = nullptr;
            } else {
                bool stopped = false;
                if (current->m_i32CurrentLine != -1) {
                    CKSekensElement* line = static_cast<CKSekensElement*>(current->m_vBlocks.m_pBlock[current->m_i32CurrentLine]);
                    if (line->Vf50() == 0) {
                        m_unk2c = (m_unk2c & 0xfffffffdu) | 2;
                        m_pPendingSekens = nullptr;
                        stopped = true;
                    } else {
                        current = m_unk1c;
                    }
                }
                if (!stopped) {
                    current->Stop();
                    m_pPendingSekens = nullptr;
                    m_unk1c = nullptr;
                }
            }
        }
    }
    if (m_unk24 != nullptr) {
        m_unk24->Stop();
        m_unk28 &= 0x00ffffffu;
        return 0;
    }
    return 0;
}

// 0x001f8ce0 CKSrvSekensor_StopSekens_maybe
uint8_t CKSrvSekensor::StopSekens(CKSekens* sekens) {
    if (sekens == nullptr) return 0;
    if (m_unk1c == sekens) {
        CKSekens* pending = m_pPendingSekens;
        m_pPendingSekens = nullptr;
        m_unk1c = nullptr;
        sekens->Stop();
        if (pending != nullptr) RequestSekens(pending);
        return 1;
    }
    if (m_pPendingSekens == sekens) {
        m_pPendingSekens = nullptr;
        return 1;
    }
    if (m_unk24 == sekens) {
        if ((m_unk28 >> 24) != 0) {
            sekens->Stop();
            m_unk28 &= 0x00ffffffu;
        }
        m_unk24 = nullptr;
        return 1;
    }
    return 0;
}

// 0x001fa0a8 CKSrvSekensor_CancelSekens_maybe
uint8_t CKSrvSekensor::CancelSekens(CKSekens* sekens) {
    if (sekens == nullptr) return 0;
    if (m_unk1c != sekens) {
        if (m_pPendingSekens != sekens) return 0;
        m_pPendingSekens = nullptr;
        return 1;
    }
    if ((sekens->m_flags & 0x40) != 0) {
        const bool interruptible = sekens->m_i32CurrentLine == -1 ||
                                   static_cast<CKSekensElement*>(sekens->m_vBlocks.m_pBlock[sekens->m_i32CurrentLine])->Vf50() != 0;
        if (interruptible) {
            CKSekens* pending = m_pPendingSekens;
            m_pPendingSekens = nullptr;
            m_unk1c = nullptr;
            sekens->Stop();
            if (pending != nullptr) RequestSekens(pending);
            return 1;
        }
    }
    m_unk2c = (m_unk2c & 0xfffffffdu) | 2;
    return 1;
}

// 0x001f86c8 CKSrvSekensor_RefreshSubtitleVisibility_maybe
void CKSrvSekensor::RefreshSubtitleVisibility() {
    CKSekens* const sekenses[2] = {m_unk1c, m_unk24};
    for (CKSekens* sekens : sekenses) {
        if (sekens == nullptr || sekens->m_unk7c != 0 || sekens->m_pText == nullptr) continue;
        if (sekens->ShouldShowSubtitles(m_unk2c & 1) == 0) {
            sekens->m_pText->Disable();  // vt+0x68
        } else {
            sekens->m_pText->Enable();  // vt+0x64
        }
    }
}

// 0x001fa2a0 UpdateCKSrvSekensor. The control flow follows the original's labels.
void CKSrvSekensor::Update(IKTime* time) {
    if (time->m_eCurrentState != 0) return;
    CKSekens* current;
    CKSekens* secondary;
    uint32_t secondaryRuns;
    int32_t result;
    uint8_t skip;
    if (m_pPendingSekens != nullptr) {
        const float limit = (m_pPendingSekens->m_flags & 0x40) == 0 ? m_unk40 : m_unk3c;
        if (limit < time->m_afCurrentTime[IKTime::FIXED_GAME_TIME] - m_fRequestTime) m_pPendingSekens = nullptr;
    }
    if (m_unk24 == nullptr) {
        current = m_unk1c;
        secondaryRuns = 0;
        if (current == nullptr) {
            m_unk48 = m_unk48 + time->m_afDeltaTime[IKTime::FIXED_GAME_TIME];
            return;
        }
    } else {
        current = m_unk1c;
        secondaryRuns = 1;
        if (current != nullptr) secondaryRuns = (m_unk24->m_pText != current->m_pText) ? 1 : 0;
    }
    m_unk48 = 0.0f;
    if (current != nullptr) {
        skip = g_pEngine->m_gameManager->GetDialogueButtonState(0) == 0xff ? 1 : 0;  // vt+0x18c
        result = current->Update(time, skip);
        if (result == 1) {
            if ((m_unk2c & 2) == 0) {
                CKSekens* pending = m_pPendingSekens;
                if (pending == nullptr) {
                    current = m_unk1c;
                } else {
                    current = m_unk1c;
                    if ((current->m_flags & 0x40) != 0) {
                        if (current != nullptr) {
                            m_pPendingSekens = nullptr;
                            m_unk1c = nullptr;
                            current->Stop();
                            RequestSekens(pending);
                        }
                        goto label_3d0;
                    }
                }
                if (current->AdvanceToNextLine() != 0) goto label_3d0;
            }
        } else if (result != 2) {
            goto label_3d0;
        }
        current = m_unk1c;
        if (current != nullptr) {
            CKSekens* pending = m_pPendingSekens;
            m_pPendingSekens = nullptr;
            m_unk1c = nullptr;
            current->Stop();
            if (pending != nullptr) RequestSekens(pending);
        }
    }
label_3d0:
    if (secondaryRuns == 0) goto label_450;
    if ((m_unk28 >> 24) == 0) {
        m_unk24->Begin();
        m_unk28 = (m_unk28 & 0x00ffffffu) | (1u << 24);
    }
    secondary = m_unk24;
    skip = g_pEngine->m_gameManager->GetDialogueButtonState(0) == 0xff ? 1 : 0;
    result = secondary->Update(time, skip);
    if (result == 1) {
        if ((m_unk2c & 2) != 0) goto label_540;
        CKSekens* pending = m_pPendingSekens;
        CKSekens* second;
        if (pending == nullptr) {
            second = m_unk24;
        } else {
            second = m_unk24;
            if ((second->m_flags & 0x40) != 0) {
                if (second != nullptr) {
                    if (m_unk1c == second) {
                        m_pPendingSekens = nullptr;
                        m_unk1c = nullptr;
                        second->Stop();
                        RequestSekens(pending);
                    } else if (pending == second) {
                        m_pPendingSekens = nullptr;
                    } else if ((m_unk28 >> 24) == 0) {
                        m_unk24 = nullptr;
                    } else {
                        second->Stop();
                        m_unk28 &= 0x00ffffffu;
                        m_unk24 = nullptr;
                    }
                }
                goto label_450;
            }
        }
        if (second->AdvanceToNextLine() != 0 || (secondary = m_unk24) == nullptr) goto label_450;
        if (m_unk1c == secondary) goto label_6e8;
        if (m_pPendingSekens == secondary) {
            m_pPendingSekens = nullptr;
            goto label_450;
        }
        if ((m_unk28 >> 24) != 0) {
            secondary->Stop();
            m_unk28 &= 0x00ffffffu;
        }
    } else {
        if (result != 2) goto label_450;
    label_540:
        secondary = m_unk24;
        if (secondary == nullptr) goto label_450;
        if (m_unk1c == secondary) {
        label_6e8:
            CKSekens* pending = m_pPendingSekens;
            m_pPendingSekens = nullptr;
            m_unk1c = nullptr;
            secondary->Stop();
            if (pending != nullptr) RequestSekens(pending);
            goto label_450;
        }
        if (m_pPendingSekens == secondary) {
            m_pPendingSekens = nullptr;
            goto label_450;
        }
        if ((m_unk28 >> 24) != 0) {
            secondary->Stop();
            m_unk28 &= 0x00ffffffu;
        }
    }
    m_unk24 = nullptr;
label_450:
    RefreshSubtitleVisibility();
}

// 0x001f8518 Platform_GetFileTag_maybe: the platform table 0x00c4afc8 (8 entries of 0x14 bytes; the first word is the tag).
// BUG(original): the test is signed (index < 8), so a negative index reads before the table; dotd answers null there.
const char* Platform_GetFileTag(int32_t index) {
    static const char* const kTags[8] = {"PS2", "WIN", "GCN", "XBX", "PSP", "XEN", "REV", "PS3"};
    if (index >= 8 || index < 0) return nullptr;
    return kTags[index];
}

// 0x001f8e40 FormatSpeechExportWavPath / 0x001f8e88 FormatSpeechExportDir: the speech export tool's paths (FormatString,
// i.e. sprintf). No caller in the original (only their OPDs).
void FormatSpeechExportWavPath(char* out, const char* root, int32_t language, int32_t sekens, int32_t line) {
    std::sprintf(out, "%sTmp-SpeechExport-%02d/Sekens_%04d_%02d.wav", root, language, sekens, line);
}
void FormatSpeechExportDir(char* out, const char* root, int32_t language) {
    std::sprintf(out, "%sTmp-SpeechExport-%02d", root, language);
}

// 0x001f88f0 CKSrvSekensor_IsCurrentSekensRunningWithFlag14Bit4_maybe: with a current sekens that is not done
// (CKSrvSekensor_IsSekensDone_maybe 0x1f4728, on the engine's sekensor), its flags' bit 4.
uint32_t CKSrvSekensor::IsCurrentSekensRunningWithFlag14Bit4() const {
    if (m_unk1c == nullptr) return 0;
    if (static_cast<CKSrvSekensor*>(g_pEngine->m_srvSekensor)->IsSekensDone(m_unk1c) != 0) return 0;
    return (m_unk1c->m_flags >> 4) & 1;
}

// 0x001f8970 CKSrvSekensor_IsCurrentSekensDone: 1 without a current sekens, else IsSekensDone 0x1f4728 of it. No caller
// in the original (only its OPD).
uint8_t CKSrvSekensor::IsCurrentSekensDone() const {
    if (m_unk1c == nullptr) return 1;
    return static_cast<CKSrvSekensor*>(g_pEngine->m_srvSekensor)->IsSekensDone(m_unk1c);
}

// 0x001f91d8 CKSrvSekensor_FindSekensByUuid_maybe: the last sekens of the list (searched backwards) whose uuid (+0x18) is
// `uuid`, or null. No caller in the original (only its OPD).
CKSekens* CKSrvSekensor::FindSekensByUuid(const uint32_t* uuid) const {
    for (uint32_t i = m_vSekensList.m_ui32NbUsedElt; i != 0; --i) {
        CKSekens* sekens = static_cast<CKSekens*>(m_vSekensList.m_pBlock[i - 1]);
        if (Uuid_Equals(sekens->m_uuid, uuid)) return sekens;
    }
    return nullptr;
}

// vt+0xa8 0x001f9450 CKSrvSekensor_vfA8: CKSekens_ForEachLineCallVf54_maybe 0x1f4ac0 on every sekens of the list.
void CKSrvSekensor::VfA8(uint8_t a, uint32_t b) {
    const uint32_t count = m_vSekensList.m_ui32NbUsedElt;
    for (uint32_t i = 0; i != count; ++i) static_cast<CKSekens*>(m_vSekensList.m_pBlock[i])->ForEachLineCallVf54(a, b);
}

// vt+0x24 0x001f94e8 CKSrvSekensor_RecursiveRegistration: every sekens' RecursiveRegistration (vt+0x24) with `type`.
void CKSrvSekensor::RecursiveRegistration(int32_t type) {
    const uint32_t count = m_vSekensList.m_ui32NbUsedElt;
    for (uint32_t i = 0; i != count; ++i) m_vSekensList.m_pBlock[i]->RecursiveRegistration(type);
}

// vt+0xac 0x001f9770 CKSrvSekensor_RegisterSekens_maybe: `sekens` appended to the list (TVector growth by 8; returns 1).
int32_t CKSrvSekensor::RegisterSekens(IKSerializable* sekens) {
    if (m_vSekensList.m_ui32NbElt == m_vSekensList.m_ui32NbUsedElt) {
        uint32_t capacity = m_vSekensList.m_ui32NbUsedElt + 8;
        if (capacity == 0) capacity = 8;
        m_vSekensList.m_pBlock = static_cast<IKSerializable**>(
            Mem_ReallocAligned16(m_vSekensList.m_pBlock, capacity * static_cast<uint32_t>(sizeof(IKSerializable*))));
        m_vSekensList.m_ui32NbElt = capacity;
    }
    m_vSekensList.m_pBlock[m_vSekensList.m_ui32NbUsedElt] = sekens;
    ++m_vSekensList.m_ui32NbUsedElt;
    return 1;
}
