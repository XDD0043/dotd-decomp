// CKGolemPhaseAttack.cpp - reconstructed original translation unit 0x4baab0-0x4bcf30 (GAME_TOC1, main_toc1), 32 functions, 30 live.
// Primary class: CKGolemPhaseAttack  key 0x97cc  category Logic  size 0x30  vtable 0xb290c8
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x4baab0  CKGolemPhaseAttack_Delete
//   [x] 0x4bab00  CKGolemPhaseAttack_vf7C
//   [x] 0x4bab08  CKGolemPhaseAttack_GetMarkedTime_maybe
//   [ ] 0x4bab10  RegisterCKGolemPhaseAttackClass
//   [ ] 0x4bab88  _GLOBAL__I_4bab88
//   [x] 0x4bab98  CKGolemPhaseAttack_MarkDamageBaseline_maybe
//   [x] 0x4babd0  CKGolemPhaseAttack_GetDamageSinceUpdate_maybe
//   [x] 0x4bac10  CKGolemPhaseAttack_GetDamageSinceMark2_maybe
//   [x] 0x4bac50  CKGolemPhaseAttack_GetDamageSincePhaseStart_maybe
//   [ ] 0x4bac90  CKGolemPhaseAttack_Save
//   [x] 0x4bacb8  CKGolemPhaseAttack_RecursiveRegistration  (inherited: KBase978C_vf24)
//   [x] 0x4bace0  CKGolemPhaseAttack_DeletingDestructor  (the same as 0x4bc1a0 CKGolemPhaseAttack_Destructor)
//   [x] 0x4bad58  CKGolemPhaseAttack_Construct  [dead]
//   [ ] 0x4badb8  CKGolemPhaseAttack_Construct_2  [dead]
//   [x] 0x4bae18  CKGolemPhaseAttack_DeleteArray
//   [x] 0x4baec0  CKGolemPhaseAttack_StartStepNoStop_maybe
//   [x] 0x4bb028  CKGolemPhaseAttack_Update
//   [x] 0x4bb0c8  CKGolemPhaseAttack_SwitchToStep
//   [x] 0x4bb320  CKGolemPhaseAttack_Stop
//   [x] 0x4bb3c0  CKGolemPhaseAttack_GetCurrentStep
//   [x] 0x4bb3f8  CKGolemPhaseAttack_ResetPhases_maybe
//   [x] 0x4bb6a0  CKGolemPhaseAttack_vf60
//   [x] 0x4bb930  CKGolemPhaseAttack_MarkTime_maybe
//   [x] 0x4bb950  CKGolemPhaseAttack_Start
//   [x] 0x4bbbe8  CKGolemPhaseAttack_PostLoad
//   [x] 0x4bbe48  CKGolemPhaseAttack_FreeAttackLists_maybe
//   [x] 0x4bc080  CKGolemPhaseAttack_Destroy
//   [x] 0x4bc1a0  CKGolemPhaseAttack_Destructor
//   [x] 0x4bc210  CKGolemPhaseAttack_DestructBody  (the same as 0x4bc1a0 CKGolemPhaseAttack_Destructor)
//   [x] 0x4bc280  CKGolemPhaseAttack_Create
//   [x] 0x4bc2f0  CKGolemPhaseAttack_CreateArray
//   [x] 0x4bc3d8  CKGolemPhaseAttack_Load
//
//   [ ] 0x9c5620  CKGolemPhaseAttack_IsKindOfClass  [inline]
//   [ ] 0x9c5658  CKGolemPhaseAttack_GetClassType  [inline]
//   [ ] 0x9c5660  CKGolemPhaseAttack_GetClassID  [inline]
#include "k2000/logic/CKGolemPhaseAttack.h"

#include "k2000/io/IKFile.h"
#include "k2000/hooks/CKHkGolem.h"
#include "k2000/logic/GameVector.h"
#include "k2000/memory/Mem.h"

namespace {

// The inlined condition list of CKGolemPhaseAttack_Load: a count, a fresh one-entry block, then per entry
// a condition id (-1: no condition, a null entry) made by the golem hook's CreatePhaseCondition (vt+0x118;
// GolemPhaseCond::Create here, as long as the hooks are not ported) and loaded with type 0 (vt+0x20).
void LoadConditions(TVector<GolemPhaseCond*, 1>* list, IKFile* file) {
    uint32_t count = 0;
    ReadU32LE(file, &count);
    GameVector_Allocate(list, 1);
    for (uint32_t i = 0; i < count; ++i) {
        uint32_t id = 0;
        ReadU32LE(file, &id);
        GolemPhaseCond* condition = nullptr;
        if (id != 0xffffffffu) {
            condition = GolemPhaseCond::Create(id);
            condition->Load(file, 0);  // BUG(original): no null test for an unknown id
        }
        GameVector_Add(list, condition);
    }
}

}  // namespace

// 0x004bc3d8 CKGolemPhaseAttack_Load: CKGolemPhaseBase's data, then (level data only) a word and the steps.
// BUG(original): each list gets a fresh block without freeing the old one or resetting its length.
int32_t CKGolemPhaseAttack::Load(IKFile* file, int32_t type) {
    CKGolemPhaseBase::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadU32LE(file, &m_unk18);
    uint32_t stepCount = 0;
    ReadU32LE(file, &stepCount);
    GameVector_Allocate(&m_steps, 1);
    for (uint32_t s = 0; s < stepCount; ++s) {
        Step* step = new Step;  // OperatorNew(0x1c), the two lists empty with capacity 1
        step->m_attacksA.m_pBlock = nullptr;
        step->m_attacksA.m_ui32NbUsedElt = 0;
        step->m_attacksA.m_ui32NbElt = 1;
        step->m_attacksB.m_ui32NbUsedElt = 0;
        step->m_attacksB.m_pBlock = nullptr;
        step->m_attacksB.m_ui32NbElt = 1;
        IKSerializable* stepRef = nullptr;
        IKFile_ReadRef(file, &stepRef);

        uint32_t count = 0;
        ReadU32LE(file, &count);
        GameVector_Allocate(&step->m_attacksA, 1);
        for (uint32_t i = 0; i < count; ++i) {
            AttackA* attack = new AttackA;  // OperatorNew(0x20)
            attack->m_conditions.m_pBlock = nullptr;
            attack->m_conditions.m_ui32NbUsedElt = 0;
            attack->m_conditions.m_ui32NbElt = 1;
            ReadU32LE(file, &attack->m_unk00);
            ReadU32LE(file, &attack->m_unk04);
            ReadU8(file, &attack->m_unk18);
            ReadU8(file, &attack->m_unk19);
            ReadS32LE(file, &attack->m_unk1c);
            LoadConditions(&attack->m_conditions, file);
            IKFile_ReadRef(file, &attack->m_unk14);
            GameVector_Add(&step->m_attacksA, attack);
        }

        count = 0;
        ReadU32LE(file, &count);
        GameVector_Allocate(&step->m_attacksB, 1);
        for (uint32_t i = 0; i < count; ++i) {
            AttackB* attack = new AttackB;  // OperatorNew(0x24)
            attack->m_conditions.m_ui32NbUsedElt = 0;
            attack->m_conditions.m_pBlock = nullptr;
            attack->m_conditions.m_ui32NbElt = 1;
            ReadU32LE(file, &attack->m_unk00);
            ReadU32LE(file, &attack->m_unk04);
            ReadU8(file, &attack->m_unk1c);
            ReadU8(file, &attack->m_unk1d);
            ReadS32LE(file, &attack->m_unk20);
            ReadF32LE(file, &attack->m_unk08);
            LoadConditions(&attack->m_conditions, file);
            IKFile_ReadRef(file, &attack->m_unk18);
            GameVector_Add(&step->m_attacksB, attack);
        }

        step->m_unk00 = static_cast<CKGolemAttackCommon*>(stepRef);
        GameVector_Add(&m_steps, step);
    }
    return 1;
}

// ---- C2.8: the phase at run time ----

// 0x004bbbe8 CKGolemPhaseAttack_PostLoad: for the level no current step (-1); every condition of every record gets
// Init (vt+0x24) with the type. BUG(original): no null test (a condition id -1 would crash; LVL010 has none).
int32_t CKGolemPhaseAttack::PostLoad(int32_t type) {
    if (type == 0) m_unk14 = 0xffffffffu;
    for (uint32_t s = 0; s < m_steps.m_ui32NbUsedElt; ++s) {
        for (uint32_t i = 0; i < m_steps.m_pBlock[s]->m_attacksA.m_ui32NbUsedElt; ++i) {
            AttackA* record = m_steps.m_pBlock[s]->m_attacksA.m_pBlock[i];
            for (uint32_t c = 0; c < record->m_conditions.m_ui32NbUsedElt; ++c) record->m_conditions.m_pBlock[c]->Init(type);
        }
        for (uint32_t i = 0; i < m_steps.m_pBlock[s]->m_attacksB.m_ui32NbUsedElt; ++i) {
            AttackB* record = m_steps.m_pBlock[s]->m_attacksB.m_pBlock[i];
            for (uint32_t c = 0; c < record->m_conditions.m_ui32NbUsedElt; ++c) record->m_conditions.m_pBlock[c]->Init(type);
        }
    }
    return 1;
}

// 0x004bb028 CKGolemPhaseAttack_Update: the golem's damage since its mark kept (+0x24); the current step's attack
// updates (vt+0x60).
void CKGolemPhaseAttack::Update(IKTime* clock) {
    m_unk24 = Golem()->GetDamageTakenSinceMark();  // 0x004bec68
    if (m_unk14 < m_steps.m_ui32NbUsedElt) m_steps.m_pBlock[m_unk14]->m_unk00->Update(clock);
}

// 0x004bb950 CKGolemPhaseAttack_Start: without a current step the first one (+0x18) becomes current and its attack
// gets the step's lists (vt+0x70 / +0x74), the blend 0 (vt+0x78, TOC +0x65f4) and starts (vt+0x50). Then the damage
// marks, every record opened (+0x19 / +0x1d = 0) and the start time.
void CKGolemPhaseAttack::Start() {
    if (m_unk14 == 0xffffffffu) {
        m_unk14 = m_unk18;
        Step* step = m_steps.m_pBlock[m_unk18];
        step->m_unk00->SetStepListA(&step->m_attacksA);
        step = m_steps.m_pBlock[m_unk14];
        step->m_unk00->SetStepListB(&step->m_attacksB);
        m_steps.m_pBlock[m_unk14]->m_unk00->SetBlendTime(0.0f);
        m_steps.m_pBlock[m_unk14]->m_unk00->StartAttack();
    }
    m_unk1c = Golem()->GetTotalDamageTaken();  // 0x004bec80
    m_unk20 = Golem()->GetTotalDamageTaken();
    for (uint32_t s = 0; s < m_steps.m_ui32NbUsedElt; ++s) {
        for (uint32_t i = 0; i < m_steps.m_pBlock[s]->m_attacksA.m_ui32NbUsedElt; ++i) {
            m_steps.m_pBlock[s]->m_attacksA.m_pBlock[i]->m_unk19 = 0;
        }
        for (uint32_t i = 0; i < m_steps.m_pBlock[s]->m_attacksB.m_ui32NbUsedElt; ++i) {
            m_steps.m_pBlock[s]->m_attacksB.m_pBlock[i]->m_unk1d = 0;
        }
    }
    m_unk28 = GolemClockTime();
    m_unk2c = GolemClockTime();
}

// 0x004bb0c8 CKGolemPhaseAttack_SwitchToStep: inside the count, the current step's attack (if any) loses its lists
// and stops (vt+0x54); the new step's attack gets its lists, the blend (vt+0x78) and starts (vt+0x50).
void CKGolemPhaseAttack::SwitchToStep(uint32_t step, float blend) {
    if (step >= m_steps.m_ui32NbUsedElt) return;
    if (m_unk14 < m_steps.m_ui32NbUsedElt) {
        m_steps.m_pBlock[m_unk14]->m_unk00->SetStepListA(nullptr);
        m_steps.m_pBlock[m_unk14]->m_unk00->SetStepListB(nullptr);
        m_steps.m_pBlock[m_unk14]->m_unk00->StopAttack();
    }
    m_unk14 = step;
    Step* s = m_steps.m_pBlock[step];
    s->m_unk00->SetStepListA(&s->m_attacksA);
    s = m_steps.m_pBlock[m_unk14];
    s->m_unk00->SetStepListB(&s->m_attacksB);
    m_steps.m_pBlock[m_unk14]->m_unk00->SetBlendTime(blend);
    m_steps.m_pBlock[m_unk14]->m_unk00->StartAttack();
}

// 0x004baec0 CKGolemPhaseAttack_StartStepNoStop_maybe: inside the count, the step's attack gets its lists, starts
// (vt+0x50) and then the blend (vt+0x78); the step becomes current whatever its index.
void CKGolemPhaseAttack::StartStepNoStop(uint32_t step, float blend) {
    if (step < m_steps.m_ui32NbUsedElt) {
        Step* s = m_steps.m_pBlock[step];
        s->m_unk00->SetStepListA(&s->m_attacksA);
        s = m_steps.m_pBlock[step];
        s->m_unk00->SetStepListB(&s->m_attacksB);
        m_steps.m_pBlock[step]->m_unk00->StartAttack();
        m_steps.m_pBlock[step]->m_unk00->SetBlendTime(blend);
    }
    m_unk14 = step;
}

// 0x004bb320 CKGolemPhaseAttack_Stop: the current step's attack stops (vt+0x54), no current step; the damage marks.
void CKGolemPhaseAttack::Stop() {
    if (m_unk14 < m_steps.m_ui32NbUsedElt) {
        m_steps.m_pBlock[m_unk14]->m_unk00->StopAttack();
        m_unk14 = 0xffffffffu;
    }
    m_unk1c = Golem()->GetTotalDamageTaken();
    m_unk20 = Golem()->GetTotalDamageTaken();
}

// 0x004bb3f8 CKGolemPhaseAttack_ResetPhases_maybe: every condition's vt+0x14, every step's attack vt+0x58
// (AttachVolumesToHotSpots); no current step.
void CKGolemPhaseAttack::ResetPhases() {
    for (uint32_t s = 0; s < m_steps.m_ui32NbUsedElt; ++s) {
        for (uint32_t i = 0; i < m_steps.m_pBlock[s]->m_attacksA.m_ui32NbUsedElt; ++i) {
            AttackA* record = m_steps.m_pBlock[s]->m_attacksA.m_pBlock[i];
            for (uint32_t c = 0; c < record->m_conditions.m_ui32NbUsedElt; ++c) {
                if (record->m_conditions.m_pBlock[c] != nullptr) record->m_conditions.m_pBlock[c]->OnPhaseReset();
            }
        }
        for (uint32_t i = 0; i < m_steps.m_pBlock[s]->m_attacksB.m_ui32NbUsedElt; ++i) {
            AttackB* record = m_steps.m_pBlock[s]->m_attacksB.m_pBlock[i];
            for (uint32_t c = 0; c < record->m_conditions.m_ui32NbUsedElt; ++c) {
                if (record->m_conditions.m_pBlock[c] != nullptr) record->m_conditions.m_pBlock[c]->OnPhaseReset();
            }
        }
    }
    for (uint32_t s = 0; s < m_steps.m_ui32NbUsedElt; ++s) m_steps.m_pBlock[s]->m_unk00->AttachVolumesToHotSpots();
    m_unk14 = 0xffffffffu;
}

// 0x004bb6a0 CKGolemPhaseAttack_vf60: every condition's vt+0x18, every step's attack vt+0x5c.
void CKGolemPhaseAttack::Vf60() {
    for (uint32_t s = 0; s < m_steps.m_ui32NbUsedElt; ++s) {
        for (uint32_t i = 0; i < m_steps.m_pBlock[s]->m_attacksA.m_ui32NbUsedElt; ++i) {
            AttackA* record = m_steps.m_pBlock[s]->m_attacksA.m_pBlock[i];
            for (uint32_t c = 0; c < record->m_conditions.m_ui32NbUsedElt; ++c) {
                if (record->m_conditions.m_pBlock[c] != nullptr) record->m_conditions.m_pBlock[c]->OnPhaseVf60();
            }
        }
        for (uint32_t i = 0; i < m_steps.m_pBlock[s]->m_attacksB.m_ui32NbUsedElt; ++i) {
            AttackB* record = m_steps.m_pBlock[s]->m_attacksB.m_pBlock[i];
            for (uint32_t c = 0; c < record->m_conditions.m_ui32NbUsedElt; ++c) {
                if (record->m_conditions.m_pBlock[c] != nullptr) record->m_conditions.m_pBlock[c]->OnPhaseVf60();
            }
        }
    }
    for (uint32_t s = 0; s < m_steps.m_ui32NbUsedElt; ++s) m_steps.m_pBlock[s]->m_unk00->Vf5C();
}

// 0x004bac50 / 0x004bab98 / 0x004bac10 / 0x004babd0: the golem's total damage less a mark (+0x1c, +0x20, +0x24).
int32_t CKGolemPhaseAttack::GetDamageSincePhaseStart() { return Golem()->GetTotalDamageTaken() - m_unk1c; }
void CKGolemPhaseAttack::MarkDamageBaseline() { m_unk1c = Golem()->GetTotalDamageTaken(); }
int32_t CKGolemPhaseAttack::GetDamageSinceMark2() { return Golem()->GetTotalDamageTaken() - m_unk20; }
int32_t CKGolemPhaseAttack::GetDamageSinceUpdate() { return Golem()->GetTotalDamageTaken() - m_unk24; }

// 0x004bb930 CKGolemPhaseAttack_MarkTime_maybe
void CKGolemPhaseAttack::MarkTime() { m_unk2c = GolemClockTime(); }

// 0x004bbe48 CKGolemPhaseAttack_FreeAttackLists_maybe (called per step by the Destroy): each record's conditions
// deleted (vt+0x04), its condition block freed and the record deleted.
static void FreeStepRecords(CKGolemPhaseAttack::Step* step) {
    for (uint32_t i = 0; i < step->m_attacksA.m_ui32NbUsedElt; ++i) {
        GolemStepA* record = step->m_attacksA.m_pBlock[i];
        for (uint32_t c = 0; c < record->m_conditions.m_ui32NbUsedElt; ++c) delete record->m_conditions.m_pBlock[c];
        if (record->m_conditions.m_pBlock != nullptr) Mem_FreeAligned16(record->m_conditions.m_pBlock);
        record->m_conditions.m_ui32NbUsedElt = 0;
        record->m_conditions.m_pBlock = nullptr;
        delete record;
    }
    for (uint32_t i = 0; i < step->m_attacksB.m_ui32NbUsedElt; ++i) {
        GolemStepB* record = step->m_attacksB.m_pBlock[i];
        for (uint32_t c = 0; c < record->m_conditions.m_ui32NbUsedElt; ++c) delete record->m_conditions.m_pBlock[c];
        if (record->m_conditions.m_pBlock != nullptr) Mem_FreeAligned16(record->m_conditions.m_pBlock);
        record->m_conditions.m_ui32NbUsedElt = 0;
        record->m_conditions.m_pBlock = nullptr;
        delete record;
    }
}
void CKGolemPhaseAttack::FreeAttackLists() {
    for (uint32_t s = 0; s < m_steps.m_ui32NbUsedElt; ++s) FreeStepRecords(m_steps.m_pBlock[s]);
}

// 0x004bc080 CKGolemPhaseAttack_Destroy: KStub_Nop_4c76d0 (the base's), then per step its records freed, its two
// record blocks freed and the step deleted.
void CKGolemPhaseAttack::Destroy() {
    for (uint32_t s = 0; s < m_steps.m_ui32NbUsedElt; ++s) {
        FreeStepRecords(m_steps.m_pBlock[s]);
        Step* step = m_steps.m_pBlock[s];
        if (step == nullptr) continue;
        if (step->m_attacksB.m_pBlock != nullptr) Mem_FreeAligned16(step->m_attacksB.m_pBlock);
        step->m_attacksB.m_ui32NbUsedElt = 0;
        step->m_attacksB.m_pBlock = nullptr;
        if (step->m_attacksA.m_pBlock != nullptr) Mem_FreeAligned16(step->m_attacksA.m_pBlock);
        step->m_attacksA.m_ui32NbUsedElt = 0;
        step->m_attacksA.m_pBlock = nullptr;
        delete step;
    }
}

// 0x004bc1a0 CKGolemPhaseAttack_Destructor: the step block freed (CKGolemPhaseBase_maybe_BaseDestructor 0x4c76d8: the
// base's vtable only).
CKGolemPhaseAttack::~CKGolemPhaseAttack() {
    if (m_steps.m_pBlock != nullptr) Mem_FreeAligned16(m_steps.m_pBlock);
    m_steps.m_ui32NbUsedElt = 0;
    m_steps.m_pBlock = nullptr;
}
