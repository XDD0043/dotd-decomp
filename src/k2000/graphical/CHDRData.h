// CHDRData.h - HDR post-processing parameters (key 0x54d, vtable 0xb17860, size 0x14). Its functions are
// in CDOFData.cpp (0xb5c70-0xb6bd8). XXL2: KModules/KGL/Main/ScreenFx/CPostRenderingFxData.h, the same
// members read in the same order.
#pragma once
#include <cstdint>

#include "k2000/components/IKComponent.h"
#include "k2000/core/Layout.h"

class CHDRData : public IKComponent {
public:
    DOTD_CLASS_KEY(kCategoryGraphical, 0x15)
    DOTD_DECLARE_FACTORIES(CHDRData)

    CHDRData() {}  // 0x000b6238 CHDRData_Create: the vtable only

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x000b6650 CHDRData_Load

    uint32_t m_eBlendMode;        // +0x04 XXL2 CMaterial::EBlendMode
    float m_fHDRIntensity;        // +0x08
    uint8_t m_bExtractLuminance;  // +0x0c XXL2 Bool
    uint8_t m_pad0d[3];
    uint8_t m_cHDRColor[4];       // +0x10 XXL2 CColor, read without a swap: the file's bytes
};
DOTD_ASSERT_SIZE(CHDRData, 0x14);
DOTD_ASSERT_OFFSET(CHDRData, m_eBlendMode, 0x04);
DOTD_ASSERT_OFFSET(CHDRData, m_fHDRIntensity, 0x08);
DOTD_ASSERT_OFFSET(CHDRData, m_bExtractLuminance, 0x0c);
DOTD_ASSERT_OFFSET(CHDRData, m_cHDRColor, 0x10);
