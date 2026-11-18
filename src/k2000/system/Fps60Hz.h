// Fps60Hz.h - --fps N (platform/fps.h; not in the original): runs a piece of the frame as whole 60 Hz updates.
//
// Some systems move through chains of states one update per link (the cinematic scenes' blocs and doors, the sekens
// lines, the sound streams' state machines), so one update per displayed frame above 60 fps runs their chains faster
// (the LVL010 opening scene took 0.15 s less at 144 fps). RunOn60HzFrames calls `update` once per 60 Hz frame that
// this displayed frame ended (none, one, or a few), each time with the frame clock showing that 60 Hz frame: the clock's
// deltas since the last one shared out, its times stepped to the 60 Hz frame's end; the clock is restored afterwards.
// Inside, dotd::fps answers as at 60 fps (fps::SubStep). Only called while dotd::fps::Unlocked().
#pragma once
#include <cstdint>

#include "k2000/system/IKTime.h"
#include "platform/fps.h"

template <typename Update>
void RunOn60HzFrames(IKTime* clock, Update&& update) {
    const int32_t ticks = dotd::fps::Ticks();
    if (ticks <= 0) return;
    float savedCurrent[IKTime::NB_TIME_MODE], savedLast[IKTime::NB_TIME_MODE], savedDelta[IKTime::NB_TIME_MODE];
    float step[IKTime::NB_TIME_MODE];
    for (int32_t m = 0; m < IKTime::NB_TIME_MODE; ++m) {
        savedCurrent[m] = clock->m_afCurrentTime[m];
        savedLast[m] = clock->m_afLastTime[m];
        savedDelta[m] = clock->m_afDeltaTime[m];
        step[m] = dotd::fps::TickDelta(m) / static_cast<float>(ticks);
    }
    for (int32_t i = 0; i < ticks; ++i) {
        for (int32_t m = 0; m < IKTime::NB_TIME_MODE; ++m) {
            const float end = savedCurrent[m] - step[m] * static_cast<float>(ticks - 1 - i);
            clock->m_afCurrentTime[m] = end;
            clock->m_afLastTime[m] = end - step[m];
            clock->m_afDeltaTime[m] = step[m];
        }
        const dotd::fps::SubStep subStep;
        update();
    }
    for (int32_t m = 0; m < IKTime::NB_TIME_MODE; ++m) {
        clock->m_afCurrentTime[m] = savedCurrent[m];
        clock->m_afLastTime[m] = savedLast[m];
        clock->m_afDeltaTime[m] = savedDelta[m];
    }
}
