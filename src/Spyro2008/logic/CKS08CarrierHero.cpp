// CKS08CarrierHero.cpp - reconstructed original translation unit 0x4b08d8-0x4b4750 (GAME_TOC1, main_toc1), 40 functions, 36 live.
// Primary class: CKS08CarrierHero  key 0x91cc  category Logic  size 0xbc  vtable 0xb28d98
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x4b08d8  CKS08CarrierHero_Delete
//   [x] 0x4b0928  CKS08CarrierHero_vf78  (header)
//   [x] 0x4b0960  CKS08CarrierHero_IsCarriedObjectAttachedToCarrierHotSpot_maybe
//   [x] 0x4b0a00  CKS08CarrierHero_SetNearbyReceiver_maybe
//   [x] 0x4b0a38  CKS08CarrierHero_HasNearbyReceiver_maybe  (header)
//   [ ] 0x4b0a40  CKS08CarrierHero_GetNearbyReceiver_maybe  [dead]
//   [x] 0x4b0a48  CKS08CarrierHero_CaptureCarryPose_maybe  (CKS08CarrierHero::CaptureCarryPose)
//   [x] 0x4b0bd0  CKS08CarrierHero_CanPickUp_maybe
//   [ ] 0x4b0cc8  CKS08CarrierHero_Save
//   [x] 0x4b0cf0  CKS08CarrierHero_RecursiveRegistration  (KBase910C's (KBase910C_vf24: nothing registered), then 1)
//   [x] 0x4b0d18  CKS08CarrierHero_Destroy
//   [x] 0x4b0d60  CKS08CarrierHero_DeleteArray
//   [x] 0x4b0e00  CKS08CarrierHero_Construct  [dead]
//   [ ] 0x4b0e58  RegisterCKS08CarrierHeroClass
//   [ ] 0x4b0ee0  _GLOBAL__D_4b0ee0
//   [ ] 0x4b0ef0  _GLOBAL__I_4b0ef0
//   [x] 0x4b0f00  CKS08CarrierHero_DestructBody  (header)
//   [x] 0x4b0f30  CKS08CarrierHero_DropCarriedObject_maybe
//   [x] 0x4b1080  CKS08CarrierHero_DeletingDestructor  (the destructor; delete)
//   [x] 0x4b10c8  CKS08CarrierHero_Destructor  (header)
//   [ ] 0x4b10f8  CKS08CarrierHero_Construct_2  [dead]
//   [x] 0x4b1150  CKS08CarrierHero_StartCarrying_2_maybe  (= 0x4b4300 CKS08CarrierHero_StartCarrying_maybe (the same code, other registers))
//   [x] 0x4b1368  CKS08CarrierHero_PostLoad  (returns 1: the root's default)
//   [x] 0x4b1370  CKS08CarrierHero_vf5C
//   [x] 0x4b14e0  CKS08CarrierHero_StopCarrying_maybe
//   [x] 0x4b1628  CKS08CarrierHero_LerpCarriedObjectToHotSpot_maybe
//   [x] 0x4b19f0  CKS08CarrierHero_vf60  (= 0x4b0960 IsCarriedObjectAttachedToCarrierHotSpot (the same code))
//   [x] 0x4b1a90  CKS08CarrierHero_CreateArray
//   [x] 0x4b1b60  CKS08CarrierHero_Create
//   [x] 0x4b1bc8  CKS08CarrierHero_IsInGrabRangeAndAngle_maybe
//   [x] 0x4b1de0  CKS08CarrierHero_FindPickupInRange_maybe
//   [ ] 0x4b2200  CKS08CarrierHero_FindAnyPickupInRange_maybe  [dead]
//   [x] 0x4b2288  CKS08CarrierHero_Load
//   [x] 0x4b26c0  CKS08CarrierHero_CarryState_maybe
//   [x] 0x4b30f8  CKS08CarrierHero_State1_LookForPickup_maybe
//   [x] 0x4b3958  CKS08CarrierHero_MessageProc
//   [x] 0x4b3e40  CKS08CarrierHero_DropCarriedObjectAndReset_maybe
//   [x] 0x4b4118  CKS08CarrierHero_Reset_maybe
//   [x] 0x4b4300  CKS08CarrierHero_StartCarrying_maybe
//   [x] 0x4b4518  CKS08CarrierHero_UpdateStateMachine
//
//   [x] 0x9c5468  CKS08CarrierHero_IsKindOfClass  [inline]
//   [x] 0x9c54a0  CKS08CarrierHero_GetClassType  [inline]
//   [x] 0x9c54a8  CKS08CarrierHero_GetClassID  [inline]
//   [x] 0x9c54b0  CKS08CarrierHero_vf64  [inline]  (header)
//   [x] 0x9c54b8  CKS08CarrierHero_vf84  [inline]  (header)
//   [x] 0x9c54c0  CKS08CarrierHero_vf7C  [inline]  (header)
//   [x] 0x9c54c8  CKS08CarrierHero_vf80  [inline]  (header)
#include "Spyro2008/logic/CKS08CarrierHero.h"
#include "k2000/groups/IKBaseGroup.h"
#include "k2000/scenegraph/CSGBranch.h"
#include "k2000/misc/Engine.h"
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/core/Ps3MemberFn.h"
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "k2000/core/Stub.h"
#include "Spyro2008/hooks/CKHkS08TransportableKey.h"
#include "k2000/fx/IKFx.h"
#include "k2000/groups/CKGrpTransportableObject.h"

#include "k2000/io/IKFile.h"
#include "k2000/logic/fx/CKInputIconNodeFx.h"
#include "k2000/logic/IKFxData.h"
#include "k2000/memory/KObjectRefList.h"
#include "k2000/render/CRenderer.h"
#include "k2000/services/CKSrvDynamic.h"
#include "k2000/services/CKSrvFx.h"
#include "k2000/scenegraph/CSGLeaf.h"
#include "k2000/math/CMatrix34.h"
#include "Renderware/rwcore/RwCamera.h"
#include "Spyro2008/groups/C22SpyroShims.h"
#include "Spyro2008/logic/CKS08GameManager.h"
#include "crt/ppc_ops.h"
#include "crt/xsinf.h"
#include "k2000/dictionaries/CAnimationDictionary.h"
#include "k2000/dictionaries/CKSoundDictionaryID.h"
#include "k2000/graphical/CKAnmKeyFrameController.h"
#include "k2000/graphical/animation/CAnimationManager.h"
#include "k2000/graphical/animation/CKBlenderController.h"
#include "k2000/hooks/CKHkPressionStone.h"
#include "k2000/logic/sound/CKSound.h"
#include "k2000/math/Quat.h"
#include "k2000/misc/CKGrpMeca.h"
#include "k2000/services/CKSrvCollision.h"
#include "k2000/services/CollisionDatas.h"
#include "k2000/system/IKTime.h"

#include <cfloat>
#include <cmath>
#include <cstring>

// 0x00426be8 CarryTarget_GetGroundedPlacementPoint_maybe (CKHkTransportableObjectSpawner.cpp).
CVector3 CarryTarget_GetGroundedPlacementPoint(IKSerializable* target);

// 0x004b2288 CKS08CarrierHero_Load: the base's Load, then (level data only) two floats, a counted word
// array, references and floats in the file's order.
int32_t CKS08CarrierHero::Load(IKFile* file, int32_t type) {
    KBase910C::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadF32LE(file, &m_unk34);
    ReadF32LE(file, &m_unk30);
    ReadU32LE(file, &m_ui32NbUnk24);
    m_aui32Unk24 = new uint32_t[m_ui32NbUnk24];
    for (uint32_t i = 0; i < m_ui32NbUnk24; ++i) ReadU32LE(file, &m_aui32Unk24[i]);
    IKFile_ReadRef(file, &m_pHotSpot);
    IKFile_ReadRef(file, &m_pAnimDico);
    IKFile_ReadRef(file, &m_pHero);
    ReadF32LE(file, &m_unk40);
    IKFile_ReadRef(file, &m_pBranch);
    IKFile_ReadRef(file, &m_pSoundDico);
    ReadF32LE(file, &m_unk0c);
    return 1;
}

namespace {
using CarrierStateFn = uint8_t (CKS08CarrierHero::*)(IKTime* clock, int32_t phase, uint8_t other);
// DOTD: the carrier's state handlers by descriptor (the table Reset builds at +0xac).
Ps3MemberFnEntry<CarrierStateFn> g_carrierStates[] = {
    {0x00bc7c38u, &CKS08CarrierHero::CarryState, "CKS08CarrierHero_CarryState_maybe 0x4b26c0", false},
    {0x00bc7c40u, &CKS08CarrierHero::State1LookForPickup, "CKS08CarrierHero_State1_LookForPickup_maybe 0x4b30f8", false},
};

CSGLeaf* NodeOf(IKSerializable* object) { return static_cast<CSGLeaf*>(static_cast<IKHook*>(object)->m_pKGLObject); }
const RwV3d& LtmPos(IKSerializable* object) { return FrameLtm(NodeOf(object)->m_pRwFrame)->pos; }

// The node's frame modelling position set (the identity flag cleared), the frame marked dirty (0x10698).
void SetNodePosition(CSGLeaf* node, float x, float y, float z) {
    RwFrame* frame = node->m_pRwFrame;
    frame->modelling.pos.x = x;
    frame->modelling.pos.y = y;
    frame->modelling.pos.z = z;
    frame->modelling.flags &= 0xfffdffffu;
    RwFrame_MarkDirty(frame);
}

// 0x00362ac8 CKHkS08Hero_GetPlayerIndexIfControlled_maybe (hero unit; inlined here): the player index (+0x26, sign-extended)
// when the hero is the tracked leader, else -1.
uint8_t PlayerIndexIfControlled(const CKHkS08Hero* hero) {
    return hero->m_ui8Hero == hero->m_ui8TrackedLeader ? hero->m_ui8Leader : 0xffu;
}

// The carrier's pickup-icon effect: the transportable's group's input icon data (+0x38) through the pooled lookup.
CKInputIconNodeFx* AcquireIcon(CKS08CarrierHero* carrier, IKSerializable* object) {
    CKGrpTransportableObject* group =
        static_cast<CKGrpTransportableObject*>(static_cast<CKHkS08TransportableBase*>(object)->Vf130());  // vt+0x130
    return static_cast<CKInputIconNodeFx*>(
        static_cast<CKSrvFx*>(g_pEngine->m_srvFx)->AcquireFx(static_cast<IKFxData*>(group->m_pUnk38), carrier));
}

void PlaceIcon(CKInputIconNodeFx* icon, IKSerializable* object) {
    const RwV3d& p = LtmPos(object);
    const CVector3 at = {p.x, p.y, p.z};
    icon->SetPosition(&at);  // 0x001c45c8
}

// 0x00c50d64 / 0x00c50da0 (static initialisers): the null vector and the "no point" vector (FLT_MAX x3).
const CVector3 kZero = {0.0f, 0.0f, 0.0f};
const CVector3 kNoPoint = {FLT_MAX, FLT_MAX, FLT_MAX};

// 0x00c50e14: the identity matrix CKGraphic_InitializeModule creates (RwMatrixCreate_Thunk) and nothing changes.
const RwMatrix* IdentityRw() {
    static const CMatrix34 identity = [] {
        CMatrix34 m;
        std::memset(&m, 0, sizeof m);
        m.m_right.x = 1.0f;
        m.m_up.y = 1.0f;
        m.m_at.z = 1.0f;
        m.m_ui32Flags = 0x20003u;
        return m;
    }();
    return reinterpret_cast<const RwMatrix*>(&identity);
}

// The inlined cosine of an angle (game form for a clear sign bit, the library's cosf of -x otherwise).
float CosOfAngle(float angle) {
    uint32_t bits;
    std::memcpy(&bits, &angle, sizeof(bits));
    if (static_cast<int32_t>(bits) < 0) return crt::LibCosf(-angle);
    return crt::InlineCosf(angle);
}
}  // namespace

// 0x004b0d18 CKS08CarrierHero_Destroy
void CKS08CarrierHero::Destroy() {
    KBase910C::Destroy();  // 0x004ac390 KStub_Nop_4ac390
    if (m_aui32Unk24 != nullptr) delete[] m_aui32Unk24;
}

// 0x004b0a00 CKS08CarrierHero_SetNearbyReceiver_maybe: set: a receiver kept with the flag; cleared: only by the receiver
// kept.
void CKS08CarrierHero::SetNearbyReceiver(uint8_t set, IKSerializable* receiver) {
    if (set == 0) {
        if (m_pReceiver != receiver) return;
        m_pReceiver = nullptr;
        m_bNearbyReceiver = 0;
        return;
    }
    if (receiver == nullptr) return;
    m_pReceiver = receiver;
    m_bNearbyReceiver = 1;
}

// 0x004b0960 CKS08CarrierHero_IsCarriedObjectAttachedToCarrierHotSpot_maybe
uint8_t CKS08CarrierHero::IsCarriedObjectAttachedToCarrierHotSpot() const {
    if (m_pCarriedObject == nullptr) return 0;
    CSGLeaf* node = NodeOf(m_pCarriedObject);
    const CSGHotSpot* spot = static_cast<const CSGHotSpot*>(m_pHotSpot);
    if (spot->m_pParent == node->m_pParent && node->m_ui8BoneParent == spot->m_ui8BoneNumber) return 1;
    if (m_pBranch == nullptr) return 0;
    return node->m_pParent == static_cast<CSGBranch*>(m_pBranch) ? 1 : 0;
}

// 0x004b0bd0 CKS08CarrierHero_CanPickUp_maybe: nothing carried, a class it carries (vt+0x78), a player-controlled hero
// that is not in a combo.
uint8_t CKS08CarrierHero::CanPickUp(IKSerializable* object) {
    if (object == nullptr || m_pCarriedObject != nullptr) return 0;
    const uint32_t id = static_cast<uint32_t>(object->GetClassID());  // vt+0x18
    if (Vf78(&id) == 0) return 0;
    CKHkS08Hero* hero = static_cast<CKHkS08Hero*>(m_pHero);
    if (hero->IsPlayerControlled() == 0) return 0;  // 0x00362af0
    return hero->IsInCombo() == 0 ? 1 : 0;          // 0x0032a698
}

// 0x004b4300 CKS08CarrierHero_StartCarrying_maybe: the hero attached to the carrier (mode 1); then its dynamic entry off,
// the object controlling its animation, locked (externally positioned), attached movement on with speed 0 (+0x3dc,
// +0x530); the object carried; with +0x90 the machine switched to state 0 (carrying; no clock).
uint8_t CKS08CarrierHero::StartCarrying(IKSerializable* object) {
    CKHkS08Hero* hero = static_cast<CKHkS08Hero*>(m_pHero);
    if (hero->AttachToObject(this, 1) == 0) return 0;  // 0x00362360
    static_cast<CKSrvDynamic*>(g_pEngine->m_srvDynamic)->SetEntryFlag(hero, 0);  // 0x0023aff8
    hero->SetObjectControlsAnim(1);                          // 0x00362010
    hero->SetExternallyPositionedAndPhysics(1, nullptr, nullptr);  // 0x0032a638
    hero->SetAttachedMovementEnabled(1);                     // 0x00362050
    if ((hero->m_ui32HeroFlags358 & 8u) != 0) hero->m_unk3dc = 0.0f;   // 0x00362670 IKHkHero_SetAttachedMoveSpeed_maybe (TOC +0x6408)
    hero->SetUnk530IfAttachedMovement(0.0f);                 // 0x003626a0
    m_pCarriedObject = object;
    if (m_bUnk90 == 0) return 1;
    const uint8_t old = m_unka8;
    if (old != 0xff) CallState(&m_pStateTable[old * 2u], nullptr, 2, 0);
    m_unka8 = 0;
    CallState(&m_pStateTable[0], nullptr, 1, old);
    return 1;
}

// 0x004b14e0 CKS08CarrierHero_StopCarrying_maybe: the object's node under sector 0's root at the hot spot's world position;
// nothing carried.
uint8_t CKS08CarrierHero::StopCarrying(IKSerializable* object) {
    CMatrix34 m;
    static_cast<CSGHotSpot*>(m_pHotSpot)->GetWorldMatrix(&m);  // 0x000ce970
    ReparentToBaseSectorRoot(NodeOf(object));
    SetNodePosition(NodeOf(object), m.m_pos.x, m.m_pos.y, m.m_pos.z);
    m_pCarriedObject = nullptr;
    return 1;
}

// 0x004b0f30 CKS08CarrierHero_DropCarriedObject_maybe: the carried object back into the pool (ReleaseObject), its node
// under sector 0's root, its state machine reset (vt+0x11c); the icon effect released.
void CKS08CarrierHero::DropCarriedObject() {
    if (m_pCarriedObject != nullptr) {
        static_cast<CKGrpTransportableObject*>(m_pUnk10)->ReleaseObject(m_pCarriedObject);  // 0x004a7ce0
        ReparentToBaseSectorRoot(NodeOf(m_pCarriedObject));
        static_cast<CKHkS08TransportableBase*>(m_pCarriedObject)->ResetStateMachine();  // vt+0x11c
        m_pCarriedObject = nullptr;
    }
    if (m_pUnk94 != nullptr) {
        static_cast<IKFx*>(m_pUnk94)->StopAndRelease(this);  // vt+0x58
        m_pUnk94 = nullptr;
    }
}

// 0x004b1de0 CKS08CarrierHero_FindPickupInRange_maybe. The live objects of the list (from the pool boundary +0x0c to the
// count), until a null slot: |dy| < 1.5 (TOC +0x644c), d^2 <= +0x30^2, the flat direction's dot with the hero's at axis
// above cos(+0x34), vt+0xf4 and vt+0x110.
IKSerializable* CKS08CarrierHero::FindPickupInRange(uint32_t key) {
    KObjectRefList* list = static_cast<CKGrpTransportableObject*>(m_pUnk10)->FindListByKey(key);  // 0x004a7538
    if (list->m_ui32Count == list->m_ui32Count2) return nullptr;
    CKHkS08Hero* hero = static_cast<CKHkS08Hero*>(m_pHero);
    const RwV3d& h = LtmPos(hero);
    const float hz = h.z;
    const float hx = h.x;
    const float hy = h.y;
    for (uint32_t i = list->m_ui32Count2; i != list->m_ui32Count; ++i) {
        IKSerializable* object = list->m_pBlock[i];
        if (object == nullptr) return nullptr;
        const RwV3d& p = LtmPos(object);
        const float dy = p.y - hy;
        if (std::fabs(dy) >= 1.5f) continue;  // bge: NaN passes
        const float dx = p.x - hx;
        const float dz = p.z - hz;
        const float r = m_unk30;
        if (!(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)) <= r * r)) continue;
        const RwV3d& q = LtmPos(object);
        const RwV3d& g = LtmPos(hero);
        float ex = q.x - g.x;
        float ey = q.y - g.y;
        float ez = q.z - g.z;
        const float length = static_cast<float>(c22spyro::MathSqrtf(ppc::fmadds(ez, ez, ppc::fmadds(ex, ex, ey * ey))));
        if (length != 0.0f) {
            const float inv = 1.0f / length;
            ez = ez * inv;
            ex = ex * inv;
            ey = ey * inv;
        }
        const float limit = CosOfAngle(m_unk34);
        const RwV3d& at = FrameLtm(NodeOf(hero)->m_pRwFrame)->at;
        const float dot = ppc::fmadds(ez, at.z, ppc::fmadds(ex, at.x, ey * at.y));
        CKHkS08TransportableBase* item = static_cast<CKHkS08TransportableBase*>(object);
        if (limit < dot && item->VfF4(this) != 0 && item->Vf110() != 0) return object;
    }
    return nullptr;
}

// 0x004b30f8 CKS08CarrierHero_State1_LookForPickup_maybe (state 1). Enter: no last candidate. Leave: none, the icon
// released. Tick: a key, power bucket or weight in range (in that order) that the carrier can pick up becomes the pickup
// (+0x14), the player's interaction target (SetHeroInteractionTarget) and the hero's carrying flag (0x32a438). A hero not
// player-controlled loses the icon; a controlled one shows the icon over the candidate while it was drawn this frame
// (+0x16 = the render frame counter), acquired when the candidate changes; the candidate kept in +0x98.
uint8_t CKS08CarrierHero::State1LookForPickup(IKTime* /*clock*/, int32_t phase, uint8_t other) {
    if (phase == 1) {
        m_pLastCandidate = nullptr;
        return other;
    }
    if (phase == 2) {
        m_pLastCandidate = nullptr;
        if (m_pUnk94 != nullptr) {
            static_cast<IKFx*>(m_pUnk94)->StopAndRelease(this);
            m_pUnk94 = nullptr;
        }
        return other;
    }
    if (phase != 0) return other;
    CKHkS08Hero* hero = static_cast<CKHkS08Hero*>(m_pHero);
    IKSerializable* found = nullptr;
    if (m_pUnk10 != nullptr) {
        found = FindPickupInRange(0xc2);
        if (found == nullptr) found = FindPickupInRange(0xc3);
        if (found == nullptr) found = FindPickupInRange(0xc5);
        if (found != nullptr && CanPickUp(found) != 0) {  // vt+0x58
            m_unk14 = found;
            static_cast<CKS08GameManager*>(g_pEngine->m_gameManager)->SetHeroInteractionTarget(this, 1, PlayerIndexIfControlled(hero));
            hero->SetCarryingObject(1);  // 0x0032a438
        }
    }
    auto releaseIcon = [this]() {
        static_cast<IKFx*>(m_pUnk94)->StopAndRelease(this);  // vt+0x58
        m_pUnk94 = nullptr;
    };
    if (hero->IsPlayerControlled() == 0) {
        if (m_pUnk94 != nullptr) releaseIcon();
        m_pLastCandidate = found;
        return other;
    }
    if (m_pLastCandidate == found) {
        if (found != nullptr) {
            if (NodeOf(found)->m_ui16LastRenderedFrame != g_ui16RenderFrameCounter) {
                if (m_pUnk94 != nullptr) releaseIcon();
                m_pLastCandidate = found;
                return other;
            }
            if (m_pUnk94 == nullptr) {
                m_pUnk94 = AcquireIcon(this, found);
                if (m_pUnk94 == nullptr) {
                    m_pLastCandidate = found;
                    return other;
                }
            }
            PlaceIcon(static_cast<CKInputIconNodeFx*>(m_pUnk94), found);
        }
    } else {
        if (m_pLastCandidate != nullptr && m_pUnk94 != nullptr) releaseIcon();
        if (found != nullptr && NodeOf(found)->m_ui16LastRenderedFrame == g_ui16RenderFrameCounter) {
            m_pUnk94 = AcquireIcon(this, found);
            if (m_pUnk94 == nullptr) {
                m_pLastCandidate = found;
                return other;
            }
            PlaceIcon(static_cast<CKInputIconNodeFx*>(m_pUnk94), found);
        }
    }
    if (m_pUnk94 != nullptr) PlaceIcon(static_cast<CKInputIconNodeFx*>(m_pUnk94), found);
    m_pLastCandidate = found;
    return other;
}

// A state handler of the carrier's table: the native function, or (not ported) the state it was given.
uint8_t CKS08CarrierHero::CallState(const uint32_t pair[2], IKTime* clock, int32_t phase, uint8_t other) {
    CarrierStateFn fn = ResolvePs3MemberFn(g_carrierStates, pair, "CKS08CarrierHero state handler");
    if (fn == nullptr) return other;
    return (this->*fn)(clock, phase, other);
}

// 0x004b4118 CKS08CarrierHero_Reset_maybe (vt+0x68): the carry state machine (two states, TOC +0x6488 / +0x648c) in
// state 1 (looking for a pickup, entered with no clock), the last object of class id 0x35 of the game manager's list
// (+0x0c: a group, its child groups from +0x18 through +0x14), nothing carried, and the carry volume's node hung under the hot spot.
void CKS08CarrierHero::Reset() {
    m_aStateTable[0] = 0x00bc7c38u;
    m_aStateTable[2] = 0x00bc7c40u;
    m_aStateTable[3] = 0;
    m_aStateTable[1] = 0;
    m_unka8 = 1;
    m_unka9 = 2;
    m_pStateTable = &m_aStateTable[0];
    CallState(&m_pStateTable[2], nullptr, 1, 0xff);
    CDefaultGameManager* manager = g_pEngine->m_gameManager;
    IKSerializable* list = manager->m_unk04[2];  // +0x0c
    m_pUnk10 = nullptr;
    if (list != nullptr) {
        for (IKBaseGroup* group = static_cast<IKBaseGroup*>(list)->m_lChilds; group != nullptr; group = group->m_pNextGroup) {
            if (group->GetClassID() == 0x35) m_pUnk10 = group;  // vt+0x18
        }
    }
    m_pUnk94 = nullptr;              // +0x94
    m_pCarriedObject = nullptr;      // +0x18
    m_bUnk90 = 0;                    // the byte at +0x90
    if (m_pHotSpot != nullptr) {
        CSGBranch* branch = static_cast<CSGBranch*>(m_pBranch);
        CSGBranch* parent = branch->m_pParent;
        if (parent != nullptr) parent->RemoveChild(branch);  // vt+0x78
        static_cast<CSGHotSpot*>(m_pHotSpot)->AttachVolume(branch);  // 0x000ce2b8
    }
    m_bNearbyReceiver = 0;      // the byte at +0x9c
    m_pReceiver = nullptr;      // +0xa0
}

// 0x004b4518 CKS08CarrierHero_UpdateStateMachine (vt+0x74): the hero is not carrying (CKHkS08Hero_SetCarryingObject_maybe
// 0x32a438 with 0: +0xed4 bit 3), the carrier's state machine runs (handlers +0xa4, current state +0xa8), then +0x9c
// and +0xa0 clear. The states' handlers are C2.8 (carrying).
void CKS08CarrierHero::UpdateStateMachine(IKTime* clock) {
    CKHkS08Hero* hero = static_cast<CKHkS08Hero*>(m_pHero);
    hero->SetCarryingObject(0);  // 0x0032a438
    const uint8_t state = m_unka8;
    if (state != 0xff) {
        const uint8_t next = CallState(&m_pStateTable[state * 2u], clock, 0, state);
        const uint8_t current = m_unka8;
        if (next != current) {
            if (current != 0xff) CallState(&m_pStateTable[current * 2u], clock, 2, next);
            m_unka8 = next;
            if (next != 0xff) CallState(&m_pStateTable[next * 2u], clock, 1, current);
        }
    }
    m_bNearbyReceiver = 0;      // the byte at +0x9c
    m_pReceiver = nullptr;      // +0xa0
}

// 0x004b3e40 CKS08CarrierHero_DropCarriedObjectAndReset_maybe (vt+0x70; CKHkS08Hero_Restart): a carried object (a key
// only when its vt+0x15c byte is set) goes back to the transportable group's pool (ReleaseObject), its node under
// sector 0's root, its state machine reset (vt+0x11c); nothing carried; the carry machine leaves its state for state 1
// (no clock) and enters it; then the effect +0x94 released (vt+0x58 with the carrier as owner).
void CKS08CarrierHero::DropCarriedObjectAndReset() {
    CKHkS08TransportableBase* carried = static_cast<CKHkS08TransportableBase*>(m_pCarriedObject);
    if (carried != nullptr &&
        (carried->GetClassID() != 0xc2 || static_cast<CKHkS08TransportableKey*>(carried)->Vf15C() != 0)) {  // vt+0x18 / +0x15c
        static_cast<CKGrpTransportableObject*>(m_pUnk10)->ReleaseObject(carried);  // 0x004a7ce0
        ReparentToBaseSectorRoot(static_cast<CSGLeaf*>(carried->m_pKGLObject));
        carried->ResetStateMachine();  // vt+0x11c
        m_pCarriedObject = nullptr;
        const uint8_t old = m_unka8;
        if (old != 0xff) CallState(&m_pStateTable[old * 2u], nullptr, 2, 1);
        m_unka8 = 1;
        CallState(&m_pStateTable[2], nullptr, 1, old);
    }
    if (m_pUnk94 != nullptr) {
        static_cast<IKFx*>(m_pUnk94)->StopAndRelease(this);  // vt+0x58
        m_pUnk94 = nullptr;
    }
}

// The carried node hung under the carry branch (+0x3c) at the identity (0x00c50e14) when it has a grip (vt+0x118), else
// under the hot spot (AttachVolume). The node leaves its parent first (vt+0x78; no null test in the original).
void CKS08CarrierHero::AttachCarriedNode() {
    CKHkS08TransportableBase* carried = static_cast<CKHkS08TransportableBase*>(m_pCarriedObject);
    CSGLeaf* node = NodeOf(carried);
    if (carried->Vf118() != nullptr) {  // vt+0x118
        node->m_pParent->RemoveChild(node);                      // vt+0x78
        static_cast<CSGBranch*>(m_pBranch)->AddChild(NodeOf(carried));  // vt+0x70
        NodeOf(carried)->SetLocalMatrix(IdentityRw());           // 0x000d0be8
        return;
    }
    node->m_pParent->RemoveChild(node);  // vt+0x78
    static_cast<CSGHotSpot*>(m_pHotSpot)->AttachVolume(NodeOf(carried));  // 0x000ce2b8
}

void CKS08CarrierHero::CaptureOrAttachCarried() {
    if (m_bUnk90 != 0) {
        AttachCarriedNode();
        return;
    }
    CaptureCarryPose();  // 0x004b0a48
}

// 0x004b0a48 CKS08CarrierHero_CaptureCarryPose_maybe: the carried node's modelling position (+0x84), the hot spot's world
// orientation (+0x64) and the node's own (+0x74) as quaternions, the lerp time (+0x44) back to 0.
void CKS08CarrierHero::CaptureCarryPose() {
    const RwFrame* frame = NodeOf(m_pCarriedObject)->m_pRwFrame;
    m_vStartPos.x = frame->modelling.pos.x;
    m_vStartPos.y = frame->modelling.pos.y;
    m_vStartPos.z = frame->modelling.pos.z;
    CMatrix34 spot;
    static_cast<CSGHotSpot*>(m_pHotSpot)->GetWorldMatrix(&spot);  // 0x000ce970
    Quat_FromMatrix(m_aQuatHotSpot, reinterpret_cast<const float*>(&spot));  // 0x002420f8
    // The node's modelling matrix copied word by word (its rotation rows with their pad words, the position).
    const RwFrame* f = NodeOf(m_pCarriedObject)->m_pRwFrame;
    CMatrix34 own;
    std::memcpy(&own, &f->modelling, sizeof own);
    Quat_FromMatrix(m_aQuatStart, reinterpret_cast<const float*>(&own));
    m_fCarryTime = 0.0f;  // stw 0
}

// 0x004b1628 CKS08CarrierHero_LerpCarriedObjectToHotSpot_maybe. The lerp time grows by the frame; with a lerp length
// above 0 and the time still under it the carried node's position goes from the start (+0x84) towards the hot spot's world
// position by min(t / length, 1) (fmadds), its orientation slerped from +0x74 to the hot spot's (+0x64, refreshed) by
// t / length (unclamped); at 1 (or with no length) the node is hung under the branch or the hot spot.
void CKS08CarrierHero::LerpCarriedObjectToHotSpot(IKTime* clock) {
    const float time = m_fCarryTime + clock->m_afDeltaTime[0];
    const float length = m_unk40;
    m_fCarryTime = time;
    if (!(length <= 0.0f) && time < length) {  // ble (NaN goes on), then blt
        float t = time / length;
        if (!(t < 1.0f)) t = 1.0f;  // blt: NaN -> 1
        static_cast<CKHkS08TransportableBase*>(m_pCarriedObject)->Vf118();  // vt+0x118 (result unused)
        CVector3 target;
        static_cast<CSGHotSpot*>(m_pHotSpot)->GetWorldPosition(&target);  // 0x000ce790
        CSGLeaf* node = NodeOf(m_pCarriedObject);
        RwFrame* frame = node->m_pRwFrame;
        frame->modelling.pos.x = ppc::fmadds(t, target.x - m_vStartPos.x, m_vStartPos.x);
        frame->modelling.pos.y = ppc::fmadds(t, target.y - m_vStartPos.y, m_vStartPos.y);
        frame->modelling.pos.z = ppc::fmadds(t, target.z - m_vStartPos.z, m_vStartPos.z);
        frame->modelling.flags &= 0xfffdffffu;
        RwFrame_MarkDirty(frame);  // 0x00010698
        CMatrix34 spot;
        static_cast<CSGHotSpot*>(m_pHotSpot)->GetWorldMatrix(&spot);
        Quat_FromMatrix(m_aQuatHotSpot, reinterpret_cast<const float*>(&spot));
        float q[4];
        Quat_Slerp(m_fCarryTime / m_unk40, q, m_aQuatStart, m_aQuatHotSpot);  // 0x00242728
        CMatrix34 m;
        std::memset(&m, 0, sizeof m);  // the words the original clears (pads left as they are: unread)
        m.m_right.x = 1.0f;
        m.m_up.y = 1.0f;
        m.m_at.z = 1.0f;
        m.m_ui32Flags = 0x20003u;
        Quat_ToMatrixNormalizing(q, &m);  // 0x00241d78
        const RwFrame* f = NodeOf(m_pCarriedObject)->m_pRwFrame;
        m.m_pos.x = f->modelling.pos.x;
        m.m_pos.y = f->modelling.pos.y;
        m.m_pos.z = f->modelling.pos.z;
        m.m_ui32Flags &= 0xfffdffffu;
        NodeOf(m_pCarriedObject)->SetLocalMatrix(reinterpret_cast<const RwMatrix*>(&m));  // 0x000d0be8
        if (t != 1.0f) return;
    }
    AttachCarriedNode();
}

// 0x004b26c0 CKS08CarrierHero_CarryState_maybe (state 0). Enter: a carrier that has to place at once (+0x90) hands the
// hero back (object anim, external position and attached movement off, +0x20 cleared); otherwise the pickup animation
// (the animation dictionary's first word) crossfades in (0.1 s, hero vt+0xc4) and +0x20 is set (no word: cleared).
// Leave: +0x90 and the carried object cleared. Tick, nothing carried: state 1. While the pickup animation runs (+0x20) it
// advances by the frame with the hero marked carrying and the pickup sound at the hero; at its end the hero is detached
// and the carried object's start pose kept (or attached at once). After it: the hero detached if still attached, the
// object lerped to the hot spot, a CKHkPressionStone (0x542) of the meca group's active actors within 3 (d^2 < 9) of the
// object found (a free one: +0x98 = the carrier); then, unless the hero keeps the object (+0x354 bit 30), a controlled
// hero without the input blocked, attached movement or a 0x2e02 HUD target that presses action 3 (no receiver near) or
// 4, 8 or 9 lets go: onto a free stone at its grounded point raised by 0.4 (vt+0xf8 with no velocity, the node placed
// there, vt+0x144(1)), else thrown with the hero's velocity (vt+0xf8). Let go: state 1.
uint8_t CKS08CarrierHero::CarryState(IKTime* clock, int32_t phase, uint8_t other) {
    CKHkS08Hero* hero = static_cast<CKHkS08Hero*>(m_pHero);
    if (phase == 1) {
        if (m_bUnk90 != 0) {
            hero->SetObjectControlsAnim(0);                              // 0x00362010
            hero->SetExternallyPositionedAndPhysics(0, nullptr, nullptr);  // 0x0032a638
            hero->SetAttachedMovementEnabled(0);                         // 0x00362050
            m_unk20 = 0;
            return other;
        }
        CAnimationDictionary* dico = static_cast<CAnimationDictionary*>(m_pAnimDico);
        if (dico == nullptr) return other;
        const uint32_t word = static_cast<uint32_t>(dico->m_apAnimations[0]);
        // 0x4b2a30 lwz + cmpwi 0: the original tests the resolved entry (null = absent); dotd keeps the word (-1 =
        // absent), so the test is the animation lookup (port-final F06's note, 2026-11-16).
        if (CAnimationManager_GetAnimation(word) == nullptr) {
            m_unk20 = 0;
            return other;
        }
        hero->CrossfadeAnimResource(0.1f, 0.0f, word, 1);  // vt+0xc4 0x0032ac88; TOC +0x6458 / +0x6408
        m_unk20 = static_cast<uint8_t>(phase);
        return other;
    }
    if (phase == 2) {
        m_bUnk90 = 0;
        m_pCarriedObject = nullptr;
        return other;
    }
    if (phase != 0) return other;
    if (m_pCarriedObject == nullptr) return 1;
    if (m_unk20 != 0) {
        const float dt = clock->m_afDeltaTime[0];
        if (hero->WillAnimEndWithin(dt) == 0) {  // 0x00364020
            hero->AdvanceObjectAnimTime(clock->m_afDeltaTime[0]);  // 0x00363410
            hero->SetCarryingObject(1);  // 0x0032a438
            CKSoundDictionaryID* sounds = static_cast<CKSoundDictionaryID*>(m_pSoundDico);
            if (sounds->GetSound(0) == nullptr) return other;  // 0x00112bc0
            const RwV3d& at = LtmPos(hero);
            const CVector3 position = {at.x, at.y, at.z};
            sounds->GetSound(0)->SetPosition(&position);  // 0x00110fa0
            sounds->GetSound(0)->Play(0.0f);              // 0x00111230; TOC +0x6408
            return other;
        }
        m_unk20 = 0;  // stb of the phase (0)
        hero->DetachFromObject();  // 0x00364608
        CaptureOrAttachCarried();
        return other;
    }
    if (hero->GetAttachedObject() == this) hero->DetachFromObject();  // 0x00361d50 / 0x00364608
    if (m_bUnk90 == 0 && m_fCarryTime < m_unk40) LerpCarriedObjectToHotSpot(clock);  // blt
    CDefaultGameManager* manager = g_pEngine->m_gameManager;
    CKGrpMeca* meca = static_cast<CKGrpMeca*>(manager->m_unk04[2]);  // +0x0c
    CKHkPressionStone* stone = nullptr;
    if (meca != nullptr && meca->m_unk30 != 0) {
        const uint32_t count = meca->m_unk30;
        for (uint32_t i = 0; i != count; ++i) {
            IKHook* hook = meca->m_pUnk2c[i];
            if (hook->IsKindOfClass(0x542) == 0) continue;  // vt+0x08
            const RwV3d& h = LtmPos(hook);
            const RwV3d& c = LtmPos(m_pCarriedObject);
            const float dy = h.y - c.y;
            const float dx = h.x - c.x;
            const float dz = h.z - c.z;
            if (!(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)) < 9.0f)) continue;  // TOC +0x645c; blt
            stone = static_cast<CKHkPressionStone*>(hook);
            if (stone->m_unk38 == 0 && stone->m_pObject == nullptr && (stone->m_bitArray & 0x20000u) == 0 &&
                (stone->m_bitArray >> 30) == 0) {
                stone->m_unk98 = this;
            }
            break;
        }
    }
    CKS08GameManager* gm = static_cast<CKS08GameManager*>(manager);
    uint8_t busy = hero->IsAttachedMovementEnabled();  // 0x003626e8
    if (busy == 0 && hero->IsPlayerControlled() != 0) {
        IKSerializable* target = gm->PlayerHudSlots()[PlayerIndexIfControlled(hero)].m_pHero;  // +0x2c8, 8-byte entries
        if (target != nullptr && target->IsKindOfClass(0x2e02) != 0) busy = 1;
    }
    if (hero->GetFlag354Bit30() == 0) {  // 0x00361de8
        if (hero->IsPlayerControlled() == 0) return other;
        if (gm->IsInputBlocked() != 0) return other;  // vt+0x1ec
        if (busy != 0) return other;
        if (gm->IsActionPressed(3, PlayerIndexIfControlled(hero)) == 0 || m_bNearbyReceiver != 0) {  // vt+0x160
            if (gm->IsActionPressed(4, PlayerIndexIfControlled(hero)) == 0 &&
                gm->IsActionPressed(8, PlayerIndexIfControlled(hero)) == 0 &&
                gm->IsActionPressed(9, PlayerIndexIfControlled(hero)) == 0) {
                return other;
            }
        }
    }
    CKHkS08TransportableBase* carried = static_cast<CKHkS08TransportableBase*>(m_pCarriedObject);
    if (stone == nullptr || stone->m_unk38 != 0 || stone->m_pObject != nullptr || (stone->m_bitArray & 0x20000u) != 0 ||
        (stone->m_bitArray >> 30) != 0) {
        const CVector3 velocity = hero->GetDerivedVelocity();  // 0x0032a730
        if (carried->VfF8(this, &velocity) == 0) return other;  // vt+0xf8
        return 1;
    }
    if (carried->VfF8(this, &kZero) == 0) return other;  // TOC +0x6460: 0x00c50d64
    const CVector3 point = CarryTarget_GetGroundedPlacementPoint(stone);  // 0x00426be8
    const float x = point.x;
    const float z = point.z;
    const float y = point.y + 0.4f;  // TOC +0x6464
    if (kNoPoint.x == x && kNoPoint.y == y && kNoPoint.z == z) return 1;  // TOC +0x6468: 0x00c50da0
    CSGLeaf* node = NodeOf(carried);
    node->SetIdentity();  // 0x000d08f0
    SetNodePosition(NodeOf(carried), x, y, z);
    NodeOf(carried)->ForceWorldMatrixUpdate();  // vt+0x50
    carried->SetFlag2C(1);                      // vt+0x144
    return 1;
}

// 0x004b3958 CKS08CarrierHero_MessageProc. 0x93f (the hero uses the pickup, CKHkS08Hero_TryUseInteractable_maybe): the
// pickup (+0x14) takes the carrier (vt+0xf0); then it is carried and the machine switches to state 0 (no clock). 0x940
// (the hero lets go of the carrier it is attached to): in state 0 with something carried and the hero attached to the
// carrier, a running pickup animation ends (+0x20 cleared, the hero detached, the start pose kept or the object attached)
// or, after it, the hero is detached and the object dropped (vt+0xf8, no velocity). Both answer 0, other messages 1.
int32_t CKS08CarrierHero::MessageProc(uint16_t message, void* /*data*/) {
    if (message == 0x93f) {
        CKHkS08TransportableBase* pickup = static_cast<CKHkS08TransportableBase*>(m_unk14);
        if (pickup->VfF0(this) == 0) return 0;  // vt+0xf0
        m_pCarriedObject = m_unk14;
        const uint8_t old = m_unka8;
        if (old != 0xff) CallState(&m_pStateTable[old * 2u], nullptr, 2, 0);
        m_unka8 = 0;
        CallState(&m_pStateTable[0], nullptr, 1, old);
        return 0;
    }
    if (message != 0x940) return 1;
    if (m_pCarriedObject == nullptr || m_unka8 != 0) return 0;
    CKHkS08Hero* hero = static_cast<CKHkS08Hero*>(m_pHero);
    if (hero->GetAttachedObject() != this) return 0;  // 0x00361d50
    if (m_unk20 == 0) {
        hero->DetachFromObject();  // 0x00364608
        static_cast<CKHkS08TransportableBase*>(m_pCarriedObject)->VfF8(this, &kZero);  // vt+0xf8; TOC +0x6460
        return 0;
    }
    m_unk20 = 0;  // stb of the state (0)
    hero->DetachFromObject();
    CaptureOrAttachCarried();
    return 0;
}

// 0x004b1370 CKS08CarrierHero_vf5C: may `object` be let go. The carried object's grip (vt+0x118) is read and its world
// position taken (unused), then the walls (RaycastWalls 0.3 high, no cull or masks, gathered; the original's unused r5
// argument, the carried node, is not part of the port's signature) between the object's and the hero's LTM positions: no
// wall, or a receiver near, and `object` the one carried: 1.
uint8_t CKS08CarrierHero::Vf5C(IKSerializable* object) {
    CSGHotSpot* grip = static_cast<CKHkS08TransportableBase*>(m_pCarriedObject)->Vf118();  // vt+0x118
    CVector3 unused;
    grip->GetWorldPosition(&unused);  // 0x000ce790
    const RwV3d& from = LtmPos(m_pCarriedObject);
    const RwV3d& to = LtmPos(m_pHero);
    CLine line;
    line.m_start = {from.x, from.y, from.z};
    line.m_VectDir.x = to.x - from.x;
    line.m_VectDir.y = to.y - from.y;
    line.m_VectDir.z = to.z - from.z;
    CGroundEdgeDatasOut out;
    const uint8_t hit = static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision)
                            ->RaycastWalls(&line, 0.3f, &out, 0, nullptr, 1);  // 0x00198438; TOC +0x640c
    if (hit != 0 && m_bNearbyReceiver == 0) return 0;
    if (m_pCarriedObject != object) return 0;
    // srawi / xor / subf / rlwinm of the pointer: bit 31 of (s - (s ^ p)), s = p >> 31, is 1 for every non-null p.
    return object != nullptr ? 1 : 0;
}

// 0x004b1bc8 CKS08CarrierHero_IsInGrabRangeAndAngle_maybe: `object` (its node's LTM position) is nearer to `pos` than the
// grab range (+0x30; fcmpu / ble: NaN refuses) and lies within the grab angle (+0x34, the inlined cosine) of `dir`: the
// cosine below the dot of `dir` with the normalised direction to the object. No caller in the original besides its OPD.
uint8_t CKS08CarrierHero::IsInGrabRangeAndAngle(const CVector3* pos, const CVector3* dir, IKSerializable* object) const {
    const RwV3d& p = LtmPos(object);
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
    if (!(m_unk30 > distance)) return 0;
    const float limit = CosOfAngle(m_unk34);
    const float dot = -ppc::fmadds(dz, dir->z, ppc::fmadds(dir->x, dx, dir->y * dy));  // fnmadds
    return limit < dot ? 1 : 0;
}
