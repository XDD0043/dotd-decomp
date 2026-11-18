// CManager2d.h - the 2D/UI manager: the fonts, the 2D scenes and the menu manager (key 0x40d, vtable
// 0xb15b98, size 0xa88). Original unit: CManager2d.cpp (0x61ab8-0x641e0). Created by
// InitializeRendererStages (renderer +0x98, GameEngineContext +0x38), then 0x630e8 CManager2d_Init_maybe.
// XXL2: K/KModules/KGL/2d/CManager2d.h (base IRendableObject): the fonts (m_apFonts[10] and their
// names), m_ui32FontsCount (read by the GAME branch in both), the scenes and m_pMenuManager (read in
// the level branch, the menu manager first), m_bUpdateScreen (set to 1 at the end of every Load).
// DotD keeps 0x100 bytes per font name (XXL2 1024), reads four scenes (XXL2 three) and loads the
// localised font ("TrcFont") and its texture dictionary separately (+0xa4c, +0xa50).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/graphical/IRendableObject.h"

struct Rt2dBrush;
struct Rt2dFont;
struct RwTexDictionary;
class CText2d;
struct CVector2;

class CManager2d : public IRendableObject {
public:
    DOTD_CLASS_KEY(kCategoryGraphical, 0x10)
    DOTD_DECLARE_FACTORIES(CManager2d)

    CManager2d();  // inlined in 0x000631e8 CManager2d_Create (copy 0x61b08 unreferenced)
    ~CManager2d() override {}
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x997b28
        return key == 0x40d || key == 0xa8d || key == 0xc;
    }
    // vt+0x0c 0x62820: when the localised font is loaded, removes it from the Rt2d font dictionary and
    // destroys it, then destroys its texture dictionary (under that dictionary as the current one).
    void DestroyGame() override;
    void Destroy() override;                                // vt+0x10 0x000628b8 CManager2d_Destroy
    int32_t Load(IKFile* file, int32_t type) override;      // vt+0x2c 0x00063db8 CManager2d_Load
    int32_t GetSerializationFlags() override { return 0; }  // vt+0x34 0x997b20
    // vt+0x54 0x00063590 CManager2d_PreUpdate (XXL2 PreUpdate): the pending scene events broadcast
    // (m_ui32PendingEvents_maybe bits 0..7 -> events 0..7), then every Flash interface updated.
    void PreUpdate(IKTime* time) override;
    // vt+0x58 0x00063008 CManager2d_UpdateAndExtract (XXL2 UpdateAndExtract(IAccumulator**, IKTime*)): the
    // Flash interfaces' PreUpdate, then the scenes +0xa68, this, +0xa74 queued in the renderer's 2D stages.
    void UpdateAndExtract(float maxDistanceSquared, RenderQueue** stages, IKTime* frameClock, RwCamera* camera, int32_t distanceCull) override;
    // vt+0x5c 0x00063428 CManager2d_Render (DrawUIManagerScenesAndMenus; XXL2 Render): scene +0xa70, the
    // Flash interfaces (overlay render states), the menu manager, scene +0xa6c.
    void Render(IKTime* frameClock) override;
    // vt+0x6c 0x00061f60 CManager2d_GetRenderingProperties: 0, 0xff, 0 and the blend table's entry 1.
    void GetRenderingProperties(uint8_t* first, uint8_t* second, uint8_t* third, uint32_t* blendMode) override {
        *first = 0;
        *second = 0xff;
        *third = 0;
        *blendMode = 1;
    }
    // vt+0x74 0x00061da8 CManager2d_ComputeSortingCoef: 0.5 (TOC1 -0x706c) for the sorting orders 1 and 2,
    // else 0.
    void ComputeSortingCoef(int32_t sortingOrder) override {
        m_fSortingCoef = static_cast<uint32_t>(sortingOrder - 1) <= 1u ? 0x1p-1f : 0.0f;
    }
    void Init();  // 0x000630e8 CManager2d_Init_maybe
    // vt+0x70 0x00062af8 CManager2d_vf70 (CanBeUpdated): 0 while the renderer's bit 2 (+0xa4, the loading frame) is set.
    int32_t CanBeUpdated() override;
    // 0x00061bf8 CManager2d_GetFont_maybe: font 0x29a is the localised font, 0..9 the loaded fonts, anything else none.
    Rt2dFont* GetFont(uint32_t id) const;
    // 0x00062008 CManager2d_GetOrCreateBrush_maybe: the brush (+0xa84), made (Rt2dBrushCreate) the first time.
    Rt2dBrush* GetOrCreateBrush();
    // 0x00062920 CManager2d_Shutdown_maybe (CRenderer_Shutdown_maybe): the localised font (vt+0x0c), the system text
    // (+0xa48), the brush and the system message strings released, then Rt2dClose.
    void Shutdown();
    // 0x00063320 CManager2d_PreRenderPass_maybe (XXL2 UpdateScreen): when the screen changed (+0xa7c), the
    // Rt2d device bound to the UI camera with the metric (0, 0, aspect, 1); every movie refitted. 1 when done.
    uint8_t UpdateScreen();
    // 0x00063550 CManager2d_PostRenderPass_maybe (XXL2 RenderMsgBox): UpdateScreen when pending, then the
    // system message overlay (0x68ef0 CManager2d_DrawSystemMessageOverlay_maybe, misc/MessageBox.cpp).
    uint8_t RenderMsgBox();
    // 0x00061b88 CManager2d_GetSystemMessageString_maybe: the cached string of system message `id` (200..203;
    // any other id reads the last slot), or the shared wide " " when it is not cached.
    const uint16_t* GetSystemMessageString(uint32_t id) const;
    // 0x00062c00 CManager2d_DrawSystemText_maybe: `text` in the system text (+0xa48) with the localised font,
    // white or pulsing grey, at (0.5, 0.8) for align 0, (0.5, 0.2) for 2, else the centre; drawn once under
    // the overlay render states (enabled only for the draw). Nothing without the text or the font.
    void DrawSystemText(const uint16_t* text, int32_t align, int32_t pulse);
    // 0x00062b98 CManager2d_BindRt2dToUICamera_maybe (XXL2 ChangeCam): marks the screen changed and binds
    // the Rt2d device to the UI camera (the argument only gates it).
    uint8_t ChangeCam(void* camera);
    // 0x00062068 CManager2d_BroadcastEvent_maybe: an event to the four scenes and the menu manager; event
    // 0 then re-applies the Flash text fonts, event 5 refreshes the Flash texts.
    void BroadcastEvent(uint8_t event, void* data);
    // 0x00062358 CManager2d_PostEvent_maybe: with data, broadcast now; without, bit `event` of the pending
    // events (PreUpdate broadcasts them).
    void PostEvent(uint8_t event, void* data);
    void BroadcastLocalisationEvents();  // 0x000623a0 CManager2d_vf78: events 0 and 5

    float m_fAspect;                     // +0x018 XXL2 GetAspectRatio: the camera context's +0x8c (UpdateScreen)
    // +0x01c Rt2dFont* by font id (0..9) (Rt2dFontStreamRead, registered in the Rt2d font dictionary).
    Rt2dFont* m_apFonts[10];
    char m_aszFontsName[10][0x100];      // +0x044 by load order; read without a length limit
    uint32_t m_unkA44;                   // +0xa44
    CText2d* m_unkA48;                   // +0xa48 created by CManager2d_Init_maybe (0x5cd)
    Rt2dFont* m_pLocalizedFont;          // +0xa4c "TrcFont" (localised branch)
    RwTexDictionary* m_pLocalizedTextures;  // +0xa50 its texture dictionary
    // +0xa54 the system message strings 200..203 (Init_maybe clears them; CManager2d_CacheLocStrings_maybe
    // 0x62508 copies them from the loc manager).
    uint16_t* m_apwszSystemMessages[4];
    uint32_t m_ui32FontsCount;           // +0xa64 K_GAME_PLATEFORMS
    IKSerializable* m_unkA68;            // +0xa68 CScene2d (a reference; DotD's fourth scene_maybe)
    IKSerializable* m_pScene;            // +0xa6c CScene2d (a reference; XXL2's first scene read_maybe)
    IKSerializable* m_pFirstScene;       // +0xa70 CScene2d (a reference; _maybe)
    IKSerializable* m_pTextBoxesScene;   // +0xa74 CScene2d (a reference; _maybe)
    IKSerializable* m_menuManager;       // +0xa78 CMenuManager (13:17), XXL2 m_pMenuManager
    uint8_t m_bUpdateScreen;             // +0xa7c (+0xa7d..+0xa7f: padding)
    uint32_t m_ui32PendingEvents_maybe;  // +0xa80 event bits PreUpdate broadcasts (UpdateScreen sets bit 1)
    // +0xa84 the constructor sets 0; CManager2d_GetOrCreateBrush_maybe 0x62008 (only DrawUIFontTextRotatedScaled_maybe
    // 0xa3a78, not ported) creates it; Shutdown destroys it.
    Rt2dBrush* m_pBrush;
};
DOTD_ASSERT_SIZE(CManager2d, 0xa88);
DOTD_ASSERT_OFFSET(CManager2d, m_fAspect, 0x18);
DOTD_ASSERT_OFFSET(CManager2d, m_apFonts, 0x1c);
DOTD_ASSERT_OFFSET(CManager2d, m_ui32PendingEvents_maybe, 0xa80);
DOTD_ASSERT_OFFSET(CManager2d, m_aszFontsName, 0x44);
DOTD_ASSERT_OFFSET(CManager2d, m_unkA48, 0xa48);
DOTD_ASSERT_OFFSET(CManager2d, m_pLocalizedFont, 0xa4c);
DOTD_ASSERT_OFFSET(CManager2d, m_pLocalizedTextures, 0xa50);
DOTD_ASSERT_OFFSET(CManager2d, m_ui32FontsCount, 0xa64);
DOTD_ASSERT_OFFSET(CManager2d, m_unkA68, 0xa68);
DOTD_ASSERT_OFFSET(CManager2d, m_pScene, 0xa6c);
DOTD_ASSERT_OFFSET(CManager2d, m_pFirstScene, 0xa70);
DOTD_ASSERT_OFFSET(CManager2d, m_pTextBoxesScene, 0xa74);
DOTD_ASSERT_OFFSET(CManager2d, m_menuManager, 0xa78);
DOTD_ASSERT_OFFSET(CManager2d, m_bUpdateScreen, 0xa7c);
DOTD_ASSERT_OFFSET(CManager2d, m_pBrush, 0xa84);

// 0x00061dc8 SetUIOverlayRenderStates: alpha test always, no Z test or write, Gouraud, no culling, the
// blend of the table's entry 1 (SRCALPHA / INVSRCALPHA), no fog, vertex alpha.
void SetUIOverlayRenderStates();

// The two CManager2d functions the language switch calls.
// vt+0x7c 0x00062610 CManager2d_UnloadLocalizedFonts: the ten level fonts out of the Rt2d font dictionary
// and destroyed, then the font texture dictionary released.
void CManager2d_UnloadLocalizedFonts(CManager2d* manager);
// 0x00062e98 UI2d_NormalizedToRasterPixels_maybe: normalised 2D coordinates (y up) to raster pixels (y down).
void UI2d_NormalizedToRasterPixels(CManager2d* manager, CVector2* out, const CVector2* in);
// 0x00062508 CManager2d_CacheLocStrings_maybe: copies of the TRC texts 200..203 at +0xa54..+0xa60.
void CManager2d_CacheLocStrings(CManager2d* manager);
