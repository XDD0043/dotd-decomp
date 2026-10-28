// CKS08GameState.cpp - reconstructed original translation unit 0x5094c8-0x50f2c8 (GAME_TOC1, main_toc1), 60 functions, 53 live.
// Primary class: CKS08GameState  key 0x794c  category Logic  size 0x1e0  vtable 0xb2b4f8
// Other owners: CKS08GameStructure (9), GetDragonTotalUpgradePoints (1), AddElementManaSpent (1), AddDragonPlayTime (1), AddPlayerSlotPlayTime (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x5094c8  CKS08GameState_Delete
//   [x] 0x509518  CKS08GameState_vfC4
//   [ ] 0x509520  CKS08GameState_vfD0
//   [ ] 0x509528  CKS08GameState_FindObjectEntryIndex_maybe  [dead]
//   [ ] 0x509580  KStub_Nop_509580  [dead]
//   [ ] 0x509588  KStub_Nop_509588  [dead]
//   [ ] 0x509590  CKS08GameState_QueryGameManagerVfC4_maybe  [dead]
//   [ ] 0x5095e0  CKS08GameState_RemoveObjectEntryAt_maybe
//   [ ] 0x509638  CKS08GameState_AddObjectEntry_maybe
//   [ ] 0x5096f0  CKS08GameState_vf8C
//   [x] 0x509718  CKS08GameState_AddModuleValue_maybe
//   [x] 0x509740  CKS08GameState_AddStageValue_maybe
//   [x] 0x509768  CKS08GameState_vfAC
//   [ ] 0x509790  CKS08GameState_vfA8
//   [x] 0x5097b8  CKS08GameState_vfA4
//   [ ] 0x5097e0  CKS08GameState_SaveStateByte_maybe
//   [ ] 0x509808  CKS08GameState_ClearGameData_maybe
//   [ ] 0x509a70  CKS08GameState_ClearLevelData
//   [x] 0x509a98  CKS08GameState_InitLevelData
//   [x] 0x509ac0  CKS08GameState_vf58
//   [ ] 0x509db0  CKS08GameState_PostLoad
//   [ ] 0x509e78  CKS08GameState_RecursiveRegistration
//   [ ] 0x509ea0  CKS08GameState_Destroy
//   [ ] 0x509ec8  CKS08GameState_Construct_2
//   [x] 0x50a128  CKS08GameState_DeleteArray
//   [ ] 0x50a1d0  CKS08GameState_CountFlaggedObjectEntries_maybe  [dead]
//   [ ] 0x50a220  RegisterCKS08GameStateClass
//   [ ] 0x50a2a8  _GLOBAL__D_50a2a8
//   [ ] 0x50a2b8  _GLOBAL__I_50a2b8
//   [ ] 0x50a2c8  CKS08GameState_vf84
//   [x] 0x50a388  CKS08GameState_CopyFrom_maybe
//   [ ] 0x50a710  CKS08GameState_ResetStateFlags_maybe
//   [ ] 0x50a8e0  CKS08GameState_vfC8
//   [ ] 0x50a930  CKS08GameState_vfCC
//   [ ] 0x50a980  CKS08GameState_CountFlaggedObjectEntriesByCategory_maybe  [dead]
//   [x] 0x50a9f0  CKS08GameState_ApplyToGame_maybe
//   [x] 0x50af70  CKS08GameState_vfC0
//   [x] 0x50afc8  CKS08GameState_CaptureFromGame_maybe
//   [x] 0x50b458  CKS08GameState_Construct
//   [x] 0x50b6b8  CKS08GameState_CreateArray
//   [x] 0x50b9d8  CKS08GameState_Create
//   [ ] 0x50bc78  CKS08GameState_Save
//   [ ] 0x50cc90  CKS08GameState_Destructor_2
//   [x] 0x50d050  CKS08GameState_Load
//   [ ] 0x50e560  CKS08GameState_DeletingDestructor
//   [ ] 0x50e928  CKS08GameState_Destructor
//   [x] 0x50ece8  CKS08GameStructure_Delete
//   [ ] 0x50ed38  FUN_0050ed38  [dead]
//   [ ] 0x50ed40  CKS08GameStructure_InvalidateCategoryCount_maybe
//   [x] 0x50ed60  CKS08GameStructure_SaveCheckpointSnapshot_maybe
//   [ ] 0x50eec0  CKS08GameStructure_RestoreCheckpointSnapshot_maybe
//   [x] 0x50f050  GetDragonTotalUpgradePoints_maybe
//   [ ] 0x50f0b8  CKS08GameStructure_GetEnemyKills_maybe
//   [ ] 0x50f0d0  CKS08GameStructure_GetBestCombo_maybe
//   [ ] 0x50f0e8  CKS08GameStructure_GetMostUsedElement_maybe
//   [ ] 0x50f200  CKS08GameStructure_GetDragonPlayTime_maybe
//   [ ] 0x50f218  CKS08GameStructure_AddEnemyKill_maybe
//   [ ] 0x50f238  AddElementManaSpent_maybe
//   [x] 0x50f288  AddDragonPlayTime_maybe
//   [x] 0x50f2a8  AddPlayerSlotPlayTime_maybe
//
//   [ ] 0x9c71c0  CKS08GameState_IsKindOfClass  [inline]
//   [x] 0x9c71f8  CKS08GameState_GetClassType  [inline]
//   [x] 0x9c7200  CKS08GameState_GetClassID  [inline]
#include "Spyro2008/logic/CKS08GameState.h"

#include <cstring>
#include <initializer_list>

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
    for (TVector<uint8_t, 8>& list : m_avbUnk134) ClearVector(&list);
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
    for (int i = 4; i >= 0; --i) m_aUnkB0[i] = 0;
    for (int i = 4; i >= 0; --i) m_aUnkC4[i] = 0;
    m_vObjectStates.m_ui32NbElt = 8;
    m_vObjectStates.m_pBlock = static_cast<ObjectState*>(Mem_AllocAligned16(8 * static_cast<uint32_t>(sizeof(ObjectState))));
    m_afUnk124[2] = 0.0f;
    m_afUnk124[1] = 0.0f;
    m_afUnk124[0] = 0.0f;
    m_unk130 = 0;
    m_aUnk110[0] = 0;
    m_aUnkEC[1] = 0;
    m_aUnkF4[1] = 0;
    m_aUnkEC[0] = 0;
    m_aUnkF4[0] = 0;
    for (int i = 4; i >= 0; --i) m_aUnkFC[i] = 0;
    for (int i = 4; i >= 1; --i) m_aUnk110[i] = 0;
    for (TVector<uint8_t, 8>& list : m_avbUnk134) GameVector_Reserve(&list);
    for (int i = 1; i >= 0; --i) {
        m_aUnkE4[i][2] = 3;
        m_aUnkE4[i][1] = 3;
        m_aUnkE4[i][0] = 3;
    }
    m_aUnk1CA[18] = 0;  // +0x1dc
    m_aUnk1CA[0] = 1;   // +0x1ca
    m_unkEA = 0;
    m_unkEB = 0;
    for (int i = 1; i < 18; ++i) m_aUnk1CA[i] = 0;  // +0x1cb..+0x1db
}

// 0x0050d050 CKS08GameState_Load
int32_t CKS08GameState::Load(IKFile* file, int32_t type) {
    CKGameState::Load(file, type);
    if (type == K_GAME_MEMCARD) {
        for (uint32_t& value : m_aUnk90) ReadU32LE(file, &value);
        ReadWordsLE(file, m_aUnkB0, 5);
        ReadWordsLE(file, m_aUnkC4, 5);
        for (uint32_t i = 0; i < m_vObjectStates.m_ui32NbUsedElt; ++i) {
            ReadU8(file, &m_vObjectStates.m_pBlock[i].m_ui8State);
        }
        ReadWordsLE(file, m_aUnkEC, 2);
        ReadWordsLE(file, m_aUnkF4, 2);
        ReadWordsLE(file, m_aUnkFC, 5);
        ReadWordsLE(file, m_aUnk110, 5);
        ReadWordsLE(file, &m_afUnk124[0], 2);  // +0x124, +0x128
        uint32_t words[2];
        ReadWordsLE(file, words, 2);  // +0x12c, +0x130: one 8-byte read
        std::memcpy(&m_afUnk124[2], &words[0], 4);
        m_unk130 = words[1];
        for (TVector<uint8_t, 8>& list : m_avbUnk134) {
            for (uint32_t j = 0; j < list.m_ui32NbUsedElt; ++j) ReadU8(file, &list.m_pBlock[j]);
        }
        for (uint8_t& value : m_aUnk1C4) ReadU8(file, &value);
        for (int i = 1; i >= 0; --i) {
            ReadU8(file, &m_aUnkE4[i][2]);
            ReadU8(file, &m_aUnkE4[i][1]);
            ReadU8(file, &m_aUnkE4[i][0]);
        }
        ReadU8(file, &m_unkEA);
        ReadU8(file, &m_unkEB);
        for (uint8_t& value : m_aUnk1CA) ReadU8(file, &value);
        return 1;
    }
    if (type == kGameStructureBlock) {
        for (uint32_t& value : m_aUnk90) ReadU32LE(file, &value);
        ReadWordsLE(file, m_aUnkB0, 5);
        ReadWordsLE(file, m_aUnkC4, 5);
        uint32_t count = 0;
        ReadU32LE(file, &count);
        for (uint32_t i = 0; i < count; ++i) {
            ObjectState entry;
            entry.m_pObject = nullptr;
            IKFile_ReadObjectRef(file, &entry.m_pObject);
            entry.m_ui8State = 0;
            GameVector_Add(&m_vObjectStates, entry);
        }
        for (TVector<uint8_t, 8>& list : m_avbUnk134) {
            uint32_t length = 0;
            ReadU32LE(file, &length);
            GameVector_Resize(&list, length);
            for (uint32_t j = 0; j < length; ++j) ReadU8(file, &list.m_pBlock[j]);
        }
        for (uint8_t& value : m_aUnk1C4) ReadU8(file, &value);
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
        s->m_unk4c = m_aUnk90[0];
        s->m_unk54 = m_aUnk90[1];
        s->m_unk64 = m_aUnk90[2];
        s->m_unk6c = m_aUnk90[3];
        s->m_unk74 = m_aUnk90[4];
        s->m_unk78 = m_aUnk90[5];
        s->SetRtWord(0x84, m_aUnk90[6]);
        s->SetRtWord(0x88, m_aUnk90[7]);
        s->SetRtWord(0x9c, m_aUnkB0[4]);
        s->SetRtWord(0x98, m_aUnkB0[3]);
        s->SetRtWord(0x94, m_aUnkB0[2]);
        s->SetRtWord(0x90, m_aUnkB0[1]);
        s->SetRtWord(0x8c, m_aUnkB0[0]);
        s->SetRtWord(0xb0, m_aUnkC4[4]);
        s->SetRtWord(0xac, m_aUnkC4[3]);
        s->SetRtWord(0xa8, m_aUnkC4[2]);
        s->SetRtWord(0xa4, m_aUnkC4[1]);
        s->SetRtWord(0xa0, m_aUnkC4[0]);
        for (uint32_t i = m_vObjectStates.m_ui32NbUsedElt; i != 0; --i) {
            const ObjectState& entry = m_vObjectStates.m_pBlock[i - 1];
            static_cast<CKS08GameLevelCollectible*>(entry.m_pObject)->m_unk1c = entry.m_ui8State;
        }
        s->SetRtWord(0x110, m_aUnkEC[1]);
        s->SetRtWord(0x118, m_aUnkF4[1]);
        s->SetRtWord(0x148, FloatBits(m_afUnk124[1]));
        s->SetRtWord(0x10c, m_aUnkEC[0]);
        s->SetRtWord(0x114, m_aUnkF4[0]);
        s->SetRtWord(0x144, FloatBits(m_afUnk124[0]));
        s->SetRtWord(0x150, m_unk130);
        s->SetRtWord(0x14c, FloatBits(m_afUnk124[2]));
        s->SetRtWord(0x12c, m_aUnkFC[4]);
        s->SetRtWord(0x128, m_aUnkFC[3]);
        s->SetRtWord(0x124, m_aUnkFC[2]);
        s->SetRtWord(0x120, m_aUnkFC[1]);
        s->SetRtWord(0x11c, m_aUnkFC[0]);
        s->SetRtWord(0x140, m_aUnk110[4]);
        s->SetRtWord(0x13c, m_aUnk110[3]);
        s->SetRtWord(0x138, m_aUnk110[2]);
        s->SetRtWord(0x134, m_aUnk110[1]);
        s->SetRtWord(0x130, m_aUnk110[0]);
        for (int32_t i = 1; i >= 0; --i) {
            s->RtByte(0xb6 + i * 3) = m_aUnkE4[i][2];
            s->RtByte(0xb5 + i * 3) = m_aUnkE4[i][1];
            s->RtByte(0xb4 + i * 3) = m_aUnkE4[i][0];
        }
        s->RtByte(0xba) = m_unkEA;
        s->RtByte(0xbb) = m_unkEB;
        // +0x23e..+0x250 (the story and bonus unlock bytes) from +0x1ca..+0x1dc.
        for (uint32_t i = 0; i <= 0x12; ++i) s->RtByte(0x23e + i) = m_aUnk1CA[i];
    }
    for (uint32_t i = 0; i < 6; ++i) s->RtByte(0x1e4 + i) = m_aUnk1C4[i];
    for (uint32_t k = 0; k < 12; ++k) {
        const TVector<uint8_t, 8>& list = m_avbUnk134[k];
        for (uint32_t i = list.m_ui32NbUsedElt; i != 0; --i) s->m_avbUnk154[k].m_pBlock[i - 1] = list.m_pBlock[i - 1];
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
    m_aUnk90[0] = s->m_unk4c;
    m_aUnk90[1] = s->m_unk54;
    m_aUnk90[2] = s->m_unk64;
    m_aUnk90[3] = s->m_unk6c;
    m_aUnk90[4] = s->m_unk74;
    m_aUnk90[5] = s->m_unk78;
    m_aUnk90[6] = s->RtWord(0x84);
    m_aUnk90[7] = s->RtWord(0x88);
    m_aUnkB0[4] = s->RtWord(0x9c);
    m_aUnkB0[3] = s->RtWord(0x98);
    m_aUnkB0[2] = s->RtWord(0x94);
    m_aUnkB0[1] = s->RtWord(0x90);
    m_aUnkB0[0] = s->RtWord(0x8c);
    m_aUnkC4[4] = s->RtWord(0xb0);
    m_aUnkC4[3] = s->RtWord(0xac);
    m_aUnkC4[2] = s->RtWord(0xa8);
    m_aUnkC4[1] = s->RtWord(0xa4);
    m_aUnkC4[0] = s->RtWord(0xa0);
    for (uint32_t i = m_vObjectStates.m_ui32NbUsedElt; i != 0; --i) {
        ObjectState& entry = m_vObjectStates.m_pBlock[i - 1];
        entry.m_ui8State = static_cast<CKS08GameLevelCollectible*>(entry.m_pObject)->m_unk1c;
    }
    m_aUnkEC[1] = s->RtWord(0x110);
    m_aUnkF4[1] = s->RtWord(0x118);
    m_afUnk124[1] = BitsFloat(s->RtWord(0x148));
    m_aUnkEC[0] = s->RtWord(0x10c);
    m_aUnkF4[0] = s->RtWord(0x114);
    m_afUnk124[0] = BitsFloat(s->RtWord(0x144));
    m_unk130 = s->RtWord(0x150);
    m_afUnk124[2] = BitsFloat(s->RtWord(0x14c));
    m_aUnkFC[4] = s->RtWord(0x12c);
    m_aUnkFC[3] = s->RtWord(0x128);
    m_aUnkFC[2] = s->RtWord(0x124);
    m_aUnkFC[1] = s->RtWord(0x120);
    m_aUnkFC[0] = s->RtWord(0x11c);
    m_aUnk110[4] = s->RtWord(0x140);
    m_aUnk110[3] = s->RtWord(0x13c);
    m_aUnk110[2] = s->RtWord(0x138);
    m_aUnk110[1] = s->RtWord(0x134);
    m_aUnk110[0] = s->RtWord(0x130);
    uint8_t* unlock = &s->RtByte(0x23e);  // +0x23e..+0x250
    for (uint32_t i = 13; i <= 0x12; ++i) m_aUnk1CA[i] = unlock[i];  // +0x1d7..+0x1dc from +0x24b..+0x250
    for (int32_t i = 1; i >= 0; --i) {
        for (int32_t j = 2; j >= 0; --j) {
            if ((g_pEngine->m_gameManager->m_flags64 & 0x2000000u) == 0) {
                m_aUnkE4[i][j] = s->RtByte(0xb4 + i * 3 + j);
            } else {
                m_aUnkE4[i][j] = 3;
            }
        }
    }
    m_unkEA = s->RtByte(0xba);
    m_unkEB = s->RtByte(0xbb);
    m_aUnk1CA[0] = unlock[0];  // +0x1ca from +0x23e
    if (g_pEngine->m_gameManager->VfC4() != 0) return;
    for (uint32_t i = 0; i < 6; ++i) m_aUnk1C4[i] = s->RtByte(0x1e4 + i);
    for (uint32_t k = 0; k < 12; ++k) {
        TVector<uint8_t, 8>& list = m_avbUnk134[k];
        for (uint32_t i = list.m_ui32NbUsedElt; i != 0; --i) list.m_pBlock[i - 1] = s->m_avbUnk154[k].m_pBlock[i - 1];
    }
    for (uint32_t i = 1; i <= 12; ++i) m_aUnk1CA[i] = unlock[i];  // +0x1cb..+0x1d6 from +0x23f..+0x24a
}

// 0x0050a388 CKS08GameState_CopyFrom_maybe (XXL2 CopyFromState): CKGameState's, then every field of Spyro's
// part (the object states and byte lists by this state's lengths).
void CKS08GameState::CopyFromState(const CKGameState* otherState) {
    CKGameState::CopyFromState(otherState);
    const CKS08GameState* other = static_cast<const CKS08GameState*>(otherState);
    for (uint32_t i = 0; i < 8; ++i) m_aUnk90[i] = other->m_aUnk90[i];
    for (uint32_t i = 0; i < 5; ++i) m_aUnkB0[i] = other->m_aUnkB0[i];
    for (uint32_t i = 0; i < 5; ++i) m_aUnkC4[i] = other->m_aUnkC4[i];
    for (uint32_t i = m_vObjectStates.m_ui32NbUsedElt; i != 0; --i)
        m_vObjectStates.m_pBlock[i - 1].m_ui8State = other->m_vObjectStates.m_pBlock[i - 1].m_ui8State;
    for (uint32_t i = 0; i < 2; ++i) m_aUnkEC[i] = other->m_aUnkEC[i];
    for (uint32_t i = 0; i < 2; ++i) m_aUnkF4[i] = other->m_aUnkF4[i];
    for (uint32_t i = 0; i < 5; ++i) m_aUnkFC[i] = other->m_aUnkFC[i];
    for (uint32_t i = 0; i < 5; ++i) m_aUnk110[i] = other->m_aUnk110[i];
    for (uint32_t i = 0; i < 3; ++i) m_afUnk124[i] = other->m_afUnk124[i];  // lfs / stfs
    m_unk130 = other->m_unk130;
    for (int32_t i = 1; i >= 0; --i) {
        m_aUnkE4[i][2] = other->m_aUnkE4[i][2];
        m_aUnkE4[i][1] = other->m_aUnkE4[i][1];
        m_aUnkE4[i][0] = other->m_aUnkE4[i][0];
    }
    m_unkEA = other->m_unkEA;
    m_unkEB = other->m_unkEB;
    m_aUnk1CA[0] = other->m_aUnk1CA[0];
    for (uint32_t i = 0; i < 6; ++i) m_aUnk1C4[i] = other->m_aUnk1C4[i];
    for (uint32_t k = 0; k < 12; ++k) {
        TVector<uint8_t, 8>& list = m_avbUnk134[k];
        for (uint32_t i = list.m_ui32NbUsedElt; i != 0; --i) list.m_pBlock[i - 1] = other->m_avbUnk134[k].m_pBlock[i - 1];
    }
    for (uint32_t i = 1; i <= 0x12; ++i) m_aUnk1CA[i] = other->m_aUnk1CA[i];
}

// 0x0050af70 CKS08GameState_vfC0
uint8_t CKS08GameState::SavesSpawnPoint() { return g_pEngine->m_gameManager->VfC4() == 0 ? 1 : 0; }

// 0x0050ed60 CKS08GameStructure_SaveCheckpointSnapshot_maybe
void CKS08GameStructure::SaveCheckpointSnapshot() {
    SetRtWord(0x1f0, m_unk4c);
    SetRtWord(0x1f4, m_unk54);
    SetRtWord(0x1f8, m_unk64);
    SetRtWord(0x1fc, m_unk6c);
    SetRtWord(0x200, m_unk74);
    SetRtWord(0x204, m_unk78);
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

// 0x0050f288 AddDragonPlayTime_maybe
void AddDragonPlayTime(IKSerializable* structure, uint32_t index, float dt) { AddRtFloat(structure, 0x144u + index * 4u, dt); }

// 0x0050f2a8 AddPlayerSlotPlayTime_maybe
void AddPlayerSlotPlayTime(IKSerializable* structure, uint32_t index, float dt) {
    AddRtFloat(structure, 0x14cu + index * 4u, dt);
}
