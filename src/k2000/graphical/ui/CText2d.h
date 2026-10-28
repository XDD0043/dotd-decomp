// CText2d.h - a text node of a 2D scene (key 0x5cd, vtable 0xb15d00, size 0x748). Original unit:
// CText2d.cpp (0x65e50-0x66e30). XXL2: K/KModules/KGL/2d/CText2d.h, bases IKNode2d and IKText2d (at
// +0x28); XXL2's Load only calls the two base Loads, DotD's then reads two references (+0x740, +0x744).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/ui/IKNode2d.h"
#include "k2000/ui/IKText2d.h"

class CText2d : public IKNode2d, public IKText2d {
public:
    DOTD_CLASS_KEY(kCategoryGraphical, 0x17)
    DOTD_DECLARE_FACTORIES(CText2d)

    CText2d() {}  // 0x00066220 CText2d_Create: the two base constructors, then the vtables
    ~CText2d() override {}
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x998220
        return key == 0x5cd || key == 0x24d || key == 0xc;
    }
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x000669c8 CText2d_Load (+ thunk 0x9982a8)
    int32_t PostLoad(int32_t type) override;            // vt+0x30 0x00066628 CText2d_PostLoad
    // vt+0x58 0x00065f48 CText2d_OnEvent_maybe: the text part's RecursiveNodeReach with the enabled bit.
    void RecursiveNodeReach(uint8_t what, void* data) override;
    // vt+0x64 0x000666b0 CText2d_Show (IKNode2d Enable): through the linked text (+0x740) when +0x744 is
    // enabled, else enabled here and the text refreshed from its loc string.
    void Enable() override;
    // vt+0x80 0x00066958 CText2d_vf80 (XXL2 slot 31 Scale): the text box times the scale, auto-size off,
    // then the layout again.
    void Scale(const CVector2& scale) override;
    // vt+0x84 0x00066290 DrawUITextWidget: IKText2d::Render while enabled (the original returns its byte).
    void Render(IKTime* time) override;
    // vt+0x88 0x00066440 CText2d_SetTextById (also IKText2d vt+0x34, thunk 0x998208): through the linked
    // text (+0x740) when +0x744 is set and that text is enabled, else SetTextFromLocString.
    uint8_t SetTextById(IKSerializable* text) override;
    // vt+0x8c 0x00066398 CText2d_SetTextWide_maybe: through the linked text like SetTextById, else
    // TextData_SetTextClearLocRef. (Not declared as a virtual yet: only CText2d has the slot.)
    uint8_t SetTextWide(const uint16_t* text) override;
    // vt+0x90 0x00066300 CText2d_SetTextAscii: through the linked text like SetTextWide, else the text part's
    // TextData_SetTextAscii. (Not declared as a virtual yet: only CText2d has the slot.)
    void SetTextAscii(const char* text);
    // 0x000664e8 CText2d_InitDefaults_maybe: the defaults of a text made by code (CManager2d_Init_maybe's
    // system text): node and text fields, the engine's loc manager and a new brush.
    void InitDefaults();

    // +0x740 a reference; PostLoad (0x66628, K_LEVEL_PLATEFORMS) calls its vt+0x68 (IKNode2d::Disable_maybe).
    IKSerializable* m_unk740;  // an IKNode2d
    IKSerializable* m_unk744;  // +0x744 a reference
};
DOTD_ASSERT_SIZE(CText2d, 0x748);
DOTD_ASSERT_OFFSET(CText2d, m_pLocManager, 0x2c);
DOTD_ASSERT_OFFSET(CText2d, m_unk740, 0x740);
DOTD_ASSERT_OFFSET(CText2d, m_unk744, 0x744);
