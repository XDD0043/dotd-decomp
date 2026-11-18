// CKTargetCursorNodeFx.h - the target-cursor effect node (key 0x460c, vtable 0xb1da88, size 0x38). Original
// unit: CKTargetCursorNodeFx.cpp. Its data is CKTargetCursorFxData (0x464c). Not in XXL2; names ours.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/fx/IKNodeFx.h"
#include "k2000/math/CMatrix34.h"

class CKTargetCursorNodeFx : public IKNodeFx {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x118)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9ad590
        return key == 0x460c || key == 0x148c || key == 0x154c || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKTargetCursorNodeFx)

    CKTargetCursorNodeFx() {}  // inlined in 0x001d5e70 CKTargetCursorNodeFx_Create: the IKNodeFx part only
    ~CKTargetCursorNodeFx() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001d5ca0 CKTargetCursorNodeFx_Load
    // vt+0x30 0x1d5c48 CKTargetCursorNodeFx_PostLoad: IKNodeFx's, then (level type) the matrix at +0x1c.
    int32_t PostLoad(int32_t type) override;
    void Destroy() override;                            // vt+0x10 0x001d5d88 CKTargetCursorNodeFx_Destroy
    void RecursiveRegistration(int32_t type) override;  // vt+0x24 0x001d5808
    // 0x001d5988 CKTargetCursorNodeFx_StopForOwner_maybe: StopForOwnerWithFadeOut without the release (the hero's
    // StopTargetCursorNow in CKHkS08Hero_19.cpp is a copy of the immediate case).
    void StopForOwner(const IKSerializable* owner, int32_t immediate);

    void Vf64() override;                      // vt+0x64 0x001d63d8 CKTargetCursorNodeFx_Start
    void Stop() override;                      // vt+0x6c 0x001d5fa0 CKTargetCursorNodeFx_Stop: stopped, the cursor hidden
    void Update(IKTime* frameClock) override;  // vt+0x78 0x001d6640 CKTargetCursorNodeFx_Update
    IKFxData* GetFxData() override;            // vt+0x80 0x009ad5d8 [inline]
    void SetFxData(IKFxData* data) override;   // vt+0x84 0x009ad5e0 [inline]

    // 0x001d61a8 CKTargetCursorNodeFx_SetupCursorStateForOwner_maybe: for the reserving `owner`, the appear phase (bit 2,
    // data +0x08 seconds from the data's start alpha / scale +0x10 / +0x14) or, with no appear time, the idle phase at the
    // idle minimum (data +0x34 / +0x28, both growing: bits 4 and 5); the alpha applied.
    void SetupCursorStateForOwner(const IKSerializable* owner);
    // 0x001d7190 StopOwnedEffectWithFadeOut_maybe (CKHkS08Hero_SetSwitchFeedbackFxActive_maybe 0x338130 calls it with 0):
    // for the reserving `owner`, the disappear phase from the current alpha and scale over data +0x0c seconds (bit 3), or
    // the cursor stopped (vt+0x6c) when that time is not positive or `immediate`; the reservation released (vt+0x54).
    void StopForOwnerWithFadeOut(const IKSerializable* owner, int32_t immediate);
    // 0x001d5ec8 CKTargetCursorNodeFx_SetPositionForOwner_maybe (C2.8 meca-hero: the switch feedback): for the reserving
    // `owner` and with a cursor node, the placement's (+0x1c) and the cursor node's position.
    void SetPositionForOwner(const IKSerializable* owner, const CVector3* position);

    // Run-time flags in m_baFxData: bit 2 appearing, bit 3 disappearing, bit 4 the scale grows, bit 5 the alpha grows,
    // bit 6 the matrix kept (no camera facing).
    IKSerializable* m_pFxData;   // +0x14 (Ghidra draft: CKTargetCursorFxData*)
    CNode* m_pCursorNode;        // +0x18 a second scene node (Ghidra draft: CNode*)
    CMatrix34* m_pMatrix1c;      // +0x1c PostLoad: RwMatrixCreate_Thunk; the cursor's placement (Start: identity)
    float m_fPhaseTime;          // +0x20 seconds left in the appear / disappear phase
    uint8_t m_ui8Alpha;          // +0x24 the cursor's alpha
    uint8_t m_pad25[3];
    float m_fScale;              // +0x28 the cursor's scale
    float m_fAngle;              // +0x2c the cursor's roll, degrees (turns at the phase's data rate)
    uint8_t m_ui8StopAlpha;      // +0x30 the alpha when the disappear phase began (StopForOwner 0x1d5988)
    uint8_t m_pad31[3];
    float m_fStopScale;          // +0x34 the scale when the disappear phase began
};
static_assert(CKTargetCursorNodeFx::kClassKey == 0x460c, "key");
DOTD_ASSERT_SIZE(CKTargetCursorNodeFx, 0x38);
DOTD_ASSERT_OFFSET(CKTargetCursorNodeFx, m_pFxData, 0x14);
DOTD_ASSERT_OFFSET(CKTargetCursorNodeFx, m_pCursorNode, 0x18);
DOTD_ASSERT_OFFSET(CKTargetCursorNodeFx, m_fPhaseTime, 0x20);
DOTD_ASSERT_OFFSET(CKTargetCursorNodeFx, m_fAngle, 0x2c);
DOTD_ASSERT_OFFSET(CKTargetCursorNodeFx, m_fStopScale, 0x34);
