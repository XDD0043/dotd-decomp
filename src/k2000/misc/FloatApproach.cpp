// FloatApproach.cpp - reconstructed original translation unit 0x2436e8-0x243ff0 (GAME_TOC1, main_toc1), 6 functions, 5 live.
// Primary owner: FloatApproach (not a registered class)
// Other owners: FloatApproachAccel (2), Math (2)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x2436e8  FloatApproach_Step
//   [x] 0x243748  FloatApproach_StepAngle_maybe
//   [x] 0x243800  FloatApproachAccel_Step_maybe  (FloatApproachAccel_Step; its callers (bridges, CKHkLedge_Update, CKHkPushKillObject) are not ported yet)
//   [ ] 0x2438f8  FloatApproachAccel_StepAngle_maybe  [dead]
//   [x] 0x243a10  Math_ApproachWithAccelDecel
//   [x] 0x243c88  Math_ApproachAngleWithAccelDecel
#include "k2000/misc/FloatApproach.h"

#include <cmath>
#include <cstdint>
#include <cstring>

#include "crt/ppc_ops.h"

// 0x002436e8 FloatApproach_Step: approach[2] moves towards approach[0] by dt * approach[1] (fmuls, then
// fsubs / fadds) and stops on it; returns it. The end tests are blelr / bgelr (not greater / not less), so an unordered
// compare (a NaN target) keeps the stepped value: the hero's speed turn divides a zero angle by a zero dt in a frozen
// frame (the finisher pause) and the original keeps its turn speed.
float FloatApproach_Step(float dt, float* approach) {
    const float target = approach[0];
    float current = approach[2];
    if (current == target) return current;
    const float step = dt * approach[1];
    if (current < target) {
        current = current + step;
        approach[2] = current;
        if (!(current > target)) return current;  // blelr
    } else {
        current = current - step;
        approach[2] = current;
        if (!(current < target)) return current;  // bgelr
    }
    approach[2] = target;
    return target;
}

// 0x00243800 FloatApproachAccel_Step_maybe. The branches as the original's (fcmpu: beq / bne, bge / ble / bgt), so that an
// unordered compare goes the same way.
float FloatApproachAccel_Step(float dt, float* state) {
    const float target = state[0];
    float current = state[4];
    if (current == target) {  // beq
        float speed = state[2];
        if (!(speed > 0.0f)) return current;  // ble
        speed = speed - dt * state[3];
        state[2] = speed;
        if (!(speed < 0.0f)) return current;  // bge
        state[2] = 0.0f;
        return current;
    }
    float speed = state[2];
    const float top = state[1];
    if (!(speed == top)) {  // bne
        const float step = dt * state[3];
        if (!(speed < top)) {  // bge
            speed = speed - step;
            state[2] = speed;
            if (speed < top) {  // bge not taken
                speed = top;
                state[2] = top;
            }
        } else {
            speed = speed + step;
            state[2] = speed;
            if (speed > top) {  // ble not taken
                speed = top;
                state[2] = top;
            }
        }
    }
    const float move = dt * speed;
    if (target > current) {  // bgt
        current = move + current;
        state[4] = current;
        if (!(current > target)) return current;  // ble
    } else {
        current = current - move;
        state[4] = current;
        if (!(current < target)) return current;  // bge
    }
    state[4] = target;
    return target;
}

// 0x00243748 FloatApproach_StepAngle_maybe
void FloatApproach_StepAngle(float dt, float* approach) {
    constexpr float kTwoPi = 6.2831854820251465f;
    constexpr float kPi = 3.1415927410125732f;
    const float target = approach[0];
    const float current = approach[2];
    if (current == target) return;
    float difference = target - current;
    const float step = dt * approach[1];
    if (difference < 0.0f) difference = difference + kTwoPi;
    // The tests as the original branches (blt to the target), so that an unordered compare takes a step.
    if (difference <= kPi) {  // cror lt|eq
        if (!(difference < step)) {
            const float next = current + step;
            approach[2] = next;
            if (next >= kTwoPi) approach[2] = next - kTwoPi;  // cror gt|eq
            return;
        }
    } else if (!(kTwoPi - difference < step)) {
        const float next = current - step;
        approach[2] = next;
        if (next < 0.0f) approach[2] = next + kTwoPi;  // bgelr returns when not less
        return;
    }
    approach[2] = approach[0];
}

namespace {
// The absolute value as the original takes it: the float stored, its sign bit cleared in memory, reloaded.
float ClearSignBit(float x) {
    uint32_t bits;
    std::memcpy(&bits, &x, 4);
    bits &= 0x7fffffffu;
    std::memcpy(&x, &bits, 4);
    return x;
}

// The truncation toward zero through the float's bits (rldicl / subfic / sraw / nor / and): shift = 127 - exponent;
// below 1 (shift >= 1) every bit is cleared (+0, the sign too); otherwise the fraction bits 0x7fffff >> -shift are
// cleared (none from shift <= -31 on).
float TruncateByExponentMask(float x) {
    uint32_t bits;
    std::memcpy(&bits, &x, 4);
    const int32_t shift = 127 - static_cast<int32_t>((bits >> 23) & 0xffu);
    int32_t fraction = 0;
    if (shift > -31) fraction = ppc::sraw(0x007fffff, static_cast<uint32_t>(-shift));
    const int32_t below = ~ppc::sraw(shift - 1, 31);
    bits &= ~(static_cast<uint32_t>(fraction) | static_cast<uint32_t>(below));
    std::memcpy(&x, &bits, 4);
    return x;
}
}  // namespace

// 0x00243a10 Math_ApproachWithAccelDecel: r3 = state, f1 = dt. state = {accel, decel, top speed, current, speed,
// target, speed bonus} (+0x00..+0x18). Returns state[3] at once when it is on the target with no speed and no
// bonus. The speed cap is the top speed, or, inside the braking distance (1 / decel) * (top * (top * 0.5)),
// sqrtf(|diff| * 2 decel) + decel * 0.01; towards a larger target the limit is cap + bonus, at most top; towards a
// smaller one bonus - cap, at least -top. The speed accelerates by `accel` towards the limit (fmadds), or by `decel`
// when it comes back from the other sign (fmadds), or decelerates by `decel` (fmuls then fsubs), clamped to the
// limit; current += dt * speed (fmadds), clamped to the target.
float Math_ApproachWithAccelDecel(float dt, float* state) {
    const float difference = ClearSignBit(state[3] - state[5]);
    if (difference == 0.0f && state[4] == 0.0f && state[6] == 0.0f) return state[3];
    float decel = state[1];
    float top = state[2];
    float cap = top;
    if (1.0f / decel * (top * (top * 0.5f)) > difference) {  // TOC1 -0x20c, -0x208
        const float root = std::sqrt(difference * (decel + decel));  // Math_Sqrtf 0x10690 (fsqrts)
        decel = state[1];
        cap = ppc::fmadds(decel, 0.00999999977648258f, root);  // TOC1 -0x204
        top = state[2];
    }
    const float target = state[5];
    const float current = state[3];
    float speed = state[4];
    if (!(target < current)) {
        float limit = cap + state[6];
        if (!(limit < top)) limit = top;
        if (speed < 0.0f) {
            speed = ppc::fmadds(dt, decel, speed);
            if (!(limit > speed)) speed = limit;
        } else if (!(limit < speed)) {
            speed = ppc::fmadds(dt, state[0], speed);
            if (!(limit > speed)) speed = limit;
        } else {
            speed = speed - dt * decel;
            if (!(limit > speed)) limit = speed;
            speed = limit;
        }
        state[4] = speed;
        float next = ppc::fmadds(dt, speed, current);
        if (!(next < target)) next = target;
        state[3] = next;
        return next;
    }
    float limit = -top;
    const float bonus = state[6] - cap;
    if (!(bonus < limit)) limit = bonus;
    if (speed > 0.0f) {
        speed = speed - dt * decel;
        if (!(limit > speed)) limit = speed;
        speed = limit;
    } else if (limit > speed) {
        speed = ppc::fmadds(dt, decel, speed);
        if (!(limit > speed)) speed = limit;
    } else {
        speed = speed - dt * state[0];
        if (!(limit > speed)) limit = speed;
        speed = limit;
    }
    state[4] = speed;
    float next = target;
    const float moved = ppc::fmadds(dt, speed, current);
    if (!(moved < target)) next = moved;
    state[3] = next;
    return next;
}

// 0x00243c88 Math_ApproachAngleWithAccelDecel: the same state for an angle in radians. The current angle and the
// target are wrapped into [0, 2 pi) (x / 2 pi minus its truncation, times 2 pi, plus 2 pi when negative); the way
// round is the target's direction from the current angle ((target - current) mod 2 pi above pi: downwards), the
// distance the shorter one (|diff|, |diff - 2 pi| above pi). The braking distance is written as
// (1 / decel) * ((1 / decel) * top^2 * (decel * -0.5)) + (1 / decel) * top^2 (fmadds). The step dt * speed (fmuls)
// lands on the target when it covers the distance; the result (not wrapped again) is stored in state[3] and
// returned. On the target with no speed and no bonus it returns the wrapped current angle without storing it.
float Math_ApproachAngleWithAccelDecel(float dt, float* state) {
    constexpr float kTwoPi = 6.2831854820251465f;  // TOC1 -0x218
    constexpr float kPi = 3.1415927410125732f;     // TOC1 -0x214
    const float currentTurns = state[3] / kTwoPi;
    const float targetTurns = state[5] / kTwoPi;
    float current = (currentTurns - TruncateByExponentMask(currentTurns)) * kTwoPi;
    float target = (targetTurns - TruncateByExponentMask(targetTurns)) * kTwoPi;
    if (current < 0.0f) current = current + kTwoPi;
    if (target < 0.0f) target = target + kTwoPi;
    const float difference = target - current;
    float forward = difference;
    if (difference < 0.0f) forward = difference + kTwoPi;
    float distance = ClearSignBit(difference);
    if (distance > kPi) distance = ClearSignBit(distance - kTwoPi);
    if (distance == 0.0f && state[4] == 0.0f && state[6] == 0.0f) return current;
    float decel = state[1];
    float top = state[2];
    const float inverse = 1.0f / decel;  // TOC1 -0x20c
    const float topSquared = inverse * (top * top);
    const float braking = ppc::fmadds(inverse, topSquared * (decel * -0.5f), topSquared);  // TOC1 -0x200
    float cap = top;
    if (braking > distance) {
        const float root = std::sqrt(distance * (decel + decel));  // Math_Sqrtf 0x10690 (fsqrts)
        decel = state[1];
        cap = ppc::fmadds(decel, 0.00999999977648258f, root);  // TOC1 -0x204
        top = state[2];
    }
    float speed = state[4];
    if (!(forward > kPi)) {
        float limit = cap + state[6];
        if (!(limit < top)) limit = top;
        if (speed < 0.0f) {
            speed = ppc::fmadds(dt, decel, speed);
            if (!(limit > speed)) speed = limit;
        } else if (!(limit < speed)) {
            speed = ppc::fmadds(dt, state[0], speed);
            if (!(limit > speed)) speed = limit;
        } else {
            speed = speed - dt * decel;
            if (!(limit > speed)) limit = speed;
            speed = limit;
        }
    } else {
        float limit = -top;
        const float bonus = state[6] - cap;
        if (!(bonus < limit)) limit = bonus;
        if (speed > 0.0f) {
            speed = speed - dt * decel;
            if (!(limit > speed)) limit = speed;
            speed = limit;
        } else if (limit > speed) {
            speed = ppc::fmadds(dt, decel, speed);
            if (!(limit > speed)) speed = limit;
        } else {
            speed = speed - dt * state[0];
            if (!(limit > speed)) limit = speed;
            speed = limit;
        }
    }
    state[4] = speed;
    const float step = dt * speed;
    const float stepLength = ClearSignBit(step);
    const float next = (distance < stepLength || distance == stepLength) ? target : current + step;
    state[3] = next;
    return next;
}
