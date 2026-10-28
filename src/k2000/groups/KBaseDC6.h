// KBaseDC6.h - the unregistered base of CKS08FightZoneCpnt (key 0xdc6, category component, derived straight
// from IKSerializable: CKS08FightZoneCpnt_IsKindOfClass 0x9bc4c8 tests 0x1146, 0xdc6, 0xc). Its functions
// sit in the CKGrpFightZone.cpp unit (0x274a70 Load, which reads nothing). No XXL2 class with this key.
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"

class KBaseDC6 : public IKSerializable {
public:
    KBaseDC6() {}  // the vtable only (inlined in CKS08FightZoneCpnt_Create 0x274c38)
    // vt+0x2c 0x00274a70 KBaseDC6_Load: reads nothing.
    int32_t Load(IKFile* /*file*/, int32_t /*type*/) override { return 1; }
};
