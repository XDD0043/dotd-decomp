// CKFlashPlaySoundEvent.h - a Flash event that plays a sound of its interface's dictionary (key 0x2e4c, vtable
// 0xb16410, size 0x0c). Original unit: CKFlashPlaySoundEvent.cpp (0x77e48-0x78280). No game file holds one. Name from
// the class table.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/graphical/ui/IKFlashGenericEvent.h"

class CKFlashPlaySoundEvent : public IKFlashGenericEvent {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0xb9)
    int32_t IsKindOfClass(uint32_t key) override { return key == 0x2e4c || key == 0x8cd || key == 0xc; }  // vt+0x08 0x9994b8
    DOTD_DECLARE_FACTORIES(CKFlashPlaySoundEvent)

    CKFlashPlaySoundEvent() {}             // inlined in 0x00078248 CKFlashPlaySoundEvent_Create: the vtables only
    ~CKFlashPlaySoundEvent() override {}   // vt+0x00 / +0x04  0x9994f8 / 0x999518
    // vt+0x24 0x00077ff8 CKFlashPlaySoundEvent_RecursiveRegistration: the base's (nothing), then for type 0 the object
    // registered with the saving manager.
    void RecursiveRegistration(int32_t type) override;
    // vt+0x2c 0x00077f28 CKFlashPlaySoundEvent_Load: the base's, then (level data) the sound index.
    int32_t Load(IKFile* file, int32_t type) override;
    // vt+0x30 0x77e98 CKFlashPlaySoundEvent_PostLoad: 1 (the default).
    // vt+0x50 0x00078080 CKFlashPlaySoundEvent_Execute: unless the index is -1, the owner's interface's (+0x04 -> +0x0c)
    // sound dictionary (+0xf0) sound `index`, made multi-instance, its pan reset and played from 0.
    void Vf50() override;

    int32_t m_soundIndex;  // +0x08 -1: none
};
DOTD_ASSERT_SIZE(CKFlashPlaySoundEvent, 0xc);
DOTD_ASSERT_OFFSET(CKFlashPlaySoundEvent, m_soundIndex, 0x08);
