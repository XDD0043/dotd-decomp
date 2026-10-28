#include "platform/cell/sys_sync.h"

#include <chrono>
#include <condition_variable>
#include <memory>
#include <mutex>
#include <vector>

#include "platform/cell/cell_errors.h"

namespace {

// Recursive host mutex with a timed lock. LV2 lwmutexes can be non-recursive; relocking one from the
// owning thread is a game bug on the PS3 (EDEADLK) and is not reproduced here.
struct HostMutex {
    std::recursive_timed_mutex m;
};

struct HostSemaphore {
    std::mutex m;
    std::condition_variable cv;
    int32_t count = 0;
    int32_t max = 1;
};

std::mutex g_tableMutex;
std::vector<std::unique_ptr<HostMutex>> g_mutexes;          // id = index + 1
std::vector<std::unique_ptr<HostSemaphore>> g_semaphores;   // id = index + 1

HostMutex* FindMutex(const sys_lwmutex_t* lw) {
    std::lock_guard<std::mutex> lock(g_tableMutex);
    if (!lw || lw->handle == 0 || lw->handle > g_mutexes.size()) return nullptr;
    return g_mutexes[lw->handle - 1].get();
}

HostSemaphore* FindSemaphore(sys_semaphore_t id) {
    std::lock_guard<std::mutex> lock(g_tableMutex);
    if (id == 0 || id > g_semaphores.size()) return nullptr;
    return g_semaphores[id - 1].get();
}

}  // namespace

int32_t sys_lwmutex_create(sys_lwmutex_t* lw, const sys_lwmutex_attribute_t* attr) {
    if (!lw) return CellError(CELL_EFAULT);
    std::lock_guard<std::mutex> lock(g_tableMutex);
    g_mutexes.push_back(std::unique_ptr<HostMutex>(new HostMutex()));
    lw->handle = static_cast<uint32_t>(g_mutexes.size());
    lw->pad0 = 0;
    lw->attribute = attr ? (attr->protocol | attr->recursive) : 0;
    lw->recursive_count = 0;
    lw->sleep_queue = 0;
    lw->pad1 = 0;
    return CELL_OK;
}

int32_t sys_lwmutex_destroy(sys_lwmutex_t* lw) {
    std::lock_guard<std::mutex> lock(g_tableMutex);
    if (!lw || lw->handle == 0 || lw->handle > g_mutexes.size() || !g_mutexes[lw->handle - 1]) return CellError(CELL_ESRCH);
    g_mutexes[lw->handle - 1].reset();
    lw->handle = 0;
    return CELL_OK;
}

int32_t sys_lwmutex_lock(sys_lwmutex_t* lw, uint64_t timeout_us) {
    HostMutex* m = FindMutex(lw);
    if (!m) return CellError(CELL_ESRCH);
    if (timeout_us == 0) {
        m->m.lock();
    } else if (!m->m.try_lock_for(std::chrono::microseconds(timeout_us))) {
        return CellError(CELL_ETIMEDOUT);
    }
    lw->recursive_count++;
    return CELL_OK;
}

int32_t sys_lwmutex_trylock(sys_lwmutex_t* lw) {
    HostMutex* m = FindMutex(lw);
    if (!m) return CellError(CELL_ESRCH);
    if (!m->m.try_lock()) return CellError(CELL_EBUSY);
    lw->recursive_count++;
    return CELL_OK;
}

int32_t sys_lwmutex_unlock(sys_lwmutex_t* lw) {
    HostMutex* m = FindMutex(lw);
    if (!m) return CellError(CELL_ESRCH);
    if (lw->recursive_count == 0) return CellError(CELL_EPERM);
    lw->recursive_count--;
    m->m.unlock();
    return CELL_OK;
}

int32_t sys_semaphore_create(sys_semaphore_t* sem, const sys_semaphore_attribute_t*, int32_t initial, int32_t max) {
    if (!sem) return CellError(CELL_EFAULT);
    if (max <= 0 || initial < 0 || initial > max) return CellError(CELL_EINVAL);
    std::lock_guard<std::mutex> lock(g_tableMutex);
    std::unique_ptr<HostSemaphore> s(new HostSemaphore());
    s->count = initial;
    s->max = max;
    g_semaphores.push_back(std::move(s));
    *sem = static_cast<sys_semaphore_t>(g_semaphores.size());
    return CELL_OK;
}

int32_t sys_semaphore_destroy(sys_semaphore_t sem) {
    std::lock_guard<std::mutex> lock(g_tableMutex);
    if (sem == 0 || sem > g_semaphores.size() || !g_semaphores[sem - 1]) return CellError(CELL_ESRCH);
    g_semaphores[sem - 1].reset();
    return CELL_OK;
}

int32_t sys_semaphore_wait(sys_semaphore_t sem, uint64_t timeout_us) {
    HostSemaphore* s = FindSemaphore(sem);
    if (!s) return CellError(CELL_ESRCH);
    std::unique_lock<std::mutex> lock(s->m);
    if (timeout_us == 0) {
        s->cv.wait(lock, [s] { return s->count > 0; });
    } else if (!s->cv.wait_for(lock, std::chrono::microseconds(timeout_us), [s] { return s->count > 0; })) {
        return CellError(CELL_ETIMEDOUT);
    }
    s->count--;
    return CELL_OK;
}

int32_t sys_semaphore_trywait(sys_semaphore_t sem) {
    HostSemaphore* s = FindSemaphore(sem);
    if (!s) return CellError(CELL_ESRCH);
    std::lock_guard<std::mutex> lock(s->m);
    if (s->count <= 0) return CellError(CELL_EBUSY);
    s->count--;
    return CELL_OK;
}

int32_t sys_semaphore_post(sys_semaphore_t sem, int32_t count) {
    HostSemaphore* s = FindSemaphore(sem);
    if (!s) return CellError(CELL_ESRCH);
    if (count <= 0) return CellError(CELL_EINVAL);
    {
        std::lock_guard<std::mutex> lock(s->m);
        if (s->count + count > s->max) return CellError(CELL_EBUSY);
        s->count += count;
    }
    s->cv.notify_all();
    return CELL_OK;
}
