// CKMecaCpntBase.h - the base of the mechanism components (key 0xa06, unregistered; XXL2:
// K/KMeca/IKMecaCpnt.h, the base of CKCrumblyZoneCpnt there too). Original unit: CKMecaCpntBase.cpp
// (0x3f7950-0x3f7ab8). On the PS3 it is only the vtable pointer (size 4).
//
// C2.1 ports the constructor and the Load only. Its vtable adds slots after +0x4c (KBaseA06_vf50..; the
// inline copies 0x9c0cf0..), not declared yet.
#pragma once
#include <cstdint>

#include "k2000/components/IKComponent.h"

class IKMecaCpnt : public IKComponent {
public:
    IKMecaCpnt() {}  // 0x003f7a08 CKMecaCpntBase_a06_maybe_ConstructBase: the vtable only
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c0cb8
        return key == 0xa06 || key == 0x6 || key == 0xc;
    }
    // vt+0x2c 0x003f7a18 CKMecaCpntBase_a06_maybe_Load: reads nothing.
    int32_t Load(IKFile* /*file*/, int32_t /*type*/) override { return 1; }
    // vt+0x58 (KBaseA06_vf58; CKGrpMeca's Start calls it on each component): empty here, the crumbly zone's
    // component clears its byte +0x0d.
    virtual void Vf58() {}
};
