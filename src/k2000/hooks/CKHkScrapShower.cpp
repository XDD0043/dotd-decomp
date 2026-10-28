// CKHkScrapShower.cpp - reconstructed original translation unit 0x4a40d0-0x4a66d0 (GAME_TOC1, main_toc1), 28 functions, 26 live.
// Primary class: CKHkScrapShower  key 0x1242  category Hook  size 0x12c  vtable 0xb285c8
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x4a40d0  RegisterCKHkScrapShowerClass
//   [ ] 0x4a4148  _GLOBAL__I_4a4148
//   [ ] 0x4a4158  CKHkScrapShower_GetInfo
//   [ ] 0x4a4240  CKHkScrapShower_PickDropPosition_maybe
//   [ ] 0x4a47f8  CKHkScrapShower_Resume
//   [ ] 0x4a4820  CKHkScrapShower_Pause
//   [ ] 0x4a4848  CKHkScrapShower_Stop
//   [ ] 0x4a4870  CKHkScrapShower_Start
//   [ ] 0x4a49c0  CKHkScrapShower_PostLoad
//   [ ] 0x4a4a00  CKHkScrapShower_Save
//   [ ] 0x4a4a28  CKHkScrapShower_RecursiveRegistration
//   [ ] 0x4a4a50  CKHkScrapShower_Destroy
//   [x] 0x4a4ab0  CKHkScrapShower_DeleteArray
//   [x] 0x4a4b50  CKHkScrapShower_Construct  [dead]
//   [ ] 0x4a4bd0  CKHkScrapShower_OnActivate
//   [ ] 0x4a4ce8  CKHkScrapShower_BaseDestructor
//   [ ] 0x4a4d18  CKHkScrapShower_vfC8
//   [ ] 0x4a4d68  CKHkScrapShower_SetDefaultState
//   [ ] 0x4a4db0  CKHkScrapShower_DeletingDestructor
//   [ ] 0x4a4df8  CKHkScrapShower_Destructor
//   [ ] 0x4a4e28  CKHkScrapShower_OnDeactivate
//   [ ] 0x4a4f18  CKHkScrapShower_Update
//   [ ] 0x4a5770  CKHkScrapShower_Construct_2  [dead]
//   [ ] 0x4a57f0  CKHkScrapShower_MessageProc
//   [ ] 0x4a5aa8  CKHkScrapShower_Restart
//   [x] 0x4a5bb8  CKHkScrapShower_CreateArray
//   [x] 0x4a5ce0  CKHkScrapShower_Create
//   [x] 0x4a5d78  CKHkScrapShower_Load
//
//   [ ] 0x9c4e50  CKHkScrapShower_IsKindOfClass  [inline]
//   [ ] 0x9c4ea8  CKHkScrapShower_GetClassType  [inline]
//   [ ] 0x9c4eb0  CKHkScrapShower_GetClassID  [inline]
//   [ ] 0x9c4eb8  CKHkScrapShower_GetTriggerProp9B  [inline]
#include "k2000/hooks/CKHkScrapShower.h"

#include "k2000/io/IKFile.h"

// 0x004a5d78 CKHkScrapShower_Load: every multi-byte read is swapped (lwbrx per word), the four single
// bytes are not.
int32_t CKHkScrapShower::Load(IKFile* file, int32_t type) {
    CKHkActorBase::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(&m_unk20), 3);
    ReadF32LE(file, &m_unk2c);
    ReadF32LE(file, &m_unkC0);
    ReadU8(file, &m_ui8NbUnk58);
    m_unk58 = new uint32_t[m_ui8NbUnk58];
    m_unk5c = new uint32_t[m_ui8NbUnk58];
    for (uint32_t i = 0; i < m_ui8NbUnk58; ++i) {
        ReadU32LE(file, &m_unk58[i]);
        ReadU32LE(file, &m_unk5c[i]);
    }
    for (uint32_t i = 0; i < 9; ++i) ReadF32LE(file, &m_unk60[i]);
    ReadU8(file, &m_unkA0);
    for (uint32_t i = 0; i < 3; ++i) ReadF32LE(file, &m_unkA4[i]);
    IKFile_ReadRef(file, &m_unk30);
    IKFile_ReadRef(file, &m_unk84);
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(&m_unk88), 3);
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(m_unk94), 2);
    IKFile_ReadRef(file, &m_unk9c);
    m_unkC4.Load(file, K_LEVEL_PLATEFORMS);
    m_unkCC.Load(file, K_LEVEL_PLATEFORMS);
    IKFile_ReadRef(file, &m_unkD4);
    ReadU8(file, &m_unkD8);
    ReadU8(file, &m_unkD9);
    ReadU8(file, &m_unkBC);
    for (uint32_t i = 0; i < 3; ++i) ReadF32LE(file, &m_unkB0[i]);
    return 1;
}
