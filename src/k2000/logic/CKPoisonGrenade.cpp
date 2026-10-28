// CKPoisonGrenade.cpp - reconstructed original translation unit 0x3b47b8-0x3b8bd8 (GAME_TOC1, main_toc1), 24 functions, 24 live.
// Primary class: CKPoisonGrenade  key 0x948c  category Logic  size 0x30c  vtable 0xb23ca8
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x3b47b8  CKPoisonGrenade_Delete
//   [ ] 0x3b4808  CKPoisonGrenade_GetAbilityId
//   [ ] 0x3b4810  CKPoisonGrenade_IsChargeDisabled_maybe
//   [ ] 0x3b4830  CKPoisonGrenade_End
//   [ ] 0x3b4920  CKPoisonGrenade_ResetRuntime
//   [ ] 0x3b4990  CKPoisonGrenade_Start
//   [ ] 0x3b49d8  CKPoisonGrenade_PostLoad
//   [ ] 0x3b4a40  CKPoisonGrenade_RecursiveRegistration
//   [ ] 0x3b4a68  CKPoisonGrenade_Destroy
//   [x] 0x3b4aa8  CKPoisonGrenade_Construct
//   [x] 0x3b4ae0  CKPoisonGrenade_DeleteArray
//   [ ] 0x3b4b80  CKPoisonGrenade_DeletingDestructor
//   [ ] 0x3b4bc8  CKPoisonGrenade_Destructor
//   [ ] 0x3b4bf8  CKPoisonGrenade_DestructBody
//   [ ] 0x3b4c28  CKPoisonGrenade_Construct_2
//   [ ] 0x3b4c60  RegisterCKPoisonGrenadeClass
//   [ ] 0x3b4ce8  _GLOBAL__D_3b4ce8
//   [ ] 0x3b4cf8  _GLOBAL__I_3b4cf8
//   [ ] 0x3b4d08  CKPoisonGrenade_Fire
//   [x] 0x3b6040  CKPoisonGrenade_CreateArray
//   [x] 0x3b60f0  CKPoisonGrenade_Create
//   [ ] 0x3b6148  CKPoisonGrenade_UpdateCharge
//   [ ] 0x3b6d50  CKPoisonGrenade_Save
//   [x] 0x3b7ce0  CKPoisonGrenade_Load
//
//   [ ] 0x9c0048  CKPoisonGrenade_IsKindOfClass  [inline]
//   [ ] 0x9c0098  CKPoisonGrenade_GetClassType  [inline]
//   [ ] 0x9c00a0  CKPoisonGrenade_GetClassID  [inline]
//   [ ] 0x9c00a8  CKPoisonGrenade_StartEmitterFx  [inline]
#include "k2000/logic/CKPoisonGrenade.h"

#include <cstdint>

#include "k2000/io/IKFile.h"

// 0x003b7ce0 CKPoisonGrenade_Load: CKProjectileElement's data, then (level data only) 236 bytes, the same
// fields as CKBlackBall_Load in another order (the original unrolls the per-level reads; the loops keep its
// order), and two pairs of 12-byte vectors (a 2-iteration loop).
int32_t CKPoisonGrenade::Load(IKFile* file, int32_t type) {
    CKProjectileElement::Load(file, type);
    if (type != 0) return 1;
    for (int32_t i = 0; i < 3; ++i) {
        IKFile_ReadRef(file, &m_unk28c[i]);
        IKFile_ReadRef(file, &m_unk298[i]);
    }
    for (int32_t i = 0; i < 3; ++i) {
        ReadF32LE(file, &m_unk214[i]);
        ReadF32LE(file, &m_unk22c[i]);
        ReadF32LE(file, &m_unk244[i]);
        ReadF32LE(file, &m_unk220[i]);
        ReadF32LE(file, &m_unk238[i]);
        ReadF32LE(file, &m_unk250[i]);
    }
    IKFile_ReadRef(file, &m_unk2a4);
    IKFile_ReadRef(file, &m_unk2a8);
    ReadU32LEWords(file, m_unk2ac, 3);
    IKFile_ReadRef(file, &m_unk2f8);
    ReadF32LE(file, &m_unk2fc);
    for (int32_t i = 0; i < 3; ++i) {
        ReadS32LE(file, &m_unk25c[i]);
        ReadF32LE(file, &m_unk274[i]);
        ReadS32LE(file, &m_unk268[i]);
        ReadF32LE(file, &m_unk280[i]);
    }
    IKFile_ReadRef(file, &m_unk2e8);
    ReadF32LE(file, &m_unk2ec);
    ReadF32LE(file, &m_unk2f0);
    ReadU32LE(file, &m_unk2f4);
    for (int32_t i = 0; i < 2; ++i) {
        ReadU32LEWords(file, reinterpret_cast<uint32_t*>(m_unk2b8[i]), 3);
        ReadU32LEWords(file, reinterpret_cast<uint32_t*>(m_unk2d0[i]), 3);
    }
    return 1;
}
