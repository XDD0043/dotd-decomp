// IKFlashGenericEvent.h - the events a Flash message in starts (key 0x8cd, vtable 0xb164d0, size 0x08; XXL2
// K/KModules/KGL/2d/Maestro/FlashObject/IKFlashGenericEvent). No game file holds one (0 references in LVL000; the
// derived CKFlashStartEventEvent 0x2dcc and CKFlashPlaySoundEvent 0x2e4c neither: outputs/remake/kp3-class-usage.json).
// Its out-of-line methods are at the end of CKFlashStartEventEvent.cpp (0x78650 Load, 0x786e0 / 0x786e8 Save /
// RecursiveRegistration) and 0x999608..0x999660 (the inline ones).
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"
#include "k2000/io/IKFile.h"
#include "k2000/ui/IKFlashObject.h"

class IKFlashGenericEvent : public IKSerializable {
public:
    IKFlashGenericEvent() {}             // inlined in the derived Create (the vtable only; +0x04 not set)
    ~IKFlashGenericEvent() override {}   // vt+0x00 / +0x04  0x999648 / 0x999660
    int32_t IsKindOfClass(uint32_t key) override { return key == 0x8cd || key == 0xc; }  // vt+0x08 0x999628
    int32_t GetClassType() override { return kCategoryGraphical; }  // vt+0x14 0x999608
    int32_t GetClassID() override { return 0x23; }                  // vt+0x18 0x999610
    // vt+0x10 0x999620 (empty), vt+0x24 0x786e8 / vt+0x28 0x786e0 / vt+0x30 0x999618 (return 1): the defaults.
    // vt+0x2c 0x00078650 IKFlashGenericEvent_Load (level data only): the owner reference.
    int32_t Load(IKFile* file, int32_t type) override {
        if (type == K_LEVEL_PLATEFORMS) IKFile_ReadRef(file, &m_pOwner);
        return 1;
    }
    // vt+0x50 (XXL2 slot 20, name unknown): the event started (CKFlashMessageIn_TriggerTargets_maybe).
    virtual void Vf50() = 0;

    IKFlashObject* m_pOwner;  // +0x04 the Flash object (its +0x0c CKFlashUI)
};
DOTD_ASSERT_SIZE(IKFlashGenericEvent, 0x8);
