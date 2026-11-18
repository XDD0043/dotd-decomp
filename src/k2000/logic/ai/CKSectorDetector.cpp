// CKSectorDetector.cpp - reconstructed original translation unit 0x1a8120-0x1a8608 (GAME_TOC1, main_toc1), 10 functions, 10 live.
// Primary class: CKSectorDetector  key 0x274c  category Logic  size 0xc  vtable 0xb1c350
// Other owners: CKSrvDetect (1), DetectorList (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1a8120  CKSectorDetector_PostLoad  (returns 1: the default slot)
//   [ ] 0x1a8128  RegisterCKSectorDetectorClass
//   [ ] 0x1a81a0  _GLOBAL__I_1a81a0
//   [x] 0x1a81b0  CKSectorDetector_Destroy
//   [x] 0x1a81f8  CKSectorDetector_Load
//   [x] 0x1a8380  CKSectorDetector_DeleteArray
//   [x] 0x1a8428  CKSectorDetector_Create
//   [x] 0x1a8460  CKSrvDetect_RunDetectors_maybe
//   [x] 0x1a8518  DetectorList_ClearDetectionFlags_maybe
//   [x] 0x1a8570  CKSectorDetector_CreateArray
//
//   [ ] 0x9aaeb0  CKSectorDetector_GetClassType  [inline]
//   [ ] 0x9aaeb8  CKSectorDetector_GetClassID  [inline]
//   [ ] 0x9aaec0  CKSectorDetector_IsKindOfClass  [inline]
//   [ ] 0x9aaee0  CKSectorDetector_Destructor  [inline]
//   [ ] 0x9aaef8  CKSectorDetector_DeletingDestructor  [inline]
#include "k2000/logic/ai/CKSectorDetector.h"

#include "k2000/io/IKFile.h"
#include "k2000/logic/ai/CKDetectorBase.h"
#include "k2000/memory/Mem.h"

// 0x001a8460 CKSrvDetect_RunDetectors_maybe
void CKSectorDetector::RunDetectors() {
    for (uint32_t i = 0; i != m_ui32NbDetector; ++i) {
        CKDetectorBase* detector = static_cast<CKDetectorBase*>(m_apDetector[i]);
        const uint32_t data = detector->m_baData;
        if (((data >> 8) & 1) != 0 || (data & 0x10) == 0) continue;
        detector->Detect();  // vt+0x50
    }
}

// 0x001a8518 DetectorList_ClearDetectionFlags_maybe
void CKSectorDetector::ClearDetectionFlags() {
    for (uint32_t i = 0; i < m_ui32NbDetector; ++i) {
        CKDetectorBase* detector = static_cast<CKDetectorBase*>(m_apDetector[i]);
        detector->m_baData &= 0xfffffff1u;
    }
}

// 0x001a81f8 CKSectorDetector_Load (XXL2 reads the count, then the array, the same way).
int32_t CKSectorDetector::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadU32LE(file, &m_ui32NbDetector);
    if (m_ui32NbDetector == 0) {
        m_apDetector = nullptr;
        return 1;
    }
    m_apDetector = static_cast<IKSerializable**>(
        Mem_AllocAligned16(m_ui32NbDetector * static_cast<uint32_t>(sizeof(IKSerializable*))));
    IKFile_ReadObjectRefArray(file, m_apDetector, m_ui32NbDetector);
    return 1;
}

// 0x001a81b0 CKSectorDetector_Destroy
void CKSectorDetector::Destroy() {
    if (m_apDetector != nullptr) {
        Mem_FreeAligned16(m_apDetector);
        m_apDetector = nullptr;
    }
}
