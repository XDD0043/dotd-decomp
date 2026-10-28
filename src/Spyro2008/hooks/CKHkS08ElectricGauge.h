// CKHkS08ElectricGauge.h - an electric gauge hook (key 0x2e42, vtable 0xb281d0, size 0xf4). Original unit:
// CKHkS08ElectricGauge.cpp. No XXL2 class. Field names are placeholders (C2.1 ports the constructor and
// Load only).
#pragma once
#include <cstdint>

#include "Spyro2008/ui/CKHkS08ElectricGaugeBase.h"
#include "k2000/core/Layout.h"
#include "k2000/services/CTriggerStarter.h"

class CKHkS08ElectricGauge : public CKHkS08ElectricGaugeBase {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0xb9)
    DOTD_DECLARE_FACTORIES(CKHkS08ElectricGauge)

    // 0x00493268 CKHkS08ElectricGauge_Create (inlined constructor, the same as 0x492ad8
    // CKHkS08ElectricGauge_Construct): +0xd1 and +0xd0 = 0xff.
    CKHkS08ElectricGauge() {
        m_unkD1 = 0xff;
        m_unkD0 = 0xff;
    }
    ~CKHkS08ElectricGauge() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00493a38 CKHkS08ElectricGauge_Load
    void Start() override;  // vt+0x50 0x00493518 CKHkS08ElectricGauge_Start (C2.2)
    // The state engine: the state `state` of the table at +0xd4 called with the frame clock, the phase (0 tick,
    // 1 enter, 2 leave) and the other state; returns the next state.
    uint8_t CallState(uint8_t state, IKTime* clock, int32_t phase, uint8_t other);
    using StateFn = uint8_t (CKHkS08ElectricGauge::*)(IKTime* clock, int32_t phase, uint8_t other);
    // 0x00492648 KStub_ReturnArg4_492648 (descriptor 0xbc4290, state 3): the state stays as given.
    uint8_t State3Idle(IKTime*, int32_t, uint8_t other) { return other; }
    // 0x00494d28 CKHkS08ElectricGauge_State1_Moving_maybe (descriptor 0xbc4568)
    uint8_t State1Moving(IKTime* clock, int32_t phase, uint8_t other);

    IKSerializable* m_unk20;          // +0x20 reference (LVL010: a CNode)
    IKSerializable* m_apUnk24[6];     // +0x24..+0x3b references (separate reads; LVL010: CSGHotSpots, then two of key 0x174c)
    uint32_t m_unk3c[2];              // +0x3c runtime
    IKSerializable* m_apUnk44[3];     // +0x44..+0x4f references (LVL010: CKExplosionFxData)
    float m_unk50;                    // +0x50
    uint32_t m_unk54;                 // +0x54 runtime
    float m_unk58;                    // +0x58
    float m_unk5c;                    // +0x5c runtime (Start: a random value around m_unk50)
    uint32_t m_unk60;                 // +0x60 runtime
    float m_unk64;                    // +0x64
    IKSerializable* m_unk68;          // +0x68 reference (read last)
    IKSerializable* m_unk6c;          // +0x6c reference
    uint32_t m_unk70;                 // +0x70 runtime (PostLoad 0x4929c0 clears it)
    float m_unk74;                    // +0x74
    uint32_t m_unk78[10];             // +0x78..+0x9f runtime
    float m_unkA0;                    // +0xa0
    float m_unkA4;                    // +0xa4
    float m_unkA8;                    // +0xa8
    CTriggerStarter m_unkAC;          // +0xac
    CTriggerStarter m_unkB4;          // +0xb4
    CTriggerStarter m_unkBC;          // +0xbc
    CTriggerStarter m_unkC4;          // +0xc4
    void* m_pStateTable;              // +0xcc Start: the state table at +0xd4 (the state engine)
    uint8_t m_unkD0;                  // +0xd0 constructor 0xff
    uint8_t m_unkD1;                  // +0xd1 constructor 0xff
    uint8_t m_padD2[2];
    // +0xd4 the state table: four {descriptor, this adjustment} pairs of PS3 pointers to member functions
    // (Start; the descriptors 0xbc4570 / 0xbc4568 / 0xbc43a0 / 0xbc4290 are the OPDs of the states 0 to 3).
    uint32_t m_unkD4[8];
};
DOTD_ASSERT_SIZE(CKHkS08ElectricGauge, 0xf4);
DOTD_ASSERT_OFFSET(CKHkS08ElectricGauge, m_unk20, 0x20);
DOTD_ASSERT_OFFSET(CKHkS08ElectricGauge, m_apUnk24, 0x24);
DOTD_ASSERT_OFFSET(CKHkS08ElectricGauge, m_apUnk44, 0x44);
DOTD_ASSERT_OFFSET(CKHkS08ElectricGauge, m_unk50, 0x50);
DOTD_ASSERT_OFFSET(CKHkS08ElectricGauge, m_unk58, 0x58);
DOTD_ASSERT_OFFSET(CKHkS08ElectricGauge, m_unk64, 0x64);
DOTD_ASSERT_OFFSET(CKHkS08ElectricGauge, m_unk68, 0x68);
DOTD_ASSERT_OFFSET(CKHkS08ElectricGauge, m_unk6c, 0x6c);
DOTD_ASSERT_OFFSET(CKHkS08ElectricGauge, m_unk74, 0x74);
DOTD_ASSERT_OFFSET(CKHkS08ElectricGauge, m_unkA0, 0xa0);
DOTD_ASSERT_OFFSET(CKHkS08ElectricGauge, m_unkAC, 0xac);
DOTD_ASSERT_OFFSET(CKHkS08ElectricGauge, m_unkC4, 0xc4);
DOTD_ASSERT_OFFSET(CKHkS08ElectricGauge, m_unkD0, 0xd0);
