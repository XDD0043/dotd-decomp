// CSpawnManager.cpp - reconstructed original translation unit 0xb8d50-0xb9fd0 (GAME_TOC1, main_toc1), 27 functions, 23 live.
// Primary class: CSpawnManager  key 0xb8d  category Graphical  size 0x44  vtable 0xb179c0
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0xb8d50  CSpawnManager_Delete  (DOTD_DECLARE_FACTORIES)
//   [ ] 0xb8da0  CSpawnManager_Construct  [dead]
//   [x] 0xb8e00  CSpawnManager_vf70  (CanBeUpdated)
//   [x] 0xb8e20  KStub_Nop_b8e20  (CSpawnManager::PostSectorUnload, CSpawnManager.h)
//   [ ] 0xb8e28  CSpawnManager_Construct_2  [dead]
//   [ ] 0xb8e88  RegisterCSpawnManagerClass
//   [ ] 0xb8f00  _GLOBAL__I_b8f00
//   [ ] 0xb8f10  CSpawnManager_UpdateEntryDirections_maybe  [dead]
//   [x] 0xb90e8  CSpawnManager_Init_maybe
//   [ ] 0xb9178  CSpawnManager_Save
//   [x] 0xb91a0  CSpawnManager_RecursiveRegistration  (CSpawnManager.h)
//   [x] 0xb91c8  CSpawnManager_Update
//   [x] 0xb9270  CSpawnManager_Shutdown_maybe
//   [x] 0xb92c8  CSpawnManager_Destroy
//   [x] 0xb9320  CSpawnManager_DeleteArray  (DOTD_DECLARE_FACTORIES)
//   [x] 0xb93c8  CSpawnManager_StartPoolShakeCaches_maybe
//   [x] 0xb9448  CSpawnManager_StopAllShakeCaches_maybe
//   [x] 0xb94b8  CSpawnManager_CallNopHookOnEntries_maybe  (empty / no effect: inherited)
//   [x] 0xb9528  CSpawnManager_MessageProc  (CSpawnManager.h)
//   [x] 0xb9530  CSpawnManager_PostLoad  (CSpawnManager.h)
//   [x] 0xb9538  CSpawnManager_CreateArray  (DOTD_DECLARE_FACTORIES)
//   [x] 0xb9638  CSpawnManager_Create
//   [x] 0xb96c0  CSpawnManager_DeletingDestructor
//   [x] 0xb9780  CSpawnManager_Enqueue
//   [x] 0xb9978  CSpawnManager_Load
//   [x] 0xb9e70  CSpawnManager_Destructor
//   [ ] 0xb9f20  CSpawnManager_Destructor_2  [dead]
//
//   [x] 0x9a1060  CSpawnManager_IsKindOfClass  [inline]
//   [x] 0x9a1088  CSpawnManager_GetClassType  [inline]
//   [x] 0x9a1090  CSpawnManager_GetClassID  [inline]
//   [x] 0x9a1098  CSpawnManager_GetSerializationFlags  [inline]
//   [ ] 0x9a10a0  CSpawnManager_Draw  [inline]
#include "k2000/graphical/CSpawnManager.h"

#include <cmath>

#include "Renderware/rwcore/RwCamera.h"
#include "crt/ppc_ops.h"
#include "k2000/scenegraph/CSGMovable.h"

#include "k2000/graphical/memory/CKSpawnPool.h"
#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"
#include "k2000/managers/CKGraphic.h"
#include "k2000/misc/Engine.h"
#include "k2000/render/CRenderer.h"

namespace {
// The inlined resize of a reference vector that grows in steps of 2, then the references.
// The blocks exist from CSpawnManager_Init_maybe (capacity 2) on.
void LoadRefVector(TVector<IKSerializable*, 2>& vector, IKFile* file, uint32_t count) {
    if (vector.m_ui32NbElt < count) {
        uint32_t capacity = (count & ~1u) + 2;
        if (capacity == 0) capacity = 2;
        vector.m_pBlock = static_cast<IKSerializable**>(
            Mem_ReallocAligned16(vector.m_pBlock, capacity * static_cast<uint32_t>(sizeof(IKSerializable*))));
        vector.m_ui32NbElt = capacity;
    }
    vector.m_ui32NbUsedElt = count;
    IKFile_ReadObjectRefArray(file, vector.m_pBlock, count);
}
}  // namespace

// 0x000b9638 CSpawnManager_Create, in the original's store order; +0x0c, +0x18 and +0x1c are left as
// they are.
CSpawnManager::CSpawnManager() {
    m_pNextAccumulatedObject = nullptr;
    m_BitProperties = 0;
    m_pPriorityParent = 0;
    m_pLightSet = nullptr;
    m_vUnk20.m_ui32NbElt = 2;
    m_vUnk20.m_pBlock = nullptr;
    m_vUnk20.m_ui32NbUsedElt = 0;
    m_vpSpawnPoolParams.m_ui32NbElt = 2;
    m_vpSpawnPoolParams.m_pBlock = nullptr;
    m_vpSpawnPoolParams.m_ui32NbUsedElt = 0;
    m_vUnk38.m_ui32NbElt = 2;
    m_vUnk38.m_ui32NbUsedElt = 0;
    m_vUnk38.m_pBlock = nullptr;
}

// 0x000b90e8 CSpawnManager_Init_maybe (InitializeRendererStages, right after the creation): the three
// vectors get blocks of their capacity 2.
void CSpawnManager::Init() {
    m_vpSpawnPoolParams.m_ui32NbElt = 2;
    m_vpSpawnPoolParams.m_pBlock = static_cast<IKSerializable**>(Mem_AllocAligned16(2 * sizeof(IKSerializable*)));
    m_vUnk38.m_ui32NbElt = 2;
    m_vUnk38.m_pBlock = static_cast<IKSerializable**>(Mem_AllocAligned16(2 * sizeof(IKSerializable*)));
    m_vUnk20.m_ui32NbElt = 2;
    m_vUnk20.m_pBlock = static_cast<SEntry*>(Mem_AllocAligned16(2 * sizeof(SEntry)));  // 0x38
}

// 0x000b9270 CSpawnManager_Shutdown_maybe
void CSpawnManager::Shutdown() {
    if (m_vUnk20.m_pBlock != nullptr) {
        Mem_FreeAligned16(m_vUnk20.m_pBlock);
        m_vUnk20.m_pBlock = nullptr;
    }
    m_vUnk20.m_ui32NbUsedElt = 0;
    m_vUnk20.m_pBlock = nullptr;
}

// 0x000b9e70 CSpawnManager_Destructor: the three vectors' blocks freed (+0x38, +0x2c, then +0x20); only the first
// vector's length and block are cleared afterwards.
CSpawnManager::~CSpawnManager() {
    if (m_vUnk38.m_pBlock != nullptr) Mem_FreeAligned16(m_vUnk38.m_pBlock);
    if (m_vpSpawnPoolParams.m_pBlock != nullptr) Mem_FreeAligned16(m_vpSpawnPoolParams.m_pBlock);
    if (m_vUnk20.m_pBlock != nullptr) Mem_FreeAligned16(m_vUnk20.m_pBlock);
    m_vUnk20.m_ui32NbUsedElt = 0;
    m_vUnk20.m_pBlock = nullptr;
}

// 0x000b92c8 CSpawnManager_Destroy (the level unload): IRendableObject's, the pool array freed (the
// pointer is kept: BUG(original), the next Load replaces it), the three vectors emptied.
void CSpawnManager::Destroy() {
    IRendableObject::Destroy();  // 0xa7248
    if (m_apSpawnPool != nullptr) Mem_FreeAligned16(m_apSpawnPool);
    m_vUnk20.m_ui32NbUsedElt = 0;
    m_vpSpawnPoolParams.m_ui32NbUsedElt = 0;
    m_vUnk38.m_ui32NbUsedElt = 0;
}

// 0x000b9978 CSpawnManager_Load
int32_t CSpawnManager::Load(IKFile* file, int32_t type) {
    IRendableObject::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadU32LE(file, &m_ui32NbPool);
    if (m_ui32NbPool == 0) {
        m_apSpawnPool = nullptr;
    } else {
        m_apSpawnPool = static_cast<IKSerializable**>(
            Mem_AllocAligned16(m_ui32NbPool * static_cast<uint32_t>(sizeof(IKSerializable*))));
        IKFile_ReadObjectRefArray(file, m_apSpawnPool, m_ui32NbPool);
    }
    uint32_t count = 0;
    ReadU32LE(file, &count);
    if (count != 0) LoadRefVector(m_vpSpawnPoolParams, file, count);
    ReadU32LE(file, &count);
    if (count != 0) LoadRefVector(m_vUnk38, file, count);
    ReadU32LE(file, &count);
    if (count != 0) {
        if (m_vUnk20.m_ui32NbElt < count) {  // grows in steps of 2
            uint32_t capacity = (count & ~1u) + 2;
            if (capacity == 0) capacity = 2;
            m_vUnk20.m_pBlock = static_cast<SEntry*>(
                Mem_ReallocAligned16(m_vUnk20.m_pBlock, capacity * static_cast<uint32_t>(sizeof(SEntry))));
            m_vUnk20.m_ui32NbElt = capacity;
        }
        m_vUnk20.m_ui32NbUsedElt = count;
        for (uint32_t i = 0; i < count; ++i) IKFile_ReadRef(file, &m_vUnk20.m_pBlock[i].m_pObject);
    }
    m_BitProperties = (m_BitProperties & ~0x100u) | 0x100u;
    return 1;
}

// 0x000b93c8 CSpawnManager_StartPoolShakeCaches_maybe
void CSpawnManager::StartPoolShakeCaches(int32_t slot) {
    for (uint32_t i = 0; i < m_ui32NbPool; ++i) static_cast<CKSpawnPool*>(m_apSpawnPool[i])->StartSlotShakeCache(slot);
}

// 0x000b9448 CSpawnManager_StopAllShakeCaches_maybe
void CSpawnManager::StopAllShakeCaches() {
    for (uint32_t i = 0; i < m_ui32NbPool; ++i) static_cast<CKSpawnPool*>(m_apSpawnPool[i])->StopAllShakeCaches();
}

// 0x000b9780 CSpawnManager_Enqueue (C2.7 enemy family). The original reads the frame's stored LTM; natively
// RwFrameGetLTM makes it current (as CKHkDetectorGroup's hero position).
void CSpawnManager::UpdateAndExtract(float, RenderQueue**, IKTime*, RwCamera*, int32_t) {
    for (uint32_t i = 0; m_vUnk20.m_ui32NbUsedElt > i; ++i) {
        SEntry& entry = m_vUnk20.m_pBlock[i];
        const RwV3d& position = RwFrameGetLTM(static_cast<CSGMovable*>(entry.m_pObject)->m_pRwFrame)->pos;
        if ((m_BitProperties & 0x100u) != 0) {
            entry.m_vDir = CVector3{0.0f, 0.0f, 0.0f};  // the null vector 0x00c50d64
        } else {
            entry.m_vDir.y = position.y - entry.m_vPos.y;
            entry.m_vDir.x = position.x - entry.m_vPos.x;
            entry.m_vDir.z = position.z - entry.m_vPos.z;
            const float length = static_cast<float>(std::sqrt(static_cast<double>(ppc::fmadds(
                entry.m_vDir.z, entry.m_vDir.z, ppc::fmadds(entry.m_vDir.x, entry.m_vDir.x, entry.m_vDir.y * entry.m_vDir.y)))));
            if (length != 0.0f) {
                const float inverse = 1.0f / length;
                entry.m_vDir.z = inverse * entry.m_vDir.z;
                entry.m_vDir.x = inverse * entry.m_vDir.x;
                entry.m_vDir.y = inverse * entry.m_vDir.y;
            }
        }
        entry.m_vPos = CVector3{position.x, position.y, position.z};
    }
    m_BitProperties &= ~0x100u;
}

// C2.8 port-all P08.
// 0x000b8e00 CSpawnManager_CanBeUpdated
int32_t CSpawnManager::CanBeUpdated() {
    return static_cast<int32_t>(((g_pEngine->m_graphic->m_renderer->m_bitProperties ^ 2) >> 1) & 1);
}
