// CKProjectileTypeFromExplosion.cpp - reconstructed original translation unit 0x59a370-0x59c668 (GAME_TOC2, main_toc2),
// 24 functions, 24 live.
// Primary class: CKProjectileTypeFromExplosion  key 0x290c  category Logic  size 0x34  vtable 0xb2e648
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x59a370  CKProjectileTypeFromExplosion_Delete  (DOTD_DECLARE_FACTORIES)
//   [ ] 0x59a3c0  RegisterCKProjectileTypeFromExplosionClass
//   [ ] 0x59a438  _GLOBAL__I_59a438
//   [x] 0x59a448  CKProjectileTypeFromExplosion_ProcessDamageContacts
//   [x] 0x59a4e0  CKProjectileTypeFromExplosion_SpawnInstanceAtPoint_maybe  (SpawnTowardPoint)
//   [x] 0x59a690  CKProjectileTypeFromExplosion_SpawnInstanceAtTarget_maybe  (SpawnAtTarget)
//   [x] 0x59a868  CKProjectileTypeFromExplosion_LaunchAtTarget
//   [x] 0x59a948  CKProjectileTypeFromExplosion_SpawnInstanceAtHook_maybe  (SpawnAtTargetSpot)
//   [x] 0x59ab28  CKProjectileTypeFromExplosion_LaunchInstance_maybe  (LaunchAtTargetSpot, vt+0x94)
//   [x] 0x59ac08  CKProjectileTypeFromExplosion_OnDeath
//   [x] 0x59ac30  CKProjectileTypeFromExplosion_IsDead
//   [x] 0x59ac58  CKProjectileTypeFromExplosion_UpdateCollision
//   [x] 0x59acb8  CKProjectileTypeFromExplosion_DeleteArray  (DOTD_DECLARE_FACTORIES)
//   [x] 0x59ad58  CKProjectileTypeFromExplosion_Create  (DOTD_DECLARE_FACTORIES; the constructor)
//   [x] 0x59adb0  CKProjectileTypeFromExplosion_LaunchAtPoint_maybe  (LaunchTowardPoint, vt+0xb0)
//   [x] 0x59aeb8  CKProjectileTypeFromExplosion_Launch
//   [x] 0x59b0f0  CKProjectileTypeFromExplosion_KillInstance  (KillProjectile)
//   [x] 0x59b1b8  CKProjectileTypeFromExplosion_CreateArray  (DOTD_DECLARE_FACTORIES; the constructor)
//   [x] 0x59b270  CKProjectileTypeFromExplosion_ComputeInterceptPoint_maybe
//   [x] 0x59bc78  CKProjectileTypeFromExplosion_UpdateMotion
//   [x] 0x59c390  CKProjectileTypeFromExplosion_Destroy
//   [ ] 0x59c3b8  CKProjectileTypeFromExplosion_Save
//   [x] 0x59c3c0  CKProjectileTypeFromExplosion_RecursiveRegistration
//   [x] 0x59c3e8  CKProjectileTypeFromExplosion_Load
//
//   [x] 0x9cb928  CKProjectileTypeFromExplosion_IsKindOfClass  [inline]  (CKProjectileTypeFromExplosion.h)
//   [x] 0x9cb960  CKProjectileTypeFromExplosion_GetClassType  [inline]  (DOTD_CLASS_KEY)
//   [x] 0x9cb968  CKProjectileTypeFromExplosion_GetClassID  [inline]  (DOTD_CLASS_KEY)
//   [x] 0x9cb970  CKProjectileTypeFromExplosion_Destructor  [inline]  (CKProjectileTypeFromExplosion.h)
//   [x] 0x9cb990  CKProjectileTypeFromExplosion_DeletingDestructor  [inline]  (CKProjectileTypeFromExplosion.h)
#include "k2000/logic/fx/CKProjectileTypeFromExplosion.h"

#include <cmath>
#include <cstring>

#include "Renderware/rwcore/RwCamera.h"
#include "Spyro2008/groups/IKGrpHero.h"
#include "crt/ppc_ops.h"
#include "crt/xatan.h"
#include "crt/xsinf.h"
#include "k2000/cameras/CKSrvCamera.h"
#include "k2000/hooks/IKHook.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/logic/fx/CKProjectileDataTypeFromExplosion.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/CSGLeaf.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/scenegraph/IKBoundingVolume.h"
#include "k2000/services/CKSrvCollision.h"

namespace {

using Record = CKProjectileTypeFromExplosion::Record;

// The shared constants (zero in the EBOOT's BSS, filled by static initialisers; TOC2 -0x6bd0 / -0x6bc8 / -0x6b5c /
// -0x6b60 / -0x6bc0 hold their addresses).
const CVector3 kAxisY = {0.0f, 1.0f, 0.0f};       // 0x00c50d40
const CVector3 kAxisZ = {0.0f, 0.0f, 1.0f};       // 0x00c50d4c
const CVector3 kNullVector = {0.0f, 0.0f, 0.0f};  // 0x00c50d64
constexpr float kZero = 0.0f;                     // TOC2 -0x6bc4
constexpr float kOne = 1.0f;                      // TOC2 -0x6c20
constexpr float kMinusZero = -0.0f;               // TOC2 -0x6bd8 (0x80000000)
constexpr float kMinusFour = -4.0f;               // TOC2 -0x6bd4 (0xc0800000)
constexpr float kPi = 3.14159274f;                // TOC2 -0x6bcc (0x40490fdb)
constexpr float kHalfPi = 1.57079637f;            // TOC2 -0x6c1c (0x3fc90fdb)
constexpr float kFirstDt = 0.02f;                 // TOC2 -0x6c28 (0x3ca3d70a)
constexpr float kRandToUnit = -3.05180438e-05f;   // TOC2 -0x6c24 (0xb8000080)

Record* RecordAt(const CKProjectileTypeFromExplosion* pool, uint32_t index) {
    return reinterpret_cast<Record**>(pool->m_apProjectileList)[index];
}
CKProjectileDataTypeFromExplosion* DataOf(const Record* record) {
    return static_cast<CKProjectileDataTypeFromExplosion*>(record->m_pData);
}
CKSrvCamera* Camera() { return static_cast<CKSrvCamera*>(g_pEngine->m_srvCamera); }

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

// One Rand_Int draw (through TocBridge_Rand_Int 0x0098fd10) as 1 - u / 32767.5, in (-1, 1] (fmadds).
float RandSigned() {
    const uint32_t r = static_cast<uint32_t>(Rand_Int()) & 0xffffu;
    return ppc::fmadds(static_cast<float>(r), kRandToUnit, kOne);
}

// The world position of a target hook: its node's LTM position.
CVector3 HookPosition(IKSerializable* target) {
    const RwV3d& at = static_cast<CSGMovable*>(static_cast<IKHook*>(target)->m_pKGLObject)->m_pRwFrame->ltm.pos;
    return CVector3{at.x, at.y, at.z};
}

// The tail the three spawns share (0x0059a594.. in each): the homing speed (data flag 0x40000000: data +0x78 + a random
// part of +0x7c; one draw; else the launch speed), the angle round the target (a second draw, x pi/2), bit 4 cleared
// (homing), then the base's SpawnInstance at the homing speed with no damage object.
void SpawnTail(CKProjectileTypeFromExplosion* pool, Record* p, uint32_t flags, CKProjectileDataTypeFromExplosion* data,
               uint8_t index, const CVector3* pos, const CVector3* dir, float speed, IKSerializable* owner,
               const RwMatrix* matrix) {
    if ((flags & 0x40000000u) == 0) {
        p->m_fCruiseSpeed = speed;
    } else {
        const float base = data->m_unk78;
        const float u = RandSigned();
        p->m_fCruiseSpeed = ppc::fmadds(u, data->m_unk7c, base);
    }
    p->m_fOrbitAngle = RandSigned() * kHalfPi;
    p->m_flags64 = static_cast<uint8_t>(p->m_flags64 & ~0x10u);
    pool->SpawnInstance(data, index, pos, dir, p->m_fCruiseSpeed, owner, matrix, nullptr);  // 0x0058c948
}

}  // namespace

// 0x0059c390 CKProjectileTypeFromExplosion_Destroy
void CKProjectileTypeFromExplosion::Destroy() { CKProjectileTypeBallisticPFX::Destroy(); }

// 0x0059c3c0 CKProjectileTypeFromExplosion_RecursiveRegistration
void CKProjectileTypeFromExplosion::RecursiveRegistration(int32_t type) {
    CKProjectileTypeBallisticPFX::RecursiveRegistration(type);
}

// 0x0059c3e8 CKProjectileTypeFromExplosion_Load: the base's Load; level data: the records rebuilt at 0xc0 bytes (each
// takes the node of the base's record, hidden), the base's lists freed. PS3: (count * 0xc0) & ~0x3f; native sizes here.
// BUG(original): the camera quakes (+0x80) the base's Load read are not copied (nor the lifetime 1.0), so the base's
// RecursiveRegistration reads the new records' unset +0x80.
int32_t CKProjectileTypeFromExplosion::Load(IKFile* file, int32_t type) {
    CKProjectileTypeBallisticPFX::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    Record** list = static_cast<Record**>(Mem_AllocAligned16(m_ui8MaxProjectiles * static_cast<uint32_t>(sizeof(Record*))));
    Record* records = static_cast<Record*>(Mem_AllocAligned16(m_ui8MaxProjectiles * static_cast<uint32_t>(sizeof(Record))));
    if (m_ui8MaxProjectiles != 0) {
        uint32_t i = 0;
        uint8_t index = 0;
        do {
            Record* p = &records[i];
            list[i] = p;
            CSGLeaf* node = reinterpret_cast<Projectile**>(m_apProjectileList)[i]->m_pNode;
            p->m_pNode = node;
            node->m_sgProperties = (node->m_sgProperties & ~4u) | 4u;
            p->m_pVolume = nullptr;
            p->m_vPos = kNullVector;      // TOC2 -0x6b60 0x00c50d64
            p->m_vPrevPos = kNullVector;
            p->m_vDir = kAxisZ;           // TOC2 -0x6b5c 0x00c50d4c
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
            ++index;
            p->m_vAimPoint = kNullVector;
            p->m_fOrbitAngle = 0.0f;
            p->m_fCruiseSpeed = 0.0f;
            i = index;
        } while (m_ui8MaxProjectiles > i);
    }
    Mem_FreeAligned16(m_apProjectileList);  // through TocBridge_Mem_FreeAligned16 0x0098f770
    Mem_FreeAligned16(m_aProjectiles);
    m_aProjectiles = records;
    m_apProjectileList = reinterpret_cast<void**>(list);
    return 1;
}

// 0x0059ac30 CKProjectileTypeFromExplosion_IsDead: the base's.
uint8_t CKProjectileTypeFromExplosion::IsDead(uint8_t index) { return CKProjectileTypeBallisticPFX::IsDead(index); }

// 0x0059ac08 CKProjectileTypeFromExplosion_OnDeath: the base's.
void CKProjectileTypeFromExplosion::OnDeath(uint8_t index) { CKProjectileTypeBallisticPFX::OnDeath(index); }

// 0x0059ac58 CKProjectileTypeFromExplosion_UpdateCollision: the base's, but not while it has a target.
void CKProjectileTypeFromExplosion::UpdateCollision(uint8_t index, float dt) {
    if (RecordAt(this, index)->m_target.m_pTarget != nullptr) return;
    CKProjectileTypeBallisticPFX::UpdateCollision(index, dt);
}

// 0x0059a448 CKProjectileTypeFromExplosion_ProcessDamageContacts: with a volume, the base's, then every collision of the
// volume asked HasContactSet (vt+0x08; the answers unused). BUG(original): the volume is read again without a null test.
void CKProjectileTypeFromExplosion::ProcessDamageContacts(uint8_t index) {
    Record* p = RecordAt(this, index);
    if (p->m_pVolume == nullptr) return;
    CKProjectileTypeBallisticPFX::ProcessDamageContacts(index);  // 0x00587d00
    IKBoundingVolume* volume = static_cast<IKBoundingVolume*>(p->m_pVolume);
    for (ICollision* c = static_cast<ICollision*>(volume->m_CollisionResList); c != nullptr; c = c->m_pNext) {
        c->HasContactSet();
    }
}

// 0x0059b0f0 CKProjectileTypeFromExplosion_KillInstance: 0x2897 with the target to the volume's owner (+0x24) when
// there is one; the target cleared; the base's KillInstance.
void CKProjectileTypeFromExplosion::KillProjectile(uint8_t index) {
    Record* p = RecordAt(this, index);
    if (p->m_pVolume != nullptr) {
        IKSerializable* owner = static_cast<IKBoundingVolume*>(p->m_pVolume)->m_pOwner;
        if (owner != nullptr) owner->MessageProc(0x2897, &p->m_target);  // vt+0x1c
    }
    p->m_target.m_unk0c = 0;
    p->m_target.m_pTarget = nullptr;
    p->m_target.m_pHotSpot = nullptr;
    CKProjectileTypeBallisticPFX::KillProjectile(index);  // 0x005886d0
}

// 0x0059a4e0 CKProjectileTypeFromExplosion_SpawnInstanceAtPoint_maybe
void CKProjectileTypeFromExplosion::SpawnTowardPoint(IKSerializable* data, uint8_t index, const CVector3* pos,
                                                     const CVector3* dir, float speed, IKSerializable* owner,
                                                     const CVector3* target, const RwMatrix* matrix) {
    Record* p = RecordAt(this, index);
    p->m_vAimPoint = *target;
    p->m_vPrevTargetPos = *target;
    p->m_fLastDt = kFirstDt;
    CKProjectileDataTypeFromExplosion* d = static_cast<CKProjectileDataTypeFromExplosion*>(data);
    SpawnTail(this, p, d->m_ui32Flags, d, index, pos, dir, speed, owner, matrix);
}

// 0x0059a690 CKProjectileTypeFromExplosion_SpawnInstanceAtTarget_maybe. BUG(original): the flag 0x40000000 is read from
// the record's previous data (+0x04, set by the SpawnInstance that follows), the homing speed's floats from `data`.
void CKProjectileTypeFromExplosion::SpawnAtTarget(IKSerializable* data, uint8_t index, const CVector3* pos,
                                                  const CVector3* dir, float speed, IKSerializable* owner,
                                                  IKSerializable* target, const RwMatrix* matrix) {
    Record* p = RecordAt(this, index);
    p->m_target.m_unk0c = 0;
    p->m_target.m_pTarget = target;
    p->m_target.m_pHotSpot = nullptr;
    const CVector3 at = HookPosition(target);
    p->m_vAimPoint = at;
    p->m_vPrevTargetPos = at;
    p->m_fLastDt = kFirstDt;
    const uint32_t flags = DataOf(p)->m_ui32Flags;
    SpawnTail(this, p, flags, static_cast<CKProjectileDataTypeFromExplosion*>(data), index, pos, dir, speed, owner, matrix);
}

// 0x0059a948 CKProjectileTypeFromExplosion_SpawnInstanceAtHook_maybe
void CKProjectileTypeFromExplosion::SpawnAtTargetSpot(IKSerializable* data, uint8_t index, const CVector3* pos,
                                                      const CVector3* dir, float speed, IKSerializable* owner,
                                                      const ProjectileTarget* target, const RwMatrix* matrix) {
    Record* p = RecordAt(this, index);
    p->m_target.m_pTarget = target->m_pTarget;
    p->m_target.m_pHotSpot = target->m_pHotSpot;
    p->m_target.m_unk0c = target->m_unk0c;
    const CVector3 at = HookPosition(target->m_pTarget);
    p->m_vAimPoint = at;
    p->m_vPrevTargetPos = at;
    p->m_fLastDt = kFirstDt;
    CKProjectileDataTypeFromExplosion* d = static_cast<CKProjectileDataTypeFromExplosion*>(data);
    SpawnTail(this, p, d->m_ui32Flags, d, index, pos, dir, speed, owner, matrix);
}

// 0x0059a868 CKProjectileTypeFromExplosion_LaunchAtTarget (vt+0x8c): the first free projectile at `target`; none free:
// 0x2897 to the owner with {target, no hot spot} (+0x08 stack garbage in the original).
uint8_t CKProjectileTypeFromExplosion::LaunchAtTarget(IKSerializable* data, const CVector3* pos, const CVector3* dir,
                                                      float speed, IKSerializable* owner, IKSerializable* target,
                                                      const RwMatrix* matrix) {
    const uint8_t index = m_ui8NbOfActiveProjectiles;
    if (!(m_ui8MaxProjectiles > index)) {
        if (owner != nullptr) {
            ProjectileTarget message{};
            message.m_pTarget = target;
            message.m_unk0c = 0;
            message.m_pHotSpot = nullptr;
            owner->MessageProc(0x2897, &message);  // vt+0x1c
        }
        return 0;
    }
    SpawnAtTarget(data, index, pos, dir, speed, owner, target, matrix);
    m_ui8NbOfActiveProjectiles = static_cast<uint8_t>(m_ui8NbOfActiveProjectiles + 1);
    return 1;
}

// 0x0059ab28 CKProjectileTypeFromExplosion_LaunchInstance_maybe (vt+0x94): the same at a target and its hot spot; none
// free: 0x2897 to the owner with the target.
uint8_t CKProjectileTypeFromExplosion::LaunchAtTargetSpot(IKSerializable* data, const CVector3* pos, const CVector3* dir,
                                                          float speed, IKSerializable* owner,
                                                          const ProjectileTarget* target, const RwMatrix* matrix) {
    const uint8_t index = m_ui8NbOfActiveProjectiles;
    if (!(m_ui8MaxProjectiles > index)) {
        if (owner != nullptr) owner->MessageProc(0x2897, const_cast<ProjectileTarget*>(target));  // vt+0x1c
        return 0;
    }
    SpawnAtTargetSpot(data, index, pos, dir, speed, owner, target, matrix);
    m_ui8NbOfActiveProjectiles = static_cast<uint8_t>(m_ui8NbOfActiveProjectiles + 1);
    return 1;
}

// 0x0059adb0 CKProjectileTypeFromExplosion_LaunchAtPoint_maybe (vt+0xb0): the same toward a point (copied); none free:
// 0x2897 to the owner with no target.
uint8_t CKProjectileTypeFromExplosion::LaunchTowardPoint(IKSerializable* data, const CVector3* pos, const CVector3* dir,
                                                         float speed, IKSerializable* owner, const CVector3* target,
                                                         const RwMatrix* matrix) {
    const uint8_t index = m_ui8NbOfActiveProjectiles;
    if (!(m_ui8MaxProjectiles > index)) {
        if (owner != nullptr) {
            ProjectileTarget message{};
            message.m_unk0c = 0;
            message.m_pTarget = nullptr;
            message.m_pHotSpot = nullptr;
            owner->MessageProc(0x2897, &message);  // vt+0x1c
        }
        return 0;
    }
    const CVector3 point = *target;
    SpawnTowardPoint(data, index, pos, dir, speed, owner, &point, matrix);
    m_ui8NbOfActiveProjectiles = static_cast<uint8_t>(m_ui8NbOfActiveProjectiles + 1);
    return 1;
}

// 0x0059aeb8 CKProjectileTypeFromExplosion_Launch (vt+0x84): data flag 0x80000000 and a controlled hero: at the first
// controlled hero (vt+0x8c); else at the data's hook (+0x74) when it has one (vt+0x8c); else toward the point data +0x88
// ahead of the camera along its real Z axis (vt+0xb0).
uint8_t CKProjectileTypeFromExplosion::Launch(IKSerializable* data, const CVector3* pos, const CVector3* dir, float speed,
                                              IKSerializable* owner, const RwMatrix* matrix) {
    CKProjectileDataTypeFromExplosion* d = static_cast<CKProjectileDataTypeFromExplosion*>(data);
    if (static_cast<int32_t>(d->m_ui32Flags) < 0) {
        IKGrpHero* group = static_cast<IKGrpHero*>(g_pEngine->m_gameManager->m_unk04[1]);  // the game manager's +0x08
        if (group != nullptr && group->m_ui8ControlledHeroCount != 0) {  // 0x002ca288 GetControlledHeroCount
            IKSerializable* hero = group->m_apControlledHeroes[0];      // 0x002ca0e0 GetControlledHeroArray
            return LaunchAtTarget(data, pos, dir, speed, owner, hero, matrix);
        }
    }
    if (d->m_unk74 != nullptr) return LaunchAtTarget(data, pos, dir, speed, owner, d->m_unk74, matrix);
    const CKSrvCamera* camera = Camera();
    const float ahead = d->m_unk88;
    CVector3 point;
    point.x = ppc::fmadds(ahead, camera->m_v3RealAxisZ.x, camera->m_v3RealPos.x);
    point.y = ppc::fmadds(ahead, camera->m_v3RealAxisZ.y, camera->m_v3RealPos.y);
    point.z = ppc::fmadds(ahead, camera->m_v3RealAxisZ.z, camera->m_v3RealPos.z);
    return LaunchTowardPoint(data, pos, dir, speed, owner, &point, matrix);
}

// 0x0059b270 CKProjectileTypeFromExplosion_ComputeInterceptPoint_maybe: from the target's velocity (its move since the
// last frame over the last time step) and the homing speed (raised by the target's speed when the target moves away
// from the projectile), the point where the projectile meets the target. Inside the data's radius (+0x80) of that
// point, the aim is one step along the flight and bit 4 (ballistic) is set; else the aim is on the circle of that radius
// round the point, at the angle +0xbc (+ pi when the target moves against the circle's side).
void CKProjectileTypeFromExplosion::ComputeInterceptPoint(Record* p) {
    CKProjectileDataTypeFromExplosion* data = DataOf(p);
    // The target's velocity: unit direction (vx, vy, vz) and speed s (s2 its square).
    const float inverseDt = kOne / p->m_fLastDt;
    const float tx = p->m_vAimPoint.x;
    const float ty = p->m_vAimPoint.y;
    const float tz = p->m_vAimPoint.z;
    float vy = (ty - p->m_vPrevTargetPos.y) * inverseDt;
    float vx = (tx - p->m_vPrevTargetPos.x) * inverseDt;
    float vz = (tz - p->m_vPrevTargetPos.z) * inverseDt;
    float s = MathSqrtf(ppc::fmadds(vz, vz, ppc::fmadds(vx, vx, vy * vy)));
    float s2 = kZero;
    if (s != kZero) {
        s2 = s * s;
        const float inverse = kOne / s;
        vz = vz * inverse;
        vx = vx * inverse;
        vy = vy * inverse;
    } else {
        s = kZero;
    }
    // The projectile to the target: unit direction and distance d; the quadratic's 2d and -d^2.
    float dx = tx - p->m_vPos.x;
    float dy = ty - p->m_vPos.y;
    float dz = tz - p->m_vPos.z;
    const float d = MathSqrtf(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));
    float twoD = kZero;
    float minusD2 = kMinusZero;  // TOC2 -0x6bd8
    float dot;
    bool away;
    if (d == kZero) {
        dot = ppc::fmadds(vz, dz, ppc::fmadds(vx, dx, vy * dy));
        away = !(dot <= kZero);  // ble: a NaN counts as away here
    } else {
        const float minusD = -d;
        twoD = d + d;
        const float inverse = kOne / d;
        dy = dy * inverse;
        dz = dz * inverse;
        dx = dx * inverse;
        minusD2 = d * minusD;
        dot = ppc::fmadds(vz, dz, ppc::fmadds(vx, dx, vy * dy));
        away = dot > kZero;  // bgt: a NaN does not
    }
    float speed = p->m_fCruiseSpeed;
    if (away && s > speed) {
        speed = s + speed;
        p->m_fCruiseSpeed = speed;
    }
    // The meeting time t: (b + sqrt(b^2 - 4 a (-d^2))) / 2a with a = speed^2 - s^2, b = dot * s * 2d (0 without a root).
    const float a = ppc::fmsubs(speed, speed, s2);
    const float sTwoD = s * twoD;
    const float b = dot * sTwoD;
    const float c = (a * kMinusFour) * minusD2;
    const float disc = ppc::fmadds(b, b, c);
    float t = kZero;
    if (disc >= kZero) {  // cror gt|eq: a NaN has no root
        const float root = MathSqrtf(disc);
        t = (b + root) / (a + a);
    }
    // The meeting point P and the unit direction e from it to the projectile.
    const float k = t * s;
    const float py = ppc::fmadds(k, vy, ty);
    const float px = ppc::fmadds(k, vx, tx);
    const float pz = ppc::fmadds(k, vz, tz);
    float ey = p->m_vPos.y - py;
    float ex = p->m_vPos.x - px;
    float ez = p->m_vPos.z - pz;
    float e = MathSqrtf(ppc::fmadds(ez, ez, ppc::fmadds(ex, ex, ey * ey)));
    const float radius = data->m_unk80;
    bool inside;
    if (e == kZero) {
        e = kZero;
        inside = !(e >= radius);  // bge: a NaN radius counts as inside
    } else {
        const float inverse = kOne / e;
        inside = e < radius;
        ez = ez * inverse;
        ex = ex * inverse;
        ey = ey * inverse;
    }
    if (inside) {
        p->m_vAimPoint.x = p->m_vPos.x + p->m_vDir.x;
        p->m_vAimPoint.z = p->m_vPos.z + p->m_vDir.z;
        p->m_vAimPoint.y = p->m_vPos.y + p->m_vDir.y;
        p->m_flags64 = static_cast<uint8_t>((p->m_flags64 & ~0x10u) | 0x10u);
        return;
    }
    // On the circle: the angle whose cosine is radius / e (0x00780c90 Math_Acosf); the radial and the perpendicular
    // parts of the radius.
    const float angle = crt::Acosf(radius / e);
    const float radial = GameCosf(angle) * radius;
    const float sine = GameSinf(angle);
    const float perpendicular = (sine * radius < kZero) ? radius * -GameSinf(angle) : GameSinf(angle) * radius;
    // c = e x Y (unit; e x Z unnormalised when e is vertical), u = e x c.
    float cx;
    float cy;
    float cz;
    {
        const float yzx = kAxisY.z * ex;
        const float yyz = kAxisY.y * ez;
        const float yxy = kAxisY.x * ey;
        cy = ppc::fmsubs(kAxisY.x, ez, yzx);
        cx = ppc::fmsubs(kAxisY.z, ey, yyz);
        cz = ppc::fmsubs(kAxisY.y, ex, yxy);
    }
    const float length = MathSqrtf(ppc::fmadds(cz, cz, ppc::fmadds(cx, cx, cy * cy)));
    if (length == kZero) {
        const float zxy = kAxisZ.x * ey;
        const float zzx = kAxisZ.z * ex;
        const float zyz = kAxisZ.y * ez;
        cz = ppc::fmsubs(kAxisZ.y, ex, zxy);
        cy = ppc::fmsubs(kAxisZ.x, ez, zzx);
        cx = ppc::fmsubs(kAxisZ.z, ey, zyz);
    } else {
        const float inverse = kOne / length;
        cz = cz * inverse;
        cy = cy * inverse;
        cx = cx * inverse;
    }
    const float czx = cz * ex;
    const float cyz = cy * ez;
    const float cxy = cx * ey;
    const float uy = ppc::fmsubs(cx, ez, czx);
    const float ux = ppc::fmsubs(cz, ey, cyz);
    const float uz = ppc::fmsubs(cy, ex, cxy);
    const float side = ppc::fmadds(vz, cz, ppc::fmadds(vx, cx, vy * cy));
    const float orbit = (side <= kZero) ? p->m_fOrbitAngle + kPi : p->m_fOrbitAngle;  // ble: a NaN keeps the angle
    const float along = GameCosf(orbit) * perpendicular;
    p->m_vAimPoint.z = ppc::fmadds(along, cz, ppc::fmadds(radial, ez, pz));
    p->m_vAimPoint.x = ppc::fmadds(along, cx, ppc::fmadds(radial, ex, px));
    p->m_vAimPoint.y = ppc::fmadds(along, cy, ppc::fmadds(radial, ey, py));
    const float across = perpendicular * GameSinf(orbit);
    p->m_vAimPoint.z = ppc::fmadds(across, uz, p->m_vAimPoint.z);
    p->m_vAimPoint.x = ppc::fmadds(across, ux, p->m_vAimPoint.x);
    p->m_vAimPoint.y = ppc::fmadds(across, uy, p->m_vAimPoint.y);
}

// 0x0059bc78 CKProjectileTypeFromExplosion_UpdateMotion. Not landed (bit 2): the target's position T (the camera's
// point data +0x88 ahead without a target, its hot spot, or its node); homing (bit 4 clear): the aim point computed, the
// direction turned toward it (the unit step from the last position added, renormalised), the move at the speed, bit 4
// set once within data +0x84 of the aim; ballistic: drag and gravity as the base's, and with a target and a pull (data
// +0x88) a pull toward T fading from data +0x80 to +0x84. Then the base's tail: vfA8 above data +0x34 (flag 0x40), the
// ribbon (option 0x80), the sound when near the camera (option 0x200000); T kept. Always: the time step and the age.
void CKProjectileTypeFromExplosion::UpdateMotion(uint8_t index, float dt) {
    Record* p = RecordAt(this, index);
    if ((p->m_flags64 & 4u) == 0) {
        p->m_vPrevPos = p->m_vPos;
        IKSerializable* target = p->m_target.m_pTarget;
        CVector3 targetPos;
        if (target == nullptr) {
            const CKSrvCamera* camera = Camera();
            const float rz = camera->m_v3RealPos.z;
            const float rx = camera->m_v3RealPos.x;
            const float ry = camera->m_v3RealPos.y;
            const float ahead = DataOf(p)->m_unk88;
            targetPos.z = ppc::fmadds(ahead, camera->m_v3RealAxisZ.z, rz);
            targetPos.x = ppc::fmadds(ahead, camera->m_v3RealAxisZ.x, rx);
            targetPos.y = ppc::fmadds(ahead, camera->m_v3RealAxisZ.y, ry);
        } else if (p->m_target.m_pHotSpot != nullptr) {
            p->m_target.m_pHotSpot->GetWorldPosition(&targetPos);  // 0x000ce790 through 0x0098fd50
        } else {
            targetPos = HookPosition(target);
        }
        if ((p->m_flags64 & 0x10u) == 0) {
            p->m_vAimPoint = targetPos;
            ComputeInterceptPoint(p);
            float sy = p->m_vAimPoint.y - p->m_vPrevPos.y;
            float sx = p->m_vAimPoint.x - p->m_vPrevPos.x;
            float sz = p->m_vAimPoint.z - p->m_vPrevPos.z;
            const float step = dt * p->m_fSpeed;
            const float length = MathSqrtf(ppc::fmadds(sz, sz, ppc::fmadds(sx, sx, sy * sy)));
            if (length != kZero) {
                const float inverse = kOne / length;
                sz = sz * inverse;
                sx = sx * inverse;
                sy = sy * inverse;
            }
            float ny = sy + p->m_vDir.y;
            float nx = sx + p->m_vDir.x;
            float nz = sz + p->m_vDir.z;
            p->m_vDir.y = ny;
            p->m_vDir.x = nx;
            p->m_vDir.z = nz;
            const float turned = MathSqrtf(ppc::fmadds(nz, nz, ppc::fmadds(nx, nx, ny * ny)));
            if (turned != kZero) {
                const float inverse = kOne / turned;
                nz = inverse * nz;
                nx = inverse * nx;
                ny = inverse * ny;
                p->m_vDir.z = nz;
                p->m_vDir.x = nx;
                p->m_vDir.y = ny;
            }
            const float posY = ppc::fmadds(step, ny, p->m_vPos.y);
            const float posX = ppc::fmadds(step, nx, p->m_vPos.x);
            const float posZ = ppc::fmadds(step, nz, p->m_vPos.z);
            p->m_vPos.y = posY;
            p->m_vPos.x = posX;
            p->m_vPos.z = posZ;
            const float ey = posY - p->m_vAimPoint.y;
            const float ex = posX - p->m_vAimPoint.x;
            const float ez = posZ - p->m_vAimPoint.z;
            const float reach = DataOf(p)->m_unk84;
            const float distance2 = ppc::fmadds(ez, ez, ppc::fmadds(ex, ex, ey * ey));
            if (distance2 <= reach * reach) {  // cror lt|eq: a NaN stays homing
                p->m_flags64 = static_cast<uint8_t>((p->m_flags64 & ~0x10u) | 0x10u);
            }
        } else {
            const float speed0 = p->m_fSpeed;
            const float speed = speed0 - dt * (speed0 * DataOf(p)->m_unk24);
            p->m_fSpeed = speed;
            const float length =
                MathSqrtf(ppc::fmadds(p->m_vDir.z, p->m_vDir.z, ppc::fmadds(p->m_vDir.x, p->m_vDir.x, p->m_vDir.y * p->m_vDir.y)));
            float vx = p->m_vDir.x;
            float vz = p->m_vDir.z;
            if (length != kZero) {
                const float k = speed / length;
                vz = k * p->m_vDir.z;
                vx = k * p->m_vDir.x;
                const float vy = k * p->m_vDir.y;
                p->m_vDir.z = vz;
                p->m_vDir.x = vx;
                p->m_vDir.y = vy;
            }
            p->m_vDir.y = p->m_vDir.y - dt * DataOf(p)->m_unk1c;
            const float velocity = MathSqrtf(ppc::fmadds(vz, vz, ppc::fmadds(vx, vx, p->m_vDir.y * p->m_vDir.y)));
            float newSpeed = kZero;
            if (velocity != kZero) {
                const float inverse = kOne / velocity;
                const float nz = inverse * p->m_vDir.z;
                const float nx = inverse * p->m_vDir.x;
                const float ny = inverse * p->m_vDir.y;
                p->m_vDir.z = nz;
                p->m_vDir.x = nx;
                p->m_vDir.y = ny;
                newSpeed = velocity;
            }
            const float step = newSpeed * dt;
            p->m_fSpeed = newSpeed;
            const float posZ = ppc::fmadds(step, p->m_vDir.z, p->m_vPos.z);
            const float posX = ppc::fmadds(step, p->m_vDir.x, p->m_vPos.x);
            const float posY = ppc::fmadds(step, p->m_vDir.y, p->m_vPos.y);
            p->m_vPos.z = posZ;
            p->m_vPos.x = posX;
            p->m_vPos.y = posY;
            if (target != nullptr && DataOf(p)->m_unk88 != kZero) {  // fcmpu / bne: a NaN pulls
                float gy = posY - targetPos.y;
                float gx = posX - targetPos.x;
                float gz = posZ - targetPos.z;
                float gap = MathSqrtf(ppc::fmadds(gz, gz, ppc::fmadds(gx, gx, gy * gy)));
                if (gap != kZero) {
                    const float inverse = kOne / gap;
                    gz = gz * inverse;
                    gx = gx * inverse;
                    gy = gy * inverse;
                } else {
                    gap = kZero;
                }
                const CKProjectileDataTypeFromExplosion* data = DataOf(p);
                const float inner = data->m_unk80;
                const float fade = (gap - inner) / (data->m_unk84 - inner);
                if (fade < kOne) {  // bge: a NaN does not pull
                    float weight = kOne;
                    if (!(fade < kZero)) weight = kOne - fade;
                    const float pull = weight * data->m_unk88;
                    const float az = ppc::fmadds(gz, pull, kNullVector.z);  // 0x00c50d64 (TOC2 -0x6bc0)
                    const float ax = ppc::fmadds(pull, gx, kNullVector.x);
                    const float ay = ppc::fmadds(pull, gy, kNullVector.y);
                    p->m_vPos.z = ppc::fmadds(dt, az, p->m_vPos.z);
                    p->m_vPos.x = ppc::fmadds(dt, ax, p->m_vPos.x);
                    p->m_vPos.y = ppc::fmadds(dt, ay, p->m_vPos.y);
                }
            }
        }
        const CKProjectileDataTypeFromExplosion* data = DataOf(p);
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
        p->m_vPrevTargetPos = targetPos;
    }
    p->m_fLastDt = dt;
    p->m_fAge = dt + p->m_fAge;
}
