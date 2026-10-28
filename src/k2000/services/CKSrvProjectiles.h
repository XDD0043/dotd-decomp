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
    DOTD_DECLARE_FACTORIES(CKSrvProjectiles)

    CKSrvProjectiles();  // 0x001f3620 CKSrvProjectiles_Construct
    ~CKSrvProjectiles() override {}

    void Destroy() override;  // vt+0x10 0x001f3920 CKSrvProjectiles_Destroy
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001f3978 CKSrvProjectiles_Load
    void Start() override {}                            // vt+0x50 0x1f3ad8  STUB(C1.6)
    void Stop() override;                               // vt+0x68 0x1f3ae0 CKSrvProjectiles_Stop
    void Pause() override {}                            // vt+0x70 0x1f3bb0  STUB(C1.6)
    void Resume() override {}                           // vt+0x78 0x1f3bb8  STUB(C1.6)
    void Update(IKTime*) override {}                    // vt+0x7c 0x1f3c00 UpdateCKSrvProjectiles  STUB(C1.6)
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
