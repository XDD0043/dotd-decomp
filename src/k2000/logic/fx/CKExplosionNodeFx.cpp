// CKExplosionNodeFx.cpp - reconstructed original translation unit 0x1b5d98-0x1b8778 (GAME_TOC1, main_toc1), 27 functions, 27 live.
// Primary class: CKExplosionNodeFx  key 0x1a4c  category Logic  size 0x50  vtable 0xb1ca38
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x1b5d98  RegisterCKExplosionNodeFxClass
//   [ ] 0x1b5e10  _GLOBAL__I_1b5e10
//   [ ] 0x1b5e20  CKExplosionNodeFx_SetDirection
//   [ ] 0x1b5fd8  CKExplosionNodeFx_PostLoad
//   [ ] 0x1b6040  CKExplosionNodeFx_Save
//   [ ] 0x1b6068  CKExplosionNodeFx_Destroy
//   [x] 0x1b60a8  CKExplosionNodeFx_DeleteArray
//   [x] 0x1b6150  CKExplosionNodeFx_Create
//   [ ] 0x1b61c0  CKExplosionNodeFx_RecursiveRegistration
//   [ ] 0x1b62c8  CKExplosionNodeFx_SetDamage
//   [ ] 0x1b62f0  CKExplosionNodeFx_SetDamageFlags
//   [ ] 0x1b6318  CKExplosionNodeFx_SetDamageCategory
//   [ ] 0x1b6340  CKExplosionNodeFx_SetDamageOwner
//   [ ] 0x1b6368  CKExplosionNodeFx_SetMatrix
//   [ ] 0x1b6438  CKExplosionNodeFx_SetPosition
//   [ ] 0x1b64a0  CKExplosionNodeFx_CountSubEffectsOfType_maybe
//   [ ] 0x1b6530  CKExplosionNodeFx_GetNthSubEffectOfType_maybe
//   [ ] 0x1b65f0  CKExplosionNodeFx_Start
//   [ ] 0x1b66e8  CKExplosionNodeFx_SetTranslation
//   [ ] 0x1b6740  CKExplosionNodeFx_Stop
//   [x] 0x1b6858  CKExplosionNodeFx_CreateArray
//   [x] 0x1b6940  CKExplosionNodeFx_Load
//   [ ] 0x1b6c20  CKExplosionNodeFx_FireSubEffect
//   [ ] 0x1b7fa8  CKExplosionNodeFx_UpdateActive_maybe
//   [ ] 0x1b8288  CKExplosionNodeFx_Update
//   [ ] 0x1b82a8  CKExplosionNodeFx_Trigger
//   [ ] 0x1b8770  CKExplosionNodeFx_Trigger
//
//   [ ] 0x9abc08  CKExplosionNodeFx_IsKindOfClass  [inline]
//   [x] 0x9abc40  CKExplosionNodeFx_GetClassType  [inline]
//   [x] 0x9abc48  CKExplosionNodeFx_GetClassID  [inline]
//   [ ] 0x9abc50  CKExplosionNodeFx_GetFxData  [inline]
//   [ ] 0x9abc58  CKExplosionNodeFx_SetFxData  [inline]
//   [ ] 0x9abc60  CKExplosionNodeFx_Destruct  [inline]
//   [ ] 0x9abce0  CKExplosionNodeFx_DeletingDestruct  [inline]
#include "k2000/logic/fx/CKExplosionNodeFx.h"

#include "Renderware/rwcore/RwMatrix.h"
#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"

// 0x001b6150 CKExplosionNodeFx_Create, the inlined constructor: the sub-effect list.
CKExplosionNodeFx::CKExplosionNodeFx() {
    m_subEffects.m_pBlock = nullptr;
    m_subEffects.m_ui32NbElt = 10;
    m_subEffects.m_ui32NbUsedElt = 0;
}

// 0x001b6940 CKExplosionNodeFx_Load
int32_t CKExplosionNodeFx::Load(IKFile* file, int32_t type) {
    IKNodeFx::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        uint32_t count = 0;
        ReadU32LE(file, &count);
        if (count == 0) {
            m_subEffects.m_ui32NbElt = 1;
            m_subEffects.m_pBlock = static_cast<SubEffect*>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(SubEffect))));
        } else {
            m_subEffects.m_ui32NbElt = count;
            m_subEffects.m_pBlock =
                static_cast<SubEffect*>(Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(SubEffect))));
        }
        if (m_subEffects.m_ui32NbElt < count) {  // never true: the capacity is at least count here
            uint32_t capacity = (count / 10) * 10 + 10;
            uint32_t bytes = capacity * static_cast<uint32_t>(sizeof(SubEffect));
            if (capacity == 0) {
                capacity = 10;
                bytes = 10 * static_cast<uint32_t>(sizeof(SubEffect));
            }
            m_subEffects.m_pBlock = static_cast<SubEffect*>(Mem_ReallocAligned16(m_subEffects.m_pBlock, bytes));
            m_subEffects.m_ui32NbElt = capacity;
        }
        m_subEffects.m_ui32NbUsedElt = count;
        for (uint32_t i = 0; i < count; ++i) {
            SubEffect& e = m_subEffects.m_pBlock[i];
            ReadS32LE(file, &e.m_value);
            if (e.m_value > 0) {
                e.m_pObject = nullptr;
            } else {
                IKFile_ReadRef(file, &e.m_pObject);
            }
        }
        ReadU8(file, &m_baFxData);  // one byte, no swap
        m_pMatrix = RwMatrixCreate();  // RwMatrixCreate_Thunk
    }
    m_unk40 = 0;
    m_unk1c = 0;
    m_pFxData = nullptr;
    m_unk2c = 0;
    m_unk30 = 0;
    return 1;
}
