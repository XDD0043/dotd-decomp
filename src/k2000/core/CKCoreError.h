// CKCoreError.h - the KCore module's error messages (key 0x8e, vtable 0xb12b88, size 0x4). Original unit:
// CKCoreError.cpp. Codes 0x20000..0x20002.
#pragma once
#include <cstdint>

#include "k2000/core/IKError.h"

class CKCoreError : public IKError {
public:
    DOTD_CLASS_KEY(kCategoryError, 0x2)
    DOTD_ERROR_IS_KIND_OF(0x8e)  // vt+0x08 0x990f58
    DOTD_DECLARE_FACTORIES(CKCoreError)
    // 0x00012378 CKCoreError_Create: operator new(4), the vtable written. 0x00012440 CKCoreError_Destructor
    // (0x12470 the deleting one + operator delete): the vtables only. vt+0x10 Destroy 0x990f20: empty (the default).

    const char* GetErrorMessage(int32_t code) override;  // vt+0x24 0x000121e8
};
DOTD_ASSERT_SIZE(CKCoreError, 0x4);
