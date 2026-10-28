// CKS08AccessoryManager.cpp - reconstructed original translation unit 0x2c74d0-0x2c81f0 (GAME_TOC1, main_toc1), 29 functions, 22 live.
// Primary class: CKS08AccessoryManager  key 0xa20c  category Logic  size 0x58  vtable 0xb22900
// Other owners: IKGrpHero (1), CKGrpS08Hero (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x2c74d0  CKS08AccessoryManager_Delete
//   [ ] 0x2c7520  CKS08AccessoryManager_ConstructNoArrays_maybe  [dead]
//   [ ] 0x2c7580  FUN_002c7580  [dead]
//   [ ] 0x2c7598  CKS08AccessoryManager_ProbeGround_maybe
//   [ ] 0x2c75f0  CKS08AccessoryManager_AddActiveItem_maybe
//   [x] 0x2c76d0  CKS08AccessoryManager_DeleteArray
//   [ ] 0x2c7770  RegisterCKS08AccessoryManagerClass
//   [ ] 0x2c77f8  _GLOBAL__D_2c77f8
//   [ ] 0x2c7808  _GLOBAL__I_2c7808
//   [ ] 0x2c7818  CKS08AccessoryManager_ClearAccessories_maybe
//   [ ] 0x2c78e0  CKS08AccessoryManager_UpdateActiveItems_maybe
//   [ ] 0x2c79b0  CKS08AccessoryManager_Construct  [dead]
//   [ ] 0x2c7a68  CKS08AccessoryManager_ConstructNoArrays_2_maybe  [dead]
//   [ ] 0x2c7ac8  CKS08AccessoryManager_Save
//   [ ] 0x2c7ad0  CKS08AccessoryManager_PostLoad
//   [ ] 0x2c7b20  CKS08AccessoryManager_RecursiveRegistration
//   [ ] 0x2c7b28  CKS08AccessoryManager_Destroy
//   [ ] 0x2c7b30  CKS08AccessoryManager_ReinitRuntime
//   [x] 0x2c7b80  CKS08AccessoryManager_ResetRuntime_maybe
//   [ ] 0x2c7bc0  FUN_002c7bc0  [dead]
//   [ ] 0x2c7c40  CKS08AccessoryManager_Construct_2  [dead]
//   [x] 0x2c7cf8  CKS08AccessoryManager_CreateArray
//   [x] 0x2c7df0  CKS08AccessoryManager_Create
//   [x] 0x2c7e78  CKS08AccessoryManager_Load
//   [ ] 0x2c8060  CKS08AccessoryManager_Destructor
//   [ ] 0x2c80d8  CKS08AccessoryManager_Destructor_2  [dead]
//   [ ] 0x2c8150  CKS08AccessoryManager_DeletingDestructor
//   [ ] 0x2c81e0  IKGrpHero_vfB8
//   [ ] 0x2c81e8  CKGrpS08Hero_vfE0
//
//   [ ] 0x9bd0e0  CKS08AccessoryManager_GetClassType  [inline]
//   [ ] 0x9bd0e8  CKS08AccessoryManager_GetClassID  [inline]
//   [ ] 0x9bd0f0  CKS08AccessoryManager_IsKindOfClass  [inline]
#include "Spyro2008/logic/CKS08AccessoryManager.h"

#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"

// 0x002c7e78 CKS08AccessoryManager_Load: a count, then that many config references appended to the
// array, whatever the type.
int32_t CKS08AccessoryManager::Load(IKFile* file, int32_t /*type*/) {
    uint32_t count = 0;
    ReadU32LE(file, &count);
    if (m_apConfigs == nullptr) {
        m_configCapacity = 1;
        m_apConfigs = static_cast<CKS08AccessoryConfig**>(
            Mem_AllocAligned16(static_cast<uint32_t>(sizeof(CKS08AccessoryConfig*))));
    }
    for (uint32_t i = 0; i < count; ++i) {
        CKS08AccessoryConfig* config = nullptr;
        IKFile_ReadRef(file, &config);
        if (m_configCapacity == m_configCount) {
            uint32_t capacity = m_configCount + 1;
            if (capacity == 0) capacity = 1;
            m_apConfigs = static_cast<CKS08AccessoryConfig**>(Mem_ReallocAligned16(
                m_apConfigs, capacity * static_cast<uint32_t>(sizeof(CKS08AccessoryConfig*))));
            m_configCapacity = capacity;
        }
        m_apConfigs[m_configCount] = config;
        m_configCount = m_configCount + 1;
    }
    return 1;
}

// 0x002c7b80 CKS08AccessoryManager_ResetRuntime_maybe (vt+0x50): the second array restarts with capacity 1
// and a one-slot block (the old block is not freed).
void CKS08AccessoryManager::ResetRuntime() {
    m_unk14 = 1;
    m_unk10 = Mem_AllocAligned16(4);
}
