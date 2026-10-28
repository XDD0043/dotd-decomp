// IKFlashMessage.h - base of the Flash messages (key 0x80d, vtable 0xb16230, size 0x24; XXL2:
// K/KModules/KGL/2d/Maestro/FlashObject/IKFlashMessage.h, no members): CKFlashMessageIn (0x84d),
// CKFlashMessageOut (0x88d). Its methods are inline: their out-of-line copies are at 0x9991d8..0x999368
// (CKFlashMessageIn.cpp). Its RecursiveRegistration, Save and PostLoad (0x999298, 0x999270, 0x999220)
// call IKFlashObject's and return 1, which is what the inherited ones do.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/ui/IKFlashObject.h"

class IKFlashMessage : public IKFlashObject {
public:
    ~IKFlashMessage() override {}                                           // vt+0x00 / +0x04  0x999368 / 0x999320
    int32_t IsKindOfClass(uint32_t key) override {                          // vt+0x08 0x9991d8
        return key == 0x80d || key == 0x74d || key == 0xc;
    }
    int32_t GetClassType() override { return kCategoryGraphical; }          // vt+0x14 0x999200 (unregistered key 0x80d)
    int32_t GetClassID() override { return 0x20; }                          // vt+0x18 0x999208
    int32_t Load(IKFile* file, int32_t type) override {                     // vt+0x2c 0x999248
        IKFlashObject::Load(file, type);
        return 1;
    }
};
DOTD_ASSERT_SIZE(IKFlashMessage, 0x24);
