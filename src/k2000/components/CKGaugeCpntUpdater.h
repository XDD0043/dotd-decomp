// CKGaugeCpntUpdater.h - drives a CKGaugeCpnt (key 0x1486, vtable 0xb20d98, size 0x20). Original unit:
// CKGaugeCpntUpdater.cpp (0x24b2e0-0x24bc70). No XXL2 class of this name.
#pragma once
#include <cstdint>

#include "k2000/components/IKComponent.h"
#include "k2000/core/Layout.h"
#include "k2000/logic/ui/CKGaugeCpnt.h"

class CKGaugeCpntUpdater : public IKComponent {
public:
    DOTD_CLASS_KEY(kCategoryComponent, 0x52)
    DOTD_DECLARE_FACTORIES(CKGaugeCpntUpdater)

    CKGaugeCpntUpdater() {}  // 0x0024b4d8 CKGaugeCpntUpdater_Create: the vtable only

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0024bad0 CKGaugeCpntUpdater_Load
    int32_t PostLoad(int32_t type) override;            // vt+0x30 0x0024bb60 CKGaugeCpntUpdater_PostLoad

    CKGaugeCpnt* m_pGauge;  // +0x04 (Ghidra draft: CKGaugeCpnt*)
    // The rest is the runtime state; PostLoad (0x24bb60) clears it: 0.0 at +0x08..+0x10, 0 at +0x14 and
    // +0x1c, 0 in the byte at +0x18.
    float m_unk08;          // +0x08
    float m_unk0c;          // +0x0c
    float m_unk10;          // +0x10
    uint32_t m_unk14;       // +0x14
    uint8_t m_unk18;        // +0x18
    uint8_t m_pad19[3];
    uint32_t m_unk1c;       // +0x1c
};
DOTD_ASSERT_SIZE(CKGaugeCpntUpdater, 0x20);
DOTD_ASSERT_OFFSET(CKGaugeCpntUpdater, m_pGauge, 0x04);

// 0x0024b248 SetGaugeValue: ignores a negative value; the value (capped at the gauge's maximum, m_pGauge +0x04)
// becomes +0x10, +0x0c takes +0x08; with `resetAux` +0x14 is cleared.
void SetGaugeValue(CKGaugeCpntUpdater* gauge, float value, int32_t resetAux);
// 0x0024b2a0 SuperGaugeRecord_SetFullFlag_maybe: the flag byte +0x18 follows `value` (clearing +0x1c) unless it
// already equals it and the gauge's byte +0x21 is set.
void SuperGaugeRecord_SetFullFlag(CKGaugeCpntUpdater* gauge, uint32_t value);
