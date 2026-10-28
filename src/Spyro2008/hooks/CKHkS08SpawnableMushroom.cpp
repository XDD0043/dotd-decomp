// CKHkS08SpawnableMushroom.cpp - reconstructed original translation unit 0x4d8018-0x4da838 (GAME_TOC1, main_toc1), 36 functions, 33 live.
// Primary class: CKHkS08SpawnableMushroom  key 0x3342  category Hook  size 0x60  vtable 0xb2a168
// Other owners: CKHkS08Fire (2)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x4d8018  CKHkS08SpawnableMushroom_Delete
//   [ ] 0x4d8068  CKHkS08SpawnableMushroom_Restart
//   [ ] 0x4d8070  CKHkS08SpawnableMushroom_Pause
//   [ ] 0x4d8078  CKHkS08SpawnableMushroom_Resume
//   [ ] 0x4d8080  FUN_004d8080  [dead]
//   [ ] 0x4d8230  CKHkS08SpawnableMushroom_vfF0
//   [ ] 0x4d8240  CKHkS08SpawnableMushroom_MessageProc
//   [ ] 0x4d8298  CKHkS08SpawnableMushroom_FaceTowards_maybe
//   [ ] 0x4d8440  CKHkS08SpawnableMushroom_Stop
//   [x] 0x4d8468  CKHkS08SpawnableMushroom_Start
//   [x] 0x4d8490  CKHkS08SpawnableMushroom_PostLoad
//   [ ] 0x4d84f8  CKHkS08SpawnableMushroom_Save
//   [ ] 0x4d8520  CKHkS08SpawnableMushroom_RecursiveRegistration
//   [ ] 0x4d8548  CKHkS08SpawnableMushroom_Destroy
//   [ ] 0x4d8590  CKHkS08SpawnableMushroom_Construct_2  [dead]
//   [x] 0x4d8600  CKHkS08SpawnableMushroom_DeleteArray
//   [ ] 0x4d86b0  CKHkS08SpawnableMushroom_Destructor_2
//   [ ] 0x4d8730  RegisterCKHkS08SpawnableMushroomClass
//   [ ] 0x4d87b8  _GLOBAL__D_4d87b8
//   [ ] 0x4d87c8  _GLOBAL__I_4d87c8
//   [ ] 0x4d87d8  CKHkS08SpawnableMushroom_AttachSounds
//   [ ] 0x4d8968  CKHkS08SpawnableMushroom_vf98
//   [x] 0x4d89b0  CKHkS08SpawnableMushroom_Construct
//   [ ] 0x4d8a20  CKHkS08SpawnableMushroom_Destroy_maybe
//   [x] 0x4d9088  CKHkS08SpawnableMushroom_Create
//   [x] 0x4d9110  CKHkS08SpawnableMushroom_CreateArray
//   [ ] 0x4d9220  CKHkS08SpawnableMushroom_DeletingDestructor
//   [ ] 0x4d92b0  CKHkS08SpawnableMushroom_Destructor
//   [ ] 0x4d9330  CKHkS08SpawnableMushroom_vf94
//   [x] 0x4d9a98  CKHkS08SpawnableMushroom_Load
//   [ ] 0x4d9cd8  CKHkS08SpawnableMushroom_ApplyDamage_maybe
//   [ ] 0x4da360  CKHkS08SpawnableMushroom_ProcessDamageContacts_maybe
//   [ ] 0x4da698  CKHkS08SpawnableMushroom_Update
//   [ ] 0x4da7a0  CKHkS08Fire_Delete
//   [ ] 0x4da7f0  CKHkS08Fire_vfC8
//   [ ] 0x4da818  FUN_004da818  [dead]
//
//   [ ] 0x9c61e0  CKHkS08SpawnableMushroom_IsKindOfClass  [inline]
//   [ ] 0x9c6240  CKHkS08SpawnableMushroom_GetClassType  [inline]
//   [ ] 0x9c6248  CKHkS08SpawnableMushroom_GetClassID  [inline]
#include "Spyro2008/hooks/CKHkS08SpawnableMushroom.h"

#include "k2000/io/IKFile.h"
#include "k2000/misc/Mat4.h"

// 0x004d9a98 CKHkS08SpawnableMushroom_Load
int32_t CKHkS08SpawnableMushroom::Load(IKFile* file, int32_t type) {
    KBase42C2::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    IKFile_ReadRef(file, &m_pUnk4C);
    IKFile_ReadRef(file, &m_pUnk54);
    IKFile_ReadRef(file, &m_pUnk50);
    IKFile_ReadRef(file, &m_pUnk5C);
    return 1;
}

// 0x004d8490 CKHkS08SpawnableMushroom_PostLoad: KBase42C2's part (0x445a68), then for the level type the two
// RwMatrix, +0x48 first.
int32_t CKHkS08SpawnableMushroom::PostLoad(int32_t type) {
    KBase42C2::PostLoad(type);
    if (type == K_LEVEL_PLATEFORMS) {
        m_pUnk48 = RwMatrixCreate_Thunk();
        m_pUnk44 = RwMatrixCreate_Thunk();
    }
    return 1;
}

// 0x004d8468 CKHkS08SpawnableMushroom_Start
void CKHkS08SpawnableMushroom::Start() {
    KBase42C2::Start();  // 0x445c70
}
