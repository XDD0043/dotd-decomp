// CKGrpS08PoolEnemy.cpp - reconstructed original translation unit 0x26ad40-0x26b348 (GAME_TOC1, main_toc1), 13 functions, 13 live.
// Primary class: CKGrpS08PoolEnemy  key 0xb44  category Group  size 0x48  vtable 0xb21988
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x26ad40  CKGrpS08PoolEnemy_Delete
//   [ ] 0x26ad90  CKGrpS08PoolEnemy_vfB8
//   [ ] 0x26adb8  CKGrpS08PoolEnemy_PostLoad
//   [ ] 0x26ade0  CKGrpS08PoolEnemy_Save
//   [ ] 0x26ae08  CKGrpS08PoolEnemy_RecursiveRegistration
//   [ ] 0x26ae30  CKGrpS08PoolEnemy_Destroy
//   [x] 0x26ae58  CKGrpS08PoolEnemy_DeleteArray
//   [x] 0x26af00  CKGrpS08PoolEnemy_Create
//   [ ] 0x26afb8  RegisterCKGrpS08PoolEnemyClass
//   [ ] 0x26b040  _GLOBAL__D_26b040
//   [ ] 0x26b050  _GLOBAL__I_26b050
//   [x] 0x26b060  CKGrpS08PoolEnemy_CreateArray
//   [x] 0x26b168  CKGrpS08PoolEnemy_Load
//
//   [ ] 0x9bbb60  CKGrpS08PoolEnemy_IsKindOfClass  [inline]
//   [x] 0x9bbbc0  CKGrpS08PoolEnemy_GetClassType  [inline]
//   [x] 0x9bbbc8  CKGrpS08PoolEnemy_GetClassID  [inline]
//   [ ] 0x9bbbd0  CKGrpS08PoolEnemy_vfCC  [inline]
//   [ ] 0x9bbbd8  CKGrpS08PoolEnemy_vfEC  [inline]
//   [ ] 0x9bbbe0  CKGrpS08PoolEnemy_DeletingDestructor  [inline]
//   [ ] 0x9bbc68  CKGrpS08PoolEnemy_Destructor  [inline]
#include "Spyro2008/groups/CKGrpS08PoolEnemy.h"

#include "k2000/groups/TVectorPush.h"

// 0x0026b168 CKGrpS08PoolEnemy_Load. No type test after the base: a new one-element block (the old one is
// not freed, the count kept), then per reference a push (grows by 1).
int32_t CKGrpS08PoolEnemy::Load(IKFile* file, int32_t type) {
    CKGrpPoolSquad::Load(file, type);
    uint32_t count = 0;
    ReadU32LE(file, &count);
    m_vSquadPools.m_ui32NbElt = 1;
    m_vSquadPools.m_pBlock =
        static_cast<IKSerializable**>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(IKSerializable*))));
    for (uint32_t i = 0; i < count; ++i) {
        IKSerializable* ref = nullptr;
        IKFile_ReadRef(file, &ref);
        TVector_GrowIfFull(m_vSquadPools);
        m_vSquadPools.m_pBlock[m_vSquadPools.m_ui32NbUsedElt++] = ref;
    }
    return 1;
}
