// CKHkS08CristalEmitter.cpp - reconstructed original translation unit 0x480508-0x483210 (GAME_TOC1, main_toc1), 37 functions, 33 live.
// Primary class: CKHkS08CristalEmitter  key 0x2bc2  category Hook  size 0x88  vtable 0xb27c00
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x480508  CKHkS08CristalEmitter_Delete
//   [ ] 0x480558  CKHkS08CristalEmitter_ReleaseFxAt60_maybe  [dead]
//   [ ] 0x4805c0  CKHkS08CristalEmitter_ReleaseFxAt6C_maybe  [dead]
//   [x] 0x480628  CKHkS08CristalEmitter_Resume  (inherited: IKHook's Resume)
//   [x] 0x480650  CKHkS08CristalEmitter_Pause  (inherited: IKHook's Pause)
//   [x] 0x480678  CKHkS08CristalEmitter_Stop  (inherited: IKHook's Stop)
//   [x] 0x4806a0  CKHkS08CristalEmitter_Start  (Start, vt+0x50)
//   [x] 0x480738  CKHkS08CristalEmitter_GetInfo  (GetInfo, vt+0x40)
//   [x] 0x480818  CKHkS08CristalEmitter_PostLoad  (PostLoad, vt+0x30)
//   [ ] 0x480878  CKHkS08CristalEmitter_Save
//   [x] 0x4808a0  CKHkS08CristalEmitter_RecursiveRegistration  (inherited: CKHkActorBase's)
//   [x] 0x4808c8  CKHkS08CristalEmitter_Destroy  (inherited: CKHkActorBase's Destroy)
//   [x] 0x4808f0  CKHkS08CristalEmitter_BaseDestructor  (the destructor)
//   [x] 0x480920  CKHkS08CristalEmitter_Construct  [dead]
//   [ ] 0x480978  CKHkS08CristalEmitter_Construct_2  [dead]
//   [x] 0x4809d0  CKHkS08CristalEmitter_DeleteArray
//   [ ] 0x480a78  RegisterCKHkS08CristalEmitterClass
//   [ ] 0x480b00  _GLOBAL__D_480b00
//   [ ] 0x480b10  _GLOBAL__I_480b10
//   [ ] 0x480b20  CKHkS08CristalEmitter_UpdateSoundPosition_maybe  [dead: no pointer to its descriptor 0xbc2498, no call]
//   [x] 0x480ba0  CKHkS08CristalEmitter_DeletingDestructor  (the deleting form of the destructor)
//   [x] 0x480be8  CKHkS08CristalEmitter_Destructor  (the destructor)
//   [x] 0x480c18  CKHkS08CristalEmitter_GetTriggerProp96  (GetInfo's value 0x96 accessor)
//   [x] 0x480c30  CKHkS08CristalEmitter_Create
//   [x] 0x480c98  CKHkS08CristalEmitter_CreateArray
//   [x] 0x480d70  CKHkS08CristalEmitter_SetOrbOpacity_maybe  (CKHkS08CristalEmitter::SetOrbOpacity)
//   [x] 0x481020  CKHkS08CristalEmitter_State1  (State1, the table +0x78; port-final F06)
//   [x] 0x4811c8  CKHkS08CristalEmitter_Restart  (Restart, vt+0x54)
//   [x] 0x481218  CKHkS08CristalEmitter_OnActivate  (VfA0)
//   [x] 0x481250  CKHkS08CristalEmitter_OnDeactivate  (VfA4)
//   [x] 0x4812c8  CKHkS08CristalEmitter_Update  (Update, vt+0x7c; port-final F06)
//   [x] 0x4816a0  CKHkS08CristalEmitter_Load
//   [ ] 0x481c40  CKHkS08CristalEmitter_ShowInputIcon_maybe  [dead: no pointer to its descriptor 0xbc2658, no call]
//   [ ] 0x481f20  CKHkS08CristalEmitter_StartParticleFxAtHotspot_maybe  [dead: no pointer to its descriptor 0xbc2660, no call]
//   [x] 0x482218  CKHkS08CristalEmitter_SpawnFx_maybe  (SpawnFx; port-final F06)
//   [x] 0x482518  CKHkS08CristalEmitter_MessageProc  (MessageProc, vt+0x1c; port-final F06)
//   [x] 0x482918  CKHkS08CristalEmitter_State0_OrbReady_maybe  (State0, the table +0x78; port-final F06)
//
//   [ ] 0x9c4800  CKHkS08CristalEmitter_IsKindOfClass  [inline]
//   [ ] 0x9c4858  CKHkS08CristalEmitter_GetClassType  [inline]
//   [ ] 0x9c4860  CKHkS08CristalEmitter_GetClassID  [inline]
#include "Spyro2008/hooks/CKHkS08CristalEmitter.h"

#include "k2000/io/IKFile.h"

// 0x004816a0 CKHkS08CristalEmitter_Load: the actor base, then the level data (type 0 only). The trigger
// starters are loaded with type 0.
int32_t CKHkS08CristalEmitter::Load(IKFile* file, int32_t type) {
    CKHkActorBase::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        IKFile_ReadRef(file, &m_pUnk24);
        ReadF32LE(file, &m_fUnk3C);
        IKFile_ReadRef(file, &m_pUnk20);
        IKFile_ReadRef(file, &m_pUnk40);
        IKFile_ReadRef(file, &m_pUnk34);
        m_unk48.Load(file, K_LEVEL_PLATEFORMS);
        IKFile_ReadRef(file, &m_pUnk44);
        IKFile_ReadRef(file, &m_pUnk30);
        IKFile_ReadRef(file, &m_pUnk50);
        ReadF32LE(file, &m_fUnk54);
        IKFile_ReadRef(file, &m_pUnk5C);
        IKFile_ReadRef(file, &m_pUnk64);
        IKFile_ReadRef(file, &m_pUnk68);
    }
    return 1;
}

// ==== P14 ===========================================================================================================
#include "k2000/core/IKInfo.h"

// 0x00480738 CKHkS08CristalEmitter_GetInfo: the actor base's answer (KStub_Return1_3f7140) folded with value 0x96's.
int32_t CKHkS08CristalEmitter::GetInfo(IKInfo* info, int32_t request) {
    const int32_t base = CKHkActorBase::GetInfo(info, request);
    int32_t own = 1;
    if (request == kGetInfoValueAccessor && info->m_ui32Id == 0x96) {
        // 0x00480c18 CKHkS08CristalEmitter_GetTriggerProp96: (+0x74 ^ 1) - 1, its sign: +0x74 == 1.
        own = AnswerInfo(info, [](IKSerializable* o, uint32_t) -> uint32_t {
            return static_cast<CKHkS08CristalEmitter*>(o)->m_unk74 == 1 ? 1u : 0u;
        }, 0);
    }
    if (base == 2 || own == 2) return 2;
    if (base == 0) return 0;
    return own;
}

// ==== port-rest R09 ===================================================================================================
#include "crt/ppc_ops.h"
#include "k2000/fx/IKFx.h"
#include "k2000/logic/CKTransformElement.h"
#include "k2000/scenegraph/CSGLeaf.h"

// 0x004806a0 CKHkS08CristalEmitter_Start (vt+0x50): the base's (empty); the two-state table (no state entered), +0x38 = 1,
// +0x2c / +0x60 / +0x28 = 0, +0x58 = FLT_MAX (0x00c4ace0, TOC1 +0x5c38 -> +0x28).
void CKHkS08CristalEmitter::Start() {
    CKHkActorBase::Start();  // 0x003f6e48
    m_aStateTable[0] = 0x00bc2688u;  // State0_OrbReady_maybe 0x482918
    m_unk38 = 1;
    m_aStateTable[2] = 0x00bc2558u;  // State1 0x481020
    m_unk2C = 0;
    m_aStateTable[1] = 0;
    m_aStateTable[3] = 0;
    m_pStateTable = m_aStateTable;
    m_unk74 = 0xff;
    m_unk75 = 2;
    m_pUnk60 = nullptr;
    m_pUnk28 = nullptr;
    m_fUnk58 = 3.40282347e+38f;
}

// 0x004811c8 CKHkS08CristalEmitter_Restart (vt+0x54): unless the sector is unloaded (IKLife bit 2) the orb transparent
// (SetOrbOpacity(0)); +0x58 = FLT_MAX.
void CKHkS08CristalEmitter::Restart() {
    if ((m_bitArray & 4u) == 0) SetOrbOpacity(0.0f);  // TOC1 +0x5c74
    m_fUnk58 = 3.40282347e+38f;
}

// 0x00481218 CKHkS08CristalEmitter_OnActivate (vt+0xa0): the actor base's (0x3f7338), then SetOrbOpacity(0).
void CKHkS08CristalEmitter::VfA0() {
    CKHkActorBase::VfA0();
    SetOrbOpacity(0.0f);
}

// 0x00481250 CKHkS08CristalEmitter_OnDeactivate (vt+0xa4): the actor base's (0x3f7370); the effect +0x6c stopped and
// released for this hook (vt+0x58), the slot cleared.
void CKHkS08CristalEmitter::VfA4() {
    CKHkActorBase::VfA4();
    if (m_pUnk6C != nullptr) {
        static_cast<IKFx*>(m_pUnk6C)->StopAndRelease(this);  // vt+0x58
        m_pUnk6C = nullptr;
    }
}

// 0x00480d70 CKHkS08CristalEmitter_SetOrbOpacity_maybe (the geometry walk is the inlined SetGeometriesAlpha:
// CKTransformElement.h)
void CKHkS08CristalEmitter::SetOrbOpacity(float opacity) {
    CSGLeaf* node = static_cast<CSGLeaf*>(m_pUnk50);
    if (node == nullptr) return;
    const float zero = 0.0f;  // TOC1 +0x5c74
    if (opacity <= zero) {  // cror lt|eq
        node->m_sgProperties = (node->m_sgProperties & 0xfffffffbu) | 4u;
        return;
    }
    if (opacity >= 1.0f) {  // TOC1 +0x5c6c, cror gt|eq
        node->m_sgProperties &= 0xfffffffbu;
        TransformFx::SetGeometriesAlpha(m_pUnk50, 0xfe);
        return;
    }
    const float kMax = 254.0f;  // TOC1 +0x5c70
    float scaled = opacity * kMax;
    node->m_sgProperties &= 0xfffffffbu;
    if (!(scaled <= kMax)) scaled = kMax;  // ble (NaN takes the clamp)
    TransformFx::SetGeometriesAlpha(m_pUnk50, static_cast<uint8_t>(ppc::fctiwz(scaled)));  // stfiwx, lbz +3
}

// ==== port-final F06 ==================================================================================================
#include "Renderware/rwcore/RwCamera.h"
#include "Spyro2008/groups/IKGrpHero.h"
#include "Spyro2008/hooks/CKHkS08CristalKey.h"
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "Spyro2008/logic/CKS08CarrierHero.h"
#include "Spyro2008/logic/CKS08GameManager.h"
#include "Spyro2008/misc/CKHkS08TransportableBase.h"
#include "k2000/core/Ps3MemberFn.h"
#include "k2000/dictionaries/CKSoundDictionaryID.h"
#include "k2000/groups/CKGrpTransportableObject.h"
#include "k2000/logic/CKLevel.h"
#include "k2000/logic/CKParticlesEffectFxData.h"
#include "k2000/logic/CKSector.h"
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/logic/IKFxData.h"
#include "k2000/logic/fx/CKExplosionNodeFx.h"
#include "k2000/logic/fx/CKInputIconNodeFx.h"
#include "k2000/logic/fx/CKParticlesEffectNodeFx.h"
#include "k2000/logic/sound/CKSound.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/CSGBranch.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/scenegraph/CSGSectorRoot.h"
#include "k2000/services/CKSrvFx.h"
#include "k2000/system/IKTime.h"

namespace {
// The table Start builds (+0x78): the descriptors' native handlers.
Ps3MemberFnEntry<CKHkS08CristalEmitter::StateFn> g_emitterStates[] = {
    {0x00bc2688u, &CKHkS08CristalEmitter::State0, "CKHkS08CristalEmitter_State0_OrbReady_maybe 0x482918", false},
    {0x00bc2558u, &CKHkS08CristalEmitter::State1, "CKHkS08CristalEmitter_State1 0x481020", false},
};

CKSrvFx* EmitterSrvFx() { return static_cast<CKSrvFx*>(g_pEngine->m_srvFx); }  // engine +0x60
CSGLeaf* NodeOf(IKSerializable* hook) { return static_cast<CSGLeaf*>(static_cast<IKHook*>(hook)->m_pKGLObject); }
RwFrame* FrameOf(IKSerializable* node) { return static_cast<CSGMovable*>(node)->m_pRwFrame; }  // node +0x04

// The position the effects take: the hot spot's world position, else the node's LTM position (frame +0x80).
void EffectPosition(IKSerializable* hotSpot, IKSerializable* node, CVector3* out) {
    if (hotSpot == nullptr) {
        const RwV3d& p = FrameLtm(FrameOf(node))->pos;
        *out = {p.x, p.y, p.z};
    } else {
        static_cast<CSGHotSpot*>(hotSpot)->GetWorldPosition(out);  // 0x000ce790
    }
}

// The effect of `slot` stopped and released for `owner` (vt+0x58), the slot cleared.
void StopAndReleaseSlot(IKSerializable** slot, const IKSerializable* owner) {
    if (*slot == nullptr) return;
    static_cast<IKFx*>(*slot)->StopAndRelease(owner);  // vt+0x58
    *slot = nullptr;
}

// 0x00362ac8 CKHkS08Hero_GetPlayerIndexIfControlled_maybe: the player (+0x26) of a hero it controls, else 0xff.
uint8_t PlayerIndexIfControlled(const CKHkS08Hero* hero) {
    return hero->m_ui8Hero == hero->m_ui8TrackedLeader ? hero->m_ui8Leader : 0xff;
}
}  // namespace

uint8_t CKHkS08CristalEmitter::CallState(const uint32_t pair[2], IKTime* clock, int32_t phase, uint8_t other) {
    StateFn fn = ResolvePs3MemberFn(g_emitterStates, pair, "CKHkS08CristalEmitter state handler");
    if (fn == nullptr) return other;
    return (this->*fn)(clock, phase, other);
}

void CKHkS08CristalEmitter::SwitchState(uint8_t next, IKTime* clock, uint8_t leaveOther) {
    const uint8_t old = m_unk74;
    if (old != 0xff) CallState(&m_pStateTable[old * 2u], clock, 2, leaveOther);
    m_unk74 = next;
    if (next != 0xff) CallState(&m_pStateTable[next * 2u], clock, 1, old);
}

// 0x004812c8 CKHkS08CristalEmitter_Update (vt+0x7c)
void CKHkS08CristalEmitter::Update(IKTime* clock) {
    CKHkActorBase::Update(clock);  // 0x003f6e68 (empty)
    if ((m_bitArray & 4u) == 0 && m_unk74 == 0xff) {
        CKHkS08CristalKey* key = static_cast<CKHkS08CristalKey*>(m_pUnk20);
        if (m_pUnk30 == nullptr) {
            m_pUnk28 = nullptr;
            key->m_pUnk20 = nullptr;
        } else {
            // 0x004a7ba8 (Ghidra CKGrpTransportableObject_TakePooledObjectOfType_maybe), class id 0xc2.
            m_pUnk28 = static_cast<CKGrpTransportableObject*>(m_pUnk30)->ActivateObjectOfType(0xc2);
            if (m_pUnk28 != nullptr) {
                static_cast<CKHkS08TransportableBase*>(m_pUnk28)->Vf108();   // vt+0x108
                static_cast<CKHkS08TransportableBase*>(m_pUnk28)->Vf128(1);  // vt+0x128
                static_cast<CKHkS08CristalKey*>(m_pUnk20)->m_unk39[0] = 0;   // stb of the life bit tested (0)
                SwitchState(0, nullptr, 0);
                static_cast<CKHkS08CristalKey*>(m_pUnk20)->m_unk39[0] = 1;
            }
            static_cast<CKHkS08CristalKey*>(m_pUnk20)->m_pUnk20 = m_pUnk28;
        }
    }
    const uint8_t state = m_unk74;
    if (state == 0xff) return;
    const uint8_t next = CallState(&m_pStateTable[state * 2u], clock, 0, state);
    if (next != m_unk74) SwitchState(next, clock, next);
}

// 0x00482518 CKHkS08CristalEmitter_MessageProc (vt+0x1c)
int32_t CKHkS08CristalEmitter::MessageProc(uint16_t message, void* data) {
    const int32_t base = CKHkActorBase::MessageProc(message, data);  // 0x003f7148
    if (message != 0x93f) {
        if (base == 3) return 3;
        if (base == 2) return 2;
        return base == 0 ? 0 : 1;  // (|base| - 1) >> 31 ^ 1
    }
    m_unk2C = static_cast<IKSerializable*>(data);
    CKHkS08Hero* hero = static_cast<CKHkS08Hero*>(m_unk2C);
    if (static_cast<KBase910C*>(hero->GetCarrier())->CanPickUp(m_pUnk28) == 0) return 0;  // 0x0032a000, vt+0x58
    // vt+0xf4 asked before the object is tested (as the original).
    if (static_cast<CKHkS08TransportableBase*>(m_pUnk28)->VfF4(static_cast<CKHkS08Hero*>(m_unk2C)->GetCarrier()) == 0) {
        return 0;
    }
    if (m_pUnk28 == nullptr) return 0;
    static_cast<CKS08CarrierHero*>(static_cast<CKHkS08Hero*>(m_unk2C)->GetCarrier())->m_bUnk90 = 1;
    if (static_cast<CKHkS08TransportableBase*>(m_pUnk28)->VfF0(static_cast<CKHkS08Hero*>(m_unk2C)->GetCarrier()) == 0) {
        return 0;
    }
    QueueTriggerSignals(&m_unk48);  // 0x00236338
    if (m_pUnk40 != nullptr) static_cast<CSGHotSpot*>(m_pUnk40)->DetachVolume(NodeOf(m_pUnk28));  // 0x000ce690
    // vt+0x84 of the hero's carrier (a CKS08CarrierHero: 0x9c54b8, its hot spot).
    CSGHotSpot* carry = static_cast<CSGHotSpot*>(
        static_cast<CKS08CarrierHero*>(static_cast<CKHkS08Hero*>(m_unk2C)->GetCarrier())->Vf7C());
    carry->AttachVolume(NodeOf(m_pUnk28));  // 0x000ce2b8
    SwitchState(1, nullptr, 1);
    StopAndReleaseSlot(&m_pUnk6C, this);
    static_cast<CKHkS08TransportableBase*>(m_pUnk28)->Vf128(0);  // vt+0x128
    m_fUnk58 = 0.0f;  // stw 0
    SpawnFx();
    static_cast<CKHkS08Hero*>(m_unk2C)->DetachFromObject();  // 0x00364608
    return 0;
}

// 0x00482218 CKHkS08CristalEmitter_SpawnFx_maybe
void CKHkS08CristalEmitter::SpawnFx() {
    IKFx* fx = EmitterSrvFx()->AcquireFx(static_cast<IKFxData*>(m_pUnk64), this);
    if (fx == nullptr) return;
    CKExplosionNodeFx* explosion = static_cast<CKExplosionNodeFx*>(fx);
    CVector3 position;
    EffectPosition(m_pUnk40, m_pKGLObject, &position);
    explosion->SetTranslation(&position, this);  // 0x001b66e8
    explosion->Trigger(this, nullptr);           // 0x001b82a8 (r5 = r6 = 0)
    explosion->ReleaseReservation(this);         // vt+0x54
}

// 0x00482918 CKHkS08CristalEmitter_State0_OrbReady_maybe (descriptor 0x00bc2688)
uint8_t CKHkS08CristalEmitter::State0(IKTime* /*clock*/, int32_t phase, uint8_t other) {
    if (phase == 1) {
        if (m_pUnk28 == nullptr) return 0xff;
        if (static_cast<CKHkS08TransportableBase*>(m_pUnk28)->Vf114() == nullptr) {  // vt+0x114: not carried
            CSGLeaf* node = NodeOf(m_pUnk28);
            node->m_pParent->RemoveChild(node);  // vt+0x78 (no test of the parent, as the original)
            if (m_pUnk40 == nullptr) {
                CKSector* sector = static_cast<CKSector*>(g_pEngine->m_level->m_vpSectors.m_pBlock[m_iSectorIndex]);
                sector->m_pSectorRoot->AddChild(node);  // vt+0x70
                RwFrame* frame = FrameOf(node);
                const RwV3d& at = FrameOf(m_pKGLObject)->modelling.pos;  // the emitter's position (frame +0x40)
                frame->modelling.pos.x = at.x;
                frame->modelling.pos.z = at.z;
                frame->modelling.pos.y = at.y;
                frame->modelling.flags &= 0xfffdffffu;  // no longer the identity (bit 17)
                RwFrame_MarkDirty(FrameOf(node));       // 0x00010698
            } else {
                static_cast<CSGHotSpot*>(m_pUnk40)->AttachVolume(node);  // 0x000ce2b8
            }
        }
        if (m_pUnk60 != nullptr) return other;
        // The data's byte +0x08 bit 4 cleared (rlwinm 27,1,31 / rlwinm 5,0,31: & 0xef).
        static_cast<CKParticlesEffectFxData*>(m_pUnk5C)->m_unk08 &= 0xefu;
        m_pUnk60 = EmitterSrvFx()->AcquireFx(static_cast<IKFxData*>(m_pUnk5C), this);
        if (m_pUnk60 == nullptr) return other;
        CVector3 position;
        EffectPosition(m_pUnk40, m_pKGLObject, &position);
        SetOwnedParticleEffectPosition(static_cast<CKParticlesEffectNodeFx*>(m_pUnk60), &position, this);  // 0x001cdce0
        return other;
    }
    if (phase == 2) {
        StopAndReleaseSlot(&m_pUnk60, this);
        StopAndReleaseSlot(&m_pUnk6C, this);
        return other;
    }
    if (phase != 0) return other;
    if (m_pUnk28 == nullptr) return 0xff;
    SetOrbOpacity(1.0f);  // TOC1 +0x5c6c
    IKGrpHero* group = static_cast<IKGrpHero*>(g_pEngine->m_gameManager->m_unk04[1]);  // engine +0x8c -> +0x08
    // BUG(original): without a hero group the count is the low byte of `this` (r31 kept), and the heroes are read
    // from the null group.
    const uint8_t count =
        group != nullptr ? group->GetHeroCount() : static_cast<uint8_t>(reinterpret_cast<uintptr_t>(this));  // 0x002ca038
    bool interacting = false;
    if (count != 0) {
        uint32_t index = 0;
        do {
            const uint8_t dragon = static_cast<uint8_t>(index);
            ++index;
            CKHkS08Hero* hero = static_cast<CKHkS08Hero*>(group->m_apHeros[dragon]);  // 0x002ca080 GetHeroByDragonIndex
            const RwV3d& own = FrameOf(m_pKGLObject)->modelling.pos;  // frame +0x40
            const RwV3d& at = FrameOf(hero->m_pKGLObject)->modelling.pos;
            const float radius2 = m_fUnk3C * m_fUnk3C;
            const float dy = at.y - own.y;
            const float dx = at.x - own.x;
            const float dz = at.z - own.z;
            const float d2 = ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy));
            if (!(d2 < radius2)) continue;                  // bge: a NaN skips the hero
            if (hero->IsPlayerControlled() == 0) continue;  // 0x00362af0
            if (hero->IsInCombo() != 0) continue;           // 0x0032a698
            interacting = true;
            static_cast<CKS08GameManager*>(g_pEngine->m_gameManager)
                ->SetHeroInteractionTarget(this, 1, PlayerIndexIfControlled(hero));  // 0x004ee770
        } while (count != static_cast<uint8_t>(index));
        if (interacting) {
            if (m_pUnk6C != nullptr) return other;
            m_pUnk6C = EmitterSrvFx()->AcquireFx(static_cast<IKFxData*>(m_pUnk68), this);
            if (m_pUnk6C == nullptr) return other;  // none free: +0x6c stays 0
            CVector3 position;
            EffectPosition(m_pUnk40, m_pKGLObject, &position);
            const CVector3 at = position;
            static_cast<CKInputIconNodeFx*>(m_pUnk6C)->SetPosition(&at);  // 0x001c45c8
            return other;
        }
    }
    StopAndReleaseSlot(&m_pUnk6C, this);
    return other;
}

// 0x00481020 CKHkS08CristalEmitter_State1 (descriptor 0x00bc2558)
uint8_t CKHkS08CristalEmitter::State1(IKTime* clock, int32_t phase, uint8_t other) {
    if (phase == 1) {
        CKSoundDictionaryID* sounds = static_cast<CKSoundDictionaryID*>(m_pUnk44);
        if (sounds->GetSound(0) != nullptr) sounds->GetSound(0)->Play(0.0f);  // 0x00112bc0, 0x00111230; TOC1 +0x5c74
        if (m_pUnk24 != nullptr) static_cast<CKHkActorBase*>(m_pUnk24)->SetEnabled(1);  // vt+0xcc
        m_fUnk58 = 0.0f;  // stw 0
        return other;
    }
    if (phase == 2) {
        if (m_pUnk24 != nullptr) static_cast<CKHkActorBase*>(m_pUnk24)->SetEnabled(0);
        SetOrbOpacity(0.0f);  // TOC1 +0x5c74
        return other;
    }
    if (phase == 0) {
        const float duration = m_fUnk54;
        float elapsed;
        if (!(m_fUnk58 < duration)) {  // bge: a NaN ends the fade
            elapsed = duration;
            m_fUnk58 = duration;
        } else {
            elapsed = m_fUnk58 + clock->m_afDeltaTime[0];  // the scalable game time (+0x1c)
            m_fUnk58 = elapsed;
        }
        SetOrbOpacity(1.0f - elapsed / duration);  // TOC1 +0x5c6c
    }
    return other;
}
