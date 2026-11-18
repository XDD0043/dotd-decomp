// CKSrvProjectiles.h - the projectile service (key 0x341, vtable 0xb1e8b8, size 0x14). Original unit:
// CKSrvProjectiles.cpp (0x1f32e0-0x1f3d98). XXL2: K/KServices/KServiceProjectiles/CKSrvProjectiles.h,
// the same members, read in the same order.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/services/IKService.h"

class CKSrvProjectiles : public IKService {
public:
    DOTD_CLASS_KEY(kCategoryService, 0xd)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9b07d8
        return key == 0x341 || key == 0x1 || key == 0x3fe || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKSrvProjectiles)

    CKSrvProjectiles();  // 0x001f3620 CKSrvProjectiles_Construct
    ~CKSrvProjectiles() override {}

    void Destroy() override;  // vt+0x10 0x001f3920 CKSrvProjectiles_Destroy
    int32_t MessageProc(uint16_t /*message*/, void* /*data*/) override { return 0; }  // vt+0x1c 0x1f3918
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001f3978 CKSrvProjectiles_Load
    void Start() override {}                            // vt+0x50 0x1f3ad8 CKSrvProjectiles_Start (empty)
    void Restart() override { Stop(); }                 // vt+0x54 0x1f3bc0 CKSrvProjectiles_Restart: Stop (vt+0x68)
    void Stop() override;                               // vt+0x68 0x1f3ae0 CKSrvProjectiles_Stop
    void Pause() override {}                            // vt+0x70 0x1f3bb0 CKSrvProjectiles_Pause (empty)
    void Resume() override {}                           // vt+0x78 0x1f3bb8 CKSrvProjectiles_Resume (empty)
    // vt+0x7c 0x001f3c00 UpdateCKSrvProjectiles: UpdateAll with the frame's dt while the clock runs (state 0).
    void Update(IKTime* frameClock) override;
    // 0x001f3330 CKSrvProjectiles_UpdateAll: every pool's active projectiles, in order: UpdateMotion,
    // ProcessDamageContacts, UpdateCollision, UpdateOrientation, then IsDead -> OnDeath (which kills it: the last
    // active one moves into its place, so the same index is looked at again).
    void UpdateAll(float dt);
    int32_t InitializeService() override { return 1; }  // vt+0x94 0x1f3588
    void DestroyService() override {}                   // vt+0x98 0x1f3590 (empty)

    IKSerializable** m_apProjectilePoolList;  // +0x0c IKProjectileType* (Mem_AllocAligned16)
    uint8_t m_ui8NbOfProjectilePools;         // +0x10
    uint8_t m_pad11[3];                       // +0x11 never written (heap residue on the live dump)
};
DOTD_ASSERT_SIZE(CKSrvProjectiles, 0x14);
DOTD_ASSERT_OFFSET(CKSrvProjectiles, m_ui32Priority, 0x08);
DOTD_ASSERT_OFFSET(CKSrvProjectiles, m_apProjectilePoolList, 0x0c);
DOTD_ASSERT_OFFSET(CKSrvProjectiles, m_ui8NbOfProjectilePools, 0x10);
