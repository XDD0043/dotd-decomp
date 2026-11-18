// CKBlackBandBloc.h - shows or hides the black bands (key 0x2c8, vtable 0xb1b0a0, size 0x3c). Original unit: CKBlackBandBloc.cpp.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/IKCinematicBloc.h"

class IKFile;
class IKTime;

class CKBlackBandBloc : public IKCinematicBloc {
public:
    DOTD_CLASS_KEY(kCategoryCinematic, 0xb)
    DOTD_DECLARE_FACTORIES(CKBlackBandBloc)
    DOTD_BLOC_IS_KIND_OF()

    // 0x001751a8 CKBlackBandBloc_Create: IKCinematicBloc_Construct, then the vtable.
    CKBlackBandBloc() {}
    ~CKBlackBandBloc() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00174fa0 CKBlackBandBloc_Load
    // vt+0x24 0x00175070 CKBlackBandBloc_RecursiveRegistration: registered with the saving manager (vt+0x24) unless the type is 4..7, then
    // IKCinematicBloc_LevelReset 0x18e8d8 (which registers it once more).
    void RecursiveRegistration(int32_t type) override;
    // vt+0x5c 0x001752c0 CKBlackBandBloc_Start: the blocs' common start (inlined), then the cinematic service's band bits
    // 4 / 5 cleared and, by the mode (+0x38): 1 every playing scene without a pending entry (+0x40) starts its entry
    // transition (bit 4 set), 2 every playing scene starts its exit transition (bit 5 set) unless its bands are kept
    // (+0x34 bit 6) with no pending entry.
    void Start() override;
    void Complete() override;           // vt+0x64 0x00175740 CKBlackBandBloc_Complete: the completion
    void Update(IKTime* time) override;  // vt+0x68 0x00174f38 CKBlackBandBloc_Update: completed at once (unless its sekens stopped it)
    void Stop() override;               // vt+0x6c 0x00174d58 CKBlackBandBloc_Stop: the completion, then Complete
    void Abort() override;              // vt+0x70 0x00174aa8 CKBlackBandBloc_Abort: not running
    // The out-of-line copies of Start's two band codes (dead in the original): 0x00174b88 / 0x00174c70.
    static void StartSceneExitTransitions();
    static void StartSceneEntryTransitions();

    uint32_t m_unk38;  // +0x38 (2 in the LVL010 files; _maybe the band mode)
};
DOTD_ASSERT_SIZE(CKBlackBandBloc, 0x3c);
DOTD_ASSERT_OFFSET(CKBlackBandBloc, m_unk38, +0x38);
