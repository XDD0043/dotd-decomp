// Reconstructed original translation unit: 0x724e0-0x72a88 (GAME_TOC1, main_toc1), 12 functions, 3 live.
// Primary owner: FlashWidgetBinding (not a registered class)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x724e0  FlashWidgetBinding_GetElement2dAt_maybe  [dead]
//   [ ] 0x724f8  FlashWidgetBinding_GetAtomicAt_maybe  [dead]
//   [ ] 0x72518  FlashWidgetBinding_GetElement2dCount_maybe  [dead]
//   [ ] 0x72520  FlashWidgetBinding_GetAtomicCount_maybe  [dead]
//   [x] 0x72528  FlashWidgetBinding_SetHidden_maybe
//   [ ] 0x72688  FlashWidgetBinding_RemoveElement2d_maybe  [dead]
//   [ ] 0x72738  FlashWidgetBinding_GetElement2dFlagBit0_maybe  [dead]
//   [ ] 0x727b8  FlashWidgetBinding_GetElement2dFlags_maybe  [dead]
//   [x] 0x72830  FlashWidgetBinding_SetElement2dFlags_maybe
//   [ ] 0x728a8  FlashWidgetBinding_RemoveAtomic_maybe  [dead]
//   [ ] 0x72988  FlashWidgetBinding_GetAtomicFlags_maybe  [dead]
//   [x] 0x72a08  FlashWidgetBinding_SetAtomicFlags_maybe
//
// The "FlashWidgetBinding" functions are CFlashHotSpot's (XXL2 CFlashHotSpot: HideHotSpotHierarchy,
// SetObjectFlags); declared in CFlashHotSpot.h.
#include "k2000/graphical/ui/CFlashHotSpot.h"

#include "k2000/scenegraph/CSGLeaf.h"

// 0x00072528 FlashWidgetBinding_SetHidden_maybe (XXL2 HideHotSpotHierarchy): the 2D objects disabled
// (vt+0x68) while hidden, enabled (vt+0x64) otherwise; the 3D nodes' hidden bit (CSGLeaf flags 0x4) set to
// the argument.
void CFlashHotSpot::HideHotSpotHierarchy(uint8_t hide) {
    m_bIsHidden = hide;
    for (uint32_t i = 0; i < m_vp2dObject.m_ui32NbUsedElt; ++i) {
        IKNode2d* node = m_vp2dObject.m_pBlock[i].m_pNode;
        if (m_bIsHidden != 0) {
            node->Disable();
        } else {
            node->Enable();
        }
    }
    const uint32_t hiddenBit = (static_cast<uint32_t>(hide) << 2) & 0x3fc;  // rlwinm 2,22,29
    for (uint32_t i = 0; i < m_vp3dNodeList.m_ui32NbUsedElt; ++i) {
        CSGLeaf* node = static_cast<CSGLeaf*>(m_vp3dNodeList.m_pBlock[i].m_pNode);
        node->m_sgProperties = (node->m_sgProperties & ~0x4u) | hiddenBit;
    }
}

// 0x00072830 FlashWidgetBinding_SetElement2dFlags_maybe (XXL2 SetObjectFlags(IKNode2d*, UInt32)): the
// flags of the object's entry, searched from the last one.
void CFlashHotSpot::SetObjectFlags(IKNode2d* node, uint32_t flags) {
    for (uint32_t i = m_vp2dObject.m_ui32NbUsedElt; i != 0;) {
        --i;
        if (m_vp2dObject.m_pBlock[i].m_pNode == node) {
            m_vp2dObject.m_pBlock[i].m_ui32Flags = flags;
            return;
        }
    }
    // BUG(original): not found, the flags go to the word before the list's block (entry -1's flags).
    reinterpret_cast<uint32_t*>(m_vp2dObject.m_pBlock)[-1] = flags;
}

// 0x00072a08 FlashWidgetBinding_SetAtomicFlags_maybe (XXL2 SetObjectFlags(CNode*, UInt32)).
void CFlashHotSpot::SetObjectFlags(IKSerializable* node, uint32_t flags) {
    for (uint32_t i = m_vp3dNodeList.m_ui32NbUsedElt; i != 0;) {
        --i;
        if (m_vp3dNodeList.m_pBlock[i].m_pNode == node) {
            m_vp3dNodeList.m_pBlock[i].m_ui32Flags = flags;
            return;
        }
    }
    // BUG(original): not found, the flags go to the word before the list's block (entry -1's flags).
    reinterpret_cast<uint32_t*>(m_vp3dNodeList.m_pBlock)[-1] = flags;
}
