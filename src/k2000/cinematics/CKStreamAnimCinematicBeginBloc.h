// CKStreamAnimCinematicBeginBloc.h - a streamed-animation cinematic step (key 0x388, vtable 0xb1bad0, size 0x3c). Original unit: CKStreamAnimCinematicBeginBloc.cpp.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/IKCinematicBloc.h"

class IKFile;

class CKStreamAnimCinematicBeginBloc : public IKCinematicBloc {
public:
    DOTD_CLASS_KEY(kCategoryCinematic, 0xe)
    DOTD_DECLARE_FACTORIES(CKStreamAnimCinematicBeginBloc)
    DOTD_BLOC_IS_KIND_OF()

    CKStreamAnimCinematicBeginBloc();  // 0x0018b818 CKStreamAnimCinematicBeginBloc_Create (the same stores as CKStreamAnimCinematicBeginBloc_Construct 0x18b260)
    ~CKStreamAnimCinematicBeginBloc() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0018b078 CKStreamAnimCinematicBeginBloc_Load

    IKSerializable* m_pStreamCpnt;  // +0x38 CKCinematicStreamCpnt in the files; 0 in the constructor
};
DOTD_ASSERT_SIZE(CKStreamAnimCinematicBeginBloc, 0x3c);
DOTD_ASSERT_OFFSET(CKStreamAnimCinematicBeginBloc, m_pStreamCpnt, +0x38);
