// CKElectricSphere.h - the electric sphere attack (key 0x964c, vtable 0xb23888, size 0x334). Original unit: CKElectricSphere.cpp
// (0x396748-0x39cf88). Derives from CKTransformElement (its Load is called first). No XXL2 class of this name: the
// members keep placeholder names (types from the Ghidra struct and the level data). Unread runtime state is padding.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/CKTransformElement.h"
#include "k2000/math/CMatrix34.h"

class CKElectricSphere : public CKTransformElement {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x259)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9bfca0
        return key == 0x964c || key == 0xc || key == 0x954c || key == 0x90cc;
    }
    DOTD_DECLARE_FACTORIES(CKElectricSphere)

    CKElectricSphere() {}  // 0x00396c10 CKElectricSphere_Construct: CKTransformElement's constructor, then the vtable only
    ~CKElectricSphere() override {}
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00397348 CKElectricSphere_Load
    // vt+0x30 0x00396b58 CKElectricSphere_PostLoad: the base's (ResetRuntime), then the two sphere nodes hidden in the
    // sector 0 root (SceneNode_SetVisibleInLayer_maybe 0x5832a8).
    int32_t PostLoad(int32_t type) override;
    void ResetRuntime() override;  // vt+0x6c 0x00396a90 CKElectricSphere_ResetRuntime
    uint8_t GetAbilityId() override { return 6; }    // vt+0x50 0x00396798
    uint8_t GetFamilyId() override { return 0x17; }  // vt+0x54 0x003967a0
    // vt+0x58 0x00396e70 CKElectricSphere_Start: the sounds cleared, the base's Start, the sphere node (+0x224) shown at
    // alpha 0 and hung under the user's hot spot +0x13c, the dash (+0x18c) cleared, the run-time words reset, the first
    // explosion's interval drawn (one Rand_Int).
    void Start(CKS08AbilityHostBase* host) override;
    // vt+0x64 0x00396998 CKElectricSphere_End: the sounds stopped, the hero's +0x1d20 back to 1, the base's End, both
    // nodes hidden in the sector 0 root.
    void End(int32_t forced) override;
    void ApplyHeroControl(uint8_t on) override;  // vt+0x68 0x003968c8: the base's, then action 3
    // vt+0x7c 0x0039a0c0 CKElectricSphere_UpdateAttack_maybe: above level 0, the dash: button 3 kicks the impulse
    // component and spins the burst node (+0x228, six Rand_Int draws); level 2 also fires an explosion (+0x200[2], one
    // more draw for the next interval). The dash's value scales the hero (host vt+0x84).
    void UpdateAttack(float dt) override;
    // vt+0x74 0x0039a798 CKElectricSphere_UpdateEffect_maybe: the pulse (the attack sphere on for one frame each period
    // +0x160, the damage set up), the dash sound's pitch, the sphere node's scale and alpha (one Rand_Int), the four
    // electric arcs turning about the user (one draw each) or made anew (six draws each), the burst node's flicker,
    // level 2's dash explosion, the animated collection, the timed explosion (one draw for the next interval).
    void UpdateEffect(float dt) override;
    // vt+0x84 0x00397130 CKElectricSphere_StopFx: the base's, the growth timer kept (+0x298), both nodes hidden, the
    // attack sphere off, the hero's +0x1d20 back to 1.
    void StopFx() override;
    // vt+0x70 0x0039bd78 CKElectricSphere_SetFxActive: on: above level 0 the loop particles (+0x268), the start explosion
    // (+0x1ec), the two sparks (+0x1dc / +0x1e0 on hot spot 2), the level's animated collection (+0x280 / +0x284), the
    // level's point light (+0x270), the sounds; off: when the particles ran, the stop explosion (+0x1f0), then every
    // effect (the sparks, the four arcs, the collection, the light) and the sounds released.
    void SetFxActive(int32_t on) override;
    // 0x003967a8 CKElectricSphere_GetFxSound_maybe (not virtual): `which` 1: the loop sound (dictionary 0); 3: the dash
    // sound (1 or 2, level 1 and up), a level's own sound only when it is there and has a sample.
    class CKSound* GetFxSound(uint32_t which);

    // The per-level arrays are indexed by the level index (m_levelIndex, 0..2); the level data stores one level's
    // record after the other (Load).
    float m_unk154[3];                  // +0x154 the attack sphere's radius (UpdateEffect: the pulse, host vt+0xfc)
    float m_unk160[3];                  // +0x160 the pulse period (Start: +0x294 = half of it)
    int32_t m_unk16c[3];                // +0x16c the sphere node's top alpha
    float m_unk178;                     // +0x178 the sphere node's random scale spread
    float m_unk17c;                     // +0x17c the arcs' start radius, times the sphere node's scale
    float m_unk180[3];                  // +0x180 the sphere node's scale
    IKSerializable* m_unk18c;           // +0x18c (reference; Ghidra: CKImpulsionCpnt *) the dash
    float m_unk190[3];                  // +0x190 a new arc's turn speed: base
    float m_unk19c[3];                  // +0x19c a new arc's turn speed: spread
    float m_unk1a8[3];                  // +0x1a8 a new arc's start direction height: base
    float m_unk1b4[3];                  // +0x1b4 a new arc's start direction height: spread
    float m_unk1c0[3];                  // +0x1c0 a new arc's end reach: base
    float m_unk1cc[3];                  // +0x1cc a new arc's end reach: spread
    float m_unk1d8;                     // +0x1d8 the arcs run while the dash value (+0x29c) is above it
    IKSerializable* m_unk1dc;           // +0x1dc (reference)
    IKSerializable* m_unk1e0;           // +0x1e0 (reference)
    IKSerializable* m_unk1e4;           // +0x1e4 runtime: the first spark effect (ResetRuntime null)
    IKSerializable* m_unk1e8;           // +0x1e8 runtime: the second spark effect (ResetRuntime null)
    IKSerializable* m_unk1ec;           // +0x1ec (reference; Ghidra: CKExplosionFxData *)
    IKSerializable* m_unk1f0;           // +0x1f0 (reference; Ghidra: CKExplosionFxData *)
    IKSerializable* m_unk1f4;           // +0x1f4 (reference; Ghidra: CKExplosionFxData *) level 2's dash explosion
    float m_unk1f8;                     // +0x1f8 the time near the top dash value before level 2's dash explosion
    IKSerializable* m_unk1fc;           // +0x1fc (reference; Ghidra: CKS08ElementDamage *) that explosion's damage
    IKSerializable* m_unk200[3];        // +0x200 (references; Ghidra: CKExplosionFxData *) the timed explosion, per level
    float m_unk20c[3];                  // +0x20c the explosion interval's base, per level
    float m_unk218[3];                  // +0x218 the explosion interval's spread, per level
    IKSerializable* m_unk224;           // +0x224 (reference; Ghidra: CNode *) the sphere node
    IKSerializable* m_unk228;           // +0x228 (reference; Ghidra: CNode *) the burst node
    float m_unk22c;                     // +0x22c the burst's duration
    float m_unk230;                     // +0x230 the burst's start scale: base
    float m_unk234;                     // +0x234 the burst's start scale: spread
    float m_unk238;                     // +0x238 the burst's end scale: base
    float m_unk23c;                     // +0x23c the burst's end scale: spread
    float m_unk240[3];                  // +0x240 the burst's scale factor, per level
    IKSerializable* m_unk24c[3];        // +0x24c (references; Ghidra: CKElectricArcFxData *) the arcs' data ([0], [1] used)
    IKSerializable* m_unk258[4];        // +0x258 runtime: the four arc effects (ResetRuntime null)
    IKSerializable* m_unk268;           // +0x268 (reference)
    IKSerializable* m_unk26c;           // +0x26c runtime: the loop particles effect (ResetRuntime null)
    IKSerializable* m_unk270[3];        // +0x270 (references; Ghidra: CKPointLightFxData *) per level
    IKSerializable* m_unk27c;           // +0x27c runtime: the light effect (ResetRuntime null)
    IKSerializable* m_unk280;           // +0x280 (reference)
    IKSerializable* m_unk284;           // +0x284 (reference)
    IKSerializable* m_unk288;           // +0x288 runtime: the collection that plays (ResetRuntime null)
    IKSerializable* m_unk28c;           // +0x28c (reference; Ghidra: CKSoundDictionaryID *)
    float m_unk290;                     // +0x290 the dash sound's top pitch
    float m_unk294;                     // +0x294 runtime: the pulse clock (ResetRuntime 0; Start: +0x160[level] x 0.5)
    float m_unk298;                     // +0x298 runtime (ResetRuntime 0)
    float m_unk29c;                     // +0x29c runtime: the dash value, the time scale (ResetRuntime / Start 1.0f)
    uint8_t m_unk2a0;                   // +0x2a0 runtime: the attack sphere is on (ResetRuntime / Start 0)
    uint8_t m_pad2a1[3];
    // +0x2a4..+0x313 runtime, written by UpdateEffect only (arc slot k = 2 x pass + data index); read only once the
    // slot's arc was made (its writer runs first).
    CVector3 m_unk2a4[4];               // +0x2a4 the arcs' start points
    float m_unk2d4[4];                  // +0x2d4 the arcs' turn speeds
    CVector3 m_unk2e4[4];               // +0x2e4 the arcs' end points
    float m_unk314;                     // +0x314 runtime: the burst's time left (ResetRuntime 0)
    float m_unk318;                     // +0x318 runtime: the burst's start scale (ResetRuntime 0)
    float m_unk31c;                     // +0x31c runtime: the burst's end scale (ResetRuntime 0)
    uint8_t m_unk320;                   // +0x320 runtime (ResetRuntime 1)
    uint8_t m_pad321[3];
    float m_unk324;                     // +0x324 runtime: the time near the top dash value (ResetRuntime 0)
    IKSerializable* m_unk328;           // +0x328 runtime: a sound (ResetRuntime null)
    IKSerializable* m_unk32c;           // +0x32c runtime: a sound (ResetRuntime null)
    float m_unk330;                     // +0x330 runtime: the time to the next timed explosion (ResetRuntime 0)
};
DOTD_ASSERT_SIZE(CKElectricSphere, 0x334);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk154, 0x154);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk160, 0x160);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk16c, 0x16c);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk178, 0x178);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk17c, 0x17c);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk180, 0x180);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk18c, 0x18c);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk190, 0x190);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk19c, 0x19c);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk1a8, 0x1a8);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk1b4, 0x1b4);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk1c0, 0x1c0);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk1cc, 0x1cc);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk1d8, 0x1d8);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk1dc, 0x1dc);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk1e0, 0x1e0);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk1ec, 0x1ec);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk1f0, 0x1f0);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk1f4, 0x1f4);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk1f8, 0x1f8);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk1fc, 0x1fc);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk200, 0x200);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk20c, 0x20c);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk218, 0x218);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk224, 0x224);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk228, 0x228);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk22c, 0x22c);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk230, 0x230);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk234, 0x234);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk238, 0x238);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk23c, 0x23c);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk240, 0x240);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk24c, 0x24c);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk258, 0x258);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk268, 0x268);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk270, 0x270);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk280, 0x280);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk284, 0x284);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk28c, 0x28c);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk290, 0x290);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk294, 0x294);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk29c, 0x29c);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk2a0, 0x2a0);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk2a4, 0x2a4);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk2d4, 0x2d4);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk2e4, 0x2e4);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk314, 0x314);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk324, 0x324);
DOTD_ASSERT_OFFSET(CKElectricSphere, m_unk330, 0x330);
