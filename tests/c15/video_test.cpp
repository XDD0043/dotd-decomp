// video_test - checkpoint C1.4, family video: Bink playback through the ported PS3_CKVideo / CVideoManager.
// Boots to the front end (headless), then plays GAME.KP3's videos as the game starts them, one game frame
// at a time (1/60 s of the fake system clock that also drives Bink's timer):
//   - the boot loading video #4 (MOVIE\00\PS3_005.VID, 800x200, 25 fps, loops) as CVideoManager's loading
//     video (PlayLoadingVideo; updated and drawn by CVideoManager::Render);
//   - the press-start background #2 (MOVIE\00\PS3_003.VID, 1280x720, 50 fps) through Start (vt+0x60), in the
//     manager's running list (PreUpdate / UpdateAndExtract / Render from the frame);
//   - the main-menu background #3 (PS3_004) on a CKVideoSegment like LVL000's [0] (intro 1-80, loop 81-1581,
//     mode 2): the jump at the intro's end.
// Checks: the frame counter advances at the video's rate (frames shown / game frames = fps / 60), the
// display rectangle (stretch for the 800x200 strip, fit for 16:9), the segment jump. PNGs of decoded
// frames (luma, and RGB by the BT.601 constants of the PS3 shader) go next to DOTD_DUMP_OBJECTS (or the
// current directory): c14-video-ps3_005.png, c14-video-ps3_003.png, c14-video-ps3_004.png.
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

#include "boot_helper.h"
#include "k2000/graphical/system/CKVideoSegment.h"
#include "k2000/graphical/system/CVideoManager.h"
#include "k2000/graphical/system/PS3_CKVideo.h"
#include "k2000/misc/Engine.h"
#include "k2000/render/CRenderer.h"
#include "k2000/managers/CKGraphic.h"
#include "platform/video/bink.h"

namespace {

// ---- a minimal PNG writer (stored deflate blocks) --------------------------------------------------
uint32_t Crc32(const uint8_t* data, size_t size, uint32_t crc = 0) {
    crc = ~crc;
    for (size_t i = 0; i < size; ++i) {
        crc ^= data[i];
        for (int k = 0; k < 8; ++k) crc = (crc >> 1) ^ (0xedb88320u & (0u - (crc & 1u)));
    }
    return ~crc;
}
void Put32(std::vector<uint8_t>& out, uint32_t v) {
    out.push_back(static_cast<uint8_t>(v >> 24));
    out.push_back(static_cast<uint8_t>(v >> 16));
    out.push_back(static_cast<uint8_t>(v >> 8));
    out.push_back(static_cast<uint8_t>(v));
}
void Chunk(std::vector<uint8_t>& out, const char* type, const std::vector<uint8_t>& data) {
    Put32(out, static_cast<uint32_t>(data.size()));
    std::vector<uint8_t> body(type, type + 4);
    body.insert(body.end(), data.begin(), data.end());
    out.insert(out.end(), body.begin(), body.end());
    Put32(out, Crc32(body.data(), body.size()));
}
bool WritePng(const std::string& path, int width, int height, int channels, const std::vector<uint8_t>& pixels) {
    std::vector<uint8_t> raw;
    for (int y = 0; y < height; ++y) {
        raw.push_back(0);
        raw.insert(raw.end(), pixels.begin() + static_cast<size_t>(y) * width * channels,
                   pixels.begin() + static_cast<size_t>(y + 1) * width * channels);
    }
    std::vector<uint8_t> z = {0x78, 0x01};
    uint32_t a = 1, b = 0;
    for (uint8_t v : raw) {
        a = (a + v) % 65521u;
        b = (b + a) % 65521u;
    }
    for (size_t pos = 0; pos < raw.size(); pos += 65535) {
        const size_t n = raw.size() - pos < 65535 ? raw.size() - pos : 65535;
        z.push_back(pos + n == raw.size() ? 1 : 0);
        z.push_back(static_cast<uint8_t>(n));
        z.push_back(static_cast<uint8_t>(n >> 8));
        z.push_back(static_cast<uint8_t>(~n));
        z.push_back(static_cast<uint8_t>(~n >> 8));
        z.insert(z.end(), raw.begin() + pos, raw.begin() + pos + n);
    }
    Put32(z, (b << 16) | a);
    std::vector<uint8_t> out = {0x89, 'P', 'N', 'G', 0x0d, 0x0a, 0x1a, 0x0a};
    std::vector<uint8_t> ihdr;
    Put32(ihdr, static_cast<uint32_t>(width));
    Put32(ihdr, static_cast<uint32_t>(height));
    ihdr.push_back(8);
    ihdr.push_back(channels == 3 ? 2 : 0);
    ihdr.push_back(0);
    ihdr.push_back(0);
    ihdr.push_back(0);
    Chunk(out, "IHDR", ihdr);
    Chunk(out, "IDAT", z);
    Chunk(out, "IEND", {});
    std::FILE* f = std::fopen(path.c_str(), "wb");
    if (f == nullptr) return false;
    std::fwrite(out.data(), 1, out.size(), f);
    std::fclose(f);
    return true;
}

std::string OutputDir() {
    const char* dump = std::getenv("DOTD_DUMP_OBJECTS");
    if (dump == nullptr) return std::string();
    std::string dir = dump;
    const size_t slash = dir.find_last_of("/\\");
    return slash == std::string::npos ? std::string() : dir.substr(0, slash + 1);
}

uint8_t Clamp255(float v) {
    if (v <= 0.0f) return 0;
    if (v >= 1.0f) return 255;
    return static_cast<uint8_t>(v * 255.0f + 0.5f);
}

// The decoded planes as a luma image (top) and the PS3 shader's RGB (bottom).
void SaveFrame(BINK* bink, const char* name) {
    dotd::video::DecodedPlanes p{};
    C15_CHECK(dotd::video::GetDecodedPlanes(bink, &p));
    if (p.frame == 0) return;
    std::vector<uint8_t> rgb(static_cast<size_t>(p.width) * p.height * 2 * 3);
    for (int y = 0; y < p.height; ++y) {
        for (int x = 0; x < p.width; ++x) {
            const float Y = p.y[y * p.yPitch + x] / 255.0f;
            const float cr = p.cr[(y / 2) * p.cPitch + x / 2] / 255.0f;
            const float cb = p.cb[(y / 2) * p.cPitch + x / 2] / 255.0f;
            uint8_t* top = &rgb[(static_cast<size_t>(y) * p.width + x) * 3];
            top[0] = top[1] = top[2] = p.y[y * p.yPitch + x];
            uint8_t* bottom = &rgb[(static_cast<size_t>(y + p.height) * p.width + x) * 3];
            bottom[0] = Clamp255(1.164123535f * Y + 1.595794678f * cr - 0.87065506f);
            bottom[1] = Clamp255(1.164123535f * Y - 0.813476563f * cr - 0.391448975f * cb + 0.529705048f);
            bottom[2] = Clamp255(1.164123535f * Y + 2.017822266f * cb - 1.081668854f);
        }
    }
    const std::string path = OutputDir() + name;
    C15_CHECK(WritePng(path, p.width, p.height * 2, 3, rgb));
    std::printf("saved %s (frame %u, %dx%d)\n", path.c_str(), p.frame, p.width, p.height);
}

// The video manager's GAME.KP3 video whose file name contains `name` (the array order is not the GAME.KP3
// object order of frontend-rendering.md's table).
PS3_CKVideo* VideoNamed(const char* name) {
    CVideoManager* manager = g_pEngine->m_videoManager;
    if (manager == nullptr) return nullptr;
    for (uint32_t i = 0; i < manager->m_ui32VideoNb; ++i) {
        PS3_CKVideo* video = static_cast<PS3_CKVideo*>(manager->m_apVideoArray[i]);
        if (video != nullptr && std::strstr(video->m_szFileName, name) != nullptr) return video;
    }
    return nullptr;
}

// Runs frames and counts the distinct frames Bink showed. Returns the count of FrameNum changes.
uint32_t RunAndCount(PS3_CKVideo* video, uint32_t frames, std::vector<uint32_t>* positions = nullptr) {
    uint32_t changes = 0;
    uint32_t last = video->m_pBink != nullptr ? video->m_pBink->FrameNum : 0;
    for (uint32_t i = 0; i < frames; ++i) {
        c15::RunFrame();
        const uint32_t now = video->m_pBink != nullptr ? video->m_pBink->FrameNum : 0;
        if (now != last) ++changes;
        last = now;
        if (positions != nullptr) positions->push_back(now);
    }
    return changes;
}

}  // namespace

int main() {
    if (!c15::BootToFrontEnd()) {
        std::printf("skipped: no game data\n");
        return 77;
    }
    c15::ParkFrontEndSequence();  // this harness drives the movies / videos itself
    if (!dotd::video::HasBinkDecoder()) {
        std::printf("skipped: built without the FFmpeg clone\n");
        c15::Shutdown();
        return 77;
    }
    CVideoManager* manager = g_pEngine->m_videoManager;
    C15_CHECK(manager != nullptr);
    C15_CHECK(manager->m_ui32VideoNb == 74);
    std::printf("videos: %u; loading video after boot: %p\n", manager->m_ui32VideoNb,
                static_cast<void*>(manager->m_pLoadingVideo));
    bool inRenderList = false;
    for (CRenderer::RendableNode* node = g_pEngine->m_graphic->m_renderer->m_lRenderableObjectList; node != nullptr;
         node = node->m_pNext) {
        if (node->m_pObject == manager) inRenderList = true;
    }
    std::printf("video manager in the renderer's list: %d\n", inRenderList ? 1 : 0);

    // ---- #4 PS3_005: the boot loading video ----------------------------------------------------------
    PS3_CKVideo* loading = VideoNamed("PS3_005");
    C15_CHECK(loading != nullptr && std::strstr(loading->m_szFileName, "PS3_005") != nullptr);
    if (loading != nullptr) {
        std::printf("#4 %s flags %08x alpha %u ratio %g\n", loading->m_szFileName, loading->m_baData,
                    loading->m_ui32AlphaLevel, loading->m_fRatio);
        manager->m_pLoadingVideo = loading;
        manager->PlayLoadingVideo();
        C15_CHECK(manager->IsLoadingVideoActive());
        C15_CHECK(loading->m_pBink != nullptr);
        C15_CHECK(loading->m_state == 5);
        if (loading->m_pBink != nullptr) {
            C15_CHECK(loading->m_pBink->Width == 800 && loading->m_pBink->Height == 200);
            C15_CHECK(loading->m_pBink->Frames == 25);
            const uint32_t shown = RunAndCount(loading, 120);  // 2 s: 50 frames at 25 fps
            std::printf("#4: %u frame changes in 120 game frames (expect ~50), now frame %u\n", shown,
                        loading->m_pBink->FrameNum);
            C15_CHECK(shown >= 47 && shown <= 52);
            // Flags 0x49c88 include 0x800 (fit) and its H/W 0.25 is below the screen's 0.5625: letterboxed,
            // 1280 x 320 at y = 200 (not stretched, as frontend-rendering.md 3.4 guessed).
            std::printf("#4 rect: pos (%g, %g) scale (%g, %g)\n", loading->m_fPosX, loading->m_fPosY,
                        loading->m_fScaleX, loading->m_fScaleY);
            C15_CHECK(loading->m_fScaleX == 1.6f && loading->m_fScaleY == 1.6f);
            C15_CHECK(loading->m_fPosX == 0.0f && loading->m_fPosY == 200.0f);
            SaveFrame(loading->m_pBink, "c14-video-ps3_005.png");
        }
        manager->StopLoadingVideo();
        C15_CHECK(!manager->IsLoadingVideoActive());
        C15_CHECK(loading->m_state == 0 && loading->m_pBink == nullptr);
    }

    // ---- #2 PS3_003: press start --------------------------------------------------------------------
    PS3_CKVideo* pressStart = VideoNamed("PS3_003");
    C15_CHECK(pressStart != nullptr && std::strstr(pressStart->m_szFileName, "PS3_003") != nullptr);
    if (pressStart != nullptr) {
        std::printf("#2 %s flags %08x alpha %u ratio %g\n", pressStart->m_szFileName, pressStart->m_baData,
                    pressStart->m_ui32AlphaLevel, pressStart->m_fRatio);
        C15_CHECK(pressStart->Start(nullptr) == 1);
        C15_CHECK(pressStart->m_state == 1);
        C15_CHECK(manager->m_lRunningVideo != nullptr && manager->m_lRunningVideo->m_pVideo == pressStart);
        // Without the renderer list entry the frame does not update it: drive the manager like the frame does.
        const uint32_t frames = 120;  // 2 s: 100 frames at 50 fps
        uint32_t shown = 0;
        uint32_t last = 0;
        for (uint32_t i = 0; i < frames; ++i) {
            if (!inRenderList) {
                manager->PreUpdate(nullptr);
                manager->UpdateAndExtract(0.0f, nullptr, nullptr, nullptr, 0);
            }
            c15::RunFrame();
            const uint32_t now = pressStart->m_pBink != nullptr ? pressStart->m_pBink->FrameNum : 0;
            if (now != last) ++shown;
            last = now;
        }
        C15_CHECK(pressStart->m_state == 5);
        std::printf("#2: %u frame changes in %u game frames (expect ~100), now frame %u\n", shown, frames, last);
        C15_CHECK(shown >= 97 && shown <= 102);
        std::printf("#2 rect: pos (%g, %g) scale (%g, %g)\n", pressStart->m_fPosX, pressStart->m_fPosY,
                    pressStart->m_fScaleX, pressStart->m_fScaleY);
        C15_CHECK(pressStart->m_fScaleX == 1.0f && pressStart->m_fScaleY == 1.0f);
        C15_CHECK(manager->HasFullscreenVideo());
        if (pressStart->m_pBink != nullptr) SaveFrame(pressStart->m_pBink, "c14-video-ps3_003.png");
        pressStart->Stop();
        C15_CHECK(pressStart->m_state == 0 && manager->m_lRunningVideo == nullptr);
    }

    // ---- #3 PS3_004 on a segment like LVL000's [0] ----------------------------------------------------
    PS3_CKVideo* menu = VideoNamed("PS3_004");
    C15_CHECK(menu != nullptr && std::strstr(menu->m_szFileName, "PS3_004") != nullptr);
    if (menu != nullptr) {
        auto makeSegment = [menu](CKVideoSegment& s, uint32_t start, uint32_t introEnd, uint32_t loop, uint32_t end) {
            s.Load(nullptr, 99);  // the stores every type makes (m_ended = 1, mode 0)
            s.m_startFrame = start;
            s.m_introEndFrame = introEnd;
            s.m_loopStartFrame = loop;
            s.m_endFrame = end;
            s.m_defaultMode = CKVideoSegment::kModeLoop;
            s.m_pVideo = menu;
        };
        auto run = [&](uint32_t frames, std::vector<uint32_t>* positions) {
            for (uint32_t i = 0; i < frames; ++i) {
                if (!inRenderList) {
                    manager->PreUpdate(nullptr);
                    manager->UpdateAndExtract(0.0f, nullptr, nullptr, nullptr, 0);
                }
                c15::RunFrame();
                // The frame on screen (the set Bink decoded last).
                dotd::video::DecodedPlanes p{};
                positions->push_back(dotd::video::GetDecodedPlanes(menu->m_pBink, &p) ? p.frame : 0);
            }
        };
        // LVL000's three segments on PS3_004: [0] 1-80 / 81-1581, [2] 1582-1687 / 1688-3188, [1] 3189-3268 / 3269-4768.
        CKVideoSegment main, chapter, shortLoop;
        makeSegment(main, 1, 80, 81, 1581);
        makeSegment(chapter, 1582, 1687, 1688, 3188);
        main.Play(CKVideoSegment::kModeDefault, 0, 0);
        C15_CHECK(main.m_mode == CKVideoSegment::kModeLoop && main.m_ended == 0);
        C15_CHECK(menu->m_pSegment == &main);
        // 3 s: the intro (80 frames at 50 fps) runs into the loop at 81 (a keyframe: the jump is seamless).
        std::vector<uint32_t> a;
        run(150, &a);
        std::printf("#3 %s flags %08x; keyframes:", menu->m_szFileName, menu->m_baData);
        for (uint32_t f = 1; menu->m_pBink != nullptr && f <= menu->m_pBink->Frames; ++f) {
            const uint32_t k = BinkGetKeyFrame(menu->m_pBink, f, BINKGETKEYNEXT);
            if (k == 0) break;
            std::printf(" %u", k);
            f = k;
        }
        std::printf("\n");
        bool monotonic = true;
        for (size_t i = 1; i < a.size(); ++i) monotonic = monotonic && a[i] >= a[i - 1];
        std::printf("#3 main: frames %u .. %u over 150 game frames, monotonic %d\n", a.front(), a.back(),
                    monotonic ? 1 : 0);
        C15_CHECK(monotonic && a.back() >= 115 && a.back() <= 130);
        // Switching menus: the same stream seeks to the chapter segment (the keyframe closest to 1582).
        chapter.Play(CKVideoSegment::kModeDefault, 0, 0);
        C15_CHECK(menu->m_pSegment == &chapter && main.m_ended == 1);
        const uint32_t key1582 = BinkGetKeyFrame(menu->m_pBink, 1582, BINKGETKEYCLOSEST);
        std::vector<uint32_t> b;
        run(30, &b);
        std::printf("#3 chapter: keyframe closest to 1582: %u; frames %u .. %u over 30 game frames\n", key1582,
                    b.front(), b.back());
        C15_CHECK(b.front() >= key1582 && b.front() <= key1582 + 2 && b.back() >= key1582 + 20);
        if (menu->m_pBink != nullptr) SaveFrame(menu->m_pBink, "c14-video-ps3_004.png");
        // A short loop (synthetic, no intro) shows the end jump: at frame 120 back to the keyframe closest to
        // 81. (With an intro end before a non-keyframe loop start, the keyframe seek would land in the intro
        // again: the real segments start their loops on keyframes.)
        makeSegment(shortLoop, 81, 81, 81, 120);
        shortLoop.Play(CKVideoSegment::kModeDefault, 0, 0);
        std::vector<uint32_t> c;
        run(120, &c);
        uint32_t jumps = 0, from = 0, to = 0;
        for (size_t i = 1; i < c.size(); ++i) {
            if (c[i] < c[i - 1]) {
                ++jumps;
                from = c[i - 1];
                to = c[i];
            }
        }
        const uint32_t key81 = BinkGetKeyFrame(menu->m_pBink, 81, BINKGETKEYCLOSEST);
        std::printf("#3 short loop: %u jumps, last from %u to %u (keyframe closest to 81: %u), max %u\n", jumps, from,
                    to, key81, *std::max_element(c.begin(), c.end()));
        C15_CHECK(jumps >= 2 && from == 120 && to == key81);
        menu->Stop();
        C15_CHECK(shortLoop.m_ended == 1 && menu->m_state == 0);
    }

    c15::Shutdown();
    std::printf("video_test: %d failure(s)\n", c15::g_failures);
    return c15::g_failures == 0 ? 0 : 1;
}
