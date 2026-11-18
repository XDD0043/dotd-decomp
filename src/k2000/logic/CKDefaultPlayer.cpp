// CKDefaultPlayer.cpp - reconstructed original translation unit 0x1a0d8-0x1a468 (GAME_TOC1, main_toc1), 5 functions, 5 live.
// Primary class: CKDefaultPlayer  key 0x184c  category Logic  size 0x14  vtable 0xb13830
// Other owners: IKPlayer (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1a0d8  CKDefaultPlayer_vf58
//   [x] 0x1a120  CKDefaultPlayer_vf54Impl
//   [x] 0x1a140  CKDefaultPlayer_LevelResetImpl
//   [x] 0x1a220  CKDefaultPlayer_vf50Impl
//   [x] 0x1a290  IKPlayer_Load
//
//   [x] 0x9927d8  IKPlayer_vf14  [inline]
//   [x] 0x9927e0  IKPlayer_vf18  [inline]
//   [x] 0x9927e8  IKPlayer_GetSerializationFlags  [inline]
//   [ ] 0x9927f0  IKPlayer_vf5C  [inline]
//   [ ] 0x992800  IKPlayer_vf64  [inline]
//   [ ] 0x992808  IKPlayer_vf68  [inline]
//   [ ] 0x992810  IKPlayer_vf6C  [inline]
//   [ ] 0x992818  IKPlayer_vf74  [inline]
//   [ ] 0x992820  IKPlayer_vf78  [inline]
//   [ ] 0x992828  IKPlayer_vf7C  [inline]
//   [ ] 0x992830  IKPlayer_DeletingDestructor  [inline]
//   [ ] 0x992870  IKPlayer_vf70  [inline]
//   [ ] 0x992878  IKPlayer_vf8  [inline]
//   [ ] 0x992898  IKPlayer_vf0  [inline]
#include "k2000/logic/IKPlayer.h"

#include "k2000/io/IKFile.h"
#include "k2000/logic/CKGameState.h"

// 0x0001a290 IKPlayer_Load. XXL2 reads the game state in K_GAME_MEMCARD too; DotD reads +0x10 there.
int32_t IKPlayer::Load(IKFile* file, int32_t type) {
    if (type == K_GAME_PLATEFORMS) {
        IKFile_ReadRef(file, &m_pGameState);
        return 1;
    }
    if (type != K_GAME_MEMCARD) return 1;
    ReadU32LE(file, &m_baLevelSaved);
    ReadU8(file, &m_bUsed);
    ReadU32LE(file, &m_unk10);
    return 1;
}

// 0x0001a0d8 CKDefaultPlayer_vf58 (IKPlayer's vt+0x58; XXL2 IKPlayer::CopyGameStructure)
void IKPlayer::CopyGameStructure() { m_pGameState->CopyFromStructure(); }

// 0x0001a120 CKDefaultPlayer_vf54Impl (XXL2 CKDefaultPlayer::InitializeNewGame)
void IKPlayer::InitializeNewGameImpl() {
    m_unk09 = 0;
    m_unk10 = 0;
    m_baLevelSaved = 0;
    m_bUsed = 0;
}

// 0x0001a220 CKDefaultPlayer_vf50Impl (XXL2 CKDefaultPlayer::CopyPlayerGameData): +0x04, the game state
// (vt+0x7c with the other's), +0x10 (lfs / stfs).
void IKPlayer::CopyPlayerGameDataImpl(IKPlayer* other) {
    m_baLevelSaved = other->m_baLevelSaved;
    m_pGameState->CopyFromState(other->m_pGameState);
    m_unk10 = other->m_unk10;
}

// 0x0001a140 CKDefaultPlayer_LevelResetImpl (C2.8 save-menu)
#include "k2000/logic/CKSavingManager.h"
#include "k2000/misc/Engine.h"
int32_t IKPlayer::LevelResetImpl(int32_t type) {
    IKSerializable* object = this;
    if (type == K_GAME_MEMCARD) {
        g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);  // vt+0x24
        object = static_cast<IKSerializable*>(m_pGameState);
    } else if (!(type == 0 || type == 1 || type == K_LEVEL_MEMCARD)) {
        return 1;
    }
    g_pEngine->m_pSavingManager->RegisterSerializableObject(object, nullptr);
    return 1;
}
