// CKLensFlareFxData.cpp - reconstructed original translation unit: 0x1c5f28-0x1c6758 (GAME_TOC1, main_toc1), 8 functions, 8 live.
// Primary class: CKLensFlareFxData  key 0x350c  category Logic  size 0x10  vtable 0xb1d140
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1c5f28  CKLensFlareFxData_GetNodeClassKey  (CKLensFlareFxData.h)
//   [x] 0x1c5f30  CKLensFlareFxData_Destroy
//   [x] 0x1c5f78  CKLensFlareFxData_PostLoad  (IKFxData's: the default)
//   [x] 0x1c5fa0  CKLensFlareFxData_Load
//   [ ] 0x1c6070  CKLensFlareFxData_Save
//   [x] 0x1c6130  CKLensFlareFxData_RecursiveRegistration
//   [x] 0x1c61a8  CKLensFlareFxData_GetInfo  (CKLensFlareFxData.h)
//   [x] 0x1c61b0  CKLensFlareFxData_MessageProc
//
//   [x] 0x9ac7a8  CKLensFlareFxData_IsKindOfClass  [inline]  (CKLensFlareFxData.h)
//   [x] 0x9ac7e0  CKLensFlareFxData_GetClassType  [inline]  (DOTD_CLASS_KEY)
//   [x] 0x9ac7e8  CKLensFlareFxData_GetClassID  [inline]  (DOTD_CLASS_KEY)
//   [x] 0x9ac7f0  CKLensFlareFxData_Destructor  [inline]  (CKLensFlareFxData.h)
//   [x] 0x9ac830  CKLensFlareFxData_DeletingDestructor  [inline]  (CKLensFlareFxData.h)
#include "k2000/logic/fx/CKLensFlareFxData.h"

#include "k2000/fx/IKFx.h"
#include "k2000/graphical/fx/CLensFlareFx.h"
#include "k2000/io/IKFile.h"
#include "k2000/misc/Engine.h"
#include "k2000/services/CKSrvFx.h"

namespace {
// The object message 0x1b91 names (its data is a pointer to it): three words from its +0x04 are the flare's new world
// position. No sender in the EBOOT has the id as an immediate (the message comes from data); the object's class is not
// known, so the read keeps the PS3 layout (a word, then the position).
struct LensFlarePositionSource {
    uint32_t m_unk00;
    float m_afPosition[3];  // +0x04
};
}  // namespace

// 0x001c5f30 CKLensFlareFxData_Destroy
void CKLensFlareFxData::Destroy() {
    m_pFlareData->Destroy();  // vt+0x10, not tested
}

// 0x001c6130 CKLensFlareFxData_RecursiveRegistration
void CKLensFlareFxData::RecursiveRegistration(int32_t type) {
    IKFxData::RecursiveRegistration(type);  // KStub_Return1_1d8340
    if (type == 0) m_pFlareData->RecursiveRegistration(0);  // vt+0x24
}

// 0x001c5fa0 CKLensFlareFxData_Load: IKFxData's, the flare data reference (level files); the held effect cleared.
int32_t CKLensFlareFxData::Load(IKFile* file, int32_t type) {
    IKFxData::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) IKFile_ReadRef(file, &m_pFlareData);
    m_pHeldFx = nullptr;
    return 1;
}

// 0x001c61b0 CKLensFlareFxData_MessageProc
int32_t CKLensFlareFxData::MessageProc(uint16_t message, void* data) {
    if (message == 0x1b01) {
        if (m_pHeldFx == nullptr) return 0;
        m_pHeldFx->StopAndRelease(this);  // vt+0x58
        m_pHeldFx = nullptr;
        return 0;
    }
    if (message == 0x1b91) {
        if (m_pHeldFx != nullptr) {
            m_pHeldFx->StopAndRelease(this);  // vt+0x58
            m_pHeldFx = nullptr;
        }
        const LensFlarePositionSource* source = *static_cast<LensFlarePositionSource* const*>(data);
        if (source != nullptr) {
            m_pFlareData->m_vPosition.x = source->m_afPosition[0];
            m_pFlareData->m_vPosition.y = source->m_afPosition[1];
            m_pFlareData->m_vPosition.z = source->m_afPosition[2];
        }
        m_pHeldFx = static_cast<CKSrvFx*>(g_pEngine->m_srvFx)->AcquireFx(this, this);
        return 0;
    }
    if (message != 0x1b00) return 1;
    if (m_pHeldFx != nullptr) {
        m_pHeldFx->StopAndRelease(this);  // vt+0x58
        m_pHeldFx = nullptr;
    }
    m_pHeldFx = static_cast<CKSrvFx*>(g_pEngine->m_srvFx)->AcquireFx(this, this);
    return 0;
}
