// CKHkS08TransportableBase.cpp - reconstructed original translation unit 0x4ac108-0x4ac358 (GAME_TOC1, main_toc1), 9 functions, 8 live.
// Primary owner: CKHkS08TransportableBase (not a registered class)
// Other owners: CKHkS08TransportableKey (2)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x4ac108  CKHkS08TransportableBase_3002_maybe_Load
//   [ ] 0x4ac1c8  CKHkS08TransportableBase_3002_maybe_Save
//   [x] 0x4ac1f0  CKHkS08TransportableBase_3002_maybe_LevelReset  (CKHkActorBase's: inherited)
//   [x] 0x4ac218  CKHkS08TransportableBase_3002_maybe_ClearReferences  (header)
//   [x] 0x4ac240  CKHkS08TransportableBase_3002_maybe_DeletingDestructor  (the implicit destructor + delete)
//   [x] 0x4ac288  CKHkS08TransportableBase_3002_maybe_Destructor  (header)
//   [x] 0x4ac2b8  CKHkS08TransportableBase_3002_maybe_BaseDestructor  (header)
//   [ ] 0x4ac2e8  CKHkS08TransportableKey_ConstructBase_2_maybe  [dead]
//   [x] 0x4ac320  CKHkS08TransportableKey_ConstructBase_maybe
//
//   [x] 0x9c5278  CKHkS08TransportableBase_3002_maybe_IsKindOf  [inline]
//   [x] 0x9c52d0  CKHkS08TransportableBase_3002_maybe_GetClassGroup  [inline]
//   [x] 0x9c52d8  CKHkS08TransportableBase_3002_maybe_GetClassId  [inline]
//   [x] 0x9c52e0  CKHkS08TransportableBase_3002_maybe_vf120  [inline]  (header)
//   [x] 0x9c52e8  CKHkS08TransportableBase_3002_maybe_vf124  [inline]
//   [x] 0x9c52f0  CKHkS08TransportableBase_3002_maybe_vf128  [inline]  (header)
#include "Spyro2008/misc/CKHkS08TransportableBase.h"

#include "k2000/io/IKFile.h"

// 0x004ac0c8 KBase3002_PostLoad: CKHkActorBase_d82_maybe_PostLoad 0x3f6e70 -> IKLife_PostLoad 0x19f68 (level type only:
// bit 2 of the bit array), then +0x28 = 0.
int32_t CKHkS08TransportableBase::PostLoad(int32_t type) {
    if (type == K_LEVEL_PLATEFORMS) m_bitArray = (m_bitArray & 0xfffffffbu) | 4u;
    m_unk28 = 0;
    return 1;
}

// 0x004ac108 CKHkS08TransportableBase_3002_maybe_Load
int32_t CKHkS08TransportableBase::Load(IKFile* file, int32_t type) {
    CKHkActorBase::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) IKFile_ReadRef(file, &m_unk20);
    return 1;
}
