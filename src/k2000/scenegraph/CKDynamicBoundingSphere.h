// CKDynamicBoundingSphere.h - a moving collision sphere (key 0x3cb, vtable 0xb13d10, size 0x50). Original
// unit: CKDynamicBoundingSphere.cpp (0xd7480-0xd7878). XXL2: K/KModules/KGL/SceneGraph/KBoundingVolume/
// CKDynamicBoundingSphere.h, the same members in the same order.
#pragma once
#include <cstdint>

#include "Renderware/rwcore/RwCamera.h"
#include "k2000/core/Layout.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/scenegraph/CKBoundingSphere.h"

class CKDynamicBoundingSphere : public CKBoundingSphere {
public:
    DOTD_CLASS_KEY(kCategoryNode, 0xf)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x993228
        return key == 0x3cb || key == 0x38b || key == 0x34b || key == 0x20b || key == 0x14b || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKDynamicBoundingSphere)

    CKDynamicBoundingSphere() {}  // inlined in 0x000d7640 CKDynamicBoundingSphere_Create (no stores of its own)
    ~CKDynamicBoundingSphere() override {}

    // vt+0x70 0x000d74d0 CKDynamicBoundingSphere_GetShapeType_maybe: a moving sphere (infos 0x20) is swept (2), else 0.
    int32_t GetShapeType() const override { return static_cast<int32_t>(((m_ba8Infos >> 5) & 1u) << 1); }

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00993328 CKDynamicBoundingSphere_Load
    // vt+0x58 0x000d76b0 CKDynamicBoundingSphere_Enqueue: CSGLeaf's (with distance 0 and no distance cull), then, while
    // the sphere follows its frame (infos bit 4), the old position kept, the move since the last position and the
    // frame's LTM position as the new last position (the swept sphere tests read them).
    void UpdateAndExtract(float maxDistanceSquared, RenderQueue** stages, IKTime* frameClock, RwCamera* camera,
                          int32_t distanceCull) override;

    CVector3 m_v3WorldMove;     // +0x2c Load: g_nullVector
    CVector3 m_v3OldPos;        // +0x38 Load: the position of the frame's LTM
    CVector3 m_v3LastWorldPos;  // +0x44 Load: the position of the frame's LTM
};
static_assert(CKDynamicBoundingSphere::kClassKey == 0x3cb, "key");
DOTD_ASSERT_SIZE(CKDynamicBoundingSphere, 0x50);
DOTD_ASSERT_OFFSET(CKDynamicBoundingSphere, m_v3WorldMove, 0x2c);
DOTD_ASSERT_OFFSET(CKDynamicBoundingSphere, m_v3OldPos, 0x38);
DOTD_ASSERT_OFFSET(CKDynamicBoundingSphere, m_v3LastWorldPos, 0x44);

// 0x00993328 CKDynamicBoundingSphere_Load (out of line from this header). No type check.
inline int32_t CKDynamicBoundingSphere::Load(IKFile* file, int32_t type) {
    CKBoundingSphere::Load(file, type);  // inlined in the original
    static const CVector3 kNullVector = {0.0f, 0.0f, 0.0f};  // g_nullVector (0x00c50d64, XXL2 name)
    m_v3WorldMove = kNullVector;
    // The position of the frame's stored LTM (RwFrame +0x80), read twice without a sync (CSGMovable::Load marks
    // the LTM dirty without computing it, so a freshly loaded node still has its identity LTM here).
    const RwV3d& pos1 = FrameLtm(m_pRwFrame)->pos;
    m_v3OldPos = CVector3{pos1.x, pos1.y, pos1.z};
    const RwV3d& pos2 = FrameLtm(m_pRwFrame)->pos;
    m_v3LastWorldPos = CVector3{pos2.x, pos2.y, pos2.z};
    return 1;
}
