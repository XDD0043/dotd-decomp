// CKAnimatedCameraData.h - the settings of an animated camera (DotD; not in XXL2) (key 0x9e8c, vtable 0xb2fad0, size 0xb0). Original unit: CKAnimatedCameraData.cpp.
// Five parallel arrays of 12 entries; the Load reads the first count (a byte, at most 12) of each.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/core/IKSerializable.h"

class IKFile;

class CKAnimatedCameraData : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x27a)
    int32_t IsKindOfClass(uint32_t key) override { return key == 0x9e8c || key == 0xc; }  // vt+0x08 0x9cd2f8
    DOTD_DECLARE_FACTORIES(CKAnimatedCameraData)

    // 0x005c0a58 CKAnimatedCameraData_Create: the vtable only (as the dead CKAnimatedCameraData_Construct 0x5c0698).
    CKAnimatedCameraData() {}
    ~CKAnimatedCameraData() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x005c1370 CKAnimatedCameraData_Load

    // The queries CKAnimatedCamera_Start_maybe makes (step 5, FX).
    // vt+0x50 0x005c0b90 CKAnimatedCameraData_PickAnimation_maybe: two rand draws (Rand_Int, each & 0xffff scaled to 0..100): with the
    // first below the chance (+0x04), the second picks one of the enabled entries (+0x08) by its weight (+0x14), from
    // the first; `*index` = that entry. 0 when the chance fails or no weight interval holds the draw.
    virtual uint8_t PickAnimation(uint32_t* index);
    // vt+0x54 0x009cd278 / +0x58 0x009cd2a8 / +0x5c 0x009cd2d0: entry `index`'s +0x44 (1.0 past the 12), +0x74 (0.0 past
    // the 12) and +0xa4 (0 past the 12).
    virtual float GetSpeed(uint32_t index) const { return index < 12 ? m_aUnk44[index] : 1.0f; }
    virtual float GetUnk74(uint32_t index) const { return index > 11 ? 0.0f : m_aUnk74[index]; }
    virtual uint8_t GetAlignToCamera(uint32_t index) const { return index < 12 ? m_aUnkA4[index] : 0; }
    virtual void Vf60() {}  // vt+0x60 0x005c06b8 CKAnimatedCameraData_vf60 (empty)
    // vt+0x30 0x005c0b28 CKAnimatedCameraData_PostLoad: vt+0x60, then 1.
    int32_t PostLoad(int32_t /*type*/) override {
        Vf60();
        return 1;
    }

    float m_unk04;         // +0x04 100.0 in LVL010
    uint8_t m_aUnk08[12];  // +0x08 read with m_aUnk14, one byte and one word per entry
    float m_aUnk14[12];    // +0x14
    float m_aUnk44[12];    // +0x44 1.0 in LVL010
    float m_aUnk74[12];    // +0x74 the Load fills the unread tail with 0.2
    uint8_t m_aUnkA4[12];  // +0xa4 the Load fills the unread tail with 1
};
DOTD_ASSERT_SIZE(CKAnimatedCameraData, 0xb0);
DOTD_ASSERT_OFFSET(CKAnimatedCameraData, m_unk04, +0x04);
DOTD_ASSERT_OFFSET(CKAnimatedCameraData, m_aUnk08, +0x08);
DOTD_ASSERT_OFFSET(CKAnimatedCameraData, m_aUnk14, +0x14);
DOTD_ASSERT_OFFSET(CKAnimatedCameraData, m_aUnk44, +0x44);
DOTD_ASSERT_OFFSET(CKAnimatedCameraData, m_aUnk74, +0x74);
DOTD_ASSERT_OFFSET(CKAnimatedCameraData, m_aUnkA4, +0xa4);
