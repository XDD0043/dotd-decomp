// CKCameraConstraint.cpp - reconstructed original translation unit 0x153988-0x1579a0 (GAME_TOC1, main_toc1), 25 functions, 24 live.
// Primary class: CKCameraConstraint  key 0x7f0c  category Logic  size 0xa0  vtable 0xb130a0
// Other owners: CameraVolume (7)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x153988  CKCameraConstraint_Delete
//   [x] 0x1539d8  CameraVolume_ContainsPoint_maybe
//   [x] 0x153b10  CKCameraConstraint_SetDefaultState
//   [ ] 0x153b38  RegisterCKCameraConstraintClass
//   [ ] 0x153bb0  _GLOBAL__I_153bb0
//   [ ] 0x153bc0  CKCameraConstraint_RecursiveRegistration
//   [x] 0x153d70  CKCameraConstraint_DeleteArray
//   [x] 0x153e18  CKCameraConstraint_Create
//   [ ] 0x153e50  CKCameraConstraint_GetBoxCenter_maybe  [dead]
//   [x] 0x153ea0  CKCameraConstraint_SetGameState
//   [x] 0x153f00  CKCameraConstraint_IsEnabledFor_maybe
//   [x] 0x153f70  CKCameraConstraint_CreateArray
//   [ ] 0x154008  CKCameraConstraint_GetInfo
//   [x] 0x154070  CKCameraConstraint_PostLoad
//   [ ] 0x1540d0  CKCameraConstraint_Destroy
//   [x] 0x1540d8  CKCameraConstraint_ContainsPoint_maybe
//   [x] 0x154278  CKCameraConstraint_MessageProc
//   [x] 0x1544a0  CameraVolume_ResolveAgainstBoundary_ModeByte0_maybe
//   [x] 0x154cf0  CameraVolume_ResolveAgainstBoundary_ModeByte2_maybe
//   [x] 0x155018  CameraVolume_ComputeNearestBoundaryPoint_maybe
//   [x] 0x155440  CameraVolume_ComputeBoundaryPointForShapeBits_maybe
//   [x] 0x1558d0  CameraVolume_ResolveAgainstBoundary_ModeByte1_maybe
//   [x] 0x155c68  CKCameraConstraint_Load
//   [ ] 0x156498  CKCameraConstraint_Save
//   [x] 0x156da8  CameraVolume_ComputeConstrainedSphericalPosition_maybe
//
//   [ ] 0x9915c8  CKCameraConstraint_GetClassType  [inline]
//   [ ] 0x9915d0  CKCameraConstraint_GetClassID  [inline]
//   [ ] 0x9915d8  IKBoundingVolume_IsKindOf  [inline]
//   [ ] 0x991610  IKBoundingVolume_GetClassGroup  [inline]
//   [ ] 0x991618  IKBoundingVolume_GetClassId  [inline]
//   [ ] 0x991620  KStub_Return1_991620  [inline]
//   [ ] 0x991628  KStub_Return0_991628  [inline]
//   [ ] 0x9917c0  CKCameraConstraint_IsKindOfClass  [inline]
//   [ ] 0x9921e8  CKCameraConstraint_DeletingDestructor  [inline]
//   [ ] 0x992228  CKCameraConstraint_Destructor  [inline]
//   [ ] 0x9a7c80  CKCameraConstraint_IsActiveConstraint_maybe  [inline]
#include "k2000/logic/cameras/CKCameraConstraint.h"

#include <cfloat>
#include <cmath>
#include <cstring>

#include "crt/ppc_ops.h"
#include "crt/xsinf.h"
#include "k2000/ai/CKHkDetectorGroup.h"
#include "k2000/cameras/CKCameraClassicTrack3.h"
#include "k2000/cameras/CKSrvCamera.h"
#include "k2000/core/Stub.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/logic/CKLevel.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/misc/Engine.h"

namespace {

// The shared axes (0x00c50d34 / 0x00c50d40 / 0x00c50d4c; zero in the EBOOT's BSS, filled by static initialisers).
const CVector3 kAxisX = {1.0f, 0.0f, 0.0f};
const CVector3 kAxisY = {0.0f, 1.0f, 0.0f};
const CVector3 kAxisZ = {0.0f, 0.0f, 1.0f};
// The word at 0x00c4acb8 + 0x28 (FLT_MAX), read through a TOC pointer.
constexpr float kFloatMax = FLT_MAX;
constexpr float kMargin = 1.0e-3f;       // TOC -0x38d8 0x3a83126f (and -0x38d4 0xba83126f, its negation)
constexpr float kHalf = 0.5f;            // TOC -0x3924 0x3f000000

// 0x00010690 Math_Sqrtf (fsqrts).
inline float Sqrtf(float x) { return std::sqrt(x); }

inline bool SignBitSet(float x) {
    int32_t bits;
    std::memcpy(&bits, &x, 4);
    return bits < 0;
}
// The inlined cosf / sinf: the single-precision polynomials for a non-negative argument (by its sign bit), the
// library's cosf 0x009a11d8 / sinf 0x009a1390 of the magnitude otherwise (the sine negated).
inline float GameCosf(float x) { return SignBitSet(x) ? crt::LibCosf(-x) : crt::InlineCosf(x); }
inline float GameSinf(float x) { return SignBitSet(x) ? -crt::LibSinf(-x) : crt::InlineSinf(x); }

// The volume shape, m_unk1c bits 3-4 (0 box, 1 vertical cylinder, 2 sphere; 3 has no volume).
inline uint32_t ZoneShape(const CKCameraConstraint* zone) { return (zone->m_unk1c >> 3) & 3u; }
// The byte at +0x9c (bits 24-31 of the word, signed): the box face the last spherical constraint chose.
inline int32_t ZoneLastFace(const CKCameraConstraint* zone) { return static_cast<int8_t>(zone->m_unk9c >> 24); }
inline void SetZoneLastFace(CKCameraConstraint* zone, int32_t face) {
    zone->m_unk9c = (zone->m_unk9c & 0x00ffffffu) | (static_cast<uint32_t>(static_cast<uint8_t>(face)) << 24);
}

// The distances along `direction` from `focus` to the two planes with normal `axis` through the box's minimum and
// maximum corners (the offsets from the focus to the corners given); FLT_MAX both when the direction is parallel.
void AxisPlaneDistances(const CVector3& axis, const CVector3& direction, const CVector3& toMin, const CVector3& toMax,
                        float* tMin, float* tMax) {
    const float denom = ppc::fmadds(direction.z, axis.z, ppc::fmadds(direction.x, axis.x, direction.y * axis.y));
    if (denom == 0.0f) {
        *tMin = kFloatMax;
        *tMax = kFloatMax;
        return;
    }
    *tMin = ppc::fmadds(toMin.z, axis.z, ppc::fmadds(toMin.x, axis.x, toMin.y * axis.y)) / denom;
    *tMax = ppc::fmadds(axis.z, toMax.z, ppc::fmadds(axis.x, toMax.x, axis.y * toMax.y)) / denom;
}

}  // namespace

// 0x001539d8 CameraVolume_ContainsPoint_maybe. The box: min <= v <= max for x, z, then y (NaN is outside).
bool CameraVolume_ContainsPoint(const CKCameraConstraint* zone, const CVector3* point) {
    const float* box = zone->m_afBox;
    const float x = point->x;
    const float minX = box[3];
    if (!(minX <= x)) return false;
    const float maxX = box[0];
    if (!(x <= maxX)) return false;
    const float minZ = box[5];
    const float z = point->z;
    if (!(minZ <= z)) return false;
    const float maxZ = box[2];
    if (!(z <= maxZ)) return false;
    const float y = point->y;
    const float minY = box[4];
    if (!(minY <= y)) return false;
    const float maxY = box[1];
    if (!(y <= maxY)) return false;
    const uint32_t shape = ZoneShape(zone);
    if (shape == 1) {  // a cylinder: the x/z distance to the centre against half the x extent
        const float sumZ = minZ + maxZ;
        const float sumX = minX + maxX;
        const float extent = maxX - minX;
        float dz = ppc::fmsubs(sumZ, kHalf, z);
        float dx = ppc::fmsubs(sumX, kHalf, x);
        float radius = extent * kHalf;
        dz = dz * dz;
        radius = radius * radius;
        dx = ppc::fmadds(dx, dx, dz);
        return dx <= radius;
    }
    if (shape == 0) return true;
    if (shape != 2) return false;
    const float sumY = minY + maxY;  // a sphere of half the x extent
    const float sumX = minX + maxX;
    const float sumZ = minZ + maxZ;
    const float extent = maxX - minX;
    float dy = ppc::fmsubs(sumY, kHalf, y);
    float dx = ppc::fmsubs(sumX, kHalf, x);
    float dz = ppc::fmsubs(sumZ, kHalf, z);
    float radius = extent * kHalf;
    dy = dy * dy;
    radius = radius * radius;
    dx = ppc::fmadds(dx, dx, dy);
    dz = ppc::fmadds(dz, dz, dx);
    return dz <= radius;
}

// 0x00153b10 CKCameraConstraint_SetDefaultState: with flag 0, "on" (bit 2) takes the initial state (bit 0).
void CKCameraConstraint::SetDefaultState(int32_t flag) {
    if (flag != 0) return;
    m_unk1c = static_cast<uint8_t>((m_unk1c & 0xfbu) | ((m_unk1c & 1u) << 2));
}

// 0x00153ea0 CKCameraConstraint_SetGameState: game state 0 switches the zone on (bit 2), 1 off; returns 1.
int32_t CKCameraConstraint::SetGameState(const SApplyGameState* state) {
    const uint32_t id = state->m_ui32GameStateId;
    if (id == 0) {
        m_unk1c = static_cast<uint8_t>(m_unk1c | 4u);
    } else if (id == 1) {
        m_unk1c = static_cast<uint8_t>(m_unk1c & 0xfbu);
    }
    return 1;
}

// 0x00153f00 CKCameraConstraint_IsEnabledFor_maybe. The word at +0x24 is the sector number (it is loaded with
// ReadF32LE: the bits are the same), the word at +0x8c the mask of the sector modes.
bool CKCameraConstraint::IsEnabledFor(uint32_t sectorMode) const {
    if ((m_unk1c & 0x04u) == 0) return false;
    uint32_t sector;
    std::memcpy(&sector, &m_unk24, sizeof(sector));
    const uint32_t bit = ppc::slw(1u, sectorMode);
    if (sector != 0 && static_cast<uint32_t>(g_pEngine->m_gameManager->m_level->m_currentSector) != sector) return false;
    uint32_t mask;
    std::memcpy(&mask, &m_afUnk80[3], sizeof(mask));
    return (bit & mask) != 0;
}

// 0x00154070 CKCameraConstraint_PostLoad: the two trigger starters' PostLoad (TriggerEventList_PostLoad_maybe).
int32_t CKCameraConstraint::PostLoad(int32_t type) {
    m_tsUnk28.PostLoad(type);
    m_tsUnk30.PostLoad(type);
    return 1;
}

// 0x001540d8 CKCameraConstraint_ContainsPoint_maybe
bool CKCameraConstraint::ContainsPoint(const float* point) const {
    if (m_unk7c != nullptr) {
        // The call is m_unk7c's vt+0xc4 with the point. In LVL010's KP3 every non-null +0x7c (23) is a CKHkDetectorGroup
        // (key 0x2d82), whose vtable 0xb2f768 has 0x005bdc38 CKHkDetectorGroup_IsTriggered_maybe at vt+0xc4; IKHook
        // declares no virtual there, so the member is called directly.
        return static_cast<const CKHkDetectorGroup*>(m_unk7c)->IsTriggered(point) != 0;
    }
    const float x = point[0];
    const float minX = m_afBox[3];
    if (!(minX <= x)) return false;
    const float maxX = m_afBox[0];
    if (!(x <= maxX)) return false;
    const float minZ = m_afBox[5];
    const float z = point[2];
    if (!(minZ <= z)) return false;
    const float maxZ = m_afBox[2];
    if (!(z <= maxZ)) return false;
    const float y = point[1];
    const float minY = m_afBox[4];
    if (!(minY <= y)) return false;
    const float maxY = m_afBox[1];
    if (!(y <= maxY)) return false;
    const uint32_t shape = (m_unk1c >> 3) & 3u;
    if (shape == 1) {  // a cylinder: the x/z distance to the centre against half the x extent
        const float sumZ = minZ + maxZ;
        const float sumX = minX + maxX;
        const float extent = maxX - minX;
        float dz = ppc::fmsubs(sumZ, 0.5f, z);
        float dx = ppc::fmsubs(sumX, 0.5f, x);
        float radius = extent * 0.5f;
        dz = dz * dz;
        radius = radius * radius;
        dx = ppc::fmadds(dx, dx, dz);
        return dx <= radius;
    }
    if (shape == 0) return true;
    if (shape != 2) return false;
    const float sumY = minY + maxY;  // a sphere
    const float sumX = minX + maxX;
    const float sumZ = minZ + maxZ;
    const float extent = maxX - minX;
    float dy = ppc::fmsubs(sumY, 0.5f, y);
    float dx = ppc::fmsubs(sumX, 0.5f, x);
    float dz = ppc::fmsubs(sumZ, 0.5f, z);
    float radius = extent * 0.5f;
    dy = dy * dy;
    radius = radius * radius;
    dx = ppc::fmadds(dx, dx, dy);
    dz = ppc::fmadds(dz, dz, dx);
    return dz <= radius;
}

// 0x00154278 CKCameraConstraint_MessageProc. The camera service's active zone is its +0xe04; entering queues the
// zone's enter signals (+0x28), leaving its exit signals (+0x30).
int32_t CKCameraConstraint::MessageProc(uint16_t message, void* /*data*/) {
    CKSrvCamera* camera = static_cast<CKSrvCamera*>(g_pEngine->m_srvCamera);
    switch (message) {
        case 0x600:  // switch on
            m_unk1c = static_cast<uint8_t>(m_unk1c | 4u);
            return 0;
        case 0x601:  // switch off; the active zone leaves
            m_unk1c = static_cast<uint8_t>(m_unk1c & 0xfbu);
            if (camera->m_pActiveConstraint != this) return 0;
            QueueTriggerSignals(&m_tsUnk30);
            camera->m_pActiveConstraint = nullptr;
            return 0;
        case 0x602: {  // enter: the previous active zone leaves, this one becomes the active zone
            CKCameraConstraint* const previous = camera->m_pActiveConstraint;
            if (previous != nullptr) QueueTriggerSignals(&previous->m_tsUnk30);
            camera->m_pActiveConstraint = this;
            QueueTriggerSignals(&m_tsUnk28);
            std::memcpy(&m_unk74, &m_afUnk44[10], sizeof(uint32_t));  // +0x74 = +0x6c (lfs / stfs)
            SetZoneLastFace(this, -1);                                // the byte at +0x9c = 0xff
            return 0;
        }
        case 0x603:  // leave (only the active zone)
            if (camera->m_pActiveConstraint != this) return 0;
            QueueTriggerSignals(&m_tsUnk30);
            camera->m_pActiveConstraint = nullptr;
            // BUG(original): the exit signals are queued a second time (two calls in the code; QueueTriggerSignals
            // pushes a second pending node for each starter data not yet marked queued).
            QueueTriggerSignals(&m_tsUnk30);
            return 0;
        default:
            return 1;
    }
}

// 0x001544a0 CameraVolume_ResolveAgainstBoundary_ModeByte0_maybe (shape 0, the box; called only by
// CameraVolume_ComputeConstrainedSphericalPosition: f1 the distance, r3 the result, r4 the zone, r5 the focus, r6 the
// unconstrained orbit position, r8 the view direction (from the camera to the focus, negated: focus + direction *
// distance is the position), r9 *constrained; r7 is not used). Six candidates: the view line's distances to the six
// face planes (pulled 0.001 inwards along the line); one inside the volume stays on the line, any other is the
// unconstrained position moved back towards the focus and clamped into the box shrunk by 0.001. The cheapest one wins:
// |its distance - `distance`| plus how far it moved off the orbit position, plus 1 unless it is the face chosen last
// time (+0x9c, kept for the next call). *constrained = 1 when the winner was clamped.
static CVector3 CameraVolume_ResolveAgainstBox(float distance, CKCameraConstraint* zone, const CVector3* focus,
                                               const CVector3* position, const CVector3* direction,
                                               uint8_t* constrained) {
    const float dirY = direction->y;
    const float dirX = direction->x;
    const float minX = zone->m_afBox[3];
    const float minZ = zone->m_afBox[5];
    const float minY = zone->m_afBox[4];
    const float dirZ = direction->z;
    const float fx = focus->x;
    const float fy = focus->y;
    const float fz = focus->z;
    const float maxX = zone->m_afBox[0];
    const float maxY = zone->m_afBox[1];
    const float maxZ = zone->m_afBox[2];
    const CVector3 dir = {dirX, dirY, dirZ};
    const CVector3 toMin = {minX - fx, minY - fy, minZ - fz};
    const CVector3 toMax = {maxX - fx, maxY - fy, maxZ - fz};
    float tMinZ, tMaxZ, tMinX, tMaxX, tMinY, tMaxY;
    AxisPlaneDistances(kAxisZ, dir, toMin, toMax, &tMinZ, &tMaxZ);
    AxisPlaneDistances(kAxisX, dir, toMin, toMax, &tMinX, &tMaxX);
    AxisPlaneDistances(kAxisY, dir, toMin, toMax, &tMinY, &tMaxY);
    // BUG(original)?: the margin is the direction's component times 0.001 added to a distance along the line.
    float t[6];
    t[0] = ppc::fmadds(dirZ, kMargin, tMinZ);
    t[1] = ppc::fmadds(dirZ, -kMargin, tMaxZ);
    t[2] = ppc::fmadds(dirX, kMargin, tMinX);
    t[3] = ppc::fmadds(dirX, -kMargin, tMaxX);
    t[4] = ppc::fmadds(dirY, kMargin, tMinY);
    t[5] = ppc::fmadds(dirY, -kMargin, tMaxY);
    const float offX = dirX * distance;  // the orbit position's offset from the focus
    const float offY = dirY * distance;
    const float offZ = dirZ * distance;
    // BUG(original): the move that gets scaled down is carried from one candidate to the next (each clamped candidate
    // starts from the previous one's shortened move, not from the full offset).
    float stepX = offX;
    float stepY = offY;
    float stepZ = offZ;
    CVector3 result = *position;
    float best = kFloatMax;
    int32_t bestFace = -1;
    CVector3 points[6];
    for (int32_t i = 0; i < 6; ++i) {
        if (t[i] <= 0.0f) continue;  // ble: a NaN distance is tried
        CVector3& p = points[i];
        p.x = ppc::fmadds(dirX, t[i], fx);
        p.y = ppc::fmadds(dirY, t[i], fy);
        p.z = ppc::fmadds(dirZ, t[i], fz);
        const uint8_t inside = CameraVolume_ContainsPoint(zone, &p) ? 1 : 0;  // inlined in the original
        float deviation = 0.0f;
        if (inside == 0) {
            const float ux = offX + fx;  // the unconstrained position again
            const float uz = offZ + fz;
            const float uy = offY + fy;
            p.x = ux;
            p.z = uz;
            p.y = uy;
            // The move's scale that keeps each axis inside the box shrunk by 0.001 (the first axis caps it at 1).
            const float loX = minX + kMargin;
            const float hiX = maxX - kMargin;
            float scale;
            if (!(p.x >= loX)) {
                float r = (loX - fx) / stepX;
                if (r < 0.0f) r = -r;
                scale = r < 1.0f ? r : 1.0f;
            } else if (p.x <= hiX) {
                scale = 1.0f;
            } else {
                float r = (hiX - fx) / stepX;
                if (r < 0.0f) r = -r;
                scale = r < 1.0f ? r : 1.0f;
            }
            const float loY = minY + kMargin;
            const float hiY = maxY - kMargin;
            if (!(p.y >= loY)) {
                float r = (loY - fy) / stepY;
                if (r < 0.0f) r = -r;
                if (scale > r) scale = r;
            } else if (!(p.y <= hiY)) {
                float r = (hiY - fy) / stepY;
                if (r < 0.0f) r = -r;
                if (!(scale <= r)) scale = r;  // ble: a NaN ratio is taken
            }
            const float loZ = minZ + kMargin;
            const float hiZ = maxZ - kMargin;
            if (!(p.z >= loZ)) {
                float r = (loZ - fz) / stepZ;
                if (r < 0.0f) r = -r;
                if (r < scale) scale = r;
            } else if (!(p.z <= hiZ)) {
                float r = (hiZ - fz) / stepZ;
                if (r < 0.0f) r = -r;
                if (!(scale <= r)) scale = r;
            }
            stepX = stepX * scale;
            stepY = stepY * scale;
            stepZ = stepZ * scale;
            p.x = stepX + fx;
            p.z = stepZ + fz;
            p.y = stepY + fy;
            p.x = (loX >= p.x) ? loX : ((p.x >= hiX) ? hiX : p.x);
            p.z = (loZ >= p.z) ? loZ : ((hiZ <= p.z) ? hiZ : p.z);
            p.y = (loY >= p.y) ? loY : ((hiY <= p.y) ? hiY : p.y);
            const float dy = p.y - fy;
            const float dx = p.x - fx;
            const float dz = p.z - fz;
            t[i] = Sqrtf(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));  // its distance from the focus
            const float gy = p.y - uy;
            const float gx = p.x - ux;
            const float gz = p.z - uz;
            deviation = Sqrtf(ppc::fmadds(gz, gz, ppc::fmadds(gx, gx, gy * gy)));
        }
        float cost = t[i] - distance;
        if (cost < 0.0f) cost = -cost;
        cost = deviation + cost;
        if (ZoneLastFace(zone) != i) cost = cost + 1.0f;
        if (!(cost >= best)) {  // bge: a NaN cost wins
            best = cost;
            bestFace = i;
            *constrained = static_cast<uint8_t>(inside ^ 1);
            result = p;
        }
    }
    SetZoneLastFace(zone, bestFace);
    return result;
}

// 0x00154cf0 CameraVolume_ResolveAgainstBoundary_ModeByte2_maybe (shape 2, the sphere; the registers as the box's;
// the unconstrained position and *constrained are not used). The view line from the focus (direction taken as unit)
// meets the sphere (centre the box's, radius half its x extent): the root nearer `distance`; one touching point; no
// intersection: the line's point nearest the centre, pushed out to the sphere when it is outside.
static CVector3 CameraVolume_ResolveAgainstSphere(float distance, CKCameraConstraint* zone, const CVector3* focus,
                                                  const CVector3* /*position*/, const CVector3* direction,
                                                  uint8_t* /*constrained*/) {
    const float maxX = zone->m_afBox[0];
    const float minY = zone->m_afBox[4];
    const float maxY = zone->m_afBox[1];
    const float sumY = maxY + minY;
    const float minX = zone->m_afBox[3];
    const float sumX = maxX + minX;
    const float minZ = zone->m_afBox[5];
    const float maxZ = zone->m_afBox[2];
    const float extent = maxX - minX;
    const float fy = focus->y;
    const float sumZ = maxZ + minZ;
    const float fx = focus->x;
    const float fz = focus->z;
    const float dy = direction->y;
    const float dx = direction->x;
    const float cy = sumY * kHalf;
    const float cx = sumX * kHalf;
    const float dz = direction->z;
    const float radius = extent * kHalf;
    const float cz = sumZ * kHalf;
    const float oy = fy - cy;
    const float ox = fx - cx;
    const float radius2 = radius * radius;
    const float oz = fz - cz;
    float c = oy * oy;
    float b = oy * dy;
    c = ppc::fmadds(ox, ox, c);
    b = ppc::fmadds(ox, dx, b);
    c = ppc::fmadds(oz, oz, c);
    b = ppc::fmadds(oz, dz, b);
    c = c - radius2;
    const float twoB = b + b;
    c = c * -4.0f;  // TOC -0x38c8 0xc0800000
    const float disc = ppc::fmadds(twoB, twoB, c);
    CVector3 out;
    if (disc < 0.0f) {
        const float dd = ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy));
        float s;
        if (dd == 0.0f) {
            s = kFloatMax;
        } else {
            const float ty = cy - fy;
            const float tx = cx - fx;
            const float tz = cz - fz;
            s = ppc::fmadds(dz, tz, ppc::fmadds(dx, tx, dy * ty)) / dd;
        }
        out.y = ppc::fmadds(s, dy, fy);
        out.x = ppc::fmadds(s, dx, fx);
        out.z = ppc::fmadds(s, dz, fz);
        float vy = out.y - cy;
        float vx = out.x - cx;
        float vz = out.z - cz;
        float length = Sqrtf(ppc::fmadds(vz, vz, ppc::fmadds(vx, vx, vy * vy)));
        if (length != 0.0f) {
            const float inv = 1.0f / length;
            vz = vz * inv;
            vx = vx * inv;
            vy = vy * inv;
        } else {
            length = 0.0f;
        }
        if (length <= radius) return out;
        out.z = ppc::fmadds(radius, vz, cz);
        out.x = ppc::fmadds(radius, vx, cx);
        out.y = ppc::fmadds(radius, vy, cy);
        return out;
    }
    if (disc <= 0.0f) {  // one touching point
        const float t = twoB / -2.0f;  // TOC -0x38c4 0xc0000000
        out.z = ppc::fmadds(dz, t, fz);
        out.x = ppc::fmadds(dx, t, fx);
        out.y = ppc::fmadds(dy, t, fy);
        return out;
    }
    const float root = Sqrtf(disc);  // fsqrts
    const float t1 = (root - twoB) * kHalf;
    const float t2 = (-twoB - root) * kHalf;
    float e1 = t1 - distance;
    if (e1 < 0.0f) e1 = -e1;
    const float e2 = std::fabs(t2 - distance);
    const float t = (e1 >= e2) ? t2 : t1;
    out.z = ppc::fmadds(dz, t, fz);
    out.x = ppc::fmadds(dx, t, fx);
    out.y = ppc::fmadds(dy, t, fy);
    return out;
}

// 0x00155018 CameraVolume_ComputeNearestBoundaryPoint_maybe
CVector3 CameraVolume_ComputeNearestBoundaryPoint(const CKCameraConstraint* zone, const CVector3* from, const CVector3* to) {
    const float dx = to->x - from->x;  // the move
    const float dz = to->z - from->z;
    const float dy = to->y - from->y;
    const float maxX = zone->m_afBox[0];
    const float minX = zone->m_afBox[3];
    const float cx = (maxX + minX) * kHalf;
    const float halfX = ppc::fmsubs(maxX - minX, kHalf, kMargin);  // the half extents less 0.001
    const float minZ = zone->m_afBox[5];
    const float minY = zone->m_afBox[4];
    const float maxY = zone->m_afBox[1];
    const float maxZ = zone->m_afBox[2];
    const float halfY = ppc::fmsubs(maxY - minY, kHalf, kMargin);
    const float halfZ = ppc::fmsubs(maxZ - minZ, kHalf, kMargin);
    const float cy = (maxY + minY) * kHalf;
    const float cz = (maxZ + minZ) * kHalf;
    const float rx = to->x - cx;  // `to` from the centre
    const float ax = rx < 0.0f ? -rx : rx;
    const float ry = to->y - cy;
    const float ay = ry < 0.0f ? -ry : ry;
    const float rz = to->z - cz;
    const float az = rz < 0.0f ? -rz : rz;
    CVector3 out;
    switch (ZoneShape(zone)) {
        case 0: {  // the box: the move scaled down so that each axis stays within the shrunk half extent
            const float adx = dx < 0.0f ? -dx : dx;
            float scale = 1.0f;
            if (!(adx <= 0.0f) && !(ax <= halfX)) {
                const float r = ((adx - ax) + halfX) / adx;
                scale = r < 1.0f ? r : 1.0f;
            }
            const float ady = std::fabs(dy);
            if (!(ady <= 0.0f) && !(ay <= halfY)) {
                const float r = ((ady - ay) + halfY) / ady;
                if (scale > r) scale = r;
            }
            const float adz = std::fabs(dz);
            if (adz > 0.0f && !(az <= halfZ)) {
                const float r = ((adz - az) + halfZ) / adz;
                if (!(scale <= r)) scale = r;  // ble: a NaN ratio is taken
            }
            const float mz = scale * dz;
            const float mx = scale * dx;
            const float my = scale * dy;
            out.z = mz + from->z;
            out.x = mx + from->x;
            out.y = my + from->y;
            return out;
        }
        case 1: {  // the cylinder: the height brought inside along the move, then the x/z offset cut to the radius
            const float ady = dy < 0.0f ? -dy : dy;
            float px;
            float py;
            float pz;
            if (ady > 0.0f && !(ay <= halfY)) {
                const float k = (halfY + (ady - ay)) / ady;
                px = dx + from->x;
                pz = dz + from->z;
                py = dy * k + from->y;
            } else {
                px = to->x;
                py = to->y;
                pz = to->z;
            }
            float vx = px - cx;
            float vz = pz - cz;
            float length = Sqrtf(ppc::fmadds(vz, vz, ppc::fmadds(vx, vx, 0.0f)));
            if (length != 0.0f) {
                const float inv = 1.0f / length;
                vz = vz * inv;
                vx = vx * inv;
            } else {
                length = 0.0f;
            }
            if (!(length <= halfX)) {
                px = cx + halfX * vx;
                pz = cz + halfX * vz;
            }
            out.x = px;
            out.y = py;
            out.z = pz;
            return out;
        }
        case 2:  // the sphere
            // BUG(original)?: the offset from the centre is not normalised (ShapeBits normalises it): the result is
            // the centre plus (to - centre) times the radius.
            out.x = cx + halfX * rx;
            out.y = cy + halfX * ry;
            out.z = cz + halfX * rz;
            return out;
        default:
            // BUG(original): no volume (shape 3) reads the result from guest address 0 (a null vector); the zones of
            // the shipped levels never have it (LVL010: all 94 are boxes). Here `to` is returned unchanged.
            return *to;
    }
}

// 0x00155440 CameraVolume_ComputeBoundaryPointForShapeBits_maybe
CVector3 CameraVolume_ComputeBoundaryPointForShapeBits(const CKCameraConstraint* zone, const CVector3* from,
                                                       const CVector3* to) {
    float dx = to->x - from->x;  // the move
    float dy = to->y - from->y;
    float dz = to->z - from->z;
    const float maxX = zone->m_afBox[0];
    const float minX = zone->m_afBox[3];
    const float cx = (maxX + minX) * kHalf;
    const float halfX = ppc::fmsubs(maxX - minX, kHalf, kMargin);  // the half extents less 0.001
    const float minY = zone->m_afBox[4];
    const float minZ = zone->m_afBox[5];
    const float maxY = zone->m_afBox[1];
    const float maxZ = zone->m_afBox[2];
    const float halfY = ppc::fmsubs(maxY - minY, kHalf, kMargin);
    const float halfZ = ppc::fmsubs(maxZ - minZ, kHalf, kMargin);
    const float cy = (maxY + minY) * kHalf;
    const float cz = (maxZ + minZ) * kHalf;
    const float rx = to->x - cx;  // `to` from the centre
    const float ax = rx < 0.0f ? -rx : rx;
    const float ry = to->y - cy;
    const float ay = ry < 0.0f ? -ry : ry;
    const float rz = to->z - cz;
    const float az = rz < 0.0f ? -rz : rz;
    CVector3 out;
    switch (ZoneShape(zone)) {
        case 0: {  // the box: the move's axes along which `to` is outside are dropped
            const float adx = dx < 0.0f ? -dx : dx;
            if (!(adx == 0.0f) && !(ax <= halfX)) dx = 0.0f;
            if (!(std::fabs(dy) == 0.0f) && !(ay <= halfY)) dy = 0.0f;
            if (std::fabs(dz) != 0.0f && !(az <= halfZ)) dz = 0.0f;
            out.x = from->x + dx;
            out.y = from->y + dy;
            out.z = from->z + dz;
            return out;
        }
        case 1: {  // the cylinder: the height brought inside along the move, then the x/z offset cut to the radius
            const float ady = dy < 0.0f ? -dy : dy;
            float px = to->x;
            float py;
            float pz = to->z;
            if (ady == 0.0f) {
                py = to->y - ady;
            } else {
                py = to->y;
                if (!(ay <= halfY)) {
                    const float k = (halfY + (ady - ay)) / ady;
                    px = dx + from->x;
                    pz = dz + from->z;
                    py = dy * k + from->y;
                }
            }
            float vx = px - cx;
            float vz = pz - cz;
            float length = Sqrtf(ppc::fmadds(vz, vz, ppc::fmadds(vx, vx, 0.0f)));
            if (length != 0.0f) {
                const float inv = 1.0f / length;
                vz = vz * inv;
                vx = vx * inv;
            } else {
                length = 0.0f;
            }
            if (!(length <= halfX)) {
                px = cx + halfX * vx;
                pz = cz + halfX * vz;
            }
            out.x = px;
            out.y = py;
            out.z = pz;
            return out;
        }
        case 2: {  // the sphere: the point of the (shrunk) sphere towards `to`
            float vx = rx;
            float vy = ry;
            float vz = rz;
            const float length = Sqrtf(ppc::fmadds(rz, rz, ppc::fmadds(rx, rx, ry * ry)));
            if (length != 0.0f) {
                const float inv = 1.0f / length;
                vz = vz * inv;
                vx = vx * inv;
                vy = vy * inv;
            }
            out.z = cz + halfX * vz;
            out.x = cx + halfX * vx;
            out.y = cy + halfX * vy;
            return out;
        }
        default:
            // BUG(original): no volume (shape 3) reads the result from guest address 0 (a null vector); the zones of
            // the shipped levels never have it (LVL010: all 94 are boxes). Here `to` is returned unchanged.
            return *to;
    }
}

// 0x001558d0 CameraVolume_ResolveAgainstBoundary_ModeByte1_maybe (shape 1, the vertical cylinder; the registers as
// the box's; the unconstrained position and *constrained are not used). The view line from the focus meets the
// cylinder of radius half the x extent less 0.001 (in x/z): the root nearer `distance`, kept when within the box's
// height; otherwise the line's point nearest the axis in the horizontal view direction, its height clamped to the box
// and its x/z offset cut to the full radius.
static CVector3 CameraVolume_ResolveAgainstCylinder(float distance, CKCameraConstraint* zone, const CVector3* focus,
                                                    const CVector3* /*position*/, const CVector3* direction,
                                                    uint8_t* /*constrained*/) {
    const float maxX = zone->m_afBox[0];
    const float minX = zone->m_afBox[3];
    const float sumX = maxX + minX;
    const float minZ = zone->m_afBox[5];
    const float extentX = maxX - minX;
    const float maxZ = zone->m_afBox[2];
    const float sumZ = maxZ + minZ;
    const float fx = focus->x;
    const float dz = direction->z;
    const float fz = focus->z;
    const float dx = direction->x;
    const float cx = sumX * kHalf;
    const float maxY = zone->m_afBox[1];
    const float radius = extentX * kHalf;
    const float minY = zone->m_afBox[4];
    const float dy = direction->y;
    const float cz = sumZ * kHalf;
    const float dz2 = dz * dz;
    const float ox = fx - cx;
    const float inner = radius - kMargin;
    const float oz = fz - cz;
    const float a = ppc::fmadds(dx, dx, dz2);
    float c = ppc::fmadds(ox, ox, 0.0f);
    const float inner2 = inner * inner;
    float b = oz * dz;
    const float minus4a = a * -4.0f;  // TOC -0x38c8 0xc0800000
    c = ppc::fmadds(oz, oz, c);
    b = ppc::fmadds(ox, dx, b);
    c = c - inner2;
    const float twoB = b + b;
    const float disc = ppc::fmadds(twoB, twoB, c * minus4a);
    CVector3 out;
    if (disc < 0.0f) {
        // BUG(original): the line misses the cylinder and the roots are never computed: the code goes on with the
        // registers that would have held them, 2b and -4a.
        const float t1 = twoB;
        const float t2 = minus4a;
        float e1 = t1 - distance;
        if (e1 < 0.0f) e1 = -e1;
        const float t = (e1 >= std::fabs(t2 - distance)) ? t2 : t1;
        out.z = ppc::fmadds(t, dz, fz);
        out.y = ppc::fmadds(t, dy, focus->y);
        out.x = ppc::fmadds(t, dx, fx);
    } else if (disc <= 0.0f) {  // one touching line
        const float t = twoB / (a * -2.0f);  // TOC -0x38c4 0xc0000000
        out.y = ppc::fmadds(dy, t, focus->y);
        out.z = ppc::fmadds(dz, t, fz);
        out.x = ppc::fmadds(dx, t, fx);
    } else {
        const float root = Sqrtf(disc);  // fsqrts
        const float twoA = a + a;
        const float t1 = (root - twoB) / twoA;
        const float t2 = (-twoB - root) / twoA;
        float e1 = t1 - distance;
        if (e1 < 0.0f) e1 = -e1;
        const float t = (e1 >= std::fabs(t2 - distance)) ? t2 : t1;
        out.z = ppc::fmadds(t, dz, fz);
        out.y = ppc::fmadds(t, dy, focus->y);
        out.x = ppc::fmadds(t, dx, fx);
    }
    if (maxY >= out.y && minY <= out.y) return out;  // within the box's height
    // The horizontal view direction (unit; y stays 0, or 0 times the inverse length).
    float hx = direction->x;
    float hz = direction->z;
    float hy = 0.0f;
    const float horizontal = Sqrtf(ppc::fmadds(hz, hz, ppc::fmadds(hx, hx, 0.0f)));
    if (horizontal != 0.0f) {
        const float inv = 1.0f / horizontal;
        hz = hz * inv;
        hx = hx * inv;
        hy = inv * 0.0f;
    }
    const float dot = ppc::fmadds(hz, direction->z, ppc::fmadds(hx, direction->x, hy * direction->y));
    float s;
    if (dot == 0.0f) {
        s = kFloatMax;
    } else {
        const float toCy = ppc::fmsubs(maxY + minY, kHalf, focus->y);
        const float toCx = cx - focus->x;
        const float toCz = cz - focus->z;
        s = ppc::fmadds(toCz, hz, ppc::fmadds(hx, toCx, toCy * hy)) / dot;
    }
    out.y = ppc::fmadds(s, direction->y, focus->y);
    out.x = ppc::fmadds(s, direction->x, focus->x);
    out.z = ppc::fmadds(s, direction->z, focus->z);
    if (!(out.y <= maxY)) {
        out.y = maxY;
    } else if (!(out.y >= minY)) {
        out.y = minY;
    }
    float vx = out.x - cx;
    float vz = out.z - cz;
    float vy = 0.0f;
    float length = Sqrtf(ppc::fmadds(vz, vz, ppc::fmadds(vx, vx, 0.0f)));
    if (length != 0.0f) {
        const float inv = 1.0f / length;
        vz = vz * inv;
        vx = vx * inv;
        vy = inv * 0.0f;
    } else {
        length = 0.0f;
    }
    if (length <= radius) return out;
    const float push = radius - length;
    out.z = ppc::fmadds(vz, push, out.z);
    out.x = ppc::fmadds(vx, push, out.x);
    out.y = ppc::fmadds(vy, push, out.y);
    return out;
}

// 0x00155c68 CKCameraConstraint_Load. Every word is swapped.
int32_t CKCameraConstraint::Load(IKFile* file, int32_t type) {
    if (type == K_LEVEL_PLATEFORMS) {
        ReadU32LEWords(file, reinterpret_cast<uint32_t*>(m_afBox), 6);  // one 0x18 read
        ReadU8(file, &m_unk1c);
        ReadF32LE(file, &m_unk20);
        ReadF32LE(file, &m_unk24);
        m_tsUnk28.Load(file, K_LEVEL_PLATEFORMS);
        m_tsUnk30.Load(file, K_LEVEL_PLATEFORMS);
        ReadU8(file, &m_unk38);
        IKFile_ReadRef(file, &m_unk3c);
        IKFile_ReadRef(file, &m_unk40);
        // +0x44 +0x48 +0x60 +0x64 +0x68 +0x4c +0x50 +0x54 +0x6c +0x70
        static constexpr uint8_t kOrder44[10] = {0, 1, 7, 8, 9, 2, 3, 4, 10, 11};
        for (uint8_t i : kOrder44) ReadF32LE(file, &m_afUnk44[i]);
        ReadF32LE(file, &m_unk78);
        IKFile_ReadRef(file, &m_unk7c);
        ReadF32LE(file, &m_afUnk80[0]);
        ReadF32LE(file, &m_afUnk80[1]);
        ReadF32LE(file, &m_afUnk80[2]);
        ReadF32LE(file, &m_afUnk44[5]);  // +0x58
        ReadF32LE(file, &m_afUnk44[6]);  // +0x5c
        for (int i = 3; i < 7; ++i) ReadF32LE(file, &m_afUnk80[i]);  // +0x8c..+0x98
    }
    return 1;
}

// 0x00156da8 CameraVolume_ComputeConstrainedSphericalPosition_maybe. The orbit position (as
// CKCameraClassicTrack3::OrbitPosition: the same inlined sines and cosines in the same order); inside the zone's
// volume it is the result, otherwise the volume's resolver (by shape) places it on the view line, the direction being
// recomputed from the angles: (-sin yaw cos pitch, sin pitch, -cos yaw cos pitch). Only the box resolver sets
// *constrained (cleared first).
CVector3 CameraVolume_ComputeConstrainedSphericalPosition(float yaw, float pitch, float distance, CKCameraConstraint* zone,
                                                          const CVector3* focus, uint8_t* constrained) {
    *constrained = 0;
    CVector3 position;
    CKCameraClassicTrack3::OrbitPosition(focus, yaw, pitch, distance, &position);
    // The inlined CameraVolume_ContainsPoint (a shape-3 zone falls through to the resolvers' default: the position).
    if (CameraVolume_ContainsPoint(zone, &position)) return position;
    const float sinYaw = GameSinf(yaw);
    const float cosPitchX = GameCosf(pitch);
    CVector3 direction;
    direction.x = cosPitchX * -sinYaw;
    const float cosYaw = GameCosf(yaw);
    const float cosPitchZ = GameCosf(pitch);
    direction.z = cosPitchZ * -cosYaw;
    direction.y = GameSinf(pitch);
    switch (ZoneShape(zone)) {
        case 1: return CameraVolume_ResolveAgainstCylinder(distance, zone, focus, &position, &direction, constrained);
        case 0: return CameraVolume_ResolveAgainstBox(distance, zone, focus, &position, &direction, constrained);
        case 2: return CameraVolume_ResolveAgainstSphere(distance, zone, focus, &position, &direction, constrained);
        default: return position;
    }
}
