// CKStreamAnimCinematicEndBloc.h - a streamed-animation cinematic step (key 0x3c8, vtable 0xb1bc00, size 0x3c). Original unit: CKStreamAnimCinematicEndBloc.cpp.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/IKCinematicBloc.h"

class IKFile;

class CKStreamAnimCinematicEndBloc : public IKCinematicBloc {
public:
    DOTD_CLASS_KEY(kCategoryCinematic, 0xf)
    DOTD_DECLARE_FACTORIES(CKStreamAnimCinematicEndBloc)
    DOTD_BLOC_IS_KIND_OF()

    CKStreamAnimCinematicEndBloc();  // 0x0018d170 CKStreamAnimCinematicEndBloc_Create (the same stores as CKStreamAnimCinematicEndBloc_Construct 0x18cdb0)
    ~CKStreamAnimCinematicEndBloc() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0018cbc8 CKStreamAnimCinematicEndBloc_Load

    IKSerializable* m_pStreamCpnt;  // +0x38 CKCinematicStreamCpnt in the files; 0 in the constructor
};
DOTD_ASSERT_SIZE(CKStreamAnimCinematicEndBloc, 0x3c);
DOTD_ASSERT_OFFSET(CKStreamAnimCinematicEndBloc, m_pStreamCpnt, +0x38);
