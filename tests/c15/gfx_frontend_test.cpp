// gfx_frontend_test - checkpoint C1.4 (family gfx): the front end drawn through the GL 3.3 backend into the
// internal 1280x720 target, in a hidden window, with PNG screenshots to look at.
//
// The movies are started as tests/c15/flash_exit_test.cpp does (the menu logic is C1.6): the press-start
// movie (#3, StartInterface as KBase730C_Open does), then StopInterface(#3) and the main menu (#0). Frames
// are stepped at 1/60 s through the game's own loop (GameLoop -> RenderGameFrame -> the 2D stage group ->
// Rt2d -> RwIm3D/atomics -> RwDevice -> platform/gfx).
//
// Checks: the device draws (non-empty Im3D and atomic lists per frame, pixels that are not the clear
// colour), the render-state stack is balanced at the end of a frame, the UI camera and aspects come
// from the ported camera context. Screenshots: DOTD_GFX_OUT (a directory; default: the current one)
// gets gfx_press_start.png, gfx_main_menu_open.png and gfx_main_menu_idle.png. Without a GL device the
// test is skipped (77).
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>

#include "Renderware/rpworld/RpGeometry.h"
#include "Renderware/rwcore/RwCamera.h"
#include "Renderware/rwcore/RwIm3D.h"
#include "Renderware/rt2d/Rt2d.h"
#include "Renderware/rt2danim/Rt2dAnim.h"
#include "boot_helper.h"
#include "k2000/logic/CKSector.h"
#include "k2000/cameras/CameraContext.h"
#include "k2000/graphical/ui/CContainer2d.h"
#include "k2000/graphical/ui/CKFlashManager.h"
#include "k2000/graphical/ui/CKFlashText.h"
#include "k2000/graphical/ui/CManager2d.h"
#include "k2000/graphical/ui/CMenuManager.h"
#include "k2000/graphical/ui/CScene2d.h"
#include "k2000/graphical/ui/CText2d.h"
#include "k2000/graphical/ui/CKFlashUI.h"
#include "k2000/managers/CKGraphic.h"
#include "k2000/misc/Engine.h"
#include "k2000/render/CRenderer.h"
#include "platform/config.h"
#include "platform/gfx/device.h"
#include "platform/sdl/app.h"

namespace {

std::string OutPath(const char* name) {
    const char* dir = std::getenv("DOTD_GFX_OUT");
    std::string path = dir != nullptr && *dir != 0 ? std::string(dir) + "/" : std::string();
    return path + name;
}

struct FrameStats {
    size_t im3d = 0;
    size_t atomics = 0;
    size_t litPixels = 0;  // pixels brighter than the clear colour
};

FrameStats Measure() {
    FrameStats stats;
    stats.im3d = RwIm3DFrameDraws().size();
    stats.atomics = RpAtomicFrameDraws().size();
    std::vector<uint8_t> rgba(static_cast<size_t>(dotd::gfx::InternalWidth()) * dotd::gfx::InternalHeight() * 4);
    if (dotd::gfx::ReadTarget(rgba.data())) {
        for (size_t i = 0; i < rgba.size(); i += 4) {
            if (rgba[i] + rgba[i + 1] + rgba[i + 2] > 24) ++stats.litPixels;
        }
    }
    return stats;
}

void Shot(const char* name, uint32_t frames, bool expectDraws) {
    for (uint32_t i = 0; i < frames; ++i) c15::RunFrame();
    const FrameStats stats = Measure();
    const std::string path = OutPath(name);
    const bool saved = dotd::gfx::SaveScreenshot(path.c_str());
    std::printf("gfx_frontend: frame %u: %zu Im3D draws, %zu atomics, %zu lit pixels -> %s%s\n", c15::FrameCount(),
                stats.im3d, stats.atomics, stats.litPixels, path.c_str(), saved ? "" : " (NOT SAVED)");
    C15_CHECK(saved);
    if (expectDraws) {
        C15_CHECK(stats.im3d + stats.atomics > 0);
        C15_CHECK(stats.litPixels > 1000);
    }
}

void DumpVisibility(CKFlashUI* ui) {
    int counts[6][2] = {};
    struct Walk {
        static void Run(Rt2dObject* o, int (*c)[2]) {
            const int t = static_cast<int>(o->type) < 6 ? static_cast<int>(o->type) : 5;
            ++c[t][(o->flag & 4) != 0 ? 1 : 0];
            if (o->type == rt2DOBJECTTYPEOBJECTSTRING && (o->flag & 4) != 0) {
                const Rt2dFont* font = o->data.objectString.font != nullptr ? o->data.objectString.font->font : nullptr;
                std::printf("gfx_frontend:   string flag %08x font %p text[0..3] %02x %02x %02x %02x height %f box %f\n",
                            static_cast<unsigned>(o->flag), static_cast<const void*>(font),
                            static_cast<unsigned char>(o->data.objectString.textString[0]),
                            static_cast<unsigned char>(o->data.objectString.textString[1]),
                            static_cast<unsigned char>(o->data.objectString.textString[2]),
                            static_cast<unsigned char>(o->data.objectString.textString[3]),
                            static_cast<double>(o->data.objectString.height),
                            static_cast<double>(o->data.objectString.boxwidth));
            }
            if (o->type == rt2DOBJECTTYPESCENE && (o->flag & 4) != 0) {
                for (RwInt32 i = 0; i < o->data.scene.objectCount; ++i) Run(Rt2dSceneGetChildByIndex(o, i), c);
            }
        }
    };
    Walk::Run(Rt2dMaestroGetScene(ui->m_pMaestro), counts);
    std::printf("gfx_frontend: objects (hidden/visible): scene %d/%d shape %d/%d pick %d/%d string %d/%d\n", counts[1][0],
                counts[1][1], counts[2][0], counts[2][1], counts[3][0], counts[3][1], counts[4][0], counts[4][1]);
}

void DumpScene(const char* name, IKSerializable* sceneObject, int depth) {
    CScene2d* scene = static_cast<CScene2d*>(sceneObject);
    if (scene == nullptr) {
        std::printf("gfx_frontend: %*s%s: null\n", depth * 2, "", name);
        return;
    }
    std::printf("gfx_frontend: %*s%s: enabled %d, %u nodes\n", depth * 2, "", name, scene->m_bEnable, scene->m_ui32NodeCount);
    int n = 0;
    for (IKNode2d* node = static_cast<IKNode2d*>(scene->m_pRootNode); node != nullptr && n < 40; node = node->m_pNext, ++n) {
        std::printf("gfx_frontend: %*s  node %d class %d:%d flags %02x pos %.3f %.3f\n", depth * 2, "", n,
                    node->GetClassType(), node->GetClassID(), node->m_baFlags, static_cast<double>(node->m_vPosition.m_fX),
                    static_cast<double>(node->m_vPosition.m_fY));
        if (node->IsKindOfClass(0x4cd) != 0 && depth < 3) {
            CContainer2d* container = static_cast<CContainer2d*>(node);
            DumpScene("buttons", container->m_pButtonObjects, depth + 2);
            DumpScene("others", container->m_pNonButtonObjects, depth + 2);
        }
    }
}

void DumpScenes() {
    CManager2d* m = g_pEngine->m_manager2d;
    DumpScene("+0xa68 (stage 17)", m->m_unkA68, 0);
    DumpScene("+0xa70 (stage 18 first)", m->m_pFirstScene, 0);
    CMenuManager* menu = static_cast<CMenuManager*>(m->m_menuManager);
    std::printf("gfx_frontend: menu manager enabled %d\n", menu->m_bEnabled);
    DumpScene("menu", menu->m_pMenuSceneContainers, 0);
    DumpScene("+0xa6c (stage 18 last)", m->m_pScene, 0);
    DumpScene("+0xa74 (stage 22)", m->m_pTextBoxesScene, 0);
}

}  // namespace

int main() {
    std::setvbuf(stdout, nullptr, _IONBF, 0);
    dotd::platform::Config& config = dotd::platform::MutableConfig();
    dotd::platform::LoadConfig(0, nullptr, config);
    if (config.usrdir.empty()) {
        std::printf("gfx_frontend: no game data configured; skipped\n");
        return 77;
    }
    config.hiddenWindow = true;
    config.vsync = false;
    config.frameRate = 0;  // uncapped: the test steps its own clock
    if (!dotd::platform::sdl::Init(config) || !dotd::gfx::Init(1280, 720)) {
        std::printf("gfx_frontend: no OpenGL 3.3 device; skipped\n");
        return 77;
    }
    if (!c15::BootToFrontEnd()) {
        std::printf("gfx_frontend: boot failed\n");
        return 1;
    }
    c15::ParkFrontEndSequence();  // this harness drives the movies itself
    // The ported camera context: 1280x720 rasters, the UI camera of the live game, 16:9 aspects.
    CameraContext* context = Engine_GetCameraContext();
    C15_CHECK(context != nullptr && context->m_pFinalColorRaster != nullptr);
    C15_CHECK(context->m_pFinalColorRaster->width == 1280 && context->m_pFinalColorRaster->height == 720);
    C15_CHECK(context->m_fHeightOverWidth == 0x1.2p-1f);           // 0x3f100000
    C15_CHECK(context->m_fMetricWidth == 0x1.c71c72p+0f);          // 0x3fe38e39
    C15_CHECK(context->m_pUICamera->viewWindow.x == 0.5f && context->m_pUICamera->nearPlane == 0x1.47ae14p-7f);

    CKFlashManager* manager = g_pEngine->m_flashManager;
    C15_CHECK(manager != nullptr && manager->m_ui32NbFlashUI == 29);
    if (manager == nullptr || manager->m_ui32NbFlashUI < 29) return 1;
    manager->SetInputConfig(1);
    CKFlashUI* pressStart = manager->GetInterfaceByIndex(3);
    CKFlashUI* mainMenu = manager->GetInterfaceByIndex(0);

    if (std::getenv("DOTD_GFX_SURVEY_MOVIES") != nullptr) {
        for (uint32_t i = 0; i < manager->m_ui32NbFlashUI; ++i) {
            CKFlashUI* ui = manager->GetInterfaceByIndex(i);
            ui->StartInterface(1);
            for (int f = 0; f < 90; ++f) c15::RunFrame();
            std::printf("gfx_frontend: survey #%u: %zu Im3D %zu atomics\n", i, RwIm3DFrameDraws().size(),
                        RpAtomicFrameDraws().size());
            DumpVisibility(ui);
            ui->StopInterface(1);
        }
    }
    {
        // Which menu-scene texts have a layout (word lines set) after the boot.
        CScene2d* menuScene = static_cast<CScene2d*>(static_cast<CMenuManager*>(g_pEngine->m_manager2d->m_menuManager)->m_pMenuSceneContainers);
        int laidOut = 0, notLaidOut = 0, withFont = 0;
        for (IKNode2d* c = static_cast<IKNode2d*>(menuScene->m_pRootNode); c != nullptr; c = c->m_pNext) {
            if (c->IsKindOfClass(0x4cd) == 0) continue;
            CScene2d* others = static_cast<CScene2d*>(static_cast<CContainer2d*>(c)->m_pNonButtonObjects);
            for (IKNode2d* n = static_cast<IKNode2d*>(others->m_pRootNode); n != nullptr; n = n->m_pNext) {
                if (n->IsKindOfClass(0x5cd) == 0) continue;
                CText2d* t = static_cast<CText2d*>(n);
                if (t->m_pFont != nullptr) ++withFont;
                if (t->m_ui32WordsCount > 0 && t->m_aui16WordsLine[0] != 0xcdcd) ++laidOut; else ++notLaidOut;
            }
        }
        std::printf("gfx_frontend: menu texts after boot: %d laid out, %d not, %d with a font\n", laidOut, notLaidOut, withFont);
    }
    // The menu texts (CText2d) get their fonts from the event-0 broadcast at the end of the load, but no
    // layout: the boot's event-1 broadcast reaches them while they are disabled, and the menus (C1.6:
    // CKInterfaceButton, CText2d_SetTextById) lay them out when they set their texts. Stand-in here: the
    // event-1 broadcast again after each menu opens (as after a screen change, CManager2d +0xa80 bit 1).
    auto relayout = [] { g_pEngine->m_manager2d->m_ui32PendingEvents_maybe |= 2; };

    // The copyrights screen (#16), as CKS08MenuCopyrights opens it. Its two strings are blank until the
    // menu sets them (C1.6), so the frame shows only the clear colour (the video is family video's).
    CKFlashUI* copyrights = manager->GetInterfaceByIndex(16);
    copyrights->StartInterface(1);
    Shot("gfx_copyrights.png", 60, false);
    copyrights->StopInterface(1);

    // Press start: the movie's hot spots pin the game logo billboard (CBillboard2d, a DXT5 texture).
    pressStart->StartInterface(1);
    Shot("gfx_press_start.png", 30, true);
    relayout();
    Shot("gfx_press_start_texts.png", 30, true);
    if (std::getenv("DOTD_GFX_SURVEY") != nullptr) DumpScenes();
    CRenderer* renderer = g_pEngine->m_graphic->m_renderer;
    C15_CHECK(renderer->m_renderStateDepth == 0);  // every Push popped by the end of the frame

    // The main menu: the movie's hot spots enable its texts (title, entries, the button legend).
    pressStart->StopInterface(1);
    mainMenu->StartInterface(1);
    Shot("gfx_main_menu_open.png", 30, false);
    relayout();
    Shot("gfx_main_menu_idle.png", 60, true);
    C15_CHECK(RwIm3DFrameDraws().size() >= 4);  // glyph batches through RwIm3D (fonts from 00LLC000)

    c15::Shutdown();
    dotd::gfx::Shutdown();
    dotd::platform::sdl::Shutdown();
    if (c15::g_failures == 0) std::printf("gfx_frontend: all tests passed\n");
    return c15::g_failures == 0 ? 0 : 1;
}
