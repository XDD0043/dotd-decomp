// freecam.h - the debug free-fly camera (C2.4 step 5; new platform code, off by default).
//
// While it is on, the world cameras (RwDevice's registered main and far cameras) are drawn from its pose instead of their
// frame's; the game's own camera state is untouched, so the logic runs as before. F1 toggles it (the pose starts at the
// game camera's), WASD move (Q / E down / up, Shift fast, Ctrl slow, the mouse wheel changes the speed), the mouse looks
// around while the right button is held. The keyboard's WASD no longer feed the pad's left stick while it is on.
// DOTD_FREECAM=x,y,z,yaw,pitch (degrees; yaw 0 looks along +z, pitch up positive) turns it on at start-up with that pose.
#pragma once

namespace dotd::platform::freecam {

bool Enabled();
void SetEnabled(bool enabled);
// The pose in RenderWare world space (left-handed, y up). SetPose also marks the pose as initialised.
void SetPose(const float position[3], float yawDegrees, float pitchDegrees);
bool HasPose();  // false until a pose was set (the first enable takes the game camera's)
void GetPose(float position[3], float* yawDegrees, float* pitchDegrees);
// The camera's unit axes (RW: x to the left of the screen, y up, z forward).
void GetAxes(float right[3], float up[3], float at[3]);

// Platform hooks (app.cpp): the event pump feeds events, the frame end integrates the movement.
void OnKey(int scancode, bool down);
void OnMouseMotion(float dx, float dy, bool rightButton);
void OnMouseWheel(float dy);
void Update(float seconds);

}  // namespace dotd::platform::freecam
