// CKCameraFogDatas.h - fog settings of a camera (key 0x3a4c, vtable 0xb1a500, size 0x28). Original unit:
// CKCameraFogDatas.cpp (0x143b58-0x144100). Derived straight from IKSerializable. Not in XXL2; names ours.
// The record reads as two (colour, float, float) groups and three more floats (LVL010: 0xff000000, 75,
// 0.0032; 0xff000000, 75, 350, 0.0032, 200, 5), _maybe two fog settings.
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"

class CKCameraFogDatas : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0xe9)
    int32_t IsKindOfClass(uint32_t key) override { return key == 0x3a4c || key == 0xc; }  // vt+0x08 0x9a78b0
    DOTD_DECLARE_FACTORIES(CKCameraFogDatas)

    CKCameraFogDatas() {}  // 0x00143cf8 CKCameraFogDatas_Create: stores the vtable only

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00143de0 CKCameraFogDatas_Load

    // The fog of the main pass and of the far pass, read by the camera service (C2.4 step 6: FogManager_GetMainColor 0x12bfc0,
    // GetMainDensity 0x12bee0, GetColorForFarPass 0x12bf60, GetFarDensity 0x12bda0, GetFarDistance 0x12be20, GetFogEnd
    // 0x12bea0, GetFogStart 0x12be60). The colours are read without a swap: the file's bytes (red, green, blue, alpha).
    uint8_t m_cMainColor[4];  // +0x04
    float m_fUnk08;           // +0x08 (FogManager_GetFogField08 0x12bf20, dead)
    float m_fMainDensity;     // +0x0c
    uint8_t m_cFarColor[4];   // +0x10
    float m_fFarDistance;     // +0x14
    float m_fUnk18;           // +0x18 (FogManager_GetFogField18 0x12bde0)
    float m_fFarDensity;      // +0x1c
    float m_fFogEnd;          // +0x20 the fog end the shader's fog uniform takes (CKSrvCamera_GetFogEnd 0x12bea0)
    float m_fFogStart;        // +0x24 the fog start (CKSrvCamera_GetFogStart 0x12be60)
};
static_assert(CKCameraFogDatas::kClassKey == 0x3a4c, "key");
DOTD_ASSERT_SIZE(CKCameraFogDatas, 0x28);
DOTD_ASSERT_OFFSET(CKCameraFogDatas, m_cMainColor, 0x04);
DOTD_ASSERT_OFFSET(CKCameraFogDatas, m_cFarColor, 0x10);
DOTD_ASSERT_OFFSET(CKCameraFogDatas, m_fFogStart, 0x24);
