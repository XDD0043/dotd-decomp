// CollisionTest.h - the volume-against-volume tests of CKSrvCollision's matrix (m_IntersectionMatrix[shape1][shape2],
// IKBoundingVolume::EShape). Original units: CollisionTest.cpp (0x19d020-0x19f3e8, with the swapping wrappers out of line
// at 0x9aa710..), Collision.cpp (0x19f3e8, the OBB pair) and CollisionTest_2.cpp (0x19fcf8-0x1a14e8). Each returns 1 when
// the volumes touch and fills the contact set (CContactSet: the response bits in the low nibble of m_Infos, the time of
// contact, the interpenetration, the normal from volume 1 to volume 2 and the world contact point).
#pragma once
#include <cstdint>

class IKBoundingVolume;
struct CContactSet;

namespace collision_test {

// CollisionTest.cpp
uint8_t AABoxVsAABox(IKBoundingVolume* a, IKBoundingVolume* b, CContactSet* set);            // 0x0019d020
uint8_t SweptAABoxVsSweptAABox(IKBoundingVolume* a, IKBoundingVolume* b, CContactSet* set);  // 0x0019d268
uint8_t AABoxVsSweptAABox(IKBoundingVolume* a, IKBoundingVolume* b, CContactSet* set);       // 0x0019d938
uint8_t AABoxVsSphere(IKBoundingVolume* a, IKBoundingVolume* b, CContactSet* set);           // 0x0019dff0
uint8_t AABoxVsSweptSphere(IKBoundingVolume* a, IKBoundingVolume* b, CContactSet* set);      // 0x0019e450
uint8_t CylinderVsCylinder(IKBoundingVolume* a, IKBoundingVolume* b, CContactSet* set);      // 0x0019e950
uint8_t CylinderVsSphere(IKBoundingVolume* a, IKBoundingVolume* b, CContactSet* set);        // 0x0019eaa0
uint8_t OBBVsAABox(IKBoundingVolume* a, IKBoundingVolume* b, CContactSet* set);              // 0x0019ee08
// The swapping wrappers (the test with the volumes exchanged, the normal negated when they touch).
uint8_t SweptAABoxVsAABoxSwapped(IKBoundingVolume* a, IKBoundingVolume* b, CContactSet* set);  // 0x009aa710
uint8_t SphereVsCylinder(IKBoundingVolume* a, IKBoundingVolume* b, CContactSet* set);          // 0x009aa790
uint8_t SweptSphereVsSphere(IKBoundingVolume* a, IKBoundingVolume* b, CContactSet* set);       // 0x009aa810
uint8_t SweptSphereVsBox(IKBoundingVolume* a, IKBoundingVolume* b, CContactSet* set);          // 0x009aa890
uint8_t SphereVsBox(IKBoundingVolume* a, IKBoundingVolume* b, CContactSet* set);               // 0x009aa910
uint8_t AABoxVsOBB(IKBoundingVolume* a, IKBoundingVolume* b, CContactSet* set);                // 0x009aa990
uint8_t SweptSphereVsAABox(IKBoundingVolume* a, IKBoundingVolume* b, CContactSet* set);        // 0x009aaa10
uint8_t SphereVsAABox(IKBoundingVolume* a, IKBoundingVolume* b, CContactSet* set);             // 0x009aaa90
// Collision.cpp
uint8_t OBBVsOBB(IKBoundingVolume* a, IKBoundingVolume* b, CContactSet* set);  // 0x0019f3e8
// CollisionTest_2.cpp
uint8_t BoxVsSphere(IKBoundingVolume* a, IKBoundingVolume* b, CContactSet* set);               // 0x0019fcf8
uint8_t BoxVsSweptSphere(IKBoundingVolume* a, IKBoundingVolume* b, CContactSet* set);          // 0x001a0238
uint8_t SphereVsSweptSphere(IKBoundingVolume* a, IKBoundingVolume* b, CContactSet* set);       // 0x001a0868
uint8_t SphereVsSphere(IKBoundingVolume* a, IKBoundingVolume* b, CContactSet* set);            // 0x001a0d40
uint8_t SweptSphereVsSweptSphere(IKBoundingVolume* a, IKBoundingVolume* b, CContactSet* set);  // 0x001a0f90

}  // namespace collision_test
