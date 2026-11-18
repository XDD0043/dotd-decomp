// CKProjectileTypeSplineLock.cpp - reconstructed original translation unit 0x597580-0x599ea8 (GAME_TOC2, main_toc2),
// 32 functions, 30 live.
// Primary class: CKProjectileTypeSplineLock  key 0x1d4c  category Logic  size 0x58  vtable 0xb2e530
// Other owners: Ray (1), ProjectWorldPointToNormalizedScreen (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x597580  CKProjectileTypeSplineLock_Delete  (DOTD_DECLARE_FACTORIES)
//   [x] 0x5975d0  CKProjectileTypeSplineLock_vf84  (Launch, vt+0x84)
//   [ ] 0x597628  Ray_IntersectPlane_maybe  [dead]
//   [x] 0x5976e8  CKProjectileTypeSplineLock_vfA8  (CKProjectileTypeSplineLock.h: empty)
//   [ ] 0x5976f0  RegisterCKProjectileTypeSplineLockClass
//   [ ] 0x597768  _GLOBAL__I_597768
//   [x] 0x597778  CKProjectileTypeSplineLock_OnDeath
//   [x] 0x5977a0  CKProjectileTypeSplineLock_UpdateCollision
//   [x] 0x5977c8  CKProjectileTypeSplineLock_DeleteArray  (DOTD_DECLARE_FACTORIES)
//   [x] 0x597868  CKProjectileTypeSplineLock_Create  (DOTD_DECLARE_FACTORIES; the constructor)
//   [x] 0x5978c0  CKProjectileTypeSplineLock_KillInstance  (KillProjectile)
//   [x] 0x597988  CKProjectileTypeSplineLock_IsDead
//   [x] 0x597a70  CKProjectileTypeSplineLock_ProcessDamageContacts
//   [x] 0x597c00  CKProjectileTypeSplineLock_CreateArray  (DOTD_DECLARE_FACTORIES; the constructor)
//   [x] 0x597cb8  ProjectWorldPointToNormalizedScreen_maybe  (a const member; no caller in the original)
//   [x] 0x597e68  CKProjectileTypeSplineLock_UpdateOrientation
//   [x] 0x597e90  CKProjectileTypeSplineLock_SpawnInstanceAtPoint_maybe  (SpawnTowardPoint)
//   [x] 0x598090  CKProjectileTypeSplineLock_LaunchAtPoint_maybe  (LaunchTowardPoint, vt+0xb0)
//   [x] 0x598190  CKProjectileTypeSplineLock_SpawnInstanceAtTarget_maybe  (SpawnAtTarget)
//   [x] 0x5983f8  CKProjectileTypeSplineLock_LaunchAtTarget_maybe  (LaunchAtTarget, vt+0x8c)
//   [x] 0x5984e0  CKProjectileTypeSplineLock_SpawnInstance  (SpawnAtTargetSpot)
//   [x] 0x598778  CKProjectileTypeSplineLock_LaunchInstance_maybe  (LaunchAtTargetSpot, vt+0x94)
//   [x] 0x598840  CKProjectileTypeSplineLock_ComputeSwirlOffset_maybe
//   [ ] 0x598b48  CKProjectileTypeSplineLock_ScreenPointToCameraPlane_maybe  [dead]
//   [x] 0x598cf8  CKProjectileTypeSplineLock_SpawnInstanceAtScreenPoint_maybe  (SpawnAtScreenPoint)
//   [x] 0x599020  CKProjectileTypeSplineLock_vfA0  (LaunchAtScreenPoint, vt+0xa0)
//   [x] 0x599118  CKProjectileTypeSplineLock_UpdateMotion
//   [x] 0x599958  CKProjectileTypeSplineLock_Destroy
//   [ ] 0x599980  CKProjectileTypeSplineLock_Save
//   [x] 0x599988  CKProjectileTypeSplineLock_PostLoad
//   [x] 0x5999b0  CKProjectileTypeSplineLock_RecursiveRegistration
//   [x] 0x5999d8  CKProjectileTypeSplineLock_Load
//
//   [x] 0x9cb760  CKProjectileTypeSplineLock_IsKindOfClass  [inline]  (CKProjectileTypeSplineLock.h)
//   [x] 0x9cb798  CKProjectileTypeSplineLock_GetClassType  [inline]  (DOTD_CLASS_KEY)
//   [x] 0x9cb7a0  CKProjectileTypeSplineLock_GetClassID  [inline]  (DOTD_CLASS_KEY)
//   [x] 0x9cb7a8  CKProjectileTypeSplineLock_Destructor  [inline]  (CKProjectileTypeSplineLock.h)
//   [x] 0x9cb7c8  CKProjectileTypeSplineLock_DeletingDestructor  [inline]  (CKProjectileTypeSplineLock.h)
#include "k2000/logic/ui/CKProjectileTypeSplineLock.h"

#include <cmath>
#include <cstring>

#include "Renderware/rwcore/RwCamera.h"
#include "Renderware/rwcore/RwRaster.h"
#include "crt/ppc_ops.h"
#include "crt/xsinf.h"
#include "k2000/cameras/CKSrvCamera.h"
#include "k2000/cameras/CameraContext.h"
#include "k2000/hooks/IKHook.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKProjectileDataTypeBallisticPFX.h"
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/managers/CKGraphic.h"
#include "k2000/math/Vec3.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/CKHkActorBase.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/misc/Engine.h"
#include "k2000/render/CRenderer.h"
#include "k2000/scenegraph/CSGLeaf.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/scenegraph/IKBoundingVolume.h"
#include "k2000/services/CKSrvCollision.h"

namespace {

using Record = CKProjectileTypeSplineLock::Record;

// The shared constants (zero in the EBOOT's BSS, filled by static initialisers; TOC2 -0x6cc4 / -0x6cc0 / -0x6cbc /
// -0x6d40 / -0x6d3c hold their addresses).
const CVector3 kAxisY = {0.0f, 1.0f, 0.0f};       // 0x00c50d40
const CVector3 kAxisZ = {0.0f, 0.0f, 1.0f};       // 0x00c50d4c
const CVector3 kNullVector = {0.0f, 0.0f, 0.0f};  // 0x00c50d64
constexpr float kZero = 0.0f;                     // TOC2 -0x6db8
constexpr float kOne = 1.0f;                      // TOC2 -0x6d78
constexpr float kDegToRad = 0.0174532905f;        // TOC2 -0x6d44 (0x3c8efa34)
constexpr float kRandMax = 65535.0f;              // TOC2 -0x6d74 (0x477fff00)

Record* RecordAt(const CKProjectileTypeSplineLock* pool, uint32_t index) {
    return reinterpret_cast<Record**>(pool->m_apProjectileList)[index];
}
CKProjectileDataTypeBallisticPFX* DataOf(const Record* record) {
    return static_cast<CKProjectileDataTypeBallisticPFX*>(record->m_pData);
}
CKSrvCamera* Camera() { return static_cast<CKSrvCamera*>(g_pEngine->m_srvCamera); }
IKBoundingVolume* VolumeOf(const Record* record) { return static_cast<IKBoundingVolume*>(record->m_pVolume); }
CSGLeaf* NodeOf(IKSerializable* hook) { return static_cast<CSGLeaf*>(static_cast<IKHook*>(hook)->m_pKGLObject); }

// 0x00010690 Math_Sqrtf (fsqrts; through TocBridge_Math_Sqrtf 0x0098fc10).
inline float MathSqrtf(float x) { return std::sqrt(x); }

inline bool SignBitSet(float x) {
    int32_t bits;
    std::memcpy(&bits, &x, 4);
    return bits < 0;
}
// The inlined cosf / sinf: the single-precision polynomials for a non-negative argument (by its sign bit), the
// library's cosf (0x0098fde0) / sinf (0x0098fdd0) of the magnitude otherwise (the sine negated).
inline float GameCosf(float x) { return SignBitSet(x) ? crt::LibCosf(-x) : crt::InlineCosf(x); }
inline float GameSinf(float x) { return SignBitSet(x) ? -crt::LibSinf(-x) : crt::InlineSinf(x); }

// The aim point of a target without a hot spot: message 0x400 (CKHkActorBase.h's SAimPointQuery) seeded with its node's
// LTM position, the record's hot spot index, no hot spot and the pool as the asker; the answered point (a hot spot it
// answers is not read).
CVector3 QueryAimPoint(CKProjectileTypeSplineLock* pool, const Record* p, IKSerializable* target) {
    SAimPointQuery query;
    const RwV3d& at = static_cast<CSGMovable*>(NodeOf(target))->m_pRwFrame->ltm.pos;
    query.m_point = {at.x, at.y, at.z};
    query.m_pHotSpot = nullptr;
    query.m_pHero = pool;
    query.m_ui8Index = p->m_target.m_unk0c;
    target->MessageProc(0x400, &query);  // vt+0x1c
    return query.m_point;
}

// The duration (the four spawns): with option 0x80000000 the distance from `pos` to `end` over +0x3c, else +0x34 - +0x38
// plus a draw of 2 * +0x38 (one Rand_Int through TocBridge_Rand_Int 0x0098fd10; fmadds).
float DistanceDuration(const CKProjectileTypeSplineLock* pool, const CVector3* pos, const CVector3& end) {
    const float dy = end.y - pos->y;
    const float dx = end.x - pos->x;
    const float dz = end.z - pos->z;
    return MathSqrtf(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy))) / pool->m_fCurveSpeed;
}
float DrawDuration(const CKProjectileTypeSplineLock* pool) {
    const float low = pool->m_fDurationBase - pool->m_fDurationRandom;
    const uint32_t r = static_cast<uint32_t>(Rand_Int()) & 0xffffu;
    float u = static_cast<float>(static_cast<double>(r)) / kRandMax;
    u = u + u;
    return ppc::fmadds(u, pool->m_fDurationRandom, low);
}

// The spawns' tail: the start and its direction kept, then the base's SpawnInstance without matrix nor damage object.
void SpawnTail(CKProjectileTypeSplineLock* pool, Record* p, IKSerializable* data, uint8_t index, const CVector3* pos,
               const CVector3* dir, float speed, IKSerializable* owner) {
    p->m_vStart.z = pos->z;
    p->m_vStart.x = pos->x;
    p->m_vStart.y = pos->y;
    p->m_vStartDir.z = dir->z;
    p->m_vStartDir.x = dir->x;
    p->m_vStartDir.y = dir->y;
    pool->SpawnInstance(data, index, pos, dir, speed, owner, nullptr, nullptr);  // 0x0058c948
}

// The world point under a screen point (0..1; SpawnAtScreenPoint, UpdateMotion): in pixels of the final colour raster
// (its width / height read as unsigned; 0 without it), CameraContext::ScreenPointToWorldRay (through 0x00990140), then
// the ray met with the plane +0x48 in front of the camera along its real Z axis. `degenerate` is set when the ray is
// parallel to the plane: the point is then the ray's direction x / y and an unset register (BUG(original), handled by
// the callers).
struct ScreenRay {
    float m_origin[3];
    float m_dir[3];
    float m_t;
    bool m_degenerate;
};
ScreenRay CastScreenPoint(const CKProjectileTypeSplineLock* pool, const float* screenPoint) {
    CameraContext* context = static_cast<CameraContext*>(g_pEngine->m_cameraContext);
    const CKSrvCamera* camera = Camera();
    const float sy = screenPoint[1];
    const float sx = screenPoint[0];
    float pixel[2];
    const RwRaster* raster = context->m_pFinalColorRaster;
    if (raster != nullptr) {
        const float width = static_cast<float>(static_cast<double>(static_cast<uint32_t>(raster->width)));
        const float height = static_cast<float>(static_cast<double>(static_cast<uint32_t>(raster->height)));
        pixel[0] = sx * width;
        pixel[1] = height * sy;
    } else {
        pixel[0] = sx * kZero;
        pixel[1] = kZero * sy;
    }
    float ray[6];
    context->ScreenPointToWorldRay(pixel, ray);
    ScreenRay out;
    for (int i = 0; i < 3; ++i) {
        out.m_origin[i] = ray[i];
        out.m_dir[i] = ray[3 + i];
    }
    const CVector3& axis = camera->m_v3RealAxisZ;
    const CVector3& eye = camera->m_v3RealPos;
    const float depth = pool->m_fScreenDepth;
    const float denominator =
        ppc::fmadds(out.m_dir[2], axis.z, ppc::fmadds(out.m_dir[0], axis.x, out.m_dir[1] * axis.y));
    out.m_degenerate = denominator == kZero;
    out.m_t = kZero;
    if (!out.m_degenerate) {
        const float py = ppc::fmadds(depth, axis.y, eye.y) - out.m_origin[1];
        const float px = ppc::fmadds(depth, axis.x, eye.x) - out.m_origin[0];
        const float pz = ppc::fmadds(depth, axis.z, eye.z) - out.m_origin[2];
        out.m_t = ppc::fmadds(pz, axis.z, ppc::fmadds(px, axis.x, py * axis.y)) / denominator;
    }
    return out;
}

}  // namespace

// 0x00599958 CKProjectileTypeSplineLock_Destroy
void CKProjectileTypeSplineLock::Destroy() { CKProjectileTypeBallisticPFX::Destroy(); }

// 0x005999b0 CKProjectileTypeSplineLock_RecursiveRegistration
void CKProjectileTypeSplineLock::RecursiveRegistration(int32_t type) {
    CKProjectileTypeBallisticPFX::RecursiveRegistration(type);
}

// 0x00599988 CKProjectileTypeSplineLock_PostLoad
int32_t CKProjectileTypeSplineLock::PostLoad(int32_t type) {
    CKProjectileTypeBallisticPFX::PostLoad(type);
    return 1;
}

// 0x005999d8 CKProjectileTypeSplineLock_Load: the base's Load; level data: five words (+0x34..+0x44, little-endian),
// the records rebuilt at 0xd4 bytes (each takes the node of the base's record, hidden, without a null test), the base's
// lists freed, then four more words (+0x48..+0x54). PS3: (count << 2) & 0x3fc and count * 0xd4; native sizes here.
// BUG(original): the lifetime, the scale, the fire ball, the particle effect and the camera quake the base's Load read
// are not copied, so the base's RecursiveRegistration reads the new records' unset +0x80.
int32_t CKProjectileTypeSplineLock::Load(IKFile* file, int32_t type) {
    CKProjectileTypeBallisticPFX::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadF32LE(file, &m_fDurationBase);
    ReadF32LE(file, &m_fDurationRandom);
    ReadF32LE(file, &m_fCurveSpeed);
    ReadF32LE(file, &m_fStartTangent);
    ReadF32LE(file, &m_fEndTangent);
    Record** list = static_cast<Record**>(Mem_AllocAligned16(m_ui8MaxProjectiles * static_cast<uint32_t>(sizeof(Record*))));
    Record* records = static_cast<Record*>(Mem_AllocAligned16(m_ui8MaxProjectiles * static_cast<uint32_t>(sizeof(Record))));
    if (m_ui8MaxProjectiles != 0) {
        uint32_t i = 0;
        uint8_t index = 0;
        do {
            Record* p = &records[i];
            list[i] = p;
            p->m_pOwner = nullptr;
            CSGLeaf* node = reinterpret_cast<Projectile**>(m_apProjectileList)[i]->m_pNode;
            p->m_pNode = node;
            node->m_sgProperties = (node->m_sgProperties & ~4u) | 4u;
            p->m_pVolume = nullptr;
            p->m_vPos = kNullVector;      // TOC2 -0x6cc4 0x00c50d64
            p->m_vPrevPos = kNullVector;
            p->m_vDir = kAxisZ;           // TOC2 -0x6cc0 0x00c50d4c
            p->m_fSpeed = 0.0f;
            p->m_GrdContDatasInOut.m_ui8SectorNumber = 0;
            p->m_GrdContDatasInOut.m_pGround = nullptr;
            p->m_GrdContDatasInOut.m_i32FaceIndex = -1;
            p->m_GrdContDatasInOut.m_eContactStatus = 3;
            p->m_flags64 = 0;
            p->m_fAge = 0.0f;
            p->m_ui8Index = index;
            p->m_target.m_pTarget = nullptr;
            p->m_target.m_pHotSpot = nullptr;
            p->m_target.m_unk0c = 0;
            p->m_bTracking = 1;
            ++index;
            p->m_vEndPoint = kNullVector;
            p->m_fDuration = 0.0f;
            p->m_vStart = kNullVector;
            p->m_vStartDir = kAxisY;      // TOC2 -0x6cbc 0x00c50d40
            i = index;
        } while (m_ui8MaxProjectiles > i);
    }
    Mem_FreeAligned16(m_apProjectileList);  // through TocBridge_Mem_FreeAligned16 0x0098f770
    Mem_FreeAligned16(m_aProjectiles);
    m_aProjectiles = records;
    m_apProjectileList = reinterpret_cast<void**>(list);
    ReadF32LE(file, &m_fScreenDepth);
    ReadF32LE(file, &m_fSwirlAngle);
    ReadF32LE(file, &m_fScreenScale);
    ReadF32LE(file, &m_unk54);
    return 1;
}

// 0x005977a0 CKProjectileTypeSplineLock_UpdateCollision: the base's.
void CKProjectileTypeSplineLock::UpdateCollision(uint8_t index, float dt) {
    CKProjectileTypeBallisticPFX::UpdateCollision(index, dt);
}

// 0x00597778 CKProjectileTypeSplineLock_OnDeath: the base's.
void CKProjectileTypeSplineLock::OnDeath(uint8_t index) { CKProjectileTypeBallisticPFX::OnDeath(index); }

// 0x00597e68 CKProjectileTypeSplineLock_UpdateOrientation: the base's.
void CKProjectileTypeSplineLock::UpdateOrientation(uint8_t index, float dt) {
    CKProjectileTypeBallisticPFX::UpdateOrientation(index, dt);
}

// 0x00597988 CKProjectileTypeSplineLock_IsDead: the base's; else, with a target: dead when the target is an enemy
// (IKHkEnemy 0x1402) with life bit 0x10, else when it is hidden (its node's bit 2).
uint8_t CKProjectileTypeSplineLock::IsDead(uint8_t index) {
    if (CKProjectileTypeBallisticPFX::IsDead(index) != 0) return 1;  // 0x00586830
    IKSerializable* target = RecordAt(this, index)->m_target.m_pTarget;
    if (target == nullptr) return 0;
    if (static_cast<uint8_t>(target->IsKindOfClass(0x1402)) != 0 && (static_cast<IKHook*>(target)->m_bitArray & 0x10u) != 0) {
        return 1;
    }
    return static_cast<uint8_t>((NodeOf(target)->m_sgProperties >> 2) & 1u);
}

// 0x005978c0 CKProjectileTypeSplineLock_KillInstance: 0x2897 with the target to the volume's owner (+0x24) when there
// are both; the target cleared; the base's KillInstance.
void CKProjectileTypeSplineLock::KillProjectile(uint8_t index) {
    Record* p = RecordAt(this, index);
    if (p->m_pVolume != nullptr) {
        IKSerializable* owner = VolumeOf(p)->m_pOwner;
        if (owner != nullptr) owner->MessageProc(0x2897, &p->m_target);  // vt+0x1c
    }
    p->m_target.m_unk0c = 0;
    p->m_target.m_pTarget = nullptr;
    p->m_target.m_pHotSpot = nullptr;
    CKProjectileTypeBallisticPFX::KillProjectile(index);  // 0x005886d0
}

// 0x00597a70 CKProjectileTypeSplineLock_ProcessDamageContacts: with a volume, the base's; then each collision of the
// volume with a contact (vt+0x08) whose other volume (vt+0x04) belongs to the target is a hit: not alive (bit 0
// cleared), 0x2896 with the target to the volume's owner, the volume's bit 2 (+0x18) cleared and the target cleared.
// BUG(original): the volume and its owner are read again without null tests; with no target a volume without owner
// counts as the target.
void CKProjectileTypeSplineLock::ProcessDamageContacts(uint8_t index) {
    Record* p = RecordAt(this, index);
    if (p->m_pVolume == nullptr) return;
    CKProjectileTypeBallisticPFX::ProcessDamageContacts(index);  // 0x00587d00
    for (ICollision* c = static_cast<ICollision*>(VolumeOf(p)->m_CollisionResList); c != nullptr; c = c->m_pNext) {
        if (c->HasContactSet() == 0) continue;  // vt+0x08
        IKSerializable* target = p->m_target.m_pTarget;
        if (static_cast<IKBoundingVolume*>(c->GetBoundingVolume2())->m_pOwner != target) continue;  // vt+0x04
        p->m_flags64 = static_cast<uint8_t>(p->m_flags64 & ~1u);
        VolumeOf(p)->m_pOwner->MessageProc(0x2896, &p->m_target);  // vt+0x1c
        IKBoundingVolume* volume = VolumeOf(p);
        volume->m_ba8Infos = static_cast<uint8_t>(volume->m_ba8Infos & ~4u);
        p->m_target.m_pTarget = nullptr;
        p->m_target.m_pHotSpot = nullptr;
        p->m_target.m_unk0c = 0;
    }
}

// 0x00597cb8 ProjectWorldPointToNormalizedScreen_maybe: behind the camera (the offset from its real position along its
// real Z axis below 0; blt, a NaN projects) 0; else ProjectWorldPointToScreen (through 0x00990130) into `screen` in
// pixels, divided by the final colour raster's size (read signed; 0 without it) with y flipped (1 - y), and `scale` =
// +0x48 * +0x50 over the distance to the camera; 1.
int32_t CKProjectileTypeSplineLock::ProjectWorldPointToNormalizedScreen(const CVector3* point, float* screen,
                                                                        float* scale) const {
    const CKSrvCamera* camera = Camera();
    const float oy = point->y - camera->m_v3RealPos.y;
    const float ox = point->x - camera->m_v3RealPos.x;
    const float oz = point->z - camera->m_v3RealPos.z;
    const float along = ppc::fmadds(oz, camera->m_v3RealAxisZ.z,
                                    ppc::fmadds(ox, camera->m_v3RealAxisZ.x, oy * camera->m_v3RealAxisZ.y));
    if (along < kZero) return 0;
    CameraContext* context = g_pEngine->m_graphic->m_renderer->m_cameraContext;
    const RwV3d at = {point->x, point->y, point->z};
    ProjectWorldPointToScreen(context, &at, screen, 1);  // 0x000a30c0
    float height = kZero;
    float width = kZero;
    const RwRaster* raster = context->m_pFinalColorRaster;
    if (raster != nullptr) {
        height = static_cast<float>(static_cast<double>(raster->height));
        width = static_cast<float>(static_cast<double>(raster->width));
    }
    const float y = screen[1] / height;
    screen[1] = kOne - y;
    screen[0] = screen[0] / width;
    const float cy = camera->m_v3RealPos.y - point->y;
    const float cx = camera->m_v3RealPos.x - point->x;
    const float cz = camera->m_v3RealPos.z - point->z;
    const float distance = MathSqrtf(ppc::fmadds(cz, cz, ppc::fmadds(cx, cx, cy * cy)));
    *scale = (m_fScreenDepth * m_fScreenScale) / distance;
    return 1;
}

// 0x00598840 CKProjectileTypeSplineLock_ComputeSwirlOffset_maybe (the PS3 caller also passes the end point, unread).
CVector3 CKProjectileTypeSplineLock::ComputeSwirlOffset() const {
    const float angle = m_fSwirlAngle * kDegToRad;
    const CKSrvCamera* camera = Camera();
    CVector3 out = kNullVector;  // TOC2 -0x6d40 0x00c50d64
    const float c = GameCosf(angle);
    out.z = ppc::fmadds(c, camera->m_v3FrameRight.z, out.z);
    out.x = ppc::fmadds(c, camera->m_v3FrameRight.x, out.x);
    out.y = ppc::fmadds(c, camera->m_v3FrameRight.y, out.y);
    const float s = GameSinf(angle);
    out.z = ppc::fmadds(s, camera->m_v3FrameUp.z, out.z);
    out.x = ppc::fmadds(s, camera->m_v3FrameUp.x, out.x);
    out.y = ppc::fmadds(s, camera->m_v3FrameUp.y, out.y);
    return out;
}

// 0x00597e90 CKProjectileTypeSplineLock_SpawnInstanceAtPoint_maybe: a fixed end point (not tracking).
void CKProjectileTypeSplineLock::SpawnTowardPoint(IKSerializable* data, uint8_t index, const CVector3* pos,
                                                  const CVector3* dir, float speed, IKSerializable* owner,
                                                  const CVector3* point) {
    Record* p = RecordAt(this, index);
    p->m_bTracking = 0;
    p->m_bScreenPoint = 0;
    p->m_vEndPoint = *point;
    if (static_cast<int32_t>(m_baOptions) < 0) {
        p->m_fDuration = DistanceDuration(this, pos, *point);
    } else {
        p->m_fDuration = DrawDuration(this);
    }
    SpawnTail(this, p, data, index, pos, dir, speed, owner);
}

// 0x00598190 CKProjectileTypeSplineLock_SpawnInstanceAtTarget_maybe: tracking `target` (no hot spot); the distance
// duration (option 0x80000000) only with a target, from its aim point (message 0x400), else the draw.
void CKProjectileTypeSplineLock::SpawnAtTarget(IKSerializable* data, uint8_t index, const CVector3* pos,
                                               const CVector3* dir, float speed, IKSerializable* owner,
                                               IKSerializable* target) {
    Record* p = RecordAt(this, index);
    p->m_bScreenPoint = 0;
    p->m_bTracking = 1;
    p->m_target.m_pTarget = target;
    p->m_target.m_pHotSpot = nullptr;
    p->m_target.m_unk0c = 0;
    if (static_cast<int32_t>(m_baOptions) < 0 && target != nullptr) {
        const CVector3 aim = QueryAimPoint(this, p, target);
        p->m_fDuration = DistanceDuration(this, pos, aim);
    } else {
        p->m_fDuration = DrawDuration(this);
    }
    SpawnTail(this, p, data, index, pos, dir, speed, owner);
}

// 0x005984e0 CKProjectileTypeSplineLock_SpawnInstance: tracking the target block's target and hot spot; the distance
// duration (option 0x80000000) from the hot spot's world position, else from the target's aim point (message 0x400;
// BUG(original): the target is not tested for null), else the draw.
void CKProjectileTypeSplineLock::SpawnAtTargetSpot(IKSerializable* data, uint8_t index, const CVector3* pos,
                                                   const CVector3* dir, float speed, IKSerializable* owner,
                                                   const ProjectileTarget* target) {
    Record* p = RecordAt(this, index);
    p->m_bScreenPoint = 0;
    p->m_bTracking = 1;
    p->m_target.m_pTarget = target->m_pTarget;
    p->m_target.m_unk0c = target->m_unk0c;
    p->m_target.m_pHotSpot = target->m_pHotSpot;
    if (static_cast<int32_t>(m_baOptions) < 0) {
        CVector3 aim;
        if (target->m_pHotSpot != nullptr) {
            target->m_pHotSpot->GetWorldPosition(&aim);  // 0x000ce790 through 0x0098fd50
        } else {
            aim = QueryAimPoint(this, p, target->m_pTarget);
        }
        p->m_fDuration = DistanceDuration(this, pos, aim);
    } else {
        p->m_fDuration = DrawDuration(this);
    }
    SpawnTail(this, p, data, index, pos, dir, speed, owner);
}

// 0x00598cf8 CKProjectileTypeSplineLock_SpawnInstanceAtScreenPoint_maybe: tracking the screen point; the end point its
// world point on the plane +0x48 in front of the camera (the distance duration from there with option 0x80000000).
// BUG(original): with the ray parallel to that plane the end point's x / z are the unset f29 / f28 (the caller's
// registers; 0 here) and its y the ray's direction x.
void CKProjectileTypeSplineLock::SpawnAtScreenPoint(IKSerializable* data, uint8_t index, const CVector3* pos,
                                                    const CVector3* dir, float speed, IKSerializable* owner,
                                                    const float* screenPoint) {
    Record* p = RecordAt(this, index);
    p->m_bScreenPoint = 1;
    p->m_afScreenPoint[0] = screenPoint[0];
    p->m_afScreenPoint[1] = screenPoint[1];
    p->m_bTracking = 1;
    const ScreenRay ray = CastScreenPoint(this, screenPoint);
    CVector3 end;
    if (ray.m_degenerate) {
        end.x = 0.0f;
        end.y = ray.m_dir[0];
        end.z = 0.0f;
    } else {
        end.x = ppc::fmadds(ray.m_dir[0], ray.m_t, ray.m_origin[0]);
        end.z = ppc::fmadds(ray.m_dir[2], ray.m_t, ray.m_origin[2]);
        end.y = ppc::fmadds(ray.m_dir[1], ray.m_t, ray.m_origin[1]);
    }
    p->m_vEndPoint.z = end.z;
    p->m_vEndPoint.x = end.x;
    p->m_vEndPoint.y = end.y;
    if (static_cast<int32_t>(m_baOptions) < 0) {
        p->m_fDuration = DistanceDuration(this, pos, end);
    } else {
        p->m_fDuration = DrawDuration(this);
    }
    SpawnTail(this, p, data, index, pos, dir, speed, owner);
}

// 0x005975d0 CKProjectileTypeSplineLock_vf84 (vt+0x84 Launch): vt+0x8c with no target (the matrix moved to r10).
uint8_t CKProjectileTypeSplineLock::Launch(IKSerializable* data, const CVector3* pos, const CVector3* dir, float speed,
                                           IKSerializable* owner, const RwMatrix* matrix) {
    return LaunchAtTarget(data, pos, dir, speed, owner, nullptr, matrix);  // vt+0x8c
}

// 0x005983f8 CKProjectileTypeSplineLock_LaunchAtTarget_maybe (vt+0x8c): the first free projectile at `target`; none
// free: 0x2897 to the owner with {target, no hot spot} (+0x08 / +0x10 stack garbage in the original). BUG(original): the
// owner is not tested for null.
uint8_t CKProjectileTypeSplineLock::LaunchAtTarget(IKSerializable* data, const CVector3* pos, const CVector3* dir,
                                                   float speed, IKSerializable* owner, IKSerializable* target,
                                                   const RwMatrix* /*matrix*/) {
    const uint8_t index = m_ui8NbOfActiveProjectiles;
    if (!(m_ui8MaxProjectiles > index)) {
        ProjectileTarget message{};
        message.m_unk0c = 0;
        message.m_pHotSpot = nullptr;
        message.m_pTarget = target;
        owner->MessageProc(0x2897, &message);  // vt+0x1c
        return 0;
    }
    SpawnAtTarget(data, index, pos, dir, speed, owner, target);  // 0x00598190
    m_ui8NbOfActiveProjectiles = static_cast<uint8_t>(m_ui8NbOfActiveProjectiles + 1);
    return 1;
}

// 0x00598778 CKProjectileTypeSplineLock_LaunchInstance_maybe (vt+0x94): the same with a target block; none free: 0x2897
// to the owner with the block. BUG(original): the owner is not tested for null.
uint8_t CKProjectileTypeSplineLock::LaunchAtTargetSpot(IKSerializable* data, const CVector3* pos, const CVector3* dir,
                                                       float speed, IKSerializable* owner,
                                                       const ProjectileTarget* target, const RwMatrix* /*matrix*/) {
    const uint8_t index = m_ui8NbOfActiveProjectiles;
    if (!(m_ui8MaxProjectiles > index)) {
        owner->MessageProc(0x2897, const_cast<ProjectileTarget*>(target));  // vt+0x1c
        return 0;
    }
    SpawnAtTargetSpot(data, index, pos, dir, speed, owner, target);  // 0x005984e0
    m_ui8NbOfActiveProjectiles = static_cast<uint8_t>(m_ui8NbOfActiveProjectiles + 1);
    return 1;
}

// 0x00599020 CKProjectileTypeSplineLock_vfA0 (vt+0xa0): the same toward a screen point (copied); none free: 0x2897 to
// the owner with no target. BUG(original): the owner is not tested for null.
uint8_t CKProjectileTypeSplineLock::LaunchAtScreenPoint(IKSerializable* data, const CVector3* pos, const CVector3* dir,
                                                        float speed, IKSerializable* owner, const float* screenPoint,
                                                        const RwMatrix* /*matrix*/) {
    const uint8_t index = m_ui8NbOfActiveProjectiles;
    if (!(m_ui8MaxProjectiles > index)) {
        ProjectileTarget message{};
        message.m_unk0c = 0;
        message.m_pTarget = nullptr;
        message.m_pHotSpot = nullptr;
        owner->MessageProc(0x2897, &message);  // vt+0x1c
        return 0;
    }
    const float point[2] = {screenPoint[0], screenPoint[1]};
    SpawnAtScreenPoint(data, index, pos, dir, speed, owner, point);  // 0x00598cf8
    m_ui8NbOfActiveProjectiles = static_cast<uint8_t>(m_ui8NbOfActiveProjectiles + 1);
    return 1;
}

// 0x00598090 CKProjectileTypeSplineLock_LaunchAtPoint_maybe (vt+0xb0): the same toward a point (copied); none free:
// 0x2897 to the owner with no target. BUG(original): the owner is not tested for null.
uint8_t CKProjectileTypeSplineLock::LaunchTowardPoint(IKSerializable* data, const CVector3* pos, const CVector3* dir,
                                                      float speed, IKSerializable* owner, const CVector3* target,
                                                      const RwMatrix* /*matrix*/) {
    const uint8_t index = m_ui8NbOfActiveProjectiles;
    if (!(m_ui8MaxProjectiles > index)) {
        ProjectileTarget message{};
        message.m_unk0c = 0;
        message.m_pTarget = nullptr;
        message.m_pHotSpot = nullptr;
        owner->MessageProc(0x2897, &message);  // vt+0x1c
        return 0;
    }
    const CVector3 point = *target;
    SpawnTowardPoint(data, index, pos, dir, speed, owner, &point);  // 0x00597e90
    m_ui8NbOfActiveProjectiles = static_cast<uint8_t>(m_ui8NbOfActiveProjectiles + 1);
    return 1;
}

// 0x00599118 CKProjectileTypeSplineLock_UpdateMotion. Not landed (bit 2): the previous position kept. Tracking (+0x9c)
// with a target that accepts the lock (message 0x402 answered 0): the end E is its screen point's world point, else its
// hot spot's world position, else its aim point (message 0x400); tracking without a (willing) target: the screen point,
// or ballistic (the target dropped; drag, gravity, the velocity renormalised, its length the speed, the move); not
// tracking: the fixed end point. On the curve: t = age / duration (past 1: 1, not alive), the control points start +
// +0x40 * the start direction and E + +0x44 * (the camera swirl for a screen point; the Y axis with option 0x40000000;
// else the unit (E - start) x ((E - start) x start direction) reversed: c x d), the position the cubic Bezier at t and
// the direction its step. Then vfA8 above data +0x34 (flag 0x40), the ribbon (option 0x80) and the sound once the camera
// is within data +0x48 (option 0x200000). The age advances in every case.
void CKProjectileTypeSplineLock::UpdateMotion(uint8_t index, float dt) {
    Record* p = RecordAt(this, index);
    if ((p->m_flags64 & 4u) == 0) {
        p->m_vPrevPos.x = p->m_vPos.x;
        p->m_vPrevPos.y = p->m_vPos.y;
        p->m_vPrevPos.z = p->m_vPos.z;
        IKSerializable* target = p->m_target.m_pTarget;
        uint32_t answer = 0;  // the 0x402 block (uninitialised in the original; the answer is not read)
        const bool locked = target != nullptr && target->MessageProc(0x402, &answer) == 0;  // vt+0x1c
        enum { kFixed, kScreen, kTarget, kBallistic } mode;
        if (p->m_bTracking == 0) {
            mode = kFixed;
        } else if (p->m_bScreenPoint != 0) {
            mode = kScreen;
        } else {
            mode = locked ? kTarget : kBallistic;
        }
        if (mode == kBallistic) {
            p->m_target.m_pTarget = nullptr;
            CKProjectileDataTypeBallisticPFX* data = DataOf(p);
            const float speed0 = p->m_fSpeed;
            const float slowed = speed0 - dt * (speed0 * data->m_unk24);
            p->m_fSpeed = slowed;
            const float vx = slowed * p->m_vDir.x;
            const float vz = slowed * p->m_vDir.z;
            const float vy = slowed * p->m_vDir.y;
            p->m_vDir.x = vx;
            p->m_vDir.z = vz;
            p->m_vDir.y = vy;
            p->m_vDir.y = p->m_vDir.y - dt * DataOf(p)->m_unk1c;
            float length = MathSqrtf(ppc::fmadds(vz, vz, ppc::fmadds(vx, vx, p->m_vDir.y * p->m_vDir.y)));
            if (length != kZero) {
                const float inverse = kOne / length;
                const float nz = inverse * p->m_vDir.z;
                const float nx = inverse * p->m_vDir.x;
                const float ny = inverse * p->m_vDir.y;
                p->m_vDir.z = nz;
                p->m_vDir.x = nx;
                p->m_vDir.y = ny;
            } else {
                length = kZero;
            }
            const float step = length * dt;
            p->m_fSpeed = length;
            const float posZ = ppc::fmadds(step, p->m_vDir.z, p->m_vPos.z);
            const float posX = ppc::fmadds(step, p->m_vDir.x, p->m_vPos.x);
            const float posY = ppc::fmadds(step, p->m_vDir.y, p->m_vPos.y);
            p->m_vPos.z = posZ;
            p->m_vPos.x = posX;
            p->m_vPos.y = posY;
        } else {
            CVector3 end;
            if (mode == kFixed) {
                end = p->m_vEndPoint;
            } else if (mode == kScreen) {
                // BUG(original): a ray parallel to the plane leaves the end's z the unset f29 (0 here), x / y the ray's
                // direction x / y.
                const ScreenRay ray = CastScreenPoint(this, p->m_afScreenPoint);
                float ex;
                float ey;
                float ez;
                if (ray.m_degenerate) {
                    ex = ray.m_dir[0];
                    ey = ray.m_dir[1];
                    ez = 0.0f;
                } else {
                    ez = ppc::fmadds(ray.m_dir[2], ray.m_t, ray.m_origin[2]);
                    ex = ppc::fmadds(ray.m_dir[0], ray.m_t, ray.m_origin[0]);
                    ey = ppc::fmadds(ray.m_dir[1], ray.m_t, ray.m_origin[1]);
                }
                // The end leads the screen point's world point by its last move (E + (E - previous)).
                const float mx = ex - p->m_vEndPoint.x;
                const float my = ey - p->m_vEndPoint.y;
                const float mz = ez - p->m_vEndPoint.z;
                p->m_vEndPoint.x = ex;
                p->m_vEndPoint.z = ez;
                p->m_vEndPoint.y = ey;
                end.x = ex + mx;
                end.y = ey + my;
                end.z = ez + mz;
            } else if (p->m_target.m_pHotSpot != nullptr) {
                p->m_target.m_pHotSpot->GetWorldPosition(&end);  // 0x000ce790 through 0x0098fd50
            } else {
                end = QueryAimPoint(this, p, p->m_target.m_pTarget);
            }
            float t = p->m_fAge / p->m_fDuration;
            if (!(t <= kOne)) {  // ble: a NaN ends the curve
                t = kOne;
                p->m_flags64 = static_cast<uint8_t>(p->m_flags64 & ~1u);
            }
            const CVector3& start = p->m_vStart;
            const float lead = m_fStartTangent;
            CVector3 control1;
            control1.x = ppc::fmadds(lead, p->m_vStartDir.x, start.x);
            control1.z = ppc::fmadds(lead, p->m_vStartDir.z, start.z);
            control1.y = ppc::fmadds(lead, p->m_vStartDir.y, start.y);
            CVector3 control2;
            if (p->m_bScreenPoint != 0) {
                const CVector3 swirl = ComputeSwirlOffset();  // 0x00598840
                const float k = m_fEndTangent;
                control2.x = ppc::fmadds(k, swirl.x, end.x);
                control2.z = ppc::fmadds(k, swirl.z, end.z);
                control2.y = ppc::fmadds(k, swirl.y, end.y);
            } else if ((m_baOptions & 0x40000000u) != 0) {
                const float k = m_fEndTangent;
                control2.z = ppc::fmadds(k, kAxisY.z, end.z);  // TOC2 -0x6d3c 0x00c50d40
                control2.x = ppc::fmadds(k, kAxisY.x, end.x);
                control2.y = ppc::fmadds(k, kAxisY.y, end.y);
            } else {
                const float dz = end.z - start.z;
                const float dy = end.y - start.y;
                const float dx = end.x - start.x;
                const CVector3& sd = p->m_vStartDir;
                // c = d x start direction, then n = c x d.
                const float cx = ppc::fmsubs(dy, sd.z, dz * sd.y);
                const float cz = ppc::fmsubs(dx, sd.y, dy * sd.x);
                const float cy = ppc::fmsubs(dz, sd.x, dx * sd.z);
                float ny = ppc::fmsubs(dx, cz, dz * cx);
                float nx = ppc::fmsubs(dz, cy, dy * cz);
                float nz = ppc::fmsubs(dy, cx, dx * cy);
                const float length = MathSqrtf(ppc::fmadds(nz, nz, ppc::fmadds(nx, nx, ny * ny)));
                if (length != kZero) {
                    const float inverse = kOne / length;
                    nz = nz * inverse;
                    nx = nx * inverse;
                    ny = ny * inverse;
                }
                const float k = m_fEndTangent;
                control2.x = ppc::fmadds(nx, k, end.x);
                control2.z = ppc::fmadds(nz, k, end.z);
                control2.y = ppc::fmadds(ny, k, end.y);
            }
            Vec3_CubicBezier(t, &p->m_vPos, &p->m_vStart, &control1, &control2, &end);  // 0x00010fc0 through 0x00990150
            const float sx = p->m_vPos.x - p->m_vPrevPos.x;
            const float sy = p->m_vPos.y - p->m_vPrevPos.y;
            const float sz = p->m_vPos.z - p->m_vPrevPos.z;
            p->m_vDir.x = sx;
            p->m_vDir.y = sy;
            p->m_vDir.z = sz;
        }
        const CKProjectileDataTypeBallisticPFX* data = DataOf(p);
        if ((data->m_ui32Flags & 0x40u) != 0 && p->m_fSpeed > data->m_unk34) VfA8();  // vt+0xa8 (empty)
        if ((m_baOptions & 0x80u) != 0) UpdateInstanceTrailSegment(index);  // 0x00586340
        if ((m_baOptions & 0x200000u) != 0 && ((p->m_flags64 >> 3) & 1u) == 0) {
            const float hearing = DataOf(p)->m_unk48;
            const float hearing2 = hearing * hearing;
            const CKSrvCamera* camera = Camera();
            const float cy = camera->m_v3RealPos.y - p->m_vPos.y;
            const float cx = camera->m_v3RealPos.x - p->m_vPos.x;
            const float cz = camera->m_v3RealPos.z - p->m_vPos.z;
            if (ppc::fmadds(cz, cz, ppc::fmadds(cx, cx, cy * cy)) < hearing2) PlayInstanceSound(index);  // 0x00586630
        }
    }
    p->m_fAge = p->m_fAge + dt;
}
