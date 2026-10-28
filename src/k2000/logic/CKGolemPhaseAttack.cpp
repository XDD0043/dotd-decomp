// CKGolemPhaseAttack.cpp - reconstructed original translation unit 0x4baab0-0x4bcf30 (GAME_TOC1, main_toc1), 32 functions, 30 live.
// Primary class: CKGolemPhaseAttack  key 0x97cc  category Logic  size 0x30  vtable 0xb290c8
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x4baab0  CKGolemPhaseAttack_Delete
//   [ ] 0x4bab00  CKGolemPhaseAttack_vf7C
//   [ ] 0x4bab08  CKGolemPhaseAttack_GetMarkedTime_maybe
//   [ ] 0x4bab10  RegisterCKGolemPhaseAttackClass
//   [ ] 0x4bab88  _GLOBAL__I_4bab88
//   [ ] 0x4bab98  CKGolemPhaseAttack_MarkDamageBaseline_maybe
//   [ ] 0x4babd0  CKGolemPhaseAttack_GetDamageSinceUpdate_maybe
//   [ ] 0x4bac10  CKGolemPhaseAttack_GetDamageSinceMark2_maybe
//   [ ] 0x4bac50  CKGolemPhaseAttack_GetDamageSincePhaseStart_maybe
//   [ ] 0x4bac90  CKGolemPhaseAttack_Save
//   [ ] 0x4bacb8  CKGolemPhaseAttack_RecursiveRegistration
//   [ ] 0x4bace0  CKGolemPhaseAttack_DeletingDestructor
//   [x] 0x4bad58  CKGolemPhaseAttack_Construct  [dead]
//   [ ] 0x4badb8  CKGolemPhaseAttack_Construct_2  [dead]
//   [x] 0x4bae18  CKGolemPhaseAttack_DeleteArray
//   [ ] 0x4baec0  CKGolemPhaseAttack_StartStepNoStop_maybe
//   [ ] 0x4bb028  CKGolemPhaseAttack_Update
//   [ ] 0x4bb0c8  CKGolemPhaseAttack_SwitchToStep
//   [ ] 0x4bb320  CKGolemPhaseAttack_Stop
//   [ ] 0x4bb3c0  CKGolemPhaseAttack_GetCurrentStep
//   [ ] 0x4bb3f8  CKGolemPhaseAttack_ResetPhases_maybe
//   [ ] 0x4bb6a0  CKGolemPhaseAttack_vf60
//   [ ] 0x4bb930  CKGolemPhaseAttack_MarkTime_maybe
//   [ ] 0x4bb950  CKGolemPhaseAttack_Start
//   [ ] 0x4bbbe8  CKGolemPhaseAttack_PostLoad
//   [ ] 0x4bbe48  CKGolemPhaseAttack_FreeAttackLists_maybe
//   [ ] 0x4bc080  CKGolemPhaseAttack_Destroy
//   [ ] 0x4bc1a0  CKGolemPhaseAttack_Destructor
//   [ ] 0x4bc210  CKGolemPhaseAttack_DestructBody
//   [x] 0x4bc280  CKGolemPhaseAttack_Create
//   [x] 0x4bc2f0  CKGolemPhaseAttack_CreateArray
//   [x] 0x4bc3d8  CKGolemPhaseAttack_Load
//
//   [ ] 0x9c5620  CKGolemPhaseAttack_IsKindOfClass  [inline]
//   [ ] 0x9c5658  CKGolemPhaseAttack_GetClassType  [inline]
//   [ ] 0x9c5660  CKGolemPhaseAttack_GetClassID  [inline]
#include "k2000/logic/CKGolemPhaseAttack.h"

#include "k2000/io/IKFile.h"
#include "k2000/logic/GameVector.h"

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
            ReadU32LE(file, &attack->m_unk1c);
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
            ReadU32LE(file, &attack->m_unk20);
            ReadU32LE(file, &attack->m_unk08);
            LoadConditions(&attack->m_conditions, file);
            IKFile_ReadRef(file, &attack->m_unk18);
            GameVector_Add(&step->m_attacksB, attack);
        }

        step->m_unk00 = stepRef;
        GameVector_Add(&m_steps, step);
    }
    return 1;
}
