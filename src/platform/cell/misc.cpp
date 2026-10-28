// Small shims: cellSysmodule (no-op) and cellVideoOutSetGamma (stored for the final blit).
#include <atomic>

#include "platform/cell/cell_errors.h"
#include "platform/cell/sysmodule.h"
#include "platform/cell/videoout.h"

int32_t cellSysmoduleLoadModule(uint16_t) { return CELL_OK; }
int32_t cellSysmoduleUnloadModule(uint16_t) { return CELL_OK; }
int32_t cellSysmoduleIsLoaded(uint16_t) { return CELL_OK; }

namespace {
std::atomic<float> g_gamma(1.0f);
}

// TODO(verify): the PS3's accepted range and error code for out-of-range values; the game only
// passes values from its brightness option (IKGameManager_ApplyOptions_maybe 0x13920).
int32_t cellVideoOutSetGamma(uint32_t, float gamma) {
    g_gamma.store(gamma);
    return CELL_OK;
}

namespace dotd::platform {
float GetVideoOutGamma() { return g_gamma.load(); }
}
