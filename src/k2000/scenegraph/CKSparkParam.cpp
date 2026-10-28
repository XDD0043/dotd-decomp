// CKSparkParam.cpp - reconstructed original translation unit 0xe4ed0-0xe5ba8 (GAME_TOC1, main_toc1), 20 functions, 15 live.
// Primary class: CKSparkParam  key 0x110b  category SceneNode  size 0x9c  vtable 0xb18ac0
// Other owners: CParticlesNodeFx (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0xe4ed0  CKSparkParam_Delete
//   [ ] 0xe4f20  CKSparkParam_Construct  [dead]
//   [ ] 0xe4f30  RegisterCKSparkParamClass
//   [ ] 0xe4fa8  _GLOBAL__I_e4fa8
//   [x] 0xe4fb8  CKSparkParam_DeleteArray
//   [ ] 0xe5058  CKSparkParam_Copy_maybe
//   [ ] 0xe51e0  CKSparkParam_Construct_2  [dead]
//   [x] 0xe51f0  CKSparkParam_CreateArray
//   [x] 0xe5280  CKSparkParam_Create
//   [ ] 0xe52b8  CKSparkParam_Save
//   [ ] 0xe52c0  CKSparkParam_RecursiveRegistration
//   [ ] 0xe52c8  CKSparkParam_PostLoad
//   [ ] 0xe52d0  CKSparkParam_Destroy
//   [ ] 0xe5318  CKSparkParam_Destructor
//   [ ] 0xe5330  CKSparkParam_Destructor_2  [dead]
//   [ ] 0xe5348  CKSparkParam_DeletingDestructor
//   [x] 0xe5388  CKSparkParam_Load
//   [ ] 0xe5b38  CParticlesNodeFx_Delete
//   [ ] 0xe5b88  FUN_000e5b88  [dead]
//   [ ] 0xe5b98  FUN_000e5b98  [dead]
//
//   [ ] 0x9a5480  CKSparkParam_GetClassType  [inline]
//   [ ] 0x9a5488  CKSparkParam_GetClassID  [inline]
//   [ ] 0x9a5490  CKSparkParam_IsKindOfClass  [inline]
#include "k2000/scenegraph/CKSparkParam.h"

#include <cstring>

#include "k2000/io/IKFile.h"

namespace {
// One read of `count` words, each swapped (the original's inlined Read + lwbrx), into floats.
void ReadFloatWords(IKFile* file, float* dst, uint32_t count) {
    uint32_t words[3];
    ReadU32LEWords(file, words, count);
    std::memcpy(dst, words, count * 4);
}
}  // namespace

// 0x000e5388 CKSparkParam_Load
int32_t CKSparkParam::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadFloatWords(file, &m_afUnk04[0], 3);   // +0x04
    ReadFloatWords(file, &m_afUnk04[3], 3);   // +0x10
    ReadFloatWords(file, &m_afUnk04[6], 3);   // +0x1c
    ReadFloatWords(file, &m_afUnk04[9], 3);   // +0x28
    ReadFloatWords(file, &m_afUnk04[12], 3);  // +0x34
    ReadFloatWords(file, &m_afUnk04[15], 2);  // +0x40
    ReadFloatWords(file, &m_afUnk04[17], 2);  // +0x48
    ReadFloatWords(file, &m_afUnk04[19], 2);  // +0x50
    ReadFloatWords(file, &m_afUnk04[21], 2);  // +0x58
    for (int32_t i = 23; i < 29; ++i) ReadF32LE(file, &m_afUnk04[i]);  // +0x60..+0x74
    for (int32_t i = 0; i < 4; ++i) ReadRaw(file, m_aColor78[i], 4);    // not swapped
    ReadF32LE(file, &m_unk88);
    ReadF32LE(file, &m_unk8c);
    ReadF32LE(file, &m_unk90);
    IKFile_ReadTextureRef(file, &m_pTexture94, 1);
    ReadRaw(file, &m_aUnk98[0], 1);
    ReadRaw(file, &m_aUnk98[1], 1);
    ReadRaw(file, &m_aUnk98[2], 1);
    return 1;
}
