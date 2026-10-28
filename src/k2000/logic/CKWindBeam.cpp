// CKWindBeam.cpp - reconstructed original translation unit 0x3e0248-0x3e6f80 (GAME_TOC1, main_toc1), 26 functions, 26 live.
// Primary class: CKWindBeam  key 0xa50c  category Logic  size 0x318  vtable 0xb24920
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x3e0248  CKWindBeam_ApplyDamageParams
//   [ ] 0x3e02a0  CKWindBeam_GetFxSound_maybe
//   [ ] 0x3e03e8  CKWindBeam_PostLoad
//   [ ] 0x3e0450  CKWindBeam_RecursiveRegistration
//   [ ] 0x3e0478  CKWindBeam_Destroy
//   [x] 0x3e04a0  CKWindBeam_Construct
//   [x] 0x3e04d8  CKWindBeam_DeleteArray
//   [ ] 0x3e0578  CKWindBeam_DeletingDestructor
//   [ ] 0x3e05c0  CKWindBeam_Destructor
//   [ ] 0x3e05f0  CKWindBeam_DestructBody
//   [ ] 0x3e0620  CKWindBeam_Construct_2
//   [ ] 0x3e0658  CKWindBeam_Start
//   [ ] 0x3e0758  RegisterCKWindBeamClass
//   [ ] 0x3e07e0  _GLOBAL__D_3e07e0
//   [ ] 0x3e07f0  _GLOBAL__I_3e07f0
//   [ ] 0x3e0800  CKWindBeam_End
//   [ ] 0x3e08f0  CKWindBeam_Slot80_maybe
//   [ ] 0x3e0cd8  CKWindBeam_ReleaseAndStopFx_maybe
//   [ ] 0x3e0e38  CKWindBeam_ResetRuntime
//   [ ] 0x3e0f98  CKWindBeam_GrabTarget_maybe
//   [x] 0x3e1398  CKWindBeam_CreateArray
//   [x] 0x3e1448  CKWindBeam_Create
//   [ ] 0x3e14a0  CKWindBeam_SetFxActive
//   [ ] 0x3e1e60  CKWindBeam_Slot84_maybe
//   [x] 0x3e4a18  CKWindBeam_Load
//   [ ] 0x3e5c80  CKWindBeam_Save
//
//   [ ] 0x9c0930  CKWindBeam_IsKindOfClass  [inline]
//   [ ] 0x9c0980  CKWindBeam_GetClassType  [inline]
//   [ ] 0x9c0988  CKWindBeam_GetClassID  [inline]
//   [ ] 0x9c0990  CKWindBeam_vf90  [inline]
//   [ ] 0x9c0998  CKWindBeam_StartEmitterFx  [inline]
#include "k2000/logic/CKWindBeam.h"

#include "k2000/io/IKFile.h"

// 0x003e4a18 CKWindBeam_Load: CKGrabElement's data, then (level data only) 0x154 bytes. The vectors are one
// 12-byte read each, byte-swapped word by word afterwards.
int32_t CKWindBeam::Load(IKFile* file, int32_t type) {
    CKGrabElement::Load(file, type);
    if (type == 0) {
        IKFile_ReadRef(file, &m_unk1a4);
        for (int32_t i = 0; i < 3; ++i) {
            ReadU32LE(file, &m_unk140[i]);
            ReadS32LE(file, &m_unk14c[i]);
            ReadS32LE(file, &m_unk158[i]);
            ReadU32LE(file, &m_unk164[i]);
            ReadF32LE(file, &m_unk170[i]);
            ReadU32LEWords(file, reinterpret_cast<uint32_t*>(m_unk17c[i]), 3);
        }
        ReadF32LE(file, &m_unk1a0);
        for (int32_t i = 0; i < 3; ++i) {
            IKFile_ReadRef(file, &m_unk1fc[i]);
            IKFile_ReadRef(file, &m_unk20c[i]);
        }
        IKFile_ReadRef(file, &m_unk1f8);
        for (int32_t i = 0; i < 3; ++i) {
            ReadS32LE(file, &m_unk1a8[i]);
            ReadU32LE(file, &m_unk1b4[i]);
            ReadU32LE(file, &m_unk1c0[i]);
            ReadU32LEWords(file, reinterpret_cast<uint32_t*>(m_unk1cc[i]), 3);
        }
        ReadU32LE(file, &m_unk1f0);
        ReadU32LE(file, &m_unk1f4);
        for (int32_t i = 0; i < 3; ++i) {
            IKFile_ReadRef(file, &m_unk21c[i]);
            IKFile_ReadRef(file, &m_unk228[i]);
        }
        ReadS32LE(file, &m_unk234);
        for (int32_t i = 0; i <= 3; ++i) ReadF32LE(file, &m_unk238[i]);   // +0x238..+0x244
        for (int32_t i = 7; i <= 20; ++i) ReadF32LE(file, &m_unk238[i]);  // +0x254..+0x288
        for (int32_t i = 4; i <= 6; ++i) ReadF32LE(file, &m_unk238[i]);   // +0x248..+0x250
        IKFile_ReadRef(file, &m_unk28c);
        IKFile_ReadRef(file, &m_unk290[0]);
        IKFile_ReadRef(file, &m_unk290[1]);
        IKFile_ReadRef(file, &m_unk290[2]);
    }
    return 1;
}
