// CKHkS08CristalReceiver.cpp - reconstructed original translation unit 0x483210-0x486570 (GAME_TOC1, main_toc1), 38 functions, 34 live.
// Primary class: CKHkS08CristalReceiver  key 0x2c02  category Hook  size 0x94  vtable 0xb27cf8
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x483210  CKHkS08CristalReceiver_Delete
//   [x] 0x483260  CKHkS08CristalReceiver_Restart  (CKHkS08CristalReceiver.h)
//   [x] 0x483270  CKHkS08CristalReceiver_SetGlowLevel_maybe  (SetGlowLevel; port-final F06)
//   [ ] 0x483490  CKHkS08CristalReceiver_ReleaseFxAt50_maybe  [dead]
//   [ ] 0x4834f8  CKHkS08CristalReceiver_ReleaseFxAt40_maybe  [dead]
//   [x] 0x483560  CKHkS08CristalReceiver_Resume  (inherited: CKHkActorBase's)
//   [x] 0x483588  CKHkS08CristalReceiver_Pause  (inherited: CKHkActorBase's)
//   [x] 0x4835b0  CKHkS08CristalReceiver_Stop  (inherited: CKHkActorBase's)
//   [x] 0x4835d8  CKHkS08CristalReceiver_Start  (Start, vt+0x50; port-final F06)
//   [x] 0x483688  CKHkS08CristalReceiver_GetInfo
//   [x] 0x483768  CKHkS08CristalReceiver_PostLoad  (CKHkS08CristalReceiver.h)
//   [ ] 0x4837c8  CKHkS08CristalReceiver_Save
//   [x] 0x4837f0  CKHkS08CristalReceiver_RecursiveRegistration  (inherited: CKHkActorBase's)
//   [x] 0x483818  CKHkS08CristalReceiver_Destroy  (inherited: CKHkActorBase's)
//   [ ] 0x483840  CKHkS08CristalReceiver_BaseDestructor  [dead: no pointer to its descriptor 0xbc2ad0, no call]
//   [x] 0x483870  CKHkS08CristalReceiver_Construct  [dead]
//   [ ] 0x4838c8  CKHkS08CristalReceiver_Construct_2  [dead]
//   [x] 0x483920  CKHkS08CristalReceiver_DeleteArray
//   [ ] 0x4839c0  RegisterCKHkS08CristalReceiverClass
//   [ ] 0x483a48  _GLOBAL__D_483a48
//   [ ] 0x483a58  _GLOBAL__I_483a58
//   [x] 0x483a68  CKHkS08CristalReceiver_DeletingDestructor  (the destructor (CKHkActorBase's only))
//   [x] 0x483ab0  CKHkS08CristalReceiver_Destructor  (the destructor (CKHkActorBase's only))
//   [x] 0x483ae0  CKHkS08CristalReceiver_GetTriggerProp96
//   [ ] 0x483af8  CKHkS08CristalReceiver_UpdateSoundPositions_maybe  [dead: no pointer to its descriptor 0xbc2b78, no call]
//   [x] 0x483b88  CKHkS08CristalReceiver_AddHotspotPointsToFx_maybe  (AddHotspotPointsToFx; port-final F06)
//   [x] 0x483cd0  CKHkS08CristalReceiver_CreateArray
//   [x] 0x483da0  CKHkS08CristalReceiver_Create
//   [x] 0x483e08  CKHkS08CristalReceiver_OnDeactivate  (VfA4; port-final F06)
//   [x] 0x483ef8  CKHkS08CristalReceiver_Update  (Update, vt+0x7c; port-final F06)
//   [x] 0x484318  CKHkS08CristalReceiver_OnActivate_maybe  (VfA0; port-final F06)
//   [x] 0x4844c8  CKHkS08CristalReceiver_MessageProc  (MessageProc, vt+0x1c; port-final F06)
//   [x] 0x4846c8  CKHkS08CristalReceiver_Load
//   [x] 0x484e60  CKHkS08CristalReceiver_TriggerReceiveFx_maybe  (TriggerReceiveFx; port-final F06)
//   [x] 0x485168  CKHkS08CristalReceiver_State0_AwaitOrb_maybe  (State0, the table +0x84; port-final F06)
//   [ ] 0x485a58  CKHkS08CristalReceiver_ShowInputIcon_maybe  [dead: no pointer to its descriptor 0xbc2cd8, no call]
//   [ ] 0x485d38  CKHkS08CristalReceiver_StartParticleFxAtHotspot_maybe  [dead: no pointer to its descriptor 0xbc2ce0, no call]
//   [x] 0x486010  CKHkS08CristalReceiver_State1_maybe  (State1, the table +0x84; port-final F06)
//
//   [ ] 0x9c4868  CKHkS08CristalReceiver_IsKindOfClass  [inline]
//   [ ] 0x9c48c0  CKHkS08CristalReceiver_GetClassType  [inline]
//   [ ] 0x9c48c8  CKHkS08CristalReceiver_GetClassID  [inline]
#include "Spyro2008/hooks/CKHkS08CristalReceiver.h"
#include "k2000/core/IKInfo.h"

#include "k2000/io/IKFile.h"

// 0x004846c8 CKHkS08CristalReceiver_Load: the actor base, then the level data (type 0 only). The trigger
// starters are loaded with type 0.
int32_t CKHkS08CristalReceiver::Load(IKFile* file, int32_t type) {
    CKHkActorBase::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        IKFile_ReadRef(file, &m_pUnk20);
        ReadF32LE(file, &m_fUnk64);
        ReadF32LE(file, &m_fUnk30);
        IKFile_ReadRef(file, &m_pUnk24);
        IKFile_ReadRef(file, &m_pUnk34);
        IKFile_ReadRef(file, &m_pUnk2C);
        IKFile_ReadRef(file, &m_pUnk38);
        IKFile_ReadRef(file, &m_pUnk58);
        IKFile_ReadRef(file, &m_pUnk48);
        IKFile_ReadRef(file, &m_pUnk28);
        m_unk68.Load(file, K_LEVEL_PLATEFORMS);
        IKFile_ReadRef(file, &m_pUnk4C);
        IKFile_ReadRef(file, &m_pUnk5C);
        IKFile_ReadRef(file, &m_pUnk60);
        IKFile_ReadRef(file, &m_pUnk54);
        IKFile_ReadRef(file, &m_pUnk3C);
        ReadF32LE(file, &m_fUnk78);
    }
    return 1;
}

// 0x00483688 CKHkS08CristalReceiver_GetInfo, with its accessor 0x00483ae0 GetTriggerProp96.
int32_t CKHkS08CristalReceiver::GetInfo(IKInfo* info, int32_t request) {
    if (request != kGetInfoValueAccessor || info->m_ui32Id != 0x96) return 1;
    return AnswerInfo(info, [](IKSerializable* o, uint32_t) {
        return static_cast<uint32_t>(static_cast<CKHkS08CristalReceiver*>(o)->GetTriggerProp96());
    }, 0);
}

// ==== port-final F06 ==================================================================================================
#include "Renderware/rpprtstd/RpPrtStd.h"
#include "Renderware/rwcore/RwCamera.h"
#include "Spyro2008/hooks/CKHkS08CristalEmitter.h"
#include "Spyro2008/hooks/CKHkS08CristalKey.h"
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "Spyro2008/logic/CKS08CarrierEnemy.h"
#include "Spyro2008/logic/CKS08CarrierHero.h"
#include "Spyro2008/logic/CKS08GameManager.h"
#include "Spyro2008/misc/CKHkS08TransportableBase.h"
#include "crt/ppc_ops.h"
#include "k2000/core/Ps3MemberFn.h"
#include "k2000/fx/IKFx.h"
#include "k2000/groups/CKGrpTransportableObject.h"
#include "k2000/logic/CKLevel.h"
#include "k2000/logic/CKSector.h"
#include "k2000/logic/CKTransformElement.h"
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/logic/IKFxData.h"
#include "k2000/logic/fx/CKExplosionNodeFx.h"
#include "k2000/logic/fx/CKInputIconNodeFx.h"
#include "k2000/logic/fx/CKParticlesEffectNodeFx.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/CParticlesNodeFx.h"
#include "k2000/scenegraph/CSGBranch.h"
#include "k2000/scenegraph/CSGLeaf.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/scenegraph/CSGSectorRoot.h"
#include "k2000/services/CKSrvFx.h"
#include "k2000/system/IKTime.h"

namespace {
// The table Start builds (+0x84): the descriptors' native handlers.
Ps3MemberFnEntry<CKHkS08CristalReceiver::StateFn> g_receiverStates[] = {
    {0x00bc2cd0u, &CKHkS08CristalReceiver::State0, "CKHkS08CristalReceiver_State0_AwaitOrb_maybe 0x485168", false},
    {0x00bc2d08u, &CKHkS08CristalReceiver::State1, "CKHkS08CristalReceiver_State1_maybe 0x486010", false},
};

// 0x00c50d64: the zero vector (TOC1 +0x5d24), the velocity State0 gives the object it hands over.
const CVector3 kReceiverZero = {0.0f, 0.0f, 0.0f};

CKSrvFx* ReceiverSrvFx() { return static_cast<CKSrvFx*>(g_pEngine->m_srvFx); }  // engine +0x60
CSGLeaf* HookNode(IKSerializable* hook) { return static_cast<CSGLeaf*>(static_cast<IKHook*>(hook)->m_pKGLObject); }
RwFrame* NodeFrame(IKSerializable* node) { return static_cast<CSGMovable*>(node)->m_pRwFrame; }  // node +0x04
CKHkS08TransportableBase* Transportable(IKSerializable* object) { return static_cast<CKHkS08TransportableBase*>(object); }

// The effect of `slot` stopped and released for `owner` (vt+0x58), the slot cleared.
void ReleaseSlot(IKSerializable** slot, const IKSerializable* owner) {
    if (*slot == nullptr) return;
    static_cast<IKFx*>(*slot)->StopAndRelease(owner);  // vt+0x58
    *slot = nullptr;
}

// A carrier's vt+0x64 (KBase910C's classes: CKS08CarrierHero 0x9c54b0 its hero, CKS08CarrierEnemy 0x4c78b0 its enemy).
IKSerializable* CarrierOwner(IKSerializable* carrier) {
    if (carrier->GetClassID() == 0x256) return static_cast<CKS08CarrierEnemy*>(carrier)->Vf64();
    return static_cast<CKS08CarrierHero*>(carrier)->Vf64();
}

// 0x00362ac8 CKHkS08Hero_GetPlayerIndexIfControlled_maybe: the player (+0x26) of a hero it controls, else 0xff.
uint8_t ReceiverPlayerIndex(const CKHkS08Hero* hero) {
    return hero->m_ui8Hero == hero->m_ui8TrackedLeader ? hero->m_ui8Leader : 0xff;
}

// The key's object hung where the receiver holds it: off its parent (vt+0x78, the parent not tested, as the original);
// under the root of the object's sector at the receiver's modelling position, or on the hot spot.
void HangObject(CKHkS08CristalReceiver* receiver, IKSerializable* object) {
    CSGLeaf* node = HookNode(object);
    node->m_pParent->RemoveChild(node);  // vt+0x78
    if (receiver->m_pUnk34 == nullptr) {
        const uint32_t index = static_cast<IKLife*>(object)->m_iSectorIndex;  // the object's sector (+0x10)
        CKSector* sector = static_cast<CKSector*>(g_pEngine->m_level->m_vpSectors.m_pBlock[index]);  // engine +0x90, +0x04
        sector->m_pSectorRoot->AddChild(node);  // vt+0x70
        RwFrame* frame = NodeFrame(node);
        const RwV3d& at = NodeFrame(receiver->m_pKGLObject)->modelling.pos;  // frame +0x40
        frame->modelling.pos.z = at.z;
        frame->modelling.pos.x = at.x;
        frame->modelling.pos.y = at.y;
        frame->modelling.flags &= 0xfffdffffu;  // no longer the identity (bit 17)
        RwFrame_MarkDirty(NodeFrame(node));     // 0x00010698
    } else {
        static_cast<CSGHotSpot*>(receiver->m_pUnk34)->AttachVolume(node);  // 0x000ce2b8
    }
}
}  // namespace

uint8_t CKHkS08CristalReceiver::CallState(const uint32_t pair[2], IKTime* clock, int32_t phase, uint8_t other) {
    StateFn fn = ResolvePs3MemberFn(g_receiverStates, pair, "CKHkS08CristalReceiver state handler");
    if (fn == nullptr) return other;
    return (this->*fn)(clock, phase, other);
}

void CKHkS08CristalReceiver::SwitchState(uint8_t next, IKTime* clock, uint8_t leaveOther) {
    const uint8_t old = m_unk80;
    if (old != 0xff) CallState(&m_pStateTable[old * 2u], clock, 2, leaveOther);
    m_unk80 = next;
    if (next != 0xff) CallState(&m_pStateTable[next * 2u], clock, 1, old);
}

// 0x004835d8 CKHkS08CristalReceiver_Start (vt+0x50)
void CKHkS08CristalReceiver::Start() {
    CKHkActorBase::Start();  // 0x003f6e48
    m_aStateTable[2] = 0x00bc2d08u;  // State1_maybe 0x486010 (TOC1 +0x5cc4)
    m_aStateTable[3] = 0;
    m_aStateTable[1] = 0;
    m_aStateTable[0] = 0x00bc2cd0u;  // State0_AwaitOrb_maybe 0x485168 (TOC1 +0x5cc0)
    m_unk81 = 2;
    m_pStateTable = m_aStateTable;
    m_unk80 = 0xff;
    if (m_pUnk20 != nullptr) static_cast<CKHkActorBase*>(m_pUnk20)->SetEnabled(0);  // vt+0xcc
}

// 0x00483270 CKHkS08CristalReceiver_SetGlowLevel_maybe
void CKHkS08CristalReceiver::SetGlowLevel(float level) {
    CSGLeaf* node = static_cast<CSGLeaf*>(m_pUnk58);
    if (node == nullptr) return;
    const float kMax = 254.0f;  // TOC1 +0x5cac
    float alpha;
    if (level <= 0.0f) {  // TOC1 +0x5cb0, cror lt|eq
        alpha = 0.0f;
        node->m_sgProperties = (node->m_sgProperties & 0xfffffffbu) | 4u;
    } else if (level >= 1.0f) {  // TOC1 +0x5ca8, cror gt|eq
        alpha = kMax;
        node->m_sgProperties &= 0xfffffffbu;
    } else {
        alpha = level * kMax;
        node->m_sgProperties &= 0xfffffffbu;
        if (!(alpha <= kMax)) alpha = kMax;  // ble (NaN takes the clamp)
    }
    // The geometry walk of node +0x1c (stfiwx, lbz +3: the low byte of fctiwz).
    TransformFx::SetGeometriesAlpha(m_pUnk58, static_cast<uint8_t>(ppc::fctiwz(alpha)));
}

// 0x00483b88 CKHkS08CristalReceiver_AddHotspotPointsToFx_maybe
void CKHkS08CristalReceiver::AddHotspotPointsToFx() {
    CVector3 position;
    IKSerializable* const hotSpots[2] = {m_pUnk5C, m_pUnk60};
    for (IKSerializable* hotSpot : hotSpots) {
        if (hotSpot == nullptr) continue;
        static_cast<CSGHotSpot*>(hotSpot)->GetWorldPosition(&position);  // 0x000ce790
        CParticlesNodeFx* particles = static_cast<CParticlesNodeFx*>(m_pUnk4C);
        if (particles->m_ui8NbActivePoints < 0x40) {
            RwV3d& point = particles->m_pAdvEmtPointList->pointList[particles->m_ui8NbActivePoints];
            point.z = position.z;
            point.x = position.x;
            point.y = position.y;
            particles->m_sgProperties = (particles->m_sgProperties & 0xffffdfffu) | 0x2000u;
            particles->m_ui8NbActivePoints = static_cast<uint8_t>(particles->m_ui8NbActivePoints + 1);
        }
    }
}

// 0x00483e08 CKHkS08CristalReceiver_OnDeactivate (vt+0xa4)
void CKHkS08CristalReceiver::VfA4() {
    CKHkActorBase::VfA4();  // 0x003f7370
    CParticlesNodeFx* particles = static_cast<CParticlesNodeFx*>(m_pUnk4C);
    particles->m_sgProperties &= 0xfff7fbffu;               // not emitting (0x400), 0x80000 off
    particles->m_pRpPrtStdEmitter->flag &= 0xfffffff7u;     // the emit flag (0x8) off
    ReleaseSlot(&m_unk50, this);
    ReleaseSlot(&m_unk40[0], this);
}

// 0x00483ef8 CKHkS08CristalReceiver_Update (vt+0x7c)
void CKHkS08CristalReceiver::Update(IKTime* clock) {
    CKHkActorBase::Update(clock);  // 0x003f6e68 (empty)
    if (m_unk80 == 0xff) {
        if (m_pUnk28 == nullptr) {
            CKHkS08CristalKey* key = static_cast<CKHkS08CristalKey*>(m_pUnk24);
            key->m_pUnk20 = nullptr;
            static_cast<CKHkS08CristalEmitter*>(key->m_pUnk24)->m_pUnk28 = key->m_pUnk20;
        } else {
            // 0x004a7ba8 (Ghidra CKGrpTransportableObject_TakePooledObjectOfType_maybe), class id 0xc2.
            static_cast<CKHkS08CristalKey*>(m_pUnk24)->m_pUnk20 =
                static_cast<CKGrpTransportableObject*>(m_pUnk28)->ActivateObjectOfType(0xc2);
            if (static_cast<CKHkS08CristalKey*>(m_pUnk24)->m_pUnk20 != nullptr) {
                Transportable(static_cast<CKHkS08CristalKey*>(m_pUnk24)->m_pUnk20)->Vf108();   // vt+0x108
                Transportable(static_cast<CKHkS08CristalKey*>(m_pUnk24)->m_pUnk20)->Vf128(1);  // vt+0x128
                static_cast<CKHkS08CristalKey*>(m_pUnk24)->m_unk39[0] = 0;
                SwitchState(1, nullptr, 1);
                static_cast<CKHkS08CristalKey*>(m_pUnk24)->m_unk39[0] = 1;
            }
            CKHkS08CristalKey* key = static_cast<CKHkS08CristalKey*>(m_pUnk24);
            static_cast<CKHkS08CristalEmitter*>(key->m_pUnk24)->m_pUnk28 = key->m_pUnk20;
        }
    }
    const uint8_t state = m_unk80;
    if (state != 0xff) {
        const uint8_t next = CallState(&m_pStateTable[state * 2u], clock, 0, state);
        if (next != m_unk80) SwitchState(next, clock, next);
    }
    SetGlowLevel(m_unk70[0]);
}

// 0x00484318 CKHkS08CristalReceiver_OnActivate_maybe (vt+0xa0; the actor base's is not called)
void CKHkS08CristalReceiver::VfA0() {
    if (m_pUnk58 != nullptr) {
        CSGLeaf* glow = static_cast<CSGLeaf*>(m_pUnk58);
        glow->m_sgProperties = (glow->m_sgProperties & 0xfffffffbu) | 4u;  // hidden
    }
    SwitchState(0, nullptr, 0);
    CParticlesNodeFx* particles = static_cast<CParticlesNodeFx*>(m_pUnk4C);
    particles->m_sgProperties = (particles->m_sgProperties & 0xfff7fbffu) | 0x400u;  // emitting, 0x80000 off
    particles->m_fEmissionSpeedAdjustment = 0.0f;                                     // stw 0
    particles->m_pRpPrtStdEmitter->flag |= 0xau;                                      // active and emitting
    m_unk70[0] = 0.0f;                                                                // stw 0
}

// 0x004844c8 CKHkS08CristalReceiver_MessageProc (vt+0x1c)
int32_t CKHkS08CristalReceiver::MessageProc(uint16_t message, void* data) {
    const int32_t base = CKHkActorBase::MessageProc(message, data);  // 0x003f7148
    int32_t own = 1;
    if (message == 0x900) {
        SwitchState(1, nullptr, 1);
        own = 0;
    }
    if (base == 3 || own == 3) return 3;
    if (base == 2 || own == 2) return 2;
    if (base == 0) return 0;
    return own;
}

// 0x00484e60 CKHkS08CristalReceiver_TriggerReceiveFx_maybe
void CKHkS08CristalReceiver::TriggerReceiveFx() {
    m_unk40[1] = ReceiverSrvFx()->AcquireFx(static_cast<IKFxData*>(m_pUnk48), this);
    if (m_unk40[1] == nullptr) return;
    CVector3 position;
    if (m_pUnk34 == nullptr) {
        const RwV3d& p = NodeFrame(m_pKGLObject)->modelling.pos;  // frame +0x40
        position = {p.x, p.y, p.z};
    } else {
        static_cast<CSGHotSpot*>(m_pUnk34)->GetWorldPosition(&position);  // 0x000ce790
    }
    static_cast<CKExplosionNodeFx*>(m_unk40[1])->SetTranslation(&position, this);  // 0x001b66e8
    static_cast<CKExplosionNodeFx*>(m_unk40[1])->Trigger(this, nullptr);           // 0x001b82a8 (r5 = r6 = 0)
    static_cast<IKFx*>(m_unk40[1])->StopAndRelease(this);                         // vt+0x58 (the slot kept)
}

// 0x00485168 CKHkS08CristalReceiver_State0_AwaitOrb_maybe (descriptor 0x00bc2cd0)
uint8_t CKHkS08CristalReceiver::State0(IKTime* /*clock*/, int32_t phase, uint8_t other) {
    if (phase != 0) return other;
    IKSerializable* object = static_cast<CKHkS08CristalKey*>(m_pUnk24)->m_pUnk20;
    if (object == nullptr) return other;
    if (Transportable(object)->Vf114() == nullptr) {  // vt+0x114: not carried
        ReleaseSlot(&m_unk40[0], this);
        return other;
    }
    if (CarrierOwner(Transportable(object)->Vf114())->GetClassID() != 0x97) {  // vt+0x64, vt+0x18: carried by a hero
        ReleaseSlot(&m_unk40[0], this);
        return other;
    }
    CKHkS08Hero* hero = static_cast<CKHkS08Hero*>(CarrierOwner(Transportable(object)->Vf114()));
    IKSerializable* carrierOwner = CarrierOwner(Transportable(object)->Vf114());
    const float glowRadius2 = m_fUnk64 * m_fUnk64;
    const RwV3d& own = FrameLtm(NodeFrame(m_pKGLObject))->pos;  // frame +0x80
    const RwV3d& at = FrameLtm(NodeFrame(static_cast<IKHook*>(carrierOwner)->m_pKGLObject))->pos;
    const float dy = at.y - own.y;
    const float dx = at.x - own.x;
    const float dz = at.z - own.z;
    const float d2 = ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy));
    if (!(d2 < glowRadius2)) {  // bge: a NaN gives no glow
        m_unk70[0] = 0.0f;
    } else {
        m_unk70[0] = (1.0f - d2 / glowRadius2) * 0.15f;  // TOC1 +0x5ca8, +0x5d2c (0x3e19999a)
    }
    if (!(m_fUnk30 * m_fUnk30 > d2)) {  // bgt
        ReleaseSlot(&m_unk40[0], this);
        return other;
    }
    if (Transportable(object)->Vf114()->GetClassID() == 0x247) {
        if (static_cast<CKS08CarrierHero*>(Transportable(object)->Vf114())->HasNearbyReceiver() == 0) {  // 0x004b0a38
            static_cast<CKS08CarrierHero*>(Transportable(object)->Vf114())->SetNearbyReceiver(1, this);  // 0x004b0a00
        }
    }
    if (m_unk40[0] == nullptr) {
        m_unk40[0] = ReceiverSrvFx()->AcquireFx(static_cast<IKFxData*>(m_pUnk3C), this);
        if (m_unk40[0] != nullptr) {
            CVector3 position;
            if (m_pUnk34 == nullptr) {
                const RwV3d& p = FrameLtm(NodeFrame(m_pKGLObject))->pos;
                position = {p.x, p.y, p.z};
            } else {
                static_cast<CSGHotSpot*>(m_pUnk34)->GetWorldPosition(&position);  // 0x000ce790
            }
            const CVector3 iconAt = position;
            static_cast<CKInputIconNodeFx*>(m_unk40[0])->SetPosition(&iconAt);  // 0x001c45c8
        }
    }
    CKS08GameManager* manager = static_cast<CKS08GameManager*>(g_pEngine->m_gameManager);  // engine +0x8c
    if (hero->IsPlayerControlled() != 0) {  // 0x00362af0
        // vt+0x160: the action's byte as a float (fcfid), against 0.0 (TOC1 +0x5cb0; ble).
        const uint8_t pressed = manager->IsActionPressed(3, ReceiverPlayerIndex(hero));
        if (!(static_cast<float>(pressed) <= 0.0f)) {
            if (Transportable(object)->VfF8(Transportable(object)->Vf114(), &kReceiverZero) != 0) {  // vt+0xf8
                Transportable(object)->Vf108();             // vt+0x108
                Transportable(object)->Vf128(1);            // vt+0x128
                Transportable(object)->ResetStateMachine(); // vt+0x11c
                hero->MessageProc(0x94d, nullptr);          // vt+0x1c
                TriggerReceiveFx();
                ReleaseSlot(&m_unk40[0], this);
                m_unk70[0] = 1.0f;  // TOC1 +0x5ca8
                return 1;
            }
        }
    }
    if (Transportable(object)->Vf114()->GetClassID() == 0x247) {
        static_cast<CKS08CarrierHero*>(Transportable(object)->Vf114())->SetNearbyReceiver(0, this);  // 0x004b0a00
    }
    return other;
}

// 0x00486010 CKHkS08CristalReceiver_State1_maybe (descriptor 0x00bc2d08)
uint8_t CKHkS08CristalReceiver::State1(IKTime* clock, int32_t phase, uint8_t other) {
    if (phase == 1) {
        IKSerializable* object = static_cast<CKHkS08CristalKey*>(m_pUnk24)->m_pUnk20;
        if (object == nullptr) return 0xff;
        if (static_cast<CKHkS08CristalKey*>(m_pUnk24)->m_unk39[0] != 0) QueueTriggerSignals(&m_unk68);  // 0x00236338
        HangObject(this, object);
        Transportable(object)->Vf128(1);  // vt+0x128
        if (m_pUnk20 != nullptr) static_cast<CKHkActorBase*>(m_pUnk20)->SetEnabled(1);  // vt+0xcc
        return other;
    }
    if (phase == 2) {
        if (m_pUnk20 != nullptr) static_cast<CKHkActorBase*>(m_pUnk20)->SetEnabled(0);
        ReleaseSlot(&m_unk50, this);
        return other;
    }
    if (phase != 0) return other;
    if (static_cast<CKHkS08CristalKey*>(m_pUnk24)->m_pUnk20 == nullptr) return 0xff;
    // The glow fades over +0x78 (0.0 TOC1 +0x5cb0, -1.0 +0x5cd4); a NaN or negative level ends at 0.
    if (m_fUnk78 == 0.0f) {
        m_unk70[0] = 0.0f;
    } else {
        const float level = ppc::fmadds(-1.0f / m_fUnk78, clock->m_afDeltaTime[0], m_unk70[0]);
        m_unk70[0] = level;
        if (!(level >= 0.0f)) m_unk70[0] = 0.0f;  // bge
    }
    if (m_unk50 == nullptr) {
        m_unk50 = ReceiverSrvFx()->AcquireFx(static_cast<IKFxData*>(m_pUnk54), this);
        if (m_unk50 != nullptr) {
            CVector3 position;
            if (m_pUnk34 == nullptr) {
                const RwV3d& p = FrameLtm(NodeFrame(m_pKGLObject))->pos;  // frame +0x80
                position = {p.x, p.y, p.z};
            } else {
                static_cast<CSGHotSpot*>(m_pUnk34)->GetWorldPosition(&position);  // 0x000ce790
            }
            SetOwnedParticleEffectPosition(static_cast<CKParticlesEffectNodeFx*>(m_unk50), &position, this);  // 0x001cdce0
        }
    }
    AddHotspotPointsToFx();
    return other;
}
