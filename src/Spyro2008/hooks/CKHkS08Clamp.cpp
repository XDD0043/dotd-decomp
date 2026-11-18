// CKHkS08Clamp.cpp - reconstructed original translation unit 0x48c7a0-0x4916f8 (GAME_TOC1, main_toc1), 55 functions, 44 live.
// Primary class: CKHkS08Clamp  key 0x2c82  category Hook  size 0x130  vtable 0xb27ee8
// Other owners: GetSpyroCynderMidpoint (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x48c7a0  CKHkS08Clamp_Delete
//   [ ] 0x48c7f0  CKHkS08Clamp_UpdateSegmentVolumeFromNode_maybe  [dead]
//   [ ] 0x48c8e8  FUN_0048c8e8  [dead]
//   [ ] 0x48c958  CKHkS08Clamp_ReflectVelocity_maybe  [dead]
//   [ ] 0x48c9d8  CKHkS08Clamp_InitCollisionVolume_maybe  [dead]
//   [ ] 0x48ca50  CKHkS08Clamp_IsPointInsideQuadXZ_maybe  [dead]
//   [x] 0x48cbb0  CKHkS08Clamp_SetDefaultState
//   [x] 0x48cbc0  CKHkS08Clamp_vfC8  (header: ApplyStatePreset)
//   [ ] 0x48cbc8  CKHkS08Clamp_SpawnFxAtNodePosition_maybe  [dead]
//   [ ] 0x48cc10  GetSpyroCynderMidpoint_maybe  [dead: no pointer to its descriptor 0xbc3838, no call]
//   [x] 0x48cd00  CKHkS08Clamp_GetDistSqToHeroLink_maybe
//   [x] 0x48cef8  CKHkS08Clamp_UpdateRotationBlend_maybe
//   [ ] 0x48d0e8  CKHkS08Clamp_SpinAroundAxis_maybe  [dead]
//   [x] 0x48d180  CKHkS08Clamp_Resume
//   [x] 0x48d1a8  CKHkS08Clamp_Pause
//   [x] 0x48d1d0  CKHkS08Clamp_GetInfo  (the actor base's 1, folded: CKHkActorBase's)
//   [ ] 0x48d220  CKHkS08Clamp_Save
//   [x] 0x48d248  CKHkS08Clamp_RecursiveRegistration  (inherited: CKHkActorBase's)
//   [x] 0x48d270  CKHkS08Clamp_Destroy  (header)
//   [x] 0x48d2b8  CKHkS08Clamp_Construct  [dead]
//   [x] 0x48d330  CKHkS08Clamp_DeleteArray
//   [ ] 0x48d3d0  CKHkS08Clamp_Destructor_2  [dead]
//   [ ] 0x48d448  CKHkS08Clamp_Construct_2  [dead]
//   [ ] 0x48d4c0  RegisterCKHkS08ClampClass
//   [ ] 0x48d548  _GLOBAL__D_48d548
//   [ ] 0x48d558  _GLOBAL__I_48d558
//   [x] 0x48d568  CKHkS08Clamp_IsInState2
//   [x] 0x48d580  CKHkS08Clamp_State3_Inactive_maybe
//   [x] 0x48d648  CKHkS08Clamp_OnActivate
//   [x] 0x48d6e0  CKHkS08Clamp_DeletingDestructor  (the destructor; delete)
//   [x] 0x48d768  CKHkS08Clamp_Destructor
//   [x] 0x48d7e0  CKHkS08Clamp_vf94  (empty, as IKLife's vt+0x94 (inherited))
//   [x] 0x48d7e8  CKHkS08Clamp_vf98  (empty, as IKLife's vt+0x98 (inherited))
//   [x] 0x48d7f0  CKHkS08Clamp_OnContactHit_maybe
//   [x] 0x48d9c8  CKHkS08Clamp_ProcessContacts_maybe
//   [x] 0x48dbc0  CKHkS08Clamp_PostLoad
//   [ ] 0x48dcb8  CKHkS08Clamp_UpdateMotionAndSpin_maybe  [dead]
//   [x] 0x48ddc8  CKHkS08Clamp_PlaySound1AndSpawnFx_maybe  (PlaySound1AndSpawnFx (callers: the clamp gun, not ported))
//   [x] 0x48df08  CKHkS08Clamp_State1
//   [x] 0x48e140  CKHkS08Clamp_CreateArray
//   [x] 0x48e240  CKHkS08Clamp_Create
//   [x] 0x48e2c8  CKHkS08Clamp_UpdateGroundImpact_maybe  (UpdateGroundImpact)
//   [x] 0x48e828  CKHkS08Clamp_State2
//   [x] 0x48ee18  CKHkS08Clamp_Load
//   [x] 0x48f330  CKHkS08Clamp_LaunchRandomDirection_maybe  (LaunchRandomDirection)
//   [x] 0x48f8d8  CKHkS08Clamp_Update
//   [x] 0x48fb80  CKHkS08Clamp_EnterState1_maybe  (EnterState1 (caller CKGrpS08Clamp_MessageProc 0x491dc8, not ported))
//   [x] 0x48fcc8  CKHkS08Clamp_EnterState3_maybe  (EnterState3 (caller CKHkS08ClampGun_ReturnClampToPool_maybe 0x491ba0, not ported))
//   [x] 0x48fe08  CKHkS08Clamp_MessageProc
//   [x] 0x490008  CKHkS08Clamp_Launch_maybe  (Launch (caller CKHkS08ClampGun_FireShot_maybe, not ported))
//   [x] 0x490210  CKHkS08Clamp_Restart
//   [x] 0x4903f0  CKHkS08Clamp_UpdateCollisionVolumesFromBones_maybe  (SetTrailActive)
//   [x] 0x490cc8  CKHkS08Clamp_State0  (State0, in the state table)
//   [x] 0x491338  CKHkS08Clamp_Stop
//   [x] 0x4913d8  CKHkS08Clamp_Start
//
//   [ ] 0x9c4940  CKHkS08Clamp_IsKindOfClass  [inline]
//   [ ] 0x9c4998  CKHkS08Clamp_GetClassType  [inline]
//   [ ] 0x9c49a0  CKHkS08Clamp_GetClassID  [inline]
#include "Spyro2008/hooks/CKHkS08Clamp.h"
#include "platform/fps.h"

#include "Renderware/rpprtstd/RpPrtStd.h"
#include "Renderware/rwcore/RwCamera.h"
#include "Renderware/rwcore/RwMatrix.h"
#include "Spyro2008/groups/CKGrpS08Clamp.h"
#include "Spyro2008/groups/CKGrpS08Hero.h"
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "k2000/core/Ps3MemberFn.h"
#include "k2000/core/Stub.h"
#include "k2000/dictionaries/CKSoundDictionaryID.h"
#include "k2000/logic/CKCoreManager.h"
#include "k2000/logic/sound/CKSound.h"
#include "k2000/scenegraph/CParticlesNodeFx.h"
#include "k2000/scenegraph/CSGBranch.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/scenegraph/CTrailNodeFx.h"
#include "k2000/math/Math.h"
#include "k2000/math/Quat.h"
#include "crt/xtanf.h"
#include "k2000/services/CKSrvCollision.h"
#include "k2000/system/IKTime.h"
#include "crt/ppc_ops.h"
#include "platform/log.h"

#include <cmath>
#include "Spyro2008/groups/CKGrpS08Meca.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/IKBoundingVolume.h"

// 0x0048dbc0 CKHkS08Clamp_PostLoad: the clamp group (the game manager's third reference, a CKGrpS08Meca, its
// +0x40) becomes the context, two new matrices, and the collision sphere at +0x2c is set up as this hook's
// (owner type 1, owner this, bit 7 of its info byte, the radius from +0xe0 when that is positive, else 0.001).
int32_t CKHkS08Clamp::PostLoad(int32_t type) {
    CKHkActorBase::PostLoad(type);  // 0x003f6e70
    m_pUnk24 = static_cast<CKGrpS08Meca*>(static_cast<CDefaultGameManager*>(g_pEngine->m_gameManager)->m_unk04[2])
                   ->m_pUnk40;
    m_pUnk40 = reinterpret_cast<CMatrix34*>(RwMatrixCreate());  // RwMatrixCreate_Thunk 0x23fa68
    m_pUnk3C = reinterpret_cast<CMatrix34*>(RwMatrixCreate());
    IKBoundingVolume* volume = static_cast<IKBoundingVolume*>(m_pUnk2C);
    volume->m_ui16PropertiesFlags = 0;
    volume->m_ui8OwnerType = 1;  // (the original stores 0, then 1)
    volume->m_pOwner = this;
    volume->m_ba8Infos = (volume->m_ba8Infos & 0x7f) | 0x80;
    if (0.0f < m_fUnkE0) {
        volume->m_fRadius = m_fUnkE0;
    } else {
        volume->m_fRadius = 0.001f;  // TOC1 +0x1788: 0x3a83126f
    }
    m_unk20 = m_unk20 & 0x00ffffffu;  // the byte at +0x20
    return 1;
}

// 0x0048ee18 CKHkS08Clamp_Load: the actor base, then the level data (type 0 only).
int32_t CKHkS08Clamp::Load(IKFile* file, int32_t type) {
    CKHkActorBase::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        ReadF32LE(file, &m_fUnk38);
        ReadF32LE(file, &m_fUnkDC);
        ReadF32LE(file, &m_fUnkE0);
        ReadF32LE(file, &m_fUnk78);
        ReadF32LE(file, &m_fUnk74);
        ReadF32LE(file, &m_fUnk7C);
        ReadF32LE(file, &m_fUnk8C);
        ReadF32LE(file, &m_fUnk90);
        ReadF32LE(file, &m_fUnkE4);
        IKFile_ReadRef(file, &m_pUnk2C);
        ReadF32LE(file, &m_fUnk94);
        ReadF32LE(file, &m_fUnk44);
        IKFile_ReadRef(file, &m_pUnkEC);
        IKFile_ReadRef(file, &m_pUnkF8);
        ReadF32LE(file, &m_fUnkFC);
        ReadU32LE(file, &m_unk100);
        ReadU8(file, &m_unk104);
    }
    return 1;
}

namespace {
// DOTD: the state handlers by descriptor (k2000/core/Ps3MemberFn.h; the table Start fills at +0x110).
Ps3MemberFnEntry<CKHkS08Clamp::StateFn> g_clampStates[] = {
    {0x00bc3b28u, &CKHkS08Clamp::State0, "CKHkS08Clamp_State0 0x490cc8", false},
    {0x00bc39c8u, &CKHkS08Clamp::State1, "CKHkS08Clamp_State1 0x48df08", false},
    {0x00bc39f0u, &CKHkS08Clamp::State2, "CKHkS08Clamp_State2 0x48e828", false},
    {0x00bc38f0u, &CKHkS08Clamp::State3, "CKHkS08Clamp_State3_Inactive_maybe 0x48d580", false},
};

CKGrpS08Hero* HeroGroup() { return static_cast<CKGrpS08Hero*>(g_pEngine->m_gameManager->m_unk04[1]); }
CSGMovable* NodeOf(const CKHkS08Clamp* clamp) { return static_cast<CSGMovable*>(clamp->m_pKGLObject); }
// The byte at +0x3c of the clamp group (the word's top byte): set while a clamp holds the heroes.
void SetGroupHolding(CKHkS08Clamp* clamp, uint32_t value) {
    CKGrpS08Clamp* group = static_cast<CKGrpS08Clamp*>(clamp->m_pUnk24);
    group->m_unk3c = (group->m_unk3c & 0x00ffffffu) | (value << 24);
}
uint32_t GroupHolding(const CKHkS08Clamp* clamp) { return static_cast<CKGrpS08Clamp*>(clamp->m_pUnk24)->m_unk3c >> 24; }
// Sound `index` of the clamp's dictionary (+0xec): its +0x5c bit 6 cleared, the loop set, at the node, played.
void PlayClampSound(const CKHkS08Clamp* clamp, uint32_t index, int32_t loop) {
    CKSoundDictionaryID* sounds = static_cast<CKSoundDictionaryID*>(clamp->m_pUnkEC);
    if (sounds->GetSound(index) == nullptr) return;  // 0x00112bc0
    sounds->GetSound(index)->m_SoundFlags &= 0xffffffbfu;
    sounds->GetSound(index)->SetLoop(loop);  // 0x00110fd0
    const RwV3d& p = FrameLtm(NodeOf(clamp)->m_pRwFrame)->pos;  // RwFrame +0x80
    const CVector3 position = {p.x, p.y, p.z};
    sounds->GetSound(index)->SetPosition(&position);  // 0x00110fa0
    sounds->GetSound(index)->Play(0.0f);              // 0x00111230
}
const RwV3d& HeroPosition(CKGrpS08Hero* group, uint32_t index) {
    CKHkS08Hero* hero = static_cast<CKHkS08Hero*>(group->m_apHeros[index]);  // GetHeroByDragonIndex 0x2ca080
    return FrameLtm(static_cast<CSGMovable*>(hero->m_pKGLObject)->m_pRwFrame)->pos;
}
}  // namespace

// CKHkS08Clamp_SpawnFx_maybe 0x491938 as State1 / State2 call it: the clamp group's effect at the node's position
// (RwFrame +0x40, the modelling matrix's), owned by the clamp (+0xf0 is passed too, unread).
void CKHkS08Clamp::SpawnFx() {
    const RwV3d& p = NodeOf(this)->m_pRwFrame->modelling.pos;
    const CVector3 position = {p.x, p.y, p.z};
    static_cast<CKGrpS08Clamp*>(m_pUnk24)->SpawnClampFx(this, &position);
}

uint8_t CKHkS08Clamp::CallState(uint8_t state, IKTime* clock, int32_t phase, uint8_t other) {
    StateFn fn = ResolvePs3MemberFn(g_clampStates, &m_pStateTable[state * 2u], "CKHkS08Clamp state handler");
    if (fn == nullptr) return other;
    return (this->*fn)(clock, phase, other);
}

// 0x004913d8 CKHkS08Clamp_Start: the state table; a clamp neither pre-set (+0x104) nor disabled (the byte at +0x20)
// is shown, woken in its group's context and starts in state 1 (waiting for the heroes), else in state 3; its
// collision volume on.
// 0x00490210 CKHkS08Clamp_Restart (vt+0x54): a clamp that is not broken (+0x104) or off (the byte +0x20) is shown, woken in
// its group's bundle and put back into state 1 (the current state left with no clock towards 1, state 1 entered);
// +0xf4 cleared.
void CKHkS08Clamp::Restart() {
    if (m_unk104 == 0 && (m_unk20 >> 24) == 0) {
        CSGLeaf* node = static_cast<CSGLeaf*>(m_pKGLObject);
        node->m_sgProperties &= 0xfffffffbu;
        SetObjectActiveInContext(g_pEngine->m_coreManager, this, 1, static_cast<IKBaseGroup*>(static_cast<CKGrpS08Clamp*>(m_pUnk24)));  // 0x0001cb10
        const uint8_t previous = m_ui8State;
        if (previous != 0xff) CallState(previous, nullptr, 2, 1);
        m_ui8State = 1;
        CallState(1, nullptr, 1, previous);
    }
    m_bUnkF4 = 0;
}

void CKHkS08Clamp::Start() {
    CKHkActorBase::Start();  // 0x003f6e48 (empty)
    const CVector3 kNull = {0.0f, 0.0f, 0.0f};  // g_nullVector 0xc50d64 (TOC1 +0x5e88)
    m_vUnk4c = kNull;
    m_vUnk64 = kNull;
    m_vUnk58 = kNull;
    m_aStateTable[6] = 0x00bc38f0u;  // State3 (+0x128)
    m_aStateTable[0] = 0x00bc3b28u;  // State0 (+0x110)
    m_aStateTable[2] = 0x00bc39c8u;  // State1 (+0x118)
    m_aStateTable[4] = 0x00bc39f0u;  // State2 (+0x120)
    m_aStateTable[7] = 0;
    m_aStateTable[1] = 0;
    m_aStateTable[3] = 0;
    m_aStateTable[5] = 0;
    m_ui8State = 0xff;
    m_ui8NbStates = 4;
    m_pStateTable = m_aStateTable;
    if (m_unk104 == 0 && (m_unk20 >> 24) == 0) {
        CSGLeaf* node = static_cast<CSGLeaf*>(m_pKGLObject);
        node->m_sgProperties &= 0xfffffffbu;
        SetObjectActiveInContext(g_pEngine->m_coreManager, this, 1, static_cast<IKBaseGroup*>(static_cast<CKGrpS08Clamp*>(m_pUnk24)));  // 0x0001cb10
        const uint8_t previous = m_ui8State;  // 0xff: nothing to leave
        m_ui8State = 1;
        CallState(1, nullptr, 1, previous);
    } else {
        m_ui8State = 3;
        CallState(3, nullptr, 1, 0xff);
    }
    SetTrailActive(1);  // 0x004903f0
    static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision)->EnableVolume(static_cast<IKBoundingVolume*>(m_pUnk2C));  // 0x00192090
    m_bUnkF4 = 0;
}

// 0x0048f8d8 CKHkS08Clamp_Update: while not off, the clamp's position is queued on its group's particle node (64
// points at most); then the state machine (the state's frame, and on a change the old state left, the new one entered).
void CKHkS08Clamp::Update(IKTime* clock) {
    if (m_ui8State != 3) {
        CParticlesNodeFx* fx = static_cast<CParticlesNodeFx*>(static_cast<CKGrpS08Clamp*>(m_pUnk24)->m_pUnk48);
        if (fx->m_ui8NbActivePoints < 0x40) {
            const RwV3d& p = NodeOf(this)->m_pRwFrame->modelling.pos;  // RwFrame +0x40
            RwV3d& point = fx->m_pAdvEmtPointList->pointList[fx->m_ui8NbActivePoints];
            point.z = p.z;
            point.x = p.x;
            point.y = p.y;
            fx->m_sgProperties = (fx->m_sgProperties & 0xffffdfffu) | 0x2000u;
            fx->m_ui8NbActivePoints = static_cast<uint8_t>(fx->m_ui8NbActivePoints + 1);
        }
    }
    const uint8_t state = m_ui8State;
    if (state == 0xff) return;
    const uint8_t next = CallState(state, clock, 0, state);
    const uint8_t current = m_ui8State;
    if (next == current) return;
    if (current != 0xff) CallState(current, clock, 2, next);
    m_ui8State = next;
    if (next != 0xff) CallState(next, clock, 1, current);
}

// 0x0048d648 CKHkS08Clamp_OnActivate (vt+0xa0): the collision volume (+0x2c) put back under the clamp's node.
void CKHkS08Clamp::VfA0() {
    CSGBranch* node = static_cast<CSGBranch*>(m_pKGLObject);
    IKBoundingVolume* volume = static_cast<IKBoundingVolume*>(m_pUnk2C);
    if (volume->m_pParent != nullptr) node->RemoveChild(volume);  // vt+0x78
    node->AddChild(volume);                                       // vt+0x70
}

// 0x0048fe08 CKHkS08Clamp_MessageProc: 0x996 switches the clamp off (state 3).
int32_t CKHkS08Clamp::MessageProc(uint16_t message, void* data) {
    const int32_t base = CKHkActorBase::MessageProc(message, data);  // 0x003f7148
    int32_t own = 1;
    if (message == 0x996) {
        const uint8_t previous = m_ui8State;
        if (previous != 0xff) CallState(previous, nullptr, 2, 3);
        m_ui8State = 3;
        CallState(3, nullptr, 1, previous);
        own = 0;
    }
    if (base == 3 || own == 3) return 3;
    if (base == 2 || own == 2) return 2;
    if (base != 0) return own;
    return 0;
}

// 0x0048cd00 CKHkS08Clamp_GetDistSqToHeroLink_maybe
uint8_t CKHkS08Clamp::IsOnHeroLink() {
    CKGrpS08Hero* group = HeroGroup();
    if (group == nullptr) return 0;
    const RwV3d& a = HeroPosition(group, 0);
    const RwV3d& b = HeroPosition(group, 1);
    const RwV3d& c = FrameLtm(NodeOf(this)->m_pRwFrame)->pos;
    float dy = b.y - a.y;
    float dx = b.x - a.x;
    float dz = b.z - a.z;
    const float rx = c.x - a.x;
    const float rz = c.z - a.z;
    float length = std::sqrt(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));
    const float kZero = 0.0f;  // TOC1 +0x5e24
    if (length != kZero) {
        const float k = 1.0f / length;  // TOC1 +0x5e38
        dz = dz * k;
        dx = dx * k;
        dy = dy * k;
    } else {
        length = kZero;
    }
    const float radius = m_fUnkE4;
    // The clamp's offset from hero 0 has no height (0 for y).
    const float along = ppc::fmadds(rz, dz, ppc::fmadds(dx, rx, dy * kZero));
    if (length + radius < along) return 0;
    if (-radius > along) return 0;
    const float py = kZero - dy * along;
    const float px = rx - dx * along;
    const float pz = rz - dz * along;
    const float distance = ppc::fmadds(pz, pz, ppc::fmadds(px, px, py * py));
    return distance <= radius * radius ? 1 : 0;
}

// 0x0048df08 CKHkS08Clamp_State1: waiting until the heroes' link crosses the clamp while no other clamp holds them
// (then state 2).
uint8_t CKHkS08Clamp::State1(IKTime* clock, int32_t phase, uint8_t other) {
    if (phase == 1) {
        m_fBlendTime = 0.0f;
        m_fStateTime = 0.0f;
    } else if (phase == 2) {
        if (other == 3) SpawnFx();
    } else if (phase == 0) {
        if (m_unk104 != 0) {
            // A launched clamp (+0x104; LVL010 has no clamp gun to launch one): +0x34 counts the time; up to +0x38 the
            // node blends while +0xf4 is clear, past it (with +0xf4 clear) +0x28 gets 0x900, sound 1 plays, state 3.
            const float time = m_fStateTime + clock->m_afDeltaTime[0];  // +0x1c
            m_fStateTime = time;
            if (!(m_fUnk38 < time)) {  // bge
                if (m_bUnkF4 == 0) UpdateRotationBlend(clock);
            } else if (m_bUnkF4 == 0) {
                m_pUnk28->MessageProc(0x900, this);  // vt+0x1c
                m_bUnkF4 = 0;
                PlayClampSound(this, 1, 0);
                return 3;
            }
        }
        if (IsOnHeroLink() != 0 && GroupHolding(this) == 0) other = 2;
    }
    return other;
}

// 0x0048e828 CKHkS08Clamp_State2: holding the heroes. Entering: sound 4 (looping), the heroes' middle (+0x98, +0xa4),
// the clamp group's holding byte, the hero group's external lock, sound 2. Each frame: the held middle (+0xa4) moves
// toward the clamp by +0x94 (or reaches it) and is the tether's middle. Leaving: sound 4 stopped, the lock released,
// sound 1, the FX.
uint8_t CKHkS08Clamp::State2(IKTime* clock, int32_t phase, uint8_t other) {
    if (phase == 1) {
        PlayClampSound(this, 4, 1);
        m_bUnkE8 = 0;
        CKGrpS08Hero* group = HeroGroup();
        const RwV3d& a = HeroPosition(group, 0);
        const RwV3d& b = HeroPosition(group, 1);
        const float kHalf = 0.5f;  // TOC1 +0x5e1c
        const CVector3 middle = {(a.x + b.x) * kHalf, (a.y + b.y) * kHalf, (a.z + b.z) * kHalf};
        m_vHoldStart = middle;
        m_vHoldPosition = middle;
        SetGroupHolding(this, 1);
        HeroGroup()->AcquireExternalLock(this);  // 0x002d4d10
        PlayClampSound(this, 2, 0);
    } else if (phase == 2) {
        CKSoundDictionaryID* sounds = static_cast<CKSoundDictionaryID*>(m_pUnkEC);
        if (sounds->GetSound(4) != nullptr) sounds->GetSound(4)->Stop(0);  // 0x001111b0
        SetGroupHolding(this, 0);
        if (HeroGroup()->IsExternalLockFree() == 0) HeroGroup()->ReleaseExternalLock(this);  // 0x002d4c30, 0x002d4c40
        PlayClampSound(this, 1, 0);
        SpawnFx();
    } else if (phase == 0) {
        if (m_unk104 != 0) {
            // A launched clamp: the blend and the contacts while +0xf4 is clear; with +0xe8 set (a contact in state 2)
            // +0x28 gets 0x900, +0xf4 is cleared and the clamp goes off (3).
            if (m_bUnkF4 == 0) {
                UpdateRotationBlend(clock);
                ProcessContacts(clock);
            }
            if (m_bUnkE8 != 0) {
                m_pUnk28->MessageProc(0x900, this);  // vt+0x1c
                m_bUnkF4 = 0;                         // stb of the phase (0)
                return 3;
            }
        }
        const RwV3d& p = NodeOf(this)->m_pRwFrame->modelling.pos;  // RwFrame +0x40
        float dy = p.y - m_vHoldPosition.y;
        float dx = p.x - m_vHoldPosition.x;
        float dz = p.z - m_vHoldPosition.z;
        const float distanceSq = ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy));
        const float distance = std::sqrt(distanceSq);
        if (distance != 0.0f) {  // TOC1 +0x5e24
            const float k = 1.0f / distance;  // TOC1 +0x5e38
            dz = dz * k;
            dx = dx * k;
            dy = dy * k;
        }
        float speed = m_fUnk94;
        // --fps N (not in the original): +0x94 per 60 Hz frame, so the pull keeps its 60 fps speed.
        if (dotd::fps::Unlocked()) speed = speed * dotd::fps::Scale();
        const float sy = speed * dy;
        const float sx = speed * dx;
        const float sz = speed * dz;
        CVector3 position;
        if (ppc::fmadds(sz, sz, ppc::fmadds(sx, sx, sy * sy)) >= distanceSq) {
            position = {p.x, p.y, p.z};
        } else {
            position = {sx + m_vHoldPosition.x, sy + m_vHoldPosition.y, sz + m_vHoldPosition.z};
        }
        m_vHoldPosition = position;
        HeroGroup()->SetExternalLockPosition(&position, this);  // 0x002d4c78
    }
    return other;
}

// 0x0048d580 CKHkS08Clamp_State3_Inactive_maybe: entering hides the clamp and puts it to sleep in its context;
// leaving shows and wakes it.
uint8_t CKHkS08Clamp::State3(IKTime* /*clock*/, int32_t phase, uint8_t other) {
    uint32_t active = 0;
    CSGLeaf* node = static_cast<CSGLeaf*>(m_pKGLObject);
    if (phase == 1) {
        node->m_sgProperties = (node->m_sgProperties & 0xfffffffbu) | 4u;
    } else if (phase == 2) {
        active = 1;
        node->m_sgProperties &= 0xfffffffbu;
    } else {
        return other;
    }
    SetObjectActiveInContext(g_pEngine->m_coreManager, this, active, static_cast<IKBaseGroup*>(static_cast<CKGrpS08Clamp*>(m_pUnk24)));
    return other;
}

CKHkS08Clamp::~CKHkS08Clamp() {
    for (ContactHistoryNode* node = m_pContactHistory; node != nullptr;) {
        ContactHistoryNode* next = node->m_pNext;  // +0x14
        ContactHistory_FreeNode(node);
        node = next;
    }
    m_pContactHistory = nullptr;
}

// 0x00491338 CKHkS08Clamp_Stop
void CKHkS08Clamp::Stop() {
    // CKHkActorBase_d82_maybe_Stop 0x3f6e50: empty.
    IKBoundingVolume* volume = static_cast<IKBoundingVolume*>(m_pUnk2C);
    if (volume->m_pParent != nullptr) static_cast<CSGBranch*>(volume->m_pParent)->RemoveChild(volume);  // vt+0x78
    SetTrailActive(0);  // 0x004903f0
    static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision)->DisableVolume(static_cast<IKBoundingVolume*>(m_pUnk2C));  // 0x001920e8
}

// 0x004903f0 CKHkS08Clamp_UpdateCollisionVolumesFromBones_maybe. Its two inlined copies of SetRibbonActive are
// CTrailNodeFx::SetRibbonActive's code (the anchors by the trail's mode; LVL010's two trails are mode 1).
void CKHkS08Clamp::SetTrailActive(int32_t active) {
    CTrailNodeFx* trail = static_cast<CTrailNodeFx*>(m_pUnkF8);
    if (trail == nullptr) return;
    trail->SetRibbonActive(0, 0, 1);  // only when ribbon 0 was on
    if (active == 0) return;
    CSGMovable* node = NodeOf(this);
    node->ForceWorldMatrixUpdate();      // vt+0x50
    const float half = m_fUnkFC * 0.5f;  // TOC1 +0x5e1c
    const RwMatrix* ltm = FrameLtm(node->m_pRwFrame);  // frame +0x50: up +0x60, pos +0x80
    STrailNodeData* ribbon = trail->m_apTrailData[0];
    ribbon->m_v3Extrem1.z = ppc::fmadds(half, ltm->up.z, ltm->pos.z);
    ribbon->m_v3Extrem1.x = ppc::fmadds(half, ltm->up.x, ltm->pos.x);
    ribbon->m_v3Extrem1.y = ppc::fmadds(half, ltm->up.y, ltm->pos.y);
    ribbon->m_v3Extrem2.y = ppc::fmadds(half, -ltm->up.y, ltm->pos.y);
    ribbon->m_v3Extrem2.z = ppc::fmadds(half, -ltm->up.z, ltm->pos.z);
    ribbon->m_v3Extrem2.x = ppc::fmadds(half, -ltm->up.x, ltm->pos.x);
    trail->SetRibbonActive(0, 1, 1);
}

// 0x0048cef8 CKHkS08Clamp_UpdateRotationBlend_maybe
void CKHkS08Clamp::UpdateRotationBlend(IKTime* clock) {
    const float kOne = 1.0f;  // TOC1 +0x5e38
    const float t = m_fBlendTime / m_fUnk44;
    if (!(t < kOne)) {  // blt
        NodeOf(this)->SetLocalMatrix(reinterpret_cast<const RwMatrix*>(m_pUnk3C));  // 0x000d0be8
        return;
    }
    m_fBlendTime = m_fBlendTime + clock->m_afDeltaTime[0];  // +0x1c
    const CMatrix34* from = m_pUnk40;
    const CMatrix34* to = m_pUnk3C;
    const float pz = ppc::fmadds(t, to->m_pos.z - from->m_pos.z, from->m_pos.z);
    const float px = ppc::fmadds(t, to->m_pos.x - from->m_pos.x, from->m_pos.x);
    const float py = ppc::fmadds(t, to->m_pos.y - from->m_pos.y, from->m_pos.y);
    float q0[4];
    float q1[4];
    Quat_FromMatrix(q0, reinterpret_cast<const float*>(from));  // 0x002420f8
    Quat_FromMatrix(q1, reinterpret_cast<const float*>(to));
    const float s = kOne - t;
    float q[4];
    q[3] = ppc::fmadds(s, q0[3], t * q1[3]);
    q[0] = ppc::fmadds(s, q0[0], t * q1[0]);
    q[1] = ppc::fmadds(s, q0[1], t * q1[1]);
    q[2] = ppc::fmadds(s, q0[2], t * q1[2]);
    Quat_Normalize(q);  // 0x00242180
    CMatrix34 m{};
    Quat_ToMatrixNormalizing(q, &m);  // 0x00241d78
    m.m_pos.z = pz;
    m.m_pos.x = px;
    m.m_pos.y = py;
    m.m_ui32Flags &= 0xfffdffffu;
    NodeOf(this)->SetLocalMatrix(reinterpret_cast<const RwMatrix*>(&m));
}

// 0x0048d9c8 CKHkS08Clamp_ProcessContacts_maybe
void CKHkS08Clamp::ProcessContacts(IKTime* clock) {
    const float kTime = -1000.0f;  // TOC1 +0x5e74
    for (ICollision* c = static_cast<ICollision*>(static_cast<IKBoundingVolume*>(m_pUnk2C)->m_CollisionResList); c != nullptr;
         c = c->m_pNext) {
        IKBoundingVolume* other;
        if (static_cast<IKBoundingVolume*>(c->GetBoundingVolume1())->m_pOwner == this) {  // vt+0x00
            c->GetBoundingVolume1();
            other = static_cast<IKBoundingVolume*>(c->GetBoundingVolume2());  // vt+0x04
        } else {
            c->GetBoundingVolume2();
            other = static_cast<IKBoundingVolume*>(c->GetBoundingVolume1());
        }
        if (c->HasContactSet() == 0 || (other->m_ui16PropertiesFlags & 8u) == 0) continue;  // vt+0x08
        if (ContactHistory_Touch(kTime, kTime, &m_pContactHistory, other, other->m_pOwner) == 0) continue;  // 0x98f380
        if (m_ui8State == 0) {
            OnContactHit(other->m_pOwner);  // (the volume's +0x1c is passed too, unread)
        } else if (m_ui8State == 2) {
            m_bUnkE8 = 1;
        }
    }
    ContactHistory_Update(&m_pContactHistory, clock);  // TocBridge 0x98f430
}

// 0x0048d7f0 CKHkS08Clamp_OnContactHit_maybe
void CKHkS08Clamp::OnContactHit(IKSerializable* owner) {
    const float kZero = 0.0f;  // TOC1 +0x5e24
    PlayClampSound(this, 0, 0);
    const RwV3d& a = FrameLtm(static_cast<CSGMovable*>(static_cast<IKHook*>(owner)->m_pKGLObject)->m_pRwFrame)->pos;
    const RwV3d& c = FrameLtm(NodeOf(this)->m_pRwFrame)->pos;
    float dx = c.x - a.x;
    float dz = c.z - a.z;
    float dy = crt::Tanf(m_fUnk8C * 0.0174532905f);  // TOC1 +0x5e3c (degrees to radians); TocBridge 0x98f660
    const float dx2 = dx * dx;
    const float dz2 = dz * dz;
    const float flat = std::sqrt((dx2 + kZero) + dz2);  // Math_Sqrtf 0x10690
    const float speed = m_fUnk90;
    dy = dy * flat;
    const float length = std::sqrt(dz2 + ppc::fmadds(dy, dy, dx2));
    if (length != kZero) {
        const float k = speed / length;
        dz = dz * k;
        dx = dx * k;
        dy = dy * k;
    }
    m_vUnk64.x = dx;
    m_vUnk64.z = dz;
    m_vUnk64.y = dy;
}

// ==== P14: the launched clamp (the clamp gun's shots; LVL110) =======================================================
#include <cstring>

#include "Spyro2008/logic/CKS08GameManager.h"
#include "crt/xsinf.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/math/Vec3.h"
#include "k2000/render/CRenderer.h"
#include "k2000/services/CollisionDatas.h"
#include "k2000/services/ICollisionMesh.h"

namespace {
// The game's inlined cosf / sinf with the library call for a negative argument (the sign bit tested as an integer).
bool ClampSignBit(float x) {
    int32_t bits;
    std::memcpy(&bits, &x, 4);
    return bits < 0;
}
float ClampCos(float x) { return ClampSignBit(x) ? crt::LibCosf(-x) : crt::InlineCosf(x); }
float ClampSin(float x) { return ClampSignBit(x) ? -crt::LibSinf(-x) : crt::InlineSinf(x); }
// The shared Y axis (0x00c50d40, filled by a static initialiser in the original) and the null vector (0x00c50d64).
const CVector3 kClampAxisY = {0.0f, 1.0f, 0.0f};
const CVector3 kClampNull = {0.0f, 0.0f, 0.0f};
constexpr float kTwoPi = 6.28318548f;     // TOC1 +0x5e40
constexpr float kRadToDeg = 57.2957802f;  // TOC1 +0x5e44
// A velocity reflected on a normal and scaled: (v + 2 (n d)) * scale with d = -(n . v) (fmuls, fmadds, fnmadds; the
// doubling as an add); unchanged (all three equal) the velocity is stopped (the null vector).
bool ReflectVelocity(CVector3& v, const CVector3& n, float scale) {
    const float d = -ppc::fmadds(n.z, v.z, ppc::fmadds(n.x, v.x, n.y * v.y));
    float rx = n.x * d;
    float rz = n.z * d;
    float ry = n.y * d;
    rx = v.x + (rx + rx);
    rz = v.z + (rz + rz);
    ry = v.y + (ry + ry);
    rx = rx * scale;
    rz = rz * scale;
    ry = ry * scale;
    if (v.x == rx && v.y == ry && v.z == rz) {
        v.z = kClampNull.z;
        v.x = kClampNull.x;
        v.y = kClampNull.y;
        return true;
    }
    v.z = rz;
    v.x = rx;
    v.y = ry;
    return false;
}
}  // namespace

void CKHkS08Clamp::ChangeState(uint8_t next) {
    const uint8_t previous = m_ui8State;
    if (previous != 0xff) CallState(previous, nullptr, 2, next);
    m_ui8State = next;
    CallState(next, nullptr, 1, previous);
}

// 0x0048fb80 CKHkS08Clamp_EnterState1_maybe
void CKHkS08Clamp::EnterState1() {
    m_bUnkF4 = 1;
    ChangeState(1);
}

// 0x0048fcc8 CKHkS08Clamp_EnterState3_maybe
void CKHkS08Clamp::EnterState3() { ChangeState(3); }

// 0x0048ddc8 CKHkS08Clamp_PlaySound1AndSpawnFx_maybe
void CKHkS08Clamp::PlaySound1AndSpawnFx() {
    if (m_ui8State != 0 && m_ui8State != 1) return;
    PlayClampSound(this, 1, 0);
    SpawnFx();  // CKHkS08Clamp_SpawnFx_maybe 0x491938 (+0xf0 passed, unread)
}

// 0x0048f330 CKHkS08Clamp_LaunchRandomDirection_maybe
void CKHkS08Clamp::LaunchRandomDirection() {
    const float a = (static_cast<float>(static_cast<uint16_t>(Rand_Int())) / 65535.0f) * kTwoPi;  // TOC1 +0x5eb8, +0x5e40
    const float b = (static_cast<float>(static_cast<uint16_t>(Rand_Int())) / 65535.0f) * kTwoPi;
    m_vSpinAxis.x = ClampCos(a) * ClampCos(b);
    m_vSpinAxis.y = ClampSin(a);
    m_vSpinAxis.z = ClampCos(a) * ClampSin(b);
}

// 0x00490008 CKHkS08Clamp_Launch_maybe
uint8_t CKHkS08Clamp::Launch(const CVector3* position, const CVector3* velocity, const CVector3* acceleration) {
    m_vUnk4c.x = position->x;
    m_vUnk4c.z = position->z;
    m_vUnk4c.y = position->y;
    RwFrame* frame = NodeOf(this)->m_pRwFrame;
    frame->modelling.pos.z = position->z;
    frame->modelling.pos.x = position->x;
    frame->modelling.pos.y = position->y;
    frame->modelling.flags &= 0xfffdffffu;
    RwFrame_MarkDirty(frame);  // 0x00010698
    m_vUnk64.x = velocity->x;
    m_vUnk64.z = velocity->z;
    m_vUnk64.y = velocity->y;
    m_vUnk58.x = acceleration->x;
    m_vUnk58.z = acceleration->z;
    m_vUnk58.y = acceleration->y;
    LaunchRandomDirection();
    ChangeState(0);
    return 1;
}

// 0x0048e2c8 CKHkS08Clamp_UpdateGroundImpact_maybe
void CKHkS08Clamp::UpdateGroundImpact(IKTime* clock) {
    CGroundContactDatasIn in;
    in.m_fDeltaMax = 0.0f;  // TOC1 +0x5e24
    float height = m_fUnkDC;
    if (m_vUnk64.y < 0.0f) height = height - m_vUnk64.y * clock->m_afDeltaTime[0];  // falling: the fall this frame more
    in.m_fObjectHeight = height;
    in.m_MasksOfGrdForTest[0] = 1;
    in.m_MasksOfGrdForTest[1] = 2;
    CKSrvCollision* collision = static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision);
    collision->GroundProbePoints(&in, &m_gcInOut, &m_vUnk4c.x, 1);  // 0x00196540
    const int32_t status = static_cast<int32_t>(m_gcInOut.m_eContactStatus);
    if (status >= 1) {
        bool landed = false;
        if (status > 2) {
            landed = status == 3;
        } else {
            const ICollisionMesh* ground = static_cast<const ICollisionMesh*>(m_gcInOut.m_pGround);
            if ((ground->m_ui16PropertiesFlags & 0x200u) != 0 && ((ground->m_ba16EngineFlags >> 1) & 1u) == 0) {
                landed = true;
            } else {
                PlayClampSound(this, 3, 0);
                m_vUnk4c.x = m_gcInOut.m_ProjectionOnGround.x;
                m_vUnk4c.y = m_gcInOut.m_ProjectionOnGround.y;
                m_vUnk4c.z = m_gcInOut.m_ProjectionOnGround.z;
                const float speedSq = ppc::fmadds(m_vUnk64.z, m_vUnk64.z, ppc::fmadds(m_vUnk64.x, m_vUnk64.x, m_vUnk64.y * m_vUnk64.y));
                if (speedSq < m_fUnk78 * m_fUnk78) {
                    if (ReflectVelocity(m_vUnk64, m_gcInOut.m_Normal, m_fUnk74)) m_bUnk70 = 0;  // unchanged: stopped
                } else {
                    // Too fast: the velocity "reflects" to itself, so it is stopped.
                    m_vUnk64.z = kClampNull.z;
                    m_vUnk64.x = kClampNull.x;
                    m_vUnk64.y = kClampNull.y;
                    m_bUnk70 = 0;
                }
            }
        }
        if (landed) {
            m_bUnk70 = 0;
            m_bUnk71 = 1;
        }
    }
    // The walls: the cylinder swept from the node's position to +0x4c.
    const RwV3d& from = NodeOf(this)->m_pRwFrame->modelling.pos;
    CLine line;
    line.m_start.x = from.x;
    line.m_start.z = from.z;
    line.m_start.y = from.y;
    line.m_VectDir.x = m_vUnk4c.x - from.x;
    line.m_VectDir.y = m_vUnk4c.y - from.y;
    line.m_VectDir.z = m_vUnk4c.z - from.z;
    CSlideGroundEdgeDatasOut out;
    const uint8_t walls = collision->ResolveSweptCylinderWalls(&line, m_fUnkE0, m_fUnkDC, &out, nullptr, nullptr, 1);  // 0x0019aa68
    if (walls == 2) {
        m_vUnk4c.x = m_vUnk4c.x + out.m_v3BouncingVector.x;
        m_vUnk4c.y = m_vUnk4c.y + out.m_v3BouncingVector.y;
        m_vUnk4c.z = m_vUnk4c.z + out.m_v3BouncingVector.z;
        ReflectVelocity(m_vUnk64, out.m_v3Normal, m_fUnk74);
    } else if (walls == 3) {
        m_vUnk4c.x = m_vUnk4c.x + out.m_v3BouncingVector.x;
        m_vUnk4c.y = m_vUnk4c.y + out.m_v3BouncingVector.y;
        m_vUnk4c.z = m_vUnk4c.z + out.m_v3BouncingVector.z;
    }
    if (m_bUnk71 != 0) return;
    const uint32_t contact = m_gcInOut.m_eContactStatus;
    if ((contact != 1 && contact != 2) || m_gcInOut.m_pGround == nullptr) return;
    // CKHkS08Enemy_GetGroundSurfaceType_maybe's test, inlined: engine flag 2 -> 3, else 0x800 -> 0, 0x1000 -> 1,
    // 0x2000 -> 2, none -> 0.
    const ICollisionMesh* ground = static_cast<const ICollisionMesh*>(m_gcInOut.m_pGround);
    uint32_t surface = 0;
    if (((ground->m_ba16EngineFlags >> 1) & 1u) != 0) {
        surface = 3;
    } else if ((ground->m_ui16PropertiesFlags & 0x800u) != 0) {
        surface = 0;
    } else if ((ground->m_ui16PropertiesFlags & 0x1000u) != 0) {
        surface = 1;
    } else if ((ground->m_ui16PropertiesFlags & 0x2000u) != 0) {
        surface = 2;
    }
    static_cast<CKS08GameManager*>(g_pEngine->m_gameManager)
        ->SpawnSurfaceFx(0.0f, this, surface, 1, &m_gcInOut.m_ProjectionOnGround.x);  // 0x004f9628
}

// 0x00490cc8 CKHkS08Clamp_State0
uint8_t CKHkS08Clamp::State0(IKTime* clock, int32_t phase, uint8_t other) {
    if (phase == 1) {
        m_bUnk71 = 0;
        m_bUnk70 = 1;
        SetTrailActive(1);  // 0x004903f0
        return other;
    }
    if (phase != 0) return other;
    ProcessContacts(clock);  // 0x0048d9c8
    const float dt = clock->m_afDeltaTime[0];  // +0x1c
    m_vUnk64.x = ppc::fmadds(dt, m_vUnk58.x, m_vUnk64.x);
    m_vUnk64.z = ppc::fmadds(dt, m_vUnk58.z, m_vUnk64.z);
    m_vUnk64.y = ppc::fmadds(dt, m_vUnk58.y, m_vUnk64.y);
    {
        const float dt2 = clock->m_afDeltaTime[0];
        const RwV3d& p = NodeOf(this)->m_pRwFrame->modelling.pos;
        m_vUnk4c.x = ppc::fmadds(dt2, m_vUnk64.x, p.x);
        m_vUnk4c.z = ppc::fmadds(dt2, m_vUnk64.z, p.z);
        m_vUnk4c.y = ppc::fmadds(dt2, m_vUnk64.y, p.y);
    }
    // The spin this frame: +0x7c degrees a second, wrapped into [0, 2pi) (bge / blt / cror: NaN is left as it is).
    float angle = (m_fUnk7C * 0.0174532905f) * clock->m_afDeltaTime[0];  // TOC1 +0x5e3c
    if (!(angle >= 0.0f)) {
        do {
            angle = angle + kTwoPi;
        } while (angle < 0.0f);
    }
    while (angle >= kTwoPi) angle = angle - kTwoPi;
    NodeOf(this)->RotateInPlace(&m_vSpinAxis.x, angle * kRadToDeg);  // 0x000d11b0
    UpdateGroundImpact(clock);
    {
        RwFrame* frame = NodeOf(this)->m_pRwFrame;
        frame->modelling.pos.z = m_vUnk4c.z;
        frame->modelling.pos.x = m_vUnk4c.x;
        frame->modelling.pos.y = m_vUnk4c.y;
        frame->modelling.flags &= 0xfffdffffu;
        RwFrame_MarkDirty(frame);  // 0x00010698
    }
    if (m_pUnkF8 != nullptr) {
        // The trail's ribbon 0 along the node's up axis (SetTrailActive's layout, without switching the ribbon).
        CSGMovable* node = NodeOf(this);
        node->ForceWorldMatrixUpdate();      // vt+0x50
        const float half = m_fUnkFC * 0.5f;  // TOC1 +0x5e1c
        const RwMatrix* ltm = FrameLtm(node->m_pRwFrame);
        STrailNodeData* ribbon = static_cast<CTrailNodeFx*>(m_pUnkF8)->m_apTrailData[0];
        ribbon->m_v3Extrem1.z = ppc::fmadds(half, ltm->up.z, ltm->pos.z);
        ribbon->m_v3Extrem1.x = ppc::fmadds(half, ltm->up.x, ltm->pos.x);
        ribbon->m_v3Extrem1.y = ppc::fmadds(half, ltm->up.y, ltm->pos.y);
        ribbon->m_v3Extrem2.y = ppc::fmadds(half, -ltm->up.y, ltm->pos.y);
        ribbon->m_v3Extrem2.z = ppc::fmadds(half, -ltm->up.z, ltm->pos.z);
        ribbon->m_v3Extrem2.x = ppc::fmadds(half, -ltm->up.x, ltm->pos.x);
    }
    if (m_bUnk70 != 0) return other;
    if (m_bUnk71 != 0) {
        // Landed: once the node is no longer drawn (its last rendered frame is not this one) the gun gets 0x900.
        if (static_cast<CSGLeaf*>(m_pKGLObject)->m_ui16LastRenderedFrame == g_ui16RenderFrameCounter) return other;
        m_pUnk28->MessageProc(0x900, this);  // vt+0x1c
        return 3;
    }
    // The flight ended in the air: State1 blends the node from its matrix (+0x40) to its yaw alone (+0x3c).
    const RwMatrix& modelling = NodeOf(this)->m_pRwFrame->modelling;
    CMatrix34 m;
    std::memcpy(&m, &modelling, sizeof m);  // all 16 words, the pads included
    const float px = m.m_pos.x;
    const float py = m.m_pos.y;
    const float pz = m.m_pos.z;
    CVector3 flat;
    flat.z = m.m_at.z;
    flat.x = m.m_at.x;
    flat.y = 0.0f;  // TOC1 +0x5e24
    float yaw = Vec3_GetYawAngleFromZ(&flat);  // 0x00244528
    if (!(yaw >= 0.0f)) {
        do {
            yaw = yaw + kTwoPi;
        } while (yaw < 0.0f);
    }
    while (yaw >= kTwoPi) yaw = yaw - kTwoPi;
    m.m_right.x = 1.0f;  // TOC1 +0x5e38
    m.m_pos.x = 0.0f;
    m.m_ui32Flags = 0x20003;
    m.m_at.z = 1.0f;
    m.m_up.y = 1.0f;
    m.m_up.x = 0.0f;
    m.m_right.z = 0.0f;
    m.m_right.y = 0.0f;
    m.m_at.y = 0.0f;
    m.m_at.x = 0.0f;
    m.m_up.z = 0.0f;
    m.m_pos.z = 0.0f;
    m.m_pos.y = 0.0f;
    Mat4_RotateInPlace(&m, &kClampAxisY, yaw * kRadToDeg);  // 0x00240498
    m.m_pos.x = px;
    m.m_pos.y = py;
    m.m_pos.z = pz;
    m.m_ui32Flags &= 0xfffdffffu;
    std::memcpy(m_pUnk3C, &m, sizeof m);
    std::memcpy(m_pUnk40, &NodeOf(this)->m_pRwFrame->modelling, sizeof(CMatrix34));
    return 1;
}
