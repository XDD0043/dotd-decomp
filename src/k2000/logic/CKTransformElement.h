// CKTransformElement.h - the shared base of the element attacks (key 0x954c, vtable 0xb24888, size 0x154). Original
// unit: CKTransformElement.cpp (0x3dc3d8-0x3e0248). No XXL2 class of this name. Bases of CKEarthBoulder, CKIceSpin,
// CKWindTwister, CKElectricSphere (and CKWindBeam). The member names are the Ghidra struct's (curated from the
// attack code); the per-level arrays are indexed by the element's upgrade level (0..2).
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"

class CKTransformElement : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x255)
    DOTD_DECLARE_FACTORIES(CKTransformElement)

    CKTransformElement() {}  // 0x003dc428 CKTransformElement_Construct: stores the vtable only
    ~CKTransformElement() override {}
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x003de4f8 CKTransformElement_Load
    // vt+0x30 0x003de488 CKTransformElement_PostLoad: the run-time state reset (vt+0x6c).
    int32_t PostLoad(int32_t type) override;
    // vt+0x50 0x003dc448 CKTransformElement_GetAbilityId (the base returns 0x17; the elements override it).
    // The slots +0x54..+0x68 (GetFamilyId, Start, Stop, Update, End, ApplyHeroControl) are not ported yet.
    virtual uint8_t GetAbilityId() { return 0x17; }
    // vt+0x6c 0x003dcea0 CKTransformElement_ResetRuntime: the run-time words of the base (the elements'
    // overrides call it first).
    virtual void ResetRuntime();

    int32_t m_levelIndex;              // +0x004 (not loaded)
    int32_t m_damage[3];               // +0x008 (file: 100, 150, ...)
    float m_damageParam10[3];          // +0x014
    float m_cooldown[3];               // +0x020
    float m_cooldownForced[3];         // +0x02c
    int32_t m_manaPerSecond[3];        // +0x038
    int32_t m_manaRequired[3];         // +0x044
    float m_dmgRandBase;               // +0x050 _maybe
    float m_dmgRandRange;              // +0x054 _maybe
    float m_dmgParam2C[3];             // +0x058
    float m_dmgParam28[3];             // +0x064
    float m_dmgEffect0[3];             // +0x070
    float m_dmgEffect1[3];             // +0x07c
    float m_dmgEffect2[3];             // +0x088
    float m_dmgEffect4[3];             // +0x094
    float m_dmgEffect6[3];             // +0x0a0
    float m_dmgEffect5[3];             // +0x0ac
    float m_dmgEffect7[3];             // +0x0b8
    float m_dmgEffect3[3];             // +0x0c4
    uint8_t m_dmgFlag34[3];            // +0x0d0
    uint8_t m_dmgFlag35[3];            // +0x0d3
    uint8_t m_padD6[2];                // +0x0d6
    float m_groundFxIntervalBase;      // +0x0d8 _maybe
    float m_groundFxIntervalRange;     // +0x0dc _maybe
    float m_unkE0;                     // +0x0e0 (file: 0.5)
    uint8_t m_airPerm1Perm0TurnEnable[3];    // +0x0e4
    uint8_t m_padE7;                         // +0x0e7
    float m_airTurnAB[2];                    // +0x0e8
    uint8_t m_mode1Perm1Perm0TurnEnable[3];  // +0x0f0
    uint8_t m_padF3;                         // +0x0f3
    float m_mode1TurnAB[2];                  // +0x0f4
    float m_airMoveSpeed;                    // +0x0fc
    float m_mode1MoveSpeed;                  // +0x100
    uint8_t m_airMode1P11f8Enable[2];        // +0x104
    uint8_t m_pad106[2];                     // +0x106
    float m_airMode1P11f8[2];                // +0x108
    uint8_t m_groundPerm1Perm0TurnEnable[3]; // +0x110
    uint8_t m_pad113;                        // +0x113
    float m_groundTurnAB[2];                 // +0x114
    float m_groundMoveSpeed;                 // +0x11c
    uint8_t m_groundP11f8Enable;             // +0x120
    uint8_t m_pad121[3];                     // +0x121
    float m_groundP11f8;                     // +0x124
    IKSerializable* m_emitterFxData;   // +0x128 (reference)
    // +0x12c..+0x14b runtime state (host, flags, timers), not loaded. ResetRuntime sets every field below except
    // +0x134 (never written: heap leftovers live).
    uint32_t m_unk12c;                 // +0x12c ResetRuntime 0
    uint8_t m_unk130[4];               // +0x130 ResetRuntime 0 (four byte stores)
    uint32_t m_unk134;                 // +0x134 never written
    uint32_t m_unk138;                 // +0x138 ResetRuntime 0
    uint8_t m_unk13c;                  // +0x13c ResetRuntime 0xff
    uint8_t m_unk13d;                  // +0x13d ResetRuntime 0
    uint8_t m_pad13e[2];
    float m_unk140;                    // +0x140 ResetRuntime -1.0f (TOC +0x41ac)
    uint32_t m_unk144;                 // +0x144 ResetRuntime 0
    uint8_t m_unk148;                  // +0x148 ResetRuntime 1
    uint8_t m_pad149[3];
    IKSerializable* m_elementDamage;   // +0x14c (reference; Ghidra: CKS08ElementDamage* pDamage)
    uint8_t m_unk150[4];               // +0x150
};
DOTD_ASSERT_SIZE(CKTransformElement, 0x154);
DOTD_ASSERT_OFFSET(CKTransformElement, m_damage, 0x8);
DOTD_ASSERT_OFFSET(CKTransformElement, m_damageParam10, 0x14);
DOTD_ASSERT_OFFSET(CKTransformElement, m_cooldown, 0x20);
DOTD_ASSERT_OFFSET(CKTransformElement, m_cooldownForced, 0x2c);
DOTD_ASSERT_OFFSET(CKTransformElement, m_manaPerSecond, 0x38);
DOTD_ASSERT_OFFSET(CKTransformElement, m_manaRequired, 0x44);
DOTD_ASSERT_OFFSET(CKTransformElement, m_dmgRandBase, 0x50);
DOTD_ASSERT_OFFSET(CKTransformElement, m_dmgRandRange, 0x54);
DOTD_ASSERT_OFFSET(CKTransformElement, m_dmgParam2C, 0x58);
DOTD_ASSERT_OFFSET(CKTransformElement, m_dmgParam28, 0x64);
DOTD_ASSERT_OFFSET(CKTransformElement, m_dmgEffect0, 0x70);
DOTD_ASSERT_OFFSET(CKTransformElement, m_dmgEffect1, 0x7c);
DOTD_ASSERT_OFFSET(CKTransformElement, m_dmgEffect2, 0x88);
DOTD_ASSERT_OFFSET(CKTransformElement, m_dmgEffect4, 0x94);
DOTD_ASSERT_OFFSET(CKTransformElement, m_dmgEffect6, 0xa0);
DOTD_ASSERT_OFFSET(CKTransformElement, m_dmgEffect5, 0xac);
DOTD_ASSERT_OFFSET(CKTransformElement, m_dmgEffect7, 0xb8);
DOTD_ASSERT_OFFSET(CKTransformElement, m_dmgEffect3, 0xc4);
DOTD_ASSERT_OFFSET(CKTransformElement, m_dmgFlag34, 0xd0);
DOTD_ASSERT_OFFSET(CKTransformElement, m_dmgFlag35, 0xd3);
DOTD_ASSERT_OFFSET(CKTransformElement, m_groundFxIntervalBase, 0xd8);
DOTD_ASSERT_OFFSET(CKTransformElement, m_groundFxIntervalRange, 0xdc);
DOTD_ASSERT_OFFSET(CKTransformElement, m_unkE0, 0xe0);
DOTD_ASSERT_OFFSET(CKTransformElement, m_airPerm1Perm0TurnEnable, 0xe4);
DOTD_ASSERT_OFFSET(CKTransformElement, m_airTurnAB, 0xe8);
DOTD_ASSERT_OFFSET(CKTransformElement, m_mode1Perm1Perm0TurnEnable, 0xf0);
DOTD_ASSERT_OFFSET(CKTransformElement, m_mode1TurnAB, 0xf4);
DOTD_ASSERT_OFFSET(CKTransformElement, m_airMoveSpeed, 0xfc);
DOTD_ASSERT_OFFSET(CKTransformElement, m_mode1MoveSpeed, 0x100);
DOTD_ASSERT_OFFSET(CKTransformElement, m_airMode1P11f8Enable, 0x104);
DOTD_ASSERT_OFFSET(CKTransformElement, m_airMode1P11f8, 0x108);
DOTD_ASSERT_OFFSET(CKTransformElement, m_groundPerm1Perm0TurnEnable, 0x110);
DOTD_ASSERT_OFFSET(CKTransformElement, m_groundTurnAB, 0x114);
DOTD_ASSERT_OFFSET(CKTransformElement, m_groundMoveSpeed, 0x11c);
DOTD_ASSERT_OFFSET(CKTransformElement, m_groundP11f8Enable, 0x120);
DOTD_ASSERT_OFFSET(CKTransformElement, m_groundP11f8, 0x124);
DOTD_ASSERT_OFFSET(CKTransformElement, m_emitterFxData, 0x128);
DOTD_ASSERT_OFFSET(CKTransformElement, m_unk12c, 0x12c);
DOTD_ASSERT_OFFSET(CKTransformElement, m_unk130, 0x130);
DOTD_ASSERT_OFFSET(CKTransformElement, m_unk138, 0x138);
DOTD_ASSERT_OFFSET(CKTransformElement, m_unk13c, 0x13c);
DOTD_ASSERT_OFFSET(CKTransformElement, m_unk140, 0x140);
DOTD_ASSERT_OFFSET(CKTransformElement, m_unk148, 0x148);
DOTD_ASSERT_OFFSET(CKTransformElement, m_elementDamage, 0x14c);
