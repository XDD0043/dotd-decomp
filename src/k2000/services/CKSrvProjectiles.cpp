// CKSrvProjectiles.cpp - reconstructed original translation unit 0x1f32e0-0x1f3d98 (GAME_TOC1, main_toc1), 26 functions, 26 live.
// Primary class: CKSrvProjectiles  key 0x341  category Service  size 0x14  vtable 0xb1e8b8
// Other owners: IKProjectileType (2), CKProjectileType (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1f32e0  CKSrvProjectiles_Delete
//   [ ] 0x1f3330  CKSrvProjectiles_UpdateAll
//   [x] 0x1f3588  CKSrvProjectiles_InitializeService
//   [x] 0x1f3590  CKSrvProjectiles_DestroyService
//   [ ] 0x1f3598  RegisterCKSrvProjectilesClass
//   [ ] 0x1f3610  _GLOBAL__I_1f3610
//   [x] 0x1f3620  CKSrvProjectiles_Construct
//   [ ] 0x1f3680  CKSrvProjectiles_Construct_2
//   [x] 0x1f36e0  CKSrvProjectiles_DeleteArray
//   [x] 0x1f3788  CKSrvProjectiles_CreateArray
//   [x] 0x1f3898  CKSrvProjectiles_Create
//   [ ] 0x1f3918  CKSrvProjectiles_MessageProc
//   [x] 0x1f3920  CKSrvProjectiles_Destroy
//   [ ] 0x1f3968  CKSrvProjectiles_RecursiveRegistration
//   [ ] 0x1f3970  CKSrvProjectiles_Save
//   [x] 0x1f3978  CKSrvProjectiles_Load
//   [ ] 0x1f3ad8  CKSrvProjectiles_Start
//   [x] 0x1f3ae0  CKSrvProjectiles_Stop
//   [ ] 0x1f3bb0  CKSrvProjectiles_Pause
//   [ ] 0x1f3bb8  CKSrvProjectiles_Resume
//   [ ] 0x1f3bc0  CKSrvProjectiles_Restart
//   [ ] 0x1f3c00  UpdateCKSrvProjectiles
//   [ ] 0x1f3c38  IKProjectileType_ClearReferences
//   [ ] 0x1f3c90  KStub_Return1_1f3c90
//   [ ] 0x1f3c98  IKProjectileType_vf28
//   [x] 0x1f3ca0  CKProjectileType_LoadBase
//
//   [ ] 0x9b07d8  CKSrvProjectiles_IsKindOfClass  [inline]
//   [ ] 0x9b0810  CKSrvProjectiles_GetClassType  [inline]
//   [ ] 0x9b0818  CKSrvProjectiles_GetClassID  [inline]
//   [ ] 0x9b0820  CKSrvProjectiles_Destructor  [inline]
//   [ ] 0x9b0840  CKSrvProjectiles_DeletingDestructor  [inline]
//   [ ] 0x9b0888  IKProjectileType_vf14  [inline]
//   [ ] 0x9b0890  IKProjectileType_vf18  [inline]
//   [ ] 0x9b0898  KStub_Return0_9b0898  [inline]
//   [ ] 0x9b08a0  IKProjectileType_vf6C  [inline]
//   [ ] 0x9b08f0  IKProjectileType_vf70  [inline]
//   [ ] 0x9b0938  IKProjectileType_vf74  [inline]
//   [ ] 0x9b0980  KStub_Return0_9b0980  [inline]
//   [ ] 0x9b0988  KStub_Return0_9b0988  [inline]
//   [ ] 0x9b0990  IKProjectileType_vf80  [inline]
//   [ ] 0x9b0ab0  IKProjectileType_vf8C  [inline]
//   [ ] 0x9b0b98  IKProjectileType_vf90  [inline]
//   [ ] 0x9b0be8  KStub_Return0_9b0be8  [inline]
//   [ ] 0x9b0c50  IKProjectileType_vf8  [inline]
//   [ ] 0x9b0c70  IKProjectileType_vf0  [inline]
//   [ ] 0x9b0c88  IKProjectileType_DeletingDestructor  [inline]
#include "k2000/services/CKSrvProjectiles.h"

#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"
#include "k2000/services/IKProjectileType.h"
#include "k2000/misc/Engine.h"

// 0x001f3620 CKSrvProjectiles_Construct (the same stores inlined in 0x1f3898 CKSrvProjectiles_Create).
CKSrvProjectiles::CKSrvProjectiles() {
    m_ui32Priority = 0xc8;
    Engine_SetProjectilesService(this);
}

// 0x001f3920 CKSrvProjectiles_Destroy: the pool array freed.
void CKSrvProjectiles::Destroy() {
    // BUG(original): freed, the pointer and the count kept (the next Load replaces them).
    if (m_apProjectilePoolList != nullptr) Mem_FreeAligned16(m_apProjectilePoolList);
}

// 0x001f3978 CKSrvProjectiles_Load: a byte count, then the pool references.
int32_t CKSrvProjectiles::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadU8(file, &m_ui8NbOfProjectilePools);
    if (m_ui8NbOfProjectilePools == 0) {
        m_apProjectilePoolList = nullptr;
        return 1;
    }
    m_apProjectilePoolList = static_cast<IKSerializable**>(
        Mem_AllocAligned16(m_ui8NbOfProjectilePools * static_cast<uint32_t>(sizeof(IKSerializable*))));
    IKFile_ReadObjectRefArray(file, m_apProjectilePoolList, m_ui8NbOfProjectilePools);
    return 1;
}
#include "k2000/services/IKProjectileType.h"

#include "k2000/io/IKFile.h"

// 0x001f3ca0 CKProjectileType_LoadBase: the record count and the options; level data only (5 bytes).
int32_t IKProjectileType::Load(IKFile* file, int32_t type) {
    if (type == K_LEVEL_PLATEFORMS) {
        ReadU8(file, &m_ui8MaxProjectiles);
        ReadU32LE(file, &m_baOptions);
        m_ui8NbOfActiveProjectiles = 0;
        m_GrdContDatasIn.m_MasksOfGrdForTest[0] = 1;
        m_GrdContDatasIn.m_MasksOfGrdForTest[1] = 0;
    }
    return 1;
}

// 0x001f3ae0 CKSrvProjectiles_Stop: every pool kills its active projectiles one by one (index 0).
// BUG(original): a pool whose KillProjectile does not lower the active count would loop forever.
void CKSrvProjectiles::Stop() {
    for (uint32_t i = 0; i < m_ui8NbOfProjectilePools; ++i) {
        IKProjectileType* pool = static_cast<IKProjectileType*>(m_apProjectilePoolList[i]);
        while (pool->m_ui8NbOfActiveProjectiles != 0) pool->KillProjectile(0);
    }
}
