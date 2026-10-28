// CSmoothedCColorLinear.h - a colour that moves linearly toward a target (XXL2 CSmoothedCColorLinear,
// 0x1c bytes there). Taken as 0x24 bytes for CKFilterNode2dFx (0x3c), whose size is XXL2's layout exactly when it
// is (_maybe; the two extra words put last). CKHDRNodeFx's colour is XXL2's 0x1c bytes (at +0x28, after four speeds:
// its Update and SetDataAndOwner, C2.4 step 8), so the filter's two words may be such fields too. Not read by any Load.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"

struct CSmoothedCColorLinear {
    uint32_t m_TargetedColor;  // +0x00 XXL2 CColor
    uint32_t m_CurrentColor;   // +0x04 XXL2 CColor
    float m_fCurrentSpeed;     // +0x08
    float m_fdRed;             // +0x0c
    float m_fdGreen;           // +0x10
    float m_fdBlue;            // +0x14
    float m_fdAlpha;           // +0x18
    uint32_t m_unk1c;          // +0x1c DotD
    uint32_t m_unk20;          // +0x20 DotD
};
DOTD_ASSERT_SIZE(CSmoothedCColorLinear, 0x24);
