// GolemPhaseCondAnd.h - the golem boss's phase conditions (no class keys, not IKSerializable). Original unit:
// GolemPhaseCondAnd.cpp (0x4c4f58-0x4c7410). CKHkGolem_CreatePhaseCondition (0x4beda0, the golem hooks'
// vt+0x118) makes one per type id 0..9; the CKGolemPhaseAttack Load reads them (type id, then the
// condition's own Load at vt+0x20 with type 0). No XXL2 counterpart: the names are Ghidra's (all _maybe
// inferences except the type ids) and the members keep placeholder names. Minimal for C2.1: constructors,
// Loads and the factory.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"

class IKFile;
class IKSerializable;

// The common base: vtable at +0x00 (10 slots +0x00..+0x24 in every condition vtable; +0x08..+0x1c and
// +0x24 not ported), the type id at +0x04 (set by each constructor, read again by each Load).
class GolemPhaseCond {
public:
    virtual ~GolemPhaseCond() {}                               // vt+0x00 / +0x04
    virtual void Load(IKFile* file, int32_t type) = 0;         // vt+0x20 (reads only for type 0)

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

    uint32_t m_unk08;  // +0x08 not read by the Load (_maybe: the start time, see InvalidateStart)
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
};
DOTD_ASSERT_SIZE(GolemPhaseCondType1, 0x8);

// Type 2 (vtable 0xb295a8, size 0xc).
class GolemPhaseCondType2 : public GolemPhaseCond {
public:
    GolemPhaseCondType2();  // 0x004c4fe8 GolemPhaseCondType2_Construct
    void Load(IKFile* file, int32_t type) override;  // vt+0x20 0x004c6928 GolemPhaseCondType2_Load

    IKSerializable* m_unk08;  // +0x08 object reference (file: key 0x2d82)
};
DOTD_ASSERT_SIZE(GolemPhaseCondType2, 0xc);
DOTD_ASSERT_OFFSET(GolemPhaseCondType2, m_unk08, 0x08);

// Type 3 (vtable 0xb29568, size 0x18).
class GolemPhaseCondition : public GolemPhaseCond {  // _maybe
public:
    GolemPhaseCondition();  // 0x004c5088 GolemPhaseCondition_Construct_maybe
    void Load(IKFile* file, int32_t type) override;  // vt+0x20 0x004c7240 GolemPhaseCondition_Load_maybe

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
    void Load(IKFile* file, int32_t type) override;  // vt+0x20 0x004c7150 GolemPhaseCondAnd_Load_maybe

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

    IKSerializable* m_unk08;  // +0x08 object reference
};
DOTD_ASSERT_SIZE(GolemPhaseCondHeroActivator, 0xc);
DOTD_ASSERT_OFFSET(GolemPhaseCondHeroActivator, m_unk08, 0x08);

// Type 6 (vtable 0xb294a8, size 0xc).
class GolemPhaseCondRandom : public GolemPhaseCond {  // _maybe
public:
    GolemPhaseCondRandom();  // 0x004c5ac0 GolemPhaseCondRandom_Construct_maybe
    void Load(IKFile* file, int32_t type) override;  // vt+0x20 0x004c6f60 GolemPhaseCondRandom_Load_maybe

    float m_unk08;  // +0x08 (constructor 100.0f; _maybe a percentage)
};
DOTD_ASSERT_SIZE(GolemPhaseCondRandom, 0xc);
DOTD_ASSERT_OFFSET(GolemPhaseCondRandom, m_unk08, 0x08);

// Type 7 (vtable 0xb29428, size 0x1c).
class GolemPhaseCondTriggerProp : public GolemPhaseCond {  // _maybe
public:
    GolemPhaseCondTriggerProp();  // 0x004c6278 GolemPhaseCondTriggerProp_Construct_maybe
    void Load(IKFile* file, int32_t type) override;  // vt+0x20 0x004c6c80 GolemPhaseCondTriggerProp_Load_maybe

    IKSerializable* m_unk08;  // +0x08 object reference (file: key 0x2d82)
    uint32_t m_unk0c;         // +0x0c (file: 0)
    uint32_t m_unk10;         // +0x10 (file: 4)
    uint32_t m_unk14;         // +0x14 not read by the Load
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

    int32_t m_unk08;  // +0x08 (constructor 1)
};
DOTD_ASSERT_SIZE(GolemPhaseCondCounter, 0xc);
DOTD_ASSERT_OFFSET(GolemPhaseCondCounter, m_unk08, 0x08);

// Type 9 (vtable 0xb293e8, size 0x10).
class GolemPhaseCondType9 : public GolemPhaseCond {
public:
    GolemPhaseCondType9();  // 0x004c5a18 GolemPhaseCondType9_Construct
    void Load(IKFile* file, int32_t type) override;  // vt+0x20 0x004c6800 GolemPhaseCondType9_Load

    uint32_t m_unk08;  // +0x08 (constructor 0)
    float m_unk0c;     // +0x0c (constructor 100.0f)
};
DOTD_ASSERT_SIZE(GolemPhaseCondType9, 0x10);
DOTD_ASSERT_OFFSET(GolemPhaseCondType9, m_unk08, 0x08);
DOTD_ASSERT_OFFSET(GolemPhaseCondType9, m_unk0c, 0x0c);
