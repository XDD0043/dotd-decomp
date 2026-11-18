// CKHkS08ElectricGaugeBase.h - the unregistered base of CKHkS08ElectricGauge (key 0x3542, vtable 0xb2a458,
// size 0x20; Ghidra CKHkS08ElectricGaugeBase_3542_maybe). Original unit: CKHkS08ElectricGaugeBase.cpp
// (0x4e0920-0x4e0ad8). No XXL2 class. It adds no field to CKHkActorBase.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/CKHkActorBase.h"

class CKHkS08ElectricGaugeBase : public CKHkActorBase {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0xd5)

    // 0x004e0a68 CKHkS08ElectricGaugeBase_3542_maybe_Construct (and 0x4e0aa0, Ghidra
    // CKHkS08ElectricGauge_ConstructBase_maybe, the same body): the CKHkActorBase part only.
    CKHkS08ElectricGaugeBase() {}
    ~CKHkS08ElectricGaugeBase() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x004e0920 CKHkS08ElectricGaugeBase_3542_maybe_Load
    // vt+0x7c 0x004e0858 CKHkS08ElectricGaugeBase_3542_maybe_Update (unit CKHkMecaSound.cpp): the actor base's update
    // (WorldObjectBase_Update_Nop 0x3f6e68, empty).
    void Update(IKTime* clock) override;
};
DOTD_ASSERT_SIZE(CKHkS08ElectricGaugeBase, 0x20);
