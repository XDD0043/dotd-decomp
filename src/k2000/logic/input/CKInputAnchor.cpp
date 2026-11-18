// CKInputAnchor.cpp - reconstructed original translation unit 0x203760-0x2044a0 (GAME_TOC1, main_toc1), 22 functions, 22 live.
// Primary class: CKInputAnchor  key 0x614c  category Logic  size 0x18  vtable 0xb1f0e0
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x203760  CKInputAnchor_Delete
//   [x] 0x2037b0  CKInputAnchor_vf50
//   [x] 0x2037c0  CKInputAnchor_PropagateValue_maybe
//   [ ] 0x203818  RegisterCKInputAnchorClass
//   [ ] 0x2038a0  _GLOBAL__D_2038a0
//   [ ] 0x2038b0  _GLOBAL__I_2038b0
//   [x] 0x2038c0  CKInputAnchor_Load
//   [ ] 0x203a78  CKInputAnchor_Save
//   [x] 0x203aa0  CKInputAnchor_RecursiveRegistration  (the base's vt+0x24, nothing)
//   [x] 0x203ac8  CKInputAnchor_Destroy
//   [x] 0x203b28  CKInputAnchor_DeletingDestructor  (C++ deleting destructor)
//   [x] 0x203ba0  CKInputAnchor_Construct
//   [x] 0x203c00  CKInputAnchor_Construct_2  (= Construct)
//   [x] 0x203c60  CKInputAnchor_DeleteArray
//   [x] 0x203d08  CKInputAnchor_DisconnectAll_maybe
//   [x] 0x203e00  CKInputAnchor_UpdateFromSource_maybe
//   [x] 0x203f68  CKInputAnchor_Destructor
//   [x] 0x203fd8  CKInputAnchor_Destructor_2_maybe  (= Destructor)
//   [x] 0x204048  CKInputAnchor_DisconnectOutput
//   [x] 0x2041e0  CKInputAnchor_ConnectOutput
//   [x] 0x204348  CKInputAnchor_CreateArray
//   [x] 0x204430  CKInputAnchor_Create
//
//   [ ] 0x9b16b0  CKInputAnchor_IsKindOfClass  [inline]
//   [ ] 0x9b16d8  CKInputAnchor_GetClassType  [inline]
//   [ ] 0x9b16e0  CKInputAnchor_GetClassID  [inline]
#include "k2000/logic/input/CKInputAnchor.h"

#include "k2000/io/IKFile.h"
#include "k2000/logic/KBase60CC.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/Engine.h"
#include "k2000/services/CKSrvInput.h"

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

// 0x00203f68 CKInputAnchor_Destructor
CKInputAnchor::~CKInputAnchor() {
    if (m_vLinks.m_pBlock != nullptr) Mem_FreeAligned16(m_vLinks.m_pBlock);
    m_vLinks.m_ui32NbUsedElt = 0;
    m_vLinks.m_pBlock = nullptr;
}

// 0x00203ac8 CKInputAnchor_Destroy: the base's (0x205218, nothing), then the link block freed (the capacity kept).
void CKInputAnchor::Destroy() {
    KBase610C::Destroy();
    if (m_vLinks.m_pBlock != nullptr) {
        Mem_FreeAligned16(m_vLinks.m_pBlock);
        m_vLinks.m_pBlock = nullptr;
    }
    m_vLinks.m_ui32NbUsedElt = 0;
    m_vLinks.m_pBlock = nullptr;
}

// 0x00203d08 CKInputAnchor_DisconnectAll_maybe: while links remain, the first one unlinked here (vt+0x64) and, when that
// succeeds, this anchor unlinked there (its vt+0x64); when both succeed the input service's link count (+0x10) drops by
// one. BUG(original): a first link whose removal fails is tried again forever (cannot happen: every link was added
// through Connect, which checks the class).
void CKInputAnchor::DisconnectAll() {
    CKSrvInput* service = static_cast<CKSrvInput*>(g_pEngine->m_srvInput);
    while (m_vLinks.m_ui32NbUsedElt != 0) {
        KBase610C* link = static_cast<KBase610C*>(m_vLinks.m_pBlock[0]);
        if (Disconnect(link) == 0) continue;
        if (link->Disconnect(this) == 0) continue;
        service->m_unk10 -= 1;
    }
}

// 0x00204048 CKInputAnchor_DisconnectOutput: 0 when `other` is not an output anchor (0x618c). Else, when it is linked,
// the last link moves into its slot and the block shrinks by one when the capacity exceeds the count (to one element at
// 0); 1 whether it was linked or not.
uint8_t CKInputAnchor::Disconnect(KBase610C* other) {
    if (static_cast<uint8_t>(other->IsKindOfClass(0x618c)) == 0) return 0;
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

// 0x002041e0 CKInputAnchor_ConnectOutput: 0 when `other` is not an output anchor (0x618c) or already linked; else
// appended (the block grows by one when full) and 1.
uint8_t CKInputAnchor::Connect(KBase610C* other) {
    if (static_cast<uint8_t>(other->IsKindOfClass(0x618c)) == 0) return 0;
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
