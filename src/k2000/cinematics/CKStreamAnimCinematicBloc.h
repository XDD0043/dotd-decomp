// CKStreamAnimCinematicBloc.h - a streamed-animation cinematic step (key 0x288, vtable 0xb1bb68, size 0x3c). Original unit: CKStreamAnimCinematicBloc.cpp.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/IKCinematicBloc.h"

class IKFile;
class IKTime;

class CKStreamAnimCinematicBloc : public IKCinematicBloc {
public:
    DOTD_CLASS_KEY(kCategoryCinematic, 0xa)
    DOTD_DECLARE_FACTORIES(CKStreamAnimCinematicBloc)
    DOTD_BLOC_IS_KIND_OF()

    CKStreamAnimCinematicBloc();  // 0x0018c520 CKStreamAnimCinematicBloc_Create (the same stores as CKStreamAnimCinematicBloc_Construct 0x18c040)
    ~CKStreamAnimCinematicBloc() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0018be90 CKStreamAnimCinematicBloc_Load
    // vt+0x24 0x0018bf78 CKStreamAnimCinematicBloc_RecursiveRegistration: the base's (IKCinematicBloc_LevelReset) first, then unless the type is 4..7
    // registered once more and the stream component's (not tested for null).
    void RecursiveRegistration(int32_t type) override;
    void Vf54() override;  // vt+0x54 0x0018bdc0 CKStreamAnimCinematicBloc_vf54: CKCinematicStreamCpnt_InitChannels_maybe(+0x38)
    // vt+0x50 0x0018bde8 CKStreamAnimCinematicBloc_ResetRuntime (the PreStart): the scene's chained scenes get
    // their flag +0x88 set and the stream's channels are reset.
    void PreStart() override;
    // The run time (C2.2, package E3).
    void Start() override;                  // vt+0x5c 0x0018c288 CKStreamAnimCinematicBloc_Start: the shared start
    void Complete() override;               // vt+0x64 0x0018c648 CKStreamAnimCinematicBloc_Complete: the stream finished, then the shared completion
    void Update(IKTime* time) override;     // vt+0x68 0x0018c168 CKStreamAnimCinematicBloc_Update: the stream read and played; at its end the bloc completes
    void Stop() override;                   // vt+0x6c 0x0018bbd8 CKStreamAnimCinematicBloc_Stop: the shared completion, Complete, then the stream stopped
    void Abort() override;                  // vt+0x70 0x0018baa0 CKStreamAnimCinematicBloc_Abort: not running, then Complete
    // vt+0x74 0x0018bb80 CKStreamAnimCinematicBloc_OnSceneStopped: a started stream finished and stopped.
    void OnSceneStopped() override;
    // vt+0x30 0x0018be30 CKStreamAnimCinematicBloc_PostLoad: IKCinematicBloc_PostLoad (1), then for a level the scene's
    // chained scenes get their flag +0x88 (the detectors pause during them).
    int32_t PostLoad(int32_t type) override;

    IKSerializable* m_pStreamCpnt;  // +0x38 CKCinematicStreamCpnt in the files; 0 in the constructor
};
DOTD_ASSERT_SIZE(CKStreamAnimCinematicBloc, 0x3c);
DOTD_ASSERT_OFFSET(CKStreamAnimCinematicBloc, m_pStreamCpnt, +0x38);
