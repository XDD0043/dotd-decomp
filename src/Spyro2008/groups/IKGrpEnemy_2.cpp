// Reconstructed original translation unit: 0x265ee0-0x2665a0 (GAME_TOC1, main_toc1), 6 functions, 6 live.
// Primary owner: IKGrpEnemy (not a registered class)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x265ee0  IKGrpEnemy_HandleMessage  (MessageProc)
//   [x] 0x2661f0  IKGrpEnemy_LevelReset  (IKGroup's only: IKBaseGroup::RecursiveRegistration inherited)
//   [ ] 0x266218  IKGrpEnemy_Save
//   [x] 0x266240  IKGrpEnemy_ClearReferences
//   [x] 0x266320  IKGrpEnemy_vf170  (LoadRecord)
//   [x] 0x266468  IKGrpEnemy_vf16C  (SaveRecord)
#include "k2000/misc/IKGrpEnemy.h"

#include "k2000/memory/Mem.h"
#include "k2000/io/IKFile.h"
#include "k2000/services/CKSrvBeacon.h"

// 0x00266240 IKGrpEnemy_ClearReferences (vt+0x10; CKGrpS08Enemy_Destroy 0x267568 only calls it): no child groups, no
// members, the three reference vectors' blocks freed and emptied (+0x4c first).
void IKGrpEnemy::Destroy() {
    m_lChilds = nullptr;
    *GetMemberListHead() = nullptr;  // vt+0xb0
    if (m_vUnk4c.m_pBlock != nullptr) Mem_FreeAligned16(m_vUnk4c.m_pBlock);
    m_vUnk4c.m_ui32NbUsedElt = 0;
    m_vUnk4c.m_pBlock = nullptr;
    if (m_vpFZSectorGrpRoot.m_pBlock != nullptr) {
        Mem_FreeAligned16(m_vpFZSectorGrpRoot.m_pBlock);
        m_vpFZSectorGrpRoot.m_pBlock = nullptr;
    }
    m_vpFZSectorGrpRoot.m_ui32NbUsedElt = 0;
    m_vpFZSectorGrpRoot.m_pBlock = nullptr;
    if (m_vUnk40.m_pBlock != nullptr) {
        Mem_FreeAligned16(m_vUnk40.m_pBlock);
        m_vUnk40.m_pBlock = nullptr;
    }
    m_vUnk40.m_ui32NbUsedElt = 0;
    m_vUnk40.m_pBlock = nullptr;
}

// 0x00265ee0 IKGrpEnemy_HandleMessage (vt+0x1c). The halves go out as two bytes, low first (the PS3 swaps them with
// lhbrx; here the value is already in host order), the fourth raw, as CKSrvBeacon's.
int32_t IKGrpEnemy::MessageProc(uint16_t message, void* data) {
    if ((message >> 8) != 0x10) return 1;
    // The message's fields are read only for 0 and 1 (as the original): CKSrvBeacon::Restart sends 0x1003 with an
    // integer as `data` (C2.8 lvl020-walkers: the x64 port read it as a pointer on a level restart).
    if ((message & 0xff) != 0 && (message & 0xff) != 1) return 1;
    CKSrvBeacon::SKBeaconMsg* msg = static_cast<CKSrvBeacon::SKBeaconMsg*>(data);
    IKFile* file = msg->m_pFile;
    const CKSrvBeacon::CKBeaconSet* set = msg->m_pBeaconSet;
    if ((message & 0xff) == 0) {
        while (msg->m_ui32NbBeacons-- != 0) {  // ends at 0xffffffff, as the original's
            const uint8_t* beacon = msg->m_pvBeacon;
            ++msg->m_ai16Accessor[3];
            msg->m_pvBeacon = msg->m_pvBeacon + set->m_ui8VolatileSizeBytes;
            for (int i = 0; i < 3; ++i) file->Write(beacon + i * 2, 2);
            file->Write(beacon + 6, 2);
        }
        return 0;
    }
    if ((message & 0xff) != 1) return 1;
    while (msg->m_ui32NbBeacons-- != 0) {
        uint8_t* beacon = msg->m_pvBeacon;
        ++msg->m_ai16Accessor[3];
        msg->m_pvBeacon = beacon + set->m_ui8VolatileSizeBytes;
        uint16_t* values = reinterpret_cast<uint16_t*>(beacon);
        ReadU16LE(file, &values[0]);  // one 6-byte read, three halves swapped
        ReadU16LE(file, &values[1]);
        ReadU16LE(file, &values[2]);
        file->Read(beacon + 6, 2);
    }
    return 0;
}

// 0x00266468 IKGrpEnemy_vf16C: the record's floats little-endian (lwbrx through a temporary), then its byte.
void IKGrpEnemy::SaveRecord(IKFile* file, void* /*unused*/, void* record) {
    SSaveRecord* r = static_cast<SSaveRecord*>(record);
    file->Write(&r->m_unk08, 4);
    file->Write(&r->m_unk0c, 4);
    file->Write(&r->m_unk10, 4);
    file->Write(&r->m_unk24, 1);
}

// 0x00266320 IKGrpEnemy_vf170
void IKGrpEnemy::LoadRecord(IKFile* file, void* /*unused*/, void* record) {
    SSaveRecord* r = static_cast<SSaveRecord*>(record);
    ReadF32LE(file, &r->m_unk08);
    ReadF32LE(file, &r->m_unk0c);
    ReadF32LE(file, &r->m_unk10);
    file->Read(&r->m_unk24, 1);
}
