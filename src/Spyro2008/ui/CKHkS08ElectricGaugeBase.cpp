// CKHkS08ElectricGaugeBase.cpp - reconstructed original translation unit 0x4e0920-0x4e0ad8 (GAME_TOC1, main_toc1), 9 functions, 9 live.
// Primary owner: CKHkS08ElectricGaugeBase (not a registered class)
// Other owners: CKHkS08ElectricGauge (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x4e0920  CKHkS08ElectricGaugeBase_3542_maybe_Load
//   [ ] 0x4e0948  CKHkS08ElectricGaugeBase_3542_maybe_Save
//   [x] 0x4e0970  CKHkS08ElectricGaugeBase_3542_maybe_LevelReset  (CKHkActorBase's: inherited)
//   [x] 0x4e0998  CKHkS08ElectricGaugeBase_3542_maybe_ClearReferences  (inherited, empty)
//   [x] 0x4e09c0  CKHkS08ElectricGaugeBase_3542_maybe_DeletingDestructor  (the implicit destructor + delete)
//   [x] 0x4e0a08  CKHkS08ElectricGaugeBase_3542_maybe_Destructor  (the implicit destructor)
//   [x] 0x4e0a38  CKHkS08ElectricGaugeBase_3542_maybe_BaseDestructor  (header)
//   [x] 0x4e0a68  CKHkS08ElectricGaugeBase_3542_maybe_Construct
//   [x] 0x4e0aa0  CKHkS08ElectricGauge_ConstructBase_maybe
//
//   [ ] 0x9c6328  CKHkS08ElectricGaugeBase_3542_maybe_IsKindOf  [inline]
//   [ ] 0x9c6380  CKHkS08ElectricGaugeBase_3542_maybe_GetClassGroup  [inline]
//   [ ] 0x9c6388  CKHkS08ElectricGaugeBase_3542_maybe_GetClassId  [inline]
#include "Spyro2008/ui/CKHkS08ElectricGaugeBase.h"

// 0x004e0920 CKHkS08ElectricGaugeBase_3542_maybe_Load: CKHkActorBase's part only.
int32_t CKHkS08ElectricGaugeBase::Load(IKFile* file, int32_t type) {
    CKHkActorBase::Load(file, type);
    return 1;
}
