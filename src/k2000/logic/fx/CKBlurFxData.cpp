// CKBlurFxData.cpp - reconstructed original translation unit 0x571348-0x571be0 (GAME_TOC2, main_toc2), 7 functions, 7 live.
// Primary class: CKBlurFxData  key 0x28c  category Logic  size ?  vtable 0xb2dd18
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x571348  CKBlurFxData_Destroy
//   [x] 0x5713c0  CKBlurFxData_PostLoad  (= the inherited slot)
//   [x] 0x5713e8  CKBlurFxData_RecursiveRegistration
//   [x] 0x571460  CKBlurFxData_MessageProc
//   [x] 0x5717d8  CKBlurFxData_GetInfo  (returns 1: the default slot)
//   [x] 0x5717e0  CKBlurFxData_Load
//   [ ] 0x5719e8  CKBlurFxData_Save
//
//   [ ] 0x9cac28  CKBlurFxData_IsKindOfClass  [inline]
//   [x] 0x9cac60  CKBlurFxData_GetClassType  [inline]
//   [x] 0x9cac68  CKBlurFxData_GetClassID  [inline]
//   [ ] 0x9cac70  CKBlurFxData_Destructor  [inline]
//   [ ] 0x9cacb0  CKBlurFxData_DeletingDestructor  [inline]
#include "k2000/logic/fx/CKBlurFxData.h"

#include "k2000/io/IKFile.h"
#include "k2000/fx/IKFx.h"
#include "k2000/misc/Engine.h"
#include "k2000/services/CKSrvFx.h"

// 0x005717e0 CKBlurFxData_Load
int32_t CKBlurFxData::Load(IKFile* file, int32_t type) {
    IKFxData::Load(file, type);  // through TocBridge_IKFxData_Load
    if (type == K_LEVEL_PLATEFORMS) {
        IKFile_ReadRef(file, &m_unk08);
        ReadU8(file, &m_unk0c);
        ReadU8(file, &m_unk18);
        ReadF32LE(file, &m_unk10);
        m_unk14 = new Key[m_unk18];
        ReadU32LEWords(file, reinterpret_cast<uint32_t*>(m_unk14), static_cast<uint32_t>(m_unk18) * 2);
    }
    m_unk1c = 0;
    return 1;
}

// 0x00571348 CKBlurFxData_Destroy
void CKBlurFxData::Destroy() {
    m_unk08->Destroy();  // vt+0x10
    if (m_unk14 != nullptr) {
        delete[] m_unk14;  // TocBridge_OperatorDeleteArray(m_unk14 - 4): the count cookie
        m_unk14 = nullptr;
    }
}

// 0x005713e8 CKBlurFxData_RecursiveRegistration
void CKBlurFxData::RecursiveRegistration(int32_t type) {
    IKFxData::RecursiveRegistration(type);  // KStub_Return1_1d8340
    if (type == 0) m_unk08->RecursiveRegistration(0);  // vt+0x24
}

// 0x00571460 CKBlurFxData_MessageProc
int32_t CKBlurFxData::MessageProc(uint16_t message, void* /*data*/) {
    if (message == 0x1b01) {
        if (m_unk1c != nullptr) {
            m_unk1c->StopAndRelease(this);  // vt+0x58
            m_unk1c = nullptr;
        }
        return 0;
    }
    if (message == 0x1b03) return 0;
    if (message != 0x1b00) return 1;
    if (m_unk1c != nullptr) {
        m_unk1c->StopAndRelease(this);  // vt+0x58
        m_unk1c = nullptr;
    }
    m_unk1c = static_cast<CKSrvFx*>(g_pEngine->m_srvFx)->AcquireFx(this, this);
    return 0;
}
