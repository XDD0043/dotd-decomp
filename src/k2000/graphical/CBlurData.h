// CBlurData.h - the radial blur screen effect's data (key 0x28d, vtable 0xb178b8, size 0x38). Original
// unit: CDOFData.cpp (the post-rendering datas). XXL2: K/KModules/KGL/Main/ScreenFx/CPostRenderingFxData.h
// (CBlurData), the same members read in the same order.
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"

class CBlurData : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryGraphical, 0xa)
    DOTD_DECLARE_FACTORIES(CBlurData)

    CBlurData() {}  // 0x000b6360 CBlurData_Create: only the vtable
    ~CBlurData() override {}

    // vt+0x2c 0x000b6798 CBlurData_Load (type 0 only)
    int32_t Load(IKFile* file, int32_t type) override;

    int32_t m_eBlendMode;                // +0x04 CMaterial::EBlendMode
    uint8_t m_bActivateMotionSettings;   // +0x08
    uint8_t m_pad09[3];
    float m_fCenterCoefficient;          // +0x0c
    float m_fSpeedCoefficient;           // +0x10
    float m_fRotationSpeedCoefficient;   // +0x14
    float m_fMaxEffectSpeed;             // +0x18
    float m_fBlurGlobalIntensity;        // +0x1c (a heap pointer live: overwritten at runtime)
    float m_fBlurStartOffset;            // +0x20
    float m_fBlurIncOffset;              // +0x24
    float m_fBlurBorderIntensity;        // +0x28
    float m_fBlurCenterIntensity;        // +0x2c
    uint8_t m_ui8NbRadialPasses;         // +0x30
    uint8_t m_pad31[3];
    uint8_t m_cBlurColor[4];             // +0x34 CColor, read raw (file bytes)
};
static_assert(CBlurData::kClassKey == 0x28d, "key");
DOTD_ASSERT_SIZE(CBlurData, 0x38);
DOTD_ASSERT_OFFSET(CBlurData, m_bActivateMotionSettings, 0x08);
DOTD_ASSERT_OFFSET(CBlurData, m_fCenterCoefficient, 0x0c);
DOTD_ASSERT_OFFSET(CBlurData, m_fBlurGlobalIntensity, 0x1c);
DOTD_ASSERT_OFFSET(CBlurData, m_fBlurCenterIntensity, 0x2c);
DOTD_ASSERT_OFFSET(CBlurData, m_ui8NbRadialPasses, 0x30);
DOTD_ASSERT_OFFSET(CBlurData, m_cBlurColor, 0x34);
