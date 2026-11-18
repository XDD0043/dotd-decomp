// CKGrpPoolSquad.cpp - reconstructed original translation unit 0x26a5e0-0x26ad40 (GAME_TOC1, main_toc1), 12 functions, 12 live.
// Primary class: CKGrpPoolSquad  key 0xb04  category Group  size 0x3c  vtable 0xb21890
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x26a5e0  CKGrpPoolSquad_Delete
//   [ ] 0x26a630  CKGrpPoolSquad_vfB8  [dead: vt+0xb8 (returns 1), called only by the dead CKCoreManager 0x1c330 / 0x1d460 (raw ELF scan of the vt+0xb8 calls) and CKGrpS08PoolEnemy_vfB8 (the same slot)]
//   [x] 0x26a638  CKGrpPoolSquad_PostLoad  (header)
//   [ ] 0x26a660  RegisterCKGrpPoolSquadClass
//   [ ] 0x26a6d8  _GLOBAL__I_26a6d8
//   [x] 0x26a6e8  CKGrpPoolSquad_DeleteArray
//   [x] 0x26a790  CKGrpPoolSquad_Create
//   [x] 0x26a820  CKGrpPoolSquad_CreateArray
//   [ ] 0x26a918  CKGrpPoolSquad_Save
//   [x] 0x26a940  CKGrpPoolSquad_Load
//   [x] 0x26abc8  CKGrpPoolSquad_RecursiveRegistration
//   [x] 0x26ace0  CKGrpPoolSquad_Destroy  (CKGrpPoolSquad.h)
//
//   [x] 0x9bba18  CKGrpPoolSquad_GetClassType  [inline]
//   [x] 0x9bba20  CKGrpPoolSquad_GetClassID  [inline]
//   [ ] 0x9bba28  CKGrpPoolSquad_vfCC  [inline]
//   [ ] 0x9bba30  CKGrpPoolSquad_IsKindOfClass  [inline]
//   [ ] 0x9bba88  CKGrpPoolSquad_Destructor  [inline]
//   [ ] 0x9bbaf0  CKGrpPoolSquad_DeletingDestructor  [inline]
#include "k2000/groups/CKGrpPoolSquad.h"

#include "k2000/memory/Mem.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/misc/Engine.h"

// 0x0026a940 CKGrpPoolSquad_Load. A new block only when the vector has none (then with the capacity set to
// the count first); the reserve to the next multiple of 5 never runs on a fresh object.
int32_t CKGrpPoolSquad::Load(IKFile* file, int32_t type) {
    GroupBasicLoad(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    uint32_t count = 0;
    ReadU32LE(file, &count);
    if (count == 0) {
        m_vUnk30.m_ui32NbElt = 5;
        m_vUnk30.m_pBlock = static_cast<IKSerializable**>(Mem_AllocAligned16(5u * static_cast<uint32_t>(sizeof(IKSerializable*))));
    } else {
        if (m_vUnk30.m_pBlock == nullptr) {
            m_vUnk30.m_ui32NbElt = count;
            m_vUnk30.m_pBlock = static_cast<IKSerializable**>(
                Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(IKSerializable*))));
        }
        if (m_vUnk30.m_ui32NbElt < count) {
            uint32_t capacity = (count / 5u) * 5u + 5u;
            if (capacity == 0) capacity = 5;
            m_vUnk30.m_pBlock = static_cast<IKSerializable**>(Mem_ReallocAligned16(
                m_vUnk30.m_pBlock, capacity * static_cast<uint32_t>(sizeof(IKSerializable*))));
            m_vUnk30.m_ui32NbElt = capacity;
        }
        m_vUnk30.m_ui32NbUsedElt = count;
    }
    for (uint32_t i = 0; i < count; ++i) IKFile_ReadRef(file, &m_vUnk30.m_pBlock[i]);
    ReadU8(file, &m_unk2c);
    return 1;
}

// 0x0026abc8 CKGrpPoolSquad_RecursiveRegistration
void CKGrpPoolSquad::RecursiveRegistration(int32_t type) {
    IKBaseGroup::RecursiveRegistration(type);  // 0x00012a68 IKGroup_LevelReset
    if (type != 0) return;
    g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);  // vt+0x24
    for (uint32_t i = 0; i < m_vUnk30.m_ui32NbUsedElt; ++i) m_vUnk30.m_pBlock[i]->RecursiveRegistration(0);  // vt+0x24
}
