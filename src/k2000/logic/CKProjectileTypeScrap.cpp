// CKProjectileTypeScrap.cpp - reconstructed original translation unit 0x5929d8-0x596240 (GAME_TOC2, main_toc2), 26 functions, 26 live.
// Primary class: CKProjectileTypeScrap  key 0x134c  category Logic  size 0x30  vtable 0xb2e3c8
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x5929d8  RegisterCKProjectileTypeScrapClass
//   [ ] 0x592a50  _GLOBAL__I_592a50
//   [x] 0x592a60  CKProjectileTypeScrap_PlayInstanceSound_maybe
//   [x] 0x592b08  CKProjectileTypeScrap_UpdateRollAxis_maybe
//   [x] 0x592c20  CKProjectileTypeScrap_ProbeGround_maybe
//   [x] 0x592cc0  CKProjectileTypeScrap_CollideAndStop_maybe
//   [x] 0x592fd0  CKProjectileTypeScrap_DeleteArray
//   [x] 0x593078  CKProjectileTypeScrap_Create
//   [x] 0x5930d0  CKProjectileTypeScrap_IsDead
//   [x] 0x593120  CKProjectileTypeScrap_UpdateMotion
//   [x] 0x593258  CKProjectileTypeScrap_KillInstance
//   [x] 0x593708  CKProjectileTypeScrap_CreateArray
//   [x] 0x5937c8  CKProjectileTypeScrap_OnDeath
//   [x] 0x593c78  CKProjectileTypeScrap_UpdateOrientation
//   [x] 0x5941a0  CKProjectileTypeScrap_TriggerImpactExplosion_maybe
//   [x] 0x5944d8  CKProjectileTypeScrap_CollideAndBounce_maybe
//   [x] 0x5947e0  CKProjectileTypeScrap_UpdateCollision
//   [x] 0x594928  CKProjectileTypeScrap_LaunchPiece
//   [x] 0x595a80  CKProjectileTypeScrap_LaunchEx
//   [x] 0x595b60  CKProjectileTypeScrap_Launch
//   [x] 0x595be0  CKProjectileTypeScrap_Destroy
//   [x] 0x595c08  CKProjectileTypeScrap_MessageProc
//   [ ] 0x595da0  CKProjectileTypeScrap_Save
//   [x] 0x595da8  CKProjectileTypeScrap_PostLoad
//   [x] 0x595db0  CKProjectileTypeScrap_RecursiveRegistration
//   [x] 0x595e28  CKProjectileTypeScrap_Load
//
//   [ ] 0x9cb608  CKProjectileTypeScrap_IsKindOfClass  [inline]
//   [ ] 0x9cb630  CKProjectileTypeScrap_GetClassType  [inline]
//   [ ] 0x9cb638  CKProjectileTypeScrap_GetClassID  [inline]
//   [x] 0x9cb640  CKProjectileTypeScrap_ProcessDamageContacts  [inline]
//   [ ] 0x9cb648  CKProjectileTypeScrap_Destructor  [inline]
//   [ ] 0x9cb668  CKProjectileTypeScrap_DeletingDestructor  [inline]
#include "k2000/logic/CKProjectileTypeScrap.h"

#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"
#include "k2000/scenegraph/CSGLeaf.h"

#include <cmath>
#include <cstring>

#include "Renderware/rwcore/RwCamera.h"
#include "Renderware/rwcore/RwFrameList.h"
#include "Renderware/rwcore/RwMatrix.h"
#include "crt/ppc_ops.h"
#include "k2000/core/Stub.h"
#include "k2000/logic/fx/CKExplosionNodeFx.h"
#include "k2000/scenegraph/IKBoundingVolume.h"
#include "k2000/dictionaries/CKSoundDictionaryID.h"
#include "k2000/fx/IKFx.h"
#include "k2000/geometry/CGeometry.h"
#include "k2000/logic/CKParticlesEffectFxData.h"
#include "k2000/logic/CKProjectileDataTypeScrap.h"
#include "k2000/logic/IKFxData.h"
#include "k2000/logic/render/CMaterial.h"
#include "k2000/logic/sound/CKSound.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/CKDynamicBoundingSphere.h"
#include "k2000/scenegraph/CNode.h"
#include "k2000/scenegraph/CSGBranch.h"
#include "k2000/services/CKSrvCollision.h"
#include "k2000/services/CKSrvFx.h"
#include "k2000/system/CTimeManager.h"
#include "k2000/system/IKTime.h"

namespace {
// The shared constants (zero in the EBOOT's BSS, filled by static initialisers).
const CVector3 kAxisX = {1.0f, 0.0f, 0.0f};       // 0x00c50d34
const CVector3 kAxisY = {0.0f, 1.0f, 0.0f};       // 0x00c50d40
const CVector3 kAxisZ = {0.0f, 0.0f, 1.0f};       // 0x00c50d4c
const CVector3 kNullVector = {0.0f, 0.0f, 0.0f};  // 0x00c50d64
}  // namespace

// 0x00595e28 CKProjectileTypeScrap_Load: IKProjectileType's data, then (level data only) a word, per
// projectile two references, and two references (9 + 8 * count + 8 bytes).
int32_t CKProjectileTypeScrap::Load(IKFile* file, int32_t type) {
    IKProjectileType::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadU32LE(file, &m_unk24);
    m_GrdContDatasIn.m_fDeltaMax = 1.0f;      // TOC1 -0x6ea4
    m_GrdContDatasIn.m_fObjectHeight = 2.0f;  // TOC1 -0x6ea0
    const uint32_t count = m_ui8MaxProjectiles;
    // PS3: count << 2 and (count * PS3 record size) masked to 16 bits (rlwinm 0,16,27); a byte count never
    // reaches the mask, so native sizes are used.
    Projectile** list = static_cast<Projectile**>(Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(Projectile*))));
    Projectile* projectiles = static_cast<Projectile*>(Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(Projectile))));
    m_aProjectiles = projectiles;
    m_apProjectileList = reinterpret_cast<void**>(list);
    for (uint32_t i = 0; i < m_ui8MaxProjectiles; ++i) {
        Projectile* p = &projectiles[i];
        list[i] = p;
        IKFile_ReadRef(file, &p->m_pNode);
        IKFile_ReadRef(file, &p->m_pBody);
        p->m_pVolume = nullptr;
        p->m_pOwner = nullptr;
        // BUG(original): no null test (unlike CKProjectileTypeBallisticPFX_Load): a null node reference
        // writes through address 0x10. Every LVL010 sample has a node.
        p->m_pNode->m_sgProperties = (p->m_pNode->m_sgProperties & ~0x4u) | 0x4u;
        p->m_vPos = kNullVector;       // 0x00c50d64
        p->m_vPrevPos = kNullVector;   // 0x00c50d64
        p->m_vVelocity = kAxisZ;       // 0x00c50d4c
        p->m_fSpeed = 0.0f;
        p->m_vRollAxis = kAxisX;       // 0x00c50d34
        p->m_GrdContDatasInOut.m_i32FaceIndex = -1;
        p->m_GrdContDatasInOut.m_eContactStatus = 3;
        p->m_GrdContDatasInOut.m_pGround = nullptr;
        p->m_GrdContDatasInOut.m_ui8SectorNumber = 0;
        p->m_ui32Index = i;
        p->m_flags58 = 0;
        p->m_fRollSpeed = 0.0f;
        p->m_fScale = 1.0f;
        p->m_pFx = nullptr;
        p->m_fAge = 0.0f;
        p->m_fLifetime = 1.0f;
    }
    IKFile_ReadRef(file, &m_unk28);
    IKFile_ReadRef(file, &m_unk2c);
    return 1;
}

namespace {
using Projectile = CKProjectileTypeScrap::Projectile;

Projectile* ProjectileAt(const CKProjectileTypeScrap* pool, uint32_t index) {
    return reinterpret_cast<Projectile**>(pool->m_apProjectileList)[index];
}
CKProjectileDataTypeScrap* DataOf(const Projectile* projectile) {
    return static_cast<CKProjectileDataTypeScrap*>(projectile->m_pData);
}
RwFrame* FrameOf(CSGLeaf* node) { return node->m_pRwFrame; }
CKSrvCollision* Collision() { return static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision); }

// 0x00010690 Math_Sqrtf (fsqrts).
inline float MathSqrtf(float x) { return std::sqrt(x); }

// 0x000d08f0 CSGMovable_SetIdentity: RwFrameSetIdentity (RW frame.c: the identity modelling matrix, the frame updated).
void SetIdentity(CSGLeaf* node) {
    RwFrame* frame = FrameOf(node);
    RwMatrixSetIdentity(&frame->modelling);
    RwFrameUpdateObjects(frame);
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
    m.at.y = scale * m.at.y;
    m.at.z = scale * m.at.z;
    m.flags &= 0xfffdfffeu;
    RwFrame_MarkDirty(frame);  // 0x00010698
}

// The frame's position set (the identity flag cleared), the frame marked dirty.
void SetFramePosition(RwFrame* frame, const CVector3& pos) {
    frame->modelling.pos.x = pos.x;
    frame->modelling.pos.y = pos.y;
    frame->modelling.pos.z = pos.z;
    frame->modelling.flags &= 0xfffdffffu;
    RwFrame_MarkDirty(frame);  // 0x00010698
}

// The roll axis inlined in LaunchPiece / UpdateOrientation (and CKProjectileTypeScrap_UpdateRollAxis_maybe 0x592b08): the
// horizontal velocity (vx, 0, vz) normalised, crossed with the Y axis; the frame's right axis when it is 0.
void ComputeRollAxis(Projectile* p, float vx, float vz) {
    const float zero = 0.0f;
    const float length = MathSqrtf(ppc::fmadds(vz, vz, ppc::fmadds(vx, vx, zero)));
    if (length == zero) {
        const RwV3d& right = FrameOf(p->m_pNode)->modelling.right;
        p->m_vRollAxis.x = right.x;
        p->m_vRollAxis.y = right.y;
        p->m_vRollAxis.z = right.z;
        return;
    }
    const float inv = 1.0f / length;
    const float y = inv * zero;
    const float z = vz * inv;
    const float x = vx * inv;
    p->m_vRollAxis.x = ppc::fmsubs(z, kAxisY.y, y * kAxisY.z);
    p->m_vRollAxis.y = ppc::fmsubs(x, kAxisY.z, z * kAxisY.x);
    p->m_vRollAxis.z = ppc::fmsubs(y, kAxisY.x, x * kAxisY.y);
}

// The inlined effect lookup of OnDeath / TriggerImpactExplosion / LaunchPiece (the reserving lookup 0x9c6468, reduced):
// the FX service's nodes of `data`'s node class and type; the first one loaded (flag bit 0) and not reserved (bit 1)
// gets the data, is reserved, owned by `owner` and started. Null when none is free.
IKFx* AcquireFx(IKFxData* data, IKSerializable* owner) {
    return static_cast<CKSrvFx*>(g_pEngine->m_srvFx)->AcquireFx(data, owner);
}

// The explosion node set up (as TriggerImpactExplosion 0x5941a0 / OnDeath inline it, through the TOC bridges): with a
// collision sphere (+0x8c), its owner (+0x24) as the damage owner, the data's category (+0x34) and flags (+0x36), the
// sphere's damage (+0x1c); then the position (+0x14) and the trigger (the caller, launch 0).
void TriggerExplosion(IKFx* node, Projectile* p, IKSerializable* caller) {
    CKExplosionNodeFx* explosion = static_cast<CKExplosionNodeFx*>(node);
    if (p->m_pVolume != nullptr) {
        IKBoundingVolume* volume = static_cast<IKBoundingVolume*>(p->m_pVolume);
        explosion->SetDamageOwner(volume->m_pOwner, caller);         // 0x001b6340
        explosion->SetDamageCategory(DataOf(p)->m_unk34, caller);    // 0x001b6318
        explosion->SetDamageFlags(DataOf(p)->m_unk36, caller);       // 0x001b62f0
        explosion->SetDamage(static_cast<IKBoundingVolume*>(p->m_pVolume)->m_unk1c, caller);  // 0x001b62c8
    }
    explosion->SetTranslation(&p->m_vPos, caller);  // 0x001b66e8
    explosion->Trigger(caller, 0);                  // 0x001b82a8
}

// The death / impact explosion: AcquireFx with the data's explosion FX data, then (the fx family's) setters and trigger,
// then the node's vt+0x54 (CKNodeFx3d_ReleaseReservation).
void SpawnExplosion(IKFxData* data, Projectile* p, IKSerializable* owner) {
    IKFx* node = AcquireFx(data, owner);
    if (node == nullptr) return;
    TriggerExplosion(node, p, owner);
    node->ReleaseReservation(owner);  // vt+0x54
}

// The geometries' alpha (CGeometry colour byte +0x23) and their "alpha blended" property bit 11 (vt+0x60 UpdateProperties
// when it changes). A geometry with property bit 12 and a material of mode 1..6 keeps 0xff and bit 11 cleared.
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

// The ground-contact parameters the pool shares (m_GrdContDatasIn): the probe depth and object height from the data's
// ground offset (+0x14).
void ResetGroundParams(CKProjectileTypeScrap* pool, const CKProjectileDataTypeScrap* data) {
    pool->m_GrdContDatasIn.m_fDeltaMax = data->m_unk14;
    pool->m_GrdContDatasIn.m_fObjectHeight = data->m_unk14 + data->m_unk14;
}

// GroundProbePoints_maybe 0x196540 with the pool's parameters and the projectile's contact, one point.
void Probe(CKProjectileTypeScrap* pool, Projectile* p, const CVector3& point) {
    const float points[3] = {point.x, point.y, point.z};
    Collision()->GroundProbePoints(reinterpret_cast<const CGroundContactDatasIn*>(&pool->m_GrdContDatasIn),
                                   reinterpret_cast<CGroundContactDatasInOut*>(&p->m_GrdContDatasInOut), points, 1);
}
}  // namespace

// 0x00592a60 CKProjectileTypeScrap_PlayInstanceSound_maybe
void CKProjectileTypeScrap::PlayInstanceSound(uint8_t index) {
    Projectile* p = ProjectileAt(this, index);
    CKSound* sound = static_cast<CKSoundDictionaryID*>(m_unk2c)->GetSound(p->m_ui32Index);  // 0x00112bc0
    if (sound != nullptr) {
        sound->SetAttachObject(p->m_pNode);  // 0x00111350
        sound->Play(0.0f);                   // 0x00111230
    }
    p->m_flags58 = static_cast<uint8_t>((p->m_flags58 & 0xfbu) | 4u);
}

// 0x00592b08 CKProjectileTypeScrap_UpdateRollAxis_maybe
void CKProjectileTypeScrap::UpdateRollAxis(Projectile* p) { ComputeRollAxis(p, p->m_vVelocity.x, p->m_vVelocity.z); }

// 0x00592c20 CKProjectileTypeScrap_ProbeGround_maybe: the point is the position less the data's ground offset (+0x14).
void CKProjectileTypeScrap::ProbeGround(Projectile* p) {
    const CVector3 point = {p->m_vPos.x, p->m_vPos.y - DataOf(p)->m_unk14, p->m_vPos.z};
    Probe(this, p, point);
    if (static_cast<uint32_t>(p->m_GrdContDatasInOut.m_eContactStatus) - 1u <= 2u) {
        p->m_flags58 = static_cast<uint8_t>(p->m_flags58 & 0xfeu);
    }
}

// 0x00592cc0 CKProjectileTypeScrap_CollideAndStop_maybe. Falling (the previous height above the current one) deepens the
// probe by the fall. Status 1 (on a ground): put on it (raised by the offset), stopped, landed (bit 3). Status 2 / 3:
// stopped; with data flag 0x800 it only stops dying, else it lands where the motion crosses a wall (RaycastWalls). A
// landing with a volume (no data flag 0x1000) switches the volume's bit 2 off and sends 0x2801 to its owner.
void CKProjectileTypeScrap::CollideAndStop(Projectile* p) {
    CKProjectileDataTypeScrap* data = DataOf(p);
    const float fall = p->m_vPrevPos.y - p->m_vPos.y;
    const CVector3 point = {p->m_vPos.x, p->m_vPos.y - data->m_unk14, p->m_vPos.z};
    if (fall > 0.0f) {
        m_GrdContDatasIn.m_fDeltaMax = fall + data->m_unk14;
        m_GrdContDatasIn.m_fObjectHeight = fall + (data->m_unk14 + data->m_unk14);
    }
    Probe(this, p, point);
    if ((p->m_flags58 & 8u) == 0) {
        bool landed = false;
        const int32_t status = static_cast<int32_t>(p->m_GrdContDatasInOut.m_eContactStatus);
        if (status == 1) {
            p->m_vPos = p->m_GrdContDatasInOut.m_ProjectionOnGround;
            p->m_fSpeed = 0.0f;
            p->m_vPos.y = p->m_vPos.y + DataOf(p)->m_unk14;
            p->m_flags58 = static_cast<uint8_t>((p->m_flags58 & 0xf7u) | 8u);
            landed = true;
        } else if (status >= 1 && status <= 3) {
            p->m_fSpeed = 0.0f;
            if ((DataOf(p)->m_unk38 & 0x800u) != 0) {
                p->m_flags58 = static_cast<uint8_t>(p->m_flags58 & 0xfeu);
            } else {
                p->m_flags58 = static_cast<uint8_t>((p->m_flags58 & 0xf7u) | 8u);
                CLine line;
                line.m_start = p->m_vPrevPos;
                line.m_VectDir.x = p->m_vPos.x - p->m_vPrevPos.x;
                line.m_VectDir.y = p->m_vPos.y - p->m_vPrevPos.y;
                line.m_VectDir.z = p->m_vPos.z - p->m_vPrevPos.z;
                CGroundEdgeDatasOut out;
                if (Collision()->RaycastWalls(&line, 0.0f, &out, 0, nullptr, 1) != 0) {  // 0x00198438
                    const float t = out.m_ftLine;
                    p->m_vPos.z = ppc::fmadds(t, line.m_VectDir.z, p->m_vPrevPos.z);
                    p->m_vPos.x = ppc::fmadds(t, line.m_VectDir.x, p->m_vPrevPos.x);
                    p->m_vPos.y = ppc::fmadds(t, line.m_VectDir.y, p->m_vPrevPos.y);
                }
                landed = true;
            }
        }
        if (landed && (DataOf(p)->m_unk38 & 0x1000u) == 0 && p->m_pVolume != nullptr) {
            IKBoundingVolume* volume = static_cast<IKBoundingVolume*>(p->m_pVolume);
            volume->m_ba8Infos = static_cast<uint8_t>(volume->m_ba8Infos & 0xfbu);
            if (volume->m_pOwner != nullptr) volume->m_pOwner->MessageProc(0x2801, &p->m_vPos);  // vt+0x1c
        }
    }
    ResetGroundParams(this, DataOf(p));
}

// 0x005941a0 CKProjectileTypeScrap_TriggerImpactExplosion_maybe: the data's impact FX data (+0x40).
void CKProjectileTypeScrap::TriggerImpactExplosion(Projectile* p) {
    SpawnExplosion(static_cast<IKFxData*>(DataOf(p)->m_unk40), p, this);
}

// 0x005944d8 CKProjectileTypeScrap_CollideAndBounce_maybe. Status 1: pushed out along the ground normal by the depth
// (times 1 + the restitution +0x08), the velocity reflected the same way, the speed cut by the impact, 0x2800 to the
// volume's owner. Status 2 / 3: the horizontal velocity reversed and scaled by the restitution; it stops dying when it
// was already against a wall, else goes back to its node's position. Then the impact explosion (data flag 0x4000).
void CKProjectileTypeScrap::CollideAndBounce(Projectile* p) {
    CKProjectileDataTypeScrap* data = DataOf(p);
    const uint32_t before = p->m_GrdContDatasInOut.m_eContactStatus;
    const CVector3 point = {p->m_vPos.x, p->m_vPos.y - data->m_unk14, p->m_vPos.z};
    Probe(this, p, point);
    const int32_t status = static_cast<int32_t>(p->m_GrdContDatasInOut.m_eContactStatus);
    if (status == 1) {
        const CVector3 n = p->m_GrdContDatasInOut.m_Normal;
        const float zero = 0.0f;
        const float one = 1.0f;
        const float depth = ppc::fmadds(n.z, zero, ppc::fmadds(n.x, zero, n.y * p->m_GrdContDatasInOut.m_fdH));
        const float k = DataOf(p)->m_unk08 + one;
        p->m_vPos.x = ppc::fmadds(n.x * depth, k, p->m_vPos.x);
        p->m_vPos.y = ppc::fmadds(k, n.y * depth, p->m_vPos.y);
        p->m_vPos.z = ppc::fmadds(k, n.z * depth, p->m_vPos.z);
        const CVector3 v = p->m_vVelocity;
        const float k2 = DataOf(p)->m_unk08 + one;
        const float dot = ppc::fmadds(n.z, v.z, ppc::fmadds(n.x, v.x, n.y * v.y));
        p->m_vVelocity.x = v.x - (n.x * dot) * k2;
        p->m_vVelocity.y = v.y - k2 * (n.y * dot);
        p->m_vVelocity.z = v.z - k2 * (n.z * dot);
        const float impact = std::fabs(dot);
        p->m_fSpeed = p->m_fSpeed - (p->m_fSpeed * impact) * (one - DataOf(p)->m_unk08);
        if ((DataOf(p)->m_unk38 & 0x1000u) == 0 && p->m_pVolume != nullptr) {
            IKSerializable* owner = static_cast<IKBoundingVolume*>(p->m_pVolume)->m_pOwner;
            if (owner != nullptr) owner->MessageProc(0x2800, &p->m_vPos);  // vt+0x1c
        }
        if ((DataOf(p)->m_unk38 & 0x4000u) != 0) TriggerImpactExplosion(p);
    } else if (status >= 1 && status <= 3) {
        p->m_vVelocity.x = -(p->m_vVelocity.x * DataOf(p)->m_unk08);
        p->m_vVelocity.z = -(p->m_vVelocity.z * DataOf(p)->m_unk08);
        if (before - 2u <= 1u) {
            p->m_flags58 = static_cast<uint8_t>(p->m_flags58 & 0xfeu);
        } else {
            const RwV3d& pos = FrameOf(p->m_pNode)->modelling.pos;
            p->m_vPos.x = pos.x;
            p->m_vPos.z = pos.z;
            p->m_vPos.y = pos.y;
        }
        if ((DataOf(p)->m_unk38 & 0x4000u) != 0) TriggerImpactExplosion(p);
    }
    ResetGroundParams(this, DataOf(p));
}

// 0x005930d0 CKProjectileTypeScrap_IsDead: one without the limit (bit 0) is dead; else when its age passed its lifetime.
uint8_t CKProjectileTypeScrap::IsDead(uint8_t index) {
    const Projectile* p = ProjectileAt(this, index);
    if ((p->m_flags58 & 1u) == 0) return 1;
    return (p->m_fAge <= p->m_fLifetime) ? 0 : 1;
}

// 0x00593120 CKProjectileTypeScrap_UpdateMotion: unless driven by its body (bit 1) or landed (bit 3): the previous
// position kept, gravity (+0x04) and the drag (+0x20, percent per second) on the velocity, the position moved, the roll
// speed from the data (+0x10, data flag 0x2). The age advances in every case.
void CKProjectileTypeScrap::UpdateMotion(uint8_t index, float dt) {
    Projectile* p = ProjectileAt(this, index);
    if (((p->m_flags58 >> 1) & 1u) == 0 && ((p->m_flags58 >> 3) & 1u) == 0) {
        p->m_vPrevPos = p->m_vPos;
        CKProjectileDataTypeScrap* data = DataOf(p);
        float vy = p->m_vVelocity.y - dt * data->m_unk04;
        p->m_vVelocity.y = vy;
        float vx;
        float vz;
        if (data->m_unk20 != 0.0f) {
            const float drag = dt * (data->m_unk20 * 1.0e-2f);  // 0x3c23d70a
            vz = p->m_vVelocity.z - drag * p->m_vVelocity.z;
            vx = p->m_vVelocity.x - drag * p->m_vVelocity.x;
            vy = vy - drag * vy;
            p->m_vVelocity.z = vz;
            p->m_vVelocity.x = vx;
            p->m_vVelocity.y = vy;
        } else {
            vx = p->m_vVelocity.x;
            vz = p->m_vVelocity.z;
        }
        p->m_vPos.y = ppc::fmadds(dt, vy, p->m_vPos.y);
        p->m_vPos.z = ppc::fmadds(dt, vz, p->m_vPos.z);
        p->m_vPos.x = ppc::fmadds(dt, vx, p->m_vPos.x);
        if ((DataOf(p)->m_unk38 & 2u) != 0 && ((p->m_flags58 >> 3) & 1u) == 0) {
            p->m_fRollSpeed = dt * DataOf(p)->m_unk10;
        }
    }
    p->m_fAge = p->m_fAge + dt;
}

// 0x00593258 CKProjectileTypeScrap_KillInstance: hidden, flags cleared; (pool option 0x100) its body parked; the last
// active projectile takes its place; (option 0x200) its sound stopped and detached; 0x2802 to its owner with its
// position; its volume taken off the node and released.
void CKProjectileTypeScrap::KillProjectile(uint8_t index) {
    Projectile* p = ProjectileAt(this, index);
    p->m_flags58 = 0;
    p->m_pNode->m_sgProperties = (p->m_pNode->m_sgProperties & 0xfffffffbu) | 4u;
    if ((m_baOptions & 0x100u) != 0) {
        // STUB(C2.8+, physics): the body (+0x10) put to sleep and parked in the physics service's container +0x3c
        // (message 0x2c02 to its owner), then its flag 0x20 (CKPxBody, not ported; no LVL010 pool has option 0x100).
        DOTD_STUB_ONCE("CKProjectileTypeScrap_KillInstance: the projectile's CKPxBody (physics)");
    }
    const uint8_t last = static_cast<uint8_t>(m_ui8NbOfActiveProjectiles - 1);
    m_ui8NbOfActiveProjectiles = last;
    if (index != last) {
        Projectile** list = reinterpret_cast<Projectile**>(m_apProjectileList);
        list[index] = list[last];
        list[m_ui8NbOfActiveProjectiles] = p;
    }
    if ((m_baOptions & 0x200u) != 0) {
        CKSound* sound = static_cast<CKSoundDictionaryID*>(m_unk2c)->GetSound(p->m_ui32Index);  // 0x00112bc0
        if (sound != nullptr) {
            sound->Stop(0);                   // 0x001111b0
            sound->SetAttachObject(nullptr);  // 0x00111350
        }
    }
    if (p->m_pOwner != nullptr) p->m_pOwner->MessageProc(0x2802, &p->m_vPos);  // vt+0x1c
    if (p->m_pVolume != nullptr) {
        CSGLeaf* volume = static_cast<CSGLeaf*>(p->m_pVolume);
        if (volume->m_pParent != nullptr) volume->m_pParent->RemoveChild(volume);       // vt+0x78
        Collision()->ReleaseDynSphere(static_cast<IKBoundingVolume*>(p->m_pVolume));  // 0x00191a38
        p->m_pVolume = nullptr;
    }
}

// 0x005937c8 CKProjectileTypeScrap_OnDeath: (pool option 0x4) an emission point at its position on the particle node
// +0x28; (data flag 0x8) its particle effect stopped and released; (data flag 0x2000) the death explosion (+0x3c); then
// KillProjectile (vt+0x60).
void CKProjectileTypeScrap::OnDeath(uint8_t index) {
    Projectile* p = ProjectileAt(this, index);
    if ((m_baOptions & 4u) != 0) {
        // STUB(C2.8): an emission point at the position on the particle node +0x28 (at most 0x40; flags 0x2000, 0x200,
        // 0x400) (no LVL010 pool has option 0x4; +0x28 is null in all of them).
        DOTD_STUB_ONCE("CKProjectileTypeScrap_OnDeath: pool option 0x4 (emission point on +0x28)");
    }
    if ((DataOf(p)->m_unk38 & 8u) != 0 && p->m_pFx != nullptr) {
        StopOwnedParticleEffect(static_cast<IKFx*>(p->m_pFx), this);  // 0x001cdde8
        static_cast<IKFx*>(p->m_pFx)->ReleaseReservation(this);        // vt+0x54
        p->m_pFx = nullptr;
    }
    if ((DataOf(p)->m_unk38 & 0x2000u) != 0) {
        SpawnExplosion(static_cast<IKFxData*>(DataOf(p)->m_unk3c), p, this);
    }
    KillProjectile(index);  // vt+0x60
}

// 0x00593c78 CKProjectileTypeScrap_UpdateOrientation. Unless driven by its body: (data flag 0x10) shrinking with its age
// (the scale ratio (1 - 0.99 age / life) / (1 - 0.99 (age - dt) / life), dt the frame clock's); the node moved to the
// position; rolling (data flag 0x2, not landed) about the roll axis from the horizontal velocity, else no roll axis.
// Then (data flag 0x40) the fade over the last +0x1c seconds of its life (the geometries' alpha).
void CKProjectileTypeScrap::UpdateOrientation(uint8_t index, float /*dt*/) {
    Projectile* p = ProjectileAt(this, index);
    if ((p->m_flags58 & 2u) == 0) {
        if ((DataOf(p)->m_unk38 & 0x10u) != 0) {
            const float neg = -0.99000001f;  // 0xbf7d70a4
            const float one = 1.0f;
            const float frameDt = g_pEngine->m_timeManager->m_pTime->m_afDeltaTime[IKTime::SCALABLE_GAME_TIME];
            const float now = ppc::fmadds(p->m_fAge / p->m_fLifetime, neg, one);
            const float before = ppc::fmadds((p->m_fAge - frameDt) / p->m_fLifetime, neg, one);
            ScaleAxes(p->m_pNode, now / before);
        }
        if ((DataOf(p)->m_unk38 & 2u) != 0 && ((p->m_flags58 >> 3) & 1u) == 0) {
            SetFramePosition(FrameOf(p->m_pNode), p->m_vPos);
            const CVector3 v = p->m_vVelocity;
            if (v.x == kNullVector.x && v.y == kNullVector.y && v.z == kNullVector.z) {
                p->m_vRollAxis = kNullVector;
            } else {
                ComputeRollAxis(p, v.x, v.z);
                static_cast<CSGMovable*>(p->m_pNode)->RotateInPlace(&p->m_vRollAxis.x,
                                                                    p->m_fRollSpeed * 57.2957802f);  // 0x000d11b0
            }
        } else {
            SetFramePosition(FrameOf(p->m_pNode), p->m_vPos);
            p->m_vRollAxis = kNullVector;
        }
    }
    CKProjectileDataTypeScrap* data = DataOf(p);
    if ((data->m_unk38 & 0x40u) != 0) {
        const float fade = data->m_unk1c;
        if (!(p->m_fLifetime - fade >= p->m_fAge)) {
            const uint8_t alpha = static_cast<uint8_t>(ppc::fctiwz(((p->m_fLifetime - p->m_fAge) / fade) * 255.0f));
            SetGeometriesAlpha(p->m_pNode, alpha);
        }
    }
}

// 0x005947e0 CKProjectileTypeScrap_UpdateCollision: with data flag 0x80 and not driven by its body: bounce (0x1), stop
// (0x400) or only the ground probe.
void CKProjectileTypeScrap::UpdateCollision(uint8_t index, float /*dt*/) {
    Projectile* p = ProjectileAt(this, index);
    ResetGroundParams(this, DataOf(p));
    if ((p->m_flags58 & 2u) != 0) return;
    const uint32_t flags = DataOf(p)->m_unk38;
    if ((flags & 0x80u) == 0) return;
    if ((flags & 1u) != 0) {
        CollideAndBounce(p);
    } else if ((flags & 0x400u) != 0) {
        CollideAndStop(p);
    } else {
        ProbeGround(p);
    }
}

// 0x00594928 CKProjectileTypeScrap_LaunchPiece. Draws rand: one for the lifetime (+0x0c + (1 - r / 32767.5) * +0x18),
// one for the scale unless +0x24 and +0x28 are both 1.0, three for the random rotation (data flag 0x20), in this order.
void CKProjectileTypeScrap::LaunchPiece(IKSerializable* dataObject, uint8_t index, const CVector3* pos,
                                        const CVector3* dir, float speed, IKSerializable* owner, const RwMatrix* matrix,
                                        IKSerializable* damage) {
    Projectile* p = ProjectileAt(this, index);
    p->m_pOwner = owner;
    p->m_pData = dataObject;
    p->m_flags58 = 1;
    const float vx = speed * dir->x;
    const float vz = speed * dir->z;
    const float vy = speed * dir->y;
    p->m_vVelocity.x = vx;
    p->m_vVelocity.z = vz;
    p->m_vVelocity.y = vy;
    ComputeRollAxis(p, vx, vz);
    const float one = 1.0f;
    p->m_fAge = 0.0f;
    p->m_GrdContDatasInOut.m_i32FaceIndex = -1;
    p->m_GrdContDatasInOut.m_ui8SectorNumber = 0;
    p->m_GrdContDatasInOut.m_eContactStatus = 3;
    p->m_GrdContDatasInOut.m_pGround = nullptr;
    p->m_vPos = *pos;
    p->m_vPrevPos = *pos;
    p->m_fRollSpeed = 0.0f;
    const float base = DataOf(p)->m_unk0c;
    {
        const uint32_t r = static_cast<uint32_t>(Rand_Int()) & 0xffffu;               // 0x00011500
        const float t = ppc::fmadds(static_cast<float>(r), -3.05180438e-05f, one);  // 0xb8000080
        p->m_fLifetime = ppc::fmadds(t, DataOf(p)->m_unk18, base);
    }
    SetIdentity(p->m_pNode);  // 0x000d08f0
    p->m_pNode->m_sgProperties &= 0xfffffffbu;
    p->m_fSpeed = speed;
    if (matrix != nullptr) static_cast<CSGMovable*>(p->m_pNode)->SetLocalMatrix(matrix);  // 0x000d0be8
    const float low = DataOf(p)->m_unk24;
    const float high = DataOf(p)->m_unk28;
    if (low == one && high == one) {
        p->m_fScale = one;
    } else {
        const uint32_t r = static_cast<uint32_t>(Rand_Int()) & 0xffffu;
        const float t = static_cast<float>(r) / 65535.0f;  // 0x477fff00
        p->m_fScale = ppc::fmadds(high - low, t, low);
        if ((m_baOptions & 0x100u) != 0) {
            // STUB(C2.8+, physics): the body's shape (+0x10 -> +0x100 -> +0x1c) vt+0x58 and
            // CKPxBody_UpdateInertiaTensor_maybe 0x219e50 (no LVL010 pool has option 0x100).
            DOTD_STUB_ONCE("CKProjectileTypeScrap_LaunchPiece: the body's inertia (physics)");
        }
    }
    ScaleAxes(p->m_pNode, p->m_fScale);
    SetFramePosition(FrameOf(p->m_pNode), *pos);
    if ((DataOf(p)->m_unk38 & 0x20u) != 0) {
        const float full = 6.28318548f;     // 0x40c90fdb
        const float degrees = 57.2957802f;  // 0x42652ee1
        CSGMovable* node = static_cast<CSGMovable*>(p->m_pNode);
        uint32_t r = static_cast<uint32_t>(Rand_Int()) & 0xffffu;
        node->RotateInPlace(&kAxisX.x, ((static_cast<float>(r) / 65535.0f) * full) * degrees);
        r = static_cast<uint32_t>(Rand_Int()) & 0xffffu;
        node->RotateInPlace(&kAxisY.x, ((static_cast<float>(r) / 65535.0f) * full) * degrees);
        r = static_cast<uint32_t>(Rand_Int()) & 0xffffu;
        node->RotateInPlace(&kAxisZ.x, ((static_cast<float>(r) / 65535.0f) * full) * degrees);
    }
    if ((DataOf(p)->m_unk38 & 0x40u) != 0) SetGeometriesAlpha(p->m_pNode, 0xff);
    if ((DataOf(p)->m_unk38 & 8u) != 0) {
        CKParticlesEffectFxData* fxData = static_cast<CKParticlesEffectFxData*>(DataOf(p)->m_unk44);
        fxData->m_pAttachHotSpot = nullptr;
        fxData->m_pAttachOwner = p->m_pNode;
        p->m_pFx = AcquireFx(static_cast<CKParticlesEffectFxData*>(DataOf(p)->m_unk44), this);
    }
    if ((m_baOptions & 0x100u) != 0) {
        // STUB(C2.8+, physics): the body woken (out of its container into the physics service's +0x40, message 0x2c00,
        // its contacts' bodies woken: CKSrvPhysics_WakeBodyIsland_maybe). No LVL010 pool has option 0x100.
        DOTD_STUB_ONCE("CKProjectileTypeScrap_LaunchPiece: waking the projectile's body (physics)");
    }
    if ((m_baOptions & 0x200u) != 0) {
        if (DataOf(p)->m_unk2c <= 0.0f) {
            PlayInstanceSound(index);  // inlined in the original
        } else {
            p->m_flags58 = static_cast<uint8_t>(p->m_flags58 & 0xfbu);
        }
    }
    if ((DataOf(p)->m_unk38 & 0x1000u) != 0) return;
    if (p->m_pVolume == nullptr) {
        if (Collision()->m_ui8NbProjectileUsed > 0x31) return;
        p->m_pVolume = Collision()->AcquireDynSphere();  // 0x00192a70
        if (p->m_pVolume == nullptr) return;
    }
    CKDynamicBoundingSphere* volume = static_cast<CKDynamicBoundingSphere*>(p->m_pVolume);
    if (volume->m_pParent != nullptr) volume->m_pParent->RemoveChild(volume);  // vt+0x78
    static_cast<CSGBranch*>(static_cast<CSGLeaf*>(p->m_pNode))->AddChild(volume);  // vt+0x70
    SetFramePosition(volume->m_pRwFrame, kNullVector);
    const float radius = DataOf(p)->m_unk30;
    if (radius > 0.0f) {
        volume->m_fRadius = radius;
    } else {
        const uint32_t bits = 0x3a83126fu;  // 0.001f, stored as a word
        std::memcpy(&volume->m_fRadius, &bits, sizeof(bits));
    }
    volume->m_ba8Infos = static_cast<uint8_t>((volume->m_ba8Infos & 0xf7u) | 8u);
    volume->m_ba8Infos = static_cast<uint8_t>((volume->m_ba8Infos & 0xdfu) | 0x20u);
    volume->m_ba8Infos = static_cast<uint8_t>((volume->m_ba8Infos & 0xfbu) | 4u);
    volume->m_pOwner = owner;
    volume->m_v3WorldMove = kNullVector;
    volume->m_v3OldPos = *pos;
    volume->m_v3LastWorldPos = *pos;
    volume->m_ui16PropertiesFlags = 0;
    volume->m_ui8OwnerType = 0;
    volume->m_ui8OwnerType = DataOf(p)->m_unk34;
    volume->m_ui16PropertiesFlags = static_cast<uint16_t>(DataOf(p)->m_unk36 | volume->m_ui16PropertiesFlags);
    volume->m_unk1c = damage;
    volume->m_ba8Infos = static_cast<uint8_t>((volume->m_ba8Infos & 0x7fu) | 0x80u);
}

// 0x00595a80 CKProjectileTypeScrap_LaunchEx: LaunchPiece without a damage object, then the volume's +0x1c = `damage`.
uint8_t CKProjectileTypeScrap::LaunchEx(IKSerializable* data, const CVector3* pos, const CVector3* dir, float speed,
                                        IKSerializable* damage, IKSerializable* owner, const RwMatrix* matrix) {
    const uint8_t index = m_ui8NbOfActiveProjectiles;
    if (m_ui8MaxProjectiles <= index) return 0;
    LaunchPiece(data, index, pos, dir, speed, owner, matrix, nullptr);
    Projectile* p = ProjectileAt(this, index);
    if (p->m_pVolume != nullptr) static_cast<IKBoundingVolume*>(p->m_pVolume)->m_unk1c = damage;
    m_ui8NbOfActiveProjectiles = static_cast<uint8_t>(m_ui8NbOfActiveProjectiles + 1);
    return 1;
}

// 0x00595b60 CKProjectileTypeScrap_Launch
uint8_t CKProjectileTypeScrap::Launch(IKSerializable* data, const CVector3* pos, const CVector3* dir, float speed,
                                      IKSerializable* owner, const RwMatrix* matrix) {
    const uint8_t index = m_ui8NbOfActiveProjectiles;
    if (m_ui8MaxProjectiles <= index) return 0;
    LaunchPiece(data, index, pos, dir, speed, owner, matrix, nullptr);
    m_ui8NbOfActiveProjectiles = static_cast<uint8_t>(m_ui8NbOfActiveProjectiles + 1);
    return 1;
}

// 0x00595c08 CKProjectileTypeScrap_MessageProc: the physics messages 0x2c00 / 0x2c02 from a projectile's body (data:
// the projectile index): 0x2c00 hands the projectile's velocity and roll to its body and sets bit 1 (driven by the
// body), 0x2c02 takes the body's position and velocity back and clears bit 1. Returns 1.
// STUB(C2.8+, physics): the body side (CKPxBody_SyncFromNode_maybe and the body's fields +0xa4 / +0xb8 / +0xf0); no LVL010
// pool has a body, so no such message arrives.
int32_t CKProjectileTypeScrap::MessageProc(uint16_t message, void* /*data*/) {
    if (((message >> 8) & 0xff) == 0x2c) {
        DOTD_STUB_ONCE("CKProjectileTypeScrap_MessageProc: physics body message (physics)");
    }
    return 1;
}

// 0x00595be0 CKProjectileTypeScrap_Destroy: IKProjectileType_Destroy 0x001f3c38 (through its TOC bridge): both lists
// freed. BUG(original): the pointers are kept (the next Load replaces them), as in CKProjectileTypeBallisticPFX.
void CKProjectileTypeScrap::Destroy() { IKProjectileType::Destroy(); }

// 0x00595db0 CKProjectileTypeScrap_RecursiveRegistration
void CKProjectileTypeScrap::RecursiveRegistration(int32_t type) {
    if (m_unk2c != nullptr) m_unk2c->RecursiveRegistration(type);
}
