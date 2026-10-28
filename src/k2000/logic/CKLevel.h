// CKLevel.h - the current level and its sectors (key 0x14c, vtable 0xb14010, size 0x48). Original
// units: CKLevel.cpp, CKLevel_2.cpp. XXL2: K/KCore/Level/CKLevel.h, the same members in the same order
// (the mutex is one word here), plus DotD's reference at +0x34. Sector streaming (C2.0): the requested
// sector is loaded through its CKSector's SectorRequest; sector 0 is the level's base sector (always
// loaded), the others stream STRlllss.KP3 files.
#pragma once
#include <cstdint>

#include "k2000/core/IKUpdatable.h"
#include "k2000/core/Layout.h"
#include "k2000/util/TVector.h"

class CKLevel : public IKUpdatable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 5)

    CKLevel();  // 0x0002f0c8 CKLevel_Construct (inlined in CKLevel_Create 0x2fd30)
    ~CKLevel() override;

    static IKBaseClass* Create();                       // 0x0002fd30 CKLevel_Create
    static void Delete(IKBaseClass* object);

    void Destroy() override;  // vt+0x10 0x0002fbc8 CKLevel_Destroy
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0002fdb0 CKLevel_Load
    int32_t PostLoad(int32_t type) override;            // vt+0x30 0x0002fb90 CKLevel_PostLoad
    const uint32_t* GetGuid() override { return m_KGuidIdentifier; }  // vt+0x44 0x993ea0 CKLevel_GetGuid
    void Start() override;  // vt+0x50 0x0002f968 CKLevel_Start
    void Stop() override {}
    void Pause() override {}
    void Resume() override {}
    // vt+0x7c 0x00030c88 CKLevel_Update: one streaming step; when a sector load finished since the last frame
    // (m_bEndLoadingNeedWarning) the sector becomes active: its root joins the main scene root, the game loop
    // announces it (vt+0x84 / +0x88) and its end-of-loading starters are queued. Then the hero's position decides
    // which sector is requested and the active sector's (and the base sector's) mesh klusters are updated.
    void Update(IKTime* frameClock) override;
    // vt+0x84 0x0002f7d8 CKLevel_PreSectorLoaded / vt+0x88 0x000300a8 CKLevel_SectorLoaded (CKGameLoop calls these
    // first): every CKSector told (vt+0x50 / +0x54); SectorLoaded then enables the trigger domains of the sector.
    void PreSectorLoaded(int32_t sector) override;
    void SectorLoaded(int32_t sector) override;
    // The sector `sector` goes (CKGameLoop_SectorUnload / PostSectorUnload call these first): its trigger
    // domains disabled, every CKSector told (CKSector vt+0x58 / vt+0x5c).
    void SectorUnload(int32_t sector) override;      // vt+0x8c 0x0002f718 CKLevel_SectorUnload
    void PostSectorUnload(int32_t sector) override;  // vt+0x90 0x0002f680 CKLevel_PostSectorUnload

    int32_t GetDefaultSector();                      // 0x0002f450 CKLevel_GetDefaultSector_maybe
    // 0x0002f150 CKLevel_IterateActiveSectors: the sectors that are drawn, one by one: with no `previous` the current sector
    // when it is loaded (its properties bit 0), else sector 0; after a sector other than 0 comes sector 0; then null.
    class CKSector* IterateActiveSectors(const class CKSector* previous);
    void UpdateSectorStreaming();                    // 0x000305d8 CKLevel_UpdateSectorStreaming
    uint8_t SwitchToSector(int32_t sector, int32_t wait);  // 0x00030908 CKLevel_SwitchToSector
    uint8_t UnloadCurrentSector(int32_t unused);     // 0x00030448 CKLevel_UnloadCurrentSector
    // 0x000306a0 CKLevel_UpdateUnloadSectors_maybe: one streaming step, and when nothing is loading or
    // unloading, the current sector (and, unless m_bCommunNeedWarning, the base sector 0) deactivated.
    // Returns 1 then, else 0.
    uint32_t UpdateUnloadSectors();
    // vt+0x6c is UpdateUnloadSectors itself (CKGameLoop's mode 9 asks it every frame until the level agrees).
    int32_t Vf6C() override { return static_cast<int32_t>(UpdateUnloadSectors()); }
    void ClearLoadingSector();                       // 0x0002f140 CKLevel_ClearLoadingSector
    void ResetSectorState();                         // 0x0002f128 CKLevel_ResetSectorState_maybe

    TVector<IKSerializable*, 1> m_vpSectors;  // +0x04 XXL2 m_vpSectors: CKSector* (key 0x10c), one per sector
    uint32_t m_unk10;                // +0x10 XXL2 m_kAsyncFlagsMutex_maybe (between the vector and the level number); not set
    uint32_t m_ui32NbSectors;        // +0x14 (CKSrvBeacon's memory-card branch reads it)
    int32_t m_currentSector;         // +0x18 (live-verified) XXL2 m_i32NumPlayingSector, 0 = none; not set by the constructor
    int32_t m_defaultSector;         // +0x1c XXL2 m_ai32NumEntrySector[0]
    int32_t m_i32NumLoadingSector;   // +0x20 -2
    int32_t m_i32NumUnloadingSector; // +0x24 -2
    int32_t m_requestedSector;       // +0x28 -2; _maybe the target sector (Ghidra nRequestedSector), XXL2 m_i32NumPostBreakingSector
    int8_t m_i8NumFirstStream;       // +0x2c
    uint8_t m_bEndLoadingNeedWarning;  // +0x2d 0
    uint8_t m_bCommunNeedWarning;      // +0x2e not set
    uint8_t m_ba8GroundStateFlags;     // +0x2f not set
    uint32_t m_ui32ProjectVersionNumber;  // +0x30
    IKSerializable* m_unk34;         // +0x34 DotD only: a reference (LVL000: CKTriggerSynchro 0x56cc); read first
    uint32_t m_KGuidIdentifier[4];   // +0x38 CGuid (Uuid_Read)
};
DOTD_ASSERT_SIZE(CKLevel, 0x48);
DOTD_ASSERT_OFFSET(CKLevel, m_vpSectors, 0x04);
DOTD_ASSERT_OFFSET(CKLevel, m_ui32NbSectors, 0x14);
DOTD_ASSERT_OFFSET(CKLevel, m_currentSector, 0x18);
DOTD_ASSERT_OFFSET(CKLevel, m_defaultSector, 0x1c);
DOTD_ASSERT_OFFSET(CKLevel, m_requestedSector, 0x28);
DOTD_ASSERT_OFFSET(CKLevel, m_i8NumFirstStream, 0x2c);
DOTD_ASSERT_OFFSET(CKLevel, m_ui32ProjectVersionNumber, 0x30);
DOTD_ASSERT_OFFSET(CKLevel, m_unk34, 0x34);
DOTD_ASSERT_OFFSET(CKLevel, m_KGuidIdentifier, 0x38);
