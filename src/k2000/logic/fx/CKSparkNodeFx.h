// CKSparkNodeFx.h - the spark effect node (key 0x244c, vtable 0xb1d970, size 0x1c). Original unit:
// CKSparkNodeFx.cpp (0x1d3e68-0x1d4890). Its data is CKSparkFxData (0x24cc). Not in XXL2; names ours.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/fx/IKNodeFx.h"

class CKSparkNodeFx : public IKNodeFx {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x91)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9ad3f0
        return key == 0x244c || key == 0x148c || key == 0x154c || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKSparkNodeFx)

    CKSparkNodeFx() {}  // inlined in 0x001d4640 CKSparkNodeFx_Create: the IKNodeFx part only
    ~CKSparkNodeFx() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001d44c8 CKSparkNodeFx_Load
    void RecursiveRegistration(int32_t type) override;  // vt+0x24 0x001d4548 CKSparkNodeFx_RecursiveRegistration
    IKFxData* GetFxData() override { return reinterpret_cast<IKFxData*>(m_pFxData); }  // vt+0x80 0x9ad438
    void SetFxData(IKFxData* data) override { m_pFxData = reinterpret_cast<IKSerializable*>(data); }  // vt+0x84 0x9ad440
    // vt+0x64 0x001d4260 CKSparkNodeFx_Start: running (bit 0 cleared), the node shown (vt+0x5c); with the data's hot
    // spot (+0x10) the node hangs under it (vt+0xa0) at its own matrix times the data's (+0x14), else under the data's
    // parent (+0x0c, vt+0x9c) at the data's matrix; its world matrix updated (vt+0x50), the data's spark parameters
    // (+0x08) taken and the sparks started.
    void Vf64() override;
    // vt+0x6c 0x001d41a0 CKSparkNodeFx_Stop: stopped (bit 0), the node hidden (vt+0x60), the live sparks released,
    // the node back under the dynamic scene root (vt+0x9c), the copied parameters' texture (+0x94) cleared.
    void Stop() override;
    // vt+0x78 0x001d4788 CKSparkNodeFx_Update: stopped once the spark node is off (+0x40).
    void Update(IKTime* frameClock) override;
    // vt+0x9c 0x001d3eb8 CKSparkNodeFx_ExtraSlot9C: the node moved under `parent` (the engine's dynamic scene root when
    // null), out of its old parent (vt+0x78) into the new one (vt+0x70), unless it is there already.
    void ReparentNode(IKSerializable* parent);
    // vt+0xa0 0x001d46c8 CKSparkNodeFx_ExtraSlotA0: the node hung under the hot spot (CSGHotSpot_AttachVolume); a null
    // hot spot reparents it to the dynamic scene root (vt+0x9c).
    void AttachNodeToHotSpot(IKSerializable* hotSpot);
    // The spark node's (+0x18, its CKSparkParam +0x50) parameter setters the fire breath shapes its burst with:
    // 0x001d3f88 CKSparkNodeFx_SetParamVec2_40_maybe (+0x40 / +0x44), 0x001d3fd8 .._SetParamVec2_50_maybe (+0x50 / +0x54),
    // 0x001d4028 .._SetParamFloat_68_maybe (+0x68), 0x001d4048 .._SetParamVec3_10_maybe (+0x10..), 0x001d40b0
    // .._SetParamVec3_1c_maybe (+0x1c..).
    void SetParamVec2_40(const float* v);
    void SetParamVec2_50(const float* v);
    void SetParamFloat_68(float value);
    void SetParamVec3_10(const float* v);
    void SetParamVec3_1c(const float* v);

    IKSerializable* m_pFxData;  // +0x14 the inline GetFxData/SetFxData (0x9ad438/0x9ad440) use it
    CNode* m_pSparkNode;        // +0x18 Load (type 0) copies m_pNode here (Ghidra draft: CSparkNodeFx*)
};
static_assert(CKSparkNodeFx::kClassKey == 0x244c, "key");
DOTD_ASSERT_SIZE(CKSparkNodeFx, 0x1c);
DOTD_ASSERT_OFFSET(CKSparkNodeFx, m_pFxData, 0x14);
DOTD_ASSERT_OFFSET(CKSparkNodeFx, m_pSparkNode, 0x18);

// 0x001d4698 StopOwnedSparkEffect_maybe (CKSparkNodeFx.cpp): when `owner` holds the effect's reservation, its spark
// node (+0x18) stops bursting (+0x41 = 1: the sparks end with the last one).
void StopOwnedSparkEffect(CKSparkNodeFx* effect, const IKSerializable* owner);
