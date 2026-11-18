// CKLogicalBlock.cpp - reconstructed original translation unit 0x20fb08-0x210070 (GAME_TOC1, main_toc1), 11 functions, 11 live.
// Primary owner: CKLogicalBlock (not a registered class)
// Other owners: KBase640C (2)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x20fb08  CKLogicalBlock_640c_maybe_Load
//   [ ] 0x20fc40  CKLogicalBlock_640c_maybe_Save
//   [x] 0x20fc68  CKLogicalBlock_640c_maybe_LevelReset
//   [x] 0x20fc90  CKLogicalBlock_640c_maybe_ClearReferences
//   [x] 0x20fcb8  CKLogicalBlock_640c_maybe_DeletingDestructor
//   [x] 0x20fd00  CKLogicalBlock_640c_maybe_Destructor
//   [x] 0x20fd30  CKLogicalBlock_640c_maybe_BaseDestructor
//   [x] 0x20fd60  CKLogicalBlock_640c_maybe_Construct_2
//   [x] 0x20fd98  CKLogicalBlock_640c_maybe_Construct
//   [x] 0x20fdd0  KBase640C_vf60
//   [x] 0x20fe70  KBase640C_CollectAnchors_maybe
//
//   [ ] 0x9b1f80  CKLogicalBlock_640c_maybe_IsKindOf  [inline]
//   [ ] 0x9b1fa8  CKLogicalBlock_640c_maybe_GetClassGroup  [inline]
//   [ ] 0x9b1fb0  CKLogicalBlock_640c_maybe_GetClassId  [inline]
#include "k2000/misc/CKLogicalBlock.h"

#include "k2000/io/IKFile.h"

// 0x0020fb08 CKLogicalBlock_640c_maybe_Load: KBase60CC's, then the two input anchors and the output anchor.
int32_t CKLogicalBlock::Load(IKFile* file, int32_t type) {
    KBase60CC::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        IKFile_ReadObjectRefArray(file, reinterpret_cast<IKSerializable**>(m_pInputs), 2);
        IKFile_ReadRef(file, &m_pOutput);
    }
    return 1;
}

// 0x0020fdd0 KBase640C_vf60: DisconnectAll (vt+0x54) of the two input anchors, then of the output anchor.
void CKLogicalBlock::DisconnectAnchors() {
    m_pInputs[0]->DisconnectAll();
    m_pInputs[1]->DisconnectAll();
    m_pOutput->DisconnectAll();
}

// 0x0020fe70 KBase640C_CollectAnchors_maybe: the two input anchors and the output anchor appended (each append grows
// the block by one element when full, to one at a capacity of 0).
void CKLogicalBlock::CollectAnchors(TVector<KBase610C*, 1>* out) {
    KAnchor_PushBack(out, m_pInputs[0]);
    KAnchor_PushBack(out, m_pInputs[1]);
    KAnchor_PushBack(out, m_pOutput);
}
