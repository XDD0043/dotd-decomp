// CMultiGeometryBasic.cpp - reconstructed original translation unit 0x245038-0x245bb8 (GAME_TOC1, main_toc1), 12 functions, 12 live.
// Primary class: CMultiGeometryBasic  key 0x314c  category Logic  size 0x20  vtable 0xb20c80
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x245038  CMultiGeometryBasic_Delete
//   [x] 0x245088  CMultiGeometryBasic_RecursiveRegistration  (CMultiGeometryBasic.h)
//   [ ] 0x2450e8  RegisterCMultiGeometryBasicClass
//   [ ] 0x245160  _GLOBAL__I_245160
//   [x] 0x245170  CMultiGeometryBasic_DeleteArray
//   [x] 0x245210  CMultiGeometryBasic_Create
//   [x] 0x245248  CMultiGeometryBasic_CreateArray
//   [x] 0x2452d8  CMultiGeometryBasic_Destroy  (empty)
//   [x] 0x2452e0  CMultiGeometryBasic_LoadShape
//   [x] 0x2455c8  CMultiGeometryBasic_Load
//   [ ] 0x245650  CMultiGeometryBasic_SaveShape_maybe  [left: save-only: only CMultiGeometryBasic_Save calls it, and Save is left out]
//   [ ] 0x245b30  CMultiGeometryBasic_Save
//
//   [ ] 0x9b9d18  CMultiGeometryBasic_GetClassType  [inline]
//   [ ] 0x9b9d20  CMultiGeometryBasic_GetClassID  [inline]
//   [ ] 0x9b9d28  CMultiGeometryBasic_Destructor  [inline]
//   [ ] 0x9b9d40  CMultiGeometryBasic_IsKindOfClass  [inline]
//   [ ] 0x9b9d60  CMultiGeometryBasic_DeletingDestructor  [inline]
#include "k2000/logic/CMultiGeometryBasic.h"

#include "k2000/io/IKFile.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/misc/Engine.h"

// 0x002452e0 CMultiGeometryBasic_LoadShape
void CMultiGeometryBasic::LoadShape(IKFile* file) {
    const uint8_t shape = m_baData & 3;
    if (shape == 1) {
        ReadU32LEWords(file, reinterpret_cast<uint32_t*>(m_afShape), 5);
        return;
    }
    if (shape != 2) {
        if (shape != 0) return;
        ReadU32LEWords(file, reinterpret_cast<uint32_t*>(m_afShape), 6);
        return;
    }
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(m_afShape), 5);
    ReadRaw(file, &m_ui8ShapeByte, 1);
}

// 0x002455c8 CMultiGeometryBasic_Load
int32_t CMultiGeometryBasic::Load(IKFile* file, int32_t type) {
    if (type == K_LEVEL_PLATEFORMS) {
        ReadRaw(file, &m_baData, 1);
        LoadShape(file);
    }
    return 1;
}

// 0x00245088 CMultiGeometryBasic_RecursiveRegistration (also CMultiGeometry's 0x1aa6d0)
void CMultiGeometryBasic::RecursiveRegistration(int32_t type) {
    if (type == 0) g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);  // vt+0x24
}
