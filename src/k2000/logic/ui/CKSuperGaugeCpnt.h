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
    DOTD_DECLARE_FACTORIES(CKSuperGaugeCpnt)

    CKSuperGaugeCpnt() {}  // 0x00250720 CKSuperGaugeCpnt_Create: the vtable only

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00250770 CKSuperGaugeCpnt_Load
    // vt+0x30 PostLoad 0x250760 returns 1.

    CKGaugeCpnt* m_apGauges[3];  // +0x04 (Ghidra draft: CKGaugeCpnt*)
};
DOTD_ASSERT_SIZE(CKSuperGaugeCpnt, 0x10);
DOTD_ASSERT_OFFSET(CKSuperGaugeCpnt, m_apGauges, 0x04);
