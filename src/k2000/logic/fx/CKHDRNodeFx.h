// CKHDRNodeFx.h - the HDR effect (key 0xf8c, vtable 0xb1ce78, size 0x50). Original unit: CKHDRNodeFx.cpp.
// XXL2: K/KServices/KServiceFx/Effects/CKHDRNodeFx.h, the same members in the same order (XXL2's Load
// reads m_pHDRCurData, then m_pHDRDefaultData, as the PS3 Load reads +0x48, then +0x44). DotD has a second
// pair of speeds: +0x18 / +0x1c move the default data, +0x20 / +0x24 the current data (Update and SetDataAndOwner
// read them so), and the smoothed colour starts at +0x28 with XXL2's 0x1c-byte layout.
//
// The effect keeps the post-rendering object's HDR on (CPostRenderingFx +0x14 bit 0x200) and points its HDR data
// (+0x44) at the default data, or at the current data while a list of data is active, while it blends their
// intensities and colours towards the data the spawn points (and the fury, its own messages) give it.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/fx/IKNodeFx.h"

class CHDRData;
class IKTime;

class CKHDRNodeFx : public IKNodeFx {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x3e)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9ac420
        return key == 0xf8c || key == 0x148c || key == 0x154c || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKHDRNodeFx)

    // XXL2 CSmoothedCColorLinear (0x1c bytes): a colour moving towards its target at m_fCurrentSpeed (in units of 255
    // per second), the channels kept as floats.
    struct SSmoothedColor {
        uint8_t m_TargetedColor[4];  // +0x00 RGBA
        uint8_t m_CurrentColor[4];   // +0x04 RGBA
        float m_fCurrentSpeed;       // +0x08
        float m_fdRed;               // +0x0c
        float m_fdGreen;             // +0x10
        float m_fdBlue;              // +0x14
        float m_fdAlpha;             // +0x18
    };
    // A list entry of the data a list effect blends to (0xc bytes from the pool 0x00ceaa40).
    struct SDataNode {
        IKSerializable* m_pData;         // +0x00 CKHDRFxData
        const IKSerializable* m_pOwner;  // +0x04
        SDataNode* m_pNext;              // +0x08
    };

    CKHDRNodeFx();  // inlined in 0x001bf4c8 CKHDRNodeFx_Create
    ~CKHDRNodeFx() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001bfab0 CKHDRNodeFx_Load
    int32_t PostLoad(int32_t type) override;            // vt+0x30 0x001bf088 CKHDRNodeFx_PostLoad
    void Destroy() override {}                          // vt+0x10 0x001befa0 CKHDRNodeFx_Destroy (empty: the node kept)
    void RecursiveRegistration(int32_t type) override;  // vt+0x24 0x001befa8
    void Vf64() override;                               // vt+0x64 0x001bf0b0 CKHDRNodeFx_Start
    void Vf68() override { Stop(); }                    // vt+0x68 0x001bf0c0 CKHDRNodeFx_Interrupt_maybe: vt+0x6c
    void Stop() override;                               // vt+0x6c 0x001bf528 CKHDRNodeFx_Stop
    IKFxData* GetFxData() override { return reinterpret_cast<IKFxData*>(m_pData); }  // vt+0x80 0x009ac470
    void SetFxData(IKFxData*) override {}               // vt+0x84 0x009ac478 (empty)
    void SetDataAndOwner(IKFxData* data, const IKSerializable* owner) override;  // vt+0x8c 0x001bfc00

    void Update(IKTime* frameClock) override;           // vt+0x78 0x001bf700 CKHDRNodeFx_Update
    // 0x001bf650 CKHDRNodeFx_StopWithFadeTime_maybe: the default intensity speed = `fade`; a data list let go (the
    // current data copied into the default data first when `fade` is above 0); the owner and the default data cleared.
    void StopWithFadeTime(float fade);
    // 0x001c0200 CKHDRNodeFx_StartBlendToSetting_maybe: the list entry of (`data`, `owner`) removed; the last entry blends
    // the default data from the current data towards `data` (the owner taken), another one (when the current data is
    // not moving) the current data towards `data`.
    void StartBlendToSetting(IKSerializable* data, const IKSerializable* owner);

    // 0x001bf188 CKHDRNodeFx_StepColorTowardTarget_maybe: `target`'s intensity moved towards `source`'s (or 0) by
    // intensitySpeed * dt and its colour to the smoothed colour, which moves towards `source`'s colour (or white) by
    // colorSpeed * dt * 255; true while either has not arrived.
    bool StepColorTowardTarget(float intensitySpeed, float colorSpeed, float dt, CHDRData* target, const CHDRData* source,
                               SSmoothedColor* color);

    SDataNode* m_lDataList;               // +0x14 XXL2 FxDataList; the constructor sets 0
    float m_fDefaultIntensitySpeed;       // +0x18 PostLoad sets 0
    float m_fDefaultColorSpeed;           // +0x1c PostLoad sets 0
    float m_fCurColorSpeed;               // +0x20 PostLoad sets 0
    float m_fCurIntensitySpeed;           // +0x24 PostLoad sets 0
    SSmoothedColor m_scCurColor;          // +0x28
    CHDRData* m_pHDRDefaultData;          // +0x44 CHDRData
    CHDRData* m_pHDRCurData;              // +0x48 CHDRData
    IKSerializable* m_pData;              // +0x4c XXL2 CKHDRFxData*; PostLoad sets 0
};
static_assert(CKHDRNodeFx::kClassKey == 0xf8c, "key");
DOTD_ASSERT_SIZE(CKHDRNodeFx::SSmoothedColor, 0x1c);
DOTD_ASSERT_SIZE(CKHDRNodeFx, 0x50);
DOTD_ASSERT_OFFSET(CKHDRNodeFx, m_lDataList, 0x14);
DOTD_ASSERT_OFFSET(CKHDRNodeFx, m_fCurIntensitySpeed, 0x24);
DOTD_ASSERT_OFFSET(CKHDRNodeFx, m_scCurColor, 0x28);
DOTD_ASSERT_OFFSET(CKHDRNodeFx, m_pHDRDefaultData, 0x44);
DOTD_ASSERT_OFFSET(CKHDRNodeFx, m_pHDRCurData, 0x48);
DOTD_ASSERT_OFFSET(CKHDRNodeFx, m_pData, 0x4c);
