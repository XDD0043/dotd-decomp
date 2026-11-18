// CKSandal.h - a pool of animated "sandal" props placed on the ground (footprints, key 0x2f0c, vtable 0xb27070, size
// 0x34). Original units: CKSandal.cpp (0x455dc0-0x456b78) and seven slots at the end of CKHkTrackerManager.cpp
// (0x455b58-0x455cd8). Base: IKProjectileType (its Load first). XXL2: K/KSandal/CKSandal.h (m_fDuration,
// m_fFadeDuration, m_pDeathFx, m_pAnimatedDictionary; SSandal: m_pAnimNode, m_v3Position, m_fRatio, m_fTimer; the
// options bit 0 GetUseDeathFx, bit 1 GetUseFade). No game file holds the class (C2.8 port-rest R06: ported from the
// disassembly anyway).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/services/IKProjectileType.h"

class CAnimatedNode;
class CAnimationDictionary;
class CParticlesNodeFx;

class CKSandal : public IKProjectileType {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0xbc)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c3e40
        return key == 0x2f0c || key == 0x130c || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKSandal)

    // One sandal (0x18 bytes, m_ui8MaxProjectiles of them; XXL2 SSandal, 0x20 there).
    struct SSandal {
        CAnimatedNode* m_pAnimNode;  // +0x00 a reference (file); the Load hides it (flag 0x4)
        CVector3 m_v3Position;       // +0x04 the Load copies g_nullVector 0x00c50d64
        float m_fRatio;              // +0x10 the blend weight (0 .. 1 from the facing); the Load sets 0
        float m_fTimer;              // +0x14 seconds since placed; the Load sets 0
    };

    // The constructor inlined in 0x00456138 CKSandal_Create / 0x00456348 CreateArray: IKProjectileType's (+0x18 = 8,
    // +0x14 = 1), then this vtable.
    CKSandal();  // out of line (CKSandal.cpp): inline ones broke the MSVC x64 Debug link (LNK1163)
    ~CKSandal() override;  // 0x009c3e78 / 0x009c3e98: the vtables only

    void Destroy() override;                            // vt+0x10 0x00456738 CKSandal_Destroy
    void RecursiveRegistration(int32_t type) override;  // vt+0x24 0x00456768 CKSandal_RecursiveRegistration
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x004567d8 CKSandal_Load

    void UpdateMotion(uint8_t index, float dt) override;     // vt+0x50 0x004562d0 CKSandal_UpdateMotion
    void UpdateCollision(uint8_t /*index*/, float /*dt*/) override {}  // vt+0x54 0x00455ba8 (empty)
    uint8_t IsDead(uint8_t index) override;                  // vt+0x58 0x00455bb0 CKSandal_vf58
    void OnDeath(uint8_t index) override;                    // vt+0x5c 0x004565d0 CKSandal_OnDeath
    void KillProjectile(uint8_t index) override;             // vt+0x60 0x00455be8 CKSandal_vf60
    void UpdateOrientation(uint8_t index, float dt) override;  // vt+0x64 0x00456400 CKSandal_UpdateFadeOut_maybe
    // vt+0x68 0x00456190 CKSandal_vf68 (XXL2 FireFrom): a free sandal placed at pos, its blend from dir against the
    // owner hook's node `at` axis. 1 when one was placed.
    uint8_t Vf68(const CVector3* pos, const CVector3* dir, const void* r6, float speed, IKSerializable* owner,
                 const void* r8) override;
    // vt+0x6c 0x00455c80 CKSandal_vf6C: the base forwarder's instructions (IKProjectileType::Vf6C).
    uint8_t Vf6C(const CVector3* pos, const CVector3* dir, const void* r6, float speed, const void* r7,
                 IKSerializable* r8, const void* r9) override {
        return Vf68(pos, dir, r6, speed, r8, r9);
    }
    // vt+0x7c 0x00455cd0 / vt+0x80 0x00455cd8 CKSandal_vf7C / vf80: return 0 (the slots' arguments are not ported: no
    // caller).
    void Vf7C() override {}
    void Vf80() override {}
    // vt+0x84 0x009b09e0 CKSandal_vf84: nothing with data; without, vt+0x68 with r5 / r6 as pos / dir (r6 kept), r8 as
    // the owner and r9 as r8. The owner argument here is the declared matrix (the PS3 r8); the forwarders pass what
    // their callers put there.
    uint8_t Launch(IKSerializable* data, const CVector3* pos, const CVector3* dir, float speed, IKSerializable* /*owner*/,
                   const RwMatrix* matrix) override {
        if (data != nullptr) return 0;
        return Vf68(pos, dir, dir, speed,
                    const_cast<IKSerializable*>(reinterpret_cast<const IKSerializable*>(matrix)), nullptr);
    }
    // vt+0x88 0x009b0a60 CKSandal_vf88: vt+0x84 with r7 = the type itself, r8 = r9 (the matrix), r9 = r10.
    uint8_t LaunchEx(IKSerializable* data, const CVector3* pos, const CVector3* dir, float speed,
                     IKSerializable* /*damage*/, IKSerializable* /*owner*/, const RwMatrix* matrix) override {
        return Launch(data, pos, dir, speed, this, matrix);
    }
    uint8_t LaunchAtPoint(IKSerializable* /*data*/, const CVector3* /*pos*/, const CVector3* /*target*/,
                          float /*speed*/, IKSerializable* /*owner*/) override {
        return 0;  // vt+0x98 0x009b0bf0 CKSandal_vf98
    }
    // vt+0x9c 0x009b0bf8 CKSandal_vf9C: vt+0x98 with r7 = the type itself, r8 = r9, r9 = r10 (vf98 returns 0).
    uint8_t LaunchAtPointEx(IKSerializable* data, const CVector3* pos, const CVector3* target, float speed,
                            IKSerializable* /*damage*/, IKSerializable* /*owner*/) override {
        return LaunchAtPoint(data, pos, target, speed, this);
    }
    void ProcessDamageContacts(uint8_t /*index*/) override {}  // vt+0xa4 0x00455dc0 (empty)

    // 0x00455e50 CKSandal_PlaceInstance_maybe (XXL2 InitProjectileFireFrom): sandal `index` shown at pos, oriented along
    // the owner's node `at` axis (up = the Y axis), its blend weight from dot(at, dir) mapped from [-0.7, 0.7] to [0, 1].
    void PlaceInstance(uint8_t index, const CVector3* pos, const CVector3* dir, float speed, IKSerializable* owner);

    float m_fDuration;                            // +0x24 a sandal dies after this (seconds)
    float m_fFadeDuration;                        // +0x28 the fade-out at the end of m_fDuration (options bit 1)
    CParticlesNodeFx* m_pDeathFx;                 // +0x2c a reference: one point emitted where a sandal dies (bit 0)
    CAnimationDictionary* m_pAnimatedDictionary;  // +0x30 a reference: words 0 and 1 the blended pair
};
static_assert(CKSandal::kClassKey == 0x2f0c, "key");
DOTD_ASSERT_SIZE(CKSandal, 0x34);
DOTD_ASSERT_SIZE(CKSandal::SSandal, 0x18);
DOTD_ASSERT_OFFSET(CKSandal, m_fDuration, 0x24);
DOTD_ASSERT_OFFSET(CKSandal, m_fFadeDuration, 0x28);
DOTD_ASSERT_OFFSET(CKSandal, m_pDeathFx, 0x2c);
DOTD_ASSERT_OFFSET(CKSandal, m_pAnimatedDictionary, 0x30);
