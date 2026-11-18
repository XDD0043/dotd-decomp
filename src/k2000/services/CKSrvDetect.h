// CKSrvDetect.h - the detection service (key 0x4c1, vtable 0xb1c2a0, size 0x18). Original unit:
// CKSrvDetect.cpp (0x1a6b70-0x1a8120). XXL2: K/KServices/KServiceDetect/CKSrvDetect.h, the same two
// members read in the same order; +0x14 is DotD's.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/services/IKService.h"

class CKSrvDetect : public IKService {
public:
    DOTD_CLASS_KEY(kCategoryService, 0x13)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9aae68
        return key == 0x4c1 || key == 0x1 || key == 0x3fe || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKSrvDetect)

    CKSrvDetect();  // 0x001a7580 CKSrvDetect_Construct
    // 0x001a7ec0 CKSrvDetect_Destructor (0x1a7f20 Destructor_2 the same, 0x1a7e58 DeletingDestructor + delete): the
    // engine's detection service cleared (Engine_SetSrvDetect(0)).
    ~CKSrvDetect() override;

    void Destroy() override;  // vt+0x10 0x001a7530 CKSrvDetect_Destroy
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001a78e0 CKSrvDetect_Load
    void Start() override { m_unk14 = 0; }             // vt+0x50 0x1a7320 CKSrvDetect_Start: no cinematic suspends
    void Restart() override { m_unk14 = 0; }           // vt+0x54 0x1a7338 CKSrvDetect_Restart: the same
    // vt+0x24 0x001a7718 CKSrvDetect_RecursiveRegistration: for type 4 every sector's detector list (CKSector +0x38)
    // gets RecursiveRegistration(4); the service itself is not registered.
    void RecursiveRegistration(int32_t type) override;
    void Stop() override {}                             // vt+0x68 0x1a7380 CKSrvDetect_Stop (empty)
    void Pause() override {}                            // vt+0x70 0x1a7378 CKSrvDetect_Pause (empty)
    void Resume() override {}                           // vt+0x78 0x1a7388 CKSrvDetect_Resume (empty)
    // vt+0x7c 0x001a7c30 UpdateCKSrvDetect: while the clock runs and no cinematic suspends it: every drawn sector's
    // detectors run (CKSrvDetect_RunDetectors_maybe), then every detected-movable list takes its movables' positions
    // as their old ones (CKSrvDetect_RefreshDetectablePositions_maybe).
    void Update(IKTime* time) override;
    // vt+0x8c 0x001a7860 CKSrvDetect_SectorUnload: every detected-movable list forgets that its entries of
    // the sector are loaded.
    // vt+0x84 0x001a7488 CKSrvDetect_PreSectorLoaded: every detected-movable list activates its entries of the
    // sector. vt+0x88 0x1a7330 (SectorLoaded) is a bare return.
    void PreSectorLoaded(int32_t sector) override;
    // vt+0x38 0x001a77e8 CKSrvDetect_SetDefaultState: every sector's detectors back to their enabled-at-load bit
    // (DetectorList_ResetEnabledToDefault_maybe 0x1a8090: vt+0x58 with +0x04 bit 5).
    void SetDefaultState(int32_t flag) override;
    void SectorUnload(int32_t sector) override;
    // vt+0x94 0x1a7a68 CKSrvDetect_InitializeService: no detected-movable list yet, returns 1.
    int32_t InitializeService() override {
        m_apDetectedMovable = nullptr;
        m_ui32NbDetectedMovable = 0;
        return 1;
    }
    void DestroyService() override {}                   // vt+0x98 0x1a7310 (empty)
    // vt+0x9c 0x001a7d90 CKSrvDetect_UpdateInitialize: every sector's detectors lose their detection bits 1-3
    // (DetectorList_ClearDetectionFlags_maybe 0x1a8518), then every detected-movable list refreshes its old positions.
    void UpdateInitialize() override;

    // 0x001a7348 CKSrvDetect_BeginCinematic_maybe: one more scene suspends the detection refresh (+0x14).
    // 0x001a7d08 CKSrvDetect_EndCinematic_maybe: the last scene to end lets the detection refresh again and refreshes the
    // old positions of every detected-movable list.
    void BeginCinematic() { ++m_unk14; }
    void EndCinematic();
    IKSerializable** m_apDetectedMovable;  // +0x0c CKDetectedMovable* (Mem_AllocAligned16)
    uint32_t m_ui32NbDetectedMovable;      // +0x10
    uint32_t m_unk14;                      // +0x14 the constructor sets 0
};
DOTD_ASSERT_SIZE(CKSrvDetect, 0x18);
DOTD_ASSERT_OFFSET(CKSrvDetect, m_ui32Priority, 0x08);
DOTD_ASSERT_OFFSET(CKSrvDetect, m_apDetectedMovable, 0x0c);
DOTD_ASSERT_OFFSET(CKSrvDetect, m_ui32NbDetectedMovable, 0x10);
DOTD_ASSERT_OFFSET(CKSrvDetect, m_unk14, 0x14);
