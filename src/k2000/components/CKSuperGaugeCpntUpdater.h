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
    DOTD_DECLARE_FACTORIES(CKSuperGaugeCpntUpdater)

    CKSuperGaugeCpntUpdater() {}  // 0x00250ee0 CKSuperGaugeCpntUpdater_Create: the vtable only

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00251358 CKSuperGaugeCpntUpdater_Load
    // 0x00250d80 CKSuperGaugeCpnt_SetFullFlag_maybe: the first updater's full flag.
    void SetFullFlag(uint32_t value);
    // 0x00250da8 CKSuperGaugeCpnt_SetMarkerValue_maybe: the third updater's value (the marker), the aux value reset.
    void SetMarkerValue(float value);
    // 0x00250dd8 CKSuperGaugeCpnt_SetValue: the first and second updaters' value; `resetAux` for both.
    void SetValue(float value, int32_t resetAux);

    CKSuperGaugeCpnt* m_pSuperGauge;       // +0x04 (Ghidra draft: CKSuperGaugeCpnt*)
    CKGaugeCpntUpdater* m_apUpdaters[3];   // +0x08 (Ghidra draft: CKGaugeCpntUpdater*); PostLoad (0x251580)
                                           // resets each one (SuperGaugeRecord_Reset_maybe)
};
DOTD_ASSERT_SIZE(CKSuperGaugeCpntUpdater, 0x14);
DOTD_ASSERT_OFFSET(CKSuperGaugeCpntUpdater, m_pSuperGauge, 0x04);
DOTD_ASSERT_OFFSET(CKSuperGaugeCpntUpdater, m_apUpdaters, 0x08);
