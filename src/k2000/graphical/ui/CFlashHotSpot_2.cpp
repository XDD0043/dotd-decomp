// CFlashHotSpot_2.cpp - reconstructed original translation unit 0x72a88-0x73b10 (GAME_TOC1, main_toc1), 10 functions, 8 live.
// Primary class: CFlashHotSpot  key 0xc0d  category Graphical  size 0x40  vtable 0xb160e8
// Other owners: FlashWidgetBinding (4)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x72a88  CFlashHotSpot_Create
//   [x] 0x72ae8  CFlashHotSpot_Save
//   [x] 0x72af0  CFlashHotSpot_RecursiveRegistration
//   [x] 0x72af8  CFlashHotSpot_PostLoad
//   [x] 0x72c30  CFlashHotSpot_Destroy
//   [x] 0x72cc0  FlashWidgetBinding_SyncAtomics_maybe
//   [ ] 0x72f00  FlashWidgetBinding_AddAtomic_maybe  [dead]
//   [x] 0x73068  CFlashHotSpot_Load
//   [x] 0x735f0  FlashWidgetBinding_SyncElements2d_maybe
//   [ ] 0x73880  FlashWidgetBinding_AddElement2d_maybe  [dead]
//
//   [x] 0x998fb0  CFlashHotSpot_GetClassType  [inline]
//   [x] 0x998fb8  CFlashHotSpot_GetClassID  [inline]
//   [x] 0x998fc0  CFlashHotSpot_IsKindOfClass  [inline]
//   [x] 0x998fe0  CFlashHotSpot_Destructor  [inline]
//   [x] 0x999078  CFlashHotSpot_DeletingDestructor  [inline]
#include "k2000/graphical/ui/CFlashHotSpot.h"

#include <cstring>

#include "Renderware/rpprtstd/RpPrtStd.h"
#include "Renderware/rt2d/Rt2d.h"
#include "Renderware/rwcore/RwCamera.h"
#include "crt/ppc_ops.h"
#include "k2000/graphical/fx/CBillboard2d.h"
#include "k2000/graphical/ui/CKFlashUI.h"
#include "k2000/graphical/ui/CText2d.h"
#include "k2000/graphical/ui/CameraContextUi.h"
#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"
#include "k2000/scenegraph/CParticlesNodeFx.h"
#include "k2000/scenegraph/CSGLeaf.h"

namespace {
// One Read of count little-endian words, then each word byte-swapped (lwbrx after the Read).
uint32_t ReadWordsLE(IKFile* file, void* dst, uint32_t count) {
    uint8_t bytes[16];
    const uint32_t got = file->Read(bytes, 4 * count);
    for (uint32_t i = 0; i < count; ++i) {
        const uint8_t* b = bytes + 4 * i;
        const uint32_t word = static_cast<uint32_t>(b[0]) | (static_cast<uint32_t>(b[1]) << 8) |
                              (static_cast<uint32_t>(b[2]) << 16) | (static_cast<uint32_t>(b[3]) << 24);
        std::memcpy(static_cast<uint8_t*>(dst) + 4 * i, &word, 4);
    }
    return got;
}

// The TVector sizing both lists share: capacity = count (1 for an empty list), then the original's
// grow-by-2 branch, which cannot run right after the assignment.
template <class T>
void SizeList(TVector<T, 2>* list, uint32_t count) {
    const uint32_t elt = static_cast<uint32_t>(sizeof(T));
    if (count == 0) {
        list->m_ui32NbElt = 1;
        list->m_pBlock = static_cast<T*>(Mem_AllocAligned16(elt));
    } else {
        list->m_ui32NbElt = count;
        list->m_pBlock = static_cast<T*>(Mem_AllocAligned16(count * elt));
    }
    if (list->m_ui32NbElt < count) {
        const uint32_t capacity = (count & ~1u) + 2;
        if (capacity == 0) {
            list->m_pBlock = static_cast<T*>(Mem_ReallocAligned16(list->m_pBlock, 2 * elt));
            list->m_ui32NbElt = 2;
        } else {
            list->m_pBlock = static_cast<T*>(Mem_ReallocAligned16(list->m_pBlock, capacity * elt));
            list->m_ui32NbElt = capacity;
        }
    }
    list->m_ui32NbUsedElt = count;
}

// 0x00c50dfc: the white colour word (CColor 0xffffffff) PostLoad copies.
const uint8_t kColorWhite[4] = {0xff, 0xff, 0xff, 0xff};

// CSGLeaf::m_sgProperties bits the hot spot drives (meanings from the scene-graph users, _maybe).
constexpr uint32_t kSgHidden = 0x4;
constexpr uint32_t kSgFxActive_maybe = 0x400;
constexpr uint32_t kSgFxPending_maybe = 0x80000;

// The node's RpPrtStdEmitter (+0x58, bound by CParticlesNodeFx_PostLoad 0xe65f0): emission stopped
// (rpPRTSTDEMITTERFLAGEMIT cleared) or started (ACTIVE | EMIT set).
void StopEmitter(CParticlesNodeFx* fx) { fx->m_pRpPrtStdEmitter->flag &= ~rpPRTSTDEMITTERFLAGEMIT; }
void StartEmitter(CParticlesNodeFx* fx) {
    fx->m_pRpPrtStdEmitter->flag |= rpPRTSTDEMITTERFLAGACTIVE | rpPRTSTDEMITTERFLAGEMIT;
}
}  // namespace

// Inlined in 0x00072a88 CFlashHotSpot_Create, the stores in its order (the TVector constructors).
CFlashHotSpot::CFlashHotSpot() {
    m_vp3dNodeList.m_pBlock = nullptr;
    m_vp3dNodeList.m_ui32NbElt = 2;
    m_vp3dNodeList.m_ui32NbUsedElt = 0;
    m_vp2dObject.m_ui32NbElt = 2;
    m_vp2dObject.m_ui32NbUsedElt = 0;
    m_vp2dObject.m_pBlock = nullptr;
}

// 0x00998fe0 CFlashHotSpot_Destructor: the two TVector destructors.
CFlashHotSpot::~CFlashHotSpot() {
    if (m_vp2dObject.m_pBlock != nullptr) Mem_FreeAligned16(m_vp2dObject.m_pBlock);
    m_vp2dObject.m_ui32NbUsedElt = 0;
    m_vp2dObject.m_pBlock = nullptr;
    if (m_vp3dNodeList.m_pBlock != nullptr) Mem_FreeAligned16(m_vp3dNodeList.m_pBlock);
    m_vp3dNodeList.m_ui32NbUsedElt = 0;
    m_vp3dNodeList.m_pBlock = nullptr;
}

// 0x00072af8 CFlashHotSpot_PostLoad: the 2D objects disabled (vt+0x68), the 3D nodes hidden, the anchor
// reset.
int32_t CFlashHotSpot::PostLoad(int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    for (uint32_t i = 0; i < m_vp2dObject.m_ui32NbUsedElt; ++i) m_vp2dObject.m_pBlock[i].m_pNode->Disable();
    for (uint32_t i = 0; i < m_vp3dNodeList.m_ui32NbUsedElt; ++i) {
        CSGLeaf* node = static_cast<CSGLeaf*>(m_vp3dNodeList.m_pBlock[i].m_pNode);
        node->m_sgProperties = (node->m_sgProperties & ~kSgHidden) | kSgHidden;
    }
    m_bVisibilityTest = 0;
    m_v2Size_maybe.m_fX = 0x1p+0f;
    m_v2Pos.m_fX = 0.0f;
    m_v2Pos.m_fY = 0.0f;
    m_v2Size_maybe.m_fY = 0x1p+0f;
    std::memcpy(m_aColor_maybe, kColorWhite, 4);
    return 1;
}

// 0x00072c30 CFlashHotSpot_Destroy: both lists freed.
void CFlashHotSpot::Destroy() {
    if (m_vp2dObject.m_pBlock != nullptr) {
        Mem_FreeAligned16(m_vp2dObject.m_pBlock);
        m_vp2dObject.m_pBlock = nullptr;
    }
    m_vp2dObject.m_ui32NbUsedElt = 0;
    m_vp2dObject.m_pBlock = nullptr;
    if (m_vp3dNodeList.m_pBlock != nullptr) {
        Mem_FreeAligned16(m_vp3dNodeList.m_pBlock);
        m_vp3dNodeList.m_pBlock = nullptr;
    }
    m_vp3dNodeList.m_ui32NbUsedElt = 0;
    m_vp3dNodeList.m_pBlock = nullptr;
}

// 0x00072cc0 FlashWidgetBinding_SyncAtomics_maybe (XXL2 Update3dAttachedObject). Node flags: 0x1 hide
// with the anchor, 0x10 a particle effect (CParticlesNodeFx) started and stopped with it, 0x100 never
// shown by the hot spot.
void CFlashHotSpot::Update3dAttachedObject(CKFlashUI* flashUI) {
    const uint32_t uiFlags = flashUI->m_baFlags;
    if (m_bVisibilityTest == 0 || (uiFlags & CKFlashUI::kNeverRender) != 0 || (uiFlags & CKFlashUI::kHotSpotsHidden) != 0) {
        for (uint32_t i = 0; i < m_vp3dNodeList.m_ui32NbUsedElt; ++i) {
            SAttachedNode& item = m_vp3dNodeList.m_pBlock[i];
            CSGLeaf* node = static_cast<CSGLeaf*>(item.m_pNode);
            uint32_t flags = item.m_ui32Flags;
            if ((flags & 1) != 0) {
                node->m_sgProperties = (node->m_sgProperties & ~kSgHidden) | kSgHidden;
                flags = item.m_ui32Flags;
            }
            if ((flags & 0x10) != 0) {
                node->m_sgProperties &= ~(kSgFxActive_maybe | kSgFxPending_maybe);  // and 0xfff7fbff
                // The node's emitter (CParticlesNodeFx +0x58, RpPrtStdEmitter) flag &= ~0x8.
                StopEmitter(static_cast<CParticlesNodeFx*>(node));
            }
        }
        return;
    }
    for (uint32_t i = 0; i < m_vp3dNodeList.m_ui32NbUsedElt; ++i) {
        SAttachedNode& item = m_vp3dNodeList.m_pBlock[i];
        CSGLeaf* node = static_cast<CSGLeaf*>(item.m_pNode);
        uint32_t flags = item.m_ui32Flags;
        if ((flags & 0x100) == 0) {
            node->m_sgProperties &= ~kSgHidden;
            flags = item.m_ui32Flags;
        }
        if ((flags & 0x10) != 0) {
            node->m_sgProperties = ((node->m_sgProperties & ~kSgFxActive_maybe) | kSgFxActive_maybe) & ~kSgFxPending_maybe;
            CParticlesNodeFx* fx = static_cast<CParticlesNodeFx*>(node);
            fx->m_fEmissionSpeedAdjustment = 0.0f;  // stw 0
            StartEmitter(fx);  // the emitter's flag |= 0xa
        }
        // The node's frame follows the anchor: modelling matrix pos = (anchor + offset.xy, offset.z), the
        // identity bit (rwMATRIXINTERNALIDENTITY 0x20000) cleared, then RwFrameUpdateObjects (0x10698;
        // nothing natively: every frame is a root, its LTM its modelling matrix).
        RwMatrix* modelling = &node->m_pRwFrame->modelling;
        const float y = m_v2Pos.m_fY + item.m_vPosOffset.y;  // fadds
        const float x = m_v2Pos.m_fX + item.m_vPosOffset.x;  // fadds
        modelling->pos.z = item.m_vPosOffset.z;
        modelling->flags &= ~0x20000u;
        modelling->pos.y = y;
        modelling->pos.x = x;
    }
}

// 0x000735f0 FlashWidgetBinding_SyncElements2d_maybe (XXL2 Update2dAttachedObject). Object flags: 0x1
// hide without an anchor, 0x100 never enabled here, 0x1000 keep its scale, 0x10000 keep its colour.
void CFlashHotSpot::Update2dAttachedObject() {
    if (m_bVisibilityTest == 0) {
        for (uint32_t i = 0; i < m_vp2dObject.m_ui32NbUsedElt; ++i) {
            SAttached2dObject& item = m_vp2dObject.m_pBlock[i];
            if ((item.m_ui32Flags & 1) != 0) item.m_pNode->Disable();  // vt+0x68
        }
        return;
    }
    for (uint32_t i = 0; i < m_vp2dObject.m_ui32NbUsedElt; ++i) {
        SAttached2dObject& item = m_vp2dObject.m_pBlock[i];
        IKNode2d* node = item.m_pNode;
        uint32_t flags = item.m_ui32Flags;
        if ((flags & 0x100) == 0) {
            node->Enable();  // vt+0x64
            flags = item.m_ui32Flags;
        }
        if ((flags & 0x1000) == 0) {
            node->m_v2ConstantScale.m_fY = m_v2Size_maybe.m_fY;
            node->m_v2ConstantScale.m_fX = m_v2Size_maybe.m_fX;
        }
        // x through the camera context's height/width ratio (engine +0x08 -> +0x48).
        const float y = m_v2Pos.m_fY + item.m_vPosOffset.m_fY;
        const float x = ppc::fmadds(CameraContext_GetHeightOverWidth(), item.m_vPosOffset.m_fX, m_v2Pos.m_fX);
        node->m_vPosition.m_fY = y;
        node->m_vPosition.m_fX = x;
        if ((item.m_ui32Flags & 0x10000) != 0) continue;
        IKNode2d* target = m_vp2dObject.m_pBlock[i].m_pNode;
        if (target == nullptr) continue;
        // The object's colour with the anchor's alpha (byte 3).
        if (target->m_ui8Type == 1) {
            IKText2d* text = static_cast<CText2d*>(target);
            uint8_t color[4];
            std::memcpy(color, &text->m_Color, 4);
            color[3] = m_aColor_maybe[3];
            text->SetColor(color);  // IKText2d vt+0x44 0x6a1f0 TextData_SetColor
        } else if (target->m_ui8Type == 3) {
            IKBillboard2d* billboard = static_cast<CBillboard2d*>(target);
            uint8_t color[4];
            std::memcpy(color, &billboard->m_Color, 4);
            color[3] = m_aColor_maybe[3];
            billboard->SetColor(color);  // IKBillboard2d vt+0x28 0x66d68 IKBillboard2d_SetColor
        }
    }
}

// 0x00073068 CFlashHotSpot_Load. Both lists are filled from the last record down.
int32_t CFlashHotSpot::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    uint32_t count = 0;
    ReadU32LE(file, &count);
    SizeList(&m_vp2dObject, count);
    for (uint32_t i = count; i-- != 0;) {
        SAttached2dObject& item = m_vp2dObject.m_pBlock[i];
        IKFile_ReadRef(file, &item.m_pNode);
        ReadWordsLE(file, &item.m_vPosOffset, 2);  // one 8-byte read
        ReadU32LE(file, &item.m_ui32Flags);
    }
    ReadU32LE(file, &count);
    SizeList(&m_vp3dNodeList, count);
    for (uint32_t i = count; i-- != 0;) {
        SAttachedNode& item = m_vp3dNodeList.m_pBlock[i];
        IKFile_ReadRef(file, &item.m_pNode);
        ReadWordsLE(file, &item.m_vPosOffset, 3);  // one 12-byte read
        ReadU32LE(file, &item.m_ui32Flags);
    }
    IKFile_ReadRef(file, &m_pFlashHotSpot);
    IKFile_ReadRef(file, &m_pParent);
    return 1;
}
