// CKPxConstraintReport.cpp - reconstructed original translation unit 0x2317a8-0x2322b0 (GAME_TOC1, main_toc1), 16 functions, 14 live.
// Primary class: CKPxConstraintReport  key 0x564c  category Logic  size 0x114  vtable 0xb20740
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x2317a8  CKPxConstraintReport_Delete
//   [ ] 0x2317f8  CKPxConstraintReport_Construct  [dead]
//   [ ] 0x231850  RegisterCKPxConstraintReportClass
//   [ ] 0x2318c8  _GLOBAL__I_2318c8
//   [x] 0x2318d8  CKPxConstraintReport_DeleteArray
//   [ ] 0x231978  CKPxConstraintReport_Construct_2  [dead]
//   [ ] 0x2319d0  CKPxConstraintReport_Save
//   [x] 0x2319d8  CKPxConstraintReport_RecursiveRegistration  (returns 1, registers nothing: the default)
//   [x] 0x2319e0  CKPxConstraintReport_SnapshotConstraintsEveryN_maybe  (SnapshotConstraintsEveryN)
//   [x] 0x231ce8  CKPxConstraintReport_CreateArray
//   [x] 0x231db8  CKPxConstraintReport_Create
//   [x] 0x231e38  CKPxConstraintReport_Destroy
//   [x] 0x231ef0  CKPxConstraintReport_Load
//   [x] 0x2320a8  CKPxConstraintReport_DeletingDestructor  (the destructor; delete)
//   [x] 0x232160  CKPxConstraintReport_Destructor
//   [x] 0x232208  CKPxConstraintReport_Destructor_2  (the destructor)
//
//   [ ] 0x9b72a8  CKPxConstraintReport_GetClassType  [inline]
//   [ ] 0x9b72b0  CKPxConstraintReport_GetClassID  [inline]
//   [ ] 0x9b72b8  CKPxConstraintReport_IsKindOfClass  [inline]
#include "k2000/logic/CKPxConstraintReport.h"

#include "k2000/io/IKFile.h"
#include "k2000/logic/CKPxBody.h"
#include "k2000/misc/Mat4.h"
#include "k2000/memory/Mem.h"

// Inlined in 0x00231db8 CKPxConstraintReport_Create.
CKPxConstraintReport::CKPxConstraintReport() {
    m_current.m_pBlock = nullptr;
    m_current.m_ui32NbElt = 1;
    m_current.m_ui32NbUsedElt = 0;
    for (TVector<SConstraint, 1>& slot : m_history) {
        slot.m_ui32NbElt = 1;
        slot.m_pBlock = nullptr;
        slot.m_ui32NbUsedElt = 0;
    }
}

// 0x00232160 CKPxConstraintReport_Destructor
CKPxConstraintReport::~CKPxConstraintReport() {
    for (int32_t i = 19; i >= 0; --i) {
        if (m_history[i].m_pBlock != nullptr) Mem_FreeAligned16(m_history[i].m_pBlock);  // 0x00052fb8
    }
    if (m_current.m_pBlock != nullptr) Mem_FreeAligned16(m_current.m_pBlock);
}

// 0x00231e38 CKPxConstraintReport_Destroy
void CKPxConstraintReport::Destroy() {
    if (m_current.m_pBlock != nullptr) Mem_FreeAligned16(m_current.m_pBlock);
    m_current.m_ui32NbUsedElt = 0;
    m_current.m_pBlock = nullptr;
    for (TVector<SConstraint, 1>& slot : m_history) {
        if (slot.m_pBlock != nullptr) Mem_FreeAligned16(slot.m_pBlock);
        slot.m_ui32NbUsedElt = 0;
        slot.m_pBlock = nullptr;
    }
}

// 0x00231ef0 CKPxConstraintReport_Load. BUG(original): the blocks a previous Load made are not freed.
int32_t CKPxConstraintReport::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadU16LE(file, &m_ui16Flags);
    m_current.m_ui32NbElt = 1;
    m_current.m_pBlock = static_cast<SConstraint*>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(SConstraint))));
    m_ui16NbCurrent = 0;
    for (TVector<SConstraint, 1>& slot : m_history) {
        slot.m_ui32NbElt = 1;
        slot.m_pBlock = static_cast<SConstraint*>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(SConstraint))));
    }
    ReadU16LE(file, &m_ui16HistorySize);
    ReadU16LE(file, &m_ui16Period);
    m_ui16Read = 0;
    m_ui16StepCounter = 0;
    m_ui16Write = 0;
    return 1;
}

// Not ported: 0x002319e0 CKPxConstraintReport_SnapshotConstraintsEveryN_maybe. Its only caller is CKSrvPhysics's body
// loop (CKSrvPhysics_IntegrateBodies_maybe 0x2141b8, a STUB: no CKPxBody in any game file), and it reads each body's
// matrix (+0xf0) of CKPxBody, which is not ported.

// 0x002319e0 CKPxConstraintReport_SnapshotConstraintsEveryN_maybe: while recording (0x200) with a history, every
// m_ui16Period steps the current constraints copied into the ring's write slot (grown to fit), their points and
// directions turned through each body's world matrix (Mat4_TransformVectorsInline, in place); the write slot moves on
// (wrapping at the history size), pushing the read slot on when it catches up.
void CKPxConstraintReport::SnapshotConstraintsEveryN() {
    if ((m_ui16Flags & 0x200) == 0) return;
    if (m_ui16HistorySize == 0) return;
    ++m_ui16StepCounter;
    if (m_ui16Period > m_ui16StepCounter) return;
    m_ui16StepCounter = 0;
    TVector<SConstraint, 1>& slot = m_history[m_ui16Write];
    const uint32_t count = m_ui16NbCurrent;
    if (slot.m_ui32NbElt < count) {
        uint32_t capacity = count + 1;
        if (capacity == 0) capacity = 1;
        // The original masks the size with ~0x3f (its 0x40-byte records): a no-op, left out for the native record size.
        slot.m_pBlock = static_cast<SConstraint*>(
            Mem_ReallocAligned16(slot.m_pBlock, capacity * static_cast<uint32_t>(sizeof(SConstraint))));  // 0x53190
        slot.m_ui32NbElt = capacity;
    }
    slot.m_ui32NbUsedElt = count;
    for (uint32_t i = 0; i < m_ui16NbCurrent; ++i) {
        const SConstraint& from = m_current.m_pBlock[i];
        SConstraint& to = slot.m_pBlock[i];
        to.m_pBodyA = from.m_pBodyA;
        to.m_vPointA = from.m_vPointA;
        to.m_pBodyB = from.m_pBodyB;
        to.m_vPointB = from.m_vPointB;
        to.m_vDirA = from.m_vDirA;
        to.m_unk2c = from.m_unk2c;  // lfs / stfs
        to.m_vDirB = from.m_vDirB;
        to.m_unk3c = from.m_unk3c;
        if (to.m_pBodyA != nullptr) {
            const CMatrix34* world = static_cast<CKPxBody*>(to.m_pBodyA)->m_pWorldMatrix;
            Mat4_TransformVectorsInline(world, &to.m_vPointA, &to.m_vPointA, 1);  // 0x00240520
            Mat4_TransformVectorsInline(static_cast<CKPxBody*>(to.m_pBodyA)->m_pWorldMatrix, &to.m_vDirA, &to.m_vDirA, 1);
        }
        if (to.m_pBodyB != nullptr) {
            const CMatrix34* world = static_cast<CKPxBody*>(to.m_pBodyB)->m_pWorldMatrix;
            Mat4_TransformVectorsInline(world, &to.m_vPointB, &to.m_vPointB, 1);
            Mat4_TransformVectorsInline(static_cast<CKPxBody*>(to.m_pBodyB)->m_pWorldMatrix, &to.m_vDirB, &to.m_vDirB, 1);
        }
    }
    ++m_ui16Write;
    if (m_ui16Write >= m_ui16HistorySize) m_ui16Write = 0;
    if (m_ui16Write != m_ui16Read) return;
    ++m_ui16Read;
    if (m_ui16Read >= m_ui16HistorySize) m_ui16Read = 0;
}
