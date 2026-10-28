// CKHkS08Malefor.cpp - reconstructed original translation unit 0x4e15d0-0x4e7ac0 (GAME_TOC1, main_toc1), 47 functions, 46 live.
// Primary class: CKHkS08Malefor  key 0x3502  category Hook  size 0x1d4  vtable 0xb2a660
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x4e15d0  CKHkS08Malefor_Delete
//   [ ] 0x4e1620  CKHkS08Malefor_vf100
//   [ ] 0x4e1628  CKHkS08Malefor_vf104
//   [ ] 0x4e1630  CKHkS08Malefor_vf108
//   [ ] 0x4e1638  CKHkS08Malefor_vf11C
//   [ ] 0x4e1640  CKHkS08Malefor_InitCollisionVolume_maybe  [dead]
//   [ ] 0x4e16b0  CKHkS08Malefor_UpdateScaleByDistance_maybe
//   [ ] 0x4e17d8  CKHkS08Malefor_AccumulateDamage_maybe
//   [ ] 0x4e1a80  CKHkS08Malefor_AccumulateDamage_2_maybe
//   [ ] 0x4e1d28  CKHkS08Malefor_vf114
//   [ ] 0x4e1d80  CKHkS08Malefor_UpdateHotSpotSegmentVolumes_maybe
//   [ ] 0x4e2080  CKHkS08Malefor_GetInfo
//   [ ] 0x4e20d0  CKHkS08Malefor_SpawnExplosionAt_maybe
//   [ ] 0x4e2190  CKHkS08Malefor_TriggerHotSpotExplosionFx_maybe
//   [ ] 0x4e2270  CKHkS08Malefor_SpawnDamageImpactFx_maybe
//   [ ] 0x4e2510  CKHkS08Malefor_SetCollisionActive_maybe
//   [ ] 0x4e2698  CKHkS08Malefor_Resume
//   [ ] 0x4e26c0  CKHkS08Malefor_Pause
//   [ ] 0x4e26e8  CKHkS08Malefor_Stop
//   [ ] 0x4e2710  CKHkS08Malefor_Save
//   [ ] 0x4e2738  CKHkS08Malefor_RecursiveRegistration
//   [ ] 0x4e2760  CKHkS08Malefor_Destroy
//   [ ] 0x4e27a8  CKHkS08Malefor_DestructBody
//   [ ] 0x4e2820  CKHkS08Malefor_Construct_2
//   [x] 0x4e2860  CKHkS08Malefor_Construct
//   [x] 0x4e28a0  CKHkS08Malefor_DeleteArray
//   [ ] 0x4e2940  RegisterCKHkS08MaleforClass
//   [ ] 0x4e29c8  _GLOBAL__D_4e29c8
//   [ ] 0x4e29d8  _GLOBAL__I_4e29d8
//   [ ] 0x4e29e8  CKHkS08Malefor_OnDeactivate
//   [ ] 0x4e2ad8  CKHkS08Malefor_OnActivate
//   [ ] 0x4e2c48  CKHkS08Malefor_MessageProc
//   [ ] 0x4e2dd8  CKHkS08Malefor_DeletingDestructor
//   [ ] 0x4e2e60  CKHkS08Malefor_Destructor
//   [ ] 0x4e2ed8  CKHkS08Malefor_Restart
//   [x] 0x4e2fb0  CKHkS08Malefor_CreateArray
//   [x] 0x4e3070  CKHkS08Malefor_Create
//   [ ] 0x4e30d0  CKHkS08Malefor_Start
//   [ ] 0x4e3198  CKHkS08Malefor_PostLoad
//   [ ] 0x4e3248  CKHkS08Malefor_ProcessDamageContacts_maybe
//   [x] 0x4e3eb8  CKHkS08Malefor_Load
//   [ ] 0x4e54d0  CKHkS08Malefor_UpdateCollisionVolumesFromBones_maybe
//   [ ] 0x4e6560  CKHkS08Malefor_vf110
//   [ ] 0x4e6570  CKHkS08Malefor_vf10C
//   [ ] 0x4e6580  CKHkS08Malefor_SpawnElementHitFx_maybe
//   [ ] 0x4e6fd8  CKHkS08Malefor_ApplyPendingDamage_maybe
//   [ ] 0x4e75d8  CKHkS08Malefor_Update
//
//   [ ] 0x9c63f8  CKHkS08Malefor_IsKindOfClass  [inline]
//   [ ] 0x9c6458  CKHkS08Malefor_GetClassType  [inline]
//   [ ] 0x9c6460  CKHkS08Malefor_GetClassID  [inline]
#include "Spyro2008/hooks/CKHkS08Malefor.h"

#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"

// 0x004e3eb8 CKHkS08Malefor_Load
int32_t CKHkS08Malefor::Load(IKFile* file, int32_t type) {
    CKHkGolem::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    IKFile_ReadRef(file, &m_unkE4);
    IKFile_ReadRef(file, &m_unkE8);
    ReadU8(file, &m_unkEC);
    m_apUnkF0 = static_cast<IKSerializable**>(
        Mem_AllocAligned16(m_unkEC * static_cast<uint32_t>(sizeof(IKSerializable*))));
    IKFile_ReadObjectRefArray(file, m_apUnkF0, m_unkEC);
    IKFile_ReadObjectRefArray(file, m_apUnkF4, 2);
    for (uint32_t& word : m_unkFC) ReadU32LE(file, &word);
    IKFile_ReadRef(file, &m_unk164);
    ReadU8(file, &m_unk168);
    for (IKSerializable*& object : m_apUnk174) IKFile_ReadRef(file, &object);
    ReadF32LE(file, &m_unkE0);
    ReadU32LE(file, &m_unk16C);
    ReadU32LE(file, &m_unk170);
    IKFile_ReadRef(file, &m_unk188);
    for (IKSerializable*& object : m_apUnk110) IKFile_ReadRef(file, &object);
    for (IKSerializable*& object : m_apUnk140) IKFile_ReadRef(file, &object);
    IKFile_ReadRef(file, &m_unk18C);
    IKFile_ReadRef(file, &m_unk190);
    for (uint32_t& word : m_unk194) ReadU32LE(file, &word);
    return 1;
}
