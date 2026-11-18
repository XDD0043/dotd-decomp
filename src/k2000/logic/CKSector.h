// CKSector.h - one streamed sector of a level (key 0x10c, vtable 0xb141f8, size 0xc0). Original unit:
// CKSector.cpp (0x32cb0-0x33b30). XXL2: K/KCore/Level/CKSector.h; its Load reads the same members in
// the same order (the trigger starters first, the AABB after the kluster lists).
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"
#include "k2000/misc/SectorRequest.h"
#include "k2000/math/CBBox.h"
#include "k2000/services/CTriggerStarter.h"

class CSGSectorRoot;
class IKTime;
class CKSoundDictionary;
class CKMeshKluster;
class CKSectorDetector;

class CKSector : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x4)
    int32_t IsKindOfClass(uint32_t key) override { return key == 0x10c || key == 0xc; }  // vt+0x08 0x994148
    DOTD_DECLARE_FACTORIES(CKSector)
    // vt+0x40 0x00033448 CKSector_GetInfo: the trigger values 5 (bit 0 of +0x06, the sector active).
    int32_t GetInfo(IKInfo* info, int32_t request) override;
    // vt+0x1c 0x00033398 CKSector_MessageProc: 0x1200 switches the level to this sector (CKLevel::SwitchToSector, no
    // wait), 0x1201 enters it (CKLevel::EnterSector: the game waits on the job queue until it is streamed); 0 for both,
    // 1 otherwise.
    int32_t MessageProc(uint16_t message, void* data) override;

    CKSector();  // inlined in 0x000335f8 CKSector_Create
    ~CKSector() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x000336a0 CKSector_Load
    int32_t PostLoad(int32_t type) override;            // vt+0x30 0x00032e18 CKSector_PostLoad
    void Destroy() override;                            // vt+0x10 0x000332d0 CKSector_Destroy

    // The sector's runtime slots (XXL2: PreSectorLoaded, SectorLoaded, SectorUnload, PostSectorUnload; the
    // argument is the sector index). CKLevel calls vt+0x58 / vt+0x5c on every sector it holds.
    virtual void PreSectorLoaded(int32_t sector);   // vt+0x50 0x00033128 CKSector_NotifySectorLoaded_maybe
    virtual void SectorLoaded(int32_t /*sector*/) {}  // vt+0x54 0x00032c20 CKSector_vf54 (empty)
    virtual void SectorUnload(int32_t /*sector*/) {}  // vt+0x58 0x00032c28 CKSector_vf58 (empty)
    virtual void PostSectorUnload(int32_t sector);  // vt+0x5c 0x00033238 CKSector_NotifySectorUnload_maybe
    // 0x000334b0 CKSector_FindSectorAtPoint_maybe: the sector the point (x, y, z) is in, by the sector's CKSas
    // boxes (last to first; the first box answers with its first number, the second with its second), or -2.
    int32_t FindSectorAtPoint(const float* point);
    // 0x000331c0 CKSector_UpdateMeshKlusters: every mesh kluster of the list updated (vt+0x58).
    void UpdateMeshKlusters(IKTime* frameClock);
    void QueueLoadedEvent();                            // 0x00032da8 CKSector_QueueLoadedEvent_maybe
    void QueueEnterEvent();                             // 0x00032de0 CKSector_QueueEnterEvent_maybe
    // 0x00032c08 CKSector_SetActive_maybe (CKSas.cpp): bit 0 of m_ba16Properties, the sector loaded/active
    // bit (CKLevel_PostLoad, CKLevel_Update, the sector unload paths; the Flash interfaces gate on it).
    void SetActive(uint16_t active) { m_ba16Properties = static_cast<uint16_t>((m_ba16Properties & 0xfffe) | active); }

    uint16_t m_ui16NumSector;               // +0x04 constructor 0xffff
    uint16_t m_ba16Properties;              // +0x06 XXL2 CBitArray16; constructor 2; Load clears bit 0
    CSGSectorRoot* m_pSectorRoot;           // +0x08
    CKSoundDictionary* m_pSoundDictionary;  // +0x0c
    IKSerializable** m_apSasOut;            // +0x10 CKSas* (OperatorNewArray); not set by the constructor
    uint32_t m_ui32NbSas;                   // +0x14
    CBBox m_AABB;                           // +0x18
    CKMeshKluster* m_lMeshKlusterList;      // +0x30 XXL2 MeshKlusterList (its head)
    IKSerializable* m_lBeaconKlusterList;   // +0x34 XXL2 BeaconKlusterList (CKBeaconKluster head)
    CKSectorDetector* m_pSectorDetector;    // +0x38
    CTriggerStarter m_tsStartLoading;       // +0x3c
    CTriggerStarter m_tsEndLoading;         // +0x44
    uint32_t m_unk4c;                       // +0x4c not set by the constructor or the Load
    SectorRequest m_request;                // +0x50 (XXL2 has no such member)
};
DOTD_ASSERT_SIZE(CKSector, 0xc0);
DOTD_ASSERT_OFFSET(CKSector, m_ui16NumSector, 0x04);
DOTD_ASSERT_OFFSET(CKSector, m_ba16Properties, 0x06);
DOTD_ASSERT_OFFSET(CKSector, m_pSectorRoot, 0x08);
DOTD_ASSERT_OFFSET(CKSector, m_pSoundDictionary, 0x0c);
DOTD_ASSERT_OFFSET(CKSector, m_apSasOut, 0x10);
DOTD_ASSERT_OFFSET(CKSector, m_ui32NbSas, 0x14);
DOTD_ASSERT_OFFSET(CKSector, m_AABB, 0x18);
DOTD_ASSERT_OFFSET(CKSector, m_lMeshKlusterList, 0x30);
DOTD_ASSERT_OFFSET(CKSector, m_lBeaconKlusterList, 0x34);
DOTD_ASSERT_OFFSET(CKSector, m_pSectorDetector, 0x38);
DOTD_ASSERT_OFFSET(CKSector, m_tsStartLoading, 0x3c);
DOTD_ASSERT_OFFSET(CKSector, m_tsEndLoading, 0x44);
DOTD_ASSERT_OFFSET(CKSector, m_request, 0x50);
