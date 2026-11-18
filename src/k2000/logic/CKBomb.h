// CKBomb.h - a pool of bombs that roll and explode after a fuse (key 0x2e0c, vtable 0xb2e2c0, size 0x64). Original unit:
// CKBomb.cpp (0x58e9c0-0x591f58, GAME_TOC2). Base: IKProjectileType. XXL2: KServiceProjectiles/CKBomb.h (the eight
// floats in this order, the five particle nodes, the explosion data, the shadow component and the damage type; its SBomb
// is DotD's 0x88-byte record below). No game file holds one (work/level-class-keys.json).
//
// C2.8 port-rest R05 ported the Load, the factories and the small slots (Destroy, MessageProc, RecursiveRegistration,
// IsDead, OnDeath, KillProjectile); the motion, collision, orientation, fuse, spawn / launch and damage slots are left
// (CKBomb.cpp's checklist).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/services/CKSrvShadow.h"
#include "k2000/services/IKProjectileType.h"

class CKBomb : public IKProjectileType {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0xb8)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x009cb478
        return key == 0x2e0c || key == 0x130c || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKBomb)

    // One bomb (XXL2 SBomb; 0x88 bytes, m_ui8MaxProjectiles of them). The Load sets the node and clears the rest it touches.
    struct Bomb {
        IKSerializable* m_pProjectileNode;              // +0x00 a reference (file): a CSGLeaf, hidden by the Load (flag 4)
        CVector3 m_v3Position;                          // +0x04 (0, 0, 0)
        CVector3 m_v3OldPosition;                       // +0x10 (0, 0, 0)
        CVector3 m_v3SpeedAt;                           // +0x1c the Load copies 0x00c50d4c (0, 0, 1)
        float m_fSpeed;                                 // +0x28 0
        float m_fAngle;                                 // +0x2c 0
        IKSerializable* m_pProjectileBS;                // +0x30 its CKDynBSphereProjectile; Load 0
        CGroundContactDatasInOut m_GrdContDatasInOut;   // +0x34 (ground 0, face -1, status 3, sector 0)
        CKShadowGround m_ShadowGround;                  // +0x60 (+0x7d used: 0)
        uint8_t m_pad7e[2];
        float m_fTimer;                                 // +0x80 0
        uint8_t m_baStates;                             // +0x84 bit 0 alive (IsDead: cleared); Load 0
        uint8_t m_pad85[3];
    };

    // 0x0058ef38 CKBomb_Create: IKProjectileType's constructor (+0x18 8, +0x14 1), then the vtable.
    // Out of line (CKBomb.cpp): inline ones failed the MSVC x64 Debug link with LNK1163 (as CWall's).
    CKBomb();
    // 0x009cb4f8 / 0x009cb4b0 CKBomb_Destructor / _DeletingDestructor (inline): vtable stores only.
    ~CKBomb() override;

    // vt+0x10 0x005918f8 CKBomb_Destroy: IKProjectileType_Destroy 0x1f3c38 (the two lists freed), then no shadow component.
    void Destroy() override;
    // vt+0x1c 0x00591930 CKBomb_MessageProc: the hazard query 0xc32 (as CKProjectileTypeBallisticPFX's, with +0x60); 1.
    int32_t MessageProc(uint16_t message, void* data) override;
    // vt+0x24 0x00591a08 CKBomb_RecursiveRegistration: IKProjectileType's (KStub_Return1_1f3c90), then for a level (type 0
    // only) the explosion data (+0x58) and the shadow component (+0x5c), no null tests.
    void RecursiveRegistration(int32_t type) override;
    // vt+0x2c 0x00591ab0 CKBomb_Load: IKProjectileType's, then (level data) the eight floats, the five particle nodes, the
    // two references, the bombs (a node each) and the damage type. The radius (+0x30) gives the ground probe's step
    // (+0x0c) and twice it its height (+0x10).
    int32_t Load(IKFile* file, int32_t type) override;
    uint8_t IsDead(uint8_t index) override;      // vt+0x58 0x0058efb0 CKBomb_IsDead: not alive (+0x84 bit 0)
    void OnDeath(uint8_t index) override;        // vt+0x5c 0x0058ea10 CKBomb_OnDeath: KillProjectile (vt+0x60)
    void KillProjectile(uint8_t index) override; // vt+0x60 0x0058f090 CKBomb_KillInstance
    // (vt+0x28 0x591a00 CKBomb_Save returns 1.)

    // ---- C2.8 port-final F03: the runtime ----
    // vt+0x50 0x0058fdb8 CKBomb_UpdateMotion: the roll (air damping, gravity), the angle step, the trail point, the
    // shadow's ground and (fuse lit) the fuse.
    void UpdateMotion(uint8_t index, float dt) override;
    // vt+0x54 0x00590d30 CKBomb_UpdateCollision: the ground under the bomb (lands or bounces) or a wall (bounces; none
    // found: the bomb dies).
    void UpdateCollision(uint8_t index, float dt) override;
    // vt+0x64 0x005909d0 CKBomb_UpdateOrientation: rolling, the node turned by the angle step about the roll axis; slow,
    // its up axis brought back to vertical; the node at the position.
    void UpdateOrientation(uint8_t index, float dt) override;
    // vt+0x84 0x0058fd18 CKBomb_Launch / vt+0x88 0x0058fc18 CKBomb_LaunchEx (the damage on the volume): a free bomb thrown
    // from pos along dir at speed for owner; 1 when one was free. `data` and `matrix` are not read.
    uint8_t Launch(IKSerializable* data, const CVector3* pos, const CVector3* dir, float speed, IKSerializable* owner,
                   const RwMatrix* matrix) override;
    uint8_t LaunchEx(IKSerializable* data, const CVector3* pos, const CVector3* dir, float speed, IKSerializable* damage,
                     IKSerializable* owner, const RwMatrix* matrix) override;
    // vt+0x98 0x00590928 CKBomb_LaunchAtPoint / vt+0x9c 0x00590820 CKBomb_LaunchAtPointEx: a free bomb thrown from pos
    // to land on target. The PS3 slots also take the caller's r9 / r10 (a velocity the bomb leads by) and f2 (its time
    // factor); the dotd slot signature (IKProjectileType.h) and CKProjectileAccessor do not carry them, so these pass
    // none (SpawnInstanceAtPoint's no-lead branch, the original's for a null pointer). No game file holds a CKBomb.
    uint8_t LaunchAtPoint(IKSerializable* data, const CVector3* pos, const CVector3* target, float speed,
                          IKSerializable* owner) override;
    uint8_t LaunchAtPointEx(IKSerializable* data, const CVector3* pos, const CVector3* target, float speed,
                            IKSerializable* damage, IKSerializable* owner) override;
    // vt+0xa4 0x005911d0 CKBomb_ProcessDamageContacts: the volume's contacts: an enemy-side volume (owner type 1, with
    // option bit 0) blows the bomb up; else (types 1 and 3) the bomb bounces off (the fuse lit), straight up off the
    // first controlled hero.
    void ProcessDamageContacts(uint8_t index) override;

    // 0x0058ec10 CKBomb_UpdateAttachedTransform_maybe: the shadow's ground point, normal and height from the ground
    // contact (a dynamic ground's through its world matrix), or the bomb's position and the up axis off the ground.
    void UpdateShadowGround(uint8_t index);
    // 0x0058f2d0 CKBomb_UpdateFuse_maybe: past the explosion time the bomb explodes (its volume released, dead, the
    // explosion effect at its foot); before, a fuse spark point (the effect of the quarter reached); the timer advances.
    void UpdateFuse(float dt, uint8_t index);
    // 0x0058f7c0 CKBomb_SpawnInstance: the bomb alive at pos, rolling along dir at speed, its node shown and placed, the
    // shadow caster registered, a projectile volume hung under the node for owner.
    void SpawnInstance(uint8_t index, const CVector3* pos, const CVector3* dir, float speed, IKSerializable* owner);
    // 0x00590088 CKBomb_SpawnInstanceAtPoint: as SpawnInstance, then the throw toward target (led by `velocity` times
    // the flight time times `lead` when given) with the arc's speed (at most 999).
    void SpawnInstanceAtPoint(uint8_t index, const CVector3* pos, const CVector3* target, IKSerializable* owner,
                              const CVector3* velocity, float speed, float lead);

    float m_fGravity;              // +0x24 (XXL2 names; one 0x20 read, each word swapped)
    float m_fContactSpring;        // +0x28
    float m_fAirDamp;              // +0x2c
    float m_fRadius;               // +0x30
    float m_fMinSpeedFx;           // +0x34
    float m_fExplosionTimer;       // +0x38
    float m_fExplosionAcc;         // +0x3c
    float m_fExplosionRadius;      // +0x40
    IKSerializable* m_apFx[5];     // +0x44 references: XXL2 m_pTimer1Fx..m_pTimer4Fx, m_pTrailFx (CParticlesNodeFx)
    IKSerializable* m_pExplosionFxData;  // +0x58 a reference (XXL2 embeds a CKExplosionFxData here)
    IKSerializable* m_pShadowCpnt;       // +0x5c a reference: the CKShadowCpnt (Destroy clears it)
    int32_t m_i32DamageType;       // +0x60 the hazard query's key (MessageProc 0xc32)
};
static_assert(CKBomb::kClassKey == 0x2e0c, "key");
DOTD_ASSERT_SIZE(CKBomb, 0x64);
DOTD_ASSERT_SIZE(CKBomb::Bomb, 0x88);
DOTD_ASSERT_OFFSET(CKBomb::Bomb, m_pProjectileBS, 0x30);
DOTD_ASSERT_OFFSET(CKBomb::Bomb, m_GrdContDatasInOut, 0x34);
DOTD_ASSERT_OFFSET(CKBomb::Bomb, m_ShadowGround, 0x60);
DOTD_ASSERT_OFFSET(CKBomb::Bomb, m_fTimer, 0x80);
DOTD_ASSERT_OFFSET(CKBomb::Bomb, m_baStates, 0x84);
DOTD_ASSERT_OFFSET(CKBomb, m_fGravity, 0x24);
DOTD_ASSERT_OFFSET(CKBomb, m_apFx, 0x44);
DOTD_ASSERT_OFFSET(CKBomb, m_pExplosionFxData, 0x58);
DOTD_ASSERT_OFFSET(CKBomb, m_pShadowCpnt, 0x5c);
DOTD_ASSERT_OFFSET(CKBomb, m_i32DamageType, 0x60);
