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
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x993f50
        return key == 0x14c || key == 0x3fe || key == 0xc;
    }

    CKLevel();  // 0x0002f0c8 CKLevel_Construct (inlined in CKLevel_Create 0x2fd30)
    ~CKLevel() override;

    static IKBaseClass* Create();                       // 0x0002fd30 CKLevel_Create
    static void Delete(IKBaseClass* object);
    // 0x0002fc28 CKLevel_CreateArray / 0x0002f5d8 CKLevel_DeleteArray (the registry's array factories: new[] with the
    // constructor inlined, the element size written; delete[]).
    static IKBaseClass* CreateArray(uint32_t count, uint16_t* elementSize);
    static void DeleteArray(IKBaseClass* first);
    // vt+0x20 0x0002f308 FindNonRecreableInstances (0), vt+0x24 0x0002f120 RecursiveRegistration (1) and vt+0x40
    // 0x0002fb80 GetInfo (1): the inherited defaults.

    void Destroy() override;  // vt+0x10 0x0002fbc8 CKLevel_Destroy
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0002fdb0 CKLevel_Load
    int32_t PostLoad(int32_t type) override;            // vt+0x30 0x0002fb90 CKLevel_PostLoad
    const uint32_t* GetGuid() override { return m_KGuidIdentifier; }  // vt+0x44 0x993ea0 CKLevel_GetGuid
    void Start() override;  // vt+0x50 0x0002f968 CKLevel_Start
    void Restart() override;  // vt+0x54 0x00030170 CKLevel_Restart
    // vt+0x68 0x0002f440 CKLevel_Stop: no sector requested (-2).
    void Stop() override { m_requestedSector = -2; }
    void Pause() override {}   // vt+0x70 0x0002f430 CKLevel_Pause (empty)
    void Resume() override {}  // vt+0x78 0x0002f438 CKLevel_Resume (empty)
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
    // 0x00030a48 CKLevel_EnterSector_maybe: unless it is the current sector, the sector is switched to (when it is not
    // loading already) and the game waits on the job queue (job 0xcb, StreamUntilSector) until it is the current one; a
    // host device in trouble (states 3..7) posts that state's message job (0xcc, 0xc8, 0xc9, 0xca, 0xca) instead. 1.
    uint8_t EnterSector(int32_t sector);
    // 0x000308a8 CKLevel_StreamUntilSector_maybe (the job callback; the sector is the job's user data): one streaming
    // step, then whether the sector is the current one.
    static uint8_t StreamUntilSector(void* level, int32_t id, void* sector);
    // 0x0004b688 CKLevel_EnterSector_HostFsStateJobCallback_maybe (CKLevel_2.cpp): done once the job no longer matches
    // the host device's state message (-1 for a working device).
    static uint8_t HostFsStateJobCallback(void* data, int32_t id, void* userData);
    uint8_t UnloadCurrentSector(int32_t unused);     // 0x00030448 CKLevel_UnloadCurrentSector
    // 0x0002f500 CKLevel_PostSectorLoad_maybe: the sector's load request posted, and waited for when `wait`; 1.
    // 0x000302b8 CKLevel_PostSectorLoadIfIdle_maybe: the same when no sector is unloading.
    // 0x00030378 CKLevel_RequestSector_maybe: the sector (-2: the default one) becomes the requested one and, when no
    // sector is unloading, is loaded (posted and waited for); 1. Sector 0 and -2 are ignored.
    // No caller of the three was found in the EBOOT (no bl, no vtable slot): ported for completeness.
    uint8_t PostSectorLoad(int32_t sector, int32_t wait);
    uint8_t PostSectorLoadIfIdle(int32_t sector, int32_t wait);
    uint8_t RequestSector(int32_t sector);
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
