// CKHkS08TransportableWeight.cpp - reconstructed original translation unit 0x4b4750-0x4b7728 (GAME_TOC1, main_toc1), 43 functions, 39 live.
// Primary class: CKHkS08TransportableWeight  key 0x3142  category Hook  size 0x1cc  vtable 0xb28e28
// Other owners: IKSerializable (6), CKGolemAttackCommon (2), CKHkS08PowerBucket (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x4b4750  CKHkS08TransportableWeight_Delete
//   [ ] 0x4b47a0  CKHkS08TransportableWeight_ReleaseFxAt138_maybe  [dead]
//   [ ] 0x4b4808  CKHkS08TransportableWeight_Resume
//   [ ] 0x4b4830  CKHkS08TransportableWeight_Pause
//   [ ] 0x4b4858  CKHkS08TransportableWeight_Stop
//   [x] 0x4b4880  CKHkS08TransportableWeight_Start
//   [x] 0x4b48c0  CKHkS08TransportableWeight_PostLoad
//   [ ] 0x4b4918  CKHkS08TransportableWeight_Save
//   [ ] 0x4b4940  CKHkS08TransportableWeight_RecursiveRegistration
//   [ ] 0x4b4968  CKHkS08TransportableWeight_Destroy
//   [x] 0x4b4990  CKHkS08TransportableWeight_Construct
//   [x] 0x4b49c8  CKHkS08TransportableWeight_DeleteArray
//   [ ] 0x4b4a68  CKHkS08TransportableWeight_BaseDestructor
//   [x] 0x4b4a98  CKHkS08PowerBucket_ConstructBase_maybe
//   [ ] 0x4b4ad0  RegisterCKHkS08TransportableWeightClass
//   [ ] 0x4b4b58  _GLOBAL__D_4b4b58
//   [ ] 0x4b4b68  _GLOBAL__I_4b4b68
//   [ ] 0x4b4b78  CKHkS08TransportableWeight_DeletingDestructor
//   [ ] 0x4b4bc0  CKHkS08TransportableWeight_Destructor
//   [ ] 0x4b4bf0  CKHkS08TransportableWeight_vfEC
//   [ ] 0x4b4c30  CKHkS08TransportableWeight_vfF0
//   [ ] 0x4b4d18  CKHkS08TransportableWeight_vfF8
//   [ ] 0x4b4f38  CKHkS08TransportableWeight_OnImpact_maybe
//   [ ] 0x4b5120  CKHkS08TransportableWeight_vf160
//   [x] 0x4b5758  CKHkS08TransportableWeight_CreateArray
//   [x] 0x4b5808  CKHkS08TransportableWeight_Create
//   [ ] 0x4b5860  CKHkS08TransportableWeight_vf188
//   [ ] 0x4b5d78  CKHkS08TransportableWeight_vf124
//   [ ] 0x4b5df0  CKHkS08TransportableWeight_Update
//   [x] 0x4b6500  CKHkS08TransportableWeight_Load
//   [ ] 0x4b6ae8  CKHkS08TransportableWeight_SpawnImpactFx_maybe
//   [ ] 0x4b6db8  CKHkS08TransportableWeight_vf120_2  [dead]
//   [ ] 0x4b7038  CKHkS08TransportableWeight_SpawnAltImpactFx_maybe
//   [ ] 0x4b7308  CKHkS08TransportableWeight_vf120
//   [ ] 0x4b7588  CKGolemAttackCommon_Delete
//   [ ] 0x4b75d8  KBaseC_vfA0_2
//   [ ] 0x4b7628  KBaseC_vf70_3
//   [ ] 0x4b7630  KBaseC_vf74_4
//   [ ] 0x4b7638  KBaseC_vf78_3
//   [ ] 0x4b7640  CKGolemAttackCommon_InitAttackVolume_maybe  [dead]
//   [ ] 0x4b7710  KStub_Nop_4b7710  [dead]
//   [ ] 0x4b7718  KBaseC_vf94_3
//   [ ] 0x4b7720  KBaseC_vf98_2
//
//   [ ] 0x9c54d0  CKHkS08TransportableWeight_IsKindOfClass  [inline]
//   [ ] 0x9c5538  CKHkS08TransportableWeight_GetClassType  [inline]
//   [ ] 0x9c5540  CKHkS08TransportableWeight_GetClassID  [inline]
//   [ ] 0x9c5548  CKHkS08TransportableWeight_vf118  [inline]
//   [ ] 0x9c5550  CKHkS08TransportableWeight_vf104  [inline]
//   [ ] 0x9c5558  CKHkS08TransportableWeight_vf17C  [inline]
//   [ ] 0x9c5560  CKHkS08TransportableWeight_vf180  [inline]
//   [ ] 0x9c5568  CKHkS08TransportableWeight_vf184  [inline]
#include "Spyro2008/hooks/CKHkS08TransportableWeight.h"

#include "k2000/io/IKFile.h"

// 0x004b6500 CKHkS08TransportableWeight_Load
int32_t CKHkS08TransportableWeight::Load(IKFile* file, int32_t type) {
    CKHkS08TransportableKey::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        IKFile_ReadRef(file, &m_unk140);
        IKFile_ReadRef(file, &m_unk144);
        ReadF32LE(file, &m_unk148);
        ReadF32LE(file, &m_unk170);
        ReadF32LE(file, &m_unk168);
        ReadF32LE(file, &m_unk14c);
        ReadF32LE(file, &m_unk16c);
        ReadF32LE(file, &m_unk174);
        ReadF32LE(file, &m_unk188);
        ReadF32LE(file, &m_unk18c);
        ReadF32LE(file, &m_unk178);
        ReadF32LE(file, &m_unk19c);
        IKFile_ReadRef(file, &m_unk1b0);
        IKFile_ReadRef(file, &m_unk134);
        IKFile_ReadRef(file, &m_unk13c);
        IKFile_ReadRef(file, &m_unk130);
        return 1;
    }
    return 1;
}

// 0x004b48c0 CKHkS08TransportableWeight_PostLoad: the Key's, then for the level type +0x138 = 0.
int32_t CKHkS08TransportableWeight::PostLoad(int32_t type) {
    CKHkS08TransportableKey::PostLoad(type);
    if (type == K_LEVEL_PLATEFORMS) m_unk138 = static_cast<uint32_t>(type);
    return 1;
}

// 0x004b4880 CKHkS08TransportableWeight_Start
void CKHkS08TransportableWeight::Start() {
    CKHkS08TransportableKey::Start();  // 0x4af358
    m_unk138 = 0;
    m_unkBC[1] = 0;  // +0xc0
}
