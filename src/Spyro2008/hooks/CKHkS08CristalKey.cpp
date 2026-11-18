// CKHkS08CristalKey.cpp - reconstructed original translation unit 0x478940-0x47b688 (GAME_TOC1, main_toc1), 35 functions, 31 live.
// Primary class: CKHkS08CristalKey  key 0x2b42  category Hook  size 0x4c  vtable 0xb27a10
// Other owners: CKHkS08CristalOrb (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x478940  CKHkS08CristalKey_Delete
//   [x] 0x478990  CKHkS08CristalKey_ApplyStatePreset_maybe  (ApplyStatePreset, vt+0xc8)
//   [ ] 0x478a08  CKHkS08CristalKey_IsCarriedByHero_2_maybe  [dead]
//   [x] 0x478af8  CKHkS08CristalKey_IsCarriedByEnemy_maybe  (CKHkS08CristalKey.h IsCarriedByEnemy)
//   [ ] 0x478be8  RegisterCKHkS08CristalKeyClass
//   [ ] 0x478c60  _GLOBAL__I_478c60
//   [x] 0x478c70  CKHkS08CristalKey_Resume  (inherited: IKHook's Resume)
//   [x] 0x478c98  CKHkS08CristalKey_Pause  (inherited: IKHook's Pause)
//   [x] 0x478cc0  CKHkS08CristalKey_SetDefaultState  (SetDefaultState, vt+0x38)
//   [x] 0x478d30  CKHkS08CristalKey_Stop  (inherited: IKHook's Stop)
//   [x] 0x478d58  CKHkS08CristalKey_Start  (Start, vt+0x50)
//   [x] 0x478da8  CKHkS08CristalKey_PostLoad  (inherited: CKHkActorBase's PostLoad)
//   [ ] 0x478dd0  CKHkS08CristalKey_Save
//   [x] 0x478df8  CKHkS08CristalKey_RecursiveRegistration  (inherited: CKHkActorBase's)
//   [x] 0x478e20  CKHkS08CristalKey_Destroy  (inherited: CKHkActorBase's Destroy)
//   [x] 0x478e48  CKHkS08CristalKey_BaseDestructor  (the destructor)
//   [x] 0x478e78  CKHkS08CristalKey_Construct  [dead]
//   [ ] 0x478eb0  CKHkS08CristalKey_Construct_2  [dead]
//   [x] 0x478ee8  CKHkS08CristalKey_DeleteArray
//   [x] 0x478f88  CKHkS08CristalKey_OnDeactivate  (VfA4 OnDeactivate, vt+0xa4)
//   [x] 0x4790f0  CKHkS08CristalKey_DeletingDestructor  (the deleting form of the destructor)
//   [x] 0x479138  CKHkS08CristalKey_Destructor  (the destructor)
//   [x] 0x479168  CKHkS08CristalKey_GetInfo  (GetInfo, vt+0x40)
//   [x] 0x4792c0  CKHkS08CristalKey_CreateArray
//   [x] 0x479370  CKHkS08CristalKey_Create
//   [x] 0x4793c8  CKHkS08CristalKey_Load
//   [ ] 0x479610  CKHkS08CristalKey_UpdateCarriedByHeroTrigger_maybe  [dead]
//   [x] 0x479738  CKHkS08CristalKey_IsCarriedByHero_maybe  (CKHkS08CristalKey.h IsCarriedByHero)
//   [x] 0x479828  CKHkS08CristalKey_IsCarried_maybe  (CKHkS08CristalKey.h IsCarried)
//   [x] 0x4799b0  CKHkS08CristalKey_Restart  (Restart, vt+0x54)
//   [x] 0x47a390  CKHkS08CristalKey_MessageProc  (MessageProc, vt+0x1c)
//   [x] 0x47a830  CKHkS08CristalKey_Update  (Update, vt+0x7c)
//   [x] 0x47b0c0  CKHkS08CristalKey_OnActivate  (VfA0 OnActivate, vt+0xa0)
//   [x] 0x47b630  CKHkS08CristalOrb_Delete  (the registry factory Delete: DOTD_DECLARE_FACTORIES(CKHkS08CristalOrb), CKHkS08CristalOrb.h)
//   [x] 0x47b680  KStub_ReturnArg4_47b680  (CKHkS08CristalOrb::State3, CKHkS08CristalOrb.h; descriptor 0xbc1c30 in the orb's table)
//
//   [ ] 0x9c4730  CKHkS08CristalKey_IsKindOfClass  [inline]
//   [ ] 0x9c4788  CKHkS08CristalKey_GetClassType  [inline]
//   [ ] 0x9c4790  CKHkS08CristalKey_GetClassID  [inline]
#include "Spyro2008/hooks/CKHkS08CristalKey.h"

#include "k2000/io/IKFile.h"

// 0x004793c8 CKHkS08CristalKey_Load: the actor base, then the level data (type 0 only). The trigger
// starters are loaded with type 0.
int32_t CKHkS08CristalKey::Load(IKFile* file, int32_t type) {
    CKHkActorBase::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        IKFile_ReadRef(file, &m_pUnk24);
        IKFile_ReadRef(file, &m_pUnk28);
        ReadU8(file, &m_unk34);
        ReadU8(file, &m_unk38);
        ReadU8(file, &m_unk37);
        ReadU8(file, &m_unk36);
        ReadU8(file, &m_unk3A);
        m_unk3C.Load(file, K_LEVEL_PLATEFORMS);
    }
    return 1;
}

// ==== port-rest R09 ===================================================================================================
#include "Spyro2008/misc/CKHkS08TransportableBase.h"
#include "k2000/core/IKInfo.h"

// The carrier test of 0x00479738 / 0x00478af8 (the carrier asked twice, as the original does: vt+0x114, then vt+0x114 and
// its class id, vt+0x18).
uint8_t CKHkS08CristalKey::IsCarriedBy(int32_t classId) const {
    CKHkS08TransportableBase* object = static_cast<CKHkS08TransportableBase*>(m_pUnk20);
    if (object == nullptr) return 0;
    if (object->Vf114() == nullptr) return 0;
    return object->Vf114()->GetClassID() == classId ? 1 : 0;
}

// 0x00479168 CKHkS08CristalKey_GetInfo
int32_t CKHkS08CristalKey::GetInfo(IKInfo* info, int32_t request) {
    const int32_t base = CKHkActorBase::GetInfo(info, request);  // KStub_Return1_3f7140
    int32_t own = 1;
    if (request == kGetInfoValueAccessor) {
        if (info->m_ui32Id == 0x99) {
            own = AnswerInfo(info, [](IKSerializable* o, uint32_t) -> uint32_t {
                return static_cast<CKHkS08CristalKey*>(o)->IsCarriedByHero();  // 0x00479738
            }, 0);
        } else if (info->m_ui32Id == 0x9a) {
            own = AnswerInfo(info, [](IKSerializable* o, uint32_t) -> uint32_t {
                return static_cast<CKHkS08CristalKey*>(o)->IsCarriedByEnemy();  // 0x00478af8
            }, 0);
        } else if (info->m_ui32Id == 0x98) {
            own = AnswerInfo(info, [](IKSerializable* o, uint32_t) -> uint32_t {
                return static_cast<CKHkS08CristalKey*>(o)->IsCarried();  // 0x00479828
            }, 0);
        }
    }
    if (base == 2 || own == 2) return 2;
    if (base == 0) return 0;
    return own;
}

// ==== port-final F06: the run time ====================================================================================
#include "Spyro2008/groups/CKGrpS08Meca.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "Spyro2008/hooks/CKHkS08CristalEmitter.h"
#include "Spyro2008/hooks/CKHkS08CristalReceiver.h"
#include "Spyro2008/components/CKS08FightZoneCpnt.h"
#include "k2000/groups/CKGrpFightZone.h"
#include "k2000/groups/CKGrpTransportableObject.h"
#include "k2000/logic/CKLevel.h"
#include "k2000/logic/CKSector.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/CSGBranch.h"
#include "k2000/scenegraph/CSGLeaf.h"
#include "k2000/scenegraph/CSGSectorRoot.h"
#include "k2000/services/CKSrvTrigger.h"
#include "k2000/services/CTriggerStarter.h"

namespace {
CKHkS08CristalEmitter* EmitterOf(const CKHkS08CristalKey* key) { return static_cast<CKHkS08CristalEmitter*>(key->m_pUnk24); }
CKHkS08CristalReceiver* ReceiverOf(const CKHkS08CristalKey* key) { return static_cast<CKHkS08CristalReceiver*>(key->m_pUnk28); }
CKHkS08TransportableBase* ObjectOf(const CKHkS08CristalKey* key) { return static_cast<CKHkS08TransportableBase*>(key->m_pUnk20); }
CSGLeaf* ObjectNode(const CKHkS08CristalKey* key) { return static_cast<CSGLeaf*>(ObjectOf(key)->m_pKGLObject); }
// The meca group's (game manager +0x0c) transportable group (+0x48).
CKGrpTransportableObject* TransportableGroup() {
    return static_cast<CKGrpTransportableObject*>(static_cast<CKGrpS08Meca*>(g_pEngine->m_gameManager->m_unk04[2])->m_pUnk48);
}
// Sector 0's root of a level (the engine's +0x90 or the game manager's +0x18, as each caller reads it).
CSGSectorRoot* FirstSectorRoot(CKLevel* level) {
    return static_cast<CKSector*>(level->m_vpSectors.m_pBlock[0])->m_pSectorRoot;
}
// The emitter takes the key when it waits (state 0), or the receiver gives it back (state 1): the emitter's / the
// receiver's switch is all the "free" test the code makes.
bool EmitterFreeOrReceiverHolding(const CKHkS08CristalKey* key) {
    return EmitterOf(key)->GetState() == 0 || ReceiverOf(key)->GetState() == 1;
}
// The transportable's node back under sector 0's root (its parent's vt+0x78 when it has one, the root's vt+0x70) and
// the transportable back into the group's pool.
void ReleaseObject(CKHkS08CristalKey* key, CKGrpTransportableObject* group) {
    CSGLeaf* node = ObjectNode(key);
    if (node->m_pParent != nullptr) node->m_pParent->RemoveChild(node);  // vt+0x78
    FirstSectorRoot(g_pEngine->m_gameManager->m_level)->AddChild(ObjectNode(key));  // vt+0x70 (game manager +0x18)
    group->ReleaseObject(key->m_pUnk20);  // 0x004a7ce0
}
// The key handed to the fight zone's component (message 0x996, Update): the emitter takes it (state 0 -> 1) or the
// receiver gives it (state 1 -> 0), else nothing; the transportable hidden, kept by the component (+0x94), not placed
// (vt+0x128 0), its node under sector 0's root. False when neither machine could take it.
bool GiveToFightZone(CKHkS08CristalKey* key, CKS08FightZoneCpnt* cpnt, bool clearPending) {
    CKHkS08CristalEmitter* emitter = EmitterOf(key);
    if (emitter->GetState() == 0) {
        emitter->SwitchState(1, nullptr, 1);
    } else {
        CKHkS08CristalReceiver* receiver = ReceiverOf(key);
        if (receiver->GetState() != 1) return false;
        receiver->SwitchState(0, nullptr, 0);
    }
    CSGLeaf* hidden = ObjectNode(key);
    hidden->m_sgProperties = (hidden->m_sgProperties & 0xfffffffbu) | 4u;
    if (clearPending) {
        key->m_unk2C = 0;
        key->m_unk30 = nullptr;
    }
    cpnt->m_unk94 = key->m_pUnk20;
    ObjectOf(key)->Vf128(0);  // vt+0x128
    CSGLeaf* node = ObjectNode(key);
    node->m_pParent->RemoveChild(node);                            // vt+0x78
    FirstSectorRoot(g_pEngine->m_level)->AddChild(ObjectNode(key));  // vt+0x70 (engine +0x90)
    return true;
}
// A fresh transportable taken from the pool (class id 0xc2), its emitter told; with one, its state machine started
// (vt+0x108) and placed (vt+0x128 1).
CKHkS08TransportableBase* TakeObject(CKHkS08CristalKey* key, CKGrpTransportableObject* group) {
    key->m_pUnk20 = group->ActivateObjectOfType(0xc2);  // 0x004a7ba8
    return ObjectOf(key);
}
// Both machines switched to `state` (the emitter first).
void SwitchBoth(CKHkS08CristalKey* key, uint8_t state) {
    EmitterOf(key)->SwitchState(state, nullptr, state);
    ReceiverOf(key)->SwitchState(state, nullptr, state);
}
}  // namespace

// 0x00478f88 CKHkS08CristalKey_OnDeactivate (vt+0xa4): the base's; the transportable (when the emitter is free or
// the receiver holds it) back into the pool. +0x39 is 0 while it runs.
void CKHkS08CristalKey::VfA4() {
    CKHkActorBase::VfA4();  // 0x003f7370
    m_unk39[0] = 0;
    if (EmitterFreeOrReceiverHolding(this) && m_pUnk20 != nullptr) {
        ReleaseObject(this, TransportableGroup());
        m_pUnk20 = nullptr;
        EmitterOf(this)->m_pUnk28 = nullptr;
    }
    m_unk39[0] = 1;
}

// 0x004799b0 CKHkS08CristalKey_Restart (vt+0x54): the runtime cleared; a key a hero carries while the emitter and
// receiver are past it (emitter 1, receiver 0, +0x3a) stays. A dead life (+0x0c bit 2) only gives the free
// transportable back. Else a missing transportable is taken (+0x48 = 1) or the present one given back, then both
// machines restart (+0x48 1: state 0, 0: state 1).
void CKHkS08CristalKey::Restart() {
    m_unk2C = 0;
    m_unk30 = nullptr;
    m_unk44 = 0;
    m_unk39[0] = 0;
    if (EmitterOf(this)->GetState() == 1 && ReceiverOf(this)->GetState() == 0 && m_unk3A != 0 && IsCarriedByHero() != 0) {
        m_unk39[0] = 1;
        return;
    }
    CKGrpTransportableObject* group = TransportableGroup();
    if ((m_bitArray & 4u) != 0) {
        if (EmitterFreeOrReceiverHolding(this) && m_pUnk20 != nullptr) {
            ReleaseObject(this, group);
            m_pUnk20 = nullptr;
            EmitterOf(this)->m_pUnk28 = nullptr;
        }
        m_unk39[0] = 1;
        return;
    }
    if (m_pUnk20 == nullptr) {
        TakeObject(this, group);
        EmitterOf(this)->m_pUnk28 = m_pUnk20;
        if (m_pUnk20 != nullptr) {
            ObjectOf(this)->Vf158(static_cast<uint8_t>(m_unk3A ^ 1));  // vt+0x158
            m_unk48 = 1;
            ObjectOf(this)->Vf108();   // vt+0x108
            ObjectOf(this)->Vf128(1);  // vt+0x128
            SwitchBoth(this, 0);
        }
    } else {
        if (EmitterFreeOrReceiverHolding(this)) ReleaseObject(this, group);
        m_pUnk20 = nullptr;
        EmitterOf(this)->m_pUnk28 = nullptr;
    }
    if (m_unk48 == 1) {
        SwitchBoth(this, 0);
    } else if (m_unk48 == 0) {
        SwitchBoth(this, 1);
    }
    m_unk39[0] = 1;
}

// 0x0047a390 CKHkS08CristalKey_MessageProc (vt+0x1c): 0x996 (a trigger's object parameter: a CKGrpFightZone) hands the
// transportable to the zone's component, or remembers the zone (+0x30, +0x2c) when there is no transportable or
// component yet; 0x997 (a byte parameter) sets +0x3a and the transportable's vt+0x158 (its negation).
int32_t CKHkS08CristalKey::MessageProc(uint16_t message, void* data) {
    const int32_t base = CKHkActorBase::MessageProc(message, data);  // 0x003f7148
    int32_t own = 1;
    if (message == 0x996) {
        own = 0;
        IKSerializable* zone = static_cast<CTriggerAction*>(data)->m_mdParam.m_pObject;
        if (zone != nullptr) {
            CKS08FightZoneCpnt* cpnt = static_cast<CKGrpFightZone*>(zone)->m_pFightZoneCpnt;
            if (m_pUnk20 == nullptr || cpnt == nullptr) {
                m_unk30 = zone;
                m_unk2C = 1;
            } else {
                GiveToFightZone(this, cpnt, false);
            }
        }
    } else if (message == 0x997 && m_pUnk20 != nullptr) {
        const uint8_t value = static_cast<uint8_t>(static_cast<CTriggerAction*>(data)->m_mdParam.m_ui32Value);  // lbz +0
        m_unk3A = value;
        ObjectOf(this)->Vf158(static_cast<uint8_t>(value ^ 1));  // vt+0x158
    }
    if (base == 3 || own == 3) return 3;
    if (base == 2 || own == 2) return 2;
    if (base == 0) return 0;
    return own;
}

// 0x0047a830 CKHkS08CristalKey_Update (vt+0x7c): the base's; a missing (with the emitter free or the receiver holding)
// or pooled-again (vt+0x140) transportable replaced from the pool; a remembered fight zone served; the trigger +0x3c
// fired when a hero (carrier class id 0x247) starts carrying it (+0x44 the last frame's).
void CKHkS08CristalKey::Update(IKTime* clock) {
    CKHkActorBase::Update(clock);  // 0x003f6e68
    CKGrpTransportableObject* group = TransportableGroup();
    if (m_pUnk20 == nullptr) {
        if (EmitterFreeOrReceiverHolding(this)) {
            if (TakeObject(this, group) != nullptr) {
                EmitterOf(this)->m_pUnk28 = m_pUnk20;
                ObjectOf(this)->Vf108();   // vt+0x108
                ObjectOf(this)->Vf128(1);  // vt+0x128
                ObjectOf(this)->Vf158(static_cast<uint8_t>(m_unk3A ^ 1));  // vt+0x158
            }
        }
    } else if (ObjectOf(this)->Vf140() != 0) {  // vt+0x140
        // (the old transportable is not given back: it is in the pool again)
        if (TakeObject(this, group) != nullptr) {
            EmitterOf(this)->m_pUnk28 = m_pUnk20;
            ObjectOf(this)->Vf108();   // vt+0x108
            ObjectOf(this)->Vf128(1);  // vt+0x128
            SwitchBoth(this, 0);
        }
    }
    if (m_unk2C != 0 && m_pUnk20 != nullptr) {
        CKS08FightZoneCpnt* cpnt = static_cast<CKGrpFightZone*>(m_unk30)->m_pFightZoneCpnt;
        if (cpnt != nullptr) GiveToFightZone(this, cpnt, true);
    }
    uint8_t carried = 0;
    if (m_pUnk20 != nullptr && ObjectOf(this)->Vf114() != nullptr) {  // vt+0x114
        if (ObjectOf(this)->Vf114()->GetClassID() == 0x247) carried = 1;  // vt+0x18
    }
    if (m_unk44 == 0 && carried != 0) QueueTriggerSignals(&m_unk3C);  // 0x00236338
    m_unk44 = carried;
}

// 0x0047b0c0 CKHkS08CristalKey_OnActivate (vt+0xa0): the base's; without a transportable one is taken from the pool
// (vt+0x158 the negated +0x3a) and both machines start by +0x48 (1: state 0, 0: state 1). +0x39 is 0 while it runs.
void CKHkS08CristalKey::VfA0() {
    CKHkActorBase::VfA0();  // 0x003f7338
    m_unk39[0] = 0;
    m_unk44 = 0;
    if (m_pUnk20 == nullptr) {
        TakeObject(this, TransportableGroup());
        EmitterOf(this)->m_pUnk28 = m_pUnk20;
        if (m_pUnk20 != nullptr) {
            ObjectOf(this)->Vf158(static_cast<uint8_t>(m_unk3A ^ 1));  // vt+0x158
            if (m_unk48 == 1) {
                ObjectOf(this)->Vf108();   // vt+0x108
                ObjectOf(this)->Vf128(1);  // vt+0x128
                SwitchBoth(this, 0);
            } else if (m_unk48 == 0) {
                ObjectOf(this)->Vf108();
                ObjectOf(this)->Vf128(1);
                SwitchBoth(this, 1);
            }
        }
    }
    m_unk39[0] = 1;
}
