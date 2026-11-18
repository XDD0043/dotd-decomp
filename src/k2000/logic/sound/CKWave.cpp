// CKWave.cpp - reconstructed original translation unit 0x1225b0-0x122a50 (GAME_TOC1, main_toc1), 11 functions, 9 live.
// Primary class: CKWave  key 0x50cc  category Logic  size 0x10  vtable 0xb19ac8
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1225b0  CKWave_Delete
//   [ ] 0x122600  CKWave_Construct  [dead]
//   [ ] 0x122618  CKWave_Construct_2  [dead]
//   [x] 0x122630  CKWave_RecursiveRegistration
//   [ ] 0x122690  RegisterCKWaveClass
//   [ ] 0x122708  _GLOBAL__I_122708
//   [x] 0x122718  CKWave_DeleteArray
//   [x] 0x1227b8  CKWave_Create
//   [x] 0x1227f8  CKWave_CreateArray
//   [ ] 0x122898  CKWave_Save
//   [x] 0x122970  CKWave_Load
//
//   [ ] 0x9a6df0  CKWave_GetClassType  [inline]
//   [ ] 0x9a6df8  CKWave_GetClassID  [inline]
//   [x] 0x9a6e00  CKWave_Destructor  [inline]
//   [ ] 0x9a6e18  CKWave_IsKindOfClass  [inline]
//   [x] 0x9a6e38  CKWave_DeletingDestructor  [inline]
#include "k2000/logic/sound/CKWave.h"

#include "k2000/io/IKFile.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/misc/Engine.h"

// 0x001227b8 CKWave_Create (the constructor is inlined there; 0x122600 CKWave_Construct is dead)
CKWave::CKWave() { m_pRwaWave = nullptr; }

// 0x00122630 CKWave_RecursiveRegistration
void CKWave::RecursiveRegistration(int32_t type) {
    if (type == 0) g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);  // vt+0x24
}

// 0x00122970 CKWave_Load
int32_t CKWave::Load(IKFile* file, int32_t type) {
    if (type == K_LEVEL_PLATEFORMS) {
        ReadF32LE(file, &m_fLength);
        ReadU16LE(file, &m_ui16SampleRate);
    }
    return 1;
}
