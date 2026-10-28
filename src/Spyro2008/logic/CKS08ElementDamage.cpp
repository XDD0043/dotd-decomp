// CKS08ElementDamage.cpp - reconstructed original translation unit 0x3f2ff0-0x3f4108 (GAME_TOC1, main_toc1), 19 functions, 17 live.
// Primary class: CKS08ElementDamage  key 0x99cc  category Logic  size 0x3c  vtable 0xb24b68
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x3f2ff0  CKS08ElementDamage_Delete
//   [ ] 0x3f3040  RegisterCKS08ElementDamageClass
//   [ ] 0x3f30b8  _GLOBAL__I_3f30b8
//   [ ] 0x3f30c8  CKS08ElementDamage_Destroy
//   [x] 0x3f3118  CKS08ElementDamage_DeleteArray
//   [ ] 0x3f31c0  CKS08ElementDamage_PostLoad
//   [ ] 0x3f31e8  CKS08ElementDamage_Assign_maybe
//   [ ] 0x3f3318  CKS08ElementDamage_RecursiveRegistration
//   [ ] 0x3f3340  CKS08ElementDamage_DeletingDestructor
//   [ ] 0x3f33b8  CKS08ElementDamage_Destructor
//   [ ] 0x3f3420  CKS08ElementDamage_DestructBody
//   [ ] 0x3f3488  CKS08ElementDamage_CopyConstruct_2_maybe
//   [ ] 0x3f3590  CKS08ElementDamage_CopyConstruct_maybe
//   [x] 0x3f3698  CKS08ElementDamage_Construct  [dead]
//   [ ] 0x3f36d8  CKS08ElementDamage_Construct_2  [dead]
//   [ ] 0x3f3718  CKS08ElementDamage_Save
//   [x] 0x3f3ad0  CKS08ElementDamage_Load
//   [x] 0x3f3fe0  CKS08ElementDamage_Create
//   [x] 0x3f4040  CKS08ElementDamage_CreateArray
//
//   [ ] 0x9c0a48  CKS08ElementDamage_IsKindOfClass  [inline]
//   [ ] 0x9c0ab0  CKS08ElementDamage_GetClassType  [inline]
//   [ ] 0x9c0ab8  CKS08ElementDamage_GetClassID  [inline]
//   [ ] 0x9c0ac0  CKS08ElementDamage_SetAmount  [inline]
//   [ ] 0x9c0ac8  CKS08ElementDamage_SetContinuous_maybe  [inline]
//   [ ] 0x9c0ad0  CKS08ElementDamage_vf58  [inline]
//   [ ] 0x9c0ae8  CKS08ElementDamage_SetStun_maybe  [inline]
//   [ ] 0x9c0af0  CKS08ElementDamage_vf60  [inline]
//   [ ] 0x9c0af8  CKS08ElementDamage_SetDamageType  [inline]
//   [ ] 0x9c0b00  CKS08ElementDamage_SetAbilityId_maybe  [inline]
//   [ ] 0x9c0b08  CKS08ElementDamage_vf6C  [inline]
//   [ ] 0x9c0b10  CKS08ElementDamage_vf70  [inline]
#include "Spyro2008/logic/CKS08ElementDamage.h"

#include "k2000/io/IKFile.h"

// 0x003f3ad0 CKS08ElementDamage_Load: CKS08StunDamage's data, two bytes, then a counted list of values
// into a fresh 10-entry array (values past the 10th are read and dropped, missing ones are zeroed), then
// a word.
int32_t CKS08ElementDamage::Load(IKFile* file, int32_t type) {
    CKS08StunDamage::Load(file, type);
    ReadU8(file, &m_unk34);
    ReadU8(file, &m_unk35);
    if (m_afValues != nullptr) {
        delete[] m_afValues;
        m_afValues = nullptr;
    }
    m_afValues = new float[10];
    uint32_t count = 0;
    ReadU32LE(file, &count);
    if (count > 10) {
        for (uint32_t i = 0; i < 10; ++i) ReadF32LE(file, &m_afValues[i]);
        for (uint32_t i = 10; i < count; ++i) {
            uint32_t dropped = 0;
            ReadU32LE(file, &dropped);
        }
    } else {
        for (uint32_t i = 0; i < count; ++i) ReadF32LE(file, &m_afValues[i]);
        for (uint32_t i = count; i < 10; ++i) m_afValues[i] = 0.0f;  // stw 0
    }
    ReadS32LE(file, &m_unk38);
    return 1;
}
