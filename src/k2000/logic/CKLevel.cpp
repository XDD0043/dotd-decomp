// CKLevel.cpp - reconstructed original translation unit 0x2f078-0x31308 (GAME_TOC1, main_toc1), 51 functions, 39 live.
// Primary class: CKLevel  key 0x14c  category Logic  size 0x48  vtable 0xb14010
// Other owners: Game (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x2f078  CKLevel_Delete  (stubs/BootStubs.cpp: new / delete)
//   [x] 0x2f0c8  CKLevel_Construct  [dead]
//   [x] 0x2f120  CKLevel_RecursiveRegistration  (1: the inherited default)
//   [x] 0x2f128  CKLevel_ResetSectorState_maybe
//   [x] 0x2f140  CKLevel_ClearLoadingSector
//   [x] 0x2f150  CKLevel_IterateActiveSectors
//   [ ] 0x2f1c8  CKLevel_PauseSectorServices_maybe  [dead]
//   [ ] 0x2f2a0  CKLevel_ResumeSectorServices_maybe  [dead]
//   [x] 0x2f308  CKLevel_FindNonRecreableInstances  (0: the inherited default)
//   [ ] 0x2f310  CKLevel_NotifyGameLoopSectorLoadActivate_maybe  [dead]
//   [ ] 0x2f3a0  CKLevel_NotifyGameLoopSectorDeactivateUnload_maybe  [dead]
//   [x] 0x2f430  CKLevel_Pause  (empty)
//   [x] 0x2f438  CKLevel_Resume  (empty)
//   [x] 0x2f440  CKLevel_Stop
//   [x] 0x2f450  CKLevel_GetDefaultSector_maybe
//   [ ] 0x2f460  FUN_0002f460  [dead]
//   [ ] 0x2f478  RegisterCKLevelClass
//   [ ] 0x2f4f0  _GLOBAL__I_2f4f0
//   [x] 0x2f500  CKLevel_PostSectorLoad_maybe
//   [x] 0x2f590  Game_GetCurrentLevelNumber_maybe  (local copy)
//   [x] 0x2f5d8  CKLevel_DeleteArray
//   [x] 0x2f680  CKLevel_PostSectorUnload
//   [x] 0x2f718  CKLevel_SectorUnload
//   [x] 0x2f7d8  CKLevel_PreSectorLoaded
//   [ ] 0x2f870  CKLevel_Construct_2  [dead]
//   [ ] 0x2f8c8  CKLevel_PauseNonBaseSectorServices_maybe  [dead]
//   [x] 0x2f968  CKLevel_Start
//   [ ] 0x2fa28  CKLevel_FinishPendingSectorRequest_maybe  [dead]
//   [ ] 0x2fae0  CKLevel_ResumeNonBaseSectorServices_maybe  [dead]
//   [x] 0x2fb80  CKLevel_GetInfo  (1: the inherited default)
//   [ ] 0x2fb88  CKLevel_Save
//   [x] 0x2fb90  CKLevel_PostLoad
//   [x] 0x2fbc8  CKLevel_Destroy
//   [x] 0x2fc28  CKLevel_CreateArray
//   [x] 0x2fd30  CKLevel_Create  (stubs/BootStubs.cpp: new / delete)
//   [x] 0x2fdb0  CKLevel_Load
//   [x] 0x300a8  CKLevel_SectorLoaded
//   [x] 0x30170  CKLevel_Restart
//   [x] 0x302b8  CKLevel_PostSectorLoadIfIdle_maybe
//   [x] 0x30378  CKLevel_RequestSector_maybe
//   [x] 0x30448  CKLevel_UnloadCurrentSector
//   [x] 0x305d8  CKLevel_UpdateSectorStreaming
//   [x] 0x306a0  CKLevel_UpdateUnloadSectors_maybe
//   [x] 0x308a8  CKLevel_StreamUntilSector_maybe
//   [x] 0x30908  CKLevel_SwitchToSector
//   [x] 0x30a48  CKLevel_EnterSector_maybe
//   [ ] 0x30b88  CKLevel_SwitchToSectorContainingPoint_maybe  [dead]
//   [x] 0x30c88  CKLevel_Update
//   [x] 0x31180  CKLevel_DeletingDestructor
//   [x] 0x31208  CKLevel_Destructor
//   [ ] 0x31288  CKLevel_Destructor_2  [dead]
//
//   [ ] 0x993e88  CKLevel_GetClassType  [inline]
//   [ ] 0x993e90  CKLevel_GetClassID  [inline]
//   [ ] 0x993e98  CKLevel_GetSerializationFlags  [inline]
//   [ ] 0x993ea0  CKLevel_GetGuid  [inline]
//   [ ] 0x993f50  CKLevel_IsKindOfClass  [inline]
#include "k2000/logic/CKLevel.h"

#include "k2000/logic/CKSector.h"
#include "k2000/scenegraph/CSGSectorRoot.h"

#include "k2000/core/Stub.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKSector.h"
#include "k2000/logic/CKTriggerSynchro.h"
#include "k2000/scenegraph/CSGBranch.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/logic/GameVector.h"
#include "k2000/managers/CKGraphic.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/CKGameLoop.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/JobQueue.h"
#include "k2000/io/KHostFS.h"
#include "k2000/render/CRenderer.h"

// 0x0002f0c8 CKLevel_Construct (the same stores inlined in CKLevel_Create 0x2fd30)
CKLevel::CKLevel() {
    m_vpSectors.m_pBlock = nullptr;
    m_vpSectors.m_ui32NbElt = 1;
    m_vpSectors.m_ui32NbUsedElt = 0;
    m_KGuidIdentifier[3] = 0;
    m_KGuidIdentifier[0] = 0;
    m_KGuidIdentifier[1] = 0;
    m_KGuidIdentifier[2] = 0;
    m_bEndLoadingNeedWarning = 0;
    m_requestedSector = -2;
    m_unk34 = nullptr;
    m_i32NumLoadingSector = -2;
    m_i32NumUnloadingSector = -2;
    m_ui32ProjectVersionNumber = 0;
}

// 0x00031208 CKLevel_Destructor (0x00031180 CKLevel_DeletingDestructor: the same, then the delete): the sector vector's
// block freed, its length and block cleared (the inlined vector destructor).
CKLevel::~CKLevel() {
    if (m_vpSectors.m_pBlock != nullptr) Mem_FreeAligned16(m_vpSectors.m_pBlock);
    m_vpSectors.m_ui32NbUsedElt = 0;
    m_vpSectors.m_pBlock = nullptr;
}

// 0x0002fbc8 CKLevel_Destroy: no dynamic scene root, the sector list freed.
void CKLevel::Destroy() {
    Engine_SetDynamicSceneRoot(nullptr);  // 0x24cb0
    if (m_vpSectors.m_pBlock != nullptr) {
        Mem_FreeAligned16(m_vpSectors.m_pBlock);
        m_vpSectors.m_pBlock = nullptr;
    }
    m_vpSectors.m_ui32NbUsedElt = 0;
    m_vpSectors.m_pBlock = nullptr;
}

// 0x0002fdb0 CKLevel_Load. The level file (type 0) gives the sectors; every type then sets the
// renderer's +0xd4 to 99.
int32_t CKLevel::Load(IKFile* file, int32_t type) {
    if (type == 0) {
        IKFile_ReadRef(file, &m_unk34);
        ReadU32LE(file, &m_ui32NbSectors);
        GameVector_Allocate(&m_vpSectors, m_ui32NbSectors);
        GameVector_Resize(&m_vpSectors, m_ui32NbSectors);
        IKFile_ReadObjectRefArray(file, m_vpSectors.m_pBlock, m_ui32NbSectors);
        ReadS32LE(file, &m_defaultSector);
        ReadRaw(file, &m_i8NumFirstStream, 1);
        ReadU32LE(file, &m_ui32ProjectVersionNumber);
        Uuid_Read(m_KGuidIdentifier, file);
        Engine_SetDynamicSceneRoot(static_cast<CKSector*>(m_vpSectors.m_pBlock[0])->m_pSectorRoot);
    }
    g_pEngine->m_graphic->m_renderer->m_unkD4 = 99;
    return 1;
}

// 0x0002fb90 CKLevel_PostLoad: the first sector (the level's base sector) made active, for every load
// type. This is the bit the Flash interfaces of LVL000 test (live: CKSector +0x06 = 0x0001 at the menu).
int32_t CKLevel::PostLoad(int32_t /*type*/) {
    static_cast<CKSector*>(m_vpSectors.m_pBlock[0])->SetActive(1);
    return 1;
}

namespace {
SectorRequest& RequestOf(CKLevel* level, int32_t sector) {
    return static_cast<CKSector*>(level->m_vpSectors.m_pBlock[sector])->m_request;
}

// The main scene root's vt+0x78 (0x000cdb30 CSGBranch_RemoveChild_maybe): the sector's root taken off the scene graph
// (its frame out of the root's, out of the child list, no parent).
void RemoveSectorRoot(CSGSectorRoot* sectorRoot) {
    static_cast<CSGBranch*>(g_pEngine->m_mainSceneRoot)->RemoveChild(sectorRoot);
}
}  // namespace

// 0x0002f680 CKLevel_PostSectorUnload: every sector told (vt+0x5c).
void CKLevel::PostSectorUnload(int32_t sector) {
    for (uint32_t i = 0; i < m_ui32NbSectors; ++i) static_cast<CKSector*>(m_vpSectors.m_pBlock[i])->PostSectorUnload(sector);
}

// 0x0002f718 CKLevel_SectorUnload: the trigger domains of the sector's set disabled, then every sector told
// (vt+0x58).
// BUG(original): the set found for the sector is not tested; a sector without one would be written at
// address 0x10.
void CKLevel::SectorUnload(int32_t sector) {
    static_cast<CKTriggerSynchro*>(m_unk34)->FindSetForSector(sector)->SetEnabled(0);
    for (uint32_t i = 0; i < m_ui32NbSectors; ++i) static_cast<CKSector*>(m_vpSectors.m_pBlock[i])->SectorUnload(sector);
}

// 0x0002f128 CKLevel_ResetSectorState_maybe
void CKLevel::ResetSectorState() {
    m_i32NumLoadingSector = 0;
    m_requestedSector = -2;
    m_currentSector = 0;
}

// 0x0002f140 CKLevel_ClearLoadingSector
void CKLevel::ClearLoadingSector() { m_i32NumLoadingSector = -2; }

// 0x0002f968 CKLevel_Start: every sector's state bits 0..2 cleared (bit 1 set, then the three cleared, in the
// original's store order, last sector first), then both "need warning" flags set (the end of the loading and the
// base sector 0: the next CKLevel_Update announces them, which wakes the lives of sector 0) and the ground state
// flags 0, then 1, then 2. Unported before 2026-10-26: m_bCommunNeedWarning stayed uninitialised (0xcd in Debug,
// so the heroes woke there; usually 0 in Release, so they never did).
// STUB(C2.8): the sectors' state bits 0..2 are not cleared here. The port activates the sectors earlier than the
// original (CKLevel_PostLoad's active bit, C1.5), so clearing them would leave the front end's sectors inactive (no
// menu sparkles); the loop comes with the level streaming / level exit path (C2.8). In the original:
//   for each sector, last first: props = ((props >> 2) << 2) | 2; props = (props >> 3) << 3;
void CKLevel::Start() {
    m_bEndLoadingNeedWarning = 1;
    m_bCommunNeedWarning = 1;
    m_ba8GroundStateFlags = 0;
    m_ba8GroundStateFlags = static_cast<uint8_t>((m_ba8GroundStateFlags & 0xfe) | 1);
    m_ba8GroundStateFlags = static_cast<uint8_t>(((m_ba8GroundStateFlags >> 2) << 2) | 2);
}

// 0x0002f150 CKLevel_IterateActiveSectors
CKSector* CKLevel::IterateActiveSectors(const CKSector* previous) {
    CKSector** sectors = reinterpret_cast<CKSector**>(m_vpSectors.m_pBlock);
    if (previous == nullptr) {
        if (m_currentSector != 0 && (sectors[m_currentSector]->m_ba16Properties & 1) != 0) return sectors[m_currentSector];
        return sectors[0];
    }
    return previous->m_ui16NumSector != 0 ? sectors[0] : nullptr;
}

// 0x0002f450 CKLevel_GetDefaultSector_maybe
int32_t CKLevel::GetDefaultSector() { return m_defaultSector; }

// 0x00030448 CKLevel_UnloadCurrentSector: the current sector (if any) deactivated and its objects unloaded
// synchronously (SectorRequest_RunSync, operation 1). The argument is not used.
uint8_t CKLevel::UnloadCurrentSector(int32_t /*unused*/) {
    const int32_t sector = m_currentSector;
    if (sector == -2 || sector == 0) return 1;
    if ((static_cast<CKSector*>(m_vpSectors.m_pBlock[sector])->m_ba16Properties & 1) != 0) {
        // An active sector first tells the game loop (vt+0x8c SectorUnload and vt+0x90 PostSectorUnload with
        // the sector) and takes its root off the main scene root (vt+0x78).
        g_pEngine->m_gameLoop->SectorUnload(sector);
        g_pEngine->m_gameLoop->PostSectorUnload(sector);
        RemoveSectorRoot(static_cast<CKSector*>(m_vpSectors.m_pBlock[m_currentSector])->m_pSectorRoot);
    }
    m_i32NumUnloadingSector = m_currentSector;
    static_cast<CKSector*>(m_vpSectors.m_pBlock[m_currentSector])->SetActive(0);  // 0x32c08
    RequestOf(this, m_currentSector).RunSync(SectorRequest::kUnload);
    return 1;
}

// 0x000305d8 CKLevel_UpdateSectorStreaming: one step towards the requested sector (the game loop calls it
// every frame of modes 1 and 6).
void CKLevel::UpdateSectorStreaming() {
    int32_t pending = m_i32NumUnloadingSector;
    if (pending == -2) {
        pending = m_i32NumLoadingSector;
        if (pending == -2) {
            const int32_t requested = m_requestedSector;
            if (requested == -2) return;
            if (m_currentSector == 0) {
                RequestOf(this, requested).Post(SectorRequest::kLoad);
            } else if (requested != m_currentSector) {
                UnloadCurrentSector(1);
            } else {
                m_requestedSector = -2;
            }
            return;
        }
    }
    RequestOf(this, pending).CheckDone();
}

// 0x00030908 CKLevel_SwitchToSector: requests the sector; with wait set, finishes what is pending, unloads
// the current sector and loads the new one before returning.
uint8_t CKLevel::SwitchToSector(int32_t sector, int32_t wait) {
    if (m_requestedSector != sector) m_requestedSector = sector;
    if (wait == 0) return 1;
    if (m_i32NumUnloadingSector != -2) RequestOf(this, m_i32NumUnloadingSector).Wait();
    if (m_i32NumLoadingSector != -2) RequestOf(this, m_i32NumLoadingSector).Wait();
    int32_t current = m_currentSector;
    if (current != 0) {
        if (m_requestedSector != current) {
            UnloadCurrentSector(1);
            current = m_currentSector;
        }
        if (current != 0) {
            m_requestedSector = -2;
            return 1;
        }
    }
    RequestOf(this, m_requestedSector).Post(SectorRequest::kLoad);
    RequestOf(this, m_requestedSector).Wait();
    m_requestedSector = -2;
    return 1;
}

// 0x000306a0 CKLevel_UpdateUnloadSectors_maybe
uint32_t CKLevel::UpdateUnloadSectors() {
    UpdateSectorStreaming();
    if (m_i32NumLoadingSector != -2 || m_i32NumUnloadingSector != -2) return 0;
    int32_t current = m_currentSector;
    if (current != 0 && current != -2) {
        if ((static_cast<CKSector*>(m_vpSectors.m_pBlock[current])->m_ba16Properties & 1) != 0) {
            g_pEngine->m_gameLoop->SectorUnload(current);
            g_pEngine->m_gameLoop->PostSectorUnload(current);
            RemoveSectorRoot(static_cast<CKSector*>(m_vpSectors.m_pBlock[m_currentSector])->m_pSectorRoot);
            current = m_currentSector;
        }
        static_cast<CKSector*>(m_vpSectors.m_pBlock[current])->SetActive(0);
        m_currentSector = 0;
    }
    if (m_bCommunNeedWarning == 0) {
        g_pEngine->m_gameLoop->SectorUnload(0);
        g_pEngine->m_gameLoop->PostSectorUnload(0);
        static_cast<CKSector*>(m_vpSectors.m_pBlock[0])->SetActive(0);
    }
    return 1;
}

// 0x0002f7d8 CKLevel_PreSectorLoaded: every sector told (vt+0x50).
void CKLevel::PreSectorLoaded(int32_t sector) {
    for (uint32_t i = 0; i < m_ui32NbSectors; ++i) static_cast<CKSector*>(m_vpSectors.m_pBlock[i])->PreSectorLoaded(sector);
}

// 0x000300a8 CKLevel_SectorLoaded: every sector told (vt+0x54, empty), then the trigger domains of the sector's
// set enabled.
// BUG(original): the set found for the sector is not tested (as in SectorUnload).
void CKLevel::SectorLoaded(int32_t sector) {
    for (uint32_t i = 0; i < m_ui32NbSectors; ++i) static_cast<CKSector*>(m_vpSectors.m_pBlock[i])->SectorLoaded(sector);
    static_cast<CKTriggerSynchro*>(m_unk34)->FindSetForSector(sector)->SetEnabled(1);
}

// 0x00030170 CKLevel_Restart (vt+0x54): every sector (last to first) that is not kept (+0x06 bit 1) gets bit 2; then
// each sector's trigger domain set is enabled when it is the base sector 0 or the current one, disabled otherwise
// (only when its flag byte differs).
// BUG(original): as in SectorLoaded, the set found for a sector is not tested.
void CKLevel::Restart() {
    for (uint32_t i = m_ui32NbSectors; i != 0; --i) {
        CKSector* sector = static_cast<CKSector*>(m_vpSectors.m_pBlock[i - 1]);
        if ((sector->m_ba16Properties & 2u) != 0) continue;
        sector->m_ba16Properties = static_cast<uint16_t>(sector->m_ba16Properties | 4u);  // rlwinm 29,1,31 / 3,0,31 / ori 4
    }
    CKTriggerSynchro* synchro = static_cast<CKTriggerSynchro*>(m_unk34);
    for (uint32_t i = 0; i < m_ui32NbSectors; ++i) {
        const uint8_t enabled = (i == 0 || static_cast<int32_t>(i) == m_currentSector) ? 1 : 0;
        if (enabled != synchro->FindSetForSector(static_cast<int32_t>(i))->m_unk10) {
            synchro->FindSetForSector(static_cast<int32_t>(i))->SetEnabled(enabled);
        }
    }
}

// 0x00030c88 CKLevel_Update. The branches follow the assembly (the decompiler's gotos), see the notes below.
void CKLevel::Update(IKTime* frameClock) {
    UpdateSectorStreaming();
    CKSector* sector = nullptr;  // r26: the current sector when a sector became active this frame
    if (m_bEndLoadingNeedWarning != 0) {
        const int32_t current = m_currentSector;
        m_bEndLoadingNeedWarning = 0;
        bool commonWarning;
        if (current != 0 && current != -2) {
            // The sector that finished loading becomes active: its root joins the main scene root unless it already
            // has a parent, and the ground flags (+0x2f) become (flags & 0xfc) | 3.
            sector = static_cast<CKSector*>(m_vpSectors.m_pBlock[current]);
            sector->SetActive(1);
            CSGSectorRoot* root = static_cast<CKSector*>(m_vpSectors.m_pBlock[m_currentSector])->m_pSectorRoot;
            if (root->m_pParent == nullptr) static_cast<CSGBranch*>(g_pEngine->m_mainSceneRoot)->AddChild(root);  // vt+0x70
            m_ba8GroundStateFlags = static_cast<uint8_t>((m_ba8GroundStateFlags & 0xfc) | 3);
            g_pEngine->m_graphic->UpdateSceneWorldMatrices();
            commonWarning = m_bCommunNeedWarning != 0;
        } else {
            g_pEngine->m_graphic->UpdateSceneWorldMatrices();
            commonWarning = m_bCommunNeedWarning != 0;
        }
        if (commonWarning) {
            // The base sector (0) was loaded too: it becomes active and is announced.
            static_cast<CKSector*>(m_vpSectors.m_pBlock[0])->SetActive(1);
            g_pEngine->m_gameLoop->PreSectorLoaded(0);
            g_pEngine->m_gameLoop->SectorLoaded(0);
            m_bCommunNeedWarning = 0;
            CKSector* base = static_cast<CKSector*>(m_vpSectors.m_pBlock[0]);
            // The sector's state bits: bit 1 clear -> bit 2 cleared, else bit 1 cleared.
            base->m_ba16Properties = (base->m_ba16Properties & 2) == 0 ? static_cast<uint16_t>(base->m_ba16Properties & ~4u)
                                                                       : static_cast<uint16_t>(base->m_ba16Properties & ~2u);
        }
        if (m_currentSector != 0 && m_currentSector != -2) {
            g_pEngine->m_gameLoop->PreSectorLoaded(m_currentSector);
            g_pEngine->m_gameLoop->SectorLoaded(m_currentSector);
            sector->m_ba16Properties = (sector->m_ba16Properties & 2) == 0 ? static_cast<uint16_t>(sector->m_ba16Properties & ~4u)
                                                                           : static_cast<uint16_t>(sector->m_ba16Properties & ~2u);
        }
        g_pEngine->m_graphic->UpdateSceneWorldMatrices();
        if (m_currentSector != 0 && m_currentSector != -2) sector->QueueLoadedEvent();
    }
    // The hero's position decides the sector: first against the current sector's boxes, then (when none holds
    // it) against the loading sector's. The target is only requested (no wait).
    const float* position = g_pEngine->m_gameManager->GetFocusedHeroNodePosition();  // vt+0x124
    int32_t found = -2;
    if (m_currentSector != -2) {
        found = static_cast<CKSector*>(m_vpSectors.m_pBlock[m_currentSector])->FindSectorAtPoint(position);
    }
    if (found == -2 && m_i32NumLoadingSector != -2) {
        found = static_cast<CKSector*>(m_vpSectors.m_pBlock[m_i32NumLoadingSector])->FindSectorAtPoint(position);
    }
    if (found != -2 && m_currentSector != found) SwitchToSector(found, 0);
    // The klusters of the active sector (the base sector when the current one is not active) and, when that
    // is not the base sector, of the base sector too.
    CKSector* updating = static_cast<CKSector*>(m_vpSectors.m_pBlock[0]);
    if (m_currentSector != 0) {
        CKSector* current = static_cast<CKSector*>(m_vpSectors.m_pBlock[m_currentSector]);
        if ((current->m_ba16Properties & 1) != 0) updating = current;
    }
    while (updating != nullptr) {
        updating->UpdateMeshKlusters(frameClock);
        if (updating->m_ui16NumSector == 0) break;
        updating = static_cast<CKSector*>(m_vpSectors.m_pBlock[0]);
    }
    m_ba8GroundStateFlags &= 0xfc;
}

// 0x000308a8 CKLevel_StreamUntilSector_maybe
uint8_t CKLevel::StreamUntilSector(void* level, int32_t /*id*/, void* sector) {
    CKLevel* self = static_cast<CKLevel*>(level);
    self->UpdateSectorStreaming();  // 0x000305d8
    return self->m_currentSector == static_cast<int32_t>(reinterpret_cast<intptr_t>(sector)) ? 1 : 0;
}

// 0x00030a48 CKLevel_EnterSector_maybe
uint8_t CKLevel::EnterSector(int32_t sector) {
    if (m_currentSector == sector) return 1;
    if (m_i32NumLoadingSector != sector) SwitchToSector(sector, 0);  // 0x00030908
    const uint32_t state = static_cast<uint32_t>(KHostFS_GetInstance()->GetDeviceState()) - 3u;  // 0x00051990, 0x000519c8
    if (state <= 4) {
        static const int32_t kStateJobs[5] = {0xcc & 0xcf, 0xc8, 0xc9, 0xca, 0xca};  // jump table 0x30b0c
        g_pEngine->m_jobQueue->PostAndWait(kStateJobs[state], 2, nullptr, &CKLevel::HostFsStateJobCallback, nullptr);
        return 1;
    }
    g_pEngine->m_jobQueue->PostAndWait(0xcb, 2, this, &CKLevel::StreamUntilSector,
                                       reinterpret_cast<void*>(static_cast<intptr_t>(sector)));
    return 1;
}

// 0x0002fc28 CKLevel_CreateArray
IKBaseClass* CKLevel::CreateArray(uint32_t count, uint16_t* elementSize) {
    if (elementSize != nullptr) *elementSize = static_cast<uint16_t>(sizeof(CKLevel));
    return new CKLevel[count];
}

// 0x0002f5d8 CKLevel_DeleteArray
void CKLevel::DeleteArray(IKBaseClass* first) { delete[] static_cast<CKLevel*>(first); }

// 0x0002f500 CKLevel_PostSectorLoad_maybe
uint8_t CKLevel::PostSectorLoad(int32_t sector, int32_t wait) {
    RequestOf(this, sector).Post(SectorRequest::kLoad);
    if (wait != 0) RequestOf(this, sector).Wait();
    return 1;
}

// 0x000302b8 CKLevel_PostSectorLoadIfIdle_maybe
uint8_t CKLevel::PostSectorLoadIfIdle(int32_t sector, int32_t wait) {
    if (m_i32NumUnloadingSector != -2) return 1;
    RequestOf(this, sector).Post(SectorRequest::kLoad);
    if (wait != 0) RequestOf(this, sector).Wait();
    return 1;
}

// 0x00030378 CKLevel_RequestSector_maybe
uint8_t CKLevel::RequestSector(int32_t sector) {
    if (sector == -2) sector = m_defaultSector;
    if (sector == 0 || sector == -2) return 1;
    m_requestedSector = sector;
    if (m_i32NumUnloadingSector != -2) return 1;
    RequestOf(this, sector).Post(SectorRequest::kLoad);
    RequestOf(this, sector).Wait();
    return 1;
}
