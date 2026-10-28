// CKGrpS08SpawnableMushroom.cpp - reconstructed original translation unit 0x4d7218-0x4d8018 (GAME_TOC1, main_toc1), 21 functions, 21 live.
// Primary class: CKGrpS08SpawnableMushroom  key 0xd84  category Group  size 0x84  vtable 0xb2a050
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x4d7218  CKGrpS08SpawnableMushroom_Delete
//   [ ] 0x4d7268  CKGrpS08SpawnableMushroom_vf100
//   [ ] 0x4d7328  CKGrpS08SpawnableMushroom_vfFC
//   [ ] 0x4d7330  RegisterCKGrpS08SpawnableMushroomClass
//   [ ] 0x4d73a8  _GLOBAL__I_4d73a8
//   [ ] 0x4d73b8  CKGrpS08SpawnableMushroom_SpawnFromSectorBeacons_maybe
//   [ ] 0x4d7958  CKGrpS08SpawnableMushroom_SectorLoaded
//   [ ] 0x4d79a0  CKGrpS08SpawnableMushroom_Restart
//   [ ] 0x4d79c8  CKGrpS08SpawnableMushroom_Update
//   [ ] 0x4d79f0  CKGrpS08SpawnableMushroom_Stop
//   [x] 0x4d7a18  CKGrpS08SpawnableMushroom_Start
//   [x] 0x4d7a40  CKGrpS08SpawnableMushroom_MessageProc
//   [ ] 0x4d7a98  CKGrpS08SpawnableMushroom_GetInfo
//   [ ] 0x4d7ae8  CKGrpS08SpawnableMushroom_PostLoad
//   [ ] 0x4d7b10  CKGrpS08SpawnableMushroom_Save
//   [ ] 0x4d7b38  CKGrpS08SpawnableMushroom_RecursiveRegistration
//   [ ] 0x4d7b60  CKGrpS08SpawnableMushroom_Destroy
//   [x] 0x4d7b88  CKGrpS08SpawnableMushroom_DeleteArray
//   [x] 0x4d7c30  CKGrpS08SpawnableMushroom_CreateArray
//   [x] 0x4d7ce8  CKGrpS08SpawnableMushroom_Create
//   [x] 0x4d7d40  CKGrpS08SpawnableMushroom_Load
//
//   [ ] 0x9c3550  CKGrpS08SpawnableMushroom_vfCC  [inline]
//   [ ] 0x9c35e8  CKGrpS08SpawnableMushroom_vfB0  [inline]
//   [ ] 0x9c35f8  CKGrpS08SpawnableMushroom_vfB4  [inline]
//   [ ] 0x9c3608  CKGrpS08SpawnableMushroom_vfBC  [inline]
//   [ ] 0x9c36b0  CKGrpS08SpawnableMushroom_vfE0  [inline]
//   [ ] 0x9c36b8  CKGrpS08SpawnableMushroom_vfE4  [inline]
//   [ ] 0x9c36c0  CKGrpS08SpawnableMushroom_vfE8  [inline]
//   [ ] 0x9c36c8  CKGrpS08SpawnableMushroom_vfD8  [inline]
//   [ ] 0x9c3708  CKGrpS08SpawnableMushroom_vfDC  [inline]
//   [ ] 0x9c5fa8  CKGrpS08SpawnableMushroom_IsKindOfClass  [inline]
//   [x] 0x9c6008  CKGrpS08SpawnableMushroom_GetClassType  [inline]
//   [x] 0x9c6010  CKGrpS08SpawnableMushroom_GetClassID  [inline]
//   [ ] 0x9c6018  CKGrpS08SpawnableMushroom_Pause  [inline]
//   [ ] 0x9c6020  CKGrpS08SpawnableMushroom_Resume  [inline]
//   [ ] 0x9c6028  CKGrpS08SpawnableMushroom_vfF0  [inline]
//   [ ] 0x9c6030  CKGrpS08SpawnableMushroom_vfF4  [inline]
//   [ ] 0x9c6038  CKGrpS08SpawnableMushroom_vf104  [inline]
//   [ ] 0x9c6040  CKGrpS08SpawnableMushroom_vf108  [inline]
//   [ ] 0x9c6058  CKGrpS08SpawnableMushroom_vf10C  [inline]
//   [ ] 0x9c6070  CKGrpS08SpawnableMushroom_vfEC  [inline]
//   [ ] 0x9c6088  CKGrpS08SpawnableMushroom_DeletingDestructor  [inline]
//   [ ] 0x9c6138  CKGrpS08SpawnableMushroom_Destructor  [inline]
#include "Spyro2008/groups/CKGrpS08SpawnableMushroom.h"

// 0x004d7d40 CKGrpS08SpawnableMushroom_Load
int32_t CKGrpS08SpawnableMushroom::Load(IKFile* file, int32_t type) {
    KBase1944::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadU8(file, &m_unk5d);
    ReadF32LE(file, &m_unk60.x);  // one 0xc-byte read, three swaps
    ReadF32LE(file, &m_unk60.y);
    ReadF32LE(file, &m_unk60.z);
    IKFile_ReadRef(file, &m_pUnk70);
    IKFile_ReadRef(file, &m_pUnk6c);
    ReadU8(file, &m_unk74);
    ReadU32LE(file, &m_unk78);
    IKFile_ReadRef(file, &m_pUnk7c);
    ReadF32LE(file, &m_unk80);
    return 1;
}

// 0x004d7a40 CKGrpS08SpawnableMushroom_MessageProc
int32_t CKGrpS08SpawnableMushroom::MessageProc(uint16_t message, void* data) {
    const int32_t result = KBase1944::MessageProc(message, data);
    if (result == 3) return 3;
    if (result == 2) return 2;
    return result != 0 ? 1 : 0;  // ((|r| - 1) >> 31) ^ 1, the low two bits kept
}

// 0x004d7a18 CKGrpS08SpawnableMushroom_Start
void CKGrpS08SpawnableMushroom::Start() {
    KBase1944::Start();  // 0x443d58
}
