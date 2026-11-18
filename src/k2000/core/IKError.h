// IKError.h - the error classes (category 14, key 0x7fe = id 0x1f): one object per registered error class, created by
// CKErrorTable::CreateErrorObjects (0x1dd30) through the registry. Derived straight from IKBaseClass (their
// IsKindOfClass copies test their own key and 0x7fe, not IKSerializable's 0xc). The PS3 object is the vtable pointer
// only (size 4). Error codes: (module << 16) | n: 0x1xxxx CKGLError, 0x2xxxx CKCoreError, 0x3xxxx CKILError.
#pragma once
#include <cstdint>

#include "k2000/core/IKBaseClass.h"
#include "k2000/core/Layout.h"

class IKError : public IKBaseClass {
public:
    // vt+0x24: the (French) message of error `code`; the module's "not documented" text for an unknown code.
    virtual const char* GetErrorMessage(int32_t code) = 0;
    // vt+0x28 0x00990ed0 IKError_vf28: Destroy (vt+0x10).
    virtual void Vf28() { Destroy(); }
};
DOTD_ASSERT_SIZE(IKError, 0x4);

// IsKindOfClass of an error class (0x990f58 / 0x99c2e0 / 0x9a63a8): its own key or IKError's 0x7fe.
#define DOTD_ERROR_IS_KIND_OF(key_) \
    int32_t IsKindOfClass(uint32_t key) override { return key == (key_) || key == 0x7fe; }
