// CKGameSpawnPoint.h - a spawn point of a level (key 0x318c, vtable 0xb14908, PS3 size 0x38). Original
// unit: CKGameSpawnPoint.cpp (0x3cb70-0x3db00). XXL2: K/KCore/Game/CKGameSpawnPoint.h, the same members
// in the same Load order (the camera beacon accessor is 8 bytes here, 4 in XXL2), plus a DotD reference
// at +0x34 read by the type-8 block.
#pragma once
#include <cstdint>

#include "Spyro2008/logic/IKGameObject.h"
#include "k2000/core/Layout.h"
#include "k2000/services/CTriggerStarter.h"

class CKGameLevel;
struct IKInfo;

class CKGameSpawnPoint : public IKGameObject {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0xc6)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x994f58
        return key == 0x318c || key == 0x330c || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKGameSpawnPoint)

    CKGameSpawnPoint();             // inlined in CKGameSpawnPoint_Create 0x3d490 / CreateArray 0x3d700
    ~CKGameSpawnPoint() override {} // vt+0x00 / +0x04  0x995068 / 0x995018

    // vt+0x60 0x0003d220 CKGameSpawnPoint_ClearLevelData_maybe: IKGameObject's, then no HDR data.
    void DestroyLevelData() override;
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0003d7f0 CKGameSpawnPoint_Load
    void InitializeGameData() override;                 // vt+0x58 0x0003d2b8 CKGameSpawnPoint_InitGameData
    void InitializeLevelData() override;                // vt+0x5c 0x0003d258 CKGameSpawnPoint_InitLevelData_maybe
    // vt+0x1c 0x0003d560 CKGameSpawnPoint_MessageProc: 0x202 makes it the structure's current spawn point (vt+0x6c);
    // 0x203 too, and its level and sector become the game manager's requested ones (+0x280 / +0x284); 0x204 too, and
    // the game manager's save request (vt+0x104 with 1, 0). 0 for those, 1 for any other.
    int32_t MessageProc(uint16_t message, void* data) override;
    // vt+0x40 0x0003d508 CKGameSpawnPoint_GetInfo: value 3 (a byte): it is the structure's current spawn point
    // (0x994fe8 CKGameSpawnPoint_IsCurrentSpawnPoint_maybe).
    int32_t GetInfo(IKInfo* info, int32_t request) override;
    uint8_t GetMatchesThisLevel() override;   // vt+0x54 0x0003cb70 CKGameSpawnPoint_IsCurrentLevel: its stage's vt+0x54
    void DestroyGameData() override;          // vt+0x64 0x0003d1f8 CKGameSpawnPoint_ClearGameData_maybe: IKGameObject's
    // vt+0x70 0x0003cbd8 CKGameSpawnPoint_GetBeaconPosition_maybe: the camera beacon's position (its three half-words
    // x 0.1); without the sector's klusters the half-words at addresses 0, 2 and 4 (BUG(original), see the code).
    virtual void GetBeaconPosition(float* position);
    // vt+0x74 0x00994f90 CKGameSpawnPoint_vf74: the camera beacon accessor is set (not all four 0xffff). Name ours.
    virtual uint8_t HasCameraBeacon();
    virtual IKSerializable* Vf78() { return nullptr; }  // vt+0x78 0x0003ccf8 CKGameSpawnPoint_vf78: 0
    // vt+0x7c 0x0003cd88 CKGameSpawnPoint_Activate_maybe (C2.2 gm): the spawn point becomes the active one at the
    // level start: its HDR effect, its start trigger signals; returns the loaded bit of its sector.
    virtual uint16_t Activate();

    CKGameLevel* m_pGameStage;  // +0x18 (XXL2 CKGameStage*) type-8 block; InitializeGameData: 0
    // +0x1c KSectorIndex (XXL2) type-8 block; InitializeGameData: -2 (the level's default sector)
    int32_t m_iSectorIndex;
    // +0x20 CKBeaconAccessor (XXL2: 4 bytes; here four u16, each byte-swapped), level part; the
    // constructor and InitializeLevelData set 0xffff (none).
    uint16_t m_baCameraPosition[4];
    IKSerializable* m_pHDRFxData;  // +0x28 (XXL2 CKHDRFxData*) level part; InitializeLevelData: 0
    CTriggerStarter m_tsStart;     // +0x2c level part
    IKSerializable* m_pUnk34;      // +0x34 DotD: type-8 block, last; constructor and InitializeGameData: 0
};
DOTD_ASSERT_SIZE(CKGameSpawnPoint, 0x38);
DOTD_ASSERT_OFFSET(CKGameSpawnPoint, m_pGameStage, 0x18);
DOTD_ASSERT_OFFSET(CKGameSpawnPoint, m_iSectorIndex, 0x1c);
DOTD_ASSERT_OFFSET(CKGameSpawnPoint, m_baCameraPosition, 0x20);
DOTD_ASSERT_OFFSET(CKGameSpawnPoint, m_pHDRFxData, 0x28);
DOTD_ASSERT_OFFSET(CKGameSpawnPoint, m_tsStart, 0x2c);
DOTD_ASSERT_OFFSET(CKGameSpawnPoint, m_pUnk34, 0x34);
