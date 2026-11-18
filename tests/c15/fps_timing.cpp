// fps_timing - measures the game's timings in seconds of game clock at a chosen frame rate, for the --fps N timing
// calculation (platform/fps.h). Not a ctest: run it by hand at 60 (DOTD_TEST_FPS unset), 144, 240 and 0 (irregular
// uncapped frames), with DOTD_TEST_FPS_RAW=1 to see the per-update systems without the calculation; compare the
// printed seconds. Headless, the fake clock of boot_helper (1/N s per frame), the pad driven by the harness.
//
// Measured (all from the game's own state, with the time of the frame they are first seen in):
//   front end: the copyrights' end (game state 4 -> 3), press start shown (state 5);
//   main menu (movie #0) and game menu (#2): the Flash labels onMenu_Video#1_Open -> onMenu_OpeningAnimEnd (Maestro:
//   61 and 58 frames at 60 fps), the main menu's closing animation (Cross -> onMenu_ClosingAnimEnd);
//   new game: the level start (mode 5, state 7), the opening video (mode 8 -> mode 5: Bink, paced by wall time), the
//   in-engine scene after it: its sekensor bloc done, its first path bloc done (actors walking), control given back
//   (60 fps: 255 / 336 / 558 frames after the video), the scene over.
// FPS_TIMING_TRACE=1 also prints every flag change of the scene's elements and the sekens line's state, to find which
// link of a chain moves when two rates disagree.
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <typeinfo>
#include <vector>

#include "Renderware/rt2danim/Rt2dAnim.h"
#include "Renderware/rt2danim/Rt2dAnimPrivate.h"
#include "Spyro2008/logic/CKS08GameManager.h"
#include "boot_helper.h"
#include "k2000/graphical/ui/CKFlashManager.h"
#include "k2000/graphical/ui/CKFlashUI.h"
#include "k2000/logic/CKCinematicScene.h"
#include "k2000/misc/CKGameLoop.h"
#include "k2000/misc/CoreSingletons.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/IKCinematicElement.h"
#include "k2000/logic/CKSekens.h"
#include "k2000/logic/CKSekensBlock.h"
#include "k2000/services/CKSrvCinematic.h"
#include "k2000/services/CKSrvSekensor.h"
#include "k2000/system/CTimeManager.h"
#include "k2000/system/IKTime.h"
#include "platform/cell/pad.h"
#include "platform/fps.h"

namespace {

uint16_t g_d1 = 0, g_d2 = 0;
uint32_t g_frame = 0;
int64_t g_t0 = 0;

bool TestPad(int port, uint16_t words[24]) {
    if (port != 0) return false;
    std::memset(words, 0, 24 * sizeof(uint16_t));
    words[CELL_PAD_BTN_OFFSET_DIGITAL1] = g_d1;
    words[CELL_PAD_BTN_OFFSET_DIGITAL2] = g_d2;
    for (int i = CELL_PAD_BTN_OFFSET_ANALOG_RIGHT_X; i <= CELL_PAD_BTN_OFFSET_ANALOG_LEFT_Y; ++i) words[i] = 0x80;
    return true;
}

double Now() { return static_cast<double>(c15::NowMicros() - g_t0) / 1e6; }
CKS08GameManager* M() { return static_cast<CKS08GameManager*>(g_pEngine->m_gameManager); }

struct Label {
    double t;
    int32_t movie;
    std::string name;
};
std::vector<Label> g_labels;

int32_t MovieOf(Rt2dMaestro* maestro) {
    CKFlashManager* manager = g_pEngine->m_flashManager;
    for (uint32_t i = 0; i < manager->m_ui32NbFlashUI; ++i)
        if (manager->GetInterfaceByIndex(i)->m_pMaestro == maestro) return static_cast<int32_t>(i);
    return -1;
}

Rt2dMessage* LoggingHandler(Rt2dMaestro* maestro, Rt2dMessage* message) {
    if (message->messageType == rt2dMESSAGETYPEGETURL) {
        Rt2dStringLabel* label = Rt2dMaestroGetStringLabelByIndex(maestro, message->intParam1);
        const RwChar* name = label != nullptr ? Rt2dMaestroGetStringLabelName(maestro, label) : nullptr;
        g_labels.push_back(Label{Now(), MovieOf(maestro), name != nullptr ? name : "?"});
    }
    return CKFlashManager::HandleMaestroEvent(maestro, message);
}

double FindLabel(int32_t movie, const char* name, double after) {
    for (const Label& l : g_labels)
        if (l.movie == movie && l.name == name && l.t >= after) return l.t;
    return -1.0;
}

int g_lastState = -1;
double g_levelStart = -1.0, g_videoStart = -1.0, g_videoEnd = -1.0;
void Step() {
    c15::RunFrame();
    ++g_frame;
    // The level's milestones, seen every frame (a 144 fps frame is short: the harness's waits could step over them).
    if (g_levelStart < 0.0 && g_pCKGameLoop->m_mode == 5 && M()->m_gameState.m_ui8Current == 7) g_levelStart = Now();
    if (g_levelStart >= 0.0 && g_videoStart < 0.0 && g_pCKGameLoop->m_mode == 8) g_videoStart = Now();
    if (g_videoStart >= 0.0 && g_videoEnd < 0.0 && g_pCKGameLoop->m_mode == 5) g_videoEnd = Now();
    const int key = g_pCKGameLoop->m_mode * 1000 + M()->m_gameState.m_ui8Current;
    if (key != g_lastState) {
        std::printf("fps_timing: %9.4f s frame %6u mode %d game state %d\n", Now(), g_frame, g_pCKGameLoop->m_mode,
                    M()->m_gameState.m_ui8Current);
        g_lastState = key;
    }
}

template <typename Pred>
double RunUntil(Pred pred, double maxSeconds) {
    const double end = Now() + maxSeconds;
    while (Now() < end) {
        if (pred()) return Now();
        Step();
    }
    return pred() ? Now() : -1.0;
}

void RunFor(double seconds) {
    RunUntil([] { return false; }, seconds);
}

void Hold(uint16_t d1, uint16_t d2, double seconds) {
    g_d1 = d1;
    g_d2 = d2;
    RunFor(seconds);
    g_d1 = g_d2 = 0;
    RunFor(0.05);
}

void Report(const char* what, double from, double to, double frames60) {
    const double span = (from >= 0.0 && to >= 0.0) ? to - from : -1.0;
    std::printf("fps_timing: RESULT %-46s %9.4f s  (60 fps reference %4.0f frames = %8.4f s, diff %+7.4f s)\n", what, span,
                frames60, frames60 / 60.0, span < 0.0 ? 0.0 : span - frames60 / 60.0);
}

}  // namespace

int main() {
    std::setvbuf(stdout, nullptr, _IONBF, 0);
    dotd::platform::SetPadSource(&TestPad);
    if (!c15::BootToFrontEnd()) return 77;
    g_t0 = c15::NowMicros();
    std::printf("fps_timing: fake clock %d fps (0 = irregular uncapped), 60 Hz timing calculation %s\n", c15::TestFps(),
                dotd::fps::Unlocked() ? "on" : "off");
    CKFlashManager* flash = g_pEngine->m_flashManager;
    uint32_t fixedStep = 0;
    for (uint32_t i = 0; i < flash->m_ui32NbFlashUI; ++i) {
        CKFlashUI* ui = flash->GetInterfaceByIndex(i);
        if (ui->m_pMaestro != nullptr) Rt2dMaestroSetMessageHandler(ui->m_pMaestro, LoggingHandler);
        if ((ui->m_baFlags & 0x80u) != 0) {  // kFixedTimeStep: the movie advances 0.02 s per update
            ++fixedStep;
            std::printf("fps_timing: Flash interface #%u has the fixed time step\n", i);
        }
    }
    std::printf("fps_timing: %u of %u Flash interfaces at the front end have the fixed time step\n", fixedStep,
                flash->m_ui32NbFlashUI);

    // The front end's own sequence: copyrights (state 4), logos (3), press start (5).
    const double copyrightsEnd = RunUntil([] { return M()->m_gameState.m_ui8Current == 3; }, 60.0);
    const double pressStart = RunUntil([] { return M()->m_gameState.m_ui8Current == 5; }, 120.0);
    RunFor(0.5);
    const double startAt = Now();
    Hold(CELL_PAD_CTRL_START, 0, 0.1);
    const double mainEnd = RunUntil([&] { return FindLabel(0, "onMenu_OpeningAnimEnd", startAt) >= 0.0; }, 10.0);
    const double mainOpen = FindLabel(0, "onMenu_Video#1_Open", startAt);
    RunFor(1.5);
    const double crossAt = Now();
    Hold(0, CELL_PAD_CTRL_CROSS, 0.07);
    const double gameEnd = RunUntil([&] { return FindLabel(2, "onMenu_OpeningAnimEnd", crossAt) >= 0.0; }, 10.0);
    const double mainClosed = FindLabel(0, "onMenu_ClosingAnimEnd", crossAt);
    const double gameOpen = FindLabel(2, "onMenu_Video#1_Open", crossAt);
    RunFor(1.5);

    // New game: Cross (Start Story Mode -> start player), Cross (Single Player), until the level starts.
    for (int k = 0; k < 6 && g_pCKGameLoop->m_mode == 5 && g_levelStart < 0.0; ++k) {
        Hold(0, CELL_PAD_CTRL_CROSS, 0.07);
        RunUntil([] { return g_pCKGameLoop->m_mode != 5 || g_levelStart >= 0.0; }, 2.5);
    }
    RunUntil([] { return g_levelStart >= 0.0; }, 120.0);
    const double levelStart = g_levelStart;
    {
        uint32_t levelFixed = 0;
        for (uint32_t i = 0; i < flash->m_ui32NbFlashUI; ++i) {
            CKFlashUI* ui = flash->GetInterfaceByIndex(i);
            if (ui->m_pMaestro != nullptr) Rt2dMaestroSetMessageHandler(ui->m_pMaestro, LoggingHandler);
            if ((ui->m_baFlags & 0x80u) != 0) ++levelFixed;
        }
        std::printf("fps_timing: %u of %u Flash interfaces in the level have the fixed time step\n", levelFixed,
                    flash->m_ui32NbFlashUI);
    }
    RunUntil([] { return g_videoEnd >= 0.0; }, 400.0);
    const double videoStart = g_videoStart;
    const double videoEnd = g_videoEnd;

    // The in-engine scene after the video.
    CKSrvCinematic* service = static_cast<CKSrvCinematic*>(g_pEngine->m_srvCinematic);
    int inEngine = -1;
    bool blocked = false;
    double sceneStart = -1.0, sekensor = -1.0, path = -1.0, control = -1.0, over = -1.0;
    RunUntil(
        [&] {
            if (inEngine < 0) {
                for (uint32_t s = 0; s < service->m_ui32SceneNumber; ++s) {
                    const CKCinematicScene* scene = static_cast<CKCinematicScene*>(service->m_pSceneList[s]);
                    if ((scene->m_baData & 1) != 0 && (scene->m_baData & 0x40) == 0 && scene->m_ui32CinematicPointerLength > 10) {
                        inEngine = static_cast<int>(s);
                        sceneStart = Now();
                        break;
                    }
                }
                if (inEngine < 0) return false;
            }
            const CKCinematicScene* scene = static_cast<CKCinematicScene*>(service->m_pSceneList[inEngine]);
            for (uint32_t k = 0; k < scene->m_ui32CinematicPointerLength; ++k) {
                IKCinematicElement* element = static_cast<IKCinematicElement*>(scene->m_pCinematicPointerList[k]);
                if (std::getenv("FPS_TIMING_TRACE") != nullptr && k == 0) {
                    static const CKSekens* s_sek = nullptr;
                    static int32_t s_line = -9;
                    static uint32_t s_state = 99;
                    const CKSekens* sek = static_cast<CKSrvSekensor*>(g_pEngine->m_srvSekensor)->GetCurrentSekens();
                    const int32_t line = sek != nullptr ? sek->m_i32CurrentLine : -9;
                    const uint32_t state = sek != nullptr ? sek->m_ui32SpeechState : 99;
                    if (sek != s_sek || line != s_line || state != s_state) {
                        std::printf("fps_timing: sekens %9.4f s (+%.4f) %p line %d speech state %u start %.4f game %.4f scaled %.4f\n", Now(), Now() - g_videoEnd,
                                    static_cast<const void*>(sek), line, state, sek != nullptr ? sek->m_fLineStartTime : 0.0f, g_pEngine->m_timeManager->m_pTime->m_afCurrentTime[1], g_pEngine->m_timeManager->m_pTime->m_afCurrentTime[0]);
                        s_sek = sek; s_line = line; s_state = state;
                    }
                    if (sek != nullptr && line >= 0) {
                        const CKSekensBlock* b = static_cast<const CKSekensBlock*>(sek->m_vBlocks.m_pBlock[line]);
                        static float s_w = -99.0f;
                        static uint32_t s_n = 99;
                        if ((b->m_unk14 <= 0.0f) != (s_w <= 0.0f) || s_n != sek->m_unk3c && sek->m_unk3c < 4) {
                            std::printf("fps_timing: sekens line %d wait %.4f (time %.4f, line time %.4f) updates %u blocks %u flags 0x%x at %.4f\n", line,
                                        b->m_unk14, b->m_fTime,
                                        reinterpret_cast<const float*>(sek->m_pDataBuffers->m_aWords0)[line], sek->m_unk3c,
                                        sek->m_vBlocks.m_ui32NbUsedElt, sek->m_flags, Now() - g_videoEnd);
                        }
                        s_w = b->m_unk14;
                        s_n = sek->m_unk3c;
                    }
                }
                if (std::getenv("FPS_TIMING_TRACE") != nullptr) {
                    static uint32_t s_flags[256];
                    if (k < 256 && s_flags[k] != element->m_DataFlags) {
                        std::printf("fps_timing: trace %9.4f s (+%.4f) element %u %s flags 0x%x -> 0x%x\n", Now(), Now() - g_videoEnd, k,
                                    typeid(*element).name(), s_flags[k], static_cast<uint32_t>(element->m_DataFlags));
                        s_flags[k] = element->m_DataFlags;
                    }
                }
                if ((element->m_DataFlags & 4) == 0) continue;
                if (sekensor < 0.0 && element->IsKindOfClass(0x508) != 0) sekensor = Now();
                if (path < 0.0 && element->IsKindOfClass(0x108) != 0) path = Now();
            }
            if (M()->IsInputBlocked() != 0) blocked = true;
            else if (blocked && control < 0.0) control = Now();
            if (control >= 0.0 && over < 0.0 && (scene->m_baData & 1) == 0) over = Now();
            return over >= 0.0;
        },
        40.0);
    RunFor(2.0);
    const bool introHolds = M()->IsInputBlocked() != 0 && M()->m_interfaceState.m_ui8Current == 0x10 &&
                            g_pEngine->m_timeManager->m_fTimeScale == 0.0f;

    for (const Label& l : g_labels)
        if (l.t >= levelStart) std::printf("fps_timing: label %9.4f s #%d %s\n", l.t, l.movie, l.name.c_str());
    std::printf("fps_timing: %u frames, %.3f s of game clock (%.2f frames per second)\n", g_frame, Now(), g_frame / Now());
    Report("boot -> copyrights end (state 4 -> 3)", 0.0, copyrightsEnd, 0);
    Report("boot -> press start shown (state 5)", 0.0, pressStart, 0);
    Report("main menu opening (#0 Video#1_Open -> OpeningAnimEnd)", mainOpen, mainEnd, 61);
    Report("main menu closing (Cross -> #0 ClosingAnimEnd)", crossAt, mainClosed, 0);
    Report("game menu opening (#2 Video#1_Open -> OpeningAnimEnd)", gameOpen, gameEnd, 58);
    Report("level start (state 7) -> opening video starts (mode 8)", levelStart, videoStart, 0);
    Report("opening video (mode 8 -> mode 5)", videoStart, videoEnd, 0);
    Report("video end -> in-engine scene seen playing", videoEnd, sceneStart, 0);
    Report("video end -> sekensor bloc done", videoEnd, sekensor, 255);
    Report("video end -> first path bloc done (actors walk)", videoEnd, path, 336);
    Report("video end -> control given back", videoEnd, control, 558);
    Report("video end -> in-engine scene over", videoEnd, over, 0);
    std::printf("fps_timing: RESULT the first fight's intro holds the input after the scene: %s\n", introHolds ? "yes" : "no");
    std::fflush(stdout);
    std::_Exit(0);  // the engine's load threads are still running (as newgame_test)
}
