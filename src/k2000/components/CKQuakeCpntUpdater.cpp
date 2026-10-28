// CKQuakeCpntUpdater.cpp - reconstructed original translation unit 0x24ebb8-0x24fba0 (GAME_TOC1, main_toc1), 19 functions, 19 live.
// Primary class: CKQuakeCpntUpdater  key 0x986  category Component  size 0x20  vtable 0xb20f50
// Other owners: ShakeSample (3), ShakeEffect (3)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x24ebb8  CKQuakeCpntUpdater_Delete
//   [ ] 0x24ec08  ShakeSample_ApplyToElement2d_maybe
//   [ ] 0x24ee00  CKQuakeCpntUpdater_GetQuakeCpnt_maybe
//   [ ] 0x24ee08  RegisterCKQuakeCpntUpdaterClass
//   [ ] 0x24ee80  _GLOBAL__I_24ee80
//   [ ] 0x24ee90  ShakeSample_BuildMatrix_maybe
//   [ ] 0x24f578  ShakeSample_ApplyToNode_maybe
//   [x] 0x24f5c8  CKQuakeCpntUpdater_EvaluateScaled
//   [x] 0x24f738  CKQuakeCpntUpdater_Stop
//   [x] 0x24f770  CKQuakeCpntUpdater_Start
//   [x] 0x24f7a8  CKQuakeCpntUpdater_DeleteArray
//   [x] 0x24f848  CKQuakeCpntUpdater_Create
//   [x] 0x24f898  CKQuakeCpntUpdater_CreateArray
//   [x] 0x24f958  CKQuakeCpntUpdater_Load
//   [ ] 0x24f9e8  CKQuakeCpntUpdater_Save
//   [ ] 0x24f9f0  CKQuakeCpntUpdater_RecursiveRegistration
//   [ ] 0x24f9f8  CKQuakeCpntUpdater_Destroy
//   [x] 0x24fa00  CKQuakeCpntUpdater_AllocCurveStates_maybe
//   [x] 0x24fb60  CKQuakeCpntUpdater_PostLoad
//
//   [ ] 0x9ba298  CKQuakeCpntUpdater_IsKindOfClass  [inline]
//   [x] 0x9ba2c0  CKQuakeCpntUpdater_GetClassType  [inline]
//   [x] 0x9ba2c8  CKQuakeCpntUpdater_GetClassID  [inline]
//   [ ] 0x9ba2d0  CKQuakeCpntUpdater_Destructor  [inline]
//   [ ] 0x9ba328  CKQuakeCpntUpdater_DeletingDestructor  [inline]
#include "k2000/components/CKQuakeCpntUpdater.h"

#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"

// 0x0024f848 CKQuakeCpntUpdater_Create, the inlined constructor: the curve-state list only.
CKQuakeCpntUpdater::CKQuakeCpntUpdater() {
    m_curveStates.m_pBlock = nullptr;
    m_curveStates.m_ui32NbElt = 1;
    m_curveStates.m_ui32NbUsedElt = 0;
}

// 0x0024f958 CKQuakeCpntUpdater_Load
int32_t CKQuakeCpntUpdater::Load(IKFile* file, int32_t type) {
    if (type == K_LEVEL_PLATEFORMS) IKFile_ReadRef(file, &m_pQuake);
    return 1;
}

// 0x0024fb60 CKQuakeCpntUpdater_PostLoad: for type 0 (the level) the effect stopped and its states allocated.
int32_t CKQuakeCpntUpdater::PostLoad(int32_t type) {
    if (type == 0) {
        m_fElapsed = 0.0f;
        m_bRunning = 0;
        AllocCurveStates();
    }
    return 1;
}

// 0x0024fa00 CKQuakeCpntUpdater_AllocCurveStates_maybe
void CKQuakeCpntUpdater::AllocCurveStates() {
    if (m_pQuake != nullptr && m_pQuake->m_entries.m_ui32NbUsedElt != 0) {
        if (m_curveStates.m_pBlock != nullptr) Mem_FreeAligned16(m_curveStates.m_pBlock);
        m_curveStates.m_ui32NbUsedElt = 0;
        m_curveStates.m_pBlock = nullptr;
        const uint32_t count = m_pQuake->m_entries.m_ui32NbUsedElt;
        m_curveStates.m_ui32NbElt = count;
        m_curveStates.m_pBlock =
            static_cast<CurveState*>(Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(CurveState))));
        if (m_curveStates.m_ui32NbElt < count) {  // as in the original: cannot happen right after the assignment
            const uint32_t capacity = count + 1;
            if (capacity == 0) {
                m_curveStates.m_pBlock = static_cast<CurveState*>(
                    Mem_ReallocAligned16(m_curveStates.m_pBlock, static_cast<uint32_t>(sizeof(CurveState))));
                m_curveStates.m_ui32NbElt = 1;
            } else {
                m_curveStates.m_pBlock = static_cast<CurveState*>(
                    Mem_ReallocAligned16(m_curveStates.m_pBlock, capacity * static_cast<uint32_t>(sizeof(CurveState))));
                m_curveStates.m_ui32NbElt = capacity;
            }
        }
        m_curveStates.m_ui32NbUsedElt = count;
        return;
    }
    if (m_curveStates.m_pBlock != nullptr) Mem_FreeAligned16(m_curveStates.m_pBlock);
    m_curveStates.m_ui32NbElt = 1;
    m_curveStates.m_ui32NbUsedElt = 0;
    m_curveStates.m_pBlock = nullptr;
    m_curveStates.m_pBlock = static_cast<CurveState*>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(CurveState))));
}

// 0x0024f770 CKQuakeCpntUpdater_Start
void CKQuakeCpntUpdater::Start() {
    if (m_pQuake != nullptr) m_pQuake->StartEffect(this);
}

// 0x0024f738 CKQuakeCpntUpdater_Stop
void CKQuakeCpntUpdater::Stop() {
    if (m_pQuake != nullptr) m_pQuake->StopEffect(this);
}

// 0x0024f5c8 CKQuakeCpntUpdater_EvaluateScaled
void CKQuakeCpntUpdater::EvaluateScaled(float dt, float scale, float out[15]) {
    if (m_pQuake == nullptr) {
        for (int32_t i = 0; i < 15; ++i) out[i] = 0.0f;
        return;
    }
    m_pQuake->Evaluate(dt, out, this);
    for (int32_t i = 0; i < 15; ++i) out[i] = out[i] * scale;
}
