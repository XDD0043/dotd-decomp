// sys_sync.h - LV2 lightweight mutexes and semaphores as the game uses them.
// sys_lwmutex_t keeps its 24-byte PS3 size (it is embedded in game objects); the first word holds a
// host handle id. Semaphores are ids, like on the PS3.
#pragma once
#include <cstdint>

struct sys_lwmutex_t {
    uint32_t handle;   // PS3: lock_var (8 bytes); here: host mutex id
    uint32_t pad0;
    uint32_t attribute;
    uint32_t recursive_count;
    uint32_t sleep_queue;
    uint32_t pad1;
};
static_assert(sizeof(sys_lwmutex_t) == 24, "PS3 layout");

struct sys_lwmutex_attribute_t {
    uint32_t protocol;   // SYS_SYNC_PRIORITY etc. (ignored on the host)
    uint32_t recursive;  // SYS_SYNC_RECURSIVE 0x10 / SYS_SYNC_NOT_RECURSIVE 0x20
    char name[8];
};

typedef uint32_t sys_semaphore_t;

struct sys_semaphore_attribute_t {
    uint32_t protocol;
    uint32_t pshared;
    uint64_t ipc_key;
    int32_t flags;
    uint32_t pad;
    char name[8];
};

int32_t sys_lwmutex_create(sys_lwmutex_t* lwmutex, const sys_lwmutex_attribute_t* attr);
int32_t sys_lwmutex_destroy(sys_lwmutex_t* lwmutex);
int32_t sys_lwmutex_lock(sys_lwmutex_t* lwmutex, uint64_t timeout_us);  // 0 = wait forever
int32_t sys_lwmutex_trylock(sys_lwmutex_t* lwmutex);
int32_t sys_lwmutex_unlock(sys_lwmutex_t* lwmutex);

int32_t sys_semaphore_create(sys_semaphore_t* sem, const sys_semaphore_attribute_t* attr, int32_t initial, int32_t max);
int32_t sys_semaphore_destroy(sys_semaphore_t sem);
int32_t sys_semaphore_wait(sys_semaphore_t sem, uint64_t timeout_us);  // 0 = wait forever
int32_t sys_semaphore_trywait(sys_semaphore_t sem);
int32_t sys_semaphore_post(sys_semaphore_t sem, int32_t count);
