// SectorRequest.h - the request that streams one sector in or out (vtable 0xb14308, size 0x70). Original
// unit: SectorRequest.cpp (0x349a0-0x35470). Every CKSector embeds one at +0x50.
//
// Operation 0 loads the sector's file (CKLoadingManager_LoadSector), 1 unloads its objects
// (CKLoadingManager_UnloadSector). Post queues it on the game loop's CKLoadRequestQueue; CheckDone / Wait
// then commit the result to the level (current / loading / unloading sector numbers). The stream index is
// the sector number + CKLevel +0x2c - 1.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/KRequest.h"

class SectorRequest : public KRequest {
public:
    enum Operation : int32_t { kLoad = 0, kUnload = 1 };

    SectorRequest();  // 0x00034ec8 (Ghidra CKSector_ConstructBase_maybe)
    ~SectorRequest() override {}  // vt+0x00 0x34d80 (KRequest's)

    void Execute() override;  // vt+0x18 0x34db0 SectorRequest_Execute (load worker)

    void SetSector(int32_t sector) { m_sector = sector; }  // 0x000349a0 SectorRequest_SetSector
    int32_t GetOperation() const { return m_operation; }    // 0x000349a8 SectorRequest_GetOperation
    int8_t GetSectorIndex() const;                          // 0x000349b0 SectorRequest_GetSectorIndex
    void Post(int32_t operation);                           // 0x00034bc8 SectorRequest_Post
    uint32_t CheckDone();                                   // 0x00034f68 SectorRequest_CheckDone
    void Wait();                                            // 0x000350e8 SectorRequest_Wait
    void RunSync(int32_t operation);                        // 0x00035258 SectorRequest_RunSync

    uint32_t m_unk60;   // +0x60 1 while posted (atomic stores), cleared when CheckDone/Wait commit
    int32_t m_sector;   // +0x64 -2; CKSector_PostLoad sets the sector number (SetSector)
    int32_t m_operation;  // +0x68 Operation
    uint32_t m_unk6c;   // +0x6c not set by the constructor
};
DOTD_ASSERT_SIZE(SectorRequest, 0x70);
DOTD_ASSERT_OFFSET(SectorRequest, m_unk60, 0x60);
DOTD_ASSERT_OFFSET(SectorRequest, m_sector, 0x64);
DOTD_ASSERT_OFFSET(SectorRequest, m_operation, 0x68);
