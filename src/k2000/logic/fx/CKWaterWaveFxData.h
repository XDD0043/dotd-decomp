// CKWaterWaveFxData.h - the data of a water-wave effect (key 0x3b8c, vtable 0xb2dcb0, size 0x14). Original
// unit: CKWaterWaveFxData.cpp; Create (0x56ef68) sits in another unit. Its node is CKWaterWaveNodeFx (0x3bcc).
// Not in XXL2; names ours.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/IKFxData.h"

class CKWaterWaveFxData : public IKFxData {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0xee)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9cab48
        return key == 0x3b8c || key == 0x304c || key == 0x6 || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKWaterWaveFxData)

    CKWaterWaveFxData() {}  // inlined in 0x0056ef68 CKWaterWaveFxData_Create: the vtables only

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00571190 CKWaterWaveFxData_Load
    uint32_t GetAssociatedFxClassIdentifier() override { return 0x3bcc; }  // vt+0x54 0x5710f0
    void Destroy() override {}  // vt+0x10 0x005710f8 (empty). vt+0x24 0x00571168 RecursiveRegistration: IKFxData's (nothing).
    // 0x00571100 CKWaterWaveFxData_EvaluateCurve_maybe: the emission interval at `speed`: +0x08 below 0.01 (TOC -0x76a4;
    // bge: an unordered speed goes on), 0 (TOC -0x76a0) above +0x0c, else speed x +0x10 + +0x08 (fused).
    float EvaluateCurve(float speed) const;

    float m_unk08;  // +0x08 (LVL010: 0.5)
    float m_unk0c;  // +0x0c (LVL010: 5)
    float m_unk10;  // +0x10 Load: -m_unk08 / m_unk0c (every type)
};
static_assert(CKWaterWaveFxData::kClassKey == 0x3b8c, "key");
DOTD_ASSERT_SIZE(CKWaterWaveFxData, 0x14);
DOTD_ASSERT_OFFSET(CKWaterWaveFxData, m_unk08, 0x08);
DOTD_ASSERT_OFFSET(CKWaterWaveFxData, m_unk10, 0x10);
