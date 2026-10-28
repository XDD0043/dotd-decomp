// CKHkS08PowerBucket.cpp - reconstructed original translation unit 0x4d3438-0x4d5418 (GAME_TOC1, main_toc1), 34 functions, 34 live.
// Primary class: CKHkS08PowerBucket  key 0x30c2  category Hook  size 0x20c  vtable 0xb29c50
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x4d3438  CKHkS08PowerBucket_vf124
//   [ ] 0x4d3490  CKHkS08PowerBucket_vf120
//   [ ] 0x4d34e8  CKHkS08PowerBucket_vf168
//   [ ] 0x4d3510  CKHkS08PowerBucket_vfEC
//   [ ] 0x4d3588  CKHkS08PowerBucket_Resume
//   [ ] 0x4d35b0  CKHkS08PowerBucket_Restart
//   [ ] 0x4d3648  CKHkS08PowerBucket_Pause
//   [ ] 0x4d3670  CKHkS08PowerBucket_PostLoad
//   [ ] 0x4d36c0  CKHkS08PowerBucket_Save
//   [ ] 0x4d36e8  CKHkS08PowerBucket_RecursiveRegistration
//   [ ] 0x4d3710  CKHkS08PowerBucket_Destroy
//   [ ] 0x4d3738  CKHkS08PowerBucket_DeletingDestructor
//   [x] 0x4d3780  CKHkS08PowerBucket_Construct
//   [ ] 0x4d37b8  CKHkS08PowerBucket_Construct_2
//   [x] 0x4d37f0  CKHkS08PowerBucket_DeleteArray
//   [ ] 0x4d3890  RegisterCKHkS08PowerBucketClass
//   [ ] 0x4d3918  _GLOBAL__D_4d3918
//   [ ] 0x4d3928  _GLOBAL__I_4d3928
//   [ ] 0x4d3938  CKHkS08PowerBucket_vf174
//   [ ] 0x4d39c8  CKHkS08PowerBucket_vf170
//   [ ] 0x4d3a58  CKHkS08PowerBucket_vf16C
//   [ ] 0x4d3ae8  CKHkS08PowerBucket_vfF8
//   [ ] 0x4d3cf8  CKHkS08PowerBucket_Stop
//   [ ] 0x4d3d48  CKHkS08PowerBucket_vf194
//   [ ] 0x4d3da0  CKHkS08PowerBucket_Destructor
//   [ ] 0x4d3dd0  CKHkS08PowerBucket_DestructBody
//   [ ] 0x4d3e00  CKHkS08PowerBucket_Start
//   [x] 0x4d3f10  CKHkS08PowerBucket_CreateArray
//   [x] 0x4d3fc0  CKHkS08PowerBucket_Create
//   [x] 0x4d4018  CKHkS08PowerBucket_Load
//   [ ] 0x4d4358  CKHkS08PowerBucket_TriggerFx_maybe
//   [ ] 0x4d4628  CKHkS08PowerBucket_Update
//   [ ] 0x4d48c0  CKHkS08PowerBucket_OnImpact_maybe
//   [ ] 0x4d4fc0  CKHkS08PowerBucket_SpawnAltImpactFx_maybe
//
//   [ ] 0x9c5e20  CKHkS08PowerBucket_IsKindOfClass  [inline]
//   [ ] 0x9c5e98  CKHkS08PowerBucket_GetClassType  [inline]
//   [ ] 0x9c5ea0  CKHkS08PowerBucket_GetClassID  [inline]
//   [ ] 0x9c5ea8  CKHkS08PowerBucket_vf104  [inline]
#include "Spyro2008/hooks/CKHkS08PowerBucket.h"

#include "k2000/io/IKFile.h"

// 0x004d4018 CKHkS08PowerBucket_Load
int32_t CKHkS08PowerBucket::Load(IKFile* file, int32_t type) {
    CKHkS08TransportableWeight::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadF32LE(file, &m_unk1f4);
    IKFile_ReadRef(file, &m_unk1d4);
    IKFile_ReadRef(file, &m_unk1d8);
    ReadF32LE(file, &m_unk1f8);
    IKFile_ReadRef(file, &m_unk1d0);
    IKFile_ReadRef(file, &m_unk1e0);
    ReadU32LE(file, &m_unk1dc);
    IKFile_ReadRef(file, &m_unk1cc);
    ReadF32LE(file, &m_unk1ec);
    return 1;
}
