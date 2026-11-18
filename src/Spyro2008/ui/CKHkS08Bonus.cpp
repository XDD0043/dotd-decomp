// CKHkS08Bonus.cpp - reconstructed original translation unit 0x5b7098-0x5b9f08 (GAME_TOC2, main_toc2), 31 functions, 30 live.
// Primary owner: CKHkS08Bonus (not a registered class)
// Other owners: RegisterCKHkS08BonusClass (1), BonusGem (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x5b7098  CKHkS08Bonus_SeekNearestHero_maybe
//   [ ] 0x5b7278  CKHkS08Bonus_UpdateTrailEndpoints_maybe  [dead: no pointer to its descriptor 0xbf1058]
//   [ ] 0x5b72c0  CKHkS08Bonus_SetRotationDeg_maybe  [dead: no pointer to its descriptor 0xbf1060]
//   [ ] 0x5b7390  CKHkS08Bonus_GetSplineLockLaunchData_maybe  [dead]
//   [ ] 0x5b73c0  CKHkS08Bonus_PlayCollectFx_maybe  [dead: no pointer to its descriptor 0xbf1070]
//   [ ] 0x5b7418  CKHkS08Bonus_TriggerCollectExplosion_maybe  [dead: no pointer to its descriptor 0xbf1078]
//   [x] 0x5b7470  CKHkS08Bonus_ReturnToPool_maybe
//   [x] 0x5b74d8  CKHkS08Bonus_DestroyArray
//   [x] 0x5b7580  CKHkS08Bonus_Create
//   [ ] 0x5b7628  RegisterCKHkS08BonusClass
//   [ ] 0x5b76b0  _GLOBAL__D_5b76b0
//   [ ] 0x5b76c0  _GLOBAL__I_5b76c0
//   [x] 0x5b76d0  CKHkS08Bonus_vfE4
//   [x] 0x5b7758  CKHkS08Bonus_SetLaunchVelocity_maybe
//   [x] 0x5b7890  CKHkS08Bonus_DisableAndReleaseFx_maybe
//   [x] 0x5b78f8  CKHkS08Bonus_SetVisible
//   [x] 0x5b7a58  CKHkS08Bonus_ClearReferences  (empty: IKBaseClass's Destroy)
//   [x] 0x5b7a60  CKHkS08Bonus_CreateArray
//   [x] 0x5b7b60  CKHkS08Bonus_LevelReset  (RecursiveRegistration)
//   [x] 0x5b7bf0  CKHkS08Bonus_Load
//   [ ] 0x5b7db0  CKHkS08Bonus_Save
//   [x] 0x5b7f88  CKHkS08Bonus_SpawnAtPosition_maybe
//   [x] 0x5b8178  CKHkS08Bonus_SpawnAt_maybe
//   [ ] 0x5b8448  CKHkS08Bonus_JitterDirection_maybe  [dead: no pointer to its descriptor 0xbf1200]
//   [x] 0x5b8590  CKHkS08Bonus_InitFlyToHeroCurve_maybe
//   [x] 0x5b8900  BonusGem_Collect
//   [ ] 0x5b8ba0  CKHkS08Bonus_UpdateSpin_maybe  [dead: no pointer to its descriptor 0xbf1218]
//   [x] 0x5b8cf8  CKHkS08Bonus_UpdateFlyToHero_maybe
//   [x] 0x5b9428  CKHkS08Bonus_ResolveBounceCollision_maybe
//   [ ] 0x5b9988  CKHkS08Bonus_UpdateBouncePhysics_maybe  [dead: no pointer to its descriptor 0xbf12b0]
//   [x] 0x5b9c28  CKHkS08Bonus_Update
//
//   [ ] 0x9cc850  CKHkS08Bonus_GetClassGroup  [inline]
//   [ ] 0x9cc858  CKHkS08Bonus_GetClassId  [inline]
//   [x] 0x9cc860  CKHkS08Bonus_vfCC  [inline]
//   [ ] 0x9cc880  CKHkS08Bonus_IsKindOf  [inline]
//   [ ] 0x9cc8d8  CKHkS08Bonus_Destructor  [inline]
//   [ ] 0x9cc8f8  CKHkS08Bonus_DeletingDestructor  [inline]
//   [ ] 0x9cc948  KBase606_vf8  [inline]
//   [ ] 0x9cc970  KBase606_vf14  [inline]
//   [ ] 0x9cc978  KBase606_vf18  [inline]
//   [ ] 0x9cc980  KBase606_vf10  [inline]
#include "Spyro2008/ui/CKHkS08Bonus.h"

#include <cmath>

#include "Renderware/rwcore/RwCamera.h"
#include "Spyro2008/groups/IKGrpHero.h"
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "Spyro2008/logic/CKS08GameManager.h"
#include "Spyro2008/memory/CKGrpS08BonusPool.h"
#include "Spyro2008/ui/CKS08BonusCpnt.h"
#include "crt/ppc_ops.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/math/Vec3.h"
#include "k2000/memory/CKGrpBonusPool.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/misc/Engine.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/misc/Mat4.h"
#include "k2000/scenegraph/CSGLeaf.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/services/CKSrvBeacon.h"
#include "k2000/services/CKSrvCollision.h"
#include "k2000/services/CollisionDatas.h"
#include "k2000/services/ICollisionMesh.h"
#include "k2000/system/IKTime.h"

namespace {

// The shared axes and the null vector (0x00c50d34 / 0x00c50d40 / 0x00c50d64; zero in the EBOOT's BSS, filled by
// static initialisers).
const CVector3 kAxisX = {1.0f, 0.0f, 0.0f};
const CVector3 kAxisY = {0.0f, 1.0f, 0.0f};
const CVector3 kNullVector = {0.0f, 0.0f, 0.0f};
constexpr float kRandScale = -3.0518044e-05f;      // TOC2 -0x6450 (0xb8000080, -1 / 32767.5)
constexpr float kRand65535 = 65535.0f;             // TOC2 -0x6434 (0x477fff00)
constexpr float kRadToDeg = 57.2957802f;           // TOC2 -0x6414 (0x42652ee1)
constexpr float kFltMax = 3.40282347e+38f;         // 0x00c4ace0 (the float limits table +0x28)

// Rand_Int (0x00011500, through its TOC bridge), its low 16 bits as a float (rldicl 48, fcfid, frsp: exact). Macros, so
// that the rand log (DOTD_REPLAY_RANDLOG) names the function that draws.
#define BONUS_RAND_U16() static_cast<float>(static_cast<uint32_t>(Rand_Int()) & 0xffffu)
// fmadds(r, -1 / 32767.5, 1): -1 .. 1.
#define BONUS_RAND_SIGNED() ppc::fmadds(BONUS_RAND_U16(), kRandScale, 1.0f)

CSGMovable* NodeOf(const CKHkS08Bonus* bonus) { return static_cast<CSGMovable*>(bonus->m_pKGLObject); }
RwFrame* FrameOf(const CKHkS08Bonus* bonus) { return NodeOf(bonus)->m_pRwFrame; }
CKGrpBonusPool* PoolOf(const CKHkS08Bonus* bonus) { return static_cast<CKGrpBonusPool*>(bonus->m_pUnk28); }
CKS08BonusCpnt* CpntOf(const CKHkS08Bonus* bonus) { return static_cast<CKS08BonusCpnt*>(bonus->m_pUnk2C); }
CVector3* AsVec(RwV3d* v) { return reinterpret_cast<CVector3*>(v); }

// The frame's modelling position set (z, x, y as the original stores it), rwMATRIXINTERNALIDENTITY cleared (the
// rlwinm 14 / rotlwi 18 pair), the frame marked dirty (0x00010698 through its TOC bridge).
void PlaceFrame(CKHkS08Bonus* bonus, const CVector3& position) {
    RwFrame* frame = FrameOf(bonus);
    frame->modelling.pos.z = position.z;
    frame->modelling.pos.x = position.x;
    frame->modelling.pos.y = position.y;
    frame->modelling.flags &= 0xfffdffffu;
    RwFrame_MarkDirty(FrameOf(bonus));
}

// The spin axis of a moving bonus (Update / UpdateFlyToHero): the world y axis crossed with the horizontal velocity
// normalised (`h` its length), or the frame's right axis when it is (almost) still.
void SpinAxis(const CKHkS08Bonus* bonus, CVector3* axis) {
    const float zero = 0.0f;  // TOC2 -0x642c
    const float vx = bonus->m_unk44.x;
    const float vz = bonus->m_unk44.z;
    const float h = std::sqrt(ppc::fmadds(vz, vz, ppc::fmadds(vx, vx, zero)));  // 0x00010690 Math_Sqrtf
    if (h == zero || h < 0.05f) {  // TOC2 -0x641c
        const RwFrame* frame = FrameOf(bonus);
        axis->x = frame->modelling.right.x;
        axis->y = frame->modelling.right.y;
        axis->z = frame->modelling.right.z;
        return;
    }
    const float k = 1.0f / h;
    const float z = vz * k;
    const float x = vx * k;
    const float y = k * zero;
    axis->y = ppc::fmsubs(x, kAxisY.z, z * kAxisY.x);
    axis->z = ppc::fmsubs(y, kAxisY.x, x * kAxisY.y);
    axis->x = ppc::fmsubs(z, kAxisY.y, y * kAxisY.z);
}

// The flight's tangents (InitFlyToHeroCurve, inlined twice): the null vector becomes the x axis, then the vector is
// normalised (unless its length is 0; y first, fused), scaled by `length`, and its y set to `height`.
void TangentFrom(CVector3* v, float length, float height) {
    if (v->x == kNullVector.x && v->y == kNullVector.y && v->z == kNullVector.z) *v = kAxisX;
    const float n = std::sqrt(ppc::fmadds(v->z, v->z, ppc::fmadds(v->x, v->x, v->y * v->y)));
    if (n != 0.0f) {
        const float k = 1.0f / n;
        v->z = k * v->z;
        v->x = k * v->x;
        v->y = k * v->y;
    }
    v->z = length * v->z;
    v->x = length * v->x;
    v->y = length * v->y;
    v->y = height;
}

// A frame row normalised (y first, fused; kept when its length is 0) and scaled by `scale` (UpdateFlyToHero's shrink).
void ScaleRow(RwV3d* row, float scale) {
    float y = row->y;
    float x = row->x;
    float z = row->z;
    const float n = std::sqrt(ppc::fmadds(z, z, ppc::fmadds(x, x, y * y)));
    if (n != 0.0f) {
        const float k = 1.0f / n;
        z = z * k;
        x = x * k;
        y = y * k;
    }
    row->x = scale * x;
    row->y = scale * y;
    row->z = scale * z;
}

// An identity RwMatrix as the original builds it on the stack (flags 0x20003; the pads are not written).
void IdentityMatrix(CMatrix34* m) {
    m->m_right = {1.0f, 0.0f, 0.0f};
    m->m_ui32Flags = 0x20003u;
    m->m_up = {0.0f, 1.0f, 0.0f};
    m->m_at = {0.0f, 0.0f, 1.0f};
    m->m_pos = {0.0f, 0.0f, 0.0f};
}

}  // namespace

// 0x005b7470 CKHkS08Bonus_ReturnToPool_maybe (vt+0xc0)
void CKHkS08Bonus::ReturnToPool() {
    CSGLeaf* node = static_cast<CSGLeaf*>(m_pKGLObject);
    node->m_sgProperties = (node->m_sgProperties & 0xfffffffbu) | 4u;
    PoolOf(this)->ReleaseBonusFx(m_pUnk80);  // 0x005b1668
    PoolOf(this)->StopBonusTrail(m_unk24);   // 0x005b3e50
}

// 0x005b7890 CKHkS08Bonus_DisableAndReleaseFx_maybe (vt+0xd8; CKGrpBonusPool_ReleaseAllActive_maybe): hidden, its effect
// (+0x80) released by its pool (+0x28, 0x5b1668), then its trail stopped (0x5b3e50).
void CKHkS08Bonus::DisableAndReleaseFx() {
    CSGLeaf* node = static_cast<CSGLeaf*>(m_pKGLObject);
    node->m_sgProperties = node->m_sgProperties | 4u;
    PoolOf(this)->ReleaseBonusFx(m_pUnk80);  // 0x005b1668
    PoolOf(this)->StopBonusTrail(m_unk24);   // 0x005b3e50
}

// 0x005b76d0 CKHkS08Bonus_vfE4 (vt+0xe4)
void CKHkS08Bonus::VfE4(const CVector3* velocity, IKSerializable* hero) {
    m_unk44.x = velocity->x;
    m_unk44.z = velocity->z;
    m_unk44.y = velocity->y;
    m_unk3c = CpntOf(this)->m_unk24;
    Collect(hero, nullptr);  // vt+0xc8
    m_unk34 = 1;
}

// 0x005b7758 CKHkS08Bonus_SetLaunchVelocity_maybe (vt+0xe0)
void CKHkS08Bonus::SetLaunchVelocity(const CVector3* velocity, const CGroundContactDatasInOut* contact) {
    m_unk44.x = velocity->x;
    m_unk44.y = velocity->y;
    m_unk44.z = velocity->z;
    const float jitter = CpntOf(this)->m_unk30[0];  // +0x30
    const float k = ppc::fmadds(jitter, BONUS_RAND_SIGNED(), 1.0f);
    m_unk44.z = k * m_unk44.z;
    m_unk44.x = k * m_unk44.x;
    m_unk44.y = k * m_unk44.y;
    if (contact != nullptr) CopyGroundContact(m_GContactInOut, *contact);
}

// 0x005b78f8 CKHkS08Bonus_SetVisible (vt+0xd0)
void CKHkS08Bonus::SpawnAtBeacon(const uint16_t* accessor) {
    CKSrvBeacon* beacons = static_cast<CKSrvBeacon*>(g_pEngine->m_srvBeacon);
    // DOTD: a sector without klusters or an id without a set has no data; the original reads its three halfwords at
    // the low addresses (0, 2, 4). Here they read as 0.
    const int16_t* data = reinterpret_cast<const int16_t*>(beacons->GetBeaconData(accessor));
    const int16_t raw[3] = {data != nullptr ? data[0] : int16_t(0), data != nullptr ? data[1] : int16_t(0),
                            data != nullptr ? data[2] : int16_t(0)};
    const float tenth = 0.1f;  // TOC2 -0x6448
    CVector3 position;
    position.x = static_cast<float>(static_cast<double>(raw[0])) * tenth;
    position.y = static_cast<float>(static_cast<double>(raw[1])) * tenth;
    position.z = static_cast<float>(static_cast<double>(raw[2])) * tenth;
    SpawnAtPosition(&position);  // vt+0xd4
}

// 0x005b7f88 CKHkS08Bonus_SpawnAtPosition_maybe (vt+0xd4)
void CKHkS08Bonus::SpawnAtPosition(const CVector3* position) {
    m_unk40 = -1.0f;  // TOC2 -0x6468
    m_unk3c = 0.0f;
    const float r = BONUS_RAND_U16();
    const CKS08BonusCpnt* cpnt = CpntOf(this);
    m_unk50 = 0;
    m_unk38 = ppc::fmadds(r / kRand65535, cpnt->m_unk14[3] - cpnt->m_unk14[2], cpnt->m_unk14[2]);
    m_unk44 = kNullVector;
    m_pUnk30 = nullptr;
    CMatrix34 matrix;
    IdentityMatrix(&matrix);
    Mat4_RotateLocalZDeg(0.0f, &matrix);  // 0x002419c0
    Mat4_RotateLocalYDeg(0.0f, &matrix);  // 0x002413d0
    Mat4_RotateLocalXDeg(0.0f, &matrix);  // 0x00241118
    NodeOf(this)->SetLocalMatrix(reinterpret_cast<const RwMatrix*>(&matrix));  // 0x000d0be8
    PlaceFrame(this, *position);
    CSGLeaf* node = static_cast<CSGLeaf*>(m_pKGLObject);
    node->m_sgProperties &= 0xfffffffbu;
    m_pUnk80 = PoolOf(this)->AcquireBonusFx(m_pKGLObject);  // 0x005b3958
    RwFrame* frame = FrameOf(this);
    PoolOf(this)->ResetBonusTrail(m_unk24, AsVec(&frame->modelling.pos), AsVec(&frame->modelling.up));  // 0x005b3ea8
}

// 0x005b8178 CKHkS08Bonus_SpawnAt_maybe (vt+0xc4)
void CKHkS08Bonus::SpawnAt(float seekTime, const CVector3* position) {
    NodeOf(this)->SetIdentity();  // 0x000d08f0
    m_pUnk30 = nullptr;
    m_GContactInOut.m_i32FaceIndex = -1;
    m_GContactInOut.m_eContactStatus = 3;
    m_GContactInOut.m_ui8SectorNumber = 0;
    m_GContactInOut.m_pGround = nullptr;
    m_unk35 = 1;
    m_unk40 = seekTime;
    m_unk34 = 0;
    m_unk3c = 0.0f;
    const float r = BONUS_RAND_U16();
    const CKS08BonusCpnt* cpnt = CpntOf(this);
    m_unk50 = 0;
    m_unk38 = ppc::fmadds(r / kRand65535, cpnt->m_unk14[3] - cpnt->m_unk14[2], cpnt->m_unk14[2]);
    m_unk44 = kNullVector;
    if (CpntOf(this)->m_unk10 == 0) {
        const float rz = BONUS_RAND_U16();
        const float ry = BONUS_RAND_U16();
        const float rx = BONUS_RAND_U16();
        CMatrix34 matrix;
        IdentityMatrix(&matrix);
        Mat4_RotateLocalZDeg(rz / kRand65535 * 360.0f, &matrix);  // 0x002419c0 (TOC2 -0x6428: 360)
        Mat4_RotateLocalYDeg(ry / kRand65535 * 360.0f, &matrix);  // 0x002413d0
        Mat4_RotateLocalXDeg(rx / kRand65535 * 360.0f, &matrix);  // 0x00241118
        NodeOf(this)->SetLocalMatrix(reinterpret_cast<const RwMatrix*>(&matrix));  // 0x000d0be8
    }
    PlaceFrame(this, *position);
    CSGLeaf* node = static_cast<CSGLeaf*>(m_pKGLObject);
    node->m_sgProperties &= 0xfffffffbu;
    m_pUnk80 = PoolOf(this)->AcquireBonusFx(m_pKGLObject);  // 0x005b3958
    RwFrame* frame = FrameOf(this);
    PoolOf(this)->ResetBonusTrail(m_unk24, AsVec(&frame->modelling.pos), AsVec(&frame->modelling.up));  // 0x005b3ea8
}

// 0x005b8590 CKHkS08Bonus_InitFlyToHeroCurve_maybe
void CKHkS08Bonus::InitFlyToHeroCurve() {
    m_unkA0.x = BONUS_RAND_SIGNED();
    const float r = BONUS_RAND_SIGNED();
    m_unkA0.y = 0.0f;
    m_unkA0.z = r;
    TangentFrom(&m_unkA0, CpntOf(this)->m_unk54[2], CpntOf(this)->m_unk54[1]);  // +0x5c, +0x58
    const RwFrame* frame = FrameOf(this);
    m_unk88.x = frame->modelling.pos.x;
    m_unk88.z = frame->modelling.pos.z;
    m_unk88.y = frame->modelling.pos.y;
    if (CpntOf(this)->m_unk10 != 0) m_unk88.y = m_unk88.y + 2.0f;  // TOC2 -0x6420
    m_unk94.x = BONUS_RAND_SIGNED();
    const float s = BONUS_RAND_SIGNED();
    m_unk94.y = 0.0f;
    m_unk94.z = s;
    TangentFrom(&m_unk94, CpntOf(this)->m_unk54[3], CpntOf(this)->m_unk54[1]);  // +0x60, +0x58
}

// 0x005b8900 BonusGem_Collect (vt+0xc8)
void CKHkS08Bonus::Collect(IKSerializable* hero, const uint16_t* accessor) {
    // bge on the age (cror: equal counts), else a negative seek time (blt).
    if (!(m_unk3c >= CpntOf(this)->m_unk24) && !(m_unk40 < 0.0f)) return;
    m_pUnk30 = hero;
    if (accessor != nullptr) {
        m_unkB0[0] = accessor[0];
        m_unkB0[3] = accessor[3];
        m_unkB0[1] = accessor[1];
        m_unkB0[2] = accessor[2];
        CKSrvBeacon* beacons = static_cast<CKSrvBeacon*>(g_pEngine->m_srvBeacon);
        CKSrvBeacon::CKBeaconSector& sector = beacons->m_aBeaconSectors[accessor[0]];
        if (sector.m_apBeaconKlusters != nullptr) {
            // DOTD: an id without a set: the original reads the set's bit count and start at the low addresses; skipped.
            const CKSrvBeacon::CKBeaconSet* set = beacons->GetBeaconSet(accessor);
            if (set != nullptr) {
                const uint32_t n = static_cast<uint32_t>(set->m_aui16Accessor[3]) +
                                   static_cast<uint32_t>(set->m_ui8PersistentSizeBits) * accessor[3];
                uint8_t* bits = sector.m_bavPersistent.m_p8Bits;
                const uint8_t bit = static_cast<uint8_t>(1u << (n & 7));
                bits[n >> 3] = static_cast<uint8_t>(bits[n >> 3] & ~bit);
                bits[n >> 3] = static_cast<uint8_t>(bits[n >> 3] | bit);
            }
        }
    }
    const RwFrame* frame = FrameOf(this);
    const CVector3 at = {frame->ltm.pos.x, frame->ltm.pos.y, frame->ltm.pos.z};
    PoolOf(this)->TriggerCollectExplosion(&at);  // 0x005b3bc0
    m_unk84 = 0.0f;
    InitFlyToHeroCurve();
    if (hero->IsKindOfClass(0x25c2) == 0) return;  // vt+0x08
    CKS08GameManager* manager = static_cast<CKS08GameManager*>(g_pEngine->m_gameManager);
    if (static_cast<CKHkS08Hero*>(hero)->GetDragonIndex() != 0) {  // 0x00361960
        manager->RefreshDragonStatDisplays(1, 0, 0);  // 0x005022b0
        return;
    }
    manager->RefreshDragonStatDisplays(0, 0, 0);
}

// 0x005b7098 CKHkS08Bonus_SeekNearestHero_maybe
void CKHkS08Bonus::SeekNearestHero() {
    const uint32_t type = PoolOf(this)->m_ui32BonusType;
    if (type == 3 || type == 4 || type == 5) {
        IKSerializable* nearest = nullptr;
        float best = kFltMax;
        IKGrpHero* group = static_cast<IKGrpHero*>(g_pEngine->m_gameManager->m_unk04[1]);
        uint32_t i = group->m_ui8ControlledHeroCount;  // 0x002ca288 GetControlledHeroCount
        while (i != 0) {
            --i;
            IKSerializable* hero = group->m_apControlledHeroes[i];  // 0x002ca0e0 GetControlledHeroArray
            const float* p = static_cast<CKHkS08Hero*>(hero)->GetPositionPtr();  // 0x00361968
            const RwFrame* frame = FrameOf(this);
            float dy = p[1] - frame->ltm.pos.y;
            float dx = p[0] - frame->ltm.pos.x;
            float dz = p[2] - frame->ltm.pos.z;
            dy = dy * dy;
            const float d = ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy));
            if (best > d) {
                best = d;
                nearest = hero;
            }
        }
        if (nearest != nullptr) {
            m_unk3c = CpntOf(this)->m_unk24;
            Collect(nearest, nullptr);  // vt+0xc8
            return;
        }
    }
    ReturnToPool();  // vt+0xc0
}

// 0x005b9428 CKHkS08Bonus_ResolveBounceCollision_maybe
void CKHkS08Bonus::ResolveBounceCollision(CVector3* position) {
    CKSrvCollision* collision = static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision);
    const CKS08BonusCpnt* cpnt = CpntOf(this);
    const float zero = 0.0f;  // TOC2 -0x642c
    // The walls between the frame's position and the new one.
    {
        const RwFrame* frame = FrameOf(this);
        CLine line;
        line.m_start.x = frame->modelling.pos.x;
        line.m_start.z = frame->modelling.pos.z;
        line.m_start.y = frame->modelling.pos.y;
        line.m_VectDir.x = position->x - frame->modelling.pos.x;
        line.m_VectDir.y = position->y - frame->modelling.pos.y;
        line.m_VectDir.z = position->z - frame->modelling.pos.z;
        CGroundEdgeDatasOut edge;
        if (collision->RaycastWalls(&line, zero, &edge, 0, nullptr, 1) != 0) {  // 0x00198438
            // The wall's normal in the horizontal plane (the edge's direction turned), jittered by three draws.
            float ex = edge.m_Edge.m_VectDir.x;
            float ez = edge.m_Edge.m_VectDir.z;
            const float rest = 1.0f - edge.m_ftLine;
            const float n = std::sqrt(ppc::fmadds(ez, ez, ppc::fmadds(ex, ex, zero)));
            if (n != zero) {
                const float k = 1.0f / n;
                ez = ez * k;
                ex = ex * k;
            }
            float nz = -ex;
            const float jitter1 = cpnt->m_unk30[1];  // +0x34
            float nx = ppc::fmadds(BONUS_RAND_SIGNED(), jitter1, ez);
            float ny = ppc::fmadds(BONUS_RAND_SIGNED(), CpntOf(this)->m_unk30[1], zero);
            const float r3 = BONUS_RAND_SIGNED();
            nz = ppc::fmadds(r3, CpntOf(this)->m_unk30[1], nz);
            const float m = std::sqrt(ppc::fmadds(nz, nz, ppc::fmadds(nx, nx, ny * ny)));
            if (m != zero) {
                const float k = 1.0f / m;
                nz = nz * k;
                nx = nx * k;
                ny = ny * k;
            }
            // The rest of the move reflected off the wall (its y taken as 0), then the velocity.
            float d = ppc::fmadds(nx, rest * line.m_VectDir.x, ny * zero);
            d = ppc::fnmadds(nz, rest * line.m_VectDir.z, d);
            float e = ppc::fmadds(CpntOf(this)->m_unk14[1], d, d);  // +0x18
            position->x = ppc::fmadds(nx, e, position->x);
            position->y = ppc::fmadds(ny, e, position->y);
            position->z = ppc::fmadds(nz, e, position->z);
            float v = ny * m_unk44.y;
            v = ppc::fmadds(nx, m_unk44.x, v);
            v = ppc::fnmadds(nz, m_unk44.z, v);
            e = ppc::fmadds(CpntOf(this)->m_unk14[1], v, v);
            m_unk44.z = ppc::fmadds(nz, e, m_unk44.z);
            m_unk44.x = ppc::fmadds(nx, e, m_unk44.x);
            m_unk44.y = ppc::fmadds(ny, e, m_unk44.y);
        }
    }
    // The ground below the new position.
    // The fall this frame: below 0.01 (bge: not below) the reach is 0.01 down and 0.21 up (TOC2 -0x63e8 / -0x63e4); else
    // the fall down and the fall + 0.2 up (TOC2 -0x63e0: 0x5b9668 adds into f0, the object height, and joins after the
    // 0.21 load). The object height also widens ProbeGroundInSectorList's box test (inf.y - height), so a bonus falling
    // more than 0.21 in a frame still finds the ground it passed through (G +24597).
    float drop = FrameOf(this)->modelling.pos.y - position->y;
    float height;
    if (!(drop >= 0.01f)) {
        drop = 0.01f;
        height = 0.21f;
    } else {
        height = drop + 0.2f;
    }
    CGroundContactDatasIn in;
    in.m_fDeltaMax = drop;
    in.m_fObjectHeight = height;
    in.m_MasksOfGrdForTest[0] = 1;
    in.m_MasksOfGrdForTest[1] = 8;
    const float lift = 0.05f;  // TOC2 -0x641c
    const float probe[3] = {position->x, position->y - lift, position->z};
    collision->GroundProbePoints(&in, &m_GContactInOut, probe, 1);  // 0x00196540
    const int32_t status = static_cast<int32_t>(m_GContactInOut.m_eContactStatus);
    if (status < 1) return;
    if (status > 2) {
        if (status == 3) SeekNearestHero();
        return;
    }
    if ((static_cast<ICollisionMesh*>(m_GContactInOut.m_pGround)->m_ui16PropertiesFlags & 0x200u) != 0) SeekNearestHero();
    ++m_unk50;
    if (CpntOf(this)->m_unk2c > m_unk50) {
        // A bounce off the ground: its normal jittered by three draws.
        const float gx = m_GContactInOut.m_Normal.x;
        const float gz = m_GContactInOut.m_Normal.z;
        const float gy = m_GContactInOut.m_Normal.y;
        float nx = ppc::fmadds(BONUS_RAND_SIGNED(), CpntOf(this)->m_unk30[1], gx);
        float ny = ppc::fmadds(BONUS_RAND_SIGNED(), CpntOf(this)->m_unk30[1], gy);
        const float r3 = BONUS_RAND_SIGNED();
        float nz = ppc::fmadds(r3, CpntOf(this)->m_unk30[1], gz);
        const float m = std::sqrt(ppc::fmadds(nz, nz, ppc::fmadds(nx, nx, ny * ny)));
        if (m != zero) {
            const float k = 1.0f / m;
            nz = nz * k;
            nx = nx * k;
            ny = ny * k;
        }
        float v = ny * m_unk44.y;
        v = ppc::fmadds(m_unk44.x, nx, v);
        v = ppc::fnmadds(nz, m_unk44.z, v);
        float e = ppc::fmadds(CpntOf(this)->m_unk14[1], v, v);
        m_unk44.z = ppc::fmadds(e, nz, m_unk44.z);
        m_unk44.x = ppc::fmadds(e, nx, m_unk44.x);
        m_unk44.y = ppc::fmadds(e, ny, m_unk44.y);
        const float h = ny * m_GContactInOut.m_fdH;
        e = ppc::fmadds(CpntOf(this)->m_unk14[1], h, h);
        position->z = ppc::fmadds(e, nz, position->z);
        position->x = ppc::fmadds(e, nx, position->x);
        position->y = ppc::fmadds(e, ny, position->y);
        return;
    }
    // No bounce left: it rests on the ground.
    m_unk44 = kNullVector;
    const float px = m_GContactInOut.m_ProjectionOnGround.x;
    const float py = m_GContactInOut.m_ProjectionOnGround.y + lift;
    const float pz = m_GContactInOut.m_ProjectionOnGround.z;
    position->x = px;
    position->z = pz;
    position->y = py;
}

// 0x005b8cf8 CKHkS08Bonus_UpdateFlyToHero_maybe
void CKHkS08Bonus::UpdateFlyToHero(IKTime* frameClock) {
    const float dt = frameClock->m_afDeltaTime[0];
    const float t = m_unk84 + dt;
    m_unk84 = t;
    const float duration = CpntOf(this)->m_unk54[0];  // +0x54
    if (t >= duration) {
        PoolOf(this)->ApplyBonusToHero(m_pUnk30, this);  // vt+0x12c
        if (m_pUnk30->IsKindOfClass(0x25c2) != 0) {
            static_cast<CKHkS08Hero*>(m_pUnk30)->ShareCollectedBonusWithPartner(this);  // 0x0032afc8
        }
        const RwFrame* frame = FrameOf(this);
        const CVector3 at = {frame->ltm.pos.x, frame->ltm.pos.y, frame->ltm.pos.z};
        static_cast<CKGrpS08BonusPool*>(PoolOf(this))->PlayCollectFx(&at);  // 0x005af800
        if (m_unk35 != 0) ++PoolOf(this)->m_unk68;
        ReturnToPool();  // vt+0xc0
        return;
    }
    float s;
    if (CpntOf(this)->m_unk10 != 0) {
        s = t - (duration - 0.5f);  // TOC2 -0x63f4
        s = s + s;
        if (!(s > 0.0f)) s = 0.0f;  // ble
    } else {
        s = t / duration;
    }
    CVector3 target;
    if (m_pUnk30->IsKindOfClass(0x25c2) != 0) {
        CKHkS08Hero* hero = static_cast<CKHkS08Hero*>(m_pUnk30);
        hero->GetDragonIndex();  // 0x00361960 (the result is not used)
        static_cast<CSGHotSpot*>(hero->GetHotSpot(5))->GetWorldPosition(&target);  // 0x00361b70, 0x000ce790
    } else {
        const RwFrame* frame = static_cast<CSGMovable*>(static_cast<IKHook*>(m_pUnk30)->m_pKGLObject)->m_pRwFrame;
        target.z = frame->ltm.pos.z;
        target.x = frame->ltm.pos.x;
        target.y = frame->ltm.pos.y;
    }
    CVector3 p2;
    p2.x = target.x + m_unkA0.x;
    p2.y = target.y + m_unkA0.y;
    p2.z = target.z + m_unkA0.z;
    CVector3 p1;
    p1.x = m_unk88.x + m_unk94.x;
    p1.y = m_unk88.y + m_unk94.y;
    p1.z = m_unk88.z + m_unk94.z;
    CVector3 out;
    Vec3_CubicBezier(s, &out, &m_unk88, &p1, &p2, &target);  // 0x00010fc0
    PlaceFrame(this, out);
    CVector3 axis;
    if (CpntOf(this)->m_unk10 != 0) {
        axis = kAxisY;
    } else {
        SpinAxis(this, &axis);
    }
    NodeOf(this)->RotateInPlace(&axis.x, m_unk38 * kRadToDeg * dt);  // 0x000d11b0
    if (CpntOf(this)->m_unk10 != 0) return;
    // It shrinks as it arrives: each row normalised and scaled by 1 - s^2 (the flags' identity and orthogonal bits
    // cleared, 0xfffdfffc), the frame marked dirty after each.
    const float scale = 1.0f - s * s;
    RwFrame* frame = FrameOf(this);
    ScaleRow(&frame->modelling.right, scale);
    frame->modelling.flags &= 0xfffdfffcu;
    RwFrame_MarkDirty(FrameOf(this));
    frame = FrameOf(this);
    ScaleRow(&frame->modelling.up, scale);
    frame->modelling.flags &= 0xfffdfffcu;
    RwFrame_MarkDirty(FrameOf(this));
    frame = FrameOf(this);
    ScaleRow(&frame->modelling.at, scale);
    frame->modelling.flags &= 0xfffdfffcu;
    RwFrame_MarkDirty(FrameOf(this));
}

// 0x005b9c28 CKHkS08Bonus_Update (vt+0x7c)
void CKHkS08Bonus::Update(IKTime* frameClock) {
    const float age = frameClock->m_afDeltaTime[0] + m_unk3c;
    m_unk3c = age;
    if (m_pUnk30 != nullptr) {
        UpdateFlyToHero(frameClock);
    } else {
        // ble on the seek time, then bge (cror) on the age.
        if (m_unk40 > 0.0f && age >= m_unk40) {
            SeekNearestHero();
            return;
        }
        if (m_unk50 < CpntOf(this)->m_unk2c) {
            const float dt = frameClock->m_afDeltaTime[0];
            const float g = -CpntOf(this)->m_unk14[0] * dt;  // +0x14
            m_unk44.z = ppc::fmadds(g, kAxisY.z, m_unk44.z);
            m_unk44.x = ppc::fmadds(g, kAxisY.x, m_unk44.x);
            m_unk44.y = ppc::fmadds(g, kAxisY.y, m_unk44.y);
            const float step = frameClock->m_afDeltaTime[0];
            const RwFrame* frame = FrameOf(this);
            CVector3 next;
            next.x = ppc::fmadds(step, m_unk44.x, frame->modelling.pos.x);
            next.z = ppc::fmadds(step, m_unk44.z, frame->modelling.pos.z);
            next.y = ppc::fmadds(step, m_unk44.y, frame->modelling.pos.y);
            ResolveBounceCollision(&next);
            PlaceFrame(this, next);
            CVector3 axis;
            if (CpntOf(this)->m_unk10 != 0) {
                axis = kAxisY;
            } else {
                SpinAxis(this, &axis);
            }
            NodeOf(this)->RotateInPlace(&axis.x, m_unk38 * kRadToDeg * frameClock->m_afDeltaTime[0]);  // 0x000d11b0
        }
    }
    RwFrame* frame = FrameOf(this);
    PoolOf(this)->SetBonusTrailEndpoints(m_unk24, AsVec(&frame->modelling.pos), AsVec(&frame->modelling.up));  // 0x005b1508
}

// 0x005b7bf0 CKHkS08Bonus_Load
int32_t CKHkS08Bonus::Load(IKFile* file, int32_t type) {
    IKHook::Load(file, type);  // through TocBridge_CKHook_Load
    if (type != K_LEVEL_PLATEFORMS) return 1;
    IKFile_ReadRef(file, &m_pUnk20);
    IKFile_ReadRef(file, &m_pUnk28);
    IKFile_ReadRef(file, &m_pUnk2C);
    return 1;
}

// 0x005b7b60 CKHkS08Bonus_LevelReset (vt+0x24)
void CKHkS08Bonus::RecursiveRegistration(int32_t type) {
    if (static_cast<uint32_t>(type - 4) > 3u) g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);
    IKHook::RecursiveRegistration(type);  // 0x00019ab8
}
