// CBackgroundCopyRender.cpp - reconstructed original translation unit 0x92e00-0x935d0 (GAME_TOC1, main_toc1), 13 functions, 13 live.
// Primary class: CBackgroundCopyRender  key 0x4d0d  category Graphical  size 0x24  vtable 0xb16c90
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x92e00  CBackgroundCopyRender_Delete
//   [ ] 0x92e50  CBackgroundCopyRender_RecursiveRegistration
//   [ ] 0x92ee8  CBackgroundCopyRender_Save
//   [ ] 0x92ef0  RegisterCBackgroundCopyRenderClass
//   [ ] 0x92f68  _GLOBAL__I_92f68
//   [x] 0x92f78  CBackgroundCopyRender_DeleteArray
//   [x] 0x93020  CBackgroundCopyRender_Create
//   [x] 0x93078  CBackgroundCopyRender_vf58  (UpdateAndExtract)
//   [x] 0x93118  CBackgroundCopyRender_CreateArray
//   [x] 0x931d0  CBackgroundCopyRender_PostLoad
//   [x] 0x931e0  CBackgroundCopyRender_Draw  (Render)
//   [ ] 0x93410  CBackgroundCopyRender_Destroy
//   [x] 0x93438  CBackgroundCopyRender_Load
//
//   [x] 0x99c6a8  CBackgroundCopyRender_GetClassType  [inline]
//   [x] 0x99c6b0  CBackgroundCopyRender_GetClassID  [inline]
//   [x] 0x99c6b8  CBackgroundCopyRender_GetSerializationFlags  [inline]
//   [x] 0x99c6c0  IScreenFx_Load  [inline]
//   [ ] 0x99c6e8  IScreenFx_vf28  [inline]
//   [x] 0x99c710  IScreenFx_vf10  [inline]
//   [x] 0x99c738  IScreenFx_vf70  [inline]  (CanBeUpdated, IScreenFx.h)
//   [x] 0x99c758  CBackgroundCopyRender_IsKindOfClass  [inline]
//   [ ] 0x99c790  IScreenFx_DeletingDestructor  [inline]
//   [ ] 0x99c7d8  CBackgroundCopyRender_DeletingDestructor  [inline]
//   [ ] 0x99c820  IScreenFx_vf0  [inline]
//   [ ] 0x99c840  CBackgroundCopyRender_Destructor  [inline]
#include "k2000/graphical/render/CBackgroundCopyRender.h"

#include "Renderware/rwcore/RwCamera.h"
#include "Renderware/rwcore/RwTexture.h"
#include "k2000/cameras/CameraContext.h"
#include "k2000/graphical/memory/CKPBuffer.h"
#include "k2000/graphical/render/CPostRenderingFx.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKCoreManager.h"
#include "k2000/managers/CKGraphic.h"
#include "k2000/misc/Engine.h"
#include "k2000/render/CRenderer.h"
#include "k2000/render/CShaderManagerPSGL.h"
#include "k2000/render/MeshShaderPassState.h"

// 0x00093078 CBackgroundCopyRender_vf58 (UpdateAndExtract): while active (+0x21 and +0x20) a frame request and the
// object into stage 4 (+0x10 of the stage array: the last stage of the far group).
void CBackgroundCopyRender::UpdateAndExtract(float, RenderQueue** stages, IKTime*, RwCamera*, int32_t) {
    if (m_unk21 != 0 && m_unk20 != 0) {
        CKPBuffer::AddFrameRequest();
        stages[4]->Add(this);
    }
}

// 0x000931d0 CBackgroundCopyRender_PostLoad: the sorting coefficient 0.
int32_t CBackgroundCopyRender::PostLoad(int32_t) {
    m_fSortingCoef = 0.0f;
    return 1;
}

// 0x000931e0 CBackgroundCopyRender_Draw (vt+0x5c), active and with the post effects (graphic caps 0x400): the far
// group's picture copied by the CKPBuffer (vt+0x5c) into the full-size shared raster (on the depth of field path with the
// main camera on the final colour meanwhile), the "backbuffer" texture (which shows that raster) bound on unit 6 for the
// far-texture shading of the main group, a frame request done.
void CBackgroundCopyRender::Render() {
    if (m_unk21 == 0 || (g_pEngine->m_graphic->m_baHardwareCaps & 0x400) == 0 || m_unk20 == 0) return;
    const CPostRenderingFx* postFx = static_cast<const CPostRenderingFx*>(g_pEngine->m_coreManager->GetObjectByClassKey(0x38d));
    if (postFx == nullptr) {
        m_unk18->Render();
    } else {
        const bool depthOfField = (g_pEngine->m_graphic->m_baHardwareCaps & 0x200) != 0 && g_pShaderManager->m_bShadersEnabled != 0 &&
                                  g_pShaderManager->m_i32ProfileMode == 6 && (postFx->m_BitProperties & 0x400) != 0;
        CameraContext* context = static_cast<CameraContext*>(g_pEngine->m_cameraContext);
        if (depthOfField) {
            RwCameraEndUpdate(context->m_pMainCamera);
            context->m_pMainCamera->frameBuffer = context->m_pFinalColorRaster;
            BeginRenderCameraUpdate(context->m_pMainCamera);
        }
        m_unk18->Render();
        if ((g_pEngine->m_graphic->m_baHardwareCaps & 0x200) != 0 && g_pShaderManager->m_bShadersEnabled != 0 &&
            g_pShaderManager->m_i32ProfileMode == 6 && (postFx->m_BitProperties & 0x400) != 0) {
            RwCameraEndUpdate(context->m_pMainCamera);
            context->m_pMainCamera->frameBuffer = context->m_unk10;
            BeginRenderCameraUpdate(context->m_pMainCamera);
        }
    }
    BindTextureOnUnit(static_cast<RwTexture*>(CKPBuffer::m_spBackBufferTexture), 6);
    CKPBuffer::m_sui16FrameRequests = static_cast<uint16_t>(CKPBuffer::m_sui16FrameRequests - 1);
}

// 0x00093020 CBackgroundCopyRender_Create: the inlined IRendableObject/IScreenFx part, in the original's
// store order. +0x0c and the class's own fields are left as they are.
CBackgroundCopyRender::CBackgroundCopyRender() {
    m_pLightSet = nullptr;
    m_pNextAccumulatedObject = nullptr;
    m_BitProperties = 0;
    m_pPriorityParent = 0;
}

// 0x00093438 CBackgroundCopyRender_Load
int32_t CBackgroundCopyRender::Load(IKFile* file, int32_t type) {
    IScreenFx::Load(file, type);  // the original calls IRendableObject_Load (IScreenFx_Load inlined)
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadF32LE(file, &m_unk1c);
    ReadU8(file, &m_unk20);
    ReadU8(file, &m_unk21);
    IKFile_ReadRef(file, &m_unk18);
    return 1;
}

// 0x0099c738 IScreenFx_vf70 (IScreenFx::CanBeUpdated, the out-of-line copy listed above): not while the renderer skips
// the world stages (its flags' bit 1).
int32_t IScreenFx::CanBeUpdated() { return (g_pEngine->m_graphic->m_renderer->m_bitProperties & 2) == 0 ? 1 : 0; }
