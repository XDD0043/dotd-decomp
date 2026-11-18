// CKSrvBeacon.h - the beacon service (key 0x2c1, vtable 0xb19bd0, size 0x24). Original unit:
// CKSrvBeacon.cpp (0x123350-0x125e70). XXL2: K/KServices/KServiceBeacon/CKSrvBeacon.h: the same
// members, the bundles and the sectors read in the same order (the sectors from the last one down).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/services/IKService.h"
#include "k2000/util/TVector.h"

class IKFile;
struct CVector3;

class CKSrvBeacon : public IKService {
public:
    DOTD_CLASS_KEY(kCategoryService, 0xb)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9a6f28
        return key == 0x2c1 || key == 0x1 || key == 0x3fe || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKSrvBeacon)

    // XXL2 CKSrvBeacon::CKBeaconBundle, 0xc bytes on the PS3: six bytes read as stored, then the owner.
    struct CKBeaconBundle {
        uint8_t m_ui8VolatileSizeInBytes;   // +0x00
        uint8_t m_ui8PeristentSizeInBits;   // +0x01 (XXL2 spelling)
        uint8_t m_ui8BeaconIndex;           // +0x02
        uint8_t m_tBeaconID;                // +0x03
        uint8_t m_bIsMcSerializable;        // +0x04
        uint8_t m_bIsSectorizable;          // +0x05
        uint8_t m_pad06[2];                 // +0x06
        IKSerializable* m_pOwner;           // +0x08
    };

    // XXL2 CBitArrayVar: a byte block holding m_ui32NbBit bits.
    struct CBitArrayVar {
        uint8_t* m_p8Bits;      // +0x00 Mem_AllocAligned16(((bits - 1) >> 3) + 1)
        uint32_t m_ui32NbBit;   // +0x04
    };

    // XXL2 CKSrvBeacon::CKBeaconSector, 0x40 bytes on the PS3. new[] (an array cookie, as the
    // original's OperatorNewArray(n * 0x40 + 4)); the constructor clears the seven pointers and the
    // two bit arrays.
    struct CKBeaconSector {
        CKBeaconSector();
        // The PS3 has no out-of-line copy: 0x00123f30 CKSrvBeacon_Destroy's array delete inlines it per element (the
        // memory-card bits and the persistent bits freed, the pointers kept); CKSrvBeacon::Destroy writes those frees
        // out in its loop before `delete[]`, so the C++ destructor is empty.
        ~CKBeaconSector() {}

        IKSerializable** m_apBeaconKlusters;     // +0x00 CKBeaconKluster* (Mem_AllocAligned16)
        void* m_aSectorBeaconSets;               // +0x04 CKBeaconSet*
        void* m_pSectorBeaconSetsIterator;       // +0x08
        void* m_pvVolatileData;                  // +0x0c
        void* m_pvVolatileDataIterator;          // +0x10
        int8_t* m_pi8IdToSets;                   // +0x14
        int8_t* m_pi8IdToSetsIterator;           // +0x18
        uint32_t m_ui32NbValidBeaconSets;        // +0x1c
        uint32_t m_ui32NbTotalBeaconSets;        // +0x20
        uint32_t m_ui32BeaconsVolatileSize;      // +0x24
        CBitArrayVar m_bavPersistent;            // +0x28 read for a level
        CBitArrayVar m_bavMCPersistent;          // +0x30 read for a memory-card restore
        uint32_t m_ui32BeaconsPersistentSize;    // +0x38
        uint32_t m_ui32BeaconsPersistentIterator;  // +0x3c not set by the constructor or Load
    };

    // XXL2 CKBeaconSet (0x1c bytes on the PS3): the beacons of one owner in one kluster. Allocated by
    // AllocateSectorBeaconSets (new[], the constructor's three stores); CKBeaconKluster_Load fills it.
    struct CKBeaconSet {
        CKBeaconSet() {
            m_aBeacons = nullptr;
            m_pNext = nullptr;
            m_ui32Priority = 0x7fffffffu;
        }

        CKBeaconSet* m_pNext;               // +0x00 XXL2 CSPriorityBaseNode<CKBeaconSet*>::m_pNext
        uint32_t m_ui32Priority;            // +0x04
        void* m_aBeacons;                   // +0x08 XXL2 m_aBeacons: AllocateBeaconSetBeacons(count * volatile size)
        uint32_t m_ui32NbBeacons;           // +0x0c XXL2 m_ui32NbBeacons
        uint8_t m_ui8VolatileSizeBytes;     // +0x10 XXL2 (one 3-byte read with the next two)
        uint8_t m_ui8PersistentSizeBits;    // +0x11 XXL2
        uint8_t m_tBeaconID;                // +0x12 XXL2 TBeaconID
        uint8_t m_pad13;
        // +0x14 four 16-bit values (one 8-byte read, each swapped); the first three are the beacon
        // accessor the 0x1001 message carries. XXL2 has bytes here (m_ui8NumSector, m_ui8NumKluster,
        // m_ui8SetIndex, then m_ui16PersistentStart): the names would be _maybe.
        uint16_t m_aui16Accessor[4];
    };

    // XXL2 SKBeaconMsg: the data of message 0x1001 (CKBeaconKluster_Load asks a set's owner to read its
    // beacons) and 0x1000. PS3 offsets in the comments.
    struct SKBeaconMsg {
        IKFile* m_pFile;               // +0x00
        CKBeaconSet* m_pBeaconSet;     // +0x04
        uint32_t m_ui32NbBeacons;      // +0x08 (the handlers count it down)
        uint32_t m_pad0c;              // +0x0c not set
        uint8_t* m_pvBeacon;           // +0x10 XXL2 m_beaconIterator.m_pvBeacon: the next beacon's data
        uint32_t m_pad14;              // +0x14 not set
        int16_t m_ai16Accessor[4];     // +0x18 XXL2 m_beaconIterator.m_tAccessor: the set's three values, -1;
                                       //       the handlers count +0x1e up per beacon
        uint8_t m_tBeaconID;           // +0x20 XXL2 m_tBeaconID
    };

    CKSrvBeacon();  // 0x001236a8 CKSrvBeacon_Construct
    // 0x00125c88 CKSrvBeacon_Destructor (0x125d28 Destructor_2 the same, 0x125dc8 DeletingDestructor + delete): the
    // global (0xcea86c) and the engine's beacon service cleared, the bundle block freed, its length and block cleared.
    ~CKSrvBeacon() override;
    // vt+0x24 0x001233a0 CKSrvBeacon_RecursiveRegistration: type 4: the service registered.
    void RecursiveRegistration(int32_t type) override;

    // vt+0x1c 0x001241b8 CKSrvBeacon_MessageProc: message 0x1001 reads the beacons of IDs 5 and 0x27 from
    // the file (returns 0); 0x1000 writes them (returns 0); other messages return 1.
    int32_t MessageProc(uint16_t message, void* data) override;
    // 0x001237b8 CKSrvBeacon_ReleaseKlusterData_maybe (XXL2 FreeSectorBeaconSets, the same arguments):
    // AllocateSectorBeaconSets undone for the unloading sector (CKBeaconKluster::Destroy); the sector's
    // blocks are freed when its iterators are back at the start.
    void FreeSectorBeaconSets(CKBeaconSet* sets, uint32_t nbValid, int8_t* idToSet, uint32_t nbTotal);
    // 0x001238b8 CKSrvBeacon_AllocBeaconData (XXL2 AllocateBeaconSetBeacons): size bytes from the loading
    // sector's volatile data block.
    void* AllocateBeaconSetBeacons(uint32_t size);
    // 0x001239a8 CKSrvBeacon_AllocKlusterBings (XXL2 AllocateSectorBeaconSets, the same arguments): the
    // loading sector's blocks (made on first use), then nbValid sets and nbTotal id bytes for one kluster.
    void AllocateSectorBeaconSets(CKBeaconSet** sets, uint32_t nbValid, int8_t** idToSet, uint32_t nbTotal);
    // 0x00124db8 CKSrvBeacon_SaveSectorBeaconBits_maybe (XXL2 StoreMCPersistentDatas): a loaded sector's
    // persistent beacon bits of the memory-card beacons copied into its memory-card bit array.
    void SaveSectorBeaconBits(int32_t sector);
    // The beacon an accessor (sector, kluster, id, index: four 16-bit values) names, as the blocs read it
    // (e.g. 0x0018dd80 CKTeleportCinematicBloc_TeleportToBeacon_maybe): three 16-bit tenths of a position, then a signed
    // yaw byte. Null for a sector without klusters or an id without a set (the original reads the low addresses).
    const uint8_t* GetBeaconData(const uint16_t* accessor) const;
    // The set an accessor names (as GetBeaconData; null without one).
    CKBeaconSet* GetBeaconSet(const uint16_t* accessor) const;
    // 0x00123438 CKSrvBeacon_BeginTypeIteration_maybe: the sets of beacon type `type` in the klusters of `sector`, linked
    // through m_pNext (the last kluster's first); null for an unknown type.
    CKBeaconSet* BeginTypeIteration(uint8_t type, int32_t sector);
    // 0x00123b40 CKSrvBeacon_GatherBeaconsOfType_maybe: the sets of beacon type `type` in every drawn sector's klusters.
    // `flags` 1: the kluster's sphere tested against the frustum (5 planes; outside: dropped, or with 4 into `outside`);
    // 2 / 8: the inside / outside list sorted by the kluster's distance key (~(int)((|dx| + |dy| + |dz|) x 1000) to
    // `center` or the camera, nearest first), else pushed in front. The inside list returned.
    CKBeaconSet* GatherBeaconsOfType(uint8_t type, uint32_t flags, CKBeaconSet** outside, const CVector3* center);
    // 0x00123530 SList_TakeNext_maybe: the head of `list`, which moves on.
    static CKBeaconSet* TakeNext(CKBeaconSet** list) {
        CKBeaconSet* head = *list;
        if (head == nullptr) return nullptr;
        *list = head->m_pNext;
        return head;
    }

    void Destroy() override;  // vt+0x10 0x00123f30 CKSrvBeacon_Destroy
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00125598 CKSrvBeacon_Load
    // vt+0x50 0x00123970 CKSrvBeacon_Start: the bundle index back to 0, the current beacon id the first bundle's
    // (0xff without bundles).
    void Start() override;
    void Restart() override;                            // vt+0x54 0x124ca8 CKSrvBeacon_Restart
    void Stop() override;                               // vt+0x68 0x124100 CKSrvBeacon_Stop
    void Pause() override {}                            // vt+0x70 0x123418 (empty)
    void Resume() override {}                           // vt+0x78 0x123420 (empty)
    // vt+0x7c 0x001238f0 UpdateCKSrvBeacon: while the clock runs, one bundle per frame: the index moves on and the
    // current beacon id is that bundle's; past the last bundle the id is 0xff until the index reaches
    // m_ui8UpdateEachFrame, then the round starts again at bundle 0.
    void Update(IKTime* time) override;
    // vt+0x8c 0x001252a0 CKSrvBeacon_SectorUnload: the sector's persistent bits saved (not for sector 0), every
    // bundle owner told with message 0x1004 (its beacon id in the high byte, the sector in the low byte).
    void SectorUnload(int32_t sector) override;
    // vt+0x88 0x00124b88 CKSrvBeacon_SectorLoaded: a sector that was saved (state bit 1) gets its persistent bits
    // restored and every bundle owner told with message 0x1002; a sector with state bit 2 only, 0x1003 (the
    // beacon id in the high byte of the data, the sector in the low byte).
    void SectorLoaded(int32_t sector) override;
    // 0x001248b8 CKSrvBeacon_RestoreSectorBeaconBits_maybe (XXL2 RestoreMCPersistentDatas): the reverse of
    // SaveSectorBeaconBits, the memory-card bits copied back into the sector's persistent bits.
    void RestoreSectorBeaconBits(int32_t sector);
    int32_t InitializeService() override { return 1; }  // vt+0x94 0x123428
    void DestroyService() override {}                   // vt+0x98 0x123430 (empty)

    TVector<CKBeaconBundle, 1> m_vBeaconBundles;  // +0x0c
    CKBeaconSector* m_aBeaconSectors;             // +0x18 new CKBeaconSector[m_ui32NbSectors]
    uint32_t m_ui32NbSectors;                     // +0x1c
    uint8_t m_ui8NumCurrentBeaconIndex;           // +0x20 not set by the constructor or Load; Start / Update
    uint8_t m_tNumCurrentBeaconID;                // +0x21 not set by the constructor or Load; Start / Update
    uint8_t m_ui8UpdateEachFrame;                 // +0x22 read first
    uint8_t m_ui8PadUnused;                       // +0x23
};
DOTD_ASSERT_SIZE(CKSrvBeacon::CKBeaconSet, 0x1c);
DOTD_ASSERT_OFFSET(CKSrvBeacon::CKBeaconSet, m_aBeacons, 0x08);
DOTD_ASSERT_OFFSET(CKSrvBeacon::CKBeaconSet, m_ui8VolatileSizeBytes, 0x10);
DOTD_ASSERT_OFFSET(CKSrvBeacon::CKBeaconSet, m_aui16Accessor, 0x14);
DOTD_ASSERT_OFFSET(CKSrvBeacon::SKBeaconMsg, m_pvBeacon, 0x10);
DOTD_ASSERT_OFFSET(CKSrvBeacon::SKBeaconMsg, m_ai16Accessor, 0x18);
DOTD_ASSERT_OFFSET(CKSrvBeacon::SKBeaconMsg, m_tBeaconID, 0x20);
DOTD_ASSERT_SIZE(CKSrvBeacon::CKBeaconBundle, 0xc);
DOTD_ASSERT_SIZE(CKSrvBeacon::CKBeaconSector, 0x40);
DOTD_ASSERT_OFFSET(CKSrvBeacon::CKBeaconSector, m_ui32NbValidBeaconSets, 0x1c);
DOTD_ASSERT_OFFSET(CKSrvBeacon::CKBeaconSector, m_bavPersistent, 0x28);
DOTD_ASSERT_OFFSET(CKSrvBeacon::CKBeaconSector, m_bavMCPersistent, 0x30);
DOTD_ASSERT_OFFSET(CKSrvBeacon::CKBeaconSector, m_ui32BeaconsPersistentSize, 0x38);
DOTD_ASSERT_SIZE(CKSrvBeacon, 0x24);
DOTD_ASSERT_OFFSET(CKSrvBeacon, m_ui32Priority, 0x08);
DOTD_ASSERT_OFFSET(CKSrvBeacon, m_vBeaconBundles, 0x0c);
DOTD_ASSERT_OFFSET(CKSrvBeacon, m_aBeaconSectors, 0x18);
DOTD_ASSERT_OFFSET(CKSrvBeacon, m_ui32NbSectors, 0x1c);
DOTD_ASSERT_OFFSET(CKSrvBeacon, m_ui8UpdateEachFrame, 0x22);

// 0x00cea86c (XXL2 g_pSrvBeacon): the constructor stores the service here; CKBeaconKluster_Load reads it.
extern CKSrvBeacon* g_pSrvBeacon;
