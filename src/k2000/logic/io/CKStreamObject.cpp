// CKStreamObject.cpp - reconstructed original translation unit 0x11a0c8-0x11b0a0 (GAME_TOC1, main_toc1), 31 functions, 27 live.
// Primary class: CKStreamObject  key 0x5a4c  category Logic  size 0x3c  vtable 0xb19a00
// Other owners: SoundInstance (2), CKSekens (2), SoundStreamTrack (1), CKSekensDataBuffers (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x11a0c8  CKStreamObject_Delete
//   [ ] 0x11a118  CKStreamObject_RecursiveRegistration
//   [ ] 0x11a178  CKStreamObject_ResetPlaybackFields_maybe  [dead]
//   [x] 0x11a1b8  CKStreamObject_SetFloat20AndInt1C_maybe
//   [x] 0x11a1c8  CKStreamObject_SetVolumeWithFade_maybe
//   [ ] 0x11a220  RegisterCKStreamObjectClass
//   [ ] 0x11a298  _GLOBAL__I_11a298
//   [ ] 0x11a2a8  CKStreamObject_GetStreamState_maybe
//   [x] 0x11a2e8  CKStreamObject_GetPlaybackPosition_maybe
//   [ ] 0x11a350  CKStreamObject_Unpause_maybe
//   [ ] 0x11a380  SoundInstance_Resume_maybe
//   [ ] 0x11a3c0  SoundInstance_Pause_maybe
//   [x] 0x11a400  CKStreamObject_DeleteArray
//   [x] 0x11a4a8  CKStreamObject_Create
//   [ ] 0x11a4f8  SoundStreamTrack_UpdateFader_maybe
//   [x] 0x11a538  FUN_0011a538
//   [ ] 0x11a5a8  CKStreamObject_IsStreamState6_maybe  [dead]
//   [ ] 0x11a5d8  CKStreamObject_GetLength_maybe
//   [x] 0x11a5f8  CKStreamObject_CreateArray
//   [ ] 0x11a6b0  CKStreamObject_PostLoad
//   [x] 0x11a6b8  CKStreamObject_ResetRuntime_maybe
//   [ ] 0x11a720  CKStreamObject_Destroy
//   [x] 0x11a728  CKStreamObject_Play_maybe
//   [x] 0x11a870  CKStreamObject_Stop_maybe
//   [x] 0x11a958  CKStreamObject_Load
//   [ ] 0x11aba8  CKStreamObject_Save
//   [ ] 0x11ad88  FUN_0011ad88  [dead]
//   [x] 0x11ada0  CKSekensDataBuffers_Construct_maybe
//   [ ] 0x11adb8  KStub_Return1_11adb8  [dead]
//   [x] 0x11adc0  CKSekens_FreeDataBuffers_maybe
//   [x] 0x11ae30  CKSekens_LoadDataBuffers_maybe
//
//   [ ] 0x9a6ca0  CKStreamObject_GetClassType  [inline]
//   [ ] 0x9a6ca8  CKStreamObject_GetClassID  [inline]
//   [ ] 0x9a6cb0  CKStreamObject_Destructor  [inline]
//   [ ] 0x9a6cc8  CKStreamObject_IsKindOfClass  [inline]
//   [ ] 0x9a6ce8  CKStreamObject_DeletingDestructor  [inline]
#include "k2000/logic/io/CKStreamObject.h"

#include "k2000/core/Stub.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/sound/CKStreamWave.h"
#include "k2000/managers/CKSoundManager.h"
#include "k2000/misc/Engine.h"
#include "k2000/sound/CKSoundStreamManager.h"
#include "k2000/sound/SoundStreamType.h"
#include "k2000/sound/SpeechStreamModel.h"
#include <cmath>
#include <cstring>

// Inlined in 0x0011a4a8 CKStreamObject_Create.
CKStreamObject::CKStreamObject() {
    m_unk2c = 0.0f;
    m_unk34 = 0.0f;
    m_unk30 = 0.0f;
}

// 0x0011a958 CKStreamObject_Load: the fields after the reads are reset whatever the type.
int32_t CKStreamObject::Load(IKFile* file, int32_t type) {
    if (type == K_LEVEL_PLATEFORMS) {
        IKFile_ReadRef(file, &m_pStreamWave);
        ReadF32LE(file, &m_unk10);
        ReadF32LE(file, &m_unk14);
        ReadF32LE(file, &m_unk18);
        ReadU8(file, &m_unk24);
        ReadF32LE(file, &m_unk28);
    }
    m_unk08 = nullptr;
    m_unk0c = nullptr;
    m_unk30 = 0.0f;
    m_unk34 = m_unk28;
    m_unk2c = m_unk28;
    m_unk20 = 0;
    m_unk39 = 0;
    m_unk1c = -1;
    return 1;
}

#include "k2000/logic/CKSekens.h"
#include "k2000/memory/Mem.h"

// 0x0011ada0 CKSekensDataBuffers_Construct_maybe
CKSekensDataBuffers::CKSekensDataBuffers() {
    m_aBytes = nullptr;
    m_aWords0 = nullptr;
    m_aWords1 = nullptr;
}

// 0x0011adc0 CKSekens_FreeDataBuffers_maybe (the pointers are left as they are).
void CKSekensDataBuffers::Free() {
    if (m_aWords0 != nullptr) Mem_FreeAligned16(m_aWords0);
    if (m_aWords1 != nullptr) Mem_FreeAligned16(m_aWords1);
    if (m_aBytes != nullptr) Mem_FreeAligned16(m_aBytes);
}

// 0x0011ae30 CKSekens_LoadDataBuffers_maybe
int32_t CKSekensDataBuffers::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_LOCALIZATION) return 1;
    ReadU8(file, &m_count);
    ReadU8(file, &m_unk05);
    if (m_count == 0) return 1;
    if (m_aWords0 != nullptr) Mem_FreeAligned16(m_aWords0);
    m_aWords0 = static_cast<uint32_t*>(Mem_AllocAligned16(static_cast<uint32_t>(m_count) * 4u));
    ReadU32LEWords(file, m_aWords0, m_count);
    if (m_aWords1 != nullptr) Mem_FreeAligned16(m_aWords1);
    m_aWords1 = static_cast<uint32_t*>(Mem_AllocAligned16(static_cast<uint32_t>(m_count) * 4u));
    ReadU32LEWords(file, m_aWords1, m_count);
    if (m_aBytes != nullptr) Mem_FreeAligned16(m_aBytes);
    m_aBytes = static_cast<uint8_t*>(Mem_AllocAligned16(m_count));
    ReadRaw(file, m_aBytes, m_count);
    return 1;
}

// 0x0011a6b8 CKStreamObject_ResetRuntime_maybe
void CKStreamObject::ResetRuntime() {
    m_unk28 = 1.0f;
    m_unk18 = 1.0f;
    m_unk10 = 0.0f;
    m_unk14 = 0.0f;
    m_unk38 = 0;
    m_unk24 = 0;
    m_pStreamWave = nullptr;
    m_pad3a[0] = 0;
    m_unk08 = nullptr;
    m_unk0c = nullptr;
    m_unk30 = 0.0f;
    m_unk34 = m_unk28;
    m_unk2c = m_unk28;
    m_unk20 = 0;
    m_unk39 = 0;
    m_unk1c = -1;
}

// 0x0011a870 CKStreamObject_Stop_maybe. Only a stream that is playing (+0x08, the stream type Play sets) does anything:
// a paused one is resumed (STUB(C2.3 audio): never paused here), the target volume goes to 0 and the current one
// follows at once or by a ramp of the fade time (+0x14), then the stream type drops the stream.
void CKStreamObject::Stop(int32_t immediate) {
    if (m_unk08 == nullptr) return;
    if (m_unk38 != 0) {
        DOTD_STUB_ONCE("CKStreamObject_Stop_maybe 0x11a870: SoundEmitterGroup_ResumeVoiceOf_maybe of a paused stream (C2.3 audio)");
        m_unk38 = 0;
    }
    m_unk2c = 0.0f;
    if (m_unk14 == 0.0f || immediate == 0) {
        m_unk34 = 0.0f;
    } else {
        m_unk30 = std::fabs(m_unk34 / m_unk14);
    }
    speech_model::Stop(this);  // SoundStreamType_StopObject_maybe 0x11e1b0
}

// 0x0011a728 CKStreamObject_Play_maybe
void CKStreamObject::Play(SoundStreamType* type, int32_t fade) {
    if (m_pStreamWave == nullptr) return;
    CKStreamWave* wave = static_cast<CKStreamWave*>(m_pStreamWave);
    // The wave records whether the stream type is the "Musics" one.
    wave->m_unk218 = type == g_pEngine->m_soundManager->m_pSoundStreamManager->FindTypeByName("Musics") ? 1 : 0;
    if (wave->m_unk218 == 0) {
        // BUG(original): a stream of another type needs the wave's length (+0x04) to be non-zero, and the speech wave the
        // sekensor shares is never given one (heap residue on the PS3: non-zero in the capture). The test is not made.
    }
    m_unk08 = type;
    m_unk38 = 0;
    m_unk34 = 0.0f;
    if (m_unk10 == 0.0f || fade == 0) m_unk34 = m_unk28;
    m_unk2c = m_unk28;
    if (m_unk10 == 0.0f || fade == 0) {
        m_unk34 = m_unk28;
    } else {
        m_unk30 = std::fabs((m_unk34 - m_unk28) / m_unk10);
    }
    speech_model::Play(this);  // SoundStreamType_PlayObject_maybe 0x11e818
}

// 0x0011a1b8 CKStreamObject_SetFloat20AndInt1C_maybe
void CKStreamObject::SetFloat20AndInt1C(float offset, int32_t item) {
    std::memcpy(&m_unk20, &offset, 4);
    m_unk1c = item;
}

// 0x0011a1c8 CKStreamObject_SetVolumeWithFade_maybe
void CKStreamObject::SetVolumeWithFade(float volume, float fadeTime, int32_t instant) {
    m_unk2c = volume;
    if (fadeTime != 0.0f && instant == 0) {
        m_unk30 = std::fabs(static_cast<float>(static_cast<double>(static_cast<float>(static_cast<double>(m_unk34) - volume)) / fadeTime));
        return;
    }
    m_unk34 = volume;
}

// 0x0011a2e8 CKStreamObject_GetPlaybackPosition_maybe
void CKStreamObject::GetPlaybackPosition(int32_t* item, float* position) const { speech_model::GetPlayback(this, item, position); }

// FUN_0011a538
uint8_t CKStreamObject::IsFinished() const { return speech_model::IsFinished(this) ? 1 : 0; }

bool CKStreamObject::HasPlayer() const { return speech_model::HasPlayer(this); }
