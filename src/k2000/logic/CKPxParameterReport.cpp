// CKPxParameterReport.cpp - reconstructed original translation unit 0x2322b0-0x232f30 (GAME_TOC1, main_toc1), 16 functions, 14 live.
// Primary class: CKPxParameterReport  key 0x568c  category Logic  size 0x70  vtable 0xb20798
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x2322b0  CKPxParameterReport_Delete
//   [ ] 0x232300  CKPxParameterReport_Construct  [dead]
//   [ ] 0x232320  RegisterCKPxParameterReportClass
//   [ ] 0x232398  _GLOBAL__I_232398
//   [x] 0x2323a8  CKPxParameterReport_DeleteArray
//   [ ] 0x232450  CKPxParameterReport_Construct_2  [dead]
//   [x] 0x232470  CKPxParameterReport_AddSampleToSlidingWindow_maybe  (AddSampleToSlidingWindow)
//   [x] 0x232b20  CKPxParameterReport_Create  (header)
//   [x] 0x232b70  CKPxParameterReport_CreateArray
//   [ ] 0x232c28  CKPxParameterReport_Save
//   [x] 0x232c30  CKPxParameterReport_Load
//   [x] 0x232dd0  CKPxParameterReport_RecursiveRegistration  (returns 1, registers nothing: the default)
//   [x] 0x232dd8  CKPxParameterReport_Destroy
//   [x] 0x232e28  CKPxParameterReport_Destructor
//   [x] 0x232e78  CKPxParameterReport_Destructor_2  (the destructor)
//   [x] 0x232ec8  CKPxParameterReport_DeletingDestructor  (the destructor; delete)
//
//   [ ] 0x9b72d8  CKPxParameterReport_GetClassType  [inline]
//   [ ] 0x9b72e0  CKPxParameterReport_GetClassID  [inline]
//   [ ] 0x9b72e8  CKPxParameterReport_IsKindOfClass  [inline]
//   [ ] 0x9b7308  KBase258C_IsKindOf  [inline]
//   [ ] 0x9b7320  KStub_Return12_9b7320  [inline]
//   [ ] 0x9b7328  KStub_Return150_9b7328  [inline]
//   [ ] 0x9b7330  KStub_Nop_9b7330  [inline]
//   [ ] 0x9b7338  KStub_Return12_9b7338  [inline]
//   [ ] 0x9b7340  KStub_Return153_9b7340  [inline]
//   [ ] 0x9b7348  KStub_Nop_9b7348  [inline]
#include "k2000/logic/CKPxParameterReport.h"

#include "crt/ppc_ops.h"

#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"

// 0x00232e28 CKPxParameterReport_Destructor
CKPxParameterReport::~CKPxParameterReport() {
    if (m_samples.m_pBlock != nullptr) Mem_FreeAligned16(m_samples.m_pBlock);  // 0x00052fb8
}

// 0x00232dd8 CKPxParameterReport_Destroy
void CKPxParameterReport::Destroy() {
    if (m_samples.m_pBlock != nullptr) Mem_FreeAligned16(m_samples.m_pBlock);
    m_samples.m_ui32NbUsedElt = 0;
    m_samples.m_pBlock = nullptr;
}

// 0x00232c30 CKPxParameterReport_Load. BUG(original): the block a previous Load made is not freed.
int32_t CKPxParameterReport::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    m_samples.m_ui32NbElt = 1;
    m_samples.m_pBlock = static_cast<SSample*>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(SSample))));  // 0x58
    ReadU16LE(file, &m_ui16WindowSize);
    for (CVector3& average : m_averages) average = CVector3{0.0f, 0.0f, 0.0f};  // 0x00c50d64
    m_ui16Oldest = 0;
    m_fTotalWeight = 0.0f;
    m_ui16Newest = 0;
    return 1;
}

// Not ported: 0x00232470 CKPxParameterReport_AddSampleToSlidingWindow_maybe. Its only caller is
// CKPxBody_RecordSampleAndUpdateShapes_maybe 0x218790 (CKPxBody is not ported; no game file holds one).

// 0x00232470 CKPxParameterReport_AddSampleToSlidingWindow_maybe: the averages turned back into sums (times the total
// weight); when the window is full (`next` is the oldest slot) the oldest sample is taken out (the oldest slot moves on,
// wrapping at the window size); the sample at the newest slot (the one just written) is added, the newest slot becomes
// `next`; the sums divided by the new total weight unless it is 0.
void CKPxParameterReport::AddSampleToSlidingWindow(const uint16_t* next) {
    const float total = m_fTotalWeight;
    for (uint32_t i = 0; i < 7; ++i) {
        CVector3& a = m_averages[i];
        const float x = total * a.x;
        const float z = total * a.z;
        const float y = total * a.y;
        a.x = x;
        a.z = z;
        a.y = y;
    }
    if (m_ui16Oldest == *next) {
        const SSample& oldest = m_samples.m_pBlock[m_ui16Oldest];
        for (uint32_t i = 0; i < 7; ++i) {
            CVector3& a = m_averages[i];
            const float w = -oldest.m_fWeight;
            const float z = ppc::fmadds(w, oldest.m_values[i].z, a.z);
            const float x = ppc::fmadds(w, oldest.m_values[i].x, a.x);
            const float y = ppc::fmadds(w, oldest.m_values[i].y, a.y);
            a.z = z;
            a.x = x;
            a.y = y;
        }
        const uint16_t moved = static_cast<uint16_t>(m_ui16Oldest + 1);
        m_ui16Oldest = m_ui16WindowSize > moved ? moved : 0;
        m_fTotalWeight = m_fTotalWeight - oldest.m_fWeight;
    }
    const SSample& newest = m_samples.m_pBlock[m_ui16Newest];
    for (uint32_t i = 0; i < 7; ++i) {
        CVector3& a = m_averages[i];
        const float w = newest.m_fWeight;
        const float x = ppc::fmadds(w, newest.m_values[i].x, a.x);
        const float z = ppc::fmadds(w, newest.m_values[i].z, a.z);
        const float y = ppc::fmadds(w, newest.m_values[i].y, a.y);
        a.x = x;
        a.z = z;
        a.y = y;
    }
    m_ui16Newest = *next;
    const float weight = m_fTotalWeight + newest.m_fWeight;
    m_fTotalWeight = weight;
    if (weight == 0.0f) return;
    for (uint32_t i = 0; i < 7; ++i) {
        CVector3& a = m_averages[i];
        const float inverse = 1.0f / m_fTotalWeight;
        const float z = inverse * a.z;
        const float x = inverse * a.x;
        const float y = inverse * a.y;
        a.z = z;
        a.x = x;
        a.y = y;
    }
}
