// CKBeaconKluster.cpp - reconstructed original translation unit 0x2e880-0x2f078 (GAME_TOC1, main_toc1), 11 functions, 11 live.
// Primary class: CKBeaconKluster  key 0x124c  category Logic  size 0x28  vtable 0xb13fb8
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x2e880  CKBeaconKluster_Delete
//   [ ] 0x2e8d0  CKBeaconKluster_RecursiveRegistration
//   [ ] 0x2e8d8  CKBeaconKluster_Save
//   [ ] 0x2e8e0  CKBeaconKluster_PostLoad
//   [ ] 0x2e8e8  RegisterCKBeaconKlusterClass
//   [ ] 0x2e960  _GLOBAL__I_2e960
//   [x] 0x2e970  CKBeaconKluster_Destroy
//   [x] 0x2e9d0  CKBeaconKluster_DeleteArray
//   [x] 0x2ea78  CKBeaconKluster_Create
//   [x] 0x2eab8  CKBeaconKluster_CreateArray
//   [x] 0x2eb60  CKBeaconKluster_Load
//
//   [ ] 0x993df8  CKBeaconKluster_GetClassType  [inline]
//   [ ] 0x993e00  CKBeaconKluster_GetClassID  [inline]
//   [ ] 0x993e08  CKBeaconKluster_GetSerializationFlags  [inline]
//   [ ] 0x993e10  CKBeaconKluster_Destructor  [inline]
//   [ ] 0x993e28  CKBeaconKluster_IsKindOfClass  [inline]
//   [ ] 0x993e48  CKBeaconKluster_DeletingDestructor  [inline]
#include "k2000/logic/ai/CKBeaconKluster.h"

#include "k2000/io/IKFile.h"

// 0x0002e970 CKBeaconKluster_Destroy
void CKBeaconKluster::Destroy() {
    if (m_aBeaconSets == nullptr) return;
    g_pSrvBeacon->FreeSectorBeaconSets(m_aBeaconSets, m_ui16NbValidSets, m_ai8IdToBeaconSet, m_ui16NbTotalSets);
    m_ai8IdToBeaconSet = nullptr;
    m_aBeaconSets = nullptr;
}

// 0x0002eb60 CKBeaconKluster_Load
int32_t CKBeaconKluster::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    IKFile_ReadRef(file, &m_pNext);
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(m_afBounds), 5);
    ReadU16LE(file, &m_ui16NbTotalSets);
    ReadU16LE(file, &m_ui16NbValidSets);
    if (m_ui16NbTotalSets == 0) {
        m_ai8IdToBeaconSet = nullptr;
        return 1;
    }
    g_pSrvBeacon->AllocateSectorBeaconSets(&m_aBeaconSets, m_ui16NbValidSets, &m_ai8IdToBeaconSet, m_ui16NbTotalSets);
    int8_t setIndex = 0;
    for (uint32_t i = 0; i < m_ui16NbTotalSets; ++i) {
        uint8_t present = 0;
        ReadRaw(file, &present, 1);
        if (present == 0) {
            m_ai8IdToBeaconSet[i] = -1;
            continue;
        }
        m_ai8IdToBeaconSet[i] = setIndex;
        CKSrvBeacon::CKBeaconSet& set = m_aBeaconSets[static_cast<uint8_t>(setIndex)];
        ReadU32LE(file, &set.m_ui32NbBeacons);
        ReadRaw(file, &set.m_ui8VolatileSizeBytes, 3);  // +0x10..+0x12 as stored
        for (uint16_t& value : set.m_aui16Accessor) ReadU16LE(file, &value);  // one 8-byte read
        if (set.m_ui32NbBeacons != 0) {
            IKSerializable* owner = nullptr;
            IKFile_ReadRef(file, &owner);
            file->Seek(4, 1);  // SEEK_CUR: the beacon block's size word
            if (set.m_ui32NbBeacons == 0) {
                set.m_aBeacons = nullptr;
            } else {
                set.m_aBeacons = g_pSrvBeacon->AllocateBeaconSetBeacons(set.m_ui32NbBeacons * set.m_ui8VolatileSizeBytes);
                CKSrvBeacon::SKBeaconMsg msg;
                msg.m_pFile = file;
                msg.m_pBeaconSet = &set;
                msg.m_ui32NbBeacons = set.m_ui32NbBeacons;
                msg.m_pvBeacon = static_cast<uint8_t*>(set.m_aBeacons);
                msg.m_ai16Accessor[0] = static_cast<int16_t>(set.m_aui16Accessor[0]);
                msg.m_ai16Accessor[1] = static_cast<int16_t>(set.m_aui16Accessor[1]);
                msg.m_ai16Accessor[2] = static_cast<int16_t>(set.m_aui16Accessor[2]);
                msg.m_ai16Accessor[3] = -1;
                msg.m_tBeaconID = set.m_tBeaconID;
                owner->MessageProc(0x1001, &msg);  // BUG(original): no null check on the owner
            }
        }
        ++setIndex;
    }
    return 1;
}
