// CAnimatedClone.h - an animated clone of a team model (key 0x58b, vtable 0xb17dd0, size 0x70). Original unit:
// CAnimatedClone.cpp (0xc8278-0xc8b70). The animated form of CClone (k2000/scenegraph/CClone.h): a CAnimatedNode
// whose sphere (+0x68) and RpTeam player (+0x6c) the clone manager hands it (CCloneManager_Load for a player with an
// RpHAnim hierarchy, STUB(C2.9) there). No XXL2 class of this name (XXL2 CCLone's member names for the shared part).
// No level file holds one (work/level-class-keys.json): C2.8 port-final F05 ported it from the code.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/scenegraph/CAnimatedNode.h"

struct RpTeamPlayer;

class CAnimatedClone : public CAnimatedNode {
public:
    DOTD_CLASS_KEY(kCategoryNode, 0x16)  // vt+0x14 / +0x18 0x9a2420 / 0x9a2428
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9a23c0
        return key == 0x58b || key == 0x54b || key == 0xcb || key == 0x24b || key == 0x20b || key == 0x14b ||
               key == 0xc;
    }
    // 0x000c8278 _Delete (vt+0x04 when not null), 0x000c8850 _Create, 0x000c8780 _CreateArray (0x70-byte elements),
    // 0x000c86d8 _DeleteArray.
    DOTD_DECLARE_FACTORIES(CAnimatedClone)

    // Inlined in 0x000c8850 CAnimatedClone_Create (and the dead constructors 0xc8648 / 0xc8690): CAnimatedNode's
    // constructor, the vtable, then the player and the sphere null. The two halfwords are the fresh heap's (zero).
    CAnimatedClone() : m_ui16NumOriginal(0), m_ui16NbLods(0), m_pRwPlayerBSphere(nullptr), m_pTeamPlayer(nullptr) {}
    // 0x000c85e8 _Destructor / 0x000c85a0 _DeletingDestructor (0x000c8618 _BaseDestructor dead): the vtable, then
    // CAnimatedNode's (0xc99c0).
    ~CAnimatedClone() override {}

    // vt+0x10 0x000c8550 CAnimatedClone_Destroy: the hierarchy's interpolator loses its animation and the hierarchy
    // is dropped (its frame is not destroyed, unlike CAnimatedNode's), the sphere cleared, then CAnimatedNode's.
    void Destroy() override;
    // vt+0x24 0x000c82c8 CAnimatedClone_RecursiveRegistration (li r3,1): nothing registered.
    void RecursiveRegistration(int32_t /*type*/) override {}
    // vt+0x2c 0x000c88b8 CAnimatedClone_Load: CNode's (not CAnimatedNode's), then the animation index (property bit 0)
    // before the attachment reference, the two halfwords (one 4-byte read), the controller, the 0x10 words +0x4c, the
    // blend slot (properties bits 9-10 = 2) and +0x60. No bone frame list: the hierarchy is the player's. No type check.
    int32_t Load(IKFile* file, int32_t type) override;
    // vt+0x30 0x000c8500 CAnimatedClone_PostLoad: CAnimatedNode's, then 1.
    int32_t PostLoad(int32_t type) override;
    // vt+0x34 0x009a2430 (li r3,1).
    int32_t GetSerializationFlags() override { return 1; }
    // vt+0x58 0x000c8358 CAnimatedClone_vf58: unless hidden (flag 4), the pose and the culling (UpdateAnimatedNodePoseAndCull
    // with the player's sphere as the world sphere); a node with the distance-cull request (bit 7 with bit 8) beyond its
    // distance limit (+0x20, squared) from the camera is not drawn. A drawn clone stamps itself and its player (+0xf4)
    // with the render frame and sets (cull answer 1: crossing the frustum) or clears the player's flag 0x10. The frame's
    // object-sync mark (privateFlags 0x8) is cleared either way. No children or geometries are traversed.
    void UpdateAndExtract(float maxDistanceSquared, RenderQueue** stages, IKTime* frameClock, RwCamera* camera,
                          int32_t distanceCull) override;
    // vt+0x7c 0x009a2438 / vt+0x80 0x009a2440 (declared non-virtual, as CNode's slots past +0x58): the halfword +0x66.
    void SetNbLods(uint16_t value) { m_ui16NbLods = value; }
    uint16_t GetNbLods() const { return m_ui16NbLods; }

    uint16_t m_ui16NumOriginal;     // +0x64 (Load; CClone's m_ui16NumOriginal at its +0x24)
    uint16_t m_ui16NbLods;          // +0x66 (Load; vt+0x7c / +0x80)
    float* m_pRwPlayerBSphere;      // +0x68 the player's bounding sphere (RwSphere: centre, radius); null at construction
    RpTeamPlayer* m_pTeamPlayer;    // +0x6c the RpTeam player; null at construction
};
static_assert(CAnimatedClone::kClassKey == 0x58b, "key");
DOTD_ASSERT_SIZE(CAnimatedClone, 0x70);
DOTD_ASSERT_OFFSET(CAnimatedClone, m_ui16NumOriginal, 0x64);
DOTD_ASSERT_OFFSET(CAnimatedClone, m_pRwPlayerBSphere, 0x68);
DOTD_ASSERT_OFFSET(CAnimatedClone, m_pTeamPlayer, 0x6c);
