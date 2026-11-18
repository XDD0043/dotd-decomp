// CKS08MaleforColdBall.cpp - reconstructed original translation unit 0x4e9120-0x4ea4c8 (GAME_TOC1, main_toc1), 24 functions, 24 live.
// Primary class: CKS08MaleforColdBall  key 0xabcc  category Logic  size 0xd0  vtable 0xb2a840
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x4e9120  RegisterCKS08MaleforColdBallClass
//   [ ] 0x4e9198  _GLOBAL__I_4e9198
//   [x] 0x4e91a8  CKS08MaleforColdBall_Explode
//   [x] 0x4e9500  CKS08MaleforColdBall_ScatterTargetPoints_maybe
//   [x] 0x4e9658  CKS08MaleforColdBall_vf5C  (inherited: CKGolemAttackCommon::Vf5C)
//   [x] 0x4e9680  CKS08MaleforColdBall_AttachVolumesToHotSpots_maybe  (inherited: CKGolemAttackCommon::AttachVolumesToHotSpots)
//   [x] 0x4e96a8  CKS08MaleforColdBall_StopAttack_maybe  (inherited: CKGolemAttackCommon::StopAttack)
//   [x] 0x4e96d0  CKS08MaleforColdBall_StartAttack_maybe
//   [x] 0x4e9710  CKS08MaleforColdBall_PostLoad
//   [ ] 0x4e9850  CKS08MaleforColdBall_Save
//   [x] 0x4e9878  CKS08MaleforColdBall_RecursiveRegistration  (inherited: CKGolemAttackCommon's RecursiveRegistration slot)
//   [x] 0x4e98a0  CKS08MaleforColdBall_Destroy  (inherited: CKGolemAttackCommon::Destroy)
//   [x] 0x4e98c8  CKS08MaleforColdBall_Destructor  (~CKS08MaleforColdBall)
//   [x] 0x4e9938  CKS08MaleforColdBall_Construct_2  (the constructor CKS08MaleforColdBall() (a second copy))
//   [x] 0x4e9998  CKS08MaleforColdBall_Construct
//   [x] 0x4e99f8  CKS08MaleforColdBall_DeleteArray
//   [x] 0x4e9a98  CKS08MaleforColdBall_DestructBody  (~CKS08MaleforColdBall)
//   [x] 0x4e9b08  CKS08MaleforColdBall_DeletingDestructor  (~CKS08MaleforColdBall)
//   [x] 0x4e9b80  CKS08MaleforColdBall_Create
//   [x] 0x4e9bf0  CKS08MaleforColdBall_CreateArray
//   [x] 0x4e9cd0  CKS08MaleforColdBall_vf64
//   [x] 0x4e9e00  CKS08MaleforColdBall_LaunchBalls_maybe
//   [x] 0x4ea078  CKS08MaleforColdBall_Update_maybe
//   [x] 0x4ea110  CKS08MaleforColdBall_Load
//
//   [ ] 0x9c6708  CKS08MaleforColdBall_IsKindOfClass  [inline]
//   [ ] 0x9c6758  CKS08MaleforColdBall_GetClassType  [inline]
//   [ ] 0x9c6760  CKS08MaleforColdBall_GetClassID  [inline]
#include "Spyro2008/logic/CKS08MaleforColdBall.h"

#include "k2000/io/IKFile.h"

// ==== port-all P13 ==================================================================================================
#include <cmath>

#include "crt/ppc_ops.h"
#include "k2000/hooks/CKHkGolem.h"
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/logic/fx/CKExplosionNodeFx.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/CSGLeaf.h"
#include "k2000/services/CKSrvFx.h"
#include "Renderware/rwcore/RwCamera.h"
#include "k2000/logic/CKProjectileAccessor.h"
#include "k2000/logic/CKProjectileTypeBallisticPFX.h"
#include "k2000/logic/ai/CKMarkerBeacon.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/services/IKProjectileType.h"
#include "k2000/system/IKTime.h"

// 0x004e9998 CKS08MaleforColdBall_Construct: CKGolemAttackCommon's constructor, then the runtime array header.
CKS08MaleforColdBall::CKS08MaleforColdBall() {
    m_unkb8 = nullptr;
    m_unkbc = 1;
    m_unkc0 = 0;
}

// 0x004ea110 CKS08MaleforColdBall_Load: CKGolemAttackCommon's data, then, for K_LEVEL_PLATEFORMS only, a
// reference, four words and four references.
int32_t CKS08MaleforColdBall::Load(IKFile* file, int32_t type) {
    CKGolemAttackCommon::Load(file, type);
    if (type != 0) return 1;

    IKFile_ReadRef(file, &m_unk98);
    ReadF32LE(file, &m_unkac);
    ReadF32LE(file, &m_unka4);
    ReadS32LE(file, &m_unka8);
    ReadF32LE(file, &m_unkb4);
    IKFile_ReadRef(file, &m_unka0);
    IKFile_ReadRef(file, &m_unk9c);
    IKFile_ReadRef(file, &m_unkc8);
    IKFile_ReadRef(file, &m_unkcc);
    return 1;
}

namespace {
// 0x00c50da0 (static initialiser): the "no point" vector, FLT_MAX x3.
const CVector3 kColdBallNoPoint = {3.40282347e+38f, 3.40282347e+38f, 3.40282347e+38f};
// The +0xa0 reference: a CKMarkerBeacon_maybe (its +0x04 position; the class is the beacon's by layout).
const CVector3& BeaconPosition(IKSerializable* beacon) { return static_cast<CKMarkerBeacon*>(beacon)->m_v3Position; }
}  // namespace

// 0x004e98c8 CKS08MaleforColdBall_Destructor
CKS08MaleforColdBall::~CKS08MaleforColdBall() {
    if (m_unkb8 != nullptr) Mem_FreeAligned16(m_unkb8);
    m_unkc0 = 0;
    m_unkb8 = nullptr;
}

// 0x004e9710 CKS08MaleforColdBall_PostLoad
int32_t CKS08MaleforColdBall::PostLoad(int32_t type) {
    CKGolemAttackCommon::PostLoad(type);
    if (type != 0) return 1;
    m_unkbc = 1;
    m_unkb8 = static_cast<CVector3*>(Mem_AllocAligned16(0xc));
    for (uint32_t i = 0; i < static_cast<uint32_t>(m_unka8);) {
        if (m_unkbc == m_unkc0) {
            uint32_t capacity = m_unkc0 + 1;
            uint32_t bytes = capacity * 0xc;
            if (capacity == 0) {
                capacity = 1;
                bytes = 0xc;
            }
            m_unkb8 = static_cast<CVector3*>(Mem_ReallocAligned16(m_unkb8, bytes & ~3u));
            m_unkbc = capacity;
        }
        ++i;
        m_unkb8[m_unkc0] = kColdBallNoPoint;
        m_unkc0 = m_unkc0 + 1;
    }
    return 1;
}

// 0x004e96d0 CKS08MaleforColdBall_StartAttack_maybe
void CKS08MaleforColdBall::StartAttack() {
    CKGolemAttackCommon::StartAttack();
    m_unkb0 = 0.0f;
    m_unkc4 = 0;
}

// 0x004ea078 CKS08MaleforColdBall_Update_maybe: ble (not greater: a NaN launches).
void CKS08MaleforColdBall::Update(IKTime* clock) {
    CKGolemAttackCommon::Update(clock);
    if (!(m_unkb4 > m_unkb0)) {
        if (m_unkc4 != 0) return;
        LaunchBalls();
        Explode();
        return;
    }
    m_unkb0 = m_unkb0 + clock->m_afDeltaTime[IKTime::SCALABLE_GAME_TIME];  // +0x1c
}

// 0x004e9cd0 CKS08MaleforColdBall_vf64: the loop's index steps back after a kill (the list compacts); the list pointer is
// read once.
void CKS08MaleforColdBall::Vf64() {
    IKProjectileType* type =
        static_cast<IKProjectileType*>(static_cast<CKProjectileAccessor*>(m_unk98)->m_pProjectileType);
    if (type == nullptr || m_unka0 == nullptr || type->m_ui8NbOfActiveProjectiles == 0) {
        Vf6C();  // vt+0x6c
        return;
    }
    uint8_t live = type->m_ui8NbOfActiveProjectiles;
    void** list = type->m_apProjectileList;
    for (uint8_t i = 0; i < live; ++i) {
        const CKProjectileTypeBallisticPFX::Projectile* ball =
            static_cast<const CKProjectileTypeBallisticPFX::Projectile*>(list[i]);
        if (ball == nullptr) continue;
        if (!(ball->m_vPos.y <= BeaconPosition(m_unka0).y)) continue;  // cror
        --live;
        type->OnDeath(i);  // vt+0x5c
        --i;
    }
}

// 0x004e9500 CKS08MaleforColdBall_ScatterTargetPoints_maybe: (u16 / 65535 twice added) x +0xa4 + centre, - +0xa4.
uint8_t CKS08MaleforColdBall::ScatterTargetPoints() {
    if (m_unka0 == nullptr) return 0;
    for (uint32_t i = 0; i < m_unkc0; ++i) {
        const float cx = BeaconPosition(m_unka0).x;
        float draw = static_cast<float>(static_cast<uint32_t>(Rand_Int()) & 0xffffu) / 65535.0f;  // 0x00011500
        m_unkb8[i].x = ppc::fmadds(draw + draw, m_unka4, cx) - m_unka4;
        m_unkb8[i].y = BeaconPosition(m_unka0).y;
        const float cz = BeaconPosition(m_unka0).z;
        draw = static_cast<float>(static_cast<uint32_t>(Rand_Int()) & 0xffffu) / 65535.0f;
        m_unkb8[i].z = ppc::fmadds(draw + draw, m_unka4, cz) - m_unka4;
    }
    return 1;
}

// 0x004e9e00 CKS08MaleforColdBall_LaunchBalls_maybe (the scatter inlined; the type's f2 1.0 is not read)
void CKS08MaleforColdBall::LaunchBalls() {
    if (ScatterTargetPoints() == 0) return;
    const CSGHotSpot* hotSpot = static_cast<const CSGHotSpot*>(Golem()->GetReference(0xb));  // vt+0xf8
    if (hotSpot == nullptr) return;
    CVector3 position;
    hotSpot->GetWorldPosition(&position);  // 0x000ce790
    for (uint32_t i = 0; i < m_unkc0; ++i) {
        CKProjectileAccessor* accessor = static_cast<CKProjectileAccessor*>(m_unk98);
        if (accessor->m_pProjectileType == nullptr) continue;
        const CVector3* point = &m_unkb8[i];
        if (point->x == kColdBallNoPoint.x && point->y == kColdBallNoPoint.y && point->z == kColdBallNoPoint.z) continue;
        accessor->LaunchAtPointEx(&position, point, m_unkac, m_unkcc, Golem());  // 0x001f2c50
        m_unkc4 = 1;
        Vf68();  // vt+0x68
    }
}

// 0x004e91a8 CKS08MaleforColdBall_Explode: a pooled effect of the explosion data (+0x9c; the inlined CKSrvFx lookup: reserved, owned
// by the attack, started; none free: nothing) at the golem's hot spot 11 (its world matrix), else at the golem's node
// position, the attack as the damage owner, category 1, flags 0x200, the damage (+0xc8), set off and released.
void CKS08MaleforColdBall::Explode() {
    CKSrvFx* fx = static_cast<CKSrvFx*>(g_pEngine->m_srvFx);
    IKFx* effect = fx->AcquireFx(static_cast<IKFxData*>(m_unk9c), this);
    if (effect == nullptr) return;
    CKExplosionNodeFx* explosion = static_cast<CKExplosionNodeFx*>(effect);
    const CSGHotSpot* hotSpot = static_cast<const CSGHotSpot*>(Golem()->GetReference(11));  // vt+0xf8
    if (hotSpot == nullptr) {
        const RwFrame* frame = static_cast<CSGLeaf*>(Golem()->m_pKGLObject)->m_pRwFrame;
        explosion->SetTranslation(reinterpret_cast<const CVector3*>(&frame->ltm.pos), this);  // 0x001b66e8
    } else {
        alignas(16) CMatrix34 matrix;
        hotSpot->GetWorldMatrix(&matrix);                                              // 0x000ce970
        explosion->SetMatrix(reinterpret_cast<const RwMatrix*>(&matrix), this);       // 0x001b6368
    }
    explosion->SetDamageOwner(this, this);    // 0x001b6340
    explosion->SetDamageCategory(1, this);    // 0x001b6318
    explosion->SetDamageFlags(0x200, this);   // 0x001b62f0
    explosion->SetDamage(m_unkc8, this);  // 0x001b62c8
    explosion->Trigger(this, nullptr);        // 0x001b82a8
    explosion->ReleaseReservation(this);      // vt+0x54
}
