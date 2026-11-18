// CKGLError.h - the graphics module's error messages (key 0x4e, vtable 0xb16998, size 0x4). Original unit:
// CKGLError.cpp. Codes 0x10000..0x1001c.
#pragma once
#include <cstdint>

#include "k2000/core/IKError.h"

class CKGLError : public IKError {
public:
    DOTD_CLASS_KEY(kCategoryError, 0x1)
    DOTD_ERROR_IS_KIND_OF(0x4e)  // vt+0x08 0x99c2e0
    DOTD_DECLARE_FACTORIES(CKGLError)
    // 0x00087e40 CKGLError_Create: operator new(4), the vtable written. 0x00087f08 CKGLError_Destructor (0x87f38 the
    // deleting one + operator delete): the vtables only. vt+0x10 Destroy 0x99c2d8: empty (the default).

    const char* GetErrorMessage(int32_t code) override;  // vt+0x24 0x00087b88
};
DOTD_ASSERT_SIZE(CKGLError, 0x4);
