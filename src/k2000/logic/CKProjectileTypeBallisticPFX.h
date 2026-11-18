// CKProjectileTypeBallisticPFX.h - a ballistic projectile pool (key 0x140c, vtable 0xb2e208, size 0x34).
// Original unit: CKProjectileTypeBallisticPFX.cpp (0x586258-0x58e9c0). Base: IKProjectileType (its Load is
// called first). XXL2 has a class of this name, but DotD loads different data (no floats; references, a
// word and a byte), so the members keep placeholder names where the runtime does not name them.
//
// The runtime (C2.7): CKSrvProjectiles_UpdateAll drives the active projectiles (UpdateMotion: drag, gravity and the
// optional steering toward heroes / mechanisms / enemies; ProcessDamageContacts: the volume's hits, bounces off them or
// dies; UpdateCollision: the ground probe in one of three modes; UpdateOrientation: the node placed and turned, scaled,
// faded, the camera quake; IsDead; OnDeath: the death explosion and shock wave, then KillProjectile). The launches
// (Launch / LaunchEx: a position and a direction; LaunchAtPoint / LaunchAtPointEx: a ballistic arc to a point) take the
// first free record and set it up from a CKProjectileDataTypeBallisticPFX.
//
// Pool options (m_baOptions): 0x20 an emission point on the particle node +0x24 when a fast projectile hits,
// 0x80 a trail ribbon per projectile (the trail node +0x28), 0x200000 a looping sound per projectile (+0x30).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/services/IKProjectileType.h"

class CSGLeaf;
class CKQuakeCameraLauncher;
class CKProjectileDataTypeBallisticPFX;

class CKProjectileTypeBallisticPFX : public IKProjectileType {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x50)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9cb3d8
        return key == 0x140c || key == 0x130c || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKProjectileTypeBallisticPFX)

    // One projectile (0x88 bytes, m_ui8MaxProjectiles of them). Names from the runtime (C2.7).
    struct Projectile {
        IKSerializable* m_pOwner;                       // +0x00 the launcher (Load 0); message 0x2802 when killed
        IKSerializable* m_pData;                        // +0x04 CKProjectileDataTypeBallisticPFX (the accessor's data)
        CSGLeaf* m_pNode;                               // +0x08 a reference (file); the Load sets its flag 0x4 (hidden)
        CVector3 m_vPos;                                // +0x0c (0, 0, 0)
        CVector3 m_vPrevPos;                            // +0x18 (0, 0, 0) the position before this frame's motion
        CVector3 m_vDir;                                // +0x24 the unit direction of flight; the Load copies 0x00c50d4c
        float m_fSpeed;                                 // +0x30 0
        IKSerializable* m_pVolume;                      // +0x34 its CKDynBSphereProjectile (data +0x44); Load 0
        CGroundContactDatasInOut m_GrdContDatasInOut;   // +0x38 the ground under it (GroundProbePoints)
        // +0x64 bit 0 alive (cleared: IsDead), bit 2 landed (collision mode C), bit 3 its sound plays; Load 0.
        uint8_t m_flags64;
        uint8_t m_pad65[3];
        float m_fAge;                                   // +0x68 0; seconds since the launch
        float m_fLifetime;                              // +0x6c 1.0; the launch draws data +0x28 .. +0x28 + +0x54
        float m_fScale;                                 // +0x70 the launch draws data +0x64 .. +0x68
        uint8_t m_ui8Index;                             // +0x74 its index (the trail ribbon and the sound of it)
        uint8_t m_pad75[3];
        IKSerializable* m_pFireBall;                    // +0x78 its CKFireBallNodeFx (data flag 0x1000); Load 0
        IKSerializable* m_pParticleFx;                  // +0x7c its particle effect (data flag 0x40); Load 0
        CKQuakeCameraLauncher* m_pQuake;                // +0x80 a reference (file): the camera quake (data flag 0x20000000)
        uint8_t m_bQuakeTriggered;                      // +0x84 the launch clears it, the quake sets it
        uint8_t m_pad85[3];
    };

    // The constructor inlined in 0x005868e8 CKProjectileTypeBallisticPFX_Create: IKProjectileType's, then
    // the vtable only.
    CKProjectileTypeBallisticPFX() {}
    ~CKProjectileTypeBallisticPFX() override {}
    // vt+0x10 0x0058e2c0 CKProjectileTypeBallisticPFX_Destroy: IKProjectileType_Destroy 0x1f3c38 (the two lists freed).
    void Destroy() override;
    // vt+0x1c 0x0058e2e8 CKProjectileTypeBallisticPFX_MessageProc: the hazard query 0xc32 (see the body); 1 otherwise.
    int32_t MessageProc(uint16_t message, void* data) override;
    // vt+0x24 0x0058e408 CKProjectileTypeBallisticPFX_RecursiveRegistration
    void RecursiveRegistration(int32_t type) override;
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0058e508 CKProjectileTypeBallisticPFX_Load
    // vt+0x30 0x0058e3c0 CKProjectileTypeBallisticPFX_PostLoad: level data with the trail option (0x80) but no trail node
    // (+0x28): the option cleared.
    int32_t PostLoad(int32_t type) override;
    // (vt+0x28 0x58e3b8 CKProjectileTypeBallisticPFX_Save returns 1, the base's.)

    void UpdateMotion(uint8_t index, float dt) override;       // vt+0x50 0x00588278
    void UpdateCollision(uint8_t index, float dt) override;    // vt+0x54 0x0058c878
    uint8_t IsDead(uint8_t index) override;                    // vt+0x58 0x00586830
    void OnDeath(uint8_t index) override;                      // vt+0x5c 0x0058a238
    void KillProjectile(uint8_t index) override;               // vt+0x60 0x005886d0 CKProjectileTypeBallisticPFX_KillInstance
    void UpdateOrientation(uint8_t index, float dt) override;  // vt+0x64 0x00587218
    uint8_t Launch(IKSerializable* data, const CVector3* pos, const CVector3* dir, float speed, IKSerializable* owner,
                   const RwMatrix* matrix) override;           // vt+0x84 0x0058e240
    uint8_t LaunchEx(IKSerializable* data, const CVector3* pos, const CVector3* dir, float speed, IKSerializable* damage,
                     IKSerializable* owner, const RwMatrix* matrix) override;  // vt+0x88 0x0058e160
    uint8_t LaunchAtPoint(IKSerializable* data, const CVector3* pos, const CVector3* target, float speed,
                          IKSerializable* owner) override;     // vt+0x98 0x0058a1c8
    uint8_t LaunchAtPointEx(IKSerializable* data, const CVector3* pos, const CVector3* target, float speed,
                            IKSerializable* damage, IKSerializable* owner) override;  // vt+0x9c 0x0058a0f8
    void ProcessDamageContacts(uint8_t index) override;        // vt+0xa4 0x00587d00
    // vt+0xa8 0x00586338 CKProjectileTypeBallisticPFX_vfA8: empty.
    virtual void VfA8() {}
    // vt+0xac 0x005864b8 CKProjectileTypeBallisticPFX_vfAC: the age (+0x68) of the projectile at `index`.
    virtual float GetProjectileAge(uint8_t index);

    // 0x0058c948 CKProjectileTypeBallisticPFX_SpawnInstance: the projectile at `index` launched from pos along dir.
    // Draws rand: the lifetime, the scale, then (data flag 0x100) three for a random rotation.
    void SpawnInstance(IKSerializable* data, uint8_t index, const CVector3* pos, const CVector3* dir, float speed,
                       IKSerializable* owner, const RwMatrix* matrix, IKSerializable* damage);
    // 0x00588d08 CKProjectileTypeBallisticPFX_SpawnAtPoint_maybe: the projectile at `index` launched from pos on an arc
    // through `target` at `speed`. The same draws.
    void SpawnAtPoint(IKSerializable* data, uint8_t index, const CVector3* pos, const CVector3* target, float speed,
                      IKSerializable* owner);
    // 0x00586630 CKProjectileTypeBallisticPFX_PlayInstanceSound_maybe: the projectile's sound (its index in +0x30)
    // attached to its node and played; flag bit 3 set.
    void PlayInstanceSound(uint8_t index);
    // 0x00586340 CKProjectileType_UpdateInstanceTrailSegment_maybe: the projectile's ribbon anchors (mode 1) either side
    // of it, half the data's width (+0x38) along the side: the node's LTM right / up rows (data flag 0x100000 with /
    // without 0x80000), else the direction crossed with the camera's real Y / Z axis.
    void UpdateInstanceTrailSegment(uint8_t index);
    // 0x00586d48 CKProjectileTypeBallisticPFX_ComputeSteering_maybe: the sum of the attractions toward the heroes (data
    // flag 0x4000000), the mechanism group's active actors (0x8000000) and the active enemies (0x10000000).
    CVector3 ComputeSteering(float dt, Projectile* projectile, const CVector3* pos);
    // 0x00586940 CKProjectileTypeBallisticPFX_ComputeAttractionVector_maybe: toward `target`'s aim point once the
    // projectile is old enough (data +0x60) and the point near enough (data +0x5c, a box distance), of length data +0x58.
    CVector3 ComputeAttractionVector(float dt, Projectile* projectile, IKSerializable* target, const CVector3* pos,
                                     IKSerializable* hittable);
    // 0x0058c148 CKProjectileTypeBallisticPFX_CollideSweepA / 0x0058a948 _CollideModeC_maybe / 0x0058b498
    // _CollideModeB_maybe: the ground probe and its answer (dies on contact / lands / bounces).
    void CollideSweepA(uint8_t index);
    void CollideModeC(uint8_t index);
    void CollideModeB(uint8_t index);

    // +0x22 (in IKProjectileType's tail padding, m_aSubclassTail[0]): a byte, the last one the Load reads.
    uint8_t& Unk22() { return m_aSubclassTail[0]; }

    IKSerializable* m_unk24;  // +0x24 a reference: the particle node of the emission points (option 0x20; a CParticlesNodeFx)
    IKSerializable* m_unk28;  // +0x28 a reference: the trail node (option 0x80; a CTrailNodeFx); PostLoad clears 0x80 without
    int32_t m_unk2c;          // +0x2c (samples: 0, -1) the hazard query's key (MessageProc 0xc32)
    IKSerializable* m_unk30;  // +0x30 a reference: the projectiles' sounds (option 0x200000; a CKSoundDictionaryID)
};
DOTD_ASSERT_SIZE(CKProjectileTypeBallisticPFX, 0x34);
DOTD_ASSERT_SIZE(CKProjectileTypeBallisticPFX::Projectile, 0x88);
DOTD_ASSERT_OFFSET(CKProjectileTypeBallisticPFX::Projectile, m_pNode, 0x08);
DOTD_ASSERT_OFFSET(CKProjectileTypeBallisticPFX::Projectile, m_vDir, 0x24);
DOTD_ASSERT_OFFSET(CKProjectileTypeBallisticPFX::Projectile, m_fSpeed, 0x30);
DOTD_ASSERT_OFFSET(CKProjectileTypeBallisticPFX::Projectile, m_pVolume, 0x34);
DOTD_ASSERT_OFFSET(CKProjectileTypeBallisticPFX::Projectile, m_GrdContDatasInOut, 0x38);
DOTD_ASSERT_OFFSET(CKProjectileTypeBallisticPFX::Projectile, m_flags64, 0x64);
DOTD_ASSERT_OFFSET(CKProjectileTypeBallisticPFX::Projectile, m_fScale, 0x70);
DOTD_ASSERT_OFFSET(CKProjectileTypeBallisticPFX::Projectile, m_ui8Index, 0x74);
DOTD_ASSERT_OFFSET(CKProjectileTypeBallisticPFX::Projectile, m_pQuake, 0x80);
DOTD_ASSERT_OFFSET(CKProjectileTypeBallisticPFX::Projectile, m_bQuakeTriggered, 0x84);
DOTD_ASSERT_OFFSET(CKProjectileTypeBallisticPFX, m_unk24, 0x24);
DOTD_ASSERT_OFFSET(CKProjectileTypeBallisticPFX, m_unk28, 0x28);
DOTD_ASSERT_OFFSET(CKProjectileTypeBallisticPFX, m_unk2c, 0x2c);
DOTD_ASSERT_OFFSET(CKProjectileTypeBallisticPFX, m_unk30, 0x30);
