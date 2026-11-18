// CClone.h - a clone of a team model (key 0x30b, vtable 0xb17ef0, size 0x30). Original unit: CClone.cpp.
// XXL2: K/KModules/KGL/SceneGraph/CCLone.h (m_ui16NumOriginal, m_ui16NbLods, m_pRwPlayerBSphere,
// m_pTeamPlayer; the file name and resource are not in the PS3 build).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/scenegraph/CNode.h"

class CClone : public CNode {
public:
    DOTD_CLASS_KEY(kCategoryNode, 0xc)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9a24c8
        return key == 0x30b || key == 0xcb || key == 0x24b || key == 0x20b || key == 0x14b || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CClone)

    CClone();  // 0x000cb7e8 CClone_Construct (inlined in 0xcb920 CClone_Create)
    ~CClone() override {}

    // vt+0x2c 0x000cb3c0 CClone_Load: CNode's, then the two u16 (one 4-byte read). No type check.
    int32_t Load(IKFile* file, int32_t type) override;
    // vt+0x30 0x000cb398 CClone_PostLoad: CSGBranch's only (not CNode's).
    int32_t PostLoad(int32_t type) override {
        CSGBranch::PostLoad(type);
        return 1;
    }

    // vt+0x10 0x000cb710 CClone_Destroy: the player's sphere pointer cleared, then CNode's.
    void Destroy() override;
    // vt+0x58 0x000cb4b0 CClone_Enqueue: unless hidden (flag 4), the player's sphere through the node frame's LTM is tested against
    // the camera (and the distance limit); a visible clone stamps itself and its player (+0xf4) with the frame counter and sets or
    // clears the player's flag 0x10 (sphere crossing the frustum); the children follow. CCloneManager_UpdateAndExtract then
    // switches the stamped players on.
    void UpdateAndExtract(float maxDistanceSquared, RenderQueue** stages, IKTime* frameClock, RwCamera* camera,
                          int32_t distanceCull) override;

    uint16_t m_ui16NumOriginal;   // +0x24
    uint16_t m_ui16NbLods;        // +0x26
    void* m_pRwPlayerBSphere;     // +0x28 RwSphere*; the constructor sets 0
    void* m_pTeamPlayer;          // +0x2c RpTeamPlayer*; the constructor sets 0
};
static_assert(CClone::kClassKey == 0x30b, "key");
DOTD_ASSERT_SIZE(CClone, 0x30);
DOTD_ASSERT_OFFSET(CClone, m_ui16NumOriginal, 0x24);
DOTD_ASSERT_OFFSET(CClone, m_ui16NbLods, 0x26);
DOTD_ASSERT_OFFSET(CClone, m_pRwPlayerBSphere, 0x28);
DOTD_ASSERT_OFFSET(CClone, m_pTeamPlayer, 0x2c);
