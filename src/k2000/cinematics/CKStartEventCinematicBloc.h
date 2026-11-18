// CKStartEventCinematicBloc.h - fires trigger events (key 0x648, vtable 0xb1ba38, size 0x40). Original unit: CKStartEventCinematicBloc.cpp.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/IKCinematicBloc.h"
#include "k2000/services/CTriggerStarter.h"

class IKFile;

class CKStartEventCinematicBloc : public IKCinematicBloc {
public:
    DOTD_CLASS_KEY(kCategoryCinematic, 0x19)
    DOTD_DECLARE_FACTORIES(CKStartEventCinematicBloc)
    DOTD_BLOC_IS_KIND_OF()

    // 0x0018a7a0 CKStartEventCinematicBloc_Create: IKCinematicBloc_Construct, then the vtable.
    CKStartEventCinematicBloc() {}
    ~CKStartEventCinematicBloc() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0018a588 CKStartEventCinematicBloc_Load
    // vt+0x24 0x0018a658 CKStartEventCinematicBloc_RecursiveRegistration: registered whatever the type (no 4..7 test), the
    // base's, then the starter's (KStub_Return1_2361b0: nothing).
    void RecursiveRegistration(int32_t type) override;

    void Start() override;                 // vt+0x5c 0x0018a8b0 CKStartEventCinematicBloc_Start
    void Complete() override;              // vt+0x64 0x0018ab90 CKStartEventCinematicBloc_Complete
    void Update(IKTime* time) override;    // vt+0x68 0x0018a560 CKStartEventCinematicBloc_Update
    void Stop() override;                  // vt+0x6c 0x0018a380 CKStartEventCinematicBloc_Stop
    void Abort() override;                 // vt+0x70 0x009aa1c8 CKStartEventCinematicBloc_Abort

    CTriggerStarter m_Starter;  // +0x38 (XXL2)
};
DOTD_ASSERT_SIZE(CKStartEventCinematicBloc, 0x40);
DOTD_ASSERT_OFFSET(CKStartEventCinematicBloc, m_Starter, +0x38);
