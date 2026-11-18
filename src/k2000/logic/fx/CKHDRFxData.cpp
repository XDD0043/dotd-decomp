// CKHDRFxData.cpp - reconstructed original translation unit 0x1be2a0-0x1bef50 (GAME_TOC1, main_toc1), 14 functions, 14 live.
// Primary class: CKHDRFxData  key 0xf0c  category Logic  size 0x18  vtable 0xb1ce10
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1be2a0  CKHDRFxData_Delete
//   [x] 0x1be2f0  CKHDRFxData_GetNodeClassKey
//   [ ] 0x1be2f8  RegisterCKHDRFxDataClass
//   [ ] 0x1be370  _GLOBAL__I_1be370
//   [x] 0x1be380  CKHDRFxData_PostLoad
//   [x] 0x1be3c0  CKHDRFxData_Load
//   [ ] 0x1be4c0  CKHDRFxData_Save
//   [x] 0x1be4e8  CKHDRFxData_RecursiveRegistration
//   [x] 0x1be560  CKHDRFxData_DeleteArray
//   [x] 0x1be608  CKHDRFxData_Create
//   [x] 0x1be650  CKHDRFxData_CreateArray
//   [x] 0x1be6f8  CKHDRFxData_GetInfo  (the default)
//   [x] 0x1be700  CKHDRFxData_Destroy  (empty)
//   [x] 0x1be708  CKHDRFxData_MessageProc
//
//   [ ] 0x9ac338  CKHDRFxData_IsKindOfClass  [inline]
//   [x] 0x9ac370  CKHDRFxData_GetClassType  [inline]
//   [x] 0x9ac378  CKHDRFxData_GetClassID  [inline]
//   [x] 0x9ac380  CKHDRFxData_vf50  [inline]
//   [ ] 0x9ac388  CKHDRFxData_Destructor  [inline]
//   [ ] 0x9ac3c8  CKHDRFxData_DeletingDestructor  [inline]
#include "k2000/logic/fx/CKHDRFxData.h"

#include <cstring>

#include "k2000/io/IKFile.h"
#include "k2000/logic/fx/CKHDRNodeFx.h"
#include "k2000/misc/Engine.h"
#include "k2000/services/CKSrvFx.h"

// 0x001be3c0 CKHDRFxData_Load
int32_t CKHDRFxData::Load(IKFile* file, int32_t type) {
    IKFxData::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        IKFile_ReadRef(file, &m_pHDRData);
        ReadF32LE(file, &m_unk0c);
    }
    return 1;
}

// 0x001be4e8 CKHDRFxData_RecursiveRegistration: IKFxData's (nothing), then for type 0 the HDR data's (vt+0x24).
void CKHDRFxData::RecursiveRegistration(int32_t type) {
    if (type == 0) m_pHDRData->RecursiveRegistration(0);
}

namespace {
// The unique-effect lookup the messages inline: the first unique effect whose class key is `key` (the array and its
// count read each time), or null.
CKHDRNodeFx* FindUniqueHDR(CKSrvFx* service, uint32_t key) {
    for (uint32_t i = 0; i < service->m_ui32UniqueFxArraySize; ++i) {
        IKSerializable* fx = service->m_apUniqueFxArray[i];
        if (static_cast<uint32_t>(fx->GetClassID() * 0x40 + fx->GetClassType()) == key) return static_cast<CKHDRNodeFx*>(fx);
    }
    return nullptr;
}
}  // namespace

// 0x001be708 CKHDRFxData_MessageProc: the message data's first word goes to +0x10 for 0x1b00, 0x1b01, 0x1b03 and 0x1b04.
// 0x1b00 / 0x1b03 start the effect (CKSrvFx::StartEffect inlined: the unique HDR effect, Vf50 is 1) with +0x14 bit 1
// cleared / set and return 0; 0x1b01 lets the effect fade out over +0x10 seconds (StopWithFadeTime) and returns 1; 0x1b04
// blends back from this data (StartBlendToSetting) and returns 0. Other messages return 1.
int32_t CKHDRFxData::MessageProc(uint16_t message, void* data) {
    CKSrvFx* service = static_cast<CKSrvFx*>(g_pEngine->m_srvFx);
    switch (message) {
    case 0x1b00:
    case 0x1b03:
        std::memcpy(&m_unk10, data, 4);
        m_unk14 = (message == 0x1b03) ? ((m_unk14 & ~2) | 2) : (m_unk14 & ~2);
        service->StartEffect(this, this);
        return 0;
    case 0x1b01: {
        std::memcpy(&m_unk10, data, 4);
        CKHDRNodeFx* fx = FindUniqueHDR(service, GetAssociatedFxClassIdentifier());  // vt+0x54
        if (fx != nullptr) fx->StopWithFadeTime(m_unk10);
        return 1;
    }
    case 0x1b04: {
        std::memcpy(&m_unk10, data, 4);
        CKHDRNodeFx* fx = FindUniqueHDR(service, GetAssociatedFxClassIdentifier());
        if (fx != nullptr) fx->StartBlendToSetting(this, this);
        return 0;
    }
    default:
        return 1;
    }
}
