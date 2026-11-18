// CKInputIconFxData.cpp - reconstructed original translation unit 0x1c34f0-0x1c4480 (GAME_TOC1, main_toc1), 19 functions, 17 live.
// Primary class: CKInputIconFxData  key 0x45cc  category Logic  size 0x48  vtable 0xb1d030
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1c34f0  CKInputIconFxData_Delete
//   [ ] 0x1c3540  CKInputIconFxData_Construct  [dead]
//   [x] 0x1c35c8  CKInputIconFxData_PostLoad
//   [x] 0x1c35d8  CKInputIconFxData_GetNodeClassKey
//   [ ] 0x1c35e0  RegisterCKInputIconFxDataClass
//   [ ] 0x1c3658  _GLOBAL__I_1c3658
//   [ ] 0x1c3668  CKInputIconFxData_Save
//   [x] 0x1c3690  CKInputIconFxData_RecursiveRegistration  (IKFxData's, nothing)
//   [x] 0x1c36b8  CKInputIconFxData_DeleteArray
//   [x] 0x1c3760  CKInputIconFxData_BaseDestructor  (C++ destructor chain)
//   [ ] 0x1c37a0  CKInputIconFxData_Construct_2  [dead]
//   [x] 0x1c3828  CKInputIconFxData_GetInfo  (the default)
//   [x] 0x1c3830  CKInputIconFxData_Destroy
//   [x] 0x1c3868  CKInputIconFxData_CreateArray
//   [x] 0x1c39c0  CKInputIconFxData_Create
//   [x] 0x1c3a70  CKInputIconFxData_Load
//   [x] 0x1c3da0  CKInputIconFxData_DeletingDestructor  (C++ deleting destructor)
//   [x] 0x1c3df8  CKInputIconFxData_Destructor  (C++ destructor: vtable stores only)
//   [x] 0x1c3e38  CKInputIconFxData_MessageProc
//
//   [ ] 0x9ac708  CKInputIconFxData_IsKindOfClass  [inline]
//   [x] 0x9ac740  CKInputIconFxData_GetClassType  [inline]
//   [x] 0x9ac748  CKInputIconFxData_GetClassID  [inline]
#include "k2000/logic/fx/CKInputIconFxData.h"

#include <cstring>

#include "k2000/hooks/IKHook.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/fx/CKInputIconNodeFx.h"
#include "k2000/math/Quat.h"
#include "k2000/misc/Engine.h"
#include "k2000/services/CKSrvFx.h"

// 0x001c39c0 CKInputIconFxData_Create, the inlined constructor, in its store order.
CKInputIconFxData::CKInputIconFxData() {
    m_unk14 = 1.0f;
    m_unk1c = 1.0f;
    m_unk33 = 0;
    m_unk0c = -1;
    m_unk30 = 0;
    m_unk31 = 0;
    m_unk32 = 0;
    m_unk08 = -1;
    m_unk10 = 0;
    m_unk18 = 1.0f;
    m_unk20 = 1.0f;
    m_unk34.x = 0.0f;  // stw 0
    m_unk24 = 10.0f;  // 0x41200000
    m_unk28 = 40.0f;  // 0x42200000
    m_unk2c = 0.0f;  // stw 0
    m_unk34.z = 0.0f;  // stw 0
    m_unk34.y = 0.0f;
    m_pTexture = nullptr;
}

// 0x001c3a70 CKInputIconFxData_Load
int32_t CKInputIconFxData::Load(IKFile* file, int32_t type) {
    IKFxData::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadS32LE(file, &m_unk08);
    ReadS32LE(file, &m_unk0c);
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(&m_unk14), 2);  // one 8-byte read
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(&m_unk1c), 2);  // one 8-byte read
    ReadF32LE(file, &m_unk24);
    ReadF32LE(file, &m_unk28);
    ReadF32LE(file, &m_unk2c);
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(&m_unk34), 3);  // one 12-byte read: +0x34, +0x38, +0x3c
    IKFile_ReadTextureRef(file, &m_pTexture, 1);
    ReadU8(file, &m_unk33);
    return 1;
}

// 0x001c3830 CKInputIconFxData_Destroy: the texture reference released (the pointer kept).
void CKInputIconFxData::Destroy() {
    if (m_pTexture != nullptr) TextureRef_Release(m_pTexture);  // RwTextureDestroy
}

namespace {
// The 0x1b00 payload: no sender is ported and its class is not known; the original reads a quaternion at its +0x10
// (_maybe a beacon or transform record). The 0x1b02 payload is a hook (its scene node m_pKGLObject, +0x1c) _maybe.
struct InputIconPlacement {
    uint8_t m_pad00[0x10];
    float m_quat[4];  // +0x10
};
}  // namespace

// 0x001c3e38 CKInputIconFxData_MessageProc: the data's effect is held in +0x44.
//  0x1b00: the message data is an object (null: 0); when no effect is held one is acquired (CKSrvFx::AcquireFx inlined:
//          reserved, owned by this data, started) and placed at the matrix of the object's quaternion (+0x10, position
//          0; the matrix flag 0x20000 cleared; UpdateWorldPosition); returns 0.
//  0x1b01: the held effect released (vt+0x58 StopAndRelease); returns 0.
//  0x1b02: as 0x1b01, then a new effect acquired and attached to the object's node (+0x1c; ApplyDisplayMode); returns 0.
//  Other messages return 1. When no effect could be acquired +0x44 is cleared.
int32_t CKInputIconFxData::MessageProc(uint16_t message, void* data) {
    void* object = nullptr;
    if (message == 0x1b01) {
        CKInputIconNodeFx* held = static_cast<CKInputIconNodeFx*>(m_pHeldFx);
        if (held == nullptr) return 0;
        held->StopAndRelease(this);  // vt+0x58
        m_pHeldFx = nullptr;
        return 0;
    }
    if (message == 0x1b02) {
        CKInputIconNodeFx* held = static_cast<CKInputIconNodeFx*>(m_pHeldFx);
        if (held != nullptr) {
            held->StopAndRelease(this);
            m_pHeldFx = nullptr;
        }
    } else {
        if (message != 0x1b00) return 1;
        std::memcpy(&object, data, sizeof(object));
        if (object == nullptr) return 0;
        if (m_pHeldFx != nullptr) return 0;
    }
    CKSrvFx* service = static_cast<CKSrvFx*>(g_pEngine->m_srvFx);
    CKInputIconNodeFx* fx = static_cast<CKInputIconNodeFx*>(service->AcquireFx(this, this));
    m_pHeldFx = fx;
    if (fx == nullptr) return 0;
    if (message == 0x1b00) {
        CMatrix34 matrix;
        Quat_ToMatrixNormalizing(static_cast<const InputIconPlacement*>(object)->m_quat, &matrix);
        matrix.m_ui32Flags &= ~0x20000u;
        static_cast<CKInputIconNodeFx*>(m_pHeldFx)->UpdateWorldPosition(&matrix);
        return 0;
    }
    std::memcpy(&object, data, sizeof(object));
    if (object == nullptr) return 0;
    IKSerializable* node = static_cast<IKHook*>(object)->m_pKGLObject;
    if (node == nullptr) return 0;
    fx->ApplyDisplayMode(node);
    return 0;
}
