// CKOutputAnchor.cpp - reconstructed original translation unit 0x2044a0-0x2050c0 (GAME_TOC1, main_toc1), 21 functions, 21 live.
// Primary class: CKOutputAnchor  key 0x618c  category Logic  size 0x18  vtable 0xb1f150
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x2044a0  CKOutputAnchor_Delete
//   [x] 0x2044f0  CKOutputAnchor_vf50
//   [ ] 0x204500  RegisterCKOutputAnchorClass
//   [ ] 0x204588  _GLOBAL__D_204588
//   [ ] 0x204598  _GLOBAL__I_204598
//   [x] 0x2045a8  CKOutputAnchor_Load
//   [ ] 0x204760  CKOutputAnchor_Save
//   [x] 0x204788  CKOutputAnchor_RecursiveRegistration
//   [x] 0x2047b0  CKOutputAnchor_Destroy
//   [x] 0x204810  CKOutputAnchor_Destructor_2_maybe
//   [x] 0x204880  CKOutputAnchor_Construct
//   [x] 0x2048e0  CKOutputAnchor_Construct_2
//   [x] 0x204940  CKOutputAnchor_DeleteArray
//   [x] 0x2049e8  CKOutputAnchor_PropagateValue_maybe
//   [x] 0x204a88  CKOutputAnchor_DisconnectAll_maybe
//   [x] 0x204b80  CKOutputAnchor_DeletingDestructor
//   [x] 0x204bf8  CKOutputAnchor_Destructor
//   [x] 0x204c68  CKOutputAnchor_DisconnectInput
//   [x] 0x204e00  CKOutputAnchor_ConnectInput
//   [x] 0x204f68  CKOutputAnchor_CreateArray
//   [x] 0x205050  CKOutputAnchor_Create
//
//   [ ] 0x9b16e8  CKOutputAnchor_IsKindOfClass  [inline]
//   [ ] 0x9b1710  CKOutputAnchor_GetClassType  [inline]
//   [ ] 0x9b1718  CKOutputAnchor_GetClassID  [inline]
#include "k2000/logic/CKOutputAnchor.h"

#include "k2000/io/IKFile.h"
#include "k2000/logic/input/CKInputAnchor.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/Engine.h"
#include "k2000/services/CKSrvInput.h"

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

// 0x00204bf8 CKOutputAnchor_Destructor
CKOutputAnchor::~CKOutputAnchor() {
    if (m_vLinks.m_pBlock != nullptr) Mem_FreeAligned16(m_vLinks.m_pBlock);
    m_vLinks.m_ui32NbUsedElt = 0;
    m_vLinks.m_pBlock = nullptr;
}

// 0x002047b0 CKOutputAnchor_Destroy: the base's (0x205218, nothing), then the link block freed (the capacity kept).
void CKOutputAnchor::Destroy() {
    KBase610C::Destroy();
    if (m_vLinks.m_pBlock != nullptr) {
        Mem_FreeAligned16(m_vLinks.m_pBlock);
        m_vLinks.m_pBlock = nullptr;
    }
    m_vLinks.m_ui32NbUsedElt = 0;
    m_vLinks.m_pBlock = nullptr;
}

// 0x00204a88 CKOutputAnchor_DisconnectAll_maybe: while links remain, the first one unlinked here (vt+0x64) and, when
// that succeeds, this anchor unlinked there (its vt+0x64); when both succeed the input service's link count (+0x10)
// drops by one. BUG(original): a first link whose removal fails is tried again forever (cannot happen: every link
// was added through Connect, which checks the class).
void CKOutputAnchor::DisconnectAll() {
    CKSrvInput* service = static_cast<CKSrvInput*>(g_pEngine->m_srvInput);
    while (m_vLinks.m_ui32NbUsedElt != 0) {
        KBase610C* link = static_cast<KBase610C*>(m_vLinks.m_pBlock[0]);
        if (Disconnect(link) == 0) continue;
        if (link->Disconnect(this) == 0) continue;
        service->m_unk10 -= 1;
    }
}

// 0x00204c68 CKOutputAnchor_DisconnectInput: 0 when `other` is not an input anchor (0x614c). Else, when it is linked,
// the last link moves into its slot and the block shrinks by one when the capacity exceeds the count (to one element
// at 0); 1 whether it was linked or not.
uint8_t CKOutputAnchor::Disconnect(KBase610C* other) {
    if (static_cast<uint8_t>(other->IsKindOfClass(0x614c)) == 0) return 0;
    const uint32_t count = m_vLinks.m_ui32NbUsedElt;
    if (count == 0) return 1;
    uint32_t i = 0;
    while (m_vLinks.m_pBlock[i] != other) {
        if (++i == count) return 1;
    }
    const uint32_t last = count - 1;
    m_vLinks.m_ui32NbUsedElt = last;
    if (last != i) m_vLinks.m_pBlock[i] = m_vLinks.m_pBlock[last];
    const uint32_t capacity = m_vLinks.m_ui32NbElt - 1;
    if (static_cast<int32_t>(capacity) < static_cast<int32_t>(m_vLinks.m_ui32NbUsedElt)) return 1;
    if (capacity == 0) {
        m_vLinks.m_pBlock = static_cast<IKSerializable**>(
            Mem_ReallocAligned16(m_vLinks.m_pBlock, static_cast<uint32_t>(sizeof(IKSerializable*))));
        m_vLinks.m_ui32NbElt = 1;
    } else {
        m_vLinks.m_pBlock = static_cast<IKSerializable**>(
            Mem_ReallocAligned16(m_vLinks.m_pBlock, capacity * static_cast<uint32_t>(sizeof(IKSerializable*))));
        m_vLinks.m_ui32NbElt = capacity;
    }
    return 1;
}

// 0x00204e00 CKOutputAnchor_ConnectInput: 0 when `other` is not an input anchor (0x614c) or already linked; else
// appended (the block grows by one when full) and 1.
uint8_t CKOutputAnchor::Connect(KBase610C* other) {
    if (static_cast<uint8_t>(other->IsKindOfClass(0x614c)) == 0) return 0;
    for (uint32_t i = 0; i < m_vLinks.m_ui32NbUsedElt; ++i)
        if (m_vLinks.m_pBlock[i] == other) return 0;
    if (m_vLinks.m_ui32NbElt == m_vLinks.m_ui32NbUsedElt) {
        uint32_t capacity = m_vLinks.m_ui32NbElt + 1;
        if (capacity == 0) capacity = 1;
        m_vLinks.m_pBlock = static_cast<IKSerializable**>(
            Mem_ReallocAligned16(m_vLinks.m_pBlock, capacity * static_cast<uint32_t>(sizeof(IKSerializable*))));
        m_vLinks.m_ui32NbElt = capacity;
    }
    m_vLinks.m_pBlock[m_vLinks.m_ui32NbUsedElt] = other;
    m_vLinks.m_ui32NbUsedElt += 1;
    return 1;
}
