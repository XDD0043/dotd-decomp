// CKS08CarrierHero.cpp - reconstructed original translation unit 0x4b08d8-0x4b4750 (GAME_TOC1, main_toc1), 40 functions, 36 live.
// Primary class: CKS08CarrierHero  key 0x91cc  category Logic  size 0xbc  vtable 0xb28d98
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x4b08d8  CKS08CarrierHero_Delete
//   [ ] 0x4b0928  CKS08CarrierHero_vf78
//   [ ] 0x4b0960  CKS08CarrierHero_IsCarriedObjectAttachedToCarrierHotSpot_maybe
//   [ ] 0x4b0a00  CKS08CarrierHero_SetNearbyReceiver_maybe
//   [ ] 0x4b0a38  CKS08CarrierHero_HasNearbyReceiver_maybe
//   [ ] 0x4b0a40  CKS08CarrierHero_GetNearbyReceiver_maybe  [dead]
//   [ ] 0x4b0a48  CKS08CarrierHero_CaptureCarryPose_maybe
//   [ ] 0x4b0bd0  CKS08CarrierHero_CanPickUp_maybe
//   [ ] 0x4b0cc8  CKS08CarrierHero_Save
//   [ ] 0x4b0cf0  CKS08CarrierHero_RecursiveRegistration
//   [ ] 0x4b0d18  CKS08CarrierHero_Destroy
//   [x] 0x4b0d60  CKS08CarrierHero_DeleteArray
//   [x] 0x4b0e00  CKS08CarrierHero_Construct  [dead]
//   [ ] 0x4b0e58  RegisterCKS08CarrierHeroClass
//   [ ] 0x4b0ee0  _GLOBAL__D_4b0ee0
//   [ ] 0x4b0ef0  _GLOBAL__I_4b0ef0
//   [ ] 0x4b0f00  CKS08CarrierHero_DestructBody
//   [ ] 0x4b0f30  CKS08CarrierHero_DropCarriedObject_maybe
//   [ ] 0x4b1080  CKS08CarrierHero_DeletingDestructor
//   [ ] 0x4b10c8  CKS08CarrierHero_Destructor
//   [ ] 0x4b10f8  CKS08CarrierHero_Construct_2  [dead]
//   [ ] 0x4b1150  CKS08CarrierHero_StartCarrying_2_maybe
//   [ ] 0x4b1368  CKS08CarrierHero_PostLoad
//   [ ] 0x4b1370  CKS08CarrierHero_vf5C
//   [ ] 0x4b14e0  CKS08CarrierHero_StopCarrying_maybe
//   [ ] 0x4b1628  CKS08CarrierHero_LerpCarriedObjectToHotSpot_maybe
//   [ ] 0x4b19f0  CKS08CarrierHero_vf60
//   [x] 0x4b1a90  CKS08CarrierHero_CreateArray
//   [x] 0x4b1b60  CKS08CarrierHero_Create
//   [ ] 0x4b1bc8  CKS08CarrierHero_IsInGrabRangeAndAngle_maybe
//   [ ] 0x4b1de0  CKS08CarrierHero_FindPickupInRange_maybe
//   [ ] 0x4b2200  CKS08CarrierHero_FindAnyPickupInRange_maybe  [dead]
//   [x] 0x4b2288  CKS08CarrierHero_Load
//   [ ] 0x4b26c0  CKS08CarrierHero_CarryState_maybe
//   [ ] 0x4b30f8  CKS08CarrierHero_State1_LookForPickup_maybe
//   [ ] 0x4b3958  CKS08CarrierHero_MessageProc
//   [ ] 0x4b3e40  CKS08CarrierHero_DropCarriedObjectAndReset_maybe
//   [x] 0x4b4118  CKS08CarrierHero_Reset_maybe
//   [ ] 0x4b4300  CKS08CarrierHero_StartCarrying_maybe
//   [x] 0x4b4518  CKS08CarrierHero_UpdateStateMachine
//
//   [ ] 0x9c5468  CKS08CarrierHero_IsKindOfClass  [inline]
//   [ ] 0x9c54a0  CKS08CarrierHero_GetClassType  [inline]
//   [ ] 0x9c54a8  CKS08CarrierHero_GetClassID  [inline]
//   [ ] 0x9c54b0  CKS08CarrierHero_vf64  [inline]
//   [ ] 0x9c54b8  CKS08CarrierHero_vf84  [inline]
//   [ ] 0x9c54c0  CKS08CarrierHero_vf7C  [inline]
//   [ ] 0x9c54c8  CKS08CarrierHero_vf80  [inline]
#include "Spyro2008/logic/CKS08CarrierHero.h"
#include "k2000/groups/IKBaseGroup.h"
#include "k2000/scenegraph/CSGBranch.h"
#include "k2000/misc/Engine.h"
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/core/Ps3MemberFn.h"
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "k2000/core/Stub.h"

#include "k2000/io/IKFile.h"

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
    {0x00bc7c38u, nullptr, "CKS08CarrierHero_CarryState_maybe 0x4b26c0 (C2.8: carrying)", false},
    {0x00bc7c40u, nullptr, "CKS08CarrierHero_State1_LookForPickup_maybe 0x4b30f8 (C2.8: carrying)", false},
};
}  // namespace

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
    m_unk44[(0x94 - 0x44) / 4] = 0;  // +0x94
    m_pCarriedObject = nullptr;      // +0x18
    m_unk44[(0x90 - 0x44) / 4] &= 0x00ffffffu;  // the byte at +0x90
    if (m_pHotSpot != nullptr) {
        CSGBranch* branch = static_cast<CSGBranch*>(m_pBranch);
        CSGBranch* parent = branch->m_pParent;
        if (parent != nullptr) parent->RemoveChild(branch);  // vt+0x78
        static_cast<CSGHotSpot*>(m_pHotSpot)->AttachVolume(branch);  // 0x000ce2b8
    }
    m_unk44[(0x9c - 0x44) / 4] &= 0x00ffffffu;  // the byte at +0x9c
    m_unk44[(0xa0 - 0x44) / 4] = 0;              // +0xa0
}

// 0x004b4518 CKS08CarrierHero_UpdateStateMachine (vt+0x74): the hero is not carrying (CKHkS08Hero_SetCarryingObject_maybe
// 0x32a438 with 0: +0xed4 bit 3), the carrier's state machine runs (handlers +0xa4, current state +0xa8), then +0x9c
// and +0xa0 clear. The states' handlers are C2.8 (carrying).
void CKS08CarrierHero::UpdateStateMachine(IKTime* clock) {
    CKHkS08Hero* hero = static_cast<CKHkS08Hero*>(m_pHero);
    hero->m_unked4 = (hero->m_unked4 & 0xfffffff7u) | (0u << 3);
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
    m_unk44[(0x9c - 0x44) / 4] &= 0x00ffffffu;  // the byte at +0x9c
    m_unk44[(0xa0 - 0x44) / 4] = 0;              // +0xa0
}
