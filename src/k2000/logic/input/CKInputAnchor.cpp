// CKInputAnchor.cpp - reconstructed original translation unit 0x203760-0x2044a0 (GAME_TOC1, main_toc1), 22 functions, 22 live.
// Primary class: CKInputAnchor  key 0x614c  category Logic  size 0x18  vtable 0xb1f0e0
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x203760  CKInputAnchor_Delete
//   [ ] 0x2037b0  CKInputAnchor_vf50
//   [x] 0x2037c0  CKInputAnchor_PropagateValue_maybe
//   [ ] 0x203818  RegisterCKInputAnchorClass
//   [ ] 0x2038a0  _GLOBAL__D_2038a0
//   [ ] 0x2038b0  _GLOBAL__I_2038b0
//   [x] 0x2038c0  CKInputAnchor_Load
//   [ ] 0x203a78  CKInputAnchor_Save
//   [ ] 0x203aa0  CKInputAnchor_RecursiveRegistration
//   [ ] 0x203ac8  CKInputAnchor_Destroy
//   [ ] 0x203b28  CKInputAnchor_DeletingDestructor
//   [x] 0x203ba0  CKInputAnchor_Construct
//   [ ] 0x203c00  CKInputAnchor_Construct_2
//   [x] 0x203c60  CKInputAnchor_DeleteArray
//   [ ] 0x203d08  CKInputAnchor_DisconnectAll_maybe
//   [x] 0x203e00  CKInputAnchor_UpdateFromSource_maybe
//   [ ] 0x203f68  CKInputAnchor_Destructor
//   [ ] 0x203fd8  CKInputAnchor_Destructor_2_maybe
//   [ ] 0x204048  CKInputAnchor_DisconnectOutput
//   [ ] 0x2041e0  CKInputAnchor_ConnectOutput
//   [x] 0x204348  CKInputAnchor_CreateArray
//   [x] 0x204430  CKInputAnchor_Create
//
//   [ ] 0x9b16b0  CKInputAnchor_IsKindOfClass  [inline]
//   [ ] 0x9b16d8  CKInputAnchor_GetClassType  [inline]
//   [ ] 0x9b16e0  CKInputAnchor_GetClassID  [inline]
#include "k2000/logic/input/CKInputAnchor.h"

#include "k2000/io/IKFile.h"
#include "k2000/logic/KBase60CC.h"

// 0x00203ba0 CKInputAnchor_Construct
CKInputAnchor::CKInputAnchor() {
    m_vLinks.m_pBlock = nullptr;
    m_vLinks.m_ui32NbElt = 1;
    m_vLinks.m_ui32NbUsedElt = 0;
}

// 0x002038c0 CKInputAnchor_Load
int32_t CKInputAnchor::Load(IKFile* file, int32_t type) {
    KBase610C::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    KAnchor_LoadRefVector(file, &m_vLinks);
    return 1;
}

// 0x002037c0 CKInputAnchor_PropagateValue_maybe: a changed value goes to the owning block's vt+0x64.
void CKInputAnchor::PropagateValue() {
    if (m_unk09 != 0) static_cast<KBase60CC*>(m_pBlock)->Evaluate(m_unk08);
}

// 0x00203e00 CKInputAnchor_UpdateFromSource_maybe. The loop count is the link count at entry; after a
// SetValue(1) the count is read again and, if it equals the index of the link found, SetValue(0) follows
// (as in the original: that index is always below the count unless SetValue changed the links).
void CKInputAnchor::UpdateFromSource(KBase610C* source, uint8_t value) {
    const uint32_t count = m_vLinks.m_ui32NbUsedElt;
    uint32_t i = 0;
    if (count != 0) {
        IKSerializable** links = m_vLinks.m_pBlock;
        if (value == 0) {
            for (; i < count; ++i) {
                KBase610C* link = static_cast<KBase610C*>(links[i]);
                if (link != source && link->m_unk08 != 0) goto found;
            }
        } else {
            for (; i < count; ++i) {
                KBase610C* link = static_cast<KBase610C*>(links[i]);
                if (link == source || link->m_unk08 != 0) goto found;
            }
        }
    }
    if (count != i) return;
    SetValue(0);  // vt+0x58
    return;
found:
    SetValue(1);
    if (m_vLinks.m_ui32NbUsedElt != i) return;
    SetValue(0);
}
