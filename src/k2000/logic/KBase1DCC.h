// KBase1DCC.h - an unregistered abstract base (key 0x1dcc; no XXL2 counterpart, the Ghidra name is kept).
// Original unit: KBase1DCC.cpp (0x1a468-0x1a5c0). PS3 vtable 0xb13440 (22 slots; GetClassType 0xc and
// GetClassID 0x77 at 0x9928b0/0x9928b8 give the key). Derived straight from IKSerializable; its classes are
// CKQuakeCameraLauncher (0xa86), CKSrvFxParticlesAccessor (0x2c0c) and CKProjectileAccessor (0x1e0c).
//
// +0x50 and +0x54 are pure. CKQuakeCameraLauncher implements them as a getter and a setter of its +0x04
// object reference: _maybe an accessor interface (Get/Set the accessed object).
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"

class KBase1DCC : public IKSerializable {
public:
    KBase1DCC() {}  // 0x0001a468 KBase1DCC_ConstructBase: stores the vtable only

    int32_t IsKindOfClass(uint32_t key) override { return key == 0x1dcc || key == 0xc; }  // vt+0x08 0x9928c0
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0001a598 KBase1DCC_Load
    // vt+0x30 PostLoad 0x1a5a0 returns 1 (the default).
    // vt+0x24 0x0001a478 (Ghidra CKSrvFxParticlesAccessor_RecursiveRegistration; the slot of KBase1DCC and of
    // CKSrvFxParticlesAccessor; CKQuakeCameraLauncher's 0x153218 has the same body): type 0 registers it with the
    // saving manager.
    void RecursiveRegistration(int32_t type) override;
    virtual IKSerializable* Vf50() = 0;              // vt+0x50 pure (CKQuakeCameraLauncher: returns +0x04)
    virtual void Vf54(IKSerializable* object) = 0;   // vt+0x54 pure (CKQuakeCameraLauncher: sets +0x04)
};
