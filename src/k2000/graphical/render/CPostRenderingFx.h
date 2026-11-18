// CPostRenderingFx.h - blur/HDR/DOF post-processing (key 0x38d, vtable 0xb17780, size 0x64). Original
// unit: CPostRenderingFx.cpp (0xb4808-0xb5c70). XXL2: KGL/Main/ScreenFx/CPostRenderingFx.h; DotD's Load
// reads XXL2's references and pass counts in XXL2's order, plus one word and three floats.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/graphical/fx/IScreenFx.h"
#include "k2000/math/CMatrix34.h"

class CDistortionScreenFx;
class CKPBuffer;

class CPostRenderingFx : public IScreenFx {
public:
    DOTD_CLASS_KEY(kCategoryGraphical, 0xe)
    DOTD_DECLARE_FACTORIES(CPostRenderingFx)

    CPostRenderingFx();                  // 0x000b4a78 CPostRenderingFx_Create (inlined)
    ~CPostRenderingFx() override {}      // 0x009a0cf0 / 0x009a0ca8 CPostRenderingFx_Destructor / _DeletingDestructor: the vtables only
    // vt+0x08 0x9a0c70
    int32_t IsKindOfClass(uint32_t key) override {
        return key == 0x38d || key == 0xacd || key == 0xa8d || key == 0xc;
    }
    int32_t Load(IKFile* file, int32_t type) override;      // vt+0x2c 0x000b58c0 CPostRenderingFx_Load
    int32_t GetSerializationFlags() override { return 2; }  // vt+0x34 0x9a0c68
    // vt+0x30 0x000b57c8 CPostRenderingFx_PostLoad: the blur and HDR targets registered, the previous camera at the
    // origin looking along z, the CKPBuffer in the renderer's list, the flags cleared.
    int32_t PostLoad(int32_t type) override;
    // vt+0x24 0x000b4858 CPostRenderingFx_RecursiveRegistration: type 0 only, itself registered, then the CKPBuffer's (+0x1c,
    // no null test).
    void RecursiveRegistration(int32_t type) override;
    // vt+0x78 0x000b48f8 CPostRenderingFx_vf78: an empty slot of its own (IScreenFx's vtable ends at +0x74); no caller known.
    virtual void Vf78() {}
    // vt+0x58 0x000b4ad0 CPostRenderingFx_UpdateAndExtract: with an effect on (blur 0x100, HDR 0x200, depth of field
    // 0x400 with the RSX profiles, or the distortion's 0x100) the CKPBuffer and this object into stage 16; else only the
    // main camera's position and direction kept.
    void UpdateAndExtract(float maxDistanceSquared, RenderQueue** stages, IKTime* frameClock, RwCamera* camera, int32_t distanceCull) override;
    // vt+0x5c 0x000b4d28 CPostRenderingFx_Render: the post chain (see the .cpp).
    void Render(IKTime* frameClock) override;

    CDistortionScreenFx* m_pDistortionFx;   // +0x18 read second
    CKPBuffer* m_pPBuffer;                  // +0x1c read first
    IKSerializable* m_pBlurData;            // +0x20 CBlurData; Load sets 0
    uint32_t m_ui32NbBlurGaussienPasses;    // +0x24
    uint32_t m_tBlurExternalRaster;         // +0x28 PostLoad (CKPBuffer_RegisterRenderTarget_maybe)
    CVector3 m_v3PreviousCameraPos;         // +0x2c PostLoad
    CVector3 m_v3PreviousCameraAt;          // +0x38 PostLoad
    IKSerializable* m_pHDRData;             // +0x44 CHDRData; Load sets 0
    uint32_t m_ui32NbHDRGaussienPasses;     // +0x48 read, then Load sets 3 (as XXL2)
    uint32_t m_tHDRExternalRaster;          // +0x4c PostLoad
    IKSerializable* m_pDOFData;             // +0x50 CDOFData; Load sets 0
    uint32_t m_unk54;                       // +0x54 read after the HDR pass count
    float m_unk58;                          // +0x58
    float m_unk5c;                          // +0x5c
    float m_unk60;                          // +0x60
};
DOTD_ASSERT_SIZE(CPostRenderingFx, 0x64);
DOTD_ASSERT_OFFSET(CPostRenderingFx, m_pDistortionFx, 0x18);
DOTD_ASSERT_OFFSET(CPostRenderingFx, m_pPBuffer, 0x1c);
DOTD_ASSERT_OFFSET(CPostRenderingFx, m_pBlurData, 0x20);
DOTD_ASSERT_OFFSET(CPostRenderingFx, m_ui32NbBlurGaussienPasses, 0x24);
DOTD_ASSERT_OFFSET(CPostRenderingFx, m_pHDRData, 0x44);
DOTD_ASSERT_OFFSET(CPostRenderingFx, m_ui32NbHDRGaussienPasses, 0x48);
DOTD_ASSERT_OFFSET(CPostRenderingFx, m_pDOFData, 0x50);
DOTD_ASSERT_OFFSET(CPostRenderingFx, m_unk54, 0x54);
DOTD_ASSERT_OFFSET(CPostRenderingFx, m_unk60, 0x60);
