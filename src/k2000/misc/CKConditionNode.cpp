// CKConditionNode.cpp - reconstructed original translation unit 0x235030-0x235188 (GAME_TOC1, main_toc1), 4 functions, 4 live.
// Primary owner: CKConditionNode (not a registered class)
// Other owners: IKEvaluator (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x235030  IKEvaluator_LevelReset  (IKEvaluator_RecursiveRegistration)
//   [x] 0x235090  CKConditionNode_Load
//   [ ] 0x235108  CKConditionNode_Save
//   [x] 0x235180  KStub_Nop_235180  (CKCombiner / CKComparator Destroy call it: empty, nothing to port)
//
//   [ ] 0x9b88c8  IKEvaluator_GetClassGroup  [inline]
//   [ ] 0x9b88d0  IKEvaluator_GetClassId  [inline]
//   [ ] 0x9b88d8  IKEvaluator_Destructor  [inline]
//   [ ] 0x9b88f0  IKEvaluator_IsKindOf  [inline]
//   [ ] 0x9b8910  IKEvaluator_DeletingDestructor  [inline]
#include "k2000/misc/IKEvaluator.h"

#include "k2000/io/IKFile.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/misc/Engine.h"

// 0x00235030 IKEvaluator_RecursiveRegistration (returns 1)
void IKEvaluator::RecursiveRegistration(int32_t type) {
    if (type == 0) g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);  // vt+0x24
}

// 0x00235090 CKConditionNode_Load (IKEvaluator::Load)
int32_t IKEvaluator::Load(IKFile* file, int32_t type) {
    if (type == K_LEVEL_PLATEFORMS) ReadU32LE(file, &m_ba32Flags);
    return 1;
}
