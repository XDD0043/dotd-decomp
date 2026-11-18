// CKCrumblyZoneElement.cpp - reconstructed original translation unit 0x402430-0x403720 (GAME_TOC1, main_toc1), 28 functions, 23 live.
// Primary class: CKCrumblyZoneElement  key 0xa30c  category Logic  size 0x30  vtable 0xb25700
// Other owners: CrumblyZonePiece (11), CKHkCrumblyZoneMultiState (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x402430  CKCrumblyZoneElement_Delete
//   [x] 0x402480  CKCrumblyZoneElement_Construct  [dead]
//   [ ] 0x402490  CKCrumblyZoneElement_Construct_2  [dead]
//   [x] 0x4024a0  CrumblyZonePiece_ReparentNodes_maybe
//   [ ] 0x402608  RegisterCKCrumblyZoneElementClass
//   [ ] 0x402680  _GLOBAL__I_402680
//   [x] 0x402690  CrumblyZonePiece_SetFxPosition
//   [x] 0x4026d0  CrumblyZonePiece_ResetMeshMatrixB_maybe
//   [x] 0x402710  CrumblyZonePiece_ResetMeshMatrixA_maybe
//   [x] 0x402750  CrumblyZonePiece_TransformMeshMatrixB_maybe
//   [x] 0x402870  CrumblyZonePiece_TransformMeshMatrixA_maybe
//   [x] 0x402990  CKHkCrumblyZoneMultiState_AdvancePieceAnim_maybe
//   [x] 0x4029d8  CKCrumblyZoneElement_DeleteArray
//   [x] 0x402a80  CrumblyZonePiece_Activate_maybe
//   [x] 0x402d68  CrumblyZonePiece_Deactivate_maybe
//   [ ] 0x402e48  CrumblyZonePiece_CaptureMeshMatrixA_maybe  [dead]
//   [x] 0x402f20  CKCrumblyZoneElement_CreateArray
//   [x] 0x402fb8  CKCrumblyZoneElement_Create
//   [ ] 0x402ff0  CrumblyZonePiece_CaptureMeshMatrixB_maybe  [dead]
//   [ ] 0x4030c8  CKCrumblyZoneElement_Save
//   [x] 0x4030d0  CKCrumblyZoneElement_RecursiveRegistration  (returns 1: the root's empty slot)
//   [x] 0x4030d8  CKCrumblyZoneElement_PostLoad  [inline]
//   [x] 0x4030f8  CKCrumblyZoneElement_Destroy
//   [x] 0x403138  CrumblyZonePiece_ApplyWorldMatrix_maybe
//   [x] 0x403358  CKCrumblyZoneElement_Load
//   [x] 0x4036b0  CKCrumblyZoneElement_Destructor  (C++ destructor chain: vtable stores only)
//   [ ] 0x4036c8  CKCrumblyZoneElement_Destructor_2  [dead]
//   [x] 0x4036e0  CKCrumblyZoneElement_DeletingDestructor  (C++ deleting destructor)
//
//   [ ] 0x9c1108  CKCrumblyZoneElement_GetClassType  [inline]
//   [ ] 0x9c1110  CKCrumblyZoneElement_GetClassID  [inline]
//   [ ] 0x9c1118  CKCrumblyZoneElement_IsKindOfClass  [inline]
#include "k2000/logic/CKCrumblyZoneElement.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/scenegraph/CSGLeaf.h"
#include "k2000/scenegraph/CSGBranch.h"
#include "k2000/hooks/IKHook.h"
#include "k2000/dictionaries/CAnimationDictionary.h"
#include "k2000/fx/IKFx.h"
#include "k2000/logic/CKParticlesEffectFxData.h"
#include "k2000/logic/IKFxData.h"
#include "k2000/logic/fx/CKParticlesEffectNodeFx.h"
#include "k2000/misc/Engine.h"
#include "k2000/services/CKSrvFx.h"

#include "k2000/io/IKFile.h"
#include "k2000/misc/Mat4.h"
#include "k2000/scenegraph/CAnimatedNode.h"
#include "k2000/system/IKTime.h"

// 0x00403358 CKCrumblyZoneElement_Load
int32_t CKCrumblyZoneElement::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    IKFile_ReadRef(file, &m_pZone);
    IKFile_ReadRef(file, &m_pNode);
    IKFile_ReadRef(file, &m_unk10);
    ReadF32LE(file, &m_unk14);
    ReadU32LE(file, &m_unk18);
    IKFile_ReadRef(file, &m_unk1c);
    IKFile_ReadRef(file, &m_unk20);
    m_pMatrix28 = RwMatrixCreate_Thunk();
    m_pMatrix2c = RwMatrixCreate_Thunk();
    CMatrix34_LoadMatrix(m_pMatrix28, file);
    CMatrix34_LoadMatrix(m_pMatrix2c, file);
    return 1;
}

namespace {
// The scene node flag 4 (hidden) of a node (+0x10, the original's rlwinm / rotlwi pair).
void SetHidden(IKSerializable* node, bool hidden) {
    CSGLeaf* leaf = static_cast<CSGLeaf*>(node);
    leaf->m_sgProperties = hidden ? (leaf->m_sgProperties | 4u) : (leaf->m_sgProperties & ~4u);
}
// A node taken off its parent (vt+0x78) and hung under `parent` (vt+0x70).
void Rehang(IKSerializable* node, IKSerializable* parent) {
    CSGLeaf* leaf = static_cast<CSGLeaf*>(node);
    if (leaf->m_pParent != nullptr) leaf->m_pParent->RemoveChild(leaf);
    static_cast<CSGBranch*>(parent)->AddChild(leaf);
}
}  // namespace

// 0x00402a80 CrumblyZonePiece_Activate_maybe
void CKCrumblyZoneElement::Activate(uint32_t anim) {
    m_unk08 = 1;
    ReparentNodes();  // 0x004024a0
    if (m_pNode != nullptr) SetHidden(m_pNode, false);
    if (m_unk10 != nullptr) {
        SetHidden(m_unk10, false);
        // The animation `anim` of the dictionary +0x1c crossfaded in (blend +0x14, from the node's current time, mode 2;
        // the word is read before the time, and not tested).
        CAnimatedNode* node = static_cast<CAnimatedNode*>(m_unk10);
        const float blend = m_unk14;
        const uint32_t word = static_cast<uint32_t>(static_cast<CAnimationDictionary*>(m_unk1c)->m_apAnimations[anim]);
        const float start = node->GetCurrentAnimTime();  // 0x000c95a8
        node->CrossfadeToAnim(blend, start, word, 2);    // 0x000c8eb0
    }
    if (m_unk20 != nullptr) {
        // The FX service's first free effect of the data's class and type (loaded, not reserved) takes the data, is
        // reserved for the piece and started (vt+0x84 / +0x88 / +0x64); null when none is free.
        CKSrvFx* fx = static_cast<CKSrvFx*>(g_pEngine->m_srvFx);  // engine +0x60
        m_unk24 = fx->AcquireFx(static_cast<IKFxData*>(m_unk20), this);
    }
}

// 0x00402d68 CrumblyZonePiece_Deactivate_maybe
void CKCrumblyZoneElement::Deactivate() {
    m_unk08 = 0;
    if (m_pNode != nullptr) SetHidden(m_pNode, true);
    if (m_unk10 != nullptr) SetHidden(m_unk10, true);
    if (m_unk24 != nullptr) {
        StopOwnedParticleEffect(static_cast<IKFx*>(m_unk24), this);  // 0x001cdde8
        static_cast<IKFx*>(m_unk24)->ReleaseReservation(this);      // vt+0x54
        m_unk24 = nullptr;
    }
}

// 0x004024a0 CrumblyZonePiece_ReparentNodes_maybe
void CKCrumblyZoneElement::ReparentNodes() {
    IKSerializable* zoneNode = static_cast<IKHook*>(m_pZone)->m_pKGLObject;  // the zone's node (+0x1c)
    if (m_pNode != nullptr) Rehang(m_pNode, zoneNode);
    if (m_unk10 != nullptr) Rehang(m_unk10, zoneNode);
    if (m_unk20 != nullptr) {
        // The FX data (a CKParticlesEffectFxData) follows the zone's node: no hot spot, flag bit 4 set.
        CKParticlesEffectFxData* data = static_cast<CKParticlesEffectFxData*>(m_unk20);
        data->m_pAttachOwner = static_cast<CSGLeaf*>(zoneNode);
        data->m_pAttachHotSpot = nullptr;
        data->m_unk08 = static_cast<uint8_t>((data->m_unk08 & 0xefu) | 0x10u);
    }
}

// 0x00402690 CrumblyZonePiece_SetFxPosition
void CKCrumblyZoneElement::SetFxPosition(const float* position) {
    if (m_unk24 == nullptr) return;
    SetOwnedParticleEffectPosition(static_cast<CKParticlesEffectNodeFx*>(m_unk24), reinterpret_cast<const CVector3*>(position),
                                   this);  // 0x001cdce0
}

// 0x00402710 CrumblyZonePiece_ResetMeshMatrixA_maybe
void CKCrumblyZoneElement::ResetMeshMatrixA() {
    if (m_pNode != nullptr) static_cast<CSGMovable*>(m_pNode)->SetLocalMatrix(reinterpret_cast<const RwMatrix*>(m_pMatrix28));
}

// 0x004026d0 CrumblyZonePiece_ResetMeshMatrixB_maybe
void CKCrumblyZoneElement::ResetMeshMatrixB() {
    if (m_unk10 != nullptr) static_cast<CSGMovable*>(m_unk10)->SetLocalMatrix(reinterpret_cast<const RwMatrix*>(m_pMatrix2c));
}

// 0x00402870 CrumblyZonePiece_TransformMeshMatrixA_maybe
void CKCrumblyZoneElement::TransformMeshMatrixA(const CMatrix34* matrix) {
    if (m_pNode == nullptr) return;
    CMatrix34 local = *m_pMatrix28;
    Mat4_TransformPostConcat(&local, matrix);  // 0x0023f760
    static_cast<CSGMovable*>(m_pNode)->SetLocalMatrix(reinterpret_cast<const RwMatrix*>(&local));  // 0x000d0be8
}

// 0x00402750 CrumblyZonePiece_TransformMeshMatrixB_maybe
void CKCrumblyZoneElement::TransformMeshMatrixB(const CMatrix34* matrix) {
    if (m_unk10 == nullptr) return;
    CMatrix34 local = *m_pMatrix2c;
    Mat4_TransformPostConcat(&local, matrix);  // 0x0023f760
    static_cast<CSGMovable*>(m_unk10)->SetLocalMatrix(reinterpret_cast<const RwMatrix*>(&local));  // 0x000d0be8
}

// 0x00403138 CrumblyZonePiece_ApplyWorldMatrix_maybe
void CKCrumblyZoneElement::ApplyWorldMatrix(const CMatrix34* matrix) {
    if (m_unk08 == 0) return;
    if (m_pNode != nullptr) {
        CMatrix34 local = *m_pMatrix28;
        Mat4_TransformPostConcat(&local, matrix);  // 0x0023f760
        static_cast<CSGMovable*>(m_pNode)->SetLocalMatrix(reinterpret_cast<const RwMatrix*>(&local));  // 0x000d0be8
    }
    if (m_unk10 != nullptr) {
        CMatrix34 local = *m_pMatrix2c;
        Mat4_TransformPostConcat(&local, matrix);
        static_cast<CSGMovable*>(m_unk10)->SetLocalMatrix(reinterpret_cast<const RwMatrix*>(&local));
    }
}

// 0x00402990 CKHkCrumblyZoneMultiState_AdvancePieceAnim_maybe
void CKCrumblyZoneElement::AdvancePieceAnim(IKTime* frameClock) {
    if (m_unk08 == 0 || m_unk10 == nullptr) return;
    static_cast<CAnimatedNode*>(m_unk10)->AddAnimTime(frameClock->m_afDeltaTime[0]);  // 0x000c9638
}

// 0x004030f8 CKCrumblyZoneElement_Destroy (the pointers are kept, as in the original)
void CKCrumblyZoneElement::Destroy() {
    RwMatrixDestroy_Thunk(m_pMatrix28);
    RwMatrixDestroy_Thunk(m_pMatrix2c);
}
