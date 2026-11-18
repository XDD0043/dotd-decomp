// CKDOFNodeFx.cpp - reconstructed original translation unit 0x1b06d8-0x1b1300 (GAME_TOC1, main_toc1), 26 functions, 23 live.
// Primary class: CKDOFNodeFx  key 0x7fcc  category Logic  size 0x20  vtable 0xb1c7b8
// Other owners: CKElectricArcFxData (5), CKDOFFxData (2)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1b06d8  CKDOFNodeFx_Delete
//   [x] 0x1b0728  CKDOFNodeFx_Destroy  (CKDOFNodeFx.h: empty (IKNodeFx's is not called))
//   [x] 0x1b0730  CKDOFNodeFx_RecursiveRegistration
//   [x] 0x1b07d8  CKDOFNodeFx_PostLoad
//   [x] 0x1b0818  CKDOFNodeFx_Start
//   [x] 0x1b0828  CKDOFNodeFx_Interrupt_maybe  (Vf68, CKDOFNodeFx.h)
//   [x] 0x1b0868  CKDOFNodeFx_InterpolateParams_maybe
//   [x] 0x1b0a40  CKDOFFxData_BeginFadeOut_maybe
//   [x] 0x1b0a58  CKDOFFxData_SetBlendTime_maybe
//   [ ] 0x1b0a60  KStub_Nop_1b0a60  [dead]
//   [ ] 0x1b0a68  FUN_001b0a68  [dead]
//   [ ] 0x1b0ad0  RegisterCKDOFNodeFxClass
//   [ ] 0x1b0b48  _GLOBAL__I_1b0b48
//   [ ] 0x1b0b58  CKDOFNodeFx_Save
//   [x] 0x1b0b80  CKDOFNodeFx_DeleteArray
//   [x] 0x1b0c20  CKDOFNodeFx_CreateArray
//   [x] 0x1b0cd0  CKDOFNodeFx_Stop
//   [x] 0x1b0de8  CKDOFNodeFx_SetDataAndOwner
//   [x] 0x1b0eb8  CKDOFNodeFx_Create
//   [x] 0x1b0f10  CKDOFNodeFx_Update
//   [x] 0x1b10f8  CKDOFNodeFx_Load
//   [x] 0x1b11b8  CKElectricArcFxData_GetNodeClassKey  (CKElectricArcFxData::GetAssociatedFxClassIdentifier, CKElectricArcFxData.h)
//   [ ] 0x1b11c0  CKElectricArcFxData_EvaluateCurve_maybe  [dead]
//   [x] 0x1b1260  CKElectricArcFxData_Destroy  (CKElectricArcFxData::Destroy, here)
//   [ ] 0x1b12b0  CKElectricArcFxData_Save
//   [x] 0x1b12d8  CKElectricArcFxData_RecursiveRegistration  (IKFxData's KStub_Return1_1d8340: the default slot)
//
//   [ ] 0x9ab7b0  CKDOFNodeFx_IsKindOfClass  [inline]
//   [x] 0x9ab7e8  CKDOFNodeFx_GetClassType  [inline]
//   [x] 0x9ab7f0  CKDOFNodeFx_GetClassID  [inline]
//   [ ] 0x9ab7f8  CKDOFNodeFx_IsGlobalEffect_maybe  [inline]
//   [ ] 0x9ab800  CKDOFNodeFx_GetFxData  [inline]
//   [ ] 0x9ab808  CKDOFNodeFx_SetFxData  [inline]
//   [ ] 0x9ab810  CKDOFNodeFx_Destruct  [inline]
//   [ ] 0x9ab830  CKDOFNodeFx_DeletingDestruct  [inline]
//   [ ] 0x9ab878  CKElectricArcFxData_IsKindOfClass  [inline]
//   [ ] 0x9ab8b0  CKElectricArcFxData_GetClassType  [inline]
//   [ ] 0x9ab8b8  CKElectricArcFxData_GetClassID  [inline]
//   [ ] 0x9ab8c0  CKElectricArcFxData_DeletingDestructor  [inline]
//   [ ] 0x9ab918  CKElectricArcFxData_Destructor  [inline]
#include "k2000/logic/fx/CKDOFNodeFx.h"

#include <cstring>

#include "crt/ppc_ops.h"
#include "k2000/graphical/CDOFData.h"
#include "k2000/graphical/render/CPostRenderingFx.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKCoreManager.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/logic/IKFxData.h"
#include "k2000/logic/fx/CKDOFFxData.h"
#include "k2000/managers/CKGraphic.h"
#include "k2000/misc/Engine.h"
#include "k2000/render/CShaderManagerPSGL.h"
#include "k2000/system/IKTime.h"

namespace {
CPostRenderingFx* PostRenderingFx() {
    return static_cast<CPostRenderingFx*>(g_pEngine->m_coreManager->GetObjectByClassKey(0x38d));  // vt+0x58
}

// CDOFData's four words +0x04..+0x10 as floats (m_unk0c / m_unk10 are typed words in CDOFData.h).
float DofGet(const IKSerializable* data, int i) {
    const CDOFData* d = static_cast<const CDOFData*>(data);
    const void* src = i == 0 ? static_cast<const void*>(&d->m_fFocusDistance)
                    : i == 1 ? static_cast<const void*>(&d->m_fFocusClamp)
                    : i == 2 ? static_cast<const void*>(&d->m_unk0c)
                             : static_cast<const void*>(&d->m_unk10);
    float v;
    std::memcpy(&v, src, 4);
    return v;
}
void DofSet(IKSerializable* data, int i, float v) {
    CDOFData* d = static_cast<CDOFData*>(data);
    void* dst = i == 0 ? static_cast<void*>(&d->m_fFocusDistance)
              : i == 1 ? static_cast<void*>(&d->m_fFocusClamp)
              : i == 2 ? static_cast<void*>(&d->m_unk0c)
                       : static_cast<void*>(&d->m_unk10);
    std::memcpy(dst, &v, 4);
}
void DofZero(IKSerializable* data) {
    CDOFData* d = static_cast<CDOFData*>(data);
    d->m_unk10 = 0;
    d->m_unk0c = 0;
    d->m_fFocusClamp = 0.0f;
    d->m_fFocusDistance = 0.0f;
}

// The depth of field path of the renderer (CRenderer.cpp DepthOfFieldPath, without the object test).
bool DofPathOn() {
    return (g_pEngine->m_graphic->m_baHardwareCaps & 0x200) != 0 && g_pShaderManager->m_bShadersEnabled != 0 &&
           g_pShaderManager->m_i32ProfileMode == 6;
}
}  // namespace

// 0x001b10f8 CKDOFNodeFx_Load: the data reference only in level files.
int32_t CKDOFNodeFx::Load(IKFile* file, int32_t type) {
    IKNodeFx::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) IKFile_ReadRef(file, &m_pDOFData);
    return 1;
}

// 0x001b0730 CKDOFNodeFx_RecursiveRegistration
void CKDOFNodeFx::RecursiveRegistration(int32_t type) {
    g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);  // vt+0x24
    if (m_pDOFData != nullptr) m_pDOFData->RecursiveRegistration(type);      // vt+0x24
}

// 0x001b07d8 CKDOFNodeFx_PostLoad
int32_t CKDOFNodeFx::PostLoad(int32_t /*type*/) {
    m_unk1c = nullptr;
    m_fBlendTime = 0.0f;  // stw 0
    DofZero(m_pDOFData);
    return 1;
}

// 0x001b0868 CKDOFNodeFx_InterpolateParams_maybe (the four floats in the order +0x10, +0x0c, +0x08, +0x04; fused
// multiply-adds as on the PS3)
void CKDOFNodeFx::InterpolateParams(float time, float dt, IKSerializable* current, const IKSerializable* target) {
    // BUG(original): a null `current` reads zeros and still stores through it (no caller passes one).
    float c[4] = {0.0f, 0.0f, 0.0f, 0.0f};  // +0x04, +0x08, +0x0c, +0x10
    float t[4] = {0.0f, 0.0f, 0.0f, 0.0f};
    for (int i = 0; i < 4; ++i) {
        if (current != nullptr) c[i] = DofGet(current, i);
        if (target != nullptr) t[i] = DofGet(target, i);
    }
    float out[4] = {t[0], t[1], t[2], t[3]};
    if (time > 0.0f) {  // ble: NaN keeps the target
        for (int i = 3; i >= 0; --i) {
            const float d = t[i] - c[i];
            out[i] = ppc::fmadds(d / time, dt, c[i]);
            if (d > 0.0f) {
                if (out[i] > t[i]) out[i] = t[i];
            } else if (d < 0.0f) {
                if (out[i] < t[i]) out[i] = t[i];
            }
        }
    }
    DofSet(current, 0, out[0]);
    DofSet(current, 3, out[3]);
    DofSet(current, 2, out[2]);
    DofSet(current, 1, out[1]);
}

// 0x001b0cd0 CKDOFNodeFx_Stop
void CKDOFNodeFx::Stop() {
    m_baFxData = static_cast<uint8_t>((m_baFxData & 0xfe) | 1);
    CPostRenderingFx* postFx = PostRenderingFx();
    if (DofPathOn() && (postFx->m_BitProperties & 0x400) != 0) postFx->m_BitProperties &= 0xfffffbffu;
    Vf60();  // vt+0x60
    m_unk1c = nullptr;
}

// 0x001b0de8 CKDOFNodeFx_SetDataAndOwner
void CKDOFNodeFx::SetDataAndOwner(IKFxData* data, const IKSerializable* /*owner*/) {
    m_unk1c = data;
    m_fBlendTime = static_cast<CKDOFFxData*>(data)->m_fFadeTime;  // lwz / stw: the bits
    CPostRenderingFx* postFx = PostRenderingFx();
    if (postFx->m_pDOFData != nullptr) {
        CDOFData_SetParams(m_pDOFData, postFx->m_pDOFData);  // 0x000b6338
        return;
    }
    DofZero(m_pDOFData);
}

// 0x001b0f10 CKDOFNodeFx_Update
void CKDOFNodeFx::Update(IKTime* frameClock) {
    CPostRenderingFx* postFx = PostRenderingFx();
    const float dt = frameClock->m_afDeltaTime[0];
    if (m_unk1c == nullptr) {
        m_fBlendTime = m_fBlendTime - dt;
        InterpolateParams(m_fBlendTime, dt, m_pDOFData, nullptr);
        postFx->m_BitProperties = (postFx->m_BitProperties & 0xfffffbffu) | 0x400u;
        postFx->m_pDOFData = m_pDOFData;
        if (CDOFData_IsInactive(m_pDOFData)) {  // 0x000b5db8
            postFx->m_BitProperties &= 0xfffffbffu;
            postFx->m_pDOFData = m_pDOFData;
            Stop();  // vt+0x6c
        }
        return;
    }
    const IKSerializable* target = static_cast<CKDOFFxData*>(m_unk1c)->m_pDOFData;
    if (DofGet(m_pDOFData, 3) != DofGet(target, 3) || DofGet(m_pDOFData, 2) != DofGet(target, 2) ||
        DofGet(m_pDOFData, 1) != DofGet(target, 1) || DofGet(m_pDOFData, 0) != DofGet(target, 0)) {
        InterpolateParams(m_fBlendTime, dt, m_pDOFData, target);
        m_fBlendTime = m_fBlendTime - dt;
    }
    postFx->m_BitProperties = (postFx->m_BitProperties & 0xfffffbffu) | 0x400u;
    postFx->m_pDOFData = m_pDOFData;
}
