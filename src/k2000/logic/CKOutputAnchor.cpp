// CKOutputAnchor.cpp - reconstructed original translation unit 0x2044a0-0x2050c0 (GAME_TOC1, main_toc1), 21 functions, 21 live.
// Primary class: CKOutputAnchor  key 0x618c  category Logic  size 0x18  vtable 0xb1f150
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x2044a0  CKOutputAnchor_Delete
//   [ ] 0x2044f0  CKOutputAnchor_vf50
//   [ ] 0x204500  RegisterCKOutputAnchorClass
//   [ ] 0x204588  _GLOBAL__D_204588
//   [ ] 0x204598  _GLOBAL__I_204598
//   [x] 0x2045a8  CKOutputAnchor_Load
//   [ ] 0x204760  CKOutputAnchor_Save
//   [ ] 0x204788  CKOutputAnchor_RecursiveRegistration
//   [ ] 0x2047b0  CKOutputAnchor_Destroy
//   [ ] 0x204810  CKOutputAnchor_Destructor_2_maybe
//   [x] 0x204880  CKOutputAnchor_Construct
//   [ ] 0x2048e0  CKOutputAnchor_Construct_2
//   [x] 0x204940  CKOutputAnchor_DeleteArray
//   [x] 0x2049e8  CKOutputAnchor_PropagateValue_maybe
//   [ ] 0x204a88  CKOutputAnchor_DisconnectAll_maybe
//   [ ] 0x204b80  CKOutputAnchor_DeletingDestructor
//   [ ] 0x204bf8  CKOutputAnchor_Destructor
//   [ ] 0x204c68  CKOutputAnchor_DisconnectInput
//   [ ] 0x204e00  CKOutputAnchor_ConnectInput
//   [x] 0x204f68  CKOutputAnchor_CreateArray
//   [x] 0x205050  CKOutputAnchor_Create
//
//   [ ] 0x9b16e8  CKOutputAnchor_IsKindOfClass  [inline]
//   [ ] 0x9b1710  CKOutputAnchor_GetClassType  [inline]
//   [ ] 0x9b1718  CKOutputAnchor_GetClassID  [inline]
#include "k2000/logic/CKOutputAnchor.h"

#include "k2000/io/IKFile.h"
#include "k2000/logic/input/CKInputAnchor.h"

// 0x00204880 CKOutputAnchor_Construct
CKOutputAnchor::CKOutputAnchor() {
    m_vLinks.m_pBlock = nullptr;
    m_vLinks.m_ui32NbElt = 1;
    m_vLinks.m_ui32NbUsedElt = 0;
}

// 0x002045a8 CKOutputAnchor_Load
int32_t CKOutputAnchor::Load(IKFile* file, int32_t type) {
    KBase610C::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    KAnchor_LoadRefVector(file, &m_vLinks);
    return 1;
}

// 0x002049e8 CKOutputAnchor_PropagateValue_maybe: a changed value goes to every linked input anchor (the
// value read once; the links and their count read again on each step).
void CKOutputAnchor::PropagateValue() {
    if (m_unk09 == 0) return;
    const uint8_t value = m_unk08;
    for (uint32_t i = 0; i < m_vLinks.m_ui32NbUsedElt; ++i)
        static_cast<CKInputAnchor*>(m_vLinks.m_pBlock[i])->UpdateFromSource(this, value);
}
