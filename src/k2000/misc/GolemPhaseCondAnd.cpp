// GolemPhaseCondAnd.cpp - reconstructed original translation unit 0x4c4f58-0x4c7410 (GAME_TOC1, main_toc1), 121 functions, 105 live.
// Primary owner: GolemPhaseCondAnd (not a registered class)
// Other owners: GolemPhaseCondition (8), GolemPhaseCondHeroActivator (8), GolemPhaseCondCounter (8), GolemPhaseCondType9 (8), GolemPhaseCondTriggerProp (7), GolemPhaseCondRandom (7), GolemPhaseCondTimer (6)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x4c4f58  GolemPhaseCondTimer_InvalidateStart_maybe
//   [x] 0x4c4f70  KStub_Nop_4c4f70
//   [x] 0x4c4f78  KStub_Nop_4c4f78
//   [x] 0x4c4f80  KStub_Nop_4c4f80
//   [x] 0x4c4f88  KStub_Nop_4c4f88
//   [x] 0x4c4f90  KStub_Nop_4c4f90
//   [x] 0x4c4f98  KStub_Nop_4c4f98
//   [x] 0x4c4fa0  GolemPhaseCondType1_IsMet_maybe
//   [x] 0x4c4fe8  GolemPhaseCondType2_Construct
//   [x] 0x4c5008  KStub_Nop_4c5008
//   [x] 0x4c5010  KStub_Nop_4c5010
//   [x] 0x4c5018  KStub_Nop_4c5018
//   [x] 0x4c5020  KStub_Nop_4c5020
//   [x] 0x4c5028  GolemPhaseCondType2_IsMet_maybe
//   [x] 0x4c5088  GolemPhaseCondition_Construct_maybe
//   [x] 0x4c50a8  KStub_Nop_4c50a8
//   [x] 0x4c50b0  KStub_Nop_4c50b0
//   [x] 0x4c50b8  KStub_Nop_4c50b8
//   [x] 0x4c50c0  GolemPhaseCondition_vf14
//   [x] 0x4c50d0  GolemPhaseCondition_vf18
//   [x] 0x4c50e0  KStub_Nop_4c50e0
//   [x] 0x4c50e8  GolemPhaseCondition_vf30
//   [x] 0x4c50f8  GolemPhaseCondAnd_vf08
//   [x] 0x4c51b0  GolemPhaseCondAnd_vf0C
//   [x] 0x4c5240  GolemPhaseCondAnd_vf10
//   [x] 0x4c52d0  GolemPhaseCondAnd_vf14
//   [x] 0x4c5348  GolemPhaseCondAnd_vf18
//   [x] 0x4c53c0  KStub_Nop_4c53c0
//   [x] 0x4c53c8  GolemPhaseCondAnd_IsMet_maybe
//   [x] 0x4c5470  GolemPhaseCondAnd_ResetBaseline_maybe
//   [x] 0x4c54f8  GolemPhaseCondAnd_vf30
//   [x] 0x4c5570  KStub_Nop_4c5570
//   [x] 0x4c5578  KStub_Nop_4c5578
//   [x] 0x4c5580  KStub_Nop_4c5580
//   [x] 0x4c5588  KStub_Nop_4c5588
//   [x] 0x4c5590  KStub_Nop_4c5590
//   [x] 0x4c5598  KStub_Nop_4c5598
//   [x] 0x4c55a0  GolemPhaseCondHeroActivator_IsMet_maybe
//   [x] 0x4c55c8  KStub_Nop_4c55c8
//   [x] 0x4c55d0  KStub_Nop_4c55d0
//   [x] 0x4c55d8  KStub_Nop_4c55d8
//   [x] 0x4c55e0  KStub_Nop_4c55e0
//   [x] 0x4c55e8  KStub_Nop_4c55e8
//   [x] 0x4c55f0  KStub_Nop_4c55f0
//   [x] 0x4c55f8  KStub_Nop_4c55f8
//   [x] 0x4c5600  KStub_Nop_4c5600
//   [x] 0x4c5608  KStub_Nop_4c5608
//   [x] 0x4c5610  KStub_Nop_4c5610
//   [x] 0x4c5618  KStub_Nop_4c5618
//   [x] 0x4c5620  KStub_Nop_4c5620
//   [x] 0x4c5628  KStub_Nop_4c5628
//   [x] 0x4c5630  KStub_Nop_4c5630
//   [x] 0x4c5638  KStub_Nop_4c5638
//   [x] 0x4c5640  GolemPhaseCondCounter_Init_maybe
//   [x] 0x4c5650  GolemPhaseCondCounter_IsMet_maybe
//   [x] 0x4c56b8  KStub_Nop_4c56b8
//   [x] 0x4c56c0  KStub_Nop_4c56c0
//   [x] 0x4c56c8  KStub_Nop_4c56c8
//   [x] 0x4c56d0  KStub_Nop_4c56d0
//   [x] 0x4c56d8  KStub_Nop_4c56d8
//   [x] 0x4c56e0  KStub_Nop_4c56e0
//   [x] 0x4c56e8  GolemPhaseCondTriggerProp_IsMet_maybe
//   [x] 0x4c5798  KStub_Nop_4c5798
//   [x] 0x4c57a0  KStub_Nop_4c57a0
//   [x] 0x4c57a8  KStub_Nop_4c57a8
//   [x] 0x4c57b0  KStub_Nop_4c57b0
//   [x] 0x4c57b8  GolemPhaseCondType9_Init
//   [x] 0x4c57c8  GolemPhaseCondRandom_IsMet_maybe
//   [x] 0x4c5838  GolemPhaseCondHeroActivator_ResetBaseline_maybe
//   [x] 0x4c5868  GolemPhaseCondType9_IsMet_maybe
//   [ ] 0x4c5978  GolemPhaseCondition_Construct_2_maybe  [dead]
//   [ ] 0x4c5998  GolemPhaseCondType2_Construct_2  [dead]
//   [x] 0x4c59b8  GolemPhaseCondType1_Construct
//   [ ] 0x4c59d0  GolemPhaseCondType1_Construct_2  [dead]
//   [x] 0x4c59e8  GolemPhaseCondTimer_Construct_maybe
//   [ ] 0x4c5a00  GolemPhaseCondTimer_Construct_2_maybe  [dead]
//   [x] 0x4c5a18  GolemPhaseCondType9_Construct
//   [ ] 0x4c5a40  GolemPhaseCondType9_Construct_2  [dead]
//   [ ] 0x4c5a68  GolemPhaseCondTriggerProp_Construct_2_maybe  [dead]
//   [x] 0x4c5a80  GolemPhaseCondCounter_Construct_maybe
//   [ ] 0x4c5aa0  GolemPhaseCondCounter_Construct_2_maybe  [dead]
//   [x] 0x4c5ac0  GolemPhaseCondRandom_Construct_maybe
//   [ ] 0x4c5ae0  GolemPhaseCondRandom_Construct_2_maybe  [dead]
//   [x] 0x4c5b00  GolemPhaseCondHeroActivator_Construct_maybe
//   [ ] 0x4c5b20  GolemPhaseCondHeroActivator_Construct_2_maybe  [dead]
//   [x] 0x4c5b40  GolemPhaseCondition_ResetBaseline_maybe
//   [x] 0x4c5cd8  GolemPhaseCondition_IsMet_maybe
//   [x] 0x4c5e90  GolemPhaseCondTimer_ResetBaseline_maybe
//   [x] 0x4c6038  GolemPhaseCondTimer_IsMet_maybe
//   [x] 0x4c6278  GolemPhaseCondTriggerProp_Construct_maybe
//   [ ] 0x4c6290  GolemPhaseCondAnd_Construct_2_maybe  [dead]
//   [x] 0x4c6320  GolemPhaseCondAnd_Construct_maybe
//   [ ] 0x4c63b0  FUN_004c63b0  [dead]
//   [x] 0x4c63c0  GolemPhaseCondCounter_DeletingDestructor_maybe  (the deleting form of the implicit destructor)
//   [x] 0x4c63f0  GolemPhaseCondCounter_Destructor_maybe  (C++ destructor chain: vtable stores only)
//   [ ] 0x4c6400  GolemPhaseCondCounter_Destructor_2_maybe  [dead]
//   [x] 0x4c6410  GolemPhaseCondRandom_DeletingDestructor_maybe  (the deleting form of the implicit destructor)
//   [x] 0x4c6440  GolemPhaseCondRandom_Destructor_maybe  (C++ destructor chain: vtable stores only)
//   [ ] 0x4c6450  GolemPhaseCondRandom_Destructor_2_maybe  [dead]
//   [x] 0x4c6460  GolemPhaseCondHeroActivator_DeletingDestructor_maybe  (the deleting form of the implicit destructor)
//   [x] 0x4c6490  GolemPhaseCondHeroActivator_Destructor_maybe  (C++ destructor chain: vtable stores only)
//   [ ] 0x4c64a0  GolemPhaseCondHeroActivator_Destructor_2_maybe  [dead]
//   [x] 0x4c64b0  GolemPhaseCondAnd_DeletingDestructor_maybe  (the deleting form of GolemPhaseCondAnd's destructor)
//   [x] 0x4c6568  GolemPhaseCondAnd_Destructor_maybe
//   [ ] 0x4c6608  GolemPhaseCondAnd_Destructor_2_maybe  [dead]
//   [x] 0x4c66a8  GolemPhaseCondType9_DeletingDestructor  (the deleting form of the implicit destructor)
//   [x] 0x4c66d8  GolemPhaseCondType9_Destructor  (C++ destructor chain: vtable stores only)
//   [ ] 0x4c66e8  GolemPhaseCondType9_Destructor_2  [dead]
//   [x] 0x4c66f8  GolemPhaseCondTriggerProp_DeletingDestructor_maybe
//   [x] 0x4c6728  GolemPhaseCondTriggerProp_Destructor_maybe  (C++ destructor chain: vtable stores only)
//   [x] 0x4c6738  GolemPhaseCondTriggerProp_Init_maybe
//   [x] 0x4c6800  GolemPhaseCondType9_Load
//   [x] 0x4c6928  GolemPhaseCondType2_Load
//   [x] 0x4c6a40  GolemPhaseCondType1_Load
//   [x] 0x4c6ab0  GolemPhaseCondTimer_Load_maybe
//   [x] 0x4c6c80  GolemPhaseCondTriggerProp_Load_maybe
//   [x] 0x4c6e88  GolemPhaseCondCounter_Load_maybe
//   [x] 0x4c6f60  GolemPhaseCondRandom_Load_maybe
//   [x] 0x4c7038  GolemPhaseCondHeroActivator_Load_maybe
//   [x] 0x4c7150  GolemPhaseCondAnd_Load_maybe
//   [x] 0x4c7240  GolemPhaseCondition_Load_maybe
//
//   [ ] 0x9c5888  GolemPhaseCondition_Destructor_maybe  [inline]
//   [ ] 0x9c5898  GolemPhaseCondTimer_DeletingDestructor_maybe  [inline]
//   [ ] 0x9c58c8  GolemPhaseCondType2_DeletingDestructor  [inline]
//   [ ] 0x9c58f8  GolemPhaseCondType2_Destructor  [inline]
//   [ ] 0x9c5908  GolemPhaseCondition_DeletingDestructor_maybe  [inline]
//   [ ] 0x9c5938  GolemPhaseCondTimer_Destructor_maybe  [inline]
//   [ ] 0x9c5948  GolemPhaseCondType1_DeletingDestructor  [inline]
//   [ ] 0x9c5978  GolemPhaseCondType1_Destructor  [inline]
#include "k2000/misc/GolemPhaseCondAnd.h"

#include "k2000/ai/CKHkDetectorGroup.h"
#include "k2000/core/IKSerializable.h"
#include "k2000/hooks/CKHkGolem.h"
#include "k2000/hooks/CKHkHeroActivator.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKGolemAttackCommon.h"
#include "k2000/logic/CKGolemPhaseManager.h"
#include "k2000/misc/CKGolemPhaseBase.h"
#include "k2000/misc/ClassRegistry.h"
#include "platform/fps.h"

// 0x004beda0 CKHkGolem_CreatePhaseCondition (CKHkGolem.cpp's unit; kept here until CKHkGolem is ported, the
// golem hook's vt+0x118 is this function in every golem hook class): OperatorNew(size) + the constructor.
// The id tests are made in the order 0, 1, 2, 3, 4, 5, 6, 8, 7, 9.
GolemPhaseCond* GolemPhaseCond::Create(uint32_t id) {
    if (id == 0) return new GolemPhaseCondTimer();
    if (id == 1) return new GolemPhaseCondType1();
    if (id == 2) return new GolemPhaseCondType2();
    if (id == 3) return new GolemPhaseCondition();
    if (id == 4) return new GolemPhaseCondAnd();
    if (id == 5) return new GolemPhaseCondHeroActivator();
    if (id == 6) return new GolemPhaseCondRandom();
    if (id == 8) return new GolemPhaseCondCounter();
    if (id == 7) return new GolemPhaseCondTriggerProp();
    if (id == 9) return new GolemPhaseCondType9();
    return nullptr;
}

// 0x004c59e8 GolemPhaseCondTimer_Construct_maybe
GolemPhaseCondTimer::GolemPhaseCondTimer() { m_type = 0; }

// 0x004c59b8 GolemPhaseCondType1_Construct
GolemPhaseCondType1::GolemPhaseCondType1() { m_type = 1; }

// 0x004c4fe8 GolemPhaseCondType2_Construct
GolemPhaseCondType2::GolemPhaseCondType2() {
    m_unk08 = nullptr;
    m_type = 2;
}

// 0x004c5088 GolemPhaseCondition_Construct_maybe
GolemPhaseCondition::GolemPhaseCondition() {
    m_unk0c = 0;
    m_type = 3;
}

// 0x004c6568 GolemPhaseCondAnd_Destructor_maybe (0x004c64b0 GolemPhaseCondAnd_DeletingDestructor_maybe)
GolemPhaseCondAnd::~GolemPhaseCondAnd() {
    if (m_unk08 != nullptr) delete m_unk08;  // vt+0x04
    if (m_unk0c != nullptr) delete m_unk0c;  // vt+0x04
}

// 0x004c6320 GolemPhaseCondAnd_Construct_maybe: the two sub-conditions' constructors are inlined.
GolemPhaseCondAnd::GolemPhaseCondAnd() {
    m_type = 4;
    m_unk08 = new GolemPhaseCondition();
    m_unk0c = new GolemPhaseCondType2();
}

// 0x004c5b00 GolemPhaseCondHeroActivator_Construct_maybe
GolemPhaseCondHeroActivator::GolemPhaseCondHeroActivator() {
    m_unk08 = nullptr;
    m_type = 5;
}

// 0x004c5ac0 GolemPhaseCondRandom_Construct_maybe
GolemPhaseCondRandom::GolemPhaseCondRandom() {
    m_unk08 = 100.0f;  // 0x42c80000
    m_type = 6;
}

// 0x004c6278 GolemPhaseCondTriggerProp_Construct_maybe
GolemPhaseCondTriggerProp::GolemPhaseCondTriggerProp() { m_type = 7; }

// 0x004c5a80 GolemPhaseCondCounter_Construct_maybe
GolemPhaseCondCounter::GolemPhaseCondCounter() {
    m_unk08 = 1;
    m_type = 8;
}

// 0x004c5a18 GolemPhaseCondType9_Construct
GolemPhaseCondType9::GolemPhaseCondType9() {
    m_unk0c = 100.0f;  // 0x42c80000
    m_type = 9;
    m_unk08 = 0;
}

// 0x004c6800 GolemPhaseCondType9_Load
void GolemPhaseCondType9::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return;
    ReadU32LE(file, &m_type);
    ReadU32LE(file, &m_unk08);
    ReadF32LE(file, &m_unk0c);
}

// 0x004c6928 GolemPhaseCondType2_Load
void GolemPhaseCondType2::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return;
    ReadU32LE(file, &m_type);
    IKFile_ReadRef(file, &m_unk08);
}

// 0x004c6a40 GolemPhaseCondType1_Load
void GolemPhaseCondType1::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return;
    ReadU32LE(file, &m_type);
}

// 0x004c6ab0 GolemPhaseCondTimer_Load_maybe: the duration before the type id, then five bytes.
void GolemPhaseCondTimer::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return;
    ReadF32LE(file, &m_unk0c);
    ReadU32LE(file, &m_type);
    ReadU8(file, &m_unk10);
    ReadU8(file, &m_unk11);
    ReadU8(file, &m_unk12);
    ReadU8(file, &m_unk13);
    ReadU8(file, &m_unk14);
}

// 0x004c6c80 GolemPhaseCondTriggerProp_Load_maybe: one word is read into a stack temporary and dropped.
void GolemPhaseCondTriggerProp::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return;
    ReadU32LE(file, &m_type);
    IKFile_ReadRef(file, &m_unk08);
    ReadU32LE(file, &m_unk0c);
    ReadU32LE(file, &m_unk10);
    uint32_t unused = 0;
    ReadU32LE(file, &unused);
    ReadU8(file, &m_unk18);
}

// 0x004c6e88 GolemPhaseCondCounter_Load_maybe
void GolemPhaseCondCounter::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return;
    ReadU32LE(file, &m_type);
    ReadS32LE(file, &m_unk08);
}

// 0x004c6f60 GolemPhaseCondRandom_Load_maybe
void GolemPhaseCondRandom::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return;
    ReadU32LE(file, &m_type);
    ReadF32LE(file, &m_unk08);
}

// 0x004c7038 GolemPhaseCondHeroActivator_Load_maybe
void GolemPhaseCondHeroActivator::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return;
    ReadU32LE(file, &m_type);
    IKFile_ReadRef(file, &m_unk08);
}

// 0x004c7150 GolemPhaseCondAnd_Load_maybe: the type id, then the +0x0c condition's Load, then the +0x08 one's
// (both through vt+0x20, type 0).
void GolemPhaseCondAnd::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return;
    ReadU32LE(file, &m_type);
    m_unk0c->Load(file, 0);
    m_unk08->Load(file, 0);
}

// 0x004c7240 GolemPhaseCondition_Load_maybe
void GolemPhaseCondition::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return;
    ReadU32LE(file, &m_type);
    ReadU8(file, &m_unk10);
    ReadU8(file, &m_unk12);
    ReadU8(file, &m_unk11);
    ReadS32LE(file, &m_unk08);
    ReadU8(file, &m_unk13);
    ReadU8(file, &m_unk14);
}

// ---- C2.8: the conditions' run-time slots ----

namespace {
// -FLT_MAX (0x00c4acb8 +0x28 negated, fneg): the timers' "no baseline".
constexpr float kNoBaseline = -3.40282347e+38f;
CKHkGolem* GolemOf(CKGolemAttackCommon* attack) { return attack->Golem(); }
CKGolemPhaseBase* CurrentPhaseOf(CKGolemAttackCommon* attack) {
    return static_cast<CKGolemPhaseBase*>(GolemOf(attack)->PhaseManager()->GetCurrentPhase());  // 0x004bd330
}
}  // namespace

// 0x004c4f58 GolemPhaseCondTimer_InvalidateStart_maybe
void GolemPhaseCondTimer::OnPhaseReset() { m_unk08 = kNoBaseline; }

// 0x004c6038 GolemPhaseCondTimer_IsMet_maybe: the time since a baseline (fsubs) not less than the duration +0x0c (fcmpu
// + cror: a NaN fails). +0x10: the golem's times (+0x13: since +0x50; else since +0x54, or, with a baseline of its own,
// +0x54 since it); +0x12: the attack's (+0x13: since its marked time; else since its start time, or the start time
// since the baseline); +0x11: the current phase's likewise (vt+0x80 / vt+0x7c); none: never. "Now" is the clock's.
uint8_t GolemPhaseCondTimer::IsMet(CKGolemAttackCommon* attack) {
    float now = GolemClockTime();
    float since;
    if (m_unk10 != 0) {
        CKHkGolem* golem = GolemOf(attack);
        if (m_unk13 != 0) {
            since = golem->GetTime50();  // 0x004becb0
        } else if (m_unk08 == kNoBaseline) {
            since = golem->GetTime54();  // 0x004becb8
        } else {
            now = golem->GetTime54();
            since = m_unk08;
        }
    } else if (m_unk12 != 0) {
        if (m_unk13 != 0) {
            since = attack->GetMarkedTime();  // vt+0x98
        } else if (m_unk08 == kNoBaseline) {
            since = attack->GetStartTime();  // vt+0x94
        } else {
            now = attack->GetStartTime();
            since = m_unk08;
        }
    } else if (m_unk11 != 0) {
        if (m_unk13 != 0) {
            since = CurrentPhaseOf(attack)->GetMarkedTime();  // vt+0x80
        } else if (m_unk08 == kNoBaseline) {
            since = CurrentPhaseOf(attack)->GetStartTime();  // vt+0x7c
        } else {
            now = CurrentPhaseOf(attack)->GetStartTime();
            since = m_unk08;
        }
    } else {
        return 0;
    }
    const float elapsed = now - since;
    return elapsed >= m_unk0c ? 1 : 0;
}

// 0x004c5e90 GolemPhaseCondTimer_ResetBaseline_maybe: without +0x14 no baseline; else the source's time (+0x13: the
// source marks its own time instead): the golem's +0x54, the attack's start time, the current phase's start time.
void GolemPhaseCondTimer::ResetBaseline(CKGolemAttackCommon* attack) {
    if (m_unk14 == 0) {
        m_unk08 = kNoBaseline;
        return;
    }
    if (m_unk10 != 0) {
        if (m_unk13 == 0) {
            m_unk08 = GolemOf(attack)->GetTime54();
            return;
        }
        GolemOf(attack)->SetTime54ToNow();  // 0x004bf9f8
        return;
    }
    if (m_unk12 != 0) {
        if (m_unk13 == 0) {
            m_unk08 = attack->GetStartTime();  // vt+0x94
        } else {
            attack->MarkTime();  // vt+0x9c
        }
        return;
    }
    if (m_unk11 != 0) {
        if (m_unk13 == 0) {
            m_unk08 = CurrentPhaseOf(attack)->GetStartTime();  // vt+0x7c
        } else {
            CurrentPhaseOf(attack)->MarkTime();  // vt+0x84
        }
    }
}

// 0x004c4fa0 GolemPhaseCondType1_IsMet_maybe: the attack's animation reached its end (vt+0x7c).
uint8_t GolemPhaseCondType1::IsMet(CKGolemAttackCommon* attack) { return attack->IsAnimEnded(); }

// 0x004c5028 GolemPhaseCondType2_IsMet_maybe: the detector group's vt+0xc0 (0x9ccff0: +0x4c bit 0); 0 without one.
uint8_t GolemPhaseCondType2::IsMet(CKGolemAttackCommon* /*attack*/) {
    if (m_unk08 == nullptr) return 0;
    return static_cast<uint8_t>(static_cast<CKHkDetectorGroup*>(m_unk08)->m_unk4C[0] & 1u);
}

// 0x004c5cd8 GolemPhaseCondition_IsMet_maybe: a damage count (unsigned) not below +0x08. +0x10: the golem's (+0x14:
// since its mark; else its total since the baseline +0x0c); +0x12: the attack's (+0x14: since its start mark, vt+0x80;
// else since its start, vt+0x88); +0x11: the current phase's (+0x14: since its start, vt+0x6c; else since its second
// mark, vt+0x74); none: never.
uint8_t GolemPhaseCondition::IsMet(CKGolemAttackCommon* attack) {
    uint32_t count;
    if (m_unk10 != 0) {
        if (m_unk14 != 0) {
            count = static_cast<uint32_t>(GolemOf(attack)->GetDamageTakenSinceMark());  // 0x004bec68
        } else {
            count = static_cast<uint32_t>(GolemOf(attack)->GetTotalDamageTaken() - static_cast<int32_t>(m_unk0c));
        }
    } else if (m_unk12 != 0) {
        count = static_cast<uint32_t>(m_unk14 != 0 ? attack->GetDamageSinceStartMark()  // vt+0x80
                                                   : attack->GetDamageSinceStart());    // vt+0x88
    } else if (m_unk11 != 0) {
        CKGolemPhaseBase* phase = CurrentPhaseOf(attack);
        count = static_cast<uint32_t>(m_unk14 != 0 ? phase->GetDamageSincePhaseStart()  // vt+0x6c
                                                   : phase->GetDamageSinceMark2());     // vt+0x74
    } else {
        return 0;
    }
    return static_cast<uint32_t>(m_unk08) <= count ? 1 : 0;
}

// 0x004c5b40 GolemPhaseCondition_ResetBaseline_maybe: without +0x13 the baseline 0; else the source's damage (+0x14:
// the source marks its own instead): the golem's total, the attack's count since its start (vt+0x88; vt+0x84 marks),
// the current phase's since its second mark (vt+0x74; vt+0x70 marks).
void GolemPhaseCondition::ResetBaseline(CKGolemAttackCommon* attack) {
    if (m_unk13 == 0) {
        m_unk0c = 0;
        return;
    }
    if (m_unk10 != 0) {
        if (m_unk14 == 0) {
            m_unk0c = static_cast<uint32_t>(GolemOf(attack)->GetTotalDamageTaken());
            return;
        }
        GolemOf(attack)->MarkDamageTaken();  // 0x004bec88
        return;
    }
    if (m_unk12 != 0) {
        if (m_unk14 == 0) {
            m_unk0c = static_cast<uint32_t>(attack->GetDamageSinceStart());  // vt+0x88
        } else {
            attack->MarkDamageStart();  // vt+0x84
        }
        return;
    }
    if (m_unk11 != 0) {
        if (m_unk14 == 0) {
            m_unk0c = static_cast<uint32_t>(CurrentPhaseOf(attack)->GetDamageSinceMark2());  // vt+0x74
        } else {
            CurrentPhaseOf(attack)->MarkDamageBaseline();  // vt+0x70
        }
    }
}

// 0x004c50f8 GolemPhaseCondAnd_vf08
void GolemPhaseCondAnd::Update(float dt) {
    if (m_unk0c != nullptr) m_unk0c->Update(dt);
    if (m_unk08 != nullptr) m_unk08->Update(dt);
}

// 0x004c51b0 GolemPhaseCondAnd_vf0C
void GolemPhaseCondAnd::OnStart() {
    if (m_unk0c != nullptr) m_unk0c->OnStart();
    if (m_unk08 != nullptr) m_unk08->OnStart();
}

// 0x004c5240 GolemPhaseCondAnd_vf10
void GolemPhaseCondAnd::Vf10() {
    if (m_unk0c != nullptr) m_unk0c->Vf10();
    if (m_unk08 != nullptr) m_unk08->Vf10();
}

// 0x004c52d0 GolemPhaseCondAnd_vf14
void GolemPhaseCondAnd::OnPhaseReset() {
    m_unk08->OnPhaseReset();
    m_unk0c->OnPhaseReset();
}

// 0x004c5348 GolemPhaseCondAnd_vf18
void GolemPhaseCondAnd::OnPhaseVf60() {
    m_unk08->OnPhaseVf60();
    m_unk0c->OnPhaseVf60();
}

// 0x004c53c8 GolemPhaseCondAnd_IsMet_maybe: the detector condition (+0x0c) first, then the damage one (+0x08).
uint8_t GolemPhaseCondAnd::IsMet(CKGolemAttackCommon* attack) {
    if (m_unk0c->IsMet(attack) == 0) return 0;
    return m_unk08->IsMet(attack) != 0 ? 1 : 0;
}

// 0x004c5470 GolemPhaseCondAnd_ResetBaseline_maybe
void GolemPhaseCondAnd::ResetBaseline(CKGolemAttackCommon* attack) {
    m_unk0c->ResetBaseline(attack);
    m_unk08->ResetBaseline(attack);
}

// 0x004c54f8 GolemPhaseCondAnd_vf30
void GolemPhaseCondAnd::Vf30() {
    m_unk0c->Vf30();
    m_unk08->Vf30();
}

// 0x004c55a0 GolemPhaseCondHeroActivator_IsMet_maybe: the activator's bit array (+0x0c) bit 10; 0 without one.
uint8_t GolemPhaseCondHeroActivator::IsMet(CKGolemAttackCommon* /*attack*/) {
    if (m_unk08 == nullptr) return 0;
    return static_cast<uint8_t>((static_cast<IKLife*>(m_unk08)->m_bitArray >> 10) & 1u);
}

// 0x004c5838 GolemPhaseCondHeroActivator_ResetBaseline_maybe: the activator switched off (li r4,0 at 0x4c5840, then
// CKHkHeroActivator_CallSetEnabled). Used by LVL050's golem[3] (phase attack 11, step 15, before its two QTE phases).
void GolemPhaseCondHeroActivator::ResetBaseline(CKGolemAttackCommon* /*attack*/) {
    CKHkHeroActivator_CallSetEnabled(m_unk08, 0);
}

// 0x004c57c8 GolemPhaseCondRandom_IsMet_maybe: one draw (Rand_Int 0x00011500, its low 16 bits: fcfid, frsp) as a
// percentage (/ 65535.0, x 100.0: TOC +0x6760 / +0x6764) not above +0x08 (fcmpu + cror: a NaN fails).
uint8_t GolemPhaseCondRandom::IsMet(CKGolemAttackCommon* /*attack*/) {
    if (dotd::fps::Unlocked()) {
        // --fps N (not in the original): the condition is evaluated every update, so roll once per 60 Hz frame (none in
        // a displayed frame that ends no 60 Hz frame) to keep the chance per second of 60 fps.
        uint8_t met = 0;
        for (int32_t i = 0; i < dotd::fps::Ticks(); ++i) {
            const float roll = static_cast<float>(static_cast<double>(static_cast<uint32_t>(Rand_Int()) & 0xffffu)) / 65535.0f * 100.0f;
            if (roll <= m_unk08) met = 1;
        }
        return met;
    }
    const float roll = static_cast<float>(static_cast<double>(static_cast<uint32_t>(Rand_Int()) & 0xffffu)) / 65535.0f * 100.0f;
    return roll <= m_unk08 ? 1 : 0;
}

// 0x004c6738 GolemPhaseCondTriggerProp_Init_maybe: for the level data, the object's accessor of value +0x10 (GetInfo,
// request 0) replaces the id (+0x10 / +0x14: the member-function pointer). The type id 7 either way.
int32_t GolemPhaseCondTriggerProp::Init(int32_t type) {
    if (type == 0) {
        IKInfo info;
        info.m_ui32Id = m_unk10;
        m_unk08->GetInfo(&info, kGetInfoValueAccessor);  // vt+0x40
        m_pfnAccessor = info.m_pfnAccessor;
        m_unk14 = 0;
    }
    m_type = 7;
    return 1;
}

// 0x004c56e8 GolemPhaseCondTriggerProp_IsMet_maybe: the object's value (the accessor with +0x0c) equal to +0x18 in its
// low byte; 0 without an object.
uint8_t GolemPhaseCondTriggerProp::IsMet(CKGolemAttackCommon* /*attack*/) {
    if (m_unk08 == nullptr) return 0;
    const uint32_t value = m_pfnAccessor(m_unk08, m_unk0c);
    return ((value ^ m_unk18) & 0xffu) == 0 ? 1 : 0;
}

// 0x004c5650 GolemPhaseCondCounter_IsMet_maybe: the attack's animation loops (vt+0x90) not below +0x08 (unsigned).
uint8_t GolemPhaseCondCounter::IsMet(CKGolemAttackCommon* attack) {
    return static_cast<uint32_t>(m_unk08) <= attack->GetAnimLoopCount() ? 1 : 0;
}

// 0x004c5868 GolemPhaseCondType9_IsMet_maybe: the golem's health percentage (+0x8c / +0x88 x 100.0, the integers as
// floats: fcfid / frsp) against +0x0c by the comparison +0x08: 0 above, 1 not below, 2 below, 3 not above, 4 equal.
uint8_t GolemPhaseCondType9::IsMet(CKGolemAttackCommon* attack) {
    CKHkGolem* golem = GolemOf(attack);
    const float health = static_cast<float>(static_cast<double>(static_cast<int64_t>(golem->m_i32Health)));
    const float maximum = static_cast<float>(static_cast<double>(static_cast<int64_t>(golem->m_i32MaxHealth)));
    const float percent = health / maximum * 100.0f;
    switch (m_unk08) {
    case 0: return m_unk0c < percent ? 1 : 0;
    case 1: return percent >= m_unk0c ? 1 : 0;
    case 2: return percent < m_unk0c ? 1 : 0;
    case 3: return percent <= m_unk0c ? 1 : 0;
    case 4: return percent == m_unk0c ? 1 : 0;
    default: return 0;
    }
}
