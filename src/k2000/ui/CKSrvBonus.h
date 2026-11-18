// CKSrvBonus.h - the bonus service (key 0x1c1, vtable 0xb2ebd8, size 0x24). Original unit: CKSrvBonus.cpp
// (0x5a9638-0x5a9bc8, GAME_TOC2). Not in XXL2. Every member and the Load are its base's (KBase201).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/services/KBase201.h"

class CKSrvBonus : public KBase201 {
public:
    DOTD_CLASS_KEY(kCategoryService, 0x7)
    DOTD_DECLARE_FACTORIES(CKSrvBonus)

    CKSrvBonus();  // 0x005a9938 CKSrvBonus_Construct
    ~CKSrvBonus() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x005a9768 CKSrvBonus_Load
    void Start() override { KBase201::Start(); }        // vt+0x50 0x5a9740 CKSrvBonus_ResetRuntime (KBase201_vf50)
    void Stop() override { KBase201::Stop(); }          // vt+0x68 0x5a9718 CKSrvBonus_ResetOnLevelEnd_maybe (a tail call of KBase201_vf68)
    void Pause() override {}                            // vt+0x70 0x5a96f0 (KBase201's, empty)
    void Resume() override {}                           // vt+0x78 0x5a96c8 (KBase201's, empty)
    void Update(IKTime* frameClock) override { KBase201::Update(frameClock); }  // vt+0x7c 0x5a9610 UpdateCKSrvBonus (ProcessDelayedSpawns)
    // vt+0xa8 0x005a9638 CKSrvBonus_SpawnBonusWithVelocity_maybe: BonusPool_SpawnBonusObject from the game manager's
    // pool (+0x10), then the bonus's launch (vt+0xe0 with the velocity).
    void SpawnBonusWithVelocity(uint32_t kind, const float* pos, const float* vel, uint8_t last) override;
    // vt+0xac 0x005a9a18 CKSrvBonus_SpawnBonus_maybe: BonusPool_SpawnBonusObject from the game manager's pool (+0x10),
    // then the bonus's vt+0xe4 (velocity, hero).
    void SpawnBonusForHero(uint32_t kind, const CVector3* pos, const CVector3* velocity, IKSerializable* hero,
                           uint8_t last) override;
    // vt+0x24 0x5a97b8 CKSrvBonus_LevelReset: KBase201's RecursiveRegistration (0x126bd8 returns 1), inherited.
    // 0x5a9858 / 0x5a98a0 / 0x5a98d0: the vtable, then KBase201's destructor (the implicit chain). 0x5a9900 = 0x5a9938.
    // vt+0x94 0x005a9830 CKSrvBonus_Init: KBase201_Init (TocBridge_KBase201_Init), its result.
    int32_t InitializeService() override { return KBase201::InitializeService(); }
    // vt+0x98 0x005a9808 CKSrvBonus_vf98: KBase201_Shutdown (TocBridge_KBase201_Shutdown).
    void DestroyService() override { KBase201::DestroyService(); }
};
DOTD_ASSERT_SIZE(CKSrvBonus, 0x24);
