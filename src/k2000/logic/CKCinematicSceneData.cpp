// CKCinematicSceneData.cpp - reconstructed original translation unit 0x16dd48-0x16e7b8 (GAME_TOC1, main_toc1), 17 functions, 15 live.
// Primary class: CKCinematicSceneData  key 0xa8c  category Logic  size 0x20  vtable 0xb1ac70
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x16dd48  CKCinematicSceneData_Delete
//   [ ] 0x16dd98  CKCinematicSceneData_Construct  [dead]
//   [ ] 0x16ddc8  CKCinematicSceneData_Construct_2  [dead]
//   [x] 0x16ddf8  CKCinematicSceneData_Destroy  (empty)
//   [x] 0x16de00  CKCinematicSceneData_RecursiveRegistration
//   [ ] 0x16dec0  CKCinematicSceneData_Save
//   [x] 0x16dec8  CKCinematicSceneData_PostLoad
//   [x] 0x16dee0  CKCinematicSceneData_GetBeaconPosition_maybe
//   [ ] 0x16e000  RegisterCKCinematicSceneDataClass
//   [ ] 0x16e078  _GLOBAL__I_16e078
//   [x] 0x16e088  CKCinematicSceneData_FreeSavedMatrix_maybe
//   [x] 0x16e0c8  CKCinematicSceneData_AllocSavedMatrix_maybe
//   [x] 0x16e100  CKCinematicSceneData_DeleteArray
//   [x] 0x16e1a8  CKCinematicSceneData_CreateArray
//   [x] 0x16e260  CKCinematicSceneData_Create
//   [x] 0x16e2b8  CKCinematicSceneData_Load
//   [x] 0x16e4a8  CKCinematicSceneData_GetBeaconDirection_maybe
//
//   [ ] 0x9a8d10  CKCinematicSceneData_GetClassType  [inline]
//   [ ] 0x9a8d18  CKCinematicSceneData_GetClassID  [inline]
//   [ ] 0x9a8d20  CKCinematicSceneData_IsKindOfClass  [inline]
//   [ ] 0x9a8d40  CKCinematicSceneData_DeletingDestructor  [inline]
//   [ ] 0x9a8d80  CKCinematicSceneData_Destructor  [inline]
//   [ ] 0x9a8d98  KStub_Nop_9a8d98  [inline]
//   [ ] 0x9a8da0  KStub_Nop_9a8da0  [inline]
//   [ ] 0x9a8da8  KStub_Nop_9a8da8  [inline]
//   [ ] 0x9a8db0  IKCinematicElement_Activate  [inline]
//   [ ] 0x9a8df0  KStub_Nop_9a8df0  [inline]
//   [ ] 0x9a8df8  KStub_Nop_9a8df8  [inline]
//   [ ] 0x9a8e00  KStub_Nop_9a8e00  [inline]
#include "k2000/logic/CKCinematicSceneData.h"

#include <cstring>

#include "crt/xsinf.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/ai/CKBeaconKluster.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/misc/Engine.h"
#include "k2000/services/CKSrvBeacon.h"
#include "k2000/misc/Mat4.h"

// 0x0016e260 CKCinematicSceneData_Create (the same stores as the dead CKCinematicSceneData_Construct
// 0x16dd98)
CKCinematicSceneData::CKCinematicSceneData() {
    m_aUnk10[0] = 0xffff;
    m_aUnk10[3] = 0xffff;
    m_aUnk10[1] = 0xffff;
    m_aUnk10[2] = 0xffff;
    m_pAnimDico = nullptr;
}

// 0x0016e2b8 CKCinematicSceneData_Load
int32_t CKCinematicSceneData::Load(IKFile* file, int32_t type) {
    if (type == K_LEVEL_PLATEFORMS) {
        IKFile_ReadRef(file, &m_pHook);
        IKFile_ReadRef(file, &m_pAnimDico);
        ReadU8(file, &m_DataFlags);
        // One 8-byte read, then each half-word swapped (lhbrx).
        uint8_t raw[8];
        ReadRaw(file, raw, 8);
        for (int i = 0; i < 4; ++i) m_aUnk10[i] = static_cast<uint16_t>(raw[2 * i] | (raw[2 * i + 1] << 8));
    }
    m_pShadowData = nullptr;
    return 1;
}

// 0x0016e088 CKCinematicSceneData_FreeSavedMatrix_maybe
void CKCinematicSceneData::FreeSavedMatrix() {
    RwMatrixDestroy_Thunk(static_cast<CMatrix34*>(m_pOriginalMatrix));
    m_pOriginalMatrix = nullptr;
}

// 0x0016e0c8 CKCinematicSceneData_AllocSavedMatrix_maybe
void CKCinematicSceneData::AllocSavedMatrix() { m_pOriginalMatrix = RwMatrixCreate_Thunk(); }

namespace {
// The interrupt beacon's data (the beacon service's sector `accessor[0]`, kluster [1], the kluster's set of id [2], the
// set's beacon [3]), as CKGameSpawnPoint_GetBeaconPosition_maybe reads it. BUG(original): a sector without klusters
// gives null (the callers then read low addresses); an id without a set (0xff) takes the set at address 0.
const uint8_t* InterruptBeacon(const uint16_t* accessor) {
    CKSrvBeacon* service = static_cast<CKSrvBeacon*>(g_pEngine->m_srvBeacon);
    CKSrvBeacon::CKBeaconSector& sector = service->m_aBeaconSectors[accessor[0]];
    if (sector.m_apBeaconKlusters == nullptr) return nullptr;
    CKBeaconKluster* kluster = reinterpret_cast<CKBeaconKluster**>(sector.m_apBeaconKlusters)[accessor[1]];
    const uint8_t setIndex = static_cast<uint8_t>(kluster->m_ai8IdToBeaconSet[accessor[2]]);
    CKSrvBeacon::CKBeaconSet* set = nullptr;
    if (setIndex != 0xff) set = kluster->m_aBeaconSets + static_cast<int8_t>(setIndex);
    return static_cast<const uint8_t*>(set->m_aBeacons) + static_cast<uint32_t>(accessor[3]) * set->m_ui8VolatileSizeBytes;
}
}  // namespace

// 0x0016dee0 CKCinematicSceneData_GetBeaconPosition_maybe
void CKCinematicSceneData::GetBeaconPosition(float* position) const {
    const uint8_t* beacon = InterruptBeacon(m_aUnk10);
    int16_t halves[3];
    std::memcpy(halves, beacon, 6);
    position[0] = static_cast<float>(halves[0]) * 0.1f;  // TOC1 -0x35e0
    position[1] = static_cast<float>(halves[1]) * 0.1f;
    position[2] = static_cast<float>(halves[2]) * 0.1f;
}

// 0x0016e4a8 CKCinematicSceneData_GetBeaconDirection_maybe (pi TOC1 -0x358c, 1/128 TOC1 -0x3588)
void CKCinematicSceneData::GetBeaconDirection(float* direction) const {
    const uint8_t* beacon = InterruptBeacon(m_aUnk10);
    const int8_t yaw = static_cast<int8_t>(beacon[6]);
    float angle = static_cast<float>(yaw) * 3.14159274f;
    angle = angle * 0.0078125f;
    int32_t bits;
    std::memcpy(&bits, &angle, 4);
    direction[0] = bits < 0 ? -crt::LibSinf(-angle) : crt::InlineSinf(angle);
    direction[2] = bits < 0 ? crt::LibCosf(-angle) : crt::InlineCosf(angle);
    direction[1] = 0.0f;
}

// 0x0016de00 CKCinematicSceneData_RecursiveRegistration (returns 1)
void CKCinematicSceneData::RecursiveRegistration(int32_t type) {
    if (static_cast<uint32_t>(type) - 4u > 3u) g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);
    if (m_pAnimDico != nullptr) m_pAnimDico->RecursiveRegistration(type);  // vt+0x24
}
