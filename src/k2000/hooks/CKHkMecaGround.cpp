// CKHkMecaGround.cpp - reconstructed original translation unit 0x4e0ad8-0x4e15d0 (GAME_TOC1, main_toc1), 29 functions, 29 live.
// Primary class: CKHkMecaGround  key 0x2dc2  category Hook  size 0x2c  vtable 0xb2a568
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x4e0ad8  CKHkMecaGround_Delete
//   [x] 0x4e0b28  CKHkMecaGround_Restart
//   [x] 0x4e0b80  CKHkMecaGround_vfC8
//   [ ] 0x4e0b90  RegisterCKHkMecaGroundClass
//   [ ] 0x4e0c08  _GLOBAL__I_4e0c08
//   [x] 0x4e0c18  CKHkMecaGround_MessageProc
//   [x] 0x4e0c70  CKHkMecaGround_GetInfo
//   [x] 0x4e0cc0  CKHkMecaGround_SetDefaultState
//   [x] 0x4e0d10  CKHkMecaGround_Update  (empty / no effect: inherited, WorldObjectBase_Update_Nop 0x3f6e68)
//   [x] 0x4e0d38  CKHkMecaGround_OnDeactivate  (= the inherited slot: CKHkActorBase_d82_maybe_OnDeactivate)
//   [x] 0x4e0d60  CKHkMecaGround_OnActivate
//   [x] 0x4e0db8  CKHkMecaGround_Resume  (empty / no effect: inherited)
//   [x] 0x4e0de0  CKHkMecaGround_Pause  (empty / no effect: inherited)
//   [x] 0x4e0e08  CKHkMecaGround_Stop  (empty / no effect: inherited, CKHkActorBase_d82_maybe_Stop 0x3f6e50)
//   [x] 0x4e0e30  CKHkMecaGround_Start
//   [x] 0x4e0e88  CKHkMecaGround_PostLoad  (= the inherited slot)
//   [ ] 0x4e0eb0  CKHkMecaGround_Save
//   [x] 0x4e0ed8  CKHkMecaGround_RecursiveRegistration  (= the inherited slot: CKHkActorBase_d82_maybe_LevelReset 0x3f6ee8, then 1)
//   [x] 0x4e0f00  CKHkMecaGround_Destroy  (inherited: CKHkActorBase_d82_maybe_ClearReferences 0x3f6e08 calls vt+0xc0, KStub_Nop_9c0bc8)
//   [x] 0x4e0f28  CKHkMecaGround_Destructor  (the C++ destructor: FreeRefList)
//   [x] 0x4e0fa0  CKHkMecaGround_Construct_2  (the C++ constructor, the same code as Construct)
//   [x] 0x4e0fe0  CKHkMecaGround_Construct
//   [x] 0x4e1020  CKHkMecaGround_DeleteArray
//   [x] 0x4e10c0  CKHkMecaGround_Destructor_2  (the same code as 0x4e0f28 CKHkMecaGround_Destructor)
//   [x] 0x4e1138  CKHkMecaGround_DeletingDestructor  (the deleting form of the destructor)
//   [x] 0x4e11c0  CKHkMecaGround_SetEnabled
//   [x] 0x4e1238  CKHkMecaGround_CreateArray
//   [x] 0x4e12f8  CKHkMecaGround_Create
//   [x] 0x4e1358  CKHkMecaGround_Load
//
//   [ ] 0x9c6390  CKHkMecaGround_IsKindOfClass  [inline]
//   [ ] 0x9c63e8  CKHkMecaGround_GetClassType  [inline]
//   [ ] 0x9c63f0  CKHkMecaGround_GetClassID  [inline]
#include "k2000/hooks/CKHkMecaGround.h"
#include "k2000/services/ICollisionMesh.h"

#include "k2000/io/IKFile.h"

// 0x004e0c18 CKHkMecaGround_MessageProc
int32_t CKHkMecaGround::MessageProc(uint16_t message, void* data) {
    const int32_t base = CKHkActorBase::MessageProc(message, data);  // 0x003f7148
    if (base == 3) return 3;
    if (base == 2) return 2;
    return base == 0 ? 0 : 1;
}

// 0x004e0c70 CKHkMecaGround_GetInfo
int32_t CKHkMecaGround::GetInfo(IKInfo* info, int32_t request) {
    const int32_t base = CKHkActorBase::GetInfo(info, request);  // KStub_Return1 0x3f7140
    if (base == 2) return 2;
    return base == 0 ? 0 : 1;
}

// 0x004e0cc0 CKHkMecaGround_SetDefaultState
void CKHkMecaGround::SetDefaultState(int32_t flag) {
    CKHkActorBase::SetDefaultState(static_cast<uint8_t>(flag));  // KStub_Nop_3f72a0
    if (flag == 0) m_unk24 = 1;
}

// 0x004e0e30 CKHkMecaGround_Start
void CKHkMecaGround::Start() {
    CKHkActorBase::Start();  // 0x003f6e48
    Restart();               // vt+0x54
}

// 0x004e0b28 CKHkMecaGround_Restart
void CKHkMecaGround::Restart() {
    if ((m_bitArray & 4u) != 0) return;
    SetEnabled(m_unk24);  // vt+0xcc
}

// 0x004e0d60 CKHkMecaGround_OnActivate
void CKHkMecaGround::VfA0() {
    CKHkActorBase::VfA0();  // 0x003f7338
    SetEnabled(m_unk24);    // vt+0xcc
}

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

// 0x004e11c0 CKHkMecaGround_SetEnabled
void CKHkMecaGround::SetEnabled(int32_t enabled) {
    m_unk24 = static_cast<uint8_t>(enabled);
    static_cast<ICollisionMesh*>(m_unk20)->SetActive(static_cast<uint16_t>(enabled));  // 0x001a6b70
    for (RefNode* node = m_pRefList; node != nullptr; node = node->m_pNext) {
        static_cast<ICollisionMesh*>(node->m_pObject)->SetActive(static_cast<uint16_t>(enabled));
    }
}
