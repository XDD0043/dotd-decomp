// CKPxMesh.cpp - reconstructed original translation unit 0x22c4b8-0x22cba8 (GAME_TOC1, main_toc1), 17 functions, 16 live.
// Primary class: CKPxMesh  key 0x470c  category Logic  size 0x2c  vtable 0xb20310
// Other owners: CKPxShape (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x22c4b8  CKPxMesh_Delete  (the registry factory: DOTD_DECLARE_FACTORIES)
//   [ ] 0x22c508  RegisterCKPxMeshClass
//   [ ] 0x22c580  _GLOBAL__I_22c580
//   [ ] 0x22c590  CKPxMesh_Save
//   [x] 0x22c5b8  CKPxMesh_RecursiveRegistration  (KBase468C's vf24 0x218068: returns 1)
//   [x] 0x22c5e0  CKPxMesh_Destroy
//   [x] 0x22c650  CKPxMesh_DeletingDestructor  (the destructor; delete)
//   [x] 0x22c698  CKPxMesh_Destructor  (C++ destructor chain: vtable stores only)
//   [x] 0x22c6c8  CKPxMesh_DestructBody  (C++ destructor chain: vtable stores only)
//   [x] 0x22c6f8  CKPxMesh_Construct  (header)
//   [x] 0x22c730  CKPxMesh_Construct_2  (the constructor's second C++ variant)
//   [x] 0x22c768  CKPxMesh_DeleteArray  (the registry factory: DOTD_DECLARE_FACTORIES)
//   [x] 0x22c808  CKPxMesh_Load
//   [x] 0x22ca90  CKPxMesh_Create  (the registry factory: DOTD_DECLARE_FACTORIES)
//   [x] 0x22cae8  CKPxMesh_CreateArray  (the registry factory: DOTD_DECLARE_FACTORIES)
//   [x] 0x22cb98  CKPxShape_474c_maybe_GetOwnerBody_maybe  (KBase468C::GetOwnerBody (k2000/misc/KBase468C.h))
//   [ ] 0x22cba0  FUN_0022cba0  [dead]
//
//   [ ] 0x9b4f08  CKPxMesh_IsKindOfClass  [inline]
//   [ ] 0x9b4f30  CKPxMesh_GetClassType  [inline]
//   [ ] 0x9b4f38  CKPxMesh_GetClassID  [inline]
#include "k2000/logic/render/CKPxMesh.h"

#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"

// 0x0022c808 CKPxMesh_Load: each block one Read, then swapped in place (lwbrx words, lhbrx halfwords).
int32_t CKPxMesh::Load(IKFile* file, int32_t type) {
    KBase468C::Load(file, type);  // 0x00218078
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadRaw(file, &m_unk18, 1);
    ReadU16LE(file, &m_ui16NbVertex);
    m_pVertices = nullptr;
    if (m_ui16NbVertex != 0) {
        const uint32_t words = static_cast<uint32_t>(m_ui16NbVertex) * 3;
        m_pVertices = static_cast<float*>(Mem_AllocAligned16(words * 4));
        ReadU32LEWords(file, reinterpret_cast<uint32_t*>(m_pVertices), words);
    }
    ReadU16LE(file, &m_ui16NbRecord);
    m_pRecords = nullptr;
    if (m_ui16NbRecord != 0) {
        const uint32_t halves = static_cast<uint32_t>(m_ui16NbRecord) * 4;
        m_pRecords = static_cast<uint16_t*>(Mem_AllocAligned16(halves * 2));
        for (uint32_t i = 0; i < halves; ++i) ReadU16LE(file, &m_pRecords[i]);  // one Read in the original
    }
    return 1;
}

// 0x0022c5e0 CKPxMesh_Destroy (CKPxObject_ClearReferences_BaseNop_maybe last)
void CKPxMesh::Destroy() {
    if (m_pVertices != nullptr) Mem_FreeAligned16(m_pVertices);
    if (m_pRecords != nullptr) Mem_FreeAligned16(m_pRecords);
    KBase468C::Destroy();
}
