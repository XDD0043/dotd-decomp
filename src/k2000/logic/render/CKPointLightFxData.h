// CKPointLightFxData.h - the data of a point-light effect (key 0xaa8c, vtable 0xb1d580, size 0x38).
// Original unit: CKPointLightFxData.cpp (0x1cf310-0x1cfa48). Its node is CKPointLightNodeFx (0xaa4c). Not in
// XXL2; names ours. The colour keys are a CurveKeys list like CLightComponent's.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/IKFxData.h"
#include "k2000/math/CurveKeys.h"

class CKPointLightFxData : public IKFxData {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x2aa)
    DOTD_DECLARE_FACTORIES(CKPointLightFxData)

    CKPointLightFxData();  // inlined in 0x001cf790 CKPointLightFxData_Create

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001cf920 CKPointLightFxData_Load
    // vt+0x30 PostLoad 0x1cf370 (stays the default in C2.1).
    uint32_t GetAssociatedFxClassIdentifier() override { return 0xaa4c; }  // vt+0x54 0x1cf360

    // +0x08/+0x0c object references (Ghidra draft: CKCurve2DCpnt*; LVL010 references class 0x5ac6).
    // EvaluateRadiusLooped / EvaluateIntensityLooped (0x1cf810/0x1cf898) _maybe read them.
    IKSerializable* m_unk08;
    IKSerializable* m_unk0c;
    TVector<CurveKey, 20> m_colorKeys;  // +0x10 (CurveKeys_Load); the constructor allocates 20 keys
    float m_unk1c;                      // +0x1c
    float m_unk20;                      // +0x20
    uint32_t m_unk24[5];                // +0x24 not set by the constructor or Load
};
static_assert(CKPointLightFxData::kClassKey == 0xaa8c, "key");
DOTD_ASSERT_SIZE(CKPointLightFxData, 0x38);
DOTD_ASSERT_OFFSET(CKPointLightFxData, m_unk08, 0x08);
DOTD_ASSERT_OFFSET(CKPointLightFxData, m_unk0c, 0x0c);
DOTD_ASSERT_OFFSET(CKPointLightFxData, m_colorKeys, 0x10);
DOTD_ASSERT_OFFSET(CKPointLightFxData, m_unk1c, 0x1c);
DOTD_ASSERT_OFFSET(CKPointLightFxData, m_unk20, 0x20);
