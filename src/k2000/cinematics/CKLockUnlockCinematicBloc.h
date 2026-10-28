// CKLockUnlockCinematicBloc.h - locks or unlocks the cinematic actors (key 0x908, vtable 0xb1b4e0, size 0x38). Original unit: CKLockUnlockCinematicBloc.cpp.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/IKCinematicBloc.h"

class IKFile;

class CKLockUnlockCinematicBloc : public IKCinematicBloc {
public:
    DOTD_CLASS_KEY(kCategoryCinematic, 0x24)
    DOTD_DECLARE_FACTORIES(CKLockUnlockCinematicBloc)
    DOTD_BLOC_IS_KIND_OF()

    // 0x0017f0e0 CKLockUnlockCinematicBloc_Create: IKCinematicBloc_Construct, then the vtable (CKLockUnlockCinematicBloc_Construct 0x17eb28).
    CKLockUnlockCinematicBloc() {}
    ~CKLockUnlockCinematicBloc() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0017eab0 CKLockUnlockCinematicBloc_Load
};
DOTD_ASSERT_SIZE(CKLockUnlockCinematicBloc, 0x38);
