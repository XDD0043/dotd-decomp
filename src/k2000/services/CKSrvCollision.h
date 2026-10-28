// CKSrvCollision.h - the collision service (key 0x81, vtable 0xb1bf30, size 0x3ab8). Original unit:
// CKSrvCollision.cpp (0x191b00-0x19ce30; Start/Stop/Pause/Resume sit in the CKGroundCpnt.cpp unit).
// XXL2: K/KServices/KServiceCollision/CKSrvCollision.h: the same members in the same order (every
// PS3 offset below follows from XXL2's order and the PS3 Load, constructor and InitializeService), read
// the same way.
//
// The loader asks it for the 50 projectile volumes (FindNonRecreableInstances) that InitializeService
// creates; the level file then gives the projectile targets, the colliding lives and the contacts to
// test. The collision tests themselves (m_IntersectionMatrix, UpdateCKSrvCollision) are STUB(C1.6).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/cameras/CKSrvCamera.h"
#include "k2000/hooks/GroundContact.h"
#include "k2000/services/CollisionDatas.h"
#include "k2000/services/IKService.h"

struct CBBox;
struct CContactToTest;
class CKMeshKluster;
class CProjectileCollision;
class IKBoundingVolume;

// XXL2 CProjectile (a TSNodeList<CProjectileCollision*>), 8 bytes on the PS3.
struct CProjectile {
    CProjectile() : m_tHead(nullptr) {}

    CProjectileCollision* m_tHead;      // +0x00 the list's head
    IKSerializable* m_pBoundingVolume;  // +0x04 IKBoundingVolume: a CKDynBSphereProjectile (11:6)
};
DOTD_ASSERT_SIZE(CProjectile, 0x8);

// XXL2 CProjectileTarget (a TSNodeList<CProjectileCollision*>), 0x48 bytes on the PS3. new[] (an array
// cookie, as the original's OperatorNewArray(n * 0x48 + 4)); the constructor clears the head.
struct CProjectileTarget {
    CProjectileTarget() : m_tHead(nullptr) {}
    ~CProjectileTarget() {}

    CProjectileCollision* m_tHead;          // +0x00
    IKSerializable* m_apBoundingVolume[16]; // +0x04 IKBoundingVolume*
    uint8_t m_ui8NbBoundingVolumes;         // +0x44
    uint8_t m_pad45[3];                     // +0x45
};
DOTD_ASSERT_SIZE(CProjectileTarget, 0x48);

// XXL2 CCollidingLife (a TSNodeList<CCollision*>), 0xc bytes on the PS3. new[] (an array cookie).
class CCollision;
struct CCollidingLife {
    CCollidingLife();  // the element constructor of CKSrvCollision_Load's new[] and of m_BoundWarned
    ~CCollidingLife() {}

    CCollision* m_tHead;               // +0x00
    IKSerializable* m_pElementToCall;  // +0x04
    CCollidingLife* m_pNext;           // +0x08
};
DOTD_ASSERT_SIZE(CCollidingLife, 0xc);

// XXL2 CContactToTest, 0x1c bytes on the PS3. new[] (an array cookie).
struct CContactToTest {
    CContactToTest();  // inlined in CKSrvCollision_Load's new[] loop (0x195544)
    ~CContactToTest() {}

    IKSerializable* m_apBoundingVolume[2];  // +0x00 IKBoundingVolume*
    uint16_t m_ui16CollidingLifeIndex[2];   // +0x08 0xffff: none
    CContactToTest* m_apSameStateNext[2];   // +0x0c the awake/asleep lists, read as indices
    CContactToTest* m_pMultiUse;            // +0x14 read as an index
    uint16_t m_ba16Infos;                   // +0x18 XXL2 CBitArray16 (big-endian bitfields on the PS3)
    uint8_t m_ui8ContactSetIndex;           // +0x1a 0xc9 (201): none of the 200 contact sets _maybe
    uint8_t m_ui8Priority;                  // +0x1b
};
DOTD_ASSERT_SIZE(CContactToTest, 0x1c);

// XXL2 CContactSet, 0x24 bytes on the PS3. Never initialised by the constructor or Load.
struct CContactSet {
    uint32_t m_Infos;                // +0x00 XXL2 CBitArray
    float m_fUDeltaTime;             // +0x04
    float m_fdInterpenetration;      // +0x08
    CVector3 m_Normale12;            // +0x0c
    CVector3 m_WorldContactPoint;    // +0x18
};
DOTD_ASSERT_SIZE(CContactSet, 0x24);

// XXL2 ICollision (a CSBaseNode<ICollision*>): the ten-slot interface of a detected collision, vtable
// 0xb1bfe0 (every slot pure, no destructor). The argument and return types are XXL2's in the comments;
// the PS3 ones are not verified.
class ICollision {
public:
    virtual IKSerializable* GetBoundingVolume1() = 0;       // +0x00 (XXL2: const IKBoundingVolume&)
    virtual IKSerializable* GetBoundingVolume2() = 0;       // +0x04
    virtual uint8_t HasContactSet() = 0;                    // +0x08
    virtual uint8_t AreResponseParamsActive(uint32_t mask) = 0;      // +0x0c
    virtual uint8_t IsResponseParamsMaskEqualTo(uint32_t mask) = 0;  // +0x10
    virtual float GetUDeltaTime() = 0;                      // +0x14
    virtual float GetdInterpenetration() = 0;               // +0x18
    virtual const CVector3* GetNormale12() = 0;             // +0x1c (XXL2: const CVector3&)
    virtual const CVector3* GetWorldContactPoint() = 0;     // +0x20 (XXL2: const CVector3&)
    virtual int32_t GetCollisionType() = 0;                 // +0x24 (XXL2: ECollision_Type)

    ICollision* m_pNext = nullptr;  // +0x04 the constructor clears it
};

// XXL2 CCollision: a volume-against-volume collision, 0xc bytes on the PS3, vtable 0xb1be50
// (Ghidra: Vt_b1be50_*; the bodies in misc/Vt_5.cpp, the unit 0x18ff28-0x190128). The contact set is the detected
// contact's (m_ui8ContactSetIndex into g_aContactSet; 0xc9 = none: the flags read 0, the floats and vectors come from
// the null base, as in the original).
class CCollision : public ICollision {
public:
    IKSerializable* GetBoundingVolume1() override;                  // 0x18ff28
    IKSerializable* GetBoundingVolume2() override;                  // 0x18ff38
    uint8_t HasContactSet() override;                               // 0x18ffa0
    uint8_t AreResponseParamsActive(uint32_t mask) override;        // 0x18ff48
    uint8_t IsResponseParamsMaskEqualTo(uint32_t mask) override;    // 0x1900d0
    float GetUDeltaTime() override;                                 // 0x190098
    float GetdInterpenetration() override;                          // 0x190060
    const CVector3* GetNormale12() override;                        // 0x190028
    const CVector3* GetWorldContactPoint() override;                // 0x18fff0
    int32_t GetCollisionType() override { return 0; }               // 0x9aa650 (returns 0)

    CContactToTest* m_pDetectedContact;  // +0x08 not set by the constructor
};

// XXL2 CProjectileCollision: a projectile-against-target collision, 0x10 bytes on the PS3, vtable
// 0xb1c010 (Ghidra: Vt_b1c010_*; the bodies in misc/Vt_6.cpp, the unit 0x19ce30-0x19d020).
class CProjectileCollision : public ICollision {
public:
    IKSerializable* GetBoundingVolume1() override;                  // 0x19ce30 the projectile's volume
    IKSerializable* GetBoundingVolume2() override;                  // 0x19ce50 the target's volume
    uint8_t HasContactSet() override;                               // 0x19ce88
    uint8_t AreResponseParamsActive(uint32_t mask) override;        // 0x19ced0
    uint8_t IsResponseParamsMaskEqualTo(uint32_t mask) override;    // 0x19cf28
    float GetUDeltaTime() override;                                 // 0x19cf80
    float GetdInterpenetration() override;                          // 0x19cfa8
    const CVector3* GetNormale12() override;                        // 0x19cfd0
    const CVector3* GetWorldContactPoint() override;                // 0x19cff8
    int32_t GetCollisionType() override { return 1; }               // 0x9aab10 (returns 1)

    uint8_t m_ui8ContactSetIndex;            // +0x08 not set by the constructor
    uint8_t m_ui8ProjectileIndex;            // +0x09
    uint16_t m_ui16TargetIndex;              // +0x0a
    uint8_t m_ui8TargetBoundingVolumeIndex;  // +0x0c
    uint8_t m_pad0d[3];                      // +0x0d
};

class CKSrvCollision : public IKService {
public:
    DOTD_CLASS_KEY(kCategoryService, 0x2)
    DOTD_DECLARE_FACTORIES(CKSrvCollision)

    static constexpr uint32_t kProjectileCount = 50;
    static constexpr uint32_t kContactSetCount = 200;
    static constexpr uint32_t kBVListingCount = 400;

    CKSrvCollision();  // inlined in 0x001949d8 CKSrvCollision_Create (0x191e60 Construct has the same stores)
    ~CKSrvCollision() override {}

    // vt+0x20 0x00191f60 CKSrvCollision_FindNonRecreableInstances: the 50 projectile volumes, only when
    // exactly 50 of class 11:6 are asked for.
    uint8_t FindNonRecreableInstances(int32_t category, uint32_t id, uint32_t count, void* out) override;
    void Destroy() override;  // vt+0x10 0x00192138 CKSrvCollision_Destroy
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00194c88 CKSrvCollision_Load
    // 0x00192090 CKSrvCollision_EnableVolume: a volume that was off is switched on (bit 0 of its infos set,
    // the service's m_Infos bit 0 set); bit 2 of the infos is set either way.
    void EnableVolume(IKBoundingVolume* volume);
    // 0x00196540 GroundProbePoints_maybe (XXL2 GetGroundContact): for each of `count` points (three floats) the ground
    // under it, into the matching contact. A contact whose sector is not active is reset first (no ground, face -1,
    // status 3, sector 0). Then the active sectors (CKLevel_IterateActiveSectors) whose box holds the point, in order:
    // the first whose kluster list finds a ground (ProbeGroundInSectorList) gives the contact and its sector number;
    // none: status 3 (the rest of the contact is kept).
    void GroundProbePoints(const CGroundContactDatasIn* in, CGroundContactDatasInOut* inOut, const float* points,
                           int32_t count);
    // The same for the camera's copies of the XXL2 types (CKSrvCamera::CGroundContactDatasIn / InOut, same layout).
    void GroundProbePoints(const CKSrvCamera::CGroundContactDatasIn* in, CKSrvCamera::CGroundContactDatasInOut* inOut,
                           const float* points, int32_t count) {
        GroundProbePoints(reinterpret_cast<const CGroundContactDatasIn*>(in),
                          reinterpret_cast<CGroundContactDatasInOut*>(inOut), points, count);
    }
    // 0x001956b8 CKSrvCollision_ProbeGroundInSectorList_maybe (XXL2 GetGroundContactOnKlusterList): the klusters whose
    // box holds the point (y down to the box's bottom less m_fObjectHeight), their active grounds whose box holds it the
    // same way, that are on (engine flag bit 0) and match the masks (a bit of MasksOfGrdForTest[0], none of [1]): the
    // contact's own ground first tries its face (vt+0x64), then any ground its faces (vt+0x68); the first answer wins.
    static uint8_t ProbeGroundInSectorList(CKMeshKluster* kluster, const CGroundContactDatasIn* in,
                                           CGroundContactDatasInOut* inOut, const float* point);
    // The wall edges: the grounds' edges gathered into m_aPotentialEdge (m_ui8NbPotentialBoundEdge of them, at most 0xfe),
    // each ground once per ray id (m_ui16RayID, ICollisionMesh::m_ui16LastRayID).
    // 0x00197478 CKSrvCollision_GatherWallsAlongSegment_maybe (XXL2 FindAllPotentialGroundEdgesForIntersection): the
    // edges near the line (or `box`, null: the line's box), the box's top raised by `height`; `cull` keeps only edges
    // facing the line. A line longer than 25 is gathered in two pieces (depth up to 5). Depth 0 empties the list.
    void GatherWallsAlongSegment(const CLine* line, float height, uint8_t cull, const CMasksOfGrdTypeForTests* masks,
                                 const CBBox* box, uint8_t depth);
    // 0x00197af8 CKSrvCollision_RaycastMeshes_maybe (XXL2 FindLineCollision): the nearest face crossed by the line among the
    // meshes `meshes` selects (bit 0 grounds, 1 walls, 2 collision meshes), from the kluster holding its start.
    uint8_t RaycastMeshes(const CLine* line, CLineCollisionDatas* out, uint32_t meshes, uint8_t backFaces,
                          const CMasksOfGrdTypeForTests* masks);
    // 0x00198438 CKSrvCollision_RaycastWalls_maybe (XXL2 FindBestIntersectionWithGroundEdges): the earliest wall edge the
    // line crosses within its vertical span.
    uint8_t RaycastWalls(const CLine* line, float height, CGroundEdgeDatasOut* out, uint8_t cull,
                         const CMasksOfGrdTypeForTests* masks, uint8_t gather);
    // 0x00198808 CKSrvCollision_CollectSweptWallCandidates_maybe (XXL2 FindAllPotentialGroundEdgesForIntersection with a
    // radius): the same for a cylinder (the box grown by the radius in x / z); the edges in the sweep form.
    void CollectSweptWallCandidates(const CLine* line, float radius, float height, uint8_t cull,
                                    const CMasksOfGrdTypeForTests* masks, const CBBox* box, uint8_t depth);
    // 0x00198ed0 CKSrvCollision_SweepCylinderAgainstWalls_maybe (XXL2 FindBestIntersectionWithGroundEdges with a radius): the
    // earliest wall edge or vertex the cylinder meets along the line.
    uint8_t SweepCylinderAgainstWalls(const CLine* line, float radius, float height, CGroundEdgeDatasOut* out, uint8_t cull,
                                      const CMasksOfGrdTypeForTests* masks, uint8_t gather);
    // 0x001996b0 CKSrvCollision_ResolveWallSegmentMovement_maybe (XXL2 SlideOnGroundEdges without a radius): the line moved
    // against the wall edges; 2 slid (out: the slide), 0 free.
    uint8_t ResolveWallSegmentMovement(const CLine* line, float height, CSlideGroundEdgeDatasOut* out,
                                       CSlideGroundEdgeDatasOut* prev, const CMasksOfGrdTypeForTests* masks, uint8_t gather);
    // 0x0019a158 CKSrvCollision_SweepCircleAgainstWallSegments_maybe (XXL2 IsInsideEdgeSpace): the cylinder at `point`
    // against the gathered edges; the push out of the deepest wall into `out`.
    uint8_t SweepCircleAgainstWallSegments(const CVector3* point, float radius, float height, CSlideGroundEdgeDatasOut* out);
    // 0x0019aa68 CKSrvCollision_ResolveSweptCylinderWalls_maybe (XXL2 SlideOnGroundEdges with a radius): the cylinder
    // moved along `line`; 0 free, 2 slid (out: the slide), 3 pushed out (out: the push).
    uint8_t ResolveSweptCylinderWalls(const CLine* line, float radius, float height, CSlideGroundEdgeDatasOut* out,
                                      CSlideGroundEdgeDatasOut* prev, const CMasksOfGrdTypeForTests* masks, uint8_t gather);
    // 0x00192b80 CKSrvCollision_AddVolume_maybe: a volume that is not registered yet gets bit 0 of its infos and
    // the service's m_Infos bit 0 set (the camera's two dodge spheres at the level start).
    void AddVolume(IKBoundingVolume* volume);
    // 0x001920e8 CKSrvCollision_DisableVolume: a volume that was on is switched off (bit 0 of its infos
    // cleared, the service's m_Infos bit 1 set); bit 2 of the infos is cleared either way.
    void DisableVolume(IKBoundingVolume* volume);
    void Start() override {}                            // vt+0x50 0x191580 (empty)
    void Stop() override {}                             // vt+0x68 0x191598 (empty)
    void Pause() override {}                            // vt+0x70 0x191590 (empty)
    void Resume() override {}                           // vt+0x78 0x1915a0 (empty)
    // vt+0x7c 0x00194440 UpdateCKSrvCollision (XXL2 Update): while the clock runs (state 0), the frame's dt kept, the
    // volumes' collision lists of the last frame cleared, then the pairs (ProcessPairs) and the projectiles
    // (ProcessDynamicVolumes).
    void Update(IKTime* frameClock) override;
    // vt+0x94 0x00191c50 CKSrvCollision_InitializeService: the collision tests (m_IntersectionMatrix), the
    // projectile volumes the loader asks for, the lists and the globals.
    int32_t InitializeService() override;
    // vt+0x98 0x00192370 CKSrvCollision_DestroyService: the 50 projectile volumes destroyed (vt+0x10) and their array.
    void DestroyService() override;
    // vt+0x9c 0x00192510 CKSrvCollision_UpdateInitialize: the warned colliding lives and the volumes' collision lists
    // cleared, no projectile used or warned, no target warned.
    void UpdateInitialize() override;

    // The test of a volume pair (m_IntersectionMatrix[shape1][shape2], IKBoundingVolume::EShape): 1 and the contact set
    // filled when they touch.
    typedef uint8_t (*CollisionTestFn)(IKBoundingVolume* volume1, IKBoundingVolume* volume2, CContactSet* set);
    // 0x00192a70 CKSrvCollision_AcquireDynSphere_maybe (XXL2 GetProjectile): the next free projectile volume, reset
    // (moving and on, at its frame's position, no owner), or null when the 50 are used.
    IKSerializable* AcquireDynSphere();
    // 0x00192bc0 CKSrvCollision_RemoveVolume_maybe: a registered volume (infos bit 0) loses the bit; the service's
    // m_Infos bit 1 (a volume was removed) set.
    void RemoveVolume(IKBoundingVolume* volume);

private:
    void DeactivateTestsOfDisabledVolumes();     // 0x001915a8 (XXL2 AsleepContactToTestIfNecessary)
    void ActivateTest(CContactToTest* contact);  // 0x00192e20 (XXL2 AddContactToTestToAwakeList)
    void ActivateTestsOfEnabledVolumes();        // 0x00193298 (XXL2 AwakeContactToTestIfNecessary)
    void ProcessDynamicVolumes();                // 0x00193638 (XXL2 FindProjectilesCollisions)
    void ProcessPairs();                         // 0x00193fe0 (XXL2 FindCollisions)

public:

    uint32_t m_Infos;                            // +0x0c XXL2 CBitArray; Load sets bits 0 and 1
    uint16_t m_ui16RayID;                        // +0x10
    uint16_t m_pad12;                            // +0x12
    void* m_aPotentialEdge;                      // +0x14 SExtrapolated_Edge2D_Full_Infos* (a global's block)
    uint8_t m_ui8NbPotentialBoundEdge;           // +0x18
    uint8_t m_pad19[3];                          // +0x19
    IKSerializable* m_aProjectileBoundingVolume; // +0x1c CKDynBSphereProjectile[50] (CreateObjectArray(11, 6, 50))
    CProjectile m_aProjectile[kProjectileCount]; // +0x20
    CProjectileTarget* m_aProjectileTarget;      // +0x1b0
    uint16_t m_ui16NbProjectileTargets;          // +0x1b4
    uint8_t m_ui8NbProjectileUsed;               // +0x1b6
    uint8_t m_ui8NbProjectilesWarned;            // +0x1b7
    uint16_t m_ui16NbTargetsWarned;              // +0x1b8
    uint16_t m_pad1ba;                           // +0x1ba
    CContactToTest* m_AwakeList;                 // +0x1bc XXL2 TSPriorityList<CContactToTest*> (the head)
    CContactToTest* m_AsleepList;                // +0x1c0 XXL2 TSNodeList<CContactToTest*>
    CCollidingLife* m_WarnedCollidingLivesList;  // +0x1c4 XXL2 TSNodeList<CCollidingLife*>
    CContactToTest* m_aContactToTest;            // +0x1c8
    CCollidingLife* m_aCollidingLife;            // +0x1cc
    CCollidingLife m_BoundWarned;                // +0x1d0
    uint16_t m_ui16NbContactToTest;              // +0x1dc
    uint16_t m_ui16NbCollidingLife;              // +0x1de
    CContactSet m_aContactSet[kContactSetCount]; // +0x1e0
    CCollision m_aCollision[kContactSetCount];   // +0x1e00
    CProjectileCollision m_aProjectileCollision[kContactSetCount];  // +0x2760
    uint32_t m_ui32NbBVListingCollisionRes;      // +0x33e0
    IKSerializable* m_apBVListingCollisionRes[kBVListingCount];    // +0x33e4 IKBoundingVolume*
    float m_fDeltaTime;                          // +0x3a24
    CollisionTestFn m_IntersectionMatrix[6][6];  // +0x3a28 the collision test per volume-shape pair (OPD pointers)
};
DOTD_ASSERT_SIZE(CCollision, 0xc);
DOTD_ASSERT_SIZE(CProjectileCollision, 0x10);
DOTD_ASSERT_SIZE(CKSrvCollision, 0x3ab8);
DOTD_ASSERT_OFFSET(CKSrvCollision, m_ui32Priority, 0x08);
DOTD_ASSERT_OFFSET(CKSrvCollision, m_Infos, 0x0c);
DOTD_ASSERT_OFFSET(CKSrvCollision, m_ui16RayID, 0x10);
DOTD_ASSERT_OFFSET(CKSrvCollision, m_aPotentialEdge, 0x14);
DOTD_ASSERT_OFFSET(CKSrvCollision, m_aProjectileBoundingVolume, 0x1c);
DOTD_ASSERT_OFFSET(CKSrvCollision, m_aProjectile, 0x20);
DOTD_ASSERT_OFFSET(CKSrvCollision, m_aProjectileTarget, 0x1b0);
DOTD_ASSERT_OFFSET(CKSrvCollision, m_ui16NbProjectileTargets, 0x1b4);
DOTD_ASSERT_OFFSET(CKSrvCollision, m_ui8NbProjectileUsed, 0x1b6);
DOTD_ASSERT_OFFSET(CKSrvCollision, m_ui16NbTargetsWarned, 0x1b8);
DOTD_ASSERT_OFFSET(CKSrvCollision, m_AwakeList, 0x1bc);
DOTD_ASSERT_OFFSET(CKSrvCollision, m_AsleepList, 0x1c0);
DOTD_ASSERT_OFFSET(CKSrvCollision, m_WarnedCollidingLivesList, 0x1c4);
DOTD_ASSERT_OFFSET(CKSrvCollision, m_aContactToTest, 0x1c8);
DOTD_ASSERT_OFFSET(CKSrvCollision, m_aCollidingLife, 0x1cc);
DOTD_ASSERT_OFFSET(CKSrvCollision, m_BoundWarned, 0x1d0);
DOTD_ASSERT_OFFSET(CKSrvCollision, m_ui16NbContactToTest, 0x1dc);
DOTD_ASSERT_OFFSET(CKSrvCollision, m_ui16NbCollidingLife, 0x1de);
DOTD_ASSERT_OFFSET(CKSrvCollision, m_aContactSet, 0x1e0);
DOTD_ASSERT_OFFSET(CKSrvCollision, m_aCollision, 0x1e00);
DOTD_ASSERT_OFFSET(CKSrvCollision, m_aProjectileCollision, 0x2760);
DOTD_ASSERT_OFFSET(CKSrvCollision, m_ui32NbBVListingCollisionRes, 0x33e0);
DOTD_ASSERT_OFFSET(CKSrvCollision, m_fDeltaTime, 0x3a24);
DOTD_ASSERT_OFFSET(CKSrvCollision, m_IntersectionMatrix, 0x3a28);

// 0x00cea8ac..0x00cea8b8 (XXL2 names): the arrays the collision objects index into, set by
// InitializeService and Load.
extern float* g_pfDeltaTime;
extern CContactSet* g_aContactSet;
extern CProjectile* g_aProjectile;
extern CProjectileTarget* g_aProjectileTarget;
static_assert(sizeof(CKSrvCamera::CGroundContactDatasIn) == sizeof(CGroundContactDatasIn), "same layout");
static_assert(sizeof(CKSrvCamera::CGroundContactDatasInOut) == sizeof(CGroundContactDatasInOut), "same layout");
