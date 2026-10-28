// CKSrvCollision.cpp - reconstructed original translation unit 0x191b00-0x19ce30 (GAME_TOC1, main_toc1), 49 functions, 39 live.
// Primary class: CKSrvCollision  key 0x81  category Service  size 0x3ab8  vtable 0xb1bf30
// Other owners: CollisionTest (4), GroundProbePoints (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x191b00  RegisterCKSrvCollisionClass
//   [ ] 0x191b78  _GLOBAL__I_191b78
//   [ ] 0x191b88  CKSrvCollision_PostLoad
//   [x] 0x191bb0  CKSrvCollision_DeleteArray
//   [x] 0x191c50  CKSrvCollision_InitializeService
//   [x] 0x191e60  CKSrvCollision_Construct
//   [x] 0x191f60  CKSrvCollision_FindNonRecreableInstances
//   [ ] 0x191fb8  CKSrvCollision_RecursiveRegistration
//   [x] 0x192090  CKSrvCollision_EnableVolume
//   [x] 0x1920e8  CKSrvCollision_DisableVolume
//   [x] 0x192138  CKSrvCollision_Destroy
//   [x] 0x192370  CKSrvCollision_DestroyService
//   [ ] 0x192410  CKSrvCollision_Construct_2
//   [x] 0x192510  CKSrvCollision_UpdateInitialize
//   [ ] 0x192648  FUN_00192648  [dead]
//   [x] 0x192a70  CKSrvCollision_AcquireDynSphere_maybe
//   [x] 0x192b80  CKSrvCollision_AddVolume_maybe
//   [x] 0x192bc0  CKSrvCollision_RemoveVolume_maybe
//   [ ] 0x192c00  CKSrvCollision_SaveObjectSlots_maybe
//   [x] 0x192e20  CKSrvCollision_ActivateTest_maybe
//   [ ] 0x1931a0  FUN_001931a0  [dead]
//   [x] 0x193298  CKSrvCollision_ActivateTestsOfEnabledVolumes_maybe
//   [ ] 0x193488  CKSrvCollision_Destructor_2  [dead]
//   [ ] 0x193520  FUN_00193520  [dead]
//   [x] 0x193638  CKSrvCollision_ProcessDynamicVolumes_maybe
//   [x] 0x193fe0  CKSrvCollision_ProcessPairs_maybe
//   [x] 0x194440  UpdateCKSrvCollision
//   [ ] 0x1944e8  CKSrvCollision_DeletingDestructor
//   [ ] 0x1945a8  CKSrvCollision_Save
//   [x] 0x1949d8  CKSrvCollision_Create
//   [x] 0x194ae8  CKSrvCollision_CreateArray
//   [x] 0x194c88  CKSrvCollision_Load
//   [ ] 0x195620  CKSrvCollision_Destructor
//   [x] 0x1956b8  CKSrvCollision_ProbeGroundInSectorList_maybe
//   [ ] 0x195968  CollisionTest_CoplanarTriangleVsTriangle_maybe  [dead]
//   [ ] 0x196420  CKSrvCollision_ClearQueryStampsInActiveSectors_maybe  [dead]
//   [x] 0x196540  GroundProbePoints_maybe
//   [ ] 0x196700  CollisionTest_TriangleVsTriangle_NoDiv_maybe  [dead]
//   [ ] 0x196db0  CollisionTest_TriangleVsTriangle_maybe  [dead]
//   [x] 0x197478  CKSrvCollision_GatherWallsAlongSegment_maybe
//   [x] 0x197af8  CKSrvCollision_RaycastMeshes_maybe
//   [x] 0x198438  CKSrvCollision_RaycastWalls_maybe
//   [x] 0x198808  CKSrvCollision_CollectSweptWallCandidates_maybe
//   [x] 0x198ed0  CKSrvCollision_SweepCylinderAgainstWalls_maybe
//   [x] 0x1996b0  CKSrvCollision_ResolveWallSegmentMovement_maybe
//   [x] 0x19a158  CKSrvCollision_SweepCircleAgainstWallSegments_maybe
//   [ ] 0x19a910  CKSrvCollision_CollectAndSweepWallSegments_maybe  [dead]
//   [x] 0x19aa68  CKSrvCollision_ResolveSweptCylinderWalls_maybe
//   [ ] 0x19c208  CollisionTest_TriangleVsTriangleWithSegment_maybe  [dead]
//
//   [ ] 0x9aa6c8  CKSrvCollision_IsKindOfClass  [inline]
//   [ ] 0x9aa700  CKSrvCollision_GetClassType  [inline]
//   [ ] 0x9aa708  CKSrvCollision_GetClassID  [inline]
#include "k2000/services/CKSrvCollision.h"

#include <cmath>

#include "Renderware/rwcore/RwCamera.h"
#include "crt/ppc_ops.h"
#include "k2000/core/Stub.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKLevel.h"
#include "k2000/logic/CKSector.h"
#include "k2000/logic/physics/CGround.h"
#include "k2000/logic/render/CKMeshKluster.h"
#include "k2000/misc/ClassManager.h"
#include "k2000/misc/CKGameLoop.h"
#include "k2000/math/CBBox.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/Mat4.h"
#include "k2000/physics/CollisionTest.h"
#include "k2000/scenegraph/CKDynamicBoundingSphere.h"
#include "k2000/scenegraph/IKBoundingVolume.h"
#include "k2000/system/IKTime.h"

float* g_pfDeltaTime = nullptr;                 // 0x00cea8ac
CContactSet* g_aContactSet = nullptr;           // 0x00cea8b0
CProjectile* g_aProjectile = nullptr;           // 0x00cea8b4
CProjectileTarget* g_aProjectileTarget = nullptr;  // 0x00cea8b8

namespace {
// One Read of count halfwords, then every halfword byte-swapped in place (lhbrx/sth).
void ReadHalvesLE(IKFile* file, uint16_t* halves, uint32_t count) {
    uint8_t* bytes = reinterpret_cast<uint8_t*>(halves);
    file->Read(bytes, count * 2);
    for (uint32_t i = 0; i < count; ++i) {
        const uint8_t* b = bytes + 2 * i;
        halves[i] = static_cast<uint16_t>(b[0] | (b[1] << 8));
    }
}
}  // namespace

// The CCollidingLife constructor (the stores of m_BoundWarned in the service's constructor and of
// CKSrvCollision_Load's new[] loop 0x1955e8, in that order).
CCollidingLife::CCollidingLife() {
    m_pNext = nullptr;
    m_tHead = nullptr;
    m_pElementToCall = nullptr;
}

// Inlined in CKSrvCollision_Load's new[] loop (0x195544). The two bitfield stores clear bit 2, then
// bit 3 of m_ba16Infos (rlwinm pairs on the PS3's big-endian bitfields).
CContactToTest::CContactToTest() {
    m_apBoundingVolume[0] = nullptr;
    m_apBoundingVolume[1] = nullptr;
    m_ui16CollidingLifeIndex[0] = 0xffff;
    m_ba16Infos = static_cast<uint16_t>(m_ba16Infos & ~0x4u);
    m_ui16CollidingLifeIndex[1] = 0xffff;
    m_ba16Infos = static_cast<uint16_t>(m_ba16Infos & ~0x8u);
    m_pMultiUse = nullptr;
    m_ui8ContactSetIndex = 0xc9;
    m_ui8Priority = 0;
    m_apSameStateNext[0] = nullptr;
    m_apSameStateNext[1] = nullptr;
}

// Inlined in 0x001949d8 CKSrvCollision_Create (0x191e60 CKSrvCollision_Construct has the same
// stores). The member arrays (the projectile list heads, m_BoundWarned, the 200 CCollision and the 200
// CProjectileCollision with their ICollision part) are constructed by their own constructors first;
// the original runs the same stores in member order.
CKSrvCollision::CKSrvCollision() {
    m_AwakeList = nullptr;
    m_AsleepList = nullptr;
    m_WarnedCollidingLivesList = nullptr;
    m_ui32Priority = 0xd2;
    Engine_SetSrvCollision(this);
}

// 0x00191f60 CKSrvCollision_FindNonRecreableInstances
uint8_t CKSrvCollision::FindNonRecreableInstances(int32_t category, uint32_t id, uint32_t count, void* out) {
    if (category != kCategoryNode || id != 6 || count != kProjectileCount) return 0;
    IKSerializable** array = *static_cast<IKSerializable***>(out);
    for (uint32_t i = 0; i < kProjectileCount; ++i) array[i] = m_aProjectile[i].m_pBoundingVolume;
    return 1;
}

// 0x00191c50 CKSrvCollision_InitializeService, in the original's order: the 36 tests first (CollisionTest_* OPDs),
// m_aPotentialEdge (the pointer held by the global 0x00c50d30) last.
int32_t CKSrvCollision::InitializeService() {
    using namespace collision_test;
    static const CollisionTestFn kTests[6][6] = {
        {SphereVsSphere, SphereVsBox, SphereVsSweptSphere, SphereVsAABox, SphereVsAABox, SphereVsCylinder},
        {BoxVsSphere, OBBVsOBB, BoxVsSweptSphere, OBBVsAABox, OBBVsAABox, SphereVsCylinder},
        {SweptSphereVsSphere, SweptSphereVsBox, SweptSphereVsSweptSphere, SweptSphereVsAABox, SweptSphereVsAABox,
         SphereVsCylinder},
        {AABoxVsSphere, AABoxVsOBB, AABoxVsSweptSphere, AABoxVsAABox, AABoxVsSweptAABox, SphereVsCylinder},
        {AABoxVsSphere, AABoxVsOBB, AABoxVsSweptSphere, SweptAABoxVsAABoxSwapped, SweptAABoxVsSweptAABox,
         SphereVsCylinder},
        {CylinderVsSphere, CylinderVsSphere, CylinderVsSphere, CylinderVsSphere, CylinderVsSphere, CylinderVsCylinder},
    };
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 6; ++j) m_IntersectionMatrix[i][j] = kTests[i][j];
    }
    m_fDeltaTime = 0.0f;
    m_aProjectileTarget = nullptr;
    m_ui16RayID = 0;
    m_Infos = 0;
    m_aContactToTest = nullptr;
    m_aCollidingLife = nullptr;
    g_pfDeltaTime = &m_fDeltaTime;
    g_aContactSet = m_aContactSet;
    g_aProjectile = m_aProjectile;
    g_aProjectileTarget = m_aProjectileTarget;
    m_BoundWarned.m_pNext = m_WarnedCollidingLivesList;  // AddHead
    m_WarnedCollidingLivesList = &m_BoundWarned;
    m_ui8NbProjectilesWarned = 0;
    m_ui32NbBVListingCollisionRes = 0;
    m_ui16NbTargetsWarned = 0;
    // The 50 projectile volumes. The original passes no size and steps by the PS3 sizeof (0x50); here
    // the stride is the native one the class manager returns.
    uint16_t stride = 0;
    m_aProjectileBoundingVolume = static_cast<IKSerializable*>(
        g_pEngine->m_classManager->CreateObjectArray(kCategoryNode, 6, kProjectileCount, &stride));
    for (uint32_t i = 0; i < kProjectileCount; ++i) {
        m_aProjectile[i].m_pBoundingVolume = reinterpret_cast<IKSerializable*>(
            reinterpret_cast<uint8_t*>(m_aProjectileBoundingVolume) + static_cast<uint32_t>(stride) * i);
    }
    m_aPotentialEdge = g_pScratchBuffer16k;  // the last store: the pointer held by the global 0x00c50d30
    return 1;
}

// 0x00192138 CKSrvCollision_Destroy: the projectile targets' and projectiles' collision lists cleared, the target and contact arrays
// freed, the warned lives unlinked, the colliding lives freed, the listed volumes' collision lists cleared.
void CKSrvCollision::Destroy() {
    for (uint32_t i = 0; i < m_ui16NbProjectileTargets; ++i) m_aProjectileTarget[i].m_tHead = nullptr;
    for (uint32_t i = 0; i < m_ui8NbProjectileUsed; ++i) m_aProjectile[i].m_tHead = nullptr;
    if (m_aProjectileTarget != nullptr) {
        delete[] m_aProjectileTarget;
        m_aProjectileTarget = nullptr;
    }
    m_AsleepList = nullptr;
    m_AwakeList = nullptr;
    if (m_aContactToTest != nullptr) {
        delete[] m_aContactToTest;
        m_aContactToTest = nullptr;
    }
    // The warned lives up to the bound: each life's collision list unlinked, then the life taken off.
    while (m_WarnedCollidingLivesList != &m_BoundWarned) {
        CCollidingLife* life = m_WarnedCollidingLivesList;
        for (ICollision* collision = life->m_tHead; collision != nullptr;) {
            ICollision* next = collision->m_pNext;
            collision->m_pNext = nullptr;
            collision = next;
        }
        life->m_tHead = nullptr;
        // BUG(original): a list that ends without the bound would read through null here (it always ends
        // with m_BoundWarned).
        CCollidingLife* next = life->m_pNext;
        if (next == nullptr) {
            m_WarnedCollidingLivesList = nullptr;
            continue;
        }
        life->m_pNext = nullptr;
        m_WarnedCollidingLivesList = next;
    }
    if (m_aCollidingLife != nullptr) {
        for (uint32_t i = 0; i < m_ui16NbCollidingLife; ++i) m_aCollidingLife[i].m_tHead = nullptr;
        if (m_aCollidingLife != nullptr) delete[] m_aCollidingLife;
        m_aCollidingLife = nullptr;
    }
    for (uint32_t i = 0; i < m_ui32NbBVListingCollisionRes; ++i) {
        static_cast<IKBoundingVolume*>(m_apBVListingCollisionRes[i])->m_CollisionResList = nullptr;
    }
    m_ui32NbBVListingCollisionRes = 0;
}

// 0x00194c88 CKSrvCollision_Load. No type test.
int32_t CKSrvCollision::Load(IKFile* file, int32_t /*type*/) {
    ReadU16LE(file, &m_ui16NbProjectileTargets);
    ReadU8(file, &m_ui8NbProjectileUsed);
    for (uint32_t i = 0; i < kProjectileCount; ++i) {
        IKFile_ReadRef(file, &m_aProjectile[i].m_pBoundingVolume);
        m_aProjectile[i].m_tHead = nullptr;
    }
    if (m_ui16NbProjectileTargets == 0) {
        m_aProjectileTarget = nullptr;
    } else {
        m_aProjectileTarget = new CProjectileTarget[m_ui16NbProjectileTargets];
        for (uint32_t i = 0; i < m_ui16NbProjectileTargets; ++i) {
            CProjectileTarget& target = m_aProjectileTarget[i];
            ReadU8(file, &target.m_ui8NbBoundingVolumes);
            IKFile_ReadObjectRefArray(file, target.m_apBoundingVolume, target.m_ui8NbBoundingVolumes);
            target.m_tHead = nullptr;
        }
    }
    m_Infos = 0;
    ReadU16LE(file, &m_ui16NbCollidingLife);
    ReadU16LE(file, &m_ui16NbContactToTest);
    if (m_ui16NbCollidingLife != 0) m_aCollidingLife = new CCollidingLife[m_ui16NbCollidingLife];
    if (m_ui16NbContactToTest != 0) m_aContactToTest = new CContactToTest[m_ui16NbContactToTest];
    for (uint32_t i = 0; i < m_ui16NbCollidingLife; ++i) {
        IKFile_ReadRef(file, &m_aCollidingLife[i].m_pElementToCall);
        m_aCollidingLife[i].m_pNext = nullptr;
        m_aCollidingLife[i].m_tHead = nullptr;
    }
    for (uint32_t i = 0; i < m_ui16NbContactToTest; ++i) {
        CContactToTest& contact = m_aContactToTest[i];
        ReadU16LE(file, &contact.m_ba16Infos);
        IKFile_ReadRef(file, &contact.m_apBoundingVolume[0]);
        IKFile_ReadRef(file, &contact.m_apBoundingVolume[1]);
        ReadU16LE(file, &contact.m_ui16CollidingLifeIndex[0]);
        ReadU16LE(file, &contact.m_ui16CollidingLifeIndex[1]);
        ReadU8(file, &contact.m_ui8Priority);
        uint16_t links[3];
        ReadHalvesLE(file, links, 3);  // one 6-byte read: three contact indices, 0xffff for none
        contact.m_apSameStateNext[0] = links[0] == 0xffff ? nullptr : &m_aContactToTest[links[0]];
        contact.m_apSameStateNext[1] = links[1] == 0xffff ? nullptr : &m_aContactToTest[links[1]];
        contact.m_pMultiUse = links[2] == 0xffff ? nullptr : &m_aContactToTest[links[2]];
    }
    uint16_t heads[2];
    ReadHalvesLE(file, heads, 2);  // one 4-byte read: the heads of the asleep and awake lists (in that order: 0x1952c0)
    m_AsleepList = heads[0] == 0xffff ? nullptr : &m_aContactToTest[heads[0]];
    m_AwakeList = heads[1] == 0xffff ? nullptr : &m_aContactToTest[heads[1]];
    m_fDeltaTime = 0.0f;
    g_pfDeltaTime = &m_fDeltaTime;
    g_aContactSet = m_aContactSet;
    g_aProjectile = m_aProjectile;
    g_aProjectileTarget = m_aProjectileTarget;
    m_Infos = (m_Infos & ~0x2u) | 0x2u;  // two one-bit fields set (XXL2: m_Infos |= 3)
    m_Infos = (m_Infos & ~0x1u) | 0x1u;
    return 1;
}

// 0x00192090 CKSrvCollision_EnableVolume
void CKSrvCollision::EnableVolume(IKBoundingVolume* volume) {
    if ((volume->m_ba8Infos & 1) == 0) {
        volume->m_ba8Infos = static_cast<uint8_t>((volume->m_ba8Infos & 0xfe) | 1);
        m_Infos = (m_Infos & 0xfffffffeu) | 1u;
    }
    volume->m_ba8Infos = static_cast<uint8_t>((volume->m_ba8Infos & 0xfb) | 4);
}

// 0x001920e8 CKSrvCollision_DisableVolume
void CKSrvCollision::DisableVolume(IKBoundingVolume* volume) {
    if ((volume->m_ba8Infos & 1) != 0) {
        volume->m_ba8Infos = static_cast<uint8_t>(volume->m_ba8Infos & 0xfe);
        m_Infos = (m_Infos & 0xfffffffdu) | 2u;
    }
    volume->m_ba8Infos = static_cast<uint8_t>(volume->m_ba8Infos & 0xfb);
}

// 0x00192b80 CKSrvCollision_AddVolume_maybe: a volume that is not registered yet gets bit 0 of its infos set and the
// service's m_Infos bit 0 (a volume was added) set.
void CKSrvCollision::AddVolume(IKBoundingVolume* volume) {
    if ((volume->m_ba8Infos & 1u) != 0) return;
    volume->m_ba8Infos = static_cast<uint8_t>((volume->m_ba8Infos & 0xfeu) | 1u);
    m_Infos = (m_Infos & 0xfffffffeu) | 1u;
}

// The contact-to-test lists (XXL2 TSPriorityList / TSNodeList, by hand in the original): a contact's next in its
// list (+0x0c), the next of another priority in the awake list (+0x10) and the link +0x14 (the partner of a
// multi-use contact, or the previous priority head in the awake list).
#define NEXT(c) ((c)->m_apSameStateNext[0])
#define SKIP(c) ((c)->m_apSameStateNext[1])
#define MULTI(c) ((c)->m_pMultiUse)
namespace {
inline uint8_t VolumeInfos(const CContactToTest* contact, int side) {
    return static_cast<IKBoundingVolume*>(contact->m_apBoundingVolume[side])->m_ba8Infos;
}
// The awake bit of the contact's infos (bit 4) cleared or set; the other bits kept (the original's rlwinm pair).
inline void SetAwake(CContactToTest* contact, bool awake) {
    contact->m_ba16Infos = static_cast<uint16_t>((contact->m_ba16Infos & ~0x10u) | (awake ? 0x10u : 0u));
}
}  // namespace


namespace {
// The awake list's insertion by priority (the inlined part of ActivateTest): after the last contact whose priority
// (+0x1b) is higher; `insertedLink` is what the next contact's +0x14 becomes (null for a plain contact, the contact
// itself for the head of a multi-use group). Returns the contact it was put after (null: the head).
CContactToTest* InsertByPriority(CContactToTest** list, CContactToTest* contact, bool linkSelf) {
    CContactToTest* after = nullptr;
    CContactToTest* head = *list;
    if (head == nullptr || !(contact->m_ui8Priority < head->m_ui8Priority)) {
        NEXT(contact) = *list;
        *list = contact;
    } else {
        CContactToTest* node = head;
        after = head;
        CContactToTest* next = NEXT(node);
        while (next != nullptr && contact->m_ui8Priority < next->m_ui8Priority) {
            after = next;
            node = next;
            next = NEXT(node);
        }
        NEXT(contact) = next;
        NEXT(node) = contact;
    }
    CContactToTest* following = NEXT(contact);
    SKIP(contact) = following;
    if (following != nullptr) {
        MULTI(contact) = MULTI(following);
        MULTI(following) = linkSelf ? contact : nullptr;
        if (MULTI(contact) != nullptr) SKIP(MULTI(contact)) = contact;
    }
    if (after == nullptr) {
        MULTI(contact) = after;
    } else {
        SKIP(after) = contact;
    }
    return after;
}
}  // namespace

// 0x00192e20 CKSrvCollision_ActivateTest_maybe (XXL2 AddContactToTestToAwakeList): the contact marked awake (infos bit
// 4) and put in the awake list by priority. Type 0 and 1 by themselves (a type 1 contact heads a multi-use group); a
// type 2 contact goes right after its partner (+0x14), which is first taken from the asleep list and put in the awake
// list by priority when it was not awake.
void CKSrvCollision::ActivateTest(CContactToTest* contact) {
    SetAwake(contact, true);
    const uint32_t type = contact->m_ba16Infos & 3u;
    if (type == 1) {
        InsertByPriority(&m_AwakeList, contact, true);
        return;
    }
    if (type == 0) {
        InsertByPriority(&m_AwakeList, contact, false);
        return;
    }
    if (type != 2) return;
    CContactToTest* partner = MULTI(contact);
    if (((partner->m_ba16Infos >> 4) & 1) != 0) {
        // BUG(original): the null test comes after the partner's infos were read.
        if (partner == nullptr) {
            NEXT(contact) = m_AwakeList;
            m_AwakeList = contact;
        } else {
            NEXT(contact) = NEXT(partner);
            NEXT(partner) = contact;
        }
        SKIP(contact) = NEXT(contact);
        return;
    }
    SetAwake(partner, true);
    // The partner leaves the asleep list.
    CContactToTest* head = m_AsleepList;
    if (head != nullptr) {
        if (partner == head) {
            m_AsleepList = NEXT(head) == nullptr ? nullptr : NEXT(partner);
            NEXT(partner) = nullptr;
        } else {
            CContactToTest* node = head;
            for (;;) {
                CContactToTest* next = NEXT(node);
                if (next == nullptr) break;
                if (next == partner) {
                    NEXT(node) = NEXT(partner);
                    if (NEXT(partner) != nullptr) NEXT(partner) = nullptr;
                    NEXT(partner) = nullptr;
                    break;
                }
                node = next;
            }
        }
    }
    InsertByPriority(&m_AwakeList, partner, true);
    NEXT(contact) = NEXT(partner);
    NEXT(partner) = contact;
    SKIP(contact) = NEXT(contact);
}

// 0x00193298 CKSrvCollision_ActivateTestsOfEnabledVolumes_maybe (XXL2 AwakeContactToTestIfNecessary): while the
// service's m_Infos bit 0 (a volume was switched on) is set, every asleep contact whose volumes are both on and whose
// awake class (infos bits 2-3) is not 0 is awoken (a multi-use contact only with its partner awake or able to wake);
// then the bit is cleared. A transcription of the original's walk (prev / prev2 trail the current contact).
void CKSrvCollision::ActivateTestsOfEnabledVolumes() {
    if ((m_Infos & 1) == 0) return;
    CContactToTest* cur = m_AsleepList;
    CContactToTest* prev = nullptr;
    CContactToTest* prev2 = nullptr;
    while (cur != nullptr) {
        CContactToTest* const contact = cur;
        bool wake = (VolumeInfos(contact, 0) & 1) != 0 && (VolumeInfos(contact, 1) & 1) != 0 &&
                    ((contact->m_ba16Infos >> 2) & 3u) != 0;
        if (wake && (contact->m_ba16Infos & 3u) == 2) {
            const CContactToTest* partner = MULTI(contact);
            if ((partner->m_ba16Infos & 0x10u) == 0 &&
                ((VolumeInfos(partner, 0) & 1) == 0 || (VolumeInfos(partner, 1) & 1) == 0)) {
                wake = false;
            }
        }
        if (!wake) {
            prev2 = prev;
            prev = cur;
            cur = NEXT(contact);
            continue;
        }
        const uint32_t type = contact->m_ba16Infos & 3u;
        CContactToTest* next = NEXT(contact);
        if (type == 2 && next == MULTI(contact)) next = NEXT(next);  // the partner is woken with it
        CContactToTest* newPrev = prev;
        if (type == 2 && NEXT(MULTI(contact)) == cur) {
            // The partner is the previous contact: it leaves the list too.
            newPrev = prev2;
            prev2 = nullptr;
        }
        if (prev == nullptr) {
            CContactToTest* head = m_AsleepList;
            if (head != nullptr) {
                CContactToTest* second = NEXT(head);
                if (second != nullptr) {
                    NEXT(head) = prev;
                    m_AsleepList = second;
                } else {
                    m_AsleepList = prev;
                }
            }
        } else {
            CContactToTest* removed = NEXT(prev);
            if (removed != nullptr) {
                NEXT(prev) = NEXT(removed);
                if (NEXT(removed) != nullptr) NEXT(removed) = nullptr;
            }
        }
        ActivateTest(contact);
        cur = next;
        prev = newPrev;
    }
    m_Infos &= ~1u;
}

namespace {
// The warned colliding lives emptied: each life's collisions unlinked, the life taken off the list, up to the bound
// (m_BoundWarned). BUG(original): a list that ends without the bound reads through null (it always ends with it).
void ClearWarnedLives(CCollidingLife** head, CCollidingLife* bound) {
    while (*head != bound) {
        CCollidingLife* life = *head;
        for (ICollision* collision = life->m_tHead; collision != nullptr;) {
            ICollision* next = collision->m_pNext;
            collision->m_pNext = nullptr;
            collision = next;
        }
        life->m_tHead = nullptr;
        CCollidingLife* next = (*head)->m_pNext;
        if (next == nullptr) {
            *head = nullptr;
            return;  // the original loops on a null head here
        }
        (*head)->m_pNext = nullptr;
        *head = next;
    }
}
}  // namespace

// 0x00192370 CKSrvCollision_DestroyService
void CKSrvCollision::DestroyService() {
    for (uint32_t i = 0; i < kProjectileCount; ++i) m_aProjectile[i].m_pBoundingVolume->Destroy();  // vt+0x10
    g_pEngine->m_classManager->DestroyObjectArray(m_aProjectileBoundingVolume);
    m_WarnedCollidingLivesList = nullptr;
}

// 0x00192510 CKSrvCollision_UpdateInitialize
void CKSrvCollision::UpdateInitialize() {
    ClearWarnedLives(&m_WarnedCollidingLivesList, &m_BoundWarned);
    m_ui8NbProjectilesWarned = 0;
    m_ui16NbTargetsWarned = 0;
    for (uint32_t i = 0; i < m_ui32NbBVListingCollisionRes; ++i) {
        static_cast<IKBoundingVolume*>(m_apBVListingCollisionRes[i])->m_CollisionResList = nullptr;
    }
    m_ui32NbBVListingCollisionRes = 0;
    for (uint32_t i = 0; i < kProjectileCount; ++i) m_aProjectile[i].m_tHead = nullptr;
    for (uint32_t i = 0; i < m_ui16NbProjectileTargets; ++i) m_aProjectileTarget[i].m_tHead = nullptr;
}

// 0x00192a70 CKSrvCollision_AcquireDynSphere_maybe
IKSerializable* CKSrvCollision::AcquireDynSphere() {
    if (m_ui8NbProjectileUsed > 49) return nullptr;
    CKDynamicBoundingSphere* sphere =
        static_cast<CKDynamicBoundingSphere*>(m_aProjectile[m_ui8NbProjectileUsed].m_pBoundingVolume);
    sphere->m_ba8Infos = static_cast<uint8_t>(sphere->m_ba8Infos | 0x3a);  // bits 1, 3, 4, 5 set in turn
    static const CVector3 kNullVector = {0.0f, 0.0f, 0.0f};                // g_nullVector 0x00c50d64
    sphere->m_v3WorldMove = kNullVector;
    const RwV3d& position = sphere->m_pRwFrame->ltm.pos;  // RwFrame +0x80
    sphere->m_v3OldPos.x = position.x;
    sphere->m_v3OldPos.z = position.z;
    sphere->m_v3OldPos.y = position.y;
    sphere->m_v3LastWorldPos.z = position.z;
    sphere->m_v3LastWorldPos.x = position.x;
    sphere->m_v3LastWorldPos.y = position.y;
    sphere->m_ui8OwnerType = 0;
    sphere->m_ui16PropertiesFlags = 0;
    sphere->m_ba8Infos = static_cast<uint8_t>(sphere->m_ba8Infos & ~0x4u);
    ++m_ui8NbProjectileUsed;
    return sphere;
}

// 0x00192bc0 CKSrvCollision_RemoveVolume_maybe
void CKSrvCollision::RemoveVolume(IKBoundingVolume* volume) {
    if ((volume->m_ba8Infos & 1u) == 0) return;
    volume->m_ba8Infos = static_cast<uint8_t>(volume->m_ba8Infos & 0xfeu);
    m_Infos = (m_Infos & 0xfffffffdu) | 2u;
}

// 0x00193638 CKSrvCollision_ProcessDynamicVolumes_maybe (XXL2 FindProjectilesCollisions): the used projectiles that
// were released (infos bit 1 clear) leave the used part of the pool (their owner cleared, their collisions with them),
// the last frame's warned projectiles and targets are cleared, then every used and active (bit 2) projectile is tested
// against the active volumes of every target, and the owners of the warned projectiles and targets get message 0x301
// with their collision lists.
// STUB(C2.7): all of it from the first used projectile on. The projectiles are fired by the combat code
// (CKSrvProjectiles, the abilities and enemies of the first fight), so none is used before C2.7, and with no projectile
// used, warned or hit the original does nothing here (the counts are 0 from the level file).
void CKSrvCollision::ProcessDynamicVolumes() {
    if (m_ui8NbProjectileUsed != 0 || m_ui8NbProjectilesWarned != 0 || m_ui16NbTargetsWarned != 0) {
        DOTD_STUB_ONCE("CKSrvCollision_ProcessDynamicVolumes_maybe 0x193638: projectiles in use (C2.7)");
    }
}

// 0x00193fe0 CKSrvCollision_ProcessPairs_maybe (XXL2 FindCollisions): the contact lists brought up to date (the
// volumes switched off, then on), the last frame's warned colliding lives cleared, then the awake contacts in order:
// the shapes' test (m_IntersectionMatrix) fills the next contact set; a touching contact of type 0 / 2 gets the set's
// index and, for each of its volumes, a collision (2 per contact, from m_aCollision): on the volume's own list when the
// volume keeps its collisions (infos bit 7; the volume is listed for the next frame's clearing), else on its colliding
// life's list (the life joins the warned list). At most 100 contacts touch per frame. A contact that does not touch
// skips the rest of its group (+0x10). Then every warned life's element gets message 0x300 with its collision list.
void CKSrvCollision::ProcessPairs() {
    DeactivateTestsOfDisabledVolumes();
    ActivateTestsOfEnabledVolumes();
    CContactToTest* contact = m_AwakeList;
    ClearWarnedLives(&m_WarnedCollidingLivesList, &m_BoundWarned);
    CCollidingLife* const bound = m_WarnedCollidingLivesList;
    if (contact == nullptr) return;
    CCollision* collision = m_aCollision;
    CContactSet* set = m_aContactSet;
    uint8_t found = 0;
    for (;;) {
        IKBoundingVolume* volume1 = static_cast<IKBoundingVolume*>(contact->m_apBoundingVolume[0]);
        IKBoundingVolume* volume2 = static_cast<IKBoundingVolume*>(contact->m_apBoundingVolume[1]);
        const int32_t shape1 = volume1->GetShapeType();  // vt+0x70
        const int32_t shape2 = volume2->GetShapeType();
        if (m_IntersectionMatrix[shape1][shape2](volume1, volume2, set) == 0) {
            contact = SKIP(contact);
        } else {
            if ((contact->m_ba16Infos & 3u) != 1) {
                contact->m_ui8ContactSetIndex = found;
                for (int side = 0; side < 2; ++side, ++collision) {
                    collision->m_pDetectedContact = contact;
                    IKBoundingVolume* volume = static_cast<IKBoundingVolume*>(contact->m_apBoundingVolume[side]);
                    if ((volume->m_ba8Infos & 0x80u) != 0) {
                        if (volume->m_CollisionResList == nullptr) {
                            m_apBVListingCollisionRes[m_ui32NbBVListingCollisionRes++] = volume;
                        }
                        collision->m_pNext = static_cast<ICollision*>(volume->m_CollisionResList);
                        volume->m_CollisionResList = static_cast<ICollision*>(collision);
                    } else if (contact->m_ui16CollidingLifeIndex[side] != 0xffff) {
                        CCollidingLife* life = &m_aCollidingLife[contact->m_ui16CollidingLifeIndex[side]];
                        if (life->m_pNext == nullptr) {
                            life->m_pNext = m_WarnedCollidingLivesList;
                            m_WarnedCollidingLivesList = life;
                        }
                        collision->m_pNext = life->m_tHead;
                        life->m_tHead = collision;
                    }
                }
                ++set;
                ++found;
            }
            contact = NEXT(contact);
        }
        if (contact == nullptr) {
            if (found == 0) return;
            break;
        }
        if (found > 99) break;
    }
    for (CCollidingLife* life = m_WarnedCollidingLivesList; life != bound; life = life->m_pNext) {
        life->m_pElementToCall->MessageProc(0x300, life->m_tHead);  // vt+0x1c
    }
}

// 0x00194440 UpdateCKSrvCollision
void CKSrvCollision::Update(IKTime* frameClock) {
    if (frameClock->m_eCurrentState != 0) return;
    m_fDeltaTime = frameClock->m_afDeltaTime[0];  // +0x1c
    for (uint32_t i = 0; i < m_ui32NbBVListingCollisionRes; ++i) {
        static_cast<IKBoundingVolume*>(m_apBVListingCollisionRes[i])->m_CollisionResList = nullptr;
    }
    m_ui32NbBVListingCollisionRes = 0;
    ProcessPairs();
    ProcessDynamicVolumes();
}
#undef NEXT
#undef SKIP
#undef MULTI


// 0x001956b8 CKSrvCollision_ProbeGroundInSectorList_maybe
uint8_t CKSrvCollision::ProbeGroundInSectorList(CKMeshKluster* kluster, const CGroundContactDatasIn* in,
                                                CGroundContactDatasInOut* inOut, const float* point) {
    const CVector3* p = reinterpret_cast<const CVector3*>(point);
    for (; kluster != nullptr; kluster = kluster->m_pNext) {
        const CBBox& box = kluster->m_BBox;
        if (!(box.m_inf.x <= p->x) || !(box.m_sup.x >= p->x)) continue;
        if (!(box.m_inf.z <= p->z) || !(box.m_sup.z >= p->z)) continue;
        if (!(p->y >= box.m_inf.y - in->m_fObjectHeight)) continue;
        for (uint32_t i = 0; i < kluster->m_ui16NbActiveGround; ++i) {
            CGround* ground = static_cast<CGround*>(kluster->m_apActiveGround[i]);
            const CBBox& mesh = *reinterpret_cast<const CBBox*>(ground->m_AABB);
            if (!(mesh.m_inf.x <= p->x) || !(mesh.m_sup.x >= p->x)) continue;
            if (!(mesh.m_inf.z <= p->z) || !(mesh.m_sup.z >= p->z)) continue;
            if (!(p->y >= mesh.m_inf.y - in->m_fObjectHeight)) continue;
            const uint32_t flags = ground->m_ba16EngineFlags;
            if ((flags & 1) == 0) continue;
            if ((flags & in->m_MasksOfGrdForTest[0]) == 0 || (flags & in->m_MasksOfGrdForTest[1]) != 0) continue;
            if (inOut->m_pGround == ground && ground->GetGroundContactOnFace(in, inOut, p)) return 1;  // vt+0x64
            if (ground->GetGroundContact(in, inOut, p)) return 1;                                    // vt+0x68
        }
    }
    return 0;
}

// 0x00196540 GroundProbePoints_maybe
void CKSrvCollision::GroundProbePoints(const CGroundContactDatasIn* in, CGroundContactDatasInOut* inOut,
                                       const float* points, int32_t count) {
    CKLevel* level = g_pEngine->m_level;
    for (; count != 0; --count, points += 3, ++inOut) {
        const CKSector* own = static_cast<const CKSector*>(level->m_vpSectors.m_pBlock[inOut->m_ui8SectorNumber]);
        if ((own->m_ba16Properties & 1) == 0) {
            inOut->m_ui8SectorNumber = 0;
            inOut->m_i32FaceIndex = -1;
            inOut->m_pGround = nullptr;
            inOut->m_eContactStatus = 3;
        }
        const CKSector* found = nullptr;
        for (CKSector* sector = level->IterateActiveSectors(nullptr); sector != nullptr;
             sector = level->IterateActiveSectors(sector)) {
            const CBBox& box = sector->m_AABB;
            if (!(box.m_inf.x <= points[0]) || !(box.m_sup.x >= points[0])) continue;
            if (!(box.m_inf.z <= points[2]) || !(box.m_sup.z >= points[2])) continue;
            if (!(box.m_inf.y <= points[1]) || !(box.m_sup.y >= points[1])) continue;
            if (!ProbeGroundInSectorList(sector->m_lMeshKlusterList, in, inOut, points)) continue;
            found = sector;
            break;
        }
        if (found != nullptr) {
            inOut->m_ui8SectorNumber = static_cast<uint8_t>(found->m_ui16NumSector);
        } else {
            inOut->m_eContactStatus = 3;
        }
    }
}

// ---- The wall edges (step 3): gathering, sweeps and line tests. XXL2 names in the comments; the PS3 code is ported
// operation for operation (the original's fused multiply-adds as ppc::fmadds / fmsubs).

namespace {

constexpr float kWallZero = 0.0f;                 // TOC -0x29b4
constexpr float kWallOne = 1.0f;                  // TOC -0x298c
constexpr float kWallSplitLength = 25.0f;         // TOC -0x2990: a longer line is gathered in pieces
constexpr float kWallSplitStep = 20.0f;           // TOC -0x2988
constexpr float kWallSplitOverlap = 0.999998987f; // TOC -0x2984 (0x3f7fffef)
constexpr float kWallPush = 0.00200000009f;       // TOC -0x296c: the distance kept from a wall
constexpr float kWallNoHit = 2.0f;                // TOC -0x2978: the starting best time of the sweeps
// 0x00c50dc4: a CVector2 (0, 0) in the data segment.
constexpr float kZeroVector2[2] = {0.0f, 0.0f};

SExtrapolated_Edge2D_Full_Infos* PotentialEdges(CKSrvCollision* service) {
    return static_cast<SExtrapolated_Edge2D_Full_Infos*>(service->m_aPotentialEdge);
}

// The ray id step of the gatherers (inlined in both): the next id, or after 0xfffd the id 1 and every mesh's last ray id
// cleared in the active sectors (grounds, walls, collision meshes).
void NextRayID(CKSrvCollision* service, CKLevel* level) {
    if (service->m_ui16RayID <= 0xfffd) {
        service->m_ui16RayID = static_cast<uint16_t>(service->m_ui16RayID + 1);
        return;
    }
    service->m_ui16RayID = 1;
    for (CKSector* sector = level->IterateActiveSectors(nullptr); sector != nullptr;
         sector = level->IterateActiveSectors(sector)) {
        for (CKMeshKluster* kluster = sector->m_lMeshKlusterList; kluster != nullptr; kluster = kluster->m_pNext) {
            for (uint32_t i = 0; i < kluster->m_ui16NbGround; ++i) {
                static_cast<ICollisionMesh*>(kluster->m_apGround[i])->m_ui16LastRayID = 0;
            }
            // The walls (+0x28) and collision meshes (+0x2c) the same way: no level of the game has one (C2.9).
            if (kluster->m_ui16NbWall != 0 || kluster->m_ui16NbCollisionMesh != 0) {
                DOTD_STUB_ONCE("CKSrvCollision ray id reset: walls / collision meshes (none in the game's files; C2.9)");
            }
        }
    }
}

// The box of a line (inlined in both gatherers): per axis the start and start + direction, the second the maximum when
// the direction is > 0.
CBBox LineBox(const CLine* line) {
    CBBox box;
    const CVector3& s = line->m_start;
    const CVector3& d = line->m_VectDir;
    if (d.x > kWallZero) {
        box.m_sup.x = d.x + s.x;
        box.m_inf.x = s.x;
    } else {
        box.m_sup.x = s.x;
        box.m_inf.x = d.x + s.x;
    }
    if (d.y > kWallZero) {
        box.m_sup.y = d.y + s.y;
        box.m_inf.y = s.y;
    } else {
        box.m_sup.y = s.y;
        box.m_inf.y = d.y + s.y;
    }
    if (d.z > kWallZero) {
        box.m_sup.z = d.z + s.z;
        box.m_inf.z = s.z;
    } else {
        box.m_sup.z = s.z;
        box.m_inf.z = d.z + s.z;
    }
    return box;
}

// The walk of both gatherers: the active sectors and their klusters whose boxes the query box overlaps strictly (x, z,
// and its top above their bottom), then each active ground not seen by this ray id whose box it overlaps (its top at or
// above the ground's bottom plus m_fHeightOffsetForNegativeEdges), that is on and matches the masks: marked with the ray
// id and asked for its edges. False when the edge array is full (the gatherer returns at once).
template <class Gather>
void WalkGroundsForEdges(CKSrvCollision* service, CKLevel* level, const CBBox& query,
                         const CMasksOfGrdTypeForTests* masks, Gather gather) {
    for (CKSector* sector = level->IterateActiveSectors(nullptr); sector != nullptr;
         sector = level->IterateActiveSectors(sector)) {
        const CBBox& s = sector->m_AABB;
        if (!(query.m_sup.x > s.m_inf.x) || !(query.m_inf.x < s.m_sup.x)) continue;
        if (!(query.m_sup.z > s.m_inf.z) || !(query.m_inf.z < s.m_sup.z)) continue;
        if (!(query.m_sup.y > s.m_inf.y)) continue;
        for (CKMeshKluster* kluster = sector->m_lMeshKlusterList; kluster != nullptr; kluster = kluster->m_pNext) {
            const CBBox& k = kluster->m_BBox;
            if (!(query.m_sup.x > k.m_inf.x) || !(query.m_inf.x < k.m_sup.x)) continue;
            if (!(query.m_sup.z > k.m_inf.z) || !(query.m_inf.z < k.m_sup.z)) continue;
            if (!(query.m_sup.y > k.m_inf.y)) continue;
            for (uint32_t i = 0; i < kluster->m_ui16NbActiveGround; ++i) {
                CGround* ground = static_cast<CGround*>(kluster->m_apActiveGround[i]);
                const uint16_t rayID = service->m_ui16RayID;
                if (rayID == ground->m_ui16LastRayID) continue;
                const CBBox& g = *reinterpret_cast<const CBBox*>(ground->m_AABB);
                if (!(query.m_sup.x >= g.m_inf.x) || !(query.m_inf.x <= g.m_sup.x)) continue;
                if (!(query.m_sup.z >= g.m_inf.z) || !(query.m_inf.z <= g.m_sup.z)) continue;
                if (!(query.m_sup.y >= g.m_inf.y + ground->m_fHeightOffsetForNegativeEdges)) continue;
                const uint32_t flags = ground->m_ba16EngineFlags;
                if ((flags & 1) == 0) continue;
                if (masks != nullptr &&
                    ((flags & masks->m_ui32GrdToTest) == 0 || (flags & masks->m_ui32GrdToAvoid) != 0)) {
                    continue;
                }
                if (service->m_ui8NbPotentialBoundEdge > 0xfd) return;
                ground->m_ui16LastRayID = rayID;
                gather(ground);
            }
        }
    }
}

// The common part of the gatherers' head: a line longer than 25 units (and depth <= 4) is gathered as two pieces, the
// first 20 units of it and the rest from just before there (BUG(original): CollectSweptWallCandidates's pieces go through
// GatherWallsAlongSegment, without the radius). True when the pieces were done.
bool SplitLongLine(CKSrvCollision* service, const CLine* line, float height, uint8_t cull,
                   const CMasksOfGrdTypeForTests* masks, uint8_t depth) {
    const float dx = line->m_VectDir.x, dy = line->m_VectDir.y, dz = line->m_VectDir.z;
    const float length = std::sqrt(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));  // Math_Sqrtf
    if (length == kWallZero || !(length > kWallSplitLength)) return false;
    const float inverse = kWallOne / length;
    const float sx = line->m_start.x, sy = line->m_start.y, sz = line->m_start.z;
    const float ex = sx + dx, ey = sy + dy, ez = sz + dz;
    const float stepZ = (dz * inverse) * kWallSplitStep;
    const float stepX = (dx * inverse) * kWallSplitStep;
    const float stepY = (dy * inverse) * kWallSplitStep;
    CLine piece;
    piece.m_start.x = sx;
    piece.m_start.y = sy;
    piece.m_start.z = sz;
    piece.m_VectDir.z = stepZ;
    piece.m_VectDir.x = stepX;
    piece.m_VectDir.y = stepY;
    const uint8_t next = static_cast<uint8_t>(depth + 1);
    service->GatherWallsAlongSegment(&piece, height, cull, masks, nullptr, next);
    const float nz = ppc::fmadds(stepZ, kWallSplitOverlap, sz);
    const float nx = ppc::fmadds(stepX, kWallSplitOverlap, sx);
    const float ny = ppc::fmadds(stepY, kWallSplitOverlap, sy);
    piece.m_start.z = nz;
    piece.m_start.x = nx;
    piece.m_start.y = ny;
    piece.m_VectDir.z = ez - nz;
    piece.m_VectDir.x = ex - nx;
    piece.m_VectDir.y = ey - ny;
    service->GatherWallsAlongSegment(&piece, height, cull, masks, nullptr, next);
    return true;
}

// Copies a sweep result (the inlined CSlideGroundEdgeDatasOut::Set: the byte only when the objects differ).
void CopySlideDatas(CSlideGroundEdgeDatasOut* to, const CSlideGroundEdgeDatasOut* from) {
    to->m_v3BouncingVector = from->m_v3BouncingVector;
    to->m_v3Normal = from->m_v3Normal;
    if (to != from) to->m_ba8Infos = from->m_ba8Infos;
    to->m_fYOfIntersection = from->m_fYOfIntersection;
    to->m_fHeightAbove = from->m_fHeightAbove;
    to->m_fHeightUnder = from->m_fHeightUnder;
}

}  // namespace

// 0x00197478 CKSrvCollision_GatherWallsAlongSegment_maybe (XXL2 FindAllPotentialGroundEdgesForIntersection(line, height,
// cull, masks, box)).
void CKSrvCollision::GatherWallsAlongSegment(const CLine* line, float height, uint8_t cull,
                                             const CMasksOfGrdTypeForTests* masks, const CBBox* box, uint8_t depth) {
    if (depth == 0) m_ui8NbPotentialBoundEdge = 0;
    if (depth <= 4 && SplitLongLine(this, line, height, cull, masks, depth)) return;
    CKLevel* level = g_pEngine->m_level;
    NextRayID(this, level);
    CBBox query = box != nullptr ? *box : LineBox(line);
    query.m_sup.y = query.m_sup.y + height;
    WalkGroundsForEdges(this, level, query, masks, [&](CGround* ground) {
        ground->FindAllPotentialEdgesForIntersection(PotentialEdges(this), &m_ui8NbPotentialBoundEdge, line, &query,
                                                     cull);  // vt+0x6c
    });
}


// 0x00197af8 CKSrvCollision_RaycastMeshes_maybe (XXL2 FindLineCollision(line, out, meshes, backFaces, masks)): the
// nearest face the line crosses (each mesh's FindLineIntersection, vt+0x58, keeps the smaller time in `out`). First the
// kluster holding the line's start (in the first active sector holding it): its grounds (meshes bit 0: active, on, the
// masks), walls (bit 1) and collision meshes (bit 2); a hit there ends the search. Else every active sector and kluster
// the segment's box test lets through (the start kluster excepted). Each mesh is tested once per ray id. `out`'s time
// starts at FLT_MAX; its sector is the sector of the last hit found.
uint8_t CKSrvCollision::RaycastMeshes(const CLine* line, CLineCollisionDatas* out, uint32_t meshes, uint8_t backFaces,
                                      const CMasksOfGrdTypeForTests* masks) {
    CKLevel* level = g_pEngine->m_level;
    NextRayID(this, level);
    out->m_i32FaceIndex = -1;
    out->m_ftOnLine = 3.40282347e+38f;  // FLT_MAX (0x00c4ace0)
    out->m_ui8SectorNumber = 0;
    out->m_pCollisionMesh = nullptr;
    // A kluster's meshes; true when one of them was hit.
    auto testKluster = [&](CKMeshKluster* kluster) {
        bool found = false;
        if ((meshes & 1u) != 0) {
            for (uint32_t i = 0; i < kluster->m_ui16NbActiveGround; ++i) {
                CGround* ground = static_cast<CGround*>(kluster->m_apActiveGround[i]);
                if (m_ui16RayID == ground->m_ui16LastRayID) continue;
                const uint32_t flags = ground->m_ba16EngineFlags;
                if ((flags & 1) == 0) continue;
                if (masks != nullptr &&
                    ((flags & masks->m_ui32GrdToTest) == 0 || (flags & masks->m_ui32GrdToAvoid) != 0)) {
                    continue;
                }
                const uint8_t hit = ground->FindLineIntersection(line, out, backFaces);  // vt+0x58
                ground->m_ui16LastRayID = m_ui16RayID;
                found = found || hit != 0;
            }
        }
        // The walls (bit 1) and collision meshes (bit 2): no level of the game has one (C2.9).
        if (((meshes & 2u) != 0 && kluster->m_ui16NbWall != 0) ||
            ((meshes & 4u) != 0 && kluster->m_ui16NbCollisionMesh != 0)) {
            DOTD_STUB_ONCE("CKSrvCollision_RaycastMeshes_maybe: walls / collision meshes (none in the game's files; C2.9)");
        }
        return found;
    };
    const CVector3& p = line->m_start;
    for (CKSector* sector = level->IterateActiveSectors(nullptr); sector != nullptr;
         sector = level->IterateActiveSectors(sector)) {
        const CBBox& s = sector->m_AABB;
        if (p.x < s.m_inf.x || s.m_sup.x < p.x) continue;
        if (p.z < s.m_inf.z || s.m_sup.z < p.z) continue;
        if (p.y < s.m_inf.y || s.m_sup.y < p.y) continue;
        for (CKMeshKluster* start = sector->m_lMeshKlusterList; start != nullptr; start = start->m_pNext) {
            const CBBox& k = start->m_BBox;
            if (!(k.m_inf.x <= p.x) || !(k.m_sup.x >= p.x)) continue;
            if (!(k.m_inf.z <= p.z) || !(k.m_sup.z >= p.z)) continue;
            if (!(k.m_inf.y <= p.y) || !(k.m_sup.y >= p.y)) continue;
            if (testKluster(start)) {
                out->m_ui8SectorNumber = static_cast<uint8_t>(sector->m_ui16NumSector);
                return 1;
            }
            uint8_t result = 0;
            for (CKSector* other = level->IterateActiveSectors(nullptr); other != nullptr;
                 other = level->IterateActiveSectors(other)) {
                if (!AABB_OverlapsSegmentBounds(&other->m_AABB, line)) continue;
                bool found = false;
                for (CKMeshKluster* kluster = other->m_lMeshKlusterList; kluster != nullptr; kluster = kluster->m_pNext) {
                    if (kluster == start || !AABB_OverlapsSegmentBounds(&kluster->m_BBox, line)) continue;
                    found = testKluster(kluster) || found;
                }
                if (found) {
                    out->m_ui8SectorNumber = static_cast<uint8_t>(other->m_ui16NumSector);
                    result = 1;
                }
            }
            return result;
        }
    }
    return 0;
}

// 0x00198438 CKSrvCollision_RaycastWalls_maybe (XXL2 FindBestIntersectionWithGroundEdges(line, height, out, cull, masks,
// gather)): the earliest wall edge the line crosses in x / z within the vertical span [y, y + height] of the line at the
// crossing (edges gathered first when `gather`): the time on the line and on the edge, the heights above / under, then
// the edge as a 3D line (from its first vertex) and its normal (dz, 0, -dx) normalised. 0 for a line that does not move.
uint8_t CKSrvCollision::RaycastWalls(const CLine* line, float height, CGroundEdgeDatasOut* out, uint8_t cull,
                                     const CMasksOfGrdTypeForTests* masks, uint8_t gather) {
    // 0x00c50d64: the shared zero vector.
    if (line->m_VectDir.x == 0.0f && line->m_VectDir.y == 0.0f && line->m_VectDir.z == 0.0f) return 0;
    if (gather != 0) GatherWallsAlongSegment(line, height, cull, masks, nullptr, 0);
    const uint32_t count = m_ui8NbPotentialBoundEdge;
    if (count == 0) return 0;
    const SExtrapolated_Edge2D_Full_Infos* edges = PotentialEdges(this);
    out->m_ftLine = kWallNoHit;
    CLine2D line2D;
    line2D.m_start.m_fX = line->m_start.x;
    line2D.m_start.m_fY = line->m_start.z;
    line2D.m_VectDir.m_fX = line->m_VectDir.x;
    line2D.m_VectDir.m_fY = line->m_VectDir.z;
    uint32_t bestIndex = 0;
    for (uint32_t i = 0; i < count; ++i) {
        const SExtrapolated_Edge2D_Full_Infos& e = edges[i];
        float tLine, tEdge;
        if (!Seg2D_IntersectSegment(&line2D, &e.m_ExtrapolatedEdge2D, &tLine, &tEdge)) continue;
        if (!(out->m_ftLine > tLine)) continue;
        const float w = kWallOne - tEdge;
        const float y = ppc::fmadds(tLine, line->m_VectDir.y, line->m_start.y);
        const float yEdge = ppc::fmadds(tEdge, e.m_YEnd, w * e.m_YStart);
        if (e.m_bEdgeWithHeight == 0) {
            if (!(y + height >= yEdge)) continue;
            out->m_ftLine = tLine;
            out->m_ftEdge = tEdge;
            bestIndex = i;
            out->m_ba8Infos = static_cast<uint8_t>(out->m_ba8Infos & 0xfcu);
            out->m_fHeightUnder = y - yEdge;
            continue;
        }
        const float h = ppc::fmadds(tEdge, e.m_fHeightOfEnd, w * e.m_fHeightOfStart);
        float above, under;
        if (h < kWallZero) {
            const float bottom = yEdge + h;
            if (!(y + height >= bottom) || !(y <= yEdge)) continue;
            under = y - bottom;
            above = yEdge - y;
        } else {
            if (!(y + height >= yEdge)) continue;
            const float top = yEdge + h;
            if (!(y <= top)) continue;
            under = y - yEdge;
            above = top - y;
        }
        out->m_ftLine = tLine;
        out->m_ftEdge = tEdge;
        bestIndex = i;
        out->m_ba8Infos = static_cast<uint8_t>((out->m_ba8Infos & 0xfcu) | 1u);
        out->m_fHeightAbove = above;
        out->m_fHeightUnder = under;
    }
    if (!(out->m_ftLine < kWallNoHit)) return 0;
    const SExtrapolated_Edge2D_Full_Infos& e = edges[bestIndex & 0xffffu];
    out->m_Edge.m_start.x = e.m_ExtrapolatedEdge2D.m_start.m_fX;
    out->m_Edge.m_start.y = e.m_YStart;
    out->m_Edge.m_start.z = e.m_ExtrapolatedEdge2D.m_start.m_fY;
    out->m_Edge.m_VectDir.x = e.m_ExtrapolatedEdge2D.m_VectDir.m_fX;
    out->m_Edge.m_VectDir.z = e.m_ExtrapolatedEdge2D.m_VectDir.m_fY;
    out->m_Edge.m_VectDir.y = e.m_YEnd - e.m_YStart;
    const float dz = e.m_ExtrapolatedEdge2D.m_VectDir.m_fY;
    const float ndx = -e.m_ExtrapolatedEdge2D.m_VectDir.m_fX;
    out->m_EdgeNormal.x = dz;
    out->m_EdgeNormal.y = kWallZero;
    out->m_EdgeNormal.z = ndx;
    const float length = std::sqrt(ppc::fmadds(ndx, ndx, ppc::fmadds(dz, dz, kWallZero)));  // Math_Sqrtf
    if (length == kWallZero) return 1;
    const float inverse = kWallOne / length;
    out->m_EdgeNormal.z = inverse * out->m_EdgeNormal.z;
    out->m_EdgeNormal.x = inverse * out->m_EdgeNormal.x;
    out->m_EdgeNormal.y = inverse * out->m_EdgeNormal.y;
    return 1;
}

// 0x00198808 CKSrvCollision_CollectSweptWallCandidates_maybe (XXL2 FindAllPotentialGroundEdgesForIntersection(line,
// radius, height, cull, masks, box)): the query box grown by the radius in x / z and the height on top; the grounds'
// sweep form (vt+0x70).
void CKSrvCollision::CollectSweptWallCandidates(const CLine* line, float radius, float height, uint8_t cull,
                                                const CMasksOfGrdTypeForTests* masks, const CBBox* box, uint8_t depth) {
    if (depth == 0) m_ui8NbPotentialBoundEdge = 0;
    if (depth <= 4 && SplitLongLine(this, line, height, cull, masks, depth)) return;
    CKLevel* level = g_pEngine->m_level;
    NextRayID(this, level);
    CBBox query = box != nullptr ? *box : LineBox(line);
    query.m_sup.y = query.m_sup.y + height;
    query.m_sup.x = query.m_sup.x + radius;
    query.m_inf.x = query.m_inf.x - radius;
    query.m_inf.z = query.m_inf.z - radius;
    query.m_sup.z = query.m_sup.z + radius;
    WalkGroundsForEdges(this, level, query, masks, [&](CGround* ground) {
        ground->FindAllPotentialEdgesForIntersection(PotentialEdges(this), &m_ui8NbPotentialBoundEdge, line, &query,
                                                     radius, cull);  // vt+0x70
    });
}

namespace {

// A hit of the sweep's first pass against the cylinder's wall slice: the time on the line, which part of which edge
// (0 the side, 1 the second vertex's circle, 2 the first's) and what goes to the result.
struct SweepHeights {
    bool hit;
    uint8_t withHeights;
    float above;
    float under;
};

// The vertical test of a hit at height y on the line against the wall at height yWall (with the wall's height h when it
// has heights): the cylinder (the line's y up to y + height) must reach the wall's bottom and the wall's top the line.
SweepHeights WallSpanTest(bool edgeWithHeight, float y, float height, float yWall, float h) {
    SweepHeights r = {false, 0, 0.0f, 0.0f};
    if (!edgeWithHeight) {
        if (!(height + y >= yWall)) return r;
        r.hit = true;
        r.under = y - yWall;
        return r;
    }
    r.withHeights = 1;
    if (h < kWallZero) {
        const float bottom = yWall + h;
        if (!(height + y >= bottom) || !(y <= yWall)) return r;
        r.hit = true;
        r.above = yWall - y;
        r.under = y - bottom;
        return r;
    }
    if (!(height + y >= yWall)) return r;
    const float top = yWall + h;
    if (!(top >= y)) return r;
    r.hit = true;
    r.above = top - y;
    r.under = y - yWall;
    return r;
}

// Stores a hit's heights into the result (bit 0 of the infos: the wall has heights).
void StoreSweepHeights(CSlideGroundEdgeDatasOut* out, const SweepHeights& h, float y) {
    out->m_ba8Infos = static_cast<uint8_t>((out->m_ba8Infos & 0xfeu) | h.withHeights);
    out->m_fYOfIntersection = y;
    if (h.withHeights != 0) out->m_fHeightAbove = h.above;
    out->m_fHeightUnder = h.under;
}

}  // namespace


// 0x00198ed0 CKSrvCollision_SweepCylinderAgainstWalls_maybe (XXL2 FindBestIntersectionWithGroundEdges(line, radius,
// height, out, cull, masks, gather), the form with a radius): the earliest time the cylinder moved along the line meets a
// gathered edge (sweep form) or one of its vertices, within the vertical span; the edge as a 3D line (from its moved-out
// start), the time on the edge (1 / 0 for the second / first vertex; infos bit 1 for a vertex, bit 0 for heights) and
// the normal: the edge's (dz, 0, -dx) or, at a vertex, from the vertex to the hit point. 0 for a line that does not move.
uint8_t CKSrvCollision::SweepCylinderAgainstWalls(const CLine* line, float radius, float height, CGroundEdgeDatasOut* out,
                                                  uint8_t cull, const CMasksOfGrdTypeForTests* masks, uint8_t gather) {
    const CVector3& s = line->m_start;
    const CVector3& d = line->m_VectDir;
    if (d.x == 0.0f && d.y == 0.0f && d.z == 0.0f) return 0;  // 0x00c50d64, the shared zero vector
    if (gather != 0) CollectSweptWallCandidates(line, radius, height, cull, masks, nullptr, 0);
    const uint32_t count = m_ui8NbPotentialBoundEdge;
    if (count == 0) return 0;
    const SExtrapolated_Edge2D_Full_Infos* edges = PotentialEdges(this);
    out->m_ftLine = kWallNoHit;
    CLine2D line2D;
    line2D.m_start.m_fX = s.x;
    line2D.m_start.m_fY = s.z;
    line2D.m_VectDir.m_fX = d.x;
    line2D.m_VectDir.m_fY = d.z;
    uint32_t bestIndex = 0;
    // Records a hit: the times, the infos (bit 0 heights, bit 1 a vertex) and the heights.
    auto record = [&](uint32_t i, float tLine, float tEdge, const SweepHeights& h, uint8_t vertex) {
        out->m_ftLine = tLine;
        out->m_ftEdge = tEdge;
        bestIndex = i;
        out->m_ba8Infos = static_cast<uint8_t>((out->m_ba8Infos & 0xfcu) | h.withHeights | (vertex << 1));
        if (h.withHeights != 0) out->m_fHeightAbove = h.above;
        out->m_fHeightUnder = h.under;
    };
    for (uint32_t i = 0; i < count; ++i) {
        const SExtrapolated_Edge2D_Full_Infos& e = edges[i];
        float tLine, tEdge;
        if (Seg2D_IntersectSegment(&line2D, &e.m_ExtrapolatedEdge2D, &tLine, &tEdge) && out->m_ftLine > tLine) {
            const float w = kWallOne - tEdge;
            const float y = ppc::fmadds(tLine, d.y, s.y);
            const float yEdge = ppc::fmadds(tEdge, e.m_YEnd, w * e.m_YStart);
            const float hEdge = e.m_bEdgeWithHeight != 0 ? ppc::fmadds(tEdge, e.m_fHeightOfEnd, w * e.m_fHeightOfStart)
                                                         : 0.0f;
            const SweepHeights h = WallSpanTest(e.m_bEdgeWithHeight != 0, y, height, yEdge, hEdge);
            if (h.hit) record(i, tLine, tEdge, h, 0);
            continue;
        }
        float t0, t1;
        if (Seg2D_IntersectCircle(radius, &line2D, &e.m_CircleCenterEnd, &t0, &t1) && out->m_ftLine > t0) {
            const float y = ppc::fmadds(t0, d.y, s.y);
            const SweepHeights h = WallSpanTest(e.m_bEdgeWithHeight != 0, y, height, e.m_YEnd, e.m_fHeightOfEnd);
            if (h.hit) record(i, t0, kWallOne, h, 1);
            continue;
        }
        if (!Seg2D_IntersectCircle(radius, &line2D, &e.m_CircleCenterStart, &t0, &t1)) continue;
        if (!(out->m_ftLine > t0)) continue;
        const float y = ppc::fmadds(t0, d.y, s.y);
        const SweepHeights h = WallSpanTest(e.m_bEdgeWithHeight != 0, y, height, e.m_YStart, e.m_fHeightOfStart);
        if (h.hit) record(i, t0, kWallZero, h, 1);
    }
    if (!(out->m_ftLine < kWallNoHit)) return 0;
    const SExtrapolated_Edge2D_Full_Infos& e = edges[bestIndex & 0xffffu];
    out->m_Edge.m_start.x = e.m_ExtrapolatedEdge2D.m_start.m_fX;
    out->m_Edge.m_start.y = e.m_YStart;
    out->m_Edge.m_start.z = e.m_ExtrapolatedEdge2D.m_start.m_fY;
    out->m_Edge.m_VectDir.y = e.m_YEnd - e.m_YStart;
    out->m_Edge.m_VectDir.x = e.m_ExtrapolatedEdge2D.m_VectDir.m_fX;
    out->m_Edge.m_VectDir.z = e.m_ExtrapolatedEdge2D.m_VectDir.m_fY;
    if (((out->m_ba8Infos >> 1) & 1u) == 0) {
        out->m_EdgeNormal.x = e.m_ExtrapolatedEdge2D.m_VectDir.m_fY;
        out->m_EdgeNormal.y = 0.0f;
        out->m_EdgeNormal.z = -e.m_ExtrapolatedEdge2D.m_VectDir.m_fX;
    } else {
        const float hz = ppc::fmadds(out->m_ftLine, d.z, s.z);
        const float hx = ppc::fmadds(out->m_ftLine, d.x, s.x);
        const CVector2& c = out->m_ftEdge != kWallOne ? e.m_CircleCenterStart : e.m_CircleCenterEnd;
        out->m_EdgeNormal.x = hx - c.m_fX;
        out->m_EdgeNormal.y = 0.0f;
        out->m_EdgeNormal.z = hz - c.m_fY;
    }
    const float nz = out->m_EdgeNormal.z;
    const float length = std::sqrt(
        ppc::fmadds(nz, nz, ppc::fmadds(out->m_EdgeNormal.x, out->m_EdgeNormal.x, out->m_EdgeNormal.y * out->m_EdgeNormal.y)));
    if (length == kWallZero) return 1;  // Math_Sqrtf
    const float inverse = kWallOne / length;
    out->m_EdgeNormal.z = inverse * out->m_EdgeNormal.z;
    out->m_EdgeNormal.x = inverse * out->m_EdgeNormal.x;
    out->m_EdgeNormal.y = inverse * out->m_EdgeNormal.y;
    return 1;
}

// 0x001996b0 CKSrvCollision_ResolveWallSegmentMovement_maybe (XXL2 SlideOnGroundEdges(line, height, out, prev, masks,
// gather), the form without a radius): the line (a point with a vertical span of `height`) moved against the wall edges
// gathered along it. Each edge's normal is (re)computed into the edge array as it is tested. The earliest wall the line
// crosses (facing it, vertically in reach) cuts the move 0.002 short and the rest is projected along it; a second pass
// stops that slide at another wall. Returns 2 (slid; the bouncing vector is the displacement from the line's end) or 0
// (free, no edge, a wall it does not move into, or a line that does not move in x / z). The value is the original's
// result masked with 2.
uint8_t CKSrvCollision::ResolveWallSegmentMovement(const CLine* line, float height, CSlideGroundEdgeDatasOut* out,
                                                   CSlideGroundEdgeDatasOut* prev, const CMasksOfGrdTypeForTests* masks,
                                                   uint8_t gather) {
    const CVector3& s = line->m_start;
    const CVector3& d = line->m_VectDir;
    CLine2D line2D;
    line2D.m_start.m_fX = s.x;
    line2D.m_start.m_fY = s.z;
    line2D.m_VectDir.m_fX = d.x;
    line2D.m_VectDir.m_fY = d.z;
    if (prev != nullptr) prev->m_ba8Infos = static_cast<uint8_t>(prev->m_ba8Infos & ~4u);
    if (gather != 0) {
        // The query box: as ResolveSweptCylinderWalls' (the start moved by the direction turned a quarter, and the end).
        const float x1 = d.z + s.x, x2 = s.x - d.z;
        const float z2 = s.z + d.x, z1 = -d.x + s.z;
        const float ex = s.x + d.x, ey = s.y + d.y, ez = s.z + d.z;
        CBBox box;
        float minX = x1 >= x2 ? x2 : x1;
        minX = minX < ex ? minX : ex;
        const float minY = ey > s.y ? s.y : ey;
        float minZ = z1 >= z2 ? z2 : z1;
        minZ = minZ < ez ? minZ : ez;
        box.m_inf.x = minX;
        box.m_inf.y = minY;
        box.m_inf.z = minZ;
        float maxX = x1 > x2 ? x1 : x2;
        maxX = maxX > ex ? maxX : ex;
        const float maxY = ey >= s.y ? ey : s.y;
        float maxZ = z1 > z2 ? z1 : z2;
        maxZ = maxZ > ez ? maxZ : ez;
        box.m_sup.x = maxX;
        box.m_sup.y = maxY;
        box.m_sup.z = maxZ;
        GatherWallsAlongSegment(line, height, 0, masks, &box, 0);
    }
    auto none = [&]() -> uint8_t {
        out->m_ba8Infos = static_cast<uint8_t>(out->m_ba8Infos & ~4u);
        return 0;
    };
    const uint32_t count = m_ui8NbPotentialBoundEdge;
    if (count == 0) return none();
    if (d.x == kZeroVector2[0] && d.z == kZeroVector2[1]) return none();
    SExtrapolated_Edge2D_Full_Infos* edges = PotentialEdges(this);
    float best = kWallNoHit;
    int32_t bestIndex = -1;
    for (uint32_t i = 0; i < count; ++i) {
        SExtrapolated_Edge2D_Full_Infos& e = edges[i];
        // The edge's normal (dz, -dx), normalised, kept in the edge.
        const float ndx = -e.m_ExtrapolatedEdge2D.m_VectDir.m_fX;
        const float dz = e.m_ExtrapolatedEdge2D.m_VectDir.m_fY;
        e.m_Normal.m_fX = dz;
        e.m_Normal.m_fY = ndx;
        const float length = std::sqrt(ppc::fmadds(dz, dz, ndx * ndx));  // Math_Sqrtf
        if (length != kWallZero) {
            const float inverse = kWallOne / length;
            e.m_Normal.m_fY = inverse * e.m_Normal.m_fY;
            e.m_Normal.m_fX = inverse * e.m_Normal.m_fX;
        }
        const float facing = ppc::fmadds(e.m_ExtrapolatedEdge2D.m_start.m_fX - s.x, e.m_Normal.m_fX,
                                         (e.m_ExtrapolatedEdge2D.m_start.m_fY - s.z) * e.m_Normal.m_fY);
        if (facing > kWallZero) continue;
        float tLine, tEdge;
        if (!Seg2D_IntersectSegment(&line2D, &e.m_ExtrapolatedEdge2D, &tLine, &tEdge)) continue;
        if (!(best > tLine)) continue;
        const float w = kWallOne - tEdge;
        const float y = ppc::fmadds(tLine, d.y, s.y);
        const float yEdge = ppc::fmadds(tEdge, e.m_YEnd, w * e.m_YStart);
        const float hEdge = e.m_bEdgeWithHeight != 0 ? ppc::fmadds(tEdge, e.m_fHeightOfEnd, w * e.m_fHeightOfStart) : 0.0f;
        const SweepHeights h = WallSpanTest(e.m_bEdgeWithHeight != 0, y, height, yEdge, hEdge);
        if (!h.hit) continue;
        best = tLine;
        bestIndex = static_cast<int32_t>(i);
        StoreSweepHeights(out, h, y);
    }
    if (bestIndex == -1) return none();
    const SExtrapolated_Edge2D_Full_Infos& hitEdge = edges[bestIndex];
    const float nx = hitEdge.m_Normal.m_fX, nz = hitEdge.m_Normal.m_fY;
    const float push = ppc::fmadds(best - kWallOne, ppc::fmadds(nx, d.x, nz * d.z), kWallPush);
    if (push < kWallZero) return none();
    const float pushZ = nz * push;
    const float pushX = nx * push;
    out->m_v3Normal.x = nx;
    out->m_v3Normal.z = nz;
    out->m_v3Normal.y = kWallZero;
    CSlideGroundEdgeDatasOut saved;
    saved.m_v3BouncingVector = out->m_v3BouncingVector;
    saved.m_v3Normal = out->m_v3Normal;
    saved.m_ba8Infos = out->m_ba8Infos;
    saved.m_fHeightAbove = out->m_fHeightAbove;
    saved.m_fHeightUnder = out->m_fHeightUnder;
    saved.m_fYOfIntersection = out->m_fYOfIntersection;
    float unitZ = d.z, unitX = d.x;
    float length = std::sqrt(ppc::fmadds(d.x, d.x, d.z * d.z));  // Math_Sqrtf
    if (length != kWallZero) {
        const float inverse = kWallOne / length;
        unitZ = unitZ * inverse;
        unitX = unitX * inverse;
    } else {
        length = kWallZero;
    }
    const float reach = best * length;
    if (reach > kWallPush) {
        const float back = (reach - length) - kWallPush;
        saved.m_v3BouncingVector.y = 0.0f;
        saved.m_v3BouncingVector.z = unitZ * back;
        saved.m_v3BouncingVector.x = unitX * back;
    } else {
        saved.m_v3BouncingVector.y = 0.0f;
        saved.m_v3BouncingVector.z = -d.z;
        saved.m_v3BouncingVector.x = -d.x;
    }
    saved.m_ba8Infos = static_cast<uint8_t>(saved.m_ba8Infos | 4u);
    if (prev != nullptr) CopySlideDatas(prev, &saved);
    // The second pass: from the end pulled back along the slid end, with the line's own heights.
    const float endX = s.x + d.x, endZ = s.z + d.z;
    CLine2D slide;
    slide.m_start.m_fX = endX + saved.m_v3BouncingVector.x;
    slide.m_start.m_fY = endZ + saved.m_v3BouncingVector.z;
    slide.m_VectDir.m_fX = (pushX + endX) - slide.m_start.m_fX;
    slide.m_VectDir.m_fY = (pushZ + endZ) - slide.m_start.m_fY;
    int32_t kind = 0;
    float best2 = kWallNoHit;
    for (uint32_t j = 0; j < count; ++j) {
        if (static_cast<int32_t>(j) == bestIndex) continue;
        const SExtrapolated_Edge2D_Full_Infos& e = edges[j];
        float tLine, tEdge;
        if (!Seg2D_IntersectSegment(&slide, &e.m_ExtrapolatedEdge2D, &tLine, &tEdge)) continue;
        if (!(tLine < best2)) continue;
        const float w = kWallOne - tEdge;
        const float y = ppc::fmadds(tLine, d.y, s.y);
        const float yEdge = ppc::fmadds(tEdge, e.m_YEnd, w * e.m_YStart);
        const float hEdge = e.m_bEdgeWithHeight != 0 ? ppc::fmadds(tEdge, e.m_fHeightOfEnd, w * e.m_fHeightOfStart) : 0.0f;
        const SweepHeights h = WallSpanTest(e.m_bEdgeWithHeight != 0, y, height, yEdge, hEdge);
        if (!h.hit) continue;
        best2 = tLine;
        kind = 3;
        StoreSweepHeights(out, h, y);
        out->m_v3Normal.z = e.m_Normal.m_fY;
        out->m_v3Normal.x = e.m_Normal.m_fX;
        out->m_v3Normal.y = kWallZero;
    }
    if (kind == 0) {
        out->m_v3BouncingVector.z = pushZ;
        out->m_v3BouncingVector.x = pushX;
        out->m_v3BouncingVector.y = 0.0f;
        out->m_ba8Infos = static_cast<uint8_t>((out->m_ba8Infos & ~6u) | 4u);
        return 2;
    }
    // Stopped by a second wall at best2 (0.002 short of it when the slide got anywhere).
    const float moveZ = best2 * slide.m_VectDir.m_fY;
    const float moveX = best2 * slide.m_VectDir.m_fX;
    const float moved = std::sqrt(ppc::fmadds(moveX, moveX, moveZ * moveZ));  // Math_Sqrtf
    if (moved != kWallZero && moved > kWallPush) {
        const float keep = moved - kWallPush;
        const float inverse = kWallOne / moved;
        out->m_v3BouncingVector.y = kWallZero;
        const float stopX = ppc::fmadds(keep, moveX * inverse, slide.m_start.m_fX);
        const float stopZ = ppc::fmadds(keep, moveZ * inverse, slide.m_start.m_fY);
        out->m_v3BouncingVector.x = stopX - (s.x + d.x);
        out->m_v3BouncingVector.z = stopZ - (s.z + d.z);
    } else {
        CopySlideDatas(out, &saved);
    }
    out->m_ba8Infos = static_cast<uint8_t>(out->m_ba8Infos | 6u);
    return 2;
}

// 0x0019a158 CKSrvCollision_SweepCircleAgainstWallSegments_maybe (XXL2 IsInsideEdgeSpace(point, radius, height, out)):
// is the cylinder (radius, height above the point's y) at the point in a gathered edge's space? Per edge, its distance
// d along the edge's normal (0 <= d <= radius; once an edge's side was hit, only a larger d) projected inside the edge
// and vertically within the wall: the wall's normal (n.x, 0, n.y) and a push of (d + 0.002) along it. Outside the edge
// (and no side hit yet): its corners within the radius (BUG(original): only the first vertex's, or the nearer of both
// when both are within: a lone second vertex in reach is ignored), with the push radius - distance. The result goes to
// `out` (bit 0 of the infos: the wall has heights; bit 1 cleared; bit 2 set when something was hit).
uint8_t CKSrvCollision::SweepCircleAgainstWallSegments(const CVector3* point, float radius, float height,
                                                       CSlideGroundEdgeDatasOut* out) {
    out->m_ba8Infos = static_cast<uint8_t>(out->m_ba8Infos & ~2u);
    const uint32_t count = m_ui8NbPotentialBoundEdge;
    uint8_t found = 0;
    if (count != 0) {
        const SExtrapolated_Edge2D_Full_Infos* edges = PotentialEdges(this);
        const float px = point->x, pz = point->z;
        float best = -3.40282347e+38f;  // -FLT_MAX (0x00c4ace0)
        bool sideHit = false;
        for (uint32_t i = 0; i < count; ++i) {
            const SExtrapolated_Edge2D_Full_Infos& e = edges[i];
            const float sx = e.m_ExtrapolatedEdge2D.m_start.m_fX, sz = e.m_ExtrapolatedEdge2D.m_start.m_fY;
            const float nx = e.m_Normal.m_fX, ny = e.m_Normal.m_fY;
            const float d = ppc::fmadds(sx - px, nx, (sz - pz) * ny);
            if (!(d >= kWallZero) || !(d <= radius)) continue;
            if (found != 0 && sideHit && !(d > best)) continue;
            // The point projected on the edge's line, and its place along the edge.
            const float qz = ppc::fmadds(ny, d, pz);
            const float qx = ppc::fmadds(nx, d, px);
            const float ex = e.m_ExtrapolatedEdge2D.m_VectDir.m_fX, ez = e.m_ExtrapolatedEdge2D.m_VectDir.m_fY;
            const float along = ppc::fmadds(qx - sx, ex, (qz - sz) * ez);
            if (along >= kWallZero) {
                const float length2 = ppc::fmadds(ex, ex, ez * ez);
                if (along <= length2) {
                    const float t = along / length2;
                    const float w = kWallOne - t;
                    const float y = ppc::fmadds(t, e.m_YEnd, w * e.m_YStart);
                    const float top = height + point->y;
                    bool hit = false;
                    float above = 0.0f, under = 0.0f;
                    uint8_t withHeights = 0;
                    if (e.m_bEdgeWithHeight == 0) {
                        if (top >= y) {
                            hit = true;
                            under = point->y - y;
                        }
                    } else {
                        const float h = ppc::fmadds(t, e.m_fHeightOfEnd, w * e.m_fHeightOfStart);
                        withHeights = 1;
                        if (h < kWallZero) {
                            const float bottom = y + h;
                            if (top >= bottom && y >= point->y) {
                                hit = true;
                                above = y - point->y;
                                under = point->y - bottom;
                            }
                        } else if (top >= y) {
                            const float wallTop = y + h;
                            if (point->y <= wallTop) {
                                hit = true;
                                above = wallTop - point->y;
                                under = point->y - y;
                            }
                        }
                    }
                    if (hit) {
                        const float push = d + kWallPush;
                        out->m_v3Normal.x = nx;
                        out->m_v3Normal.y = kWallZero;
                        out->m_v3Normal.z = ny;
                        out->m_v3BouncingVector.y = kWallZero;
                        out->m_v3BouncingVector.z = ny * push;
                        out->m_v3BouncingVector.x = nx * push;
                        out->m_ba8Infos = static_cast<uint8_t>((out->m_ba8Infos & 0xfeu) | withHeights);
                        if (withHeights != 0) out->m_fHeightAbove = above;
                        out->m_fHeightUnder = under;
                        out->m_fYOfIntersection = point->y;
                        best = d;
                        sideHit = true;
                        found = 1;
                        continue;
                    }
                }
            }
            // The corners.
            if (sideHit) continue;
            const float r2 = radius * radius;
            const float endDz = pz - e.m_CircleCenterEnd.m_fY, endDx = px - e.m_CircleCenterEnd.m_fX;
            const float startDz = pz - e.m_CircleCenterStart.m_fY, startDx = px - e.m_CircleCenterStart.m_fX;
            const float end2 = ppc::fmadds(endDx, endDx, endDz * endDz);
            const float start2 = ppc::fmadds(startDx, startDx, startDz * startDz);
            bool useStart;
            if (!(r2 >= end2)) {
                if (!(r2 >= start2)) continue;
                useStart = true;
            } else {
                if (!(r2 >= start2)) continue;
                useStart = end2 > start2;
            }
            const float pen = radius - std::sqrt(useStart ? start2 : end2);  // Math_Sqrtf
            if (!(pen > best)) continue;
            const CVector2& c = useStart ? e.m_CircleCenterStart : e.m_CircleCenterEnd;
            const float y = useStart ? e.m_YStart : e.m_YEnd;
            const float top = height + point->y;
            float above = 0.0f, under = 0.0f;
            uint8_t withHeights = 0;
            if (e.m_bEdgeWithHeight == 0) {
                if (!(top >= y)) continue;
                under = point->y - y;
            } else {
                const float h = useStart ? e.m_fHeightOfStart : e.m_fHeightOfEnd;
                withHeights = 1;
                const float other = y + h;
                if (h < kWallZero) {
                    if (!(top >= other) || !(y >= point->y)) continue;
                    above = y - point->y;
                    under = point->y - other;
                } else {
                    if (!(top >= y) || !(point->y <= other)) continue;
                    above = other - point->y;
                    under = point->y - y;
                }
            }
            float nz = pz - c.m_fY;
            float nx2 = px - c.m_fX;
            const float length = std::sqrt(ppc::fmadds(nx2, nx2, nz * nz));  // Math_Sqrtf
            if (length != kWallZero) {
                const float inverse = kWallOne / length;
                nz = nz * inverse;
                nx2 = nx2 * inverse;
            }
            const float push = pen + kWallPush;
            out->m_v3Normal.y = kWallZero;
            out->m_v3BouncingVector.y = kWallZero;
            best = pen;
            out->m_v3Normal.x = nx2;
            found = 1;
            out->m_v3Normal.z = nz;
            out->m_v3BouncingVector.z = push * nz;
            out->m_v3BouncingVector.x = push * nx2;
            out->m_ba8Infos = static_cast<uint8_t>((out->m_ba8Infos & 0xfeu) | withHeights);
            if (withHeights != 0) out->m_fHeightAbove = above;
            out->m_fHeightUnder = under;
            out->m_fYOfIntersection = point->y;
        }
    }
    out->m_ba8Infos = static_cast<uint8_t>((out->m_ba8Infos & ~4u) | (found << 2));
    return found;
}

// 0x0019aa68 CKSrvCollision_ResolveSweptCylinderWalls_maybe (XXL2 SlideOnGroundEdges(line, radius, height, out, prev,
// masks, gather)): a vertical cylinder (radius, height above the line) moved along the line against the wall edges
// (gathered first when `gather`). Returns 0: free (or no edge); 2: it slid along a wall (the bouncing vector is the
// slide's displacement); 3: pushed out at the end (the bouncing vector is the push; `prev`, when given, receives the
// result too). The two passes: the first finds the earliest side or corner the line meets (a wall facing the line,
// vertically in reach), the line is cut there and the rest projected along the wall; the second pass sweeps that rest
// against the other edges.
uint8_t CKSrvCollision::ResolveSweptCylinderWalls(const CLine* line, float radius, float height,
                                                  CSlideGroundEdgeDatasOut* out, CSlideGroundEdgeDatasOut* prev,
                                                  const CMasksOfGrdTypeForTests* masks, uint8_t gather) {
    const CVector3& s = line->m_start;
    const CVector3& d = line->m_VectDir;
    CLine2D line2D;
    line2D.m_start.m_fX = s.x;
    line2D.m_start.m_fY = s.z;
    line2D.m_VectDir.m_fX = d.x;
    line2D.m_VectDir.m_fY = d.z;
    if (prev != nullptr) prev->m_ba8Infos = static_cast<uint8_t>(prev->m_ba8Infos & ~4u);
    if (gather != 0) {
        // The query box: the start moved sideways by the direction turned a quarter (x +- d.z, z -+ d.x) and the end.
        const float x1 = d.z + s.x, x2 = s.x - d.z;
        const float z2 = s.z + d.x, z1 = -d.x + s.z;
        const float ex = s.x + d.x, ey = s.y + d.y, ez = s.z + d.z;
        CBBox box;
        float minX = x1 >= x2 ? x2 : x1;
        minX = minX < ex ? minX : ex;
        const float minY = ey > s.y ? s.y : ey;
        float minZ = z1 >= z2 ? z2 : z1;
        minZ = minZ < ez ? minZ : ez;
        box.m_inf.x = minX;
        box.m_inf.y = minY;
        box.m_inf.z = minZ;
        float maxX = x1 > x2 ? x1 : x2;
        maxX = maxX > ex ? maxX : ex;
        const float maxY = ey >= s.y ? ey : s.y;
        float maxZ = z1 > z2 ? z1 : z2;
        maxZ = maxZ > ez ? maxZ : ez;
        box.m_sup.x = maxX;
        box.m_sup.y = maxY;
        box.m_sup.z = maxZ;
        CollectSweptWallCandidates(line, radius, height, 0, masks, &box, 0);
    }
    const uint32_t count = m_ui8NbPotentialBoundEdge;
    auto none = [&]() -> uint8_t {
        out->m_ba8Infos = static_cast<uint8_t>(out->m_ba8Infos & ~4u);
        return 0;
    };
    if (count == 0) return none();
    const SExtrapolated_Edge2D_Full_Infos* edges = PotentialEdges(this);
    CVector3 endPoint;
    endPoint.x = s.x + d.x;
    endPoint.y = s.y + d.y;
    endPoint.z = s.z + d.z;
    auto dotBounce = [&](const CSlideGroundEdgeDatasOut* o) {
        return ppc::fmadds(o->m_v3BouncingVector.z, d.z,
                           ppc::fmadds(d.x, o->m_v3BouncingVector.x, o->m_v3BouncingVector.y * d.y));
    };
    auto pushedBack = [&]() -> uint8_t {  // the bouncing vector less the direction; `prev` takes the result
        out->m_v3BouncingVector.x = out->m_v3BouncingVector.x - d.x;
        out->m_v3BouncingVector.y = out->m_v3BouncingVector.y - d.y;
        out->m_v3BouncingVector.z = out->m_v3BouncingVector.z - d.z;
        if (prev != nullptr) CopySlideDatas(prev, out);
        return 3;
    };
    // Already inside at the start, moving into the wall.
    if (SweepCircleAgainstWallSegments(&s, radius, height, out) && !(dotBounce(out) >= kWallZero)) return pushedBack();
    // At the end only (the start was free, or the move leaves the wall).
    auto testEnd = [&]() -> uint8_t {
        if (!SweepCircleAgainstWallSegments(&endPoint, radius, height, out)) return none();
        if (prev != nullptr) CopySlideDatas(prev, out);
        return 3;
    };
    // Not moving in x / z: the end point.
    if (d.x == kZeroVector2[0] && d.z == kZeroVector2[1]) return testEnd();

    // The first pass.
    float bestT = kWallNoHit;
    int32_t bestIndex = -1;
    int32_t kind = 0;
    for (uint32_t i = 0; i < count; ++i) {
        const SExtrapolated_Edge2D_Full_Infos& e = edges[i];
        // Only walls facing the line's start (its first vertex on the line's side of the normal).
        const float facing = ppc::fmadds(e.m_CircleCenterStart.m_fX - s.x, e.m_Normal.m_fX,
                                         (e.m_CircleCenterStart.m_fY - s.z) * e.m_Normal.m_fY);
        if (facing > kWallZero) continue;
        float tLine, tEdge;
        if (Seg2D_IntersectSegment(&line2D, &e.m_ExtrapolatedEdge2D, &tLine, &tEdge) && bestT > tLine) {
            const float w = kWallOne - tEdge;
            const float y = ppc::fmadds(tLine, d.y, s.y);
            const float yEdge = ppc::fmadds(tEdge, e.m_YEnd, w * e.m_YStart);
            const float hEdge = e.m_bEdgeWithHeight != 0 ? ppc::fmadds(tEdge, e.m_fHeightOfEnd, w * e.m_fHeightOfStart)
                                                         : 0.0f;
            const SweepHeights h = WallSpanTest(e.m_bEdgeWithHeight != 0, y, height, yEdge, hEdge);
            if (!h.hit) continue;
            bestT = tLine;
            bestIndex = static_cast<int32_t>(i);
            kind = 0;
            StoreSweepHeights(out, h, y);
            continue;
        }
        float t0, t1;
        if (Seg2D_IntersectCircle(radius, &line2D, &e.m_CircleCenterEnd, &t0, &t1) && bestT > t0) {
            const float y = ppc::fmadds(t0, d.y, s.y);
            const SweepHeights h = WallSpanTest(e.m_bEdgeWithHeight != 0, y, height, e.m_YEnd, e.m_fHeightOfEnd);
            if (!h.hit) continue;
            bestT = t0;
            bestIndex = static_cast<int32_t>(i);
            kind = 1;
            StoreSweepHeights(out, h, y);
            continue;
        }
        if (!Seg2D_IntersectCircle(radius, &line2D, &e.m_CircleCenterStart, &t0, &t1)) continue;
        if (!(bestT > t0)) continue;
        const float y = ppc::fmadds(t0, d.y, s.y);
        const SweepHeights h = WallSpanTest(e.m_bEdgeWithHeight != 0, y, height, e.m_YStart, e.m_fHeightOfStart);
        if (!h.hit) continue;
        bestT = t0;
        bestIndex = static_cast<int32_t>(i);
        kind = 2;
        StoreSweepHeights(out, h, y);
    }
    if (bestIndex == -1) return testEnd();

    // The response to the first hit: the wall's normal (a side's, or from the corner's centre to the hit point), the
    // push = (bestT - 1) * (normal . direction) + 0.002 back along it.
    const SExtrapolated_Edge2D_Full_Infos& hitEdge = edges[bestIndex];
    float normalX, normalZ;
    float push;
    if (kind == 0) {
        normalX = hitEdge.m_Normal.m_fX;
        normalZ = hitEdge.m_Normal.m_fY;
        push = ppc::fmadds(bestT - kWallOne, ppc::fmadds(normalX, d.x, normalZ * d.z), kWallPush);
        if (push < kWallZero) goto pushedAtStartOrEnd;
        out->m_v3Normal.x = normalX;
        out->m_v3Normal.y = kWallZero;
        out->m_v3Normal.z = normalZ;
    } else {
        const float hx = ppc::fmadds(bestT, d.x, s.x);
        const float hz = ppc::fmadds(bestT, d.z, s.z);
        const CVector2& c = kind == 1 ? hitEdge.m_CircleCenterEnd : hitEdge.m_CircleCenterStart;
        normalZ = hz - c.m_fY;
        normalX = hx - c.m_fX;
        const float length = std::sqrt(ppc::fmadds(normalX, normalX, normalZ * normalZ));  // Math_Sqrtf
        if (length != kWallZero) {
            const float inverse = kWallOne / length;
            normalZ = normalZ * inverse;
            normalX = normalX * inverse;
        }
        out->m_v3Normal.x = normalX;
        out->m_v3Normal.y = kWallZero;
        out->m_v3Normal.z = normalZ;
        push = ppc::fmadds(bestT - kWallOne, ppc::fmadds(normalX, d.x, normalZ * d.z), kWallPush);
        if (push < kWallZero) goto pushedAtStartOrEnd;
    }
    {
        const float pushZ = normalZ * push;  // f21
        const float pushX = normalX * push;  // f22
        // The slide: the line cut at the hit (0.002 short of it), the rest of the move along the wall.
        CSlideGroundEdgeDatasOut saved;
        saved.m_v3BouncingVector = out->m_v3BouncingVector;
        saved.m_v3Normal = out->m_v3Normal;
        saved.m_ba8Infos = out->m_ba8Infos;
        saved.m_fHeightAbove = out->m_fHeightAbove;
        saved.m_fHeightUnder = out->m_fHeightUnder;
        saved.m_fYOfIntersection = out->m_fYOfIntersection;
        float unitZ = d.z, unitX = d.x;
        float length = std::sqrt(ppc::fmadds(d.x, d.x, d.z * d.z));  // Math_Sqrtf
        if (length != kWallZero) {
            const float inverse = kWallOne / length;
            unitZ = unitZ * inverse;
            unitX = unitX * inverse;
        } else {
            length = kWallZero;
        }
        const float reach = length * bestT;
        if (!(reach > kWallPush)) {
            saved.m_v3BouncingVector.y = 0.0f;
            saved.m_v3BouncingVector.z = -d.z;
            saved.m_v3BouncingVector.x = -d.x;
        } else {
            const float back = (reach - length) - kWallPush;
            saved.m_v3BouncingVector.y = 0.0f;
            saved.m_v3BouncingVector.z = unitZ * back;
            saved.m_v3BouncingVector.x = unitX * back;
        }
        saved.m_ba8Infos = static_cast<uint8_t>(saved.m_ba8Infos | 4u);
        if (prev != nullptr) CopySlideDatas(prev, &saved);
        // The second pass: from the end pulled back (the cut) along the slid end.
        const float yHit = ppc::fmadds(bestT, d.y, s.y);
        const float endX = s.x + d.x, endZ = s.z + d.z, endY = s.y + d.y;
        CLine2D slide;
        slide.m_start.m_fX = endX + saved.m_v3BouncingVector.x;
        slide.m_start.m_fY = endZ + saved.m_v3BouncingVector.z;
        const float dropY = endY - yHit;
        slide.m_VectDir.m_fX = (pushX + endX) - slide.m_start.m_fX;
        slide.m_VectDir.m_fY = (pushZ + endZ) - slide.m_start.m_fY;
        float best2 = kWallNoHit;
        for (uint32_t j = 0; j < count; ++j) {
            if (static_cast<int32_t>(j) == bestIndex) continue;
            const SExtrapolated_Edge2D_Full_Infos& e = edges[j];
            float tLine, tEdge;
            if (Seg2D_IntersectSegment(&slide, &e.m_ExtrapolatedEdge2D, &tLine, &tEdge) && best2 > tLine) {
                const float w = kWallOne - tEdge;
                const float y = ppc::fmadds(dropY, tLine, yHit);
                const float yEdge = ppc::fmadds(tEdge, e.m_YEnd, w * e.m_YStart);
                const float hEdge = e.m_bEdgeWithHeight != 0
                                        ? ppc::fmadds(tEdge, e.m_fHeightOfEnd, w * e.m_fHeightOfStart)
                                        : 0.0f;
                const SweepHeights h = WallSpanTest(e.m_bEdgeWithHeight != 0, y, height, yEdge, hEdge);
                if (!h.hit) continue;
                best2 = tLine;
                kind = 3;
                StoreSweepHeights(out, h, y);
                out->m_v3Normal.z = e.m_Normal.m_fY;
                out->m_v3Normal.x = e.m_Normal.m_fX;
                out->m_v3Normal.y = kWallZero;
                continue;
            }
            float t0, t1;
            const CVector2* center = &e.m_CircleCenterEnd;
            float yWall = e.m_YEnd, hWall = e.m_fHeightOfEnd;
            if (!(Seg2D_IntersectCircle(radius, &slide, center, &t0, &t1) && best2 > t0)) {
                center = &e.m_CircleCenterStart;
                yWall = e.m_YStart;
                hWall = e.m_fHeightOfStart;
                if (!Seg2D_IntersectCircle(radius, &slide, center, &t0, &t1)) continue;
                if (!(best2 > t0)) continue;
            }
            const float y = ppc::fmadds(dropY, t0, yHit);
            const SweepHeights h = WallSpanTest(e.m_bEdgeWithHeight != 0, y, height, yWall, hWall);
            if (!h.hit) continue;
            StoreSweepHeights(out, h, y);
            const float cz = ppc::fmadds(t0, slide.m_VectDir.m_fY, slide.m_start.m_fY);
            const float cx = ppc::fmadds(t0, slide.m_VectDir.m_fX, slide.m_start.m_fX);
            float nz = cz - center->m_fY;
            float nx = cx - center->m_fX;
            const float length2 = std::sqrt(ppc::fmadds(nx, nx, nz * nz));  // Math_Sqrtf
            if (length2 != kWallZero) {
                const float inverse = kWallOne / length2;
                nz = nz * inverse;
                nx = nx * inverse;
            }
            best2 = t0;
            kind = 3;
            out->m_v3Normal.x = nx;
            out->m_v3Normal.y = kWallZero;
            out->m_v3Normal.z = nz;
        }
        if (kind <= 2) {
            // Nothing in the way of the slide: is its end free?
            CVector3 slidEnd;
            slidEnd.x = endX + pushX;
            slidEnd.y = endY;
            slidEnd.z = endZ + pushZ;
            if (SweepCircleAgainstWallSegments(&slidEnd, radius, height, out)) {
                out->m_v3BouncingVector.x = pushX + out->m_v3BouncingVector.x;
                out->m_v3BouncingVector.z = pushZ + out->m_v3BouncingVector.z;
                return 3;
            }
            out->m_v3BouncingVector.z = pushZ;
            out->m_v3BouncingVector.x = pushX;
            out->m_v3BouncingVector.y = 0.0f;
            out->m_ba8Infos = static_cast<uint8_t>((out->m_ba8Infos & ~6u) | 4u);
            return 2;
        }
        if (kind != 3) return none();
        // The slide met another wall at best2: stop there (less 0.002) when it got anywhere.
        const float moveZ = best2 * slide.m_VectDir.m_fY;
        const float moveX = best2 * slide.m_VectDir.m_fX;
        const float moved = std::sqrt(ppc::fmadds(moveX, moveX, moveZ * moveZ));  // Math_Sqrtf
        if (moved == kWallZero || !(moved > kWallPush)) {
            CopySlideDatas(out, &saved);
            if (SweepCircleAgainstWallSegments(&s, radius, height, out)) {
                out->m_v3BouncingVector.x = out->m_v3BouncingVector.x - d.x;
                out->m_v3BouncingVector.y = out->m_v3BouncingVector.y - d.y;
                out->m_v3BouncingVector.z = out->m_v3BouncingVector.z - d.z;
                return 3;
            }
        } else {
            const float keep = moved - kWallPush;
            const float inverse = kWallOne / moved;
            CVector3 stop;
            stop.x = ppc::fmadds(keep, moveX * inverse, slide.m_start.m_fX);
            stop.z = ppc::fmadds(keep, moveZ * inverse, slide.m_start.m_fY);
            stop.y = endY;
            const float stopDz = stop.z - endZ;
            const float stopDx = stop.x - endX;
            if (SweepCircleAgainstWallSegments(&stop, radius, height, out)) {
                out->m_v3BouncingVector.x = stopDx + out->m_v3BouncingVector.x;
                out->m_v3BouncingVector.z = stopDz + out->m_v3BouncingVector.z;
                return 3;
            }
            out->m_v3BouncingVector.z = stopDz;
            out->m_v3BouncingVector.x = stopDx;
            out->m_v3BouncingVector.y = kWallZero;
        }
        out->m_ba8Infos = static_cast<uint8_t>(out->m_ba8Infos | 6u);
        return 2;
    }
pushedAtStartOrEnd:
    // The hit wall pushes the line back out: inside at the start moving in, else at the end.
    if (SweepCircleAgainstWallSegments(&s, radius, height, out) && !(dotBounce(out) >= kWallZero)) return pushedBack();
    return testEnd();
}
