// GolemPhaseCondAnd.cpp - reconstructed original translation unit 0x4c4f58-0x4c7410 (GAME_TOC1, main_toc1), 121 functions, 105 live.
// Primary owner: GolemPhaseCondAnd (not a registered class)
// Other owners: GolemPhaseCondition (8), GolemPhaseCondHeroActivator (8), GolemPhaseCondCounter (8), GolemPhaseCondType9 (8), GolemPhaseCondTriggerProp (7), GolemPhaseCondRandom (7), GolemPhaseCondTimer (6)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x4c4f58  GolemPhaseCondTimer_InvalidateStart_maybe
//   [ ] 0x4c4f70  KStub_Nop_4c4f70
//   [ ] 0x4c4f78  KStub_Nop_4c4f78
//   [ ] 0x4c4f80  KStub_Nop_4c4f80
//   [ ] 0x4c4f88  KStub_Nop_4c4f88
//   [ ] 0x4c4f90  KStub_Nop_4c4f90
//   [ ] 0x4c4f98  KStub_Nop_4c4f98
//   [ ] 0x4c4fa0  GolemPhaseCondType1_IsMet_maybe
//   [x] 0x4c4fe8  GolemPhaseCondType2_Construct
//   [ ] 0x4c5008  KStub_Nop_4c5008
//   [ ] 0x4c5010  KStub_Nop_4c5010
//   [ ] 0x4c5018  KStub_Nop_4c5018
//   [ ] 0x4c5020  KStub_Nop_4c5020
//   [ ] 0x4c5028  GolemPhaseCondType2_IsMet_maybe
//   [x] 0x4c5088  GolemPhaseCondition_Construct_maybe
//   [ ] 0x4c50a8  KStub_Nop_4c50a8
//   [ ] 0x4c50b0  KStub_Nop_4c50b0
//   [ ] 0x4c50b8  KStub_Nop_4c50b8
//   [ ] 0x4c50c0  GolemPhaseCondition_vf14
//   [ ] 0x4c50d0  GolemPhaseCondition_vf18
//   [ ] 0x4c50e0  KStub_Nop_4c50e0
//   [ ] 0x4c50e8  GolemPhaseCondition_vf30
//   [ ] 0x4c50f8  GolemPhaseCondAnd_vf08
//   [ ] 0x4c51b0  GolemPhaseCondAnd_vf0C
//   [ ] 0x4c5240  GolemPhaseCondAnd_vf10
//   [ ] 0x4c52d0  GolemPhaseCondAnd_vf14
//   [ ] 0x4c5348  GolemPhaseCondAnd_vf18
//   [ ] 0x4c53c0  KStub_Nop_4c53c0
//   [ ] 0x4c53c8  GolemPhaseCondAnd_IsMet_maybe
//   [ ] 0x4c5470  GolemPhaseCondAnd_ResetBaseline_maybe
//   [ ] 0x4c54f8  GolemPhaseCondAnd_vf30
//   [ ] 0x4c5570  KStub_Nop_4c5570
//   [ ] 0x4c5578  KStub_Nop_4c5578
//   [ ] 0x4c5580  KStub_Nop_4c5580
//   [ ] 0x4c5588  KStub_Nop_4c5588
//   [ ] 0x4c5590  KStub_Nop_4c5590
//   [ ] 0x4c5598  KStub_Nop_4c5598
//   [ ] 0x4c55a0  GolemPhaseCondHeroActivator_IsMet_maybe
//   [ ] 0x4c55c8  KStub_Nop_4c55c8
//   [ ] 0x4c55d0  KStub_Nop_4c55d0
//   [ ] 0x4c55d8  KStub_Nop_4c55d8
//   [ ] 0x4c55e0  KStub_Nop_4c55e0
//   [ ] 0x4c55e8  KStub_Nop_4c55e8
//   [ ] 0x4c55f0  KStub_Nop_4c55f0
//   [ ] 0x4c55f8  KStub_Nop_4c55f8
//   [ ] 0x4c5600  KStub_Nop_4c5600
//   [ ] 0x4c5608  KStub_Nop_4c5608
//   [ ] 0x4c5610  KStub_Nop_4c5610
//   [ ] 0x4c5618  KStub_Nop_4c5618
//   [ ] 0x4c5620  KStub_Nop_4c5620
//   [ ] 0x4c5628  KStub_Nop_4c5628
//   [ ] 0x4c5630  KStub_Nop_4c5630
//   [ ] 0x4c5638  KStub_Nop_4c5638
//   [ ] 0x4c5640  GolemPhaseCondCounter_Init_maybe
//   [ ] 0x4c5650  GolemPhaseCondCounter_IsMet_maybe
//   [ ] 0x4c56b8  KStub_Nop_4c56b8
//   [ ] 0x4c56c0  KStub_Nop_4c56c0
//   [ ] 0x4c56c8  KStub_Nop_4c56c8
//   [ ] 0x4c56d0  KStub_Nop_4c56d0
//   [ ] 0x4c56d8  KStub_Nop_4c56d8
//   [ ] 0x4c56e0  KStub_Nop_4c56e0
//   [ ] 0x4c56e8  GolemPhaseCondTriggerProp_IsMet_maybe
//   [ ] 0x4c5798  KStub_Nop_4c5798
//   [ ] 0x4c57a0  KStub_Nop_4c57a0
//   [ ] 0x4c57a8  KStub_Nop_4c57a8
//   [ ] 0x4c57b0  KStub_Nop_4c57b0
//   [ ] 0x4c57b8  GolemPhaseCondType9_Init
//   [ ] 0x4c57c8  GolemPhaseCondRandom_IsMet_maybe
//   [ ] 0x4c5838  GolemPhaseCondHeroActivator_ResetBaseline_maybe
//   [ ] 0x4c5868  GolemPhaseCondType9_IsMet_maybe
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
//   [ ] 0x4c5b40  GolemPhaseCondition_ResetBaseline_maybe
//   [ ] 0x4c5cd8  GolemPhaseCondition_IsMet_maybe
//   [ ] 0x4c5e90  GolemPhaseCondTimer_ResetBaseline_maybe
//   [ ] 0x4c6038  GolemPhaseCondTimer_IsMet_maybe
//   [x] 0x4c6278  GolemPhaseCondTriggerProp_Construct_maybe
//   [ ] 0x4c6290  GolemPhaseCondAnd_Construct_2_maybe  [dead]
//   [x] 0x4c6320  GolemPhaseCondAnd_Construct_maybe
//   [ ] 0x4c63b0  FUN_004c63b0  [dead]
//   [ ] 0x4c63c0  GolemPhaseCondCounter_DeletingDestructor_maybe
//   [ ] 0x4c63f0  GolemPhaseCondCounter_Destructor_maybe
//   [ ] 0x4c6400  GolemPhaseCondCounter_Destructor_2_maybe  [dead]
//   [ ] 0x4c6410  GolemPhaseCondRandom_DeletingDestructor_maybe
//   [ ] 0x4c6440  GolemPhaseCondRandom_Destructor_maybe
//   [ ] 0x4c6450  GolemPhaseCondRandom_Destructor_2_maybe  [dead]
//   [ ] 0x4c6460  GolemPhaseCondHeroActivator_DeletingDestructor_maybe
//   [ ] 0x4c6490  GolemPhaseCondHeroActivator_Destructor_maybe
//   [ ] 0x4c64a0  GolemPhaseCondHeroActivator_Destructor_2_maybe  [dead]
//   [ ] 0x4c64b0  GolemPhaseCondAnd_DeletingDestructor_maybe
//   [ ] 0x4c6568  GolemPhaseCondAnd_Destructor_maybe
//   [ ] 0x4c6608  GolemPhaseCondAnd_Destructor_2_maybe  [dead]
//   [ ] 0x4c66a8  GolemPhaseCondType9_DeletingDestructor
//   [ ] 0x4c66d8  GolemPhaseCondType9_Destructor
//   [ ] 0x4c66e8  GolemPhaseCondType9_Destructor_2  [dead]
//   [ ] 0x4c66f8  GolemPhaseCondTriggerProp_DeletingDestructor_maybe
//   [ ] 0x4c6728  GolemPhaseCondTriggerProp_Destructor_maybe
//   [ ] 0x4c6738  GolemPhaseCondTriggerProp_Init_maybe
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

#include "k2000/core/IKSerializable.h"
#include "k2000/io/IKFile.h"

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
