// sys_thread.h - PPU threads and timer sleep as the game uses them.
// Priorities are recorded only. sys_ppu_thread_exit records the exit value; the game's only callers
// (KThread_NativeEntry_maybe 0x591b0 and the KHostFS fatal-error path) return right after it.
#pragma once
#include <cstddef>
#include <cstdint>

typedef uint64_t sys_ppu_thread_t;

int32_t sys_ppu_thread_create(sys_ppu_thread_t* thread_id, void (*entry)(uint64_t), uint64_t arg, int32_t prio,
                              size_t stacksize, uint64_t flags, const char* threadname);
int32_t sys_ppu_thread_get_id(sys_ppu_thread_t* thread_id);
void sys_ppu_thread_exit(uint64_t val);
int32_t sys_ppu_thread_join(sys_ppu_thread_t thread_id, uint64_t* vptr);
void sys_ppu_thread_yield();
int32_t sys_ppu_thread_set_priority(sys_ppu_thread_t thread_id, int32_t prio);
int32_t sys_ppu_thread_get_priority(sys_ppu_thread_t thread_id, int32_t* prio);
int32_t sys_timer_usleep(uint64_t sleep_time_us);

namespace dotd::platform {
// Reproducible runs (tests, replays; off by default, new platform code, not in the original): a poll of an
// asynchronous request (KRequest_IsFinished 0x57978) that is queued or running waits until the worker is done, so
// a load takes the same number of game frames in every run. Without it the frame a load is seen finished depends on
// the worker thread's speed, which shifts every later frame's absolute time and with it the float frame dt
// (IKTime_Update 0x53fb0 subtracts two float absolute times).
void SetDeterministicRequests(bool on);
bool DeterministicRequests();
}  // namespace dotd::platform
