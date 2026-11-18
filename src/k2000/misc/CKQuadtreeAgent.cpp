// Reconstructed original translation unit: 0x47d78-0x48228 (GAME_TOC1, main_toc1), 11 functions, 8 live.
// Primary owner: CKQuadtreeAgent (not a registered class)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x47d78  CKQuadtreeAgent_RepositionSelf_maybe  [dead]
//   [ ] 0x47db0  CKQuadtreeAgent_600c_maybe_ConstructBase_2  [dead]
//   [x] 0x47dc8  CKQuadtreeAgent_600c_maybe_ConstructBase  (CKQuadtreeAgent.h constructor)
//   [x] 0x47de0  CKQuadtreeAgent_600c_maybe_vf28  (the default Save (returns 1))
//   [x] 0x47de8  CKQuadtreeAgent_600c_maybe_vf24  (the default RecursiveRegistration (returns 1, registers nothing))
//   [x] 0x47df0  KStub_Nop_47df0  (Destroy: the default (empty))
//   [x] 0x47df8  CKQuadtreeAgent_600c_maybe_Load  (CKQuadtreeAgent.h Load)
//   [x] 0x480f8  CKQuadtreeAgent_600c_maybe_DeletingDestructor  (the deleting form of CKQuadtreeAgent.h's destructor)
//   [x] 0x48138  CKQuadtreeAgent_600c_maybe_vf0  (CKQuadtreeAgent.h destructor: vtable stores only)
//   [x] 0x48150  CKQuadtreeAgent_600c_maybe_BaseDestructor  (CKQuadtreeAgent.h destructor: vtable stores only)
//   [ ] 0x48168  FUN_00048168  [dead]
//
//   [ ] 0x995900  CKQuadtreeAgent_600c_maybe_vf14  [inline]
//   [ ] 0x995908  CKQuadtreeAgent_600c_maybe_vf18  [inline]
//   [ ] 0x995910  CKQuadtreeAgent_600c_maybe_vf8  [inline]
//   [ ] 0x995930  KStub_Return0_995930  [inline]
//   [ ] 0x995938  KStub_Return1_995938  [inline]
//   [ ] 0x995940  KStub_Return0_995940  [inline]
//   [ ] 0x995948  KStub_Nop_995948  [inline]
//   [ ] 0x995950  KStub_ReturnM1_995950  [inline]
//   [ ] 0x995958  KStub_Nop_995958  [inline]
//   [ ] 0x995960  KStub_ReturnM1_995960  [inline]
//   [ ] 0x995968  KStub_Return0_995968  [inline]
//   [ ] 0x995970  KStub_Nop_995970  [inline]
//   [ ] 0x995978  KStub_Return0_995978  [inline]
//   [ ] 0x995980  KStub_Return0_995980  [inline]
//   [ ] 0x995988  KStub_Return1_995988  [inline]
//   [ ] 0x995990  KStub_Return1_995990  [inline]
//   [ ] 0x995998  KStub_Return1_995998  [inline]
//   [ ] 0x9959a0  KStub_Return1_9959a0  [inline]
//   [ ] 0x9959a8  KStub_Nop_9959a8  [inline]
//   [ ] 0x9959b0  KStub_Nop_9959b0  [inline]
//   [ ] 0x9959b8  KStub_ReturnM2_9959b8  [inline]
//   [ ] 0x9959c0  KStub_Nop_9959c0  [inline]
//   [ ] 0x9959c8  KStub_ReturnM2_9959c8  [inline]
//   [ ] 0x9959d0  KStub_Nop_9959d0  [inline]
//   [ ] 0x9959d8  KStub_ReturnM2_9959d8  [inline]
//   [ ] 0x9959e0  KStub_Nop_9959e0  [inline]
//   [ ] 0x9959e8  KStub_ReturnM2_9959e8  [inline]
//   [ ] 0x9959f0  KStub_Nop_9959f0  [inline]
//   [ ] 0x9959f8  KStub_ReturnM2_9959f8  [inline]
//   [ ] 0x995a00  KStub_Return0_995a00  [inline]
#include "k2000/misc/CKQuadtreeAgent.h"

#include "k2000/logic/CKQuadtree.h"
#include "k2000/logic/system/CKQuadtreeCell.h"

// 0x00047d30 CKQuadtreeCell_InvalidateToRoot_maybe (unit Vt_2.cpp)
void CKQuadtreeAgent::InvalidateToRoot() {
    CKQuadtreeAgent* agent = this;
    do {
        if (agent->m_bDirty != 0) return;
        agent->m_unk28 = nullptr;
        agent->m_bDirty = 1;
        agent = static_cast<CKQuadtreeAgent*>(agent->m_unk1c);
    } while (agent != nullptr);
    CKQuadtree* tree = static_cast<CKQuadtree*>(static_cast<CKQuadtreeCell*>(m_unk24)->m_unk20);
    tree->m_unk61 = 1;
    tree->m_unk60 = 1;
}
