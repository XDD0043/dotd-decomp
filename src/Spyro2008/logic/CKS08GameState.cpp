// CKS08GameState.cpp - reconstructed original translation unit 0x5094c8-0x50f2c8 (GAME_TOC1, main_toc1), 60 functions, 53 live.
// Primary class: CKS08GameState  key 0x794c  category Logic  size 0x1e0  vtable 0xb2b4f8
// Other owners: CKS08GameStructure (9), GetDragonTotalUpgradePoints (1), AddElementManaSpent (1), AddDragonPlayTime (1), AddPlayerSlotPlayTime (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x5094c8  CKS08GameState_Delete
//   [x] 0x509518  CKS08GameState_vfC4
//   [x] 0x509520  CKS08GameState_vfD0
//   [ ] 0x509528  CKS08GameState_FindObjectEntryIndex_maybe  [dead]
//   [ ] 0x509580  KStub_Nop_509580  [dead]
//   [ ] 0x509588  KStub_Nop_509588  [dead]
//   [ ] 0x509590  CKS08GameState_QueryGameManagerVfC4_maybe  [dead]
//   [x] 0x5095e0  CKS08GameState_RemoveObjectEntryAt_maybe
//   [x] 0x509638  CKS08GameState_AddObjectEntry_maybe
//   [x] 0x5096f0  CKS08GameState_vf8C
//   [x] 0x509718  CKS08GameState_AddModuleValue_maybe
//   [x] 0x509740  CKS08GameState_AddStageValue_maybe
//   [x] 0x509768  CKS08GameState_vfAC
//   [x] 0x509790  CKS08GameState_vfA8
//   [x] 0x5097b8  CKS08GameState_vfA4
//   [x] 0x5097e0  CKS08GameState_SaveStateByte_maybe
//   [x] 0x509808  CKS08GameState_ClearGameData_maybe
//   [x] 0x509a70  CKS08GameState_ClearLevelData
//   [x] 0x509a98  CKS08GameState_InitLevelData
//   [x] 0x509ac0  CKS08GameState_vf58
//   [x] 0x509db0  CKS08GameState_PostLoad  (= the inherited slot)
//   [x] 0x509e78  CKS08GameState_RecursiveRegistration  (inherited: CKGameState_RecursiveRegistration)
//   [x] 0x509ea0  CKS08GameState_Destroy
//   [x] 0x509ec8  CKS08GameState_Construct_2  (= 0x50b458 CKS08GameState_Construct)
//   [x] 0x50a128  CKS08GameState_DeleteArray
//   [ ] 0x50a1d0  CKS08GameState_CountFlaggedObjectEntries_maybe  [dead]
//   [ ] 0x50a220  RegisterCKS08GameStateClass
//   [ ] 0x50a2a8  _GLOBAL__D_50a2a8
//   [ ] 0x50a2b8  _GLOBAL__I_50a2b8
//   [x] 0x50a2c8  CKS08GameState_vf84
//   [x] 0x50a388  CKS08GameState_CopyFrom_maybe
//   [x] 0x50a710  CKS08GameState_ResetStateFlags_maybe
//   [x] 0x50a8e0  CKS08GameState_vfC8
//   [x] 0x50a930  CKS08GameState_vfCC
//   [ ] 0x50a980  CKS08GameState_CountFlaggedObjectEntriesByCategory_maybe  [dead]
//   [x] 0x50a9f0  CKS08GameState_ApplyToGame_maybe
//   [x] 0x50af70  CKS08GameState_vfC0
//   [x] 0x50afc8  CKS08GameState_CaptureFromGame_maybe
//   [x] 0x50b458  CKS08GameState_Construct
//   [x] 0x50b6b8  CKS08GameState_CreateArray
//   [x] 0x50b9d8  CKS08GameState_Create
//   [x] 0x50bc78  CKS08GameState_Save
//   [x] 0x50cc90  CKS08GameState_Destructor_2  (= 0x50e928)
//   [x] 0x50d050  CKS08GameState_Load
//   [x] 0x50e560  CKS08GameState_DeletingDestructor  (the destructor; delete)
//   [x] 0x50e928  CKS08GameState_Destructor  (its own vectors here, then ~CKGameState (CKGameState.cpp))
//   [x] 0x50ece8  CKS08GameStructure_Delete
//   [ ] 0x50ed38  FUN_0050ed38  [dead]
//   [x] 0x50ed40  CKS08GameStructure_InvalidateCategoryCount_maybe
//   [x] 0x50ed60  CKS08GameStructure_SaveCheckpointSnapshot_maybe
//   [x] 0x50eec0  CKS08GameStructure_RestoreCheckpointSnapshot_maybe
//   [x] 0x50f050  GetDragonTotalUpgradePoints_maybe
//   [x] 0x50f0b8  CKS08GameStructure_GetEnemyKills_maybe
//   [x] 0x50f0d0  CKS08GameStructure_GetBestCombo_maybe
//   [x] 0x50f0e8  CKS08GameStructure_GetMostUsedElement_maybe
//   [x] 0x50f200  CKS08GameStructure_GetDragonPlayTime_maybe
//   [x] 0x50f218  CKS08GameStructure_AddEnemyKill_maybe  (inline, CKS08GameStructure.h)
//   [x] 0x50f238  AddElementManaSpent_maybe
//   [x] 0x50f288  AddDragonPlayTime_maybe
//   [x] 0x50f2a8  AddPlayerSlotPlayTime_maybe
//
//   [ ] 0x9c71c0  CKS08GameState_IsKindOfClass  [inline]
//   [x] 0x9c71f8  CKS08GameState_GetClassType  [inline]
//   [x] 0x9c7200  CKS08GameState_GetClassID  [inline]
#include "Spyro2008/logic/CKS08GameState.h"

#include <cstring>
#include <initializer_list>

#include "Spyro2008/logic/CKS08GameLevel.h"
#include "Spyro2008/logic/CKS08GameLevelCollectible.h"
#include "Spyro2008/logic/CKS08GameStructure.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/logic/GameVector.h"
#include "k2000/misc/Engine.h"

namespace {

// count little-endian words in one read (the original reads 0x14 or 8 bytes, then swaps each word).
void ReadWordsLE(IKFile* file, void* dst, uint32_t count) {
    uint8_t bytes[0x14];
    ReadRaw(file, bytes, count * 4);
    for (uint32_t i = 0; i < count; ++i) {
        const uint32_t word = static_cast<uint32_t>(bytes[i * 4]) | (static_cast<uint32_t>(bytes[i * 4 + 1]) << 8) |
                              (static_cast<uint32_t>(bytes[i * 4 + 2]) << 16) |
                              (static_cast<uint32_t>(bytes[i * 4 + 3]) << 24);
        std::memcpy(static_cast<uint8_t*>(dst) + i * 4, &word, 4);
    }
}

template <class T>
void ClearVector(TVector<T, 8>* vector) {
    vector->m_pBlock = nullptr;
    vector->m_ui32NbUsedElt = 0;
    vector->m_ui32NbElt = 8;
}

}  // namespace

// 0x0050b458 CKS08GameState_Construct: CKGameState's part (inlined), then +0xd8 and the twelve byte lists.
CKS08GameState::CKS08GameState() {
    ClearVector(&m_vObjectStates);
    for (TVector<uint8_t, 8>& list : m_avObjectiveStates) ClearVector(&list);
}

// 0x00509ac0 CKS08GameState_vf58 (InitializeGameData). The old blocks are not freed; the lengths are not
// reset; +0x1c4..+0x1c9 are left as they are.
void CKS08GameState::InitializeGameData() {
    CKGameState::InitializeGameData();
    m_aUnk90[3] = 300;
    m_aUnk90[0] = 300;
    m_aUnk90[1] = 300;
    m_aUnk90[2] = 300;
    for (int i = 4; i < 8; ++i) m_aUnk90[i] = 0;
    for (int i = 4; i >= 0; --i) m_adwSpyroElementXp[i] = 0;
    for (int i = 4; i >= 0; --i) m_adwCynderElementXp[i] = 0;
    m_vObjectStates.m_ui32NbElt = 8;
    m_vObjectStates.m_pBlock = static_cast<ObjectState*>(Mem_AllocAligned16(8 * static_cast<uint32_t>(sizeof(ObjectState))));
    m_afUnk124[2] = 0.0f;
    m_afUnk124[1] = 0.0f;
    m_afUnk124[0] = 0.0f;
    m_fPlayer1PlayTime = 0;
    m_adwCynderElementManaSpent[0] = 0;
    m_adwEnemyKills[1] = 0;
    m_adwBestCombo[1] = 0;
    m_adwEnemyKills[0] = 0;
    m_adwBestCombo[0] = 0;
    for (int i = 4; i >= 0; --i) m_adwSpyroElementManaSpent[i] = 0;
    for (int i = 4; i >= 1; --i) m_adwCynderElementManaSpent[i] = 0;
    for (TVector<uint8_t, 8>& list : m_avObjectiveStates) GameVector_Reserve(&list);
    for (int i = 1; i >= 0; --i) {
        m_abEquippedArmor[i][2] = 3;
        m_abEquippedArmor[i][1] = 3;
        m_abEquippedArmor[i][0] = 3;
    }
    m_aUnk1CA[18] = 0;  // +0x1dc
    m_aUnk1CA[0] = 1;   // +0x1ca
    m_bCynderArmorMeshHidden = 0;
    m_bSpyroArmorMeshHidden = 0;
    for (int i = 1; i < 18; ++i) m_aUnk1CA[i] = 0;  // +0x1cb..+0x1db
}

// 0x0050d050 CKS08GameState_Load
int32_t CKS08GameState::Load(IKFile* file, int32_t type) {
    CKGameState::Load(file, type);
    if (type == K_GAME_MEMCARD) {
        for (uint32_t& value : m_aUnk90) ReadU32LE(file, &value);
        ReadWordsLE(file, m_adwSpyroElementXp, 5);
        ReadWordsLE(file, m_adwCynderElementXp, 5);
        for (uint32_t i = 0; i < m_vObjectStates.m_ui32NbUsedElt; ++i) {
            ReadU8(file, &m_vObjectStates.m_pBlock[i].m_ui8State);
        }
        ReadWordsLE(file, m_adwEnemyKills, 2);
        ReadWordsLE(file, m_adwBestCombo, 2);
        ReadWordsLE(file, m_adwSpyroElementManaSpent, 5);
        ReadWordsLE(file, m_adwCynderElementManaSpent, 5);
        ReadWordsLE(file, &m_afUnk124[0], 2);  // +0x124, +0x128
        uint32_t words[2];
        ReadWordsLE(file, words, 2);  // +0x12c, +0x130: one 8-byte read
        std::memcpy(&m_afUnk124[2], &words[0], 4);
        m_fPlayer1PlayTime = words[1];
        for (TVector<uint8_t, 8>& list : m_avObjectiveStates) {
            for (uint32_t j = 0; j < list.m_ui32NbUsedElt; ++j) ReadU8(file, &list.m_pBlock[j]);
        }
        for (uint8_t& value : m_abScriptCounters) ReadU8(file, &value);
        for (int i = 1; i >= 0; --i) {
            ReadU8(file, &m_abEquippedArmor[i][2]);
            ReadU8(file, &m_abEquippedArmor[i][1]);
            ReadU8(file, &m_abEquippedArmor[i][0]);
        }
        ReadU8(file, &m_bCynderArmorMeshHidden);
        ReadU8(file, &m_bSpyroArmorMeshHidden);
        for (uint8_t& value : m_aUnk1CA) ReadU8(file, &value);
        return 1;
    }
    if (type == kGameStructureBlock) {
        for (uint32_t& value : m_aUnk90) ReadU32LE(file, &value);
        ReadWordsLE(file, m_adwSpyroElementXp, 5);
        ReadWordsLE(file, m_adwCynderElementXp, 5);
        uint32_t count = 0;
        ReadU32LE(file, &count);
        for (uint32_t i = 0; i < count; ++i) {
            ObjectState entry;
            entry.m_pObject = nullptr;
            IKFile_ReadObjectRef(file, &entry.m_pObject);
            entry.m_ui8State = 0;
            GameVector_Add(&m_vObjectStates, entry);
        }
        for (TVector<uint8_t, 8>& list : m_avObjectiveStates) {
            uint32_t length = 0;
            ReadU32LE(file, &length);
            GameVector_Resize(&list, length);
            for (uint32_t j = 0; j < length; ++j) ReadU8(file, &list.m_pBlock[j]);
        }
        for (uint8_t& value : m_abScriptCounters) ReadU8(file, &value);
        return 1;
    }
    if (type != K_LEVEL_PLATEFORMS) return 1;
    // The level part: references and end offsets; the known ones are skipped (Seek), the others added
    // with state 0 (nothing more is read for them).
    uint32_t count = 0;
    ReadU32LE(file, &count);
    while (count-- != 0) {
        IKSerializable* object = nullptr;
        IKFile_ReadObjectRef(file, &object);
        uint32_t end = 0;
        ReadU32LE(file, &end);
        bool found = false;
        for (uint32_t i = m_vObjectStates.m_ui32NbUsedElt; i-- != 0;) {  // from the last entry down
            if (m_vObjectStates.m_pBlock[i].m_pObject == object) {
                found = true;
                break;
            }
        }
        if (found) {
            file->Seek(static_cast<int32_t>(end), kSeekSet);
            continue;
        }
        ObjectState entry;
        entry.m_pObject = object;
        entry.m_ui8State = 0;
        GameVector_Add(&m_vObjectStates, entry);
    }
    return 1;
}

// ---- C1.6 gm: the state and the game structure ----
namespace {
uint32_t FloatBits(float value) {
    uint32_t bits;
    std::memcpy(&bits, &value, 4);
    return bits;
}
float BitsFloat(uint32_t bits) {
    float value;
    std::memcpy(&value, &bits, 4);
    return value;
}
}  // namespace

// 0x0050a9f0 CKS08GameState_ApplyToGame_maybe (XXL2 ApplyToStructure): CKGameState's; outside the chapter
// mode (game manager vt+0xc4 == 0) the counters, the collectibles' states (+0x1c), the six bytes +0xb4 and
// the unlock bytes; always the bytes +0x1e4..+0x1e9 and the twelve byte lists; then the eight {byte, word}
// pairs +0xbc..+0x108 cleared and the checkpoint copies taken. Stores in the original's order.
void CKS08GameState::ApplyToStructure() {
    CKGameState::ApplyToStructure();
    CKS08GameStructure* s = static_cast<CKS08GameStructure*>(m_pGameStructure);
    if (g_pEngine->m_gameManager->VfC4() == 0) {
        s->m_dwSpyroHealth = m_aUnk90[0];
        s->m_dwCynderHealth = m_aUnk90[1];
        s->m_dwSpyroMana = m_aUnk90[2];
        s->m_dwCynderMana = m_aUnk90[3];
        s->m_dwSpyroFury = m_aUnk90[4];
        s->m_dwCynderFury = m_aUnk90[5];
        s->SetRtWord(0x84, m_aUnk90[6]);
        s->SetRtWord(0x88, m_aUnk90[7]);
        s->SetRtWord(0x9c, m_adwSpyroElementXp[4]);
        s->SetRtWord(0x98, m_adwSpyroElementXp[3]);
        s->SetRtWord(0x94, m_adwSpyroElementXp[2]);
        s->SetRtWord(0x90, m_adwSpyroElementXp[1]);
        s->SetRtWord(0x8c, m_adwSpyroElementXp[0]);
        s->SetRtWord(0xb0, m_adwCynderElementXp[4]);
        s->SetRtWord(0xac, m_adwCynderElementXp[3]);
        s->SetRtWord(0xa8, m_adwCynderElementXp[2]);
        s->SetRtWord(0xa4, m_adwCynderElementXp[1]);
        s->SetRtWord(0xa0, m_adwCynderElementXp[0]);
        for (uint32_t i = m_vObjectStates.m_ui32NbUsedElt; i != 0; --i) {
            const ObjectState& entry = m_vObjectStates.m_pBlock[i - 1];
            static_cast<CKS08GameLevelCollectible*>(entry.m_pObject)->m_bCollected = entry.m_ui8State;
        }
        s->SetRtWord(0x110, m_adwEnemyKills[1]);
        s->SetRtWord(0x118, m_adwBestCombo[1]);
        s->SetRtWord(0x148, FloatBits(m_afUnk124[1]));
        s->SetRtWord(0x10c, m_adwEnemyKills[0]);
        s->SetRtWord(0x114, m_adwBestCombo[0]);
        s->SetRtWord(0x144, FloatBits(m_afUnk124[0]));
        s->SetRtWord(0x150, m_fPlayer1PlayTime);
        s->SetRtWord(0x14c, FloatBits(m_afUnk124[2]));
        s->SetRtWord(0x12c, m_adwSpyroElementManaSpent[4]);
        s->SetRtWord(0x128, m_adwSpyroElementManaSpent[3]);
        s->SetRtWord(0x124, m_adwSpyroElementManaSpent[2]);
        s->SetRtWord(0x120, m_adwSpyroElementManaSpent[1]);
        s->SetRtWord(0x11c, m_adwSpyroElementManaSpent[0]);
        s->SetRtWord(0x140, m_adwCynderElementManaSpent[4]);
        s->SetRtWord(0x13c, m_adwCynderElementManaSpent[3]);
        s->SetRtWord(0x138, m_adwCynderElementManaSpent[2]);
        s->SetRtWord(0x134, m_adwCynderElementManaSpent[1]);
        s->SetRtWord(0x130, m_adwCynderElementManaSpent[0]);
        for (int32_t i = 1; i >= 0; --i) {
            s->RtByte(0xb6 + i * 3) = m_abEquippedArmor[i][2];
            s->RtByte(0xb5 + i * 3) = m_abEquippedArmor[i][1];
            s->RtByte(0xb4 + i * 3) = m_abEquippedArmor[i][0];
        }
        s->RtByte(0xba) = m_bCynderArmorMeshHidden;
        s->RtByte(0xbb) = m_bSpyroArmorMeshHidden;
        // +0x23e..+0x250 (the story and bonus unlock bytes) from +0x1ca..+0x1dc.
        for (uint32_t i = 0; i <= 0x12; ++i) s->RtByte(0x23e + i) = m_aUnk1CA[i];
    }
    for (uint32_t i = 0; i < 6; ++i) s->RtByte(0x1e4 + i) = m_abScriptCounters[i];
    for (uint32_t k = 0; k < 12; ++k) {
        const TVector<uint8_t, 8>& list = m_avObjectiveStates[k];
        for (uint32_t i = list.m_ui32NbUsedElt; i != 0; --i) s->m_avObjectiveStates[k].m_pBlock[i - 1] = list.m_pBlock[i - 1];
    }
    for (uint32_t o : {0xfcu, 0xecu, 0xdcu, 0xccu, 0xbcu}) {  // two {byte, word} pairs each
        s->RtByte(o) = 0;
        s->SetRtWord(o + 4, 0);
        s->RtByte(o + 8) = 0;
        s->SetRtWord(o + 0xc, 0);
    }
    s->SaveCheckpointSnapshot();
}

// 0x0050afc8 CKS08GameState_CaptureFromGame_maybe (XXL2 CopyFromStructure): CKGameState's, then the reverse
// of ApplyToStructure. The six bytes +0xe4..+0xe9 are 3 while the game manager's flag 0x2000000 (+0x64)
// is set (re-read for every byte); the unlock bytes +0x1ca and +0x1d7..+0x1dc always, the others and the
// byte lists outside the chapter mode only.
void CKS08GameState::CopyFromStructure() {
    CKGameState::CopyFromStructure();
    CKS08GameStructure* s = static_cast<CKS08GameStructure*>(m_pGameStructure);
    m_aUnk90[0] = s->m_dwSpyroHealth;
    m_aUnk90[1] = s->m_dwCynderHealth;
    m_aUnk90[2] = s->m_dwSpyroMana;
    m_aUnk90[3] = s->m_dwCynderMana;
    m_aUnk90[4] = s->m_dwSpyroFury;
    m_aUnk90[5] = s->m_dwCynderFury;
    m_aUnk90[6] = s->RtWord(0x84);
    m_aUnk90[7] = s->RtWord(0x88);
    m_adwSpyroElementXp[4] = s->RtWord(0x9c);
    m_adwSpyroElementXp[3] = s->RtWord(0x98);
    m_adwSpyroElementXp[2] = s->RtWord(0x94);
    m_adwSpyroElementXp[1] = s->RtWord(0x90);
    m_adwSpyroElementXp[0] = s->RtWord(0x8c);
    m_adwCynderElementXp[4] = s->RtWord(0xb0);
    m_adwCynderElementXp[3] = s->RtWord(0xac);
    m_adwCynderElementXp[2] = s->RtWord(0xa8);
    m_adwCynderElementXp[1] = s->RtWord(0xa4);
    m_adwCynderElementXp[0] = s->RtWord(0xa0);
    for (uint32_t i = m_vObjectStates.m_ui32NbUsedElt; i != 0; --i) {
        ObjectState& entry = m_vObjectStates.m_pBlock[i - 1];
        entry.m_ui8State = static_cast<CKS08GameLevelCollectible*>(entry.m_pObject)->m_bCollected;
    }
    m_adwEnemyKills[1] = s->RtWord(0x110);
    m_adwBestCombo[1] = s->RtWord(0x118);
    m_afUnk124[1] = BitsFloat(s->RtWord(0x148));
    m_adwEnemyKills[0] = s->RtWord(0x10c);
    m_adwBestCombo[0] = s->RtWord(0x114);
    m_afUnk124[0] = BitsFloat(s->RtWord(0x144));
    m_fPlayer1PlayTime = s->RtWord(0x150);
    m_afUnk124[2] = BitsFloat(s->RtWord(0x14c));
    m_adwSpyroElementManaSpent[4] = s->RtWord(0x12c);
    m_adwSpyroElementManaSpent[3] = s->RtWord(0x128);
    m_adwSpyroElementManaSpent[2] = s->RtWord(0x124);
    m_adwSpyroElementManaSpent[1] = s->RtWord(0x120);
    m_adwSpyroElementManaSpent[0] = s->RtWord(0x11c);
    m_adwCynderElementManaSpent[4] = s->RtWord(0x140);
    m_adwCynderElementManaSpent[3] = s->RtWord(0x13c);
    m_adwCynderElementManaSpent[2] = s->RtWord(0x138);
    m_adwCynderElementManaSpent[1] = s->RtWord(0x134);
    m_adwCynderElementManaSpent[0] = s->RtWord(0x130);
    uint8_t* unlock = &s->RtByte(0x23e);  // +0x23e..+0x250
    for (uint32_t i = 13; i <= 0x12; ++i) m_aUnk1CA[i] = unlock[i];  // +0x1d7..+0x1dc from +0x24b..+0x250
    for (int32_t i = 1; i >= 0; --i) {
        for (int32_t j = 2; j >= 0; --j) {
            if ((g_pEngine->m_gameManager->m_flags64 & 0x2000000u) == 0) {
                m_abEquippedArmor[i][j] = s->RtByte(0xb4 + i * 3 + j);
            } else {
                m_abEquippedArmor[i][j] = 3;
            }
        }
    }
    m_bCynderArmorMeshHidden = s->RtByte(0xba);
    m_bSpyroArmorMeshHidden = s->RtByte(0xbb);
    m_aUnk1CA[0] = unlock[0];  // +0x1ca from +0x23e
    if (g_pEngine->m_gameManager->VfC4() != 0) return;
    for (uint32_t i = 0; i < 6; ++i) m_abScriptCounters[i] = s->RtByte(0x1e4 + i);
    for (uint32_t k = 0; k < 12; ++k) {
        TVector<uint8_t, 8>& list = m_avObjectiveStates[k];
        for (uint32_t i = list.m_ui32NbUsedElt; i != 0; --i) list.m_pBlock[i - 1] = s->m_avObjectiveStates[k].m_pBlock[i - 1];
    }
    for (uint32_t i = 1; i <= 12; ++i) m_aUnk1CA[i] = unlock[i];  // +0x1cb..+0x1d6 from +0x23f..+0x24a
}

// 0x0050a388 CKS08GameState_CopyFrom_maybe (XXL2 CopyFromState): CKGameState's, then every field of Spyro's
// part (the object states and byte lists by this state's lengths).
void CKS08GameState::CopyFromState(const CKGameState* otherState) {
    CKGameState::CopyFromState(otherState);
    const CKS08GameState* other = static_cast<const CKS08GameState*>(otherState);
    for (uint32_t i = 0; i < 8; ++i) m_aUnk90[i] = other->m_aUnk90[i];
    for (uint32_t i = 0; i < 5; ++i) m_adwSpyroElementXp[i] = other->m_adwSpyroElementXp[i];
    for (uint32_t i = 0; i < 5; ++i) m_adwCynderElementXp[i] = other->m_adwCynderElementXp[i];
    for (uint32_t i = m_vObjectStates.m_ui32NbUsedElt; i != 0; --i)
        m_vObjectStates.m_pBlock[i - 1].m_ui8State = other->m_vObjectStates.m_pBlock[i - 1].m_ui8State;
    for (uint32_t i = 0; i < 2; ++i) m_adwEnemyKills[i] = other->m_adwEnemyKills[i];
    for (uint32_t i = 0; i < 2; ++i) m_adwBestCombo[i] = other->m_adwBestCombo[i];
    for (uint32_t i = 0; i < 5; ++i) m_adwSpyroElementManaSpent[i] = other->m_adwSpyroElementManaSpent[i];
    for (uint32_t i = 0; i < 5; ++i) m_adwCynderElementManaSpent[i] = other->m_adwCynderElementManaSpent[i];
    for (uint32_t i = 0; i < 3; ++i) m_afUnk124[i] = other->m_afUnk124[i];  // lfs / stfs
    m_fPlayer1PlayTime = other->m_fPlayer1PlayTime;
    for (int32_t i = 1; i >= 0; --i) {
        m_abEquippedArmor[i][2] = other->m_abEquippedArmor[i][2];
        m_abEquippedArmor[i][1] = other->m_abEquippedArmor[i][1];
        m_abEquippedArmor[i][0] = other->m_abEquippedArmor[i][0];
    }
    m_bCynderArmorMeshHidden = other->m_bCynderArmorMeshHidden;
    m_bSpyroArmorMeshHidden = other->m_bSpyroArmorMeshHidden;
    m_aUnk1CA[0] = other->m_aUnk1CA[0];
    for (uint32_t i = 0; i < 6; ++i) m_abScriptCounters[i] = other->m_abScriptCounters[i];
    for (uint32_t k = 0; k < 12; ++k) {
        TVector<uint8_t, 8>& list = m_avObjectiveStates[k];
        for (uint32_t i = list.m_ui32NbUsedElt; i != 0; --i) list.m_pBlock[i - 1] = other->m_avObjectiveStates[k].m_pBlock[i - 1];
    }
    for (uint32_t i = 1; i <= 0x12; ++i) m_aUnk1CA[i] = other->m_aUnk1CA[i];
}

// 0x0050af70 CKS08GameState_vfC0
uint8_t CKS08GameState::SavesSpawnPoint() { return g_pEngine->m_gameManager->VfC4() == 0 ? 1 : 0; }

// 0x00509ea0 CKS08GameState_Destroy
void CKS08GameState::Destroy() { CKGameState::Destroy(); }

// 0x00509a70 CKS08GameState_ClearLevelData
void CKS08GameState::DestroyLevelData() { CKGameState::DestroyLevelData(); }

namespace {
template <class T>
void FreeStateList(TVector<T, 8>* list) {
    if (list->m_pBlock != nullptr) {
        Mem_FreeAligned16(list->m_pBlock);
        list->m_pBlock = nullptr;
    }
    list->m_ui32NbUsedElt = 0;
    list->m_pBlock = nullptr;
}
}  // namespace

// 0x00509808 CKS08GameState_ClearGameData_maybe
void CKS08GameState::DestroyGameData() {
    CKGameState::DestroyGameData();  // 0x3f458
    FreeStateList(&m_vObjectStates);
    for (TVector<uint8_t, 8>& list : m_avObjectiveStates) FreeStateList(&list);
}

// 0x0050a710 CKS08GameState_ResetStateFlags_maybe
void CKS08GameState::Vf6C() {
    CKGameState::Vf6C();  // 0x3e300
    m_aUnk90[3] = 300;
    m_afUnk124[2] = 0.0f;
    m_aUnk90[0] = 300;
    m_aUnk90[1] = 300;
    m_aUnk90[2] = 300;
    for (int i = 4; i < 8; ++i) m_aUnk90[i] = 0;
    for (int i = 4; i >= 0; --i) m_adwSpyroElementXp[i] = 0;
    for (int i = 4; i >= 0; --i) m_adwCynderElementXp[i] = 0;
    m_adwEnemyKills[1] = 0;
    m_adwBestCombo[1] = 0;
    m_afUnk124[1] = 0.0f;
    m_adwEnemyKills[0] = 0;
    m_adwBestCombo[0] = 0;
    m_afUnk124[0] = 0.0f;
    m_fPlayer1PlayTime = 0;
    for (int i = 4; i >= 0; --i) m_adwSpyroElementManaSpent[i] = 0;
    m_adwCynderElementManaSpent[4] = 0;
    m_adwCynderElementManaSpent[3] = 0;
    m_adwCynderElementManaSpent[2] = 0;
    m_adwCynderElementManaSpent[0] = 0;
    m_adwCynderElementManaSpent[1] = 0;
    for (TVector<uint8_t, 8>& list : m_avObjectiveStates) {
        for (uint32_t i = 0; i < list.m_ui32NbUsedElt; ++i) list.m_pBlock[i] = 0;
    }
    for (int i = 1; i >= 0; --i) {
        m_abEquippedArmor[i][2] = 3;
        m_abEquippedArmor[i][1] = 3;
        m_abEquippedArmor[i][0] = 3;
    }
    m_aUnk1CA[18] = 0;  // +0x1dc
    m_aUnk1CA[0] = 1;   // +0x1ca
    m_bCynderArmorMeshHidden = 0;
    m_bSpyroArmorMeshHidden = 0;
    for (int i = 1; i < 18; ++i) m_aUnk1CA[i] = 0;  // +0x1cb..+0x1db
}

// 0x0050a2c8 CKS08GameState_vf84: the stage is read before the scan; an entry swapped in is not tested again.
void CKS08GameState::RemoveGameStage(uint32_t index) {
    const CKGameLevel* stage = m_vpStages.m_pBlock[index];
    for (uint32_t i = m_vObjectStates.m_ui32NbUsedElt; i != 0; --i) {
        ObjectState& entry = m_vObjectStates.m_pBlock[i - 1];
        if (static_cast<const CKGameLevel*>(static_cast<KBase1D0C*>(entry.m_pObject)->m_pLevel) != stage) continue;
        const uint32_t last = --m_vObjectStates.m_ui32NbUsedElt;
        if (i - 1 == last) continue;
        entry.m_pObject = m_vObjectStates.m_pBlock[last].m_pObject;
        entry.m_ui8State = m_vObjectStates.m_pBlock[last].m_ui8State;
    }
    CKGameState::RemoveGameStage(index);  // 0x3dae8
}

// 0x005096f0 CKS08GameState_vf8C
void CKS08GameState::RemoveGameModule(uint32_t index) { CKGameState::RemoveGameModule(index); }

// 0x005097e0 CKS08GameState_SaveStateByte_maybe
void CKS08GameState::WriteStageData(IKFile* file, int32_t type, uint32_t index) { CKGameState::WriteStageData(file, type, index); }

// 0x00509790 CKS08GameState_vfA8
void CKS08GameState::WriteModuleData(IKFile* file, int32_t type, uint32_t index) { CKGameState::WriteModuleData(file, type, index); }

// 0x0050a8e0 CKS08GameState_vfC8
void CKS08GameState::ApplyCollectibleStates() {
    for (uint32_t i = m_vObjectStates.m_ui32NbUsedElt; i != 0; --i) {
        ObjectState& entry = m_vObjectStates.m_pBlock[i - 1];
        static_cast<CKS08GameLevelCollectible*>(entry.m_pObject)->m_bCollected = entry.m_ui8State;
    }
}

// 0x0050a930 CKS08GameState_vfCC
void CKS08GameState::ClearCollectibleStates() {
    for (uint32_t i = m_vObjectStates.m_ui32NbUsedElt; i != 0; --i)
        static_cast<CKS08GameLevelCollectible*>(m_vObjectStates.m_pBlock[i - 1].m_pObject)->m_bCollected = 0;
}

// 0x0050ed60 CKS08GameStructure_SaveCheckpointSnapshot_maybe
void CKS08GameStructure::SaveCheckpointSnapshot() {
    SetRtWord(0x1f0, m_dwSpyroHealth);
    SetRtWord(0x1f4, m_dwCynderHealth);
    SetRtWord(0x1f8, m_dwSpyroMana);
    SetRtWord(0x1fc, m_dwCynderMana);
    SetRtWord(0x200, m_dwSpyroFury);
    SetRtWord(0x204, m_dwCynderFury);
    SetRtWord(0x208, RtWord(0x84));
    SetRtWord(0x20c, RtWord(0x88));
    SetRtWord(0x220, RtWord(0x9c));
    SetRtWord(0x21c, RtWord(0x98));
    SetRtWord(0x218, RtWord(0x94));
    SetRtWord(0x214, RtWord(0x90));
    SetRtWord(0x210, RtWord(0x8c));
    SetRtWord(0x234, RtWord(0xb0));
    SetRtWord(0x230, RtWord(0xac));
    SetRtWord(0x22c, RtWord(0xa8));
    SetRtWord(0x228, RtWord(0xa4));
    SetRtWord(0x224, RtWord(0xa0));
    for (int32_t i = 1; i >= 0; --i) {
        RtByte(0x23a + i * 3) = RtByte(0xb6 + i * 3);
        RtByte(0x239 + i * 3) = RtByte(0xb5 + i * 3);
        RtByte(0x238 + i * 3) = RtByte(0xb4 + i * 3);
    }
}

// 0x0050eec0 CKS08GameStructure_RestoreCheckpointSnapshot_maybe (CKS08GameManager_Restart): SaveCheckpointSnapshot's
// copies put back; the two healths come back at least at +0x1ec (cmplw / bge: the larger of the two).
void CKS08GameStructure::RestoreCheckpointSnapshot() {
    const uint32_t minimum = m_dwCheckpointMinHealth;
    m_dwSpyroHealth = minimum < RtWord(0x1f0) ? RtWord(0x1f0) : minimum;
    m_dwCynderHealth = minimum < RtWord(0x1f4) ? RtWord(0x1f4) : minimum;
    SetRtWord(0xa0, RtWord(0x224));
    m_dwSpyroMana = RtWord(0x1f8);
    m_dwCynderMana = RtWord(0x1fc);
    m_dwSpyroFury = RtWord(0x200);
    m_dwCynderFury = RtWord(0x204);
    SetRtWord(0x84, RtWord(0x208));
    SetRtWord(0x88, RtWord(0x20c));
    SetRtWord(0x9c, RtWord(0x220));
    SetRtWord(0x98, RtWord(0x21c));
    SetRtWord(0x94, RtWord(0x218));
    SetRtWord(0x90, RtWord(0x214));
    SetRtWord(0x8c, RtWord(0x210));
    SetRtWord(0xb0, RtWord(0x234));
    SetRtWord(0xac, RtWord(0x230));
    SetRtWord(0xa8, RtWord(0x22c));
    SetRtWord(0xa4, RtWord(0x228));
    for (int32_t i = 1; i >= 0; --i) {
        RtByte(0xb6 + i * 3) = RtByte(0x23a + i * 3);
        RtByte(0xb5 + i * 3) = RtByte(0x239 + i * 3);
        RtByte(0xb4 + i * 3) = RtByte(0x238 + i * 3);
    }
}

// 0x0050f050 GetDragonTotalUpgradePoints_maybe: the points a dragon (0 Spyro, else Cynder) has spent and holds:
// the free points (+0x84 / +0x88) and the four upgrade levels' points (+0x8c..+0x98 / +0xa0..+0xac).
uint32_t GetDragonTotalUpgradePoints(CKS08GameStructure* structure, int32_t dragon) {
    if (dragon == 0) {
        return structure->RtWord(0x84) + structure->RtWord(0x98) + structure->RtWord(0x94) + structure->RtWord(0x90) +
               structure->RtWord(0x8c);
    }
    return structure->RtWord(0x88) + structure->RtWord(0xac) + structure->RtWord(0xa8) + structure->RtWord(0xa4) +
           structure->RtWord(0xa0);
}

namespace {
float AddRtFloat(IKSerializable* structure, uint32_t offset, float dt) {
    CKS08GameStructure* game = static_cast<CKS08GameStructure*>(structure);
    const uint32_t bits = game->RtWord(offset);
    float value;
    std::memcpy(&value, &bits, sizeof(value));
    value = value + dt;  // fadds
    uint32_t out;
    std::memcpy(&out, &value, sizeof(out));
    game->SetRtWord(offset, out);
    return value;
}
}  // namespace

// 0x0050f238 AddElementManaSpent_maybe
void AddElementManaSpent(IKSerializable* structure, uint32_t dragon, uint32_t element, uint32_t amount) {
    CKS08GameStructure* game = static_cast<CKS08GameStructure*>(structure);
    const uint32_t offset = (dragon == 0 ? 0x11cu : 0x130u) + element * 4u;
    game->SetRtWord(offset, game->RtWord(offset) + amount);
}

// 0x0050f288 AddDragonPlayTime_maybe
void AddDragonPlayTime(IKSerializable* structure, uint32_t index, float dt) { AddRtFloat(structure, 0x144u + index * 4u, dt); }

// 0x0050f2a8 AddPlayerSlotPlayTime_maybe
void AddPlayerSlotPlayTime(IKSerializable* structure, uint32_t index, float dt) {
    AddRtFloat(structure, 0x14cu + index * 4u, dt);
}

// 0x0050bc78 CKS08GameState_Save (C2.8 save-menu): Load's K_GAME_MEMCARD layout written back, word by word (little-endian)
// and byte by byte.
int32_t CKS08GameState::Save(IKFile* file, int32_t type) {
    CKGameState::Save(file, type);
    if (type != K_GAME_MEMCARD) return 1;
    for (const uint32_t value : m_aUnk90) WriteU32LE(file, value);
    for (const uint32_t value : m_adwSpyroElementXp) WriteU32LE(file, value);
    for (const uint32_t value : m_adwCynderElementXp) WriteU32LE(file, value);
    for (uint32_t i = 0; i < m_vObjectStates.m_ui32NbUsedElt; ++i) file->Write(&m_vObjectStates.m_pBlock[i].m_ui8State, 1);
    for (const uint32_t value : m_adwEnemyKills) WriteU32LE(file, value);
    for (const uint32_t value : m_adwBestCombo) WriteU32LE(file, value);
    for (const uint32_t value : m_adwSpyroElementManaSpent) WriteU32LE(file, value);
    for (const uint32_t value : m_adwCynderElementManaSpent) WriteU32LE(file, value);
    uint32_t bits[3];
    std::memcpy(bits, m_afUnk124, sizeof(bits));  // lfs / stfs: the words' bits
    for (const uint32_t value : bits) WriteU32LE(file, value);
    WriteU32LE(file, m_fPlayer1PlayTime);
    for (const TVector<uint8_t, 8>& list : m_avObjectiveStates) {
        for (uint32_t j = 0; j < list.m_ui32NbUsedElt; ++j) file->Write(&list.m_pBlock[j], 1);
    }
    for (const uint8_t& value : m_abScriptCounters) file->Write(&value, 1);
    for (int i = 1; i >= 0; --i) {
        file->Write(&m_abEquippedArmor[i][2], 1);
        file->Write(&m_abEquippedArmor[i][1], 1);
        file->Write(&m_abEquippedArmor[i][0], 1);
    }
    file->Write(&m_bCynderArmorMeshHidden, 1);
    file->Write(&m_bSpyroArmorMeshHidden, 1);
    for (const uint8_t& value : m_aUnk1CA) file->Write(&value, 1);
    return 1;
}

// 0x005095e0 CKS08GameState_RemoveObjectEntryAt_maybe: entry `index` of the +0xd8 list removed, the later ones moved
// down (memmove; no caller in the original besides its OPD).
void CKS08GameState::RemoveObjectEntryAt(uint32_t index) {
    const uint32_t count = --m_vObjectStates.m_ui32NbUsedElt;
    ObjectState* entry = &m_vObjectStates.m_pBlock[index];
    std::memmove(entry, entry + 1, (count - index) * sizeof(ObjectState));
}

// 0x00509638 CKS08GameState_AddObjectEntry_maybe: `object` appended to the +0xd8 list with state 0 (TVector growth by
// 8); its index. No caller in the original besides its OPD.
uint32_t CKS08GameState::AddObjectEntry(IKSerializable* object) {
    if (m_vObjectStates.m_ui32NbElt == m_vObjectStates.m_ui32NbUsedElt) {
        uint32_t capacity = m_vObjectStates.m_ui32NbUsedElt + 8;
        if (capacity == 0) capacity = 8;
        m_vObjectStates.m_pBlock = static_cast<ObjectState*>(
            Mem_ReallocAligned16(m_vObjectStates.m_pBlock, capacity * static_cast<uint32_t>(sizeof(ObjectState))));
        m_vObjectStates.m_ui32NbElt = capacity;
    }
    ObjectState* entry = &m_vObjectStates.m_pBlock[m_vObjectStates.m_ui32NbUsedElt];
    ++m_vObjectStates.m_ui32NbUsedElt;
    entry->m_ui8State = 0;
    entry->m_pObject = object;
    return m_vObjectStates.m_ui32NbUsedElt - 1;
}

// 0x0050e928 CKS08GameState_Destructor (0x50cc90 _Destructor_2 the same, 0x50e560 _DeletingDestructor then the delete):
// the twelve byte lists (last to first), then the +0xd8 list freed, each block and length cleared; CKGameState's
// destructor (inlined there) follows.
CKS08GameState::~CKS08GameState() {
    for (uint32_t i = 12; i != 0; --i) {
        TVector<uint8_t, 8>& list = m_avObjectiveStates[i - 1];
        if (list.m_pBlock != nullptr) Mem_FreeAligned16(list.m_pBlock);
        list.m_pBlock = nullptr;
        list.m_ui32NbUsedElt = 0;
    }
    if (m_vObjectStates.m_pBlock != nullptr) Mem_FreeAligned16(m_vObjectStates.m_pBlock);
    m_vObjectStates.m_ui32NbUsedElt = 0;
    m_vObjectStates.m_pBlock = nullptr;
}

// 0x0050f0b8 CKS08GameStructure_GetEnemyKills_maybe / 0x0050f0d0 _GetBestCombo_maybe / 0x0050f200
// _GetDragonPlayTime_maybe: the words at +0x10c / +0x114 / the float at +0x144, + index * 4.
uint32_t CKS08GameStructure::GetEnemyKills(uint32_t index) const { return RtWord(0x10cu + index * 4u); }
uint32_t CKS08GameStructure::GetBestCombo(uint32_t index) const { return RtWord(0x114u + index * 4u); }
float CKS08GameStructure::GetDragonPlayTime(uint32_t index) const {
    const uint32_t bits = RtWord(0x144u + index * 4u);
    float value;
    std::memcpy(&value, &bits, sizeof(value));
    return value;
}

// 0x0050f0e8 CKS08GameStructure_GetMostUsedElement_maybe: of dragon `dragon`'s (0 Spyro +0x11c, else Cynder +0x130) five
// element counters, the index of the largest (unsigned): element 4 when its counter is not 0 (else 0) to start, then
// 3, 2, 1 each taking over when strictly larger; 0 when element 0's counter is larger than that maximum.
uint32_t CKS08GameStructure::GetMostUsedElement(int32_t dragon) const {
    const uint32_t base = dragon != 0 ? 0x130u : 0x11cu;
    uint32_t best = RtWord(base + 0x10);
    uint32_t index = best != 0 ? 4u : 0u;
    for (uint32_t i = 3; i != 0; --i) {
        const uint32_t value = RtWord(base + i * 4u);
        if (best < value) {
            best = value;
            index = i;
        }
    }
    if (RtWord(base) > best) return 0;
    return index;
}
