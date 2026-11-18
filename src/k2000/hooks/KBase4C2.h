// KBase4C2.h - the unregistered base of CKCameraBeacon (key 0x4c2, size 0x20). Its functions sit in the
// CKCameraBeacon_2.cpp unit (0x1dfb50-0x1dfd28). No XXL2 class of this key and no curated name yet. It adds
// no field to IKHook: its constructor 0x1dfb50 sets the IKLife/IKHook parts only.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/hooks/IKHook.h"

class IKTime;

class KBase4C2 : public IKHook {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0x13)

    KBase4C2() {}  // 0x001dfb50 CKCameraBeacon_ConstructBase_maybe (the IKLife/IKHook defaults)
    ~KBase4C2() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001dfbe0 KBase4C2_Load
    // vt+0xc0 0x001dfbc8 KBase4C2_vfC0 (empty; CKCameraBeacon overrides it, no caller of the slot is known).
    virtual void VfC0(IKTime* /*clock*/) {}
};
DOTD_ASSERT_SIZE(KBase4C2, 0x20);
