// CKGameModule.h - a module (a mission step) of a level (key 0x334c, vtable 0xb147e8, PS3 size 0x30).
// Original unit: CKGameModule.cpp (0x3b4f0-0x3c2f0), with CKGameModule_Delete/IsCurrentLevel at the end
// of CKGameLevel.cpp. XXL2: K/KCore/Game/CKGameModule.h (m_pGameStage, m_vObjects), in the same Load
// order; DotD adds the byte at +0x1c and the word at +0x2c.
#pragma once
#include <cstdint>

#include "Spyro2008/logic/IKGameObject.h"
#include "k2000/core/Layout.h"
#include "k2000/util/TVector.h"

class CKGameLevel;

// XXL2 SGameModuleObject (K/KCore/Game/CKGameModule.h): an object of the module and its states. 0x10
// bytes on the PS3.
struct SGameModuleObject {
    IKSerializable* m_pObject;        // +0x00
    uint32_t m_ui32Ident;             // +0x04
    uint32_t m_ui32StateIdForLeft;    // +0x08
    uint32_t m_ui32StateIdForDone;    // +0x0c
};
DOTD_ASSERT_SIZE(SGameModuleObject, 0x10);

class CKTriggerSynchro;

class CKGameModule : public IKGameObject {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0xcd)
    DOTD_DECLARE_FACTORIES(CKGameModule)

    CKGameModule();             // inlined in CKGameModule_Create 0x3b9e8 / CreateArray 0x3bd08
    ~CKGameModule() override {} // vt+0x00 / +0x04  0x994e38 / 0x994db0

    // vt+0x60 0x0003b790 CKGameModule_ClearLevelData (XXL2 DestroyLevelData): the level part (+0x2c, the
    // object list) dropped at the level unload.
    void DestroyLevelData() override;
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0003bf18 CKGameModule_Load
    void InitializeGameData() override;                 // vt+0x58 0x0003b868 CKGameModule_InitGameData
    void InitializeLevelData() override;                // vt+0x5c 0x0003b808 CKGameModule_InitLevelData
    // Not ported: vt+0x1c 0x3be88 MessageProc, +0x40 0x3bcb0 GetInfo, +0x54 0x3b460, +0x60 0x3b790
    // ClearLevelData (STUB(C1.6)).
    // vt+0x68 0x0003b658 CKGameModule_vf68 (XXL2 ApplyGameStateToLevel): ApplyDone when activated, else
    // ApplyLeft.
    void ApplyGameStateToLevel() override;

    // vt+0x70 0x0003bb08 (Ghidra CKGameModule_SetActivated_maybe): flag bit 1, then vt+0x80 when vt+0x90
    // allows it. Names ours.
    virtual void SetActivated(uint8_t activated);
    virtual uint32_t IsActivated() { return (m_baFlags >> 1) & 1u; }  // vt+0x74 0x994d28
    // C1.6 gm: the game state's save / restore filters (CKGameState CopyFromStructure / ApplyToStructure):
    // vt+0x78 0x3b4f8 whether the activated bit is captured, vt+0x7c 0x3b500 whether it is applied (both 1
    // here; CKS08GameModule asks the game manager). Names ours.
    virtual uint8_t CanSaveActivated() { return 1; }
    virtual uint8_t CanRestoreActivated() { return 1; }
    // vt+0x80 0x994d80: flag bit 2. Name ours.
    virtual void SetFlag2(uint32_t value) { m_baFlags = (m_baFlags & ~4u) | (value << 2); }
    virtual uint32_t GetFlag2() { return (m_baFlags >> 2) & 1u; }  // vt+0x84 0x994da0
    // C1.6 gm: vt+0x88 0x3b508 whether flag 2 is applied, vt+0x8c 0x3b510 whether it is captured (1). Names ours.
    virtual uint8_t CanRestoreFlag2() { return 1; }
    virtual uint8_t CanSaveFlag2() { return 1; }
    // vt+0x90 0x3b518: whether SetActivated passes the value on to SetFlag2 (1). Name ours.
    virtual uint8_t CanSetFlag2() { return 1; }
    // C1.6 gm: vt+0x94 0x0003b520 CKGameModule_vf94 / vt+0x98 0x0003ba58 CKGameModule_vf98 (XXL2 ApplyLeft /
    // ApplyDone): every object of the module gets its "left" / "done" state (SetGameState, vt+0x3c).
    virtual void ApplyLeft();
    virtual void ApplyDone();

    // C1.6 gm: 0x0003bdf0 CKGameModule_UpdateTriggerDomains_maybe (from IKGameStructure's
    // RefreshModuleTriggerDomains).
    void UpdateTriggerDomains();

    CKGameLevel* m_pGameStage;  // +0x18 (XXL2 CKGameStage*) type-8 block; InitializeGameData: 0
    uint8_t m_unk1c;            // +0x1c DotD: type-8 block, after m_pGameStage
    TVector<SGameModuleObject, 8> m_vObjects;  // +0x20 level part (K_LEVEL_PLATEFORMS)
    // +0x2c DotD: InitializeLevelData sets 0 (0x3b4f0 Ghidra CKGameModule_SetField2C_maybe sets it).
    CKTriggerSynchro* m_pTriggerSynchro;  // +0x2c the CKTriggerSynchro entry of this module (CKGameModule_SetField2C_maybe 0x3b4f0)
};
DOTD_ASSERT_SIZE(CKGameModule, 0x30);
DOTD_ASSERT_OFFSET(CKGameModule, m_pGameStage, 0x18);
DOTD_ASSERT_OFFSET(CKGameModule, m_unk1c, 0x1c);
DOTD_ASSERT_OFFSET(CKGameModule, m_vObjects, 0x20);
DOTD_ASSERT_OFFSET(CKGameModule, m_pTriggerSynchro, 0x2c);
