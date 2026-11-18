// CKLightningCinematicBloc.h - a cinematic bloc that strikes a lightning object effect between two beacons (key 0x6c8,
// vtable 0xb1b448, size 0xa0). Original unit: CKLightningCinematicBloc.cpp (0x17d0f0-0x17e7f0). Not in XXL2; no level
// file holds the class (nothing replays it). C2.8 port-final F01 ported it from the code; member names are ours.
// The bloc embeds the effect's data (a CKLightningObjectFxData at +0x38, loaded with the bloc); its Start places the
// data's two ends on the beacons +0x88 / +0x90 (tenths) and takes a free node of the data's class from the FX service's
// pools (CKSrvFx::AcquireFx). Flag 0x80 (m_DataFlags): the effect is struck again whenever it ends, for +0x98 seconds;
// without it the bloc completes when the effect ends.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/fx/CKLightningObjectFxData.h"
#include "k2000/misc/IKCinematicBloc.h"

class IKFile;
class IKFx;
class IKTime;

class CKLightningCinematicBloc : public IKCinematicBloc {
public:
    // vt+0x14 / +0x18 0x9a9878 / 0x9a9880: category 8 (cinematic), id 0x1b.
    DOTD_CLASS_KEY(kCategoryCinematic, 0x1b)
    // vt+0x08 0x009a9840 CKLightningCinematicBloc_IsKindOfClass [inline]: 0x6c8, 0x84c, 0x808, 0xc.
    DOTD_BLOC_IS_KIND_OF()
    // 0x0017d0f0 _Delete, 0x0017d1f0 _DeleteArray, 0x0017d2a0 _CreateArray, 0x0017e1a0 _Create.
    DOTD_DECLARE_FACTORIES(CKLightningCinematicBloc)

    // 0x0017e1a0 CKLightningCinematicBloc_Create: IKCinematicBloc_Construct, the vtables (the embedded data's), the two
    // beacon accessors 0xffff. The rest is the fresh heap's zeroes.
    CKLightningCinematicBloc();
    // 0x009a98a0 _Destructor / 0x009a9910 _DeletingDestructor [inline]: the vtables, the embedded data's destructor.
    ~CKLightningCinematicBloc() override {}

    // vt+0x10 0x0017da88 CKLightningCinematicBloc_Destroy: empty.
    void Destroy() override {}
    // vt+0x24 0x0017d1c8 CKLightningCinematicBloc_RecursiveRegistration: the base's, then 1: inherited.
    // vt+0x28 0x17d7b0 _Save: not ported (the saves are out of scope).
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0017d5e0 CKLightningCinematicBloc_Load
    // vt+0x58 0x009a9888 PreActivate [inline]: empty (the default).
    void Start() override;               // vt+0x5c 0x0017da90 CKLightningCinematicBloc_Start
    void Complete() override;            // vt+0x64 0x0017e238 CKLightningCinematicBloc_Complete
    void Update(IKTime* time) override;  // vt+0x68 0x0017e410 CKLightningCinematicBloc_Update
    void Stop() override;                // vt+0x6c 0x0017d3b0 CKLightningCinematicBloc_Stop
    // vt+0x70 0x009a9890 CKLightningCinematicBloc_Abort [inline]: not running (bit 0 cleared).
    void Abort() override { m_DataFlags &= 0xfffffffeu; }

    // The inlined effect strike of Start / Update: a free node of the data's class taken from the FX service's pools
    // (CKSrvFx::AcquireFx: data set, reserved, owner this bloc, started) into +0x80; without one the bloc completes.
    void StrikeEffect();
    // The inlined release of Stop / Update: a running node (bit 0 clear) stopped and released (vt+0x58), +0x80 cleared.
    void ReleaseRunningEffect();

    CKLightningObjectFxData m_lightningData;  // +0x38 (Load) the effect's data; +0x18..+0x2c of it are the two ends
    IKFx* m_pEffect;                          // +0x80 the node struck (Load clears it)
    uint32_t m_unk84;                         // +0x84 not used in the unit
    uint16_t m_aui16StartBeacon[4];           // +0x88 (Load, one 8-byte read, each half-word swapped) sector, kluster,
                                              //       id, index (CKSrvBeacon::GetBeaconData)
    uint16_t m_aui16EndBeacon[4];             // +0x90 (Load) the same
    float m_fDuration;                        // +0x98 (Load, after the data) flag 0x80: how long the strikes go on
    float m_fTimeLeft;                        // +0x9c Start: +0x98; Update counts it down
};
DOTD_ASSERT_SIZE(CKLightningCinematicBloc, 0xa0);
DOTD_ASSERT_OFFSET(CKLightningCinematicBloc, m_lightningData, 0x38);
DOTD_ASSERT_OFFSET(CKLightningCinematicBloc, m_pEffect, 0x80);
DOTD_ASSERT_OFFSET(CKLightningCinematicBloc, m_aui16StartBeacon, 0x88);
DOTD_ASSERT_OFFSET(CKLightningCinematicBloc, m_aui16EndBeacon, 0x90);
DOTD_ASSERT_OFFSET(CKLightningCinematicBloc, m_fDuration, 0x98);
DOTD_ASSERT_OFFSET(CKLightningCinematicBloc, m_fTimeLeft, 0x9c);
