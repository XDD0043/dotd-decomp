// CKGraphic.cpp - reconstructed original translation unit 0x59508-0x5ac10 (GAME_TOC1, main_toc1), 61 functions, 52 live.
// Primary class: CKGraphic  key 0x80  category Manager  size 0x30  vtable 0xb15580
// Other owners: ElbFS (4), Graphics (3), RwEngine (2), BindTextureOnUnit (1), Rw (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x59508  CKGraphic_Delete
//   [x] 0x59558  CKGraphic_Construct  [dead]
//   [ ] 0x59590  CKGraphic_Construct_2  [dead]
//   [ ] 0x595c8  CKGraphic_PreUpdate
//   [ ] 0x595d0  CKGraphic_PostUpdate
//   [ ] 0x595d8  KStub_Nop_595d8
//   [ ] 0x595e0  CKGraphic_SectorUnload
//   [ ] 0x595e8  KStub_Return1_595e8  [dead]
//   [x] 0x595f0  KStub_Return0_595f0
//   [x] 0x595f8  Graphics_GetScreenOffset_maybe
//   [ ] 0x59610  KStub_Nop_59610  [dead]
//   [ ] 0x59618  KStub_Nop_59618
//   [ ] 0x59620  KStub_Return1_59620  [dead]
//   [ ] 0x59628  KStub_Return0_59628  [dead]
//   [ ] 0x59630  FUN_00059630  [dead]
//   [ ] 0x596a8  CKGraphic_RecursiveRegistration
//   [ ] 0x596b0  CKGraphic_GetRwInitParamsHalf0_maybe
//   [ ] 0x596c0  CKGraphic_DestroyGame
//   [x] 0x596c8  CKGraphic_DestroyLocalizedData
//   [ ] 0x59718  FUN_00059718  [dead]
//   [ ] 0x59790  CKGraphic_DeleteArray
//   [ ] 0x59838  RegisterCKGraphicClass
//   [ ] 0x598b0  _GLOBAL__I_598b0
//   [ ] 0x598c0  BindTextureOnUnit_maybe
//   [ ] 0x59968  CKGraphic_UpdateSceneWorldMatrices_maybe
//   [x] 0x59990  Rw_PurgeFreeLists_maybe
//   [ ] 0x599c0  CKGraphic_CreateRenderer
//   [ ] 0x59a60  Graphics_GetCurrentVideoMode_maybe
//   [ ] 0x59a88  Graphics_GetNumVideoModes_maybe
//   [ ] 0x59ab0  RwEngine_IsCurrentVideoModeExclusive_maybe
//   [ ] 0x59af0  RwEngine_SelectVideoMode0_maybe
//   [ ] 0x59b28  CKGraphic_AttachRwPlugins_maybe
//   [ ] 0x59c00  CKGraphic_Update
//   [ ] 0x59c40  CKGraphic_Start
//   [ ] 0x59c88  CKGraphic_DestroyModule
//   [ ] 0x59e48  CKGraphic_Resume
//   [ ] 0x59e78  CKGraphic_Pause
//   [x] 0x59ea8  CKGraphic_PostSectorUnload
//   [x] 0x59ed8  CKGraphic_PreSectorLoaded
//   [ ] 0x59f08  CKGraphic_RefreshFrameBuffersIfResized_maybe
//   [x] 0x59f58  CKGraphic_FindNonRecreableInstances
//   [x] 0x5a128  CKGraphic_Stop
//   [x] 0x5a180  CKGraphic_UpdateLocalizedData
//   [ ] 0x5a208  CKGraphic_MessageProc
//   [ ] 0x5a258  CKGraphic_Save
//   [x] 0x5a338  CKGraphic_Load
//   [x] 0x5a530  CKGraphic_PostLoad
//   [x] 0x5a5c8  CKGraphic_Destroy
//   [ ] 0x5a6a8  CKGraphic_CreateArray
//   [ ] 0x5a780  CKGraphic_Create
//   [ ] 0x5a7e8  CKGraphic_InitializeModule
//   [ ] 0x5aa88  CKGraphic_Destructor
//   [ ] 0x5aaa8  CKGraphic_Destructor_2  [dead]
//   [ ] 0x5aac8  CKGraphic_DeletingDestructor
//   [ ] 0x5ab10  ElbFS_FileClose
//   [ ] 0x5ab20  ElbFS_FileRead
//   [ ] 0x5ab68  ElbFS_FileWrite
//   [ ] 0x5abb0  KStub_Return1_5abb0
//   [ ] 0x5abb8  KStub_Return0_5abb8
//   [ ] 0x5abc0  ElbFS_FileIsEOF
//   [ ] 0x5ac08  KStub_Return1_5ac08
//
//   [ ] 0x996758  CKGraphic_GetClassType  [inline]
//   [ ] 0x996760  CKGraphic_GetClassID  [inline]
//   [ ] 0x996768  CKGraphic_SectorLoaded  [inline]
//   [ ] 0x9969a8  CKGraphic_IsKindOfClass  [inline]
//   [ ] 0x9969e0  HashTableStr_DeletingDestructor_2  [inline]
//   [ ] 0x996b78  HashTableU32_DeletingDestructor_4  [inline]
//   [ ] 0x996c98  HashTableU32_Destructor_4  [inline]
//   [ ] 0x996db8  HashTableStr_Destructor_2  [inline]
#include "k2000/managers/CKGraphic.h"

#include "k2000/graphical/CSpawnManager.h"
#include "k2000/graphical/system/CVideoManager.h"
#include "k2000/graphical/ui/CKFlashManager.h"
#include "k2000/graphical/ui/CManager2d.h"
#include "k2000/io/IKFile.h"
#include "k2000/misc/Engine.h"
#include "k2000/render/CRenderer.h"
#include "k2000/render/CShaderManagerPSGL.h"
#include "k2000/render/TextureBank.h"
#include "k2000/cameras/CameraContext.h"

// 0x00059f58 CKGraphic_FindNonRecreableInstances
uint8_t CKGraphic::FindNonRecreableInstances(int32_t category, uint32_t id, uint32_t /*count*/, void* out) {
    IKSerializable** slot = static_cast<IKSerializable**>(out);
    if (category == kCategoryNode) {
        if (id != 5) return 0;
        *slot = m_renderer->m_cameraContext->m_pCamera;  // camera context +0x2c (the IKCamera)
        return 1;
    }
    if (category != kCategoryGraphical) return 0;
    switch (id) {
    case 3: *slot = m_renderer->m_cloneManager; return 1;
    case 8: *slot = m_animationManager; return 1;
    case 0x10: *slot = m_renderer->m_manager2d; return 1;
    case 0x11: *slot = m_renderer->m_manager2d->m_menuManager; return 1;
    case 0x1a: *slot = m_renderer->m_backgroundManager; return 1;
    case 0x1c: *slot = m_renderer->m_flashManager; return 1;
    case 0x24: *slot = m_renderer->m_lightManager; return 1;
    case 0x27: *slot = m_renderer->m_videoManager; return 1;
    case 0x2e: *slot = m_renderer->m_spawnManager; return 1;
    default: return 0;
    }
}

// 0x00059558 CKGraphic_Construct (the same stores inlined in CKGraphic_Create 0x5a780)
CKGraphic::CKGraphic() {
    m_unk20 = nullptr;
    m_pTextureManager = nullptr;
    m_animationManager = nullptr;
    m_renderer = nullptr;
    m_baHardwareCaps = 0;
    m_i32XScreenOffset = 0;
    m_i32YScreenOffset = 0;
    m_unk24 = 0;
}

// 0x0005a338 CKGraphic_Load. The game file (type 1) only feeds the shader manager; the other types feed
// the renderer, the texture bank and the shader manager, and a level (type 0) adds an optional texture.
int32_t CKGraphic::Load(IKFile* file, int32_t type) {
    if (type == 1) {
        g_pShaderManager->Load(file, 1);
        return 1;
    }
    m_renderer->Load(file, type);
    m_pTextureManager->Load(file, type);
    g_pShaderManager->Load(file, type);
    if (type != 0) return 1;
    uint8_t hasTexture = 0;
    ReadU8(file, &hasTexture);
    if (hasTexture == 0) {
        m_pFogTexture = nullptr;
        return 1;
    }
    IKFile_ReadTextureRef(file, &m_pFogTexture, 1);
    return 1;
}

// 0x0005a530 CKGraphic_PostLoad
int32_t CKGraphic::PostLoad(int32_t type) {
    if (type != 1) {
        m_renderer->PostLoad(type);
        m_pTextureManager->PostLoad(type);
    }
    return 1;
}

// 0x0005a5c8 CKGraphic_Destroy: the texture bank released, the renderer's level data dropped, the shader
// manager's vt+0x10 (nothing) and the level's texture released.
void CKGraphic::Destroy() {
    if (m_pTextureManager != nullptr) m_pTextureManager->Destroy();  // vt+0x08
    if (m_renderer != nullptr) m_renderer->Destroy();
    if (g_pShaderManager != nullptr) g_pShaderManager->Destroy();
    if (m_pFogTexture != nullptr) TextureRef_Release(m_pFogTexture);  // RwTextureDestroy
}

// 0x0005a180 CKGraphic_UpdateLocalizedData: the 2D manager's localisation events (vt+0x78: fonts, then
// texts), then CVideoManager_ForEachVideoNopHook_maybe on the renderer's video manager (+0xb4), which does
// nothing.
void CKGraphic::UpdateLocalizedData() {
    g_pEngine->m_manager2d->BroadcastLocalisationEvents();
}

// 0x000596c8 CKGraphic_DestroyLocalizedData
void CKGraphic::DestroyLocalizedData() { CManager2d_UnloadLocalizedFonts(g_pEngine->m_manager2d); }

// (0x595f0 KStub_Return0_595f0 is CKGraphic::SetScreenOffset in the header.)
// 0x000595f8 Graphics_GetScreenOffset_maybe
void CKGraphic::GetScreenOffset(int32_t* x, int32_t* y) {
    *x = m_i32XScreenOffset;
    *y = m_i32YScreenOffset;
}

// 0x00059990 Rw_PurgeFreeLists_maybe. The remake's RenderWare objects live on the host heap: there are no
// RW free lists to purge and no resource arena (RwResourcesEmptyArena) to empty.
void Rw_PurgeFreeLists(CKGraphic* /*graphic*/) {}



// 0x0005a128 CKGraphic_Stop: every video stopped, the flash interfaces hidden, the spawn manager's shake
// caches stopped (renderer +0xb4, +0xb0, +0xb8).
void CKGraphic::Stop() {
    m_renderer->m_videoManager->StopAllVideos();
    static_cast<CKFlashManager*>(m_renderer->m_flashManager)->Stop();
    static_cast<CSpawnManager*>(m_renderer->m_spawnManager)->StopAllShakeCaches();
}

// 0x00059ed8 CKGraphic_PreSectorLoaded
void CKGraphic::PreSectorLoaded(int32_t sector) {
    static_cast<CSpawnManager*>(m_renderer->m_spawnManager)->StartPoolShakeCaches(sector);
}

// 0x00059ea8 CKGraphic_PostSectorUnload: calls 0xb8e20 on the spawn manager, which only returns.
void CKGraphic::PostSectorUnload(int32_t /*sector*/) {}
