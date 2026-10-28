// CKSoundDictionaryID.cpp - reconstructed original translation unit 0x112b18-0x113080 (GAME_TOC1, main_toc1), 18 functions, 15 live.
// Primary class: CKSoundDictionaryID  key 0x109  category Dictionary  size 0x10  vtable 0xb19888
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x112b18  CKSoundDictionaryID_Delete
//   [ ] 0x112b68  CKSoundDictionaryID_Construct  [dead]
//   [ ] 0x112b88  CKSoundDictionaryID_Construct_2  [dead]
//   [ ] 0x112ba8  CKSoundDictionaryID_RecursiveRegistration
//   [ ] 0x112bb0  CKSoundDictionaryID_Save
//   [ ] 0x112bb8  CKSoundDictionaryID_PostLoad
//   [x] 0x112bc0  CKSoundDictionaryID_GetSound
//   [x] 0x112bd8  CKSoundDictionaryID_GetSound_2
//   [ ] 0x112bf0  RegisterCKSoundDictionaryIDClass
//   [ ] 0x112c68  _GLOBAL__I_112c68
//   [x] 0x112c78  CKSoundDictionaryID_Load
//   [ ] 0x112e30  CKSoundDictionaryID_Destroy
//   [x] 0x112e80  CKSoundDictionaryID_DeleteArray
//   [x] 0x112f20  CKSoundDictionaryID_Create
//   [x] 0x112f68  CKSoundDictionaryID_CreateArray
//   [ ] 0x113010  CKSoundDictionaryID_DeletingDestructor
//   [ ] 0x113050  CKSoundDictionaryID_Destructor
//   [ ] 0x113068  CKSoundDictionaryID_Destructor_2  [dead]
//
//   [ ] 0x9a6b98  CKSoundDictionaryID_GetClassType  [inline]
//   [ ] 0x9a6ba0  CKSoundDictionaryID_GetClassID  [inline]
//   [ ] 0x9a6ba8  CKSoundDictionaryID_IsKindOfClass  [inline]
#include "k2000/dictionaries/CKSoundDictionaryID.h"

#include "k2000/io/IKFile.h"
#include "k2000/logic/sound/CKSound.h"

// 0x00112f20 CKSoundDictionaryID_Create (the constructor is inlined there; 0x112b68 is dead)
CKSoundDictionaryID::CKSoundDictionaryID() {
    m_ui32SectorNum = 0;
    m_apKSound = nullptr;
    m_ui32NbKSound = 0;
}

// 0x00112c78 CKSoundDictionaryID_Load
int32_t CKSoundDictionaryID::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadU32LE(file, &m_ui32NbKSound);
    if (m_ui32NbKSound == 0) {
        m_apKSound = nullptr;
    } else {
        m_apKSound = new CKSound*[m_ui32NbKSound];  // OperatorNewArray(count * 4)
        for (uint32_t i = 0; i < m_ui32NbKSound; ++i) IKFile_ReadRef(file, &m_apKSound[i]);
    }
    ReadU32LE(file, &m_ui32SectorNum);
    return 1;
}

// 0x00112bc0 CKSoundDictionaryID_GetSound
CKSound* CKSoundDictionaryID::GetSound(uint32_t index) { return m_apKSound[index]; }

// 0x00112bd8 CKSoundDictionaryID_GetSound_2 (a second copy of the same code)
CKSound* CKSoundDictionaryID::GetSound2(uint32_t index) { return m_apKSound[index]; }
