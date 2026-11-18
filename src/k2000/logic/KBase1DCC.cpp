// KBase1DCC.cpp - reconstructed original translation unit 0x1a468-0x1a5c0 (GAME_TOC1, main_toc1), 12 functions, 11 live.
// Primary owner: KBase1DCC (not a registered class)
// Other owners: CKSrvFxParticlesAccessor (1), CKService (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1a468  KBase1DCC_ConstructBase
//   [x] 0x1a478  CKSrvFxParticlesAccessor_RecursiveRegistration  (KBase1DCC::RecursiveRegistration, KBase1DCC.h)
//   [x] 0x1a4d8  KBase1DCC_DeletingDestructor  (the destructor; delete)
//   [x] 0x1a520  KBase1DCC_Destructor  (C++ destructor chain: vtable stores only)
//   [x] 0x1a550  KBase1DCC_BaseDestructor  (C++ destructor chain: vtable stores only)
//   [ ] 0x1a580  KBase1DCC_ConstructBase_2  [dead]
//   [x] 0x1a590  KBase1DCC_vf28  (Save: returns 1, the default slot)
//   [x] 0x1a598  KBase1DCC_Load
//   [x] 0x1a5a0  KBase1DCC_PostLoad  (returns 1: the default slot)
//   [x] 0x1a5a8  KStub_Nop_1a5a8  (empty)
//   [x] 0x1a5b0  KStub_Return1_1a5b0  (IKService's PostLoad: returns 1, the default slot)
//   [x] 0x1a5b8  CKService_ClearReferences_BaseNop_maybe  (empty)
//
//   [ ] 0x9928b0  KBase1DCC_vf14  [inline]
//   [ ] 0x9928b8  KBase1DCC_vf18  [inline]
//   [x] 0x9928c0  KBase1DCC_vf8  [inline]
//   [ ] 0x9928e0  KStub_Nop_9928e0  [inline]
//   [ ] 0x9928e8  KStub_Return0_9928e8  [inline]
//   [ ] 0x9928f0  KStub_Nop_9928f0  [inline]
//   [ ] 0x9928f8  KStub_Nop_9928f8  [inline]
//   [ ] 0x992900  KStub_Nop_992900  [inline]
#include "k2000/logic/KBase1DCC.h"

#include "k2000/logic/CKSavingManager.h"
#include "k2000/misc/Engine.h"

// 0x0001a598 KBase1DCC_Load: reads nothing.
int32_t KBase1DCC::Load(IKFile* /*file*/, int32_t /*type*/) { return 1; }

// 0x0001a478 CKSrvFxParticlesAccessor_RecursiveRegistration (KBase1DCC's slot)
void KBase1DCC::RecursiveRegistration(int32_t type) {
    if (type == 0) g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);  // vt+0x24
}
