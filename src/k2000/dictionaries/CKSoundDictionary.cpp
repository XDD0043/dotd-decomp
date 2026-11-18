// CKSoundDictionary.cpp - reconstructed original translation unit 0x1122f8-0x112b18 (GAME_TOC1, main_toc1), 12 functions, 11 live.
// Primary class: CKSoundDictionary  key 0xc9  category Dictionary  size 0x18  vtable 0xb19830
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1122f8  CKSoundDictionary_Delete
//   [ ] 0x112348  CKSoundDictionary_Save
//   [x] 0x112350  CKSoundDictionary_PostLoad  (IKSerializable's default PostLoad: 1)
//   [x] 0x112358  CKSoundDictionary_RecursiveRegistration
//   [ ] 0x112448  RegisterCKSoundDictionaryClass
//   [ ] 0x1124c0  _GLOBAL__I_1124c0
//   [x] 0x1124d0  CKSoundDictionary_DeleteArray
//   [x] 0x112578  CKSoundDictionary_Create
//   [x] 0x1125d0  CKSoundDictionary_Destroy
//   [ ] 0x1126b0  CKSoundDictionary_GetWave_maybe  [dead]
//   [x] 0x1126e0  CKSoundDictionary_Load
//   [x] 0x112a60  CKSoundDictionary_CreateArray
//
//   [ ] 0x9a6a80  CKSoundDictionary_GetClassType  [inline]
//   [ ] 0x9a6a88  CKSoundDictionary_GetClassID  [inline]
//   [ ] 0x9a6a90  CKSoundDictionary_IsKindOfClass  [inline]
//   [x] 0x9a6ab0  CKSoundDictionary_DeletingDestructor  [inline]
//   [x] 0x9a6b30  CKSoundDictionary_Destructor  [inline]
#include "k2000/dictionaries/CKSoundDictionary.h"

#include "Renderware/rwcore/RwStream.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/sound/CKWave.h"
#include "k2000/memory/Mem.h"
#include "platform/audio/rwa.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/misc/Engine.h"

#include <vector>

// 0x00112578 CKSoundDictionary_Create (the constructor is inlined there)
CKSoundDictionary::CKSoundDictionary() {
    m_apKWave = nullptr;
    m_waveCapacity = 1;
    m_ui32NbSound = 0;
    m_pRwSoundDictionary = nullptr;
}

// 0x00112358 CKSoundDictionary_RecursiveRegistration
void CKSoundDictionary::RecursiveRegistration(int32_t type) {
    if (type != 0) return;
    g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);  // vt+0x24
    for (uint32_t i = 0; i < m_ui32NbSound; ++i) m_apKWave[i]->RecursiveRegistration(0);  // the count re-read each turn
}

// 0x001126e0 CKSoundDictionary_Load
int32_t CKSoundDictionary::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadRaw(file, &m_ui8NumSector, 1);
    if (m_ui8NumSector == -3) return 0;
    uint32_t count = 0;
    ReadU32LE(file, &count);
    if (count == 0) {
        m_waveCapacity = 1;
        m_apKWave = static_cast<IKSerializable**>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(IKSerializable*))));
    } else {
        m_waveCapacity = count;
        m_apKWave = static_cast<IKSerializable**>(Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(IKSerializable*))));
    }
    if (m_waveCapacity < count) {  // as in the original: cannot happen after the assignment above
        uint32_t capacity = count + 1;
        if (capacity == 0) capacity = 1;
        m_apKWave = static_cast<IKSerializable**>(
            Mem_ReallocAligned16(m_apKWave, capacity * static_cast<uint32_t>(sizeof(IKSerializable*))));
        m_waveCapacity = capacity;
    }
    m_ui32NbSound = count;
    for (uint32_t i = 0; i < count; ++i) IKFile_ReadRef(file, &m_apKWave[i]);

    uint32_t length = 0, version = 0;
    if (m_ui32NbSound != 0 && RwStreamFindChunk(file->m_pRwStream, 0x809, &length, &version) != 0) {
        // RwaWaveDict_StreamRead_maybe(0, stream, the output's driver, 0, 0, 0) reads the chunk's payload
        // (platform/audio/rwa.h). On failure the original notifies the sound manager (KStub_Nop_113190),
        // seeks to the end of the chunk and returns 0.
        std::vector<uint8_t> payload(length);
        const uint32_t got = RwStreamRead(file->m_pRwStream, payload.data(), length);
        RwaWaveDict* dict = got == length ? RwaWaveDict_StreamRead(std::move(payload)) : nullptr;
        m_pRwSoundDictionary = dict;
        if (dict == nullptr) return 0;
        RwaWaveDict_GetWaveCount(dict);  // the result is not used
        for (uint32_t i = 0; i < m_ui32NbSound; ++i) {
            static_cast<CKWave*>(m_apKWave[i])->m_pRwaWave = RwaWaveDict_GetWave(m_pRwSoundDictionary, i);
        }
    }
    return 1;
}

// 0x001125d0 CKSoundDictionary_Destroy. The original destroys the dictionary's first wave once per sound
// (RwaWave_Destroy_maybe on RwaWaveDict_GetWave_maybe(dict, 0): a destroyed wave leaves the dictionary), then the
// dictionary (RwaWaveDict_Destroy_maybe). DOTD: the platform dictionary owns its waves (platform/audio/rwa.h), so
// RwaWaveDict_Destroy frees them with it (and takes them from the voices still holding one).
void CKSoundDictionary::Destroy() {
    if (m_pRwSoundDictionary != nullptr) {
        RwaWaveDict_Destroy(m_pRwSoundDictionary);
        m_pRwSoundDictionary = nullptr;
    }
    if (m_apKWave != nullptr) {
        Mem_FreeAligned16(m_apKWave);
        m_apKWave = nullptr;
    }
    m_ui32NbSound = 0;
    m_apKWave = nullptr;
}
