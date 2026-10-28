// CKS08GameManager_3.cpp - reconstructed original translation unit 0x4f6648-0x4fdad8 (GAME_TOC1, main_toc1), 94 functions, 79 live.
// Primary class: CKS08GameManager  key 0x784c  category Logic  size 0xf2c  vtable 0xb2af78
// Other owners: GetElementLevel (1), SpawnElementGroundFx (1), GetTotalFury (1), IsFuryGaugeFull (1), SetEquippedArmor (1), ClearEquippedArmors (1), AddDragonFury (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x4f6648  CKS08GameManager_Delete
//   [x] 0x4f6698  CKS08GameManager_InitStateHandlerTable
//   [ ] 0x4f6718  KStub_Return0_4f6718  [dead]
//   [ ] 0x4f6720  KStub_Nop_4f6720  [dead]
//   [ ] 0x4f6728  FUN_004f6728  [dead]
//   [x] 0x4f6838  CKS08GameManager_CallMember2E0Vf60Arg0_maybe
//   [x] 0x4f6890  CKS08GameManager_CallMember2E0Vf78_maybe
//   [x] 0x4f68e0  CKS08GameManager_vf158
//   [ ] 0x4f6a20  CKS08GameManager_vf28C
//   [ ] 0x4f6a28  CKS08GameManager_GetUpgradeLevelForPoints_maybe  [dead]
//   [ ] 0x4f6ac0  FUN_004f6ac0  [dead]
//   [ ] 0x4f6b08  KStub_Nop_4f6b08  [dead]
//   [ ] 0x4f6b10  CKS08GameManager_GetBonusValue_maybe
//   [ ] 0x4f6b40  KStub_Nop_4f6b40  [dead]
//   [x] 0x4f6b48  CKS08GameManager_vf31C
//   [ ] 0x4f6b78  CKS08GameManager_RequestStoredMusicTrack_maybe
//   [x] 0x4f6bc0  CKS08GameManager_vf1D4
//   [x] 0x4f6be8  CKS08GameManager_GetDirectionActionState_maybe
//   [ ] 0x4f6de0  CKS08GameManager_GetCurrentMainLevelIndex_maybe
//   [ ] 0x4f6e18  CKS08GameManager_BuildSaveDetailText_maybe
//   [x] 0x4f6e78  CKS08GameManager_GetFocusedHeroCamera_maybe
//   [x] 0x4f6eb8  CKS08GameManager_vfAC
//   [ ] 0x4f7080  CKS08GameManager_vf94
//   [ ] 0x4f70a8  CKS08GameManager_vf98
//   [ ] 0x4f70d0  CKS08GameManager_vfC0
//   [ ] 0x4f70f8  CKS08GameManager_IsPad1Connected_maybe  [dead]
//   [x] 0x4f7130  CKS08GameManager_SetSaveRequestFlag_maybe
//   [x] 0x4f7158  CKS08GameManager_vf240
//   [x] 0x4f7180  CKS08GameManager_PostLoad
//   [ ] 0x4f7280  CKS08GameManager_RecursiveRegistration
//   [x] 0x4f7c28  CKS08GameManager_Destroy
//   [ ] 0x4f7c80  CKS08GameManager_DeleteArray
//   [ ] 0x4f7d20  RegisterCKS08GameManagerType
//   [ ] 0x4f7da8  _GLOBAL__D_4f7da8
//   [ ] 0x4f7db8  _GLOBAL__I_4f7db8
//   [ ] 0x4f7dc8  CKS08GameManager_vfD0
//   [ ] 0x4f7e90  CKS08GameManager_GetInfo
//   [ ] 0x4f8090  CKS08GameManager_vf2EC
//   [x] 0x4f80f8  CKS08GameManager_ResetGameProgress_maybe
//   [ ] 0x4f8208  CKS08GameManager_vfBC
//   [ ] 0x4f8318  CKS08GameManager_OnSaveGameDone_maybe
//   [ ] 0x4f85a8  CKS08GameManager_vf290
//   [ ] 0x4f8618  CKS08GameManager_SpawnGemReward_maybe
//   [ ] 0x4f8750  CKS08GameManager_StartDeathSequence_maybe
//   [ ] 0x4f8858  CKS08GameManager_GetSaveSubtitleText_maybe
//   [x] 0x4f88f8  CKS08GameManager_GetGroundSurfaceBit_maybe
//   [ ] 0x4f8940  CKS08GameManager_SetOnlyMainPlayerActive_maybe
//   [ ] 0x4f89d8  CKS08GameManager_IsAnyMenuButtonPressed_maybe
//   [x] 0x4f8b50  CKS08GameManager_vf320
//   [ ] 0x4f8cc0  CKS08GameManager_PlayCollectibleMusic_maybe
//   [x] 0x4f8d08  CKS08GameManager_Start
//   [ ] 0x4f8f18  CKS08GameManager_Save
//   [x] 0x4f8f78  CKS08GameManager_Update
//   [x] 0x4f9408  CKS08GameManager_Construct
//   [ ] 0x4f94b0  CKS08GameManager_Construct_2
//   [ ] 0x4f9558  GetElementLevel
//   [ ] 0x4f9628  CKS08GameManager_SpawnSurfaceFx
//   [ ] 0x4f9988  CKS08GameManager_DeletingDestructor
//   [ ] 0x4f9a60  CKS08GameManager_Destructor
//   [ ] 0x4f9b30  CKS08GameManager_DestructBody_2
//   [ ] 0x4f9c00  CKS08GameManager_vfF0
//   [ ] 0x4f9d60  CKS08GameManager_vfCC
//   [ ] 0x4fa0e8  CKS08GameManager_Restart
//   [ ] 0x4fa238  CKS08GameManager_CreateArray
//   [ ] 0x4fa370  CreateCKS08GameManager
//   [x] 0x4fa438  CKS08GameManager_MessageProc
//   [x] 0x4fb3d8  CKS08GameManager_HandlePauseInput_maybe
//   [ ] 0x4fb848  SpawnElementGroundFx_maybe
//   [ ] 0x4fbb08  CKS08GameManager_SpawnDefaultExplosionFx_maybe
//   [ ] 0x4fbd70  CKS08GameManager_SpawnExplosionFx
//   [x] 0x4fc010  CKS08GameManager_LoadRefTableE4C_maybe
//   [x] 0x4fc228  CKS08GameManager_Load
//   [ ] 0x4fd420  GetTotalFury_maybe
//   [ ] 0x4fd438  IsFuryGaugeFull_2_maybe
//   [ ] 0x4fd480  SetEquippedArmor_maybe
//   [ ] 0x4fd4b8  ClearEquippedArmors_maybe  [dead]
//   [ ] 0x4fd508  KStub_Return0_4fd508  [dead]
//   [ ] 0x4fd510  KStub_Nop_4fd510  [dead]
//   [ ] 0x4fd518  KStub_Return0_4fd518  [dead]
//   [ ] 0x4fd520  KStub_Nop_4fd520  [dead]
//   [ ] 0x4fd528  AddDragonFury_maybe
//   [ ] 0x4fd608  FUN_004fd608  [dead]
//   [x] 0x4fd628  GetArmorMeshHiddenFlag_maybe
//   [x] 0x4fd658  GetEquippedArmor_maybe
//   [ ] 0x4fd680  GetDragonFury_maybe
//   [ ] 0x4fd6c0  ResetAllDragonFury_maybe  [dead]
//   [ ] 0x4fd6d8  RefillAllDragonsMana
//   [x] 0x4fd740  GetDragonManaCapacity
//   [x] 0x4fd7c8  GetDragonMana
//   [x] 0x4fd808  ConsumeDragonMana
//   [ ] 0x4fd8d8  RefillAllDragonsHealth
//   [x] 0x4fd940  GetDragonHealthCapacity
//   [x] 0x4fd9c8  GetDragonHealth
//   [x] 0x4fda08  DamageDragon
//
//   [ ] 0x991250  CKS08GameManager_GetSerializationFlags  [inline]
//   [ ] 0x9c6868  CKS08GameManager_vf14C  [inline]
//   [ ] 0x9c6880  CKS08GameManager_vf16C  [inline]
//   [ ] 0x9c6918  CKS08GameManager_vf260  [inline]
//   [ ] 0x9c6920  CKS08GameManager_vf264  [inline]
//   [ ] 0x9c6928  CKS08GameManager_vf268  [inline]
//   [ ] 0x9c6938  CKS08GameManager_vf270  [inline]
//   [ ] 0x9c6940  CKS08GameManager_vf274  [inline]
//   [ ] 0x9c6948  CKS08GameManager_vf278  [inline]
//   [ ] 0x9c6950  CKS08GameManager_vf27C  [inline]
//   [ ] 0x9c6958  CKS08GameManager_vf280  [inline]
//   [ ] 0x9c6960  CKS08GameManager_vf284  [inline]
//   [ ] 0x9c6968  CKS08GameManager_vf288  [inline]
//   [ ] 0x9c6990  CKS08GameManager_vf2A0  [inline]
//   [ ] 0x9c6998  CKS08GameManager_vf2A4  [inline]
//   [ ] 0x9c69a0  CKS08GameManager_vf2A8  [inline]
//   [ ] 0x9c69a8  CKS08GameManager_vf2AC  [inline]
//   [ ] 0x9c69b0  CKS08GameManager_vf2B0  [inline]
//   [ ] 0x9c69b8  CKS08GameManager_vf2B4  [inline]
//   [ ] 0x9c69c0  CKS08GameManager_vf2B8  [inline]
//   [ ] 0x9c69c8  CKS08GameManager_vf2BC  [inline]
//   [ ] 0x9c69d0  CKS08GameManager_vf2C0  [inline]
//   [ ] 0x9c69d8  CKS08GameManager_vf2C4  [inline]
//   [ ] 0x9c69e0  CKS08GameManager_vf2C8  [inline]
//   [ ] 0x9c69e8  CKS08GameManager_vf2CC  [inline]
//   [ ] 0x9c69f0  CKS08GameManager_vf2D0  [inline]
//   [x] 0x9c69f8  CKS08GameManager_vfE0  [inline]
//   [ ] 0x9c6a00  CKS08GameManager_vf2D4  [inline]
//   [ ] 0x9c6a08  CKS08GameManager_vf2E0  [inline]
//   [ ] 0x9c6a18  CKS08GameManager_vfE8  [inline]
//   [x] 0x9c6a78  CKS08GameManager_vfDC  [inline]
//   [x] 0x9c6a80  CKS08GameManager_vf308  [inline]
//   [x] 0x9c6a88  CKS08GameManager_vf30C  [inline]
//   [ ] 0x9c6a90  CKS08GameManager_vf208  [inline]
//   [x] 0x9c6aa0  CKS08GameManager_vf314  [inline]
//   [x] 0x9c6af8  CKS08GameManager_vf324  [inline]
//   [ ] 0x9c6b08  CKS08GameManager_vf32C  [inline]
//   [ ] 0x9c6b10  CKS08GameManager_vf330  [inline]
//   [x] 0x9c6b68  CKS08GameManager_vf310  [inline]
//   [ ] 0x9c6cb0  CKS08GameManager_IsKindOfClass  [inline]
//   [ ] 0x9c6cf8  CKS08GameManager_GetClassType  [inline]
//   [ ] 0x9c6d00  CKS08GameManager_GetClassID  [inline]
//   [ ] 0x9c6d08  CKS08GameManager_vf100  [inline]
//   [ ] 0x9c6d10  CKS08GameManager_vf254  [inline]
//   [ ] 0x9c6d18  CKS08GameManager_vf258  [inline]
//   [ ] 0x9c6d20  CKS08GameManager_vf1B0  [inline]
//   [ ] 0x9c6d28  CKS08GameManager_vf1B8  [inline]
//   [ ] 0x9c6d30  CKS08GameManager_vf358  [inline]
//   [x] 0x9c6d38  CKS08GameManager_GetMaxPlayers_maybe  [inline]
//   [x] 0x9c6d40  CKS08GameManager_GetPlayerCount_maybe  [inline]
//   [ ] 0x9c6d48  CKS08GameManager_GetTriggerProp4B4  [inline]
//   [ ] 0x9c6d50  CKS08GameManager_vf1D8  [inline]
//   [ ] 0x9c6d58  CKS08GameManager_vf1DC  [inline]
//   [ ] 0x9c6d60  CKS08GameManager_vf1E0  [inline]
//   [ ] 0x9c6d78  CKS08GameManager_vf298  [inline]
//   [ ] 0x9c6d80  CKS08GameManager_vf29C  [inline]
//   [ ] 0x9c6d98  CKS08GameManager_GetTriggerProp4B1  [inline]
//   [x] 0x9c6da8  CKS08GameManager_vf214  [inline]
//   [ ] 0x9c6dd8  CKS08GameManager_vf2F4  [inline]
//   [x] 0x9c6de0  CKS08GameManager_vf2F8  [inline]
//   [ ] 0x9c6e28  CKS08GameManager_vf2FC  [inline]
//   [ ] 0x9c6e70  CKS08GameManager_vf300  [inline]
//   [x] 0x9c6e78  CKS08GameManager_vf340  [inline]
//   [x] 0x9c6e80  CKS08GameManager_vf344  [inline]
//   [x] 0x9c6e90  CKS08GameManager_vf338  [inline]
//   [x] 0x9c6e98  CKS08GameManager_vf33C  [inline]
//   [x] 0x9c6ea0  CKS08GameManager_vf348  [inline]
//   [x] 0x9c6ea8  CKS08GameManager_GetHudInterfaces  [inline]
//   [x] 0x9c6eb8  CKS08GameManager_vf350  [inline]
//   [x] 0x9c6ec0  CKS08GameManager_GetCounterTextVarTable_maybe  [inline]
//   [ ] 0x9c6ed0  CKS08GameManager_vf26C  [inline]
//   [ ] 0x9c6ee8  CKS08GameManager_GetTriggerProp4B5  [inline]
//   [ ] 0x9c6f30  CKS08GameManager_vf318  [inline]
//   [ ] 0x9c6f38  CKS08GameManager_vfD4  [inline]
//   [ ] 0x9c6f40  CKS08GameManager_vf194  [inline]
//   [ ] 0x9c6f48  CKS08GameManager_vf198  [inline]
//   [ ] 0x9c6f50  CKS08GameManager_vf19C  [inline]
//   [ ] 0x9c6f58  CKS08GameManager_vf1A0  [inline]
//   [ ] 0x9c6f60  CKS08GameManager_vf1AC  [inline]
//   [x] 0x9c6f68  CKS08GameManager_vf304  [inline]
//   [ ] 0x9c6f70  CKS08GameManager_GetTriggerProp4B0  [inline]
//   [ ] 0x9c6f80  GetCynderManaCapacity  [inline]
//   [ ] 0x9c6fb0  GetSpyroManaCapacity  [inline]
//   [ ] 0x9c6fe0  CKS08GameManager_IsInterfaceStateNot10_maybe  [inline]
//   [ ] 0x9c6ff8  CKS08GameManager_vf218  [inline]
//   [x] 0x9c7028  CKS08GameManager_vfC4  [inline]
#include "Spyro2008/logic/CKS08GameManager.h"
#include "Spyro2008/logic/CKS08InGameInterfaceBoss.h"
#include "Spyro2008/logic/CKS08InGameInterfaceCenter.h"
#include "Spyro2008/logic/CKS08ObjectiveList.h"
#include "Spyro2008/logic/ui/CKS08MenuPauseInfo.h"
#include "k2000/graphical/ui/CKFlashMessageOut.h"
#include "k2000/services/CKSrvTrigger.h"
#include "k2000/services/ICollisionMesh.h"
#include "Spyro2008/groups/IKGrpHero.h"
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "k2000/logic/CKCinematicScene.h"

#include "k2000/io/IKFile.h"
#include <cstring>

#include "k2000/memory/Mem.h"

#include "Spyro2008/logic/CKMenuBase114c.h"
#include "k2000/core/Stub.h"
#include "crt/ppc_ops.h"
#include "k2000/managers/CKSoundManager.h"
#include "k2000/misc/JobQueue.h"
#include "k2000/services/CKSrvCinematic.h"
#include "k2000/graphical/system/IKVideo.h"
#include "k2000/graphical/system/CKVideoSegment.h"
#include "k2000/graphical/system/CVideoManager.h"
#include "k2000/graphical/system/PS3_CKVideo.h"
#include "k2000/input/CKInputDico.h"
#include "k2000/managers/CKInput.h"
#include "k2000/misc/CKGameLoop.h"
#include "k2000/misc/Engine.h"
#include "k2000/system/IKTime.h"
#include "k2000/ui/IKNode2d.h"
#include "k2000/components/CKLocTextAccessor.h"
#include "k2000/system/IKTime.h"
#include "Spyro2008/logic/CKS08GameStructure.h"
#include "k2000/components/CKBonusData.h"
#include "k2000/logic/CKGameState.h"
#include "k2000/logic/IKPlayer.h"
#include "k2000/logic/KBase60CC.h"
#include "k2000/services/CKSrvInput.h"
#include "k2000/system/CTimeManager.h"

// 0x004f9408 CKS08GameManager_Construct, with the IKCommonGameManager part of 0x004edee0
// CKS08GameManager_ConstructBase_maybe (CDefaultGameManager's constructor has the IKGameManager part).
CKS08GameManager::CKS08GameManager() {
    m_unk2BC.m_ui32NbElt = 10;
    m_unk2BC.m_pBlock = nullptr;
    m_unk2BC.m_ui32NbUsedElt = 0;
    m_unk2D0.m_ui32NbElt = 8;
    m_unk2D0.m_pBlock = nullptr;
    m_unk2D0.m_ui32NbUsedElt = 0;
    m_gameState.m_ui8Current = 0xff;
    m_gameState.m_pOwner = nullptr;
    m_interfaceState.m_ui8Current = 0xff;
    m_gameState.m_pTable = nullptr;
    m_gameState.m_ui8Count = 0;
    m_interfaceState.m_pOwner = nullptr;
    m_interfaceState.m_pTable = nullptr;
    m_interfaceState.m_ui8Count = 0;
    m_ui32MenuStackDepth = 0;
    m_unk468[0] = 0.0f;
    m_unk468[2] = 0.0f;
    m_unk468[1] = 0.0f;
    m_unk474.m_ui32NbElt = 8;
    m_unk474.m_pBlock = nullptr;
    m_unk474.m_ui32NbUsedElt = 0;
    m_unk4DC = 0.0f;
    m_unk4CD = 0;
    m_unk4D0 = 0;
    std::memset(m_unk6E4, 0, sizeof(m_unk6E4));
    std::memset(m_unk4E4, 0, sizeof(m_unk4E4));
    m_unkAE4 = nullptr;
    // CKS08GameManager_Construct
    m_unkAE9 = 0;
    m_unkBB4.m_pBlock = nullptr;
    m_unkBB4.m_ui32NbUsedElt = 0;
    m_unkBC8.m_ui32NbElt = 5;
    m_unkBC8.m_ui32NbUsedElt = 0;
    m_unkBC8.m_pBlock = nullptr;
    m_unkBB4.m_ui32NbElt = 5;
    m_unkBB4.m_pBlock = static_cast<IKSerializable**>(Mem_AllocAligned16(5 * static_cast<uint32_t>(sizeof(IKSerializable*))));
    m_unkBC8.m_ui32NbElt = 5;
    m_unkBC8.m_pBlock = static_cast<IKSerializable**>(Mem_AllocAligned16(5 * static_cast<uint32_t>(sizeof(IKSerializable*))));
}

// 0x004fc010 CKS08GameManager_LoadRefTableE4C_maybe: a level's table of references, rows of three
// (a word the Load drops, the row count, the column count, then row by row).
void CKS08GameManager::LoadRefTable(IKFile* stream, int32_t mode) {
    if (mode != 0) return;
    uint32_t unused = 0;
    ReadRaw(stream, &unused, 4);
    uint32_t rows = 0;
    ReadU32LE(stream, &rows);
    uint32_t columns = 0;
    ReadU32LE(stream, &columns);
    for (uint32_t row = 0; row < rows; ++row) {
        for (uint32_t column = 0; column < columns; ++column) IKFile_ReadRef(stream, &m_aRefTable[row][column]);
    }
}

// 0x004fc228 CKS08GameManager_Load: the common part, the HUD resources, then GAME's six bytes (mode 1)
// or a level's references (mode 0), and the level's reference table.
int32_t CKS08GameManager::Load(IKFile* stream, int32_t mode) {
    LoadCommon(stream, mode);
    LoadHudResources(stream, mode);
    if (mode == 1) {
        for (uint8_t& value : m_unkAF4) ReadU8(stream, &value);
    } else if (mode == 0) {
        IKFile_ReadRef(stream, &m_unkD88);
        IKFile_ReadObjectRefArray(stream, m_unkD9C, 2);
        IKFile_ReadRef(stream, &m_unkD98);
        ReadU32LE(stream, &m_unkD94);
        ReadU32LE(stream, &m_unkDA4);
        IKFile_ReadRef(stream, &m_unkDA8);
        ReadU32LE(stream, &m_unkDC0);
        ReadU32LE(stream, &m_unkDC4);
        ReadU32LE(stream, &m_unkDC8);
        IKFile_ReadRef(stream, &m_unkDAC);
        IKFile_ReadRef(stream, &m_unkDB0);
        IKFile_ReadRef(stream, &m_unkDB4);
        ReadU32LE(stream, &m_unkDEC);
        ReadU32LE(stream, &m_unkDE8);
        ReadU32LE(stream, &m_unkDF0);
        IKFile_ReadRef(stream, &m_unkDDC);
        IKFile_ReadRef(stream, &m_unkDE0);
        IKFile_ReadRef(stream, &m_unkDE4);
        IKFile_ReadRef(stream, &m_unkBDC);
        for (uint32_t i = 5; i != 0;) {  // from the last record
            --i;
            ReadU32LEWords(stream, &m_aUnkC48[i].m_unk0, 3);
        }
        for (uint32_t i = 5; i != 0;) {
            --i;
            ReadU32LEWords(stream, &m_aUnkC84[i].m_unk0, 3);
        }
        IKFile_ReadRef(stream, &m_unkE38);
        IKFile_ReadRef(stream, &m_unkE44);
        IKFile_ReadRef(stream, &m_unkE40);
        IKFile_ReadRef(stream, &m_unkE3C);
        IKFile_ReadRef(stream, &m_unkE88[2]);  // +0xe90
        IKFile_ReadRef(stream, &m_unkE88[1]);  // +0xe8c
        IKFile_ReadRef(stream, &m_unkEC4);
        for (IKSerializable*& slot : m_unkEC8) IKFile_ReadRef(stream, &slot);
        IKFile_ReadRef(stream, &m_unkAEC);
        uint32_t count = 0;
        ReadU32LE(stream, &count);
        IKSerializable** list = m_unkE88;
        for (uint32_t i = 0; i < count; ++i) IKFile_ReadRef(stream, &list[i]);  // BUG(original): no bound
        ReadU32LEWords(stream, m_unkEA8, 6);
        IKFile_ReadRef(stream, &m_unkEC0);
        m_unkB00.Load(stream, 0);
        for (IKSerializable*& slot : m_unkF00) {  // +0xf00 .. +0xf18
            IKFile_ReadRef(stream, &slot);
        }
        IKFile_ReadRef(stream, &m_unkF20);
        IKFile_ReadRef(stream, &m_unkF24);
        IKFile_ReadRef(stream, &m_unkAF0);
        IKFile_ReadRef(stream, &m_unkEF8);
        IKFile_ReadRef(stream, &m_unkEFC);
    }
    LoadRefTable(stream, mode);
    return 1;
}

// 0x004f6698 CKS08GameManager_InitStateHandlerTable: Spyro's states over IKCommonGameManager's.
void CKS08GameManager::InitStateHandlerTable(StateHandler* table) {
    table[9] = &CKS08GameManager::StateHeroDeath;
    table[2] = &CKS08GameManager::State2;
    table[4] = &CKS08GameManager::State4;
    table[5] = &CKS08GameManager::State5;
    table[6] = &CKS08GameManager::State6;
    table[7] = &CKS08GameManager::StateInGame;
    table[8] = &CKS08GameManager::StateMenuPause;
}

// 0x004f6838 CKS08GameManager_CallMember2E0Vf60Arg0_maybe: the demo video played.
void CKS08GameManager::PlayDemoVideo() {
    if (m_unk2E0 != nullptr) static_cast<IKVideo*>(m_unk2E0)->Start(nullptr);
}

// 0x004f6890 CKS08GameManager_CallMember2E0Vf78_maybe: the demo video stopped.
void CKS08GameManager::StopDemoVideo() {
    if (m_unk2E0 != nullptr) static_cast<IKVideo*>(m_unk2E0)->Stop();
}

// 0x004f7158 CKS08GameManager_vf240: IKCommonGameManager's.
void CKS08GameManager::Vf240(int32_t result) { Vf240Common(result); }

// 0x004f68e0 CKS08GameManager_vf158: 1..GetMaxPlayers players; player 0 active, player 1 when there are two.
uint8_t CKS08GameManager::SetPlayerCount(uint32_t count) {
    if (count == 0 || count > GetMaxPlayers()) return 0;
    m_unkAE9 = static_cast<uint8_t>(count);
    SetPlayerActive(0, 1);
    SetPlayerActive(1, GetPlayerCount() == 2 ? 1 : 0);
    return 1;
}

// 0x004f6eb8 CKS08GameManager_vfAC: the front end restarts: bit 5 of +0xafc cleared, IKCommonGameManager's,
// one player (vt+0x158), KStub_Nop_4ec920(this, 0) (empty), the HUD panels' element 0, then the seven
// players' vt+0x60 (empty for CKS08Player), from +0x5c down to +0x44.
void CKS08GameManager::VfAC() {
    m_unkAFC &= ~0x20u;
    VfACCommon();
    SetPlayerCount(1);
    SelectSpyroHudPanelElement(0);
    SelectCynderHudPanelElement(0);
    for (uint32_t i = 7; i != 0; --i) static_cast<IKPlayer*>(m_players[i - 1])->Vf60();
}

// 0x004f7c28 CKS08GameManager_Destroy
void CKS08GameManager::Destroy() {
    DestroyCommon();  // 0x4ed790
    m_unkD88 = nullptr;
    DestroyTextures();
    m_unkF24 = nullptr;
    m_unkF20 = nullptr;
}

// 0x004f7180 CKS08GameManager_PostLoad: IKCommonGameManager's, then (a level) the trigger list and the
// two pairs of HUD vectors cleared (TOC1 +0x721c: the zero vector).
int32_t CKS08GameManager::PostLoad(int32_t type) {
    PostLoadCommon(type);
    if (type == 0) {
        // TriggerEventList_PostLoad_maybe(+0xb00) returns 1. +0xdf8..+0xe34 (CKS08GameManager_PostLoad):
        // the three-float vectors at +0xe18, +0xe24, +0xdf8, +0xe04 (zero), the bytes +0xe30/+0xe31 and
        // +0xe10/+0xe11, the words +0xe34 and +0xe14: all 0.
        for (uint32_t i = 1; i <= 0x10; ++i) m_unkDF4[i] = 0;
    }
    return 1;
}

// 0x004f8d08 CKS08GameManager_Start: IKGameManager_ResetRuntimeImpl, then Spyro's run state: the dragon
// stat HUD, the four vectors (TOC1 +0x721c: the zero vector) and their bytes and words, the bonus data
// (+0xec0), the counters, and the input service's blocks 0 and 1 activated (vt+0x50).
void CKS08GameManager::Start() {
    m_unkEA4 &= 0x00ffffffu;  // the byte at +0xea4
    // KStub_Nop_4fe308(this): empty.
    ResetRuntime();
    m_unkAFC &= 0xffffff3fu;
    ResetDragonStatHud();
    for (uint32_t i = 1; i <= 0x10; ++i) m_unkDF4[i] = 0;  // +0xdf8..+0xe34 (the zero vectors, bytes and words)
    static_cast<CKBonusData*>(m_unkEC0)->ResetRuntime();
    m_unkF1C = 0;
    m_unkAFC &= ~0x100u;
    m_unkEA0 = -0x1p+0f;  // TOC1 +0x7204: -1.0
    m_afUnkBAC[1] = 0.0f;
    m_afUnkBAC[0] = 0.0f;
    m_unkBB4.m_ui32NbUsedElt = 0;
    m_unkBC8.m_ui32NbUsedElt = 0;
    m_unkAFC &= 0xfffff9ffu;
    m_unkDCC[0] = 0;
    m_unkDCC[1] = 0;
    m_unkDCC[2] = 0;
    CKSrvInput* service = static_cast<CKSrvInput*>(g_pEngine->m_srvInput);
    if (KBase60CC* block = service->GetInputBlock(0)) block->OnActivate();  // vt+0x50
    if (KBase60CC* block = service->GetInputBlock(1)) block->OnActivate();
    m_unkF28 &= 0x00ffffffu;  // the byte at +0xf28
}

// 0x004f8f78 CKS08GameManager_Update: IKGameManager_Update, then (game state 7, in game) the HUD, the effect
// the hero asked for and the countdown of the save request.
void CKS08GameManager::Update(IKTime* frameClock) {
    UpdateCommon(frameClock);
    if ((m_unkEA4 >> 24) != 0) {
        m_unkEA4 &= 0x00ffffffu;
        // KStub_Nop_13070(this, the game structure's current spawn point's sector): empty.
    }
    if (m_gameState.m_ui8Current != 7) return;
    UpdateInGameHud(frameClock);
    if ((m_unkAFC & 0x100) != 0 && m_unkF1C == 0) {
        // The FX data +0xf18 asks for its effect: the FX service's unique effects (or, for a shared one, the
        // first free node of its class and type) take it (IKFx vt+0x84 / +0x88 / +0x8c: the data and this as
        // owner, then vt+0x64), and +0xf1c remembers the effect. STUB(C2.7, the FX service): the IKFx slots are not declared
        // yet (k2000/fx/IKFx.h); the flag is cleared at the level start and no effect is running then.
        DOTD_STUB_ONCE("CKS08GameManager_Update: start the effect of the FX data +0xf18 (flag 0x100)");
    }
    // The save request's countdown (+0xea0, -1 off): at zero the request goes out (vt+0x104).
    if (m_unkEA0 >= 0.0f) {
        m_unkEA0 = m_unkEA0 - frameClock->m_afDeltaTime[IKTime::SCALABLE_GAME_TIME];
        if (m_unkEA0 <= 0.0f) {
            RequestSave(0, 0);  // vt+0x104
            m_unkEA0 = -0x1p+0f;  // TOC1 +0x7204
        }
    }
}

// 0x009c6da8 CKS08GameManager_vf214: a text of the +0x144 CKLocTextAccessor: its 13th text, else its default.
IKSerializable* CKS08GameManager::Vf214() {
    CKLocTextAccessor* texts = static_cast<CKLocTextAccessor*>(m_unk144);
    if (texts->m_texts.m_pBlock != nullptr) return texts->m_texts.m_pBlock[0xc];
    return texts->m_pText;
}

// ---- C1.6 gm ----
// 0x004f6b48 CKS08GameManager_vf31C (Ghidra GetPointerPosition_maybe): -1.0 (0xbf800000) into +0x29c and
// +0x298 of the player's pair, and returned.
CVector2 CKS08GameManager::GetPointerPosition(int32_t player) {
    m_afUnk298[player * 2 + 1] = -0x1p+0f;
    m_afUnk298[player * 2] = -0x1p+0f;
    return CVector2{-0x1p+0f, -0x1p+0f};
}

// 0x004f6bc0 CKS08GameManager_vf1D4: IKCommonGameManager_vf1D4.
void CKS08GameManager::ResetEditedOptions() { ResetEditedOptionsCommon(); }

// 0x004f6be8 CKS08GameManager_GetDirectionActionState_maybe (vt+0x188; step 5, the camera track's right stick)
uint8_t CKS08GameManager::GetDirectionActionState(uint8_t direction) {
    if (m_unkAE9 == 0) return 0;
    uint32_t held = 0;
    uint32_t sum = 0;
    uint32_t counter = 0;
    uint32_t player = 0;
    do {
        uint32_t mapped = direction;
        if (Vf1BC(static_cast<int32_t>(player)) != 0) {
            if (direction == 2) mapped = 3;
            else if (direction == 3) mapped = 2;
        }
        mapped &= 0xffu;
        if (Vf1B4(static_cast<int32_t>(player)) != 0) {
            if (mapped == 0) mapped = 1;
            else if (mapped == 1) mapped = 0;
        }
        const uint32_t entry = (player * 0x32 + m_unk498[mapped]) & 0xffu;
        const uint8_t state = m_pCommonInputDicos->GetButtonState(static_cast<int32_t>(entry));
        if (state != 0) {
            held = held + 1;
            sum = sum + state;
        }
        counter = counter + 1;
        player = counter & 0xffu;
    } while (m_unkAE9 > player);
    if ((held & 0xffu) == 0) return 0;
    return static_cast<uint8_t>(ppc::divw(static_cast<int32_t>(sum & 0xffffu), static_cast<int32_t>(held & 0xffu)));
}

// 0x004f80f8 CKS08GameManager_ResetGameProgress_maybe (XXL2 NewGame)
void CKS08GameManager::NewGame() {
    NewGameCommon();
    m_unkE94[1] = 0xffffffffu;  // +0xe98
    static_cast<CKS08GameStructure*>(m_gameStructure)->ResetProgress();
    Vf2F0(0);                   // vt+0x2f0
    static_cast<IKPlayer*>(m_players[0])->CopyGameStructure();  // +0x44 vt+0x58
    static_cast<IKPlayer*>(m_players[6])->CopyPlayerGameData(static_cast<IKPlayer*>(m_players[0]));  // +0x5c vt+0x50
    if ((m_flags64 & 0x80u) != 0) static_cast<IKGameStructure*>(m_gameStructure)->Vf58();
}

// 0x004f8b50 CKS08GameManager_vf320
void CKS08GameManager::Vf320() {
    CKSrvInput* service = static_cast<CKSrvInput*>(g_pEngine->m_srvInput);
    KBase60CC* block = service->GetInputBlock(0);
    if (block != nullptr && block->m_unk0e != 0)
        block->Update(g_pEngine->m_timeManager->m_pTime->m_afDeltaTime[IKTime::SYSTEM_TIME]);  // vt+0x58
    block = service->GetInputBlock(1);
    if (block != nullptr && block->m_unk0e != 0)
        block->Update(g_pEngine->m_timeManager->m_pTime->m_afDeltaTime[IKTime::SYSTEM_TIME]);
    GetPointerPosition(0);  // vt+0x31c
    GetPointerPosition(1);
}

namespace {
// A CKLocTextAccessor's text: its list's entry `index` when it has a list (+0x04), else its single text (+0x10).
IKSerializable* AccessorText(IKSerializable* accessor, uint32_t index) {
    CKLocTextAccessor* texts = static_cast<CKLocTextAccessor*>(accessor);
    return texts->m_texts.m_pBlock != nullptr ? texts->m_texts.m_pBlock[index] : texts->m_pText;
}

// 0x2650..0x2653: the boss HUD (GetHudInterfaces()[3], [4] in levels with a second one) posts its flash message 2 (show) or
// 1 (hide; then the byte +0xe0 bit 0 and the timer +0xf0 cleared).
void PostBossHudMessage(CKS08InGameInterfaceBoss* boss, bool hide) {
    if (!hide) {
        IKSerializable* out = boss->VfC0()[2];  // vt+0xc0
        if (out != nullptr) static_cast<CKFlashMessageOut*>(out)->PostFlashMessage();
        return;
    }
    IKSerializable* out = boss->VfC0()[1];
    if (out != nullptr) static_cast<CKFlashMessageOut*>(out)->PostFlashMessage();
    boss->m_baFlagsE0 = static_cast<uint8_t>(boss->m_baFlagsE0 & 0xfe);
    boss->m_fTime = 0.0f;
}
}  // namespace

// 0x004fa438 CKS08GameManager_MessageProc. With the debug flag (VfC4) the id 0x2667 is refused. Then HandleUIMessage, then the
// scripts' ids: the jump table 0x263c..0x270a (the ids it does not list go on to the objective ids 0x26cb..0x26fa, which
// sit in its range). "dispatched" is 1 for an id of neither table and 0 once one took it; the answer combines it with
// HandleUIMessage's.
int32_t CKS08GameManager::MessageProc(uint16_t message, void* data) {
    if (VfC4() != 0 && message == 0x2667) return 1;
    const uint8_t uiResult = HandleUIMessage(message, data);
    const CTriggerAction* action = static_cast<const CTriggerAction*>(data);
    CKS08GameStructure* structure = static_cast<CKS08GameStructure*>(m_gameStructure);  // +0x6c
    int32_t dispatched = 0;
    // The info pages' messages need the option on, no debug flag and no pages showing (+0xafc bit 7).
    auto infoPagesFree = [&]() { return structure->AreInfoPopupsEnabled() != 0 && VfC4() == 0 && (m_unkAFC & 0x80) == 0; };
    CKS08MenuPauseInfo* info = static_cast<CKS08MenuPauseInfo*>(Vf344()[0x10]);  // vt+0x344, menu 0x10
    switch (message) {
    case 0x263c: structure->m_unk1e4[0] = static_cast<uint8_t>(action->m_mdParam.m_ui32Value); break;
    case 0x263d: structure->m_unk1e4[1] = static_cast<uint8_t>(action->m_mdParam.m_ui32Value); break;
    case 0x263e: structure->m_unk1e4[2] = static_cast<uint8_t>(action->m_mdParam.m_ui32Value); break;
    case 0x263f: structure->m_unk1e4[3] = static_cast<uint8_t>(action->m_mdParam.m_ui32Value); break;
    case 0x2640: structure->m_unk1e4[4] = static_cast<uint8_t>(action->m_mdParam.m_ui32Value); break;
    case 0x2641: ++structure->m_unk1e4[0]; break;
    case 0x2642: ++structure->m_unk1e4[1]; break;
    case 0x2643: ++structure->m_unk1e4[2]; break;
    case 0x2644: ++structure->m_unk1e4[3]; break;
    case 0x2645: ++structure->m_unk1e4[4]; break;
    case 0x2646: structure->SetUnlockFlagByte(static_cast<int32_t>(action->m_mdParam.m_ui32Value), 1); break;
    case 0x2647: structure->m_unk1e4[5] = static_cast<uint8_t>(action->m_mdParam.m_ui32Value); break;
    case 0x2648: ++structure->m_unk1e4[5]; break;
    case 0x2649: if (structure->m_unk1e4[0] != 0) --structure->m_unk1e4[0]; break;
    case 0x264a: if (structure->m_unk1e4[1] != 0) --structure->m_unk1e4[1]; break;
    case 0x264b: if (structure->m_unk1e4[2] != 0) --structure->m_unk1e4[2]; break;
    case 0x264c: if (structure->m_unk1e4[3] != 0) --structure->m_unk1e4[3]; break;
    case 0x264d: if (structure->m_unk1e4[4] != 0) --structure->m_unk1e4[4]; break;
    case 0x264e: if (structure->m_unk1e4[5] != 0) --structure->m_unk1e4[5]; break;
    case 0x264f:  // the info pages: no slow motion, the pages pending
        if (infoPagesFree()) {
            info->m_bTimeScaling = 0;
            m_unkAFC |= 0x80;
        }
        break;
    case 0x2650:
    case 0x2651:
    case 0x2652:
    case 0x2653: {
        IKSerializable* boss = GetHudInterfaces()[message <= 0x2651 ? 3 : 4];  // vt+0x34c
        if (boss != nullptr) PostBossHudMessage(static_cast<CKS08InGameInterfaceBoss*>(boss), (message & 1) == 0);
        break;
    }
    case 0x26c8:  // the info pages with the slow motion, pending
        if (infoPagesFree()) {
            info->m_bTimeScaling = 1;
            m_unkAFC |= 0x80;
        }
        break;
    case 0x26c9:  // the info pages' title
        if (infoPagesFree() && action->m_mdParam.m_pObject != nullptr) info->SetTitleText(action->m_mdParam.m_pObject);
        break;
    case 0x26ca:  // an info page (the vector grows by 3)
        if (infoPagesFree() && action->m_mdParam.m_pObject != nullptr) {
            TVector<IKSerializable*, 3>& pages = info->m_aPageTextIds;
            if (pages.m_ui32NbUsedElt == pages.m_ui32NbElt) {
                uint32_t capacity = pages.m_ui32NbElt + 3;
                if (capacity == 0) capacity = 3;
                pages.m_pBlock = static_cast<IKSerializable**>(
                    Mem_ReallocAligned16(pages.m_pBlock, capacity * static_cast<uint32_t>(sizeof(IKSerializable*))));
                pages.m_ui32NbElt = capacity;
            }
            pages.m_pBlock[pages.m_ui32NbUsedElt++] = action->m_mdParam.m_pObject;
        }
        break;
    case 0x2704:
    case 0x2705:
    case 0x2706:
    case 0x2707:
    case 0x2708:
    case 0x2709:
        break;  // in the table, nothing done
    case 0x270a: structure->SaveCheckpointSnapshot(); break;
    default:
        if (message >= 0x26cb && message <= 0x26fa) {
            // The objective lists: id 0x26cb + 4 * list + op, the objective index in the parameter. The objective's state
            // byte (the game structure's byte list +0x154 + list * 0xc) becomes the op; ops 1 and 2 show its HUD text (the
            // entry's text accessor, first text): op 1 queued (+0x06 set) or with the accessor +0xec4's first text, op 2
            // with its second text unless +0x06 is set.
            const uint32_t list = static_cast<uint32_t>(message - 0x26cb) >> 2;
            const uint32_t op = static_cast<uint32_t>(message - 0x26cb) & 3;
            const uint32_t index = action->m_mdParam.m_ui32Value;
            structure->m_avbUnk154[list].m_pBlock[index] = static_cast<uint8_t>(op);
            if (op == 1 || op == 2) {
                const CKS08ObjectiveList::Entry& entry = static_cast<CKS08ObjectiveList*>(m_unkEC8[list])->m_aEntries[index];
                IKSerializable* text = AccessorText(entry.m_pObject, 0);
                if (entry.m_ui16Unk6 != 0) {
                    if (op == 1) QueueHudMessage(text);
                } else if (op == 1) {
                    ShowCenterHudMessage(text);
                } else {
                    ShowCenterHudMessagePairSecond(text);
                }
            }
        } else {
            dispatched = 1;
        }
        break;
    }
    if (uiResult == 3 || dispatched == 3) return 3;
    if (uiResult == 2 || dispatched == 2) return 2;
    return uiResult != 0 ? dispatched : 0;
}

// 0x004fefd8 CKS08GameManager_QueueHudMessage_maybe
void CKS08GameManager::QueueHudMessage(IKSerializable* text) {
    IKSerializable* center = GetHudInterfaces()[1];  // vt+0x34c
    if (center != nullptr) static_cast<CKS08InGameInterfaceCenter*>(center)->QueueMessage(text);
}

// 0x004ff080 CKS08GameManager_ShowCenterHudMessagePairSecondFromTable_maybe
void CKS08GameManager::ShowCenterHudMessagePairSecond(IKSerializable* text) {
    IKSerializable* center = GetHudInterfaces()[1];
    if (center != nullptr) static_cast<CKS08InGameInterfaceCenter*>(center)->ShowOrQueueMessagePair(text, AccessorText(m_unkEC4, 1));
}

// 0x004ff150 CKS08GameManager_ShowCenterHudMessage_maybe
void CKS08GameManager::ShowCenterHudMessage(IKSerializable* text) {
    IKSerializable* center = GetHudInterfaces()[1];
    if (center != nullptr) static_cast<CKS08InGameInterfaceCenter*>(center)->ShowOrQueueMessagePair(AccessorText(m_unkEC4, 0), text);
}

// 0x004f1f88 CKS08GameManager_CheckPauseOrSkipRequest_maybe. In game (state 7), with no save-data request pending, no game video
// playing and the interface not on its state 0x10: START with a skippable scene playing restores the sound volume and asks
// the skip prompt (+0x4d0 = 2 tells the answer, message 0x2d00, what it was for; the game loop is inhibited meanwhile);
// otherwise the pause button (entry 0, or entry 0x32 of the second player) switches to the pause state 8 and anything
// else leaves +0x4cd = 1 for HandlePauseInput's own button check.
void CKS08GameManager::CheckPauseRequest() {
    m_unk4CD = 0;
    if (m_gameState.m_ui8Current != 7) return;
    if (Vf108() != 0) return;
    if (g_pEngine->m_videoManager->HasVideoWithoutFlag40() != 0) return;
    if (Vf35C() == 0) return;
    CKSrvCinematic* cinematic = static_cast<CKSrvCinematic*>(g_pEngine->m_srvCinematic);
    const bool skipRequested = cinematic->IsSkippableScenePlaying() != 0 && CKSrvCinematic::IsStartPressedAnyPlayer() != 0;
    const uint8_t pause = m_pCommonInputDicos->GetButtonState(0);
    const bool secondPause = GetPlayerCount() >= 2 && m_pCommonInputDicos->GetButtonState(0x32) == 0xff;
    if (skipRequested) {
        g_pEngine->m_soundManager->RestoreSavedVolume(1);
        m_unk4D0 = 2;
        MessageBox_Show(1.0f, -1.0f, this, GetSkipCinematicPromptText(), 3, 6);
        ++g_pEngine->m_gameLoop->m_inhibitCount;  // CKGameLoop_IncPauseCount_maybe
    } else if (pause == 0xff || secondPause) {
        m_gameState.Switch(8);
    } else {
        m_unk4CD = 1;
    }
}

// 0x004fb3d8 CKS08GameManager_HandlePauseInput_maybe: CheckPauseRequest, then (+0x4cd) the pause: flag +0xafc bit 9 (a
// forced pause) switches to state 8; unless bit 7 is set, the pause button (entry 1, or entry 0x33 with two players
// and the controller mode 2) does too, with the flag +0xafc bit 6 set. (KStub_Nop_4ec920 after the switch is empty.)
void CKS08GameManager::HandlePauseInput(IKTime* /*frameClock*/) {
    CheckPauseRequest();
    if (m_unk4CD == 0) return;
    if ((m_unkAFC & 0x200) != 0) {
        m_gameState.Switch(8);
        return;
    }
    if ((m_unkAFC & 0x80) != 0) return;
    if (m_pCommonInputDicos->GetButtonState(1) == 0xff) {
        m_unkAFC = (m_unkAFC & 0xffffffbfu) | 0x40;
        m_gameState.Switch(8);
    } else if (GetPlayerCount() == 2 && m_pCommonInputDicos->GetButtonState(0x33) == 0xff) {
        m_unkAFC = (m_unkAFC & 0xffffffbfu) | 0x40;
        m_gameState.Switch(8);
    }
}

// 0x004f6e78 CKS08GameManager_GetFocusedHeroCamera_maybe, with 0x002d4bc0 CKGrpS08Hero_GetFocusedHeroCamera_maybe: the
// hero of the group's list at the focused index (byte +0x66), its camera target (+0x1818).
// The focus index is set by the hero group's PostLoad (SetFocusedDragon 0x2cc3f0, CKGrpS08Hero_3.cpp); before that it is
// 0xff, which the original would read past the list with. No camera target stands in for it.
IKSerializable* CKS08GameManager::GetFocusedHeroCamera() {
    IKGrpHero* group = static_cast<IKGrpHero*>(m_unk04[1]);
    if (group == nullptr) return nullptr;
    if (group->m_unk66 == 0xff) {
        DOTD_STUB_ONCE("CKGrpS08Hero_GetFocusedHeroCamera_maybe: no focused hero yet (before the hero group's PostLoad)");
        return nullptr;
    }
    return static_cast<CKHkS08Hero*>(group->m_apHeros[group->m_unk66])->m_unk1818;
}

// 0x004f88f8 CKS08GameManager_GetGroundSurfaceBit_maybe
uint16_t CKS08GameManager::GetGroundSurfaceBit(const IKSerializable* ground) const {
    const ICollisionMesh* mesh = static_cast<const ICollisionMesh*>(ground);
    if (((mesh->m_ba16EngineFlags >> 6) & 1) != 0) return 1;
    if ((mesh->m_ui16PropertiesFlags & 0x200) != 0 && (mesh->m_ba16EngineFlags & 2) == 0) return 1;
    return static_cast<uint16_t>((mesh->m_ui16PropertiesFlags >> 1) & 1);
}

// ---- step 4 ANIM: the dragon stats. ----
namespace {
CKS08GameStructure* DragonStats(CKS08GameManager* manager) {
    return static_cast<CKS08GameStructure*>(manager->m_gameStructure);  // +0x6c
}
}  // namespace

// 0x004fd628 GetArmorMeshHiddenFlag_maybe
uint8_t CKS08GameManager::GetArmorMeshHiddenFlag(int32_t dragon) {
    return DragonStats(this)->RtByte(dragon != 0 ? 0xba : 0xbb);
}

// 0x004fd658 GetEquippedArmor_maybe
uint8_t CKS08GameManager::GetEquippedArmor(int32_t dragon, int32_t slot) {
    return DragonStats(this)->RtByte(static_cast<uint32_t>(dragon * 3 + slot + 0xb4));
}

// 0x004fd740 GetDragonManaCapacity: the dragon's mana capacity (the collected upgrades only).
uint32_t CKS08GameManager::GetDragonManaCapacity(int32_t dragon) {
    if (dragon == 0) return static_cast<uint32_t>(ComputeSpyroManaCapacity(DragonStats(this), 0));  // 0x00511710
    if (dragon != 1) return 0;
    return static_cast<uint32_t>(ComputeCynderManaCapacity(DragonStats(this), 0));  // 0x005115d0
}

// 0x004fd7c8 GetDragonMana
uint32_t CKS08GameManager::GetDragonMana(int32_t dragon) {
    if (dragon == 0) return DragonStats(this)->m_unk64;
    if (dragon != 1) return 0;
    return DragonStats(this)->m_unk6c;
}

// 0x004fd808 ConsumeDragonMana: the mana less `amount`, not below 0; the mana display refreshed.
void CKS08GameManager::ConsumeDragonMana(int32_t dragon, uint32_t amount) {
    if (dragon == 0) {
        CKS08GameStructure* stats = DragonStats(this);
        stats->m_unk64 = amount < stats->m_unk64 ? stats->m_unk64 - amount : 0;
        RefreshDragonStatDisplays(0, 0, 1);  // 0x005022b0
        return;
    }
    if (dragon != 1) return;
    CKS08GameStructure* stats = DragonStats(this);
    stats->m_unk6c = amount < stats->m_unk6c ? stats->m_unk6c - amount : 0;
    RefreshDragonStatDisplays(1, 0, 1);
}

// 0x004fd940 GetDragonHealthCapacity: the dragon's health capacity (the collected upgrades only).
uint32_t CKS08GameManager::GetDragonHealthCapacity(int32_t dragon) {
    if (dragon == 0) return static_cast<uint32_t>(ComputeSpyroHealthCapacity(DragonStats(this), 0));  // 0x005111a0
    if (dragon != 1) return 0;
    return static_cast<uint32_t>(ComputeCynderHealthCapacity(DragonStats(this), 0));  // 0x00511060
}

// 0x004fd9c8 GetDragonHealth
uint32_t CKS08GameManager::GetDragonHealth(int32_t dragon) {
    if (dragon == 0) return DragonStats(this)->m_unk4c;
    if (dragon != 1) return 0;
    return DragonStats(this)->m_unk54;
}

// 0x004fda08 DamageDragon: the health less `amount`, not below 0; the health display refreshed.
void CKS08GameManager::DamageDragon(int32_t dragon, uint32_t amount) {
    if (dragon == 0) {
        CKS08GameStructure* stats = DragonStats(this);
        stats->m_unk4c = amount < stats->m_unk4c ? stats->m_unk4c - amount : 0;
        RefreshDragonStatDisplays(0, 1, 0);  // 0x005022b0
        return;
    }
    if (dragon != 1) return;
    CKS08GameStructure* stats = DragonStats(this);
    stats->m_unk54 = amount < stats->m_unk54 ? stats->m_unk54 - amount : 0;
    RefreshDragonStatDisplays(1, 1, 0);
}
