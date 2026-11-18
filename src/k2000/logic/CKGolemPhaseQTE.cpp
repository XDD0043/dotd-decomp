// CKGolemPhaseQTE.cpp - reconstructed original translation unit 0x4bddd8-0x4bed00 (GAME_TOC1, main_toc1), 43 functions, 37 live.
// Primary class: CKGolemPhaseQTE  key 0xa10c  category Logic  size 0x2c  vtable 0xb291d0
// Other owners: CKHkGolem (8)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x4bddd8  CKGolemPhaseQTE_Delete
//   [x] 0x4bde28  CKGolemPhaseQTE_ResetPhases_maybe
//   [x] 0x4bde30  CKGolemPhaseQTE_vf60
//   [x] 0x4bde38  CKGolemPhaseQTE_vf64
//   [x] 0x4bde40  CKGolemPhaseQTE_vf68
//   [x] 0x4bde48  CKGolemPhaseQTE_MessageProc
//   [x] 0x4bde80  CKGolemPhaseQTE_vf84
//   [ ] 0x4bde88  RegisterCKGolemPhaseQTEClass
//   [ ] 0x4bdf00  _GLOBAL__I_4bdf00
//   [x] 0x4bdf10  CKGolemPhaseQTE_GetDamageSinceUpdate_maybe
//   [x] 0x4bdf50  CKGolemPhaseQTE_vf74
//   [x] 0x4bdf90  CKGolemPhaseQTE_MarkDamageBaseline_maybe
//   [x] 0x4bdfc8  CKGolemPhaseQTE_GetDamageSincePhaseStart_maybe
//   [x] 0x4be008  CKGolemPhaseQTE_vf58
//   [ ] 0x4be038  CKGolemPhaseQTE_Save
//   [x] 0x4be060  CKGolemPhaseQTE_RecursiveRegistration  (inherited: KBase978C_vf24)
//   [x] 0x4be088  CKGolemPhaseQTE_Destroy  (KStub_Nop_4c76d0: empty, inherited)
//   [x] 0x4be0b0  CKGolemPhaseQTE_DeletingDestructor  (C++ destructor chain: vtable stores only)
//   [x] 0x4be0f8  CKGolemPhaseQTE_Destructor  (the base's vtable only: inherited)
//   [x] 0x4be128  CKGolemPhaseQTE_DestructBody  (C++ destructor chain: vtable stores only)
//   [x] 0x4be158  CKGolemPhaseQTE_Construct  [dead]
//   [ ] 0x4be190  CKGolemPhaseQTE_Construct_2  [dead]
//   [x] 0x4be1c8  CKGolemPhaseQTE_DeleteArray
//   [x] 0x4be268  CKGolemPhaseQTE_Start
//   [x] 0x4be2e0  CKGolemPhaseQTE_vf80
//   [x] 0x4be2f8  CKGolemPhaseQTE_vf7C
//   [x] 0x4be310  CKGolemPhaseQTE_Update_maybe
//   [x] 0x4be3b8  CKGolemPhaseQTE_CreateArray
//   [x] 0x4be468  CKGolemPhaseQTE_Create
//   [x] 0x4be4c0  CKGolemPhaseQTE_Load
//   [x] 0x4be6f0  CKHkGolem_Delete  (the registry factory: DOTD_DECLARE_FACTORIES in CKHkGolem.h)
//   [ ] 0x4be740  FUN_004be740  [dead]
//   [ ] 0x4be8e8  FUN_004be8e8  [dead]
//   [ ] 0x4bea90  CKHkGolem_ReleaseEntryObjectsById_maybe  [dead]
//   [x] 0x4bec68  CKHkGolem_GetDamageTakenSinceMark_maybe
//   [x] 0x4bec80  CKHkGolem_GetTotalDamageTaken
//   [x] 0x4bec88  CKHkGolem_MarkDamageTaken_maybe
//   [ ] 0x4bec98  FUN_004bec98  [dead]
//   [x] 0x4becb0  CKHkGolem_GetTime50_maybe
//   [x] 0x4becb8  CKHkGolem_GetTime54_maybe
//   [x] 0x4becc0  KStub_Return1_4becc0
//   [x] 0x4becc8  CKHkGolem_ApplyDamagePoints_maybe
//   [x] 0x4becf8  KStub_Nop_4becf8
//
//   [ ] 0x9c56a0  CKGolemPhaseQTE_IsKindOfClass  [inline]
//   [ ] 0x9c56d8  CKGolemPhaseQTE_GetClassType  [inline]
//   [ ] 0x9c56e0  CKGolemPhaseQTE_GetClassID  [inline]
#include "k2000/logic/CKGolemPhaseQTE.h"

#include <cstring>

#include "k2000/hooks/CKHkGolem.h"
#include "k2000/hooks/CKHkSequenceMgr.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKGolemPhaseManager.h"
#include "k2000/misc/Engine.h"
#include "k2000/system/CTimeManager.h"

// 0x004be4c0 CKGolemPhaseQTE_Load: CKGolemPhaseBase's data, then, for K_LEVEL_PLATEFORMS only, a reference and
// five words.
int32_t CKGolemPhaseQTE::Load(IKFile* file, int32_t type) {
    CKGolemPhaseBase::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        IKFile_ReadRef(file, &m_unk08);
        ReadS32LE(file, &m_unk18);
        ReadS32LE(file, &m_unk1c);
        ReadS32LE(file, &m_unk20);
        ReadS32LE(file, &m_unk24);
        ReadF32LE(file, &m_unk28);
    }
    return 1;
}

// ---- C2.8: the QTE phase ----

// 0x004bde48 CKGolemPhaseQTE_MessageProc: the sequence manager's listener message (CKHkSequenceMgr::SListenerMsg).
// BUG(original): request 7's answer byte is written at the message's first byte (the sender word), not at its data
// pointer (+0x08); the manager's byte stays 1 (a wrong input counts) and the sender word is not read again.
int32_t CKGolemPhaseQTE::MessageProc(uint16_t message, void* data) {
    if (message != 0x407) return 1;
    const uint32_t request = static_cast<const CKHkSequenceMgr::SListenerMsg*>(data)->m_ui32Request;  // +0x04
    if (request < 7) return 0;
    if (request == 7) {
        static_cast<uint8_t*>(data)[0] = 1;
        return 0;
    }
    return 1;
}

// 0x004be268 CKGolemPhaseQTE_Start: the sequence (if any) starts with this phase as its listener (the frame clock,
// index 0); the damage marks.
void CKGolemPhaseQTE::Start() {
    if (m_unk08 != nullptr) {
        static_cast<CKHkSequenceMgr*>(m_unk08)->StartSequenceWithListener(this, g_pEngine->m_timeManager->m_pTime, 0);
    }
    m_unk0c = Golem()->GetDamageTakenSinceMark();  // 0x004bec68
    m_unk10 = Golem()->GetDamageTakenSinceMark();
}

// 0x004be310 CKGolemPhaseQTE_Update_maybe: the damage since the golem's mark kept; once the sequence no longer runs
// (+0xd4 bit 0 clear) the golem goes to the won (+0x131 set: +0x18 / +0x1c) or the lost (+0x20 / +0x24) phase and step
// with the blend +0x28. BUG(original): no null test of the sequence.
void CKGolemPhaseQTE::Update(IKTime* /*clock*/) {
    m_unk14 = Golem()->GetDamageTakenSinceMark();
    const CKHkSequenceMgr* sequence = static_cast<const CKHkSequenceMgr*>(m_unk08);
    if ((sequence->m_unkD4 & 1u) != 0) return;
    if (sequence->m_unk131 != 0) {
        Golem()->PhaseManager()->SwitchToPhase(static_cast<uint32_t>(m_unk18), static_cast<uint32_t>(m_unk1c), m_unk28);
        return;
    }
    Golem()->PhaseManager()->SwitchToPhase(static_cast<uint32_t>(m_unk20), static_cast<uint32_t>(m_unk24), m_unk28);
}

// 0x004be008 CKGolemPhaseQTE_vf58: the sequence aborted when this phase listens to it.
void CKGolemPhaseQTE::Stop() { static_cast<CKHkSequenceMgr*>(m_unk08)->AbortForOwner(this); }

// 0x004bdfc8 / 0x004bdf90 / 0x004bdf50 / 0x004bdf10: the golem's total damage less a mark (+0x0c, +0x10, +0x14).
int32_t CKGolemPhaseQTE::GetDamageSincePhaseStart() { return Golem()->GetTotalDamageTaken() - m_unk0c; }
void CKGolemPhaseQTE::MarkDamageBaseline() { m_unk0c = Golem()->GetTotalDamageTaken(); }
int32_t CKGolemPhaseQTE::GetDamageSinceMark2() { return Golem()->GetTotalDamageTaken() - m_unk10; }
int32_t CKGolemPhaseQTE::GetDamageSinceUpdate() { return Golem()->GetTotalDamageTaken() - m_unk14; }

// 0x004be2f8 CKGolemPhaseQTE_vf7C / 0x004be2e0 CKGolemPhaseQTE_vf80
float CKGolemPhaseQTE::GetStartTime() { return GolemClockTime(); }
float CKGolemPhaseQTE::GetMarkedTime() { return GolemClockTime(); }
