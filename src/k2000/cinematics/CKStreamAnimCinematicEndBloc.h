// CKStreamAnimCinematicEndBloc.h - a streamed-animation cinematic step (key 0x3c8, vtable 0xb1bc00, size 0x3c). Original unit: CKStreamAnimCinematicEndBloc.cpp.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/IKCinematicBloc.h"

class IKFile;
class IKTime;

class CKStreamAnimCinematicEndBloc : public IKCinematicBloc {
public:
    DOTD_CLASS_KEY(kCategoryCinematic, 0xf)
    DOTD_DECLARE_FACTORIES(CKStreamAnimCinematicEndBloc)
    DOTD_BLOC_IS_KIND_OF()

    CKStreamAnimCinematicEndBloc();  // 0x0018d170 CKStreamAnimCinematicEndBloc_Create (the same stores as CKStreamAnimCinematicEndBloc_Construct 0x18cdb0)
    ~CKStreamAnimCinematicEndBloc() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0018cbc8 CKStreamAnimCinematicEndBloc_Load
    // vt+0x24 0x0018ccb0 CKStreamAnimCinematicEndBloc_RecursiveRegistration: the base's (IKCinematicBloc_LevelReset) first, then unless the type is 4..7
    // registered once more and the stream component's when set.
    void RecursiveRegistration(int32_t type) override;
    // The run time (C2.2, package E3).
    void Start() override;                  // vt+0x5c 0x0018ced8 CKStreamAnimCinematicEndBloc_Start: the shared start
    void Complete() override;               // vt+0x64 0x0018d298 CKStreamAnimCinematicEndBloc_Complete: the shared completion
    void Update(IKTime* time) override;     // vt+0x68 0x0018cb40 CKStreamAnimCinematicEndBloc_Update: the stream stopped, the bloc completed
    void Stop() override;                   // vt+0x6c 0x0018c960 CKStreamAnimCinematicEndBloc_Stop: the shared completion, then Complete
    void Abort() override;                  // vt+0x70 0x0018c880 CKStreamAnimCinematicEndBloc_Abort: not running, then Complete

    IKSerializable* m_pStreamCpnt;  // +0x38 CKCinematicStreamCpnt in the files; 0 in the constructor
};
DOTD_ASSERT_SIZE(CKStreamAnimCinematicEndBloc, 0x3c);
DOTD_ASSERT_OFFSET(CKStreamAnimCinematicEndBloc, m_pStreamCpnt, +0x38);
