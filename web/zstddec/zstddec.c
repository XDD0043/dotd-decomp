// zstddec.c - the zstd decoder as the page's download worker uses it (pack-worker.js): one frame at a time,
// its compressed bytes fed as they arrive from the network, decoded straight into one buffer the size of the
// whole file (so the decoder keeps no window of its own), optionally against a prefix: the content of another
// file the browser already has, which the frame was compressed as a difference to (pack.py).
#include <stddef.h>
#include <stdint.h>

#include <emscripten.h>

#define ZSTD_STATIC_LINKING_ONLY
#include "zstd.h"

static ZSTD_DCtx* g_ctx;
static ZSTD_outBuffer g_out;
static const char* g_error = "";

// Starts a frame. `out` / `capacity`: where the whole content goes (it must not move until the frame is done).
// `prefix` / `prefixSize`: the base content of a difference, or 0. Returns 0, or -1 (dotd_zstd_error says why).
EMSCRIPTEN_KEEPALIVE int dotd_zstd_begin(void* out, size_t capacity, const void* prefix, size_t prefixSize) {
    if (g_ctx == NULL) g_ctx = ZSTD_createDCtx();
    if (g_ctx == NULL) {
        g_error = "no decoder";
        return -1;
    }
    ZSTD_DCtx_reset(g_ctx, ZSTD_reset_session_and_parameters);
    size_t r = ZSTD_DCtx_setParameter(g_ctx, ZSTD_d_windowLogMax, ZSTD_WINDOWLOG_MAX);
    if (!ZSTD_isError(r)) r = ZSTD_DCtx_setParameter(g_ctx, ZSTD_d_stableOutBuffer, 1);
    if (!ZSTD_isError(r) && prefixSize != 0) r = ZSTD_DCtx_refPrefix(g_ctx, prefix, prefixSize);
    if (ZSTD_isError(r)) {
        g_error = ZSTD_getErrorName(r);
        return -1;
    }
    g_out.dst = out;
    g_out.size = capacity;
    g_out.pos = 0;
    g_error = "";
    return 0;
}

// The next `size` compressed bytes. Returns 0 when the frame is complete (its checksum verified), 1 when it
// wants more, -1 on an error.
EMSCRIPTEN_KEEPALIVE int dotd_zstd_feed(const void* in, size_t size) {
    ZSTD_inBuffer input = {in, size, 0};
    while (input.pos < input.size) {
        const size_t r = ZSTD_decompressStream(g_ctx, &g_out, &input);
        if (ZSTD_isError(r)) {
            g_error = ZSTD_getErrorName(r);
            return -1;
        }
        if (r == 0) return 0;
    }
    return 1;
}

EMSCRIPTEN_KEEPALIVE size_t dotd_zstd_written(void) { return g_out.pos; }
EMSCRIPTEN_KEEPALIVE const char* dotd_zstd_error(void) { return g_error; }
