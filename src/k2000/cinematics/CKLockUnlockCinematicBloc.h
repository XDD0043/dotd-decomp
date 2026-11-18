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
    void Start() override;     // vt+0x5c 0x0017ee48 CKLockUnlockCinematicBloc_Start: the blocs' common start only
    void Complete() override;  // vt+0x64 0x0017e8d8 CKLockUnlockCinematicBloc_Complete: the completion
    // vt+0x68 0x0017ec40 CKLockUnlockCinematicBloc_Update: (unless its sekens stopped it) the actor's life object (or
    // the hook) locked when it was not (its 0x486 component kept in the data's +0x18) or unlocked (the other running
    // exclusive blocs on the same actor stopped), then completed.
    void Update(IKTime* time) override;
    void Stop() override;      // vt+0x6c 0x0017f238 CKLockUnlockCinematicBloc_Stop: the completion, then Complete
    void Abort() override;     // vt+0x70 0x0017e840 CKLockUnlockCinematicBloc_Abort: not running
};
DOTD_ASSERT_SIZE(CKLockUnlockCinematicBloc, 0x38);
