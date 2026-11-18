// IKProjectileType.h - the projectile types' unregistered abstract base (key 0x130c; XXL2:
// K/KServices/KServiceProjectiles/IKProjectileType.h, the same members in the same order). Its Load
// (0x1f3ca0 CKProjectileType_LoadBase, reached through 0x990090 TocBridge_CKProjectileType_LoadBase) lives
// in CKSrvProjectiles.cpp. Classes: CKProjectileTypeBallisticPFX (0x140c), CKProjectileTypeScrap (0x134c).
// The runtime slots are declared in vtable order (C2.7); CKProjectileTypeScrap overrides them.
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"
#include "k2000/math/CMatrix34.h"

struct RwMatrix;
class CSGHotSpot;

// The target of a CKProjectileTypeFromExplosion / TargetLock / SplineLock projectile (0x14 bytes on the PS3; C2.8
// port-final F04, port-last Z4): the launch argument of vt+0x94, the record's copy (+0x88) and the data of messages
// 0x2896 / 0x2897 (sent on a hit, when no projectile is free and when one dies). Names ours.
struct ProjectileTarget {
    IKSerializable* m_pTarget;  // +0x00 an IKHook: its node's LTM position is the aim
    CSGHotSpot* m_pHotSpot;     // +0x04 when set, its world position is the aim instead
    uint32_t m_unk08;           // +0x08 never written by the launches
    uint8_t m_unk0c;            // +0x0c the hot spot index of the aim point query (message 0x400)
    uint8_t m_pad0d[3];
    // +0x10 the damage object CKProjectileTypeTargetLock_LaunchAtTargetInfo (vt+0x94) passes to SpawnInstance; the
    // records keep the slot (+0x98) without writing it (FromExplosion's, TargetLock's 0x9c-byte records).
    IKSerializable* m_pDamage;
};

class IKProjectileType : public IKSerializable {
public:
    struct CGroundContactDatasIn {  // XXL2 names (16 bytes, as in XXL2)
        float m_fDeltaMax;                // +0x00 the derived Loads set 1.0
        float m_fObjectHeight;            // +0x04 the derived Loads set 2.0
        uint32_t m_MasksOfGrdForTest[2];  // +0x08 constructor 1, 8; the Load 1, 0
    };
    struct CGroundContactDatasInOut {  // XXL2 names (the derived Loads set the projectiles' copies)
        IKSerializable* m_pGround;      // +0x00 CGround*; the Loads set 0
        int32_t m_i32FaceIndex;         // +0x04 -1
        CVector3 m_Normal;              // +0x08
        uint32_t m_eContactStatus;      // +0x14 3
        CVector3 m_ProjectionOnGround;  // +0x18
        float m_fdH;                    // +0x24
        uint8_t m_ui8SectorNumber;      // +0x28 0
        uint8_t m_pad29[3];
    };

    // The constructor inlined in CKProjectileTypeBallisticPFX_Create (0x5868e8) / CKProjectileTypeScrap_Create
    // (0x593078): this vtable, +0x18 = 8, +0x14 = 1.
    IKProjectileType() {
        m_GrdContDatasIn.m_MasksOfGrdForTest[1] = 8;
        m_GrdContDatasIn.m_MasksOfGrdForTest[0] = 1;
    }
    // vt+0x10 0x001f3c38 IKProjectileType_ClearReferences (CKSrvProjectiles.cpp): both lists freed, the pointers kept.
    void Destroy() override;
    // vt+0x2c 0x001f3ca0 CKProjectileType_LoadBase
    int32_t Load(IKFile* file, int32_t type) override;

    // The projectile types' runtime slots (XXL2 CKProjectileTypeBallisticPFX: UpdateProjectilePosition,
    // UpdateProjectileCollision, IsProjectileNeedToBeKilled, KillProjectile, ApplyTransform, FireFrom, ...;
    // DotD has one more slot in front of KillProjectile). `index` is the projectile's place in the active part of
    // m_apProjectileList (0 .. m_ui8NbOfActiveProjectiles - 1). CKSrvProjectiles_UpdateAll 0x1f3330 calls, per active
    // projectile: UpdateMotion, ProcessDamageContacts, UpdateCollision, UpdateOrientation, then IsDead and OnDeath.
    // The base bodies stand in for the abstract slots; the registered types override them.
    virtual void UpdateMotion(uint8_t /*index*/, float /*dt*/) {}       // vt+0x50 (XXL2 UpdateProjectilePosition)
    virtual void UpdateCollision(uint8_t /*index*/, float /*dt*/) {}    // vt+0x54 (XXL2 UpdateProjectileCollision)
    virtual uint8_t IsDead(uint8_t /*index*/) { return 0; }             // vt+0x58 (XXL2 IsProjectileNeedToBeKilled)
    virtual void OnDeath(uint8_t /*index*/) {}                          // vt+0x5c: the death effects, then KillProjectile
    // vt+0x60 (XXL2 KillProjectile(index); CKProjectileTypeScrap_KillInstance 0x593258, CKProjectileTypeBallisticPFX
    // 0x5886d0): the projectile of that index killed (the active ones are compacted to the front, so index 0 kills them
    // one by one). Both registered types override every runtime slot (CKProjectileTypeBallisticPFX.cpp, C2.7).
    virtual void KillProjectile(uint8_t /*index*/) {}
    virtual void UpdateOrientation(uint8_t /*index*/, float /*dt*/) {}  // vt+0x64 (XXL2 ApplyTransform)
    // vt+0x68..+0x80: the launch variants' forwarders (0x9b08a0 / 0x9b08f0 / 0x9b0938 / 0x9b0990 call vt+0x68 / +0x68 /
    // +0x6c / +0x7c with the arguments moved). Nothing in LVL010 calls them; the signatures are not ported.
    // vt+0x68 (0x9b0898 KStub_Return0; CKSandal_vf68 0x456190 places a sandal): XXL2 FireFrom(pos, dir, speed, owner,
    // matrix). r6 is passed along by the forwarders and read by no body; r8 likewise (C2.8 port-rest R06: typed for
    // CKSandal, the only override with a body).
    virtual uint8_t Vf68(const CVector3* /*pos*/, const CVector3* /*dir*/, const void* /*r6*/, float /*speed*/,
                         IKSerializable* /*owner*/, const void* /*r8*/) {
        return 0;
    }
    // vt+0x6c 0x009b08a0 IKProjectileType_vf6C (CKSandal_vf6C 0x455c80 the same instructions): vt+0x68 with r4..r6 and
    // f1 kept, r8 / r9 moved down to r7 / r8 (r7 dropped).
    virtual uint8_t Vf6C(const CVector3* pos, const CVector3* dir, const void* r6, float speed, const void* /*r7*/,
                         IKSerializable* r8, const void* r9) {
        return Vf68(pos, dir, r6, speed, r8, r9);
    }
    virtual void Vf70() {}  // vt+0x70 0x9b08f0
    virtual void Vf74() {}  // vt+0x74 0x9b0938
    virtual void Vf78() {}  // vt+0x78 0x9b0980 KStub_Return0
    virtual void Vf7C() {}  // vt+0x7c 0x9b0988 KStub_Return0
    virtual void Vf80() {}  // vt+0x80 0x9b0990
    // vt+0x84 Launch (CKProjectileTypeScrap_Launch 0x595b60, CKProjectileTypeBallisticPFX_Launch 0x58e240): a projectile
    // of the pool fired with `data` (the accessor's +0x08) from pos along dir at `speed`, for `owner`; `matrix` (may be
    // null) is the node's local matrix. 1 when one was free. The base slot has no body of its own (both registered
    // types override it).
    virtual uint8_t Launch(IKSerializable* /*data*/, const CVector3* /*pos*/, const CVector3* /*dir*/, float /*speed*/,
                           IKSerializable* /*owner*/, const RwMatrix* /*matrix*/) {
        return 0;
    }
    // vt+0x88 LaunchEx (CKProjectileTypeScrap_LaunchEx 0x595a80, ...BallisticPFX_LaunchEx 0x58e160): the same with the
    // damage object the projectile's volume carries (+0x1c), passed before the owner.
    virtual uint8_t LaunchEx(IKSerializable* /*data*/, const CVector3* /*pos*/, const CVector3* /*dir*/, float /*speed*/,
                             IKSerializable* /*damage*/, IKSerializable* /*owner*/, const RwMatrix* /*matrix*/) {
        return 0;
    }
    // vt+0x8c..+0x94: launch variants (0x9b0ab0 / 0x9b0b98 forward to vt+0x84 / +0x70 / +0x88). The registers as the
    // accessor passes them (CKProjectileAccessor_Launch8C 0x1f2a10 / _Launch94 0x1f2b28): r4 data, r5 pos, r6 dir, f1
    // speed, r8 owner, r9 the target (vt+0x94: a ProjectileTarget), r10 the matrix (r7 is garbage).
    // vt+0x8c 0x009b0ab0 IKProjectileType_vf8C (C2.8 port-final F04: typed for CKProjectileTypeFromExplosion_LaunchAtTarget
    // 0x59a868, the only override): with data, Launch (vt+0x84) with r8 the owner and r10 the matrix; without, vt+0x70
    // 0x9b08f0, which forwards to vt+0x68 (KStub_Return0_9b0898 in the registered types): 0.
    virtual uint8_t LaunchAtTarget(IKSerializable* data, const CVector3* pos, const CVector3* dir, float speed,
                                   IKSerializable* owner, IKSerializable* /*target*/, const RwMatrix* matrix) {
        if (data == nullptr) return 0;
        return Launch(data, pos, dir, speed, owner, matrix);
    }
    // vt+0x90 0x009b0b98 IKProjectileType_vf90 (no registered type overrides it): LaunchEx (vt+0x88) with the type
    // itself as the damage (r7 = r3), r8 the owner and r9 (the caller's target slot) the matrix; damage and matrix dropped.
    virtual uint8_t LaunchExTargeted(IKSerializable* data, const CVector3* pos, const CVector3* dir, float speed,
                                     IKSerializable* /*damage*/, IKSerializable* owner, IKSerializable* target,
                                     const RwMatrix* /*matrix*/) {
        return Launch90Body(data, pos, dir, speed, owner, target);  // 0x9b0b98: the type as damage, r8 owner, r9 matrix
    }
    // vt+0x94 0x9b0be8 KStub_Return0 (C2.8 port-final F04: typed for CKProjectileTypeFromExplosion_LaunchInstance_maybe
    // 0x59ab28, the only override): a launch at a target and its hot spot.
    virtual uint8_t LaunchAtTargetSpot(IKSerializable* /*data*/, const CVector3* /*pos*/, const CVector3* /*dir*/,
                                       float /*speed*/, IKSerializable* /*owner*/, const ProjectileTarget* /*target*/,
                                       const RwMatrix* /*matrix*/) {
        return 0;
    }
    // C2.8 port-all P03: the bodies of vt+0x90 / +0xa0 as CKProjectileAccessor's Launch90 / A0 reach them (the registered
    // types keep the base slots). Non-virtual: no type overrides them. The argument names are the registers (the PS3
    // forwarders shuffle them as written).
    // 0x009b0b98: LaunchEx (vt+0x88) with the type itself in r7 (the damage argument), r8 the owner, r9 the matrix.
    uint8_t Launch90Body(IKSerializable* data, const CVector3* pos, const CVector3* dir, float speed, void* r8, void* r9) {
        return LaunchEx(data, pos, dir, speed, this, static_cast<IKSerializable*>(r8), static_cast<const RwMatrix*>(r9));
    }
    // vt+0x98 LaunchAtPoint (CKProjectileTypeBallisticPFX_LaunchAtPoint 0x58a1c8; CKProjectileTypeScrap_vf98 0x5928f8 returns
    // 0): a projectile of the pool fired with `data` from pos toward the point `target` at `speed`, for `owner`. 1 when one
    // was free. The PS3 callers also pass a matrix (r9 / r10) and a second float (f2, 1.0 from CKPoisonGrenade_Fire) that
    // no body reads.
    virtual uint8_t LaunchAtPoint(IKSerializable* /*data*/, const CVector3* /*pos*/, const CVector3* /*target*/,
                                  float /*speed*/, IKSerializable* /*owner*/) {
        return 0;
    }
    // vt+0x9c LaunchAtPointEx (CKProjectileTypeBallisticPFX_LaunchAtPointEx 0x58a0f8; CKProjectileTypeScrap_vf9C 0x592900
    // returns 0): the same with the damage object the projectile's volume carries (+0x1c), passed before the owner.
    virtual uint8_t LaunchAtPointEx(IKSerializable* /*data*/, const CVector3* /*pos*/, const CVector3* /*target*/,
                                    float /*speed*/, IKSerializable* /*damage*/, IKSerializable* /*owner*/) {
        return 0;
    }
    // vt+0xa0 0x9b0c48 KStub_Return0 (C2.8 port-last Z4: typed for CKProjectileTypeSplineLock_vfA0 0x599020, the only
    // override): a launch toward a screen point (two floats in 0..1; CKProjectileAccessor_LaunchA0 passes a copy).
    virtual uint8_t LaunchAtScreenPoint(IKSerializable* /*data*/, const CVector3* /*pos*/, const CVector3* /*dir*/,
                                        float /*speed*/, IKSerializable* /*owner*/, const float* /*screenPoint*/,
                                        const RwMatrix* /*matrix*/) {
        return 0;
    }
    // vt+0xa4: the projectile's damage contacts (CKProjectileTypeScrap 0x9cb640 is empty; BallisticPFX 0x587d00).
    virtual void ProcessDamageContacts(uint8_t /*index*/) {}

    void** m_apProjectileList;                // +0x04 the projectiles (pointers into +0x08), made by the derived Load
    void* m_aProjectiles;                     // +0x08 the derived class's projectile records (Mem_AllocAligned16)
    CGroundContactDatasIn m_GrdContDatasIn;   // +0x0c
    uint32_t m_baOptions;                     // +0x1c XXL2 CBitArray (bit 0x80: CKProjectileTypeBallisticPFX_PostLoad)
    uint8_t m_ui8MaxProjectiles;              // +0x20 the record count
    uint8_t m_ui8NbOfActiveProjectiles;       // +0x21 the Load sets 0
    // +0x22..+0x23: the PS3 (Itanium C++ ABI) puts a subclass's first member in this tail padding
    // (CKProjectileTypeBallisticPFX's byte at +0x22); the host compilers never do, so it is declared here.
    uint8_t m_aSubclassTail[2];
};
DOTD_ASSERT_SIZE(IKProjectileType, 0x24);
DOTD_ASSERT_SIZE(IKProjectileType::CGroundContactDatasInOut, 0x2c);
DOTD_ASSERT_OFFSET(IKProjectileType, m_apProjectileList, 0x04);
DOTD_ASSERT_OFFSET(IKProjectileType, m_aProjectiles, 0x08);
DOTD_ASSERT_OFFSET(IKProjectileType, m_GrdContDatasIn, 0x0c);
DOTD_ASSERT_OFFSET(IKProjectileType, m_baOptions, 0x1c);
DOTD_ASSERT_OFFSET(IKProjectileType, m_ui8MaxProjectiles, 0x20);
DOTD_ASSERT_OFFSET(IKProjectileType, m_ui8NbOfActiveProjectiles, 0x21);
DOTD_ASSERT_OFFSET(IKProjectileType, m_aSubclassTail, 0x22);
