// CKProjectileTypeBallisticPFX.cpp - reconstructed original translation unit 0x586258-0x58e9c0 (GAME_TOC2, main_toc2), 36 functions, 33 live.
// Primary class: CKProjectileTypeBallisticPFX  key 0x140c  category Logic  size ?  vtable 0xb2e208
// Other owners: CKProjectileType (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x586258  CKProjectileTypeBallisticPFX_AddFxEmitPointAndStart_maybe  [dead]
//   [x] 0x586338  CKProjectileTypeBallisticPFX_vfA8
//   [x] 0x586340  CKProjectileType_UpdateInstanceTrailSegment_maybe
//   [x] 0x5864b8  CKProjectileTypeBallisticPFX_vfAC
//   [ ] 0x5864d8  CKProjectileTypeBallisticPFX_GetTargetPositionFromHook_maybe  [dead]
//   [ ] 0x5865a8  RegisterCKProjectileTypeBallisticPFXClass
//   [ ] 0x586620  _GLOBAL__I_586620
//   [x] 0x586630  CKProjectileTypeBallisticPFX_PlayInstanceSound_maybe
//   [x] 0x5866d8  CKProjectileTypeBallisticPFX_DeleteArray
//   [x] 0x586778  CKProjectileTypeBallisticPFX_CreateArray
//   [x] 0x586830  CKProjectileTypeBallisticPFX_IsDead
//   [x] 0x5868e8  CKProjectileTypeBallisticPFX_Create
//   [x] 0x586940  CKProjectileTypeBallisticPFX_ComputeAttractionVector_maybe
//   [ ] 0x586ba0  CKProjectileTypeBallisticPFX_SumAttractionVectors_maybe  [dead]
//   [x] 0x586d48  CKProjectileTypeBallisticPFX_ComputeSteering_maybe
//   [x] 0x587218  CKProjectileTypeBallisticPFX_UpdateOrientation
//   [x] 0x587d00  CKProjectileTypeBallisticPFX_ProcessDamageContacts
//   [x] 0x588278  CKProjectileTypeBallisticPFX_UpdateMotion
//   [x] 0x5886d0  CKProjectileTypeBallisticPFX_KillInstance
//   [x] 0x588d08  CKProjectileTypeBallisticPFX_SpawnAtPoint_maybe
//   [x] 0x58a0f8  CKProjectileTypeBallisticPFX_LaunchAtPointEx
//   [x] 0x58a1c8  CKProjectileTypeBallisticPFX_LaunchAtPoint
//   [x] 0x58a238  CKProjectileTypeBallisticPFX_OnDeath
//   [x] 0x58a948  CKProjectileTypeBallisticPFX_CollideModeC_maybe
//   [x] 0x58b498  CKProjectileTypeBallisticPFX_CollideModeB_maybe
//   [x] 0x58c148  CKProjectileTypeBallisticPFX_CollideSweepA
//   [x] 0x58c878  CKProjectileTypeBallisticPFX_UpdateCollision
//   [x] 0x58c948  CKProjectileTypeBallisticPFX_SpawnInstance
//   [x] 0x58e160  CKProjectileTypeBallisticPFX_LaunchEx
//   [x] 0x58e240  CKProjectileTypeBallisticPFX_Launch
//   [x] 0x58e2c0  CKProjectileTypeBallisticPFX_Destroy
//   [x] 0x58e2e8  CKProjectileTypeBallisticPFX_MessageProc
//   [x] 0x58e3b8  CKProjectileTypeBallisticPFX_Save
//   [x] 0x58e3c0  CKProjectileTypeBallisticPFX_PostLoad
//   [x] 0x58e408  CKProjectileTypeBallisticPFX_RecursiveRegistration
//   [x] 0x58e508  CKProjectileTypeBallisticPFX_Load
//
//   [ ] 0x9cb3d8  CKProjectileTypeBallisticPFX_IsKindOfClass  [inline]
//   [ ] 0x9cb400  CKProjectileTypeBallisticPFX_GetClassType  [inline]
//   [ ] 0x9cb408  CKProjectileTypeBallisticPFX_GetClassID  [inline]
//   [ ] 0x9cb410  CKProjectileTypeBallisticPFX_Destructor  [inline]
//   [ ] 0x9cb430  CKProjectileTypeBallisticPFX_DeletingDestructor  [inline]
#include "k2000/logic/CKProjectileTypeBallisticPFX.h"

#include <cmath>
#include <cstring>

#include "Renderware/rpprtstd/RpPrtStd.h"
#include "Renderware/rwcore/RwCamera.h"
#include "Renderware/rwcore/RwFrameList.h"
#include "Renderware/rwcore/RwMatrix.h"
#include "Spyro2008/groups/IKGrpHero.h"
#include "crt/ppc_ops.h"
#include "crt/xatan.h"
#include "k2000/cameras/CKSrvCamera.h"
#include "k2000/components/CKQuakeCameraLauncher.h"
#include "k2000/core/Stub.h"
#include "k2000/dictionaries/CKSoundDictionaryID.h"
#include "k2000/fx/IKFx.h"
#include "k2000/geometry/CGeometry.h"
#include "k2000/hooks/GroundContact.h"
#include "k2000/hooks/IKHook.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/logic/CKParticlesEffectFxData.h"
#include "k2000/logic/CKProjectileDataTypeBallisticPFX.h"
#include "k2000/logic/IKFxData.h"
#include "k2000/logic/fx/CKExplosionNodeFx.h"
#include "k2000/logic/fx/CKFireBallNodeFx.h"
#include "k2000/logic/fx/CKShockWaveNodeFx.h"
#include "k2000/logic/render/CMaterial.h"
#include "k2000/logic/sound/CKSound.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/CKGrpMeca.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/IKGrpEnemy.h"
#include "k2000/render/CRenderer.h"
#include "k2000/scenegraph/CKDynamicBoundingSphere.h"
#include "k2000/scenegraph/CNode.h"
#include "k2000/scenegraph/CParticlesNodeFx.h"
#include "k2000/scenegraph/CSGBranch.h"
#include "k2000/scenegraph/CSGLeaf.h"
#include "k2000/scenegraph/CTrailNodeFx.h"
#include "k2000/scenegraph/IKBoundingVolume.h"
#include "k2000/services/CKSrvCollision.h"
#include "k2000/services/CKSrvFx.h"

namespace {
// The shared constants (zero in the EBOOT's BSS, filled by static initialisers; TOC2 -0x71e8 / -0x71e4 / -0x71d8 /
// -0x7244 hold their addresses).
const CVector3 kAxisX = {1.0f, 0.0f, 0.0f};       // 0x00c50d34
const CVector3 kAxisY = {0.0f, 1.0f, 0.0f};       // 0x00c50d40
const CVector3 kAxisZ = {0.0f, 0.0f, 1.0f};       // 0x00c50d4c
const CVector3 kNullVector = {0.0f, 0.0f, 0.0f};  // 0x00c50d64
constexpr float kZero = 0.0f;                     // TOC2 -0x7218
constexpr float kOne = 1.0f;                      // TOC2 -0x71f4
constexpr float kMinusOne = -1.0f;                // TOC2 -0x71dc
constexpr float kVertical = 0.99000001f;          // TOC2 -0x71ec (0x3f7d70a4; -0x71f0 its negative)
constexpr float kTwoPi = 6.28318548f;             // TOC2 -0x71d4 (0x40c90fdb)
constexpr float kRadToDeg = 57.2957802f;          // TOC2 -0x71e0 (0x42652ee1)
constexpr float kAlphaScale = 255.0f;             // TOC2 -0x71cc
constexpr float kMinSpeed = 0.1f;                 // TOC2 -0x720c (0x3dcccccd)
constexpr float kHalf = 0.5f;                     // TOC2 -0x71a0
constexpr float kMaxSpeed = 999.0f;               // TOC2 -0x719c
constexpr float kRandToUnit = -3.05180438e-05f;   // TOC2 -0x71a8 (0xb8000080)
constexpr float kRandMax = 65535.0f;              // TOC2 -0x71a4 (0x477fff00)
constexpr uint32_t kMinRadiusBits = 0x3a83126fu;  // 0.001f (TOC2 -0x71d0; stored as a word or a float)

using Projectile = CKProjectileTypeBallisticPFX::Projectile;

Projectile* ProjectileAt(const CKProjectileTypeBallisticPFX* pool, uint32_t index) {
    return reinterpret_cast<Projectile**>(pool->m_apProjectileList)[index];
}
CKProjectileDataTypeBallisticPFX* DataOf(const Projectile* projectile) {
    return static_cast<CKProjectileDataTypeBallisticPFX*>(projectile->m_pData);
}
RwFrame* FrameOf(CSGLeaf* node) { return node->m_pRwFrame; }
CSGMovable* MovableOf(CSGLeaf* node) { return static_cast<CSGMovable*>(node); }
CKSrvCollision* Collision() { return static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision); }
CKSrvFx* FxService() { return static_cast<CKSrvFx*>(g_pEngine->m_srvFx); }
CKSrvCamera* Camera() { return static_cast<CKSrvCamera*>(g_pEngine->m_srvCamera); }
CKDynamicBoundingSphere* VolumeOf(const Projectile* p) { return static_cast<CKDynamicBoundingSphere*>(p->m_pVolume); }
CTrailNodeFx* TrailOf(const CKProjectileTypeBallisticPFX* pool) { return static_cast<CTrailNodeFx*>(pool->m_unk28); }

// 0x00010690 Math_Sqrtf (fsqrts; through TocBridge_Math_Sqrtf 0x0098fc10).
inline float MathSqrtf(float x) { return std::sqrt(x); }

float WordF32(uint32_t bits) {
    float value;
    std::memcpy(&value, &bits, sizeof(value));
    return value;
}

// The frame's position set (the identity flag cleared), the frame marked dirty (RwFrame_MarkDirty 0x00010698).
void SetFramePosition(RwFrame* frame, const CVector3& pos) {
    frame->modelling.pos.x = pos.x;
    frame->modelling.pos.y = pos.y;
    frame->modelling.pos.z = pos.z;
    frame->modelling.flags &= 0xfffdffffu;
    RwFrame_MarkDirty(frame);
}

// The frame's modelling axes scaled by `scale` (the identity and orthonormal flags cleared), the frame marked dirty.
void ScaleAxes(CSGLeaf* node, float scale) {
    RwFrame* frame = FrameOf(node);
    RwMatrix& m = frame->modelling;
    m.right.x = scale * m.right.x;
    m.right.y = scale * m.right.y;
    m.right.z = scale * m.right.z;
    m.up.x = scale * m.up.x;
    m.up.y = scale * m.up.y;
    m.up.z = scale * m.up.z;
    m.at.x = scale * m.at.x;
    m.at.z = scale * m.at.z;
    m.at.y = scale * m.at.y;
    m.flags &= 0xfffdfffeu;
    RwFrame_MarkDirty(frame);
}

// The geometries' alpha (CGeometry colour byte +0x23) and their "alpha blended" property bit 11 (vt+0x60 UpdateProperties
// when it changes); 0xff clears the bit everywhere. A geometry with property bit 12 and a material of mode 1..6 keeps
// 0xff and the bit cleared (the inlined walk of UpdateOrientation; SpawnInstance / SpawnAtPoint inline the 0xff one).
void SetGeometriesAlpha(CSGLeaf* node, uint8_t alpha) {
    CGeometry* geometry = static_cast<CGeometry*>(static_cast<CNode*>(node)->m_lGeometryList);
    if (geometry == nullptr) return;
    if (alpha == 0xff) {
        for (; geometry != nullptr; geometry = geometry->m_pNext) {
            geometry->m_cGeometryColor[3] = 0xff;
            const uint32_t bits = geometry->m_BitProperties;
            if (((bits >> 11) & 1u) != 0) {
                geometry->m_BitProperties = bits & 0xfffff7ffu;
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
        const uint32_t bits = geometry->m_BitProperties;
        if (((bits >> 11) & 1u) != blend) {
            geometry->m_BitProperties = (bits & 0xfffff7ffu) | (blend << 11);
            geometry->UpdateProperties();  // vt+0x60
        }
    }
}

// The pool option 0x20's emission point (inlined after a hit): the projectile's position appended to the particle node
// +0x24's points (at most 0x40; scene flag 0x2000), the node emitting (flags 0x200 and 0x400 on, 0x80000 off, the
// emission speed adjustment 0, the emitter active and emitting).
void AddEmissionPoint(CKProjectileTypeBallisticPFX* pool, const Projectile* p) {
    CParticlesNodeFx* node = static_cast<CParticlesNodeFx*>(pool->m_unk24);
    const uint32_t count = node->m_ui8NbActivePoints;
    if (count <= 0x3f) {
        RwV3d* point = &node->m_pAdvEmtPointList->pointList[count];
        point->z = p->m_vPos.z;
        point->x = p->m_vPos.x;
        point->y = p->m_vPos.y;
        node->m_sgProperties = (node->m_sgProperties & ~0x2000u) | 0x2000u;
        node->m_ui8NbActivePoints = static_cast<uint8_t>(node->m_ui8NbActivePoints + 1);
        node = static_cast<CParticlesNodeFx*>(pool->m_unk24);
    }
    node->m_sgProperties = ((node->m_sgProperties | 0x200u) | 0x400u) & ~0x80000u;
    node->m_fEmissionSpeedAdjustment = kZero;
    node->m_pRpPrtStdEmitter->flag |= rpPRTSTDEMITTERFLAGACTIVE | rpPRTSTDEMITTERFLAGEMIT;  // 0xa
}

// The emission point when the pool has option 0x20 and the projectile is faster than the data's +0x34 (ble: a NaN
// leaves none).
void MaybeAddEmissionPoint(CKProjectileTypeBallisticPFX* pool, const Projectile* p) {
    if ((pool->m_baOptions & 0x20u) == 0) return;
    if (!(p->m_fSpeed > DataOf(p)->m_unk34)) return;
    AddEmissionPoint(pool, p);
}

// The impact / death shock wave (data +0x08) from the FX service's pool (the inlined CKSrvFx::AcquireFx), for the pool:
// with a volume its owner as the damage owner, the data's owner type (+0x4c) and flags (+0x4e); at `position`, triggered
// and released (vt+0x54). `ownerUnchecked`: the caller reads the volume's owner without testing the volume (see
// CollideModeB).
void TriggerShockWave(CKProjectileTypeBallisticPFX* pool, const Projectile* p, const CVector3* position,
                      bool ownerUnchecked) {
    IKFx* fx = FxService()->AcquireFx(static_cast<IKFxData*>(DataOf(p)->m_unk08), pool);
    if (fx == nullptr) return;
    CKShockWaveNodeFx* wave = static_cast<CKShockWaveNodeFx*>(fx);
    IKBoundingVolume* volume = static_cast<IKBoundingVolume*>(p->m_pVolume);
    if (volume != nullptr || ownerUnchecked) {
        // BUG(original): with `ownerUnchecked` a projectile without a volume reads its owner at address 0x24 (a fault
        // on the PS3); dotd uses no owner. Every LVL010 data has a volume (+0x44); the collision pool can run out.
        wave->SetDamageOwner(volume != nullptr ? volume->m_pOwner : nullptr, pool);  // 0x001d26f0
        wave->SetDamageType(DataOf(p)->m_unk4c, pool);                               // 0x001d26c8
        wave->SetDamageFlags(DataOf(p)->m_unk4e, pool);                              // 0x001d26a0
    }
    wave->SetPosition(position, pool);  // 0x001d2cd0
    wave->Trigger(pool);                // 0x001d2cc8 -> 0x001d2928
    wave->ReleaseReservation(pool);     // vt+0x54
}

// The pool's ground test parameters back to the projectile's half height (data +0x30 times the scale) and twice it.
void ResetGroundParams(CKProjectileTypeBallisticPFX* pool, uint8_t index) {
    const Projectile* p = ProjectileAt(pool, index);
    pool->m_GrdContDatasIn.m_fDeltaMax = DataOf(p)->m_unk30 * p->m_fScale;
    const float half = DataOf(p)->m_unk30 * p->m_fScale;
    pool->m_GrdContDatasIn.m_fObjectHeight = half + half;
}

// The collision modes' common start: the probe point (the position, half height lower), a fall deepening the test
// (ModeB / ModeC: only when falling, `clampFall` false; SweepA: a rise counts as no fall, `clampFall` true), the ground
// under it (GroundProbePoints_maybe 0x00196540 through its TOC bridge).
void ProbeGround(CKProjectileTypeBallisticPFX* pool, uint8_t index, bool clampFall) {
    Projectile* p = ProjectileAt(pool, index);
    CVector3 point = p->m_vPos;
    point.y = p->m_vPos.y - DataOf(p)->m_unk30 * p->m_fScale;
    float fall = p->m_vPrevPos.y - p->m_vPos.y;
    bool set = true;
    if (clampFall) {
        if (fall < kZero) fall = kZero;  // blt (a NaN stays)
    } else {
        set = fall > kZero;  // ble skips
    }
    if (set) {
        pool->m_GrdContDatasIn.m_fDeltaMax = ppc::fmadds(DataOf(p)->m_unk30, p->m_fScale, fall);
        const float half = DataOf(ProjectileAt(pool, index))->m_unk30 * ProjectileAt(pool, index)->m_fScale;
        pool->m_GrdContDatasIn.m_fObjectHeight = fall + (half + half);
    }
    const float points[3] = {point.x, point.y, point.z};
    Collision()->GroundProbePoints(reinterpret_cast<const CGroundContactDatasIn*>(&pool->m_GrdContDatasIn),
                                   reinterpret_cast<CGroundContactDatasInOut*>(&p->m_GrdContDatasInOut), points, 1);
}

// The wall raycast of the collision modes: from the previous position along this frame's motion, the projectile's
// half height as the height (CKSrvCollision_RaycastWalls_maybe 0x00198438 through its TOC bridge).
uint8_t RaycastMotion(const Projectile* p, CLine* line, CGroundEdgeDatasOut* out) {
    line->m_start = p->m_vPrevPos;
    line->m_VectDir.x = p->m_vPos.x - p->m_vPrevPos.x;
    line->m_VectDir.y = p->m_vPos.y - p->m_vPrevPos.y;
    line->m_VectDir.z = p->m_vPos.z - p->m_vPrevPos.z;
    return Collision()->RaycastWalls(line, DataOf(p)->m_unk30 * p->m_fScale, out, 0, nullptr, 1);
}

// Landed (mode C): flag bit 2, the volume no longer damaging (its bit 2 off) and 0x2801 to its owner with the position.
void Land(Projectile* p) {
    p->m_flags64 = static_cast<uint8_t>((p->m_flags64 & 0xfbu) | 4u);
    IKBoundingVolume* volume = static_cast<IKBoundingVolume*>(p->m_pVolume);
    if (volume == nullptr) return;
    volume->m_ba8Infos = static_cast<uint8_t>(volume->m_ba8Infos & 0xfbu);
    if (volume->m_pOwner != nullptr) volume->m_pOwner->MessageProc(0x2801, &p->m_vPos);  // vt+0x1c
}

// A bounce's message: 0x2800 to the volume's owner with the position.
void NotifyBounce(Projectile* p) {
    IKBoundingVolume* volume = static_cast<IKBoundingVolume*>(p->m_pVolume);
    if (volume == nullptr || volume->m_pOwner == nullptr) return;
    volume->m_pOwner->MessageProc(0x2800, &p->m_vPos);  // vt+0x1c
}

// The random rotation of a launch (data flag 0x100): three Rand_Int draws, a turn of up to a full circle about X, Y and
// Z in this order (CSGMovable_RotateInPlace 0x000d11b0 in degrees).
void RandomRotation(CSGLeaf* node) {
    uint32_t r = static_cast<uint32_t>(Rand_Int()) & 0xffffu;  // 0x00011500 through 0x0098fd10
    MovableOf(node)->RotateInPlace(&kAxisX.x, ((static_cast<float>(r) / kRandMax) * kTwoPi) * kRadToDeg);
    r = static_cast<uint32_t>(Rand_Int()) & 0xffffu;
    MovableOf(node)->RotateInPlace(&kAxisY.x, ((static_cast<float>(r) / kRandMax) * kTwoPi) * kRadToDeg);
    r = static_cast<uint32_t>(Rand_Int()) & 0xffffu;
    MovableOf(node)->RotateInPlace(&kAxisZ.x, ((static_cast<float>(r) / kRandMax) * kTwoPi) * kRadToDeg);
}

// The launches' common volume setup (data +0x44): a projectile volume from the collision service (unless 0x32 or more
// are used) hung under the node at its origin, with the radius (<= 0: 0.001), infos bits 3, 5, 2 and 7, the owner, no
// motion, the data's owner type and flags. Without data +0x44 a volume kept from an earlier launch is set up the same.
// `damage`: SpawnInstance stores it (+0x1c), SpawnAtPoint leaves the field.
void SetupVolume(Projectile* p, IKSerializable* owner, const CVector3* pos, float radius, bool setDamage,
                 IKSerializable* damage) {
    if (DataOf(p)->m_unk44 != 0) {
        if (p->m_pVolume == nullptr) {
            if (Collision()->m_ui8NbProjectileUsed > 0x31) return;
            p->m_pVolume = Collision()->AcquireDynSphere();  // 0x00192a70
            if (p->m_pVolume == nullptr) return;
        }
    } else if (p->m_pVolume == nullptr) {
        return;
    }
    CKDynamicBoundingSphere* volume = VolumeOf(p);
    if (volume->m_pParent != nullptr) volume->m_pParent->RemoveChild(volume);  // vt+0x78
    static_cast<CSGBranch*>(p->m_pNode)->AddChild(volume);                     // vt+0x70
    SetFramePosition(VolumeOf(p)->m_pRwFrame, kNullVector);
    if (radius <= kZero) {
        std::memcpy(&VolumeOf(p)->m_fRadius, &kMinRadiusBits, sizeof(kMinRadiusBits));
    } else {
        VolumeOf(p)->m_fRadius = radius;
    }
    volume = VolumeOf(p);
    volume->m_ba8Infos = static_cast<uint8_t>((volume->m_ba8Infos & 0xf7u) | 8u);
    volume->m_ba8Infos = static_cast<uint8_t>((volume->m_ba8Infos & 0xdfu) | 0x20u);
    volume->m_ba8Infos = static_cast<uint8_t>((volume->m_ba8Infos & 0xfbu) | 4u);
    volume->m_pOwner = owner;
    volume->m_v3WorldMove = kNullVector;
    volume->m_v3OldPos = *pos;
    volume->m_v3LastWorldPos = *pos;
    volume->m_ui16PropertiesFlags = 0;
    volume->m_ui8OwnerType = 0;
    volume->m_ui8OwnerType = DataOf(p)->m_unk4c;
    volume->m_ui16PropertiesFlags = static_cast<uint16_t>(DataOf(p)->m_unk4e | volume->m_ui16PropertiesFlags);
    if (setDamage) volume->m_unk1c = damage;
    volume->m_ba8Infos = static_cast<uint8_t>((volume->m_ba8Infos & 0x7fu) | 0x80u);
}

// The launch explosion (data flag 0x2000000, data +0x14) at the projectile, turned along its direction
// (CKExplosionNodeFx_SetPosition 0x001b6438), triggered (launch 0) and released, for the pool.
void LaunchExplosion(CKProjectileTypeBallisticPFX* pool, Projectile* p) {
    if ((DataOf(p)->m_ui32Flags & 0x2000000u) == 0) return;
    IKFx* fx = FxService()->AcquireFx(static_cast<IKFxData*>(DataOf(p)->m_unk14), pool);
    if (fx == nullptr) return;
    CKExplosionNodeFx* explosion = static_cast<CKExplosionNodeFx*>(fx);
    explosion->SetPosition(&p->m_vDir, &p->m_vPos, pool);  // 0x001b6438
    explosion->Trigger(pool, 0);                           // 0x001b82a8
    explosion->ReleaseReservation(pool);                   // vt+0x54
}

// The particle effect following the node (data flag 0x40, data +0x10): the effect data attached to the node (no hot
// spot), a pooled effect started for the pool.
void StartParticleFx(CKProjectileTypeBallisticPFX* pool, Projectile* p) {
    CKParticlesEffectFxData* fxData = static_cast<CKParticlesEffectFxData*>(DataOf(p)->m_unk10);
    fxData->m_pAttachOwner = p->m_pNode;
    fxData->m_pAttachHotSpot = nullptr;
    p->m_pParticleFx = FxService()->AcquireFx(static_cast<CKParticlesEffectFxData*>(DataOf(p)->m_unk10), pool);
}

// The fire ball (data flag 0x1000, data +0x0c): a pooled CKFireBallNodeFx following the node.
void StartFireBall(CKProjectileTypeBallisticPFX* pool, Projectile* p, const CVector3* direction) {
    p->m_pFireBall = FxService()->AcquireFx(static_cast<IKFxData*>(DataOf(p)->m_unk0c), pool);
    if (p->m_pFireBall != nullptr) {
        // 0x001ba5a8 CKFireBallNodeFx_SetFollowNode (the node) and 0x001ba5e0 CKFireBallNodeFx_SetDirection (`direction`),
        // both for the pool (C2.8 port-rest R06). No LVL010 data sets flag 0x1000.
        CKFireBallNodeFx* fireBall = static_cast<CKFireBallNodeFx*>(p->m_pFireBall);
        fireBall->SetFollowNode(p->m_pNode, pool);
        static_cast<CKFireBallNodeFx*>(p->m_pFireBall)->SetDirection(direction, pool);
    }
}

// The trail ribbon of a launch (pool option 0x80; CTrailNodeFx_SetRibbonActive_maybe 0x009bdfb8 inlined): a ribbon
// still on is switched off and laid out between its old anchors, the anchors moved either side of the projectile,
// the ribbon switched on and laid out between them.
void RestartTrail(CKProjectileTypeBallisticPFX* pool, uint8_t index) {
    const uint32_t ribbon = ProjectileAt(pool, index)->m_ui8Index;
    TrailOf(pool)->SetRibbonActive(ribbon, 0, 1);
    pool->UpdateInstanceTrailSegment(index);
    TrailOf(pool)->SetRibbonActive(ProjectileAt(pool, index)->m_ui8Index, 1, 1);
}

// The looping sound of a launch (pool option 0x200000): played at once when the data's camera distance (+0x48) is not
// positive (cror lt|eq), else left for UpdateMotion (flag bit 3 cleared).
void StartSound(CKProjectileTypeBallisticPFX* pool, uint8_t index, Projectile* p) {
    if ((pool->m_baOptions & 0x200000u) == 0) return;
    if (DataOf(p)->m_unk48 <= kZero) {
        pool->PlayInstanceSound(index);  // inlined in the original
    } else {
        p->m_flags64 = static_cast<uint8_t>(p->m_flags64 & 0xf7u);
    }
}

// The KStub_Return0_265a18 the hazard query calls on the enemy group: a stub that returns 0.
IKSerializable* EnemyGroupHazardSource(int32_t /*key*/) { return nullptr; }

// The hazard query block of message 0xc32 (CKHkS08Hero_6.cpp's HazardHitQuery: the PS3 layout).
struct HazardQuery {
    IKSerializable* m_hero;      // +0x00
    IKBoundingVolume* m_volume;  // +0x04
    float m_dirX;                // +0x08
    float m_dirZ;                // +0x0c
    uint32_t m_unk10;            // +0x10
    CVector3 m_point;            // +0x14
    int32_t m_kind;              // +0x20
    uint8_t m_damage;            // +0x24
};
}  // namespace

// 0x0058e508 CKProjectileTypeBallisticPFX_Load: IKProjectileType's data, then (level data only) two
// references, per projectile two references, a word, a reference and a byte (13 + 8 * count + 9 bytes).
int32_t CKProjectileTypeBallisticPFX::Load(IKFile* file, int32_t type) {
    IKProjectileType::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    IKFile_ReadRef(file, &m_unk24);
    IKFile_ReadRef(file, &m_unk28);
    m_GrdContDatasIn.m_fDeltaMax = 1.0f;      // TOC1 -0x7128
    m_GrdContDatasIn.m_fObjectHeight = 2.0f;  // TOC1 -0x7124
    const uint32_t count = m_ui8MaxProjectiles;
    // PS3: count << 2 and (count * PS3 record size) masked to 16 bits (rlwinm 0,16,28); a byte count never
    // reaches the mask, so native sizes are used.
    Projectile** list = static_cast<Projectile**>(Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(Projectile*))));
    Projectile* projectiles = static_cast<Projectile*>(Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(Projectile))));
    m_aProjectiles = projectiles;
    m_apProjectileList = reinterpret_cast<void**>(list);
    for (uint8_t i = 0; i < m_ui8MaxProjectiles; ++i) {
        Projectile* p = &projectiles[i];
        list[i] = p;
        CSGLeaf* node = nullptr;
        IKFile_ReadRef(file, &node);
        IKFile_ReadRef(file, &p->m_pQuake);
        p->m_pNode = node;
        if (node != nullptr) node->m_sgProperties = (node->m_sgProperties & ~0x4u) | 0x4u;
        p->m_pOwner = nullptr;
        p->m_pVolume = nullptr;
        p->m_vPos = kNullVector;      // 0x00c50d64 (TOC1 -0x7120)
        p->m_vPrevPos = kNullVector;  // 0x00c50d64
        p->m_vDir = kAxisZ;           // 0x00c50d4c (TOC1 -0x711c): the Z axis once the static initialisers ran
        p->m_fSpeed = 0.0f;
        p->m_GrdContDatasInOut.m_i32FaceIndex = -1;
        p->m_GrdContDatasInOut.m_eContactStatus = 3;
        p->m_GrdContDatasInOut.m_ui8SectorNumber = 0;
        p->m_GrdContDatasInOut.m_pGround = nullptr;
        p->m_ui8Index = i;
        p->m_fLifetime = 1.0f;
        p->m_pParticleFx = nullptr;
        p->m_flags64 = 0;
        p->m_fAge = 0.0f;
        p->m_pFireBall = nullptr;
    }
    ReadS32LE(file, &m_unk2c);
    IKFile_ReadRef(file, &m_unk30);
    ReadU8(file, &Unk22());
    return 1;
}

// 0x0058e2c0 CKProjectileTypeBallisticPFX_Destroy: IKProjectileType_Destroy 0x001f3c38 (through its TOC bridge): both
// lists freed. BUG(original): the pointers are kept (the next Load replaces them).
void CKProjectileTypeBallisticPFX::Destroy() { IKProjectileType::Destroy(); }

// 0x0058e2e8 CKProjectileTypeBallisticPFX_MessageProc. 0xc32 (the hero's hazard query, CKHkS08Hero_6.cpp): the enemy
// group's KStub_Return0_265a18 (+0x2c, through its TOC bridge) gives the source whose +0x08..+0x10 (the direction and a
// word) and byte +0x24 (the damage) answer, with the query's volume its frame's LTM position (+0x80) as the point;
// returns 0. BUG(original): the stub returns null, so the answer reads address 0 (a fault on the PS3); dotd answers
// nothing (no LVL010 path sends 0xc32 to a projectile pool). Any other message: 1.
int32_t CKProjectileTypeBallisticPFX::MessageProc(uint16_t message, void* data) {
    if (message != 0xc32) return 1;
    const uint8_t* source = reinterpret_cast<const uint8_t*>(EnemyGroupHazardSource(m_unk2c));
    if (source == nullptr) return 0;  // BUG(original), see above
    // The answer as the original writes it (the source's words at +0x08 / +0x0c / +0x10, its byte at +0x24).
    HazardQuery* query = static_cast<HazardQuery*>(data);
    std::memcpy(&query->m_dirX, source + 0x08, sizeof(float));
    std::memcpy(&query->m_dirZ, source + 0x0c, sizeof(float));
    std::memcpy(&query->m_unk10, source + 0x10, sizeof(uint32_t));
    query->m_damage = source[0x24];
    if (query->m_volume != nullptr) {
        const RwV3d& at = static_cast<CSGLeaf*>(static_cast<IKSerializable*>(query->m_volume))->m_pRwFrame->ltm.pos;
        query->m_point = {at.x, at.y, at.z};
    }
    return 0;
}

// 0x0058e408 CKProjectileTypeBallisticPFX_RecursiveRegistration: the base's (KStub_Return1_1f3c90), then for the
// types outside 4..7 the sound dictionary (+0x30) and every projectile's camera quake (+0x80), vt+0x24 each.
void CKProjectileTypeBallisticPFX::RecursiveRegistration(int32_t type) {
    if (static_cast<uint32_t>(type) - 4u <= 3u) return;
    if (m_unk30 != nullptr) m_unk30->RecursiveRegistration(type);
    for (uint8_t i = 0; i < m_ui8MaxProjectiles; ++i) {
        // BUG(original): no null test (every LVL010 projectile has its CKQuakeCameraLauncher).
        reinterpret_cast<IKSerializable*>(ProjectileAt(this, i)->m_pQuake)->RecursiveRegistration(type);
    }
}

// 0x0058e3c0 CKProjectileTypeBallisticPFX_PostLoad
int32_t CKProjectileTypeBallisticPFX::PostLoad(int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    if ((m_baOptions & 0x80u) == 0) return 1;
    if (m_unk28 != nullptr) return 1;
    m_baOptions &= ~0x80u;
    return 1;
}

// 0x005864b8 CKProjectileTypeBallisticPFX_vfAC
float CKProjectileTypeBallisticPFX::GetProjectileAge(uint8_t index) { return ProjectileAt(this, index)->m_fAge; }

// 0x00586630 CKProjectileTypeBallisticPFX_PlayInstanceSound_maybe
void CKProjectileTypeBallisticPFX::PlayInstanceSound(uint8_t index) {
    Projectile* p = ProjectileAt(this, index);
    CKSound* sound = static_cast<CKSoundDictionaryID*>(m_unk30)->GetSound(p->m_ui8Index);  // 0x00112bc0
    if (sound != nullptr) {
        sound->SetAttachObject(p->m_pNode);  // 0x00111350
        sound->Play(0.0f);                   // 0x00111230
    }
    p->m_flags64 = static_cast<uint8_t>((p->m_flags64 & 0xf7u) | 8u);
}

// 0x00586340 CKProjectileType_UpdateInstanceTrailSegment_maybe (also inlined in UpdateMotion, SpawnInstance and
// SpawnAtPoint). The camera's real axes are CKSrvCamera +0x5bc / +0x5c8 (the side: direction x axis, fmsubs).
void CKProjectileTypeBallisticPFX::UpdateInstanceTrailSegment(uint8_t index) {
    Projectile* p = ProjectileAt(this, index);
    const uint32_t flags = DataOf(p)->m_ui32Flags;
    float sx, sy, sz;
    if ((flags & 0x100000u) != 0) {
        const RwMatrix& ltm = FrameOf(p->m_pNode)->ltm;
        const RwV3d& row = (flags & 0x80000u) != 0 ? ltm.right : ltm.up;
        sx = row.x;
        sy = row.y;
        sz = row.z;
    } else {
        const CVector3& axis = (flags & 0x80000u) != 0 ? Camera()->m_v3RealAxisY : Camera()->m_v3RealAxisZ;
        const CVector3 d = p->m_vDir;
        sz = ppc::fmsubs(axis.y, d.x, d.y * axis.x);
        sy = ppc::fmsubs(d.z, axis.x, axis.z * d.x);
        sx = ppc::fmsubs(d.y, axis.z, d.z * axis.y);
    }
    const float w = DataOf(p)->m_unk38;
    const float nw = -w;
    STrailNodeData* trail = TrailOf(this)->m_apTrailData[p->m_ui8Index];
    trail->m_v3Extrem1.z = ppc::fmadds(sz, nw, p->m_vPos.z);
    trail->m_v3Extrem1.x = ppc::fmadds(nw, sx, p->m_vPos.x);
    trail->m_v3Extrem1.y = ppc::fmadds(nw, sy, p->m_vPos.y);
    trail->m_v3Extrem2.z = ppc::fmadds(sz, w, p->m_vPos.z);
    trail->m_v3Extrem2.x = ppc::fmadds(w, sx, p->m_vPos.x);
    trail->m_v3Extrem2.y = ppc::fmadds(w, sy, p->m_vPos.y);
}

// 0x00586830 CKProjectileTypeBallisticPFX_IsDead: not alive (bit 0) is dead; data flag 0x8 dies slower than 0.1 (blt);
// data flag 0x10 dies past the lifetime (ble keeps it), with data +0x2c only while not drawn this frame (the node's
// +0x16 against the render frame counter 0x00c29694).
uint8_t CKProjectileTypeBallisticPFX::IsDead(uint8_t index) {
    const Projectile* p = ProjectileAt(this, index);
    if ((p->m_flags64 & 1u) == 0) return 1;
    const uint32_t flags = DataOf(p)->m_ui32Flags;
    if ((flags & 8u) != 0) {
        if (p->m_fSpeed < kMinSpeed) return 1;
    }
    if ((flags & 0x10u) == 0) return 0;
    if (!(p->m_fAge > p->m_fLifetime)) return 0;
    if (DataOf(p)->m_unk2c == 0) return 1;
    return p->m_pNode->m_ui16LastRenderedFrame == g_ui16RenderFrameCounter ? 0 : 1;
}

// 0x00586940 CKProjectileTypeBallisticPFX_ComputeAttractionVector_maybe. Once the age reached data +0x60 (cror gt|eq):
// the target's aim point (message 0x400 with an SAimPointQuery: index 0, the target node's LTM position, no hot spot,
// the pool as the asker); nearer than data +0x5c in the box distance (bge: a NaN counts as near) the vector to it,
// scaled to data +0x58 when its length is positive (cror lt|eq: else multiplied by 0). `dt` and `hittable` (the
// target's answer to 0x402) are not read.
CVector3 CKProjectileTypeBallisticPFX::ComputeAttractionVector(float /*dt*/, Projectile* projectile,
                                                               IKSerializable* target, const CVector3* pos,
                                                               IKSerializable* /*hittable*/) {
    CVector3 out = kNullVector;
    if (!(projectile->m_fAge >= DataOf(projectile)->m_unk60)) return out;
    struct {
        uint8_t m_ui8Index;          // +0x00
        CVector3 m_point;            // +0x04
        IKSerializable* m_pHotSpot;  // +0x10
        IKSerializable* m_pAsker;    // +0x14
    } query;
    const RwV3d& at = FrameOf(static_cast<CSGLeaf*>(static_cast<IKHook*>(target)->m_pKGLObject))->ltm.pos;
    query.m_point = {at.x, at.y, at.z};
    query.m_ui8Index = 0;
    query.m_pAsker = this;
    query.m_pHotSpot = nullptr;
    target->MessageProc(0x400, &query);  // vt+0x1c
    const CVector3 point = query.m_point;
    const float box = (std::fabs(point.x - pos->x) + std::fabs(point.y - pos->y)) + std::fabs(point.z - pos->z);
    if (!(box < DataOf(projectile)->m_unk5c)) return out;
    out.y = point.y + out.y;
    out.x = point.x + out.x;
    out.z = point.z + out.z;
    out.y = out.y - pos->y;
    out.x = out.x - pos->x;
    out.z = out.z - pos->z;
    const float length = MathSqrtf(ppc::fmadds(out.z, out.z, ppc::fmadds(out.x, out.x, out.y * out.y)));
    if (length <= kZero) {
        out.x = out.x * kZero;
        out.y = out.y * kZero;
        out.z = out.z * kZero;
        return out;
    }
    const float k = DataOf(projectile)->m_unk58 / length;
    out.z = k * out.z;
    out.x = k * out.x;
    out.y = k * out.y;
    return out;
}

// 0x00586d48 CKProjectileTypeBallisticPFX_ComputeSteering_maybe. The candidates (each with a node, +0x1c) are asked
// 0x402 (the byte block cleared first); one that answers 0 with a nonzero block pulls the projectile
// (ComputeAttractionVector). Each group's pulls are summed from the null vector, then added to the result.
CVector3 CKProjectileTypeBallisticPFX::ComputeSteering(float dt, Projectile* projectile, const CVector3* pos) {
    CVector3 out = kNullVector;
    CDefaultGameManager* manager = g_pEngine->m_gameManager;
    if (manager == nullptr) return out;
    // The heroes (CKGrpS08Hero_GetHeroList 0x002ca0f0 / GetHeroCount 0x002ca038 through their TOC bridges).
    if ((DataOf(projectile)->m_ui32Flags & 0x4000000u) != 0 && manager->m_unk04[1] != nullptr) {
        IKGrpHero* heroes = static_cast<IKGrpHero*>(manager->m_unk04[1]);
        IKSerializable** list = heroes->m_apHeroesCopy;
        const uint32_t count = heroes->GetHeroCount();
        if (list != nullptr) {
            float sx = kNullVector.x;
            float sy = kNullVector.y;
            float sz = kNullVector.z;
            for (uint32_t left = count; left != 0; --left) {
                IKSerializable* hero = *list++;
                if (hero == nullptr || static_cast<IKHook*>(hero)->m_pKGLObject == nullptr) continue;
                // The block: a word cleared, the answer's byte written at its start, tested as a word (nonzero either
                // way on both byte orders).
                uint32_t hittable = 0;
                if (hero->MessageProc(0x402, &hittable) != 0 || hittable == 0) continue;  // vt+0x1c
                const CVector3 pull = ComputeAttractionVector(dt, projectile, hero, pos, nullptr);
                sx = sx + pull.x;
                sy = sy + pull.y;
                sz = sz + pull.z;
            }
            out.x = sx + out.x;
            out.y = sy + out.y;
            out.z = out.z + sz;
        }
    }
    // The mechanism group's active actors (CKGrpMeca +0x2c / +0x30).
    if ((DataOf(projectile)->m_ui32Flags & 0x8000000u) != 0 && manager->m_unk04[2] != nullptr) {
        CKGrpMeca* meca = static_cast<CKGrpMeca*>(manager->m_unk04[2]);
        IKHook** list = meca->m_pUnk2c;
        const uint32_t count = meca->m_unk30;
        if (list != nullptr) {
            float sx = kNullVector.x;
            float sy = kNullVector.y;
            float sz = kNullVector.z;
            for (uint32_t left = count; left != 0; --left) {
                IKHook* actor = *list++;
                if (actor == nullptr || actor->m_pKGLObject == nullptr) continue;
                uint32_t hittable = 0;
                if (actor->MessageProc(0x402, &hittable) != 0 || hittable == 0) continue;
                const CVector3 pull = ComputeAttractionVector(dt, projectile, actor, pos, nullptr);
                sx = sx + pull.x;
                sy = sy + pull.y;
                sz = sz + pull.z;
            }
            out.x = out.x + sx;
            out.y = out.y + sy;
            out.z = out.z + sz;
        }
    }
    // The active enemies (IKGrpEnemy +0x58 / +0x120).
    if ((DataOf(projectile)->m_ui32Flags & 0x10000000u) != 0 && manager->m_unk04[0] != nullptr) {
        IKGrpEnemy* enemies = static_cast<IKGrpEnemy*>(manager->m_unk04[0]);
        float sz = kNullVector.z;
        float sx = kNullVector.x;
        float sy = kNullVector.y;
        const uint32_t count = enemies->m_ui32NbActiveEnemies;
        for (uint32_t i = 0; i != count; ++i) {
            IKSerializable* enemy = enemies->m_apActiveEnemies[i];
            if (enemy == nullptr || static_cast<IKHook*>(enemy)->m_pKGLObject == nullptr) continue;
            uint32_t hittable = 0;
            if (enemy->MessageProc(0x402, &hittable) != 0 || hittable == 0) continue;
            const CVector3 pull = ComputeAttractionVector(dt, projectile, enemy, pos, nullptr);
            sx = sx + pull.x;
            sy = sy + pull.y;
            sz = sz + pull.z;
        }
        out.x = out.x + sx;
        out.y = out.y + sy;
        out.z = out.z + sz;
    }
    return out;
}

// 0x00587218 CKProjectileTypeBallisticPFX_UpdateOrientation (the clamps keep the original's cror senses).
void CKProjectileTypeBallisticPFX::UpdateOrientation(uint8_t index, float dt) {
    Projectile* p = ProjectileAt(this, index);
    if (((p->m_flags64 >> 2) & 1u) != 0) {
        // Landed: only placed.
        SetFramePosition(FrameOf(p->m_pNode), p->m_vPos);
        return;
    }
    const uint32_t flags = DataOf(p)->m_ui32Flags;
    if ((flags & 1u) == 0) {
        // Not turned along the flight: placed, spun by the frame (Y, X, Z).
        SetFramePosition(FrameOf(p->m_pNode), p->m_vPos);
        if ((DataOf(p)->m_ui32Flags & 0x40000u) != 0) {
            MovableOf(p->m_pNode)->RotateInPlace(&kAxisY.x, dt * DataOf(p)->m_unk3c);  // 0x000d11b0
        }
        if ((DataOf(p)->m_ui32Flags & 0x400000u) != 0) {
            MovableOf(p->m_pNode)->RotateInPlace(&kAxisX.x, dt * DataOf(p)->m_unk3c);
        }
        if ((DataOf(p)->m_ui32Flags & 0x1000000u) != 0) {
            MovableOf(p->m_pNode)->RotateInPlace(&kAxisZ.x, dt * DataOf(p)->m_unk3c);
        }
    } else if ((flags & 0x100u) != 0) {
        // Rolling: placed, turned about the axis across the flight (X when nearly vertical) by the distance over the
        // rolling radius (data +0x40).
        SetFramePosition(FrameOf(p->m_pNode), p->m_vPos);
        float dx = p->m_vDir.x;
        float dy = p->m_vDir.y;
        float dz = p->m_vDir.z;
        const float length = MathSqrtf(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));
        if (length != kZero) {
            const float inv = kOne / length;
            dz = dz * inv;
            dx = dx * inv;
            dy = dy * inv;
        }
        const bool vertical = (dy < kZero) ? (dy < -kVertical) : (dy > kVertical);
        CVector3 axis;
        if (vertical) {
            axis = kAxisX;
        } else {
            axis.y = ppc::fmsubs(dx, kAxisY.z, dz * kAxisY.x);
            axis.z = ppc::fmsubs(dy, kAxisY.x, dx * kAxisY.y);
            axis.x = ppc::fmsubs(dz, kAxisY.y, dy * kAxisY.z);
        }
        MovableOf(p->m_pNode)->RotateInPlace(&axis.x, (dt * (p->m_fSpeed / DataOf(p)->m_unk40)) * kRadToDeg);
    } else {
        // Turned along the flight: the identity at the position, pitched (X) then yawed (Y) to the direction, spun by
        // the age about its own right / up / at rows, scaled.
        MovableOf(p->m_pNode)->SetIdentity();  // 0x000d08f0
        SetFramePosition(FrameOf(p->m_pNode), p->m_vPos);
        float dx = p->m_vDir.x;
        float dz = p->m_vDir.z;
        const float flat = MathSqrtf(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, kZero)));
        if (flat != kZero) {
            const float inv = kOne / flat;
            dz = dz * inv;
            dx = dx * inv;
        }
        const bool outside = (dz < kZero) ? (dz < kMinusOne) : (dz > kOne);
        float yaw;
        if (outside && dz < kZero) {
            yaw = crt::Acosf(kMinusOne);  // 0x00780c90
        } else {
            if (outside) {
                dz = kAxisZ.z;
                dx = kAxisZ.x;
            }
            float c = dz;
            if (c <= kMinusOne) c = kMinusOne;
            if (c >= kOne) c = kOne;
            yaw = crt::Acosf(c);
            if (dx < kZero) yaw = kTwoPi - yaw;
        }
        float s = p->m_vDir.y;
        if (s <= kMinusOne) s = kMinusOne;
        if (s >= kOne) s = kOne;
        const float pitch = crt::Asinf(s);  // 0x00780d70
        MovableOf(p->m_pNode)->RotateInPlace(&kAxisX.x, (kTwoPi - pitch) * kRadToDeg);
        MovableOf(p->m_pNode)->RotateInPlace(&kAxisY.x, yaw * kRadToDeg);
        RwMatrix& m = FrameOf(p->m_pNode)->modelling;
        if ((DataOf(p)->m_ui32Flags & 0x400000u) != 0) {
            MovableOf(p->m_pNode)->RotateInPlace(&m.right.x, DataOf(p)->m_unk3c * p->m_fAge);
        }
        if ((DataOf(p)->m_ui32Flags & 0x40000u) != 0) {
            MovableOf(p->m_pNode)->RotateInPlace(&FrameOf(p->m_pNode)->modelling.up.x, DataOf(p)->m_unk3c * p->m_fAge);
        }
        if ((DataOf(p)->m_ui32Flags & 0x1000000u) != 0) {
            MovableOf(p->m_pNode)->RotateInPlace(&FrameOf(p->m_pNode)->modelling.at.x, DataOf(p)->m_unk3c * p->m_fAge);
        }
        ScaleAxes(p->m_pNode, p->m_fScale);
    }
    // The fire ball turned with the flight.
    if ((DataOf(p)->m_ui32Flags & 0x1000u) != 0 && p->m_pFireBall != nullptr) {
        // 0x001ba5e0 CKFireBallNodeFx_SetDirection (the direction +0x24, the pool; C2.8 port-rest R06).
        static_cast<CKFireBallNodeFx*>(p->m_pFireBall)->SetDirection(&p->m_vDir, this);
    }
    // The growth: the scale from 1 to data +0x6c over the lifetime; the volume's radius follows.
    const float grow = DataOf(p)->m_unk6c;
    if (grow != kOne) {
        const float t = p->m_fAge / p->m_fLifetime;
        const float before = p->m_fScale;
        const float scale = ppc::fmadds(grow, t, kOne - t);
        p->m_fScale = scale;
        ScaleAxes(p->m_pNode, scale / before);
        if (p->m_pVolume != nullptr) {
            const float radius = DataOf(p)->m_unk40 * p->m_fScale;
            if (radius <= kZero) {
                VolumeOf(p)->m_fRadius = WordF32(kMinRadiusBits);  // TOC2 -0x71d0
            } else {
                VolumeOf(p)->m_fRadius = radius;
            }
        }
    }
    // The fade over the last data +0x70 seconds.
    const float fade = DataOf(p)->m_unk70;
    if (fade > kZero && p->m_fLifetime - fade < p->m_fAge) {
        const uint8_t alpha = static_cast<uint8_t>(ppc::fctiwz(((p->m_fLifetime - p->m_fAge) / fade) * kAlphaScale));
        SetGeometriesAlpha(p->m_pNode, alpha);
    }
    // The camera quake (data flag 0x20000000): once the camera comes within the settings' zero-strength distance (data
    // +0x18 +0x20, cror lt|eq), the projectile's launcher takes the settings and starts; after that it follows.
    if ((DataOf(p)->m_ui32Flags & 0x20000000u) == 0) return;
    if (p->m_bQuakeTriggered != 0) {
        p->m_pQuake->SetSourcePosition(&p->m_vPos);  // 0x001532c8
        return;
    }
    CKQuakeCameraLauncher* settings = static_cast<CKQuakeCameraLauncher*>(DataOf(p)->m_unk18);
    const float reach = settings->m_unk20;
    const CVector3& camera = Camera()->m_v3RealPos;
    const float cy = camera.y - p->m_vPos.y;
    const float cx = camera.x - p->m_vPos.x;
    const float cz = camera.z - p->m_vPos.z;
    if (!(ppc::fmadds(cz, cz, ppc::fmadds(cx, cx, cy * cy)) <= reach * reach)) return;
    p->m_pQuake->Vf54(settings->m_pQuake);  // CameraShakeData_CallVf54_maybe 0x00153288
    p->m_pQuake->m_unk20 = static_cast<CKQuakeCameraLauncher*>(DataOf(p)->m_unk18)->m_unk20;
    p->m_pQuake->m_unk1c = static_cast<CKQuakeCameraLauncher*>(DataOf(p)->m_unk18)->m_unk1c;
    p->m_pQuake->m_unk24 = static_cast<CKQuakeCameraLauncher*>(DataOf(p)->m_unk18)->m_unk24;
    p->m_pQuake->SetSourcePosition(&p->m_vPos);  // 0x001532c8
    p->m_pQuake->Trigger();                      // 0x001533c0
    p->m_bQuakeTriggered = 1;
}

// 0x00587d00 CKProjectileTypeBallisticPFX_ProcessDamageContacts: the volume's collisions this frame that have a
// contact set. Without data flag 0x4000: a hit on a volume of owner type 1 / 2 / 3 kills it with data flag 0x8000 /
// 0x20000 / 0x10000; with data flag 0x2 it bounces instead (the velocity against the contact normal, cut to data +0x20,
// the position put the radius off the contact point). Each such hit can leave an emission point.
void CKProjectileTypeBallisticPFX::ProcessDamageContacts(uint8_t index) {
    Projectile* p = ProjectileAt(this, index);
    if (p->m_pVolume == nullptr) return;
    for (ICollision* c = static_cast<ICollision*>(VolumeOf(p)->m_CollisionResList); c != nullptr; c = c->m_pNext) {
        if (c->HasContactSet() == 0) continue;  // vt+0x08
        const uint32_t flags = DataOf(p)->m_ui32Flags;
        if ((flags & 0x4000u) == 0) {
            if ((flags & 2u) == 0) {
                c->GetBoundingVolume1();  // vt+0x00 (the result unused)
                const uint8_t type = static_cast<IKBoundingVolume*>(c->GetBoundingVolume2())->m_ui8OwnerType;
                uint32_t dies = 0;
                if (type == 1) {
                    dies = DataOf(p)->m_ui32Flags & 0x8000u;
                } else if (type == 2) {
                    dies = DataOf(p)->m_ui32Flags & 0x20000u;
                } else if (type == 3) {
                    dies = DataOf(p)->m_ui32Flags & 0x10000u;
                }
                if (dies != 0) p->m_flags64 = static_cast<uint8_t>(p->m_flags64 & 0xfeu);
            } else {
                c->GetBoundingVolume1();
                const uint8_t type = static_cast<IKBoundingVolume*>(c->GetBoundingVolume2())->m_ui8OwnerType;
                uint32_t bounces = 0;
                if (type == 1) {
                    bounces = (DataOf(p)->m_ui32Flags >> 15) & 1u;
                } else if (type == 2) {
                    bounces = (DataOf(p)->m_ui32Flags >> 17) & 1u;
                } else if (type == 3) {
                    bounces = (DataOf(p)->m_ui32Flags >> 16) & 1u;  // lhz +0x50: the upper half
                }
                const float vy = ppc::fmadds(p->m_fSpeed, p->m_vDir.y, kNullVector.y);
                const float vx = ppc::fmadds(p->m_fSpeed, p->m_vDir.x, kNullVector.x);
                const float vz = ppc::fmadds(p->m_fSpeed, p->m_vDir.z, kNullVector.z);
                const CVector3 n = *c->GetNormale12();  // vt+0x1c
                const float dot = ppc::fmadds(vz, n.z, ppc::fmadds(vx, n.x, vy * n.y));
                if (dot > kZero && (bounces & 0xffu) != 0) {
                    const float nx = -n.x;
                    const float ny = -n.y;
                    const float nz = -n.z;
                    const CVector3 point = *c->GetWorldContactPoint();  // vt+0x20
                    const float twice = dot + dot;
                    const float radius = DataOf(p)->m_unk40;
                    const float pz = ppc::fmadds(nz, radius, point.z);
                    const float ry = ppc::fmadds(ny, twice, vy);
                    const float rx = ppc::fmadds(nx, twice, vx);
                    const float py = ppc::fmadds(ny, radius, point.y);
                    const float px = ppc::fmadds(nx, radius, point.x);
                    const float rz = ppc::fmadds(nz, twice, vz);
                    p->m_vPos.z = pz;
                    p->m_vPos.y = py;
                    p->m_vPos.x = px;
                    const float lengthSq = ppc::fmadds(rz, rz, ppc::fmadds(rx, rx, ry * ry));
                    CKDynamicBoundingSphere* volume = VolumeOf(p);
                    volume->m_v3WorldMove = kNullVector;
                    volume->m_v3OldPos = {px, py, pz};
                    volume->m_v3LastWorldPos = {px, py, pz};
                    p->m_vDir = {rx, ry, rz};
                    float length = MathSqrtf(lengthSq);
                    if (length == kZero) {
                        length = kZero;
                    } else {
                        const float inv = kOne / length;
                        p->m_vDir.z = inv * p->m_vDir.z;
                        p->m_vDir.x = inv * p->m_vDir.x;
                        p->m_vDir.y = inv * p->m_vDir.y;
                    }
                    p->m_fSpeed = length;
                    p->m_fSpeed = length * DataOf(p)->m_unk20;
                }
            }
        }
        MaybeAddEmissionPoint(this, ProjectileAt(this, index));
    }
}

// 0x00588278 CKProjectileTypeBallisticPFX_UpdateMotion. Unless landed (bit 2): the speed less its drag (data +0x24),
// gravity (data +0x1c) on the velocity, the steering (data flags 0x4000000 / 0x8000000 / 0x10000000), the position
// moved, the direction and speed from the velocity; the trail's anchors (pool option 0x80); the sound once the camera
// is within data +0x48 (option 0x200000, bge: a NaN stays silent). The age advances in every case.
void CKProjectileTypeBallisticPFX::UpdateMotion(uint8_t index, float dt) {
    Projectile* p = ProjectileAt(this, index);
    if ((p->m_flags64 & 4u) == 0) {
        CKProjectileDataTypeBallisticPFX* data = DataOf(p);
        const float speed = p->m_fSpeed - dt * (p->m_fSpeed * data->m_unk24);
        p->m_fSpeed = speed;
        float vx = speed * p->m_vDir.x;
        float vz = speed * p->m_vDir.z;
        float vy = ppc::fmsubs(speed, p->m_vDir.y, dt * data->m_unk1c);
        const uint32_t flags = data->m_ui32Flags;
        if ((flags & 0x4000000u) != 0 || (flags & 0x8000000u) != 0 || (flags & 0x10000000u) != 0) {
            const CVector3 steer = ComputeSteering(dt, p, &p->m_vPos);
            vy = ppc::fmadds(dt, steer.y, vy);
            vx = ppc::fmadds(dt, steer.x, vx);
            vz = ppc::fmadds(dt, steer.z, vz);
        }
        const float lengthSq = ppc::fmadds(vz, vz, ppc::fmadds(vx, vx, vy * vy));
        p->m_vPrevPos = p->m_vPos;
        p->m_vPos.y = ppc::fmadds(dt, vy, p->m_vPos.y);
        p->m_vPos.z = ppc::fmadds(dt, vz, p->m_vPos.z);
        p->m_vPos.x = ppc::fmadds(dt, vx, p->m_vPos.x);
        float length = MathSqrtf(lengthSq);
        if (length == kZero) {
            length = kZero;
        } else {
            const float inv = kOne / length;
            vz = vz * inv;
            vx = vx * inv;
            vy = vy * inv;
        }
        p->m_fSpeed = length;
        p->m_vDir = {vx, vy, vz};
        if ((m_baOptions & 0x80u) != 0) UpdateInstanceTrailSegment(index);  // inlined in the original
        if ((m_baOptions & 0x200000u) != 0 && ((p->m_flags64 >> 3) & 1u) == 0) {
            const float reach = DataOf(p)->m_unk48;
            const CVector3& camera = Camera()->m_v3RealPos;
            const float cy = camera.y - p->m_vPos.y;
            const float cx = camera.x - p->m_vPos.x;
            const float cz = camera.z - p->m_vPos.z;
            if (ppc::fmadds(cz, cz, ppc::fmadds(cx, cx, cy * cy)) < reach * reach) {
                PlayInstanceSound(index);  // inlined in the original
            }
        }
    }
    p->m_fAge = p->m_fAge + dt;
}

// 0x005886d0 CKProjectileTypeBallisticPFX_KillInstance: not alive, hidden; (option 0x80) its ribbon off; (option
// 0x200000) its sound stopped and detached; 0x2802 to its owner with its position; its volume taken off the node and
// released; the last active projectile takes its place.
void CKProjectileTypeBallisticPFX::KillProjectile(uint8_t index) {
    Projectile* p = ProjectileAt(this, index);
    p->m_flags64 = 0;
    p->m_pNode->m_sgProperties = (p->m_pNode->m_sgProperties & 0xfffffffbu) | 4u;
    if ((m_baOptions & 0x80u) != 0) TrailOf(this)->SetRibbonActive(p->m_ui8Index, 0, 1);  // inlined 0x009bdfb8
    if ((m_baOptions & 0x200000u) != 0) {
        CKSound* sound = static_cast<CKSoundDictionaryID*>(m_unk30)->GetSound(p->m_ui8Index);  // 0x00112bc0
        if (sound != nullptr) {
            Sound_Stop(sound, 0);             // 0x001111b0
            sound->SetAttachObject(nullptr);  // 0x00111350
        }
    }
    if (p->m_pOwner != nullptr) p->m_pOwner->MessageProc(0x2802, &p->m_vPos);  // vt+0x1c
    if (p->m_pVolume != nullptr) {
        CKDynamicBoundingSphere* volume = VolumeOf(p);
        if (volume->m_pParent != nullptr) volume->m_pParent->RemoveChild(volume);  // vt+0x78
        Collision()->ReleaseDynSphere(VolumeOf(p));                               // 0x00191a38
        p->m_pVolume = nullptr;
    }
    const uint8_t last = static_cast<uint8_t>(m_ui8NbOfActiveProjectiles - 1);
    if (index == last) {
        m_ui8NbOfActiveProjectiles = last;
        return;
    }
    m_ui8NbOfActiveProjectiles = last;
    Projectile** list = reinterpret_cast<Projectile**>(m_apProjectileList);
    list[index] = list[last];
    list[m_ui8NbOfActiveProjectiles] = p;
}

// 0x00588d08 CKProjectileTypeBallisticPFX_SpawnAtPoint_maybe. The orientation is updated (vt+0x64, dt 0) before the
// direction is set, from the record's previous direction (as the original). The arc: the horizontal direction to the
// target at `speed`, the vertical speed that meets it under gravity (data +0x1c), normalised; the speed its length
// (at most 999). A target straight above / below goes straight up / down at `speed`.
void CKProjectileTypeBallisticPFX::SpawnAtPoint(IKSerializable* data, uint8_t index, const CVector3* pos,
                                                const CVector3* target, float speed, IKSerializable* owner) {
    Projectile* p = ProjectileAt(this, index);
    p->m_pData = data;
    p->m_pOwner = owner;
    p->m_flags64 = 1;
    p->m_fAge = 0.0f;
    const float base = DataOf(p)->m_unk28;
    {
        const uint32_t r = static_cast<uint32_t>(Rand_Int()) & 0xffffu;  // 0x00011500 through 0x0098fd10
        const float t = ppc::fmadds(static_cast<float>(r), kRandToUnit, kOne);
        p->m_fLifetime = ppc::fmadds(t, DataOf(p)->m_unk54, base);
    }
    p->m_GrdContDatasInOut.m_i32FaceIndex = -1;
    p->m_GrdContDatasInOut.m_eContactStatus = 3;
    p->m_GrdContDatasInOut.m_ui8SectorNumber = 0;
    p->m_GrdContDatasInOut.m_pGround = nullptr;
    p->m_vPos = *pos;
    p->m_vPrevPos = *pos;
    MovableOf(p->m_pNode)->SetIdentity();  // 0x000d08f0
    p->m_pNode->m_sgProperties &= 0xfffffffbu;
    SetFramePosition(FrameOf(p->m_pNode), *pos);
    p->m_pFireBall = nullptr;
    {
        const float low = DataOf(p)->m_unk64;
        const float high = DataOf(p)->m_unk68;
        const uint32_t r = static_cast<uint32_t>(Rand_Int()) & 0xffffu;
        p->m_fScale = ppc::fmadds(high - low, static_cast<float>(r) / kRandMax, low);
    }
    ScaleAxes(p->m_pNode, p->m_fScale);
    p->m_bQuakeTriggered = 0;
    if ((m_baOptions & 0x80u) != 0) RestartTrail(this, index);
    if ((DataOf(p)->m_ui32Flags & 0x1000u) != 0) StartFireBall(this, p, &kAxisY);
    if ((DataOf(p)->m_ui32Flags & 0x40u) != 0) StartParticleFx(this, p);
    if ((DataOf(p)->m_ui32Flags & 0x100u) != 0) RandomRotation(p->m_pNode);
    StartSound(this, index, p);
    if (DataOf(p)->m_unk70 > kZero) SetGeometriesAlpha(p->m_pNode, 0xff);
    UpdateOrientation(index, 0.0f);  // vt+0x64
    SetupVolume(p, owner, pos, DataOf(p)->m_unk40, false, nullptr);
    // The arc.
    p->m_vDir.y = kZero;
    p->m_vDir.x = target->x - pos->x;
    const float dy = target->y - pos->y;
    p->m_vDir.z = target->z - pos->z;
    const float flat =
        MathSqrtf(ppc::fmadds(p->m_vDir.z, p->m_vDir.z, ppc::fmadds(p->m_vDir.x, p->m_vDir.x, p->m_vDir.y * p->m_vDir.y)));
    if (flat == kZero) {
        p->m_vDir = {kZero, dy < kZero ? kMinusOne : kOne, kZero};
        p->m_fSpeed = speed;
    } else {
        const float inv = kOne / flat;
        p->m_vDir.z = inv * p->m_vDir.z;
        p->m_vDir.x = inv * p->m_vDir.x;
        p->m_vDir.y = inv * p->m_vDir.y;
        float vy = (dy * speed) / flat;
        p->m_vDir.x = speed * p->m_vDir.x;
        p->m_vDir.z = speed * p->m_vDir.z;
        vy = vy + (flat * (DataOf(p)->m_unk1c * kHalf)) / speed;
        p->m_vDir.y = vy;
        const float length = MathSqrtf(
            ppc::fmadds(p->m_vDir.z, p->m_vDir.z, ppc::fmadds(p->m_vDir.x, p->m_vDir.x, p->m_vDir.y * p->m_vDir.y)));
        if (length == kZero) {
            p->m_fSpeed = kZero;
        } else {
            const float k = kOne / length;
            p->m_vDir.z = k * p->m_vDir.z;
            p->m_vDir.x = k * p->m_vDir.x;
            p->m_vDir.y = k * p->m_vDir.y;
            p->m_fSpeed = (length > kMaxSpeed) ? kMaxSpeed : length;
        }
    }
    LaunchExplosion(this, p);
}

// 0x0058a0f8 CKProjectileTypeBallisticPFX_LaunchAtPointEx: SpawnAtPoint, then the volume's damage (+0x1c).
uint8_t CKProjectileTypeBallisticPFX::LaunchAtPointEx(IKSerializable* data, const CVector3* pos,
                                                      const CVector3* target, float speed, IKSerializable* damage,
                                                      IKSerializable* owner) {
    const uint8_t index = m_ui8NbOfActiveProjectiles;
    if (!(m_ui8MaxProjectiles > index)) return 0;
    SpawnAtPoint(data, index, pos, target, speed, owner);
    Projectile* p = ProjectileAt(this, index);
    if (p->m_pVolume != nullptr) static_cast<IKBoundingVolume*>(p->m_pVolume)->m_unk1c = damage;
    m_ui8NbOfActiveProjectiles = static_cast<uint8_t>(m_ui8NbOfActiveProjectiles + 1);
    return 1;
}

// 0x0058a1c8 CKProjectileTypeBallisticPFX_LaunchAtPoint
uint8_t CKProjectileTypeBallisticPFX::LaunchAtPoint(IKSerializable* data, const CVector3* pos, const CVector3* target,
                                                    float speed, IKSerializable* owner) {
    const uint8_t index = m_ui8NbOfActiveProjectiles;
    if (!(m_ui8MaxProjectiles > index)) return 0;
    SpawnAtPoint(data, index, pos, target, speed, owner);
    m_ui8NbOfActiveProjectiles = static_cast<uint8_t>(m_ui8NbOfActiveProjectiles + 1);
    return 1;
}

// 0x0058a238 CKProjectileTypeBallisticPFX_OnDeath: the fire ball (data flag 0x1000) and the particle effect (0x40)
// stopped and released; (data flag 0x400) the death explosion (data +0x04) for the volume's owner (else the pool) with
// the volume's damage; (data flag 0x800) the death shock wave (data +0x08) for the pool; then KillProjectile (vt+0x60).
void CKProjectileTypeBallisticPFX::OnDeath(uint8_t index) {
    Projectile* p = ProjectileAt(this, index);
    if ((DataOf(p)->m_ui32Flags & 0x1000u) != 0 && p->m_pFireBall != nullptr) {
        // 0x001ba530 CKFireBallNodeFx_RequestStopForOwner_maybe (the pool; C2.8 port-rest R06); then released.
        static_cast<CKFireBallNodeFx*>(p->m_pFireBall)->RequestStopForOwner(this);
        static_cast<IKFx*>(p->m_pFireBall)->ReleaseReservation(this);  // vt+0x54
        p->m_pFireBall = nullptr;
    }
    if ((DataOf(p)->m_ui32Flags & 0x40u) != 0 && p->m_pParticleFx != nullptr) {
        StopOwnedParticleEffect(static_cast<IKFx*>(p->m_pParticleFx), this);  // 0x001cdde8
        static_cast<IKFx*>(p->m_pParticleFx)->ReleaseReservation(this);        // vt+0x54
        p->m_pParticleFx = nullptr;
    }
    if ((DataOf(p)->m_ui32Flags & 0x400u) != 0) {
        IKSerializable* owner = this;
        if (p->m_pVolume != nullptr && static_cast<IKBoundingVolume*>(p->m_pVolume)->m_pOwner != nullptr) {
            owner = static_cast<IKBoundingVolume*>(p->m_pVolume)->m_pOwner;
        }
        IKFx* fx = FxService()->AcquireFx(static_cast<IKFxData*>(DataOf(p)->m_unk04), owner);
        if (fx != nullptr) {
            CKExplosionNodeFx* explosion = static_cast<CKExplosionNodeFx*>(fx);
            if (p->m_pVolume != nullptr) {
                explosion->SetDamageOwner(owner, owner);                                          // 0x001b6340
                explosion->SetDamageCategory(DataOf(p)->m_unk4c, owner);                          // 0x001b6318
                explosion->SetDamageFlags(DataOf(p)->m_unk4e, owner);                             // 0x001b62f0
                explosion->SetDamage(static_cast<IKBoundingVolume*>(p->m_pVolume)->m_unk1c, owner);  // 0x001b62c8
            }
            explosion->SetTranslation(&p->m_vPos, owner);  // 0x001b66e8
            explosion->Trigger(owner, 0);                  // 0x001b82a8
            explosion->ReleaseReservation(owner);          // vt+0x54
        }
    }
    if ((DataOf(p)->m_ui32Flags & 0x800u) != 0) TriggerShockWave(this, p, &p->m_vPos, false);
    KillProjectile(index);  // vt+0x60
}

// 0x0058a948 CKProjectileTypeBallisticPFX_CollideModeC_maybe (data flag 0x4): lands. Unless landed: on a ground (status
// 1) put on its projection, stopped, landed, the impact shock wave (data flag 0x2000) at the contact's world point;
// against a wall (status 2 / 3) stopped and either dying (data flag 0x800000) or landing where the motion meets the
// wall, the shock wave at its position. Each can leave an emission point first.
void CKProjectileTypeBallisticPFX::CollideModeC(uint8_t index) {
    ProbeGround(this, index, false);
    Projectile* p = ProjectileAt(this, index);
    if ((p->m_flags64 & 4u) == 0) {
        const int32_t status = static_cast<int32_t>(p->m_GrdContDatasInOut.m_eContactStatus);
        if (status == 1) {
            p->m_vPos = p->m_GrdContDatasInOut.m_ProjectionOnGround;
            p->m_fSpeed = kZero;
            Land(p);
            MaybeAddEmissionPoint(this, ProjectileAt(this, index));
            if ((DataOf(p)->m_ui32Flags & 0x2000u) != 0) {
                CVector3 point;
                GroundContact_GetWorldPoint(reinterpret_cast<const ::CGroundContactDatasInOut*>(&p->m_GrdContDatasInOut),
                                            &point);  // 0x001a70e0
                TriggerShockWave(this, p, &point, false);
            }
        } else if (status >= 1 && status <= 3) {
            p->m_fSpeed = kZero;
            if ((DataOf(p)->m_ui32Flags & 0x800000u) != 0) {
                p->m_flags64 = static_cast<uint8_t>(p->m_flags64 & 0xfeu);
            } else {
                CLine line;
                CGroundEdgeDatasOut out;
                if (RaycastMotion(ProjectileAt(this, index), &line, &out) != 0) {
                    const float t = out.m_ftLine;
                    p->m_vPos.z = ppc::fmadds(t, line.m_VectDir.z, p->m_vPrevPos.z);
                    p->m_vPos.x = ppc::fmadds(t, line.m_VectDir.x, p->m_vPrevPos.x);
                    p->m_vPos.y = ppc::fmadds(t, line.m_VectDir.y, p->m_vPrevPos.y);
                }
                Land(p);
            }
            MaybeAddEmissionPoint(this, ProjectileAt(this, index));
            if ((DataOf(p)->m_ui32Flags & 0x2000u) != 0) TriggerShockWave(this, p, &p->m_vPos, false);
        }
    }
    ResetGroundParams(this, index);
}

// 0x0058b498 CKProjectileTypeBallisticPFX_CollideModeB_maybe (data flag 0x2): bounces. On a ground (status 1) pushed out
// along the normal by the depth times 1 + the restitution (data +0x20), the direction reflected the same way, the speed
// cut by the impact, 0x2800 to the volume's owner, an emission point, the shock wave at the contact's world point.
// Against a wall (status 2 / 3, where the motion meets it) the same about the wall's horizontal normal, an emission
// point, the shock wave at its position, then 0x2800.
void CKProjectileTypeBallisticPFX::CollideModeB(uint8_t index) {
    ProbeGround(this, index, false);
    Projectile* p = ProjectileAt(this, index);
    const int32_t status = static_cast<int32_t>(p->m_GrdContDatasInOut.m_eContactStatus);
    if (status == 1) {
        const CVector3 n = p->m_GrdContDatasInOut.m_Normal;
        const float depth = ppc::fmadds(n.z, kZero, ppc::fmadds(n.x, kZero, n.y * p->m_GrdContDatasInOut.m_fdH));
        const float k = DataOf(p)->m_unk20 + kOne;
        p->m_vPos.y = ppc::fmadds(k, n.y * depth, p->m_vPos.y);
        p->m_vPos.x = ppc::fmadds(n.x * depth, k, p->m_vPos.x);
        p->m_vPos.z = ppc::fmadds(k, n.z * depth, p->m_vPos.z);
        const CVector3 v = p->m_vDir;
        const float dot = ppc::fmadds(n.z, v.z, ppc::fmadds(n.x, v.x, n.y * v.y));
        const float k2 = DataOf(p)->m_unk20 + kOne;
        p->m_vDir.x = v.x - (n.x * dot) * k2;
        p->m_vDir.y = v.y - k2 * (n.y * dot);
        p->m_vDir.z = v.z - k2 * (n.z * dot);
        const float impact = std::fabs(dot);
        p->m_fSpeed = p->m_fSpeed - (p->m_fSpeed * impact) * (kOne - DataOf(p)->m_unk20);
        NotifyBounce(p);
        MaybeAddEmissionPoint(this, ProjectileAt(this, index));
        if ((DataOf(p)->m_ui32Flags & 0x2000u) != 0) {
            CVector3 point;
            GroundContact_GetWorldPoint(reinterpret_cast<const ::CGroundContactDatasInOut*>(&p->m_GrdContDatasInOut),
                                        &point);  // 0x001a70e0
            TriggerShockWave(this, p, &point, true);
        }
    } else if (status >= 1 && status <= 3) {
        CLine line;
        CGroundEdgeDatasOut out;
        if (RaycastMotion(ProjectileAt(this, index), &line, &out) != 0) {
            float ex = out.m_Edge.m_VectDir.x;
            float ez = out.m_Edge.m_VectDir.z;
            const float t = out.m_ftLine;
            const float flat = MathSqrtf(ppc::fmadds(ez, ez, ppc::fmadds(ex, ex, kZero)));
            if (flat != kZero) {
                const float inv = kOne / flat;
                ez = ez * inv;
                ex = ex * inv;
            }
            // The wall's normal (ez, 0, -ex).
            const float nx = ez;
            const float nz = -ex;
            const float hx = ppc::fmadds(t, line.m_VectDir.x, p->m_vPrevPos.x);
            const float hz = ppc::fmadds(t, line.m_VectDir.z, p->m_vPrevPos.z);
            const float zeroTerm = ppc::fmadds(t, kZero, kZero) * kZero;
            p->m_vPos.y = p->m_vPos.y + kZero;
            const float k = DataOf(p)->m_unk20 + kOne;
            const float depth = ppc::fmadds(nz, hz - p->m_vPos.z, ppc::fmadds(nx, hx - p->m_vPos.x, zeroTerm));
            p->m_vPos.x = ppc::fmadds(nx * depth, k, p->m_vPos.x);
            p->m_vPos.z = ppc::fmadds(k, nz * depth, p->m_vPos.z);
            const CVector3 v = p->m_vDir;
            const float dot = ppc::fmadds(nz, v.z, ppc::fmadds(nx, v.x, v.y * kZero));
            const float k2 = DataOf(p)->m_unk20 + kOne;
            p->m_vDir.x = v.x - (nx * dot) * k2;
            p->m_vDir.z = v.z - k2 * (nz * dot);
            p->m_vDir.y = v.y - k2 * (dot * kZero);
            const float impact = std::fabs(dot);
            p->m_fSpeed = p->m_fSpeed - (p->m_fSpeed * impact) * (kOne - DataOf(p)->m_unk20);
            if ((m_baOptions & 0x20u) != 0 && DataOf(p)->m_unk34 < p->m_fSpeed) {
                AddEmissionPoint(this, ProjectileAt(this, index));
            }
            if ((DataOf(p)->m_ui32Flags & 0x2000u) != 0) TriggerShockWave(this, p, &p->m_vPos, false);
            NotifyBounce(p);
        }
    }
    ResetGroundParams(this, index);
}

// 0x0058c148 CKProjectileTypeBallisticPFX_CollideSweepA (neither 0x2 nor 0x4): dies on contact. A ground or wall under
// it (status 1 / 2) puts it back where it was this frame, dying; an emission point, the shock wave at the contact's
// world point. Status 3 dies at its previous position only where the motion meets a wall (an emission point, no shock
// wave). The test parameters are left as the fall set them.
void CKProjectileTypeBallisticPFX::CollideSweepA(uint8_t index) {
    ProbeGround(this, index, true);
    Projectile* p = ProjectileAt(this, index);
    const int32_t status = static_cast<int32_t>(p->m_GrdContDatasInOut.m_eContactStatus);
    if (status < 1) return;
    if (status <= 2) {
        p->m_flags64 = static_cast<uint8_t>(p->m_flags64 & 0xfeu);
        p->m_vPos = p->m_vPrevPos;
        MaybeAddEmissionPoint(this, ProjectileAt(this, index));
        if ((DataOf(p)->m_ui32Flags & 0x2000u) != 0) {
            CVector3 point;
            GroundContact_GetWorldPoint(reinterpret_cast<const ::CGroundContactDatasInOut*>(&p->m_GrdContDatasInOut),
                                        &point);  // 0x001a70e0
            TriggerShockWave(this, p, &point, false);
        }
        return;
    }
    if (status != 3) return;
    CLine line;
    CGroundEdgeDatasOut out;
    if (RaycastMotion(ProjectileAt(this, index), &line, &out) == 0) return;
    p->m_flags64 = static_cast<uint8_t>(p->m_flags64 & 0xfeu);
    p->m_vPos = p->m_vPrevPos;
    MaybeAddEmissionPoint(this, ProjectileAt(this, index));
}

// 0x0058c878 CKProjectileTypeBallisticPFX_UpdateCollision: with data +0x45 the ground test masks (1, 8), or (1, 0) with
// data flag 0x200, then mode B (data flag 0x2), C (0x4) or the sweep.
void CKProjectileTypeBallisticPFX::UpdateCollision(uint8_t index, float /*dt*/) {
    const Projectile* p = ProjectileAt(this, index);
    if (DataOf(p)->m_unk45 == 0) return;
    m_GrdContDatasIn.m_MasksOfGrdForTest[0] = 1;
    m_GrdContDatasIn.m_MasksOfGrdForTest[1] = (DataOf(p)->m_ui32Flags & 0x200u) == 0 ? 8u : 0u;
    const uint32_t flags = DataOf(p)->m_ui32Flags;
    if ((flags & 2u) != 0) {
        CollideModeB(index);
    } else if ((flags & 4u) != 0) {
        CollideModeC(index);
    } else {
        CollideSweepA(index);
    }
}

// 0x0058c948 CKProjectileTypeBallisticPFX_SpawnInstance. `damage` (a stack argument): the volume's +0x1c (Launch and
// LaunchEx pass 0).
void CKProjectileTypeBallisticPFX::SpawnInstance(IKSerializable* data, uint8_t index, const CVector3* pos,
                                                 const CVector3* dir, float speed, IKSerializable* owner,
                                                 const RwMatrix* matrix, IKSerializable* damage) {
    Projectile* p = ProjectileAt(this, index);
    p->m_pData = data;
    p->m_pOwner = owner;
    p->m_flags64 = 1;
    p->m_fSpeed = speed;
    p->m_fAge = 0.0f;
    const float base = DataOf(p)->m_unk28;
    {
        const uint32_t r = static_cast<uint32_t>(Rand_Int()) & 0xffffu;  // 0x00011500 through 0x0098fd10
        const float t = ppc::fmadds(static_cast<float>(r), kRandToUnit, kOne);
        p->m_fLifetime = ppc::fmadds(t, DataOf(p)->m_unk54, base);
    }
    p->m_GrdContDatasInOut.m_i32FaceIndex = -1;
    p->m_GrdContDatasInOut.m_eContactStatus = 3;
    p->m_GrdContDatasInOut.m_ui8SectorNumber = 0;
    p->m_GrdContDatasInOut.m_pGround = nullptr;
    p->m_vPos = *pos;
    p->m_vPrevPos = *pos;
    p->m_vDir = *dir;
    p->m_pFireBall = nullptr;
    {
        const float low = DataOf(p)->m_unk64;
        const float high = DataOf(p)->m_unk68;
        const uint32_t r = static_cast<uint32_t>(Rand_Int()) & 0xffffu;
        p->m_bQuakeTriggered = 0;
        p->m_fScale = ppc::fmadds(high - low, static_cast<float>(r) / kRandMax, low);
    }
    MovableOf(p->m_pNode)->SetIdentity();  // 0x000d08f0
    p->m_pNode->m_sgProperties &= 0xfffffffbu;
    if (matrix != nullptr) MovableOf(p->m_pNode)->SetLocalMatrix(matrix);  // 0x000d0be8
    SetFramePosition(FrameOf(p->m_pNode), *pos);
    if ((DataOf(p)->m_ui32Flags & 0x100u) != 0) RandomRotation(p->m_pNode);
    ScaleAxes(p->m_pNode, p->m_fScale);
    if ((DataOf(p)->m_ui32Flags & 0x1000u) != 0) StartFireBall(this, p, dir);
    if ((DataOf(p)->m_ui32Flags & 0x40u) != 0) StartParticleFx(this, p);
    if ((m_baOptions & 0x80u) != 0) RestartTrail(this, index);
    StartSound(this, index, p);
    if (DataOf(p)->m_unk70 > kZero) SetGeometriesAlpha(p->m_pNode, 0xff);
    UpdateOrientation(index, 0.0f);  // vt+0x64
    SetupVolume(p, owner, pos, DataOf(p)->m_unk40 * p->m_fScale, true, damage);
    LaunchExplosion(this, p);
}

// 0x0058e160 CKProjectileTypeBallisticPFX_LaunchEx: SpawnInstance without a damage object, then the volume's +0x1c.
uint8_t CKProjectileTypeBallisticPFX::LaunchEx(IKSerializable* data, const CVector3* pos, const CVector3* dir,
                                               float speed, IKSerializable* damage, IKSerializable* owner,
                                               const RwMatrix* matrix) {
    const uint8_t index = m_ui8NbOfActiveProjectiles;
    if (!(m_ui8MaxProjectiles > index)) return 0;
    SpawnInstance(data, index, pos, dir, speed, owner, matrix, nullptr);
    Projectile* p = ProjectileAt(this, index);
    if (p->m_pVolume != nullptr) static_cast<IKBoundingVolume*>(p->m_pVolume)->m_unk1c = damage;
    m_ui8NbOfActiveProjectiles = static_cast<uint8_t>(m_ui8NbOfActiveProjectiles + 1);
    return 1;
}

// 0x0058e240 CKProjectileTypeBallisticPFX_Launch
uint8_t CKProjectileTypeBallisticPFX::Launch(IKSerializable* data, const CVector3* pos, const CVector3* dir,
                                             float speed, IKSerializable* owner, const RwMatrix* matrix) {
    const uint8_t index = m_ui8NbOfActiveProjectiles;
    if (!(m_ui8MaxProjectiles > index)) return 0;
    SpawnInstance(data, index, pos, dir, speed, owner, matrix, nullptr);
    m_ui8NbOfActiveProjectiles = static_cast<uint8_t>(m_ui8NbOfActiveProjectiles + 1);
    return 1;
}
