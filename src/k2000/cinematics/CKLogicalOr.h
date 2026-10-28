// CKLogicalOr.h - a cinematic scene's OR door (key 0x88, vtable 0xb1ae60, size 0x28). Original unit:
// CKLogicalOr.cpp. XXL2: no members of its own.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/IKLogicalDoor.h"

class CKLogicalOr : public IKLogicalDoor {
public:
    DOTD_CLASS_KEY(kCategoryCinematic, 0x2)
    DOTD_DECLARE_FACTORIES(CKLogicalOr)
    DOTD_DOOR_IS_KIND_OF()

    // 0x0016fc78 CKLogicalOr_Create: IKCinematicElement_Construct, then the vtable.
    CKLogicalOr() {}
    ~CKLogicalOr() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0016fa10 CKLogicalOr_Load
    void Start() override;                              // vt+0x5c 0x0016fcd8 CKLogicalOr_Start
    void Complete() override { CompleteDoor(); }        // vt+0x64 0x0016f840 CKLogicalOr_Complete
    void Update(IKTime*) override;                      // vt+0x68 0x0016fdc8 CKLogicalOr_Update
    void Abort() override;                              // vt+0x70 0x0016f738 CKLogicalOr_Abort
};
DOTD_ASSERT_SIZE(CKLogicalOr, 0x28);
