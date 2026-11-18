// CBillboardList2d.h - a row (or column) of 2D billboards sharing a size, colour and spacing (key 0x58d, vtable
// 0xb158c8, size 0x84; XXL2: K/KModules/KGL/2d/CBillboardList2d.h, an IKNode2d with the same members in the same
// order). Original unit: CBillboardList2d.cpp (0x5c868-0x5f768; a few of its methods sit at the end of
// CBillboardButton2d.cpp's range). No game file holds one.
//
// The slots after IKNode2d's (+0x88..+0xd8) are XXL2's 33..53 one for one (CreateBillboardsList .. HideBillboard), the
// names below. m_baFlags bit 2 (0x4) is the stretch-to-aspect-ratio flag (Enable/DisableStretchToAspectRatio).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/math/CVector2.h"
#include "k2000/ui/IKNode2d.h"
#include "k2000/util/TVector.h"

struct Rt2dBrush;
struct Rt2dPath;
struct RwTexture;

class CBillboardList2d : public IKNode2d {
public:
    DOTD_CLASS_KEY(kCategoryGraphical, 0x16)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9976a8
        return key == 0x58d || key == 0x24d || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CBillboardList2d)

    // A billboard's four UV corners (XXL2 CVector2[4]).
    struct BillboardUVs {
        CVector2 m_aUV[4];
    };

    // 0x0005f278 CBillboardList2d_Create: the node base (0x69a00), the six vectors empty (null, 5, 0), no spacing,
    // alignment 0, size (0, 0), colour 0.
    CBillboardList2d();
    // 0x00997818 CBillboardList2d_Destructor (0x9976d0 the deleting one): the UV, texture, show, brush, link and path
    // blocks freed (each vector's length and block cleared), then the node base's vtable.
    ~CBillboardList2d() override;
    // vt+0x10 0x0005c870 CBillboardList2d_Destroy: IKNode2d's (FreeMemory, vt+0x54); inherited.
    // vt+0x24 0x0005c750 CBillboardList2d_RecursiveRegistration: returns 1, registers nothing (not IKNode2d's).
    void RecursiveRegistration(int32_t /*type*/) override {}
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0005e6a0 CBillboardList2d_Load (every type)

    // vt+0x54 0x0005f4c8 CBillboardList2d_ResetRuntime_maybe (XXL2 FreeMemory): IKNode2d's, the billboards and the
    // textures destroyed, then no spacing, alignment 0, size (0, 0), colour 0.
    void FreeMemory() override;
    // vt+0x58 0x0005dff8 CBillboardList2d_vf58 (XXL2 RecursiveNodeReach): `what` 7 (a texture going away, `data` it):
    // every texture slot below the brush count that holds it is emptied (SetTexture(null, slot)).
    void RecursiveNodeReach(uint8_t what, void* data) override;
    // vt+0x78 0x0005d7c0 CBillboardList2d_GetBoundingRect (XXL2 GetBoundingBox): the box of the whole row by the
    // alignment (0 right, 1 left, 2 up, 3 down from the first billboard); unknown alignments leave the box.
    void GetBoundingBox(CBox2D* box) const override;
    // vt+0x80 0x0005f210 CBillboardList2d_vf80 (XXL2 Scale): SetBillboardsSize(size x scale).
    void Scale(const CVector2& scale) override;
    // vt+0x84 0x0005d518 CBillboardList2d_Draw (XXL2 Render): enabled lists draw every shown billboard with a path and
    // a brush, stepped by the alignment, rotated and sized (the width x the aspect when stretched).
    void Render(IKTime* time) override;

    // vt+0x88 0x0005ee28 CBillboardList2d_SetBillboardCount (XXL2 CreateBillboardsList): the billboards destroyed, then
    // `count` empty ones (no path, no texture link, a new brush, hidden, the default UVs).
    virtual void CreateBillboardsList(uint32_t count);
    // vt+0x8c 0x0005f5b8 CBillboardList2d_ResetTextureSlots_maybe (XXL2 CreateTexturesList): the textures destroyed,
    // then `count` empty slots.
    virtual void CreateTexturesList(uint32_t count);
    // vt+0x90 0x0005d9d0 CBillboardList2d_AddBillboard: one more billboard (no path, no link, a brush in the list's
    // colour, the default UVs), built (CreateBillboard) and shown.
    virtual void AddBillboard();
    // vt+0x94 0x0005d0c8 CBillboardList2d_RemoveBillboard: billboard `index`'s path and brush destroyed and its entries
    // removed (the UV entry is not: BUG(original), the later billboards keep their old UVs' positions).
    virtual void RemoveBillboard(uint32_t index);
    // vt+0x98 0x0005cb70 CBillboardList2d_vf98 (XXL2 AddTexture): one more empty texture slot.
    virtual void AddTexture();
    // vt+0x9c 0x0005dea0 CBillboardList2d_RemoveTexture: links past `index` shift down, links to it are removed
    // (RemoveTextureFromBillboard), then the texture destroyed and its slot removed.
    virtual void RemoveTexture(uint32_t index);
    // vt+0xa0 0x0005cfb0 CBillboardList2d_RefreshItemShape_maybe (XXL2 CreateBillboard): billboard `index`'s brush
    // gets its UVs and a new path holding the rect (-0.5, -0.5, 1, 1); 1 when made.
    virtual int32_t CreateBillboard(uint32_t index);
    // vt+0xa4 0x0005ce10 CBillboardList2d_RefreshAllItemShapes_maybe (XXL2 CreateBillboards): every billboard built;
    // 1 when all were (the result byte).
    virtual int32_t CreateBillboards();
    // vt+0xa8 0x0005ceb8 CBillboardList2d_vfA8 (XXL2 SetColor): the colour word, then every brush's four corners.
    virtual void SetColor(const uint32_t* color);
    // vt+0xac 0x0005c790 CBillboardList2d_vfAC (XXL2 SetBillboardsSize).
    virtual void SetBillboardsSize(const CVector2* size) { m_vBillboardsSize = *size; }
    // vt+0xb0 0x00997638 CBillboardList2d_vfB0 (XXL2 UpdateUVs): a billboard below the count gives its brush (not
    // tested for null) its UVs.
    virtual void UpdateUVs(uint32_t index);
    // vt+0xb4 0x00997590 CBillboardList2d_vfB4 (XXL2 SetUVs): a billboard below the count takes the four UVs (eight
    // words copied), then UpdateUVs.
    virtual void SetUVs(uint32_t index, const BillboardUVs* uvs);
    // vt+0xb8 0x0005d428 CBillboardList2d_vfB8 (XXL2 LinkTextureToBillboard): with both in range and a brush, the
    // brush takes the texture, the link is stored and the billboard shown; 1 then.
    virtual int32_t LinkTextureToBillboard(uint32_t texture, uint32_t billboard);
    // vt+0xbc 0x0005d320 CBillboardList2d_ResetItemBrush (XXL2 RemoveTextureFromBillboard): a billboard below the count
    // gets a new brush and no link, the list's colour (SetColor with a copy) and is built again (its result).
    virtual int32_t RemoveTextureFromBillboard(uint32_t billboard);
    // vt+0xc0 0x0005dd50 CBillboardList2d_vfC0 (XXL2 SetTexture): slot `index` (below the slot count) takes `texture`
    // (the old one destroyed, the new one's count raised) and every billboard linked to the slot is linked again; 1.
    virtual int32_t SetTexture(RwTexture* texture, uint32_t index);
    // vt+0xc4 0x0005d240 / +0xc8 0x0005d228 (XXL2 Enable / DisableStretchToAspectRatio): flag bit 2.
    virtual void EnableStretchToAspectRatio() { m_baFlags = static_cast<uint8_t>((m_baFlags & ~0x4u) | 0x4u); }
    virtual void DisableStretchToAspectRatio() { m_baFlags = static_cast<uint8_t>(m_baFlags & 0xfbu); }
    virtual void SetAlignType(uint8_t type) { m_ui8AlignType = type; }  // vt+0xcc 0x0005c858
    virtual void SetSpacing(float spacing) { m_f32Spacing = spacing; }  // vt+0xd0 0x0005c868
    // vt+0xd4 0x0005cf80 / +0xd8 0x0005cf50 (XXL2 ShowBillboard / HideBillboard): the show byte set / cleared; 0 when
    // `index` is above the count. BUG(original): the test lets `index` == count through (a byte past the used ones).
    virtual int32_t ShowBillboard(uint32_t index);
    virtual int32_t HideBillboard(uint32_t index);

    // 0x0005c9d0 CBillboardList2d_ClearBillboards (XXL2 DestroyBillboards): every path and brush destroyed, then the
    // path, link, brush, show and UV blocks freed and emptied.
    void DestroyBillboards();
    // 0x0005c920 CBillboardList2d_FreeTextures_maybe (XXL2 DestroyTextures; FreeMemory inlines it): every texture
    // destroyed, the block freed and emptied.
    void DestroyTextures();

    TVector<Rt2dPath*, 5> m_vpBillboards;         // +0x28
    TVector<int32_t, 5> m_vi32LinkedTextures;     // +0x34 the texture slot of each billboard, -1 for none
    TVector<Rt2dBrush*, 5> m_vpBrushes;           // +0x40
    TVector<uint8_t, 5> m_vbShowBillboards;       // +0x4c
    uint32_t m_Color;                             // +0x58 CColor, read raw (RwRGBA bytes)
    TVector<RwTexture*, 5> m_vpTextures;          // +0x5c (XXL2 CTexture*; the PS3 destroys them as RwTextures)
    CVector2 m_vBillboardsSize;                   // +0x68
    TVector<BillboardUVs, 5> m_vvUVs;             // +0x70
    uint8_t m_ui8AlignType;                       // +0x7c 0 right, 1 left, 2 up, 3 down
    uint8_t m_pad7d[3];
    float m_f32Spacing;                           // +0x80
};
DOTD_ASSERT_SIZE(CBillboardList2d::BillboardUVs, 0x20);
DOTD_ASSERT_SIZE(CBillboardList2d, 0x84);
DOTD_ASSERT_OFFSET(CBillboardList2d, m_vpBillboards, 0x28);
DOTD_ASSERT_OFFSET(CBillboardList2d, m_vi32LinkedTextures, 0x34);
DOTD_ASSERT_OFFSET(CBillboardList2d, m_vpBrushes, 0x40);
DOTD_ASSERT_OFFSET(CBillboardList2d, m_vbShowBillboards, 0x4c);
DOTD_ASSERT_OFFSET(CBillboardList2d, m_Color, 0x58);
DOTD_ASSERT_OFFSET(CBillboardList2d, m_vpTextures, 0x5c);
DOTD_ASSERT_OFFSET(CBillboardList2d, m_vBillboardsSize, 0x68);
DOTD_ASSERT_OFFSET(CBillboardList2d, m_vvUVs, 0x70);
DOTD_ASSERT_OFFSET(CBillboardList2d, m_ui8AlignType, 0x7c);
DOTD_ASSERT_OFFSET(CBillboardList2d, m_f32Spacing, 0x80);
