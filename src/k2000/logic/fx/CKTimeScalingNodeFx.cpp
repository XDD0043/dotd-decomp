// CKTimeScalingNodeFx.cpp - reconstructed original translation unit 0x1d7d50-0x1d8348 (GAME_TOC1, main_toc1), 22 functions, 22 live.
// Primary class: CKTimeScalingNodeFx  key 0x27cc  category Logic  size 0x24  vtable 0xb1db98
// Other owners: CKNodeFxBase (3)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1d7d50  CKTimeScalingNodeFx_Delete
//   [x] 0x1d7da0  CKTimeScalingNodeFx_Destroy  (empty)
//   [x] 0x1d7da8  CKTimeScalingNodeFx_RecursiveRegistration
//   [x] 0x1d7e00  CKTimeScalingNodeFx_PostLoad
//   [x] 0x1d7e10  CKTimeScalingNodeFx_Start
//   [x] 0x1d7e30  CKTimeScalingNodeFx_Interrupt_maybe
//   [x] 0x1d7e70  CKTimeScalingNodeFx_StopIfOwnedBy_maybe
//   [ ] 0x1d7ed0  RegisterCKTimeScalingNodeFxClass
//   [ ] 0x1d7f48  _GLOBAL__I_1d7f48
//   [x] 0x1d7f58  CKTimeScalingNodeFx_Load
//   [ ] 0x1d7f80  CKTimeScalingNodeFx_Save
//   [x] 0x1d7fa8  CKTimeScalingNodeFx_DeleteArray
//   [x] 0x1d8050  CKTimeScalingNodeFx_CreateArray
//   [x] 0x1d8108  CKTimeScalingNodeFx_Update
//   [x] 0x1d81d8  CKTimeScalingNodeFx_SetDataAndOwner
//   [x] 0x1d8238  CKTimeScalingNodeFx_Stop
//   [x] 0x1d82b8  CKTimeScalingNodeFx_Create
//   [x] 0x1d8310  IKFx_ResetRuntimeFlags  (IKFx::ResetRuntimeFlags, IKFx.h)
//   [x] 0x1d8320  IKFx_Load
//   [ ] 0x1d8330  IKFx_Save
//   [x] 0x1d8338  KStub_Return1_1d8338  (IKFxData PostLoad: the IKSerializable default)
//   [x] 0x1d8340  KStub_Return1_1d8340  (the FX data base's RecursiveRegistration: nothing (the default slot))
//
//   [ ] 0x9ab490  IKFx_StopIfLinkedTo  [inline]
//   [ ] 0x9ab498  IKFx_SetOwner  [inline]
//   [ ] 0x9ab4a0  IKFx_IsGlobalEffect_maybe  [inline]
//   [ ] 0x9ad738  CKTimeScalingNodeFx_IsKindOfClass  [inline]
//   [x] 0x9ad770  CKTimeScalingNodeFx_GetClassType  [inline]
//   [x] 0x9ad778  CKTimeScalingNodeFx_GetClassID  [inline]
//   [ ] 0x9ad780  CKTimeScalingNodeFx_IsGlobalEffect_maybe  [inline]
//   [x] 0x9ad788  CKTimeScalingNodeFx_GetFxData  [inline]
//   [x] 0x9ad790  CKTimeScalingNodeFx_SetFxData  [inline]
//   [ ] 0x9ad798  CKTimeScalingNodeFx_Destruct  [inline]
//   [ ] 0x9ad7b8  CKTimeScalingNodeFx_DeletingDestruct  [inline]
//   [x] 0x9ad800  IKFx_GetClassType  [inline]
//   [x] 0x9ad808  IKFx_GetClassID  [inline]
//   [ ] 0x9ad810  IKFx_SetUpdateWhenPaused  [inline]
//   [ ] 0x9ad818  IKFx_GetUpdateWhenPaused  [inline]
//   [ ] 0x9ad820  IKFx_DeletingDestruct  [inline]
//   [ ] 0x9ad860  IKFx_IsKindOfClass  [inline]
//   [ ] 0x9ad880  IKFx_Destruct  [inline]
#include "k2000/logic/fx/CKTimeScalingNodeFx.h"

#include "k2000/fx/IKFx.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/logic/fx/CKTimeScalingFxData.h"
#include "k2000/misc/Engine.h"
#include "k2000/system/CTimeManager.h"
#include "k2000/system/IKTime.h"

// 0x001d7f58 CKTimeScalingNodeFx_Load
int32_t CKTimeScalingNodeFx::Load(IKFile* file, int32_t type) {
    IKNodeFx::Load(file, type);
    return 1;
}

// 0x001d8320 IKFx_Load: reads nothing.
int32_t IKFx::Load(IKFile* /*file*/, int32_t /*type*/) {
    m_bUpdateWhenPaused = 0;
    return 1;
}

// 0x001d7e00 CKTimeScalingNodeFx_PostLoad
int32_t CKTimeScalingNodeFx::PostLoad(int32_t /*type*/) {
    m_pData = nullptr;
    return 1;
}

// 0x001d7e10 CKTimeScalingNodeFx_Start: running, the data's time from 0.
void CKTimeScalingNodeFx::Vf64() {
    m_baFxData = static_cast<uint8_t>(m_baFxData & 0xfe);
    m_fElapsed = 0.0f;
}

// 0x001d8238 CKTimeScalingNodeFx_Stop: stopped, the node hidden (vt+0x60), the data dropped and the game time scale back to
// 1 (TOC -0x189c).
void CKTimeScalingNodeFx::Stop() {
    m_baFxData = static_cast<uint8_t>((m_baFxData & 0xfe) | 1);
    Vf60();
    m_pData = nullptr;
    g_pEngine->m_timeManager->m_fTimeScale = 1.0f;
}

// 0x001d8108 CKTimeScalingNodeFx_Update: the data's time advances by IKTime +0x20 (m_afDeltaTime[1], not scaled by the time
// scale this effect sets); before the data's end (+0x0c) the scale is read from its curve, after it the last scale stays
// unless the data stops at its end (+0x08 bit 0). Data bit 1 stops the effect at once. The scale is written every frame.
void CKTimeScalingNodeFx::Update(IKTime* frameClock) {
    CKTimeScalingFxData* data = m_pData;
    if ((data->m_unk08 & 2) == 0) {
        const float t = m_fElapsed + frameClock->m_afDeltaTime[1];
        m_fElapsed = t;
        if (data->m_unk0c > t) {
            m_fScale = data->EvaluateScaleCurve(t);
        } else if ((data->m_unk08 & 1) != 0) {
            Stop();  // vt+0x6c
            return;
        }
        g_pEngine->m_timeManager->m_fTimeScale = m_fScale;
        return;
    }
    Stop();  // vt+0x6c
}

// 0x009ad788 CKTimeScalingNodeFx_GetFxData
IKFxData* CKTimeScalingNodeFx::GetFxData() { return m_pData; }

// 0x001d81d8 CKTimeScalingNodeFx_SetDataAndOwner (the data is never null when an effect already runs one: its +0x10 is read
// before the null test).
void CKTimeScalingNodeFx::SetDataAndOwner(IKFxData* data, const IKSerializable* owner) {
    CKTimeScalingFxData* next = static_cast<CKTimeScalingFxData*>(data);
    if (m_pData != nullptr) {
        if (next->m_unk10 <= m_pData->m_unk10) return;
        if ((next->m_unk08 & 2) != 0) return;
    }
    m_pScaleOwner = owner;
    m_fElapsed = 0.0f;
    m_pData = next;
}

// 0x001d7e70 CKTimeScalingNodeFx_StopIfOwnedBy_maybe
void CKTimeScalingNodeFx::StopIfOwnedBy(const CKTimeScalingFxData* data, const IKSerializable* owner) {
    if (m_pData == data && m_pScaleOwner == owner) Stop();  // vt+0x6c
}

// 0x001d7da8 CKTimeScalingNodeFx_RecursiveRegistration: registered with the saving manager (vt+0x24, no owner) only.
void CKTimeScalingNodeFx::RecursiveRegistration(int32_t /*type*/) {
    g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);  // vt+0x24
}
