// CVector2.h - the engine's 2-vector and 2D box (XXL2: K/KUL/CVector2/CVector2.h, CVector2 m_fX, m_fY;
// K/KUL/CBox2D/CBox2D.h, CBox2D m_inf, m_sup). Plain data, as on the PS3.
#pragma once

#include "k2000/core/Layout.h"

struct CVector2 {
    float m_fX;  // +0x00
    float m_fY;  // +0x04
};
DOTD_ASSERT_SIZE(CVector2, 0x8);

struct CBox2D {
    CVector2 m_inf;  // +0x00
    CVector2 m_sup;  // +0x08
};
DOTD_ASSERT_SIZE(CBox2D, 0x10);
