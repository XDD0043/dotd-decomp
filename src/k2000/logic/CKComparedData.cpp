// CKComparedData.cpp - reconstructed original translation unit 0x232f30-0x2336a0 (GAME_TOC1, main_toc1), 11 functions, 11 live.
// Primary class: CKComparedData  key 0x234c  category Logic  size 0x18  vtable 0xb207f0
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x232f30  CKComparedData_Delete
//   [x] 0x232f80  CKComparedData_Destroy  (empty)
//   [x] 0x232f88  CKComparedData_RecursiveRegistration
//   [ ] 0x232fe8  RegisterCKComparedDataClass
//   [ ] 0x233060  _GLOBAL__I_233060
//   [x] 0x233070  CKComparedData_DeleteArray
//   [x] 0x233118  CKComparedData_Create
//   [x] 0x233150  CKComparedData_CreateArray
//   [ ] 0x2331e8  CKComparedData_Save
//   [x] 0x2331f0  CKComparedData_PostLoad
//   [x] 0x2332d0  CKComparedData_Load
//
//   [ ] 0x9b7350  CKComparedData_GetClassType  [inline]
//   [ ] 0x9b7358  CKComparedData_GetClassID  [inline]
//   [ ] 0x9b7360  KBase264C_IsKindOf  [inline]
//   [ ] 0x9b7380  CKComparedData_IsKindOfClass  [inline]
//   [ ] 0x9b73a0  CKComparedData_Destructor  [inline]
//   [ ] 0x9b73b8  KBase258C_DeletingDestructor  [inline]
//   [ ] 0x9b73e8  KBase258C_Destructor  [inline]
//   [ ] 0x9b73f8  KBase264C_DeletingDestructor  [inline]
//   [ ] 0x9b7438  KBase264C_Destructor  [inline]
//   [ ] 0x9b7450  CKComparedData_DeletingDestructor  [inline]
#include "k2000/logic/CKComparedData.h"

#include "k2000/io/IKFile.h"
#include "k2000/core/Stub.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/misc/Engine.h"

#include <cstdlib>

// 0x002331f0 CKComparedData_PostLoad (vt+0x30; type 0 = level load)
int32_t CKComparedData::PostLoad(int32_t type) {
    if (type == 0) {
        const uint32_t mode = (m_ba32Flags >> 2) & 3;
        if (mode == 0) {
            // vt+0x40 of the object with a 40-byte stack buffer and 0; the buffer is dropped (the
            // native GetInfo takes no arguments).
            if (std::getenv("DOTD_DBG_TRIG") != nullptr) {
                DOTD_LOG("trig operand %p obj=%p key=%x arg=%08x id=%08x", static_cast<void*>(this), static_cast<void*>(m_pObject),
                         (m_pObject->GetClassID() << 6) + m_pObject->GetClassType(), m_unk08, m_unk0c);
            }
            IKInfo info;
            info.m_ui32Id = m_unk0c;
            m_pObject->GetInfo(&info, kGetInfoValueAccessor);  // vt+0x40
            m_pfnAccessor = info.m_pfnAccessor;
            m_unk10 = 0;
        } else if (mode == 2) {
            // The first memory byte (big-endian high byte) of +0x08: its bit 0 is cleared.
            m_unk08 &= ~0x01000000u;
        }
    }
    return 1;
}

// 0x002332d0 CKComparedData_Load
int32_t CKComparedData::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadU32LE(file, &m_ba32Flags);
    const uint32_t mode = (m_ba32Flags >> 2) & 3;
    if (mode == 0) {
        IKFile_ReadRef(file, &m_pObject);
        ReadU32LE(file, &m_unk08);
        ReadU32LE(file, &m_unk0c);
        uint32_t unused = 0;  // read and dropped
        ReadU32LE(file, &unused);
        return 1;
    }
    if (mode == 2) {
        // A raw byte into the first (big-endian high) byte of +0x08; the other three keep their bytes.
        uint8_t b = 0;
        ReadU8(file, &b);
        m_unk08 = (m_unk08 & 0x00ffffffu) | (static_cast<uint32_t>(b) << 24);
        IKFile_ReadRef(file, &m_pObject);  // through a local, as the original
        return 1;
    }
    // mode 1 or 3: a typed constant.
    uint32_t constType = 0;
    ReadU32LE(file, &constType);
    if (constType == 0) {
        uint8_t b = 0;  // a byte stored into all four bytes of the word
        ReadU8(file, &b);
        m_ui32Value = static_cast<uint32_t>(b) * 0x01010101u;
    } else if (constType == 1 || constType == 2) {
        ReadU32LE(file, &m_ui32Value);  // an integer or a float
    } else if (constType == 3) {
        IKFile_ReadRef(file, &m_pObject);
    }
    return 1;
}

// 0x00232f88 CKComparedData_RecursiveRegistration (returns 1)
void CKComparedData::RecursiveRegistration(int32_t type) {
    if (type == 0) g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);  // vt+0x24
}
