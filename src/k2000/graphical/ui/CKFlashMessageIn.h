// CKFlashMessageIn.h - a message the Flash interface sends to the game, with the events it fires (key 0x84d,
// vtable 0xb161b8, size 0x2c). Original unit: CKFlashMessageIn.cpp (0x74e30-0x754e0). XXL2:
// K/KModules/KGL/2d/Maestro/FlashObject/CKFlashMessageIn.h, the same members read in the same order.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/graphical/ui/IKFlashMessage.h"

// IKFlashGenericEvent (key 0x8cd; XXL2 K/KModules/KGL/2d/Maestro/FlashObject/IKFlashGenericEvent): the
// events a message in starts. No front-end file holds one (0 references in LVL000); only the slot
// CKFlashMessageIn_TriggerTargets_maybe calls is declared (vt+0x50, XXL2 slot 20, name unknown).
class IKFlashGenericEvent : public IKSerializable {
public:
    virtual void Vf50() = 0;  // vt+0x50
};

class CKFlashMessageIn : public IKFlashMessage {
public:
    DOTD_CLASS_KEY(kCategoryGraphical, 0x21)
    DOTD_DECLARE_FACTORIES(CKFlashMessageIn)

    // Inlined in 0x000750b8 CKFlashMessageIn_Create: only the vtables (copy 0x74e80 unreferenced).
    CKFlashMessageIn() {}
    ~CKFlashMessageIn() override {}                                         // vt+0x00 / +0x04  0x754a0 / 0x75458
    int32_t IsKindOfClass(uint32_t key) override {                          // vt+0x08 0x9992e8
        return key == 0x84d || key == 0x80d || key == 0x74d || key == 0xc;
    }
    void Destroy() override;                                                // vt+0x10 0x000751b8 CKFlashMessageIn_Destroy
    int32_t GetInfo() override { return 1; }                                // vt+0x40 0x75100
    int32_t Load(IKFile* file, int32_t type) override;                      // vt+0x2c 0x000752b0 CKFlashMessageIn_Load
    // vt+0x54 0x74f50 CKFlashMessageIn_vf54 only calls IKFlashObject's (inherited).
    // 0x00075108 CKFlashMessageIn_TriggerTargets_maybe (XXL2 StartAllEvents): vt+0x50 of every event.
    void StartAllEvents();

    IKFlashGenericEvent** m_apGenericEvent;  // +0x24 IKFlashGenericEvent (0x8cd) references (Mem_AllocAligned16); not set by the constructor
    uint32_t m_ui32GenericEventNb;      // +0x28 not set by the constructor
};
DOTD_ASSERT_SIZE(CKFlashMessageIn, 0x2c);
DOTD_ASSERT_OFFSET(CKFlashMessageIn, m_apGenericEvent, 0x24);
DOTD_ASSERT_OFFSET(CKFlashMessageIn, m_ui32GenericEventNb, 0x28);
