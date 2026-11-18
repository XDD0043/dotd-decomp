// Reconstructed original translation unit: 0x47b688-0x480508 (GAME_TOC1, main_toc1), 54 functions, 34 live.
// Primary class: CKHkS08CristalOrb  key 0x2b82  category Hook  size 0x154  vtable 0xb27b08
// Other owners: Hook (2), Vec3 (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x47b688  CKHkS08CristalOrb_IntegrateMotion_maybe  [dead]
//   [ ] 0x47b710  CKHkS08CristalOrb_GetFlagA8Bit5_maybe  [dead]
//   [ ] 0x47b720  CKHkS08CristalOrb_SetOwnerLock_maybe  [dead]
//   [ ] 0x47b7a8  CKHkS08CristalOrb_GetOwnerLockFlag_maybe  [dead]
//   [ ] 0x47b7b0  CKHkS08CristalOrb_ReflectVelocity_maybe  [dead]
//   [ ] 0x47b870  Vec3_YawDifferenceWrapped_3_maybe  [dead]
//   [ ] 0x47b900  CKHkS08CristalOrb_GetHeroSqrDistance_maybe  [dead: no pointer to its descriptor 0xbc1cd0, no call]
//   [ ] 0x47ba10  CKHkS08CristalOrb_ProbeGroundAtPoint_maybe  [dead]
//   [ ] 0x47ba80  CKHkS08CristalOrb_CaptureCarryPose_maybe  [dead: no pointer to its descriptor 0xbc1ce0, no call]
//   [x] 0x47bc10  CKHkS08CristalOrb_DetachFromCarrierHotSpot_maybe  (DetachFromCarrierHotSpot; State0 leave)
//   [x] 0x47bd28  CKHkS08CristalOrb_Resume  (inherited: CKHkActorBase's Resume)
//   [x] 0x47bd50  CKHkS08CristalOrb_Pause  (inherited: CKHkActorBase's Pause)
//   [x] 0x47bd78  CKHkS08CristalOrb_PostLoad  (PostLoad, vt+0x30)
//   [ ] 0x47bdb8  CKHkS08CristalOrb_Save
//   [x] 0x47bde0  CKHkS08CristalOrb_RecursiveRegistration  (inherited: CKHkActorBase's)
//   [x] 0x47be08  CKHkS08CristalOrb_Destroy  (Destroy, vt+0x10)
//   [ ] 0x47be50  CKHkS08CristalOrb_Construct  [dead]
//   [x] 0x47bec0  CKHkS08CristalOrb_DeleteArray  (DOTD_DECLARE_FACTORIES(CKHkS08CristalOrb), CKHkS08CristalOrb.h)
//   [ ] 0x47bf60  RegisterCKHkS08CristalOrbClass
//   [ ] 0x47bfe8  _GLOBAL__D_47bfe8
//   [ ] 0x47bff8  _GLOBAL__I_47bff8
//   [ ] 0x47c008  CKHkS08CristalOrb_BaseDestructor  [dead: no pointer to its descriptor 0xbc1d58, no call]
//   [x] 0x47c038  CKHkS08CristalOrb_MessageProc  (MessageProc, vt+0x1c)
//   [ ] 0x47c3b0  CKHkS08CristalOrb_SetFlagA8Bit5_maybe  [dead]
//   [ ] 0x47c3f0  CKHkS08CristalOrb_ReleaseHolderReservation_maybe  [dead]
//   [ ] 0x47c448  FUN_0047c448  [dead]
//   [x] 0x47c470  CKHkS08CristalOrb_DeletingDestructor  (the deleting form of the destructor)
//   [x] 0x47c4b8  CKHkS08CristalOrb_Destructor  (the destructor)
//   [ ] 0x47c4e8  Hook_GetWorldPosition_maybe  [dead]
//   [ ] 0x47c570  CKHkS08CristalOrb_GetFlagA8Bit6_maybe  [dead]
//   [ ] 0x47c580  CKHkS08CristalOrb_SetFlagA8Bit6_maybe  [dead]
//   [ ] 0x47c5c0  CKHkS08CristalOrb_Construct_2  [dead]
//   [ ] 0x47c630  CKHkS08CristalOrb_IsInState0  [dead]
//   [ ] 0x47c640  Hook_GetWorldMatrix_maybe  [dead]
//   [x] 0x47c758  CKHkS08CristalOrb_Stop  (Stop, vt+0x68)
//   [x] 0x47c850  CKHkS08CristalOrb_CreateArray  (DOTD_DECLARE_FACTORIES)
//   [x] 0x47c950  CKHkS08CristalOrb_Create  (DOTD_DECLARE_FACTORIES: the header's constructor)
//   [x] 0x47c9d8  CKHkS08CristalOrb_OnActivate  (VfA0 OnActivate, vt+0xa0)
//   [x] 0x47cc20  CKHkS08CristalOrb_LerpToCarrierHotSpot_maybe  (LerpToCarrierHotSpot; State0 tick)
//   [x] 0x47ce98  CKHkS08CristalOrb_IsPointInInteractionCone_maybe  (IsPointInInteractionCone; UpdateHeroInteraction)
//   [x] 0x47d0b0  CKHkS08CristalOrb_UpdateHeroInteraction_maybe  (UpdateHeroInteraction; State1 tick)
//   [x] 0x47d250  CKHkS08CristalOrb_State1_Idle_maybe  (State1, the table +0x134 by descriptor 0xbc1ea8)
//   [ ] 0x47d498  CKHkS08CristalOrb_FindGroundPointByRaising_maybe  [dead]
//   [x] 0x47d5f8  CKHkS08CristalOrb_Load  (Load, vt+0x2c)
//   [x] 0x47de90  CKHkS08CristalOrb_UpdateBounce_maybe  (UpdateBounce; State2 tick)
//   [x] 0x47e600  CKHkS08CristalOrb_State2  (State2, descriptor 0xbc1f00)
//   [x] 0x47e968  CKHkS08CristalOrb_SnapToGround_maybe  (SnapToGround; Restart)
//   [x] 0x47ee48  CKHkS08CristalOrb_State0_Carried_maybe  (State0, descriptor 0xbc1f28)
//   [x] 0x47f520  CKHkS08CristalOrb_Start  (Start, vt+0x50)
//   [x] 0x47f6b8  CKHkS08CristalOrb_Restart  (Restart, vt+0x54)
//   [x] 0x47f888  CKHkS08CristalOrb_Update  (Update, vt+0x7c)
//   [ ] 0x47fc78  CKHkS08CristalOrb_AttachToHero_maybe  [dead: no pointer to its descriptor 0xbc1ff8, no call]
//   [ ] 0x47fea0  CKHkS08CristalOrb_ReserveForHolder_maybe  [dead]
//   [ ] 0x480018  CKHkS08CristalOrb_SetLinkedObject_maybe  [dead]
//
//   [ ] 0x9c4798  CKHkS08CristalOrb_IsKindOfClass  [inline]
//   [ ] 0x9c47f0  CKHkS08CristalOrb_GetClassType  [inline]
//   [ ] 0x9c47f8  CKHkS08CristalOrb_GetClassID  [inline]
#include "Spyro2008/hooks/CKHkS08CristalOrb.h"

#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/Mat4.h"

// 0x0047be08 CKHkS08CristalOrb_Destroy (vt+0x10)
void CKHkS08CristalOrb::Destroy() {
    CKHkActorBase::Destroy();           // 0x003f6e08 (vt+0xc0)
    RwMatrixDestroy_Thunk(m_pMatrix24);  // 0x0023f968
    Mem_FreeAligned16(m_apRefs98);      // 0x00052fb8
}

// 0x0047bd78 CKHkS08CristalOrb_PostLoad (vt+0x30)
int32_t CKHkS08CristalOrb::PostLoad(int32_t type) {
    CKHkActorBase::PostLoad(type);           // 0x003f6e70
    m_pMatrix24 = RwMatrixCreate_Thunk();   // 0x0023fa68
    return 1;
}

// 0x0047d5f8 CKHkS08CristalOrb_Load: the actor base, then the level data (type 0 only): eight floats, two vectors, two
// floats, the ten flag bytes (bit k of +0xa8 = the byte << k, unmasked), the reference count and block (Mem_CallocAligned16
// 0x531f8), then +0x11c and +0x20.
int32_t CKHkS08CristalOrb::Load(IKFile* file, int32_t type) {
    CKHkActorBase::Load(file, type);  // 0x003f6e98
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadF32LE(file, &m_fUnk34);
    ReadF32LE(file, &m_fUnk38);
    ReadU32LE(file, &m_ui32Unk3C);  // a word (MessageProc 0x93f reads its low byte)
    ReadF32LE(file, &m_fUnkD8);
    ReadF32LE(file, &m_fUnkDC);
    ReadF32LE(file, &m_fUnk110);
    ReadF32LE(file, &m_fUnk120);
    ReadF32LE(file, &m_fUnk90);
    ReadF32LE(file, &m_vUnkF8.x);  // one 12-byte read, each word swapped
    ReadF32LE(file, &m_vUnkF8.y);
    ReadF32LE(file, &m_vUnkF8.z);
    ReadF32LE(file, &m_vUnk104.x);
    ReadF32LE(file, &m_vUnk104.y);
    ReadF32LE(file, &m_vUnk104.z);
    ReadF32LE(file, &m_fUnk118);
    ReadF32LE(file, &m_fUnk114);
    for (uint32_t bit = 0; bit < 10; ++bit) {
        uint8_t value = 0;
        ReadU8(file, &value);
        m_unkA8 = (m_unkA8 & ~(1u << bit)) | (static_cast<uint32_t>(value) << bit);
    }
    ReadU8(file, &m_ui8NbRefs);
    m_apRefs98 = static_cast<IKSerializable**>(Mem_CallocAligned16(static_cast<uint32_t>(sizeof(IKSerializable*)), m_ui8NbRefs));  // (4, count) on the PS3
    for (uint32_t i = 0; i < m_ui8NbRefs; ++i) IKFile_ReadRef(file, &m_apRefs98[i]);
    IKFile_ReadRef(file, &m_pUnk11C);
    IKFile_ReadRef(file, &m_pUnk20);
    return 1;
}

// ==== port-final F06: the run time ====================================================================================
#include <cfloat>
#include <cmath>
#include <cstring>

#include "Renderware/rwcore/RwCamera.h"
#include "Spyro2008/groups/CKGrpS08Enemy.h"
#include "Spyro2008/groups/CKGrpS08Hero.h"
#include "Spyro2008/hooks/CKHkS08CristalKey.h"
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "Spyro2008/logic/CKS08GameManager.h"
#include "crt/ppc_ops.h"
#include "crt/xsinf.h"
#include "k2000/core/Ps3MemberFn.h"
#include "k2000/dictionaries/CAnimationDictionary.h"
#include "k2000/graphical/animation/CAnimationManager.h"
#include "k2000/groups/TVectorPush.h"
#include "k2000/logic/CKLevel.h"
#include "k2000/logic/CKSector.h"
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/math/Quat.h"
#include "k2000/math/Vec3.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/CSGBranch.h"
#include "k2000/scenegraph/CSGLeaf.h"
#include "k2000/scenegraph/CSGSectorRoot.h"
#include "k2000/services/CKSrvCollision.h"
#include "k2000/services/CKSrvDynamic.h"
#include "k2000/services/CollisionDatas.h"
#include "k2000/system/IKTime.h"

namespace {
// DOTD: the orb's state handlers by descriptor (k2000/core/Ps3MemberFn.h; the table Start builds at +0x134).
Ps3MemberFnEntry<CKHkS08CristalOrb::StateFn> g_orbStates[] = {
    {0x00bc1f28u, &CKHkS08CristalOrb::State0, "CKHkS08CristalOrb_State0_Carried_maybe 0x47ee48", false},
    {0x00bc1ea8u, &CKHkS08CristalOrb::State1, "CKHkS08CristalOrb_State1_Idle_maybe 0x47d250", false},
    {0x00bc1f00u, &CKHkS08CristalOrb::State2, "CKHkS08CristalOrb_State2 0x47e600", false},
    {0x00bc1c30u, &CKHkS08CristalOrb::State3, "KStub_ReturnArg4_47b680 0x47b680", false},
};

const float kZero = 0.0f;                   // TOC1 +0x5b68
const float kOne = 1.0f;                    // TOC1 +0x5b98
const float kHalf = 0.5f;                   // TOC1 +0x5b70: the probes' delta max and the raise step
const float kCrossfade = 0x1.99999ap-4f;    // TOC1 +0x5bf0 (0x3dcccccd, 0.1)
const float kTwoPi = 0x1.921fb6p+2f;        // TOC1 +0x5b64 (0x40c90fdb)
const float kRadToDeg = 0x1.ca5dc2p+5f;     // TOC1 +0x5bec (0x42652ee1)
const float kNoPoint = FLT_MAX;             // 0x00c4ace0 (TOC1 +0x5bd0 block +0x28)
const CVector3 kNull = {0.0f, 0.0f, 0.0f};  // 0x00c50d64 (TOC1 +0x5be0; filled by a static initialiser)
const CVector3 kAxisY = {0.0f, 1.0f, 0.0f}; // 0x00c50d40 (TOC1 +0x5be8)
const CVector3 kAxisZ = {0.0f, 0.0f, 1.0f}; // 0x00c50d4c (TOC1 +0x5be4)

CSGLeaf* NodeOf(const IKHook* hook) { return static_cast<CSGLeaf*>(hook->m_pKGLObject); }
RwFrame* FrameOf(const IKHook* hook) { return NodeOf(hook)->m_pRwFrame; }
CKHkS08Hero* HeroOf(const CKHkS08CristalOrb* orb) { return static_cast<CKHkS08Hero*>(orb->m_pHero9C); }
CKSrvCollision* Collision() { return static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision); }
CSGSectorRoot* SectorRoot(uint32_t index) {
    return static_cast<CKSector*>(g_pEngine->m_level->m_vpSectors.m_pBlock[index])->m_pSectorRoot;
}
CMatrix34* AsMatrix(RwMatrix* m) { return reinterpret_cast<CMatrix34*>(m); }
const RwMatrix* AsRw(const CMatrix34* m) { return reinterpret_cast<const RwMatrix*>(m); }

// The frame's modelling position set (the identity flag 0x20000 cleared), the frame marked dirty (0x10698).
void SetFramePosition(RwFrame* frame, float x, float y, float z) {
    frame->modelling.pos.x = x;
    frame->modelling.pos.y = y;
    frame->modelling.pos.z = z;
    frame->modelling.flags &= 0xfffdffffu;
    RwFrame_MarkDirty(frame);
}

// The probe the orb's ground tests use: delta max 0.5, the object height +0xd8, masks {1, 2}.
CGroundContactDatasIn ProbeIn(float height) {
    CGroundContactDatasIn in;
    in.m_fDeltaMax = kHalf;
    in.m_fObjectHeight = height;
    in.m_MasksOfGrdForTest[0] = 1;
    in.m_MasksOfGrdForTest[1] = 2;
    return in;
}
// The contact status as the code reads it: the low byte of the word (+0x17 of the contact).
uint8_t StatusByte(const CGroundContactDatasInOut& contact) { return static_cast<uint8_t>(contact.m_eContactStatus); }

// The game's cosine of a float angle: the inlined polynomial for a clear sign bit, the library's cosf of the negation
// otherwise (the original tests the stored word's sign).
float GameCosf(float x) {
    uint32_t bits;
    std::memcpy(&bits, &x, 4);
    return static_cast<int32_t>(bits) < 0 ? crt::LibCosf(-x) : crt::InlineCosf(x);
}

// The answer merge of the MessageProcs (the base's and the own): 3 wins, then 2; a base 0 gives 0, else the own one.
int32_t MergeAnswers(int32_t base, int32_t own) {
    if (base == 3 || own == 3) return 3;
    if (base == 2 || own == 2) return 2;
    if (base == 0) return 0;
    return own;
}

// The velocity bounced off a plane of normal n (restitution +0x114); below the landing speed (+0x118, squared) it
// keeps the old velocity. An unchanged velocity becomes the null vector (and, for the ground, bit 4 of +0xa8).
void Bounce(CKHkS08CristalOrb* orb, const CVector3& n, bool ground) {
    CVector3& v = orb->m_vVelEC;
    const float vx = v.x, vy = v.y, vz = v.z;
    float d = n.y * vy;
    d = ppc::fmadds(n.x, vx, d);
    d = ppc::fnmadds(n.z, vz, d);
    float ry = n.y * d, rx = n.x * d, rz = n.z * d;
    ry = ry + ry;
    rx = rx + rx;
    rz = rz + rz;
    const float e = orb->m_fUnk114;
    float wy = (vy + ry) * e;
    float wx = (vx + rx) * e;
    float wz = (vz + rz) * e;
    const float minSq = orb->m_fUnk118 * orb->m_fUnk118;
    float lenSq = wy * wy;
    lenSq = ppc::fmadds(wx, wx, lenSq);
    lenSq = ppc::fmadds(wz, wz, lenSq);
    if (lenSq < minSq) {
        wx = vx;
        wy = vy;
        wz = vz;
    }
    if (vx != wx || vy != wy || vz != wz) {
        v.z = wz;
        v.x = wx;
        v.y = wy;
        return;
    }
    v.z = kNull.z;
    v.x = kNull.x;
    v.y = kNull.y;
    if (ground) orb->m_unkA8 = (orb->m_unkA8 & 0xffffffefu) | 0x10u;
}

// The start of the lerp to the hot spot (State0's enter and its pick-up animation's end): the hero let go of the
// animation, bit 0 of +0xa8 set, the start position, the target and start orientations, the time 0.
void BeginLerp(CKHkS08CristalOrb* orb) {
    orb->m_unkA8 &= 0xfffffffdu;
    HeroOf(orb)->SetObjectControlsAnim(0);                // 0x00362010
    HeroOf(orb)->SetLockedToObject(0, nullptr, nullptr);  // 0x003622a8
    HeroOf(orb)->SetAttachedMovementEnabled(0);           // 0x00362050
    orb->m_unkA8 = (orb->m_unkA8 & 0xfffffffeu) | 1u;
    const RwV3d& pos = FrameOf(orb)->modelling.pos;
    orb->m_vStart80.x = pos.x;
    orb->m_vStart80.z = pos.z;
    orb->m_vStart80.y = pos.y;
    CMatrix34 target;
    orb->m_pHotSpot40->GetWorldMatrix(&target);                 // 0x000ce970
    Quat_FromMatrix(orb->m_afQuatTarget60, &target.m_right.x);  // 0x002420f8
    CMatrix34 start = *AsMatrix(&FrameOf(orb)->modelling);
    Quat_FromMatrix(orb->m_afQuatStart70, &start.m_right.x);
    orb->m_fLerpTime8C = 0.0f;
}
}  // namespace

uint8_t CKHkS08CristalOrb::CallState(const uint32_t pair[2], IKTime* clock, int32_t phase, uint8_t other) {
    StateFn fn = ResolvePs3MemberFn(g_orbStates, pair, "CKHkS08CristalOrb state handler");
    if (fn == nullptr) return other;
    return (this->*fn)(clock, phase, other);
}

// 0x0047bc10 CKHkS08CristalOrb_DetachFromCarrierHotSpot_maybe: hung under the hot spot (its node and bone) and not
// handed over (+0xa8 bit 9): off the hot spot, back under the sector root at the hot spot's world matrix.
void CKHkS08CristalOrb::DetachFromCarrierHotSpot() {
    CSGHotSpot* hotSpot = m_pHotSpot40;
    if (hotSpot == nullptr) return;
    CSGLeaf* node = NodeOf(this);
    if (static_cast<const void*>(node->m_pParent) != static_cast<const void*>(hotSpot->m_pParent)) return;
    if (node->m_ui8BoneParent != hotSpot->m_ui8BoneNumber) return;
    if ((m_unkA8 & 0x200u) != 0) return;
    hotSpot->DetachVolume(node);                         // 0x000ce690
    SectorRoot(m_iSectorIndex)->AddChild(NodeOf(this));  // vt+0x70
    CMatrix34 world;
    m_pHotSpot40->GetWorldMatrix(&world);        // 0x000ce970
    NodeOf(this)->SetLocalMatrix(AsRw(&world));  // 0x000d0be8
}

// 0x0047c038 CKHkS08CristalOrb_MessageProc: 0x93f (a hero takes it: data the hero) attaches it to his hot spot +0x3c
// and enters state 0; 0x940 the hero lets go.
int32_t CKHkS08CristalOrb::MessageProc(uint16_t message, void* data) {
    const int32_t base = CKHkActorBase::MessageProc(message, data);  // 0x003f7148
    int32_t own = 1;
    if (message == 0x93f) {
        m_pHero9C = static_cast<IKSerializable*>(data);
        m_ui8HeroIndexA4 = HeroOf(this)->GetDragonIndex();  // 0x00361960
        m_pHotSpot40 = static_cast<CSGHotSpot*>(HeroOf(this)->GetHotSpot(static_cast<uint8_t>(m_ui32Unk3C)));  // 0x00361b70
        if (m_pHotSpot40 == nullptr) {
            m_pHero9C = nullptr;
            return 0;
        }
        m_unkA8 = (m_unkA8 & 0xfffffff7u) | 8u;
        if (HeroOf(this)->AttachToObject(this, 1) != 0) {  // 0x00362360
            static_cast<CKSrvDynamic*>(g_pEngine->m_srvDynamic)->SetEntryFlag(m_pHero9C, 0);  // 0x0023aff8
            HeroOf(this)->SetObjectControlsAnim(1);                // 0x00362010
            HeroOf(this)->SetLockedToObject(1, nullptr, nullptr);  // 0x003622a8
            HeroOf(this)->SetAttachedMovementEnabled(1);           // 0x00362050
            HeroOf(this)->SetAttachedMoveSpeed(kZero);             // 0x00362670
            HeroOf(this)->SetUnk530IfAttachedMovement(kZero);      // 0x003626a0
            const uint8_t old = m_ui8State;
            if (old != 0xff) CallState(&m_pStateTable[old * 2u], nullptr, 2, 0);
            m_ui8State = 0;
            CallState(&m_pStateTable[0], nullptr, 1, old);
            own = 0;
        }
    } else if (message == 0x940) {
        HeroOf(this)->DetachFromObject();  // 0x00364608
        own = 0;
    }
    return MergeAnswers(base, own);
}

// 0x0047c758 CKHkS08CristalOrb_Stop: the base's, the node back under its sector's root, out of the enemy group's orbs.
void CKHkS08CristalOrb::Stop() {
    CKHkActorBase::Stop();  // 0x003f6e50
    CSGLeaf* node = NodeOf(this);
    node->m_pParent->RemoveChild(node);                  // vt+0x78
    SectorRoot(m_iSectorIndex)->AddChild(NodeOf(this));  // vt+0x70
    CKGrpS08Enemy* enemies = static_cast<CKGrpS08Enemy*>(g_pEngine->m_gameManager->m_unk04[0]);  // +0x04
    if (enemies != nullptr) enemies->RemoveCristalOrb(this);  // 0x00267950
}

// 0x0047c9d8 CKHkS08CristalOrb_OnActivate: the base's, the node's modelling matrix into +0x24 and its parent into +0x28,
// the orb into the enemy group's orbs (+0x1b0, grown by one), the node +0x11c placed at the orb.
void CKHkS08CristalOrb::VfA0() {
    CKHkActorBase::VfA0();  // 0x003f7338
    *m_pMatrix24 = *AsMatrix(&FrameOf(this)->modelling);
    m_pParent28 = NodeOf(this)->m_pParent;
    CKGrpS08Enemy* enemies = static_cast<CKGrpS08Enemy*>(g_pEngine->m_gameManager->m_unk04[0]);  // +0x04
    if (enemies != nullptr) {
        TVector_GrowIfFull(enemies->m_vUnk1b0);  // Mem_ReallocAligned16 0x00053190
        enemies->m_vUnk1b0.m_pBlock[enemies->m_vUnk1b0.m_ui32NbUsedElt] = this;
        ++enemies->m_vUnk1b0.m_ui32NbUsedElt;
    }
    if (m_pUnk11C != nullptr) {
        const RwV3d& pos = FrameOf(this)->modelling.pos;
        SetFramePosition(static_cast<CSGLeaf*>(m_pUnk11C)->m_pRwFrame, pos.x, pos.y, pos.z);
    }
}

// 0x0047cc20 CKHkS08CristalOrb_LerpToCarrierHotSpot_maybe: the time advanced; the node moved (position lerp, the time
// over the duration clamped to 1) and turned (the orientations blended unclamped, normalised) towards the hot spot; at
// 1 bit 0 of +0xa8 cleared and the node hung on the hot spot.
void CKHkS08CristalOrb::LerpToCarrierHotSpot(IKTime* clock) {
    m_fLerpTime8C = m_fLerpTime8C + clock->m_afDeltaTime[0];
    CVector3 target;
    m_pHotSpot40->GetWorldPosition(&target);  // 0x000ce790
    float t = m_fLerpTime8C / m_fUnk90;
    if (!(t < kOne)) t = kOne;
    const float sx = m_vStart80.x, sy = m_vStart80.y, sz = m_vStart80.z;
    RwFrame* frame = FrameOf(this);
    frame->modelling.pos.x = ppc::fmadds(t, target.x - sx, sx);
    frame->modelling.pos.y = ppc::fmadds(t, target.y - sy, sy);
    frame->modelling.pos.z = ppc::fmadds(t, target.z - sz, sz);
    frame->modelling.flags &= 0xfffdffffu;
    RwFrame_MarkDirty(frame);
    CMatrix34 world;
    m_pHotSpot40->GetWorldMatrix(&world);                 // 0x000ce970
    Quat_FromMatrix(m_afQuatTarget60, &world.m_right.x);  // 0x002420f8
    const float s = m_fLerpTime8C / m_fUnk90;
    const float w3 = s * m_afQuatTarget60[3];
    const float w0 = s * m_afQuatTarget60[0];
    const float w1 = s * m_afQuatTarget60[1];
    const float w2 = s * m_afQuatTarget60[2];
    const float r = kOne - s;
    float q[4];
    q[3] = ppc::fmadds(r, m_afQuatStart70[3], w3);
    q[0] = ppc::fmadds(r, m_afQuatStart70[0], w0);
    q[1] = ppc::fmadds(r, m_afQuatStart70[1], w1);
    q[2] = ppc::fmadds(r, m_afQuatStart70[2], w2);
    Quat_Normalize(q);                // 0x00242180
    CMatrix34 m;
    Quat_ToMatrixNormalizing(q, &m);  // 0x00241d78
    const RwV3d& pos = FrameOf(this)->modelling.pos;
    m.m_pos.z = pos.z;
    m.m_pos.x = pos.x;
    m.m_pos.y = pos.y;
    m.m_ui32Flags &= 0xfffdffffu;
    NodeOf(this)->SetLocalMatrix(AsRw(&m));  // 0x000d0be8
    if (t == kOne) {
        m_unkA8 &= 0xfffffffeu;
        CSGLeaf* node = NodeOf(this);
        node->m_pParent->RemoveChild(node);        // vt+0x78
        m_pHotSpot40->AttachVolume(NodeOf(this));  // 0x000ce2b8
    }
}

// 0x0047ce98 CKHkS08CristalOrb_IsPointInInteractionCone_maybe: `point` nearer than +0x34 and the direction from the orb
// to it within the cone of angle +0x38 around -`direction`.
uint8_t CKHkS08CristalOrb::IsPointInInteractionCone(const CVector3* point, const CVector3* direction) {
    const RwV3d& pos = FrameOf(this)->modelling.pos;
    float dy = point->y - pos.y;
    float dx = point->x - pos.x;
    float dz = point->z - pos.z;
    float sq = dy * dy;
    sq = ppc::fmadds(dx, dx, sq);
    sq = ppc::fmadds(dz, dz, sq);
    float length = static_cast<float>(std::sqrt(static_cast<double>(sq)));  // Math_Sqrtf 0x00010690
    if (length != kZero) {
        const float inv = kOne / length;
        dz = dz * inv;
        dx = dx * inv;
        dy = dy * inv;
    } else {
        length = kZero;
    }
    if (m_fUnk34 <= length) return 0;
    const float dirZ = direction->z, dirX = direction->x, dirY = direction->y;
    const float cosine = GameCosf(m_fUnk38);
    float dot = dirY * dy;
    dot = ppc::fmadds(dirX, dx, dot);
    dot = ppc::fnmadds(dirZ, dz, dot);
    return cosine < dot ? 1 : 0;
}

// 0x0047d0b0 CKHkS08CristalOrb_UpdateHeroInteraction_maybe: each player hero facing the orb within the cone, not in a
// combo, makes it his interaction target (type 1).
void CKHkS08CristalOrb::UpdateHeroInteraction() {
    CKGrpS08Hero* group = static_cast<CKGrpS08Hero*>(g_pEngine->m_gameManager->m_unk04[1]);  // +0x08
    if (group == nullptr) return;
    const uint8_t count = group->GetHeroCount();  // 0x002ca038
    if (count == 0) return;
    uint8_t i = 0;
    do {
        CKHkS08Hero* hero = static_cast<CKHkS08Hero*>(group->m_apHeros[i]);  // 0x002ca080
        i = static_cast<uint8_t>(i + 1);
        if (hero->IsPlayerControlled() == 0) continue;  // 0x00362af0
        const RwMatrix& m = static_cast<CSGLeaf*>(hero->m_pKGLObject)->m_pRwFrame->modelling;
        const CVector3 position = {m.pos.x, m.pos.y, m.pos.z};
        const CVector3 at = {m.at.x, m.at.y, m.at.z};
        if (IsPointInInteractionCone(&position, &at) == 0) continue;
        if (hero->IsInCombo() != 0) continue;  // 0x0032a698
        CKS08GameManager* manager = static_cast<CKS08GameManager*>(g_pEngine->m_gameManager);
        // 0x00362ac8 CKHkS08Hero_GetPlayerIndexIfControlled_maybe: the leader byte (+0x26) of a player's hero, else -1.
        const uint8_t player = hero->m_ui8Hero == hero->m_ui8TrackedLeader ? hero->m_ui8Leader : 0xff;
        manager->SetHeroInteractionTarget(this, 1, player);  // 0x004ee770
    } while (i != count);
}

// 0x0047d250 CKHkS08CristalOrb_State1_Idle_maybe: at rest (+0xa8 bit 8); the interaction offer, the node +0x11c hidden
// while the hero is within +0x120.
uint8_t CKHkS08CristalOrb::State1(IKTime* /*clock*/, int32_t phase, uint8_t other) {
    if (phase == 1) {
        m_unkA8 |= 0x100u;
        return other;
    }
    if (phase == 2) {
        if (m_pUnk11C != nullptr) {
            CSGLeaf* node = static_cast<CSGLeaf*>(m_pUnk11C);
            node->m_sgProperties = (node->m_sgProperties & 0xfffffffbu) | 4u;
        }
        m_unkA8 &= 0xfffffeffu;
        return other;
    }
    if (phase != 0) return other;
    UpdateHeroInteraction();
    float distSq = kZero;
    CKGrpS08Hero* group = static_cast<CKGrpS08Hero*>(g_pEngine->m_gameManager->m_unk04[1]);  // +0x08
    if (group != nullptr) {
        const uint8_t count = group->GetHeroCount();  // 0x002ca038
        if (count != 0) {
            // BUG(original): only the last hero's distance is kept.
            uint8_t i = 0;
            do {
                CKHkS08Hero* hero = static_cast<CKHkS08Hero*>(group->m_apHeros[i]);  // 0x002ca080
                i = static_cast<uint8_t>(i + 1);
                const RwV3d& own = FrameOf(this)->modelling.pos;
                const RwV3d& at = static_cast<CSGLeaf*>(hero->m_pKGLObject)->m_pRwFrame->modelling.pos;
                const float dy = at.y - own.y;
                const float dx = at.x - own.x;
                const float dz = at.z - own.z;
                distSq = dy * dy;
                distSq = ppc::fmadds(dx, dx, distSq);
                distSq = ppc::fmadds(dz, dz, distSq);
            } while (i != count);
        }
    }
    const float radiusSq = m_fUnk120 * m_fUnk120;
    if (m_pUnk11C == nullptr) return other;
    CSGLeaf* node = static_cast<CSGLeaf*>(m_pUnk11C);
    if (radiusSq <= distSq) {
        node->m_sgProperties &= 0xfffffffbu;
    } else {
        node->m_sgProperties = (node->m_sgProperties & 0xfffffffbu) | 4u;
    }
    return other;
}

// 0x0047de90 CKHkS08CristalOrb_UpdateBounce_maybe: the ground under the thrown orb (on it: placed and bounced, landing
// below the speed +0x118; none: landed, the ground searched upwards in ten steps of 0.5), then the walls (a slide
// bounces the velocity, a push only moves it).
void CKHkS08CristalOrb::UpdateBounce(IKTime* /*clock*/) {
    CGroundContactDatasIn in = ProbeIn(m_fUnkD8);
    Collision()->GroundProbePoints(&in, &m_GContactInOut, &m_vPosE0.x, 1);  // 0x00196540
    const uint8_t status = StatusByte(m_GContactInOut);
    if (status == 1) {
        m_vPosE0.x = m_GContactInOut.m_ProjectionOnGround.x;
        m_vPosE0.y = m_GContactInOut.m_ProjectionOnGround.y;
        m_vPosE0.z = m_GContactInOut.m_ProjectionOnGround.z;
        Bounce(this, m_GContactInOut.m_Normal, true);
    } else if (status == 3) {
        m_unkA8 = (m_unkA8 & 0xffffffefu) | 0x10u;
        CVector3 probe = m_vPosE0;
        CVector3 found = {kNoPoint, kNoPoint, kNoPoint};
        for (int32_t i = 0; i < 10; ++i) {
            in = ProbeIn(m_fUnkD8);
            Collision()->GroundProbePoints(&in, &m_GContactInOut, &probe.x, 1);  // 0x00196540
            if (StatusByte(m_GContactInOut) <= 1) {
                found.x = m_GContactInOut.m_ProjectionOnGround.x;
                found.z = m_GContactInOut.m_ProjectionOnGround.z;
                found.y = m_GContactInOut.m_ProjectionOnGround.y;
                break;
            }
            probe.y = probe.y + kHalf;
        }
        if (kNoPoint != found.x || kNoPoint != found.y || kNoPoint != found.z) {
            m_vPosE0.x = found.x;
            m_vPosE0.y = found.y;
            m_vPosE0.z = found.z;
        }
    }
    const RwV3d& node = FrameOf(this)->modelling.pos;
    CLine line;
    line.m_start.x = node.x;
    line.m_start.z = node.z;
    line.m_start.y = node.y;
    line.m_VectDir.x = m_vPosE0.x - node.x;
    line.m_VectDir.y = m_vPosE0.y - node.y;
    line.m_VectDir.z = m_vPosE0.z - node.z;
    CSlideGroundEdgeDatasOut out;
    std::memset(&out, 0, sizeof out);  // BUG(original): an uninitialised stack block (read only when 2 or 3 is returned)
    const uint8_t result = Collision()->ResolveSweptCylinderWalls(&line, m_fUnkDC, m_fUnkD8, &out, nullptr, nullptr, 1);  // 0x0019aa68
    if (result == 2) {
        m_vPosE0.x = m_vPosE0.x + out.m_v3BouncingVector.x;
        m_vPosE0.y = m_vPosE0.y + out.m_v3BouncingVector.y;
        m_vPosE0.z = m_vPosE0.z + out.m_v3BouncingVector.z;
        Bounce(this, out.m_v3Normal, false);
    } else if (result == 3) {
        m_vPosE0.x = m_vPosE0.x + out.m_v3BouncingVector.x;
        m_vPosE0.y = m_vPosE0.y + out.m_v3BouncingVector.y;
        m_vPosE0.z = m_vPosE0.z + out.m_v3BouncingVector.z;
    }
}

// 0x0047e600 CKHkS08CristalOrb_State2: thrown. Enter: bit 4 (landed) cleared. Tick: the position and velocity
// integrated, bounced, the node placed; landed: state 1. Leave: the node upright, turned about y to its heading.
uint8_t CKHkS08CristalOrb::State2(IKTime* clock, int32_t phase, uint8_t other) {
    if (phase == 1) {
        m_unkA8 &= 0xffffffefu;
        return other;
    }
    if (phase == 2) {
        const CMatrix34 m = *AsMatrix(&FrameOf(this)->modelling);
        const float px = m.m_pos.x, py = m.m_pos.y, pz = m.m_pos.z;
        CVector3 axis = {kAxisZ.x, kAxisZ.y, kAxisZ.z};
        CVector3 heading = {m.m_at.x, kZero, m.m_at.z};
        float diff = Vec3_GetYawAngleFromX(&axis);  // 0x00244638
        diff = diff - Vec3_GetYawAngleFromX(&heading);
        if (diff < kZero) {
            do {
                diff = diff + kTwoPi;
            } while (diff < kZero);
        }
        while (diff >= kTwoPi) diff = diff - kTwoPi;
        NodeOf(this)->SetIdentity();  // 0x000d08f0
        SetFramePosition(FrameOf(this), px, py, pz);
        NodeOf(this)->RotateInPlace(&kAxisY.x, diff * kRadToDeg);  // 0x000d11b0
        return other;
    }
    if (phase != 0) return other;
    const float dt = clock->m_afDeltaTime[0];
    const RwV3d& pos = FrameOf(this)->modelling.pos;
    m_vPosE0.x = ppc::fmadds(dt, m_vVelEC.x, pos.x);
    m_vPosE0.z = ppc::fmadds(dt, m_vVelEC.z, pos.z);
    m_vPosE0.y = ppc::fmadds(dt, m_vVelEC.y, pos.y);
    const float dt2 = clock->m_afDeltaTime[0];
    m_vVelEC.x = ppc::fmadds(dt2, m_vUnkF8.x, m_vVelEC.x);
    m_vVelEC.z = ppc::fmadds(dt2, m_vUnkF8.z, m_vVelEC.z);
    m_vVelEC.y = ppc::fmadds(dt2, m_vUnkF8.y, m_vVelEC.y);
    UpdateBounce(clock);
    SetFramePosition(FrameOf(this), m_vPosE0.x, m_vPosE0.y, m_vPosE0.z);
    if ((m_unkA8 & 0x10u) != 0) return 1;
    return other;
}

// 0x0047e968 CKHkS08CristalOrb_SnapToGround_maybe: the node put on the ground under the hot spot; without a ground
// there, the ground searched upwards from the thrown position (+0xe0) in ten steps of 0.5.
void CKHkS08CristalOrb::SnapToGround() {
    CVector3 at;
    m_pHotSpot40->GetWorldPosition(&at);  // 0x000ce790
    CGroundContactDatasIn in = ProbeIn(m_fUnkD8);
    Collision()->GroundProbePoints(&in, &m_GContactInOut, &at.x, 1);  // 0x00196540
    const uint8_t status = StatusByte(m_GContactInOut);
    if (status == 1 || status < 1) {
        at.y = m_GContactInOut.m_ProjectionOnGround.y;
        SetFramePosition(FrameOf(this), at.x, at.y, at.z);
        return;
    }
    if (status != 3) return;
    CVector3 probe = m_vPosE0;
    CVector3 found = {kNoPoint, kNoPoint, kNoPoint};
    for (int32_t i = 0; i < 10; ++i) {
        in = ProbeIn(m_fUnkD8);
        Collision()->GroundProbePoints(&in, &m_GContactInOut, &probe.x, 1);  // 0x00196540
        if (StatusByte(m_GContactInOut) <= 1) {
            found.x = m_GContactInOut.m_ProjectionOnGround.x;
            found.z = m_GContactInOut.m_ProjectionOnGround.z;
            found.y = m_GContactInOut.m_ProjectionOnGround.y;
            break;
        }
        probe.y = probe.y + kHalf;
    }
    if (kNoPoint != found.x || kNoPoint != found.y || kNoPoint != found.z) {
        SetFramePosition(FrameOf(this), found.x, found.y, found.z);
    }
}

// 0x0047ee48 CKHkS08CristalOrb_State0_Carried_maybe: carried. Enter (from state 1): the hero's pick-up animation
// (his dictionary +0x98 by his index), else the lerp to the hot spot; leave: off the hot spot, the hero let go. Tick: a
// hero no longer playing (or flag +0x354 bit 30) drops it (state 2, no velocity); the pick-up animation, then the
// lerp; the hero's throw input (with no taker +0x30) throws it along +0x104 (state 2) unless the hot spot is over no
// ground.
uint8_t CKHkS08CristalOrb::State0(IKTime* clock, int32_t phase, uint8_t other) {
    if (phase == 1) {
        if (other != 1) {
            m_unkA8 &= 0xfffffffcu;
            return other;
        }
        IKSerializable* dictionary = m_apRefs98[m_ui8HeroIndexA4];
        if (dictionary == nullptr) return other;
        const uint32_t word = static_cast<uint32_t>(static_cast<CAnimationDictionary*>(dictionary)->m_apAnimations[0]);
        if (CAnimationManager_GetAnimation(word) != nullptr) {
            HeroOf(this)->CrossfadeAnimResource(kCrossfade, kZero, word, 1);  // vt+0xc4
            m_unkA8 = (m_unkA8 & 0xfffffffdu) | 2u;
            return other;
        }
        BeginLerp(this);
        return other;
    }
    if (phase == 2) {
        DetachFromCarrierHotSpot();        // 0x0047bc10
        HeroOf(this)->DetachFromObject();  // 0x00364608
        return other;
    }
    if (phase != 0) return other;
    CKHkS08Hero* hero = HeroOf(this);
    if (hero->GetFlag354Bit30() != 0 || hero->IsPlayerControlled() == 0) {  // 0x00361de8, 0x00362af0
        m_unkA8 &= 0xfffffff7u;
        m_vVelEC.x = kNull.x;
        m_vVelEC.z = kNull.z;
        m_vVelEC.y = kNull.y;
        return 2;
    }
    if ((m_unkA8 & 2u) != 0) {
        if (hero->WillAnimEndWithin(clock->m_afDeltaTime[0]) == 0) {  // 0x00364020
            hero->AdvanceObjectAnimTime(clock->m_afDeltaTime[0]);     // 0x00363410
            return other;
        }
        BeginLerp(this);
        return other;
    }
    if ((m_unkA8 & 1u) != 0) {
        LerpToCarrierHotSpot(clock);  // 0x0047cc20
        return other;
    }
    if (static_cast<uint8_t>(hero->GetPlayerInputFlag358b21()) == 0) return other;  // 0x00362c98
    if (m_pUnk30 != nullptr) return other;
    m_unkA8 &= 0xfffffff7u;
    CMatrix34 world;
    m_pHotSpot40->GetWorldMatrix(&world);  // 0x000ce970
    CGroundContactDatasIn in = ProbeIn(m_fUnkD8);
    CVector3 point = world.m_pos;
    Collision()->GroundProbePoints(&in, &m_GContactInOut, &point.x, 1);  // 0x00196540
    if (static_cast<uint8_t>(StatusByte(m_GContactInOut) - 2u) <= 1) return other;
    Mat4_TransformVectors(&world, &m_vVelEC, &m_vUnk104, 1);  // 0x0023f7b0
    const float speed = m_fUnk110;
    m_vVelEC.x = speed * m_vVelEC.x;
    m_vVelEC.z = speed * m_vVelEC.z;
    m_vVelEC.y = speed * m_vVelEC.y;
    const CVector3 carrier = HeroOf(this)->GetDerivedVelocity();  // 0x0032a730
    m_vVelEC.x = m_vVelEC.x + carrier.x;
    m_vVelEC.y = m_vVelEC.y + carrier.y;
    m_vVelEC.z = m_vVelEC.z + carrier.z;
    return 2;
}

// 0x0047f520 CKHkS08CristalOrb_Start: the base's, the four handler pairs, state 1 entered (other 0xff), the runtime
// cleared (bits 0, 2, 3, 8, 9 of +0xa8; the contact's defaults).
void CKHkS08CristalOrb::Start() {
    CKHkActorBase::Start();  // 0x003f6e48
    m_aStateTable[7] = 0;
    m_aStateTable[0] = 0x00bc1f28u;  // TOC1 +0x5c14: State0
    m_aStateTable[3] = 0;
    m_aStateTable[1] = 0;
    m_aStateTable[5] = 0;
    m_aStateTable[2] = 0x00bc1ea8u;  // TOC1 +0x5c10: State1
    m_aStateTable[4] = 0x00bc1f00u;  // TOC1 +0x5c18: State2
    m_aStateTable[6] = 0x00bc1c30u;  // TOC1 +0x5c1c: State3 (KStub_ReturnArg4_47b680)
    m_ui8State = 1;
    m_ui8NbStates = 4;
    m_pStateTable = m_aStateTable;
    CallState(&m_pStateTable[2], nullptr, 1, 0xff);
    m_vUnk50.x = kNull.x;
    m_vUnk50.z = kNull.z;
    m_vUnk50.y = kNull.y;
    m_vUnk44.x = kNull.x;
    m_unk5C = 0;
    m_vUnk44.y = kNull.y;
    m_vUnk44.z = kNull.z;
    m_pHero9C = nullptr;
    m_pHotSpot40 = nullptr;
    m_unkA8 &= 0xfffffcf2u;
    m_GContactInOut.m_i32FaceIndex = -1;
    m_GContactInOut.m_eContactStatus = 3;
    m_GContactInOut.m_ui8SectorNumber = 0;
    m_GContactInOut.m_pGround = nullptr;
    m_unk124 = 0;
    m_pUnk2C = nullptr;
    m_pUnk30 = nullptr;
    m_unk128 = 0;
}

// 0x0047f6b8 CKHkS08CristalOrb_Restart: unless the key's flag (+0x20's byte +0x34) is set: carried (state 0) and not
// lerping, a landed orb (bit 5) goes back to rest on the ground, else the hero takes it again.
void CKHkS08CristalOrb::Restart() {
    m_unk128 = 0;
    m_unk124 = 0;
    if (static_cast<CKHkS08CristalKey*>(m_pUnk20)->m_unk34 != 0) return;
    const uint8_t state = m_ui8State;
    if (state != 0) return;
    if ((m_unkA8 & 1u) != 0) return;
    if ((m_unkA8 & 0x20u) != 0) {
        CallState(&m_pStateTable[0], nullptr, 2, 1);
        m_ui8State = 1;
        CallState(&m_pStateTable[2], nullptr, 1, state);
        SnapToGround();  // 0x0047e968 (a tail call)
        return;
    }
    HeroOf(this)->DetachFromObject();       // 0x00364608
    HeroOf(this)->AttachToObject(this, 1);  // 0x00362360
}

// 0x0047f888 CKHkS08CristalOrb_Update: the base's, the machine's tick and switch; then an offered taker (+0x30) asked
// with message 0x900 while the hero gives the input: accepted (0), the orb is handed over (state 3, +0x2c the taker,
// +0xa8 bit 9). +0x30 is cleared either way.
void CKHkS08CristalOrb::Update(IKTime* clock) {
    CKHkActorBase::Update(clock);  // 0x003f6e68
    uint8_t state = m_ui8State;
    if (state != 0xff) {
        const uint8_t next = CallState(&m_pStateTable[state * 2u], clock, 0, state);
        state = m_ui8State;
        if (next != state) {
            if (state != 0xff) CallState(&m_pStateTable[state * 2u], clock, 2, next);
            m_ui8State = next;
            if (next != 0xff) CallState(&m_pStateTable[next * 2u], clock, 1, state);
        }
    }
    if (m_pUnk30 != nullptr && static_cast<uint8_t>(HeroOf(this)->GetPlayerInputFlag358b21()) != 0) {  // 0x00362c98
        if (m_pUnk30->MessageProc(0x900, this) == 0) {  // vt+0x1c
            const uint8_t old = m_ui8State;
            if (old != 0xff) CallState(&m_pStateTable[old * 2u], clock, 2, 3);
            m_ui8State = 3;
            CallState(&m_pStateTable[6], clock, 1, old);
            m_pUnk2C = m_pUnk30;
            m_unkA8 = (m_unkA8 & 0xfffffdffu) | 0x200u;
            m_pUnk30 = nullptr;
            return;
        }
    }
    m_pUnk30 = nullptr;
}
