// IKComponent.h - the components (key 0x6; XXL2: K/KCore/Interfaces/IKComponent.h): data objects that
// hooks, nodes and other objects reference (curves, gauges, particle and FX parameters, bonus and
// vibration data). Derived straight from IKSerializable; IKFxData (0x304c) is one of them.
//
// XXL2's IKComponent declares no members and no virtual methods beyond IsKindOfClass (its 16 bytes are
// the vtable pointer and XXL2's debug pointer). On the PS3 it is only the vtable pointer and it has no
// vtable of its own (abstract): the inline IsKindOfClass copy is 0x991218. It adds no slots: the
// component vtables (CKParticlesCpnt 0xb1df00, ...) end at +0x4c.
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"

class IKComponent : public IKSerializable {
public:
    int32_t IsKindOfClass(uint32_t key) override { return key == 0x6 || key == 0xc; }  // vt+0x08 0x991218
};
