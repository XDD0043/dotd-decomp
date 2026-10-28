// CBackgroundCopyRender.h - a screen effect that copies the back buffer into a CKPBuffer (key 0x4d0d,
// vtable 0xb16c90, size 0x24). Original unit: CBackgroundCopyRender.cpp (0x92e00-0x935d0). Not in XXL2;
// the field names are ours (Ghidra struct: pUnk18, flUnk1c, dwUnk20).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/graphical/fx/IScreenFx.h"

class CKPBuffer;

class CBackgroundCopyRender : public IScreenFx {
public:
    DOTD_CLASS_KEY(kCategoryGraphical, 0x134)
    DOTD_DECLARE_FACTORIES(CBackgroundCopyRender)

    CBackgroundCopyRender();                  // 0x00093020 CBackgroundCopyRender_Create (inlined)
    ~CBackgroundCopyRender() override {}      // STUB(C1.6): 0x99c840 / 0x99c7d8
    // vt+0x08 0x99c758
    int32_t IsKindOfClass(uint32_t key) override {
        return key == 0x4d0d || key == 0xacd || key == 0xa8d || key == 0xc;
    }
    int32_t Load(IKFile* file, int32_t type) override;      // vt+0x2c 0x00093438 CBackgroundCopyRender_Load
    int32_t GetSerializationFlags() override { return 2; }  // vt+0x34 0x99c6b8
    int32_t PostLoad(int32_t type) override;                // vt+0x30 0x000931d0 CBackgroundCopyRender_PostLoad
    // vt+0x58 0x00093078 / vt+0x5c 0x000931e0 (CBackgroundCopyRender.cpp)
    void UpdateAndExtract(float maxDistanceSquared, RenderQueue** stages, IKTime* frameClock, RwCamera* camera, int32_t distanceCull) override;
    void Render() override;

    CKPBuffer* m_unk18;  // +0x18 a CKPBuffer reference (read last)
    float m_unk1c;       // +0x1c
    uint8_t m_unk20;     // +0x20
    uint8_t m_unk21;     // +0x21
    uint8_t m_pad22[2];  // +0x22 never written
};
DOTD_ASSERT_SIZE(CBackgroundCopyRender, 0x24);
DOTD_ASSERT_OFFSET(CBackgroundCopyRender, m_unk18, 0x18);
DOTD_ASSERT_OFFSET(CBackgroundCopyRender, m_unk1c, 0x1c);
DOTD_ASSERT_OFFSET(CBackgroundCopyRender, m_unk20, 0x20);
DOTD_ASSERT_OFFSET(CBackgroundCopyRender, m_unk21, 0x21);
