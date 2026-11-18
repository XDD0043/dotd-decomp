// CKGaugeCpntUpdater.h - drives a CKGaugeCpnt (key 0x1486, vtable 0xb20d98, size 0x20). Original unit:
// CKGaugeCpntUpdater.cpp (0x24b2e0-0x24bc70). No XXL2 class of this name.
#pragma once
#include <cstdint>

#include "k2000/components/IKComponent.h"
#include "k2000/core/Layout.h"
#include "k2000/logic/ui/CKGaugeCpnt.h"

class KBase730C;

class CKGaugeCpntUpdater : public IKComponent {
public:
    DOTD_CLASS_KEY(kCategoryComponent, 0x52)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9b9f18
        return key == 0x1486 || key == 0x6 || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKGaugeCpntUpdater)

    CKGaugeCpntUpdater() {}  // 0x0024b4d8 CKGaugeCpntUpdater_Create: the vtable only

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0024bad0 CKGaugeCpntUpdater_Load
    int32_t PostLoad(int32_t type) override;            // vt+0x30 0x0024bb60 CKGaugeCpntUpdater_PostLoad
    // 0x0024b368 CKGaugeCpntUpdater_Update_maybe: the gauge's displayed value advanced and sampled (1); without a gauge
    // the sample cleared (0).
    int32_t Update(float dt, GaugeSample* sample);
    // 0x0024bba0 CKGaugeCpntUpdater_EvaluateSample_maybe: the gauge's sample at transformation time `t`
    // (CKGaugeCpnt_EvaluateSample_maybe 0x24a1a8; 1); without a gauge the sample cleared (0). No caller in the original.
    // (vt+0x10 0x24bb98 Destroy: empty, vt+0x24 0x24bb90 RecursiveRegistration: 1, the defaults.)
    int32_t EvaluateSample(float t, GaugeSample* sample);
    // 0x0024b218 SuperGaugeRecord_Reset_maybe: the runtime state cleared (as PostLoad).
    void Reset();

    CKGaugeCpnt* m_pGauge;  // +0x04 (Ghidra draft: CKGaugeCpnt*)
    // The rest is the runtime state; PostLoad (0x24bb60) clears it: 0.0 at +0x08..+0x10, 0 at +0x14 and
    // +0x1c, 0 in the byte at +0x18.
    float m_unk08;          // +0x08 the displayed value
    float m_unk0c;          // +0x0c the previous target (SetGaugeValue)
    float m_unk10;          // +0x10 the target value
    float m_unk14;          // +0x14 the rise / fall delay time (SetGaugeValue clears it with resetAux)
    uint8_t m_unk18;        // +0x18 flashing (the "full" flag)
    uint8_t m_pad19[3];
    float m_fFlashTime;     // +0x1c the flash time (CKGaugeCpnt_UpdateDisplayedValue_maybe)
};
DOTD_ASSERT_SIZE(CKGaugeCpntUpdater, 0x20);
DOTD_ASSERT_OFFSET(CKGaugeCpntUpdater, m_pGauge, 0x04);

// 0x0024b248 SetGaugeValue: ignores a negative value; the value (capped at the gauge's maximum, m_pGauge +0x04)
// becomes +0x10, +0x0c takes +0x08; with `resetAux` +0x14 is cleared.
void SetGaugeValue(CKGaugeCpntUpdater* gauge, float value, int32_t resetAux);
// 0x0024b2a0 SuperGaugeRecord_SetFullFlag_maybe: the flag byte +0x18 follows `value` (clearing +0x1c) unless it
// already equals it and the gauge's byte +0x21 is set.
void SuperGaugeRecord_SetFullFlag(CKGaugeCpntUpdater* gauge, uint32_t value);
// Clears a sample as the updaters' "no gauge" paths do (colour 0xffffffff).
void GaugeSample_Clear(GaugeSample* sample);
// 0x0024b600 GaugeSample_ApplyToElement2d_maybe: the sample on the menu's widget slot `slot`: x / y through the menu's
// vt+0x7c / vt+0x80, rotation and constant scale on the node, and the colour (white when unset): a text (0x5cd) gets it
// as its colour and its variables' colour, a billboard (0x3cd) as its colour.
void GaugeSample_ApplyToElement2d(const GaugeSample* sample, KBase730C* menu, uint32_t slot);
