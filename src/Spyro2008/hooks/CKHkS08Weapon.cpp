// CKHkS08Weapon.cpp - reconstructed original translation unit 0x2b0ea0-0x2b2d08 (GAME_TOC1, main_toc1), 31 functions, 27 live.
// Primary class: CKHkS08Weapon  key 0x2902  category Hook  size 0xd0  vtable 0xb223f8
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x2b0ea0  CKHkS08Weapon_Delete
//   [x] 0x2b0ef0  CKHkS08Weapon_Pause
//   [x] 0x2b0ef8  CKHkS08Weapon_Resume
//   [x] 0x2b0f00  CKHkS08Weapon_vfC0
//   [x] 0x2b0f08  CKHkS08Weapon_vfCC  (CKHkS08Weapon.h: empty)
//   [ ] 0x2b0f10  CKHkS08Weapon_ResetRuntime_2  [dead]
//   [ ] 0x2b0f98  CKHkS08Weapon_InitStateMachine_maybe  [dead]
//   [ ] 0x2b0fd8  CKHkS08Weapon_InitDefaults_maybe  [dead]
//   [ ] 0x2b1020  CKHkS08Weapon_SyncFramePosition_maybe  [dead]
//   [x] 0x2b1088  CKHkS08Weapon_RecursiveRegistration  (IKHook's: the default)
//   [x] 0x2b10b0  CKHkS08Weapon_Destroy
//   [x] 0x2b10f8  CKHkS08Weapon_DeleteArray
//   [x] 0x2b1198  CKHkS08Weapon_Create
//   [ ] 0x2b1250  RegisterCKHkS08WeaponClass
//   [ ] 0x2b12d8  _GLOBAL__D_2b12d8
//   [ ] 0x2b12e8  _GLOBAL__I_2b12e8
//   [x] 0x2b12f8  CKHkS08Weapon_TakeFromPool_maybe
//   [x] 0x2b1500  CKHkS08Weapon_PostLoad
//   [x] 0x2b1558  CKHkS08Weapon_ReturnToPool_maybe
//   [x] 0x2b1688  CKHkS08Weapon_Stop
//   [x] 0x2b1748  CKHkS08Weapon_MessageProc  (returns 1: the default)
//   [x] 0x2b1750  CKHkS08Weapon_CreateArray
//   [x] 0x2b1870  CKHkS08Weapon_Load
//   [ ] 0x2b1a38  CKHkS08Weapon_Save
//   [x] 0x2b1be8  CKHkS08Weapon_Start
//   [x] 0x2b1c70  CKHkS08Weapon_State0
//   [x] 0x2b2218  CKHkS08Weapon_SetEjectVelocity_maybe
//   [x] 0x2b24e0  CKHkS08Weapon_State1
//   [x] 0x2b2870  CKHkS08Weapon_Update
//   [x] 0x2b2a70  CKHkS08Weapon_SetLanded_maybe
//   [x] 0x2b2bc0  CKHkS08Weapon_SetEjected_maybe
//
//   [ ] 0x9bcaa0  CKHkS08Weapon_IsKindOfClass  [inline]
//   [ ] 0x9bcae8  CKHkS08Weapon_GetClassType  [inline]
//   [ ] 0x9bcaf0  CKHkS08Weapon_GetClassID  [inline]
//   [ ] 0x9bcaf8  CKHkS08Weapon_Destructor  [inline]
//   [ ] 0x9bcb18  CKHkS08Weapon_DeletingDestructor  [inline]
#include "Spyro2008/hooks/CKHkS08Weapon.h"
#include "k2000/core/Ps3MemberFn.h"

#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"
#include "Spyro2008/groups/CKGrpS08Enemy.h"
#include "k2000/core/Stub.h"
#include "k2000/groups/IKBaseGroup.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/logic/CKCoreManager.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/CSGLeaf.h"
#include "Renderware/rwcore/RwCamera.h"
#include "Spyro2008/groups/CKGrpS08WeaponPool.h"
#include "Spyro2008/hooks/CKHkS08EnemyShared.h"
#include "crt/ppc_ops.h"
#include "crt/xatan.h"
#include "k2000/ai/CKHkDetectorGroup.h"
#include "k2000/groups/CKGrpFightZone.h"
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/misc/Mat4.h"
#include "k2000/scenegraph/CSGBranch.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/services/CKSrvCollision.h"
#include "k2000/system/IKTime.h"

namespace {
// 0x00c4092c (TOC +0x16d0): the reference count per weapon kind (read-only; only Load, Save and
// CKHkS08Weapon_State0 read it). Nine words before the next table (0x01010101 at index 9)_maybe.
const uint32_t kWeaponRefCount[9] = {0, 0, 0, 0, 2, 0, 0, 2, 0};
}  // namespace

// 0x002b1870 CKHkS08Weapon_Load
int32_t CKHkS08Weapon::Load(IKFile* file, int32_t type) {
    IKHook::Load(file, type);
    ReadU32LE(file, &m_unk20);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    uint32_t count = 0;
    ReadU32LE(file, &count);
    // BUG(original): the block is sized by the kind's table entry, the read by the file's count.
    m_apUnkAC = static_cast<IKSerializable**>(
        Mem_CallocAligned16(static_cast<uint32_t>(sizeof(IKSerializable*)), kWeaponRefCount[m_unk20]));
    IKFile_ReadObjectRefArray(file, m_apUnkAC, count);
    return 1;
}

// 0x002b10b0 CKHkS08Weapon_Destroy
void CKHkS08Weapon::Destroy() {
    if (m_apUnkAC == nullptr) return;
    Mem_FreeAligned16(m_apUnkAC);
    m_apUnkAC = nullptr;
}

// 0x0001d5c0 Group_TransferHook_maybe (CKCoreManager.cpp, not ported): xfork, a stub in CKHkS08Enemy_xforkB.cpp.
void GroupTransferHook(CKCoreManager* core, IKHook* hook, IKBaseGroup* to, IKBaseGroup* from, uint32_t flags);

namespace {
// DOTD: the weapon's state handlers by descriptor (k2000/core/Ps3MemberFn.h; the table Start builds at +0xc0).
Ps3MemberFnEntry<CKHkS08Weapon::StateFn> g_weaponStates[] = {
    {0x00b93f20u, &CKHkS08Weapon::State0, "CKHkS08Weapon_State0 0x2b1c70", false},
    {0x00b93f30u, &CKHkS08Weapon::State1, "CKHkS08Weapon_State1 0x2b24e0", false},
};
}  // namespace

uint8_t CKHkS08Weapon::CallState(const uint32_t pair[2], IKTime* clock, int32_t phase, uint8_t other) {
    StateFn fn = ResolvePs3MemberFn(g_weaponStates, pair, "CKHkS08Weapon state handler");
    if (fn == nullptr) return other;
    return (this->*fn)(clock, phase, other);
}

// 0x002b1be8 CKHkS08Weapon_Start
void CKHkS08Weapon::Start() {
    // The state engine: a table of two handlers at +0xc0 (the PS3 descriptors of CKHkS08Weapon_State0 / State1,
    // TOC +0x1684 / +0x1688) that +0xb8 points to; the current state byte pair 0xff / 2.
    // CallState maps them to the native handlers (g_weaponStates); Update runs them.
    m_unkC0[0] = 0x00b93f20u;
    m_unkC0[2] = 0x00b93f30u;
    m_unkC0[1] = 0;
    m_unkC0[3] = 0;
    m_unkB8 = &m_unkC0[0];
    m_unkBC = 0xff;
    m_unkBD = 2;
    m_GContactIn.m_fDeltaMax = 0.2f;     // TOC +0x168c (0x3e4ccccd)
    m_GContactIn.m_fObjectHeight = 1.0f;  // TOC +0x1690
    m_GContactIn.m_MasksOfGrdForTest[0] = 1;
    m_GContactIn.m_MasksOfGrdForTest[1] = 2;
    m_GContactInOut.m_i32FaceIndex = -1;
    m_GContactInOut.m_eContactStatus = 3;
    m_GContactInOut.m_ui8SectorNumber = 0;
    m_GContactInOut.m_pGround = nullptr;
    m_pOwnerB4 = nullptr;
}

void CKHkS08Weapon::SwitchState(uint8_t next) {
    uint32_t* rows = static_cast<uint32_t*>(m_unkB8);
    const uint8_t old = m_unkBC;
    if (old != 0xff) CallState(rows + old * 2, nullptr, 2, next);
    m_unkBC = next;
    CallState(rows + next * 2, nullptr, 1, old);
}

// 0x002b12f8 CKHkS08Weapon_TakeFromPool_maybe
void CKHkS08Weapon::TakeFromPool() {
    CKCoreManager* core = g_pEngine->m_coreManager;  // +0x2c
    CKGrpS08Enemy* enemies = static_cast<CKGrpS08Enemy*>(g_pEngine->m_gameManager->m_unk04[0]);
    IKBaseGroup* pool = static_cast<IKBaseGroup*>(enemies->m_vUnk180.m_pBlock[m_unk20]);
    for (IKHook* hook = *reinterpret_cast<IKHook**>(pool->GetMemberListHead()); hook != nullptr; hook = hook->m_pNextHook) {
        if (hook == this) {
            // 0x0001d5c0 Group_TransferHook_maybe(core, this, weapon group, pool, 0)
            GroupTransferHook(core, this, static_cast<IKBaseGroup*>(enemies->m_pUnk190), pool, 0);
            break;
        }
    }
    m_landedAB = 0;
    m_inHandA8 = 1;
    m_unkA9 = 0;
    const uint8_t old = m_unkBC;
    if (old != 0xff) CallState(static_cast<uint32_t*>(m_unkB8) + old * 2, nullptr, 2, 0xff);
    m_unkBC = 0xff;
    SetObjectActiveInContext(core, this, 1, static_cast<IKBaseGroup*>(enemies->m_pUnk190));  // 0x0001cb10
    CSGLeaf* node = static_cast<CSGLeaf*>(m_pKGLObject);
    node->m_sgProperties &= 0xfffffffbu;
}

// 0x002b1558 CKHkS08Weapon_ReturnToPool_maybe
void CKHkS08Weapon::ReturnToPool() {
    CKCoreManager* core = g_pEngine->m_coreManager;  // +0x2c
    CKGrpS08Enemy* enemies = static_cast<CKGrpS08Enemy*>(g_pEngine->m_gameManager->m_unk04[0]);
    IKBaseGroup* weapons = static_cast<IKBaseGroup*>(enemies->m_pUnk190);
    SetObjectActiveInContext(core, this, 0, weapons);  // 0x0001cb10
    for (IKHook* hook = *reinterpret_cast<IKHook**>(weapons->GetMemberListHead()); hook != nullptr; hook = hook->m_pNextHook) {
        if (hook == this) {
            // 0x0001d5c0 Group_TransferHook_maybe(core, this, the kind's pool, weapon group, 0)
            GroupTransferHook(core, this, static_cast<IKBaseGroup*>(enemies->m_vUnk180.m_pBlock[m_unk20]), weapons, 0);
            break;
        }
    }
    CSGLeaf* node = static_cast<CSGLeaf*>(m_pKGLObject);
    node->m_sgProperties = (node->m_sgProperties & 0xfffffffbu) | 4u;
    m_landedAB = 0;
    m_ejectedAA = 0;
}

// 0x002b2a70 CKHkS08Weapon_SetLanded_maybe
void CKHkS08Weapon::SetLanded(uint8_t landed) {
    m_landedAB = landed;
    if (landed != 0) SwitchState(1);
}

// 0x002b2bc0 CKHkS08Weapon_SetEjected_maybe
void CKHkS08Weapon::SetEjected(uint8_t ejected) {
    m_ejectedAA = ejected;
    if (ejected != 0) SwitchState(0);
}

namespace {
// The weapon's kind pool (the enemy group's +0x180 references, by the kind +0x20).
CKGrpS08WeaponPool* KindPool(const CKHkS08Weapon* weapon) {
    CKGrpS08Enemy* enemies = static_cast<CKGrpS08Enemy*>(g_pEngine->m_gameManager->m_unk04[0]);
    return static_cast<CKGrpS08WeaponPool*>(enemies->m_vUnk180.m_pBlock[weapon->m_unk20]);
}
RwFrame* NodeFrame(const CKHkS08Weapon* weapon) { return static_cast<CSGMovable*>(weapon->m_pKGLObject)->m_pRwFrame; }
// The node's modelling position from +0x24, flag 0x20000 cleared, the frame marked dirty.
void PlaceNode(CKHkS08Weapon* weapon) {
    RwFrame* frame = NodeFrame(weapon);
    frame->modelling.pos.z = weapon->m_v3Position.z;
    frame->modelling.pos.x = weapon->m_v3Position.x;
    frame->modelling.pos.y = weapon->m_v3Position.y;
    frame->modelling.flags &= 0xfffdffffu;
    RwFrame_MarkDirty(frame);  // 0x00010698
}
}  // namespace

// 0x002b1500 CKHkS08Weapon_PostLoad
int32_t CKHkS08Weapon::PostLoad(int32_t type) {
    PostLoadLife(type);  // 0x00019f68 IKLife_PostLoad
    CSGLeaf* node = static_cast<CSGLeaf*>(m_pKGLObject);
    node->m_sgProperties = (node->m_sgProperties & 0xfffffffbu) | 4u;
    return 1;
}

// 0x002b1688 CKHkS08Weapon_Stop
void CKHkS08Weapon::Stop() {
    CSGLeaf* node = static_cast<CSGLeaf*>(m_pKGLObject);
    CSGBranch* root = static_cast<CSGBranch*>(g_pEngine->m_dynamicSceneRoot);
    if (static_cast<IKSerializable*>(node->m_pParent) == static_cast<IKSerializable*>(root)) return;
    if (node->m_pParent != nullptr) node->m_pParent->RemoveChild(node);  // vt+0x78
    root->AddChild(static_cast<CSGLeaf*>(m_pKGLObject));                 // vt+0x70
}

// 0x002b2870 CKHkS08Weapon_Update
void CKHkS08Weapon::Update(IKTime* frameClock) {
    uint32_t* rows = static_cast<uint32_t*>(m_unkB8);
    const uint8_t state = m_unkBC;
    if (state == 0xff) return;
    const uint8_t next = CallState(rows + state * 2, frameClock, 0, state);
    const uint8_t now = m_unkBC;
    if (next == now) return;
    if (now != 0xff) CallState(rows + now * 2, frameClock, 2, next);
    m_unkBC = next;
    if (next != 0xff) CallState(rows + next * 2, frameClock, 1, now);
}

// 0x002b1c70 CKHkS08Weapon_State0
uint8_t CKHkS08Weapon::State0(IKTime* clock, int32_t phase, uint8_t /*other*/) {
    if (phase == 1) {
        RwFrame* frame = NodeFrame(this);
        m_v3Position = CVector3{frame->modelling.pos.x, frame->modelling.pos.y, frame->modelling.pos.z};
        m_unk30 = 0.0f;
        m_fFlightTime = 0.0f;
        // The cross product of the eject velocity with y (0x00c50d40), normalised; then replaced by the node's right.
        const CVector3& e = m_v3EjectVelocity;
        const CVector3& y = enemy::kAxisY;
        m_v3SpinAxis.x = ppc::fmsubs(e.y, y.z, e.z * y.y);
        m_v3SpinAxis.y = ppc::fmsubs(e.z, y.x, e.x * y.z);
        m_v3SpinAxis.z = ppc::fmsubs(e.x, y.y, e.y * y.x);
        const float length = static_cast<float>(enemy::MathSqrtf(ppc::fmadds(
            m_v3SpinAxis.z, m_v3SpinAxis.z, ppc::fmadds(m_v3SpinAxis.x, m_v3SpinAxis.x, m_v3SpinAxis.y * m_v3SpinAxis.y))));
        if (length != 0.0f) {
            const float k = 1.0f / length;  // TOC +0x1690
            m_v3SpinAxis.z = k * m_v3SpinAxis.z;
            m_v3SpinAxis.x = k * m_v3SpinAxis.x;
            m_v3SpinAxis.y = k * m_v3SpinAxis.y;
        }
        const RwV3d& right = NodeFrame(this)->modelling.right;
        m_v3SpinAxis = CVector3{right.x, right.y, right.z};
        m_v3Velocity = CVector3{0.0f, 0.0f, 0.0f};
        m_v3EjectVelocity.y = -m_v3EjectVelocity.y;
        return 0;
    }
    if (phase == 2) {
        m_ejectedAA = 0;
        return 0;
    }
    if (phase != 0) return 0;
    CKGrpS08Enemy* enemies = static_cast<CKGrpS08Enemy*>(g_pEngine->m_gameManager->m_unk04[0]);
    const CKHkDetectorGroup* zone =
        static_cast<const CKHkDetectorGroup*>(enemies->m_pCurrentFightZone->m_pUnk30);  // +0x30 -> +0x30
    const CKGrpS08WeaponPool* pool = KindPool(this);
    if (zone->IsTriggered(&m_v3Position.x) != 0 && kWeaponRefCount[m_unk20] == 2 &&  // vt+0xc4
        m_apUnkAC[0] != nullptr && m_apUnkAC[1] != nullptr) {
        CKSrvCollision* collision = static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision);
        bool land = false;
        bool lost = false;
        for (int32_t i = 0; i < 2 && !land && !lost; ++i) {
            CVector3 at{};
            static_cast<CSGHotSpot*>(m_apUnkAC[i])->GetWorldPosition(&at);              // 0x000ce790
            collision->GroundProbePoints(&m_GContactIn, &m_GContactInOut, &at.x, 1);  // 0x00196540
            const int32_t status = static_cast<int32_t>(m_GContactInOut.m_eContactStatus);
            if (status >= 1 && status <= 2) land = true;
            else if (status == 3) lost = true;
        }
        if (land) {
            // 0x2b21a8: on the ground.
            m_v3Position.y = m_v3Position.y + m_GContactInOut.m_fdH;
            PlaceNode(this);
            m_landedAB = 1;
            return 1;
        }
        if (!lost) {
            // 0x2b2008: the flight step.
            const float dt = clock->m_afDeltaTime[0];
            m_fFlightTime = dt + m_fFlightTime;
            const float gravity = -pool->m_unk30;
            m_v3Accel = CVector3{0.0f, gravity, 0.0f};
            if (m_fFlightTime < m_fPushTime) {
                const float k = 1.0f / pool->m_unk2c;
                const CVector3 e = m_v3EjectVelocity;
                m_v3Accel.z = ppc::fmadds(k, e.z, 0.0f);
                m_v3Accel.y = ppc::fmadds(k, e.y, gravity);
                m_v3Accel.x = ppc::fmadds(k, e.x, 0.0f);
            }
            m_v3Velocity.x = ppc::fmadds(dt, m_v3Accel.x, m_v3Velocity.x);
            m_v3Velocity.y = ppc::fmadds(dt, m_v3Accel.y, m_v3Velocity.y);
            m_v3Velocity.z = ppc::fmadds(dt, m_v3Accel.z, m_v3Velocity.z);
            m_v3Position.x = ppc::fmadds(dt, m_v3Velocity.x, m_v3Position.x);
            m_v3Position.y = ppc::fmadds(dt, m_v3Velocity.y, m_v3Position.y);
            m_v3Position.z = ppc::fmadds(dt, m_v3Velocity.z, m_v3Position.z);
            // The spins about the node's own right, up and at (TOC +0x16f0 57.29578: degrees).
            CMatrix34* m = reinterpret_cast<CMatrix34*>(&NodeFrame(this)->modelling);
            Mat4_RotateInPlace(m, &m->m_right, dt * pool->m_unk34 * 57.2957802f);  // 0x00240498
            Mat4_RotateInPlace(m, &m->m_up, dt * pool->m_unk38 * 57.2957802f);
            Mat4_RotateInPlace(m, &m->m_at, dt * pool->m_unk3c * 57.2957802f);
            PlaceNode(this);
            return 0;
        }
    }
    // 0x2b1d48: back to the pool.
    ReturnToPool();  // vt+0xc8
    VfCC();          // vt+0xcc
    return 0xff;
}

// 0x002b24e0 CKHkS08Weapon_State1
uint8_t CKHkS08Weapon::State1(IKTime* clock, int32_t phase, uint8_t /*other*/) {
    if (phase == 0) {
        if (m_inHandA8 != 0) return 0xff;
        m_fGroundTime = m_fGroundTime + clock->m_afDeltaTime[0];
        CKGrpS08Enemy* enemies = static_cast<CKGrpS08Enemy*>(g_pEngine->m_gameManager->m_unk04[0]);
        const CKGrpS08WeaponPool* pool = KindPool(this);
        const uint32_t grounded = enemies->CountGroundedWeapons();  // 0x00266ea0
        if (!(grounded > enemies->m_unk194) && !(m_fGroundTime >= pool->m_unk44)) return 1;
        ReturnToPool();  // vt+0xc8
        VfCC();          // vt+0xcc
        return 0xff;
    }
    if (phase != 1) return 1;
    // Enter: on the ground (status 0 lowers by the height, 1..2 raise), laid flat.
    CKSrvCollision* collision = static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision);
    collision->GroundProbePoints(&m_GContactIn, &m_GContactInOut, &m_v3Position.x, 1);  // 0x00196540
    const int32_t status = static_cast<int32_t>(m_GContactInOut.m_eContactStatus);
    if (status == 0) {
        m_v3Position.y = m_v3Position.y - m_GContactInOut.m_fdH;
    } else if (status > 0 && status <= 2) {
        m_v3Position.y = m_v3Position.y + m_GContactInOut.m_fdH;
    }
    RwMatrix& m = NodeFrame(this)->modelling;
    m.right = RwV3d{enemy::kAxisY.x, enemy::kAxisY.y, enemy::kAxisY.z};  // 0x00c50d40
    m.flags &= 0xfffdfffcu;
    float ax = m.at.x;
    float az = m.at.z;
    float ay = 0.0f;
    float xx = ax * ax;
    const float flat = static_cast<float>(enemy::MathSqrtf(ppc::fmadds(az, az, xx + 0.0f)));  // fadds, fmadds
    if (flat != 0.0f) {
        const float k = 1.0f / flat;
        ax = ax * k;
        az = az * k;
        ay = k * 0.0f;
        xx = ax * ax;
    }
    m.at.y = ay;
    m.at.x = ax;
    m.at.z = az;
    m.flags &= 0xfffdfffcu;
    float ux = -az;
    float uy = 0.0f;
    float uz = ax;
    const float side = static_cast<float>(enemy::MathSqrtf(ppc::fmadds(ux, ux, 0.0f) + xx));
    if (side != 0.0f) {
        const float k = 1.0f / side;
        uz = k * ax;
        ux = ux * k;
        uy = k * 0.0f;
    }
    m.up.x = ux;
    m.up.y = uy;
    m.up.z = uz;
    m.flags &= 0xfffdfffcu;
    PlaceNode(this);
    m_fGroundTime = 0.0f;
    return 1;
}

// 0x002b2218 CKHkS08Weapon_SetEjectVelocity_maybe. The cone test: the angle (acos of the clamped dot product) between
// the flat direction and the direction; below the pool's +0x40 the direction is the flat one turned up by +0x40
// (a basis right (-z, 0, x), up y, at the flat direction, Mat4_RotateLocalXDeg by -57.29578 x +0x40).
void CKHkS08Weapon::SetEjectVelocity(const CVector3* direction) {
    const float x = direction->x;
    const float y = direction->y;
    const float z = direction->z;
    const float xx = x * x;
    const float zz = z * z;
    const CKGrpS08WeaponPool* pool = KindPool(this);
    m_v3EjectVelocity = CVector3{x, y, z};
    // The flat direction (fadds: x x + 0, + z z).
    float fx = x, fy = 0.0f, fz = z;
    const float flat = static_cast<float>(enemy::MathSqrtf((xx + 0.0f) + zz));
    if (flat != 0.0f) {
        const float k = 1.0f / flat;
        fy = k * 0.0f;
        fz = z * k;
        fx = x * k;
    }
    // The unit direction.
    float dx = x, dy = y, dz = z;
    const float length = static_cast<float>(enemy::MathSqrtf(zz + ppc::fmadds(y, y, xx)));
    if (length != 0.0f) {
        const float k = 1.0f / length;
        dz = z * k;
        dx = x * k;
        dy = y * k;
    }
    float dot = ppc::fmadds(fz, dz, ppc::fmadds(fx, dx, fy * dy));
    if (dot <= -1.0f) {  // TOC +0x16b0; cror lt|eq: a NaN goes on (both tests false)
        dot = -1.0f;
    } else if (dot >= 1.0f) {
        dot = 1.0f;
    }
    if (pool->m_unk40 > crt::Acosf(dot)) {  // 0x0098e1a0 Math_Acosf
        alignas(16) CMatrix34 basis;
        // BUG(original): the basis's position and pads are the stack's (not read by the rotation).
        basis.m_pos = CVector3{0.0f, 0.0f, 0.0f};
        basis.m_ui32Flags = 0;
        basis.m_ui32pad1 = 0;
        basis.m_ui32pad2 = 0;
        basis.m_ui32pad3 = 0;
        basis.m_at = CVector3{fx, fy, fz};
        basis.m_ui32Flags &= 0xfffdfffcu;  // DOTD: the original clears these bits of the stack word
        basis.m_up = enemy::kAxisY;        // 0x00c50d40
        basis.m_right = CVector3{-fz, 0.0f, fx};
        Mat4_RotateLocalXDeg(pool->m_unk40 * -57.2957802f, &basis);  // 0x00241118, TOC +0x16f8
        m_v3EjectVelocity = basis.m_at;
    }
    // 0x2b236c: unit length, at the pool's speed backwards.
    CVector3& v = m_v3EjectVelocity;
    float vx = v.x, vy = v.y, vz = v.z;
    const float span = static_cast<float>(enemy::MathSqrtf(ppc::fmadds(vz, vz, ppc::fmadds(vx, vx, vy * vy))));
    if (span != 0.0f) {
        const float k = 1.0f / span;
        vz = k * vz;
        vx = k * vx;
        vy = k * vy;
        v = CVector3{vx, vy, vz};
    }
    const float speed = -pool->m_unk48;
    v.z = speed * vz;
    v.x = speed * vx;
    v.y = speed * vy;
    m_fPushTime = pool->m_unk4c;
}
