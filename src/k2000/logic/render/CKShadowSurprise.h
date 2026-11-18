// CKShadowSurprise.h - Cynder's shadow surprise (key 0xa4cc, vtable 0xb247f0, size 0x274; ability id 14, Cynder's
// element 1, hero slot 2). Original unit:
// CKShadowSurprise.cpp. Base: CKTransformElement (0x954c), whose Load it calls first. Not in XXL2; names ours.
// The per-level arrays (three entries) follow the base's convention: indexed by the element's upgrade level.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/CKTransformElement.h"
#include "k2000/math/CMatrix34.h"

class CKSound;

class CKShadowSurprise : public CKTransformElement {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x293)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c0848
        return key == 0xa4cc || key == 0xc || key == 0x954c || key == 0x90cc;
    }
    DOTD_DECLARE_FACTORIES(CKShadowSurprise)

    CKShadowSurprise() {}  // 0x003d7ee0 CKShadowSurprise_Construct: CKTransformElement, then the vtable
    ~CKShadowSurprise() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x003d8ef8 CKShadowSurprise_Load
    int32_t PostLoad(int32_t type) override;           // vt+0x30 0x003d7e40 CKShadowSurprise_PostLoad
    uint8_t GetAbilityId() override { return 0xe; }    // vt+0x50 0x003d7550 CKShadowSurprise_GetAbilityId
    uint8_t GetFamilyId() override { return 0x17; }    // vt+0x54 0x003d7558 CKShadowSurprise_GetFamilyId
    // vt+0x58 0x003d7d00 CKShadowSurprise_Start: the sounds cleared, the base's Start, the impulse component's value,
    // speed and timer cleared, the timers reset (+0x258 = +0x23c, +0x25c = 0), the time scale +0x254 = 1.
    void Start(CKS08AbilityHostBase* host) override;
    // vt+0x64 0x003d7948 CKShadowSurprise_End: the sounds stopped, the hero's +0x1d20 back to 1, the attack sphere
    // off, the user's node shown, the shadow node hidden in the sector 0 root; the base's End.
    void End(int32_t forced) override;
    // vt+0x68 0x003d7798 CKShadowSurprise_ApplyHeroControl: the base's, then actions 7, 11 and 12.
    void ApplyHeroControl(uint8_t on) override;
    void ResetRuntime() override;                      // vt+0x6c 0x003d7d70 CKShadowSurprise_ResetRuntime
    // vt+0x70 0x003dae90 CKShadowSurprise_SetFxActive: on: the shadow node shown at the user (scaled +0x1a8[level], its
    // geometries at the start alpha), the level's particles, animated collection and point light, the start explosion,
    // the user's node hidden, the sounds; off: the effects released, the level's end explosion (with its damage), the
    // user's node shown.
    void SetFxActive(int32_t on) override;
    // vt+0x74 0x003d8248 CKShadowSurprise_UpdateEffect_maybe: the time scale's timers, the dash sound's pitch, the shadow
    // node fading and spinning at the user, the effects following, the hero's speed (host vt+0x68) scaled; at level 2
    // a projectile every +0x23c (+- +0x240) / +0x254 seconds. Rand_Int: three draws per projectile.
    void UpdateEffect(float dt) override;
    // vt+0x78 0x009c08a8 CKShadowSurprise_StartEmitterFx: the base's (a thunk).
    // vt+0x7c 0x003dbfd0 CKShadowSurprise_UpdateAttack_maybe: above level 0, the dash: button 3 kicks the impulse
    // component (+0x1d8) with an explosion; its value (+0x254) scales the hero (host vt+0x84).
    void UpdateAttack(float dt) override;
    // vt+0x84 0x003d7ac0 CKShadowSurprise_StopFx: the base's, the damage set up, the attack sphere on, the hero's actions
    // back, the shadow node's fade-out from its current alpha (+0x1d0 0: hidden at once).
    void StopFx() override;
    // vt+0x8c 0x003d7560 CKShadowSurprise_IsGroundTrailActive_maybe: above level 0, the host's vt+0x30.
    uint8_t IsGroundTrailActive() override;

    // 0x003d75c0 CKShadowSurprise_GetFxSound_maybe (not virtual): `which` 1: the loop sound (dictionary 0, 1 or 2 by
    // level), 3: the dash sound (3 or 4, level 1 and up); a level's own sound only when it is there and has a sample.
    CKSound* GetFxSound(uint32_t which);
    // The shadow node's geometries at `alpha` (the alpha walk).
    void SetShadowAlpha(uint8_t alpha);

    float m_unk154[3];         // +0x154 the attack sphere's radius, per level
    int32_t m_unk160[3];       // +0x160 the shadow node's alpha once faded in (extsw: signed), per level
    int32_t m_unk16c[3];       // +0x16c the shadow node's alpha at the start, per level (its low byte: SetFxActive)
    int32_t m_unk178[3];       // +0x178 the shadow node's alpha at the end of the fade-out, per level
    float m_unk184[3];         // +0x184 the spin about x (degrees per second of +0x25c), per level
    float m_unk190[3];         // +0x190 the spin about y, per level
    float m_unk19c[3];         // +0x19c the spin about z, per level
    CVector3 m_unk1a8[3];      // +0x1a8 the shadow node's scale, per level, one 12-byte read each
    float m_unk1cc;            // +0x1cc the fade-in time
    float m_unk1d0;            // +0x1d0 the fade-out time (0: hidden at once)
    IKSerializable* m_unk1d4;  // +0x1d4 (reference; a CNode) the shadow node
    IKSerializable* m_unk1d8;  // +0x1d8 (reference; CKImpulsionCpnt) the dash
    IKSerializable* m_unk1dc[3];  // +0x1dc (references; CKParticlesEffectFxData) per level
    IKSerializable* m_unk1e8;  // +0x1e8 runtime: the particles' effect
    IKSerializable* m_unk1ec[3];  // +0x1ec (references; CKAnimatedFxCollection) per level
    IKSerializable* m_unk1f8;  // +0x1f8 runtime: the collection that plays
    IKSerializable* m_unk1fc[3];  // +0x1fc (references; CKPointLightFxData) per level
    IKSerializable* m_unk208;  // +0x208 runtime: the light's effect
    IKSerializable* m_unk20c;  // +0x20c (reference; CKExplosionFxData) the start explosion
    IKSerializable* m_unk210[3];  // +0x210 (references; CKExplosionFxData) the end explosion, per level
    IKSerializable* m_unk21c;  // +0x21c (reference; CKExplosionFxData) the dash explosion
    IKSerializable* m_unk220[3];  // +0x220 (references; damages) the end explosion's, per level
    IKSerializable* m_unk22c;  // +0x22c (reference; CKProjectileAccessor) level 2's projectiles
    IKSerializable* m_unk230;  // +0x230 (Ghidra draft: CKS08ElementDamage*) the projectiles' damage
    float m_unk234[6];         // +0x234 the projectiles: speed with the dash at its bottom, at its top; the interval's
                               // base and spread; the launch height; the direction's y
    IKSerializable* m_unk24c;  // +0x24c (Ghidra draft: CKSoundDictionaryID*)
    float m_unk250;            // +0x250 the dash sound's pitch at the top
    float m_unk254;            // +0x254 the time scale (the dash's value; Start / ResetRuntime 1.0f, TOC +0x4118)
    float m_unk258;            // +0x258 the time to the next projectile (Start: +0x23c)
    float m_unk25c;            // +0x25c the scaled time since the start
    float m_unk260;            // +0x260 +0x25c when the fade-out started
    uint8_t m_unk264;          // +0x264 the shadow node faded in
    uint8_t m_pad265[3];
    uint32_t m_unk268;         // +0x268 the fade-out's start alpha (StopFx)
    CKSound* m_unk26c;         // +0x26c the loop sound
    CKSound* m_unk270;         // +0x270 the dash sound
};
static_assert(CKShadowSurprise::kClassKey == 0xa4cc, "key");
DOTD_ASSERT_SIZE(CKShadowSurprise, 0x274);
DOTD_ASSERT_OFFSET(CKShadowSurprise, m_unk154, 0x154);
DOTD_ASSERT_OFFSET(CKShadowSurprise, m_unk160, 0x160);
DOTD_ASSERT_OFFSET(CKShadowSurprise, m_unk178, 0x178);
DOTD_ASSERT_OFFSET(CKShadowSurprise, m_unk19c, 0x19c);
DOTD_ASSERT_OFFSET(CKShadowSurprise, m_unk1a8, 0x1a8);
DOTD_ASSERT_OFFSET(CKShadowSurprise, m_unk1cc, 0x1cc);
DOTD_ASSERT_OFFSET(CKShadowSurprise, m_unk1d4, 0x1d4);
DOTD_ASSERT_OFFSET(CKShadowSurprise, m_unk1ec, 0x1ec);
DOTD_ASSERT_OFFSET(CKShadowSurprise, m_unk1fc, 0x1fc);
DOTD_ASSERT_OFFSET(CKShadowSurprise, m_unk20c, 0x20c);
DOTD_ASSERT_OFFSET(CKShadowSurprise, m_unk230, 0x230);
DOTD_ASSERT_OFFSET(CKShadowSurprise, m_unk234, 0x234);
DOTD_ASSERT_OFFSET(CKShadowSurprise, m_unk24c, 0x24c);
DOTD_ASSERT_OFFSET(CKShadowSurprise, m_unk250, 0x250);
DOTD_ASSERT_OFFSET(CKShadowSurprise, m_unk208, 0x208);
DOTD_ASSERT_OFFSET(CKShadowSurprise, m_unk1e8, 0x1e8);
DOTD_ASSERT_OFFSET(CKShadowSurprise, m_unk270, 0x270);
DOTD_ASSERT_OFFSET(CKShadowSurprise, m_unk268, 0x268);
DOTD_ASSERT_OFFSET(CKShadowSurprise, m_unk264, 0x264);
DOTD_ASSERT_OFFSET(CKShadowSurprise, m_unk254, 0x254);
