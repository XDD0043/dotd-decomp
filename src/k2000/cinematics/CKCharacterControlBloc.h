// CKCharacterControlBloc.h - gives or takes the hero control (key 0x348, vtable 0xb1b138, size 0x40). Original unit: CKCharacterControlBloc.cpp.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/IKCinematicBloc.h"

class IKFile;

class CKCharacterControlBloc : public IKCinematicBloc {
public:
    DOTD_CLASS_KEY(kCategoryCinematic, 0xd)
    DOTD_DECLARE_FACTORIES(CKCharacterControlBloc)
    DOTD_BLOC_IS_KIND_OF()

    // 0x00175f98 CKCharacterControlBloc_Create: IKCinematicBloc_Construct, then the vtable.
    CKCharacterControlBloc() {}
    ~CKCharacterControlBloc() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001763b0 CKCharacterControlBloc_Load

    IKSerializable* m_unk38;  // +0x38 CKControlableHero in the files
    IKSerializable* m_unk3c;  // +0x3c CKMarkerBeacon in the files
};
DOTD_ASSERT_SIZE(CKCharacterControlBloc, 0x40);
DOTD_ASSERT_OFFSET(CKCharacterControlBloc, m_unk38, +0x38);
DOTD_ASSERT_OFFSET(CKCharacterControlBloc, m_unk3c, +0x3c);
