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
    // vt+0x24 0x00175d28 CKCharacterControlBloc_RecursiveRegistration: registered (unless 4..7), the base's, then for a level file
    // (type 0) the hero's and the beacon's (type 0 passed).
    void RecursiveRegistration(int32_t type) override;

    // vt+0x5c 0x00175ff0 CKCharacterControlBloc_Start: the blocs' start (StartCommon), then the controllable hero (+0x38)
    // bound and sent to the marker beacon (+0x3c: its position and the at row of its orientation; zeros without one).
    void Start() override;
    // vt+0x64 0x00176500 CKCharacterControlBloc_Complete: CompleteBloc, then the hero detached (vt+0x58).
    void Complete() override;
    // vt+0x68 0x00175c28 CKCharacterControlBloc_Update: completed once the hero's move-to ends (vt+0x54 answers non-zero).
    void Update(IKTime* time) override;
    // vt+0x70 0x00175968 CKCharacterControlBloc_Abort (the scene's Stop): bit 0 of the element flags cleared, then
    // Complete (vt+0x64), which detaches the hero.
    void Abort() override;
    // vt+0x6c 0x00175a48 CKCharacterControlBloc_Stop: CompleteBloc, then Complete (vt+0x64).
    void Stop() override;

    IKSerializable* m_unk38;  // +0x38 CKControlableHero in the files
    IKSerializable* m_unk3c;  // +0x3c CKMarkerBeacon in the files
};
DOTD_ASSERT_SIZE(CKCharacterControlBloc, 0x40);
DOTD_ASSERT_OFFSET(CKCharacterControlBloc, m_unk38, +0x38);
DOTD_ASSERT_OFFSET(CKCharacterControlBloc, m_unk3c, +0x3c);
