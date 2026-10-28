// CKLinkedBeaconSeq.cpp - reconstructed original translation unit 0x450df0-0x451658 (GAME_TOC1, main_toc1), 24 functions, 16 live.
// Primary class: CKLinkedBeaconSeq  key 0x4a0c  category Logic  size 0x1c  vtable 0xb26e68
// Other owners: CKHkTrackerManager (5), KBase9F0C (1), CKKLBCharacterSparx (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x450df0  CKLinkedBeaconSeq_Delete
//   [x] 0x450e40  CKLinkedBeaconSeq_Construct  [dead]
//   [ ] 0x450e50  CKLinkedBeaconSeq_Construct_2  [dead]
//   [ ] 0x450e60  RegisterCKLinkedBeaconSeqClass
//   [ ] 0x450ed8  _GLOBAL__I_450ed8
//   [x] 0x450ee8  CKLinkedBeaconSeq_DeleteArray
//   [x] 0x450f90  CKLinkedBeaconSeq_CreateArray
//   [x] 0x451028  CKLinkedBeaconSeq_Create
//   [ ] 0x451060  CKLinkedBeaconSeq_Save
//   [ ] 0x451068  CKLinkedBeaconSeq_PostLoad
//   [ ] 0x451070  CKLinkedBeaconSeq_RecursiveRegistration
//   [ ] 0x451110  CKLinkedBeaconSeq_Destroy
//   [x] 0x451188  CKLinkedBeaconSeq_Load
//   [ ] 0x451498  CKLinkedBeaconSeq_Destructor
//   [ ] 0x4514b0  CKLinkedBeaconSeq_Destructor_2  [dead]
//   [ ] 0x4514c8  CKLinkedBeaconSeq_DeletingDestructor
//   [ ] 0x451508  KBase9F0C_vf28
//   [x] 0x451510  CKKLBCharacterSparx_LoadBase_maybe
//   [ ] 0x4515a0  CKHkTrackerManager_Delete
//   [ ] 0x4515f0  CKHkTrackerManager_SetTrackByte48_maybe  [dead]
//   [ ] 0x451608  CKHkTrackerManager_GetTrackByte48_maybe  [dead]
//   [ ] 0x451620  CKHkTrackerManager_SetTrackFloat4C_maybe  [dead]
//   [ ] 0x451638  CKHkTrackerManager_GetTrackFloat4C_maybe  [dead]
//   [ ] 0x451650  KStub_Nop_451650  [dead]
//
//   [ ] 0x9c3d10  CKLinkedBeaconSeq_GetClassType  [inline]
//   [ ] 0x9c3d18  CKLinkedBeaconSeq_GetClassID  [inline]
//   [ ] 0x9c3d20  CKLinkedBeaconSeq_IsKindOfClass  [inline]
//   [ ] 0x9c3d40  KBase9F0C_vf14  [inline]
//   [ ] 0x9c3d48  KBase9F0C_vf18  [inline]
//   [ ] 0x9c3d50  KBase9F0C_vfA8  [inline]
//   [ ] 0x9c3d58  KBase9F0C_vf8  [inline]
//   [ ] 0x9c3d80  KBase9F0C_vf0  [inline]
//   [ ] 0x9c3d98  KBase9F0C_DeletingDestructor  [inline]
#include "k2000/logic/ai/CKLinkedBeaconSeq.h"

#include "k2000/io/IKFile.h"
#include "k2000/logic/ai/CKKLBCharacterBase.h"

// 0x00451188 CKLinkedBeaconSeq_Load: the data is read whatever the type; the references only for
// K_LEVEL_PLATEFORMS.
int32_t CKLinkedBeaconSeq::Load(IKFile* file, int32_t type) {
    ReadU8(file, &m_unk14);
    ReadU32LE(file, &m_unk18);
    ReadS32LE(file, &m_nbEntries);
    ReadU8(file, &m_unk15);
    ReadU8(file, &m_unk16);
    m_aEntries = new Entry[static_cast<uint32_t>(m_nbEntries)];  // OperatorNewArray(count * 8)
    for (int32_t i = 0; i < m_nbEntries; ++i) {
        ReadU8(file, &m_aEntries[i].m_unk0);
        ReadU32LE(file, &m_aEntries[i].m_unk4);
    }
    if (type == K_LEVEL_PLATEFORMS) {
        IKFile_ReadRef(file, &m_pLauncherCpnt);
        IKFile_ReadRef(file, &m_pAnimDictionary);
    }
    return 1;
}

// 0x00451510 CKKLBCharacterSparx_LoadBase_maybe (CKKLBCharacterBase's vt+0x2c)
int32_t CKKLBCharacterBase::Load(IKFile* file, int32_t type) {
    if (type == K_LEVEL_PLATEFORMS) IKFile_ReadRef(file, &m_pBeacon);
    return 1;
}
