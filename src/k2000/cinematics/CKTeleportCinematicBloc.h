// CKTeleportCinematicBloc.h - teleports an actor (key 0x788, vtable 0xb1bc98, size 0x88). Original unit: CKTeleportCinematicBloc.cpp.
// XXL2: the same members in the same load order; the target is four half-words in DotD.
// The ground-contact blocks are CKSrvCamera's XXL2 types (CGroundContactDatasIn/InOut).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/IKCinematicBloc.h"
#include "k2000/cameras/CKSrvCamera.h"

class IKFile;

class CKTeleportCinematicBloc : public IKCinematicBloc {
public:
    DOTD_CLASS_KEY(kCategoryCinematic, 0x1e)
    DOTD_DECLARE_FACTORIES(CKTeleportCinematicBloc)
    DOTD_BLOC_IS_KIND_OF()

    CKTeleportCinematicBloc();  // 0x0018d858 CKTeleportCinematicBloc_Create (the constructor inlined)
    ~CKTeleportCinematicBloc() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0018d900 CKTeleportCinematicBloc_Load

    void Start() override;                 // vt+0x5c 0x0018e400 CKTeleportCinematicBloc_Start
    void Complete() override;              // vt+0x64 0x0018e6e8 CKTeleportCinematicBloc_Complete
    void Update(IKTime* time) override;    // vt+0x68 0x0018e358 CKTeleportCinematicBloc_Update
    void Stop() override;                  // vt+0x6c 0x0018d5a0 CKTeleportCinematicBloc_Stop
    void Abort() override;                 // vt+0x70 0x0018d4c0 CKTeleportCinematicBloc_Abort
    uint8_t UsesActor() override { return 1; }  // vt+0x80 0x009aa498
    // 0x0018dd80 CKTeleportCinematicBloc_TeleportToBeacon_maybe: the actor's node put at the beacon (position in tenths, yaw
    // in 1/128 half turns), on the ground below it when bit 7 of the flags asks for it, its scale kept.
    void TeleportToBeacon();

    float m_fCurrentTime;                                // +0x38 runtime
    float m_fPauseTime;                                  // +0x3c
    uint16_t m_baTarget[4];                              // +0x40 XXL2 CKBeaconAccessor; 0xffff each in the constructor
    CKSrvCamera::CGroundContactDatasIn m_DatasIn;        // +0x48 the Load sets 0.5, 1.2, 1, 8
    CKSrvCamera::CGroundContactDatasInOut m_DatasInOut;  // +0x58
    uint32_t m_unk84;                                    // +0x84 DotD; not set by the constructor nor the Load
};
DOTD_ASSERT_SIZE(CKTeleportCinematicBloc, 0x88);
DOTD_ASSERT_OFFSET(CKTeleportCinematicBloc, m_fCurrentTime, +0x38);
DOTD_ASSERT_OFFSET(CKTeleportCinematicBloc, m_fPauseTime, +0x3c);
DOTD_ASSERT_OFFSET(CKTeleportCinematicBloc, m_baTarget, +0x40);
DOTD_ASSERT_OFFSET(CKTeleportCinematicBloc, m_DatasIn, +0x48);
DOTD_ASSERT_OFFSET(CKTeleportCinematicBloc, m_DatasInOut, +0x58);
DOTD_ASSERT_OFFSET(CKTeleportCinematicBloc, m_unk84, +0x84);
