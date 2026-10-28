// Reconstructed original translation unit: 0x582a48-0x5854c8 (GAME_TOC2, main_toc2), 27 functions, 25 live.
// Primary owner: Math (not a registered class)
// Other owners: Vec3 (6), CKCounterNodeFx (4), GroundContact (3), SceneNode (2), ContactHistory (2), CKSrvCamera (1), Mat4 (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x582a48  Math_WrapAngleTo2Pi_maybe
//   [ ] 0x582a98  Math_EvalRampHoldDecay_2_maybe  [dead]
//   [ ] 0x582b08  Math_SolveQuadratic_maybe
//   [ ] 0x582bc8  Math_SmoothStep_maybe
//   [x] 0x582c18  Math_WrapAngleToPi
//   [ ] 0x582c60  SceneNode_SetAlphaRecursive_maybe
//   [x] 0x582e08  GroundContact_GetWorldPoint_maybe
//   [x] 0x582f28  CKSrvCamera_GetViewDirection_maybe
//   [ ] 0x582f58  CKCounterNodeFx_SetDigitTexture_2_maybe
//   [ ] 0x583028  CKCounterNodeFx_SetDigitTexture_maybe
//   [x] 0x5830f8  ContactHistory_Touch_maybe
//   [x] 0x5832a8  SceneNode_SetVisibleInLayer_maybe
//   [x] 0x5833c0  ContactHistory_Update_maybe
//   [ ] 0x5835c8  Mat4_InterpolateSlerp_maybe
//   [ ] 0x583878  CKCounterNodeFx_SetDigitUVs_maybe
//   [x] 0x5839d8  Vec3_YawDifferenceWrapped_maybe
//   [x] 0x583a68  Math_EvalRampHoldDecay_maybe
//   [ ] 0x583af0  FxQuad_UpdateSpriteAtlasFrame_maybe  [dead]
//   [ ] 0x583df8  Vec3_ProjectOntoPlaneOfVectors_maybe
//   [x] 0x583ef8  GroundContact_ProbeGroundPoint_maybe
//   [x] 0x5840d0  Vec3_ProjectOnPlane_maybe
//   [ ] 0x5841a8  Vec3_RotateTowardByAngle_maybe
//   [x] 0x5843f0  GroundContact_SnapNavPoint_maybe
//   [ ] 0x5845f8  CKCounterNodeFx_UpdateRadialGaugeGeometry_maybe
//   [x] 0x584e40  Vec3_RotateYawFlatNormalized_maybe
//   [x] 0x585110  Vec3_GenerateRadialPointsXZ_maybe
//   [ ] 0x585220  Vec2_RotateNormalized_maybe
#include "k2000/math/Math.h"

#include "k2000/ai/CKSrvPathFinding.h"
#include "k2000/logic/CKPFGraphNode.h"

#include "k2000/hooks/GroundContact.h"
#include "k2000/logic/CKLevel.h"
#include "k2000/logic/CKSector.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/CSGBranch.h"
#include "k2000/scenegraph/CSGSectorRoot.h"
#include "k2000/system/IKTime.h"
#include "k2000/services/CKSrvCollision.h"
#include "k2000/services/ICollisionMesh.h"
#include "k2000/misc/Mat4.h"
#include "k2000/cameras/CKSrvCamera.h"
#include "k2000/math/Vec3.h"
#include "crt/ppc_ops.h"
#include "crt/xsinf.h"
#include <cmath>
#include <cstring>

// 0x00582c18 Math_WrapAngleToPi: TOC2 -0x7340 (-pi 0xc0490fdb), -0x7358 (2 pi 0x40c90fdb), -0x733c (pi 0x40490fdb).
float Math_WrapAngleToPi(float angle) {
    const float minusPi = -0x1.921fb6p+1f;
    const float twoPi = 0x1.921fb6p+2f;
    const float pi = 0x1.921fb6p+1f;
    if (!(angle >= minusPi)) {  // bge: a NaN goes round once
        do {
            angle = angle + twoPi;
        } while (angle < minusPi);
    }
    if (!(angle >= pi)) return angle;  // cror gt|eq
    do {
        angle = angle - twoPi;
    } while (angle >= pi);
    return angle;
}

// 0x005832a8 SceneNode_SetVisibleInLayer_maybe
void SceneNode_SetVisibleInLayer(CSGLeaf* node, uint32_t visible, int32_t keepWorldTransform, int32_t layer) {
    if (node == nullptr) return;
    node->m_sgProperties = (node->m_sgProperties & 0xfffffffbu) | ((visible & 0xffu) << 2);
    CSGBranch* parent = node->m_pParent;
    CSGBranch* root = static_cast<CSGBranch*>(
        static_cast<CKSector*>(g_pEngine->m_level->m_vpSectors.m_pBlock[layer])->m_pSectorRoot);
    if (parent != root) {
        if (parent != nullptr) parent->RemoveChild(node);  // vt+0x78
        if (keepWorldTransform == 0) {
            root->AddChild(node);  // vt+0x70
        } else {
            root->AddChildKeepWorldTransform(node);  // vt+0x74
        }
    }
}

// 0x00582e08 GroundContact_GetWorldPoint_maybe (GroundContact_GetWorldPoint 0x1a70e0 inlined)
void GroundContact_GetWorldPointOr(const CGroundContactDatasInOut* contact, const CVector3* fallback, CVector3* out) {
    if (contact->m_pGround == nullptr) {
        *out = *fallback;
        return;
    }
    GroundContact_GetWorldPoint(contact, out);
}

namespace {
// The FreeListPool 0x00ceaa70 of the contact histories: released entries are taken first (last released first).
ContactHistoryNode* g_contactHistoryFree = nullptr;
ContactHistoryNode* AllocContactHistoryNode() {
    ContactHistoryNode* node = g_contactHistoryFree;
    if (node == nullptr) return new ContactHistoryNode();  // FreeListPool_Grow
    g_contactHistoryFree = node->m_pNext;
    return node;
}
void FreeContactHistoryNode(ContactHistoryNode* node) {
    node->m_pNext = g_contactHistoryFree;  // the pool's link is the entry's first word in the original
    g_contactHistoryFree = node;
}
constexpr float kNoTime = -1000.0f;  // 0xc47a0000
}  // namespace

// 0x00582f28 CKSrvCamera_GetViewDirection_maybe
void CKSrvCamera_GetViewDirection(CVector3* out) {
    const CKSrvCamera* camera = static_cast<const CKSrvCamera*>(g_pEngine->m_srvCamera);
    const CVector3 direction = camera->m_v3HeadingDir;  // +0x624
    out->z = direction.z;
    out->x = direction.x;
    out->y = direction.y;
}

// 0x005839d8 Vec3_YawDifferenceWrapped_maybe
float Vec3_YawDifferenceWrapped(const CVector3* from, const CVector3* to) {
    const float yawTo = Vec3_GetYawAngleFromX(to);      // 0x00244638
    const float yawFrom = Vec3_GetYawAngleFromX(from);
    constexpr float kTwoPi = 6.28318548f;  // TOC2 -0x7358 (0x40c90fdb)
    float angle = yawTo - yawFrom;
    if (!(angle >= 0.0f)) {  // bge: a NaN takes this side too
        do {
            angle = angle + kTwoPi;
        } while (angle < 0.0f);
    }
    while (angle >= kTwoPi) angle = angle - kTwoPi;  // cror gt|eq
    return angle;
}

// 0x005830f8 ContactHistory_Touch_maybe
uint8_t ContactHistory_Touch(float time1, float time2, ContactHistoryNode** head, IKSerializable* key, IKSerializable* owner) {
    uint8_t ownerSeen = 0;
    ContactHistoryNode* node = *head;
    if (node != nullptr) {
        if (node->m_pKey == key) {
            node->m_bTouched = 1;
            return 0;
        }
        if (owner == nullptr) {
            for (node = node->m_pNext; node != nullptr; node = node->m_pNext) {
                if (node->m_pKey == key) {
                    node->m_bTouched = 1;
                    return 0;
                }
            }
        } else {
            for (;;) {
                if (node->m_pOwner == owner) ownerSeen = 1;
                node = node->m_pNext;
                if (node == nullptr) break;
                if (node->m_pKey == key) {
                    node->m_bTouched = 1;
                    return 0;
                }
            }
        }
    }
    ContactHistoryNode* entry = AllocContactHistoryNode();
    entry->m_pNext = nullptr;
    entry->m_fTime2 = time2;
    entry->m_fTime1 = time1;
    entry->m_bTouched = 1;
    entry->m_pOwner = owner;
    entry->m_pKey = key;
    entry->m_pNext = *head;
    *head = entry;
    return static_cast<uint8_t>(ownerSeen ^ 1);
}

// 0x005833c0 ContactHistory_Update_maybe
void ContactHistory_Update(ContactHistoryNode** head, IKTime* clock) {
    ContactHistoryNode* prev = nullptr;
    ContactHistoryNode* node = *head;
    while (node != nullptr) {
        if (clock != nullptr) {
            const float dt = clock->m_afDeltaTime[0];  // +0x1c
            if (node->m_fTime1 != kNoTime) node->m_fTime1 = node->m_fTime1 - dt;
            if (node->m_fTime2 != kNoTime) node->m_fTime2 = node->m_fTime2 - dt;
        } else if (!(node->m_fTime1 == kNoTime && node->m_fTime2 == kNoTime)) {
            node->m_fTime1 = kNoTime;
            node->m_fTime2 = kNoTime;
        }
        bool remove;
        if (node->m_bTouched != 0) {
            remove = node->m_fTime2 != kNoTime && node->m_fTime2 <= 0.0f;
            if (!remove) node->m_bTouched = 0;
        } else {
            remove = node->m_fTime1 == kNoTime || node->m_fTime1 <= 0.0f;
        }
        if (!remove) {
            prev = node;
            node = node->m_pNext;
            continue;
        }
        ContactHistoryNode* next = node->m_pNext;
        if (*head == node) {
            FreeContactHistoryNode(node);
            prev = nullptr;
            *head = next;
        } else {
            prev->m_pNext = next;
            FreeContactHistoryNode(node);
        }
        node = next;
    }
}

// 0x00583a68 Math_EvalRampHoldDecay_maybe
int32_t Math_EvalRampHoldDecay(float* out, float t, const float* params) {
    const float rampTime = params[0];
    const float holdTime = params[1];
    const float decayTime = params[2];
    const float offset = params[3];
    const float slope = params[4];
    const float decaySlope = params[5];
    if (!(rampTime <= t)) {
        *out = ppc::fmadds(slope, t, offset);
        return 1;
    }
    const float holdEnd = rampTime + holdTime;
    if (t < holdEnd) {
        *out = ppc::fmadds(rampTime, slope, offset);
        return 1;
    }
    if (decayTime + holdEnd <= t) return 0;
    *out = ppc::fmadds(rampTime, slope, offset) - decaySlope * (t - holdEnd);
    return 1;
}

// 0x00583ef8 GroundContact_ProbeGroundPoint_maybe
uint8_t GroundContact_ProbeGroundPoint(CGroundContactDatasInOut* contact, CVector3* point, const CGroundContactDatasIn* in) {
    CGroundContactDatasIn probe;  // without `in`: no reach above or below (0, 0), masks 1 / 8
    if (in == nullptr) {
        probe.m_fObjectHeight = 0.0f;
        probe.m_fDeltaMax = 0.0f;
    } else {
        probe.m_fDeltaMax = in->m_fDeltaMax;
        probe.m_fObjectHeight = in->m_fObjectHeight;
        probe.m_MasksOfGrdForTest[0] = in->m_MasksOfGrdForTest[0];
        probe.m_MasksOfGrdForTest[1] = in->m_MasksOfGrdForTest[1];
    }
    static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision)->GroundProbePoints(&probe, contact, &point->x, 1);
    if (contact->m_eContactStatus > 1) return 0;
    ICollisionMesh* ground = static_cast<ICollisionMesh*>(contact->m_pGround);
    if (ground != nullptr) {
        if (ground->GetClassID() == 0x13) {  // vt+0x18
            Mat4_TransformPoints(ground->GetWorldMatrix(), point, &contact->m_ProjectionOnGround, 1);  // vt+0x50
        } else {
            *point = contact->m_ProjectionOnGround;
        }
    }
    point->y = point->y - 0.01f;  // TOC2 -0x72fc
    return 1;
}

// 0x005840d0 Vec3_ProjectOnPlane_maybe
CVector3 Vec3_ProjectOnPlane(const CVector3* normal, const CVector3* v) {
    float nx = normal->x;
    float ny = normal->y;
    float nz = normal->z;
    const float length = std::sqrt(ppc::fmadds(nz, nz, ppc::fmadds(nx, nx, ny * ny)));  // Math_Sqrtf 0x10690
    if (length != 0.0f) {
        const float inverse = 1.0f / length;  // TOC2 -0x7348
        nz = nz * inverse;
        nx = nx * inverse;
        ny = ny * inverse;
    }
    const float minusDot = ppc::fnmadds(v->z, nz, ppc::fmadds(v->x, nx, v->y * ny));
    CVector3 out;
    out.z = ppc::fmadds(nz, minusDot, v->z);
    out.x = ppc::fmadds(nx, minusDot, v->x);
    out.y = ppc::fmadds(ny, minusDot, v->y);
    return out;
}

// 0x005843f0 GroundContact_SnapNavPoint_maybe: the nav point put on the ground under it (probed from its sector's
// top y: the graph node's box, no reach, masks 1 / 8; through a moving ground's matrix; less 0.01 in y), then its
// sector found again. 1 when a ground was found (status 0 or 1) and the sector is the one it had; else 0.
uint32_t GroundContact_SnapNavPoint(CGroundContactDatasInOut* contact, CPFPoint* point) {
    CKSrvPathFinding* service = static_cast<CKSrvPathFinding*>(g_pEngine->m_srvPathFinding);
    CVector3 probe;
    probe.x = point->m_position.x;
    probe.z = point->m_position.z;
    probe.y = static_cast<const CKPFGraphNode*>(service->m_Graph.m_apGraphNodes[point->m_unk0c])->m_Sector.m_box.m_sup.y;
    CGroundContactDatasIn in;
    in.m_fDeltaMax = 0.0f;
    in.m_fObjectHeight = 0.0f;
    in.m_MasksOfGrdForTest[0] = 1;
    in.m_MasksOfGrdForTest[1] = 8;
    static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision)->GroundProbePoints(&in, contact, &probe.x, 1);
    if (static_cast<int32_t>(contact->m_eContactStatus) > 1) return 0;
    ICollisionMesh* ground = static_cast<ICollisionMesh*>(contact->m_pGround);
    if (ground != nullptr) {
        if (ground->GetClassID() == 0x13) {  // vt+0x18
            Mat4_TransformPoints(ground->GetWorldMatrix(), &probe, &contact->m_ProjectionOnGround, 1);  // vt+0x50
        } else {
            probe = contact->m_ProjectionOnGround;
        }
    }
    const float y = probe.y - 0.01f;  // TOC2 -0x72fc
    point->m_position.x = probe.x;
    point->m_position.z = probe.z;
    point->m_position.y = y;
    const uint16_t sector = point->m_unk0c;
    service->FindSectorForPoint(point);  // 0x001e5ca0
    if (static_cast<int16_t>(point->m_unk0c) == -1) return 0;
    return static_cast<int32_t>(sector) == static_cast<int16_t>(point->m_unk0c) ? 1u : 0u;
}

// 0x00584e40 Vec3_RotateYawFlatNormalized_maybe
void Vec3_RotateYawFlatNormalized(float angle, CVector3* v) {
    const float x = v->x;
    if (x == 0.0f && v->y == 0.0f && v->z == 0.0f) return;  // the zero vector 0x00c50d64
    if (angle == 0.0f) return;
    int32_t angleBits;
    std::memcpy(&angleBits, &angle, 4);
    float c;
    float s;
    if (angleBits >= 0) {
        c = crt::InlineCosf(angle);
        s = crt::InlineSinf(angle);
    } else {
        c = crt::LibCosf(-angle);
        s = -crt::LibSinf(-angle);
    }
    const float z = v->z;
    const float sz = s * z;
    const float cz = c * z;
    v->y = 0.0f;
    const float newX = ppc::fmsubs(c, x, sz);
    const float newZ = ppc::fmadds(s, x, cz);
    v->x = newX;
    v->z = newZ;
    const float length = std::sqrt(ppc::fmadds(newZ, newZ, ppc::fmadds(newX, newX, 0.0f)));  // Math_Sqrtf 0x10690
    if (length == 0.0f) return;
    const float inv = 1.0f / length;
    v->z = inv * v->z;
    v->x = inv * v->x;
    v->y = inv * v->y;
}

// 0x00585110 Vec3_GenerateRadialPointsXZ_maybe
void Vec3_GenerateRadialPointsXZ(float angle, float radius, const CVector3* center, const CVector3* direction,
                                 CVector3* points, int32_t count, CVector3* lastDirection) {
    CVector3 turning = *direction;
    for (int32_t i = 0; i != count; ++i) {
        Vec3_RotateYawFlatNormalized(angle, &turning);
        const float x = ppc::fmadds(radius, turning.x, center->x);
        const float z = ppc::fmadds(radius, turning.z, center->z);
        points[i].y = center->y;
        points[i].x = x;
        points[i].z = z;
    }
    if (lastDirection != nullptr) *lastDirection = turning;
}
