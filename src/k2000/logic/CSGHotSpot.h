// CSGHotSpot.h - a point attached to a scene-graph node (key 0x2b4c, vtable 0xb181a0, size 0x28). Original
// unit: CSGHotSpot.cpp (0xcdf20-0xceb28). XXL2: K/KModules/KGL/SceneGraph/CSGHotSpot.h, the same members
// read in the same order (m_pParent, m_ui8BoneNumber, then position and orientation in one read).
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"
#include "k2000/math/CMatrix34.h"

class CSGBranch;
class CSGLeaf;

class CSGHotSpot : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0xad)
    DOTD_DECLARE_FACTORIES(CSGHotSpot)

    CSGHotSpot() {}  // 0x000ce280 CSGHotSpot_Create: only the vtable
    ~CSGHotSpot() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x000cdf80 CSGHotSpot_Load

    // 0x000ce2b8 CSGHotSpot_AttachVolume (not virtual): hangs the volume's node under the hot spot's node
    // (the child list without a bone, the bone's attachment group otherwise), orients it with the hot spot's
    // orientation and places it at the hot spot's position (in the node's frame). 1 when done, 0 when the
    // hot spot has no node.
    int32_t AttachVolume(CSGLeaf* volume);
    // 0x000ce790 CSGHotSpot_GetWorldPosition (not virtual): the hot spot in the world: its position through the node's
    // frame matrix (+0x50 as stored), or through its bone's matrix times it while the node was drawn this frame (or has
    // scene flag 0x2000). 0 without a node.
    int32_t GetWorldPosition(CVector3* out) const;

    CVector3 m_v3RelativePosition;        // +0x04
    float m_qUnitRelativeOrientation[4];  // +0x10 CQuaternion (x, y, z, w)
    CSGBranch* m_pParent;                 // +0x20 the node (the Ghidra struct: a CSGSectorRoot)
    uint8_t m_ui8BoneNumber;              // +0x24 0xff = none
};
static_assert(CSGHotSpot::kClassKey == 0x2b4c, "key");
DOTD_ASSERT_SIZE(CSGHotSpot, 0x28);
DOTD_ASSERT_OFFSET(CSGHotSpot, m_v3RelativePosition, 0x04);
DOTD_ASSERT_OFFSET(CSGHotSpot, m_qUnitRelativeOrientation, 0x10);
DOTD_ASSERT_OFFSET(CSGHotSpot, m_pParent, 0x20);
DOTD_ASSERT_OFFSET(CSGHotSpot, m_ui8BoneNumber, 0x24);
