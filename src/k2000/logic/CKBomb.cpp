// Reconstructed original translation unit: 0x58e9c0-0x591f58 (GAME_TOC2, main_toc2), 30 functions, 28 live.
// Primary class: CKBomb  key 0x2e0c  category Logic  size 0x64  vtable 0xb2e2c0
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x58e9c0  CKBomb_Delete  (DOTD_DECLARE_FACTORIES(CKBomb))
//   [x] 0x58ea10  CKBomb_OnDeath
//   [ ] 0x58ea50  RegisterCKBombClass
//   [ ] 0x58eac8  _GLOBAL__I_58eac8
//   [ ] 0x58ead8  CKBomb_UnregisterShadowCaster_maybe  [dead: no pointer to its descriptor 0xbe88e8, no call (raw ELF scan)]
//   [ ] 0x58eb38  CKBomb_RegisterShadowCaster_maybe  [dead: no pointer to its descriptor 0xbe88f0, no call (raw ELF scan)]
//   [x] 0x58ec10  CKBomb_UpdateAttachedTransform_maybe  (UpdateShadowGround)
//   [x] 0x58ee98  CKBomb_DeleteArray  (DOTD_DECLARE_FACTORIES)
//   [x] 0x58ef38  CKBomb_Create  (DOTD_DECLARE_FACTORIES: the header's constructor)
//   [ ] 0x58ef90  FUN_0058ef90  [dead]
//   [x] 0x58efb0  CKBomb_IsDead
//   [x] 0x58efd8  CKBomb_CreateArray  (DOTD_DECLARE_FACTORIES)
//   [x] 0x58f090  CKBomb_KillInstance  (CKBomb::KillProjectile)
//   [ ] 0x58f240  CKBomb_AddFxEmitPoint_maybe  [dead]
//   [x] 0x58f2d0  CKBomb_UpdateFuse_maybe  (UpdateFuse)
//   [x] 0x58f7c0  CKBomb_SpawnInstance
//   [x] 0x58fc18  CKBomb_LaunchEx
//   [x] 0x58fd18  CKBomb_Launch
//   [x] 0x58fdb8  CKBomb_UpdateMotion
//   [x] 0x590088  CKBomb_SpawnInstanceAtPoint
//   [x] 0x590820  CKBomb_LaunchAtPointEx
//   [x] 0x590928  CKBomb_LaunchAtPoint
//   [x] 0x5909d0  CKBomb_UpdateOrientation
//   [x] 0x590d30  CKBomb_UpdateCollision
//   [x] 0x5911d0  CKBomb_ProcessDamageContacts
//   [x] 0x5918f8  CKBomb_Destroy
//   [x] 0x591930  CKBomb_MessageProc
//   [ ] 0x591a00  CKBomb_Save
//   [x] 0x591a08  CKBomb_RecursiveRegistration
//   [x] 0x591ab0  CKBomb_Load
//
//   [x] 0x9cb478  CKBomb_IsKindOfClass  [inline]  (the header)
//   [x] 0x9cb4a0  CKBomb_GetClassType  [inline]  (DOTD_CLASS_KEY)
//   [x] 0x9cb4a8  CKBomb_GetClassID  [inline]  (DOTD_CLASS_KEY)
//   [x] 0x9cb4b0  CKBomb_DeletingDestructor  [inline]  (the destructor, then delete)
//   [x] 0x9cb4f8  CKBomb_Destructor  [inline]  (the destructor)
#include "k2000/logic/CKBomb.h"

#include <cstring>

#include "Renderware/rwcore/RwCamera.h"
#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/CKDynamicBoundingSphere.h"
#include "k2000/scenegraph/CSGBranch.h"
#include "k2000/scenegraph/CSGLeaf.h"
#include "k2000/scenegraph/IKBoundingVolume.h"
#include "k2000/services/CKSrvCollision.h"
#include "Renderware/rpprtstd/RpPrtStd.h"
#include "Spyro2008/groups/IKGrpHero.h"
#include "crt/ppc_ops.h"
#include "k2000/fx/IKFx.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/logic/IKFxData.h"
#include "k2000/logic/fx/CKExplosionNodeFx.h"
#include "k2000/misc/Mat4.h"
#include "k2000/scenegraph/CParticlesNodeFx.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/services/CKSrvFx.h"
#include "k2000/services/CollisionDatas.h"
#include "k2000/services/ICollisionMesh.h"

#include <cmath>

namespace {

const CVector3 kNullVector{0.0f, 0.0f, 0.0f};  // 0x00c50d64
const CVector3 kAxisZ{0.0f, 0.0f, 1.0f};       // 0x00c50d4c (the static initialisers' Z axis)
const CVector3 kAxisX{1.0f, 0.0f, 0.0f};       // 0x00c50d34 (TOC2 -0x7090)
const CVector3 kUpAxis{0.0f, 1.0f, 0.0f};      // 0x00c50d40 (TOC2 -0x70ec)

// TOC2 constants (compared by their bits).
constexpr float kZero = 0.0f;               // -0x70bc
constexpr float kOne = 1.0f;                // -0x70a0
constexpr float kMinSpeed = 0.1f;           // -0x70a4 (0x3dcccccd)
constexpr float kMinRadius = 0.001f;        // -0x70c0 (0x3a83126f)
constexpr float kQuarter3 = 0.75f;          // -0x70d8
constexpr float kHalf = 0.5f;               // -0x70d4
constexpr float kQuarter = 0.25f;           // -0x70d0
constexpr float kMaxThrowSpeed = 999.0f;    // -0x709c (0x4479c000)
constexpr float kVertical = 0.99f;          // -0x7094 (0x3f7d70a4; -0x7098 its negative)
constexpr float kRadToDeg = 57.2957802f;    // -0x708c (0x42652ee1)
constexpr float kUprightRate = 5.0f;        // -0x7088 (-0x7084 its negative)
constexpr float kHeroBounceMin = 2.0f;      // -0x7080
constexpr float kHeroBounceSpeed = 10.0f;   // -0x707c (0x41200000)

CKBomb::Bomb* BombAt(CKBomb* pool, uint8_t index) { return static_cast<CKBomb::Bomb*>(pool->m_apProjectileList[index]); }
CKSrvCollision* Collision() { return static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision); }
CKSrvFx* FxService() { return static_cast<CKSrvFx*>(g_pEngine->m_srvFx); }
CKDynamicBoundingSphere* VolumeOf(const CKBomb::Bomb* b) { return static_cast<CKDynamicBoundingSphere*>(b->m_pProjectileBS); }
CSGLeaf* NodeOf(const CKBomb::Bomb* b) { return static_cast<CSGLeaf*>(b->m_pProjectileNode); }

// 0x00010690 Math_Sqrtf (fsqrts; through TocBridge_Math_Sqrtf 0x0098fc10).
inline float MathSqrtf(float x) { return std::sqrt(x); }

// The particle point the bomb inlines (UpdateMotion's trail, UpdateFuse's spark): the position appended to the
// effect's points (at most 0x40) and its scene flag 0x2000 set.
void AddFxPoint(IKSerializable* fx, const CVector3& pos) {
    CParticlesNodeFx* node = static_cast<CParticlesNodeFx*>(fx);
    const uint32_t count = node->m_ui8NbActivePoints;
    if (count > 0x3f) return;
    RwV3d* point = &node->m_pAdvEmtPointList->pointList[count];
    point->z = pos.z;
    point->x = pos.x;
    point->y = pos.y;
    node->m_sgProperties = (node->m_sgProperties & ~0x2000u) | 0x2000u;
    node->m_ui8NbActivePoints = static_cast<uint8_t>(node->m_ui8NbActivePoints + 1);
}

// The frame's modelling position (dirty bit 0x20000 cleared, the frame marked dirty).
void SetFramePosition(RwFrame* frame, const CVector3& pos) {
    frame->modelling.pos.z = pos.z;
    frame->modelling.pos.x = pos.x;
    frame->modelling.pos.y = pos.y;
    frame->modelling.flags &= 0xfffdffffu;
    RwFrame_MarkDirty(frame);  // 0x00010698
}

// The explosion the bomb inlines (UpdateFuse past the timer, ProcessDamageContacts on an enemy-side volume): the volume
// detached and given back (its owner kept as the damage owner), the bomb dead, then the explosion effect (the FX
// service's pool, the inlined AcquireFx) at the bomb's foot (y less the radius), damage category 1, flags 0x244,
// triggered (no launch) and released.
void Explode(CKBomb* pool, CKBomb::Bomb* b) {
    CKDynamicBoundingSphere* volume = VolumeOf(b);
    IKSerializable* owner = volume->m_pOwner;
    if (volume->m_pParent != nullptr) volume->m_pParent->RemoveChild(volume);  // vt+0x78
    Collision()->ReleaseDynSphere(VolumeOf(b));  // 0x00191a38
    b->m_pProjectileBS = nullptr;
    b->m_baStates = static_cast<uint8_t>(b->m_baStates & 0xfeu);
    IKFx* fx = FxService()->AcquireFx(static_cast<IKFxData*>(pool->m_pExplosionFxData), pool);
    if (fx == nullptr) return;
    CKExplosionNodeFx* explosion = static_cast<CKExplosionNodeFx*>(fx);
    const CVector3 foot{b->m_v3Position.x, b->m_v3Position.y - pool->m_fRadius, b->m_v3Position.z};
    explosion->SetTranslation(&foot, pool);       // 0x001b66e8
    explosion->SetDamageOwner(owner, pool);       // 0x001b6340
    explosion->SetDamageCategory(1, pool);        // 0x001b6318
    explosion->SetDamageFlags(0x244, pool);       // 0x001b62f0
    explosion->Trigger(pool, nullptr);            // 0x001b82a8 (r5 / r6 0)
    explosion->ReleaseReservation(pool);          // vt+0x54
}

// The common start of both spawns (SpawnInstanceAtPoint without the speed store): alive (states 1), the angle, the
// timer and the contact reset, the position (and the previous one) at pos, the node shown (flag 4 off), its matrix the
// identity at pos, the shadow caster registered (with a shadow component: the ground at pos, up, height 0).
void SpawnStart(CKBomb* pool, uint8_t index, const CVector3* pos) {
    CKBomb::Bomb* b = BombAt(pool, index);
    b->m_baStates = 1;
    b->m_fAngle = 0.0f;
    b->m_fTimer = 0.0f;
    b->m_GrdContDatasInOut.m_ui8SectorNumber = 0;
    b->m_GrdContDatasInOut.m_i32FaceIndex = -1;
    b->m_GrdContDatasInOut.m_eContactStatus = 3;
    b->m_GrdContDatasInOut.m_pGround = nullptr;
    b->m_v3Position = *pos;
    b->m_v3OldPosition = *pos;
}
void SpawnPlaceNode(CKBomb* pool, uint8_t index, const CVector3* pos) {
    CKBomb::Bomb* b = BombAt(pool, index);
    CSGLeaf* node = NodeOf(b);
    node->m_sgProperties = node->m_sgProperties & 0xfffffffbu;
    static_cast<CSGMovable*>(static_cast<IKSerializable*>(node))->SetIdentity();  // 0x000d08f0
    SetFramePosition(NodeOf(b)->m_pRwFrame, *pos);
    CKBomb::Bomb* again = BombAt(pool, index);
    if (pool->m_pShadowCpnt != nullptr) {
        static_cast<CKSrvShadow*>(g_pEngine->m_srvShadow)
            ->RegisterCaster(pool->m_pShadowCpnt, again->m_pProjectileNode, &again->m_ShadowGround, 0, 0, 0);  // 0x001fb6f8
        again->m_ShadowGround.m_v3Position = again->m_v3Position;
        again->m_ShadowGround.m_v3Normal = kUpAxis;
        again->m_ShadowGround.m_fUnk18 = 0.0f;
    }
}
// The volume of both spawns (unless none is left): hung under the node at its origin, the pool's radius (not above 0:
// 0.001), infos bits 3, 5 and 2, the owner, no motion, at pos, owner type 2, infos bit 7. False when no volume was got.
bool SpawnVolume(CKBomb* pool, CKBomb::Bomb* b, const CVector3* pos, IKSerializable* owner) {
    if (b->m_pProjectileBS == nullptr) {
        b->m_pProjectileBS = Collision()->AcquireDynSphere();  // 0x00192a70
        if (b->m_pProjectileBS == nullptr) return false;
    }
    CKDynamicBoundingSphere* volume = VolumeOf(b);
    if (volume->m_pParent != nullptr) volume->m_pParent->RemoveChild(volume);  // vt+0x78
    static_cast<CSGBranch*>(b->m_pProjectileNode)->AddChild(VolumeOf(b));      // vt+0x70
    SetFramePosition(VolumeOf(b)->m_pRwFrame, kNullVector);
    if (pool->m_fRadius > kZero) {
        VolumeOf(b)->m_fRadius = pool->m_fRadius;
    } else {
        VolumeOf(b)->m_fRadius = kMinRadius;  // ble: a NaN radius too
    }
    volume = VolumeOf(b);
    volume->m_ba8Infos = static_cast<uint8_t>((volume->m_ba8Infos & 0xf7u) | 8u);
    volume->m_ba8Infos = static_cast<uint8_t>((volume->m_ba8Infos & 0xdfu) | 0x20u);
    volume->m_ba8Infos = static_cast<uint8_t>((volume->m_ba8Infos & 0xfbu) | 4u);
    volume->m_pOwner = owner;
    volume->m_v3WorldMove = kNullVector;
    volume->m_v3OldPos = *pos;
    volume->m_v3LastWorldPos = *pos;
    volume->m_ui16PropertiesFlags = 0;
    volume->m_ui8OwnerType = 0;
    volume->m_ui8OwnerType = 2;
    volume->m_ba8Infos = static_cast<uint8_t>((volume->m_ba8Infos & 0x7fu) | 0x80u);
    return true;
}

// The KStub_Return0_265a18 the hazard query calls on the enemy group (as in CKProjectileTypeBallisticPFX.cpp): 0.
IKSerializable* EnemyGroupHazardSource(int32_t /*key*/) { return nullptr; }

// The hazard query block of message 0xc32 (CKHkS08Hero_6.cpp's HazardHitQuery, the PS3 layout).
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

CKBomb::CKBomb() {}
CKBomb::~CKBomb() {}

// 0x005918f8 CKBomb_Destroy
void CKBomb::Destroy() {
    IKProjectileType::Destroy();  // 0x001f3c38 through its TOC bridge
    m_pShadowCpnt = nullptr;
}

// 0x00591930 CKBomb_MessageProc. 0xc32: the enemy group's KStub_Return0_265a18 (+0x60) gives the source whose +0x08..+0x10
// and byte +0x24 answer, the query's volume its frame's LTM position (+0x80..+0x88) the point; returns 0. BUG(original):
// the stub returns null, so the answer reads address 0 (a fault on the PS3); dotd answers nothing (as the BallisticPFX
// pool). Any other message: 1.
int32_t CKBomb::MessageProc(uint16_t message, void* data) {
    if (message != 0xc32) return 1;
    const uint8_t* source = reinterpret_cast<const uint8_t*>(EnemyGroupHazardSource(m_i32DamageType));
    if (source == nullptr) return 0;  // BUG(original), see above
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

// 0x00591a08 CKBomb_RecursiveRegistration
void CKBomb::RecursiveRegistration(int32_t type) {
    // KStub_Return1_1f3c90 (IKProjectileType's, through its TOC bridge): nothing.
    if (type != K_LEVEL_PLATEFORMS) return;
    m_pExplosionFxData->RecursiveRegistration(0);  // vt+0x24
    m_pShadowCpnt->RecursiveRegistration(0);
}

// 0x00591ab0 CKBomb_Load
int32_t CKBomb::Load(IKFile* file, int32_t type) {
    IKProjectileType::Load(file, type);  // 0x001f3ca0 through its TOC bridge
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(&m_fGravity), 8);
    m_GrdContDatasIn.m_fDeltaMax = m_fRadius;
    m_GrdContDatasIn.m_fObjectHeight = m_fRadius + m_fRadius;
    IKFile_ReadObjectRefArray(file, m_apFx, 5);
    IKFile_ReadRef(file, &m_pExplosionFxData);
    IKFile_ReadRef(file, &m_pShadowCpnt);
    // PS3: count << 2 and count * 0x88; native sizes here (a byte count).
    const uint32_t count = m_ui8MaxProjectiles;
    Bomb** list = static_cast<Bomb**>(Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(Bomb*))));
    Bomb* bombs = static_cast<Bomb*>(Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(Bomb))));
    m_aProjectiles = bombs;
    m_apProjectileList = reinterpret_cast<void**>(list);
    for (uint8_t i = 0; i < m_ui8MaxProjectiles; ++i) {
        Bomb* b = &bombs[i];
        list[i] = b;
        CSGLeaf* node = nullptr;
        IKFile_ReadRef(file, &node);
        b->m_pProjectileNode = node;
        // No null test on the PS3 (flag 4: hidden); guarded as the BallisticPFX pool's Load.
        if (node != nullptr) node->m_sgProperties = (node->m_sgProperties & ~0x4u) | 0x4u;
        b->m_pProjectileBS = nullptr;
        b->m_v3Position = kNullVector;
        b->m_v3OldPosition = kNullVector;
        b->m_v3SpeedAt = kAxisZ;
        b->m_fSpeed = 0.0f;
        b->m_GrdContDatasInOut.m_ui8SectorNumber = 0;
        b->m_GrdContDatasInOut.m_pGround = nullptr;
        b->m_GrdContDatasInOut.m_i32FaceIndex = -1;
        b->m_GrdContDatasInOut.m_eContactStatus = 3;
        b->m_ShadowGround.m_bUsed_maybe = 0;
        b->m_baStates = 0;
        b->m_fTimer = 0.0f;
        b->m_fAngle = 0.0f;
    }
    ReadS32LE(file, &m_i32DamageType);
    return 1;
}

// 0x0058efb0 CKBomb_IsDead
uint8_t CKBomb::IsDead(uint8_t index) { return static_cast<uint8_t>((BombAt(this, index)->m_baStates & 1u) ^ 1u); }

// 0x0058ea10 CKBomb_OnDeath
void CKBomb::OnDeath(uint8_t index) { KillProjectile(index); }  // vt+0x60

// 0x0058f090 CKBomb_KillInstance: not alive, the node hidden, the shadow given back (with a shadow component), the volume
// detached and released, then the active bombs compacted (the last active one takes the slot).
void CKBomb::KillProjectile(uint8_t index) {
    Bomb* b = BombAt(this, index);
    b->m_baStates = 0;
    CSGLeaf* node = static_cast<CSGLeaf*>(b->m_pProjectileNode);
    node->m_sgProperties = (node->m_sgProperties & 0xfffffffbu) | 4u;
    if (m_pShadowCpnt != nullptr) {
        static_cast<CKSrvShadow*>(g_pEngine->m_srvShadow)->UnregisterCaster(&BombAt(this, index)->m_ShadowGround,
                                                                           m_pShadowCpnt);  // 0x001fd6f0
    }
    if (b->m_pProjectileBS != nullptr) {
        CKDynamicBoundingSphere* volume = static_cast<CKDynamicBoundingSphere*>(b->m_pProjectileBS);
        if (volume->m_pParent != nullptr) volume->m_pParent->RemoveChild(volume);  // vt+0x78
        static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision)
            ->ReleaseDynSphere(static_cast<CKDynamicBoundingSphere*>(b->m_pProjectileBS));  // 0x00191a38
        b->m_pProjectileBS = nullptr;
    }
    const uint8_t last = static_cast<uint8_t>(m_ui8NbOfActiveProjectiles - 1);
    if (index != m_ui8NbOfActiveProjectiles - 1) {
        m_ui8NbOfActiveProjectiles = last;
        m_apProjectileList[index] = m_apProjectileList[last];
        m_apProjectileList[m_ui8NbOfActiveProjectiles] = b;
        return;
    }
    m_ui8NbOfActiveProjectiles = last;
}

// 0x0058ec10 CKBomb_UpdateAttachedTransform_maybe
void CKBomb::UpdateShadowGround(uint8_t index) {
    Bomb* b = BombAt(this, index);
    CGroundContactDatasInOut& contact = b->m_GrdContDatasInOut;
    CKShadowGround& shadow = b->m_ShadowGround;
    if (contact.m_eContactStatus == 0 || contact.m_eContactStatus == 1) {
        ICollisionMesh* ground = static_cast<ICollisionMesh*>(contact.m_pGround);
        const bool dynamic = ground->GetClassID() == 0x13;  // vt+0x18: CDynamicGround
        shadow.m_v3Position = contact.m_ProjectionOnGround;
        shadow.m_v3Normal = contact.m_Normal;
        shadow.m_fUnk18 = contact.m_fdH;
        if (!dynamic) return;
        const CVector3 position = shadow.m_v3Position;
        const CVector3 normal = shadow.m_v3Normal;
        Mat4_TransformPoints(static_cast<ICollisionMesh*>(contact.m_pGround)->GetWorldMatrix(), &shadow.m_v3Position,
                             &position, 1);  // vt+0x50, 0x0023f7e8
        Mat4_TransformVectors(static_cast<ICollisionMesh*>(contact.m_pGround)->GetWorldMatrix(), &shadow.m_v3Normal,
                              &normal, 1);  // 0x0023f7b0
        return;
    }
    shadow.m_v3Position = b->m_v3Position;
    shadow.m_v3Normal = kUpAxis;
    shadow.m_fUnk18 = contact.m_fdH;
}

// 0x0058f2d0 CKBomb_UpdateFuse_maybe: past the explosion time (ble: a NaN timer stays a fuse) the explosion; else the
// spark point of the quarter reached (the fourth effect past 3/4, the third past 1/2, the second past 1/4 (bge: NaN
// the first), the first). The timer advances (fadds) after either.
void CKBomb::UpdateFuse(float dt, uint8_t index) {
    Bomb* b = BombAt(this, index);
    const float limit = m_fExplosionTimer;
    const float timer = b->m_fTimer;
    if (timer > limit) {
        Explode(this, b);
    } else {
        IKSerializable* fx;
        if (limit * kQuarter3 < timer) {
            fx = m_apFx[3];
        } else if (limit * kHalf < timer) {
            fx = m_apFx[2];
        } else if (limit * kQuarter < timer) {
            fx = m_apFx[1];
        } else {
            fx = m_apFx[0];
        }
        AddFxPoint(fx, b->m_v3Position);
    }
    b->m_fTimer = b->m_fTimer + dt;
}

// 0x0058f7c0 CKBomb_SpawnInstance (the PS3 r7 is not read)
void CKBomb::SpawnInstance(uint8_t index, const CVector3* pos, const CVector3* dir, float speed, IKSerializable* owner) {
    Bomb* b = BombAt(this, index);
    b->m_fSpeed = speed;
    SpawnStart(this, index, pos);
    b->m_v3SpeedAt = *dir;
    SpawnPlaceNode(this, index, pos);
    SpawnVolume(this, b, pos, owner);
}

// 0x00590088 CKBomb_SpawnInstanceAtPoint: the spawn without the speed, then the throw. The flat distance d to the target
// (fmadds(dz, dz, fmadds(dx, dx, 0))) over the speed is the flight time; with a velocity the target is led by it times
// the time times `lead`. The direction is the flat one to the (led) target, normalised, times the speed, its y the
// speed times the height difference over the flat length plus the length times half the gravity over the speed; the
// result normalised, its length the speed (at most 999: bgt).
void CKBomb::SpawnInstanceAtPoint(uint8_t index, const CVector3* pos, const CVector3* target, IKSerializable* owner,
                                  const CVector3* velocity, float speed, float lead) {
    Bomb* b = BombAt(this, index);
    SpawnStart(this, index, pos);
    SpawnPlaceNode(this, index, pos);
    SpawnVolume(this, b, pos, owner);
    CVector3& at = b->m_v3SpeedAt;
    float flat;
    float dy;
    if (velocity != nullptr) {
        const float tx = target->x - pos->x;
        const float tz = target->z - pos->z;
        float distance = MathSqrtf(ppc::fmadds(tz, tz, ppc::fmadds(tx, tx, kZero)));
        if (distance == kZero) distance = kZero;
        const float time = (distance / speed) * lead;
        at.y = kZero;
        at.x = ppc::fmadds(time, velocity->x, target->x) - pos->x;
        at.z = ppc::fmadds(time, velocity->z, target->z) - pos->z;
        flat = MathSqrtf(ppc::fmadds(at.z, at.z, ppc::fmadds(at.x, at.x, at.y * at.y)));
        if (flat != kZero) {
            const float inv = kOne / flat;
            at.z = inv * at.z;
            at.x = inv * at.x;
            at.y = inv * at.y;
        } else {
            flat = kZero;
        }
        dy = ppc::fmadds(time, velocity->y, target->y) - pos->y;
    } else {
        at.x = target->x - pos->x;
        at.y = kZero;
        at.z = target->z - pos->z;
        flat = MathSqrtf(ppc::fmadds(at.z, at.z, ppc::fmadds(at.x, at.x, at.y * at.y)));
        if (flat != kZero) {
            const float inv = kOne / flat;
            at.z = inv * at.z;
            at.x = inv * at.x;
            at.y = inv * at.y;
        } else {
            flat = kZero;
        }
        dy = target->y - pos->y;
    }
    at.x = speed * at.x;
    at.z = speed * at.z;
    const float halfGravity = m_fGravity * kHalf;
    const float rise = (speed * dy) / flat;
    const float fall = (flat * halfGravity) / speed;
    at.y = rise + fall;
    const float length = MathSqrtf(ppc::fmadds(at.z, at.z, ppc::fmadds(at.x, at.x, at.y * at.y)));
    if (length == kZero) {
        b->m_fSpeed = kZero;
        return;
    }
    const float inv = kOne / length;
    at.z = inv * at.z;
    at.x = inv * at.x;
    at.y = inv * at.y;
    b->m_fSpeed = length > kMaxThrowSpeed ? kMaxThrowSpeed : length;
}

// 0x0058fc18 CKBomb_LaunchEx (the damage on the volume, +0x1c)
uint8_t CKBomb::LaunchEx(IKSerializable* /*data*/, const CVector3* pos, const CVector3* dir, float speed,
                         IKSerializable* damage, IKSerializable* owner, const RwMatrix* /*matrix*/) {
    const uint8_t index = m_ui8NbOfActiveProjectiles;
    if (!(m_ui8MaxProjectiles > index)) return 0;
    const CVector3 from = *pos;
    const CVector3 along = *dir;
    SpawnInstance(index, &from, &along, speed, owner);
    Bomb* b = BombAt(this, index);
    if (b->m_pProjectileBS != nullptr) static_cast<IKBoundingVolume*>(b->m_pProjectileBS)->m_unk1c = damage;
    m_ui8NbOfActiveProjectiles = static_cast<uint8_t>(m_ui8NbOfActiveProjectiles + 1);
    return 1;
}

// 0x0058fd18 CKBomb_Launch
uint8_t CKBomb::Launch(IKSerializable* /*data*/, const CVector3* pos, const CVector3* dir, float speed,
                       IKSerializable* owner, const RwMatrix* /*matrix*/) {
    const uint8_t index = m_ui8NbOfActiveProjectiles;
    if (!(m_ui8MaxProjectiles > index)) return 0;
    const CVector3 from = *pos;
    const CVector3 along = *dir;
    SpawnInstance(index, &from, &along, speed, owner);
    m_ui8NbOfActiveProjectiles = static_cast<uint8_t>(m_ui8NbOfActiveProjectiles + 1);
    return 1;
}

// 0x00590820 CKBomb_LaunchAtPointEx (see the header: no velocity / lead reach the dotd slot)
uint8_t CKBomb::LaunchAtPointEx(IKSerializable* /*data*/, const CVector3* pos, const CVector3* target, float speed,
                                IKSerializable* damage, IKSerializable* owner) {
    const uint8_t index = m_ui8NbOfActiveProjectiles;
    if (!(m_ui8MaxProjectiles > index)) return 0;
    const CVector3 from = *pos;
    const CVector3 to = *target;
    SpawnInstanceAtPoint(index, &from, &to, owner, nullptr, speed, 0.0f);
    Bomb* b = BombAt(this, index);
    if (b->m_pProjectileBS != nullptr) static_cast<IKBoundingVolume*>(b->m_pProjectileBS)->m_unk1c = damage;
    m_ui8NbOfActiveProjectiles = static_cast<uint8_t>(m_ui8NbOfActiveProjectiles + 1);
    return 1;
}

// 0x00590928 CKBomb_LaunchAtPoint
uint8_t CKBomb::LaunchAtPoint(IKSerializable* /*data*/, const CVector3* pos, const CVector3* target, float speed,
                              IKSerializable* owner) {
    const uint8_t index = m_ui8NbOfActiveProjectiles;
    if (!(m_ui8MaxProjectiles > index)) return 0;
    const CVector3 from = *pos;
    const CVector3 to = *target;
    SpawnInstanceAtPoint(index, &from, &to, owner, nullptr, speed, 0.0f);
    m_ui8NbOfActiveProjectiles = static_cast<uint8_t>(m_ui8NbOfActiveProjectiles + 1);
    return 1;
}

// 0x0058fdb8 CKBomb_UpdateMotion. Faster than 0.1 (bgt): the speed damped by the air (speed - dt * speed * damp), the
// previous position kept, the position advanced (fmadds) by the speed along the direction, y less dt * gravity
// (fmsubs), the new velocity normalised into the direction and its length the speed (0 for none). The angle step: the
// speed * dt over the radius when faster than 0.1, else dt (ble). Faster than the trail speed (ble: NaN none), a trail
// point. Then the shadow's ground and, with the fuse lit (bit 1), the fuse.
void CKBomb::UpdateMotion(uint8_t index, float dt) {
    Bomb* b = BombAt(this, index);
    if (b->m_fSpeed > kMinSpeed) {
        const float speed = b->m_fSpeed - dt * (b->m_fSpeed * m_fAirDamp);
        b->m_fSpeed = speed;
        float vx = speed * b->m_v3SpeedAt.x;
        float vz = speed * b->m_v3SpeedAt.z;
        const float fallStep = dt * m_fGravity;
        b->m_v3OldPosition.x = b->m_v3Position.x;
        b->m_v3OldPosition.z = b->m_v3Position.z;
        b->m_v3OldPosition.y = b->m_v3Position.y;
        b->m_v3Position.x = ppc::fmadds(dt, vx, b->m_v3Position.x);
        b->m_v3Position.z = ppc::fmadds(dt, vz, b->m_v3Position.z);
        float vy = ppc::fmsubs(speed, b->m_v3SpeedAt.y, fallStep);
        b->m_v3Position.y = ppc::fmadds(dt, vy, b->m_v3Position.y);
        float length = MathSqrtf(ppc::fmadds(vz, vz, ppc::fmadds(vx, vx, vy * vy)));
        if (length == kZero) {
            length = kZero;
        } else {
            const float inv = kOne / length;
            vz = vz * inv;
            vx = vx * inv;
            vy = vy * inv;
        }
        b->m_fSpeed = length;
        b->m_v3SpeedAt.z = vz;
        b->m_v3SpeedAt.x = vx;
        b->m_v3SpeedAt.y = vy;
    }
    if (b->m_fSpeed > kMinSpeed) {
        b->m_fAngle = (b->m_fSpeed * dt) / m_fRadius;
    } else {
        b->m_fAngle = dt;
    }
    if (b->m_fSpeed > m_fMinSpeedFx) AddFxPoint(m_apFx[4], BombAt(this, index)->m_v3Position);
    UpdateShadowGround(index);
    if (((b->m_baStates >> 1) & 1u) != 0) UpdateFuse(dt, index);
}

// 0x005909d0 CKBomb_UpdateOrientation (dt not read). Rolling (bgt 0.1): the roll axis is X when the direction is within
// 0.99 of vertical (above 0.99 or a NaN, or below -0.99), else up x direction (fmsubs, normalised); the node turned by
// the angle step in degrees. Slow: the node's up axis (frame modelling.up) brought toward vertical (y up by 5 per angle
// step to 1; x and z toward 0 by 5 per step, clamped at 0), normalised, the node oriented from it and the modelling
// right row (the original passes the frame +0x10). The node is then put at the position.
void CKBomb::UpdateOrientation(uint8_t index, float /*dt*/) {
    Bomb* b = BombAt(this, index);
    if (b->m_fSpeed > kMinSpeed) {
        const float sy = b->m_v3SpeedAt.y;
        bool vertical;
        if (sy < kZero) {
            vertical = sy < -kVertical;
        } else {
            vertical = !(sy <= kVertical);
        }
        CVector3 axis;
        if (vertical) {
            axis = kAxisX;
        } else {
            const CVector3& s = b->m_v3SpeedAt;
            const float ux = kUpAxis.x;
            const float uy = kUpAxis.y;
            const float uz = kUpAxis.z;
            axis.x = ppc::fmsubs(uy, s.z, uz * s.y);
            axis.y = ppc::fmsubs(uz, s.x, ux * s.z);
            axis.z = ppc::fmsubs(ux, s.y, uy * s.x);
            const float length = MathSqrtf(ppc::fmadds(axis.z, axis.z, ppc::fmadds(axis.x, axis.x, axis.y * axis.y)));
            if (length != kZero) {
                const float inv = kOne / length;
                axis.z = axis.z * inv;
                axis.x = axis.x * inv;
                axis.y = axis.y * inv;
            }
        }
        static_cast<CSGMovable*>(b->m_pProjectileNode)->RotateInPlace(&axis.x, b->m_fAngle * kRadToDeg);  // 0x000d11b0
    } else {
        RwFrame* frame = NodeOf(b)->m_pRwFrame;
        CVector3 up{frame->modelling.up.x, frame->modelling.up.y, frame->modelling.up.z};
        bool settle;
        if (up.y < kOne) {
            up.y = ppc::fmadds(b->m_fAngle, kUprightRate, up.y);
            if (up.y > kOne) {
                up.y = kOne;
                settle = true;
            } else {
                settle = up.y > kZero;
            }
        } else {
            settle = up.y > kZero;
        }
        if (settle) {
            if (up.x != kZero) {
                if (up.x < kZero) {
                    up.x = ppc::fmadds(b->m_fAngle, kUprightRate, up.x);
                    if (up.x > kZero) up.x = kZero;
                } else {
                    up.x = ppc::fmadds(b->m_fAngle, -kUprightRate, up.x);
                    if (up.x < kZero) up.x = kZero;
                }
            }
            if (up.z != kZero) {
                if (up.z < kZero) {
                    up.z = ppc::fmadds(b->m_fAngle, kUprightRate, up.z);
                    if (up.z > kZero) up.z = kZero;
                } else {
                    up.z = ppc::fmadds(b->m_fAngle, -kUprightRate, up.z);
                    if (up.z < kZero) up.z = kZero;
                }
            }
        }
        const float length = MathSqrtf(ppc::fmadds(up.z, up.z, ppc::fmadds(up.x, up.x, up.y * up.y)));
        if (length != kZero) {
            const float inv = kOne / length;
            up.z = up.z * inv;
            up.x = up.x * inv;
            up.y = up.y * inv;
        }
        RwFrame* now = NodeOf(b)->m_pRwFrame;
        static_cast<CSGMovable*>(b->m_pProjectileNode)
            ->SetOrientationFromUpAt(&up, reinterpret_cast<const CVector3*>(&now->modelling.right));  // 0x000d0a88
    }
    SetFramePosition(NodeOf(b)->m_pRwFrame, b->m_v3Position);
}

// 0x00590d30 CKBomb_UpdateCollision (dt not read). The ground probe from the bomb's foot (a fall deepens the test:
// bgt). Status 1 (on the ground): slow (ble 0.1) the bomb lands on the projection, its foot on it, speed 0; fast it
// bounces off the normal: the position pushed out by (spring + 1) times the normal's share of the height, the direction
// reflected by (spring + 1) times its share along the normal, normalised; the speed times the spring and the fuse lit.
// Status 2 or 3: the wall raycast of this frame's motion; no wall: the bomb dies (bit 0 cleared); a wall: the same
// bounce off the wall's flat normal (edge z, 0, -edge x). The probe's step and height are restored at the end.
void CKBomb::UpdateCollision(uint8_t index, float /*dt*/) {
    Bomb* b = BombAt(this, index);
    const float radius = m_fRadius;
    const float points[3] = {b->m_v3Position.x, b->m_v3Position.y - radius, b->m_v3Position.z};
    const float fall = b->m_v3OldPosition.y - b->m_v3Position.y;
    if (fall > kZero) {
        m_GrdContDatasIn.m_fDeltaMax = fall + radius;
        m_GrdContDatasIn.m_fObjectHeight = fall + (m_fRadius + m_fRadius);
    }
    Collision()->GroundProbePoints(reinterpret_cast<const ::CGroundContactDatasIn*>(&m_GrdContDatasIn),
                                   reinterpret_cast<::CGroundContactDatasInOut*>(&b->m_GrdContDatasInOut), points,
                                   1);  // 0x00196540
    const uint32_t status = b->m_GrdContDatasInOut.m_eContactStatus;
    const int32_t signedStatus = static_cast<int32_t>(status);
    bool bounced = false;
    if (signedStatus == 1) {
        if (!(b->m_fSpeed > kMinSpeed)) {
            b->m_v3Position.y = b->m_GrdContDatasInOut.m_ProjectionOnGround.y;
            b->m_v3Position.z = b->m_GrdContDatasInOut.m_ProjectionOnGround.z;
            b->m_v3Position.x = b->m_GrdContDatasInOut.m_ProjectionOnGround.x;
            const float y = b->m_v3Position.y + m_fRadius;
            b->m_fSpeed = kZero;
            b->m_v3Position.y = y;
        } else {
            const CVector3 n = b->m_GrdContDatasInOut.m_Normal;
            const float k = m_fContactSpring + kOne;
            const float share = ppc::fmadds(n.z, kZero, ppc::fmadds(n.x, kZero, n.y * b->m_GrdContDatasInOut.m_fdH));
            const float sy = n.y * share;
            const float sx = n.x * share;
            const float sz = n.z * share;
            b->m_v3Position.y = ppc::fmadds(k, sy, b->m_v3Position.y);
            b->m_v3Position.x = ppc::fmadds(sx, k, b->m_v3Position.x);
            b->m_v3Position.z = ppc::fmadds(k, sz, b->m_v3Position.z);
            CVector3& at = b->m_v3SpeedAt;
            const float k2 = m_fContactSpring + kOne;
            const float dot = ppc::fmadds(n.z, at.z, ppc::fmadds(n.x, at.x, n.y * at.y));
            const float ry = at.y - k2 * (n.y * dot);
            const float rx = at.x - (n.x * dot) * k2;
            const float rz = at.z - k2 * (n.z * dot);
            at.y = ry;
            at.x = rx;
            at.z = rz;
            const float length = MathSqrtf(ppc::fmadds(rz, rz, ppc::fmadds(rx, rx, ry * ry)));
            if (length != kZero) {
                const float inv = kOne / length;
                at.z = inv * at.z;
                at.x = inv * at.x;
                at.y = inv * at.y;
            }
            bounced = true;
        }
    } else if (signedStatus >= 1 && signedStatus <= 3) {
        CLine line;
        line.m_start = b->m_v3OldPosition;
        line.m_VectDir.x = b->m_v3Position.x - b->m_v3OldPosition.x;
        line.m_VectDir.y = b->m_v3Position.y - b->m_v3OldPosition.y;
        line.m_VectDir.z = b->m_v3Position.z - b->m_v3OldPosition.z;
        CGroundEdgeDatasOut out;
        if (Collision()->RaycastWalls(&line, m_fRadius, &out, 0, nullptr, 1) == 0) {  // 0x00198438
            b->m_baStates = static_cast<uint8_t>(b->m_baStates & 0xfeu);
        } else {
            float ex = out.m_Edge.m_VectDir.x;
            float ez = out.m_Edge.m_VectDir.z;
            const float t = out.m_ftLine;
            const float length = MathSqrtf(ppc::fmadds(ez, ez, ppc::fmadds(ex, ex, kZero)));
            if (length != kZero) {
                const float inv = kOne / length;
                ez = ez * inv;
                ex = ex * inv;
            }
            // The wall's flat normal (ez, 0, -ex).
            const float nx = ez;
            const float nz = -ex;
            const float hitY0 = ppc::fmadds(t, kZero, kZero) * kZero;
            const float hitX = ppc::fmadds(t, line.m_VectDir.x, b->m_v3OldPosition.x) - b->m_v3Position.x;
            const float hitZ = ppc::fmadds(t, line.m_VectDir.z, b->m_v3OldPosition.z) - b->m_v3Position.z;
            const float k = m_fContactSpring + kOne;
            b->m_v3Position.y = b->m_v3Position.y + kZero;
            const float share = ppc::fmadds(nz, hitZ, ppc::fmadds(nx, hitX, hitY0));
            b->m_v3Position.x = ppc::fmadds(nx * share, k, b->m_v3Position.x);
            b->m_v3Position.z = ppc::fmadds(k, nz * share, b->m_v3Position.z);
            CVector3& at = b->m_v3SpeedAt;
            const float k2 = m_fContactSpring + kOne;
            const float dot = ppc::fmadds(nz, at.z, ppc::fmadds(nx, at.x, at.y * kZero));
            const float ry = at.y - k2 * (dot * kZero);
            const float rx = at.x - (nx * dot) * k2;
            const float rz = at.z - k2 * (nz * dot);
            at.y = ry;
            at.x = rx;
            at.z = rz;
            const float len = MathSqrtf(ppc::fmadds(rz, rz, ppc::fmadds(rx, rx, ry * ry)));
            if (len != kZero) {
                const float inv = kOne / len;
                at.z = inv * at.z;
                at.x = inv * at.x;
                at.y = inv * at.y;
            }
            bounced = true;
        }
    }
    if (bounced) {
        b->m_fSpeed = b->m_fSpeed * m_fContactSpring;
        b->m_baStates = static_cast<uint8_t>((b->m_baStates & 0xfdu) | 2u);
    }
    m_GrdContDatasIn.m_fDeltaMax = m_fRadius;
    m_GrdContDatasIn.m_fObjectHeight = m_fRadius + m_fRadius;
}

// 0x005911d0 CKBomb_ProcessDamageContacts. For each contact of the volume (with a contact set): the other volume's
// owner type 1 with option bit 0 blows the bomb up (and ends the walk); types 1 (without the option) and 3: the fuse is
// lit, the bomb is put out of the contact (the point plus the radius against the normal) and its volume there with no
// motion; when it moves into the contact (dot >= 0, cror) or is slow (below 0.1; bge: NaN not): off the first
// controlled hero it jumps (speed below 2 (bge): 10, else times the spring; the direction the reversed normal plus up,
// normalised), off anything else it reflects (the velocity plus twice its share along the reversed normal, normalised,
// the length times the spring).
void CKBomb::ProcessDamageContacts(uint8_t index) {
    Bomb* b = BombAt(this, index);
    if (b->m_pProjectileBS == nullptr) return;
    for (ICollision* c = static_cast<ICollision*>(VolumeOf(b)->m_CollisionResList); c != nullptr; c = c->m_pNext) {
        if (c->HasContactSet() == 0) continue;  // vt+0x08
        c->GetBoundingVolume1();  // vt+0x00 (the result unused)
        IKBoundingVolume* other = static_cast<IKBoundingVolume*>(c->GetBoundingVolume2());  // vt+0x04
        const uint8_t type = other->m_ui8OwnerType;
        if (type == 1) {
            if ((m_baOptions & 1u) != 0) {
                Explode(this, b);
                return;
            }
        } else if (type != 3) {
            continue;
        }
        IKSerializable* hero =
            static_cast<IKGrpHero*>(g_pEngine->m_gameManager->m_unk04[1])->m_apControlledHeroes[0];  // 0x002ca0e0
        b->m_baStates = static_cast<uint8_t>((b->m_baStates & 0xfdu) | 2u);
        const float vx = ppc::fmadds(b->m_fSpeed, b->m_v3SpeedAt.x, kNullVector.x);
        const float vy = ppc::fmadds(b->m_fSpeed, b->m_v3SpeedAt.y, kNullVector.y);
        const float vz = ppc::fmadds(b->m_fSpeed, b->m_v3SpeedAt.z, kNullVector.z);
        const CVector3 n = *c->GetNormale12();  // vt+0x1c
        float nx = -n.x;
        float ny = -n.y;
        float nz = -n.z;
        const float dot = ppc::fmadds(vz, n.z, ppc::fmadds(vx, n.x, vy * n.y));
        const CVector3 point = *c->GetWorldContactPoint();  // vt+0x20
        const float r = m_fRadius;
        const float pz = ppc::fmadds(nz, r, point.z);
        const float px = ppc::fmadds(nx, r, point.x);
        const float py = ppc::fmadds(ny, r, point.y);
        b->m_v3Position.z = pz;
        b->m_v3Position.x = px;
        b->m_v3Position.y = py;
        CKDynamicBoundingSphere* volume = VolumeOf(b);
        volume->m_v3WorldMove = kNullVector;
        volume->m_v3OldPos = {px, py, pz};
        volume->m_v3LastWorldPos = {px, py, pz};
        if (!(dot >= kZero) && !(b->m_fSpeed < kMinSpeed)) continue;
        if (other->m_pOwner == hero) {
            if (b->m_fSpeed < kHeroBounceMin) {
                b->m_fSpeed = kHeroBounceSpeed;
            } else {
                b->m_fSpeed = b->m_fSpeed * m_fContactSpring;
            }
            float uy = ny + kOne;
            const float length = MathSqrtf(ppc::fmadds(nz, nz, ppc::fmadds(nx, nx, uy * uy)));
            if (length != kZero) {
                const float inv = kOne / length;
                nz = nz * inv;
                nx = nx * inv;
                uy = uy * inv;
            }
            b->m_v3SpeedAt.z = nz;
            b->m_v3SpeedAt.x = nx;
            b->m_v3SpeedAt.y = uy;
            continue;
        }
        const float twice = dot + dot;
        float ry = ppc::fmadds(ny, twice, vy);
        float rx = ppc::fmadds(nx, twice, vx);
        float rz = ppc::fmadds(nz, twice, vz);
        float length = MathSqrtf(ppc::fmadds(rz, rz, ppc::fmadds(rx, rx, ry * ry)));
        if (length != kZero) {
            const float inv = kOne / length;
            rz = rz * inv;
            rx = rx * inv;
            ry = ry * inv;
        } else {
            length = kZero;
        }
        b->m_fSpeed = length;
        b->m_v3SpeedAt.z = rz;
        b->m_v3SpeedAt.x = rx;
        b->m_v3SpeedAt.y = ry;
        b->m_fSpeed = b->m_fSpeed * m_fContactSpring;
    }
}
