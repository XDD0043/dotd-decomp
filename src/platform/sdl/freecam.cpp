// freecam.cpp - see freecam.h.
#include "platform/sdl/freecam.h"

#include <SDL3/SDL.h>

#include <cmath>
#include <cstdio>
#include <cstdlib>

namespace dotd::platform::freecam {
namespace {
bool g_enabled = false;
bool g_hasPose = false;
bool g_envRead = false;
float g_position[3] = {0, 0, 0};
float g_yaw = 0.0f;    // radians, 0 looks along +z
float g_pitch = 0.0f;  // radians, positive looks up
float g_speed = 20.0f;  // world units per second

void ReadEnvironment() {
    if (g_envRead) return;
    g_envRead = true;
    const char* text = std::getenv("DOTD_FREECAM");
    if (text == nullptr) return;
    float v[5] = {0, 0, 0, 0, 0};
    if (std::sscanf(text, "%f,%f,%f,%f,%f", &v[0], &v[1], &v[2], &v[3], &v[4]) >= 3) {
        SetPose(v, v[3], v[4]);
        g_enabled = true;
    }
}
}  // namespace

bool Enabled() {
    ReadEnvironment();
    return g_enabled;
}

void SetEnabled(bool enabled) {
    ReadEnvironment();
    g_enabled = enabled;
}

void SetPose(const float position[3], float yawDegrees, float pitchDegrees) {
    for (int i = 0; i < 3; ++i) g_position[i] = position[i];
    g_yaw = yawDegrees * 0.0174532925f;
    g_pitch = pitchDegrees * 0.0174532925f;
    g_hasPose = true;
}

bool HasPose() { return g_hasPose; }

void GetPose(float position[3], float* yawDegrees, float* pitchDegrees) {
    for (int i = 0; i < 3; ++i) position[i] = g_position[i];
    *yawDegrees = g_yaw * 57.2957795f;
    *pitchDegrees = g_pitch * 57.2957795f;
}

void GetAxes(float right[3], float up[3], float at[3]) {
    const float cp = std::cos(g_pitch), sp = std::sin(g_pitch);
    const float sy = std::sin(g_yaw), cy = std::cos(g_yaw);
    at[0] = cp * sy;
    at[1] = sp;
    at[2] = cp * cy;
    // RW is left-handed: right = up x at points to the left of the screen.
    right[0] = cy;
    right[1] = 0.0f;
    right[2] = -sy;
    up[0] = at[1] * right[2] - at[2] * right[1];
    up[1] = at[2] * right[0] - at[0] * right[2];
    up[2] = at[0] * right[1] - at[1] * right[0];
}

void OnKey(int scancode, bool down) {
    if (down && scancode == SDL_SCANCODE_F1) SetEnabled(!Enabled());
}

void OnMouseMotion(float dx, float dy, bool rightButton) {
    if (!Enabled() || !rightButton) return;
    g_yaw += dx * 0.0035f;
    g_pitch -= dy * 0.0035f;
    const float limit = 1.553f;  // just under 89 degrees
    if (g_pitch > limit) g_pitch = limit;
    if (g_pitch < -limit) g_pitch = -limit;
}

void OnMouseWheel(float dy) {
    if (!Enabled()) return;
    g_speed *= std::pow(1.25f, dy);
    if (g_speed < 0.5f) g_speed = 0.5f;
    if (g_speed > 20000.0f) g_speed = 20000.0f;
}

void Update(float seconds) {
    if (!Enabled()) return;
    int count = 0;
    const bool* k = SDL_GetKeyboardState(&count);
    if (k == nullptr) return;
    float speed = g_speed;
    if (k[SDL_SCANCODE_LSHIFT] || k[SDL_SCANCODE_RSHIFT]) speed *= 5.0f;
    if (k[SDL_SCANCODE_LCTRL] || k[SDL_SCANCODE_RCTRL]) speed *= 0.2f;
    float right[3], up[3], at[3];
    GetAxes(right, up, at);
    float move[3] = {0, 0, 0};
    auto add = [&](const float* axis, float s) {
        for (int i = 0; i < 3; ++i) move[i] += axis[i] * s;
    };
    if (k[SDL_SCANCODE_W]) add(at, 1.0f);
    if (k[SDL_SCANCODE_S]) add(at, -1.0f);
    if (k[SDL_SCANCODE_A]) add(right, 1.0f);  // right points to the left of the screen
    if (k[SDL_SCANCODE_D]) add(right, -1.0f);
    if (k[SDL_SCANCODE_E]) move[1] += 1.0f;
    if (k[SDL_SCANCODE_Q]) move[1] -= 1.0f;
    for (int i = 0; i < 3; ++i) g_position[i] += move[i] * speed * seconds;
}

}  // namespace dotd::platform::freecam
