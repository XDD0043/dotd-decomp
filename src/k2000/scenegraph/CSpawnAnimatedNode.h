// CSpawnAnimatedNode.h - an animated scene node spawned from a pool (key 0x90b, vtable 0xb18450, size 0xc8). Original
// unit: CSpawnAnimatedNode.cpp (0xd32b8-0xd3888). Bases CAnimatedNode (0x64) and the spawn data ISpawnNode (+0x64), as
// CSpawnNode's CNode / ISpawnNode. No level file holds one (work/level-class-keys.json); C2.8 port-rest R08 ported it
// from the code.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/ISpawnNode.h"
#include "k2000/scenegraph/CAnimatedNode.h"

class CSpawnAnimatedNode : public CAnimatedNode, public ISpawnNode {
public:
    DOTD_CLASS_KEY(kCategoryNode, 0x24)  // vt+0x14 / +0x18 0x9a2b50 / 0x9a2b58
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9a2af0
        return key == 0x90b || key == 0x54b || key == 0xcb || key == 0x24b || key == 0x20b || key == 0x14b ||
               key == 0xc;
    }
    // 0x000d32b8 _Delete, 0x000d3708 _Create, 0x000d3760 _CreateArray, 0x000d3668 _DeleteArray.
    DOTD_DECLARE_FACTORIES(CSpawnAnimatedNode)

    // Inlined in 0x000d3708 CSpawnAnimatedNode_Create: CAnimatedNode's constructor, then the vtable. The spawn data and
    // the slot are what the fresh heap leaves (zero; the PostLoad sets the slot -1).
    CSpawnAnimatedNode() : ISpawnNode() {
        m_pSpawnPool = nullptr;
        for (float& f : m_unk04) f = 0.0f;
        m_unk10 = 0.0f;
        for (float& f : m_rwBSphereCenter) f = 0.0f;
        m_rwBSphereRadius = 0.0f;
        m_ui32SectorNum = 0;
        m_unk28 = 0;
        m_pOriginalMatrix = nullptr;
        m_unk30 = nullptr;
        m_unk34 = 0;
        for (uint32_t& w : m_aUnk38) w = 0;
        for (float& f : m_aUnk50) f = 0.0f;
        m_i32AnimSlot = 0;
    }
    ~CSpawnAnimatedNode() override {}  // 0x9a2b68 / 0x9a2b98: the bases'

    // vt+0x10 0x000d3610 CSpawnAnimatedNode_Destroy: no hierarchy (+0x2c), no slot, CAnimatedNode's, then the spawn
    // data's references.
    void Destroy() override;
    // vt+0x24 0x000d3308 CSpawnAnimatedNode_RecursiveRegistration (li r3,1): nothing registered, as CSGLeaf's
    // (inherited).
    // vt+0x2c 0x000d3598 CSpawnAnimatedNode_Load: CAnimatedNode's, then (type 0) the spawn data.
    int32_t Load(IKFile* file, int32_t type) override;
    // vt+0x30 0x000d3508 CSpawnAnimatedNode_PostLoad: CAnimatedNode's, the spawn data's (the node as its movable), then
    // (type 0) no slot (+0xc4 = -1).
    int32_t PostLoad(int32_t type) override;
    // vt+0x58 0x000d33d8 CSpawnAnimatedNode_Enqueue (C2.8 port-final F05): unless hidden (flag 4), the spawn data's
    // CullAndUpdate (0xd5e20); when drawn the node is stamped with the render frame, posed from the pool's shared
    // hierarchy slot (CSpawnAnimatedNode_UpdateSharedAnim, CZoneNode.h) and its geometries enqueued with the world sphere that gave
    // (SpawnInstance_EnqueueGeometries_maybe 0xd4bf0). No children are traversed.
    void UpdateAndExtract(float maxDistanceSquared, RenderQueue** stages, IKTime* frameClock, RwCamera* camera,
                          int32_t distanceCull) override;

    int32_t m_i32AnimSlot;  // +0xc4 the pool's hierarchy slot (CSpawnAnimatedNode_UpdateSharedAnim_maybe 0xd4a60), -1 none
};
static_assert(CSpawnAnimatedNode::kClassKey == 0x90b, "key");
DOTD_ASSERT_SIZE(CSpawnAnimatedNode, 0xc8);
DOTD_ASSERT_OFFSET(CSpawnAnimatedNode, m_i32AnimSlot, 0xc4);
