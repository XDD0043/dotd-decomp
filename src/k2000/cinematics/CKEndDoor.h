// CKEndDoor.h - a cinematic scene's end door (key 0x7c8, vtable 0xb1acc8, size 0x28). Original unit:
// CKEndDoor.cpp. XXL2: no members of its own.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/IKLogicalDoor.h"

class CKEndDoor : public IKLogicalDoor {
public:
    DOTD_CLASS_KEY(kCategoryCinematic, 0x1f)
    DOTD_DECLARE_FACTORIES(CKEndDoor)
    DOTD_DOOR_IS_KIND_OF()

    // 0x0016ecb8 CKEndDoor_Create: IKCinematicElement_Construct, then the vtable.
    CKEndDoor() {}
    ~CKEndDoor() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0016eb30 CKEndDoor_Load
    void Start() override { CountIncomingActivation(); }  // vt+0x5c 0x0016eac0 CKEndDoor_Start
    void Complete() override { CompleteDoor(); }          // vt+0x64 0x0016e8f0 CKEndDoor_Complete
    void Update(IKTime*) override { Complete(); }         // vt+0x68 0x0016e808 CKEndDoor_Update
    void Abort() override;                                // vt+0x70 0x0016e848 CKEndDoor_Abort
};
DOTD_ASSERT_SIZE(CKEndDoor, 0x28);
