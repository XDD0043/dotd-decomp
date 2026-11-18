// CKGameSekens.h - a sekens (a scripted sequence) of the game structure (key 0x504c, vtable 0xb14890, size 0x20).
// Original unit: CKGameSekens.cpp (0x3c4f0-0x3caf0). The level's +0x54 list holds them (CKGameLevel::MarkSekensSeen);
// the same layout as CKGameVideo up to +0x1c. No XXL2 class of this name.
#pragma once
#include <cstdint>

#include "Spyro2008/logic/IKGameObject.h"
#include "k2000/core/Layout.h"

class IKFile;

class CKGameSekens : public IKGameObject {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x141)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x994eb8
        return key == 0x504c || key == 0x330c || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKGameSekens)

    // 0x0003c8b8 CKGameSekens_Create / 0x0003c910 CreateArray inline it: IKGameObject_ConstructBase, the vtable.
    CKGameSekens() : m_unk18(nullptr), m_unk1c(nullptr) {}
    ~CKGameSekens() override {}

    // vt+0x24 0x0003c7c8 RecursiveRegistration and vt+0x10 0x0003c7f0 Destroy: IKGameObject's (inherited).
    // vt+0x2c 0x0003c9c0 CKGameSekens_Load: IKGameObject's, then the level part's sekens (type 0, +0x1c) or the
    // game-structure block's level (type 8, +0x18).
    int32_t Load(IKFile* file, int32_t type) override;
    // vt+0x30 0x0003c778 CKGameSekens_PostLoad: IKGameObject's (0x42e40, 1), 1.
    int32_t PostLoad(int32_t type) override {
        IKGameObject::PostLoad(type);
        return 1;
    }
    // vt+0x54 0x0003c540 CKGameSekens_IsCurrentLevel: its level's (vt+0x54), 0 without one.
    uint8_t GetMatchesThisLevel() override;
    // vt+0x58 0x0003c720 CKGameSekens_vf58: IKGameObject's, no sekens, the "seen" flag (bit 1) cleared.
    void InitializeGameData() override;
    // vt+0x5c 0x0003c6f8 CKGameSekens_InitLevelData_maybe: IKGameObject's (nothing).
    void InitializeLevelData() override { IKGameObject::InitializeLevelData(); }
    // vt+0x60 0x0003c6c0 CKGameSekens_vf60: IKGameObject's (nothing), the sekens forgotten.
    void DestroyLevelData() override {
        IKGameObject::DestroyLevelData();
        m_unk1c = nullptr;
    }
    // vt+0x64 0x0003c698 CKGameSekens_ClearGameData_maybe: IKGameObject's.
    void DestroyGameData() override { IKGameObject::DestroyGameData(); }
    // vt+0x68 0x0003c630 CKGameSekens_vf68: IKGameObject's (nothing), then the sekens' "seen" flag (CKSekens +0x14 bit
    // 8) = this one's bit 1.
    void ApplyGameStateToLevel() override;

    IKSerializable* m_unk18;  // +0x18 the level (a CKGameLevel; the game-structure block, type 8)
    IKSerializable* m_unk1c;  // +0x1c the sekens (a CKSekens; the level part, type 0)
};
DOTD_ASSERT_SIZE(CKGameSekens, 0x20);
DOTD_ASSERT_OFFSET(CKGameSekens, m_unk18, 0x18);
DOTD_ASSERT_OFFSET(CKGameSekens, m_unk1c, 0x1c);
