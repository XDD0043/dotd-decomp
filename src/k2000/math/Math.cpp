// Reconstructed original translation unit: 0x582a48-0x5854c8 (GAME_TOC2, main_toc2), 27 functions, 25 live.
// Primary owner: Math (not a registered class)
// Other owners: Vec3 (6), CKCounterNodeFx (4), GroundContact (3), SceneNode (2), ContactHistory (2), CKSrvCamera (1), Mat4 (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x582a48  Math_WrapAngleTo2Pi_maybe  [dead: its only caller, TocBridge 0x98f450, is called only from the dead IKHkHero_IntegrateLocomotionStep_maybe 0x356bb8]
//   [ ] 0x582a98  Math_EvalRampHoldDecay_2_maybe  [dead]
//   [x] 0x582b08  Math_SolveQuadratic_maybe
//   [x] 0x582bc8  Math_SmoothStep_maybe
//   [x] 0x582c18  Math_WrapAngleToPi
//   [x] 0x582c60  SceneNode_SetAlphaRecursive_maybe
//   [x] 0x582e08  GroundContact_GetWorldPoint_maybe
//   [x] 0x582f28  CKSrvCamera_GetViewDirection_maybe
//   [x] 0x582f58  CKCounterNodeFx_SetDigitTexture_2_maybe  [dead: no pointer to its descriptor 0xbe7368, no call]  (CounterNode_SetDigitTextures_2)
//   [x] 0x583028  CKCounterNodeFx_SetDigitTexture_maybe  (CounterNode_SetDigitTextures, Math.h)
//   [x] 0x5830f8  ContactHistory_Touch_maybe
//   [x] 0x5832a8  SceneNode_SetVisibleInLayer_maybe
//   [x] 0x5833c0  ContactHistory_Update_maybe
//   [x] 0x5835c8  Mat4_InterpolateSlerp_maybe  [dead: no pointer to its descriptor 0xbe73c0, no call]
//   [x] 0x583878  CKCounterNodeFx_SetDigitUVs_maybe  (CounterNode_SetDigitUVs, Math.h)
//   [x] 0x5839d8  Vec3_YawDifferenceWrapped_maybe
//   [x] 0x583a68  Math_EvalRampHoldDecay_maybe
//   [ ] 0x583af0  FxQuad_UpdateSpriteAtlasFrame_maybe  [dead]
//   [x] 0x583df8  Vec3_ProjectOntoPlaneOfVectors_maybe  [dead: no pointer to its descriptor 0xbe7428, no call]
//   [x] 0x583ef8  GroundContact_ProbeGroundPoint_maybe
//   [x] 0x5840d0  Vec3_ProjectOnPlane_maybe
//   [x] 0x5841a8  Vec3_RotateTowardByAngle_maybe
//   [x] 0x5843f0  GroundContact_SnapNavPoint_maybe
//   [x] 0x5845f8  CKCounterNodeFx_UpdateRadialGaugeGeometry_maybe  (CounterNode_UpdateRadialGauge, Math.h)
//   [x] 0x584e40  Vec3_RotateYawFlatNormalized_maybe
//   [x] 0x585110  Vec3_GenerateRadialPointsXZ_maybe
//   [x] 0x585220  Vec2_RotateNormalized_maybe  [dead: no pointer to its descriptor 0xbe7480, no call]
#include "k2000/math/Math.h"

#include "k2000/ai/CKSrvPathFinding.h"
#include "k2000/logic/CKPFGraphNode.h"

#include "k2000/hooks/GroundContact.h"
#include "k2000/logic/CKLevel.h"
#include "k2000/logic/CKSector.h"
#include "k2000/misc/Engine.h"
#include "k2000/geometry/CGeometry.h"
#include "k2000/logic/render/CMaterial.h"
#include "k2000/scenegraph/CNode.h"
#include "k2000/scenegraph/CSGBranch.h"
#include "k2000/scenegraph/CSGSectorRoot.h"
#include "k2000/system/IKTime.h"
#include "k2000/services/CKSrvCollision.h"
#include "k2000/services/ICollisionMesh.h"
#include "k2000/misc/Mat4.h"
#include "k2000/cameras/CKSrvCamera.h"
#include "k2000/math/Vec3.h"
#include "k2000/math/Quat.h"
#include "Renderware/rpworld/RpAtomic.h"
#include "Renderware/rpworld/RpGeometry.h"
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

// 0x00582c60 SceneNode_SetAlphaRecursive_maybe: with `hide`
// the node is hidden when the alpha is 0; every geometry's colour alpha set (255: blending off) and its blending
// (render property bit 11) switched to match, the properties updated (vt+0x60) when it changed. A geometry with bit
// 0x1000 whose material mode (bits 3-6) is 1..6 keeps alpha 255 without blending.
void SceneNode_SetAlphaRecursive(IKSerializable* object, uint8_t alpha, int32_t hide) {
    CNode* node = static_cast<CNode*>(object);
    if (node == nullptr) return;
    if (hide != 0) node->m_sgProperties = (node->m_sgProperties & 0xfffffffbu) | (alpha == 0 ? 4u : 0u);
    CGeometry* geometry = static_cast<CGeometry*>(node->m_lGeometryList);
    if (geometry == nullptr) return;
    if (alpha == 0xff) {
        for (; geometry != nullptr; geometry = geometry->m_pNext) {
            geometry->m_cGeometryColor[3] = alpha;
            if (((geometry->m_BitProperties >> 11) & 1u) != 0) {
                geometry->m_BitProperties &= 0xfffff7ffu;
                geometry->UpdateProperties();  // vt+0x60
            }
        }
        return;
    }
    for (; geometry != nullptr; geometry = geometry->m_pNext) {
        uint32_t blend = 1;
        uint8_t value = alpha;
        if ((geometry->m_BitProperties & 0x1000u) != 0) {
            const uint32_t mode = (static_cast<CMaterial*>(geometry->m_pMaterial)->m_baProperties >> 3) & 0xfu;
            if (mode != 0 && mode <= 6) {
                blend = 0;
                value = 0xff;
            }
        }
        geometry->m_cGeometryColor[3] = value;
        if (((geometry->m_BitProperties >> 11) & 1u) != blend) {
            geometry->m_BitProperties = (geometry->m_BitProperties & 0xfffff7ffu) | (blend << 11);
            geometry->UpdateProperties();  // vt+0x60
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
// The FreeListPool 0x00ceaa70 of the contact histories (FreeListPools_InitGlobal_maybe 0x244a08: 0x18-byte nodes, 0x200
// per chunk): released entries are taken first (last released first), a new chunk by FreeListPool_Grow 0x00244908 when
// the free list is empty; the link is the entry's first word (m_pKey) while it is free. Every user writes all the fields.
FreeListPool g_contactHistoryPool = {nullptr, nullptr, static_cast<uint32_t>(sizeof(ContactHistoryNode)), 0x200};
ContactHistoryNode* AllocContactHistoryNode() {
    return static_cast<ContactHistoryNode*>(FreeListPool_Alloc(&g_contactHistoryPool));
}
void FreeContactHistoryNode(ContactHistoryNode* node) { FreeListPool_Free(&g_contactHistoryPool, node); }
constexpr float kNoTime = -1000.0f;  // 0xc47a0000
}  // namespace

ContactHistoryNode* ContactHistory_AllocNode() { return AllocContactHistoryNode(); }
void ContactHistory_FreeNode(ContactHistoryNode* node) { FreeContactHistoryNode(node); }

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
    probe.y = static_cast<const CKPFGraphNode*>(service->m_Graph.m_apGraphNodes[point->m_i16GraphNodeIndex])->m_Sector.m_box.m_sup.y;
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
    const uint16_t sector = point->m_i16GraphNodeIndex;
    service->FindSectorForPoint(point);  // 0x001e5ca0
    if (static_cast<int16_t>(point->m_i16GraphNodeIndex) == -1) return 0;
    return static_cast<int32_t>(sector) == static_cast<int16_t>(point->m_i16GraphNodeIndex) ? 1u : 0u;
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

namespace {
// The vector normalised in place when it is not null (the original's inline Normalize: 1 / length times each part).
void NormalizeInPlace(CVector3* v) {
    const float length = std::sqrt(ppc::fmadds(v->z, v->z, ppc::fmadds(v->x, v->x, v->y * v->y)));  // Math_Sqrtf
    if (length == 0.0f) return;  // TOC2 -0x7354
    const float inverse = 1.0f / length;  // TOC2 -0x7348
    v->z = inverse * v->z;
    v->x = inverse * v->x;
    v->y = inverse * v->y;
}
}  // namespace

// 0x005841a8 Vec3_RotateTowardByAngle_maybe
void Vec3_RotateTowardByAngle(CVector3* out, CVector3* v, CVector3* axis, float radians) {
    NormalizeInPlace(v);
    NormalizeInPlace(axis);
    CMatrix34 m{};  // the identity with flags 0x20003 (the pad words are not written)
    m.m_right.x = 1.0f;
    m.m_ui32Flags = 0x20003u;
    m.m_up.y = 1.0f;
    m.m_at.z = 1.0f;
    if (Mat4_SetBasisFromUpAt(&m, v, axis) == 0) {  // 0x002400a8 (TocBridge)
        *out = *v;
        return;
    }
    Mat4_RotateLocalXDeg(radians * 57.2957802f, &m);  // TOC2 -0x72f4, 0x00241118 (TocBridge)
    *out = m.m_up;
}

// 0x00582b08 Math_SolveQuadratic_maybe: TOC2 -0x7354 (0), -0x7350 (-4), -0x734c (-2).
int32_t Math_SolveQuadratic(float a, float b, float c, float* root1, float* root2) {
    if (a == 0.0f && b == 0.0f && c == 0.0f) return 0;
    if (a == 0.0f) {
        if (b == 0.0f) return 0;
        *root1 = 0.0f;  // BUG(original): the constant 0 stored, not -c / b
        *root2 = 0.0f;
        return 1;
    }
    const float d = ppc::fmadds(b, b, (a * -4.0f) * c);
    if (d < 0.0f) return 0;  // blt
    if (!(d > 0.0f)) {      // ble 0x582b44: taken when not greater, a NaN included (one root)
        const float root = b / (a * -2.0f);
        *root1 = root;
        *root2 = root;
        return 1;
    }
    const float s = std::sqrt(d);  // fsqrts
    const float twoA = a + a;
    *root1 = (s - b) / twoA;
    *root2 = (-b - s) / twoA;
    return 2;
}

// 0x00582bc8 Math_SmoothStep_maybe: TOC2 -0x7348 (1), -0x7344 (3), -0x734c (-2).
float Math_SmoothStep(float t) {
    if (!(t < 1.0f)) return t;  // blt
    if (!(t > 0.0f)) return t;  // ble: a NaN returns t
    const float t2 = t * t;
    return ppc::fmadds(t * t2, -2.0f, t2 * 3.0f);
}

namespace {
// The game's inlined sine / cosine (crt/xsinf.h): the octant polynomials for a non-negative angle, else the library's
// cosf / sinf of the negated angle (TocBridge 0x98fde0 / 0x98fdd0), the sine negated back.
bool AngleSignBit(float angle) {
    uint32_t bits;
    std::memcpy(&bits, &angle, 4);
    return (bits >> 31) != 0;
}
float SinOf(float angle) { return AngleSignBit(angle) ? -crt::LibSinf(-angle) : crt::InlineSinf(angle); }
float CosOf(float angle) { return AngleSignBit(angle) ? crt::LibCosf(-angle) : crt::InlineCosf(angle); }

// The two texture writes of the digit setters: the material's RenderWare texture, then its property bits 0 and 1 set.
void SetGeometryTexture(CGeometry* geometry, RwTexture* texture) {
    CMaterial* material = static_cast<CMaterial*>(geometry->m_pMaterial);
    material->SetTexture(texture);  // TocBridge 0x98fe60 -> 0x000bc238 SetMaterialTexture_maybe
    material = static_cast<CMaterial*>(geometry->m_pMaterial);
    material->m_baProperties = (material->m_baProperties & 0xfffffffeu) | 1u;
    material = static_cast<CMaterial*>(geometry->m_pMaterial);
    material->m_baProperties = (material->m_baProperties & 0xfffffffdu) | 2u;  // and with -3
}
}  // namespace

// 0x00582a48 Math_WrapAngleTo2Pi_maybe: TOC2 -0x7354 (0), -0x7358 (2 pi 0x40c90fdb). Dead in the original (its only
// caller is the TocBridge 0x98f450, called only by the dead IKHkHero_IntegrateLocomotionStep_maybe 0x356bb8).
float Math_WrapAngleTo2Pi(float angle) {
    const float twoPi = 0x1.921fb6p+2f;
    if (!(angle >= 0.0f)) {  // bge: a NaN goes round once
        do {
            angle = angle + twoPi;
        } while (angle < 0.0f);
    }
    if (!(angle >= twoPi)) return angle;  // cror gt|eq
    do {
        angle = angle - twoPi;
    } while (angle >= twoPi);
    return angle;
}

// 0x00583028 CKCounterNodeFx_SetDigitTexture_maybe (CKCounterNodeFx_Start 0x577078 calls it with the counter's +0x1c /
// +0x18 textures). No null test of the node nor of its geometries.
void CounterNode_SetDigitTextures(CNode* node, RwTexture* first, RwTexture* second) {
    CGeometry* geometry = static_cast<CGeometry*>(node->m_lGeometryList);
    SetGeometryTexture(geometry, first);
    SetGeometryTexture(geometry->m_pNext, second);
}

// 0x00582f58 CKCounterNodeFx_SetDigitTexture_2_maybe: the same code as 0x00583028 (dead: no pointer to its descriptor
// 0xbe7368, no call).
void CounterNode_SetDigitTextures_2(CNode* node, RwTexture* first, RwTexture* second) {
    CGeometry* geometry = static_cast<CGeometry*>(node->m_lGeometryList);
    SetGeometryTexture(geometry, first);
    SetGeometryTexture(geometry->m_pNext, second);
}

// 0x005835c8 Mat4_InterpolateSlerp_maybe: t 0 copies a, t 1 copies b (a NaN interpolates); else the rotation slerped
// through quaternions (TocBridge Quat_FromMatrix / Quat_Slerp / Quat_ToMatrixNormalizing_maybe), the position a + t (b -
// a) (fmuls then fadds) and the flags' bit 17 (rwMATRIXINTERNALIDENTITY) cleared. Dead in the original (no pointer to its
// descriptor 0xbe73c0, no call).
void Mat4_InterpolateSlerp(float t, const CMatrix34* a, const CMatrix34* b, CMatrix34* out) {
    if (t == 0.0f) {
        *out = *a;
        return;
    }
    if (t == 1.0f) {
        *out = *b;
        return;
    }
    float qa[4];
    float qb[4];
    float q[4];
    Quat_FromMatrix(qa, reinterpret_cast<const float*>(a));
    Quat_FromMatrix(qb, reinterpret_cast<const float*>(b));
    Quat_Slerp(t, q, qa, qb);
    const float ax = a->m_pos.x;
    const float az = a->m_pos.z;
    const float dx = b->m_pos.x - ax;
    const float ay = a->m_pos.y;
    const float dz = b->m_pos.z - az;
    const float dy = b->m_pos.y - ay;
    Quat_ToMatrixNormalizing(q, out);
    out->m_pos.x = ax + t * dx;
    out->m_pos.z = az + t * dz;
    out->m_pos.y = ay + t * dy;
    out->m_ui32Flags = ppc::rlwinm(ppc::rlwinm(out->m_ui32Flags, 14, 1, 31), 18, 0, 31);
}

// 0x00583878 CKCounterNodeFx_SetDigitUVs_maybe (CKCounterNodeFx_Update 0x576758): the first geometry's four texture
// coordinates take the cell `frame` of a cols x rows atlas (row = (int)(frame / cols), column = frame - cols * row);
// the low corners through fmadds with 0 (TOC2 -0x7354), as the original. A null node or geometry does nothing.
void CounterNode_SetDigitUVs(CNode* node, uint8_t cols, uint8_t rows, uint8_t frame) {
    if (node == nullptr) return;
    CGeometry* geometry = static_cast<CGeometry*>(node->m_lGeometryList);
    if (geometry == nullptr) return;
    RpGeometryLock(geometry->m_pRpAtomic->geometry, 0x10);
    const float colsF = static_cast<float>(cols);
    const float du = 1.0f / colsF;
    const float dv = 1.0f / static_cast<float>(rows);
    const float frameF = static_cast<float>(frame);
    const float row = static_cast<float>(ppc::fctiwz(du * frameF));
    const float v0 = dv * row;
    const float column = frameF - colsF * row;
    const float v1 = v0 + dv;
    const float vLow = ppc::fmadds(dv, 0.0f, v0);
    const float u0 = du * column;
    RwTexCoords* uv = geometry->m_pRpAtomic->geometry->texCoords[0];
    uv[0].v = vLow;
    uv[1].v = vLow;
    uv[2].v = v1;
    uv[3].v = v1;
    const float u1 = u0 + du;
    const float uLow = ppc::fmadds(du, 0.0f, u0);
    uv[0].u = uLow;
    uv[1].u = u1;
    uv[2].u = u1;
    uv[3].u = uLow;
    geometry->UnlockGeometry();  // TocBridge 0x98fd70
}

// 0x00583df8 Vec3_ProjectOntoPlaneOfVectors_maybe: `p` moved onto the plane through the origin spanned by `a` and `b`:
// n = a x b, normalised unless of length 0 (beq: a NaN length normalises), p + n' * d with d = -(n . p).
// BUG(original): d is taken with the unnormalised cross product. Dead in the original (no pointer to its descriptor
// 0xbe7428, no call).
void Vec3_ProjectOntoPlaneOfVectors(CVector3* out, const CVector3* a, const CVector3* b, const CVector3* p) {
    const float ny = ppc::fmsubs(a->z, b->x, b->z * a->x);
    const float nx = ppc::fmsubs(a->y, b->z, a->z * b->y);
    const float nz = ppc::fmsubs(b->y, a->x, a->y * b->x);
    const float length = std::sqrt(ppc::fmadds(nz, nz, ppc::fmadds(nx, nx, ny * ny)));  // Math_Sqrtf 0x10690
    float unitZ = nz;
    float unitY = ny;
    float unitX = nx;
    if (!(length == 0.0f)) {
        const float inv = 1.0f / length;
        unitZ = nz * inv;
        unitX = nx * inv;
        unitY = ny * inv;
    }
    const float d = ppc::fnmadds(nz, p->z, ppc::fmadds(nx, p->x, ny * p->y));
    const float z = ppc::fmadds(unitZ, d, p->z);
    const float x = ppc::fmadds(unitX, d, p->x);
    const float y = ppc::fmadds(unitY, d, p->y);
    out->z = z;
    out->x = x;
    out->y = y;
}

// 0x005845f8 CKCounterNodeFx_UpdateRadialGaugeGeometry_maybe (CKCounterNodeFx_Update 0x576740 with 1, 1, 0): the first
// geometry is a fan: vertex 0 the centre, vertices 1.. on the unit circle from the Y axis (0x00c50d40) turned by
// (1 - fill) 2 pi, stepping fill 2 pi / (count - 2); the texture coordinates (0.5 + x / 2, 0.5 - y / 2), mapped into
// the atlas cell `frame` of cols x rows unless both are 1. The node may be null; its geometry is not tested.
void CounterNode_UpdateRadialGauge(CNode* node, float fill, uint8_t cols, uint8_t rows, uint8_t frame) {
    if (node == nullptr) return;
    CGeometry* geometry = static_cast<CGeometry*>(node->m_lGeometryList);
    const float one = 1.0f;
    const float empty = one - fill;
    RpGeometryLock(geometry->m_pRpAtomic->geometry, 0x12);
    const float twoPi = 0x1.921fb6p+2f;
    const float start = empty * twoPi;
    RpGeometry* rp = geometry->m_pRpAtomic->geometry;
    RwTexCoords* uv = rp->texCoords[0];
    RwV3d* verts = rp->morphTarget->verts;
    const float cosStart = CosOf(start);
    const float sinStart = SinOf(start);
    static const float kAxisY[2] = {0.0f, 1.0f};  // 0x00c50d40: (x, y) of the shared Y axis
    const float axisX = kAxisY[0];
    const float axisY = kAxisY[1];
    const float frameF = static_cast<float>(frame);
    const float colsF = static_cast<float>(static_cast<int32_t>(cols));
    const float rowsF = static_cast<float>(static_cast<int32_t>(rows));
    const float span = (one - empty) * twoPi;
    const float du = one / colsF;
    const float dv = one / rowsF;
    const int32_t rowIndex = ppc::fctiwz(du * frameF);
    const float count = static_cast<float>(static_cast<uint32_t>(rp->numVertices));
    const float row = static_cast<float>(rowIndex);
    const float step = (one / (count - 2.0f)) * span;
    const float column = frameF - colsF * row;
    const float cosStep = CosOf(step);
    const float sinStep = SinOf(step);
    uv[0].u = 0.5f;
    uv[0].v = 0.5f;
    if (cols != 1 || rows != 1) {
        uv[0].u = ppc::fmadds(du, 0.5f, du * column);
        uv[0].v = ppc::fmadds(dv, 0.5f, dv * row);
    }
    if (static_cast<uint32_t>(geometry->m_pRpAtomic->geometry->numVertices) <= 1u) {
        geometry->UnlockGeometry();
        return;
    }
    float y = ppc::fmsubs(cosStart, axisY, axisX * sinStart);
    float x = ppc::fmadds(cosStart, axisX, sinStart * axisY);
    if (cols == 1 && rows == 1) {
        for (uint32_t i = 1;; ++i) {
            const float u = ppc::fmadds(x, 0.5f, 0.5f);
            const float px = x + verts[0].x;
            const float py = y + verts[0].y;
            const float pz = verts[0].z + 0.0f;
            const float v = ppc::fmadds(y, -0.5f, 0.5f);
            const float minusX = -x;
            verts[i].x = px;
            verts[i].y = py;
            verts[i].z = pz;
            uv[i].u = u;
            uv[i].v = v;
            if (!(static_cast<uint32_t>(geometry->m_pRpAtomic->geometry->numVertices) > i + 1)) break;
            const float sy = sinStep * y;
            const float sx = minusX * sinStep;
            x = ppc::fmadds(x, cosStep, sy);
            y = ppc::fmadds(cosStep, y, sx);
        }
    } else {
        // The original's three loops for (cols, rows) other than (1, 1) are the same code.
        const float uOffset = du * column;
        const float vOffset = dv * row;
        for (uint32_t i = 1;; ++i) {
            float u = ppc::fmadds(x, 0.5f, 0.5f);
            float v = ppc::fmadds(y, -0.5f, 0.5f);
            const float px = verts[0].x + x;
            const float py = verts[0].y + y;
            const float pz = verts[0].z + 0.0f;
            u = ppc::fmadds(du, u, uOffset);
            v = ppc::fmadds(dv, v, vOffset);
            verts[i].x = px;
            verts[i].y = py;
            verts[i].z = pz;
            uv[i].u = u;
            uv[i].v = v;
            if (!(static_cast<uint32_t>(geometry->m_pRpAtomic->geometry->numVertices) > i + 1)) break;
            const float xs = x * sinStep;
            const float sy = sinStep * y;
            y = ppc::fmsubs(cosStep, y, xs);
            x = ppc::fmadds(cosStep, x, sy);
        }
    }
    geometry->UnlockGeometry();  // TocBridge 0x98fd70
}

// 0x00585220 Vec2_RotateNormalized_maybe: `v` (x, y) turned by `angle` (the game's inlined cosine / sine) and normalised;
// a zero vector, a zero angle or a zero result length leave it. Dead in the original (no pointer to its descriptor
// 0xbe7480, no call).
void Vec2_RotateNormalized(float angle, float* v) {
    const float x = v[0];
    if (x == 0.0f && v[1] == 0.0f) return;
    if (angle == 0.0f) return;
    const float c = CosOf(angle);
    const float s = SinOf(angle);
    const float y = v[1];
    const float newY = ppc::fmadds(s, x, c * y);
    const float newX = ppc::fmsubs(c, x, s * y);
    v[1] = newY;
    v[0] = newX;
    const float length = std::sqrt(ppc::fmadds(newX, newX, newY * newY));  // Math_Sqrtf 0x10690
    if (length == 0.0f) return;
    const float inv = 1.0f / length;
    const float ox = v[0];
    v[1] = inv * v[1];
    v[0] = inv * ox;
}
