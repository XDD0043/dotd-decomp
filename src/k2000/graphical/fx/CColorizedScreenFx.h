// CColorizedScreenFx.h - full-screen colour fades (key 0xccd, vtable 0xb17528, size 0x4c). Original unit:
// CColorizedScreenFx.cpp (0xb01f0-0xb1580). XXL2: KGL/Main/ScreenFx/CColorizedScreenFx.h derives it from
// IScreenFx; DotD from IRendableObject (its Create stores the IRendableObject vtable 0xb17218, its
// IsKindOfClass tests 0xccd, 0xa8d, 0xc). The members fill the 0x34 bytes exactly in XXL2's order;
// only m_pCSData is confirmed (PostLoad clears it, as XXL2's), the others are _maybe.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/graphical/IRendableObject.h"

class CColorizedScreenData;

class CColorizedScreenFx : public IRendableObject {
public:
    DOTD_CLASS_KEY(kCategoryGraphical, 0x33)
    DOTD_DECLARE_FACTORIES(CColorizedScreenFx)

    CColorizedScreenFx();                 // 0x000b07a8 CColorizedScreenFx_Create (inlined)
    ~CColorizedScreenFx() override {}     // STUB(C1.6): 0x9a0948 / 0x9a0900
    // vt+0x08 0x9a07e0
    int32_t IsKindOfClass(uint32_t key) override { return key == 0xccd || key == 0xa8d || key == 0xc; }
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x000b05e8 CColorizedScreenFx_Load
    int32_t PostLoad(int32_t type) override;            // vt+0x30 0x000b0840 CColorizedScreenFx_PostLoad
    // vt+0x58 0x000b1170 CColorizedScreenFx_UpdateAndEnqueue: the fade step (the frame clock is the
    // engine's; the PS3 passes it), then the enqueue into the frame's accumulators (family gfx).
    void UpdateAndExtract(float maxDistanceSquared, RenderQueue** stages, IKTime* frameClock, RwCamera* camera, int32_t distanceCull) override;
    // vt+0x5c 0x000b10e8 CColorizedScreenFx_Render: when shown (+0x14 bit 0x100), the full-screen quad in
    // the current colour (+0x24) with the blend of the table entry +0x3c (DrawScreenColorQuad).
    void Render() override;
    int32_t CanBeUpdated() override;                    // vt+0x70 0x9a0818 CColorizedScreenFx_CanBeUpdated
    void ComputeSortingCoef(int32_t sortingOrder) override;  // vt+0x74 0x000b0c80 (by the sort mode)

    // XXL2 CSmoothedCColorLinear (0x1c bytes): a colour moving towards its target at m_fSpeed (in units of
    // 255 per second), kept both as floats and as the CColor the draw reads. The member names are ours
    // (XXL2 has the class, not its members); the use is CColorizedScreenFx_UpdateAndEnqueue's.
    struct SmoothedColor {
        uint8_t m_cTarget[4];        // +0x00 (fx +0x20)
        uint8_t m_cCurrent[4];       // +0x04 (fx +0x24) the colour drawn (bytes r, g, b, a)
        float m_fSpeed;              // +0x08 (fx +0x28)
        float m_afCurrent[4];        // +0x0c (fx +0x2c) r, g, b, a as floats
    };

    // The m_BitProperties bits (IRendableObject +0x14) this class uses.
    enum : uint32_t {
        kQueueIndexMask = 0x1f,      // with kExplicitQueue: the accumulator to enqueue into
        kExplicitQueue = 0x20,
        kActive = 0x100,             // updated and drawn; cleared when a fade ends (unless kHold)
        kHold = 0x200,               // _maybe: keep drawing the end colour (ApplyData: data bit 3)
        kColorModeShift = 10,        // 2 bits: 0 no fade, 1 primary -> secondary, 2 there and back
        kSortModeShift = 12,         // 2 bits: the render queue (ApplyData: from data bits 0-1)
        kUnscaledTime = 0x4000,      // run while the clock is paused (ApplyData: data bit 2)
    };

    // 0x000b0378 CColorizedScreenFx_StartColorFade_maybe (XXL2 CColorizedScreenFx::Start(CColor, CColor,
    // Float32, Float32, ...); order of the PS3 arguments: the two blend times in f1/f2, then the colours
    // and modes).
    void StartColorFade(float blendPrimary, float blendSecondary, const uint8_t* primary, uint32_t blendMode,
                        uint32_t sortMode, uint32_t colorMode, const uint8_t* secondary);
    // 0x000b0b00 CColorizedScreenFx_ApplyData_maybe: starts the fade a CColorizedScreenData describes.
    void ApplyData(CColorizedScreenData* data);

    uint8_t m_cPrimaryColor[4];      // +0x18
    uint8_t m_cSecondaryColor[4];    // +0x1c
    SmoothedColor m_scColor;         // +0x20
    uint32_t m_eBlendMod;            // +0x3c
    float m_fBackBlendSpeed;         // +0x40 the speed back to the primary colour (colour mode 2)
    float m_fColorTime;              // +0x44 _maybe (not used by the fade code)
    CColorizedScreenData* m_pCSData; // +0x48 the data last applied; PostLoad sets 0
};
DOTD_ASSERT_SIZE(CColorizedScreenFx, 0x4c);
DOTD_ASSERT_OFFSET(CColorizedScreenFx, m_scColor, 0x20);
DOTD_ASSERT_OFFSET(CColorizedScreenFx, m_eBlendMod, 0x3c);
DOTD_ASSERT_OFFSET(CColorizedScreenFx, m_fBackBlendSpeed, 0x40);
DOTD_ASSERT_OFFSET(CColorizedScreenFx, m_pCSData, 0x48);
DOTD_ASSERT_SIZE(CColorizedScreenFx::SmoothedColor, 0x1c);
