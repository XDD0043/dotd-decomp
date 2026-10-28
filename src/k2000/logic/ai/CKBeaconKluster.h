// CKBeaconKluster.h - a cluster of beacon sets in a sector (key 0x124c, vtable 0xb13fb8, size 0x28).
// Original unit: CKBeaconKluster.cpp. XXL2: K/KCore/Level/CKBeaconKluster.h (CSBaseNode<CKBeaconKluster*>,
// m_BSphere, m_aBeaconSets, m_ai8IdToBeaconSet, m_ui16NbValidSets, m_ui16NbTotalSets; the same Load,
// except that DotD reads five floats where XXL2 reads its CBSphere).
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"
#include "k2000/services/CKSrvBeacon.h"

class CKBeaconKluster : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x49)
    DOTD_DECLARE_FACTORIES(CKBeaconKluster)

    CKBeaconKluster() { m_pNext = nullptr; }  // inlined in 0x0002ea78 CKBeaconKluster_Create
    ~CKBeaconKluster() override {}

    // vt+0x10 0x0002e970 CKBeaconKluster_Destroy: the beacon sets given back to the beacon service.
    void Destroy() override;

    // vt+0x2c 0x0002eb60 CKBeaconKluster_Load: the beacon sets come from the beacon service; each set's
    // owner reads its beacons from the file (message 0x1001).
    int32_t Load(IKFile* file, int32_t type) override;

    CKBeaconKluster* m_pNext;                    // +0x04 XXL2 CSBaseNode<CKBeaconKluster*>::m_pNext (a reference)
    float m_afBounds[5];                         // +0x08 XXL2 m_BSphere's place (DotD: five floats)
    CKSrvBeacon::CKBeaconSet* m_aBeaconSets;     // +0x1c XXL2 m_aBeaconSets
    int8_t* m_ai8IdToBeaconSet;                  // +0x20 XXL2 m_ai8IdToBeaconSet (-1: no set)
    uint16_t m_ui16NbValidSets;                  // +0x24 XXL2 m_ui16NbValidSets
    uint16_t m_ui16NbTotalSets;                  // +0x26 XXL2 m_ui16NbTotalSets (read first)
};
static_assert(CKBeaconKluster::kClassKey == 0x124c, "key");
DOTD_ASSERT_SIZE(CKBeaconKluster, 0x28);
DOTD_ASSERT_OFFSET(CKBeaconKluster, m_pNext, 0x04);
DOTD_ASSERT_OFFSET(CKBeaconKluster, m_afBounds, 0x08);
DOTD_ASSERT_OFFSET(CKBeaconKluster, m_aBeaconSets, 0x1c);
DOTD_ASSERT_OFFSET(CKBeaconKluster, m_ai8IdToBeaconSet, 0x20);
DOTD_ASSERT_OFFSET(CKBeaconKluster, m_ui16NbValidSets, 0x24);
DOTD_ASSERT_OFFSET(CKBeaconKluster, m_ui16NbTotalSets, 0x26);
