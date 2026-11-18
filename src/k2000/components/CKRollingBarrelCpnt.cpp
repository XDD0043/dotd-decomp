// CKRollingBarrelCpnt.cpp - reconstructed original translation unit 0x441860-0x441f60 (GAME_TOC1, main_toc1), 16 functions, 14 live.
// Primary class: CKRollingBarrelCpnt  key 0xd86  category Component  size 0x10  vtable 0xb265f8
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x441860  CKRollingBarrelCpnt_Delete
//   [ ] 0x4418b0  RegisterCKRollingBarrelCpntClass
//   [ ] 0x441928  _GLOBAL__I_441928
//   [x] 0x441938  CKRollingBarrelCpnt_PostLoad  (the base's, inherited)
//   [x] 0x441960  CKRollingBarrelCpnt_Load
//   [ ] 0x441b28  CKRollingBarrelCpnt_Save
//   [x] 0x441b50  CKRollingBarrelCpnt_RecursiveRegistration  (the base's, inherited)
//   [x] 0x441b78  CKRollingBarrelCpnt_Destroy  (the base's, inherited)
//   [ ] 0x441ba0  CKRollingBarrelCpnt_DestructBody  [dead: no pointer to its descriptor 0xbb9e08]
//   [ ] 0x441bf8  CKRollingBarrelCpnt_Construct  [dead]
//   [ ] 0x441c58  CKRollingBarrelCpnt_Construct_2  [dead]
//   [x] 0x441cb8  CKRollingBarrelCpnt_DeleteArray
//   [x] 0x441d58  CKRollingBarrelCpnt_DeletingDestructor
//   [x] 0x441db8  CKRollingBarrelCpnt_Destructor
//   [x] 0x441e10  CKRollingBarrelCpnt_CreateArray
//   [x] 0x441ef0  CKRollingBarrelCpnt_Create
//
//   [x] 0x9c34c8  CKRollingBarrelCpnt_IsKindOfClass  [inline]
//   [x] 0x9c3500  CKRollingBarrelCpnt_GetClassType  [inline]
//   [x] 0x9c3508  CKRollingBarrelCpnt_GetClassID  [inline]
#include "k2000/components/CKRollingBarrelCpnt.h"

#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"

// C2.8 port-rest R02.

// 0x00441db8 CKRollingBarrelCpnt_Destructor (0x441d58 the deleting one)
CKRollingBarrelCpnt::~CKRollingBarrelCpnt() {
    if (m_vUnk04.m_pBlock != nullptr) Mem_FreeAligned16(m_vUnk04.m_pBlock);
}

// 0x00441960 CKRollingBarrelCpnt_Load: the base's (nothing read); a level file: one u32 count, the vector sized to it
// (an empty one still gets a block of one reference and capacity 1, its used count left), then the references read in
// place. The old block, if any, is not freed.
int32_t CKRollingBarrelCpnt::Load(IKFile* file, int32_t type) {
    IKMecaCpnt::Load(file, type);  // 0x003f7a18
    if (type != K_LEVEL_PLATEFORMS) return 1;
    uint32_t count = 0;
    ReadU32LE(file, &count);
    if (count == 0) {
        m_vUnk04.m_ui32NbElt = 1;
        m_vUnk04.m_pBlock = static_cast<IKSerializable**>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(IKSerializable*))));
    } else {
        m_vUnk04.m_ui32NbElt = count;
        m_vUnk04.m_pBlock =
            static_cast<IKSerializable**>(Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(IKSerializable*))));
        // (The original's grow-to-count+1 branch when the capacity is below the count cannot run: it was just set.)
        m_vUnk04.m_ui32NbUsedElt = count;
    }
    for (uint32_t i = 0; i < count; ++i) IKFile_ReadRef(file, &m_vUnk04.m_pBlock[i]);
    return 1;
}
