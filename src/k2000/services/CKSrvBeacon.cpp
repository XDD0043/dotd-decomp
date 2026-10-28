// CKSrvBeacon.cpp - reconstructed original translation unit 0x123350-0x125e70 (GAME_TOC1, main_toc1), 35 functions, 35 live.
// Primary class: CKSrvBeacon  key 0x2c1  category Service  size 0x24  vtable 0xb19bd0
// Other owners: SList (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x123350  CKSrvBeacon_Delete
//   [ ] 0x1233a0  CKSrvBeacon_RecursiveRegistration
//   [x] 0x123418  CKSrvBeacon_Pause
//   [ ] 0x123420  CKSrvBeacon_Resume
//   [x] 0x123428  CKSrvBeacon_InitializeService
//   [x] 0x123430  CKSrvBeacon_DestroyService
//   [ ] 0x123438  CKSrvBeacon_BeginTypeIteration_maybe
//   [ ] 0x123530  SList_TakeNext_maybe
//   [ ] 0x123550  RegisterCKSrvBeaconClass
//   [ ] 0x1235c8  _GLOBAL__I_1235c8
//   [x] 0x1235d8  CKSrvBeacon_DeleteArray
//   [ ] 0x123680  CKSrvBeacon_PostLoad
//   [x] 0x1236a8  CKSrvBeacon_Construct
//   [ ] 0x123730  CKSrvBeacon_Construct_2
//   [x] 0x1237b8  CKSrvBeacon_ReleaseKlusterData_maybe
//   [x] 0x1238b8  CKSrvBeacon_AllocBeaconData
//   [ ] 0x1238f0  UpdateCKSrvBeacon
//   [ ] 0x123970  CKSrvBeacon_Start
//   [x] 0x1239a8  CKSrvBeacon_AllocKlusterBings
//   [ ] 0x123b40  CKSrvBeacon_GatherBeaconsOfType_maybe
//   [x] 0x123f30  CKSrvBeacon_Destroy
//   [x] 0x124100  CKSrvBeacon_Stop
//   [x] 0x1241b8  CKSrvBeacon_MessageProc
//   [x] 0x1246c8  CKSrvBeacon_CreateArray
//   [x] 0x124810  CKSrvBeacon_Create
//   [x] 0x1248b8  CKSrvBeacon_RestoreSectorBeaconBits_maybe
//   [x] 0x124b88  CKSrvBeacon_SectorLoaded
//   [ ] 0x124ca8  CKSrvBeacon_Restart
//   [x] 0x124db8  CKSrvBeacon_SaveSectorBeaconBits_maybe
//   [x] 0x1252a0  CKSrvBeacon_SectorUnload
//   [ ] 0x125378  CKSrvBeacon_Save
//   [x] 0x125598  CKSrvBeacon_Load
//   [ ] 0x125c88  CKSrvBeacon_Destructor
//   [ ] 0x125d28  CKSrvBeacon_Destructor_2_maybe
//   [ ] 0x125dc8  CKSrvBeacon_DeletingDestructor
//
//   [ ] 0x9a6f28  CKSrvBeacon_IsKindOfClass  [inline]
//   [ ] 0x9a6f60  CKSrvBeacon_GetClassType  [inline]
//   [ ] 0x9a6f68  CKSrvBeacon_GetClassID  [inline]
#include "k2000/services/CKSrvBeacon.h"

#include "k2000/core/Stub.h"
#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"
#include "k2000/logic/CKLevel.h"
#include "k2000/logic/CKSector.h"
#include "k2000/logic/ai/CKBeaconKluster.h"
#include "k2000/misc/Engine.h"

CKSrvBeacon* g_pSrvBeacon = nullptr;  // 0x00cea86c

// 0x00124100 CKSrvBeacon_Stop (leaving a level or the front end): the memory-card bit array of every sector
// (counted from the level's sector count, last to first) freed and emptied.
void CKSrvBeacon::Stop() {
    for (uint32_t i = g_pEngine->m_level->m_ui32NbSectors; i != 0; --i) {
        CBitArrayVar& bits = m_aBeaconSectors[i - 1].m_bavMCPersistent;
        if (bits.m_p8Bits != nullptr) {
            Mem_FreeAligned16(bits.m_p8Bits);
            bits.m_p8Bits = nullptr;
        }
        bits.m_ui32NbBit = 0;
    }
}

// 0x001252a0 CKSrvBeacon_SectorUnload
void CKSrvBeacon::SectorUnload(int32_t sector) {
    const uint32_t unloading = static_cast<uint32_t>(sector);
    if (unloading != 0) SaveSectorBeaconBits(unloading);
    for (uint32_t i = 0; i < m_vBeaconBundles.m_ui32NbUsedElt; ++i) {
        const CKBeaconBundle& bundle = m_vBeaconBundles.m_pBlock[i];
        if (bundle.m_pOwner != nullptr) {
            const uint32_t data = (static_cast<uint32_t>(bundle.m_tBeaconID) << 8) | (unloading & 0xff);
            bundle.m_pOwner->MessageProc(0x1004, reinterpret_cast<void*>(static_cast<uintptr_t>(data)));
        }
    }
}

namespace {
// The memory-card branch loops over the level's sector count, CKLevel +0x14 (XXL2
// CKLevel::m_ui32NbSectors).
uint32_t LevelSectorCount() { return g_pEngine->m_level->m_ui32NbSectors; }

// The inlined CBitArrayVar resize: the bit count, the old block freed, a new block of whole bytes.
void ResizeBits(CKSrvBeacon::CBitArrayVar* bits, uint32_t count) {
    uint8_t* old = bits->m_p8Bits;
    bits->m_ui32NbBit = count;
    if (old != nullptr) Mem_FreeAligned16(old);
    bits->m_p8Bits = static_cast<uint8_t*>(Mem_AllocAligned16(((bits->m_ui32NbBit - 1) >> 3) + 1));
}
}  // namespace

// The element constructor, inlined in CKSrvBeacon_Load's new[] loop (0x125880): the pointers and bit
// arrays cleared, in the original's order.
CKSrvBeacon::CKBeaconSector::CKBeaconSector() {
    m_bavPersistent.m_ui32NbBit = 0;
    m_bavPersistent.m_p8Bits = nullptr;
    m_bavMCPersistent.m_ui32NbBit = 0;
    m_bavMCPersistent.m_p8Bits = nullptr;
    m_pvVolatileDataIterator = nullptr;
    m_pi8IdToSets = nullptr;
    m_apBeaconKlusters = nullptr;
    m_pSectorBeaconSetsIterator = nullptr;
    m_aSectorBeaconSets = nullptr;
    m_pvVolatileData = nullptr;
    m_pi8IdToSetsIterator = nullptr;
}

// 0x001236a8 CKSrvBeacon_Construct (the same stores inlined in 0x124810 CKSrvBeacon_Create).
CKSrvBeacon::CKSrvBeacon() {
    m_vBeaconBundles.m_ui32NbElt = 1;
    m_vBeaconBundles.m_pBlock = nullptr;
    m_vBeaconBundles.m_ui32NbUsedElt = 0;
    m_ui32Priority = 0xbe;
    m_aBeaconSectors = nullptr;
    g_pSrvBeacon = this;
    Engine_SetSrvBeacon(this);
}

// 0x00123f30 CKSrvBeacon_Destroy: the bundle list freed, then every sector's blocks and the sector array.
void CKSrvBeacon::Destroy() {
    if (m_vBeaconBundles.m_pBlock != nullptr) {
        Mem_FreeAligned16(m_vBeaconBundles.m_pBlock);
        m_vBeaconBundles.m_pBlock = nullptr;
    }
    m_vBeaconBundles.m_ui32NbUsedElt = 0;
    m_vBeaconBundles.m_pBlock = nullptr;
    if (m_aBeaconSectors == nullptr) return;
    // Every sector from the last one down (the count is the new[] cookie: m_ui32NbSectors here).
    for (uint32_t i = m_ui32NbSectors; i != 0; --i) {
        CKBeaconSector& sector = m_aBeaconSectors[i - 1];
        if (sector.m_aSectorBeaconSets != nullptr) {
            ::operator delete[](sector.m_aSectorBeaconSets);  // OperatorDeleteArray (a cookie block)
            sector.m_pSectorBeaconSetsIterator = nullptr;
            sector.m_aSectorBeaconSets = nullptr;
        }
        if (sector.m_pvVolatileData != nullptr) {
            Mem_FreeAligned16(sector.m_pvVolatileData);
            sector.m_pvVolatileData = nullptr;
            sector.m_pvVolatileDataIterator = nullptr;
        }
        if (sector.m_pi8IdToSets != nullptr) {
            Mem_FreeAligned16(sector.m_pi8IdToSets);
            sector.m_pi8IdToSets = nullptr;
            sector.m_pi8IdToSetsIterator = nullptr;
        }
        if (sector.m_apBeaconKlusters != nullptr) {
            Mem_FreeAligned16(sector.m_apBeaconKlusters);
            sector.m_apBeaconKlusters = nullptr;
        }
        if (sector.m_bavPersistent.m_p8Bits != nullptr) {
            Mem_FreeAligned16(sector.m_bavPersistent.m_p8Bits);
            sector.m_bavPersistent.m_p8Bits = nullptr;
        }
        sector.m_bavPersistent.m_ui32NbBit = 0;
        // The inlined ~CKBeaconSector: the memory-card bits freed (the pointer kept), the persistent bits again.
        if (sector.m_bavMCPersistent.m_p8Bits != nullptr) Mem_FreeAligned16(sector.m_bavMCPersistent.m_p8Bits);
        if (sector.m_bavPersistent.m_p8Bits != nullptr) Mem_FreeAligned16(sector.m_bavPersistent.m_p8Bits);
    }
    delete[] m_aBeaconSectors;
    m_aBeaconSectors = nullptr;
}

// 0x00125598 CKSrvBeacon_Load. A level gives the bundles and the sectors; a memory-card restore
// (K_LEVEL_MEMCARD) the persistent bits of each saved sector.
int32_t CKSrvBeacon::Load(IKFile* file, int32_t type) {
    if (type == K_LEVEL_PLATEFORMS) {
        ReadU8(file, &m_ui8UpdateEachFrame);
        uint32_t count = 0;
        ReadU32LE(file, &count);
        if (count == 0) {  // a one-bundle block; the length stays as it is
            m_vBeaconBundles.m_ui32NbElt = 1;
            m_vBeaconBundles.m_pBlock = static_cast<CKBeaconBundle*>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(CKBeaconBundle))));
        } else {
            m_vBeaconBundles.m_ui32NbElt = count;
            m_vBeaconBundles.m_pBlock =
                static_cast<CKBeaconBundle*>(Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(CKBeaconBundle))));
            if (m_vBeaconBundles.m_ui32NbElt < count) {  // as in the original: cannot happen here
                uint32_t capacity = count + 1;
                if (capacity == 0) capacity = 1;
                m_vBeaconBundles.m_pBlock = static_cast<CKBeaconBundle*>(Mem_ReallocAligned16(
                    m_vBeaconBundles.m_pBlock, capacity * static_cast<uint32_t>(sizeof(CKBeaconBundle))));
                m_vBeaconBundles.m_ui32NbElt = capacity;
            }
            m_vBeaconBundles.m_ui32NbUsedElt = count;
            for (uint32_t i = 0; i < count; ++i) {
                ReadRaw(file, &m_vBeaconBundles.m_pBlock[i], 6);  // the six byte fields as stored
                IKFile_ReadRef(file, &m_vBeaconBundles.m_pBlock[i].m_pOwner);
            }
        }
        ReadU32LE(file, &m_ui32NbSectors);
        m_aBeaconSectors = new CKBeaconSector[m_ui32NbSectors];
        for (uint32_t i = m_ui32NbSectors; i != 0;) {  // from the last sector down
            --i;
            CKBeaconSector& sector = m_aBeaconSectors[i];
            ReadU32LE(file, &sector.m_ui32NbValidBeaconSets);
            ReadU32LE(file, &sector.m_ui32NbTotalBeaconSets);
            ReadU32LE(file, &sector.m_ui32BeaconsVolatileSize);
            ReadU32LE(file, &sector.m_ui32BeaconsPersistentSize);
            if (sector.m_ui32BeaconsPersistentSize != 0) {
                ResizeBits(&sector.m_bavPersistent, sector.m_ui32BeaconsPersistentSize);
                file->Read(sector.m_bavPersistent.m_p8Bits, ((sector.m_ui32BeaconsPersistentSize - 1) >> 3) + 1);
            }
            uint32_t klusters = 0;
            ReadU32LE(file, &klusters);
            if (klusters == 0) {
                sector.m_apBeaconKlusters = nullptr;
            } else {
                sector.m_apBeaconKlusters = static_cast<IKSerializable**>(
                    Mem_AllocAligned16(klusters * static_cast<uint32_t>(sizeof(IKSerializable*))));
                IKFile_ReadObjectRefArray(file, sector.m_apBeaconKlusters, klusters);
            }
        }
        return 1;
    }
    if (type == K_LEVEL_MEMCARD) {
        const uint32_t sectors = LevelSectorCount();
        for (uint32_t i = 0; i != sectors; ++i) {
            uint8_t saved = 0;
            ReadU8(file, &saved);
            if (saved == 0) continue;
            uint32_t bits = 0;
            ReadU32LE(file, &bits);
            ResizeBits(&m_aBeaconSectors[i].m_bavMCPersistent, bits);
            file->Read(m_aBeaconSectors[i].m_bavMCPersistent.m_p8Bits, ((bits - 1) >> 3) + 1);
        }
    }
    return 1;
}

// 0x001238b8 CKSrvBeacon_AllocBeaconData
void* CKSrvBeacon::AllocateBeaconSetBeacons(uint32_t size) {
    CKBeaconSector& sector = m_aBeaconSectors[g_pEngine->m_level->m_i32NumLoadingSector];
    uint8_t* data = static_cast<uint8_t*>(sector.m_pvVolatileDataIterator);
    sector.m_pvVolatileDataIterator = data + size;
    return data;
}

// 0x001239a8 CKSrvBeacon_AllocKlusterBings
void CKSrvBeacon::AllocateSectorBeaconSets(CKBeaconSet** sets, uint32_t nbValid, int8_t** idToSet, uint32_t nbTotal) {
    CKBeaconSector& sector = m_aBeaconSectors[g_pEngine->m_level->m_i32NumLoadingSector];
    if (sector.m_aSectorBeaconSets == nullptr) {
        const uint32_t count = sector.m_ui32NbValidBeaconSets;
        if (count == 0) {
            sector.m_pSectorBeaconSetsIterator = nullptr;
        } else {
            CKBeaconSet* block = new CKBeaconSet[count];  // OperatorNewArray(count * 0x1c + 4): a cookie block
            sector.m_pSectorBeaconSetsIterator = block;
            sector.m_aSectorBeaconSets = block;
        }
        if (sector.m_ui32BeaconsVolatileSize == 0) {
            sector.m_pvVolatileData = nullptr;
            sector.m_pvVolatileDataIterator = nullptr;
        } else {
            void* block = Mem_AllocAligned16(sector.m_ui32BeaconsVolatileSize);
            sector.m_pvVolatileData = block;
            sector.m_pvVolatileDataIterator = block;
        }
        if (sector.m_ui32NbTotalBeaconSets == 0) {
            sector.m_pi8IdToSets = nullptr;
            sector.m_pi8IdToSetsIterator = nullptr;
        } else {
            int8_t* block = static_cast<int8_t*>(Mem_AllocAligned16(sector.m_ui32NbTotalBeaconSets));
            sector.m_pi8IdToSets = block;
            sector.m_pi8IdToSetsIterator = block;
        }
    }
    CKBeaconSet* setIterator = static_cast<CKBeaconSet*>(sector.m_pSectorBeaconSetsIterator);
    *sets = setIterator;
    sector.m_pSectorBeaconSetsIterator = setIterator + nbValid;
    *idToSet = sector.m_pi8IdToSetsIterator;
    sector.m_pi8IdToSetsIterator += nbTotal;
}

// 0x001241b8 CKSrvBeacon_MessageProc
int32_t CKSrvBeacon::MessageProc(uint16_t message, void* data) {
    SKBeaconMsg* msg = static_cast<SKBeaconMsg*>(data);
    if (message == 0x1000) {
        // The save path: the same loops as 0x1001 with Write; each half-word goes out as two bytes, low first
        // (the PS3 reverses it with lhbrx; here the value is already in host order).
        IKFile* file = msg->m_pFile;
        const CKBeaconSet* set = msg->m_pBeaconSet;
        if (msg->m_tBeaconID == 5) {
            while (msg->m_ui32NbBeacons-- != 0) {  // ends at 0xffffffff, as the original's
                const uint8_t* beacon = msg->m_pvBeacon;
                ++msg->m_ai16Accessor[3];
                msg->m_pvBeacon = msg->m_pvBeacon + set->m_ui8VolatileSizeBytes;
                for (int i = 0; i < 4; ++i) file->Write(beacon + i * 2, 2);
            }
        } else if (msg->m_tBeaconID == 0x27) {
            while (msg->m_ui32NbBeacons-- != 0) {
                const uint8_t* beacon = msg->m_pvBeacon;
                ++msg->m_ai16Accessor[3];
                msg->m_pvBeacon = msg->m_pvBeacon + set->m_ui8VolatileSizeBytes;
                for (int i = 0; i < 3; ++i) file->Write(beacon + i * 2, 2);
                file->Write(beacon + 6, 2);
            }
        }
        return 0;
    }
    if (message != 0x1001) return 1;
    if (msg->m_tBeaconID == 5) {
        // BUG(original): the iterator advances by one beacon only, though all of them are read here.
        uint8_t* beacons = msg->m_pvBeacon;
        ++msg->m_ai16Accessor[3];
        msg->m_pvBeacon = beacons + msg->m_pBeaconSet->m_ui8VolatileSizeBytes;
        const uint32_t halves = msg->m_ui32NbBeacons * 4;
        msg->m_pFile->Read(beacons, msg->m_ui32NbBeacons << 3);
        uint16_t* values = reinterpret_cast<uint16_t*>(beacons);
        for (uint32_t i = 0; i < halves; ++i) {
            const uint8_t* b = reinterpret_cast<const uint8_t*>(&values[i]);
            values[i] = static_cast<uint16_t>(b[0] | (b[1] << 8));  // lhbrx: the file is little-endian
        }
    } else if (msg->m_tBeaconID == 0x27) {
        IKFile* file = msg->m_pFile;
        const CKBeaconSet* set = msg->m_pBeaconSet;
        while (msg->m_ui32NbBeacons-- != 0) {  // ends at 0xffffffff, as the original's
            uint8_t* beacon = msg->m_pvBeacon;
            ++msg->m_ai16Accessor[3];
            msg->m_pvBeacon = beacon + set->m_ui8VolatileSizeBytes;
            uint16_t* values = reinterpret_cast<uint16_t*>(beacon);
            ReadU16LE(file, &values[0]);  // one 6-byte read, three halves swapped
            ReadU16LE(file, &values[1]);
            ReadU16LE(file, &values[2]);
            ReadRaw(file, beacon + 6, 2);
        }
    }
    return 0;
}

// 0x001237b8 CKSrvBeacon_ReleaseKlusterData_maybe (the sets and id pointers are not used: the iterators
// only move back by the counts).
void CKSrvBeacon::FreeSectorBeaconSets(CKBeaconSet* /*sets*/, uint32_t nbValid, int8_t* /*idToSet*/, uint32_t nbTotal) {
    const int32_t index = g_pEngine->m_level->m_i32NumUnloadingSector;
    if (index == -2) return;
    CKBeaconSector& sector = m_aBeaconSectors[index];
    CKBeaconSet* first = static_cast<CKBeaconSet*>(sector.m_aSectorBeaconSets);
    CKBeaconSet* iterator = static_cast<CKBeaconSet*>(sector.m_pSectorBeaconSetsIterator) - nbValid;
    sector.m_pSectorBeaconSetsIterator = iterator;
    sector.m_pi8IdToSetsIterator -= nbTotal;
    if (first != iterator) return;
    if (first != nullptr) {
        delete[] first;  // OperatorDeleteArray(block - 4): the cookie block
        sector.m_aSectorBeaconSets = nullptr;
        sector.m_pSectorBeaconSetsIterator = nullptr;
    }
    if (sector.m_pvVolatileData != nullptr) {
        Mem_FreeAligned16(sector.m_pvVolatileData);
        sector.m_pvVolatileData = nullptr;
        sector.m_pvVolatileDataIterator = nullptr;
    }
    if (sector.m_pi8IdToSets != nullptr) {
        Mem_FreeAligned16(sector.m_pi8IdToSets);
        sector.m_pi8IdToSets = nullptr;
        sector.m_pi8IdToSetsIterator = nullptr;
    }
}

// 0x00124db8 CKSrvBeacon_SaveSectorBeaconBits_maybe (XXL2 StoreMCPersistentDatas): for a loaded sector, the
// persistent bits of the memory-card beacons (the bundles with m_bIsMcSerializable) copied from the
// sector's persistent bit array (+0x28) into its memory-card array (+0x30), set after set. The first call
// sizes and allocates that array (the sum of persistent bits of those sets); no memory-card beacon, no
// array. Gathering the sets of a beacon index threads them through CKBeaconSet::m_pNext (the last kluster
// first), as the original does.
void CKSrvBeacon::SaveSectorBeaconBits(int32_t sectorIndex) {
    CKSector* sector = static_cast<CKSector*>(g_pEngine->m_level->m_vpSectors.m_pBlock[sectorIndex]);
    if ((sector->m_ba16Properties & 1) == 0) return;
    CKBeaconSector& beaconSector = m_aBeaconSectors[sectorIndex];
    const uint32_t bundleCount = m_vBeaconBundles.m_ui32NbUsedElt;
    // The sets of one beacon index over the sector's klusters (null when it has none).
    auto gatherSets = [sector](uint8_t beaconIndex) -> CKBeaconSet* {
        CKBeaconSet* head = nullptr;
        for (CKBeaconKluster* kluster = static_cast<CKBeaconKluster*>(sector->m_lBeaconKlusterList); kluster != nullptr;
             kluster = kluster->m_pNext) {
            const int8_t setIndex = kluster->m_ai8IdToBeaconSet[beaconIndex];
            if (setIndex == -1) continue;
            CKBeaconSet* set = kluster->m_aBeaconSets + setIndex;
            set->m_pNext = head;
            head = set;
        }
        return head;
    };
    // The memory-card bundle the bundle `index`'s id names (the last bundle with that id), or null.
    auto memoryCardBundle = [this, bundleCount](uint32_t index) -> const CKBeaconBundle* {
        const uint8_t id = m_vBeaconBundles.m_pBlock[index].m_tBeaconID;
        for (uint32_t j = bundleCount; j != 0; --j) {
            const CKBeaconBundle& bundle = m_vBeaconBundles.m_pBlock[j - 1];
            if (bundle.m_tBeaconID != id) continue;
            return bundle.m_bIsMcSerializable != 0 ? &bundle : nullptr;
        }
        return nullptr;
    };
    if (beaconSector.m_bavMCPersistent.m_p8Bits == nullptr) {
        if (bundleCount == 0) return;
        uint32_t totalBits = 0;
        for (uint32_t i = 0; i < bundleCount; ++i) {
            const CKBeaconBundle* bundle = memoryCardBundle(i);
            if (bundle == nullptr) continue;
            const uint8_t beaconIndex = bundle->m_ui8BeaconIndex;
            if (beaconIndex == 0xff || sector->m_lBeaconKlusterList == nullptr) continue;
            for (CKBeaconSet* set = gatherSets(beaconIndex); set != nullptr; set = set->m_pNext) {
                totalBits += static_cast<uint32_t>(set->m_ui8PersistentSizeBits) * set->m_ui32NbBeacons;
            }
        }
        if (totalBits == 0) return;
        beaconSector.m_bavMCPersistent.m_ui32NbBit = totalBits;
        beaconSector.m_bavMCPersistent.m_p8Bits = static_cast<uint8_t*>(Mem_AllocAligned16(((totalBits - 1) >> 3) + 1));
    }
    if (bundleCount == 0) return;
    uint32_t cursor = 0;  // the next bit of the memory-card array
    for (uint32_t i = 0; i < bundleCount; ++i) {
        const CKBeaconBundle* bundle = memoryCardBundle(i);
        if (bundle == nullptr) continue;
        const uint8_t beaconIndex = bundle->m_ui8BeaconIndex;
        if (beaconIndex == 0xff || sector->m_lBeaconKlusterList == nullptr) continue;
        for (CKBeaconSet* set = gatherSets(beaconIndex); set != nullptr; set = set->m_pNext) {
            uint32_t source = set->m_aui16Accessor[3];  // the set's first persistent bit
            const int32_t bits = static_cast<int32_t>(set->m_ui8PersistentSizeBits) * static_cast<int32_t>(set->m_ui32NbBeacons);
            for (int32_t k = 0; k < bits; ++k) {
                uint8_t* destination = beaconSector.m_bavMCPersistent.m_p8Bits + (cursor >> 3);
                const uint32_t destinationBit = cursor & 7;
                const uint8_t sourceByte = beaconSector.m_bavPersistent.m_p8Bits[source >> 3];
                *destination = static_cast<uint8_t>(*destination & ~(1u << destinationBit));
                *destination = static_cast<uint8_t>(*destination | (((sourceByte >> (source & 7)) & 1u) << destinationBit));
                ++cursor;
                ++source;
            }
        }
    }
}

// 0x001248b8 CKSrvBeacon_RestoreSectorBeaconBits_maybe (XXL2 RestoreMCPersistentDatas): SaveSectorBeaconBits the
// other way round (no "sector loaded" test, no sizing: without a memory-card array there is nothing to restore).
void CKSrvBeacon::RestoreSectorBeaconBits(int32_t sectorIndex) {
    CKBeaconSector& beaconSector = m_aBeaconSectors[sectorIndex];
    if (beaconSector.m_bavMCPersistent.m_p8Bits == nullptr) return;
    CKSector* sector = static_cast<CKSector*>(g_pEngine->m_level->m_vpSectors.m_pBlock[sectorIndex]);
    const uint32_t bundleCount = m_vBeaconBundles.m_ui32NbUsedElt;
    if (bundleCount == 0) return;
    uint32_t cursor = 0;  // the next bit of the memory-card array
    for (uint32_t i = 0; i < bundleCount; ++i) {
        // The memory-card bundle the bundle i's id names (the last bundle with that id), or none.
        const uint8_t id = m_vBeaconBundles.m_pBlock[i].m_tBeaconID;
        const CKBeaconBundle* bundle = nullptr;
        for (uint32_t j = bundleCount; j != 0; --j) {
            const CKBeaconBundle& candidate = m_vBeaconBundles.m_pBlock[j - 1];
            if (candidate.m_tBeaconID != id) continue;
            bundle = &candidate;
            break;
        }
        if (bundle == nullptr || bundle->m_bIsMcSerializable == 0) continue;
        const uint8_t beaconIndex = bundle->m_ui8BeaconIndex;
        if (beaconIndex == 0xff || sector->m_lBeaconKlusterList == nullptr) continue;
        // The sets of that beacon index over the sector's klusters, threaded through m_pNext (last kluster first).
        CKBeaconSet* head = nullptr;
        for (CKBeaconKluster* kluster = static_cast<CKBeaconKluster*>(sector->m_lBeaconKlusterList); kluster != nullptr;
             kluster = kluster->m_pNext) {
            const int8_t setIndex = kluster->m_ai8IdToBeaconSet[beaconIndex];
            if (setIndex == -1) continue;
            CKBeaconSet* set = kluster->m_aBeaconSets + setIndex;
            set->m_pNext = head;
            head = set;
        }
        for (CKBeaconSet* set = head; set != nullptr; set = set->m_pNext) {
            uint32_t destination = set->m_aui16Accessor[3];  // the set's first persistent bit
            const int32_t bits = static_cast<int32_t>(set->m_ui8PersistentSizeBits) * static_cast<int32_t>(set->m_ui32NbBeacons);
            for (int32_t k = 0; k < bits; ++k) {
                uint8_t* destinationByte = beaconSector.m_bavPersistent.m_p8Bits + (destination >> 3);
                const uint32_t destinationBit = destination & 7;
                const uint8_t sourceByte = beaconSector.m_bavMCPersistent.m_p8Bits[cursor >> 3];
                *destinationByte = static_cast<uint8_t>(*destinationByte & ~(1u << destinationBit));
                *destinationByte = static_cast<uint8_t>(*destinationByte | (((sourceByte >> (cursor & 7)) & 1u) << destinationBit));
                ++cursor;
                ++destination;
            }
        }
    }
}

// 0x00124b88 CKSrvBeacon_SectorLoaded
void CKSrvBeacon::SectorLoaded(int32_t sector) {
    const uint16_t state = static_cast<CKSector*>(g_pEngine->m_level->m_vpSectors.m_pBlock[sector])->m_ba16Properties;
    uint32_t message;
    if (((state >> 1) & 1) == 0) {
        if (((state >> 2) & 1) == 0) return;
        message = 0x1003;
    } else {
        message = 0x1002;
        RestoreSectorBeaconBits(sector);
    }
    for (uint32_t i = 0; i < m_vBeaconBundles.m_ui32NbUsedElt; ++i) {
        const CKBeaconBundle& bundle = m_vBeaconBundles.m_pBlock[i];
        if (bundle.m_pOwner != nullptr) {
            const uint32_t data = (static_cast<uint32_t>(bundle.m_tBeaconID) << 8) | (static_cast<uint32_t>(sector) & 0xff);
            bundle.m_pOwner->MessageProc(static_cast<uint16_t>(message), reinterpret_cast<void*>(static_cast<uintptr_t>(data)));
        }
    }
}

// The beacon an accessor names (see the header).
const uint8_t* CKSrvBeacon::GetBeaconData(const uint16_t* accessor) const {
    const CKBeaconSector& sector = m_aBeaconSectors[accessor[0]];
    if (sector.m_apBeaconKlusters == nullptr) return nullptr;
    const CKBeaconKluster* kluster = static_cast<const CKBeaconKluster*>(sector.m_apBeaconKlusters[accessor[1]]);
    const int8_t setIndex = kluster->m_ai8IdToBeaconSet[accessor[2]];
    if (setIndex == -1) return nullptr;
    const CKBeaconSet* set = &kluster->m_aBeaconSets[setIndex];
    return static_cast<const uint8_t*>(set->m_aBeacons) + static_cast<uint32_t>(accessor[3]) * set->m_ui8VolatileSizeBytes;
}
