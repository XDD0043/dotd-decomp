// CKProjectileTypeTargetLock.cpp - reconstructed original translation unit 0x596240-0x597580 (GAME_TOC2, main_toc2),
// 21 functions, 21 live.
// Primary class: CKProjectileTypeTargetLock  key 0x248c  category Logic  size 0x44  vtable 0xb2e478
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x596240  CKProjectileTypeTargetLock_Delete  (DOTD_DECLARE_FACTORIES)
//   [x] 0x596290  CKProjectileTypeTargetLock_vf84  (Launch, vt+0x84)
//   [ ] 0x5962e8  RegisterCKProjectileTypeTargetLockClass
//   [ ] 0x596360  _GLOBAL__I_596360
//   [x] 0x596370  CKProjectileTypeTargetLock_SpawnWithTarget_maybe  (SpawnWithTarget; no caller in the original)
//   [x] 0x5963d8  CKProjectileTypeTargetLock_SpawnInstanceSetTarget_maybe  (SpawnWithTargetInfo; no caller in the original)
//   [x] 0x596458  CKProjectileTypeTargetLock_OnDeath
//   [x] 0x596480  CKProjectileTypeTargetLock_UpdateCollision
//   [x] 0x5964d8  CKProjectileTypeTargetLock_DeleteArray  (DOTD_DECLARE_FACTORIES)
//   [x] 0x596580  CKProjectileTypeTargetLock_Create  (DOTD_DECLARE_FACTORIES; the constructor)
//   [x] 0x5965d8  CKProjectileTypeTargetLock_ProcessDamageContacts
//   [x] 0x596770  CKProjectileTypeTargetLock_KillInstance  (KillProjectile)
//   [x] 0x596828  CKProjectileTypeTargetLock_IsDead
//   [x] 0x596998  CKProjectileTypeTargetLock_CreateArray  (DOTD_DECLARE_FACTORIES; the constructor)
//   [x] 0x596a58  CKProjectileTypeTargetLock_UpdateMotion
//   [x] 0x596f98  CKProjectileTypeTargetLock_LaunchAtTargetInfo  (LaunchAtTargetSpot, vt+0x94)
//   [x] 0x5970c8  CKProjectileTypeTargetLock_LaunchAtTarget  (vt+0x8c)
//   [x] 0x597200  CKProjectileTypeTargetLock_Destroy
//   [ ] 0x597228  CKProjectileTypeTargetLock_Save
//   [x] 0x597230  CKProjectileTypeTargetLock_RecursiveRegistration
//   [x] 0x597258  CKProjectileTypeTargetLock_Load
//
//   [x] 0x9cb6b0  CKProjectileTypeTargetLock_IsKindOfClass  [inline]  (CKProjectileTypeTargetLock.h)
//   [x] 0x9cb6e8  CKProjectileTypeTargetLock_GetClassType  [inline]  (DOTD_CLASS_KEY)
//   [x] 0x9cb6f0  CKProjectileTypeTargetLock_GetClassID  [inline]  (DOTD_CLASS_KEY)
//   [x] 0x9cb6f8  CKProjectileTypeTargetLock_Destructor  [inline]  (CKProjectileTypeTargetLock.h)
//   [x] 0x9cb718  CKProjectileTypeTargetLock_DeletingDestructor  [inline]  (CKProjectileTypeTargetLock.h)
#include "k2000/logic/ui/CKProjectileTypeTargetLock.h"

#include <cmath>

#include "Renderware/rwcore/RwCamera.h"
#include "Renderware/rwcore/RwMatrix.h"
#include "crt/ppc_ops.h"
#include "k2000/cameras/CKSrvCamera.h"
#include "k2000/hooks/IKHook.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKProjectileDataTypeBallisticPFX.h"
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/CKHkActorBase.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/CSGLeaf.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/scenegraph/IKBoundingVolume.h"
#include "k2000/services/CKSrvCollision.h"

namespace {

using Record = CKProjectileTypeTargetLock::Record;

// The shared constants (zero in the EBOOT's BSS, filled by static initialisers; TOC2 -0x6dd4 / -0x6dd0 hold their
// addresses).
const CVector3 kAxisZ = {0.0f, 0.0f, 1.0f};       // 0x00c50d4c
const CVector3 kNullVector = {0.0f, 0.0f, 0.0f};  // 0x00c50d64
constexpr float kZero = 0.0f;                     // TOC2 -0x6e50
constexpr float kOne = 1.0f;                      // TOC2 -0x6e58

Record* RecordAt(const CKProjectileTypeTargetLock* pool, uint32_t index) {
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

}  // namespace

// 0x00597200 CKProjectileTypeTargetLock_Destroy
void CKProjectileTypeTargetLock::Destroy() { CKProjectileTypeBallisticPFX::Destroy(); }

// 0x00597230 CKProjectileTypeTargetLock_RecursiveRegistration
void CKProjectileTypeTargetLock::RecursiveRegistration(int32_t type) {
    CKProjectileTypeBallisticPFX::RecursiveRegistration(type);
}

// 0x00597258 CKProjectileTypeTargetLock_Load: the base's Load; level data: the turn rates, the range and the collision
// byte (words read little-endian), then the records rebuilt at 0x9c bytes (each takes the node of the base's record,
// hidden, without a null test), the base's lists freed. PS3: (count << 2) & 0x3fc and count * 0x9c; native sizes here.
// BUG(original): the owner (+0x00), the lifetime, the scale, the fire ball, the particle effect and the camera quake the
// base's Load read are not copied, so the base's RecursiveRegistration reads the new records' unset +0x80.
int32_t CKProjectileTypeTargetLock::Load(IKFile* file, int32_t type) {
    CKProjectileTypeBallisticPFX::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadF32LE(file, &m_fTurnRateAtRange);
    ReadF32LE(file, &m_fTurnRateAtTarget);
    ReadF32LE(file, &m_fTurnRange);
    ReadU8(file, &m_bCollideWhileLocked);
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
            p->m_vPos = kNullVector;      // TOC2 -0x6dd4 0x00c50d64
            p->m_vPrevPos = kNullVector;
            p->m_vDir = kAxisZ;           // TOC2 -0x6dd0 0x00c50d4c
            p->m_fSpeed = 0.0f;
            p->m_GrdContDatasInOut.m_ui8SectorNumber = 0;
            p->m_GrdContDatasInOut.m_pGround = nullptr;
            p->m_GrdContDatasInOut.m_i32FaceIndex = -1;
            p->m_GrdContDatasInOut.m_eContactStatus = 3;
            p->m_flags64 = 0;
            p->m_fAge = 0.0f;
            p->m_ui8Index = index;
            ++index;
            p->m_target.m_unk0c = 0;
            p->m_target.m_pTarget = nullptr;
            p->m_target.m_pHotSpot = nullptr;
            i = index;
        } while (m_ui8MaxProjectiles > i);
    }
    Mem_FreeAligned16(m_apProjectileList);  // through TocBridge_Mem_FreeAligned16 0x0098f770
    Mem_FreeAligned16(m_aProjectiles);
    m_aProjectiles = records;
    m_apProjectileList = reinterpret_cast<void**>(list);
    return 1;
}

// 0x00596458 CKProjectileTypeTargetLock_OnDeath: the base's.
void CKProjectileTypeTargetLock::OnDeath(uint8_t index) { CKProjectileTypeBallisticPFX::OnDeath(index); }

// 0x00596480 CKProjectileTypeTargetLock_UpdateCollision: the base's without a target, or with one when the pool's byte
// (+0x40) says so.
void CKProjectileTypeTargetLock::UpdateCollision(uint8_t index, float dt) {
    if (RecordAt(this, index)->m_target.m_pTarget != nullptr && m_bCollideWhileLocked == 0) return;
    CKProjectileTypeBallisticPFX::UpdateCollision(index, dt);  // 0x0058c878
}

// 0x00596828 CKProjectileTypeTargetLock_IsDead: the base's; else, with a target: dead when the target is an enemy
// (IKHkEnemy 0x1402) with life bit 0x10, an actor (CKHkActorBase 0xd82) whose vt+0xd8 answers 0, or hidden (its node's
// bit 2); else the record's bit 4 (set by a hit).
uint8_t CKProjectileTypeTargetLock::IsDead(uint8_t index) {
    if (CKProjectileTypeBallisticPFX::IsDead(index) != 0) return 1;  // 0x00586830
    const Record* p = RecordAt(this, index);
    IKSerializable* target = p->m_target.m_pTarget;
    if (target == nullptr) return 0;
    if (static_cast<uint8_t>(target->IsKindOfClass(0x1402)) != 0 && (static_cast<IKHook*>(target)->m_bitArray & 0x10u) != 0) {
        return 1;
    }
    if (static_cast<uint8_t>(target->IsKindOfClass(0xd82)) != 0 && static_cast<CKHkActorBase*>(target)->VfD8() == 0) {
        return 1;  // vt+0xd8
    }
    if ((NodeOf(target)->m_sgProperties & 4u) != 0) return 1;
    return static_cast<uint8_t>((p->m_flags64 >> 4) & 1u);
}

// 0x00596770 CKProjectileTypeTargetLock_KillInstance: 0x2897 with the target to the volume's owner (+0x24) when there
// is one; the target cleared; the base's KillInstance. BUG(original): the volume itself is read without a null test.
void CKProjectileTypeTargetLock::KillProjectile(uint8_t index) {
    Record* p = RecordAt(this, index);
    IKSerializable* owner = VolumeOf(p)->m_pOwner;
    if (owner != nullptr) owner->MessageProc(0x2897, &p->m_target);  // vt+0x1c
    p->m_target.m_unk0c = 0;
    p->m_target.m_pTarget = nullptr;
    p->m_target.m_pHotSpot = nullptr;
    CKProjectileTypeBallisticPFX::KillProjectile(index);  // 0x005886d0
}

// 0x005965d8 CKProjectileTypeTargetLock_ProcessDamageContacts: with a volume, the base's; then each collision of the
// volume with a contact (vt+0x08) whose other volume (vt+0x04) belongs to the target is a hit: bit 4 set, 0x2896 with the
// target to the volume's owner, the volume's bit 2 (+0x18) cleared and the target cleared. BUG(original): the volume
// and its owner are read again without null tests; with no target a volume without owner counts as the target.
void CKProjectileTypeTargetLock::ProcessDamageContacts(uint8_t index) {
    Record* p = RecordAt(this, index);
    if (p->m_pVolume == nullptr) return;
    CKProjectileTypeBallisticPFX::ProcessDamageContacts(index);  // 0x00587d00
    for (ICollision* c = static_cast<ICollision*>(VolumeOf(p)->m_CollisionResList); c != nullptr; c = c->m_pNext) {
        if (c->HasContactSet() == 0) continue;  // vt+0x08
        IKSerializable* target = p->m_target.m_pTarget;
        if (static_cast<IKBoundingVolume*>(c->GetBoundingVolume2())->m_pOwner != target) continue;  // vt+0x04
        p->m_flags64 = static_cast<uint8_t>((p->m_flags64 & ~0x10u) | 0x10u);
        VolumeOf(p)->m_pOwner->MessageProc(0x2896, &p->m_target);  // vt+0x1c
        IKBoundingVolume* volume = VolumeOf(p);
        volume->m_ba8Infos = static_cast<uint8_t>(volume->m_ba8Infos & ~4u);
        p->m_target.m_pTarget = nullptr;
        p->m_target.m_pHotSpot = nullptr;
        p->m_target.m_unk0c = 0;
    }
}

// 0x00596370 CKProjectileTypeTargetLock_SpawnWithTarget_maybe: the target set (no hot spot), then the base's
// SpawnInstance without matrix nor damage object.
void CKProjectileTypeTargetLock::SpawnWithTarget(IKSerializable* data, uint8_t index, const CVector3* pos,
                                                 const CVector3* dir, float speed, IKSerializable* owner,
                                                 IKSerializable* target) {
    Record* p = RecordAt(this, index);
    p->m_target.m_pTarget = target;
    p->m_target.m_unk0c = 0;
    p->m_target.m_pHotSpot = nullptr;
    SpawnInstance(data, index, pos, dir, speed, owner, nullptr, nullptr);  // 0x0058c948
}

// 0x005963d8 CKProjectileTypeTargetLock_SpawnInstanceSetTarget_maybe: the target, hot spot and index copied, then the
// base's SpawnInstance without matrix, with the info's damage object (+0x10).
void CKProjectileTypeTargetLock::SpawnWithTargetInfo(IKSerializable* data, uint8_t index, const CVector3* pos,
                                                     const CVector3* dir, float speed, IKSerializable* owner,
                                                     const ProjectileTarget* target) {
    Record* p = RecordAt(this, index);
    p->m_target.m_unk0c = target->m_unk0c;
    p->m_target.m_pTarget = target->m_pTarget;
    p->m_target.m_pHotSpot = target->m_pHotSpot;
    SpawnInstance(data, index, pos, dir, speed, owner, nullptr, target->m_pDamage);  // 0x0058c948
}

// 0x00596290 CKProjectileTypeTargetLock_vf84 (vt+0x84 Launch): vt+0x8c with no target (the matrix moved to r10).
uint8_t CKProjectileTypeTargetLock::Launch(IKSerializable* data, const CVector3* pos, const CVector3* dir, float speed,
                                           IKSerializable* owner, const RwMatrix* matrix) {
    return LaunchAtTarget(data, pos, dir, speed, owner, nullptr, matrix);  // vt+0x8c
}

// 0x005970c8 CKProjectileTypeTargetLock_LaunchAtTarget (vt+0x8c): the first free projectile at `target` (SpawnWithTarget
// inlined: the matrix is dropped); none free: 0x2897 to the owner with {target, no hot spot} (+0x08 / +0x10 stack garbage
// in the original). BUG(original): the owner is not tested for null.
uint8_t CKProjectileTypeTargetLock::LaunchAtTarget(IKSerializable* data, const CVector3* pos, const CVector3* dir,
                                                   float speed, IKSerializable* owner, IKSerializable* target,
                                                   const RwMatrix* /*matrix*/) {
    const uint8_t index = m_ui8NbOfActiveProjectiles;
    if (!(m_ui8MaxProjectiles > index)) {
        ProjectileTarget message{};
        message.m_pTarget = target;
        message.m_unk0c = 0;
        message.m_pHotSpot = nullptr;
        owner->MessageProc(0x2897, &message);  // vt+0x1c
        return 0;
    }
    Record* p = RecordAt(this, index);
    p->m_target.m_unk0c = 0;
    p->m_target.m_pTarget = target;
    p->m_target.m_pHotSpot = nullptr;
    SpawnInstance(data, index, pos, dir, speed, owner, nullptr, nullptr);  // 0x0058c948
    m_ui8NbOfActiveProjectiles = static_cast<uint8_t>(m_ui8NbOfActiveProjectiles + 1);
    return 1;
}

// 0x00596f98 CKProjectileTypeTargetLock_LaunchAtTargetInfo (vt+0x94): the same with a target block (SpawnWithTargetInfo
// inlined: its damage object +0x10 passed on, the matrix dropped); none free: 0x2897 to the owner with the block.
// BUG(original): the owner is not tested for null.
uint8_t CKProjectileTypeTargetLock::LaunchAtTargetSpot(IKSerializable* data, const CVector3* pos, const CVector3* dir,
                                                       float speed, IKSerializable* owner,
                                                       const ProjectileTarget* target, const RwMatrix* /*matrix*/) {
    const uint8_t index = m_ui8NbOfActiveProjectiles;
    if (!(m_ui8MaxProjectiles > index)) {
        owner->MessageProc(0x2897, const_cast<ProjectileTarget*>(target));  // vt+0x1c
        return 0;
    }
    Record* p = RecordAt(this, index);
    p->m_target.m_unk0c = target->m_unk0c;
    p->m_target.m_pTarget = target->m_pTarget;
    p->m_target.m_pHotSpot = target->m_pHotSpot;
    SpawnInstance(data, index, pos, dir, speed, owner, nullptr, target->m_pDamage);  // 0x0058c948
    m_ui8NbOfActiveProjectiles = static_cast<uint8_t>(m_ui8NbOfActiveProjectiles + 1);
    return 1;
}

// 0x00596a58 CKProjectileTypeTargetLock_UpdateMotion. Not landed (bit 2): the previous position kept; while the target
// accepts the lock (message 0x402 answered 0): its aim point T (its hot spot's world position, else message 0x400 with
// the node's LTM position, the record's index and the pool), the direction turned toward T by at most dt times the turn
// rate (the rate lerped from +0x34 at the range +0x3c to +0x38 at the target; the full turn when the step covers it),
// the speed kept; else the target dropped and the motion ballistic (the drag, gravity, the velocity renormalised, its
// length the speed). Then the move, vfA8 above data +0x34 (flag 0x40), the ribbon (option 0x80) and the sound once the
// camera is within data +0x48 (option 0x200000). The age advances in every case.
void CKProjectileTypeTargetLock::UpdateMotion(uint8_t index, float dt) {
    Record* p = RecordAt(this, index);
    if ((p->m_flags64 & 4u) == 0) {
        p->m_vPrevPos.x = p->m_vPos.x;
        p->m_vPrevPos.z = p->m_vPos.z;
        p->m_vPrevPos.y = p->m_vPos.y;
        IKSerializable* target = p->m_target.m_pTarget;
        uint32_t answer = 0;  // the 0x402 block (uninitialised in the original; the answer is not read)
        float speed;
        if (target != nullptr && target->MessageProc(0x402, &answer) == 0) {  // vt+0x1c
            const float sx = p->m_vDir.x;
            const float sy = p->m_vDir.y;
            const float sz = p->m_vDir.z;
            CVector3 aim;
            if (p->m_target.m_pHotSpot != nullptr) {
                p->m_target.m_pHotSpot->GetWorldPosition(&aim);  // 0x000ce790 through 0x0098fd50
            } else {
                SAimPointQuery query;
                const RwV3d& at = static_cast<CSGMovable*>(NodeOf(target))->m_pRwFrame->ltm.pos;
                query.m_point = {at.x, at.y, at.z};
                query.m_pHotSpot = nullptr;
                query.m_pHero = this;
                query.m_ui8Index = p->m_target.m_unk0c;
                target->MessageProc(0x400, &query);  // vt+0x1c
                aim = query.m_point;
            }
            float dy = aim.y - p->m_vPos.y;
            float dx = aim.x - p->m_vPos.x;
            float dz = aim.z - p->m_vPos.z;
            float distance = MathSqrtf(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));
            if (distance == kZero) {
                distance = kZero;
            } else {
                const float inverse = kOne / distance;
                dz = dz * inverse;
                dx = dx * inverse;
                dy = dy * inverse;
            }
            const float range = m_fTurnRange;
            float closeness = kZero;
            if (!(distance > range)) closeness = range - distance;  // bgt: a NaN takes the difference
            const float rateAtRange = m_fTurnRateAtRange;
            float nx = sx;
            float ny = sy;
            float nz = sz;
            if (dx != sx || dy != sy || dz != sz) {  // fcmpu / bne: a NaN turns
                const float span = m_fTurnRateAtTarget - rateAtRange;
                const float ey = dy - sy;
                const float ex = dx - sx;
                const float ez = dz - sz;
                nx = dx;
                nz = dz;
                ny = dy;
                const float rate = ppc::fmadds(closeness / range, span, rateAtRange);
                const float turn = dt * rate;
                const float gap2 = ppc::fmadds(ez, ez, ppc::fmadds(ex, ex, ey * ey));
                if (!(turn * turn > gap2)) {  // bgt: a NaN steps
                    const float k = turn * rwInvSqrt(gap2);  // 0x000114d8 Math_InvSqrtf through 0x00990120
                    nz = ppc::fmadds(ez, k, sz);
                    nx = ppc::fmadds(ex, k, sx);
                    ny = ppc::fmadds(ey, k, sy);
                }
            }
            p->m_vDir.z = nz;
            p->m_vDir.x = nx;
            p->m_vDir.y = ny;
            speed = p->m_fSpeed;
        } else {
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
            p->m_fSpeed = length;
            speed = length;
        }
        const float step = dt * speed;
        const float posZ = ppc::fmadds(step, p->m_vDir.z, p->m_vPos.z);
        const float posX = ppc::fmadds(step, p->m_vDir.x, p->m_vPos.x);
        const float posY = ppc::fmadds(step, p->m_vDir.y, p->m_vPos.y);
        p->m_vPos.z = posZ;
        p->m_vPos.x = posX;
        p->m_vPos.y = posY;
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
