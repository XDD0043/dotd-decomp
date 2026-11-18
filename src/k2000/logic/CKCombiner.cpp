// CKCombiner.cpp - reconstructed original translation unit 0x233db0-0x234850 (GAME_TOC1, main_toc1), 17 functions, 17 live.
// Primary class: CKCombiner  key 0x22cc  category Logic  size 0x10  vtable 0xb20900
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x233db0  CKCombiner_Delete
//   [ ] 0x233e00  RegisterCKCombinerClass
//   [ ] 0x233e78  _GLOBAL__I_233e78
//   [x] 0x233e88  CKCombiner_Load
//   [ ] 0x234010  CKCombiner_Save
//   [x] 0x234038  CKCombiner_Destroy  (KStub_Nop_235180: IKEvaluator's empty Destroy)
//   [x] 0x234060  CKCombiner_DeleteArray
//   [x] 0x234100  CKCombiner_Create
//   [x] 0x234150  CKCombiner_RecursiveRegistration
//   [x] 0x2341f0  CKCombiner_vf50
//   [x] 0x234258  CKCombiner_vf68
//   [x] 0x2342c0  CKCombiner_vf64
//   [x] 0x234328  CKCombiner_vf60
//   [x] 0x234390  CKCombiner_ClearEventLatches_maybe
//   [x] 0x2343f8  CKCombiner_ClearFiredEvents_maybe
//   [x] 0x234460  CKCombiner_CreateArray
//   [x] 0x234508  CKCombiner_Evaluate
//
//   [ ] 0x9b7518  CKCombiner_IsKindOfClass  [inline]
//   [ ] 0x9b7540  CKCombiner_GetClassType  [inline]
//   [ ] 0x9b7548  CKCombiner_GetClassID  [inline]
//   [ ] 0x9b7550  CKCombiner_Destructor  [inline]
//   [ ] 0x9b7570  CKCombiner_DeletingDestructor  [inline]
#include "k2000/logic/CKCombiner.h"

#include "k2000/io/IKFile.h"

// 0x00234150 CKCombiner_RecursiveRegistration
void CKCombiner::RecursiveRegistration(int32_t type) {
    IKEvaluator::RecursiveRegistration(type);  // 0x00235030
    if (type != 0) return;
    for (IKEvaluator* evaluator = m_lEvaluators; evaluator != nullptr; evaluator = evaluator->m_pNext) {
        evaluator->RecursiveRegistration(0);  // vt+0x24
    }
}

// 0x00233e88 CKCombiner_Load: each referenced evaluator is pushed at the head of the list (the
// referenced objects are already created, so their m_pNext is written here).
int32_t CKCombiner::Load(IKFile* file, int32_t type) {
    const int32_t result = IKEvaluator::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return result;
    uint32_t count = 0;
    ReadU32LE(file, &count);
    for (uint32_t i = 0; i < count; ++i) {
        IKEvaluator* evaluator = nullptr;
        IKFile_ReadRef(file, &evaluator);
        evaluator->m_pNext = m_lEvaluators;  // BUG(original): no null check
        m_lEvaluators = evaluator;
    }
    return result;
}

// 0x00234328 CKCombiner_vf60
void CKCombiner::Vf60() {
    for (IKEvaluator* evaluator = m_lEvaluators; evaluator != nullptr; evaluator = evaluator->m_pNext) evaluator->Vf60();
}

// 0x002343f8 CKCombiner_ClearFiredEvents_maybe: Start on each evaluator, in list order.
void CKCombiner::Start() {
    for (IKEvaluator* evaluator = m_lEvaluators; evaluator != nullptr; evaluator = evaluator->m_pNext) evaluator->Start();
}

// 0x002342c0 CKCombiner_vf64
void CKCombiner::Asleep() {
    for (IKEvaluator* evaluator = m_lEvaluators; evaluator != nullptr; evaluator = evaluator->m_pNext) evaluator->Asleep();
}

// 0x00234258 CKCombiner_vf68
void CKCombiner::Vf68() {
    for (IKEvaluator* evaluator = m_lEvaluators; evaluator != nullptr; evaluator = evaluator->m_pNext) evaluator->Vf68();
}

// 0x002341f0 CKCombiner_vf50
void CKCombiner::Vf50() {
    for (IKEvaluator* evaluator = m_lEvaluators; evaluator != nullptr; evaluator = evaluator->m_pNext) evaluator->Vf50();
}

// 0x00234390 CKCombiner_ClearEventLatches_maybe
void CKCombiner::Vf5C() {
    for (IKEvaluator* evaluator = m_lEvaluators; evaluator != nullptr; evaluator = evaluator->m_pNext) evaluator->Vf5C();
}

// 0x00234508 CKCombiner_Evaluate: the evaluators in list order, each stopping as soon as the result is known.
// Flags bits 1-3: 0 (and 6, 7) all true; 1 not all true; 2 any true; 3 none true; 4 exactly one true (false
// without any); 5 not exactly one true (true without any).
bool CKCombiner::Vf54() {
    IKEvaluator* node = m_lEvaluators;
    switch ((m_ba32Flags >> 1) & 7) {
        default:
            for (; node != nullptr; node = node->m_pNext) {
                if (!node->Vf54()) return false;
            }
            return true;
        case 1:
            for (; node != nullptr; node = node->m_pNext) {
                if (!node->Vf54()) return true;
            }
            return false;
        case 2:
            for (; node != nullptr; node = node->m_pNext) {
                if (node->Vf54()) return true;
            }
            return false;
        case 3:
            for (; node != nullptr; node = node->m_pNext) {
                if (node->Vf54()) return false;
            }
            return true;
        case 4:
            for (; node != nullptr; node = node->m_pNext) {
                if (node->Vf54()) {
                    for (node = node->m_pNext; node != nullptr; node = node->m_pNext) {
                        if (node->Vf54()) return false;
                    }
                    return true;
                }
            }
            return false;
        case 5:
            for (; node != nullptr; node = node->m_pNext) {
                if (node->Vf54()) {
                    for (node = node->m_pNext; node != nullptr; node = node->m_pNext) {
                        if (node->Vf54()) return true;
                    }
                    return false;
                }
            }
            return true;
    }
}
