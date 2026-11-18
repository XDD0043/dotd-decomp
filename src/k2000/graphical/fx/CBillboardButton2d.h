// CBillboardButton2d.h - a 2D button drawn as a billboard (key 0x64d, vtable 0xb157d0, size 0x70; XXL2:
// K/KModules/KGL/2d/CBillboardButton2d.h, bases IKButton2d and IKBillboard2d at +0x28). Original unit:
// CBillboardButton2d.cpp (0x5be10-0x5c868). No game file holds one (outputs/remake/kp3-class-usage.json).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/ui/IKBillboard2d.h"
#include "k2000/ui/IKButton2d.h"

class CBillboardButton2d : public IKButton2d, public IKBillboard2d {
public:
    DOTD_CLASS_KEY(kCategoryGraphical, 0x19)
    DOTD_DECLARE_FACTORIES(CBillboardButton2d)

    // 0x0005c680 CBillboardButton2d_Create (= CBillboardButton2d_Construct 0x5c310 / _Construct_2 0x5c508): the two
    // base constructors, then the selected colour 0.
    CBillboardButton2d();
    ~CBillboardButton2d() override;                 // vt+0x00 / +0x04 0x997558 / 0x9974f8
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x997468
        return key == 0x64d || key == 0x2cd || key == 0x24d || key == 0xc;
    }
    // vt+0x10 0x0005c2c8 CBillboardButton2d_Destroy: the billboard part's FreeMemoryBillboard2D (0x66c18), then
    // IKButton2d's (0x67ce8).
    void Destroy() override;
    // vt+0x24 0x0005c218 CBillboardButton2d_RecursiveRegistration: outside the save types 4..7 the button registered,
    // then IKNode2d's (0x69848) and the billboard part's (KStub_Return1_66c58: nothing).
    void RecursiveRegistration(int32_t type) override;
    // vt+0x2c 0x0005c180 CBillboardButton2d_Load: IKButton2d's, the billboard part's (0x67598), then the selected
    // colour (4 raw bytes).
    int32_t Load(IKFile* file, int32_t type) override;
    // vt+0x54 0x0005be78 CBillboardButton2d_ResetRuntime_maybe (FreeMemory): IKNode2d's (0x69ce8), the selected colour 0.
    void FreeMemory() override;
    // vt+0x78 0x0005be38 CBillboardButton2d_GetBoundingRect: the billboard part's box at the node position (0x66ef8).
    void GetBoundingBox(CBox2D* box) const override;
    // vt+0x80 0x0005be10 CBillboardButton2d_vf80 (XXL2 Scale): the billboard size times the scale.
    void Scale(const CVector2& scale) override;
    // vt+0x84 0x0005c498 CBillboardButton2d_Draw_maybe (XXL2 Render): when enabled, the quad
    // (DrawUIBillboardShapeWithTransform with the node's rotation, position, alignment and constant scale).
    void Render(IKTime* time) override;
    // vt+0x88 0x0005c038 CBillboardButton2d_vf88 (XXL2 Select): an enabled button not yet selected takes the selected
    // colour on its brush's four corners; then IKButton2d's Select (0x67d78).
    void Select() override;
    // vt+0x8c 0x0005bfb0 CBillboardButton2d_vf8C (XXL2 Deselect): a selected button gets its colour back; then
    // IKButton2d's Deselect (0x67d60).
    void Deselect() override;
    // vt+0x90 0x0005bf38 CBillboardButton2d_vf90 (XXL2 SetColor): the colour; shown at once unless selected.
    virtual void SetButtonColor(const uint32_t* color);
    // vt+0x94 0x0005c428 CBillboardButton2d_vf94 (XXL2 SetSelectColor): the selected colour; shown at once when selected.
    virtual void SetSelectColor(const uint32_t* color);

    uint32_t m_SelectColor;  // +0x6c CColor, read raw (XXL2 m_SelectColor _maybe)
};
DOTD_ASSERT_SIZE(CBillboardButton2d, 0x70);
DOTD_ASSERT_OFFSET(CBillboardButton2d, m_pBillboard, 0x2c);
DOTD_ASSERT_OFFSET(CBillboardButton2d, m_SelectColor, 0x6c);
