// CKExplosionNodeFx.h - the explosion effect node (key 0x1a4c, vtable 0xb1ca38, size 0x50). Original unit:
// CKExplosionNodeFx.cpp (0x1b5d98-0x1b8ab0). Its data is CKExplosionFxData (0x1a8c). Not in XXL2; names ours.
//
// The sub-effects (+0x20) are 12-byte records: a value and, when the value is not positive, an object
// reference (LVL010: CKSrvFxParticlesAccessor). CountSubEffectsOfType / GetNthSubEffectOfType
// (0x1b64a0/0x1b6530) _maybe read the value as a type.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/fx/IKNodeFx.h"
#include "k2000/logic/fx/CKExplosionFxData.h"
#include "k2000/util/TVector.h"

struct RwMatrix;
class CKDynamicBoundingSphere;
struct CVector3;

class CKExplosionNodeFx : public IKNodeFx {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x69)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9abc08
        return key == 0x1a4c || key == 0x148c || key == 0x154c || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKExplosionNodeFx)

    // One per part of the FX data (the same index): the part's type and, for the types that need one, its object.
    struct SubEffect {
        IKSerializable* m_pObject;  // +0x00 read when m_value <= 0, else set to null (type 0: a CKSrvFxParticlesAccessor)
        int32_t m_value;            // +0x04 the type (FireSubEffect's switch: 0..8)
        uint8_t m_bFired;           // +0x08 runtime: Trigger clears it, FireSubEffect sets it
        uint8_t m_pad09[3];
    };

    CKExplosionNodeFx();  // inlined in 0x001b6150 CKExplosionNodeFx_Create
    ~CKExplosionNodeFx() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001b6940 CKExplosionNodeFx_Load
    // vt+0x24 0x001b61c0 CKExplosionNodeFx_RecursiveRegistration: registered with the saving manager whatever the type,
    // then every sub-effect object of a type not above 0 (a byte index, as in the original).
    void RecursiveRegistration(int32_t type) override;
    // 0x001b64a0 CKExplosionNodeFx_CountSubEffectsOfType_maybe: for the owner that reserved the node (+0x0c bit 1, +0x08),
    // the number of sub-effects of `type`; 0 otherwise.
    int32_t CountSubEffectsOfType(uint32_t type, const IKSerializable* owner) const;
    // 0x001b6530 CKExplosionNodeFx_GetNthSubEffectOfType_maybe: for the owner that reserved the node and a type above 1,
    // the object of the FX data's part whose sub-effect is the n-th of `type` (n from 0); null otherwise.
    IKSerializable* GetNthSubEffectOfType(uint32_t type, const IKSerializable* owner, int32_t n) const;
    // vt+0x30 0x001b5fd8 CKExplosionNodeFx_PostLoad: IKNodeFx's, the colour white (0x00c50dfc), then Stop (vt+0x6c).
    int32_t PostLoad(int32_t type) override;
    void Destroy() override;  // vt+0x10 0x001b6068 CKExplosionNodeFx_Destroy: the matrix destroyed
    // vt+0x64 0x001b65f0 CKExplosionNodeFx_Start: active-pending, the matrix the identity; without data stopped, else
    // the run-time state reset and the duration (data +0x08) and colour (data +0x38) taken.
    void Vf64() override;
    // vt+0x6c 0x001b6740 CKExplosionNodeFx_Stop: the damage sphere released, the pad vibration stopped, stopped.
    void Stop() override;
    // vt+0x78 0x001b8288 CKExplosionNodeFx_Update: while triggered (bit 2), UpdateActive.
    void Update(IKTime* frameClock) override;
    IKFxData* GetFxData() override { return reinterpret_cast<IKFxData*>(m_pFxData); }      // vt+0x80 0x9abc50
    void SetFxData(IKFxData* data) override { m_pFxData = reinterpret_cast<IKSerializable*>(data); }  // vt+0x84 0x9abc58

    // The owner's setters (not virtual): each only for the owner that reserved the node (bit 1, +0x08).
    // 0x001b66e8 CKExplosionNodeFx_SetTranslation: the matrix's position.
    void SetTranslation(const CVector3* position, const IKSerializable* owner);
    // 0x001b5e20 CKExplosionNodeFx_SetDirection: the matrix turned to `direction` (normalised, its at): up = at x the
    // reference axis (X when the direction is within 0.99 of vertical, else Y), right = up x at; the flags' bits 0, 1
    // and 17 cleared.
    void SetDirection(const CVector3* direction, const IKSerializable* owner);
    // 0x001b6438 CKExplosionNodeFx_SetPosition: the matrix's position, then turned to `direction` (SetDirection).
    void SetPosition(const CVector3* direction, const CVector3* position, const IKSerializable* owner);
    // 0x001b6368 CKExplosionNodeFx_SetMatrix: the whole matrix.
    void SetMatrix(const RwMatrix* matrix, const IKSerializable* owner);
    // 0x001b6318 CKExplosionNodeFx_SetDamageCategory / 0x001b62f0 _SetDamageFlags: the damage sphere's owner type and
    // property flags.
    void SetDamageCategory(uint8_t category, const IKSerializable* owner);
    void SetDamageFlags(uint16_t flags, const IKSerializable* owner);
    // 0x001b6340 CKExplosionNodeFx_SetDamageOwner / 0x001b62c8 _SetDamage: the damage sphere's owner (+0x30) / damage (+0x40).
    void SetDamageOwner(IKSerializable* damageOwner, const IKSerializable* owner);
    void SetDamage(IKSerializable* damage, const IKSerializable* owner);
    // 0x001b82a8 CKExplosionNodeFx_Trigger: the explosion goes off at the matrix's position: a random sound of the
    // data's dictionary (one rand draw), the damage sphere (with a damage owner), the sub-effects due at time 0, the pad
    // vibration and the camera quake. `launch` is kept for the projectile sub-effects (+0x44).
    void Trigger(const IKSerializable* owner, const void* launch);

private:
    // 0x001b7fa8 CKExplosionNodeFx_UpdateActive_maybe: stopped once the duration is over and every sub-effect fired;
    // else the time advanced, the sub-effects due fired and the damage sphere grown.
    void UpdateActive(IKTime* frameClock);
    // 0x001b6c20 CKExplosionNodeFx_FireSubEffect: one sub-effect by its type (the record marked fired first).
    void FireSubEffect(SubEffect* effect, CKExplosionFxData::Part* part);
public:

    IKSerializable* m_pFxData;        // +0x14 a CKExplosionFxData (GetFxData 0x9abc50); Load sets 0 (every type)
    float m_fDuration;                // +0x18 Start: the data's +0x08
    float m_fElapsed;                 // +0x1c the time since the trigger; Load sets 0 (every type)
    TVector<SubEffect, 10> m_subEffects;  // +0x20 the constructor: null, 10, 0
    CKDynamicBoundingSphere* m_pDamageSphere;  // +0x2c the collision service's projectile sphere; Load sets 0
    IKSerializable* m_pDamageOwner;   // +0x30 the sphere's owner (+0x24); none: no sphere. Load / Start / Stop clear it
    RwMatrix* m_pMatrix;              // +0x34 Load (type 0): RwMatrixCreate
    float m_fDamageRadius;            // +0x38 the sphere's radius (Trigger: 0.1, grown by UpdateActive)
    uint8_t m_ui8DamageCategory;      // +0x3c the sphere's owner type (+0x19)
    uint8_t m_pad3d;
    uint16_t m_ui16DamageFlags;       // +0x3e or-ed into the sphere's property flags (+0x1a)
    IKSerializable* m_pDamage;        // +0x40 the sphere's +0x1c (a CKS08Damage); Load / Start / Stop clear it
    const void* m_unk44;              // +0x44 Trigger's `launch` (a matrix, e.g. a node's LTM): the projectile sub-effects launch with it
    uint8_t m_aColor[4];              // +0x48 RGBA (PostLoad: white, 0x00c50dfc; Start: the data's +0x38)
    const IKSerializable* m_pTriggerOwner;  // +0x4c Trigger: the owner then; Start clears it
};
static_assert(CKExplosionNodeFx::kClassKey == 0x1a4c, "key");
DOTD_ASSERT_SIZE(CKExplosionNodeFx::SubEffect, 0xc);
DOTD_ASSERT_SIZE(CKExplosionNodeFx, 0x50);
DOTD_ASSERT_OFFSET(CKExplosionNodeFx, m_pFxData, 0x14);
DOTD_ASSERT_OFFSET(CKExplosionNodeFx, m_fElapsed, 0x1c);
DOTD_ASSERT_OFFSET(CKExplosionNodeFx, m_subEffects, 0x20);
DOTD_ASSERT_OFFSET(CKExplosionNodeFx, m_pDamageSphere, 0x2c);
DOTD_ASSERT_OFFSET(CKExplosionNodeFx, m_ui16DamageFlags, 0x3e);
DOTD_ASSERT_OFFSET(CKExplosionNodeFx, m_pTriggerOwner, 0x4c);
DOTD_ASSERT_OFFSET(CKExplosionNodeFx, m_pMatrix, 0x34);
DOTD_ASSERT_OFFSET(CKExplosionNodeFx, m_pDamage, 0x40);
