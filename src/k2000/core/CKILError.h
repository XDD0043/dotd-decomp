// CKILError.h - the input module's error messages (key 0xce, vtable 0xb19460, size 0x4). Original unit:
// CKILError.cpp. Codes 0x30000..0x30028.
#pragma once
#include <cstdint>

#include "k2000/core/IKError.h"

class CKILError : public IKError {
public:
    DOTD_CLASS_KEY(kCategoryError, 0x3)
    DOTD_ERROR_IS_KIND_OF(0xce)  // vt+0x08 0x9a63a8
    DOTD_DECLARE_FACTORIES(CKILError)
    // 0x00103638 CKILError_Create: operator new(4), the vtable written. 0x00103700 CKILError_Destructor (0x103730 the
    // deleting one + operator delete): the vtables only. vt+0x10 Destroy 0x9a63a0: empty (the default).

    const char* GetErrorMessage(int32_t code) override;  // vt+0x24 0x001032f8
    virtual int32_t Vf2C() { return 1; }                 // vt+0x2c 0x009a6398 CKILError_vf2C (this class only)
};
DOTD_ASSERT_SIZE(CKILError, 0x4);
