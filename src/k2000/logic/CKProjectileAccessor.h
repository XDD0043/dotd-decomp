// CKProjectileAccessor.h - the handle through which game objects launch projectiles (key 0x1e0c, vtable
// 0xb1e858, size 0xc). Original unit: CKProjectileAccessor.cpp (0x1f2868-0x1f32e0). Base: KBase1DCC (the
// accessor interface: vt+0x50/+0x54 get and set +0x04). No XXL2 class of this name.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/KBase1DCC.h"
#include "k2000/math/CMatrix34.h"

struct RwMatrix;

class CKProjectileAccessor : public KBase1DCC {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x78)
    DOTD_DECLARE_FACTORIES(CKProjectileAccessor)

    // 0x001f2f10 CKProjectileAccessor_Construct: KBase1DCC, the vtable, +0x04 = null (+0x08 left as is).
    CKProjectileAccessor() { m_pProjectileType = nullptr; }
    ~CKProjectileAccessor() override {}
    // vt+0x08 0x9b07a0 (CKS08EnemyAttack_Load tests its reference with it)
    int32_t IsKindOfClass(uint32_t key) override { return key == 0x1e0c || key == 0x1dcc || key == 0xc; }
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001f3190 CKProjectileAccessor_Load
    IKSerializable* Vf50() override { return m_pProjectileType; }                       // vt+0x50 0x1f28b8
    void Vf54(IKSerializable* object) override { m_pProjectileType = object; }          // vt+0x54 0x1f28c0

    // 0x001f28c8 CKProjectileAccessor_GetMaxCount / 0x001f28e8 GetActiveCount / 0x001f3038 GetFreeSlots: the type's
    // record count, its active count and their difference (0 without a type).
    int32_t GetMaxCount() const;
    int32_t GetActiveCount() const;
    int32_t GetFreeSlots() const;
    // 0x001f2908 CKProjectileAccessor_Launch: with a type (+0x04), its vt+0x84 (type, data +0x08, pos, dir, speed,
    // owner, matrix) and its byte result; 0 without a type. (The golem's launchers call it with speed 25.0 and no
    // matrix.)
    uint8_t Launch(const CVector3* pos, const CVector3* dir, float speed, IKSerializable* owner, const RwMatrix* matrix);
    // 0x001f2988 CKProjectileAccessor_Launch (the second one): the same through vt+0x88 with the damage object first.
    uint8_t LaunchEx(const CVector3* pos, const CVector3* dir, float speed, IKSerializable* damage, IKSerializable* owner,
                     const RwMatrix* matrix);
    // 0x001f2a98 CKProjectileAccessor_Launch90: with a type, its vt+0x90 (type, data +0x08, pos, dir, speed, damage,
    // owner, target, matrix) and its byte result; 0 without a type.
    uint8_t Launch90(const CVector3* pos, const CVector3* dir, float speed, IKSerializable* damage, IKSerializable* owner,
                     IKSerializable* target, const RwMatrix* matrix);
    // 0x001f2c50 CKProjectileAccessor_LaunchAtPointEx: with a type, its vt+0x9c (type, data +0x08, pos, target, speed,
    // damage, owner) and its byte result; 0 without a type. The PS3 code also hands on a matrix (r9 -> r10) and the f2
    // float of its caller, which the type's LaunchAtPointEx never reads.
    uint8_t LaunchAtPointEx(const CVector3* pos, const CVector3* target, float speed, IKSerializable* damage,
                            IKSerializable* owner);

    // C2.8 port-all P03: the other launch variants (no LVL010 caller; CKBlackBall_Fire calls Launch90,
    // CKHkScrapShower_LaunchScrapAtPoint_maybe LaunchAtPoint). Each forwards to the type's slot with the type, the data
    // (+0x08), pos, dir / target and speed, and the caller's r7.. moved up one register (the caller's r6 is dropped, the
    // callee's r7 is the slot pointer the call loaded); 0 without a type. Arguments named by their PS3 register.
    // 0x001f2a10 CKProjectileAccessor_Launch8C (the type's vt+0x8c LaunchAtTarget: r7 the owner, r8 the target, r9 the
    // matrix; the base slot: Launch with the owner and the matrix, 0 without data)
    uint8_t Launch8C(const CVector3* pos, const CVector3* dir, float speed, void* r6, void* r7, void* r8, void* r9);
    // 0x001f2b28 CKProjectileAccessor_Launch94 (the type's vt+0x94 LaunchAtTargetSpot: r7 the owner, r8 a ProjectileTarget,
    // r9 the matrix; KStub_Return0_9b0be8 but in CKProjectileTypeFromExplosion)
    uint8_t Launch94(const CVector3* pos, const CVector3* dir, float speed, void* r6, void* r7, void* r8, void* r9);
    // 0x001f2bb0 CKProjectileAccessor_LaunchA0 (the type's vt+0xa0 LaunchAtScreenPoint: r7 the owner, r8 points to two
    // floats the accessor copies to its stack for the slot, r9 the matrix; KStub_Return0_9b0c48 but in
    // CKProjectileTypeSplineLock)
    uint8_t LaunchA0(const CVector3* pos, const CVector3* dir, float speed, void* r6, void* r7, const float* r8, void* r9);
    // 0x001f2cd8 CKProjectileAccessor_LaunchAtPoint (vt+0x98, the caller's r7 the owner)
    uint8_t LaunchAtPoint(const CVector3* pos, const CVector3* target, float speed, void* r6, IKSerializable* owner,
                          void* r8);
    // vt+0x10 0x001f2e30 CKProjectileAccessor_Destroy: KStub_Nop_1a5a8 (the base's), then the type reference cleared.
    void Destroy() override { m_pProjectileType = nullptr; }
    // vt+0x24 0x001f2de0 CKProjectileAccessor_RecursiveRegistration: CKSrvFxParticlesAccessor_RecursiveRegistration
    // 0x1a478 (KBase1DCC's slot): type 0 registers the object with the saving manager (vt+0x24, no owner).
    void RecursiveRegistration(int32_t type) override;

    // +0x04 the projectile type (file: CKProjectileTypeScrap / CKProjectileTypeBallisticPFX references).
    IKSerializable* m_pProjectileType;
    // +0x08 the projectile data (file: CKProjectileDataTypeScrap / ...BallisticPFX references).
    IKSerializable* m_pProjectileData;
};
DOTD_ASSERT_SIZE(CKProjectileAccessor, 0xc);
DOTD_ASSERT_OFFSET(CKProjectileAccessor, m_pProjectileType, 0x04);
DOTD_ASSERT_OFFSET(CKProjectileAccessor, m_pProjectileData, 0x08);
