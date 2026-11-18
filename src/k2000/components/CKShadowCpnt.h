// CKShadowCpnt.h - an object's blob-shadow parameters (key 0x486, vtable 0xb1ed88, size 0x2c). Original
// unit: CKShadowCpnt.cpp. XXL2: K/KServices/KServiceShadow/Cpnt/CKShadowCpnt.h; its Load reads the same
// fields in the same order (six floats, the colour, two floats, four bytes), so the names are XXL2's.
#pragma once
#include <cstdint>

#include "k2000/components/IKComponent.h"
#include "k2000/core/Layout.h"

class CKShadowCpnt : public IKComponent {
public:
    DOTD_CLASS_KEY(kCategoryComponent, 0x12)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9b1180
        return key == 0x486 || key == 0x6 || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKShadowCpnt)

    CKShadowCpnt() {}  // 0x001fe9b0 CKShadowCpnt_Create: the vtable only

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001fea88 CKShadowCpnt_Load
    void SetShadowLong(float value) { m_fShadowLong = value; }    // 0x001fe7e0 CKShadowCpnt_SetFloat04_maybe
    void SetShadowWidth(float value) { m_fShadowWidth = value; }  // 0x001fe7e8 CKShadowCpnt_SetFloat08_maybe

    float m_fShadowLong;               // +0x04
    float m_fShadowWidth;              // +0x08
    float m_fShadowScale;              // +0x0c
    float m_fShadowMinScale;           // +0x10
    float m_fShadowDistanceMax;        // +0x14
    float m_fShadowDistanceThreshold;  // +0x18
    uint8_t m_ShadowColor[4];          // +0x1c XXL2 CColor, read raw (not swapped): the file's byte order
    float m_fSpeedSmoothColor;         // +0x20
    float m_fSpeedSmoothNormal;        // +0x24
    uint8_t m_ui8Priority;             // +0x28
    uint8_t m_ui8IndexTexture;         // +0x29
    uint8_t m_bAlwaysVisible;          // +0x2a
    uint8_t m_bSmoothNormal;           // +0x2b
};
DOTD_ASSERT_SIZE(CKShadowCpnt, 0x2c);
DOTD_ASSERT_OFFSET(CKShadowCpnt, m_fShadowLong, 0x04);
DOTD_ASSERT_OFFSET(CKShadowCpnt, m_ShadowColor, 0x1c);
DOTD_ASSERT_OFFSET(CKShadowCpnt, m_fSpeedSmoothNormal, 0x24);
DOTD_ASSERT_OFFSET(CKShadowCpnt, m_ui8Priority, 0x28);
DOTD_ASSERT_OFFSET(CKShadowCpnt, m_bSmoothNormal, 0x2b);
