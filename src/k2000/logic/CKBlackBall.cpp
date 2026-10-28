// CKBlackBall.cpp - reconstructed original translation unit 0x3798b8-0x37d2e0 (GAME_TOC1, main_toc1), 24 functions, 24 live.
// Primary class: CKBlackBall  key 0x94cc  category Logic  size 0x30c  vtable 0xb23458
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x3798b8  CKBlackBall_Delete
//   [ ] 0x379908  CKBlackBall_GetAbilityId
//   [ ] 0x379910  CKBlackBall_IsChargeDisabled_maybe
//   [ ] 0x379930  CKBlackBall_End
//   [ ] 0x379a20  CKBlackBall_ResetRuntime
//   [ ] 0x379a88  CKBlackBall_Start
//   [ ] 0x379ad0  CKBlackBall_PostLoad
//   [ ] 0x379b38  CKBlackBall_RecursiveRegistration
//   [ ] 0x379b60  CKBlackBall_Destroy
//   [x] 0x379ba0  CKBlackBall_Construct
//   [x] 0x379bd8  CKBlackBall_DeleteArray
//   [ ] 0x379c78  CKBlackBall_DeletingDestructor
//   [ ] 0x379cc0  CKBlackBall_Destructor
//   [ ] 0x379cf0  CKBlackBall_DestructBody
//   [ ] 0x379d20  CKBlackBall_Construct_2
//   [ ] 0x379d58  RegisterCKBlackBallClass
//   [ ] 0x379de0  _GLOBAL__D_379de0
//   [ ] 0x379df0  _GLOBAL__I_379df0
//   [x] 0x379e00  CKBlackBall_CreateArray
//   [x] 0x379eb0  CKBlackBall_Create
//   [ ] 0x379f08  CKBlackBall_UpdateCharge
//   [ ] 0x37ab10  CKBlackBall_Fire
//   [ ] 0x37bd88  CKBlackBall_Save
//   [x] 0x37c8a8  CKBlackBall_Load
//
//   [ ] 0x9bf900  CKBlackBall_IsKindOfClass  [inline]
//   [ ] 0x9bf950  CKBlackBall_GetClassType  [inline]
//   [ ] 0x9bf958  CKBlackBall_GetClassID  [inline]
//   [ ] 0x9bf960  CKBlackBall_StartEmitterFx  [inline]
#include "k2000/logic/CKBlackBall.h"

#include <cstdint>

#include "k2000/io/IKFile.h"

// 0x0037c8a8 CKBlackBall_Load: CKProjectileElement's data, then (level data only) 236 bytes: six accessor
// references, three levels of ten parameters (a 3-iteration loop), references, and two pairs of 12-byte
// vectors (a 2-iteration loop).
int32_t CKBlackBall::Load(IKFile* file, int32_t type) {
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
        ReadS32LE(file, &m_unk25c[i]);
        ReadF32LE(file, &m_unk274[i]);
        ReadF32LE(file, &m_unk220[i]);
        ReadF32LE(file, &m_unk238[i]);
        ReadF32LE(file, &m_unk250[i]);
        ReadS32LE(file, &m_unk268[i]);
        ReadF32LE(file, &m_unk280[i]);
    }
    IKFile_ReadRef(file, &m_unk2a4);
    IKFile_ReadRef(file, &m_unk2a8);
    ReadU32LEWords(file, m_unk2ac, 3);
    IKFile_ReadRef(file, &m_unk2e8);
    IKFile_ReadRef(file, &m_unk2f8);
    ReadF32LE(file, &m_unk2ec);
    ReadF32LE(file, &m_unk2f0);
    ReadU32LE(file, &m_unk2f4);
    ReadF32LE(file, &m_unk2fc);
    for (int32_t i = 0; i < 2; ++i) {
        ReadU32LEWords(file, reinterpret_cast<uint32_t*>(m_unk2b8[i]), 3);
        ReadU32LEWords(file, reinterpret_cast<uint32_t*>(m_unk2d0[i]), 3);
    }
    return 1;
}
