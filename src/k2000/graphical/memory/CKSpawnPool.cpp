// CKSpawnPool.cpp - reconstructed original translation unit 0xb6bd8-0xb7b00 (GAME_TOC1, main_toc1), 16 functions, 15 live.
// Primary class: CKSpawnPool  key 0xbcd  category Graphical  size 0x30  vtable 0xb17910
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0xb6bd8  RegisterCKSpawnPoolClass
//   [ ] 0xb6c50  _GLOBAL__I_b6c50
//   [ ] 0xb6c60  CKSpawnPool_ClearReferences_2  [dead]
//   [ ] 0xb6d00  CKSpawnPool_AcquireAnimSlot_maybe
//   [x] 0xb6dd0  CKSpawnPool_DeleteArray
//   [x] 0xb6e78  CKSpawnPool_Create
//   [x] 0xb6ed8  CKSpawnPool_StartSlotShakeCache_maybe
//   [ ] 0xb6f48  CKSpawnPool_UpdateAnimSlot_maybe
//   [x] 0xb70e8  CKSpawnPool_StopAllShakeCaches_maybe
//   [ ] 0xb7160  CKSpawnPool_RecursiveRegistration
//   [x] 0xb73a8  CKSpawnPool_CreateArray
//   [ ] 0xb7470  CKSpawnPool_Save
//   [ ] 0xb7478  CKSpawnPool_MessageProc
//   [ ] 0xb7480  CKSpawnPool_PostLoad
//   [x] 0xb7518  CKSpawnPool_Load
//   [ ] 0xb7a60  CKSpawnPool_Destroy
//
//   [ ] 0x9a0ef8  CKSpawnPool_GetClassType  [inline]
//   [ ] 0x9a0f00  CKSpawnPool_GetClassID  [inline]
//   [ ] 0x9a0f08  CKSpawnPool_IsKindOfClass  [inline]
//   [ ] 0x9a0f28  CKSpawnPool_Destruct  [inline]
//   [ ] 0x9a0fa0  CKSpawnPool_DeletingDestruct  [inline]
#include "k2000/graphical/memory/CKSpawnPool.h"

#include "k2000/graphical/memory/CKSpawnPoolParams.h"
#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"
#include "k2000/scenegraph/CAnimatedNode.h"

namespace {
// The inlined vector load: a count, then (when non-zero) the block sized to it and the references.
void LoadRefVector(IKFile* file, IKSerializable*** block, uint32_t* capacity, uint32_t* size) {
    uint32_t count = 0;
    ReadU32LE(file, &count);
    if (count == 0) return;
    *capacity = count;
    *block = static_cast<IKSerializable**>(Mem_AllocAligned16(count * sizeof(IKSerializable*)));
    // (The growth path, Mem_ReallocAligned16 when the capacity is below the count, cannot run.)
    *size = count;
    IKFile_ReadObjectRefArray(file, *block, count);
}
}  // namespace

// 0x000b7518 CKSpawnPool_Load
int32_t CKSpawnPool::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    LoadRefVector(file, &m_apSpawnPoolParams, &m_ui32ParamsCapacity, &m_ui32NbSpawnPoolParams);
    LoadRefVector(file, &m_apRenderParams, &m_ui32RenderParamsCapacity, &m_ui32NbRenderParams);
    ReadU32LE(file, &m_unk08);
    IKFile_ReadRef(file, &m_pNode);
    ReadU32LE(file, &m_ui32NumHierarchy);
    if (m_ui32NumHierarchy == 0) {
        m_asRpHAnimHierarchy = nullptr;
        return 1;
    }
    m_asRpHAnimHierarchy = static_cast<SAnimHierarchy*>(Mem_AllocAligned16(m_ui32NumHierarchy * sizeof(SAnimHierarchy)));
    uint32_t i = 0;
    do {
        SAnimHierarchy* entry = &m_asRpHAnimHierarchy[i];
        IKFile_ReadBoneFrameList(file, K_LEVEL_PLATEFORMS, &entry->m_pRootFrame, &entry->m_pRpHAnimHierarchy, nullptr);
        entry->m_unk0c = 0;
        IKFile_ReadRef(file, &entry->m_pController);
        ReadU32LE(file, &entry->m_unk20);
        ++i;
    } while (i < m_ui32NumHierarchy);
    return 1;
}

// 0x000b70e8 CKSpawnPool_StopAllShakeCaches_maybe
void CKSpawnPool::StopAllShakeCaches() {
    for (uint32_t i = 0; i < m_ui32NbSpawnPoolParams; ++i) {
        if (m_apSpawnPoolParams[i] != nullptr) static_cast<CKSpawnPoolParams*>(m_apSpawnPoolParams[i])->StopAllShakes();
    }
}

// 0x000b6ed8 CKSpawnPool_StartSlotShakeCache_maybe
void CKSpawnPool::StartSlotShakeCache(int32_t slot) {
    CKSpawnPoolParams* params = static_cast<CKSpawnPoolParams*>(m_apSpawnPoolParams[slot]);
    if (params != nullptr && (params->m_unk04 & 2) != 0) params->StartAllShakes();
}
