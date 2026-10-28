// gfx_c16_test - checkpoint C1.6 (family gfx): the real front-end sequence (auto-load, copyrights, the
// three logos, press start, START, main menu: CKS08GameManager's own states, not a harness) drawn through
// the GL backend, with a PNG of each screen.
//
// Checks: during the logos (game state 3) KBase3B0C_State3 keeps the camera context's clear colour at the
// shared black without alpha (0x00000000) every frame; the press-start and main-menu texts that hold a
// "#$n#" pad token show a pad-icon glyph (a private-use character the font maps), not '?'; the Scale
// slots (vt+0x80) of CText2d / CBillboard2d / CContainer2d multiply the sizes. Screenshots: DOTD_GFX_OUT
// (a directory; default: the current one) gets c16_<screen>.png. Without a GL device the test is skipped.
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <utility>
#include <vector>

#include "Renderware/rpprtstd/RpPrtStd.h"
#include "Renderware/rwcore/RwCamera.h"
#include "Renderware/rt2d/Rt2d.h"
#include "Renderware/rt2d/Rt2dTypes.h"
#include "Spyro2008/logic/CKS08GameManager.h"
#include "boot_helper.h"
#include "k2000/cameras/CameraContext.h"
#include "k2000/graphical/fx/CBillboard2d.h"
#include "k2000/graphical/ui/CContainer2d.h"
#include "k2000/graphical/ui/CManager2d.h"
#include "k2000/graphical/ui/CMenuManager.h"
#include "k2000/graphical/ui/CScene2d.h"
#include "k2000/graphical/ui/CText2d.h"
#include "k2000/misc/CKGameLoop.h"
#include "k2000/misc/CoreSingletons.h"
#include "k2000/misc/Engine.h"
#include "platform/cell/pad.h"
#include "platform/config.h"
#include "platform/gfx/device.h"
#include "platform/sdl/app.h"

namespace {

bool g_startHeld = false;

bool TestPad(int port, uint16_t words[24]) {
    if (port != 0) return false;
    std::memset(words, 0, 24 * sizeof(uint16_t));
    words[CELL_PAD_BTN_OFFSET_DIGITAL1] = g_startHeld ? CELL_PAD_CTRL_START : 0;
    for (int i = CELL_PAD_BTN_OFFSET_ANALOG_RIGHT_X; i <= CELL_PAD_BTN_OFFSET_ANALOG_LEFT_Y; ++i) words[i] = 0x80;
    return true;
}

std::string OutPath(const char* name) {
    const char* dir = std::getenv("DOTD_GFX_OUT");
    std::string path = dir != nullptr && *dir != 0 ? std::string(dir) + "/" : std::string();
    return path + name;
}

void Shot(const char* name) {
    const std::string path = OutPath(name);
    const bool saved = dotd::gfx::SaveScreenshot(path.c_str());
    std::printf("gfx_c16: frame %u -> %s%s\n", c15::FrameCount(), path.c_str(), saved ? "" : " (NOT SAVED)");
    C15_CHECK(saved);
}

// Every CText2d under a scene (containers' button and non-button scenes included).
void CollectTexts(IKSerializable* sceneObject, std::vector<CText2d*>& out, int depth) {
    CScene2d* scene = static_cast<CScene2d*>(sceneObject);
    if (scene == nullptr || depth > 4) return;
    for (IKNode2d* node = static_cast<IKNode2d*>(scene->m_pRootNode); node != nullptr; node = node->m_pNext) {
        if (node->IsKindOfClass(0x5cd) != 0) out.push_back(static_cast<CText2d*>(node));
        if (node->IsKindOfClass(0x4cd) != 0) {
            CContainer2d* container = static_cast<CContainer2d*>(node);
            CollectTexts(container->m_pButtonObjects, out, depth + 1);
            CollectTexts(container->m_pNonButtonObjects, out, depth + 1);
        }
    }
}

std::vector<CText2d*> AllTexts() {
    std::vector<CText2d*> texts;
    CManager2d* m = g_pEngine->m_manager2d;
    CollectTexts(m->m_unkA68, texts, 0);
    CollectTexts(m->m_pFirstScene, texts, 0);
    CollectTexts(static_cast<CMenuManager*>(m->m_menuManager)->m_pMenuSceneContainers, texts, 0);
    CollectTexts(m->m_pScene, texts, 0);
    CollectTexts(m->m_pTextBoxesScene, texts, 0);
    return texts;
}

std::string Ascii(const uint16_t* w) {
    std::string s;
    for (; *w != 0 && s.size() < 60; ++w) {
        if (*w >= 0x20 && *w < 0x7f) {
            s += static_cast<char>(*w);
        } else {
            char buf[12];
            std::snprintf(buf, sizeof(buf), "<%04x>", *w);
            s += buf;
        }
    }
    return s;
}

// The enabled texts' pad glyphs: private-use characters (U+E000..U+F8FF), and '?' in a text with "#$n#"
// token entries (a "#£a_b_c_#" token is replaced once and leaves no entry). Returns {private-use glyphs,
// '?' in token texts}; *found is set when `want` is among the glyphs.
std::pair<int, int> CheckPadGlyphs(const char* screen, uint16_t want, bool* found) {
    int glyphs = 0, unknown = 0;
    for (CText2d* t : AllTexts()) {
        if ((t->m_baFlags & 2) == 0) continue;
        const uint32_t count = t->m_ui16ButtonTokensCount <= 5 ? t->m_ui16ButtonTokensCount : 0;
        for (const uint16_t* c = t->m_wszText; *c != 0; ++c) {
            const bool pua = *c >= 0xe000 && *c <= 0xf8ff;
            const bool question = *c == 0x3f && count != 0;
            if (!pua && !question) continue;
            if (pua) ++glyphs;
            if (question) ++unknown;
            if (pua && *c == want && found != nullptr) *found = true;
            std::printf("gfx_c16: %s: glyph U+%04x in \"%s\" (%u token entries)\n", screen, *c, Ascii(t->m_wszText).c_str(),
                        count);
        }
    }
    return {glyphs, unknown};
}

void CheckScale() {
    // vt+0x80 on detached copies (no scene, no font: CText2d's layout returns at once without one).
    CBillboard2d billboard;
    billboard.m_vBillboardSize.m_fX = 0x1.8p+0f;
    billboard.m_vBillboardSize.m_fY = 0x1p-1f;
    billboard.Scale(CVector2{0x1p+1f, 0x1.8p+1f});
    C15_CHECK(billboard.m_vBillboardSize.m_fX == 0x1.8p+1f && billboard.m_vBillboardSize.m_fY == 0x1.8p+0f);
}

// The RpPrtStd plugin data of the loaded particle atomics: every emitter read (STREAMREAD set, on its
// atomic, with its classes), and the particle nodes bound to their emitters by CParticlesNodeFx_PostLoad,
// the point lists inside the emitters with their points after them.
void CheckParticleEmitters() {
    const RpPrtStdShimStats stats = RpPrtStdShim_Stats();
    std::printf("gfx_c16: %u emitters read (%u bad), %u particle nodes bound (%u with a point list, %u bad)\n",
                stats.emittersRead, stats.badEmitters, stats.nodesBound, stats.nodesWithPointList, stats.badNodes);
    C15_CHECK(stats.emittersRead > 0 && stats.badEmitters == 0);
    // The plugin readers end 8 bytes past each plugin chunk, as measured on the original's streams.
    std::printf("gfx_c16: %u plugin streams, %u not ending 8 bytes past their chunk\n", stats.streamsRead,
                stats.streamLengthMismatches);
    C15_CHECK(stats.streamsRead > 0 && stats.streamLengthMismatches == 0);
    C15_CHECK(stats.nodesBound > 0 && stats.nodesWithPointList > 0 && stats.badNodes == 0);
}

// 0xa4be8 Camera_SetFovAndAspectFromRaster (the options' aspect ratio): the reference aspect kept, the
// aspects from the 1280x720 raster, the field of view (70) reapplied to the main camera's view window
// (tan 35 / (0.5625 * 4/3), tan 35 * 0.75), the 2D screen marked changed.
void CheckFovAndAspect(CameraContext* context) {
    const float previous = context->m_fReferenceAspect78;
    g_pEngine->m_manager2d->m_bUpdateScreen = 0;
    Camera_SetFovAndAspectFromRaster(0x1.c71c72p+0f, context);  // 16:9
    C15_CHECK(context->m_fReferenceAspect78 == 0x1.c71c72p+0f);
    C15_CHECK(context->m_fHeightOverWidth == 0x1.2p-1f && context->m_fDisplayAspect == 1280.0f / 720.0f);
    C15_CHECK(context->m_fAppliedFieldOfView == 70.0f && g_pEngine->m_manager2d->m_bUpdateScreen == 1);
    const RwV2d window = context->m_pMainCamera->viewWindow;
    std::printf("gfx_c16: main camera view window %a %a\n", window.x, window.y);
    C15_CHECK(std::fabs(window.x - 0.933610f) < 1e-5f && std::fabs(window.y - 0.525156f) < 1e-5f);
    Camera_SetFovAndAspectFromRaster(previous, context);
}

}  // namespace

int main() {
    std::setvbuf(stdout, nullptr, _IONBF, 0);
    dotd::platform::Config& config = dotd::platform::MutableConfig();
    dotd::platform::LoadConfig(0, nullptr, config);
    if (config.usrdir.empty()) {
        std::printf("gfx_c16: no game data configured; skipped\n");
        return 77;
    }
    config.hiddenWindow = true;
    config.vsync = false;
    config.frameRate = 0;
    if (!dotd::platform::sdl::Init(config) || !dotd::gfx::Init(1280, 720)) {
        std::printf("gfx_c16: no OpenGL 3.3 device; skipped\n");
        return 77;
    }
    dotd::platform::SetPadSource(&TestPad);
    if (!c15::BootToFrontEnd()) {
        std::printf("gfx_c16: boot failed\n");
        return 1;
    }
    CheckScale();
    CKS08GameManager* manager = static_cast<CKS08GameManager*>(g_pEngine->m_gameManager);
    CameraContext* context = Engine_GetCameraContext();
    C15_CHECK(context != nullptr);
    if (context == nullptr) return 1;
    CheckParticleEmitters();
    CheckFovAndAspect(context);
    // The start-up config's back colour (alpha cleared) until the logos.
    std::printf("gfx_c16: clear colour after the boot %08x\n", context->m_clearColor);

    uint32_t frame = 0;
    int lastState = -1, lastLogo = -2;
    int logoFrames = 0, logoClearOk = 0;
    bool copyrightsShot = false;
    uint32_t stateStart = 0;
    while (frame < 3000 && manager->m_gameState.m_ui8Current != 5) {
        // A stale colour to see State3 write it back every frame.
        if (manager->m_gameState.m_ui8Current == 3) context->m_clearColor = 0x12345600u;
        c15::RunFrame();
        ++frame;
        const int state = manager->m_gameState.m_ui8Current;
        if (state != lastState) {
            std::printf("gfx_c16: frame %u game state %d\n", frame, state);
            lastState = state;
            stateStart = frame;
        }
        if (state == 3) {
            ++logoFrames;
            if (context->m_clearColor == 0) ++logoClearOk;
            const int logo = manager->m_i32CurrentLogo;
            if (logo != lastLogo) {
                lastLogo = logo;
                stateStart = frame;
            }
            if (frame == stateStart + 40 && logo >= 0) {
                char name[32];
                std::snprintf(name, sizeof(name), "c16_logo%d.png", logo + 1);
                Shot(name);
            }
        }
        if (state == 4 && !copyrightsShot && frame == stateStart + 120) {
            Shot("c16_copyrights.png");
            copyrightsShot = true;
        }
    }
    std::printf("gfx_c16: logos: %d frames, clear colour 0 on %d\n", logoFrames, logoClearOk);
    C15_CHECK(logoFrames > 0 && logoClearOk == logoFrames);
    C15_CHECK(copyrightsShot);
    C15_CHECK(manager->m_gameState.m_ui8Current == 5);

    for (int i = 0; i < 90; ++i, ++frame) c15::RunFrame();
    Shot("c16_press_start.png");
    // "Press the START button" is plain text (RPCS3's live string has no glyph either).
    const std::pair<int, int> press = CheckPadGlyphs("press start", 0, nullptr);
    C15_CHECK(press.second == 0);

    g_startHeld = true;
    for (int i = 0; i < 6; ++i, ++frame) c15::RunFrame();
    g_startHeld = false;
    for (int i = 0; i < 600 && manager->m_gameState.m_ui8Current != 6; ++i, ++frame) c15::RunFrame();
    C15_CHECK(manager->m_gameState.m_ui8Current == 6);
    for (int i = 0; i < 90; ++i, ++frame) c15::RunFrame();
    Shot("c16_main_menu.png");
    // The Accept prompt: RPCS3's live CText2d holds U+E818 " Accept" (GetActionButtonGlyph: pad command
    // 0x0c * 2 - 0x1800, the cross), from the "#£..._#" token of its loc string.
    bool crossFound = false;
    const std::pair<int, int> menu = CheckPadGlyphs("main menu", 0xe818, &crossFound);
    C15_CHECK(menu.first > 0 && menu.second == 0 && crossFound);

    // CContainer2d::Scale on a loaded menu container: every node of both scenes scaled once (texts:
    // their box, auto-size off, a new layout).
    {
        CScene2d* menuScene = static_cast<CScene2d*>(
            static_cast<CMenuManager*>(g_pEngine->m_manager2d->m_menuManager)->m_pMenuSceneContainers);
        CContainer2d* container = nullptr;
        CText2d* text = nullptr;
        for (IKNode2d* c = static_cast<IKNode2d*>(menuScene->m_pRootNode); c != nullptr && text == nullptr; c = c->m_pNext) {
            if (c->IsKindOfClass(0x4cd) == 0) continue;
            CScene2d* others = static_cast<CScene2d*>(static_cast<CContainer2d*>(c)->m_pNonButtonObjects);
            if (others == nullptr) continue;
            for (IKNode2d* n = static_cast<IKNode2d*>(others->m_pRootNode); n != nullptr; n = n->m_pNext) {
                if (n->IsKindOfClass(0x5cd) != 0 && static_cast<CText2d*>(n)->m_pFont != nullptr) {
                    container = static_cast<CContainer2d*>(c);
                    text = static_cast<CText2d*>(n);
                    break;
                }
            }
        }
        C15_CHECK(text != nullptr);
        if (text != nullptr) {
            const CVector2 box = text->m_vBoxSize;
            container->Scale(CVector2{0x1p+1f, 0x1p-1f});
            std::printf("gfx_c16: container %s scaled: text box %g x %g -> %g x %g, %u lines\n", container->m_szName,
                        static_cast<double>(box.m_fX), static_cast<double>(box.m_fY),
                        static_cast<double>(text->m_vBoxSize.m_fX), static_cast<double>(text->m_vBoxSize.m_fY),
                        text->m_ui32BoxLinesCount);
            C15_CHECK(text->m_vBoxSize.m_fX == box.m_fX * 0x1p+1f && text->m_vBoxSize.m_fY == box.m_fY * 0x1p-1f);
            C15_CHECK(text->m_bAutoSize == 0);
        }
    }

    dotd::platform::SetPadSource(nullptr);
    c15::Shutdown();
    dotd::gfx::Shutdown();
    dotd::platform::sdl::Shutdown();
    if (c15::g_failures == 0) std::printf("gfx_c16: all tests passed\n");
    return c15::g_failures == 0 ? 0 : 1;
}
