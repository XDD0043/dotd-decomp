// CKS08GameLevel.cpp - reconstructed original translation unit 0x506e00-0x507d58 (GAME_TOC1, main_toc1), 24 functions, 23 live.
// Primary class: CKS08GameLevel  key 0x788c  category Logic  size 0x9c  vtable 0xb2b348
// Other owners: CountStatEntriesByCategory (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x506e00  RegisterCKS08GameLevelClass
//   [ ] 0x506e78  _GLOBAL__I_506e78
//   [ ] 0x506e88  CKS08GameLevel_ClearGameData_maybe
//   [x] 0x506ef8  CKS08GameLevel_InitLevelData
//   [x] 0x506f30  CKS08GameLevel_vf58
//   [ ] 0x506f90  CKS08GameLevel_PostLoad
//   [ ] 0x506fb8  CKS08GameLevel_Save
//   [ ] 0x506fe0  CKS08GameLevel_Destroy
//   [x] 0x507008  CKS08GameLevel_Construct
//   [ ] 0x507070  CKS08GameLevel_Construct_2
//   [x] 0x5070d8  CKS08GameLevel_DeleteArray
//   [x] 0x507178  CountStatEntriesByCategory
//   [x] 0x507230  CKS08GameLevel_vf68
//   [ ] 0x5072e0  CKS08GameLevel_RecursiveRegistration
//   [ ] 0x5073a0  CKS08GameLevel_IsArmorPieceCollected_maybe
//   [ ] 0x507440  CKS08GameLevel_CountCollectedOfType_maybe
//   [ ] 0x5074b0  CKS08GameLevel_CountEntriesByFlagBit0_maybe  [dead]
//   [x] 0x507530  CKS08GameLevel_ClearLevelData_maybe
//   [x] 0x5075e8  CKS08GameLevel_Load
//   [x] 0x507888  CKS08GameLevel_CreateArray
//   [x] 0x507980  CKS08GameLevel_Create
//   [ ] 0x5079f8  CKS08GameLevel_Destructor_2
//   [ ] 0x507b18  CKS08GameLevel_DeletingDestructor
//   [ ] 0x507c38  CKS08GameLevel_Destructor
//
//   [ ] 0x9c7070  CKS08GameLevel_IsKindOfClass  [inline]
//   [x] 0x9c70a8  CKS08GameLevel_GetClassType  [inline]
//   [x] 0x9c70b0  CKS08GameLevel_GetClassID  [inline]
#include "Spyro2008/logic/CKS08GameLevel.h"

#include "k2000/io/IKFile.h"
#include "k2000/logic/GameVector.h"

// 0x00507008 CKS08GameLevel_Construct (CKS08GameLevel_Create 0x507980 inlines the same)
CKS08GameLevel::CKS08GameLevel() {
    m_vpCollectibles.m_pBlock = nullptr;
    m_vpCollectibles.m_ui32NbElt = 8;
    m_vpCollectibles.m_ui32NbUsedElt = 0;
    m_ui32NbLocalCollectibles = 0;
    m_ui32NbGlobalCollectibles = 0;
}

// 0x00506ef8 CKS08GameLevel_InitLevelData
void CKS08GameLevel::InitializeLevelData() {
    CKGameLevel::InitializeLevelData();
    m_ui32NbLocalCollectibles = 0;
}

// 0x00506f30 CKS08GameLevel_vf58 (InitializeGameData). The old block is not freed.
void CKS08GameLevel::InitializeGameData() {
    CKGameLevel::InitializeGameData();
    GameVector_Reserve(&m_vpCollectibles);
    m_ui32NbGlobalCollectibles = 0;
}

// 0x00507530 CKS08GameLevel_ClearLevelData_maybe
void CKS08GameLevel::DestroyLevelData() {
    for (uint32_t i = m_vpCollectibles.m_ui32NbUsedElt; i != 0; --i) {
        CKS08GameLevelCollectible** entry = &m_vpCollectibles.m_pBlock[i - 1];
        if (IKGameObject_IsGameEntry(reinterpret_cast<IKSerializable*>(*entry))) continue;  // single inheritance
        const uint32_t last = --m_vpCollectibles.m_ui32NbUsedElt;
        if (i - 1 != last) *entry = m_vpCollectibles.m_pBlock[last];
        --m_ui32NbLocalCollectibles;
    }
    CKGameLevel::DestroyLevelData();  // 0x3a3e0
}

// 0x005075e8 CKS08GameLevel_Load
int32_t CKS08GameLevel::Load(IKFile* file, int32_t type) {
    CKGameLevel::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        ReadU32LE(file, &m_ui32NbLocalCollectibles);
        if (m_ui32NbLocalCollectibles == 0) return 1;
        GameVector_Resize(&m_vpCollectibles, m_ui32NbLocalCollectibles + m_ui32NbGlobalCollectibles);
        IKFile_ReadObjectRefArray(file,
                                  reinterpret_cast<IKSerializable**>(m_vpCollectibles.m_pBlock + m_ui32NbGlobalCollectibles),
                                  m_ui32NbLocalCollectibles);
        return 1;
    }
    if (type != kGameStructureBlock) return 1;
    ReadU32LE(file, &m_ui32NbGlobalCollectibles);
    if (m_ui32NbGlobalCollectibles == 0) return 1;
    GameVector_Resize(&m_vpCollectibles, m_ui32NbGlobalCollectibles);
    IKFile_ReadObjectRefArray(file, reinterpret_cast<IKSerializable**>(m_vpCollectibles.m_pBlock),
                              m_ui32NbGlobalCollectibles);
    return 1;
}

#include "Spyro2008/logic/CKS08GameLevelCollectible.h"

// 0x00507230 CKS08GameLevel_vf68
void CKS08GameLevel::ApplyGameStateToLevel() {
    CKGameLevel::ApplyGameStateToLevel();
    for (uint32_t i = m_vpCollectibles.m_ui32NbUsedElt; i != 0; --i)
        static_cast<IKGameObject*>(m_vpCollectibles.m_pBlock[i - 1])->ApplyGameStateToLevel();
}

// 0x00507178 CountStatEntriesByCategory: the level's collectibles of one category (byte +0x1d), counting
// only the ones with their flag (+0x1c) set when requireFlag is non-zero.
uint32_t CountStatEntriesByCategory(CKS08GameLevel* level, uint8_t category, int32_t requireFlag) {
    uint32_t count = 0;
    for (uint32_t i = 0; i < level->m_vpCollectibles.m_ui32NbUsedElt; ++i) {
        const CKS08GameLevelCollectible* entry = level->m_vpCollectibles.m_pBlock[i];
        if (entry->m_unk1d != category) continue;
        if (requireFlag != 0 && entry->m_unk1c == 0) continue;
        ++count;
    }
    return count;
}
