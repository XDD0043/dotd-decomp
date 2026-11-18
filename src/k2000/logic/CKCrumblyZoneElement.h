// CKCrumblyZoneElement.h - one element of a crumbly zone (key 0xa30c, vtable 0xb25700, size 0x30).
// Original unit: CKCrumblyZoneElement.cpp. DotD only (no XXL2 class); the names are ours, the reference
// types from the files (struct draft).
#pragma once

class IKTime;
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"
#include "k2000/math/CMatrix34.h"

class CKCrumblyZoneElement : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x28c)
    int32_t IsKindOfClass(uint32_t key) override { return key == 0xa30c || key == 0xc; }  // vt+0x08 0x9c1118
    DOTD_DECLARE_FACTORIES(CKCrumblyZoneElement)

    CKCrumblyZoneElement() {}  // 0x00402480 CKCrumblyZoneElement_Construct: only the vtable
    // 0x004036b0 CKCrumblyZoneElement_Destructor / 0x004036e0 DeletingDestructor: vtable stores only (operator delete).
    ~CKCrumblyZoneElement() override {}
    void Destroy() override;  // vt+0x10 0x004030f8 CKCrumblyZoneElement_Destroy: both matrices destroyed

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00403358 CKCrumblyZoneElement_Load
    // vt+0x30 0x004030d8 CKCrumblyZoneElement_PostLoad: no FX running (+0x24), the piece off (+0x08).
    int32_t PostLoad(int32_t /*type*/) override {
        m_unk24 = nullptr;
        m_unk08 = 0;
        return 1;
    }

    // 0x00402a80 CrumblyZonePiece_Activate_maybe: the piece on (+0x08), its nodes under the zone's node and shown (scene
    // flag 4 cleared); the animated node (+0x10) crossfades to `anim` of +0x1c and the FX (+0x20) starts (kept in +0x24).
    void Activate(uint32_t anim);
    // 0x00402d68 CrumblyZonePiece_Deactivate_maybe: the piece off, its nodes hidden, its FX (+0x24) stopped and released.
    void Deactivate();
    // 0x004024a0 CrumblyZonePiece_ReparentNodes_maybe: the node (+0x0c) and the animated node (+0x10) taken off their
    // parents and hung under the zone's node; the FX data (+0x20) attached to it.
    void ReparentNodes();
    // 0x00402690 CrumblyZonePiece_SetFxPosition: the running FX (+0x24) moved to `position` (SetOwnedParticleEffectPosition).
    void SetFxPosition(const float* position);
    // 0x00402710 CrumblyZonePiece_ResetMeshMatrixA_maybe / 0x004026d0 _ResetMeshMatrixB_maybe: the node / the animated
    // node back to its loaded local matrix (+0x28 / +0x2c; CSGMovable_SetLocalMatrix_maybe 0xd0be8).
    void ResetMeshMatrixA();
    void ResetMeshMatrixB();
    // 0x00403138 CrumblyZonePiece_ApplyWorldMatrix_maybe: an active piece's node / animated node get their loaded matrix
    // (+0x28 / +0x2c) post-concatenated with `matrix` as their local matrix.
    void ApplyWorldMatrix(const CMatrix34* matrix);
    // 0x00402870 CrumblyZonePiece_TransformMeshMatrixA_maybe / 0x00402750 _TransformMeshMatrixB_maybe: the node (+0x0c) /
    // the animated node (+0x10), when there is one, gets its loaded matrix (+0x28 / +0x2c) post-concatenated with `matrix`
    // as its local matrix (ApplyWorldMatrix's halves without the "on" test; only OPD descriptors 0xbb40a0 / 0xbb4098
    // point at them, nothing calls them).
    void TransformMeshMatrixA(const CMatrix34* matrix);
    void TransformMeshMatrixB(const CMatrix34* matrix);
    // 0x00402990 CKHkCrumblyZoneMultiState_AdvancePieceAnim_maybe: an active piece's animated node (+0x10) advanced by the
    // frame time.
    void AdvancePieceAnim(IKTime* frameClock);

    IKSerializable* m_pZone;      // +0x04 CKHkS08CrumblyZoneMultiState in the files
    uint8_t m_unk08;              // +0x08 the piece is on (Activate / Deactivate); not loaded, PostLoad clears it
    uint8_t m_pad09[3];
    IKSerializable* m_pNode;      // +0x0c a scene node (CNode) in the files
    IKSerializable* m_unk10;      // +0x10 a CAnimatedNode (sector 2 of LVL010), else null
    float m_unk14;                // +0x14
    uint32_t m_unk18;             // +0x18
    IKSerializable* m_unk1c;      // +0x1c CAnimationDictionary of +0x10 (Activate crossfades its entry `anim`)
    IKSerializable* m_unk20;      // +0x20 CKParticlesEffectFxData (the piece FX), or null
    IKSerializable* m_unk24;      // +0x24 the running FX (Activate); not loaded, PostLoad sets 0
    CMatrix34* m_pMatrix28;       // +0x28 RwMatrixCreate, then loaded
    CMatrix34* m_pMatrix2c;       // +0x2c RwMatrixCreate, then loaded
};
DOTD_ASSERT_SIZE(CKCrumblyZoneElement, 0x30);
DOTD_ASSERT_OFFSET(CKCrumblyZoneElement, m_pZone, 0x04);
DOTD_ASSERT_OFFSET(CKCrumblyZoneElement, m_pNode, 0x0c);
DOTD_ASSERT_OFFSET(CKCrumblyZoneElement, m_unk10, 0x10);
DOTD_ASSERT_OFFSET(CKCrumblyZoneElement, m_unk14, 0x14);
DOTD_ASSERT_OFFSET(CKCrumblyZoneElement, m_unk18, 0x18);
DOTD_ASSERT_OFFSET(CKCrumblyZoneElement, m_unk1c, 0x1c);
DOTD_ASSERT_OFFSET(CKCrumblyZoneElement, m_unk20, 0x20);
DOTD_ASSERT_OFFSET(CKCrumblyZoneElement, m_pMatrix28, 0x28);
DOTD_ASSERT_OFFSET(CKCrumblyZoneElement, m_pMatrix2c, 0x2c);
