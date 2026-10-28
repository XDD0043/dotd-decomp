// CKPointLightNodeFx.cpp - reconstructed original translation unit 0x1cfb08-0x1d0470 (GAME_TOC1, main_toc1), 14 functions, 14 live.
// Primary class: CKPointLightNodeFx  key 0xaa4c  category Logic  size 0x2c  vtable 0xb1d5e8
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1cfb08  CKPointLightNodeFx_Delete
//   [ ] 0x1cfb58  CKPointLightNodeFx_RecursiveRegistration
//   [ ] 0x1cfbb0  RegisterCKPointLightNodeFxClass
//   [ ] 0x1cfc28  _GLOBAL__I_1cfc28
//   [x] 0x1cfc38  CKPointLightNodeFx_PostLoad
//   [x] 0x1cfc98  CKPointLightNodeFx_Load
//   [ ] 0x1cfd58  CKPointLightNodeFx_Save
//   [ ] 0x1cfd80  CKPointLightNodeFx_Destroy
//   [x] 0x1cfda8  CKPointLightNodeFx_DeleteArray
//   [x] 0x1cfe48  CKPointLightNodeFx_Create
//   [ ] 0x1cfea0  CKPointLightNodeFx_Start
//   [ ] 0x1d0130  CKPointLightNodeFx_Stop
//   [x] 0x1d0218  CKPointLightNodeFx_CreateArray
//   [ ] 0x1d02c8  CKPointLightNodeFx_Update
//
//   [ ] 0x9acf70  CKPointLightNodeFx_IsKindOfClass  [inline]
//   [x] 0x9acfb0  CKPointLightNodeFx_GetClassType  [inline]
//   [x] 0x9acfb8  CKPointLightNodeFx_GetClassID  [inline]
//   [ ] 0x9acfc0  CKPointLightNodeFx_GetFxData  [inline]
//   [ ] 0x9acfc8  CKPointLightNodeFx_SetFxData  [inline]
//   [ ] 0x9acfd0  CKPointLightNodeFx_Destruct  [inline]
//   [ ] 0x9acff0  CKPointLightNodeFx_DeletingDestruct  [inline]
#include "k2000/logic/render/CKPointLightNodeFx.h"

#include "k2000/io/IKFile.h"
#include "k2000/scenegraph/CSGPointLight.h"

// 0x001cfc98 CKPointLightNodeFx_Load
int32_t CKPointLightNodeFx::Load(IKFile* file, int32_t type) {
    IKNodeFx::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) IKFile_ReadRef(file, &m_pPointLight);
    return 1;
}

// 0x001cfc38 CKPointLightNodeFx_PostLoad: IKNodeFx_PostLoad; for the level type the light's byte at +0x18 (the file's
// last byte) is set to the type (0: stb r31).
int32_t CKPointLightNodeFx::PostLoad(int32_t type) {
    IKNodeFx::PostLoad(type);
    if (type == K_LEVEL_PLATEFORMS && m_pPointLight != nullptr) {
        static_cast<CSGPointLight*>(m_pPointLight)->m_unk18 = static_cast<uint8_t>(type);
    }
    return 1;
}
