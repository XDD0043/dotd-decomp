// CKSector.cpp - reconstructed original translation unit 0x32cb0-0x33b30 (GAME_TOC1, main_toc1), 20 functions, 18 live.
// Primary class: CKSector  key 0x10c  category Logic  size 0xc0  vtable 0xb141f8
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x32cb0  CKSector_RemoveMeshKluster_maybe  [dead]
//   [ ] 0x32d20  RegisterCKSectorClass
//   [ ] 0x32d98  _GLOBAL__I_32d98
//   [x] 0x32da8  CKSector_QueueLoadedEvent_maybe
//   [x] 0x32de0  CKSector_QueueEnterEvent_maybe
//   [x] 0x32e18  CKSector_PostLoad
//   [ ] 0x32e90  CKSector_Save
//   [ ] 0x32f00  CKSector_RecursiveRegistration
//   [x] 0x32f60  CKSector_DeleteArray
//   [x] 0x33010  CKSector_CreateArray
//   [x] 0x33128  CKSector_NotifySectorLoaded_maybe
//   [x] 0x331c0  CKSector_UpdateMeshKlusters
//   [x] 0x33238  CKSector_NotifySectorUnload_maybe
//   [ ] 0x332d0  CKSector_Destroy
//   [ ] 0x33328  CKSector_InsertMeshKlusterSorted_maybe  [dead]
//   [ ] 0x33398  CKSector_MessageProc
//   [ ] 0x33448  CKSector_GetInfo
//   [x] 0x334b0  CKSector_FindSectorAtPoint_maybe
//   [x] 0x335f8  CKSector_Create
//   [x] 0x336a0  CKSector_Load
//
//   [ ] 0x994120  CKSector_GetClassType  [inline]
//   [ ] 0x994128  CKSector_GetClassID  [inline]
//   [ ] 0x994130  CKSector_GetSerializationFlags  [inline]
//   [ ] 0x994138  CKSector_GetTriggerProp5  [inline]
//   [ ] 0x994148  CKSector_IsKindOfClass  [inline]
//   [ ] 0x994168  CKSector_DeletingDestructor  [inline]
//   [ ] 0x9941d0  CKSector_Destructor  [inline]
#include "k2000/logic/CKSector.h"

#include "k2000/core/Stub.h"
#include "k2000/dictionaries/CKSoundDictionary.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKSas.h"
#include "k2000/logic/ai/CKSectorDetector.h"
#include "k2000/logic/render/CKMeshKluster.h"
#include "k2000/scenegraph/CSGSectorRoot.h"

// Inlined in 0x000335f8 CKSector_Create: +0x30, +0x34, the request (+0x50), then the sector's own.
CKSector::CKSector() {
    m_lMeshKlusterList = nullptr;
    m_lBeaconKlusterList = nullptr;
    m_ba16Properties = 0;
    m_ui16NumSector = 0xffff;
    m_pSectorRoot = nullptr;
    m_pSoundDictionary = nullptr;
    m_ba16Properties = static_cast<uint16_t>((m_ba16Properties & ~0x7u) | 0x2u);  // bit 1 set, bits 0 and 2 clear
}

// 0x00033128 CKSector_NotifySectorLoaded_maybe (vt+0x50): the sector's own index told: every mesh kluster
// of the list gets vt+0x50 with it.
void CKSector::PreSectorLoaded(int32_t sector) {
    if (m_ui16NumSector != static_cast<uint32_t>(sector)) return;
    for (CKMeshKluster* kluster = m_lMeshKlusterList; kluster != nullptr; kluster = kluster->m_pNext) {
        kluster->SectorLoaded_maybe(m_ui16NumSector);
    }
}

// 0x00033238 CKSector_NotifySectorUnload_maybe (vt+0x5c): the same for vt+0x54 (the active grounds dropped).
void CKSector::PostSectorUnload(int32_t sector) {
    if (m_ui16NumSector != static_cast<uint32_t>(sector)) return;
    for (CKMeshKluster* kluster = m_lMeshKlusterList; kluster != nullptr; kluster = kluster->m_pNext) {
        kluster->SectorUnload_maybe(m_ui16NumSector);
    }
}

// 0x00032e18 CKSector_PostLoad: the trigger starters' PostLoad, then the request learns its sector number.
int32_t CKSector::PostLoad(int32_t type) {
    m_tsStartLoading.PostLoad(type);
    m_tsEndLoading.PostLoad(type);
    m_request.SetSector(m_ui16NumSector);  // lhz: zero-extended
    return 1;
}

// 0x00032da8 CKSector_QueueLoadedEvent_maybe: QueueTriggerSignals on the end-loading starter.
void CKSector::QueueLoadedEvent() { QueueTriggerSignals(&m_tsEndLoading); }

// 0x00032de0 CKSector_QueueEnterEvent_maybe: QueueTriggerSignals on the start-loading starter.
void CKSector::QueueEnterEvent() { QueueTriggerSignals(&m_tsStartLoading); }

// 0x000336a0 CKSector_Load. No type test of its own: the trigger starters test it.
int32_t CKSector::Load(IKFile* file, int32_t type) {
    m_tsStartLoading.Load(file, type);
    m_tsEndLoading.Load(file, type);
    IKFile_ReadRef(file, &m_pSectorRoot);
    ReadU16LE(file, &m_ui16NumSector);
    ReadU16LE(file, &m_ba16Properties);
    m_ba16Properties &= 0xfffe;
    uint32_t count = 0;
    ReadU32LE(file, &count);
    if (count == 0) {
        m_ui32NbSas = 0;
        m_apSasOut = nullptr;
    } else {
        m_apSasOut = new IKSerializable*[count];  // OperatorNewArray(count * 4)
        m_ui32NbSas = count;
        IKFile_ReadObjectRefArray(file, m_apSasOut, count);
    }
    IKFile_ReadRef(file, &m_pSoundDictionary);
    IKFile_ReadRef(file, &m_lBeaconKlusterList);
    IKFile_ReadRef(file, &m_lMeshKlusterList);
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(&m_AABB), 6);
    IKFile_ReadRef(file, &m_pSectorDetector);
    return 1;
}

// 0x000331c0 CKSector_UpdateMeshKlusters
void CKSector::UpdateMeshKlusters(IKTime* frameClock) {
    for (CKMeshKluster* kluster = m_lMeshKlusterList; kluster != nullptr; kluster = kluster->m_pNext) {
        kluster->UpdateDynamicGrounds(frameClock);  // vt+0x58
    }
}

// 0x000334b0 CKSector_FindSectorAtPoint_maybe: the boxes' bounds are inclusive.
int32_t CKSector::FindSectorAtPoint(const float* point) {
    const float x = point[0], y = point[1], z = point[2];
    for (uint32_t i = m_ui32NbSas; i != 0; --i) {
        const CKSas* sas = static_cast<const CKSas*>(m_apSasOut[i - 1]);
        const CKSas::SBox& a = sas->m_boxA;
        if (a.m_vMin[0] <= x && x <= a.m_vMax[0] && a.m_vMin[2] <= z && z <= a.m_vMax[2] && a.m_vMin[1] <= y &&
            y <= a.m_vMax[1]) {
            return static_cast<int32_t>(sas->m_ui32SectorA);
        }
        const CKSas::SBox& b = sas->m_boxB;
        if (b.m_vMin[0] <= x && x <= b.m_vMax[0] && b.m_vMin[2] <= z && z <= b.m_vMax[2] && b.m_vMin[1] <= y &&
            y <= b.m_vMax[1]) {
            return static_cast<int32_t>(sas->m_ui32SectorB);
        }
    }
    return -2;
}
