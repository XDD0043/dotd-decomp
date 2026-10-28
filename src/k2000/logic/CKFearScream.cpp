// CKFearScream.cpp - reconstructed original translation unit 0x3a0f00-0x3a3240 (GAME_TOC1, main_toc1), 29 functions, 29 live.
// Primary class: CKFearScream  key 0x944c  category Logic  size 0x24c  vtable 0xb239b8
// Other owners: CKFireBreath (3), ResetFireBreathRuntimeEffects (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x3a0f00  CKFearScream_Delete
//   [ ] 0x3a0f50  CKFearScream_GetAbilityId
//   [ ] 0x3a0f58  CKFearScream_IsChargeDisabled_maybe
//   [ ] 0x3a0fa8  CKFearScream_End
//   [ ] 0x3a1038  CKFearScream_GetFxSound_maybe
//   [ ] 0x3a1180  CKFearScream_ResetRuntime
//   [ ] 0x3a11d0  CKFearScream_Start
//   [ ] 0x3a1220  CKFearScream_PostLoad
//   [ ] 0x3a1270  CKFearScream_RecursiveRegistration
//   [ ] 0x3a1298  CKFearScream_Destroy
//   [x] 0x3a12c0  CKFearScream_Construct
//   [ ] 0x3a12f8  CKFearScream_Construct_2
//   [x] 0x3a1330  CKFearScream_DeleteArray
//   [ ] 0x3a13d0  CKFearScream_DeletingDestructor
//   [ ] 0x3a1418  CKFearScream_Destructor
//   [ ] 0x3a1448  CKFearScream_DestructBody
//   [ ] 0x3a1478  RegisterCKFearScreamClass
//   [ ] 0x3a1500  _GLOBAL__D_3a1500
//   [ ] 0x3a1510  _GLOBAL__I_3a1510
//   [x] 0x3a1520  CKFearScream_Create
//   [x] 0x3a1578  CKFearScream_CreateArray
//   [ ] 0x3a1628  CKFearScream_UpdateCharge
//   [x] 0x3a1cb8  CKFearScream_Load
//   [ ] 0x3a21b8  CKFearScream_Save
//   [ ] 0x3a2750  CKFearScream_Fire
//   [ ] 0x3a3040  CKFireBreath_Delete
//   [ ] 0x3a3090  CKFireBreath_GetAbilityId
//   [ ] 0x3a3098  CKFireBreath_GetSound_maybe
//   [ ] 0x3a31e0  ResetFireBreathRuntimeEffects
//
//   [ ] 0x9bfdb0  CKFearScream_IsKindOfClass  [inline]
//   [ ] 0x9bfe00  CKFearScream_GetClassType  [inline]
//   [ ] 0x9bfe08  CKFearScream_GetClassID  [inline]
//   [ ] 0x9bfe10  CKFearScream_StartEmitterFx  [inline]
#include "k2000/logic/CKFearScream.h"

#include <cstdint>

#include "k2000/io/IKFile.h"

// 0x003a1cb8 CKFearScream_Load: CKProjectileElement's data, then (level data only) 48 bytes: eight object
// references, a 12-byte block of three swapped words, a sound reference.
int32_t CKFearScream::Load(IKFile* file, int32_t type) {
    CKProjectileElement::Load(file, type);
    if (type != 0) return 1;
    for (int32_t i = 0; i < 7; ++i) IKFile_ReadRef(file, &m_unk214[i]);
    IKFile_ReadRef(file, &m_unk230);
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(m_unk234), 3);
    IKFile_ReadRef(file, &m_unk240);
    return 1;
}
