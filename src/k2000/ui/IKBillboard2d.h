// IKBillboard2d.h - the textured-quad part of the 2D billboards (unregistered, size 0x44; XXL2:
// K/KModules/KGL/2d/IKBillboard2d.h, the same members read in the same order). The second base of
// CBillboard2d (at +0x28, vtable = CBillboard2d's + 0x90), and of the billboard buttons.
// Original unit: the CBillboard2d_2.cpp range (0x66e30-0x67ec0).
//
// Its vtable matches XXL2's slot for slot (0 FreeMemoryBillboard2D 0x66db0, 1/2 destructors, 3 Destroy,
// 4 RecursiveRegistration, 5 Load, 6 Save, 7/8 GetClassType/GetClassID, 9 CreateBillboard 0x66e30,
// 10 SetColor 0x66d68, 11 SetBillboardSize 0x66d20, ...); the derived class's Load and Save reach it
// through thunks. Only the slots the loaders use are declared here.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/math/CVector2.h"

class IKFile;
struct Rt2dBrush;
struct RwTexture;

class IKBillboard2d {
public:
    IKBillboard2d();  // 0x000670f0 CBillboard2d_ConstructBrush_maybe (XXL2 IKBillboard2d::IKBillboard2d)
    virtual ~IKBillboard2d() {}
    // 0x00067598 CBillboard2d_LoadBrush (XXL2 IKBillboard2d::Load). The type is passed but not tested.
    virtual int32_t Load(IKFile* file, int32_t type);
    // vt+0x24 0x00066e30 IKBillboard2d_CreateBillboard (BillboardBrush_RebuildPath_maybe): Rt2dBrushSetUV
    // with m_pvUVs, then a new Rt2dPath (m_pBillboard) holding the rect (-0.5, -0.5, 1, 1); 1 when made.
    virtual int32_t CreateBillboard();
    // vt+0x40 0x00067028 BillboardBrush_RecreateBrush_maybe (CBillboard2d_2.cpp; also the billboard buttons' slot): the
    // brush destroyed (Rt2dBrushDestroy) and a new empty one made (Rt2dBrushCreate: no texture, the default UVs); with
    // it the colour word set again (vt+0x28 SetColor with a copy of m_Color) and the billboard rebuilt (vt+0x24
    // CreateBillboard), whose result it returns; 0 when no brush could be made. CKFlashNode2dFx_Stop 0x1bc638 calls it.
    virtual uint8_t RecreateBrush();
    // vt+0x34 0x00066c70 BillboardBrush_ApplyUV: Rt2dBrushSetUV with m_pvUVs. Called directly (no
    // front-end class overrides it).
    void ApplyUV();
    // vt+0x38 0x00066cb8 BillboardBrush_SetTexture: Rt2dBrushSetTexture unless the brush has it already; 0
    // without a brush, else 1 when the brush has the texture. Called directly (no front-end override).
    int32_t SetTexture(RwTexture* texture);
    // 0x000671a0 DrawUIBillboardShapeWithTransform: the quad at `position` (x in screen-height units, the
    // aspect applied), aligned by hAlign/vAlign (0, 1, 2), sized by m_vBillboardSize x scale (the width x
    // the aspect when m_bStretchToAspectRatio), rotated by `rotation` degrees, in the blend of
    // m_bUseAlpha's table entry; the border outline when m_bEnableBorder. 1.
    uint8_t DrawShapeWithTransform(float rotation, const CVector2* position, uint8_t hAlign, uint8_t vAlign,
                                   const CVector2* scale);
    // vt+0x28 0x00066d68 IKBillboard2d_SetColor (XXL2 slot 10 SetColor; CText2d.cpp): the colour word, then
    // the brush's four corners. Called directly (the slot is not declared yet; no front-end override).
    void SetColor(const uint8_t* color);
    // vt+0x00 0x00066db0 IKBillboard2d_FreeMemoryBillboard2D_maybe (XXL2 slot 0 FreeMemoryBillboard2D; Ghidra
    // Rt2dShape_Release_maybe, graphical/ui/CText2d.cpp's checklist line and body): the path and the
    // brush destroyed and cleared, then the stretch byte, the size and the colour word 0. Called directly (the slot
    // is not declared: no front-end override).
    void FreeMemoryBillboard2D();
    // vt+0x44 0x00066ef8 BillboardBrush_ComputeAlignedRect_maybe (XXL2 IKBillboard2d::GetBoundingBox(CBox2D&, const
    // CVector2&, UInt8, UInt8)): the box of the quad at `position`, sized m_vBillboardSize (the width divided by the
    // aspect unless m_bStretchToAspectRatio), aligned by hAlign / vAlign (0, 1 centred, 2). Called directly.
    void GetBoundingBox(CBox2D* box, const CVector2* position, uint8_t hAlign, uint8_t vAlign) const;
    // vt+0x0c 0x00066c18 BillboardBrush_ClearReferences_maybe (XXL2 IKBillboard2d::Destroy; CBillboard2d_Destroy
    // 0x5b3a8 and CBillboardButton2d_Destroy call it): FreeMemoryBillboard2D through vt+0x00. Name ours (Destroy is
    // IKNode2d's in the derived classes).
    void DestroyBillboard() { FreeMemoryBillboard2D(); }
    // 0x00066c60 BillboardBrush_GetTexture: the brush's texture (Rt2dBrush +0x68; no null test).
    RwTexture* GetTexture() const;
    // vt+0x2c 0x00066d20 BillboardBrush_SetAlpha_maybe (DotD's slot): the colour's alpha byte (+0x0f), then the brush's
    // four corners.
    void SetAlpha(uint8_t alpha);

    void* m_pBillboard;           // +0x04 Rt2dPath* (CreateBillboard)
    Rt2dBrush* m_pBrush;          // +0x08 Rt2dBrushStreamRead
    uint32_t m_Color;             // +0x0c CColor, read raw (4 file bytes, seen big-endian by the PS3)
    uint32_t m_borderColor;       // +0x10 CColor, read raw; not set by the constructor
    CVector2 m_vBillboardSize;    // +0x14
    uint8_t m_bStretchToAspectRatio;  // +0x1c
    uint8_t m_bEnableBorder;      // +0x1d (+0x1e..+0x1f: padding the original never writes)
    CVector2 m_pvUVs[4];          // +0x20
    uint8_t m_bUseAlpha;          // +0x40 the constructor sets 1; the blend table index (+0x41..+0x43: padding)
};
DOTD_ASSERT_SIZE(IKBillboard2d, 0x44);
DOTD_ASSERT_OFFSET(IKBillboard2d, m_pBillboard, 0x04);
DOTD_ASSERT_OFFSET(IKBillboard2d, m_pBrush, 0x08);
DOTD_ASSERT_OFFSET(IKBillboard2d, m_Color, 0x0c);
DOTD_ASSERT_OFFSET(IKBillboard2d, m_borderColor, 0x10);
DOTD_ASSERT_OFFSET(IKBillboard2d, m_vBillboardSize, 0x14);
DOTD_ASSERT_OFFSET(IKBillboard2d, m_bStretchToAspectRatio, 0x1c);
DOTD_ASSERT_OFFSET(IKBillboard2d, m_bEnableBorder, 0x1d);
DOTD_ASSERT_OFFSET(IKBillboard2d, m_pvUVs, 0x20);
DOTD_ASSERT_OFFSET(IKBillboard2d, m_bUseAlpha, 0x40);
