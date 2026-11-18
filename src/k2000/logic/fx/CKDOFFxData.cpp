// CKDOFFxData.cpp - reconstructed original translation unit 0x1af710-0x1b06d8 (GAME_TOC1, main_toc1), 16 functions, 16 live.
// Primary class: CKDOFFxData  key 0x7f8c  category Logic  size 0x10  vtable 0xb1c750
// Other owners: CKSrvFx (2)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1af710  CKDOFFxData_Delete
//   [x] 0x1af760  CKDOFFxData_GetNodeClassKey
//   [ ] 0x1af768  RegisterCKDOFFxDataClass
//   [ ] 0x1af7e0  _GLOBAL__I_1af7e0
//   [x] 0x1af7f0  CKDOFFxData_PostLoad
//   [x] 0x1af818  CKDOFFxData_Load
//   [ ] 0x1af918  CKDOFFxData_Save
//   [x] 0x1af940  CKDOFFxData_RecursiveRegistration
//   [x] 0x1af9b8  CKDOFFxData_DeleteArray
//   [x] 0x1afa58  CKDOFFxData_CreateArray
//   [x] 0x1afaf8  CKSrvFx_StartCameraFx_maybe
//   [x] 0x1aff80  CKDOFFxData_Create
//   [x] 0x1affc8  CKDOFFxData_GetInfo  (returns 1: the default slot)
//   [x] 0x1affd0  CKDOFFxData_Destroy  (empty: the default slot)
//   [x] 0x1affd8  CKSrvFx_StopCameraFx_maybe
//   [x] 0x1b0148  CKDOFFxData_MessageProc
//
//   [x] 0x9ab6c8  CKDOFFxData_IsKindOfClass  [inline]
//   [x] 0x9ab700  CKDOFFxData_GetClassType  [inline]
//   [x] 0x9ab708  CKDOFFxData_GetClassID  [inline]
//   [x] 0x9ab710  CKDOFFxData_vf50  [inline]
//   [ ] 0x9ab718  CKDOFFxData_DeletingDestructor  [inline]
//   [ ] 0x9ab770  CKDOFFxData_Destructor  [inline]
#include "k2000/logic/fx/CKDOFFxData.h"

#include "k2000/fx/IKFx.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/fx/CKDOFNodeFx.h"
#include "k2000/misc/Engine.h"
#include "k2000/services/CKSrvFx.h"

namespace {

// The unique effect of `data`'s node class (the inlined search of the service's unique effects: vt+0x18 id << 6 plus
// vt+0x14 type against the data's vt+0x54); its slot may hold null.
bool FindUniqueFx(IKFxData* data, IKSerializable** fx) {
    CKSrvFx* service = static_cast<CKSrvFx*>(g_pEngine->m_srvFx);
    const uint32_t key = data->GetAssociatedFxClassIdentifier();  // vt+0x54
    for (uint32_t i = 0; i < service->m_ui32UniqueFxArraySize; ++i) {
        IKSerializable* unique = service->m_apUniqueFxArray[i];
        if (static_cast<uint32_t>((unique->GetClassID() << 6) + unique->GetClassType()) != key) continue;
        *fx = unique;
        return true;
    }
    return false;
}

}  // namespace

// 0x001af818 CKDOFFxData_Load
int32_t CKDOFFxData::Load(IKFile* file, int32_t type) {
    IKFxData::Load(file, type);  // 0x001d8348
    if (type == K_LEVEL_PLATEFORMS) {
        IKFile_ReadRef(file, &m_pDOFData);
        ReadF32LE(file, &m_fFadeTime);
    }
    return 1;
}

// 0x001b0148 CKDOFFxData_MessageProc
int32_t CKDOFFxData::MessageProc(uint16_t message, void* data) {
    IKSerializable* fx = nullptr;
    if (message == 0x1b00) {
        static_cast<CKSrvFx*>(g_pEngine->m_srvFx)->StartEffect(this, this);
        if (FindUniqueFx(this, &fx) && fx != nullptr) static_cast<CKDOFNodeFx*>(fx)->SetBlendTime(*static_cast<const float*>(data));  // 0x001b0a58
        return 0;
    }
    if (message == 0x1b01) {
        if (FindUniqueFx(this, &fx) && fx != nullptr) static_cast<CKDOFNodeFx*>(fx)->BeginFadeOut(*static_cast<const float*>(data));  // 0x001b0a40
    }
    return 1;
}

// 0x001afaf8 CKSrvFx_StartCameraFx_maybe: the camera's attached effect started (as the FX data's message 0x1b00, the
// data as owner), then the unique DOF node given the blend time when it is not negative (`cror gt|eq`: not NaN either).
void CKSrvFx::StartCameraFx(float time, IKFxData* data) {
    static_cast<CKSrvFx*>(g_pEngine->m_srvFx)->StartEffect(data, data);
    IKSerializable* fx = nullptr;
    if (!FindUniqueFx(data, &fx) || fx == nullptr) return;
    if (time >= 0.0f) static_cast<CKDOFNodeFx*>(fx)->SetBlendTime(time);  // 0x001b0a58
}

// 0x001affd8 CKSrvFx_StopCameraFx_maybe: the unique DOF node faded out over `time`, or over the data's +0x0c when `time`
// is negative (or NaN).
void CKSrvFx::StopCameraFx(float time, IKFxData* data) {
    IKSerializable* fx = nullptr;
    if (!FindUniqueFx(data, &fx) || fx == nullptr) return;
    if (time >= 0.0f) {
        static_cast<CKDOFNodeFx*>(fx)->BeginFadeOut(time);
    } else {
        static_cast<CKDOFNodeFx*>(fx)->BeginFadeOut(static_cast<CKDOFFxData*>(data)->m_fFadeTime);
    }
}

// 0x001af940 CKDOFFxData_RecursiveRegistration
void CKDOFFxData::RecursiveRegistration(int32_t type) {
    IKFxData::RecursiveRegistration(type);  // KStub_Return1_1d8340
    if (type == 0) m_pDOFData->RecursiveRegistration(0);  // vt+0x24
}
