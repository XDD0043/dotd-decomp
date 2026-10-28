// CKTimeScalingNodeFx.h - the time-scaling effect (key 0x27cc, vtable 0xb1db98, size 0x24). Original unit:
// CKTimeScalingNodeFx.cpp (0x1d7d50-0x1d8348, with IKFx's out-of-line methods at its end). Not in XXL2.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/fx/IKNodeFx.h"

class CKTimeScalingFxData;

class CKTimeScalingNodeFx : public IKNodeFx {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x9f)
    DOTD_DECLARE_FACTORIES(CKTimeScalingNodeFx)

    CKTimeScalingNodeFx() {}  // inlined in 0x001d82b8 CKTimeScalingNodeFx_Create: the IKNodeFx part only
    ~CKTimeScalingNodeFx() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001d7f58 CKTimeScalingNodeFx_Load
    int32_t PostLoad(int32_t type) override;            // vt+0x30 0x001d7e00 CKTimeScalingNodeFx_PostLoad
    void Vf64() override;                               // vt+0x64 0x001d7e10 CKTimeScalingNodeFx_Start
    void Vf68() override { Stop(); }                    // vt+0x68 0x001d7e30 CKTimeScalingNodeFx_Interrupt_maybe
    void Stop() override;                               // vt+0x6c 0x001d8238 CKTimeScalingNodeFx_Stop
    void Update(IKTime* frameClock) override;           // vt+0x78 0x001d8108 CKTimeScalingNodeFx_Update
    IKFxData* GetFxData() override;                     // vt+0x80 0x009ad788 (+0x18)
    void SetFxData(IKFxData* /*data*/) override {}      // vt+0x84 0x009ad790 (empty)
    // vt+0x8c 0x001d81d8 CKTimeScalingNodeFx_SetDataAndOwner: a running effect keeps its data unless the new one has a
    // higher priority (+0x10) and is not flagged (+0x08 bit 1).
    void SetDataAndOwner(IKFxData* data, const IKSerializable* owner) override;
    // 0x001d7e70 CKTimeScalingNodeFx_StopIfOwnedBy_maybe: Stop (vt+0x6c) when the effect runs this data for this owner.
    void StopIfOwnedBy(const CKTimeScalingFxData* data, const IKSerializable* owner);

    const IKSerializable* m_pScaleOwner;  // +0x14 the owner given with the data (SetDataAndOwner); not set by the constructor or Load
    CKTimeScalingFxData* m_pData;         // +0x18 PostLoad (0x1d7e00) and Stop set 0
    float m_fElapsed;                     // +0x1c the data's time: Start and SetDataAndOwner set 0, Update adds IKTime +0x20
    float m_fScale;                       // +0x20 the last scale from the data's curve, written to CTimeManager +0x10
};
static_assert(CKTimeScalingNodeFx::kClassKey == 0x27cc, "key");
DOTD_ASSERT_SIZE(CKTimeScalingNodeFx, 0x24);
