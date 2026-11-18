// CKSpawnPool.cpp - reconstructed original translation unit 0xb6bd8-0xb7b00 (GAME_TOC1, main_toc1), 16 functions, 15 live.
// Primary class: CKSpawnPool  key 0xbcd  category Graphical  size 0x30  vtable 0xb17910
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0xb6bd8  RegisterCKSpawnPoolClass
//   [ ] 0xb6c50  _GLOBAL__I_b6c50
//   [ ] 0xb6c60  CKSpawnPool_ClearReferences_2  [dead]
//   [x] 0xb6d00  CKSpawnPool_AcquireAnimSlot_maybe  (AcquireAnimSlot; its caller 0xd4a60 (CZoneNode.cpp) is R08's)
//   [x] 0xb6dd0  CKSpawnPool_DeleteArray
//   [x] 0xb6e78  CKSpawnPool_Create
//   [x] 0xb6ed8  CKSpawnPool_StartSlotShakeCache_maybe
//   [x] 0xb6f48  CKSpawnPool_UpdateAnimSlot_maybe  (UpdateAnimSlot; its caller 0xd4a60 (CZoneNode.cpp) is R08's)
//   [x] 0xb70e8  CKSpawnPool_StopAllShakeCaches_maybe
//   [x] 0xb7160  CKSpawnPool_RecursiveRegistration  (CKSpawnPool::RecursiveRegistration)
//   [x] 0xb73a8  CKSpawnPool_CreateArray
//   [ ] 0xb7470  CKSpawnPool_Save
//   [x] 0xb7478  CKSpawnPool_MessageProc  (MessageProc: returns 1, the default slot)
//   [x] 0xb7480  CKSpawnPool_PostLoad
//   [x] 0xb7518  CKSpawnPool_Load
//   [x] 0xb7a60  CKSpawnPool_Destroy  (CKSpawnPool::Destroy)
//
//   [ ] 0x9a0ef8  CKSpawnPool_GetClassType  [inline]
//   [ ] 0x9a0f00  CKSpawnPool_GetClassID  [inline]
//   [ ] 0x9a0f08  CKSpawnPool_IsKindOfClass  [inline]
//   [ ] 0x9a0f28  CKSpawnPool_Destruct  [inline]
//   [ ] 0x9a0fa0  CKSpawnPool_DeletingDestruct  [inline]
#include "k2000/graphical/memory/CKSpawnPool.h"

#include "k2000/graphical/CKAnmKeyFrameController.h"
#include "k2000/graphical/animation/CAnimationManager.h"
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
        ReadF32LE(file, &entry->m_unk20);
        ++i;
    } while (i < m_ui32NumHierarchy);
    return 1;
}

// 0x000b7480 CKSpawnPool_PostLoad: (type 0) every hierarchy's controller gets the template node's first animation
// (CAnimatedNode +0x5c), from 0 (TOC -0x5b68: 0.0f), no restart (r6 0). The original passes +0x5c as the animation
// pointer CAnimatedNode_PostLoad put there; dotd keeps the dictionary word there and resolves it
// (CAnimationManager_GetAnimation; a node without bit 0 keeps 0xffffffff, which the original would pass as is and
// dotd passes as null).
int32_t CKSpawnPool::PostLoad(int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    for (uint32_t i = 0; i < m_ui32NumHierarchy; ++i) {
        const CAnimatedNode* node = static_cast<const CAnimatedNode*>(m_pNode);
        static_cast<CKAnmKeyFrameController*>(m_asRpHAnimHierarchy[i].m_pController)
            ->SetAnim(0.0f, CAnimationManager_GetAnimation(node->m_unk5c), false);  // 0x0007ab20
    }
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

#include "Renderware/rphanim/RpHAnim.h"
#include "Renderware/rwcore/RwCamera.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/misc/Engine.h"

// 0x000b7160 CKSpawnPool_RecursiveRegistration
void CKSpawnPool::RecursiveRegistration(int32_t type) {
    if (type == 0) g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);  // vt+0x24
    for (uint32_t i = 0; i < m_ui32NbSpawnPoolParams; ++i) m_apSpawnPoolParams[i]->RecursiveRegistration(type);
    for (uint32_t i = 0; i < m_ui32NbRenderParams; ++i) m_apRenderParams[i]->RecursiveRegistration(type);
    if (type != 0) return;
    m_pNode->RecursiveRegistration(0);
    // BUG(original)? the walk starts at hierarchy 1.
    for (uint32_t i = 1; i < m_ui32NumHierarchy; ++i) m_asRpHAnimHierarchy[i].m_pController->RecursiveRegistration(0);
}

// 0x000b7a60 CKSpawnPool_Destroy
void CKSpawnPool::Destroy() {
    for (uint32_t i = 0; i < m_ui32NumHierarchy; ++i) {
        RwFrameDestroy(m_asRpHAnimHierarchy[i].m_pRpHAnimHierarchy->parentFrame);  // 0x000c8d60
    }
    if (m_asRpHAnimHierarchy != nullptr) {
        Mem_FreeAligned16(m_asRpHAnimHierarchy);
        m_asRpHAnimHierarchy = nullptr;
    }
}

// C2.8 port-rest R02.

#include "k2000/misc/ClassRegistry.h"
#include "k2000/render/CRenderer.h"
#include "k2000/system/IKTime.h"

// 0x000b6d00 CKSpawnPool_AcquireAnimSlot_maybe
uint32_t CKSpawnPool::AcquireAnimSlot() {
    uint32_t slot = m_unk2c;
    if (slot >= m_ui32NumHierarchy) {
        slot = 0;
        m_unk2c = 0;
    }
    if ((m_unk08 & 1u) == 0) {
        SAnimHierarchy* entry = &m_asRpHAnimHierarchy[slot];
        const uint32_t draw = static_cast<uint32_t>(Rand_Int()) & 0xffffu;
        CKAnmKeyFrameController* controller = static_cast<CKAnmKeyFrameController*>(entry->m_pController);
        const float duration = controller->GetDuration();  // 0x0007ab60 Anim_GetDuration
        // fcfid / frsp, fdivs by 65535 (TOC -0x5b78 0x477fff00), fmuls by the duration.
        const float time = static_cast<float>(static_cast<double>(draw)) / 65535.0f * duration;
        entry->m_unk20 = time;
        static_cast<CKAnmKeyFrameController*>(entry->m_pController)->m_unk50 = time;
        slot = m_unk2c;
    }
    m_unk2c = slot + 1;
    return slot;
}

// 0x000b6f48 CKSpawnPool_UpdateAnimSlot_maybe
void CKSpawnPool::UpdateAnimSlot(CAnimatedNode* node, RenderQueue** stages, IKTime* clock, uint32_t slot,
                                 float* sphere, float* worldSphere, RwCamera* camera) {
    SAnimHierarchy* entry = &m_asRpHAnimHierarchy[slot];
    CKAnmKeyFrameController* controller = static_cast<CKAnmKeyFrameController*>(entry->m_pController);
    node->SetHAnimHierarchy(entry->m_pRpHAnimHierarchy, entry->m_pController, 0, 0);  // 0x000c9a08
    if (entry->m_unk0c == g_ui16RenderFrameCounter) {
        // 0x000cbfc0: the slot's cached sphere (radius +0x1c) into world space.
        TransformNodeBoundingSphereToWorld(entry->m_aUnk10[3], node, worldSphere, &worldSphere[3], entry->m_aUnk10);
        return;
    }
    if (clock->m_eCurrentState == 0) {
        const float time = entry->m_unk20 + clock->m_afDeltaTime[0];  // clock +0x1c
        entry->m_unk20 = time;
        controller->m_unk50 = time;
    }
    node->UpdatePoseAndCull(stages, clock, sphere, worldSphere, camera);  // 0x000cabc8
    entry->m_aUnk10[0] = sphere[0];
    entry->m_aUnk10[1] = sphere[1];
    entry->m_aUnk10[2] = sphere[2];
    entry->m_aUnk10[3] = sphere[3];
    entry->m_unk0c = g_ui16RenderFrameCounter;
}
