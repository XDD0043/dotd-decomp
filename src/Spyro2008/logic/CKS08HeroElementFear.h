// CKS08HeroElementFear.h - the fear hero element (key 0x8a4c, vtable 0xb24298, size 0x2e4). Original unit:
// CKS08HeroElementFear.cpp (0x3cff48-0x3d0f88). C2.8 port-final F08. No XXL2 class of this name: the members keep
// placeholder names. No level file of DotD holds one (CKS08HeroElement.h).
//
// Its repeated shot (vt+0x74) is a cast instead of a projectile: the mana of the level spent, the active enemies inside
// a cone along the hero's hot spot 4 direction (within +0x50[level] in x / z and 2.0 in y) asked for (the result of
// vt+0xfc is not used), the cast spark (+0x2dc) under the hero's hot spot 0x12 and the quake (+0x2e0) triggered.
#pragma once
#include <cstdint>

#include "Spyro2008/logic/CKS08HeroElement.h"

class CKS08HeroElementFear : public CKS08HeroElement {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x229)
    // vt+0x08 0x009c04c8 CKS08HeroElementFear_IsKindOfClass
    int32_t IsKindOfClass(uint32_t key) override {
        return (key == 0x8a4c || key == 0x890c) ? 1 : (key == 0xc ? 1 : 0);
    }
    DOTD_DECLARE_FACTORIES(CKS08HeroElementFear)

    CKS08HeroElementFear() {}  // inlined in 0x003d0588 CKS08HeroElementFear_Create: the vtable only
    // 0x009c0510 Destructor / 0x009c0530 DeletingDestructor: the base's vtables back, nothing freed.
    ~CKS08HeroElementFear() override {}
    void Destroy() override;                            // vt+0x10 0x003d0388: the base's
    void RecursiveRegistration(int32_t type) override;  // vt+0x24 0x003d0360: the base's, then 1
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x003d0a90
    int32_t PostLoad(int32_t type) override;            // vt+0x30 0x003d05c0: the base's, then 1

    // vt+0x74 0x003d09c8 CKS08HeroElementFear_UpdateRepeatCast_maybe: the base's repeat timer with TryCast instead of
    // FireProjectile.
    void UpdateRepeatFire(float dt, int8_t level) override;

    // 0x003d08a0 CKS08HeroElementFear_TryCast_maybe: with the hero and mana for `level` (else vt+0x60): the mana spent,
    // AffectEnemiesInCone, PlayCastFx.
    void TryCast(uint8_t level);
    // 0x003d0148 CKS08HeroElementFear_AffectEnemiesInCone_maybe: each active enemy within 2.0 in y of the hot spot 0x12
    // and inside the aim cone (IsPointInAimCone) gets vt+0xfc called (GetDamageA; its result is dropped).
    void AffectEnemiesInCone(uint8_t level);
    // 0x003cff48 CKS08HeroElement_IsPointInAimCone_maybe (Fear's: it reads +0x2cc): `point` within +0x50[level] of
    // `origin` in x / z and within half the angle +0x2cc[level] (degrees) of the hero's hot spot 4 direction.
    uint8_t IsPointInAimCone(const CVector3* point, const CVector3* origin, int8_t level);
    // 0x003d05e8 CKS08HeroElementFear_PlayCastFx_maybe: the spark +0x2dc hung under the hero's hot spot 0x12 and
    // acquired (the inlined CKSrvFx::AcquireFx; the effect is not kept), then the quake +0x2e0 triggered.
    void PlayCastFx();

    float m_unk2cc[4];          // +0x2cc the cone angle of each level (degrees)
    IKSerializable* m_unk2dc;   // +0x2dc reference: the cast spark (CKSparkFxData)
    IKSerializable* m_unk2e0;   // +0x2e0 reference: the quake (CKQuakeCameraLauncher)
};
DOTD_ASSERT_SIZE(CKS08HeroElementFear, 0x2e4);
DOTD_ASSERT_OFFSET(CKS08HeroElementFear, m_unk2cc, 0x2cc);
DOTD_ASSERT_OFFSET(CKS08HeroElementFear, m_unk2e0, 0x2e0);
