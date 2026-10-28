// SoundVoiceManager.cpp - reconstructed original translation unit 0x117468-0x11a0c8 (GAME_TOC1, main_toc1), 33 functions, 21 live.
// Primary owner: SoundVoiceManager (not a registered class)
// Other owners: SoundEngine (4), SoundBank (3), SoundChannelSet (3), SoundBackend (3), SoundList (2), SoundInstance (1), CKSoundManager (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x117468  SoundVoiceManager_DestroyChannelPool_maybe  [dead]
//   [ ] 0x117598  FUN_00117598  [dead]
//   [x] 0x1175c0  SoundBank_StopSectorSounds
//   [ ] 0x117660  SoundBank_PlaySectorAutoSounds_2_maybe  [dead]
//   [x] 0x117780  SoundList_Append
//   [x] 0x117860  SoundVoiceManager_Load_maybe
//   [ ] 0x117a70  SoundVoiceManager_Save_maybe  [dead]
//   [ ] 0x117c68  FUN_00117c68  [dead]
//   [ ] 0x117d20  SoundVoiceManager_ApplyAllVoiceParameters_maybe  [dead]
//   [x] 0x117db8  SoundEngine_InsertByPriority_maybe
//   [ ] 0x117f90  SoundInstance_IsOutOfListenerRange_maybe
//   [ ] 0x1180f8  SoundEngine_GetSharedVoiceCount_maybe
//   [ ] 0x118150  SoundVoiceManager_DestroyVoicePool_maybe  [dead]
//   [ ] 0x118250  SoundVoiceManager_CreateChannelPool_maybe  [dead]
//   [x] 0x118340  SoundChannelSet_PauseAll_maybe
//   [x] 0x1183f0  SoundChannelSet_ResumeAll_maybe
//   [x] 0x1184a0  SoundList_StopFlaggedSounds_maybe
//   [ ] 0x118558  SoundVoiceManager_DetachAllActiveChannels_maybe  [dead]
//   [ ] 0x118638  SoundVoiceManager_ReleaseChannel_maybe  [dead]
//   [x] 0x1187b0  SoundVoiceManager_AcquireChannel_maybe
//   [ ] 0x1188f8  SoundVoiceManager_CreateVoicePool_maybe  [dead]
//   [ ] 0x118a00  SoundVoiceManager_ReleaseVoicesAndChannels_maybe  [dead]
//   [x] 0x118b68  SoundEngine_CullAndPrioritise_maybe
//   [x] 0x118cf8  SoundEngine_Update_maybe
//   [x] 0x119000  SoundBank_PlaySectorAutoSounds_maybe
//   [x] 0x119120  SoundVoiceManager_StopAll_maybe
//   [ ] 0x119298  SoundChannelSet_ReleaseAllVoices_maybe
//   [ ] 0x119510  CKSoundManager_ReleaseVoicePool_maybe
//   [x] 0x1196a0  SoundVoiceManager_Init_maybe
//   [ ] 0x1198e8  SoundBackend_ReleaseVoices_maybe
//   [ ] 0x119b48  SoundVoiceManager_RebuildVoicePool_maybe
//   [x] 0x119d10  SoundBackend_StopSound_maybe
//   [x] 0x119e50  SoundBackend_PlaySound_maybe
#include "k2000/sound/SoundVoiceManager.h"

#include <cmath>
#include <cstring>

#include "crt/ppc_ops.h"
#include "k2000/core/IKSerializable.h"
#include "k2000/dictionaries/CKSoundDictionaryID.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/sound/CKSound.h"
#include "k2000/logic/sound/CKWave.h"
#include "k2000/managers/CKSoundManager.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/Engine.h"
#include "k2000/sound/CKListener.h"
#include "k2000/sound/CKSoundOutput.h"
#include "k2000/sound/CKSoundStreamManager.h"
#include "k2000/sound/SoundInstance.h"
#include "k2000/sound/SoundVoice.h"

namespace {

constexpr float kZero = 0.0f;             // TOC -0x4494
constexpr float kOne = 1.0f;              // TOC -0x4490
constexpr float kThousand = 1000.0f;      // TOC -0x448c
constexpr float kPriorityScale = 102000.0f;  // TOC -0x4488
constexpr uint32_t kHasVoiceBonus = 100000;  // lis/ori 0x186a0
constexpr uint32_t kInstanceCount = 128;

// Moves the instance of the active-list node `node` (whose predecessor is `prev`, null at the head) to
// the free list, as SoundEngine_Update_maybe and SoundVoiceManager_StopAll_maybe do it inline.
SoundNode* UnlinkActive(SoundVoiceManager* vm, SoundNode* prev, SoundNode* node) {
    SoundNode* next = node->m_pNext;
    if (prev == nullptr) {
        vm->m_pActiveInstances = next;
    } else {
        prev->m_pNext = next;
    }
    SoundNode_Free(node);
    return next;
}

void PushFree(SoundVoiceManager* vm, SoundInstance* instance) {
    SoundNode* node = SoundNode_Alloc();
    node->m_pNext = nullptr;
    node->m_pInstance = instance;
    node->m_pNext = vm->m_pFreeInstances;
    vm->m_pFreeInstances = node;
}

const CVector3* ListenerPosition(SoundVoiceManager* vm) { return vm->m_pListener->GetPosition(); }

}  // namespace

// Inlined in CKSoundManager_InitializeModule (0x00113b04-0x00113b38), the stores in its order.
SoundVoiceManager::SoundVoiceManager() {
    m_pPriorityList = nullptr;
    m_vpSounds.m_ui32NbElt = 100;
    m_vpSounds.m_pBlock = nullptr;
    m_vpSounds.m_ui32NbUsedElt = 0;
    m_pActiveInstances = nullptr;
    m_pFreeInstances = nullptr;
}

// 0x001196a0 SoundVoiceManager_Init_maybe
void SoundVoiceManager::Init() {
    m_pListener = new CKListener();  // OperatorNew(0x44)
    CKSoundManager* manager = g_pEngine->m_soundManager;
    const uint32_t outputVoices = manager->m_pOutput->m_unk04;
    const uint32_t streamVoices = manager->m_pSoundStreamManager->SumVoiceCounts();
    if (streamVoices < outputVoices) {
        m_ui32NbVoices = outputVoices - streamVoices;
        if (m_ui32NbVoices != 0) {
            m_aVoices = new SoundVoice[m_ui32NbVoices];  // OperatorNewArray(count * 0xc + 4), SoundVoice_Construct_maybe each
        } else {
            m_aVoices = nullptr;
        }
    } else {
        m_ui32NbVoices = 0;
        m_aVoices = nullptr;
    }
    m_fVoiceRatioVelocity = kOne;
    m_apSoundDictionary = nullptr;
    m_pSoundCodedDictionaryID = nullptr;
    m_pStreamBuffer = Mem_AllocAligned16(0x10040);
    // the 64-byte aligned 64 KB inside it are zeroed and published to RWA's stream players (TOC 0xc11560 /
    // 0xc11564); the platform's stream players keep their own buffers
    uint8_t* aligned = reinterpret_cast<uint8_t*>((reinterpret_cast<uintptr_t>(m_pStreamBuffer) + 0x3f) & ~static_cast<uintptr_t>(0x3f));
    std::memset(aligned, 0, 0x10000);
    m_vpSounds.m_ui32NbElt = 100;
    m_vpSounds.m_pBlock = static_cast<CKSound**>(Mem_AllocAligned16(100 * static_cast<uint32_t>(sizeof(CKSound*))));
    for (uint32_t i = 0; i < kInstanceCount; ++i) {
        SoundInstance* instance = new SoundInstance();  // OperatorNew(0x54) + SoundChannel_Reset_maybe
        PushFree(this, instance);
    }
}

// 0x00117860 SoundVoiceManager_Load_maybe
int32_t SoundVoiceManager::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    m_pListener->Load(file, K_LEVEL_PLATEFORMS);
    ReadF32LE(file, &m_fVoiceRatioVelocity);
    IKFile_ReadRef(file, &m_pSoundCodedDictionaryID);
    ReadU32LE(file, &m_ui32NbSoundDictionary);
    if (m_ui32NbSoundDictionary != 0) {
        m_apSoundDictionary = new IKSerializable*[m_ui32NbSoundDictionary];  // OperatorNewArray(count * 4)
        IKFile_ReadObjectRefArray(file, m_apSoundDictionary, m_ui32NbSoundDictionary);
    }
    return 1;
}

// 0x00117780 SoundList_Append: m_vpSounds grows by 100.
void SoundVoiceManager::AppendSound(CKSound* sound) {
    const uint32_t size = m_vpSounds.m_ui32NbUsedElt;
    if (m_vpSounds.m_ui32NbElt == size) {
        uint32_t capacity = size + 100;
        uint32_t bytes = capacity * static_cast<uint32_t>(sizeof(CKSound*));
        if (capacity == 0) {  // as in the original (cannot happen)
            capacity = 100;
            bytes = 100 * static_cast<uint32_t>(sizeof(CKSound*));
        }
        m_vpSounds.m_pBlock = static_cast<CKSound**>(Mem_ReallocAligned16(m_vpSounds.m_pBlock, bytes));
        m_vpSounds.m_ui32NbElt = capacity;
    }
    m_vpSounds.m_pBlock[m_vpSounds.m_ui32NbUsedElt] = sound;
    ++m_vpSounds.m_ui32NbUsedElt;
}

// 0x00117db8 SoundEngine_InsertByPriority_maybe: priority = ((1/d^2 x 1000 x 1000 + 100000 if it holds
// a voice) + 1000) / 102000 x 1000 (fctidz, the low word); the list stays sorted, highest first, and
// an instance goes after the ones of the same priority.
void SoundVoiceManager::InsertByPriority(SoundInstance* instance) {
    if ((instance->IsNotDelayState() & 0xff) == 0) {
        instance->SetVoiceAllowed(0);
        return;
    }
    const int32_t voice = static_cast<int32_t>(reinterpret_cast<uintptr_t>(instance->m_pVoice));
    const int32_t sign = voice >> 31;
    const uint32_t hasVoice = (static_cast<uint32_t>(sign - (sign ^ voice)) >> 31) & 1u;
    const float bonus = static_cast<float>(static_cast<double>(hasVoice * kHasVoiceBonus)) + kZero;
    const CVector3* listener = ListenerPosition(this);
    const float dx = instance->m_position.x - listener->x;
    const float dy = instance->m_position.y - listener->y;
    const float dz = instance->m_position.z - listener->z;
    float d2 = dy * dy;
    d2 = ppc::fmadds(dx, dx, d2);
    d2 = ppc::fmadds(dz, dz, d2);
    float p = kOne / d2;
    p = p * kThousand;
    p = ppc::fmadds(p, kThousand, bonus);
    p = p + kThousand;
    p = p / kPriorityScale;
    p = p * kThousand;
    const uint32_t priority = static_cast<uint32_t>(ppc::fctidz(p));
    instance->m_priority = priority;
    SoundInstance* head = m_pPriorityList;
    if (head != nullptr && head->m_priority > priority) {
        SoundInstance* prev = head;
        for (SoundInstance* it = head->m_pNextPriority; it != nullptr && it->m_priority > priority; it = it->m_pNextPriority) {
            prev = it;
        }
        instance->m_pNextPriority = prev->m_pNextPriority;
        prev->m_pNextPriority = instance;
        return;
    }
    instance->m_pNextPriority = m_pPriorityList;
    m_pPriorityList = instance;
}

// 0x00118340 SoundChannelSet_PauseAll_maybe: every voice (last first), then every playing instance.
void SoundVoiceManager::PauseAll() {
    for (uint32_t i = m_ui32NbVoices; i != 0; --i) m_aVoices[i - 1].Pause();
    for (SoundNode* node = m_pActiveInstances; node != nullptr; node = node->m_pNext) node->m_pInstance->Pause();
}

// 0x001183f0 SoundChannelSet_ResumeAll_maybe
void SoundVoiceManager::ResumeAll() {
    for (uint32_t i = m_ui32NbVoices; i != 0; --i) m_aVoices[i - 1].Resume();
    for (SoundNode* node = m_pActiveInstances; node != nullptr; node = node->m_pNext) node->m_pInstance->Resume();
}

// 0x001187b0 SoundVoiceManager_AcquireChannel_maybe: an instance from the free list (a new one when it
// is empty), initialised and linked at the head of the active list.
SoundInstance* SoundVoiceManager::AcquireChannel(float startSeconds, CKSound* sound) {
    SoundInstance* instance;
    SoundNode* node = m_pFreeInstances;
    if (node == nullptr) {
        instance = new SoundInstance();  // OperatorNew(0x54) + SoundChannel_Reset_maybe
        instance->Initialize(startSeconds, sound);
    } else {
        instance = node->m_pInstance;
        SoundNode* next = node->m_pNext;
        SoundNode_Free(node);
        m_pFreeInstances = next;
        instance->Initialize(startSeconds, sound);
    }
    SoundNode* active = SoundNode_Alloc();
    active->m_pNext = nullptr;
    active->m_pInstance = instance;
    active->m_pNext = m_pActiveInstances;
    m_pActiveInstances = active;
    return instance;
}

// 0x00118b68 SoundEngine_CullAndPrioritise_maybe: beyond the sound's maximum distance, or with the
// listener outside its box (flag 1), an instance gets no voice; the others are sorted by priority.
void SoundVoiceManager::CullAndPrioritise() {
    for (SoundNode* node = m_pActiveInstances; node != nullptr; node = node->m_pNext) {
        SoundInstance* instance = node->m_pInstance;
        const CVector3* l = ListenerPosition(this);
        CKSound* sound = instance->m_pSound;
        const float dy = instance->m_position.y - l->y;
        const float dx = instance->m_position.x - l->x;
        const float dz = instance->m_position.z - l->z;
        float d2 = dy * dy;
        d2 = ppc::fmadds(dx, dx, d2);
        d2 = ppc::fmadds(dz, dz, d2);
        const float distance = std::sqrt(d2);  // 0x00010690 Math_Sqrtf (fsqrts)
        bool audible = !(sound->m_fDistanceMax < distance);
        if (audible && (sound->m_SoundFlags & CKSound::kFlagBoundingBox) != 0) {
            const float* box = sound->m_BoundingBox;  // max x, y, z, min x, y, z
            audible = box[3] <= l->x && box[0] >= l->x && box[5] <= l->z && box[2] >= l->z && box[4] <= l->y &&
                      box[1] >= l->y;
        }
        if (audible) {
            InsertByPriority(instance);
        } else {
            instance->SetVoiceAllowed(0);
        }
    }
}

// 0x00118cf8 SoundEngine_Update_maybe
void SoundVoiceManager::Update(IKTime* clock) {
    m_pListener->Update(clock);
    for (SoundInstance* it = m_pPriorityList; it != nullptr;) {
        SoundInstance* next = it->m_pNextPriority;
        it->m_pNextPriority = nullptr;
        it = next;
    }
    m_pPriorityList = nullptr;
    // the stopped instances go back to the free list; the others not paused run their state machine
    SoundNode* prev = nullptr;
    for (SoundNode* node = m_pActiveInstances; node != nullptr;) {
        SoundInstance* instance = node->m_pInstance;
        if (instance->m_state == SoundInstance::kStateStopped) {
            node = UnlinkActive(this, prev, node);
            instance->Detach();
            PushFree(this, instance);
            continue;
        }
        if ((instance->m_flags & SoundInstance::kFlagPaused) == 0) instance->UpdateState(clock);
        prev = node;
        node = node->m_pNext;
    }
    CullAndPrioritise();
    // the first m_ui32NbVoices of the priority list may hold a voice, the others not
    SoundInstance* it = m_pPriorityList;
    uint32_t i = 0;
    for (; i < m_ui32NbVoices && it != nullptr; ++i, it = it->m_pNextPriority) it->SetVoiceAllowed(1);
    for (; it != nullptr; it = it->m_pNextPriority) it->SetVoiceAllowed(0);
    for (uint32_t v = m_ui32NbVoices; v != 0; --v) m_aVoices[v - 1].ApplyParameters();
}

// 0x00119120 SoundVoiceManager_StopAll_maybe: every voice released (last first), the priority list
// cleared, every active instance detached and freed, the listener reset.
void SoundVoiceManager::StopAll() {
    for (uint32_t v = m_ui32NbVoices; v != 0; --v) {
        if (m_aVoices[v - 1].m_pInstance != nullptr) m_aVoices[v - 1].Release();
    }
    for (SoundInstance* it = m_pPriorityList; it != nullptr;) {
        SoundInstance* next = it->m_pNextPriority;
        it->m_pNextPriority = nullptr;
        it = next;
    }
    m_pPriorityList = nullptr;
    while (m_pActiveInstances != nullptr) {
        SoundInstance* instance = m_pActiveInstances->m_pInstance;
        instance->Detach();
        UnlinkActive(this, nullptr, m_pActiveInstances);
        PushFree(this, instance);
    }
    m_pListener->Reset();
}

// 0x00119d10 SoundBackend_StopSound_maybe: each instance fades out over the sound's fade-out time
// (immediate = 0 and a fade-out time) or stops.
void SoundVoiceManager::StopSound(CKSound* sound, uint8_t immediate) {
    for (uint32_t i = 0; sound->m_pInstances != nullptr && i < sound->CountInstances(); ++i) {
        SoundInstance* instance = sound->GetInstanceAt(i);
        if (immediate == 0 && static_cast<double>(sound->m_fFadeOutTime) != 0.0) {
            if (instance->m_state == SoundInstance::kStateDelay) {
                instance->ChangeState(SoundInstance::kStateStopped);
            } else if (instance->m_state != SoundInstance::kStateStopped) {
                instance->ChangeState(SoundInstance::kStateFadeOut);
                instance->m_flags = (instance->m_flags & ~SoundInstance::kFlagStolen) | SoundInstance::kFlagStolen;
            }
        } else {
            instance->ChangeState(SoundInstance::kStateStopped);
        }
    }
}

// 0x00119e50 SoundBackend_PlaySound_maybe
void SoundVoiceManager::PlaySound(float startSeconds, CKSound* sound) {
    CKSoundManager* manager = g_pEngine->m_soundManager;
    if ((sound->m_SoundFlags & CKSound::kFlagMusic) != 0 && manager->m_pSoundStreamManager->m_unk18 != 0) return;
    if (sound->GetSample() == nullptr || sound->GetSample()->m_pRwaWave == nullptr) return;
    uint32_t flags = sound->m_SoundFlags;
    // a single-instance sound restarts; a looping multi-instance one too
    if ((flags & CKSound::kFlagMultiInstance) == 0 && sound->m_pInstances != nullptr && sound->CountInstances() != 0) {
        sound->Stop(1);
        flags = sound->m_SoundFlags;
    }
    if ((flags & CKSound::kFlagMultiInstance) != 0 && (flags & CKSound::kFlagLoop) != 0 && sound->m_pInstances != nullptr &&
        sound->CountInstances() != 0) {
        sound->Stop(1);
        flags = sound->m_SoundFlags;
    }
    if ((flags & CKSound::kFlagMultiInstance) != 0 && sound->m_ui32MaxInstances <= sound->CountInstances()) {
        SoundInstance* first = sound->GetInstanceAt(0);  // the newest (the list is newest first)
        if (sound->m_eInstanceMode != 1) {
            if (sound->m_eInstanceMode != 2) return;
            if (sound->m_fFadeOutTime != kZero) {
                if (first->m_state == SoundInstance::kStateDelay) {
                    first->ChangeState(SoundInstance::kStateStopped);
                } else if (first->m_state != SoundInstance::kStateStopped) {
                    first->ChangeState(SoundInstance::kStateFadeOut);
                    first->m_flags = (first->m_flags & ~SoundInstance::kFlagStolen) | SoundInstance::kFlagStolen;
                }
                AcquireChannel(startSeconds, sound);
                return;
            }
        }
        first->ChangeState(SoundInstance::kStateStopped);
    }
    AcquireChannel(startSeconds, sound);
}

// 0x001184a0 SoundList_StopFlaggedSounds_maybe: the music-flagged sounds playing on a voice stop (fade).
void SoundVoiceManager::StopFlaggedSounds() {
    for (uint32_t i = 0; i < m_ui32NbVoices; ++i) {
        SoundInstance* instance = m_aVoices[i].m_pInstance;
        if (instance == nullptr) continue;
        CKSound* sound = instance->m_pSound;
        if ((sound->m_SoundFlags & CKSound::kFlagMusic) != 0) sound->Stop(0);
    }
}

// 0x001175c0 SoundBank_StopSectorSounds
void SoundVoiceManager::StopSectorSounds(int32_t sector) {
    for (uint32_t i = 0; i < m_vpSounds.m_ui32NbUsedElt; ++i) {
        CKSound* sound = m_vpSounds.m_pBlock[i];
        if (static_cast<int32_t>(sound->m_iSectorIndex) == sector) Sound_Stop(sound, 1);
    }
}

// 0x00119000 SoundBank_PlaySectorAutoSounds_maybe (the start time is the constant 0.0 at TOC -0x4494)
void SoundVoiceManager::PlaySectorAutoSounds(int32_t sector) {
    const uint32_t count = m_pSoundCodedDictionaryID->m_ui32NbKSound;
    if (count == 0) return;
    for (uint32_t index = 0; index < count; ++index) {
        CKSound* sound = m_pSoundCodedDictionaryID->GetSound(index);
        if (m_vpSounds.m_ui32NbUsedElt == 0) continue;
        bool listed = false;
        for (uint32_t i = 0; i < m_vpSounds.m_ui32NbUsedElt; ++i) {
            if (m_vpSounds.m_pBlock[i] == sound) {
                listed = true;
                break;
            }
        }
        if (!listed) continue;
        if (static_cast<int32_t>(sound->m_iSectorIndex) == sector && (sound->m_SoundFlags & 8) != 0) sound->Play(0.0f);
    }
}
