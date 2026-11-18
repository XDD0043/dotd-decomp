// CKS08AccessoryManager.cpp - reconstructed original translation unit 0x2c74d0-0x2c81f0 (GAME_TOC1, main_toc1), 29 functions, 22 live.
// Primary class: CKS08AccessoryManager  key 0xa20c  category Logic  size 0x58  vtable 0xb22900
// Other owners: IKGrpHero (1), CKGrpS08Hero (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x2c74d0  CKS08AccessoryManager_Delete
//   [ ] 0x2c7520  CKS08AccessoryManager_ConstructNoArrays_maybe  [dead]
//   [ ] 0x2c7580  FUN_002c7580  [dead]
//   [x] 0x2c7598  CKS08AccessoryManager_ProbeGround_maybe
//   [x] 0x2c75f0  CKS08AccessoryManager_AddActiveItem_maybe
//   [x] 0x2c76d0  CKS08AccessoryManager_DeleteArray
//   [ ] 0x2c7770  RegisterCKS08AccessoryManagerClass
//   [ ] 0x2c77f8  _GLOBAL__D_2c77f8
//   [ ] 0x2c7808  _GLOBAL__I_2c7808
//   [x] 0x2c7818  CKS08AccessoryManager_ClearAccessories_maybe
//   [x] 0x2c78e0  CKS08AccessoryManager_UpdateActiveItems_maybe
//   [ ] 0x2c79b0  CKS08AccessoryManager_Construct  [dead]
//   [ ] 0x2c7a68  CKS08AccessoryManager_ConstructNoArrays_2_maybe  [dead]
//   [ ] 0x2c7ac8  CKS08AccessoryManager_Save
//   [x] 0x2c7ad0  CKS08AccessoryManager_PostLoad
//   [x] 0x2c7b20  CKS08AccessoryManager_RecursiveRegistration  (returns 1: the root's empty slot)
//   [x] 0x2c7b28  CKS08AccessoryManager_Destroy  (empty: the root's default)
//   [x] 0x2c7b30  CKS08AccessoryManager_ReinitRuntime
//   [x] 0x2c7b80  CKS08AccessoryManager_ResetRuntime_maybe
//   [ ] 0x2c7bc0  FUN_002c7bc0  [dead]
//   [ ] 0x2c7c40  CKS08AccessoryManager_Construct_2  [dead]
//   [x] 0x2c7cf8  CKS08AccessoryManager_CreateArray
//   [x] 0x2c7df0  CKS08AccessoryManager_Create
//   [x] 0x2c7e78  CKS08AccessoryManager_Load
//   [x] 0x2c8060  CKS08AccessoryManager_Destructor
//   [ ] 0x2c80d8  CKS08AccessoryManager_Destructor_2  [dead]
//   [x] 0x2c8150  CKS08AccessoryManager_DeletingDestructor  (the destructor; delete)
//   [x] 0x2c81e0  IKGrpHero_vfB8  (IKGrpHero vtable 0xb22968 +0xb8: returns 1; no call of the slot found, not declared)
//   [x] 0x2c81e8  CKGrpS08Hero_vfE0  (IKGrpHero / CKGrpS08Hero vt+0xe0: empty; no call of the slot found, not declared)
//
//   [ ] 0x9bd0e0  CKS08AccessoryManager_GetClassType  [inline]
//   [ ] 0x9bd0e8  CKS08AccessoryManager_GetClassID  [inline]
//   [ ] 0x9bd0f0  CKS08AccessoryManager_IsKindOfClass  [inline]
#include "Spyro2008/logic/CKS08AccessoryManager.h"
#include "k2000/services/CKSrvCollision.h"
#include "k2000/misc/Engine.h"
#include "Spyro2008/logic/CKS08EnemyElement.h"

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

// 0x002c7b30 CKS08AccessoryManager_ReinitRuntime (vt+0x54; CKGrpS08Enemy_Restart): a one-slot block with capacity 1
// only when the second array has none.
void CKS08AccessoryManager::ReinitRuntime() {
    if (m_unk10 == nullptr) {
        m_unk14 = 1;
        m_unk10 = Mem_AllocAligned16(4);
    }
}

// 0x002c7ad0 CKS08AccessoryManager_PostLoad
int32_t CKS08AccessoryManager::PostLoad(int32_t /*type*/) {
    m_groundIn.m_fDeltaMax = 0.2f;
    m_groundIn.m_fObjectHeight = 2.0f;
    m_groundIn.m_MasksOfGrdForTest[0] = 1;
    m_groundIn.m_MasksOfGrdForTest[1] = 8;
    m_groundContact.m_pGround = nullptr;
    m_groundContact.m_ui8SectorNumber = 0;
    m_groundContact.m_i32FaceIndex = -1;
    m_groundContact.m_eContactStatus = 3;
    return 1;
}

// 0x002c75f0 CKS08AccessoryManager_AddActiveItem_maybe
void CKS08AccessoryManager::AddActiveItem(CKS08EnemyElement* item) {
    if (m_unk14 == m_unk18) {
        uint32_t capacity = m_unk18 + 1;
        if (capacity == 0) capacity = 1;
        m_unk10 = Mem_ReallocAligned16(m_unk10, capacity * static_cast<uint32_t>(sizeof(CKS08EnemyElement*)));
        m_unk14 = capacity;
    }
    static_cast<CKS08EnemyElement**>(m_unk10)[m_unk18] = item;
    m_unk18 = m_unk18 + 1;
}

// 0x002c7818 CKS08AccessoryManager_ClearAccessories_maybe
void CKS08AccessoryManager::ClearAccessories() {
    const uint32_t count = m_unk18;
    for (uint32_t i = 0; i != count; ++i) {
        CKS08EnemyElement* item = static_cast<CKS08EnemyElement**>(m_unk10)[i];
        if (item != nullptr) item->ReturnToGroup();  // vt+0x50 0x0026c158
    }
    if (m_unk10 != nullptr) Mem_FreeAligned16(m_unk10);  // 0x00052fb8
    m_unk18 = 0;
    m_unk10 = nullptr;
}

// 0x002c7598 CKS08AccessoryManager_ProbeGround_maybe
const CGroundContactDatasInOut* CKS08AccessoryManager::ProbeGround(const CVector3* point) {
    static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision)->GroundProbePoints(&m_groundIn, &m_groundContact, &point->x, 1);  // 0x00196540
    return &m_groundContact;
}
