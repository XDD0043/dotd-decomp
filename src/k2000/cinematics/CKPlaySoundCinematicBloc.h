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
    // vt+0x24 0x001867c0 CKPlaySoundCinematicBloc_RecursiveRegistration: registered whatever the type (no 4..7 test),
    // then IKCinematicBloc_LevelReset 0x18e8d8 (which registers it once more unless 4..7).
    void RecursiveRegistration(int32_t type) override;
    // vt+0x5c 0x00186c68 CKPlaySoundCinematicBloc_Start: the blocs' common start, then the sound (when the index is not
    // -1) attached to the actor's node (when there is an actor), its volume, speed (the pitch) and loop (flags bit 7)
    // set and played from 0.
    void Start() override;
    // vt+0x64 0x00186fd0 CKPlaySoundCinematicBloc_Complete: the completion, then the sound stopped (with its fade).
    void Complete() override;
    // vt+0x68 0x001866e8 CKPlaySoundCinematicBloc_Update: unless its sekens stopped it or it loops (flags bit 7), the bloc
    // completes once the sound has no playing instance left.
    void Update(IKTime* time) override;
    // vt+0x6c 0x00186508 CKPlaySoundCinematicBloc_Stop: the completion inlined, then Complete (vt+0x64).
    void Stop() override;
    // vt+0x70 0x009a9e50 CKPlaySoundCinematicBloc_Abort: bit 0 of the element flags cleared.
    void Abort() override { m_DataFlags &= 0xfffffffeu; }

    int32_t m_i32SoundIndex;  // +0x38
    float m_fVolume;          // +0x3c
    float m_fPitch;           // +0x40
};
DOTD_ASSERT_SIZE(CKPlaySoundCinematicBloc, 0x44);
DOTD_ASSERT_OFFSET(CKPlaySoundCinematicBloc, m_i32SoundIndex, +0x38);
DOTD_ASSERT_OFFSET(CKPlaySoundCinematicBloc, m_fVolume, +0x3c);
DOTD_ASSERT_OFFSET(CKPlaySoundCinematicBloc, m_fPitch, +0x40);
