// CKSpawnPoolParams.cpp - reconstructed original translation unit 0xb7b00-0xb8d50 (GAME_TOC1, main_toc1), 23 functions, 19 live.
// Primary class: CKSpawnPoolParams  key 0x60d  category Graphical  size 0x20  vtable 0xb17968
// Other owners: ShakeMatrixCache (4)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0xb7b00  CKSpawnPoolParams_Delete
//   [ ] 0xb7b50  CKSpawnPoolParams_Construct  [dead]
//   [ ] 0xb7b70  KStub_Nop_b7b70
//   [ ] 0xb7b78  CKSpawnPoolParams_NextIndex_maybe
//   [ ] 0xb7bd0  CKSpawnPoolParams_Construct_2  [dead]
//   [ ] 0xb7bf0  RegisterCKSpawnPoolParamsClass
//   [ ] 0xb7c68  _GLOBAL__I_b7c68
//   [x] 0xb7c78  ShakeMatrixCache_StopAll_maybe
//   [x] 0xb7d58  ShakeMatrixCache_Start_maybe
//   [ ] 0xb7f40  ShakeMatrixCache_UpdateEntry_maybe
//   [x] 0xb81c8  CKSpawnPoolParams_DeleteArray
//   [ ] 0xb8268  ShakeMatrixCache_GetMatrix_maybe
//   [ ] 0xb8300  CKSpawnPoolParams_RecursiveRegistration
//   [x] 0xb8440  CKSpawnPoolParams_CreateArray
//   [x] 0xb84f0  CKSpawnPoolParams_Create
//   [ ] 0xb8540  CKSpawnPoolParams_PostLoad
//   [ ] 0xb8548  CKSpawnPoolParams_Destroy
//   [ ] 0xb85f8  CKSpawnPoolParams_Destructor
//   [x] 0xb8660  CKSpawnPoolParams_Load
//   [ ] 0xb8930  CKSpawnPoolParams_Save
//   [ ] 0xb8b38  CKSpawnPoolParams_SetShakeActive_maybe  [dead]
//   [ ] 0xb8c68  CKSpawnPoolParams_Destructor_2  [dead]
//   [ ] 0xb8cd0  CKSpawnPoolParams_DeletingDestructor
//
//   [ ] 0x9a1030  CKSpawnPoolParams_GetClassType  [inline]
//   [ ] 0x9a1038  CKSpawnPoolParams_GetClassID  [inline]
//   [ ] 0x9a1040  CKSpawnPoolParams_IsKindOfClass  [inline]
#include "k2000/graphical/memory/CKSpawnPoolParams.h"

#include "k2000/components/CKQuakeCpntUpdater.h"
#include "k2000/core/Stub.h"
#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/Mat4.h"

// 0x000b8660 CKSpawnPoolParams_Load
int32_t CKSpawnPoolParams::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    IKFile_ReadRef(file, &m_pUnk08);
    ReadU32LE(file, &m_unk04);
    m_ui32NbActiveMatrix = 0;
    m_ui32NbNextActiveMatrix = 0;
    uint32_t count = 0;
    ReadU32LE(file, &count);
    if (count == 0) {
        m_ui32Capacity = 1;
        m_vsMatrixData = static_cast<SMatrixData*>(Mem_AllocAligned16(sizeof(SMatrixData)));
    } else {
        m_ui32Capacity = count;
        m_vsMatrixData = static_cast<SMatrixData*>(Mem_AllocAligned16(count * sizeof(SMatrixData)));
        // (The growth path, Mem_ReallocAligned16 when the capacity is below the count, cannot run.)
        m_ui32NbMatrixData = count;
    }
    for (uint32_t i = 0; i < count; ++i) {
        SMatrixData* entry = &m_vsMatrixData[i];
        entry->m_pMatrix = RwMatrixCreate_Thunk();
        entry->m_ui16Id = 0xffff;
        IKFile_ReadRef(file, &entry->m_pObject);
        ++m_ui32NbActiveMatrix;
    }
    return 1;
}

// 0x000b7c78 ShakeMatrixCache_StopAll_maybe
void CKSpawnPoolParams::StopAllShakes() {
    for (uint32_t i = 0; i < m_ui32NbActiveMatrix; ++i) {
        CMatrix34* matrix = m_vsMatrixData[i].m_pMatrix;
        matrix->m_ui32Flags = 0x20003;
        matrix->m_right = {1.0f, 0.0f, 0.0f};
        matrix->m_up = {0.0f, 1.0f, 0.0f};
        matrix->m_at = {0.0f, 0.0f, 1.0f};
        matrix->m_pos = {0.0f, 0.0f, 0.0f};
        static_cast<CKQuakeCpntUpdater*>(m_vsMatrixData[i].m_pObject)->Stop();  // CKQuakeCpntUpdater_Stop 0x24f738
    }
}

// 0x000b7d58 ShakeMatrixCache_Start_maybe, slot -1. Without flag 4 every matrix is active; with it only the first,
// reset to the identity like StopAllShakes' (the pads kept).
void CKSpawnPoolParams::StartAllShakes() {
    if ((m_unk04 & 4) == 0) {
        m_ui32NbActiveMatrix = m_ui32NbMatrixData;
    } else {
        m_ui32NbActiveMatrix = 1;
        CMatrix34* matrix = m_vsMatrixData[0].m_pMatrix;
        matrix->m_ui32Flags = 0x20003;
        matrix->m_right = {1.0f, 0.0f, 0.0f};
        matrix->m_up = {0.0f, 1.0f, 0.0f};
        matrix->m_at = {0.0f, 0.0f, 1.0f};
        matrix->m_pos = {0.0f, 0.0f, 0.0f};
        static_cast<CKQuakeCpntUpdater*>(m_vsMatrixData[0].m_pObject)->Start();  // CKQuakeCpntUpdater_Start 0x24f770
    }
    for (uint32_t i = 0; i < m_ui32NbActiveMatrix; ++i) {
        static_cast<CKQuakeCpntUpdater*>(m_vsMatrixData[i].m_pObject)->Start();
    }
}
