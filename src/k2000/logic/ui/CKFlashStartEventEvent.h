// CKFlashStartEventEvent.h - a Flash event that fires a trigger starter (key 0x2dcc, vtable 0xb16470, size 0x10).
// Original unit: CKFlashStartEventEvent.cpp (0x78280-0x786f0). No game file holds one. Name from the class table.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/graphical/ui/IKFlashGenericEvent.h"
#include "k2000/services/CTriggerStarter.h"

class CKFlashStartEventEvent : public IKFlashGenericEvent {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0xb7)
    int32_t IsKindOfClass(uint32_t key) override { return key == 0x2dcc || key == 0x8cd || key == 0xc; }  // vt+0x08 0x999560
    DOTD_DECLARE_FACTORIES(CKFlashStartEventEvent)

    CKFlashStartEventEvent() {}             // inlined in 0x00078610 CKFlashStartEventEvent_Create: the vtables only
    ~CKFlashStartEventEvent() override {}   // vt+0x00 / +0x04  0x9995e8 / 0x9995a0
    // vt+0x24 0x00078400 CKFlashStartEventEvent_RecursiveRegistration: the base's (nothing), then for type 0 the object
    // registered with the saving manager and the starter's 0x2361b0 (KStub_Return1: nothing).
    void RecursiveRegistration(int32_t type) override;
    // vt+0x2c 0x00078360 CKFlashStartEventEvent_Load: the base's, then (level data) the trigger starter.
    int32_t Load(IKFile* file, int32_t type) override;
    // vt+0x30 0x782d0 CKFlashStartEventEvent_PostLoad (1) and vt+0x40 0x78648 CKFlashStartEventEvent_GetInfo (1): the
    // defaults.
    // vt+0x50 0x000784a8 CKFlashStartEventEvent_FireEvent: the starter's signals queued (QueueTriggerSignals).
    void Vf50() override;

    CTriggerStarter m_tsStart;  // +0x08
};
DOTD_ASSERT_SIZE(CKFlashStartEventEvent, 0x10);
DOTD_ASSERT_OFFSET(CKFlashStartEventEvent, m_tsStart, 0x08);
