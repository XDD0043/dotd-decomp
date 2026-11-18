// CSGAnchor.h - a scene-graph anchor (key 0x10b, vtable 0xb18010, size 0x1c). Original unit: CSGAnchor.cpp
// (0xccaa0-0xcd078). No XXL2 class of this name; the names are ours.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/scenegraph/CSGLeaf.h"

class CSGAnchor : public CSGLeaf {
public:
    DOTD_CLASS_KEY(kCategoryNode, 0x4)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9a25a0
        return key == 0x10b || key == 0x20b || key == 0x14b || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CSGAnchor)

    CSGAnchor() {}  // 0x000ccf60 CSGAnchor_Create: CSGLeaf's constructor, then the vtable
    ~CSGAnchor() override {}

    // vt+0x2c 0x000ccfb8 CSGAnchor_Load: CSGLeaf's, then (type 0) one reference.
    int32_t Load(IKFile* file, int32_t type) override;
    // vt+0x58 0x000ccaf0 CSGAnchor_vf58 (C2.8 port-final F05): CSGLeaf's traversal (distance 0, no distance cull), then
    // unless hidden (flag 4) the target's vt+0xc0 with the clock. The one anchor of the game (LVL060 STR06000) targets a
    // CKCameraBeacon (reference 0x00020582: hook class 22), whose base KBase4C2 has that slot.
    void UpdateAndExtract(float maxDistanceSquared, RenderQueue** stages, IKTime* frameClock, RwCamera* camera,
                          int32_t distanceCull) override;

    IKSerializable* m_pTarget;  // +0x18 _maybe the anchored object (a KBase4C2: LVL060's is a CKCameraBeacon)
};
static_assert(CSGAnchor::kClassKey == 0x10b, "key");
DOTD_ASSERT_SIZE(CSGAnchor, 0x1c);
DOTD_ASSERT_OFFSET(CSGAnchor, m_pTarget, 0x18);
