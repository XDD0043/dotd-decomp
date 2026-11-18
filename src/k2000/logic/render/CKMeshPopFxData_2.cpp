// CKMeshPopFxData_2.cpp - reconstructed original translation unit 0x1c8060-0x1c9338 (GAME_TOC1, main_toc1), 8 functions, 8 live.
// Primary class: CKMeshPopFxData  key 0xa28c  category Logic  size 0x64  vtable 0xb1d360
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1c8060  CKMeshPopFxData_GetNodeClassKey
//   [x] 0x1c8070  CKMeshPopFxData_PostLoad
//   [ ] 0x1c8090  CKMeshPopFxData_Save
//   [x] 0x1c80b8  CKMeshPopFxData_RecursiveRegistration
//   [x] 0x1c8160  CKMeshPopFxData_GetInfo  (IKSerializable's: returns 1)
//   [x] 0x1c8168  CKMeshPopFxData_Destroy  (empty: IKSerializable's)
//   [x] 0x1c8170  CKMeshPopFxData_Load
//   [x] 0x1c8700  CKMeshPopFxData_MessageProc
//
//   [ ] 0x9acae8  CKMeshPopFxData_IsKindOfClass  [inline]
//   [x] 0x9acb28  CKMeshPopFxData_GetClassType  [inline]
//   [x] 0x9acb30  CKMeshPopFxData_GetClassID  [inline]
//   [ ] 0x9acb38  CKMeshPopFxData_DeletingDestructor  [inline]
//   [ ] 0x9acb90  CKMeshPopFxData_Destructor  [inline]
#include "k2000/logic/render/CKMeshPopFxData.h"

#include "k2000/fx/IKFx.h"
#include "k2000/hooks/IKHook.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/ai/CKMarkerBeacon.h"
#include "k2000/logic/render/CKMeshPopNodeFx.h"
#include "k2000/math/Quat.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/CNode.h"
#include "k2000/services/CKSrvFx.h"

#include <cstring>

// 0x001c8170 CKMeshPopFxData_Load
int32_t CKMeshPopFxData::Load(IKFile* file, int32_t type) {
    IKFxData::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        IKFile_ReadRef(file, &m_unk10);
        ReadU8(file, &m_unk18);
        ReadU8(file, &m_unk19);
        ReadF32LE(file, &m_unk1c);
        ReadF32LE(file, &m_unk20);
        ReadF32LE(file, &m_unk24);
        ReadF32LE(file, &m_unk2c);
        ReadF32LE(file, &m_unk30);
        ReadF32LE(file, &m_unk34);
        ReadF32LE(file, &m_unk40);
        ReadS32LE(file, &m_unk38);
        ReadS32LE(file, &m_unk3c);
    }
    // The rest is read whatever the type.
    ReadU8(file, &m_unk44);
    ReadF32LE(file, &m_unk48);
    IKFile_ReadRef(file, &m_unk14);
    ReadF32LE(file, &m_unk28);
    ReadU8(file, &m_unk4c);
    ReadF32LE(file, &m_unk50);
    uint32_t words[3];
    ReadU32LEWords(file, words, 3);  // one 12-byte read
    std::memcpy(m_unk54, words, sizeof m_unk54);
    return 1;
}

// 0x001c8070 CKMeshPopFxData_PostLoad (every type)
int32_t CKMeshPopFxData::PostLoad(int32_t /*type*/) {
    m_pReservedFx = nullptr;
    m_unk08 = nullptr;
    m_unk0c = nullptr;
    return 1;
}

// 0x001c80b8 CKMeshPopFxData_RecursiveRegistration (KStub_Return1_1d8340 first: nothing)
void CKMeshPopFxData::RecursiveRegistration(int32_t type) {
    if (type != 0) return;
    m_unk10->RecursiveRegistration(0);  // vt+0x24
    m_unk14->RecursiveRegistration(0);
}

// 0x001c8700 CKMeshPopFxData_MessageProc. The node lookups are CKSrvFx's inlined StartEffect (a non-repeating data)
// and the reserving AcquireFx (a repeating one, kept in +0x60; nothing while it holds one).
int32_t CKMeshPopFxData::MessageProc(uint16_t message, void* data) {
    if (message == 0x1b01) {
        if (m_pReservedFx != nullptr) {
            m_pReservedFx->StopAndRelease(this);  // vt+0x58
            m_pReservedFx = nullptr;
        }
        return 0;
    }
    if (message != 0x1b00 && message != 0x1b02) return 1;
    IKSerializable* object = *static_cast<IKSerializable* const*>(data);
    if (object == nullptr) return 0;
    CKSrvFx* service = static_cast<CKSrvFx*>(g_pEngine->m_srvFx);
    IKFx* fx;
    if (m_unk18 == 0) {
        fx = service->StartEffect(this, this);
    } else {
        if (m_pReservedFx != nullptr) return 0;
        fx = service->AcquireFx(this, this);
        m_pReservedFx = fx;
    }
    if (fx == nullptr) return 0;
    CKMeshPopNodeFx* node = static_cast<CKMeshPopNodeFx*>(fx);
    if (message == 0x1b00) {
        // The marker's orientation (+0x10) and position (+0x04), read through the members (x64).
        const CKMarkerBeacon* marker = static_cast<const CKMarkerBeacon*>(object);
        float q[4];
        std::memcpy(q, marker->m_qOrientation, sizeof q);
        CMatrix34 matrix;
        Quat_ToMatrixNormalizing(q, &matrix);  // 0x00241d78
        const CVector3 p = marker->m_v3Position;
        matrix.m_pos.z = p.z;
        matrix.m_pos.x = p.x;
        matrix.m_pos.y = p.y;
        matrix.m_ui32Flags &= 0xfffdffffu;
        node->SetMatrixForOwner(this, &matrix);  // 0x001c9428
    } else {
        IKSerializable* kgl = static_cast<IKHook*>(object)->m_pKGLObject;  // +0x1c
        if (kgl->IsKindOfClass(0xcb) != 0) {  // a CNode
            m_unk08 = static_cast<CNode*>(kgl);
            m_unk0c = nullptr;
        }
    }
    node->SetActive(this, 1);  // 0x001cb568
    return 0;
}
