// IKFxData.cpp - reconstructed original translation unit 0x1d8348-0x1d84f0 (GAME_TOC1, main_toc1), 2 functions, 2 live.
// Primary owner: IKFxData (not a registered class)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1d8348  IKFxData_Load
//   [ ] 0x1d8418  IKFxData_Save
//
//   [x] 0x9ab3a8  IKFxData_GetTypeIndex  [inline]
//   [x] 0x9ad898  IKFxData_IsKindOf  [inline]
//   [ ] 0x9ad8c0  IKFxData_GetClassGroup  [inline]
//   [ ] 0x9ad8c8  IKFxData_GetClassId  [inline]
//   [ ] 0x9ad8d0  IKFxData_DeletingDestructor  [inline]
//   [ ] 0x9ad918  IKFxData_Destructor  [inline]
#include "k2000/logic/IKFxData.h"

#include "k2000/io/IKFile.h"

// 0x001d8348 IKFxData_Load
int32_t IKFxData::Load(IKFile* file, int32_t type) {
    if (type == K_LEVEL_PLATEFORMS) {
        // The first word is swapped into a stack word and dropped: 0x02a4ca65 in every record (the
        // constant IKFxData_Save writes first; XXL-Editor asserts it too).
        uint32_t magic = 0;
        ReadU32LE(file, &magic);
        ReadU32LE(file, &m_typeIndex);
    }
    return 1;
}
