// CKFilterNode2dFx.h - a colour filter on a 2D node (key 0x19cc, vtable 0xb1cb48, size 0x3c). Original
// unit: CKFilterNode2dFx.cpp. XXL2: K/KServices/KServiceFx/Effects/CKFilterNode2dFx.h, the same members
// (with DotD's 0x24-byte CSmoothedCColorLinear the PS3 size is exactly XXL2's layout).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/fx/CSmoothedCColorLinear.h"
#include "k2000/fx/IKNode2dFx.h"

class CKFilterNode2dFx : public IKNode2dFx {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x67)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9abf38
        return key == 0x19cc || key == 0x158c || key == 0x154c || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKFilterNode2dFx)

    CKFilterNode2dFx() {}  // inlined in 0x001b9620 CKFilterNode2dFx_Create: the IKNode2dFx part only
    ~CKFilterNode2dFx() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001b94a8 CKFilterNode2dFx_Load
    // vt+0x24 0x001b94f8 CKFilterNode2dFx_RecursiveRegistration: registered with the saving manager whatever the type, then
    // IKNode2dFx's (0x1d8518: the node's, when set).
    void RecursiveRegistration(int32_t type) override;
    // 0x001b9a18 CKFilterNode2dFx_BeginFadeOut_maybe: for the owner that reserved it, a fade-out over `time` seconds (the
    // node's alpha / time per second); a time not above 0 stops it at once (vt+0x6c).
    void BeginFadeOut(float time, const IKSerializable* owner);

    void Vf64() override;                      // vt+0x64 0x001b9ad0 CKFilterNode2dFx_Start
    void Stop() override;                      // vt+0x6c 0x001b93e0 CKFilterNode2dFx_Stop
    void Update(IKTime* frameClock) override;  // vt+0x78 0x001b9678 CKFilterNode2dFx_Update
    IKFxData* GetFxData() override;            // vt+0x80 0x009abf80 [inline]
    void SetFxData(IKFxData* data) override;   // vt+0x84 0x009abf88 [inline]

    IKSerializable* m_pFilterData;   // +0x14 XXL2 CKFilterFxData*; not set by the constructor or Load
    CSmoothedCColorLinear m_sColor;  // +0x18
};
static_assert(CKFilterNode2dFx::kClassKey == 0x19cc, "key");
DOTD_ASSERT_SIZE(CKFilterNode2dFx, 0x3c);
DOTD_ASSERT_OFFSET(CKFilterNode2dFx, m_pFilterData, 0x14);
DOTD_ASSERT_OFFSET(CKFilterNode2dFx, m_sColor, 0x18);
