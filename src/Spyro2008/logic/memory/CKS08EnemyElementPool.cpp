// CKS08EnemyElementPool.cpp - reconstructed original translation unit 0x26c918-0x26cfa0 (GAME_TOC1, main_toc1), 15 functions, 12 live.
// Primary class: CKS08EnemyElementPool  key 0x7a4c  category Logic  size 0x24  vtable 0xb21ae0
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x26c918  CKS08EnemyElementPool_Delete
//   [x] 0x26c968  CKS08EnemyElementPool_DeleteArray
//   [x] 0x26ca10  CKS08EnemyElementPool_Create
//   [ ] 0x26ca60  RegisterCKS08EnemyElementPoolClass
//   [ ] 0x26cae8  _GLOBAL__D_26cae8
//   [ ] 0x26caf8  _GLOBAL__I_26caf8
//   [ ] 0x26cb08  CKS08EnemyElementPool_SetElementActive_maybe  [dead]
//   [ ] 0x26cb18  CKS08EnemyElementPool_SetElementInactive_maybe  [dead]
//   [ ] 0x26cb28  CKS08EnemyElementPool_SetElement_maybe  [dead]
//   [x] 0x26cb40  CKS08EnemyElementPool_CreateArray
//   [ ] 0x26cbf8  CKS08EnemyElementPool_Save
//   [ ] 0x26cc00  CKS08EnemyElementPool_RecursiveRegistration
//   [ ] 0x26cc08  CKS08EnemyElementPool_PostLoad
//   [ ] 0x26cc58  CKS08EnemyElementPool_Destroy
//   [x] 0x26cc60  CKS08EnemyElementPool_Load
//
//   [ ] 0x9bbd78  CKS08EnemyElementPool_GetClassType  [inline]
//   [ ] 0x9bbd80  CKS08EnemyElementPool_GetClassID  [inline]
//   [ ] 0x9bbd88  CKS08EnemyElementPool_GetOwnClassId  [inline]
//   [ ] 0x9bbd90  CKS08EnemyElementPool_IsKindOfClass  [inline]
//   [ ] 0x9bbdb0  CKS08EnemyElementPool_DeletingDestructor  [inline]
//   [ ] 0x9bbe18  CKS08EnemyElementPool_Destructor  [inline]
#include "Spyro2008/logic/memory/CKS08EnemyElementPool.h"

#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"

// 0x0026cc60 CKS08EnemyElementPool_Load: the element references appended to the array, then the config
// reference, a byte and three words, whatever the type.
int32_t CKS08EnemyElementPool::Load(IKFile* file, int32_t /*type*/) {
    if (m_apElements == nullptr) {
        m_capacity = 1;
        m_apElements = static_cast<CKS08EnemyElement**>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(CKS08EnemyElement*))));
    }
    uint32_t count = 0;
    ReadU32LE(file, &count);
    for (uint32_t i = 0; i < count; ++i) {
        if (m_capacity == m_count) {
            uint32_t capacity = m_count + 1;
            if (capacity == 0) capacity = 1;
            m_apElements = static_cast<CKS08EnemyElement**>(
                Mem_ReallocAligned16(m_apElements, capacity * static_cast<uint32_t>(sizeof(CKS08EnemyElement*))));
            m_count = m_count + 1;
            m_capacity = capacity;
        } else {
            m_count = m_count + 1;
        }
        // BUG(original): the slot is the loop index, not the old count (the same when the array starts empty).
        IKFile_ReadRef(file, &m_apElements[i]);
    }
    IKFile_ReadRef(file, &m_pConfig);
    ReadU8(file, &m_unk10);
    ReadS32LE(file, &m_unk14);
    ReadF32LE(file, &m_unk18);
    ReadF32LE(file, &m_unk1c);
    return 1;
}
