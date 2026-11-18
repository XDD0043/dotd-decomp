// CKFilterFxData.cpp - reconstructed original translation unit 0x1b8778-0x1b9358 (GAME_TOC1, main_toc1), 10 functions, 9 live.
// Primary class: CKFilterFxData  key 0x1a0c  category Logic  size 0x28  vtable 0xb1cae0
// Other owners: CKFilterNode2dFx (2)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1b8778  CKFilterFxData_GetNodeClassKey
//   [x] 0x1b8780  CKFilterFxData_RecursiveRegistration  (IKFxData's KStub_Return1_1d8340: the default slot)
//   [x] 0x1b87a8  CKFilterFxData_GetInfo  (returns 1: the default slot)
//   [x] 0x1b87b0  CKFilterFxData_Destroy
//   [x] 0x1b87e8  CKFilterFxData_Load
//   [ ] 0x1b89e8  CKFilterFxData_Save
//   [x] 0x1b8bd8  CKFilterFxData_MessageProc
//   [x] 0x1b92f8  CKFilterNode2dFx_Delete  (CKFilterNode2dFx's factory Delete: DOTD_DECLARE_FACTORIES)
//   [x] 0x1b9348  CKFilterNode2dFx_Destroy  (empty: the default slot)
//   [ ] 0x1b9350  KStub_Nop_1b9350  [dead]
//
//   [ ] 0x9abd68  CKFilterFxData_IsKindOfClass  [inline]
//   [x] 0x9abda0  CKFilterFxData_GetClassType  [inline]
//   [x] 0x9abda8  CKFilterFxData_GetClassID  [inline]
//   [ ] 0x9abdb0  CKFilterFxData_DeletingDestructor  [inline]
//   [ ] 0x9abe08  CKFilterFxData_Destructor  [inline]
#include "k2000/logic/fx/CKFilterFxData.h"

#include "k2000/io/IKFile.h"
#include "Renderware/rwcore/RwTexture.h"
#include "k2000/fx/IKFx.h"
#include "k2000/logic/fx/CKFilterNode2dFx.h"
#include "k2000/misc/Engine.h"
#include "k2000/services/CKSrvFx.h"

// 0x001b87e8 CKFilterFxData_Load
int32_t CKFilterFxData::Load(IKFile* file, int32_t type) {
    if (type == K_LEVEL_PLATEFORMS) {
        IKFxData::Load(file, K_LEVEL_PLATEFORMS);
        ReadF32LE(file, &m_fColorSpeed);
        ReadRaw(file, m_FinalColor, 4);
        ReadRaw(file, m_StartColor, 4);
        IKFile_ReadTextureRef(file, &m_pTexture, 1);
        uint8_t flag = 0;
        ReadU8(file, &flag);
        m_baFlags = static_cast<uint8_t>((m_baFlags & 0xfc) | (flag << 1));
        ReadU8(file, &m_ui8BlendMod);
        ReadF32LE(file, &m_unk08);
    }
    m_unk20 = 0;  // every type
    return 1;
}

// 0x001b87b0 CKFilterFxData_Destroy
void CKFilterFxData::Destroy() {
    if (m_pTexture != nullptr) RwTextureDestroy(static_cast<RwTexture*>(m_pTexture));  // TocBridge_RwTextureDestroy
}

// 0x001b8bd8 CKFilterFxData_MessageProc
int32_t CKFilterFxData::MessageProc(uint16_t message, void* data) {
    if (message == 0x1b01) {
        if (m_unk20 == nullptr) return 0;
        m_unk20->StopAndRelease(this);  // vt+0x58
        m_unk20 = nullptr;
        return 0;
    }
    if (message == 0x1b1e) {
        if (m_unk20 == nullptr) return 0;
        static_cast<CKFilterNode2dFx*>(m_unk20)->BeginFadeOut(*static_cast<const float*>(data), this);  // 0x001b9a18
        m_unk20->ReleaseReservation(this);  // vt+0x54
        return 0;
    }
    if (message != 0x1b00) return 1;
    CKSrvFx* fxService = static_cast<CKSrvFx*>(g_pEngine->m_srvFx);
    if (((m_baFlags >> 1) & 1u) == 0) {
        if (m_unk20 != nullptr) {
            m_unk20->StopAndRelease(this);  // vt+0x58
            m_unk20 = nullptr;
        }
        m_unk20 = fxService->AcquireFx(this, this);
        return 0;
    }
    fxService->StartEffect(this, this);  // every path answers 0
    return 0;
}
