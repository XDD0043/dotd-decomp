// CKPauseCinematicBloc.h - a cinematic pause (key 0x748, vtable 0xb1b740, size 0x40). Original unit: CKPauseCinematicBloc.cpp.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/IKCinematicBloc.h"

class IKFile;

class CKPauseCinematicBloc : public IKCinematicBloc {
public:
    DOTD_CLASS_KEY(kCategoryCinematic, 0x1d)
    DOTD_DECLARE_FACTORIES(CKPauseCinematicBloc)
    DOTD_BLOC_IS_KIND_OF()

    // 0x001846e0 CKPauseCinematicBloc_Create: IKCinematicBloc_Construct, then the vtable.
    CKPauseCinematicBloc() {}
    ~CKPauseCinematicBloc() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00184460 CKPauseCinematicBloc_Load

    void Start() override;                 // vt+0x5c 0x001847f0 CKPauseCinematicBloc_Start
    void Complete() override;              // vt+0x64 0x00184ab0 CKPauseCinematicBloc_Complete
    void Update(IKTime* time) override;    // vt+0x68 0x001843c0 CKPauseCinematicBloc_Update
    void Stop() override;                  // vt+0x6c 0x001841e0 CKPauseCinematicBloc_Stop
    void Abort() override;                 // vt+0x70 0x00184148 CKPauseCinematicBloc_Abort

    float m_fPauseTime;    // +0x38 (XXL2 name and load)
    float m_fCurrentTime;  // +0x3c (XXL2) runtime; not set by the constructor
};
DOTD_ASSERT_SIZE(CKPauseCinematicBloc, 0x40);
DOTD_ASSERT_OFFSET(CKPauseCinematicBloc, m_fPauseTime, +0x38);
DOTD_ASSERT_OFFSET(CKPauseCinematicBloc, m_fCurrentTime, +0x3c);
