// CFlashHotSpot.h - ties 3D scene nodes and 2D nodes to a Flash object's screen position (key 0xc0d,
// vtable 0xb160e8, size 0x40). Original units: CFlashHotSpot.cpp (0x722f8-0x724e0) and CFlashHotSpot_2.cpp
// (0x72a88-0x73b10). XXL2: K/KModules/KGL/2d/Maestro/FlashObject/CFlashHotSpot.h, the same members read in
// the same order; DotD has no m_vpObject (XXL2's Load allocates it last) and adds +0x34..+0x3f.
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/math/CVector2.h"
#include "k2000/ui/IKFlashObject.h"
#include "k2000/ui/IKNode2d.h"
#include "k2000/util/TVector.h"

class CKFlashUI;

// XXL2 SAttachedNode (0x14 bytes on the PS3).
struct SAttachedNode {
    IKSerializable* m_pNode;  // +0x00 XXL2 CNode* (a reference)
    CVector3 m_vPosOffset;    // +0x04
    uint32_t m_ui32Flags;     // +0x10
};
DOTD_ASSERT_SIZE(SAttachedNode, 0x14);

// XXL2 SAttached2dObject (0x10 bytes on the PS3).
struct SAttached2dObject {
    IKNode2d* m_pNode;        // +0x00 a reference
    CVector2 m_vPosOffset;    // +0x04
    uint32_t m_ui32Flags;     // +0x0c
};
DOTD_ASSERT_SIZE(SAttached2dObject, 0x10);

class CFlashHotSpot : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryGraphical, 0x30)
    DOTD_DECLARE_FACTORIES(CFlashHotSpot)

    CFlashHotSpot();  // inlined in 0x00072a88 CFlashHotSpot_Create
    ~CFlashHotSpot() override;                                              // vt+0x00 / +0x04  0x998fe0 / 0x999078
    int32_t IsKindOfClass(uint32_t key) override { return key == 0xc0d || key == 0xc; }  // vt+0x08 0x998fc0
    void Destroy() override;                                                // vt+0x10 0x00072c30 CFlashHotSpot_Destroy
    void RecursiveRegistration(int32_t /*type*/) override {}                // vt+0x24 0x72af0 (returns 1)
    int32_t Save(IKFile* /*file*/, int32_t /*type*/) override { return 1; }                   // vt+0x28 0x72ae8
    int32_t Load(IKFile* file, int32_t type) override;                      // vt+0x2c 0x00073068 CFlashHotSpot_Load
    int32_t PostLoad(int32_t type) override;                                // vt+0x30 0x00072af8 CFlashHotSpot_PostLoad

    // The Ghidra names say FlashWidgetBinding_*: they are this class's (XXL2 CFlashHotSpot) methods.
    // 0x00072528 FlashWidgetBinding_SetHidden_maybe (XXL2 HideHotSpotHierarchy): the 2D objects disabled
    // (or enabled), the 3D nodes' hidden bit (CSGLeaf flags bit 2) set to hide.
    void HideHotSpotHierarchy(uint8_t hide);
    // 0x00072198 FlashWidgetBinding_UpdateAnchor_maybe (CKFlashUI.cpp): the anchor's screen position, size
    // and colour from the flash object (vt+0x60); m_bVisibilityTest = found.
    void UpdateAnchor();
    uint8_t IsAnchorUnresolved() const { return m_bVisibilityTest ^ 1; }  // 0x000722e8 (CKFlashUI.cpp)
    // 0x00072cc0 FlashWidgetBinding_SyncAtomics_maybe (XXL2 Update3dAttachedObject): the 3D nodes follow
    // the anchor (or are hidden when it is not found or the interface hides its hot spots).
    void Update3dAttachedObject(CKFlashUI* flashUI);
    // 0x000735f0 FlashWidgetBinding_SyncElements2d_maybe (XXL2 Update2dAttachedObject): the 2D objects
    // follow the anchor: enabled, scaled, placed and given the anchor's alpha; disabled without one.
    void Update2dAttachedObject();
    // 0x00072830 FlashWidgetBinding_SetElement2dFlags_maybe (XXL2 SetObjectFlags(IKNode2d*, UInt32)).
    // BUG(original): an object that is not in the list writes the word before the block.
    void SetObjectFlags(IKNode2d* node, uint32_t flags);
    // 0x00072a08 FlashWidgetBinding_SetAtomicFlags_maybe (XXL2 SetObjectFlags(CNode*, UInt32)); the same bug.
    void SetObjectFlags(IKSerializable* node, uint32_t flags);

    TVector<SAttachedNode, 2> m_vp3dNodeList;       // +0x04 (block, capacity +0x08, count +0x0c)
    TVector<SAttached2dObject, 2> m_vp2dObject;     // +0x10 (block, capacity +0x14, count +0x18)
    IKFlashObject* m_pFlashHotSpot;                 // +0x1c a reference (a CKFlashText in LVL000)
    uint8_t m_bIsHidden;                            // +0x20 HideHotSpotHierarchy's argument
    IKSerializable* m_pParent;                      // +0x24 CKFlashUI (a reference)
    uint8_t m_bVisibilityTest;                      // +0x28 the anchor was found (UpdateAnchor); PostLoad sets 0
    CVector2 m_v2Pos;                               // +0x2c the anchor, normalised; PostLoad sets (0, 0)
    CVector2 m_v2Size_maybe;                        // +0x34 (DotD) the anchor's size: the 2D objects' scale; PostLoad (1, 1)
    uint8_t m_aColor_maybe[4];                      // +0x3c (DotD) the anchor's RGBA; PostLoad copies 0x00c50dfc (white)
};
DOTD_ASSERT_SIZE(CFlashHotSpot, 0x40);
DOTD_ASSERT_OFFSET(CFlashHotSpot, m_vp3dNodeList, 0x04);
DOTD_ASSERT_OFFSET(CFlashHotSpot, m_vp2dObject, 0x10);
DOTD_ASSERT_OFFSET(CFlashHotSpot, m_pFlashHotSpot, 0x1c);
DOTD_ASSERT_OFFSET(CFlashHotSpot, m_pParent, 0x24);
DOTD_ASSERT_OFFSET(CFlashHotSpot, m_bIsHidden, 0x20);
DOTD_ASSERT_OFFSET(CFlashHotSpot, m_bVisibilityTest, 0x28);
DOTD_ASSERT_OFFSET(CFlashHotSpot, m_v2Pos, 0x2c);
DOTD_ASSERT_OFFSET(CFlashHotSpot, m_v2Size_maybe, 0x34);
DOTD_ASSERT_OFFSET(CFlashHotSpot, m_aColor_maybe, 0x3c);
