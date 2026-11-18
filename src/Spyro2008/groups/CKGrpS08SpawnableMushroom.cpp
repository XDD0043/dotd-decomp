// CKGrpS08SpawnableMushroom.cpp - reconstructed original translation unit 0x4d7218-0x4d8018 (GAME_TOC1, main_toc1), 21 functions, 21 live.
// Primary class: CKGrpS08SpawnableMushroom  key 0xd84  category Group  size 0x84  vtable 0xb2a050
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x4d7218  CKGrpS08SpawnableMushroom_Delete
//   [x] 0x4d7268  CKGrpS08SpawnableMushroom_vf100
//   [x] 0x4d7328  CKGrpS08SpawnableMushroom_vfFC
//   [ ] 0x4d7330  RegisterCKGrpS08SpawnableMushroomClass
//   [ ] 0x4d73a8  _GLOBAL__I_4d73a8
//   [x] 0x4d73b8  CKGrpS08SpawnableMushroom_SpawnFromSectorBeacons_maybe
//   [x] 0x4d7958  CKGrpS08SpawnableMushroom_SectorLoaded
//   [x] 0x4d79a0  CKGrpS08SpawnableMushroom_Restart
//   [x] 0x4d79c8  CKGrpS08SpawnableMushroom_Update
//   [x] 0x4d79f0  CKGrpS08SpawnableMushroom_Stop
//   [x] 0x4d7a18  CKGrpS08SpawnableMushroom_Start
//   [x] 0x4d7a40  CKGrpS08SpawnableMushroom_MessageProc
//   [x] 0x4d7a98  CKGrpS08SpawnableMushroom_GetInfo  (KBase1944's answer (1) mapped to 1: IKSerializable's GetInfo inherited)
//   [x] 0x4d7ae8  CKGrpS08SpawnableMushroom_PostLoad  (= KBase1944::PostLoad, inherited)
//   [ ] 0x4d7b10  CKGrpS08SpawnableMushroom_Save
//   [x] 0x4d7b38  CKGrpS08SpawnableMushroom_RecursiveRegistration  (KBase1944's (IKGroup's): inherited)
//   [x] 0x4d7b60  CKGrpS08SpawnableMushroom_Destroy  (inherited: KBase1944_Destroy)
//   [x] 0x4d7b88  CKGrpS08SpawnableMushroom_DeleteArray
//   [x] 0x4d7c30  CKGrpS08SpawnableMushroom_CreateArray
//   [x] 0x4d7ce8  CKGrpS08SpawnableMushroom_Create
//   [x] 0x4d7d40  CKGrpS08SpawnableMushroom_Load
//
//   [ ] 0x9c3550  CKGrpS08SpawnableMushroom_vfCC  [inline]
//   [ ] 0x9c35e8  CKGrpS08SpawnableMushroom_vfB0  [inline]
//   [ ] 0x9c35f8  CKGrpS08SpawnableMushroom_vfB4  [inline]
//   [ ] 0x9c3608  CKGrpS08SpawnableMushroom_vfBC  [inline]
//   [ ] 0x9c36b0  CKGrpS08SpawnableMushroom_vfE0  [inline]
//   [ ] 0x9c36b8  CKGrpS08SpawnableMushroom_vfE4  [inline]
//   [ ] 0x9c36c0  CKGrpS08SpawnableMushroom_vfE8  [inline]
//   [ ] 0x9c36c8  CKGrpS08SpawnableMushroom_vfD8  [inline]
//   [ ] 0x9c3708  CKGrpS08SpawnableMushroom_vfDC  [inline]
//   [ ] 0x9c5fa8  CKGrpS08SpawnableMushroom_IsKindOfClass  [inline]
//   [x] 0x9c6008  CKGrpS08SpawnableMushroom_GetClassType  [inline]
//   [x] 0x9c6010  CKGrpS08SpawnableMushroom_GetClassID  [inline]
//   [ ] 0x9c6018  CKGrpS08SpawnableMushroom_Pause  [inline]
//   [ ] 0x9c6020  CKGrpS08SpawnableMushroom_Resume  [inline]
//   [ ] 0x9c6028  CKGrpS08SpawnableMushroom_vfF0  [inline]
//   [ ] 0x9c6030  CKGrpS08SpawnableMushroom_vfF4  [inline]
//   [ ] 0x9c6038  CKGrpS08SpawnableMushroom_vf104  [inline]
//   [ ] 0x9c6040  CKGrpS08SpawnableMushroom_vf108  [inline]
//   [ ] 0x9c6058  CKGrpS08SpawnableMushroom_vf10C  [inline]
//   [ ] 0x9c6070  CKGrpS08SpawnableMushroom_vfEC  [inline]
//   [ ] 0x9c6088  CKGrpS08SpawnableMushroom_DeletingDestructor  [inline]
//   [ ] 0x9c6138  CKGrpS08SpawnableMushroom_Destructor  [inline]
#include "Spyro2008/groups/CKGrpS08SpawnableMushroom.h"
#include "k2000/services/CKSrvBeacon.h"
#include "k2000/misc/Engine.h"

// 0x004d7d40 CKGrpS08SpawnableMushroom_Load
int32_t CKGrpS08SpawnableMushroom::Load(IKFile* file, int32_t type) {
    KBase1944::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadU8(file, &m_unk5d);
    ReadF32LE(file, &m_unk60.x);  // one 0xc-byte read, three swaps
    ReadF32LE(file, &m_unk60.y);
    ReadF32LE(file, &m_unk60.z);
    IKFile_ReadRef(file, &m_pUnk70);
    IKFile_ReadRef(file, &m_pUnk6c);
    ReadU8(file, &m_unk74);
    ReadU32LE(file, &m_unk78);
    IKFile_ReadRef(file, &m_pUnk7c);
    ReadF32LE(file, &m_unk80);
    return 1;
}

// 0x004d7a40 CKGrpS08SpawnableMushroom_MessageProc
int32_t CKGrpS08SpawnableMushroom::MessageProc(uint16_t message, void* data) {
    const int32_t result = KBase1944::MessageProc(message, data);
    if (result == 3) return 3;
    if (result == 2) return 2;
    return result != 0 ? 1 : 0;  // ((|r| - 1) >> 31) ^ 1, the low two bits kept
}

// 0x004d7a18 CKGrpS08SpawnableMushroom_Start
void CKGrpS08SpawnableMushroom::Start() {
    KBase1944::Start();  // 0x443d58
}

namespace {
// 0x00a70c4c (TOC +0x6b2c): per mushroom kind the frustum radius, the sphere's height, then the beacon type (words).
constexpr float kKindRadius[5] = {10.0f, 10.0f, 10.0f, 10.0f, 10.0f};
constexpr float kKindHeight[5] = {2.0f, 2.0f, 2.0f, 2.0f, 2.0f};
constexpr uint8_t kKindBeaconType[5] = {0x60, 0x67, 0x68, 0x69, 0x6a};

CKSrvBeacon* Beacons() { return static_cast<CKSrvBeacon*>(g_pEngine->m_srvBeacon); }

// Bit `n` of a sector's persistent bits.
uint8_t* PersistentBits(const uint16_t* slot) { return Beacons()->m_aBeaconSectors[slot[0]].m_bavPersistent.m_p8Bits; }
void WriteBit(uint8_t* bits, uint32_t n, uint32_t value) {
    bits[n >> 3] = static_cast<uint8_t>(bits[n >> 3] & ~(1u << (n & 7)));
    bits[n >> 3] = static_cast<uint8_t>(bits[n >> 3] | ((value & 1u) << (n & 7)));
}
}  // namespace

uint8_t CKGrpS08SpawnableMushroom::VfEC(uint32_t kind) { return kKindBeaconType[kind]; }
float CKGrpS08SpawnableMushroom::Vf108(uint32_t kind) { return kKindRadius[kind]; }
float CKGrpS08SpawnableMushroom::Vf10C(uint32_t kind) { return kKindHeight[kind]; }

// 0x004d7268 CKGrpS08SpawnableMushroom_vf100
uint8_t CKGrpS08SpawnableMushroom::Vf100(const uint16_t* slot) {
    if (Beacons()->m_aBeaconSectors[slot[0]].m_apBeaconKlusters == nullptr) return 1;
    const CKSrvBeacon::CKBeaconSet* set = Beacons()->GetBeaconSet(slot);
    if (set == nullptr) return 1;  // DOTD: the original reads the low addresses
    const uint32_t n = static_cast<uint32_t>(set->m_aui16Accessor[3]) + static_cast<uint32_t>(set->m_ui8PersistentSizeBits) * slot[3];
    return static_cast<uint8_t>(((PersistentBits(slot)[n >> 3] >> (n & 7)) & 1u) ^ 1u);
}

// 0x004d7958 CKGrpS08SpawnableMushroom_SectorLoaded
void CKGrpS08SpawnableMushroom::SectorLoaded(int32_t sector) {
    KBase1944::SectorLoaded(sector);  // 0x00019e60 IKLife_SectorLoaded
    SpawnFromSectorBeacons(sector);
}

// 0x004d73b8 CKGrpS08SpawnableMushroom_SpawnFromSectorBeacons_maybe
void CKGrpS08SpawnableMushroom::SpawnFromSectorBeacons(int32_t sector) {
    CKSrvBeacon* beacons = Beacons();
    CKSrvBeacon::CKBeaconSet* list = beacons->BeginTypeIteration(VfEC(m_unk2c), sector);  // 0x00123438
    while (CKSrvBeacon::CKBeaconSet* set = CKSrvBeacon::TakeNext(&list)) {
        uint16_t slot[4] = {set->m_aui16Accessor[0], set->m_aui16Accessor[1], set->m_aui16Accessor[2], 0xffff};
        const uint8_t* beacon = static_cast<const uint8_t*>(set->m_aBeacons);
        for (uint32_t i = 0; i < set->m_ui32NbBeacons; ++i, beacon += set->m_ui8VolatileSizeBytes) {
            ++slot[3];
            if (beacons->m_aBeaconSectors[slot[0]].m_apBeaconKlusters != nullptr) {
                const CKSrvBeacon::CKBeaconSet* s = beacons->GetBeaconSet(slot);
                if (s != nullptr) {
                    uint8_t* bits = PersistentBits(slot);
                    const uint32_t base = static_cast<uint32_t>(s->m_aui16Accessor[3]) +
                                          static_cast<uint32_t>(s->m_ui8PersistentSizeBits) * slot[3];
                    bits[base >> 3] = static_cast<uint8_t>(bits[base >> 3] & ~(1u << (base & 7)));
                    for (uint32_t b = 0; b < 8; ++b) WriteBit(bits, base + 1 + b, static_cast<uint32_t>(m_unk74) >> b);
                }
            }
            VfFC(slot, beacon);  // vt+0xfc
        }
    }
}
