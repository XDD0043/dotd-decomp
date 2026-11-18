// FloatApproach.h - a float approaching a target at a speed: {target, speed, current} (Ghidra
// FloatApproach; the menus' animation ramps and the game manager's interface video fade use it).
// Original unit: FloatApproach.cpp (0x2436e8-0x243ff0).
#pragma once

// 0x002436e8 FloatApproach_Step
float FloatApproach_Step(float dt, float* approach);
// 0x00243748 FloatApproach_StepAngle_maybe: the same for an angle in radians (approach[2] current, [0] target, [1] speed):
// the way round that is shorter, the angle kept in [0, 2 pi); on the target when the step reaches it.
void FloatApproach_StepAngle(float dt, float* approach);
// 0x00243a10 Math_ApproachWithAccelDecel and 0x00243c88 Math_ApproachAngleWithAccelDecel (step 5, the shared
// helpers; r3 = state, f1 = dt): state[3] (+0x0c) approaches state[5] (+0x14) with the speed state[4] (+0x10),
// accelerating by state[0] and decelerating by state[1] (also inside the braking distance top^2 / (2 decel), where the
// cap becomes sqrtf(2 decel |diff|) + 0.01 decel) up to the top speed state[2], the speed limit raised by the bonus
// state[6] (+0x18); returns the new state[3]. The angle form works in radians on the wrapped angles (the shorter way;
// state[3] gets the wrapped current + step, not wrapped again, or the wrapped target) and returns the wrapped current angle without
// storing it when there is nothing to do.
float Math_ApproachWithAccelDecel(float dt, float* state);
// 0x00243800 FloatApproachAccel_Step_maybe: state {target, top speed, speed, acceleration, current}: on the target the
// speed decays by dt * acceleration down to 0; otherwise the speed moves towards the top speed by dt * acceleration
// (stopping on it), then current moves towards the target by dt * speed (stopping on it). Returns current. Callers: the
// bridges (CKHkBridgeBase State1 / State7), CKHkLedge_Update, CKHkPushKillObject_UpdateAxisPosition_maybe (not ported).
float FloatApproachAccel_Step(float dt, float* state);
float Math_ApproachAngleWithAccelDecel(float dt, float* state);
