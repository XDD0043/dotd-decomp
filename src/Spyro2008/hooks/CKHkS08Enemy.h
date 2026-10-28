// CKHkS08Enemy.h - Spyro's enemy hook (key 0x26c2, vtable 0xb22078, size 0x8f8). Original units:
// CKHkS08Enemy.cpp (constructor, IKHkEnemy) and CKHkS08Enemy_2.cpp..CKHkS08Enemy_16.cpp (Load in _9). No XXL2
// class of this name; derives from IKHkEnemy.
//
// A second base sits at +0x1c0 (vtable 0xb21458: destructors, a no-op, Save 0x265550, Load 0x265870; Ghidra
// Vt_b21458_*): not modelled yet, its vtable word is a plain field. An embedded CKS08Damage sits at +0x8bc
// (CKS08Damage_Construct 0x4ebc70, the combat family's class).
#pragma once
#include <cstdint>

#include "Spyro2008/hooks/IKHkEnemy.h"
#include "Spyro2008/logic/CKS08Damage.h"
#include "k2000/core/Layout.h"
#include "k2000/util/TVector.h"

class CKHkS08Enemy : public IKHkEnemy {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0x9b)
    DOTD_DECLARE_FACTORIES(CKHkS08Enemy)

    CKHkS08Enemy();  // 0x0027d548 CKHkS08Enemy_Construct (inlined in CKHkS08Enemy_Create 0x27e408)
    ~CKHkS08Enemy() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x002951a0 CKHkS08Enemy_Load
    void Start() override;  // vt+0x50 0x00294a78 CKHkS08Enemy_Start (C2.2)
    int32_t PostLoad(int32_t type) override;  // vt+0x30 0x00294aa0 CKHkS08Enemy_PostLoad
    void ResetRuntimeState() override;        // vt+0xc4 0x00291e88 CKHkS08Enemy_ResetRuntimeState_maybe

    uint32_t m_unk1B4[3];                   // +0x1b4
    void* m_pSecondVtable1C0;               // +0x1c0 the second base's vtable (0xb21458); null here
    uint8_t m_pad1c4[42];
    uint8_t m_unk1ee;  // +0x1ee  (C2.2 strict3)
    uint8_t m_pad1ef[73];
    uint8_t m_unk238;  // +0x238  (C2.2 strict3)
    uint8_t m_unk239;  // +0x239  (C2.2 strict3)
    uint8_t m_pad23a[34];
    uint32_t m_unk25c;  // +0x25c  (C2.2 strict3)
    uint32_t m_unk260;  // +0x260  (C2.2 strict3)
    uint8_t m_unk264;  // +0x264  (C2.2 strict3)
    uint8_t m_pad265[43];
    uint8_t m_unk290;  // +0x290  (C2.2 strict3)
    uint8_t m_pad291[3];
    uint32_t m_unk294;  // +0x294  (C2.2 strict3)
    uint32_t m_unk298;  // +0x298  (C2.2 strict3)
    uint32_t m_pad29c[2];
    uint32_t m_unk2a4;  // +0x2a4  (C2.2 strict3)
    uint32_t m_unk2a8;  // +0x2a8  (C2.2 strict3)
    uint32_t m_unk2ac;  // +0x2ac  (C2.2 strict3)
    uint32_t m_unk2b0[30];  // +0x2b0 ResetRuntimeState clears the thirty words
    uint8_t m_unk328;  // +0x328  (C2.2 strict3)
    uint8_t m_pad329[3];
    uint32_t m_unk32c;  // +0x32c  (C2.2 strict3)
    uint32_t m_unk330;  // +0x330  (C2.2 strict3)
    uint32_t m_pad334[4];
    uint32_t m_unk344;  // +0x344  (C2.2 strict3)
    uint32_t m_unk348;  // +0x348  (C2.2 strict3)
    uint32_t m_pad34c[3];
    uint8_t m_unk358;  // +0x358  (C2.2 strict3)
    uint8_t m_pad359[3];
    uint32_t m_unk35c;  // +0x35c  (C2.2 strict3)
    uint32_t m_pad360;
    float m_unk364;  // +0x364  (C2.2 strict3)
    float m_unk368;  // +0x368  (C2.2 strict3)
    float m_unk36c;  // +0x36c  (C2.2 strict3)
    float m_unk370;  // +0x370  (C2.2 strict3)
    float m_unk374;  // +0x374  (C2.2 strict3)
    float m_unk378;  // +0x378  (C2.2 strict3)
    float m_unk37c;  // +0x37c  (C2.2 strict3)
    float m_unk380;  // +0x380  (C2.2 strict3)
    float m_unk384;  // +0x384  (C2.2 strict3)
    float m_unk388;  // +0x388  (C2.2 strict3)
    float m_unk38c;  // +0x38c  (C2.2 strict3)
    float m_unk390;  // +0x390  (C2.2 strict3)
    uint32_t m_unk394;  // +0x394  (C2.2 strict3)
    uint8_t m_unk398;  // +0x398  (C2.2 strict3)
    uint8_t m_pad399[7];
    uint8_t m_unk3A0;                       // +0x3a0 constructor 0xff (Ghidra bState)
    uint8_t m_unk3A1;                       // +0x3a1 constructor 0xff
    uint8_t m_pad3A2[2];
    uint32_t m_unk3A4[0x50];                // +0x3a4
    // Four reference vectors sized by the kind's count (kEnemyRefCount[m_ui8EnemyClassType]), and one word
    // vector that gets a zero per +0x4e4 entry (Load). Constructor: no block, capacity 1, nothing used.
    TVector<IKSerializable*, 1> m_unk4E4;   // +0x4e4
    TVector<IKSerializable*, 1> m_unk4F0;   // +0x4f0
    TVector<IKSerializable*, 1> m_unk4FC;   // +0x4fc
    TVector<IKSerializable*, 1> m_unk508;   // +0x508
    TVector<void*, 1> m_unk514;             // +0x514 (Ghidra dwArmorParts, +0x51c dwArmorPartCount: unverified)
    uint32_t m_unk520[6];                   // +0x520
    uint8_t m_unk538;                       // +0x538 constructor 0xff
    uint8_t m_unk539;                       // +0x539 constructor 0xff
    uint8_t m_pad53A[2];
    uint32_t m_unk53C[7];                   // +0x53c
    uint8_t m_unk558;                       // +0x558 constructor 0xff
    uint8_t m_unk559;                       // +0x559 constructor 0xff
    uint8_t m_pad55A[2];
    uint32_t m_unk55C[0x23];                // +0x55c
    uint8_t m_unk5E8;                       // +0x5e8 constructor 0xff
    uint8_t m_unk5E9;                       // +0x5e9 constructor 0xff
    uint8_t m_pad5EA[2];
    uint32_t m_unk5EC[0x51];                // +0x5ec
    uint8_t m_unk730;                       // +0x730 read (one byte; +0x731..+0x733 runtime)
    uint8_t m_pad731[3];
    IKSerializable* m_unk734;               // +0x734 reference (live: a CKS08CarrierEnemy)
    uint32_t m_unk738[0x13];                // +0x738
    IKSerializable* m_unk784;               // +0x784 reference (live: a CKCometDash)
    uint32_t m_unk788[0x41];                // +0x788
    IKSerializable* m_unk88C;               // +0x88c reference (live: a CGlowNodeFx)
    uint32_t m_unk890[0xb];                 // +0x890
    CKS08Damage m_damage8BC;                // +0x8bc embedded CKS08Damage (0x28 bytes; CKS08Damage_Construct 0x4ebc70)
    uint32_t m_unk8E4[5];                   // +0x8e4
};
DOTD_ASSERT_SIZE(CKHkS08Enemy, 0x8f8);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_pSecondVtable1C0, 0x1c0);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk3A0, 0x3a0);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk4E4, 0x4e4);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk4F0, 0x4f0);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk4FC, 0x4fc);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk508, 0x508);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk514, 0x514);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk538, 0x538);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk558, 0x558);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk5E8, 0x5e8);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk730, 0x730);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk734, 0x734);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk784, 0x784);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk88C, 0x88c);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_damage8BC, 0x8bc);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk1ee, 0x1ee);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk238, 0x238);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk239, 0x239);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk25c, 0x25c);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk260, 0x260);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk264, 0x264);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk290, 0x290);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk294, 0x294);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk298, 0x298);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk2a4, 0x2a4);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk2a8, 0x2a8);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk2ac, 0x2ac);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk328, 0x328);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk32c, 0x32c);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk330, 0x330);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk344, 0x344);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk348, 0x348);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk358, 0x358);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk35c, 0x35c);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk364, 0x364);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk368, 0x368);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk36c, 0x36c);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk370, 0x370);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk374, 0x374);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk378, 0x378);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk37c, 0x37c);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk380, 0x380);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk384, 0x384);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk388, 0x388);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk38c, 0x38c);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk390, 0x390);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk394, 0x394);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk398, 0x398);
