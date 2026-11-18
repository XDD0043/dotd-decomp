// CKSpawnPoolParams.cpp - reconstructed original translation unit 0xb7b00-0xb8d50 (GAME_TOC1, main_toc1), 23 functions, 19 live.
// Primary class: CKSpawnPoolParams  key 0x60d  category Graphical  size 0x20  vtable 0xb17968
// Other owners: ShakeMatrixCache (4)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0xb7b00  CKSpawnPoolParams_Delete
//   [ ] 0xb7b50  CKSpawnPoolParams_Construct  [dead]
//   [x] 0xb7b70  KStub_Nop_b7b70  (empty: CSpawnManager_PreUpdate calls it, nothing to port)
//   [x] 0xb7b78  CKSpawnPoolParams_NextIndex_maybe  (CKSpawnPoolParams::NextIndex)
//   [ ] 0xb7bd0  CKSpawnPoolParams_Construct_2  [dead]
//   [ ] 0xb7bf0  RegisterCKSpawnPoolParamsClass
//   [ ] 0xb7c68  _GLOBAL__I_b7c68
//   [x] 0xb7c78  ShakeMatrixCache_StopAll_maybe
//   [x] 0xb7d58  ShakeMatrixCache_Start_maybe
//   [x] 0xb7f40  ShakeMatrixCache_UpdateEntry_maybe  (CKSpawnPoolParams::UpdateShakeEntry)
//   [x] 0xb81c8  CKSpawnPoolParams_DeleteArray
//   [x] 0xb8268  ShakeMatrixCache_GetMatrix_maybe  (CKSpawnPoolParams::GetShakeMatrix)
//   [x] 0xb8300  CKSpawnPoolParams_RecursiveRegistration  (CKSpawnPoolParams::RecursiveRegistration)
//   [x] 0xb8440  CKSpawnPoolParams_CreateArray
//   [x] 0xb84f0  CKSpawnPoolParams_Create
//   [x] 0xb8540  CKSpawnPoolParams_PostLoad  (PostLoad: returns 1, the default slot)
//   [x] 0xb8548  CKSpawnPoolParams_Destroy  (CKSpawnPoolParams::Destroy)
//   [x] 0xb85f8  CKSpawnPoolParams_Destructor  (~CKSpawnPoolParams, CKSpawnPoolParams.h)
//   [x] 0xb8660  CKSpawnPoolParams_Load
//   [ ] 0xb8930  CKSpawnPoolParams_Save
//   [ ] 0xb8b38  CKSpawnPoolParams_SetShakeActive_maybe  [dead]
//   [ ] 0xb8c68  CKSpawnPoolParams_Destructor_2  [dead]
//   [x] 0xb8cd0  CKSpawnPoolParams_DeletingDestructor  (~CKSpawnPoolParams, CKSpawnPoolParams.h; delete)
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
#include "k2000/misc/ClassRegistry.h"

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

// 0x000b7d58 ShakeMatrixCache_Start_maybe with any slot (C2.8 port-final F05; StartAllShakes above is its slot -1 form,
// kept for its caller). The one-slot form: CKQuakeCpntUpdater_GetQuakeCpnt_maybe 0x24ee00 and its duration (+0x04) are
// read before the Rand_Int 0x11500 draw; the draw's low half becomes a float (fcfid / frsp, exact), over 65535 (fdivs),
// times the duration (fmuls), and EvaluateScaled 0x24f5c8 runs with that time and 1 into a scratch output block.
void CKSpawnPoolParams::StartShake(uint32_t slot) {
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
        static_cast<CKQuakeCpntUpdater*>(m_vsMatrixData[0].m_pObject)->Start();  // 0x0024f770
    }
    if (slot == 0xffffffffu) {
        for (uint32_t i = 0; i < m_ui32NbActiveMatrix; ++i) {
            static_cast<CKQuakeCpntUpdater*>(m_vsMatrixData[i].m_pObject)->Start();
        }
        return;
    }
    SMatrixData* entry = &m_vsMatrixData[slot];
    static_cast<CKQuakeCpntUpdater*>(entry->m_pObject)->Start();  // 0x0024f770
    const uint32_t flags = m_unk04;
    if ((flags & 2) == 0 || (flags & 4) != 0) return;
    const float duration = static_cast<CKQuakeCpntUpdater*>(entry->m_pObject)->GetQuakeCpnt()->m_fDuration;
    CKQuakeCpntUpdater* updater = static_cast<CKQuakeCpntUpdater*>(entry->m_pObject);
    const float draw = static_cast<float>(static_cast<uint32_t>(Rand_Int()) & 0xffffu);  // 0x00011500
    float out[16];
    updater->EvaluateScaled(duration * (draw / 65535.0f), 1.0f, out);  // TOC1 -0x5b34 65535, -0x5b38 1
}

#include <cmath>

#include "crt/ppc_ops.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/misc/Engine.h"
#include "k2000/render/CRenderer.h"
#include "k2000/system/CTimeManager.h"
#include "k2000/system/IKTime.h"

// 0x000b8300 CKSpawnPoolParams_RecursiveRegistration
void CKSpawnPoolParams::RecursiveRegistration(int32_t type) {
    if (type != 0) return;
    g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);  // vt+0x24
    m_pUnk08->RecursiveRegistration(0);
    const uint32_t count = m_ui32NbMatrixData;
    for (uint32_t i = 0; i < count; ++i) m_vsMatrixData[i].m_pObject->RecursiveRegistration(0);
}

// 0x000b8548 CKSpawnPoolParams_Destroy
void CKSpawnPoolParams::Destroy() {
    const uint32_t count = m_ui32NbMatrixData;
    for (uint32_t i = 0; i < count; ++i) RwMatrixDestroy_Thunk(m_vsMatrixData[i].m_pMatrix);
    if (m_vsMatrixData != nullptr) {
        Mem_FreeAligned16(m_vsMatrixData);
        m_vsMatrixData = nullptr;
    }
    m_ui32NbMatrixData = 0;
    m_vsMatrixData = nullptr;
}

// 0x000b7b78 CKSpawnPoolParams_NextIndex_maybe
uint32_t CKSpawnPoolParams::NextIndex() {
    uint32_t index = 0;
    if ((m_unk04 & 2) == 0 || (m_unk04 & 4) == 0) {
        index = m_ui32NbNextActiveMatrix;
        if (m_ui32NbActiveMatrix <= index) {
            index = 0;
            m_ui32NbNextActiveMatrix = 0;
        }
        m_ui32NbNextActiveMatrix = index + 1;
    }
    return index;
}

// 0x000b8268 ShakeMatrixCache_GetMatrix_maybe
CMatrix34* CKSpawnPoolParams::GetShakeMatrix(uint32_t index, const CVector3* direction, uint8_t oriented) {
    if (m_vsMatrixData[index].m_ui16Id != g_ui16RenderFrameCounter) {
        UpdateShakeEntry(index, g_pEngine->m_timeManager->m_pTime, direction, oriented);
    }
    return m_vsMatrixData[index].m_pMatrix;
}

// 0x000b7f40 ShakeMatrixCache_UpdateEntry_maybe. The direction's length is fused (fmuls y, then fmadds x and z); a zero
// length leaves it unnormalised. Its normalised y decides the up fallback (ble: an unordered |y| takes the x axis).
void CKSpawnPoolParams::UpdateShakeEntry(uint32_t index, IKTime* clock, const CVector3* direction, uint8_t oriented) {
    if (clock->m_eCurrentState != IKTime::RUNNING) return;
    SMatrixData& entry = m_vsMatrixData[index];
    CMatrix34* matrix = entry.m_pMatrix;
    matrix->m_ui32Flags = 0x20003;
    matrix->m_right = {1.0f, 0.0f, 0.0f};
    matrix->m_up = {0.0f, 1.0f, 0.0f};
    matrix->m_at = {0.0f, 0.0f, 1.0f};
    matrix->m_pos = {0.0f, 0.0f, 0.0f};
    CKQuakeCpntUpdater* updater = static_cast<CKQuakeCpntUpdater*>(entry.m_pObject);
    if (updater->m_bRunning == 0) return;
    float out[15];
    updater->EvaluateScaled(clock->m_afDeltaTime[1], 1.0f, out);  // 0x0024f5c8
    if (updater->m_bRunning == 0 && (m_unk04 & 2) != 0) updater->Start();  // 0x0024f770
    CMatrix34 basis;
    const CMatrix34* base = nullptr;
    if (oriented != 0) {
        static const CVector3 kNull = {0.0f, 0.0f, 0.0f};    // 0x00c50d64
        static const CVector3 kAxisX = {1.0f, 0.0f, 0.0f};   // 0x00c50d34
        static const CVector3 kAxisY = {0.0f, 1.0f, 0.0f};   // 0x00c50d40
        if (!(kNull.x == direction->x && direction->y == kNull.y && direction->z == kNull.z)) {
            CVector3 at = *direction;
            const float length = std::sqrt(ppc::fmadds(at.z, at.z, ppc::fmadds(at.x, at.x, at.y * at.y)));  // 0x00010690
            if (length != 0.0f) {
                const float inverse = 1.0f / length;
                at.z = at.z * inverse;
                at.x = at.x * inverse;
                at.y = at.y * inverse;
            }
            if (!(std::fabs(at.y) <= 0.95f)) at = kAxisX;  // TOC1 -0x5b2c
            Mat4_SetBasisFromAtUp(&basis, &at, &kAxisY);  // 0x0023fd30
            base = &basis;
        }
    }
    ShakeSample_BuildMatrix(updater, out, matrix, base);  // 0x0024ee90
    entry.m_ui16Id = g_ui16RenderFrameCounter;
}
