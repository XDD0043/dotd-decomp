// CKStreamAnimCinematicBeginBloc.h - a streamed-animation cinematic step (key 0x388, vtable 0xb1bad0, size 0x3c). Original unit: CKStreamAnimCinematicBeginBloc.cpp.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/IKCinematicBloc.h"

class IKFile;
class IKTime;

class CKStreamAnimCinematicBeginBloc : public IKCinematicBloc {
public:
    DOTD_CLASS_KEY(kCategoryCinematic, 0xe)
    DOTD_DECLARE_FACTORIES(CKStreamAnimCinematicBeginBloc)
    DOTD_BLOC_IS_KIND_OF()

    CKStreamAnimCinematicBeginBloc();  // 0x0018b818 CKStreamAnimCinematicBeginBloc_Create (the same stores as CKStreamAnimCinematicBeginBloc_Construct 0x18b260)
    ~CKStreamAnimCinematicBeginBloc() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0018b078 CKStreamAnimCinematicBeginBloc_Load
    // vt+0x24 0x0018b160 CKStreamAnimCinematicBeginBloc_RecursiveRegistration: the base's (IKCinematicBloc_LevelReset) first, then unless the type is 4..7
    // registered once more and the stream component's when set.
    void RecursiveRegistration(int32_t type) override;
    // The run time (C2.2, package E3).
    void Start() override;                  // vt+0x5c 0x0018b4a0 CKStreamAnimCinematicBeginBloc_Start: the shared start, then the stream started with media
    void Complete() override;               // vt+0x64 0x0018b878 CKStreamAnimCinematicBeginBloc_Complete: the shared completion
    void Update(IKTime* time) override;     // vt+0x68 0x0018b388 CKStreamAnimCinematicBeginBloc_Update: the stream read ahead; once ready the bloc completes
    void Stop() override;                   // vt+0x6c 0x0018ae98 CKStreamAnimCinematicBeginBloc_Stop: the shared completion, then Complete
    void Abort() override;                  // vt+0x70 0x0018adb8 CKStreamAnimCinematicBeginBloc_Abort: not running, then Complete

    IKSerializable* m_pStreamCpnt;  // +0x38 CKCinematicStreamCpnt in the files; 0 in the constructor
};
DOTD_ASSERT_SIZE(CKStreamAnimCinematicBeginBloc, 0x3c);
DOTD_ASSERT_OFFSET(CKStreamAnimCinematicBeginBloc, m_pStreamCpnt, +0x38);
