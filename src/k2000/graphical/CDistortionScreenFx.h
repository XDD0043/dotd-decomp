// CDistortionScreenFx.h - the screen distortion effect (key 0xc4d, vtable 0xb17618, size 0x38). Its code
// is in CDistortionScreenData.cpp (0xb1580-0xb3170). XXL2: KGL/Main/ScreenFx/CDistortionScreenFx.h
// (m_fTime, m_pLeaf, m_pDistortionData); the DotD field names are ours unless noted.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/graphical/fx/IScreenFx.h"

class CDistortionScreenFx : public IScreenFx {
public:
    DOTD_CLASS_KEY(kCategoryGraphical, 0x31)
    DOTD_DECLARE_FACTORIES(CDistortionScreenFx)

    CDistortionScreenFx();                  // 0x000b1fb0 CDistortionScreenFx_Create (inlined)
    ~CDistortionScreenFx() override {}      // STUB(C1.6): 0x9a0a88 / 0x9a09e8
    // vt+0x08 0x9a09b0
    int32_t IsKindOfClass(uint32_t key) override {
        return key == 0xc4d || key == 0xacd || key == 0xa8d || key == 0xc;
    }
    int32_t Load(IKFile* file, int32_t type) override;      // vt+0x2c 0x000b2378 CDistortionScreenFx_Load
    int32_t GetSerializationFlags() override { return 2; }  // vt+0x34 0x9a0988
    void UpdateAndExtract(float, RenderQueue**, IKTime*, RwCamera*, int32_t) override {}                     // vt+0x58 0xb1570  STUB(C2.7): the distortion grid, started by CKDistortionNodeFx (FX service)
    void Render() override {}                               // vt+0x5c 0xb2c88  STUB(C2.7): drawn by CPostRenderingFx_Draw while its +0x14 bit 0x100 is set (by CKDistortionNodeFx)

    uint32_t m_unk18[3];  // +0x18 PostLoad clears them (grid state); not written by Load
    // +0x24 the grid resolution _maybe: XXL2 reads m_ui8Resol (a byte) in CDistortionScreenData::Load before
    // BuildGrid; DotD reads the byte here and builds the grid in this class's PostLoad (LVL000: 20).
    uint8_t m_ui8Resol;
    uint8_t m_pad25[3];   // +0x25 never written
    uint32_t m_unk28;     // +0x28 Load sets 0
    uint32_t m_unk2c;     // +0x2c PostLoad sets 0
    void* m_unk30;        // +0x30 Load sets 0 (the grid buffers _maybe)
    void* m_unk34;        // +0x34 Load sets 0
};
DOTD_ASSERT_SIZE(CDistortionScreenFx, 0x38);
DOTD_ASSERT_OFFSET(CDistortionScreenFx, m_ui8Resol, 0x24);
DOTD_ASSERT_OFFSET(CDistortionScreenFx, m_unk28, 0x28);
DOTD_ASSERT_OFFSET(CDistortionScreenFx, m_unk30, 0x30);
DOTD_ASSERT_OFFSET(CDistortionScreenFx, m_unk34, 0x34);
