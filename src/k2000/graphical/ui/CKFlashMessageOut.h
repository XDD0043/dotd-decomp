// CKFlashMessageOut.h - a message the game sends to the Flash interface (key 0x88d, vtable 0xb162a8,
// size 0x24, no members of its own). Original unit: CKFlashMessageOut.cpp (0x754e0-0x75960). XXL2:
// K/KModules/KGL/2d/Maestro/FlashObject/CKFlashMessageOut.h (no members either).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/graphical/ui/IKFlashMessage.h"

class CKFlashMessageOut : public IKFlashMessage {
public:
    DOTD_CLASS_KEY(kCategoryGraphical, 0x22)
    DOTD_DECLARE_FACTORIES(CKFlashMessageOut)

    // Inlined in 0x00075790 CKFlashMessageOut_Create: only the vtables (copy 0x75530 unreferenced).
    CKFlashMessageOut() {}
    ~CKFlashMessageOut() override {}                                        // vt+0x00 / +0x04  0x758d8 / 0x75918
    int32_t IsKindOfClass(uint32_t key) override {                          // vt+0x08 0x999398
        return key == 0x88d || key == 0x80d || key == 0x74d || key == 0xc;
    }
    int32_t Load(IKFile* file, int32_t type) override;                      // vt+0x2c 0x00075888 CKFlashMessageOut_Load
    // vt+0x54 0x755e8 CKFlashMessageOut_vf54 only calls IKFlashObject's (inherited).
    // 0x00075610 CKFlashMessageOut_Send_maybe (XXL2 PostFlashMessage): the interface posts the label.
    void PostFlashMessage();
};
DOTD_ASSERT_SIZE(CKFlashMessageOut, 0x24);
