// CColorizedScreenData.h - the parameters of a screen colour filter (key 0x110c, vtable 0xb174d0, size
// 0x1c). Its functions are in CColorizedScreenFx.cpp (0xb01f0-0xb1580). XXL2:
// KModules/kgl/Main/ScreenFx/CColorizedScreenFx.h, the same members read in the same order.
#pragma once
#include <cstdint>

#include "k2000/components/IKComponent.h"
#include "k2000/core/Layout.h"

class CColorizedScreenData : public IKComponent {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x44)
    DOTD_DECLARE_FACTORIES(CColorizedScreenData)

    CColorizedScreenData() {}  // 0x000b0800 CColorizedScreenData_Create: the vtable only

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x000b0d40 CColorizedScreenData_Load
    // vt+0x30 PostLoad 0xb0838 returns 1.

    uint8_t m_baInfos;           // +0x04 XXL2 CBitArray8
    uint8_t m_pad05[3];
    uint8_t m_cPrimary[4];       // +0x08 XXL2 CColor, read without a swap: the file's bytes
    uint8_t m_cSecondary[4];     // +0x0c XXL2 CColor, read without a swap: the file's bytes
    float m_fBlendPrimary;       // +0x10
    float m_fBlendSecondary;     // +0x14
    uint8_t m_ui8BlendMode;      // +0x18
    uint8_t m_ui8ColorMode;      // +0x19
    uint8_t m_pad1a[2];
};
DOTD_ASSERT_SIZE(CColorizedScreenData, 0x1c);
DOTD_ASSERT_OFFSET(CColorizedScreenData, m_baInfos, 0x04);
DOTD_ASSERT_OFFSET(CColorizedScreenData, m_cPrimary, 0x08);
DOTD_ASSERT_OFFSET(CColorizedScreenData, m_cSecondary, 0x0c);
DOTD_ASSERT_OFFSET(CColorizedScreenData, m_fBlendPrimary, 0x10);
DOTD_ASSERT_OFFSET(CColorizedScreenData, m_fBlendSecondary, 0x14);
DOTD_ASSERT_OFFSET(CColorizedScreenData, m_ui8BlendMode, 0x18);
DOTD_ASSERT_OFFSET(CColorizedScreenData, m_ui8ColorMode, 0x19);
