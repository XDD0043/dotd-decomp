// IKGrpEnemy.cpp - reconstructed original translation unit 0x2665a0-0x266d20 (GAME_TOC1, main_toc1), 2 functions, 2 live.
// Primary owner: IKGrpEnemy (not a registered class)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x2665a0  IKGrpEnemy_IsAnyEnemyInCone_maybe
//   [x] 0x2667e0  IKGrpEnemy_Load
#include "k2000/misc/IKGrpEnemy.h"

#include "k2000/groups/TVectorPush.h"
#include "k2000/io/IKFile.h"

namespace {
// The vector read IKGrpEnemy_Load inlines three times: the count, the resize (TVector_ResizeForLoad),
// then each reference read into slot i.
void LoadRefVector(TVector<IKSerializable*, 1>& vector, IKFile* file) {
    uint32_t count = 0;
    ReadU32LE(file, &count);
    TVector_ResizeForLoad(vector, count);
    if (count == 0) return;
    for (uint32_t i = 0; i < count; ++i) IKFile_ReadRef(file, &vector.m_pBlock[i]);
}
}  // namespace

// 0x002667e0 IKGrpEnemy_Load
int32_t IKGrpEnemy::Load(IKFile* file, int32_t type) {
    GroupBasicLoad(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    LoadRefVector(m_vUnk4c, file);
    IKFile_ReadRef(file, &m_pPoolGrpRoot);
    LoadRefVector(m_vpFZSectorGrpRoot, file);
    LoadRefVector(m_vUnk40, file);
    return 1;
}
