// perf.cpp - see perf.h. New platform code (debug / profiling only).
#include "platform/gfx/perf.h"

#include <chrono>
#include <cstdio>
#include <cstdlib>

#include "platform/gfx/gl.h"
#include "platform/log.h"

#if defined(_WIN32)
extern "C" {
__declspec(dllimport) void* __stdcall GetModuleHandleA(const char* name);
__declspec(dllimport) void* __stdcall GetProcAddress(void* module, const char* name);
}
#endif

namespace dotd::gfx::perf {

bool g_enabled = false;
uint64_t g_counters[kCounterCount] = {};

namespace {

using Clock = std::chrono::steady_clock;

// Timer queries (desktop GL 3.3 core; EXT_disjoint_timer_query elsewhere): optional.
constexpr GLenum kTimeElapsed = 0x88BF;
constexpr GLenum kQueryResult = 0x8866;
constexpr GLenum kQueryResultAvailable = 0x8867;
typedef void(DOTD_GLAPI* PFN_GenQueries)(GLsizei n, GLuint* ids);
typedef void(DOTD_GLAPI* PFN_DeleteQueries)(GLsizei n, const GLuint* ids);
typedef void(DOTD_GLAPI* PFN_BeginQuery)(GLenum target, GLuint id);
typedef void(DOTD_GLAPI* PFN_EndQuery)(GLenum target);
typedef void(DOTD_GLAPI* PFN_GetQueryObjectuiv)(GLuint id, GLenum pname, GLuint* value);
typedef void(DOTD_GLAPI* PFN_GetQueryObjectui64v)(GLuint id, GLenum pname, uint64_t* value);
PFN_GenQueries glGenQueries_ = nullptr;
PFN_DeleteQueries glDeleteQueries_ = nullptr;
PFN_BeginQuery glBeginQuery_ = nullptr;
PFN_EndQuery glEndQuery_ = nullptr;
PFN_GetQueryObjectuiv glGetQueryObjectuiv_ = nullptr;
PFN_GetQueryObjectui64v glGetQueryObjectui64v_ = nullptr;

constexpr int kQueries = 8;
// A frame longer than this logs a "gfxstats hitch" line: half a 60 Hz frame natively. On the web the time between
// two presents includes the wait for the browser's next animation frame, so only a missed 60 Hz frame counts.
#ifdef __EMSCRIPTEN__
constexpr double kHitchMs = 25.0;
#else
constexpr double kHitchMs = 1000.0 / 120.0;
#endif
GLuint g_queries[kQueries] = {};
bool g_queryPending[kQueries] = {};
int g_queryNext = 0;
bool g_queryOpen = false;
bool g_haveQueries = false;

uint32_t g_window = 0;  // frames per log line
struct Totals {
    uint64_t frames = 0;
    double wallMs = 0.0;
    double swapMs = 0.0;
    double gpuMs = 0.0;
    uint64_t gpuFrames = 0;
    double maxWallMs = 0.0;      // the longest frame
    uint64_t over4 = 0;          // frames longer than 4 ms, 8.33 ms (120 Hz) and 16.67 ms (60 Hz)
    uint64_t over8 = 0;
    uint64_t over16 = 0;
    uint64_t counters[kCounterCount] = {};
    void Add(const Totals& o) {
        if (o.maxWallMs > maxWallMs) maxWallMs = o.maxWallMs;
        over4 += o.over4;
        over8 += o.over8;
        over16 += o.over16;
        frames += o.frames;
        wallMs += o.wallMs;
        swapMs += o.swapMs;
        gpuMs += o.gpuMs;
        gpuFrames += o.gpuFrames;
        for (int i = 0; i < kCounterCount; ++i) counters[i] += o.counters[i];
    }
};
Totals g_windowTotals;
Totals g_allTotals;
double g_workMs[kWorkCount] = {};
uint32_t g_workCount[kWorkCount] = {};
double g_workTotalMs[kWorkCount] = {};
uint32_t g_workTotalCount[kWorkCount] = {};
Clock::time_point g_lastPresent;
Clock::time_point g_beforePresent;
bool g_havePresent = false;
uint64_t g_frame = 0;

void Line(const char* what, const Totals& t) {
    if (t.frames == 0) return;
    const double n = static_cast<double>(t.frames);
    const uint64_t* c = t.counters;
    DOTD_LOG("gfxstats %s: %llu frames, wall %.3f ms (max %.2f; over 4 / 8.3 / 16.7 ms: %llu / %llu / %llu), gpu %.3f ms, "
             "swap %.3f ms | per frame: draws %.1f (instances %.1f), "
             "programs %.1f, uniforms %.1f, ubo %.1f, texbinds %.1f, samplerparams %.1f, buffers %.1f (%.1f KB), "
             "targets %.1f, vaos %.1f",
             what, static_cast<unsigned long long>(t.frames), t.wallMs / n, t.maxWallMs,
             static_cast<unsigned long long>(t.over4), static_cast<unsigned long long>(t.over8),
             static_cast<unsigned long long>(t.over16), t.gpuFrames != 0 ? t.gpuMs / static_cast<double>(t.gpuFrames) : 0.0, t.swapMs / n, c[kDraws] / n,
             c[kInstances] / n, c[kPrograms] / n, c[kUniforms] / n, c[kUniformBlocks] / n, c[kTextureBinds] / n,
             c[kSamplerParams] / n, c[kBufferUploads] / n, c[kBufferBytes] / n / 1024.0, c[kTargetBinds] / n,
             c[kVaoBinds] / n);
}

void CollectQueries() {
    for (int i = 0; i < kQueries; ++i) {
        if (!g_queryPending[i]) continue;
        GLuint available = 0;
        glGetQueryObjectuiv_(g_queries[i], kQueryResultAvailable, &available);
        if (available == 0) continue;
        uint64_t ns = 0;
        glGetQueryObjectui64v_(g_queries[i], kQueryResult, &ns);
        g_windowTotals.gpuMs += static_cast<double>(ns) / 1e6;
        ++g_windowTotals.gpuFrames;
        g_queryPending[i] = false;
    }
}

void BeginQuery() {
    if (!g_haveQueries || g_queryOpen) return;
    if (g_queryPending[g_queryNext]) return;  // the ring is full: this frame is not measured
    glBeginQuery_(kTimeElapsed, g_queries[g_queryNext]);
    g_queryOpen = true;
}

// ---- RenderDoc's in-application API (renderdoc_app.h, RENDERDOC_API_1_1_2: a table of function pointers) ----
typedef int (*PFN_RenderDocGetApi)(int version, void** api);
typedef void (*PFN_RenderDocTriggerCapture)();
constexpr int kRenderDocApi112 = 10102;
constexpr int kRenderDocTriggerCaptureSlot = 15;  // GetAPIVersion 0, ... GetCapture 14, TriggerCapture 15
void** g_renderDoc = nullptr;
bool g_renderDocLooked = false;

void LogTotals();  // below
void LogWork();

}  // namespace

void Init(void* (*getProc)(const char* name)) {
    const char* stats = std::getenv("DOTD_GFX_STATS");
    g_window = stats != nullptr ? static_cast<uint32_t>(std::strtoul(stats, nullptr, 10)) : 0;
    g_enabled = g_window != 0;
    g_windowTotals = Totals();
    g_allTotals = Totals();
    g_havePresent = false;
    g_frame = 0;
    for (uint64_t& c : g_counters) c = 0;
    for (int i = 0; i < kWorkCount; ++i) {
        g_workTotalMs[i] = 0.0;
        g_workTotalCount[i] = 0;
    }
    g_haveQueries = false;
    if (!g_enabled) return;
    glGenQueries_ = reinterpret_cast<PFN_GenQueries>(getProc("glGenQueries"));
    glDeleteQueries_ = reinterpret_cast<PFN_DeleteQueries>(getProc("glDeleteQueries"));
    glBeginQuery_ = reinterpret_cast<PFN_BeginQuery>(getProc("glBeginQuery"));
    glEndQuery_ = reinterpret_cast<PFN_EndQuery>(getProc("glEndQuery"));
    glGetQueryObjectuiv_ = reinterpret_cast<PFN_GetQueryObjectuiv>(getProc("glGetQueryObjectuiv"));
    glGetQueryObjectui64v_ = reinterpret_cast<PFN_GetQueryObjectui64v>(getProc("glGetQueryObjectui64v"));
    g_haveQueries = glGenQueries_ != nullptr && glDeleteQueries_ != nullptr && glBeginQuery_ != nullptr &&
                    glEndQuery_ != nullptr && glGetQueryObjectuiv_ != nullptr && glGetQueryObjectui64v_ != nullptr;
    if (g_haveQueries) {
        glGenQueries_(kQueries, g_queries);
        for (bool& pending : g_queryPending) pending = false;
        g_queryNext = 0;
        g_queryOpen = false;
        BeginQuery();
    }
    static bool s_atExit = false;
    if (!s_atExit) {
        s_atExit = true;
        std::atexit(&LogTotals);
    }
    DOTD_LOG("gfxstats: on, a line every %u frames, GPU timer queries %s", g_window, g_haveQueries ? "yes" : "no");
}

namespace {
// The first-use work so far (cumulative; logged with every window line: the test runners leave through _Exit).
void LogWork() {
    DOTD_LOG("gfxstats work: shader variants %.1f ms (%u): translation %.1f ms, compiles %.1f ms (%u), links %.1f ms (%u); "
             "textures %.1f ms (%u); meshes %.1f ms (%u)",
             g_workTotalMs[kWorkShader], g_workTotalCount[kWorkShader], g_workTotalMs[kWorkShaderTranslate],
             g_workTotalMs[kWorkShaderCompile], g_workTotalCount[kWorkShaderCompile], g_workTotalMs[kWorkShaderLink],
             g_workTotalCount[kWorkShaderLink], g_workTotalMs[kWorkTexture], g_workTotalCount[kWorkTexture],
             g_workTotalMs[kWorkMesh], g_workTotalCount[kWorkMesh]);
}

// The run's totals (Shutdown, or the process exit when the device was never shut down: the test runners).
void LogTotals() {
    if (!g_enabled) return;
    Line("window", g_windowTotals);
    g_allTotals.Add(g_windowTotals);
    g_windowTotals = Totals();
    Line("total", g_allTotals);
    LogWork();
    g_enabled = false;
}
}  // namespace

void Shutdown() {
    if (!g_enabled) return;
    LogTotals();
    if (g_haveQueries) {
        if (g_queryOpen) glEndQuery_(kTimeElapsed);
        glDeleteQueries_(kQueries, g_queries);
    }
    g_queryOpen = false;
    g_haveQueries = false;
    g_enabled = false;
}

void BeforePresent() {
    if (!g_enabled) return;
    if (g_queryOpen) {
        glEndQuery_(kTimeElapsed);
        g_queryPending[g_queryNext] = true;
        g_queryNext = (g_queryNext + 1) % kQueries;
        g_queryOpen = false;
    }
    g_beforePresent = Clock::now();
}

void AfterPresent() {
    if (!g_enabled) return;
    const Clock::time_point now = Clock::now();
    if (g_havePresent) {
        const double wall = std::chrono::duration<double, std::milli>(now - g_lastPresent).count();
        g_windowTotals.wallMs += wall;
        if (wall > g_windowTotals.maxWallMs) g_windowTotals.maxWallMs = wall;
        if (wall > 4.0) ++g_windowTotals.over4;
        if (wall > 1000.0 / 120.0) ++g_windowTotals.over8;
        if (wall > 1000.0 / 60.0) ++g_windowTotals.over16;
        if (wall > kHitchMs) {
            DOTD_LOG("gfxstats hitch: frame %llu took %.2f ms: shader variants %.2f ms (%u), textures %.2f ms (%u), "
                     "meshes %.2f ms (%u), present %.2f ms",
                     static_cast<unsigned long long>(g_frame + 1), wall, g_workMs[kWorkShader], g_workCount[kWorkShader],
                     g_workMs[kWorkTexture], g_workCount[kWorkTexture], g_workMs[kWorkMesh], g_workCount[kWorkMesh],
                     std::chrono::duration<double, std::milli>(now - g_beforePresent).count());
        }
        g_windowTotals.swapMs += std::chrono::duration<double, std::milli>(now - g_beforePresent).count();
        ++g_windowTotals.frames;
        for (int i = 0; i < kCounterCount; ++i) g_windowTotals.counters[i] += g_counters[i];
    }
    for (uint64_t& c : g_counters) c = 0;
    for (int i = 0; i < kWorkCount; ++i) {
        g_workMs[i] = 0.0;
        g_workCount[i] = 0;
    }
    g_lastPresent = now;
    g_havePresent = true;
    ++g_frame;
    if (g_haveQueries) {
        CollectQueries();
        BeginQuery();
    }
    if (g_windowTotals.frames >= g_window) {
        char what[32];
        std::snprintf(what, sizeof what, "@%llu", static_cast<unsigned long long>(g_frame));
        Line(what, g_windowTotals);
        LogWork();
        g_allTotals.Add(g_windowTotals);
        g_windowTotals = Totals();
    }
}

Scope::Scope(Work work) : m_work(work) {
    if (g_enabled) m_start = Clock::now().time_since_epoch().count();
}

Scope::~Scope() {
    if (m_start == 0) return;
    const Clock::duration elapsed(Clock::now().time_since_epoch().count() - m_start);
    const double ms = std::chrono::duration<double, std::milli>(elapsed).count();
    g_workMs[m_work] += ms;
    ++g_workCount[m_work];
    g_workTotalMs[m_work] += ms;
    ++g_workTotalCount[m_work];
}

void CaptureNextFrame() {
#if defined(_WIN32)
    if (!g_renderDocLooked) {
        g_renderDocLooked = true;
        if (std::getenv("DOTD_RDOC_ON_SHOT") == nullptr) return;
        void* module = GetModuleHandleA("renderdoc.dll");
        if (module == nullptr) {
            DOTD_LOG("gfx: DOTD_RDOC_ON_SHOT: renderdoc.dll is not in the process");
            return;
        }
        const auto getApi = reinterpret_cast<PFN_RenderDocGetApi>(GetProcAddress(module, "RENDERDOC_GetAPI"));
        void* api = nullptr;
        if (getApi == nullptr || getApi(kRenderDocApi112, &api) != 1 || api == nullptr) {
            DOTD_LOG("gfx: DOTD_RDOC_ON_SHOT: RENDERDOC_GetAPI failed");
            return;
        }
        g_renderDoc = static_cast<void**>(api);
    }
    if (g_renderDoc == nullptr) return;
    reinterpret_cast<PFN_RenderDocTriggerCapture>(g_renderDoc[kRenderDocTriggerCaptureSlot])();
    DOTD_LOG("gfx: RenderDoc capture of the next frame requested");
#endif
}

}  // namespace dotd::gfx::perf
