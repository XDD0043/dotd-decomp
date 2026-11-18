// CKS08HeroElementElectric.h - the electric hero element (key 0x8a0c, vtable 0xb24150, size 0x3a4). Original unit:
// CKS08HeroElementElectric.cpp (0x3cb878-0x3cff48). C2.8 port-final F08. No XXL2 class of this name: the members keep
// placeholder names. No level file of DotD holds one (CKS08HeroElement.h).
//
// Side A (vt+0x68 / vt+0x74): a charged cast. Starting it spawns an explosion (+0x338), acquires four electric arcs
// (+0x340.. -> +0x350..) and two sparks (+0x364 / +0x368 -> +0x36c / +0x370); while it runs, each arc is thrown at
// random around the hot spot (UpdateRandomArc, a timer each +0x318..), the cast repeats +0x2dc[level] times
// (TryCast: mana, the damage block's damage plus the charge +0x37c) and holding action 5 charges it (+0x378 presses
// up to +0x30c raise +0x37c while below +0x2ec[level]); vt+0x7c ends it (sparks off, explosion +0x33c).
// Side B (vt+0x6c / vt+0x78 / vt+0x80): two arcs (+0x380 / +0x384 -> +0x388 / +0x38c) between hot spots 0x14 / 0x15
// and from hot spot 1 to the grabbed enemy (within +0x394[level]) or along the aim, faded in and out over +0x390.
//
// BUG(original): nothing sets the sphere mesh +0x360 (PostLoad clears it), so with +0x334 set vt+0x68 / vt+0x7c and
// UpdateSphereVisual would read through a null node. Natively the node part is skipped when it is null.
#pragma once
#include <cstdint>

#include "Spyro2008/logic/CKS08HeroElement.h"

class CNode;

class CKS08HeroElementElectric : public CKS08HeroElement {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x228)
    // vt+0x08 0x009c0410 CKS08HeroElementElectric_IsKindOfClass
    int32_t IsKindOfClass(uint32_t key) override {
        return (key == 0x8a0c || key == 0x890c) ? 1 : (key == 0xc ? 1 : 0);
    }
    DOTD_DECLARE_FACTORIES(CKS08HeroElementElectric)

    CKS08HeroElementElectric() {}  // inlined in 0x003cc038 CKS08HeroElementElectric_Create: the vtable only
    // 0x009c0460 Destructor / 0x009c0480 DeletingDestructor: the base's vtables back, nothing freed.
    ~CKS08HeroElementElectric() override {}
    void Destroy() override;                            // vt+0x10 0x003cbe38: the base's
    void RecursiveRegistration(int32_t type) override;  // vt+0x24 0x003cbe10: the base's, then 1
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x003ccda8
    int32_t PostLoad(int32_t type) override;            // vt+0x30 0x003cc560

    // vt+0x68 0x003cfd90 CKS08HeroElementElectric_vf68: the cast's timer 0.5 / (+0x2dc[level] + 1); when not casting
    // yet the arcs dropped, the charge reset, the sphere shown, the arc timers -1, SpawnFx and the sparks on; casting,
    // +0x2dc[level] casts left.
    void StartRepeatFire(int8_t level) override;
    // vt+0x6c 0x003cebe0 CKS08HeroElementElectric_vf6C: side B's arcs on, the hero's target validated.
    void StartBeam(float speed, int8_t level) override;
    // vt+0x74 0x003ccb08 CKS08HeroElementElectric_UpdateRepeatCast_maybe
    void UpdateRepeatFire(float dt, int8_t level) override;
    // vt+0x78 0x003cc330 CKS08HeroElementElectric_Update_maybe: side B's channel (the base's mana per second), 1 when
    // it ended (no hero, past +0x390 without a grabbed enemy, or out of mana); else its arcs updated and 0.
    int32_t UpdateChannel(float dt, float speed, float scale, uint8_t level) override;
    // vt+0x7c 0x003cfd20 CKS08HeroElementElectric_vf7C: the cast ended: the sphere hidden, the sparks off, SpawnFx2.
    void Vf7C() override;
    void StopBeam(uint8_t level) override;   // vt+0x80 0x003cebd8: SetArcFxActive(level, 0)
    uint8_t Vf138() override { return 1; }   // vt+0x138 0x009c0458

    // 0x003cb918 CKS08HeroElementElectric_UpdateArcEndpoints: arc +0x388 from the hero's hot spot 0x14 to 0x15.
    void UpdateArcEndpoints();
    // 0x003cbb00 CKS08HeroElementElectric_UpdateSphereVisual_maybe: the sphere +0x360 scaled (+0x2cc[level] / +0x330
    // with a random +-+0x32c) and faded with the cast's progress (+0x2fc[level]).
    void UpdateSphereVisual(float dt, uint8_t level);
    // 0x003cc070 CKS08HeroElementElectric_UpdateArcFxFade_maybe: arc +0x38c from the hot spot 1 to the grabbed enemy
    // (within +0x394[level]) or +0x394[level] along the aim, its end alphas faded over +0x390.
    void UpdateArcFxFade(float dt, uint8_t level);
    // 0x003cc5e0 CKS08HeroElementElectric_UpdateRandomArc_maybe: when `timer` has run out, a new one (+0x310 +-
    // +0x314) and `arc` thrown from the hot spot +0x80 in a random direction (+0x2cc[level] long) to the hero's
    // targeting position pushed out 1.5 .. 2.5 x +0x2cc[level] in x / z.
    void UpdateRandomArc(IKFx* arc, uint8_t level, float* timer);
    // 0x003cc8d0 CKS08HeroElementElectric_TryCast_maybe: with the hero and mana for `level` (else vt+0x60): the mana
    // spent, damage block A's damage the level's plus the charge, the cast's time restarted.
    void TryCast(float dt, uint8_t level);
    // 0x003cec70 CKS08HeroElementElectric_SpawnFx_maybe / 0x003ce3f8 _SpawnFx_2_maybe: an explosion of +0x338 / +0x33c
    // at the hero (as CKS08HeroElementEarth's SpawnFx).
    void SpawnFx();
    void SpawnFx2();
    // 0x003ce6b8 CKS08HeroElementElectric_SetArcFxActive_maybe: side B's arcs acquired (the second at alpha 0) or
    // stopped and let go.
    void SetArcFxActive(uint8_t level, uint8_t on);
    // 0x003cef30 CKS08HeroElementElectric_SetSparkFxActive_maybe: side A's four arcs and two sparks (under the hero's
    // hot spot 0x12) acquired, or stopped and let go.
    void SetSparkFxActive(uint8_t on);

    float m_unk2cc[4];          // +0x2cc the arcs' reach of each level (and the sphere's scale)
    int32_t m_unk2dc[4];        // +0x2dc the casts of each level
    int32_t m_unk2ec[4];        // +0x2ec the charge limit of each level
    int32_t m_unk2fc[4];        // +0x2fc the sphere's alpha of each level
    int32_t m_unk30c;           // +0x30c the presses of action 5 per charge step
    float m_unk310;             // +0x310 the random arcs' period
    float m_unk314;             // +0x314 the random arcs' period spread
    float m_unk318[4];          // +0x318 the random arcs' timers
    float m_unk328;             // +0x328 the time since the cast (or side B) started
    float m_unk32c;             // +0x32c the sphere's scale spread
    float m_unk330;             // +0x330 the sphere's scale divisor
    uint8_t m_unk334;           // +0x334 with the sphere
    uint8_t m_pad335[3];
    IKSerializable* m_unk338;   // +0x338 reference: the cast's explosion (SpawnFx)
    IKSerializable* m_unk33c;   // +0x33c reference: the end explosion (SpawnFx2)
    IKSerializable* m_apUnk340[4];  // +0x340 references: side A's arc data (CKElectricArcFxData)
    IKFx* m_apUnk350[4];        // +0x350 side A's arcs (CKElectricArcNodeFx)
    CNode* m_unk360;            // +0x360 the sphere (PostLoad 0; see the BUG above)
    IKSerializable* m_unk364;   // +0x364 reference: a spark (CKSparkFxData)
    IKSerializable* m_unk368;   // +0x368 reference: a spark (CKSparkFxData)
    IKFx* m_unk36c;             // +0x36c the sparks acquired (CKSparkNodeFx)
    IKFx* m_unk370;             // +0x370
    uint8_t m_unk374;           // +0x374 casting
    uint8_t m_pad375[3];
    int32_t m_unk378;           // +0x378 the presses of action 5 since the last charge step
    int32_t m_unk37c;           // +0x37c the charge
    IKSerializable* m_unk380;   // +0x380 reference: side B's first arc data
    IKSerializable* m_unk384;   // +0x384 reference: side B's second arc data
    IKFx* m_unk388;             // +0x388 side B's arcs (CKElectricArcNodeFx)
    IKFx* m_unk38c;             // +0x38c
    float m_unk390;             // +0x390 side B's duration (its fade in / out takes half each)
    float m_unk394[4];          // +0x394 side B's reach of each level
};
DOTD_ASSERT_SIZE(CKS08HeroElementElectric, 0x3a4);
DOTD_ASSERT_OFFSET(CKS08HeroElementElectric, m_unk2cc, 0x2cc);
DOTD_ASSERT_OFFSET(CKS08HeroElementElectric, m_unk30c, 0x30c);
DOTD_ASSERT_OFFSET(CKS08HeroElementElectric, m_unk318, 0x318);
DOTD_ASSERT_OFFSET(CKS08HeroElementElectric, m_unk334, 0x334);
DOTD_ASSERT_OFFSET(CKS08HeroElementElectric, m_apUnk350, 0x350);
DOTD_ASSERT_OFFSET(CKS08HeroElementElectric, m_unk360, 0x360);
DOTD_ASSERT_OFFSET(CKS08HeroElementElectric, m_unk374, 0x374);
DOTD_ASSERT_OFFSET(CKS08HeroElementElectric, m_unk380, 0x380);
DOTD_ASSERT_OFFSET(CKS08HeroElementElectric, m_unk394, 0x394);
