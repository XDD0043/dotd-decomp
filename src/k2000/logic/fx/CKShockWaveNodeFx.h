// CKShockWaveNodeFx.h - the shockwave effect node (key 0x30cc, vtable 0xb1d808, size 0x58). Original unit:
// CKShockWaveNodeFx.cpp (0x1d22e8-0x1d3400). Its data is CKShockWaveFxData (0x310c). Not in XXL2; names ours.
// Load reads only the IKNodeFx part; everything else is set at run time.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/fx/IKNodeFx.h"
#include "k2000/math/CMatrix34.h"

class CKShockWaveNodeFx : public IKNodeFx {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0xc3)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9ad220
        return key == 0x30cc || key == 0x148c || key == 0x154c || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKShockWaveNodeFx)

    CKShockWaveNodeFx() {}  // inlined in 0x001d2648 CKShockWaveNodeFx_Create: the IKNodeFx part only
    ~CKShockWaveNodeFx() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001d24b0 CKShockWaveNodeFx_Load
    void RecursiveRegistration(int32_t type) override;  // vt+0x24 0x001d2500 CKShockWaveNodeFx_RecursiveRegistration
    // vt+0x30 0x001d2338 CKShockWaveNodeFx_PostLoad: the colour white (0x00c50dfc); the node's first geometry gets render
    // flags 0x2f in its low six bits.
    int32_t PostLoad(int32_t type) override;
    IKFxData* GetFxData() override { return reinterpret_cast<IKFxData*>(m_pFxData); }                   // vt+0x80 0x9ad268
    void SetFxData(IKFxData* data) override { m_pFxData = reinterpret_cast<IKSerializable*>(data); }  // vt+0x84 0x9ad270
    // vt+0x64 0x001d2718 CKShockWaveNodeFx_Start: not stopped nor triggered, no damage sphere or owner, the radius 0.01, no
    // direction, the data's colour (+0x40).
    void Vf64() override;
    // vt+0x6c 0x001d2770 CKShockWaveNodeFx_Stop: stopped, the damage sphere released, no owner nor direction, hidden.
    void Stop() override;
    // vt+0x78 0x001d2d70 CKShockWaveNodeFx_Update: while triggered: the time on (stopped at the data's duration); the
    // material's U scroll (data +0x0c, the blend modes 5, 6, 11..14, kept in [-1, 1]); the node turned to the camera (data
    // +0x30 bit 2: up = -camera at, at = the camera's right / up mix by +0x50) or to the direction (+0x38, side +0x44;
    // none: the rotation reset); scaled by the data's radius / height keys; the damage sphere at the node, growing to the
    // data's +0x34 at its +0x38 rate; the colour with the alpha key (its blend flag 0x800 kept in step).
    void Update(IKTime* frameClock) override;
    // 0x001d2928 CKShockWaveNodeFx_Trigger (the owner's): triggered and shown; with a damage owner (+0x2c) a projectile
    // sphere (radius 0.1, the owner type +0x30, the flags +0x32, the data's damage +0x3c) under the dynamic scene root at
    // the node; the material's UV offset cleared; +0x50 a random (0, 1].
    void Trigger(const IKSerializable* owner);
    // 0x001d2cd0 CKShockWaveNodeFx_SetPosition / 0x001d2410 FxAttachment_SetPositionIfOwner_maybe (the same body): the
    // node's position.
    void SetPosition(const CVector3* position, const IKSerializable* owner);
    // 0x001d3340 CKShockWaveNodeFx_SetDirection_maybe: the direction (+0x38) normalised, +0x50 a random (0, 1]; not straight
    // up: the side (+0x44) = direction x Y turned about the direction by +0x50 (direction x side x +0x50 + side),
    // normalised; straight up: no direction.
    void SetDirection(const CVector3* direction, const IKSerializable* owner);
    // 0x001d26a0 / 0x001d26c8 / 0x001d26f0 CKShockWaveNodeFx_SetDamageFlags / _SetDamageType / _SetDamageOwner.
    void SetDamageFlags(uint16_t flags, const IKSerializable* owner);
    void SetDamageType(uint8_t type, const IKSerializable* owner);
    void SetDamageOwner(IKSerializable* damageOwner, const IKSerializable* owner);

    float m_fElapsed;            // +0x14 the time since the trigger
    IKSerializable* m_pFxData;   // +0x18 a CKShockWaveFxData (the inline GetFxData 0x9ad268 returns it)
    uint32_t m_unk1c[3];         // +0x1c not set by Load
    class CKDynamicBoundingSphere* m_pDamageSphere;  // +0x28 the collision service's projectile sphere (Trigger)
    IKSerializable* m_pDamageOwner;  // +0x2c the sphere's owner; none: no sphere
    uint8_t m_ui8DamageType;     // +0x30 the sphere's owner type
    uint8_t m_pad31;
    uint16_t m_ui16DamageFlags;  // +0x32 the sphere's property flags
    float m_fRadius;             // +0x34 the sphere's radius
    CVector3 m_v3Direction;      // +0x38 (SetDirection; Start / Stop: the null vector)
    CVector3 m_v3Side;           // +0x44
    float m_fRandom;             // +0x50 (Trigger, SetDirection)
    int32_t m_unk54;             // +0x54 the colour, raw bytes (PostLoad white, Start the data's +0x40)
};
static_assert(CKShockWaveNodeFx::kClassKey == 0x30cc, "key");
DOTD_ASSERT_SIZE(CKShockWaveNodeFx, 0x58);
DOTD_ASSERT_OFFSET(CKShockWaveNodeFx, m_pFxData, 0x18);
DOTD_ASSERT_OFFSET(CKShockWaveNodeFx, m_unk54, 0x54);
