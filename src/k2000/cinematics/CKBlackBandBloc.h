// CKBlackBandBloc.h - shows or hides the black bands (key 0x2c8, vtable 0xb1b0a0, size 0x3c). Original unit: CKBlackBandBloc.cpp.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/IKCinematicBloc.h"

class IKFile;

class CKBlackBandBloc : public IKCinematicBloc {
public:
    DOTD_CLASS_KEY(kCategoryCinematic, 0xb)
    DOTD_DECLARE_FACTORIES(CKBlackBandBloc)
    DOTD_BLOC_IS_KIND_OF()

    // 0x001751a8 CKBlackBandBloc_Create: IKCinematicBloc_Construct, then the vtable.
    CKBlackBandBloc() {}
    ~CKBlackBandBloc() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00174fa0 CKBlackBandBloc_Load

    uint32_t m_unk38;  // +0x38 (2 in the LVL010 files; _maybe the band mode)
};
DOTD_ASSERT_SIZE(CKBlackBandBloc, 0x3c);
DOTD_ASSERT_OFFSET(CKBlackBandBloc, m_unk38, +0x38);
