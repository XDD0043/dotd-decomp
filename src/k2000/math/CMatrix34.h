// CMatrix34.h - the engine's 3x4 matrix and 3-vector (XXL2: CMatrix34 with m_right, m_ui32Flags, m_up,
// m_at, m_pos and pads; the RwMatrix layout, 0x40 bytes).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"

class IKFile;

struct CVector3 {
    float x, y, z;
};
DOTD_ASSERT_SIZE(CVector3, 0xc);

struct CMatrix34 {
    CVector3 m_right;      // +0x00
    uint32_t m_ui32Flags;  // +0x0c
    CVector3 m_up;         // +0x10
    uint32_t m_ui32pad1;   // +0x1c
    CVector3 m_at;         // +0x20
    uint32_t m_ui32pad2;   // +0x2c
    CVector3 m_pos;        // +0x30
    uint32_t m_ui32pad3;   // +0x3c
};
DOTD_ASSERT_SIZE(CMatrix34, 0x40);

// 0x0023f4c0 CMatrix34_LoadMatrix (was Mat4_Load; XXL2 CMatrix34::LoadMatrix(IKFile*)): one 0x40-byte
// read, then every word byte-swapped (flags and pads included).
void CMatrix34_LoadMatrix(CMatrix34* matrix, IKFile* file);
