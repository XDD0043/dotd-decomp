// CKS08HeroElement.h - a dragon's element attack of an older design (key 0x890c, vtable 0xb231f8 of 0x13c bytes, size
// 0x2cc). Original unit: CKS08HeroElement.cpp (0x36ffa0-0x374d00). No XXL2 class of this name: the members keep
// placeholder names. A root-level class (not an ability element: the CKAbilityElement family replaced it); no level
// file of DotD holds one or a derived element (work/level-class-keys.json), so nothing in the game calls its slots.
// Base of CKS08HeroElementEarth / Electric / Fear / Shadow / Wind (their Loads call this one first; their vtables
// keep slots +0x50..+0x138 of this one except where they override them).
//
// Two attacks per element, each with four levels (arrays [4], indexed by the level): side A (+0x10..+0x11c, +0x120
// projectiles) fires projectiles (vt+0x54 FireProjectile, repeated by vt+0x68 / vt+0x74), side B (+0x130..+0x254) a
// beam: a chain of segments (DirectionChain +0x2c8) that follows the hero's aim (vt+0x6c starts it, vt+0x78 spends
// mana per second and updates it, vt+0x5c tests whether a point is inside it, vt+0x80 ends it). The damage values of
// each side are copied into a 0x40-byte block (+0x2a8 / +0x2ac) for the projectile launch.
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"
#include "k2000/math/CMatrix34.h"

class CKHkS08Hero;
class IKFx;
class IKTime;
struct DirectionChain;

class CKS08HeroElement : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x224)
    // vt+0x08 0x009bef10: the class key or IKSerializable's.
    int32_t IsKindOfClass(uint32_t key) override { return key == 0x890c ? 1 : (key == 0xc ? 1 : 0); }
    DOTD_DECLARE_FACTORIES(CKS08HeroElement)

    // The damage values of one side (Mem_CallocAligned16(1, 0x40), vt+0xf8), handed to the projectile type's launch
    // (vt+0x88) as its damage object.
    struct DamageParams {
        float m_fDamage;        // +0x00 (float) of the side's damage word (+0x10 / +0x16c)
        float m_af04[9];        // +0x04..+0x24 the side's floats (+0x84.. / +0x1c0..; +0x04 = +0x84, +0x08 = +0x94 ...)
        uint8_t m_ui8_28;       // +0x28 the side's first byte (+0x114 / +0x250)
        uint8_t m_ui8_29;       // +0x29 its second (+0x118 / +0x254)
        uint8_t m_pad2a[2];
        uint32_t m_unk2c;       // +0x2c 0
        uint32_t m_unk30;       // +0x30 0
        uint32_t m_unk34;       // +0x34 0
        float m_f38;            // +0x38 side A: +0x70[level]; side B: 0
        uint8_t m_pad3c[4];
    };
    struct Color {
        uint8_t m_aRgba[4];     // read raw (four bytes, not swapped)
    };

    CKS08HeroElement() {}  // inlined in 0x003707d8 CKS08HeroElement_Create: the vtable only
    // 0x009bf7e8 Destructor / 0x009bf7a8 DeletingDestructor: IKSerializable's vtable back, nothing freed (Destroy does).
    ~CKS08HeroElement() override {}
    void Destroy() override;                            // vt+0x10 0x00371580
    void RecursiveRegistration(int32_t /*type*/) override {}  // vt+0x24 0x00371578 (li r3,1: the root's)
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00372158
    int32_t PostLoad(int32_t type) override;            // vt+0x30 0x003715d8

    // ---- the element's slots ----
    // vt+0x50 0x003708b8: the side A projectiles of `level` move (their type's vt+0x50 with the clock's delta), then
    // the first whose age (vt+0xac) times +0x11c passes +0x50[level] dies (vt+0x5c).
    virtual void UpdateProjectiles(IKTime* clock, int32_t level);
    // vt+0x54 0x00371e58 CKS08HeroElement_FireProjectile
    virtual void FireProjectile(int8_t level);
    // vt+0x58 0x00370d08: the beam (side B) of `level` follows the hero's hot spot 4 direction and hits the enemies
    // inside it (vt+0x5c for each active enemy).
    virtual void UpdateBeam(float dt, float speed, float scale, uint8_t level);
    // vt+0x5c 0x003712a0: `point` is inside the beam started at `origin` (within its length and its cone).
    virtual uint8_t IsPointInBeam(float scale, const CVector3* point, const CVector3* origin, int8_t level);
    // vt+0x60 0x00370338: out of mana: the hero's particle node 0 emits (CKHkS08Hero::EnableSubNode).
    virtual void OnOutOfMana();
    // vt+0x64 0x00371710: the beam particles of `level` aimed (the hero's particle node 0, when `on`), then
    // SetCastFxActive (vt+0x130).
    virtual void SetBeamFxActive(int8_t level, uint8_t on);
    // vt+0x68 0x003701a0: the repeated shots of `level`: the count +0x30[level], the first after 0.12 s (dragon 0 and
    // +0x0c clear) or at once.
    virtual void StartRepeatFire(int8_t level);
    // vt+0x6c 0x00371ab8: the beam of `level` built along the hero's aim, then its effects on (vt+0x64).
    virtual void StartBeam(float speed, int8_t level);
    // vt+0x70 0x00370398 CKS08HeroElement_HasEnoughMana: the dragon's mana above +0x60[level].
    virtual uint8_t HasEnoughMana(uint8_t level);
    // vt+0x74 0x00370210: the repeat timer runs out: one more shot (vt+0x54) and the next in 1 / +0x20[level] s.
    virtual void UpdateRepeatFire(float dt, int8_t level);
    // vt+0x78 0x00370ac8 CKS08HeroElement_UpdateChannel_maybe: the beam's mana per second; 1 when it ended (no hero, or
    // out of mana: vt+0x60), else the beam updated (vt+0x58) and 0.
    virtual int32_t UpdateChannel(float dt, float speed, float scale, uint8_t level);
    virtual void Vf7C() {}                     // vt+0x7c 0x009bedf0 (empty)
    // vt+0x80 0x00371608: the beam freed (its segments, the chain) and its effects off (vt+0x64).
    virtual void StopBeam(uint8_t level);
    virtual uint8_t Vf84() { return 0; }       // vt+0x84 0x009bedf8
    virtual void Vf88() {}                     // vt+0x88 0x009bee00 (empty)
    virtual int32_t GetAnimId() { return m_unk144 + 0x91; }   // vt+0x8c 0x00370308
    virtual int32_t GetAnimIdB1() { return m_unk274 + 0x91; } // vt+0x90 0x00370318
    virtual int32_t GetAnimIdB2() { return m_unk278 + 0x91; } // vt+0x94 0x00370328
    // vt+0x98..+0xf4 0x009bee08..0x009beec0: the loaded movement settings of each side.
    virtual uint8_t GetA148() { return m_unk148; }  // vt+0x98
    virtual uint8_t GetA149() { return m_unk149; }  // vt+0x9c
    virtual uint8_t GetA14a() { return m_unk14a; }  // vt+0xa0
    virtual float GetA14c() { return m_unk14c; }    // vt+0xa4
    virtual float GetA150() { return m_unk150; }    // vt+0xa8
    virtual uint8_t GetA154() { return m_unk154; }  // vt+0xac
    virtual uint8_t GetA155() { return m_unk155; }  // vt+0xb0
    virtual uint8_t GetA156() { return m_unk156; }  // vt+0xb4
    virtual float GetA158() { return m_unk158; }    // vt+0xb8
    virtual float GetA15c() { return m_unk15c; }    // vt+0xbc
    virtual float GetA160() { return m_unk160; }    // vt+0xc0
    virtual float GetA164() { return m_unk164; }    // vt+0xc4
    virtual uint8_t GetB27c() { return m_unk27c; }  // vt+0xc8
    virtual uint8_t GetB27d() { return m_unk27d; }  // vt+0xcc
    virtual uint8_t GetB27e() { return m_unk27e; }  // vt+0xd0
    virtual float GetB280() { return m_unk280; }    // vt+0xd4
    virtual float GetB284() { return m_unk284; }    // vt+0xd8
    virtual uint8_t GetB288() { return m_unk288; }  // vt+0xdc
    virtual uint8_t GetB289() { return m_unk289; }  // vt+0xe0
    virtual uint8_t GetB28a() { return m_unk28a; }  // vt+0xe4
    virtual float GetB28c() { return m_unk28c; }    // vt+0xe8
    virtual float GetB290() { return m_unk290; }    // vt+0xec
    virtual float GetB294() { return m_unk294; }    // vt+0xf0
    virtual float GetB298() { return m_unk298; }    // vt+0xf4
    // vt+0xf8 0x00370408: both damage blocks (allocated when missing) filled from `level`'s values.
    virtual void SetDamageLevel(uint8_t level);
    virtual DamageParams* GetDamageA() { return m_pDamageA; }  // vt+0xfc 0x00370018
    virtual DamageParams* GetDamageB() { return m_pDamageB; }  // vt+0x100 0x00370020
    // vt+0x104 0x00370028: side B's damage block of `level` scaled by `scale` (the frame's share of the beam).
    virtual void ScaleDamageB(float scale, int32_t level);
    virtual void SetDragon(uint8_t dragon) { m_ui8Dragon = dragon; }  // vt+0x108 0x009beec8
    virtual uint8_t GetDragon() { return m_ui8Dragon; }               // vt+0x10c 0x009beed0
    virtual void SetUnk0c(uint8_t value) { m_unk0c = value; }         // vt+0x110 0x009beed8
    virtual uint8_t GetUnk0c() { return m_unk0c; }                    // vt+0x114 0x009beee0
    virtual int32_t Vf118() { return 0; }      // vt+0x118 0x003702f8 KStub_Return0
    virtual int32_t Vf11C() { return 0; }      // vt+0x11c 0x00370300 KStub_Return0
    // vt+0x120 0x00370cc0: the colour of side 0 (+0x2b0) or 1 (+0x2b4), white (0x00c50dfc) otherwise.
    virtual Color GetColor(int32_t side);
    virtual uint8_t GetHotSpotIndex() { return m_unk80; }              // vt+0x124 0x009beee8
    virtual uint32_t GetSegmentCount() { return m_unk2a0 + 1; }        // vt+0x128 0x009beef0
    virtual float GetFollowSpeed() { return m_unk2a4; }                // vt+0x12c 0x009bef00
    // vt+0x130 0x00370f88 CKS08HeroElement_SetCastFxActive_maybe: the spark (+0x26c) under the hero's hot spot 0x12
    // acquired into +0x270, or stopped and let go.
    virtual void SetCastFxActive(uint8_t on);
    // vt+0x134 0x00370a28 CKS08HeroElement_GetHero: +0x08, else the hero group's hero of the dragon (kept).
    virtual CKHkS08Hero* GetHero();
    virtual uint8_t Vf138() { return 0; }      // vt+0x138 0x009bef08 KStub_Return0

    // ---- members (the Load reads type 0 only) ----
    uint8_t m_ui8Dragon;          // +0x04 the dragon (vt+0x108)
    uint8_t m_pad05[3];
    CKHkS08Hero* m_pHero;         // +0x08 the hero (GetHero; PostLoad 0)
    uint8_t m_unk0c;              // +0x0c (vt+0x110; vt+0x68: no first-shot delay when set)
    uint8_t m_pad0d[3];
    // Side A, per level.
    int32_t m_unk10[4];           // +0x10 the damage (the block's +0x00)
    int32_t m_unk20[4];           // +0x20 the repeated shots per second (vt+0x74)
    int32_t m_unk30[4];           // +0x30 the repeated shot count (vt+0x68)
    uint32_t m_unk40[4];          // +0x40 (no reader found)
    float m_unk50[4];             // +0x50 the projectiles' life (vt+0x50: age times +0x11c)
    uint32_t m_unk60[4];          // +0x60 the mana per shot
    float m_unk70[4];             // +0x70 the block's +0x38
    uint8_t m_unk80;              // +0x80 the hot spot of the shots (vt+0x124; 0xff: 1)
    uint8_t m_pad81[3];
    float m_unk84[9][4];          // +0x84..+0x110 the block's +0x04..+0x24
    uint8_t m_unk114[4];          // +0x114 the block's +0x28
    uint8_t m_unk118[4];          // +0x118 the block's +0x29
    float m_unk11c;               // +0x11c the projectiles' speed bonus (added to the hero's)
    IKSerializable* m_apUnk120[4];  // +0x120 references: the CKProjectileAccessor of each level
    // Side B.
    uint32_t m_unk130[4];         // +0x130 (no reader found)
    uint8_t m_unk140;             // +0x140 (no reader found)
    uint8_t m_pad141[3];
    int32_t m_unk144;             // +0x144 the animation (vt+0x8c: +0x91)
    uint8_t m_unk148;             // +0x148 (vt+0x98)
    uint8_t m_unk149;             // +0x149 (vt+0x9c)
    uint8_t m_unk14a;             // +0x14a (vt+0xa0)
    uint8_t m_pad14b;
    float m_unk14c;               // +0x14c (vt+0xa4)
    float m_unk150;               // +0x150 (vt+0xa8)
    uint8_t m_unk154;             // +0x154 (vt+0xac)
    uint8_t m_unk155;             // +0x155 (vt+0xb0)
    uint8_t m_unk156;             // +0x156 (vt+0xb4)
    uint8_t m_pad157;
    float m_unk158;               // +0x158 (vt+0xb8)
    float m_unk15c;               // +0x15c (vt+0xbc)
    float m_unk160;               // +0x160 (vt+0xc0)
    float m_unk164;               // +0x164 (vt+0xc4)
    uint32_t m_unk168;            // +0x168 (not loaded)
    int32_t m_unk16c[4];          // +0x16c the beam's damage (block B's +0x00)
    uint32_t m_unk17c[4];         // +0x17c (no reader found)
    float m_unk18c[4];            // +0x18c the beam's length
    int32_t m_unk19c[4];          // +0x19c the beam's mana per second
    float m_unk1ac[4];            // +0x1ac the beam's cone angle (degrees)
    uint8_t m_unk1bc;             // +0x1bc (no reader found)
    uint8_t m_pad1bd[3];
    float m_unk1c0[9][4];         // +0x1c0..+0x24c block B's +0x04..+0x24
    uint8_t m_unk250[4];          // +0x250 block B's +0x28
    uint8_t m_unk254[4];          // +0x254 block B's +0x29
    IKSerializable* m_apUnk258[4];  // +0x258 references (side B's accessors, no reader found)
    uint8_t m_unk268;             // +0x268 (no reader found)
    uint8_t m_pad269[3];
    IKSerializable* m_unk26c;     // +0x26c reference: the cast spark (CKSparkFxData)
    IKFx* m_unk270;               // +0x270 the spark acquired (vt+0x130; PostLoad 0)
    int32_t m_unk274;             // +0x274 an animation (vt+0x90)
    int32_t m_unk278;             // +0x278 an animation (vt+0x94)
    uint8_t m_unk27c;             // +0x27c (vt+0xc8)
    uint8_t m_unk27d;             // +0x27d (vt+0xcc)
    uint8_t m_unk27e;             // +0x27e (vt+0xd0)
    uint8_t m_pad27f;
    float m_unk280;               // +0x280 (vt+0xd4)
    float m_unk284;               // +0x284 (vt+0xd8)
    uint8_t m_unk288;             // +0x288 (vt+0xdc)
    uint8_t m_unk289;             // +0x289 (vt+0xe0)
    uint8_t m_unk28a;             // +0x28a (vt+0xe4)
    uint8_t m_pad28b;
    float m_unk28c;               // +0x28c (vt+0xe8)
    float m_unk290;               // +0x290 (vt+0xec)
    float m_unk294;               // +0x294 (vt+0xf0)
    float m_unk298;               // +0x298 (vt+0xf4)
    uint32_t m_unk29c;            // +0x29c (not loaded)
    uint32_t m_unk2a0;            // +0x2a0 the beam's segment count less one (vt+0x128)
    float m_unk2a4;               // +0x2a4 the segments' follow speed (vt+0x12c)
    DamageParams* m_pDamageA;     // +0x2a8 (Load / vt+0xf8)
    DamageParams* m_pDamageB;     // +0x2ac
    Color m_unk2b0;               // +0x2b0 side 0's colour
    Color m_unk2b4;               // +0x2b4 side 1's colour
    float m_unk2b8;               // +0x2b8 the time to the next repeated shot
    int32_t m_unk2bc;             // +0x2bc the repeated shots left
    float m_unk2c0;               // +0x2c0 the beam's mana not spent yet (a fraction)
    float m_unk2c4;               // +0x2c4 PostLoad 5.0 (no reader found)
    DirectionChain* m_pBeam;      // +0x2c8 the beam (vt+0x6c / vt+0x80)
};
DOTD_ASSERT_SIZE(CKS08HeroElement::DamageParams, 0x40);
DOTD_ASSERT_SIZE(CKS08HeroElement, 0x2cc);
DOTD_ASSERT_OFFSET(CKS08HeroElement, m_pHero, 0x08);
DOTD_ASSERT_OFFSET(CKS08HeroElement, m_unk10, 0x10);
DOTD_ASSERT_OFFSET(CKS08HeroElement, m_unk70, 0x70);
DOTD_ASSERT_OFFSET(CKS08HeroElement, m_unk84, 0x84);
DOTD_ASSERT_OFFSET(CKS08HeroElement, m_unk114, 0x114);
DOTD_ASSERT_OFFSET(CKS08HeroElement, m_apUnk120, 0x120);
DOTD_ASSERT_OFFSET(CKS08HeroElement, m_unk130, 0x130);
DOTD_ASSERT_OFFSET(CKS08HeroElement, m_unk144, 0x144);
DOTD_ASSERT_OFFSET(CKS08HeroElement, m_unk168, 0x168);
DOTD_ASSERT_OFFSET(CKS08HeroElement, m_unk16c, 0x16c);
DOTD_ASSERT_OFFSET(CKS08HeroElement, m_unk1ac, 0x1ac);
DOTD_ASSERT_OFFSET(CKS08HeroElement, m_unk1c0, 0x1c0);
DOTD_ASSERT_OFFSET(CKS08HeroElement, m_unk250, 0x250);
DOTD_ASSERT_OFFSET(CKS08HeroElement, m_apUnk258, 0x258);
DOTD_ASSERT_OFFSET(CKS08HeroElement, m_unk26c, 0x26c);
DOTD_ASSERT_OFFSET(CKS08HeroElement, m_unk274, 0x274);
DOTD_ASSERT_OFFSET(CKS08HeroElement, m_unk28c, 0x28c);
DOTD_ASSERT_OFFSET(CKS08HeroElement, m_unk2a0, 0x2a0);
DOTD_ASSERT_OFFSET(CKS08HeroElement, m_pDamageA, 0x2a8);
DOTD_ASSERT_OFFSET(CKS08HeroElement, m_unk2b0, 0x2b0);
DOTD_ASSERT_OFFSET(CKS08HeroElement, m_pBeam, 0x2c8);
