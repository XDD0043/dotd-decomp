// CKProjectileTypeScrap.h - a debris projectile pool (key 0x134c, vtable 0xb2e3c8, size 0x30). Original
// unit: CKProjectileTypeScrap.cpp (0x5929d8-0x596240). Base: IKProjectileType (its Load is called first).
// XXL2 has a class of this name, but DotD loads different data (a word and references, no floats), so the
// members keep placeholder names.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/services/IKProjectileType.h"

struct RwMatrix;

class CSGLeaf;

class CKProjectileTypeScrap : public IKProjectileType {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x4d)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9cb608
        return key == 0x134c || key == 0x130c || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKProjectileTypeScrap)

    // One projectile (0x90 bytes, m_ui8MaxProjectiles of them). Names from the runtime (C2.7): what the launch, the
    // motion, the collision and the kill read and write.
    struct Projectile {
        uint32_t m_ui32Index;                           // +0x00 its index (the Load); also the sound's index in +0x2c
        IKSerializable* m_pOwner;                       // +0x04 the launcher (Load 0); message 0x2802 when killed
        IKSerializable* m_pData;                        // +0x08 CKProjectileDataTypeScrap (the accessor's data)
        CSGLeaf* m_pNode;                               // +0x0c a CNode (file); the Load sets its flag 0x4 (hidden)
        IKSerializable* m_pBody;                        // +0x10 a CKPxBody (file; null in every LVL010 pool)
        CVector3 m_vPos;                                // +0x14 (0, 0, 0)
        CVector3 m_vPrevPos;                            // +0x20 (0, 0, 0) the position before this frame's motion
        CVector3 m_vVelocity;                           // +0x2c the Load copies the Z axis 0xc50d4c (0, 0, 1)
        float m_fSpeed;                                 // +0x38 0; the launch speed, cut by bounces, 0 when stopped
        CVector3 m_vRollAxis;                           // +0x3c the Load copies the X axis 0xc50d34 (1, 0, 0)
        float m_fRollSpeed;                             // +0x48 0; degrees through 57.29578 (data flag 0x2)
        float m_fScale;                                 // +0x4c 1.0
        float m_fAge;                                   // +0x50 0; seconds since the launch
        float m_fLifetime;                              // +0x54 1.0; dies at this age (flag bit 0)
        // +0x58 bit 0 dies at m_fLifetime, bit 1 driven by its body (physics), bit 2 its sound plays, bit 3 landed
        // (stopped on the ground); the Load sets 0.
        uint8_t m_flags58;
        uint8_t m_pad59[3];
        CGroundContactDatasInOut m_GrdContDatasInOut;   // +0x5c the ground under it (GroundProbePoints)
        IKSerializable* m_pFx;                          // +0x88 its particle effect (data flag 0x8); Load 0
        IKSerializable* m_pVolume;                      // +0x8c its CKDynBSphereProjectile; Load 0
    };

    // The constructor inlined in 0x00593078 CKProjectileTypeScrap_Create: IKProjectileType's, then the
    // vtable only.
    CKProjectileTypeScrap() {}
    ~CKProjectileTypeScrap() override {}
    int32_t MessageProc(uint16_t message, void* data) override;  // vt+0x1c 0x00595c08 CKProjectileTypeScrap_MessageProc
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00595e28 CKProjectileTypeScrap_Load
    int32_t PostLoad(int32_t /*type*/) override { return 1; }  // vt+0x30 0x595da8 CKProjectileTypeScrap_PostLoad
    // vt+0x10 0x00595be0 CKProjectileTypeScrap_Destroy: IKProjectileType_Destroy 0x1f3c38 (the two lists freed).
    void Destroy() override;
    // vt+0x24 0x00595db0 CKProjectileTypeScrap_RecursiveRegistration: the base's KStub_Return1_1f3c90 (nothing), then
    // the reference +0x2c recurses with the same type.
    void RecursiveRegistration(int32_t type) override;

    void UpdateMotion(uint8_t index, float dt) override;       // vt+0x50 0x00593120 CKProjectileTypeScrap_UpdateMotion
    void UpdateCollision(uint8_t index, float dt) override;    // vt+0x54 0x005947e0 CKProjectileTypeScrap_UpdateCollision
    uint8_t IsDead(uint8_t index) override;                    // vt+0x58 0x005930d0 CKProjectileTypeScrap_IsDead
    void OnDeath(uint8_t index) override;                      // vt+0x5c 0x005937c8 CKProjectileTypeScrap_OnDeath
    void KillProjectile(uint8_t index) override;               // vt+0x60 0x00593258 CKProjectileTypeScrap_KillInstance
    void UpdateOrientation(uint8_t index, float dt) override;  // vt+0x64 0x00593c78 CKProjectileTypeScrap_UpdateOrientation
    uint8_t Launch(IKSerializable* data, const CVector3* pos, const CVector3* dir, float speed, IKSerializable* owner,
                   const RwMatrix* matrix) override;           // vt+0x84 0x00595b60 CKProjectileTypeScrap_Launch
    uint8_t LaunchEx(IKSerializable* data, const CVector3* pos, const CVector3* dir, float speed, IKSerializable* damage,
                     IKSerializable* owner, const RwMatrix* matrix) override;  // vt+0x88 0x00595a80
    uint8_t LaunchAtPoint(IKSerializable* /*data*/, const CVector3* /*pos*/, const CVector3* /*target*/, float /*speed*/,
                          IKSerializable* /*owner*/) override {
        return 0;  // vt+0x98 0x5928f8 CKProjectileTypeScrap_vf98
    }
    uint8_t LaunchAtPointEx(IKSerializable* /*data*/, const CVector3* /*pos*/, const CVector3* /*target*/,
                            float /*speed*/, IKSerializable* /*damage*/, IKSerializable* /*owner*/) override {
        return 0;  // vt+0x9c 0x592900 CKProjectileTypeScrap_vf9C
    }
    void ProcessDamageContacts(uint8_t /*index*/) override {}  // vt+0xa4 0x9cb640 (empty)

    // 0x00594928 CKProjectileTypeScrap_LaunchPiece: the projectile at `index` (the first free one) set up and shown.
    void LaunchPiece(IKSerializable* data, uint8_t index, const CVector3* pos, const CVector3* dir, float speed,
                     IKSerializable* owner, const RwMatrix* matrix, IKSerializable* damage);
    // 0x00592a60 CKProjectileTypeScrap_PlayInstanceSound_maybe: the projectile's sound (index m_ui32Index of +0x2c)
    // attached to its node and played; flag bit 2 set.
    void PlayInstanceSound(uint8_t index);
    // 0x00592b08 CKProjectileTypeScrap_UpdateRollAxis_maybe: the roll axis from the horizontal velocity.
    void UpdateRollAxis(Projectile* projectile);
    // 0x00592c20 CKProjectileTypeScrap_ProbeGround_maybe: the ground under the projectile; on it: flag bit 0 cleared.
    void ProbeGround(Projectile* projectile);
    // 0x00592cc0 CKProjectileTypeScrap_CollideAndStop_maybe: lands on the ground (data flag 0x400).
    void CollideAndStop(Projectile* projectile);
    // 0x005944d8 CKProjectileTypeScrap_CollideAndBounce_maybe: bounces on the ground (data flag 0x1).
    void CollideAndBounce(Projectile* projectile);
    // 0x005941a0 CKProjectileTypeScrap_TriggerImpactExplosion_maybe: the impact explosion (data flag 0x4000).
    void TriggerImpactExplosion(Projectile* projectile);

    uint32_t m_unk24;         // +0x24 (samples: 0)
    IKSerializable* m_unk28;  // +0x28 a reference
    IKSerializable* m_unk2c;  // +0x2c a reference
};
DOTD_ASSERT_SIZE(CKProjectileTypeScrap, 0x30);
DOTD_ASSERT_SIZE(CKProjectileTypeScrap::Projectile, 0x90);
DOTD_ASSERT_OFFSET(CKProjectileTypeScrap::Projectile, m_pNode, 0x0c);
DOTD_ASSERT_OFFSET(CKProjectileTypeScrap::Projectile, m_pBody, 0x10);
DOTD_ASSERT_OFFSET(CKProjectileTypeScrap::Projectile, m_fSpeed, 0x38);
DOTD_ASSERT_OFFSET(CKProjectileTypeScrap::Projectile, m_fAge, 0x50);
DOTD_ASSERT_OFFSET(CKProjectileTypeScrap::Projectile, m_flags58, 0x58);
DOTD_ASSERT_OFFSET(CKProjectileTypeScrap::Projectile, m_GrdContDatasInOut, 0x5c);
DOTD_ASSERT_OFFSET(CKProjectileTypeScrap::Projectile, m_pFx, 0x88);
DOTD_ASSERT_OFFSET(CKProjectileTypeScrap::Projectile, m_pVolume, 0x8c);
DOTD_ASSERT_OFFSET(CKProjectileTypeScrap, m_unk24, 0x24);
DOTD_ASSERT_OFFSET(CKProjectileTypeScrap, m_unk28, 0x28);
DOTD_ASSERT_OFFSET(CKProjectileTypeScrap, m_unk2c, 0x2c);
