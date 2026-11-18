// CKDefaultGameStructure_2.cpp - reconstructed original translation unit 0x41714-0x426b8 (GAME_TOC1, main_toc1), 12 functions, 6 live.
// Primary class: CKDefaultGameStructure  key 0x354c  category Logic  size 0x48  vtable 0xb146e8
// Other owners: IKGameStructure (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x41714  FUN_00041714  [dead]
//   [x] 0x41888  CKDefaultGameStructure_DestroyGame
//   [x] 0x41910  IKGameStructure_ClearReferences
//   [x] 0x41aa0  CKDefaultGameStructure_PostLoad
//   [ ] 0x41ca8  CKDefaultGameStructure_IsModuleFlag2SetOrAbsentById_Arr48_maybe  [dead]
//   [ ] 0x41d70  FUN_00041d70  [dead]
//   [ ] 0x41d94  FUN_00041d94  [dead]
//   [x] 0x41da8  CKDefaultGameStructure_MarkSekensSeenInCurrentLevel_maybe  (ported in CKGameState.cpp)
//   [ ] 0x41db4  CKDefaultGameStructure_MarkSekensSeenInCurrentLevel_maybe_Body  [dead]
//   [ ] 0x41e80  CKDefaultGameStructure_IsSekensSeenInCurrentLevel_maybe  [dead]
//   [x] 0x41f90  CKDefaultGameStructure_LoadImpl
//   [x] 0x41ff4  KStub_Nop_41ff4  (empty; no live reference: Ghidra's are stray computed calls)
#include "k2000/misc/IKGameStructure.h"

#include "Spyro2008/logic/IKGameObject.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/memory/Mem.h"
#include "k2000/logic/CKGameState.h"
#include "k2000/logic/CKGameModule.h"
#include "k2000/logic/CKTriggerSynchro.h"
#include "k2000/logic/GameVector.h"
#include "k2000/logic/CKGameLevel.h"
#include "k2000/logic/CKGameSpawnPoint.h"
#include "k2000/misc/CoreSingletons.h"

namespace {
template <class T>
void RemoveLevelEntries(TVector<T*, 8>* list, uint32_t* localCount) {
    for (uint32_t i = list->m_ui32NbUsedElt; i != 0; --i) {
        T** entry = &list->m_pBlock[i - 1];
        if (IKGameObject_IsGameEntry(reinterpret_cast<IKSerializable*>(*entry))) continue;  // single inheritance
        const uint32_t last = --list->m_ui32NbUsedElt;
        if (i - 1 != last) *entry = list->m_pBlock[last];
        --*localCount;
    }
}
}  // namespace

// 0x00041910 IKGameStructure_Destroy (Ghidra IKGameStructure_ClearReferences)
void IKGameStructure::Destroy() {
    RemoveLevelEntries(&m_vpStages, &m_ui32NbLocalStages);
    RemoveLevelEntries(&m_vpStates, &m_ui32NbLocalStates);
    if (m_vpUnk24.m_pBlock != nullptr) {
        Mem_FreeAligned16(m_vpUnk24.m_pBlock);
        m_vpUnk24.m_pBlock = nullptr;
    }
    m_vpUnk24.m_ui32NbUsedElt = 0;
    m_vpUnk24.m_pBlock = nullptr;
    if (m_pCurrentSpawnPoint != nullptr && m_bCurrentSpawnPointGlobal == 0) m_pCurrentSpawnPoint = nullptr;
}

// 0x00041f90 (Ghidra CKDefaultGameStructure_LoadImpl): IKGameStructure's Load. GAME.KP3 holds the levels
// and game states; a level file appends its own and replaces the +0x24 list.
int32_t IKGameStructure::Load(IKFile* file, int32_t type) {
    if (type == K_LEVEL_PLATEFORMS) {
        ReadU32LE(file, &m_ui32NbLocalStages);
        if (m_ui32NbLocalStages != 0) {
            GameVector_Resize(&m_vpStages, m_ui32NbLocalStages + m_ui32NbGlobalStages);
            IKFile_ReadObjectRefArray(file, reinterpret_cast<IKSerializable**>(m_vpStages.m_pBlock + m_ui32NbGlobalStages),
                                      m_ui32NbLocalStages);
        }
        ReadU32LE(file, &m_ui32NbLocalStates);
        if (m_ui32NbLocalStates != 0) {
            GameVector_Resize(&m_vpStates, m_ui32NbLocalStates + m_ui32NbGlobalStates);
            IKFile_ReadObjectRefArray(file, reinterpret_cast<IKSerializable**>(m_vpStates.m_pBlock + m_ui32NbGlobalStates),
                                      m_ui32NbLocalStates);
        }
        uint32_t count = 0;
        ReadU32LE(file, &count);
        if (count == 0) return 1;
        GameVector_Allocate(&m_vpUnk24, count);
        GameVector_Resize(&m_vpUnk24, count);  // the capacity is already count: only the length
        IKFile_ReadObjectRefArray(file, reinterpret_cast<IKSerializable**>(m_vpUnk24.m_pBlock), count);
        return 1;
    }
    if (type != K_GAME_PLATEFORMS) return 1;
    IKFile_ReadRef(file, &m_pGameManager);
    IKFile_ReadRef(file, &m_pStartGameState);
    ReadU32LE(file, &m_ui32NbGlobalStages);
    GameVector_Allocate(&m_vpStages, m_ui32NbGlobalStages);
    if (m_ui32NbGlobalStages != 0) {
        GameVector_Resize(&m_vpStages, m_ui32NbGlobalStages);
        IKFile_ReadObjectRefArray(file, reinterpret_cast<IKSerializable**>(m_vpStages.m_pBlock), m_ui32NbGlobalStages);
    }
    ReadU32LE(file, &m_ui32NbGlobalStates);
    GameVector_Allocate(&m_vpStates, m_ui32NbGlobalStates);
    if (m_ui32NbGlobalStates == 0) return 1;
    GameVector_Resize(&m_vpStates, m_ui32NbGlobalStates);
    IKFile_ReadObjectRefArray(file, reinterpret_cast<IKSerializable**>(m_vpStates.m_pBlock), m_ui32NbGlobalStates);
    return 1;
}

// 0x00041888 CKDefaultGameStructure_DestroyGame
void IKGameStructure::DestroyGame() {
    if (m_vpStates.m_pBlock != nullptr) {
        Mem_FreeAligned16(m_vpStates.m_pBlock);
        m_vpStates.m_pBlock = nullptr;
    }
    m_vpStates.m_ui32NbUsedElt = 0;
    m_vpStates.m_pBlock = nullptr;
    if (m_vpStages.m_pBlock != nullptr) {
        Mem_FreeAligned16(m_vpStages.m_pBlock);
        m_vpStages.m_ui32NbUsedElt = 0;
        m_vpStages.m_pBlock = nullptr;
    }
}

// 0x00041aa0 CKDefaultGameStructure_PostLoad
int32_t IKGameStructure::PostLoad(int32_t type) {
    if (type == 1) {
        AppConfig* config = Engine_GetBootConfigStruct();  // 0x252a90
        if (config != nullptr) {
            const uint32_t* uuid = reinterpret_cast<const uint32_t*>(config->gameStateUuid);  // +0x9c
            if (!Uuid_IsNull(uuid)) {
                for (uint32_t i = 0; i < m_vpStates.m_ui32NbUsedElt; ++i) {
                    if (Uuid_Equals(m_vpStates.m_pBlock[i]->m_guidIdentifier, uuid)) {
                        m_pStartGameState = m_vpStates.m_pBlock[i];
                        break;
                    }
                }
            } else if (static_cast<uint32_t>(config->unkAc) < m_vpStates.m_ui32NbUsedElt) {
                m_pStartGameState = m_vpStates.m_pBlock[static_cast<uint32_t>(config->unkAc)];
            }
        }
        if (m_pStartGameState == nullptr) {
            m_pCurrentSpawnPoint = nullptr;
        } else {
            m_pStartGameState->ApplyToStructure();  // vt+0x70
            // BUG(original): a start state without a spawn point leaves none current, and this reads through null.
            CDefaultGameManager* manager = m_pGameManager;
            const int32_t level = m_pCurrentSpawnPoint->m_pGameStage->m_i32StageIndex;
            manager->m_requestedSector = m_pCurrentSpawnPoint->m_iSectorIndex;
            manager->m_requestedLevel = level;
        }
    } else if (type == 0 && m_vpUnk24.m_ui32NbUsedElt != 0) {
        for (uint32_t i = 0; i < m_vpUnk24.m_ui32NbUsedElt; ++i) {
            CKTriggerSynchro* synchro = reinterpret_cast<CKTriggerSynchro*>(m_vpUnk24.m_pBlock[i]);
            static_cast<CKGameModule*>(synchro->m_unk10)->m_pTriggerSynchro = synchro;  // CKGameModule_SetField2C_maybe 0x3b4f0
        }
    }
    return 1;
}
