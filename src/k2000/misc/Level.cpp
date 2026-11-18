// Reconstructed original translation unit: 0x506ba8-0x506e00 (GAME_TOC1, main_toc1), 1 functions, 1 live.
// Primary owner: Level (not a registered class)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x506ba8  Level_GetMainLevelIndex  (C2.8 menus-load; declared in CKS08GameStructure.h)
#include "Spyro2008/logic/CKS08GameStructure.h"
#include "k2000/logic/CKGameLevel.h"

// 0x00506ba8 Level_GetMainLevelIndex: the main level's index (0..11) of a level number (+0x1c: 10, 20, ... 120), 99
// otherwise (the jump table over 10..120; li 0x63 & 0x6f).
int32_t Level_GetMainLevelIndex(const CKGameLevel* level) {
    const uint32_t number = static_cast<uint32_t>(level->m_i32StageIndex) - 10u;
    if (number > 0x6e || number % 10u != 0) return 99;
    return static_cast<int32_t>(number / 10u);
}
