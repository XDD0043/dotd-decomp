// CKS08FightZoneCpnt.cpp - reconstructed original translation unit 0x274b00-0x276f58 (GAME_TOC1, main_toc1), 25 functions, 25 live.
// Primary class: CKS08FightZoneCpnt  key 0x1146  category Component  size 0xb0  vtable 0xb21eb0
// Other owners: IKHkEnemy (4)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x274b00  CKS08FightZoneCpnt_vf50
//   [ ] 0x274b08  CKS08FightZoneCpnt_vf54
//   [ ] 0x274b10  CKS08FightZoneCpnt_vf78
//   [ ] 0x274b18  CKS08FightZoneCpnt_GetFirstNonNullRef4C_maybe
//   [ ] 0x274b48  CKS08FightZoneCpnt_RecursiveRegistration
//   [ ] 0x274b70  CKS08FightZoneCpnt_Destroy
//   [x] 0x274b98  CKS08FightZoneCpnt_DeleteArray
//   [x] 0x274c38  CKS08FightZoneCpnt_Create
//   [ ] 0x274ce0  RegisterCKS08FightZoneCpntClass
//   [ ] 0x274d68  _GLOBAL__D_274d68
//   [ ] 0x274d78  _GLOBAL__I_274d78
//   [ ] 0x274d88  CKS08FightZoneCpnt_vf6C
//   [x] 0x274dd8  CKS08FightZoneCpnt_vf60
//   [ ] 0x274e08  CKS08FightZoneCpnt_vf58
//   [ ] 0x274fd0  CKS08FightZoneCpnt_vf7C
//   [ ] 0x275050  CKS08FightZoneCpnt_PostLoad
//   [ ] 0x275058  CKS08FightZoneCpnt_Update_maybe
//   [x] 0x275510  CKS08FightZoneCpnt_CreateArray
//   [ ] 0x275630  CKS08FightZoneCpnt_vf68
//   [x] 0x2758c0  CKS08FightZoneCpnt_Load
//   [ ] 0x2765c0  CKS08FightZoneCpnt_Save
//   [ ] 0x276f00  IKHkEnemy_ClearReferences
//   [ ] 0x276f40  IKHkEnemy_ResetRuntime
//   [ ] 0x276f48  IKHkEnemy_OnLevelExit_maybe
//   [ ] 0x276f50  IKHkEnemy_vfC8
//
//   [x] 0x9bc418  CKS08FightZoneCpnt_vf64  [inline]
//   [x] 0x9bc4c8  CKS08FightZoneCpnt_IsKindOfClass  [inline]
//   [x] 0x9bc4f0  CKS08FightZoneCpnt_GetClassType  [inline]
//   [x] 0x9bc4f8  CKS08FightZoneCpnt_GetClassID  [inline]
//   [ ] 0x9bc500  CKS08FightZoneCpnt_vf74  [inline]
//   [ ] 0x9bc510  CKS08FightZoneCpnt_vf70  [inline]
//   [ ] 0x9bc518  CKS08FightZoneCpnt_Destructor  [inline]
//   [ ] 0x9bc640  CKS08FightZoneCpnt_DeletingDestructor  [inline]
#include "Spyro2008/components/CKS08FightZoneCpnt.h"

#include "k2000/groups/TVectorPush.h"

// 0x00274dd8 CKS08FightZoneCpnt_vf60: the byte +0xa4 is 1 when the vector at +0x30 is empty (the original's
// |n| - 1 sign bit), 0 otherwise.
void CKS08FightZoneCpnt::Vf60() {
    m_unka8 = 0;
    m_unk94 = 0;
    m_unka4 = m_vUnk30.m_ui32NbUsedElt == 0 ? 1 : 0;
}

// 0x002758c0 CKS08FightZoneCpnt_Load. No type test: every type reads the data.
int32_t CKS08FightZoneCpnt::Load(IKFile* file, int32_t type) {
    KBaseDC6::Load(file, type);
    ReadU32LE(file, &m_unk04);
    ReadF32LE(file, &m_unk18);
    ReadF32LE(file, &m_unk1c);
    ReadU32LE(file, &m_unk20);
    for (uint32_t& w : m_unk24) ReadU32LE(file, &w);
    TVector_LoadRefsCounted(m_vUnk30, file);
    ReadU32LE(file, &m_unk3c);
    ReadF32LE(file, &m_unk0c);
    ReadU8(file, &m_unk10);
    ReadF32LE(file, &m_unk40);
    ReadF32LE(file, &m_unk48);
    IKFile_ReadRef(file, &m_pUnk4c);
    ReadU32LE(file, &m_unk58);
    TVector_LoadRefsCounted(m_vUnk64, file);
    TVector_LoadBytes(m_vUnk70, file);
    TVector_LoadRefsCounted(m_vUnk98, file);
    TVector_LoadBytes(m_vUnk7c, file);
    TVector_LoadBytes(m_vUnk88, file);
    IKFile_ReadRef(file, &m_pUnk50);
    ReadF32LE(file, &m_unk60);
    IKFile_ReadRef(file, &m_pUnk54);
    ReadU8(file, &m_unkac);
    return 1;
}
