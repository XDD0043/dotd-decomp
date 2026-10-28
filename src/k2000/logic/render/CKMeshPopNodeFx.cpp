// CKMeshPopNodeFx.cpp - reconstructed original translation unit 0x1c9338-0x1cbc50 (GAME_TOC1, main_toc1), 27 functions, 25 live.
// Primary class: CKMeshPopNodeFx  key 0xa24c  category Logic  size 0x38  vtable 0xb1d3c8
// Other owners: CKParticlesEffectFxData (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1c9338  CKMeshPopNodeFx_Delete
//   [ ] 0x1c9388  CKMeshPopNodeFx_InitMatrices_maybe  [dead]
//   [ ] 0x1c9428  CKMeshPopNodeFx_SetMatrixForOwner_maybe
//   [ ] 0x1c94f8  RegisterCKMeshPopNodeFxClass
//   [ ] 0x1c9570  _GLOBAL__I_1c9570
//   [ ] 0x1c9580  CKMeshPopNodeFx_ApplyAlphaCurve_maybe
//   [ ] 0x1c9728  CKMeshPopNodeFx_ApplyMoveUpdater_maybe
//   [ ] 0x1c97c0  CKMeshPopNodeFx_Save
//   [ ] 0x1c97e8  CKMeshPopNodeFx_RecursiveRegistration
//   [ ] 0x1c98a8  CKMeshPopNodeFx_Destroy
//   [x] 0x1c9900  CKMeshPopNodeFx_DeleteArray
//   [x] 0x1c99a8  CKMeshPopNodeFx_Create
//   [ ] 0x1c9a00  CKMeshPopNodeFx_SetUpDirForOwner_maybe
//   [ ] 0x1c9c08  CKMeshPopNodeFx_SetPositionForOwner_maybe
//   [ ] 0x1c9c60  FUN_001c9c60  [dead]
//   [ ] 0x1c9c70  CKMeshPopNodeFx_Stop
//   [ ] 0x1c9d90  CKMeshPopNodeFx_PlaceWithRandomYaw_maybe
//   [x] 0x1c9f90  CKMeshPopNodeFx_CreateArray
//   [x] 0x1ca048  CKMeshPopNodeFx_Load
//   [ ] 0x1ca108  CKMeshPopNodeFx_ScatterElementRandomOffset_maybe
//   [ ] 0x1ca730  CKMeshPopNodeFx_Start
//   [x] 0x1ca850  CKMeshPopNodeFx_PostLoad
//   [ ] 0x1ca978  CKMeshPopNodeFx_PlaceAtTarget_maybe
//   [ ] 0x1caf50  CKMeshPopNodeFx_TriggerPop_maybe
//   [ ] 0x1cb568  CKMeshPopNodeFx_SetActive_maybe
//   [ ] 0x1cb6e8  CKMeshPopNodeFx_Update
//   [ ] 0x1cbc48  CKParticlesEffectFxData_GetNodeClassKey
//
//   [ ] 0x9acbd0  CKMeshPopNodeFx_IsKindOfClass  [inline]
//   [x] 0x9acc10  CKMeshPopNodeFx_GetClassType  [inline]
//   [x] 0x9acc18  CKMeshPopNodeFx_GetClassID  [inline]
//   [ ] 0x9acc20  CKMeshPopNodeFx_GetFxData  [inline]
//   [ ] 0x9acc28  CKMeshPopNodeFx_SetFxData  [inline]
//   [ ] 0x9acc30  CKMeshPopNodeFx_Destruct  [inline]
//   [ ] 0x9acc50  CKMeshPopNodeFx_DeletingDestruct  [inline]
#include "k2000/logic/render/CKMeshPopNodeFx.h"

#include "k2000/io/IKFile.h"
#include "k2000/misc/Mat4.h"
#include "k2000/scenegraph/CNode.h"

// 0x001ca048 CKMeshPopNodeFx_Load
int32_t CKMeshPopNodeFx::Load(IKFile* file, int32_t type) {
    IKNodeFx::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) IKFile_ReadRef(file, &m_pMoveUpdater);
    return 1;
}

// The matrix the PostLoad stores: identity with flags 0x20003 (right/up/at diagonal 1.0f, the rest 0; the pads
// +0x1c/+0x2c/+0x3c are not written).
static void SetIdentityMatrixWithFlags(CMatrix34* m) {
    m->m_up.z = 0.0f;  // stw r0: the words of the original's zero stores, in the original's order
    m->m_right.z = 0.0f;
    m->m_right.y = 0.0f;
    m->m_at.y = 0.0f;
    m->m_at.x = 0.0f;
    m->m_up.x = 0.0f;
    m->m_pos.z = 0.0f;
    m->m_pos.y = 0.0f;
    m->m_pos.x = 0.0f;
    m->m_ui32Flags = 0x20003u;
    m->m_at.z = 1.0f;
    m->m_up.y = 1.0f;
    m->m_right.x = 1.0f;
}

// 0x001ca850 CKMeshPopNodeFx_PostLoad: IKNodeFx_PostLoad, the node's flags bit 2 (hidden: cleared, then set), two
// RwMatrixCreate_Thunk matrices for the level load (type 0), then both matrices identity with flags 0x20003 and
// the run-time words (TOC -0x1cb0 = 1.0f, -0x1cac = 3600.0f, -0x1ca8 = -1.0f).
int32_t CKMeshPopNodeFx::PostLoad(int32_t type) {
    IKNodeFx::PostLoad(type);
    if (m_pNode != nullptr) m_pNode->m_sgProperties = (m_pNode->m_sgProperties & 0xfffffffbu) | 4u;
    if (type == K_LEVEL_PLATEFORMS) {
        m_unk24 = RwMatrixCreate_Thunk();
        m_unk20 = RwMatrixCreate_Thunk();
    }
    m_unk1c = 0;
    m_unk2c = 0;
    SetIdentityMatrixWithFlags(m_unk24);
    SetIdentityMatrixWithFlags(m_unk20);
    m_unk34 = -1.0f;
    m_unk28 = 3600.0f;
    m_unk30 = 1.0f;
    return 1;
}
