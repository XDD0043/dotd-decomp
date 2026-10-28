// SectorRequest.cpp - reconstructed original translation unit 0x349a0-0x35470 (GAME_TOC1, main_toc1), 16 functions, 15 live.
// Primary owner: SectorRequest (not a registered class)
// Other owners: CKSector (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x349a0  SectorRequest_SetSector
//   [x] 0x349a8  SectorRequest_GetOperation
//   [x] 0x349b0  SectorRequest_GetSectorIndex
//   [ ] 0x349d8  SectorRequest_ApplyCompletionToLevel_maybe  [dead]
//   [ ] 0x34ab8  SectorRequest_IsPending
//   [ ] 0x34af8  SectorRequest_Destructor_2
//   [ ] 0x34b28  SectorRequest_Construct
//   [x] 0x34bc8  SectorRequest_Post
//   [ ] 0x34d38  SectorRequest_DeletingDestructor
//   [ ] 0x34d80  SectorRequest_Destructor
//   [x] 0x34db0  SectorRequest_Execute
//   [ ] 0x34e70  SectorRequest_GetSectorState
//   [x] 0x34ec8  CKSector_ConstructBase_maybe
//   [x] 0x34f68  SectorRequest_CheckDone
//   [x] 0x350e8  SectorRequest_Wait
//   [x] 0x35258  SectorRequest_RunSync
#include "k2000/misc/SectorRequest.h"

#include "k2000/logic/CKLevel.h"
#include "k2000/logic/CKSector.h"
#include "k2000/logic/io/CKLoadingManager.h"
#include "k2000/misc/CKGameLoop.h"
#include "k2000/misc/Engine.h"

namespace {
// The level's +0x2f flags after a sector request starts loading or finishes unloading: bit 0 cleared,
// bit 1 set (the original sets bit 0, then rewrites the byte as (b >> 2 << 2) | 2).
void MarkSectorFlags(CKLevel* level) {
    level->m_ba8GroundStateFlags = static_cast<uint8_t>((level->m_ba8GroundStateFlags & 0xfe) | 1);
    level->m_ba8GroundStateFlags = static_cast<uint8_t>(((level->m_ba8GroundStateFlags >> 2) << 2) | 2);
}

// The load's start (Post and RunSync with operation 0): the level's loading sector, the flags, the
// sector's start-loading triggers.
void BeginLoad(int32_t sector) {
    CKLevel* level = g_pEngine->m_level;
    level->m_i32NumLoadingSector = sector;
    MarkSectorFlags(level);
    static_cast<CKSector*>(g_pEngine->m_level->m_vpSectors.m_pBlock[sector])->QueueEnterEvent();
}

// The commit of a finished request (CheckDone, Wait, RunSync; inlined in each).
void Commit(const SectorRequest* request) {
    CKLevel* level = g_pEngine->m_level;
    if (request->m_operation == SectorRequest::kLoad) {
        if (level->m_currentSector != request->m_sector) level->m_currentSector = request->m_sector;
        g_pEngine->m_level->m_i32NumLoadingSector = -2;
        g_pEngine->m_level->m_bEndLoadingNeedWarning = 1;
        return;
    }
    if (level->m_currentSector != 0) level->m_currentSector = 0;
    g_pEngine->m_level->m_i32NumUnloadingSector = -2;
    MarkSectorFlags(g_pEngine->m_level);
}
}  // namespace

// 0x00034ec8 (Ghidra CKSector_ConstructBase_maybe): KRequest_Construct, then the request's own fields.
SectorRequest::SectorRequest() {
    m_unk60 = 0;  // the original stores it in a lwarx/stwcx. loop (an atomic store); nothing runs yet
    m_sector = -2;
    m_operation = 0;
}

// 0x000349b0 SectorRequest_GetSectorIndex: the stream index of the sector (a signed byte).
int8_t SectorRequest::GetSectorIndex() const {
    return static_cast<int8_t>(m_sector + g_pEngine->m_level->m_i8NumFirstStream - 1);
}

// 0x00034db0 SectorRequest_Execute (the load worker, or RunSync on the caller's thread)
void SectorRequest::Execute() {
    if (m_operation == kLoad) {
        g_pEngine->m_objectDatabase->LoadSector(GetSectorIndex(), 1, nullptr, nullptr);
        return;
    }
    if (m_operation != kUnload) return;
    g_pEngine->m_objectDatabase->UnloadSector(GetSectorIndex());
}

// 0x00034bc8 SectorRequest_Post
void SectorRequest::Post(int32_t operation) {
    Reset();  // vt+0x08
    m_operation = operation;
    if (operation == kLoad) BeginLoad(m_sector);
    g_pEngine->m_gameLoop->m_loadQueue.Enqueue(this);
    m_unk60 = 1;  // atomic store
}

// 0x00034f68 SectorRequest_CheckDone: 1 once the request finished and was committed.
uint32_t SectorRequest::CheckDone() {
    uint8_t succeeded = 0;
    IsFinished(&succeeded);
    if (succeeded == 0) return 0;
    Commit(this);
    m_unk60 = 0;  // atomic store
    return 1;
}

// 0x000350e8 SectorRequest_Wait: CheckDone's commit after KRequest_Wait.
void SectorRequest::Wait() {
    uint8_t succeeded = 0;
    KRequest::Wait(&succeeded);
    if (succeeded == 0) return;
    Commit(this);
    m_unk60 = 0;  // atomic store
}

// 0x00035258 SectorRequest_RunSync: Post's start, Execute on this thread, the commit.
void SectorRequest::RunSync(int32_t operation) {
    Reset();  // vt+0x08
    m_operation = operation;
    if (operation == kLoad) BeginLoad(m_sector);
    Execute();  // vt+0x18
    Commit(this);
}
