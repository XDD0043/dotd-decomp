// CKSuperGaugeCpntUpdater.h - drives a CKSuperGaugeCpnt through three gauge updaters (key 0x14c6, vtable
// 0xb21058, size 0x14). Original unit: CKSuperGaugeCpntUpdater.cpp (0x250b38-0x251628). No XXL2 class of this name.
#pragma once
#include <cstdint>

#include "k2000/components/CKGaugeCpntUpdater.h"
#include "k2000/components/IKComponent.h"
#include "k2000/core/Layout.h"
#include "k2000/logic/ui/CKSuperGaugeCpnt.h"

class CKSuperGaugeCpntUpdater : public IKComponent {
public:
    DOTD_CLASS_KEY(kCategoryComponent, 0x53)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9ba478
        return key == 0x14c6 || key == 0x6 || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKSuperGaugeCpntUpdater)

    CKSuperGaugeCpntUpdater() {}  // 0x00250ee0 CKSuperGaugeCpntUpdater_Create: the vtable only

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00251358 CKSuperGaugeCpntUpdater_Load
    int32_t PostLoad(int32_t type) override;            // vt+0x30 0x00251580 CKSuperGaugeCpntUpdater_PostLoad
    // 0x00250fd8 CKSuperGaugeCpntUpdater_Tick: the three channels advanced and sampled (1); without a super gauge the
    // samples cleared (0).
    int32_t Tick(float dt, GaugeSample samples[3]);
    // 0x00250d80 CKSuperGaugeCpnt_SetFullFlag_maybe: the first updater's full flag.
    void SetFullFlag(uint32_t value);
    // 0x00250da8 CKSuperGaugeCpnt_SetMarkerValue_maybe: the third updater's value (the marker), the aux value reset.
    void SetMarkerValue(float value);
    // 0x00250f18 CKSuperGaugeCpnt_GetMarkerValue_maybe (C2.8 port-rest R02): the third updater's value (the marker).
    float GetMarkerValue() const;
    // 0x00250dd8 CKSuperGaugeCpnt_SetValue: the first and second updaters' value; `resetAux` for both.
    void SetValue(float value, int32_t resetAux);

    CKSuperGaugeCpnt* m_pSuperGauge;       // +0x04 (Ghidra draft: CKSuperGaugeCpnt*)
    CKGaugeCpntUpdater* m_apUpdaters[3];   // +0x08 (Ghidra draft: CKGaugeCpntUpdater*); PostLoad (0x251580)
                                           // resets each one (SuperGaugeRecord_Reset_maybe)
};
DOTD_ASSERT_SIZE(CKSuperGaugeCpntUpdater, 0x14);

// 0x00250bc8 GaugeSamples_ApplyToElements2d_maybe: sample i on the menu's widget slot `slot_i` (skipped when negative).
void GaugeSamples_ApplyToElements2d(CKSuperGaugeCpntUpdater* updater, const GaugeSample samples[3], KBase730C* menu,
                                    int32_t slot0, int32_t slot1, int32_t slot2);
DOTD_ASSERT_OFFSET(CKSuperGaugeCpntUpdater, m_pSuperGauge, 0x04);
DOTD_ASSERT_OFFSET(CKSuperGaugeCpntUpdater, m_apUpdaters, 0x08);
