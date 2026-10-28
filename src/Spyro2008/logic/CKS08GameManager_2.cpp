// CKS08GameManager_2.cpp - reconstructed original translation unit 0x4ec6e8-0x4f4708 (GAME_TOC1, main_toc1), 84 functions, 83 live.
// Primary class: CKS08GameManager  key 0x784c  category Logic  size 0xf2c  vtable 0xb2af78
// Other owners: KBase3B0C (16), CKS08GameManagerBase (4), SetHeroInteractionTarget (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x4ec6e8  CKS08GameManager_NotifyInputActivity_maybe
//   [ ] 0x4ec798  CKS08GameManager_IsFlag480ClearedThisFrame_maybe
//   [ ] 0x4ec7d0  KStub_ReturnM1_4ec7d0
//   [ ] 0x4ec7d8  IKCommonGameManager_vf2D8
//   [ ] 0x4ec7e0  IKCommonGameManager_vf2DC
//   [ ] 0x4ec7e8  CKS08GameManager_vf15C
//   [x] 0x4ec878  CKS08GameManager_vfF4
//   [x] 0x4ec918  KStub_Return1_4ec918
//   [x] 0x4ec920  KStub_Nop_4ec920
//   [ ] 0x4ec928  CKS08GameManager_vf228
//   [ ] 0x4ec938  CKS08GameManager_vf22C
//   [ ] 0x4ec948  FUN_004ec948  [dead]
//   [x] 0x4ec968  CKS08GameManager_SetActiveCameraIndex_maybe
//   [x] 0x4ec9b8  CKS08GameManager_PickRandomTipText_maybe
//   [ ] 0x4eccb0  CKS08GameManager_vf190
//   [x] 0x4ecd10  CKS08GameManager_vf18C
//   [ ] 0x4ecd70  IKCommonGameManager_GetDirectionActionState_maybe
//   [x] 0x4ecdd0  CKS08GameManager_IsActionPressed
//   [ ] 0x4ecea8  CKS08GameManager_vf168
//   [x] 0x4ecf80  CKS08GameManager_GetActionValue
//   [x] 0x4ed058  IKCommonGameManager_vf1D4
//   [x] 0x4ed080  CKS08GameManager_ResetFadeVideoIfMode2ThenVf338_maybe
//   [x] 0x4ed198  CKS08GameManager_IsTrackedLevelCurrent_maybe
//   [x] 0x4ed1f8  CKS08GameManager_vf108
//   [x] 0x4ed220  CKS08GameManager_RequestSave_maybe
//   [x] 0x4ed298  CKS08GameManager_vfB4
//   [ ] 0x4ed2c0  CKS08GameManager_vfB0
//   [x] 0x4ed2e8  CKS08GameManager_InitDefaultOptions_maybe
//   [x] 0x4ed310  CKS08GameManager_SectorLoaded
//   [x] 0x4ed440  CKS08GameManager_Resume
//   [x] 0x4ed540  CKS08GameManager_Pause
//   [ ] 0x4ed670  IKCommonGameManager_Save
//   [ ] 0x4ed698  IKCommonGameManager_LevelReset
//   [ ] 0x4ed6c0  CKS08GameManager_DestroyGame
//   [x] 0x4ed790  IKCommonGameManager_ClearReferences
//   [x] 0x4ed7d8  CKS08GameManager_SetAllHeroesInvulnerable_maybe
//   [x] 0x4ed878  CKS08GameManager_IsInputBlocked_maybe
//   [x] 0x4ed8b8  CKS08GameManager_SetInputBlocked_maybe
//   [x] 0x4ed8f0  CKS08GameManager_GetControlledHeroCount
//   [x] 0x4ed930  CKS08GameManager_GetFocusedHeroMoveVector_maybe
//   [ ] 0x4ed9c0  CKS08GameManager_GetFocusedHeroNodeForward_maybe
//   [x] 0x4eda18  CKS08GameManager_GetFocusedHeroPosition_maybe
//   [x] 0x4eda80  CKS08GameManager_vf144
//   [ ] 0x4edab8  CKS08GameManager_GetFocusedHeroNode_maybe
//   [x] 0x4edaf8  IKCommonGameManager_PostLoad
//   [ ] 0x4edc78  CKS08GameManager_IsNoRestartPending_maybe
//   [ ] 0x4edcc8  IKCommonGameManager_vfC0
//   [x] 0x4edce8  CKS08GameManager_SetPlayerActive_maybe
//   [x] 0x4edd20  CKS08GameManager_GetHeroesInvulnerableMask_maybe
//   [x] 0x4edde8  CKS08GameManager_IsPlayerActive_maybe
//   [x] 0x4ede20  CKS08GameManager_SetHeroesInvulnerableFromMask_maybe
//   [x] 0x4edee0  CKS08GameManager_ConstructBase_maybe
//   [x] 0x4ee100  CKS08GameManager_InterfaceStateDispatch
//   [x] 0x4ee1a8  CKS08GameManager_HandleControllerDisconnect_maybe
//   [x] 0x4ee310  CKS08GameManager_IsVideoSkipPressed_maybe
//   [ ] 0x4ee4d0  CKS08GameManager_IsAnyMenuButtonActive_maybe
//   [x] 0x4ee668  CKS08GameManager_vf2F0
//   [x] 0x4ee710  CKS08GameManager_OnLevelStart_maybe
//   [ ] 0x4ee770  SetHeroInteractionTarget
//   [ ] 0x4ee988  CKS08GameManager_vf140
//   [x] 0x4eea60  CKS08GameManager_GetFocusedHeroNodePosition_maybe
//   [x] 0x4eeab8  CKS08GameManager_SectorUnload
//   [x] 0x4eebe8  IKCommonGameManager_vf240
//   [x] 0x4eed08  CKS08GameManager_ResetProgress_maybe
//   [ ] 0x4eed90  IKCommonGameManager_ResolveTriggerProperty
//   [x] 0x4eee20  CKS08GameManager_HandleCinematicAndUIMessage_maybe
//   [ ] 0x4ef6a8  CKS08GameManager_vfA8
//   [x] 0x4ef738  CKS08GameManager_Init
//   [x] 0x4efb48  CKS08GameManager_vf2E8
//   [ ] 0x4efbe8  IKCommonGameManager_Construct
//   [ ] 0x4efe08  IKCommonGameManager_DeletingDestructor
//   [ ] 0x4eff30  CKS08GameManager_SwitchInterfaceStateToStackTop_maybe
//   [x] 0x4f0110  IKCommonGameManager_Load
//   [ ] 0x4f0db8  IKCommonGameManager_Destructor
//   [ ] 0x4f0ed8  IKCommonGameManager_DestructBody
//   [x] 0x4f0ff8  IKGameManager_ResetRuntimeImpl
//   [ ] 0x4f1a38  CKS08GameManager_vf210
//   [x] 0x4f1d90  IKCommonGameManager_vfAC
//   [x] 0x4f1f88  CKS08GameManager_CheckPauseOrSkipRequest_maybe
//   [x] 0x4f22e8  CKS08GameManager_Stop
//   [ ] 0x4f27b0  IKGameManager_ReinitRuntimeImpl
//   [x] 0x4f2dd0  IKGameManager_Update
//   [x] 0x4f46f8  KStub_Return0_4f46f8
//   [x] 0x4f4700  KStub_Return4_4f4700
//
//   [ ] 0x9c6810  IKCommonGameManager_IsKindOf  [inline]
//   [ ] 0x9c6848  IKCommonGameManager_GetClassGroup  [inline]
//   [ ] 0x9c6850  IKCommonGameManager_GetClassId  [inline]
//   [ ] 0x9c6858  IKCommonGameManager_vf254  [inline]
//   [ ] 0x9c6860  IKCommonGameManager_vf258  [inline]
//   [ ] 0x9c6870  IKCommonGameManager_vf150  [inline]
//   [ ] 0x9c6878  IKCommonGameManager_vf154  [inline]
//   [ ] 0x9c6888  IKCommonGameManager_vf1B0  [inline]
//   [ ] 0x9c68d0  IKCommonGameManager_vf1B8  [inline]
//   [ ] 0x9c6930  IKCommonGameManager_vf26C  [inline]
//   [ ] 0x9c6970  IKCommonGameManager_vf28C  [inline]
//   [ ] 0x9c6978  IKCommonGameManager_vf290  [inline]
//   [ ] 0x9c6980  IKCommonGameManager_vf298  [inline]
//   [ ] 0x9c6988  IKCommonGameManager_vf29C  [inline]
//   [ ] 0x9c6a10  IKCommonGameManager_vf304  [inline]
//   [ ] 0x9c6ad8  IKCommonGameManager_vf31C  [inline]
//   [ ] 0x9c6af0  IKCommonGameManager_vf320  [inline]
//   [ ] 0x9c6b00  IKCommonGameManager_vf328  [inline]
//   [ ] 0x9c6b18  IKCommonGameManager_vf338  [inline]
//   [ ] 0x9c6b20  IKCommonGameManager_vf33C  [inline]
//   [ ] 0x9c6b28  IKCommonGameManager_vf340  [inline]
//   [ ] 0x9c6b30  IKCommonGameManager_vf344  [inline]
//   [ ] 0x9c6b38  IKCommonGameManager_vf348  [inline]
//   [ ] 0x9c6b40  IKCommonGameManager_vf34C  [inline]
//   [ ] 0x9c6b48  IKCommonGameManager_vf350  [inline]
//   [ ] 0x9c6b50  IKCommonGameManager_vf354  [inline]
//   [ ] 0x9c6b58  IKCommonGameManager_vf358  [inline]
//   [ ] 0x9c6b60  IKCommonGameManager_vf35C  [inline]
//   [ ] 0x9c6ba0  IKCommonGameManager_vf25C  [inline]
#include "Spyro2008/logic/CKS08GameManager.h"

#include <cstdlib>
#include <cstring>

#include "Spyro2008/groups/CKGrpS08Hero.h"
#include "Spyro2008/groups/IKGrpHero.h"
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "Spyro2008/hooks/IKHkHero.h"
#include "Spyro2008/logic/CKMenuBase114c.h"
#include "Renderware/rwcore/RwCamera.h"
#include "Renderware/rwcore/RwMatrix.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/cameras/CKSrvCamera.h"
#include "k2000/components/CKLocTextAccessor.h"
#include "k2000/core/Stub.h"
#include "k2000/graphical/ui/CText2d.h"
#include "k2000/managers/CKSoundManager.h"
#include "k2000/sound/CKListener.h"
#include "k2000/sound/SoundVoiceManager.h"
#include "k2000/graphical/system/IKVideo.h"
#include "k2000/graphical/system/CKVideoSegment.h"
#include "k2000/graphical/system/CVideoManager.h"
#include "k2000/graphical/system/PS3_CKVideo.h"
#include "k2000/graphical/fx/CColorizedScreenFx.h"
#include "k2000/graphical/ui/CKFlashManager.h"
#include "k2000/graphical/ui/CKFlashUI.h"
#include "k2000/input/CKInputDico.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKGameLevel.h"
#include "k2000/logic/CKGameSpawnPoint.h"
#include "k2000/logic/CKGameState.h"
#include "k2000/logic/IKPlayer.h"
#include "k2000/managers/CKInput.h"
#include "k2000/memory/Mem.h"
#include "k2000/logic/ui/CKLocText.h"
#include "k2000/logic/ui/CLocManager.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/misc/CKGameLoop.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/FloatApproach.h"
#include "k2000/logic/CKCinematicScene.h"
#include "k2000/services/CKSrvCinematic.h"
#include "k2000/misc/IKGameStructure.h"
#include "k2000/system/CTimeManager.h"
#include "k2000/system/IKTime.h"
#include "k2000/ui/IKNode2d.h"

void KStub_Nop_106c0(int32_t id, const void* handler);  // 0x000106c0 (the four Init registrations)
void KStub_Nop_106b8(int32_t id, const void* handler);  // 0x000106b8

// ---- the state machines (inlined by the PS3 code at every use) ----
void CKS08GameManager::StateMachine::Switch(uint8_t next) {
    uint8_t previous = m_ui8Current;
    if (previous != 0xff) {
        Call(previous, 2, next);
        previous = m_ui8Current;
    }
    m_ui8Current = next;
    if (next != 0xff) Call(next, 1, previous);
}

uint8_t CKS08GameManager::StateMachine::Tick() {
    uint8_t current = m_ui8Current;
    if (current == 0xff) return 0xff;
    const uint8_t next = Call(current, 0, current);
    current = m_ui8Current;
    if (next == current) return current;
    if (current != 0xff) {
        Call(current, 2, next);
        current = m_ui8Current;
    }
    m_ui8Current = next;
    if (next == 0xff) return next;
    Call(next, 1, current);
    return m_ui8Current;
}

// 0x004ef738 CKS08GameManager_Init: InitImpl, then the game state machine (StateCount entries: the
// IKCommonGameManager handlers, then vt+0x328's) and the interface state machine (one per menu slot:
// InterfaceStateDispatch, the none slot (vt+0x338) InterfaceNone).
void CKS08GameManager::Init() {
    InitImpl();
    m_unk328 = 0xffff;
    Vf334();
    m_flags64 &= ~0x80u;
    m_unk2FC = 1;
    m_unk2B8 = (m_unk2B8 & 0x00ffffffu) | 0x01000000u;  // the byte at +0x2b8 (big-endian word)
    StateHandler* table = static_cast<StateHandler*>(Mem_CallocAligned16(StateCount(), static_cast<uint32_t>(sizeof(StateHandler))));
    // The TOC1 +0x7018..+0x7044 handlers, in the original's store order.
    table[1] = &CKS08GameManager::State1;
    table[2] = &CKS08GameManager::State2Common;
    table[4] = &CKS08GameManager::StateReturn4;
    table[3] = &CKS08GameManager::State3;
    table[5] = &CKS08GameManager::State5Common;
    table[6] = &CKS08GameManager::State6Common;
    table[7] = &CKS08GameManager::StateInGameCommon;
    table[8] = &CKS08GameManager::StateMenuCommon;
    table[0] = &CKS08GameManager::StateReturn0;
    table[9] = &CKS08GameManager::StateHeroDeathCommon;
    table[10] = &CKS08GameManager::StateReturn10;
    table[11] = &CKS08GameManager::StateReturn11;
    InitStateHandlerTable(table);
    const uint32_t count = StateCount();
    m_gameState.m_pOwner = this;
    m_gameState.m_pTable = static_cast<StateHandler*>(Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(StateHandler))));
    for (uint32_t i = 0; i < count; ++i) m_gameState.m_pTable[i] = table[i];  // memcpy of the PS3 pairs
    m_gameState.m_ui8Count = static_cast<uint8_t>(count);
    Mem_FreeAligned16(table);
    const uint8_t menus = MenuStateCount();
    StateHandler* interfaceTable =
        static_cast<StateHandler*>(Mem_CallocAligned16(menus, static_cast<uint32_t>(sizeof(StateHandler))));
    for (uint32_t i = menus; i != 0;) {
        --i;
        interfaceTable[i] = (NoMenuId() == i) ? &CKS08GameManager::InterfaceNone : &CKS08GameManager::InterfaceStateDispatch;
    }
    const uint32_t interfaceCount = MenuStateCount();
    m_interfaceState.m_pOwner = this;
    m_interfaceState.m_pTable =
        static_cast<StateHandler*>(Mem_AllocAligned16(interfaceCount * static_cast<uint32_t>(sizeof(StateHandler))));
    for (uint32_t i = 0; i < interfaceCount; ++i) m_interfaceState.m_pTable[i] = interfaceTable[i];
    m_interfaceState.m_ui8Count = static_cast<uint8_t>(interfaceCount);
    Mem_FreeAligned16(interfaceTable);
    m_unk324 = 0;
    // Four registrations with empty bodies on the PS3 (TOC1 +0x7050..+0x705c: strings).
    KStub_Nop_106c0(0x14, nullptr);
    KStub_Nop_106c0(0x16, nullptr);
    KStub_Nop_106c0(0x17, nullptr);
    KStub_Nop_106b8(0x13, nullptr);
}
#include "k2000/io/IKFile.h"
#include "k2000/io/SaveData.h"
#include "k2000/logic/GameVector.h"
#include "k2000/memory/Mem.h"

// 0x004f0110 IKCommonGameManager_Load
void CKS08GameManager::LoadCommon(IKFile* stream, int32_t mode) {
    LoadImpl(stream, mode);
    if (mode == 1) {
        // Words (a block of exactly count, one when 0).
        uint32_t count = 0;
        ReadU32LE(stream, &count);
        if (count == 0) {
            m_unk2BC.m_ui32NbElt = 1;
            m_unk2BC.m_pBlock = static_cast<uint32_t*>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(uint32_t))));
        } else {
            m_unk2BC.m_ui32NbElt = count;
            m_unk2BC.m_pBlock = static_cast<uint32_t*>(Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(uint32_t))));
        }
        if (m_unk2BC.m_ui32NbElt < count) {  // as in the original: cannot happen here
            uint32_t capacity = (count / 10) * 10 + 10;
            if (capacity == 0) capacity = 10;
            m_unk2BC.m_pBlock = static_cast<uint32_t*>(
                Mem_ReallocAligned16(m_unk2BC.m_pBlock, capacity * static_cast<uint32_t>(sizeof(uint32_t))));
            m_unk2BC.m_ui32NbElt = capacity;
        }
        m_unk2BC.m_ui32NbUsedElt = count;
        ReadU32LEWords(stream, m_unk2BC.m_pBlock, count);
        IKFile_ReadRef(stream, &m_unk2CC);
        // A block sized for count references (the logo videos); each reference is read into a local (cleared
        // first: stw r23, 0x78(r1)), which the KP3 resolver fills at once, then appended (lwz 0x78(r1)).
        ReadU32LE(stream, &count);
        GameVector_Allocate(&m_unk2D0, count);
        while (count-- != 0) {
            IKSerializable* reference = nullptr;
            IKFile_ReadRef(stream, &reference);
            GameVector_Add(&m_unk2D0, reference);
        }
        IKFile_ReadRef(stream, &m_unk2E0);
        IKFile_ReadRef(stream, &m_unk2E4);
        ReadU32LE(stream, &count);
        if (count != 0) {
            m_unk474.m_ui32NbElt = count;
            m_unk474.m_pBlock = static_cast<IKSerializable**>(Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(IKSerializable*))));
            GameVector_Resize(&m_unk474, count);
            IKFile_ReadObjectRefArray(stream, m_unk474.m_pBlock, count);
        }
        ReadU32LEWords(stream, GetCounterTextVarTable(), Vf350());
        IKFile_ReadRef(stream, &m_unk460);
        ReadRaw(stream, m_unk498, 9);
        ReadU8(stream, &m_unk4A1);
        ReadU8(stream, &m_unk4A2);
        SaveData_LoadIconBlobs(stream, 1);
        return;
    }
    if (mode != 0) return;
    for (uint32_t i = 0; i < Vf340(); ++i) IKFile_ReadRef(stream, &Vf344()[i]);
    for (uint32_t i = 0; i < Vf348(); ++i) IKFile_ReadRef(stream, &GetHudInterfaces()[i]);
    IKFile_ReadRef(stream, &m_unk490);
    IKFile_ReadObjectRefArray(stream, m_unk2A8, 2);
    IKFile_ReadObjectRefArray(stream, m_unk2B0, 2);
    IKFile_ReadRef(stream, &m_unk4BC);
    IKFile_ReadRef(stream, &m_unk4C0);
    m_unk4A4.Load(stream, 0);
    m_unk4AC.Load(stream, 0);
    m_unk4B4.Load(stream, 0);
    IKFile_ReadRef(stream, &m_unk4C4);
    IKFile_ReadRef(stream, &m_unk4D8);
    SaveData_LoadIconBlobs(stream, 0);
    IKFile_ReadRef(stream, &m_unk4E0);
}

IKVideo* CKS08GameManager::GetInterfaceVideo() { return static_cast<IKVideo*>(m_unk460); }
IKVideo* CKS08GameManager::GetDemoVideo() { return static_cast<IKVideo*>(m_unk2E0); }

// 0x009c6b68 CKS08GameManager_vf310: flags +0x64 bit 12 + (player != 0).
uint8_t CKS08GameManager::Vf310(int32_t player) {
    return static_cast<uint8_t>((m_flags64 >> (12 + (player != 0 ? 1 : 0))) & 1);
}

// 0x009c6aa0 CKS08GameManager_vf314
void CKS08GameManager::Vf314(int32_t player, uint8_t value) {
    const uint32_t bit = 12 + (player != 0 ? 1u : 0u);
    m_flags64 = (m_flags64 & ~(1u << bit)) | (static_cast<uint32_t>(value) << bit);
}

// 0x004ed080 CKS08GameManager_ResetFadeVideoIfMode2ThenVf338_maybe: the "no menu" interface state; on leave,
// the interface video's fade reset to opaque.
uint8_t CKS08GameManager::InterfaceNone(int32_t phase, uint8_t /*other*/) {
    if (phase == 2 && m_unk460 != nullptr) {
        IKVideo* video = GetInterfaceVideo();
        m_unk468[0] = 255.0f;  // 0x437f0000
        m_unk468[1] = 0.0f;
        m_unk468[2] = 255.0f;
        video->SetFadeLevel(0xff);
        video->m_baData &= ~0x10u;
        video->m_baFrameFlags &= ~0x80u;
    }
    return NoMenuId();
}

// 0x004ed198 CKS08GameManager_IsTrackedLevelCurrent_maybe: +0x2cc (the front-end level) is the game
// structure's current level.
uint8_t CKS08GameManager::IsFrontEndLevel() {
    CKGameLevel* current = static_cast<IKGameStructure*>(m_gameStructure)->GetCurrentLevel();
    if (m_unk2CC == nullptr) return 0;
    return static_cast<IKSerializable*>(current) == m_unk2CC ? 1 : 0;
}

// 0x004ed440 CKS08GameManager_Resume: the base's (0x134e8, empty), then every HUD screen's vt+0x58.
void CKS08GameManager::Resume() {
    for (uint32_t i = Vf348(); i != 0; --i) {
        IKSerializable* hud = GetHudInterfaces()[i - 1];
        if (hud == nullptr) continue;
        static_cast<CKMenuBase114c*>(hud)->Resume();
    }
}

// 0x004ed540 CKS08GameManager_Pause: the base's (0x134e0, empty), then every HUD screen hidden (vt+0xb0)
// and paused (vt+0x54).
void CKS08GameManager::Pause() {
    for (uint32_t i = Vf348(); i != 0; --i) {
        IKSerializable* hud = GetHudInterfaces()[i - 1];
        if (hud == nullptr) continue;
        static_cast<CKMenuBase114c*>(hud)->SetVisible(0);
        static_cast<CKMenuBase114c*>(hud)->Pause(0);
    }
}

// 0x004ec9b8 CKS08GameManager_PickRandomTipText_maybe: the loading screen's tip (a title and a text of the
// localization manager's first 40 texts, pairs 2i / 2i+1 where the second exists), random among the tips not
// shown yet (all shown: the flags start again). Cleared and left empty for the front-end level (+0x2cc).
void CKS08GameManager::PickRandomTipText() {
    std::memset(m_unk6E4, 0, sizeof(m_unk6E4));
    std::memset(m_unk4E4, 0, sizeof(m_unk4E4));
    if (m_unk2CC == static_cast<IKGameStructure*>(m_gameStructure)->FindLevelById(m_requestedLevel)) return;
    CLocManager* texts = static_cast<CLocManager*>(m_unk4E0);  // +0x04 the text block, +0x10 the default text
    // The text `index`: the block's entry, else the default text (CLocManager::GetText-like, unchecked).
    auto textAt = [texts](uint32_t index) -> CKLocText* {
        return texts->m_vpTexts.m_pBlock != nullptr ? texts->m_vpTexts.m_pBlock[index] : reinterpret_cast<CKLocText*>(texts->m_pDefaultTrcText);
    };
    if (m_unkAE4 == nullptr) {
        uint8_t count = 0;
        m_unkAE8 = 0;
        for (uint32_t pair = 0; pair < 20; ++pair) {
            if (textAt(pair * 2 + 1) != nullptr) m_unkAE8 = ++count;
        }
        if (count == 0) return;
        m_unkAE4 = static_cast<uint8_t*>(std::malloc(count));
        std::memset(m_unkAE4, 0, m_unkAE8);
    }
    uint32_t unused = 0;
    for (uint32_t i = 0; i < m_unkAE8; ++i) unused += m_unkAE4[i] == 0 ? 1 : 0;
    if (unused == 0) {
        std::memset(m_unkAE4, 0, m_unkAE8);
        unused = m_unkAE8;
    }
    // BUG(original): the flags are indexed by the pair number, so a null pair before the last one runs past
    // the count-sized block.
    uint32_t wanted = static_cast<uint32_t>(Rand_Int()) % unused + 1;
    uint32_t pair = 0;
    for (;; ++pair) {
        if (m_unkAE4[pair] == 0 && --wanted == 0) break;
    }
    m_unkAE4[pair] = 1;
    if (textAt(pair * 2) != nullptr) LocString_CopyText(textAt(pair * 2), reinterpret_cast<uint16_t*>(m_unk4E4));
    if (textAt(pair * 2 + 1) != nullptr) LocString_CopyText(textAt(pair * 2 + 1), reinterpret_cast<uint16_t*>(m_unk6E4));
}

// 0x004f22e8 CKS08GameManager_Stop (leaving a level or the front end, GameLoop mode 9): the base's, then the
// game state 0, every menu closed (vt+0xa8), no menu, every HUD screen closed, the pause fade hidden and the
// next loading tip picked.
void CKS08GameManager::Stop() {
    CDefaultGameManager::Stop();  // 0x13e08
    m_unk324 = 0;
    m_gameState.Switch(0);
    for (uint32_t i = Vf340(); i != 0; --i) {
        IKSerializable* menu = Vf344()[i - 1];
        if (menu != nullptr) static_cast<CKMenuBase114c*>(menu)->VfA8();  // KBase730C_ClearSlotsAndClose_maybe
    }
    const uint8_t none = NoMenuId();
    m_ui8PrevMenu = MenuStateCount();
    m_interfaceState.Switch(none);
    m_aMenuStack[0] = none;
    m_ui32MenuStackDepth = 1;
    for (uint32_t i = Vf348(); i != 0; --i) {
        IKSerializable* hud = GetHudInterfaces()[i - 1];
        if (hud != nullptr) static_cast<CKMenuBase114c*>(hud)->VfA8();
    }
    static_cast<CColorizedScreenFx*>(m_unk490)->m_BitProperties &= ~CColorizedScreenFx::kActive;
    PickRandomTipText();
}

// 0x004eeab8 CKS08GameManager_SectorUnload: CDefaultGameManager_SectorUnload (0x134f8, a bare return), then
// every HUD screen (last to first) with a flash interface (+0x0c) of that sector (its +0x22c, -1 without the
// interface) closed.
void CKS08GameManager::SectorUnload(int32_t sector) {
    for (uint32_t i = Vf348(); i != 0; --i) {
        CKMenuBase114c* hud = static_cast<CKMenuBase114c*>(GetHudInterfaces()[i - 1]);
        if (hud == nullptr) continue;
        int32_t hudSector = -1;
        if (hud->m_pFlashUI != nullptr) hudSector = static_cast<int32_t>(static_cast<CKFlashUI*>(hud->m_pFlashUI)->m_ui32Unk22c);
        if (hudSector == sector) hud->VfA8();  // KBase730C_ClearSlotsAndClose_maybe
    }
}

// 0x004ed310 CKS08GameManager_SectorLoaded
void CKS08GameManager::SectorLoaded(int32_t sector) {
    for (uint32_t i = Vf348(); i != 0; --i) {
        CKMenuBase114c* hud = static_cast<CKMenuBase114c*>(GetHudInterfaces()[i - 1]);
        if (hud == nullptr) continue;
        int32_t hudSector = -1;
        if (hud->m_pFlashUI != nullptr) hudSector = static_cast<int32_t>(static_cast<CKFlashUI*>(hud->m_pFlashUI)->m_ui32Unk22c);
        if (hudSector == sector) hud->Reset();  // vt+0x9c KBase730C_vf9C
    }
}

// 0x004eea60 CKS08GameManager_GetFocusedHeroNodePosition_maybe. The focused node is CKGrpS08Hero_GetFocusedHeroNode_maybe
// (0x2ca128): the group's +0x44 list at the focused index (a signed byte at +0x66, -1 = none, then null).
// BUG(original): no test of the node; its frame is read at +4.
// The focus index is set by the hero group's PostLoad (SetFocusedDragon 0x2cc3f0, CKGrpS08Hero_3.cpp); before that it
// is -1, which the original would not survive (null node). The zero vector stands in, so CKLevel_Update finds no
// sector at the point and requests none.
const float* CKS08GameManager::GetFocusedHeroNodePosition() {
    IKGrpHero* group = static_cast<IKGrpHero*>(m_unk04[1]);
    if (group == nullptr) return CDefaultGameManager::GetFocusedHeroNodePosition();
    const int8_t index = static_cast<int8_t>(group->m_unk66);
    if (index == -1) {
        DOTD_STUB_ONCE("CKS08GameManager_GetFocusedHeroNodePosition_maybe: no focused hero yet (before the hero group's PostLoad)");
        return CDefaultGameManager::GetFocusedHeroNodePosition();
    }
    CSGMovable* node = static_cast<CSGMovable*>(group->m_apUnk44[index]);
    // The LTM is computed on demand (the PS3 reads the frame's stored LTM, synchronised by
    // CKGraphic_UpdateSceneWorldMatrices_maybe right before).
    return &RwFrameGetLTM(node->m_pRwFrame)->pos.x;
}

// 0x004eda18 CKS08GameManager_GetFocusedHeroPosition_maybe (step 5, FX: the camera's heading lock). The focused hero
// is CKGrpS08Hero_GetFocusedHero 0x2ca0f8 (+0x66, -1 none).
const float* CKS08GameManager::GetFocusedHeroPosition() {
    IKGrpHero* group = static_cast<IKGrpHero*>(m_unk04[1]);
    if (group != nullptr && static_cast<int8_t>(group->m_unk66) != -1) {
        IKHkHero* hero = static_cast<IKHkHero*>(group->m_apHeros[static_cast<int8_t>(group->m_unk66)]);
        if (hero != nullptr) {
            // 0x00363c78 IKHkHero_GetTargetingPositionPtr_maybe
            if ((hero->m_bitArray & 2u) == 0) return &hero->m_unk570;
            return &static_cast<CSGMovable*>(hero->m_pKGLObject)->m_pRwFrame->ltm.pos.x;
        }
    }
    return CDefaultGameManager::GetFocusedHeroNodePosition();
}

// 0x004ed930 CKS08GameManager_GetFocusedHeroMoveVector_maybe (step 5, FX)
const float* CKS08GameManager::GetFocusedHeroMoveVector() {
    IKGrpHero* group = static_cast<IKGrpHero*>(m_unk04[1]);
    if (group != nullptr && static_cast<int8_t>(group->m_unk66) != -1) {
        CKHkS08Hero* hero = static_cast<CKHkS08Hero*>(group->m_apHeros[static_cast<int8_t>(group->m_unk66)]);
        if (hero != nullptr) {
            // 0x00362dd0 CKHkS08Hero_GetPlayerInputByte394: the player's input byte (+0x394) of the leading hero, its input
            // read again first with +0x358 bit 3; 0 for the other hero.
            uint8_t input = 0;
            if (hero->m_ui8Hero == hero->m_ui8TrackedLeader) {
                if ((hero->m_unk358 & 8u) != 0) hero->ReadHeroPlayerInput();  // 0x00369670
                input = hero->m_unk394;
            }
            if (input != 0) return &hero->m_unk3b8;  // 0x00361a60 IKHkHero_GetVec3Ptr3B8_maybe
        }
    }
    return CDefaultGameManager::GetFocusedHeroNodePosition();
}

// 0x004ed8f0 CKS08GameManager_GetControlledHeroCount: 1 without the hero group (+0x08), else the group's
// count (0x2ca288 GetControlledHeroCount: the byte at +0x50, the high byte of the word here).
uint8_t CKS08GameManager::GetControlledHeroCount() {
    if (m_unk04[1] == nullptr) return 1;
    return static_cast<IKGrpHero*>(m_unk04[1])->m_ui8ControlledHeroCount;
}

// 0x004ed8b8 CKS08GameManager_SetInputBlocked_maybe (vt+0x1e8) / 0x004ed878 IsInputBlocked_maybe (vt+0x1ec): the hero
// group's input-blocked bit (0x2ca268 / 0x2ca258: bit 3 of +0xf8); nothing / 0 without the group.
void CKS08GameManager::SetInputBlocked(uint8_t blocked) {
    CKGrpS08Hero* group = static_cast<CKGrpS08Hero*>(m_unk04[1]);
    if (group != nullptr) group->m_unkf8 = (group->m_unkf8 & 0xfffffff7u) | (static_cast<uint32_t>(blocked) << 3);
}
uint8_t CKS08GameManager::IsInputBlocked() {
    CKGrpS08Hero* group = static_cast<CKGrpS08Hero*>(m_unk04[1]);
    if (group == nullptr) return 0;
    return static_cast<uint8_t>((group->m_unkf8 >> 3) & 1);
}

// 0x004edd20 CKS08GameManager_GetHeroesInvulnerableMask_maybe (vt+0x1f0): bit i = hero i's invulnerable bit
// (IKHkHero_IsInvulnerable_maybe 0x361b10: +0x35c bit 2). The hero count is the group's (vt+0xf4, 2).
void CKS08GameManager::GetHeroesInvulnerableMask(uint32_t* mask) {
    *mask = 0;
    CKGrpS08Hero* group = static_cast<CKGrpS08Hero*>(m_unk04[1]);
    if (group == nullptr) return;
    const uint32_t count = group->GetHeroCount();
    for (uint32_t i = 0; i != count; ++i) {
        IKHkHero* hero = static_cast<IKHkHero*>(group->m_apHeros[i]);  // 0x2ca080 GetHeroByDragonIndex
        const uint32_t invulnerable = (hero->m_unk35c >> 2) & 1;
        *mask = (*mask & ~(1u << (i & 0x3f))) | (invulnerable << (i & 0x3f));
    }
}

// 0x004ede20 CKS08GameManager_SetHeroesInvulnerableFromMask_maybe (vt+0x1f4)
void CKS08GameManager::SetHeroesInvulnerableFromMask(const uint32_t* mask) {
    CKGrpS08Hero* group = static_cast<CKGrpS08Hero*>(m_unk04[1]);
    if (group == nullptr) return;
    const uint32_t count = group->GetHeroCount();
    for (uint32_t i = 0; i != count; ++i) {
        IKHkHero* hero = static_cast<IKHkHero*>(group->m_apHeros[i]);
        const uint32_t bit = ((1u << (i & 0x3f)) & *mask) != 0 ? 1u : 0u;
        hero->m_unk35c = (hero->m_unk35c & 0xfffffffbu) | (bit << 2);  // IKHkHero_SetInvulnerable_maybe 0x361b20
    }
}

// 0x004ed7d8 CKS08GameManager_SetAllHeroesInvulnerable_maybe (vt+0x1f8)
void CKS08GameManager::SetAllHeroesInvulnerable(uint8_t invulnerable) {
    CKGrpS08Hero* group = static_cast<CKGrpS08Hero*>(m_unk04[1]);
    if (group == nullptr) return;
    const uint32_t count = group->GetHeroCount();
    for (uint32_t i = 0; i != count; ++i) {
        IKHkHero* hero = static_cast<IKHkHero*>(group->m_apHeros[i]);
        hero->m_unk35c = (hero->m_unk35c & 0xfffffffbu) | (static_cast<uint32_t>(invulnerable) << 2);
    }
}

// 0x004eee20 CKS08GameManager_HandleCinematicAndUIMessage_maybe. 0x500 (a cinematic scene started): with bands (the scene's band
// bit 0) the HUD interfaces are hidden, last to first. 0x2501 (a video started): the same when it is not a
// video-to-texture (flag 0x40) and the game state is 7. 0x2502 (a video stopped): the game video of that video is
// marked seen in every level. STUB(C2.8, moved from C2.6: level scripts send them; the text display is C2.7 HUD): the
// text and message ids 0x2667 and 0x2669..0x2679 are not ported (the original answers 0 for an unknown id, as here).
uint8_t CKS08GameManager::HandleUIMessage(uint16_t message, void* data) {
    auto hideHud = [this]() {
        for (uint32_t i = Vf348(); i != 0;) {
            --i;
            CKMenuBase114c* menu = static_cast<CKMenuBase114c*>(GetHudInterfaces()[i]);
            if (menu != nullptr) menu->SetVisible(0);  // vt+0xb0
        }
    };
    if (message == 0x500) {
        const CKCinematicScene* scene = static_cast<const CKCinematicScene*>(data);
        if ((scene->m_baBlackBandData & 1) != 0) hideHud();
        return 0;
    }
    if (message == 0x2501) {
        const IKVideo* video = static_cast<const IKVideo*>(data);
        if ((video->m_baData & 0x40u) == 0 && m_gameState.m_ui8Current == 7) hideHud();
        return 0;
    }
    if (message == 0x2502) {
        const IKVideo* video = static_cast<const IKVideo*>(data);
        if ((video->m_baData & 0x40u) != 0) return 0;
        static_cast<IKGameStructure*>(m_gameStructure)->SetModuleFlag2InAllLevels(video);
        return 0;
    }
    if (message == 0x2d00) {
        // The answer (data) of the message box MessageBox_Show asked: the skip prompt (+0x4d0 == 2) puts the sound volume
        // back to muted for the scene and gives the game loop back; "yes" (5) asks the cinematic service for the skip (bit 3).
        if (m_unk4D0 == 2) {
            g_pEngine->m_soundManager->SaveAndMuteVolume(1);
            --g_pEngine->m_gameLoop->m_inhibitCount;  // CKGameLoop_DecPauseCount_maybe
            if (reinterpret_cast<intptr_t>(data) == 5) {
                CKSrvCinematic* service = static_cast<CKSrvCinematic*>(g_pEngine->m_srvCinematic);
                service->m_baData = static_cast<uint8_t>((service->m_baData & 0xf7) | 8);
            }
        }
        m_unk4D0 = 0;
        return 1;
    }
    if (message == 0x2667 || (message >= 0x2669 && message <= 0x2679))
        DOTD_STUB_ONCE("CKS08GameManager_HandleCinematicAndUIMessage_maybe: the HUD text messages (C2.7 / C2.8, moved from C2.6)");
    return 0;
}

// 0x004ec968 CKS08GameManager_SetActiveCameraIndex_maybe (vt+0x294). BUG(original): the list head is read
// before the index is checked against the count.
void CKS08GameManager::SetActiveCameraIndex(uint32_t index) {
    CKSrvCamera* camera = static_cast<CKSrvCamera*>(g_pEngine->m_srvCamera);
    if (camera->m_unk24[0] == index) return;
    if (*camera->m_aCameraSectorMode[index] == nullptr) return;
    if (camera->m_ui32NbCameraSectorMode <= index) return;
    camera->m_unk24[0] = index;
}

// 0x004ed790 IKCommonGameManager_Destroy (the level unload)
void CKS08GameManager::DestroyCommon() {
    ClearReferencesImpl();  // 0x156d8
    // BUG(original): freed, the pointer kept (the next level's PostLoad allocates a new array).
    if (m_unk2C8 != nullptr) ::operator delete[](m_unk2C8);
}

// 0x004edaf8 IKCommonGameManager_PostLoad
int32_t CKS08GameManager::PostLoadCommon(int32_t type) {
    PostLoadImpl(type);
    if (type == 0) {
        m_unk2C8 = ::operator new[](static_cast<size_t>(GetMaxPlayers()) * sizeof(PlayerHudSlot));  // OperatorNewArray(count << 3)
        Vf334();
        // TriggerEventList_PostLoad_maybe (0x236330, returns 1) on +0x4a4, +0x4a4 again and +0x4b4.
        m_unk464 = nullptr;
        return 1;
    }
    if (type != 1) {
        m_unk464 = nullptr;
        return 1;
    }
    g_pEngine->m_input->SelectMappingSet(0);
    m_unk464 = nullptr;
    return 1;
}

// 0x004edce8 CKS08GameManager_SetPlayerActive_maybe: flags +0x64 bit 14 + (player != 0).
void CKS08GameManager::SetPlayerActive(int32_t player, uint8_t active) {
    const uint32_t bit = 14 + (player != 0 ? 1u : 0u);
    m_flags64 = (m_flags64 & ~(1u << bit)) | (static_cast<uint32_t>(active) << bit);
}

// 0x004edde8 CKS08GameManager_IsPlayerActive_maybe
uint8_t CKS08GameManager::IsPlayerActive(int32_t player) {
    return static_cast<uint8_t>((m_flags64 >> (14 + (player != 0 ? 1 : 0))) & 1);
}

// 0x004ee100 CKS08GameManager_InterfaceStateDispatch: the current menu's (vt+0x344, the menu table)
// HandleStatePhase.
uint8_t CKS08GameManager::InterfaceStateDispatch(int32_t phase, uint8_t other) {
    IKSerializable* menu = Vf344()[m_interfaceState.m_ui8Current];
    return static_cast<CKMenuBase114c*>(menu)->HandleStatePhase(phase, other);
}

// 0x004eebe8 IKCommonGameManager_vf240 (CKS08GameManager_vf240 0x4f7158 calls it): the menu a finished
// load-game flow shows.
void CKS08GameManager::Vf240Common(int32_t result) {
    if (result == 1) {
        m_aMenuStack[0] = MainMenuId();  // vt+0x2f8
        m_ui32MenuStackDepth = 1;
        return;
    }
    if (result != 0) return;
    // The game structure's vt+0x60 (0x40cd0) with player 0: the player's game state applied to it.
    static_cast<IKGameStructure*>(m_gameStructure)->ApplyPlayerGameState(static_cast<IKPlayer*>(m_players[0]));
    m_aMenuStack[0] = Vf2FC();
    m_ui32MenuStackDepth = 1;
}

// 0x004efb48 CKS08GameManager_vf2E8
uint8_t CKS08GameManager::RequestSpawnPointLevel() {
    IKGameStructure* structure = static_cast<IKGameStructure*>(m_gameStructure);
    CKGameSpawnPoint* spawnPoint = structure->m_pCurrentSpawnPoint;
    structure->SetCurrentSpawnPoint(spawnPoint);  // vt+0x6c
    return RequestLevelChange(spawnPoint->m_pGameStage->m_i32StageIndex, spawnPoint->m_iSectorIndex);  // vt+0x2e4
}

// 0x004ee1a8 CKS08GameManager_HandleControllerDisconnect_maybe. STUB(C1.6): the system message (port 0:
// the "TRC_WIIMOTE_SLOT" text variables and job 500; other ports: the reconnect message box).
void CKS08GameManager::HandleControllerDisconnect(uint8_t /*port*/) {
    DOTD_STUB_ONCE("CKS08GameManager_HandleControllerDisconnect_maybe (C1.6)");
}

// 0x00110330 SoundListener_SetFollowCamera_maybe(listener, 1) and 0x00110308 SetOrientationFollowCamera_maybe(
// listener, 1): the listener's position and orientation sources are the camera (0).
static void FollowCamera(CKListener* listener) {
    listener->m_unk38 = 0;
    listener->m_unk3c = 0;
}

// 0x004f0ff8 IKGameManager_ResetRuntimeImpl: the players, the "IKCommonGameManager" input project, the
// Flash input, the menus reset, no menu, then the first game state (5 press start or 6 main menu on the
// front-end level after vfAC chose, 7 in game elsewhere).
void CKS08GameManager::ResetRuntime() {
    // 0x00c50dc4: a static the game initialises to (-1, -1) (the live +0x298..+0x2a4) _maybe.
    static const float kNoPosition[2] = {-1.0f, -1.0f};
    ResetRuntimeImpl();
    m_flags64 &= ~0x10000000u;
    m_unk4CC = 0;
    m_flags64 &= 0xfff1ffffu;
    SetPlayerActive(1, GetPlayerCount() > 1 ? 1 : 0);
    Vf314(1, 0);
    m_afUnk298[2] = kNoPosition[0];
    m_afUnk298[3] = kNoPosition[1];
    static_cast<IKNode2d*>(m_unk2A8[1])->Disable();
    static_cast<IKNode2d*>(m_unk2B0[1])->Disable();
    SetPlayerActive(0, GetPlayerCount() != 0 ? 1 : 0);
    Vf314(0, 0);
    m_afUnk298[0] = kNoPosition[0];
    m_afUnk298[1] = kNoPosition[1];
    static_cast<IKNode2d*>(m_unk2A8[0])->Disable();
    static_cast<IKNode2d*>(m_unk2B0[0])->Disable();
    m_unk4A3 = 0;
    m_flags64 &= 0xfffef7ffu;
    CKInput* input = g_pEngine->m_input;
    input->SelectMappingSet(0);
    input->SetMappingEnabled(0, 1);
    const uint32_t project = static_cast<uint32_t>(input->FindMappingIndexByName("IKCommonGameManager")) & 0xff;
    m_pCommonInputDicos = project != 0xff ? input->m_aaInputDico[project] : nullptr;
    g_pEngine->m_flashManager->SetInputConfig(1);
    FollowCamera(g_pEngine->m_soundManager->m_pVoiceManager->m_pListener);
    for (uint32_t i = GetMaxPlayers(); i != 0; --i) {
        PlayerHudSlot& slot = PlayerHudSlots()[i - 1];
        slot.m_pHero = nullptr;
        slot.m_ui8Flag = 0;
    }
    for (uint32_t i = Vf340(); i != 0; --i) {
        IKSerializable* menu = Vf344()[i - 1];
        if (menu != nullptr) static_cast<CKMenuBase114c*>(menu)->Reset();  // vt+0x9c
    }
    const uint8_t none = NoMenuId();
    m_ui8PrevMenu = MenuStateCount();
    m_interfaceState.Switch(none);
    m_aMenuStack[0] = none;
    m_ui32MenuStackDepth = 1;
    m_flags64 &= 0xfffff9ffu;
    m_fUnk320 = 0x1.fffffep+127f;  // FLT_MAX: TOC1 +0x7090 -> +0x28
    if (IsFrontEndLevel() == 0) {
        m_gameState.Switch(7);
        // The fade over the level start: the screen fx (+0x490) shown and started from black (opaque) to
        // black (transparent) in one second (0xb0870 ScreenFade_Start_maybe is StartColorFade_maybe's twin:
        // blend mode 1, sort mode 2, colour mode 1). The colour is the shared black at 0x00c50df8.
        CColorizedScreenFx* fade = static_cast<CColorizedScreenFx*>(m_unk490);
        const uint8_t primary[4] = {0, 0, 0, 0xff};
        const uint8_t secondary[4] = {0, 0, 0, 0};
        fade->m_BitProperties = (fade->m_BitProperties & ~CColorizedScreenFx::kActive) | CColorizedScreenFx::kActive;
        fade->StartColorFade(1.0f, 1.0f, primary, 1, 2, 1, secondary);
    } else {
        SetActiveCameraIndex(0);  // vt+0x294
        if (m_unk2FC == 0) {
            m_unk2FC = 1;
            m_gameState.Switch(5);
        } else if (m_unk2FC != 1) {
            m_gameState.Switch(6);
        }
    }
    std::memset(m_aUnk480, 0, sizeof(m_aUnk480));
    std::memset(m_aUnk488, 0, sizeof(m_aUnk488));
}

// 0x004f1d90 IKCommonGameManager_vfAC: the game restarts: KStub_Nop_12fb8, vt+0xb8 (NewGame), +0x2fc = 1,
// flags +0x64 (bits 14 and 16-19 cleared, 14 set), no request, and on the front-end level the game state 1
// (the auto-load).
void CKS08GameManager::VfACCommon() {
    NewGame();  // vt+0xb8
    m_unk2FC = 1;
    const uint32_t flags = m_flags64;
    m_flags64 = (flags & 0xfff10000u) | ((flags & 0x3fffu) | 0x4000u);
    m_ui8RequestedState = 0xff;
    m_unk4D4 &= 0x00ffffffu;  // the byte at +0x4d4 (param_1 + 0x135)
    if (IsFrontEndLevel() != 0) m_gameState.Switch(1);
}

// 0x004f2dd0 IKGameManager_Update
void CKS08GameManager::UpdateCommon(IKTime* frameClock) {
    IKTime* engineClock = g_pEngine->m_timeManager->m_pTime;
    {
        // The first player's play time (+0x10) on the engine clock's fixed delta.
        IKPlayer* player = static_cast<IKPlayer*>(m_players[0]);
        float time;
        std::memcpy(&time, &player->m_unk10, 4);
        time = engineClock->m_afDeltaTime[IKTime::FIXED_GAME_TIME] + time;
        std::memcpy(&player->m_unk10, &time, 4);
    }
    if (frameClock->m_eCurrentState != IKTime::RUNNING || g_pEngine->m_gameLoop->m_unk5c != 0) Vf320();
    Vf314(1, 0);
    Vf314(0, 0);
    // Flags 0x20000 / 0x40000 / 0x80000: the trigger signals of the starters at +0x4a4 / +0x4ac / +0x4b4.
    if ((m_flags64 & 0x20000) != 0) { m_flags64 &= ~0x20000u; QueueTriggerSignals(&m_unk4A4); }
    if ((m_flags64 & 0x40000) != 0) { m_flags64 &= ~0x40000u; QueueTriggerSignals(&m_unk4AC); }
    if ((m_flags64 & 0x80000) != 0) { m_flags64 &= ~0x80000u; QueueTriggerSignals(&m_unk4B4); }
    if (m_unk4CC != 0 && frameClock->m_eCurrentState == IKTime::RUNNING) {
        // The respawn: the game structure's current spawn point's sector requested.
        m_unk4CC = 0;
        g_pEngine->m_gameLoop->RequestSectorLoad(static_cast<IKGameStructure*>(m_gameStructure)->m_pCurrentSpawnPoint->m_iSectorIndex);
    }
    IKGameManager_UpdateLevel(this, frameClock);  // 0x13088
    // Bit 10 keeps last frame's bit 9; bit 9 is set below only in game.
    m_flags64 = (m_flags64 & ~0x400u) | (((m_flags64 >> 9) & 1) << 10);
    uint32_t inGame = 0;
    if (m_gameState.m_ui8Current == 7 && engineClock->m_eCurrentState == IKTime::RUNNING) {
        // In game: bit 9 unless a video plays, a cinematic scene is active with its black bands (flag 0 of
        // +0x34) or with its +0x22 bit 0, or flags 0x4000000 / 0x10000000 are set.
        bool blocked = g_pEngine->m_videoManager->HasVideoWithoutFlag40() != 0;
        CKSrvCinematic* cinematic = static_cast<CKSrvCinematic*>(g_pEngine->m_srvCinematic);
        if (!blocked) {
            for (uint32_t i = 0; i < cinematic->m_ui32SceneNumber && !blocked; ++i) {
                const CKCinematicScene* scene = static_cast<const CKCinematicScene*>(cinematic->m_pSceneList[i]);
                if ((scene->m_baData & 1) != 0 && (scene->m_baBlackBandData & 1) != 0) blocked = true;
            }
        }
        if (!blocked) {
            for (uint32_t i = 0; i < cinematic->m_ui32SceneNumber && !blocked; ++i) {
                const CKCinematicScene* scene = static_cast<const CKCinematicScene*>(cinematic->m_pSceneList[i]);
                if ((scene->m_baData & 1) != 0 && (scene->m_unk22 & 1) != 0) blocked = true;
            }
        }
        if (!blocked && (m_flags64 & 0x14000000u) == 0) inGame = 0x200;
    }
    m_flags64 = (m_flags64 & ~0x200u) | inGame;
    if ((m_flags64 & 0x400) == 0) {
        if ((m_flags64 & 0x200) != 0) m_fUnk320 = engineClock->m_afCurrentTime[IKTime::FIXED_GAME_TIME] * 0x1.eb851ep-5f;  // 0.06f
    } else if ((m_flags64 & 0x200) == 0) {
        m_fUnk320 = 0x1.fffffep+127f;  // FLT_MAX
    }
    if (m_unk04[1] != nullptr) {
        // The heroes' HUD panels, from the last controlled hero down: a hero that asked for one (its slot,
        // message 0x2666 gives the panel) while the HUD time has come shows it, any other hides its panel;
        // then the slots are cleared.
        for (uint32_t i = GetControlledHeroCount(); i-- != 0;) {
            IKSerializable* hero = PlayerHudSlots()[i].m_pHero;
            if (hero == nullptr || hero->GetClassID() == -1 ||
                engineClock->m_afCurrentTime[IKTime::FIXED_GAME_TIME] < m_fUnk320) {
                HidePlayerHudPanel(static_cast<uint8_t>(i));  // vt+0x2dc
            } else {
                SHudPanelMessage message = {nullptr, -1, 0, 0};
                hero->MessageProc(0x2666, &message);
                ShowPlayerHudPanel(message.m_pText, message.m_i32Value, message.m_i32Type, static_cast<uint8_t>(i));  // vt+0x2d8
            }
        }
        for (uint32_t i = GetMaxPlayers(); i-- != 0;) {
            PlayerHudSlots()[i].m_pHero = nullptr;
            PlayerHudSlots()[i].m_ui8Flag = 0;
        }
    }

    // The game state machine: a requested switch first, then the frame.
    m_ui8PrevState = m_gameState.m_ui8Current;
    const uint8_t requested = m_ui8RequestedState;
    if (static_cast<int8_t>(requested) != -1 && m_gameState.m_ui8Current != requested) {
        m_gameState.Switch(requested);
        m_ui8PrevState = m_ui8RequestedState;
        m_ui8RequestedState = 0xff;
    }
    m_ui8UpdatedState = m_gameState.Tick();
    // The front end's sequence: a state that returned to 0 hands over to the next one (by the halfword
    // +0x2f8: the state before the frame and the one after it).
    if (IsFrontEndLevel() != 0) {
        if (m_ui8PrevState == 1 && m_ui8UpdatedState == 0) m_gameState.Switch(4);
        if (m_ui8PrevState == 2 && m_ui8UpdatedState == 0) m_gameState.Switch(4);
        if (m_ui8PrevState == 4 && m_ui8UpdatedState == 0) m_gameState.Switch(3);
        if (m_ui8PrevState == 3 && m_ui8UpdatedState == 0) m_gameState.Switch(5);
        if (m_ui8PrevState == 5 && m_ui8UpdatedState == 0) m_gameState.Switch(6);
    }
    if (m_ui8PrevState == 9 && m_ui8UpdatedState == 0) {
        // The hero death is over: the spawn point's sector requested.
        g_pEngine->m_gameLoop->RequestSectorLoad(static_cast<IKGameStructure*>(m_gameStructure)->m_pCurrentSpawnPoint->m_iSectorIndex);
    }

    // The HUD screens: shown while the time bit's moment (+0x320) has passed.
    for (uint32_t i = Vf348(); i != 0; --i) {
        IKSerializable* hud = GetHudInterfaces()[i - 1];
        if (hud == nullptr) continue;
        static_cast<CKMenuBase114c*>(hud)->SetVisible(m_fUnk320 <= engineClock->m_afCurrentTime[IKTime::FIXED_GAME_TIME] ? 1 : 0);
    }

    // The interface state machine: the top of the menu stack becomes the shown menu.
    auto switchToStackTop = [this]() {
        if (m_unk290 != -1 || g_pEngine->m_gameLoop->m_mode == CKGameLoop::kModePauseMenu) return;
        const uint8_t top = m_aMenuStack[static_cast<int32_t>(m_ui32MenuStackDepth) - 1];
        if (top == m_interfaceState.m_ui8Current) return;
        m_ui8PrevMenu = m_interfaceState.m_ui8Current;
        m_interfaceState.Switch(top);
    };
    switchToStackTop();
    if (m_interfaceState.m_ui8Current != NoMenuId()) {
        m_interfaceState.Tick();
        // The interface video's fade: towards +0x468 at 0.02 per frame while it plays (0 otherwise).
        IKVideo* video = GetInterfaceVideo();
        float dt = 0.0f;  // TOC1 +0x6ff8
        if ((video->m_baData & 1) != 0) dt = 0x1.47ae14p-6f;  // 0x000aa948 KStub_ReturnFloat0p02_aa948
        const float level = FloatApproach_Step(dt, m_unk468);
        if (level == 255.0f) {
            video->m_baData &= ~0x10u;
            video->m_baFrameFlags &= ~0x80u;
            video->SetFadeLevel(0xff);
        } else {
            // lroundf (0x0098d3a0 bridge): the level is in [0, 255] here.
            video->SetFadeLevel(static_cast<uint32_t>(static_cast<int32_t>(level + 0.5f)));
        }
        switchToStackTop();
    }

    // This frame's bytes become last frame's.
    m_aUnk488[0] = m_aUnk480[0];
    m_aUnk488[1] = m_aUnk480[1];
    m_aUnk488[2] = m_aUnk480[2];
    m_aUnk488[3] = m_aUnk480[3];
    m_aUnk488[4] = m_aUnk480[4];
    m_aUnk488[7] = m_aUnk480[7];
    m_aUnk488[5] = m_aUnk480[5];
    m_aUnk488[6] = m_aUnk480[6];
    m_aUnk480[7] = 0;
    m_aUnk480[0] = 0;
    m_aUnk480[1] = 0;
    m_aUnk480[2] = 0;
    m_aUnk480[3] = 0;
    m_aUnk480[4] = 0;
    m_aUnk480[5] = 0;
    m_aUnk480[6] = 0;

    // The second player's pad (+0x270: 1 = back to one player, 2 = waiting for pad 2). The +0x4d8 text is the
    // "connect pad 2" prompt and +0x4dc its timer: shown for a second, hidden for half a second, again. The
    // timer is reset whenever the prompt (when there is one) is hidden or its cycle ends.
    CText2d* prompt = static_cast<CText2d*>(m_unk4D8);
    bool resetTimer = false;
    if (m_unk270 == 1) {
        SetPlayerCount(1);
        m_unk270 = 0;
        if (prompt != nullptr) { prompt->Disable(); resetTimer = true; }
    } else if (m_unk270 != 2 || GetPlayerCount() == 2) {
        if (prompt != nullptr) { prompt->Disable(); resetTimer = true; }
    } else {
        IKSerializable* text = Vf214();
        if (g_pEngine->m_input->IsPadConnected(1) == 0) {
            CKLocTextAccessor* texts = static_cast<CKLocTextAccessor*>(m_unk144);
            text = texts->m_texts.m_pBlock == nullptr ? texts->m_pText : texts->m_texts.m_pBlock[4];
        } else {
            SetPlayerCount(m_unk270 & 0xffu);  // vt+0x158 (the byte at +0x273)
            m_unk270 = 0;
        }
        if (text == nullptr) {
            if (prompt != nullptr) { prompt->Disable(); resetTimer = true; }
        } else if (prompt != nullptr) {
            m_unk4DC = m_unk4DC + frameClock->m_afDeltaTime[IKTime::FIXED_GAME_TIME];
            if (m_unk4DC < 1.0f) {
                prompt->SetTextById(text);  // vt+0x88
                prompt->Enable();           // vt+0x64
            } else {
                prompt->Disable();
                resetTimer = !(m_unk4DC < 1.5f);
            }
        }
    }
    if (resetTimer) m_unk4DC = 0.0f;
    m_flags64 &= ~0x10000000u;
}

// 0x004f46f8 KStub_Return0_4f46f8: game state 0 (idle; the front-end sequence moves on from it).
uint8_t CKS08GameManager::StateReturn0(int32_t, uint8_t) { return 0; }
// 0x004f4700 KStub_Return4_4f4700: IKCommonGameManager's state 4.
uint8_t CKS08GameManager::StateReturn4(int32_t, uint8_t) { return 4; }

// 0x004ec878 CKS08GameManager_vfF4
uint8_t CKS08GameManager::AllowsBgmDuringVideo(IKVideo* video) {
    const uint8_t state = m_gameState.m_ui8Current;
    if (state == 3) return 0;
    if (state != 5) return 1;
    return GetDemoVideo() != video ? 1 : 0;
}

// ---- C1.6 gm: the game manager slots the menus call, the new game ----
#include "Spyro2008/logic/CKS08GameStructure.h"

// 0x004ec920 KStub_Nop_4ec920: empty (vfAC calls it with 0).

// 0x004ee710 CKS08GameManager_OnLevelStart_maybe: the base's, then the sound listener follows the camera.
void CKS08GameManager::OnLevelStart() {
    CDefaultGameManager::OnLevelStart();
    FollowCamera(g_pEngine->m_soundManager->m_pVoiceManager->m_pListener);
}

// 0x004ed220 CKS08GameManager_RequestSave_maybe: the base's, then vt+0x10c.
void CKS08GameManager::RequestSave(uint32_t unused, uint8_t value) {
    CDefaultGameManager::RequestSave(unused, value);
    SetSaveRequestFlag(unused, value);
}

// 0x004f7130 CKS08GameManager_SetSaveRequestFlag_maybe: the base's (0x14f20).
void CKS08GameManager::SetSaveRequestFlag(uint32_t unused, uint8_t value) {
    CDefaultGameManager::SetSaveRequestFlag(unused, value);
}

// 0x004ed298 CKS08GameManager_vfB4: CDefaultGameManager_RequestGameExit_maybe (0x14d68).
void CKS08GameManager::ExitGame() { RequestGameExit(); }

// 0x004ed058 IKCommonGameManager_vf1D4: CDefaultGameManager_vf1D4 (0x172b0).
void CKS08GameManager::ResetEditedOptionsCommon() { CDefaultGameManager::ResetEditedOptions(); }

// 0x004ee310 CKS08GameManager_IsVideoSkipPressed_maybe
// BUG(original): without a "Flash Manager" project the configuration pointer is null and the first
// GetButtonState reads through it.
uint8_t CKS08GameManager::IsVideoSkipPressed() {
    CKInput* input = g_pEngine->m_input;
    const uint32_t project = static_cast<uint32_t>(input->FindMappingIndexByName("Flash Manager")) & 0xff;
    const CKInputDico* dico = project != 0xff ? &input->m_aaInputDico[project][1] : nullptr;
    uint8_t pressed = 1;
    if (dico->GetButtonState(0xe) != 0xff && dico->GetButtonState(4) != 0xff && dico->GetButtonState(5) != 0xff) pressed = 0;
    if (IsPlayerActive(1) == 0) return pressed;  // vt+0x180
    if (dico->GetButtonState(0x22) == 0xff || dico->GetButtonState(0x18) == 0xff) return static_cast<uint8_t>(pressed | 1);
    return static_cast<uint8_t>(pressed | (dico->GetButtonState(0x19) == 0xff ? 1 : 0));
}

// 0x004ee668 CKS08GameManager_vf2F0
uint8_t CKS08GameManager::Vf2F0(uint32_t index) {
    if (index >= m_unk474.m_ui32NbUsedElt) return 0;
    CKGameState* state = static_cast<CKGameState*>(m_unk474.m_pBlock[index]);
    if (state == nullptr) return 0;
    state->ApplyToStructure();  // vt+0x70
    state->Vf74();              // vt+0x74 (empty)
    return 1;
}

// 0x004eed08 CKS08GameManager_ResetProgress_maybe (XXL2 IKCommonGameManager::NewGame)
void CKS08GameManager::NewGameCommon() {
    BasicNewGame();  // 0x159a8
    Vf334();
    m_flags64 &= ~0x80u;
    m_unk2FC = 2;
}

// The entry index of 0x4ecdd0 / 0x4ecf80 (mulli/add, rldicl 56: the low byte). GetMaxPlayers (vt+0x150) is
// only called for actions from 50 up.
static int32_t ActionEntryIndex(CKS08GameManager* manager, uint32_t action, uint8_t player) {
    if (action < 0x32) return static_cast<int32_t>((static_cast<uint32_t>(player) * 0x32 + action) & 0xff);
    const uint32_t players = manager->GetMaxPlayers();
    return static_cast<int32_t>(((players * 0x19 + player) * 2 + (action - 0x32)) & 0xff);
}

// 0x004ecd10 CKS08GameManager_vf18C: the dialogue button of the player (a byte +0x4a1 + player, -1 = none) in the common
// input configuration, entry (+0x4a3) * 50 + button.
uint8_t CKS08GameManager::GetDialogueButtonState(int32_t player) {
    const uint8_t* buttons = &m_unk4A1;
    if (static_cast<int8_t>(buttons[player]) == -1) return 0;
    return m_pCommonInputDicos->GetButtonState(static_cast<int32_t>(m_unk4A3) * 50 + static_cast<int8_t>(buttons[player]));
}

// 0x004ecdd0 CKS08GameManager_IsActionPressed
uint8_t CKS08GameManager::IsActionPressed(uint32_t action, uint8_t player) {
    return m_pCommonInputDicos->GetButtonState(ActionEntryIndex(this, action, player));
}

// 0x004ecf80 CKS08GameManager_GetActionValue
float CKS08GameManager::GetActionValue(uint32_t action, uint8_t player) {
    return m_pCommonInputDicos->GetActionTimePressed(ActionEntryIndex(this, action, player));
}
