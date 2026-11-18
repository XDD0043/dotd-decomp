// CKSuperGaugeCpnt.h - three gauges shown as one (key 0xa94c, vtable 0xb21000, size 0x10). Original unit:
// CKSuperGaugeCpnt.cpp (0x2503e8-0x250b38). No XXL2 class of this name.
#pragma once
#include <cstdint>

#include "k2000/components/IKComponent.h"
#include "k2000/core/Layout.h"
#include "k2000/logic/ui/CKGaugeCpnt.h"

class CKSuperGaugeCpnt : public IKComponent {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x2a5)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9ba3c0
        return key == 0xa94c || key == 0x6 || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKSuperGaugeCpnt)

    CKSuperGaugeCpnt() {}  // 0x00250720 CKSuperGaugeCpnt_Create: the vtable only

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00250770 CKSuperGaugeCpnt_Load
    // vt+0x30 PostLoad 0x250760 returns 1.
    // 0x002504c0 CKSuperGaugeCpnt_TickChannels: each gauge's displayed value advanced with its record (the updater's
    // three), into the three samples.
    void TickChannels(float dt, GaugeSample samples[3], class CKSuperGaugeCpntUpdater* updater) const;

    CKGaugeCpnt* m_apGauges[3];  // +0x04 (Ghidra draft: CKGaugeCpnt*)
};
DOTD_ASSERT_SIZE(CKSuperGaugeCpnt, 0x10);
DOTD_ASSERT_OFFSET(CKSuperGaugeCpnt, m_apGauges, 0x04);
