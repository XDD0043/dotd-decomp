// CZoneNode.h - a scene node with detection zones (key 0x88b, vtable 0xb18580, size 0x30). Original unit:
// CZoneNode.cpp. XXL2: K/KModules/KGL/SceneGraph/CZoneNode.h (m_apDetectZone, m_ui32NbDetectors); DotD
// keeps them as a growable array (block, capacity, size).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/scenegraph/CNode.h"

class CZoneNode : public CNode {
public:
    DOTD_CLASS_KEY(kCategoryNode, 0x22)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9a2cc8
        return key == 0x88b || key == 0xcb || key == 0x24b || key == 0x20b || key == 0x14b || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CZoneNode)

    CZoneNode() : m_apDetectZone(nullptr), m_ui32Capacity(2), m_ui32NbDetectors(0) {}  // 0x000d4198 CZoneNode_Create
    ~CZoneNode() override {}
    // vt+0x10 0x000d4090 CZoneNode_Destroy: CNode's, then the zone block freed and cleared, no zone.
    void Destroy() override;
    // vt+0x24 0x000d4578 CZoneNode_RecursiveRegistration: CNode's (nothing), then type 0: every zone geometry gets
    // RecursiveRegistration(0). vt+0x70 0x0d3eb0 AddChild is CSGBranch's (a tail call).
    void RecursiveRegistration(int32_t type) override;

    // vt+0x2c 0x000d4208 CZoneNode_Load: CNode's, then (type 0) property bit 12 and the zones.
    int32_t Load(IKFile* file, int32_t type) override;
    // vt+0x58 0x000d4710 CZoneNode_Enqueue: the node is shown (flag 4 cleared) while the camera object's position (the
    // IKCamera of the renderer's camera context, its frame's modelling position) is inside one of its zones (a box,
    // shape type 0, or a sphere, type 1; the other types never match), else hidden (flag 4 set). With property bit 12
    // the background root of the node's sector (the background manager's entry for GetSectorIndex) takes the same
    // flag. Then CNode's traversal (EnqueueSceneNodeAndChildren 0xcc160) with the caller's camera.
    void UpdateAndExtract(float maxDistanceSquared, RenderQueue** stages, IKTime* frameClock, RwCamera* camera,
                          int32_t distanceCull) override;

    IKSerializable** m_apDetectZone;  // +0x24 CMultiGeometryBasic references (Mem_AllocAligned16)
    uint32_t m_ui32Capacity;          // +0x28 the block's capacity (2 when empty)
    uint32_t m_ui32NbDetectors;       // +0x2c
};
static_assert(CZoneNode::kClassKey == 0x88b, "key");
DOTD_ASSERT_SIZE(CZoneNode, 0x30);
DOTD_ASSERT_OFFSET(CZoneNode, m_apDetectZone, 0x24);
DOTD_ASSERT_OFFSET(CZoneNode, m_ui32Capacity, 0x28);
DOTD_ASSERT_OFFSET(CZoneNode, m_ui32NbDetectors, 0x2c);

// 0x000d4a60 CSpawnAnimatedNode_UpdateSharedAnim_maybe (in CZoneNode's unit; port-final F06): a slot of -1 first takes
// the spawn pool's next one (CKSpawnPool_AcquireAnimSlot_maybe 0xb6d00, stored back), then the pool poses `node` with
// it (CKSpawnPool_UpdateAnimSlot_maybe 0xb6f48). Its only caller: CSpawnAnimatedNode_Enqueue 0xd33d8 (F05 this round).
class ISpawnNode;
class CAnimatedNode;
class IKTime;
class RenderQueue;
struct RwCamera;
void CSpawnAnimatedNode_UpdateSharedAnim(ISpawnNode* spawn, CAnimatedNode* node, RenderQueue** stages, IKTime* clock,
                                         int32_t* slot, float* sphere, float* worldSphere, RwCamera* camera);
