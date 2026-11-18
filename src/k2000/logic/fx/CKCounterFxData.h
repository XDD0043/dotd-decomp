// CKCounterFxData.h - the data of a counter display effect (key 0x58cc, vtable 0xb2df38, size 0x4c): a value out of a
// maximum shown by a CKCounterNodeFx (key 0x590c) as a radial gauge at a point or over a target, coloured by a curve of
// the fill. Original unit: CKCounterFxData.cpp (0x5748c0-0x575810). Not in XXL2; names ours. No game file holds the
// class (C2.8 port-final F04; the field map from port-rest R06's analysis).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/IKFxData.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/math/CurveKeys.h"

class CKCounterNodeFx;

class CKCounterFxData : public IKFxData {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x163)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9cae68
        return key == 0x58cc || key == 0x304c || key == 0x6 || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKCounterFxData)

    // 0x00574fb0 CKCounterFxData_Construct_maybe (also 0x574de8, and inlined in Create / CreateArray): the vtables, the
    // colour keys' block of 20 (Mem_AllocAligned16 0xa0).
    CKCounterFxData();
    // 0x005753c0 / 0x00575428 / 0x00574f38: the keys' block freed, then the component base's destructor.
    ~CKCounterFxData() override;

    void Destroy() override {}  // vt+0x10 0x00574f30 (empty)
    // vt+0x1c 0x00575010 CKCounterFxData_MessageProc: 0x1b00..0x1b06 (a jump table) return 0, the rest 1.
    int32_t MessageProc(uint16_t message, void* data) override;
    // vt+0x24 0x00574dc0: IKFxData's (KStub_Return1_1d8340), the default. vt+0x30 PostLoad: IKFxData's.
    int32_t Load(IKFile* file, int32_t type) override;      // vt+0x2c 0x00575490 CKCounterFxData_Load
    // vt+0x40 0x00574f28 CKCounterFxData_GetInfo: returns 1, as the default.
    uint32_t GetAssociatedFxClassIdentifier() override { return 0x590c; }  // vt+0x54 0x00574910

    // 0x00574978 CKCounterFxData_AcquireNode_maybe: a counter node from the FX service (CKSrvFx::AcquireFx inlined: this
    // data, this owner, started), kept in +0x1c (null when none is free).
    void AcquireNode();
    // 0x00574928 CKCounterNodeFx_SetValueClamped_maybe: the value set to `value` clamped to 0 .. the maximum.
    void SetValueClamped(float value);
    // 0x00574c58 CKCounterFxData_ResetNode_maybe: the node's pulse restarted (CKCounterNodeFx_ResetDisplay_maybe).
    void ResetNode();
    // 0x00574d48 CKCounterFxData_ReleaseNode_maybe: the node fades out (its state 2) and is let go.
    void ReleaseNode();

    IKSerializable* m_pTarget;           // +0x08 a reference (a CSGMovable: the counter stands over its position, flag 2)
    CVector3 m_vPosition;                // +0x0c the counter's position without a target
    float m_fHeight;                     // +0x18 added to the position's y
    CKCounterNodeFx* m_pNode;            // +0x1c the acquired node (the Load clears it)
    TVector<CurveKey, 20> m_colorKeys;   // +0x20 the colour by fill (CurveKeys_Load)
    float m_fScale;                      // +0x2c the gauge's size
    float m_fMinDistance;                // +0x30 flag 1: the camera distance clamped to [+0x30, +0x34]
    float m_fMaxDistance;                // +0x34
    float m_fValue;                      // +0x38 the Load sets the maximum
    float m_fMaxValue;                   // +0x3c
    float m_fFadeInTime;                 // +0x40
    float m_fFadeOutTime;                // +0x44
    uint8_t m_flags;                     // +0x48 bit 0 the size follows the camera distance, bit 1 over the target
    uint8_t m_pad49[3];
};
static_assert(CKCounterFxData::kClassKey == 0x58cc, "key");
DOTD_ASSERT_SIZE(CKCounterFxData, 0x4c);
DOTD_ASSERT_OFFSET(CKCounterFxData, m_pTarget, 0x08);
DOTD_ASSERT_OFFSET(CKCounterFxData, m_vPosition, 0x0c);
DOTD_ASSERT_OFFSET(CKCounterFxData, m_pNode, 0x1c);
DOTD_ASSERT_OFFSET(CKCounterFxData, m_colorKeys, 0x20);
DOTD_ASSERT_OFFSET(CKCounterFxData, m_fScale, 0x2c);
DOTD_ASSERT_OFFSET(CKCounterFxData, m_fValue, 0x38);
DOTD_ASSERT_OFFSET(CKCounterFxData, m_fFadeOutTime, 0x44);
DOTD_ASSERT_OFFSET(CKCounterFxData, m_flags, 0x48);
