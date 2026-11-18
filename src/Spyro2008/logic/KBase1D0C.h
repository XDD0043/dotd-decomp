// KBase1D0C.h - the unregistered base of CKS08GameLevelCollectible (key 0x1d0c, PS3 size 0x1c): a game
// object that belongs to a level. DotD only, so it keeps the placeholder name. Original code: in the
// IKGameObject unit (0x43160-0x433f8) and CKS08GameLevelCollectible.cpp (0x433f8-0x43480: the
// constructor).
#pragma once
#include <cstdint>

#include "Spyro2008/logic/IKGameObject.h"
#include "k2000/core/Layout.h"

class CKS08GameLevel;

class KBase1D0C : public IKGameObject {
public:
    KBase1D0C();             // 0x00043438 (Ghidra CKS08GameLevelCollectible_ConstructBase_maybe)
    ~KBase1D0C() override {} // vt+0x00 / +0x04  0x9957a0 / 0x995758

    int32_t GetClassType() override { return 0xc; }    // vt+0x14 0x995748
    int32_t GetClassID() override { return 0x74; }     // vt+0x18 0x995750
    // vt+0x2c 0x000432a0 (Ghidra CKS08GameLevelCollectible_LoadBase_maybe)
    int32_t Load(IKFile* file, int32_t type) override;
    // vt+0x58 0x43250 InitGameData and vt+0x5c 0x43228 InitLevelData only call IKGameObject's.
    void Destroy() override { IKGameObject::Destroy(); }      // vt+0x10 0x000433d0 KBase1D0C_Destroy (Ghidra ..._ClearReferences)
    // vt+0x24 0x000433a8 KBase1D0C_vf24 / vt+0x28 0x00043380 KBase1D0C_vf28 / vt+0x30 0x00043278 KBase1D0C_PostLoad:
    // IKGameObject's RecursiveRegistration (0x42e38), Save (0x42e30) and PostLoad (0x42e40), which do nothing; 1.
    void RecursiveRegistration(int32_t) override {}
    int32_t Save(IKFile*, int32_t) override { return 1; }
    int32_t PostLoad(int32_t) override { return 1; }
    void DestroyLevelData() override { IKGameObject::DestroyLevelData(); }  // vt+0x60 0x00043200 KBase1D0C_ClearLevelData
    void DestroyGameData() override { IKGameObject::DestroyGameData(); }    // vt+0x64 0x000431d8 KBase1D0C_vf64
    void ApplyGameStateToLevel() override {}                                // vt+0x68 0x000431c8 KBase1D0C_vf68 (empty)
    int32_t MessageProc(uint16_t, void*) override { return 1; }  // vt+0x1c 0x00043478 KStub_Return1_43478
    virtual void Vf70() {}  // vt+0x70 0x000431d0 (Ghidra CKS08GameLevelCollectible_vf70; empty)
    // vt+0x54 0x00043160 CKS08GameLevelCollectible_IsCurrentLevel (KBase1D0C's slot): its level is the loaded one.
    uint8_t GetMatchesThisLevel() override;

    // +0x18 the collectible's level (type-8 block; the constructor sets 0). Name ours: the struct draft
    // types it CKS08GameLevel*, whose +0x88 list holds the collectibles.
    CKS08GameLevel* m_pLevel;
};
DOTD_ASSERT_SIZE(KBase1D0C, 0x1c);
DOTD_ASSERT_OFFSET(KBase1D0C, m_pLevel, 0x18);
