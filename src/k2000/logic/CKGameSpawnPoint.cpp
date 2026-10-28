// CKGameSpawnPoint.cpp - reconstructed original translation unit 0x3cb70-0x3da88 (GAME_TOC1, main_toc1), 20 functions, 20 live.
// Primary class: CKGameSpawnPoint  key 0x318c  category Logic  size 0x38  vtable 0xb14908
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x3cb70  CKGameSpawnPoint_IsCurrentLevel
//   [ ] 0x3cbd8  CKGameSpawnPoint_GetBeaconPosition_maybe
//   [ ] 0x3ccf8  CKGameSpawnPoint_vf78
//   [ ] 0x3cd00  RegisterCKGameSpawnPointClass
//   [ ] 0x3cd78  _GLOBAL__I_3cd78
//   [x] 0x3cd88  CKGameSpawnPoint_Activate_maybe
//   [ ] 0x3d1f8  CKGameSpawnPoint_ClearGameData_maybe
//   [x] 0x3d220  CKGameSpawnPoint_ClearLevelData_maybe
//   [x] 0x3d258  CKGameSpawnPoint_InitLevelData_maybe
//   [x] 0x3d2b8  CKGameSpawnPoint_InitGameData
//   [ ] 0x3d300  CKGameSpawnPoint_PostLoad
//   [ ] 0x3d368  CKGameSpawnPoint_Save
//   [ ] 0x3d390  CKGameSpawnPoint_RecursiveRegistration
//   [ ] 0x3d3b8  CKGameSpawnPoint_Destroy
//   [x] 0x3d3e0  CKGameSpawnPoint_DeleteArray
//   [x] 0x3d490  CKGameSpawnPoint_Create
//   [ ] 0x3d508  CKGameSpawnPoint_GetInfo
//   [ ] 0x3d560  CKGameSpawnPoint_MessageProc
//   [x] 0x3d700  CKGameSpawnPoint_CreateArray
//   [x] 0x3d7f0  CKGameSpawnPoint_Load
//
//   [ ] 0x994f58  CKGameSpawnPoint_IsKindOfClass  [inline]
//   [x] 0x994f80  CKGameSpawnPoint_GetClassType  [inline]
//   [x] 0x994f88  CKGameSpawnPoint_GetClassID  [inline]
//   [ ] 0x994f90  CKGameSpawnPoint_vf74  [inline]
//   [ ] 0x994fe8  CKGameSpawnPoint_IsCurrentSpawnPoint_maybe  [inline]
//   [ ] 0x995018  CKGameSpawnPoint_DeletingDestructor  [inline]
//   [ ] 0x995068  CKGameSpawnPoint_Destructor  [inline]
#include "k2000/logic/CKGameSpawnPoint.h"

#include "k2000/core/Stub.h"
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
