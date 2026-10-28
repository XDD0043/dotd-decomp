// CKAttackMoveElement.h - the shared base of the element attack moves (key 0x9a0c, vtable 0xb23340, size 0x1a8).
// Original unit: CKAttackMoveElement.cpp (0x374d50-0x3798b8). No XXL2 class of this name: the members keep
// placeholder names. Base of CKBlackCombo, CKCometDash, CKPoisonSpin, CKPurpleCombo.
// Its own base is the unregistered abstract KBase90CC (CKAbilityElement_maybe); its Load is not called and its
// constructor only stores a vtable, so the port derives from IKSerializable directly (+0x04 is that base's field).
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"

// Three floats read with one 12-byte Read and swapped word by word (the derived Loads' +0x1e4 records;
// file values such as 0.75 0.75 1.0: a scale, _maybe).
struct CKAttackMoveVec3 {
    float m_unk0;
    float m_unk4;
    float m_unk8;
};
DOTD_ASSERT_SIZE(CKAttackMoveVec3, 0xc);

class CKAttackMoveElement : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x268)
    DOTD_DECLARE_FACTORIES(CKAttackMoveElement)

    CKAttackMoveElement() {}  // 0x00374da0 CKAttackMoveElement_Construct: stores the vtable only
    ~CKAttackMoveElement() override {}
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00377578 CKAttackMoveElement_Load

    uint32_t m_unk04;      // +0x04 (not loaded; live 0)
    int32_t m_unk08[3];    // +0x08 (file: 90 135 270)
    float m_unk14;         // +0x14
    float m_unk18;         // +0x18
    float m_unk1c;         // +0x1c
    float m_unk20[3];      // +0x20
    float m_unk2c;         // +0x2c
    float m_unk30;         // +0x30
    float m_unk34;         // +0x34
    int32_t m_unk38[3];    // +0x38 (file: 80 100 133)
    float m_unk44[3];      // +0x44
    float m_unk50;         // +0x50
    float m_unk54;         // +0x54
    float m_unk58;         // +0x58
    float m_unk5c;         // +0x5c
    float m_unk60;         // +0x60
    float m_unk64;         // +0x64
    float m_unk68;         // +0x68 (file and live: 0; float assumed)
    float m_unk6c;         // +0x6c (file and live: 0)
    float m_unk70;         // +0x70 (file and live: 0)
    float m_unk74;         // +0x74 (file and live: 0)
    float m_unk78[3];      // +0x78
    float m_unk84[3];      // +0x84
    float m_unk90[3];      // +0x90
    float m_unk9c[3];      // +0x9c (file and live: 0; float assumed, as +0xa8..+0xec)
    float m_unka8[3];      // +0xa8
    float m_unkb4[3];      // +0xb4
    float m_unkc0[3];      // +0xc0
    float m_unkcc[3];      // +0xcc
    float m_unkd8[3];      // +0xd8
    float m_unke4;         // +0xe4
    float m_unke8;         // +0xe8
    float m_unkec;         // +0xec
    uint8_t m_unkf0[3];    // +0xf0
    uint8_t m_unkf3[3];    // +0xf3
    uint8_t m_padF6[2];    // +0xf6
    float m_unkf8[3];      // +0xf8
    float m_unk104[3];     // +0x104
    float m_unk110[3];     // +0x110
    float m_unk11c;        // +0x11c (file and live: 0)
    float m_unk120;        // +0x120 (file and live: 0)
    float m_unk124;        // +0x124 (file and live: 0)
    float m_unk128;        // +0x128
    float m_unk12c;        // +0x12c
    float m_unk130;        // +0x130
    uint8_t m_unk134;      // +0x134
    uint8_t m_unk135;      // +0x135
    uint8_t m_unk136;      // +0x136
    uint8_t m_pad137;      // +0x137
    float m_unk138;        // +0x138
    float m_unk13c;        // +0x13c
    uint8_t m_unk140;      // +0x140
    uint8_t m_unk141;      // +0x141
    uint8_t m_unk142;      // +0x142
    uint8_t m_pad143;      // +0x143
    float m_unk144;        // +0x144
    float m_unk148;        // +0x148
    float m_unk14c;        // +0x14c
    float m_unk150;        // +0x150
    uint8_t m_unk154;      // +0x154
    uint8_t m_unk155;      // +0x155
    uint8_t m_pad156[2];   // +0x156
    float m_unk158;        // +0x158
    float m_unk15c;        // +0x15c
    uint8_t m_unk160;      // +0x160
    uint8_t m_unk161;      // +0x161
    uint8_t m_unk162;      // +0x162
    uint8_t m_pad163;      // +0x163
    float m_unk164;        // +0x164
    float m_unk168;        // +0x168
    float m_unk16c;        // +0x16c
    uint8_t m_unk170;      // +0x170 (one byte loaded; live, the word holds more: +0x171..+0x173 set at runtime)
    uint8_t m_unk171[3];   // +0x171 (not loaded)
    float m_unk174;        // +0x174
    IKSerializable* m_unk178;  // +0x178 (live: CKExplosionFxData)
    uint8_t m_unk17c[0x20];    // +0x17c..+0x19b runtime (not loaded)
    IKSerializable* m_unk19c;  // +0x19c (live: CKS08ElementDamage)
    uint8_t m_unk1a0[8];       // +0x1a0..+0x1a7 runtime (not loaded)
};
DOTD_ASSERT_SIZE(CKAttackMoveElement, 0x1a8);
DOTD_ASSERT_OFFSET(CKAttackMoveElement, m_unk08, 0x08);
DOTD_ASSERT_OFFSET(CKAttackMoveElement, m_unk14, 0x14);
DOTD_ASSERT_OFFSET(CKAttackMoveElement, m_unk20, 0x20);
DOTD_ASSERT_OFFSET(CKAttackMoveElement, m_unk2c, 0x2c);
DOTD_ASSERT_OFFSET(CKAttackMoveElement, m_unk38, 0x38);
DOTD_ASSERT_OFFSET(CKAttackMoveElement, m_unk44, 0x44);
DOTD_ASSERT_OFFSET(CKAttackMoveElement, m_unk50, 0x50);
DOTD_ASSERT_OFFSET(CKAttackMoveElement, m_unk5c, 0x5c);
DOTD_ASSERT_OFFSET(CKAttackMoveElement, m_unk70, 0x70);
DOTD_ASSERT_OFFSET(CKAttackMoveElement, m_unk78, 0x78);
DOTD_ASSERT_OFFSET(CKAttackMoveElement, m_unk9c, 0x9c);
DOTD_ASSERT_OFFSET(CKAttackMoveElement, m_unkd8, 0xd8);
DOTD_ASSERT_OFFSET(CKAttackMoveElement, m_unke4, 0xe4);
DOTD_ASSERT_OFFSET(CKAttackMoveElement, m_unkf0, 0xf0);
DOTD_ASSERT_OFFSET(CKAttackMoveElement, m_unkf3, 0xf3);
DOTD_ASSERT_OFFSET(CKAttackMoveElement, m_unkf8, 0xf8);
DOTD_ASSERT_OFFSET(CKAttackMoveElement, m_unk110, 0x110);
DOTD_ASSERT_OFFSET(CKAttackMoveElement, m_unk11c, 0x11c);
DOTD_ASSERT_OFFSET(CKAttackMoveElement, m_unk130, 0x130);
DOTD_ASSERT_OFFSET(CKAttackMoveElement, m_unk134, 0x134);
DOTD_ASSERT_OFFSET(CKAttackMoveElement, m_unk138, 0x138);
DOTD_ASSERT_OFFSET(CKAttackMoveElement, m_unk140, 0x140);
DOTD_ASSERT_OFFSET(CKAttackMoveElement, m_unk144, 0x144);
DOTD_ASSERT_OFFSET(CKAttackMoveElement, m_unk154, 0x154);
DOTD_ASSERT_OFFSET(CKAttackMoveElement, m_unk158, 0x158);
DOTD_ASSERT_OFFSET(CKAttackMoveElement, m_unk160, 0x160);
DOTD_ASSERT_OFFSET(CKAttackMoveElement, m_unk164, 0x164);
DOTD_ASSERT_OFFSET(CKAttackMoveElement, m_unk170, 0x170);
DOTD_ASSERT_OFFSET(CKAttackMoveElement, m_unk174, 0x174);
DOTD_ASSERT_OFFSET(CKAttackMoveElement, m_unk178, 0x178);
DOTD_ASSERT_OFFSET(CKAttackMoveElement, m_unk19c, 0x19c);
