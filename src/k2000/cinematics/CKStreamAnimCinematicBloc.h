// CKStreamAnimCinematicBloc.h - a streamed-animation cinematic step (key 0x288, vtable 0xb1bb68, size 0x3c). Original unit: CKStreamAnimCinematicBloc.cpp.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/IKCinematicBloc.h"

class IKFile;

class CKStreamAnimCinematicBloc : public IKCinematicBloc {
public:
    DOTD_CLASS_KEY(kCategoryCinematic, 0xa)
    DOTD_DECLARE_FACTORIES(CKStreamAnimCinematicBloc)
    DOTD_BLOC_IS_KIND_OF()

    CKStreamAnimCinematicBloc();  // 0x0018c520 CKStreamAnimCinematicBloc_Create (the same stores as CKStreamAnimCinematicBloc_Construct 0x18c040)
    ~CKStreamAnimCinematicBloc() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0018be90 CKStreamAnimCinematicBloc_Load
    void Vf54() override;  // vt+0x54 0x0018bdc0 CKStreamAnimCinematicBloc_vf54: CKCinematicStreamCpnt_InitChannels_maybe(+0x38)
    // vt+0x50 0x0018bde8 CKStreamAnimCinematicBloc_ResetRuntime (the PreStart): the scene's chained scenes get
    // their flag +0x88 set and the stream's channels are reset.
    void PreStart() override;

    IKSerializable* m_pStreamCpnt;  // +0x38 CKCinematicStreamCpnt in the files; 0 in the constructor
};
DOTD_ASSERT_SIZE(CKStreamAnimCinematicBloc, 0x3c);
DOTD_ASSERT_OFFSET(CKStreamAnimCinematicBloc, m_pStreamCpnt, +0x38);
