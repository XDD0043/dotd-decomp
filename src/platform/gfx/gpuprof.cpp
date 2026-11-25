#include "platform/gfx/gpuprof.h"

#include <algorithm>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <string>
#include <vector>

#include "platform/gfx/gl.h"
#include "platform/gfx/perf.h"
#include "platform/log.h"

namespace dotd::gfx::gpuprof {

namespace {

using gl::glFinish;
using Clock = std::chrono::steady_clock;

// Segments: 0..22 a stage; 23..45 what follows stage s until the next mark (target switches, the scene colour copy,
// the 2D group's video, the present's blit after the last stage); 46 the frame from FrameStart to its first stage.
constexpr int kAfter = kStages;
constexpr int kBefore = 2 * kStages;
constexpr int kSegments = 2 * kStages + 1;
constexpr int kReportEvery = 8;  // measured frames per report

struct Segment {
    double ms = 0.0;      // mark to mark
    double waitMs = 0.0;  // of which inside the closing glFinish
    uint64_t draws = 0;
    uint32_t frames = 0;  // measured frames in which it ran
};

int g_every = 0;
int g_sinceMeasured = 0;
bool g_measuring = false;
uint32_t g_skip = 0;
uint32_t g_items[kStages] = {};
int g_skipItemsStage = -1;
uint32_t g_skipFrom = 0, g_skipTo = 0;
int g_sync = 0;
int g_described = -1;
int g_opaqueMode = 0;
std::vector<std::string> g_descriptions;  // the described stage's items in the last measured frame

int g_open = -1;
Clock::time_point g_segStart, g_frameStart;
uint64_t g_drawsAtStart = 0;
bool g_ranThisFrame[kSegments] = {};

Segment g_acc[kSegments];
std::map<std::string, uint32_t> g_classes[kStages];
uint32_t g_measured = 0;
double g_frameMs = 0.0, g_drainMs = 0.0, g_finishMs = 0.0;

double Ms(Clock::duration d) { return std::chrono::duration<double, std::milli>(d).count(); }

uint64_t Draws() { return perf::g_counters[perf::kDraws]; }

// Ends the open segment with a finish and opens `next` (-1: none).
void Mark(int next) {
    const Clock::time_point beforeFinish = Clock::now();
    glFinish();
    const Clock::time_point now = Clock::now();
    if (g_open >= 0) {
        Segment& s = g_acc[g_open];
        s.ms += Ms(now - g_segStart);
        s.waitMs += Ms(now - beforeFinish);
        s.draws += Draws() - g_drawsAtStart;
        if (!g_ranThisFrame[g_open]) {
            g_ranThisFrame[g_open] = true;
            ++s.frames;
        }
    }
    g_open = next;
    g_segStart = Clock::now();
    g_drawsAtStart = Draws();
}

std::string SegmentName(int segment) {
    char name[48];
    if (segment < kAfter) {
        std::snprintf(name, sizeof(name), "stage %02d", segment);
    } else if (segment < kBefore) {
        std::snprintf(name, sizeof(name), "after stage %02d", segment - kAfter);
    } else {
        std::snprintf(name, sizeof(name), "before the stages");
    }
    return name;
}

void Report() {
    const double n = static_cast<double>(g_measured);
    DOTD_LOG("gpuprof: %u measured frames (every %d): frame %.2f ms (marks to present), drain %.2f ms, finish cost "
             "%.3f ms, skip mask 0x%x",
             g_measured, g_every, g_frameMs / n, g_drainMs / n, g_finishMs / n, g_skip);
    std::vector<int> order;
    for (int i = 0; i < kSegments; ++i) {
        if (g_acc[i].frames != 0) order.push_back(i);
    }
    std::sort(order.begin(), order.end(), [](int a, int b) { return g_acc[a].ms > g_acc[b].ms; });
    for (int i : order) {
        const Segment& s = g_acc[i];
        if (s.ms / n < 0.05) continue;
        std::string classes;
        if (i < kAfter) {
            std::vector<std::pair<uint32_t, std::string>> list;
            for (const auto& c : g_classes[i]) list.emplace_back(c.second, c.first);
            std::sort(list.begin(), list.end(), [](const auto& a, const auto& b) { return a.first > b.first; });
            for (size_t k = 0; k < list.size() && k < 5; ++k) {
                char part[96];
                std::snprintf(part, sizeof(part), "%s%s %.1f", k ? ", " : " | ", list[k].second.c_str(), list[k].first / n);
                classes += part;
            }
        }
        DOTD_LOG("gpuprof seg %s: %.2f ms (gpu wait %.2f), draws %.1f%s", SegmentName(i).c_str(), s.ms / n,
                 s.waitMs / n, static_cast<double>(s.draws) / n, classes.c_str());
    }
    if (g_described >= 0) {
        for (size_t i = 0; i < g_descriptions.size(); ++i) {
            DOTD_LOG("gpuprof item stage %02d #%zu: %s", g_described, i, g_descriptions[i].c_str());
        }
    }
    for (Segment& s : g_acc) s = Segment();
    for (auto& c : g_classes) c.clear();
    g_measured = 0;
    g_frameMs = g_drainMs = g_finishMs = 0.0;
}

}  // namespace

void Init() {
    if (const char* every = std::getenv("DOTD_GPU_PROF")) SetMeasureEvery(std::atoi(every));
    if (const char* skip = std::getenv("DOTD_SKIP_STAGES")) {
        uint32_t mask = 0;
        for (const char* p = skip; *p != '\0';) {
            char* end = nullptr;
            const long stage = std::strtol(p, &end, 10);
            if (end == p) {
                ++p;
                continue;
            }
            if (stage >= 0 && stage < kStages) mask |= 1u << stage;
            p = end;
        }
        SetSkipMask(mask);
    }
    if (const char* opaque = std::getenv("DOTD_OPAQUE")) {
        SetOpaqueMode((std::strstr(opaque, "reverse") ? kOpaqueReverse : 0) | (std::strstr(opaque, "prepass") ? kOpaquePrepass : 0));
    }
}

void SetSkipItems(int stage, uint32_t from, uint32_t to) {
    g_skipItemsStage = from < to ? stage : -1;
    g_skipFrom = from;
    g_skipTo = to;
}

bool ItemSkipped(int stage, uint32_t index) { return stage == g_skipItemsStage && index >= g_skipFrom && index < g_skipTo; }

void SetStageSync(int sync) { g_sync = sync; }

void SetDescribedStage(int stage) { g_described = stage; }

void SetOpaqueMode(int mode) {
    if (mode != g_opaqueMode) DOTD_LOG("gpuprof: opaque queues%s%s", mode & kOpaqueReverse ? " near to far" : "",
                                       mode & kOpaquePrepass ? " with a depth pre-pass" : mode ? "" : " as the original");
    g_opaqueMode = mode;
}

int OpaqueMode() { return g_opaqueMode; }

bool Describing(int stage) { return g_measuring && stage >= 0 && stage == g_described; }

void NoteItemDescription(uint32_t index, const char* text) {
    if (g_descriptions.size() <= index) g_descriptions.resize(index + 1);
    g_descriptions[index] = text;
}

void SetMeasureEvery(int every) {
    g_every = every > 0 ? every : 0;
    g_sinceMeasured = 0;
    if (g_every == 0 && g_measured != 0) Report();
    if (g_every != 0) DOTD_LOG("gpuprof: every %d frames one measured frame", g_every);
}

void SetSkipMask(uint32_t mask) {
    if (mask != g_skip) DOTD_LOG("gpuprof: skip mask 0x%x", mask);
    g_skip = mask;
}

uint32_t SkipMask() { return g_skip; }

uint32_t StageItems(int stage) { return stage >= 0 && stage < kStages ? g_items[stage] : 0; }

bool Measuring() { return g_measuring; }

void FrameStart() {
    if (g_every == 0 || !gl::glFinish || ++g_sinceMeasured < g_every) return;
    g_sinceMeasured = 0;
    g_measuring = true;
    g_descriptions.clear();
    std::memset(g_ranThisFrame, 0, sizeof(g_ranThisFrame));
    const Clock::time_point start = Clock::now();
    glFinish();  // what the GPU still had of the previous frame
    const Clock::time_point drained = Clock::now();
    glFinish();  // nothing left: the finish's own cost
    const Clock::time_point calibrated = Clock::now();
    g_drainMs += Ms(drained - start);
    g_finishMs += Ms(calibrated - drained);
    g_frameStart = calibrated;
    g_open = kBefore;
    g_segStart = calibrated;
    g_drawsAtStart = Draws();
}

void BeginStage(int stage, uint32_t items) {
    if (stage < 0 || stage >= kStages) return;
    g_items[stage] = items;
    if (g_measuring) Mark(stage);
}

void EndStage(int stage) {
    if (g_measuring && stage >= 0 && stage < kStages) {
        Mark(kAfter + stage);
    } else if (g_sync == 1) {
        gl::glFlush();
    } else if (g_sync == 2) {
        glFinish();
    }
}

void NoteItem(int stage, const char* className) {
    if (g_measuring && stage >= 0 && stage < kStages) ++g_classes[stage][className != nullptr ? className : "?"];
}

void FrameEnd() {
    if (!g_measuring) return;
    Mark(-1);
    g_measuring = false;
    g_frameMs += Ms(Clock::now() - g_frameStart);
    if (++g_measured >= kReportEvery) Report();
}

}  // namespace dotd::gfx::gpuprof
