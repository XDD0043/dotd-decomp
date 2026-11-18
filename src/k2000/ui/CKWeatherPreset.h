// CKWeatherPreset.h - a weather preset (key 0x9c6, vtable 0xb2ee28, size 0x4c). Original unit:
// CKWeatherPreset.cpp (0x5ae528-0x5aeb88). Base: IKComponent (IsKindOfClass 0x9cbf48 accepts 0x9c6, 6, 0xc).
// Not in XXL2; names ours. Used by LVL040 (2 objects there).
#pragma once
#include <cstdint>

#include "k2000/components/IKComponent.h"
#include "k2000/core/Layout.h"

class CKWeatherPreset : public IKComponent {
public:
    DOTD_CLASS_KEY(kCategoryComponent, 0x27)
    DOTD_DECLARE_FACTORIES(CKWeatherPreset)

    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9cbf48
        return key == 0x9c6 || key == 0x6 || key == 0xc;
    }

    CKWeatherPreset() {}  // 0x005ae8a8 CKWeatherPreset_Create: stores the vtable only

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x005ae8e8 CKWeatherPreset_Load
    // vt+0x30 PostLoad 0x5ae810 returns 1 (the default). vt+0x24 0x5ae808 (RecursiveRegistration) returns 1 and
    // registers nothing, vt+0x10 0x5ae8e0 (Destroy) is empty: the defaults. 0x5ae6b0 / 0x5ae6e0 / 0x5ae728: the vtable,
    // then IKComponent's destructor (implicit).

    // 0x005ae758 WeatherPreset_CopyFrom_maybe: every field of `other` but +0x40 / +0x44 (CKHkWeatherCenter's
    // ApplyPreset copies those two itself).
    void CopyFrom(const CKWeatherPreset* other);

    float m_unk04[8];      // +0x04 eight byte-swapped words read in one 32-byte block (LVL040: floats)
    uint32_t m_unk24[3];   // +0x24 three byte-swapped words read in one 12-byte block (LVL040: 20, 10, 5)
    uint8_t m_unk30[8];    // +0x30 eight bytes read without a swap (LVL040: two colours, _maybe)
    uint8_t m_unk38[4];    // +0x38 read without a swap, after +0x3c
    uint8_t m_unk3c[4];    // +0x3c read without a swap
    float m_unk40[2];      // +0x40 two byte-swapped words read in one 8-byte block
    uint8_t m_unk48;       // +0x48 one byte
    uint8_t m_pad49[3];
};
static_assert(CKWeatherPreset::kClassKey == 0x9c6, "key");
DOTD_ASSERT_SIZE(CKWeatherPreset, 0x4c);
DOTD_ASSERT_OFFSET(CKWeatherPreset, m_unk04, 0x04);
DOTD_ASSERT_OFFSET(CKWeatherPreset, m_unk24, 0x24);
DOTD_ASSERT_OFFSET(CKWeatherPreset, m_unk30, 0x30);
DOTD_ASSERT_OFFSET(CKWeatherPreset, m_unk38, 0x38);
DOTD_ASSERT_OFFSET(CKWeatherPreset, m_unk3c, 0x3c);
DOTD_ASSERT_OFFSET(CKWeatherPreset, m_unk40, 0x40);
DOTD_ASSERT_OFFSET(CKWeatherPreset, m_unk48, 0x48);
