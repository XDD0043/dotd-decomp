// CManager2d.cpp - reconstructed original translation unit 0x61ab8-0x64208 (GAME_TOC1, main_toc1), 51 functions, 39 live.
// Primary class: CManager2d  key 0x40d  category Graphical  size 0xa88  vtable 0xb15b98
// Other owners: UI2d (4), Font (1), SetUIOverlayRenderStates (1), EnqueueUIManagerRenderStages (1), DrawUIManagerScenesAndMenus (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x61ab8  CManager2d_Delete
//   [ ] 0x61b08  CManager2d_Construct  [dead]
//   [ ] 0x61b48  CManager2d_Construct_2  [dead]
//   [x] 0x61b88  CManager2d_GetSystemMessageString_maybe
//   [ ] 0x61bd0  CManager2d_RecursiveRegistration
//   [ ] 0x61bd8  KStub_Nop_61bd8  [dead]
//   [ ] 0x61be0  Font_SetTextureFilterLinear_Callback_maybe
//   [ ] 0x61bf8  CManager2d_GetFont_maybe
//   [ ] 0x61c38  CManager2d_GetNthLoadedFont_maybe  [dead]
//   [x] 0x61da8  CManager2d_vf74 (ComputeSortingCoef, in the header)
//   [x] 0x61dc8  SetUIOverlayRenderStates
//   [x] 0x61f60  CManager2d_GetMaterialRenderInfo (GetRenderingProperties, in the header)
//   [ ] 0x61f80  RegisterCManager2dType
//   [ ] 0x61ff8  _GLOBAL__I_61ff8
//   [ ] 0x62008  CManager2d_GetOrCreateBrush_maybe
//   [x] 0x62068  CManager2d_BroadcastEvent_maybe
//   [ ] 0x621a8  CManager2d_FlushPendingEvents_maybe  [dead]
//   [x] 0x62358  CManager2d_PostEvent_maybe
//   [x] 0x623a0  CManager2d_vf78
//   [ ] 0x623e0  CManager2d_RemoveScene74ChildAt_maybe  [dead]
//   [ ] 0x62410  CManager2d_AddElementToScene74_maybe  [dead]
//   [ ] 0x62478  CManager2d_SetFontIntergapSpacing_maybe  [dead]
//   [ ] 0x624e0  CManager2d_Save
//   [x] 0x62508  CManager2d_CacheLocStrings_maybe
//   [x] 0x62610  CManager2d_UnloadLocalizedFonts
//   [x] 0x62820  CManager2d_DestroyGame
//   [x] 0x628b8  CManager2d_Destroy
//   [ ] 0x62920  CManager2d_Shutdown_maybe
//   [x] 0x62a58  CManager2d_DeleteArray
//   [ ] 0x62af8  CManager2d_vf70
//   [ ] 0x62b18  UI2d_RasterPixelsToNormalized_maybe  [dead]
//   [x] 0x62b98  CManager2d_BindRt2dToUICamera_maybe
//   [x] 0x62c00  CManager2d_DrawSystemText_maybe
//   [ ] 0x62e98  UI2d_NormalizedToRasterPixels_maybe
//   [ ] 0x62f18  UI2d_RasterPixelsToNormalizedNoFlip_maybe  [dead]
//   [ ] 0x62f90  UI2d_NormalizedToRasterPixelsNoFlip_maybe  [dead]
//   [x] 0x63008  EnqueueUIManagerRenderStages
//   [x] 0x630e8  CManager2d_Init_maybe
//   [x] 0x631e0  CManager2d_PostLoad
//   [x] 0x631e8  CManager2d_Create
//   [x] 0x63258  CManager2d_CreateArray
//   [x] 0x63320  CManager2d_PreRenderPass_maybe
//   [x] 0x63428  DrawUIManagerScenesAndMenus
//   [x] 0x63550  CManager2d_PostRenderPass_maybe
//   [x] 0x63590  CManager2d_Update
//   [x] 0x63788  CManager2d_LoadFonts_maybe
//   [x] 0x63ac8  CManager2d_LoadLocalizedFonts_maybe
//   [x] 0x63db8  CManager2d_Load
//   [ ] 0x64180  CManager2d_Destructor
//   [ ] 0x641a0  CManager2d_Destructor_2  [dead]
//   [ ] 0x641c0  CManager2d_DeletingDestructor
//
//   [ ] 0x997b10  CManager2d_GetClassType  [inline]
//   [ ] 0x997b18  CManager2d_GetClassID  [inline]
//   [x] 0x997b20  CManager2d_GetSerializationFlags  [inline]
//   [x] 0x997b28  CManager2d_IsKindOfClass  [inline]
#include "k2000/graphical/ui/CManager2d.h"

#include <cstring>

#include "Renderware/rt2d/Rt2d.h"
#include "Renderware/rwcore/RwIm3D.h"
#include "k2000/geometry/CGeometry.h"
#include "k2000/graphical/ui/CKFlashManager.h"
#include "k2000/graphical/ui/CMenuManager.h"
#include "k2000/graphical/ui/CScene2d.h"
#include "k2000/graphical/ui/CameraContextUi.h"
#include "k2000/misc/CKGameLoop.h"
#include "k2000/misc/Engine.h"
#include "k2000/graphical/ui/CText2d.h"
#include "Renderware/rwcore/RwStream.h"
#include "Renderware/rwcore/RwTexture.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/io/CKLoadingManager.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/managers/CKGraphic.h"
#include "k2000/render/CRenderer.h"
#include "k2000/misc/MessageBox.h"
#include "k2000/system/CTimeManager.h"
#include "k2000/misc/Wcs.h"
#include "k2000/memory/Mem.h"
#include "k2000/logic/ui/CLocManager.h"
#include "k2000/logic/ui/CKLocText.h"

namespace {
void* StateWord(uintptr_t value) { return reinterpret_cast<void*>(value); }
}  // namespace

// 0x000631e8 CManager2d_Create (the constructor inlined), in its store order: the IRendableObject part,
// then +0xa84, +0xa48, +0xa4c, +0xa50 and +0xa78.
CManager2d::CManager2d() {
    m_pNextAccumulatedObject = nullptr;
    m_BitProperties = 0;
    m_pPriorityParent = 0;
    m_pLightSet = nullptr;
    m_unkA84 = 0;
    m_unkA48 = nullptr;
    m_pLocalizedFont = nullptr;
    m_pLocalizedTextures = nullptr;
    m_menuManager = nullptr;
}

// 0x000630e8 CManager2d_Init_maybe (InitializeRendererStages, right after the creation): Rt2d opened on
// the UI camera (renderer camera context +0x20), no font texture dictionary, then the stores in order.
void CManager2d::Init() {
    Rt2dOpen(CameraContext_GetUICamera());
    Rt2dFontTexDictionarySet(nullptr);
    m_menuManager = nullptr;
    m_pScene = nullptr;
    m_pFirstScene = nullptr;
    m_unkA68 = nullptr;
    m_pTextBoxesScene = nullptr;
    m_apFonts[9] = nullptr;
    for (uint32_t i = 0; i < 9; ++i) m_apFonts[i] = nullptr;
    m_pLocalizedFont = nullptr;
    m_pLocalizedTextures = nullptr;
    m_apwszSystemMessages[3] = nullptr;
    m_apwszSystemMessages[0] = nullptr;
    m_apwszSystemMessages[1] = nullptr;
    m_apwszSystemMessages[2] = nullptr;
    m_unkA48 = static_cast<CText2d*>(ClassRegistry_CreateObjectByKey(0x5cd));
    m_unkA48->InitDefaults();
    m_ui32PendingEvents_maybe = 0;
    m_bUpdateScreen = 1;
    m_ui32FontsCount = 0;
    // DEV: the CMenuManager the GAME file's global provider hands out (CKGraphic slot 0x11 reads +0xa78).
    // Where the original creates it is not traced (this Init clears +0xa78). STUB(C1.5) creation point.
    m_menuManager = static_cast<IKSerializable*>(ClassRegistry_CreateObjectByKey(0x44d));
}

namespace {

// 0x00c296a0: the localised branch's cached size (the bytes CManager2d_LoadLocalizedFonts_maybe read
// the first time); -1 until then. Later loads skip the bytes while the font is still loaded.
int32_t s_localizedFontsSize = -1;

// An RwImage chunk (0x18) as a raster: the struct chunk's width, height and depth, the pixels kept as
// they are. STUB(C1.4): Raster_CreateFromImage_maybe (the texture bank's raster); here the raster records
// the image so the fonts' rasters exist (Rt2dFontStreamRead requires one per page).
RwShim_DdsRaster* RasterFromImageChunk(RwStream* stream) {
    RwShim_Blob* image = RwShim_ReadChunkBlob(stream, 0x18);
    RwShim_DdsRaster* raster = RwShim_RasterFromImageBlob(image);
    RwShim_FreeBlob(image);
    return raster;
}

// The texture part both font loaders share: count, then per texture its name and mask
// (IKFile_ReadLengthPrefixedString, no limit) and an RwImage chunk (RwStreamFindChunk(0x18),
// RwImageStreamRead), made into a raster (Raster_CreateFromImage_maybe with the texture bank) and a
// texture named name/mask (STRCPY into RwTexture +0x10/+0x30) added to the dictionary; the image is then
// destroyed. Thread_YieldDuringLoad(1) before each.
void LoadFontTextures(IKFile* file, RwTexDictionary* dictionary) {
    uint32_t count = 0;
    ReadU32LE(file, &count);
    for (uint32_t i = 0; i < count; ++i) {
        Thread_YieldDuringLoad(1);
        char name[0x108];
        char mask[0x100];
        IKFile_ReadLengthPrefixedString(file, name, -1);
        IKFile_ReadLengthPrefixedString(file, mask, -1);
        RwTexture* texture = RwTextureCreate(RasterFromImageChunk(file->m_pRwStream));
        // STRCPY in the original (no limit); the shim's names hold 32 characters like RW's.
        std::strncpy(texture->name, name, sizeof(texture->name) - 1);
        std::strncpy(texture->mask, mask, sizeof(texture->mask) - 1);
        RwTexDictionaryAddTexture(dictionary, texture);
    }
}

// RwTexDictionaryForAllTextures(dict, 0x00061be0 Font_SetTextureFilterLinear_Callback_maybe, 0): every
// texture's filter mode becomes 2 (linear).
void SetFontTexturesLinear(RwTexDictionary* dictionary) {
    for (RwTexture* texture : dictionary->textures) {
        texture->filterAddressing = (texture->filterAddressing & 0xffffff00u) | 2u;
    }
}

// 0x00063788 CManager2d_LoadFonts_maybe (K_LEVEL_LOCALIZATION): a new texture dictionary for the font
// textures (made current while they load), linear filtering, the dictionary as Rt2d's font texture
// dictionary, then the fonts: per font its id (above 9 ends the Load), its 0x199 chunk (none ends the
// Load; Rt2dFontStreamRead, a null font ends it) and its name (stored in load order), the font added to
// the Rt2d font dictionary under that name.
void LoadFonts(CManager2d* self, IKFile* file) {
    RwTexDictionary* previous = RwTexDictionaryGetCurrent();
    RwTexDictionary* dictionary = RwTexDictionaryCreate();
    RwTexDictionarySetCurrent(dictionary);
    LoadFontTextures(file, dictionary);
    RwTexDictionarySetCurrent(previous);
    SetFontTexturesLinear(dictionary);
    Rt2dFontTexDictionarySet(dictionary);
    uint32_t count = 0;
    ReadU32LE(file, &count);
    char* name = self->m_aszFontsName[0];
    for (uint32_t i = 0; i < count; ++i) {
        Thread_YieldDuringLoad(1);
        uint32_t id = 0;
        ReadU32LE(file, &id);
        if (id > 9) return;
        if (RwStreamFindChunk(file->m_pRwStream, 0x199, nullptr, nullptr) == 0) return;
        Rt2dFont* font = Rt2dFontStreamRead(file->m_pRwStream);
        self->m_apFonts[id] = font;
        if (font == nullptr) return;
        IKFile_ReadLengthPrefixedString(file, name, -1);
        _rt2dFontDictionaryAdd(self->m_apFonts[id], name);
        name += sizeof(self->m_aszFontsName[0]);
    }
}

// 0x00063ac8 CManager2d_LoadLocalizedFonts_maybe (K_GAME_LOCALIZATION): the textures into a new
// dictionary kept at +0xa50 (linear filtering), made Rt2d's font texture dictionary for the time of the
// load, then a flag byte (read raw) and, when set, the 0x199 font added to the font dictionary as
// "TrcFont" (TOC1 -0x7018) at +0xa4c. BUG(original): a missing chunk or a null font returns without
// restoring the previous font texture dictionary.
void LoadLocalizedFonts(CManager2d* self, IKFile* file) {
    RwTexDictionary* previous = RwTexDictionaryGetCurrent();
    self->m_pLocalizedTextures = RwTexDictionaryCreate();
    RwTexDictionarySetCurrent(self->m_pLocalizedTextures);
    LoadFontTextures(file, self->m_pLocalizedTextures);
    RwTexDictionarySetCurrent(previous);
    SetFontTexturesLinear(self->m_pLocalizedTextures);
    RwTexDictionary* previousFonts = Rt2dFontTexDictionaryGet();
    Rt2dFontTexDictionarySet(self->m_pLocalizedTextures);
    self->m_pLocalizedFont = nullptr;
    uint8_t hasFont = 0;
    ReadU8(file, &hasFont);
    if (hasFont != 0) {
        if (RwStreamFindChunk(file->m_pRwStream, 0x199, nullptr, nullptr) == 0) return;
        self->m_pLocalizedFont = Rt2dFontStreamRead(file->m_pRwStream);
        if (self->m_pLocalizedFont == nullptr) return;
        _rt2dFontDictionaryAdd(self->m_pLocalizedFont, "TrcFont");
    }
    Rt2dFontTexDictionarySet(previousFonts);
}

}  // namespace

// 0x000628b8 CManager2d_Destroy (the level unload): IRendableObject's, then the screen flag, the menu
// manager and the scenes +0xa6c / +0xa74 forgotten (the level's objects), then the level fonts unloaded
// (vt+0x7c).
void CManager2d::Destroy() {
    IRendableObject::Destroy();  // 0xa7248
    m_bUpdateScreen = 0;
    m_menuManager = nullptr;
    m_pScene = nullptr;
    m_pTextBoxesScene = nullptr;
    CManager2d_UnloadLocalizedFonts(this);  // vt+0x7c
}

// 0x00062820 CManager2d_DestroyGame: with the localised font loaded, under its texture dictionary as the
// font texture dictionary: the font out of the font dictionary and destroyed; then the dictionary.
// STUB(C1.4): RwTexDictionaryDestroy (the shim keeps its dictionaries).
void CManager2d::DestroyGame() {
    if (m_pLocalizedFont == nullptr) return;
    RwTexDictionary* previous = Rt2dFontTexDictionaryGet();
    Rt2dFontTexDictionarySet(m_pLocalizedTextures);
    _rt2dFontDictionaryRemove(m_pLocalizedFont);
    Rt2dFontDestroy(m_pLocalizedFont);
    m_pLocalizedFont = nullptr;
    Rt2dFontTexDictionarySet(previous);
    m_pLocalizedTextures = nullptr;
}

// 0x00063db8 CManager2d_Load. IRendableObject's Load for every type, then one branch per type; every
// path sets m_bUpdateScreen.
int32_t CManager2d::Load(IKFile* file, int32_t type) {
    IRendableObject::Load(file, type);
    if (type == K_GAME_PLATEFORMS) {
        ReadU32LE(file, &m_ui32FontsCount);
    } else if (type == K_GAME_LOCALIZATION) {
        if (s_localizedFontsSize != -1 && m_pLocalizedFont != nullptr) {
            file->Seek(s_localizedFontsSize, kSeekCur);  // the fonts are still loaded: skip their bytes
        } else {
            const uint32_t start = file->Tell();
            DestroyGame();  // vt+0x0c
            LoadLocalizedFonts(this, file);
            s_localizedFontsSize = static_cast<int32_t>(file->Tell() - start);
        }
    } else if (type == K_LEVEL_LOCALIZATION) {
        LoadFonts(this, file);
    } else if (type == K_LEVEL_PLATEFORMS) {
        IKFile_ReadRef(file, &m_menuManager);
        IKFile_ReadRef(file, &m_pScene);
        IKFile_ReadRef(file, &m_pFirstScene);
        IKFile_ReadRef(file, &m_unkA68);
        IKFile_ReadRef(file, &m_pTextBoxesScene);
    }
    m_bUpdateScreen = 1;
    return 1;
}


// 0x00061dc8 SetUIOverlayRenderStates (RWEngine +0x20 = RwRenderStateSet). The blend factors are the
// blend table's entry 1 (0x00c297f0 src 5, 0x00c29800 dest 6).
void SetUIOverlayRenderStates() {
    RwRenderStateSet(rwRENDERSTATEALPHATESTFUNCTION, StateWord(8));
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE, StateWord(0));
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, StateWord(0));
    RwRenderStateSet(rwRENDERSTATESHADEMODE, StateWord(2));
    RwRenderStateSet(rwRENDERSTATECULLMODE, StateWord(1));
    RwRenderStateSet(rwRENDERSTATESRCBLEND, StateWord(5));
    RwRenderStateSet(rwRENDERSTATEDESTBLEND, StateWord(6));
    RwRenderStateSet(rwRENDERSTATEFOGENABLE, StateWord(0));
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, StateWord(1));
}

// 0x00062068 CManager2d_BroadcastEvent_maybe
void CManager2d::BroadcastEvent(uint8_t event, void* data) {
    if (m_pScene != nullptr) {
        static_cast<CScene2d*>(m_pScene)->BroadcastEvent(event, data);
        static_cast<CScene2d*>(m_pTextBoxesScene)->BroadcastEvent(event, data);
        static_cast<CMenuManager*>(m_menuManager)->BroadcastEvent(event, data);
        static_cast<CScene2d*>(m_pFirstScene)->BroadcastEvent(event, data);
        static_cast<CScene2d*>(m_unkA68)->BroadcastEvent(event, data);
    }
    if (event == 0) {
        g_pEngine->m_flashManager->ReloadAllTextFonts();
    } else if (event == 5) {
        g_pEngine->m_flashManager->RefreshAllTexts();
    }
}

// 0x000623a0 CManager2d_vf78
void CManager2d::BroadcastLocalisationEvents() {
    BroadcastEvent(0, nullptr);
    BroadcastEvent(5, nullptr);
}

// 0x00062b98 CManager2d_BindRt2dToUICamera_maybe (XXL2 ChangeCam)
uint8_t CManager2d::ChangeCam(void* camera) {
    if (camera == nullptr) return 0;
    m_bUpdateScreen = 1;
    return Rt2dDeviceSetCamera(CameraContext_GetUICamera());
}

// 0x00063008 CManager2d_UpdateAndExtract
// (the stage array is the renderer's, renderer +0x38: +0x44 stage 17, +0x48 stage 18, +0x58 stage 22).
void CManager2d::UpdateAndExtract(float /*maxDistanceSquared*/, RenderQueue** /*stages*/, IKTime* /*frameClock*/, RwCamera* /*camera*/, int32_t /*distanceCull*/) {
    g_pEngine->m_flashManager->PreUpdate(nullptr);
    CRenderer* renderer = g_pEngine->m_graphic->m_renderer;
    renderer->GetStage(17)->Add(static_cast<IRendableObject*>(m_unkA68));
    renderer->GetStage(18)->Add(this);
    renderer->GetStage(22)->Add(static_cast<IRendableObject*>(m_pTextBoxesScene));
}

// 0x00063320 CManager2d_PreRenderPass_maybe (XXL2 UpdateScreen). Not while the game loop loads (mode 1).
uint8_t CManager2d::UpdateScreen() {
    if (m_bUpdateScreen == 0 || !CameraContext_HasRasters() || g_pEngine->m_gameLoop->m_mode == 1) return 0;
    Rt2dDeviceSetCamera(CameraContext_GetUICamera());
    Rt2dCTMPush();
    Rt2dCTMSetIdentity();
    m_fAspect = CameraContext_GetMetricWidth();  // camera context +0x8c
    Rt2dDeviceSetMetric(0.0f, 0.0f, m_fAspect, 0x1p+0f);
    Rt2dCTMPop();
    m_bUpdateScreen = 0;
    m_ui32PendingEvents_maybe |= 2;
    g_pEngine->m_flashManager->RefreshSize();
    return 1;
}

// 0x00063428 CManager2d_Render (DrawUIManagerScenesAndMenus)
void CManager2d::Render() {
    if (m_bUpdateScreen != 0) UpdateScreen();
    static_cast<CScene2d*>(m_pFirstScene)->Render();
    CKFlashManager* flashManager = g_pEngine->m_flashManager;
    PushRenderStates(g_pRenderStateRenderer);  // the renderer's state stack (TOC1 -0x702c -> 0x00c5c90c)
    SetUIOverlayRenderStates();
    flashManager->Render(nullptr);
    PopRenderStates(g_pRenderStateRenderer);
    static_cast<CMenuManager*>(m_menuManager)->DrawActiveUIMenu();  // vt+0x50
    static_cast<CScene2d*>(m_pScene)->Render();
}

// 0x00063550 CManager2d_PostRenderPass_maybe (XXL2 RenderMsgBox)
uint8_t CManager2d::RenderMsgBox() {
    if (m_bUpdateScreen != 0) UpdateScreen();
    // PORT: under the render lock (the original draws unguarded): the overlay's text uses the process-wide
    // Rt2d CTM stack, which the loader thread's CKFlashUI::PostLoad (Rt2dSceneUpdateLTM) also pushes onto.
    RenderLock_Lock();
    CManager2d_DrawSystemMessageOverlay();  // 0x68ef0
    RenderLock_Unlock();
    return 1;
}

namespace {
// The shared constants the system text reads: 0x00c2966e the UTF-16 " " and 0x00c50dfc the white CColor
// (Str.cpp's static initialiser; local copies).
const uint16_t kSharedSpaceW[] = {0x20, 0};
const uint8_t kSharedWhite[4] = {0xff, 0xff, 0xff, 0xff};
}  // namespace

// 0x00061b88 CManager2d_GetSystemMessageString_maybe: slot (id * 4 - 800) clamped (unsigned) to 0xc.
const uint16_t* CManager2d::GetSystemMessageString(uint32_t id) const {
    uint32_t offset = id * 4u - 800u;
    if (offset > 0xc) offset = 0xc;
    const uint16_t* text = m_apwszSystemMessages[offset / 4];
    if (text != nullptr) return text;
    return kSharedSpaceW;  // TOC1 -0x7070 -> 0x00c2966e
}

// 0x00062c00 CManager2d_DrawSystemText_maybe
void CManager2d::DrawSystemText(const uint16_t* text, int32_t align, int32_t pulse) {
    CText2d* const systemText = m_unkA48;
    if (systemText == nullptr || m_pLocalizedFont == nullptr) return;
    PushRenderStates(g_pRenderStateRenderer);
    SetUIOverlayRenderStates();  // with the engine's CManager2d (engine +0x38)
    uint8_t color[4];
    if (pulse == 0) {
        std::memcpy(color, kSharedWhite, 4);  // TOC1 -0x7028 -> 0x00c50dfc
    } else {
        CManager2d_GetPulsingTextColor(color);
    }
    m_unkA48->SetColor(color);                        // IKText2d vt+0x44
    m_unkA48->m_VarColor = m_unkA48->m_Color;
    m_unkA48->SetFont(0x29a);                         // IKText2d vt+0x40: the localised font
    m_unkA48->SetTextWide(text);                      // vt+0x8c
    m_unkA48->Enable();                               // vt+0x64
    if (align == 0) {
        m_unkA48->m_vPosition.m_fY = 0x1.99999ap-1f;  // 0.8f (TOC1 -0x7024)
        m_unkA48->m_vPosition.m_fX = 0x1p-1f;         // 0.5f (TOC1 -0x706c)
    } else if (align == 2) {
        m_unkA48->m_vPosition.m_fY = 0x1.99999ap-3f;  // 0.2f (TOC1 -0x7020)
        m_unkA48->m_vPosition.m_fX = 0x1p-1f;
    } else {
        m_unkA48->m_vPosition.m_fY = 0x1p-1f;
        m_unkA48->m_vPosition.m_fX = 0x1p-1f;
    }
    m_unkA48->Render(g_pEngine->m_timeManager->m_pTime);  // vt+0x84 with the frame clock
    m_unkA48->Disable();                                  // vt+0x68
    PopRenderStates(g_pRenderStateRenderer);
}

// 0x00063590 CManager2d_PreUpdate: bits 0..7 of the pending events, in order, then cleared; then the Flash
// interfaces updated with the frame clock.
void CManager2d::PreUpdate(IKTime* time) {
    for (uint32_t event = 0; event < 8; ++event) {
        if ((m_ui32PendingEvents_maybe & (1u << event)) != 0) BroadcastEvent(static_cast<uint8_t>(event), nullptr);
    }
    m_ui32PendingEvents_maybe = 0;
    g_pEngine->m_flashManager->Update(time);
}

// 0x00062358 CManager2d_PostEvent_maybe
void CManager2d::PostEvent(uint8_t event, void* data) {
    if (data != nullptr) {
        BroadcastEvent(event, data);
        return;
    }
    m_ui32PendingEvents_maybe |= 1u << (event & 0x3f);
}

// vt+0x7c 0x00062610 CManager2d_UnloadLocalizedFonts (the language switch): the ten level fonts out of the
// Rt2d font dictionary and destroyed, then the font texture dictionary released. RwTexDictionaryDestroy is
// STUB(C1.4) (the shim keeps its dictionaries, as CManager2d_DestroyGame).
void CManager2d_UnloadLocalizedFonts(CManager2d* manager) {
    for (Rt2dFont*& font : manager->m_apFonts) {
        if (font == nullptr) continue;
        _rt2dFontDictionaryRemove(font);
        Rt2dFontDestroy(font);
        font = nullptr;
    }
    if (Rt2dFontTexDictionaryGet() != nullptr) Rt2dFontTexDictionarySet(nullptr);
}

// 0x00062508 CManager2d_CacheLocStrings_maybe: copies of the TRC texts 200..203 into +0xa54..+0xa60,
// allocated the first time, reallocated to the new length after that.
void CManager2d_CacheLocStrings(CManager2d* manager) {
    for (uint32_t i = 0; i < 4; ++i) {
        const uint16_t* text = LocString_GetText(g_pEngine->m_locManager->GetText(i + 200));
        uint32_t length = 0;
        while (text[length] != 0) ++length;  // 0x00010a18 Wcs_Length
        uint16_t*& copy = manager->m_apwszSystemMessages[i];
        if (copy == nullptr) {
            copy = static_cast<uint16_t*>(Mem_AllocAligned16(length * 2 + 2));
        } else {
            copy = static_cast<uint16_t*>(Mem_ReallocAligned16(copy, length * 2 + 2));
        }
        WStr_CopyReturnEnd(copy, text);
    }
}
