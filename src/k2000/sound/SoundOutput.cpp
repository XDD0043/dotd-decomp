// SoundOutput.cpp - reconstructed original translation unit 0x114510-0x115058 (GAME_TOC1, main_toc1), 18 functions, 14 live.
// Primary owner: SoundOutput (not a registered class)
// Other owners: SoundOutputEffectMgr (2)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x114510  SoundOutput_GetMasterVolume_maybe
//   [x] 0x114518  SoundOutput_SetMasterVolume_maybe
//   [x] 0x114578  SoundOutputEffectMgr_SetCurrent_maybe
//   [ ] 0x1145a8  SoundOutput_GetOutputMode_maybe
//   [ ] 0x114660  SoundOutput_SetOutputMode_maybe
//   [ ] 0x114720  FUN_00114720  [dead]
//   [ ] 0x114738  SoundOutput_LevelReset_maybe
//   [x] 0x114858  SoundOutput_Construct_maybe
//   [ ] 0x114890  SoundOutput_Construct_2_maybe  [dead]
//   [ ] 0x1148c8  SoundOutput_ClearEffectRefs_maybe
//   [x] 0x1148d8  SoundOutput_Init_maybe
//   [ ] 0x114980  SoundOutput_ShutdownDriver_maybe
//   [ ] 0x114a30  SoundOutput_FreeEffectArrays_maybe
//   [ ] 0x114ab0  SoundOutput_FreeEffectArrays_2_maybe  [dead]
//   [ ] 0x114b30  SoundOutputEffectMgr_SelectByIndex_maybe
//   [x] 0x114b80  SoundOutput_ResetOutputEffect_maybe
//   [x] 0x114bd0  SoundOutput_LoadEffectRefs_maybe
//   [ ] 0x114e78  SoundOutput_SaveEffectRefs_maybe  [dead]
#include "k2000/sound/CKSoundOutput.h"

#include "k2000/core/IKSerializable.h"
#include "k2000/io/IKFile.h"
#include "k2000/managers/CKSoundManager.h"
#include "k2000/managers/CKSoundOutputEffect.h"
#include "k2000/memory/Mem.h"
#include "platform/audio/rwa.h"

// 0x00114510 SoundOutput_GetMasterVolume_maybe
float SoundOutput_GetMasterVolume(CKSoundOutput* output) { return output->m_fVolume; }

// 0x00114518 SoundOutput_SetMasterVolume_maybe: clamped to [0, 1] (NaN gives 0).
void SoundOutput_SetMasterVolume(float volume, CKSoundOutput* output) {
    if (!(volume > 0.0f)) {
        volume = 0.0f;
    } else if (volume > 1.0f) {
        volume = 1.0f;
    }
    output->m_fVolume = volume;
    if (output->m_rwaOutput != nullptr) RwaPS3_SetPortLevel(volume, output->m_rwaOutput);
}

float SoundOutput_GetMasterVolume(CKSoundManager* manager) { return SoundOutput_GetMasterVolume(manager->m_pOutput); }
void SoundOutput_SetMasterVolume(float volume, CKSoundManager* manager) {
    SoundOutput_SetMasterVolume(volume, manager->m_pOutput);
}

// 0x00114858 SoundOutput_Construct_maybe. The stores in the original's order.
CKSoundOutput::CKSoundOutput() {
    m_vpEnvironment.m_pBlock = nullptr;
    m_vpEnvironment.m_ui32NbElt = 1;
    m_vpEnvironment.m_ui32NbUsedElt = 0;
    m_vpUnk18.m_ui32NbElt = 1;
    m_vpUnk18.m_pBlock = nullptr;
    m_vpUnk18.m_ui32NbUsedElt = 0;
    m_rwaOutput = nullptr;
    m_fVolume = 1.0f;
}

// 0x001148d8 SoundOutput_Init_maybe
void CKSoundOutput::Init() {
    m_rwaOutput = RwaPS3Driver_Create();  // RwaPS3Driver_Create_maybe(0, 0, 4, 0, 0)
    m_unk04 = 0x80;
    m_vpUnk18.m_ui32NbElt = 1;
    IKSerializable** block = static_cast<IKSerializable**>(Mem_AllocAligned16(sizeof(IKSerializable*)));
    m_vpEnvironment.m_ui32NbElt = 1;
    m_vpUnk18.m_pBlock = block;
    m_vpEnvironment.m_pBlock = static_cast<IKSerializable**>(Mem_AllocAligned16(sizeof(IKSerializable*)));
    m_pCurrentEffect = nullptr;
}

namespace {

// The inlined reference-list read of SoundOutput_LoadEffectRefs_maybe: a count, the list grown to
// count + 1 slots when it is too small, then the references.
void LoadRefList(TVector<IKSerializable*, 1>* list, IKFile* file) {
    uint32_t count = 0;
    ReadU32LE(file, &count);
    if (count == 0) return;
    if (list->m_ui32NbElt < count) {
        uint32_t capacity = count + 1;
        uint32_t bytes = capacity * static_cast<uint32_t>(sizeof(IKSerializable*));
        if (capacity == 0) {  // as in the original (cannot happen)
            capacity = 1;
            bytes = static_cast<uint32_t>(sizeof(IKSerializable*));
        }
        list->m_pBlock = static_cast<IKSerializable**>(Mem_ReallocAligned16(list->m_pBlock, bytes));
        list->m_ui32NbElt = capacity;
    }
    list->m_ui32NbUsedElt = count;
    IKFile_ReadObjectRefArray(file, list->m_pBlock, count);
}

}  // namespace

// 0x00114bd0 SoundOutput_LoadEffectRefs_maybe
int32_t CKSoundOutput::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    LoadRefList(&m_vpEnvironment, file);
    LoadRefList(&m_vpUnk18, file);
    return 1;
}

// 0x00114578 SoundOutputEffectMgr_SetCurrent_maybe: the level's output (reverb) environment.
void CKSoundOutput::SetCurrentEffect(CKSoundOutputEffect* effect) {
    m_pCurrentEffect = effect;
    RwaPS3Driver_SetOutputEffect(m_rwaOutput, effect->m_rwaOutputEffect);
}

// 0x00114b80 SoundOutput_ResetOutputEffect_maybe: the first environment once, then none current.
void CKSoundOutput::ResetOutputEffect() {
    // BUG(original): with no environment loaded the slot Init allocated is read uninitialised; here it
    // counts as none.
    CKSoundOutputEffect* first =
        m_vpEnvironment.m_ui32NbUsedElt != 0 ? static_cast<CKSoundOutputEffect*>(m_vpEnvironment.m_pBlock[0]) : nullptr;
    m_pCurrentEffect = first;
    if (first != nullptr) RwaPS3Driver_SetOutputEffect(m_rwaOutput, first->m_rwaOutputEffect);
    m_pCurrentEffect = nullptr;
}
