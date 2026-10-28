// HeroTimedImpulse.h - the timed impulse records of the hero (step 6 FLY). The original keeps several records of the
// same layout in CKHkS08Hero and inlines their two operations wherever they are used: +0x13f4 (the flight thrust),
// +0x1414 (the +0x13d8 force), +0x145c (the flight dash), +0x156c (the take-off push), +0x1d3c (the take-off impulse).
// Layout (0x20 bytes): +0x00 magnitude, +0x04 duration, +0x08 active (byte), +0x0c direction, +0x18 time left, +0x1c the
// last step. The hero's members of a record are typed by their old placeholders (some are words): the files copy them
// into this struct and back, which keeps every bit.
#pragma once
#include <cstdint>

#include "crt/ppc_ops.h"
#include "k2000/math/CMatrix34.h"

struct HeroTimedImpulse {
    float m_magnitude;  // +0x00
    float m_duration;   // +0x04
    uint8_t m_active;   // +0x08
    CVector3 m_dir;     // +0x0c
    float m_left;       // +0x18
    float m_last;       // +0x1c

    // The step every user inlines: an active record whose time ran out (below 0) is cleared (direction to `zero`, the
    // times 0); otherwise its time runs down by `dt`, which is kept as the last step.
    void Step(float dt, const CVector3& zero) {
        if (m_active == 0) return;
        if (m_left < 0.0f) {
            m_dir = zero;
            m_active = 0;
            m_last = 0.0f;
            m_left = 0.0f;
            return;
        }
        m_left = m_left - dt;
        m_last = dt;
    }
    // The evaluation: `base` plus the magnitude along the direction while the record is active and stepped; on the step
    // its time ran out, the magnitude is scaled by the part of the step that was left ((last + left) / last).
    CVector3 Evaluate(const CVector3& base) const {
        if (m_active == 0 || m_last == 0.0f) return base;
        float scale = m_magnitude;
        if (!(m_left >= 0.0f)) scale = ((m_last + m_left) / m_last) * m_magnitude;
        return CVector3{ppc::fmadds(scale, m_dir.x, base.x), ppc::fmadds(scale, m_dir.y, base.y),
                        ppc::fmadds(scale, m_dir.z, base.z)};
    }
    // Start: the direction, the time left = the duration, the last step 0, active.
    void Start(const CVector3& dir) {
        m_dir = dir;
        m_left = m_duration;
        m_last = 0.0f;
        m_active = 1;
    }
};
