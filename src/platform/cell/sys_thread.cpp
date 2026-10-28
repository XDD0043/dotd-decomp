#include "platform/cell/sys_thread.h"

#include <SDL3/SDL_timer.h>

#include <atomic>
#include <chrono>
#include <map>
#include <memory>
#include <mutex>
#include <string>
#include <thread>

#include "platform/cell/cell_errors.h"
#include "platform/log.h"

namespace {

struct ThreadRecord {
    std::thread thread;
    std::string name;
    int32_t prio = 0;
    uint64_t exitValue = 0;
};

std::mutex g_mutex;
std::map<sys_ppu_thread_t, std::unique_ptr<ThreadRecord>> g_threads;
std::atomic<sys_ppu_thread_t> g_nextId(0x01000001);  // PS3 PPU thread ids look like this
thread_local sys_ppu_thread_t t_currentId = 0;
thread_local uint64_t t_exitValue = 0;

sys_ppu_thread_t MainThreadId() {
    static const sys_ppu_thread_t id = 0x01000000;  // the process's main thread
    return id;
}

}  // namespace

int32_t sys_ppu_thread_create(sys_ppu_thread_t* thread_id, void (*entry)(uint64_t), uint64_t arg, int32_t prio, size_t,
                              uint64_t, const char* threadname) {
    if (!thread_id || !entry) return CellError(CELL_EFAULT);
    const sys_ppu_thread_t id = g_nextId.fetch_add(1);
    ThreadRecord* rec = new ThreadRecord();
    rec->name = threadname ? threadname : "";
    rec->prio = prio;
    {
        std::lock_guard<std::mutex> lock(g_mutex);
        g_threads[id].reset(rec);
    }
    // Stack size is not adjustable through std::thread; the host default (1 MB+) exceeds the PS3's 64 KB.
    rec->thread = std::thread([id, entry, arg, rec]() {
        t_currentId = id;
        entry(arg);
        rec->exitValue = t_exitValue;
    });
    *thread_id = id;
    DOTD_LOG("thread: created '%s' (prio %d)", rec->name.c_str(), prio);
    return CELL_OK;
}

int32_t sys_ppu_thread_get_id(sys_ppu_thread_t* thread_id) {
    if (!thread_id) return CellError(CELL_EFAULT);
    *thread_id = t_currentId ? t_currentId : MainThreadId();
    return CELL_OK;
}

void sys_ppu_thread_exit(uint64_t val) { t_exitValue = val; }

int32_t sys_ppu_thread_join(sys_ppu_thread_t thread_id, uint64_t* vptr) {
    ThreadRecord* rec = nullptr;
    {
        std::lock_guard<std::mutex> lock(g_mutex);
        auto it = g_threads.find(thread_id);
        if (it == g_threads.end()) return CellError(CELL_ESRCH);
        rec = it->second.get();
    }
    if (rec->thread.get_id() == std::this_thread::get_id()) return CellError(CELL_EDEADLK);
    if (rec->thread.joinable()) rec->thread.join();
    if (vptr) *vptr = rec->exitValue;
    std::lock_guard<std::mutex> lock(g_mutex);
    g_threads.erase(thread_id);
    return CELL_OK;
}

void sys_ppu_thread_yield() { std::this_thread::yield(); }

int32_t sys_ppu_thread_set_priority(sys_ppu_thread_t thread_id, int32_t prio) {
    std::lock_guard<std::mutex> lock(g_mutex);
    auto it = g_threads.find(thread_id);
    if (it != g_threads.end()) it->second->prio = prio;
    return CELL_OK;
}

int32_t sys_ppu_thread_get_priority(sys_ppu_thread_t thread_id, int32_t* prio) {
    if (!prio) return CellError(CELL_EFAULT);
    std::lock_guard<std::mutex> lock(g_mutex);
    auto it = g_threads.find(thread_id);
    *prio = it != g_threads.end() ? it->second->prio : 1001;  // the main thread runs at 1001
    return CELL_OK;
}

namespace dotd::platform {
namespace {
std::atomic<bool> g_deterministicRequests(false);
}
void SetDeterministicRequests(bool on) { g_deterministicRequests = on; }
bool DeterministicRequests() { return g_deterministicRequests; }
}  // namespace dotd::platform

int32_t sys_timer_usleep(uint64_t sleep_time_us) {
    // std::this_thread::sleep_for rounds up to the Windows timer tick (15.6 ms by default), which
    // turned the game's 5 ms loading-frame sleep into ~15 ms. SDL_DelayNS uses a high-resolution
    // waitable timer where the OS has one.
    SDL_DelayNS(sleep_time_us * 1000u);
    return CELL_OK;
}
