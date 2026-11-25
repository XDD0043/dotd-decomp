// GolemPhaseCondAnd.h - the golem boss's phase conditions (no class keys, not IKSerializable). Original unit:
// GolemPhaseCondAnd.cpp (0x4c4f58-0x4c7410). CKHkGolem_CreatePhaseCondition (0x4beda0, the golem hooks'
// vt+0x118) makes one per type id 0..9; the CKGolemPhaseAttack Load reads them (type id, then the
// condition's own Load at vt+0x20 with type 0). No XXL2 counterpart: the names are Ghidra's (all _maybe
// inferences except the type ids) and the members keep placeholder names. Minimal for C2.1: constructors,
// Loads and the factory.
#pragma once
#include <cstdint>

#include "k2000/core/IKInfo.h"
#include "k2000/core/Layout.h"

class IKFile;
class IKSerializable;

class CKGolemAttackCommon;

// The common base: vtable at +0x00 (13 slots +0x00..+0x30 in every condition vtable), the type id at +0x04 (set by
// each constructor, read again by each Load). The attack's step lists (CKGolemAttackCommon_AdvanceStepsList58 /
// 5C) ask IsMet (vt+0x28) and, for the chosen entry, ResetBaseline (vt+0x2c); the attack's Update runs Update
// (vt+0x08), its StartAttack OnStart (vt+0x0c), the phase's ResetPhases / vf60 OnPhaseReset (vt+0x14) / OnPhaseVf60
// (vt+0x18), the phase's PostLoad Init (vt+0x24). The slots a type leaves empty are KStub_Nop / KStub_Return1.
class GolemPhaseCond {
public:
    virtual ~GolemPhaseCond() {}                               // vt+0x00 / +0x04
    virtual void Update(float /*dt*/) {}                       // vt+0x08 (the attack's Update: the frame time)
    virtual void OnStart() {}                                  // vt+0x0c (CKGolemAttackCommon_StartAttack)
    virtual void Vf10() {}                                     // vt+0x10 (no caller found)
    virtual void OnPhaseReset() {}                             // vt+0x14 (CKGolemPhaseAttack_ResetPhases_maybe)
    virtual void OnPhaseVf60() {}                              // vt+0x18 (CKGolemPhaseAttack_vf60)
    virtual void Vf1C() {}                                     // vt+0x1c (no caller found)
    virtual void Load(IKFile* file, int32_t type) = 0;         // vt+0x20 (reads only for type 0)
    virtual int32_t Init(int32_t /*type*/) { return 1; }       // vt+0x24 0x9c5830 KStub_Return1 (CKGolemPhaseAttack_PostLoad)
    virtual uint8_t IsMet(CKGolemAttackCommon* attack) = 0;    // vt+0x28
    virtual void ResetBaseline(CKGolemAttackCommon* /*attack*/) {}  // vt+0x2c 0x9c5838 KStub_Nop
    virtual void Vf30() {}                                     // vt+0x30 0x9c5840 KStub_Nop

    // 0x004beda0 CKHkGolem_CreatePhaseCondition: OperatorNew + the condition's constructor; null for an
    // unknown id. In the original a virtual of the golem hook (vt+0x118, the same function in CKHkGolem,
    // CKHkS08DragonCityGolem and CKHkS08DragonCityGolemTail); it does not use the hook.
    static GolemPhaseCond* Create(uint32_t id);

    uint32_t m_type;  // +0x04 type id (the factory's id)
};

// Type 0 (vtable 0xb29628, size 0x18).
class GolemPhaseCondTimer : public GolemPhaseCond {  // _maybe: a timer
public:
    GolemPhaseCondTimer();  // 0x004c59e8 GolemPhaseCondTimer_Construct_maybe
    void Load(IKFile* file, int32_t type) override;  // vt+0x20 0x004c6ab0 GolemPhaseCondTimer_Load_maybe
    // vt+0x14 0x004c4f58 GolemPhaseCondTimer_InvalidateStart_maybe: no baseline (-FLT_MAX, 0x00c4acb8 +0x28 negated).
    void OnPhaseReset() override;
    uint8_t IsMet(CKGolemAttackCommon* attack) override;         // vt+0x28 0x004c6038 GolemPhaseCondTimer_IsMet_maybe
    void ResetBaseline(CKGolemAttackCommon* attack) override;   // vt+0x2c 0x004c5e90 GolemPhaseCondTimer_ResetBaseline_maybe

    float m_unk08;     // +0x08 not read by the Load: the baseline time (-FLT_MAX: none; ResetBaseline / InvalidateStart)
    float m_unk0c;     // +0x0c (file: 0.5 .. 15.0)
    uint8_t m_unk10;   // +0x10
    uint8_t m_unk11;   // +0x11
    uint8_t m_unk12;   // +0x12
    uint8_t m_unk13;   // +0x13
    uint8_t m_unk14;   // +0x14 (+0x15..+0x17 padding)
};
DOTD_ASSERT_SIZE(GolemPhaseCondTimer, 0x18);
DOTD_ASSERT_OFFSET(GolemPhaseCondTimer, m_type, 0x04);
DOTD_ASSERT_OFFSET(GolemPhaseCondTimer, m_unk0c, 0x0c);
DOTD_ASSERT_OFFSET(GolemPhaseCondTimer, m_unk10, 0x10);
DOTD_ASSERT_OFFSET(GolemPhaseCondTimer, m_unk14, 0x14);

// Type 1 (vtable 0xb295e8, size 0x8).
class GolemPhaseCondType1 : public GolemPhaseCond {
public:
    GolemPhaseCondType1();  // 0x004c59b8 GolemPhaseCondType1_Construct
    void Load(IKFile* file, int32_t type) override;  // vt+0x20 0x004c6a40 GolemPhaseCondType1_Load
    uint8_t IsMet(CKGolemAttackCommon* attack) override;  // vt+0x28 0x004c4fa0 GolemPhaseCondType1_IsMet_maybe
};
DOTD_ASSERT_SIZE(GolemPhaseCondType1, 0x8);

// Type 2 (vtable 0xb295a8, size 0xc).
class GolemPhaseCondType2 : public GolemPhaseCond {
public:
    GolemPhaseCondType2();  // 0x004c4fe8 GolemPhaseCondType2_Construct
    void Load(IKFile* file, int32_t type) override;  // vt+0x20 0x004c6928 GolemPhaseCondType2_Load
    uint8_t IsMet(CKGolemAttackCommon* attack) override;  // vt+0x28 0x004c5028 GolemPhaseCondType2_IsMet_maybe

    IKSerializable* m_unk08;  // +0x08 object reference (file: key 0x2d82)
};
DOTD_ASSERT_SIZE(GolemPhaseCondType2, 0xc);
DOTD_ASSERT_OFFSET(GolemPhaseCondType2, m_unk08, 0x08);

// Type 3 (vtable 0xb29568, size 0x18).
class GolemPhaseCondition : public GolemPhaseCond {  // _maybe
public:
    GolemPhaseCondition();  // 0x004c5088 GolemPhaseCondition_Construct_maybe
    void Load(IKFile* file, int32_t type) override;  // vt+0x20 0x004c7240 GolemPhaseCondition_Load_maybe
    void OnPhaseReset() override { m_unk0c = 0; }  // vt+0x14 0x004c50c0 GolemPhaseCondition_vf14
    void OnPhaseVf60() override { m_unk0c = 0; }   // vt+0x18 0x004c50d0 GolemPhaseCondition_vf18
    uint8_t IsMet(CKGolemAttackCommon* attack) override;         // vt+0x28 0x004c5cd8 GolemPhaseCondition_IsMet_maybe
    void ResetBaseline(CKGolemAttackCommon* attack) override;   // vt+0x2c 0x004c5b40 GolemPhaseCondition_ResetBaseline_maybe
    void Vf30() override { m_unk0c = 0; }          // vt+0x30 0x004c50e8 GolemPhaseCondition_vf30

    int32_t m_unk08;   // +0x08 (file: 300)
    uint32_t m_unk0c;  // +0x0c not read by the Load (constructor 0)
    uint8_t m_unk10;   // +0x10 the bytes are read in the order +10, +12, +11, (+08), +13, +14
    uint8_t m_unk11;   // +0x11
    uint8_t m_unk12;   // +0x12
    uint8_t m_unk13;   // +0x13
    uint8_t m_unk14;   // +0x14 (+0x15..+0x17 padding)
};
DOTD_ASSERT_SIZE(GolemPhaseCondition, 0x18);
DOTD_ASSERT_OFFSET(GolemPhaseCondition, m_unk08, 0x08);
DOTD_ASSERT_OFFSET(GolemPhaseCondition, m_unk0c, 0x0c);
DOTD_ASSERT_OFFSET(GolemPhaseCondition, m_unk10, 0x10);
DOTD_ASSERT_OFFSET(GolemPhaseCondition, m_unk14, 0x14);

// Type 4 (vtable 0xb29528, size 0x10): owns a type-3 and a type-2 condition, made by its constructor.
class GolemPhaseCondAnd : public GolemPhaseCond {  // _maybe: both must hold
public:
    GolemPhaseCondAnd();  // 0x004c6320 GolemPhaseCondAnd_Construct_maybe
    // 0x004c6568 GolemPhaseCondAnd_Destructor_maybe (0x4c64b0 deleting): the two sub-conditions deleted (vt+0x04),
    // +0x08 first, then the base (vtable only).
    ~GolemPhaseCondAnd() override;
    void Load(IKFile* file, int32_t type) override;  // vt+0x20 0x004c7150 GolemPhaseCondAnd_Load_maybe
    // The slots pass on to both sub-conditions: +0x0c first, then +0x08 (vt+0x08 / +0x0c / +0x10 test them for null,
    // the others do not; vt+0x14 / +0x18 take +0x08 first).
    void Update(float dt) override;      // vt+0x08 0x004c50f8 GolemPhaseCondAnd_vf08
    void OnStart() override;             // vt+0x0c 0x004c51b0 GolemPhaseCondAnd_vf0C
    void Vf10() override;                // vt+0x10 0x004c5240 GolemPhaseCondAnd_vf10
    void OnPhaseReset() override;        // vt+0x14 0x004c52d0 GolemPhaseCondAnd_vf14
    void OnPhaseVf60() override;         // vt+0x18 0x004c5348 GolemPhaseCondAnd_vf18
    uint8_t IsMet(CKGolemAttackCommon* attack) override;         // vt+0x28 0x004c53c8 GolemPhaseCondAnd_IsMet_maybe
    void ResetBaseline(CKGolemAttackCommon* attack) override;   // vt+0x2c 0x004c5470 GolemPhaseCondAnd_ResetBaseline_maybe
    void Vf30() override;                // vt+0x30 0x004c54f8 GolemPhaseCondAnd_vf30

    GolemPhaseCondition* m_unk08;  // +0x08 OperatorNew(0x18), type 3
    GolemPhaseCondType2* m_unk0c;  // +0x0c OperatorNew(0xc), type 2
};
DOTD_ASSERT_SIZE(GolemPhaseCondAnd, 0x10);
DOTD_ASSERT_OFFSET(GolemPhaseCondAnd, m_unk08, 0x08);
DOTD_ASSERT_OFFSET(GolemPhaseCondAnd, m_unk0c, 0x0c);

// Type 5 (vtable 0xb294e8, size 0xc).
class GolemPhaseCondHeroActivator : public GolemPhaseCond {  // _maybe
public:
    GolemPhaseCondHeroActivator();  // 0x004c5b00 GolemPhaseCondHeroActivator_Construct_maybe
    void Load(IKFile* file, int32_t type) override;  // vt+0x20 0x004c7038 GolemPhaseCondHeroActivator_Load_maybe
    uint8_t IsMet(CKGolemAttackCommon* attack) override;  // vt+0x28 0x004c55a0 GolemPhaseCondHeroActivator_IsMet_maybe
    // vt+0x2c 0x004c5838 GolemPhaseCondHeroActivator_ResetBaseline_maybe: CKHkHeroActivator_CallSetEnabled(0).
    void ResetBaseline(CKGolemAttackCommon* attack) override;

    IKSerializable* m_unk08;  // +0x08 object reference
};
DOTD_ASSERT_SIZE(GolemPhaseCondHeroActivator, 0xc);
DOTD_ASSERT_OFFSET(GolemPhaseCondHeroActivator, m_unk08, 0x08);

// Type 6 (vtable 0xb294a8, size 0xc).
class GolemPhaseCondRandom : public GolemPhaseCond {  // _maybe
public:
    GolemPhaseCondRandom();  // 0x004c5ac0 GolemPhaseCondRandom_Construct_maybe
    void Load(IKFile* file, int32_t type) override;  // vt+0x20 0x004c6f60 GolemPhaseCondRandom_Load_maybe
    uint8_t IsMet(CKGolemAttackCommon* attack) override;  // vt+0x28 0x004c57c8 GolemPhaseCondRandom_IsMet_maybe (rand)

    float m_unk08;  // +0x08 (constructor 100.0f; _maybe a percentage)
};
DOTD_ASSERT_SIZE(GolemPhaseCondRandom, 0xc);
DOTD_ASSERT_OFFSET(GolemPhaseCondRandom, m_unk08, 0x08);

// Type 7 (vtable 0xb29428, size 0x1c).
class GolemPhaseCondTriggerProp : public GolemPhaseCond {  // _maybe
public:
    GolemPhaseCondTriggerProp();  // 0x004c6278 GolemPhaseCondTriggerProp_Construct_maybe
    void Load(IKFile* file, int32_t type) override;  // vt+0x20 0x004c6c80 GolemPhaseCondTriggerProp_Load_maybe
    int32_t Init(int32_t type) override;  // vt+0x24 0x004c6738 GolemPhaseCondTriggerProp_Init_maybe
    uint8_t IsMet(CKGolemAttackCommon* attack) override;  // vt+0x28 0x004c56e8 GolemPhaseCondTriggerProp_IsMet_maybe

    IKSerializable* m_unk08;  // +0x08 object reference (file: key 0x2d82)
    uint32_t m_unk0c;         // +0x0c (file: 0)
    // +0x10 the value id (file: 4) until Init asks the object's GetInfo (vt+0x40, request 0) for its accessor; then the
    // accessor (a PS3 member-function pointer: the descriptor here, the this-adjustment +0x14).
    union {
        uint32_t m_unk10;
        InfoAccessor m_pfnAccessor;
    };
    uint32_t m_unk14;         // +0x14 not read by the Load: the accessor's this-adjustment (Init: 0)
    uint8_t m_unk18;          // +0x18 (+0x19..+0x1b padding)
};
DOTD_ASSERT_SIZE(GolemPhaseCondTriggerProp, 0x1c);
DOTD_ASSERT_OFFSET(GolemPhaseCondTriggerProp, m_unk08, 0x08);
DOTD_ASSERT_OFFSET(GolemPhaseCondTriggerProp, m_unk0c, 0x0c);
DOTD_ASSERT_OFFSET(GolemPhaseCondTriggerProp, m_unk10, 0x10);
DOTD_ASSERT_OFFSET(GolemPhaseCondTriggerProp, m_unk18, 0x18);

// Type 8 (vtable 0xb29468, size 0xc).
class GolemPhaseCondCounter : public GolemPhaseCond {  // _maybe
public:
    GolemPhaseCondCounter();  // 0x004c5a80 GolemPhaseCondCounter_Construct_maybe
    void Load(IKFile* file, int32_t type) override;  // vt+0x20 0x004c6e88 GolemPhaseCondCounter_Load_maybe
    int32_t Init(int32_t /*type*/) override { m_type = 8; return 1; }  // vt+0x24 0x004c5640 GolemPhaseCondCounter_Init_maybe
    uint8_t IsMet(CKGolemAttackCommon* attack) override;  // vt+0x28 0x004c5650 GolemPhaseCondCounter_IsMet_maybe

    int32_t m_unk08;  // +0x08 (constructor 1)
};
DOTD_ASSERT_SIZE(GolemPhaseCondCounter, 0xc);
DOTD_ASSERT_OFFSET(GolemPhaseCondCounter, m_unk08, 0x08);

// Type 9 (vtable 0xb293e8, size 0x10).
class GolemPhaseCondType9 : public GolemPhaseCond {
public:
    GolemPhaseCondType9();  // 0x004c5a18 GolemPhaseCondType9_Construct
    void Load(IKFile* file, int32_t type) override;  // vt+0x20 0x004c6800 GolemPhaseCondType9_Load
    int32_t Init(int32_t /*type*/) override { m_type = 9; return 1; }  // vt+0x24 0x004c57b8 GolemPhaseCondType9_Init
    uint8_t IsMet(CKGolemAttackCommon* attack) override;  // vt+0x28 0x004c5868 GolemPhaseCondType9_IsMet_maybe

    uint32_t m_unk08;  // +0x08 (constructor 0)
    float m_unk0c;     // +0x0c (constructor 100.0f)
};
DOTD_ASSERT_SIZE(GolemPhaseCondType9, 0x10);
DOTD_ASSERT_OFFSET(GolemPhaseCondType9, m_unk08, 0x08);
DOTD_ASSERT_OFFSET(GolemPhaseCondType9, m_unk0c, 0x0c);
