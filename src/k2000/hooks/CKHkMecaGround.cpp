// CKHkMecaGround.cpp - reconstructed original translation unit 0x4e0ad8-0x4e15d0 (GAME_TOC1, main_toc1), 29 functions, 29 live.
// Primary class: CKHkMecaGround  key 0x2dc2  category Hook  size 0x2c  vtable 0xb2a568
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x4e0ad8  CKHkMecaGround_Delete
//   [ ] 0x4e0b28  CKHkMecaGround_Restart
//   [ ] 0x4e0b80  CKHkMecaGround_vfC8
//   [ ] 0x4e0b90  RegisterCKHkMecaGroundClass
//   [ ] 0x4e0c08  _GLOBAL__I_4e0c08
//   [ ] 0x4e0c18  CKHkMecaGround_MessageProc
//   [ ] 0x4e0c70  CKHkMecaGround_GetInfo
//   [ ] 0x4e0cc0  CKHkMecaGround_SetDefaultState
//   [ ] 0x4e0d10  CKHkMecaGround_Update
//   [ ] 0x4e0d38  CKHkMecaGround_OnDeactivate
//   [ ] 0x4e0d60  CKHkMecaGround_OnActivate
//   [ ] 0x4e0db8  CKHkMecaGround_Resume
//   [ ] 0x4e0de0  CKHkMecaGround_Pause
//   [ ] 0x4e0e08  CKHkMecaGround_Stop
//   [ ] 0x4e0e30  CKHkMecaGround_Start
//   [ ] 0x4e0e88  CKHkMecaGround_PostLoad
//   [ ] 0x4e0eb0  CKHkMecaGround_Save
//   [ ] 0x4e0ed8  CKHkMecaGround_RecursiveRegistration
//   [ ] 0x4e0f00  CKHkMecaGround_Destroy
//   [ ] 0x4e0f28  CKHkMecaGround_Destructor
//   [ ] 0x4e0fa0  CKHkMecaGround_Construct_2
//   [x] 0x4e0fe0  CKHkMecaGround_Construct
//   [x] 0x4e1020  CKHkMecaGround_DeleteArray
//   [ ] 0x4e10c0  CKHkMecaGround_Destructor_2
//   [ ] 0x4e1138  CKHkMecaGround_DeletingDestructor
//   [ ] 0x4e11c0  CKHkMecaGround_SetEnabled
//   [x] 0x4e1238  CKHkMecaGround_CreateArray
//   [x] 0x4e12f8  CKHkMecaGround_Create
//   [x] 0x4e1358  CKHkMecaGround_Load
//
//   [ ] 0x9c6390  CKHkMecaGround_IsKindOfClass  [inline]
//   [ ] 0x9c63e8  CKHkMecaGround_GetClassType  [inline]
//   [ ] 0x9c63f0  CKHkMecaGround_GetClassID  [inline]
#include "k2000/hooks/CKHkMecaGround.h"

#include "k2000/io/IKFile.h"

// 0x004e1358 CKHkMecaGround_Load
int32_t CKHkMecaGround::Load(IKFile* file, int32_t type) {
    CKHkActorBase::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        IKFile_ReadRef(file, &m_unk20);
        // The old list's nodes go back to the pool (FreeListPool 0x00ceaa20, its free list at +0x14).
        RefNode* node = m_pRefList;
        while (node != nullptr) {
            RefNode* next = node->m_pNext;
            delete node;
            node = next;
        }
        m_pRefList = nullptr;
        uint32_t count = 0;
        ReadU32LE(file, &count);
        for (uint32_t i = 0; i < count; ++i) {
            IKSerializable* object = nullptr;
            IKFile_ReadObjectRef(file, &object);
            RefNode* added = new RefNode();  // taken from the pool (FreeListPool_Grow when empty)
            added->m_pObject = object;
            added->m_pNext = m_pRefList;
            m_pRefList = added;
        }
    }
    return 1;
}
