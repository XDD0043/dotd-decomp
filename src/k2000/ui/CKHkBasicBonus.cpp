// CKHkBasicBonus.cpp - reconstructed original translation unit 0x5b48c8-0x5b7098 (GAME_TOC2, main_toc2), 23 functions,
// 20 live.
// Primary owner: CKHkBasicBonus (key 0x1c82; k2000/ui/CKHkBasicBonus.h)
// Other owners: CKHkS08Bonus (3)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x5b48c8  CKHkBasicBonus_GetSplineLockProjectileType_maybe  [dead]
//   [x] 0x5b48f8  CKHkBasicBonus_DestroyArray  (DeleteArray factory: DOTD_DECLARE_FACTORIES(CKHkBasicBonus); port-final F06)
//   [x] 0x5b49a8  CKHkBasicBonus_Create  (DOTD_DECLARE_FACTORIES + the constructor in CKHkBasicBonus.h; port-final F06)
//   [x] 0x5b4a50  CKHkBasicBonus_vfE4  (VfE4, XXL2 InitSpeedAndTarget; port-final F06)
//   [ ] 0x5b4a80  CKHkBasicBonus_SetFlagBitfields_2_maybe  [dead]
//   [x] 0x5b4ae0  CKHkBasicBonus_vfDC  (VfDC, XXL2 OnSectorUnload; port-final F06)
//   [x] 0x5b4b58  CKHkBasicBonus_ReturnToPool_maybe  (ReturnToPool, XXL2 Despawn; port-final F06)
//   [x] 0x5b4c90  CKHkBasicBonus_DisableAndReleaseFx_maybe  (XXL2 FastDespawn; port-final F06)
//   [x] 0x5b4d88  CKHkBasicBonus_SetVisible  (SpawnAtBeacon, XXL2 FastSpawn(CKBeaconAccessor&); port-final F06)
//   [x] 0x5b4f18  CKHkBasicBonus_ClearReferences  (the Destroy slot: empty, inline in the header; port-final F06)
//   [x] 0x5b4f20  CKHkBasicBonus_CreateArray  (DOTD_DECLARE_FACTORIES(CKHkBasicBonus); port-final F06)
//   [x] 0x5b5028  CKHkBasicBonus_LevelReset  (RecursiveRegistration; port-final F06)
//   [x] 0x5b50b8  CKHkBasicBonus_SnapToGround_maybe  (SetLaunchVelocity, XXL2 InitSpeedAndLanding; port-final F06)
//   [x] 0x5b56d0  CKHkBasicBonus_vfC8  (Collect, XXL2 Catched; port-final F06)
//   [ ] 0x5b59c0  CKHkBasicBonus_Save
//   [x] 0x5b5cf0  CKHkBasicBonus_Load  (port-final F06)
//   [x] 0x5b5f50  CKHkBasicBonus_Update  (port-final F06)
//   [x] 0x5b6c70  CKHkBasicBonus_SpawnAtPosition_maybe  (XXL2 FastSpawn(const CVector3&); port-final F06)
//   [x] 0x5b6df0  CKHkBasicBonus_SpawnAt_maybe  (SpawnAt, XXL2 Spawn; port-final F06)
//   [x] 0x5b6fc0  CKHkS08Bonus_Destroy  (DOTD_DECLARE_FACTORIES(CKHkS08Bonus))
//   [x] 0x5b7010  CKHkS08Bonus_vfDC  (CKHkS08Bonus::VfDC, CKHkS08Bonus.h)
//   [x] 0x5b7038  CKHkS08Bonus_InitSpawnedBonus_maybe  (inline at its only caller CKHkS08CrumblyZoneMultiState_Update (through TocBridge 0x98f560))
//   [ ] 0x5b7080  FUN_005b7080  [dead]
//
//   [x] 0x9cc570  CKHkBasicBonus_GetClassGroup  [inline]  (DOTD_CLASS_KEY)
//   [x] 0x9cc578  CKHkBasicBonus_GetClassId  [inline]  (DOTD_CLASS_KEY)
//   [x] 0x9cc580  CKHkBasicBonus_vfCC  [inline]  (IsCollected, CKHkBasicBonus.h)
//   [ ] 0x9cc5a0  KBase1C42_Load  [inline]  (IKHkBonus::Load, key 0x1c42: IKHook's + the +0x20 reference; both bonus
//                 Loads inline it)
//   [x] 0x9cc660  CKHkBasicBonus_IsKindOf  [inline]  (CKHkBasicBonus.h)
//   [x] 0x9cc6b8  CKHkBasicBonus_Destructor  [inline]  (CKHkBasicBonus.h)
//   [ ] 0x9cc6d8  KBase1C42_Save  [inline]
//   [x] 0x9cc798  CKHkBasicBonus_DeletingDestructor  [inline]  (CKHkBasicBonus.h)
//   [ ] 0x9cc7e8  KBase1C42_DeletingDestructor  [inline]
//   [ ] 0x9cc830  KBase1C42_Destructor  [inline]
//
// No level file holds a CKHkBasicBonus (LVL000..LVL120 and GAME.KP3 have only CKHkS08Bonus 0x3302), so nothing replays
// this file; it is ported from the disassembly with the pool's slots wired through IKHkBonus.
#include "k2000/ui/CKHkBasicBonus.h"

#include <cmath>

#include "Renderware/rwcore/RwCamera.h"
#include "crt/ppc_ops.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/logic/physics/CDynamicGround.h"
#include "k2000/memory/CKGrpBonusPool.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/Mat4.h"
#include "k2000/scenegraph/CSGBranch.h"
#include "k2000/scenegraph/CSGLeaf.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/services/CKSrvBeacon.h"
#include "k2000/services/CKSrvCollision.h"
#include "k2000/services/CollisionDatas.h"
#include "k2000/services/ICollisionMesh.h"
#include "k2000/system/IKTime.h"
#include "k2000/ui/CKBonusCpnt.h"

namespace {

// The shared y axis and null vector (0x00c50d40 / 0x00c50d64, TOC2 -0x64e4 / -0x64d4; filled by static initialisers).
const CVector3 kAxisY = {0.0f, 1.0f, 0.0f};
const CVector3 kNullVector = {0.0f, 0.0f, 0.0f};

CSGLeaf* NodeOf(const CKHkBasicBonus* bonus) { return static_cast<CSGLeaf*>(bonus->m_pKGLObject); }
RwFrame* FrameOf(const CKHkBasicBonus* bonus) { return NodeOf(bonus)->m_pRwFrame; }
CKGrpBonusPool* PoolOf(const CKHkBasicBonus* bonus) { return static_cast<CKGrpBonusPool*>(bonus->m_pGroup); }
CKBonusCpnt* CpntOf(const CKHkBasicBonus* bonus) { return static_cast<CKBonusCpnt*>(bonus->m_pBonusCpnt); }
CVector3* AsVec(RwV3d* v) { return reinterpret_cast<CVector3*>(v); }

// The frame's modelling position set (z, x, y as the code stores it), rwMATRIXINTERNALIDENTITY cleared, the frame marked
// dirty (RwFrame_MarkDirty 0x10698 through its TOC bridge).
void PlaceFrame(const CKHkBasicBonus* bonus, const CVector3& position) {
    RwFrame* frame = FrameOf(bonus);
    frame->modelling.pos.z = position.z;
    frame->modelling.pos.x = position.x;
    frame->modelling.pos.y = position.y;
    frame->modelling.flags &= 0xfffdffffu;
    RwFrame_MarkDirty(FrameOf(bonus));
}

// The node moved from its parent to the dynamic scene root (vt+0x78 of the parent, vt+0x70 of the root).
void ReattachToDynamicRoot(const CKHkBasicBonus* bonus) {
    CSGLeaf* node = NodeOf(bonus);
    node->m_pParent->RemoveChild(node);                                                      // vt+0x78
    static_cast<CSGBranch*>(g_pEngine->m_dynamicSceneRoot)->AddChild(NodeOf(bonus));       // vt+0x70
}

// The behaviour bits 3..11 of the bit array from the component's flags (the spawns' inlined SetBehaviour).
uint32_t BehaviourFromFlags(uint32_t bits, uint32_t flags) {
    bits = (bits & 0xfffffff7u) | (((flags >> 2) & 1u) << 3);
    bits = (bits & 0xffffffcfu) | ((flags << 4) & 0x30u);
    bits = (bits & 0xffffff3fu) | ((flags << 3) & 0xc0u);
    bits = (bits & 0xfffffcffu) | ((flags << 1) & 0x300u);
    bits = (bits & 0xfffff3ffu) | ((flags << 5) & 0xc00u);
    return bits;
}

// The modelling matrix's three rows times `k` (right, up, then at: x, z, y), rwMATRIXINTERNALIDENTITY and
// rwMATRIXTYPENORMAL cleared (0xfffdfffe), the frame marked dirty (Update's scale passes).
void ScaleRows(const CKHkBasicBonus* bonus, float k) {
    RwFrame* frame = FrameOf(bonus);
    RwMatrix& m = frame->modelling;
    m.right.x = k * m.right.x;
    m.right.y = k * m.right.y;
    m.right.z = k * m.right.z;
    m.up.x = k * m.up.x;
    m.up.y = k * m.up.y;
    m.up.z = k * m.up.z;
    const float ax = k * m.at.x;
    const float az = k * m.at.z;
    const float ay = k * m.at.y;
    m.at.x = ax;
    m.at.z = az;
    m.at.y = ay;
    m.flags &= 0xfffdfffeu;
    RwFrame_MarkDirty(frame);
}

}  // namespace

// 0x005b5028 CKHkBasicBonus_LevelReset (vt+0x24)
void CKHkBasicBonus::RecursiveRegistration(int32_t type) {
    if (static_cast<uint32_t>(type - 4) > 3u) g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);
    IKHook::RecursiveRegistration(type);  // 0x00019ab8 (TocBridge_IKHook_RecursiveRegistration)
}

// 0x005b5cf0 CKHkBasicBonus_Load (vt+0x2c): IKHook's; for the level type the next bonus (IKHkBonus's +0x20), the
// group / component / catcher as one array of three references, four words (+0x34..+0x40) in one read, the speed (three
// words) in another, then the ground contact's defaults (ground 0, sector 0, face -1, status 3).
int32_t CKHkBasicBonus::Load(IKFile* file, int32_t type) {
    IKHook::Load(file, type);  // through TocBridge_CKHook_Load
    if (type != K_LEVEL_PLATEFORMS) return 1;
    IKFile_ReadRef(file, &m_pNextBonus);
    IKFile_ReadObjectRefArray(file, &m_pGroup, 3);
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(&m_fLifeExpectancy), 4);
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(&m_vSpeed), 3);
    m_GrndDataInOut.m_pGround = nullptr;
    m_GrndDataInOut.m_ui8SectorNumber = 0;
    m_GrndDataInOut.m_i32FaceIndex = -1;
    m_GrndDataInOut.m_eContactStatus = 3;
    return 1;
}

// 0x005b4a50 CKHkBasicBonus_vfE4 (vt+0xe4, XXL2 InitSpeedAndTarget): the catcher, the speed, the timer 0.
void CKHkBasicBonus::VfE4(const CVector3* velocity, IKSerializable* catcher) {
    m_pCatcher = catcher;
    m_vSpeed.x = velocity->x;
    m_vSpeed.z = velocity->z;
    m_vSpeed.y = velocity->y;
    m_fTimer = 0.0f;  // stw 0
}

// 0x005b4ae0 CKHkBasicBonus_vfDC (vt+0xdc, XXL2 OnSectorUnload): the ground contact back to its defaults; a bonus
// attached under a moving ground (bit 13) is despawned at once (vt+0xd8).
void CKHkBasicBonus::VfDC() {
    m_GrndDataInOut.m_pGround = nullptr;
    m_GrndDataInOut.m_ui8SectorNumber = 0;
    m_GrndDataInOut.m_i32FaceIndex = -1;
    m_GrndDataInOut.m_eContactStatus = 3;
    if ((m_bitArray & 0x2000u) != 0) DisableAndReleaseFx();  // vt+0xd8
}

// 0x005b4b58 CKHkBasicBonus_ReturnToPool_maybe (vt+0xc0, XXL2 Despawn): hidden (node flag 4), back under the dynamic
// root when it hung under a moving ground (bit 13 cleared first), its effect released, its trail stopped, then the
// pool's collect explosion at its world position.
void CKHkBasicBonus::ReturnToPool() {
    CSGLeaf* node = NodeOf(this);
    node->m_sgProperties = (node->m_sgProperties & 0xfffffffbu) | 4u;
    if ((m_bitArray & 0x2000u) != 0) {
        m_bitArray &= 0xffffdfffu;
        ReattachToDynamicRoot(this);
    }
    PoolOf(this)->ReleaseBonusFx(m_pUnk7C);  // 0x005b1668
    PoolOf(this)->StopBonusTrail(m_ui32PoolIndex);   // 0x005b3e50
    const RwFrame* frame = FrameOf(this);
    const CVector3 at = {frame->ltm.pos.x, frame->ltm.pos.y, frame->ltm.pos.z};
    PoolOf(this)->TriggerCollectExplosion(&at);  // 0x005b3bc0
}

// 0x005b4c90 CKHkBasicBonus_DisableAndReleaseFx_maybe (vt+0xd8, XXL2 FastDespawn): as ReturnToPool without the
// explosion.
void CKHkBasicBonus::DisableAndReleaseFx() {
    CSGLeaf* node = NodeOf(this);
    node->m_sgProperties = (node->m_sgProperties & 0xfffffffbu) | 4u;
    if ((m_bitArray & 0x2000u) != 0) {
        m_bitArray &= 0xffffdfffu;
        ReattachToDynamicRoot(this);
    }
    PoolOf(this)->ReleaseBonusFx(m_pUnk7C);  // 0x005b1668
    PoolOf(this)->StopBonusTrail(m_ui32PoolIndex);   // 0x005b3e50
}

// 0x005b4d88 CKHkBasicBonus_SetVisible (vt+0xd0, XXL2 FastSpawn(CKBeaconAccessor&)): the beacon's position (three
// 16-bit tenths, fused with the floating height along y) given to vt+0xd4.
void CKHkBasicBonus::SpawnAtBeacon(const uint16_t* accessor) {
    CKSrvBeacon* beacons = static_cast<CKSrvBeacon*>(g_pEngine->m_srvBeacon);
    // DOTD: a sector without klusters or an id without a set has no data; the original reads its three halfwords at
    // the low addresses (0, 2, 4). Here they read as 0 (as CKHkS08Bonus::SpawnAtBeacon).
    const int16_t* data = reinterpret_cast<const int16_t*>(beacons->GetBeaconData(accessor));
    const int16_t raw[3] = {data != nullptr ? data[0] : int16_t(0), data != nullptr ? data[1] : int16_t(0),
                            data != nullptr ? data[2] : int16_t(0)};
    const float tenth = 0.1f;  // TOC2 -0x64e8 (0x3dcccccd)
    const float height = CpntOf(this)->m_fFloatingHeight;
    CVector3 position;
    position.x = ppc::fmadds(static_cast<float>(raw[0]), tenth, height * kAxisY.x);
    position.y = ppc::fmadds(static_cast<float>(raw[1]), tenth, height * kAxisY.y);
    position.z = ppc::fmadds(static_cast<float>(raw[2]), tenth, height * kAxisY.z);
    SpawnAtPosition(&position);  // vt+0xd4
}

// 0x005b6c70 CKHkBasicBonus_SpawnAtPosition_maybe (vt+0xd4, XXL2 FastSpawn(const CVector3&)): placed at `position`, no
// life expectancy and no minimum age (-1), the bob's height, shown, bit 12 set and bit 13 cleared, the behaviour from
// the component's flags, its effect taken and its trail reset.
void CKHkBasicBonus::SpawnAtPosition(const CVector3* position) {
    PlaceFrame(this, *position);
    m_fMinSpawnTime = -1.0f;  // TOC2 -0x64b0
    m_fLifeExpectancy = -1.0f;
    m_fTimer = 0.0f;  // stw 0
    m_pCatcher = nullptr;
    m_fCurrentHeight = CpntOf(this)->m_fFloatingHeight;
    CSGLeaf* node = NodeOf(this);
    node->m_sgProperties &= 0xfffffffbu;
    m_bitArray = (m_bitArray & 0xffffcfffu) | 0x1000u;
    m_bitArray = BehaviourFromFlags(m_bitArray, CpntOf(this)->m_baFlags);
    m_pUnk7C = PoolOf(this)->AcquireBonusFx(m_pKGLObject);  // 0x005b3958
    RwFrame* frame = FrameOf(this);
    PoolOf(this)->ResetBonusTrail(m_ui32PoolIndex, AsVec(&frame->modelling.pos), AsVec(&frame->modelling.up));  // 0x005b3ea8
}

// 0x005b6df0 CKHkBasicBonus_SpawnAt_maybe (vt+0xc4, XXL2 Spawn(pos, lifeExpectancy)): the life expectancy, the timer 0,
// caught from 0.3 s on, the bob's height; the node reset to the identity and placed at `position` raised by the
// floating height (fused), shown, no speed, no catcher, bits 12 and 13 cleared, the behaviour from the component's
// flags, its effect taken and its trail reset.
void CKHkBasicBonus::SpawnAt(float lifeExpectancy, const CVector3* position) {
    m_fLifeExpectancy = lifeExpectancy;
    m_fTimer = 0.0f;          // stw 0
    m_fMinSpawnTime = 0.3f;   // TOC2 -0x64ac (0x3e99999a)
    m_fCurrentHeight = CpntOf(this)->m_fFloatingHeight;
    static_cast<CSGMovable*>(m_pKGLObject)->SetIdentity();  // 0x000d08f0 (TocBridge 0x98ff50)
    const float height = CpntOf(this)->m_fFloatingHeight;
    RwFrame* frame = FrameOf(this);
    frame->modelling.pos.x = ppc::fmadds(height, kAxisY.x, position->x);
    frame->modelling.pos.y = ppc::fmadds(height, kAxisY.y, position->y);
    frame->modelling.pos.z = ppc::fmadds(height, kAxisY.z, position->z);
    frame->modelling.flags &= 0xfffdffffu;
    RwFrame_MarkDirty(FrameOf(this));
    CSGLeaf* node = NodeOf(this);
    node->m_sgProperties &= 0xfffffffbu;
    m_vSpeed.x = kNullVector.x;
    m_vSpeed.z = kNullVector.z;
    m_vSpeed.y = kNullVector.y;
    m_pCatcher = nullptr;
    m_bitArray &= 0xffffcfffu;
    m_bitArray = BehaviourFromFlags(m_bitArray, CpntOf(this)->m_baFlags);
    m_pUnk7C = PoolOf(this)->AcquireBonusFx(m_pKGLObject);  // 0x005b3958
    frame = FrameOf(this);
    PoolOf(this)->ResetBonusTrail(m_ui32PoolIndex, AsVec(&frame->modelling.pos), AsVec(&frame->modelling.up));  // 0x005b3ea8
}

// 0x005b56d0 CKHkBasicBonus_vfC8 (vt+0xc8, XXL2 Catched): once older than its minimum age (ble: NaN never), caught by
// `catcher`: the pick-up impulse along y, the timer 0, bit 12 cleared; a bonus under a moving ground goes back under
// the dynamic root at its world position (bit 13 cleared). The accessor kept (0xffff without one) and the beacon's
// persistent bit set; the component's flag 9 counts a collect sound in the pool.
void CKHkBasicBonus::Collect(IKSerializable* catcher, const uint16_t* accessor) {
    if (!(m_fTimer > m_fMinSpawnTime)) return;  // ble
    m_pCatcher = catcher;
    const float impulse = CpntOf(this)->m_fPickUpVerticalImpulse;
    m_vSpeed.x = impulse * kAxisY.x;
    m_vSpeed.z = impulse * kAxisY.z;
    m_vSpeed.y = impulse * kAxisY.y;
    m_fTimer = 0.0f;  // stw 0
    m_bitArray &= 0xffffefffu;
    if ((m_bitArray & 0x2000u) != 0) {
        const RwFrame* frame = FrameOf(this);
        const float wz = frame->ltm.pos.z;
        const float wx = frame->ltm.pos.x;
        const float wy = frame->ltm.pos.y;
        ReattachToDynamicRoot(this);
        PlaceFrame(this, CVector3{wx, wy, wz});
        m_bitArray &= 0xffffdfffu;
    }
    m_aui16Accessor[0] = 0xffff;
    m_aui16Accessor[3] = 0xffff;
    m_aui16Accessor[1] = 0xffff;
    m_aui16Accessor[2] = 0xffff;
    if (accessor != nullptr) {
        m_aui16Accessor[3] = accessor[3];
        m_aui16Accessor[0] = accessor[0];
        m_aui16Accessor[1] = accessor[1];
        m_aui16Accessor[2] = accessor[2];
        CKSrvBeacon* beacons = static_cast<CKSrvBeacon*>(g_pEngine->m_srvBeacon);
        CKSrvBeacon::CKBeaconSector& sector = beacons->m_aBeaconSectors[accessor[0]];
        if (sector.m_apBeaconKlusters != nullptr) {
            // DOTD: an id without a set: the original reads the set's bit count and start at the low addresses; skipped
            // (as CKHkS08Bonus::Collect).
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
    if ((CpntOf(this)->m_baFlags & 0x200u) != 0) ++PoolOf(this)->m_unk68;
}

// 0x005b50b8 CKHkBasicBonus_SnapToGround_maybe (vt+0xe0, XXL2 InitSpeedAndLanding): the landing of a launched bonus.
// The ground (`contact` copied first when given) under the point one speed step away (reach 2, height 2, masks 1 / 8);
// none, or one the pool refuses (vt+0x120): the ground under the bonus itself with no horizontal speed; still none:
// it hovers (static translation 1, no speed). On a moving ground (CDynamicGround) with engine flag 4 it keeps the speed
// and falls freely (3); on another moving ground it is moved into the ground's space and hung under the ground's node
// (or its parent when that is no branch), bit 13 set. Then the drop (2): the height above the ground (capped at the
// scaled half height) gives the vertical speed's time to land, which scales the horizontal speed.
void CKHkBasicBonus::SetLaunchVelocity(const CVector3* velocity, const CGroundContactDatasInOut* contact) {
    float vx = velocity->x;
    float vz = velocity->z;
    const RwFrame* frame = FrameOf(this);
    CVector3 at = {frame->modelling.pos.x, frame->modelling.pos.y, frame->modelling.pos.z};
    CVector3 point = {at.x + vx, at.y, at.z + vz};
    CGroundContactDatasIn in;  // masks 1, 8
    in.m_fDeltaMax = 2.0f;      // TOC2 -0x64d8
    in.m_fObjectHeight = 2.0f;
    if (contact != nullptr) CopyGroundContact(m_GrndDataInOut, *contact);
    CKSrvCollision* collision = static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision);
    CKGrpBonusPool* pool = PoolOf(this);
    collision->GroundProbePoints(&in, &m_GrndDataInOut, &point.x, 1);  // 0x00196540 (TocBridge 0x98fca0)
    if (m_GrndDataInOut.m_eContactStatus != 3 && static_cast<uint8_t>(pool->Vf120(m_GrndDataInOut.m_pGround)) != 0) {
        if (m_GrndDataInOut.m_eContactStatus != 0) {
            point.x = m_GrndDataInOut.m_ProjectionOnGround.x;
            point.y = m_GrndDataInOut.m_ProjectionOnGround.y;
            point.z = m_GrndDataInOut.m_ProjectionOnGround.z;
        }
    } else {
        point = at;
        vx = kNullVector.x;
        vz = kNullVector.z;
        collision->GroundProbePoints(&in, &m_GrndDataInOut, &point.x, 1);
        if (m_GrndDataInOut.m_eContactStatus != 0 ||
            static_cast<uint8_t>(pool->Vf120(m_GrndDataInOut.m_pGround)) == 0) {  // vt+0x120
            m_vSpeed.x = kNullVector.x;
            m_vSpeed.z = kNullVector.z;
            m_vSpeed.y = kNullVector.y;
            m_bitArray = (m_bitArray & 0xffffffcfu) | 0x10u;
            m_fMinSpawnTime = 0.0f;  // stw 0
            m_fCurrentHeight = 0.0f;
            return;
        }
    }
    IKSerializable* ground = m_GrndDataInOut.m_pGround;
    if (ground->IsKindOfClass(0x4cc) != 0) {  // vt+0x08: a CDynamicGround
        CDynamicGround* dynamic = static_cast<CDynamicGround*>(ground);
        if (((dynamic->m_ba16EngineFlags >> 4) & 1u) != 0) {
            m_vSpeed.x = velocity->x;
            m_vSpeed.z = velocity->z;
            m_vSpeed.y = velocity->y;
            m_bitArray = (m_bitArray & 0xffffffcfu) | 0x30u;
            m_fMinSpawnTime = 0.0f;  // stw 0
            m_fCurrentHeight = 0.0f;
            return;
        }
        CVector3 local;
        Mat4_TransformPoints(dynamic->GetInvertedWorldMatrix(), &local, &at, 1);  // vt+0x54; 0x0023f7e8
        at = local;
        PlaceFrame(this, local);
        CSGLeaf* node = NodeOf(this);
        node->m_pParent->RemoveChild(node);  // vt+0x78
        IKSerializable* parent = dynamic->m_pParent;
        CSGBranch* target = parent->IsKindOfClass(0x24b) != 0  // vt+0x08: a CSGBranch
                                ? static_cast<CSGBranch*>(parent)
                                : static_cast<CSGLeaf*>(parent)->m_pParent;
        target->AddChild(NodeOf(this));  // vt+0x70
        m_bitArray = (m_bitArray & 0xffffdfffu) | 0x2000u;
    }
    const CVector3& ground3 = m_GrndDataInOut.m_ProjectionOnGround;
    point.x = ground3.x;
    point.z = ground3.z;
    point.y = ground3.y;
    const float height = at.y - ground3.y;
    m_fCurrentHeight = height;
    const CKBonusCpnt* cpnt = CpntOf(this);
    float cap = cpnt->m_fHalfHeight * cpnt->m_fScale;
    if (!(height > cap)) cap = height;  // ble
    const float top = cap + ground3.y;
    point.y = top;
    const float drop = at.y - top;
    float energy = 0.0f;  // TOC2 -0x64c0
    if (!(drop < 0.0f)) energy = drop * 24.0f;  // blt; TOC2 -0x64d0
    m_bitArray = (m_bitArray & 0xffffffcfu) | 0x20u;
    const float vy = velocity->y;
    const float root = std::sqrt(ppc::fmadds(vy, vy, energy));  // 0x00010690 Math_Sqrtf (TocBridge 0x98fc10)
    const float time = (vy + root) / 12.0f;                      // TOC2 -0x64cc
    float k = 10.0f;                                             // TOC2 -0x64c8
    if (time > 0.1f) k = 1.0f / time;                            // bgt; TOC2 -0x64e8, -0x64c4
    const float sz = vz * k;
    m_vSpeed.y = velocity->y;
    const float sx = vx * k;
    m_vSpeed.z = sz;
    m_vSpeed.x = sx;
}

// 0x005b5f50 CKHkBasicBonus_Update (vt+0x7c). The timer runs (unless free and the pool's bit 7 holds it). Free: past
// its life expectancy it despawns (no frame update); else the static rotation / scale and translation of the
// behaviour bits. Caught: the caught rotation, scale and translation (the flight to the catcher with the pick-up
// acceleration and accuracy; on arrival the pool's IsCatcherChanged (vt+0x128) may hand it on, else ApplyEffect
// (vt+0x12c) and despawn). Then the frame placed and the trail's endpoints set.
void CKHkBasicBonus::Update(IKTime* frameClock) {
    const float dt = frameClock->m_afDeltaTime[0];
    const CMatrix34* spin = CpntOf(this)->m_pRotationMatrix;
    const RwFrame* frame0 = FrameOf(this);
    CVector3 pos = {frame0->modelling.pos.x, frame0->modelling.pos.y, frame0->modelling.pos.z};
    const float scale = CpntOf(this)->m_fScale;
    const float halfHeight = CpntOf(this)->m_fHalfHeight;
    CSGMovable* node = static_cast<CSGMovable*>(m_pKGLObject);
    CKSrvCollision* collision = static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision);
    if (IsCollected() != 0 || (PoolOf(this)->m_bitArray & 0x80u) == 0) m_fTimer = dt + m_fTimer;  // vt+0xcc
    if (m_pCatcher == nullptr) {
        const float life = m_fLifeExpectancy;
        if (life > 0.0f && m_fTimer >= life) {  // ble / cror gt|eq
            ReturnToPool();  // vt+0xc0
            return;
        }
        if (((m_bitArray >> 3) & 1u) == 1u) {
            node->SetLocalMatrix(reinterpret_cast<const RwMatrix*>(spin));  // 0x000d0be8 (TocBridge 0x990050)
        } else if (((CpntOf(this)->m_baFlags >> 3) & 3u) == 1u) {
            node->SetUniformScale(CpntOf(this)->m_fScale);  // 0x000d0970 (TocBridge 0x9906f0)
        } else {
            node->SetIdentity();  // 0x000d08f0 (TocBridge 0x98ff50)
        }
        uint32_t bits = m_bitArray;
        const uint32_t scaling = (bits >> 6) & 3u;
        if ((scaling == 0 || scaling == 2) && ((CpntOf(this)->m_baFlags >> 3) & 3u) == 1u) {
            ScaleRows(this, 1.0f / CpntOf(this)->m_fScale);  // TOC2 -0x64c4
            bits = m_bitArray;
        }
        const float cap = halfHeight * scale;
        const uint32_t move = (bits >> 4) & 3u;
        if (move == 2) {
            // The drop to rest: gravity (-12 along y) while above the scaled half height, else the bounce speed up.
            if (m_fCurrentHeight > cap) {  // ble
                const float g = dt * -12.0f;  // TOC2 -0x64bc
                m_vSpeed.z = ppc::fmadds(g, kAxisY.z, m_vSpeed.z);
                m_vSpeed.x = ppc::fmadds(g, kAxisY.x, m_vSpeed.x);
                m_vSpeed.y = ppc::fmadds(g, kAxisY.y, m_vSpeed.y);
            } else {
                m_vSpeed.y = CpntOf(this)->m_fVerticalBounceSpeed;
                m_vSpeed.z = 0.0f;  // stw 0
                m_vSpeed.x = 0.0f;  // stw 0
            }
            m_fCurrentHeight = ppc::fmadds(dt, m_vSpeed.y, m_fCurrentHeight);
            pos.x = ppc::fmadds(dt, m_vSpeed.x, pos.x);
            pos.y = ppc::fmadds(dt, m_vSpeed.y, pos.y);
            pos.z = ppc::fmadds(dt, m_vSpeed.z, pos.z);
        } else if (move == 3) {
            // The free fall: moved, gravity, the ground probe (reach 0, height 0, masks 1 / 8) at the new position.
            pos.x = ppc::fmadds(dt, m_vSpeed.x, pos.x);
            pos.y = ppc::fmadds(dt, m_vSpeed.y, pos.y);
            pos.z = ppc::fmadds(dt, m_vSpeed.z, pos.z);
            const float g = dt * -12.0f;  // TOC2 -0x64bc
            m_vSpeed.x = ppc::fmadds(g, kAxisY.x, m_vSpeed.x);
            m_vSpeed.z = ppc::fmadds(g, kAxisY.z, m_vSpeed.z);
            m_vSpeed.y = ppc::fmadds(g, kAxisY.y, m_vSpeed.y);
            CGroundContactDatasIn in;  // masks 1, 8
            in.m_fDeltaMax = 0.0f;     // stw 0
            in.m_fObjectHeight = 0.0f;
            collision->GroundProbePoints(&in, &m_GrndDataInOut, &pos.x, 1);  // 0x00196540 (TocBridge 0x98fca0)
            const uint32_t status = m_GrndDataInOut.m_eContactStatus;
            if (status == 0) {
                // BUG(original): on a ground the gravity step is added a second time.
                m_vSpeed.z = ppc::fmadds(g, kAxisY.z, m_vSpeed.z);
                m_vSpeed.x = ppc::fmadds(g, kAxisY.x, m_vSpeed.x);
                m_vSpeed.y = ppc::fmadds(g, kAxisY.y, m_vSpeed.y);
                if (m_GrndDataInOut.m_pGround->IsKindOfClass(0x4cc) == 0) {  // vt+0x08: not a CDynamicGround
                    const float height = pos.y - m_GrndDataInOut.m_ProjectionOnGround.y;
                    m_fCurrentHeight = height;
                    if (cap >= height) {  // cror gt|eq
                        m_vSpeed.z = 0.0f;  // stw 0
                        m_vSpeed.y = CpntOf(this)->m_fVerticalBounceSpeed;
                        m_vSpeed.x = 0.0f;  // stw 0
                        m_bitArray = (m_bitArray & 0xffffffcfu) | 0x20u;
                    }
                }
            } else if (status == 2) {
                // Against a wall: the line from the frame's position to the new one; a hit reflects the speed off the
                // wall's normal (-1.5 times its component), none despawns.
                const RwFrame* frame = FrameOf(this);
                CLine line;
                line.m_start.x = frame->modelling.pos.x;
                line.m_start.y = frame->modelling.pos.y;
                line.m_start.z = frame->modelling.pos.z;
                line.m_VectDir.x = pos.x - frame->modelling.pos.x;
                line.m_VectDir.y = pos.y - frame->modelling.pos.y;
                line.m_VectDir.z = pos.z - frame->modelling.pos.z;
                CGroundEdgeDatasOut edge;
                if (collision->RaycastWalls(&line, 0.0f, &edge, 1, nullptr, 1) != 0) {  // 0x00198438 (TocBridge 0x990040)
                    const CVector3& n = edge.m_EdgeNormal;
                    float d = n.y * m_vSpeed.y;
                    d = ppc::fmadds(n.x, m_vSpeed.x, d);
                    d = ppc::fmadds(n.z, m_vSpeed.z, d);
                    d = d * -1.5f;  // TOC2 -0x64b8
                    m_vSpeed.z = ppc::fmadds(n.z, d, m_vSpeed.z);
                    m_vSpeed.x = ppc::fmadds(n.x, d, m_vSpeed.x);
                    m_vSpeed.y = ppc::fmadds(n.y, d, m_vSpeed.y);
                } else {
                    ReturnToPool();  // vt+0xc0
                }
            } else {
                ReturnToPool();  // vt+0xc0
            }
        } else if (move == 1) {
            // The bob: the spin matrix's height (its +0x34) followed along y.
            m_vSpeed.x = kNullVector.x;
            m_vSpeed.y = kNullVector.y;
            m_vSpeed.z = kNullVector.z;
            const float d = spin->m_pos.y - m_fCurrentHeight;
            pos.y = ppc::fmadds(d, kAxisY.y, pos.y);
            pos.z = ppc::fmadds(d, kAxisY.z, pos.z);
            pos.x = ppc::fmadds(d, kAxisY.x, pos.x);
            m_fCurrentHeight = spin->m_pos.y;
        }
    } else {
        bool fly = false;
        bool arrived = false;
        uint32_t bits = m_bitArray;
        const uint32_t rotation = (bits >> 8) & 3u;
        if (rotation == 1) {
            node->SetLocalMatrix(reinterpret_cast<const RwMatrix*>(spin));  // 0x000d0be8
            bits = m_bitArray;
        } else if (rotation == 0) {
            if (((CpntOf(this)->m_baFlags >> 3) & 3u) == 1u) {
                node->SetUniformScale(CpntOf(this)->m_fScale);  // 0x000d0970
            } else {
                node->SetIdentity();  // 0x000d08f0
            }
            bits = m_bitArray;
        } else if (rotation == 2) {
            node->SetLocalMatrix(reinterpret_cast<const RwMatrix*>(spin));  // 0x000d0be8
            node->RotateInPlace(&kAxisY.x, m_fTimer * CpntOf(this)->m_fRotationAcc);  // 0x000d11b0 (TocBridge 0x98fe50)
            bits = m_bitArray;
        }
        const uint32_t scaling = (bits >> 6) & 3u;
        if (scaling == 0) {
            if (((CpntOf(this)->m_baFlags >> 3) & 3u) == 1u) {
                ScaleRows(this, 1.0f / CpntOf(this)->m_fScale);  // TOC2 -0x64c4
                bits = m_bitArray;
            }
        } else if (scaling == 2) {
            // The growth while caught: 1 + (scale - 1) * timer / max fly time (divided by the scale too when the
            // component's frame is scaled).
            const CKBonusCpnt* cpnt = CpntOf(this);
            float k;
            if (((cpnt->m_baFlags >> 3) & 3u) == 1u) {
                k = (cpnt->m_fScale - 1.0f) * m_fTimer / (cpnt->m_fScale * cpnt->m_fMaxFlyTime) + 1.0f;
            } else {
                k = (cpnt->m_fScale - 1.0f) * m_fTimer / cpnt->m_fMaxFlyTime + 1.0f;
            }
            ScaleRows(this, k);
            bits = m_bitArray;
        }
        const uint32_t move = (bits >> 10) & 3u;
        if (move == 1) {
            fly = true;
        } else if (move == 0) {
            PoolOf(this)->ApplyBonusToHero(m_pCatcher, this);  // vt+0x12c
            if ((CpntOf(this)->m_baFlags & 0x200u) == 0) ++PoolOf(this)->m_unk68;
            ReturnToPool();  // vt+0xc0
            fly = true;      // as the original (b 0x5b63b8): the flight runs on after the despawn (the catcher is kept)
        } else if (move == 2) {
            if (m_fTimer > CpntOf(this)->m_fMaxFlyTime) {  // bgt
                arrived = true;
            } else {
                pos.y = ppc::fmadds(CpntOf(this)->m_fPickUpVerticalImpulse, frameClock->m_afDeltaTime[0], pos.y);
            }
        } else {
            PoolOf(this)->ApplyBonusToHero(m_pCatcher, this);  // vt+0x12c
            ReturnToPool();                                    // vt+0xc0
        }
        if (fly) {
            // Towards the catcher's node (0.5 above it), at the pick-up acceleration times the timer, the speed blended
            // by the accuracy; arrived when this frame's step reaches it.
            const RwV3d& to = static_cast<CSGMovable*>(static_cast<IKHook*>(m_pCatcher)->m_pKGLObject)->m_pRwFrame->ltm.pos;
            const RwV3d& me = FrameOf(this)->ltm.pos;
            float dy = (to.y - me.y) + 0.5f;  // TOC2 -0x64b4
            float dx = (to.x - me.x) + 0.0f;  // TOC2 -0x64c0
            float dz = (to.z - me.z) + 0.0f;
            float dist = std::sqrt(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));  // Math_Sqrtf (TocBridge 0x98fc10)
            if (dist != 0.0f) {
                const float k = 1.0f / dist;
                dz = dz * k;
                dx = dx * k;
                dy = dy * k;
            } else {
                dist = 0.0f;
            }
            const CKBonusCpnt* cpnt = CpntOf(this);
            const float speed = cpnt->m_fPickUpAcc * m_fTimer;
            if (dt * speed >= dist) {  // cror gt|eq
                arrived = true;
            } else {
                const float sx = m_vSpeed.x;
                const float sy = m_vSpeed.y;
                const float sz = m_vSpeed.z;
                const float ex = ppc::fmsubs(dx, speed, sx);
                const float ey = ppc::fmsubs(dy, speed, sy);
                const float ez = ppc::fmsubs(dz, speed, sz);
                const float accuracy = cpnt->m_fAccuracy;
                m_vSpeed.x = ppc::fmadds(ex, accuracy, sx);
                m_vSpeed.y = ppc::fmadds(ey, accuracy, sy);
                m_vSpeed.z = ppc::fmadds(ez, accuracy, sz);
                pos.x = ppc::fmadds(dt, m_vSpeed.x, pos.x);
                pos.y = ppc::fmadds(dt, m_vSpeed.y, pos.y);
                pos.z = ppc::fmadds(dt, m_vSpeed.z, pos.z);
            }
        }
        if (arrived) {
            IKSerializable* next = PoolOf(this)->IsCatcherChanged(m_pCatcher);  // vt+0x128
            if (next != nullptr) {
                Collect(next, nullptr);  // vt+0xc8
            } else {
                PoolOf(this)->ApplyBonusToHero(m_pCatcher, this);  // vt+0x12c
                if ((CpntOf(this)->m_baFlags & 0x200u) == 0) ++PoolOf(this)->m_unk68;
                ReturnToPool();  // vt+0xc0
            }
        }
    }
    PlaceFrame(this, pos);
    RwFrame* frame = FrameOf(this);
    PoolOf(this)->SetBonusTrailEndpoints(m_ui32PoolIndex, AsVec(&frame->modelling.pos), AsVec(&frame->modelling.up));  // 0x005b1508
}
