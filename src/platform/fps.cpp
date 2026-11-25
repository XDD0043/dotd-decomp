#include "platform/fps.h"

#include <cmath>

namespace dotd::fps {

namespace {
constexpr double kTickRate = 60.0;  // the PS3's frame rate
constexpr double kMaxFrames = 6.0;  // IKTime clamps dt to 0.1 s = 6 frames at 60 Hz
bool g_unlocked = false;
double g_phase = 0.0;  // the part of a 60 Hz frame carried to the next displayed frame
int32_t g_ticks = 1;
uint32_t g_tickCount = 0;
float g_scale = 1.0f;
float g_tickDelta[3] = {0.0f, 0.0f, 0.0f};  // the clock's deltas since the last displayed frame that ended a tick
int32_t g_subStep = 0;
}  // namespace

void Configure(bool unlocked) {
    g_unlocked = unlocked;
    g_phase = 0.0;
    g_ticks = 1;
    g_tickCount = 0;
    g_scale = 1.0f;
    g_tickDelta[0] = g_tickDelta[1] = g_tickDelta[2] = 0.0f;
}

bool Unlocked() { return g_unlocked; }

void SetUnlocked(bool unlocked) {
    if (g_unlocked == unlocked) return;
    g_unlocked = unlocked;
    g_phase = 0.0;
    g_ticks = 1;
    g_scale = 1.0f;
    g_tickDelta[0] = g_tickDelta[1] = g_tickDelta[2] = 0.0f;
}

void OnClockUpdate(const float delta[3]) {
    if (!g_unlocked) return;
    if (g_ticks > 0) g_tickDelta[0] = g_tickDelta[1] = g_tickDelta[2] = 0.0f;  // the last frame used them up
    for (int i = 0; i < 3; ++i) g_tickDelta[i] += delta[i];
    double frames = static_cast<double>(delta[2]) * kTickRate;
    if (!(frames > 0.0)) frames = 0.0;  // also NaN
    if (frames > kMaxFrames) frames = kMaxFrames;
    g_scale = static_cast<float>(frames);
    g_phase += frames;
    // A tiny epsilon, so that frames of 16.6666 ms (a 60 fps run with the calculation on) do not miss a tick by rounding.
    const double whole = std::floor(g_phase + 1e-6);
    g_ticks = static_cast<int32_t>(whole);
    g_phase -= whole;
    if (g_phase < 0.0) g_phase = 0.0;
    g_tickCount += static_cast<uint32_t>(g_ticks);
}

int32_t Ticks() { return g_unlocked && g_subStep == 0 ? g_ticks : 1; }

uint32_t TickCount() { return g_tickCount; }

float Scale() { return g_unlocked && g_subStep == 0 ? g_scale : 1.0f; }

float Dt60(float dt) {
    if (!g_unlocked || g_subStep != 0) return dt;
    if (!(g_scale > 0.0f)) return 0.0f;
    return dt / g_scale;
}

int64_t TruncSteps(float rate, float dt) {
    const float product = rate * Dt60(dt);
    if (!(product == product)) return 0;  // NaN
    return static_cast<int64_t>(static_cast<double>(product)) * Ticks();
}

float TickDelta(int32_t mode) { return mode >= 0 && mode < 3 ? g_tickDelta[mode] : 0.0f; }

SubStep::SubStep() { ++g_subStep; }
SubStep::~SubStep() { --g_subStep; }

}  // namespace dotd::fps
