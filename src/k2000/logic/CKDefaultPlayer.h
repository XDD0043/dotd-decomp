// CKDefaultPlayer.h - the engine's default player (key 0x184c, vtable 0xb13830, size 0x14; XXL2: CKDefaultPlayer).
// Original unit: CKDefaultPlayer_2.cpp (0x1d808-0x1dbb0); its bodies are IKPlayer's Impl functions (CKDefaultPlayer.cpp).
// Spyro creates CKS08Player instead (GetPlayerClassKey).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/IKPlayer.h"

class CKDefaultPlayer : public IKPlayer {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x61)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x992bc8
        return key == 0x184c || key == 0x180c || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKDefaultPlayer)

    // 0x0001daa0 CKDefaultPlayer_Create / 0x0001daf8 CreateArray inline it: IKPlayer's part (+0x0c, +0x04, +0x08), the
    // vtable.
    CKDefaultPlayer() {}
    ~CKDefaultPlayer() override {}

    // vt+0x2c 0x0001d958 CKDefaultPlayer_Load: IKPlayer's (0x1a290), 1.
    int32_t Load(IKFile* file, int32_t type) override {
        IKPlayer::Load(file, type);
        return 1;
    }
    // vt+0x30 0x0001d930 CKDefaultPlayer_PostLoad (0x1a0d0, 1) and vt+0x10 0x0001d9d0 Destroy (IKPlayer_Destroy 0x19f90,
    // empty): the inherited defaults.
    // vt+0x24 0x0001d9a8 CKDefaultPlayer_RecursiveRegistration: CKDefaultPlayer_LevelResetImpl (0x1a140).
    void RecursiveRegistration(int32_t type) override { LevelResetImpl(type); }
    // vt+0x50 0x0001d908 CKDefaultPlayer_vf50: CKDefaultPlayer_vf50Impl (0x1a220).
    void CopyPlayerGameData(IKPlayer* other) override { CopyPlayerGameDataImpl(other); }
    // vt+0x54 0x0001d8e0 CKDefaultPlayer_vf54: CKDefaultPlayer_vf54Impl (0x1a120).
    void InitializeNewGame() override { InitializeNewGameImpl(); }
};
DOTD_ASSERT_SIZE(CKDefaultPlayer, 0x14);
