// CKSekensorCinematicBloc.h - starts a sequence (CKSekens) (key 0x508, vtable 0xb1b9a0, size 0x3c). Original unit: CKSekensorCinematicBloc.cpp.
// XXL2 has an index here (m_i32SeqIdToLaunch); DotD reads a reference.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/IKCinematicBloc.h"

class IKFile;

class CKSekensorCinematicBloc : public IKCinematicBloc {
public:
    DOTD_CLASS_KEY(kCategoryCinematic, 0x14)
    DOTD_DECLARE_FACTORIES(CKSekensorCinematicBloc)
    DOTD_BLOC_IS_KIND_OF()

    // 0x00189a90 CKSekensorCinematicBloc_Create: IKCinematicBloc_Construct, then the vtable.
    CKSekensorCinematicBloc() {}
    ~CKSekensorCinematicBloc() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00189850 CKSekensorCinematicBloc_Load
    // vt+0x24 0x00189958 CKSekensorCinematicBloc_RecursiveRegistration: registered with the saving manager (vt+0x24) unless the type is 4..7, then
    // IKCinematicBloc_LevelReset 0x18e8d8 (which registers it once more).
    void RecursiveRegistration(int32_t type) override;

    void Start() override;                 // vt+0x5c 0x00189d68 CKSekensorCinematicBloc_Start
    void Complete() override;              // vt+0x64 0x00189650 CKSekensorCinematicBloc_Complete
    void Update(IKTime* time) override;    // vt+0x68 0x00189b70 CKSekensorCinematicBloc_Update
    void Stop() override;                  // vt+0x6c 0x0018a0a8 CKSekensorCinematicBloc_Stop
    void Abort() override;                 // vt+0x70 0x00189ae8 CKSekensorCinematicBloc_Abort

    IKSerializable* m_pSekens;  // +0x38 CKSekens in the files (XXL2: m_i32SeqIdToLaunch)
};
DOTD_ASSERT_SIZE(CKSekensorCinematicBloc, 0x3c);
DOTD_ASSERT_OFFSET(CKSekensorCinematicBloc, m_pSekens, +0x38);
