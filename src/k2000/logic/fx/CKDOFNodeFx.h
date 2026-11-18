// CKDOFNodeFx.h - the depth-of-field effect (key 0x7fcc, vtable 0xb1c7b8, size 0x20). Original unit:
// CKDOFNodeFx.cpp. Not in XXL2.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/fx/IKNodeFx.h"

class CKDOFNodeFx : public IKNodeFx {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x1ff)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9ab7b0
        return key == 0x7fcc || key == 0x148c || key == 0x154c || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKDOFNodeFx)

    CKDOFNodeFx() {}  // inlined in 0x001b0eb8 CKDOFNodeFx_Create: the IKNodeFx part only
    ~CKDOFNodeFx() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001b10f8 CKDOFNodeFx_Load
    // vt+0x64 0x001b0818 CKDOFNodeFx_Start: running (the stopped bit cleared), the same code as IKNodeFx's.
    void Vf64() override { m_baFxData = static_cast<uint8_t>(m_baFxData & 0xfe); }
    void Destroy() override {}  // vt+0x10 0x001b0728 CKDOFNodeFx_Destroy: empty (the node is kept)
    // vt+0x24 0x001b0730 CKDOFNodeFx_RecursiveRegistration: registered with the saving manager whatever the type, then
    // the CDOFData's (when set).
    void RecursiveRegistration(int32_t type) override;
    // vt+0x30 0x001b07d8 CKDOFNodeFx_PostLoad: no data, blend time 0, the CDOFData's four words 0.
    int32_t PostLoad(int32_t type) override;
    void Vf68() override { Stop(); }  // vt+0x68 0x001b0828 CKDOFNodeFx_Interrupt_maybe: Stop (vt+0x6c)
    // vt+0x6c 0x001b0cd0 CKDOFNodeFx_Stop: stopped; the post-rendering object's depth of field (bit 0x400) off when its
    // path is on (graphic caps 0x200, shaders on, profile mode 6); then vt+0x60 and no data.
    void Stop() override;
    // vt+0x78 0x001b0f10 CKDOFNodeFx_Update: without data the CDOFData blends to 0 over the blend time and the effect stops
    // once it is inactive; with data it blends towards the data's CDOFData. Either way the post-rendering object shows it
    // (bit 0x400, its +0x50).
    void Update(IKTime* frameClock) override;
    // vt+0x8c 0x001b0de8 CKDOFNodeFx_SetDataAndOwner: the data and its fade time (the owner is not kept); the CDOFData
    // takes the post-rendering object's current one (0 without one).
    void SetDataAndOwner(IKFxData* data, const IKSerializable* owner) override;
    // 0x001b0868 CKDOFNodeFx_InterpolateParams_maybe: `current`'s four floats moved towards `target`'s (0 without) by
    // dt / time of the gap, clamped at the target; with time not above 0 they take the target.
    static void InterpolateParams(float time, float dt, IKSerializable* current, const IKSerializable* target);
    // 0x001b0a58 CKDOFFxData_SetBlendTime_maybe (a CKDOFNodeFx method): the blend time.
    void SetBlendTime(float time) { m_fBlendTime = time; }
    // 0x001b0a40 CKDOFFxData_BeginFadeOut_maybe (a CKDOFNodeFx method): the blend time, the owner (+0x08) and +0x1c
    // cleared.
    void BeginFadeOut(float time) {
        m_fBlendTime = time;
        m_pOwner = nullptr;
        m_unk1c = 0;
    }

    float m_fBlendTime;          // +0x14 PostLoad (0x1b07d8) sets 0; SetBlendTime / BeginFadeOut
    // +0x18 the CDOFData reference (LVL000: class 0x10cd); name ours. PostLoad clears its +0x04..+0x10.
    IKSerializable* m_pDOFData;
    IKFxData* m_unk1c;           // +0x1c PostLoad sets 0; SetDataAndOwner: the CKDOFFxData (its +0x08 the target CDOFData)
};
static_assert(CKDOFNodeFx::kClassKey == 0x7fcc, "key");
DOTD_ASSERT_SIZE(CKDOFNodeFx, 0x20);
DOTD_ASSERT_OFFSET(CKDOFNodeFx, m_pDOFData, 0x18);
