// CKS08CarrierEnemy.cpp - reconstructed original translation unit 0x4c7730-0x4c98d8 (GAME_TOC1, main_toc1), 39 functions, 35 live.
// Primary class: CKS08CarrierEnemy  key 0x958c  category Logic  size 0xa8  vtable 0xb297e0
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x4c7730  CKS08CarrierEnemy_Delete
//   [x] 0x4c7780  CKS08CarrierEnemy_vf58
//   [x] 0x4c7878  CKS08CarrierEnemy_vf5C
//   [x] 0x4c78b0  CKS08CarrierEnemy_vf64  (header)
//   [x] 0x4c78b8  CKS08CarrierEnemy_State0_Carry_maybe
//   [x] 0x4c79d0  CKS08CarrierEnemy_vf78
//   [ ] 0x4c79f8  KStub_Return0_4c79f8  [dead]
//   [x] 0x4c7a00  CKS08CarrierEnemy_State2_PickUp_maybe
//   [x] 0x4c7c48  CKS08CarrierEnemy_IsCarrying_maybe  (header)
//   [x] 0x4c7c58  CKS08CarrierEnemy_ClaimTransportableInReach_maybe
//   [ ] 0x4c7ef0  CKS08CarrierEnemy_ClaimTransportableInReach_Key0xC2_maybe  [dead]
//   [ ] 0x4c7f10  CKS08CarrierEnemy_Save
//   [x] 0x4c7f38  CKS08CarrierEnemy_RecursiveRegistration  (KBase910C's (KBase910C_vf24: nothing registered), then 1)
//   [x] 0x4c7f60  CKS08CarrierEnemy_Destroy  (header)
//   [x] 0x4c7fa8  CKS08CarrierEnemy_DeleteArray
//   [x] 0x4c8048  CKS08CarrierEnemy_Construct  [dead]
//   [x] 0x4c80a0  CKS08CarrierEnemy_CaptureCarryPose_maybe
//   [ ] 0x4c8228  RegisterCKS08CarrierEnemyClass
//   [ ] 0x4c82b0  _GLOBAL__D_4c82b0
//   [ ] 0x4c82c0  _GLOBAL__I_4c82c0
//   [x] 0x4c82d0  CKS08CarrierEnemy_DropCarriedObject_maybe
//   [x] 0x4c8450  CKS08CarrierEnemy_StartCarrying_maybe
//   [ ] 0x4c84d0  CKS08CarrierEnemy_Construct_2  [dead]
//   [x] 0x4c8528  CKS08CarrierEnemy_DestructBody  (header)
//   [x] 0x4c8558  CKS08CarrierEnemy_DeletingDestructor  (header)
//   [x] 0x4c85a0  CKS08CarrierEnemy_Destructor  (header)
//   [x] 0x4c85d0  CKS08CarrierEnemy_vf70  (= 0x4c82d0 CKS08CarrierEnemy_DropCarriedObject_maybe (the same code))
//   [x] 0x4c8750  CKS08CarrierEnemy_MessageProc  (returns 1: the root's default)
//   [x] 0x4c8758  CKS08CarrierEnemy_PostLoad  (returns 1: the root's default)
//   [ ] 0x4c8760  CKS08CarrierEnemy_LerpCarriedObjectToHotSpot_maybe  [dead: no pointer to its descriptor 0xbcafc0, no call (C2.8 port-rest R10)]
//   [x] 0x4c89f0  CKS08CarrierEnemy_StopCarrying_maybe
//   [x] 0x4c8c30  CKS08CarrierEnemy_IsTransportableInReach_maybe
//   [x] 0x4c8da0  CKS08CarrierEnemy_CreateArray
//   [x] 0x4c8e70  CKS08CarrierEnemy_Create
//   [x] 0x4c8ed8  CKS08CarrierEnemy_IsInGrabRangeAndAngle_maybe
//   [x] 0x4c90f0  CKS08CarrierEnemy_Load
//   [x] 0x4c93e8  CKS08CarrierEnemy_UpdateStateMachine_maybe
//   [x] 0x4c95e8  CKS08CarrierEnemy_ResetStateMachine_maybe
//   [x] 0x4c9720  CKS08CarrierEnemy_Reset_maybe
//
//   [ ] 0x9c5380  CKS08CarrierEnemy_vf60  [inline]
//   [ ] 0x9c5388  CKS08CarrierEnemy_vf80  [inline]
//   [ ] 0x9c5a00  CKS08CarrierEnemy_IsKindOfClass  [inline]
//   [ ] 0x9c5a38  CKS08CarrierEnemy_GetClassType  [inline]
//   [ ] 0x9c5a40  CKS08CarrierEnemy_GetClassID  [inline]
//   [ ] 0x9c5a48  CKS08CarrierEnemy_vf7C  [inline]
#include "Spyro2008/logic/CKS08CarrierEnemy.h"

#include "Spyro2008/components/CKS08FightZoneCpnt.h"
#include "Spyro2008/hooks/CKHkS08Enemy.h"
#include "k2000/core/Ps3MemberFn.h"
#include "k2000/core/Stub.h"
#include "k2000/groups/CKGrpFightZone.h"
#include "k2000/groups/CKGrpSquad.h"
#include "k2000/groups/IKBaseGroup.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/misc/Engine.h"

#include "k2000/io/IKFile.h"
#include "k2000/groups/CKGrpTransportableObject.h"
#include "k2000/memory/KObjectRefList.h"
#include "k2000/scenegraph/CSGBranch.h"
#include "k2000/scenegraph/CSGLeaf.h"
#include "Renderware/rwcore/RwCamera.h"
#include "Spyro2008/misc/CKHkS08TransportableBase.h"
#include "crt/ppc_ops.h"
#include <cstring>
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/math/Quat.h"
#include "crt/xsinf.h"
#include "Spyro2008/groups/C22SpyroShims.h"

// 0x004c90f0 CKS08CarrierEnemy_Load: the base's Load, then (level data only) two floats, a counted word
// array, two references and a float.
int32_t CKS08CarrierEnemy::Load(IKFile* file, int32_t type) {
    KBase910C::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadF32LE(file, &m_unk2c);
    ReadF32LE(file, &m_unk28);
    ReadU32LE(file, &m_ui32NbUnk1c);
    m_aui32Unk1c = new uint32_t[m_ui32NbUnk1c];
    for (uint32_t i = 0; i < m_ui32NbUnk1c; ++i) ReadU32LE(file, &m_aui32Unk1c[i]);
    IKFile_ReadRef(file, &m_pHotSpot);
    IKFile_ReadRef(file, &m_pEnemy);
    ReadF32LE(file, &m_unk34);
    return 1;
}

namespace {
// DOTD: the carrier's state handlers by descriptor (the rows Reset writes; TOC +0x6858 / +0x685c / +0x6860).
Ps3MemberFnEntry<CKS08CarrierEnemy::StateFn> g_carrierStates[] = {
    {0x00bcae18u, &CKS08CarrierEnemy::State0Carry, "CKS08CarrierEnemy_State0_Carry_maybe 0x4c78b8", false},
    {0x00bcaff0u, &CKS08CarrierEnemy::IsTransportableInReach, "CKS08CarrierEnemy_IsTransportableInReach_maybe 0x4c8c30", false},
    {0x00bcae30u, &CKS08CarrierEnemy::State2PickUp, "CKS08CarrierEnemy_State2_PickUp_maybe 0x4c7a00", false},
};
}  // namespace

uint8_t CKS08CarrierEnemy::CallState(const uint32_t pair[2], IKTime* clock, int32_t phase, uint8_t other) {
    StateFn fn = ResolvePs3MemberFn(g_carrierStates, pair, "CKS08CarrierEnemy state handler");
    if (fn == nullptr) return other;
    return (this->*fn)(clock, phase, other);
}

// 0x004c9720 CKS08CarrierEnemy_Reset_maybe: the three rows, state 1 entered (clock null, from 0xff), the transport
// group found again, the hot spot 3 of the enemy.
void CKS08CarrierEnemy::Reset() {
    m_aStates[0][0] = 0x00bcae18u;
    m_aStates[1][0] = 0x00bcaff0u;
    m_aStates[2][0] = 0x00bcae30u;
    m_aStates[2][1] = 0;
    m_aStates[0][1] = 0;
    m_aStates[1][1] = 0;
    m_unk8c = 1;
    m_unk8d = 3;
    m_pStates = &m_aStates[0][0];
    CallState(m_aStates[1], nullptr, 1, 0xff);
    IKBaseGroup* parent = static_cast<IKBaseGroup*>(g_pEngine->m_gameManager->m_unk04[2]);  // +0x0c
    m_pTransportGroup = nullptr;
    if (parent != nullptr && parent->m_lChilds != nullptr) {
        // The children counted first (only to skip an empty list), then the last of class id 0x35 kept.
        for (IKBaseGroup* child = parent->m_lChilds; child != nullptr; child = child->m_pNextGroup) {
            if (child->GetClassID() == 0x35) m_pTransportGroup = child;  // vt+0x18
        }
    }
    m_unk84 = 0;
    m_unk10 = nullptr;
    m_unk0c = nullptr;
    m_pHotSpot = reinterpret_cast<IKSerializable*>(static_cast<CKHkS08Enemy*>(m_pEnemy)->GetHotSpot(3));  // 0x002892e8
}

// 0x004c95e8 CKS08CarrierEnemy_ResetStateMachine_maybe: back to state 0.
void CKS08CarrierEnemy::ResetStateMachine() {
    const uint8_t old = m_unk8c;
    if (old != 0xff) CallState(m_pStates + old * 2, nullptr, 2, 0);
    m_unk8c = 0;
    CallState(m_pStates, nullptr, 1, old);
}

// 0x004c93e8 CKS08CarrierEnemy_UpdateStateMachine_maybe
void CKS08CarrierEnemy::UpdateStateMachine(IKTime* clock) {
    const uint8_t state = m_unk8c;
    if (state == 0xff) return;
    const uint8_t next = CallState(m_pStates + state * 2, clock, 0, state);
    const uint8_t old = m_unk8c;
    if (next == old) return;
    if (old != 0xff) CallState(m_pStates + old * 2, clock, 2, next);
    m_unk8c = next;
    if (next != 0xff) CallState(m_pStates + next * 2, clock, 1, old);
}

// 0x004c8c30 CKS08CarrierEnemy_IsTransportableInReach_maybe (state 1): in a fight zone of mode 4 with a transport group,
// a claimable transportable (key 0xc2) within reach (+0x28) that vt+0x58 accepts makes the next state 2.
uint8_t CKS08CarrierEnemy::IsTransportableInReach(IKTime* /*clock*/, int32_t phase, uint8_t other) {
    if (phase != 0) return other;
    CKHkS08Enemy* enemy = static_cast<CKHkS08Enemy*>(m_pEnemy);
    CKGrpFightZone* zone = static_cast<CKGrpFightZone*>(static_cast<CKGrpSquad*>(enemy->m_pGroupSquad)->m_pParent);
    if (zone->m_pFightZoneCpnt->m_unk04 != 4 || m_pTransportGroup == nullptr) return other;
    IKSerializable* object = ClaimTransportableInReach(0xc2);  // 0x004c7c58
    if (object == nullptr) return other;
    const float reach = m_unk28;
    const RwV3d& p = FrameLtm(static_cast<CSGLeaf*>(static_cast<IKHook*>(object)->m_pKGLObject)->m_pRwFrame)->pos;
    const RwV3d& e = FrameLtm(static_cast<CSGLeaf*>(enemy->m_pKGLObject)->m_pRwFrame)->pos;
    const float pz = p.z, px = p.x, py = p.y;
    const float ez = e.z, ex = e.x, ey = e.y;
    if (CanPickUp(object) == 0) return other;  // vt+0x58
    const float dz = pz - ez, dx = px - ex, dy = py - ey;
    if (ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)) <= reach * reach) return 2;
    return other;
}

// 0x004c7c58 CKS08CarrierEnemy_ClaimTransportableInReach_maybe. The enemy's transportable (+0x738), if any, stays claimed
// while it can be picked up (vt+0xf4) and is in a state (vt+0x110), else it is unmarked (vt+0x138 with 0) and null comes
// back. Without one, the first live transportable of class `key` (IsKindOf 0x3002, not marked (vt+0x13c), vt+0xf4,
// vt+0x110) becomes the enemy's and the claim (+0x0c), marked (vt+0x138 with 1); null comes back that frame too
// (BUG(original)? the claim answers the next frame).
IKSerializable* CKS08CarrierEnemy::ClaimTransportableInReach(uint32_t key) {
    CKHkS08Enemy* enemy = static_cast<CKHkS08Enemy*>(m_pEnemy);
    CKHkS08TransportableBase* held = static_cast<CKHkS08TransportableBase*>(enemy->m_unk738);
    if (held != nullptr) {
        if (held->VfF4(this) == 0 || held->Vf110() == 0) {
            held->Vf138(0);
            return nullptr;
        }
        return held;
    }
    KObjectRefList* list = static_cast<CKGrpTransportableObject*>(m_pTransportGroup)->FindListByKey(key);  // 0x004a7538
    for (uint32_t i = list->m_ui32Count2; i != list->m_ui32Count; ++i) {
        CKHkS08TransportableBase* object = static_cast<CKHkS08TransportableBase*>(list->m_pBlock[i]);
        if (object == nullptr) break;
        if (object->IsKindOfClass(0x3002) != 0 && object->Vf13C() == 0 && object->VfF4(this) != 0 &&
            object->Vf110() != 0) {
            enemy->m_unk738 = object;
            object->Vf138(1);
            m_unk0c = object;
            return nullptr;
        }
    }
    return nullptr;
}

// 0x004c7780 CKS08CarrierEnemy_vf58
uint8_t CKS08CarrierEnemy::CanPickUp(IKSerializable* object) {
    if (object == nullptr || m_unk10 != nullptr) return 0;
    const uint32_t id = static_cast<uint32_t>(object->GetClassID());  // vt+0x18
    if (Vf78(&id) == 0) return 0;  // vt+0x78
    return static_cast<uint8_t>(static_cast<CKHkS08TransportableBase*>(object)->Vf100() ^ 1u);  // vt+0x100
}

// 0x004c79d0 CKS08CarrierEnemy_vf78: keys only (0xc2).
uint8_t CKS08CarrierEnemy::Vf78(const uint32_t* classId) const { return *classId == 0xc2u ? 1 : 0; }

// 0x004c82d0 CKS08CarrierEnemy_DropCarriedObject_maybe: the carried transportable unmarked (vt+0x138 with 0), its node
// (keeping its world pose: the LTM as its local matrix) out of its parent and under the engine's dynamic scene root
// (+0x14); still held by this carrier (vt+0xfc): dropped (vt+0xf8 with the zero vector 0x00c50d64); nothing carried.
void CKS08CarrierEnemy::DropCarriedObject() {
    CKHkS08TransportableBase* object = static_cast<CKHkS08TransportableBase*>(m_unk10);
    if (object == nullptr) return;
    object->Vf138(0);
    CSGLeaf* node = static_cast<CSGLeaf*>(object->m_pKGLObject);
    if (node->m_pParent != nullptr) {
        node->SetLocalMatrix(FrameLtm(node->m_pRwFrame));  // 0x000d0be8
        node->m_pParent->RemoveChild(node);  // vt+0x78
    }
    static_cast<CSGBranch*>(g_pEngine->m_dynamicSceneRoot)->AddChild(node);  // vt+0x70
    static const CVector3 kZero = {0.0f, 0.0f, 0.0f};
    if (object->VfFC(this) != 0) object->VfF8(this, &kZero);
    m_unk10 = nullptr;
}

// ==== C2.8 port-all P12 ===================================================================================================
namespace {
CSGLeaf* CarriedNode(IKSerializable* object) { return static_cast<CSGLeaf*>(static_cast<IKHook*>(object)->m_pKGLObject); }

// The inlined cosine of an angle (game form for a clear sign bit, the library's cosf of -x otherwise), as
// CKS08CarrierHero.cpp's.
float CarrierCosOfAngle(float angle) {
    uint32_t bits;
    std::memcpy(&bits, &angle, sizeof(bits));
    if (static_cast<int32_t>(bits) < 0) return crt::LibCosf(-angle);
    return crt::InlineCosf(angle);
}
}  // namespace

// vt+0x5c 0x004c7878 CKS08CarrierEnemy_vf5C: `object` is the carried transportable (+0x10, not null).
uint8_t CKS08CarrierEnemy::Vf5C(IKSerializable* object) {
    if (m_unk10 != object) return 0;
    return m_unk10 != nullptr ? 1 : 0;
}

// vt+0x50 0x004c8450 CKS08CarrierEnemy_StartCarrying_maybe: `object` carried (+0x10), its node taken from its parent
// (vt+0x78) and hung under the hot spot (CSGHotSpot_AttachVolume 0xce2b8); returns 0.
uint8_t CKS08CarrierEnemy::StartCarrying(IKSerializable* object) {
    m_unk10 = object;
    CSGLeaf* node = CarriedNode(object);
    if (node->m_pParent != nullptr) node->m_pParent->RemoveChild(node);  // vt+0x78
    static_cast<CSGHotSpot*>(m_pHotSpot)->AttachVolume(CarriedNode(m_unk10));
    return 0;
}

// 0x004c80a0 CKS08CarrierEnemy_CaptureCarryPose_maybe (the code of CKS08CarrierHero_CaptureCarryPose_maybe 0x4b0a48 on
// this layout): the claimed transportable's (+0x0c) modelling position (+0x78), the hot spot's world orientation (+0x58)
// and the node's own (+0x68) as quaternions, the lerp time (+0x38) back to 0.
void CKS08CarrierEnemy::CaptureCarryPose() {
    const RwFrame* frame = CarriedNode(m_unk0c)->m_pRwFrame;
    m_vStartPos.x = frame->modelling.pos.x;
    m_vStartPos.y = frame->modelling.pos.y;
    m_vStartPos.z = frame->modelling.pos.z;
    CMatrix34 spot;
    static_cast<CSGHotSpot*>(m_pHotSpot)->GetWorldMatrix(&spot);  // 0x000ce970
    Quat_FromMatrix(m_aQuatHotSpot, reinterpret_cast<const float*>(&spot));  // 0x002420f8
    const RwFrame* f = CarriedNode(m_unk0c)->m_pRwFrame;
    CMatrix34 own;
    std::memcpy(&own, &f->modelling, sizeof own);
    Quat_FromMatrix(m_aQuatStart, reinterpret_cast<const float*>(&own));
    m_fCarryTime = 0.0f;
}

// 0x004c8ed8 CKS08CarrierEnemy_IsInGrabRangeAndAngle_maybe (the code of CKS08CarrierHero_IsInGrabRangeAndAngle_maybe
// 0x4b1bc8 with the range +0x28 and the angle +0x2c). No caller in the original besides its OPD.
uint8_t CKS08CarrierEnemy::IsInGrabRangeAndAngle(const CVector3* pos, const CVector3* dir, IKSerializable* object) const {
    const RwV3d& p = FrameLtm(CarriedNode(object)->m_pRwFrame)->pos;
    float dy = pos->y - p.y;
    float dx = pos->x - p.x;
    float dz = pos->z - p.z;
    float distance = static_cast<float>(c22spyro::MathSqrtf(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy))));
    if (distance != 0.0f) {
        const float inv = 1.0f / distance;
        dz = dz * inv;
        dx = dx * inv;
        dy = dy * inv;
    } else {
        distance = 0.0f;
    }
    if (!(m_unk28 > distance)) return 0;
    const float limit = CarrierCosOfAngle(m_unk2c);
    const float dot = -ppc::fmadds(dz, dir->z, ppc::fmadds(dir->x, dx, dir->y * dy));  // fnmadds
    return limit < dot ? 1 : 0;
}

// 0x004c78b8 CKS08CarrierEnemy_State0_Carry_maybe (state 0). Only its exit does something: the carried transportable
// (+0x10) is let go when it agrees (vt+0xfc, then vt+0xf8 with the null velocity 0x00c50d64), unmarked (vt+0x138 with
// 0), and neither the carrier nor the enemy (+0x738) keeps it.
uint8_t CKS08CarrierEnemy::State0Carry(IKTime* /*clock*/, int32_t phase, uint8_t other) {
    if (phase != 2) return other;
    CKHkS08TransportableBase* carried = static_cast<CKHkS08TransportableBase*>(m_unk10);
    if (carried->VfFC(this) != 0) {
        static const CVector3 kZero = {0.0f, 0.0f, 0.0f};
        carried->VfF8(this, &kZero);
    }
    static_cast<CKHkS08TransportableBase*>(m_unk10)->Vf138(0);
    m_unk10 = nullptr;
    static_cast<CKHkS08Enemy*>(m_pEnemy)->m_unk738 = nullptr;
    return other;
}

// 0x004c7a00 CKS08CarrierEnemy_State2_PickUp_maybe (state 2). Enter: the enemy's main state machine switched to state
// 0x19 (the pick-up; its exit and enter run with a null clock). Update: when the claimed transportable (+0x0c) can be
// picked up (vt+0xf4) and no hit is pending on the enemy (+0x239) it is picked up (vt+0xf0) and carried (+0x10): state 0;
// else back to state 1.
uint8_t CKS08CarrierEnemy::State2PickUp(IKTime* /*clock*/, int32_t phase, uint8_t other) {
    if (phase != 0) {
        if (phase == 1) static_cast<CKHkS08Enemy*>(m_pEnemy)->SwitchMainState(0x19, nullptr);
        return other;
    }
    CKHkS08TransportableBase* claimed = static_cast<CKHkS08TransportableBase*>(m_unk0c);
    if (claimed->VfF4(this) != 0 && static_cast<CKHkS08Enemy*>(m_pEnemy)->m_bPendingHit == 0) {
        static_cast<CKHkS08TransportableBase*>(m_unk0c)->VfF0(this);
        m_unk10 = m_unk0c;
        return 0;
    }
    return 1;
}

// vt+0x54 0x004c89f0 CKS08CarrierEnemy_StopCarrying_maybe: `object` unmarked (vt+0x138 with 0), its node under sector 0's
// root (ReparentToBaseSectorRoot, the inlined block), placed at the enemy's drop point (+0x8e4) or, when that is the null
// vector (fcmpu: NaN is not), at the hot spot's world position; nothing claimed or carried; returns 1.
uint8_t CKS08CarrierEnemy::StopCarrying(IKSerializable* object) {
    CMatrix34 spot;
    static_cast<CSGHotSpot*>(m_pHotSpot)->GetWorldMatrix(&spot);  // 0x000ce970
    CKHkS08TransportableBase* item = static_cast<CKHkS08TransportableBase*>(object);
    item->Vf138(0);
    ReparentToBaseSectorRoot(CarriedNode(object));
    const CKHkS08Enemy* enemy = static_cast<const CKHkS08Enemy*>(m_pEnemy);
    float x = enemy->m_unk8e4, y = enemy->m_unk8e8, z = enemy->m_unk8ec;
    if (enemy->m_unk8e4 == 0.0f && enemy->m_unk8e8 == 0.0f && enemy->m_unk8ec == 0.0f) {
        x = spot.m_pos.x;
        y = spot.m_pos.y;
        z = spot.m_pos.z;
    }
    RwFrame* frame = CarriedNode(object)->m_pRwFrame;
    frame->modelling.pos.z = z;
    frame->modelling.pos.x = x;
    frame->modelling.pos.y = y;
    frame->modelling.flags &= 0xfffdffffu;
    RwFrame_MarkDirty(frame);
    m_unk0c = nullptr;
    m_unk10 = nullptr;
    return 1;
}
