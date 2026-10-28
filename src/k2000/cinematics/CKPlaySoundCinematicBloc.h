// CKPlaySoundCinematicBloc.h - plays a sound (key 0x708, vtable 0xb1b870, size 0x44). Original unit: CKPlaySoundCinematicBloc.cpp.
// XXL2: the same members in the same load order.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/IKCinematicBloc.h"

class IKFile;

class CKPlaySoundCinematicBloc : public IKCinematicBloc {
public:
    DOTD_CLASS_KEY(kCategoryCinematic, 0x1c)
    DOTD_DECLARE_FACTORIES(CKPlaySoundCinematicBloc)
    DOTD_BLOC_IS_KIND_OF()

    // 0x001868e8 CKPlaySoundCinematicBloc_Create: IKCinematicBloc_Construct, then the vtable.
    CKPlaySoundCinematicBloc() {}
    ~CKPlaySoundCinematicBloc() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00186a00 CKPlaySoundCinematicBloc_Load

    int32_t m_i32SoundIndex;  // +0x38
    float m_fVolume;          // +0x3c
    float m_fPitch;           // +0x40
};
DOTD_ASSERT_SIZE(CKPlaySoundCinematicBloc, 0x44);
DOTD_ASSERT_OFFSET(CKPlaySoundCinematicBloc, m_i32SoundIndex, +0x38);
DOTD_ASSERT_OFFSET(CKPlaySoundCinematicBloc, m_fVolume, +0x3c);
DOTD_ASSERT_OFFSET(CKPlaySoundCinematicBloc, m_fPitch, +0x40);
