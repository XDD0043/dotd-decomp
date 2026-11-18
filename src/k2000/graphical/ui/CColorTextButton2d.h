// CColorTextButton2d.h - a 2D button drawn as text that changes colour when selected (key 0x30d, vtable 0xb159b0,
// size 0x744; XXL2: K/KModules/KGL/2d/CColorTextButton2d.h, bases IKButton2d and IKText2d at +0x28, then
// m_SelectColor). Original unit: CColorTextButton2d.cpp (0x5f768-0x600b0; its Delete factory 0x5f708 sits in
// CBillboardList2d.cpp's range). No game file holds one.
//
// The text part's vtable (CColorTextButton2d's + 0xa0) keeps IKText2d's own text setters (+0x34 SetTextFromLocString,
// +0x38 SetTextClearLocRef) and reaches this class's SetColor (+0x44) and Scale (+0x50) through thunks; dotd's
// IKText2d declares SetColor non-virtual, so only the primary slot (+0x90) dispatches here.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/ui/IKButton2d.h"
#include "k2000/ui/IKText2d.h"

class CColorTextButton2d : public IKButton2d, public IKText2d {
public:
    DOTD_CLASS_KEY(kCategoryGraphical, 0xc)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x997950
        return key == 0x30d || key == 0x2cd || key == 0x24d || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CColorTextButton2d)

    // 0x0005ff30 CColorTextButton2d_Create (= _Construct 0x5fb20 / _Construct_2_maybe 0x5fdf8): the node base, the text
    // part's constructor (0x6b260), the select colour 0.
    CColorTextButton2d() : m_SelectColor(0) {}
    // vt+0x00 / +0x04 0x9979d8 / 0x997a10: the vtable stores only.
    ~CColorTextButton2d() override {}
    // vt+0x10 0x0005fad8 CColorTextButton2d_Destroy: the text part's (Text2dBlock_Destroy 0x6a0c0: FreeMemoryText2D),
    // then IKButton2d's.
    void Destroy() override;
    // vt+0x2c 0x0005fa40 CColorTextButton2d_Load (+ thunk 0x9979b0): IKButton2d's, the text part's, then the select
    // colour (4 raw bytes); every type.
    int32_t Load(IKFile* file, int32_t type) override;
    // vt+0x30 0x0005fdc8 CColorTextButton2d_PostLoad (+ thunk 0x9979c8): the text tokenised (0x6b2d8); 1.
    int32_t PostLoad(int32_t type) override;
    // vt+0x54 0x0005f7e8 CColorTextButton2d_ResetRuntime_maybe (XXL2 FreeMemory): IKNode2d's, the select colour 0.
    void FreeMemory() override;
    // vt+0x58 0x0005f768 CColorTextButton2d_vf58 (XXL2 RecursiveNodeReach): the text part's with the enabled bit.
    void RecursiveNodeReach(uint8_t what, void* data) override;
    // vt+0x64 0x0005fe68 CColorTextButton2d_Show (XXL2 Enable): a disabled button is enabled and its text refreshed
    // from the loc string (0x6bd10).
    void Enable() override;
    // vt+0x78 0x0005f7a8 CColorTextButton2d_GetBoundingRect: the text part's aligned rect at the node's position.
    void GetBoundingBox(CBox2D* box) const override;
    // vt+0x80 0x0005fec0 CColorTextButton2d_vf80 (XXL2 Scale; + thunk 0x997a00): auto-size off, the text box times the
    // scale, the layout (0x6a468) and the empty post-layout hook (0x6a0b0).
    void Scale(const CVector2& scale) override;
    // vt+0x84 0x0005fc30 CColorTextButton2d_vf84 (XXL2 Render): the text drawn while enabled (the original returns its
    // byte).
    void Render(IKTime* time) override;
    // vt+0x88 0x0005fca0 CColorTextButton2d_vf88 (XXL2 Select): an enabled button not yet selected takes the select
    // colour on the text brush; then IKButton2d's Select.
    void Select() override;
    // vt+0x8c 0x0005f920 CColorTextButton2d_vf8C (XXL2 Deselect): a selected button gets the text colour back; then
    // IKButton2d's Deselect.
    void Deselect() override;
    // vt+0x90 0x0005fd50 CColorTextButton2d_vf90 (XXL2 SetColor; + thunk 0x9979c0): the text colour; shown at once
    // unless selected.
    virtual void SetButtonColor(const uint32_t* color);
    // vt+0x94 0x0005f8a8 CColorTextButton2d_vf94 (XXL2 SetSelectColor): the select colour; shown at once when selected.
    virtual void SetSelectColor(const uint32_t* color);

    // The text part's +0x34 / +0x38 slots in this class's vtable: IKText2d's own SetTextFromLocString (0x6c668) and
    // SetTextClearLocRef (0x6c580).
    uint8_t SetTextById(IKSerializable* text) override { return SetTextFromLocString(text); }
    uint8_t SetTextWide(const uint16_t* text) override { return SetTextClearLocRef(text); }

    uint32_t m_SelectColor;  // +0x740 CColor, read raw (XXL2 m_SelectColor)
};
DOTD_ASSERT_SIZE(CColorTextButton2d, 0x744);
DOTD_ASSERT_OFFSET(CColorTextButton2d, m_pLocManager, 0x2c);
DOTD_ASSERT_OFFSET(CColorTextButton2d, m_SelectColor, 0x740);
