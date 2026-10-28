// CurveKeys.h - key lists of the colour and gauge curves (CKGaugeCpnt, CLightComponent,
// CKPointLightFxData, the light colour animations). Original unit: CurveKeys.cpp (0x246350-0x246bb8).
// The container is the engine's TVector (it grows in steps of 20 like XXL2's TVector<T, 20, false>);
// the key's names are ours.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/util/TVector.h"

class IKFile;

struct CurveKey {
    uint32_t m_key;          // +0x00 byte-swapped on load
    uint8_t m_valueRaw[4];   // +0x04 read without a swap: the file's little-endian bytes. On the PS3 a
                             // word load of it sees them big-endian; a consumer must do the same.
};
DOTD_ASSERT_SIZE(CurveKey, 0x8);

// 0x002469b8 CurveKeys_Load_maybe: u32 "present"; when non-zero, u32 count and count keys. The block
// grows to the next multiple of 20 keys when it is too small; the count is stored either way.
void CurveKeys_Load(TVector<CurveKey, 20>* keys, IKFile* file);

// 0x00246408 ColorCurve_Evaluate: the colour (r, g, b, a bytes) of the key list at time `t` (see CurveKeys.cpp).
void ColorCurve_Evaluate(float t, uint8_t out[4], const TVector<CurveKey, 20>* keys);
