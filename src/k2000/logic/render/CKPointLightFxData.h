// CKPointLightFxData.h - the data of a point-light effect (key 0xaa8c, vtable 0xb1d580, size 0x38).
// Original unit: CKPointLightFxData.cpp (0x1cf310-0x1cfa48). Its node is CKPointLightNodeFx (0xaa4c). Not in
// XXL2; names ours. The colour keys are a CurveKeys list like CLightComponent's.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/IKFxData.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/math/CurveKeys.h"

class CKPointLightFxData : public IKFxData {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x2aa)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9ace40
        return key == 0xaa8c || key == 0x304c || key == 0x6 || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKPointLightFxData)

    CKPointLightFxData();  // inlined in 0x001cf790 CKPointLightFxData_Create

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001cf920 CKPointLightFxData_Load
    // vt+0x30 0x001cf370 CKPointLightFxData_PostLoad: (type 0) no attach node or hot spot, the position the zero vector.
    int32_t PostLoad(int32_t type) override;
    // vt+0x24 0x001cf4f8 CKPointLightFxData_RecursiveRegistration: the FX data base's (nothing), then (type 0) the two
    // curves (+0x08, +0x0c).
    void RecursiveRegistration(int32_t type) override;
    // vt+0x1c 0x001cf758 CKPointLightFxData_MessageProc: 0x1b00 and 0x1b02 are taken (0) without doing anything, the rest
    // returns 1. vt+0x40 GetInfo 0x1cf750 returns 1, vt+0x10 Destroy 0x1cf788 is empty.
    int32_t MessageProc(uint16_t message, void* /*data*/) override { return (message == 0x1b00 || message == 0x1b02) ? 0 : 1; }

    // The looped curves at time `t` (the time wrapped into the period +0x1c, see the .cpp): 0x001cf430
    // CKPointLightNodeFx_EvaluateColorLooped_maybe (the colour keys +0x10), 0x001cf810 .._EvaluateIntensityLooped_maybe
    // (the curve +0x0c), 0x001cf898 .._EvaluateRadiusLooped (the curve +0x08).
    void EvaluateColorLooped(float t, uint8_t out[4]) const;
    float EvaluateIntensityLooped(float t) const;
    float EvaluateRadiusLooped(float t) const;
    uint32_t GetAssociatedFxClassIdentifier() override { return 0xaa4c; }  // vt+0x54 0x1cf360

    // +0x08/+0x0c object references (Ghidra draft: CKCurve2DCpnt*; LVL010 references class 0x5ac6).
    // EvaluateIntensityLooped / EvaluateRadiusLooped (0x1cf810/0x1cf898) _maybe read them.
    IKSerializable* m_pRadiusCurve;
    IKSerializable* m_pIntensityCurve;  // _maybe
    TVector<CurveKey, 20> m_colorKeys;  // +0x10 (CurveKeys_Load); the constructor allocates 20 keys
    float m_fLoopPeriod;                      // +0x1c
    float m_unk20;                      // +0x20
    // +0x24..+0x34 the run-time placement (PostLoad; the effect's owner sets them before the start): the node the light
    // hangs under, else the hot spot, and the position (relative to it).
    IKSerializable* m_pAttachNode;      // +0x24 Ghidra: CAnimatedNode*
    IKSerializable* m_pAttachHotSpot;   // +0x28 a CSGHotSpot
    CVector3 m_vPosition;               // +0x2c
};
static_assert(CKPointLightFxData::kClassKey == 0xaa8c, "key");
DOTD_ASSERT_SIZE(CKPointLightFxData, 0x38);
DOTD_ASSERT_OFFSET(CKPointLightFxData, m_pRadiusCurve, 0x08);
DOTD_ASSERT_OFFSET(CKPointLightFxData, m_pIntensityCurve, 0x0c);
DOTD_ASSERT_OFFSET(CKPointLightFxData, m_colorKeys, 0x10);
DOTD_ASSERT_OFFSET(CKPointLightFxData, m_fLoopPeriod, 0x1c);
DOTD_ASSERT_OFFSET(CKPointLightFxData, m_unk20, 0x20);
