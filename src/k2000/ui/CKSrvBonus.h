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
    void Start() override {}                            // vt+0x50 0x5a9740  STUB(C1.6)
    void Stop() override { KBase201::Stop(); }          // vt+0x68 0x5a9718 CKSrvBonus_ResetOnLevelEnd_maybe (a tail call of KBase201_vf68)
    void Pause() override {}                            // vt+0x70 0x5a96f0 (KBase201's, empty)
    void Resume() override {}                           // vt+0x78 0x5a96c8 (KBase201's, empty)
    void Update(IKTime*) override {}                    // vt+0x7c 0x5a9610 UpdateCKSrvBonus  STUB(C1.6)
    // vt+0x94 0x5a9830: KBase201_Init (STUB(C1.6), see KBase201).
    int32_t InitializeService() override { return KBase201::InitializeService(); }
    void DestroyService() override {}                   // vt+0x98 0x5a9808  STUB(C1.6)
};
DOTD_ASSERT_SIZE(CKSrvBonus, 0x24);
