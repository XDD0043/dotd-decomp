// CKGameSpawnPoint.cpp - reconstructed original translation unit 0x3cb70-0x3da88 (GAME_TOC1, main_toc1), 20 functions, 20 live.
// Primary class: CKGameSpawnPoint  key 0x318c  category Logic  size 0x38  vtable 0xb14908
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x3cb70  CKGameSpawnPoint_IsCurrentLevel
//   [x] 0x3cbd8  CKGameSpawnPoint_GetBeaconPosition_maybe
//   [x] 0x3ccf8  CKGameSpawnPoint_vf78
//   [ ] 0x3cd00  RegisterCKGameSpawnPointClass
//   [ ] 0x3cd78  _GLOBAL__I_3cd78
//   [x] 0x3cd88  CKGameSpawnPoint_Activate_maybe
//   [x] 0x3d1f8  CKGameSpawnPoint_ClearGameData_maybe
//   [x] 0x3d220  CKGameSpawnPoint_ClearLevelData_maybe
//   [x] 0x3d258  CKGameSpawnPoint_InitLevelData_maybe
//   [x] 0x3d2b8  CKGameSpawnPoint_InitGameData
//   [x] 0x3d300  CKGameSpawnPoint_PostLoad  (empty / no effect: inherited)
//   [ ] 0x3d368  CKGameSpawnPoint_Save
//   [x] 0x3d390  CKGameSpawnPoint_RecursiveRegistration  (inherited: IKGameObject_vf24, nothing)
//   [x] 0x3d3b8  CKGameSpawnPoint_Destroy  (inherited: IKGameObject_Destroy)
//   [x] 0x3d3e0  CKGameSpawnPoint_DeleteArray
//   [x] 0x3d490  CKGameSpawnPoint_Create
//   [x] 0x3d508  CKGameSpawnPoint_GetInfo
//   [x] 0x3d560  CKGameSpawnPoint_MessageProc
//   [x] 0x3d700  CKGameSpawnPoint_CreateArray
//   [x] 0x3d7f0  CKGameSpawnPoint_Load
//
//   [ ] 0x994f58  CKGameSpawnPoint_IsKindOfClass  [inline]
//   [x] 0x994f80  CKGameSpawnPoint_GetClassType  [inline]
//   [x] 0x994f88  CKGameSpawnPoint_GetClassID  [inline]
//   [x] 0x994f90  CKGameSpawnPoint_vf74  [inline]
//   [x] 0x994fe8  CKGameSpawnPoint_IsCurrentSpawnPoint_maybe  [inline]
//   [ ] 0x995018  CKGameSpawnPoint_DeletingDestructor  [inline]
//   [ ] 0x995068  CKGameSpawnPoint_Destructor  [inline]
#include "k2000/logic/CKGameSpawnPoint.h"

#include <cstring>

#include "k2000/core/IKInfo.h"
#include "k2000/core/Stub.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/logic/ai/CKBeaconKluster.h"
#include "k2000/misc/IKGameStructure.h"
#include "k2000/services/CKSrvBeacon.h"
#include "k2000/graphical/CHDRData.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKGameLevel.h"
#include "k2000/logic/CKLevel.h"
#include "k2000/logic/CKSector.h"
#include "k2000/logic/fx/CKHDRFxData.h"
#include "k2000/fx/IKFx.h"
#include "k2000/misc/Engine.h"
#include "k2000/services/CKSrvFx.h"

// The constructor inlined in CKGameSpawnPoint_Create 0x3d490: the four beacon words, then +0x34.
// m_tsStart is left as it is.
CKGameSpawnPoint::CKGameSpawnPoint() {
    m_baCameraPosition[0] = 0xffff;
    m_baCameraPosition[3] = 0xffff;
    m_baCameraPosition[1] = 0xffff;
    m_baCameraPosition[2] = 0xffff;
    m_pUnk34 = nullptr;
}

// 0x0003d258 CKGameSpawnPoint_InitLevelData_maybe
void CKGameSpawnPoint::InitializeLevelData() {
    IKGameObject::InitializeLevelData();
    m_baCameraPosition[0] = 0xffff;
    m_baCameraPosition[3] = 0xffff;
    m_baCameraPosition[1] = 0xffff;
    m_baCameraPosition[2] = 0xffff;
    m_pHDRFxData = nullptr;
}

// 0x0003d2b8 CKGameSpawnPoint_InitGameData
void CKGameSpawnPoint::InitializeGameData() {
    IKGameObject::InitializeGameData();
    m_pUnk34 = nullptr;
    m_iSectorIndex = -2;
    m_pGameStage = nullptr;
}

// 0x0003d220 CKGameSpawnPoint_ClearLevelData_maybe
void CKGameSpawnPoint::DestroyLevelData() {
    IKGameObject::DestroyLevelData();  // 0x42d90
    m_pHDRFxData = nullptr;
}

// 0x0003d1f8 CKGameSpawnPoint_ClearGameData_maybe
void CKGameSpawnPoint::DestroyGameData() { IKGameObject::DestroyGameData(); }

// 0x0003cb70 CKGameSpawnPoint_IsCurrentLevel
uint8_t CKGameSpawnPoint::GetMatchesThisLevel() {
    if (m_pGameStage == nullptr) return 0;
    return m_pGameStage->GetMatchesThisLevel() != 0 ? 1 : 0;  // vt+0x54
}

// 0x0003d560 CKGameSpawnPoint_MessageProc
int32_t CKGameSpawnPoint::MessageProc(uint16_t message, void*) {
    if (message == 0x203) {
        m_pGameStage->m_pGameStructure->SetCurrentSpawnPoint(this);  // vt+0x6c
        CDefaultGameManager* manager = m_pGameStage->GetGameManager();  // 0x391e0
        const int32_t level = m_pGameStage->m_i32StageIndex;
        manager->m_requestedSector = m_iSectorIndex;
        manager->m_requestedLevel = level;
        return 0;
    }
    if (message == 0x204) {
        m_pGameStage->m_pGameStructure->SetCurrentSpawnPoint(this);  // vt+0x6c
        g_pEngine->m_gameManager->RequestSave(1, 0);                 // vt+0x104
        return 0;
    }
    if (message != 0x202) return 1;
    m_pGameStage->m_pGameStructure->SetCurrentSpawnPoint(this);  // vt+0x6c
    return 0;
}

// 0x0003d508 CKGameSpawnPoint_GetInfo
int32_t CKGameSpawnPoint::GetInfo(IKInfo* info, int32_t request) {
    if (request != kGetInfoValueAccessor || info->m_ui32Id != 3) return 1;
    // 0x00994fe8 CKGameSpawnPoint_IsCurrentSpawnPoint_maybe: its stage's structure's current spawn point is it.
    return AnswerInfo(info, [](IKSerializable* o, uint32_t) -> uint32_t {
        CKGameSpawnPoint* point = static_cast<CKGameSpawnPoint*>(o);
        return point->m_pGameStage->m_pGameStructure->m_pCurrentSpawnPoint == point ? 1u : 0u;
    }, 0);
}

// 0x0003cbd8 CKGameSpawnPoint_GetBeaconPosition_maybe: the beacon service's sector (accessor half 0), kluster (1),
// the kluster's set of the id (2) and the set's beacon (3).
void CKGameSpawnPoint::GetBeaconPosition(float* position) {
    // BUG(original): a sector without klusters reads the half-words at addresses 0, 2 and 4; an id without a set
    // (0xff) reads the set at address 0.
    const uint8_t* beacon = nullptr;
    CKSrvBeacon* service = static_cast<CKSrvBeacon*>(g_pEngine->m_srvBeacon);
    CKSrvBeacon::CKBeaconSector& sector = service->m_aBeaconSectors[m_baCameraPosition[0]];
    if (sector.m_apBeaconKlusters != nullptr) {
        CKBeaconKluster* kluster = reinterpret_cast<CKBeaconKluster**>(sector.m_apBeaconKlusters)[m_baCameraPosition[1]];
        const uint8_t setIndex = static_cast<uint8_t>(kluster->m_ai8IdToBeaconSet[m_baCameraPosition[2]]);
        CKSrvBeacon::CKBeaconSet* set = nullptr;
        if (setIndex != 0xff) set = kluster->m_aBeaconSets + static_cast<int8_t>(setIndex);
        beacon = static_cast<const uint8_t*>(set->m_aBeacons) + static_cast<uint32_t>(m_baCameraPosition[3]) * set->m_ui8VolatileSizeBytes;
    }
    int16_t halves[3];
    std::memcpy(halves, beacon, 6);
    position[0] = static_cast<float>(halves[0]) * 0.1f;  // TOC1 -0x7688
    position[1] = static_cast<float>(halves[1]) * 0.1f;
    position[2] = static_cast<float>(halves[2]) * 0.1f;
}

// 0x00994f90 CKGameSpawnPoint_vf74
uint8_t CKGameSpawnPoint::HasCameraBeacon() {
    const bool none = m_baCameraPosition[0] == 0xffff && m_baCameraPosition[1] == 0xffff && m_baCameraPosition[2] == 0xffff &&
                      m_baCameraPosition[3] == 0xffff;
    return none ? 0 : 1;
}

// 0x0003d7f0 CKGameSpawnPoint_Load
int32_t CKGameSpawnPoint::Load(IKFile* file, int32_t type) {
    IKGameObject::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) {
        if (type == kGameStructureBlock) {
            IKFile_ReadRef(file, &m_pGameStage);
            ReadS32LE(file, &m_iSectorIndex);
            IKFile_ReadRef(file, &m_pUnk34);
        }
        return 1;
    }
    // One 8-byte read, then each half-word swapped (lhbrx).
    uint8_t beacon[8];
    ReadRaw(file, beacon, 8);
    for (int i = 0; i < 4; ++i) {
        m_baCameraPosition[i] = static_cast<uint16_t>(beacon[i * 2] | (beacon[i * 2 + 1] << 8));
    }
    IKFile_ReadRef(file, &m_pHDRFxData);
    m_tsStart.Load(file, K_LEVEL_PLATEFORMS);
    return 1;
}

// 0x0003cd88 CKGameSpawnPoint_Activate_maybe (vt+0x7c)
uint16_t CKGameSpawnPoint::Activate() {
    CKHDRFxData* fx = static_cast<CKHDRFxData*>(m_pHDRFxData);
    CKLevel* level = g_pEngine->m_level;
    if (fx != nullptr && static_cast<CHDRData*>(fx->m_pHDRData)->m_fHDRIntensity != 0.0f) {
        fx->m_unk14 = static_cast<int32_t>(static_cast<uint32_t>(fx->m_unk14) & 0xfffffffdu);
        fx->m_unk10 = fx->m_unk0c;
        // The FX service's effect for the data (inlined): a unique effect (the data's vt+0x50) is the unique node of
        // the data's node class (vt+0x54), given the data and the spawn point (vt+0x8c) and started (vt+0x64) when it
        // is stopped and not reserved; any other the first stopped, unreserved node of the class and type (vt+0x58),
        // given the data (vt+0x84) and the owner (vt+0x88), then started.
        CKSrvFx* service = static_cast<CKSrvFx*>(g_pEngine->m_srvFx);
        IKFxData* data = fx;
        const uint32_t nodeClass = data->GetAssociatedFxClassIdentifier();
        if (static_cast<uint8_t>(data->Vf50()) == 0) {
            const uint32_t type = data->GetAssociatedFxClassType();
            // The first mapping of the class with an entry of the type (a class mapping without it lets the search go on).
            const CKSrvFx::CUnderMappingindex* under = nullptr;
            for (uint32_t i = 0; i < service->m_ui32EltNb && under == nullptr; ++i) {
                const CKSrvFx::CMappingindex& mapping = service->m_apMappingIndexTable[i];
                if (mapping.m_ui32ClassId != nodeClass || mapping.m_ui32NbTypeFx == 0) continue;
                for (uint32_t j = 0; j < mapping.m_ui32NbTypeFx; ++j) {
                    if (static_cast<uint32_t>(mapping.m_aUnderMapping[j].m_i32FxTypeId) == type) {
                        under = &mapping.m_aUnderMapping[j];
                        break;
                    }
                }
            }
            if (under != nullptr) {
                for (uint32_t k = 0; k < under->m_ui32MaxSize; ++k) {
                    IKFx* node = static_cast<IKFx*>(under->m_apFxArrayForTypeId[k]);
                    if ((node->m_baFxData & 1) != 0 && (node->m_baFxData & 2) == 0) {
                        node->SetFxData(data);  // vt+0x84
                        node->SetOwner(this);   // vt+0x88
                        node->Vf64();           // vt+0x64
                        break;
                    }
                }
            }
        } else {
            for (uint32_t i = 0; i < service->m_ui32UniqueFxArraySize; ++i) {
                IKFx* node = static_cast<IKFx*>(service->m_apUniqueFxArray[i]);
                if (static_cast<uint32_t>(node->GetClassID()) * 0x40 + static_cast<uint32_t>(node->GetClassType()) != nodeClass) continue;
                node->SetDataAndOwner(data, this);
                const uint8_t state = node->m_baFxData;
                if ((state & 1) != 0 && ((state >> 1) & 1) == 0) node->Vf64();
                break;
            }
        }
    }
    QueueTriggerSignals(&m_tsStart);
    const int32_t sector = m_iSectorIndex;
    if (sector >= 0 && sector < static_cast<int32_t>(level->m_ui32NbSectors)) {
        return static_cast<uint16_t>(static_cast<CKSector*>(level->m_vpSectors.m_pBlock[sector])->m_ba16Properties & 1);
    }
    return 0;
}
