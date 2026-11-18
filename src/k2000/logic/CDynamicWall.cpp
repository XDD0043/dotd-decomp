// CDynamicWall.cpp - reconstructed original translation unit 0x1a3920-0x1a3e90 (GAME_TOC1, main_toc1), 11 functions, 11 live.
// Primary class: CDynamicWall  key 0x54c  category Logic  size 0x68  vtable 0xb1c130
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1a3920  CDynamicWall_Delete  (DOTD_DECLARE_FACTORIES(CDynamicWall): the virtual deleting destructor)
//   [x] 0x1a3970  CDynamicWall_RecursiveRegistration
//   [ ] 0x1a39d8  CDynamicWall_Save
//   [ ] 0x1a39e0  RegisterCDynamicWallClass
//   [ ] 0x1a3a58  _GLOBAL__I_1a3a58
//   [x] 0x1a3a68  CDynamicWall_RefreshTransform_maybe  (CDynamicWall::Update)
//   [x] 0x1a3b38  CDynamicWall_Load
//   [x] 0x1a3cb0  CDynamicWall_FreeGeometry  (CDynamicWall::MyDestroy)
//   [x] 0x1a3d08  CDynamicWall_DeleteArray  (DOTD_DECLARE_FACTORIES: delete[] of 0x68-byte elements)
//   [x] 0x1a3da8  CDynamicWall_Create  (DOTD_DECLARE_FACTORIES: new, the two vtable stores)
//   [x] 0x1a3df0  CDynamicWall_CreateArray  (DOTD_DECLARE_FACTORIES: new[], the stride written)
//
//   [ ] 0x9aac70  CDynamicWall_IsKindOfClass  [inline]
//   [ ] 0x9aaca8  CDynamicWall_GetClassType  [inline]
//   [ ] 0x9aacb0  CDynamicWall_GetClassID  [inline]
//   [ ] 0x9aacb8  CDynamicWall_GetSerializationFlags  [inline]
//   [ ] 0x9aacc0  CDynamicWall_DeletingDestructor  [inline]
//   [ ] 0x9aad08  CDynamicWall_Destructor  [inline]
#include "k2000/logic/CDynamicWall.h"

#include "Renderware/rwcore/RwCamera.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/math/CBBox.h"
#include "k2000/misc/CKQuadtreeAgent.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/Mat4.h"
#include "k2000/scenegraph/CSGMovable.h"

CDynamicWall::CDynamicWall() {}
CDynamicWall::~CDynamicWall() {}

namespace {

}  // namespace

// 0x001a3970 CDynamicWall_RecursiveRegistration
void CDynamicWall::RecursiveRegistration(int32_t type) {
    if (static_cast<uint32_t>(type - 4) > 3u) g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);  // vt+0x24
}

// 0x001a3a68 CDynamicWall_RefreshTransform_maybe
void CDynamicWall::Update(uint8_t updateIndex) {
    if (m_ui8UpdateIndex == updateIndex) return;
    m_ui8UpdateIndex = updateIndex;
    const CMatrix34* parentLtm =
        reinterpret_cast<const CMatrix34*>(&static_cast<CSGMovable*>(m_pParent)->m_pRwFrame->ltm);  // frame +0x50
    Mat4_Multiply(m_pWorldMatrix, m_pLocalMatrix, parentLtm);  // 0x0023f788
    Mat4_Invert(m_pInvertedWorldMatrix, m_pWorldMatrix);       // 0x0023f878
    BBox_TransformByMatrix(reinterpret_cast<CBBox*>(m_AABB), reinterpret_cast<const CBBox*>(m_OBB), m_pWorldMatrix);  // 0x0023bce0
    if (m_unk04 != nullptr) UpdateQuadtreeBounds();  // 0x001a6bc0
}

// 0x001a3b38 CDynamicWall_Load
int32_t CDynamicWall::Load(IKFile* file, int32_t type) {
    CWall::Load(file, type);  // 0x001a5eb8
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(m_OBB), 6);
    IKFile_ReadRef(file, &m_pParent);
    m_pLocalMatrix = RwMatrixCreate_Thunk();  // 0x0023fa68
    CMatrix34_LoadMatrix(m_pLocalMatrix, file);
    m_ui8UpdateIndex = 100;
    return 1;
}

// 0x001a3cb0 CDynamicWall_FreeGeometry
void CDynamicWall::MyDestroy() {
    CWall::MyDestroy();  // 0x001a6080
    if (m_pLocalMatrix != nullptr) {
        RwMatrixDestroy_Thunk(m_pLocalMatrix);  // 0x0023f968
        m_pLocalMatrix = nullptr;
    }
    m_pParent = nullptr;
}
