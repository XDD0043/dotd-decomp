// CKS08GameSpawnPoint.cpp - reconstructed original translation unit 0x508720-0x5094c8 (GAME_TOC1, main_toc1), 18 functions, 18 live.
// Primary class: CKS08GameSpawnPoint  key 0x790c  category Logic  size 0xa0  vtable 0xb2b470
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x508720  CKS08GameSpawnPoint_Delete
//   [x] 0x508770  CKS08GameSpawnPoint_vf78
//   [x] 0x508778  CKS08GameSpawnPoint_Activate_maybe
//   [x] 0x5087a0  CKS08GameSpawnPoint_ClearGameData_maybe
//   [x] 0x5087c8  CKS08GameSpawnPoint_ClearLevelData
//   [x] 0x5087f0  CKS08GameSpawnPoint_InitLevelData
//   [x] 0x508828  CKS08GameSpawnPoint_InitGameData
//   [x] 0x508850  CKS08GameSpawnPoint_PostLoad  (empty / no effect: inherited)
//   [ ] 0x508878  CKS08GameSpawnPoint_Save
//   [x] 0x5088a0  CKS08GameSpawnPoint_MessageProc
//   [x] 0x508a30  CKS08GameSpawnPoint_DeleteArray
//   [x] 0x508ae0  CKS08GameSpawnPoint_CreateArray
//   [ ] 0x508c20  RegisterCKS08GameSpawnPointClass
//   [ ] 0x508ca8  _GLOBAL__D_508ca8
//   [ ] 0x508cb8  _GLOBAL__I_508cb8
//   [x] 0x508cc8  CKS08GameSpawnPoint_Load
//   [x] 0x508ff8  CKS08GameSpawnPoint_Create
//   [x] 0x5090a8  CKS08GameSpawnPoint_ResolveSlotPosition_maybe
//
//   [ ] 0x9c7100  CKS08GameSpawnPoint_IsKindOfClass  [inline]
//   [x] 0x9c7138  CKS08GameSpawnPoint_GetClassType  [inline]
//   [x] 0x9c7140  CKS08GameSpawnPoint_GetClassID  [inline]
//   [ ] 0x9c7148  CKS08GameSpawnPoint_DeletingDestructor  [inline]
//   [ ] 0x9c7198  CKS08GameSpawnPoint_Destructor  [inline]
#include "Spyro2008/logic/CKS08GameSpawnPoint.h"

#include <cstring>

#include "Spyro2008/logic/CKS08GameManager.h"
#include "crt/ppc_ops.h"
#include "k2000/logic/CKGameLevel.h"
#include "k2000/misc/IKGameStructure.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/ai/CKBeaconKluster.h"
#include "k2000/misc/Engine.h"
#include "k2000/services/CKSrvBeacon.h"

// The constructor inlined in CKS08GameSpawnPoint_Create 0x508ff8: CKGameSpawnPoint's, then the eight
// beacon half-words (+0x40, +0x46, +0x42, +0x44, +0x4e, +0x48, +0x4a, +0x4c).
CKS08GameSpawnPoint::CKS08GameSpawnPoint() {
    m_aBeacons[0][0] = 0xffff;
    m_aBeacons[0][3] = 0xffff;
    m_aBeacons[0][1] = 0xffff;
    m_aBeacons[0][2] = 0xffff;
    m_aBeacons[1][3] = 0xffff;
    m_aBeacons[1][0] = 0xffff;
    m_aBeacons[1][1] = 0xffff;
    m_aBeacons[1][2] = 0xffff;
}

// 0x005087f0 CKS08GameSpawnPoint_InitLevelData
void CKS08GameSpawnPoint::InitializeLevelData() {
    CKGameSpawnPoint::InitializeLevelData();
    m_pUnk38 = nullptr;
}

// 0x00508cc8 CKS08GameSpawnPoint_Load
int32_t CKS08GameSpawnPoint::Load(IKFile* file, int32_t type) {
    CKGameSpawnPoint::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        // One 16-byte read, then each half-word swapped (lhbrx).
        uint8_t beacons[16];
        ReadRaw(file, beacons, 16);
        for (int i = 0; i < 8; ++i) {
            m_aBeacons[i / 4][i % 4] = static_cast<uint16_t>(beacons[i * 2] | (beacons[i * 2 + 1] << 8));
        }
        uint8_t count = 0;
        ReadU8(file, &count);
        for (uint8_t i = static_cast<uint8_t>(count - 1); i != 0xff; --i) {  // from the last slot down
            Slot& slot = m_aSlots[i];  // no bound check, as in the original (two slots)
            ReadU8(file, &slot.m_unk18);
            ReadU8(file, &slot.m_unk19);
            ReadU32LE(file, &slot.m_unk1c);
            ReadU8(file, &slot.m_unk20);
        }
        IKFile_ReadRef(file, &m_pUnk38);
        ReadU8(file, &m_unk98);
        return 1;
    }
    if (type != kGameStructureBlock) return 1;
    ReadU8(file, &m_unk99);
    return 1;
}

namespace {
// The PS3 SDK's sinf/cosf (0x9a1390 / 0x9a11d8, inlined at 0x5090a8 for a non-negative angle), from the
// assembly: the angle in octants, folded into [0, 1], then one of two polynomials (the fmadds/fmsubs
// chains in the original's order). A negative angle is -sin(-x) / cos(-x) there.
float OctantReduce(float x, int32_t* n) {
    const float scaled = x * 1.2732395f;  // 4/pi, TOC1 +0x7524
    *n = ppc::fctiwz(scaled);
    float fraction = scaled - static_cast<float>(*n);
    if ((*n & 1) != 0) fraction = 1.0f - fraction;  // TOC1 +0x7528
    return fraction;
}
// TOC1 +0x752c..+0x7538
float PolyEven(float x) {
    float t = x * -0.00031872783f;
    t = ppc::fmadds(x, t, 0.015849683f);
    t = x * t;
    t = ppc::fmsubs(x, t, 0.30842417f);
    t = x * t;
    return ppc::fmadds(x, t, 0.99999994f);
}
// TOC1 +0x753c..+0x7548, then the final multiply
float PolyOdd(float x) {
    float t = x * -3.5950437e-05f;
    t = ppc::fmadds(x, t, 0.002490001f);
    t = x * t;
    t = ppc::fmsubs(x, t, 0.080745436f);
    t = x * t;
    t = ppc::fmadds(x, t, 0.7853982f);
    return x * t;
}
float SinfPositive(float x) {
    int32_t n;
    const float fraction = OctantReduce(x, &n);
    float result = ((n + 1) & 2) != 0 ? PolyEven(fraction) : PolyOdd(fraction);
    if ((n & 7) > 3) result = -result;
    return result;
}
float CosfPositive(float x) {
    int32_t n;
    const float fraction = OctantReduce(x, &n);
    float result = ((n + 1) & 2) == 0 ? PolyEven(fraction) : PolyOdd(fraction);
    if (((n + 2) & 7) > 3) result = -result;
    return result;
}
bool SignBit(float x) {
    int32_t bits;
    std::memcpy(&bits, &x, 4);
    return bits < 0;
}
}  // namespace

// 0x005090a8 CKS08GameSpawnPoint_ResolveSlotPosition_maybe: the slot's position (the beacon's three
// half-words / 10) and direction (sin, 0, cos of its angle byte), or nothing when the slot's accessor is
// all 0xffff. The beacon is found through the beacon service: sector, kluster, id, then the set's beacon.
CKS08GameSpawnPoint::Slot* CKS08GameSpawnPoint::ResolveSlotPosition(int32_t slot) {
    const uint16_t* accessor = m_aBeacons[slot];
    if (accessor[0] == 0xffff && accessor[1] == 0xffff && accessor[2] == 0xffff && accessor[3] == 0xffff)
        return nullptr;
    const uint8_t* beacon = nullptr;  // BUG(original): without klusters it reads address 0 (halves 0, 1, 2; angle byte 6)
    CKSrvBeacon* service = static_cast<CKSrvBeacon*>(g_pEngine->m_srvBeacon);
    CKSrvBeacon::CKBeaconSector& sector = service->m_aBeaconSectors[accessor[0]];
    if (sector.m_apBeaconKlusters != nullptr) {
        CKBeaconKluster* kluster = reinterpret_cast<CKBeaconKluster**>(sector.m_apBeaconKlusters)[accessor[1]];
        const uint8_t setIndex = static_cast<uint8_t>(kluster->m_ai8IdToBeaconSet[accessor[2]]);
        CKSrvBeacon::CKBeaconSet* set = nullptr;  // 0 for the id with no set (0xff)
        if (setIndex != 0xff) set = kluster->m_aBeaconSets + static_cast<int8_t>(setIndex);
        beacon = static_cast<const uint8_t*>(set->m_aBeacons) + static_cast<uint32_t>(accessor[3]) * set->m_ui8VolatileSizeBytes;
    }
    int16_t halves[3];
    std::memcpy(halves, beacon, 6);
    Slot& out = m_aSlots[slot];
    out.m_vPosition[0] = static_cast<float>(halves[0]) * 0.1f;  // 0.1f, TOC1 +0x754c
    out.m_vPosition[1] = static_cast<float>(halves[1]) * 0.1f;
    out.m_vPosition[2] = static_cast<float>(halves[2]) * 0.1f;
    const float angle = static_cast<float>(static_cast<int8_t>(beacon[6])) * 3.1415927f * 0.0078125f;  // pi, 1/128
    float s;
    float c;
    if (SignBit(angle)) {
        s = -SinfPositive(-angle);
        c = CosfPositive(-angle);
    } else {
        s = SinfPositive(angle);
        c = CosfPositive(angle);
    }
    out.m_vDirection[0] = s;
    out.m_vDirection[1] = 0.0f;
    out.m_vDirection[2] = c;
    return &out;
}

// 0x00508778 CKS08GameSpawnPoint_Activate_maybe
uint16_t CKS08GameSpawnPoint::Activate() { return CKGameSpawnPoint::Activate(); }

// 0x005087c8 CKS08GameSpawnPoint_ClearLevelData
void CKS08GameSpawnPoint::DestroyLevelData() { CKGameSpawnPoint::DestroyLevelData(); }

// 0x005087a0 CKS08GameSpawnPoint_ClearGameData_maybe
void CKS08GameSpawnPoint::DestroyGameData() { CKGameSpawnPoint::DestroyGameData(); }

// 0x005088a0 CKS08GameSpawnPoint_MessageProc
int32_t CKS08GameSpawnPoint::MessageProc(uint16_t message, void* data) {
    if (message != 0x203) {
        const int32_t answer = CKGameSpawnPoint::MessageProc(message, data);  // 0x3d560
        if (answer == 3) return 3;
        if (answer == 2) return 2;
        return answer != 0 ? 1 : 0;
    }
    CKS08GameManager* manager = static_cast<CKS08GameManager*>(m_pGameStage->GetGameManager());  // 0x391e0
    if (manager->VfC4() != 0) {  // vt+0xc4
        manager->m_unkAFC = (manager->m_unkAFC & ~0x200u) | 0x200u;
        return 0;
    }
    m_pGameStage->m_pGameStructure->SetCurrentSpawnPoint(this);  // vt+0x6c
    CDefaultGameManager* owner = m_pGameStage->GetGameManager();
    const uint32_t flags = manager->m_flags64;
    const int32_t level = m_pGameStage->m_i32StageIndex;
    owner->m_requestedSector = m_iSectorIndex;
    owner->m_requestedLevel = level;
    if ((flags & 0x10000u) != 0) manager->m_unkAFC = (manager->m_unkAFC & ~0x400u) | 0x400u;
    return 0;
}
